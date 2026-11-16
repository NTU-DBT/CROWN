#include "selection_exception_support.hpp"

int main() { try {
  using namespace c05_fault;
  const auto f = c02_test::fixture(); const auto snapshot = c02_test::candidates(f);
  const auto plan = planner::lower_tree(f.catalog, f.query, snapshot.candidate(0)->tree());
  auto owner = runtime::PhysicalRuntime::initialize(plan, f.database); heat(owner, f);
  const auto update = [&](SetOperation operation, Row row) {
    static_cast<void>(owner.apply({owner.sequence() + 1, TableId{0}, operation, std::move(row)}));
  };
  update(SetOperation::insert, Row{std::int64_t{2}}); update(SetOperation::erase, Row{std::int64_t{2}});
  update(SetOperation::erase, Row{std::int64_t{3}});
  const auto evidence = capture(snapshot, owner).inputs(); const ps::Source source = ps::DirectCQ{};
  check(owner.canonical_state().sources == f.database.tables && evidence.denominator() == 103 &&
      evidence.weights()[0].changed == 2 && evidence.weights()[0].noop == 91,
      "C05 fault setup lacks changed/erase/no-op census");
  Totals totals;
  for (const auto policy : {ps::Policy::height_only, ps::Policy::committed_input_native_depth, ps::Policy::tuple_index_slots}) {
    const auto selection_request = request(policy);
    sweep("C05 pure policy", snapshot, owner, source, evidence, [&](ps::PlanCache& cache) {
      return ps::select(snapshot, source, selection_request,
          policy == ps::Policy::height_only ? std::optional<pr::Evidence>{} : evidence, &cache, ps::CacheUse::read_write);
    }, false, totals);
  }
  auto both = request(ps::Policy::committed_input_native_depth); both.constraint = ps::TupleIndexSlotLimit{"31"};
  sweep("C05 pure dual assessment", snapshot, owner, source, evidence, [&](ps::PlanCache& cache) {
    return ps::select(snapshot, source, both, evidence, &cache, ps::CacheUse::read_write);
  }, false, totals);
  const auto height = request(ps::Policy::height_only);
  sweep("C05 warm pure artifact", snapshot, owner, source, evidence, [&](ps::PlanCache& cache) {
    return ps::select(snapshot, source, height, evidence, &cache, ps::CacheUse::read_write);
  }, true, totals);
  sweep("C05 current height late wrapper", snapshot, owner, source, evidence, [&](ps::PlanCache& cache) {
    return rs::select_current(snapshot, source, owner, height, {}, &cache, ps::CacheUse::read_write);
  }, false, totals);
  sweep("C05 current dual assessment late wrapper", snapshot, owner, source, evidence, [&](ps::PlanCache& cache) {
    return rs::select_current(snapshot, source, owner, both, {}, &cache, ps::CacheUse::read_write);
  }, false, totals);
  check(totals.publication_failures != 0 && totals.assessment_failures != 0 && totals.lowering_failures != 0,
      "C05 full fault sweep missed a required phase");
  std::cout << "C05 persistent positions=" << totals.positions << " recovered_cleanup_positions=" << totals.recovered
      << " publication_failures=" << totals.publication_failures << "; complete owner/workload/cache/old results preserved\n";
} catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; } }
