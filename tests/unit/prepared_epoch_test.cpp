#include "crown/api/error.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/support.hpp"
#include "evaluator.hpp"
#include "native_input.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace {
using namespace crown;
using namespace crown::runtime;

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

void check_rollback_statistics(const storage::ArenaStatistics& before,
                               const storage::ArenaStatistics& after,
                               const std::string& context) {
  check(before.live_records == after.live_records &&
            before.retained_records == after.retained_records && before.pins == after.pins,
        context + ": failed epoch changed live/retained tuple counts or pins");
  check(after.slots >= before.slots,
        context + ": rollback unexpectedly reduced the aggregate arena high-water slot count");
  // Failed writes may grow the arena's high-water mark and free-slot count.
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

PhysicalPlan unary_plan() {
  const Catalog catalog{1, {{"unary", {{"x", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}},
                    {{"unary", TableId{0}, {VariableId{0}}}},
                    {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"unary", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan loop_alias_plan() {
  const Catalog catalog{1, {{"edge", {{"from", ScalarType::int64},
                                       {"to", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
                    {{"forward", TableId{0}, {VariableId{0}, VariableId{1}}},
                     {"reverse", TableId{0}, {VariableId{1}, VariableId{0}}}},
                    {{VariableId{0}, "x"}, {VariableId{1}, "y"}}, false};
  const FreeConnexTree tree{NodeId{0}, {
      {"intersection", NodeKind::generalized, {VariableId{0}, VariableId{1}},
       {NodeId{1}, NodeId{2}}, {}, {}},
      {"forward", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}},
      {"reverse", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan boolean_alias_plan() {
  const Catalog catalog{1, {{"unary", {{"x", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}},
                    {{"first", TableId{0}, {VariableId{0}}},
                     {"second", TableId{0}, {VariableId{0}}}}, {}, false};
  const FreeConnexTree tree{NodeId{0}, {
      {"intersection", NodeKind::generalized, {VariableId{0}},
       {NodeId{1}, NodeId{2}}, {}, {}},
      {"first", NodeKind::native, {VariableId{0}}, {}, 0, {}},
      {"second", NodeKind::native, {VariableId{0}}, {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

bool same_tuple(const storage::Tuple& left, const storage::Tuple& right) {
  return left.values() == right.values();
}

bool same_snapshot(const SupportSnapshot& left, const SupportSnapshot& right) {
  if (left.sequence != right.sequence || left.has_answer != right.has_answer ||
      left.nodes.size() != right.nodes.size()) return false;
  for (std::size_t i = 0; i < left.nodes.size(); ++i) {
    const auto& a = left.nodes[i];
    const auto& b = right.nodes[i];
    if (a.node != b.node || a.kind != b.kind || a.records.size() != b.records.size() ||
        a.survivors.size() != b.survivors.size() || a.parent_keys.size() != b.parent_keys.size() ||
        a.visible_keys.has_value() != b.visible_keys.has_value()) return false;
    for (std::size_t j = 0; j < a.records.size(); ++j) {
      const auto& x = a.records[j];
      const auto& y = b.records[j];
      if (!same_tuple(x.tuple, y.tuple) || x.handle != y.handle || x.satisfied != y.satisfied ||
          x.child_present != y.child_present || x.survives != y.survives) return false;
    }
    for (std::size_t j = 0; j < a.survivors.size(); ++j)
      if (!same_tuple(a.survivors[j], b.survivors[j])) return false;
    for (std::size_t j = 0; j < a.parent_keys.size(); ++j) {
      const auto& x = a.parent_keys[j];
      const auto& y = b.parent_keys[j];
      if (!same_tuple(x.key, y.key) || x.handle != y.handle || x.support != y.support) return false;
    }
    if (a.visible_keys) {
      if (a.visible_keys->size() != b.visible_keys->size()) return false;
      for (std::size_t j = 0; j < a.visible_keys->size(); ++j) {
        const auto& x = (*a.visible_keys)[j];
        const auto& y = (*b.visible_keys)[j];
        if (!same_tuple(x.key, y.key) || x.handle != y.handle || x.support != y.support) return false;
      }
    }
  }
  return true;
}

void expect_closed(SupportRuntime::PendingEpoch& pending) {
  check(!pending.active(), "closed prepared epoch still reports active");
  expect_error([&] { static_cast<void>(pending.stage(NodeId{0}, {n(1)})); }, "invalid_epoch");
  expect_error([&] { static_cast<void>(pending.preview()); }, "invalid_epoch");
  expect_error([&] { static_cast<void>(pending.snapshot()); }, "invalid_epoch");
  expect_error([&] { static_cast<void>(pending.commit()); }, "invalid_epoch");
  pending.rollback();
}

void check_busy_readers(SupportRuntime& runtime, SupportHandle existing) {
  expect_error([&] { static_cast<void>(runtime.has_answer()); }, "runtime_busy");
  expect_error([&] { static_cast<void>(runtime.snapshot()); }, "runtime_busy");
  expect_error([&] { static_cast<void>(runtime.find(NodeId{0}, SupportRole::records, {n(1)})); },
               "runtime_busy");
  expect_error([&] { static_cast<void>(runtime.get(existing)); }, "runtime_busy");
  expect_error([&] { static_cast<void>(runtime.storage_statistics()); }, "runtime_busy");
  expect_error([&] { runtime.check_invariants(); }, "runtime_busy");
  expect_error([&] {
    static_cast<void>(runtime.apply({runtime.sequence() + 1, NodeId{0}, SetOperation::insert, {n(3)}}));
  }, "runtime_busy");
  expect_error([&] {
    static_cast<void>(runtime.begin_epoch(runtime.sequence() + 1, SetOperation::insert));
  }, "runtime_busy");
}

Relation visible_answers(const SupportSnapshot& snapshot, NodeId root) {
  Relation result;
  const auto& visible = snapshot.nodes.at(root.value).visible_keys;
  check(visible.has_value(), "query root has no visible projection");
  for (const auto& key : *visible) result.insert(crown::storage::export_row(key.key.values()));
  return result;
}

void check_reference_answers(const SupportRuntime& runtime, const SupportSnapshot& snapshot,
                             const Database& database) {
  const auto expected = reference::evaluate(reference::input::catalog(runtime.plan().catalog()), reference::input::query(runtime.plan().query()), database);
  check(snapshot.has_answer == !expected.empty(),
        "tentative answer presence differs from the full CQ evaluator");
  check(visible_answers(snapshot, *runtime.plan().tree().root) == expected,
        "tentative visible answers differ from the full CQ evaluator");
}

void check_epoch_trace(const SupportEpoch& epoch, std::size_t changed_native_stages) {
  check(epoch.journal != nullptr && epoch.journal->sequence == epoch.sequence,
        "a changed prepared epoch has no matching journal");
  check(epoch.metrics.events_enqueued == epoch.metrics.events_applied &&
        epoch.metrics.events_enqueued == changed_native_stages + epoch.metrics.child_key_events,
        "prepared epoch did not aggregate all native and child events across stages");
  check(epoch.journal->events.size() == epoch.metrics.events_applied,
        "prepared epoch trace omitted an applied event");
  std::vector<const PropagationEvent*> by_application(epoch.journal->events.size(), nullptr);
  std::vector<bool> seen_id(epoch.journal->events.size(), false);
  std::size_t native_count = 0;
  std::size_t child_count = 0;
  for (std::size_t i = 0; i < epoch.journal->events.size(); ++i) {
    const auto& event = epoch.journal->events[i];
    check(event.id == i + 1 && event.sequence == epoch.sequence,
          "event IDs reset between stages or use the wrong tentative sequence");
    check(event.applied_ordinal > 0 && event.applied_ordinal <= by_application.size(),
          "event has an out-of-range application ordinal");
    auto& applied = by_application[static_cast<std::size_t>(event.applied_ordinal - 1)];
    check(applied == nullptr, "an event has a duplicate application ordinal");
    applied = &event;
    seen_id[i] = true;
    if (event.kind == SupportEventKind::native_update) {
      ++native_count;
      check(event.cause == 0, "native event has a child-event cause");
    } else {
      ++child_count;
      check(event.cause > 0 && event.cause < event.id,
            "child event does not name an earlier active event as its cause");
      const auto& source = epoch.journal->events.at(static_cast<std::size_t>(event.cause - 1));
      check(source.id == event.cause && source.applied_ordinal < event.applied_ordinal,
            "child event cause was not active before the child was applied");
    }
  }
  check(std::all_of(seen_id.begin(), seen_id.end(), [](bool value) { return value; }) &&
        std::all_of(by_application.begin(), by_application.end(),
                    [](const PropagationEvent* event) { return event != nullptr; }),
        "prepared epoch event IDs or application ordinals are not contiguous");
  check(native_count == changed_native_stages && child_count == epoch.metrics.child_key_events,
        "prepared epoch trace changed the number of native or child events");
  check(epoch.metrics.journal_records == epoch.journal->records.size(),
        "prepared epoch did not aggregate journal records across stages");
  for (std::size_t i = 0; i < epoch.journal->records.size(); ++i) {
    const auto& record = epoch.journal->records[i];
    check(record.ordinal == i + 1 && record.cause > 0 &&
          record.cause <= epoch.metrics.events_applied,
          "prepared epoch journal ordinals or causes reset between stages");
  }
}

void busy_preview_commit_and_rollback() {
  SupportRuntime runtime(unary_plan(), SupportOptions{.capture_transitions = true});
  const auto first = runtime.apply({1, NodeId{0}, SetOperation::insert, {n(1)}});
  const auto existing = runtime.find(NodeId{0}, SupportRole::records, {n(1)});
  check(first.native_changed && existing.has_value(), "busy-reader fixture did not commit its first row");
  const auto* plan = &runtime.plan();
  const auto* options = &runtime.options();
  const auto owner = runtime.owner();
  const auto before = runtime.snapshot();

  expect_error([&] { static_cast<void>(runtime.begin_epoch(3, SetOperation::insert)); },
               "invalid_sequence");
  expect_error([&] {
    static_cast<void>(runtime.begin_epoch(2, static_cast<SetOperation>(255)));
  }, "invalid_native_update");
  check(runtime.ready() && runtime.sequence() == 1 && same_snapshot(before, runtime.snapshot()),
        "invalid begin_epoch requests changed the last committed state");

  auto pending = runtime.begin_epoch(2, SetOperation::insert);
  check(pending.active() && !runtime.ready() && runtime.sequence() == 1,
        "begin_epoch did not hide readiness while keeping the committed sequence");
  check(&runtime.plan() == plan && &runtime.options() == options && runtime.owner() == owner,
        "read-only runtime identity changed while a prepared epoch was active");
  check_busy_readers(runtime, *existing);

  const auto& empty_preview = pending.preview();
  check(empty_preview.sequence == 2 && !empty_preview.native_changed && empty_preview.journal == nullptr,
        "new epoch preview published work before a real stage");
  const auto duplicate = pending.stage(NodeId{0}, Row{n(1)});
  check(!duplicate && pending.preview().journal == nullptr && !pending.preview().native_changed,
        "a duplicate native insert created event work or a journal");
  check(pending.preview().metrics.work == 0 && pending.preview().metrics.events_enqueued == 0 &&
        pending.preview().metrics.events_applied == 0,
        "a duplicate native insert charged work or enqueued events");
  check(pending.stage(NodeId{0}, Row{n(2)}), "new native row was reported as a no-op");
  const auto& changed_preview = pending.preview();
  check(changed_preview.sequence == 2 && changed_preview.native_changed &&
        changed_preview.journal != nullptr && changed_preview.journal->sequence == 2,
        "first changed stage did not create the tentative epoch journal");
  const auto tentative = pending.snapshot();
  check(tentative.sequence == 2 && tentative.has_answer && tentative.nodes[0].records.size() == 2 &&
        tentative.nodes[0].survivors.size() == 2,
        "owner-only snapshot omitted tentative native and survivor state");
  expect_error([&] { static_cast<void>(runtime.snapshot()); }, "runtime_busy");
  check(!same_snapshot(before, tentative), "owner-only snapshot did not expose tentative state");
  check_busy_readers(runtime, *existing);

  auto committed = pending.commit();
  check(!pending.active() && runtime.ready() && runtime.sequence() == 2 &&
        committed.sequence == 2 && committed.native_changed && committed.has_answer,
        "commit did not publish exactly one prepared sequence");
  check(committed.journal && runtime.snapshot().nodes[0].records.size() == 2 &&
        runtime.get(*existing).has_value(),
        "commit lost prior handles or the newly staged row");
  expect_closed(pending);
  runtime.check_invariants();

  const auto noop = runtime.apply({3, NodeId{0}, SetOperation::insert, {n(1)}});
  check(!noop.native_changed && noop.sequence == 3 && noop.journal == nullptr &&
        runtime.sequence() == 3 && runtime.ready(),
        "legacy apply no-op no longer consumes one sequence without event work");

  const auto before_rollback = runtime.snapshot();
  {
    auto abandoned = runtime.begin_epoch(4, SetOperation::erase);
    check(abandoned.stage(NodeId{0}, Row{n(1)}), "tentative erase was reported as a no-op");
    check(!same_snapshot(before_rollback, abandoned.snapshot()),
          "owner snapshot omitted tentative deletion state");
    abandoned.rollback();
    expect_closed(abandoned);
  }
  check(runtime.ready() && runtime.sequence() == 3 &&
        same_snapshot(before_rollback, runtime.snapshot()),
        "explicit rollback published tentative changes or consumed sequence");
  {
    auto abandoned = runtime.begin_epoch(4, SetOperation::insert);
    check(abandoned.stage(NodeId{0}, Row{n(9)}), "tentative insert was reported as a no-op");
  }
  check(runtime.ready() && runtime.sequence() == 3 &&
        same_snapshot(before_rollback, runtime.snapshot()),
        "prepared epoch destruction did not roll back its staged row");
}

void loop_edge_aliases_accumulate_new_new_cross_terms() {
  const auto plan = loop_alias_plan();
  SupportOptions options;
  options.capture_transitions = true;
  SupportRuntime runtime(plan, options);
  auto pending = runtime.begin_epoch(1, SetOperation::insert);

  // Both occurrences are aliases of the same physical edge relation. Rows
  // are logical tuples in ascending variable order, so the reverse port
  // receives the transposed values from each physical edge.
  check(pending.stage(NodeId{1}, Row{n(1), n(2)}), "forward alias insertion was a no-op");
  check(pending.stage(NodeId{2}, Row{n(2), n(1)}), "reverse alias insertion was a no-op");
  auto owner_view = pending.snapshot();
  check(owner_view.sequence == 1 && !owner_view.has_answer &&
        owner_view.nodes[0].records.size() == 2 && owner_view.nodes[0].survivors.empty(),
        "first physical edge did not leave two incomplete tentative candidates");
  check(owner_view.nodes[0].records[0].satisfied.value == 1 &&
        owner_view.nodes[0].records[1].satisfied.value == 1,
        "each partial loop candidate must have exactly one present alias");

  // The next physical edge contributes the opposite logical tuples. The
  // first of these two stages completes one cross-term before the other is
  // complete, which is safe because the whole epoch is still unpublished.
  check(pending.stage(NodeId{1}, Row{n(2), n(1)}), "second forward edge insertion was a no-op");
  owner_view = pending.snapshot();
  check(owner_view.has_answer && owner_view.nodes[0].survivors.size() == 1 &&
        owner_view.nodes[0].survivors[0].values() == Row{n(2), n(1)},
        "new forward and reverse aliases did not form their cross-term inside one epoch");
  check(pending.stage(NodeId{2}, Row{n(1), n(2)}), "second reverse edge insertion was a no-op");
  check(!pending.stage(NodeId{2}, Row{n(1), n(2)}), "duplicate alias tuple changed the pending set");

  const auto& preview = pending.preview();
  check(preview.native_changed && preview.sequence == 1 && preview.journal != nullptr,
        "multi-stage preview lost its tentative epoch header");
  check_epoch_trace(preview, 4);
  check(preview.metrics.events_enqueued == 8 && preview.metrics.child_key_events == 4,
        "each staged alias row must enqueue one native and one parent-key event");
  owner_view = pending.snapshot();
  const auto& root = owner_view.nodes[0];
  check(owner_view.has_answer && root.records.size() == 2 && root.survivors.size() == 2 &&
        root.parent_keys.size() == 1 && root.parent_keys[0].key.values().empty() &&
        root.parent_keys[0].support.value == 2,
        "same-root projection support must count its two distinct surviving loop tuples");
  check(root.visible_keys && root.visible_keys->size() == 2 &&
        root.visible_keys->at(0).support.value == 1 && root.visible_keys->at(1).support.value == 1,
        "loop root visible keys do not preserve both exact answer tuples");
  for (const auto& record : root.records)
    check(record.satisfied.value == 2 && record.child_present == std::vector<bool>{true, true} &&
          record.survives,
          "committed loop candidate has inconsistent alias presence metadata");
  for (std::size_t child_id = 1; child_id <= 2; ++child_id) {
    const auto& child = owner_view.nodes[child_id];
    check(child.records.size() == 2 && child.survivors.size() == 2 &&
          child.parent_keys.size() == 2 && child.visible_keys && child.visible_keys->size() == 2,
          "loop alias omitted an expected native, survivor, P, or E state");
    for (const auto& key : child.parent_keys)
      check(key.support.value == 1, "loop alias P count is not exact for one local tuple");
    for (const auto& key : *child.visible_keys)
      check(key.support.value == 1, "loop alias E count is not exact for one local tuple");
  }

  Database database;
  database.tables.resize(1);
  database.tables[0].insert(Row{n(1), n(2)});
  database.tables[0].insert(Row{n(2), n(1)});
  auto committed = pending.commit();
  check(committed.native_changed && committed.has_answer && runtime.ready() && runtime.sequence() == 1,
        "loop-edge batch did not commit as one logical epoch");
  check_reference_answers(runtime, runtime.snapshot(), database);
  check_epoch_trace(committed, 4);
  runtime.check_invariants();

  auto absent_erase = runtime.begin_epoch(2, SetOperation::erase);
  check(!absent_erase.stage(NodeId{1}, Row{n(99), n(99)}) &&
        absent_erase.preview().journal == nullptr && !absent_erase.preview().native_changed &&
        absent_erase.preview().metrics.work == 0 &&
        absent_erase.preview().metrics.events_enqueued == 0 &&
        absent_erase.preview().metrics.events_applied == 0,
        "absent erase produced pending event work");
  auto noop = absent_erase.commit();
  check(!noop.native_changed && noop.sequence == 2 && noop.journal == nullptr &&
        runtime.sequence() == 2 && runtime.ready(),
        "no-op prepared epoch did not commit one sequence without a journal");

  auto remove_edge = runtime.begin_epoch(3, SetOperation::erase);
  check(remove_edge.stage(NodeId{1}, Row{n(1), n(2)}) &&
        remove_edge.stage(NodeId{2}, Row{n(2), n(1)}),
        "same-polarity removal of one physical edge was not staged on both aliases");
  owner_view = remove_edge.snapshot();
  check(!owner_view.has_answer && owner_view.nodes[0].survivors.empty(),
        "tentative physical edge removal retained a loop answer");
  database.tables[0].erase(Row{n(1), n(2)});
  const auto removed = remove_edge.commit();
  check(removed.native_changed && removed.sequence == 3 && !removed.has_answer,
        "loop-edge erase epoch published an inconsistent answer flag");
  check_reference_answers(runtime, runtime.snapshot(), database);
  runtime.check_invariants();
}

void same_scope_aliases_and_boolean_nullary_projection_counts() {
  const auto plan = boolean_alias_plan();
  SupportOptions options;
  options.capture_transitions = true;
  SupportRuntime runtime(plan, options);
  auto pending = runtime.begin_epoch(1, SetOperation::insert);
  check(pending.stage(NodeId{2}, Row{n(6)}) && pending.stage(NodeId{1}, Row{n(6)}),
        "first same-scope alias pair was not staged");
  auto owner_view = pending.snapshot();
  check(owner_view.has_answer && owner_view.nodes[0].survivors.size() == 1 &&
        owner_view.nodes[0].visible_keys && owner_view.nodes[0].visible_keys->size() == 1 &&
        owner_view.nodes[0].visible_keys->front().key.values().empty() &&
        owner_view.nodes[0].visible_keys->front().support.value == 1,
        "first existential tuple did not create the Boolean nullary answer");
  check(pending.stage(NodeId{2}, Row{n(5)}) && pending.stage(NodeId{1}, Row{n(5)}),
        "second same-scope alias pair was not staged");

  const auto& preview = pending.preview();
  check_epoch_trace(preview, 4);
  owner_view = pending.snapshot();
  const auto& root = owner_view.nodes[0];
  check(root.survivors.size() == 2 && root.parent_keys.size() == 1 &&
        root.parent_keys.front().key.values().empty() && root.parent_keys.front().support.value == 2,
        "same-scope generalized root lost a distinct existential survivor");
  check(root.visible_keys && root.visible_keys->size() == 1 &&
        root.visible_keys->front().key.values().empty() && root.visible_keys->front().support.value == 2,
        "Boolean visible projection count must reflect both distinct local survivors");
  for (std::size_t child_id = 1; child_id <= 2; ++child_id) {
    const auto& child = owner_view.nodes[child_id];
    check(child.records.size() == 2 && child.survivors.size() == 2 && child.parent_keys.size() == 2,
          "same-scope native alias did not retain both logical input tuples");
    check(!child.visible_keys,
          "non-connex same-scope child unexpectedly exposes a Boolean visible relation");
    for (const auto& key : child.parent_keys)
      check(key.support.value == 1, "same-scope native P count is not exact for one tuple");
  }

  Database database;
  database.tables.resize(1);
  database.tables[0].insert(Row{n(5)});
  database.tables[0].insert(Row{n(6)});
  const auto committed = pending.commit();
  check(committed.native_changed && committed.has_answer && committed.sequence == 1,
        "same-scope Boolean epoch did not commit");
  check_reference_answers(runtime, runtime.snapshot(), database);
  check(runtime.snapshot().nodes[0].visible_keys->front().support.value == 2,
        "published Boolean support count changed at commit");
  runtime.check_invariants();
}

void invalid_stages_abort_whole_epoch_and_allow_retry() {
  SupportRuntime runtime(boolean_alias_plan());
  static_cast<void>(runtime.apply({1, NodeId{1}, SetOperation::insert, {n(5)}}));
  static_cast<void>(runtime.apply({2, NodeId{2}, SetOperation::insert, {n(5)}}));
  const auto before = runtime.snapshot();
  const auto before_stats = runtime.storage_statistics();
  const auto old_handle = runtime.find(NodeId{0}, SupportRole::visible, {});
  check(old_handle.has_value() && before.has_answer, "invalid-stage fixture lacks a live old answer");
  const auto owner = runtime.owner();

  auto wrong_type = runtime.begin_epoch(3, SetOperation::insert);
  check(wrong_type.stage(NodeId{1}, Row{n(6)}), "pre-failure native stage was a no-op");
  expect_error([&] {
    static_cast<void>(wrong_type.stage(NodeId{2}, Row{Value{std::string("wrong type")}}));
  }, "invalid_tuple");
  check(!wrong_type.active() && runtime.ready() && runtime.sequence() == 2 &&
        runtime.owner() == owner && same_snapshot(before, runtime.snapshot()) &&
        runtime.get(*old_handle).has_value() &&
        !runtime.find(NodeId{1}, SupportRole::records, {n(6)}),
        "invalid tuple stage did not roll back all earlier tentative state and handles");
  check_rollback_statistics(before_stats, runtime.storage_statistics(), "invalid tuple stage");
  expect_closed(wrong_type);
  runtime.check_invariants();

  auto retry = runtime.begin_epoch(3, SetOperation::insert);
  check(retry.stage(NodeId{1}, Row{n(6)}) && retry.stage(NodeId{2}, Row{n(6)}),
        "same sequence could not be retried after invalid tuple rollback");
  Database database;
  database.tables.resize(1);
  database.tables[0].insert(Row{n(5)});
  database.tables[0].insert(Row{n(6)});
  const auto retried = retry.commit();
  check(retried.sequence == 3 && retried.native_changed && retried.has_answer,
        "retry did not publish the complete corrected epoch");
  check_reference_answers(runtime, runtime.snapshot(), database);

  const auto after_retry = runtime.snapshot();
  const auto after_retry_stats = runtime.storage_statistics();
  auto invalid_node = runtime.begin_epoch(4, SetOperation::insert);
  check(invalid_node.stage(NodeId{1}, Row{n(7)}), "pre-invalid-node stage was a no-op");
  expect_error([&] { static_cast<void>(invalid_node.stage(NodeId{99}, Row{n(7)})); },
               "invalid_native_update");
  check(!invalid_node.active() && runtime.ready() && runtime.sequence() == 3 &&
        same_snapshot(after_retry, runtime.snapshot()),
        "invalid native node did not abort the complete prepared epoch");
  check_rollback_statistics(after_retry_stats, runtime.storage_statistics(), "invalid native node");
  expect_closed(invalid_node);

  auto generalized = runtime.begin_epoch(4, SetOperation::insert);
  check(generalized.stage(NodeId{1}, Row{n(7)}), "pre-generalized-failure stage was a no-op");
  expect_error([&] { static_cast<void>(generalized.stage(NodeId{0}, Row{n(7)})); },
               "invalid_native_update");
  check(!generalized.active() && runtime.ready() && runtime.sequence() == 3 &&
        same_snapshot(after_retry, runtime.snapshot()) &&
        !runtime.find(NodeId{1}, SupportRole::records, {n(7)}),
        "generalized-node stage did not abort the complete prepared epoch");
  check_rollback_statistics(after_retry_stats, runtime.storage_statistics(), "generalized-node stage");
  expect_closed(generalized);

  auto generalized_retry = runtime.begin_epoch(4, SetOperation::insert);
  check(generalized_retry.stage(NodeId{1}, Row{n(7)}) &&
        generalized_retry.stage(NodeId{2}, Row{n(7)}),
        "same sequence could not be retried after generalized-node rejection");
  database.tables[0].insert(Row{n(7)});
  const auto final = generalized_retry.commit();
  check(final.sequence == 4 && final.native_changed && final.has_answer,
        "generalized-node retry did not commit");
  check_reference_answers(runtime, runtime.snapshot(), database);
  runtime.check_invariants();
}

void work_and_support_failures_abort_partial_epochs() {
  SupportRuntime probe(unary_plan(), SupportOptions{.work_limit = std::nullopt});
  const auto measured = probe.apply({1, NodeId{0}, SetOperation::insert, {n(1)}}).metrics.work;
  check(measured > 0, "work-limit fixture measured no native work");
  SupportOptions exact_work;
  exact_work.work_limit = measured;
  SupportRuntime limited_work(unary_plan(), exact_work);
  const auto empty_before = limited_work.snapshot();
  const auto empty_stats = limited_work.storage_statistics();
  auto work_epoch = limited_work.begin_epoch(1, SetOperation::insert);
  check(work_epoch.stage(NodeId{0}, Row{n(1)}) && work_epoch.preview().metrics.work == measured,
        "first stage did not consume the exact measured work budget");
  expect_error([&] { static_cast<void>(work_epoch.stage(NodeId{0}, Row{n(2)})); }, "resource_limit");
  check(!work_epoch.active() && limited_work.ready() && limited_work.sequence() == 0 &&
        same_snapshot(empty_before, limited_work.snapshot()),
        "work-limit failure left the earlier stage partially published");
  check_rollback_statistics(empty_stats, limited_work.storage_statistics(), "work-limit failure");
  expect_closed(work_epoch);
  auto work_retry = limited_work.begin_epoch(1, SetOperation::insert);
  check(work_retry.stage(NodeId{0}, Row{n(1)}), "work-limited same-sequence retry was a no-op");
  check(work_retry.commit().native_changed && limited_work.sequence() == 1,
        "work-limited epoch did not retry from the original committed sequence");

  SupportOptions exact_support;
  exact_support.support_limit = 1;
  SupportRuntime limited_support(unary_plan(), exact_support);
  const auto support_before = limited_support.snapshot();
  const auto support_stats = limited_support.storage_statistics();
  auto support_epoch = limited_support.begin_epoch(1, SetOperation::insert);
  check(support_epoch.stage(NodeId{0}, Row{n(1)}), "first bounded-support stage was a no-op");
  expect_error([&] { static_cast<void>(support_epoch.stage(NodeId{0}, Row{n(2)})); },
               "support_overflow");
  check(!support_epoch.active() && limited_support.ready() && limited_support.sequence() == 0 &&
        same_snapshot(support_before, limited_support.snapshot()),
        "support-limit failure did not roll back all earlier tentative changes");
  check_rollback_statistics(support_stats, limited_support.storage_statistics(), "support-limit failure");
  expect_closed(support_epoch);
  auto support_retry = limited_support.begin_epoch(1, SetOperation::insert);
  check(support_retry.stage(NodeId{0}, Row{n(2)}),
        "support-limited same-sequence retry was rejected");
  check(support_retry.commit().native_changed && limited_support.sequence() == 1,
        "support-limited retry did not commit after atomic failure");
}

void pending_owns_runtime_impl_across_facade_move_and_destruction() {
  SupportRuntime source(unary_plan());
  auto pending = source.begin_epoch(1, SetOperation::insert);
  SupportRuntime destination(std::move(source));
  check(pending.stage(NodeId{0}, Row{n(8)}), "moved-facade stage was a no-op");
  check(pending.snapshot().sequence == 1, "moved-facade pending snapshot lost its sequence");
  const auto moved_commit = pending.commit();
  check(moved_commit.native_changed && destination.sequence() == 1 && destination.ready() &&
        destination.find(NodeId{0}, SupportRole::records, {n(8)}).has_value(),
        "pending epoch lost its owner when the runtime facade moved");

  std::optional<SupportRuntime::PendingEpoch> detached;
  {
    SupportRuntime temporary(unary_plan());
    detached.emplace(temporary.begin_epoch(1, SetOperation::insert));
  }
  check(detached->active() && detached->stage(NodeId{0}, Row{n(9)}),
        "pending token did not retain runtime state after facade destruction");
  const auto detached_snapshot = detached->snapshot();
  check(detached_snapshot.sequence == 1 && detached_snapshot.has_answer,
        "detached pending token lost its tentative snapshot");
  const auto detached_commit = detached->commit();
  check(detached_commit.native_changed && detached_commit.sequence == 1 && detached_commit.has_answer,
        "detached pending token could not commit its owned implementation");
}

void moved_from_tokens_and_changed_value_journals() {
  SupportRuntime runtime(unary_plan());
  auto source = runtime.begin_epoch(1, SetOperation::insert);
  auto destination = std::move(source);
  check(!source.active() && destination.active(), "move did not transfer pending epoch ownership");
  expect_error([&] { static_cast<void>(source.stage(NodeId{0}, Row{n(1)})); }, "invalid_epoch");
  expect_error([&] { static_cast<void>(source.preview()); }, "invalid_epoch");
  expect_error([&] { static_cast<void>(source.snapshot()); }, "invalid_epoch");
  expect_error([&] { static_cast<void>(source.commit()); }, "invalid_epoch");
  source.rollback();
  check(destination.stage(NodeId{0}, Row{n(42)}), "moved-to pending token stage was a no-op");
  const auto committed = destination.commit();
  check(committed.journal && !destination.active(), "moved-to pending token did not commit a journal");

  constexpr std::int64_t unrelated = 32;
  std::shared_ptr<const SupportJournal> retained;
  {
    SupportRuntime journal_runtime(unary_plan());
    for (std::int64_t i = 0; i < unrelated; ++i)
      static_cast<void>(journal_runtime.apply({journal_runtime.sequence() + 1, NodeId{0},
          SetOperation::insert, {n(i)}}));
    auto one_change = journal_runtime.begin_epoch(journal_runtime.sequence() + 1, SetOperation::insert);
    check(one_change.stage(NodeId{0}, Row{n(1000)}), "journal-retention stage was a no-op");
    const auto result = one_change.commit();
    retained = result.journal;
    check(retained && retained->records.size() < static_cast<std::size_t>(unrelated),
          "prepared journal retained more than its affected values");
    for (const auto& record : retained->records) {
      if (record.handle.role == SupportRole::records || record.handle.role == SupportRole::survivors ||
          record.handle.role == SupportRole::visible)
        check(record.tuple().values() == Row{n(1000)},
              "prepared journal retained an unrelated logical tuple");
    }
    for (std::int64_t i = 0; i < unrelated; ++i)
      static_cast<void>(journal_runtime.apply({journal_runtime.sequence() + 1, NodeId{0},
          SetOperation::erase, {n(i)}}));
    static_cast<void>(journal_runtime.apply({journal_runtime.sequence() + 1, NodeId{0},
        SetOperation::erase, {n(1000)}}));
    const auto statistics = journal_runtime.storage_statistics();
    check(statistics.live_records == 0 &&
          statistics.retained_records < static_cast<std::size_t>(unrelated),
          "prepared journal pin retained the whole runtime after unrelated rows were erased");
  }
  check(retained && retained->sequence == static_cast<std::uint64_t>(unrelated + 1),
        "prepared journal lifetime depended on its runtime facade");
  check(std::any_of(retained->records.begin(), retained->records.end(), [](const JournalRecord& record) {
          return record.handle.role == SupportRole::records && record.tuple().values() == Row{n(1000)};
        }), "prepared journal did not retain its changed native tuple after runtime destruction");
}

}  // namespace

int main() {
  try {
    busy_preview_commit_and_rollback();
    loop_edge_aliases_accumulate_new_new_cross_terms();
    same_scope_aliases_and_boolean_nullary_projection_counts();
    invalid_stages_abort_whole_epoch_and_allow_retry();
    work_and_support_failures_abort_partial_epochs();
    pending_owns_runtime_impl_across_facade_move_and_destruction();
    moved_from_tokens_and_changed_value_journals();
    std::cout << "prepared logical epochs, staged aliases, rollback, and journal ownership passed\n";
  } catch (const std::exception& failure) {
    std::cerr << failure.what() << '\n';
    return 1;
  }
  return 0;
}
