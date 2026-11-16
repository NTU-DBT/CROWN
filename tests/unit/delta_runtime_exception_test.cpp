#include "crown/api/error.hpp"
#include "crown/frontend/bind.hpp"
#include "crown/frontend/normalize.hpp"
#include "crown/io/document.hpp"
#include "crown/io/support.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/delta.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
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

// Keep failures armed while DeltaRuntime unwinds its private live image and
// output spool. Only ordinary throwing scalar/array new is directly replaced.
// There are no dedicated aligned/nothrow replacements; indirect delegation is
// not asserted. Direct malloc/realloc/system calls and MemoryAccount admission
// denials are outside this injected fault seam.
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
LiveMaintenance selected_policy=DeltaOptions{}.live_maintenance;

static_assert(std::is_nothrow_move_constructible_v<DeltaRuntime>);
static_assert(std::is_nothrow_move_assignable_v<DeltaRuntime>);
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

PhysicalPlan make_plan() {
  constexpr VariableId x{0}, z{1}, y{2};
  const Catalog catalog{17, {{"E", {{"x", ScalarType::int64}, {"z", ScalarType::int64}}}}};
  const Query query{
      {{"x", ScalarType::int64}, {"z", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"first", TableId{0}, {x, z}}, {"second", TableId{0}, {z, y}}},
      {{x, "x"}, {z, "z"}, {y, "y"}}, false};
  const FreeConnexTree tree{NodeId{0}, {
      {"first", NodeKind::native, {x, z}, {NodeId{1}}, 0, {}},
      {"second", NodeKind::native, {z, y}, {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
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

PhysicalPlan make_normalized_plan() {
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

PhysicalPlan make_exists_plan() {
  const Catalog catalog{19, {{"r", {{"x", ScalarType::int64}}}}};
  const auto binding = frontend::bind_sql("SELECT EXISTS(SELECT NULL FROM r)", catalog);
  if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&binding))
    throw std::runtime_error(failure->diagnostic.code + ": " + failure->diagnostic.message);
  auto normalized = frontend::normalize_sql(std::get<frontend::BoundSql>(binding));
  if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&normalized))
    throw std::runtime_error(failure->diagnostic.code + ": " + failure->diagnostic.message);
  auto program = std::get<frontend::NormalizedSql>(std::move(normalized));
  check(program.binding.wrapper == frontend::SqlWrapper::exists && program.core.atoms.size() == 1,
        "EXISTS fixture did not lower to one nullary core occurrence");
  const FreeConnexTree tree{NodeId{0}, {
      {program.core.atoms[0].occurrence, NodeKind::native, {}, {}, 0, {}}}, {}, {}};
  return planner::lower_normalized(program, tree);
}

DeltaOptions options(DeltaMode mode = DeltaMode::delta) {
  DeltaOptions result;
  result.mode = mode;
  result.live_maintenance = selected_policy;
  result.physical.support.capture_transitions = true;
  return result;
}

void apply_and_discard(DeltaRuntime& runtime, SetOperation operation, const Row& values) {
  auto output = runtime.apply({runtime.sequence() + 1, TableId{0}, operation, values});
  output.discard();
  check(runtime.ready(), "discarding a fixture epoch did not release its output lease");
}

void apply_and_discard_at(DeltaRuntime& runtime, TableId table,
                          SetOperation operation, const Row& values) {
  auto output = runtime.apply({runtime.sequence() + 1, table, operation, values});
  output.discard();
  check(runtime.ready(), "discarding a fixture epoch did not release its output lease");
}

void seed_base(DeltaRuntime& runtime, bool include_loop = false) {
  apply_and_discard(runtime, SetOperation::insert, edge(1, 2));
  apply_and_discard(runtime, SetOperation::insert, edge(2, 1));
  if (include_loop) apply_and_discard(runtime, SetOperation::insert, edge(1, 1));
}

const std::vector<Row>& loop_delta_rows() {
  static const std::vector<Row> rows{
      {n(1), n(1), n(1)}, {n(1), n(1), n(2)}, {n(2), n(1), n(1)}};
  return rows;
}

void check_output(DeltaRuntime::Epoch& epoch, DeltaRuntime& runtime,
                 SetOperation operation, const std::vector<Row>& expected) {
  check(epoch.sequence() == runtime.sequence(), "delta artifact sequence differs from its committed input");
  check(epoch.active() == !expected.empty() && epoch.remaining() == expected.size(),
        "delta artifact did not retain exactly its expected output lease and row count");
  std::vector<Row> rows;
  std::uint64_t next_ordinal = 1;
  while (auto record = epoch.next()) {
    check(record->operation == operation, "self-join delta record has the wrong sign");
    check(record->ordinal == next_ordinal++, "delta spool ordinals are not contiguous in acceptance order");
    rows.push_back(crown::storage::export_row(record->tuple.values()));
  }
  std::sort(rows.begin(), rows.end());
  check(rows == expected, "self-join delta output differs from the exact expected signed set");
  check(!epoch.active() && epoch.remaining() == 0 && runtime.ready(),
        "delivering the last committed delta row did not release the output lease");
  check(epoch.metrics().spool_rows == expected.size(), "spool row metric differs from delivered row count");
  check(epoch.input().support.journal != nullptr,
        "delivered artifact lost its committed support audit journal");
  runtime.check_invariants();
}

struct DerivationImage {
  Row values;
  std::uint64_t count;
  bool operator==(const DerivationImage&) const = default;
};
struct SnapshotImage {
  std::uint64_t sequence = 0;
  std::vector<Relation> physical;
  io::Json support;
  std::vector<std::vector<DerivationImage>> derivations;
  bool operator==(const SnapshotImage&) const = default;
};

SnapshotImage snapshot_image(const DeltaRuntime& runtime) {
  const auto snapshot = runtime.snapshot();
  SnapshotImage result;
  result.sequence = snapshot.sequence;
  result.physical = snapshot.physical.tables;
  result.support = io::write_support_snapshot(snapshot.support, runtime.plan());
  result.derivations.resize(snapshot.derivations.size());
  for (std::size_t occurrence = 0; occurrence < snapshot.derivations.size(); ++occurrence) {
    for (const auto& derivation : snapshot.derivations[occurrence])
      result.derivations[occurrence].push_back({crown::storage::export_row(derivation.tuple.values()), derivation.count});
  }
  return result;
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
          std::string(context) + ": failed delta epoch changed committed " + std::string(name) +
              " records/pins or reduced arena high-water slots");
  };
  check_arena(before.source, after.source, "source");
  check_arena(before.support, after.support, "support");
  check(before.derivation_keys == after.derivation_keys,
        std::string(context) + ": failed delta epoch changed committed derivation-key count");
}

void check_unchanged(DeltaRuntime& runtime, const SnapshotImage& before,
                     const std::optional<LiveSnapshot>& live_before,
                     const PhysicalStorageStatistics& stats_before,
                     std::uint64_t sequence, bool answer, DeltaMode mode,
                     std::string_view context) {
  check(runtime.ready() && runtime.sequence() == sequence && runtime.has_answer() == answer &&
            runtime.mode() == mode,
        std::string(context) + ": failed delta epoch changed readiness, sequence, answer, or mode");
  check(snapshot_image(runtime) == before,
        std::string(context) + ": failed delta epoch changed physical rows, support counts, or derivations");
  check(same_live(runtime.live_snapshot(), live_before),
        std::string(context) + ": failed delta epoch changed committed live factors");
  check_stats(stats_before, runtime.storage_statistics(), context);
  runtime.check_invariants();
}

enum class LoopChange { insert, erase };

SetOperation sign(LoopChange change) {
  return change == LoopChange::insert ? SetOperation::insert : SetOperation::erase;
}

void prepare_change(DeltaRuntime& runtime, LoopChange change) {
  seed_base(runtime, change == LoopChange::erase);
}

std::size_t sweep_change_failures(LoopChange change) {
  const auto expected_sign = sign(change);
  std::size_t failures = 0;
  constexpr std::ptrdiff_t max_points = 8192;
  for (std::ptrdiff_t step = 0; step < max_points; ++step) {
    DeltaRuntime runtime{make_plan(), options()};
    prepare_change(runtime, change);
    const auto before = snapshot_image(runtime);
    const auto live_before = runtime.live_snapshot();
    const auto stats_before = runtime.storage_statistics();
    const auto sequence = runtime.sequence();
    const auto answer = runtime.has_answer();
    const PhysicalSetUpdate update{sequence + 1, TableId{0}, expected_sign, edge(1, 1)};

    bool failed = false;
    std::optional<DeltaRuntime::Epoch> output;
    {
      FaultScope fault(step);
      try {
        output.emplace(runtime.apply(update));
      } catch (const std::bad_alloc&) {
        failed = true;
        fail_after = 0;  // Keep all private rollback cleanup under persistent failure.
      }
    }

    if (failed) {
      ++failures;
      check_unchanged(runtime, before, live_before, stats_before, sequence, answer,
                      DeltaMode::delta, "self-join ordinary-new failure sweep");
      auto retry = runtime.apply(update);
      check_output(retry, runtime, expected_sign, loop_delta_rows());
      continue;
    }

    check(failures > 0, "self-join ordinary-new failure sweep did not inject bad_alloc");
    check(output.has_value(), "successful self-join ordinary-new failure sweep returned no artifact");
    check_output(*output, runtime, expected_sign, loop_delta_rows());
    std::cout << (change == LoopChange::insert ? "insert" : "delete")
              << " self-join ordinary-new failures=" << failures << '\n';
    return failures;
  }
  throw std::runtime_error("self-join ordinary-new failure sweep exceeded 8192 fault points");
}

void seed_shared_separator(DeltaRuntime& runtime) {
  apply_and_discard_at(runtime, TableId{0}, SetOperation::insert, {n(1), n(7)});
  apply_and_discard_at(runtime, TableId{0}, SetOperation::insert, {n(2), n(7)});
  apply_and_discard_at(runtime, TableId{1}, SetOperation::insert, {n(7), n(9)});
  const auto live = runtime.live_snapshot();
  check(live && live->factors.size() == 2 &&
            live->factors[0] == Relation{{n(1), n(7)}, {n(2), n(7)}} &&
            live->factors[1] == Relation{{n(7), n(9)}},
        "shared-separator fixture did not start with two live parents and one child key");
  runtime.check_invariants();
}

void sweep_shared_separator_delete_failures() {
  constexpr std::ptrdiff_t max_points = 8192;
  const std::vector<Row> expected{{n(1), n(7), n(9)}, {n(2), n(7), n(9)}};
  std::size_t failures = 0;
  for (std::ptrdiff_t step = 0; step < max_points; ++step) {
    DeltaRuntime runtime{make_shared_separator_plan(), options()};
    seed_shared_separator(runtime);
    const auto before = snapshot_image(runtime);
    const auto live_before = runtime.live_snapshot();
    const auto stats_before = runtime.storage_statistics();
    const auto sequence = runtime.sequence();
    const auto answer = runtime.has_answer();
    const PhysicalSetUpdate update{
        sequence + 1, TableId{1}, SetOperation::erase, {n(7), n(9)}};

    bool failed = false;
    std::optional<DeltaRuntime::Epoch> output;
    {
      FaultScope fault(step);
      try {
        output.emplace(runtime.apply(update));
      } catch (const std::bad_alloc&) {
        failed = true;
        fail_after = 0;  // Keep rollback cleanup under persistent failure.
      }
    }

    if (failed) {
      ++failures;
      check_unchanged(runtime, before, live_before, stats_before, sequence,
                      answer, DeltaMode::delta, "shared-separator ordinary-new failure sweep");
      auto retry = runtime.apply(update);
      check_output(retry, runtime, SetOperation::erase, expected);
      continue;
    }

    check(failures > 0,
          "shared-separator ordinary-new failure sweep did not inject bad_alloc");
    check(output.has_value(),
          "successful shared-separator ordinary-new failure sweep returned no artifact");
    check_output(*output, runtime, SetOperation::erase, expected);
    std::cout << "shared-separator deletion ordinary-new failures=" << failures
              << " first success fault point=" << step << '\n';
    return;
  }
  throw std::runtime_error(
      "shared-separator ordinary-new failure sweep exceeded 8192 fault points");
}

void check_mode_bootstrap_failure_sweep() {
  std::size_t failures = 0;
  constexpr std::ptrdiff_t max_points = 8192;
  for (std::ptrdiff_t step = 0; step < max_points; ++step) {
    DeltaRuntime runtime{make_plan(), options(DeltaMode::maintenance)};
    seed_base(runtime);
    const auto before = snapshot_image(runtime);
    const auto stats_before = runtime.storage_statistics();
    const auto sequence = runtime.sequence();
    const auto answer = runtime.has_answer();

    bool failed = false;
    {
      FaultScope fault(step);
      try {
        static_cast<void>(runtime.set_mode(DeltaMode::delta));
      } catch (const std::bad_alloc&) {
        failed = true;
        fail_after = 0;
      }
    }
    if (failed) {
      ++failures;
      check(runtime.mode() == DeltaMode::maintenance && !runtime.live_snapshot(),
            "failed delta bootstrap installed a partial live image or changed mode");
      check_unchanged(runtime, before, {}, stats_before, sequence, answer,
                      DeltaMode::maintenance, "mode-bootstrap ordinary-new failure sweep");

      static_cast<void>(runtime.set_mode(DeltaMode::delta));
      const auto live = runtime.live_snapshot();
      check(runtime.mode() == DeltaMode::delta && live && live->sequence == runtime.sequence() &&
                live->factors.size() == 2,
            "successful retry after bootstrap bad_alloc did not install the complete live image");
      auto retry = runtime.apply({runtime.sequence() + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
      check_output(retry, runtime, SetOperation::insert, loop_delta_rows());
      continue;
    }

    check(failures > 0, "mode-bootstrap ordinary-new failure sweep did not inject bad_alloc");
    const auto live = runtime.live_snapshot();
    check(runtime.mode() == DeltaMode::delta && live && live->sequence == sequence &&
              live->factors.size() == 2,
          "successful delta bootstrap did not tag every live factor with the committed sequence");
    check(runtime.bootstrap_metrics().live_rows > 0,
          "successful bootstrap omitted its rebuilt live-row metrics");
    runtime.check_invariants();
    std::cout << "mode bootstrap ordinary-new failures=" << failures << '\n';
    return;
  }
  throw std::runtime_error("mode-bootstrap ordinary-new failure sweep exceeded 8192 fault points");
}

void check_spool_limit_atomicity(std::size_t row_limit, std::size_t byte_limit,
                                 std::string_view label) {
  auto config = options(DeltaMode::maintenance);
  config.spool_row_limit = row_limit;
  config.spool_byte_limit = byte_limit;
  DeltaRuntime runtime{make_plan(), config};
  seed_base(runtime);  // No spool is used while maintenance mode is active.
  static_cast<void>(runtime.set_mode(DeltaMode::delta));
  const auto before = snapshot_image(runtime);
  const auto live_before = runtime.live_snapshot();
  const auto stats_before = runtime.storage_statistics();
  const auto sequence = runtime.sequence();
  const auto answer = runtime.has_answer();

  expect_error([&] {
    static_cast<void>(runtime.apply({sequence + 1, TableId{0}, SetOperation::insert, edge(1, 1)}));
  }, "resource_limit");
  check_unchanged(runtime, before, live_before, stats_before, sequence, answer,
                  DeltaMode::delta, label);
}

void check_exists_sql_row(const DeltaRuntime& runtime, bool expected) {
  auto cursor = runtime.results();
  const auto row = cursor.next();
  check(row && row->values().size() == 1 && std::get<bool>(row->values()[0]) == expected,
        "EXISTS SQL result did not retain its expected Boolean row");
  check(!cursor.next(), "EXISTS SQL result emitted more than one Boolean row");
}

void check_exists_flip_output(DeltaRuntime::Epoch& output, DeltaRuntime& runtime) {
  check(output.remaining() == 2 && output.active(),
        "EXISTS false-to-true transition did not prepare both replacement rows");
  const auto erased = output.next();
  const auto inserted = output.next();
  check(erased && erased->ordinal == 1 && erased->operation == SetOperation::erase &&
            erased->tuple.values().size() == 1 && !std::get<bool>(erased->tuple.values()[0]),
        "EXISTS false-to-true transition did not erase the old false row first");
  check(inserted && inserted->ordinal == 2 && inserted->operation == SetOperation::insert &&
            inserted->tuple.values().size() == 1 && std::get<bool>(inserted->tuple.values()[0]),
        "EXISTS false-to-true transition did not insert the new true row second");
  check(!output.active() && output.remaining() == 0 && runtime.ready(),
        "delivering the EXISTS replacement did not release its output lease");
}

void check_exists_mapping_spool_failure_is_atomic() {
  auto config = options();
  config.spool_row_limit = 1;
  DeltaRuntime runtime{make_exists_plan(), config};
  const auto before = snapshot_image(runtime);
  const auto live_before = runtime.live_snapshot();
  const auto stats_before = runtime.storage_statistics();
  const auto sequence = runtime.sequence();
  const auto answer = runtime.has_answer();
  check(!answer && runtime.mode() == DeltaMode::delta,
        "EXISTS late-spool fixture did not start at false in delta mode");
  check_exists_sql_row(runtime, false);

  const PhysicalSetUpdate update{sequence + 1, TableId{0}, SetOperation::insert, Row{n(1)}};
  std::optional<DeltaRuntime::Epoch> returned;
  expect_error([&] { returned.emplace(runtime.apply(update)); }, "resource_limit");
  check(!returned.has_value(), "late EXISTS spool rejection returned a partial artifact");
  check_unchanged(runtime, before, live_before, stats_before, sequence, false,
                  DeltaMode::delta, "late EXISTS mapping spool failure");
  check_exists_sql_row(runtime, false);

  // The same input with room for both replacement records proves the rejected
  // quota lay between the old-false erase and new-true insert appends.
  DeltaRuntime clean{make_exists_plan(), options()};
  auto expected = clean.apply(update);
  check_exists_flip_output(expected, clean);
}

void check_zero_spool_limits_allow_empty_output() {
  auto config = options(DeltaMode::maintenance);
  config.spool_row_limit = 0;
  config.spool_byte_limit = 0;
  DeltaRuntime runtime{make_plan(), config};
  seed_base(runtime);
  static_cast<void>(runtime.set_mode(DeltaMode::delta));
  const auto before = snapshot_image(runtime);
  const auto live_before = runtime.live_snapshot();
  check(live_before.has_value(), "zero-spool no-op fixture has no committed live image");
  const auto sequence = runtime.sequence();
  auto output = runtime.apply({sequence + 1, TableId{0}, SetOperation::insert, edge(1, 2)});
  check(output.input().input.sequence == sequence + 1 && !output.input().input.physical_changed &&
            output.remaining() == 0 && !output.active() && output.metrics().spool_rows == 0 && runtime.ready(),
        "zero spool budgets rejected or retained a genuinely empty duplicate-insert epoch");
  const auto after = snapshot_image(runtime);
  auto expected_support = before.support;
  expected_support["sequence"] = sequence + 1;
  check(after.physical == before.physical && after.derivations == before.derivations &&
            after.support == expected_support,
        "empty zero-spool epoch changed physical rows, support counts, or derivation counts");
  const auto live_after = runtime.live_snapshot();
  check(live_after && live_after->sequence == sequence + 1 &&
            live_after->factors == live_before->factors,
        "empty zero-spool epoch did not advance the live sequence without changing L");
  runtime.check_invariants();
}

void check_bootstrap_cursor_limit_preserves_maintenance() {
  auto config = options(DeltaMode::maintenance);
  config.cursor.work_limit = 0;
  DeltaRuntime runtime{make_plan(), config};
  seed_base(runtime);
  const auto before = snapshot_image(runtime);
  const auto stats_before = runtime.storage_statistics();
  const auto sequence = runtime.sequence();
  const auto answer = runtime.has_answer();
  expect_error([&] { static_cast<void>(runtime.set_mode(DeltaMode::delta)); }, "resource_limit");
  check(runtime.mode() == DeltaMode::maintenance && !runtime.live_snapshot(),
        "cursor work-limit bootstrap failure changed maintenance mode or installed live rows");
  check_unchanged(runtime, before, {}, stats_before, sequence, answer,
                  DeltaMode::maintenance, "cursor-limit bootstrap");
}

void check_active_output_blocks_input_and_mode_switch() {
  DeltaRuntime runtime{make_plan(), options()};
  seed_base(runtime);
  auto output = runtime.apply({runtime.sequence() + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
  const auto committed_sequence = runtime.sequence();
  check(output.active() && output.remaining() == 3 && !runtime.ready(),
        "nonempty committed delta did not hold the session output lease");
  expect_error([&] { static_cast<void>(runtime.apply({committed_sequence + 1, TableId{0},
      SetOperation::insert, edge(3, 4)})); }, "runtime_busy");
  expect_error([&] { static_cast<void>(runtime.set_mode(DeltaMode::maintenance)); }, "runtime_busy");
  check(runtime.sequence() == committed_sequence && runtime.mode() == DeltaMode::delta && !runtime.ready(),
        "blocked input or mode switch changed the committed output epoch");
  output.discard();
  check(runtime.ready() && runtime.sequence() == committed_sequence,
        "discarding committed output did not permit the next input");
  runtime.check_invariants();
}

void check_delivery_and_discard_are_allocation_free() {
  {
    DeltaRuntime runtime{make_plan(), options()};
    seed_base(runtime);
    auto output = runtime.apply({runtime.sequence() + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
    bool values_ok = true;
    std::size_t count = 0;
    std::uint64_t ordinal = 1;
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      while (auto record = output.next()) {
        values_ok = values_ok && record->operation == SetOperation::insert &&
            record->ordinal == ordinal++ && record->tuple.values().size() == 3 &&
            std::get<std::int64_t>(record->tuple.values()[0]) >= 1;
        ++count;
      }
    }
    check(values_ok && count == 3 && !output.active() && output.remaining() == 0 && runtime.ready(),
          "ordinary-new guard did not move every committed row and release the output lease");
    check(output.input().support.journal != nullptr && output.input().input.source &&
              output.input().input.source->tuple().values() == edge(1, 1),
          "delivery cleanup dropped the physical source/support audit pins");
    runtime.check_invariants();
  }

  {
    DeltaRuntime runtime{make_plan(), options()};
    seed_base(runtime);
    auto output = runtime.apply({runtime.sequence() + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
    const auto committed_sequence = runtime.sequence();
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      output.discard();
    }
    check(!output.active() && runtime.ready() && runtime.sequence() == committed_sequence &&
              output.input().support.journal != nullptr,
          "ordinary-new guard rolled back input or failed to release its output lease");
    runtime.check_invariants();
  }
}

void check_facade_move_and_destruction_with_active_output() {
  {
    DeltaRuntime original{make_plan(), options()};
    seed_base(original);
    auto output = original.apply({original.sequence() + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
    DeltaRuntime moved{std::move(original)};
    check(!moved.ready() && output.active(), "moving the facade detached its committed output lease");
    check_output(output, moved, SetOperation::insert, loop_delta_rows());
  }

  {
    std::optional<DeltaRuntime::Epoch> output;
    {
      DeltaRuntime runtime{make_plan(), options()};
      seed_base(runtime);
      output.emplace(runtime.apply({runtime.sequence() + 1, TableId{0}, SetOperation::insert, edge(1, 1)}));
      check(output->active() && !runtime.ready(), "destruction fixture did not retain active committed output");
    }
    bool rows_ok = true;
    std::size_t count = 0;
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      while (auto record = output->next()) {
        rows_ok = rows_ok && record->operation == SetOperation::insert && record->ordinal == count + 1;
        ++count;
      }
    }
    check(rows_ok && count == 3 && !output->active() && output->input().support.journal != nullptr,
          "active output requested intercepted ordinary new or could not finish after facade destruction");
  }

  {
    std::optional<DeltaRuntime::Epoch> output;
    {
      DeltaRuntime runtime{make_plan(), options()};
      seed_base(runtime);
      output.emplace(runtime.apply({runtime.sequence() + 1, TableId{0}, SetOperation::insert, edge(1, 1)}));
    }
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      output->discard();
    }
    check(!output->active() && output->input().input.source &&
              output->input().input.source->tuple().values() == edge(1, 1),
          "active output requested intercepted ordinary new or could not be discarded after facade destruction");
  }
}

void check_final_epoch_and_plan_destruction_are_allocation_free() {
  {
    std::optional<DeltaRuntime::Epoch> output;
    {
      DeltaRuntime runtime{make_plan(), options()};
      seed_base(runtime);
      output.emplace(runtime.apply({runtime.sequence() + 1, TableId{0}, SetOperation::insert, edge(1, 1)}));
      check(output->active(), "final-epoch destruction fixture has no committed delta output");
    }
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      output.reset();
    }
    check(!output.has_value(), "final epoch destruction requested intercepted ordinary new or retained its output token");
  }

  {
    std::optional<PhysicalPlan> plan;
    plan.emplace(make_plan());
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      plan.reset();
    }
    check(!plan.has_value(), "direct PhysicalPlan destruction requested intercepted ordinary new or failed");
  }

  {
    std::optional<PhysicalPlan> plan;
    plan.emplace(make_normalized_plan());
    check(plan->normalized().has_value(), "normalized identity teardown fixture lacks SQL metadata");
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      plan.reset();
    }
    check(!plan.has_value(), "nested SQL canonical identity destruction requested intercepted ordinary new or failed");
  }
}

void check_finite_work_limit_preserves_input() {
  auto calibration_options = options(DeltaMode::maintenance);
  DeltaRuntime calibration{make_plan(), calibration_options};
  seed_base(calibration);
  const auto bootstrap = calibration.set_mode(DeltaMode::delta);
  const auto bootstrap_work = bootstrap.work;
  auto clean = calibration.apply({calibration.sequence() + 1, TableId{0}, SetOperation::insert, edge(1, 1)});
  const auto clean_work = clean.metrics().work;
  clean.discard();
  check(clean_work > bootstrap_work,
        "self-join fixture does not provide a work limit between bootstrap and update costs");

  auto limited_options = options(DeltaMode::maintenance);
  limited_options.work_limit = bootstrap_work;
  DeltaRuntime limited{make_plan(), limited_options};
  seed_base(limited);
  static_cast<void>(limited.set_mode(DeltaMode::delta));
  const auto before = snapshot_image(limited);
  const auto live_before = limited.live_snapshot();
  const auto stats_before = limited.storage_statistics();
  const auto sequence = limited.sequence();
  const auto answer = limited.has_answer();
  expect_error([&] {
    static_cast<void>(limited.apply({sequence + 1, TableId{0}, SetOperation::insert, edge(1, 1)}));
  }, "resource_limit");
  check_unchanged(limited, before, live_before, stats_before, sequence, answer,
                  DeltaMode::delta, "finite delta work limit");
}

}  // namespace

int main(int argc,char** argv) {
  try {
    if (argc==2 && std::string_view(argv[1])=="eager") selected_policy=LiveMaintenance::eager;
    else if (argc==2 && std::string_view(argv[1])=="incremental") selected_policy=LiveMaintenance::incremental;
    else check(argc==1,"expected no argument, eager or incremental live policy");
    std::cout<<"live_policy="<<(selected_policy==LiveMaintenance::eager?"eager":
        selected_policy==LiveMaintenance::on_output?"on_output":"incremental")<<'\n';
    const auto insert_failures = sweep_change_failures(LoopChange::insert);
    const auto delete_failures = sweep_change_failures(LoopChange::erase);
    static_cast<void>(insert_failures);
    static_cast<void>(delete_failures);
    sweep_shared_separator_delete_failures();
    check_mode_bootstrap_failure_sweep();
    check_spool_limit_atomicity(2, 64 * 1024 * 1024, "row spool limit");
    check_spool_limit_atomicity(65536, 1, "byte spool limit");
    check_exists_mapping_spool_failure_is_atomic();
    check_zero_spool_limits_allow_empty_output();
    check_bootstrap_cursor_limit_preserves_maintenance();
    check_active_output_blocks_input_and_mode_switch();
    check_delivery_and_discard_are_allocation_free();
    check_facade_move_and_destruction_with_active_output();
    check_final_epoch_and_plan_destruction_are_allocation_free();
    check_finite_work_limit_preserves_input();
    std::cout << "DeltaRuntime ordinary-new rollback, bounded spool, mode bootstrap, and output lifecycle checks passed\n";
  } catch (const std::exception& failure) {
    fail_after = -1;
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
