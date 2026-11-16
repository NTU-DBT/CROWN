#include "crown/planner/recognize.hpp"

#include "crown/api/error.hpp"
#include <limits>
#include <map>
#include <utility>

namespace crown::planner {
namespace {
struct Limit {};
// Selected reduction/containment steps only; validation and container work
// retain their own costs. Exhaustion publishes no partial classification.
struct Budget {
  RecognitionLimits limits;
  std::uint64_t work = 0;
  void charge() {
    if (work == std::numeric_limits<std::uint64_t>::max() || (limits.work_limit && work >= *limits.work_limit)) throw Limit{};
    ++work;
  }
};
bool contains(const Scope& larger, const Scope& smaller, Budget& budget) {
  auto large = larger.begin(), small = smaller.begin();
  while (small != smaller.end()) {
    budget.charge();
    if (large == larger.end() || *small < *large) return false;
    if (*large < *small) ++large;
    else { ++large; ++small; }
  }
  return true;
}
// Restart the ordered passes after each deletion to keep the witness stable.
// These scope copies are compiler scratch, not mutable-input elimination.
GyoResult reduce(const std::vector<Scope>& scopes, Budget& budget) {
  std::vector<ResidualEdge> remaining;
  for (std::size_t i = 0; i < scopes.size(); ++i) {
    budget.charge();
    for (const auto variable : scopes[i]) { static_cast<void>(variable); budget.charge(); }
    remaining.push_back({i,scopes[i]});
  }
  GyoResult result{false, {}, {}};
  while (!remaining.empty()) {
    budget.charge();
    bool changed = false;
    for (std::size_t i = 0; i < remaining.size(); ++i) {
      budget.charge();
      if (remaining[i].scope.empty()) {
        result.witness.push_back({ReductionKind::empty_edge, remaining[i].edge, {}, {}});
        remaining.erase(remaining.begin() + static_cast<std::ptrdiff_t>(i));
        changed = true;
        break;
      }
    }
    if (changed) continue;
    std::map<VariableId, std::size_t> counts;
    for (const auto& edge : remaining) for (const auto variable : edge.scope) { budget.charge(); ++counts[variable]; }
    for (auto& edge : remaining) {
      for (const auto variable : edge.scope) {
        budget.charge();
        if (counts.at(variable) == 1) {
          result.witness.push_back({ReductionKind::private_variable, edge.edge, {}, variable});
          edge.scope.erase(variable);
          changed = true;
          break;
        }
      }
      if (changed) break;
    }
    if (changed) continue;
    for (std::size_t i = 0; i < remaining.size() && !changed; ++i) {
      for (std::size_t j = 0; j < remaining.size(); ++j) {
        budget.charge();
        if (i != j && contains(remaining[j].scope,remaining[i].scope,budget)) {
          result.witness.push_back({ReductionKind::contained_edge, remaining[i].edge, remaining[j].edge, {}});
          remaining.erase(remaining.begin() + static_cast<std::ptrdiff_t>(i));
          changed = true;
          break;
        }
      }
    }
    if (!changed) break;
  }
  result.acyclic = remaining.empty();
  result.failed_core = std::move(remaining);
  return result;
}
}  // namespace

GyoResult gyo_reduce(const std::vector<Scope>& scopes) {
  Budget budget{{std::nullopt}};
  try { return reduce(scopes,budget); }
  catch (const Limit&) { throw Error("resource_limit","GYO work counter exhausted"); }
}

StructuralAnalysis analyze(const Catalog& catalog, const Query& query) {
  auto run = analyze_bounded(catalog,query,{std::nullopt});
  if (!run.analysis) throw Error("resource_limit","GYO work counter exhausted");
  return std::move(*run.analysis);
}

RecognitionRun analyze_bounded(const Catalog& catalog, const Query& query, RecognitionLimits limits) {
  validate(catalog, query);
  Budget budget{limits};
  try {
    budget.charge();
    std::vector<Scope> scopes;
    for (const auto& atom : query.atoms) {
      budget.charge();
      Scope scope;
      for (const auto& term : atom.terms) { budget.charge(); if (const auto* variable = std::get_if<VariableId>(&term)) scope.insert(*variable); }
      scopes.push_back(std::move(scope));
    }
    auto body = reduce(scopes,budget);
    Scope head;
    for (const auto& output : query.head) { budget.charge(); head.insert(output.variable); }
    // Recognition only: this edge never enters a runtime plan or database.
    scopes.push_back(std::move(head));
    auto augmented = reduce(scopes,budget);
    const auto classification = !body.acyclic ? QueryClass::cyclic : augmented.acyclic ? QueryClass::free_connex : QueryClass::acyclic_non_free_connex;
    return {StructuralAnalysis{classification,std::move(body),std::move(augmented)},budget.work};
  } catch (const Limit&) { return {std::nullopt,budget.work}; }
}
}  // namespace crown::planner
