#include "selection_fixture.hpp"
#include "crown/api/error.hpp"
#include <iostream>

int main() { try {
  using namespace c05_test;
  const Catalog catalog{7, {{"unused", {{"value", ScalarType::int64}}},
      {"r", {{"x", ScalarType::int64}, {"flag", ScalarType::int64}, {"payload", ScalarType::string}}}}};
  const std::string sql = "SELECT DISTINCT a.x FROM r a JOIN r b ON a.x=b.x WHERE a.flag=1";
  auto bound = frontend::bind_sql(sql, catalog); check(std::holds_alternative<frontend::BoundSql>(bound), "C05 SQL binding");
  auto normalized = frontend::normalize_sql(std::get<frontend::BoundSql>(bound));
  check(std::holds_alternative<frontend::NormalizedSql>(normalized), "C05 SQL normalization");
  const auto program = std::get<frontend::NormalizedSql>(normalized);
  const auto snapshot = c02_test::candidates(Fixture{program.core_catalog, program.core, {}}, 1, 0);
  const auto basis = planner::lower_normalized(program, snapshot.candidate(0)->tree());
  const ps::Source source = ps::PhysicalBasis{basis};
  Database initial; initial.tables.resize(2);
  initial.tables[0] = Relation{Row{std::int64_t{99}}};
  initial.tables[1] = Relation{Row{std::int64_t{1}, std::int64_t{1}, std::string("a")},
      Row{std::int64_t{2}, std::int64_t{0}, std::string("b")}};
  auto owner = runtime::PhysicalRuntime::initialize(basis, initial); owner.configure_workload_statistics(counters());
  for (unsigned i = 0; i < 3; ++i) static_cast<void>(owner.apply({owner.sequence() + 1, TableId{1}, SetOperation::insert, *initial.tables[1].begin()}));
  for (unsigned i = 0; i < 2; ++i) static_cast<void>(owner.apply({owner.sequence() + 1, TableId{1}, SetOperation::erase,
      Row{std::int64_t{3}, std::int64_t{1}, std::string("absent")}}));
  for (unsigned i = 0; i < 2; ++i) static_cast<void>(owner.apply({owner.sequence() + 1, TableId{0}, SetOperation::insert, *initial.tables[0].begin()}));
  const auto facts = capture(snapshot, owner);
  check(facts.inputs().denominator() == 7 && facts.inputs().sources().size() == 1 && facts.inputs().sources()[0].table == TableId{1} &&
      facts.inputs().sources()[0].rows == 2, "C05 alias physical source/denominator");
  auto depth = request(ps::Policy::committed_input_native_depth);
  const auto selected = complete(ps::select(snapshot, source, depth, facts.inputs()));
  const ps::Source native_source=ps::PhysicalBasis{owner.plan()};
  auto compiler_cache=ps::PlanCache::create();auto native_cache=ps::PlanCache::create();
  const auto compiler_cached=complete(ps::select(snapshot,source,depth,facts.inputs(),&compiler_cache,ps::CacheUse::read_write));
  const auto native_cached=complete(ps::select(snapshot,native_source,depth,facts.inputs(),&native_cache,ps::CacheUse::read_write));
  check(compiler_cached.plan().physical_sha256()==native_cached.plan().physical_sha256() &&
    compiler_cached.cache_binding() && native_cached.cache_binding() &&
    *compiler_cached.cache_binding()==*native_cached.cache_binding(),
    "native explicit basis changed exact source/cache binding or selected compiler output");
  check(std::get<CompiledProgram>(std::get<ps::PhysicalBasis>(native_cached.source()).plan).account().statistics().owner==
    owner.accounted_memory_statistics().owner,"native explicit basis created a different query account");
  for (const auto& score : assessment(selected, pr::Policy::committed_input_native_depth).scores()) {
    check(score.numerator == "10" && score.denominator == "7" && score.depths.size() == 2, "C05 alias literal N/W=10/7");
    check(score.table_depths.size() == 2 && score.table_depths[0].contribution == "0" && score.table_depths[1].contribution == "10",
        "C05 unused source/alias term lost");
  }
  auto selected_owner = runtime::PhysicalRuntime::initialize(selected.plan(), initial);
  check(answers(selected_owner) == Relation{Row{std::int64_t{1}}} && selected.plan().normalized() &&
      selected.plan().normalized()->binding.source == sql, "C05 selected normalized source/output lost");
  const auto wrong = ps::select(snapshot, ps::Source{ps::DirectCQ{}}, depth, facts.inputs());
  check(!wrong.selection && wrong.stop == ps::Stop::binding_mismatch, "C05 normalized facts substituted for direct CQ semantics");
  auto different = program; different.binding.source = sql + " /* retained source spelling */";
  // Replay source text rather than accepting this editable program as authority.
  auto changed_bound = frontend::bind_sql(different.binding.source, catalog);
  auto changed_normalized = frontend::normalize_sql(std::get<frontend::BoundSql>(changed_bound));
  const auto changed_basis = planner::lower_normalized(std::get<frontend::NormalizedSql>(changed_normalized), snapshot.candidate(0)->tree());
  const auto mismatched = ps::select(snapshot, ps::Source{ps::PhysicalBasis{changed_basis}}, depth, facts.inputs());
  check(!mismatched.selection && mismatched.stop == ps::Stop::binding_mismatch, "C05 source spelling omitted from full binding");
  for (unsigned field = 0; field < 4; ++field) {
    auto tiny = request(ps::Policy::tuple_index_slots); tiny.constraint = ps::TupleIndexSlotLimit{"1000"};
    if (field == 0) tiny.limits.aggregate.lowering_work = 0;
    if (field == 1) tiny.limits.aggregate.identity_work = 0;
    if (field == 2) tiny.limits.aggregate.binding_replay_work = 0;
    if (field == 3) tiny.limits.aggregate.normalization_work = 0;
    const auto stopped = ps::select(snapshot, source, tiny, facts.inputs());
    check(!stopped.selection && stopped.stop == ps::Stop::resource_limit, "C05 native normalized zero cap became fallback");
  }
  const auto value = Decimal::parse("12345678901234567890123456789012345678");
  const auto predicate = Decimal::parse("87654321098765432109876543210987654321");
  Fixture decimal;
  decimal.catalog = Catalog{1, {{"decimal_rows", {{"x", ScalarType::decimal}, {"filter", ScalarType::decimal}}}}};
  decimal.query = Query{{{"x", ScalarType::decimal}}, {{"r", TableId{0}, {VariableId{0}, Value{predicate}}}},
      {{VariableId{0}, "first"}, {VariableId{0}, "again"}}, false};
  decimal.database.tables = {Relation{Row{value, predicate}, Row{value, Decimal::parse("0")}}};
  const auto decimals = c02_test::candidates(decimal, 1, 1);
  const auto decimal_plan = planner::lower_tree(decimal.catalog, decimal.query, decimals.candidate(0)->tree());
  auto decimal_owner = runtime::PhysicalRuntime::initialize(decimal_plan, decimal.database);
  auto memory = request(ps::Policy::tuple_index_slots); memory.constraint = ps::TupleIndexSlotLimit{"13"};
  const auto accepted = complete(rs::select_current(decimals, ps::Source{ps::DirectCQ{}}, decimal_owner, memory));
  const auto& winner = accepted.selection();
  check(assessment(winner, pr::Policy::tuple_index_slots).scores()[0].slots == "13", "C05 literal repeated Decimal Q=13");
  auto repeated = runtime::PhysicalRuntime::initialize(winner.plan(), decimal.database);
  check(answers(repeated) == Relation{Row{value, value}}, "C05 repeated Decimal output changed");
  bool unequal_rejected = false;
  const auto exported_plan = PhysicalPlan::from_compiled(winner.plan());
  try { static_cast<void>(exported_plan.result_layout().tuple(Row{value, predicate})); }
  catch (const Error& error) { unequal_rejected = error.code() == "invalid_tuple"; }
  check(unequal_rejected, "C05 retained repeated equality missing");
  memory.constraint = ps::TupleIndexSlotLimit{"12"};
  const auto refused = rs::select_current(decimals, ps::Source{ps::DirectCQ{}}, decimal_owner, memory);
  check(!refused.selection && refused.stop == ps::Stop::constraint_unsatisfied, "C05 Decimal exact cap boundary");
  for (bool nullary : {false, true}) {
    Fixture f; f.catalog.tables = {{"T", {{"x", ScalarType::int64}}}};
    if (!nullary) f.query.variables = {{"x", ScalarType::int64}};
    Atom atom{"t", TableId{0}, {}};
    if (nullary) atom.terms.emplace_back(IgnoredColumn{}); else atom.terms.emplace_back(VariableId{0});
    f.query.atoms.push_back(std::move(atom));
    f.database.tables = {Relation{Row{std::int64_t{1}}, Row{std::int64_t{2}}, Row{std::int64_t{3}}}};
    const auto set = c02_test::candidates(f, 1, 0);
    const auto plan = planner::lower_tree(f.catalog, f.query, set.candidate(0)->tree());
    auto actual = runtime::PhysicalRuntime::initialize(plan, f.database);
    auto cap = request(ps::Policy::tuple_index_slots); cap.constraint = ps::TupleIndexSlotLimit{nullary ? "4" : "14"};
    const auto chosen = complete(rs::select_current(set, ps::Source{ps::DirectCQ{}}, actual, cap));
    check(assessment(chosen.selection(), pr::Policy::tuple_index_slots).scores()[0].slots == (nullary ? "4" : "14"), "C05 unary/nullary slots");
    f.database.tables[0].clear(); auto empty = runtime::PhysicalRuntime::initialize(plan, f.database); cap.constraint = ps::TupleIndexSlotLimit{"0"};
    const auto zero = complete(rs::select_current(set, ps::Source{ps::DirectCQ{}}, empty, cap));
    check(assessment(zero.selection(), pr::Policy::tuple_index_slots).scores()[0].slots == "0", "C05 exact zero source cap");
  }
  for (bool contradiction : {false, true}) {
    Fixture f; f.query.contradiction = contradiction; const auto set = c02_test::candidates(f, 0, 1);
    auto owner0 = runtime::PhysicalRuntime::initialize(planner::lower_tree(f.catalog, f.query, set.candidate(0)->tree()), f.database);
    auto cap = request(ps::Policy::tuple_index_slots); cap.constraint = ps::TupleIndexSlotLimit{"0"};
    const auto chosen = complete(rs::select_current(set, ps::Source{ps::DirectCQ{}}, owner0, cap));
    check(chosen.selection().selected().height() == 0 && owner0.has_answer() == !contradiction, "C05 constant operator semantics");
  }
  std::cout << "C05 normalized alias10/7, full source mismatch, Decimal repeated13, unary/nullary/empty/constant cases passed\n";
} catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; } }
