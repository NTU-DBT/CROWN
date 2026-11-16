#pragma once
#include "crown/runtime/ranking_evidence.hpp"
#include "../planner/ranking_detail.hpp"
namespace crown::runtime::ranking::detail {
// Private classifier seam for isolated boundary tests. It returns numeric
// observations only and cannot manufacture public actual-owner Evidence.
struct Census {pr::Reasons reasons{};std::uint64_t total{};std::vector<pr::InputWeight> weights;};
Census classify_census(const workload::Snapshot&,::crown::planner::ranking::detail::Budget&);
}
