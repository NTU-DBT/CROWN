#include "crown/api/error.hpp"
#include "crown/planner/verify.hpp"
#include "delta_model.hpp"
#include "evaluator.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <map>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

namespace {
using namespace crown;
using namespace crown::reference::delta;

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

template <class Action>
void expect_error(Action&& action, std::string_view code) {
  try {
    action();
  } catch (const Error& error) {
    check(error.code() == code,
          "expected " + std::string(code) + ", got " + error.code());
    return;
  }
  throw std::runtime_error("expected error " + std::string(code));
}

Value n(std::int64_t value) { return value; }
Value s(std::string value) { return value; }
Value b(bool value) { return value; }

struct Fixture {
  Catalog catalog;
  Query query;
  FreeConnexTree tree;
  Database database;
};

VariableSet variable_set(std::initializer_list<std::size_t> values) {
  VariableSet result;
  for (const auto value : values) result.insert(VariableId{value});
  return result;
}

// Convert one physical table row to the exact, set-valued occurrence row the
// model receives. Repeated variables and constants are handled like the A04
// evaluator; ignored columns never enter a native E factor.
std::optional<Row> occurrence_row(const Atom& atom, const Row& physical) {
  std::map<VariableId, Value> assignment;
  for (std::size_t column = 0; column < atom.terms.size(); ++column) {
    const auto& term = atom.terms[column];
    if (const auto* variable = std::get_if<VariableId>(&term)) {
      const auto [found, inserted] = assignment.emplace(*variable, physical[column]);
      if (!inserted && found->second != physical[column]) return std::nullopt;
    } else if (const auto* literal = std::get_if<Value>(&term)) {
      if (*literal != physical[column]) return std::nullopt;
    }
  }
  Row result;
  result.reserve(assignment.size());
  for (const auto& [variable, value] : assignment) {
    static_cast<void>(variable);
    result.push_back(value);
  }
  return result;
}

std::vector<Relation> native_inputs(const Fixture& fixture) {
  std::vector<Relation> result(fixture.tree.nodes.size());
  std::vector<bool> seen(fixture.query.atoms.size());
  for (std::size_t node_id = 0; node_id < fixture.tree.nodes.size(); ++node_id) {
    const auto& node = fixture.tree.nodes[node_id];
    if (node.kind != NodeKind::native) continue;
    check(node.occurrence.has_value(), "native tree node has no occurrence");
    const auto occurrence = *node.occurrence;
    check(occurrence < fixture.query.atoms.size() && !seen[occurrence],
          "native tree occurrence is out of range or repeated");
    seen[occurrence] = true;
    const auto& atom = fixture.query.atoms[occurrence];
    for (const auto& row : fixture.database.tables.at(atom.table.value)) {
      if (const auto projected = occurrence_row(atom, row))
        result[node_id].insert(*projected);
    }
  }
  check(std::all_of(seen.begin(), seen.end(), [](bool value) { return value; }),
        "fixture tree does not cover every query occurrence");
  return result;
}

Snapshot snapshot(const Fixture& fixture) {
  const auto checked = planner::validate_tree(fixture.catalog, fixture.query, fixture.tree);
  check(checked.valid, "fixture has an invalid free-connex tree");
  return recompute(fixture.catalog, fixture.query, fixture.tree,
                   native_inputs(fixture));
}

// Make an alias-prefix database: each query occurrence gets a fresh table,
// with the same physical rows as its original base table. This lets the
// independent A04 evaluator check alias-local occurrence expansion directly.
std::pair<std::pair<Catalog, Query>, Database> occurrence_expansion(
    const Fixture& fixture) {
  Catalog catalog;
  catalog.version = fixture.catalog.version;
  Database database;
  Query query = fixture.query;
  for (std::size_t occurrence = 0; occurrence < fixture.query.atoms.size(); ++occurrence) {
    const auto& original = fixture.query.atoms[occurrence];
    const auto new_id = TableId{catalog.tables.size()};
    auto table = fixture.catalog.tables.at(original.table.value);
    table.name += "__occ" + std::to_string(occurrence);
    catalog.tables.push_back(std::move(table));
    database.tables.push_back(fixture.database.tables.at(original.table.value));
    query.atoms[occurrence].table = new_id;
  }
  return {{std::move(catalog), std::move(query)}, std::move(database)};
}

Relation exact_delta(const Relation& before, const Relation& after,
                     SetOperation operation) {
  Relation result;
  if (operation == SetOperation::insert) {
    std::set_difference(after.begin(), after.end(), before.begin(), before.end(),
                        std::inserter(result, result.end()));
  } else {
    std::set_difference(before.begin(), before.end(), after.begin(), after.end(),
                        std::inserter(result, result.end()));
  }
  return result;
}

Relation as_set(const std::vector<Row>& rows) {
  return Relation(rows.begin(), rows.end());
}

Relation project_answer_to_scope(const Relation& answer,
                                const Snapshot& query_snapshot,
                                const std::vector<VariableId>& scope) {
  Relation result;
  std::map<VariableId, std::size_t> positions;
  for (std::size_t field = 0; field < query_snapshot.head.size(); ++field)
    positions.emplace(query_snapshot.head[field], field);
  for (const auto& output : answer) {
    std::map<VariableId, Value> assignment;
    for (const auto& [variable, position] : positions)
      assignment.emplace(variable, output[position]);
    Row projected;
    projected.reserve(scope.size());
    for (const auto variable : scope) {
      const auto found = assignment.find(variable);
      check(found != assignment.end(), "visible factor variable is absent from answer head");
      projected.push_back(found->second);
    }
    result.insert(std::move(projected));
  }
  return result;
}

std::string show(const Row& row) {
  std::string result = "[";
  for (std::size_t i = 0; i < row.size(); ++i) {
    if (i != 0) result += ",";
    result += std::visit([](const auto& value) -> std::string {
      using T = std::decay_t<decltype(value)>;
      if constexpr (std::is_same_v<T, std::string>) return "\"" + value + "\"";
      else if constexpr (std::is_same_v<T, bool>) return value ? "true" : "false";
      else if constexpr (std::is_same_v<T, Date>) return value.to_string();
      else if constexpr (std::is_same_v<T, Decimal>) return value.to_string();
      else return std::to_string(value);
    }, row[i]);
  }
  return result + "]";
}

struct CheckedTransition {
  Transition transition;
  Relation before_answer;
  Relation after_answer;
  Relation expected_delta;
};

CheckedTransition check_step(const Fixture& before_fixture,
                             const Fixture& after_fixture,
                             SetOperation operation,
                             const std::string& label) {
  check(before_fixture.catalog.tables.size() == after_fixture.catalog.tables.size() &&
            before_fixture.query.atoms.size() == after_fixture.query.atoms.size() &&
            before_fixture.tree.nodes.size() == after_fixture.tree.nodes.size(),
        label + ": fixture structure changed across one occurrence step");
  const auto before_snapshot = snapshot(before_fixture);
  const auto after_snapshot = snapshot(after_fixture);
  const auto before_answer = reference::evaluate(before_fixture.catalog,
                                                 before_fixture.query,
                                                 before_fixture.database);
  const auto after_answer = reference::evaluate(after_fixture.catalog,
                                                after_fixture.query,
                                                after_fixture.database);

  const auto before_expanded = occurrence_expansion(before_fixture);
  const auto after_expanded = occurrence_expansion(after_fixture);
  check(reference::evaluate(before_expanded.first.first,
                            before_expanded.first.second,
                            before_expanded.second) == before_answer,
        label + ": alias-prefix A04 differs from same-base-table A04 before step");
  check(reference::evaluate(after_expanded.first.first,
                            after_expanded.first.second,
                            after_expanded.second) == after_answer,
        label + ": alias-prefix A04 differs from same-base-table A04 after step");

  const auto before_enumerated = enumerate(before_snapshot);
  const auto after_enumerated = enumerate(after_snapshot);
  check(as_set(before_enumerated) == before_answer &&
            before_enumerated.size() == before_answer.size(),
        label + ": model enumeration differs from whole-query A04 before step");
  check(as_set(after_enumerated) == after_answer &&
            after_enumerated.size() == after_answer.size(),
        label + ": model enumeration differs from whole-query A04 after step");

  const auto before_live = bootstrap_live(before_snapshot);
  const auto after_live = bootstrap_live(after_snapshot);
  check(before_live.size() == before_snapshot.factors.size() &&
            after_live.size() == after_snapshot.factors.size(),
        label + ": bootstrap returned a wrong live-factor count");
  for (std::size_t factor = 0; factor < before_snapshot.factors.size(); ++factor) {
    const auto expected_before = project_answer_to_scope(
        before_answer, before_snapshot, before_snapshot.factors[factor].scope);
    const auto expected_after = project_answer_to_scope(
        after_answer, after_snapshot, after_snapshot.factors[factor].scope);
    check(before_live[factor] == expected_before &&
              after_live[factor] == expected_after,
          label + ": bootstrap live factor differs from exact global-answer projection");
  }

  const auto expected = exact_delta(before_answer, after_answer, operation);
  auto transition = partition(before_snapshot, after_snapshot, operation);
  const auto actual = as_set(transition.rows);
  check(actual == expected,
        label + ": model delta differs from exact independent A04 set difference");
  check(transition.rows.size() == actual.size(),
        label + ": append-only transition output contains a duplicate tuple");
  if (expected.empty())
    check(before_live == after_live,
          label + ": an empty output delta changed exact global live memberships");

  const auto factor_count = std::max(before_snapshot.factors.size(),
                                     after_snapshot.factors.size());
  const auto factor_bound = static_cast<std::uint64_t>(factor_count) *
                            static_cast<std::uint64_t>(expected.size());
  check(transition.metrics.candidates <= factor_bound,
        label + ": candidate count exceeds factor-count times exact output delta");
  check(transition.metrics.live_witnesses <= factor_bound,
        label + ": live-witness count exceeds factor-count times exact output delta");
  check(transition.metrics.live_witnesses <= transition.metrics.changed_keys,
        label + ": live witness count exceeds changed E-key count");
  check(transition.metrics.accepted == transition.rows.size() &&
            transition.metrics.accepted + transition.metrics.rejected ==
                transition.metrics.candidates,
        label + ": fragment candidate accounting is inconsistent");
  return {std::move(transition), before_answer, after_answer, expected};
}

Fixture one_table_fixture(std::string name, std::vector<Column> columns,
                          Query query, FreeConnexTree tree,
                          Relation rows) {
  Catalog catalog{1, {{std::move(name), std::move(columns)}}};
  return {std::move(catalog), std::move(query), std::move(tree),
          Database{{std::move(rows)}}};
}

void hidden_projection_and_physical_counts() {
  const Query query{{{"x", ScalarType::int64}, {"z", ScalarType::int64}},
                    {{"r", TableId{0}, {VariableId{0}, VariableId{1},
                                        IgnoredColumn{}}}},
                    {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}}}, {}, {}};
  const auto before = one_table_fixture(
      "r", {{"x", ScalarType::int64}, {"z", ScalarType::int64},
            {"payload", ScalarType::int64}}, query, tree,
      Relation{{n(1), n(10), n(100)}});
  auto after_db = before.database;
  after_db.tables[0].insert({n(1), n(10), n(101)});
  const auto after = Fixture{before.catalog, before.query, before.tree,
                             std::move(after_db)};
  const auto step = check_step(before, after, SetOperation::insert,
                               "physical projection-count-only");
  check(step.before_answer == step.after_answer &&
            step.transition.metrics.changed_keys == 0 &&
            step.transition.rows.empty(),
        "ignored payload insertion must not change an occurrence E factor");

  const Query projected{{{"x", ScalarType::int64}, {"z", ScalarType::int64}},
                        {{"r", TableId{0}, {VariableId{0}, VariableId{1}}}},
                        {{VariableId{0}, "x"}}, false};
  const FreeConnexTree projected_tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}}}, {}, {}};
  const auto hidden_before = one_table_fixture(
      "r", {{"x", ScalarType::int64}, {"z", ScalarType::int64}},
      projected, projected_tree, Relation{{n(1), n(10)}});
  auto hidden_after_db = hidden_before.database;
  hidden_after_db.tables[0].insert({n(1), n(11)});
  const auto hidden_after = Fixture{hidden_before.catalog, hidden_before.query,
                                    hidden_before.tree,
                                    std::move(hidden_after_db)};
  const auto collision = check_step(hidden_before, hidden_after,
                                    SetOperation::insert,
                                    "hidden projected E collision");
  check(collision.before_answer == collision.after_answer &&
            collision.transition.metrics.changed_keys == 0 &&
            collision.transition.rows.empty(),
        "adding a hidden z for a live x must leave projected E and Q(x) unchanged");
  const auto reverse = check_step(hidden_after, hidden_before,
                                  SetOperation::erase,
                                  "hidden projected E collision erase");
  check(reverse.transition.rows.empty(),
        "deleting a hidden z while another z survives must emit no answer");
  const Fixture no_hidden_rows{hidden_before.catalog, hidden_before.query,
      hidden_before.tree, Database{{Relation{}}}};
  const auto last = check_step(hidden_before, no_hidden_rows,
      SetOperation::erase, "last hidden projection witness erase");
  check(last.expected_delta == Relation{{n(1)}} &&
            last.transition.rows == std::vector<Row>{{n(1)}},
        "erasing the last hidden witness must remove its visible x once");
}

void root_and_ancestor_partitions() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}}},
       {"s", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}}},
       {"s", TableId{1}, {VariableId{0}, VariableId{1}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "y"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}}, {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 1, {}}}, {}, {}};
  const Fixture before{catalog, query, tree,
                       Database{{Relation{Row{n(1)}}, Relation{{n(1), n(10)}}}}};
  auto after_db = before.database;
  after_db.tables[1].clear();
  const Fixture after{catalog, query, tree, std::move(after_db)};
  const auto removed = check_step(before, after, SetOperation::erase,
                                  "ancestor and child E delete through S");
  check(removed.expected_delta == Relation{{n(1), n(10)}} &&
            removed.transition.rows == std::vector<Row>{{n(1), n(10)}} &&
            removed.transition.metrics.changed_keys == 2 &&
            removed.transition.fragments.size() == 2 &&
            removed.transition.fragments[0].factor == 0 &&
            removed.transition.fragments[0].accepted ==
                std::vector<Row>{{n(1), n(10)}} &&
            removed.transition.fragments[1].factor == 1 &&
            removed.transition.fragments[1].rejected ==
                std::vector<Row>{{n(1), n(10)}},
        "ancestor and child E changes must emit once, owned by root factor 0");
  const auto& owner = removed.transition.fragments.front();
  std::cout << "trace ancestor-child-delete owner_factor=" << owner.factor
            << " key=" << show(owner.witness)
            << " output=" << show(owner.accepted.front()) << '\n';

  const Catalog full_catalog{1,
      {{"r", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}}}};
  const Query full_query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}, VariableId{1}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "y"}}, false};
  const FreeConnexTree full_tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}}}, {}, {}};
  const Fixture full_before{full_catalog, full_query, full_tree,
      Database{{Relation{{n(1), n(2)}, {n(3), n(4)}}}}};
  auto full_db = full_before.database;
  full_db.tables[0].insert({n(5), n(6)});
  const Fixture full_after{full_catalog, full_query, full_tree,
                           std::move(full_db)};
  const auto full_root = check_step(full_before, full_after,
      SetOperation::insert, "one-atom root empty-separator witness");
  check(full_root.expected_delta == Relation{{n(5), n(6)}} &&
            full_root.transition.rows == std::vector<Row>{{n(5), n(6)}} &&
            full_root.transition.changed[0] == Relation{{n(5), n(6)}} &&
            full_root.transition.fragments.size() == 1 &&
            full_root.transition.fragments[0].witness == Row{n(5), n(6)},
        "full root witness binds the complete new key despite its empty parent separator");

  // The child has an empty separator to the root. Its first key can become
  // live only after a complete root witness exists; the root query answer
  // projects x and therefore emits each x exactly once.
  const Catalog disconnected_catalog{1,
      {{"r", {{"x", ScalarType::int64}}},
       {"s", {{"y", ScalarType::int64}}}}};
  const Query disconnected{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}}},
       {"s", TableId{1}, {VariableId{1}}}},
      {{VariableId{0}, "x"}}, false};
  const FreeConnexTree disconnected_tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}}, {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, {VariableId{1}}, {}, 1, {}}}, {}, {}};
  const Fixture disconnected_before{disconnected_catalog, disconnected,
      disconnected_tree, Database{{Relation{Row{n(1)}, Row{n(2)}}, Relation{}}}};
  auto activated_db = disconnected_before.database;
  activated_db.tables[1].insert({n(9)});
  const Fixture activated{disconnected_catalog, disconnected,
      disconnected_tree, std::move(activated_db)};
  const auto activation = check_step(disconnected_before, activated,
                                     SetOperation::insert,
                                     "empty-separator root witness activation");
  check(activation.expected_delta == Relation{{n(1)}, {n(2)}} &&
            activation.transition.rows.size() == 2 &&
            activation.transition.metrics.live_witnesses > 0,
        "an empty-separator child key must enumerate every full root witness");
}

void deep_and_dead_witnesses() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}},
       {"s", {{"y", ScalarType::int64}, {"z", ScalarType::int64}}},
       {"t", {{"z", ScalarType::int64}, {"w", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64},
                     {"z", ScalarType::int64}, {"w", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"s", TableId{1}, {VariableId{1}, VariableId{2}}},
       {"t", TableId{2}, {VariableId{2}, VariableId{3}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "y"},
       {VariableId{2}, "z"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, {VariableId{1}, VariableId{2}}, {NodeId{2}}, 1, {}},
       {"t", NodeKind::native, {VariableId{2}, VariableId{3}}, {}, 2, {}}}, {}, {}};
  const Fixture before{catalog, query, tree,
      Database{{Relation{{n(1), n(1)}}, Relation{{n(1), n(10)}},
                Relation{{n(10), n(100)}, {n(20), n(100)}}}}};
  auto after_db = before.database;
  after_db.tables[1].insert({n(1), n(20)});
  const Fixture after{catalog, query, tree, std::move(after_db)};
  const auto deep = check_step(before, after, SetOperation::insert,
                               "specification U05 propagation below unchanged root");
  const auto old_snapshot = snapshot(before);
  const auto new_snapshot = snapshot(after);
  const auto old_live = bootstrap_live(old_snapshot);
  const auto new_live = bootstrap_live(new_snapshot);
  check(old_snapshot.factors.front().rows == new_snapshot.factors.front().rows &&
            old_snapshot.factors[1].rows != new_snapshot.factors[1].rows &&
            old_snapshot.factors.back().rows == new_snapshot.factors.back().rows &&
            old_live.back() != new_live.back() &&
            deep.expected_delta == Relation{{n(1), n(1), n(20)}} &&
            deep.transition.rows == std::vector<Row>{{n(1), n(1), n(20)}} &&
            deep.transition.fragments.size() == 1 &&
            deep.transition.fragments[0].factor == 1,
        "U05 S key must emit while root E stays fixed and T liveness gains z=20");

  const Query joined{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}}},
       {"s", TableId{1}, {VariableId{0}, VariableId{1}}}},
      {{VariableId{0}, "x"}}, false};
  const FreeConnexTree joined_tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}}, {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 1, {}}}, {}, {}};
  const Fixture dead_before{Catalog{1,
      {{"r", {{"x", ScalarType::int64}}},
       {"s", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}}}},
      joined, joined_tree,
      Database{{Relation{}, Relation{}}}};
  auto dead_db = dead_before.database;
  dead_db.tables[1].insert({n(3), n(11)});
  const Fixture dead_after{dead_before.catalog, dead_before.query,
                           dead_before.tree, std::move(dead_db)};
  const auto dead = check_step(dead_before, dead_after, SetOperation::insert,
                               "unlive child E witness");
  check(dead.transition.metrics.dead_witnesses > 0 &&
            dead.transition.metrics.candidates == 0 &&
            dead.transition.rows.empty(),
        "E changes with no globally live parent completion must be counted dead");
}

void root_activation_boolean_and_constants() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}}},
       {"s", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}}},
       {"s", TableId{1}, {VariableId{0}, VariableId{1}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "y"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}}, {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 1, {}}}, {}, {}};
  const Fixture before{catalog, query, tree,
                       Database{{Relation{}, Relation{{n(3), n(30)}}}}};
  auto db = before.database;
  db.tables[0].insert({n(3)});
  const Fixture after{catalog, query, tree, std::move(db)};
  const auto activation = check_step(before, after, SetOperation::insert,
                                     "root liveness activates existing child E");
  check(activation.expected_delta == Relation{{n(3), n(30)}} &&
            activation.transition.rows == std::vector<Row>{{n(3), n(30)}} &&
            activation.transition.fragments.front().factor == 0,
        "root activation must enumerate an already-existing child factor");

  const Catalog bool_catalog{1, {{"flags", {{"tag", ScalarType::boolean}}}}};
  const Query boolean{{}, {{"flags", TableId{0}, {IgnoredColumn{}}}}, {}, false};
  const FreeConnexTree bool_tree{NodeId{0},
      {{"flags", NodeKind::native, {}, {}, 0, {}}}, {}, {}};
  const Fixture empty_bool{bool_catalog, boolean, bool_tree,
                           Database{{Relation{}}}};
  auto bool_db = empty_bool.database;
  bool_db.tables[0].insert({b(true)});
  const Fixture true_bool{bool_catalog, boolean, bool_tree, std::move(bool_db)};
  const auto made_true = check_step(empty_bool, true_bool, SetOperation::insert,
                                    "Boolean nullary activation");
  check(made_true.expected_delta == Relation{Row{}} &&
            made_true.transition.rows == std::vector<Row>{Row{}} &&
            enumerate(snapshot(true_bool)) == std::vector<Row>{Row{}},
        "a Boolean answer is represented by one empty tuple");

  auto false_bool_db = true_bool.database;
  false_bool_db.tables[0].clear();
  const Fixture false_bool{bool_catalog, boolean, bool_tree,
                           std::move(false_bool_db)};
  const auto made_false = check_step(true_bool, false_bool, SetOperation::erase,
                                     "Boolean nullary deactivation");
  check(made_false.expected_delta == Relation{Row{}} &&
            made_false.transition.rows == std::vector<Row>{Row{}},
        "deleting the last Boolean witness must emit one empty tuple");

  const Catalog constant_catalog{1, {{"r", {{"x", ScalarType::int64}}}}};
  const Query constant{{}, {{"r", TableId{0}, {n(7)}}}, {}, false};
  const FreeConnexTree constant_tree{NodeId{0},
      {{"r", NodeKind::native, {}, {}, 0, {}}}, {}, {}};
  const Fixture no_match{constant_catalog, constant, constant_tree,
                         Database{{Relation{Row{n(8)}}}}};
  auto constant_db = no_match.database;
  constant_db.tables[0].insert({n(7)});
  const Fixture match{constant_catalog, constant, constant_tree,
                      std::move(constant_db)};
  const auto constant_activation = check_step(no_match, match,
      SetOperation::insert, "constant-filtered native activation");
  check(constant_activation.expected_delta == Relation{Row{}} &&
            constant_activation.transition.rows == std::vector<Row>{Row{}},
        "a literal-filtered native row can activate a nullary answer");

  auto filtered_db = no_match.database;
  filtered_db.tables[0].insert({n(9)});
  const Fixture still_filtered{constant_catalog, constant, constant_tree,
                               std::move(filtered_db)};
  const auto filtered = check_step(no_match, still_filtered,
      SetOperation::insert, "constant-filtered physical-only stage");
  check(filtered.expected_delta.empty() &&
            filtered.transition.metrics.changed_keys == 0 &&
            filtered.transition.rows.empty(),
        "a physical row filtered by a query constant must not change native E");

  const Query true_constant{{}, {}, {}, false};
  const FreeConnexTree empty_tree{};
  const Fixture constant_true{Catalog{}, true_constant, empty_tree, Database{}};
  const auto true_snapshot = snapshot(constant_true);
  check(true_snapshot.constant_answer &&
            enumerate(true_snapshot) == std::vector<Row>{Row{}} &&
            bootstrap_live(true_snapshot).empty(),
        "empty-body constant route has a true nullary answer and no factors");
  const Fixture constant_false{Catalog{}, Query{{}, {}, {}, true}, empty_tree, Database{}};
  const auto false_snapshot = snapshot(constant_false);
  check(!false_snapshot.constant_answer && enumerate(false_snapshot).empty() &&
            bootstrap_live(false_snapshot).empty(),
        "contradictory constant route has no answer or live factors");
  for (const auto operation : {SetOperation::insert, SetOperation::erase}) {
    check(partition(true_snapshot, true_snapshot, operation).rows.empty() &&
              partition(false_snapshot, false_snapshot, operation).rows.empty(),
          "unchanged constant routes must have no signed delta");
  }
}

void alias_predicate_count_only_routes() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}, {"status", ScalarType::int64},
               {"payload", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}},
      {{"status_one", TableId{0},
        {VariableId{0}, n(1), IgnoredColumn{}}},
       {"status_two", TableId{0},
        {VariableId{0}, n(2), IgnoredColumn{}}}},
      {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"g", NodeKind::generalized, {VariableId{0}},
         {NodeId{1}, NodeId{2}}, {}, {}},
       {"status_one", NodeKind::native, {VariableId{0}}, {}, 0, {}},
       {"status_two", NodeKind::native, {VariableId{0}}, {}, 1, {}}}, {}, {}};
  const Row status_one_a{n(4), n(1), n(10)};
  const Row status_one_b{n(4), n(1), n(11)};
  const Row status_two{n(4), n(2), n(20)};
  const Fixture physical0{catalog, query, tree,
      Database{{Relation{status_one_a, status_one_b}}}};
  const auto expanded0 = occurrence_expansion(physical0);
  Fixture prefix0{expanded0.first.first, expanded0.first.second, tree,
                  expanded0.second};
  check(reference::evaluate(prefix0.catalog, prefix0.query,
                            prefix0.database) ==
            reference::evaluate(physical0.catalog, physical0.query,
                                physical0.database),
        "alias-local guard expansion differs from initial same-table A04");

  const auto check_physical_event = [&](const Fixture& physical_before,
                                        const Fixture& physical_after,
                                        const Fixture& alias_after,
                                        SetOperation operation,
                                        const CheckedTransition& stage_a,
                                        const CheckedTransition& stage_b,
                                        std::size_t expected_a,
                                        std::size_t expected_b,
                                        const std::string& label) {
    check(stage_a.expected_delta.size() == expected_a &&
              stage_b.expected_delta.size() == expected_b,
          label + ": wrong per-alias output counts");
    std::vector<Row> staged = stage_a.transition.rows;
    staged.insert(staged.end(), stage_b.transition.rows.begin(),
                  stage_b.transition.rows.end());
    const auto before_answer = reference::evaluate(
        physical_before.catalog, physical_before.query,
        physical_before.database);
    const auto after_answer = reference::evaluate(
        physical_after.catalog, physical_after.query,
        physical_after.database);
    const auto expected = exact_delta(before_answer, after_answer, operation);
    check(reference::evaluate(alias_after.catalog, alias_after.query,
                              alias_after.database) == after_answer,
          label + ": staged alias endpoint differs from same-base-table A04");
    const auto expanded_endpoint = occurrence_expansion(physical_after);
    check(reference::evaluate(expanded_endpoint.first.first,
                              expanded_endpoint.first.second,
                              expanded_endpoint.second) == after_answer,
          label + ": expanded alias endpoint differs from same-base-table A04");
    check(staged.size() == expected.size() && as_set(staged) == expected &&
              staged.size() == as_set(staged).size(),
          label + ": ordered alias-stage outputs do not match physical A04 delta exactly");
  };

  // Insert status 2: alias A is filtered; alias B creates the first answer.
  auto physical1_db = physical0.database;
  physical1_db.tables[0].insert(status_two);
  const Fixture physical1{catalog, query, tree, std::move(physical1_db)};
  auto prefix1_db = prefix0.database;
  prefix1_db.tables[0].insert(status_two);
  const Fixture prefix1{prefix0.catalog, prefix0.query, prefix0.tree,
                        std::move(prefix1_db)};
  const auto insert_a = check_step(prefix0, prefix1, SetOperation::insert,
                                   "predicate alias insert route A");
  auto prefix2_db = prefix1.database;
  prefix2_db.tables[1].insert(status_two);
  const Fixture prefix2{prefix1.catalog, prefix1.query, prefix1.tree,
                        std::move(prefix2_db)};
  const auto insert_b = check_step(prefix1, prefix2, SetOperation::insert,
                                   "predicate alias insert route B");
  check(insert_a.transition.rows.empty() &&
            insert_b.transition.rows == std::vector<Row>{{n(4)}},
        "different alias constants must route the inserted row only to alias B");
  check_physical_event(physical0, physical1, prefix2, SetOperation::insert,
                       insert_a, insert_b, 0, 1,
                       "predicate alias insert epoch");

  // Delete one of two status-1 derivations. The physical row count falls,
  // but alias A's projected x support remains positive and alias B filters it.
  auto physical2_db = physical1.database;
  physical2_db.tables[0].erase(status_one_a);
  const Fixture physical2{catalog, query, tree, std::move(physical2_db)};
  auto prefix3_db = prefix2.database;
  prefix3_db.tables[0].erase(status_one_a);
  const Fixture prefix3{prefix2.catalog, prefix2.query, prefix2.tree,
                        std::move(prefix3_db)};
  const auto delete_one_a = check_step(prefix2, prefix3, SetOperation::erase,
                                       "predicate alias count-only delete A");
  auto prefix4_db = prefix3.database;
  prefix4_db.tables[1].erase(status_one_a);
  const Fixture prefix4{prefix3.catalog, prefix3.query, prefix3.tree,
                        std::move(prefix4_db)};
  const auto delete_one_b = check_step(prefix3, prefix4, SetOperation::erase,
                                       "predicate alias filtered delete B");
  check(delete_one_a.transition.metrics.changed_keys == 0 &&
            delete_one_b.transition.metrics.changed_keys == 0 &&
            delete_one_a.transition.rows.empty() &&
            delete_one_b.transition.rows.empty(),
        "positive-to-positive alias support and the other alias filter create no E changes");
  check_physical_event(physical1, physical2, prefix4, SetOperation::erase,
                       delete_one_a, delete_one_b, 0, 0,
                       "predicate alias count-only deletion epoch");

  // Delete the last status-1 derivation. Alias A loses x=4; alias B still
  // filters this physical row, so the single projected result disappears
  // during route A and is not repeated during route B.
  auto physical3_db = physical2.database;
  physical3_db.tables[0].erase(status_one_b);
  const Fixture physical3{catalog, query, tree, std::move(physical3_db)};
  auto prefix5_db = prefix4.database;
  prefix5_db.tables[0].erase(status_one_b);
  const Fixture prefix5{prefix4.catalog, prefix4.query, prefix4.tree,
                        std::move(prefix5_db)};
  const auto delete_last_a = check_step(prefix4, prefix5, SetOperation::erase,
                                        "predicate alias last-support delete A");
  auto prefix6_db = prefix5.database;
  prefix6_db.tables[1].erase(status_one_b);
  const Fixture prefix6{prefix5.catalog, prefix5.query, prefix5.tree,
                        std::move(prefix6_db)};
  const auto delete_last_b = check_step(prefix5, prefix6, SetOperation::erase,
                                        "predicate alias filtered last delete B");
  check(delete_last_a.transition.rows == std::vector<Row>{{n(4)}} &&
            delete_last_b.transition.rows.empty(),
        "the last alias A support emits one deletion before filtered route B");
  check_physical_event(physical2, physical3, prefix6, SetOperation::erase,
                       delete_last_a, delete_last_b, 1, 0,
                       "predicate alias last-support deletion epoch");
}

void products_aliases_and_heads() {
  for (const auto arity : {std::size_t{3}, std::size_t{8}}) {
    Catalog catalog;
    Query query;
    query.variables.push_back({"x", ScalarType::int64});
    std::vector<NodeId> children;
    Database database;
    for (std::size_t i = 0; i < arity; ++i) {
      const auto variable = i + 1;
      query.variables.push_back({"v" + std::to_string(i), ScalarType::int64});
      query.atoms.push_back({"r" + std::to_string(i), TableId{i},
                             {VariableId{0}, VariableId{variable}}});
      query.head.push_back({VariableId{0}, "x"});
      query.head.push_back({VariableId{variable}, "v" + std::to_string(i)});
      catalog.tables.push_back({"r" + std::to_string(i),
          {{"x", ScalarType::int64}, {"v", ScalarType::int64}}});
      database.tables.push_back(Relation{{n(0), n(0)}, {n(0), n(1)}});
      children.push_back(NodeId{i + 1});
    }
    FreeConnexTree tree;
    tree.root = NodeId{0};
    tree.nodes.push_back({"product", NodeKind::generalized,
                          variable_set({0}), children, {}, {}});
    for (std::size_t i = 0; i < arity; ++i)
      tree.nodes.push_back({"r" + std::to_string(i), NodeKind::native,
          variable_set({0, i + 1}), {}, i, {}});
    const Fixture before{catalog, query, tree, database};
    auto after_db = database;
    after_db.tables[arity - 1].insert({n(0), n(2)});
    const Fixture after{catalog, query, tree, std::move(after_db)};
    const auto step = check_step(before, after, SetOperation::insert,
        "generalized " + std::to_string(arity) + "-child product");
    const auto expected_size = (std::size_t{1} << (arity - 1));
    check(step.expected_delta.size() == expected_size &&
              step.transition.rows.size() == expected_size,
          "product delta must enumerate every sibling combination exactly once");
  }

  // Two aliases of one base table have the same scope and change together.
  const Catalog same_catalog{1,
      {{"r", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}}}};
  const Query same_query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"left", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"right", TableId{0}, {VariableId{0}, VariableId{1}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "y"}}, false};
  const FreeConnexTree same_tree{NodeId{0},
      {{"g", NodeKind::generalized, {VariableId{0}, VariableId{1}},
         {NodeId{1}, NodeId{2}}, {}, {}},
       {"left", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}},
       {"right", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 1, {}}}, {}, {}};
  const Fixture same_before{same_catalog, same_query, same_tree,
                            Database{{Relation{{n(1), n(10)}}}}};
  auto same_db = same_before.database;
  same_db.tables[0].insert({n(2), n(20)});
  const Fixture same_after{same_catalog, same_query, same_tree,
                           std::move(same_db)};
  const auto same = check_step(same_before, same_after, SetOperation::insert,
                               "same-scope aliases on one physical table");
  check(same.expected_delta == Relation{{n(2), n(20)}} &&
            same.transition.rows.size() == 1,
        "two same-scope aliases must not duplicate a projected output");

  const Catalog same_prefix_catalog{1,
      {{"left", { {"x", ScalarType::int64}, {"y", ScalarType::int64} }},
       {"right", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}}}};
  Query same_prefix_query = same_query;
  same_prefix_query.atoms[0].table = TableId{0};
  same_prefix_query.atoms[1].table = TableId{1};
  const Fixture same_prefix0{same_prefix_catalog, same_prefix_query, same_tree,
      Database{{Relation{{n(1), n(10)}}, Relation{{n(1), n(10)}}}}};
  auto same_prefix1_db = same_prefix0.database;
  same_prefix1_db.tables[0].insert({n(2), n(20)});
  const Fixture same_prefix1{same_prefix_catalog, same_prefix_query, same_tree,
                             std::move(same_prefix1_db)};
  const auto same_route1 = check_step(same_prefix0, same_prefix1,
      SetOperation::insert, "same-scope alias insert route 1");
  check(same_route1.expected_delta.empty() &&
            same_route1.transition.metrics.dead_witnesses > 0,
        "the first same-scope alias key is not live before its matching route");
  auto same_prefix2_db = same_prefix1.database;
  same_prefix2_db.tables[1].insert({n(2), n(20)});
  const Fixture same_prefix2{same_prefix_catalog, same_prefix_query, same_tree,
                             std::move(same_prefix2_db)};
  const auto same_route2 = check_step(same_prefix1, same_prefix2,
      SetOperation::insert, "same-scope alias insert route 2");
  check(same_route2.expected_delta == Relation{{n(2), n(20)}} &&
            same_route2.transition.rows.size() == 1,
        "the second same-scope alias route completes the new output once");
  auto same_delete1_db = same_prefix2.database;
  same_delete1_db.tables[0].erase({n(2), n(20)});
  const Fixture same_delete1{same_prefix_catalog, same_prefix_query, same_tree,
                             std::move(same_delete1_db)};
  const auto same_erase1 = check_step(same_prefix2, same_delete1,
      SetOperation::erase, "same-scope alias erase route 1");
  check(same_erase1.expected_delta == Relation{{n(2), n(20)}},
        "first same-scope alias erasure removes the matching output");
  auto same_delete2_db = same_delete1.database;
  same_delete2_db.tables[1].erase({n(2), n(20)});
  const Fixture same_delete2{same_prefix_catalog, same_prefix_query, same_tree,
                             std::move(same_delete2_db)};
  const auto same_erase2 = check_step(same_delete1, same_delete2,
      SetOperation::erase, "same-scope alias erase route 2");
  check(same_erase2.expected_delta.empty(),
        "second same-scope alias erasure must not repeat the removed output");
  const auto same_prefix_answers = reference::evaluate(
      same_prefix_catalog, same_prefix_query, same_prefix0.database);
  const auto same_final_prefix_answers = reference::evaluate(
      same_prefix_catalog, same_prefix_query, same_prefix2.database);
  check(same_prefix_answers == reference::evaluate(
            same_catalog, same_query, same_before.database) &&
            same_final_prefix_answers == reference::evaluate(
            same_catalog, same_query, same_after.database),
        "same-scope alias prefix endpoints match the same-base-table CQ");

  // Expand E(x,z), E(z,y) into occurrence-local tables so the one physical
  // loop insertion drains as two prefixes. This exposes the new-new alias
  // combination and gives deletion the same route order.
  const std::vector<Column> edge_columns{{"src", ScalarType::int64},
                                         {"dst", ScalarType::int64}};
  const Catalog prefix_catalog{1,
      {{"edge_left", edge_columns}, {"edge_right", edge_columns}}};
  const Query prefix_query{{{"x", ScalarType::int64}, {"z", ScalarType::int64},
                            {"y", ScalarType::int64}},
      {{"left", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"right", TableId{1}, {VariableId{1}, VariableId{2}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "z"},
       {VariableId{2}, "y"}}, false};
  const FreeConnexTree prefix_tree{NodeId{0},
      {{"g", NodeKind::generalized, {VariableId{1}},
         {NodeId{1}, NodeId{2}}, {}, {}},
       {"left", NodeKind::native,
        {VariableId{0}, VariableId{1}}, {}, 0, {}},
       {"right", NodeKind::native,
        {VariableId{1}, VariableId{2}}, {}, 1, {}}}, {}, {}};
  const Relation old_edges{{n(1), n(2)}, {n(2), n(1)}};
  const Row loop_edge{n(1), n(1)};
  const Fixture prefix0{prefix_catalog, prefix_query, prefix_tree,
                        Database{{old_edges, old_edges}}};
  auto route1_db = prefix0.database;
  route1_db.tables[0].insert(loop_edge);
  const Fixture prefix1{prefix_catalog, prefix_query, prefix_tree,
                        std::move(route1_db)};
  const auto route1 = check_step(prefix0, prefix1, SetOperation::insert,
                                 "self-join insert route 1");
  check(route1.expected_delta == Relation{{n(1), n(1), n(2)}} &&
            route1.transition.rows == std::vector<Row>{{n(1), n(1), n(2)}},
        "first alias route emits the old-second-alias completion");

  auto route2_db = prefix1.database;
  route2_db.tables[1].insert(loop_edge);
  const Fixture prefix2{prefix_catalog, prefix_query, prefix_tree,
                        std::move(route2_db)};
  const auto route2 = check_step(prefix1, prefix2, SetOperation::insert,
                                 "self-join insert route 2");
  check(route2.expected_delta ==
            Relation{{n(1), n(1), n(1)}, {n(2), n(1), n(1)}} &&
            route2.transition.rows.size() == 2,
        "second alias route emits the two completions enabled by its new edge");

  const Catalog physical_catalog{1, {{"edge", edge_columns}}};
  const Query physical_query{{{"x", ScalarType::int64}, {"z", ScalarType::int64},
                              {"y", ScalarType::int64}},
      {{"left", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"right", TableId{0}, {VariableId{1}, VariableId{2}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "z"},
       {VariableId{2}, "y"}}, false};
  const Fixture physical_before{physical_catalog, physical_query, prefix_tree,
                                Database{{old_edges}}};
  auto physical_db = physical_before.database;
  physical_db.tables[0].insert(loop_edge);
  const Fixture physical_after{physical_catalog, physical_query, prefix_tree,
                               std::move(physical_db)};
  const auto physical_before_answer = reference::evaluate(
      physical_catalog, physical_query, physical_before.database);
  const auto physical_after_answer = reference::evaluate(
      physical_catalog, physical_query, physical_after.database);
  check(physical_before_answer == reference::evaluate(
            prefix_catalog, prefix_query, prefix0.database) &&
            physical_after_answer == reference::evaluate(
            prefix_catalog, prefix_query, prefix2.database),
        "alias-prefix endpoints must match the original same-base-table CQ");
  std::vector<Row> staged_insertions = route1.transition.rows;
  staged_insertions.insert(staged_insertions.end(), route2.transition.rows.begin(),
                           route2.transition.rows.end());
  const auto physical_insert_delta = exact_delta(
      physical_before_answer, physical_after_answer, SetOperation::insert);
  check(staged_insertions.size() == physical_insert_delta.size() &&
            as_set(staged_insertions) == physical_insert_delta &&
            staged_insertions.size() == as_set(staged_insertions).size(),
        "ordered alias route insertions must telescope exactly without duplicates");

  auto delete_route1_db = prefix2.database;
  delete_route1_db.tables[0].erase(loop_edge);
  const Fixture delete1{prefix_catalog, prefix_query, prefix_tree,
                        std::move(delete_route1_db)};
  const auto erase1 = check_step(prefix2, delete1, SetOperation::erase,
                                 "self-join erase route 1");
  check(erase1.expected_delta ==
            Relation{{n(1), n(1), n(1)}, {n(1), n(1), n(2)}} &&
            erase1.transition.rows.size() == 2,
        "first erase route removes the two assignments using the first alias loop");

  auto delete_route2_db = delete1.database;
  delete_route2_db.tables[1].erase(loop_edge);
  const Fixture delete2{prefix_catalog, prefix_query, prefix_tree,
                        std::move(delete_route2_db)};
  const auto erase2 = check_step(delete1, delete2, SetOperation::erase,
                                 "self-join erase route 2");
  check(erase2.expected_delta == Relation{{n(2), n(1), n(1)}} &&
            erase2.transition.rows == std::vector<Row>{{n(2), n(1), n(1)}},
        "second erase route removes the last new-new completion");
  std::vector<Row> staged_erasures = erase1.transition.rows;
  staged_erasures.insert(staged_erasures.end(), erase2.transition.rows.begin(),
                         erase2.transition.rows.end());
  const auto physical_erase_delta = exact_delta(
      physical_after_answer, physical_before_answer, SetOperation::erase);
  check(staged_erasures.size() == physical_erase_delta.size() &&
            as_set(staged_erasures) == physical_erase_delta &&
            staged_erasures.size() == as_set(staged_erasures).size(),
        "ordered alias route erasures must telescope exactly without duplicates");

  const Query repeated{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}, VariableId{1}}}},
      {{VariableId{1}, "y"}, {VariableId{0}, "x"}, {VariableId{1}, "again"}}, false};
  const FreeConnexTree repeated_tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}}}, {}, {}};
  const auto repeated_before = one_table_fixture(
      "r", {{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      repeated, repeated_tree, Relation{});
  auto repeated_db = repeated_before.database;
  repeated_db.tables[0].insert({n(7), n(4)});
  const Fixture repeated_after{repeated_before.catalog, repeated_before.query,
      repeated_before.tree, std::move(repeated_db)};
  const auto repeated_step = check_step(repeated_before, repeated_after,
      SetOperation::insert, "reordered repeated head");
  check(repeated_step.transition.rows ==
            std::vector<Row>{{n(4), n(7), n(4)}} &&
            enumerate(snapshot(repeated_after)) ==
                std::vector<Row>{{n(4), n(7), n(4)}} &&
            bootstrap_live(snapshot(repeated_after)).size() == 1,
        "output order and repeated head fields must be preserved");
}

void exhaustive_tiny_domains() {
  std::uint64_t steps = 0;
  const std::vector<Row> hidden_domain{{n(0), n(0)}, {n(0), n(1)},
                                       {n(1), n(0)}, {n(1), n(1)}};
  const Query hidden_query{{{"x", ScalarType::int64}, {"z", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}, VariableId{1}}}},
      {{VariableId{0}, "x"}}, false};
  const FreeConnexTree hidden_tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}}}, {}, {}};
  for (unsigned mask = 0; mask < 16; ++mask) {
    Relation initial;
    for (std::size_t i = 0; i < hidden_domain.size(); ++i)
      if ((mask & (1U << i)) != 0U) initial.insert(hidden_domain[i]);
    const Fixture base = one_table_fixture("r",
        {{"x", ScalarType::int64}, {"z", ScalarType::int64}},
        hidden_query, hidden_tree, initial);
    for (std::size_t i = 0; i < hidden_domain.size(); ++i) {
      auto next = initial;
      const bool inserting = (mask & (1U << i)) == 0U;
      if (inserting) next.insert(hidden_domain[i]);
      else next.erase(hidden_domain[i]);
      const Fixture changed{base.catalog, base.query, base.tree,
                            Database{{std::move(next)}}};
      static_cast<void>(check_step(base, changed,
          inserting ? SetOperation::insert : SetOperation::erase,
          "exhaustive hidden-R mask=" + std::to_string(mask) +
              " tuple=" + std::to_string(i)));
      ++steps;
    }
  }

  const Catalog path_catalog{1,
      {{"r", {{"x", ScalarType::int64}}},
       {"s", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}}}};
  const Query path_query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}}},
       {"s", TableId{1}, {VariableId{0}, VariableId{1}}}},
      {{VariableId{0}, "x"}}, false};
  const FreeConnexTree path_tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}}, {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 1, {}}}, {}, {}};
  const std::vector<Row> r_domain{{n(0)}, {n(1)}};
  const std::vector<Row> s_domain{{n(0), n(0)}, {n(0), n(1)},
                                  {n(1), n(0)}, {n(1), n(1)}};
  for (unsigned rmask = 0; rmask < 4; ++rmask) {
    Relation rrows;
    for (std::size_t i = 0; i < r_domain.size(); ++i)
      if ((rmask & (1U << i)) != 0U) rrows.insert(r_domain[i]);
    for (unsigned smask = 0; smask < 16; ++smask) {
      Relation srows;
      for (std::size_t i = 0; i < s_domain.size(); ++i)
        if ((smask & (1U << i)) != 0U) srows.insert(s_domain[i]);
      const Fixture base{path_catalog, path_query, path_tree,
                         Database{{rrows, srows}}};
      for (std::size_t i = 0; i < r_domain.size() + s_domain.size(); ++i) {
        auto next = base.database;
        const bool is_r = i < r_domain.size();
        const auto local = is_r ? i : i - r_domain.size();
        auto& relation = next.tables[is_r ? 0 : 1];
        const auto& row = is_r ? r_domain[local] : s_domain[local];
        const bool inserting = !relation.contains(row);
        if (inserting) relation.insert(row);
        else relation.erase(row);
        const Fixture changed{path_catalog, path_query, path_tree,
                             std::move(next)};
        static_cast<void>(check_step(base, changed,
            inserting ? SetOperation::insert : SetOperation::erase,
            "exhaustive R-S mask=" + std::to_string(rmask) + ":" +
                std::to_string(smask) + " tuple=" + std::to_string(i)));
        ++steps;
      }
    }
  }

  // Projected R(x,z) -> S(z,y), head x. The z separator stays hidden, so
  // root E is the set of live x values and an S update cannot create output
  // unless it completes a previously missing root projection.
  const Catalog chain_catalog{1,
      {{"r", {{"x", ScalarType::int64}, {"z", ScalarType::int64}}},
       {"s", {{"z", ScalarType::int64}, {"y", ScalarType::int64}}}}};
  const Query chain_query{{{"x", ScalarType::int64}, {"z", ScalarType::int64},
                           {"y", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"s", TableId{1}, {VariableId{1}, VariableId{2}}}},
      {{VariableId{0}, "x"}}, false};
  const FreeConnexTree chain_tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, {VariableId{1}, VariableId{2}}, {}, 1, {}}}, {}, {}};
  const std::vector<Row> r_chain{{n(0), n(0)}, {n(0), n(1)},
                                 {n(1), n(0)}, {n(1), n(1)}};
  const std::vector<Row> s_chain{{n(0), n(0)}, {n(0), n(1)},
                                 {n(1), n(0)}, {n(1), n(1)}};
  for (unsigned rmask = 0; rmask < 16; ++rmask) {
    Relation rrows;
    for (std::size_t i = 0; i < r_chain.size(); ++i)
      if ((rmask & (1U << i)) != 0U) rrows.insert(r_chain[i]);
    for (unsigned smask = 0; smask < 16; ++smask) {
      Relation srows;
      for (std::size_t i = 0; i < s_chain.size(); ++i)
        if ((smask & (1U << i)) != 0U) srows.insert(s_chain[i]);
      const Fixture base{chain_catalog, chain_query, chain_tree,
                         Database{{rrows, srows}}};
      for (std::size_t i = 0; i < r_chain.size() + s_chain.size(); ++i) {
        auto next = base.database;
        const bool is_r = i < r_chain.size();
        const auto local = is_r ? i : i - r_chain.size();
        auto& relation = next.tables[is_r ? 0 : 1];
        const auto& row = is_r ? r_chain[local] : s_chain[local];
        const bool inserting = !relation.contains(row);
        if (inserting) relation.insert(row);
        else relation.erase(row);
        const Fixture changed{chain_catalog, chain_query, chain_tree,
                             std::move(next)};
        static_cast<void>(check_step(base, changed,
            inserting ? SetOperation::insert : SetOperation::erase,
            "exhaustive projected R-S mask=" + std::to_string(rmask) + ":" +
                std::to_string(smask) + " tuple=" + std::to_string(i)));
        ++steps;
      }
    }
  }

  // Boolean and disconnected constant-head routes are exhaustive over the
  // four subsets of a two-value unary relation.
  const Query bool_query{{{"x", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}}}}, {}, false};
  const FreeConnexTree bool_tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
  for (unsigned mask = 0; mask < 4; ++mask) {
    Relation rows;
    for (std::size_t i = 0; i < 2; ++i)
      if ((mask & (1U << i)) != 0U) rows.insert({n(static_cast<std::int64_t>(i))});
    const Fixture base = one_table_fixture("r", {{"x", ScalarType::int64}},
        bool_query, bool_tree, rows);
    for (std::size_t i = 0; i < 2; ++i) {
      auto changed_rows = rows;
      const Row row{n(static_cast<std::int64_t>(i))};
      const bool inserting = !changed_rows.contains(row);
      if (inserting) changed_rows.insert(row);
      else changed_rows.erase(row);
      const Fixture changed{base.catalog, base.query, base.tree,
                            Database{{std::move(changed_rows)}}};
      static_cast<void>(check_step(base, changed,
          inserting ? SetOperation::insert : SetOperation::erase,
          "exhaustive Boolean mask=" + std::to_string(mask)));
      ++steps;
    }
  }
  std::cout << "exhaustive_delta_steps=" << steps << '\n';
}

void simultaneous_projection_collision() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}, {"z", ScalarType::int64},
               {"h", ScalarType::int64}}},
       {"s", {{"z", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"z", ScalarType::int64},
                     {"h", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}, VariableId{1}, VariableId{2}}},
       {"s", TableId{1}, {VariableId{1}}}},
      {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native,
        {VariableId{0}, VariableId{1}, VariableId{2}}, {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, {VariableId{1}}, {}, 1, {}}}, {}, {}};
  const Fixture before{catalog, query, tree,
      Database{{Relation{{n(4), n(1), n(10)}, {n(4), n(1), n(11)}},
                Relation{}}}};
  auto inserted_db = before.database;
  inserted_db.tables[1].insert({n(1)});
  const Fixture after{catalog, query, tree, std::move(inserted_db)};
  const auto inserted = check_step(before, after, SetOperation::insert,
                                   "U06 simultaneous projection collision");
  check(inserted.expected_delta == Relation{{n(4)}} &&
            inserted.transition.rows == std::vector<Row>{{n(4)}} &&
            inserted.transition.metrics.changed_keys == 1,
        "one child key activating two hidden witnesses must add one projected x");
  const auto deleted = check_step(after, before, SetOperation::erase,
                                  "U06 simultaneous projection collision erase");
  check(deleted.expected_delta == Relation{{n(4)}} &&
            deleted.transition.rows == std::vector<Row>{{n(4)}} &&
            deleted.transition.metrics.changed_keys == 1,
        "deleting one child key must remove the projected x once");
}

void rejects_invalid_inputs() {
  const Catalog catalog{1, {{"r", {{"x", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}}}}, {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
  const Fixture empty{catalog, query, tree, Database{{Relation{}}}};
  auto inserted_db = empty.database;
  inserted_db.tables[0].insert({n(1)});
  const Fixture inserted{catalog, query, tree, std::move(inserted_db)};
  const auto before = snapshot(empty);
  const auto after = snapshot(inserted);
  const auto valid_insert = partition(before, after, SetOperation::insert);
  check(valid_insert.rows == std::vector<Row>{{n(1)}},
        "a same-sign inserted snapshot must be accepted");
  expect_error([&] { static_cast<void>(partition(before, after, SetOperation::erase)); },
               "invalid_delta_transition");
  expect_error([&] { static_cast<void>(partition(before, before,
      static_cast<SetOperation>(255))); }, "invalid_delta_transition");

  Snapshot mixed_before;
  mixed_before.head = {VariableId{0}, VariableId{1}};
  mixed_before.factors = {
      Factor{NodeId{0}, {}, {VariableId{0}}, Relation{{n(1)}}},
      Factor{NodeId{1}, std::size_t{0}, {VariableId{0}, VariableId{1}},
             Relation{{n(1), n(10)}}}};
  Snapshot mixed_after;
  mixed_after.head = mixed_before.head;
  mixed_after.factors = {
      Factor{NodeId{0}, {}, {VariableId{0}}, Relation{{n(2)}}},
      Factor{NodeId{1}, std::size_t{0}, {VariableId{0}, VariableId{1}},
             Relation{{n(2), n(20)}}}};
  expect_error([&] { static_cast<void>(partition(mixed_before, mixed_after,
      SetOperation::insert)); }, "invalid_delta_transition");
  expect_error([&] { static_cast<void>(partition(mixed_before, mixed_after,
      SetOperation::erase)); }, "invalid_delta_transition");

  auto incompatible = after;
  incompatible.head = {VariableId{0}, VariableId{0}};
  expect_error([&] { static_cast<void>(partition(before, incompatible,
      SetOperation::insert)); }, "invalid_delta_transition");

  auto bad_scope = before;
  bad_scope.factors[0].scope.push_back(VariableId{99});
  expect_error([&] { static_cast<void>(enumerate(bad_scope)); },
               "invalid_delta_model");
  auto bad_type = after;
  bad_type.factors[0].rows.insert({s("wrong")});
  expect_error([&] { static_cast<void>(bootstrap_live(bad_type)); },
               "invalid_delta_model");

  Snapshot invalid_totality;
  invalid_totality.head = {VariableId{0}, VariableId{1}};
  invalid_totality.factors = {
      Factor{NodeId{0}, {}, {VariableId{0}}, Relation{{n(1)}}},
      Factor{NodeId{1}, std::size_t{0}, {VariableId{0}, VariableId{1}},
             Relation{{n(2), n(20)}}}};
  expect_error([&] { static_cast<void>(bootstrap_live(invalid_totality)); },
               "invalid_delta_model");
  auto bad_input = native_inputs(empty);
  bad_input[0].insert({s("wrong")});
  expect_error([&] { static_cast<void>(recompute(catalog, query, tree, bad_input)); },
               "invalid_delta_model");
  expect_error([&] { static_cast<void>(recompute(catalog, query, tree, {})); },
               "invalid_delta_model");
}

}  // namespace

int main() {
  try {
    hidden_projection_and_physical_counts();
    root_and_ancestor_partitions();
    deep_and_dead_witnesses();
    root_activation_boolean_and_constants();
    alias_predicate_count_only_routes();
    products_aliases_and_heads();
    exhaustive_tiny_domains();
    simultaneous_projection_collision();
    rejects_invalid_inputs();
    std::cout << "delta specification checks passed\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
