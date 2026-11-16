#pragma once

#include "crown/planner/residual.hpp"

namespace crown::reference {

// Literal, test-only replay of the frozen-ear definition. This computes the
// round relation from Query terms and sets; it does not call planner internals.
[[nodiscard]] planner::ResidualTraceRecord frozen_residual_trace(const Query& query);

}  // namespace crown::reference
