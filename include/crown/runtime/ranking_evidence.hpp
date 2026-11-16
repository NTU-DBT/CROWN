#pragma once
#include "crown/planner/ranking.hpp"
#include "crown/runtime/combined_statistics.hpp"
#include "crown/runtime/session.hpp"

namespace crown::runtime::ranking {
namespace pr=::crown::planner::ranking;
namespace detail {struct Factory; struct Data;}
struct CaptureOptions {
  bool source_cardinalities=true;
  statistics::Limits state_limits;
  pr::Limits processing;
};
class RuntimeEvidence {
 public:
  RuntimeEvidence(const RuntimeEvidence&) noexcept=default;
  RuntimeEvidence& operator=(const RuntimeEvidence&) noexcept=default;
  RuntimeEvidence(RuntimeEvidence&& x) noexcept:data_(x.data_) {}
  RuntimeEvidence& operator=(RuntimeEvidence&& x) noexcept {data_=x.data_;return *this;}
  const pr::Evidence& inputs() const noexcept;
  const std::optional<statistics::CombinedCapture>& captured() const noexcept;
  const std::optional<SessionStatisticsContext>& session_context() const noexcept;
 private:
  friend struct detail::Factory;
  explicit RuntimeEvidence(std::shared_ptr<const detail::Data> data) noexcept:data_(std::move(data)) {}
  std::shared_ptr<const detail::Data> data_;
};
struct CaptureAttempt {
  pr::Stop stop=pr::Stop::internal_error;
  std::optional<RuntimeEvidence> evidence;
  pr::Usage usage;
  pr::Reasons reasons{};
};
struct Revalidation {
  // Actual committed owner-boundary/read reasons, independent of whether a
  // particular statistical policy has usable observations in that boundary.
  pr::Reasons boundary{}, depth{}, memory{};
  bool usable(pr::Policy p) const noexcept {
    switch(p){case pr::Policy::height_only:return true;
      case pr::Policy::committed_input_native_depth:return depth==0;
      case pr::Policy::tuple_index_slots:return memory==0;}
    return false;
  }
  bool all_facts_usable() const noexcept {return depth==0 && memory==0;}
};
[[nodiscard]] CaptureAttempt capture(const planner::CandidateSnapshot&,const PhysicalRuntime&,const CaptureOptions& = {}) noexcept;
[[nodiscard]] CaptureAttempt capture(const planner::CandidateSnapshot&,const DeltaRuntime&,const CaptureOptions& = {}) noexcept;
[[nodiscard]] CaptureAttempt capture(const planner::CandidateSnapshot&,const QuerySession&,const CaptureOptions& = {}) noexcept;
[[nodiscard]] Revalidation revalidate(const RuntimeEvidence&,const PhysicalRuntime&) noexcept;
[[nodiscard]] Revalidation revalidate(const RuntimeEvidence&,const DeltaRuntime&) noexcept;
[[nodiscard]] Revalidation revalidate(const RuntimeEvidence&,const QuerySession&) noexcept;
// Height-only uses the owner account without a source-fact capture/binding;
// source-aware select_current has its separate fresh actual-owner admission.
[[nodiscard]] pr::Attempt rank_current(const planner::CandidateSnapshot&,const PhysicalRuntime&,const pr::Request& = {},statistics::Limits = {}) noexcept;
[[nodiscard]] pr::Attempt rank_current(const planner::CandidateSnapshot&,const DeltaRuntime&,const pr::Request& = {},statistics::Limits = {}) noexcept;
[[nodiscard]] pr::Attempt rank_current(const planner::CandidateSnapshot&,const QuerySession&,const pr::Request& = {},statistics::Limits = {}) noexcept;
} // namespace crown::runtime::ranking
