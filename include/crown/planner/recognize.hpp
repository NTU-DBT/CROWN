#pragma once

#include "crown/ir/model.hpp"
#include <optional>
#include <set>
#include <vector>

namespace crown::planner {
using Scope = std::set<VariableId>;
enum class ReductionKind { private_variable, contained_edge, empty_edge };
struct ReductionStep {
  ReductionKind kind;
  std::size_t edge;
  std::optional<std::size_t> anchor;
  std::optional<VariableId> variable;
};
struct ResidualEdge { std::size_t edge; Scope scope; };
struct GyoResult {
  bool acyclic;
  std::vector<ReductionStep> witness;
  std::vector<ResidualEdge> failed_core;
};
enum class QueryClass { free_connex, acyclic_non_free_connex, cyclic };
struct StructuralAnalysis { QueryClass query_class; GyoResult body; GyoResult augmented; };
// Caps explicit recognition checkpoints after catalog/query validation; it is not a byte or elapsed-time limit.
struct RecognitionLimits { std::optional<std::uint64_t> work_limit = 1000000; };
struct RecognitionRun {
  std::optional<StructuralAnalysis> analysis;  // Absent on resource exhaustion.
  std::uint64_t work = 0;
};

// Scope reduction never removes occurrences from the actual query IR.
[[nodiscard]] GyoResult gyo_reduce(const std::vector<Scope>& scopes);
[[nodiscard]] StructuralAnalysis analyze(const Catalog& catalog, const Query& query);
[[nodiscard]] RecognitionRun analyze_bounded(const Catalog& catalog, const Query& query, RecognitionLimits limits = {});
}  // namespace crown::planner
