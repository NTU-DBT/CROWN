#include "crown/io/recognition.hpp"

namespace crown::io {
namespace {
Json reduction_json(const planner::GyoResult& reduction, const Query& query) {
  auto witness = Json::array();
  for (const auto& step : reduction.witness) {
    const auto kind = step.kind == planner::ReductionKind::private_variable ? "remove_private_variable" : step.kind == planner::ReductionKind::contained_edge ? "remove_contained_edge" : "remove_empty_edge";
    Json item{{"kind",kind},{"edge",step.edge}};
    if (step.anchor) item["anchor"] = *step.anchor;
    if (step.variable) item["variable"] = query.variables.at(step.variable->value).name;
    witness.push_back(std::move(item));
  }
  auto core = Json::array();
  for (const auto& edge : reduction.failed_core) {
    auto scope = Json::array();
    for (const auto variable : edge.scope) scope.push_back(query.variables.at(variable.value).name);
    core.push_back({{"edge",edge.edge},{"scope",std::move(scope)}});
  }
  return {{"acyclic",reduction.acyclic},{"witness",std::move(witness)},{"failed_core",std::move(core)}};
}
}  // namespace
Json write_structural_analysis(const planner::StructuralAnalysis& analysis, const Query& query) {
  // Report the supplied structural witness; exact minimum height remains unchecked.
  const auto classification = analysis.query_class == planner::QueryClass::free_connex ? "free_connex" : analysis.query_class == planner::QueryClass::cyclic ? "cyclic" : "acyclic_non_free_connex";
  return {{"schema_version",1},{"query_class",classification},{"body",reduction_json(analysis.body,query)},
      {"augmented",reduction_json(analysis.augmented,query)},{"synthetic_head_edge",query.atoms.size()},{"height_status","not_checked"}};
}
}  // namespace crown::io
