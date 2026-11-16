#pragma once
#include "crown/io/oracle.hpp"
#include "crown/planner/search.hpp"

namespace crown::io {
// Allocating IO is outside advance quanta. Authority is accepted only through
// immutable checked types or the live owner, never caller-edited progress data.
[[nodiscard]] Json write_validated_incumbent(const planner::ValidatedIncumbent&);
[[nodiscard]] Json write_verified_optimum(const planner::VerifiedOptimum&);
[[nodiscard]] Json write_verified_infeasible(const planner::VerifiedInfeasible&);
[[nodiscard]] Json write_search_progress(const planner::ExactSearch&);
[[nodiscard]] Json write_replay_progress(const planner::CertificateReplay&);
}  // namespace crown::io
