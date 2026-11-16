#include "crown/runtime/selection.hpp"
#include "../planner/selection_detail.hpp"
#include "crown/api/error.hpp"
#include <new>
#include <type_traits>

namespace crown::runtime::selection {
namespace sd = ::crown::planner::selection::detail;
namespace pr = ::crown::planner::ranking;
namespace detail {
struct Data { ps::Selection selection; ranking::RuntimeEvidence capture;std::optional<std::uint64_t> preparation_ns; };
struct Factory {
  static CurrentSelection make(std::shared_ptr<const Data> data) noexcept { return CurrentSelection(std::move(data)); }
};
}
const ps::Selection& CurrentSelection::selection() const noexcept { return data_->selection; }
const ranking::RuntimeEvidence& CurrentSelection::capture() const noexcept { return data_->capture; }
std::optional<std::uint64_t> CurrentSelection::preparation_nanoseconds() const noexcept {return data_->preparation_ns;}
std::optional<PatternGuarantee> CurrentSelection::pattern_guarantee() const noexcept {
  const auto& context = data_->capture.session_context();
  if (!data_->selection.pattern_guarantee() || !context || !context->status().update_patterns ||
      context->status().update_patterns->violation) return {};
  return PatternGuarantee(data_);
}
ps::PatternGuarantee PatternGuarantee::selected() const noexcept { return *data_->selection.pattern_guarantee(); }
const UpdatePatternStatus& PatternGuarantee::enforcement() const & noexcept {
  return *data_->capture.session_context()->status().update_patterns;
}
statistics::OwnerStamp PatternGuarantee::stamp() const noexcept { return data_->capture.captured()->state().stamp(); }
bool PatternGuarantee::selected_plan_matches_capture() const noexcept {
  const auto& actual = enforcement().physical_sha256;
  return data_->selection.plan().physical_sha256() == std::string_view(actual.data(), actual.size());
}
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
// Caller retains exclusive synchronous owner access through capture and publication.
// Current stamps alone do not establish pending, source-layer or mode agreement.
template<class Owner> void boundary(const ranking::RuntimeEvidence& facts, const Owner& owner, sd::Budget& budget,
    const std::optional<crown::patterns::Declaration>& requested) {
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
      if (requested) {
        const auto& profile=context.status().update_patterns;
        sd::require(profile.has_value() && !profile->violation,ps::Stop::boundary_unavailable);
        budget.work(66);
        sd::require(profile->monitored_sequence==state.stamp().sequence &&
            profile->declaration.source_sha256()==requested->source_sha256() &&
            profile->declaration.source_tables()==requested->source_tables(),ps::Stop::binding_mismatch);
        const auto actual=profile->declaration.rules(),expected=requested->rules();
        sd::require(actual.size()==expected.size(),ps::Stop::binding_mismatch);
        for(std::size_t i=0;i<actual.size();++i) {
          budget.work();sd::require(actual[i]==expected[i],ps::Stop::binding_mismatch);
        }
      }
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
// Keep the public noexcept diagnostic mapper around the one prepublication
// capture/prepare/cache transaction; source/row ownership is in retained native graphs.
template<class Owner> Attempt current(const planner::CandidateSnapshot& snapshot, const ps::Source& source,
    const Owner& owner, const ps::Request& request, statistics::Limits state_limits, ps::PlanCache* cache, ps::CacheUse use,bool measured=false) noexcept {
  using Clock=std::chrono::steady_clock;const auto started=measured?Clock::now():Clock::time_point{};
  Attempt out; std::optional<sd::Operation> operation;
  std::shared_ptr<detail::Data> published;
  try {
    constexpr auto origin = std::is_same_v<Owner, PhysicalRuntime> ? sd::Origin::physical :
        (std::is_same_v<Owner, DeltaRuntime> ? sd::Origin::delta : sd::Origin::session);
    const auto plan=[&] {
      if constexpr(std::is_same_v<Owner,QuerySession>)return owner.report_metadata().plan();
      else return owner.plan();
    }();
    operation.emplace(snapshot, source, request, std::optional<pr::Evidence>{}, cache, use, origin,plan.account());
    operation->admit();
    if constexpr (!std::is_same_v<Owner,QuerySession>)
      sd::require(!request.update_patterns,ps::Stop::unsupported_model);
    operation->diagnostic.stage = ps::Stage::capture;
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
    boundary(*captured.evidence, owner, operation->budget, request.update_patterns);
    auto prepared = operation->prepare();
    const auto pure = sd::Factory::selection(prepared.data);
    operation->budget.work(); operation->budget.bytes(sizeof(detail::Data));
    // This allocation precedes every cache statistic, eviction and insertion.
    constexpr resource::MemoryAttribution wrapper{resource::MemoryOwnerKind::capture,13};
    published = resource::make_accounted_shared<detail::Data>(wrapper,operation->budget.memory,
        resource::MemoryPurpose::capture,detail::Data{pure,*captured.evidence,{}});
    auto result = detail::Factory::make(published);
    operation->finalize(prepared);
    out.selection = std::move(result);
  } catch (const sd::Failure& failure) {
    if (operation) operation->note(failure);
    else { out.stop = failure.stop; out.resource = failure.resource; out.component_stop = failure.component; out.reasons = failure.reasons; }
  } catch (const sd::rd::Failure& failure) {
    if (operation) operation->note(failure.stop);
  } catch (const std::bad_alloc&) {
    if (operation) operation->note({ps::Stop::allocation_failure, ps::Resource::none, {}, 0}); else out.stop = ps::Stop::allocation_failure;
  } catch (const storage::IndexFailure& failure) {
    if(operation) {
      const auto code=failure.code();
      if(code=="storage_work_limit" || code=="storage_capacity" || code=="storage_overflow")operation->note(pr::Stop::lowering_limit);
      else operation->note({ps::Stop::internal_error,ps::Resource::none,{},0});
    }
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
  operation.reset();
  if(measured && out.selection) {
    const auto ended=Clock::now();
    if(ended>=started)published->preparation_ns=static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(ended-started).count());
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
Attempt select_for_reoptimization(const planner::CandidateSnapshot& snapshot,const ps::Source& source,const QuerySession& session,
    const ps::Request& request,statistics::Limits limits,ps::PlanCache* cache,ps::CacheUse use) noexcept {
  return current(snapshot,source,session,request,limits,cache,use,true);
}
// Historical choices require fresh owner/interval/producer binding and real timing.
void begin_reoptimization(QuerySession& session,const CurrentSelection& choice,reoptimization::Options options) {
  using Clock=std::chrono::steady_clock;const auto started=Clock::now();
  const auto measured=choice.preparation_nanoseconds();
  if(!measured)throw Error("reoptimization_unmeasured_selection","prepare a measured selection before reoptimization");
  if(choice.selection().request().update_patterns) {
    const auto profile=session.update_pattern_status();
    if(!profile.declaration || profile.violation)
      throw Error("reoptimization_stale_selection","declared pattern monitor is unavailable or rejected input");
  }
  const auto checked=ranking::revalidate(choice.capture(),session);
  const auto changed=pr::reason(pr::Reason::interval_changed)|pr::reason(pr::Reason::mode_changed);
  if(checked.boundary || (checked.depth&changed) || !checked.usable(choice.selection().effective_policy()))
    throw Error("reoptimization_stale_selection","selection owner, epoch, configuration or required observations changed");
  const auto metadata=session.report_metadata();const auto& selected=choice.selection().plan();const auto& a=metadata.plan().options();const auto& b=selected.options();
  if(metadata.plan().physical_source_sha256()!=selected.physical_source_sha256() || a.indexed_storage!=b.indexed_storage ||
      a.policy.arithmetic!=b.policy.arithmetic || a.policy.planner!=b.policy.planner || a.policy.optimization!=b.policy.optimization ||
      a.policy.cost_model!=b.policy.cost_model || a.limits.work_limit!=b.limits.work_limit || a.limits.identity.work_limit!=b.limits.identity.work_limit)
    throw Error("reoptimization_selection_binding","selection source or physical producer options differ from the session");
  const auto& stamp=choice.capture().inputs().identity();
  if(options.expected && (options.expected->owner!=stamp.owner || options.expected->epoch!=stamp.epoch))
    throw Error("reoptimization_stale_source","requested source differs from the checked selection");
  options.expected=reoptimization::Boundary{stamp.owner,stamp.epoch};
  const auto ended=Clock::now();
  if(ended<started)throw Error("reoptimization_selection_clock","selection validation clock regressed");
  const auto validation=static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(ended-started).count());
  if(validation>UINT64_MAX-*measured)throw Error("reoptimization_selection_cost","selection preparation cost overflowed");
  session.begin_reoptimization_with_cost(choice.selection().selected(),std::move(options),*measured+validation);
}
} // namespace crown::runtime::selection
