#include "ranking_fixture.hpp"
#include "crown/planner/selection.hpp"
#include <iostream>

int main() { try {
  using namespace c02_test; namespace ps = planner::selection;
  const auto f = c02_test::fixture(); const auto snapshot = c02_test::candidates(f);
  auto cache = ps::PlanCache::create(); const ps::Source source = ps::DirectCQ{};
  ps::Request request; request.policy = ps::Policy::height_only;
  const auto first = ps::select(snapshot, source, request, {}, &cache, ps::CacheUse::read_write);
  const auto second = ps::select(snapshot, source, request, {}, &cache, ps::CacheUse::read_only);
  check(first.selection && second.selection, "C05 pure selection failed");
  const auto& cold = *first.selection; const auto& warm = *second.selection;
  check(warm.cache_observation().disposition == ps::CacheDisposition::hit && warm.usage().lowering_work == 0 &&
      warm.cache_binding() == cold.cache_binding() && warm.selected().structural_key() == cold.selected().structural_key(),
      "C05 pure cache reuse failed");
  check(cold.evidence_use() == ps::EvidenceUse::absent && cold.plan().guarantee().height_status == "valid_upper_bound",
      "C05 pure link manufactured runtime/proof authority");
  std::cout << "C05 pure selection link without runtime/report passed\n";
} catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; } }
