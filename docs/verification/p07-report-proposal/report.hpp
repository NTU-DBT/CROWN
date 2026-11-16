#pragma once
// Excluded P07 report proposal; no installed/native API or proof constructor.
#include "../p07-api-proposal-2026-11-07.hpp"
#include "crown/io/search.hpp"

namespace crown::io::alternatives_proposal {
// Allocating export is outside advance quanta. Progress accepts the live owner,
// never caller-edited diagnostic aggregates. JSON itself conveys no authority.
[[nodiscard]] Json write_candidate_progress(const planner::CandidateProvider&);
[[nodiscard]] Json write_minimum_height_candidate(const planner::MinimumHeightCandidate&);
[[nodiscard]] Json write_candidate_snapshot(const planner::CandidateSnapshot&);
} // namespace crown::io::alternatives_proposal
