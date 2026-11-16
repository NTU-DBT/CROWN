#include "crown/api/error.hpp"
#include "crown/frontend/bind.hpp"
#include "crown/frontend/normalize.hpp"
#include "crown/io/support.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/delta.hpp"

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <new>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

// Keep failure armed while a pending epoch closes cursors and undoes private
// physical, support, and live-image state. It replaces ordinary throwing scalar/array global new forms.
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

static_assert(std::is_nothrow_move_constructible_v<DeltaRuntime>);
static_assert(std::is_nothrow_move_assignable_v<DeltaRuntime>);
static_assert(std::is_nothrow_move_constructible_v<DeltaRuntime::PendingEpoch>);
static_assert(std::is_nothrow_move_assignable_v<DeltaRuntime::PendingEpoch>);
static_assert(std::is_nothrow_move_constructible_v<DeltaRuntime::Epoch>);
static_assert(std::is_nothrow_move_assignable_v<DeltaRuntime::Epoch>);

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
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

Value n(std::int64_t value) { return value; }
Row edge(std::int64_t left, std::int64_t right) { return {n(left), n(right)}; }

PhysicalPlan make_alias_separator_plan() {
  const Catalog catalog{18, {{"e", {{"x", ScalarType::int64}, {"z", ScalarType::int64}}}}};
  const auto binding = frontend::bind_sql(
      "SELECT DISTINCT l.x, l.z, r.z FROM E AS l JOIN E AS r ON l.z = r.x", catalog);
  if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&binding))
    throw std::runtime_error(failure->diagnostic.code + ": " + failure->diagnostic.message);
  auto normalized = frontend::normalize_sql(std::get<frontend::BoundSql>(binding));
  if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&normalized))
    throw std::runtime_error(failure->diagnostic.code + ": " + failure->diagnostic.message);
  auto program = std::get<frontend::NormalizedSql>(std::move(normalized));
  const FreeConnexTree tree{NodeId{0}, {
      {"join-key", NodeKind::generalized, {VariableId{1}}, {NodeId{1}, NodeId{2}}, {}, {}},
      {"left", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}},
      {"right", NodeKind::native, {VariableId{1}, VariableId{2}}, {}, 1, {}}}, {}, {}};
  return planner::lower_normalized(program, tree);
}

PhysicalPlan make_shared_separator_plan() {
  constexpr VariableId a{0}, x{1}, y{2};
  const Catalog catalog{20, {
      {"R", {{"a", ScalarType::int64}, {"x", ScalarType::int64}}},
      {"S", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}}}};
  const Query query{
      {{"a", ScalarType::int64}, {"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"r", TableId{0}, {a, x}}, {"s", TableId{1}, {x, y}}},
      {{a, "a"}, {x, "x"}, {y, "y"}}, false};
  const FreeConnexTree tree{NodeId{0}, {
      {"r", NodeKind::native, {a, x}, {NodeId{1}}, 0, {}},
      {"s", NodeKind::native, {x, y}, {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

DeltaOptions options(std::size_t spool_rows = 65536,
                     std::size_t spool_bytes = 64 * 1024 * 1024) {
  DeltaOptions result;
  result.mode = DeltaMode::delta;
  result.live_maintenance = LiveMaintenance::on_output;
  result.physical.support.capture_transitions = true;
  result.spool_row_limit = spool_rows;
  result.spool_byte_limit = spool_bytes;
  return result;
}

void apply_and_discard(DeltaRuntime& runtime, TableId table,
                       SetOperation operation, Row values) {
  auto epoch = runtime.apply({runtime.sequence() + 1, table, operation, std::move(values)});
  epoch.discard();
  check(runtime.ready(), "discarding a seed output did not release its output lease");
}

void seed_alias_plan(DeltaRuntime& runtime) {
  apply_and_discard(runtime, TableId{0}, SetOperation::insert, edge(1, 2));
  apply_and_discard(runtime, TableId{0}, SetOperation::insert, edge(2, 1));
}

void seed_shared_separator(DeltaRuntime& runtime) {
  apply_and_discard(runtime, TableId{0}, SetOperation::insert, {n(1), n(7)});
  apply_and_discard(runtime, TableId{0}, SetOperation::insert, {n(2), n(7)});
  apply_and_discard(runtime, TableId{1}, SetOperation::insert, {n(7), n(9)});
}

struct DerivationImage {
  Row values;
  std::uint64_t count;
  bool operator==(const DerivationImage&) const = default;
};
struct SnapshotImage {
  std::uint64_t sequence = 0;
  SupportOwnerId owner{};
  std::vector<Relation> physical;
  io::Json support;
  std::vector<std::vector<DerivationImage>> derivations;
  bool operator==(const SnapshotImage&) const = default;
};

SnapshotImage snapshot_image(const DeltaRuntime& runtime) {
  const auto snapshot = runtime.snapshot();
  SnapshotImage result;
  result.sequence = snapshot.sequence;
  result.owner = runtime.owner();
  result.physical = snapshot.physical.tables;
  result.support = io::write_support_snapshot(snapshot.support, runtime.plan());
  result.derivations.resize(snapshot.derivations.size());
  for (std::size_t occurrence = 0; occurrence < snapshot.derivations.size(); ++occurrence)
    for (const auto& derivation : snapshot.derivations[occurrence])
      result.derivations[occurrence].push_back({crown::storage::export_row(derivation.tuple.values()), derivation.count});
  return result;
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

bool same_logical_snapshot(const SnapshotImage& left, const SnapshotImage& right) {
  return left.sequence == right.sequence && left.physical == right.physical &&
         normalized_owners(left.support) == normalized_owners(right.support) &&
         left.derivations == right.derivations;
}

bool same_live(const std::optional<LiveSnapshot>& left,
               const std::optional<LiveSnapshot>& right) {
  if (left.has_value() != right.has_value()) return false;
  return !left || (left->sequence == right->sequence && left->factors == right->factors);
}

void check_stats(const PhysicalStorageStatistics& before,
                 const PhysicalStorageStatistics& after,
                 std::string_view context) {
  const auto check_arena = [&](const storage::ArenaStatistics& old_stats,
                               const storage::ArenaStatistics& new_stats,
                               std::string_view name) {
    check(old_stats.live_records == new_stats.live_records &&
              old_stats.retained_records == new_stats.retained_records &&
              old_stats.pins == new_stats.pins && new_stats.slots >= old_stats.slots,
          std::string(context) + ": aborted epoch changed committed " + std::string(name) +
              " records/pins or reduced arena high-water slots");
  };
  check_arena(before.source, after.source, "source");
  check_arena(before.support, after.support, "support");
  check(before.derivation_keys == after.derivation_keys,
        std::string(context) + ": aborted epoch changed committed derivation-key count");
}

void check_unchanged(DeltaRuntime& runtime, const SnapshotImage& before,
                     const std::optional<LiveSnapshot>& live_before,
                     const PhysicalStorageStatistics& stats_before,
                     std::uint64_t sequence, bool answer, std::string_view context) {
  check(runtime.ready() && runtime.state() == DeltaState::ready &&
            runtime.sequence() == sequence && runtime.has_answer() == answer,
        std::string(context) + ": aborted epoch changed readiness, sequence, or answer");
  check(runtime.owner() == before.owner,
        std::string(context) + ": aborted epoch changed the public support owner");
  check(snapshot_image(runtime) == before,
        std::string(context) + ": aborted epoch changed physical rows, support counts, or derivations");
  check(same_live(runtime.live_snapshot(), live_before),
        std::string(context) + ": aborted epoch changed committed live factors");
  check_stats(stats_before, runtime.storage_statistics(), context);
  runtime.check_invariants();
}

struct RecordImage {
  std::uint64_t ordinal;
  SetOperation operation;
  Row values;
  bool operator==(const RecordImage&) const = default;
};

std::vector<RecordImage> records(DeltaRuntime::Epoch& epoch) {
  std::vector<RecordImage> result;
  while (auto record = epoch.next())
    result.push_back({record->ordinal, record->operation, crown::storage::export_row(record->tuple.values())});
  return result;
}

void check_retry_matches_clean(DeltaRuntime& retried_runtime,
                               DeltaRuntime::Epoch& retried_output,
                               DeltaRuntime& clean_runtime,
                               DeltaRuntime::Epoch& clean_output,
                               std::uint64_t expected_sequence,
                               std::string_view context) {
  check(retried_output.sequence() == expected_sequence &&
            clean_output.sequence() == expected_sequence,
        std::string(context) + ": retry and clean output sequences differ");
  check(records(retried_output) == records(clean_output),
        std::string(context) + ": same-sequence retry output differs from clean execution");
  check(same_logical_snapshot(snapshot_image(retried_runtime), snapshot_image(clean_runtime)),
        std::string(context) + ": retry physical/support/derivation snapshot differs from clean execution");
  check(same_live(retried_runtime.live_snapshot(), clean_runtime.live_snapshot()),
        std::string(context) + ": retry live image differs from clean execution");
  check_stats(clean_runtime.storage_statistics(), retried_runtime.storage_statistics(), context);
  retried_runtime.check_invariants();
  clean_runtime.check_invariants();
}

template <class RuntimeFactory, class Seeder>
void sweep_begin_failures(RuntimeFactory make_runtime, Seeder seed,
                          std::string_view label) {
  constexpr std::ptrdiff_t max_points = 4096;
  std::size_t failures = 0;
  for (std::ptrdiff_t point = 0; point < max_points; ++point) {
    auto runtime = make_runtime();
    seed(runtime);
    const auto before = snapshot_image(runtime);
    const auto live_before = runtime.live_snapshot();
    const auto stats_before = runtime.storage_statistics();
    const auto sequence = runtime.sequence();
    const auto answer = runtime.has_answer();
    const PhysicalSetUpdate update{sequence + 1, TableId{0}, SetOperation::insert, edge(1, 1)};

    bool failed = false;
    std::optional<DeltaRuntime::PendingEpoch> pending;
    {
      FaultScope fault(point);
      try {
        pending.emplace(runtime.begin(update));
      } catch (const std::bad_alloc&) {
        failed = true;
        fail_after = 0;
      }
    }
    if (failed) {
      ++failures;
      check_unchanged(runtime, before, live_before, stats_before, sequence, answer, label);
      auto retry = runtime.begin(update);
      check(retry.active() && retry.sequence() == sequence + 1,
            std::string(label) + ": same-sequence begin retry did not open a pending epoch");
      retry.drain();
      auto committed = retry.commit();
      auto clean = make_runtime();
      seed(clean);
      auto clean_output = clean.apply(update);
      check_retry_matches_clean(runtime, committed, clean, clean_output, sequence + 1, label);
      committed.discard();
      clean_output.discard();
      continue;
    }

    check(failures > 0, std::string(label) + ": ordinary-new fault sweep injected no begin failure");
    check(pending && pending->active() && runtime.state() == DeltaState::pending_delta,
          std::string(label) + ": successful begin did not publish a private pending state");
    pending->rollback();
    check_unchanged(runtime, before, live_before, stats_before, sequence, answer, label);
    std::cout << label << " begin ordinary-new failures=" << failures << '\n';
    return;
  }
  throw std::runtime_error(std::string(label) + ": begin ordinary-new fault sweep exceeded fault points");
}

template <class Seeder>
void sweep_first_step_failures(Seeder seed, std::string_view label) {
  constexpr std::ptrdiff_t max_points = 4096;
  std::size_t failures = 0;
  for (std::ptrdiff_t point = 0; point < max_points; ++point) {
    DeltaRuntime runtime{make_alias_separator_plan(), options()};
    seed(runtime);
    const auto before = snapshot_image(runtime);
    const auto live_before = runtime.live_snapshot();
    const auto stats_before = runtime.storage_statistics();
    const auto sequence = runtime.sequence();
    const auto answer = runtime.has_answer();
    auto pending = runtime.begin({sequence + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
    check(pending.active(), std::string(label) + ": fixture begin did not retain its transaction");

    bool failed = false;
    DeltaStep returned = DeltaStep::progress;
    {
      FaultScope fault(point);
      try {
        returned = pending.step();
      } catch (const std::bad_alloc&) {
        failed = true;
        fail_after = 0;
      }
    }
    if (failed) {
      ++failures;
      check(!pending.active() && pending.state() == DeltaState::aborted &&
                runtime.state() == DeltaState::ready,
            std::string(label) + ": ordinary-new failure left a ghost pending epoch");
      check_unchanged(runtime, before, live_before, stats_before, sequence, answer, label);
      auto retry = runtime.begin({sequence + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
      retry.drain();
      auto retried = retry.commit();
      DeltaRuntime clean{make_alias_separator_plan(), options()};
      seed(clean);
      auto clean_output = clean.apply({sequence + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
      check_retry_matches_clean(runtime, retried, clean, clean_output, sequence + 1, label);
      retried.discard();
      clean_output.discard();
      continue;
    }

    check(failures > 0, std::string(label) + ": ordinary-new fault sweep injected no step failure");
    check(returned == DeltaStep::progress || returned == DeltaStep::core_result ||
              returned == DeltaStep::prepared,
          std::string(label) + ": successful step returned an unknown transition");
    pending.rollback();
    check_unchanged(runtime, before, live_before, stats_before, sequence, answer, label);
    std::cout << label << " first-step ordinary-new failures=" << failures << '\n';
    return;
  }
  throw std::runtime_error(std::string(label) + ": step ordinary-new fault sweep exceeded fault points");
}

void sweep_resumed_cursor_failures() {
  constexpr std::ptrdiff_t max_points = 4096;
  std::size_t failures = 0;
  for (std::ptrdiff_t point = 0; point < max_points; ++point) {
    DeltaRuntime runtime{make_shared_separator_plan(), options()};
    seed_shared_separator(runtime);
    const auto before = snapshot_image(runtime);
    const auto live_before = runtime.live_snapshot();
    const auto stats_before = runtime.storage_statistics();
    const auto sequence = runtime.sequence();
    const auto answer = runtime.has_answer();
    const PhysicalSetUpdate update{sequence + 1, TableId{1}, SetOperation::insert, {n(7), n(10)}};
    auto pending = runtime.begin(update);
    while (true) {
      const auto result = pending.step();
      if (result == DeltaStep::core_result) break;
      check(result != DeltaStep::prepared,
            "selected-cursor fixture prepared before exposing a cursor result");
    }
    pending.pause();
    pending.resume();

    bool failed = false;
    DeltaStep returned = DeltaStep::progress;
    {
      FaultScope fault(point);
      try {
        returned = pending.step();
      } catch (const std::bad_alloc&) {
        failed = true;
        fail_after = 0;
      }
    }
    if (failed) {
      ++failures;
      check(!pending.active() && pending.state() == DeltaState::aborted,
            "ordinary-new failure while resuming a selected cursor left the epoch active");
      check_unchanged(runtime, before, live_before, stats_before, sequence, answer,
                      "selected-cursor resume ordinary-new fault sweep");
      auto retry = runtime.begin(update);
      retry.drain();
      auto result = retry.commit();
      DeltaRuntime clean{make_shared_separator_plan(), options()};
      seed_shared_separator(clean);
      auto clean_result = clean.apply(update);
      check_retry_matches_clean(runtime, result, clean, clean_result, sequence + 1,
                                "selected-cursor resume ordinary-new fault sweep");
      result.discard();
      clean_result.discard();
      continue;
    }

    check(failures > 0,
          "selected-cursor resume ordinary-new fault sweep injected no failure");
    check(returned == DeltaStep::progress || returned == DeltaStep::core_result ||
              returned == DeltaStep::prepared,
          "resumed selected cursor returned an unknown transition");
    pending.rollback();
    check_unchanged(runtime, before, live_before, stats_before, sequence, answer,
                    "selected-cursor resume ordinary-new fault sweep");
    std::cout << "selected-cursor resume ordinary-new failures=" << failures << '\n';
    return;
  }
  throw std::runtime_error("selected-cursor resume sweep exceeded fault points");
}

void sweep_paused_drain_failures() {
  constexpr std::ptrdiff_t max_points = 8192;
  std::size_t failures = 0;
  for (std::ptrdiff_t point = 0; point < max_points; ++point) {
    DeltaRuntime runtime{make_alias_separator_plan(), options()};
    seed_alias_plan(runtime);
    const auto before = snapshot_image(runtime);
    const auto live_before = runtime.live_snapshot();
    const auto stats_before = runtime.storage_statistics();
    const auto sequence = runtime.sequence();
    const auto answer = runtime.has_answer();
    auto pending = runtime.begin({sequence + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
    pending.pause();
    expect_error([&] { static_cast<void>(pending.step()); }, "delta_paused");
    check(pending.active() && pending.state() == DeltaState::paused &&
              runtime.state() == DeltaState::paused,
          "misuse of step while paused aborted or advanced the pending epoch");
    pending.resume();
    const auto prefix = pending.step();
    if (prefix == DeltaStep::prepared) {
      // The chosen fixture has work, but this guard keeps quota and lifecycle
      // assertions useful if a query rewrite changes its route plan.
      check(false, "paused drain fixture prepared before producing a stage prefix");
    }
    pending.pause();

    bool failed = false;
    {
      FaultScope fault(point);
      try {
        pending.drain();
      } catch (const std::bad_alloc&) {
        failed = true;
        fail_after = 0;
      }
    }
    if (failed) {
      ++failures;
      check(!pending.active() && pending.state() == DeltaState::aborted,
            "faulted drain did not abort its whole paused epoch");
      check_unchanged(runtime, before, live_before, stats_before, sequence, answer,
                      "paused drain ordinary-new fault sweep");
      auto retry = runtime.begin({sequence + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
      retry.drain();
      auto result = retry.commit();
      DeltaRuntime clean{make_alias_separator_plan(), options()};
      seed_alias_plan(clean);
      auto clean_result = clean.apply({sequence + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
      check_retry_matches_clean(runtime, result, clean, clean_result, sequence + 1,
                                "paused drain ordinary-new fault sweep");
      result.discard();
      clean_result.discard();
      continue;
    }

    check(failures > 0, "paused drain ordinary-new fault sweep injected no failure");
    check(pending.state() == DeltaState::epoch_prepared,
          "successful drain did not finish the epoch after a pause");
    auto result = pending.commit();
    check(result.sequence() == sequence + 1,
          "successful paused drain committed the wrong sequence");
    result.discard();
    runtime.check_invariants();
    std::cout << "paused drain ordinary-new failures=" << failures << '\n';
    return;
  }
  throw std::runtime_error("paused drain ordinary-new fault sweep exceeded fault points");
}

void test_stage_prefix_rollback_and_aliases() {
  for (const auto kind : {0, 1}) {
    auto make_runtime = [&] {
      return kind == 0 ? DeltaRuntime{make_alias_separator_plan(), options()}
                       : DeltaRuntime{make_shared_separator_plan(), options()};
    };
    auto seed = [&](DeltaRuntime& runtime) {
      if (kind == 0) seed_alias_plan(runtime);
      else seed_shared_separator(runtime);
    };
    auto runtime = make_runtime();
    seed(runtime);
    const auto before = snapshot_image(runtime);
    const auto live_before = runtime.live_snapshot();
    const auto stats_before = runtime.storage_statistics();
    const auto sequence = runtime.sequence();
    const auto answer = runtime.has_answer();
    const PhysicalSetUpdate update = kind == 0
        ? PhysicalSetUpdate{sequence + 1, TableId{0}, SetOperation::insert, edge(1, 1)}
        : PhysicalSetUpdate{sequence + 1, TableId{1}, SetOperation::erase, {n(7), n(9)}};
    auto pending = runtime.begin(update);

    bool saw_core_prefix = false;
    while (!saw_core_prefix) {
      const auto result = pending.step();
      saw_core_prefix = result == DeltaStep::core_result;
      check(result != DeltaStep::prepared,
            "stage-prefix rollback fixture prepared without exposing an accepted core row");
    }
    pending.pause();
    pending.rollback();
    check(!pending.active() && pending.state() == DeltaState::aborted,
          "rollback after a core prefix did not close the pending epoch");
    check_unchanged(runtime, before, live_before, stats_before, sequence, answer,
                    kind == 0 ? "multi-alias core-prefix rollback" : "shared-separator core-prefix rollback");

    auto retried = runtime.begin(update);
    retried.drain();
    auto result = retried.commit();
    auto clean = make_runtime();
    seed(clean);
    auto clean_result = clean.apply(update);
    check_retry_matches_clean(runtime, result, clean, clean_result, sequence + 1,
                              kind == 0 ? "multi-alias prefix retry" : "shared-separator prefix retry");
    check(result.sequence() == sequence + 1 && result.input().input.sequence == sequence + 1,
          "same-sequence retry after a core-prefix rollback lost its physical input");
    check(!result.stages().empty(), "same-sequence retry omitted completed route summaries");
    if (kind == 0)
      check(result.stages().size() >= 2,
            "multi-alias retry did not preserve separate ordered route prefixes");
    else
      check(result.metrics().live_separator_updates > 0 || result.metrics().live_changes > 0,
            "shared-separator retry did not exercise separator maintenance");
    result.discard();
    clean_result.discard();
    runtime.check_invariants();
  }
}

void test_noalloc_pending_lifecycle() {
  {
    DeltaRuntime runtime{make_alias_separator_plan(), options()};
    seed_alias_plan(runtime);
    const auto before = snapshot_image(runtime);
    const auto live_before = runtime.live_snapshot();
    const auto stats_before = runtime.storage_statistics();
    const auto sequence = runtime.sequence();
    const auto answer = runtime.has_answer();
    auto pending = runtime.begin({sequence + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
    static_cast<void>(pending.step());
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      pending.rollback();
    }
    check(!pending.active() && pending.state() == DeltaState::aborted,
          "explicit rollback with ordinary scalar/array global new forced to fail left the pending transaction active");
    check_unchanged(runtime, before, live_before, stats_before, sequence,
                    answer, "explicit pending rollback with ordinary scalar/array global new forced to fail");
  }

  {
    DeltaRuntime runtime{make_alias_separator_plan(), options()};
    seed_alias_plan(runtime);
    const auto sequence = runtime.sequence();
    std::optional<DeltaRuntime::PendingEpoch> pending;
    pending.emplace(runtime.begin({sequence + 1, TableId{0}, SetOperation::insert, edge(1, 1)}));
    static_cast<void>(pending->step());
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      pending.reset();
    }
    check(!pending && runtime.ready() && runtime.sequence() == sequence,
          "pending destruction with ordinary scalar/array global new forced to fail published or retained an epoch");
    runtime.check_invariants();
  }

  {
    DeltaRuntime runtime{make_alias_separator_plan(), options()};
    seed_alias_plan(runtime);
    const auto sequence = runtime.sequence();
    auto source = runtime.begin({sequence + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
    std::optional<DeltaRuntime::PendingEpoch> moved;
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      moved.emplace(std::move(source));
      auto moved_again = std::move(*moved);
      moved.emplace(std::move(moved_again));
      moved->rollback();
    }
    check(!source.active() && moved->state() == DeltaState::aborted && runtime.ready() &&
              runtime.sequence() == sequence,
          "pending moves with ordinary scalar/array global new forced to fail detached rollback from the runtime");
    runtime.check_invariants();
  }

  {
    std::optional<DeltaRuntime::PendingEpoch> pending;
    {
      DeltaRuntime runtime{make_alias_separator_plan(), options()};
      seed_alias_plan(runtime);
      const auto sequence = runtime.sequence();
      pending.emplace(runtime.begin({sequence + 1, TableId{0}, SetOperation::insert, edge(1, 1)}));
      static_cast<void>(pending->step());
    }
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      pending->rollback();
      pending.reset();
    }
    check(!pending, "pending epoch could not unwind while ordinary scalar/array global new was forced to fail after facade destruction");
  }

  {
    DeltaRuntime runtime{make_alias_separator_plan(), options()};
    seed_alias_plan(runtime);
    const auto sequence = runtime.sequence();
    auto pending = runtime.begin({sequence + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      pending.pause();
      pending.resume();
      pending.start_drain();
    }
    check(pending.state() == DeltaState::draining,
          "pause/resume/start_drain with ordinary scalar/array global new forced to fail did not reach draining state");
    pending.drain();
    check(pending.state() == DeltaState::epoch_prepared,
          "drain after start_drain did not prepare the epoch");
    DeltaRuntime::Epoch committed = [&] {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      return pending.commit();
    }();
    check(committed.sequence() == sequence + 1 && runtime.sequence() == sequence + 1,
          "prepared commit with ordinary scalar/array global new forced to fail did not publish its input sequence");
    committed.discard();
    runtime.check_invariants();
  }
}

void test_quota_failures_after_partial_progress() {
  {
    auto limited_config = options(1);
    limited_config.mode = DeltaMode::maintenance;
    DeltaRuntime runtime{make_alias_separator_plan(), limited_config};
    seed_alias_plan(runtime);
    static_cast<void>(runtime.set_mode(DeltaMode::delta));
    const auto before = snapshot_image(runtime);
    const auto live_before = runtime.live_snapshot();
    const auto stats_before = runtime.storage_statistics();
    const auto sequence = runtime.sequence();
    const auto answer = runtime.has_answer();
    auto pending = runtime.begin({sequence + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
    while (pending.metrics().spool_rows == 0) {
      const auto result = pending.step();
      check(result != DeltaStep::prepared,
            "late spool quota fixture prepared before producing an output prefix");
    }
    check(pending.metrics().spool_rows == 1,
          "late spool quota fixture did not retain exactly one private output prefix");
    bool limited = false;
    try {
      pending.drain();
    } catch (const Error& failure) {
      limited = failure.code() == "resource_limit";
    }
    check(limited && !pending.active() && pending.state() == DeltaState::aborted,
          "spool quota failure after partial progress did not abort the whole epoch");
    check_unchanged(runtime, before, live_before, stats_before, sequence, answer,
                    "late spool quota failure");
  }

  {
    // Calibrate an exact private prefix, then place the work ceiling at that
    // prefix so later drain work fails after the physical update has begun.
    auto calibration_options = options();
    calibration_options.mode = DeltaMode::maintenance;
    DeltaRuntime calibration{make_alias_separator_plan(), calibration_options};
    seed_alias_plan(calibration);
    const auto bootstrap = calibration.set_mode(DeltaMode::delta);
    const auto sequence = calibration.sequence();
    auto sample = calibration.begin({sequence + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
    while (true) {
      const auto result = sample.step();
      if (result == DeltaStep::core_result) break;
      check(result != DeltaStep::prepared,
            "work quota calibration produced no accepted core prefix");
    }
    const auto prefix_work = sample.metrics().work;
    const auto bootstrap_work = bootstrap.work;
    sample.drain();
    const auto full_work = sample.metrics().work;
    const auto work_ceiling = std::max(prefix_work, bootstrap_work);
    check(full_work > work_ceiling,
          "work quota fixture has no remaining work after both bootstrap and core prefix");
    auto sample_result = sample.commit();
    sample_result.discard();

    auto limited_options = options();
    limited_options.work_limit = work_ceiling;
    limited_options.mode = DeltaMode::maintenance;
    DeltaRuntime runtime{make_alias_separator_plan(), limited_options};
    seed_alias_plan(runtime);
    const auto limited_bootstrap = runtime.set_mode(DeltaMode::delta);
    check(limited_bootstrap.work <= work_ceiling,
          "limited work fixture could not bootstrap below its calibrated work ceiling");
    const auto before = snapshot_image(runtime);
    const auto live_before = runtime.live_snapshot();
    const auto stats_before = runtime.storage_statistics();
    const auto limited_sequence = runtime.sequence();
    const auto answer = runtime.has_answer();
    auto pending = runtime.begin({limited_sequence + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
    while (true) {
      const auto result = pending.step();
      if (result == DeltaStep::core_result) break;
      check(result != DeltaStep::prepared,
            "work quota fixture prepared before reaching its calibrated prefix");
    }
    check(pending.metrics().work == prefix_work,
          "work quota fixture did not reproduce its calibrated partial prefix");
    bool limited = false;
    try {
      pending.drain();
    } catch (const Error& failure) {
      limited = failure.code() == "resource_limit";
    }
    check(limited && !pending.active() && pending.state() == DeltaState::aborted,
          "work quota failure after partial progress did not abort the whole epoch");
    check_unchanged(runtime, before, live_before, stats_before, limited_sequence, answer,
                    "late work quota failure");
  }

  {
    auto no_output = options(0, 0);
    no_output.mode = DeltaMode::maintenance;
    DeltaRuntime runtime{make_alias_separator_plan(), no_output};
    seed_alias_plan(runtime);
    static_cast<void>(runtime.set_mode(DeltaMode::delta));
    const auto sequence = runtime.sequence();
    auto pending = runtime.begin({sequence + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
    pending.start_drain();
    pending.drain();
    check(pending.state() == DeltaState::epoch_prepared &&
              pending.metrics().accepted > 0 && pending.metrics().discarded_records > 0 &&
              pending.metrics().spool_rows == 0,
          "drain/discard did not finish internal work while bypassing the zero output quota");
    auto discarded = pending.commit();
    check(discarded.sequence() == sequence + 1 && discarded.remaining() == 0 && runtime.ready(),
          "zero-quota discard did not commit a private input without an output lease");
    runtime.check_invariants();
  }
}

void burn_for(std::chrono::milliseconds duration) {
  const auto end = std::chrono::steady_clock::now() + duration;
  while (std::chrono::steady_clock::now() < end) {}
}

void test_serializer_callback_lifecycle_and_timing() {
  DeltaRuntime runtime{make_alias_separator_plan(), options()};
  seed_alias_plan(runtime);
  auto output = runtime.apply({runtime.sequence() + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
  struct CodecFailure {};
  std::size_t serializers = 0, sinks = 0;
  const std::function<void(const SignedResult&)> throwing_serializer = [&](const SignedResult&) {
    ++serializers;
    throw CodecFailure{};
  };
  const std::function<void(const SignedResult&)> sink = [&](const SignedResult&) { ++sinks; };
  bool threw = false;
  {
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    try {
      static_cast<void>(output.deliver_one(throwing_serializer, sink));
    } catch (const CodecFailure&) {
      threw = true;
    }
  }
  const auto after_codec_failure = output.timings();
  check(threw && serializers == 1 && sinks == 0 && output.active() && output.remaining() == 3 &&
            after_codec_failure.serialization_ns > 0 && after_codec_failure.sink_wait_ns == 0,
        "serializer failure called the sink, consumed the front, or mixed callback timing phases");

  const std::function<void(const SignedResult&)> serializer = [&](const SignedResult&) {
    ++serializers;
    burn_for(std::chrono::milliseconds(2));
  };
  const std::function<void(const SignedResult&)> successful_sink = [&](const SignedResult&) {
    ++sinks;
    burn_for(std::chrono::milliseconds(2));
  };
  check(output.deliver_one(serializer, successful_sink),
        "successful serializer/sink callbacks did not acknowledge their front row");
  const auto after_success = output.timings();
  check(serializers == 2 && sinks == 1 && output.remaining() == 2 &&
            after_success.serialization_ns > after_codec_failure.serialization_ns &&
            after_success.sink_wait_ns > after_codec_failure.sink_wait_ns,
        "serializer and sink callbacks were not timed in separate accumulated phases");
  output.discard();
  runtime.check_invariants();
}

void test_delivery_callback_lifecycle() {
  {
    DeltaRuntime runtime{make_alias_separator_plan(), options()};
    seed_alias_plan(runtime);
    const auto sequence = runtime.sequence();
    auto output = runtime.apply({sequence + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
    const auto remaining = output.remaining();
    struct SinkFailure {};
    std::uint64_t thrown_ordinal = 0;
    const std::function<void(const SignedResult&)> throwing_sink = [&](const SignedResult& row) {
      thrown_ordinal = row.ordinal;
      throw SinkFailure{};
    };
    bool threw = false;
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      try {
        static_cast<void>(output.deliver_one(throwing_sink));
      } catch (const SinkFailure&) {
        threw = true;
      }
    }
    check(threw && output.active() && output.remaining() == remaining &&
              thrown_ordinal == 1 && !runtime.ready() && runtime.sequence() == sequence + 1,
          "throwing sink consumed the front record or released the committed output lease");
    std::uint64_t next_ordinal = thrown_ordinal;
    bool valid = true;
    std::vector<RecordImage> delivered_records;
    delivered_records.reserve(remaining);
    const std::function<void(const SignedResult&)> retry_sink = [&](const SignedResult& row) {
      valid = valid && row.ordinal == next_ordinal++ && row.operation == SetOperation::insert &&
              row.tuple.values().size() == 3;
      delivered_records.push_back({row.ordinal, row.operation, crown::storage::export_row(row.tuple.values())});
    };
    while (output.deliver_one(retry_sink)) {}
    check(valid && next_ordinal > 1 && !output.active() && runtime.ready(),
          "callback retry did not deliver contiguous original ordinals or release its lease");
    auto next_input = runtime.apply({runtime.sequence() + 1, TableId{0}, SetOperation::insert, edge(3, 4)});

    DeltaRuntime clean{make_alias_separator_plan(), options()};
    seed_alias_plan(clean);
    auto clean_first = clean.apply({clean.sequence() + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
    const auto clean_records = records(clean_first);
    check(delivered_records == clean_records,
          "retry after a throwing callback did not reproduce the exact clean output rows");
    clean_first.discard();
    auto clean_next = clean.apply({clean.sequence() + 1, TableId{0}, SetOperation::insert, edge(3, 4)});
    check(next_input.input().input.sequence == clean_next.input().input.sequence &&
              next_input.sequence() == clean_next.sequence() && clean_records.size() == remaining &&
              records(next_input) == records(clean_next) &&
              same_logical_snapshot(snapshot_image(runtime), snapshot_image(clean)),
          "retrying delivery changed the following clean input result or runtime snapshot");
    next_input.discard();
    clean_next.discard();
    runtime.check_invariants();
    clean.check_invariants();
  }

  {
    DeltaRuntime runtime{make_alias_separator_plan(), options()};
    seed_alias_plan(runtime);
    auto output = runtime.apply({runtime.sequence() + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
    std::uint64_t ordinal = 0;
    bool kept_front_valid = false;
    std::optional<DeltaRuntime::Epoch> replacement;
    const std::function<void(const SignedResult&)> move_sink = [&](const SignedResult& front) {
      ordinal = front.ordinal;
      replacement.emplace(std::move(output));
      kept_front_valid = front.ordinal == ordinal && front.operation == SetOperation::insert &&
                         front.tuple.values().size() == 3;
    };
    bool delivered = false;
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      delivered = output.deliver_one(move_sink);
    }
    check(delivered && kept_front_valid && ordinal == 1 && replacement && replacement->active() &&
              replacement->remaining() == 2 && !output.active() && !runtime.ready(),
          "moving the epoch in its sink invalidated the borrowed front or delivery acknowledgement");
    replacement->discard();
    check(runtime.ready(), "discard after callback move did not release the original shared output lease");
  }

  {
    DeltaRuntime runtime{make_alias_separator_plan(), options()};
    seed_alias_plan(runtime);
    auto output = runtime.apply({runtime.sequence() + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
    bool called = false;
    const std::function<void(const SignedResult&)> discard_sink = [&](const SignedResult& row) {
      called = row.ordinal == 1;
      output.discard();  // The request is deferred until this borrowed row is released.
    };
    bool delivered = false;
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      delivered = output.deliver_one(discard_sink);
    }
    check(delivered && called && !output.active() && output.remaining() == 0 && runtime.ready(),
          "callback-triggered discard was not safely deferred until callback unwind");
    runtime.check_invariants();
  }

  {
    DeltaRuntime runtime{make_alias_separator_plan(), options()};
    seed_alias_plan(runtime);
    auto output = runtime.apply({runtime.sequence() + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
    std::size_t callbacks = 0;
    const std::function<void(const SignedResult&)> reentrant_sink = [&](const SignedResult&) {
      ++callbacks;
      static_cast<void>(output.next());
    };
    expect_error([&] { static_cast<void>(output.deliver_one(reentrant_sink)); }, "runtime_busy");
    check(callbacks == 1 && output.remaining() == 3 && output.active(),
          "reentrant next consumed a record while deliver_one owned the front row");
    output.discard();
    runtime.check_invariants();
  }
}

void test_discard_faults_and_drain_quotas() {
  constexpr std::ptrdiff_t max_points = 8192;
  std::size_t failures = 0;
  for (std::ptrdiff_t point = 0; point < max_points; ++point) {
    DeltaRuntime runtime{make_alias_separator_plan(), options()};
    seed_alias_plan(runtime);
    const auto before = snapshot_image(runtime);
    const auto live_before = runtime.live_snapshot();
    const auto stats_before = runtime.storage_statistics();
    const auto sequence = runtime.sequence();
    const auto answer = runtime.has_answer();
    auto pending = runtime.begin({sequence + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
    static_cast<void>(pending.step());
    pending.pause();

    bool failed = false;
    std::optional<DeltaRuntime::Epoch> discarded;
    {
      FaultScope fault(point);
      try {
        discarded.emplace(pending.discard());
      } catch (const std::bad_alloc&) {
        failed = true;
        fail_after = 0;
      }
    }
    if (failed) {
      ++failures;
      check(!pending.active() && pending.state() == DeltaState::aborted,
            "faulted discard left a ghost pending epoch");
      check_unchanged(runtime, before, live_before, stats_before, sequence, answer,
                      "paused discard ordinary-new fault sweep");
      auto retry = runtime.begin({sequence + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
      retry.drain();
      auto result = retry.commit();
      DeltaRuntime clean{make_alias_separator_plan(), options()};
      seed_alias_plan(clean);
      auto clean_result = clean.apply({sequence + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
      check_retry_matches_clean(runtime, result, clean, clean_result, sequence + 1,
                                "paused discard ordinary-new fault sweep");
      result.discard();
      clean_result.discard();
      continue;
    }

    check(failures > 0, "paused discard ordinary-new fault sweep injected no failure");
    check(discarded && discarded->sequence() == sequence + 1 &&
              discarded->remaining() == 0 && !discarded->active() && runtime.ready(),
          "successful paused discard did not commit an empty public epoch");
    check(discarded->metrics().accepted > 0 && discarded->metrics().discarded_records > 0,
          "successful paused discard skipped required internal work or omitted discard accounting");
    runtime.check_invariants();
    std::cout << "paused discard ordinary-new failures=" << failures << '\n';
    return;
  }
  throw std::runtime_error("paused discard ordinary-new fault sweep exceeded fault points");
}

void test_prepare_commit_and_state_errors() {
  DeltaRuntime runtime{make_alias_separator_plan(), options()};
  seed_alias_plan(runtime);
  const auto sequence = runtime.sequence();
  auto pending = runtime.begin({sequence + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
  expect_error([&] { static_cast<void>(pending.commit()); }, "runtime_busy");
  check(pending.active() && runtime.state() == DeltaState::pending_delta,
        "early commit misuse aborted or advanced the pending epoch");
  pending.drain();
  check(pending.state() == DeltaState::epoch_prepared && runtime.state() == DeltaState::epoch_prepared,
        "drain did not expose the prepared commit barrier");
  auto result = [&] {
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    return pending.commit();
  }();
  check(result.sequence() == sequence + 1 && runtime.state() == DeltaState::committed_output,
        "prepared commit with ordinary scalar/array global new forced to fail did not publish and lease the output");
  result.discard();
  check(runtime.ready(), "prepared commit output discard did not restore writer readiness");
  runtime.check_invariants();
}

}  // namespace

int main() {
  try {
    sweep_begin_failures(
        [] { return DeltaRuntime{make_alias_separator_plan(), options()}; },
        seed_alias_plan, "multi-alias");
    sweep_first_step_failures(seed_alias_plan, "selected-cursor first step");
    sweep_resumed_cursor_failures();
    sweep_paused_drain_failures();
    test_stage_prefix_rollback_and_aliases();
    test_noalloc_pending_lifecycle();
    test_quota_failures_after_partial_progress();
    test_serializer_callback_lifecycle_and_timing();
    test_delivery_callback_lifecycle();
    test_discard_faults_and_drain_quotas();
    test_prepare_commit_and_state_errors();
    std::cout << "DeltaRuntime pending epoch failure, rollback, drain, commit, and delivery lifecycle checks passed\n";
  } catch (const std::exception& failure) {
    fail_after = -1;
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
