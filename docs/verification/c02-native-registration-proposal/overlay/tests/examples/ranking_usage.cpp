#include <optional>

#include "crown/planner/candidates.hpp"
#include "crown/planner/ranking.hpp"
#include "crown/runtime/physical.hpp"
#include "crown/runtime/ranking_evidence.hpp"

namespace c02_guide {
namespace pr = crown::planner::ranking;
namespace rr = crown::runtime::ranking;

[[nodiscard]] pr::Attempt height_only(
    const crown::planner::CandidateSnapshot& candidates) noexcept {
  pr::Request request{};
  request.policy = pr::Policy::height_only;
  request.fallback = pr::Fallback::require_evidence;
  return pr::rank(candidates, request);
}

[[nodiscard]] pr::Attempt current_native_depth(
    const crown::planner::CandidateSnapshot& candidates,
    const crown::runtime::PhysicalRuntime& owner) noexcept {
  pr::Request request{};
  request.policy = pr::Policy::committed_input_native_depth;
  request.fallback = pr::Fallback::height_only;
  auto attempt = rr::rank_current(candidates, owner, request);

  if (!attempt.result && attempt.stop == pr::Stop::evidence_unavailable) {
    return attempt;
  }
  if (attempt.result &&
      attempt.result->effective_policy() == pr::Policy::height_only) {
    const auto fallback_reasons = attempt.result->fallback_reasons();
    (void)fallback_reasons;
  }
  return attempt;
}

[[nodiscard]] std::optional<pr::Attempt> current_tuple_index_slots(
    const crown::planner::CandidateSnapshot& candidates,
    const crown::runtime::PhysicalRuntime& owner,
    const rr::RuntimeEvidence& retained,
    rr::Revalidation& current_check) noexcept {
  constexpr auto policy = pr::Policy::tuple_index_slots;
  current_check = rr::revalidate(retained, owner);
  if (current_check.boundary != 0 || !current_check.usable(policy)) {
    return std::nullopt;
  }

  pr::Request request{};
  request.policy = policy;
  request.fallback = pr::Fallback::require_evidence;
  const std::optional<pr::Evidence> as_of{retained.inputs()};
  return std::optional<pr::Attempt>{pr::rank(candidates, request, as_of)};
}
}  // namespace c02_guide
