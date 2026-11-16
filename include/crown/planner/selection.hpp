#pragma once

#include "crown/planner/ranking.hpp"
#include "crown/planner/update_pattern.hpp"
#include <variant>

namespace crown::planner::selection {
namespace rank = ::crown::planner::ranking;
namespace detail { struct Factory; struct SelectionData; struct CacheData; }
// Select the supported scoring baseline without changing required height. See
// docs/selection.md.
enum class Policy { height_only, committed_input_native_depth, tuple_index_slots, maintenance_cost };
// Choose retained-prefix scope or require real generator exhaustion. See docs/selection.md.
enum class FamilyPolicy { retained_prefix, require_exhausted_family };
// Name the admitted compiled layout policy. See docs/selection.md.
enum class LayoutPolicy { native_layout_v1 };
// Name identical compiled-index requirement sharing. See docs/selection.md.
enum class IndexPolicy { share_identical_requirements_v1 };
// Control whether artifact cache lookup/insertion participates. See docs/selection.md.
enum class CacheUse { bypass, read_only, read_write };
// Provide explicit initial compiler options for the original proof model. See
// docs/selection.md.
struct DirectCQ { PhysicalOptions options; };
// Explicit compiler input or the actual immutable program of a runtime owner.
// Retain a complete physical source for selection/replanning. See docs/selection.md.
struct PhysicalBasis { std::variant<PhysicalPlan,CompiledProgram> plan; };
using Source = std::variant<DirectCQ, PhysicalBasis>;
// Supply a mandatory unitless modeled slot cap. See docs/selection.md.
struct TupleIndexSlotLimit { std::string maximum; };
// Describe reserved allocator-byte prediction choices. See docs/selection.md.
enum class BytePrediction { live_allocation, peak_allocation };
// Carry an explicitly unsupported allocator-byte constraint. See docs/selection.md.
struct AllocatorByteLimit { std::uint64_t maximum; BytePrediction prediction; };
// Select no constraint, mandatory modeled slots or reserved byte prediction. See
// docs/selection.md.
using Constraint = std::variant<std::monostate, TupleIndexSlotLimit, AllocatorByteLimit>;
// Use the shared finite ranking processing dimensions for selection. See docs/selection.md.
struct Limits { rank::Limits aggregate; };
// State policy, family, layout/index, slot/pattern conditions and aggregate limits.
// Pattern admissibility is conditional on separate runtime enforcement. See docs/selection.md.
struct Request {
  Policy policy = Policy::committed_input_native_depth;
  rank::Fallback fallback = rank::Fallback::height_only;
  FamilyPolicy family = FamilyPolicy::retained_prefix;
  LayoutPolicy layout = LayoutPolicy::native_layout_v1;
  IndexPolicy indexes = IndexPolicy::share_identical_requirements_v1;
  Constraint constraint;
  Limits limits;
  // Optional conditional admissibility. Runtime enforcement is a separate contract.
  std::optional<patterns::Declaration> update_patterns;
};
using SelectionText=resource::OwnerText;
template<class T> using SelectionVector=std::vector<T,resource::OwnerAllocator<T>>;
// Owning result fields retain the receiving query account. Ordinary Source and
// Request values remain explicit compiler/caller inputs and exports.
// Retain policy text inside the receiving selection account. See docs/selection.md.
struct CapturedCachePolicy {
  SelectionText arithmetic,planner,optimization,cost_model;
  CapturedCachePolicy(const resource::MemoryAccount&,const io::CachePolicy&);
};
// Retain account-backed policy with exact physical limits/backend options. See
// docs/selection.md.
struct CapturedPhysicalOptions {
  CapturedCachePolicy policy;
  PhysicalLimits limits;
  std::optional<storage::IndexedBackendSpec> indexed_storage;
  CapturedPhysicalOptions(const resource::MemoryAccount&,const PhysicalOptions&);
};
// Keep DirectCQ options in a result-owned account representation. See docs/selection.md.
struct CapturedDirectCQ { CapturedPhysicalOptions options; };
using CapturedSource=std::variant<CapturedDirectCQ,PhysicalBasis>;
struct CapturedTupleIndexSlotLimit { SelectionText maximum; };
using CapturedConstraint=std::variant<std::monostate,CapturedTupleIndexSlotLimit,AllocatorByteLimit>;
// Retain exact request choices, source-bound pattern rules and finite limits. See
// docs/selection.md.
struct CapturedRequest {
  Policy policy;
  rank::Fallback fallback;
  FamilyPolicy family;
  LayoutPolicy layout;
  IndexPolicy indexes;
  CapturedConstraint constraint;
  Limits limits;
  // Optional conditional admissibility. Runtime enforcement is a separate contract.
  std::optional<patterns::Declaration> update_patterns;
  CapturedRequest(const resource::MemoryAccount&,const Request&);
};
// Locate the last synchronous selection stage. See docs/selection.md.
enum class Stage { admission, capture, source_binding, constraint_assessment,
  primary_assessment, decision, cache_key, cache_lookup, lowering,
  cache_admission, publication, pattern_analysis };
// Distinguish successful selection, unsupported/unavailable input and failed processing. See
// docs/selection.md.
enum class Stop { complete, invalid_handle, invalid_request, binding_mismatch,
  no_candidates, incomplete_family, unsupported_model, unsupported_layout,
  unsupported_memory_prediction, evidence_unavailable, boundary_unavailable,
  constraint_unsatisfied, resource_limit, lowering_failure,
  allocation_failure, internal_error };
// Name the exhausted processing/cache dimension when known. See docs/selection.md.
enum class Resource { none, work, cells, key_bytes, payload_bytes, candidates,
  score_bits, lowering, identity, binding_replay, normalization, active_time,
  cache_key_bytes, cache_plan_payload, counter_overflow };
// State whether pure selection retained as-of evidence. See docs/selection.md.
enum class EvidenceUse { absent, as_of };
// Distinguish absent, measured and historically unmeasured evidence preparation. See
// docs/selection.md.
enum class PreparationTiming { absent, measured, unmeasured };
// Explain whether a retained complete C02 result served primary or mandatory slot filtering.
// See docs/selection.md.
enum class AssessmentPurpose { primary, slot_constraint, primary_and_constraint };
// Retain one full C02 assessment and its role. See docs/selection.md.
struct Assessment { AssessmentPurpose purpose; rank::Result result; };
// Label slot-cap and optional pattern admissibility of one retained candidate.
// Slot failure takes precedence; every pattern analysis remains separately inspectable.
enum class Eligibility { unconstrained, within_slot_limit, above_slot_limit, pattern_unproved };
// Record one candidate index and its eligibility. See docs/selection.md.
struct CandidateDecision { std::size_t candidate_index; Eligibility eligibility; };
// Bound FIFO entries and logical retained key/plan component bytes. See docs/selection.md.
struct CacheLimits {
  std::size_t entries = 128;
  std::uint64_t key_bytes = 8 * 1024 * 1024;
  std::uint64_t plan_payload_bytes = 32 * 1024 * 1024;
  bool operator==(const CacheLimits&) const = default;
};
// Report committed cache counters and retained logical sizes. See docs/selection.md.
struct CacheStatistics {
  std::uint64_t hits{}, misses{}, insertions{}, evictions{};
  std::size_t entries{};
  std::uint64_t key_bytes{}, plan_payload_bytes{};
  bool operator==(const CacheStatistics&) const = default;
};
// Exclusive caller; no global state or public raw-key insertion capability.
// Own an exclusive FIFO cache of whole compiled artifacts. See docs/selection.md.
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
// Describe this successful call cache participation. See docs/selection.md.
enum class CacheDisposition { bypassed, disabled, hit, miss_read_only, inserted };
// Retain cache-use/capacity and byte-comparison diagnostics. See docs/selection.md.
struct CacheObservation {
  CacheUse requested = CacheUse::bypass;
  std::optional<CacheLimits> limits;
  CacheDisposition disposition = CacheDisposition::bypassed;
  std::uint64_t compared_bytes{}, binding_bytes{};
};
// A qualified support-process bound for the selected immutable plan. This
// report shares the existing funded selection, including its exact source,
// candidate, declaration and edge premises. It does not establish enforcement.
// I includes charged initialization; each replacement starts a new such run.
class PatternGuarantee {
 public:
  PatternGuarantee(const PatternGuarantee&) noexcept = default;
  PatternGuarantee& operator=(const PatternGuarantee&) noexcept = default;
  PatternGuarantee(PatternGuarantee&& other) noexcept : data_(other.data_) {}
  PatternGuarantee& operator=(PatternGuarantee&& other) noexcept { data_ = other.data_; return *this; }
  static constexpr std::string_view bound = "O_Q(I + U)";
  static constexpr std::string_view units = "fixed-query amortized successful logical Boolean native support actions";
  static constexpr std::string_view input_accounting =
      "I=physical source rows at charged initialization; U=physical source events including noops";
  static constexpr std::string_view excluded_costs =
      "source adaptation; storage lookups/scans/comparisons; scalar widths; allocation; monitoring; journal; rollback/retry; output; total CPU/delay";
  static constexpr std::string_view proof_reference = "docs/update_patterns.md#support-action-guarantee-profile";
  const patterns::Analysis& analysis() const & noexcept;
  const patterns::Analysis& analysis() const && = delete;
  const CompiledProgram& plan() const & noexcept;
  const CompiledProgram& plan() const && = delete;
 private:
  friend class Selection;
  explicit PatternGuarantee(std::shared_ptr<const detail::SelectionData> data) noexcept : data_(std::move(data)) {}
  std::shared_ptr<const detail::SelectionData> data_;
};
// Immutable owning result. Neither this handle nor its cache binding asserts
// actual-owner freshness or confers proof/import/deployment authority.
// Retain a successful immutable chosen native program and complete decision context. See
// docs/selection.md.
// Moves retain source validity for direct borrows. Assignment can destroy
// a large previous destination payload when its last owner is released.
class Selection {
 public:
  Selection(const Selection&) noexcept = default;
  Selection& operator=(const Selection&) noexcept = default;
  Selection(Selection&& other) noexcept : data_(other.data_) {}
  Selection& operator=(Selection&& other) noexcept { data_ = other.data_; return *this; }
  const CandidateSnapshot& snapshot() const noexcept;
  const MinimumHeightCandidate& selected() const noexcept;
  std::size_t selected_index() const noexcept;
  const CompiledProgram& plan() const noexcept;
  const CapturedSource& source() const noexcept;
  const CapturedRequest& request() const noexcept;
  Source export_source() const;
  Request export_request() const;
  const resource::MemoryAccount& account() const & noexcept;
  const resource::MemoryAccount& account() const &&=delete;
  const SelectionVector<Assessment>& assessments() const noexcept;
  const SelectionVector<CandidateDecision>& decisions() const noexcept;
  // Empty when no pattern condition was requested; otherwise one entry per retained candidate.
  const SelectionVector<patterns::Analysis>& pattern_analyses() const noexcept;
  // Absent for undeclared/unproved requests. O(1) sharing, no new allocation;
  // final-owner destruction can release the whole retained selection graph.
  std::optional<PatternGuarantee> pattern_guarantee() const noexcept;
  const std::optional<rank::Evidence>& evidence() const noexcept;
  EvidenceUse evidence_use() const noexcept;
  rank::Policy effective_policy() const noexcept;
  rank::Reasons fallback_reasons() const noexcept;
  const rank::Usage& usage() const noexcept;
  PreparationTiming preparation_timing() const noexcept;
  const CacheObservation& cache_observation() const noexcept;
  const std::optional<SelectionText>& cache_binding() const noexcept;
  static constexpr unsigned format_version = 1;
  static constexpr unsigned cache_binding_version = 1;
 private:
  friend struct detail::Factory;
  explicit Selection(std::shared_ptr<const detail::SelectionData> data) noexcept : data_(std::move(data)) {}
  std::shared_ptr<const detail::SelectionData> data_;
};
// Return fixed diagnostics and optional complete Selection from a noexcept call. See
// docs/selection.md.
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
