#include "update_pattern_detail.hpp"
#include <algorithm>

namespace crown::planner::patterns {
namespace {
template<class T> void reserve(Vector<T>& values, std::size_t count, detail::rd::Budget& budget) {
  if (count > UINT64_MAX / sizeof(T)) throw detail::rd::Failure{ranking::Stop::byte_limit};
  budget.cells(static_cast<std::uint64_t>(count));
  budget.bytes(static_cast<std::uint64_t>(count) * sizeof(T));
  values.reserve(count);
}
// Charge the actual logarithmic declaration lookup, without a second index.
const TableRule* find_rule(const Declaration& declaration, TableId table, detail::rd::Budget& budget) {
  const auto rules = declaration.rules();
  const auto found = std::lower_bound(rules.begin(), rules.end(), table,
      [&](const auto& rule, TableId key) {
        budget.work();
        return rule.table < key;
      });
  budget.work();
  return found != rules.end() && found->table == table ? &*found : nullptr;
}
// Each admitted input maps one physical row to zero/one occurrence row. Inserts
// only increase its support count; aliases add a fixed occurrence fanout. Use
// actual physical base IDs, which can differ from normalized core table IDs.
bool all_sources_insertion_only(const CompiledProgram& source, const Declaration& declaration,
    detail::rd::Budget& budget) {
  for (const auto& input : source.inputs()) {
    budget.work();
    const auto* rule = find_rule(declaration, input.base, budget);
    if (!rule || !rule->insertion_only) return false;
  }
  return true;
}
// A verified tree needs no visited set. Build a parent-before-child order, then
// fold subtree flags in reverse. Both scratch vectors use the receiving grant;
// no recursion, row copies, retained index or runtime update work is added.
Vector<std::uint8_t> insertion_subtrees(const MinimumHeightCandidate& candidate,
    const Declaration& declaration, const resource::MemoryAccount& account, detail::rd::Budget& budget) {
  const auto& tree = candidate.tree();
  Vector<NodeId> order(detail::allocator<NodeId>(account, resource::MemoryPurpose::scratch));
  Vector<std::uint8_t> flags(detail::allocator<std::uint8_t>(account, resource::MemoryPurpose::scratch));
  reserve(order, tree.nodes.size(), budget);
  reserve(flags, tree.nodes.size(), budget);
  budget.work(static_cast<std::uint64_t>(tree.nodes.size()));
  flags.resize(tree.nodes.size(), 1);
  order.push_back(*tree.root);
  for (std::size_t index = 0; index < order.size(); ++index) {
    budget.work();
    for (const auto child : tree.nodes[order[index].value].children) {
      budget.work();order.push_back(child);
    }
  }
  for (auto node = order.rbegin(); node != order.rend(); ++node) {
    budget.work();
    const auto& current = tree.nodes[node->value];
    if (current.kind == NodeKind::native) {
      const auto table = candidate.query().atoms[*current.occurrence].table;
      const auto* rule = find_rule(declaration, table, budget);
      flags[node->value] = rule && rule->insertion_only;
    }
    for (const auto child : current.children) {
      budget.work();flags[node->value] &= flags[child.value];
    }
  }
  return flags;
}
}
std::string_view name(SufficientCase value) noexcept {
  switch (value) {
    case SufficientCase::unknown: return "unknown";
    case SufficientCase::constant_result: return "constant_result";
    case SufficientCase::insertion_only: return "insertion_only";
    case SufficientCase::height_one: return "height_one";
    case SufficientCase::height_two_edges: return "height_two_edges";
    case SufficientCase::subtree_edges: return "subtree_edges";
  }
  return "unrecognized";
}
std::string_view name(Transfer value) noexcept {
  switch (value) {
    case Transfer::checked_typed_cq: return "checked_typed_cq";
    case Transfer::normalized_source: return "normalized_source";
    case Transfer::nullable_source: return "nullable_source";
    case Transfer::self_join: return "self_join";
    case Transfer::ignored_column: return "ignored_column";
    case Transfer::not_checked: return "not_checked";
    case Transfer::not_required: return "not_required";
    case Transfer::checked_event_mapping: return "checked_event_mapping";
    case Transfer::checked_monotone_source: return "checked_monotone_source";
  }
  return "unrecognized";
}
std::string_view name(EdgeBasis value) noexcept {
  switch (value) {
    case EdgeBasis::unproved: return "unproved";
    case EdgeBasis::child_insertion_only: return "child_insertion_only";
    case EdgeBasis::joint_fifo_scope: return "joint_fifo_scope";
    case EdgeBasis::subtree_insertion_only: return "subtree_insertion_only";
  }
  return "unrecognized";
}
Analysis::Analysis(const resource::MemoryAccount& account, const MinimumHeightCandidate& checked,
    const Declaration& requested)
    : candidate(checked), declaration(requested), edges(detail::allocator<EdgeCondition>(account)) {}

// Bind the full typed CQ before analysing an independently supplied candidate.
Analysis detail::analyse(const resource::MemoryAccount& account, const CompiledProgram& source,
    const MinimumHeightCandidate& candidate, const Declaration& declaration, rd::Budget& budget) {
  if (!source || !candidate.valid() || !declaration) throw rd::Failure{ranking::Stop::invalid_handle};
  budget.work(64);
  if (!declaration.matches(source)) throw rd::Failure{ranking::Stop::binding_mismatch};
  const auto expected = rd::score_binding(source.catalog(), source.query(), budget, account);
  const auto actual = rd::score_binding(candidate.catalog(), candidate.query(), budget, account);
  budget.work(static_cast<std::uint64_t>(std::max(expected.size(), actual.size())));
  if (expected != actual) throw rd::Failure{ranking::Stop::binding_mismatch};
  return analyse_bound(account, source, candidate, declaration, budget);
}

// Native adapters give zero/one crossing per routed occurrence. Monotone sources
// and arbitrary height-one trees need no FIFO lifetime transfer. Higher mixed
// trees retain the injective/self-join-free gate. For Q atoms, C columns/terms,
// R rules and T tree nodes: O(C + Q log Q + Q log(R+1) + T) charged comparisons
// and O(Q+T) scratch/edge cells; binding, bytes and allocator costs are additional.
Analysis detail::analyse_bound(const resource::MemoryAccount& account, const CompiledProgram& source,
    const MinimumHeightCandidate& candidate, const Declaration& declaration, rd::Budget& budget) {
  budget.work(2);
  Analysis result(account, candidate, declaration);
  result.height = candidate.height();
  if (source.route() != PhysicalRoute::tree) {
    result.transfer = Transfer::not_required;
    result.sufficient = SufficientCase::constant_result;
    return result;
  }
  if (all_sources_insertion_only(source, declaration, budget)) {
    result.transfer = Transfer::checked_monotone_source;
    result.sufficient = SufficientCase::insertion_only;
    return result;
  }
  if (result.height <= 1) {
    result.transfer = Transfer::checked_event_mapping;
    result.sufficient = SufficientCase::height_one;
    return result;
  }
  if (source.normalized()) {
    result.transfer = Transfer::normalized_source;
    return result;
  }
  const auto& query = candidate.query();
  const auto& catalog = candidate.catalog();
  Vector<TableId> tables(allocator<TableId>(account, resource::MemoryPurpose::scratch));
  reserve(tables, query.atoms.size(), budget);
  for (const auto& atom : query.atoms) {
    budget.work();
    tables.push_back(atom.table);
    for (const auto& column : catalog.tables[atom.table.value].columns) {
      budget.work();
      if (column.nullable) { result.transfer = Transfer::nullable_source; return result; }
    }
    // Repeated variables and constants reconstruct every accepted source
    // column. An ignored column permits the P4 projection counterexample.
    for (const auto& term : atom.terms) {
      budget.work();
      if (std::holds_alternative<IgnoredColumn>(term)) {
        result.transfer = Transfer::ignored_column;
        return result;
      }
    }
  }
  std::sort(tables.begin(), tables.end(), [&](auto a, auto b) { budget.work(); return a < b; });
  for (std::size_t i = 1; i < tables.size(); ++i) {
    budget.work();
    if (tables[i - 1] == tables[i]) { result.transfer = Transfer::self_join; return result; }
  }
  result.transfer = Transfer::checked_typed_cq;

  // An insertion-only internal input can still lose survivor status through its
  // descendants. Require its whole subtree to be monotone; FIFO alone is used
  // only for native leaves. At height two this is the original edge condition.
  Vector<std::uint8_t> subtrees(allocator<std::uint8_t>(account, resource::MemoryPurpose::scratch));
  if (result.height > 2) subtrees = insertion_subtrees(candidate, declaration, account, budget);
  reserve(result.edges, query.atoms.size(), budget);
  bool proved = true;
  const auto& tree = candidate.tree();
  for (std::size_t p = 0; p < tree.nodes.size(); ++p) {
    budget.work();
    const auto& parent = tree.nodes[p];
    if (parent.kind != NodeKind::native || parent.children.empty()) continue;
    const auto parent_table = query.atoms[*parent.occurrence].table;
    const auto* parent_rule = find_rule(declaration, parent_table, budget);
    for (const auto child_id : parent.children) {
      budget.work();
      const auto& child = tree.nodes[child_id.value];
      if (child.kind != NodeKind::native) throw rd::Failure{ranking::Stop::internal_error};
      const auto child_table = query.atoms[*child.occurrence].table;
      const auto* child_rule = find_rule(declaration, child_table, budget);
      EdgeCondition edge{NodeId{p}, child_id, parent_table, child_table};
      const bool leaf = child.children.empty();
      const bool insertion = result.height > 2 ? subtrees[child_id.value] != 0 : child_rule && child_rule->insertion_only;
      if (insertion) {
        edge.basis = leaf ? EdgeBasis::child_insertion_only : EdgeBasis::subtree_insertion_only;
      } else if (leaf && parent_rule && child_rule && parent_rule->fifo_scope &&
          parent_rule->fifo_scope == child_rule->fifo_scope) {
        edge.basis = EdgeBasis::joint_fifo_scope;
        edge.fifo_scope = parent_rule->fifo_scope;
      } else {
        proved = false;
      }
      result.edges.push_back(edge);
    }
  }
  if (proved) result.sufficient = result.height <= 2 ? SufficientCase::height_two_edges : SufficientCase::subtree_edges;
  return result;
}

// One translation boundary; private visitors use the existing ranking failures
// and RAII. Failed work never yields a partial conditional report.
Attempt analyse(const resource::MemoryAccount& account, const CompiledProgram& source,
    const MinimumHeightCandidate& candidate, const Declaration& declaration, const ranking::Limits& limits) noexcept {
  Attempt out;
  std::optional<detail::rd::Budget> budget;
  try {
    budget.emplace(limits, ranking::Usage{}, account);
    auto result = detail::analyse(account, source, candidate, declaration, *budget);
    budget->time();
    out.analysis.emplace(std::move(result));
    out.stop = ranking::Stop::complete;
  } catch (const detail::rd::Failure& failure) {
    out.stop = failure.stop;
  } catch (const std::bad_alloc&) {
    out.stop = ranking::Stop::allocation_failure;
  } catch (...) {
    out.stop = ranking::Stop::internal_error;
  }
  if (budget) out.usage = budget->usage;
  return out;
}
} // namespace crown::planner::patterns
