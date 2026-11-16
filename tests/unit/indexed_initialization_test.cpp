#include "indexed_runtime_fixture.hpp"
#include "crown/api/error.hpp"
#include "crown/frontend/bind.hpp"
#include "crown/frontend/normalize.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/session.hpp"
#include "evaluator.hpp"
#include "native_input.hpp"

#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

namespace {
using namespace crown;
using namespace crown::runtime;
using Assignment = std::map<VariableId, Value>;
using Counts = std::map<Row, std::uint64_t>;
using SignedKey = std::pair<SetOperation, Row>;
using RowAdapter = std::function<std::optional<Assignment>(OccurrenceId, const Row&)>;

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

template <class Action>
void expect_code(Action&& action, std::string_view code) {
  try {
    std::forward<Action>(action)();
  } catch (const Error& failure) {
    check(failure.code() == code,
          "expected " + std::string(code) + ", got " + failure.code());
    return;
  }
  throw std::runtime_error("expected error " + std::string(code));
}

Value n(std::int64_t value) { return value; }
Value s(std::string value) { return value; }

Row project(const Assignment& assignment, const auto& variables) {
  Row result;
  result.reserve(variables.size());
  for (const auto variable : variables) result.push_back(assignment.at(variable));
  return result;
}

std::optional<Assignment> assign_terms(const auto& atom, const Row& row) {
  if (atom.terms.size() != row.size()) return {};
  Assignment result;
  for (std::size_t field = 0; field < atom.terms.size(); ++field) {
    if (const auto* variable = std::get_if<VariableId>(&atom.terms[field])) {
      const auto [found, inserted] = result.emplace(*variable, row[field]);
      if (!inserted && found->second != row[field]) return {};
    } else if (const auto* constant = std::get_if<1>(&atom.terms[field])) {
      if (reference::input::scalar(*constant) != row[field]) return {};
    }
  }
  return result;
}

std::optional<Assignment> source_assignment(const auto& plan,
    const auto& input, const Row& row, const RowAdapter& adapter = {}) {
  if (adapter) return adapter(input.occurrence, row);
  if (!plan.normalized())
    return assign_terms(plan.query().atoms.at(input.occurrence.value), row);
  const auto& program = reference::input::normalized(*plan.normalized());
  const auto logical = frontend::adapt_row(program, input.occurrence, row);
  if (!logical) return {};
  return assign_terms(program.core.atoms.at(input.occurrence.value), *logical);
}

std::vector<std::vector<CanonicalCount>> independent_derivations(
    const auto& plan, const Database& database, const RowAdapter& adapter = {}) {
  std::vector<Counts> counts(plan.inputs().size());
  for (const auto& input : plan.inputs()) {
    const auto& scope = plan.nodes().at(input.node.value).scope;
    for (const auto& row : database.tables.at(input.base.value)) {
      const auto assignment = source_assignment(plan, input, row, adapter);
      if (assignment) ++counts.at(input.occurrence.value)[project(*assignment, scope)];
    }
  }
  std::vector<std::vector<CanonicalCount>> result;
  result.reserve(counts.size());
  for (const auto& occurrence : counts) {
    std::vector<CanonicalCount> entries;
    entries.reserve(occurrence.size());
    for (const auto& [key, count] : occurrence) entries.push_back({key, count});
    result.push_back(std::move(entries));
  }
  return result;
}

Relation independent_output(const auto& plan, const Database& database) {
  if (!plan.normalized())
    return reference::evaluate(reference::input::catalog(plan.source_catalog()), reference::input::query(plan.query()), database);
  const auto& program = reference::input::normalized(*plan.normalized());
  Database logical;
  logical.tables.resize(program.core_catalog.tables.size());
  for (const auto& adapter : program.adapters) {
    const auto target = program.core.atoms.at(adapter.occurrence.value).table;
    for (const auto& row : database.tables.at(adapter.base.value))
      if (auto mapped = frontend::adapt_row(program, adapter.occurrence, row))
        logical.tables.at(target.value).insert(std::move(*mapped));
  }
  const auto core = reference::evaluate(program.core_catalog, program.core, logical);
  return frontend::map_sql_result(program, core);
}

Relation independent_core(const auto& plan, const Database& database) {
  if (!plan.normalized())
    return reference::evaluate(reference::input::catalog(plan.source_catalog()), reference::input::query(plan.query()), database);
  const auto& program = reference::input::normalized(*plan.normalized());
  Database logical;
  logical.tables.resize(program.core_catalog.tables.size());
  for (const auto& adapter : program.adapters) {
    const auto target = program.core.atoms.at(adapter.occurrence.value).table;
    for (const auto& row : database.tables.at(adapter.base.value))
      if (auto mapped = frontend::adapt_row(program, adapter.occurrence, row))
        logical.tables.at(target.value).insert(std::move(*mapped));
  }
  return reference::evaluate(program.core_catalog, program.core, logical);
}

Relation drain(SupportRuntime::ResultCursor& cursor, const std::string& where) {
  Relation rows;
  while (auto tuple = cursor.next()) {
    check(tuple->layout().same_token(cursor.layout()), where + ": tuple layout token changed");
    check(tuple->values().size() == cursor.layout().fields().size(), where + ": output arity changed");
    for (std::size_t field = 0; field < tuple->values().size(); ++field)
      check(type_of(tuple->values()[field]) == cursor.layout().fields()[field].type,
            where + ": output scalar type changed");
    check(rows.insert(crown::storage::export_row(tuple->values())).second, where + ": cursor emitted a duplicate set row");
  }
  return rows;
}
Relation drain(SupportRuntime::ResultCursor&& cursor,const std::string& where) {
  return drain(cursor,where);
}

void check_physical_state(const PhysicalRuntime& runtime, const Database& database,
                          const RowAdapter& adapter = {}, std::uint64_t sequence = 0) {
  const auto state = runtime.snapshot();
  const auto canonical = runtime.canonical_state();
  check(runtime.sequence() == sequence && state.sequence == sequence &&
        state.support.sequence == sequence && canonical.sequence == sequence &&
        canonical.support.sequence == sequence,
        "physical snapshot sequence differs from the committed owner sequence");
  check(state.physical.tables == database.tables && canonical.sources == database.tables,
        "initialized physical source sets differ from the complete input snapshot");
  check(canonical.derivations == independent_derivations(runtime.plan(), database, adapter),
        "initialized per-occurrence counts differ from an independent source scan");
  check(runtime.inspect_invariants().valid(), "initialized physical invariants are not valid");
  auto cursor = runtime.results();
  check(drain(cursor, "physical initialized output") ==
        independent_output(runtime.plan(), database),
        "initialized physical output differs from the reference evaluator");
}

std::vector<Relation> independent_live_factors(const auto& plan,
                                                const Relation& core) {
  std::map<VariableId, std::size_t> head_positions;
  for (std::size_t i = 0; i < plan.query().head.size(); ++i)
    head_positions.try_emplace(plan.query().head[i].variable, i);
  std::vector<Relation> result;
  for (const auto& step : plan.enumeration().steps) {
    const auto& scope = plan.nodes().at(step.node.value).visible_scope;
    Relation factor;
    for (const auto& row : core) {
      Row key;
      for (const auto variable : scope) {
        const auto position = head_positions.find(variable);
        check(position != head_positions.end(), "live scope variable missing from core head");
        key.push_back(row.at(position->second));
      }
      factor.insert(std::move(key));
    }
    result.push_back(std::move(factor));
  }
  return result;
}

void check_delta_state(const DeltaRuntime& runtime, const Database& database,
                       const RowAdapter& adapter = {}) {
  const auto snapshot = runtime.snapshot();
  const auto canonical = runtime.canonical_state();
  check(snapshot.sequence == runtime.sequence() && snapshot.physical.tables == database.tables,
        "initialized delta physical snapshot differs from the full source database");
  check(canonical.physical.sources == database.tables &&
        canonical.physical.derivations == independent_derivations(runtime.plan(), database, adapter),
        "initialized delta source or alias counts differ from an independent scan");
  check(runtime.inspect_invariants().valid(), "initialized delta invariants are not valid");
  auto cursor = runtime.results();
  check(drain(cursor, "delta initialized output") ==
        independent_output(runtime.plan(), database),
        "initialized delta output differs from the reference evaluator");

  if (runtime.mode() == DeltaMode::maintenance) {
    check(!canonical.live && !runtime.live_snapshot(), "maintenance initialization retained a live image");
    return;
  }
  check(canonical.live.has_value(), "delta initialization omitted L and its two live indexes");
  const auto live = runtime.live_snapshot();
  check(live.has_value() && live->sequence == runtime.sequence(), "initialized live snapshot is missing or stale");
  const auto wanted = independent_live_factors(runtime.plan(), independent_core(runtime.plan(), database));
  check(live->factors == wanted, "initialized live factors differ from independent A04 projections");
  check(canonical.live->factors.size() == wanted.size(), "canonical live factors are incomplete");
  std::size_t rows = 0, parent_rows = 0, child_rows = 0;
  for (std::size_t i = 0; i < wanted.size(); ++i) {
    check(canonical.live->factors[i].rows == wanted[i], "canonical live factor rows differ from A04");
    rows += wanted[i].size();
    for (const auto& bucket : canonical.live->factors[i].parents) parent_rows += bucket.rows.size();
    for (const auto& bucket : canonical.live->factors[i].children) child_rows += bucket.rows.size();
  }
  check(canonical.live->rows == rows && canonical.live->parent_rows == parent_rows &&
        canonical.live->child_rows == child_rows,
        "canonical live aggregate counts do not reconcile with the complete indexes");
  const auto report = runtime.inspect_invariants();
  check(report.statistics.live_rows == rows && report.statistics.live_parent_rows == parent_rows &&
        report.statistics.live_child_rows == child_rows,
        "live inspection totals do not reconcile with canonical state");
}

PhysicalPlan intersection_plan(std::size_t children) {
  Catalog catalog{11, {}};
  Query query;
  query.variables.push_back({"x", ScalarType::int64});
  std::vector<NodeId> child_ids;
  for (std::size_t i = 0; i < children; ++i) {
    const auto table = TableId{i};
    catalog.tables.push_back({"t" + std::to_string(i),
        {{"x", ScalarType::int64}, {"local", ScalarType::int64}, {"payload", ScalarType::string}}});
    const auto variable = VariableId{i + 1};
    query.variables.push_back({"v" + std::to_string(i), ScalarType::int64});
    query.atoms.push_back({"a" + std::to_string(i), table,
        {VariableId{0}, variable, IgnoredColumn{}}});
    query.head.push_back({variable, "v" + std::to_string(i)});
    child_ids.push_back(NodeId{i + 1});
  }
  query.head.insert(query.head.begin(), {VariableId{0}, "x"});
  FreeConnexTree tree;
  tree.root = NodeId{0};
  tree.nodes.push_back({"common_x", NodeKind::generalized, {VariableId{0}}, child_ids, {}, {}});
  for (std::size_t i = 0; i < children; ++i)
    tree.nodes.push_back({"a" + std::to_string(i), NodeKind::native,
        {VariableId{0}, VariableId{i + 1}}, {}, i, {}});
  return s04_runtime::lower_tree(catalog, query, tree);
}

Database intersection_database(std::size_t children) {
  Database database;
  database.tables.resize(children);
  for (std::size_t i = 0; i < children; ++i) {
    database.tables[i].insert({n(1), n(static_cast<std::int64_t>(10 + i)), s("copy-a")});
    database.tables[i].insert({n(1), n(static_cast<std::int64_t>(10 + i)), s("copy-b")});
    if (i + 1 < children)
      database.tables[i].insert({n(2), n(static_cast<std::int64_t>(20 + i)), s("only-some-children")});
  }
  return database;
}

void check_build_metrics(const BuildMetrics& direct, const BuildMetrics& replay,
                         const std::string& where) {
  check(direct.replay_inputs == 0 && direct.replay_events == 0 && direct.replay_work == 0,
        where + ": direct build reported replay work");
  check(replay.replay_inputs > 0, where + ": insertion replay did not ingest any source rows");
}

void generalized_bootstrap_and_live_indexes(std::size_t children) {
  const auto plan = intersection_plan(children);
  const auto database = intersection_database(children);
  const BuildOptions direct_options{BuildMethod::direct, std::nullopt};
  const BuildOptions replay_options{BuildMethod::insertion_replay, std::nullopt};
  auto direct = PhysicalRuntime::initialize(plan, database, {}, direct_options);
  auto replay = PhysicalRuntime::initialize(plan, database, {}, replay_options);
  check_build_metrics(direct.initialization_metrics(), replay.initialization_metrics(),
                      "generalized " + std::to_string(children) + " child build");
  check_physical_state(direct, database);
  check_physical_state(replay, database);
  check(direct.canonical_state() == replay.canonical_state(),
        "direct and replay builds differ for a generalized multi-child intersection");
  const auto root = direct.canonical_state().support.nodes.at(0);
  check(root.records.size() == 2 && root.survivors == Relation{{n(1)}},
        "generalized candidate union or children-first intersection is incorrect");

  DeltaOptions delta_options;
  delta_options.mode = DeltaMode::delta;
  delta_options.spool_row_limit = 0;
  delta_options.spool_byte_limit = 0;
  auto maintained = DeltaRuntime::initialize(plan, database, delta_options, direct_options);
  auto maintained_replay = DeltaRuntime::initialize(plan, database, delta_options, replay_options);
  check_build_metrics(maintained.initialization_metrics(), maintained_replay.initialization_metrics(),
                      "delta generalized build");
  check(maintained.canonical_state() == maintained_replay.canonical_state(),
        "direct and replay delta initialization differ");
  check(maintained.bootstrap_metrics().spool_rows == 0 && maintained.bootstrap_metrics().spool_bytes == 0,
        "initial live bootstrap retained signed output records");
  check_delta_state(maintained, database);
  check_delta_state(maintained_replay, database);
}

PhysicalPlan internal_native_root_plan() {
  const Catalog catalog{4, {
      {"left", {{"x", ScalarType::int64}, {"y", ScalarType::int64}, {"tag", ScalarType::string}}},
      {"right", {{"y", ScalarType::int64}, {"z", ScalarType::int64}, {"tag", ScalarType::string}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}, {"z", ScalarType::int64}},
      {{"left", TableId{0}, {VariableId{0}, VariableId{1}, IgnoredColumn{}}},
       {"right", TableId{1}, {VariableId{1}, VariableId{2}, IgnoredColumn{}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "y"}, {VariableId{2}, "z"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"left_root", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{1}}, 0, {}},
       {"right_child", NodeKind::native, {VariableId{1}, VariableId{2}}, {}, 1, {}}}, {}, {}};
  return s04_runtime::lower_tree(catalog, query, tree);
}

void native_root_and_disconnected_nullary() {
  const auto plan = internal_native_root_plan();
  Database database;
  database.tables = {
      {{n(1), n(2), s("left-1")}, {n(1), n(2), s("left-2")}, {n(9), n(3), s("no-match")}},
      {{n(2), n(8), s("right-1")}, {n(2), n(7), s("right-2")}}};
  auto direct = PhysicalRuntime::initialize(plan, database);
  auto replay = PhysicalRuntime::initialize(plan, database, {}, {BuildMethod::insertion_replay, std::nullopt});
  check_physical_state(direct, database);
  check(direct.canonical_state() == replay.canonical_state(),
        "native internal root direct and replay states differ");
  check(direct.canonical_state().support.nodes.at(0).kind == NodeKind::native &&
        direct.canonical_state().support.nodes.at(0).records.size() == 2,
        "native internal root did not retain its own projected records");

  const Catalog product_catalog{1, {
      {"a", {{"x", ScalarType::int64}}}, {"b", {{"y", ScalarType::string}}}}};
  const Query product_query{{{"x", ScalarType::int64}, {"y", ScalarType::string}},
      {{"a", TableId{0}, {VariableId{0}}}, {"b", TableId{1}, {VariableId{1}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "y"}}, false};
  const FreeConnexTree product_tree{NodeId{0},
      {{"separator", NodeKind::generalized, {}, {NodeId{1}, NodeId{2}}, {}, {}},
       {"a", NodeKind::native, {VariableId{0}}, {}, 0, {}},
       {"b", NodeKind::native, {VariableId{1}}, {}, 1, {}}}, {}, {}};
  const auto product_plan = s04_runtime::lower_tree(product_catalog, product_query, product_tree);
  Database product_database;
  product_database.tables = {{{n(1)}, {n(2)}}, {{s("m")}, {s("n")}}};
  auto product = PhysicalRuntime::initialize(product_plan, product_database);
  check_physical_state(product, product_database);
  check(drain(product.results(), "disconnected product").size() == 4,
        "disconnected nullary separator did not produce the independent product");

  const Catalog boolean_catalog{2, {{"flags", {{"enabled", ScalarType::boolean}, {"payload", ScalarType::string}}}}};
  const Query boolean_query{{}, {{"any", TableId{0}, {IgnoredColumn{}, IgnoredColumn{}}}}, {}, false};
  const FreeConnexTree nullary_tree{NodeId{0}, {{"any", NodeKind::native, {}, {}, 0, {}}}, {}, {}};
  const auto nullary_plan = s04_runtime::lower_tree(boolean_catalog, boolean_query, nullary_tree);
  Database empty;
  empty.tables.resize(1);
  auto empty_nullary = PhysicalRuntime::initialize(nullary_plan, empty);
  check_physical_state(empty_nullary, empty);
  Database witnesses;
  witnesses.tables = {{{Value{true}, s("one")}, {Value{false}, s("two")}}};
  auto nonempty_nullary = PhysicalRuntime::initialize(nullary_plan, witnesses);
  check_physical_state(nonempty_nullary, witnesses);
  check(nonempty_nullary.derivation_count(OccurrenceId{0}, {}) == 2 &&
        nonempty_nullary.has_answer(), "nullary answer lost per-source-row derivation counts");
}

PhysicalPlan sql_plan(std::string_view sql, const Catalog& catalog) {
  const auto binding = frontend::bind_sql(sql, catalog);
  if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&binding))
    throw std::runtime_error(failure->diagnostic.code + ": " + failure->diagnostic.message);
  auto normalized = frontend::normalize_sql(std::get<frontend::BoundSql>(binding));
  if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&normalized))
    throw std::runtime_error(failure->diagnostic.code + ": " + failure->diagnostic.message);
  auto program = std::get<frontend::NormalizedSql>(std::move(normalized));
  const auto& query = program.core;
  if (query.contradiction || query.atoms.empty())
    return s04_runtime::lower_normalized(program, FreeConnexTree{});
  FreeConnexTree tree;
  tree.root = NodeId{0};
  if (query.atoms.size() == 1) {
    VariableSet scope;
    for (const auto& term : query.atoms[0].terms)
      if (const auto* variable = std::get_if<VariableId>(&term)) scope.insert(*variable);
    tree.nodes.push_back({query.atoms[0].occurrence, NodeKind::native, scope, {}, 0, {}});
    return s04_runtime::lower_normalized(program, tree);
  }
  VariableSet common;
  bool first = true;
  std::vector<VariableSet> scopes(query.atoms.size());
  for (std::size_t i = 0; i < query.atoms.size(); ++i) {
    for (const auto& term : query.atoms[i].terms)
      if (const auto* variable = std::get_if<VariableId>(&term)) scopes[i].insert(*variable);
    if (first) { common = scopes[i]; first = false; }
    else {
      VariableSet intersection;
      std::set_intersection(common.begin(), common.end(), scopes[i].begin(), scopes[i].end(),
          std::inserter(intersection, intersection.end()));
      common = std::move(intersection);
    }
  }
  std::vector<NodeId> children;
  for (std::size_t i = 0; i < query.atoms.size(); ++i) children.push_back(NodeId{i + 1});
  tree.nodes.push_back({"sql_root", NodeKind::generalized, common, children, {}, {}});
  for (std::size_t i = 0; i < query.atoms.size(); ++i)
    tree.nodes.push_back({query.atoms[i].occurrence, NodeKind::native, scopes[i], {}, i, {}});
  return s04_runtime::lower_normalized(program, tree);
}

PhysicalPlan filtered_self_join_plan(const Catalog& catalog) {
  return sql_plan("SELECT DISTINCT a.x, a.x AS again, 7 AS fixed "
                  "FROM r a JOIN r b ON a.x=b.x WHERE a.flag=1", catalog);
}

RowAdapter filtered_self_join_adapter() {
  return [](OccurrenceId occurrence, const Row& row) -> std::optional<Assignment> {
    if (occurrence == OccurrenceId{0} && row.at(1) != n(1)) return {};
    return Assignment{{VariableId{0}, row.at(0)}};
  };
}

Relation independent_filtered_sql(const Database& database) {
  std::set<Value> left, right;
  for (const auto& row : database.tables.at(0)) {
    right.insert(row.at(0));
    if (row.at(1) == n(1)) left.insert(row.at(0));
  }
  Relation output;
  for (const auto& value : left)
    if (right.contains(value)) output.insert({value, value, n(7)});
  return output;
}

Relation drain_signed(DeltaRuntime::Epoch& epoch, const Relation& before,
                      const Relation& after, const std::string& where) {
  std::set<SignedKey> expected, actual;
  for (const auto& row : after) if (!before.contains(row)) expected.emplace(SetOperation::insert, row);
  for (const auto& row : before) if (!after.contains(row)) expected.emplace(SetOperation::erase, row);
  std::size_t records = 0;
  while (auto record = epoch.next()) {
    ++records;
    check(actual.emplace(record->operation, crown::storage::export_row(record->tuple.values())).second,
          where + ": a raw signed record was duplicated");
    check(record->tuple.layout().same_token(epoch.layout()), where + ": signed output layout changed");
  }
  check(actual == expected && records == expected.size(),
        where + ": raw signed records differ from independent before/after A04 sets");
  return after;
}

void apply_checked_sql_delta(DeltaRuntime& runtime, Database& database,
                             std::uint64_t sequence, SetOperation operation,
                             const Row& row) {
  const auto before = independent_filtered_sql(database);
  Database after = database;
  if (operation == SetOperation::insert) after.tables[0].insert(row);
  else after.tables[0].erase(row);
  const auto expected_after = independent_filtered_sql(after);
  auto epoch = runtime.apply({sequence, TableId{0}, operation, row});
  check(epoch.sequence() == sequence && epoch.input().input.sequence == sequence,
        "delta initialization suffix did not advance from public sequence one");
  static_cast<void>(drain_signed(epoch, before, expected_after,
                                 "initialized SQL event " + std::to_string(sequence)));
  database = std::move(after);
  check(runtime.ready() && runtime.sequence() == sequence,
        "draining an initialized suffix did not release the writer");
  check_delta_state(runtime, database, filtered_self_join_adapter());
  check(drain(runtime.results(), "initialized SQL suffix output") == expected_after,
        "committed suffix result differs from the independent SQL self-join");
}

void aliases_projection_collisions_and_suffix() {
  const Catalog catalog{6, {{"r", {{"x", ScalarType::int64}, {"flag", ScalarType::int64},
                                      {"payload", ScalarType::string}}}}};
  const auto plan = filtered_self_join_plan(catalog);
  Database database;
  database.tables = {{{n(1), n(1), s("first")}, {n(1), n(1), s("second")}}};
  const auto adapter = filtered_self_join_adapter();
  auto direct = PhysicalRuntime::initialize(plan, database);
  auto replay = PhysicalRuntime::initialize(plan, database, {}, {BuildMethod::insertion_replay, std::nullopt});
  check_physical_state(direct, database, adapter);
  check_physical_state(replay, database, adapter);
  check(direct.canonical_state() == replay.canonical_state(),
        "direct and replay builds differ with alias filters and projection collisions");
  check(drain(direct.results(), "repeated and constant SQL projection") ==
        Relation{{n(1), n(1), n(7)}},
        "initial SQL output lost repeated or constant head fields");
  check(direct.canonical_state().derivations.at(0).front().count == 2 &&
        direct.canonical_state().derivations.at(1).front().count == 2,
        "full-row source identity did not retain both projected alias counts");

  DeltaOptions options;
  options.mode = DeltaMode::delta;
  auto maintained = DeltaRuntime::initialize(plan, database, options);
  check_delta_state(maintained, database, adapter);
  apply_checked_sql_delta(maintained, database, 1, SetOperation::insert, {n(1), n(1), s("first")});
  apply_checked_sql_delta(maintained, database, 2, SetOperation::insert, {n(1), n(1), s("third")});
  apply_checked_sql_delta(maintained, database, 3, SetOperation::insert, {n(2), n(0), s("filtered")});
  apply_checked_sql_delta(maintained, database, 4, SetOperation::insert, {n(2), n(1), s("matching")});
  apply_checked_sql_delta(maintained, database, 5, SetOperation::erase, {n(9), n(1), s("absent")});
  apply_checked_sql_delta(maintained, database, 6, SetOperation::erase, {n(1), n(1), s("first")});
  apply_checked_sql_delta(maintained, database, 7, SetOperation::erase, {n(1), n(1), s("second")});
  apply_checked_sql_delta(maintained, database, 8, SetOperation::erase, {n(1), n(1), s("third")});
}

PhysicalPlan reciprocal_loop_plan() {
  const Catalog catalog{9, {{"edge", {{"src", ScalarType::int64}, {"dst", ScalarType::int64},
                                         {"enabled", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"forward", TableId{0}, {VariableId{0}, VariableId{1}, n(1)}},
       {"reverse", TableId{0}, {VariableId{1}, VariableId{0}, n(1)}},
       {"loop", TableId{0}, {VariableId{0}, VariableId{0}, n(1)}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "y"}, {VariableId{0}, "again"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"common", NodeKind::generalized, {VariableId{0}}, {NodeId{1}, NodeId{3}}, {}, {}},
       {"forward", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{2}}, 0, {}},
       {"reverse", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 1, {}},
       {"loop", NodeKind::native, {VariableId{0}}, {}, 2, {}}}, {}, {}};
  return s04_runtime::lower_tree(catalog, query, tree);
}

void self_join_loops_and_constants() {
  const auto plan = reciprocal_loop_plan();
  Database database;
  database.tables = {{{n(1), n(2), n(1)}, {n(2), n(1), n(1)}, {n(1), n(1), n(1)},
                      {n(4), n(4), n(1)}, {n(1), n(2), n(0)}}};
  auto direct = PhysicalRuntime::initialize(plan, database);
  auto replay = PhysicalRuntime::initialize(plan, database, {}, {BuildMethod::insertion_replay, std::nullopt});
  check_physical_state(direct, database);
  check(direct.canonical_state() == replay.canonical_state(),
        "direct/replay differs for repeated-variable self-join loops and constants");
  check(drain(direct.results(), "loop/repeated-variable result") ==
        Relation{{n(1), n(1), n(1)}, {n(1), n(2), n(1)}, {n(4), n(4), n(4)}},
        "self-join loops or repeated output variables were evaluated incorrectly");
}

Catalog cyclic_catalog() {
  Catalog catalog{12, {
      {"a", {{"id", ScalarType::int64}, {"b_id", ScalarType::int64}}},
      {"b", {{"id", ScalarType::int64}, {"a_id", ScalarType::int64}}},
      {"unused", {{"label", ScalarType::string}}}}};
  catalog.tables[0].constraints = {
      UniqueConstraint{"a_pk", {ColumnId{0}}, ConstraintStatus::enforced},
      ForeignKeyConstraint{"a_to_b", {ColumnId{1}}, TableId{1}, {ColumnId{0}}, ConstraintStatus::enforced}};
  catalog.tables[1].constraints = {
      UniqueConstraint{"b_pk", {ColumnId{0}}, ConstraintStatus::enforced},
      ForeignKeyConstraint{"b_to_a", {ColumnId{1}}, TableId{0}, {ColumnId{0}}, ConstraintStatus::enforced}};
  return catalog;
}

PhysicalPlan cyclic_plan(const Catalog& catalog) {
  const Query query{{{"id", ScalarType::int64}},
      {{"only_a", TableId{0}, {VariableId{0}, IgnoredColumn{}}}},
      {{VariableId{0}, "id"}}, false};
  const FreeConnexTree tree{NodeId{0}, {{"only_a", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
  return s04_runtime::lower_tree(catalog, query, tree);
}

void cyclic_constraints_and_rejected_images() {
  const auto catalog = cyclic_catalog();
  const auto plan = cyclic_plan(catalog);
  Database cycle;
  cycle.tables = {{{n(1), n(10)}}, {{n(10), n(1)}}, {{s("unused, but validated")}}};
  PhysicalRuntime empty(plan);
  expect_code([&] { static_cast<void>(empty.apply({1, TableId{0}, SetOperation::insert, {n(1), n(10)}})); },
              "constraint_violation");
  auto initialized = PhysicalRuntime::initialize(plan, cycle);
  check_physical_state(initialized, cycle);
  check(initialized.sequence() == 0 && initialized.snapshot().physical.tables == cycle.tables,
        "valid cyclic foreign-key snapshot did not initialize at sequence zero");

  auto duplicate_unique = cycle;
  duplicate_unique.tables[0].insert({n(1), n(10)});
  duplicate_unique.tables[0].insert({n(1), n(20)});
  duplicate_unique.tables[1].insert({n(20), n(1)});
  expect_code([&] { static_cast<void>(PhysicalRuntime::initialize(plan, duplicate_unique)); },
              "constraint_violation");
  auto dangling_unused = cycle;
  dangling_unused.tables[2].insert({s("bad unused row")});
  dangling_unused.tables[1].insert({n(20), n(99)});
  expect_code([&] { static_cast<void>(PhysicalRuntime::initialize(plan, dangling_unused)); },
              "constraint_violation");
  auto missing_table = cycle;
  missing_table.tables.pop_back();
  expect_code([&] { static_cast<void>(PhysicalRuntime::initialize(plan, missing_table)); },
              "invalid_database");
  auto short_row = cycle;
  short_row.tables[2].insert({s("wrong arity")});
  short_row.tables[0].insert({n(2)});
  expect_code([&] { static_cast<void>(PhysicalRuntime::initialize(plan, short_row)); }, "invalid_update");
  auto wrong_type = cycle;
  wrong_type.tables[2].insert({s("wrong type")});
  wrong_type.tables[0].insert({s("not an integer"), n(10)});
  expect_code([&] { static_cast<void>(PhysicalRuntime::initialize(plan, wrong_type)); }, "invalid_update");
}

void physical_rebuild_ownership_and_barriers() {
  const auto plan = intersection_plan(3);
  const auto database = intersection_database(3);
  auto runtime = PhysicalRuntime::initialize(plan, database);
  const auto initial_handle = runtime.find_source(TableId{0}, {n(1), n(10), s("copy-a")});
  check(initial_handle.has_value(), "initialized source handle missing");
  const auto support_handle = runtime.find_support(NodeId{1}, SupportRole::records, {n(1), n(10)});
  check(support_handle.has_value(), "initialized native support handle missing");
  const auto old_owner = runtime.owner();
  const auto before = runtime.canonical_state();

  {
    auto cursor = runtime.results();
    expect_code([&] { static_cast<void>(runtime.rebuilt()); }, "runtime_busy");
    cursor.cancel();
  }
  {
    auto pending = runtime.prepare({1, TableId{0}, SetOperation::insert,
                                    {n(1), n(10), s("copy-a")}});
    expect_code([&] { static_cast<void>(runtime.rebuilt()); }, "runtime_busy");
  }
  check(runtime.ready() && runtime.sequence() == 0 && runtime.canonical_state() == before,
        "rejected rebuild barrier changed the original owner");
  expect_code([&] { static_cast<void>(runtime.rebuilt({BuildMethod::direct, 0})); }, "resource_limit");
  check(runtime.owner() == old_owner && runtime.canonical_state() == before,
        "failed rebuild changed the original owner, handles, or state");

  static_cast<void>(runtime.apply({1, TableId{0}, SetOperation::insert,
                                   {n(1), n(10), s("copy-a")}}));
  const auto advanced = runtime.canonical_state();
  const auto old_result = [&]() {
    auto cursor = runtime.results();
    auto tuple = cursor.next();
    check(tuple.has_value(), "initialized result tuple missing before rebuild");
    cursor.cancel();
    return *tuple;
  }();
  auto rebuilt = runtime.rebuilt();
  check(rebuilt.owner() != runtime.owner() && rebuilt.sequence() == 1 &&
        rebuilt.canonical_state() == advanced,
        "rebuild did not publish a new owner with the original committed sequence and canonical state");
  check(runtime.owner() == old_owner && runtime.canonical_state() == advanced,
        "rebuild modified or rebound the original owner");
  check(runtime.get_source(TableId{0}, *initial_handle).has_value() &&
        runtime.get_support(*support_handle).has_value(),
        "rebuild invalidated handles still owned by the original runtime");
  expect_code([&] { static_cast<void>(rebuilt.get_source(TableId{0}, *initial_handle)); }, "foreign_handle");
  expect_code([&] { static_cast<void>(rebuilt.get_support(*support_handle)); }, "foreign_support_handle");
  check(old_result.values() == Row{n(1), n(10), n(11), n(12)},
        "a tuple returned before rebuild lost its owning values");
  check_physical_state(rebuilt, database, {}, 1);
}

void delta_rebuild_preserves_mode_and_barrier() {
  const auto plan = intersection_plan(3);
  auto database = intersection_database(3);
  DeltaOptions options;
  options.mode = DeltaMode::delta;
  options.live_maintenance = LiveMaintenance::eager;
  options.spool_row_limit = 8;
  options.spool_byte_limit = 4096;
  auto runtime = DeltaRuntime::initialize(plan, database, options);
  static_cast<void>(runtime.apply({1, TableId{0}, SetOperation::insert,
                                  {n(1), n(10), s("copy-a")}}));
  const auto before = runtime.canonical_state();
  auto rebuilt = runtime.rebuilt();
  check(rebuilt.owner() != runtime.owner() && rebuilt.sequence() == 1 &&
        rebuilt.mode() == DeltaMode::delta && rebuilt.options().live_maintenance == LiveMaintenance::eager &&
        rebuilt.canonical_state() == before,
        "delta rebuild did not preserve sequence, configured mode, policy, and canonical indexes");
  check(runtime.canonical_state() == before && runtime.sequence() == 1,
        "delta rebuild modified its original owner");
  check_delta_state(rebuilt, database);

  static_cast<void>(runtime.apply({2, TableId{0}, SetOperation::erase,
                                   {n(1), n(10), s("copy-a")}}));
  auto output = runtime.apply({3, TableId{0}, SetOperation::erase,
                               {n(1), n(10), s("copy-b")}});
  expect_code([&] { static_cast<void>(runtime.rebuilt()); }, "runtime_busy");
  output.discard();
  database.tables[0].erase({n(1), n(10), s("copy-a")});
  database.tables[0].erase({n(1), n(10), s("copy-b")});
  auto after_output = runtime.rebuilt();
  check(after_output.sequence() == 3 && after_output.canonical_state() == runtime.canonical_state(),
        "delta rebuild after output drain failed to preserve committed state");
}

void scalar_exists_and_constant_routes() {
  const Catalog source{3, {{"r", {{"x", ScalarType::int64}}}}};
  const auto exists = sql_plan("SELECT EXISTS(SELECT NULL FROM r)", source);
  Database empty;
  empty.tables.resize(1);
  DeltaOptions options;
  options.mode = DeltaMode::delta;
  options.spool_row_limit = 0;
  options.spool_byte_limit = 0;
  auto false_at_zero = DeltaRuntime::initialize(exists, empty, options);
  check_delta_state(false_at_zero, empty);
  check(drain(false_at_zero.results(), "false scalar exists at sequence zero") ==
        Relation{{Value{false}}}, "scalar EXISTS false row was absent at initial epoch zero");
  Database populated;
  populated.tables = {{{n(44)}}};
  auto true_at_zero = DeltaRuntime::initialize(exists, populated, options);
  check_delta_state(true_at_zero, populated);
  check(drain(true_at_zero.results(), "true scalar exists at sequence zero") ==
        Relation{{Value{true}}}, "scalar EXISTS true row was absent at initial epoch zero");

  const Catalog no_tables{1, {}};
  const auto constant_true = sql_plan("SELECT DISTINCT 7 AS fixed", no_tables);
  auto true_constant = PhysicalRuntime::initialize(constant_true, Database{});
  check_physical_state(true_constant, Database{});
  check(drain(true_constant.results(), "source-free constant true") == Relation{{n(7)}},
        "source-free constant true route was initialized as an empty union");

  const auto source_constant = sql_plan("SELECT DISTINCT 7 AS fixed FROM r", source);
  auto nullary_source = PhysicalRuntime::initialize(source_constant, empty);
  check_physical_state(nullary_source, empty);
  check(nullary_source.plan().nodes().size() == 1 && nullary_source.plan().nodes()[0].scope.empty(),
        "constant projection did not retain its nullary native route");
  Database one_row;
  one_row.tables = {{{n(1)}, {n(2)}}};
  auto true_nullary = PhysicalRuntime::initialize(source_constant, one_row);
  check_physical_state(true_nullary, one_row);
  check(true_nullary.derivation_count(OccurrenceId{0}, {}) == 2 &&
        drain(true_nullary.results(), "source constant projection") == Relation{{n(7)}},
        "nullary derivation count or constant projection output is wrong");

  const auto false_route = sql_plan("SELECT DISTINCT 7 AS fixed FROM r WHERE FALSE", source);
  auto false_constant = PhysicalRuntime::initialize(false_route, one_row);
  check_physical_state(false_constant, one_row);
  check(false_constant.canonical_state().sources == one_row.tables &&
        drain(false_constant.results(), "source-backed constant false") .empty(),
        "constant false initialization skipped source ownership or emitted an answer");
}

std::string json_input(const auto& plan, std::uint64_t sequence,
                       TableId table, Row row) {
  return io::write_input_json({PhysicalSetUpdate{sequence, table, SetOperation::insert, std::move(row)},
                               std::nullopt}, plan.source_catalog()) + "\n";
}

void session_initial_database_and_first_event() {
  const Catalog catalog{6, {{"r", {{"x", ScalarType::int64}, {"flag", ScalarType::int64},
                                      {"payload", ScalarType::string}}}}};
  const auto plan = filtered_self_join_plan(catalog);
  Database supplied;
  supplied.tables = {{{n(1), n(1), s("initial")}}};
  const auto original = supplied;
  const auto source_row = Row{n(2), n(1), s("after-bootstrap")};
  auto input = std::make_unique<std::istringstream>(json_input(plan, 1, TableId{0}, source_row));
  auto session = QuerySession::create(plan, supplied, std::move(input), SessionOptions{}, BuildOptions{});
  supplied.tables[0].clear();
  check(session->status().committed_sequence == 0 && session->progress() == io::InputProgress{},
        "initial Database was counted as accepted session input progress");
  check(session->snapshot().sequence == 0 &&
        independent_filtered_sql(original) == Relation{{n(1), n(1), n(7)}},
        "session did not preserve the owned initial snapshot at sequence zero");
  const auto initial_rows = session->snapshot();
  Relation actual_initial;
  for (const auto& tuple : initial_rows.rows) actual_initial.insert(crown::storage::export_row(tuple.values()));
  check(actual_initial == independent_filtered_sql(original),
        "session initial snapshot differs from the independent self-join answer");

  session->start();
  check(session->begin_next(), "session did not accept external event one after initialization");
  while (session->step() != DeltaStep::prepared) {}
  session->commit();
  check(session->status().committed_sequence == 1 && session->progress().sequence == 1,
        "first external event did not commit at sequence one");
  Database after = original;
  after.tables[0].insert(source_row);
  std::set<SignedKey> expected{{SetOperation::insert, {n(2), n(2), n(7)}}};
  std::set<SignedKey> actual;
  while (auto record = session->next_output())
    check(actual.emplace(record->operation, crown::storage::export_row(record->tuple.values())).second,
          "session emitted a duplicate first-event signed result");
  check(actual == expected, "session first-event delta differs from independent before/after SQL answers");
  const auto committed = session->snapshot();
  Relation committed_rows;
  for (const auto& tuple : committed.rows) committed_rows.insert(crown::storage::export_row(tuple.values()));
  check(committed.sequence == 1 && committed_rows == independent_filtered_sql(after),
        "session initialized owner did not commit its first external source update");
}

void initialization_budgets() {
  const auto plan = intersection_plan(3);
  const auto database = intersection_database(3);
  expect_code([&] {
    static_cast<void>(PhysicalRuntime::initialize(plan, database, {}, {BuildMethod::direct, 0}));
  }, "resource_limit");
  expect_code([&] {
    static_cast<void>(PhysicalRuntime::initialize(plan, database, {}, {BuildMethod::insertion_replay, 0}));
  }, "resource_limit");
}
}  // namespace

int main() {
  static_assert(!std::is_copy_constructible_v<PhysicalRuntime>);
  static_assert(!std::is_copy_constructible_v<DeltaRuntime>);
  static_assert(!std::is_copy_constructible_v<QuerySession>);
  try {
    generalized_bootstrap_and_live_indexes(3);
    generalized_bootstrap_and_live_indexes(8);
    native_root_and_disconnected_nullary();
    aliases_projection_collisions_and_suffix();
    self_join_loops_and_constants();
    cyclic_constraints_and_rejected_images();
    physical_rebuild_ownership_and_barriers();
    delta_rebuild_preserves_mode_and_barrier();
    scalar_exists_and_constant_routes();
    session_initial_database_and_first_event();
    initialization_budgets();
    std::cout << "R06 initialization, rebuild, aliases, and independent state checks PASS\n";
  } catch (const std::exception& failure) {
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
