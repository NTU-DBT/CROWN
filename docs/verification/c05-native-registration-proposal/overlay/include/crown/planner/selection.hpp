#pragma once

#include "crown/planner/ranking.hpp"
#include <variant>

namespace crown::planner::selection {
namespace rank = ::crown::planner::ranking;
namespace detail { struct Factory; struct SelectionData; struct CacheData; }
enum class Policy { height_only, committed_input_native_depth, tuple_index_slots, maintenance_cost };
enum class FamilyPolicy { retained_prefix, require_exhausted_family };
enum class LayoutPolicy { native_layout_v1 };
enum class IndexPolicy { share_identical_requirements_v1 };
enum class CacheUse { bypass, read_only, read_write };
struct DirectCQ { PhysicalOptions options; };
struct PhysicalBasis { PhysicalPlan plan; };
using Source = std::variant<DirectCQ, PhysicalBasis>;
struct TupleIndexSlotLimit { std::string maximum; };
enum class BytePrediction { live_allocation, peak_allocation };
struct AllocatorByteLimit { std::uint64_t maximum; BytePrediction prediction; };
using Constraint = std::variant<std::monostate, TupleIndexSlotLimit, AllocatorByteLimit>;
struct Limits { rank::Limits aggregate; };
struct Request {
  Policy policy = Policy::committed_input_native_depth;
  rank::Fallback fallback = rank::Fallback::height_only;
  FamilyPolicy family = FamilyPolicy::retained_prefix;
  LayoutPolicy layout = LayoutPolicy::native_layout_v1;
  IndexPolicy indexes = IndexPolicy::share_identical_requirements_v1;
  Constraint constraint;
  Limits limits;
};
enum class Stage { admission, capture, source_binding, constraint_assessment,
  primary_assessment, decision, cache_key, cache_lookup, lowering,
  cache_admission, publication };
enum class Stop { complete, invalid_handle, invalid_request, binding_mismatch,
  no_candidates, incomplete_family, unsupported_model, unsupported_layout,
  unsupported_memory_prediction, evidence_unavailable, boundary_unavailable,
  constraint_unsatisfied, resource_limit, lowering_failure,
  allocation_failure, internal_error };
enum class Resource { none, work, cells, key_bytes, payload_bytes, candidates,
  score_bits, lowering, identity, binding_replay, normalization, active_time,
  cache_key_bytes, cache_plan_payload, counter_overflow };
enum class EvidenceUse { absent, as_of };
enum class PreparationTiming { absent, measured, unmeasured };
enum class AssessmentPurpose { primary, slot_constraint, primary_and_constraint };
struct Assessment { AssessmentPurpose purpose; rank::Result result; };
enum class Eligibility { unconstrained, within_slot_limit, above_slot_limit };
struct CandidateDecision { std::size_t candidate_index; Eligibility eligibility; };
struct CacheLimits {
  std::size_t entries = 128;
  std::uint64_t key_bytes = 8 * 1024 * 1024;
  std::uint64_t plan_payload_bytes = 32 * 1024 * 1024;
  bool operator==(const CacheLimits&) const = default;
};
struct CacheStatistics {
  std::uint64_t hits{}, misses{}, insertions{}, evictions{};
  std::size_t entries{};
  std::uint64_t key_bytes{}, plan_payload_bytes{};
  bool operator==(const CacheStatistics&) const = default;
};
// Exclusive caller; no global state or public raw-key insertion capability.
class PlanCache {
 public:
  static PlanCache create(CacheLimits = {});
  ~PlanCache();
  PlanCache(PlanCache&&) noexcept;
  PlanCache& operator=(PlanCache&&) noexcept;
  PlanCache(const PlanCache&) = delete;
  PlanCache& operator=(const PlanCache&) = delete;
  bool valid() const noexcept;
  CacheLimits limits() const noexcept;
  CacheStatistics statistics() const noexcept;
  void clear() noexcept;
 private:
  friend struct detail::Factory;
  explicit PlanCache(std::unique_ptr<detail::CacheData>) noexcept;
  std::unique_ptr<detail::CacheData> data_;
};
enum class CacheDisposition { bypassed, disabled, hit, miss_read_only, inserted };
struct CacheObservation {
  CacheUse requested = CacheUse::bypass;
  std::optional<CacheLimits> limits;
  CacheDisposition disposition = CacheDisposition::bypassed;
  std::uint64_t compared_bytes{}, binding_bytes{};
};
// Immutable owning result. Neither this handle nor its cache binding asserts
// actual-owner freshness or confers proof/import/deployment authority.
class Selection {
 public:
  Selection(const Selection&) noexcept = default;
  Selection& operator=(const Selection&) noexcept = default;
  Selection(Selection&& other) noexcept : data_(other.data_) {}
  Selection& operator=(Selection&& other) noexcept { data_ = other.data_; return *this; }
  const CandidateSnapshot& snapshot() const noexcept;
  const MinimumHeightCandidate& selected() const noexcept;
  std::size_t selected_index() const noexcept;
  const PhysicalPlan& plan() const noexcept;
  const Source& source() const noexcept;
  const Request& request() const noexcept;
  const std::vector<Assessment>& assessments() const noexcept;
  const std::vector<CandidateDecision>& decisions() const noexcept;
  const std::optional<rank::Evidence>& evidence() const noexcept;
  EvidenceUse evidence_use() const noexcept;
  rank::Policy effective_policy() const noexcept;
  rank::Reasons fallback_reasons() const noexcept;
  const rank::Usage& usage() const noexcept;
  PreparationTiming preparation_timing() const noexcept;
  const CacheObservation& cache_observation() const noexcept;
  const std::optional<std::string>& cache_binding() const noexcept;
  static constexpr unsigned format_version = 1;
  static constexpr unsigned cache_binding_version = 1;
 private:
  friend struct detail::Factory;
  explicit Selection(std::shared_ptr<const detail::SelectionData> data) noexcept : data_(std::move(data)) {}
  std::shared_ptr<const detail::SelectionData> data_;
};
struct Attempt {
  Stop stop = Stop::internal_error;
  Stage stage = Stage::admission;
  std::optional<Selection> selection;
  rank::Usage usage;
  std::optional<rank::Stop> component_stop;
  Resource resource = Resource::none;
  rank::Reasons reasons{};
  PreparationTiming preparation_timing = PreparationTiming::absent;
  std::size_t retained{}, constraint_evaluated{}, primary_evaluated{};
};
[[nodiscard]] Attempt select(const CandidateSnapshot&, const Source&,
    const Request& = {}, const std::optional<rank::Evidence>& = {},
    PlanCache* = nullptr, CacheUse = CacheUse::bypass) noexcept;
} // namespace crown::planner::selection
