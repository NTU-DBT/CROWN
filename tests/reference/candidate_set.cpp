#include "candidate_set.hpp"

#include "crown/planner/verify.hpp"

#include <algorithm>
#include <limits>
#include <new>
#include <set>
#include <stdexcept>
#include <utility>

namespace crown::reference {
namespace {

struct StopRequest {
  NormalFormCollectionStop reason;
};

struct Edge {
  std::size_t first;
  std::size_t second;
};

struct RootedShape {
  std::vector<std::vector<std::size_t>> children;
  std::size_t native_height = 0;
};

template <class Charge>
[[nodiscard]] std::string signature_node(const FreeConnexTree& tree, NodeId id, Charge& charge) {
  charge();
  const auto& node = tree.nodes[id.value];
  std::vector<std::string> child_signatures;
  child_signatures.reserve(node.children.size());
  for (const auto child : node.children) {
    child_signatures.push_back(signature_node(tree, child, charge));
  }
  std::sort(child_signatures.begin(), child_signatures.end(), [&charge](const std::string& left,
                                                                        const std::string& right) {
    charge();
    return left < right;
  });

  std::string encoded = "node{kind=";
  encoded += node.kind == NodeKind::native ? "native" : "generalized";
  encoded += ";occurrence=";
  if (node.occurrence) {
    encoded += "some:";
    encoded += std::to_string(*node.occurrence);
  } else {
    encoded += "none";
  }
  encoded += ";scope[";
  encoded += std::to_string(node.scope.size());
  encoded += "]=[";
  for (auto variable = node.scope.begin(); variable != node.scope.end(); ++variable) {
    charge();
    if (variable != node.scope.begin()) encoded += ',';
    encoded += std::to_string(variable->value);
  }
  encoded += ";children[";
  encoded += std::to_string(child_signatures.size());
  encoded += "]={";
  for (const auto& child : child_signatures) {
    charge();
    encoded += std::to_string(child.size());
    encoded += '#';
    encoded += child;
  }
  encoded += "}}";
  return encoded;
}

template <class Charge>
[[nodiscard]] std::string make_reference_signature(const FreeConnexTree& tree, Charge& charge) {
  if (!tree.root) return "NFREF1<EMPTY:0>";
  auto root_signature = signature_node(tree, *tree.root, charge);
  std::string result_signature = "NFREF1<ROOT:";
  result_signature += std::to_string(root_signature.size());
  result_signature += '#';
  result_signature += root_signature;
  result_signature += '>';
  return result_signature;
}

struct Collector {
  const Catalog& catalog;
  const Query& query;
  std::size_t requested_height;
  NormalFormCollectionLimits limits;
  NormalFormCollectionResult result;
  std::vector<VariableSet> native_scopes;
  std::vector<VariableSet> scope_universe;

  Collector(const Catalog& source_catalog, const Query& source_query,
            std::size_t source_height, NormalFormCollectionLimits source_limits)
      : catalog(source_catalog), query(source_query), requested_height(source_height),
        limits(source_limits) {}

  void charge() {
    if (result.work_units == std::numeric_limits<std::uint64_t>::max()) {
      throw StopRequest{NormalFormCollectionStop::work_counter_overflow};
    }
    if (result.work_units >= limits.max_work_units) {
      throw StopRequest{NormalFormCollectionStop::work_limit};
    }
    ++result.work_units;
  }

  void initialize_native_scopes() {
    if (query.atoms.size() > normal_form_reference_native_cap) {
      throw StopRequest{NormalFormCollectionStop::native_occurrence_cap};
    }

    native_scopes.reserve(query.atoms.size());
    VariableSet active_variables;
    for (const auto& atom : query.atoms) {
      charge();
      VariableSet scope;
      for (const auto& term : atom.terms) {
        charge();
        if (const auto* variable = std::get_if<VariableId>(&term)) {
          scope.insert(*variable);
          active_variables.insert(*variable);
          if (active_variables.size() > normal_form_reference_active_variable_cap) {
            throw StopRequest{NormalFormCollectionStop::active_variable_cap};
          }
        }
      }
      native_scopes.push_back(std::move(scope));
    }
  }

  void collect_subsets(const std::vector<VariableId>& variables, std::size_t position,
                       VariableSet& current, std::set<VariableSet>& unique) {
    charge();
    if (position == variables.size()) {
      unique.insert(current);
      return;
    }
    collect_subsets(variables, position + 1, current, unique);
    current.insert(variables[position]);
    collect_subsets(variables, position + 1, current, unique);
    current.erase(variables[position]);
  }

  void build_scope_universe() {
    std::set<VariableSet> unique;
    for (const auto& native_scope : native_scopes) {
      std::vector<VariableId> variables(native_scope.begin(), native_scope.end());
      VariableSet current;
      collect_subsets(variables, 0, current, unique);
    }
    scope_universe.assign(unique.begin(), unique.end());
  }

  [[nodiscard]] std::vector<Edge> decode_prufer(std::size_t node_count,
                                                 const std::vector<std::size_t>& code) {
    std::vector<Edge> edges;
    if (node_count == 1) return edges;
    if (node_count == 2) {
      charge();
      edges.push_back({0, 1});
      return edges;
    }

    std::vector<std::size_t> degree(node_count, 1);
    for (const auto label : code) {
      charge();
      ++degree[label];
    }

    edges.reserve(node_count - 1);
    for (const auto label : code) {
      std::size_t leaf = node_count;
      for (std::size_t candidate = 0; candidate < node_count; ++candidate) {
        charge();
        if (degree[candidate] == 1) {
          leaf = candidate;
          break;
        }
      }
      if (leaf == node_count) throw std::logic_error("invalid Prüfer sequence state");
      edges.push_back({leaf, label});
      --degree[leaf];
      --degree[label];
    }

    std::size_t first_leaf = node_count;
    std::size_t second_leaf = node_count;
    for (std::size_t label = 0; label < node_count; ++label) {
      charge();
      if (degree[label] != 1) continue;
      if (first_leaf == node_count) first_leaf = label;
      else second_leaf = label;
    }
    if (second_leaf == node_count) throw std::logic_error("incomplete Prüfer sequence state");
    edges.push_back({first_leaf, second_leaf});
    return edges;
  }

  [[nodiscard]] bool advance_prufer(std::vector<std::size_t>& code, std::size_t base) {
    for (std::size_t position = code.size(); position > 0; --position) {
      charge();
      auto& digit = code[position - 1];
      if (digit + 1 < base) {
        ++digit;
        return true;
      }
      digit = 0;
    }
    return false;
  }

  [[nodiscard]] RootedShape orient(const std::vector<Edge>& edges, std::size_t node_count,
                                   std::size_t root) {
    std::vector<std::vector<std::size_t>> adjacency(node_count);
    for (const auto& edge : edges) {
      charge();
      adjacency[edge.first].push_back(edge.second);
      adjacency[edge.second].push_back(edge.first);
    }
    for (auto& neighbors : adjacency) std::sort(neighbors.begin(), neighbors.end());

    RootedShape shape;
    shape.children.resize(node_count);
    std::vector<std::size_t> parent(node_count, node_count);
    std::vector<std::size_t> order;
    order.reserve(node_count);
    parent[root] = root;
    order.push_back(root);
    for (std::size_t cursor = 0; cursor < order.size(); ++cursor) {
      const auto node = order[cursor];
      for (const auto neighbor : adjacency[node]) {
        charge();
        if (neighbor == parent[node]) continue;
        if (parent[neighbor] != node_count) throw std::logic_error("Prüfer decoder did not produce a tree");
        parent[neighbor] = node;
        shape.children[node].push_back(neighbor);
        order.push_back(neighbor);
      }
    }
    if (order.size() != node_count) throw std::logic_error("Prüfer tree is disconnected");

    std::vector<std::size_t> native_depth(node_count, 0);
    native_depth[root] = root < native_scopes.size() ? 1 : 0;
    shape.native_height = native_depth[root];
    for (std::size_t cursor = 0; cursor < order.size(); ++cursor) {
      const auto node = order[cursor];
      for (const auto child : shape.children[node]) {
        charge();
        native_depth[child] = native_depth[node] + (child < native_scopes.size() ? 1U : 0U);
        shape.native_height = std::max(shape.native_height, native_depth[child]);
      }
    }
    return shape;
  }

  [[nodiscard]] bool is_normal_form(const RootedShape& shape, std::size_t native_count) {
    for (std::size_t node = 0; node < shape.children.size(); ++node) {
      charge();
      const bool generalized = node >= native_count;
      if (shape.children[node].empty() && generalized) return false;
      if (generalized && shape.children[node].size() < 2) return false;
      if (!generalized) {
        for (const auto child : shape.children[node]) {
          charge();
          if (child >= native_count) return false;
        }
      }
    }
    return shape.native_height == requested_height;
  }

  [[nodiscard]] FreeConnexTree make_tree(const RootedShape& shape, std::size_t root,
                                          const std::vector<VariableSet>& generalized_scopes) {
    const auto native_count = native_scopes.size();
    FreeConnexTree tree;
    tree.root = NodeId{root};
    tree.nodes.reserve(shape.children.size());
    for (std::size_t label = 0; label < shape.children.size(); ++label) {
      charge();
      const bool native = label < native_count;
      TreeNode node;
      node.id = "reference-node-" + std::to_string(label);
      node.kind = native ? NodeKind::native : NodeKind::generalized;
      node.scope = native ? native_scopes[label] : generalized_scopes[label - native_count];
      if (native) node.occurrence = label;
      for (const auto child : shape.children[label]) {
        charge();
        node.children.push_back(NodeId{child});
      }
      tree.nodes.push_back(std::move(node));
    }
    return tree;
  }

  [[nodiscard]] std::string structural_signature(const FreeConnexTree& tree) {
    auto meter = [this] { charge(); };
    return ::crown::reference::make_reference_signature(tree, meter);
  }

  void consider(FreeConnexTree tree) {
    charge();
    const auto report = planner::validate_tree(catalog, query, tree);
    if (!report.valid || !report.native_height || *report.native_height != requested_height) return;

    // Claims are copied only from this successful P02 report. They are not
    // part of the reference signature, and the checker saw no caller claims.
    tree.claimed_native_height = report.native_height;
    tree.claimed_connex = report.maximal_connex;
    auto signature = structural_signature(tree);
    for (const auto& existing : result.plans) {
      charge();
      if (existing.signature == signature) return;
    }
    charge();
    result.plans.push_back({std::move(signature), std::move(tree)});
  }

  void assign_generalized_scopes(const RootedShape& shape, std::size_t root,
                                 std::size_t generalized_count,
                                 std::vector<VariableSet>& assignment,
                                 std::size_t position) {
    charge();
    if (position == generalized_count) {
      consider(make_tree(shape, root, assignment));
      return;
    }
    for (const auto& scope : scope_universe) {
      charge();
      assignment[position] = scope;
      assign_generalized_scopes(shape, root, generalized_count, assignment, position + 1);
    }
  }

  void consider_rooted_topology(const std::vector<Edge>& edges, std::size_t node_count,
                                std::size_t root, std::size_t generalized_count) {
    charge();
    const auto shape = orient(edges, node_count, root);
    if (!is_normal_form(shape, native_scopes.size())) return;

    if (generalized_count == 0) {
      consider(make_tree(shape, root, {}));
      return;
    }
    std::vector<VariableSet> assignment(generalized_count);
    assign_generalized_scopes(shape, root, generalized_count, assignment, 0);
  }

  void enumerate_generalized_count(std::size_t generalized_count) {
    const auto native_count = native_scopes.size();
    if (generalized_count > std::numeric_limits<std::size_t>::max() - native_count) {
      throw StopRequest{NormalFormCollectionStop::container_limit};
    }
    const auto node_count = native_count + generalized_count;
    if (node_count == 0) throw std::logic_error("empty body must use its dedicated branch");

    std::vector<std::size_t> code(node_count > 2 ? node_count - 2 : 0, 0);
    bool more_codes = true;
    while (more_codes) {
      charge();
      const auto edges = decode_prufer(node_count, code);
      for (std::size_t root = 0; root < node_count; ++root) {
        charge();
        consider_rooted_topology(edges, node_count, root, generalized_count);
      }
      more_codes = advance_prufer(code, node_count);
    }
  }

  void collect_empty_body() {
    FreeConnexTree empty;
    consider(std::move(empty));
    result.exhausted = true;
  }

  void run() {
    initialize_native_scopes();
    if (native_scopes.empty()) {
      collect_empty_body();
      return;
    }
    if (native_scopes.size() > 1) build_scope_universe();
    for (std::size_t generalized_count = 0; generalized_count < native_scopes.size();
         ++generalized_count) {
      charge();
      enumerate_generalized_count(generalized_count);
    }
    result.exhausted = true;
  }
};

}  // namespace

std::string normal_form_reference_signature(const FreeConnexTree& checked_tree) {
  const auto no_charge = [] {};
  return make_reference_signature(checked_tree, no_charge);
}

NormalFormCollectionResult collect_normal_form_plan_set(
    const Catalog& catalog, const Query& query, std::size_t supplied_native_height,
    NormalFormCollectionLimits limits) {
  Collector collector{catalog, query, supplied_native_height, limits};
  try {
    collector.run();
  } catch (const StopRequest& stopped) {
    collector.result.exhausted = false;
    collector.result.resource_limited = true;
    collector.result.stop = stopped.reason;
  } catch (const std::bad_alloc&) {
    collector.result.exhausted = false;
    collector.result.resource_limited = true;
    collector.result.stop = NormalFormCollectionStop::allocation_failure;
  } catch (const std::length_error&) {
    collector.result.exhausted = false;
    collector.result.resource_limited = true;
    collector.result.stop = NormalFormCollectionStop::container_limit;
  }
  return std::move(collector.result);
}

}  // namespace crown::reference
