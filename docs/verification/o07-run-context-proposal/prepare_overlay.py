from pathlib import Path
import json,hashlib
H=Path(__file__).resolve().parent;R=H.parents[2];B=H.parent/'o07-runtime-proposal/overlay';M=H.parent/'o07-mode-binding-proposal/overlay'
paths=['include/crown/runtime/'+p+'.hpp' for p in ['observation','physical','delta','session']]+['src/runtime/'+p+'.cpp' for p in ['observation','physical','delta','session']]
pins={}
for rel in paths:
 p=next(p for p in [M/rel,B/rel,R/rel] if p.exists());o=H/'overlay'/rel;o.parent.mkdir(parents=True,exist_ok=True);o.write_bytes(p.read_bytes());pins[str(p.relative_to(R))]=hashlib.sha256(p.read_bytes()).hexdigest()
for name in ['o07-runtime-proposal','o07-mode-binding-proposal']:
 for rel,digest in json.loads((H.parent/name/'baseline-sha256.json').read_text()).items():pins[rel]=digest
(H/'baseline-sha256.json').write_text(json.dumps(pins,indent=2)+'\n')
def edit(rel,old,new):
 p=H/'overlay'/rel;s=p.read_text();assert old in s,(rel,old[:80]);p.write_text(s.replace(old,new))
obs='include/crown/runtime/observation.hpp'
edit(obs,'#include <array>','#include "crown/runtime/initialization.hpp"\n#include <string>\n#include <array>')
edit(obs,'enum class ObservationLayer', '''// Successful construction metadata is independent of optional event counters.
enum class InitializationRoute { empty_constructor, initialized_database, rebuilt_snapshot };
struct InitializationContext {
  InitializationRoute route=InitializationRoute::empty_constructor;
  // No BuildOptions were applied by the empty constructor.
  std::optional<BuildOptions> applied_build;
};
struct SessionRunContext;
struct BenchmarkLabels {
  std::optional<std::string> run, input_adapter, output_codec, sink;
};
// Explicit caller declarations only: no callback inspection, validation of
// claims, durability, completeness, measured cost, or proof authority.
class DeclaredBenchmarkContext {
 public:
  explicit DeclaredBenchmarkContext(BenchmarkLabels labels):labels_(std::move(labels)) {}
  [[nodiscard]] const BenchmarkLabels& labels() const noexcept { return labels_; }
 private:
  const BenchmarkLabels labels_;
};
struct OutputDisposition {
  bool drain_requested=false, retention_disabled=false;
  bool prepared=false, published=false, released=false;
  bool transferred=false, serialization_invoked=false, sink_invoked=false;
  bool unread_discarded=false;
};
enum class ObservationLayer''')
edit(obs,'  std::optional<ObservationConfiguration> configuration;', '''  std::optional<ObservationConfiguration> configuration;
  std::optional<InitializationContext> initialization;
  std::shared_ptr<const DeclaredBenchmarkContext> declared_benchmark;
  std::optional<OutputDisposition> output;''')
edit(obs,'  std::optional<ObservationConfiguration> current_configuration;', '''  std::optional<ObservationConfiguration> current_configuration;
  std::optional<InitializationContext> initialization;
  std::shared_ptr<const DeclaredBenchmarkContext> current_declared_benchmark;
  std::shared_ptr<const SessionRunContext> session_context;''')
edit(obs,'  void configure(ObservationConfiguration value)', '''  void initialize(InitializationContext value) noexcept { snapshot_.initialization=value; }
  void declare_benchmark(std::shared_ptr<const DeclaredBenchmarkContext> value) noexcept {
    snapshot_.current_declared_benchmark=std::move(value);
  }
  void output(ObservationTicket ticket,OutputDisposition value) noexcept {
    auto* summary=target();
    if (summary && summary->owner==ObservationLayer::delta && summary->attempt==ticket.attempt)
      summary->output=value;
  }
  void configure(ObservationConfiguration value)''')
edit('src/runtime/observation.cpp','    if (layer==ObservationLayer::delta) summary.configuration=snapshot_.current_configuration;', '''    summary.initialization=snapshot_.initialization;
    if (layer==ObservationLayer::delta) {
      summary.configuration=snapshot_.current_configuration;
      summary.declared_benchmark=snapshot_.current_declared_benchmark;
      summary.output.emplace();
    }''')
for p in ['physical','delta']:
 edit('include/crown/runtime/'+p+'.hpp','  [[nodiscard]] const BuildMetrics& initialization_metrics() const;','  [[nodiscard]] const BuildMetrics& initialization_metrics() const;\n  [[nodiscard]] InitializationContext initialization_context() const;')
edit('include/crown/runtime/delta.hpp','  [[nodiscard]] ObservationSnapshot observations() const;', '''  [[nodiscard]] ObservationSnapshot observations() const;
  // Explicit diagnostic declaration; affects only future attempt bindings.
  // Caller constructs immutable labels before mutation. No parsing or clocks.
  void declare_benchmark_context(std::shared_ptr<const DeclaredBenchmarkContext>);''')
p='src/runtime/physical.cpp'
edit(p,'  BuildMetrics build_metrics;','  BuildMetrics build_metrics;\n  InitializationContext initialization_context;')
edit(p,'PhysicalRuntime::PhysicalRuntime(PhysicalPlan plan,PhysicalRuntimeOptions options):impl_(std::make_shared<Impl>(std::move(plan),options)) {}','''PhysicalRuntime::PhysicalRuntime(PhysicalPlan plan,PhysicalRuntimeOptions options):impl_(std::make_shared<Impl>(std::move(plan),options)) {
  if (impl_->observation) impl_->observation->initialize(impl_->initialization_context);
}''')
edit(p,'  d.build_metrics=metrics; d.kernel.seed_sequence(sequence); d.sequence=sequence;','''  d.build_metrics=metrics; d.kernel.seed_sequence(sequence); d.sequence=sequence;
  d.initialization_context={InitializationRoute::initialized_database,build};
  if (d.observation) d.observation->initialize(d.initialization_context);''')
edit(p,'  return initialize_at(d.kernel.plan(),database,d.options,build,d.sequence,prefix);','''  auto result=initialize_at(d.kernel.plan(),database,d.options,build,d.sequence,prefix);
  result.impl().initialization_context.route=InitializationRoute::rebuilt_snapshot;
  if (result.impl().observation) result.impl().observation->initialize(result.impl().initialization_context);
  return result;''')
edit(p,'const BuildMetrics& PhysicalRuntime::initialization_metrics()', 'InitializationContext PhysicalRuntime::initialization_context() const { return impl().initialization_context; }\nconst BuildMetrics& PhysicalRuntime::initialization_metrics()')
p='src/runtime/delta.cpp'
edit(p,'  BuildMetrics initialization;','  BuildMetrics initialization;\n  std::shared_ptr<const DeclaredBenchmarkContext> declared_benchmark;')
edit(p,'const BuildMetrics& DeltaRuntime::initialization_metrics()', 'InitializationContext DeltaRuntime::initialization_context() const { return impl().physical.initialization_context(); }\nconst BuildMetrics& DeltaRuntime::initialization_metrics()')
edit(p,'  result.impl().options=d.options;','  result.impl().options=d.options;\n  result.declare_benchmark_context(d.declared_benchmark);')
edit(p,'ObservationSnapshot DeltaRuntime::observations() const { return impl().physical.observations(); }','''void DeltaRuntime::declare_benchmark_context(std::shared_ptr<const DeclaredBenchmarkContext> value) {
  auto& d=impl(); d.declared_benchmark=std::move(value);
  if (d.observation) d.observation->declare_benchmark(d.declared_benchmark);
}
ObservationSnapshot DeltaRuntime::observations() const {
  const auto& d=impl(); auto result=d.physical.observations();
  result.initialization=d.physical.initialization_context();
  result.current_declared_benchmark=d.declared_benchmark; return result;
}''')
edit(p,'ObservationTrace DeltaRuntime::observation_trace() const { return impl().physical.observation_trace(); }','''ObservationTrace DeltaRuntime::observation_trace() const {
  auto result=impl().physical.observation_trace(); result.snapshot=observations(); return result;
}''')
edit(p,'  bool retain_output=true, delivering=false, discard_requested=false;', '''  bool retain_output=true, delivering=false, discard_requested=false;
  detail::ObservationTicket observation_ticket;
  OutputDisposition disposition;
  bool observation_closed=false;
  void observe_output() noexcept {
    if (observation && !observation_closed) observation->output(observation_ticket,disposition);
  }''')
edit(p,'    if (delivering) { discard_requested=true; return; }','''    if (delivering) { discard_requested=true; return; }
    if (observation && !observation_closed) {
      disposition.unread_discarded=disposition.unread_discarded || !rows.empty();
      disposition.released=true; observe_output(); observation_closed=true;
    }''')
edit(p,'    if (!retain_output) return;','''    if (observation) { disposition.drain_requested=true; observe_output(); }
    if (!retain_output) return;''')
edit(p,'    retain_output=false; rows.clear(); payload_bytes=0;','''    if (observation) {
      disposition.retention_disabled=true;
      disposition.unread_discarded=disposition.unread_discarded || !rows.empty(); observe_output();
    }
    retain_output=false; rows.clear(); payload_bytes=0;''')
edit(p,'    if (output->observation) observation_ticket=output->observation->begin(ObservationLayer::delta,sequence);','''    if (output->observation) {
      observation_ticket=output->observation->begin(ObservationLayer::delta,sequence);
      output->observation_ticket=observation_ticket;
    }''')
edit(p,'    if (output->observation) output->observation->event(TraceKind::prepared);','''    if (output->observation) {
      output->disposition.prepared=true; output->observe_output();
      output->observation->event(TraceKind::prepared);
    }''')
edit(p,'  data_->output->observe();\n  if (data_->output->observation)', '''  data_->output->observe();
  if (data_->output->observation) {
    data_->output->disposition.published=true;
    data_->output->disposition.released=data_->output->rows.empty();
    data_->output->observe_output();
    if (data_->output->rows.empty()) data_->output->observation_closed=true;
  }
  if (data_->output->observation)''')
edit(p,'    data_->observation->add(MetricId::delta_transferred_records);','    data_->disposition.transferred=true; data_->observe_output();\n    data_->observation->add(MetricId::delta_transferred_records);')
edit(p,'        data->observation->add(MetricId::delta_serialization_attempts);','        data->disposition.serialization_invoked=true; data->observe_output();\n        data->observation->add(MetricId::delta_serialization_attempts);')
edit(p,'      data->observation->add(MetricId::delta_sink_attempts);','      data->disposition.sink_invoked=true; data->observe_output();\n      data->observation->add(MetricId::delta_sink_attempts);')
p='include/crown/runtime/session.hpp'
edit(p,'  SnapshotLimits snapshot;\n};','''  SnapshotLimits snapshot;
  std::shared_ptr<const DeclaredBenchmarkContext> declared_benchmark;
};
enum class SessionInputKind { owned_stream, typed_physical, typed_window };
// Constructed once during session admission, never copied by observation hooks.
// Exact native bytes remain native bytes; strict text encoding is an export duty.
struct SessionRunContext {
  SessionInputKind input_kind;
  io::InputOptions input;
  std::optional<io::QueueLimits> queue;
  std::optional<WindowOptions> window;
  SnapshotLimits snapshot;
  InitializationContext initialization;
};''')
edit(p,'  [[nodiscard]] SessionStatus status() const;','  [[nodiscard]] SessionStatus status() const;\n  [[nodiscard]] std::shared_ptr<const SessionRunContext> run_context() const;')
p='src/runtime/session.cpp'
edit(p,'  SnapshotLimits snapshot_limits;','  SnapshotLimits snapshot_limits;\n  std::shared_ptr<const SessionRunContext> run_context;')
edit(p,'    reader.emplace(*input,runtime->plan().source_catalog(),std::move(options.input));','''    run_context=std::make_shared<const SessionRunContext>(SessionRunContext{
        SessionInputKind::owned_stream,options.input,{},{},options.snapshot,runtime->initialization_context()});
    runtime->declare_benchmark_context(std::move(options.declared_benchmark));
    reader.emplace(*input,runtime->plan().source_catalog(),std::move(options.input));''')
edit(p,'    queue.emplace(runtime->plan().source_catalog(),window?io::QueueMode::window:io::QueueMode::physical,','''    run_context=std::make_shared<const SessionRunContext>(SessionRunContext{
        window?SessionInputKind::typed_window:SessionInputKind::typed_physical,
        options.input,limits,window?std::optional<WindowOptions>{window->options()}:std::nullopt,
        options.snapshot,runtime->initialization_context()});
    runtime->declare_benchmark_context(std::move(options.declared_benchmark));
    queue.emplace(runtime->plan().source_catalog(),window?io::QueueMode::window:io::QueueMode::physical,''')
edit(p,'    retained_observation.session_attached=true;','    retained_observation.session_context=run_context;\n    retained_observation.session_attached=true;')
edit(p,'ObservationSnapshot QuerySession::observations() const {','''std::shared_ptr<const SessionRunContext> QuerySession::run_context() const {
  auto& d=*data_; Impl::Guard guard(d); return d.run_context;
}
ObservationSnapshot QuerySession::observations() const {''')
edit(p,'  result.session_attached=true; result.session_committed_sequence=d.committed_sequence;','  result.session_context=d.run_context;\n  result.session_attached=true; result.session_committed_sequence=d.committed_sequence;')
edit(p,'  result.snapshot.session_attached=true;','  result.snapshot.session_context=d.run_context;\n  result.snapshot.session_attached=true;')
edit('src/runtime/observation.cpp','static_assert(std::is_trivially_copyable_v<ObservationSnapshot>);','''// Owned immutable admission metadata adds shared handles; copying/refcounting
// is nonallocating and cannot throw. Destruction may release owned metadata.
static_assert(std::is_nothrow_copy_constructible_v<ObservationSnapshot>);
static_assert(std::is_nothrow_copy_assignable_v<ObservationSnapshot>);''')
edit('include/crown/runtime/observation.hpp','  bool drain_requested=false, retention_disabled=false;','  bool discard_drain_requested=false, completion_drain_invoked=false, retention_disabled=false;')
edit('src/runtime/delta.cpp','disposition.drain_requested=true','disposition.discard_drain_requested=true')
edit('src/runtime/delta.cpp','void DeltaRuntime::PendingEpoch::drain() {\n  require(bool(data_),"invalid_delta_epoch","moved-from pending delta epoch"); data_->validate();','''void DeltaRuntime::PendingEpoch::drain() {
  require(bool(data_),"invalid_delta_epoch","moved-from pending delta epoch"); data_->validate();
  if (data_->output->observation) {
    data_->output->disposition.completion_drain_invoked=true; data_->output->observe_output();
  }''')
edit('src/runtime/physical.cpp','ObservationSnapshot PhysicalRuntime::observations() const { return impl().kernel.observations(); }','''ObservationSnapshot PhysicalRuntime::observations() const {
  auto result=impl().kernel.observations(); result.initialization=impl().initialization_context; return result;
}''')
edit('src/runtime/physical.cpp','ObservationTrace PhysicalRuntime::observation_trace() const { return impl().kernel.observation_trace(); }','''ObservationTrace PhysicalRuntime::observation_trace() const {
  auto result=impl().kernel.observation_trace(); result.snapshot.initialization=impl().initialization_context; return result;
}''')
edit('include/crown/runtime/session.hpp','  InitializationContext initialization;\n};','''  InitializationContext initialization;
  DeltaOptions requested_delta;
  DeltaMode resolved_mode;
  DeltaCompletion resolved_completion;
};''')
edit('src/runtime/session.cpp','options.snapshot,runtime->initialization_context()});','options.snapshot,runtime->initialization_context(),runtime->options(),runtime->mode(),runtime->completion()});')
for name in ['ObservationSummary','ObservationSnapshot']:
 edit('include/crown/runtime/observation.hpp','struct '+name+' {','''struct '''+name+''' {
  '''+name+'''() noexcept = default;
  '''+name+'''(const '''+name+'''&) noexcept = default;
  '''+name+'''& operator=(const '''+name+'''&) noexcept = default;
  '''+name+'''('''+name+'''&&) noexcept = default;
  '''+name+'''& operator=('''+name+'''&&) noexcept = default;''')

# Pin unchanged EXPLAIN consumers and exact reusable non-runtime archives too.
p=H/'baseline-sha256.json';pins=json.loads(p.read_text())
for f in (H.parent/'o07-explain-proposal/overlay').rglob('*'):
 if f.is_file():pins[str(f.relative_to(R))]=hashlib.sha256(f.read_bytes()).hexdigest()
for rel in ['build/release/libcrown_plan.a','build/release/libcrown_sql.a','build/release/_deps/libpg_query/libpg_query-18.1.0/libpg_query.a','build/release/libcrown_core.a']:
 pins[rel]=hashlib.sha256((R/rel).read_bytes()).hexdigest()
p.write_text(json.dumps(pins,indent=2)+'\n')
