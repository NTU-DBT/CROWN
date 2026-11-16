#include "crown/planner/lower.hpp"
#include "crown/runtime/delta.hpp"

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using namespace crown;
using namespace crown::runtime;

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

Value n(std::int64_t value) { return value; }

PhysicalPlan disconnected_product_plan(std::size_t arity) {
  Catalog catalog;
  catalog.version = 1;
  Query query;
  FreeConnexTree tree;
  tree.root = NodeId{0};
  std::vector<NodeId> children;
  for (std::size_t i = 0; i < arity; ++i) {
    query.variables.push_back({"x" + std::to_string(i), ScalarType::int64});
    query.atoms.push_back({"r" + std::to_string(i), TableId{i},
                           {VariableId{i}}});
    query.head.push_back({VariableId{i}, "x" + std::to_string(i)});
    catalog.tables.push_back({"r" + std::to_string(i),
                              {{"x", ScalarType::int64}}});
    children.push_back(NodeId{i + 1});
  }
  tree.nodes.push_back({"product", NodeKind::generalized, {}, children, {}, {}});
  for (std::size_t i = 0; i < arity; ++i) {
    VariableSet scope{VariableId{i}};
    tree.nodes.push_back({"r" + std::to_string(i), NodeKind::native,
                          std::move(scope), {}, i, {}});
  }
  return planner::lower_tree(catalog, query, tree);
}

Database product_database(std::size_t arity, std::size_t width) {
  Database database;
  database.tables.resize(arity);
  for (auto& table : database.tables) {
    for (std::size_t i = 0; i < width; ++i)
      table.insert({n(static_cast<std::int64_t>(i))});
  }
  return database;
}

std::size_t relation_rows(const std::vector<Relation>& relations) {
  std::size_t result = 0;
  for (const auto& relation : relations) result += relation.size();
  return result;
}

std::size_t count_keys(const std::vector<std::vector<CanonicalCount>>& counts) {
  std::size_t result = 0;
  for (const auto& relation : counts) result += relation.size();
  return result;
}

void check_canonical_reconciliation(const DeltaRuntime& runtime,
    const InvariantReport& report, const std::string& method) {
  const auto state = runtime.canonical_state();
  const auto storage = runtime.storage_statistics();
  const auto& statistics = report.statistics;
  check(state.live.has_value(), method + ": initialized delta state has no L");
  check(statistics.source_storage_records == storage.source.live_records,
        method + ": source live records do not reconcile with source arenas");
  check(statistics.support_storage_records == storage.support.live_records,
        method + ": support live records do not reconcile with support arenas");
  check(statistics.derivation_keys == storage.derivation_keys,
        method + ": derivation keys do not reconcile with physical storage stats");
  check(statistics.source_rows == relation_rows(state.physical.sources),
        method + ": inspected source rows differ from canonical source sets");
  check(statistics.derivation_keys == count_keys(state.physical.derivations),
        method + ": inspected derivation keys differ from canonical derivations");

  std::size_t native_records = 0;
  std::size_t generalized_records = 0;
  std::size_t survivors = 0;
  std::size_t parent_keys = 0;
  std::size_t visible_keys = 0;
  std::size_t child_flags = 0;
  for (const auto& node : state.physical.support.nodes) {
    if (node.kind == NodeKind::native) native_records += node.records.size();
    else generalized_records += node.records.size();
    survivors += node.survivors.size();
    parent_keys += node.parent.size();
    if (node.visible) visible_keys += node.visible->size();
    for (const auto& record : node.records)
      child_flags += record.child_present.size();
  }
  check(statistics.native_records == native_records,
        method + ": native record count differs from canonical node rows");
  check(statistics.generalized_records == generalized_records,
        method + ": generalized record count differs from canonical node rows");
  check(statistics.survivors == survivors,
        method + ": survivor count differs from canonical node rows");
  check(statistics.parent_keys == parent_keys,
        method + ": P key count differs from canonical node rows");
  check(statistics.visible_keys == visible_keys,
        method + ": E key count differs from canonical node rows");
  check(statistics.child_flags == child_flags,
        method + ": child flag count differs from canonical node rows");

  std::size_t live_rows = 0;
  std::size_t live_parent_rows = 0;
  std::size_t live_child_rows = 0;
  std::size_t live_parent_buckets = 0;
  std::size_t live_child_buckets = 0;
  for (const auto& factor : state.live->factors) {
    live_rows += factor.rows.size();
    live_parent_buckets += factor.parents.size();
    live_child_buckets += factor.children.size();
    for (const auto& bucket : factor.parents) {
      check(bucket.count == bucket.rows.size(),
            method + ": canonical parent bucket count differs from its rows");
      live_parent_rows += bucket.rows.size();
    }
    for (const auto& bucket : factor.children) {
      check(bucket.count == bucket.rows.size(),
            method + ": canonical child bucket count differs from its rows");
      live_child_rows += bucket.rows.size();
    }
  }
  check(state.live->rows == live_rows && statistics.live_rows == live_rows,
        method + ": L row total does not reconcile with canonical factors");
  check(state.live->parent_rows == live_parent_rows &&
            statistics.live_parent_rows == live_parent_rows &&
            statistics.live_parent_buckets == live_parent_buckets,
        method + ": parent bucket totals do not reconcile with canonical buckets");
  check(state.live->child_rows == live_child_rows &&
            statistics.live_child_rows == live_child_rows &&
            statistics.live_child_buckets == live_child_buckets,
        method + ": child bucket totals do not reconcile with canonical buckets");
}

std::size_t check_linear_state_and_print(const DeltaRuntime& runtime, std::size_t width,
    const std::string& method) {
  const auto report = runtime.inspect_invariants();
  check(report.complete && report.valid(),
        method + ": initialized state failed invariant inspection");
  check_canonical_reconciliation(runtime, report, method);

  const auto& statistics = report.statistics;
  const auto state = runtime.canonical_state();
  const std::size_t arity = runtime.plan().inputs().size();
  const auto input_rows = arity * width;
  check(statistics.source_rows == input_rows,
        method + ": source row count differs from the independent fixture size");
  check(statistics.derivation_keys <= input_rows &&
            statistics.native_records <= input_rows,
        method + ": source-derived state exceeded its fixed-query linear bound");
  check(!state.physical.support.nodes.empty(),
        method + ": canonical state omitted the multi-child support node");
  const auto& root = state.physical.support.nodes.front();
  check(root.kind == NodeKind::generalized && root.records.size() == 1 &&
            root.records.front().satisfied == arity &&
            root.records.front().child_present.size() == arity,
        method + ": multi-child generalized support projection is incorrect");
  for (const bool present : root.records.front().child_present)
    check(present, method + ": a populated child projection is absent");

  const auto total_record_count = statistics.source_storage_records +
      statistics.support_storage_records + statistics.live_rows +
      statistics.live_parent_rows + statistics.live_child_rows;
  check(total_record_count <= 32 * (1 + width),
        method + ": retained local records exceeded the fixed-query linear bound");

  const auto storage = runtime.storage_statistics();
  std::cout << "records method=" << method << " N=" << width
            << " source_rows=" << statistics.source_rows
            << " source_live=" << storage.source.live_records
            << " source_slots=" << storage.source.slots
            << " support_live=" << storage.support.live_records
            << " support_slots=" << storage.support.slots
            << " derivation_keys=" << statistics.derivation_keys
            << " native_records=" << statistics.native_records
            << " generalized_records=" << statistics.generalized_records
            << " survivors=" << statistics.survivors
            << " parent_keys=" << statistics.parent_keys
            << " visible_keys=" << statistics.visible_keys
            << " child_flags=" << statistics.child_flags
            << " live_rows=" << statistics.live_rows
            << " parent_bucket_rows=" << statistics.live_parent_rows
            << " parent_buckets=" << statistics.live_parent_buckets
            << " child_bucket_rows=" << statistics.live_child_rows
            << " child_buckets=" << statistics.live_child_buckets << '\n';
  return total_record_count;
}

struct RecordCounts {
  std::size_t direct;
  std::size_t replay;
};

RecordCounts compare_initialization_methods_at_scale(std::size_t width) {
  constexpr std::size_t arity = 2;
  const auto plan = disconnected_product_plan(arity);
  const auto database = product_database(arity, width);
  DeltaOptions options;
  options.mode = DeltaMode::delta;

  BuildOptions direct_build;
  direct_build.method = BuildMethod::direct;
  auto direct = DeltaRuntime::initialize(plan, database, options, direct_build);
  const auto& direct_metrics = direct.initialization_metrics();
  check(direct_metrics.replay_inputs == 0 && direct_metrics.replay_events == 0 &&
            direct_metrics.replay_work == 0,
        "direct initialization unexpectedly used insertion replay");
  const auto direct_records =
      check_linear_state_and_print(direct, width, "direct");

  BuildOptions replay_build;
  replay_build.method = BuildMethod::insertion_replay;
  auto replayed = DeltaRuntime::initialize(plan, database, options, replay_build);
  const auto& replay_metrics = replayed.initialization_metrics();
  check(replay_metrics.replay_inputs > 0 && replay_metrics.replay_events > 0 &&
            replay_metrics.replay_work > 0,
        "insertion replay did not report replay inputs, events and work");
  const auto replay_records =
      check_linear_state_and_print(replayed, width, "insertion_replay");
  check(direct.owner() != replayed.owner(),
        "direct and insertion-replay builds reused an owner");
  check(direct.canonical_state() == replayed.canonical_state(),
        "direct and insertion-replay canonical states differ");
  return {direct_records, replay_records};
}

void churn_rebuild_separates_live_rows_pins_and_arena_high_water() {
  constexpr std::size_t arity = 2;
  constexpr std::size_t width = 16;
  const auto plan = disconnected_product_plan(arity);
  const auto database = product_database(arity, width);
  auto runtime = PhysicalRuntime::initialize(plan, database);
  std::vector<storage::AccountedTupleArena::Pin> erased_source_pins;
  std::uint64_t sequence = runtime.sequence();

  for (std::size_t table = 0; table < arity; ++table) {
    for (std::size_t i = 0; i < width; ++i) {
      const Row row{n(static_cast<std::int64_t>(i))};
      auto epoch = runtime.apply({++sequence, TableId{table},
                                  SetOperation::erase, row});
      check(epoch.input.source.has_value(),
            "erase event did not retain its changed source row");
      erased_source_pins.push_back(
          std::move(epoch.input.source->retained));
    }
  }
  const auto empty_storage = runtime.storage_statistics();
  check(empty_storage.source.live_records == 0 &&
            empty_storage.source.retained_records > 0,
        "caller-held source pins were confused with live source records");

  for (std::size_t table = 0; table < arity; ++table) {
    for (std::size_t i = 0; i < width; ++i) {
      const Row row{n(static_cast<std::int64_t>(i))};
      auto epoch = runtime.apply({++sequence, TableId{table},
                                  SetOperation::insert, row});
      check(epoch.input.physical_changed,
            "churn insert did not restore source membership");
    }
  }
  const auto pinned_storage = runtime.storage_statistics();
  check(pinned_storage.source.live_records == arity * width &&
            pinned_storage.source.retained_records > 0 &&
            pinned_storage.source.slots > pinned_storage.source.live_records,
        "churn did not separate live source rows from retained pins and arena slots");
  const auto slots_before_release = pinned_storage.source.slots;

  erased_source_pins.clear();
  const auto released_storage = runtime.storage_statistics();
  check(released_storage.source.live_records == arity * width &&
            released_storage.source.retained_records == 0 &&
            released_storage.source.slots == slots_before_release,
        "releasing caller pins changed membership or hid arena high-water slots");

  auto rebuilt = runtime.rebuilt();
  const auto rebuilt_storage = rebuilt.storage_statistics();
  check(rebuilt.owner() != runtime.owner() &&
            rebuilt.sequence() == runtime.sequence(),
        "rebuild failed to create a new owner at the committed sequence");
  check(rebuilt.canonical_state() == runtime.canonical_state(),
        "rebuild changed canonical state after churn");
  check(rebuilt_storage.source.live_records == released_storage.source.live_records &&
            rebuilt_storage.source.retained_records == 0 &&
            rebuilt_storage.source.slots < released_storage.source.slots,
        "rebuild did not separate live state from the old owner's arena high-water");
  std::cout << "churn live_source=" << released_storage.source.live_records
            << " retained_after_release=" << released_storage.source.retained_records
            << " old_owner_slots=" << released_storage.source.slots
            << " rebuilt_live_source=" << rebuilt_storage.source.live_records
            << " rebuilt_slots=" << rebuilt_storage.source.slots << '\n';
}

}  // namespace

int main() {
  try {
    std::vector<RecordCounts> matrix;
    for (const auto width : {std::size_t{2}, std::size_t{16}, std::size_t{64}})
      matrix.push_back(compare_initialization_methods_at_scale(width));
    check(matrix.back().direct <= 8 * matrix[1].direct &&
              matrix.back().replay <= 8 * matrix[1].replay,
          "retained direct or replay records scaled faster than the fixed-query linear matrix");
    churn_rebuild_separates_live_rows_pins_and_arena_high_water();
    return 0;
  } catch (const std::exception& failure) {
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
