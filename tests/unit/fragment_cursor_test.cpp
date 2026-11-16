#include "crown/api/error.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/physical.hpp"
#include "evaluator.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace {
using namespace crown;
using namespace crown::runtime;

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

template <class Action>
void expect_error(Action&& action, std::string_view code) {
  try {
    action();
  } catch (const Error& failure) {
    check(failure.code() == code,
          "expected " + std::string(code) + ", got " + failure.code());
    return;
  }
  throw std::runtime_error("expected error " + std::string(code));
}

Value n(std::int64_t value) { return value; }
Value s(std::string value) { return value; }
Value day(std::string_view value) { return Date::parse(value); }
Value decimal(std::string_view value) { return Decimal::parse(value); }

Relation drain(SupportRuntime::ResultCursor& cursor) {
  Relation rows;
  while (auto row = cursor.next()) {
    check(row->layout().same_token(cursor.layout()),
          "fragment cursor returned a tuple with a different output layout token");
    check(rows.insert(crown::storage::export_row(row->values())).second,
          "fragment cursor emitted a duplicate assignment");
  }
  check(cursor.state() == ResultCursorState::exhausted && !cursor.active(),
        "fragment cursor did not release its lease on exhaustion");
  check(!cursor.next(), "exhausted fragment cursor did not keep returning nullopt");
  return rows;
}

void check_schema(const storage::TupleLayout& layout,
                  const std::vector<VariableId>& variables,
                  const std::string& context) {
  check(layout.fields().size() == variables.size(), context + ": wrong output arity");
  for (std::size_t i = 0; i < variables.size(); ++i)
    check(layout.fields()[i].variable == variables[i],
          context + ": output variables are not in ascending ID order");
}

Relation a04_assignments(const Catalog& catalog, const Query& query,
                         const Database& database) {
  Query full = query;
  full.head.clear();
  for (std::size_t i = 0; i < full.variables.size(); ++i)
    full.head.push_back({VariableId{i}, full.variables[i].name});
  return reference::evaluate(catalog, full, database);
}

Relation a04_project(const Relation& assignments, const Query& query,
                     const FixedAssignment& fixed = {}) {
  Relation projected;
  for (const auto& assignment : assignments) {
    bool matches = true;
    for (const auto& binding : fixed) {
      if (assignment.at(binding.variable.value) != binding.value) {
        matches = false;
        break;
      }
    }
    if (!matches) continue;
    Row output;
    for (const auto& field : query.head)
      output.push_back(assignment.at(field.variable.value));
    projected.insert(std::move(output));
  }
  return projected;
}

void insert(PhysicalRuntime& runtime, std::uint64_t& sequence,
            TableId table, Row row) {
  const auto result = runtime.apply({++sequence, table, SetOperation::insert, row});
  check(result.input.physical_changed, "fixture source row was not inserted");
}

PhysicalPlan one_hidden_variable_plan() {
  const Catalog catalog{1, {{"r", {{"x", ScalarType::int64},
                                    {"z", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"z", ScalarType::int64}},
                    {{"r", TableId{0}, {VariableId{0}, VariableId{1}}}},
                    {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

// The selected local fragment is S(x,z,y). R(a,x) is its outside parent and
// deliberately has no row for x=20. Its separator x is visible, while z is
// hidden inside the selected child subtree.
PhysicalPlan local_child_plan() {
  const Catalog catalog{1,
      {{"r", {{"a", ScalarType::int64}, {"x", ScalarType::int64}}},
       {"s", {{"x", ScalarType::int64}, {"z", ScalarType::int64},
               {"y", ScalarType::int64}}}}};
  const Query query{{{"a", ScalarType::int64}, {"x", ScalarType::int64},
                     {"z", ScalarType::int64}, {"y", ScalarType::int64}},
                    {{"r", TableId{0}, {VariableId{0}, VariableId{1}}},
                     {"s", TableId{1}, {VariableId{1}, VariableId{2}, VariableId{3}}}},
                    {{VariableId{1}, "x"}, {VariableId{3}, "y"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, {VariableId{1}, VariableId{2}, VariableId{3}}, {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan outside_c_star_child_plan() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}, {"z", ScalarType::int64}}},
       {"s", {{"z", ScalarType::int64}, {"y", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"z", ScalarType::int64},
                     {"y", ScalarType::int64}},
                    {{"r", TableId{0}, {VariableId{0}, VariableId{1}}},
                     {"s", TableId{1}, {VariableId{1}, VariableId{2}}}},
                    {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, {VariableId{1}, VariableId{2}}, {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan depth_three_plan() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}, {"z", ScalarType::int64}}},
       {"s", {{"z", ScalarType::int64}, {"y", ScalarType::int64}}},
       {"t", {{"y", ScalarType::int64}, {"z", ScalarType::int64},
               {"w", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"z", ScalarType::int64},
                     {"y", ScalarType::int64}, {"w", ScalarType::int64}},
                    {{"r", TableId{0}, {VariableId{0}, VariableId{1}}},
                     {"s", TableId{1}, {VariableId{1}, VariableId{2}}},
                     {"t", TableId{2}, {VariableId{2}, VariableId{1}, VariableId{3}}}},
                    {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, {VariableId{1}, VariableId{2}}, {NodeId{2}}, 1, {}},
       {"t", NodeKind::native,
        {VariableId{1}, VariableId{2}, VariableId{3}}, {}, 2, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan shared_siblings_plan() {
  const Catalog catalog{1,
      {{"a", {{"x", ScalarType::int64}, {"a", ScalarType::int64}}},
       {"b", {{"x", ScalarType::int64}, {"b", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"a", ScalarType::int64},
                     {"b", ScalarType::int64}},
                    {{"a", TableId{0}, {VariableId{0}, VariableId{1}}},
                     {"b", TableId{1}, {VariableId{0}, VariableId{2}}}},
                    {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"product", NodeKind::generalized, {VariableId{0}},
         {NodeId{1}, NodeId{2}}, {}, {}},
       {"a", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}},
       {"b", NodeKind::native, {VariableId{0}, VariableId{2}}, {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan product_plan(std::size_t arity) {
  Catalog catalog;
  catalog.version = 1;
  Query query;
  std::vector<NodeId> children;
  for (std::size_t i = 0; i < arity; ++i) {
    query.variables.push_back({"v" + std::to_string(i), ScalarType::int64});
    query.atoms.push_back({"t" + std::to_string(i), TableId{i}, {VariableId{i}}});
    catalog.tables.push_back({"t" + std::to_string(i), {{"v", ScalarType::int64}}});
    children.push_back(NodeId{i + 1});
  }
  FreeConnexTree tree;
  tree.root = NodeId{0};
  tree.nodes.push_back({"product", NodeKind::generalized, {}, children, {}, {}});
  for (std::size_t i = 0; i < arity; ++i)
    tree.nodes.push_back({"t" + std::to_string(i), NodeKind::native,
                          {VariableId{i}}, {}, i, {}});
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan typed_plan() {
  const Catalog catalog{1,
      {{"typed", {{"n", ScalarType::int64}, {"label", ScalarType::string},
                   {"day", ScalarType::date},
                   {"amount", ScalarType::decimal, false, Collation::binary,
                    DecimalSpec{8, 2}},
                   {"flag", ScalarType::boolean}}}}};
  const Query query{{{"n", ScalarType::int64}, {"label", ScalarType::string},
                     {"day", ScalarType::date}, {"amount", ScalarType::decimal},
                     {"flag", ScalarType::boolean}},
                    {{"typed", TableId{0}, {VariableId{0}, VariableId{1},
                         VariableId{2}, VariableId{3}, VariableId{4}}}},
                    {{VariableId{0}, "n"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"typed", NodeKind::native,
        {VariableId{0}, VariableId{1}, VariableId{2}, VariableId{3}, VariableId{4}},
        {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan self_join_plan() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}, {"value", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"z", ScalarType::int64},
                     {"w", ScalarType::int64}},
                    {{"r_z", TableId{0}, {VariableId{0}, VariableId{1}}},
                     {"r_w", TableId{0}, {VariableId{0}, VariableId{2}}}},
                    {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"product", NodeKind::generalized, {VariableId{0}},
         {NodeId{1}, NodeId{2}}, {}, {}},
       {"r_z", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}},
       {"r_w", NodeKind::native, {VariableId{0}, VariableId{2}}, {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan nullary_atom_plan() {
  const Catalog catalog{1, {{"flags", {{"tag", ScalarType::string}}}}};
  const Query query{{}, {{"flags", TableId{0}, {IgnoredColumn{}}}}, {}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"flags", NodeKind::native, {}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan constant_plan(bool truth) {
  const Catalog catalog{1, {}};
  const Query query{{}, {}, {}, !truth};
  return planner::lower_tree(catalog, query, FreeConnexTree{});
}

void hidden_bindings_project_without_multiplying_rows() {
  auto plan = one_hidden_variable_plan();
  PhysicalRuntime runtime(plan);
  Database database;
  database.tables.resize(1);
  std::uint64_t sequence = 0;
  for (const Row& row : {Row{n(1), n(10)}, Row{n(1), n(20)}, Row{n(2), n(20)}}) {
    insert(runtime, sequence, TableId{0}, row);
    database.tables[0].insert(row);
  }
  const Relation expected_assignments =
      a04_assignments(plan.catalog(), plan.query(), database);

  auto view = runtime.current_view();
  auto all = view.witnesses();
  check_schema(all.layout(), {VariableId{0}, VariableId{1}}, "whole witness assignment");
  check(drain(all) == expected_assignments &&
            expected_assignments == Relation{{n(1), n(10)}, {n(1), n(20)}, {n(2), n(20)}},
        "whole witness cursor omitted a hidden-variable assignment");

  auto projected = view.completions({});
  check(drain(projected) == a04_project(expected_assignments, plan.query()) &&
            a04_project(expected_assignments, plan.query()) == Relation{{n(1)}, {n(2)}},
        "projected completions duplicated a row with multiple hidden witnesses");
  auto matching = view.completions({{VariableId{1}, n(20)}});
  check_schema(matching.layout(), {VariableId{0}}, "hidden-bound completion");
  const FixedAssignment z20{{VariableId{1}, n(20)}};
  check(drain(matching) == a04_project(expected_assignments, plan.query(), z20) &&
            a04_project(expected_assignments, plan.query(), z20) ==
                Relation{{n(1)}, {n(2)}},
        "hidden binding did not restrict projected completions");
  auto projected_collision = view.completions({{VariableId{1}, n(10)}});
  const FixedAssignment z10{{VariableId{1}, n(10)}};
  check(drain(projected_collision) == a04_project(expected_assignments, plan.query(), z10) &&
            a04_project(expected_assignments, plan.query(), z10) == Relation{{n(1)}},
        "hidden binding failed to collapse duplicate projected witnesses");
  auto absent = view.completions({{VariableId{1}, n(99)}});
  const FixedAssignment z99{{VariableId{1}, n(99)}};
  check(drain(absent) == a04_project(expected_assignments, plan.query(), z99) &&
            a04_project(expected_assignments, plan.query(), z99).empty(),
        "unsupported hidden value returned a projected row");

  expect_error([&] {
    static_cast<void>(view.completions({{VariableId{1}, n(10)},
                                        {VariableId{1}, n(20)}}));
  }, "invalid_binding");
  expect_error([&] {
    static_cast<void>(view.witnesses({{VariableId{1}, s("wrong type")}}));
  }, "invalid_binding");
  expect_error([&] {
    static_cast<void>(view.witnesses({{VariableId{99}, n(1)}}));
  }, "invalid_binding");
  view.close();
}

void local_fragments_and_full_physical_subtrees() {
  auto plan = local_child_plan();
  PhysicalRuntime runtime(plan);
  Database database;
  database.tables.resize(2);
  std::uint64_t sequence = 0;
  const Row r_row{n(1), n(10)};
  const std::vector<Row> s_rows{{n(10), n(10), n(100)},
                                {n(20), n(20), n(200)}};
  insert(runtime, sequence, TableId{0}, r_row);
  database.tables[0].insert(r_row);
  for (const Row& row : s_rows) {
    insert(runtime, sequence, TableId{1}, row);
    database.tables[1].insert(row);
  }

  Query local_query{{{"x", ScalarType::int64}, {"z", ScalarType::int64},
                     {"y", ScalarType::int64}},
                    {{"s", TableId{1}, {VariableId{0}, VariableId{1}, VariableId{2}}}},
                    {{VariableId{0}, "x"}, {VariableId{1}, "z"},
                     {VariableId{2}, "y"}}, false};
  const Relation expected_local =
      a04_assignments(plan.catalog(), local_query, database);
  local_query.head = {{VariableId{0}, "x"}, {VariableId{2}, "y"}};
  const Relation expected_local_output = a04_project(expected_local, local_query);
  const FixedAssignment z20{{VariableId{2}, n(20)}};
  const FixedAssignment local_z20{{VariableId{1}, n(20)}};
  const Relation expected_local_hidden =
      a04_project(expected_local, local_query, local_z20);
  const Relation expected_whole_hidden =
      a04_project(a04_assignments(plan.catalog(), plan.query(), database),
                  plan.query(), z20);

  auto view = runtime.current_view();
  auto local = view.completions({}, VisibleFragment{NodeId{1}});
  check_schema(local.layout(), {VariableId{1}, VariableId{3}}, "child C* fragment");
  check(drain(local) == expected_local_output &&
            expected_local_output == Relation{{n(10), n(100)}, {n(20), n(200)}},
        "local child fragment was restricted by its outside parent");

  auto local_hidden = view.completions(z20,
                                       VisibleFragment{NodeId{1}});
  check(drain(local_hidden) == expected_local_hidden &&
            expected_local_hidden == Relation{{n(20), n(200)}},
        "hidden binding inside a local fragment did not filter its rows");
  auto absent_from_fragment = view.completions({{VariableId{0}, n(999)}},
                                               VisibleFragment{NodeId{1}});
  check(drain(absent_from_fragment) ==
            Relation{{n(10), n(100)}, {n(20), n(200)}},
        "local fragment did not ignore a valid binding outside its subtree");
  auto whole_hidden = view.completions({{VariableId{2}, n(20)}});
  check(drain(whole_hidden) == expected_whole_hidden && expected_whole_hidden.empty(),
        "whole-query completion ignored its unsupported hidden parent witness");

  auto full_tree = view.witnesses({}, WitnessFragment{.root = NodeId{0}});
  check_schema(full_tree.layout(), {VariableId{0}, VariableId{1},
                                    VariableId{2}, VariableId{3}},
               "whole physical subtree");
  check(drain(full_tree) == a04_assignments(plan.catalog(), plan.query(), database) &&
            a04_assignments(plan.catalog(), plan.query(), database) ==
                Relation{{n(1), n(10), n(10), n(100)}},
        "root witness fragment did not include the physical descendant outside C*");
  auto local_tree = view.witnesses({}, WitnessFragment{.root = NodeId{1}});
  check_schema(local_tree.layout(), {VariableId{1}, VariableId{2}, VariableId{3}},
               "physical child subtree");
  check(drain(local_tree) == expected_local &&
            expected_local == Relation{{n(10), n(10), n(100)},
                                       {n(20), n(20), n(200)}},
        "root-selected child witness fragment included its outside parent");

  auto identity = view.witnesses({}, WitnessFragment{.nodes = std::vector<NodeId>{}});
  check_schema(identity.layout(), {}, "empty factor selection");
  check(drain(identity) == Relation{{}},
        "empty factor selection did not produce the nullary join identity");

  expect_error([&] {
    static_cast<void>(view.witnesses({}, WitnessFragment{.root = NodeId{99}}));
  }, "invalid_fragment");
  expect_error([&] {
    static_cast<void>(view.witnesses({}, WitnessFragment{.nodes =
        std::vector<NodeId>{NodeId{99}}}));
  }, "invalid_fragment");
  expect_error([&] {
    static_cast<void>(view.witnesses({}, WitnessFragment{.nodes =
        std::vector<NodeId>{NodeId{1}, NodeId{1}}}));
  }, "invalid_fragment");
  expect_error([&] {
    static_cast<void>(view.witnesses({}, WitnessFragment{.root = NodeId{0},
        .nodes = std::vector<NodeId>{NodeId{1}}}));
  }, "invalid_fragment");
  view.close();
}

void physical_subtree_can_include_nodes_outside_c_star() {
  auto plan = outside_c_star_child_plan();
  check(plan.enumeration().steps.size() == 1 &&
            plan.enumeration().steps.front().node == NodeId{0},
        "fixture did not keep its hidden child outside C*");
  PhysicalRuntime runtime(plan);
  Database database;
  database.tables.resize(2);
  std::uint64_t sequence = 0;
  for (const Row& row : {Row{n(1), n(10)}, Row{n(2), n(20)}}) {
    insert(runtime, sequence, TableId{0}, row);
    database.tables[0].insert(row);
  }
  const Row child{n(10), n(100)};
  insert(runtime, sequence, TableId{1}, child);
  database.tables[1].insert(child);

  const Relation expected = a04_assignments(plan.catalog(), plan.query(), database);
  auto view = runtime.current_view();
  auto full = view.witnesses();
  check(drain(full) == expected && expected == Relation{{n(1), n(10), n(100)}},
        "whole-tree witnesses omitted the hidden child outside C*");
  auto physical_root = view.witnesses({}, WitnessFragment{.root = NodeId{0}});
  check(drain(physical_root) == expected,
        "root witness fragment did not include its physical child outside C*");
  auto physical_child = view.witnesses({}, WitnessFragment{.root = NodeId{1}});
  check_schema(physical_child.layout(), {VariableId{1}, VariableId{2}},
               "outside-C* physical child");
  check(drain(physical_child) == Relation{{n(10), n(100)}},
        "root-selected outside-C* node did not expose its local survivor factor");
  expect_error([&] {
    static_cast<void>(view.completions({}, VisibleFragment{NodeId{1}}));
  }, "invalid_fragment");
  auto hidden_parent_miss = view.completions({{VariableId{1}, n(20)}});
  check(drain(hidden_parent_miss).empty(),
        "whole completion ignored an unsupported hidden parent binding");
  view.close();
}

void depth_three_shared_hidden_variable_and_factor_subsets() {
  auto plan = depth_three_plan();
  PhysicalRuntime runtime(plan);
  Database database;
  database.tables.resize(3);
  std::uint64_t sequence = 0;
  for (const Row& row : {Row{n(1), n(10)}, Row{n(2), n(20)},
                         Row{n(3), n(30)}, Row{n(4), n(40)}}) {
    insert(runtime, sequence, TableId{0}, row);
    database.tables[0].insert(row);
  }
  for (const Row& row : {Row{n(10), n(100)}, Row{n(10), n(101)},
                         Row{n(20), n(100)}, Row{n(30), n(300)},
                         Row{n(40), n(400)}}) {
    insert(runtime, sequence, TableId{1}, row);
    database.tables[1].insert(row);
  }
  for (const Row& row : {Row{n(100), n(10), n(7)}, Row{n(100), n(10), n(9)},
                         Row{n(101), n(10), n(10)}, Row{n(100), n(20), n(8)},
                         Row{n(300), n(20), n(12)}, Row{n(300), n(30), n(11)},
                         Row{n(400), n(40), n(13)}, Row{n(999), n(10), n(14)}}) {
    insert(runtime, sequence, TableId{2}, row);
    database.tables[2].insert(row);
  }

  auto view = runtime.current_view();
  const Relation expected_full{{n(1), n(10), n(100), n(7)},
                               {n(1), n(10), n(100), n(9)},
                               {n(1), n(10), n(101), n(10)},
                               {n(2), n(20), n(100), n(8)},
                               {n(3), n(30), n(300), n(11)},
                               {n(4), n(40), n(400), n(13)}};
  auto all = view.witnesses();
  check_schema(all.layout(), {VariableId{0}, VariableId{1}, VariableId{2}, VariableId{3}},
               "depth-three full witness assignment");
  const Relation reference_full = a04_assignments(plan.catalog(), plan.query(), database);
  check(drain(all) == expected_full && reference_full == expected_full,
        "whole-tree witnesses did not enforce a hidden ancestor variable in the leaf");

  auto fixed_hidden = view.completions({{VariableId{1}, n(10)},
                                        {VariableId{2}, n(100)}});
  check_schema(fixed_hidden.layout(), {VariableId{0}}, "depth-three hidden completion");
  const FixedAssignment z10_y100{{VariableId{1}, n(10)}, {VariableId{2}, n(100)}};
  check(drain(fixed_hidden) == a04_project(reference_full, plan.query(), z10_y100) &&
            a04_project(reference_full, plan.query(), z10_y100) == Relation{{n(1)}},
        "bound hidden separator values did not filter the depth-three output");
  auto conflict = view.completions({{VariableId{1}, n(10)},
                                    {VariableId{2}, n(300)}});
  const FixedAssignment z10_y300{{VariableId{1}, n(10)}, {VariableId{2}, n(300)}};
  check(drain(conflict) == a04_project(reference_full, plan.query(), z10_y300) &&
            a04_project(reference_full, plan.query(), z10_y300).empty(),
        "whole completion joined different values of a shared hidden variable");

  Query middle_query{{{"z", ScalarType::int64}, {"y", ScalarType::int64},
                      {"w", ScalarType::int64}},
                     {{"s", TableId{1}, {VariableId{0}, VariableId{1}}},
                      {"t", TableId{2}, {VariableId{1}, VariableId{0}, VariableId{2}}}},
                     {{VariableId{0}, "z"}, {VariableId{1}, "y"},
                      {VariableId{2}, "w"}}, false};
  const Relation expected_middle =
      a04_assignments(plan.catalog(), middle_query, database);
  auto middle_subtree = view.witnesses({}, WitnessFragment{.root = NodeId{1}});
  check_schema(middle_subtree.layout(), {VariableId{1}, VariableId{2}, VariableId{3}},
               "middle physical subtree");
  check(drain(middle_subtree) == expected_middle && expected_middle ==
            Relation{{n(10), n(100), n(7)}, {n(10), n(100), n(9)},
                     {n(10), n(101), n(10)}, {n(20), n(100), n(8)},
                     {n(30), n(300), n(11)}, {n(40), n(400), n(13)}},
        "subtree witnesses did not join all selected descendant factors");

  // The root factor survives for z=10 because y=100 or y=101 has a complete
  // descendant witness. Joining that S factor with the leaf factor at z=10
  // intentionally also permits y=999: the omitted middle factor is not part
  // of this exact factor selection.
  auto nonadjacent = view.witnesses({}, WitnessFragment{.nodes =
      std::vector<NodeId>{NodeId{0}, NodeId{2}}});
  check_schema(nonadjacent.layout(),
               {VariableId{0}, VariableId{1}, VariableId{2}, VariableId{3}},
               "nonadjacent factor selection");
  check(drain(nonadjacent) ==
            Relation{{n(1), n(10), n(100), n(7)},
                     {n(1), n(10), n(100), n(9)},
                     {n(1), n(10), n(101), n(10)},
                     {n(1), n(10), n(999), n(14)},
                     {n(2), n(20), n(100), n(8)},
                     {n(2), n(20), n(300), n(12)},
                     {n(3), n(30), n(300), n(11)},
                     {n(4), n(40), n(400), n(13)}},
        "nonadjacent S-factor join did not retain shared values or omit the middle factor");

  auto omitted_binding = view.witnesses({{VariableId{0}, n(999)}},
      WitnessFragment{.nodes = std::vector<NodeId>{NodeId{2}}});
  check(drain(omitted_binding) ==
            Relation{{n(10), n(100), n(7)}, {n(10), n(100), n(9)},
                     {n(10), n(101), n(10)}, {n(10), n(999), n(14)},
                     {n(20), n(100), n(8)}, {n(20), n(300), n(12)},
                     {n(30), n(300), n(11)}, {n(40), n(400), n(13)}},
        "factor selection did not ignore a valid binding absent from its variable union");
  view.close();
}

void shared_factor_values_and_generalized_products() {
  PhysicalRuntime shared(shared_siblings_plan());
  std::uint64_t sequence = 0;
  insert(shared, sequence, TableId{0}, {n(1), n(10)});
  insert(shared, sequence, TableId{0}, {n(2), n(20)});
  insert(shared, sequence, TableId{1}, {n(1), n(100)});
  insert(shared, sequence, TableId{1}, {n(1), n(101)});
  insert(shared, sequence, TableId{1}, {n(3), n(300)});
  auto view = shared.current_view();
  auto siblings = view.witnesses({}, WitnessFragment{.nodes =
      std::vector<NodeId>{NodeId{2}, NodeId{1}}});
  check_schema(siblings.layout(), {VariableId{0}, VariableId{1}, VariableId{2}},
               "disconnected siblings with shared variables");
  check(drain(siblings) == Relation{{n(1), n(10), n(100)},
                                    {n(1), n(10), n(101)}},
        "disconnected selected factors did not agree on their shared variable");
  auto parent_factor = view.witnesses({}, WitnessFragment{.nodes =
      std::vector<NodeId>{NodeId{0}}});
  check_schema(parent_factor.layout(), {VariableId{0}}, "generalized parent factor");
  check(drain(parent_factor) == Relation{{n(1)}},
        "generalized S factor retained a key without support from every child");
  view.close();

  for (const std::size_t arity : {std::size_t{3}, std::size_t{8}}) {
    PhysicalRuntime product(product_plan(arity));
    std::uint64_t product_sequence = 0;
    std::vector<std::vector<Value>> choices(arity);
    for (std::size_t i = 0; i < arity; ++i) {
      for (std::int64_t offset = 0; offset < 2; ++offset) {
        const auto value = static_cast<std::int64_t>(i * 100 +
            static_cast<std::size_t>(offset) + 1);
        choices[i].push_back(n(value));
        insert(product, product_sequence, TableId{i}, {n(value)});
      }
    }

    Relation expected{{}};
    for (const auto& values : choices) {
      Relation next;
      for (const auto& prefix : expected)
        for (const auto& value : values) {
          Row row = prefix;
          row.push_back(value);
          next.insert(std::move(row));
        }
      expected = std::move(next);
    }

    auto product_view = product.current_view();
    auto all = product_view.witnesses();
    std::vector<VariableId> all_variables;
    for (std::size_t i = 0; i < arity; ++i) all_variables.push_back(VariableId{i});
    check_schema(all.layout(), all_variables, "generalized-root product");
    check(drain(all) == expected,
          "generalized root did not enumerate its complete child product");
    auto root = product_view.witnesses({}, WitnessFragment{.root = NodeId{0}});
    check(drain(root) == expected,
          "root-selected witnesses differed from the full generalized subtree");

    const std::size_t left = arity == 3 ? 0 : 1;
    const std::size_t right = arity - 1;
    auto selected = product_view.witnesses({}, WitnessFragment{.nodes =
        std::vector<NodeId>{NodeId{right + 1}, NodeId{left + 1}}});
    Relation expected_selected;
    for (const auto& left_value : choices[left])
      for (const auto& right_value : choices[right])
        expected_selected.insert({left_value, right_value});
    check_schema(selected.layout(), {VariableId{left}, VariableId{right}},
                 "exact generalized child-factor selection");
    check(drain(selected) == expected_selected,
          "exact disconnected factor selection did not form its independent product");
    product_view.close();
  }
}

void self_join_aliases_keep_positive_support_during_delete() {
  auto plan = self_join_plan();
  PhysicalRuntime runtime(plan);
  Database before_database;
  before_database.tables.resize(1);
  const Row first{n(1), n(10)};
  const Row second{n(1), n(20)};
  before_database.tables[0].insert(first);
  before_database.tables[0].insert(second);
  std::uint64_t sequence = 0;
  insert(runtime, sequence, TableId{0}, first);
  insert(runtime, sequence, TableId{0}, second);

  Database after_database = before_database;
  check(after_database.tables[0].erase(first) == 1,
        "self-join reference fixture did not contain the deleted source row");
  const Relation expected_before =
      a04_assignments(plan.catalog(), plan.query(), before_database);
  const Relation expected_after =
      a04_assignments(plan.catalog(), plan.query(), after_database);
  check(expected_before.size() == 4 && expected_after == Relation{{n(1), n(20), n(20)}},
        "A04 self-join fixture did not yield four-to-one full assignments");

  auto pending = runtime.prepare({3, TableId{0}, SetOperation::erase, first});
  check(pending.preview().derivations.size() == 2,
        "self-join erase did not route through both occurrence aliases");
  auto before = pending.view(SnapshotSide::before);
  auto after = pending.view(SnapshotSide::after);
  auto before_full = before.witnesses();
  auto after_full = after.witnesses();
  check(drain(before_full) == expected_before && drain(after_full) == expected_after,
        "self-join before/after witness assignments differ from A04");

  auto before_projected = before.completions({});
  auto after_projected = after.completions({});
  check(drain(before_projected) == a04_project(expected_before, plan.query()) &&
            drain(after_projected) == a04_project(expected_after, plan.query()) &&
            a04_project(expected_before, plan.query()) == Relation{{n(1)}} &&
            a04_project(expected_after, plan.query()) == Relation{{n(1)}},
        "self-join erase removed an answer with surviving support");

  const FixedAssignment hidden{{VariableId{1}, n(10)},
                               {VariableId{2}, n(20)}};
  auto before_hidden = before.completions(hidden);
  auto after_hidden = after.completions(hidden);
  check(drain(before_hidden) == a04_project(expected_before, plan.query(), hidden) &&
            drain(after_hidden) == a04_project(expected_after, plan.query(), hidden) &&
            a04_project(expected_before, plan.query(), hidden) == Relation{{n(1)}} &&
            a04_project(expected_after, plan.query(), hidden).empty(),
        "self-join hidden bindings did not track both updated aliases atomically");

  static_cast<void>(pending.commit());
  before.close();
  after.close();
  check(runtime.ready(), "self-join committed views retained the writer lease");
}

void typed_bindings_nullary_values_and_constant_routes() {
  PhysicalRuntime typed(typed_plan());
  std::uint64_t sequence = 0;
  const Row first{n(5), s("alpha"), day("2025-03-08"), decimal("12.30"), true};
  const Row second{n(5), s("beta"), day("2024-02-29"), decimal("4.50"), false};
  insert(typed, sequence, TableId{0}, first);
  insert(typed, sequence, TableId{0}, second);
  auto typed_view = typed.current_view();
  auto typed_witness = typed_view.witnesses(
      {{VariableId{1}, s("alpha")}, {VariableId{2}, day("2025-03-08")},
       {VariableId{3}, decimal("12.30")}, {VariableId{4}, true}});
  check_schema(typed_witness.layout(),
               {VariableId{0}, VariableId{1}, VariableId{2}, VariableId{3}, VariableId{4}},
               "typed witness bindings");
  check(drain(typed_witness) == Relation{first},
        "string/date/decimal/boolean bindings did not select the typed witness");
  expect_error([&] {
    static_cast<void>(typed_view.witnesses({{VariableId{2}, s("2025-03-08")}}));
  }, "invalid_binding");
  expect_error([&] {
    static_cast<void>(typed_view.completions({{VariableId{3}, n(12)}}));
  }, "invalid_binding");
  typed_view.close();

  PhysicalRuntime flags(nullary_atom_plan());
  std::uint64_t flag_sequence = 0;
  auto empty_flags = flags.current_view();
  auto absent_flag = empty_flags.witnesses();
  check(drain(absent_flag).empty(), "empty nullary factor produced a witness");
  auto identity = empty_flags.witnesses({}, WitnessFragment{.nodes =
      std::vector<NodeId>{}});
  check(drain(identity) == Relation{{}},
        "empty selected factor set depended on an unselected nullary atom");
  empty_flags.close();

  insert(flags, flag_sequence, TableId{0}, {s("first")});
  auto populated_flags = flags.current_view();
  auto nullary = populated_flags.witnesses();
  check_schema(nullary.layout(), {}, "nullary factor assignment");
  check(drain(nullary) == Relation{{}},
        "supported nullary native factor failed to emit one empty assignment");
  populated_flags.close();

  PhysicalRuntime truth(constant_plan(true));
  auto true_view = truth.current_view();
  auto true_witness = true_view.witnesses();
  check(drain(true_witness) == Relation{{}},
        "constant-true query did not expose the nullary identity witness");
  true_view.close();
  PhysicalRuntime falsity(constant_plan(false));
  auto false_view = falsity.current_view();
  auto false_witness = false_view.witnesses();
  check(drain(false_witness).empty(),
        "constant-false query exposed a witness assignment");
  false_view.close();
}

void journal_commit_rollback_and_facade_lifetimes() {
  PhysicalRuntime runtime(one_hidden_variable_plan());
  std::uint64_t sequence = 0;
  insert(runtime, sequence, TableId{0}, {n(1), n(10)});
  insert(runtime, sequence, TableId{0}, {n(1), n(20)});

  auto pending = runtime.prepare({3, TableId{0}, SetOperation::erase, {n(1), n(10)}});
  check(pending.preview().physical_changed && pending.support().native_changed &&
            std::none_of(pending.support().transitions.begin(),
                         pending.support().transitions.end(),
                         [](const MembershipTransition& transition) {
                           return transition.handle.role == SupportRole::visible &&
                                  transition.operation == SetOperation::erase;
                         }),
        "deleting one hidden witness removed the still-supported visible key");
  auto before = pending.view(SnapshotSide::before);
  auto after = pending.view(SnapshotSide::after);
  auto before_projected = before.completions({});
  auto after_projected = after.completions({});
  check(drain(before_projected) == Relation{{n(1)}} &&
            drain(after_projected) == Relation{{n(1)}},
        "before/after completion lost the positive visible support count");
  auto before_cursor = before.witnesses();
  auto first_before = before_cursor.next();
  check(first_before.has_value(), "before witness cursor did not start before deletion");
  auto after_cursor = after.witnesses();
  check(drain(after_cursor) == Relation{{n(1), n(20)}},
        "after witness cursor retained the deleted hidden assignment");
  static_cast<void>(pending.commit());
  Relation continued{crown::storage::export_row(first_before->values())};
  while (auto row = before_cursor.next())
    check(continued.insert(crown::storage::export_row(row->values())).second,
          "before witness cursor repeated a row across commit");
  check(continued == Relation{{n(1), n(10)}, {n(1), n(20)}},
        "before witness cursor lost its hidden assignment across commit");
  before.close();
  after.close();
  check(runtime.ready(), "committed witness views retained the writer lease after closing");

  SupportRuntime support(one_hidden_variable_plan());
  auto staged = support.begin_epoch(1, SetOperation::insert);
  check(staged.stage(NodeId{0}, {n(2), n(30)}) &&
            staged.stage(NodeId{0}, {n(2), n(40)}),
        "multi-stage witness fixture did not accept both native rows");
  auto staged_before = staged.view(SnapshotSide::before);
  auto staged_after = staged.view(SnapshotSide::after);
  auto empty_before = staged_before.witnesses();
  check(drain(empty_before).empty(), "before view exposed staged witness assignments");
  auto tentative = staged_after.witnesses();
  auto tentative_first = tentative.next();
  check(tentative_first.has_value(), "tentative witness cursor did not expose its staged prefix");
  staged.rollback();
  check(!staged_before.valid() && !staged_after.valid() &&
            !tentative.active() && tentative.state() == ResultCursorState::failed,
        "rollback did not invalidate witness views and fail their active cursor");
  expect_error([&] { static_cast<void>(tentative.next()); }, "invalid_cursor");
  auto rolled_back = support.witnesses();
  check(drain(rolled_back).empty(), "rolled-back witness assignments remained visible");

  std::optional<SupportRuntime::EpochView> detached;
  std::optional<storage::Tuple> saved;
  {
    PhysicalRuntime owner(one_hidden_variable_plan());
    std::uint64_t owner_sequence = 0;
    insert(owner, owner_sequence, TableId{0}, {n(7), n(70)});
    detached.emplace(owner.current_view());
    auto cursor = detached->witnesses();
    saved = cursor.next();
    check(saved && saved->values() == Row{n(7), n(70)},
          "witness tuple did not own its assignment values");
    cursor.cancel();
  }
  check(detached && detached->valid() && saved &&
            saved->values() == Row{n(7), n(70)},
        "witness view or tuple depended on the physical facade lifetime");
  auto detached_cursor = detached->witnesses();
  check(drain(detached_cursor) == Relation{{n(7), n(70)}},
        "detached witness view could not enumerate after facade destruction");
  detached->close();
}

}  // namespace

int main() {
  try {
    hidden_bindings_project_without_multiplying_rows();
    local_fragments_and_full_physical_subtrees();
    physical_subtree_can_include_nodes_outside_c_star();
    depth_three_shared_hidden_variable_and_factor_subsets();
    shared_factor_values_and_generalized_products();
    self_join_aliases_keep_positive_support_during_delete();
    typed_bindings_nullary_values_and_constant_routes();
    journal_commit_rollback_and_facade_lifetimes();
    std::cout << "D02 hidden bindings and fragment witness cursors passed\n";
  } catch (const std::exception& failure) {
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
