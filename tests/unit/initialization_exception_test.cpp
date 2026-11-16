#include "crown/api/error.hpp"
#include "crown/io/ingest.hpp"
#include "crown/io/inspection.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/session.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <new>
#include <optional>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

// Keep allocation failures armed while unpublished runtime state and owned
// streams unwind. This executable owns its global-new replacement.
namespace {
thread_local std::ptrdiff_t fail_after = -1;
thread_local std::size_t allocation_count = 0;
thread_local std::size_t largest_allocation = 0;

[[gnu::noinline]] void* malloc_new(std::size_t bytes) {
  ++allocation_count;
  largest_allocation = std::max(largest_allocation, bytes);
  if (fail_after >= 0) {
    if (fail_after == 0) throw std::bad_alloc{};
    --fail_after;
  }
  if (auto* result = std::malloc(bytes == 0 ? 1 : bytes)) return result;
  throw std::bad_alloc{};
}

struct FaultScope {
  explicit FaultScope(std::ptrdiff_t point = -1) noexcept { fail_after = point; }
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

static_assert(std::is_nothrow_move_constructible_v<PhysicalRuntime>);
static_assert(std::is_nothrow_move_assignable_v<PhysicalRuntime>);
static_assert(std::is_nothrow_move_constructible_v<DeltaRuntime>);
static_assert(std::is_nothrow_move_assignable_v<DeltaRuntime>);
static_assert(std::is_nothrow_destructible_v<QuerySession>);

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

template <class Action>
void expect_error(Action&& action, std::string_view code) {
  try {
    std::forward<Action>(action)();
  } catch (const Error& failure) {
    check(failure.code() == code,
          "expected " + std::string(code) + ", got " + failure.code());
    return;
  }
  throw std::runtime_error("expected error code " + std::string(code));
}

Value n(std::int64_t value) { return value; }
Value s(std::string value) { return value; }

PhysicalPlan make_plan() {
  constexpr VariableId x{0}, z{1};
  const Catalog catalog{71, {{"E", {{"x", ScalarType::int64},
                                     {"z", ScalarType::int64},
                                     {"note", ScalarType::string}}}}};
  const Query query{
      {{"x", ScalarType::int64}, {"z", ScalarType::int64}},
      {{"forward", TableId{0}, {x, z, IgnoredColumn{}}},
       {"reverse", TableId{0}, {z, x, IgnoredColumn{}}},
       {"zero", TableId{0}, {x, n(0), IgnoredColumn{}}}},
      {{x, "x"}}, false};
  const FreeConnexTree tree{NodeId{0}, {
      {"projected", NodeKind::generalized, {x}, {NodeId{1}, NodeId{4}}, {}, {}},
      {"reciprocal", NodeKind::generalized, {x, z}, {NodeId{2}, NodeId{3}}, {}, {}},
      {"forward", NodeKind::native, {x, z}, {}, 0, {}},
      {"reverse", NodeKind::native, {x, z}, {}, 1, {}},
      {"zero", NodeKind::native, {x}, {}, 2, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

Database make_database() {
  return {{Relation{
      {n(1), n(2), s("one-two")},
      {n(2), n(0), s("two-zero")},
      {n(2), n(1), s("two-one")},
      {n(2), n(7), s("two-seven")},
      {n(3), n(0), s("three-zero")},
      {n(3), n(4), s("three-four")},
      {n(5), n(6), s("five-six")},
      {n(7), n(2), s("seven-two")},
      {n(9), n(8), s("nine-eight-a")},
      {n(9), n(8), s("nine-eight-b")}}}};
}

const Database& database() {
  static const Database value = make_database();
  return value;
}

bool same_database(const Database& left, const Database& right) {
  return left.tables == right.tables;
}

PhysicalRuntimeOptions physical_options() { return {}; }

DeltaOptions delta_options() {
  DeltaOptions result;
  result.mode = DeltaMode::delta;
  result.live_maintenance = LiveMaintenance::on_output;
  result.completion = DeltaCompletion::ordered_replay;
  return result;
}

BuildOptions build_options(BuildMethod method) {
  BuildOptions result;
  result.method = method;
  return result;
}

PhysicalSetUpdate prefix_update() {
  return {1, TableId{0}, SetOperation::insert,
          {n(8), n(9), s("prefix-row")}};
}

PhysicalSetUpdate suffix_update(std::uint64_t sequence) {
  return {sequence, TableId{0}, SetOperation::insert,
          {n(4), n(3), s("suffix-row")}};
}

std::set<Row> collect_results(PhysicalRuntime& runtime) {
  std::set<Row> result;
  auto cursor = runtime.results();
  while (auto tuple = cursor.next()) result.insert(crown::storage::export_row(tuple->values()));
  return result;
}

std::set<Row> collect_results(DeltaRuntime& runtime) {
  std::set<Row> result;
  auto cursor = runtime.results();
  while (auto tuple = cursor.next()) result.insert(crown::storage::export_row(tuple->values()));
  return result;
}

struct OutputImage {
  std::uint64_t ordinal;
  SetOperation operation;
  Row row;
  bool operator==(const OutputImage&) const = default;
};

std::vector<OutputImage> drain(DeltaRuntime::Epoch& epoch) {
  std::vector<OutputImage> result;
  while (auto output = epoch.next())
    result.push_back({output->ordinal, output->operation,
                      crown::storage::export_row(output->tuple.values())});
  return result;
}

struct SupportProbe {
  NodeId node;
  SupportRole role;
  Row row;
  SupportHandle handle;
  bool operator==(const SupportProbe&) const = default;
};

struct SourceProbe {
  TableId table;
  Row row;
  TupleHandle handle;
  bool operator==(const SourceProbe&) const = default;
};

struct PublicHandles {
  std::vector<SourceProbe> sources;
  std::vector<SupportProbe> support;
  bool operator==(const PublicHandles&) const = default;
};

std::vector<SupportProbe> support_handles(const SupportSnapshot& snapshot,
                                          PhysicalRuntime& runtime) {
  std::vector<SupportProbe> result;
  const auto add = [&](NodeId node, SupportRole role, const Row& row) {
    const auto handle = runtime.find_support(node, role, row);
    check(handle.has_value(), "initialized support row has no public handle");
    const auto stored = runtime.get_support(*handle);
    check(stored && stored->values() == row,
          "initialized support handle does not resolve to its row");
    result.push_back({node, role, row, *handle});
  };
  for (const auto& node : snapshot.nodes) {
    for (const auto& record : node.records)
      add(node.node, SupportRole::records, crown::storage::export_row(record.tuple.values()));
    for (const auto& row : node.survivors)
      add(node.node, SupportRole::survivors, crown::storage::export_row(row.values()));
    for (const auto& row : node.parent_keys)
      add(node.node, SupportRole::parent_support, crown::storage::export_row(row.key.values()));
    if (node.visible_keys) {
      for (const auto& row : *node.visible_keys)
        add(node.node, SupportRole::visible, crown::storage::export_row(row.key.values()));
    }
  }
  return result;
}

PublicHandles public_handles(PhysicalRuntime& runtime) {
  const auto snapshot = runtime.snapshot();
  PublicHandles result;
  for (std::size_t table = 0; table < snapshot.physical.tables.size(); ++table) {
    for (const auto& row : snapshot.physical.tables[table]) {
      const TableId id{table};
      const auto handle = runtime.find_source(id, row);
      check(handle.has_value(), "initialized source row has no public handle");
      const auto stored = runtime.get_source(id, *handle);
      check(stored && stored->values() == row,
            "initialized source handle does not resolve to its full row");
      result.sources.push_back({id, row, *handle});
    }
  }
  result.support = support_handles(snapshot.support, runtime);
  return result;
}

std::vector<SupportHandle> support_handles(const PhysicalSnapshot& snapshot) {
  std::vector<SupportHandle> result;
  for (const auto& node : snapshot.support.nodes) {
    for (const auto& record : node.records) result.push_back(record.handle);
    for (const auto& row : node.parent_keys) result.push_back(row.handle);
    if (node.visible_keys) {
      for (const auto& row : *node.visible_keys) result.push_back(row.handle);
    }
  }
  return result;
}

void check_public_handles(PhysicalRuntime& runtime,
                          const PublicHandles& expected) {
  check(public_handles(runtime) == expected,
        "physical initialization/rebuild changed a public source or support handle");
}

std::vector<SupportHandle> delta_support_handles(DeltaRuntime& runtime) {
  return support_handles(runtime.snapshot());
}

void check_physical_state(PhysicalRuntime& runtime,
                          const CanonicalPhysicalState& expected,
                          std::uint64_t sequence) {
  check(runtime.ready() && runtime.sequence() == sequence,
        "physical owner is not writer-ready at its committed sequence");
  check(runtime.canonical_state() == expected,
        "physical canonical state changed across initialization/rebuild failure");
  check(runtime.inspect_invariants().valid(),
        "physical initialized owner failed invariant inspection");
}

void check_delta_state(DeltaRuntime& runtime,
                       const CanonicalDeltaState& expected,
                       std::uint64_t sequence, DeltaMode mode) {
  check(runtime.ready() && runtime.sequence() == sequence &&
            runtime.mode() == mode && runtime.state() == DeltaState::ready,
        "delta owner readiness, mode, or sequence changed across rebuild");
  check(runtime.canonical_state() == expected,
        "delta canonical state changed across initialization/rebuild failure");
  check(runtime.inspect_invariants().valid(),
        "delta initialized owner failed invariant inspection");
}

struct SweepStats {
  std::size_t failure_points;
  std::size_t successful_allocation_calls;
};

// Calibrate the successful operation's allocation count, then inject each
// consecutive allocation failure until that same operation completes. Counts
// are observations of this path, not a uniform allocation or byte limit.
template <class Context, class Result, class Prepare, class Invoke,
          class CheckSuccess, class CheckFailure>
SweepStats sweep_allocations(std::string_view label, Prepare prepare,
                             Invoke invoke, CheckSuccess check_success,
                             CheckFailure check_failure) {
  auto calibration_context = prepare();
  allocation_count = 0;
  Result calibration = invoke(calibration_context);
  const std::size_t successful_allocation_calls = allocation_count;
  check_success(calibration_context, calibration);

  check(successful_allocation_calls <
            static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max()) - 2,
        std::string(label) + ": observed allocation count exceeds fault index range");
  const std::size_t limit = successful_allocation_calls + 2;
  std::size_t failures = 0;
  for (std::size_t point = 0; point <= limit; ++point) {
    auto context = prepare();
    std::optional<Result> result;
    bool failed = false;
    allocation_count = 0;
    {
      FaultScope fault(static_cast<std::ptrdiff_t>(point));
      try {
        result.emplace(invoke(context));
      } catch (const std::bad_alloc&) {
        failed = true;
        // Keep failure armed throughout destruction of all partially built
        // owners and any output produced before the exception.
        fault.forbid_allocations();
      }
    }
    const std::size_t attempt_allocation_calls = allocation_count;
    if (failed) {
      ++failures;
      check_failure(context);
      continue;
    }

    check(failures > 0,
          std::string(label) + ": allocation sweep injected no bad_alloc");
    check_success(context, *result);
    std::cout << label << " failure_points=" << failures
              << " successful_allocation_calls=" << successful_allocation_calls
              << " final_attempt_allocation_calls=" << attempt_allocation_calls << '\n';
    return {failures, successful_allocation_calls};
  }
  throw std::runtime_error(std::string(label) +
                           ": allocation sweep exceeded its observed path length");
}

void check_build_metrics(std::string_view label, const BuildMetrics& metrics,
                         BuildMethod method, bool expect_live) {
  check(metrics.work > 0 && metrics.source_rows > 0 &&
            metrics.adapter_visits > 0 && metrics.adapter_rejections > 0 &&
            metrics.derivation_changes > 0 && metrics.native_keys > 0 &&
            metrics.generalized_candidates > 0 && metrics.survivors > 0 &&
            metrics.parent_keys > 0,
        std::string(label) + ": expected source, adapter, and support build work was not observed");
  if (method == BuildMethod::direct) {
    check(metrics.replay_inputs == 0 && metrics.replay_events == 0,
          std::string(label) + ": direct build reported insertion-replay work");
  } else {
    check(metrics.replay_inputs > 0 && metrics.replay_events > 0 &&
              metrics.replay_work > 0,
          std::string(label) + ": insertion-replay path was not observed");
  }
  if (expect_live) {
    check(metrics.live_bootstrap_work > 0 && metrics.live_rows > 0 &&
              metrics.live_parent_rows > 0,
          std::string(label) + ": live bootstrap phase was not observed");
  }
  std::cout << label << " work=" << metrics.work
            << " source_rows=" << metrics.source_rows
            << " adapter_visits=" << metrics.adapter_visits
            << " adapter_rejections=" << metrics.adapter_rejections
            << " derivation_changes=" << metrics.derivation_changes
            << " native_keys=" << metrics.native_keys
            << " generalized_candidates=" << metrics.generalized_candidates
            << " replay_inputs=" << metrics.replay_inputs
            << " replay_events=" << metrics.replay_events
            << " live_bootstrap_work=" << metrics.live_bootstrap_work
            << " live_rows=" << metrics.live_rows << '\n';
}

struct PhysicalInitAttempt { PhysicalPlan plan; };

void sweep_physical_initialization(BuildMethod method) {
  const auto build = build_options(method);
  const auto prepare = [] { return PhysicalInitAttempt{make_plan()}; };
  const auto invoke = [&](PhysicalInitAttempt& context) {
    return PhysicalRuntime::initialize(std::move(context.plan), database(),
                                       physical_options(), build);
  };
  const auto success = [&](PhysicalInitAttempt&, PhysicalRuntime& runtime) {
    check(runtime.ready() && runtime.sequence() == 0,
          "physical initialization published a fabricated input sequence");
    check(runtime.canonical_state().support.sequence == 0,
          "physical initialization fabricated support progress");
    check(collect_results(runtime) == std::set<Row>{{n(2)}},
          "physical bootstrap did not build the projected self-join answer");
    check(runtime.inspect_invariants().valid(),
          "physical bootstrap invariant report is not valid");
    check_build_metrics(method == BuildMethod::direct
                            ? "physical.initialize.direct.metrics"
                            : "physical.initialize.replay.metrics",
                        runtime.initialization_metrics(), method, false);
    check(same_database(database(), make_database()),
          "physical initialization changed the caller's database");
  };
  const auto failure = [&](PhysicalInitAttempt&) {
    check(same_database(database(), make_database()),
          "failed physical initialization changed the caller's database");
  };
  const auto stats = sweep_allocations<PhysicalInitAttempt, PhysicalRuntime>(
      method == BuildMethod::direct ? "physical.initialize.direct"
                                    : "physical.initialize.replay",
      prepare, invoke, success, failure);
  check(stats.failure_points > 0,
        "physical initialization observed no allocation failure points");
}

struct DeltaInitAttempt { PhysicalPlan plan; };

void sweep_delta_initialization(BuildMethod method) {
  const auto build = build_options(method);
  const auto options = delta_options();
  const auto prepare = [] { return DeltaInitAttempt{make_plan()}; };
  const auto invoke = [&](DeltaInitAttempt& context) {
    return DeltaRuntime::initialize(std::move(context.plan), database(), options,
                                    build);
  };
  const auto success = [&](DeltaInitAttempt&, DeltaRuntime& runtime) {
    check(runtime.ready() && runtime.sequence() == 0 &&
              runtime.mode() == DeltaMode::delta &&
              runtime.state() == DeltaState::ready,
          "delta initialization published input progress or lost its requested mode");
    check(runtime.canonical_state().physical.sequence == 0 &&
              runtime.canonical_state().live &&
              runtime.canonical_state().live->sequence == 0,
          "delta initialization fabricated a committed sequence");
    check(collect_results(runtime) == std::set<Row>{{n(2)}},
          "delta bootstrap did not build the projected self-join answer");
    check(runtime.inspect_invariants().valid(),
          "delta bootstrap invariant report is not valid");
    check_build_metrics(method == BuildMethod::direct
                            ? "delta.initialize.direct.metrics"
                            : "delta.initialize.replay.metrics",
                        runtime.initialization_metrics(), method, true);
    check(same_database(database(), make_database()),
          "delta initialization changed the caller's database");
  };
  const auto failure = [&](DeltaInitAttempt&) {
    check(same_database(database(), make_database()),
          "failed delta initialization changed the caller's database");
  };
  const auto stats = sweep_allocations<DeltaInitAttempt, DeltaRuntime>(
      method == BuildMethod::direct ? "delta.initialize.direct.live"
                                    : "delta.initialize.replay.live",
      prepare, invoke, success, failure);
  check(stats.failure_points > 0,
        "delta initialization observed no allocation failure points");
}

struct PhysicalRebuildAttempt {
  PhysicalRuntime runtime;
  PhysicalEpoch held_epoch;
  CanonicalPhysicalState before;
  PublicHandles handles;
  SupportOwnerId owner;

  PhysicalRebuildAttempt()
      : runtime(PhysicalRuntime::initialize(make_plan(), database(),
                                            physical_options(),
                                            build_options(BuildMethod::direct))),
        held_epoch(runtime.apply(prefix_update())),
        before(runtime.canonical_state()), handles(public_handles(runtime)),
        owner(runtime.owner()) {}
};

void sweep_physical_rebuild(BuildMethod method) {
  const auto build = build_options(method);
  const auto prepare = [] { return PhysicalRebuildAttempt{}; };
  const auto invoke = [&](PhysicalRebuildAttempt& context) {
    return context.runtime.rebuilt(build);
  };
  const auto success = [&](PhysicalRebuildAttempt& context,
                           PhysicalRuntime& rebuilt) {
    check_physical_state(context.runtime, context.before, 1);
    check_public_handles(context.runtime, context.handles);
    check(context.runtime.owner() == context.owner,
          "successful rebuild replaced or mutated the original owner");
    check(rebuilt.owner() != context.owner && rebuilt.sequence() == 1 &&
              rebuilt.ready() && rebuilt.canonical_state() == context.before,
          "physical rebuild did not create an equivalent new owner at the old sequence");
    check(rebuilt.initialization_metrics().source_rows > 0,
          "physical rebuilt owner did not report its source build");
    check(context.held_epoch.input.source &&
              context.held_epoch.input.source->tuple().values() ==
                  prefix_update().values,
          "stored committed source pin did not survive physical rebuild");

    PhysicalRuntime clean = PhysicalRuntime::initialize(
        make_plan(), database(), physical_options(), build_options(method));
    static_cast<void>(clean.apply(prefix_update()));
    check(clean.canonical_state() == rebuilt.canonical_state(),
          "physical rebuilt state differs from a clean initialization and prefix");

    const auto suffix = suffix_update(2);
    static_cast<void>(rebuilt.apply(suffix));
    static_cast<void>(clean.apply(suffix));
    check(rebuilt.canonical_state() == clean.canonical_state() &&
              collect_results(rebuilt) == std::set<Row>{{n(2)}, {n(3)}} &&
              collect_results(clean) == collect_results(rebuilt),
          "physical rebuild did not accept a clean-oracle suffix update");
    check(rebuilt.sequence() == 2 && rebuilt.ready(),
          "physical suffix update did not advance exactly one real input");
    check_build_metrics(method == BuildMethod::direct
                            ? "physical.rebuild.direct.metrics"
                            : "physical.rebuild.replay.metrics",
                        rebuilt.initialization_metrics(), method, false);
  };
  const auto failure = [&](PhysicalRebuildAttempt& context) {
    check_physical_state(context.runtime, context.before, 1);
    check(context.runtime.owner() == context.owner,
          "failed physical rebuild changed the original owner ID");
    check_public_handles(context.runtime, context.handles);
    check(context.held_epoch.input.source &&
              context.held_epoch.input.source->tuple().values() ==
                  prefix_update().values,
          "failed physical rebuild released a previously stored source pin");
  };
  const auto stats = sweep_allocations<PhysicalRebuildAttempt, PhysicalRuntime>(
      method == BuildMethod::direct ? "physical.rebuild.direct"
                                    : "physical.rebuild.replay",
      prepare, invoke, success, failure);
  check(stats.failure_points > 0,
        "physical rebuild observed no allocation failure points");
}

bool same_delta_options(const DeltaOptions& left, const DeltaOptions& right) {
  return left.physical.work_limit == right.physical.work_limit &&
         left.physical.support.work_limit == right.physical.support.work_limit &&
         left.physical.support.support_limit == right.physical.support.support_limit &&
         left.physical.support.order == right.physical.support.order &&
         left.physical.support.capture_transitions ==
             right.physical.support.capture_transitions &&
         left.physical.derivation_limit == right.physical.derivation_limit &&
         left.mode == right.mode && left.view == right.view &&
         left.live_maintenance == right.live_maintenance &&
         left.completion == right.completion &&
         left.work_limit == right.work_limit &&
         left.cursor.work_limit == right.cursor.work_limit &&
         left.epoch_view.work_limit == right.epoch_view.work_limit &&
         left.spool_row_limit == right.spool_row_limit &&
         left.spool_byte_limit == right.spool_byte_limit;
}

struct DeltaRebuildAttempt {
  DeltaRuntime runtime;
  CanonicalDeltaState before;
  std::vector<SupportHandle> handles;
  DeltaOptions options;
  SupportOwnerId owner;

  DeltaRebuildAttempt()
      : runtime(DeltaRuntime::initialize(make_plan(), database(), delta_options(),
                                         build_options(BuildMethod::direct))),
        options(runtime.options()), owner(runtime.owner()) {
    auto prefix = runtime.apply(prefix_update());
    prefix.discard();
    before = runtime.canonical_state();
    handles = delta_support_handles(runtime);
  }
};

void sweep_delta_rebuild(BuildMethod method) {
  const auto build = build_options(method);
  const auto prepare = [] { return DeltaRebuildAttempt{}; };
  const auto invoke = [&](DeltaRebuildAttempt& context) {
    return context.runtime.rebuilt(build);
  };
  const auto success = [&](DeltaRebuildAttempt& context, DeltaRuntime& rebuilt) {
    check_delta_state(context.runtime, context.before, 1, DeltaMode::delta);
    check(context.runtime.owner() == context.owner &&
              same_delta_options(context.runtime.options(), context.options),
          "successful delta rebuild changed the original owner or options");
    check(rebuilt.owner() != context.owner && rebuilt.sequence() == 1 &&
              rebuilt.mode() == DeltaMode::delta && rebuilt.ready() &&
              rebuilt.canonical_state() == context.before &&
              same_delta_options(rebuilt.options(), context.options),
          "delta rebuild did not preserve the old state, mode, sequence, and options");
    check(delta_support_handles(context.runtime) == context.handles,
          "successful delta rebuild changed original support handles");
    check_build_metrics(method == BuildMethod::direct
                            ? "delta.rebuild.direct.metrics"
                            : "delta.rebuild.replay.metrics",
                        rebuilt.initialization_metrics(), method, true);

    DeltaRuntime clean = DeltaRuntime::initialize(
        make_plan(), database(), context.options, build_options(method));
    auto prefix = clean.apply(prefix_update());
    prefix.discard();
    check(clean.canonical_state() == rebuilt.canonical_state(),
          "delta rebuilt state differs from a clean initialization and prefix");

    const auto suffix = suffix_update(2);
    auto output = rebuilt.apply(suffix);
    auto clean_output = clean.apply(suffix);
    const auto rebuilt_rows = drain(output);
    const auto clean_rows = drain(clean_output);
    check(rebuilt_rows == clean_rows &&
              rebuilt_rows == std::vector<OutputImage>{{1, SetOperation::insert,
                                                         {n(3)}}},
          "delta rebuild suffix output differs from a clean oracle update");
    check(rebuilt.canonical_state() == clean.canonical_state() &&
              rebuilt.sequence() == 2 && rebuilt.ready() &&
              collect_results(rebuilt) == std::set<Row>{{n(2)}, {n(3)}},
          "delta rebuild suffix did not preserve the clean result and sequence");
  };
  const auto failure = [&](DeltaRebuildAttempt& context) {
    check_delta_state(context.runtime, context.before, 1, DeltaMode::delta);
    check(context.runtime.owner() == context.owner &&
              same_delta_options(context.runtime.options(), context.options),
          "failed delta rebuild changed the old owner, mode, or options");
    check(delta_support_handles(context.runtime) == context.handles,
          "failed delta rebuild changed old support handles");
  };
  const auto stats = sweep_allocations<DeltaRebuildAttempt, DeltaRuntime>(
      method == BuildMethod::direct ? "delta.rebuild.direct.live"
                                    : "delta.rebuild.replay.live",
      prepare, invoke, success, failure);
  check(stats.failure_points > 0,
        "delta rebuild observed no allocation failure points");
}

void check_late_build_work_failures() {
  for (const auto method : {BuildMethod::direct, BuildMethod::insertion_replay}) {
    const auto baseline = PhysicalRuntime::initialize(
        make_plan(), database(), physical_options(), build_options(method));
    const auto physical_work = baseline.initialization_metrics().work;
    check(physical_work > 1, "physical build fixture has too little cumulative work");
    auto one_short = build_options(method);
    one_short.work_limit = physical_work - 1;
    expect_error([&] {
      static_cast<void>(PhysicalRuntime::initialize(
          make_plan(), database(), physical_options(), one_short));
    }, "resource_limit");
    check(same_database(database(), make_database()),
          "late physical build-work failure changed caller data");

    const auto delta = DeltaRuntime::initialize(
        make_plan(), database(), delta_options(), build_options(method));
    const auto total_work = delta.initialization_metrics().work;
    check(total_work > delta.initialization_metrics().live_bootstrap_work + 1,
          "delta build fixture did not separate physical and live build work");
    auto live_one_short = build_options(method);
    live_one_short.work_limit = total_work - 1;
    expect_error([&] {
      static_cast<void>(DeltaRuntime::initialize(
          make_plan(), database(), delta_options(), live_one_short));
    }, "resource_limit");
    check(same_database(database(), make_database()),
          "late delta/live build-work failure changed caller data");
    std::cout << (method == BuildMethod::direct ? "build_work.direct" :
                                                        "build_work.replay")
              << " physical_total=" << physical_work
              << " delta_live_total=" << total_work
              << " live_phase=" << delta.initialization_metrics().live_bootstrap_work
              << " rejected_at=" << total_work - 1 << '\n';
  }
}

PhysicalPlan make_constant_unused_source_plan(const Catalog& catalog) {
  const Query query{{}, {}, {}, false};
  const FreeConnexTree tree{};
  return planner::lower_tree(catalog, query, tree);
}

Database constrained_unused_database() {
  Relation rows;
  for (std::int64_t value = 0; value < 64; ++value)
    rows.insert(Row{n(value)});
  return {{std::move(rows)}};
}

void check_constraint_projection_work_budgets() {
  auto source = constrained_unused_database();
  Table table{"unused", {{"id", ScalarType::int64}}};
  for (std::size_t index = 0; index < 12; ++index) {
    table.constraints.push_back(UniqueConstraint{
        "unique_projection_" + std::to_string(index), {ColumnId{0}},
        ConstraintStatus::enforced});
  }
  const Catalog catalog{74, {std::move(table)}};
  auto plan = make_constant_unused_source_plan(catalog);
  auto unlimited = PhysicalRuntime::initialize(plan, source);
  check(unlimited.ready() && unlimited.sequence() == 0 &&
            unlimited.snapshot().physical.tables == source.tables,
        "unlimited unused-source build rejected its valid unique constraints");

  auto limited_build = build_options(BuildMethod::direct);
  limited_build.work_limit = 500;
  expect_error([&] {
    static_cast<void>(PhysicalRuntime::initialize(
        plan, source, physical_options(), limited_build));
  }, "resource_limit");

  auto stopped = unlimited.inspect_invariants(InspectionOptions{500, 128});
  check(!stopped.complete && !stopped.valid() && stopped.work <= 500,
        "bounded inspection did not report an incomplete, invalid result");
  check(unlimited.inspect_invariants().valid(),
        "unlimited inspection failed repeated enforced-key projections");
  check(same_database(source, constrained_unused_database()),
        "constraint work-limit checks changed the caller's unused source rows");
  std::cout << "constraint_projection_work rows=" << source.tables.front().size()
            << " repeated_unique_constraints=" << catalog.tables.front().constraints.size()
            << " cap=500 incomplete_report_work=" << stopped.work << '\n';
}

PhysicalPlan make_long_string_plan();

void check_rebuild_budget_precedes_large_source_copy() {
  const std::string payload(32768, 'r');
  const Database source{{Relation{{n(1), s(payload)}}}};
  auto runtime = PhysicalRuntime::initialize(make_long_string_plan(), source);
  const auto before = runtime.canonical_state();
  const auto handle = runtime.find_source(TableId{0}, {n(1), s(payload)});
  check(handle.has_value(), "large-string source row has no public handle");
  BuildOptions no_rebuild_work;
  no_rebuild_work.work_limit = 0;
  largest_allocation = 0;
  expect_error([&] { static_cast<void>(runtime.rebuilt(no_rebuild_work)); },
               "resource_limit");
  const auto attempted_largest_allocation = largest_allocation;
  check(attempted_largest_allocation < payload.size() / 2,
        "zero-work rebuild allocated a source-payload-sized copy before rejecting");
  check(runtime.ready() && runtime.sequence() == 0 &&
            runtime.canonical_state() == before &&
            runtime.find_source(TableId{0}, {n(1), s(payload)}) == handle,
        "zero-work rebuild rejection changed its original owner or source handle");
  const auto stored = runtime.get_source(TableId{0}, *handle);
  check(stored && stored->values() == Row{n(1), s(payload)} &&
            same_database(source, Database{{Relation{{n(1), s(payload)}}}}),
        "zero-work rebuild rejection changed source or caller-owned values");
  std::cout << "rebuild_budget.zero_work largest_allocation="
            << attempted_largest_allocation
            << " payload_bytes=" << payload.size() << '\n';
}

void check_exact_support_and_derivation_caps() {
  for (const auto method : {BuildMethod::direct, BuildMethod::insertion_replay}) {
    auto support_options = physical_options();
    support_options.support.support_limit = 1;
    expect_error([&] {
      static_cast<void>(PhysicalRuntime::initialize(
          make_plan(), database(), support_options, build_options(method)));
    }, "support_overflow");

    auto derivation_options = physical_options();
    derivation_options.derivation_limit = 1;
    expect_error([&] {
      static_cast<void>(PhysicalRuntime::initialize(
          make_plan(), database(), derivation_options, build_options(method)));
    }, "derivation_overflow");
    check(same_database(database(), make_database()),
          "support or derivation cap failure changed the caller's database");
  }
}

void check_update_limits_are_separate_from_build_limits() {
  for (const auto method : {BuildMethod::direct, BuildMethod::insertion_replay}) {
    auto physical_config = physical_options();
    physical_config.work_limit = 0;
    physical_config.support.work_limit = 0;
    auto physical = PhysicalRuntime::initialize(
        make_plan(), database(), physical_config,
        BuildOptions{method, std::nullopt});
    check(physical.ready() && physical.sequence() == 0 &&
              physical.options().work_limit == 0 &&
              physical.options().support.work_limit == 0,
          "ordinary physical update caps were incorrectly used as build caps");
    const auto physical_before = physical.canonical_state();
    expect_error([&] { static_cast<void>(physical.apply(prefix_update())); },
                 "resource_limit");
    check(physical.ready() && physical.sequence() == 0 &&
              physical.canonical_state() == physical_before &&
              physical.options().work_limit == 0 &&
              physical.options().support.work_limit == 0,
          "physical initialization changed ordinary update limits or state");

    auto delta_config = delta_options();
    delta_config.physical.work_limit = 0;
    delta_config.physical.support.work_limit = 0;
    delta_config.work_limit = 0;
    delta_config.cursor.work_limit = 0;
    delta_config.epoch_view.work_limit = 0;
    auto delta = DeltaRuntime::initialize(
        make_plan(), database(), delta_config,
        BuildOptions{method, std::nullopt});
    check(delta.ready() && delta.sequence() == 0 && delta.mode() == DeltaMode::delta &&
              same_delta_options(delta.options(), delta_config),
          "delta build limits replaced ordinary per-update work limits");
    const auto delta_before = delta.canonical_state();
    expect_error([&] { static_cast<void>(delta.apply(prefix_update())); },
                 "resource_limit");
    check(delta.ready() && delta.sequence() == 0 &&
              delta.canonical_state() == delta_before &&
              same_delta_options(delta.options(), delta_config),
          "delta initialization did not restore caller update limits");
  }
}

PhysicalPlan make_cyclic_fk_plan() {
  Table a{"A", {{"id", ScalarType::int64}, {"b_id", ScalarType::int64}}};
  a.constraints.push_back(UniqueConstraint{
      "A_pk", {ColumnId{0}}, ConstraintStatus::enforced});
  a.constraints.push_back(ForeignKeyConstraint{
      "A_to_B", {ColumnId{1}}, TableId{1}, {ColumnId{0}},
      ConstraintStatus::enforced});
  Table b{"B", {{"id", ScalarType::int64}, {"a_id", ScalarType::int64}}};
  b.constraints.push_back(UniqueConstraint{
      "B_pk", {ColumnId{0}}, ConstraintStatus::enforced});
  b.constraints.push_back(ForeignKeyConstraint{
      "B_to_A", {ColumnId{1}}, TableId{0}, {ColumnId{0}},
      ConstraintStatus::enforced});
  const Catalog catalog{72, {std::move(a), std::move(b)}};
  const Query query{{{"id", ScalarType::int64}},
                    {{"only_a", TableId{0}, {VariableId{0}, IgnoredColumn{}}}},
                    {{VariableId{0}, "id"}}, false};
  const FreeConnexTree tree{NodeId{0}, {
      {"A", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

Database cyclic_fk_database() {
  return {{Relation{{n(1), n(10)}}, Relation{{n(10), n(1)}}}};
}

void check_complete_cyclic_foreign_key_bootstrap() {
  const auto original = cyclic_fk_database();
  for (const auto method : {BuildMethod::direct, BuildMethod::insertion_replay}) {
    PhysicalRuntime empty(make_cyclic_fk_plan());
    expect_error([&] {
      static_cast<void>(empty.apply(
          {1, TableId{0}, SetOperation::insert, {n(1), n(10)}}));
    }, "constraint_violation");
    expect_error([&] {
      static_cast<void>(empty.apply(
          {1, TableId{1}, SetOperation::insert, {n(10), n(1)}}));
    }, "constraint_violation");
    check(empty.ready() && empty.sequence() == 0 &&
              empty.canonical_state().sources ==
                  std::vector<Relation>{Relation{}, Relation{}},
          "failed cyclic-FK prefix insert changed the empty owner");

    auto initialized = PhysicalRuntime::initialize(
        make_cyclic_fk_plan(), original, physical_options(), build_options(method));
    check(initialized.ready() && initialized.sequence() == 0 &&
              initialized.snapshot().physical.tables == original.tables &&
              initialized.initialization_metrics().constraint_rows > 0 &&
              initialized.inspect_invariants().valid(),
          "complete cyclic foreign-key snapshot did not initialize atomically");
  }
  check(same_database(original, cyclic_fk_database()),
        "cyclic-FK initialization changed the caller's database");
}

class OwnedStream final : public std::istringstream {
 public:
  OwnedStream(std::string bytes, bool* destroyed)
      : std::istringstream(std::move(bytes)), destroyed_(destroyed) {
    if (destroyed_) *destroyed_ = false;
  }
  ~OwnedStream() override {
    if (destroyed_) *destroyed_ = true;
  }

 private:
  bool* destroyed_;
};

struct SessionInitAttempt {
  PhysicalPlan plan;
  bool stream_destroyed = false;
  std::unique_ptr<std::istream> input;

  explicit SessionInitAttempt(const std::string& bytes)
      : plan(make_plan()),
        input(std::make_unique<OwnedStream>(bytes, &stream_destroyed)) {}
};

std::string suffix_input() {
  const auto plan = make_plan();
  const io::InputEvent input{suffix_update(1),
                             io::SourcePosition{"init-source", 41}};
  return io::write_input_json(input, plan.source_catalog()) + "\n";
}

std::set<Row> snapshot_rows(const SessionSnapshot& snapshot) {
  std::set<Row> result;
  for (const auto& row : snapshot.rows) result.insert(crown::storage::export_row(row.values()));
  return result;
}

void sweep_initialized_session_creation(BuildMethod method) {
  const std::string bytes = suffix_input();
  auto options = SessionOptions{};
  options.delta = delta_options();
  const auto build = build_options(method);
  const auto prepare = [&] { return SessionInitAttempt{bytes}; };
  const auto invoke = [&](SessionInitAttempt& context) {
    return QuerySession::create(std::move(context.plan), database(),
                                std::move(context.input), options, build);
  };
  const auto success = [&](SessionInitAttempt& context,
                           QuerySession::Owner& session) {
    check(session != nullptr && !context.stream_destroyed,
          "successful initialized session did not retain its owned stream");
    const auto status = session->status();
    check(status.state == SessionState::created &&
              status.phase == SessionPhase::ready &&
              status.committed_sequence == 0 && !status.input_failed &&
              !status.end_of_input && !status.pending_sequence &&
              status.output_remaining == 0 &&
              session->progress() == io::InputProgress{},
          "initialized session fabricated accepted input progress or output");
    auto saved = session->snapshot();
    check(saved.sequence == 0 && saved.progress == io::InputProgress{} &&
              snapshot_rows(saved) == std::set<Row>{{n(2)}},
          "initialized session snapshot did not contain only epoch-zero query state");
    check(same_database(database(), make_database()),
          "initialized session changed the caller's database");
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      session.reset();
    }
    check(context.stream_destroyed,
          "initialized session teardown did not release its owned stream");
    check(snapshot_rows(saved) == std::set<Row>{{n(2)}},
          "owning session snapshot did not survive session destruction");
  };
  const auto failure = [&](SessionInitAttempt& context) {
    check(context.stream_destroyed,
          "failed initialized session construction did not destroy its owned stream");
    check(same_database(database(), make_database()),
          "failed initialized session construction changed caller data");
  };
  static_cast<void>(sweep_allocations<SessionInitAttempt,
                                      QuerySession::Owner>(
      method == BuildMethod::direct ? "session.initialize.direct"
                                    : "session.initialize.replay",
      prepare, invoke, success, failure));
}

void check_rebuild_barriers() {
  PhysicalRuntime physical = PhysicalRuntime::initialize(
      make_plan(), database(), physical_options());
  {
    auto pending = physical.prepare(prefix_update());
    expect_error([&] { static_cast<void>(physical.rebuilt()); }, "runtime_busy");
    pending.rollback();
  }
  {
    auto cursor = physical.results();
    expect_error([&] { static_cast<void>(physical.rebuilt()); }, "runtime_busy");
    cursor.cancel();
  }
  check(physical.ready() && physical.sequence() == 0,
        "physical rebuild barrier test failed to return to a ready owner");

  DeltaRuntime delta = DeltaRuntime::initialize(
      make_plan(), database(), delta_options());
  {
    auto pending = delta.begin(prefix_update());
    expect_error([&] { static_cast<void>(delta.rebuilt()); }, "runtime_busy");
    pending.rollback();
  }
  {
    auto cursor = delta.results();
    expect_error([&] { static_cast<void>(delta.rebuilt()); }, "runtime_busy");
    cursor.cancel();
  }
  auto output = delta.apply(suffix_update(1));
  check(output.remaining() > 0,
        "delta rebuild barrier fixture produced no unread output");
  expect_error([&] { static_cast<void>(delta.rebuilt()); }, "runtime_busy");
  output.discard();
  auto rebuilt = delta.rebuilt();
  check(rebuilt.ready() && rebuilt.mode() == DeltaMode::delta &&
            rebuilt.sequence() == 1 && delta.sequence() == 1,
        "delta rebuild did not work after pending/read/output barriers closed");
}

void check_no_allocation_moves_and_pin_cleanup() {
  const Row retained_source_row = prefix_update().values;
  std::optional<PhysicalRuntime> physical;
  physical.emplace(PhysicalRuntime::initialize(make_plan(), database()));
  std::optional<PhysicalEpoch> pin;
  pin.emplace(physical->apply(prefix_update()));
  check(pin->input.source &&
            pin->input.source->tuple().values() == retained_source_row,
        "physical pin fixture did not retain its committed source row");
  bool pin_survived_owner_destruction = false;
  {
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    std::optional<PhysicalRuntime> moved;
    moved.emplace(std::move(*physical));
    physical.reset();
    moved.reset();
    pin_survived_owner_destruction = pin->input.source &&
        pin->input.source->tuple().values() == retained_source_row;
    pin.reset();
  }
  check(pin_survived_owner_destruction,
        "stored source pin did not survive final physical owner destruction");

  std::optional<PhysicalRuntime> left;
  std::optional<PhysicalRuntime> right;
  left.emplace(PhysicalRuntime::initialize(make_plan(), database()));
  right.emplace(PhysicalRuntime::initialize(make_plan(), database()));
  {
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    *left = std::move(*right);
    right.reset();
    left.reset();
  }

  std::optional<DeltaRuntime> delta;
  delta.emplace(DeltaRuntime::initialize(make_plan(), database(), delta_options()));
  std::optional<DeltaRuntime::Epoch> unread;
  unread.emplace(delta->apply(suffix_update(1)));
  check(unread->remaining() > 0,
        "delta no-allocation teardown fixture produced no output");
  std::optional<SignedResult> stored;
  {
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    std::optional<DeltaRuntime> moved;
    moved.emplace(std::move(*delta));
    delta.reset();
    moved.reset();
    stored = unread->next();
    unread.reset();
  }
  check(stored && stored->operation == SetOperation::insert &&
            stored->tuple.values() == Row{n(3)},
        "stored delta output did not survive final-owner and pin cleanup");

  std::optional<DeltaRuntime> delta_left;
  std::optional<DeltaRuntime> delta_right;
  delta_left.emplace(DeltaRuntime::initialize(make_plan(), database(), delta_options()));
  delta_right.emplace(DeltaRuntime::initialize(make_plan(), database(), delta_options()));
  {
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    *delta_left = std::move(*delta_right);
    delta_right.reset();
    delta_left.reset();
  }
}

struct WriterAttempt {};

template <class Writer>
void sweep_writer_allocations(std::string_view label, Writer writer,
                              std::string_view expected_marker) {
  const auto prepare = [] { return WriterAttempt{}; };
  const auto invoke = [&](WriterAttempt&) { return writer(); };
  const auto success = [&](WriterAttempt&, std::string& output) {
    check(output.find(expected_marker) != std::string::npos,
          std::string(label) + ": writer output lacks its expected versioned marker");
  };
  const auto failure = [&](WriterAttempt&) {};
  static_cast<void>(sweep_allocations<WriterAttempt, std::string>(
      label, prepare, invoke, success, failure));
}

PhysicalPlan make_long_string_plan() {
  const Catalog catalog{73, {{"L", {{"id", ScalarType::int64},
                                     {"payload", ScalarType::string}}}}};
  const Query query{{{"id", ScalarType::int64}},
                    {{"l", TableId{0},
                      {VariableId{0}, IgnoredColumn{}}}},
                    {{VariableId{0}, "id"}}, false};
  const FreeConnexTree tree{NodeId{0}, {
      {"l", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

void check_inspection_writer_failures_and_byte_bound() {
  auto physical = PhysicalRuntime::initialize(make_plan(), database());
  auto delta = DeltaRuntime::initialize(make_plan(), database(), delta_options());
  const auto physical_state = physical.canonical_state();
  const auto delta_state = delta.canonical_state();
  const auto report = physical.inspect_invariants();
  check(report.valid(), "writer fixture invariant report is not valid");
  sweep_writer_allocations("inspection.writer.physical", [&] {
    return io::write_runtime_state(physical_state);
  }, "\"kind\":\"physical\"");
  sweep_writer_allocations("inspection.writer.delta", [&] {
    return io::write_runtime_state(delta_state);
  }, "\"kind\":\"delta\"");
  sweep_writer_allocations("inspection.writer.report", [&] {
    return io::write_invariant_report(report);
  }, "\"valid\":true");

  const std::string payload(32768, 'p');
  const Database long_database{{Relation{{n(1), s(payload)}}}};
  auto long_runtime = PhysicalRuntime::initialize(
      make_long_string_plan(), long_database);
  const auto long_state = long_runtime.canonical_state();
  const auto full = io::write_runtime_state(long_state);
  const auto position = full.find(payload);
  check(position != std::string::npos && position < payload.size() / 4,
        "long-string byte-limit fixture has an unexpectedly large prefix");
  const std::size_t limit = position + payload.size() / 2;
  largest_allocation = 0;
  expect_error([&] {
    static_cast<void>(io::write_runtime_state(long_state, limit));
  }, "resource_limit");
  check(largest_allocation < payload.size() / 2,
        "byte-bounded writer allocated a payload-sized buffer before rejecting");
  std::cout << "inspection.writer.long_string_bytes=" << payload.size()
            << " encoded_prefix=" << position
            << " byte_limit=" << limit
            << " largest_allocation=" << largest_allocation << '\n';
}

void check_no_fabricated_input_and_suffix_equivalence() {
  auto physical = PhysicalRuntime::initialize(make_plan(), database());
  check(physical.sequence() == 0 && physical.ready() &&
            physical.canonical_state().sequence == 0 &&
            collect_results(physical) == std::set<Row>{{n(2)}},
        "physical initialization did not keep sequence zero and built results");

  auto delta = DeltaRuntime::initialize(make_plan(), database(), delta_options());
  check(delta.sequence() == 0 && delta.ready() &&
            delta.mode() == DeltaMode::delta &&
            delta.canonical_state().physical.sequence == 0 &&
            delta.canonical_state().live &&
            delta.canonical_state().live->sequence == 0 &&
            collect_results(delta) == std::set<Row>{{n(2)}},
        "delta initialization did not keep physical/live progress at zero");

  const auto physical_before = physical.canonical_state();
  static_cast<void>(physical.apply(prefix_update()));
  auto clean_physical = PhysicalRuntime::initialize(make_plan(), database());
  static_cast<void>(clean_physical.apply(prefix_update()));
  check(physical.sequence() == 1 &&
            physical.canonical_state() == clean_physical.canonical_state() &&
            physical_before.sequence == 0,
        "first real physical input did not advance from initialization sequence zero");

  const auto delta_before = delta.canonical_state();
  auto prefix = delta.apply(prefix_update());
  prefix.discard();
  auto clean_delta = DeltaRuntime::initialize(make_plan(), database(), delta_options());
  auto clean_prefix = clean_delta.apply(prefix_update());
  clean_prefix.discard();
  check(delta.sequence() == 1 &&
            delta.canonical_state() == clean_delta.canonical_state() &&
            delta_before.physical.sequence == 0,
        "first real delta input did not advance from initialization sequence zero");
}

}  // namespace

int main() {
  try {
    const auto original = database();
    sweep_physical_initialization(BuildMethod::direct);
    sweep_physical_initialization(BuildMethod::insertion_replay);
    sweep_delta_initialization(BuildMethod::direct);
    sweep_delta_initialization(BuildMethod::insertion_replay);

    sweep_physical_rebuild(BuildMethod::direct);
    sweep_physical_rebuild(BuildMethod::insertion_replay);
    sweep_delta_rebuild(BuildMethod::direct);
    sweep_delta_rebuild(BuildMethod::insertion_replay);

    check_late_build_work_failures();
    check_exact_support_and_derivation_caps();
    check_constraint_projection_work_budgets();
    check_rebuild_budget_precedes_large_source_copy();
    check_update_limits_are_separate_from_build_limits();
    check_complete_cyclic_foreign_key_bootstrap();
    check_no_fabricated_input_and_suffix_equivalence();
    sweep_initialized_session_creation(BuildMethod::direct);
    sweep_initialized_session_creation(BuildMethod::insertion_replay);
    check_rebuild_barriers();
    check_no_allocation_moves_and_pin_cleanup();
    check_inspection_writer_failures_and_byte_bound();

    check(same_database(database(), original),
          "initialization/rebuild/session tests changed the caller's database");
    std::cout << "initialization, rebuild, session, and diagnostic writer exception checks passed\n";
  } catch (const std::exception& failure) {
    std::cerr << "initialization exception test failed: " << failure.what() << '\n';
    return 1;
  }
}
