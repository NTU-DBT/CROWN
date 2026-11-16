#pragma once

#include "crown/planner/candidates.hpp"
#include "crown/runtime/delta.hpp"
#include <memory>
#include <variant>

namespace crown::observability {
// Mode identity is captured from a real runtime. It is not a history of prior
// attempts: the current observation overlay has no per-attempt mode generation.
class ModeDescriptor {
 public:
  [[nodiscard]] static ModeDescriptor compile_only(PhysicalPlan);
  [[nodiscard]] static ModeDescriptor capture(const runtime::DeltaRuntime&);
  [[nodiscard]] const PhysicalPlan& plan() const;
  [[nodiscard]] bool running() const;
  [[nodiscard]] std::uint64_t owner() const;
  [[nodiscard]] std::uint64_t sequence() const;
  [[nodiscard]] runtime::DeltaState state() const;
  [[nodiscard]] const std::optional<runtime::DeltaOptions>& options() const;
  [[nodiscard]] const std::optional<runtime::DeltaRuntimeProfile>& profile() const;
 private:
  struct Data;
  explicit ModeDescriptor(std::shared_ptr<const Data>);
  [[nodiscard]] const Data& data() const;
  std::shared_ptr<const Data> data_;
};
using HeightEvidence=std::variant<std::monostate,planner::ValidatedIncumbent,
    planner::VerifiedOptimum,planner::MinimumHeightCandidate>;
enum class HeightStatus { checked_upper, verified_original_minimum };
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
  [[nodiscard]] const PhysicalPlan& plan() const;
  [[nodiscard]] const ModeDescriptor& mode() const;
  [[nodiscard]] HeightStatus height_status() const;
  [[nodiscard]] std::size_t selected_height() const;
  [[nodiscard]] const HeightEvidence& evidence() const;
  [[nodiscard]] std::optional<planner::VerifiedOptimum> optimum() const;
  [[nodiscard]] const std::optional<planner::CandidateSnapshot>& family() const;
  [[nodiscard]] const std::optional<runtime::ObservationSnapshot>& observation() const;
 private:
  struct Data;
  explicit PlanExplanation(std::shared_ptr<const Data>);
  [[nodiscard]] static PlanExplanation make(ModeDescriptor,HeightEvidence,
      std::optional<planner::CandidateSnapshot>,std::optional<runtime::ObservationSnapshot>,ExplainLimits);
  [[nodiscard]] const Data& data() const;
  std::shared_ptr<const Data> data_;
};
} // namespace crown::observability
