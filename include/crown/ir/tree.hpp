#pragma once

#include "crown/ir/model.hpp"
#include <optional>

namespace crown {
using VariableSet = std::set<VariableId>;
enum class NodeKind { native, generalized };
// This aggregate records proposed structure; validate_tree checks its references,
// scopes, occurrence rules, topology, and claimed separator before acceptance.
struct TreeNode {
  std::string id;
  NodeKind kind;
  VariableSet scope;
  std::vector<NodeId> children;
  std::optional<std::size_t> occurrence;
  std::optional<VariableSet> claimed_separator;
};
// This aggregate carries optional claims; validate_tree checks them and reports
// a valid upper bound, not proof that the supplied tree has minimum height.
struct FreeConnexTree {
  std::optional<NodeId> root;
  std::vector<TreeNode> nodes;
  std::optional<std::vector<NodeId>> claimed_connex;
  std::optional<std::size_t> claimed_native_height;
};
}  // namespace crown
