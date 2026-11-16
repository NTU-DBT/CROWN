#include "crown/io/search.hpp"
#include "query_binding.hpp"

namespace crown::io {
namespace {
using namespace planner;
#define P06_ENUM_CASE(Type, Value) case Type::Value: return #Value
const char* name(SearchPhase value) noexcept {
  switch (value) {
    P06_ENUM_CASE(SearchPhase, admitted); P06_ENUM_CASE(SearchPhase, preprocess);
    P06_ENUM_CASE(SearchPhase, search); P06_ENUM_CASE(SearchPhase, build_incumbent);
    P06_ENUM_CASE(SearchPhase, validate_incumbent); P06_ENUM_CASE(SearchPhase, export_proof);
    P06_ENUM_CASE(SearchPhase, replay); P06_ENUM_CASE(SearchPhase, complete);
    P06_ENUM_CASE(SearchPhase, failed); P06_ENUM_CASE(SearchPhase, cancelled); P06_ENUM_CASE(SearchPhase, moved_from);
  }
  return "unknown";
}
const char* name(ReplayPhase value) noexcept {
  switch (value) {
    P06_ENUM_CASE(ReplayPhase, admitted); P06_ENUM_CASE(ReplayPhase, dispatch);
    P06_ENUM_CASE(ReplayPhase, validate_upper); P06_ENUM_CASE(ReplayPhase, build_scopes);
    P06_ENUM_CASE(ReplayPhase, classify_scope_orbits); P06_ENUM_CASE(ReplayPhase, index_claims);
    P06_ENUM_CASE(ReplayPhase, order_claims); P06_ENUM_CASE(ReplayPhase, prove_claim);
    P06_ENUM_CASE(ReplayPhase, match_root); P06_ENUM_CASE(ReplayPhase, complete);
    P06_ENUM_CASE(ReplayPhase, failed); P06_ENUM_CASE(ReplayPhase, cancelled); P06_ENUM_CASE(ReplayPhase, moved_from);
  }
  return "unknown";
}
const char* name(StopReason value) noexcept {
  switch (value) {
    P06_ENUM_CASE(StopReason, none); P06_ENUM_CASE(StopReason, quantum_work); P06_ENUM_CASE(StopReason, quantum_time);
    P06_ENUM_CASE(StopReason, total_work); P06_ENUM_CASE(StopReason, total_time); P06_ENUM_CASE(StopReason, depth_limit);
    P06_ENUM_CASE(StopReason, allocation_failure); P06_ENUM_CASE(StopReason, counter_overflow);
    P06_ENUM_CASE(StopReason, invalid_quantum); P06_ENUM_CASE(StopReason, invalid_certificate);
    P06_ENUM_CASE(StopReason, internal_failure); P06_ENUM_CASE(StopReason, complete);
    P06_ENUM_CASE(StopReason, cancelled); P06_ENUM_CASE(StopReason, moved_from);
  }
  return "unknown";
}
const char* name(ResultKind value) noexcept {
  switch (value) {
    P06_ENUM_CASE(ResultKind, unfinished); P06_ENUM_CASE(ResultKind, verified_optimum);
    P06_ENUM_CASE(ResultKind, verified_infeasible); P06_ENUM_CASE(ResultKind, failed);
  }
  return "unknown";
}
#undef P06_ENUM_CASE
Json counters(const WorkCounters& value) {
  return {{"attempted", value.attempted}, {"committed_transitions", value.committed_transitions},
          {"allocation_failures", value.allocation_failures}, {"active_nanoseconds", value.active_nanoseconds},
          {"current_depth", value.current_depth}, {"peak_depth", value.peak_depth}};
}
Json phase_limit(const PhaseCeiling& value) {
  return {{"work", value.work ? Json(*value.work) : Json(nullptr)},
          {"active_nanoseconds", value.active_time ? Json(value.active_time->count()) : Json(nullptr)}};
}
Json depth_limit(const std::optional<std::size_t>& value) { return value ? Json(*value) : Json(nullptr); }
Json checked_certificate(const HeightCertificate& proof, const SearchBinding& binding) {
  // Cold compatibility export copies proof payload and the returned certificate DOM.
  // The checked token is the authority; this temporary compatibility aggregate
  // cannot be supplied by callers of these typed overloads.
  OracleResult result;
  result.status = proof.tree ? OracleStatus::proven_minimum : OracleStatus::unsupported;
  result.minimum_height = proof.minimum_height; result.tree = proof.tree;
  result.lower_bounds = proof.lower_bounds; result.algorithm = proof.algorithm;
  result.certificate_verified = true;
  return write_oracle(result, binding.catalog(), binding.query()).at("certificate");
}
}  // namespace
Json write_validated_incumbent(const planner::ValidatedIncumbent& value) {
  const auto binding = value.binding();
  return {{"schema_version", 1}, {"artifact", "validated_incumbent"},
          {"accounting", "continuation_v1"}, {"query_binding", detail::query_binding(binding.catalog(), binding.query())},
          {"height_status", "valid_upper_bound"}, {"height_upper_bound", value.height()},
          {"tree", write_tree(value.tree(), binding.catalog(), binding.query())}, {"certificate", nullptr}};
}
Json write_verified_optimum(const planner::VerifiedOptimum& value) {
  return checked_certificate(value.certificate(), value.binding());
}
Json write_verified_infeasible(const planner::VerifiedInfeasible& value) {
  return checked_certificate(value.certificate(), value.binding());
}
Json write_search_progress(const planner::ExactSearch& owner) {
  const auto binding = owner.binding();
  const auto progress = owner.progress();
  const auto limits = owner.limits();
  const auto incumbent = owner.incumbent();
  return {{"schema_version", 1}, {"artifact", "search_progress"}, {"accounting", "continuation_v1"},
          {"query_binding", detail::query_binding(binding.catalog(), binding.query())},
          {"policy", owner.policy() == planner::SearchPolicy::strict ? "strict" : "best_found"},
          {"phase", name(progress.phase)}, {"stop_reason", name(progress.last_stop)}, {"result_kind", name(progress.result)},
          {"height_lower_bound", depth_limit(progress.heights.lower)}, {"height_upper_bound", depth_limit(progress.heights.upper)},
          {"lower_evidence", progress.heights.lower_evidence == planner::BoundEvidence::universal ? "universal" : "independently_checked"},
          {"infeasible", progress.heights.infeasible}, {"producer_complete", progress.producer_complete}, {"proof_complete", progress.proof_complete},
          {"producer", counters(progress.producer)}, {"replay", counters(progress.replay)}, {"limit_revision", progress.limit_revision},
          {"limits", {{"producer", phase_limit(limits.producer)}, {"replay", phase_limit(limits.replay)}, {"logical_depth", depth_limit(limits.logical_depth)}}},
          {"incumbent", incumbent ? write_validated_incumbent(*incumbent) : Json(nullptr)}, {"certificate", nullptr}};
}
Json write_replay_progress(const planner::CertificateReplay& owner) {
  const auto binding = owner.binding();
  const auto progress = owner.progress();
  const auto limits = owner.limits();
  return {{"schema_version", 1}, {"artifact", "certificate_replay_progress"}, {"accounting", "continuation_v1"},
          {"query_binding", detail::query_binding(binding.catalog(), binding.query())},
          {"phase", name(progress.phase)}, {"stop_reason", name(progress.last_stop)},
          {"complete", progress.complete}, {"valid", progress.valid}, {"checked_claims", progress.checked_claims},
          {"work", counters(progress.work)}, {"limit_revision", progress.limit_revision},
          {"limits", {{"phase", phase_limit(limits.limits)}, {"logical_depth", depth_limit(limits.logical_depth)}}},
          {"certificate", nullptr}};
}
}  // namespace crown::io
