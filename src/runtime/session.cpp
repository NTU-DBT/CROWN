#include "update_pattern_detail.hpp"
#include "crown/runtime/session.hpp"
#include "crown/runtime/session_checkpoint.hpp"
#include "crown/runtime/session_journal.hpp"
#include "crown/runtime/session_generation.hpp"
#include "crown/runtime/session_local_sink.hpp"
#include "crown/runtime/session_reoptimization.hpp"
#include "crown/io/compiler_plan_artifact.hpp"
#include "crown/ir/digest.hpp"
#include "crown/recovery/session_image.hpp"
#include "crown/recovery/session_file.hpp"
#include "../recovery/session_image_detail.hpp"
#include "../recovery/session_file_detail.hpp"
#include "../recovery/generation_detail.hpp"
#include "storage_work.hpp"
#include "../io/checkpoint_detail.hpp"
#include "memory_report_detail.hpp"
#include "owner_statistics_detail.hpp"
#include "reoptimization_detail.hpp"

#include "crown/api/error.hpp"
#ifdef CROWN_RUNTIME_TESTING
#include "runtime_probe.hpp"
#endif
#include <algorithm>
#include <limits>
#include <new>
#include <stdexcept>
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
std::size_t payload(const storage::Tuple& tuple) {
  require(tuple.is_accounted(),"runtime_contract","snapshot output has no query-account payload");
  const auto bytes=tuple.memory_usage().requested_bytes;
  require(bytes<=std::numeric_limits<std::size_t>::max(),"resource_limit","snapshot payload exceeds host size_t");
  return static_cast<std::size_t>(bytes);
}
static_assert(std::is_nothrow_move_constructible_v<DeltaRuntime::PendingEpoch>);
static_assert(std::is_nothrow_move_constructible_v<DeltaRuntime::Epoch>);
static_assert(std::is_nothrow_move_constructible_v<SignedResult>);
static_assert(std::is_nothrow_move_constructible_v<io::InputProgress>);
static_assert(std::is_nothrow_move_assignable_v<io::InputProgress>);
static_assert(std::is_nothrow_move_constructible_v<SessionSnapshot>);
}  // namespace

struct SessionRows::Data {
  std::vector<storage::Tuple,resource::MemoryAllocator<storage::Tuple>> values;
  resource::MemoryUsage control_usage;
  explicit Data(const resource::MemoryAccount& account)
      :values(resource::MemoryAllocator<storage::Tuple>(account,resource::MemoryPurpose::output_buffer,
          {resource::MemoryOwnerKind::output,0})) {}
};
std::size_t SessionRows::size() const noexcept {return data_?data_->values.size():0;}
std::size_t SessionRows::capacity() const noexcept {return data_?data_->values.capacity():0;}
const storage::Tuple* SessionRows::data() const noexcept {return data_?data_->values.data():nullptr;}
const storage::Tuple& SessionRows::at(std::size_t i) const {
  if(i>=size())throw std::out_of_range("snapshot row is out of range");
  return (*this)[i];
}
resource::MemoryUsage SessionRows::owner_usage() const noexcept {return data_?data_->control_usage:resource::MemoryUsage{};}
resource::MemoryUsage SessionRows::memory_usage() const {
  auto usage=owner_usage();
  if(data_) {
    const auto slots=data_->values.get_allocator().allocation_usage(data_->values.data(),data_->values.capacity());
    usage.allocations+=slots.allocations;usage.requested_bytes+=slots.requested_bytes;usage.payload_bytes+=slots.payload_bytes;
  }
  return usage;
}
void SessionRows::prepare() {
  if(data_) {
    require(data_.use_count()==1,"runtime_contract","snapshot collection already published");return;
  }
  const auto before=account_.statistics().current;
  auto data=resource::make_accounted_shared<Data>({resource::MemoryOwnerKind::output,0},account_,
      resource::MemoryPurpose::output_buffer,account_);
  const auto after=account_.statistics().current;
  // Data's constructor only installs an empty allocator-aware vector. This is
  // its actual shared object/control allocation, with no nested allocations.
  data->control_usage={after.allocations-before.allocations,after.requested_bytes-before.requested_bytes,
      after.payload_bytes-before.payload_bytes};
  data_=std::move(data);
}
void SessionRows::reserve(std::size_t capacity) {prepare();data_->values.reserve(capacity);}
void SessionRows::append(storage::Tuple tuple) {
  prepare();
  require(tuple.is_accounted() && tuple.account_statistics().owner==account_.statistics().owner,
      "runtime_contract","snapshot row belongs to another query account");
  data_->values.push_back(std::move(tuple));
}

struct SessionStatisticsContext::Data {
  SessionReportMetadata metadata;
  SessionStatus status;
  CapturedObservationTrace trace;
  std::optional<statistics::CombinedCapture> combined;
  workload::Options options;
  std::optional<CursorObservation> cursor;
  bool requested;
};
const SessionReportMetadata& SessionStatisticsContext::metadata() const noexcept{return data_->metadata;}
const SessionStatus& SessionStatisticsContext::status() const noexcept{return data_->status;}
const CapturedObservationTrace& SessionStatisticsContext::trace() const noexcept{return data_->trace;}
const std::optional<statistics::CombinedCapture>& SessionStatisticsContext::combined() const noexcept{return data_->combined;}
const workload::Options& SessionStatisticsContext::workload_options() const noexcept{return data_->options;}
const std::optional<CursorObservation>& SessionStatisticsContext::cursor() const noexcept{return data_->cursor;}
bool SessionStatisticsContext::state_requested() const noexcept{return data_->requested;}

namespace {
struct ManagedPlan {
  recovery::EncodedPlanDescriptor encoded;
  recovery::PlanSelection selection;
  std::size_t artifact_size;
  ManagedPlan(recovery::EncodedPlanDescriptor bytes,recovery::PlanSelection metadata,std::size_t size)
      :encoded(std::move(bytes)),selection(std::move(metadata)),artifact_size(size) {}
  [[nodiscard]] std::string_view bytes() const noexcept {return {encoded.bytes.data(),encoded.bytes.size()};}
  [[nodiscard]] std::string_view artifact() const noexcept {return bytes().substr(encoded.bytes.size()-64-artifact_size,artifact_size);}
};
bool logical_binding(const recovery::ImageBinding& a,const recovery::ImageBinding& b) {
  return a.source_sha256==b.source_sha256 && a.catalog_version==b.catalog_version && a.policy==b.policy;
}
template<std::size_t N> std::string_view view(const std::array<char,N>& value) noexcept {return {value.data(),value.size()};}
void generation_binding(bool condition) {
  if(!condition)throw recovery::GenerationFailure(recovery::GenerationFault::binding,recovery::GenerationStage::state,recovery::GenerationOutcome::unchanged);
}
std::array<char,64> result_schema(const resource::MemoryAccount& account,const DeltaRuntime& runtime) {
  recovery::ImageVector<ScalarType> fields(recovery::image_allocator<ScalarType>(account));fields.reserve(runtime.result_layout().fields().size());
  for(const auto& field:runtime.result_layout().fields())fields.push_back(field.type);
  return recovery::sink::schema_sha256(account,fields);
}
struct PublicationPreparation {
  reoptimization::detail::State& candidate;
  reoptimization::detail::State::Clock::time_point started;
  bool finished=false;
  explicit PublicationPreparation(reoptimization::detail::State& state):candidate(state),started(state.time()) {}
  ~PublicationPreparation() {if(!finished && candidate.active())static_cast<void>(candidate.publication_prepared(started));}
  bool finish() noexcept {finished=true;return candidate.publication_prepared(started);}
};
struct ManagedGeneration {
  recovery::detail::GenerationOwner file;
  SessionGenerationOptions options;
  resource::AccountedUnique<ManagedPlan> plan;
  ManagedGeneration(recovery::detail::GenerationOwner&& owner,const SessionGenerationOptions& policy)
      :file(std::move(owner)),options(policy) {}
};
struct ManagedLocalSink {
  recovery::sink::Header header;
  SessionLocalSinkOptions options;
  recovery::ImageVector<ScalarType> schema;
  std::optional<recovery::sink::File> file;
  std::uint64_t verified_sequence=0;
  std::uint64_t delivery_work=0;
  std::uint64_t blocked_inputs=0;
  bool replaying=false,failed=false;
  std::optional<recovery::GenerationDeliveryAnchor> verified_prefix;
  explicit ManagedLocalSink(const resource::MemoryAccount& account):schema(recovery::image_allocator<ScalarType>(account)) {}
};
void generation_checkpoint_policy(std::string_view path,const recovery::CheckpointFileLimits& limits) {
  if(limits.path_bytes>=4096 || path.size()>limits.path_bytes || limits.chunk_bytes==0 || limits.operations==0 ||
      limits.chunk_bytes>static_cast<std::size_t>(std::numeric_limits<std::int64_t>::max()))
    throw recovery::GenerationFailure(recovery::GenerationFault::limit,recovery::GenerationStage::path,recovery::GenerationOutcome::unchanged);
}
struct RecoveryOutput {
  recovery::ImageVector<RecoveredResult> rows;
  std::size_t position=0;
  std::uint64_t payload_bytes=0;
  explicit RecoveryOutput(const resource::MemoryAccount& account):rows(recovery::image_allocator<RecoveredResult>(account)) {}
  std::uint64_t retained_bytes() const {
    return resource::MemoryAccount::allocation_bytes(sizeof(RecoveryOutput),alignof(RecoveryOutput))+
        rows.get_allocator().allocation_usage(rows.data(),rows.capacity()).requested_bytes+payload_bytes;
  }
  void append(RecoveredResult row,std::size_t max_rows,std::size_t max_bytes) {
    if(rows.size()>=max_rows)throw recovery::ImageFailure(recovery::ImageFault::limit);
    if(!row.value.tuple.is_accounted() || row.value.tuple.account_statistics().owner!=rows.get_allocator().account().statistics().owner)throw resource::MemoryFailure(resource::MemoryFault::contract);
    const auto bytes=row.value.tuple.memory_usage().requested_bytes;
    if(bytes>max_bytes || payload_bytes>max_bytes-bytes)throw recovery::ImageFailure(recovery::ImageFault::limit);
    const auto capacity=rows.size()<rows.capacity()?rows.capacity():std::min(max_rows,rows.capacity()>max_rows/2?max_rows:std::max<std::size_t>(1,2*rows.capacity()));
    if(capacity>SIZE_MAX/sizeof(RecoveredResult))throw recovery::ImageFailure(recovery::ImageFault::limit);
    const auto slots=resource::MemoryAccount::allocation_bytes(capacity*sizeof(RecoveredResult),alignof(RecoveredResult));
    const auto control=resource::MemoryAccount::allocation_bytes(sizeof(RecoveryOutput),alignof(RecoveryOutput));
    if(control>max_bytes || slots>max_bytes-control || payload_bytes+bytes>max_bytes-control-slots)throw recovery::ImageFailure(recovery::ImageFault::limit);
    if(capacity>rows.capacity())rows.reserve(capacity);
    if(retained_bytes()+bytes>max_bytes)throw recovery::ImageFailure(recovery::ImageFault::limit);
    rows.push_back(std::move(row));payload_bytes+=bytes;
  }
};
}
struct LockedGenerationRecovery::Data {
  recovery::detail::GenerationOwner owner;
  SessionGenerationRecoveryOptions options;
  CompiledProgram expected;
  std::shared_ptr<detail::StorageWorkContext> context;
  resource::AccountedUnique<ManagedPlan> plan;
  Data(recovery::detail::GenerationOwner file,SessionGenerationRecoveryOptions policy,CompiledProgram source,
      std::shared_ptr<detail::StorageWorkContext> receiving,resource::AccountedUnique<ManagedPlan> descriptor)
      :owner(std::move(file)),options(policy),expected(std::move(source)),context(std::move(receiving)),plan(std::move(descriptor)) {}
};
LockedGenerationRecovery::LockedGenerationRecovery(resource::AccountedUnique<Data> data) noexcept:data_(std::move(data)) {}
LockedGenerationRecovery::~LockedGenerationRecovery()=default;
bool LockedGenerationRecovery::has_plan() const noexcept {return bool(data_->plan);}
std::string_view LockedGenerationRecovery::compiler_artifact() const & noexcept {
  return data_->plan?data_->plan->artifact():std::string_view{};
}
resource::MemoryStatistics LockedGenerationRecovery::accounted_memory_statistics() const {return data_->context->memory().statistics();}
struct QuerySession::Impl {
  const std::thread::id writer=std::this_thread::get_id();
  bool busy=false;
  SessionState control=SessionState::created;
  std::uint64_t committed_sequence=0;
  bool input_failed=false,end_of_input=false,semantic_input_failed=false;
  SnapshotLimits snapshot_limits;
  std::shared_ptr<const SessionRunContext> run_context;
  PatternHistory pattern_history=PatternHistory::current_session;
  std::uint64_t pattern_origin_sequence=0,pattern_origin_command_sequence=0;
  std::optional<PatternViolation> pattern_violation;
  std::optional<recovery::journal::File> journal;
  resource::AccountedUnique<ManagedGeneration> generation;
  resource::AccountedUnique<ManagedLocalSink> local_sink;
  resource::AccountedUnique<reoptimization::detail::State> reoptimization;
  std::optional<std::uint64_t> last_switch_epoch;
  recovery::journal::Limits journal_record_limits;
  SessionJournalState journal_confirmed;
  resource::AccountedUnique<RecoveryOutput> recovered_output;
  SessionJournalRecoveryStatus recovered_status;
  bool recovery_output_complete=false;
  std::uint64_t recovery_end_sequence=0;
  bool delivery_pending() const noexcept {return local_sink && (local_sink->failed || !local_sink->file || local_sink->verified_sequence<committed_sequence);}
  bool recovery_output_pending() const noexcept {return recovered_output && recovered_output->position<recovered_output->rows.size();}
  std::size_t output_remaining() const {return output?output->remaining():recovered_output?recovered_output->rows.size()-recovered_output->position:0;}
  void clear_recovered_output() noexcept {recovered_output.reset();}
  void prepare_local_sink(const recovery::journal::Header& journal,const SessionLocalSinkOptions& options,bool replaying) {
    const auto& account=runtime->compiled_program().account();
    auto sink=resource::make_accounted_unique<ManagedLocalSink>(recovery::image_owner,account,resource::MemoryPurpose::recovery_log,account);sink->options=options;
    const auto fields=runtime->result_layout().fields();require(fields.size()<=options.file.record.fields,"resource_limit","sink schema exceeds configured fields");sink->schema.reserve(fields.size());
    for(const auto& field:fields)sink->schema.push_back(field.type);
    sink->header={journal.query_id,options.sink_id,journal.binding,journal.generation,journal.physical_sequence,fields.size(),recovery::sink::schema_sha256(account,sink->schema)};
    sink->verified_sequence=journal.physical_sequence;sink->replaying=replaying;local_sink=std::move(sink);
  }
  void establish_sink_prefix(const recovery::sink::File& file,const recovery::journal::Header& journal,
      const std::optional<recovery::GenerationDeliveryAnchor>& expected) {
    auto& sink=*local_sink;const auto state=file.state();
    const auto matches=[&](const recovery::GenerationDeliveryAnchor& anchor){const auto prefix=file.prefix(anchor.sequence);return anchor.sink_id==state.header.sink_id && anchor.bytes==prefix.bytes && anchor.content_sha256==prefix.content_sha256;};
    if(expected)require(expected->sequence==journal.physical_sequence && matches(*expected),"local_sink_binding","sink prefix differs from the durable checkpoint delivery anchor");
    if(sink.verified_prefix)require(matches(*sink.verified_prefix),"local_sink_binding","sink prefix changed since native verification");
    else if(expected || state.header.base_sequence==journal.physical_sequence) {
      const auto prefix=file.prefix(journal.physical_sequence);sink.verified_prefix=recovery::GenerationDeliveryAnchor{state.header.sink_id,prefix.sequence,prefix.bytes,prefix.content_sha256};
    }
  }
  void advance_sink_prefix(std::uint64_t sequence) {
    auto& sink=*local_sink;if(sink.verified_prefix){const auto prefix=sink.file->prefix(sequence);sink.verified_prefix=recovery::GenerationDeliveryAnchor{sink.header.sink_id,prefix.sequence,prefix.bytes,prefix.content_sha256};}
  }
  void collect_recovered_output(const recovery::journal::Header& header,const SessionJournalRecoveryOptions& options) {
    const auto sequence=committed_sequence;
    if(local_sink && sequence<=local_sink->file->state().sequence) {
      auto& sink=*local_sink;
      require(sequence>sink.verified_sequence && sequence-sink.verified_sequence==1,"local_sink_binding","sink verification skipped a physical epoch");
      const auto count=output?output->remaining():0;
      require(count<=sink.options.file.record.rows,"resource_limit","sink row limit exceeded");
      if(sink.delivery_work>=sink.options.delivery_work || count>sink.options.delivery_work-sink.delivery_work-1)throw recovery::ImageFailure(recovery::ImageFault::work);
      sink.delivery_work+=1+count;
      recovery::ImageVector<recovery::sink::RowView> rows(recovery::image_allocator<recovery::sink::RowView>(runtime->compiled_program().account()));rows.reserve(count);
      if(output)output->visit_complete([](const SignedResult& value,void* context){auto& values=*static_cast<recovery::ImageVector<recovery::sink::RowView>*>(context);values.push_back({value.operation,value.tuple.values()});},&rows);
      sink.file->verify_epoch(header.generation,sequence,rows);
      if(output){output->acknowledge_complete();retain_observation();output.reset();}
      advance_sink_prefix(sequence);sink.verified_sequence=sequence;return;
    }
    if(!output)return;
    if(sequence<=options.outputs_after_physical_sequence.value_or(header.physical_sequence)){output->discard();output.reset();return;}
    while(auto value=output->next()) {
      if(!recovered_output) {
        if(resource::MemoryAccount::allocation_bytes(sizeof(RecoveryOutput),alignof(RecoveryOutput))>options.output_bytes)throw recovery::ImageFailure(recovery::ImageFault::limit);
        const auto& account=runtime->compiled_program().account();recovered_output=resource::make_accounted_unique<RecoveryOutput>(recovery::image_owner,account,resource::MemoryPurpose::recovery_log,account);
      }
      recovered_output->append(RecoveredResult{header.query_id,header.generation,sequence,std::move(*value)},options.output_rows,options.output_bytes);
    }
    output.reset();retain_observation();
  }
  static void replay_frame(std::string_view frame,const recovery::journal::Scanned& after,void* context);
  struct ReplayContext {Impl& data;const SessionJournalRecoveryOptions& options;recovery::journal::Header header;std::uint64_t remaining,source_remaining;};

  void journal_available() const {
    if(journal_confirmed.recovery_required)throw SessionJournalFailure(SessionJournalFault::recovery_required);
  }
  void require_recovery() noexcept {
    journal_confirmed.recovery_required=true;
    if(reoptimization)reoptimization->cancel(reoptimization::Phase::recovery_required,reoptimization::Stop::native_failure);
  }
  void journal_confirm() noexcept {
    const auto state=journal->state();
    journal_confirmed={true,false,state.records,state.physical_sequence,state.command_sequence,
        state.pending?state.pending->next_substep:0,state.pending?std::optional<std::uint64_t>{state.pending->ordinal}:std::nullopt};
  }
  void journal_append(std::string_view frame) {
    try{journal->append(frame);journal_confirm();}
    catch(const recovery::journal::FileFailure&){require_recovery();throw;}
  }
  void journal_input(const io::InputItemView& item) {
    if(!journal)return;
    journal_available();const auto state=journal->state();
    const auto sequence=std::visit([](const auto& input)->std::uint64_t {
      using T=std::remove_cvref_t<decltype(input)>;
      if constexpr(std::is_same_v<T,io::InputEventView>)return input.update.sequence;else return input.sequence;
    },item);
    if(state.pending) {
      if(state.pending->input.sequence!=sequence)throw SessionJournalFailure(SessionJournalFault::state);
      return; // Immutable reader/queue head is retained through retries/substeps.
    }
    recovery::journal::InputView input_view{item,{}};
    if(reader) {
      const auto position=reader->decoder_position();
      input_view.reader=recovery::journal::ReaderAdvanceView{position.bytes,position.records,position.header_read,position.csv_fields};
    }
    const auto encoded=recovery::journal::encode(runtime->compiled_program().account(),state.records,
        recovery::journal::PayloadView{input_view},journal_record_limits);
    journal_append({encoded.bytes.data(),encoded.bytes.size()});
  }
  void journal_decision() {
    if(!journal)return;
    journal_available();const auto state=journal->state();
    if(!state.pending)throw SessionJournalFailure(SessionJournalFault::state);
    const bool complete=!window_pending || window_pending->completes_command();
    recovery::journal::Commit decision{state.pending->ordinal,state.pending->input_sha256,
        pending?recovery::journal::CommitKind::physical:recovery::journal::CommitKind::metadata,
        pending?pending->sequence():committed_sequence,complete?state.pending->input.sequence:accepted_sequence(),state.pending->next_substep,complete};
    const auto encoded=recovery::journal::encode(runtime->compiled_program().account(),state.records,
        recovery::journal::PayloadView{decision},journal_record_limits);
    journal_append({encoded.bytes.data(),encoded.bytes.size()});
  }
  void finish(bool discard) {
    bool decided=false;
    try {
      journal_decision();decided=journal.has_value();
      if(pending){const auto sequence=pending->sequence();publish(pending->commit(),sequence,discard);}
      else acknowledge();
    }catch(...) {
      if(decided)require_recovery();
      abort();throw;
    }
  }
  // Reader borrows this owned stream. Reverse destruction preserves lifetime,
  // including when a later member's construction throws.
  std::unique_ptr<std::istream> input;
  std::optional<io::EventReader> reader;
  std::optional<io::TypedQueue> queue;
  resource::AccountedUnique<WindowController> window;
  std::optional<WindowController::Prepared> window_pending;
  bool metadata_ready=false,metadata_draining=false;
  std::optional<std::uint64_t> pending_command_sequence;
  std::optional<DeltaRuntime> runtime;
  std::optional<DeltaRuntime::PendingEpoch> pending;
  std::optional<DeltaRuntime::Epoch> output;
  io::AccountedInputProgress final_progress;
  ObservationSnapshot retained_observation;
  std::optional<SessionReportMetadata> retained_report_metadata;
  std::optional<CursorObservation> retained_cursor_observation;
  workload::Options retained_workload_options;

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
  // Durable root selection can be uncertain after an I/O failure. Preserve
  // the authority-bearing file/lock owner and latch recovery_required; do not
  // treat this guard as ordinary rollback of an in-memory tentative mutation.
  struct SelectionGuard {
    Impl& session;
    ManagedGeneration& managed;
    recovery::GenerationRoot before;
    resource::AccountedUnique<ManagedGeneration>* fresh=nullptr;
    bool complete=false;
    SelectionGuard(Impl& data,ManagedGeneration& owner,resource::AccountedUnique<ManagedGeneration>* created=nullptr)
        :session(data),managed(owner),before(owner.file.selected()),fresh(created) {}
    ~SelectionGuard() {
      if(complete || (!managed.file.selection_attempted() && managed.file.selected()==before))return;
      session.require_recovery();if(fresh && *fresh)session.generation=std::move(*fresh);
    }
  };
  // Admission uses the original query cap and a finite metadata grant. No
  // FIFO assumption is accepted without the window owner's real birth history.
  static std::optional<patterns::Declaration> capture_patterns(const CompiledProgram& program,
      const std::optional<UpdatePatternOptions>& options,const WindowController* window) {
    if (!options) return {};
    require(bool(options->declaration),"invalid_update_pattern","update pattern declaration is empty");
    auto remaining=options->capture_limits;
    const auto charge=[&](std::uint64_t n) {
      if (n>remaining.work) throw patterns::Failure(patterns::Fault::work_limit);
      remaining.work-=n;
    };
    charge(64);
    require(options->declaration.matches(program),"invalid_update_pattern","update pattern belongs to another source");
    for (const auto& rule:options->declaration.rules()) {
      charge(1);
      require(!rule.fifo_scope || (window && window->manages(rule.table)),
          "unsupported_update_pattern","FIFO declarations require managed window tables with known lifetime origins");
    }
    return patterns::Declaration::copy_of(program.account(),options->declaration,remaining);
  }
  // Snapshot only committed counters and the actual owning tree. Copying the
  // immutable declaration handle allocates no rule vector; restore provenance
  // is explicit because checkpoint metadata does not authenticate past input.
  [[nodiscard]] UpdatePatternStatus pattern_status() const {
    UpdatePatternStatus out;
    if(!run_context->update_patterns)return out;
    out.declaration=*run_context->update_patterns;
    out.history=pattern_history;
    out.insertion=window?PatternInsertionPolicy::reject_lifetime_termination:PatternInsertionPolicy::reject_erase_commands;
    out.origin_sequence=pattern_origin_sequence;out.origin_command_sequence=pattern_origin_command_sequence;
    out.monitored_sequence=committed_sequence;out.completed_command_sequence=accepted_sequence();
    const auto hash=runtime->compiled_program().physical_sha256();
    std::copy(hash.begin(),hash.end(),out.physical_sha256.begin());
    out.violation=pattern_violation;
    return out;
  }
  // Cheap nonwindow policy: reject every erase command, including set no-ops,
  // before journal/native preparation. O(log R) borrowed lookup, no row copy.
  void check_pattern(const PhysicalUpdateView& update,PatternViolation& violation) const {
    if (!run_context->update_patterns || update.operation!=SetOperation::erase) return;
    const auto* rule=run_context->update_patterns->find(update.table);
    pattern_detail::require(!rule || !rule->insertion_only,PatternViolationKind::erase_command,
        update.table,update.sequence,0,&violation);
  }
  Impl(DeltaRuntime value,std::unique_ptr<std::istream> stream,std::optional<io::QueueLimits> limits,
      SessionOptions options,resource::AccountedUnique<WindowController> windows)
      :snapshot_limits(options.snapshot),input(std::move(stream)),window(std::move(windows)),runtime(std::move(value)) {
    const auto& account=runtime->compiled_program().account();
    run_context=resource::make_accounted_shared<SessionRunContext>({resource::MemoryOwnerKind::session,0},
        account,resource::MemoryPurpose::immutable_metadata,SessionRunContext{
        limits?(window?SessionInputKind::typed_window:SessionInputKind::typed_physical):SessionInputKind::owned_stream,
        io::AccountedInputOptions(account,options.input),limits,window?std::optional<AccountedWindowOptions>{window->options()}:std::nullopt,
        options.snapshot,runtime->initialization_context(),runtime->options(),runtime->mode(),runtime->completion(),
        capture_patterns(runtime->compiled_program(),options.update_patterns,window.get())});
    runtime->declare_benchmark_context(std::move(options.declared_benchmark));
    if(limits)queue.emplace(runtime->compiled_program(),window?io::QueueMode::window:io::QueueMode::physical,
        *limits,options.input.limits);
    else reader.emplace(io::EventReader::with_options(*input,runtime->compiled_program(),run_context->input));
    retain_report_metadata();
  }
  Impl(DeltaRuntime value,std::unique_ptr<std::istream> stream,const SessionCheckpoint& state,const SessionCheckpointLimits& limits)
      :control(state.state),committed_sequence(state.committed_sequence),input_failed(state.input_failed),end_of_input(state.end_of_input),
       snapshot_limits(state.snapshot),input(std::move(stream)),runtime(std::move(value)) {
    const auto check=[](bool condition) {if(!condition)throw recovery::ImageFailure(recovery::ImageFault::corrupt);};
    const auto& account=runtime->compiled_program().account();const auto& program=runtime->compiled_program();
    check(runtime->sequence()==committed_sequence);
    if(state.window)window=resource::make_accounted_unique<WindowController>({resource::MemoryOwnerKind::session,0},account,
        resource::MemoryPurpose::support_metadata,account,program.source_catalog(),*state.window,limits.window);
    io::checkpoint_detail::Budget policy_budget{limits.source};policy_budget.options(state.input_options.get());
    io::AccountedInputOptions options;
    if(control==SessionState::stopped) {
      options=io::AccountedInputOptions(account,state.input_options);
      check(std::holds_alternative<io::AccountedInputProgress>(state.source));
      const auto& progress=std::get<io::AccountedInputProgress>(state.source);
      policy_budget.positions(progress,options.get().limits);
      final_progress=io::AccountedInputProgress(account,progress);
      if(state.input_kind==SessionInputKind::owned_stream)io::EventReader::validate_checkpoint_options(program,options,final_progress);
      else check(!options.get().limits.records || final_progress.sequence<=*options.get().limits.records);
    }else if(state.input_kind==SessionInputKind::owned_stream) {
      check(std::holds_alternative<io::ReaderCheckpoint>(state.source));
      const auto& saved=std::get<io::ReaderCheckpoint>(state.source);
      reader.emplace(io::EventReader::restore_state(*input,program,saved,limits.source));
      check(state.input_options.same_values(saved.options));check(end_of_input==saved.ended);
      options=reader->native_options();
    }else {
      options=io::AccountedInputOptions(account,state.input_options);
      check(std::holds_alternative<io::QueueCheckpoint>(state.source));
      const auto& saved=std::get<io::QueueCheckpoint>(state.source);
      check(state.queue_limits && *state.queue_limits==saved.limits && options.get().limits==saved.input_limits);
      check(saved.mode==(window?io::QueueMode::window:io::QueueMode::physical));
      check(!end_of_input || saved.closed);queue.emplace(program,saved,limits.source);
    }
    const auto accepted=accepted_sequence();
    if(window) {
      const auto progress=window->progress();
      check(progress.physical_sequence==committed_sequence && progress.completed_command_sequence==accepted && !progress.active_command_sequence);
    }else check(accepted==committed_sequence);
    if(control==SessionState::created)check(accepted==0 && committed_sequence==0 && !end_of_input && !input_failed);
    run_context=resource::make_accounted_shared<SessionRunContext>({resource::MemoryOwnerKind::session,0},account,
        resource::MemoryPurpose::immutable_metadata,SessionRunContext{state.input_kind,std::move(options),state.queue_limits,
        window?std::optional<AccountedWindowOptions>{window->options()}:std::nullopt,state.snapshot,
        runtime->initialization_context(),runtime->options(),runtime->mode(),runtime->completion(),
        capture_patterns(program,state.update_patterns?std::optional<UpdatePatternOptions>{
            UpdatePatternOptions{*state.update_patterns,limits.patterns}}:std::nullopt,window.get())});
    pattern_history=PatternHistory::restored_checkpoint;
    pattern_origin_sequence=state.pattern_origin_sequence;
    pattern_origin_command_sequence=state.pattern_origin_command_sequence;
    pattern_violation=state.pattern_violation;
    retained_workload_options=runtime->workload_statistics_options();retain_observation();
  }
  [[nodiscard]] SessionCheckpoint checkpoint(const SessionCheckpointLimits&,const DeltaRuntime* replacement=nullptr) const;
  [[nodiscard]] std::shared_ptr<const SessionRunContext> replacement_context(const DeltaRuntime& target) const {
    const auto& previous=*run_context;
    require(!previous.update_patterns || previous.update_patterns->matches(target.compiled_program()),
        "invalid_update_pattern","replacement program changes the declared source");
    return resource::make_accounted_shared<SessionRunContext>({resource::MemoryOwnerKind::session,0},target.compiled_program().account(),
        resource::MemoryPurpose::immutable_metadata,SessionRunContext{previous.input_kind,previous.input,previous.queue,previous.window,
        snapshot_limits,target.initialization_context(),target.options(),target.mode(),target.completion(),previous.update_patterns});
  }
  void install_reoptimization(reoptimization::detail::State& candidate,std::shared_ptr<const SessionRunContext> context,
      recovery::journal::File log,resource::AccountedUnique<ManagedPlan> plan) noexcept {
    auto previous=std::move(runtime);runtime.emplace(candidate.take_target());run_context=std::move(context);
    journal.reset();journal.emplace(std::move(log));journal_record_limits=generation->options.journal.file.scan.record;journal_confirm();
    generation->plan=std::move(plan);last_switch_epoch=committed_sequence;retain_observation();previous.reset();
  }
  ~Impl() { drop(); }
  bool has_private() const noexcept { return pending.has_value() || window_pending.has_value(); }
  void admission_available() const {
    journal_available();
    require(control!=SessionState::dropped,"session_dropped","the query session has been dropped");
    require(control!=SessionState::stopped,"session_stopped","the query session has been stopped");
    require(control!=SessionState::paused,"session_paused","resume admission before feeding input");
    require(!reoptimization || !reoptimization->frozen(),"reoptimization_barrier","candidate barrier has frozen new input admission");
    require(queue.has_value(),"session_not_typed","this session owns a stream input");
  }
  void available(bool paused_ok=false) const {
    journal_available();
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
    return (output || recovery_output_pending() || delivery_pending())?SessionPhase::output:SessionPhase::ready;
  }
  std::uint64_t accepted_sequence() const {
    if(reader)return reader->progress().sequence;
    if(queue)return queue->progress().sequence;
    return final_progress.sequence;
  }
  io::InputProgress export_accepted() const {
    if(reader)return reader->progress().export_value();
    if(queue)return queue->progress().export_value();
    return final_progress.export_value();
  }
  void need_pending() const {
    require(has_private(),"session_no_pending_epoch","the query session has no private pending input");
  }
  void abort() noexcept {
    if (pending) { pending->rollback(); pending.reset(); }
    if(reoptimization)reoptimization->rollback_stage();
    window_pending.reset(); pending_command_sequence.reset(); metadata_ready=false; metadata_draining=false;
  }
  void retain_report_metadata() noexcept {
    if(runtime)retained_report_metadata=SessionReportMetadata(runtime->compiled_program(),runtime->options(),
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
    // Source/window preparation reserved acknowledgement storage before engine
    // work. After publication this path uses nonthrowing state changes/cleanup.
    acknowledge(); committed_sequence=sequence; pending.reset();
    if(reoptimization)reoptimization->committed(sequence);
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
  bool admitted_input() const {
    // A cached decoded stream row is already admitted, including after an
    // aborted native attempt. Inspect counters without reading another byte.
    return reader?reader->records_read()>reader->progress().sequence:queue && !queue->empty();
  }
  void prepare_update(const PhysicalUpdateView& update) {
    if(reoptimization)reoptimization->stage(*runtime,update);
    pending.emplace(runtime->begin_view(update));
  }
  SessionBegin begin(bool replay=false,bool paused_ok=false) {
    available(paused_ok);
    require(!has_private(),"session_pending_epoch","finish the private pending input before reading another event");
    if(!replay && delivery_pending()){if(local_sink->blocked_inputs<UINT64_MAX)++local_sink->blocked_inputs;return SessionBegin::would_block;}
    require(!output && (replay || !recovery_output_pending()),"session_output_pending","consume or discard committed output before reading another event");
    require(runtime->ready(),"runtime_busy","session runtime is not at a writer-ready barrier");
    require(runtime->sequence()==committed_sequence && (window || accepted_sequence()==committed_sequence),
        "invalid_sequence","session source and runtime committed progress differ");
    require(!semantic_input_failed,"input_failed","session input has failed semantic validation");
    if(reoptimization && reoptimization->frozen() && !admitted_input())return SessionBegin::would_block;
    PatternViolation observed;
    try {
      if (reader) {
        const auto* event=reader->peek();
        if (!event) { end_of_input=true; return SessionBegin::end; }
        check_pattern(event->update,observed);
        journal_input(io::InputItemView{*event});
        prepare_update(event->update);
      } else {
        const auto* item=queue->peek();
        if (!item) {
          if (!queue->closed()) return SessionBegin::would_block;
          end_of_input=true; return SessionBegin::end;
        }
        if (window) {
          const auto next=committed_sequence==std::numeric_limits<std::uint64_t>::max()
              ?committed_sequence:committed_sequence+1;
          window_pending.emplace(window->prepare_pattern_view(std::get<io::WindowCommandView>(*item),next,
              run_context->update_patterns?&*run_context->update_patterns:nullptr,&observed));
          pending_command_sequence=std::get<io::WindowCommandView>(*item).sequence;
          journal_input(*item);
          if (window_pending->update()) prepare_update(*window_pending->update());
        } else {
          const auto& update=std::get<io::InputEventView>(*item).update;
          check_pattern(update,observed);journal_input(*item);prepare_update(update);
        }
      }
      return SessionBegin::pending;
    } catch (const Error& error) {
      const auto& code=error.code();
      if (code=="update_pattern_violation" && !pattern_violation) pattern_violation=observed;
      semantic_input_failed=semantic_input_failed || code=="update_pattern_violation" || code=="invalid_window_command" ||
          code=="window_fifo_violation" || code=="late_window_event";
      input_failed=input_failed || semantic_input_failed || (reader && reader->failed()) || (queue && queue->failed());
      abort(); throw;
    } catch (...) { abort(); throw; }
  }
  void stop() noexcept {
    if (control==SessionState::stopped || control==SessionState::dropped) return;
    abort();clear_recovered_output();recovery_output_complete=false;
    if(reoptimization)reoptimization->cancel();
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
    stop(); clear_recovered_output();reoptimization.reset();window.reset(); runtime.reset();journal.reset();generation.reset();local_sink.reset();journal_confirmed.enabled=false;
    if (retained_observation.options.mode==ObservationMode::trace) {
      retained_observation.trace=TraceDisposition::released;
      retained_observation.trace_records=0;
    }
    final_progress=io::AccountedInputProgress{}; control=SessionState::dropped;
  }
};

void QuerySession::Impl::replay_frame(std::string_view frame,const recovery::journal::Scanned& after,void* context) {
  auto& replay=*static_cast<ReplayContext*>(context);auto& d=replay.data;const auto& options=replay.options;
  auto limits=options.journal.file.scan.record;limits.record.work=std::min(limits.record.work,replay.remaining);
  const auto info=recovery::journal::inspect(frame,limits);replay.remaining-=info.statistics.work;
  if(info.kind==recovery::journal::Kind::input) {
    if(info.statistics.work>replay.remaining/2)throw recovery::ImageFailure(recovery::ImageFault::work);
    replay.remaining-=2*info.statistics.work; // decode inspection plus bounded body materialization
    const auto decoded=recovery::journal::decode(d.runtime->compiled_program().account(),frame,limits);const auto view=decoded.input_view();
    auto source_limits=options.journal.native.source;source_limits.work=std::min(source_limits.work,replay.source_remaining);std::uint64_t source_work=0;
    if(d.reader) {
      if(!view.reader)throw SessionJournalFailure(SessionJournalFault::transition);
      const auto& reader=*view.reader;source_work=d.reader->stage_replay(std::get<io::InputEventView>(view.item),
          io::ReaderPositionView{reader.bytes,reader.records,reader.header_read,reader.csv_fields},source_limits);
    }else source_work=d.queue->stage_replay(view.item,source_limits);
    replay.source_remaining-=source_work;d.recovered_status.source_work=options.source_work-replay.source_remaining;
  }else if(info.kind==recovery::journal::Kind::commit) {
    if(d.begin(true)!=SessionBegin::pending)throw SessionJournalFailure(SessionJournalFault::transition);
    const auto& expected=info.commit;const bool physical=d.pending.has_value();const bool complete=!d.window_pending || d.window_pending->completes_command();
    if(physical!=(expected.kind==recovery::journal::CommitKind::physical) || complete!=expected.completes_input ||
        (physical?d.pending->sequence():d.committed_sequence)!=expected.physical_sequence ||
        (complete?(d.reader?d.reader->records_read():d.pending_command_sequence.value_or(d.accepted_sequence()+1)):d.accepted_sequence())!=expected.command_sequence)
      throw SessionJournalFailure(SessionJournalFault::transition);
    if(d.pending){while(d.pending->step()!=DeltaStep::prepared){}}else d.metadata_ready=true;
    d.finish(false);if(physical)d.collect_recovered_output(replay.header,options);
    if(d.committed_sequence!=after.physical_sequence || d.accepted_sequence()!=after.command_sequence)throw SessionJournalFailure(SessionJournalFault::transition);
  }
  d.recovered_status.records=after.records;d.recovered_status.decode_work=options.decode_work-replay.remaining;
}

QuerySession::QuerySession(resource::AccountedUnique<Impl> data) noexcept:data_(std::move(data)) {}
#ifdef CROWN_RUNTIME_TESTING
std::optional<RuntimeStorageWork> RuntimeTestProbe::index_work(const QuerySession& session) {
  auto& d=*session.data_;QuerySession::Impl::Guard guard(d);
  return d.runtime?index_work(*d.runtime):std::nullopt;
}
void RuntimeTestProbe::seed_session_physical_sequence(QuerySession& runtime,std::uint64_t sequence) {
  auto& d=*runtime.data_; QuerySession::Impl::Guard guard(d);
  require(d.window && !d.has_private() && !d.output,"invalid_probe","sequence probe needs a ready window session");
  seed_delta_sequence(*d.runtime,sequence); seed_window_sequence(*d.window,sequence); d.committed_sequence=sequence;
}
#endif
QuerySession::Owner QuerySession::create_impl(PlanSource plan,const Database* initial,std::unique_ptr<std::istream> input,
    std::optional<io::QueueLimits> limits,SessionOptions options,std::optional<WindowOptions> windows,BuildOptions build) {
  resource::AccountedUnique<WindowController> window;
  if(limits) {
    const auto& profile=options.input;
    require(profile.format==io::InputFormat::jsonl && !profile.table && profile.delimiter==',' &&
        profile.header && profile.csv_operation==SetOperation::insert && profile.relation_tokens.empty() &&
        !profile.null_token && !profile.source && profile.byte_offset==0,
        "invalid_session_options","typed input does not accept wire-format profile options");
  } else require(bool(input),"invalid_session_options","a session requires an owned input stream");
  auto runtime=std::visit([&](auto& source){return initial?DeltaRuntime::initialize(std::move(source),*initial,options.delta,build):DeltaRuntime(std::move(source),options.delta);},plan);
  const auto account=runtime.compiled_program().account();
  const resource::MemoryAttribution owner{resource::MemoryOwnerKind::session,0};
  if(windows) {
    window=resource::make_accounted_unique<WindowController>(owner,account,resource::MemoryPurpose::support_metadata,
        account,runtime.compiled_program().source_catalog(),std::move(*windows));
    if(initial)for(auto table:window->options().managed_tables) {
      require(table.value<initial->tables.size(),"invalid_database","initial database is missing a managed table");
      require(initial->tables[table.value].empty(),"invalid_window_initial_state","managed window tables must initially be empty");
    }
  }
  auto data=resource::make_accounted_unique<Impl>(owner,account,resource::MemoryPurpose::support_metadata,
      std::move(runtime),std::move(input),limits,std::move(options),std::move(window));
  resource::MemoryAllocator<QuerySession> allocator(account,resource::MemoryPurpose::support_metadata,owner);
  auto* facade=allocator.allocate(1);
  ::new(static_cast<void*>(facade))QuerySession(std::move(data));
  return Owner(facade,resource::MemoryDelete<QuerySession>(allocator));
}
QuerySession::Owner QuerySession::create(PhysicalPlan plan,std::unique_ptr<std::istream> input,SessionOptions options) {
  return create_impl(std::move(plan),nullptr,std::move(input),{},std::move(options),{},{});
}
QuerySession::Owner QuerySession::create(PhysicalPlan plan,const Database& initial,
    std::unique_ptr<std::istream> input,SessionOptions options,BuildOptions build) {
  return create_impl(std::move(plan),&initial,std::move(input),{},std::move(options),{},build);
}
QuerySession::Owner QuerySession::create_typed(PhysicalPlan plan,io::QueueLimits limits,SessionOptions options) {
  return create_impl(std::move(plan),nullptr,{},limits,std::move(options),{},{});
}
QuerySession::Owner QuerySession::create_typed(PhysicalPlan plan,const Database& initial,
    io::QueueLimits limits,SessionOptions options,BuildOptions build) {
  return create_impl(std::move(plan),&initial,{},limits,std::move(options),{},build);
}
QuerySession::Owner QuerySession::create_windowed(PhysicalPlan plan,WindowOptions window,
    io::QueueLimits limits,SessionOptions options) {
  return create_impl(std::move(plan),nullptr,{},limits,std::move(options),std::move(window),{});
}
QuerySession::Owner QuerySession::create_windowed(PhysicalPlan plan,const Database& initial,
    WindowOptions window,io::QueueLimits limits,SessionOptions options,BuildOptions build) {
  return create_impl(std::move(plan),&initial,{},limits,std::move(options),std::move(window),build);
}
QuerySession::Owner QuerySession::create(CompiledProgram plan,std::unique_ptr<std::istream> input,SessionOptions options) {
  return create_impl(std::move(plan),nullptr,std::move(input),{},std::move(options),{},{});
}
QuerySession::Owner QuerySession::create(CompiledProgram plan,const Database& initial,
    std::unique_ptr<std::istream> input,SessionOptions options,BuildOptions build) {
  return create_impl(std::move(plan),&initial,std::move(input),{},std::move(options),{},build);
}
QuerySession::Owner QuerySession::create_typed(CompiledProgram plan,io::QueueLimits limits,SessionOptions options) {
  return create_impl(std::move(plan),nullptr,{},limits,std::move(options),{},{});
}
QuerySession::Owner QuerySession::create_typed(CompiledProgram plan,const Database& initial,
    io::QueueLimits limits,SessionOptions options,BuildOptions build) {
  return create_impl(std::move(plan),&initial,{},limits,std::move(options),{},build);
}
QuerySession::Owner QuerySession::create_windowed(CompiledProgram plan,WindowOptions window,io::QueueLimits limits,SessionOptions options) {
  return create_impl(std::move(plan),nullptr,{},limits,std::move(options),std::move(window),{});
}
QuerySession::Owner QuerySession::create_windowed(CompiledProgram plan,const Database& initial,
    WindowOptions window,io::QueueLimits limits,SessionOptions options,BuildOptions build) {
  return create_impl(std::move(plan),&initial,{},limits,std::move(options),std::move(window),build);
}
QuerySession::~QuerySession() {
  // Exclusive lifetime is required. Keep Impl alive and reentrancy blocked
  // through owned stream destruction; never call a throwing public guard here.
  data_->busy=true; data_->drop();
}
void QuerySession::enable_journal(std::string_view checkpoint_path,std::string_view journal_path,const SessionJournalOptions& options) {
  auto& d=*data_;Impl::Guard guard(d);d.journal_available();
  if(d.journal || d.control==SessionState::stopped || d.control==SessionState::dropped || d.input_failed || d.end_of_input)
    throw SessionJournalFailure(SessionJournalFault::state);
  auto captured=d.checkpoint(options.native);const auto& account=d.runtime->compiled_program().account();
  const auto current=recovery::encode_session_image(account,captured,options.native,options.checkpoint.image);
  recovery::detail::SessionFileReader checkpoint(checkpoint_path,options.checkpoint);const auto stored=checkpoint.read(account);
  if(stored!=current.bytes)throw SessionJournalFailure(SessionJournalFault::checkpoint);
  recovery::journal::Header header;header.query_id=options.query_id;header.generation=options.generation;
  header.binding=current.manifest.runtime_manifest.binding;header.checkpoint_sha256=sha256_fixed({stored.data(),stored.size()});
  header.physical_sequence=d.committed_sequence;header.command_sequence=d.accepted_sequence();
  header.input_kind=d.reader?recovery::journal::InputKind::stream:d.window?recovery::journal::InputKind::window:recovery::journal::InputKind::physical;
  d.journal.emplace(recovery::journal::File::create(account,journal_path,header,options.file));
  d.journal_record_limits=options.file.scan.record;d.journal_confirm();
}
SessionJournalState QuerySession::journal_state() const {
  auto& d=*data_;Impl::Guard guard(d);return d.journal_confirmed;
}
QuerySession::Owner QuerySession::restore_journal(CompiledProgram program,std::string_view checkpoint_path,std::string_view journal_path,
    const SessionJournalRecoveryOptions& requested,std::unique_ptr<std::istream> continuation) {
  return restore_journal_selected(std::move(program),checkpoint_path,journal_path,requested,std::move(continuation),nullptr);
}
QuerySession::Owner QuerySession::restore_journal_with_local_sink(CompiledProgram program,std::string_view checkpoint_path,std::string_view journal_path,
    const SessionJournalRecoveryOptions& requested,std::string_view sink_path,const SessionLocalSinkOptions& sink_options,std::unique_ptr<std::istream> continuation) {
  return restore_journal_selected(std::move(program),checkpoint_path,journal_path,requested,std::move(continuation),nullptr,sink_path,&sink_options);
}
QuerySession::Owner QuerySession::restore_journal_selected(CompiledProgram program,std::string_view checkpoint_path,std::string_view journal_path,
    const SessionJournalRecoveryOptions& requested,std::unique_ptr<std::istream> continuation,const recovery::GenerationRoot* selected,
    std::string_view sink_path,const SessionLocalSinkOptions* requested_sink,const recovery::detail::GenerationOwner* retirement_owner,
    std::shared_ptr<detail::StorageWorkContext> funded_context,const recovery::sink::Header* sink_origin,const recovery::ImageBinding* expected_binding) {
  static_assert(std::is_trivially_copy_constructible_v<SessionJournalRecoveryOptions>);
  static_assert(std::is_trivially_copy_constructible_v<SessionLocalSinkOptions>);
  const auto options=requested;
  const auto sink_options=requested_sink?std::optional<SessionLocalSinkOptions>{*requested_sink}:std::nullopt;
  require(!sink_options || !options.outputs_after_physical_sequence,"partial_epoch_output","sink-aware recovery requires actual durable output coverage");
  SessionRestoreOptions native;native.build=options.build;native.limits=options.journal.native;native.memory_limit_bytes=options.memory_limit_bytes;
  recovery::detail::SessionFileReader checkpoint(checkpoint_path,options.journal.checkpoint);
  const auto cap=options.memory_limit_bytes.value_or(checkpoint.memory_limit_bytes());
  auto context=funded_context?std::move(funded_context):detail::new_storage_context(program,cap);
  generation_binding(context->memory().statistics().limit_bytes==cap);const auto bytes=checkpoint.read(context->memory());
  const auto validated=recovery::detail::validate_session_image({bytes.data(),bytes.size()},native.limits,options.journal.checkpoint.image);
  const auto& manifest=validated.inspected.manifest;
  if(expected_binding)generation_binding(manifest.runtime_manifest.binding==*expected_binding);
  if(selected && (selected->checkpoint_sha256!=sha256_fixed({bytes.data(),bytes.size()}) ||
      selected->physical_sequence!=manifest.committed_sequence || selected->command_sequence!=manifest.accepted_sequence))
    throw recovery::GenerationFailure(recovery::GenerationFault::binding,recovery::GenerationStage::read_data,recovery::GenerationOutcome::unchanged);
  if(manifest.state==SessionState::stopped || manifest.input_failed || manifest.end_of_input)throw SessionJournalFailure(SessionJournalFault::checkpoint);
  auto decoded=recovery::detail::materialize_session_image(context->memory(),validated);
  auto result=restore_funded(std::move(program),decoded.state,native,std::move(continuation),context,decoded.runtime_bytes);auto& d=*result->data_;Impl::Guard guard(d);
  if(expected_binding)generation_binding(d.runtime->checkpoint_binding()==*expected_binding);
  recovery::journal::Header header;header.query_id=options.journal.query_id;header.generation=options.journal.generation;header.binding=manifest.runtime_manifest.binding;
  header.checkpoint_sha256=sha256_fixed({bytes.data(),bytes.size()});header.physical_sequence=manifest.committed_sequence;header.command_sequence=manifest.accepted_sequence;
  header.input_kind=d.reader?recovery::journal::InputKind::stream:d.window?recovery::journal::InputKind::window:recovery::journal::InputKind::physical;
  if(sink_options) {
    d.prepare_local_sink(header,*sink_options,true);auto& sink=*d.local_sink;
    if(sink_origin) {
      generation_binding(sink_origin->query_id==header.query_id && sink_origin->sink_id==sink_options->sink_id &&
          logical_binding(sink_origin->binding,header.binding) && sink_origin->fields==sink.schema.size() &&
          sink_origin->schema_sha256==recovery::sink::schema_sha256(context->memory(),sink.schema));
      sink.header=*sink_origin;
    }
    auto file=recovery::sink::File::open(context->memory(),sink_path,sink.header,sink.schema,sink_options->file,
        sink_origin?recovery::sink::HeaderMatch::exact:recovery::sink::HeaderMatch::identity);
    const auto state=file.state();require(state.header.base_sequence<=header.physical_sequence && state.header.first_generation<=header.generation &&
        state.sequence>=header.physical_sequence && state.generation<=header.generation,"local_sink_binding","sink does not cover the selected checkpoint");
    require(!state.torn_tail || sink_options->repair_torn_tail,"local_sink_tail","local sink has an incomplete tail");
    d.establish_sink_prefix(file,header,selected?selected->delivery:std::nullopt);
    sink.header=state.header;sink.file.emplace(std::move(file));
  }
  d.control=SessionState::running;Impl::ReplayContext replay{d,options,header,options.decode_work,options.source_work};
  auto file=recovery::journal::File::open_replay(context->memory(),journal_path,header,options.journal.file,Impl::replay_frame,&replay);
  const auto state=file.state();if(state.pending) {
    d.recovered_status.pending_input_sequence=state.pending->input.sequence;
    if(d.queue) {
      const auto* item=d.queue->peek();if(!item)throw SessionJournalFailure(SessionJournalFault::transition);
      if(d.window){const auto next=d.committed_sequence==UINT64_MAX?UINT64_MAX:d.committed_sequence+1;auto prepared=d.window->prepare_view(std::get<io::WindowCommandView>(*item),next);}
    }
  }
  if(d.reader) {
    const auto position=d.reader->decoder_position();d.recovered_status.reader_bytes=position.bytes;d.recovered_status.reader_records=position.records;
    if(options.seek_source_from_origin) {
      if(position.bytes>static_cast<std::uint64_t>(std::numeric_limits<std::streamoff>::max()) || d.input->bad())throw SessionJournalFailure(SessionJournalFault::continuation);
      try{d.input->clear();d.input->seekg(static_cast<std::streamoff>(position.bytes),std::ios::beg);}catch(const std::ios_base::failure&){throw SessionJournalFailure(SessionJournalFault::continuation);}
      if(!*d.input)throw SessionJournalFailure(SessionJournalFault::continuation);
    }
  }else if(options.seek_source_from_origin)throw SessionJournalFailure(SessionJournalFault::continuation);
  if(d.local_sink) {
    auto& sink=*d.local_sink;const auto persisted=sink.file->state();
    require(persisted.sequence<=d.committed_sequence && sink.verified_sequence==persisted.sequence,"local_sink_binding","sink is ahead of the validated native journal");
    sink.replaying=sink.verified_sequence<d.committed_sequence;
    if(retirement_owner)retirement_owner->validate_retirement(*sink.file);
  }
  if(state.torn_tail && !options.repair_torn_tail)throw SessionJournalFailure(SessionJournalFault::tail);
  // Replay is still private. Repair either tail only after complete native,
  // source and sink checks; no public owner or output has escaped.
  if(state.torn_tail)file.repair_tail();
  if(d.local_sink && d.local_sink->file->state().torn_tail)d.local_sink->file->repair_tail();
  d.journal.emplace(std::move(file));d.journal_record_limits=options.journal.file.scan.record;d.journal_confirm();d.control=SessionState::paused;d.end_of_input=false;
  d.recovery_output_complete=!options.outputs_after_physical_sequence.has_value();d.recovery_end_sequence=d.committed_sequence;
  return result;
}
SessionJournalRecoveryStatus QuerySession::recovery_status() const {
  auto& d=*data_;Impl::Guard guard(d);auto status=d.recovered_status;
  if(d.recovered_output){status.output_remaining=d.recovered_output->rows.size()-d.recovered_output->position;status.output_bytes=static_cast<std::size_t>(d.recovered_output->retained_bytes());}
  return status;
}
std::optional<RecoveredResult> QuerySession::next_recovered_output() {
  auto& d=*data_;Impl::Guard guard(d);d.available(true);require(!d.has_private(),"session_pending_epoch","finish private work before output");
  require(!d.local_sink,"local_sink_attached","deliver whole epochs through the attached local sink");
  if(!d.recovery_output_pending())return {};
  d.recovery_output_complete=false;
  auto& buffer=*d.recovered_output;std::optional<RecoveredResult> value{std::move(buffer.rows[buffer.position++])};buffer.payload_bytes-=value->value.tuple.memory_usage().requested_bytes;
  if(!d.recovery_output_pending()){d.clear_recovered_output();}
  return value;
}
void QuerySession::discard_recovered_output() {auto& d=*data_;Impl::Guard guard(d);d.available(true);require(!d.local_sink,"local_sink_attached","attached local delivery cannot be discarded");d.recovery_output_complete=false;d.clear_recovered_output();}

void QuerySession::create_local_sink(std::string_view path,const SessionLocalSinkOptions& options) {local_sink_impl(path,options,true);}
void QuerySession::open_local_sink(std::string_view path,const SessionLocalSinkOptions& options) {local_sink_impl(path,options,false);}
void QuerySession::local_sink_impl(std::string_view path,const SessionLocalSinkOptions& requested,bool create) {
  const auto options=requested;auto& d=*data_;Impl::Guard guard(d);d.journal_available();
  require(d.journal && d.runtime && d.control!=SessionState::stopped && d.control!=SessionState::dropped && !d.has_private(),"local_sink_state","local sink requires a healthy journaled committed session");
  const auto journal=d.journal->state().header;const auto& account=d.runtime->compiled_program().account();
  if(create)require((!d.local_sink || (d.local_sink->failed && !d.local_sink->file)) && !d.output && !d.recovery_output_pending() && d.committed_sequence==journal.physical_sequence,"local_sink_state","create the local sink at its journal checkpoint boundary");
  if(create)require(!d.generation || !d.generation->file.selected().delivery,"local_sink_binding","the selected checkpoint already binds a durable sink prefix");
  else if(!d.local_sink)require(d.committed_sequence==journal.physical_sequence || (d.recovered_status.records && d.recovery_output_complete && d.recovery_end_sequence==d.committed_sequence),
      "partial_epoch_output","opening a sink requires complete unconsumed replay coverage");
  if(!d.local_sink) {
    d.prepare_local_sink(journal,options,!create && d.committed_sequence>journal.physical_sequence);
    if(d.generation && d.generation->plan && d.generation->plan->selection.sink_origin) {
      generation_binding(!create && options.sink_id==d.generation->plan->selection.sink_origin->sink_id);
      d.local_sink->header=*d.generation->plan->selection.sink_origin;
    }
  }else require((!create || (d.local_sink->failed && !d.local_sink->file)) && d.local_sink->header.sink_id==options.sink_id,"local_sink_state","reopen the same bound sink identity");
  auto& sink=*d.local_sink;const bool known_origin=d.generation && d.generation->plan && d.generation->plan->selection.sink_origin;
  const bool discover=!known_origin && !sink.file.has_value() && sink.header.base_sequence==journal.physical_sequence && sink.verified_sequence==journal.physical_sequence;
  sink.file.reset();sink.failed=true;
  auto file=create?recovery::sink::File::create(account,path,sink.header,sink.schema,options.file):
      recovery::sink::File::open(account,path,sink.header,sink.schema,options.file,discover?recovery::sink::HeaderMatch::identity:recovery::sink::HeaderMatch::exact);
  const auto state=file.state();require(state.header.base_sequence<=journal.physical_sequence && state.header.first_generation<=journal.generation &&
      state.sequence>=journal.physical_sequence && state.sequence<=d.committed_sequence && state.generation<=journal.generation,"local_sink_binding","sink coverage does not match the native journal boundary");
  d.establish_sink_prefix(file,journal,d.generation?d.generation->file.selected().delivery:std::nullopt);
  if(state.torn_tail){require(options.repair_torn_tail,"local_sink_tail","local sink has an incomplete tail");file.repair_tail();}
  sink.header=state.header;sink.options=options;sink.file.emplace(std::move(file));sink.failed=false;
}
SessionLocalSinkState QuerySession::local_sink_state() const {
  auto& d=*data_;Impl::Guard guard(d);if(!d.local_sink)return {};const auto& sink=*d.local_sink;
  recovery::sink::State persisted;persisted.header=sink.header;persisted.sequence=sink.header.base_sequence;persisted.generation=sink.header.first_generation;
  if(sink.file)persisted=sink.file->state();
  return {true,sink.failed || !sink.file || persisted.recovery_required,sink.replaying,sink.verified_sequence,sink.delivery_work,sink.blocked_inputs,persisted,sink.verified_prefix.has_value()};
}
LocalDelivery QuerySession::deliver_local_epoch() {
  auto& d=*data_;Impl::Guard guard(d);d.available(true);require(d.local_sink && d.local_sink->file && !d.local_sink->failed && !d.has_private(),"local_sink_state","local delivery requires a healthy sink and committed output");
  auto& sink=*d.local_sink;if(sink.verified_sequence==d.committed_sequence)return {};
  const auto charge=[&](std::uint64_t count){if(sink.delivery_work>sink.options.delivery_work || count>sink.options.delivery_work-sink.delivery_work)throw recovery::ImageFailure(recovery::ImageFault::work);sink.delivery_work+=count;};charge(1);
  require(sink.verified_sequence<d.committed_sequence,"local_sink_binding","local sink is ahead of committed state");const auto sequence=sink.verified_sequence+1;
  const auto generation=d.journal->state().header.generation;recovery::ImageVector<recovery::sink::RowView> rows(recovery::image_allocator<recovery::sink::RowView>(d.runtime->compiled_program().account()));
  std::size_t end=0;
  if(sink.replaying) {
    require(d.recovery_output_complete && d.recovery_end_sequence==d.committed_sequence,"partial_epoch_output","replay output coverage was consumed or discarded");
    if(d.recovered_output) {
      auto& buffer=*d.recovered_output;end=buffer.position;
      while(end<buffer.rows.size() && buffer.rows[end].physical_sequence==sequence){charge(1);require(rows.size()<sink.options.file.record.rows,"resource_limit","sink row limit exceeded");const auto& value=buffer.rows[end];require(value.generation==generation,"local_sink_binding","replayed generation differs");rows.push_back({value.value.operation,value.value.tuple.values()});++end;}
      require(end==buffer.rows.size() || buffer.rows[end].physical_sequence>sequence,"local_sink_binding","replayed output is out of physical order");
    }
  }else {
    require(sequence==d.committed_sequence,"local_sink_binding","live delivery skipped an epoch");
    if(d.output) {
      const auto count=d.output->remaining();require(count<=sink.options.file.record.rows,"resource_limit","sink row limit exceeded");charge(count);rows.reserve(count);
      d.output->visit_complete([](const SignedResult& value,void* context){auto& values=*static_cast<recovery::ImageVector<recovery::sink::RowView>*>(context);values.push_back({value.operation,value.tuple.values()});},&rows);
    }
  }
  bool published=false;
  try{published=sink.file->append(generation,sequence,rows);}catch(const recovery::sink::Failure&){sink.failed=true;throw;}
  if(sink.replaying && d.recovered_output) {
    auto& buffer=*d.recovered_output;
    while(buffer.position<end){auto released=std::move(buffer.rows[buffer.position++]);buffer.payload_bytes-=released.value.tuple.memory_usage().requested_bytes;}
    if(!d.recovery_output_pending())d.clear_recovered_output();
  }else if(d.output){d.output->acknowledge_complete();d.retain_observation();d.output.reset();}
  d.advance_sink_prefix(sequence);sink.verified_sequence=sequence;if(sequence==d.committed_sequence)sink.replaying=false;
  return {published?LocalDeliveryKind::published:LocalDeliveryKind::duplicate,generation,sequence,rows.size()};
}
recovery::sink::Epoch QuerySession::read_local_epoch(std::uint64_t sequence) {
  auto& d=*data_;Impl::Guard guard(d);d.available(true);require(d.local_sink && d.local_sink->file && !d.local_sink->failed,"local_sink_state","local sink is unavailable");
  try{return d.local_sink->file->read_epoch(sequence);}catch(const recovery::sink::Failure&){d.local_sink->failed=true;throw;}
}
recovery::sink::Receipt QuerySession::local_sink_receipt() const {
  auto& d=*data_;Impl::Guard guard(d);d.journal_available();require(d.local_sink && d.local_sink->file && !d.local_sink->failed && !d.delivery_pending() && !d.has_private(),"local_sink_state","delivery is not verified through the committed boundary");return d.local_sink->file->receipt();
}

void QuerySession::enable_generation(std::string_view root_path,const SessionGenerationOptions& requested) {
  const auto options=requested;auto& d=*data_;Impl::Guard guard(d);d.journal_available();
  if(d.journal || d.generation || d.control==SessionState::stopped || d.control==SessionState::dropped || d.input_failed || d.end_of_input ||
      options.retained_generations==0 || options.journal.generation==0)throw SessionJournalFailure(SessionJournalFault::state);
  auto captured=d.checkpoint(options.journal.native);const auto& account=d.runtime->compiled_program().account();
  const auto image=recovery::encode_session_image(account,captured,options.journal.native,options.journal.checkpoint.image);
  recovery::detail::GenerationOwner owner(root_path,options.journal.query_id,true,options.root);
  auto managed=resource::make_accounted_unique<ManagedGeneration>(recovery::image_owner,account,resource::MemoryPurpose::recovery_log,std::move(owner),options);
  const auto generation=options.journal.generation;const auto log_path=managed->file.journal_path(generation);
  const auto checkpoint_path=managed->file.checkpoint_path(generation);generation_checkpoint_policy(checkpoint_path.data(),options.journal.checkpoint);
  recovery::journal::Header header;header.query_id=options.journal.query_id;header.generation=generation;
  header.binding=image.manifest.runtime_manifest.binding;header.checkpoint_sha256=sha256_fixed({image.bytes.data(),image.bytes.size()});
  header.physical_sequence=d.committed_sequence;header.command_sequence=d.accepted_sequence();
  header.input_kind=d.reader?recovery::journal::InputKind::stream:d.window?recovery::journal::InputKind::window:recovery::journal::InputKind::physical;
  try {
    managed->file.publish_checkpoint(generation,{image.bytes.data(),image.bytes.size()});
    auto file=recovery::journal::File::create(account,log_path.data(),header,options.journal.file);
    managed->file.publish_root({header.query_id,generation,generation,header.checkpoint_sha256,header.physical_sequence,header.command_sequence});
    d.journal.emplace(std::move(file));d.journal_record_limits=options.journal.file.scan.record;d.journal_confirm();d.generation=std::move(managed);
  }catch(const recovery::GenerationFailure&) {
    d.require_recovery();d.generation=std::move(managed);throw;
  }catch(const recovery::journal::FileFailure&) {
    d.require_recovery();d.generation=std::move(managed);throw;
  }catch(...) {
    if(managed->file.selection_attempted()){d.require_recovery();d.generation=std::move(managed);}
    throw;
  }
}
void QuerySession::promote_journal(std::string_view root_path,const SessionGenerationOptions& requested) {
  const auto options=requested;auto& d=*data_;Impl::Guard guard(d);d.journal_available();
  require(d.journal && !d.generation && d.runtime && d.control!=SessionState::stopped && d.control!=SessionState::dropped &&
      !d.input_failed && !d.end_of_input && (!d.reader || !d.reader->failed()) && (!d.queue || !d.queue->failed()) &&
      !d.journal->state().pending && !d.admitted_input() && options.retained_generations>0,
      "generation_promotion_state","promotion requires a healthy journal and a complete input boundary");
  const auto previous=d.journal->state().header;
  generation_binding(previous.query_id==options.journal.query_id && previous.generation<UINT64_MAX);
  require(!d.local_sink || d.local_sink->verified_prefix.has_value(),"local_sink_unverified","promotion requires authenticated sink coverage");
  auto captured=d.checkpoint(options.journal.native);const auto& account=d.runtime->compiled_program().account();
  const auto image=recovery::encode_session_image(account,captured,options.journal.native,options.journal.checkpoint.image);
  recovery::detail::GenerationOwner owner(root_path,previous.query_id,true,options.root);
  auto managed=resource::make_accounted_unique<ManagedGeneration>(recovery::image_owner,account,resource::MemoryPurpose::recovery_log,std::move(owner),options);
  const auto next=previous.generation+1;const auto log_path=managed->file.journal_path(next),checkpoint_path=managed->file.checkpoint_path(next);
  generation_checkpoint_policy(checkpoint_path.data(),options.journal.checkpoint);
  auto header=previous;header.generation=next;header.binding=image.manifest.runtime_manifest.binding;
  header.checkpoint_sha256=sha256_fixed({image.bytes.data(),image.bytes.size()});header.physical_sequence=d.committed_sequence;header.command_sequence=d.accepted_sequence();
  Impl::SelectionGuard selection_guard(d,*managed,&managed);
  managed->file.publish_checkpoint(next,{image.bytes.data(),image.bytes.size()});
  auto log=recovery::journal::File::create(account,log_path.data(),header,options.journal.file);
  managed->file.publish_root({header.query_id,next,next,header.checkpoint_sha256,header.physical_sequence,header.command_sequence,
      d.local_sink?d.local_sink->verified_prefix:std::nullopt});
  d.journal.reset();d.journal.emplace(std::move(log));d.journal_record_limits=options.journal.file.scan.record;d.journal_confirm();
  d.generation=std::move(managed);selection_guard.complete=true;
}
void QuerySession::rotate_generation() {
  auto& d=*data_;Impl::Guard guard(d);d.journal_available();
  if(!d.generation || !d.journal || d.control==SessionState::stopped || d.control==SessionState::dropped || d.input_failed || d.end_of_input ||
      d.journal->state().pending)throw SessionJournalFailure(SessionJournalFault::state);
  auto& managed=*d.generation;const auto before=managed.file.selected();const auto& options=managed.options;
  require(!d.local_sink || d.local_sink->verified_prefix.has_value(),"local_sink_unverified","rotation with a sink requires authenticated checkpoint-prefix coverage");
  if(before.generation==UINT64_MAX || before.generation-before.first_generation>=options.retained_generations-1)
    throw recovery::GenerationFailure(recovery::GenerationFault::limit,recovery::GenerationStage::state,recovery::GenerationOutcome::unchanged);
  auto captured=d.checkpoint(options.journal.native);const auto& account=d.runtime->compiled_program().account();
  const auto image=recovery::encode_session_image(account,captured,options.journal.native,options.journal.checkpoint.image);
  const auto next=before.generation+1;const auto log_path=managed.file.journal_path(next);
  const auto checkpoint_path=managed.file.checkpoint_path(next);generation_checkpoint_policy(checkpoint_path.data(),options.journal.checkpoint);
  recovery::journal::Header header;header.query_id=before.query_id;header.generation=next;header.binding=image.manifest.runtime_manifest.binding;
  header.checkpoint_sha256=sha256_fixed({image.bytes.data(),image.bytes.size()});header.physical_sequence=d.committed_sequence;header.command_sequence=d.accepted_sequence();
  header.input_kind=d.reader?recovery::journal::InputKind::stream:d.window?recovery::journal::InputKind::window:recovery::journal::InputKind::physical;
  resource::AccountedUnique<ManagedPlan> plan;
  if(managed.plan) {
    generation_binding(managed.plan->selection.target==header.binding);
    recovery::PlanSelection selection{before,header.binding,header.binding,next,header.physical_sequence,header.command_sequence,
        d.local_sink?std::optional<recovery::sink::Header>{d.local_sink->header}:managed.plan->selection.sink_origin,d.last_switch_epoch};
    auto encoded=recovery::encode_plan_descriptor(account,selection,managed.plan->artifact(),options.descriptor);
    plan=resource::make_accounted_unique<ManagedPlan>(recovery::image_owner,account,resource::MemoryPurpose::recovery_log,
        std::move(encoded),selection,managed.plan->artifact_size);
  }
  recovery::GenerationRoot selected{header.query_id,next,before.first_generation,header.checkpoint_sha256,header.physical_sequence,header.command_sequence,
      d.local_sink?d.local_sink->verified_prefix:std::nullopt,plan?std::optional<std::array<char,64>>{sha256_fixed(plan->bytes())}:std::nullopt};
  Impl::SelectionGuard selection_guard(d,managed);
  managed.file.prepare_next(next);if(plan)managed.file.publish_plan(next,plan->bytes());
  managed.file.publish_checkpoint(next,{image.bytes.data(),image.bytes.size()});
  auto file=recovery::journal::File::create(account,log_path.data(),header,options.journal.file);
  managed.file.publish_root(selected);
  d.journal.reset();d.journal.emplace(std::move(file));d.journal_record_limits=options.journal.file.scan.record;d.journal_confirm();
  managed.plan=std::move(plan);selection_guard.complete=true;
}
void QuerySession::retire_generation_history() {
  auto& d=*data_;Impl::Guard guard(d);d.journal_available();
  require(d.generation && d.journal && d.runtime && d.control!=SessionState::stopped && d.control!=SessionState::dropped &&
      !d.has_private() && !d.output && !d.recovery_output_pending() && !d.delivery_pending() && !d.journal->state().pending,
      "generation_retirement_state","retirement requires a healthy quiescent generation and verified local delivery");
  require(d.local_sink && d.local_sink->file && !d.local_sink->failed,"generation_retirement_sink","retirement requires the attached durable local sink");
  require(d.local_sink->verified_prefix.has_value(),"generation_retirement_sink","the pre-checkpoint sink prefix has no native delivery anchor");
  const auto receipt=d.local_sink->file->receipt();const auto& managed=*d.generation;const auto selected=managed.file.selected();
  const auto binding=d.journal->state().header.binding;
  const bool lineage=managed.plan && managed.plan->selection.target==binding && managed.plan->selection.sink_origin &&
      *managed.plan->selection.sink_origin==receipt.header() && selected.plan_sha256 && *selected.plan_sha256==sha256_fixed(managed.plan->bytes());
  require(receipt.sequence()==d.local_sink->verified_sequence && receipt.sequence()==d.committed_sequence &&
      (receipt.header().binding==binding || lineage) && receipt.bytes()==d.local_sink->verified_prefix->bytes &&
      receipt.content_sha256()==d.local_sink->verified_prefix->content_sha256,"generation_retirement_sink","delivery has not verified the native boundary");
  const auto& options=managed.options;const auto checkpoint_path=managed.file.checkpoint_path(selected.generation);
  recovery::detail::SessionFileReader checkpoint(checkpoint_path.data(),options.journal.checkpoint);
  const auto bytes=checkpoint.read(d.runtime->compiled_program().account());
  const auto inspected=recovery::detail::validate_session_image({bytes.data(),bytes.size()},options.journal.native,options.journal.checkpoint.image);
  require(inspected.inspected.manifest.committed_sequence==selected.physical_sequence &&
      inspected.inspected.manifest.accepted_sequence==selected.command_sequence &&
      inspected.inspected.manifest.runtime_manifest.binding==d.journal->state().header.binding,"generation_retirement_checkpoint","selected native checkpoint binding differs");
  try{d.generation->file.retire_history(receipt,{bytes.data(),bytes.size()},d.runtime->compiled_program().account());}
  catch(const recovery::GenerationFailure&){d.require_recovery();throw;}
}
SessionGenerationState QuerySession::generation_state() const {
  auto& d=*data_;Impl::Guard guard(d);if(!d.generation)return {};
  const auto& file=d.generation->file;const auto& intent=file.retirement();
  return {true,d.journal_confirmed.recovery_required,file.selected(),file.operations(),file.validation_work(),intent.has_value(),intent?intent->before.first_generation:0,intent?intent->before.generation:0};
}
QuerySession::Owner QuerySession::restore_generation(CompiledProgram program,std::string_view root_path,
    const SessionGenerationRecoveryOptions& requested,std::unique_ptr<std::istream> continuation) {
  return restore_generation_impl(std::move(program),root_path,requested,std::move(continuation),{},nullptr);
}
QuerySession::Owner QuerySession::restore_generation_with_local_sink(CompiledProgram program,std::string_view root_path,
    const SessionGenerationRecoveryOptions& requested,std::string_view sink_path,const SessionLocalSinkOptions& sink_options,std::unique_ptr<std::istream> continuation) {
  return restore_generation_impl(std::move(program),root_path,requested,std::move(continuation),sink_path,&sink_options);
}
QuerySession::Owner QuerySession::restore_generation_impl(CompiledProgram program,std::string_view root_path,
    const SessionGenerationRecoveryOptions& requested,std::unique_ptr<std::istream> continuation,std::string_view sink_path,const SessionLocalSinkOptions* requested_sink) {
  static_assert(std::is_trivially_copy_constructible_v<SessionGenerationRecoveryOptions>);const auto options=requested;
  const auto sink_options=requested_sink?std::optional<SessionLocalSinkOptions>{*requested_sink}:std::nullopt;
  if(options.retained_generations==0)throw SessionJournalFailure(SessionJournalFault::state);
  recovery::detail::GenerationOwner owner(root_path,options.replay.journal.query_id,false,options.root);const auto selected=owner.selected();
  // v3 needs descriptor-aware admission and immutable sink-origin lineage.
  // A caller-selected compiled plan cannot bypass that recovery boundary.
  if(selected.plan_sha256)throw recovery::GenerationFailure(recovery::GenerationFault::binding,recovery::GenerationStage::state,recovery::GenerationOutcome::unchanged);
  if(selected.generation-selected.first_generation>=options.retained_generations)
    throw recovery::GenerationFailure(recovery::GenerationFault::limit,recovery::GenerationStage::state,recovery::GenerationOutcome::unchanged);
  if(owner.retirement()) {
    if(!sink_options)throw recovery::GenerationFailure(recovery::GenerationFault::state,recovery::GenerationStage::state,recovery::GenerationOutcome::unchanged);
    if(owner.retirement()->before.generation-owner.retirement()->before.first_generation>=options.retained_generations)
      throw recovery::GenerationFailure(recovery::GenerationFault::limit,recovery::GenerationStage::state,recovery::GenerationOutcome::unchanged);
  }
  const auto checkpoint=owner.checkpoint_path(selected.generation),log=owner.journal_path(selected.generation);
  auto replay=options.replay;replay.journal.generation=selected.generation;
  SessionGenerationOptions policy;policy.journal=replay.journal;policy.root=options.root;policy.retained_generations=options.retained_generations;
  recovery::detail::SessionFileReader image(checkpoint.data(),replay.journal.checkpoint);
  auto context=detail::new_storage_context(program,replay.memory_limit_bytes.value_or(image.memory_limit_bytes()));
  // Admission phase: fund the final holder while preserving the original
  // root lock. Replay may repair validated incomplete WAL/sink tails afterward;
  // installing this holder below is a nonthrowing move, not another allocation.
  auto managed=resource::make_accounted_unique<ManagedGeneration>(recovery::image_owner,context->memory(),resource::MemoryPurpose::recovery_log,std::move(owner),policy);
  auto result=restore_journal_selected(std::move(program),checkpoint.data(),log.data(),replay,std::move(continuation),&selected,sink_path,
      sink_options?&*sink_options:nullptr,&managed->file,std::move(context));auto& d=*result->data_;
  d.generation=std::move(managed);
  if(d.generation->file.retirement())result->retire_generation_history();
  return result;
}

LockedGenerationRecovery::Owner QuerySession::lock_generation_recovery(CompiledProgram expected,std::string_view root_path,
    const SessionGenerationRecoveryOptions& options) {
  require(bool(expected) && options.retained_generations>0,"generation_recovery_source","supply the expected admitted source and a retained-generation grant");
  recovery::detail::GenerationOwner owner(root_path,options.replay.journal.query_id,false,options.root);const auto selected=owner.selected();
  generation_binding(selected.generation-selected.first_generation<options.retained_generations);
  if(owner.retirement())generation_binding(owner.retirement()->before.generation-owner.retirement()->before.first_generation<options.retained_generations);
  const auto checkpoint_path=owner.checkpoint_path(selected.generation);
  recovery::detail::SessionFileReader checkpoint(checkpoint_path.data(),options.replay.journal.checkpoint);
  const auto cap=options.replay.memory_limit_bytes.value_or(checkpoint.memory_limit_bytes());auto context=detail::new_storage_context(expected,cap);
  const auto& account=context->memory();resource::AccountedUnique<ManagedPlan> plan;
  if(selected.plan_sha256) {
    auto bytes=owner.read_plan(account);const auto inspected=recovery::inspect_plan_descriptor({bytes.data(),bytes.size()},options.descriptor);
    const auto& metadata=inspected.selection;
    generation_binding(metadata.predecessor.query_id==selected.query_id && metadata.generation<=selected.generation &&
        metadata.physical_sequence<=selected.physical_sequence && metadata.command_sequence<=selected.command_sequence &&
        view(metadata.target.source_sha256)==expected.physical_source_sha256() && metadata.target.catalog_version==expected.source_catalog().version &&
        bool(selected.delivery)==bool(metadata.sink_origin) && (!selected.delivery || selected.delivery->sink_id==metadata.sink_origin->sink_id));
    recovery::EncodedPlanDescriptor encoded{std::move(bytes),inspected.statistics};
    plan=resource::make_accounted_unique<ManagedPlan>(recovery::image_owner,account,resource::MemoryPurpose::recovery_log,
        std::move(encoded),metadata,inspected.compiler_artifact.size());
  }
  auto data=resource::make_accounted_unique<LockedGenerationRecovery::Data>(recovery::image_owner,account,resource::MemoryPurpose::recovery_log,
      std::move(owner),options,std::move(expected),context,std::move(plan));
  resource::MemoryAllocator<LockedGenerationRecovery> allocator(account,resource::MemoryPurpose::recovery_log,recovery::image_owner);
  auto* facade=allocator.allocate(1);::new(static_cast<void*>(facade))LockedGenerationRecovery(std::move(data));
  return LockedGenerationRecovery::Owner(facade,resource::MemoryDelete<LockedGenerationRecovery>(allocator));
}
QuerySession::Owner QuerySession::restore_selected_generation(LockedGenerationRecovery::Owner input,
    const io::CompilerPlanArtifact& artifact,std::unique_ptr<std::istream> continuation) {
  return restore_locked_generation(std::move(input),artifact,std::move(continuation),{},nullptr);
}
QuerySession::Owner QuerySession::restore_selected_generation_with_local_sink(LockedGenerationRecovery::Owner input,
    const io::CompilerPlanArtifact& artifact,std::string_view sink_path,const SessionLocalSinkOptions& sink_options,std::unique_ptr<std::istream> continuation) {
  return restore_locked_generation(std::move(input),artifact,std::move(continuation),sink_path,&sink_options);
}
QuerySession::Owner QuerySession::restore_locked_generation(LockedGenerationRecovery::Owner input,const io::CompilerPlanArtifact& artifact,
    std::unique_ptr<std::istream> continuation,std::string_view sink_path,const SessionLocalSinkOptions* sink_options) {
  require(bool(input) && bool(artifact.program()),"generation_recovery_input","consume a live locked recovery input and checked compiler artifact");
  auto& locked=*input->data_;const auto selected=locked.owner.selected();const auto& compiled=artifact.program();
  if(locked.owner.retirement() && !sink_options)
    throw recovery::GenerationFailure(recovery::GenerationFault::state,recovery::GenerationStage::state,recovery::GenerationOutcome::unchanged);
  generation_binding(compiled.physical_source_sha256()==locked.expected.physical_source_sha256() &&
      compiled.options().indexed_storage==locked.expected.options().indexed_storage);
  if(locked.plan)generation_binding(artifact.bytes()==locked.plan->artifact() &&
      compiled.physical_sha256()==view(locked.plan->selection.target.physical_sha256) && (!locked.plan->selection.sink_origin || sink_options));
  else generation_binding(compiled.physical_sha256()==locked.expected.physical_sha256());
  const auto checkpoint=locked.owner.checkpoint_path(selected.generation),log=locked.owner.journal_path(selected.generation);
  auto replay=locked.options.replay;replay.journal.generation=selected.generation;
  SessionGenerationOptions policy;policy.journal=replay.journal;policy.root=locked.options.root;policy.retained_generations=locked.options.retained_generations;policy.descriptor=locked.options.descriptor;
  auto managed=resource::make_accounted_unique<ManagedGeneration>(recovery::image_owner,locked.context->memory(),resource::MemoryPurpose::recovery_log,
      std::move(locked.owner),policy);managed->plan=std::move(locked.plan);
  const auto* origin=managed->plan && managed->plan->selection.sink_origin?&*managed->plan->selection.sink_origin:nullptr;
  auto result=restore_journal_selected(compiled,checkpoint.data(),log.data(),replay,std::move(continuation),&selected,sink_path,sink_options,
      &managed->file,locked.context,origin,managed->plan?&managed->plan->selection.target:nullptr);auto& d=*result->data_;
  d.generation=std::move(managed);
  if(d.generation->plan)d.last_switch_epoch=d.generation->plan->selection.last_switch_epoch.value_or(d.generation->plan->selection.physical_sequence);
  if(d.generation->file.retirement())result->retire_generation_history();
  return result;
}

SessionCheckpoint QuerySession::checkpoint_state() const {return checkpoint_state(SessionCheckpointLimits{});}
SessionCheckpoint QuerySession::Impl::checkpoint(const SessionCheckpointLimits& limits,const DeltaRuntime* replacement) const {
  const auto& d=*this;d.journal_available();
  require(d.runtime.has_value(),"session_dropped","a dropped session has no checkpoint state");
  require(!d.has_private() && !d.output && !d.recovery_output_pending() && d.runtime->ready(),"session_checkpoint_busy","checkpoint requires a quiescent session");
  require(!d.delivery_pending(),"local_sink_pending","deliver committed output before checkpointing");
  require(!d.queue || d.queue->empty(),"session_checkpoint_busy","checkpoint requires an empty input queue");
  const auto& engine=replacement?*replacement:*d.runtime;
  require(engine.ready() && engine.sequence()==d.committed_sequence,"invalid_sequence","replacement checkpoint is not at the committed barrier");
  io::checkpoint_detail::Budget policy_budget{limits.source};policy_budget.options(d.run_context->input.get());
  SessionCheckpoint result;result.state=d.control;result.input_kind=d.run_context->input_kind;
  result.input_failed=d.input_failed;result.end_of_input=d.end_of_input;result.committed_sequence=d.committed_sequence;
  result.input_options=d.run_context->input;result.queue_limits=d.run_context->queue;result.snapshot=d.snapshot_limits;
  result.delta=engine.options();result.delta.mode=engine.mode();result.workload=engine.workload_statistics_options();
  result.update_patterns=d.run_context->update_patterns;
  if(result.update_patterns) {
    const auto usage=result.update_patterns->copy_usage();
    if(usage.work>limits.patterns.work)throw recovery::ImageFailure(recovery::ImageFault::work);
    if(usage.cells>limits.patterns.cells || usage.payload_bytes>limits.patterns.payload_bytes)
      throw recovery::ImageFailure(recovery::ImageFault::limit);
  }
  result.version=result.update_patterns?SessionCheckpoint::current_version:SessionCheckpoint::legacy_version;
  result.pattern_origin_sequence=d.pattern_origin_sequence;
  result.pattern_origin_command_sequence=d.pattern_origin_command_sequence;
  result.pattern_violation=d.pattern_violation;
  if(d.window)result.window=d.window->checkpoint_state(limits.window);
  if(d.control==SessionState::stopped) {
    policy_budget.positions(d.final_progress,d.run_context->input.get().limits);
    result.source=io::AccountedInputProgress(d.runtime->compiled_program().account(),d.final_progress);
  }else if(d.reader)result.source=d.reader->checkpoint_state(limits.source);
  else result.source=d.queue->checkpoint_state(limits.source);
  const auto accepted=d.accepted_sequence();
  require(d.runtime->sequence()==d.committed_sequence,"invalid_sequence","session/runtime checkpoint sequence differs");
  if(result.window)require(result.window->progress.physical_sequence==d.committed_sequence &&
      result.window->progress.completed_command_sequence==accepted,"invalid_sequence","window/source checkpoint progress differs");
  else require(accepted==d.committed_sequence,"invalid_sequence","source/runtime checkpoint progress differs");
  result.runtime_image=engine.checkpoint_image(limits.image);return result;
}
SessionCheckpoint QuerySession::checkpoint_state(const SessionCheckpointLimits& limits) const {
  auto& d=*data_;Impl::Guard guard(d);return d.checkpoint(limits);
}
recovery::SessionImage QuerySession::checkpoint_image() const {return checkpoint_image(SessionCheckpointLimits{},recovery::SessionImageLimits{});}
recovery::SessionImage QuerySession::checkpoint_image(const SessionCheckpointLimits& native,const recovery::SessionImageLimits& limits) const {
  auto& d=*data_;Impl::Guard guard(d);auto state=d.checkpoint(native);
  return recovery::encode_session_image(d.runtime->compiled_program().account(),state,native,limits);
}
QuerySession::Owner QuerySession::restore_image(CompiledProgram program,std::string_view bytes,std::unique_ptr<std::istream> continuation) {
  return restore_image(std::move(program),bytes,SessionRestoreOptions{},recovery::SessionImageLimits{},std::move(continuation));
}
QuerySession::Owner QuerySession::restore_image(CompiledProgram program,std::string_view bytes,const SessionRestoreOptions& options,
    std::unique_ptr<std::istream> continuation) {
  return restore_image(std::move(program),bytes,options,recovery::SessionImageLimits{},std::move(continuation));
}
QuerySession::Owner QuerySession::restore_image(CompiledProgram program,std::string_view bytes,const SessionRestoreOptions& options,
    const recovery::SessionImageLimits& limits,std::unique_ptr<std::istream> continuation) {
  const auto validated=recovery::detail::validate_session_image(bytes,options.limits,limits);
  const auto& manifest=validated.inspected.manifest;
  if(bool(continuation)!=(manifest.input_kind==SessionInputKind::owned_stream && manifest.state!=SessionState::stopped))
    throw recovery::ImageFailure(recovery::ImageFault::corrupt);
  const auto cap=options.memory_limit_bytes.value_or(validated.inspected.delta.physical.support.memory_limit_bytes);
  auto context=detail::new_storage_context(program,cap);
  auto decoded=recovery::detail::materialize_session_image(context->memory(),validated);
  return restore_funded(std::move(program),decoded.state,options,std::move(continuation),context,decoded.runtime_bytes);
}
QuerySession::Owner QuerySession::restore_state(CompiledProgram program,const SessionCheckpoint& state,
    std::unique_ptr<std::istream> continuation) {
  return restore_state(std::move(program),state,SessionRestoreOptions{},std::move(continuation));
}
recovery::PublishedCheckpoint QuerySession::checkpoint_file(std::string_view path) const {
  return checkpoint_file(path,SessionCheckpointLimits{},recovery::CheckpointFileLimits{});
}
recovery::PublishedCheckpoint QuerySession::checkpoint_file(std::string_view path,const SessionCheckpointLimits& native,
    const recovery::CheckpointFileLimits& limits) const {
  auto& d=*data_;Impl::Guard guard(d);if(d.journal)throw SessionJournalFailure(SessionJournalFault::state);
  auto state=d.checkpoint(native);
  auto image=recovery::encode_session_image(d.runtime->compiled_program().account(),state,native,limits.image);
  return recovery::publish_session_image(path,image,native,limits);
}
QuerySession::Owner QuerySession::restore_file(CompiledProgram program,std::string_view path,std::unique_ptr<std::istream> continuation) {
  return restore_file(std::move(program),path,SessionRestoreOptions{},recovery::CheckpointFileLimits{},std::move(continuation));
}
QuerySession::Owner QuerySession::restore_file(CompiledProgram program,std::string_view path,const SessionRestoreOptions& options,
    std::unique_ptr<std::istream> continuation) {
  return restore_file(std::move(program),path,options,recovery::CheckpointFileLimits{},std::move(continuation));
}
QuerySession::Owner QuerySession::restore_file(CompiledProgram program,std::string_view path,const SessionRestoreOptions& options,
    const recovery::CheckpointFileLimits& limits,std::unique_ptr<std::istream> continuation) {
  recovery::detail::SessionFileReader reader(path,limits);
  const auto cap=options.memory_limit_bytes.value_or(reader.memory_limit_bytes());auto context=detail::new_storage_context(program,cap);
  const auto bytes=reader.read(context->memory());
  const auto validated=recovery::detail::validate_session_image({bytes.data(),bytes.size()},options.limits,limits.image);
  const auto& manifest=validated.inspected.manifest;
  if(bool(continuation)!=(manifest.input_kind==SessionInputKind::owned_stream && manifest.state!=SessionState::stopped))
    throw recovery::ImageFailure(recovery::ImageFault::corrupt);
  auto decoded=recovery::detail::materialize_session_image(context->memory(),validated);
  return restore_funded(std::move(program),decoded.state,options,std::move(continuation),context,decoded.runtime_bytes);
}
QuerySession::Owner QuerySession::restore_state(CompiledProgram program,const SessionCheckpoint& state,
    const SessionRestoreOptions& options,std::unique_ptr<std::istream> continuation) {
  const auto& encoded=state.runtime_image.bytes;
  return restore_funded(std::move(program),state,options,std::move(continuation),{},{encoded.data(),encoded.size()});
}
QuerySession::Owner QuerySession::restore_funded(CompiledProgram program,const SessionCheckpoint& state,
    const SessionRestoreOptions& options,std::unique_ptr<std::istream> continuation,
    std::shared_ptr<detail::StorageWorkContext> context,std::string_view runtime_bytes) {
  const auto check=[](bool condition,recovery::ImageFault fault=recovery::ImageFault::corrupt) {
    if(!condition)throw recovery::ImageFailure(fault);
  };
  check(state.version==(state.update_patterns?SessionCheckpoint::current_version:SessionCheckpoint::legacy_version),recovery::ImageFault::version);
  check(!state.update_patterns || state.update_patterns->matches(program),recovery::ImageFault::binding);
  check(state.update_patterns || (!state.pattern_violation && !state.pattern_origin_sequence && !state.pattern_origin_command_sequence));
  check(state.state==SessionState::created || state.state==SessionState::running || state.state==SessionState::paused || state.state==SessionState::stopped);
  check(state.input_kind==SessionInputKind::owned_stream || state.input_kind==SessionInputKind::typed_physical || state.input_kind==SessionInputKind::typed_window);
  const bool stopped=state.state==SessionState::stopped,stream=state.input_kind==SessionInputKind::owned_stream;
  check(bool(continuation)==(stream && !stopped));check(!state.input_failed || stopped);
  check(state.queue_limits.has_value()==!stream);check(state.window.has_value()==(state.input_kind==SessionInputKind::typed_window));
  if(state.window)check(state.window->stopped==stopped && !state.window->progress.active_command_sequence);
  const io::AccountedInputProgress* progress=nullptr;
  if(stopped) {
    progress=std::get_if<io::AccountedInputProgress>(&state.source);check(progress!=nullptr);
  }else if(stream) {
    const auto* reader=std::get_if<io::ReaderCheckpoint>(&state.source);check(reader!=nullptr);
    // Session-owned reader record ordinals start at zero. No unacknowledged
    // record may remain at this barrier, so read count equals accepted sequence.
    check(reader->records==reader->progress.sequence);progress=&reader->progress;
  }else {
    const auto* queue=std::get_if<io::QueueCheckpoint>(&state.source);check(queue!=nullptr);progress=&queue->progress;
  }
  check(progress->source_positions.size()<=progress->sequence);
  check(progress->sequence==(state.window?state.window->progress.completed_command_sequence:state.committed_sequence));
  check(state.pattern_origin_sequence<=state.committed_sequence && state.pattern_origin_command_sequence<=progress->sequence);
  check(state.window || state.pattern_origin_sequence==state.pattern_origin_command_sequence);
  if(state.pattern_violation) {
    const auto& violation=*state.pattern_violation;
    check(state.update_patterns && state.input_failed && progress->sequence<UINT64_MAX &&
        violation.command_sequence==progress->sequence+1);
    const auto* rule=state.update_patterns->find(violation.table);
    check(rule!=nullptr);
    switch(violation.kind) {
      case PatternViolationKind::erase_command:check(!state.window && rule->insertion_only && violation.label==0);break;
      case PatternViolationKind::physical_erase:check(bool(state.window) && rule->insertion_only && violation.label>0);break;
      case PatternViolationKind::fifo_scope:check(bool(state.window) && rule->fifo_scope && violation.label>0);break;
      default:check(false);
    }
  }
  if(!stream) {
    const auto& input=state.input_options.get();
    check(input.format==io::InputFormat::jsonl && !input.table && input.delimiter==',' && input.header &&
        input.csv_operation==SetOperation::insert && input.relation_tokens.empty() && !input.null_token && !input.source && input.byte_offset==0 &&
        !input.limits.total_bytes);
  }
  auto delta=state.delta;if(options.memory_limit_bytes)delta.physical.support.memory_limit_bytes=*options.memory_limit_bytes;
  auto runtime=DeltaRuntime::restore_session_image(std::move(program),runtime_bytes,delta,options.build,options.limits.image,
      state.window?&*state.window:nullptr,options.limits.matching_work,&state.workload,std::move(context));
  const auto account=runtime.compiled_program().account();const resource::MemoryAttribution owner{resource::MemoryOwnerKind::session,0};
  auto data=resource::make_accounted_unique<Impl>(owner,account,resource::MemoryPurpose::support_metadata,
      std::move(runtime),std::move(continuation),state,options.limits);
  resource::MemoryAllocator<QuerySession> allocator(account,resource::MemoryPurpose::support_metadata,owner);
  auto* facade=allocator.allocate(1);::new(static_cast<void*>(facade))QuerySession(std::move(data));
  return Owner(facade,resource::MemoryDelete<QuerySession>(allocator));
}
SessionStatus QuerySession::status() const {
  auto& d=*data_; Impl::Guard guard(d);
  return {d.control,d.phase(),d.committed_sequence,d.input_failed || (d.reader && d.reader->failed()) || (d.queue && d.queue->failed()),d.end_of_input,
      d.pending?std::optional<std::uint64_t>{d.pending->sequence()}:std::nullopt,
      d.pending?d.pending->metrics().work:0,d.output_remaining(),
      d.queue?std::optional<io::QueueStats>{d.queue->stats()}:std::nullopt,
      d.window?std::optional<WindowProgress>{d.window->progress()}:std::nullopt,d.pending_command_sequence,
      d.runtime && d.run_context->update_patterns?std::optional<UpdatePatternStatus>{d.pattern_status()}:std::nullopt};
}
UpdatePatternStatus QuerySession::update_pattern_status() const {
  auto& d=*data_;Impl::Guard guard(d);
  require(d.runtime.has_value(),"session_dropped","a dropped session has no active monitor");
  return d.pattern_status();
}
io::InputProgress QuerySession::progress() const {
  auto& d=*data_; Impl::Guard guard(d);
  require(d.control!=SessionState::dropped,"session_dropped","the query session has been dropped"); return d.export_accepted();
}
void QuerySession::begin_reoptimization(const planner::MinimumHeightCandidate& candidate,reoptimization::Options options) {
  begin_reoptimization_with_cost(candidate,std::move(options),0);
}
void QuerySession::begin_reoptimization_with_cost(const planner::MinimumHeightCandidate& candidate,reoptimization::Options options,std::uint64_t selection_ns) {
  auto& d=*data_;Impl::Guard guard(d);d.available(true);
  require(!d.reoptimization || !d.reoptimization->active(),"reoptimization_active","cancel the active candidate before preparing another");
  require(!d.has_private() && !d.output && !d.recovery_output_pending() && !d.delivery_pending(),
      "reoptimization_busy","candidate snapshot requires a committed delivered session barrier");
  require(d.runtime->ready() && d.runtime->sequence()==d.committed_sequence,
      "reoptimization_busy","candidate snapshot requires a writer-ready source epoch");
  const auto& account=d.runtime->compiled_program().account();
  const auto started=reoptimization::detail::State::Clock::now();
  auto candidate_state=resource::make_accounted_unique<reoptimization::detail::State>(reoptimization::detail::attribution,
      account,resource::MemoryPurpose::support_metadata,*d.runtime,candidate,std::move(options),d.last_switch_epoch,started,selection_ns);
  d.reoptimization=std::move(candidate_state);
}
void QuerySession::request_reoptimization_barrier() {
  auto& d=*data_;Impl::Guard guard(d);d.available(true);
  require(d.reoptimization && d.reoptimization->active(),"reoptimization_inactive","prepare a candidate before requesting its barrier");
  d.reoptimization->request_barrier();
}
reoptimization::Status QuerySession::advance_reoptimization(std::uint64_t quantum) {
  auto& d=*data_;Impl::Guard guard(d);d.available(true);
  if(!d.reoptimization)return {};
  auto& candidate=*d.reoptimization;
  if(!candidate.active() || candidate.verified() || quantum==0)return candidate.status();
  if(candidate.frozen()) {
    candidate.barrier_progress();
    while(quantum!=0 && candidate.active()) {
      if(d.output || d.recovery_output_pending() || d.delivery_pending()) {
        candidate.waiting_output();return candidate.status();
      }
      if(!d.has_private() && !d.admitted_input())break;
      const auto start=candidate.time();--quantum;
      try {
        if(!d.has_private())static_cast<void>(d.begin(false,true));
        else if(!d.pending){d.metadata_ready=true;d.finish(false);}
        else {
          if(d.pending->state()==DeltaState::paused)d.pending->resume();
          if(d.pending->step()==DeltaStep::prepared)d.finish(false);
        }
      }catch(...) {d.abort();candidate.cancel(d.journal_confirmed.recovery_required?reoptimization::Phase::recovery_required:reoptimization::Phase::failed,
          reoptimization::Stop::native_failure);throw;}
      candidate.old_drain_elapsed(start);
    }
    if(!candidate.active() || d.has_private() || d.admitted_input() || d.output || d.recovery_output_pending() || d.delivery_pending())
      return candidate.status();
    // Keep the existing checkpoint's empty-queue and complete-command guards.
    if(d.journal && d.journal->state().pending)return candidate.status();
    if(d.window && d.window->progress().active_command_sequence)return candidate.status();
  }
  candidate.advance(quantum);
  if(candidate.active() && candidate.frozen() && candidate.caught_up())candidate.verify(*d.runtime);
  return candidate.status();
}
void QuerySession::cancel_reoptimization() {
  auto& d=*data_;Impl::Guard guard(d);
  d.journal_available();
  if(d.reoptimization)d.reoptimization->cancel();
}
reoptimization::Status QuerySession::reoptimization_status() const {
  auto& d=*data_;Impl::Guard guard(d);return d.reoptimization?d.reoptimization->status():reoptimization::Status{};
}
reoptimization::Status QuerySession::publish_reoptimization(const io::CompilerPlanArtifact& artifact,reoptimization::PublicationOptions requested) {
  auto& d=*data_;Impl::Guard guard(d);d.available(true);
  require(d.reoptimization && d.reoptimization->verified(),"reoptimization_not_verified","verify the candidate before publication");
  require(d.generation && d.journal,"reoptimization_generation_required","enable a managed root or promote the journal before switching plans");
  require(!d.input_failed && !d.end_of_input && (!d.reader || !d.reader->failed()) && (!d.queue || !d.queue->failed()),
      "reoptimization_input_state","publication requires healthy unfinished input");
  require(!d.journal->state().pending && !d.has_private() && !d.admitted_input() && !d.output && !d.recovery_output_pending() && !d.delivery_pending(),
      "reoptimization_busy","publication requires complete input, window and delivery barriers");
  auto& candidate=*d.reoptimization;
  reoptimization::detail::State::Clock::time_point started,selected;
  bool published=false;
  {
    PublicationPreparation preparation(candidate);
    auto& target=candidate.target();auto& managed=*d.generation;const auto before=managed.file.selected();const auto& options=managed.options;
    if(before.generation==UINT64_MAX || before.generation-before.first_generation>=options.retained_generations-1)
      throw recovery::GenerationFailure(recovery::GenerationFault::limit,recovery::GenerationStage::state,recovery::GenerationOutcome::unchanged);
    require(artifact.program() && artifact.program().physical_sha256()==target.plan().physical_sha256() &&
        artifact.program().physical_source_sha256()==target.plan().physical_source_sha256(),"reoptimization_artifact_binding","compiler input differs from the checked native target");
    candidate.charge_artifact(artifact.statistics().preparation_ns,artifact.statistics().compiler_memory,sha256_fixed(artifact.bytes()));
    target.configure_workload_statistics(d.runtime->workload_statistics_options());target.reset_workload_statistics();
    auto context=d.replacement_context(target);const auto& account=target.compiled_program().account();
    auto captured=d.checkpoint(options.journal.native,&target);
    auto image=recovery::encode_session_image(account,captured,options.journal.native,options.journal.checkpoint.image);
    recovery::PlanSelection selection{before,d.runtime->checkpoint_binding(),target.checkpoint_binding(),before.generation+1,d.committed_sequence,d.accepted_sequence(),{},d.committed_sequence};
    if(d.local_sink) {
      require(d.local_sink->verified_prefix.has_value(),"local_sink_unverified","switching requires authenticated output-prefix coverage");
      selection.sink_origin=d.local_sink->header;
      require(logical_binding(selection.sink_origin->binding,selection.target) && selection.sink_origin->fields==target.result_layout().fields().size() &&
          selection.sink_origin->schema_sha256==result_schema(account,target),"local_sink_binding","target schema/source/policy differs from immutable sink origin");
    }
    auto encoded=recovery::encode_plan_descriptor(account,selection,artifact.bytes(),requested.descriptor);
    auto plan=resource::make_accounted_unique<ManagedPlan>(recovery::image_owner,account,resource::MemoryPurpose::recovery_log,
        std::move(encoded),selection,artifact.bytes().size());
    const auto log_path=managed.file.journal_path(selection.generation),checkpoint_path=managed.file.checkpoint_path(selection.generation);
    generation_checkpoint_policy(checkpoint_path.data(),options.journal.checkpoint);
    recovery::journal::Header header{ };header.query_id=before.query_id;header.generation=selection.generation;header.binding=selection.target;
    header.checkpoint_sha256=sha256_fixed({image.bytes.data(),image.bytes.size()});header.physical_sequence=d.committed_sequence;header.command_sequence=d.accepted_sequence();
    header.input_kind=d.reader?recovery::journal::InputKind::stream:d.window?recovery::journal::InputKind::window:recovery::journal::InputKind::physical;
    recovery::GenerationRoot next{before.query_id,selection.generation,before.first_generation,header.checkpoint_sha256,header.physical_sequence,header.command_sequence,
        d.local_sink?d.local_sink->verified_prefix:std::nullopt,sha256_fixed(plan->bytes())};
    Impl::SelectionGuard selection_guard(d,managed);
    managed.file.prepare_next(selection.generation);managed.file.publish_plan(selection.generation,plan->bytes());
    managed.file.publish_checkpoint(selection.generation,{image.bytes.data(),image.bytes.size()});
    auto log=recovery::journal::File::create(account,log_path.data(),header,options.journal.file);
    if(preparation.finish()) {
      started=reoptimization::detail::State::Clock::now();managed.file.publish_root(next);
      selected=reoptimization::detail::State::Clock::now();d.install_reoptimization(candidate,std::move(context),std::move(log),std::move(plan));
      selection_guard.complete=true;published=true;
    }
  }
  if(published)candidate.complete_publication(started,selected,reoptimization::detail::State::Clock::now());
  return candidate.status();
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
  require(result!=SessionBegin::would_block,"input_would_block","input is temporarily blocked by an empty open queue or pending durable delivery");
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
    d.finish(false); return;
  }
  require(d.pending->state()==DeltaState::epoch_prepared,"session_epoch_not_prepared","finish private production before committing input");
  d.finish(false);
}
void QuerySession::start_drain() {
  auto& d=*data_; Impl::Guard guard(d); d.available(true); d.need_pending();
  require(!d.local_sink,"local_sink_attached","attached local output must be retained or cancelled by stop");
  if (!d.pending) { d.metadata_draining=true; return; }
  try { d.pending->start_drain(); } catch (...) { d.abort(); throw; }
}
void QuerySession::drain() {
  auto& d=*data_; Impl::Guard guard(d); d.available(true);
  require(!d.local_sink,"local_sink_attached","attached local output must be delivered or cancelled by stop");
  d.recovery_output_complete=false;
  if (d.pending) {
    const auto sequence=d.pending->sequence();
    try {
      if(d.journal){d.pending->start_drain();d.pending->drain();d.finish(true);}
      else d.publish(d.pending->discard(),sequence,true);
    } catch (...) { d.abort(); throw; }
  } else if (d.window_pending) { d.finish(true); }
  else if (d.output) { d.output->discard(); d.retain_observation(); d.output.reset(); }
  else d.clear_recovered_output();
}
std::optional<SignedResult> QuerySession::next_output() {
  auto& d=*data_; Impl::Guard guard(d); d.available(true);
  require(!d.local_sink,"local_sink_attached","deliver whole epochs through the attached local sink");
  require(!d.has_private(),"session_pending_epoch","private pending output cannot be observed before commitment");
  require(!d.recovery_output_pending(),"session_recovery_output_pending","consume recovered output through its identity-bearing API");
  if (!d.output) return {};
  auto row=d.output->next(); d.retain_observation(); if (!d.output->active()) d.output.reset(); return row;
}
SessionSnapshot QuerySession::snapshot(std::optional<SnapshotLimits> limits) const {
  auto& d=*data_; Impl::Guard guard(d);d.journal_available();
  require(d.control!=SessionState::dropped,"session_dropped","the query session has been dropped");
  require(!d.has_private(),"session_pending_epoch","snapshots require a committed epoch boundary");
  const auto budget=limits.value_or(d.snapshot_limits);
  SessionSnapshot result{d.committed_sequence,d.export_accepted(),d.runtime->result_layout(),SessionRows(d.runtime->compiled_program().account()),0,
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
      result.rows.prepare();
      const auto control=result.rows.owner_usage().requested_bytes;
      const auto framing=resource::MemoryAccount::allocation_bytes(sizeof(storage::Tuple),alignof(storage::Tuple))-sizeof(storage::Tuple);
      const auto remaining=budget.bytes-next_payload;
      require(control<=remaining && framing<=remaining-control,"resource_limit","session snapshot collection limit exceeded");
      const auto capacity=std::min({preferred,budget.rows,static_cast<std::size_t>((remaining-control-framing)/sizeof(storage::Tuple))});
      require(capacity>=count,"resource_limit","session snapshot vector limit exceeded");
      result.rows.reserve(capacity);
    }
    const auto storage=result.rows.memory_usage().requested_bytes;
    require(storage<=std::numeric_limits<std::size_t>::max(),"resource_limit","snapshot collection exceeds host size_t");
    const auto bytes=add(static_cast<std::size_t>(storage),next_payload);
    require(bytes<=budget.bytes,"resource_limit","session snapshot byte limit exceeded");
    result.rows.append(std::move(*row)); payload_bytes=next_payload; result.accounted_bytes=bytes;
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
  if(d.runtime)return SessionReportMetadata(d.runtime->compiled_program(),d.runtime->options(),
      d.runtime->profile(),d.runtime->owner(),d.runtime->sequence(),d.runtime->state());
  const auto& saved=*d.retained_report_metadata;
  return SessionReportMetadata(saved.plan(),saved.options(),saved.profile(),saved.owner(),saved.sequence(),{});
}
std::optional<CommittedStateGauges> QuerySession::report_gauges() const {
  auto& d=*data_;Impl::Guard guard(d);
  if(!d.runtime || d.has_private())return {};
  return d.runtime->committed_state_gauges();
}
std::optional<CapturedStateGauges> QuerySession::capture_state_gauges() const {
  auto& d=*data_;Impl::Guard guard(d);
  if(!d.runtime || d.has_private())return {};
  return d.runtime->capture_state_gauges();
}
std::optional<CursorObservation> QuerySession::last_cursor_observation() const {
  auto& d=*data_; Impl::Guard guard(d);
  return d.runtime?d.runtime->last_cursor_observation():d.retained_cursor_observation;
}
std::optional<resource::MemoryStatistics> QuerySession::accounted_memory_statistics() const {
  auto& d=*data_;Impl::Guard guard(d);
  return d.runtime?std::optional{d.runtime->accounted_memory_statistics()}:std::nullopt;
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
  // Drop releases trace payload; summaries still share immutable program and
  // session metadata under the original query account.
  auto result=d.runtime?d.runtime->observation_trace():ObservationTrace{d.retained_observation,{}};
  result.snapshot.session_context=d.run_context;
  result.snapshot.session_attached=true;
  result.snapshot.session_committed_sequence=d.committed_sequence;
  return result;
}
CapturedObservationTrace QuerySession::capture_observation_trace() const {
  auto& d=*data_;Impl::Guard guard(d);
  const auto& account=d.runtime?d.runtime->compiled_program().account():d.retained_report_metadata->plan().account();
  auto result=d.runtime?d.runtime->capture_observation_trace():CapturedObservationTrace(account);
  if(!d.runtime)result.snapshot=d.retained_observation;
  result.snapshot.session_context=d.run_context;result.snapshot.session_attached=true;
  result.snapshot.session_committed_sequence=d.committed_sequence;return result;
}
}  // namespace crown::runtime

namespace crown::runtime {
void QuerySession::configure_workload_statistics(const workload::Options& options) {
  auto& d=*data_; Impl::Guard guard(d);
  require(d.runtime.has_value(),"session_dropped","statistics owner has been released");
  require(!d.has_private(),"session_pending_epoch","statistics configuration requires a quiescent session");
  d.runtime->configure_workload_statistics(options);
  d.retained_workload_options=d.runtime->workload_statistics_options();
}
void QuerySession::reset_workload_statistics() {
  auto& d=*data_; Impl::Guard guard(d);
  require(d.runtime.has_value(),"session_dropped","statistics owner has been released");
  require(!d.has_private(),"session_pending_epoch","statistics reset requires a quiescent session");
  d.runtime->reset_workload_statistics();
}
workload::Options QuerySession::workload_statistics_options() const {
  auto& d=*data_;Impl::Guard guard(d);
  return d.runtime?d.runtime->workload_statistics_options():d.retained_workload_options;
}
std::optional<workload::Snapshot> QuerySession::workload_statistics() const {
  auto& d=*data_; Impl::Guard guard(d);
  if (!d.runtime) return {};
  auto result=d.runtime->workload_statistics();
  return d.has_private()?result.with_pending():std::move(result);
}
} // namespace crown::runtime

namespace crown::runtime {
std::optional<statistics::OwnerCapture> QuerySession::capture_statistics(const statistics::OwnerRequest& request,statistics::Limits limits) const {
  auto& d=*data_;Impl::Guard guard(d);if(!d.runtime)return {};
  if(d.has_private()){statistics::detail::OwnerBuilder pending{{d.runtime->owner(),d.runtime->sequence(),statistics::OwnerLayer::physical},d.runtime->compiled_program(),request,limits,true};return pending.finish();}
  return d.runtime->capture_statistics(request,limits);
}
std::optional<statistics::Freshness> QuerySession::statistics_freshness(const statistics::OwnerCapture& captured,std::uint64_t max_event_lag) const {
  auto& d=*data_;Impl::Guard guard(d);if(!d.runtime)return {};
  return d.runtime->statistics_freshness(captured,max_event_lag);
}
std::optional<statistics::CombinedCapture> QuerySession::capture_combined_statistics(const statistics::OwnerRequest& request,statistics::Limits limits) const {
  auto& d=*data_;Impl::Guard guard(d);if(!d.runtime)return {};
  if(!d.has_private())return d.runtime->capture_combined_statistics(request,limits);
  statistics::detail::OwnerBuilder pending{{d.runtime->owner(),d.runtime->sequence(),statistics::OwnerLayer::physical},d.runtime->compiled_program(),request,limits,true};
  auto events=d.runtime->workload_statistics().with_pending();
  return statistics::CombinedCapture(pending.finish(),std::move(events));
}
SessionStatisticsContext QuerySession::capture_statistics_context(
    const std::optional<statistics::OwnerRequest>& selections,statistics::Limits limits) const {
  std::optional<statistics::OwnerRequestView> view;if(selections)view.emplace(*selections);
  return capture_statistics_context_view(view,limits);
}
SessionStatisticsContext QuerySession::capture_statistics_context_view(
    const std::optional<statistics::OwnerRequestView>& selections,statistics::Limits limits) const {
  auto& d=*data_;Impl::Guard guard(d);
  const auto metadata=d.runtime?SessionReportMetadata(d.runtime->compiled_program(),d.runtime->options(),d.runtime->profile(),d.runtime->owner(),d.runtime->sequence(),d.runtime->state()):
      SessionReportMetadata(d.retained_report_metadata->plan(),d.retained_report_metadata->options(),d.retained_report_metadata->profile(),d.retained_report_metadata->owner(),d.retained_report_metadata->sequence(),{});
  const SessionStatus status{d.control,d.phase(),d.committed_sequence,
      d.input_failed || (d.reader && d.reader->failed()) || (d.queue && d.queue->failed()),d.end_of_input,
      d.pending?std::optional<std::uint64_t>{d.pending->sequence()}:std::nullopt,d.pending?d.pending->metrics().work:0,
      d.output_remaining(),d.queue?std::optional<io::QueueStats>{d.queue->stats()}:std::nullopt,
      d.window?std::optional<WindowProgress>{d.window->progress()}:std::nullopt,d.pending_command_sequence,
      d.runtime && d.run_context->update_patterns?std::optional<UpdatePatternStatus>{d.pattern_status()}:std::nullopt};
  auto trace=d.runtime?d.runtime->capture_observation_trace():CapturedObservationTrace(metadata.plan().account());
  if(!d.runtime)trace.snapshot=d.retained_observation;
  trace.snapshot.session_context=d.run_context;trace.snapshot.session_attached=true;
  trace.snapshot.session_committed_sequence=d.committed_sequence;
  std::optional<statistics::CombinedCapture> combined;
  const statistics::OwnerRequestView empty;
  const auto& request=selections?*selections:empty;
  if(d.runtime){
    if(d.has_private()){
      statistics::detail::OwnerBuilder state{{d.runtime->owner(),d.runtime->sequence(),statistics::OwnerLayer::physical},d.runtime->compiled_program(),request,limits,true};
      combined=statistics::CombinedCapture(state.finish(),d.runtime->workload_statistics().with_pending());
    }else combined=d.runtime->capture_combined_statistics_view(request,limits);
  }
  return SessionStatisticsContext(resource::make_accounted_shared<SessionStatisticsContext::Data>(
      {resource::MemoryOwnerKind::capture,0},metadata.plan().account(),resource::MemoryPurpose::capture,SessionStatisticsContext::Data{
      metadata,status,std::move(trace),std::move(combined),d.runtime?d.runtime->workload_statistics_options():d.retained_workload_options,
      d.runtime?d.runtime->last_cursor_observation():d.retained_cursor_observation,selections.has_value()}));
}
}

namespace crown::runtime::memory::detail {
Attempt Access::capture(const QuerySession& owner,Limits limits) noexcept {
  return attempt([&](Usage& usage) {
    if(!owner.data_)throw Failure{Stop::invalid_handle};
    auto& d=*owner.data_;QuerySession::Impl::Guard guard(d);
    const auto& plan=d.runtime?d.runtime->compiled_program():d.retained_report_metadata->plan();
    const auto availability=!d.runtime?Availability::released:d.has_private()?Availability::pending:Availability::committed;
    const auto id=d.runtime?d.runtime->owner():d.retained_report_metadata->owner();
    Builder builder(plan.account(),Layer::session,availability,id.value,d.committed_sequence,plan.physical_sha256(),limits,usage);
    if(availability==Availability::committed) {
      append(builder,*d.runtime);builder.operation(Coordinator{Layer::session,{resource::MemoryOwnerKind::session,0}});
    }
    return builder.finish();
  });
}
}
