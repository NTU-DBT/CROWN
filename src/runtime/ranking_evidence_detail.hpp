#pragma once
#include "crown/runtime/ranking_evidence.hpp"
#include "../planner/ranking_detail.hpp"
namespace crown::runtime::ranking::detail {
// Private classifier seam for isolated boundary tests. It returns numeric
// observations only and cannot manufacture public actual-owner Evidence.
struct Census {
  pr::Reasons reasons{};std::uint64_t total{};pr::EvidenceVector<pr::InputWeight> weights;
  explicit Census(const resource::MemoryAccount& account)
      :weights(::crown::planner::ranking::detail::evidence_allocator<pr::InputWeight>(account)) {}
};
Census classify_census(const workload::Snapshot&,::crown::planner::ranking::detail::Budget&);
}
