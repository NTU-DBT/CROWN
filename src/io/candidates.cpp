#include "crown/io/candidates.hpp"
#include "crown/api/error.hpp"
#include "crown/io/residual.hpp"
#include "query_binding.hpp"

namespace crown::io {
namespace {
using namespace planner;
#define ENUM_CASE(Type, Value) case Type::Value: return #Value
const char* name(CandidatePhase value) {
  switch (value) {
    ENUM_CASE(CandidatePhase, admitted); ENUM_CASE(CandidatePhase, exact_seed);
    ENUM_CASE(CandidatePhase, residual_seed); ENUM_CASE(CandidatePhase, enumerate);
    ENUM_CASE(CandidatePhase, validate); ENUM_CASE(CandidatePhase, canonicalize);
    ENUM_CASE(CandidatePhase, publish); ENUM_CASE(CandidatePhase, exhausted);
    ENUM_CASE(CandidatePhase, failed); ENUM_CASE(CandidatePhase, cancelled);
    ENUM_CASE(CandidatePhase, moved_from);
  }
  throw Error("invalid_candidate_report", "unknown candidate phase");
}
const char* name(CandidateStop value) {
  switch (value) {
    ENUM_CASE(CandidateStop, none); ENUM_CASE(CandidateStop, candidate_ready);
    ENUM_CASE(CandidateStop, quantum_work); ENUM_CASE(CandidateStop, quantum_time);
    ENUM_CASE(CandidateStop, total_work); ENUM_CASE(CandidateStop, total_time);
    ENUM_CASE(CandidateStop, depth_limit); ENUM_CASE(CandidateStop, record_limit);
    ENUM_CASE(CandidateStop, cell_limit); ENUM_CASE(CandidateStop, candidate_capacity);
    ENUM_CASE(CandidateStop, allocation_failure); ENUM_CASE(CandidateStop, counter_overflow);
    ENUM_CASE(CandidateStop, invalid_quantum); ENUM_CASE(CandidateStop, internal_failure);
    ENUM_CASE(CandidateStop, exhausted); ENUM_CASE(CandidateStop, cancelled);
    ENUM_CASE(CandidateStop, moved_from);
  }
  throw Error("invalid_candidate_report", "unknown candidate stop");
}
const char* name(CandidateSource value) {
  switch (value) {
    ENUM_CASE(CandidateSource, exact_witness); ENUM_CASE(CandidateSource, residual_seed);
    ENUM_CASE(CandidateSource, normal_form);
    ENUM_CASE(CandidateSource, supplied_proposal);
  }
  throw Error("invalid_candidate_report", "unknown candidate source");
}
const char* name(ResidualOrigin value) {
  switch (value) {
    ENUM_CASE(ResidualOrigin, hierarchy_seed); ENUM_CASE(ResidualOrigin, native_leaf);
    ENUM_CASE(ResidualOrigin, generalized_leaf); ENUM_CASE(ResidualOrigin, generalized_graft);
    ENUM_CASE(ResidualOrigin, exact_repair); ENUM_CASE(ResidualOrigin, exact_original);
  }
  throw Error("invalid_candidate_report", "unknown residual origin");
}
#undef ENUM_CASE
const char* family(CandidateFamily value) {
  switch (value) {
    case CandidateFamily::exact_seed_residual_seed_normal_form_v1:
      return "exact-seed/residual-seed/normal-form-v1";
    case CandidateFamily::finite_proposals_v1: return "finite-proposals-v1";
  }
  throw Error("invalid_candidate_report", "unknown candidate family");
}
const char* exhaustion_scope(CandidateFamily value) {
  switch (value) {
    case CandidateFamily::exact_seed_residual_seed_normal_form_v1:
      return "admitted_seeds_and_normal_form_v1_only";
    case CandidateFamily::finite_proposals_v1: return "supplied_finite_proposals_v1_only";
  }
  throw Error("invalid_candidate_report", "unknown candidate family");
}
Json context(const CandidateContext& c) {
  if (c.updates != CandidateUpdateProfile::mixed_full_row_set_v1 ||
      c.arithmetic != "exact-nonnull-v1" || c.planner != "crown-tree-v1" ||
      c.optimization != "structural-height-v1" || c.cost_model != "no-cost-v1" ||
      c.canonicalization != "structural-tree-key-v1")
    throw Error("invalid_candidate_report", "unsupported candidate context");
  return {{"updates", "mixed-full-row-set-v1"}, {"arithmetic", c.arithmetic},
          {"planner", c.planner}, {"optimization", c.optimization},
          {"cost_model", c.cost_model}, {"canonicalization", c.canonicalization}};
}
// Each report owns another catalog/query/proof export. Rendering does not
// advance a provider or turn the returned editable JSON into a checked token.
Json common(const char* artifact, const VerifiedOptimum& proof,
            const CandidateContext& c, CandidateFamily f) {
  const auto binding = proof.binding();
  return {{"schema_version", 1}, {"artifact", artifact}, {"accounting", "continuation_v1"},
          {"query_binding", detail::query_binding(binding.catalog(), binding.query())},
          {"context", context(c)}, {"family", family(f)},
          {"optimization_scope", "structural_height_only"},
          {"original_proof", {{"scope", "original_query"},
                              {"certificate", write_verified_optimum(proof)}}}};
}
Json counters(const WorkCounters& v) {
  return {{"attempted", v.attempted}, {"committed_transitions", v.committed_transitions},
          {"allocation_failures", v.allocation_failures}, {"active_nanoseconds", v.active_nanoseconds},
          {"current_depth", v.current_depth}, {"peak_depth", v.peak_depth}};
}
template<class T> Json optional_number(const std::optional<T>& v) { return v ? Json(*v) : Json(nullptr); }
Json limits(const CandidateLimits& v) {
  return {{"enumeration", {{"work", optional_number(v.enumeration.work)},
          {"active_nanoseconds", v.enumeration.active_time ? Json(v.enumeration.active_time->count()) : Json(nullptr)}}},
          {"logical_depth", optional_number(v.logical_depth)}, {"records", optional_number(v.records)},
          {"cells", optional_number(v.cells)}, {"retained_candidates", optional_number(v.retained_candidates)}};
}
}
Json write_minimum_height_candidate(const planner::MinimumHeightCandidate& value) {
  if (!value.valid()) throw Error("invalid_candidate_report", "candidate was moved from");
  const auto proof = value.original_proof();
  if (value.height() != proof.height() ||
      detail::query_binding(value.catalog(), value.query()) !=
          detail::query_binding(proof.binding().catalog(), proof.binding().query()))
    throw Error("invalid_candidate_report", "candidate height or binding differs from supplied proof");
  const auto p = value.provenance();
  auto result = common("minimum_height_candidate", proof, value.context(), p.family);
  result["height_relationship"] = "checked_upper_matches_supplied_original_minimum";
  result["checked_upper"] = {{"proof_status", "checked_upper_only"}, {"height", value.height()},
                            {"tree", write_tree(value.tree(), value.catalog(), value.query())}};
  result["structural_key"] = value.structural_key();
  result["provenance"] = {{"source", name(p.source)}, {"sequence", p.sequence},
      {"residual_last_step", p.residual_last_step ? Json(name(*p.residual_last_step)) : Json(nullptr)},
      {"residual_trace", p.residual_trace ? write_residual_trace(*p.residual_trace) : Json(nullptr)}};
  return result;
}
Json write_candidate_progress(const planner::CandidateProvider& owner) {
  const auto p = owner.progress();
  auto result = common("candidate_progress", owner.original_proof(), owner.context(), p.family);
  result["report_role"] = "enumeration_diagnostic";
  result["phase"] = name(p.phase); result["stop_reason"] = name(p.last_stop);
  result["verified_original_height"] = optional_number(p.verified_original_height);
  result["family_exhausted"] = p.family_exhausted;
  result["exhaustion_scope"] = exhaustion_scope(p.family);
  result["candidate_count"] = p.candidate_count;
  result["work"] = counters(p.work);
  const auto& s = p.statistics;
  result["statistics"] = {{"proposed", s.proposed}, {"rejected", s.rejected}, {"taller", s.taller},
      {"duplicates", s.duplicates}, {"published", s.published}, {"topologies", s.topologies},
      {"scope_tuples", s.scope_tuples}, {"cache_seeded", s.cache_seeded}};
  result["records"] = p.records; result["cells"] = p.cells;
  result["limit_revision"] = p.limit_revision; result["limits"] = limits(owner.limits());
  return result;
}
Json write_candidate_snapshot(const planner::CandidateSnapshot& value) {
  if (!value.valid()) throw Error("invalid_candidate_report", "snapshot was moved from");
  auto result = common("candidate_snapshot", value.original_proof(), value.context(), value.family());
  result["family_exhausted"] = value.family_exhausted();
  result["exhaustion_scope"] = exhaustion_scope(value.family());
  result["candidate_count"] = value.candidate_count();
  auto prefix = Json::array();
  for (std::size_t i = 0; i < value.candidate_count(); ++i) {
    const auto candidate = value.candidate(i);
    if (!candidate) throw Error("invalid_candidate_report", "snapshot prefix has a missing candidate");
    prefix.push_back(write_minimum_height_candidate(*candidate));
  }
  result["prefix"] = std::move(prefix);
  return result;
}
} // namespace crown::io
