#pragma once

#include "crown/planner/lower.hpp"

namespace crown::io {
[[nodiscard]] Json write_physical_options(const PhysicalOptions& options);
[[nodiscard]] PhysicalOptions read_physical_options(std::string_view text);
// Canonical owned compile input, excluding initial rows and update streams.
[[nodiscard]] Json write_physical_source(const Catalog& catalog, const Query& query, const std::optional<frontend::NormalizedSql>& normalized);
[[nodiscard]] Json write_physical(const PhysicalPlan& plan);
// Explicit caller DTO export for serializing an immutable native compiler
// program. This delegates to the unchanged PhysicalPlan serializer.
[[nodiscard]] Json write_physical(const CompiledProgram& plan);
struct PhysicalReadLimits {
  PhysicalLimits lowering;
  ProgramReadLimits program;
};
// Rebuilds every program from owned source/query/tree and compares the complete
// artifact. Host caps are independent of stored producer limits; no imported
// tree_valid/height/guarantee flag or compiled slot is trusted.
[[nodiscard]] PhysicalPlan read_physical(std::string_view text, const PhysicalReadLimits& limits = {});
}  // namespace crown::io
