#pragma once

#include "crown/planner/update_pattern.hpp"
#include "ranking_detail.hpp"

namespace crown::planner::patterns::detail {
namespace rd = ::crown::planner::ranking::detail;
inline constexpr resource::MemoryAttribution owner{resource::MemoryOwnerKind::capture, 16};
template<class T> resource::OwnerAllocator<T> allocator(const resource::MemoryAccount& account,
    resource::MemoryPurpose purpose = resource::MemoryPurpose::capture) {
  return resource::OwnerAllocator<T>(account, purpose, owner);
}
Analysis analyse(const resource::MemoryAccount&, const CompiledProgram&, const MinimumHeightCandidate&,
    const Declaration&, rd::Budget&);
// Selection already checked full snapshot/source binding and the declaration
// once. Reuse that invariant instead of reserializing the source per candidate.
Analysis analyse_bound(const resource::MemoryAccount&, const CompiledProgram&, const MinimumHeightCandidate&,
    const Declaration&, rd::Budget&);
} // namespace crown::planner::patterns::detail
