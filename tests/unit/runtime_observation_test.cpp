#include "crown/api/error.hpp"
#include "crown/io/ingest.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/delta.hpp"
#include "crown/runtime/observation.hpp"
#include "crown/runtime/physical.hpp"
#include "crown/runtime/session.hpp"
#include "crown/runtime/support.hpp"
#include "evaluator.hpp"

#include <algorithm>
#include <array>
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <new>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace allocation_probe {
std::atomic<bool> active{false};
std::atomic<std::size_t> count{0};

void note() noexcept {
  if (active.load(std::memory_order_relaxed))
    count.fetch_add(1, std::memory_order_relaxed);
}

void* allocate(std::size_t bytes) {
  note();
  if (void* result = std::malloc(bytes == 0 ? 1 : bytes)) return result;
  throw std::bad_alloc{};
}

void* allocate_aligned(std::size_t bytes, std::size_t alignment) {
  note();
  void* result = nullptr;
  if (posix_memalign(&result, alignment, bytes == 0 ? alignment : bytes) == 0)
    return result;
  throw std::bad_alloc{};
}

template <class Action>
std::size_t count_during(Action&& action) {
  count.store(0, std::memory_order_relaxed);
  active.store(true, std::memory_order_relaxed);
  try {
    std::forward<Action>(action)();
  } catch (...) {
    active.store(false, std::memory_order_relaxed);
    throw;
  }
  active.store(false, std::memory_order_relaxed);
  return count.load(std::memory_order_relaxed);
}
}  // namespace allocation_probe

void* operator new(std::size_t bytes) { return allocation_probe::allocate(bytes); }
void* operator new[](std::size_t bytes) { return allocation_probe::allocate(bytes); }
void* operator new(std::size_t bytes, std::align_val_t alignment) {
  return allocation_probe::allocate_aligned(bytes, static_cast<std::size_t>(alignment));
}
void* operator new[](std::size_t bytes, std::align_val_t alignment) {
  return allocation_probe::allocate_aligned(bytes, static_cast<std::size_t>(alignment));
}
void operator delete(void* pointer) noexcept { std::free(pointer); }
void operator delete[](void* pointer) noexcept { std::free(pointer); }
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
void operator delete(void* pointer, std::align_val_t) noexcept { std::free(pointer); }
void operator delete[](void* pointer, std::align_val_t) noexcept { std::free(pointer); }
void operator delete(void* pointer, std::size_t, std::align_val_t) noexcept {
  std::free(pointer);
}
void operator delete[](void* pointer, std::size_t, std::align_val_t) noexcept {
  std::free(pointer);
}

namespace {
using namespace crown;
using namespace crown::runtime;

static_assert(std::is_trivially_copyable_v<TraceRecord>);
static_assert(std::is_standard_layout_v<TraceRecord>);
static_assert(std::is_same_v<decltype(TraceRecord::event), std::uint64_t>);
static_assert(std::is_same_v<decltype(TraceRecord::cause), std::uint64_t>);
static_assert(std::is_same_v<decltype(TraceRecord::tuple), std::uint64_t>);

void check(bool condition, std::string_view message) {
  if (!condition) throw std::runtime_error(std::string(message));
}

template <class Action>
void expect_resource_limit(Action&& action, std::string_view label) {
  bool caught = false;
  try {
    std::forward<Action>(action)();
  } catch (const Error& error) {
    caught = error.code() == "resource_limit";
  }
  check(caught, label);
}

Value integer(std::int64_t value) { return Value{value}; }
Value string(std::string value) { return Value{std::move(value)}; }
Row row(std::int64_t value) { return Row{integer(value)}; }
Row edge(std::int64_t x, std::int64_t y) { return Row{integer(x), integer(y)}; }

struct QFixture {
  Catalog catalog{1, {
      {"R", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}},
      {"S", {{"y", ScalarType::int64}}},
  }};
  Query query{
      {{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"R", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"S", TableId{1}, {VariableId{1}}}},
      {{VariableId{0}, "x"}},
      false,
  };
  PhysicalPlan plan;
  Database initial;

  QFixture()
      : plan(planner::lower_tree(catalog, query, FreeConnexTree{
            NodeId{0},
            {{"R", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{1}}, 0, {}},
             {"S", NodeKind::native, {VariableId{1}}, {}, 1, {}}},
            {},
            {},
        })) {
    initial.tables.resize(2);
    initial.tables[0].insert(edge(7, 9));
  }
};

Catalog constrained_q_catalog() {
  Catalog catalog{1, {
      {"R", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}},
      {"S", {{"y", ScalarType::int64}}},
  }};
  catalog.tables[1].constraints = {
      UniqueConstraint{"S_y_unique", {ColumnId{0}}, ConstraintStatus::enforced},
  };
  return catalog;
}

struct ConstraintQFixture {
  static constexpr std::int64_t irrelevant_begin = 100;
  static constexpr std::int64_t irrelevant_end = 200;
  Catalog catalog{constrained_q_catalog()};
  Query query{
      {{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"R", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"S", TableId{1}, {VariableId{1}}}},
      {{VariableId{0}, "x"}},
      false,
  };
  PhysicalPlan plan{planner::lower_tree(catalog, query, FreeConnexTree{
      NodeId{0},
      {{"R", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{1}}, 0, {}},
       {"S", NodeKind::native, {VariableId{1}}, {}, 1, {}}},
      {},
      {},
  })};
  Database initial;

  ConstraintQFixture() {
    initial.tables.resize(2);
    initial.tables[0].insert(edge(7, 9));
    for (auto value = irrelevant_begin; value < irrelevant_end; ++value)
      initial.tables[1].insert(row(value));
  }
};

struct AliasFixture {
  Catalog catalog{1, {
      {"edge", {{"src", ScalarType::int64}, {"dst", ScalarType::int64},
                 {"payload", ScalarType::string}}},
  }};
  Query query{
      {{"x", ScalarType::int64}, {"y", ScalarType::int64},
       {"z", ScalarType::int64}},
      {{"forward", TableId{0}, {VariableId{0}, VariableId{1}, IgnoredColumn{}}},
       {"reverse", TableId{0}, {VariableId{1}, VariableId{2}, IgnoredColumn{}}}},
      {{VariableId{1}, "y"}},
      false,
  };
  PhysicalPlan plan;

  AliasFixture()
      : plan(planner::lower_tree(catalog, query, FreeConnexTree{
            NodeId{0},
            {{"projected_join", NodeKind::generalized, {VariableId{1}},
              {NodeId{1}, NodeId{2}}, {}, {}},
             {"forward", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}},
             {"reverse", NodeKind::native, {VariableId{1}, VariableId{2}}, {}, 1, {}}},
            {},
            {},
        })) {}
};

ObservationOptions observation_options(ObservationMode mode,
                                      std::size_t trace_capacity = 256,
                                      std::uint64_t sample_period = 1,
                                      std::uint64_t sample_offset = 0,
                                      bool trace_timings = true) {
  ObservationOptions result;
  result.mode = mode;
  result.trace_capacity = trace_capacity;
  result.sample_period = sample_period;
  result.sample_offset = sample_offset;
  result.trace_timings = trace_timings;
  return result;
}

constexpr std::array<ObservationMode, 4> modes{
    ObservationMode::off, ObservationMode::counters,
    ObservationMode::timed, ObservationMode::trace};

Relation drain(SupportRuntime::ResultCursor cursor) {
  Relation result;
  while (auto tuple = cursor.next())
    check(result.insert(crown::storage::export_row(tuple->values())).second, "support cursor emitted duplicate set row");
  return result;
}

Relation drain_physical(SupportRuntime::ResultCursor cursor) {
  return drain(std::move(cursor));
}

Relation expected_q(const QFixture& fixture) {
  auto after = fixture.initial;
  after.tables[1].insert(row(9));
  return reference::evaluate(fixture.catalog, fixture.query, after);
}

void check_q_metrics(const SupportMetrics& m) {
  check(m.work == 40, "Q support work must equal the literal 40 boundary");
  check(m.copied_rows == 0 && m.copied_index_memberships == 0 &&
        m.copied_metadata_entries == 0 && m.copied_child_flags == 0,
        "Q historical whole-state copy counters differ");
  check(m.native_record_visits == 2 && m.child_key_probes == 0 &&
        m.child_key_events == 1, "Q native visit / child-key counters differ");
  check(m.survivor_transitions == 2 && m.parent_key_transitions == 2 &&
        m.visible_key_transitions == 1, "Q logical transition counters differ");
  check(m.candidates_created == 0 && m.candidates_reclaimed == 0,
        "Q native fixture created a generalized candidate");
  check(m.storage_changes == 6 && m.metadata_changes == 5 &&
        m.saved_child_flags == 1 && m.journal_records == 7,
        "Q storage, metadata, flag, or journal counters differ");
  check(m.events_enqueued == 2 && m.events_applied == 2 && m.queue_peak == 1,
        "Q event and queue counters differ");
}

void check_q_physical_metrics(const PhysicalMetrics& m) {
  check(m.work == 44, "Q physical work must equal the literal 44 boundary");
  check(m.source_changes == 1 && m.aliases_visited == 1 && m.aliases_filtered == 0 &&
        m.derivation_changes == 1 && m.native_crossings == 1,
        "Q physical source/alias/derivation/crossing counters differ");
  check(m.constraint_rows == 0 && m.constraint_validations == 0,
        "Q unconstrained fixture charged constraint work");
}

bool same_support_metrics(const SupportMetrics& left, const SupportMetrics& right) {
  return std::tie(left.work, left.copied_rows, left.copied_index_memberships,
                  left.copied_metadata_entries, left.copied_child_flags,
                  left.native_record_visits, left.child_key_probes,
                  left.child_key_events, left.survivor_transitions,
                  left.parent_key_transitions, left.visible_key_transitions,
                  left.candidates_created, left.candidates_reclaimed,
                  left.storage_changes, left.metadata_changes, left.saved_child_flags,
                  left.journal_records, left.events_enqueued, left.events_applied,
                  left.queue_peak) ==
      std::tie(right.work, right.copied_rows, right.copied_index_memberships,
               right.copied_metadata_entries, right.copied_child_flags,
               right.native_record_visits, right.child_key_probes,
               right.child_key_events, right.survivor_transitions,
               right.parent_key_transitions, right.visible_key_transitions,
               right.candidates_created, right.candidates_reclaimed,
               right.storage_changes, right.metadata_changes, right.saved_child_flags,
               right.journal_records, right.events_enqueued, right.events_applied,
               right.queue_peak);
}

std::string describe_support_metrics(const SupportMetrics& m) {
  std::ostringstream out;
  out << " support_metrics{work=" << m.work
      << ", copied_rows=" << m.copied_rows
      << ", copied_index_memberships=" << m.copied_index_memberships
      << ", copied_metadata_entries=" << m.copied_metadata_entries
      << ", copied_child_flags=" << m.copied_child_flags
      << ", native_record_visits=" << m.native_record_visits
      << ", child_key_probes=" << m.child_key_probes
      << ", child_key_events=" << m.child_key_events
      << ", survivor_transitions=" << m.survivor_transitions
      << ", parent_key_transitions=" << m.parent_key_transitions
      << ", visible_key_transitions=" << m.visible_key_transitions
      << ", candidates_created=" << m.candidates_created
      << ", candidates_reclaimed=" << m.candidates_reclaimed
      << ", storage_changes=" << m.storage_changes
      << ", metadata_changes=" << m.metadata_changes
      << ", saved_child_flags=" << m.saved_child_flags
      << ", journal_records=" << m.journal_records
      << ", events_enqueued=" << m.events_enqueued
      << ", events_applied=" << m.events_applied
      << ", queue_peak=" << m.queue_peak << '}';
  return out.str();
}

bool same_physical_metrics(const PhysicalMetrics& left, const PhysicalMetrics& right) {
  return std::tie(left.work, left.source_changes, left.aliases_visited,
                  left.aliases_filtered, left.derivation_changes, left.native_crossings,
                  left.constraint_rows, left.constraint_validations) ==
      std::tie(right.work, right.source_changes, right.aliases_visited,
               right.aliases_filtered, right.derivation_changes, right.native_crossings,
               right.constraint_rows, right.constraint_validations);
}

const MetricDescriptor& descriptor(MetricId id) {
  const auto registry = observation_registry();
  for (const auto& item : registry)
    if (item.id == id) return item;
  throw std::runtime_error("registry omitted a declared metric ID");
}

void check_registry() {
  const auto registry = observation_registry();
  check(registry.size() == observation_metric_count,
        "metric registry size differs from its declared enum");
  for (std::size_t index = 0; index < registry.size(); ++index)
    check(static_cast<std::size_t>(registry[index].id) == index,
          "metric registry order/ID mapping is not total");
  const auto& support_work = descriptor(MetricId::support_work);
  const auto& inclusive = descriptor(MetricId::physical_work_inclusive);
  const auto& exclusive = descriptor(MetricId::physical_work_exclusive);
  check(support_work.accounting == "mandatory-runtime-v1" &&
        support_work.layer == ObservationLayer::support &&
        support_work.scope ==
            "admitted_attempt; aborted values are attempted work, not committed changes",
        "support work registry metadata differs");
  check(inclusive.accounting == "mandatory-runtime-v1" &&
        inclusive.includes ==
            "successfully charged support.work; incomplete nested charge is unavailable" &&
        exclusive.accounting == "optional-observation-v1" &&
        exclusive.includes == "support.work excluded",
        "inclusive/exclusive physical work registry metadata differs");
}

std::string_view availability_name(MetricAvailability availability) {
  switch (availability) {
    case MetricAvailability::unavailable: return "unavailable";
    case MetricAvailability::disabled: return "disabled";
    case MetricAvailability::available: return "available";
  }
  return "unknown";
}

void check_metric(const ObservationSummary& summary, MetricId id,
                  MetricAvailability availability, std::uint64_t value,
                  std::string_view label) {
  const auto& metric = summary.metric(id);
  const bool value_matches = availability != MetricAvailability::available ||
      metric.value == value;
  if (metric.availability == availability && value_matches) return;
  const auto& info = descriptor(id);
  const auto expected_value = availability == MetricAvailability::available
      ? std::to_string(value)
      : std::string("not asserted for nonavailable metrics");
  throw std::runtime_error(
      std::string(label) + ": metric " + std::string(info.name) +
      " expected availability=" + std::string(availability_name(availability)) +
      " value=" + expected_value + "; actual availability=" +
      std::string(availability_name(metric.availability)) +
      " value=" + std::to_string(metric.value));
}

void check_q_state(const SupportSnapshot& state, std::uint64_t sequence,
                   bool answer) {
  check(state.sequence == sequence && state.has_answer == answer,
        "Q support sequence or Boolean answer differs");
  check(state.nodes.size() == 2, "Q support state has the wrong node count");
  const auto& root = state.nodes[0];
  const auto& child = state.nodes[1];
  check(root.node == NodeId{0} && root.kind == NodeKind::native &&
        child.node == NodeId{1} && child.kind == NodeKind::native,
        "Q node descriptors differ");
  check(root.records.size() == 1 &&
        root.records[0].tuple.values() == edge(7, 9), "Q root R(7,9) record missing");
  check(child.records.size() == (answer ? 1U : 0U), "Q child record count differs");
  if (answer) {
    check(root.records[0].satisfied.value == 1 &&
          root.records[0].child_present == std::vector<bool>{true} && root.records[0].survives,
          "Q root child flag / survival differs after insertion");
    check(root.survivors.size() == 1 && root.survivors[0].values() == edge(7, 9),
          "Q root survivor differs after insertion");
    check(root.parent_keys.size() == 1 && root.parent_keys[0].key.values().empty() &&
          root.parent_keys[0].support.value == 1, "Q root empty parent key differs");
    check(root.visible_keys && root.visible_keys->size() == 1 &&
          root.visible_keys->front().key.values() == row(7) &&
          root.visible_keys->front().support.value == 1, "Q root E(7) differs");
    check(child.records[0].tuple.values() == row(9) &&
          child.records[0].satisfied.value == 0 && child.records[0].child_present.empty() &&
          child.records[0].survives, "Q child S(9) record differs");
    check(child.survivors.size() == 1 && child.survivors[0].values() == row(9) &&
          child.parent_keys.size() == 1 && child.parent_keys[0].key.values() == row(9) &&
          child.parent_keys[0].support.value == 1 && !child.visible_keys,
          "Q child survivor / separator differs");
  } else {
    check(root.records[0].satisfied.value == 0 &&
          root.records[0].child_present == std::vector<bool>{false} &&
          !root.records[0].survives && root.survivors.empty() && root.parent_keys.empty() &&
          root.visible_keys && root.visible_keys->empty(),
          "Q root rollback state differs");
    check(child.survivors.empty() && child.parent_keys.empty() && !child.visible_keys,
          "Q child rollback state differs");
  }
}

void check_q_initial_physical(const PhysicalSnapshot& state,
                              const Database& initial) {
  check(state.sequence == 0 && state.physical.tables == initial.tables,
        "Q source state changed before publication");
  check_q_state(state.support, 0, false);
  check(state.derivations.size() == 2 && state.derivations[0].size() == 1 &&
        state.derivations[0][0].tuple.values() == edge(7, 9) &&
        state.derivations[0][0].count == 1 && state.derivations[1].empty(),
        "Q initial derivations differ");
}

void check_constraint_q_rollback(const PhysicalSnapshot& state,
                                 const ConstraintQFixture& fixture) {
  check(state.sequence == 0 && state.physical.tables == fixture.initial.tables &&
        state.support.sequence == 0 && !state.support.has_answer,
        "constraint-heavy Q failure changed source or committed sequence");
  const auto& root = state.support.nodes[0];
  const auto& child = state.support.nodes[1];
  check(root.records.size() == 1 && root.records[0].tuple.values() == edge(7, 9) &&
        root.records[0].satisfied.value == 0 &&
        root.records[0].child_present == std::vector<bool>{false} &&
        !root.records[0].survives && root.survivors.empty() &&
        root.parent_keys.empty() && root.visible_keys && root.visible_keys->empty(),
        "constraint-heavy Q failure changed the R before-state");
  const auto expected_child_count = static_cast<std::size_t>(
      ConstraintQFixture::irrelevant_end - ConstraintQFixture::irrelevant_begin);
  check(child.records.size() == expected_child_count &&
        child.survivors.size() == expected_child_count &&
        child.parent_keys.size() == expected_child_count && !child.visible_keys,
        "constraint-heavy Q failure changed the committed S before-state");
  for (const auto& record : child.records)
    check(record.tuple.values() != row(9),
          "constraint-heavy Q failure retained the rejected S(9) row");
}

void check_q_journal(const SupportEpoch& epoch) {
  check(epoch.journal && epoch.journal->sequence == epoch.sequence &&
        epoch.journal->records.size() == 7 && epoch.journal->events.empty(),
        "Q mandatory support journal totals differ");
  const auto changed = [&](NodeId node, SupportRole role, const Row& key,
                           std::uint64_t cause) {
    for (const auto& record : epoch.journal->records)
      if (record.handle.node == node && record.handle.role == role &&
          record.tuple().values() == key && record.cause == cause &&
          !record.before.member && record.after.member)
        return true;
    return false;
  };
  check(changed(NodeId{1}, SupportRole::records, row(9), 1) &&
        changed(NodeId{1}, SupportRole::survivors, row(9), 1) &&
        changed(NodeId{1}, SupportRole::parent_support, row(9), 1) &&
        changed(NodeId{0}, SupportRole::survivors, edge(7, 9), 2) &&
        changed(NodeId{0}, SupportRole::parent_support, Row{}, 2) &&
        changed(NodeId{0}, SupportRole::visible, row(7), 2),
        "Q journal before/after changes or causes differ");
  bool root_flag_change = false;
  for (const auto& record : epoch.journal->records)
    if (record.handle.node == NodeId{0} && record.handle.role == SupportRole::records &&
        record.tuple().values() == edge(7, 9))
      root_flag_change = record.cause == 2 && record.before.member && record.after.member &&
          record.before.satisfied == SatisfiedChildCount{0} &&
          record.after.satisfied == SatisfiedChildCount{1} &&
          std::ranges::equal(record.before.child_present, std::vector<bool>{false}) &&
          std::ranges::equal(record.after.child_present, std::vector<bool>{true});
  check(root_flag_change, "Q journal did not retain the R child-flag transition");
}

void check_observation_header(const ObservationSnapshot& snapshot,
                              ObservationMode mode, std::uint64_t sequence,
                              ObservationLayer owner, std::uint64_t runtime_owner) {
  check(snapshot.mandatory_accounting && snapshot.options.mode == mode,
        "observation mode or mandatory-accounting marker differs");
  check(snapshot.support_owner == runtime_owner,
        "observation snapshot support owner differs from runtime owner");
  check(!snapshot.current && snapshot.last && snapshot.last->sequence == sequence &&
        snapshot.last->owner == owner && snapshot.last->outcome == ObservationOutcome::committed,
        "observation last-attempt summary differs");
  check(snapshot.last->attempt > 0 && snapshot.attempts >= snapshot.last->attempt &&
        snapshot.commits > 0 && snapshot.aborts == 0,
        "observation lifetime attempt counters differ");
  check(!snapshot.trace_dropped_saturated,
        "ordinary observation attempt unexpectedly saturated its dropped count");
}

void check_q_physical_observation(const ObservationSnapshot& snapshot,
                                  ObservationMode mode, std::uint64_t owner) {
  if (mode == ObservationMode::off) {
    check(snapshot.options.mode == ObservationMode::off && snapshot.mandatory_accounting &&
          !snapshot.current && !snapshot.last && snapshot.attempts == 0 &&
          snapshot.trace == TraceDisposition::disabled && !snapshot.trace_dropped_saturated,
          "off mode retained an observation attempt");
    return;
  }
  check_observation_header(snapshot, mode, 1, ObservationLayer::physical, owner);
  const auto& summary = *snapshot.last;
  check_metric(summary, MetricId::support_work, MetricAvailability::available, 40,
               "observed Q support work differs");
  check_metric(summary, MetricId::support_reverse_index_records_visited,
               MetricAvailability::available, 1, "Q reverse-index visits differ");
  check_metric(summary, MetricId::support_native_record_visits,
               MetricAvailability::available, 2, "Q native record visits differ");
  check_metric(summary, MetricId::physical_work_inclusive,
               MetricAvailability::available, 44, "Q inclusive physical work differs");
  check_metric(summary, MetricId::physical_work_exclusive,
               MetricAvailability::available, 4, "Q exclusive physical work differs");
  check_metric(summary, MetricId::physical_aliases_filtered,
               MetricAvailability::available, 0, "explicit zero alias-filter count missing");
  check_metric(summary, MetricId::physical_constraint_rows,
               MetricAvailability::available, 0, "explicit zero constraint-row count missing");
  check_metric(summary, MetricId::delta_work,
               MetricAvailability::unavailable, 0, "unentered delta-layer metric must be unavailable");
  check_metric(summary, MetricId::delta_propagation_ns,
               MetricAvailability::unavailable, 0, "unentered delta timing must be unavailable");
  check(descriptor(MetricId::physical_work_inclusive).scope ==
            descriptor(MetricId::support_work).scope,
        "inclusive/support metrics have different attempt scopes");
  check(summary.metric(MetricId::physical_work_inclusive).value ==
            summary.metric(MetricId::physical_work_exclusive).value +
                summary.metric(MetricId::support_work).value,
        "inclusive physical work double-counts or omits support work");
  check(snapshot.trace == (mode == ObservationMode::trace
                               ? TraceDisposition::committed
                               : TraceDisposition::disabled),
        "Q trace disposition differs by mode");
}

struct PhysicalModeRun {
  SupportMetrics support;
  PhysicalMetrics physical;
  std::size_t allocations = 0;
  ObservationTrace trace;
};

PhysicalModeRun run_q_physical_mode(ObservationMode mode, BuildMethod method,
                                    std::size_t trace_capacity = 256,
                                    std::uint64_t sample_period = 1,
                                    std::uint64_t sample_offset = 0) {
  QFixture fixture;
  PhysicalRuntimeOptions options;
  options.support.work_limit = 40;
  options.support.observation = observation_options(mode, trace_capacity,
                                                     sample_period, sample_offset);
  options.work_limit = 44;
  const BuildOptions build{method, std::nullopt};
  auto runtime = PhysicalRuntime::initialize(fixture.plan, fixture.initial,
                                              options, build);
  if (mode == ObservationMode::off)
    check(!runtime.observations().last && runtime.observations().attempts == 0,
          "off-mode initialization unexpectedly admitted an observation");
  else
    check(runtime.observations().attempts == 0 && !runtime.observations().last,
          "initialization replay must not appear as an update attempt");

  const PhysicalSetUpdate update{1, TableId{1}, SetOperation::insert, row(9)};
  std::optional<PhysicalEpoch> output;
  const auto allocations = allocation_probe::count_during([&] {
    output.emplace(runtime.apply(update));
  });
  check(output.has_value(), "physical Q update returned no epoch");
  const auto& epoch = *output;
  check_q_physical_metrics(epoch.input.metrics);
  check_q_metrics(epoch.support.metrics);
  check(epoch.input.sequence == 1 && epoch.support.sequence == 1 &&
        epoch.input.physical_changed && epoch.support.native_changed &&
        epoch.support.has_answer, "physical Q update publication differs");
  check_q_journal(epoch.support);
  check_q_state(runtime.snapshot().support, 1, true);
  check(runtime.snapshot().physical.tables[0] == fixture.initial.tables[0] &&
        runtime.snapshot().physical.tables[1] == Relation{row(9)},
        "physical Q source tables differ after commit");
  check(runtime.derivation_count(OccurrenceId{0}, edge(7, 9)) == 1 &&
        runtime.derivation_count(OccurrenceId{1}, row(9)) == 1,
        "physical Q derivation counts differ");
  const auto expected = expected_q(fixture);
  check(expected == Relation{row(7)} && drain_physical(runtime.results()) == expected,
        "physical Q answer differs from the independent evaluator");
  check_q_physical_observation(runtime.observations(), mode, runtime.owner().value);
  ObservationTrace trace;
  if (mode == ObservationMode::trace) {
    trace = runtime.observation_trace();
    check(trace.snapshot.trace_records == trace.records.size() &&
          !trace.snapshot.trace_truncated && trace.snapshot.trace_dropped == 0 &&
        !trace.snapshot.trace_dropped_saturated &&
          trace.records.size() > 2 && trace.records.front().kind == TraceKind::begin &&
          trace.records.back().kind == TraceKind::commit,
          "full Q trace is incomplete or missing terminal events");
    std::size_t source_changes = 0, aliases = 0, native_events = 0;
    std::size_t enqueued = 0, applied = 0, journals = 0, reverse_visits = 0;
    for (const auto& item : trace.records) {
      source_changes += item.kind == TraceKind::source_change ? 1U : 0U;
      aliases += item.kind == TraceKind::alias ? 1U : 0U;
      native_events += item.kind == TraceKind::native_event ? 1U : 0U;
      enqueued += item.kind == TraceKind::child_enqueued ? 1U : 0U;
      applied += item.kind == TraceKind::child_applied ? 1U : 0U;
      journals += item.kind == TraceKind::journal ? 1U : 0U;
      reverse_visits += item.kind == TraceKind::reverse_visit ? 1U : 0U;
      if (item.kind == TraceKind::alias)
        check(item.occurrence == 1 && item.prefix == 1,
              "Q trace alias occurrence/prefix differs");
      if (item.kind == TraceKind::native_event)
        check(item.node == 1 && item.before == 0 && item.after == 1 &&
              item.tuple != observation_no_id && item.event == 1 && item.cause == 0,
              "Q trace native event identity differs");
      if (item.kind == TraceKind::child_enqueued)
        check(item.event == 2 && item.cause == 1 && item.node == 0 &&
              item.before == 0 && item.after == 1,
              "Q trace queued child event identity differs");
      if (item.kind == TraceKind::child_applied)
        check(item.event == 2 && item.cause == 0 && item.node == 0,
              "Q trace applied child event identity differs");
      if (item.kind == TraceKind::reverse_visit)
        check(item.node == 0 && item.event == 2 && item.cause == 2 &&
              item.tuple != observation_no_id,
              "Q reverse visit trace identity differs");
    }
    check(source_changes == 1 && aliases == 1 && native_events == 1 &&
          enqueued == 1 && applied == 1 && journals == 7 && reverse_visits == 1,
          "Q trace record-kind counts differ from the hand trace");
  }

  const PhysicalSetUpdate duplicate{2, TableId{1}, SetOperation::insert, row(9)};
  const auto repeated = runtime.apply(duplicate);
  check(!repeated.input.physical_changed && !repeated.support.native_changed &&
        repeated.support.journal == nullptr && repeated.support.transitions.empty() &&
        repeated.input.metrics.work == 0 && repeated.support.metrics.work == 0 &&
        drain_physical(runtime.results()) == expected,
        "physical duplicate update changed mandatory state or result");
  const auto no_op_observation = runtime.observations();
  if (mode == ObservationMode::off) {
    check(!no_op_observation.last && no_op_observation.attempts == 0,
          "off mode created a duplicate no-op attempt");
  } else {
    check(no_op_observation.last && no_op_observation.last->sequence == 2 &&
          no_op_observation.last->outcome == ObservationOutcome::committed,
          "duplicate no-op did not close a committed observation attempt");
    check_metric(*no_op_observation.last, MetricId::support_work,
                 MetricAvailability::available, 0,
                 "duplicate no-op support work must be an explicit zero");
    check_metric(*no_op_observation.last, MetricId::physical_work_inclusive,
                 MetricAvailability::available, 0,
                 "duplicate no-op physical work must be an explicit zero");
    const auto expected_no_op_trace = mode != ObservationMode::trace
        ? TraceDisposition::disabled
        : ((2U % sample_period) == sample_offset
               ? TraceDisposition::committed
               : TraceDisposition::not_sampled);
    check(no_op_observation.trace == expected_no_op_trace,
          "duplicate no-op trace disposition differs");
    check(!no_op_observation.trace_dropped_saturated,
          "duplicate no-op did not reset its dropped-count saturation flag");
    if (mode == ObservationMode::trace && expected_no_op_trace == TraceDisposition::not_sampled)
      check(runtime.observation_trace().records.empty(),
            "unselected duplicate sequence retained causal records");
  }
  return {epoch.support.metrics, epoch.input.metrics, allocations, std::move(trace)};
}

void test_q_observation_modes() {
  check_registry();
  for (const auto method : {BuildMethod::direct, BuildMethod::insertion_replay}) {
    std::optional<PhysicalModeRun> baseline;
    for (const auto mode : modes) {
      auto run = run_q_physical_mode(mode, method, 256, 2, 1);
      if (!baseline) baseline.emplace(std::move(run));
      else {
        check(same_support_metrics(baseline->support, run.support) &&
              same_physical_metrics(baseline->physical, run.physical),
              "Q mandatory work/counters changed by observation mode");
        check(baseline->allocations == run.allocations,
              "optional observation mode added allocations during physical mutation");
      }
      if (mode == ObservationMode::trace) {
        check(run.trace.snapshot.trace == TraceDisposition::committed,
              "sampled Q sequence 1 was not traced");
        const auto selected_count = run.trace.records.size();
        check(selected_count > 2, "selected Q trace has no causal records");
      }
    }
  }
}

void test_direct_support_modes_and_allocations() {
  std::optional<SupportMetrics> baseline_metrics;
  std::optional<std::size_t> baseline_allocations;
  std::optional<std::size_t> baseline_noop_allocations;
  for (const auto mode : modes) {
    QFixture fixture;
    SupportOptions options;
    options.work_limit = 40;
    options.observation = observation_options(mode, 256, 2, 1);
    SupportRuntime runtime(fixture.plan, options);
    const auto seed = runtime.apply({1, NodeId{0}, SetOperation::insert, edge(7, 9)});
    check(seed.native_changed && !seed.has_answer && seed.sequence == 1,
          "direct support setup differs from the Q before-state");
    const NativeSetUpdate update{2, NodeId{1}, SetOperation::insert, row(9)};
    std::optional<SupportEpoch> output;
    const auto allocations = allocation_probe::count_during([&] {
      output.emplace(runtime.apply(update));
    });
    check(output.has_value(), "direct support Q update returned no epoch");
    check_q_metrics(output->metrics);
    check(output->native_changed && output->has_answer && output->sequence == 2,
          "direct support Q update publication differs");
    check_q_journal(*output);
    check_q_state(runtime.snapshot(), 2, true);
    auto final_database = fixture.initial;
    final_database.tables[1].insert(row(9));
    const auto expected = reference::evaluate(fixture.catalog, fixture.query,
                                               final_database);
    check(expected == Relation{row(7)} && drain(runtime.results()) == expected,
          "direct support Q answer differs from independent evaluation");
    const auto observed = runtime.observations();
    if (mode == ObservationMode::off) {
      check(!observed.last && observed.mandatory_accounting &&
            observed.trace == TraceDisposition::disabled,
            "off direct support mode retained an observation");
    } else {
      check_observation_header(observed, mode, 2, ObservationLayer::support,
                               runtime.owner().value);
      check_metric(*observed.last, MetricId::support_work,
                   MetricAvailability::available, 40,
                   "direct support observation work differs");
      check_metric(*observed.last, MetricId::support_reverse_index_records_visited,
                   MetricAvailability::available, 1,
                   "direct support reverse visit differs");
      check_metric(*observed.last, MetricId::physical_work_inclusive,
                   MetricAvailability::unavailable, 0,
                   "unentered physical layer must be unavailable");
      check_metric(*observed.last, MetricId::support_candidates_created,
                   MetricAvailability::available, 0,
                   "explicit zero generalized-candidate metric missing");
    }
    if (!baseline_metrics) {
      baseline_metrics.emplace(output->metrics);
      baseline_allocations.emplace(allocations);
    } else {
      check(same_support_metrics(*baseline_metrics, output->metrics),
            "direct Q support metrics changed by observation mode");
      check(*baseline_allocations == allocations,
            "optional observation mode added allocations during direct mutation");
    }
    for (const auto& noop : {NativeSetUpdate{3,NodeId{1},SetOperation::insert,row(9)},
                             NativeSetUpdate{4,NodeId{1},SetOperation::erase,row(10)}}) {
      std::optional<SupportEpoch> result;
      const auto noop_allocations=allocation_probe::count_during([&]{result.emplace(runtime.apply(noop));});
      check(result && !result->native_changed && !result->journal && result->metrics.work==0,
            "direct no-op must retain its transaction-free path");
      if(!baseline_noop_allocations)baseline_noop_allocations=noop_allocations;
      else check(noop_allocations==*baseline_noop_allocations,"direct no-op observation added allocations");
      const auto latest=runtime.observations();
      if(mode==ObservationMode::off)check(!latest.last,"disabled no-op observation was published");
      else {
        check_observation_header(latest,mode,noop.sequence,ObservationLayer::support,runtime.owner().value);
        check_metric(*latest.last,MetricId::support_work,MetricAvailability::available,0,"no-op support zero is missing");
        check_metric(*latest.last,MetricId::physical_work_inclusive,MetricAvailability::unavailable,0,"no-op invented a physical layer");
        check(latest.attempts==noop.sequence && latest.commits==noop.sequence,"direct no-op observation census lost an epoch");
      }
    }
  }
}

void test_work_limit_boundaries_and_rollback_allocations() {
  std::optional<std::size_t> support_failure_allocations;
  std::optional<std::size_t> physical_failure_allocations;
  std::optional<std::size_t> support_cancel_allocations;
  std::optional<std::size_t> physical_cancel_allocations;
  std::optional<std::size_t> nested_support_failure_allocations;
  std::optional<std::size_t> constraint_charge_failure_allocations;

  for (const auto mode : modes) {
    QFixture fixture;
    SupportOptions support_options;
    support_options.work_limit = 39;
    support_options.observation = observation_options(mode, 256);
    SupportRuntime support(fixture.plan, support_options);
    static_cast<void>(support.apply({1, NodeId{0}, SetOperation::insert, edge(7, 9)}));
    const NativeSetUpdate support_update{2, NodeId{1}, SetOperation::insert, row(9)};
    const auto support_allocations = allocation_probe::count_during([&] {
      expect_resource_limit([&] { static_cast<void>(support.apply(support_update)); },
                            "support 39-work boundary did not reject");
    });
    check(support.sequence() == 1 && support.ready() && !support.has_answer(),
          "support 39-work failure did not roll back sequence and answer");
    check(!support.find(NodeId{1}, SupportRole::records, row(9)),
          "support 39-work failure retained S(9)");
    check_q_state(support.snapshot(), 1, false);
    const auto support_failure = support.observations();
    if (mode == ObservationMode::off) {
      check(!support_failure.last, "off support failure retained an observation");
    } else {
      check(support_failure.last && support_failure.last->sequence == 2 &&
            support_failure.last->outcome == ObservationOutcome::aborted,
            "support limit failure was not recorded as an aborted attempt");
      const auto& work = support_failure.last->metric(MetricId::support_work);
      check(work.availability == MetricAvailability::available && work.value < 40,
            "support failure lost partial mandatory work accounting");
      check(support_failure.aborts == 1 && support_failure.commits == 1,
            "support failure lifetime outcome counters differ");
      if (mode == ObservationMode::trace) {
        const auto trace = support.observation_trace();
        check(trace.snapshot.trace == TraceDisposition::aborted &&
              !trace.records.empty() && trace.records.front().kind == TraceKind::begin &&
              trace.records.back().kind == TraceKind::abort,
              "support failure trace omits its abort terminal record");
      }
    }
    if (!support_failure_allocations) support_failure_allocations = support_allocations;
    else check(*support_failure_allocations == support_allocations,
               "optional observation mode allocated during support failure rollback");

    QFixture cancel_fixture;
    SupportOptions cancel_options;
    cancel_options.observation = observation_options(mode, 256);
    SupportRuntime cancel_runtime(cancel_fixture.plan, cancel_options);
    static_cast<void>(cancel_runtime.apply(
        {1, NodeId{0}, SetOperation::insert, edge(7, 9)}));
    const auto cancel_allocations = allocation_probe::count_during([&] {
      auto pending = cancel_runtime.begin_epoch(2, SetOperation::insert);
      check(pending.stage(NodeId{1}, row(9)), "support cancel fixture did not stage S(9)");
      pending.rollback();
    });
    check(cancel_runtime.sequence() == 1 && cancel_runtime.ready() &&
          !cancel_runtime.has_answer(), "support cancellation changed committed state");
    check_q_state(cancel_runtime.snapshot(), 1, false);
    const auto cancel_observation = cancel_runtime.observations();
    if (mode == ObservationMode::off)
      check(!cancel_observation.last, "off support cancellation retained an observation");
    else {
      check(cancel_observation.last && cancel_observation.last->sequence == 2 &&
            cancel_observation.last->outcome == ObservationOutcome::aborted,
            "support cancellation did not close its attempt as aborted");
      check_metric(*cancel_observation.last, MetricId::support_work,
                   MetricAvailability::available, 40,
                   "support cancellation lost completed mandatory work");
    }
    if (!support_cancel_allocations) support_cancel_allocations = cancel_allocations;
    else check(*support_cancel_allocations == cancel_allocations,
               "optional observation mode allocated during support cancellation");

    PhysicalRuntimeOptions physical_options;
    physical_options.work_limit = 43;
    physical_options.support.observation = observation_options(mode, 256);
    auto physical = PhysicalRuntime::initialize(fixture.plan, fixture.initial,
                                                 physical_options);
    const PhysicalSetUpdate physical_update{1, TableId{1}, SetOperation::insert,
                                             row(9)};
    const auto physical_allocations = allocation_probe::count_during([&] {
      expect_resource_limit([&] {
        static_cast<void>(physical.apply(physical_update));
      }, "physical 43-work boundary did not reject");
    });
    check(physical.sequence() == 0 && physical.ready() && !physical.has_answer(),
          "physical 43-work failure did not roll back publication");
    check_q_initial_physical(physical.snapshot(), fixture.initial);
    check(drain_physical(physical.results()).empty(),
          "physical 43-work failure exposed a result");
    const auto physical_failure = physical.observations();
    if (mode == ObservationMode::off) {
      check(!physical_failure.last, "off physical failure retained an observation");
    } else {
      check(physical_failure.last && physical_failure.last->sequence == 1 &&
            physical_failure.last->outcome == ObservationOutcome::aborted,
            "physical limit failure was not recorded as an aborted attempt");
      check_metric(*physical_failure.last, MetricId::support_work,
                   MetricAvailability::available, 40,
                   "physical failure lost completed mandatory support work");
      check_metric(*physical_failure.last, MetricId::physical_work_inclusive,
                   MetricAvailability::unavailable, 0,
                   "physical/support incomplete total must be unavailable");
      check_metric(*physical_failure.last, MetricId::physical_work_exclusive,
                   MetricAvailability::unavailable, 0,
                   "incomplete physical/support rollup must be unavailable");
      if (mode == ObservationMode::trace) {
        const auto trace = physical.observation_trace();
        check(trace.snapshot.trace == TraceDisposition::aborted &&
              !trace.records.empty() && trace.records.front().kind == TraceKind::begin &&
              trace.records.back().kind == TraceKind::abort,
              "physical failure trace omits its abort terminal record");
      }
    }
    if (!physical_failure_allocations) physical_failure_allocations = physical_allocations;
    else check(*physical_failure_allocations == physical_allocations,
               "optional observation mode allocated during physical failure rollback");

    PhysicalRuntimeOptions nested_failure_options;
    nested_failure_options.work_limit = 1000;
    nested_failure_options.support.work_limit = 39;
    nested_failure_options.support.observation = observation_options(mode, 256);
    auto nested_limited = PhysicalRuntime::initialize(fixture.plan, fixture.initial,
                                                       nested_failure_options);
    const auto nested_allocations = allocation_probe::count_during([&] {
      expect_resource_limit([&] {
        static_cast<void>(nested_limited.apply(physical_update));
      }, "inner support 39-work boundary did not reject through physical runtime");
    });
    check(nested_limited.sequence() == 0 && nested_limited.ready() &&
          !nested_limited.has_answer(),
          "inner support work failure changed physical committed state");
    check_q_initial_physical(nested_limited.snapshot(), fixture.initial);
    const auto nested_failure = nested_limited.observations();
    if (mode == ObservationMode::off) {
      check(!nested_failure.last,
            "off inner-support failure retained an observation");
    } else {
      check(nested_failure.last && nested_failure.last->outcome == ObservationOutcome::aborted,
            "inner support limit failure was not recorded as aborted");
      const auto& work = nested_failure.last->metric(MetricId::support_work);
      check(work.availability == MetricAvailability::available && work.value < 40,
            "inner support failure lost partial mandatory work accounting");
      check_metric(*nested_failure.last, MetricId::physical_work_inclusive,
                   MetricAvailability::unavailable, 0,
                   "physical inclusive work must be unavailable after support-stage failure");
      check_metric(*nested_failure.last, MetricId::physical_work_exclusive,
                   MetricAvailability::unavailable, 0,
                   "physical exclusive work must be unavailable after support-stage failure");
      if (mode == ObservationMode::trace) {
        const auto trace = nested_limited.observation_trace();
        check(trace.snapshot.trace == TraceDisposition::aborted &&
              !trace.records.empty() && trace.records.back().kind == TraceKind::abort,
              "inner support failure trace omits abort");
      }
    }
    if (!nested_support_failure_allocations)
      nested_support_failure_allocations = nested_allocations;
    else
      check(*nested_support_failure_allocations == nested_allocations,
            "optional observations allocated during inner support failure rollback");

    ConstraintQFixture constrained;
    PhysicalRuntimeOptions constraint_options;
    // Literal physical prefix: source change 1 + 102 constraint rows + one
    // constraint validation + alias/derivation/crossing 1 each = 107. The
    // cap 130 admits that coordinator prefix and rejects adding support work 40.
    constexpr std::uint64_t coordinator_prefix = 107;
    constexpr std::uint64_t constraint_charge_cap = 130;
    static_assert(coordinator_prefix < constraint_charge_cap &&
                  constraint_charge_cap < coordinator_prefix + 40);
    constraint_options.work_limit = constraint_charge_cap;
    constraint_options.support.observation = observation_options(mode, 256);
    auto constraint_limited = PhysicalRuntime::initialize(constrained.plan,
                                                           constrained.initial,
                                                           constraint_options);
    const PhysicalSetUpdate constrained_update{1, TableId{1}, SetOperation::insert,
                                                row(9)};
    const auto constraint_allocations = allocation_probe::count_during([&] {
      expect_resource_limit([&] {
        static_cast<void>(constraint_limited.apply(constrained_update));
      }, "constraint-heavy support charge did not exceed its cap");
    });
    check(constraint_limited.sequence() == 0 && constraint_limited.ready() &&
          !constraint_limited.has_answer(),
          "constraint-heavy work failure changed physical committed state");
    check_constraint_q_rollback(constraint_limited.snapshot(), constrained);
    const auto constraint_failure = constraint_limited.observations();
    if (mode == ObservationMode::off) {
      check(!constraint_failure.last,
            "off constraint-heavy failure retained an observation");
    } else {
      check(constraint_failure.last &&
            constraint_failure.last->outcome == ObservationOutcome::aborted,
            "constraint-heavy physical charge failure was not recorded as aborted");
      check_metric(*constraint_failure.last, MetricId::support_work,
                   MetricAvailability::available, 40,
                   "constraint-heavy failure lost completed support work");
      check_metric(*constraint_failure.last, MetricId::physical_source_changes,
                   MetricAvailability::available, 1,
                   "constraint-heavy source charge differs");
      check_metric(*constraint_failure.last, MetricId::physical_constraint_rows,
                   MetricAvailability::available, 102,
                   "constraint-heavy row scan count differs");
      check_metric(*constraint_failure.last, MetricId::physical_constraint_validations,
                   MetricAvailability::available, 1,
                   "constraint-heavy validation count differs");
      check_metric(*constraint_failure.last, MetricId::physical_aliases_visited,
                   MetricAvailability::available, 1,
                   "constraint-heavy alias count differs");
      check_metric(*constraint_failure.last, MetricId::physical_derivation_changes,
                   MetricAvailability::available, 1,
                   "constraint-heavy derivation count differs");
      check_metric(*constraint_failure.last, MetricId::physical_native_crossings,
                   MetricAvailability::available, 1,
                   "constraint-heavy native crossing differs");
      const auto charged_prefix =
          constraint_failure.last->metric(MetricId::physical_source_changes).value +
          constraint_failure.last->metric(MetricId::physical_constraint_rows).value +
          constraint_failure.last->metric(MetricId::physical_constraint_validations).value +
          constraint_failure.last->metric(MetricId::physical_aliases_visited).value +
          constraint_failure.last->metric(MetricId::physical_derivation_changes).value +
          constraint_failure.last->metric(MetricId::physical_native_crossings).value;
      check(charged_prefix == coordinator_prefix &&
            charged_prefix >= constraint_failure.last->metric(MetricId::support_work).value,
            "constraint-heavy raw coordinator work does not exceed support work");
      check_metric(*constraint_failure.last, MetricId::physical_work_inclusive,
                   MetricAvailability::unavailable, 0,
                   "partial nested support charge exposed an invalid inclusive total");
      check_metric(*constraint_failure.last, MetricId::physical_work_exclusive,
                   MetricAvailability::unavailable, 0,
                   "partial nested support charge exposed an invalid exclusive total");
      if (mode == ObservationMode::trace) {
        const auto trace = constraint_limited.observation_trace();
        check(trace.snapshot.trace == TraceDisposition::aborted &&
              !trace.records.empty() && trace.records.back().kind == TraceKind::abort,
              "constraint-heavy failure trace omits abort");
      }
    }
    if (!constraint_charge_failure_allocations)
      constraint_charge_failure_allocations = constraint_allocations;
    else
      check(*constraint_charge_failure_allocations == constraint_allocations,
            "optional observations allocated during constraint-heavy failure rollback");

    PhysicalRuntimeOptions cancel_physical_options;
    cancel_physical_options.support.observation = observation_options(mode, 256);
    auto cancel_physical = PhysicalRuntime::initialize(fixture.plan, fixture.initial,
                                                        cancel_physical_options);
    const auto physical_cancel_count = allocation_probe::count_during([&] {
      auto pending = cancel_physical.prepare(physical_update);
      pending.rollback();
    });
    check(cancel_physical.sequence() == 0 && cancel_physical.ready() &&
          !cancel_physical.has_answer(), "physical cancellation changed committed state");
    check_q_initial_physical(cancel_physical.snapshot(), fixture.initial);
    const auto physical_cancel_observation = cancel_physical.observations();
    if (mode == ObservationMode::off)
      check(!physical_cancel_observation.last,
            "off physical cancellation retained an observation");
    else {
      check(physical_cancel_observation.last &&
            physical_cancel_observation.last->outcome == ObservationOutcome::aborted,
            "physical cancellation did not close its attempt as aborted");
      check_metric(*physical_cancel_observation.last, MetricId::support_work,
                   MetricAvailability::available, 40,
                   "physical cancellation lost completed support work");
      check_metric(*physical_cancel_observation.last, MetricId::physical_work_inclusive,
                   MetricAvailability::available, 44,
                   "physical cancellation lost completed inclusive work");
      check_metric(*physical_cancel_observation.last, MetricId::physical_work_exclusive,
                   MetricAvailability::available, 4,
                   "physical cancellation lost completed exclusive work");
    }
    if (!physical_cancel_allocations)
      physical_cancel_allocations = physical_cancel_count;
    else
      check(*physical_cancel_allocations == physical_cancel_count,
            "optional observation mode allocated during physical cancellation");
  }

  // The exact endpoints are exercised by test_direct_support_modes_and_allocations
  // (support work 40) and test_q_observation_modes (physical work 44).
  check(support_failure_allocations && physical_failure_allocations &&
        support_cancel_allocations && physical_cancel_allocations &&
        nested_support_failure_allocations && constraint_charge_failure_allocations,
        "allocation comparison did not cover all limit and cancellation paths");
}

ObservationTrace run_q_trace_capacity(std::size_t capacity) {
  QFixture fixture;
  PhysicalRuntimeOptions options;
  options.support.work_limit = 40;
  options.support.observation = observation_options(ObservationMode::trace,
                                                     capacity);
  options.work_limit = 44;
  auto runtime = PhysicalRuntime::initialize(fixture.plan, fixture.initial, options);
  static_cast<void>(runtime.apply(
      {1, TableId{1}, SetOperation::insert, row(9)}));
  return runtime.observation_trace();
}

void test_trace_caps_sampling_and_release() {
  const auto full = run_q_trace_capacity(256);
  check(!full.snapshot.trace_truncated && full.snapshot.trace_dropped == 0 &&
        full.snapshot.trace_records == full.records.size() && full.records.size() > 2,
        "full capacity trace unexpectedly truncated");
  const auto zero = run_q_trace_capacity(0);
  check(zero.records.empty() && zero.snapshot.trace_records == 0 &&
        zero.snapshot.trace_truncated && zero.snapshot.trace_dropped == full.records.size() &&
        !zero.snapshot.trace_dropped_saturated &&
        zero.snapshot.trace == TraceDisposition::committed,
        "zero-capacity trace did not report exact drops and committed outcome");
  const auto one = run_q_trace_capacity(1);
  check(one.records.size() == 1 && one.records.front().kind == TraceKind::begin &&
        one.snapshot.trace_records == 1 && one.snapshot.trace_truncated &&
        one.snapshot.trace_dropped == full.records.size() - 1 &&
        !one.snapshot.trace_dropped_saturated &&
        one.snapshot.trace == TraceDisposition::committed,
        "capacity-one trace did not preserve the first record and report loss");
  const auto exact = run_q_trace_capacity(full.records.size());
  check(exact.records.size() == full.records.size() &&
        exact.snapshot.trace_records == full.records.size() &&
        exact.snapshot.trace_dropped == 0 && !exact.snapshot.trace_dropped_saturated &&
        !exact.snapshot.trace_truncated &&
        exact.records.back().kind == TraceKind::commit,
        "exact-capacity trace did not retain its final commit event");

  QFixture fixture;
  PhysicalRuntimeOptions options;
  options.support.observation = observation_options(ObservationMode::trace, 256, 2, 1);
  auto runtime = PhysicalRuntime::initialize(fixture.plan, fixture.initial, options);
  static_cast<void>(runtime.apply({1, TableId{1}, SetOperation::insert, row(9)}));
  const auto selected = runtime.observation_trace();
  check(selected.snapshot.trace == TraceDisposition::committed &&
        selected.snapshot.trace_sequence == 1 && !selected.records.empty(),
        "selected odd sequence was not traced");
  const auto duplicate = runtime.apply({2, TableId{1}, SetOperation::insert, row(9)});
  check(!duplicate.input.physical_changed && duplicate.input.metrics.work == 0,
        "unselected no-op trace fixture unexpectedly changed state");
  const auto unselected = runtime.observation_trace();
  check(unselected.snapshot.trace == TraceDisposition::not_sampled &&
        unselected.snapshot.trace_sequence == 2 && unselected.records.empty() &&
        unselected.snapshot.trace_records == 0 && unselected.snapshot.trace_dropped == 0,
        "unselected even sequence retained a trace record");
  check(!unselected.snapshot.trace_dropped_saturated,
        "unselected trace did not reset the dropped-count saturation flag");

  ObservationTrace detached;
  {
    QFixture abort_fixture;
    PhysicalRuntimeOptions abort_options;
    abort_options.support.observation = observation_options(ObservationMode::trace, 256);
    auto aborting = PhysicalRuntime::initialize(abort_fixture.plan,
                                                 abort_fixture.initial,
                                                 abort_options);
    auto pending = aborting.prepare({1, TableId{1}, SetOperation::insert, row(9)});
    pending.rollback();
    detached = aborting.observation_trace();
    check(detached.snapshot.trace == TraceDisposition::aborted &&
          detached.snapshot.last &&
          detached.snapshot.last->outcome == ObservationOutcome::aborted &&
          !detached.records.empty() && detached.records.back().kind == TraceKind::abort,
          "cancelled physical scope did not retain an aborted terminal trace");
    check(aborting.sequence() == 0 && aborting.ready(),
          "cancelled trace fixture changed committed state");
  }
  check(!detached.records.empty() && detached.records.front().kind == TraceKind::begin &&
        detached.records.back().kind == TraceKind::abort,
        "owning numeric trace did not survive runtime destruction");
}

std::size_t injected_clock_calls = 0;
std::uint64_t injected_clock_value = 0;

std::uint64_t counting_clock() noexcept {
  ++injected_clock_calls;
  injected_clock_value += 10;
  return injected_clock_value;
}

void reset_clock() noexcept {
  injected_clock_calls = 0;
  injected_clock_value = 0;
  detail::set_observation_clock_for_testing(&counting_clock);
}

struct ClockReset {
  ~ClockReset() { detail::set_observation_clock_for_testing(nullptr); }
};

void test_optional_clock_reads() {
  ClockReset reset;
  for (const auto mode : modes) {
    QFixture fixture;
    DeltaOptions options;
    options.physical.support.observation = observation_options(
        mode, 256, 1, 0, true);
    options.completion = DeltaCompletion::ordered_replay;
    auto runtime = DeltaRuntime::initialize(fixture.plan, fixture.initial, options);
    reset_clock();
    auto epoch = runtime.apply({1, TableId{1}, SetOperation::insert, row(9)});
    const auto snapshot = runtime.observations();
    const auto expected = expected_q(fixture);
    const auto signed_result = epoch.next();
    check(expected == Relation{row(7)} && signed_result &&
          signed_result->operation == SetOperation::insert &&
          signed_result->tuple.values() == row(7) && !epoch.next(),
          "delta clock fixture changed the independent signed answer");
    check(epoch.input().support.metrics.work == 40 &&
          epoch.input().input.metrics.work == 44,
          "delta clock fixture changed mandatory support/physical work");
    if (mode == ObservationMode::off) {
      check(injected_clock_calls == 0 && !snapshot.last,
            "off mode evaluated the optional clock");
      continue;
    }
    check(snapshot.last && snapshot.last->sequence == 1 &&
          snapshot.last->outcome == ObservationOutcome::committed,
          "delta clock attempt summary differs");
    const auto& summary = *snapshot.last;
    const auto& reads = summary.metric(MetricId::delta_clock_reads);
    const auto& nested_reads = summary.metric(MetricId::nested_cursor_clock_reads);
    check(reads.availability == MetricAvailability::available &&
          nested_reads.availability == MetricAvailability::available &&
          reads.value + nested_reads.value == injected_clock_calls,
          "injected clock calls do not reconcile with disjoint delta and nested-cursor reads");
    if (mode == ObservationMode::counters) {
      check(injected_clock_calls == 0,
            "counters mode performed an optional clock read");
      check_metric(summary, MetricId::delta_propagation_ns,
                   MetricAvailability::disabled, 0,
                   "counters mode timing must be explicitly disabled");
    } else {
      check(injected_clock_calls > 0,
            "timed/trace mode did not invoke the injected clock");
      const auto& propagation = summary.metric(MetricId::delta_propagation_ns);
      const auto& internal = summary.metric(MetricId::delta_internal_delta_ns);
      check(propagation.availability == MetricAvailability::available &&
            internal.availability == MetricAvailability::available &&
            (propagation.value > 0 || internal.value > 0),
            "timed/trace mode did not record positive deterministic timings");
    }
    check_metric(summary, MetricId::support_work, MetricAvailability::available, 40,
                 "timing mode altered mandatory support work");
    check_metric(summary, MetricId::physical_work_inclusive,
                 MetricAvailability::available, 44,
                 "timing mode altered mandatory physical work");
  }

  QFixture fixture;
  DeltaOptions no_trace_clock;
  no_trace_clock.physical.support.observation = observation_options(
      ObservationMode::trace, 256, 1, 0, false);
  no_trace_clock.completion = DeltaCompletion::ordered_replay;
  auto runtime = DeltaRuntime::initialize(fixture.plan, fixture.initial, no_trace_clock);
  reset_clock();
  const auto epoch = runtime.apply({1, TableId{1}, SetOperation::insert, row(9)});
  const auto snapshot = runtime.observations();
  check(epoch.input().support.metrics.work == 40 && injected_clock_calls == 0,
        "trace_timings=false performed a clock read or changed mandatory work");
  check(snapshot.last && snapshot.trace == TraceDisposition::committed,
        "trace without timings did not retain its causal trace");
  check_metric(*snapshot.last, MetricId::delta_clock_reads,
               MetricAvailability::available, 0,
               "trace clock-disabled counter must be an explicit zero");
  check_metric(*snapshot.last, MetricId::delta_propagation_ns,
               MetricAvailability::disabled, 0,
               "trace timing-disabled state is not explicit");
}

void test_multi_alias_generalized_projection() {
  std::optional<PhysicalMetrics> baseline_physical;
  std::optional<SupportMetrics> baseline_support;
  std::optional<std::size_t> baseline_allocations;
  for (const auto mode : modes) {
    AliasFixture fixture;
    check(fixture.plan.nodes().size() == 3 &&
          fixture.plan.nodes()[0].kind == NodeKind::generalized &&
          fixture.plan.inputs().size() == 2 && fixture.query.head.size() == 1 &&
          fixture.plan.enumeration().steps.size() == 3 &&
          fixture.plan.nodes()[0].visible_relation.has_value() &&
          fixture.plan.nodes()[1].visible_relation.has_value() &&
          fixture.plan.nodes()[2].visible_relation.has_value(),
          "self-join fixture is not a two-alias generalized projection");
    Database initial;
    initial.tables.resize(1);
    PhysicalRuntimeOptions options;
    options.support.observation = observation_options(mode, 256);
    PhysicalRuntime runtime(fixture.plan, options);
    const PhysicalSetUpdate update{1, TableId{0}, SetOperation::insert,
                                   {integer(3), integer(3), string("edge")}};
    std::optional<PhysicalEpoch> output;
    const auto allocations = allocation_probe::count_during([&] {
      output.emplace(runtime.apply(update));
    });
    const auto& epoch = *output;
    Database final_database = initial;
    final_database.tables[0].insert({integer(3), integer(3), string("edge")});
    const auto expected = reference::evaluate(fixture.catalog, fixture.query,
                                              final_database);
    const auto actual = drain_physical(runtime.results());
    const auto state = runtime.snapshot();
    check(expected == Relation{row(3)} && actual == expected,
          "self-join projection differs from independent evaluation");
    check(state.sequence == 1 && state.physical.tables == final_database.tables &&
          state.support.sequence == 1 && state.support.has_answer &&
          state.support.nodes.size() == 3,
          "self-join committed source/support state differs from the independent fixture");
    const auto& generalized = state.support.nodes[0];
    check(generalized.kind == NodeKind::generalized && generalized.records.size() == 1 &&
          generalized.records[0].tuple.values() == row(3) &&
          generalized.records[0].survives && generalized.survivors.size() == 1 &&
          generalized.survivors[0].values() == row(3) && generalized.visible_keys &&
          generalized.visible_keys->size() == 1 &&
          generalized.visible_keys->front().key.values() == row(3),
          "self-join generalized candidate or projected visible state differs");
    check(state.support.nodes[1].records.size() == 1 &&
          state.support.nodes[1].records[0].tuple.values() == edge(3, 3) &&
          state.support.nodes[2].records.size() == 1 &&
          state.support.nodes[2].records[0].tuple.values() == edge(3, 3),
          "self-join native alias state differs");
    for (const auto& node : state.support.nodes)
      check(node.visible_keys && node.visible_keys->size() == 1 &&
            node.visible_keys->front().key.values() == row(3),
            "self-join C* node does not retain its single E(y=3) key");
    const auto support_diagnostic = describe_support_metrics(epoch.support.metrics);
    check(epoch.input.metrics.source_changes == 1 &&
          epoch.input.metrics.aliases_visited == 2 &&
          epoch.input.metrics.aliases_filtered == 0 &&
          epoch.input.metrics.derivation_changes == 2 &&
          epoch.input.metrics.native_crossings == 2,
          "self-join physical alias counters differ");
    check(epoch.support.metrics.candidates_created == 1,
          "self-join generalized candidate count differs from the hand trace:" +
              support_diagnostic);
    check(epoch.support.metrics.visible_key_transitions == 3,
          "self-join C* visible transition count differs from the hand trace:" +
              support_diagnostic);
    const auto observed = runtime.observations();
    if (mode == ObservationMode::off) {
      check(!observed.last && runtime.has_answer(),
            "self-join off mode lost mandatory answer state");
    } else {
      check(observed.last && observed.last->sequence == 1 &&
            observed.last->outcome == ObservationOutcome::committed,
            "self-join observation attempt differs");
      check_metric(*observed.last, MetricId::physical_aliases_visited,
                   MetricAvailability::available, 2,
                   "self-join alias visit observation differs");
      check_metric(*observed.last, MetricId::support_candidates_created,
                   MetricAvailability::available,
                   epoch.support.metrics.candidates_created,
                   "self-join candidate metric differs from mandatory support state");
      check_metric(*observed.last, MetricId::support_work,
                   MetricAvailability::available, epoch.support.metrics.work,
                   "self-join support work observation differs");
      check_metric(*observed.last, MetricId::physical_work_inclusive,
                   MetricAvailability::available, epoch.input.metrics.work,
                   "self-join inclusive work observation differs");
    }
    if (!baseline_physical) {
      baseline_physical.emplace(epoch.input.metrics);
      baseline_support.emplace(epoch.support.metrics);
      baseline_allocations.emplace(allocations);
    } else {
      check(same_physical_metrics(*baseline_physical, epoch.input.metrics) &&
            same_support_metrics(*baseline_support, epoch.support.metrics),
            "self-join mandatory metrics changed by observation mode");
      check(*baseline_allocations == allocations,
            "optional observations allocated during self-join mutation");
    }
  }
}

void test_session_retained_summary() {
  QFixture fixture;
  Database final_database;
  final_database.tables.resize(2);
  final_database.tables[0].insert(edge(7, 9));
  const io::InputEvent input{
      {1, TableId{1}, SetOperation::insert, row(9)},
      io::SourcePosition{"observation-test", 0},
  };
  auto bytes = io::write_input_json(input, fixture.catalog);
  bytes.push_back('\n');
  std::unique_ptr<std::istream> stream =
      std::make_unique<std::istringstream>(std::move(bytes));
  SessionOptions options;
  options.delta.physical.support.observation = observation_options(
      ObservationMode::trace, 256);
  auto session = QuerySession::create(fixture.plan, fixture.initial,
                                      std::move(stream), options);
  session->start();
  check(session->begin_next_result() == SessionBegin::pending,
        "session did not admit the prepared Q input");
  while (session->step() != DeltaStep::prepared) {}
  session->commit();
  const auto output = session->next_output();
  check(output && output->operation == SetOperation::insert &&
        output->tuple.values() == row(7),
        "session output differs from independent Q result");
  check(!session->next_output(), "session emitted an unexpected second result");
  const auto retained = session->observations();
  check(retained.session_attached && retained.session_committed_sequence == 1 &&
        retained.last && retained.last->sequence == 1 &&
        retained.last->outcome == ObservationOutcome::committed &&
        retained.trace == TraceDisposition::committed,
        "session did not expose its drained committed observation summary");
  const auto trace = session->observation_trace();
  check(trace.snapshot.session_attached && trace.snapshot.trace == TraceDisposition::committed &&
        !trace.records.empty(), "session trace disappeared before drop");
  session->stop();
  session->drop();
  const auto after_drop = session->observations();
  check(after_drop.session_attached && after_drop.session_committed_sequence == 1 &&
        after_drop.last && after_drop.last->sequence == 1 &&
        after_drop.last->outcome == ObservationOutcome::committed,
        "session drop lost the retained committed epoch summary");
  const auto released = session->observation_trace();
  check(released.snapshot.trace == TraceDisposition::released &&
        released.records.empty() && released.snapshot.last &&
        released.snapshot.last->sequence == 1,
        "session drop did not release trace rows while retaining its summary");
}

}  // namespace

template <class Action>
void run_scenario(std::string_view name, Action&& action) {
  std::cout << "[O07] " << name << " ..." << std::endl;
  try {
    std::forward<Action>(action)();
  } catch (const std::exception& error) {
    throw std::runtime_error(std::string(name) + ": " + error.what());
  }
  std::cout << "[O07] " << name << " PASS" << std::endl;
}

int main() {
  try {
    run_scenario("Q physical observation modes", test_q_observation_modes);
    run_scenario("direct support observation modes", test_direct_support_modes_and_allocations);
    run_scenario("work limits and rollback", test_work_limit_boundaries_and_rollback_allocations);
    run_scenario("trace caps, sampling, and release", test_trace_caps_sampling_and_release);
    run_scenario("optional clock reads", test_optional_clock_reads);
    run_scenario("multi-alias generalized projection", test_multi_alias_generalized_projection);
    run_scenario("session retained summary", test_session_retained_summary);
    std::cout << "Excluded O07 runtime observation proposal passed\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
