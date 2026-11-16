#include "producer_cursor.hpp"
#include "crown/api/error.hpp"
#include <algorithm>
#include <map>
#include <set>

namespace crown::planner::continuation_detail {
namespace {
using namespace producer_private;
// Members keeps input-binding occurrence indices in sorted order; equal scopes remain distinct. See
// docs/planner_proofs.md, branch partitions.
using Members = std::vector<std::size_t>;
// Key includes the native subset, generalized-root permission and C* reachability; all three
// affect the recurrence. See docs/planner_proofs.md, branch partitions.
struct Key {
  Members members;
  bool generalized = true, reachable = true;
  // Compare the occurrence vector and both context flags, so equal subsets with different
  // permissions stay separate. See docs/planner_proofs.md, branch partitions.
  auto operator<=>(const Key&) const = default;
};
// Order immutable memo keys by contents; shared ownership identity does not identify a state.
// See docs/planner_proofs.md, branch partitions.
struct KeyLess {
  // Borrow non-null keys and compare their values for memo lookup. See
  // docs/planner_proofs.md, branch partitions.
  bool operator()(const std::shared_ptr<const Key>& a, const std::shared_ptr<const Key>& b) const { return *a < *b; }
};
// Classify equal complete scopes while retaining all native IDs. See docs/planner_proofs.md,
// P04 symmetry.
struct ScopeLess {
  // Compare complete scope contents for structural symmetry only. See docs/planner_proofs.md,
  // P04 symmetry.
  bool operator()(const std::shared_ptr<const VariableSet>& a, const std::shared_ptr<const VariableSet>& b) const { return *a < *b; }
};
// A Choice is a producer witness, with null height for infeasibility; P02 must check a
// materialized tree before it supplies an upper bound. See docs/planner_proofs.md, P06
// authority.
struct Choice {
  std::optional<std::size_t> height;
  NodeKind kind = NodeKind::native;
  std::optional<std::size_t> occurrence;
  std::shared_ptr<const VariableSet> scope;
  std::vector<const Choice*> children;
};
// Child edges never own their target. All records have stable addresses in a
// flat arena, so releasing a deep hierarchy uses vector iteration rather than
// recursively releasing shared child records. Draft records are private until
// publication; completed records are only exposed through const Choice*.
// Flat ownership keeps child pointers stable and teardown iterative over records. See
// docs/planner_continuations.md, retained state.
struct ChoiceArena {
  std::vector<std::unique_ptr<Choice>> records;
  // Commit a prepared choice only after arena insertion succeeds; a failed growth leaves the
  // draft available for retry. See docs/planner_continuations.md, retained state.
  Choice* append(std::unique_ptr<Choice>& prepared) {
    auto* result = prepared.get();
    // unique_ptr movement is noexcept: vector growth failure preserves both
    // the arena and the prepared record, and publication below cannot throw.
    records.push_back(std::move(prepared));
    return result;
  }
  // Allocate a private default choice, then transfer it to the arena. See
  // docs/planner_continuations.md, retained state.
  Choice* append() {
    auto prepared = std::make_unique<Choice>();
    return append(prepared);
  }
};
// Metadata stores U(S), boundary B(S) and exclusive head E(S) for one actual native subset.
// See docs/planner_proofs.md, branch partitions.
struct Metadata { VariableSet variables, boundary, private_head; };
// Create child frames in the pending-operation scheduler before awaiting them; preserve
// parent state on allocation failure. See docs/planner_continuations.md, grants.
#define SUBTASK(expression) do { co_await operation([&] { task = (expression); }, e.depth + 1); co_await task; } while (false)
// Append source IDs in order to a caller-retained destination; callers pass fresh state
// vectors. See docs/planner_continuations.md, grants.
Task copy_members(Engine&, const Members& source, Members& dest) {
  co_await operation([&] { dest.reserve(dest.size() + source.size()); });
  for (const auto member : source) co_await operation([&] { dest.push_back(member); });
}
// Union a stable source scope into retained scratch one variable per pending operation. See
// docs/planner_continuations.md, grants.
Task copy_scope(Engine&, const VariableSet& source, VariableSet& dest) {
  for (const auto variable : source) co_await operation([&] { dest.insert(variable); });
}
// Test required ⊆ scope with an early missing-variable exit. See docs/planner_proofs.md,
// branch partitions.
Task contains(Engine&, const VariableSet& scope, const VariableSet& required, bool& result) {
  result = true;
  for (const auto variable : required) {
    co_await operation([&] { result = scope.contains(variable); });
    if (!result) co_return;
  }
}
// Copy a checked tree into fresh certificate scratch, preserving node indices and optional
// claims through saved operations. See docs/planner_continuations.md, grants.
Task copy_tree(Engine& e, const FreeConnexTree& source, FreeConnexTree& target) {
  Task task;
  co_await operation([&] { target.nodes.reserve(source.nodes.size()); });
  target.root = source.root;
  target.claimed_native_height = source.claimed_native_height;
  for (const auto& node : source.nodes) {
    co_await operation([&] { target.nodes.push_back({node.id, node.kind, {}, {}, node.occurrence, {}}); });
    SUBTASK(copy_scope(e, node.scope, target.nodes.back().scope));
    co_await operation([&] { target.nodes.back().children.reserve(node.children.size()); });
    for (const auto child : node.children) co_await operation([&] { target.nodes.back().children.push_back(child); });
    if (node.claimed_separator) {
      target.nodes.back().claimed_separator.emplace();
      SUBTASK(copy_scope(e, *node.claimed_separator, *target.nodes.back().claimed_separator));
    }
  }
  if (source.claimed_connex) {
    target.claimed_connex.emplace();
    co_await operation([&] { target.claimed_connex->reserve(source.claimed_connex->size()); });
    for (const auto node : *source.claimed_connex) co_await operation([&] { target.claimed_connex->push_back(node); });
  }
}
} // namespace
// Retain the choice arena while a witness builder reads the completed root; this is a
// candidate, not checked authority. See docs/planner_continuations.md, authority.
struct FrozenCandidate {
  std::shared_ptr<const ChoiceArena> arena;
  const Choice* root = nullptr;
};

// Own exact-search cursors and memo entries; candidates pause the producer until
// materialization and P02 validation finish. See docs/planner_continuations.md, authority.
struct ProducerMachine::Impl {
  // Capture the admitted binding; preprocessing starts only on step. See
  // docs/planner_continuations.md, grants.
  explicit Impl(std::shared_ptr<const BindingData> b) : binding(std::move(b)) {}
  // Cancel live frames before Task/member destruction; retained candidates keep their own
  // arena ownership. See docs/planner_continuations.md, lifetime.
  ~Impl() { e.cancel(); }
  std::shared_ptr<const BindingData> binding;
  Engine e;
  Task run;
  SearchPhase phase = SearchPhase::admitted;
  SearchStatistics stats;
  std::vector<std::shared_ptr<VariableSet>> scopes;
  VariableSet head;
  std::map<VariableId, std::size_t> totals;
  std::map<std::shared_ptr<const VariableSet>, Members, ScopeLess> classes;
  std::vector<Members> components;
  std::map<std::shared_ptr<const Key>, const Choice*, KeyLess> choices;
  std::shared_ptr<ChoiceArena> arena;
  std::shared_ptr<const FrozenCandidate> pending;
  std::shared_ptr<const CheckedUpper> upper;
  std::shared_ptr<const HeightCertificate> proof;
  std::shared_ptr<HeightCertificate> draft;
  std::shared_ptr<Key> root;
  const Choice* selected = nullptr;

  // Derive ports from full native scopes and global occurrence totals, never from output
  // projections. See docs/planner_proofs.md, branch partitions.
  Task metadata(const Members& members, Metadata& out) {
    std::map<VariableId, std::size_t> counts;
    for (const auto occurrence : members) {
      co_await operation([] {});
      for (const auto variable : *scopes[occurrence]) co_await operation([&] { ++counts[variable]; });
    }
    for (const auto& [variable, count] : counts) {
      co_await operation([&] { out.variables.insert(variable); });
      if (count < totals.at(variable)) co_await operation([&] { out.boundary.insert(variable); });
      else if (head.contains(variable)) co_await operation([&] { out.private_head.insert(variable); });
    }
  }
  // Publish an arena-retaining root candidate only after its wrapper is ready. See
  // docs/planner_continuations.md, authority.
  Task publish(const Choice* choice) {
    co_await operation([&] {
      auto frozen = std::make_shared<FrozenCandidate>();
      frozen->arena = arena;
      frozen->root = choice;
      pending = std::move(frozen);
    });
  }
  // Keep strict improvements only; prune with native root cost and safe child lower bounds,
  // never with residual rounds or cost scores. See docs/planner_proofs.md, P04 pruning.
  Task consider(const std::shared_ptr<const Key>& key, NodeKind kind,
                std::optional<std::size_t> occurrence, std::shared_ptr<const VariableSet> scope,
                const std::vector<Members>& blocks, const Choice*& best) {
    Task task;
    const auto cost = kind == NodeKind::native ? std::size_t{1} : std::size_t{0};
    co_await operation([&] { ++stats.candidates; });
    if (best && best->height && cost + (blocks.empty() ? 0 : 1) >= *best->height) {
      co_await operation([&] { ++stats.bound_prunes; }); co_return;
    }
    std::unique_ptr<Choice> candidate;
    co_await operation([&] { candidate = std::make_unique<Choice>(); });
    candidate->height = cost; candidate->kind = kind; candidate->occurrence = occurrence; candidate->scope = std::move(scope);
    std::size_t maximum = 0;
    for (const auto& block : blocks) {
      Metadata meta;
      SUBTASK(metadata(block, meta));
      bool reachable = false;
      if (key->reachable) { SUBTASK(contains(e, head, meta.boundary, reachable)); }
      std::shared_ptr<Key> child;
      co_await operation([&] { child = std::make_shared<Key>(); });
      child->generalized = kind == NodeKind::generalized; child->reachable = reachable;
      SUBTASK(copy_members(e, block, child->members));
      const Choice* value = nullptr;
      SUBTASK(solve(child, value));
      if (!value->height) co_return;
      maximum = std::max(maximum, *value->height);
      if (best && best->height && cost + maximum >= *best->height) {
        co_await operation([&] { ++stats.bound_prunes; }); co_return;
      }
      co_await operation([&] { candidate->children.push_back(value); });
    }
    candidate->height = cost + maximum;
    co_await operation([&] { best = arena->append(candidate); });
    if (key == root) { SUBTASK(publish(best)); }
  }
  // Check native ports or derive the unique normalized generalized scope from child unions
  // before considering a partition. See docs/planner_proofs.md, branch partitions.
  Task inspect_partition(const std::shared_ptr<const Key>& key, const Metadata& meta,
                         std::optional<std::size_t> occurrence, const std::vector<Members>& blocks,
                         const Choice*& best) {
    Task task;
    co_await operation([&] { ++stats.partitions; });
    if (occurrence) {
      for (const auto& block : blocks) {
        Metadata child;
        SUBTASK(metadata(block, child));
        bool valid = false;
        SUBTASK(contains(e, *scopes[*occurrence], child.boundary, valid));
        if (!valid) co_return;
      }
      SUBTASK(consider(key, NodeKind::native, occurrence, scopes[*occurrence], blocks, best));
    } else {
      if (blocks.size() < 2) co_return;
      std::map<VariableId, std::size_t> incidence;
      for (const auto& block : blocks) {
        Metadata child;
        SUBTASK(metadata(block, child));
        for (const auto variable : child.variables) co_await operation([&] { ++incidence[variable]; });
      }
      std::shared_ptr<VariableSet> shared;
      co_await operation([&] { shared = std::make_shared<VariableSet>(); });
      for (const auto& [variable, count] : incidence) {
        co_await operation([&] { if (count >= 2) shared->insert(variable); });
      }
      bool valid = false;
      SUBTASK(contains(e, *shared, meta.boundary, valid));
      if (!valid) co_return;
      for (const auto& block : blocks) {
        Metadata child;
        SUBTASK(metadata(block, child));
        SUBTASK(contains(e, child.variables, *shared, valid));
        if (!valid) co_return;
      }
      SUBTASK(consider(key, NodeKind::generalized, {}, shared, blocks, best));
    }
  }
  // Enumerate partitions by ordered insertion; return early only at the universal nonempty
  // lower bound one. See docs/planner_proofs.md, branch partitions.
  Task partitions(const std::shared_ptr<const Key>& key, const Metadata& meta,
                  std::optional<std::size_t> occurrence, const Members& members, std::size_t position,
                  std::vector<Members>& blocks, const Choice*& best) {
    Task task;
    if (position == members.size()) {
      SUBTASK(inspect_partition(key, meta, occurrence, blocks, best)); co_return;
    }
    const auto existing = blocks.size();
    for (std::size_t i = 0; i < existing; ++i) {
      co_await operation([&] { blocks[i].push_back(members[position]); });
      SUBTASK(partitions(key, meta, occurrence, members, position + 1, blocks, best));
      co_await operation([&] { blocks[i].pop_back(); });
      if (best && best->height == 1) co_return;
    }
    co_await operation([&] { Members block; block.push_back(members[position]); blocks.push_back(std::move(block)); });
    SUBTASK(partitions(key, meta, occurrence, members, position + 1, blocks, best));
    co_await operation([&] { blocks.pop_back(); });
  }
  // Memoize only complete state optima; component, symmetry and incumbent rules preserve one
  // optimum. A resource stop never creates an infeasible memo value. See
  // docs/planner_proofs.md, P03/P04.
  Task solve(std::shared_ptr<const Key> key, const Choice*& result) {
    Task task;
    co_await operation([] {});
    const auto cached = choices.find(key);
    if (cached != choices.end()) {
      result = cached->second;
      co_await operation([&] { ++stats.cache_hits; }); co_return;
    }
    co_await operation([&] { ++stats.states; });
    const Choice* best = nullptr;
    if (key == root && components.size() > 1) {
      Choice* combined = nullptr;
      co_await operation([&] { combined = arena->append(); });
      combined->kind = NodeKind::generalized; combined->height = 0;
      co_await operation([&] { combined->scope = std::make_shared<VariableSet>(); });
      co_await operation([&] { ++stats.component_splits; });
      for (const auto& component : components) {
        std::shared_ptr<Key> child;
        co_await operation([&] { child = std::make_shared<Key>(); });
        SUBTASK(copy_members(e, component, child->members));
        const Choice* value = nullptr;
        SUBTASK(solve(child, value));
        if (!value->height) { combined->height.reset(); break; }
        combined->height = std::max(*combined->height, *value->height);
        co_await operation([&] { combined->children.push_back(value); });
      }
      best = combined;
      if (best->height) { SUBTASK(publish(best)); }
    } else {
      Metadata meta;
      SUBTASK(metadata(key->members, meta));
      if (key->reachable || meta.private_head.empty()) {
        std::set<std::shared_ptr<const VariableSet>, ScopeLess> native_roots;
        for (const auto occurrence : key->members) {
          bool fresh = false;
          co_await operation([&] { fresh = native_roots.insert(scopes[occurrence]).second; });
          if (!fresh) { co_await operation([&] { ++stats.symmetry_skips; }); continue; }
          bool valid = false;
          SUBTASK(contains(e, *scopes[occurrence], meta.boundary, valid));
          if (!valid) continue;
          Members remaining;
          for (const auto item : key->members) co_await operation([&] { if (item != occurrence) remaining.push_back(item); });
          std::vector<Members> blocks;
          SUBTASK(partitions(key, meta, occurrence, remaining, 0, blocks, best));
          if (best && best->height == 1) break;
        }
        if (key->generalized && (!best || best->height != 1)) {
          std::vector<Members> blocks;
          SUBTASK(partitions(key, meta, {}, key->members, 0, blocks, best));
        }
      }
    }
    if (!best) co_await operation([&] { best = arena->append(); });
    co_await operation([&] { choices.emplace(key, best); });
    result = best;
  }
  // Build full scopes, equal-scope classes and variable-sharing components while preserving
  // every original occurrence. See docs/planner_proofs.md, P04 rules.
  Task preprocess() {
    Task task;
    std::vector<std::size_t> parent;
    std::map<VariableId, std::size_t> first;
    co_await operation([&] { parent.reserve(binding->query.atoms.size()); });
    co_await operation([&] { scopes.reserve(binding->query.atoms.size()); });
    for (std::size_t i = 0; i < binding->query.atoms.size(); ++i) {
      co_await operation([&] { parent.push_back(i); });
      co_await operation([&] { auto scope = std::make_shared<VariableSet>(); scopes.push_back(std::move(scope)); });
      for (const auto& term : binding->query.atoms[i].terms) {
        co_await operation([&] { if (const auto* v = std::get_if<VariableId>(&term)) scopes[i]->insert(*v); });
      }
      for (const auto variable : *scopes[i]) {
        co_await operation([&] { ++totals[variable]; });
        bool inserted = false;
        std::size_t other = i;
        co_await operation([&] { const auto [it, fresh] = first.emplace(variable, i); inserted = fresh; other = it->second; });
        if (!inserted) {
          auto a = i, b = other;
          while (parent[a] != a) co_await operation([&] { a = parent[a]; });
          while (parent[b] != b) co_await operation([&] { b = parent[b]; });
          co_await operation([&] { parent[a] = b; });
        }
      }
      co_await operation([&] { classes.try_emplace(scopes[i]); });
      co_await operation([&] { classes.find(scopes[i])->second.push_back(i); });
    }
    for (const auto& output : binding->query.head) co_await operation([&] { head.insert(output.variable); });
    std::map<std::size_t, Members> grouped;
    for (std::size_t i = 0; i < parent.size(); ++i) {
      auto representative = i;
      while (parent[representative] != representative) co_await operation([&] { representative = parent[representative]; });
      co_await operation([&] { grouped.try_emplace(representative); });
      co_await operation([&] { grouped.find(representative)->second.push_back(i); });
    }
    for (auto& [id, members] : grouped) {
      static_cast<void>(id);
      // Reserve before moving an owned component so allocation failure cannot
      // consume the source vector.
      co_await operation([&] { components.reserve(components.size() + 1); });
      co_await operation([&] { components.push_back(std::move(members)); });
    }
  }
  // Recognize laminar incidence classes with free-variable upward closure; a hit constructs
  // an upper candidate at height one, then P02 checks it. See docs/planner_proofs.md, P04
  // hierarchy.
  Task hierarchy(const Choice*& result) {
    Task task;
    co_await operation([&] { ++stats.hierarchy_tests; });
    std::map<VariableId, std::shared_ptr<Members>> incidence;
    for (std::size_t i = 0; i < scopes.size(); ++i) {
      co_await operation([] {});
      for (const auto variable : *scopes[i]) {
        co_await operation([&] { if (!incidence.contains(variable)) { auto members = std::make_shared<Members>(); incidence.emplace(variable, std::move(members)); } });
        co_await operation([&] { incidence.at(variable)->push_back(i); });
      }
    }
    // Group equal variable incidences before discovering the least strict superset and
    // constructing the forest. See docs/planner_proofs.md, P04 hierarchy.
    struct Group {
      std::shared_ptr<const Members> members;
      VariableSet variables;
      bool free = false, hidden = false;
      std::optional<std::size_t> parent;
      Choice* node = nullptr;
    };
    // Compare immutable incidence vectors by contents to form hierarchy classes. See
    // docs/planner_proofs.md, P04 hierarchy.
    struct MemberLess {
      // Equal occurrence vectors identify one hierarchy class, even when its variables mix
      // free and hidden roles. See docs/planner_proofs.md, P04 hierarchy.
      bool operator()(const std::shared_ptr<const Members>& a, const std::shared_ptr<const Members>& b) const { return *a < *b; }
    };
    std::map<std::shared_ptr<const Members>, std::shared_ptr<Group>, MemberLess> grouped;
    for (const auto& [variable, members] : incidence) {
      co_await operation([&] {
        if (!grouped.contains(members)) {
          auto group = std::make_shared<Group>(); group->members = members;
          grouped.emplace(members, std::move(group));
        }
      });
      auto group = grouped.find(members)->second;
      co_await operation([&] { group->variables.insert(variable); });
      if (head.contains(variable)) group->free = true; else group->hidden = true;
    }
    std::vector<std::shared_ptr<Group>> groups;
    for (const auto& [members, group] : grouped) {
      static_cast<void>(members);
      co_await operation([&] { groups.push_back(group); });
      auto position = groups.size() - 1;
      while (position > 0) {
        bool swap = false;
        co_await operation([&] { swap = groups[position]->members->size() > groups[position - 1]->members->size(); });
        if (!swap) break;
        co_await operation([&] { groups[position].swap(groups[position - 1]); --position; });
      }
    }
    for (std::size_t i = 0; i < groups.size(); ++i) {
      for (std::size_t j = 0; j < i; ++j) {
        bool intersects = false;
        for (const auto occurrence : *groups[i]->members) {
          co_await operation([&] { intersects = std::binary_search(groups[j]->members->begin(), groups[j]->members->end(), occurrence); });
          if (intersects) break;
        }
        if (!intersects) continue;
        std::size_t a = 0, b = 0;
        bool subset = true;
        while (a < groups[i]->members->size() && b < groups[j]->members->size()) {
          co_await operation([&] {
            const auto x = (*groups[i]->members)[a], y = (*groups[j]->members)[b];
            if (x == y) { ++a; ++b; }
            else if (x > y) ++b;
            else subset = false;
          });
          if (!subset) break;
        }
        if (!subset || a != groups[i]->members->size()) co_return;
        if (groups[i]->free && groups[j]->hidden) co_return;
        co_await operation([&] {
          if (!groups[i]->parent || groups[j]->members->size() < groups[*groups[i]->parent]->members->size()) groups[i]->parent = j;
        });
      }
    }
    std::vector<const Choice*> roots;
    for (auto& group : groups) {
      co_await operation([] {});
      if (group->members->size() < 2) continue;
      Choice* node = nullptr;
      std::shared_ptr<VariableSet> scope;
      co_await operation([&] { node = arena->append(); });
      co_await operation([&] { scope = std::make_shared<VariableSet>(); });
      SUBTASK(copy_scope(e, group->variables, *scope));
      if (group->parent) { SUBTASK(copy_scope(e, *groups[*group->parent]->node->scope, *scope)); }
      node->height = 1; node->kind = NodeKind::generalized; node->scope = std::move(scope);
      if (group->parent) co_await operation([&] { groups[*group->parent]->node->children.push_back(node); });
      else co_await operation([&] { roots.push_back(node); });
      group->node = node;
    }
    for (std::size_t occurrence = 0; occurrence < scopes.size(); ++occurrence) {
      Choice* parent_node = nullptr;
      for (const auto& group : groups) {
        co_await operation([&] {
          if (group->node && std::binary_search(group->members->begin(), group->members->end(), occurrence)) parent_node = group->node;
        });
      }
      Choice* leaf = nullptr;
      co_await operation([&] { leaf = arena->append(); });
      leaf->height = 1; leaf->scope = scopes[occurrence]; leaf->occurrence = occurrence;
      if (parent_node) co_await operation([&] { parent_node->children.push_back(leaf); });
      else co_await operation([&] { roots.push_back(leaf); });
    }
    if (roots.size() == 1) result = roots.front();
    else {
      Choice* joined = nullptr;
      co_await operation([&] { joined = arena->append(); });
      co_await operation([&] { joined->scope = std::make_shared<VariableSet>(); });
      joined->height = 1; joined->kind = NodeKind::generalized; joined->children = std::move(roots);
      result = joined;
    }
    co_await operation([&] { ++stats.hierarchy_hits; });
  }
  // Export complete memo claims and a matching independently checked upper; this producer
  // certificate still requires independent replay. See docs/planner_proofs.md, lower-bound
  // evidence.
  Task export_proof() {
    Task task;
    co_await operation([&] { draft = std::make_shared<HeightCertificate>(); });
    co_await operation([&] { draft->algorithm = "crown_partition_exact_v2"; });
    draft->minimum_height = selected->height;
    if (selected->height) {
      // Only the facade's complete independent P02 authority can supply this
      // upper. A stale earlier improving candidate cannot finalize the proof.
      co_await operation([&] {
        if (!upper || upper->binding != binding || upper->height != *selected->height)
          throw Error("invalid_search_witness", "final selected choice has no matching checked upper");
      });
      draft->tree.emplace();
      SUBTASK(copy_tree(e, *upper->tree, *draft->tree));
      draft->tree->claimed_native_height = upper->height;
      if (!draft->tree->claimed_connex) {
        draft->tree->claimed_connex.emplace();
        co_await operation([&] { draft->tree->claimed_connex->reserve(upper->report->maximal_connex.size()); });
        for (const auto node : upper->report->maximal_connex)
          co_await operation([&] { draft->tree->claimed_connex->push_back(node); });
      }
    }
    std::map<std::shared_ptr<const Key>, std::optional<std::size_t>, KeyLess> canonical;
    for (const auto& [key, choice] : choices) {
      std::shared_ptr<Key> representative;
      co_await operation([&] { representative = std::make_shared<Key>(); });
      representative->generalized = key->generalized; representative->reachable = key->reachable;
      for (const auto& [scope, members] : classes) {
        static_cast<void>(scope);
        std::size_t count = 0;
        co_await operation([] {});
        for (const auto occurrence : key->members) co_await operation([&] { if (std::binary_search(members.begin(), members.end(), occurrence)) ++count; });
        for (std::size_t i = 0; i < count; ++i) {
          co_await operation([&] { representative->members.push_back(members[i]); });
          auto position = representative->members.size() - 1;
          while (position > 0) {
            bool swap = false;
            co_await operation([&] { swap = representative->members[position] < representative->members[position - 1]; });
            if (!swap) break;
            co_await operation([&] { std::swap(representative->members[position], representative->members[position - 1]); --position; });
          }
        }
      }
      co_await operation([&] {
        const auto [it, inserted] = canonical.emplace(representative, choice->height);
        if (!inserted && it->second != choice->height) throw Error("invalid_search_proof", "scope orbit states disagree");
      });
    }
    for (const auto& [key, height] : canonical) {
      co_await operation([&] { draft->lower_bounds.push_back({{}, key->generalized, key->reachable, height}); });
      SUBTASK(copy_members(e, key->members, draft->lower_bounds.back().occurrences));
    }
    co_await operation([&] { proof = draft; phase = SearchPhase::complete; });
  }
  // Drive the structural routes and export only after the final candidate has a checked
  // upper; empty body alone has height zero. See docs/planner_continuations.md, authority.
  Task main() {
    Task task;
    phase = SearchPhase::preprocess;
    co_await operation([&] { arena = std::make_shared<ChoiceArena>(); });
    co_await operation([&] { root = std::make_shared<Key>(); });
    if (binding->query.atoms.empty()) {
      Choice* empty = nullptr;
      co_await operation([&] { empty = arena->append(); });
      empty->height = 0; selected = empty;
      co_await operation([&] { ++stats.empty_body_hits; });
      SUBTASK(publish(selected));
    } else {
      SUBTASK(preprocess());
      for (std::size_t i = 0; i < scopes.size(); ++i) co_await operation([&] { root->members.push_back(i); });
      if (scopes.size() == 1) {
        Choice* singleton = nullptr;
        co_await operation([&] { singleton = arena->append(); });
        singleton->height = 1; singleton->scope = scopes.front(); singleton->occurrence = 0; selected = singleton;
        co_await operation([&] { ++stats.singleton_hits; });
      } else { SUBTASK(hierarchy(selected)); }
      phase = SearchPhase::search;
      if (selected) {
        co_await operation([&] { choices.emplace(root, selected); });
        SUBTASK(publish(selected));
      } else { SUBTASK(solve(root, selected)); }
    }
    phase = SearchPhase::export_proof;
    SUBTASK(export_proof());
    phase = SearchPhase::complete;
  }
};

// Allocate an inert producer shell around the owned binding; step starts work. See
// docs/planner_continuations.md, grants.
ProducerMachine::ProducerMachine(std::shared_ptr<const BindingData> binding) : data_(std::make_unique<Impl>(std::move(binding))) {}
// Destroy the producer and cancel active frames; shared candidate arenas may outlive it. See
// docs/planner_continuations.md, lifetime.
ProducerMachine::~ProducerMachine() = default;
// Transfer the saved producer owner without moving frames or choice payloads. See
// docs/planner_continuations.md, lifetime.
ProducerMachine::ProducerMachine(ProducerMachine&&) noexcept = default;
// Replace ownership, releasing the previous producer and its unfinished state. See
// docs/planner_continuations.md, lifetime.
ProducerMachine& ProducerMachine::operator=(ProducerMachine&&) noexcept = default;
// Advance a saved transition, stopping for the candidate handshake or depth permission before
// creating more work. See docs/planner_continuations.md, grants.
UnitResult ProducerMachine::step(const UnitContext& context) {
  auto& d = *data_;
  if (d.pending) return {UnitEvent::candidate_ready, 0};
  if (d.proof) return {UnitEvent::producer_complete, 0};
  if (!d.run.handle) {
    if (!d.binding->query.atoms.empty() && !context.permits(1)) return {UnitEvent::depth_blocked, 1};
    auto prepared = d.main(); d.run = std::move(prepared); d.e.administrative_only = d.binding->query.atoms.empty(); d.e.start(d.run);
    return {};
  }
  auto result = d.e.step(context);
  if (result.event == UnitEvent::depth_blocked) return result;
  if (d.pending) return {UnitEvent::candidate_ready, 0};
  if (d.proof) return {UnitEvent::producer_complete, 0};
  return {};
}
// Read producer progress only; phase alone carries no minimum authority. See
// docs/planner_continuations.md, authority.
SearchPhase ProducerMachine::phase() const noexcept { return data_->phase; }
// Borrow producer counters while the machine lives; counters provide progress evidence, not
// lower bounds. See docs/planner_continuations.md, resource accounting.
const SearchStatistics& ProducerMachine::statistics() const noexcept { return data_->stats; }
// Report logical coroutine depth, with zero for empty administrative or completed work. See
// docs/planner_continuations.md, resource accounting.
std::size_t ProducerMachine::current_depth() const noexcept { return data_->proof || data_->e.administrative_only ? 0 : data_->e.depth; }
// Retain the pending arena-backed candidate for witness construction and P02 validation. See
// docs/planner_continuations.md, authority.
std::shared_ptr<const FrozenCandidate> ProducerMachine::candidate() const noexcept { return data_->pending; }
// Accept only facade-supplied P02 authority; final export checks its binding and selected
// height. See docs/planner_continuations.md, authority.
void ProducerMachine::accept_upper(std::shared_ptr<const CheckedUpper> upper) noexcept { data_->upper = std::move(upper); }
// Clear pending only after checked-upper publication succeeds, then resume exact search. See
// docs/planner_continuations.md, authority.
void ProducerMachine::acknowledge_candidate() noexcept { data_->pending.reset(); }
// Retain the exported certificate for independent replay; producer completion alone proves no
// public optimum. See docs/planner_continuations.md, authority.
std::shared_ptr<const HeightCertificate> ProducerMachine::completed_proof() const noexcept { return data_->proof; }

// Own incremental witness copying while the frozen candidate retains all borrowed choices;
// P02 validation follows. See docs/planner_continuations.md, retained state.
struct WitnessMachine::Impl {
  // Capture binding and candidate owners without traversing the choice graph. See
  // docs/planner_continuations.md, grants.
  Impl(std::shared_ptr<const BindingData> b, std::shared_ptr<const FrozenCandidate> c) : binding(std::move(b)), candidate(std::move(c)) {}
  // Cancel copying frames before releasing their borrowed draft and candidate data. See
  // docs/planner_continuations.md, lifetime.
  ~Impl() { e.cancel(); }
  std::shared_ptr<const BindingData> binding;
  std::shared_ptr<const FrozenCandidate> candidate;
  Engine e;
  Task run;
  std::shared_ptr<FreeConnexTree> draft;
  std::shared_ptr<const FreeConnexTree> completed;
  // Append a choice in preorder and link only existing parent IDs; keep the partial tree
  // private until copying completes. See docs/planner_continuations.md, grants.
  Task append(const Choice* choice, std::optional<NodeId> parent) {
    Task task;
    const NodeId id{draft->nodes.size()};
    co_await operation([&] { draft->nodes.push_back({"node" + std::to_string(id.value), choice->kind, {}, {}, choice->occurrence, {}}); });
    if (choice->scope) { SUBTASK(copy_scope(e, *choice->scope, draft->nodes[id.value].scope)); }
    if (parent) co_await operation([&] { draft->nodes[parent->value].children.push_back(id); });
    else draft->root = id;
    for (const auto& child : choice->children) { SUBTASK(append(child, id)); }
  }
  // Publish the concrete tree only after all choice copying finishes; its height claim still
  // needs P02 checking. See docs/planner_continuations.md, authority.
  Task main() {
    Task task;
    co_await operation([&] { draft = std::make_shared<FreeConnexTree>(); });
    if (candidate->root->height != 0) { SUBTASK(append(candidate->root, {})); }
    draft->claimed_native_height = candidate->root->height;
    co_await operation([&] { completed = draft; });
  }
};
// Allocate a witness shell retaining its binding and frozen candidate; copying starts on
// step. See docs/planner_continuations.md, grants.
WitnessMachine::WitnessMachine(std::shared_ptr<const BindingData> binding, std::shared_ptr<const FrozenCandidate> candidate)
    : data_(std::make_unique<Impl>(std::move(binding), std::move(candidate))) {}
// Release witness execution; any previously retained complete tree remains owned separately.
// See docs/planner_continuations.md, lifetime.
WitnessMachine::~WitnessMachine() = default;
// Transfer witness execution without moving its draft or suspended frames. See
// docs/planner_continuations.md, lifetime.
WitnessMachine::WitnessMachine(WitnessMachine&&) noexcept = default;
// Replace the witness owner, cancelling and releasing any prior destination copy. See
// docs/planner_continuations.md, lifetime.
WitnessMachine& WitnessMachine::operator=(WitnessMachine&&) noexcept = default;
// Advance one saved witness transition and publish completion only after the draft is whole.
// See docs/planner_continuations.md, grants.
UnitResult WitnessMachine::step(const UnitContext& context) {
  auto& d = *data_;
  if (d.completed) return {UnitEvent::witness_complete, 0};
  if (!d.run.handle) {
    if (!d.binding->query.atoms.empty() && !context.permits(1)) return {UnitEvent::depth_blocked, 1};
    auto prepared = d.main(); d.run = std::move(prepared); d.e.administrative_only = d.binding->query.atoms.empty(); d.e.start(d.run); return {};
  }
  auto result = d.e.step(context);
  if (result.event == UnitEvent::depth_blocked) return result;
  return d.completed ? UnitResult{UnitEvent::witness_complete, 0} : UnitResult{};
}
// Read copier frame depth separately from tree native height. See
// docs/planner_continuations.md, resource accounting.
std::size_t WitnessMachine::current_depth() const noexcept { return data_->e.administrative_only ? 0 : data_->e.depth; }
// Retain the complete candidate tree for P02 validation; copying alone gives no checked
// upper. See docs/planner_continuations.md, authority.
std::shared_ptr<const FreeConnexTree> WitnessMachine::tree() const noexcept { return data_->completed; }
#undef SUBTASK
} // namespace crown::planner::continuation_detail
