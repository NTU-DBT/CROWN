#include "crown/runtime/selection.hpp"
#include "../planner/selection_detail.hpp"
#include "crown/api/error.hpp"
#include <new>
#include <type_traits>

namespace crown::runtime::selection {
namespace sd = ::crown::planner::selection::detail;
namespace pr = ::crown::planner::ranking;
namespace detail {
struct Data { ps::Selection selection; ranking::RuntimeEvidence capture; };
struct Factory {
  static CurrentSelection make(std::shared_ptr<const Data> data) noexcept { return CurrentSelection(std::move(data)); }
};
}
const ps::Selection& CurrentSelection::selection() const noexcept { return data_->selection; }
const ranking::RuntimeEvidence& CurrentSelection::capture() const noexcept { return data_->capture; }
namespace {
std::optional<statistics::Freshness> freshness(const PhysicalRuntime& owner, const statistics::OwnerCapture& captured) {
  return owner.statistics_freshness(captured, 0);
}
std::optional<statistics::Freshness> freshness(const DeltaRuntime& owner, const statistics::OwnerCapture& captured) {
  return owner.statistics_freshness(captured, 0);
}
std::optional<statistics::Freshness> freshness(const QuerySession& owner, const statistics::OwnerCapture& captured) {
  return owner.statistics_freshness(captured, 0);
}
pr::Reasons reason(std::optional<statistics::Freshness> value) {
  if (!value) return pr::reason(pr::Reason::released);
  switch (*value) {
    case statistics::Freshness::current: return 0;
    case statistics::Freshness::within_lag:
    case statistics::Freshness::stale: return pr::reason(pr::Reason::stale);
    case statistics::Freshness::foreign_owner: return pr::reason(pr::Reason::foreign_owner);
    case statistics::Freshness::future_sequence: return pr::reason(pr::Reason::future_sequence);
    case statistics::Freshness::scope_mismatch: return pr::reason(pr::Reason::layer_mismatch);
  }
  return pr::reason(pr::Reason::read_failed);
}
template<class Owner> void boundary(const ranking::RuntimeEvidence& facts, const Owner& owner, sd::Budget& budget) {
  if (!facts.captured()) throw sd::Failure{ps::Stop::boundary_unavailable, ps::Resource::none, {}, pr::reason(pr::Reason::released)};
  const auto& combined = *facts.captured(); const auto& state = combined.state(); const auto& workload = combined.workload();
  budget.work(1); auto reasons = reason(freshness(owner, state));
  budget.work(12);
  if (state.availability() == statistics::Availability::pending_private_state || workload.pending() || facts.inputs().identity().pending)
    reasons |= pr::reason(pr::Reason::pending);
  if (state.stamp().layer != statistics::OwnerLayer::physical || state.physical_source_scope() != statistics::Availability::available)
    reasons |= pr::reason(pr::Reason::layer_mismatch);
  if (state.stamp().owner != workload.stamp().owner || state.stamp().sequence != workload.stamp().committed_epoch ||
      facts.inputs().identity().owner != state.stamp().owner.value || facts.inputs().identity().epoch != state.stamp().sequence)
    reasons |= pr::reason(pr::Reason::source_scope);
  const bool delta_owner = !std::is_same_v<Owner, PhysicalRuntime>;
  if (workload.modes().delta_owner != delta_owner || facts.inputs().identity().modes.delta_owner != delta_owner)
    reasons |= pr::reason(pr::Reason::layer_mismatch);
  if constexpr (std::is_same_v<Owner, QuerySession>) {
    budget.work(12);
    if (!facts.session_context()) reasons |= pr::reason(pr::Reason::read_failed);
    else {
      const auto& context = *facts.session_context(); const auto& metadata = context.metadata(); const auto& modes = workload.modes();
      if (context.status().state == SessionState::dropped || !metadata.state()) reasons |= pr::reason(pr::Reason::released);
      if (metadata.owner() != state.stamp().owner || metadata.sequence() != state.stamp().sequence ||
          context.status().committed_sequence != state.stamp().sequence) reasons |= pr::reason(pr::Reason::source_scope);
      if (metadata.options().mode != modes.requested_mode || metadata.profile().mode != modes.resolved_mode ||
          metadata.options().completion != modes.requested_completion || metadata.profile().completion != modes.resolved_completion ||
          metadata.options().live_maintenance != modes.live_maintenance || metadata.options().view != modes.view ||
          context.workload_options() != workload.options()) reasons |= pr::reason(pr::Reason::mode_changed);
    }
  }
  if (reasons) throw sd::Failure{ps::Stop::boundary_unavailable, ps::Resource::none, {}, reasons};
}
template<class Owner> Attempt current(const planner::CandidateSnapshot& snapshot, const ps::Source& source,
    const Owner& owner, const ps::Request& request, statistics::Limits state_limits, ps::PlanCache* cache, ps::CacheUse use) noexcept {
  Attempt out; std::optional<sd::Operation> operation;
  try {
    constexpr auto origin = std::is_same_v<Owner, PhysicalRuntime> ? sd::Origin::physical :
        (std::is_same_v<Owner, DeltaRuntime> ? sd::Origin::delta : sd::Origin::session);
    operation.emplace(snapshot, source, request, std::optional<pr::Evidence>{}, cache, use, origin);
    operation->admit(); operation->diagnostic.stage = ps::Stage::capture;
    ranking::CaptureOptions capture_options;
    capture_options.source_cardinalities = operation->needs_sources(); capture_options.state_limits = state_limits;
    capture_options.processing = operation->budget.begin_delegate();
    auto captured = ranking::capture(snapshot, owner, capture_options);
    operation->budget.end_delegate(captured.usage);
    if (captured.stop != pr::Stop::complete) {
      if (captured.stop == pr::Stop::internal_error)
        throw sd::Failure{ps::Stop::boundary_unavailable, ps::Resource::none, captured.stop, pr::reason(pr::Reason::read_failed)};
      sd::component_failure(captured.stop, captured.reasons);
    }
    sd::require(captured.evidence.has_value());
    operation->attach(captured.evidence->inputs());
    boundary(*captured.evidence, owner, operation->budget);
    auto prepared = operation->prepare();
    const auto pure = sd::Factory::selection(prepared.data);
    operation->budget.work(); operation->budget.bytes(sizeof(detail::Data));
    // This allocation precedes every cache statistic, eviction and insertion.
    auto data = std::make_shared<const detail::Data>(detail::Data{pure, *captured.evidence});
    auto result = detail::Factory::make(std::move(data));
    operation->finalize(prepared);
    out.selection = std::move(result);
  } catch (const sd::Failure& failure) {
    if (operation) operation->note(failure);
    else { out.stop = failure.stop; out.resource = failure.resource; out.component_stop = failure.component; out.reasons = failure.reasons; }
  } catch (const sd::rd::Failure& failure) {
    if (operation) operation->note(failure.stop);
  } catch (const std::bad_alloc&) {
    if (operation) operation->note({ps::Stop::allocation_failure, ps::Resource::none, {}, 0}); else out.stop = ps::Stop::allocation_failure;
  } catch (const Error& error) {
    if (operation) {
      if (error.code() == "resource_limit") operation->note(pr::Stop::lowering_limit);
      else operation->note({error.code() == "invalid_physical_plan" ? ps::Stop::invalid_handle : ps::Stop::lowering_failure, ps::Resource::none, {}, 0});
    }
  } catch (...) {
    if (operation) operation->note({ps::Stop::internal_error, ps::Resource::none, {}, 0});
  }
  if (operation) {
    operation->finish(); const auto& diagnostic = operation->diagnostic;
    out.stop = diagnostic.stop; out.stage = diagnostic.stage; out.usage = diagnostic.usage;
    out.component_stop = diagnostic.component_stop; out.resource = diagnostic.resource; out.reasons = diagnostic.reasons;
    out.preparation_timing = diagnostic.preparation_timing; out.retained = diagnostic.retained;
    out.constraint_evaluated = diagnostic.constraint_evaluated; out.primary_evaluated = diagnostic.primary_evaluated;
  }
  return out;
}
}
Attempt select_current(const planner::CandidateSnapshot& s, const ps::Source& source, const PhysicalRuntime& owner,
    const ps::Request& request, statistics::Limits limits, ps::PlanCache* cache, ps::CacheUse use) noexcept {
  return current(s, source, owner, request, limits, cache, use);
}
Attempt select_current(const planner::CandidateSnapshot& s, const ps::Source& source, const DeltaRuntime& owner,
    const ps::Request& request, statistics::Limits limits, ps::PlanCache* cache, ps::CacheUse use) noexcept {
  return current(s, source, owner, request, limits, cache, use);
}
Attempt select_current(const planner::CandidateSnapshot& s, const ps::Source& source, const QuerySession& owner,
    const ps::Request& request, statistics::Limits limits, ps::PlanCache* cache, ps::CacheUse use) noexcept {
  return current(s, source, owner, request, limits, cache, use);
}
} // namespace crown::runtime::selection
