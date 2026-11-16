#include "crown/api/error.hpp"
#include "crown/io/ingest.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/delta.hpp"
#include "crown/runtime/observation.hpp"
#include "crown/runtime/physical.hpp"
#include "crown/runtime/session.hpp"
#include "crown/runtime/support.hpp"
#include "evaluator.hpp"

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <new>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>

namespace allocation_probe {
constexpr std::size_t no_failure = std::numeric_limits<std::size_t>::max();
std::atomic<bool> active{false};
std::atomic<std::size_t> count{0};
std::atomic<std::size_t> fail_at{no_failure};
std::atomic<bool> injected{false};
std::atomic<std::size_t> injected_faults{0};

void note() {
  if (!active.load(std::memory_order_relaxed)) return;
  const auto index = count.fetch_add(1, std::memory_order_relaxed);
  if (index >= fail_at.load(std::memory_order_relaxed)) {
    injected.store(true, std::memory_order_relaxed);
    injected_faults.fetch_add(1, std::memory_order_relaxed);
    throw std::bad_alloc{};
  }
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
void measure(Action&& action, std::size_t fail_index,
             std::size_t& allocations, bool& failure_injected,
             std::size_t& failures) {
  count.store(0, std::memory_order_relaxed);
  fail_at.store(fail_index, std::memory_order_relaxed);
  injected.store(false, std::memory_order_relaxed);
  injected_faults.store(0, std::memory_order_relaxed);
  active.store(true, std::memory_order_relaxed);
  try {
    std::forward<Action>(action)();
  } catch (...) {
    active.store(false, std::memory_order_relaxed);
    allocations = count.load(std::memory_order_relaxed);
    failure_injected = injected.load(std::memory_order_relaxed);
    failures = injected_faults.load(std::memory_order_relaxed);
    throw;
  }
  active.store(false, std::memory_order_relaxed);
  allocations = count.load(std::memory_order_relaxed);
  failure_injected = injected.load(std::memory_order_relaxed);
  failures = injected_faults.load(std::memory_order_relaxed);
}

void disarm() noexcept {
  active.store(false, std::memory_order_relaxed);
  fail_at.store(no_failure, std::memory_order_relaxed);
  injected.store(false, std::memory_order_relaxed);
  injected_faults.store(0, std::memory_order_relaxed);
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

static_assert(std::is_trivially_copyable_v<ObservationConfiguration>);
static_assert(std::is_nothrow_copy_constructible_v<ObservationSnapshot>);
static_assert(std::is_nothrow_copy_assignable_v<ObservationSnapshot>);
static_assert(std::is_nothrow_copy_constructible_v<ObservationSummary>);
static_assert(std::is_nothrow_copy_assignable_v<ObservationSummary>);

std::uint64_t clock_reads = 0;
std::uint64_t fake_clock() noexcept { return ++clock_reads; }

void check(bool condition, std::string_view message) {
  if (!condition) throw std::runtime_error(std::string(message));
}

template <class Action>
void expect_error(std::string_view code, Action&& action, std::string_view label) {
  bool caught = false;
  try {
    std::forward<Action>(action)();
  } catch (const Error& error) {
    caught = true;
    check(error.code() == code, label);
  }
  check(caught, label);
}

Value integer(std::int64_t value) { return Value{value}; }
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
      {{VariableId{0}, "x"}}, false,
  };
  PhysicalPlan plan;
  Database initial;

  QFixture()
      : plan(planner::lower_tree(catalog, query, FreeConnexTree{
            NodeId{0},
            {{"R", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{1}}, 0, {}},
             {"S", NodeKind::native, {VariableId{1}}, {}, 1, {}}},
            {}, {},
        })) {
    initial.tables.resize(2);
    initial.tables[0].insert(edge(7, 9));
  }

  [[nodiscard]] Database with_match() const {
    auto result = initial;
    result.tables[1].insert(row(9));
    return result;
  }
};

ObservationOptions observation_options(ObservationMode mode) {
  ObservationOptions result;
  result.mode = mode;
  result.trace_capacity = 19;
  result.sample_period = 3;
  result.sample_offset = 1;
  result.trace_timings = false;
  return result;
}

DeltaOptions exact_options(ObservationMode mode = ObservationMode::trace) {
  DeltaOptions result;
  result.physical.support.work_limit = std::uint64_t{713};
  result.physical.support.support_limit = 911;
  result.physical.support.order = PropagationOrder::lifo;
  result.physical.support.capture_transitions = true;
  result.physical.support.observation = observation_options(mode);
  result.physical.work_limit = std::nullopt;
  result.physical.derivation_limit = 1409;
  result.mode = DeltaMode::maintenance;
  result.view = ResultView::core;
  result.live_maintenance = LiveMaintenance::eager;
  result.completion = DeltaCompletion::automatic;
  result.work_limit = std::uint64_t{1601};
  result.cursor.work_limit = std::nullopt;
  result.epoch_view.work_limit = std::uint64_t{1801};
  result.spool_row_limit = 1901;
  result.spool_byte_limit = 2003;
  return result;
}

bool same_options(const DeltaOptions& a, const DeltaOptions& b) {
  return a.physical.support.work_limit == b.physical.support.work_limit &&
      a.physical.support.support_limit == b.physical.support.support_limit &&
      a.physical.support.order == b.physical.support.order &&
      a.physical.support.capture_transitions == b.physical.support.capture_transitions &&
      a.physical.support.observation == b.physical.support.observation &&
      a.physical.work_limit == b.physical.work_limit &&
      a.physical.derivation_limit == b.physical.derivation_limit &&
      a.mode == b.mode && a.view == b.view &&
      a.live_maintenance == b.live_maintenance && a.completion == b.completion &&
      a.work_limit == b.work_limit && a.cursor.work_limit == b.cursor.work_limit &&
      a.epoch_view.work_limit == b.epoch_view.work_limit &&
      a.spool_row_limit == b.spool_row_limit &&
      a.spool_byte_limit == b.spool_byte_limit;
}

void check_configuration(const ObservationConfiguration& actual,
                         const DeltaOptions& requested, DeltaMode resolved_mode,
                         DeltaCompletion resolved_completion, std::uint64_t owner,
                         std::uint64_t generation, bool saturated,
                         std::size_t factors = 1) {
  check(ObservationConfiguration::format_version() == 1,
        "configuration format version must equal literal 1");
  check(same_options(actual.requested_options(), requested),
        "configuration did not reconstruct every requested nested option");
  check(actual.mode() == resolved_mode,
        "configuration resolved mode differs from the expected mode");
  check(actual.live_maintenance() == requested.live_maintenance,
        "configuration live-maintenance policy differs from request");
  check(actual.completion() == resolved_completion,
        "configuration actual completion differs from its independent resolution");
  check(actual.view() == requested.view, "configuration result view differs from request");
  check(actual.support_owner() == owner && owner != 0,
        "configuration owner differs from the physical runtime owner");
  check(actual.generation() == generation &&
        actual.generation_saturated() == saturated,
        "configuration generation or saturation differs from literal expectation");
  check(actual.query_factors() == factors,
        "configuration factor count differs from literal Q(x)=R(x,y),S(y) count");
}

Relation drain(SupportRuntime::ResultCursor cursor) {
  Relation result;
  while (auto tuple = cursor.next())
    check(result.insert(crown::storage::export_row(tuple->values())).second, "runtime emitted a duplicate set row");
  return result;
}

Relation reference_result(const QFixture& fixture, const Database& database) {
  return reference::evaluate(fixture.catalog, fixture.query, database);
}

void check_runtime_result(DeltaRuntime& runtime, const QFixture& fixture,
                          const Database& database, std::string_view message) {
  check(drain(runtime.results()) == reference_result(fixture, database), message);
  check(runtime.snapshot().physical.tables == database.tables,
        "delta runtime physical state differs from the independent literal database");
}

void check_attempt_config(const ObservationSummary& summary,
                          const DeltaOptions& requested, DeltaMode resolved,
                          std::uint64_t owner, std::uint64_t generation,
                          ObservationOutcome outcome) {
  check(summary.configuration.has_value(),
        "delta-layer attempt lacks its captured configuration");
  check_configuration(*summary.configuration, requested, resolved,
                      DeltaCompletion::anchored, owner, generation, false);
  check(summary.outcome == outcome, "attempt outcome differs from expected boundary");
}

void scenario_timeline_and_retained_configuration() {
  QFixture fixture;
  auto requested = exact_options();
  DeltaRuntime runtime = DeltaRuntime::initialize(fixture.plan, fixture.initial, requested);
  const auto owner = runtime.owner().value;
  // Q's physical tree has two nodes, but C* contains only R: S's separator
  // {y} is not a subset of head {x}, so Q enumerates one maximal-connex factor.
  check(runtime.plan().nodes().size() == 2,
        "literal Q tree must contain the R root and S child physical nodes");
  auto state = runtime.observations();
  check(state.current_configuration.has_value() && !state.last && state.attempts == 0,
        "initialization must bind generation zero without inventing an attempt");
  check_configuration(*state.current_configuration, requested, DeltaMode::maintenance,
                      DeltaCompletion::anchored, owner, 0, false);
  check_runtime_result(runtime, fixture, fixture.initial,
                       "initial maintenance result differs from independent Q evaluator");

  BuildOptions replay_build;
  replay_build.method = BuildMethod::insertion_replay;
  replay_build.work_limit = std::nullopt;
  auto replay_initialized = DeltaRuntime::initialize(
      fixture.plan, fixture.initial, requested, replay_build);
  const auto replay_state = replay_initialized.observations();
  check(replay_state.current_configuration && !replay_state.last &&
        replay_state.attempts == 0,
        "insertion-replay initialization counted bootstrap as a configuration attempt");
  check_configuration(*replay_state.current_configuration, requested,
                      DeltaMode::maintenance, DeltaCompletion::anchored,
                      replay_initialized.owner().value, 0, false);
  check_runtime_result(replay_initialized, fixture, fixture.initial,
                       "insertion-replay initialization differs from independent Q evaluator");

  static_cast<void>(runtime.set_mode(DeltaMode::maintenance));
  state = runtime.observations();
  check(state.current_configuration && state.current_configuration->generation() == 0,
        "same-mode maintenance request changed the configuration generation");

  PhysicalSetUpdate insert_s{1, TableId{1}, SetOperation::insert, row(9)};
  auto maintenance_insert = runtime.apply(insert_s);
  auto with_match = fixture.initial;
  with_match.tables[1].insert(row(9));
  check(maintenance_insert.remaining() == 0 && !maintenance_insert.next(),
        "maintenance update unexpectedly emitted a delta row");
  check_runtime_result(runtime, fixture, with_match,
                       "maintenance update differs from independent Q reference result");
  state = runtime.observations();
  check(state.last.has_value(), "maintenance input should leave a retained attempt summary");
  check_attempt_config(*state.last, requested, DeltaMode::maintenance, owner, 0,
                       ObservationOutcome::committed);

  static_cast<void>(runtime.set_mode(DeltaMode::delta));
  state = runtime.observations();
  check_configuration(*state.current_configuration, requested, DeltaMode::delta,
                      DeltaCompletion::anchored, owner, 1, false);
  check(state.last && state.last->configuration &&
        state.last->configuration->mode() == DeltaMode::maintenance &&
        state.last->configuration->generation() == 0,
        "switch to delta relabeled the historical maintenance attempt");
  static_cast<void>(runtime.set_mode(DeltaMode::delta));
  check(runtime.observations().current_configuration->generation() == 1,
        "same-mode delta request changed the configuration generation");

  PhysicalSetUpdate erase_s{2, TableId{1}, SetOperation::erase, row(9)};
  auto pending = runtime.begin(erase_s);
  state = runtime.observations();
  check(state.current && state.current->outcome == ObservationOutcome::pending &&
        state.current->configuration && state.current->configuration->generation() == 1,
        "pending attempt did not capture the current generation before work");
  pending.rollback();
  state = runtime.observations();
  check(state.last.has_value(), "aborted delta attempt was not retained");
  check_attempt_config(*state.last, requested, DeltaMode::delta, owner, 1,
                       ObservationOutcome::aborted);
  check(runtime.sequence() == 1,
        "rolling back a pending delta attempt advanced the physical sequence");
  check_runtime_result(runtime, fixture, with_match,
                       "aborted delta attempt changed the reference result");

  auto erase_epoch = runtime.apply(erase_s);
  auto empty_answer = fixture.initial;
  const auto before_busy_switch = runtime.observations();
  expect_error("runtime_busy", [&] {
    static_cast<void>(runtime.set_mode(DeltaMode::maintenance));
  }, "committed unread output should block a mode switch");
  const auto after_busy_switch = runtime.observations();
  check(runtime.mode() == DeltaMode::delta && after_busy_switch.current_configuration &&
        before_busy_switch.current_configuration &&
        after_busy_switch.current_configuration->generation() == 1 &&
        after_busy_switch.last && before_busy_switch.last &&
        after_busy_switch.last->configuration && before_busy_switch.last->configuration &&
        after_busy_switch.last->configuration->generation() ==
            before_busy_switch.last->configuration->generation(),
        "busy mode switch changed current or historical configuration");
  const auto erase_record = erase_epoch.next();
  check(erase_record && erase_record->operation == SetOperation::erase &&
        erase_record->tuple.values() == row(7),
        "committed delta output differs from literal erase of projected row 7");
  check(!erase_epoch.next(), "erase epoch emitted an extra output row");
  check_runtime_result(runtime, fixture, empty_answer,
                       "committed erase differs from independent Q reference result");
  state = runtime.observations();
  check(state.last.has_value(), "committed delta summary was not retained");
  check_attempt_config(*state.last, requested, DeltaMode::delta, owner, 1,
                       ObservationOutcome::committed);

  static_cast<void>(runtime.set_mode(DeltaMode::maintenance));
  state = runtime.observations();
  check_configuration(*state.current_configuration, requested, DeltaMode::maintenance,
                      DeltaCompletion::anchored, owner, 2, false);
  check(state.last && state.last->configuration &&
        state.last->configuration->generation() == 1 &&
        state.last->configuration->mode() == DeltaMode::delta,
        "switch to maintenance rewrote the historical delta summary");

  PhysicalSetUpdate insert_again{3, TableId{1}, SetOperation::insert, row(9)};
  auto maintenance_again = runtime.apply(insert_again);
  with_match.tables[1].insert(row(9));
  check(maintenance_again.remaining() == 0 && !maintenance_again.next(),
        "second maintenance update unexpectedly emitted output");
  check_runtime_result(runtime, fixture, with_match,
                       "second maintenance update differs from independent Q evaluator");
  state = runtime.observations();
  check(state.last && state.last->configuration,
        "second maintenance attempt did not retain its configuration");
  check_attempt_config(*state.last, requested, DeltaMode::maintenance, owner, 2,
                       ObservationOutcome::committed);

  static_cast<void>(runtime.set_mode(DeltaMode::delta));
  state = runtime.observations();
  check_configuration(*state.current_configuration, requested, DeltaMode::delta,
                      DeltaCompletion::anchored, owner, 3, false);
  check(state.last && state.last->configuration &&
        state.last->configuration->generation() == 2,
        "second switch to delta relabeled the maintenance summary");
  PhysicalSetUpdate erase_again{4, TableId{1}, SetOperation::erase, row(9)};
  auto second_erase = runtime.apply(erase_again);
  const auto final_record = second_erase.next();
  check(final_record && final_record->operation == SetOperation::erase &&
        final_record->tuple.values() == row(7) && !second_erase.next(),
        "second delta completion differs from literal Q result transition");
  check_runtime_result(runtime, fixture, empty_answer,
                       "second delta update differs from independent Q evaluator");
  state = runtime.observations();
  check_attempt_config(*state.last, requested, DeltaMode::delta, owner, 3,
                       ObservationOutcome::committed);

  auto captured = runtime.observations();
  const auto saved = *captured.current_configuration;
  std::size_t allocations = 0;
  bool injected = false;
  std::size_t faults = 0;
  allocation_probe::measure([&] {
    const auto copy = runtime.observations();
    const auto reconstructed = saved.requested_options();
    check(copy.current_configuration && same_options(reconstructed, requested),
          "inline configuration copy changed values");
  }, allocation_probe::no_failure, allocations, injected, faults);
  check(allocations == 0 && !injected && faults == 0,
        "reading/copying configuration allocated memory");

  DeltaRuntime moved = std::move(runtime);
  check(moved.owner().value == owner && moved.observations().current_configuration &&
        moved.observations().current_configuration->generation() == 3,
        "moving the runtime changed its owner or current configuration");
  static_cast<void>(moved.set_mode(DeltaMode::maintenance));
  check(moved.observations().current_configuration->generation() == 4,
        "successful mode switch after move did not advance generation");
  check(captured.current_configuration &&
        captured.current_configuration->generation() == 3 &&
        saved.generation() == 3 && saved.mode() == DeltaMode::delta,
        "copied current snapshot/configuration changed after a later mode switch");

  ObservationSnapshot detached;
  ObservationConfiguration detached_configuration = saved;
  std::uint64_t rebuilt_owner = 0;
  {
    auto rebuilt = moved.rebuilt();
    rebuilt_owner = rebuilt.owner().value;
    const auto rebuilt_state = rebuilt.observations();
    check(rebuilt_owner != owner && rebuilt_state.current_configuration,
          "rebuilt runtime did not bind a fresh owner configuration");
    check_configuration(*rebuilt_state.current_configuration, requested,
                        DeltaMode::maintenance, DeltaCompletion::anchored,
                        rebuilt_owner, 0, false);
    check(!rebuilt_state.last && rebuilt_state.attempts == 0,
          "rebuilt runtime inherited attempt history from the old owner");
    check_runtime_result(rebuilt, fixture, empty_answer,
                         "rebuilt runtime result differs from independent Q reference");
    detached = rebuilt_state;
    detached_configuration = *rebuilt_state.current_configuration;
  }
  check(detached.current_configuration && detached.current_configuration->support_owner() == rebuilt_owner &&
        detached_configuration.support_owner() == rebuilt_owner &&
        detached_configuration.generation() == 0 &&
        same_options(detached_configuration.requested_options(), requested),
        "owning configuration/snapshot did not survive runtime destruction");
}

void scenario_failed_bootstrap_is_atomic() {
  QFixture fixture;
  auto requested = exact_options(ObservationMode::counters);
  requested.epoch_view.work_limit = std::uint64_t{0};
  requested.cursor.work_limit = std::uint64_t{0};
  const auto seeded = fixture.with_match();
  DeltaRuntime runtime = DeltaRuntime::initialize(fixture.plan, seeded, requested);
  const auto owner = runtime.owner().value;
  auto before = runtime.observations();
  check(before.current_configuration.has_value(),
        "failed-bootstrap fixture lacks initial current configuration");
  expect_error("resource_limit", [&] {
    static_cast<void>(runtime.set_mode(DeltaMode::delta));
  }, "zero epoch-view/cursor budget should reject delta bootstrap");
  const auto after = runtime.observations();
  check(runtime.mode() == DeltaMode::maintenance && !runtime.live_snapshot() &&
        runtime.owner().value == owner && runtime.sequence() == 0,
        "failed live-image bootstrap changed runtime mode, owner, sequence or cache");
  check(after.current_configuration && after.current_configuration->generation() == 0 &&
        same_options(after.current_configuration->requested_options(), requested) &&
        !after.last && after.attempts == 0,
        "failed live-image bootstrap changed the configuration or invented an attempt");
  check_runtime_result(runtime, fixture, seeded,
                       "failed live-image bootstrap changed the independent query result");
  static_cast<void>(runtime.set_mode(DeltaMode::maintenance));
  check(runtime.observations().current_configuration->generation() == 0,
        "same-mode request after failed bootstrap changed generation");
}

void scenario_allocation_failure_sweep_and_recovery() {
  QFixture fixture;
  auto requested = exact_options(ObservationMode::counters);
  const auto seeded = fixture.with_match();
  std::size_t successful_allocations = 0;
  bool injected = false;
  std::size_t calibration_faults = 0;
  {
    auto calibration = DeltaRuntime::initialize(fixture.plan, seeded, requested);
    allocation_probe::measure([&] {
      static_cast<void>(calibration.set_mode(DeltaMode::delta));
    }, allocation_probe::no_failure, successful_allocations, injected,
       calibration_faults);
    check(calibration.mode() == DeltaMode::delta,
          "allocation calibration did not complete successful live-image bootstrap");
  }
  check(successful_allocations > 0 && !injected && calibration_faults == 0,
        "allocation failure sweep has no observed successful bootstrap allocations");

  std::size_t aggregate_faults = 0;
  for (std::size_t fail_index = 0; fail_index < successful_allocations; ++fail_index) {
    auto runtime = DeltaRuntime::initialize(fixture.plan, seeded, requested);
    const auto owner = runtime.owner().value;
    const auto before_canonical = runtime.canonical_state();
    const auto before_physical = runtime.snapshot();
    const auto before_storage = runtime.storage_statistics();
    const auto before_observation = runtime.observations();
    const auto before_answer = runtime.has_answer();
    const auto before_sequence = runtime.sequence();
    std::size_t total_faults = 0;

    auto verify_unchanged = [&] {
      const auto after = runtime.observations();
      const auto storage = runtime.storage_statistics();
      check(runtime.mode() == DeltaMode::maintenance && !runtime.live_snapshot() &&
            runtime.owner().value == owner && runtime.sequence() == before_sequence &&
            before_sequence == 0 && runtime.has_answer() == before_answer,
            "persistent bad_alloc changed mode, owner, cache, sequence or answer flag");
      check(runtime.canonical_state() == before_canonical &&
            runtime.snapshot().physical.tables == before_physical.physical.tables,
            "persistent bad_alloc changed full canonical/physical state");
      check(storage.source == before_storage.source &&
            storage.support == before_storage.support &&
            storage.derivation_keys == before_storage.derivation_keys,
            "persistent bad_alloc changed owner storage statistics");
      check(after.current_configuration && before_observation.current_configuration &&
            after.current_configuration->support_owner() == owner &&
            after.current_configuration->generation() == 0 &&
            !after.current_configuration->generation_saturated() &&
            after.current_configuration->mode() == DeltaMode::maintenance &&
            same_options(after.current_configuration->requested_options(), requested) &&
            !after.last && after.attempts == before_observation.attempts &&
            !before_observation.last,
            "persistent bad_alloc changed current/historical configuration binding");
      check_runtime_result(runtime, fixture, seeded,
                           "persistent bad_alloc changed independent query result/state");
      runtime.check_invariants();
    };

    // Keep this allocation position armed across two failed calls on the same
    // maintenance owner. `note` fails every allocation at or after fail_index,
    // including any allocation attempted while the first exception unwinds.
    for (std::size_t failed_retry = 0; failed_retry < 2; ++failed_retry) {
      std::size_t observed_allocations = 0;
      std::size_t injected_fault_count = 0;
      bool failure_was_injected = false;
      bool caught_bad_alloc = false;
      try {
        allocation_probe::measure([&] {
          static_cast<void>(runtime.set_mode(DeltaMode::delta));
        }, fail_index, observed_allocations, failure_was_injected,
           injected_fault_count);
      } catch (const std::bad_alloc&) {
        caught_bad_alloc = true;
      }
      check(caught_bad_alloc && failure_was_injected &&
            observed_allocations >= fail_index + 1 && injected_fault_count >= 1,
            "persistent bootstrap fault missed its literal allocation position");
      total_faults += injected_fault_count;
      verify_unchanged();
    }

    // Disable only after both failures and their state checks; recovery uses
    // the exact same owner and the same unmodified requested options.
    allocation_probe::disarm();
    static_cast<void>(runtime.set_mode(DeltaMode::delta));
    const auto recovered = runtime.observations();
    check(runtime.mode() == DeltaMode::delta && runtime.owner().value == owner &&
          recovered.current_configuration &&
          recovered.current_configuration->generation() == 1 &&
          !recovered.current_configuration->generation_saturated(),
          "same owner did not recover after injected bootstrap allocation failure");
    check_runtime_result(runtime, fixture, seeded,
                         "recovered bootstrap differs from independent Q reference result");
    check(runtime.canonical_state().delta_maintained &&
          runtime.canonical_state().physical == before_canonical.physical,
          "same-owner recovery did not install only the live delta image");
    allocation_probe::disarm();
    aggregate_faults += total_faults;
  }
  std::cout << "  swept " << successful_allocations
            << " positions with two same-owner persistent failures each; observed "
            << aggregate_faults << " injected bad_alloc requests\n";
}

void scenario_generation_saturation_and_off_suppression() {
  QFixture fixture;
  auto requested = exact_options(ObservationMode::counters);
  constexpr auto maximum = std::numeric_limits<std::uint64_t>::max();
  detail::set_observation_initial_generation_for_testing(maximum - 1);
  auto runtime = DeltaRuntime::initialize(fixture.plan, fixture.initial, requested);
  detail::set_observation_initial_generation_for_testing(0);
  const auto owner = runtime.owner().value;
  auto initial = runtime.observations();
  check(initial.current_configuration &&
        initial.current_configuration->generation() == maximum - 1 &&
        !initial.current_configuration->generation_saturated(),
        "test seam did not seed a newly constructed enabled owner at UINT64_MAX-1");
  static_cast<void>(runtime.set_mode(DeltaMode::maintenance));
  check(runtime.observations().current_configuration->generation() == maximum - 1,
        "same-mode request advanced a near-maximum generation");
  static_cast<void>(runtime.set_mode(DeltaMode::delta));
  auto at_maximum = runtime.observations();
  check(at_maximum.current_configuration &&
        at_maximum.current_configuration->generation() == maximum &&
        !at_maximum.current_configuration->generation_saturated(),
        "first semantic switch did not reach exact UINT64_MAX without saturation");
  const auto saved_at_maximum = *at_maximum.current_configuration;
  static_cast<void>(runtime.set_mode(DeltaMode::maintenance));
  auto saturated = runtime.observations();
  check(saturated.current_configuration && runtime.mode() == DeltaMode::maintenance &&
        saturated.current_configuration->generation() == maximum &&
        saturated.current_configuration->generation_saturated(),
        "successful switch beyond UINT64_MAX was rejected or not marked saturated");
  static_cast<void>(runtime.set_mode(DeltaMode::delta));
  check(runtime.observations().current_configuration->generation() == maximum &&
        runtime.observations().current_configuration->generation_saturated(),
        "subsequent successful switch cleared the generation saturation marker");
  check(saved_at_maximum.generation() == maximum &&
        !saved_at_maximum.generation_saturated() && saved_at_maximum.mode() == DeltaMode::delta,
        "copied pre-saturation configuration changed after owner saturation");

  PhysicalSetUpdate insert_s{1, TableId{1}, SetOperation::insert, row(9)};
  auto epoch = runtime.apply(insert_s);
  const auto output = epoch.next();
  check(output && output->operation == SetOperation::insert &&
        output->tuple.values() == row(7) && !epoch.next(),
        "saturated-generation runtime changed the independent literal Q output");
  const auto summary = runtime.observations().last;
  check(summary && summary->configuration &&
        summary->configuration->generation() == maximum &&
        summary->configuration->generation_saturated(),
        "attempt summary did not retain saturated configuration identity");

  auto off_options = exact_options(ObservationMode::off);
  // Off removes the observation collector and cannot coexist with the legacy
  // allocating transition journal. Keep the full-capture round trip covered
  // separately by the enabled trace configuration used above.
  expect_error("invalid_observation_options", [&] {
    static_cast<void>(DeltaRuntime::initialize(fixture.plan, fixture.initial,
                                               off_options));
  }, "off plus legacy transition capture must retain its constructor rejection");
  off_options.physical.support.capture_transitions = false;
  detail::set_observation_initial_generation_for_testing(maximum);
  auto off = DeltaRuntime::initialize(fixture.plan, fixture.initial, off_options);
  detail::set_observation_initial_generation_for_testing(0);
  check(!off.observations().current_configuration && !off.observations().last,
        "off mode exposed a generation/configuration despite disabled observation");
  static_cast<void>(off.set_mode(DeltaMode::delta));
  auto off_epoch = off.apply(insert_s);
  const auto off_output = off_epoch.next();
  check(off_output && off_output->operation == SetOperation::insert &&
        off_output->tuple.values() == row(7) && !off_epoch.next(),
        "off-mode saturated seam changed mandatory runtime output");
  const auto off_snapshot = off.observations();
  check(!off_snapshot.current_configuration && !off_snapshot.last &&
        off_snapshot.options.mode == ObservationMode::off && off_snapshot.mandatory_accounting,
        "off mode retained optional configuration state or disabled mandatory accounting");
  check(owner != 0, "generation-boundary runtime owner was not assigned");
}

struct ModeRun {
  PhysicalMetrics physical;
  SupportMetrics support;
  DeltaMetrics delta;
  std::size_t allocations = 0;
  std::uint64_t clock_count = 0;
};

ModeRun run_observation_mode(const QFixture& fixture, ObservationMode mode) {
  auto requested = exact_options(mode);
  // Match the legacy allocating transition-capture policy across off,
  // counters and timed runs; off+capture is intentionally invalid.
  requested.physical.support.capture_transitions = false;
  requested.physical.support.observation.trace_timings = false;
  requested.mode = DeltaMode::delta;
  requested.live_maintenance = LiveMaintenance::eager;
  auto runtime = DeltaRuntime::initialize(fixture.plan, fixture.initial, requested);
  detail::set_observation_clock_for_testing(&fake_clock);
  clock_reads = 0;
  PhysicalSetUpdate update{1, TableId{1}, SetOperation::insert, row(9)};
  std::size_t allocations = 0;
  bool injected = false;
  std::size_t faults = 0;
  PhysicalMetrics physical;
  SupportMetrics support;
  DeltaMetrics delta;
  allocation_probe::measure([&] {
    auto epoch = runtime.apply(update);
    physical = epoch.input().input.metrics;
    support = epoch.input().support.metrics;
    delta = epoch.metrics();
    const auto output = epoch.next();
    check(output && output->operation == SetOperation::insert &&
          output->tuple.values() == row(7) && !epoch.next(),
          "observation-mode update differs from independent literal output");
  }, allocation_probe::no_failure, allocations, injected, faults);
  const auto reads = clock_reads;
  detail::set_observation_clock_for_testing(nullptr);
  check(!injected && faults == 0,
        "clock comparison unexpectedly injected allocation failure");
  const auto expected = reference_result(fixture, fixture.with_match());
  check(drain(runtime.results()) == expected,
        "observation-mode final state differs from independent reference evaluator");
  const auto snapshot = runtime.observations();
  if (mode == ObservationMode::off) {
    check(!snapshot.current_configuration && !snapshot.last,
          "off mode constructed optional mode-binding state");
  } else {
    check(snapshot.last && snapshot.last->configuration,
          "enabled mode did not retain the configuration captured for its attempt");
    check_configuration(*snapshot.last->configuration, requested, DeltaMode::delta,
                        DeltaCompletion::anchored, runtime.owner().value, 0, false);
  }
  return {physical, support, delta, allocations, reads};
}

void scenario_off_equivalence_and_optional_clock() {
  QFixture fixture;
  const auto off = run_observation_mode(fixture, ObservationMode::off);
  const auto counters = run_observation_mode(fixture, ObservationMode::counters);
  const auto timed = run_observation_mode(fixture, ObservationMode::timed);
  check(off.physical.work == counters.physical.work &&
        off.physical.source_changes == counters.physical.source_changes &&
        off.physical.aliases_visited == counters.physical.aliases_visited &&
        off.physical.derivation_changes == counters.physical.derivation_changes &&
        off.support.work == counters.support.work &&
        off.support.native_record_visits == counters.support.native_record_visits &&
        off.support.child_key_probes == counters.support.child_key_probes &&
        off.delta.work == counters.delta.work && off.delta.accepted == counters.delta.accepted,
        "off and counters modes changed mandatory work/results on the same Q update");
  check(off.physical.work == timed.physical.work &&
        off.support.work == timed.support.work && off.delta.work == timed.delta.work,
        "timing mode changed mandatory work on the same Q update");
  check(off.allocations == counters.allocations &&
        off.allocations == timed.allocations,
        "optional mode/configuration added mutation allocations to the matched Q update");
  check(off.clock_count == 0 && counters.clock_count == 0 && timed.clock_count > 0,
        "off/counters clock suppression or timed clock collection differs from expectation");
}

void scenario_direct_lower_layers_unbound() {
  QFixture fixture;
  auto requested = exact_options(ObservationMode::counters);

  SupportOptions support_options = requested.physical.support;
  SupportRuntime support(fixture.plan, support_options);
  auto support_epoch = support.apply({1, NodeId{0}, SetOperation::insert, edge(7, 9)});
  const auto support_snapshot = support.observations();
  check(support_snapshot.last && !support_snapshot.last->configuration &&
        !support_snapshot.current_configuration,
        "direct support-only attempt fabricated a delta configuration binding");
  check(support_epoch.sequence == 1,
        "direct support-only fixture did not perform its literal native update");

  PhysicalRuntimeOptions physical_options = requested.physical;
  PhysicalRuntime physical(fixture.plan, physical_options);
  auto physical_epoch = physical.apply(
      {1, TableId{1}, SetOperation::insert, row(9)});
  const auto physical_snapshot = physical.observations();
  check(physical_snapshot.last && !physical_snapshot.last->configuration &&
        !physical_snapshot.current_configuration,
        "direct physical-only attempt fabricated a delta configuration binding");
  check(physical_epoch.input.sequence == 1,
        "direct physical-only fixture did not perform its literal source update");
}

void scenario_session_drain_drop_retains_captured_configuration() {
  QFixture fixture;
  auto requested = exact_options(ObservationMode::trace);
  requested.mode = DeltaMode::delta;
  requested.live_maintenance = LiveMaintenance::eager;
  SessionOptions options;
  options.delta = requested;
  const io::InputEvent event{
      {1, TableId{1}, SetOperation::insert, row(9)},
      io::SourcePosition{"mode-binding-session", 0},
  };
  auto input_bytes = io::write_input_json(event, fixture.catalog);
  input_bytes.push_back('\n');
  std::unique_ptr<std::istream> input =
      std::make_unique<std::istringstream>(std::move(input_bytes));
  auto session = QuerySession::create(fixture.plan, fixture.initial,
                                      std::move(input), options);
  const auto owner = session->observations().support_owner;
  auto current = session->observations();
  check(current.current_configuration.has_value(),
        "session did not expose initialized current mode binding");
  check_configuration(*current.current_configuration, requested, DeltaMode::delta,
                      DeltaCompletion::anchored, owner, 0, false);
  session->start();
  check(session->begin_next_result() == SessionBegin::pending,
        "session did not admit its single literal Q input");
  while (session->step() != DeltaStep::prepared) {}
  session->commit();
  const auto expected = reference_result(fixture, fixture.with_match());
  const auto session_rows = session->snapshot().rows;
  Relation actual;
  for (const auto& tuple : session_rows)
    check(actual.insert(crown::storage::export_row(tuple.values())).second, "session snapshot duplicated an output row");
  check(actual == expected && expected == Relation{row(7)},
        "session committed result differs from independent reference Q evaluator");
  const auto committed = session->observations();
  check(committed.last && committed.last->outcome == ObservationOutcome::committed &&
        committed.last->configuration,
        "session commit did not retain its bound attempt summary");
  check_configuration(*committed.last->configuration, requested, DeltaMode::delta,
                      DeltaCompletion::anchored, owner, 0, false);

  session->drain();
  const auto drained = session->observations();
  check(drained.last && drained.last->configuration &&
        drained.last->configuration->support_owner() == owner &&
        drained.last->configuration->generation() == 0,
        "session output drain rewrote or discarded the committed mode binding");
  const auto trace_before_drop = session->observation_trace();
  check(trace_before_drop.snapshot.last && !trace_before_drop.records.empty(),
        "trace-mode session lost its bounded causal rows before drop");
  session->stop();
  session->drop();
  const auto after_drop = session->observations();
  check(after_drop.session_attached && after_drop.last &&
        after_drop.last->configuration &&
        after_drop.last->configuration->support_owner() == owner &&
        after_drop.last->configuration->mode() == DeltaMode::delta &&
        after_drop.last->configuration->generation() == 0,
        "session drop lost the retained historical configuration value");
  const auto released_trace = session->observation_trace();
  check(released_trace.snapshot.trace == TraceDisposition::released &&
        released_trace.records.empty() && released_trace.snapshot.last &&
        released_trace.snapshot.last->configuration &&
        released_trace.snapshot.last->configuration->support_owner() == owner,
        "session drop did not release trace rows while retaining configuration summary");
}

template <class Action>
void run_scenario(std::string_view name, Action&& action) {
  std::cout << "[O07 mode binding] " << name << " ..." << std::endl;
  try {
    std::forward<Action>(action)();
  } catch (const std::exception& error) {
    throw std::runtime_error(std::string(name) + ": " + error.what());
  }
}
}  // namespace

int main() {
  try {
    run_scenario("historical/current timeline, moves, rebuild and value lifetime",
                 scenario_timeline_and_retained_configuration);
    run_scenario("failed bootstrap preserves configuration and owner",
                 scenario_failed_bootstrap_is_atomic);
    run_scenario("mode-switch allocation failures and same-owner recovery",
                 scenario_allocation_failure_sweep_and_recovery);
    run_scenario("generation saturation and off-mode suppression",
                 scenario_generation_saturation_and_off_suppression);
    run_scenario("off/counters/timed equivalence, allocation and clock checks",
                 scenario_off_equivalence_and_optional_clock);
    run_scenario("direct lower-layer summaries stay unbound",
                 scenario_direct_lower_layers_unbound);
    run_scenario("session drain/drop retains the historical binding",
                 scenario_session_drain_drop_retains_captured_configuration);
    detail::set_observation_clock_for_testing(nullptr);
    detail::set_observation_initial_generation_for_testing(0);
    std::cout << "All independent O07 mode-binding proposal scenarios passed.\n";
    return 0;
  } catch (const std::exception& error) {
    detail::set_observation_clock_for_testing(nullptr);
    detail::set_observation_initial_generation_for_testing(0);
    std::cerr << "O07 mode-binding proposal failed: " << error.what() << '\n';
    return 1;
  }
}
