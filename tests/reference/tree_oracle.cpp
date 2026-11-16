#include "tree_oracle.hpp"

#include "crown/api/error.hpp"
#include "crown/planner/verify.hpp"
#include "../../src/planner/search_budget.hpp"
#include <algorithm>
#include <functional>
#include <numeric>
#include <new>

namespace crown::reference {
planner::OracleResult exhaustive_minimum_tree(const Catalog& catalog, const Query& query, const planner::SearchLimits& limits) {
  validate(catalog, query);
  planner::detail::WorkBudget budget(limits);
  planner::OracleResult result;
  result.algorithm = "literal_normal_form_v1";
  result.limits = limits;
  const auto m = query.atoms.size();
  std::vector<VariableSet> native_scopes;
  try {
    budget.charge();
    for (const auto& atom : query.atoms) {
      budget.charge();
      VariableSet scope;
      for (const auto& term : atom.terms) if (const auto* variable = std::get_if<VariableId>(&term)) scope.insert(*variable);
      native_scopes.push_back(std::move(scope));
    }
    if (m == 0) {
      result.status = planner::OracleStatus::proven_minimum;
      result.minimum_height = 0;
      result.tree = FreeConnexTree{};
    } else {
      std::optional<std::vector<VariableSet>> universe;
      const auto scopes = [&]() -> const std::vector<VariableSet>& {
        if (!universe) {
          std::set<VariableSet> unique;
          for (const auto& native : native_scopes) {
            std::vector<VariableId> variables(native.begin(), native.end());
            VariableSet current;
            std::function<void(std::size_t)> visit = [&](std::size_t position) {
              auto frame = budget.frame();
              if (position == variables.size()) {
                unique.insert(current);
                if (limits.literal_scope_limit && unique.size() > *limits.literal_scope_limit) throw planner::detail::SearchStopped("literal scope materialization limit reached");
              } else {
                visit(position + 1);
                current.insert(variables[position]);
                visit(position + 1);
                current.erase(variables[position]);
              }
            };
            visit(0);
          }
          universe.emplace(unique.begin(), unique.end());
        }
        return *universe;
      };
      for (std::size_t bound = 1; bound <= m && !result.tree; ++bound) {
        for (std::size_t generalized = 0; generalized < m && !result.tree; ++generalized) {
          budget.charge();
          const auto count = m + generalized;
          if (count < m) throw planner::detail::SearchStopped("normal-form node count exceeds platform range");
          if (generalized != 0) static_cast<void>(scopes());
          for (std::size_t root = 0; root < count && !result.tree; ++root) {
            std::vector<std::size_t> parent(count, root);
            std::function<bool(std::size_t)> topology = [&](std::size_t position) {
              auto frame = budget.frame();
              if (position < count) {
                if (position == root) return topology(position + 1);
                for (std::size_t candidate = 0; candidate < count; ++candidate) {
                  if (candidate == position) continue;
                  parent[position] = candidate;
                  if (topology(position + 1)) return true;
                }
                return false;
              }
              FreeConnexTree tree{NodeId{root}, {}, {}, {}};
              for (std::size_t i = 0; i < count; ++i) {
                tree.nodes.push_back({"node" + std::to_string(i), i < m ? NodeKind::native : NodeKind::generalized,
                                      i < m ? native_scopes[i] : VariableSet{}, {}, i < m ? std::optional<std::size_t>{i} : std::nullopt, {}});
              }
              for (std::size_t i = 0; i < count; ++i) if (i != root) tree.nodes[parent[i]].children.push_back(NodeId{i});
              for (std::size_t i = m; i < count; ++i) if (tree.nodes[i].children.size() < 2) return false;
              for (std::size_t i = 0; i < count; ++i) {
                std::size_t current = i;
                std::size_t native_height = i < m ? 1 : 0;
                std::size_t length = 0;
                while (current != root && length < count) {
                  const auto above = parent[current];
                  if (current >= m && above < m) return false;
                  current = above;
                  native_height += current < m ? 1U : 0U;
                  ++length;
                }
                if (current != root || native_height > bound) return false;
              }
              std::function<bool(std::size_t)> labels = [&](std::size_t i) {
                auto label_frame = budget.frame();
                if (i == count) {
                  ++budget.statistics.candidates;
                  const auto report = planner::validate_tree(catalog, query, tree);
                  if (!report.valid || *report.native_height > bound) return false;
                  tree.claimed_native_height = report.native_height;
                  tree.claimed_connex = report.maximal_connex;
                  result.tree = tree;
                  result.minimum_height = report.native_height;
                  return true;
                }
                for (const auto& scope : scopes()) { tree.nodes[i].scope = scope; if (labels(i + 1)) return true; }
                return false;
              };
              return labels(m);
            };
            static_cast<void>(topology(0));
          }
        }
      }
      result.status = result.tree ? planner::OracleStatus::proven_minimum : planner::OracleStatus::unsupported;
    }
  } catch (const planner::detail::SearchStopped& stopped) {
    result.status = planner::OracleStatus::resource_limit;
    result.reason = stopped.what();
    result.tree.reset(); result.minimum_height.reset();
  } catch (const std::bad_alloc&) {
    result.status = planner::OracleStatus::resource_limit;
    result.tree.reset(); result.minimum_height.reset();
    result.reason = "literal search allocation failed";
  }
  result.statistics = budget.statistics;
  return result;
}
}  // namespace crown::reference
