#include "crown/io/residual.hpp"

#include "crown/api/error.hpp"
#include "query_binding.hpp"

namespace crown::io {
namespace {
using namespace planner;

#define RESIDUAL_ENUM_CASE(Type, Value) case Type::Value: return #Value
const char* name(ResidualMode value) noexcept {
  switch (value) {
    RESIDUAL_ENUM_CASE(ResidualMode, candidates_with_exact_repair);
    RESIDUAL_ENUM_CASE(ResidualMode, require_exact_original);
  }
  return "unknown";
}
const char* name(ResidualOrigin value) noexcept {
  switch (value) {
    RESIDUAL_ENUM_CASE(ResidualOrigin, hierarchy_seed);
    RESIDUAL_ENUM_CASE(ResidualOrigin, native_leaf);
    RESIDUAL_ENUM_CASE(ResidualOrigin, generalized_leaf);
    RESIDUAL_ENUM_CASE(ResidualOrigin, generalized_graft);
    RESIDUAL_ENUM_CASE(ResidualOrigin, exact_repair);
    RESIDUAL_ENUM_CASE(ResidualOrigin, exact_original);
  }
  return "unknown";
}
const char* name(ResidualPhase value) noexcept {
  switch (value) {
    RESIDUAL_ENUM_CASE(ResidualPhase, admitted);
    RESIDUAL_ENUM_CASE(ResidualPhase, scopes);
    RESIDUAL_ENUM_CASE(ResidualPhase, recognize);
    RESIDUAL_ENUM_CASE(ResidualPhase, eligibility);
    RESIDUAL_ENUM_CASE(ResidualPhase, delete_ears);
    RESIDUAL_ENUM_CASE(ResidualPhase, seal_layer);
    RESIDUAL_ENUM_CASE(ResidualPhase, trace_replay);
    RESIDUAL_ENUM_CASE(ResidualPhase, seed);
    RESIDUAL_ENUM_CASE(ResidualPhase, restore);
    RESIDUAL_ENUM_CASE(ResidualPhase, validate_candidate);
    RESIDUAL_ENUM_CASE(ResidualPhase, repair);
    RESIDUAL_ENUM_CASE(ResidualPhase, exact_original);
    RESIDUAL_ENUM_CASE(ResidualPhase, complete);
    RESIDUAL_ENUM_CASE(ResidualPhase, failed);
    RESIDUAL_ENUM_CASE(ResidualPhase, cancelled);
    RESIDUAL_ENUM_CASE(ResidualPhase, moved_from);
  }
  return "unknown";
}
const char* name(ResidualResult value) noexcept {
  switch (value) {
    RESIDUAL_ENUM_CASE(ResidualResult, unfinished);
    RESIDUAL_ENUM_CASE(ResidualResult, checked_candidate);
    RESIDUAL_ENUM_CASE(ResidualResult, verified_optimum);
    RESIDUAL_ENUM_CASE(ResidualResult, verified_infeasible);
    RESIDUAL_ENUM_CASE(ResidualResult, failed);
  }
  return "unknown";
}
const char* name(ResidualProofStatus value) noexcept {
  switch (value) {
    RESIDUAL_ENUM_CASE(ResidualProofStatus, none);
    RESIDUAL_ENUM_CASE(ResidualProofStatus, trace_verified);
    RESIDUAL_ENUM_CASE(ResidualProofStatus, checked_upper_only);
    RESIDUAL_ENUM_CASE(ResidualProofStatus, exact_original_verified);
  }
  return "unknown";
}
const char* name(ResidualStopReason value) noexcept {
  switch (value) {
    RESIDUAL_ENUM_CASE(ResidualStopReason, none);
    RESIDUAL_ENUM_CASE(ResidualStopReason, quantum_work);
    RESIDUAL_ENUM_CASE(ResidualStopReason, quantum_time);
    RESIDUAL_ENUM_CASE(ResidualStopReason, total_work);
    RESIDUAL_ENUM_CASE(ResidualStopReason, total_time);
    RESIDUAL_ENUM_CASE(ResidualStopReason, depth_limit);
    RESIDUAL_ENUM_CASE(ResidualStopReason, record_limit);
    RESIDUAL_ENUM_CASE(ResidualStopReason, cell_limit);
    RESIDUAL_ENUM_CASE(ResidualStopReason, exact_limit);
    RESIDUAL_ENUM_CASE(ResidualStopReason, allocation_failure);
    RESIDUAL_ENUM_CASE(ResidualStopReason, counter_overflow);
    RESIDUAL_ENUM_CASE(ResidualStopReason, invalid_quantum);
    RESIDUAL_ENUM_CASE(ResidualStopReason, invalid_trace);
    RESIDUAL_ENUM_CASE(ResidualStopReason, internal_failure);
    RESIDUAL_ENUM_CASE(ResidualStopReason, complete);
    RESIDUAL_ENUM_CASE(ResidualStopReason, cancelled);
    RESIDUAL_ENUM_CASE(ResidualStopReason, moved_from);
  }
  return "unknown";
}
const char* name(ResidualTerminal value) noexcept {
  switch (value) {
    RESIDUAL_ENUM_CASE(ResidualTerminal, empty_body);
    RESIDUAL_ENUM_CASE(ResidualTerminal, hierarchical);
    RESIDUAL_ENUM_CASE(ResidualTerminal, stalled);
  }
  return "unknown";
}
const char* name(EarCondition value) noexcept {
  switch (value) {
    RESIDUAL_ENUM_CASE(EarCondition, first);
    RESIDUAL_ENUM_CASE(EarCondition, second);
    RESIDUAL_ENUM_CASE(EarCondition, both);
  }
  return "unknown";
}
const char* name(SearchPhase value) noexcept {
  switch (value) {
    RESIDUAL_ENUM_CASE(SearchPhase, admitted);
    RESIDUAL_ENUM_CASE(SearchPhase, preprocess);
    RESIDUAL_ENUM_CASE(SearchPhase, search);
    RESIDUAL_ENUM_CASE(SearchPhase, build_incumbent);
    RESIDUAL_ENUM_CASE(SearchPhase, validate_incumbent);
    RESIDUAL_ENUM_CASE(SearchPhase, export_proof);
    RESIDUAL_ENUM_CASE(SearchPhase, replay);
    RESIDUAL_ENUM_CASE(SearchPhase, complete);
    RESIDUAL_ENUM_CASE(SearchPhase, failed);
    RESIDUAL_ENUM_CASE(SearchPhase, cancelled);
    RESIDUAL_ENUM_CASE(SearchPhase, moved_from);
  }
  return "unknown";
}
const char* name(StopReason value) noexcept {
  switch (value) {
    RESIDUAL_ENUM_CASE(StopReason, none);
    RESIDUAL_ENUM_CASE(StopReason, quantum_work);
    RESIDUAL_ENUM_CASE(StopReason, quantum_time);
    RESIDUAL_ENUM_CASE(StopReason, total_work);
    RESIDUAL_ENUM_CASE(StopReason, total_time);
    RESIDUAL_ENUM_CASE(StopReason, depth_limit);
    RESIDUAL_ENUM_CASE(StopReason, allocation_failure);
    RESIDUAL_ENUM_CASE(StopReason, counter_overflow);
    RESIDUAL_ENUM_CASE(StopReason, invalid_quantum);
    RESIDUAL_ENUM_CASE(StopReason, invalid_certificate);
    RESIDUAL_ENUM_CASE(StopReason, internal_failure);
    RESIDUAL_ENUM_CASE(StopReason, complete);
    RESIDUAL_ENUM_CASE(StopReason, cancelled);
    RESIDUAL_ENUM_CASE(StopReason, moved_from);
  }
  return "unknown";
}
const char* name(ResultKind value) noexcept {
  switch (value) {
    RESIDUAL_ENUM_CASE(ResultKind, unfinished);
    RESIDUAL_ENUM_CASE(ResultKind, verified_optimum);
    RESIDUAL_ENUM_CASE(ResultKind, verified_infeasible);
    RESIDUAL_ENUM_CASE(ResultKind, failed);
  }
  return "unknown";
}
const char* name(BoundEvidence value) noexcept {
  switch (value) {
    RESIDUAL_ENUM_CASE(BoundEvidence, universal);
    RESIDUAL_ENUM_CASE(BoundEvidence, independently_checked);
  }
  return "unknown";
}
#undef RESIDUAL_ENUM_CASE

Json index_set(const VariableSet& values) {
  auto result = Json::array();
  for (const auto value : values) result.push_back(value.value);
  return result;
}
Json index_list(const std::vector<std::size_t>& values) {
  auto result = Json::array();
  for (const auto value : values) result.push_back(value);
  return result;
}
Json optional_index(const std::optional<std::size_t>& value) {
  return value ? Json(*value) : Json(nullptr);
}
Json optional_variable(const std::optional<VariableId>& value) {
  return value ? Json(value->value) : Json(nullptr);
}
Json counters(const WorkCounters& value) {
  return {{"attempted", value.attempted},
          {"committed_transitions", value.committed_transitions},
          {"allocation_failures", value.allocation_failures},
          {"active_nanoseconds", value.active_nanoseconds},
          {"current_depth", value.current_depth},
          {"peak_depth", value.peak_depth}};
}
Json phase_limit(const PhaseCeiling& value) {
  return {{"work", value.work ? Json(*value.work) : Json(nullptr)},
          {"active_nanoseconds", value.active_time ? Json(value.active_time->count()) : Json(nullptr)}};
}
Json depth_limit(const std::optional<std::size_t>& value) {
  return value ? Json(*value) : Json(nullptr);
}
Json statistics(const ResidualStatistics& value) {
  return {{"hierarchy_tests", value.hierarchy_tests},
          {"rounds", value.rounds},
          {"eligibility_pairs", value.eligibility_pairs},
          {"deletions", value.deletions},
          {"restorations", value.restorations},
          {"drafts", value.drafts},
          {"rejected_drafts", value.rejected_drafts},
          {"generalized_grafts", value.generalized_grafts},
          {"exact_repairs", value.exact_repairs},
          {"original_exact_runs", value.original_exact_runs},
          {"candidate_publications", value.candidate_publications},
          {"admissions", value.admissions}};
}
Json exact_statistics(const SearchStatistics& value) {
  return {{"work", value.work},
          {"states", value.states},
          {"partitions", value.partitions},
          {"candidates", value.candidates},
          {"cache_hits", value.cache_hits},
          {"certificate_work", value.certificate_work},
          {"hierarchy_tests", value.hierarchy_tests},
          {"hierarchy_hits", value.hierarchy_hits},
          {"singleton_hits", value.singleton_hits},
          {"empty_body_hits", value.empty_body_hits},
          {"component_splits", value.component_splits},
          {"symmetry_skips", value.symmetry_skips},
          {"bound_prunes", value.bound_prunes}};
}
// Compatibility path builds/validates a full binding Document/DOM before
// copying out its query subtree; that cost is outside residual work quanta.
Json query_payload(const Catalog& catalog, const Query& query) {
  return detail::query_binding(catalog, query).at("query");
}
Json ear_anchor(const EarAnchor& value) {
  return {{"occurrence", value.occurrence}, {"condition", name(value.condition)}};
}
Json ear(const EarRecord& value) {
  auto anchors = Json::array();
  for (const auto& anchor : value.anchors) anchors.push_back(ear_anchor(anchor));
  return {{"occurrence", value.occurrence},
          {"shared", index_set(value.shared)},
          {"unique", index_set(value.unique)},
          {"anchors", std::move(anchors)}};
}
Json layer(const ResidualLayer& value) {
  auto ears = Json::array();
  for (const auto& item : value.ears) ears.push_back(ear(item));
  auto deletions = Json::array();
  for (const auto& item : value.deletions) {
    deletions.push_back({{"occurrence", item.occurrence}, {"anchor_occurrence", item.anchor}});
  }
  return {{"members", index_list(value.members)},
          {"variables", index_set(value.variables)},
          {"head", index_set(value.head)},
          {"unique", index_set(value.unique)},
          {"ears", std::move(ears)},
          {"deletions", std::move(deletions)},
          {"remaining", index_list(value.remaining)},
          {"residual_head", index_set(value.residual_head)}};
}
Json trace_view(const ResidualTrace& value) {
  const auto& record = value.record();
  const auto& view = record.terminal_view;
  auto original_variables = Json::array();
  for (const auto variable : view.original_variables) original_variables.push_back(variable.value);
  auto occurrence_to_local = Json::array();
  for (const auto local : view.occurrence_to_local) occurrence_to_local.push_back(optional_index(local));
  auto variable_to_local = Json::array();
  for (const auto local : view.variable_to_local) variable_to_local.push_back(optional_variable(local));
  return {{"original_occurrences", index_list(view.original_occurrences)},
          {"original_variables", std::move(original_variables)},
          {"occurrence_to_local", std::move(occurrence_to_local)},
          {"variable_to_local", std::move(variable_to_local)},
          {"query", query_payload(value.catalog(), view.query)}};
}
// The immutable handle certifies this frozen trace only, not tree height.
Json trace_document(const ResidualTrace& value) {
  if (!value.valid()) throw Error("invalid_residual_handle", "residual trace was moved from");
  const auto& record = value.record();
  auto scopes = Json::array();
  for (const auto& scope : record.original_scopes) scopes.push_back(index_set(scope));
  auto layers = Json::array();
  for (const auto& item : record.layers) layers.push_back(layer(item));
  return {{"schema_version", 1},
          {"artifact", "residual_trace"},
          {"accounting", "continuation_v1"},
          {"query_binding", detail::query_binding(value.catalog(), value.query())},
          {"audit_scope", "frozen_residual_trace_only"},
          {"trace_verified", true},
          {"trace_version", record.version},
          {"original_scopes", std::move(scopes)},
          {"layers", std::move(layers)},
          {"terminal_members", index_list(record.terminal_members)},
          {"terminal_head", index_set(record.terminal_head)},
          {"terminal", name(record.terminal)},
          {"terminal_view", trace_view(value)}};
}
// A typed checked upper remains upper-only; exact original proof is separate.
Json candidate_document(const ResidualCandidate& value) {
  if (!value.valid()) throw Error("invalid_residual_handle", "residual candidate was moved from");
  const auto& catalog = value.catalog();
  const auto& query = value.query();
  return {{"schema_version", 1},
          {"artifact", "residual_candidate"},
          {"accounting", "continuation_v1"},
          {"query_binding", detail::query_binding(catalog, query)},
          {"proof_status", "checked_upper_only"},
          {"height_status", "valid_upper_bound"},
          {"height_upper_bound", value.height()},
          {"origin", name(value.origin())},
          {"tree", write_tree(value.tree(), catalog, query)},
          {"certificate", nullptr}};
}
Json exact_diagnostic(const SearchProgress& value, bool original_scope) {
  return {{"scope_original", original_scope},
          {"phase", name(value.phase)},
          {"stop_reason", name(value.last_stop)},
          {"result_kind", name(value.result)},
          {"height_lower_bound", optional_index(value.heights.lower)},
          {"height_upper_bound", optional_index(value.heights.upper)},
          {"lower_evidence", name(value.heights.lower_evidence)},
          {"infeasible", value.heights.infeasible},
          {"producer_complete", value.producer_complete},
          {"proof_complete", value.proof_complete},
          {"producer", counters(value.producer)},
          {"replay", counters(value.replay)},
          {"structural", exact_statistics(value.structural)},
          {"limit_revision", value.limit_revision}};
}
Json residual_limits(const ResidualLimits& value) {
  return {{"residual", phase_limit(value.residual)},
          {"logical_depth", depth_limit(value.logical_depth)},
          {"record_limit", value.record_limit ? Json(*value.record_limit) : Json(nullptr)},
          {"cell_limit", value.cell_limit ? Json(*value.cell_limit) : Json(nullptr)},
          {"exact", {{"producer", phase_limit(value.exact.producer)},
                      {"replay", phase_limit(value.exact.replay)},
                      {"logical_depth", depth_limit(value.exact.logical_depth)}}}};
}
}  // namespace

Json write_residual_trace(const planner::ResidualTrace& value) {
  return trace_document(value);
}

Json write_residual_candidate(const planner::ResidualCandidate& value) {
  return candidate_document(value);
}

// Exclusive diagnostic export: no advance/replay, but ordinary allocating DOM
// construction and nested copies have no final byte/item cap in this API.
Json write_residual_progress(const planner::ResidualSearch& owner) {
  const auto& catalog = owner.catalog();
  const auto& query = owner.query();
  const auto options = owner.options();
  const auto progress = owner.progress();
  const auto trace = owner.trace();
  const auto candidate = owner.candidate();
  const auto optimum = owner.exact_original();
  const auto infeasibility = owner.infeasibility();
  if (optimum && infeasibility) {
    throw Error("invalid_residual_authority", "residual owner published optimum and infeasibility together");
  }
  Json certificate = nullptr;
  if (optimum) certificate = write_verified_optimum(*optimum);
  else if (infeasibility) certificate = write_verified_infeasible(*infeasibility);

  const auto& exact = progress.exact_progress;
  return {{"schema_version", 1},
          {"artifact", "residual_search_progress"},
          {"accounting", "continuation_v1"},
          {"query_binding", detail::query_binding(catalog, query)},
          {"mode", name(options.mode)},
          {"phase", name(progress.phase)},
          {"stop_reason", name(progress.last_stop)},
          {"exact_stop_reason", name(progress.exact_stop)},
          {"result", name(progress.result)},
          {"proof_status", name(progress.proof_status)},
          {"height_lower_bound", optional_index(progress.heights.lower)},
          {"height_upper_bound", optional_index(progress.heights.upper)},
          {"lower_evidence", name(progress.heights.lower_evidence)},
          {"infeasible", progress.heights.infeasible},
          {"trace_complete", progress.trace_complete},
          {"trace_verified", progress.trace_verified},
          {"exact_scope_original", progress.exact_scope_original},
          {"work", counters(progress.work)},
          {"statistics", statistics(progress.statistics)},
          {"records", progress.records},
          {"cells", progress.cells},
          {"limit_revision", progress.limit_revision},
          {"limits", residual_limits(options.limits)},
          {"exact_diagnostic", exact_diagnostic(exact, progress.exact_scope_original)},
          {"trace", trace ? trace_document(*trace) : Json(nullptr)},
          {"candidate", candidate ? candidate_document(*candidate) : Json(nullptr)},
          {"certificate", std::move(certificate)}};
}
}  // namespace crown::io
