#include "crown/planner/oracle.hpp"

#include "crown/api/error.hpp"
#include "crown/planner/verify.hpp"
#include "planner_baseline_budget.hpp"
#include <algorithm>
#include <functional>
#include <map>
#include <new>
#include <set>

namespace crown::planner {
namespace {
using Members = std::vector<std::size_t>;

struct Key {
  Members members;
  bool generalized;
  bool reachable;
  auto operator<=>(const Key&) const = default;
};

struct Metadata {
  VariableSet variables;
  VariableSet boundary;
  VariableSet private_head;
};

struct Choice {
  std::optional<std::size_t> height;
  NodeKind kind = NodeKind::native;
  std::optional<std::size_t> occurrence;
  VariableSet scope;
  std::vector<Key> children;
};

// Frozen pre-P06 labelled-state recurrence: every native root and unordered
// sibling partition is explored, with no component split, symmetry orbit,
// incumbent bound, hierarchy path, or shortcut state.
class PartitionSearch {
 public:
  PartitionSearch(const Query& query, baseline_detail::WorkBudget& budget)
      : budget_(budget) {
    for (const auto& atom : query.atoms) {
      budget_.charge();
      VariableSet scope;
      for (const auto& term : atom.terms) {
        budget_.charge();
        if (const auto* variable = std::get_if<VariableId>(&term))
          scope.insert(*variable);
      }
      for (const auto variable : scope) {
        budget_.charge();
        ++total_[variable];
      }
      scopes_.push_back(std::move(scope));
    }
    for (const auto& output : query.head) {
      budget_.charge();
      head_.insert(output.variable);
    }
  }

  const Choice& solve(const Key& key) {
    auto frame = budget_.frame();
    const auto cached = choices_.find(key);
    if (cached != choices_.end()) {
      ++budget_.statistics.cache_hits;
      return cached->second;
    }
    ++budget_.statistics.states;
    Choice best;
    const auto& meta = metadata(key.members);
    if (!key.reachable && !meta.private_head.empty())
      return choices_.emplace(key, std::move(best)).first->second;

    const auto consider = [&](NodeKind kind, std::optional<std::size_t> occurrence,
                              const VariableSet& scope,
                              const std::vector<Members>& blocks) {
      budget_.charge();
      ++budget_.statistics.candidates;
      std::size_t height = 0;
      std::vector<Key> children;
      for (const auto& block : blocks) {
        const auto reachable = key.reachable &&
                               contains_all(head_, metadata(block).boundary);
        Key child{block, kind == NodeKind::generalized, reachable};
        const auto& choice = solve(child);
        if (!choice.height) return;
        height = std::max(height, *choice.height);
        children.push_back(std::move(child));
      }
      if (kind == NodeKind::native) ++height;
      if (!best.height || height < *best.height)
        best = {height, kind, occurrence, scope, std::move(children)};
    };

    for (const auto root : key.members) {
      budget_.charge();
      if (!contains_all(scopes_[root], meta.boundary)) continue;
      Members remaining;
      for (const auto item : key.members) {
        budget_.charge();
        if (item != root) remaining.push_back(item);
      }
      partitions(remaining, [&](const auto& blocks) {
        for (const auto& block : blocks)
          if (!contains_all(scopes_[root], metadata(block).boundary)) return false;
        consider(NodeKind::native, root, scopes_[root], blocks);
        // Height one is the universal nonempty lower bound, so the original
        // v1 search may stop once this exact optimum is found.
        return best.height == 1;
      });
      if (best.height == 1)
        return choices_.emplace(key, std::move(best)).first->second;
    }

    if (key.generalized) {
      partitions(key.members, [&](const auto& blocks) {
        if (blocks.size() < 2) return false;
        VariableSet shared;
        std::map<VariableId, std::size_t> incidence;
        for (const auto& block : blocks)
          for (const auto variable : metadata(block).variables) {
            budget_.charge();
            ++incidence[variable];
          }
        for (const auto& [variable, count] : incidence) {
          budget_.charge();
          if (count >= 2) shared.insert(variable);
        }
        if (!contains_all(shared, meta.boundary)) return false;
        for (const auto& block : blocks)
          if (!contains_all(metadata(block).variables, shared)) return false;
        consider(NodeKind::generalized, {}, shared, blocks);
        return best.height == 1;
      });
    }
    return choices_.emplace(key, std::move(best)).first->second;
  }

  FreeConnexTree build(const Key& root) {
    FreeConnexTree tree;
    std::function<NodeId(const Key&)> append = [&](const Key& key) {
      auto frame = budget_.frame();
      const auto& choice = choices_.at(key);
      for (const auto variable : choice.scope) {
        static_cast<void>(variable);
        budget_.charge();
      }
      const NodeId id{tree.nodes.size()};
      tree.nodes.push_back({"node" + std::to_string(id.value), choice.kind,
                            choice.scope, {}, choice.occurrence, {}});
      for (const auto& child : choice.children) {
        const auto child_id = append(child);
        tree.nodes[id.value].children.push_back(child_id);
      }
      return id;
    };
    tree.root = append(root);
    return tree;
  }

  std::vector<LowerBoundEntry> proof() {
    // Identity keys retain the complete v1 state set and its map order. There
    // is no v2 scope-orbit canonicalization or proof-state transport here.
    std::map<Key, std::optional<std::size_t>> proof_states;
    for (const auto& [key, choice] : choices_) {
      budget_.charge();
      const auto [it, inserted] = proof_states.emplace(key, choice.height);
      if (!inserted && it->second != choice.height)
        throw Error("invalid_search_proof", "duplicate baseline states disagree");
    }
    std::vector<LowerBoundEntry> entries;
    for (const auto& [key, height] : proof_states) {
      budget_.charge();
      for (const auto occurrence : key.members) {
        static_cast<void>(occurrence);
        budget_.charge();
      }
      entries.push_back({key.members, key.generalized, key.reachable, height});
    }
    return entries;
  }

 private:
  bool contains_all(const VariableSet& scope, const VariableSet& required) {
    for (const auto variable : required) {
      budget_.charge();
      if (!scope.contains(variable)) return false;
    }
    return true;
  }

  const Metadata& metadata(const Members& members) {
    budget_.charge();
    const auto found = metadata_.find(members);
    if (found != metadata_.end()) return found->second;
    Metadata value;
    std::map<VariableId, std::size_t> inside;
    for (const auto occurrence : members) {
      budget_.charge();
      for (const auto variable : scopes_[occurrence]) {
        budget_.charge();
        ++inside[variable];
      }
    }
    for (const auto& [variable, count] : inside) {
      budget_.charge();
      value.variables.insert(variable);
      if (count < total_.at(variable))
        value.boundary.insert(variable);
      else if (head_.contains(variable))
        value.private_head.insert(variable);
    }
    return metadata_.emplace(members, std::move(value)).first->second;
  }

  void partitions(const Members& members,
                  const std::function<bool(const std::vector<Members>&)>& accept) {
    std::vector<Members> blocks;
    std::function<bool(std::size_t)> next = [&](std::size_t position) {
      auto frame = budget_.frame();
      if (position == members.size()) {
        ++budget_.statistics.partitions;
        return accept(blocks);
      }
      const auto existing = blocks.size();
      for (std::size_t i = 0; i < existing; ++i) {
        blocks[i].push_back(members[position]);
        const auto stop = next(position + 1);
        blocks[i].pop_back();
        if (stop) return true;
      }
      blocks.push_back({members[position]});
      const auto stop = next(position + 1);
      blocks.pop_back();
      return stop;
    };
    static_cast<void>(next(0));
  }

  baseline_detail::WorkBudget& budget_;
  std::vector<VariableSet> scopes_;
  VariableSet head_;
  std::map<VariableId, std::size_t> total_;
  std::map<Members, Metadata> metadata_;
  std::map<Key, Choice> choices_;
};

OracleResult run_baseline(const Catalog& catalog, const Query& query,
                          const SearchLimits& limits) {
  validate(catalog, query);
  baseline_detail::WorkBudget budget(limits);
  OracleResult result;
  result.algorithm = "crown_partition_exact_v1";
  result.limits = limits;
  try {
    budget.charge();
    if (query.atoms.empty()) {
      result.minimum_height = 0;
      result.tree = FreeConnexTree{};
    } else {
      Members members(query.atoms.size());
      for (std::size_t i = 0; i < members.size(); ++i) {
        budget.charge();
        members[i] = i;
      }
      const Key root{members, true, true};
      PartitionSearch search(query, budget);
      const auto& choice = search.solve(root);
      result.minimum_height = choice.height;
      if (choice.height) result.tree = search.build(root);
      result.lower_bounds = search.proof();
      if (result.tree) {
        budget.charge();
        const auto checked = validate_tree(catalog, query, *result.tree);
        if (!checked.valid || checked.native_height != result.minimum_height)
          throw Error("invalid_search_witness",
                      "exact search produced an invalid tree or mismatched height");
        result.tree->claimed_native_height = checked.native_height;
        result.tree->claimed_connex = checked.maximal_connex;
      }
    }

    // Preserve v1 payload accounting and the strict, independent public replay.
    for (const auto& entry : result.lower_bounds) {
      budget.charge();
      for (const auto occurrence : entry.occurrences) {
        static_cast<void>(occurrence);
        budget.charge();
      }
    }
    if (result.tree) {
      for (const auto& node : result.tree->nodes) {
        budget.charge();
        for (const auto variable : node.scope) {
          static_cast<void>(variable);
          budget.charge();
        }
        for (const auto child : node.children) {
          static_cast<void>(child);
          budget.charge();
        }
      }
    }
    const HeightCertificate certificate{result.algorithm, result.minimum_height,
                                        result.tree, result.lower_bounds};
    const auto checked = verify_height_certificate(catalog, query, certificate, limits);
    result.statistics = budget.statistics;
    result.statistics.certificate_work = checked.work;
    if (checked.resource_limit)
      throw baseline_detail::SearchStopped("certificate replay: " + checked.message);
    if (!checked.valid)
      throw Error("invalid_search_certificate", checked.message);
    result.certificate_verified = true;
    result.status = result.tree ? OracleStatus::proven_minimum : OracleStatus::unsupported;
    result.reason = result.tree
        ? "minimum height and upper witness independently checked"
        : "no admissible CROWN tree exists for this body/head";
  } catch (const baseline_detail::SearchStopped& stopped) {
    result.status = OracleStatus::resource_limit;
    result.reason = stopped.what();
    result.minimum_height.reset();
    result.tree.reset();
    result.lower_bounds.clear();
    result.certificate_verified = false;
    const auto replay_work = result.statistics.certificate_work;
    result.statistics = budget.statistics;
    result.statistics.certificate_work = replay_work;
  } catch (const std::bad_alloc&) {
    result.status = OracleStatus::resource_limit;
    result.minimum_height.reset();
    result.tree.reset();
    std::vector<LowerBoundEntry>{}.swap(result.lower_bounds);
    result.certificate_verified = false;
    result.statistics = budget.statistics;
    result.reason = "exact search allocation failed";
  }
  if (result.statistics.work == 0) result.statistics = budget.statistics;
  return result;
}
}  // namespace

#ifdef CROWN_PLANNER_TESTING
namespace testing {
OracleResult minimum_tree_baseline(const Catalog& catalog, const Query& query,
                                   const SearchLimits& limits) {
  return run_baseline(catalog, query, limits);
}
}  // namespace testing
#endif
}  // namespace crown::planner
