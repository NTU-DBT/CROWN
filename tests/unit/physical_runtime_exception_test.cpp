#include "crown/api/error.hpp"
#include "crown/io/document.hpp"
#include "crown/io/support.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/physical.hpp"

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

// Keep this injector local to the executable. The noinline wrapper prevents
// GCC's replaceable-new mismatch warning around the custom global operators.
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

static_assert(std::is_nothrow_move_constructible_v<PhysicalRuntime::PendingUpdate>);
static_assert(std::is_nothrow_move_assignable_v<PhysicalRuntime::PendingUpdate>);
static_assert(std::is_nothrow_move_constructible_v<PhysicalRuntime>);
static_assert(std::is_nothrow_move_assignable_v<PhysicalRuntime>);

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

Value n(std::int64_t value) { return value; }
Value s(std::string value) { return value; }

const Row& row_a() {
  static const Row value{n(10), n(1), s("source-row-a")};
  return value;
}
const Row& row_b() {
  static const Row value{n(10), n(1), s("source-row-b")};
  return value;
}
const Row& row_c() {
  static const Row value{n(10), n(2), s("source-row-c")};
  return value;
}

PhysicalPlan make_plan() {
  Catalog catalog{1, {{"R", {{"x", ScalarType::int64}, {"y", ScalarType::int64},
                              {"witness", ScalarType::string}}}}};
  Query query{
      {{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"left", TableId{0}, {VariableId{0}, VariableId{1}, IgnoredColumn{}}},
       {"right", TableId{0}, {VariableId{0}, VariableId{1}, IgnoredColumn{}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "y"}}, false};
  FreeConnexTree tree{NodeId{0}, {
      {"root", NodeKind::generalized, {VariableId{0}, VariableId{1}}, {NodeId{1}, NodeId{2}}, {}, {}},
      {"left", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}},
      {"right", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalRuntimeOptions options() {
  PhysicalRuntimeOptions result;
  result.support.capture_transitions = true;
  return result;
}

enum class Scenario { insert_new_projection, erase_last_projection, insert_existing_projection,
                      erase_shared_projection };

SetOperation operation(Scenario scenario) {
  return scenario == Scenario::insert_new_projection || scenario == Scenario::insert_existing_projection
             ? SetOperation::insert
             : SetOperation::erase;
}

PhysicalSetUpdate target_update(const PhysicalRuntime& runtime, Scenario scenario) {
  const Row& values = scenario == Scenario::insert_new_projection ? row_c() :
                      scenario == Scenario::erase_last_projection ? row_a() : row_b();
  return {runtime.sequence() + 1, TableId{0}, operation(scenario), values};
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

io::Json row_json(const Row& values) {
  auto result = io::Json::array();
  for (const auto& value : values) result.push_back(io::write_scalar(value));
  return result;
}

std::string operation_name(SetOperation operation_value) {
  return operation_value == SetOperation::insert ? "insert" : "erase";
}

io::Json preview_image(const PhysicalPreview& preview) {
  const auto& metrics = preview.metrics;
  auto derivations = io::Json::array();
  for (const auto& change : preview.derivations)
    derivations.push_back({{"occurrence", change.occurrence.value}, {"node", change.node.value},
                           {"tuple", row_json(crown::storage::export_row(change.tuple.values()))}, {"before", change.before},
                           {"after", change.after}, {"native_changed", change.native_changed}});

  io::Json source = nullptr;
  if (preview.source) {
    const auto& handle = preview.source->handle;
    source = {{"handle", {{"owner", 0}, {"relation", handle.relation.value}, {"tuple", handle.tuple.value}}},
              {"tuple", row_json(storage::export_row(preview.source->tuple().values()))}};
  }
  return {{"sequence", preview.sequence}, {"table", preview.table.value},
          {"operation", operation_name(preview.operation)}, {"physical_changed", preview.physical_changed},
          {"metrics", {{"work", metrics.work}, {"source_changes", metrics.source_changes},
                        {"aliases_visited", metrics.aliases_visited}, {"aliases_filtered", metrics.aliases_filtered},
                        {"derivation_changes", metrics.derivation_changes}, {"native_crossings", metrics.native_crossings},
                        {"constraint_rows", metrics.constraint_rows},
                        {"constraint_validations", metrics.constraint_validations}}},
          {"source", std::move(source)}, {"derivations", std::move(derivations)}};
}

io::Json epoch_image(const PhysicalEpoch& epoch) {
  return {{"input", preview_image(epoch.input)},
          {"support", normalized_owners(io::write_support_epoch(epoch.support))}};
}

struct DerivationImage {
  Row values;
  std::uint64_t count;
  bool operator==(const DerivationImage&) const = default;
};
struct SnapshotImage {
  std::uint64_t sequence;
  std::vector<Relation> physical;
  io::Json support;
  std::vector<std::vector<DerivationImage>> derivations;
  bool operator==(const SnapshotImage& other) const {
    return sequence == other.sequence && physical == other.physical && support == other.support &&
           derivations == other.derivations;
  }
};

SnapshotImage snapshot_image(const PhysicalRuntime& runtime) {
  const auto snapshot = runtime.snapshot();
  SnapshotImage result{snapshot.sequence, snapshot.physical.tables,
                       normalized_owners(io::write_support_snapshot(snapshot.support, runtime.plan())), {}};
  result.derivations.resize(snapshot.derivations.size());
  for (std::size_t i = 0; i < snapshot.derivations.size(); ++i) {
    for (const auto& derivation : snapshot.derivations[i])
      result.derivations[i].push_back({crown::storage::export_row(derivation.tuple.values()), derivation.count});
  }
  return result;
}

struct SourceHandleImage {
  TableId table;
  TupleHandle handle;
  Row values;
  bool operator==(const SourceHandleImage&) const = default;
};
struct SupportHandleImage {
  SupportHandle handle;
  Row values;
  bool operator==(const SupportHandleImage&) const = default;
};
struct PublicHandles {
  std::vector<SourceHandleImage> source;
  std::vector<SupportHandleImage> support;
  bool operator==(const PublicHandles&) const = default;
};

PublicHandles public_handles(const PhysicalRuntime& runtime) {
  const auto snapshot = runtime.snapshot();
  PublicHandles result;
  for (std::size_t table = 0; table < snapshot.physical.tables.size(); ++table) {
    for (const auto& row : snapshot.physical.tables[table]) {
      const auto handle = runtime.find_source(TableId{table}, row);
      check(handle.has_value(), "source snapshot row has no public source handle");
      const auto stored = runtime.get_source(TableId{table}, *handle);
      check(stored && stored->values() == row, "source handle does not resolve to its complete physical row");
      result.source.push_back({TableId{table}, *handle, row});
    }
  }

  const auto add_support = [&](SupportHandle handle, const storage::Tuple& value) {
    const auto stored = runtime.get_support(handle);
    check(stored && stored->layout().same_token(value.layout()) && stored->values() == value.values(),
          "support snapshot handle does not resolve to its tuple");
    result.support.push_back({handle, crown::storage::export_row(value.values())});
  };
  for (const auto& node : snapshot.support.nodes) {
    for (const auto& record : node.records) add_support(record.handle, record.tuple);
    for (const auto& tuple : node.survivors) {
      const auto handle = runtime.find_support(node.node, SupportRole::survivors, crown::storage::export_row(tuple.values()));
      check(handle.has_value(), "support survivor has no public handle");
      add_support(*handle, tuple);
    }
    for (const auto& key : node.parent_keys) add_support(key.handle, key.key);
    if (node.visible_keys)
      for (const auto& key : *node.visible_keys) add_support(key.handle, key.key);
  }
  return result;
}

struct HeldEpoch {
  PhysicalEpoch epoch;
  TupleHandle source_handle{};
  ArenaHandle source_pin{};
  Row source_values;
  io::Json logical;
  std::vector<Row> journal_values;

  explicit HeldEpoch(PhysicalEpoch value) : epoch(std::move(value)) {
    check(epoch.input.source.has_value(), "fixture commit did not retain its full source row");
    source_handle = epoch.input.source->handle;
    source_pin = epoch.input.source->retained.handle();
    source_values = storage::export_row(epoch.input.source->tuple().values());
    logical = normalized_owners(io::write_support_epoch(epoch.support));
    if (epoch.support.journal)
      for (const auto& record : epoch.support.journal->records) journal_values.push_back(storage::export_row(record.tuple().values()));
  }
};
using HeldEpochs = std::vector<HeldEpoch>;

void check_held(const HeldEpochs& held, const std::string& context) {
  for (const auto& image : held) {
    check(image.epoch.input.source && image.epoch.input.source->handle == image.source_handle &&
              image.epoch.input.source->retained.handle() == image.source_pin &&
              image.epoch.input.source->tuple().values() == image.source_values,
          context + ": a committed source-row pin changed or lost its tuple");
    check(normalized_owners(io::write_support_epoch(image.epoch.support)) == image.logical,
          context + ": an older committed logical journal changed");
    std::vector<Row> rows;
    if (image.epoch.support.journal)
      for (const auto& record : image.epoch.support.journal->records) rows.push_back(storage::export_row(record.tuple().values()));
    check(rows == image.journal_values, context + ": an older logical journal lost or changed a pinned tuple");
  }
}

void hold(HeldEpochs& held, PhysicalEpoch epoch) { held.emplace_back(std::move(epoch)); }

std::uint64_t initialize(PhysicalRuntime& runtime, Scenario scenario, HeldEpochs& held) {
  hold(held, runtime.apply({1, TableId{0}, SetOperation::insert, row_a()}));
  if (scenario != Scenario::insert_existing_projection)
    hold(held, runtime.apply({2, TableId{0}, SetOperation::insert, row_b()}));
  if (scenario == Scenario::erase_last_projection)
    hold(held, runtime.apply({3, TableId{0}, SetOperation::erase, row_b()}));
  const std::uint64_t expected_count = scenario == Scenario::insert_existing_projection ? 1 :
                                       scenario == Scenario::erase_last_projection ? 1 : 2;
  check(runtime.derivation_count(OccurrenceId{0}, Row{n(10), n(1)}) == expected_count &&
            runtime.derivation_count(OccurrenceId{1}, Row{n(10), n(1)}) == expected_count,
        "full source rows did not induce the expected final-native projection count");
  runtime.check_invariants();
  check_held(held, "physical fixture initialization");
  return runtime.sequence();
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

void check_rollback_statistics(const PhysicalStorageStatistics& before,
                               const PhysicalStorageStatistics& after,
                               const std::string& context) {
  const auto check_arena = [&](const storage::ArenaStatistics& old_stats,
                               const storage::ArenaStatistics& new_stats, std::string_view name) {
    check(old_stats.live_records == new_stats.live_records &&
              old_stats.retained_records == new_stats.retained_records && old_stats.pins == new_stats.pins,
          context + ": failed physical epoch changed " + std::string(name) + " live/retained tuple counts or pins");
    check(new_stats.slots >= old_stats.slots,
          context + ": rollback unexpectedly reduced " + std::string(name) + " arena high-water slots");
  };
  check_arena(before.source, after.source, "source");
  check_arena(before.support, after.support, "support");
  check(before.derivation_keys == after.derivation_keys,
        context + ": failed physical epoch changed the committed derivation-key count");
}

void check_unchanged(PhysicalRuntime& runtime, const SnapshotImage& before,
                     const PublicHandles& handles, const PhysicalStorageStatistics& stats,
                     std::uint64_t sequence, bool answer, SupportOwnerId owner,
                     const HeldEpochs& held, const std::string& context) {
  check(runtime.ready() && runtime.sequence() == sequence && runtime.has_answer() == answer && runtime.owner() == owner,
        context + ": failed update changed readiness, sequence, answer state or owner");
  check(snapshot_image(runtime) == before, context + ": failed update changed the physical/logical snapshot or counts");
  check(public_handles(runtime) == handles, context + ": failed update changed a public source/support handle");
  check_rollback_statistics(stats, runtime.storage_statistics(), context);
  check_held(held, context);
  runtime.check_invariants();
}

void check_busy_readers(PhysicalRuntime& runtime, const PhysicalRuntime::PendingUpdate& pending,
                        std::uint64_t sequence, const PublicHandles& handles) {
  check(!runtime.ready() && runtime.sequence() == sequence,
        "opening a physical update published its tentative sequence or reported ready");
  check(pending.preview().physical_changed && pending.preview().source &&
            pending.preview().derivations.size() == 2 && pending.preview().metrics.aliases_visited == 2,
        "physical preview did not include the full source update and both alias derivations");
  check(pending.snapshot().sequence == sequence + 1,
        "private physical snapshot omitted the tentative sequence");
  const auto source = handles.source.front();
  const auto support = handles.support.front();
  expect_error([&] { static_cast<void>(runtime.has_answer()); }, "runtime_busy");
  expect_error([&] { static_cast<void>(runtime.snapshot()); }, "runtime_busy");
  expect_error([&] { static_cast<void>(runtime.derivation_count(OccurrenceId{0}, Row{n(10), n(1)})); }, "runtime_busy");
  expect_error([&] { static_cast<void>(runtime.find_source(source.table, source.values)); }, "runtime_busy");
  expect_error([&] { static_cast<void>(runtime.get_source(source.table, source.handle)); }, "runtime_busy");
  expect_error([&] { static_cast<void>(runtime.find_support(support.handle.node, support.handle.role, support.values)); },
               "runtime_busy");
  expect_error([&] { static_cast<void>(runtime.get_support(support.handle)); }, "runtime_busy");
  expect_error([&] { static_cast<void>(runtime.storage_statistics()); }, "runtime_busy");
  expect_error([&] { runtime.check_invariants(); }, "runtime_busy");
}

struct ExpectedResult {
  SnapshotImage snapshot;
  io::Json epoch;
};

ExpectedResult clean_result(const PhysicalPlan& plan, Scenario scenario) {
  PhysicalRuntime runtime{plan, options()};
  HeldEpochs held;
  static_cast<void>(initialize(runtime, scenario, held));
  const auto epoch = runtime.apply(target_update(runtime, scenario));
  check(epoch.input.physical_changed && epoch.input.source && epoch.input.derivations.size() == 2,
        "clean physical update did not report both aliases and a source change");
  const std::uint64_t before = scenario == Scenario::insert_new_projection ? 0 :
                               scenario == Scenario::insert_existing_projection ? 1 :
                               scenario == Scenario::erase_last_projection ? 1 : 2;
  const std::uint64_t after = scenario == Scenario::insert_new_projection ||
                                      scenario == Scenario::insert_existing_projection ? before + 1 : before - 1;
  const bool crossing = scenario == Scenario::insert_new_projection ||
                        scenario == Scenario::erase_last_projection;
  for (std::size_t i = 0; i < epoch.input.derivations.size(); ++i) {
    const auto& change = epoch.input.derivations[i];
    check(change.occurrence == OccurrenceId{i} && change.before == before && change.after == after &&
              change.native_changed == crossing,
          "physical alias preview did not report the expected final-native count transition");
  }
  check(epoch.support.native_changed == crossing,
        "logical support commit did not match the final-native zero crossing");
  check(runtime.sequence() == epoch.input.sequence && runtime.ready(), "clean physical update did not commit");
  check_held(held, "clean physical update");
  runtime.check_invariants();
  return {snapshot_image(runtime), epoch_image(epoch)};
}

struct SweepResult {
  std::size_t failures = 0;
  std::size_t prepare_failures = 0;
  std::size_t commit_failures = 0;
};

SweepResult sweep(const PhysicalPlan& plan, Scenario scenario) {
  constexpr std::ptrdiff_t max_points = 8192;
  const auto expected = clean_result(plan, scenario);
  SweepResult counts;

  for (std::ptrdiff_t step = 0; step < max_points; ++step) {
    PhysicalRuntime runtime{plan, options()};
    HeldEpochs held;
    const auto sequence = initialize(runtime, scenario, held);
    const auto before = snapshot_image(runtime);
    const auto answer = runtime.has_answer();
    const auto owner = runtime.owner();
    const auto handles = public_handles(runtime);
    const auto storage_before = runtime.storage_statistics();
    const auto update = target_update(runtime, scenario);

    bool failed = false;
    bool failed_during_prepare = false;
    bool failed_during_commit = false;
    std::optional<PhysicalRuntime::PendingUpdate> pending;
    std::optional<PhysicalEpoch> result;
    {
      FaultScope fault(step);
      try {
        pending.emplace(runtime.prepare(update));
        result.emplace(pending->commit());
        pending.reset();
      } catch (const std::bad_alloc&) {
        failed = true;
        fail_after = 0;  // Keep failure armed while any returned token unwinds.
        failed_during_prepare = !pending.has_value();
        failed_during_commit = pending.has_value();
        pending.reset();
      }
    }

    if (failed) {
      ++counts.failures;
      if (failed_during_prepare) ++counts.prepare_failures;
      if (failed_during_commit) ++counts.commit_failures;
      check(failed_during_prepare && !failed_during_commit,
            "physical commit allocated or failed after prepare returned its token");
      check_unchanged(runtime, before, handles, storage_before, sequence, answer, owner, held,
                      "physical allocation sweep");

      // The same complete source-row update and sequence must be reusable.
      const auto retry = runtime.apply(update);
      check(epoch_image(retry) == expected.epoch && snapshot_image(runtime) == expected.snapshot,
            "retry of a failed physical epoch differed from a clean run modulo owners");
      check_held(held, "physical allocation sweep retry");
      runtime.check_invariants();
      continue;
    }

    check(counts.failures > 0,
          "physical allocation sweep reached success without injecting bad_alloc");
    check(result && epoch_image(*result) == expected.epoch && snapshot_image(runtime) == expected.snapshot,
          "first successful physical update differed from a clean run modulo owners");
    check_held(held, "successful physical allocation sweep");
    runtime.check_invariants();
    return counts;
  }
  throw std::runtime_error("physical allocation sweep exceeded 8192 fault points");
}

void check_explicit_rollback_is_noalloc(const PhysicalPlan& plan) {
  PhysicalRuntime runtime{plan, options()};
  HeldEpochs held;
  const auto sequence = initialize(runtime, Scenario::insert_new_projection, held);
  const auto before = snapshot_image(runtime);
  const auto handles = public_handles(runtime);
  const auto stats = runtime.storage_statistics();
  const auto answer = runtime.has_answer();
  const auto owner = runtime.owner();
  auto pending = runtime.prepare(target_update(runtime, Scenario::insert_new_projection));
  {
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    pending.rollback();
  }
  check(!pending.active(), "explicit physical rollback left its token active");
  check_unchanged(runtime, before, handles, stats, sequence, answer, owner, held,
                  "no-allocation physical rollback");
  expect_error([&] { static_cast<void>(pending.commit()); }, "invalid_epoch");
}

void check_destructor_cancellation_is_noalloc(const PhysicalPlan& plan) {
  PhysicalRuntime runtime{plan, options()};
  HeldEpochs held;
  const auto sequence = initialize(runtime, Scenario::insert_new_projection, held);
  const auto before = snapshot_image(runtime);
  const auto handles = public_handles(runtime);
  const auto stats = runtime.storage_statistics();
  const auto answer = runtime.has_answer();
  const auto owner = runtime.owner();
  bool remained_active = false;
  {
    FaultScope no_allocations;
    {
      auto pending = runtime.prepare(target_update(runtime, Scenario::insert_new_projection));
      no_allocations.forbid_allocations();
      remained_active = pending.active();
    }
  }
  check(remained_active, "destructor fixture did not prepare an active physical update");
  check_unchanged(runtime, before, handles, stats, sequence, answer, owner, held,
                  "no-allocation physical token destructor");
}

void check_move_assignment_is_noalloc(const PhysicalPlan& plan) {
  PhysicalRuntime destination_runtime{plan, options()};
  PhysicalRuntime source_runtime{plan, options()};
  HeldEpochs destination_held, source_held;
  const auto destination_sequence = initialize(destination_runtime, Scenario::insert_new_projection, destination_held);
  const auto source_sequence = initialize(source_runtime, Scenario::insert_new_projection, source_held);
  const auto destination_before = snapshot_image(destination_runtime);
  const auto source_before = snapshot_image(source_runtime);
  const auto destination_handles = public_handles(destination_runtime);
  const auto source_handles = public_handles(source_runtime);
  const auto destination_stats = destination_runtime.storage_statistics();
  const auto source_stats = source_runtime.storage_statistics();
  const auto destination_answer = destination_runtime.has_answer();
  const auto source_answer = source_runtime.has_answer();
  const auto destination_owner = destination_runtime.owner();
  const auto source_owner = source_runtime.owner();

  auto destination = destination_runtime.prepare(target_update(destination_runtime, Scenario::insert_new_projection));
  auto source = source_runtime.prepare(target_update(source_runtime, Scenario::insert_new_projection));
  bool transferred = false;
  {
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    destination = std::move(source);
    transferred = !source.active() && destination.active();
    destination.rollback();
  }
  check(transferred, "physical pending move assignment did not transfer its active token");
  check(!destination.active() && destination_runtime.ready() && source_runtime.ready(),
        "physical pending move assignment failed to cancel both updates");
  check_unchanged(destination_runtime, destination_before, destination_handles, destination_stats,
                  destination_sequence, destination_answer, destination_owner, destination_held,
                  "physical move-assignment destination");
  check_unchanged(source_runtime, source_before, source_handles, source_stats, source_sequence,
                  source_answer, source_owner, source_held, "physical move-assignment source");
  expect_error([&] { static_cast<void>(destination.commit()); }, "invalid_epoch");
}

void check_facade_destruction_with_active_update(const PhysicalPlan& plan) {
  std::optional<PhysicalRuntime::PendingUpdate> pending;
  HeldEpochs held;
  {
    PhysicalRuntime runtime{plan, options()};
    static_cast<void>(initialize(runtime, Scenario::insert_new_projection, held));
    pending.emplace(runtime.prepare(target_update(runtime, Scenario::insert_new_projection)));
    check(pending->active(), "facade-destruction fixture did not retain an active physical update");
  }
  {
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    pending->rollback();
  }
  check(!pending->active(), "active physical update could not roll back after facade destruction");
  check_held(held, "physical facade destruction");
  expect_error([&] { static_cast<void>(pending->commit()); }, "invalid_epoch");
}

void check_commit_after_facade_destruction_is_noalloc(const PhysicalPlan& plan) {
  std::optional<PhysicalRuntime::PendingUpdate> pending;
  std::optional<PhysicalEpoch> output;
  HeldEpochs held;
  {
    PhysicalRuntime runtime{plan, options()};
    static_cast<void>(initialize(runtime, Scenario::insert_new_projection, held));
    pending.emplace(runtime.prepare(target_update(runtime, Scenario::insert_new_projection)));
  }
  bool closed = false;
  {
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    output.emplace(pending->commit());
    closed = !pending->active();
  }
  check(output.has_value() && closed,
        "active physical update could not commit without allocation after facade destruction");
  held.emplace_back(std::move(*output));
  check(held.back().source_values == row_c() && held.back().epoch.support.journal != nullptr,
        "facade-free commit lost its source pin or logical journal");
  check_held(held, "physical commit after facade destruction");
  expect_error([&] { static_cast<void>(pending->commit()); }, "invalid_epoch");
}

void check_commit_is_noalloc(const PhysicalPlan& plan) {
  PhysicalRuntime runtime{plan, options()};
  HeldEpochs held;
  static_cast<void>(initialize(runtime, Scenario::insert_new_projection, held));
  const auto expected = clean_result(plan, Scenario::insert_new_projection);
  auto pending = runtime.prepare(target_update(runtime, Scenario::insert_new_projection));
  std::optional<PhysicalEpoch> output;
  {
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    output.emplace(pending.commit());
  }
  check(output && !pending.active() && runtime.ready(), "no-allocation physical commit did not close its token");
  check(epoch_image(*output) == expected.epoch && snapshot_image(runtime) == expected.snapshot,
        "no-allocation physical commit differed from its clean result");
  check_held(held, "no-allocation physical commit");
  expect_error([&] { static_cast<void>(pending.commit()); }, "invalid_epoch");
  runtime.check_invariants();
}

void check_staged_output_exception_cancels(const PhysicalPlan& plan, Scenario scenario) {
  PhysicalRuntime runtime{plan, options()};
  HeldEpochs held;
  const auto sequence = initialize(runtime, scenario, held);
  const auto before = snapshot_image(runtime);
  const auto handles = public_handles(runtime);
  const auto stats = runtime.storage_statistics();
  const auto answer = runtime.has_answer();
  const auto owner = runtime.owner();
  const auto update = target_update(runtime, scenario);
  auto pending = runtime.prepare(update);
  check_busy_readers(runtime, pending, sequence, handles);

  bool output_failed = false;
  {
    FaultScope no_allocations(0);
    try {
      // This models a caller building its private output before commit. The
      // copy allocates; its failure must leave cancellation available.
      std::vector<DerivationChange> staged_output(pending.preview().derivations.begin(), pending.preview().derivations.end());
      static_cast<void>(staged_output);
    } catch (const std::bad_alloc&) {
      output_failed = true;
    }
  }
  check(output_failed && pending.active() && !runtime.ready() && runtime.sequence() == sequence,
        "staged-output allocation failure published or closed its physical update");
  expect_error([&] { static_cast<void>(runtime.snapshot()); }, "runtime_busy");
  expect_error([&] { static_cast<void>(runtime.find_source(TableId{0}, row_a())); }, "runtime_busy");
  expect_error([&] { static_cast<void>(runtime.storage_statistics()); }, "runtime_busy");
  {
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    pending.rollback();
  }
  check(!pending.active(), "staged-output exception rollback left the physical token active");
  check_unchanged(runtime, before, handles, stats, sequence, answer, owner, held,
                  "staged-output exception cancellation");
  const auto retry = runtime.apply(update);
  const auto expected = clean_result(plan, scenario);
  check(epoch_image(retry) == expected.epoch && snapshot_image(runtime) == expected.snapshot,
        "retry after staged-output cancellation differed from a clean result");
  check_held(held, "staged-output retry");
  runtime.check_invariants();
}

}  // namespace

int main() {
  try {
    const auto plan = make_plan();
    check_explicit_rollback_is_noalloc(plan);
    check_destructor_cancellation_is_noalloc(plan);
    check_move_assignment_is_noalloc(plan);
    check_facade_destruction_with_active_update(plan);
    check_commit_after_facade_destruction_is_noalloc(plan);
    check_commit_is_noalloc(plan);
    check_staged_output_exception_cancels(plan, Scenario::insert_new_projection);
    check_staged_output_exception_cancels(plan, Scenario::erase_last_projection);

    const auto insert_new = sweep(plan, Scenario::insert_new_projection);
    const auto erase_last = sweep(plan, Scenario::erase_last_projection);
    const auto insert_existing = sweep(plan, Scenario::insert_existing_projection);
    const auto erase_shared = sweep(plan, Scenario::erase_shared_projection);
    check(insert_new.prepare_failures > 0 && erase_last.prepare_failures > 0 &&
              insert_existing.prepare_failures > 0 && erase_shared.prepare_failures > 0,
          "physical fault sweeps missed bad_alloc during prepare/alias routing");
    check(insert_new.commit_failures == 0 && erase_last.commit_failures == 0 &&
              insert_existing.commit_failures == 0 && erase_shared.commit_failures == 0,
          "physical commit allocated under the exhaustive prepare fault sweep");
    std::cout << "physical runtime allocation rollback points: insert_new=" << insert_new.failures
              << " erase_last=" << erase_last.failures
              << " insert_projection_collision=" << insert_existing.failures
              << " erase_projection_collision=" << erase_shared.failures << '\n';
  } catch (const std::exception& failure) {
    fail_after = -1;
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
