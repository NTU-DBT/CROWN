#include "crown/planner/lower.hpp"
#include "crown/runtime/delta.hpp"
#include "evaluator.hpp"
#include "native_input.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <initializer_list>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace {
using namespace crown;
using namespace crown::runtime;
using SignedKey = std::pair<SetOperation, Row>;

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

Value n(std::int64_t value) { return value; }

VariableSet variables(std::initializer_list<std::size_t> values) {
  VariableSet result;
  for (const auto value : values) result.insert(VariableId{value});
  return result;
}

DeltaOptions options(LiveMaintenance maintenance) {
  DeltaOptions result;
  result.mode = DeltaMode::maintenance;
  result.live_maintenance = maintenance;
  result.completion = DeltaCompletion::anchored;
  return result;
}

Relation a04(const auto& plan, const Database& database) {
  return reference::evaluate(reference::input::catalog(plan.catalog()), reference::input::query(plan.query()), database);
}

std::set<SignedKey> difference(const Relation& before, const Relation& after) {
  std::set<SignedKey> result;
  for (const auto& row : after)
    if (!before.contains(row)) result.emplace(SetOperation::insert, row);
  for (const auto& row : before)
    if (!after.contains(row)) result.emplace(SetOperation::erase, row);
  return result;
}

std::set<SignedKey> drain(DeltaRuntime::Epoch& epoch) {
  std::set<SignedKey> rows;
  while (auto record = epoch.next()) {
    check(rows.emplace(record->operation, crown::storage::export_row(record->tuple.values())).second,
          "delta epoch emitted a duplicate operation/row pair");
  }
  check(epoch.remaining() == 0 && !epoch.active(),
        "delta epoch did not release its output lease");
  check(!epoch.next(), "exhausted delta epoch returned another record");
  return rows;
}

std::vector<Relation> a04_live(const auto& plan,
                               const Relation& answer) {
  std::map<VariableId, std::size_t> head_positions;
  for (std::size_t field = 0; field < plan.query().head.size(); ++field)
    head_positions.try_emplace(plan.query().head[field].variable, field);

  std::vector<Relation> result;
  result.reserve(plan.enumeration().steps.size());
  for (const auto& step : plan.enumeration().steps) {
    const auto& scope = plan.nodes().at(step.node.value).visible_scope;
    Relation factor;
    for (const auto& assignment : answer) {
      Row key;
      key.reserve(scope.size());
      for (const auto variable : scope) {
        const auto position = head_positions.find(variable);
        check(position != head_positions.end(),
              "A04 answer head omits a variable from a visible E scope");
        key.push_back(assignment.at(position->second));
      }
      factor.insert(std::move(key));
    }
    result.push_back(std::move(factor));
  }
  return result;
}

std::size_t rows(const std::vector<Relation>& factors) {
  std::size_t result = 0;
  for (const auto& factor : factors) result += factor.size();
  return result;
}

void check_live(const DeltaRuntime& runtime, const Database& database,
                const std::string& label) {
  const auto snapshot = runtime.live_snapshot();
  check(snapshot.has_value(), label + ": delta mode has no live snapshot");
  check(snapshot->sequence == runtime.sequence(),
        label + ": live snapshot sequence is stale");
  check(snapshot->factors == a04_live(runtime.plan(), a04(runtime.plan(), database)),
        label + ": live factors differ from independent A04 projections");
  runtime.check_invariants();
}

void check_stage_signatures(const std::vector<DeltaStage>& left,
                            const std::vector<DeltaStage>& right,
                            const std::string& label) {
  check(left.size() == right.size(), label + ": route stage count differs");
  for (std::size_t i = 0; i < left.size(); ++i) {
    const auto& a = left[i];
    const auto& b = right[i];
    check(a.occurrence == b.occurrence && a.prefix == b.prefix &&
              a.before_answer == b.before_answer &&
              a.after_answer == b.after_answer &&
              a.changed_keys == b.changed_keys &&
              a.candidates == b.candidates && a.accepted == b.accepted &&
              a.rejected == b.rejected && a.output_begin == b.output_begin &&
              a.output_count == b.output_count && a.live_rows == b.live_rows,
          label + ": route stage signature differs at index " +
              std::to_string(i));
  }
}

void check_on_output_metrics(const DeltaMetrics& incremental,
                             const DeltaMetrics& on_output,
                             const std::string& label) {
  check(on_output.live_bucket_opens == 0 && on_output.live_bucket_rows == 0,
        label + ": on-output maintenance opened or visited a live E bucket");
  check(on_output.e_rows_scanned == 0 && on_output.parent_live_rows == 0,
        label + ": on-output maintenance scanned E keys or rebuilt parent counts");
  check(on_output.live_changes == incremental.live_changes &&
            on_output.live_inserts == incremental.live_inserts &&
            on_output.live_erases == incremental.live_erases,
        label + ": on-output L mutations differ from incremental maintenance");
  check(on_output.live_separator_updates ==
                incremental.live_separator_updates &&
            on_output.live_separator_crossings ==
                incremental.live_separator_crossings,
        label + ": on-output parent support counts differ from incremental maintenance");
}

PhysicalPlan root_child_plan() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}}},
       {"s", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}}},
       {"s", TableId{1}, {VariableId{0}, VariableId{1}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "y"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, variables({0}), {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, variables({0, 1}), {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan shared_separator_plan() {
  const Catalog catalog{1,
      {{"r", {{"a", ScalarType::int64}, {"x", ScalarType::int64}}},
       {"s", {{"x", ScalarType::int64}, {"z", ScalarType::int64}}}}};
  const Query query{{{"a", ScalarType::int64}, {"x", ScalarType::int64},
                     {"z", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"s", TableId{1}, {VariableId{1}, VariableId{2}}}},
      {{VariableId{0}, "a"}, {VariableId{1}, "x"}, {VariableId{2}, "z"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, variables({0, 1}), {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, variables({1, 2}), {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan deep_chain_plan() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}},
       {"s", {{"y", ScalarType::int64}, {"z", ScalarType::int64}}},
       {"t", {{"z", ScalarType::int64}, {"w", ScalarType::int64}}},
       {"u", {{"w", ScalarType::int64}, {"q", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64},
                     {"z", ScalarType::int64}, {"w", ScalarType::int64},
                     {"q", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"s", TableId{1}, {VariableId{1}, VariableId{2}}},
       {"t", TableId{2}, {VariableId{2}, VariableId{3}}},
       {"u", TableId{3}, {VariableId{3}, VariableId{4}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "y"}, {VariableId{2}, "z"},
       {VariableId{3}, "w"}, {VariableId{4}, "q"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, variables({0, 1}), {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, variables({1, 2}), {NodeId{2}}, 1, {}},
       {"t", NodeKind::native, variables({2, 3}), {NodeId{3}}, 2, {}},
       {"u", NodeKind::native, variables({3, 4}), {}, 3, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan delayed_child_cleanup_plan() {
  const Catalog catalog{1,
      {{"r", {{"k", ScalarType::int64}}},
       {"p", {{"k", ScalarType::int64}, {"a", ScalarType::int64},
               {"x", ScalarType::int64}}},
       {"s", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}},
       {"t", {{"y", ScalarType::int64}, {"z", ScalarType::int64}}}}};
  const Query query{{{"k", ScalarType::int64}, {"a", ScalarType::int64},
                     {"x", ScalarType::int64}, {"y", ScalarType::int64},
                     {"z", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}}},
       {"p", TableId{1}, {VariableId{0}, VariableId{1}, VariableId{2}}},
       {"s", TableId{2}, {VariableId{2}, VariableId{3}}},
       {"t", TableId{3}, {VariableId{3}, VariableId{4}}}},
      {{VariableId{0}, "k"}, {VariableId{1}, "a"}, {VariableId{2}, "x"},
       {VariableId{3}, "y"}, {VariableId{4}, "z"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, variables({0}), {NodeId{1}}, 0, {}},
       {"p", NodeKind::native, variables({0, 1, 2}), {NodeId{2}}, 1, {}},
       {"s", NodeKind::native, variables({2, 3}), {NodeId{3}}, 2, {}},
       {"t", NodeKind::native, variables({3, 4}), {}, 3, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan coalesced_plan() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}}},
       {"s", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}}},
       {"s", TableId{1}, {VariableId{0}, VariableId{1}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "y"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"join", NodeKind::generalized, variables({0}), {NodeId{1}, NodeId{2}}, {}, {}},
       {"r", NodeKind::native, variables({0}), {}, 0, {}},
       {"s", NodeKind::native, variables({0, 1}), {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan product_plan(std::size_t arity) {
  Catalog catalog;
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
  for (std::size_t i = 0; i < arity; ++i)
    tree.nodes.push_back({"r" + std::to_string(i), NodeKind::native,
                          variables({i}), {}, i, {}});
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan same_scope_alias_plan() {
  const Catalog catalog{1,
      {{"edge", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"left", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"right", TableId{0}, {VariableId{0}, VariableId{1}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "y"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"join", NodeKind::generalized, variables({0, 1}), {NodeId{1}, NodeId{2}}, {}, {}},
       {"left", NodeKind::native, variables({0, 1}), {}, 0, {}},
       {"right", NodeKind::native, variables({0, 1}), {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

struct EpochPairResult {
  DeltaMetrics incremental;
  DeltaMetrics eager;
  DeltaMetrics on_output;
  std::vector<DeltaStage> incremental_stages;
  std::vector<DeltaStage> eager_stages;
  std::vector<DeltaStage> on_output_stages;
};

class RuntimePair {
 public:
  RuntimePair(PhysicalPlan incremental_plan, PhysicalPlan eager_plan,
              PhysicalPlan on_output_plan, std::size_t table_count)
      :incremental_(std::move(incremental_plan), options(LiveMaintenance::incremental)),
       eager_(std::move(eager_plan), options(LiveMaintenance::eager)),
       on_output_(std::move(on_output_plan), options(LiveMaintenance::on_output)) {
    database_.tables.resize(table_count);
  }

  void seed(TableId table, Row row) {
    PhysicalSetUpdate update{++sequence_, table, SetOperation::insert, row};
    auto incremental_epoch = incremental_.apply(update);
    auto eager_epoch = eager_.apply(update);
    auto on_output_epoch = on_output_.apply(update);
    check(drain(incremental_epoch).empty() && drain(eager_epoch).empty() &&
              drain(on_output_epoch).empty(),
          "maintenance seed unexpectedly returned delta output");
    check(database_.tables.at(table.value).insert(std::move(row)).second,
          "fixture seeded a duplicate physical row");
  }

  std::tuple<DeltaMetrics, DeltaMetrics, DeltaMetrics> bootstrap() {
    const auto incremental_metrics = incremental_.set_mode(DeltaMode::delta);
    const auto eager_metrics = eager_.set_mode(DeltaMode::delta);
    const auto on_output_metrics = on_output_.set_mode(DeltaMode::delta);
    check_live(incremental_, database_, "incremental bootstrap");
    check_live(eager_, database_, "eager bootstrap");
    check_live(on_output_, database_, "on-output bootstrap");
    check(incremental_.live_snapshot()->factors == eager_.live_snapshot()->factors,
          "incremental and eager bootstrap produced different L factors");
    check(incremental_.live_snapshot()->factors == on_output_.live_snapshot()->factors,
          "incremental and on-output bootstrap produced different L factors");
    return {incremental_metrics, eager_metrics, on_output_metrics};
  }

  void maintenance() {
    static_cast<void>(incremental_.set_mode(DeltaMode::maintenance));
    static_cast<void>(eager_.set_mode(DeltaMode::maintenance));
    static_cast<void>(on_output_.set_mode(DeltaMode::maintenance));
    check(!incremental_.live_snapshot() && !eager_.live_snapshot() &&
              !on_output_.live_snapshot(),
          "maintenance mode retained a live snapshot");
  }

  EpochPairResult apply(TableId table, SetOperation operation, Row row,
                        const std::string& label) {
    const auto before = a04(incremental_.plan(), database_);
    auto after_database = database_;
    auto& relation = after_database.tables.at(table.value);
    const bool changed = operation == SetOperation::insert
        ? relation.insert(row).second : relation.erase(row) != 0;
    check(changed, label + ": fixture update did not cross physical set membership");

    PhysicalSetUpdate update{++sequence_, table, operation, std::move(row)};
    auto incremental_epoch = incremental_.apply(update);
    auto eager_epoch = eager_.apply(update);
    auto on_output_epoch = on_output_.apply(update);
    const auto expected = difference(before, a04(incremental_.plan(), after_database));
    check(drain(incremental_epoch) == expected,
          label + ": incremental output differs from independent A04 difference");
    check(drain(eager_epoch) == expected,
          label + ": eager output differs from independent A04 difference");
    check(drain(on_output_epoch) == expected,
          label + ": on-output output differs from independent A04 difference");

    EpochPairResult result;
    result.incremental = incremental_epoch.metrics();
    result.eager = eager_epoch.metrics();
    result.on_output = on_output_epoch.metrics();
    result.incremental_stages.assign(incremental_epoch.stages().begin(),
                                     incremental_epoch.stages().end());
    result.eager_stages.assign(eager_epoch.stages().begin(),
                               eager_epoch.stages().end());
    result.on_output_stages.assign(on_output_epoch.stages().begin(),
                                   on_output_epoch.stages().end());
    database_ = std::move(after_database);
    check_live(incremental_, database_, label + " incremental");
    check_live(eager_, database_, label + " eager");
    check_live(on_output_, database_, label + " on-output");
    const auto incremental_live = incremental_.live_snapshot();
    const auto eager_live = eager_.live_snapshot();
    const auto on_output_live = on_output_.live_snapshot();
    check(incremental_live->factors == eager_live->factors,
          label + ": incremental and eager live factors differ");
    check(incremental_live->factors == on_output_live->factors,
          label + ": incremental and on-output live factors differ");
    check(result.incremental.live_rows == rows(incremental_live->factors) &&
              result.eager.live_rows == rows(eager_live->factors) &&
              result.on_output.live_rows == rows(on_output_live->factors),
          label + ": live_rows metric differs from current A04 L cardinality");
    check_stage_signatures(result.incremental_stages, result.eager_stages,
                           label + " incremental/eager stages");
    check_stage_signatures(result.incremental_stages, result.on_output_stages,
                           label + " incremental/on-output stages");
    check_on_output_metrics(result.incremental, result.on_output, label);
    return result;
  }

  [[nodiscard]] const Database& database() const { return database_; }
  [[nodiscard]] const DeltaRuntime& incremental() const { return incremental_; }
  [[nodiscard]] const DeltaRuntime& eager() const { return eager_; }
  [[nodiscard]] const DeltaRuntime& on_output() const { return on_output_; }

 private:
  DeltaRuntime incremental_;
  DeltaRuntime eager_;
  DeltaRuntime on_output_;
  Database database_;
  std::uint64_t sequence_ = 0;
};

using LiveWork = std::tuple<std::uint64_t, std::uint64_t, std::uint64_t,
                            std::uint64_t, std::uint64_t, std::uint64_t,
                            std::uint64_t, std::uint64_t, std::size_t,
                            std::uint64_t>;

LiveWork live_work(const DeltaMetrics& metrics) {
  return {metrics.live_probes, metrics.live_changes, metrics.live_inserts,
          metrics.live_erases, metrics.live_bucket_opens, metrics.live_bucket_rows,
          metrics.live_separator_updates, metrics.live_separator_crossings,
          metrics.live_queue_peak, metrics.live_journal_entries};
}

DeltaMetrics empty_delta_work(std::size_t dead_rows) {
  RuntimePair pair(root_child_plan(), root_child_plan(), root_child_plan(), 2);
  for (std::size_t i = 0; i < dead_rows; ++i)
    pair.seed(TableId{1}, {n(static_cast<std::int64_t>(i + 1)), n(10)});
  const auto [incremental_bootstrap, eager_bootstrap, on_output_bootstrap] =
      pair.bootstrap();
  check(incremental_bootstrap.e_rows_scanned == dead_rows &&
            eager_bootstrap.e_rows_scanned == dead_rows &&
            on_output_bootstrap.e_rows_scanned == dead_rows,
        "bootstrap did not scan the seeded E keys exactly once");

  const auto empty = pair.apply(TableId{0}, SetOperation::insert, {n(100)},
                                "unrelated E growth with empty query delta");
  check(empty.incremental.changed_keys == 0 && empty.eager.changed_keys == 0,
        "unmatched root insertion changed an E membership");
  check(empty.incremental.e_rows_scanned == 0 &&
            empty.incremental.live_rows_copied == 0 &&
            empty.incremental.live_bucket_rows == 0 &&
            empty.incremental.live_changes == 0,
        "incremental D=0 update scanned or copied unrelated E rows");
  check(empty.eager.e_rows_scanned == dead_rows,
        "eager comparison did not expose its per-route E rebuild");
  check(empty.on_output.e_rows_scanned == 0 &&
            empty.on_output.parent_live_rows == 0 &&
            empty.on_output.live_bucket_opens == 0 &&
            empty.on_output.live_bucket_rows == 0,
        "on-output empty delta scanned E or parent factors");
  return empty.incremental;
}

void unrelated_e_growth_is_not_scanned() {
  const auto small = empty_delta_work(1);
  const auto large = empty_delta_work(64);
  check(live_work(small) == live_work(large),
        "unrelated E growth changed incremental live operation counts");
  check(small.work == large.work,
        "unrelated E growth changed aggregate delta work on an empty delta");
  check(small.live_bucket_rows == 0 && large.live_bucket_rows == 0,
        "empty delta visited an unrelated child bucket");
  std::cout << "incremental empty-delta work=" << small.work << " -> " << large.work
            << " for 1 -> 64 dead E rows; bucket rows=0\n";
}

void unchanged_e_becomes_live_and_unlive() {
  RuntimePair pair(root_child_plan(), root_child_plan(), root_child_plan(), 2);
  pair.seed(TableId{1}, {n(3), n(30)});
  static_cast<void>(pair.bootstrap());

  const auto activated = pair.apply(TableId{0}, SetOperation::insert, {n(3)},
                                    "unchanged child E becomes live");
  check(activated.incremental.live_bucket_rows == 1 &&
            activated.incremental.live_inserts == 2 &&
            activated.incremental.live_changes == 2,
        "root activation did not visit and insert its unchanged child E key once");

  const auto removed = pair.apply(TableId{0}, SetOperation::erase, {n(3)},
                                  "unchanged child E becomes unlive");
  check(removed.incremental.live_bucket_rows == 1 &&
            removed.incremental.live_erases == 2 &&
            removed.incremental.live_changes == 2,
        "root deactivation did not remove its child L key once");
}

void shared_separator_count_crossings() {
  RuntimePair pair(shared_separator_plan(), shared_separator_plan(),
                   shared_separator_plan(), 2);
  pair.seed(TableId{0}, {n(1), n(7)});
  pair.seed(TableId{0}, {n(2), n(7)});
  pair.seed(TableId{1}, {n(7), n(9)});
  static_cast<void>(pair.bootstrap());

  const auto one_parent = pair.apply(TableId{0}, SetOperation::erase,
                                     {n(1), n(7)}, "shared separator 2 to 1");
  check(one_parent.incremental.live_separator_updates == 1 &&
            one_parent.incremental.live_separator_crossings == 0 &&
            one_parent.incremental.live_bucket_rows == 0,
        "2-to-1 parent support scanned or deactivated the shared child bucket");
  check(pair.incremental().live_snapshot()->factors[1].contains({n(7), n(9)}),
        "one remaining parent did not preserve the shared child key");

  const auto no_parents = pair.apply(TableId{0}, SetOperation::erase,
                                     {n(2), n(7)}, "shared separator 1 to 0");
  check(no_parents.incremental.live_separator_updates == 1 &&
            no_parents.incremental.live_separator_crossings == 1 &&
            no_parents.incremental.live_bucket_rows == 1,
        "1-to-0 parent support did not visit the one affected child key");
  check(!pair.incremental().live_snapshot()->factors[1].contains({n(7), n(9)}),
        "child key remained live after its final parent disappeared");
}

DeltaMetrics anchored_child_insertion_work(std::size_t root_rows) {
  RuntimePair pair(shared_separator_plan(), shared_separator_plan(),
                   shared_separator_plan(), 2);
  for (std::size_t i = 0; i < root_rows; ++i) {
    const auto value = n(static_cast<std::int64_t>(i));
    pair.seed(TableId{0}, {value, value});
    pair.seed(TableId{1}, {value, n(0)});
  }
  static_cast<void>(pair.bootstrap());

  const auto result = pair.apply(
      TableId{1}, SetOperation::insert,
      {n(static_cast<std::int64_t>(root_rows - 1)), n(1)},
      "on-output live child insertion with anchored completion");
  check(result.on_output.changed_keys == 1 && result.on_output.accepted == 1,
        "anchored child insertion did not have one changed E key and one accepted answer");
  check(result.on_output.live_changes == 1 &&
            result.on_output.live_inserts == 1 &&
            result.on_output.live_erases == 0 &&
            result.on_output.live_separator_updates == 0 &&
            result.on_output.live_separator_crossings == 0,
        "anchored child insertion did not have J=1 and U=0 live actions");
  check(result.on_output.e_rows_scanned == 0 &&
            result.on_output.parent_live_rows == 0 &&
            result.on_output.live_bucket_opens == 0 &&
            result.on_output.live_bucket_rows == 0,
        "anchored child insertion rebuilt or scanned E/live buckets");
  return result.on_output;
}

void anchored_completion_avoids_unrelated_root_scan() {
  const auto one_root_row = anchored_child_insertion_work(1);
  const auto many_root_rows = anchored_child_insertion_work(64);
  check(live_work(one_root_row) == live_work(many_root_rows),
        "anchored completion growth changed on-output live-action counts");
  check(many_root_rows.cursor_startup_work == one_root_row.cursor_startup_work &&
            many_root_rows.cursor_results_work == one_root_row.cursor_results_work &&
            many_root_rows.cursor_termination_work == one_root_row.cursor_termination_work,
        "anchored child completion scanned unrelated root E keys");
  std::cout << "on-output anchored completion: "
            << "cursor_results_work N=1 " << one_root_row.cursor_results_work
            << ", N=64 " << many_root_rows.cursor_results_work
            << "; J=1, U=0, accepted=1\n";
}

void deep_descendant_cascade() {
  RuntimePair pair(deep_chain_plan(), deep_chain_plan(), deep_chain_plan(), 4);
  pair.seed(TableId{1}, {n(1), n(2)});
  pair.seed(TableId{2}, {n(2), n(3)});
  pair.seed(TableId{3}, {n(3), n(4)});
  static_cast<void>(pair.bootstrap());

  const auto activation = pair.apply(TableId{0}, SetOperation::insert,
                                     {n(10), n(1)}, "four-level liveness cascade");
  check(activation.incremental.live_inserts == 4 &&
            activation.incremental.live_changes == 4 &&
            activation.incremental.live_bucket_rows == 3,
        "deep activation did not visit each descendant E bucket once");
  check(activation.incremental.live_queue_peak > 0,
        "deep liveness cascade did not exercise the incremental work queue");
  check(activation.incremental.accepted == 1,
        "deep activation did not emit its single full assignment");
}

void shared_separator_later_completion_cleans_child() {
  RuntimePair pair(delayed_child_cleanup_plan(), delayed_child_cleanup_plan(),
                   delayed_child_cleanup_plan(), 4);
  pair.seed(TableId{0}, {n(0)});
  pair.seed(TableId{1}, {n(0), n(1), n(7)});
  pair.seed(TableId{1}, {n(0), n(2), n(7)});
  pair.seed(TableId{2}, {n(7), n(10)});
  pair.seed(TableId{2}, {n(7), n(20)});
  pair.seed(TableId{3}, {n(10), n(100)});
  pair.seed(TableId{3}, {n(10), n(101)});
  pair.seed(TableId{3}, {n(20), n(200)});
  pair.seed(TableId{3}, {n(20), n(201)});
  static_cast<void>(pair.bootstrap());

  const auto deleted = pair.apply(TableId{0}, SetOperation::erase, {n(0)},
                                  "shared separator delayed child cleanup");
  check(deleted.incremental.accepted == 8 &&
            deleted.on_output.accepted == 8,
        "shared separator fixture did not enumerate all eight completions");
  check(deleted.incremental.live_erases == 9 &&
            deleted.on_output.live_erases == 9 &&
            deleted.incremental.live_separator_updates == 5 &&
            deleted.on_output.live_separator_updates == 5 &&
            deleted.incremental.live_separator_crossings == 4 &&
            deleted.on_output.live_separator_crossings == 4,
        "final parent removal did not clean all child and descendant L keys");
  check(rows(pair.incremental().live_snapshot()->factors) == 0 &&
            rows(pair.on_output().live_snapshot()->factors) == 0,
        "a child key first seen before zero parent support survived its later completion");

  const auto inserted = pair.apply(TableId{0}, SetOperation::insert, {n(0)},
                                   "shared separator delayed child reactivation");
  check(inserted.incremental.accepted == 8 &&
            inserted.on_output.accepted == 8 &&
            inserted.incremental.live_inserts == 9 &&
            inserted.on_output.live_inserts == 9,
        "shared separator reactivation did not restore every projected key");
  check(rows(pair.on_output().live_snapshot()->factors) == 9,
        "shared separator reactivation did not restore all L projections");
}

void simultaneous_parent_and_child_e_changes_are_idempotent() {
  RuntimePair pair(coalesced_plan(), coalesced_plan(), coalesced_plan(), 2);
  pair.seed(TableId{0}, {n(1)});
  static_cast<void>(pair.bootstrap());

  const auto inserted = pair.apply(TableId{1}, SetOperation::insert,
                                   {n(1), n(10)}, "coalesced parent and child E insertion");
  check(inserted.incremental.changed_keys >= 2,
        "fixture did not change both parent and child E memberships");
  check(inserted.incremental.live_inserts == 3 &&
            inserted.incremental.live_changes == 3,
        "overlapping parent activation and child E insertion duplicated L mutations");
  check(inserted.incremental.live_bucket_rows == 2,
        "coalesced activation did not visit each of its two child rows once");

  const auto erased = pair.apply(TableId{1}, SetOperation::erase,
                                 {n(1), n(10)}, "coalesced parent and child E deletion");
  check(erased.incremental.live_erases == 3 &&
            erased.incremental.live_changes == 3,
        "overlapping parent deactivation and child E deletion duplicated L erasures");
}

void nullary_product_activation() {
  RuntimePair pair(product_plan(3), product_plan(3), product_plan(3), 3);
  pair.seed(TableId{0}, {n(1)});
  pair.seed(TableId{0}, {n(2)});
  pair.seed(TableId{1}, {n(10)});
  pair.seed(TableId{1}, {n(20)});
  static_cast<void>(pair.bootstrap());

  const auto first_product = pair.apply(TableId{2}, SetOperation::insert,
                                        {n(30)}, "nullary root activates product");
  check(first_product.incremental.accepted == 4,
        "nullary root activation did not enumerate the four-row disconnected product");
  check(first_product.incremental.live_inserts == 6 &&
            first_product.incremental.live_changes == 6 &&
            first_product.incremental.live_bucket_rows == 5,
        "empty-separator activation did not insert each child E membership once");
  const auto live = pair.incremental().live_snapshot();
  check(live && live->factors.size() == 4 && live->factors[0].contains(Row{}) &&
            live->factors[1].size() == 2 && live->factors[2].size() == 2 &&
            live->factors[3] == Relation{Row{n(30)}},
        "nullary root or disconnected child L projections are wrong");
}

void aliases_and_mode_rebootstrap() {
  RuntimePair pair(same_scope_alias_plan(), same_scope_alias_plan(),
                   same_scope_alias_plan(), 1);
  pair.seed(TableId{0}, {n(1), n(10)});
  static_cast<void>(pair.bootstrap());

  const auto alias_insert = pair.apply(TableId{0}, SetOperation::insert,
                                       {n(2), n(20)}, "two aliases complete one answer");
  check(alias_insert.incremental_stages.size() == 2 &&
            alias_insert.incremental_stages[0].output_count == 0 &&
            alias_insert.incremental_stages[1].output_count == 1,
        "alias route prefixes did not own the new answer exactly once");

  pair.maintenance();
  pair.seed(TableId{0}, {n(3), n(30)});
  const auto [incremental_bootstrap, eager_bootstrap, on_output_bootstrap] =
      pair.bootstrap();
  check(incremental_bootstrap.e_rows_scanned > 0 &&
            eager_bootstrap.e_rows_scanned > 0 &&
            on_output_bootstrap.e_rows_scanned > 0,
        "mode re-entry did not bootstrap current E factors");
  check_live(pair.incremental(), pair.database(), "incremental mode rebootstrap");
  check_live(pair.eager(), pair.database(), "eager mode rebootstrap");
  check_live(pair.on_output(), pair.database(), "on-output mode rebootstrap");

  const auto after_rebootstrap = pair.apply(TableId{0}, SetOperation::insert,
      {n(4), n(40)}, "alias update after fresh bootstrap");
  check(after_rebootstrap.incremental_stages.size() == 2 &&
            after_rebootstrap.incremental_stages[0].output_count == 0 &&
            after_rebootstrap.incremental_stages[1].output_count == 1,
        "post-bootstrap alias routes did not emit at the completing prefix");
}

}  // namespace

int main() {
  try {
    unrelated_e_growth_is_not_scanned();
    unchanged_e_becomes_live_and_unlive();
    shared_separator_count_crossings();
    anchored_completion_avoids_unrelated_root_scan();
    deep_descendant_cascade();
    shared_separator_later_completion_cleans_child();
    simultaneous_parent_and_child_e_changes_are_idempotent();
    nullary_product_activation();
    aliases_and_mode_rebootstrap();
    std::cout << "incremental L fixtures passed\n";
  } catch (const std::exception& failure) {
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
