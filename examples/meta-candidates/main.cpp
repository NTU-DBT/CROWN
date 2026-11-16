#include "crown/planner/meta_candidates.hpp"
#include "crown/io/candidates.hpp"
#include <iostream>
#include <stdexcept>

// Boolean R(x),S(y): ordinary rooted trees have height2, whereas the empty
// generalized root gives height1. The original exact proof supplies authority.
int main() {
  try {
    using namespace crown;
    Catalog catalog;
    catalog.tables = {{"R",{{"x",ScalarType::int64}}},{"S",{{"y",ScalarType::int64}}}};
    Query query;
    query.variables = {{"x",ScalarType::int64},{"y",ScalarType::int64}};
    query.atoms = {{"r",TableId{0},{VariableId{0}}},{"s",TableId{1},{VariableId{1}}}};
    auto exact = planner::ExactSearch::create(catalog,query);
    if (exact.advance({1'000'000,{}}).progress.result != planner::ResultKind::verified_optimum || !exact.optimum())
      throw std::runtime_error("the example's original exact proof did not complete");
    auto prepared = planner::meta::prepare_meta_candidates(*exact.optimum());
    if (!prepared.provider || prepared.normalized_minimum_family_exhausted())
      throw std::runtime_error("preparation and checked admission were confused");
    bool exhausted = false;
    for (std::size_t i = 0; i < 1000; ++i) {
      const auto stop = prepared.provider->advance({1'000'000,{}}).stopped_for;
      if (stop == planner::CandidateStop::exhausted) { exhausted = true; break; }
      if (stop != planner::CandidateStop::candidate_ready && stop != planner::CandidateStop::quantum_work)
        throw std::runtime_error("mapped candidate admission stopped unexpectedly");
    }
    if (!exhausted || !prepared.normalized_minimum_family_exhausted() || prepared.provider->candidate_count() != 1)
      throw std::runtime_error("the normalized minimum family did not complete");
    const auto candidate = *prepared.provider->candidate(0);
    io::Json report{{"artifact","meta_candidate_example"},{"schema_version",1},
        {"ordinary_rooted_trees",prepared.report.rooted_ordinary_trees},
        {"all_ordinary_roots_materialized",prepared.report.all_ordinary_roots_materialized},
        {"ordinary_undirected_trees",prepared.report.undirected_trees},
        {"ordinary_family_exhausted",prepared.report.ordinary_exhausted},
        {"mapped_input_fibers_exhausted",prepared.report.mapped_input_fibers_exhausted},
        {"normalized_minimum_family_exhausted",prepared.normalized_minimum_family_exhausted()},
        {"heuristic_used",prepared.report.heuristic_used},{"global_cost_optimal",false},
        {"family_scope",std::string(prepared.report.scope)},{"cost_scope",std::string(prepared.report.cost_scope)},
        {"candidate",io::write_minimum_height_candidate(candidate)}};
    std::cout << report.dump(2) << '\n'; std::cout.flush();
    return std::cout ? 0 : 1;
  } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
