#include "crown/api/error.hpp"
#include "crown/io/document.hpp"
#include "crown/io/support.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/support.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <new>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

// This executable owns the allocation fault injector so every prepared-epoch
// allocation boundary can be swept without affecting other tests.
namespace {
thread_local std::ptrdiff_t fail_after = -1;
[[gnu::noinline]] void* malloc_new(std::size_t bytes) {
  if (fail_after >= 0) {
    if (fail_after == 0) throw std::bad_alloc{};
    --fail_after;
  }
  if (auto* result = std::malloc(bytes == 0 ? 1 : bytes)) return result;
  throw std::bad_alloc{};
}
struct FaultScope {
  explicit FaultScope(std::ptrdiff_t step = -1) { fail_after = step; }
  ~FaultScope() { fail_after = -1; }
  FaultScope(const FaultScope&) = delete;
  FaultScope& operator=(const FaultScope&) = delete;
  void forbid_allocations() noexcept { fail_after = 0; }
};
}  // namespace

void* operator new(std::size_t bytes) { return malloc_new(bytes); }
void* operator new[](std::size_t bytes) { return malloc_new(bytes); }
void operator delete(void* pointer) noexcept { std::free(pointer); }
void operator delete[](void* pointer) noexcept { std::free(pointer); }
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }

namespace {
using namespace crown;
using namespace crown::runtime;

static_assert(std::is_nothrow_move_constructible_v<SupportEpoch>);
static_assert(std::is_nothrow_move_constructible_v<SupportRuntime::PendingEpoch>);
static_assert(std::is_nothrow_move_assignable_v<SupportRuntime::PendingEpoch>);

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

Value n(std::int64_t value) { return value; }
Value s(std::string value) { return value; }

const Row& a_y1() {
  static const Row value{n(10), n(1), s("a-y1")};
  return value;
}
const Row& b_y1() {
  static const Row value{n(10), n(1), s("b-y1")};
  return value;
}
const Row& a_y2_first() {
  static const Row value{n(10), n(2), s("a-y2-first")};
  return value;
}
const Row& a_y2_second() {
  static const Row value{n(10), n(2), s("a-y2-second")};
  return value;
}
const Row& b_y2() {
  static const Row value{n(10), n(2), s("b-y2")};
  return value;
}

PhysicalPlan make_plan() {
  Catalog catalog{2, {
      {"A", {{"x", ScalarType::int64}, {"y", ScalarType::int64}, {"a_witness", ScalarType::string}}},
      {"B", {{"x", ScalarType::int64}, {"y", ScalarType::int64}, {"b_witness", ScalarType::string}}}}};
  Query query{
      {{"x", ScalarType::int64}, {"y", ScalarType::int64},
       {"a_witness", ScalarType::string}, {"b_witness", ScalarType::string}},
      {{"a", TableId{0}, {VariableId{0}, VariableId{1}, VariableId{2}}},
       {"b", TableId{1}, {VariableId{0}, VariableId{1}, VariableId{3}}}},
      {{VariableId{0}, "x"}}, false};
  FreeConnexTree tree{NodeId{0}, {
      {"root", NodeKind::generalized, {VariableId{0}, VariableId{1}},
       {NodeId{1}, NodeId{2}}, {}, {}},
      {"a", NodeKind::native, {VariableId{0}, VariableId{1}, VariableId{2}}, {}, 0, {}},
      {"b", NodeKind::native, {VariableId{0}, VariableId{1}, VariableId{3}}, {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

SupportOptions options() {
  SupportOptions result;
  result.capture_transitions = true;
  return result;
}

enum class Direction { insert, erase };

struct StageInput {
  NodeId node;
  Row values;
};

std::array<StageInput, 3> stages(Direction direction) {
  static_cast<void>(direction);
  const auto& first = a_y2_first();
  const auto& second = b_y2();
  const auto& third = a_y2_second();
  return {{{NodeId{1}, first}, {NodeId{2}, second}, {NodeId{1}, third}}};
}

SetOperation operation(Direction direction) {
  return direction == Direction::insert ? SetOperation::insert : SetOperation::erase;
}

io::Json normalized_owners(io::Json value) {
  const auto normalize = [&](const auto& self, io::Json& item) -> void {
    if (item.is_object()) {
      if (item.contains("owner")) item["owner"] = 0;
      for (auto& member : item.items()) self(self, member.value());
    } else if (item.is_array()) {
      for (auto& member : item) self(self, member);
    }
  };
  normalize(normalize, value);
  return value;
}

io::Json normalized_snapshot(const SupportRuntime& runtime, const PhysicalPlan& plan) {
  check(runtime.ready(), "cannot serialize a support snapshot while an epoch is open");
  return normalized_owners(io::write_support_snapshot(runtime.snapshot(), plan));
}

io::Json normalized_epoch(const SupportEpoch& epoch) {
  return normalized_owners(io::write_support_epoch(epoch));
}

template <class Action>
void expect_error(Action&& action, std::string_view code) {
  try {
    std::forward<Action>(action)();
  } catch (const Error& failure) {
    check(failure.code() == code, "unexpected error code: expected " + std::string(code) +
                                      ", got " + failure.code());
    return;
  }
  throw std::runtime_error("expected error code " + std::string(code));
}

template <class Action>
void expect_any_error(Action&& action, const std::string& message) {
  try {
    std::forward<Action>(action)();
  } catch (const Error&) {
    return;
  }
  throw std::runtime_error(message);
}

struct JournalValue {
  storage::AccountedLayout layout;
  Row values;
  bool operator==(const JournalValue& other) const {
    return layout.same_token(other.layout) && values == other.values;
  }
};

std::vector<JournalValue> retained_values(const std::shared_ptr<const SupportJournal>& journal) {
  check(journal != nullptr, "committed epoch omitted its retained journal");
  std::vector<JournalValue> result;
  result.reserve(journal->records.size());
  for (const auto& record : journal->records) result.push_back({record.tuple().layout(), storage::export_row(record.tuple().values())});
  return result;
}

using JournalImage = std::pair<std::shared_ptr<const SupportJournal>, std::vector<JournalValue>>;
using JournalImages = std::vector<JournalImage>;

void remember_journal(JournalImages& images, const SupportEpoch& epoch) {
  check(epoch.journal != nullptr && !epoch.journal->records.empty(),
        "real setup epoch did not retain affected values");
  images.emplace_back(epoch.journal, retained_values(epoch.journal));
}

void check_journals(const JournalImages& images, const std::string& context) {
  for (const auto& [journal, expected] : images) {
    check(retained_values(journal) == expected,
          context + ": a committed journal lost or changed one of its pinned tuples");
  }
}

JournalImages initialize(SupportRuntime& runtime, Direction target) {
  JournalImages images;
  auto first = runtime.apply({1, NodeId{1}, SetOperation::insert, a_y1()});
  check(first.native_changed && runtime.ready(), "first baseline update did not commit");
  remember_journal(images, first);
  auto second = runtime.apply({2, NodeId{2}, SetOperation::insert, b_y1()});
  check(second.native_changed && runtime.ready(), "second baseline update did not commit");
  remember_journal(images, second);

  if (target == Direction::erase) {
    auto inserted = std::array<StageInput, 3>{
        StageInput{NodeId{1}, a_y2_first()}, StageInput{NodeId{2}, b_y2()},
        StageInput{NodeId{1}, a_y2_second()}};
    auto pending = runtime.begin_epoch(runtime.sequence() + 1, SetOperation::insert);
    for (const auto& item : inserted)
      check(pending.stage(item.node, item.values), "delete fixture insertion stage was a no-op");
    auto epoch = pending.commit();
    check(!pending.active() && runtime.ready(), "delete fixture insertion did not close its token");
    remember_journal(images, epoch);
  }
  runtime.check_invariants();
  return images;
}

SupportEpoch run_batch(SupportRuntime& runtime, Direction direction) {
  auto pending = runtime.begin_epoch(runtime.sequence() + 1, operation(direction));
  for (const auto& item : stages(direction))
    check(pending.stage(item.node, item.values), "prepared epoch stage unexpectedly reported no change");
  auto epoch = pending.commit();
  check(!pending.active() && runtime.ready(), "commit did not close the pending epoch");
  return epoch;
}

struct PublicHandle {
  SupportHandle handle;
  storage::Tuple value;
  bool operator==(const PublicHandle&) const = default;
};

std::vector<PublicHandle> public_handles(const SupportRuntime& runtime) {
  const auto snapshot = runtime.snapshot();
  std::vector<PublicHandle> result;
  const auto add = [&](SupportHandle handle, const storage::Tuple& value) {
    const auto found = runtime.get(handle);
    check(found && found->layout().same_token(value.layout()) && found->values() == value.values(),
          "snapshot exposed a handle that does not resolve to its tuple");
    result.push_back({handle, *found});
  };
  for (const auto& node : snapshot.nodes) {
    for (const auto& record : node.records) add(record.handle, record.tuple);
    for (const auto& tuple : node.survivors) {
      const auto handle = runtime.find(node.node, SupportRole::survivors, crown::storage::export_row(tuple.values()));
      check(handle.has_value(), "snapshot survivor has no public handle");
      add(*handle, tuple);
    }
    for (const auto& key : node.parent_keys) add(key.handle, key.key);
    if (node.visible_keys)
      for (const auto& key : *node.visible_keys) add(key.handle, key.key);
  }
  return result;
}

struct RootCounterHandles {
  SupportHandle parent;
  SupportHandle visible;
};

RootCounterHandles root_counter_handles(const SupportRuntime& runtime) {
  const auto parent = runtime.find(NodeId{0}, SupportRole::parent_support, Row{});
  const auto visible = runtime.find(NodeId{0}, SupportRole::visible, Row{n(10)});
  check(parent && visible, "root P/E keys were absent before the prepared epoch");
  return {*parent, *visible};
}

const ProjectionKeySnapshot* projection_key(const std::vector<ProjectionKeySnapshot>& keys,
                                             const Row& values) {
  const auto found = std::find_if(keys.begin(), keys.end(), [&](const ProjectionKeySnapshot& key) {
    return key.key.values() == values;
  });
  return found == keys.end() ? nullptr : &*found;
}

void check_count(const SupportSnapshot& snapshot, NodeId node, SupportRole role,
                 const Row& values, std::uint64_t expected, const std::string& context) {
  const auto& state = snapshot.nodes.at(node.value);
  const std::vector<ProjectionKeySnapshot>* keys = nullptr;
  if (role == SupportRole::parent_support) keys = &state.parent_keys;
  else if (role == SupportRole::visible && state.visible_keys) keys = &*state.visible_keys;
  check(keys != nullptr, context + ": requested projection is absent");
  const auto* key = projection_key(*keys, values);
  check(key && key->support.value == expected, context + ": projection counter has the wrong value");
}

void check_batch_result(const SupportRuntime& runtime, const SupportEpoch& epoch,
                        Direction direction, RootCounterHandles stable_counters) {
  const auto snapshot = runtime.snapshot();
  const auto root_p = runtime.find(NodeId{0}, SupportRole::parent_support, Row{});
  const auto root_e = runtime.find(NodeId{0}, SupportRole::visible, Row{n(10)});
  check(root_p && root_e && *root_p == stable_counters.parent && *root_e == stable_counters.visible,
        "positive root P/E count change replaced a stable public key handle");

  const std::uint64_t expected_root_count = direction == Direction::insert ? 2 : 1;
  check_count(snapshot, NodeId{0}, SupportRole::parent_support, Row{}, expected_root_count,
              "root parent-support collision");
  check_count(snapshot, NodeId{0}, SupportRole::visible, Row{n(10)}, expected_root_count,
              "root enumeration-support collision");
  if (direction == Direction::insert) {
    check_count(snapshot, NodeId{1}, SupportRole::parent_support, Row{n(10), n(2)}, 2,
                "left alias witness count");
    check(snapshot.nodes.at(0).records.size() == 2 && snapshot.nodes.at(0).survivors.size() == 2,
          "three staged inserts did not create both colliding root tuples");
  } else {
    check(snapshot.nodes.at(0).records.size() == 1 && snapshot.nodes.at(0).survivors.size() == 1,
          "three staged deletions did not return the root to its original tuple");
  }

  check(epoch.sequence == runtime.sequence() && epoch.native_changed && epoch.has_answer,
        "committed prepared epoch reported the wrong sequence or answer state");
  check(epoch.journal != nullptr && epoch.journal->sequence == epoch.sequence,
        "committed prepared epoch omitted its retained journal");
  check(epoch.metrics.events_enqueued == epoch.metrics.events_applied,
        "prepared epoch did not apply every queued propagation event");

  const auto& events = epoch.journal->events;
  std::vector<std::uint64_t> native_ids;
  std::vector<std::uint64_t> ordinals;
  std::set<std::uint64_t> ids;
  std::size_t child_events = 0;
  for (const auto& event : events) {
    check(ids.insert(event.id).second, "prepared epoch reused a native or child event ID");
    check(event.applied_ordinal > 0, "prepared epoch event omitted its applied ordinal");
    ordinals.push_back(event.applied_ordinal);
    if (event.kind == SupportEventKind::native_update) {
      native_ids.push_back(event.id);
      check(event.cause == 0, "native input event has a nonzero cause");
    } else {
      ++child_events;
      check(event.cause > 0, "child-key event has no causal native or parent event");
    }
  }
  std::sort(ordinals.begin(), ordinals.end());
  check(native_ids.size() == 3 && native_ids[0] == 1 && native_ids[1] > 1 && native_ids[2] > native_ids[1],
        "batch native event IDs did not advance across the three stages");
  check(child_events > 0 && ordinals.size() == events.size(),
        "prepared epoch omitted child propagation events or applied ordinals");
  for (std::size_t i = 0; i < ordinals.size(); ++i)
    check(ordinals[i] == i + 1, "prepared epoch applied ordinals are not a one-based permutation");
}

struct ExpectedResult {
  io::Json snapshot;
  io::Json epoch;
};

ExpectedResult clean_result(const PhysicalPlan& plan, Direction direction) {
  SupportRuntime runtime{plan, options()};
  auto pins = initialize(runtime, direction);
  static_cast<void>(pins);
  const auto stable_counters = root_counter_handles(runtime);
  auto epoch = run_batch(runtime, direction);
  check_batch_result(runtime, epoch, direction, stable_counters);
  runtime.check_invariants();
  return {normalized_snapshot(runtime, plan), normalized_epoch(epoch)};
}

void check_rollback_statistics(const storage::ArenaStatistics& before,
                               const storage::ArenaStatistics& after,
                               const std::string& context) {
  check(before.live_records == after.live_records &&
            before.retained_records == after.retained_records && before.pins == after.pins,
        context + ": failed epoch changed live/retained tuple counts or pins");
  check(after.slots >= before.slots,
        context + ": rollback unexpectedly reduced the aggregate arena high-water slot count");
  // Free slots and generations may grow as tentative slots are retired.
}

enum class Phase : std::size_t { begin = 0, first_stage = 1, second_stage = 2, third_stage = 3, commit = 4 };

struct SweepCounts {
  std::size_t failures = 0;
  std::array<std::size_t, 5> failed_phase{};
};

SweepCounts sweep(const PhysicalPlan& plan, Direction direction) {
  constexpr std::ptrdiff_t max_points = 8192;
  const auto expected = clean_result(plan, direction);
  const auto staged = stages(direction);
  const auto set_operation = operation(direction);
  SweepCounts counts;

  for (std::ptrdiff_t step = 0; step < max_points; ++step) {
    SupportRuntime runtime{plan, options()};
    const auto pins = initialize(runtime, direction);
    const auto before = normalized_snapshot(runtime, plan);
    const auto sequence = runtime.sequence();
    const auto answer = runtime.has_answer();
    const auto owner = runtime.owner();
    const auto before_handles = public_handles(runtime);
    const auto counters = root_counter_handles(runtime);
    const auto storage_before = runtime.storage_statistics();

    bool failed = false;
    bool token_existed_on_failure = false;
    bool stage_failure_closed_token = false;
    Phase phase = Phase::begin;
    std::array<bool, 3> stage_results{};
    std::optional<SupportRuntime::PendingEpoch> pending;
    std::optional<SupportEpoch> result;
    {
      FaultScope fault(step);
      try {
        pending.emplace(runtime.begin_epoch(sequence + 1, set_operation));
        phase = Phase::first_stage;
        stage_results[0] = pending->stage(staged[0].node, staged[0].values);
        phase = Phase::second_stage;
        stage_results[1] = pending->stage(staged[1].node, staged[1].values);
        phase = Phase::third_stage;
        stage_results[2] = pending->stage(staged[2].node, staged[2].values);
        phase = Phase::commit;
        result.emplace(pending->commit());
        pending.reset();
      } catch (const std::bad_alloc&) {
        failed = true;
        fail_after = 0;  // Keep allocation failure armed through token cleanup.
        token_existed_on_failure = pending.has_value();
        if (phase == Phase::first_stage || phase == Phase::second_stage || phase == Phase::third_stage)
          stage_failure_closed_token = pending && !pending->active();
        pending.reset();
      }
    }

    if (failed) {
      ++counts.failures;
      ++counts.failed_phase.at(static_cast<std::size_t>(phase));
      check((phase == Phase::begin) == !token_existed_on_failure,
            "begin allocation failure did not leave the runtime without an epoch token");
      if (phase == Phase::first_stage || phase == Phase::second_stage || phase == Phase::third_stage)
        check(stage_failure_closed_token,
              "bad_alloc during a stage did not automatically abort and close the whole epoch");
      check(runtime.ready(), "allocation failure left the runtime busy");
      check(runtime.sequence() == sequence && runtime.has_answer() == answer && runtime.owner() == owner,
            "failed prepared epoch changed the committed sequence, answer or owner");
      check(normalized_snapshot(runtime, plan) == before,
            "failed prepared epoch changed snapshot values or public tuple IDs");
      check(public_handles(runtime) == before_handles,
            "failed prepared epoch changed or invalidated a public support handle");
      const auto after_counters = root_counter_handles(runtime);
      check(after_counters.parent == counters.parent && after_counters.visible == counters.visible,
            "failed prepared epoch changed an existing root P/E handle");
      check_rollback_statistics(storage_before, runtime.storage_statistics(), "prepared epoch fault sweep");
      check_journals(pins, "prepared epoch fault sweep");
      runtime.check_invariants();

      // Reuse the exact sequence and all three stages after every injected
      // failure; exact JSON comparison covers IDs, causes, ordinals and work.
      const auto retry_counters = root_counter_handles(runtime);
      auto retry = run_batch(runtime, direction);
      check(normalized_epoch(retry) == expected.epoch &&
                normalized_snapshot(runtime, plan) == expected.snapshot,
            "same-sequence prepared epoch retry differed from a clean committed run");
      check_batch_result(runtime, retry, direction, retry_counters);
      check_journals(pins, "prepared epoch retry");
      runtime.check_invariants();
      continue;
    }

    check(counts.failures > 0,
          "prepared epoch fault sweep reached success without injecting an allocation failure");
    check(stage_results == std::array<bool, 3>{true, true, true},
          "a successful prepared epoch stage reported no change");
    check(result && normalized_epoch(*result) == expected.epoch &&
              normalized_snapshot(runtime, plan) == expected.snapshot,
          "first non-failing prepared epoch differed from a clean committed run");
    check_batch_result(runtime, *result, direction, counters);
    check_journals(pins, "successful prepared epoch");
    runtime.check_invariants();
    return counts;
  }
  throw std::runtime_error("prepared epoch allocation sweep exceeded 8192 fault points");
}

void check_busy_readers(const PhysicalPlan& plan) {
  SupportRuntime runtime{plan, options()};
  auto pins = initialize(runtime, Direction::insert);
  static_cast<void>(pins);
  const auto before = normalized_snapshot(runtime, plan);
  const auto committed_sequence = runtime.sequence();
  const auto old_handle = runtime.find(NodeId{1}, SupportRole::records, a_y1());
  check(old_handle.has_value(), "busy-reader fixture has no existing native handle");

  auto pending = runtime.begin_epoch(committed_sequence + 1, SetOperation::insert);
  check(!runtime.ready() && runtime.sequence() == committed_sequence,
        "opening a token published its sequence or reported the runtime ready");
  check(pending.stage(NodeId{1}, a_y2_first()), "busy-reader fixture stage was a no-op");
  check(!runtime.ready() && runtime.sequence() == committed_sequence,
        "staging published the tentative sequence or reported the runtime ready");
  check(pending.preview().sequence == committed_sequence + 1,
        "token preview omitted its tentative epoch sequence");
  const auto private_snapshot = pending.snapshot();
  check(private_snapshot.sequence == committed_sequence + 1,
        "token snapshot omitted its tentative epoch sequence");

  expect_error([&] { static_cast<void>(runtime.has_answer()); }, "runtime_busy");
  expect_error([&] { static_cast<void>(runtime.snapshot()); }, "runtime_busy");
  expect_error([&] { static_cast<void>(runtime.find(NodeId{1}, SupportRole::records, a_y1())); }, "runtime_busy");
  expect_error([&] { static_cast<void>(runtime.get(*old_handle)); }, "runtime_busy");
  expect_error([&] { static_cast<void>(runtime.storage_statistics()); }, "runtime_busy");
  expect_error([&] { runtime.check_invariants(); }, "runtime_busy");

  pending.rollback();
  check(!pending.active() && runtime.ready() && runtime.sequence() == committed_sequence,
        "explicit rollback did not close the token without publishing its sequence");
  check(normalized_snapshot(runtime, plan) == before,
        "explicit pending-epoch cancellation changed the committed snapshot");
  expect_error([&] { static_cast<void>(pending.commit()); }, "invalid_epoch");
  runtime.check_invariants();
}

void check_invalid_stage_aborts(const PhysicalPlan& plan) {
  SupportRuntime runtime{plan, options()};
  const auto pins = initialize(runtime, Direction::insert);
  const auto before = normalized_snapshot(runtime, plan);
  const auto handles = public_handles(runtime);
  const auto stats = runtime.storage_statistics();
  const auto sequence = runtime.sequence();
  auto pending = runtime.begin_epoch(sequence + 1, SetOperation::insert);
  check(pending.stage(NodeId{1}, a_y2_first()), "valid prefix stage was a no-op");
  expect_any_error([&] { static_cast<void>(pending.stage(NodeId{plan.nodes().size()}, a_y2_second())); },
                   "invalid node stage unexpectedly succeeded");
  check(!pending.active() && runtime.ready() && runtime.sequence() == sequence,
        "invalid stage did not roll back and close the entire epoch");
  check(normalized_snapshot(runtime, plan) == before && public_handles(runtime) == handles,
        "invalid stage partially published its successful prefix");
  check_rollback_statistics(stats, runtime.storage_statistics(), "invalid stage");
  check_journals(pins, "invalid stage");
  expect_error([&] { static_cast<void>(pending.commit()); }, "invalid_epoch");
  runtime.check_invariants();
}

void check_destructor_cancellation_is_noalloc(const PhysicalPlan& plan) {
  SupportRuntime runtime{plan, options()};
  const auto pins = initialize(runtime, Direction::insert);
  const auto before = normalized_snapshot(runtime, plan);
  const auto sequence = runtime.sequence();
  {
    FaultScope no_allocations;
    {
      auto pending = runtime.begin_epoch(sequence + 1, SetOperation::insert);
      // Constructing the token and staging may allocate; arm failure only
      // after earlier stage work succeeded, before its destructor runs.
      check(pending.stage(NodeId{1}, a_y2_first()), "destructor-cancellation stage was a no-op");
      no_allocations.forbid_allocations();
    }
  }
  check(runtime.ready() && runtime.sequence() == sequence,
        "token destructor did not cancel its staged epoch");
  check(normalized_snapshot(runtime, plan) == before,
        "no-allocation token destructor changed committed state");
  check_journals(pins, "token destructor cancellation");
  runtime.check_invariants();
}

void check_move_assignment_is_noalloc(const PhysicalPlan& plan) {
  SupportRuntime destination_runtime{plan, options()};
  SupportRuntime source_runtime{plan, options()};
  const auto destination_pins = initialize(destination_runtime, Direction::insert);
  const auto source_pins = initialize(source_runtime, Direction::insert);
  const auto destination_before = normalized_snapshot(destination_runtime, plan);
  const auto source_before = normalized_snapshot(source_runtime, plan);
  const auto destination_sequence = destination_runtime.sequence();
  const auto source_sequence = source_runtime.sequence();

  auto destination = destination_runtime.begin_epoch(destination_sequence + 1, SetOperation::insert);
  auto source = source_runtime.begin_epoch(source_sequence + 1, SetOperation::insert);
  check(destination.stage(NodeId{1}, a_y2_first()) && source.stage(NodeId{1}, a_y2_first()),
        "move-assignment fixture stage was a no-op");
  bool source_closed = false;
  {
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    destination = std::move(source);
    source_closed = !source.active();
    destination.rollback();
  }
  check(source_closed && !destination.active() && destination_runtime.ready() && source_runtime.ready(),
        "move assignment failed to cancel its destination and transferred tokens");
  check(destination_runtime.sequence() == destination_sequence &&
            source_runtime.sequence() == source_sequence,
        "move assignment published a tentative sequence");
  check(normalized_snapshot(destination_runtime, plan) == destination_before &&
            normalized_snapshot(source_runtime, plan) == source_before,
        "no-allocation token move assignment changed a committed snapshot");
  check_journals(destination_pins, "move-assignment destination");
  check_journals(source_pins, "move-assignment source");
  expect_error([&] { static_cast<void>(destination.commit()); }, "invalid_epoch");
  destination_runtime.check_invariants();
  source_runtime.check_invariants();
}

void check_active_token_survives_runtime_move(const PhysicalPlan& plan) {
  SupportRuntime runtime{plan, options()};
  const auto pins = initialize(runtime, Direction::insert);
  const auto before = normalized_snapshot(runtime, plan);
  const auto sequence = runtime.sequence();
  auto pending = runtime.begin_epoch(sequence + 1, SetOperation::insert);
  check(pending.stage(NodeId{1}, a_y2_first()), "runtime-move fixture stage was a no-op");

  SupportRuntime moved{std::move(runtime)};
  check(pending.active() && !moved.ready() && moved.sequence() == sequence,
        "moving the facade detached its active pending epoch from the runtime implementation");
  pending.rollback();
  check(!pending.active() && moved.ready() && moved.sequence() == sequence,
        "token rollback after facade move did not restore readiness");
  check(normalized_snapshot(moved, plan) == before,
        "token rollback after facade move changed committed state");
  check_journals(pins, "runtime move with active token");
  moved.check_invariants();
}

void check_token_retains_runtime_after_facade_destruction(const PhysicalPlan& plan) {
  std::optional<SupportRuntime::PendingEpoch> pending;
  {
    SupportRuntime runtime{plan, options()};
    const auto pins = initialize(runtime, Direction::insert);
    static_cast<void>(pins);
    pending.emplace(runtime.begin_epoch(runtime.sequence() + 1, SetOperation::insert));
    check(pending->stage(NodeId{1}, a_y2_first()), "destroyed-facade fixture stage was a no-op");
  }
  {
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    pending->rollback();
  }
  check(!pending->active(), "token could not roll back after its runtime facade was destroyed");
  expect_error([&] { static_cast<void>(pending->commit()); }, "invalid_epoch");
}

void check_commit_is_noalloc_and_returns_by_move(const PhysicalPlan& plan) {
  SupportRuntime runtime{plan, options()};
  auto pins = initialize(runtime, Direction::insert);
  const auto stable_counters = root_counter_handles(runtime);
  const auto sequence = runtime.sequence();
  auto pending = runtime.begin_epoch(sequence + 1, SetOperation::insert);
  for (const auto& item : stages(Direction::insert))
    check(pending.stage(item.node, item.values), "no-allocation commit fixture stage was a no-op");

  std::optional<SupportEpoch> output;
  {
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    output.emplace(pending.commit());
  }
  check(output.has_value() && !pending.active() && runtime.ready(),
        "no-allocation commit failed to return and close its epoch");
  check(runtime.sequence() == sequence + 1,
        "no-allocation commit did not publish exactly one sequence");
  check_batch_result(runtime, *output, Direction::insert, stable_counters);
  check_journals(pins, "no-allocation commit");
  expect_error([&] { static_cast<void>(pending.commit()); }, "invalid_epoch");
  runtime.check_invariants();
}

}  // namespace

int main() {
  try {
    const auto plan = make_plan();
    check_busy_readers(plan);
    check_invalid_stage_aborts(plan);
    check_destructor_cancellation_is_noalloc(plan);
    check_move_assignment_is_noalloc(plan);
    check_active_token_survives_runtime_move(plan);
    check_token_retains_runtime_after_facade_destruction(plan);
    check_commit_is_noalloc_and_returns_by_move(plan);

    const auto insertion = sweep(plan, Direction::insert);
    const auto deletion = sweep(plan, Direction::erase);
    check(insertion.failed_phase[static_cast<std::size_t>(Phase::begin)] > 0 &&
              insertion.failed_phase[static_cast<std::size_t>(Phase::first_stage)] > 0 &&
              insertion.failed_phase[static_cast<std::size_t>(Phase::second_stage)] > 0 &&
              insertion.failed_phase[static_cast<std::size_t>(Phase::third_stage)] > 0,
          "insertion fault sweep missed begin or one of its three stage allocation paths");
    check(deletion.failed_phase[static_cast<std::size_t>(Phase::begin)] > 0 &&
              deletion.failed_phase[static_cast<std::size_t>(Phase::first_stage)] > 0 &&
              deletion.failed_phase[static_cast<std::size_t>(Phase::second_stage)] > 0 &&
              deletion.failed_phase[static_cast<std::size_t>(Phase::third_stage)] > 0,
          "deletion fault sweep missed begin or one of its three stage allocation paths");
    check(insertion.failed_phase[static_cast<std::size_t>(Phase::commit)] == 0 &&
              deletion.failed_phase[static_cast<std::size_t>(Phase::commit)] == 0,
          "prepared epoch commit allocated under the exhaustive fault sweep");
    std::cout << "prepared epoch allocation rollback points: insert=" << insertion.failures
              << " erase=" << deletion.failures << '\n';
  } catch (const std::exception& failure) {
    fail_after = -1;
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
