#pragma once
#include "crown/planner/search.hpp"

namespace crown::observability {
enum class QueryExplainSource { exact_search, certificate_replay, checked_upper, verified_optimum, verified_infeasible, checked_certificate };
enum class QueryHeightStatus { unknown, owner_checked_upper_unpublished, checked_upper, verified_optimum, verified_infeasible };
struct QueryExplainLimits { std::size_t witness_nodes=100000,certificate_entries=1000000; };
// Immutable owning read. Capture requires the producer's existing exclusive
// caller discipline, and performs no advance, replay, recognition or JSON work.
// No constructor accepts editable progress, flags, trees or legacy aggregates.
class QueryExplanation {
 public:
  [[nodiscard]] static QueryExplanation capture(const planner::ExactSearch&,QueryExplainLimits={});
  [[nodiscard]] static QueryExplanation capture(const planner::CertificateReplay&,QueryExplainLimits={});
  [[nodiscard]] static QueryExplanation from(planner::ValidatedIncumbent,QueryExplainLimits={});
  [[nodiscard]] static QueryExplanation from(planner::VerifiedOptimum,QueryExplainLimits={});
  [[nodiscard]] static QueryExplanation from(planner::VerifiedInfeasible,QueryExplainLimits={});
  [[nodiscard]] static QueryExplanation from(planner::CheckedCertificate,QueryExplainLimits={});
  [[nodiscard]] const planner::SearchBinding& binding() const;
  [[nodiscard]] QueryExplainSource source() const;
  [[nodiscard]] QueryHeightStatus height_status() const;
  [[nodiscard]] std::optional<std::size_t> lower() const;
  // A numeric producer upper can precede a published witness; tree export cannot.
  [[nodiscard]] std::optional<std::size_t> upper() const;
  [[nodiscard]] const std::optional<planner::SearchProgress>& search_progress() const;
  [[nodiscard]] const std::optional<planner::ReplayProgress>& replay_progress() const;
  [[nodiscard]] const std::optional<planner::SearchPolicy>& policy() const;
  [[nodiscard]] const std::optional<planner::ContinuationLimits>& search_limits() const;
  [[nodiscard]] const std::optional<planner::ReplayOptions>& replay_limits() const;
  [[nodiscard]] const std::optional<planner::ValidatedIncumbent>& witness() const;
  [[nodiscard]] const std::optional<planner::VerifiedOptimum>& optimum() const;
  [[nodiscard]] const std::optional<planner::VerifiedInfeasible>& infeasibility() const;
  [[nodiscard]] const std::optional<planner::CheckedCertificate>& checked_certificate() const;
  [[nodiscard]] const planner::HeightCertificate* certificate() const;
 private:
  struct Data;
  explicit QueryExplanation(std::shared_ptr<const Data>);
  [[nodiscard]] static QueryExplanation finish(std::shared_ptr<Data>,QueryExplainLimits);
  [[nodiscard]] const Data& data() const;
  std::shared_ptr<const Data> data_;
};
} // namespace crown::observability
