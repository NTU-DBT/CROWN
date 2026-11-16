#include "selection_detail.hpp"
#include "ranking_payload.hpp"
#include <type_traits>

namespace crown::planner::selection::detail {
namespace {
// Known first-DirectCQ copies and the post-lower identity use the same public
// component model as C02. Native private temporaries/allocator peak are excluded.
template<class T> void fixed(Budget& b) { b.work(); b.bytes(sizeof(T)); }
// Charge visited sequence elements and modeled element storage. See
// docs/selection_accounting.md.
template<class T> void sequence(const std::vector<T>& values, Budget& b) {
  b.work(static_cast<std::uint64_t>(values.size())); b.vector<T>(values.size());
}
void string(const std::string& value, Budget& b) {
  b.work(static_cast<std::uint64_t>(value.size())); b.bytes(static_cast<std::uint64_t>(value.size()));
}
// Admit dynamic scalar component allowance. See docs/selection_accounting.md.
void scalar(const Value& value, Budget& b) {
  b.work();
  if (const auto* text = std::get_if<std::string>(&value)) string(*text, b);
  else if (std::holds_alternative<Decimal>(value)) { b.work(38); b.bytes(38); }
}
void variables(const VariableSet& values, Budget& b) {
  b.work(static_cast<std::uint64_t>(values.size())); b.vector<VariableId>(values.size());
}
void catalog(const Catalog& value, Budget& b) {
  sequence(value.tables, b);
  for (const auto& table : value.tables) {
    string(table.name, b); sequence(table.columns, b);
    for (const auto& column : table.columns) string(column.name, b);
    sequence(table.constraints, b);
    for (const auto& constraint : table.constraints) {
      std::visit([&](const auto& item) {
        string(item.name, b); sequence(item.columns, b);
        if constexpr (std::is_same_v<std::decay_t<decltype(item)>, ForeignKeyConstraint>) sequence(item.referenced_columns, b);
      }, constraint);
    }
    sequence(table.statistics.distinct_counts, b);
    for (const auto& item : table.statistics.distinct_counts) sequence(item.columns, b);
    sequence(table.key_hints, b);
    for (const auto& hint : table.key_hints) { sequence(hint.columns, b); string(hint.reason, b); }
  }
}
void query(const Query& value, Budget& b) {
  sequence(value.variables, b); for (const auto& variable : value.variables) string(variable.name, b);
  sequence(value.atoms, b);
  for (const auto& atom : value.atoms) {
    string(atom.occurrence, b); sequence(atom.terms, b);
    for (const auto& term : atom.terms) if (const auto* item = std::get_if<Value>(&term)) scalar(*item, b);
  }
  sequence(value.head, b); for (const auto& output : value.head) string(output.alias, b);
}
void tree(const FreeConnexTree& value, Budget& b) {
  sequence(value.nodes, b);
  for (const auto& node : value.nodes) {
    string(node.id, b); variables(node.scope, b); sequence(node.children, b);
    if (node.claimed_separator) variables(*node.claimed_separator, b);
  }
  if (value.claimed_connex) sequence(*value.claimed_connex, b);
}
// Iteratively charge an ordinary identity DOM and traversal scratch. See
// docs/selection_accounting.md.
void canonical(const io::Json& root, Budget& b) {
  fixed<std::vector<io::Json*>>(b);
  b.vector<const io::Json*>(1); std::vector<const io::Json*> pending{&root};
  while (!pending.empty()) {
    const auto* item = pending.back(); pending.pop_back(); b.work(); b.cells(); b.bytes(sizeof(io::Json));
    if (item->is_structured()) b.vector<io::Json*>(1);
    if (item->is_string()) string(item->get_ref<const io::Json::string_t&>(), b);
    else if (item->is_object()) {
      for (const auto& pair : item->get_ref<const io::Json::object_t&>()) {
        b.bytes(sizeof(std::string)); string(pair.first, b); b.vector<const io::Json*>(1); pending.push_back(&pair.second);
      }
    } else if (item->is_array()) {
      for (const auto& child : item->get_ref<const io::Json::array_t&>()) {
        b.vector<const io::Json*>(1); pending.push_back(&child);
      }
    } else require(!item->is_binary());
  }
}
}
// Pre-admit known first DirectCQ compiler source components. See
// docs/selection_accounting.md.
void direct_source_payload(const MinimumHeightCandidate& candidate, Budget& budget) {
  fixed<PhysicalPlan>(budget); fixed<Catalog>(budget); fixed<Query>(budget);
  fixed<FreeConnexTree>(budget); fixed<std::optional<frontend::NormalizedSql>>(budget);
  catalog(candidate.catalog(), budget); query(candidate.query(), budget); tree(candidate.tree(), budget);
}
void identity_payload(const io::QueryIdentity& identity, Budget& budget) {
  fixed<io::QueryIdentity>(budget); canonical(identity.canonical, budget);
  string(identity.semantic_sha256, budget); string(identity.output_contract_sha256, budget);
  string(identity.cost_inputs_sha256, budget); string(identity.plan_cache_sha256, budget);
  sequence(identity.occurrence_order, budget); sequence(identity.variable_order, budget);
}
// Use the C02 native identity component visitor under existing grant/account. See
// docs/selection_accounting.md.
void identity_payload(const program::QueryIdentity& identity, Budget& budget) {
  budget.borrowed([&](rd::Budget& b){rd::plan_identity_payload(identity,b);});
}
void source_payload(const MinimumHeightCandidate& candidate, const PhysicalPlan& basis, Budget& budget) {
  budget.borrowed([&](rd::Budget& b) { rd::plan_source_payload(candidate, basis, b); });
}
void source_payload(const MinimumHeightCandidate& candidate, const CompiledProgram& basis, Budget& budget) {
  budget.borrowed([&](rd::Budget& b) { rd::plan_source_payload(candidate, basis, b); });
}
void compiled_payload(const PhysicalPlan& plan, Budget& budget) {
  budget.borrowed([&](rd::Budget& b) { rd::plan_compiled_payload(plan, b); });
}
void compiled_payload(const CompiledProgram& plan, Budget& budget) {
  budget.borrowed([&](rd::Budget& b) { rd::plan_compiled_payload(plan, b); });
}
// Compute logical source-plus-compiled retention charge for one cache entry. See
// docs/selection_accounting.md.
std::uint64_t cache_plan_payload(const MinimumHeightCandidate& candidate, const CompiledProgram& plan, Budget& budget) {
  const auto before = budget.usage.payload_bytes;
  source_payload(candidate, plan, budget); compiled_payload(plan, budget);
  return budget.usage.payload_bytes - before;
}
} // namespace crown::planner::selection::detail
