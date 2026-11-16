#pragma once

#include "crown/io/search.hpp"
#include "crown/planner/residual.hpp"

namespace crown::io {
// Allocating report serialization is outside residual advance quanta. The
// overloads accept immutable checked artifacts or the live owner so JSON fields
// cannot be used to manufacture proof authority.
[[nodiscard]] Json write_residual_trace(const planner::ResidualTrace&);
[[nodiscard]] Json write_residual_candidate(const planner::ResidualCandidate&);
[[nodiscard]] Json write_residual_progress(const planner::ResidualSearch&);
}  // namespace crown::io
