from pathlib import Path
import json,hashlib
H=Path(__file__).resolve().parent;R=H.parents[2]
roots=[H.parent/'o07-run-context-proposal/overlay',H.parent/'o07-mode-binding-proposal/overlay',H.parent/'o07-runtime-proposal/overlay',R]
paths=['include/crown/runtime/'+n+'.hpp' for n in ['observation','support','physical','delta']]+['src/runtime/'+n+'.cpp' for n in ['observation','support','physical','delta']]
pins={}
for rel in paths:
 src=next(p/rel for p in roots if (p/rel).is_file());dst=H/'overlay'/rel;dst.parent.mkdir(parents=True,exist_ok=True);dst.write_bytes(src.read_bytes());pins[str(src.relative_to(R))]=hashlib.sha256(src.read_bytes()).hexdigest()
pins.update(json.loads((H.parent/'o07-run-context-proposal/baseline-sha256.json').read_text()))
for name in ['o07-runtime-proposal','o07-mode-binding-proposal','o07-run-context-proposal','o07-explain-proposal']:
 for p in (H.parent/name/'overlay').rglob('*'):
  if p.is_file():pins[str(p.relative_to(R))]=hashlib.sha256(p.read_bytes()).hexdigest()
(H/'baseline-sha256.json').write_text(json.dumps(pins,indent=2)+'\n')
def edit(rel,old,new):
 p=H/'overlay'/rel;s=p.read_text();assert old in s,(rel,old[:100]);p.write_text(s.replace(old,new))
edit('include/crown/runtime/observation.hpp','namespace detail {\nstruct ObservationTicket','namespace detail {\n// Shared monotonic/test clock without attributing a read to delta metrics.\n[[nodiscard]] std::uint64_t read_observation_clock() noexcept;\nstruct ObservationTicket')
edit('src/runtime/observation.cpp','  add(MetricId::delta_clock_reads);\n#ifdef CROWN_RUNTIME_TESTING','  add(MetricId::delta_clock_reads);\n  return read_observation_clock();\n}\nstd::uint64_t read_observation_clock() noexcept {\n#ifdef CROWN_RUNTIME_TESTING')
header='include/crown/runtime/support.hpp'
edit(header,'// Logical support kernel with affected-record metadata/storage undo.', '''enum class CursorObservationSource { committed_results, epoch_visible, epoch_witnesses, epoch_keys, epoch_bucket };
enum class CursorTerminalReason { not_recorded, none, exhausted, explicit_cancel, destruction, move_replacement, invalidated, startup_failure, next_failure };
enum class CursorMetricId { startup_ns, successful_next_ns, exhausted_next_ns,
  failed_next_ns, cleanup_ns, successful_calls, exhausted_calls, failed_calls,
  cancel_calls, cleanup_calls, clock_reads, clock_regressions, count };
inline constexpr std::size_t cursor_metric_count=static_cast<std::size_t>(CursorMetricId::count);
struct CursorMetricDescriptor {
  CursorMetricId id;
  std::string_view name,unit,scope;
  MetricKind kind;
};
[[nodiscard]] std::span<const CursorMetricDescriptor> cursor_observation_registry() noexcept;
struct CursorObservation {
  ObservationOptions options;
  std::optional<ObservationConfiguration> configuration;
  std::uint64_t owner=0,sequence=0,cursor_id=0;
  bool cursor_id_saturated=false,constructed=false,tentative_at_creation=false;
  ResultView view=ResultView::core;
  CursorObservationSource source=CursorObservationSource::committed_results;
  std::optional<SnapshotSide> side;
  ResultCursorOptions limits;
  ResultCursorState state=ResultCursorState::active;
  CursorTerminalReason terminal_reason=CursorTerminalReason::not_recorded;
  ResultCursorMetrics mandatory;
  std::array<MetricValue,cursor_metric_count> values{};
  [[nodiscard]] const MetricValue& metric(CursorMetricId id) const noexcept {
    const auto index=static_cast<std::size_t>(id);
    static constexpr MetricValue unavailable{};
    return index<values.size()?values[index]:unavailable;
  }
};
struct NodeStateGauge {
  NodeId node;
  NodeKind kind;
  std::uint64_t records=0,survivors=0,projected_parent_keys=0;
  MetricValue visible_factor_assignments;
};
struct BaseStateGauge { TableId table; std::uint64_t tuples=0; };
struct CommittedStateGauges {
  std::uint64_t owner=0,sequence=0;
  std::vector<BaseStateGauge> bases;
  MetricValue base_tuples;
  std::vector<NodeStateGauge> nodes;
  // Unsupported facts remain unavailable, never fabricated as zero.
  MetricValue full_result_count,allocated_bytes,live_bytes,checkpoint_bytes,
      checkpoint_ns,recovery_replay_length;
};

// Logical support kernel with affected-record metadata/storage undo.''')
edit(header,'    [[nodiscard]] const ResultCursorMetrics& metrics() const;','    [[nodiscard]] const ResultCursorMetrics& metrics() const;\n    [[nodiscard]] CursorObservation observation() const;')
edit(header,'  [[nodiscard]] ObservationSnapshot observations() const;','''  [[nodiscard]] ObservationSnapshot observations() const;
  // Latest enabled cursor lifecycle publication; not an aggregate or update metric.
  [[nodiscard]] std::optional<CursorObservation> last_cursor_observation() const;
  // Explicit allocating read of committed relation cardinalities, even when off.
  [[nodiscard]] CommittedStateGauges committed_state_gauges() const;''')
for name in ['physical','delta']:
 edit('include/crown/runtime/'+name+'.hpp','  [[nodiscard]] ObservationSnapshot observations() const;','''  [[nodiscard]] ObservationSnapshot observations() const;
  [[nodiscard]] std::optional<CursorObservation> last_cursor_observation() const;
  [[nodiscard]] CommittedStateGauges committed_state_gauges() const;''')
p='src/runtime/support.cpp'
edit(p,'#include <utility>','#include <utility>\n#include <type_traits>')
helper='''
constexpr std::array<CursorMetricDescriptor,cursor_metric_count> cursor_registry{{
 {CursorMetricId::startup_ns,"cursor.startup_ns","nanoseconds","cursor construction/allocation/preparation; failed construction includes unwinding",MetricKind::timing},
 {CursorMetricId::successful_next_ns,"cursor.successful_next_ns","nanoseconds","sum of successful active next calls; excludes caller pause",MetricKind::timing},
 {CursorMetricId::exhausted_next_ns,"cursor.exhausted_next_ns","nanoseconds","first exhausted active next; excludes cleanup",MetricKind::timing},
 {CursorMetricId::failed_next_ns,"cursor.failed_next_ns","nanoseconds","failed active next; excludes cleanup and later rejected calls",MetricKind::timing},
 {CursorMetricId::cleanup_ns,"cursor.cleanup_ns","nanoseconds","one admitted cursor cleanup/lease release; excludes owning plan/layout destruction",MetricKind::timing},
 {CursorMetricId::successful_calls,"cursor.successful_calls","count","active next returning one owning row",MetricKind::counter},
 {CursorMetricId::exhausted_calls,"cursor.exhausted_calls","count","first active next returning no row",MetricKind::counter},
 {CursorMetricId::failed_calls,"cursor.failed_calls","count","active next throwing; excludes construction and closed/moved rejection",MetricKind::counter},
 {CursorMetricId::cancel_calls,"cursor.cancel_calls","count","explicit cancel while active; excludes idempotent closed cancel",MetricKind::counter},
 {CursorMetricId::cleanup_calls,"cursor.cleanup_calls","count","one admitted cursor close",MetricKind::counter},
 {CursorMetricId::clock_reads,"cursor.clock_reads","count","optional reads local to this cursor; excludes delta clock registry",MetricKind::counter},
 {CursorMetricId::clock_regressions,"cursor.clock_regressions","count","backward clock intervals; affected timing becomes unavailable",MetricKind::counter}
}};
bool cursor_clocks(const CursorObservation& value) noexcept {
 return value.options.mode==ObservationMode::timed ||
     (value.options.mode==ObservationMode::trace && value.options.trace_timings);
}
void cursor_add(CursorObservation& value,CursorMetricId id,std::uint64_t amount=1) noexcept {
 auto& metric=value.values[static_cast<std::size_t>(id)];
 if(metric.availability!=MetricAvailability::available)return;
 if(amount>UINT64_MAX-metric.value){metric.value=UINT64_MAX;metric.saturated=true;}
 else metric.value+=amount;
}
std::uint64_t cursor_now(CursorObservation& value) noexcept {
 if(!cursor_clocks(value))return 0;
 cursor_add(value,CursorMetricId::clock_reads);return detail::read_observation_clock();
}
void cursor_elapsed(CursorObservation& value,CursorMetricId id,std::uint64_t start) noexcept {
 if(!cursor_clocks(value))return;
 const auto finish=cursor_now(value);
 if(finish<start){cursor_add(value,CursorMetricId::clock_regressions);value.values[static_cast<std::size_t>(id)].availability=MetricAvailability::unavailable;}
 else cursor_add(value,id,finish-start);
}
'''
edit(p,'}  // namespace\n\nProjectionSupportCount increment_support',helper+'}  // namespace\n\nstd::span<const CursorMetricDescriptor> cursor_observation_registry() noexcept { return cursor_registry; }\nstatic_assert(std::is_trivially_copyable_v<CursorObservation>);\n\nProjectionSupportCount increment_support')
edit(p,'  std::shared_ptr<detail::ObservationState> observation;\n  storage::TupleLayout sql_output;','''  std::shared_ptr<detail::ObservationState> observation;
  std::optional<CursorObservation> last_cursor;
  std::uint64_t next_cursor_id=0;
  bool cursor_id_saturated=false;
  storage::TupleLayout sql_output;''')
edit(p,'  ResultCursorMetrics metrics;\n  ResultCursorState status=', '''  ResultCursorMetrics metrics;
  ResultCursorMetrics* startup_sink=nullptr;
  std::shared_ptr<detail::ObservationState> observation;
  std::weak_ptr<Impl> diagnostic_owner;
  CursorObservation diagnostic;
  bool observation_admitted=false;
  void publish() noexcept {
    if(!observation || !observation_admitted)return;
    diagnostic.mandatory=metrics;diagnostic.state=status;
    if(auto owner=diagnostic_owner.lock())owner->last_cursor=diagnostic;
  }
  template<class Make> static std::unique_ptr<Data> create(const std::shared_ptr<Impl>& owner,
      ResultCursorOptions limits,ResultView view,CursorObservationSource source,
      std::optional<SnapshotSide> side,bool tentative,std::uint64_t epoch,Make make) {
    CursorObservation summary;
    summary.options=owner->options.observation;summary.owner=owner->owner.value;
    summary.sequence=epoch;summary.limits=limits;summary.view=view;summary.source=source;
    summary.side=side;summary.tentative_at_creation=tentative;
    const bool enabled=bool(owner->observation);
    if(enabled){
      if(owner->next_cursor_id==UINT64_MAX)owner->cursor_id_saturated=true;else ++owner->next_cursor_id;
      summary.cursor_id=owner->next_cursor_id;summary.cursor_id_saturated=owner->cursor_id_saturated;
      summary.configuration=owner->observation->configuration();summary.terminal_reason=CursorTerminalReason::none;
    }
    for(const auto& entry:cursor_registry)summary.values[static_cast<std::size_t>(entry.id)].availability=
      !enabled || (entry.kind==MetricKind::timing && !cursor_clocks(summary))?MetricAvailability::disabled:MetricAvailability::available;
    const auto start=cursor_now(summary);
    try {
      auto cursor=make(enabled?&summary.mandatory:nullptr);
      cursor->startup_sink=nullptr;
      if(source==CursorObservationSource::committed_results){++owner->readers;cursor->leased=true;}
      else cursor->link();
      summary.constructed=true;summary.mandatory=cursor->metrics;
      cursor_elapsed(summary,CursorMetricId::startup_ns,start);
      cursor->diagnostic=summary;cursor->observation_admitted=enabled;cursor->publish();return cursor;
    }catch(...){
      if(enabled){
        cursor_elapsed(summary,CursorMetricId::startup_ns,start);
        summary.state=ResultCursorState::failed;summary.terminal_reason=CursorTerminalReason::startup_failure;
        summary.values[static_cast<std::size_t>(CursorMetricId::cleanup_ns)].availability=MetricAvailability::unavailable;
        summary.values[static_cast<std::size_t>(CursorMetricId::cleanup_calls)].availability=MetricAvailability::unavailable;
        owner->last_cursor=summary;
      }
      throw;
    }
  }
  ResultCursorState status=''')
edit(p,'Data(std::shared_ptr<Impl> owner,ResultCursorOptions limits,ResultView mode,bool initialize=true)','Data(std::shared_ptr<Impl> owner,ResultCursorOptions limits,ResultView mode,bool initialize=true,ResultCursorMetrics* startup=nullptr)')
edit(p,'output_layout(view==ResultView::sql?runtime->sql_output:plan.result_layout()),\n       epoch','output_layout(view==ResultView::sql?runtime->sql_output:plan.result_layout()),\n       startup_sink(startup),observation(runtime->observation),diagnostic_owner(observation?runtime:std::shared_ptr<Impl>{}),\n       epoch')
for sig in ['const FixedAssignment& bindings,VisibleFragment fragment','const FixedAssignment& bindings,WitnessFragment fragment','NodeId id','NodeId id,const Row& separator']:
 edit(p,'Data(std::shared_ptr<EpochView::Data> context,'+sig+',ResultCursorOptions limits)', 'Data(std::shared_ptr<EpochView::Data> context,'+sig+',ResultCursorOptions limits,ResultCursorMetrics* startup=nullptr)')
edit(p,':Data(context->group->runtime,limits,ResultView::core,false)', ':Data(context->group->runtime,limits,ResultView::core,false,startup)')
edit(p,'  ~Data() { close(ResultCursorState::cancelled); }','''  ~Data() {
    close(ResultCursorState::cancelled,CursorTerminalReason::destruction);
    if(startup_sink)*startup_sink=metrics;
  }''')
edit(p,'    metrics.total_work+=amount; work.work+=amount; work.*field+=amount;','    metrics.total_work+=amount; work.work+=amount; work.*field+=amount;\n    if(startup_sink)*startup_sink=metrics;')
edit(p,'  void close(ResultCursorState state) noexcept {\n    if (status!=ResultCursorState::active) return;','''  void close(ResultCursorState state,CursorTerminalReason reason) noexcept {
    if (status!=ResultCursorState::active) return;
    const auto start=observation_admitted?cursor_now(diagnostic):0;
    if(observation_admitted){diagnostic.terminal_reason=reason;cursor_add(diagnostic,CursorMetricId::cleanup_calls);}''')
edit(p,'    snapshot.reset(); runtime.reset(); status=state;','''    snapshot.reset(); runtime.reset(); status=state;
    if(observation_admitted){cursor_elapsed(diagnostic,CursorMetricId::cleanup_ns,start);publish();}''')
edit(p,'first->close(ResultCursorState::failed)','first->close(ResultCursorState::failed,CursorTerminalReason::invalidated)')
edit(p,'  if (this!=&other) data_=std::move(other.data_);\n  return *this;\n}\nSupportRuntime::ResultCursor::~ResultCursor()', '''  if (this!=&other) {
    if(data_)data_->close(ResultCursorState::cancelled,CursorTerminalReason::move_replacement);
    data_=std::move(other.data_);
  }
  return *this;
}
SupportRuntime::ResultCursor::~ResultCursor()''')
edit(p,'void SupportRuntime::ResultCursor::cancel() noexcept { if (data_) data_->close(ResultCursorState::cancelled); }','''CursorObservation SupportRuntime::ResultCursor::observation() const {
  require(bool(data_),"invalid_cursor","moved-from result cursor");
  auto result=data_->diagnostic;result.mandatory=data_->metrics;result.state=data_->status;return result;
}
void SupportRuntime::ResultCursor::cancel() noexcept {
  if(data_ && data_->status==ResultCursorState::active){
    if(data_->observation_admitted)cursor_add(data_->diagnostic,CursorMetricId::cancel_calls);
    data_->close(ResultCursorState::cancelled,CursorTerminalReason::explicit_cancel);
  }
}''')
edit(p,'  CursorWork action;\n  try {','  CursorWork action;\n  const auto start=data_->observation_admitted?cursor_now(data_->diagnostic):0;\n  try {')
edit(p,'      Data::merge(data_->metrics.results,action); data_->metrics.max_result_work=std::max(data_->metrics.max_result_work,action.work);\n    } else { Data::merge(data_->metrics.termination,action); data_->close(ResultCursorState::exhausted); }','''      Data::merge(data_->metrics.results,action); data_->metrics.max_result_work=std::max(data_->metrics.max_result_work,action.work);
      if(data_->observation_admitted){cursor_add(data_->diagnostic,CursorMetricId::successful_calls);cursor_elapsed(data_->diagnostic,CursorMetricId::successful_next_ns,start);data_->publish();}
    } else {
      Data::merge(data_->metrics.termination,action);
      if(data_->observation_admitted){cursor_add(data_->diagnostic,CursorMetricId::exhausted_calls);cursor_elapsed(data_->diagnostic,CursorMetricId::exhausted_next_ns,start);}
      data_->close(ResultCursorState::exhausted,CursorTerminalReason::exhausted);
    }''')
edit(p,'    data_->metrics.last=action; Data::merge(data_->metrics.failed,action); data_->close(ResultCursorState::failed); throw;','''    data_->metrics.last=action; Data::merge(data_->metrics.failed,action);
    if(data_->observation_admitted){cursor_add(data_->diagnostic,CursorMetricId::failed_calls);cursor_elapsed(data_->diagnostic,CursorMetricId::failed_next_ns,start);}
    data_->close(ResultCursorState::failed,CursorTerminalReason::next_failure); throw;''')
edit(p,'  auto data=std::make_unique<ResultCursor::Data>(impl_,options,view);\n  ++d.readers; data->leased=true; return ResultCursor(std::move(data));','''  auto data=ResultCursor::Data::create(impl_,options,view,CursorObservationSource::committed_results,{},false,d.sequence,
      [&](ResultCursorMetrics* startup){return std::make_unique<ResultCursor::Data>(impl_,options,view,true,startup);});
  return ResultCursor(std::move(data));''')
for old,source in [('data_,fixed,fragment,options','epoch_visible'),('data_,fixed,std::move(fragment),options','epoch_witnesses'),('data_,node,options','epoch_keys'),('data_,node,separator,options','epoch_bucket')]:
 edit(p,'  auto cursor=std::make_unique<ResultCursor::Data>('+old+'); cursor->link();','''  auto cursor=ResultCursor::Data::create(data_->group->runtime,options,ResultView::core,
      CursorObservationSource::'''+source+''',data_->side,tentative(),sequence(),
      [&](ResultCursorMetrics* startup){return std::make_unique<ResultCursor::Data>('''+old+''',startup);});''')
edit(p,'SupportSnapshot SupportRuntime::snapshot() const {','''std::optional<CursorObservation> SupportRuntime::last_cursor_observation() const { return impl().last_cursor; }
CommittedStateGauges SupportRuntime::committed_state_gauges() const {
  const auto& d=impl();d.readable();CommittedStateGauges result;
  result.owner=d.owner.value;result.sequence=d.sequence;result.nodes.reserve(d.plan.nodes().size());
  for(const auto& node:d.plan.nodes()){
    NodeStateGauge value{node.id,node.kind,
      static_cast<std::uint64_t>(d.state->storage.table(node.records).size()),
      static_cast<std::uint64_t>(d.state->storage.table(node.survivors).size()),
      static_cast<std::uint64_t>(d.state->storage.table(node.parent_support).size()),{}};
    if(node.visible_relation)value.visible_factor_assignments={static_cast<std::uint64_t>(d.state->storage.table(*node.visible_relation).size()),MetricAvailability::available,false};
    result.nodes.push_back(value);
  }
  return result;
}
SupportSnapshot SupportRuntime::snapshot() const {''')
p='src/runtime/physical.cpp'
edit(p,'ObservationSnapshot PhysicalRuntime::observations() const {','''std::optional<CursorObservation> PhysicalRuntime::last_cursor_observation() const { return impl().kernel.last_cursor_observation(); }
CommittedStateGauges PhysicalRuntime::committed_state_gauges() const {
  const auto& d=impl();d.readable();auto result=d.kernel.committed_state_gauges();
  result.base_tuples={0,MetricAvailability::available,false};result.bases.reserve(d.sources.size());
  for(std::size_t i=0;i<d.sources.size();++i){
    const auto count=static_cast<std::uint64_t>(d.sources[i].size());result.bases.push_back({TableId{i},count});
    if(count>UINT64_MAX-result.base_tuples.value){result.base_tuples.value=UINT64_MAX;result.base_tuples.saturated=true;}
    else result.base_tuples.value+=count;
  }
  return result;
}
ObservationSnapshot PhysicalRuntime::observations() const {''')
p='src/runtime/delta.cpp'
edit(p,'ObservationSnapshot DeltaRuntime::observations() const {','''std::optional<CursorObservation> DeltaRuntime::last_cursor_observation() const { return impl().physical.last_cursor_observation(); }
CommittedStateGauges DeltaRuntime::committed_state_gauges() const { const auto& d=impl();d.readable();return d.physical.committed_state_gauges(); }
ObservationSnapshot DeltaRuntime::observations() const {''')
for rel in ['include/crown/runtime/session.hpp','src/runtime/session.cpp']:
 src=next(p/rel for p in roots if (p/rel).is_file());dst=H/'overlay'/rel;dst.parent.mkdir(parents=True,exist_ok=True);dst.write_bytes(src.read_bytes())
edit('include/crown/runtime/session.hpp','  [[nodiscard]] ObservationSnapshot observations() const;','  [[nodiscard]] ObservationSnapshot observations() const;\n  [[nodiscard]] std::optional<CursorObservation> last_cursor_observation() const;')
edit('src/runtime/session.cpp','  ObservationSnapshot retained_observation;','  ObservationSnapshot retained_observation;\n  std::optional<CursorObservation> retained_cursor_observation;')
edit('src/runtime/session.cpp','    if (runtime) retained_observation=runtime->observations();','''    if (runtime) {
      retained_observation=runtime->observations();
      retained_cursor_observation=runtime->last_cursor_observation();
    }''')
edit('src/runtime/session.cpp','ObservationSnapshot QuerySession::observations() const {','''std::optional<CursorObservation> QuerySession::last_cursor_observation() const {
  auto& d=*data_; Impl::Guard guard(d);
  return d.runtime?d.runtime->last_cursor_observation():d.retained_cursor_observation;
}
ObservationSnapshot QuerySession::observations() const {''')
# Nested cursor times overlap enclosing delta phases; count clock reads in a
# separate attempt subset so fake-clock reconciliation need not retain every
# internal cursor. Never attribute later current-result reads to a last update.
edit('include/crown/runtime/observation.hpp','  delta_clock_reads,\n  count','  delta_clock_reads,\n  nested_cursor_clock_reads,\n  count')
edit('include/crown/runtime/observation.hpp','  [[nodiscard]] bool clocks_enabled() const noexcept;','''  void note_cursor_clock_read() noexcept {
    if(snapshot_.current && snapshot_.current->owner==ObservationLayer::delta)
      add(MetricId::nested_cursor_clock_reads);
  }
  [[nodiscard]] bool clocks_enabled() const noexcept;''')
edit('src/runtime/observation.cpp','}};\nvoid increment(','''  {MetricId::nested_cursor_clock_reads, "cursor.nested_clock_reads", "count", "optional-observation-v1", "cursor clock reads while this delta attempt is active; excludes later current-result reads", ObservationLayer::delta, MetricKind::counter, "subset of per-cursor clock_reads; do not add both; delta.clock_reads + this count reconciles active-attempt clock calls"},
}};
void increment(''')
p=H/'overlay/src/runtime/support.cpp';s=p.read_text()
for old in ['cursor construction/allocation/preparation; failed construction includes unwinding','sum of successful active next calls; excludes caller pause','first exhausted active next; excludes cleanup','failed active next; excludes cleanup and later rejected calls','one admitted cursor cleanup/lease release; excludes owning plan/layout destruction']:
 s=s.replace('"'+old+'"','"'+old+'; epoch-view time may nest inside delta propagation/internal time, not additive with enclosing phase"')
s=s.replace('std::uint64_t cursor_now(CursorObservation& value) noexcept {','std::uint64_t cursor_now(CursorObservation& value,const std::shared_ptr<detail::ObservationState>& observer) noexcept {')
s=s.replace('cursor_add(value,CursorMetricId::clock_reads);return detail::read_observation_clock();','cursor_add(value,CursorMetricId::clock_reads);if(observer)observer->note_cursor_clock_read();return detail::read_observation_clock();')
s=s.replace('void cursor_elapsed(CursorObservation& value,CursorMetricId id,std::uint64_t start) noexcept {','void cursor_elapsed(CursorObservation& value,CursorMetricId id,std::uint64_t start,const std::shared_ptr<detail::ObservationState>& observer) noexcept {')
s=s.replace('const auto finish=cursor_now(value);','const auto finish=cursor_now(value,observer);')
s=s.replace('cursor_now(summary)','cursor_now(summary,owner->observation)').replace('cursor_elapsed(summary,CursorMetricId::startup_ns,start)','cursor_elapsed(summary,CursorMetricId::startup_ns,start,owner->observation)')
s=s.replace('cursor_now(diagnostic)','cursor_now(diagnostic,observation)').replace('cursor_elapsed(diagnostic,CursorMetricId::cleanup_ns,start)','cursor_elapsed(diagnostic,CursorMetricId::cleanup_ns,start,observation)')
s=s.replace('cursor_now(data_->diagnostic)','cursor_now(data_->diagnostic,data_->observation)')
for metric in ['successful_next_ns','exhausted_next_ns','failed_next_ns']:
 s=s.replace('cursor_elapsed(data_->diagnostic,CursorMetricId::'+metric+',start)','cursor_elapsed(data_->diagnostic,CursorMetricId::'+metric+',start,data_->observation)')
p.write_text(s)
