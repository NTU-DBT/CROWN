#pragma once

#include "crown/io/document.hpp"
#include "crown/planner/recognize.hpp"

namespace crown::io {
[[nodiscard]] Json write_structural_analysis(const planner::StructuralAnalysis& analysis, const Query& query);
}  // namespace crown::io
