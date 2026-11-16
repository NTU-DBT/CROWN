#include "crown/planner/keys.hpp"
#include "crown/api/error.hpp"

namespace crown::planner::keys {
namespace {
// One cold guard balance covers all candidates and the final ID mapping.
// Existing tree search/replay/lowering keep their own declared allowances.
struct Budget {
  std::uint64_t remaining, used = 0;
  void take() {
    if(!remaining) throw Error("key_work_limit", "key rewrite work grant exceeded");
    --remaining; ++used;
  }
};

bool same_term(const Term& a, const Term& b, Budget& budget) {
  budget.take();
  if(const auto* variable = std::get_if<VariableId>(&a))
    return std::get_if<VariableId>(&b) && *variable == std::get<VariableId>(b);
  if(const auto* value = std::get_if<Value>(&a))
    return std::get_if<Value>(&b) && *value == std::get<Value>(b);
  return false; // Two ignored fields do not establish equality.
}

// F01 validates the catalog; replay the exact enforced-key premise rather than
// infer it from a hint, a statistic, or a currently unique database snapshot.
std::optional<std::size_t> target_key(const Table& table,
    const ForeignKeyConstraint& foreign, Budget& budget) {
  for(std::size_t i = 0; i < table.constraints.size(); ++i) {
    budget.take();
    const auto* key = std::get_if<UniqueConstraint>(&table.constraints[i]);
    if(!key || key->status != ConstraintStatus::enforced ||
        key->columns.size() != foreign.referenced_columns.size()) continue;
    bool same = true;
    for(const auto column : key->columns) {
      bool found = false;
      for(const auto referenced : foreign.referenced_columns) {
        budget.take();
        if(column == referenced) { found = true; break; }
      }
      if(!found) { same = false; break; }
    }
    if(same) return i; // Includes the genuine empty UNIQUE/FK key.
  }
  return {};
}

// The FK witness fixes every matched key value. Other parent fields impose no
// restriction only when ignored or independent private existential variables.
bool entailed(const Atom& source, const Atom& parent, const ForeignKeyConstraint& foreign,
    const std::vector<std::size_t>& uses, const std::vector<bool>& head, Budget& budget) {
  for(std::size_t i = 0; i < foreign.columns.size(); ++i)
    if(!same_term(source.terms[foreign.columns[i].value],
                 parent.terms[foreign.referenced_columns[i].value], budget)) return false;
  for(std::size_t field = 0; field < parent.terms.size(); ++field) {
    budget.take();
    bool key = false;
    for(const auto column : foreign.referenced_columns) {
      budget.take();
      if(column.value == field) { key = true; break; }
    }
    if(key || std::holds_alternative<IgnoredColumn>(parent.terms[field])) continue;
    const auto* variable = std::get_if<VariableId>(&parent.terms[field]);
    if(!variable || uses[variable->value] != 1 || head[variable->value]) return false;
  }
  return true;
}
} // namespace

struct Plan::Data {
  PhysicalPlan general, execution;
  Reason reason;
  std::vector<Elimination> eliminations;
  std::vector<OccurrenceId> occurrences;
  std::vector<VariableId> variables;
  Usage usage;
  std::optional<HeightCertificate> certificate;
};

const PhysicalPlan& Plan::general() const & noexcept { return data_->general; }
const PhysicalPlan& Plan::execution() const & noexcept { return data_->execution; }
Reason Plan::reason() const noexcept { return data_->reason; }
bool Plan::specialized() const noexcept { return reason() == Reason::specialized; }
std::span<const Elimination> Plan::eliminations() const & noexcept { return data_->eliminations; }
std::span<const OccurrenceId> Plan::occurrences() const & noexcept { return data_->occurrences; }
std::span<const VariableId> Plan::variables() const & noexcept { return data_->variables; }
const Usage& Plan::usage() const & noexcept { return data_->usage; }
const std::optional<HeightCertificate>& Plan::reduced_certificate() const & noexcept { return data_->certificate; }

Plan specialize(const PhysicalPlan& general, const Limits& limits) {
  Budget budget{limits.work}; budget.take();
  const auto& query = general.query();
  const auto& catalog = general.catalog();
  std::vector<bool> live(query.atoms.size(), true), head(query.variables.size(), false);
  std::vector<std::size_t> uses(query.variables.size(), 0);
  std::vector<Elimination> steps;
  Reason reason = general.normalized() ? Reason::normalized_sql :
      general.route() != PhysicalRoute::tree ? Reason::constant_route : Reason::no_match;
  if(reason == Reason::no_match) {
    for(const auto& atom : query.atoms) for(const auto& term : atom.terms) {
      budget.take();
      if(const auto* variable = std::get_if<VariableId>(&term)) ++uses[variable->value];
    }
    for(const auto& output : query.head) { budget.take(); head[output.variable.value] = true; }
    // Every removal uses a different still-live occurrence. Updating use counts
    // makes later private-variable guards refer to the actual current query.
    bool changed = true;
    while(changed) {
      changed = false;
      for(std::size_t removed = 0; removed < query.atoms.size(); ++removed) {
        budget.take();
        if(!live[removed]) continue;
        const auto& parent = query.atoms[removed];
        for(std::size_t witness = 0; witness < query.atoms.size() && live[removed]; ++witness) {
          budget.take();
          if(witness == removed || !live[witness]) continue;
          const auto& source = query.atoms[witness];
          const auto& constraints = catalog.tables[source.table.value].constraints;
          for(std::size_t f = 0; f < constraints.size(); ++f) {
            budget.take();
            const auto* foreign = std::get_if<ForeignKeyConstraint>(&constraints[f]);
            if(!foreign || foreign->status != ConstraintStatus::enforced ||
                foreign->referenced_table != parent.table) continue;
            const auto unique = target_key(catalog.tables[parent.table.value], *foreign, budget);
            if(!unique || !entailed(source, parent, *foreign, uses, head, budget)) continue;
            steps.push_back({OccurrenceId{removed}, OccurrenceId{witness}, f, *unique});
            live[removed] = false; changed = true;
            for(const auto& term : parent.terms) {
              budget.take();
              if(const auto* variable = std::get_if<VariableId>(&term)) --uses[variable->value];
            }
            break;
          }
        }
      }
    }
  }

  // Retain original IDs for inspection. Compact only the reduced query's IDs;
  // all physical source TableIds, schemas, constraints and row layouts stay put.
  std::vector<OccurrenceId> occurrences;
  std::vector<VariableId> variables;
  std::vector<std::optional<VariableId>> remap(query.variables.size());
  Query reduced;
  for(std::size_t i = 0; i < query.variables.size(); ++i) {
    budget.take();
    if(steps.empty() || uses[i]) {
      remap[i] = VariableId{variables.size()}; variables.push_back(VariableId{i});
      if(!steps.empty()) reduced.variables.push_back(query.variables[i]);
    }
  }
  for(std::size_t i = 0; i < query.atoms.size(); ++i) {
    budget.take();
    if(!live[i]) continue;
    occurrences.push_back(OccurrenceId{i});
    if(steps.empty()) continue;
    auto atom = query.atoms[i];
    for(auto& term : atom.terms) {
      budget.take();
      if(auto* variable = std::get_if<VariableId>(&term)) *variable = remap[variable->value].value();
    }
    reduced.atoms.push_back(std::move(atom));
  }
  Usage usage;
  PhysicalPlan execution = general;
  std::optional<HeightCertificate> certificate;
  if(!steps.empty()) {
    for(const auto& output : query.head) {
      budget.take();
      reduced.head.push_back({remap[output.variable.value].value(), output.alias});
    }
    auto searched = minimum_tree(catalog, reduced, limits.search);
    if(searched.status == OracleStatus::resource_limit)
      throw Error("key_search_limit", "reduced-query tree search exhausted its limits");
    if(searched.status != OracleStatus::proven_minimum || !searched.tree || !searched.certificate_verified)
      throw Error("key_rewrite", "reduced query has no independently verified tree");
    execution = lower_tree(catalog, reduced, *searched.tree, general.options(), limits.lowering);
    usage.search = searched.statistics; usage.lowering_work = execution.work();
    certificate = HeightCertificate{std::move(searched.algorithm), searched.minimum_height,
        std::move(searched.tree), std::move(searched.lower_bounds)};
    reason = Reason::specialized;
  }
  usage.work = budget.used;
  return Plan(std::make_shared<Plan::Data>(Plan::Data{general, std::move(execution), reason,
      std::move(steps), std::move(occurrences), std::move(variables), usage, std::move(certificate)}));
}
} // namespace crown::planner::keys
