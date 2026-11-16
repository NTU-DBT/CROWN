#include "selection_exception_support.hpp"

int main() { try {
  using namespace c05_fault;
  const Catalog catalog{1, {{"R", {{"x", ScalarType::int64}}}}};
  const std::string sql = "SELECT DISTINCT a.x, a.x AS repeated FROM \"R\" AS a WHERE a.x >= 0";
  auto bound = frontend::bind_sql(sql, catalog);
  check(std::holds_alternative<frontend::BoundSql>(bound), "C05 normalized fault bind");
  auto normalized = frontend::normalize_sql(std::get<frontend::BoundSql>(bound));
  check(std::holds_alternative<frontend::NormalizedSql>(normalized), "C05 normalized fault normalize");
  const auto program = std::get<frontend::NormalizedSql>(std::move(normalized));
  const Fixture logical{program.core_catalog, program.core, {}}; const auto snapshot = c02_test::candidates(logical, 1, 1);
  check(snapshot.candidate_count() == 1, "C05 normalized unary family changed");
  const auto plan = planner::lower_normalized(program, snapshot.candidate(0)->tree());
  const Database database{{Relation{Row{std::int64_t{1}}, Row{std::int64_t{-1}}}}};
  auto owner = runtime::PhysicalRuntime::initialize(plan, database); owner.configure_workload_statistics(counters());
  const auto update = [&](SetOperation operation, std::int64_t value) {
    static_cast<void>(owner.apply({owner.sequence() + 1, TableId{0}, operation, Row{value}}));
  };
  update(SetOperation::insert, 1); update(SetOperation::insert, 2); update(SetOperation::erase, 2); update(SetOperation::erase, 3);
  check(owner.canonical_state().sources == database.tables && answers(owner) == Relation{Row{std::int64_t{1}, std::int64_t{1}}},
      "C05 normalized fault fixture changed source/output");
  const auto evidence = capture(snapshot, owner).inputs(); const ps::Source source = ps::PhysicalBasis{plan};
  Totals totals; const auto height = request(ps::Policy::height_only);
  sweep("C05 normalized winner replay/identity", snapshot, owner, source, evidence, [&](ps::PlanCache& cache) {
    return ps::select(snapshot, source, height, {}, &cache, ps::CacheUse::read_write);
  }, false, totals);
  auto both = request(ps::Policy::committed_input_native_depth); both.constraint = ps::TupleIndexSlotLimit{"13"};
  const auto literal = complete(ps::select(snapshot, source, both, evidence));
  check(assessment(literal, pr::Policy::tuple_index_slots).scores()[0].slots == "13" &&
      assessment(literal, pr::Policy::committed_input_native_depth).scores()[0].numerator == "4" &&
      assessment(literal, pr::Policy::committed_input_native_depth).scores()[0].denominator == "4",
      "C05 normalized literal constraint/depth oracle");
  sweep("C05 normalized two assessments", snapshot, owner, source, evidence, [&](ps::PlanCache& cache) {
    return ps::select(snapshot, source, both, evidence, &cache, ps::CacheUse::read_write);
  }, false, totals);
  sweep("C05 normalized actual current publication", snapshot, owner, source, evidence, [&](ps::PlanCache& cache) {
    return rs::select_current(snapshot, source, owner, both, {}, &cache, ps::CacheUse::read_write);
  }, false, totals);
  check(totals.publication_failures != 0 && totals.assessment_failures != 0 && totals.lowering_failures != 0,
      "C05 normalized fault sweep missed lower/assessment/publication");
  std::cout << "C05 normalized persistent positions=" << totals.positions << " recovered_cleanup_positions=" << totals.recovered
      << "; owned replay/source/identity/cache/late wrapper preserved\n";
} catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; } }
