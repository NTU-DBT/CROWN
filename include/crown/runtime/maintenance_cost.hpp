#pragma once

#include "crown/runtime/ranking_evidence.hpp"
#include <array>

namespace crown::runtime::cost {
namespace pr = ::crown::planner::ranking;
namespace detail { struct Factory; struct CalibrationData; struct ProfileData; struct ResultData; }
using U64 = std::uint64_t;

// Factory arithmetic reduces nonnegative ratios and checks 64-bit intermediates.
// Public Ratio fields are unchecked; fit uses floating point before quantization.
struct Ratio { U64 numerator{}, denominator{1}; bool operator==(const Ratio&) const = default; };
enum class Component : std::size_t {
  base_input, base_change, adapter_visit, derivation_change, survivor_transition,
  parent_count_update, parent_presence_transition, visible_count_update, visible_presence_transition, edge_lookup, native_bucket_touch,
  generalized_hit, annotation_change, snapshot_start, snapshot_row,
  snapshot_end, delta_start, delta_row, delta_end, encoded_byte,
  checkpoint_start, checkpoint_byte, count
};
inline constexpr auto component_count = static_cast<std::size_t>(Component::count);
std::string_view component_name(Component) noexcept;

// Caller-supplied measured calibration observations, not native query facts.
// Every sample measures only its named operation, with consistent environment,
// backend, scalar/layout and instrumentation context supplied in the label.
struct CalibrationSample { Component component; U64 units{}, elapsed_ns{}; };
enum class CalibrationOrigin { isolated_measurement_ratios, fitted_linear_assumption };
// A whole measured phase and its observed feature vector. The fit infers a
// linear attribution; it does not turn that attribution into observed facts.
struct FitObservation { std::array<U64,component_count> units{}; U64 elapsed_ns{}; };
struct FitOptions {
  std::size_t max_iterations{10000};
  double relative_tolerance{1e-9}, rank_tolerance{1e-10};
  Ratio ridge{0,1};
  U64 quantization_denominator{1'000'000};
  std::optional<workload::ModeFacts> modes;
};
struct FitSummary {
  FitOptions options;
  std::size_t observations{}, observed_features{}, numerical_rank{}, iterations{};
  U64 total_elapsed_ns{};
  bool underdetermined{};
  double root_mean_square_error_ns{}, maximum_absolute_error_ns{};
};
struct FeatureCensus {
  std::array<U64,component_count> units{};
  workload::Stamp stamp;
  workload::ModeFacts modes;
};
struct FeatureAttempt { pr::Stop stop=pr::Stop::internal_error; std::optional<FeatureCensus> census; pr::Usage usage; };
// Exact committed full-detail counters only. Disabled, sampled, truncated,
// saturated, logical-only or private intervals cannot become timing features.
[[nodiscard]] FeatureAttempt features(const workload::Snapshot&,pr::Limits = {}) noexcept;
// elapsed_ns is the isolated sample total, or zero for a jointly fitted rate.
// Joint raw timings remain in fit_observations(), rather than being counted
// as independently measured time for each correlated feature.
struct Coefficient { Ratio nanoseconds_per_unit; U64 samples{}, units{}, elapsed_ns{}; };
class Calibration {
  // Copies share immutable Data; views require a retained readable handle.
  // Default moves may empty the source; labels do not validate measurements.
 public:
  const std::array<std::optional<Coefficient>, component_count>& coefficients() const noexcept;
  std::string_view context() const noexcept;
  std::string_view backend() const noexcept;
  CalibrationOrigin origin() const noexcept;
  const std::optional<FitSummary>& fit_summary() const noexcept;
  std::span<const FitObservation> fit_observations() const noexcept;
 private:
  friend struct detail::Factory;
  explicit Calibration(std::shared_ptr<const detail::CalibrationData> x):data_(std::move(x)) {}
  std::shared_ptr<const detail::CalibrationData> data_;
};
struct CalibrationAttempt {
  pr::Stop stop=pr::Stop::internal_error;
  std::optional<Calibration> calibration;
  pr::Usage usage;
};
[[nodiscard]] CalibrationAttempt calibrate(const resource::MemoryAccount&,std::string_view context,
    std::string_view backend,std::span<const CalibrationSample>,pr::Limits = {}) noexcept;
// Deterministic, zero-initialized, fixed-coordinate-order nonnegative fitting.
// IEEE floating arithmetic is used only by this approximate calibration step;
// published coefficients are quantized exact ratios used by estimate().
// Insufficient variation is reported as numerical rank/underdetermination;
// missing columns stay unavailable. No statistical confidence bound follows.
[[nodiscard]] CalibrationAttempt fit(const resource::MemoryAccount&,std::string_view context,
    std::string_view backend,std::span<const FitObservation>,const FitOptions& = {},pr::Limits = {}) noexcept;

// Factory captures an actual quiescent owner, including its account at capture.
// Profile membership and the exact candidate physical binding are checked.
class Profile {
  // Retains actual captured evidence, not the mutable runtime that produced it.
  // Capture/revalidate are cold scans; these accessors only borrow stored facts.
 public:
  const planner::MinimumHeightCandidate& candidate() const noexcept;
  const runtime::ranking::RuntimeEvidence& evidence() const noexcept;
  const resource::MemoryStatistics& memory_at_capture() const noexcept;
 private:
  friend struct detail::Factory;
  explicit Profile(std::shared_ptr<const detail::ProfileData> x):data_(std::move(x)) {}
  std::shared_ptr<const detail::ProfileData> data_;
};
struct CaptureAttempt { pr::Stop stop=pr::Stop::internal_error; std::optional<Profile> profile; pr::Usage usage; };
[[nodiscard]] CaptureAttempt capture(const planner::CandidateSnapshot&,std::size_t candidate,
    const PhysicalRuntime&,pr::Limits = {}) noexcept;
[[nodiscard]] CaptureAttempt capture(const planner::CandidateSnapshot&,std::size_t candidate,
    const DeltaRuntime&,pr::Limits = {}) noexcept;
[[nodiscard]] CaptureAttempt capture(const planner::CandidateSnapshot&,std::size_t candidate,
    const QuerySession&,pr::Limits = {}) noexcept;
[[nodiscard]] runtime::ranking::Revalidation revalidate(const Profile&,const PhysicalRuntime&) noexcept;
[[nodiscard]] runtime::ranking::Revalidation revalidate(const Profile&,const DeltaRuntime&) noexcept;
[[nodiscard]] runtime::ranking::Revalidation revalidate(const Profile&,const QuerySession&) noexcept;

// Future counts for a declared horizon, not rates measured by C01 (which has
// no clock). All tables/operations must be listed exactly once, including zero.
struct InputDemand { TableId table; workload::Operation operation; U64 inputs{}; };
struct OutputDemand {
  U64 snapshot_requests{}, snapshot_rows_per_request{};
  U64 delta_epochs{}, delta_rows{}, encoded_bytes{};
  U64 checkpoint_requests{}, checkpoint_bytes{}, annotation_changes{};
  // Optional aggregate demand supports snapshots whose row counts vary across
  // the horizon. Absent retains requests * rows_per_request.
  std::optional<U64> snapshot_rows_total{};
};
struct Request {
  std::span<const InputDemand> input;
  OutputDemand output;
  U64 memory_budget_bytes=256U*1024U*1024U;
  pr::Limits limits;
};
enum class Basis { declared_demand, observed_census, observed_complete_detail };
enum class Issue : U64 {
  none=0, profile_missing=1, detail_unavailable=2, stratum_unobserved=4,
  calibration_missing=8, calibration_backend=16, memory_budget=32,
  incompatible_output_mode=64, calibration_mode=128
};
using Issues = U64;
constexpr Issues issue(Issue x) noexcept { return static_cast<Issues>(x); }
struct Confidence {
  Basis basis{Basis::declared_demand};
  workload::Availability availability{workload::Availability::unavailable};
  U64 complete_inputs{}, observed_events{};
  // A sampled count is not a statistical confidence interval or future fact.
};
struct Term {
  Component component{};
  std::optional<std::size_t> descriptor;
  std::optional<Ratio> units, nanoseconds;
  Confidence confidence;
  Issues issues{};
};
struct CandidateEstimate {
  // The term vector owns funded payload; copying this record can allocate.
  // Candidate/Profile handles share their actual immutable owners.
  planner::MinimumHeightCandidate candidate;
  std::optional<Profile> observations;
  pr::ScoreVector<Term> terms;
  std::optional<Ratio> maintenance_ns, snapshot_ns, delta_ns, encoding_ns, checkpoint_ns, annotation_ns, total_ns;
  std::optional<workload::Stamp> observed_stamp;
  std::optional<workload::ModeFacts> observed_modes;
  U64 memory_budget_bytes{};
  std::optional<resource::MemoryStatistics> memory_at_capture;
  // The budget is a separate constraint, never bytes added to nanoseconds.
  // Passing this as-of check does not predict that future state fits the budget.
  bool future_memory_unknown{true};
  Issues issues{};
  CandidateEstimate(const resource::MemoryAccount&,planner::MinimumHeightCandidate);
};
class Result {
  // Handle copies share all copied demand/terms and retained model evidence.
  // Returned views borrow Data; last release can destroy the retained graph.
 public:
  const pr::ScoreVector<CandidateEstimate>& candidates() const noexcept;
  const Calibration& calibration() const noexcept;
  const pr::Usage& usage() const noexcept;
  // Demand is copied into the receiving account; Result never borrows Request.
  std::span<const InputDemand> input_demand() const noexcept;
  const OutputDemand& output_demand() const noexcept;
  static constexpr unsigned format_version=1, arithmetic_version=1;
 private:
  friend struct detail::Factory;
  explicit Result(std::shared_ptr<const detail::ResultData> x):data_(std::move(x)) {}
  std::shared_ptr<const detail::ResultData> data_;
};
struct Attempt { pr::Stop stop=pr::Stop::internal_error; std::optional<Result> result; pr::Usage usage; };
// Produces a decomposition (possibly explicitly unavailable) for EVERY retained
// checked candidate. No choice, proof, owner mutation or automatic C05 enabling.
[[nodiscard]] Attempt estimate(const resource::MemoryAccount&,const planner::CandidateSnapshot&,
    std::span<const Profile>,const Calibration&,const Request&) noexcept;
} // namespace crown::runtime::cost
