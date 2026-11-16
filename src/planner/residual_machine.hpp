#pragma once
#include "crown/planner/residual.hpp"
#include "continuation_machine.hpp"
#include <exception>
#include <limits>

namespace crown::planner::residual_detail {
namespace cd = continuation_detail;
struct Limited : std::exception {
  ResidualStopReason reason;
  explicit Limited(ResidualStopReason r) noexcept : reason(r) {}
  const char* what() const noexcept override { return "residual resource limit"; }
};
// Cumulative logical construction, including discarded drafts and replay.
// Call prepare before throwing work and commit only after its success, with
// exclusive access between them. Capacity, delegated storage and whole binding
// admission copies are outside this record/cell account (see residual_candidates).
struct ConstructionBudget {
  ResidualLimits limits;
  std::uint64_t records = 0, cells = 0;
  explicit ConstructionBudget(ResidualLimits value) noexcept : limits(value) {}
  void prepare(std::uint64_t r, std::uint64_t c) const {
    const auto maximum = std::numeric_limits<std::uint64_t>::max();
    if (r > maximum - records || c > maximum - cells) throw Limited(ResidualStopReason::counter_overflow);
    if (limits.record_limit && (records > *limits.record_limit || r > *limits.record_limit - records)) throw Limited(ResidualStopReason::record_limit);
    if (limits.cell_limit && (cells > *limits.cell_limit || c > *limits.cell_limit - cells)) throw Limited(ResidualStopReason::cell_limit);
  }
  void commit(std::uint64_t r, std::uint64_t c) noexcept { records += r; cells += c; }
};
enum class Event { advanced, complete, stopped, need_original_exact, checked_upper, invalid_trace };
struct Step {
  Event event = Event::advanced;
  ResidualStopReason reason = ResidualStopReason::none;
  StopReason exact_reason = StopReason::none;
  std::size_t requested_depth = 0;
};
struct TraceData {
  std::shared_ptr<const cd::BindingData> binding;
  std::shared_ptr<const ResidualTraceRecord> record;
};
// Private payload: exactly one of checked/exact_upper supplies an original-
// query upper witness. Neither a prefix proof nor caller-edited data enters it.
struct CandidateData {
  std::shared_ptr<const cd::BindingData> binding;
  std::shared_ptr<const TraceData> trace;
  std::shared_ptr<const cd::CheckedUpper> checked;
  std::optional<ValidatedIncumbent> exact_upper;
  ResidualOrigin origin = ResidualOrigin::hierarchy_seed;
};
class InducedViewMachine {
 public:
  InducedViewMachine(std::shared_ptr<const cd::BindingData>, std::shared_ptr<const std::vector<std::size_t>>, std::shared_ptr<ConstructionBudget>);
  ~InducedViewMachine();
  InducedViewMachine(InducedViewMachine&&) noexcept;
  InducedViewMachine& operator=(InducedViewMachine&&) noexcept;
  Step step(const cd::UnitContext&);
  std::shared_ptr<const ResidualView> view() const noexcept;
  std::size_t current_depth() const noexcept;
 private:
  struct Impl; std::unique_ptr<Impl> data_;
};
class ReductionMachine {
 public:
  ReductionMachine(std::shared_ptr<const cd::BindingData>, std::shared_ptr<ConstructionBudget>);
  ~ReductionMachine();
  ReductionMachine(ReductionMachine&&) noexcept;
  ReductionMachine& operator=(ReductionMachine&&) noexcept;
  Step step(const cd::UnitContext&);
  ResidualPhase phase() const noexcept;
  const ResidualStatistics& statistics() const noexcept;
  std::size_t current_depth() const noexcept;
  std::shared_ptr<const ResidualTraceRecord> trace_record() const noexcept;
 private:
  struct Impl; std::unique_ptr<Impl> data_;
};
class TraceReplayMachine {
 public:
  TraceReplayMachine(std::shared_ptr<const cd::BindingData>, std::shared_ptr<const ResidualTraceRecord>, std::shared_ptr<ConstructionBudget>);
  ~TraceReplayMachine();
  Step step(const cd::UnitContext&);
  std::size_t current_depth() const noexcept;
  ResidualTraceReport report() const noexcept;
 private:
  struct Impl; std::unique_ptr<Impl> data_;
};
class ReconstructionMachine {
 public:
  ReconstructionMachine(std::shared_ptr<const cd::BindingData>, std::shared_ptr<const ResidualTraceRecord>, std::shared_ptr<ConstructionBudget>);
  ~ReconstructionMachine();
  ReconstructionMachine(ReconstructionMachine&&) noexcept;
  ReconstructionMachine& operator=(ReconstructionMachine&&) noexcept;
  Step step(const cd::UnitContext&);
  ResidualPhase phase() const noexcept;
  const ResidualStatistics& statistics() const noexcept;
  std::size_t current_depth() const noexcept;
  std::shared_ptr<const cd::CheckedUpper> checked_upper() const noexcept;
  ResidualOrigin origin() const noexcept;
  SearchProgress exact_progress() const noexcept;
  LimitChange raise_exact_limits(ContinuationLimits) noexcept;
 private:
  struct Impl; std::unique_ptr<Impl> data_;
};
}  // namespace crown::planner::residual_detail
