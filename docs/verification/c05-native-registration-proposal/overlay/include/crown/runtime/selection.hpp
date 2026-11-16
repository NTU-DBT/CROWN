#pragma once

#include "crown/planner/selection.hpp"
#include "crown/runtime/ranking_evidence.hpp"

namespace crown::runtime::selection {
namespace ps = ::crown::planner::selection;
namespace detail { struct Factory; struct Data; }
class CurrentSelection {
 public:
  CurrentSelection(const CurrentSelection&) noexcept = default;
  CurrentSelection& operator=(const CurrentSelection&) noexcept = default;
  CurrentSelection(CurrentSelection&& other) noexcept : data_(other.data_) {}
  CurrentSelection& operator=(CurrentSelection&& other) noexcept { data_ = other.data_; return *this; }
  const ps::Selection& selection() const noexcept;
  const ranking::RuntimeEvidence& capture() const noexcept;
 private:
  friend struct detail::Factory;
  explicit CurrentSelection(std::shared_ptr<const detail::Data> data) noexcept : data_(std::move(data)) {}
  std::shared_ptr<const detail::Data> data_;
};
struct Attempt {
  ps::Stop stop = ps::Stop::internal_error;
  ps::Stage stage = ps::Stage::admission;
  std::optional<CurrentSelection> selection;
  planner::ranking::Usage usage;
  std::optional<planner::ranking::Stop> component_stop;
  ps::Resource resource = ps::Resource::none;
  planner::ranking::Reasons reasons{};
  ps::PreparationTiming preparation_timing = ps::PreparationTiming::absent;
  std::size_t retained{}, constraint_evaluated{}, primary_evaluated{};
};
// A fresh bounded capture is made even for height-only. The caller preserves
// the underlying owner's exclusive synchronous-access contract throughout.
[[nodiscard]] Attempt select_current(const planner::CandidateSnapshot&, const ps::Source&,
    const PhysicalRuntime&, const ps::Request& = {}, statistics::Limits = {},
    ps::PlanCache* = nullptr, ps::CacheUse = ps::CacheUse::bypass) noexcept;
[[nodiscard]] Attempt select_current(const planner::CandidateSnapshot&, const ps::Source&,
    const DeltaRuntime&, const ps::Request& = {}, statistics::Limits = {},
    ps::PlanCache* = nullptr, ps::CacheUse = ps::CacheUse::bypass) noexcept;
[[nodiscard]] Attempt select_current(const planner::CandidateSnapshot&, const ps::Source&,
    const QuerySession&, const ps::Request& = {}, statistics::Limits = {},
    ps::PlanCache* = nullptr, ps::CacheUse = ps::CacheUse::bypass) noexcept;
} // namespace crown::runtime::selection
