#pragma once

#include "crown/planner/candidates.hpp"
#include "crown/runtime/session.hpp"
#include <memory>
#include <variant>

namespace crown::observability {
class StatisticsExplanation;
enum class RuntimePresence { compile_only, live, stopped_retained, released };
enum class ExplanationKind { physical, runtime, session };
enum class GaugeAvailability { available, compile_only, pending_private_state, runtime_released };
// Current/retained owner configuration is separate from immutable begin-bound
// attempt configuration. No arbitrary public metadata constructor exists.
class ModeDescriptor {
 public:
  [[nodiscard]] static ModeDescriptor compile_only(PhysicalPlan);
  [[nodiscard]] static ModeDescriptor capture(const runtime::DeltaRuntime&);
  [[nodiscard]] static ModeDescriptor capture(const runtime::QuerySession&);
  [[nodiscard]] const PhysicalPlan& plan() const;
  [[nodiscard]] bool running() const;
  [[nodiscard]] std::uint64_t owner() const;
  [[nodiscard]] std::uint64_t sequence() const;
  [[nodiscard]] std::optional<runtime::DeltaState> state() const;
  [[nodiscard]] RuntimePresence presence() const;
  [[nodiscard]] const std::optional<runtime::DeltaOptions>& options() const;
  [[nodiscard]] const std::optional<runtime::DeltaRuntimeProfile>& profile() const;
 private:
  struct Data;
  explicit ModeDescriptor(std::shared_ptr<const Data>);
  friend class StatisticsExplanation;
  [[nodiscard]] static ModeDescriptor from_session(const runtime::SessionReportMetadata&,const runtime::SessionStatus&);
  [[nodiscard]] const Data& data() const;
  std::shared_ptr<const Data> data_;
};
using HeightEvidence=std::variant<std::monostate,planner::ValidatedIncumbent,
    planner::VerifiedOptimum,planner::MinimumHeightCandidate>;
enum class HeightStatus { checked_upper, verified_original_minimum, checked_constant_operator };
struct ExplainLimits {
  std::size_t nodes=100000;
};
// Admission uses exact native Catalog/Query comparison, never JSON, a digest,
// a caller-supplied validation flag, or alpha-equivalence. The immutable plan
// was already admitted by P08. Serialization is a separate explicit operation.
class PlanExplanation {
 public:
  [[nodiscard]] static PlanExplanation create(PhysicalPlan,HeightEvidence={},
      std::optional<planner::CandidateSnapshot> family={},ExplainLimits={});
  [[nodiscard]] static PlanExplanation capture(const runtime::DeltaRuntime&,HeightEvidence={},
      std::optional<planner::CandidateSnapshot> family={},ExplainLimits={});
  // Uses the session's actual owning typed plan; no supplied-plan/hash join.
  [[nodiscard]] static PlanExplanation capture(const runtime::QuerySession&,HeightEvidence={},
      std::optional<planner::CandidateSnapshot> family={},ExplainLimits={});
  [[nodiscard]] const PhysicalPlan& plan() const;
  [[nodiscard]] ExplanationKind kind() const;
  [[nodiscard]] GaugeAvailability gauge_availability() const;
  [[nodiscard]] const std::optional<runtime::CommittedStateGauges>& gauges() const;
  [[nodiscard]] const std::optional<runtime::CursorObservation>& cursor() const;
  [[nodiscard]] const std::optional<runtime::SessionStatus>& session_status() const;
  [[nodiscard]] const ModeDescriptor& mode() const;
  [[nodiscard]] HeightStatus height_status() const;
  [[nodiscard]] std::size_t selected_height() const;
  [[nodiscard]] const HeightEvidence& evidence() const;
  [[nodiscard]] std::optional<planner::VerifiedOptimum> optimum() const;
  [[nodiscard]] const std::optional<planner::CandidateSnapshot>& family() const;
  [[nodiscard]] const std::optional<runtime::ObservationSnapshot>& observation() const;
  [[nodiscard]] const std::vector<runtime::TraceRecord>& trace_records() const;
 private:
  struct Data;
  explicit PlanExplanation(std::shared_ptr<const Data>);
  friend class StatisticsExplanation;
  [[nodiscard]] static PlanExplanation capture_statistics_context(const runtime::DeltaRuntime&,ExplainLimits);
  [[nodiscard]] static PlanExplanation make(ModeDescriptor,HeightEvidence,
      std::optional<planner::CandidateSnapshot>,std::optional<runtime::ObservationSnapshot>,ExplainLimits,
      ExplanationKind=ExplanationKind::physical,GaugeAvailability=GaugeAvailability::compile_only,
      std::optional<runtime::CommittedStateGauges> = {},std::optional<runtime::CursorObservation> = {},
      std::optional<runtime::SessionStatus> = {},std::vector<runtime::TraceRecord> = {});
  [[nodiscard]] const Data& data() const;
  std::shared_ptr<const Data> data_;
};
} // namespace crown::observability
