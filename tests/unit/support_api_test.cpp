#include "crown/api/error.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/support.hpp"
#include "crown/storage/physical.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
#include <utility>
#include <vector>

namespace {
using namespace crown;
using namespace crown::runtime;

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

template <class Action>
void expect_error(Action&& action, std::string_view code) {
  try {
    action();
  } catch (const Error& failure) {
    check(failure.code() == code,
          "wrong error: " + failure.code() + ", expected " + std::string(code));
    return;
  }
  throw std::runtime_error("expected error: " + std::string(code));
}

Value n(std::int64_t value) { return value; }
Value s(std::string value) { return value; }
Value date(std::string_view value) { return Date::parse(value); }
Value decimal(std::string_view value) { return Decimal::parse(value); }

PhysicalPlan unary_plan() {
  const Catalog catalog{1, {{"unary", {{"x", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}},
                    {{"unary", TableId{0}, {VariableId{0}}}},
                    {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"unary", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan typed_plan() {
  const Catalog catalog{2, {{"typed", {
      {"word", ScalarType::string}, {"day", ScalarType::date},
      {"amount", ScalarType::decimal, false, Collation::binary, DecimalSpec{8, 2}}}}}};
  const Query query{{{"word", ScalarType::string}, {"day", ScalarType::date},
                     {"amount", ScalarType::decimal}},
                    {{"typed", TableId{0}, {VariableId{0}, VariableId{1}, VariableId{2}}}},
                    {{VariableId{0}, "word"}, {VariableId{1}, "day"}, {VariableId{2}, "amount"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"typed", NodeKind::native, {VariableId{0}, VariableId{1}, VariableId{2}}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan generalized_pair_plan() {
  const Catalog catalog{4, {
      {"left", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}},
      {"right", {{"y", ScalarType::int64}, {"z", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}, {"z", ScalarType::int64}},
                    {{"left", TableId{0}, {VariableId{0}, VariableId{1}}},
                     {"right", TableId{1}, {VariableId{1}, VariableId{2}}}},
                    {{VariableId{1}, "y"}}, false};
  const FreeConnexTree tree{NodeId{0}, {
      {"intersection", NodeKind::generalized, {VariableId{1}}, {NodeId{1}, NodeId{2}}, {}, {}},
      {"left", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}},
      {"right", NodeKind::native, {VariableId{1}, VariableId{2}}, {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan nested_plan() {
  const Catalog catalog{6, {
      {"b", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}},
      {"c", {{"y", ScalarType::int64}}},
      {"g", {{"x", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
                    {{"b", TableId{0}, {VariableId{0}, VariableId{1}}},
                     {"c", TableId{1}, {VariableId{1}}},
                     {"g", TableId{2}, {VariableId{0}}}},
                    {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0}, {
      {"root", NodeKind::generalized, {VariableId{0}}, {NodeId{1}, NodeId{3}}, {}, {}},
      {"b", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{2}}, 0, {}},
      {"c", NodeKind::native, {VariableId{1}}, {}, 1, {}},
      {"g", NodeKind::native, {VariableId{0}}, {}, 2, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan native_join_plan() {
  const Catalog catalog{4, {
      {"left", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}},
      {"right", {{"y", ScalarType::int64}, {"z", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}, {"z", ScalarType::int64}},
                    {{"left", TableId{0}, {VariableId{0}, VariableId{1}}},
                     {"right", TableId{1}, {VariableId{1}, VariableId{2}}}},
                    {{VariableId{0}, "x"}, {VariableId{1}, "y"}, {VariableId{2}, "z"}}, false};
  const FreeConnexTree tree{NodeId{0}, {
      {"left", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{1}}, 0, {}},
      {"right", NodeKind::native, {VariableId{1}, VariableId{2}}, {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

const NodeSupportSnapshot& node(const SupportSnapshot& snapshot, NodeId id) {
  return snapshot.nodes.at(id.value);
}

const ProjectionKeySnapshot* key_with_values(
    const std::vector<ProjectionKeySnapshot>& keys, const Row& values) {
  const auto found = std::find_if(keys.begin(), keys.end(), [&](const auto& key) {
    return key.key.values() == values;
  });
  return found == keys.end() ? nullptr : &*found;
}

bool zero(const SupportMetrics& m) {
  return m.work == 0 && m.copied_rows == 0 && m.copied_index_memberships == 0 &&
      m.copied_metadata_entries == 0 && m.copied_child_flags == 0 &&
      m.native_record_visits == 0 && m.child_key_probes == 0 && m.child_key_events == 0 &&
      m.survivor_transitions == 0 && m.parent_key_transitions == 0 &&
      m.visible_key_transitions == 0 && m.candidates_created == 0 && m.candidates_reclaimed == 0 &&
      m.storage_changes == 0 && m.metadata_changes == 0 && m.saved_child_flags == 0 &&
      m.journal_records == 0 && m.events_enqueued == 0 && m.events_applied == 0 && m.queue_peak == 0;
}

bool has_transition(const SupportEpoch& epoch, NodeId node_id, SupportRole role,
                    SetOperation operation, const Row& tuple) {
  return std::any_of(epoch.transitions.begin(), epoch.transitions.end(), [&](const auto& event) {
    return event.handle.node == node_id && event.handle.role == role &&
        event.operation == operation && event.tuple.values() == tuple;
  });
}

void check_journaled_mutation(const SupportEpoch& epoch) {
  const auto& m = epoch.metrics;
  check(m.copied_rows == 0 && m.copied_index_memberships == 0 &&
        m.copied_metadata_entries == 0 && m.copied_child_flags == 0,
        "an affected-record update must not report copied state");
  check(epoch.journal && epoch.journal->sequence == epoch.sequence &&
        m.journal_records == epoch.journal->records.size() && m.journal_records > 0,
        "a real update retains its affected-record journal and accounts for its records");
  check(m.storage_changes > 0 && m.metadata_changes > 0,
        "a real update accounts for storage and metadata changes");
}

using RecordView = std::tuple<Row, std::size_t, std::vector<bool>, bool>;
using KeyView = std::pair<Row, std::uint64_t>;

std::vector<RecordView> record_views(const NodeSupportSnapshot& state) {
  std::vector<RecordView> result;
  for (const auto& record : state.records)
    result.emplace_back(crown::storage::export_row(record.tuple.values()), record.satisfied.value, record.child_present, record.survives);
  return result;
}

std::vector<KeyView> key_views(const std::vector<ProjectionKeySnapshot>& keys) {
  std::vector<KeyView> result;
  for (const auto& key : keys) result.emplace_back(crown::storage::export_row(key.key.values()), key.support.value);
  return result;
}

std::vector<Row> row_views(const std::vector<storage::Tuple>& tuples) {
  std::vector<Row> result;
  for (const auto& tuple : tuples) result.push_back(crown::storage::export_row(tuple.values()));
  return result;
}

void compare_canonical_state(const SupportSnapshot& left, const SupportSnapshot& right) {
  check(left.sequence == right.sequence && left.has_answer == right.has_answer,
        "propagation order changed sequence or answer state");
  check(left.nodes.size() == right.nodes.size(), "propagation order changed node count");
  for (std::size_t i = 0; i < left.nodes.size(); ++i) {
    const auto& a = left.nodes[i];
    const auto& b = right.nodes[i];
    check(a.node == b.node && a.kind == b.kind, "propagation order changed node identity");
    check(record_views(a) == record_views(b), "propagation order changed canonical records/flags");
    check(row_views(a.survivors) == row_views(b.survivors), "propagation order changed survivors");
    check(key_views(a.parent_keys) == key_views(b.parent_keys), "propagation order changed parent support counts");
    check(a.visible_keys.has_value() == b.visible_keys.has_value(), "propagation order changed visible shape");
    if (a.visible_keys) check(key_views(*a.visible_keys) == key_views(*b.visible_keys),
                              "propagation order changed visible support counts");
  }
}

void checked_projection_counters() {
  constexpr auto maximum = std::numeric_limits<std::uint64_t>::max();
  const std::uint64_t above_double_exact = (std::uint64_t{1} << 53U) + 117U;
  check(increment_support({above_double_exact}).value == above_double_exact + 1U,
        "projection counters increment exactly above the double integer range");
  check(increment_support({maximum - 1U}).value == maximum,
        "projection counter reaches uint64 max exactly");
  expect_error([&] { static_cast<void>(increment_support({maximum})); }, "support_overflow");
  expect_error([&] { static_cast<void>(increment_support({}, 0)); }, "support_overflow");
  check(decrement_support({1}).value == 0, "projection support decrements to zero");
  expect_error([&] { static_cast<void>(decrement_support({})); }, "runtime_contract");
}

void options_and_validation_are_checked_before_commit() {
  auto plan = unary_plan();
  SupportOptions invalid_support;
  invalid_support.support_limit = 0;
  expect_error([&] { SupportRuntime runtime(plan, invalid_support); }, "invalid_options");
  SupportOptions invalid_order;
  invalid_order.order = static_cast<PropagationOrder>(255);
  expect_error([&] { SupportRuntime runtime(plan, invalid_order); }, "invalid_options");

  SupportRuntime runtime(plan);
  const auto owner = runtime.owner();
  expect_error([&] { static_cast<void>(runtime.apply({2, NodeId{0}, SetOperation::insert, {n(1)}})); },
               "invalid_sequence");
  expect_error([&] { static_cast<void>(runtime.apply({1, NodeId{7}, SetOperation::insert, {n(1)}})); },
               "invalid_native_update");
  expect_error([&] { static_cast<void>(runtime.apply({1, NodeId{0}, SetOperation::insert, {n(1), n(2)}})); },
               "invalid_tuple");
  expect_error([&] { static_cast<void>(runtime.apply({1, NodeId{0}, static_cast<SetOperation>(255), {n(1)}})); },
               "invalid_native_update");
  check(runtime.sequence() == 0 && runtime.owner() == owner && !runtime.has_answer() &&
        !runtime.find(NodeId{0}, SupportRole::records, {n(1)}),
        "invalid updates preserve sequence, owner, answer, and records");

  SupportRuntime generalized(generalized_pair_plan());
  expect_error([&] { static_cast<void>(generalized.apply({1, NodeId{0}, SetOperation::insert, {n(10)}})); },
               "invalid_native_update");
  check(generalized.sequence() == 0 && !generalized.has_answer(),
        "external generalized writes are rejected without advancing the epoch");

  SupportRuntime typed(typed_plan());
  const Row accepted{s("é"), date("2024-02-29"), decimal("123.40")};
  expect_error([&] { static_cast<void>(typed.apply({1, NodeId{0}, SetOperation::insert,
                                                    {s("é"), s("2024-02-29"), decimal("123.40")}})); },
               "invalid_tuple");
  check(typed.sequence() == 0 && !typed.find(NodeId{0}, SupportRole::records, accepted),
        "wrong scalar tags are rejected atomically");
  const auto inserted = typed.apply({1, NodeId{0}, SetOperation::insert, accepted});
  check(inserted.native_changed && typed.find(NodeId{0}, SupportRole::records, accepted).has_value(),
        "typed logical native tuple is accepted");
  check(!typed.find(NodeId{0}, SupportRole::records,
                    {s("é"), date("2024-02-29"), decimal("123.41")}),
        "decimal key lookup preserves exact value equality");
  check(!typed.find(NodeId{0}, SupportRole::records,
                    {s("é"), date("2024-03-01"), decimal("123.40")}),
        "date key lookup preserves exact value equality");
  check(!typed.find(NodeId{0}, SupportRole::records,
                    {s("e"), date("2024-02-29"), decimal("123.40")}),
        "string key lookup preserves binary value equality");
  typed.check_invariants();
}

void noops_sequences_metrics_and_owned_handles() {
  const auto plan = generalized_pair_plan();
  SupportRuntime runtime(plan, SupportOptions{.capture_transitions = true});
  const Row left_first{n(1), n(10)};
  const Row left_second{n(2), n(10)};
  // The right native scope is sorted by VariableId as {y, z}.
  const Row right{n(10), n(7)};

  const auto first = runtime.apply({1, NodeId{1}, SetOperation::insert, left_first});
  check(first.native_changed && first.sequence == 1 && !first.has_answer,
        "first left witness creates an incomplete generalized candidate");
  check_journaled_mutation(first);
  check(first.metrics.native_record_visits == 1 && first.metrics.child_key_probes == 0 &&
        first.metrics.parent_key_transitions == 1 && first.metrics.candidates_created == 1,
        "first leaf insertion reports native work and the generalized candidate event");
  const auto first_left_key = runtime.find(NodeId{1}, SupportRole::parent_support, {n(10)});
  check(first_left_key.has_value(), "left projection support key is findable through the generic role API");
  const auto first_snapshot = runtime.snapshot();
  const auto first_support = key_with_values(node(first_snapshot, NodeId{1}).parent_keys, {n(10)});
  check(first_support && first_support->support.value == 1 && first_support->handle == *first_left_key,
        "left key snapshot reports its exact support count and stable public handle");

  const auto second = runtime.apply({2, NodeId{1}, SetOperation::insert, left_second});
  check(second.native_changed && !second.has_answer && second.metrics.native_record_visits == 1,
        "second witness changes a native set but does not repeat a positive key event");
  check_journaled_mutation(second);
  check(second.metrics.parent_key_transitions == 0 && second.metrics.candidates_created == 0 &&
        !has_transition(second, NodeId{1}, SupportRole::parent_support, SetOperation::insert, {n(10)}),
        "a positive projection count change is local metadata, not a membership transition");
  const auto second_snapshot = runtime.snapshot();
  const auto second_support = key_with_values(node(second_snapshot, NodeId{1}).parent_keys, {n(10)});
  check(second_support && second_support->support.value == 2 && second_support->handle == *first_left_key,
        "stable support handle persists while its exact count changes from one to two");

  const auto third = runtime.apply({3, NodeId{2}, SetOperation::insert, right});
  check(third.native_changed && third.has_answer && runtime.has_answer(),
        "a matching right witness makes the generalized root survive");
  const auto root_record = runtime.find(NodeId{0}, SupportRole::records, {n(10)});
  const auto root_survivor = runtime.find(NodeId{0}, SupportRole::survivors, {n(10)});
  const auto root_visible = runtime.find(NodeId{0}, SupportRole::visible, {n(10)});
  check(root_record && root_survivor && root_visible && runtime.get(*root_record)->values() == Row{n(10)} &&
        runtime.get(*root_survivor)->values() == Row{n(10)} && runtime.get(*root_visible)->values() == Row{n(10)},
        "generic find/get exposes owning records, survivors, and visible keys");
  const auto root_state = runtime.snapshot();
  const auto root_parent = key_with_values(node(root_state, NodeId{0}).parent_keys, {});
  check(node(root_state, NodeId{0}).visible_keys.has_value(),
        "the output node exposes a visible projection relation");
  const auto root_output = key_with_values(*node(root_state, NodeId{0}).visible_keys, {n(10)});
  check(root_parent && root_parent->support.value == 1 && root_output && root_output->support.value == 1,
        "snapshot owns root parent and visible support counts");

  const auto fourth = runtime.apply({4, NodeId{1}, SetOperation::erase, left_first});
  check(fourth.native_changed && fourth.has_answer &&
        runtime.find(NodeId{1}, SupportRole::parent_support, {n(10)}) == first_left_key,
        "decrementing a shared support key leaves its handle live");
  const auto remaining_snapshot = runtime.snapshot();
  const auto remaining = key_with_values(node(remaining_snapshot, NodeId{1}).parent_keys, {n(10)});
  check(remaining && remaining->support.value == 1 && remaining->handle == *first_left_key,
        "support count reaches one without an erase/insert transition");
  check(!has_transition(fourth, NodeId{1}, SupportRole::parent_support, SetOperation::erase, {n(10)}),
        "nonzero decrement emits no local membership transition");

  const auto fifth = runtime.apply({5, NodeId{1}, SetOperation::erase, left_second});
  check(fifth.native_changed && !fifth.has_answer && !runtime.has_answer(),
        "removing the last left witness makes the root stop surviving");
  check(!runtime.get(*first_left_key) &&
        has_transition(fifth, NodeId{1}, SupportRole::parent_support, SetOperation::erase, {n(10)}),
        "zero crossing removes the old key handle and captures its owned deleted key");

  const auto sixth = runtime.apply({6, NodeId{1}, SetOperation::insert, left_first});
  const auto replacement_key = runtime.find(NodeId{1}, SupportRole::parent_support, {n(10)});
  check(sixth.native_changed && sixth.has_answer && replacement_key &&
        replacement_key->owner == first_left_key->owner && replacement_key->node == first_left_key->node &&
        replacement_key->role == first_left_key->role && replacement_key->tuple != first_left_key->tuple &&
        has_transition(sixth, NodeId{1}, SupportRole::parent_support, SetOperation::insert, {n(10)}),
        "reinsertion allocates a fresh tuple ID while preserving runtime/node/role identity");

  const auto before_noop = runtime.snapshot();
  const auto duplicate = runtime.apply({7, NodeId{1}, SetOperation::insert, left_first});
  check(!duplicate.native_changed && duplicate.sequence == 7 && duplicate.has_answer &&
        zero(duplicate.metrics) && duplicate.transitions.empty() && !duplicate.journal,
        "duplicate insert is a zero-work no-op that still consumes its sequence");
  const auto absent = runtime.apply({8, NodeId{1}, SetOperation::erase, {n(99), n(10)}});
  check(!absent.native_changed && absent.sequence == 8 && absent.has_answer &&
        zero(absent.metrics) && absent.transitions.empty() && !absent.journal,
        "absent delete is a zero-work no-op that still consumes its sequence");
  check(before_noop.sequence == 6 && runtime.sequence() == 8,
        "owning snapshots retain their captured sequence across later no-op epochs");
  const auto deleted_transition = std::find_if(fifth.transitions.begin(), fifth.transitions.end(), [](const auto& event) {
    return event.handle.node == NodeId{1} && event.handle.role == SupportRole::parent_support &&
        event.operation == SetOperation::erase;
  });
  check(deleted_transition != fifth.transitions.end(), "capture includes the local support-key deletion");
  auto deleted_key_copy = deleted_transition->tuple;
  check(deleted_key_copy.values() == Row{n(10)}, "delete transition owns the key row");
  static_cast<void>(runtime.apply({9, NodeId{2}, SetOperation::erase, right}));
  const auto last_delete = runtime.apply({10, NodeId{1}, SetOperation::erase, left_first});
  check(last_delete.metrics.candidates_reclaimed == 1,
        "the generalized candidate is reclaimed after its final child support disappears");
  check(deleted_key_copy.values() == Row{n(10)},
        "captured transition key survives deletion of all corresponding live state");
  runtime.check_invariants();
}

void support_limit_failure_is_atomic_and_retryable() {
  SupportOptions options;
  options.support_limit = 1;
  options.capture_transitions = true;
  SupportRuntime runtime(unary_plan(), options);
  const auto first = runtime.apply({1, NodeId{0}, SetOperation::insert, {n(20)}});
  const auto key = runtime.find(NodeId{0}, SupportRole::parent_support, {});
  check(first.native_changed && key, "support counter reaches configured limit exactly");
  const auto before = runtime.snapshot();
  const auto owner = runtime.owner();
  const auto before_stats = runtime.storage_statistics();
  const auto retained_journal = first.journal;

  expect_error([&] {
    static_cast<void>(runtime.apply({2, NodeId{0}, SetOperation::insert, {n(21)}}));
  }, "support_overflow");
  check(runtime.sequence() == 1 && runtime.owner() == owner && runtime.snapshot().sequence == before.sequence &&
        runtime.snapshot().has_answer == before.has_answer && runtime.get(*key).has_value() &&
        !runtime.find(NodeId{0}, SupportRole::records, {n(21)}),
        "support overflow rolls back affected changes and preserves old handles and state");
  const auto after_failure_stats = runtime.storage_statistics();
  check(after_failure_stats.live_records == before_stats.live_records &&
        after_failure_stats.retained_records == before_stats.retained_records &&
        after_failure_stats.pins == before_stats.pins && retained_journal == first.journal &&
        retained_journal && retained_journal->records.size() == first.metrics.journal_records,
        "a failed update publishes no partial journal or storage changes");
  const auto after_failure = runtime.snapshot();
  const auto still_one = key_with_values(node(after_failure, NodeId{0}).parent_keys, {});
  check(still_one && still_one->support.value == 1 && still_one->handle == *key,
        "failed increment preserves the exact counter and support handle");
  runtime.check_invariants();

  const auto remove = runtime.apply({2, NodeId{0}, SetOperation::erase, {n(20)}});
  check(remove.native_changed && !runtime.get(*key), "retry path frees the bounded projection support");
  const auto inserted = runtime.apply({3, NodeId{0}, SetOperation::insert, {n(21)}});
  const auto replacement = runtime.find(NodeId{0}, SupportRole::parent_support, {});
  check(inserted.native_changed && replacement && replacement->tuple != key->tuple,
        "same logical key can be retried after capacity is freed with a fresh tuple ID");
  runtime.check_invariants();
}

void work_limit_boundaries_and_atomic_retry() {
  SupportOptions unlimited;
  unlimited.work_limit = std::nullopt;
  SupportRuntime probe(unary_plan(), unlimited);
  const auto measured = probe.apply({1, NodeId{0}, SetOperation::insert, {n(3)}}).metrics.work;
  check(measured > 0, "a real reference mutation reports nonzero charged work");

  SupportOptions exact;
  exact.work_limit = measured;
  SupportRuntime accepted(unary_plan(), exact);
  const auto at_limit = accepted.apply({1, NodeId{0}, SetOperation::insert, {n(3)}});
  check(at_limit.metrics.work == measured && accepted.sequence() == 1,
        "work limit accepts the exact measured boundary");

  SupportOptions short_by_one;
  short_by_one.work_limit = measured - 1U;
  SupportRuntime rejected(unary_plan(), short_by_one);
  const auto rejected_owner = rejected.owner();
  expect_error([&] {
    static_cast<void>(rejected.apply({1, NodeId{0}, SetOperation::insert, {n(3)}}));
  }, "resource_limit");
  check(rejected.sequence() == 0 && rejected.owner() == rejected_owner && !rejected.has_answer() &&
        !rejected.find(NodeId{0}, SupportRole::records, {n(3)}),
        "under-bound work failure preserves sequence, owner, answer, and records");

  SupportOptions zero_work;
  zero_work.work_limit = 0;
  SupportRuntime no_work(unary_plan(), zero_work);
  const auto no_op = no_work.apply({1, NodeId{0}, SetOperation::erase, {n(3)}});
  check(no_op.sequence == 1 && !no_op.native_changed && zero(no_op.metrics),
        "a no-op remains legal at a zero work cap and consumes its sequence");
  expect_error([&] {
    static_cast<void>(no_work.apply({2, NodeId{0}, SetOperation::insert, {n(3)}}));
  }, "resource_limit");
  check(no_work.sequence() == 1 && !no_work.find(NodeId{0}, SupportRole::records, {n(3)}),
        "zero-work cap failure is atomic after a consumed no-op sequence");

}

void fifo_and_lifo_produce_same_canonical_state() {
  const auto plan = nested_plan();
  SupportOptions fifo_options;
  fifo_options.order = PropagationOrder::fifo;
  fifo_options.capture_transitions = true;
  SupportOptions lifo_options = fifo_options;
  lifo_options.order = PropagationOrder::lifo;
  SupportRuntime fifo(plan, fifo_options);
  SupportRuntime lifo(plan, lifo_options);

  const std::vector<NativeSetUpdate> prefix{
      {1, NodeId{1}, SetOperation::insert, {n(1), n(10)}},
      {2, NodeId{1}, SetOperation::insert, {n(2), n(10)}}};
  for (const auto& update : prefix) {
    const auto a = fifo.apply(update);
    const auto b = lifo.apply(update);
    check(a.has_answer == b.has_answer, "FIFO/LIFO differ before multi-key propagation");
    compare_canonical_state(fifo.snapshot(), lifo.snapshot());
  }

  const auto fifo_epoch = fifo.apply({3, NodeId{2}, SetOperation::insert, {n(10)}});
  const auto lifo_epoch = lifo.apply({3, NodeId{2}, SetOperation::insert, {n(10)}});
  check(!fifo_epoch.has_answer && !lifo_epoch.has_answer,
        "nested support creates two root candidates before their root-side witnesses arrive");
  check(fifo_epoch.metrics.native_record_visits == 3 && lifo_epoch.metrics.native_record_visits == 3 &&
        fifo_epoch.metrics.child_key_events == 3 && lifo_epoch.metrics.child_key_events == 3,
        "one nested event visits only its native source and the two matching indexed parent rows");
  compare_canonical_state(fifo.snapshot(), lifo.snapshot());

  const auto fifo_first = fifo.apply({4, NodeId{3}, SetOperation::insert, {n(1)}});
  const auto lifo_first = lifo.apply({4, NodeId{3}, SetOperation::insert, {n(1)}});
  check(fifo_first.has_answer && lifo_first.has_answer, "first root-side witness makes an output answer true");
  compare_canonical_state(fifo.snapshot(), lifo.snapshot());
  const auto fifo_second = fifo.apply({5, NodeId{3}, SetOperation::insert, {n(2)}});
  const auto lifo_second = lifo.apply({5, NodeId{3}, SetOperation::insert, {n(2)}});
  check(fifo_second.has_answer && lifo_second.has_answer && fifo.has_answer() && lifo.has_answer(),
        "second root-side witness preserves answers under both propagation orders");
  compare_canonical_state(fifo.snapshot(), lifo.snapshot());

  const auto remove_c_fifo = fifo.apply({6, NodeId{2}, SetOperation::erase, {n(10)}});
  const auto remove_c_lifo = lifo.apply({6, NodeId{2}, SetOperation::erase, {n(10)}});
  check(!remove_c_fifo.has_answer && !remove_c_lifo.has_answer &&
        remove_c_fifo.metrics.survivor_transitions > 0 && remove_c_lifo.metrics.survivor_transitions > 0,
        "one child removal crosses local survivor memberships without emitting a full answer delta");
  compare_canonical_state(fifo.snapshot(), lifo.snapshot());
  fifo.check_invariants();
  lifo.check_invariants();
}

void reference_storage_snapshot_copy_owns_and_preserves_ids() {
  const auto plan = native_join_plan();
  storage::ReferencePlanStorage original(plan);
  const auto& root = plan.nodes()[0];
  auto& original_table = original.table(root.records);
  const auto row = root.layout.tuple({n(1), n(10)});
  const auto inserted = original_table.insert(row);
  check(inserted.inserted && original_table.indices().size() > 0,
        "native parent plan supplies a populated indexed relation");

  const std::vector<FieldId> extra_fields{FieldId{0}};
  const auto extra_target = storage::projected_layout(LayoutId{701}, root.layout, extra_fields);
  const storage::Projection extra_projection{root.layout, extra_target, extra_fields};
  const auto extra_index = original_table.add_index(extra_projection);
  const auto original_indices = original_table.indices();
  const auto old_owner = original_table.owner();
  const auto old_index_max = std::max_element(original_indices.begin(), original_indices.end(),
      [](IndexId a, IndexId b) { return a.value < b.value; })->value;

  auto copy = original.snapshot_copy();
  auto& copied_table = copy.table(root.records);
  check(copied_table.owner() != old_owner && copied_table.indices() == original_indices,
        "plan snapshot copy gets a fresh owner while preserving registered index IDs");
  const auto copied_handle = copied_table.find(row);
  check(copied_handle && copied_handle->tuple == inserted.handle.tuple && copied_handle->owner != inserted.handle.owner,
        "copied row keeps its tuple ID under a fresh backend owner");
  expect_error([&] { static_cast<void>(copied_table.get(inserted.handle)); }, "foreign_handle");
  check(copied_table.snapshot().size() == 1 && copied_table.get(*copied_handle)->values() == row.values(),
        "snapshot copy owns cloned rows and returns them through its own handles");
  check(std::ranges::equal(copied_table.projection(extra_index).fields(),extra_fields) &&
        copied_table.key_count(extra_index) == original_table.key_count(extra_index),
        "snapshot copy preserves an added index definition and its memberships");
  const auto original_key = original_table.projection(extra_index).apply(row);
  const auto copied_bucket = copied_table.bucket(extra_index, original_key);
  check(copied_bucket.size() == 1 && copied_bucket[0] == *copied_handle,
        "copied index buckets resolve to copied-owner handles with preserved IDs");

  const std::vector<FieldId> next_fields{FieldId{1}};
  const auto original_next_target = storage::projected_layout(LayoutId{702}, root.layout, next_fields);
  const auto copied_next_target = storage::projected_layout(LayoutId{703}, root.layout, next_fields);
  const auto original_next = original_table.add_index({root.layout, original_next_target, next_fields});
  const auto copied_next = copied_table.add_index({root.layout, copied_next_target, next_fields});
  check(original_next.value == old_index_max + 1U && copied_next == original_next,
        "both independent copies continue their per-table monotonic index ID counters");

  const auto second_row = root.layout.tuple({n(2), n(11)});
  const auto copied_insert = copied_table.insert(second_row);
  check(copied_insert.inserted && copied_insert.handle.tuple.value == inserted.handle.tuple.value + 1U &&
        !original_table.find(second_row),
        "copy mutation is independent and continues the copied tuple ID counter");
  const auto original_insert = original_table.insert(second_row);
  check(original_insert.inserted && original_insert.handle.tuple == copied_insert.handle.tuple &&
        original_insert.handle.owner == old_owner && copied_insert.handle.owner != old_owner,
        "original and copy independently allocate the same next local tuple ID");
  original.check_invariants();
  copy.check_invariants();
}

void constant_routes_and_runtime_moves() {
  const Catalog catalog{1, {}};
  const FreeConnexTree empty_tree{};
  const Query true_query{{}, {}, {}, false};
  const auto true_plan = planner::lower_tree(catalog, true_query, empty_tree);
  SupportRuntime true_runtime(true_plan);
  check(true_plan.route() == PhysicalRoute::constant_true && true_plan.inputs().empty() &&
        true_runtime.has_answer() && true_runtime.snapshot().has_answer && true_runtime.snapshot().nodes.empty(),
        "constant true has an initial answer and no physical input ports or support nodes");

  const Query false_query{{}, {}, {}, true};
  const auto false_plan = planner::lower_tree(catalog, false_query, empty_tree);
  SupportRuntime false_runtime(false_plan);
  check(false_plan.route() == PhysicalRoute::constant_false && false_plan.inputs().empty() &&
        !false_runtime.has_answer() && !false_runtime.snapshot().has_answer && false_runtime.snapshot().nodes.empty(),
        "constant false has no initial answer and no physical input ports or support nodes");
  expect_error([&] { static_cast<void>(true_runtime.apply({1, NodeId{0}, SetOperation::insert, {}})); },
               "invalid_native_update");
  check(true_runtime.sequence() == 0, "constant routes reject external node writes");

  SupportRuntime source(unary_plan());
  static_cast<void>(source.apply({1, NodeId{0}, SetOperation::insert, {n(42)}}));
  const auto source_owner = source.owner();
  const auto handle = source.find(NodeId{0}, SupportRole::records, {n(42)});
  check(handle.has_value(), "source runtime has a public handle to move");
  SupportRuntime moved(std::move(source));
  check(moved.owner() == source_owner && moved.get(*handle)->values() == Row{n(42)} && moved.sequence() == 1,
        "move construction transfers runtime ownership and keeps public handles valid");
  expect_error([&] { static_cast<void>(source.sequence()); }, "invalid_runtime");

  auto* self = &moved;
  moved = std::move(*self);
  check(moved.owner() == source_owner && moved.get(*handle)->values() == Row{n(42)},
        "pointer-aliased self-move preserves the runtime and its handles");

  SupportRuntime destination(unary_plan());
  const auto foreign = destination.owner();
  static_cast<void>(destination.apply({1, NodeId{0}, SetOperation::insert, {n(9)}}));
  const auto destination_handle = destination.find(NodeId{0}, SupportRole::records, {n(9)});
  destination = std::move(moved);
  check(destination.owner() == source_owner && destination.get(*handle)->values() == Row{n(42)},
        "move assignment transfers owner, plan, sequence, and live rows");
  expect_error([&] { static_cast<void>(destination.get(*destination_handle)); }, "foreign_support_handle");
  check(destination.owner() != foreign && destination.sequence() == 1,
        "destination's previous runtime owner is replaced on move assignment");
  expect_error([&] { static_cast<void>(moved.has_answer()); }, "invalid_runtime");
  destination.check_invariants();
}

}  // namespace

int main() {
  try {
    checked_projection_counters();
    options_and_validation_are_checked_before_commit();
    noops_sequences_metrics_and_owned_handles();
    support_limit_failure_is_atomic_and_retryable();
    work_limit_boundaries_and_atomic_retry();
    fifo_and_lifo_produce_same_canonical_state();
    reference_storage_snapshot_copy_owns_and_preserves_ids();
    constant_routes_and_runtime_moves();
  } catch (const std::exception& failure) {
    std::cerr << failure.what() << '\n';
    return 1;
  }
  return 0;
}
