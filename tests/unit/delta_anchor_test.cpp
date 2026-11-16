#include "crown/planner/lower.hpp"
#include "crown/runtime/delta.hpp"
#include "evaluator.hpp"
#include "native_input.hpp"

#include <algorithm>
#include <cstddef>
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

DeltaOptions options(DeltaCompletion completion) {
  DeltaOptions result;
  result.mode = DeltaMode::maintenance;
  result.completion = completion;
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

void check_layout(const storage::TupleLayout& layout,
                  const auto& variables_in_order,
                  const std::string& label) {
  const auto& fields = layout.fields();
  check(fields.size() == variables_in_order.size(),
        label + ": result layout has the wrong arity");
  for (std::size_t field = 0; field < fields.size(); ++field) {
    check(fields[field].type == ScalarType::int64,
          label + ": result layout has a wrong scalar type");
    check(fields[field].variable == variables_in_order[field],
          label + ": result layout changed head order or repeated-head slots");
  }
}

Relation drain_current(SupportRuntime::ResultCursor& cursor,
                      const std::string& label) {
  Relation result;
  const auto& layout = cursor.layout();
  while (auto tuple = cursor.next()) {
    check(tuple->layout().same_token(layout),
          label + ": current tuple has a different layout token");
    check(tuple->values().size() == layout.fields().size(),
          label + ": current tuple has the wrong arity");
    for (std::size_t field = 0; field < tuple->values().size(); ++field)
      check(type_of(tuple->values()[field]) == layout.fields()[field].type,
            label + ": current tuple has a wrong scalar type");
    check(result.insert(crown::storage::export_row(tuple->values())).second,
          label + ": current result cursor emitted a duplicate row");
  }
  check(cursor.state() == ResultCursorState::exhausted && !cursor.active(),
        label + ": current result cursor did not release its lease");
  check(!cursor.next(), label + ": exhausted result cursor returned a row");
  return result;
}

void check_current_and_live(const DeltaRuntime& runtime,
                            const Database& database,
                            const std::vector<VariableId>& head_order,
                            const std::string& label) {
  const auto expected = a04(runtime.plan(), database);
  auto core = runtime.core_results();
  check_layout(core.layout(), head_order, label + " core layout");
  check(drain_current(core, label + " core") == expected,
        label + ": current core results differ from A04");
  auto output = runtime.results();
  check_layout(output.layout(), head_order, label + " output layout");
  check(drain_current(output, label + " output") == expected,
        label + ": current output results differ from A04");
  check(runtime.has_answer() == !expected.empty(),
        label + ": answer truth differs from A04");

  const auto live = runtime.live_snapshot();
  check(live.has_value(), label + ": delta mode has no live snapshot");
  check(live->sequence == runtime.sequence(),
        label + ": live snapshot sequence is stale");
  check(live->factors == a04_live(runtime.plan(), expected),
        label + ": live projections differ from independent A04 projections");
  runtime.check_invariants();
}

struct EventResult {
  std::vector<SignedKey> raw;
  std::vector<DeltaStage> stages;
  DeltaMetrics metrics;
};

EventResult drain_event(DeltaRuntime& runtime, DeltaRuntime::Epoch& epoch,
                        const std::set<SignedKey>& expected,
                        const std::vector<VariableId>& head_order,
                        const std::string& label) {
  check_layout(epoch.layout(), head_order, label + " epoch layout");
  check(epoch.layout().same_token(runtime.result_layout()),
        label + ": epoch layout token differs from the runtime");
  check(epoch.remaining() == expected.size(),
        label + ": raw signed cardinality differs from A04");
  check(epoch.active() == !expected.empty(),
        label + ": output lease state differs from the signed result count");
  check(runtime.ready() == expected.empty(),
        label + ": writer readiness differs from pending output");

  EventResult result;
  std::set<SignedKey> unique;
  std::uint64_t ordinal = 0;
  while (auto record = epoch.next()) {
    check(record->ordinal == ++ordinal,
          label + ": signed result ordinals are not contiguous");
    check(record->tuple.layout().same_token(epoch.layout()),
          label + ": signed tuple has a different layout token");
    check(record->tuple.values().size() == epoch.layout().fields().size(),
          label + ": signed tuple has the wrong arity");
    for (std::size_t field = 0; field < record->tuple.values().size(); ++field)
      check(type_of(record->tuple.values()[field]) ==
                epoch.layout().fields()[field].type,
            label + ": signed tuple has a wrong scalar type");
    const SignedKey key{record->operation, crown::storage::export_row(record->tuple.values())};
    check(unique.insert(key).second,
          label + ": epoch emitted a duplicate operation/row pair");
    result.raw.push_back(key);
  }
  check(unique == expected,
        label + ": raw signed output differs from A04 set difference");
  check(result.raw.size() == expected.size(),
        label + ": raw signed output cardinality changed");
  check(epoch.remaining() == 0 && !epoch.active() && runtime.ready(),
        label + ": draining the epoch did not release its output lease");
  check(!epoch.next(), label + ": exhausted epoch returned another record");
  result.stages.assign(epoch.stages().begin(), epoch.stages().end());
  result.metrics = epoch.metrics();
  return result;
}

void drain_empty_maintenance(DeltaRuntime& runtime,
                             DeltaRuntime::Epoch& epoch,
                             const std::string& label) {
  check(epoch.remaining() == 0 && !epoch.active(),
        label + ": maintenance update unexpectedly prepared delta output");
  check(!epoch.next(), label + ": empty maintenance epoch returned a record");
  check(runtime.ready(), label + ": empty maintenance epoch retained its lease");
}

class Pair {
 public:
  Pair(PhysicalPlan plan, std::size_t table_count)
      : anchored_(plan, options(DeltaCompletion::anchored)),
        root_first_(std::move(plan), options(DeltaCompletion::root_first)) {
    database_.tables.resize(table_count);
  }

  void seed(TableId table, Row row, const std::string& label) {
    const auto sequence = ++sequence_;
    PhysicalSetUpdate update{sequence, table, SetOperation::insert, row};
    auto anchored_epoch = anchored_.apply(update);
    auto root_first_epoch = root_first_.apply(update);
    check(anchored_epoch.sequence() == sequence &&
              root_first_epoch.sequence() == sequence,
          label + ": maintenance seed sequence did not commit");
    drain_empty_maintenance(anchored_, anchored_epoch,
                            label + " anchored maintenance");
    drain_empty_maintenance(root_first_, root_first_epoch,
                            label + " root-first maintenance");
    check(database_.tables.at(table.value).insert(std::move(row)).second,
          label + ": fixture seeded a duplicate physical row");
    check(anchored_.mode() == DeltaMode::maintenance &&
              root_first_.mode() == DeltaMode::maintenance,
          label + ": constructor did not start in maintenance mode");
    anchored_.check_invariants();
    root_first_.check_invariants();
  }

  void bootstrap(const std::vector<VariableId>& head_order,
                 const std::string& label) {
    static_cast<void>(anchored_.set_mode(DeltaMode::delta));
    static_cast<void>(root_first_.set_mode(DeltaMode::delta));
    check_current_and_live(anchored_, database_, head_order,
                           label + " anchored bootstrap");
    check_current_and_live(root_first_, database_, head_order,
                           label + " root-first bootstrap");
  }

  void maintenance(const std::vector<VariableId>& head_order,
                   const std::string& label) {
    static_cast<void>(anchored_.set_mode(DeltaMode::maintenance));
    static_cast<void>(root_first_.set_mode(DeltaMode::maintenance));
    check(!anchored_.live_snapshot() && !root_first_.live_snapshot(),
          label + ": maintenance mode retained a live snapshot");
    check_current_and_maintenance(anchored_, database_, head_order,
                                  label + " anchored maintenance mode");
    check_current_and_maintenance(root_first_, database_, head_order,
                                  label + " root-first maintenance mode");
  }

  std::pair<EventResult, EventResult> apply(
      TableId table, SetOperation operation, Row row,
      const std::vector<VariableId>& head_order, const std::string& label) {
    const auto before = a04(anchored_.plan(), database_);
    auto after_database = database_;
    auto& relation = after_database.tables.at(table.value);
    const bool changed = operation == SetOperation::insert
        ? relation.insert(row).second : relation.erase(row) == 1;
    check(changed, label + ": fixture update did not change physical membership");
    const auto expected = difference(before, a04(anchored_.plan(), after_database));
    check(expected == difference(a04(root_first_.plan(), database_),
                                 a04(root_first_.plan(), after_database)),
          label + ": completion policies have different A04 differences");

    const auto sequence = ++sequence_;
    PhysicalSetUpdate update{sequence, table, operation, std::move(row)};
    auto anchored_epoch = anchored_.apply(update);
    auto root_first_epoch = root_first_.apply(update);
    check(anchored_epoch.sequence() == sequence &&
              root_first_epoch.sequence() == sequence,
          label + ": delta sequence did not commit");
    auto anchored_result = drain_event(anchored_, anchored_epoch, expected,
                                       head_order, label + " anchored");
    auto root_first_result = drain_event(root_first_, root_first_epoch, expected,
                                         head_order, label + " root-first");
    database_ = std::move(after_database);
    check_current_and_live(anchored_, database_, head_order,
                           label + " anchored after-state");
    check_current_and_live(root_first_, database_, head_order,
                           label + " root-first after-state");
    return {std::move(anchored_result), std::move(root_first_result)};
  }

  [[nodiscard]] const Database& database() const { return database_; }
  [[nodiscard]] const DeltaRuntime& anchored() const { return anchored_; }
  [[nodiscard]] const DeltaRuntime& root_first() const { return root_first_; }

 private:
  static void check_current_and_maintenance(
      const DeltaRuntime& runtime, const Database& database,
      const std::vector<VariableId>& head_order, const std::string& label) {
    const auto expected = a04(runtime.plan(), database);
    auto core = runtime.core_results();
    check_layout(core.layout(), head_order, label + " core layout");
    check(drain_current(core, label + " core") == expected,
          label + ": current core results differ from A04");
    auto output = runtime.results();
    check_layout(output.layout(), head_order, label + " output layout");
    check(drain_current(output, label + " output") == expected,
          label + ": current output results differ from A04");
    runtime.check_invariants();
  }

  DeltaRuntime anchored_;
  DeltaRuntime root_first_;
  Database database_;
  std::uint64_t sequence_ = 0;
};

PhysicalPlan diagnostic_plan() {
  const Catalog catalog{1,
      {{"r", {{"a", ScalarType::int64}, {"x", ScalarType::int64}}},
       {"s", {{"x", ScalarType::int64}, {"z", ScalarType::int64}}}}};
  const Query query{
      {{"a", ScalarType::int64}, {"x", ScalarType::int64},
       {"z", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"s", TableId{1}, {VariableId{1}, VariableId{2}}}},
      {{VariableId{2}, "out_z"}, {VariableId{0}, "out_a"},
       {VariableId{1}, "out_x"}, {VariableId{1}, "out_x_again"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, variables({0, 1}), {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, variables({1, 2}), {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

struct DiagnosticMetrics {
  DeltaMetrics anchored_insert;
  DeltaMetrics root_first_insert;
  DeltaMetrics anchored_erase;
  DeltaMetrics root_first_erase;
};

DiagnosticMetrics diagnostic_run(std::size_t count) {
  const auto head_order = std::vector<VariableId>{VariableId{2}, VariableId{0},
                                                   VariableId{1}, VariableId{1}};
  Pair pair(diagnostic_plan(), 2);
  for (std::size_t i = 0; i < count; ++i) {
    const auto value = n(static_cast<std::int64_t>(i));
    pair.seed(TableId{0}, {value, value}, "diagnostic R seed");
    pair.seed(TableId{1}, {value, n(0)}, "diagnostic S seed");
  }
  pair.bootstrap(head_order, "diagnostic");
  check(a04(pair.anchored().plan(), pair.database()).size() == count,
        "diagnostic fixture did not produce N baseline answers");

  const auto x = n(static_cast<std::int64_t>(count - 1));
  const Row new_child{ x, n(1) };
  const Row answer{ n(1), x, x, x };
  auto [inserted_anchor, inserted_root] = pair.apply(
      TableId{1}, SetOperation::insert, new_child, head_order,
      "diagnostic child insertion");
  const std::set<SignedKey> insertion{{SetOperation::insert, answer}};
  check(std::set<SignedKey>(inserted_anchor.raw.begin(), inserted_anchor.raw.end()) ==
            insertion && inserted_anchor.raw.size() == 1 &&
            std::set<SignedKey>(inserted_root.raw.begin(), inserted_root.raw.end()) ==
            insertion && inserted_root.raw.size() == 1,
        "diagnostic insertion did not emit exactly its one signed repeated-head row");
  check(a04(pair.anchored().plan(), pair.database()).size() == count + 1,
        "diagnostic insertion changed the wrong number of current answers");

  auto [erased_anchor, erased_root] = pair.apply(
      TableId{1}, SetOperation::erase, new_child, head_order,
      "diagnostic child deletion");
  const std::set<SignedKey> deletion{{SetOperation::erase, answer}};
  check(std::set<SignedKey>(erased_anchor.raw.begin(), erased_anchor.raw.end()) ==
            deletion && erased_anchor.raw.size() == 1 &&
            std::set<SignedKey>(erased_root.raw.begin(), erased_root.raw.end()) ==
            deletion && erased_root.raw.size() == 1,
        "diagnostic deletion did not emit exactly its one signed repeated-head row");
  check(a04(pair.anchored().plan(), pair.database()).size() == count,
        "diagnostic deletion did not restore the baseline answer cardinality");
  return {inserted_anchor.metrics, inserted_root.metrics,
          erased_anchor.metrics, erased_root.metrics};
}

using CursorWork = std::tuple<std::uint64_t, std::uint64_t, std::uint64_t,
                              std::uint64_t, std::uint64_t, std::uint64_t>;

CursorWork cursor_work(const DeltaMetrics& metrics) {
  return {metrics.cursor_startup_work, metrics.cursor_results_work,
          metrics.cursor_termination_work,metrics.anchor_max_startup_work,
          metrics.anchor_max_result_work,metrics.anchor_max_termination_work};
}

void anchored_completion_scales_with_changed_witness() {
  const auto one = diagnostic_run(1);
  const auto many = diagnostic_run(64);
  check(cursor_work(one.anchored_insert) == cursor_work(many.anchored_insert) &&
            cursor_work(one.anchored_erase) == cursor_work(many.anchored_erase),
        "anchored insertion/deletion cursor work grew with unrelated root rows");
  for (const auto* metrics : {&many.anchored_insert, &many.anchored_erase}) {
    check(metrics->cursor_startup_work <= 128 &&
              metrics->cursor_results_work <= 128 &&
              metrics->cursor_termination_work <= 128,
          "anchored cursor work exceeded the fixture's bounded allowance");
  }
  check(many.root_first_insert.cursor_results_work >
            one.root_first_insert.cursor_results_work &&
            many.root_first_erase.cursor_results_work >
            one.root_first_erase.cursor_results_work,
        "root-first completion did not expose growth with unrelated root rows");
  std::cout << "anchored cursor work remains bounded for N=1 and N=64; "
               "root-first result work grows\n";
  std::cout<<"insert anchored phases="<<many.anchored_insert.cursor_startup_work<<','
           <<many.anchored_insert.cursor_results_work<<','<<many.anchored_insert.cursor_termination_work
           <<"; root-first result work="<<one.root_first_insert.cursor_results_work<<" -> "
           <<many.root_first_insert.cursor_results_work<<'\n';
  std::cout<<"erase anchored phases="<<many.anchored_erase.cursor_startup_work<<','
           <<many.anchored_erase.cursor_results_work<<','<<many.anchored_erase.cursor_termination_work
           <<"; root-first result work="<<one.root_first_erase.cursor_results_work<<" -> "
           <<many.root_first_erase.cursor_results_work<<'\n';
}

PhysicalPlan deep_sibling_plan() {
  const Catalog catalog{1,
      {{"r", {{"a", ScalarType::int64}, {"x", ScalarType::int64}}},
       {"s", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}},
       {"t", {{"y", ScalarType::int64}, {"z", ScalarType::int64}}},
       {"v", {{"x", ScalarType::int64}, {"w", ScalarType::int64}}}}};
  const Query query{
      {{"a", ScalarType::int64}, {"x", ScalarType::int64},
       {"y", ScalarType::int64}, {"z", ScalarType::int64},
       {"w", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"s", TableId{1}, {VariableId{1}, VariableId{2}}},
       {"t", TableId{2}, {VariableId{2}, VariableId{3}}},
       {"v", TableId{3}, {VariableId{1}, VariableId{4}}}},
      {{VariableId{0}, "a"}, {VariableId{1}, "x"},
       {VariableId{2}, "y"}, {VariableId{3}, "z"},
       {VariableId{4}, "w"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, variables({0, 1}),
         {NodeId{1}, NodeId{3}}, 0, {}},
       {"s", NodeKind::native, variables({1, 2}), {NodeId{2}}, 1, {}},
       {"t", NodeKind::native, variables({2, 3}), {}, 2, {}},
       {"v", NodeKind::native, variables({1, 4}), {}, 3, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

std::size_t path_depth_to_root(const auto& plan, NodeId node) {
  const auto& steps = plan.enumeration().steps;
  auto position = std::find_if(steps.begin(), steps.end(),
      [&](const auto& step) { return step.node == node; });
  check(position != steps.end(), "deep fixture omitted its changed witness step");
  std::size_t depth = 0;
  while (position->parent_step) {
    ++depth;
    position = steps.begin() +
        static_cast<std::ptrdiff_t>(*position->parent_step);
  }
  return depth;
}

void reverse_path_deletion_and_sibling_products() {
  const auto head_order = std::vector<VariableId>{VariableId{0}, VariableId{1},
      VariableId{2}, VariableId{3}, VariableId{4}};
  auto plan = deep_sibling_plan();
  check(path_depth_to_root(plan, NodeId{2}) >= 2,
        "deep fixture does not reverse at least two C* edges");
  Pair pair(std::move(plan), 4);
  pair.seed(TableId{0}, {n(1), n(7)}, "deep R parent one");
  pair.seed(TableId{0}, {n(2), n(7)}, "deep R parent two");
  pair.seed(TableId{1}, {n(7), n(10)}, "deep shared S separator");
  pair.seed(TableId{3}, {n(7), n(100)}, "deep V sibling one");
  pair.seed(TableId{3}, {n(7), n(101)}, "deep V sibling two");
  pair.bootstrap(head_order, "deep reverse path");
  check(a04(pair.anchored().plan(), pair.database()).empty(),
        "deep fixture unexpectedly answered before its T witness");

  const std::set<Row> completed{
      {n(1), n(7), n(10), n(99), n(100)},
      {n(1), n(7), n(10), n(99), n(101)},
      {n(2), n(7), n(10), n(99), n(100)},
      {n(2), n(7), n(10), n(99), n(101)}};
  auto [inserted_anchor, inserted_root] = pair.apply(
      TableId{2}, SetOperation::insert, {n(10), n(99)}, head_order,
      "deep changed witness insertion");
  std::set<SignedKey> expected_insertions;
  for (const auto& row : completed)
    expected_insertions.emplace(SetOperation::insert, row);
  check(std::set<SignedKey>(inserted_anchor.raw.begin(), inserted_anchor.raw.end()) ==
            expected_insertions && inserted_anchor.raw.size() == 4 &&
            std::set<SignedKey>(inserted_root.raw.begin(), inserted_root.raw.end()) ==
            expected_insertions && inserted_root.raw.size() == 4,
        "reverse-path completion lost a parent row or sibling product");

  auto [erased_anchor, erased_root] = pair.apply(
      TableId{2}, SetOperation::erase, {n(10), n(99)}, head_order,
      "deep changed witness deletion");
  std::set<SignedKey> expected_deletions;
  for (const auto& row : completed)
    expected_deletions.emplace(SetOperation::erase, row);
  check(std::set<SignedKey>(erased_anchor.raw.begin(), erased_anchor.raw.end()) ==
            expected_deletions && erased_anchor.raw.size() == 4 &&
            std::set<SignedKey>(erased_root.raw.begin(), erased_root.raw.end()) ==
            expected_deletions && erased_root.raw.size() == 4,
        "on-output deletion lost rows while removing selected live parents");
  check(pair.anchored().live_snapshot()->factors ==
            a04_live(pair.anchored().plan(), Relation{}),
        "deep deletion left parent or sibling L rows live");
}

PhysicalPlan nullary_separator_plan() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}}},
       {"s", {{"y", ScalarType::int64}}}}};
  const Query query{
      {{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}}},
       {"s", TableId{1}, {VariableId{1}}}},
      {{VariableId{1}, "y"}, {VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"product", NodeKind::generalized, {}, {NodeId{1}, NodeId{2}}, {}, {}},
       {"r", NodeKind::native, variables({0}), {}, 0, {}},
       {"s", NodeKind::native, variables({1}), {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

void nullary_separator_and_product() {
  const auto head_order = std::vector<VariableId>{VariableId{1}, VariableId{0}};
  Pair pair(nullary_separator_plan(), 2);
  pair.seed(TableId{0}, {n(1)}, "nullary product R one");
  pair.seed(TableId{0}, {n(2)}, "nullary product R two");
  pair.bootstrap(head_order, "nullary product");
  check(a04(pair.anchored().plan(), pair.database()).empty(),
        "nullary product answered without every child");

  auto [inserted_anchor, inserted_root] = pair.apply(
      TableId{1}, SetOperation::insert, {n(10)}, head_order,
      "nullary separator activation");
  const std::set<SignedKey> insertions{
      {SetOperation::insert, Row{n(10), n(1)}},
      {SetOperation::insert, Row{n(10), n(2)}}};
  check(std::set<SignedKey>(inserted_anchor.raw.begin(), inserted_anchor.raw.end()) ==
            insertions && inserted_anchor.raw.size() == 2 &&
            std::set<SignedKey>(inserted_root.raw.begin(), inserted_root.raw.end()) ==
            insertions && inserted_root.raw.size() == 2,
        "nullary separator did not produce the full disconnected product");
  const auto& steps = pair.anchored().plan().enumeration().steps;
  const auto root = std::find_if(steps.begin(), steps.end(),
      [](const auto& step) { return step.node == NodeId{0}; });
  check(root != steps.end() &&
            pair.anchored().live_snapshot()->factors.at(
                static_cast<std::size_t>(root - steps.begin())).contains(Row{}),
        "empty separator did not retain its nullary live key");

  auto [erased_anchor, erased_root] = pair.apply(
      TableId{1}, SetOperation::erase, {n(10)}, head_order,
      "nullary separator deactivation");
  const std::set<SignedKey> deletions{
      {SetOperation::erase, Row{n(10), n(1)}},
      {SetOperation::erase, Row{n(10), n(2)}}};
  check(std::set<SignedKey>(erased_anchor.raw.begin(), erased_anchor.raw.end()) ==
            deletions && erased_anchor.raw.size() == 2 &&
            std::set<SignedKey>(erased_root.raw.begin(), erased_root.raw.end()) ==
            deletions && erased_root.raw.size() == 2,
        "nullary separator did not retract the full disconnected product");
}

PhysicalPlan alias_plan() {
  const Catalog catalog{1,
      {{"edge", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}}}};
  const Query query{
      {{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"left", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"right", TableId{0}, {VariableId{0}, VariableId{1}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "y"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"join", NodeKind::generalized, variables({0, 1}),
         {NodeId{1}, NodeId{2}}, {}, {}},
       {"left", NodeKind::native, variables({0, 1}), {}, 0, {}},
       {"right", NodeKind::native, variables({0, 1}), {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

void check_alias_stage_ownership(const std::pair<EventResult, EventResult>& event,
                                std::size_t first_count,
                                std::size_t second_count,
                                const std::string& label) {
  for (const auto* result : {&event.first, &event.second}) {
    check(result->stages.size() == 2,
          label + ": alias source update did not retain both route stages");
    check(result->stages[0].output_count == first_count &&
              result->stages[1].output_count == second_count,
          label + ": alias output was assigned to the wrong occurrence prefix");
  }
}

void alias_stage_isolation_and_rebootstrap() {
  const auto head_order = std::vector<VariableId>{VariableId{0}, VariableId{1}};
  Pair pair(alias_plan(), 1);
  pair.seed(TableId{0}, {n(1), n(10)}, "alias maintenance seed");
  pair.bootstrap(head_order, "alias first bootstrap");

  const auto inserted = pair.apply(TableId{0}, SetOperation::insert,
      {n(2), n(20)}, head_order, "alias completing prefix");
  check_alias_stage_ownership(inserted, 0, 1, "alias insertion");
  const auto erased = pair.apply(TableId{0}, SetOperation::erase,
      {n(2), n(20)}, head_order, "alias prefix removal");
  check_alias_stage_ownership(erased, 1, 0, "alias deletion");

  pair.maintenance(head_order, "alias mode switch");
  pair.seed(TableId{0}, {n(3), n(30)}, "alias maintenance-only row");
  pair.bootstrap(head_order, "alias rebootstrap");
  const auto post_bootstrap = pair.apply(TableId{0}, SetOperation::insert,
      {n(4), n(40)}, head_order, "alias post-rebootstrap route");
  check_alias_stage_ownership(post_bootstrap, 0, 1,
                              "alias post-rebootstrap insertion");
}

}  // namespace

int main() {
  try {
    anchored_completion_scales_with_changed_witness();
    reverse_path_deletion_and_sibling_products();
    nullary_separator_and_product();
    alias_stage_isolation_and_rebootstrap();
    std::cout << "anchored delta completion fixtures passed\n";
  } catch (const std::exception& failure) {
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
