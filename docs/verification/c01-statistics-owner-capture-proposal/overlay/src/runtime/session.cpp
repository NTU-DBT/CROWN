#include "crown/runtime/session.hpp"
#include "owner_statistics_detail.hpp"

#include "crown/api/error.hpp"
#ifdef CROWN_RUNTIME_TESTING
#include "runtime_probe.hpp"
#endif
#include <algorithm>
#include <limits>
#include <thread>
#include <type_traits>
#include <utility>

namespace crown::runtime {
namespace {
void require(bool condition,std::string_view code,std::string_view message) {
  if (!condition) throw Error(std::string(code),std::string(message));
}
std::size_t add(std::size_t left,std::size_t right) {
  require(right<=std::numeric_limits<std::size_t>::max()-left,"resource_limit","snapshot size accounting exhausted");
  return left+right;
}
std::size_t slots(std::size_t count,std::size_t width) {
  require(count<=std::numeric_limits<std::size_t>::max()/width,"resource_limit","snapshot slot accounting exhausted");
  return count*width;
}
std::size_t payload(const storage::Tuple& tuple) {
  auto bytes=slots(tuple.values().capacity(),sizeof(Value));
  for (const auto& value : tuple.values()) {
    if (const auto* text=std::get_if<std::string>(&value)) bytes=add(bytes,add(text->capacity(),1));
    else if (std::holds_alternative<Decimal>(value)) bytes=add(bytes,64);
  }
  return bytes;
}
static_assert(std::is_nothrow_move_constructible_v<DeltaRuntime::PendingEpoch>);
static_assert(std::is_nothrow_move_constructible_v<DeltaRuntime::Epoch>);
static_assert(std::is_nothrow_move_constructible_v<SignedResult>);
static_assert(std::is_nothrow_move_constructible_v<io::InputProgress>);
static_assert(std::is_nothrow_move_assignable_v<io::InputProgress>);
static_assert(std::is_nothrow_move_constructible_v<SessionSnapshot>);
}  // namespace

struct QuerySession::Impl {
  const std::thread::id writer=std::this_thread::get_id();
  bool busy=false;
  SessionState control=SessionState::created;
  std::uint64_t committed_sequence=0;
  bool input_failed=false,end_of_input=false,window_input_failed=false;
  SnapshotLimits snapshot_limits;
  std::shared_ptr<const SessionRunContext> run_context;
  // Reader borrows this owned stream. Reverse destruction preserves lifetime,
  // including when a later member's construction throws.
  std::unique_ptr<std::istream> input;
  std::optional<io::EventReader> reader;
  std::optional<io::TypedQueue> queue;
  std::optional<WindowController> window;
  std::optional<WindowController::Prepared> window_pending;
  bool metadata_ready=false,metadata_draining=false;
  std::optional<std::uint64_t> pending_command_sequence;
  std::optional<DeltaRuntime> runtime;
  std::optional<DeltaRuntime::PendingEpoch> pending;
  std::optional<DeltaRuntime::Epoch> output;
  io::InputProgress final_progress;
  ObservationSnapshot retained_observation;
  std::optional<SessionReportMetadata> retained_report_metadata;
  std::optional<CursorObservation> retained_cursor_observation;

  struct Guard {
    Impl& data;
    explicit Guard(Impl& owner):data(owner) {
      // Check immutable writer identity before accessing any mutable state.
      require(std::this_thread::get_id()==data.writer,"session_wrong_thread","session operations belong to their creator thread");
      require(!data.busy,"session_busy","a session operation is already active");
      data.busy=true;
    }
    ~Guard() { data.busy=false; }
    Guard(const Guard&)=delete;
    Guard& operator=(const Guard&)=delete;
  };
  Impl(PhysicalPlan plan,std::unique_ptr<std::istream> stream,SessionOptions options,
      const Database* initial=nullptr,BuildOptions build={})
      :snapshot_limits(options.snapshot),input(std::move(stream)) {
    require(bool(input),"invalid_session_options","a session requires an owned input stream");
    if (initial) runtime.emplace(DeltaRuntime::initialize(std::move(plan),*initial,std::move(options.delta),build));
    else runtime.emplace(std::move(plan),std::move(options.delta));
    run_context=std::make_shared<const SessionRunContext>(SessionRunContext{
        SessionInputKind::owned_stream,options.input,{},{},options.snapshot,runtime->initialization_context(),runtime->options(),runtime->mode(),runtime->completion()});
    runtime->declare_benchmark_context(std::move(options.declared_benchmark));
    reader.emplace(*input,runtime->plan().source_catalog(),std::move(options.input));
    retain_report_metadata();
  }
  Impl(PhysicalPlan plan,io::QueueLimits limits,SessionOptions options,
      std::optional<WindowOptions> windows,const Database* initial=nullptr,BuildOptions build={})
      :snapshot_limits(options.snapshot) {
    const auto& profile=options.input;
    require(profile.format==io::InputFormat::jsonl && !profile.table && profile.delimiter==',' &&
        profile.header && profile.csv_operation==SetOperation::insert && profile.relation_tokens.empty() &&
        !profile.null_token && !profile.source && profile.byte_offset==0,
        "invalid_session_options","typed input does not accept wire-format profile options");
    if (windows) {
      window.emplace(plan.source_catalog(),std::move(*windows));
      if (initial) for (auto table:window->options().managed_tables) {
        require(table.value<initial->tables.size(),"invalid_database","initial database is missing a managed table");
        require(initial->tables[table.value].empty(),"invalid_window_initial_state","managed window tables must initially be empty");
      }
    }
    if (initial) runtime.emplace(DeltaRuntime::initialize(std::move(plan),*initial,std::move(options.delta),build));
    else runtime.emplace(std::move(plan),std::move(options.delta));
    run_context=std::make_shared<const SessionRunContext>(SessionRunContext{
        window?SessionInputKind::typed_window:SessionInputKind::typed_physical,
        options.input,limits,window?std::optional<WindowOptions>{window->options()}:std::nullopt,
        options.snapshot,runtime->initialization_context(),runtime->options(),runtime->mode(),runtime->completion()});
    runtime->declare_benchmark_context(std::move(options.declared_benchmark));
    queue.emplace(runtime->plan().source_catalog(),window?io::QueueMode::window:io::QueueMode::physical,
        limits,options.input.limits);
    retain_report_metadata();
  }
  ~Impl() { drop(); }
  bool has_private() const noexcept { return pending.has_value() || window_pending.has_value(); }
  void admission_available() const {
    require(control!=SessionState::dropped,"session_dropped","the query session has been dropped");
    require(control!=SessionState::stopped,"session_stopped","the query session has been stopped");
    require(control!=SessionState::paused,"session_paused","resume admission before feeding input");
    require(queue.has_value(),"session_not_typed","this session owns a stream input");
  }
  void available(bool paused_ok=false) const {
    require(control!=SessionState::dropped,"session_dropped","the query session has been dropped");
    require(control!=SessionState::stopped,"session_stopped","the query session has been stopped");
    require(control!=SessionState::created,"session_not_started","start the query session first");
    require(paused_ok || control!=SessionState::paused,"session_paused","resume admission before advancing the query session");
  }
  SessionPhase phase() const noexcept {
    if (pending) {
      switch (pending->state()) {
        case DeltaState::paused: return SessionPhase::paused_pending;
        case DeltaState::draining: return SessionPhase::draining;
        case DeltaState::epoch_prepared: return SessionPhase::prepared;
        default: return SessionPhase::pending;
      }
    }
    if (window_pending) {
      if (metadata_ready) return SessionPhase::prepared;
      if (metadata_draining) return SessionPhase::draining;
      return control==SessionState::paused?SessionPhase::paused_pending:SessionPhase::pending;
    }
    return output?SessionPhase::output:SessionPhase::ready;
  }
  const io::InputProgress& accepted() const { return reader?reader->progress():(queue?queue->progress():final_progress); }
  void need_pending() const {
    require(has_private(),"session_no_pending_epoch","the query session has no private pending input");
  }
  void abort() noexcept {
    if (pending) { pending->rollback(); pending.reset(); }
    window_pending.reset(); pending_command_sequence.reset(); metadata_ready=false; metadata_draining=false;
  }
  void retain_report_metadata() noexcept {
    if(runtime)retained_report_metadata=SessionReportMetadata(runtime->plan(),runtime->options(),
        runtime->profile(),runtime->owner(),runtime->sequence(),runtime->state());
  }
  void retain_observation() noexcept {
    retain_report_metadata();
    if (runtime) {
      retained_observation=runtime->observations();
      retained_cursor_observation=runtime->last_cursor_observation();
    }
    retained_observation.session_context=run_context;
    retained_observation.session_attached=true;
    retained_observation.session_committed_sequence=committed_sequence;
  }
  void publish(DeltaRuntime::Epoch epoch,std::uint64_t sequence,bool discard) noexcept {
    // The reader prepared its source map node before engine work. Once the
    // engine publishes, every operation here is a nonthrowing move or cleanup.
    acknowledge(); committed_sequence=sequence; pending.reset();
    if (discard) { epoch.discard(); retain_observation(); }
    else {
      output.emplace(std::move(epoch));
      // Even an inactive Epoch still owns PhysicalEpoch journals/source pins.
      retain_observation();
      if (!output->active()) output.reset();
    }
  }
  void acknowledge() noexcept {
    bool complete=true;
    if (window_pending) {
      complete=window_pending->completes_command();
      window_pending->publish(); window_pending.reset();
    }
    if (complete) {
      if (reader) reader->acknowledge();
      else queue->acknowledge();
    }
    pending_command_sequence.reset(); metadata_ready=false; metadata_draining=false;
  }
  SessionBegin begin() {
    available();
    require(!has_private(),"session_pending_epoch","finish the private pending input before reading another event");
    require(!output,"session_output_pending","consume or discard committed output before reading another event");
    require(runtime->ready(),"runtime_busy","session runtime is not at a writer-ready barrier");
    require(runtime->sequence()==committed_sequence && (window || accepted().sequence==committed_sequence),
        "invalid_sequence","session source and runtime committed progress differ");
    require(!window_input_failed,"input_failed","window input has failed semantic validation");
    try {
      if (reader) {
        const auto* event=reader->peek();
        if (!event) { end_of_input=true; return SessionBegin::end; }
        pending.emplace(runtime->begin(event->update));
      } else {
        const auto* item=queue->peek();
        if (!item) {
          if (!queue->closed()) return SessionBegin::would_block;
          end_of_input=true; return SessionBegin::end;
        }
        if (window) {
          const auto next=committed_sequence==std::numeric_limits<std::uint64_t>::max()
              ?committed_sequence:committed_sequence+1;
          window_pending.emplace(window->prepare(std::get<io::WindowCommand>(*item),next));
          pending_command_sequence=std::get<io::WindowCommand>(*item).sequence;
          if (window_pending->update()) pending.emplace(runtime->begin(*window_pending->update()));
        } else pending.emplace(runtime->begin(std::get<io::InputEvent>(*item).update));
      }
      return SessionBegin::pending;
    } catch (const Error& error) {
      const auto& code=error.code();
      window_input_failed=window_input_failed || code=="invalid_window_command" ||
          code=="window_fifo_violation" || code=="late_window_event";
      input_failed=input_failed || window_input_failed || (reader && reader->failed()) || (queue && queue->failed());
      abort(); throw;
    } catch (...) { abort(); throw; }
  }
  void stop() noexcept {
    if (control==SessionState::stopped || control==SessionState::dropped) return;
    abort();
    if (output) { output->discard(); retain_observation(); output.reset(); }
    if (reader) {
      input_failed=input_failed || reader->failed();
      final_progress=reader->close(); reader.reset();
    }
    if (queue) {
      input_failed=input_failed || queue->failed();
      final_progress=queue->close(); queue.reset();
    }
    if (window) window->stop();
    retain_observation(); input.reset(); control=SessionState::stopped;
  }
  void drop() noexcept {
    if (control==SessionState::dropped) return;
    stop(); window.reset(); runtime.reset();
    if (retained_observation.options.mode==ObservationMode::trace) {
      retained_observation.trace=TraceDisposition::released;
      retained_observation.trace_records=0;
    }
    final_progress=io::InputProgress{}; control=SessionState::dropped;
  }
};

QuerySession::QuerySession(std::unique_ptr<Impl> data) noexcept:data_(std::move(data)) {}
#ifdef CROWN_RUNTIME_TESTING
void RuntimeTestProbe::seed_session_physical_sequence(QuerySession& runtime,std::uint64_t sequence) {
  auto& d=*runtime.data_; QuerySession::Impl::Guard guard(d);
  require(d.window && !d.has_private() && !d.output,"invalid_probe","sequence probe needs a ready window session");
  seed_delta_sequence(*d.runtime,sequence); seed_window_sequence(*d.window,sequence); d.committed_sequence=sequence;
}
#endif
std::unique_ptr<QuerySession> QuerySession::create(PhysicalPlan plan,std::unique_ptr<std::istream> input,SessionOptions options) {
  auto data=std::make_unique<Impl>(std::move(plan),std::move(input),std::move(options));
  return std::unique_ptr<QuerySession>(new QuerySession(std::move(data)));
}
std::unique_ptr<QuerySession> QuerySession::create(PhysicalPlan plan,const Database& initial,
    std::unique_ptr<std::istream> input,SessionOptions options,BuildOptions build) {
  auto data=std::make_unique<Impl>(std::move(plan),std::move(input),std::move(options),&initial,build);
  return std::unique_ptr<QuerySession>(new QuerySession(std::move(data)));
}
std::unique_ptr<QuerySession> QuerySession::create_typed(PhysicalPlan plan,io::QueueLimits limits,SessionOptions options) {
  auto data=std::make_unique<Impl>(std::move(plan),limits,std::move(options),std::nullopt);
  return std::unique_ptr<QuerySession>(new QuerySession(std::move(data)));
}
std::unique_ptr<QuerySession> QuerySession::create_typed(PhysicalPlan plan,const Database& initial,
    io::QueueLimits limits,SessionOptions options,BuildOptions build) {
  auto data=std::make_unique<Impl>(std::move(plan),limits,std::move(options),std::nullopt,&initial,build);
  return std::unique_ptr<QuerySession>(new QuerySession(std::move(data)));
}
std::unique_ptr<QuerySession> QuerySession::create_windowed(PhysicalPlan plan,WindowOptions window,
    io::QueueLimits limits,SessionOptions options) {
  auto data=std::make_unique<Impl>(std::move(plan),limits,std::move(options),std::move(window));
  return std::unique_ptr<QuerySession>(new QuerySession(std::move(data)));
}
std::unique_ptr<QuerySession> QuerySession::create_windowed(PhysicalPlan plan,const Database& initial,
    WindowOptions window,io::QueueLimits limits,SessionOptions options,BuildOptions build) {
  auto data=std::make_unique<Impl>(std::move(plan),limits,std::move(options),std::move(window),&initial,build);
  return std::unique_ptr<QuerySession>(new QuerySession(std::move(data)));
}
QuerySession::~QuerySession() {
  // Exclusive lifetime is required. Keep Impl alive and reentrancy blocked
  // through owned stream destruction; never call a throwing public guard here.
  data_->busy=true; data_->drop();
}
SessionStatus QuerySession::status() const {
  auto& d=*data_; Impl::Guard guard(d);
  return {d.control,d.phase(),d.committed_sequence,d.input_failed || (d.reader && d.reader->failed()) || (d.queue && d.queue->failed()),d.end_of_input,
      d.pending?std::optional<std::uint64_t>{d.pending->sequence()}:std::nullopt,
      d.pending?d.pending->metrics().work:0,d.output?d.output->remaining():0,
      d.queue?std::optional<io::QueueStats>{d.queue->stats()}:std::nullopt,
      d.window?std::optional<WindowProgress>{d.window->progress()}:std::nullopt,d.pending_command_sequence};
}
io::InputProgress QuerySession::progress() const {
  auto& d=*data_; Impl::Guard guard(d);
  require(d.control!=SessionState::dropped,"session_dropped","the query session has been dropped"); return d.accepted();
}
void QuerySession::start() {
  auto& d=*data_; Impl::Guard guard(d);
  require(d.control!=SessionState::dropped,"session_dropped","the query session has been dropped");
  require(d.control!=SessionState::stopped,"session_stopped","a stopped query session cannot restart its input");
  if (d.control==SessionState::paused && d.pending && d.pending->state()==DeltaState::paused) d.pending->resume();
  d.control=SessionState::running;
}
void QuerySession::pause() {
  auto& d=*data_; Impl::Guard guard(d); d.available(true);
  if (d.control==SessionState::paused) return;
  if (d.pending && d.pending->state()==DeltaState::pending_delta) d.pending->pause();
  // Draining/prepared/output do not have a D06 pause state. Admission and
  // producer stepping still stop; explicit one-epoch drain remains allowed.
  d.control=SessionState::paused;
}
io::Admission QuerySession::enqueue(io::TransportBatch& batch) {
  auto& d=*data_; Impl::Guard guard(d); d.admission_available(); return d.queue->enqueue(batch);
}
void QuerySession::finish_input() {
  auto& d=*data_; Impl::Guard guard(d); d.admission_available(); d.queue->finish();
}
SessionBegin QuerySession::begin_next_result() {
  auto& d=*data_; Impl::Guard guard(d); return d.begin();
}
bool QuerySession::begin_next() {
  auto& d=*data_; Impl::Guard guard(d);
  const auto result=d.begin();
  require(result!=SessionBegin::would_block,"input_would_block","typed input is open and currently empty");
  return result==SessionBegin::pending;
}
DeltaStep QuerySession::step() {
  auto& d=*data_; Impl::Guard guard(d); d.available(); d.need_pending();
  if (!d.pending) { d.metadata_ready=true; return DeltaStep::prepared; }
  try { return d.pending->step(); } catch (...) { d.abort(); throw; }
}
void QuerySession::commit() {
  auto& d=*data_; Impl::Guard guard(d); d.available(); d.need_pending();
  if (!d.pending) {
    require(d.metadata_ready,"session_epoch_not_prepared","finish private preparation before committing input");
    d.acknowledge(); return;
  }
  require(d.pending->state()==DeltaState::epoch_prepared,"session_epoch_not_prepared","finish private production before committing input");
  const auto sequence=d.pending->sequence();
  try { d.publish(d.pending->commit(),sequence,false); } catch (...) { d.abort(); throw; }
}
void QuerySession::start_drain() {
  auto& d=*data_; Impl::Guard guard(d); d.available(true); d.need_pending();
  if (!d.pending) { d.metadata_draining=true; return; }
  try { d.pending->start_drain(); } catch (...) { d.abort(); throw; }
}
void QuerySession::drain() {
  auto& d=*data_; Impl::Guard guard(d); d.available(true);
  if (d.pending) {
    const auto sequence=d.pending->sequence();
    try { d.publish(d.pending->discard(),sequence,true); } catch (...) { d.abort(); throw; }
  } else if (d.window_pending) { d.acknowledge(); }
  else if (d.output) { d.output->discard(); d.retain_observation(); d.output.reset(); }
}
std::optional<SignedResult> QuerySession::next_output() {
  auto& d=*data_; Impl::Guard guard(d); d.available(true);
  require(!d.has_private(),"session_pending_epoch","private pending output cannot be observed before commitment");
  if (!d.output) return {};
  auto row=d.output->next(); d.retain_observation(); if (!d.output->active()) d.output.reset(); return row;
}
SessionSnapshot QuerySession::snapshot(std::optional<SnapshotLimits> limits) const {
  auto& d=*data_; Impl::Guard guard(d);
  require(d.control!=SessionState::dropped,"session_dropped","the query session has been dropped");
  require(!d.has_private(),"session_pending_epoch","snapshots require a committed epoch boundary");
  const auto budget=limits.value_or(d.snapshot_limits);
  SessionSnapshot result{d.committed_sequence,d.accepted(),d.runtime->result_layout(),{},0,
      d.window?std::optional<WindowProgress>{d.window->progress()}:std::nullopt};
  auto cursor=d.runtime->results(budget.cursor);
  std::size_t payload_bytes=0;
  while (auto row=cursor.next()) {
    const auto count=add(result.rows.size(),1);
    require(count<=budget.rows,"resource_limit","session snapshot row limit exceeded");
    const auto next_payload=add(payload_bytes,payload(*row));
    require(next_payload<=budget.bytes,"resource_limit","session snapshot payload limit exceeded");
    if (result.rows.size()==result.rows.capacity()) {
      const auto old=result.rows.capacity();
      const auto preferred=old==0?std::size_t{1}:add(old,std::min(old,budget.rows-old));
      const auto capacity=std::min({preferred,budget.rows,(budget.bytes-next_payload)/sizeof(storage::Tuple)});
      require(capacity>=count,"resource_limit","session snapshot vector limit exceeded");
      result.rows.reserve(capacity);
    }
    const auto bytes=add(slots(result.rows.capacity(),sizeof(storage::Tuple)),next_payload);
    require(bytes<=budget.bytes,"resource_limit","session snapshot byte limit exceeded");
    result.rows.push_back(std::move(*row)); payload_bytes=next_payload; result.accounted_bytes=bytes;
  }
  return result;
}
std::optional<WindowCanonicalState> QuerySession::window_state() const {
  auto& d=*data_; Impl::Guard guard(d);
  require(d.control!=SessionState::dropped,"session_dropped","the query session has been dropped");
  require(!d.has_private(),"session_pending_epoch","window inspection requires a committed step boundary");
  if (!d.window) return std::nullopt;
  return d.window->canonical_state();
}
void QuerySession::stop() { auto& d=*data_; Impl::Guard guard(d); d.stop(); }
void QuerySession::drop() { auto& d=*data_; Impl::Guard guard(d); d.drop(); }
std::shared_ptr<const SessionRunContext> QuerySession::run_context() const {
  auto& d=*data_; Impl::Guard guard(d); return d.run_context;
}
SessionReportMetadata QuerySession::report_metadata() const {
  auto& d=*data_;Impl::Guard guard(d);
  if(d.runtime)return SessionReportMetadata(d.runtime->plan(),d.runtime->options(),
      d.runtime->profile(),d.runtime->owner(),d.runtime->sequence(),d.runtime->state());
  const auto& saved=*d.retained_report_metadata;
  return SessionReportMetadata(saved.plan(),saved.options(),saved.profile(),saved.owner(),saved.sequence(),{});
}
std::optional<CommittedStateGauges> QuerySession::report_gauges() const {
  auto& d=*data_;Impl::Guard guard(d);
  if(!d.runtime || d.has_private())return {};
  return d.runtime->committed_state_gauges();
}
std::optional<CursorObservation> QuerySession::last_cursor_observation() const {
  auto& d=*data_; Impl::Guard guard(d);
  return d.runtime?d.runtime->last_cursor_observation():d.retained_cursor_observation;
}
ObservationSnapshot QuerySession::observations() const {
  auto& d=*data_; Impl::Guard guard(d);
  auto result=d.runtime?d.runtime->observations():d.retained_observation;
  result.session_context=d.run_context;
  result.session_attached=true; result.session_committed_sequence=d.committed_sequence;
  return result;
}
ObservationTrace QuerySession::observation_trace() const {
  auto& d=*data_; Impl::Guard guard(d);
  // Drop releases optional trace storage, retaining only the fixed summary.
  auto result=d.runtime?d.runtime->observation_trace():ObservationTrace{d.retained_observation,{}};
  result.snapshot.session_context=d.run_context;
  result.snapshot.session_attached=true;
  result.snapshot.session_committed_sequence=d.committed_sequence;
  return result;
}
}  // namespace crown::runtime

namespace crown::runtime {
std::optional<statistics::OwnerCapture> QuerySession::capture_statistics(const statistics::OwnerRequest& request,statistics::Limits limits) const {
  auto& d=*data_;Impl::Guard guard(d);if(!d.runtime)return {};
  if(d.has_private()){statistics::detail::OwnerBuilder pending{{d.runtime->owner(),d.runtime->sequence(),statistics::OwnerLayer::physical},d.runtime->plan(),request,limits,true};return pending.finish();}
  return d.runtime->capture_statistics(request,limits);
}
std::optional<statistics::Freshness> QuerySession::statistics_freshness(const statistics::OwnerCapture& captured,std::uint64_t max_event_lag) const {
  auto& d=*data_;Impl::Guard guard(d);if(!d.runtime)return {};
  return d.runtime->statistics_freshness(captured,max_event_lag);
}
}
