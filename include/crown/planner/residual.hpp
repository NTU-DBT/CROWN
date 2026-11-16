#pragma once

#include "crown/planner/search.hpp"

#include <memory>
#include <optional>
#include <string_view>

namespace crown::planner {
namespace residual_detail {
struct TraceData;
struct CandidateData;
struct ArtifactFactory;
}

// Candidate mode may finish with a checked upper; the default also completes
// original-query exact proof. Both modes use original exact fallback if needed.
enum class ResidualMode { candidates_with_exact_repair, require_exact_original };
// Last successful tree-construction step, independent of exactness. Earlier
// graft/repair activity remains in statistics even after later native restores.
enum class ResidualOrigin { hierarchy_seed, native_leaf, generalized_leaf, generalized_graft, exact_repair, exact_original };
enum class ResidualPhase {
  admitted, scopes, recognize, eligibility, delete_ears, seal_layer, trace_replay,
  seed, restore, validate_candidate, repair, exact_original, complete, failed, cancelled, moved_from
};
enum class ResidualResult { unfinished, checked_candidate, verified_optimum, verified_infeasible, failed };
enum class ResidualProofStatus { none, trace_verified, checked_upper_only, exact_original_verified };
enum class ResidualStopReason {
  none, quantum_work, quantum_time, total_work, total_time, depth_limit,
  record_limit, cell_limit, exact_limit, allocation_failure, counter_overflow,
  invalid_quantum, invalid_trace, internal_failure, complete, cancelled, moved_from
};
enum class ResidualTerminal { empty_body, hierarchical, stalled };
// Frozen ear-condition bits: P2 arXiv:2603.14754v1, Section 2.1.4,
// Definition 2.9. These bits describe supports, not reconstruction or height proof.
enum class EarCondition : unsigned { first = 1, second = 2, both = 3 };
struct EarAnchor {
  std::size_t occurrence = 0;
  EarCondition condition = EarCondition::first;
};
struct EarRecord {
  std::size_t occurrence = 0;
  VariableSet shared;
  VariableSet unique;
  std::vector<EarAnchor> anchors;
};
struct EarDeletion { std::size_t occurrence = 0, anchor = 0; };
// Every ID in the trace is an original occurrence/variable ID. The dense view
// is an explicit separate binding; its proof never certifies the original query.
// Dense local occurrence/variable IDs map explicitly to ascending original IDs.
// Table IDs still address the retained original catalog. Ordered surviving head
// positions, repeated aliases, constants and ignored columns are preserved.
struct ResidualView {
  Query query;
  std::vector<std::size_t> original_occurrences;
  std::vector<VariableId> original_variables;
  std::vector<std::optional<std::size_t>> occurrence_to_local;
  std::vector<std::optional<VariableId>> variable_to_local;
};
// Snapshot all eligibility before deletion. Repeatedly remove the smallest
// original ear with its smallest still-live frozen anchor; a stalled round is
// retained and requests complete search rather than claiming infeasibility.
struct ResidualLayer {
  std::vector<std::size_t> members;
  VariableSet variables, head, unique;
  std::vector<EarRecord> ears;
  std::vector<EarDeletion> deletions;
  std::vector<std::size_t> remaining;
  VariableSet residual_head;
};
struct ResidualTraceRecord {
  std::uint64_t version = 1;
  std::vector<VariableSet> original_scopes;
  std::vector<ResidualLayer> layers;
  std::vector<std::size_t> terminal_members;
  VariableSet terminal_head;
  ResidualTerminal terminal = ResidualTerminal::empty_body;
  ResidualView terminal_view;
};
struct ResidualLimits {
  PhaseCeiling residual{50'000'000, {}};
  // Residual/view/P02 frames; delegated exact owners use exact.logical_depth
  // and report their depths in the separate exact_progress counters.
  std::optional<std::size_t> logical_depth = 256;
  // Cumulative logical construction records/cells, including discarded drafts;
  // only residual metadata/view/tree content is counted here. Catalog/query
  // admission copies, P02 validator scratch and delegated exact storage are
  // separate costs, not a global allocator-capacity byte limit.
  std::optional<std::uint64_t> record_limit = 1'000'000;
  std::optional<std::uint64_t> cell_limit = 10'000'000;
  ContinuationLimits exact;
};
struct ResidualOptions {
  ResidualMode mode = ResidualMode::require_exact_original;
  ResidualLimits limits;
};
struct ResidualStatistics {
  std::uint64_t hierarchy_tests = 0, rounds = 0, eligibility_pairs = 0, deletions = 0;
  std::uint64_t restorations = 0, drafts = 0, rejected_drafts = 0, generalized_grafts = 0;
  std::uint64_t exact_repairs = 0, original_exact_runs = 0, candidate_publications = 0;
  std::uint64_t admissions = 0;
};
// Bounds concern the full original query. The lower remains universal 0/1
// until original proof completes; exact_progress may instead describe an
// induced seed/repair, as distinguished by exact_scope_original. This snapshot
// is diagnostic data and cannot be edited into authoritative handles.
struct ResidualProgress {
  ResidualPhase phase = ResidualPhase::admitted;
  ResidualResult result = ResidualResult::unfinished;
  ResidualProofStatus proof_status = ResidualProofStatus::none;
  ResidualStopReason last_stop = ResidualStopReason::none;
  StopReason exact_stop = StopReason::none;
  HeightInterval heights;
  WorkCounters work;
  ResidualStatistics statistics;
  std::uint64_t records = 0, cells = 0, limit_revision = 0;
  bool trace_complete = false, trace_verified = false, exact_scope_original = false;
  SearchProgress exact_progress;
};
struct ResidualAdvance { ResidualStopReason stopped_for; StopReason exact_reason; ResidualProgress progress; };

enum class ResidualTraceRule {
  none, version, scopes, membership, variables, head, unique, eligibility,
  deletion, maximal_round, terminal, mapping, query, resource_limit, allocation_failure
};
struct ResidualTraceReport {
  bool valid = false, resource_limit = false;
  std::uint64_t work = 0;
  ResidualTraceRule rule = ResidualTraceRule::none;
  std::optional<std::size_t> layer, occurrence, anchor;
};

// Immutable replayed reduction with owned original binding; no tree/height
// authority. Copies survive facade destruction; getters borrow from a live
// handle and reject moved-from handles. Copy/move/valid do not allocate.
class ResidualTrace {
 public:
  ResidualTrace(const ResidualTrace&) noexcept = default;
  ResidualTrace& operator=(const ResidualTrace&) noexcept = default;
  ResidualTrace(ResidualTrace&&) noexcept = default;
  ResidualTrace& operator=(ResidualTrace&&) noexcept = default;
  bool valid() const noexcept;
  const Catalog& catalog() const;
  const Query& query() const;
  const ResidualTraceRecord& record() const;
 private:
  friend struct residual_detail::ArtifactFactory;
  explicit ResidualTrace(std::shared_ptr<const residual_detail::TraceData>) noexcept;
  std::shared_ptr<const residual_detail::TraceData> data_;
};
// Immutable original-query P02 upper witness with owned source and trace.
// Exactness requires the separate original VerifiedOptimum. Old copies keep
// their checked upper when later search publishes a better candidate.
class ResidualCandidate {
 public:
  ResidualCandidate(const ResidualCandidate&) noexcept = default;
  ResidualCandidate& operator=(const ResidualCandidate&) noexcept = default;
  ResidualCandidate(ResidualCandidate&&) noexcept = default;
  ResidualCandidate& operator=(ResidualCandidate&&) noexcept = default;
  bool valid() const noexcept;
  const Catalog& catalog() const;
  const Query& query() const;
  const FreeConnexTree& tree() const;
  std::size_t height() const;
  ResidualOrigin origin() const;
  ResidualTrace trace() const;
  // Every candidate establishes an upper bound; exactness is a separate P06 type.
 private:
  friend struct residual_detail::ArtifactFactory;
  explicit ResidualCandidate(std::shared_ptr<const residual_detail::CandidateData>) noexcept;
  std::shared_ptr<const residual_detail::CandidateData> data_;
};
// Exclusive single-caller resumable owner; movable between threads under
// exclusive ownership. create owns/validates input before metering. Nonzero
// advance calls resume saved positions; zero grants are inert. Resource and
// allocation stops permit retry/monotone raises; internal failure/overflow are
// terminal. Admission copies, cleanup and container/string widths remain
// explicit costs outside per-cell construction counts and hard deadlines.
// Published trace/candidate handles survive cancel, move and destruction.
class ResidualSearch {
 public:
  static ResidualSearch create(Catalog, Query, ResidualOptions = {});
  ~ResidualSearch();
  ResidualSearch(ResidualSearch&&) noexcept;
  ResidualSearch& operator=(ResidualSearch&&) noexcept;
  ResidualSearch(const ResidualSearch&) = delete;
  ResidualSearch& operator=(const ResidualSearch&) = delete;
  ResidualAdvance advance(WorkQuantum) noexcept;
  ResidualProgress progress() const noexcept;
  ResidualOptions options() const;
  const Catalog& catalog() const;
  const Query& query() const;
  std::optional<ResidualTrace> trace() const noexcept;
  std::optional<ResidualCandidate> candidate() const noexcept;
  std::optional<VerifiedOptimum> exact_original() const noexcept;
  std::optional<VerifiedInfeasible> infeasibility() const noexcept;
  LimitChange raise_limits(ResidualLimits) noexcept;
  void cancel() noexcept;
 private:
  struct Impl;
  explicit ResidualSearch(std::unique_ptr<Impl>) noexcept;
  std::unique_ptr<Impl> data_;
};
// Independent diagnostic replay only; validity here proves the frozen trace,
// never a tree upper bound, family completeness or a minimum-height claim.
[[nodiscard]] ResidualTraceReport verify_residual_trace(const Catalog&, const Query&,
                                                       const ResidualTraceRecord&, const SearchLimits& = {});
}  // namespace crown::planner
