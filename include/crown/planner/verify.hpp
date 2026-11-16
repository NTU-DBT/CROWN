#pragma once

#include "crown/ir/tree.hpp"

namespace crown::planner {
struct PlanViolation {
  std::string rule;
  std::string message;
  std::optional<NodeId> node;
  std::optional<VariableId> variable;
  std::optional<std::size_t> occurrence;
  std::optional<NodeId> related_node;
};
struct ValidationReport {
  bool valid = false;
  std::optional<std::size_t> native_height;
  std::optional<std::size_t> edge_depth;
  std::vector<NodeId> maximal_connex;
  std::vector<VariableSet> separators;
  std::vector<PlanViolation> violations;
};

// Independent of tree constructors, GYO, search pruning and runtime helpers.
// A successful report establishes validity and an upper bound, not optimality.
[[nodiscard]] ValidationReport validate_tree(const Catalog& catalog, const Query& query, const FreeConnexTree& tree);
}  // namespace crown::planner
