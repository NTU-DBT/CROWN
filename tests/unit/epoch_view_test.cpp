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

Relation drain(SupportRuntime::ResultCursor& cursor) {
  Relation rows;
  while (auto row = cursor.next()) {
    check(row->layout().same_token(cursor.layout()),
          "view cursor returned a tuple with a different output layout token");
    check(rows.insert(crown::storage::export_row(row->values())).second,
          "view cursor emitted a duplicate projected row");
  }
  check(cursor.state() == ResultCursorState::exhausted && !cursor.active(),
        "view cursor did not release its lease on exhaustion");
  check(!cursor.next(), "exhausted view cursor did not keep returning nullopt");
  return rows;
}

void check_schema(const storage::TupleLayout& layout,
                  const std::vector<VariableId>& variables,
                  const std::string& context) {
  check(layout.fields().size() == variables.size(), context + ": wrong output arity");
  for (std::size_t i = 0; i < variables.size(); ++i)
    check(layout.fields()[i].variable == variables[i],
          context + ": output variables are not in the required order");
}

PhysicalPlan xy_plan() {
  const Catalog catalog{1, {{"r", {{"x", ScalarType::int64},
                                    {"y", ScalarType::int64}}}}};
  // Keep a deliberately non-sorted head so whole-query output order can be
  // distinguished from the sorted schema of a root fragment.
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
                    {{"r", TableId{0}, {VariableId{0}, VariableId{1}}}},
                    {{VariableId{1}, "y"}, {VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan hidden_witness_plan() {
  const Catalog catalog{1, {{"r", {{"x", ScalarType::int64},
                                    {"witness", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"witness", ScalarType::int64}},
                    {{"r", TableId{0}, {VariableId{0}, VariableId{1}}}},
                    {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan hidden_branch_plan() {
  const Catalog catalog{1, {{"r", {{"x", ScalarType::int64},
                                    {"z", ScalarType::int64}}},
                            {"s", {{"z", ScalarType::int64},
                                    {"w", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"z", ScalarType::int64},
                     {"w", ScalarType::int64}},
                    {{"r", TableId{0}, {VariableId{0}, VariableId{1}}},
                     {"s", TableId{1}, {VariableId{1}, VariableId{2}}}},
                    {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, {VariableId{1}, VariableId{2}}, {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan chain_plan() {
  const Catalog catalog{1, {{"r", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}},
                            {"s", {{"y", ScalarType::int64}, {"z", ScalarType::int64}}},
                            {"t", {{"z", ScalarType::int64}, {"w", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64},
                     {"z", ScalarType::int64}, {"w", ScalarType::int64}},
                    {{"r", TableId{0}, {VariableId{0}, VariableId{1}}},
                     {"s", TableId{1}, {VariableId{1}, VariableId{2}}},
                     {"t", TableId{2}, {VariableId{2}, VariableId{3}}}},
                    {{VariableId{3}, "w"}, {VariableId{0}, "x"},
                     {VariableId{2}, "z"}, {VariableId{1}, "y"},
                     {VariableId{3}, "again_w"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, {VariableId{1}, VariableId{2}}, {NodeId{2}}, 1, {}},
       {"t", NodeKind::native, {VariableId{2}, VariableId{3}}, {}, 2, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan nullary_plan() {
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

void apply_insert(PhysicalRuntime& runtime, std::uint64_t& sequence,
                  TableId table, Row row) {
  const auto result = runtime.apply({++sequence, table, SetOperation::insert, row});
  check(result.input.physical_changed, "physical view fixture row was not inserted");
}

void full_head_witness_restriction_and_bindings() {
  auto plan = xy_plan();
  PhysicalRuntime runtime(plan);
  Database database;
  database.tables.resize(1);
  std::uint64_t sequence = 0;
  for (const Row& row : {Row{n(1), n(10)}, Row{n(1), n(20)}, Row{n(2), n(10)}}) {
    apply_insert(runtime, sequence, TableId{0}, row);
    database.tables[0].insert(row);
  }

  auto view = runtime.current_view();
  check(view.valid() && !view.tentative() && view.sequence() == sequence &&
            view.owner() == runtime.owner(),
        "current view did not pin the committed epoch identity");
  auto all = view.results();
  check_schema(all.layout(), {VariableId{1}, VariableId{0}},
               "whole-query result");
  const auto expected = reference::evaluate(plan.catalog(), plan.query(), database);
  check(drain(all) == expected,
        "current view differs from the independent A04 evaluator");

  const FixedAssignment exact{{VariableId{0}, n(1)}, {VariableId{1}, n(20)}};
  auto exact_cursor = view.completions(exact);
  check_schema(exact_cursor.layout(), {VariableId{1}, VariableId{0}},
               "whole-query completions");
  check(drain(exact_cursor) == Relation{{n(20), n(1)}},
        "empty-separator root completion ignored one of its full-head witnesses");

  const FixedAssignment partial{{VariableId{0}, n(1)}};
  auto partial_cursor = view.completions(partial);
  check(drain(partial_cursor) == Relation{{n(10), n(1)}, {n(20), n(1)}},
        "partial visible-variable binding returned the wrong completions");
  const FixedAssignment repeated{{VariableId{0}, n(1)}, {VariableId{0}, n(1)}};
  auto repeated_cursor = view.completions(repeated);
  check(drain(repeated_cursor) == Relation{{n(10), n(1)}, {n(20), n(1)}},
        "repeated identical variable binding was not accepted");

  expect_error([&] {
    static_cast<void>(view.completions({{VariableId{0}, n(1)}, {VariableId{0}, n(2)}}));
  }, "invalid_binding");
  expect_error([&] {
    static_cast<void>(view.completions({{VariableId{0}, s("wrong type")}}));
  }, "invalid_binding");
  expect_error([&] {
    static_cast<void>(view.completions({{VariableId{99}, n(1)}}));
  }, "invalid_binding");

  auto fragment = view.completions(exact, VisibleFragment{NodeId{0}});
  check_schema(fragment.layout(), {VariableId{0}, VariableId{1}},
               "root fragment");
  check(drain(fragment) == Relation{{n(1), n(20)}},
        "root fragment did not emit its sorted visible-variable schema");
  auto unbound_fragment = view.completions({}, VisibleFragment{NodeId{0}});
  check(drain(unbound_fragment) == Relation{{n(1), n(10)}, {n(1), n(20)}, {n(2), n(10)}},
        "root fragment did not enumerate all visible root rows");
  expect_error([&] {
    static_cast<void>(view.completions({}, VisibleFragment{NodeId{99}}));
  }, "invalid_fragment");

  check(runtime.current_view().valid(), "a second current view could not be constructed");
  expect_error([&] {
    static_cast<void>(runtime.apply({sequence + 1, TableId{0}, SetOperation::insert,
                                     {n(3), n(30)}}));
  }, "runtime_busy");
  view.close();
}

void hidden_bindings_and_c_star_fragments() {
  PhysicalRuntime runtime(hidden_witness_plan());
  std::uint64_t sequence = 0;
  apply_insert(runtime, sequence, TableId{0}, {n(1), n(10)});
  apply_insert(runtime, sequence, TableId{0}, {n(1), n(20)});
  auto view = runtime.current_view();
  auto visible = view.completions({{VariableId{0}, n(1)}});
  check(drain(visible) == Relation{{n(1)}},
        "visible binding did not collapse hidden witnesses");
  auto hidden_match = view.completions({{VariableId{1}, n(10)}});
  check(drain(hidden_match) == Relation{{n(1)}},
        "hidden binding did not restrict a projected completion");
  auto hidden_miss = view.completions({{VariableId{1}, n(99)}});
  check(drain(hidden_miss).empty(),
        "unsupported hidden binding returned a projected completion");
  view.close();

  PhysicalRuntime branch(hidden_branch_plan());
  std::uint64_t branch_sequence = 0;
  apply_insert(branch, branch_sequence, TableId{0}, {n(4), n(7)});
  apply_insert(branch, branch_sequence, TableId{1}, {n(7), n(8)});
  check(std::none_of(branch.plan().enumeration().steps.begin(),
                     branch.plan().enumeration().steps.end(),
                     [](const auto& step) { return step.node == NodeId{1}; }),
        "hidden branch unexpectedly entered the C* enumeration");
  auto branch_view = branch.current_view();
  expect_error([&] {
    static_cast<void>(branch_view.completions({}, VisibleFragment{NodeId{1}}));
  }, "invalid_fragment");
  branch_view.close();
}

void ancestor_child_chain_and_independent_ejoin() {
  auto plan = chain_plan();
  PhysicalRuntime runtime(plan);
  Database database;
  database.tables.resize(3);
  std::uint64_t sequence = 0;
  const std::vector<Row> r_rows{{n(1), n(10)}, {n(1), n(20)}, {n(2), n(10)}};
  const std::vector<Row> s_rows{{n(10), n(100)}, {n(10), n(200)}, {n(20), n(300)}};
  const std::vector<Row> t_rows{{n(100), n(7)}, {n(100), n(70)},
                                {n(200), n(8)}, {n(300), n(9)}};
  for (const auto& row : r_rows) {
    apply_insert(runtime, sequence, TableId{0}, row);
    database.tables[0].insert(row);
  }
  for (const auto& row : s_rows) {
    apply_insert(runtime, sequence, TableId{1}, row);
    database.tables[1].insert(row);
  }
  for (const auto& row : t_rows) {
    apply_insert(runtime, sequence, TableId{2}, row);
    database.tables[2].insert(row);
  }
  check(plan.enumeration().steps.size() == 3 &&
            plan.enumeration().steps[1].parent_step == 0 &&
            plan.enumeration().steps[2].parent_step == 1,
        "fixture did not preserve its three-level C* chain");

  Relation hand_ejoin;
  Relation sorted_whole;
  for (const auto& r : r_rows)
    for (const auto& ss : s_rows) {
      if (r[1] != ss[0]) continue;
      for (const auto& t : t_rows) {
        if (ss[1] != t[0]) continue;
        hand_ejoin.insert({t[1], r[0], ss[1], r[1], t[1]});
        sorted_whole.insert({r[0], r[1], ss[1], t[1]});
      }
    }
  const auto expected = reference::evaluate(plan.catalog(), plan.query(), database);
  check(hand_ejoin == expected,
        "hand-built three-relation E-join disagrees with the independent A04 evaluator");

  auto view = runtime.current_view();
  auto full = view.results();
  check_schema(full.layout(), {VariableId{3}, VariableId{0}, VariableId{2},
                               VariableId{1}, VariableId{3}},
               "chain whole-query result");
  check(drain(full) == expected,
        "three-level before/current view traversal disagrees with its E-join");

  auto whole_fragment = view.completions({}, VisibleFragment{NodeId{0}});
  check_schema(whole_fragment.layout(), {VariableId{0}, VariableId{1},
                                         VariableId{2}, VariableId{3}},
               "chain root fragment");
  check(drain(whole_fragment) == sorted_whole,
        "root fragment did not join ancestor and descendant C* rows");

  auto child_fragment = view.completions({{VariableId{1}, n(10)}},
                                         VisibleFragment{NodeId{1}});
  check_schema(child_fragment.layout(), {VariableId{1}, VariableId{2}, VariableId{3}},
               "chain child fragment");
  check(drain(child_fragment) == Relation{{n(10), n(100), n(7)},
                                          {n(10), n(100), n(70)},
                                          {n(10), n(200), n(8)}},
        "subtree fragment did not traverse its child and grandchild rows");
  view.close();
}

void projection_count_changes_keep_visible_rows() {
  SupportRuntime runtime(hidden_witness_plan());
  check(runtime.apply({1, NodeId{0}, SetOperation::insert, {n(1), n(10)}}).native_changed,
        "projection-count fixture did not insert its first native witness");
  check(runtime.apply({2, NodeId{0}, SetOperation::insert, {n(1), n(20)}}).native_changed,
        "projection-count fixture did not insert its second native witness");
  auto pending = runtime.begin_epoch(3, SetOperation::erase);
  check(pending.stage(NodeId{0}, {n(1), n(10)}),
        "projection-count fixture did not stage its witness deletion");
  auto before = pending.view(SnapshotSide::before);
  auto after = pending.view(SnapshotSide::after);
  check(before.tentative() && after.tentative() &&
            before.metrics().journal_records > 0 && after.metrics().journal_records > 0,
        "tentative projection views omitted their journal-backed work");
  check(before.metrics().membership_changes > 0 && after.metrics().membership_changes > 0,
        "projection-count fixture did not include its removed hidden witness membership");
  auto before_rows = before.results();
  auto after_rows = after.results();
  check(drain(before_rows) == Relation{{n(1)}} && drain(after_rows) == Relation{{n(1)}},
        "positive visible projection support change removed a still-supported answer");
  static_cast<void>(pending.commit());
  before.close();
  after.close();
}

void pending_view_freezes_prefix_and_commit_preserves_old_cursor() {
  PhysicalRuntime runtime(xy_plan());
  std::uint64_t sequence = 0;
  apply_insert(runtime, sequence, TableId{0}, {n(1), n(10)});
  apply_insert(runtime, sequence, TableId{0}, {n(2), n(20)});
  const auto deleted_handle = runtime.find_source(TableId{0}, {n(2), n(20)});
  check(deleted_handle.has_value(), "pending-view fixture could not find the row to erase");

  auto pending = runtime.prepare({3, TableId{0}, SetOperation::erase, {n(2), n(20)}});
  expect_error([&] {
    static_cast<void>(pending.view(SnapshotSide::after, EpochViewOptions{.work_limit = 0}));
  }, "resource_limit");
  check(pending.active(), "failed view construction auto-aborted its prepared update");

  auto before = pending.view(SnapshotSide::before);
  auto after = pending.view(SnapshotSide::after);
  check(before.tentative() && after.tentative() && before.sequence() == 2 &&
            after.sequence() == 3 && before.owner() == runtime.owner(),
        "pending before/after views do not identify both sides of the update");
  const auto& before_metrics = before.metrics();
  const auto& after_metrics = after.metrics();
  check(before_metrics.work == after_metrics.work &&
            before_metrics.journal_records == after_metrics.journal_records &&
            before_metrics.membership_changes == after_metrics.membership_changes &&
            before_metrics.restored_rows == after_metrics.restored_rows &&
            before_metrics.excluded_rows == after_metrics.excluded_rows &&
            before_metrics.restored_rows > 0 && before_metrics.excluded_rows == 0,
        "before/after views did not share metrics for the before-relative-to-after patch");

  std::optional<SupportRuntime::EpochView> before_copy;
  before_copy.emplace(before);
  std::optional<SupportRuntime::ResultCursor> before_cursor;
  before_cursor.emplace(before.results());
  auto initial_before_row = before_cursor->next();
  check(initial_before_row && initial_before_row->values() == Row{n(10), n(1)},
        "before cursor did not begin from the committed visible rows");
  std::optional<SupportRuntime::ResultCursor> after_cursor;
  after_cursor.emplace(after.results());
  check(drain(*after_cursor) == Relation{{n(10), n(1)}},
        "after cursor exposed a row deleted by the pending update");

  expect_error([&] { static_cast<void>(runtime.results()); }, "runtime_busy");
  expect_error([&] { static_cast<void>(runtime.core_results()); }, "runtime_busy");
  expect_error([&] { static_cast<void>(runtime.current_view()); }, "runtime_busy");
  expect_error([&] {
    static_cast<void>(runtime.apply({4, TableId{0}, SetOperation::insert,
                                     {n(3), n(30)}}));
  }, "runtime_busy");

  static_cast<void>(pending.commit());
  check(runtime.sequence() == 3 && before.valid() && after.valid(),
        "commit invalidated views of the published journal prefix");
  auto deleted_before_row = before_cursor->next();
  check(deleted_before_row && deleted_before_row->values() == Row{n(20), n(2)},
        "partially consumed before cursor lost its deleted row after commit");
  check(!before_cursor->next(), "before cursor emitted more rows than its snapshot");
  check(!runtime.get_source(TableId{0}, *deleted_handle),
        "committed physical erase left the source row live");
  const auto retained = runtime.storage_statistics();
  check(retained.support.retained_records > 0,
        "journal-backed before view did not pin deleted support rows");

  expect_error([&] {
    static_cast<void>(runtime.apply({4, TableId{0}, SetOperation::insert,
                                     {n(3), n(30)}}));
  }, "runtime_busy");
  before.close();
  expect_error([&] {
    static_cast<void>(runtime.apply({4, TableId{0}, SetOperation::insert,
                                     {n(3), n(30)}}));
  }, "runtime_busy");
  before_copy->close();
  before_copy.reset();
  before_cursor.reset();
  expect_error([&] {
    static_cast<void>(runtime.apply({4, TableId{0}, SetOperation::insert,
                                     {n(3), n(30)}}));
  }, "runtime_busy");
  after.close();
  after_cursor.reset();

  check(runtime.storage_statistics().support.retained_records == 0,
        "closing every view and cursor did not release erased-row pins");
  check(runtime.ready(), "closing every view and cursor did not release the writer lease");
  sequence = runtime.sequence();
  apply_insert(runtime, sequence, TableId{0}, {n(3), n(30)});
  check(runtime.sequence() == 4,
        "physical inputs did not resume after every committed view lease closed");
}

void pending_chain_leaf_delete_restores_ghost_rows_through_parent_keys() {
  const auto plan = chain_plan();
  PhysicalRuntimeOptions options;
  options.support.capture_transitions = true;
  PhysicalRuntime runtime(plan, options);
  Database before_database;
  before_database.tables.resize(3);
  std::uint64_t sequence = 0;
  const std::vector<Row> r_rows{{n(1), n(10)}, {n(2), n(20)}};
  const std::vector<Row> s_rows{{n(10), n(100)}, {n(20), n(200)}};
  const std::vector<Row> t_rows{{n(100), n(7)}, {n(200), n(8)}};
  for (const auto& row : r_rows) {
    apply_insert(runtime, sequence, TableId{0}, row);
    before_database.tables[0].insert(row);
  }
  for (const auto& row : s_rows) {
    apply_insert(runtime, sequence, TableId{1}, row);
    before_database.tables[1].insert(row);
  }
  for (const auto& row : t_rows) {
    apply_insert(runtime, sequence, TableId{2}, row);
    before_database.tables[2].insert(row);
  }

  const Row leaf{n(100), n(7)};
  Database after_database = before_database;
  check(after_database.tables[2].erase(leaf) == 1,
        "chain fixture did not contain its leaf row");
  const Relation expected_before = reference::evaluate(plan.catalog(), plan.query(), before_database);
  const Relation expected_after = reference::evaluate(plan.catalog(), plan.query(), after_database);
  Query subtree_query{{{"y", ScalarType::int64}, {"z", ScalarType::int64},
                       {"w", ScalarType::int64}},
      {{"s", TableId{1}, {VariableId{0}, VariableId{1}}},
       {"t", TableId{2}, {VariableId{1}, VariableId{2}}}},
      {{VariableId{0}, "y"}, {VariableId{1}, "z"}, {VariableId{2}, "w"}}, false};
  const Relation expected_subtree_before =
      reference::evaluate(plan.catalog(), subtree_query, before_database);
  const Relation expected_subtree_after =
      reference::evaluate(plan.catalog(), subtree_query, after_database);
  const auto matching_field = [](const Relation& rows, std::size_t field, const Value& value) {
    Relation selected;
    for (const auto& row : rows)
      if (row.at(field) == value) selected.insert(row);
    return selected;
  };
  check(expected_before.size() == 2 && expected_after.size() == 1 &&
            expected_subtree_before.size() == 2 && expected_subtree_after.size() == 1,
        "three-level chain fixture did not retain its independent branch after deletion");

  auto pending = runtime.prepare({sequence + 1, TableId{2}, SetOperation::erase, leaf});
  auto before = pending.view(SnapshotSide::before);
  auto after = pending.view(SnapshotSide::after);
  const auto& deletion_metrics = before.metrics();
  check(deletion_metrics.restored_rows > 0 && deletion_metrics.excluded_rows == 0 &&
            before.metrics().restored_rows == after.metrics().restored_rows &&
            before.metrics().excluded_rows == after.metrics().excluded_rows,
        "leaf deletion did not produce one shared before-relative restoration patch");
  std::set<std::size_t> erased_visible_nodes;
  for (const auto& transition : pending.support().transitions)
    if (transition.handle.role == SupportRole::visible &&
        transition.operation == SetOperation::erase)
      erased_visible_nodes.insert(transition.handle.node.value);
  check(erased_visible_nodes == std::set<std::size_t>{0, 1, 2},
        "leaf deletion did not change visible E membership at the leaf and both ancestors");

  auto before_full = before.results();
  auto after_full = after.results();
  check(drain(before_full) == expected_before && drain(after_full) == expected_after,
        "prepared chain views differ from independent before/after database evaluation");
  const FixedAssignment parent_binding{{VariableId{1}, n(10)}};
  auto before_bound = before.completions(parent_binding);
  auto after_bound = after.completions(parent_binding);
  check(drain(before_bound) == matching_field(expected_before, 3, n(10)) &&
            drain(after_bound) == matching_field(expected_after, 3, n(10)),
        "typed parent-key binding returned wrong full-query completions across deletion");
  auto before_child = before.completions(parent_binding, VisibleFragment{NodeId{1}});
  auto after_child = after.completions(parent_binding, VisibleFragment{NodeId{1}});
  check(drain(before_child) == matching_field(expected_subtree_before, 0, n(10)) &&
            drain(after_child) == matching_field(expected_subtree_after, 0, n(10)),
        "child-root fragment did not follow its parent-key bucket across deletion");

  auto continuing_before = before.results();
  auto first_before_row = continuing_before.next();
  check(first_before_row.has_value(), "before cursor could not begin before the pending deletion");
  Relation continued_before_rows{crown::storage::export_row(first_before_row->values())};
  static_cast<void>(pending.commit());
  while (auto row = continuing_before.next())
    check(continued_before_rows.insert(crown::storage::export_row(row->values())).second,
          "partially consumed chain before cursor repeated a row after commit");
  check(continued_before_rows == expected_before,
        "partially consumed chain before cursor lost a restored ghost row across commit");
  before.close();
  after.close();
  check(runtime.ready(), "closed chain deletion views kept the runtime leased");

  Database insertion_before_database = after_database;
  Database insertion_after_database = before_database;
  const Relation expected_insert_before =
      reference::evaluate(plan.catalog(), plan.query(), insertion_before_database);
  const Relation expected_insert_after =
      reference::evaluate(plan.catalog(), plan.query(), insertion_after_database);
  const Relation expected_insert_subtree_before =
      reference::evaluate(plan.catalog(), subtree_query, insertion_before_database);
  const Relation expected_insert_subtree_after =
      reference::evaluate(plan.catalog(), subtree_query, insertion_after_database);
  auto insertion = runtime.prepare({runtime.sequence() + 1, TableId{2}, SetOperation::insert, leaf});
  auto insertion_before = insertion.view(SnapshotSide::before);
  auto insertion_after = insertion.view(SnapshotSide::after);
  check(insertion_before.metrics().restored_rows == 0 &&
            insertion_before.metrics().excluded_rows > 0 &&
            insertion_before.metrics().excluded_rows == insertion_after.metrics().excluded_rows,
        "leaf insertion did not produce one shared before-relative exclusion patch");
  auto insertion_before_full = insertion_before.results();
  auto insertion_after_full = insertion_after.results();
  check(drain(insertion_before_full) == expected_insert_before &&
            drain(insertion_after_full) == expected_insert_after,
        "prepared chain insertion views differ from independent before/after evaluation");
  auto insertion_before_child =
      insertion_before.completions(parent_binding, VisibleFragment{NodeId{1}});
  auto insertion_after_child =
      insertion_after.completions(parent_binding, VisibleFragment{NodeId{1}});
  check(drain(insertion_before_child) ==
            matching_field(expected_insert_subtree_before, 0, n(10)) &&
            drain(insertion_after_child) ==
            matching_field(expected_insert_subtree_after, 0, n(10)),
        "child-root fragment did not exclude the inserted parent-key bucket on the before side");
  static_cast<void>(insertion.commit());
  insertion_before.close();
  insertion_after.close();
  check(runtime.ready(), "closed chain insertion views kept the runtime leased");
}

void current_view_copies_and_multiple_cursors_guard_mutations() {
  SupportRuntime runtime(xy_plan());
  static_cast<void>(runtime.apply({1, NodeId{0}, SetOperation::insert,
                                   {n(1), n(10)}}));
  auto view = runtime.current_view();
  auto copy = view;
  check(view.valid() && !view.tentative() && view.sequence() == 1 &&
            view.owner() == runtime.owner(),
        "current logical view has the wrong committed identity");
  std::optional<SupportRuntime::ResultCursor> first;
  std::optional<SupportRuntime::ResultCursor> second;
  first.emplace(view.results());
  second.emplace(copy.results());
  check(first->sequence() == 1 && second->owner() == runtime.owner(),
        "view cursors did not retain their source epoch identity");
  auto first_row = first->next();
  auto second_row = second->next();
  check(first_row && second_row && first_row->values() == Row{n(10), n(1)} &&
            second_row->values() == Row{n(10), n(1)},
        "multiple current-view cursors did not independently read the committed row");
  expect_error([&] {
    static_cast<void>(runtime.apply({2, NodeId{0}, SetOperation::insert,
                                     {n(2), n(20)}}));
  }, "runtime_busy");

  view.close();
  check(!view.valid(), "closing one view facade did not clear that facade");
  expect_error([&] {
    static_cast<void>(runtime.apply({2, NodeId{0}, SetOperation::insert,
                                     {n(2), n(20)}}));
  }, "runtime_busy");
  copy.close();
  first.reset();
  expect_error([&] {
    static_cast<void>(runtime.apply({2, NodeId{0}, SetOperation::insert,
                                     {n(2), n(20)}}));
  }, "runtime_busy");
  second.reset();
  check(runtime.apply({2, NodeId{0}, SetOperation::insert,
                       {n(2), n(20)}}).native_changed,
        "current-view read lease did not end after its last cursor closed");
}

void pending_logical_stage_resumes_only_after_all_view_copies_close() {
  SupportRuntime runtime(xy_plan());
  auto pending = runtime.begin_epoch(1, SetOperation::insert);
  check(pending.stage(NodeId{0}, {n(1), n(10)}),
        "pending-view stage fixture did not add its first row");
  expect_error([&] {
    static_cast<void>(pending.view(SnapshotSide::after,
                                   EpochViewOptions{.work_limit = 0}));
  }, "resource_limit");
  check(pending.active(), "failed logical view construction closed its pending epoch");

  auto view = pending.view(SnapshotSide::after);
  auto copy = view;
  std::optional<SupportRuntime::ResultCursor> cursor;
  cursor.emplace(view.results());
  auto tentative_row = cursor->next();
  check(tentative_row && tentative_row->values() == Row{n(10), n(1)},
        "owner-only cursor could not read its tentative view while pending");
  expect_error([&] { static_cast<void>(runtime.results()); }, "runtime_busy");
  expect_error([&] { static_cast<void>(runtime.snapshot()); }, "runtime_busy");
  expect_error([&] { static_cast<void>(runtime.has_answer()); }, "runtime_busy");
  expect_error([&] { static_cast<void>(pending.stage(NodeId{0}, {n(2), n(20)})); },
               "runtime_busy");
  check(pending.active() && pending.preview().native_changed,
        "a rejected stage while a view was held auto-aborted the pending epoch");

  view.close();
  expect_error([&] { static_cast<void>(pending.stage(NodeId{0}, {n(2), n(20)})); },
               "runtime_busy");
  copy.close();
  expect_error([&] { static_cast<void>(pending.stage(NodeId{0}, {n(2), n(20)})); },
               "runtime_busy");
  cursor.reset();
  check(pending.stage(NodeId{0}, {n(2), n(20)}),
        "pending stage did not resume after all external view leases closed");
  check(pending.commit().native_changed && runtime.sequence() == 1,
        "resumed staged prefix did not commit as one logical epoch");
}

void rollback_invalidates_views_and_closes_cursors() {
  SupportRuntime runtime(xy_plan());
  auto pending = runtime.begin_epoch(1, SetOperation::insert);
  check(pending.stage(NodeId{0}, {n(1), n(10)}),
        "rollback fixture did not stage its tentative row");
  auto view = pending.view(SnapshotSide::after);
  std::optional<SupportRuntime::ResultCursor> first;
  std::optional<SupportRuntime::ResultCursor> second;
  first.emplace(view.results());
  second.emplace(view.completions({}));
  auto tentative_row = first->next();
  check(tentative_row && tentative_row->values() == Row{n(10), n(1)},
        "rollback fixture cursor did not read its tentative row");
  check(second->active(), "second rollback cursor did not keep its lease");

  pending.rollback();
  check(!pending.active() && !view.valid() && !first->active() && !second->active() &&
            first->state() == ResultCursorState::failed &&
            second->state() == ResultCursorState::failed,
        "rollback did not invalidate the view and proactively fail every active cursor");
  expect_error([&] { static_cast<void>(first->next()); }, "invalid_cursor");
  expect_error([&] { static_cast<void>(second->next()); }, "invalid_cursor");
  expect_error([&] { static_cast<void>(pending.view(SnapshotSide::before)); },
               "invalid_epoch");
  check(runtime.ready(), "aborted views kept the runtime in a pending state");
  check(runtime.apply({1, NodeId{0}, SetOperation::insert,
                       {n(2), n(20)}}).native_changed,
        "aborted view objects blocked later writes to the restored runtime");
  view.close();
  first.reset();
  second.reset();
}

void nullary_truth_constant_routes_and_noop_views() {
  PhysicalRuntime truth(nullary_plan());
  {
    auto empty = truth.current_view();
    auto empty_rows = empty.results();
    check(drain(empty_rows).empty(), "empty nullary view returned a truth row");
    empty.close();
  }

  {
    auto first = truth.prepare({1, TableId{0}, SetOperation::insert, {s("a")} });
    auto first_before = first.view(SnapshotSide::before);
    auto first_after = first.view(SnapshotSide::after);
    auto first_before_cursor = first_before.results();
    check(drain(first_before_cursor).empty(),
          "nullary before view was true before its first witness");
    auto first_after_cursor = first_after.results();
    check(drain(first_after_cursor) == Relation{{}},
          "nullary after view failed to project a true witness to one empty row");
    static_cast<void>(first.commit());
    first_before.close();
    first_after.close();
  }

  {
    auto second = truth.prepare({2, TableId{0}, SetOperation::insert, {s("b")} });
    check(second.preview().physical_changed && !second.support().native_changed,
          "second nullary witness was not recognized as a native logical no-op");
    auto duplicate_before = second.view(SnapshotSide::before);
    auto duplicate_after = second.view(SnapshotSide::after);
    auto duplicate_before_rows = duplicate_before.results();
    auto duplicate_after_rows = duplicate_after.results();
    check(drain(duplicate_before_rows) == Relation{{}} &&
              drain(duplicate_after_rows) == Relation{{}},
          "no-op nullary views did not preserve the existing truth row on both sides");
    static_cast<void>(second.commit());
    duplicate_before.close();
    duplicate_after.close();
  }

  {
    auto erase_one = truth.prepare({3, TableId{0}, SetOperation::erase, {s("a")} });
    auto still_before = erase_one.view(SnapshotSide::before);
    auto still_after = erase_one.view(SnapshotSide::after);
    auto still_before_rows = still_before.results();
    auto still_after_rows = still_after.results();
    check(drain(still_before_rows) == Relation{{}} &&
              drain(still_after_rows) == Relation{{}},
          "nullary truth disappeared while another physical witness remained");
    static_cast<void>(erase_one.commit());
    still_before.close();
    still_after.close();
  }

  {
    auto erase_last = truth.prepare({4, TableId{0}, SetOperation::erase, {s("b")} });
    auto true_before = erase_last.view(SnapshotSide::before);
    auto false_after = erase_last.view(SnapshotSide::after);
    auto true_rows = true_before.results();
    auto false_rows = false_after.results();
    check(drain(true_rows) == Relation{{}} && drain(false_rows).empty(),
          "nullary before/after truth did not follow last-witness deletion");
    static_cast<void>(erase_last.commit());
    true_before.close();
    false_after.close();
  }

  PhysicalRuntime constant_true(constant_plan(true));
  auto true_view = constant_true.current_view();
  auto constant_true_cursor = true_view.results();
  check(drain(constant_true_cursor) == Relation{{}},
        "constant-true route did not expose its nullary truth row");
  true_view.close();
  PhysicalRuntime constant_false(constant_plan(false));
  auto false_view = constant_false.current_view();
  auto constant_false_cursor = false_view.results();
  check(drain(constant_false_cursor).empty(),
        "constant-false route exposed a nullary row");
  false_view.close();
}

void view_and_value_owning_lifetimes_survive_facade_move_and_destruction() {
  std::optional<SupportRuntime::EpochView> detached;
  std::optional<storage::Tuple> saved;
  SupportOwnerId owner{};
  {
    PhysicalRuntime original(xy_plan());
    std::uint64_t sequence = 0;
    apply_insert(original, sequence, TableId{0}, {n(7), n(70)});
    detached.emplace(original.current_view());
    owner = original.owner();
    auto cursor = detached->completions({{VariableId{0}, n(7)}});
    saved = cursor.next();
    check(saved && saved->values() == Row{n(70), n(7)},
          "bound result tuple did not own its projected values");
    cursor.cancel();

    PhysicalRuntime moved(std::move(original));
    check(detached->owner() == moved.owner() && detached->owner() == owner,
          "moving the physical facade invalidated a live epoch view");
    auto copy = *detached;
    auto moved_cursor = copy.results();
    check(drain(moved_cursor) == Relation{{n(70), n(7)}},
          "copied view could not enumerate through a moved runtime facade");
    copy.close();
  }
  check(detached && detached->valid(),
        "epoch view did not retain its owner after the runtime facade was destroyed");
  auto moved_view = std::move(*detached);
  check(!detached->valid() && moved_view.valid(),
        "moving an epoch view did not transfer its live facade");
  auto cursor = moved_view.results();
  check(drain(cursor) == Relation{{n(70), n(7)}},
        "moved view could not read after its runtime facade was destroyed");
  moved_view.close();
  check(saved && saved->values() == Row{n(70), n(7)} &&
            saved->layout().fields().size() == 2,
        "copied result values or layout depended on the view/runtime lifetime");
}

}  // namespace

int main() {
  try {
    full_head_witness_restriction_and_bindings();
    hidden_bindings_and_c_star_fragments();
    ancestor_child_chain_and_independent_ejoin();
    projection_count_changes_keep_visible_rows();
    pending_view_freezes_prefix_and_commit_preserves_old_cursor();
    pending_chain_leaf_delete_restores_ghost_rows_through_parent_keys();
    current_view_copies_and_multiple_cursors_guard_mutations();
    pending_logical_stage_resumes_only_after_all_view_copies_close();
    rollback_invalidates_views_and_closes_cursors();
    nullary_truth_constant_routes_and_noop_views();
    view_and_value_owning_lifetimes_survive_facade_move_and_destruction();
    std::cout << "journal-backed epoch views and D02 completion foundation passed\n";
  } catch (const std::exception& failure) {
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
