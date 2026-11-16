#pragma once
#include "crown/observability/explain.hpp"
#include "crown/runtime/combined_statistics.hpp"

namespace crown::observability {
struct StatisticsCaptureOptions {
  // Absent means metadata/workload only. No default state traversal.
  // An explicit request owns vectors; copying options can allocate before capture.
  std::optional<runtime::statistics::OwnerRequest> state;
  runtime::statistics::Limits state_limits;
  ExplainLimits structure;
};
enum class IntervalComparison { same, changed, foreign_owner, saturated, unavailable };
struct StatisticsComparison {
  std::uint64_t previous_owner{},previous_sequence{},actual_owner{},actual_sequence{},max_event_lag{};
  std::optional<runtime::statistics::Freshness> data;
  IntervalComparison configuration=IntervalComparison::unavailable;
  IntervalComparison reset=IntervalComparison::unavailable;
  IntervalComparison segment=IntervalComparison::unavailable;
};
// Factory-only owning report. No constructor accepts caller stamps, paired
// snapshots, availability flags, or an unchecked legacy context.
class StatisticsExplanation {
 public:
  StatisticsExplanation(const StatisticsExplanation&) noexcept=default;
  StatisticsExplanation(StatisticsExplanation&& other) noexcept:data_(other.data_) {}
  StatisticsExplanation& operator=(const StatisticsExplanation&) noexcept=default;
  StatisticsExplanation& operator=(StatisticsExplanation&& other) noexcept {data_=other.data_;return *this;}
  [[nodiscard]] static StatisticsExplanation capture(const runtime::DeltaRuntime&,
      const StatisticsCaptureOptions& = {},const StatisticsExplanation* previous=nullptr,std::uint64_t max_event_lag=0);
  [[nodiscard]] static StatisticsExplanation capture(const runtime::QuerySession&,
      const StatisticsCaptureOptions& = {},const StatisticsExplanation* previous=nullptr,std::uint64_t max_event_lag=0);
  [[nodiscard]] const runtime::CompiledProgram& plan() const noexcept;
  [[nodiscard]] const ModeDescriptor& mode() const noexcept;
  [[nodiscard]] const std::optional<runtime::SessionStatus>& session() const noexcept;
  [[nodiscard]] const runtime::ObservationSnapshot& observation() const noexcept;
  [[nodiscard]] const runtime::CapturedTraceRecords& trace() const noexcept;
  [[nodiscard]] const std::optional<runtime::statistics::CombinedCapture>& combined() const noexcept;
  [[nodiscard]] const runtime::workload::Options& workload_options() const noexcept;
  [[nodiscard]] bool state_requested() const noexcept;
  [[nodiscard]] const std::optional<StatisticsComparison>& comparison() const noexcept;
  static constexpr std::uint32_t schema_version=3;
 private:
  struct Data;
  explicit StatisticsExplanation(std::shared_ptr<const Data> value):data_(std::move(value)) {}
  [[nodiscard]] static StatisticsExplanation make(PlanExplanation,
      std::optional<runtime::statistics::CombinedCapture>,runtime::workload::Options,bool,
      const StatisticsExplanation*,std::uint64_t);
  std::shared_ptr<const Data> data_;
};
}
