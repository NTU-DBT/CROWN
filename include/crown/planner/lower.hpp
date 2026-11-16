#pragma once

#include "crown/ir/physical.hpp"
#include "crown/io/normalization.hpp"

namespace crown::planner {
// Limits count selected checkpoints; replay, validation, copies, JSON/hash
// and allocator costs remain separate. Factories propagate existing errors.
// Each factory independently validates actual inputs; a mutable validation
// report/boolean is never accepted as authority. Low-level supplied-tree
// lowering establishes an upper bound, not a minimum-height selection policy.
[[nodiscard]] PhysicalPlan lower_tree(const Catalog& catalog, const Query& query, const FreeConnexTree& tree, const PhysicalOptions& options = {}, const std::optional<PhysicalLimits>& host_limits = {});
// Replays the complete program, grounds legacy v1 to v2, then validates the
// tree against that grounded core. Constant-false plans require an empty tree.
[[nodiscard]] PhysicalPlan lower_normalized(const frontend::NormalizedSql& program, const FreeConnexTree& tree, const PhysicalOptions& options = {}, const io::ProgramReadLimits& program_limits = {}, const std::optional<PhysicalLimits>& host_limits = {});
}  // namespace crown::planner
