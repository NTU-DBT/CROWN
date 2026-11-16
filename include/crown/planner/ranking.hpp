#pragma once
#include "crown/ir/program.hpp"
#include "crown/resource/owner_allocator.hpp"
#include "crown/resource/owner_text.hpp"

#include "crown/planner/candidates.hpp"
#include "crown/ir/physical.hpp"
#include <chrono>
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace crown::planner::ranking {
namespace detail { struct Factory; struct EvidenceData; struct ResultData; }
enum class Policy { height_only, committed_input_native_depth, tuple_index_slots };
enum class Fallback { require_evidence, height_only };
enum class Stop { complete, no_candidates, evidence_unavailable, invalid_handle,
  binding_mismatch, invalid_limits, work_limit, cell_limit, byte_limit,
  bit_limit, candidate_limit, lowering_limit, time_limit, allocation_failure, internal_error };
enum class Reason : std::uint64_t {
  none=0, not_captured=1, disabled=2, pending=4, released=8, source_scope=16,
  source_limit=32, source_incomplete=64, empty_census=128, root_incomplete=256,
  root_saturated=512, denominator_unavailable=1024, interval_saturated=2048,
  protocol=4096, stale=8192, foreign_owner=16384, future_sequence=32768,
  layer_mismatch=65536, interval_changed=131072, mode_changed=262144, read_failed=524288,
  source_budget_exhausted=1048576
};
using Reasons=std::uint64_t;
constexpr Reasons reason(Reason value) noexcept {return static_cast<Reasons>(value);}
struct Limits {
  std::uint64_t work=1'000'000, cells=1'000'000, binding_key_bytes=8*1024*1024,
      payload_bytes=16*1024*1024, lowering_work=1'000'000,
      identity_work=1'000'000, binding_replay_work=1'000'000, normalization_work=1'000'000;
  std::size_t candidates=128;
  unsigned score_bits=512;
  std::optional<std::chrono::nanoseconds> active_time;
};
struct Usage {
  std::uint64_t work{}, cells{}, binding_key_bytes{}, payload_bytes{},
      lowering_work{}, identity_work{}, binding_replay_work{}, normalization_work{},
      active_nanoseconds{};
  bool operator==(const Usage&) const=default;
};
struct Request {Policy policy=Policy::height_only; Fallback fallback=Fallback::require_evidence; Limits limits;};
struct InputWeight {TableId table; std::uint64_t inserts{}, erases{}, changed{}, noop{};};
struct SourceCardinality {TableId table; std::uint64_t rows{};};
enum class CaptureState {not_requested, available, budget_exhausted, pending_private_state, unavailable, released};
struct SourceObservation {TableId table; CaptureState state; std::optional<std::uint64_t> cardinality;};
template<class T> using EvidenceVector=std::vector<T,resource::OwnerAllocator<T>>;
using EvidenceText=std::basic_string<char,std::char_traits<char>,resource::OwnerAllocator<char>>;
template<class T> using ScoreVector=std::vector<T,resource::OwnerAllocator<T>>;
using ScoreText=resource::OwnerText;
struct ModeIdentity {
  bool delta_owner{};
  std::uint64_t requested_mode{}, resolved_mode{}, requested_completion{}, resolved_completion{}, live_maintenance{}, view{};
  bool operator==(const ModeIdentity&) const=default;
};
struct EvidenceIdentity {
  std::uint64_t owner{}, epoch{}, interval_start{}, reset{}, configuration{}, segment{}, format{1};
  std::uint64_t collection_mode{}, max_cells{}, period{}, offset{}, detail_budget{};
  ModeIdentity modes;
  bool pending{}, reset_saturated{}, configuration_saturated{}, segment_saturated{};
};
struct CaptureAccounting {
  Limits processing_limits;
  CaptureState state=CaptureState::not_requested;
  bool state_requested{};
  std::size_t requested_components{}, returned_components{};
  std::uint64_t state_work_limit{}, state_rows_limit{}, state_keys_limit{}, state_bytes_limit{};
  std::size_t state_projection_width{}, state_heavy_keys{};
  std::uint64_t state_work{}, state_rows{}, state_keys{}, state_bytes{};
  std::size_t snapshot_descriptors{}, snapshot_cells{};
};
// Factory-produced score input, separate from the structural proof. Always an
// as-of record: this pure layer cannot assert that an owner is still current.
// Moves deliberately retain the source shared owner, so noexcept getters can
// borrow directly. Assignments may destroy a large old destination payload.
class Evidence {
 public:
  Evidence(const Evidence&) noexcept=default;
  Evidence& operator=(const Evidence&) noexcept=default;
  Evidence(Evidence&& x) noexcept:data_(x.data_) {}
  Evidence& operator=(Evidence&& x) noexcept {data_=x.data_;return *this;}
  const CompiledProgram& plan() const noexcept;
  const EvidenceVector<InputWeight>& weights() const noexcept;
  const EvidenceVector<SourceCardinality>& sources() const noexcept;
  const EvidenceVector<SourceObservation>& source_observations() const noexcept;
  const EvidenceIdentity& identity() const noexcept;
  const CaptureAccounting& capture_accounting() const noexcept;
  Reasons depth_reasons() const noexcept;
  Reasons memory_reasons() const noexcept;
  std::uint64_t denominator() const noexcept;
  const Usage& preparation_usage() const noexcept;
 private:
  friend struct detail::Factory;
  explicit Evidence(std::shared_ptr<const detail::EvidenceData> data) noexcept:data_(std::move(data)) {}
  std::shared_ptr<const detail::EvidenceData> data_;
};
struct OccurrenceDepth {OccurrenceId occurrence; TableId table; std::uint64_t depth{};};
struct TableDepth {
  TableId table; std::uint64_t inserts{}, erases{};
  ScoreText depth_sum, contribution;
};
struct PopulationBound {
  NodeId node; ScoreText records, survivors, parent_support;
  std::optional<ScoreText> visible;
};
struct SlotTerm {
  RelationId relation; std::optional<IndexRequirementId> index;
  std::size_t width{}; ScoreText population, contribution;
};
struct CandidateScore {
  MinimumHeightCandidate candidate;
  ScoreText structural_key;
  std::size_t height{};
  ScoreText numerator, denominator, slots;
  ScoreVector<OccurrenceDepth> depths;
  ScoreVector<TableDepth> table_depths;
  ScoreVector<PopulationBound> populations;
  ScoreVector<SlotTerm> slot_terms;
  std::optional<CompiledProgram> modeled_plan;
  CandidateScore(const resource::MemoryAccount&,MinimumHeightCandidate);
};
// Complete ranking of this retained prefix only; no provider advance or plan
// install. Copy-like moves keep both handles usable for direct const borrows.
class Result {
 public:
  Result(const Result&) noexcept=default;
  Result& operator=(const Result&) noexcept=default;
  Result(Result&& x) noexcept:data_(x.data_) {}
  Result& operator=(Result&& x) noexcept {data_=x.data_;return *this;}
  const CandidateSnapshot& snapshot() const noexcept;
  const MinimumHeightCandidate& selected() const noexcept;
  std::size_t selected_index() const noexcept;
  const ScoreVector<CandidateScore>& scores() const noexcept;
  const resource::MemoryAccount& account() const & noexcept;
  const resource::MemoryAccount& account() const &&=delete;
  const std::optional<Evidence>& evidence() const noexcept;
  const Request& request() const noexcept;
  Policy effective_policy() const noexcept;
  Reasons fallback_reasons() const noexcept;
  const Usage& usage() const noexcept;
  static constexpr unsigned format_version=1;
  static constexpr unsigned arithmetic_version=1;
 private:
  friend struct detail::Factory;
  explicit Result(std::shared_ptr<const detail::ResultData> data) noexcept:data_(std::move(data)) {}
  std::shared_ptr<const detail::ResultData> data_;
};
struct Attempt {
  Stop stop=Stop::internal_error;
  std::optional<Result> result;
  Usage usage;
  std::size_t evaluated{};
  Reasons reasons{};
};
// All retained members are evaluated or no Result is published. No provider
// advancement, owner mutation, proof construction, cache or report dependency.
[[nodiscard]] Attempt rank(const CandidateSnapshot&,const Request& = {},
    const std::optional<Evidence>& = {}) noexcept;
// Runtime/receiving-owner path, including height-only ranking without evidence.
// All new retained and temporary storage uses this existing account.
[[nodiscard]] Attempt rank_with_account(const resource::MemoryAccount&,const CandidateSnapshot&,
    const Request& = {},const std::optional<Evidence>& = {}) noexcept;
} // namespace crown::planner::ranking
