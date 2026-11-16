#pragma once
#include "ranking_detail.hpp"

namespace crown::planner::ranking::detail {
// Logical owned component payload, not allocator capacity or a peak bound.
// Immutable caller-owned handles are borrowed; every newly lowered plan is
// admitted separately, even when its source text equals a previous plan's.
void plan_source_payload(const MinimumHeightCandidate&,const PhysicalPlan&,Budget&);
void plan_compiled_payload(const PhysicalPlan&,Budget&);
} // namespace crown::planner::ranking::detail
