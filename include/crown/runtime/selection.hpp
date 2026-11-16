#pragma once

#include "crown/planner/selection.hpp"
#include "crown/runtime/ranking_evidence.hpp"

namespace crown::runtime::selection {
namespace ps = ::crown::planner::selection;
namespace detail { struct Factory; struct Data; }
// Qualify the selected plan with a real Session's captured source premises.
// The selected plan can differ from the installed plan: inspect the hash match.
// This owns the existing immutable selection/capture, not a live owner handle;
// its prefix is historical after the owner advances. No update work is measured
// retrospectively, especially across replacement or trusted checkpoint restore.
class PatternGuarantee {
 public:
  PatternGuarantee(const PatternGuarantee&) noexcept = default;
  PatternGuarantee& operator=(const PatternGuarantee&) noexcept = default;
  PatternGuarantee(PatternGuarantee&& other) noexcept : data_(other.data_) {}
  PatternGuarantee& operator=(PatternGuarantee&& other) noexcept { data_ = other.data_; return *this; }
  ps::PatternGuarantee selected() const noexcept;
  const UpdatePatternStatus& enforcement() const & noexcept;
  const UpdatePatternStatus& enforcement() const && = delete;
  statistics::OwnerStamp stamp() const noexcept;
  bool selected_plan_matches_capture() const noexcept;
 private:
  friend class CurrentSelection;
  explicit PatternGuarantee(std::shared_ptr<const detail::Data> data) noexcept : data_(std::move(data)) {}
  std::shared_ptr<const detail::Data> data_;
};
class CurrentSelection {
 public:
  CurrentSelection(const CurrentSelection&) noexcept = default;
  CurrentSelection& operator=(const CurrentSelection&) noexcept = default;
  CurrentSelection(CurrentSelection&& other) noexcept : data_(other.data_) {}
  CurrentSelection& operator=(CurrentSelection&& other) noexcept { data_ = other.data_; return *this; }
  const ps::Selection& selection() const noexcept;
  const ranking::RuntimeEvidence& capture() const noexcept;
  // Available only from the explicit measured reoptimization selection entry.
  // Includes capture, ranking, lowering, cache work and temporary teardown.
  std::optional<std::uint64_t> preparation_nanoseconds() const noexcept;
  // Present only with a proved selected case and actual unrejected Session
  // premises from the same capture. O(1), no allocation or fresh live read.
  std::optional<PatternGuarantee> pattern_guarantee() const noexcept;
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
[[nodiscard]] Attempt select_for_reoptimization(const planner::CandidateSnapshot&,const ps::Source&,
    const QuerySession&,const ps::Request& = {},statistics::Limits = {},
    ps::PlanCache* = nullptr,ps::CacheUse = ps::CacheUse::bypass) noexcept;
// Rejects an unmeasured, stale, foreign or differently configured selection.
// Freshness is checked again before native preparation; C02 scores never become
// time estimates. The ordinary native candidate API has no C05 dependency.
void begin_reoptimization(QuerySession&,const CurrentSelection&,reoptimization::Options={});
} // namespace crown::runtime::selection
