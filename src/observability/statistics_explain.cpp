#include "crown/observability/statistics_explain.hpp"
#include "crown/api/error.hpp"
#include "crown/resource/ownership.hpp"

namespace crown::observability {
namespace ws=runtime::workload;
namespace st=runtime::statistics;
// Retains current captured graphs; previous-report comparison stores values only.
struct StatisticsExplanation::Data {
  PlanExplanation context;
  std::optional<st::CombinedCapture> combined;
  ws::Options options;
  bool requested;
  std::optional<StatisticsComparison> comparison;
};
StatisticsExplanation StatisticsExplanation::make(PlanExplanation context,std::optional<st::CombinedCapture> combined,
    ws::Options options,bool requested,const StatisticsExplanation* previous,std::uint64_t lag) {
  const auto& mode=context.mode();const auto& observed=*context.observation();
  const bool observation_owner=observed.options.mode==runtime::ObservationMode::off?
      observed.support_owner==0:observed.support_owner==mode.owner();
  if(!observation_owner || !mode.options() || observed.options!=mode.options()->physical.support.observation)
    throw Error("statistics_binding","observation and current report owner/options disagree");
  if(combined){
    const auto& state=combined->state();const auto& work=combined->workload();const auto& facts=work.modes();
    const auto& opts=*mode.options();const auto& profile=*mode.profile();
    if(state.stamp().owner.value!=mode.owner() || state.stamp().sequence!=mode.sequence() ||
        state.plan().physical_sha256()!=mode.plan().physical_sha256() || work.options()!=options ||
        work.pending()!=(context.gauge_availability()==GaugeAvailability::pending_private_state) ||
        !facts.delta_owner || facts.requested_mode!=opts.mode || facts.requested_completion!=opts.completion ||
        facts.resolved_mode!=profile.mode || facts.resolved_completion!=profile.completion ||
        facts.live_maintenance!=profile.live_maintenance || facts.view!=profile.view)
      throw Error("statistics_binding","state/workload and current report boundary disagree");
  }else if(mode.presence()!=RuntimePresence::released)throw Error("statistics_binding","live report lacks its actual statistics owner");
  if(observed.current_configuration){const auto& current=*observed.current_configuration;
    if(current.support_owner()!=mode.owner() || current.mode()!=mode.profile()->mode ||
        current.completion()!=mode.profile()->completion || current.live_maintenance()!=mode.profile()->live_maintenance ||
        current.view()!=mode.profile()->view)
      throw Error("statistics_binding","current observation configuration differs from actual mode");
  }
  const auto account=context.plan().account();
  auto result=resource::make_accounted_shared<Data>({resource::MemoryOwnerKind::capture,8},account,
      resource::MemoryPurpose::capture,Data{std::move(context),std::move(combined),options,requested,{}});
  if(previous){
    StatisticsComparison comparison;comparison.previous_owner=previous->mode().owner();comparison.previous_sequence=previous->mode().sequence();
    comparison.actual_owner=result->context.mode().owner();comparison.actual_sequence=result->context.mode().sequence();comparison.max_event_lag=lag;
    if(previous->combined() && result->combined){
      const auto& old=previous->combined()->workload();const auto& now=result->combined->workload();
      comparison.data=st::compare_freshness(previous->combined()->state().stamp(),result->combined->state().stamp(),lag);
      const auto domain=[&](std::uint64_t a,std::uint64_t b,bool saturated){
        return old.stamp().owner!=now.stamp().owner?IntervalComparison::foreign_owner:
            saturated?IntervalComparison::saturated:a==b?IntervalComparison::same:IntervalComparison::changed;
      };
      comparison.configuration=domain(old.stamp().configuration_generation,now.stamp().configuration_generation,
          old.stamp().configuration_saturated || now.stamp().configuration_saturated);
      comparison.reset=domain(old.stamp().reset_generation,now.stamp().reset_generation,old.stamp().reset_saturated || now.stamp().reset_saturated);
      comparison.segment=domain(old.stamp().segment,now.stamp().segment,old.stamp().segment_saturated || now.stamp().segment_saturated);
    }
    result->comparison=comparison;
  }
  return StatisticsExplanation(std::move(result));
}
StatisticsExplanation StatisticsExplanation::capture(const runtime::DeltaRuntime& runtime,const StatisticsCaptureOptions& options,
    const StatisticsExplanation* previous,std::uint64_t lag) {
  auto context=PlanExplanation::capture_statistics_context(runtime,options.structure);
  const st::OwnerRequest empty;
  auto combined=runtime.capture_combined_statistics(options.state?*options.state:empty,options.state_limits);
  return make(std::move(context),std::move(combined),runtime.workload_statistics_options(),options.state.has_value(),previous,lag);
}
StatisticsExplanation StatisticsExplanation::capture(const runtime::QuerySession& session,const StatisticsCaptureOptions& options,
    const StatisticsExplanation* previous,std::uint64_t lag) {
  const auto native=session.capture_statistics_context(options.state,options.state_limits);
  const auto availability=!native.combined()?GaugeAvailability::runtime_released:
      native.combined()->workload().pending()?GaugeAvailability::pending_private_state:GaugeAvailability::available;
  auto context=PlanExplanation::make(ModeDescriptor::from_session(native.metadata(),native.status()),{},{},native.trace().snapshot,
      options.structure,ExplanationKind::session,availability,{},native.cursor(),native.status(),native.trace().records);
  return make(std::move(context),native.combined(),native.workload_options(),native.state_requested(),previous,lag);
}
const runtime::CompiledProgram& StatisticsExplanation::plan() const noexcept{return data_->context.plan();}
const ModeDescriptor& StatisticsExplanation::mode() const noexcept{return data_->context.mode();}
const std::optional<runtime::SessionStatus>& StatisticsExplanation::session() const noexcept{return data_->context.session_status();}
const runtime::ObservationSnapshot& StatisticsExplanation::observation() const noexcept{return *data_->context.observation();}
const runtime::CapturedTraceRecords& StatisticsExplanation::trace() const noexcept{return data_->context.trace_records();}
const std::optional<st::CombinedCapture>& StatisticsExplanation::combined() const noexcept{return data_->combined;}
const ws::Options& StatisticsExplanation::workload_options() const noexcept{return data_->options;}
bool StatisticsExplanation::state_requested() const noexcept{return data_->requested;}
const std::optional<StatisticsComparison>& StatisticsExplanation::comparison() const noexcept{return data_->comparison;}
}
