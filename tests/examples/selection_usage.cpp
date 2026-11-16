#include "crown/runtime/selection.hpp"

namespace crown::examples {
// Obtaining the typed proof/provider snapshot and initializing an owner remain
// separate caller operations. No selected plan is installed in that owner.
planner::selection::Attempt choose_height(const planner::CandidateSnapshot& candidates) {
  planner::selection::Request request;
  request.policy = planner::selection::Policy::height_only;
  request.family = planner::selection::FamilyPolicy::retained_prefix;
  return planner::selection::select(candidates, planner::selection::DirectCQ{}, request);
}
runtime::selection::Attempt choose_current(const planner::CandidateSnapshot& candidates,
    const runtime::PhysicalRuntime& owner, planner::selection::PlanCache& cache) {
  planner::selection::Request request;
  request.policy = planner::selection::Policy::committed_input_native_depth;
  request.fallback = planner::ranking::Fallback::height_only;
  request.constraint = planner::selection::TupleIndexSlotLimit{"32"};
  request.limits.aggregate.work = 1'000'000;
  // Slots are a unitless source-cardinality proxy. This is not a byte cap.
  return runtime::selection::select_current(candidates,
      planner::selection::PhysicalBasis{owner.plan()}, owner, request, {}, &cache,
      planner::selection::CacheUse::read_write);
}
planner::selection::Attempt choose_as_of(const planner::CandidateSnapshot& candidates,
    const PhysicalPlan& basis, const planner::ranking::Evidence& evidence) {
  planner::selection::Request request;
  request.policy = planner::selection::Policy::tuple_index_slots;
  request.fallback = planner::ranking::Fallback::require_evidence;
  return planner::selection::select(candidates, planner::selection::PhysicalBasis{basis}, request, evidence);
}
} // namespace crown::examples
