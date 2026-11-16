#pragma once

#include "crown/io/document.hpp"
#include "crown/planner/verify.hpp"

namespace crown::io {
[[nodiscard]] FreeConnexTree read_tree(std::string_view text, const Catalog& catalog, const Query& query);
[[nodiscard]] Json write_tree(const FreeConnexTree& tree, const Catalog& catalog, const Query& query);
[[nodiscard]] Json write_validation(const planner::ValidationReport& report, const FreeConnexTree& tree, const Query& query);
}  // namespace crown::io
