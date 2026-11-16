#include "crown/planner/verify.hpp"
#include "continuation_machine.hpp"

#include <algorithm>
#include <deque>
#include <set>
#include <string_view>
#include <utility>

namespace crown::planner::continuation_detail {

// Each case commits one cursor transition. Set/map lookup, allocation and
// scalar/string comparison remain abstract operations, with their actual costs.
// Scans, initialization, in-cursor scratch clearing and traversal save cursors.
// Deques keep existing elements in place on append; their internal map/allocation
// work is still a container cost. Report vectors reserve before incremental
// export. Final owner/scratch destruction happens outside the step protocol.
struct ValidationMachine::Impl {
  enum class Phase {
    start, empty_cover, empty_connex, empty_height, counts, nodes,
    node_name, node_scope, node_kind, native_terms, native_compare_begin,
    native_compare, native_scope_bad, native_clear, generalized_occurrence,
    generalized_leaf, node_next, cover, root, edges, parent_counts,
    reach_start, reach, reach_check, order_start, order, separator_reserve,
    separator_init, properties, separator, above, guard_begin, guard,
    claimed_separator_begin, claimed_separator, claimed_separator_bad,
    property_finish, connect_start, connect_seed, connect_walk,
    connect_check, connect_clear, head, maximal_reserve, maximal_start,
    maximal_node, maximal_scope, maximal_child, maximal_separator,
    head_check, supplied_start, supplied_ids, supplied_root, supplied_node,
    supplied_parent, supplied_separator, supplied_scope, supplied_head,
    height, export_prepare, export_violation, publish, done
  };
  struct NodeState {
    std::size_t parents = 0;
    std::optional<NodeId> parent;
    bool seen = false;
    std::optional<std::size_t> connected_variable;
    std::optional<NodeId> native_ancestor;
    std::size_t height = 0;
    std::size_t depth = 0;
  };
  struct Frame { NodeId node; std::size_t child = 0; };
  std::shared_ptr<const BindingData> binding;
  std::shared_ptr<const FreeConnexTree> tree;
  std::shared_ptr<ValidationReport> result = std::make_shared<ValidationReport>();
  std::shared_ptr<const CheckedUpper> authority;
  Phase phase = Phase::start;
  bool active = false;
  bool topology_valid = true;
  std::deque<std::size_t> occurrences;
  std::deque<NodeState> states;
  std::set<std::string_view> names;
  std::deque<Frame> frames;
  std::deque<NodeId> order;
  std::deque<NodeId> queue;
  std::deque<PlanViolation> violations;
  VariableSet complete_scope, head, covered, claimed_coverage;
  std::set<NodeId> supplied;
  VariableSet::const_iterator it{}, other{};
  std::set<NodeId>::const_iterator supplied_it{};
  std::size_t i = 0, j = 0, k = 0, position = 0, variable = 0;
  std::size_t height = 0, edge_depth = 0;
  NodeId first{0};
  bool output_only = true;

  Impl(std::shared_ptr<const BindingData> b, std::shared_ptr<const FreeConnexTree> t)
      : binding(std::move(b)), tree(std::move(t)) {}
  void violation(std::string rule, std::string message,
                 std::optional<NodeId> node = {}, std::optional<VariableId> var = {},
                 std::optional<std::size_t> occurrence = {}, std::optional<NodeId> related = {}) {
    violations.push_back({std::move(rule), std::move(message), node, var, occurrence, related});
  }
  UnitResult step(const UnitContext& context) {
    const auto& query = binding->query;
    const auto& t = *tree;
    switch (phase) {
      case Phase::start:
        if (!query.atoms.empty() && !context.permits(1)) return {UnitEvent::depth_blocked, 1};
        active = !query.atoms.empty();
        phase = query.atoms.empty() ? Phase::empty_cover : Phase::counts;
        break;
      case Phase::empty_cover:
        if (t.root || !t.nodes.empty()) violation("cover", "an empty-body constant query requires the empty tree");
        phase = Phase::empty_connex;
        break;
      case Phase::empty_connex:
        if (t.claimed_connex && !t.claimed_connex->empty()) violation("connex_certificate", "the empty tree has no connex nodes");
        phase = Phase::empty_height;
        break;
      case Phase::empty_height:
        if (t.claimed_native_height && *t.claimed_native_height != 0) violation("height", "the empty tree has native height zero");
        phase = Phase::export_prepare;
        break;
      case Phase::counts:
        if (occurrences.size() < query.atoms.size()) occurrences.push_back(0);
        else phase = Phase::nodes;
        break;
      case Phase::nodes:
        if (states.size() < t.nodes.size()) states.emplace_back();
        else { i = 0; phase = Phase::node_name; }
        break;
      case Phase::node_name:
        if (i == t.nodes.size()) { i = 0; phase = Phase::cover; break; }
        if (t.nodes[i].id.empty() || names.contains(t.nodes[i].id))
          violation("topology", "node IDs must be nonempty and unique", NodeId{i});
        else names.insert(t.nodes[i].id);
        it = t.nodes[i].scope.begin();
        phase = Phase::node_scope;
        break;
      case Phase::node_scope:
        if (it == t.nodes[i].scope.end()) { phase = Phase::node_kind; break; }
        if (it->value >= query.variables.size()) violation("scope", "node scope contains an unknown variable ID", NodeId{i}, *it);
        ++it;
        break;
      case Phase::node_kind: {
        const auto& node = t.nodes[i];
        if (node.kind == NodeKind::native) {
          if (!node.occurrence || *node.occurrence >= query.atoms.size()) {
            violation("cover", "native node must reference a query occurrence", NodeId{i}, {}, node.occurrence);
            phase = Phase::node_next;
          } else {
            ++occurrences[*node.occurrence]; j = 0; phase = Phase::native_terms;
          }
        } else if (node.kind == NodeKind::generalized) phase = Phase::generalized_occurrence;
        else { violation("scope", "unknown node kind", NodeId{i}); phase = Phase::node_next; }
        break;
      }
      case Phase::native_terms: {
        const auto& terms = query.atoms[*t.nodes[i].occurrence].terms;
        if (j == terms.size()) { phase = Phase::native_compare_begin; break; }
        if (const auto* v = std::get_if<VariableId>(&terms[j])) complete_scope.insert(*v);
        ++j;
        break;
      }
      case Phase::native_compare_begin:
        if (complete_scope.size() != t.nodes[i].scope.size()) phase = Phase::native_scope_bad;
        else { it = complete_scope.begin(); other = t.nodes[i].scope.begin(); phase = Phase::native_compare; }
        break;
      case Phase::native_compare:
        if (it == complete_scope.end()) phase = Phase::native_clear;
        else if (*it != *other) phase = Phase::native_scope_bad;
        else { ++it; ++other; }
        break;
      case Phase::native_scope_bad:
        violation("scope", "native node must carry its complete occurrence scope", NodeId{i}, {}, t.nodes[i].occurrence);
        phase = Phase::native_clear;
        break;
      case Phase::native_clear:
        if (!complete_scope.empty()) complete_scope.erase(complete_scope.begin());
        else phase = Phase::node_next;
        break;
      case Phase::generalized_occurrence:
        if (t.nodes[i].occurrence) violation("cover", "generalized node cannot reference an external occurrence", NodeId{i}, {}, t.nodes[i].occurrence);
        phase = Phase::generalized_leaf;
        break;
      case Phase::generalized_leaf:
        if (t.nodes[i].children.empty()) violation("cover", "every leaf must be native", NodeId{i});
        phase = Phase::node_next;
        break;
      case Phase::node_next:
        ++i; phase = Phase::node_name;
        break;
      case Phase::cover:
        if (i == occurrences.size()) { phase = Phase::root; break; }
        if (occurrences[i] != 1) violation("cover", "each native occurrence must appear exactly once", {}, {}, i);
        ++i;
        break;
      case Phase::root:
        // Numeric topology must be safe before separator/connectivity traversals.
        if (!t.root || t.root->value >= t.nodes.size()) {
          violation("topology", "nonempty tree needs an in-range root", t.root);
          topology_valid = false;
        }
        i = 0; j = 0; phase = Phase::edges;
        break;
      case Phase::edges:
        if (i == t.nodes.size()) { i = 0; phase = Phase::parent_counts; break; }
        if (j == t.nodes[i].children.size()) { ++i; j = 0; break; }
        if (const auto child = t.nodes[i].children[j]; child.value >= t.nodes.size()) {
          violation("topology", "child ID is out of range", NodeId{i}, {}, {}, child);
          topology_valid = false;
        } else { ++states[child.value].parents; states[child.value].parent = NodeId{i}; }
        ++j;
        break;
      case Phase::parent_counts:
        if (!t.root || t.root->value >= t.nodes.size() || i == t.nodes.size()) {
          phase = topology_valid ? Phase::reach_start : Phase::export_prepare;
          break;
        }
        if (states[i].parents != (i == t.root->value ? std::size_t{0} : std::size_t{1})) {
          violation("topology", "root must have no parent; every other node needs exactly one", NodeId{i});
          topology_valid = false;
        }
        ++i;
        break;
      case Phase::reach_start:
        if (!context.permits(1)) return {UnitEvent::depth_blocked, 1};
        frames.push_back({*t.root, 0});
        states[t.root->value].seen = true;
        phase = Phase::reach;
        break;
      case Phase::reach:
        if (frames.empty()) { i = 0; phase = Phase::reach_check; break; }
        if (frames.back().child == t.nodes[frames.back().node.value].children.size()) { frames.pop_back(); break; }
        {
          const auto child = t.nodes[frames.back().node.value].children[frames.back().child];
          if (states[child.value].seen) { ++frames.back().child; break; }
          const auto desired = frames.size() + 1;
          if (!context.permits(desired)) return {UnitEvent::depth_blocked, desired};
          frames.push_back({child, 0});
          ++frames[frames.size() - 2].child;
          states[child.value].seen = true;
        }
        break;
      case Phase::reach_check:
        if (i == states.size()) { phase = topology_valid ? Phase::order_start : Phase::export_prepare; break; }
        if (!states[i].seen) {
          violation("topology", "node is disconnected from the root (possibly in a cycle)", NodeId{i});
          topology_valid = false;
        }
        ++i;
        break;
      case Phase::order_start:
        order.push_back(*t.root); position = 0; j = 0; phase = Phase::order;
        break;
      case Phase::order:
        if (position == order.size()) { phase = Phase::separator_reserve; break; }
        if (j == t.nodes[order[position].value].children.size()) { ++position; j = 0; break; }
        order.push_back(t.nodes[order[position].value].children[j]);
        ++j;
        break;
      case Phase::separator_reserve:
        result->separators.reserve(t.nodes.size());
        phase = Phase::separator_init;
        break;
      case Phase::separator_init:
        if (result->separators.size() < t.nodes.size()) result->separators.emplace_back();
        else { position = 0; phase = Phase::properties; }
        break;
      case Phase::properties:
        if (position == order.size()) { variable = 0; phase = Phase::connect_start; break; }
        i = order[position].value;
        if (const auto parent = states[i].parent) {
          states[i].native_ancestor = t.nodes[parent->value].kind == NodeKind::native ? parent : states[parent->value].native_ancestor;
          states[i].height = states[parent->value].height;
          states[i].depth = states[parent->value].depth + 1;
        }
        it = t.nodes[i].scope.begin(); phase = Phase::separator;
        break;
      case Phase::separator:
        if (!states[i].parent || it == t.nodes[i].scope.end()) { phase = Phase::above; break; }
        if (t.nodes[states[i].parent->value].scope.contains(*it)) result->separators[i].insert(*it);
        ++it;
        break;
      case Phase::above:
        if (t.nodes[i].kind == NodeKind::native) ++states[i].height;
        else if (states[i].native_ancestor) violation("above", "generalized node has a native ancestor", NodeId{i}, {}, {}, states[i].native_ancestor);
        j = 0; phase = Phase::guard_begin;
        break;
      case Phase::guard_begin:
        if (t.nodes[i].kind != NodeKind::generalized || j == t.nodes[i].children.size()) { phase = Phase::claimed_separator_begin; break; }
        it = t.nodes[i].scope.begin(); phase = Phase::guard;
        break;
      case Phase::guard:
        if (it == t.nodes[i].scope.end()) { ++j; phase = Phase::guard_begin; break; }
        if (!t.nodes[t.nodes[i].children[j].value].scope.contains(*it))
          violation("guard", "generalized scope is not contained in a child's scope", NodeId{i}, *it, {}, t.nodes[i].children[j]);
        ++it;
        break;
      case Phase::claimed_separator_begin:
        if (!t.nodes[i].claimed_separator) phase = Phase::property_finish;
        else if (t.nodes[i].claimed_separator->size() != result->separators[i].size()) phase = Phase::claimed_separator_bad;
        else { it = t.nodes[i].claimed_separator->begin(); other = result->separators[i].begin(); phase = Phase::claimed_separator; }
        break;
      case Phase::claimed_separator:
        if (it == t.nodes[i].claimed_separator->end()) phase = Phase::property_finish;
        else if (*it != *other) phase = Phase::claimed_separator_bad;
        else { ++it; ++other; }
        break;
      case Phase::claimed_separator_bad:
        violation("separator", "claimed separator differs from the actual parent-scope intersection", NodeId{i});
        phase = Phase::property_finish;
        break;
      case Phase::property_finish:
        if (t.nodes[i].children.empty()) { height = std::max(height, states[i].height); edge_depth = std::max(edge_depth, states[i].depth); }
        ++position; phase = Phase::properties;
        break;
      case Phase::connect_start:
        // Connectivity uses the containing-node subgraph, including parent edges.
        if (variable == query.variables.size()) { i = 0; phase = Phase::head; break; }
        i = 0; phase = Phase::connect_seed;
        break;
      case Phase::connect_seed:
        if (i == t.nodes.size()) { ++variable; phase = Phase::connect_start; break; }
        if (!t.nodes[i].scope.contains(VariableId{variable})) { ++i; break; }
        queue.push_back(NodeId{i});
        states[i].connected_variable = variable;
        first = NodeId{i}; position = 0; j = 0; phase = Phase::connect_walk;
        break;
      case Phase::connect_walk: {
        if (position == queue.size()) { i = 0; phase = Phase::connect_check; break; }
        const auto current = queue[position];
        std::optional<NodeId> next;
        if (j == 0) next = states[current.value].parent;
        else if (j - 1 < t.nodes[current.value].children.size()) next = t.nodes[current.value].children[j - 1];
        else { ++position; j = 0; break; }
        if (next && t.nodes[next->value].scope.contains(VariableId{variable}) && states[next->value].connected_variable != variable) {
          queue.push_back(*next);
          states[next->value].connected_variable = variable;
        }
        ++j;
        break;
      }
      case Phase::connect_check:
        if (i == t.nodes.size()) { phase = Phase::connect_clear; break; }
        if (t.nodes[i].scope.contains(VariableId{variable}) && states[i].connected_variable != variable) {
          violation("connect", "variable occurrences do not induce a connected subtree", NodeId{i}, VariableId{variable}, {}, first);
          phase = Phase::connect_clear;
        } else ++i;
        break;
      case Phase::connect_clear:
        if (!queue.empty()) queue.pop_front();
        else { ++variable; phase = Phase::connect_start; }
        break;
      case Phase::head:
        if (i == query.head.size()) { phase = Phase::maximal_reserve; break; }
        head.insert(query.head[i].variable); ++i;
        break;
      case Phase::maximal_reserve:
        result->maximal_connex.reserve(t.nodes.size()); phase = Phase::maximal_start;
        break;
      case Phase::maximal_start:
        // C* crosses exactly output-only separators. Root scope may include
        // hidden variables; coverage, not root-scope containment, decides connex.
        result->maximal_connex.push_back(*t.root); position = 0; phase = Phase::maximal_node;
        break;
      case Phase::maximal_node:
        if (position == result->maximal_connex.size()) { it = head.begin(); phase = Phase::head_check; break; }
        i = result->maximal_connex[position].value; it = t.nodes[i].scope.begin(); phase = Phase::maximal_scope;
        break;
      case Phase::maximal_scope:
        if (it == t.nodes[i].scope.end()) { j = 0; phase = Phase::maximal_child; break; }
        covered.insert(*it); ++it;
        break;
      case Phase::maximal_child:
        if (j == t.nodes[i].children.size()) { ++position; phase = Phase::maximal_node; break; }
        k = t.nodes[i].children[j].value; it = result->separators[k].begin(); output_only = true; phase = Phase::maximal_separator;
        break;
      case Phase::maximal_separator:
        if (!output_only || it == result->separators[k].end()) {
          if (output_only) result->maximal_connex.push_back(NodeId{k});
          ++j; phase = Phase::maximal_child; break;
        }
        if (!head.contains(*it)) output_only = false;
        ++it;
        break;
      case Phase::head_check:
        if (it == head.end()) { phase = Phase::supplied_start; break; }
        if (!covered.contains(*it)) violation("connex", "maximal root-connected output subtree does not cover a head variable", t.root, *it);
        ++it;
        break;
      case Phase::supplied_start:
        if (t.claimed_connex) { i = 0; phase = Phase::supplied_ids; }
        else phase = Phase::height;
        break;
      case Phase::supplied_ids:
        if (i == t.claimed_connex->size()) { phase = Phase::supplied_root; break; }
        if (const auto id = (*t.claimed_connex)[i]; id.value >= t.nodes.size() || supplied.contains(id))
          violation("connex_certificate", "claimed connex node IDs must be in range and unique", id);
        else supplied.insert(id);
        ++i;
        break;
      case Phase::supplied_root:
        if (!supplied.contains(*t.root)) violation("connex_certificate", "claimed connex subtree must contain the root", t.root);
        supplied_it = supplied.begin(); phase = Phase::supplied_node;
        break;
      case Phase::supplied_node:
        if (supplied_it == supplied.end()) { it = head.begin(); phase = Phase::supplied_head; break; }
        i = supplied_it->value; phase = Phase::supplied_parent;
        break;
      case Phase::supplied_parent:
        if (states[i].parent && !supplied.contains(*states[i].parent)) violation("connex_certificate", "claimed connex subtree is not root-connected", NodeId{i});
        it = result->separators[i].begin(); phase = Phase::supplied_separator;
        break;
      case Phase::supplied_separator:
        if (it == result->separators[i].end()) { it = t.nodes[i].scope.begin(); phase = Phase::supplied_scope; break; }
        if (!head.contains(*it)) {
          violation("connex_certificate", "claimed connex subtree crosses a hidden-variable separator", NodeId{i});
          it = t.nodes[i].scope.begin(); phase = Phase::supplied_scope;
        } else ++it;
        break;
      case Phase::supplied_scope:
        if (it == t.nodes[i].scope.end()) { ++supplied_it; phase = Phase::supplied_node; break; }
        claimed_coverage.insert(*it); ++it;
        break;
      case Phase::supplied_head:
        if (it == head.end()) { phase = Phase::height; break; }
        if (!claimed_coverage.contains(*it)) violation("connex_certificate", "claimed connex subtree does not cover a head variable", t.root, *it);
        ++it;
        break;
      case Phase::height:
        if (t.claimed_native_height && *t.claimed_native_height != height) violation("height", "claimed native height differs from the checked native path count", t.root);
        phase = Phase::export_prepare;
        break;
      case Phase::export_prepare:
        result->violations.reserve(violations.size()); phase = Phase::export_violation;
        break;
      case Phase::export_violation:
        if (violations.empty()) { phase = Phase::publish; break; }
        result->violations.push_back(std::move(violations.front())); violations.pop_front();
        break;
      case Phase::publish:
        if (result->violations.empty()) {
          // Allocate the authority before mutating the report's validity. No
          // throw is possible after publishing either the report or authority.
          auto prepared = std::make_shared<CheckedUpper>(CheckedUpper{binding, tree, result, height});
          result->native_height = height; result->edge_depth = edge_depth;
          result->valid = true; authority = std::move(prepared);
        }
        active = false; phase = Phase::done;
        return {result->valid ? UnitEvent::upper_valid : UnitEvent::upper_invalid, 0};
      case Phase::done:
        return {result->valid ? UnitEvent::upper_valid : UnitEvent::upper_invalid, 0};
    }
    return {};
  }
};

ValidationMachine::ValidationMachine(std::shared_ptr<const BindingData> binding,
                                     std::shared_ptr<const FreeConnexTree> tree)
    : data_(std::make_unique<Impl>(std::move(binding), std::move(tree))) {}
ValidationMachine::~ValidationMachine() = default;
ValidationMachine::ValidationMachine(ValidationMachine&&) noexcept = default;
ValidationMachine& ValidationMachine::operator=(ValidationMachine&&) noexcept = default;
UnitResult ValidationMachine::step(const UnitContext& context) { return data_->step(context); }
const ValidationReport& ValidationMachine::report() const noexcept { return *data_->result; }
std::shared_ptr<const CheckedUpper> ValidationMachine::checked() const noexcept { return data_->authority; }
std::size_t ValidationMachine::current_depth() const noexcept {
  // One saved rule frame is active for nonempty input. Reachability reuses it
  // as its root frame and adds one explicit frame per descended tree edge.
  // Breadth-first frontiers are width, not simultaneously nested frames.
  return data_->active ? std::max(std::size_t{1}, data_->frames.size()) : 0;
}
}  // namespace crown::planner::continuation_detail

namespace crown::planner {
ValidationReport validate_tree(const Catalog& catalog, const Query& query, const FreeConnexTree& tree) {
  // Input validation and ownership copies are explicit blocking-adapter admission
  // work, outside continuation quanta. The rule engine below is the real cursor.
  validate(catalog, query);
  auto binding = std::make_shared<continuation_detail::BindingData>(
      continuation_detail::BindingData{catalog, query, AccountingVersion::continuation_v1});
  auto owned_tree = std::make_shared<FreeConnexTree>(tree);
  continuation_detail::ValidationMachine machine(std::move(binding), std::move(owned_tree));
  for (;;) {
    const auto event = machine.step({std::nullopt}).event;
    if (event == continuation_detail::UnitEvent::upper_valid || event == continuation_detail::UnitEvent::upper_invalid)
      return machine.report(); // Allocating legacy result export, outside quanta.
  }
}
}  // namespace crown::planner
