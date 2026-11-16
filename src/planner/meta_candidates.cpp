#include "crown/planner/meta_candidates.hpp"
#include "crown/api/error.hpp"
#include <algorithm>
#include <limits>
#include <utility>

namespace crown::planner::meta {
namespace {
struct Halt { MappingStop stop; };
struct Budget {
  const MetaMappingLimits& limits;
  MetaMappingUsage& usage;
  void step() {
    if (usage.work == limits.work) throw Halt{MappingStop::work_limit};
    ++usage.work;
  }
  void cells(std::size_t count) {
    if (count > limits.cells - usage.cells) throw Halt{MappingStop::cell_limit};
    usage.cells += count;
  }
  void fragment() {
    step();
    if (usage.fragments == limits.fragments) throw Halt{MappingStop::fragment_limit};
    ++usage.fragments;
  }
  void enter(std::size_t depth) {
    step();
    if (depth > limits.depth) throw Halt{MappingStop::depth_limit};
    cells(1); // One admitted logical recursion frame, not stack-byte accounting.
    usage.peak_depth = std::max(usage.peak_depth, depth);
  }
};
template<class T> void append(std::vector<T>& into, T value, Budget& b) {
  b.step(); b.cells(1);
  if (into.size() == into.max_size()) throw Halt{MappingStop::cell_limit};
  into.push_back(std::move(value));
}
void variable(Scope& into, VariableId value, Budget& b) {
  b.step();
  if (!into.contains(value)) { b.cells(1); into.insert(value); }
}
Scope copied(const Scope& from, Budget& b) {
  b.step(); b.cells(from.size()); return from;
}
bool covers(const Scope& large, const Scope& small, Budget& b) {
  auto i = large.begin();
  for (auto v : small) {
    b.step();
    while (i != large.end() && *i < v) { b.step(); ++i; }
    if (i == large.end() || *i != v) return false;
  }
  return true;
}
bool equal(const Scope& a, const Scope& c, Budget& b) {
  b.step(); return a.size() == c.size() && covers(a, c, b);
}
Scope intersection(const Scope& a, const Scope& c, Budget& b) {
  Scope result;
  auto x = a.begin(), y = c.begin();
  while (x != a.end() && y != c.end()) {
    b.step();
    if (*x < *y) ++x;
    else if (*y < *x) ++y;
    else { variable(result, *x, b); ++x; ++y; }
  }
  return result;
}
// Descending dynamic binary subsets: visit the full set first, then every
// other nonempty subset. No machine-word mask or power-set size is computed.
bool previous(std::vector<unsigned char>& digits, Budget& b) {
  for (std::size_t i = digits.size(); i != 0;) {
    b.step(); --i;
    if (digits[i]) {
      digits[i] = 0;
      for (auto bit : digits) { b.step(); if (bit) return true; }
      return false;
    }
    digits[i] = 1;
  }
  return false;
}

struct PrefixNode {
  std::optional<std::size_t> occurrence;
  Scope scope; // Only generalized nodes store a scope; native scopes are shared.
  std::vector<std::size_t> children;
};
struct Prefix { std::vector<PrefixNode> nodes; std::size_t root = 0; };
using Family = std::vector<Prefix>;
struct Branch { std::vector<std::size_t> leaves; Family family; };

class Mapper {
  const Query& query;
  std::size_t required_height;
  MetaCandidateReport& report;
  std::vector<FreeConnexTree>& output;
  Budget budget;
  std::vector<Scope> native;
  std::vector<std::vector<std::size_t>> adjacent;
  std::vector<unsigned char> roots;
  std::vector<std::size_t> native_parent;

  void scopes() {
    budget.step(); budget.cells(query.atoms.size()); native.resize(query.atoms.size());
    for (std::size_t i = 0; i < query.atoms.size(); ++i)
      for (const auto& term : query.atoms[i].terms) {
        budget.step();
        if (const auto* v = std::get_if<VariableId>(&term)) variable(native[i], *v, budget);
      }
  }
  void sort(std::vector<std::size_t>& values) {
    std::sort(values.begin(), values.end(), [&](auto a, auto c) { budget.step(); return a < c; });
  }
  // Parent references are checked before indexing. Connectivity and induced
  // variable edge counts recheck the ordinary input independently of its maker.
  void graph(const JoinTree& tree) {
    const auto n = native.size();
    if (tree.parent.size() != n || tree.root >= n || tree.parent[tree.root] != tree.root)
      throw Halt{MappingStop::invalid_join_tree};
    budget.cells(n); adjacent.assign(n, {});
    for (std::size_t i = 0; i < n; ++i) {
      budget.step();
      if (i == tree.root) continue;
      const auto parent = tree.parent[i];
      if (parent >= n || parent == i) throw Halt{MappingStop::invalid_join_tree};
      append(adjacent[i], parent, budget); append(adjacent[parent], i, budget);
    }
    for (auto& neighbors : adjacent) sort(neighbors);
    budget.cells(n); std::vector<unsigned char> seen(n);
    std::vector<std::size_t> walk; append(walk, tree.root, budget); seen[tree.root] = 1;
    for (std::size_t i = 0; i < walk.size(); ++i)
      for (auto next : adjacent[walk[i]]) {
        budget.step();
        if (!seen[next]) { append(walk, next, budget); seen[next] = 1; }
      }
    if (walk.size() != n) throw Halt{MappingStop::invalid_join_tree};
    for (std::size_t v = 0; v < query.variables.size(); ++v) {
      std::size_t vertices = 0, edges = 0;
      for (std::size_t i = 0; i < n; ++i) {
        budget.step(); const bool has = native[i].contains(VariableId{v});
        vertices += has;
        if (i != tree.root && has && native[tree.parent[i]].contains(VariableId{v})) ++edges;
      }
      if (vertices && edges != vertices - 1) throw Halt{MappingStop::invalid_join_tree};
    }
  }
  bool connected(const std::vector<std::size_t>& selected) {
    budget.cells(native.size()); std::vector<unsigned char> seen(native.size());
    std::vector<std::size_t> walk; append(walk, selected.front(), budget); seen[selected.front()] = 1;
    for (std::size_t i = 0; i < walk.size(); ++i)
      for (auto next : adjacent[walk[i]]) {
        budget.step();
        if (roots[next] && !seen[next]) { append(walk, next, budget); seen[next] = 1; }
      }
    return walk.size() == selected.size();
  }
  // Removing R--R edges leaves one native component per first-native root.
  // Its native-only height is independent of the zero-weight prefix topology.
  std::size_t forest(const std::vector<std::size_t>& selected) {
    const auto n = native.size(); budget.cells(n); native_parent.assign(n, n);
    budget.cells(n); std::vector<std::size_t> depth(n);
    std::vector<std::size_t> walk;
    for (auto root : selected) {
      append(walk, root, budget); native_parent[root] = root; depth[root] = 1;
    }
    std::size_t height = 1;
    for (std::size_t i = 0; i < walk.size(); ++i) {
      const auto here = walk[i];
      for (auto next : adjacent[here]) {
        budget.step();
        if ((roots[here] && roots[next]) || native_parent[next] != n) continue;
        append(walk, next, budget); native_parent[next] = here; depth[next] = depth[here] + 1;
        height = std::max(height, depth[next]);
      }
    }
    if (walk.size() != n) throw Halt{MappingStop::invalid_join_tree};
    return height;
  }
  Scope common(const std::vector<std::size_t>& selected) {
    auto result = copied(native[selected.front()], budget);
    for (std::size_t i = 1; i < selected.size(); ++i)
      for (auto v = result.begin(); v != result.end();) {
        budget.step();
        if (!native[selected[i]].contains(*v)) v = result.erase(v); else ++v;
      }
    return result;
  }
  std::vector<std::size_t> branch(std::size_t anchor, std::size_t entry,
                                const std::vector<unsigned char>& member) {
    budget.cells(native.size()); std::vector<unsigned char> seen(native.size());
    seen[anchor] = 1; seen[entry] = 1;
    std::vector<std::size_t> result; append(result, entry, budget);
    for (std::size_t i = 0; i < result.size(); ++i)
      for (auto next : adjacent[result[i]]) {
        budget.step();
        if (member[next] && !seen[next]) { append(result, next, budget); seen[next] = 1; }
      }
    sort(result); return result;
  }
  // Copy a child into one disjoint block. Input indices stay stable; checked
  // representable room makes every offset addition safe before publication.
  std::size_t merge(Prefix& into, const Prefix& child) {
    const auto offset = into.nodes.size();
    if (child.nodes.empty() || child.root >= child.nodes.size() ||
        child.nodes.size() > into.nodes.max_size() - offset) throw Halt{MappingStop::fragment_limit};
    for (const auto& source : child.nodes) {
      budget.step(); PrefixNode node{source.occurrence, copied(source.scope, budget), {}};
      for (auto c : source.children) {
        if (c >= child.nodes.size()) throw Halt{MappingStop::invalid_join_tree};
        append(node.children, offset + c, budget);
      }
      append(into.nodes, std::move(node), budget);
    }
    return offset + child.root;
  }
  void emit(const Prefix& prefix) {
    budget.step();
    if (output.size() == budget.limits.output_trees) throw Halt{MappingStop::output_limit};
    const auto n = native.size(); budget.cells(n);
    std::vector<std::size_t> positions(n, std::numeric_limits<std::size_t>::max());
    FreeConnexTree tree; tree.root = NodeId{prefix.root};
    for (const auto& source : prefix.nodes) {
      budget.step(); const auto index = tree.nodes.size();
      TreeNode node{"meta-lift-" + std::to_string(index),
          source.occurrence ? NodeKind::native : NodeKind::generalized, {}, {}, source.occurrence, {}};
      if (source.occurrence) {
        const auto occurrence = *source.occurrence;
        if (occurrence >= n || positions[occurrence] != std::numeric_limits<std::size_t>::max())
          throw Halt{MappingStop::invalid_join_tree};
        positions[occurrence] = index; node.scope = copied(native[occurrence], budget);
      } else node.scope = copied(source.scope, budget);
      for (auto c : source.children) {
        if (c >= prefix.nodes.size()) throw Halt{MappingStop::invalid_join_tree};
        append(node.children, NodeId{c}, budget);
      }
      append(tree.nodes, std::move(node), budget);
    }
    for (std::size_t i = 0; i < n; ++i) {
      budget.step(); if (positions[i] != std::numeric_limits<std::size_t>::max()) continue;
      positions[i] = tree.nodes.size();
      append(tree.nodes, TreeNode{"meta-lift-" + std::to_string(tree.nodes.size()), NodeKind::native,
          copied(native[i], budget), {}, i, {}}, budget);
    }
    for (std::size_t i = 0; i < n; ++i) {
      budget.step();
      if (native_parent[i] != i) append(tree.nodes[positions[native_parent[i]]].children, NodeId{positions[i]}, budget);
    }
    append(output, std::move(tree), budget); budget.usage.output_trees = output.size();
  }
  void retain(Prefix prefix, Family& family, bool top) {
    if (top) emit(prefix); else append(family, std::move(prefix), budget);
  }
  Family descend(const std::vector<std::size_t>& selected, std::size_t depth) {
    if (depth == budget.limits.depth) throw Halt{MappingStop::depth_limit};
    budget.enter(depth + 1); return lift(selected, depth + 1, false);
  }
  // For a generalized cluster S, Guard/RIP force chi=intersection(scope[r],r∈S).
  // Canonical contraction toward min(S) makes child blocks whole branches cut
  // at that anchor; their crossing separators must equal the forced scope.
  Family lift(const std::vector<std::size_t>& selected, std::size_t depth, bool top) {
    budget.step(); Family result;
    if (selected.size() == 1) {
      budget.fragment(); Prefix leaf;
      append(leaf.nodes, PrefixNode{selected.front(), {}, {}}, budget);
      retain(std::move(leaf), result, top); return result;
    }
    const auto anchor = selected.front(); const auto scope = common(selected);
    budget.cells(native.size()); std::vector<unsigned char> member(native.size());
    for (auto v : selected) { budget.step(); member[v] = 1; }
    Scope boundary;
    for (auto v : selected) for (auto next : adjacent[v]) {
      budget.step();
      if (roots[next] && !member[next]) {
        const auto separator = intersection(native[v], native[next], budget);
        for (auto x : separator) variable(boundary, x, budget);
      }
    }
    if (!covers(scope, boundary, budget)) return result;
    std::vector<Branch> branches;
    for (auto next : adjacent[anchor]) {
      budget.step(); if (!member[next]) continue;
      if (!equal(intersection(native[anchor], native[next], budget), scope, budget)) continue;
      auto leaves = branch(anchor, next, member);
      if (leaves.front() != next) continue; // The edge must hit min(child block).
      auto family = descend(leaves, depth);
      if (!family.empty()) append(branches, Branch{std::move(leaves), std::move(family)}, budget);
    }
    if (branches.empty()) return result;
    budget.cells(branches.size()); std::vector<unsigned char> cuts(branches.size(), 1);
    do {
      budget.step(); ++report.generalized_partitions;
      budget.cells(native.size()); auto center_member = member;
      for (std::size_t i = 0; i < branches.size(); ++i) if (cuts[i])
        for (auto v : branches[i].leaves) { budget.step(); center_member[v] = 0; }
      std::vector<std::size_t> center;
      for (auto v : selected) { budget.step(); if (center_member[v]) append(center, v, budget); }
      auto central = descend(center, depth);
      if (central.empty()) continue;
      std::vector<const Family*> choices; append(choices, static_cast<const Family*>(&central), budget);
      for (std::size_t i = 0; i < branches.size(); ++i)
        if (cuts[i]) append(choices, static_cast<const Family*>(&branches[i].family), budget);
      budget.cells(choices.size()); std::vector<std::size_t> digits(choices.size());
      for (;;) {
        budget.fragment(); Prefix parent;
        append(parent.nodes, PrefixNode{{}, copied(scope, budget), {}}, budget);
        for (std::size_t i = 0; i < choices.size(); ++i) {
          budget.step();
          const auto child_root = merge(parent, (*choices[i])[digits[i]]);
          append(parent.nodes[0].children, child_root, budget);
        }
        retain(std::move(parent), result, top);
        std::size_t i = digits.size();
        while (i != 0) {
          budget.step(); --i;
          if (++digits[i] < choices[i]->size()) break;
          digits[i] = 0;
        }
        if (i == 0 && digits[0] == 0) break;
      }
    } while (previous(cuts, budget));
    return result;
  }
  void root_sets() {
    const auto n = native.size(); budget.cells(n); roots.assign(n, 1);
    do {
      budget.step(); ++report.root_sets;
      std::vector<std::size_t> selected;
      for (std::size_t i = 0; i < n; ++i) { budget.step(); if (roots[i]) append(selected, i, budget); }
      if (!connected(selected)) continue;
      if (forest(selected) != required_height) { ++report.height_pruned_root_sets; continue; }
      budget.enter(1); static_cast<void>(lift(selected, 1, true));
    } while (previous(roots, budget));
  }
 public:
  Mapper(const Query& q, std::size_t height, const MetaMappingLimits& limits,
         MetaCandidateReport& diagnostics, std::vector<FreeConnexTree>& drafts)
      : query(q), required_height(height), report(diagnostics), output(drafts), budget{limits, diagnostics.mapping_usage} {}
  void run(const std::vector<JoinTree>& trees) {
    scopes();
    for (const auto& tree : trees) {
      budget.step();
      if (tree.parent.size() != native.size() || tree.root >= native.size() || tree.parent[tree.root] != tree.root)
        throw Halt{MappingStop::invalid_join_tree};
      if (tree.root != 0) continue; // One orientation represents each undirected J.
      graph(tree); ++report.undirected_trees; root_sets();
    }
  }
};
} // namespace

PreparedMetaCandidates prepare_meta_candidates(VerifiedOptimum proof, MetaCandidateLimits limits) {
  if (!proof.valid()) throw Error("invalid_candidate_proof", "meta candidates require the original verified optimum");
  PreparedMetaCandidates result;
  const auto binding = proof.binding();
  const auto built = construct(binding.catalog(), binding.query(), limits.construction);
  result.report.construction_stop = built.stop; result.report.construction_usage = built.usage;
  if (built.stop != Stop::complete || !built.decomposition) return result;
  const auto ordinary = enumerate(binding.catalog(), binding.query(), *built.decomposition, limits.enumeration);
  result.report.enumeration_stop = ordinary.stop; result.report.enumeration_metadata = ordinary.metadata;
  result.report.enumeration_usage = ordinary.usage; result.report.rooted_ordinary_trees = ordinary.trees.size();
  result.report.ordinary_exhausted = ordinary.stop == EnumerationStop::complete;
  result.report.all_ordinary_roots_materialized = ordinary.all_roots;
  std::vector<FreeConnexTree> drafts;
  try {
    if (!ordinary.trees.empty()) {
      Mapper mapper(binding.query(), proof.height(), limits.mapping, result.report, drafts);
      mapper.run(ordinary.trees);
    }
    result.report.mapping_stop = MappingStop::complete;
    result.report.mapped_input_fibers_exhausted = true;
  } catch (const Halt& stop) { result.report.mapping_stop = stop.stop; }
  result.provider.emplace(CandidateProvider::from_proposals(std::move(proof), std::move(drafts), {}, limits.admission));
  return result;
}
} // namespace crown::planner::meta
