#pragma once
#include "crown/runtime/combined_statistics.hpp"

#include "crown/io/batch.hpp"
#include "crown/io/input_options.hpp"
#include "crown/runtime/window.hpp"
#include "crown/runtime/update_pattern.hpp"
#include "crown/runtime/delta.hpp"
#include "crown/runtime/reoptimization.hpp"
#include "crown/runtime/workload_statistics.hpp"
#include "crown/runtime/program.hpp"
#include "crown/resource/ownership.hpp"

namespace crown::recovery {struct SessionImage;struct SessionImageLimits;struct CheckpointFileLimits;struct PublishedCheckpoint;struct GenerationRoot;}
namespace crown::recovery::sink {class Receipt;struct Epoch;}
namespace crown::recovery::detail {class GenerationOwner;}
namespace crown::io {class CompilerPlanArtifact;}
namespace crown::runtime {
class QuerySession;
namespace selection {
class CurrentSelection;
void begin_reoptimization(QuerySession&,const CurrentSelection&,reoptimization::Options);
}
struct SessionCheckpoint;
struct SessionCheckpointLimits;
struct SessionRestoreOptions;
struct SessionJournalOptions;
struct SessionJournalState;
struct SessionJournalRecoveryOptions;
struct SessionJournalRecoveryStatus;
struct RecoveredResult;
struct SessionGenerationOptions;
struct SessionGenerationRecoveryOptions;
struct SessionGenerationState;
struct SessionLocalSinkOptions;
struct SessionLocalSinkState;
struct LocalDelivery;
class LockedGenerationRecovery;
enum class SessionBegin { pending, would_block, end };
enum class SessionState { created, running, paused, stopped, dropped };
enum class SessionPhase { ready, pending, paused_pending, draining, prepared, output };
struct SessionStatus {
  SessionState state;
  SessionPhase phase;
  std::uint64_t committed_sequence;
  bool input_failed;
  bool end_of_input;
  std::optional<std::uint64_t> pending_sequence;
  std::uint64_t pending_work;
  std::size_t output_remaining;
  std::optional<io::QueueStats> queue;
  std::optional<WindowProgress> window;
  std::optional<std::uint64_t> pending_command_sequence;
  std::optional<UpdatePatternStatus> update_patterns;
};
struct SnapshotLimits {
  std::size_t rows=65536;
  // Actual retained collection/control/capacity requests plus each native
  // tuple's scalar/shared-owner requests, including account framing. Shared
  // metadata, progress and cursor scratch are outside this snapshot sublimit;
  // transient old/new capacity blocks still consume the original query budget.
  std::size_t bytes=64*1024*1024;
  ResultCursorOptions cursor;
};
struct SessionOptions {
  // Input options own ordinary token/text storage; copying them may allocate.
  // The benchmark handle retains its actual immutable declaration context.
  io::InputOptions input;
  DeltaOptions delta;
  SnapshotLimits snapshot;
  std::shared_ptr<const DeclaredBenchmarkContext> declared_benchmark;
  std::optional<UpdatePatternOptions> update_patterns;
};
enum class SessionInputKind { owned_stream, typed_physical, typed_window };
// Constructed once during session admission, never copied by observation hooks.
// Exact native bytes remain native bytes; strict text encoding is an export duty.
struct SessionRunContext {
  SessionInputKind input_kind;
  io::AccountedInputOptions input;
  std::optional<io::QueueLimits> queue;
  std::optional<AccountedWindowOptions> window;
  SnapshotLimits snapshot;
  InitializationContext initialization;
  DeltaOptions requested_delta;
  DeltaMode resolved_mode;
  DeltaCompletion resolved_completion;
  std::optional<patterns::Declaration> update_patterns;
};
// Immutable snapshot collection. Copies retain the original funded storage;
// moves/assignment transfer its owner without unequal-allocator vector copies.
// Iterators/references borrow from this collection's lifetime.
class SessionRows {
  // Only private, uniquely owned Data may grow before snapshot publication.
  // memory_usage() counts collection/control, excluding each tuple payload.
 public:
  using const_iterator=std::span<const storage::Tuple>::iterator;
  SessionRows() noexcept=default;
  [[nodiscard]] std::size_t size() const noexcept;
  [[nodiscard]] std::size_t capacity() const noexcept;
  [[nodiscard]] bool empty() const noexcept {return size()==0;}
  [[nodiscard]] const storage::Tuple* data() const noexcept;
  [[nodiscard]] const storage::Tuple& operator[](std::size_t i) const noexcept {return data()[i];}
  [[nodiscard]] const storage::Tuple& at(std::size_t) const;
  [[nodiscard]] const storage::Tuple& front() const noexcept {return (*this)[0];}
  [[nodiscard]] const storage::Tuple& back() const noexcept {return (*this)[size()-1];}
  [[nodiscard]] const_iterator begin() const noexcept {return std::span<const storage::Tuple>{data(),size()}.begin();}
  [[nodiscard]] const_iterator end() const noexcept {return std::span<const storage::Tuple>{data(),size()}.end();}
  [[nodiscard]] resource::MemoryUsage memory_usage() const;
  [[nodiscard]] resource::MemoryStatistics account_statistics() const {return account_.statistics();}
 private:
  friend class QuerySession;
  struct Data;
  explicit SessionRows(const resource::MemoryAccount& account) noexcept:account_(account) {}
  void prepare();
  void reserve(std::size_t);
  void append(storage::Tuple);
  [[nodiscard]] resource::MemoryUsage owner_usage() const noexcept;
  resource::MemoryAccount account_;
  std::shared_ptr<Data> data_;
};
struct SessionSnapshot {
  // Copies share SessionRows; copying exported progress maps/text may allocate.
  // Fields describe a committed read; they do not grant native/durable authority.
  std::uint64_t sequence;
  io::InputProgress progress;
  storage::TupleLayout layout;
  SessionRows rows;
  std::size_t accounted_bytes=0;
  std::optional<WindowProgress> window;
};

// Immutable metadata-only handle sharing the actual accounted program.
class SessionReportMetadata {
 public:
  SessionReportMetadata(const SessionReportMetadata&) noexcept = default;
  SessionReportMetadata& operator=(const SessionReportMetadata&) noexcept = default;
  [[nodiscard]] const CompiledProgram& plan() const noexcept { return plan_; }
  [[nodiscard]] const DeltaOptions& options() const noexcept { return options_; }
  [[nodiscard]] const DeltaRuntimeProfile& profile() const noexcept { return profile_; }
  [[nodiscard]] SupportOwnerId owner() const noexcept { return owner_; }
  [[nodiscard]] std::uint64_t sequence() const noexcept { return sequence_; }
  [[nodiscard]] std::optional<DeltaState> state() const noexcept { return state_; }
 private:
  friend class QuerySession;
  SessionReportMetadata(CompiledProgram plan,DeltaOptions options,DeltaRuntimeProfile profile,
      SupportOwnerId owner,std::uint64_t sequence,std::optional<DeltaState> state) noexcept
      :plan_(std::move(plan)),options_(options),profile_(profile),owner_(owner),sequence_(sequence),state_(state) {}
  CompiledProgram plan_;
  DeltaOptions options_;
  DeltaRuntimeProfile profile_;
  SupportOwnerId owner_;
  std::uint64_t sequence_;
  std::optional<DeltaState> state_;
};

// One guarded runtime-only diagnostic boundary. Factory-produced and owning;
// no report/observability dependency or public metadata constructor.
class SessionStatisticsContext {
  // Copies/copy-like moves share the captured graph; accessors borrow from it.
  // Factory capture can scan/allocate trace, workload and requested populations.
 public:
  SessionStatisticsContext(const SessionStatisticsContext&) noexcept=default;
  SessionStatisticsContext(SessionStatisticsContext&& other) noexcept:data_(other.data_) {}
  SessionStatisticsContext& operator=(const SessionStatisticsContext&) noexcept=default;
  SessionStatisticsContext& operator=(SessionStatisticsContext&& other) noexcept {data_=other.data_;return *this;}
  [[nodiscard]] const SessionReportMetadata& metadata() const noexcept;
  [[nodiscard]] const SessionStatus& status() const noexcept;
  [[nodiscard]] const CapturedObservationTrace& trace() const noexcept;
  [[nodiscard]] const std::optional<statistics::CombinedCapture>& combined() const noexcept;
  [[nodiscard]] const workload::Options& workload_options() const noexcept;
  [[nodiscard]] const std::optional<CursorObservation>& cursor() const noexcept;
  [[nodiscard]] bool state_requested() const noexcept;
 private:
  friend class QuerySession;
  struct Data;
  explicit SessionStatisticsContext(std::shared_ptr<const Data> data) noexcept:data_(std::move(data)) {}
  std::shared_ptr<const Data> data_;
};

// Synchronous, creator-thread writer ownership. Owns the input stream and all
// runtime/pending/output resources. Never exposes an internal token or lease.
// Accepted sequence starts at zero; initialization overloads preserve supplied rows.
// Destruction requires exclusive ownership, as for its owned input stream.
class QuerySession {
  friend struct memory::detail::Access;
 public:
  using Owner=resource::AccountedUnique<QuerySession>;
  [[nodiscard]] static Owner create(PhysicalPlan plan,
      std::unique_ptr<std::istream> input,SessionOptions options={});
  [[nodiscard]] static Owner create(CompiledProgram plan,
      std::unique_ptr<std::istream> input,SessionOptions options={});
  [[nodiscard]] static Owner create(PhysicalPlan plan,const Database& initial,
      std::unique_ptr<std::istream> input,SessionOptions options={},BuildOptions build={});
  [[nodiscard]] static Owner create(CompiledProgram plan,const Database& initial,
      std::unique_ptr<std::istream> input,SessionOptions options={},BuildOptions build={});
  [[nodiscard]] static Owner create_typed(PhysicalPlan plan,
      io::QueueLimits limits={},SessionOptions options={});
  [[nodiscard]] static Owner create_typed(CompiledProgram plan,
      io::QueueLimits limits={},SessionOptions options={});
  [[nodiscard]] static Owner create_typed(PhysicalPlan plan,const Database& initial,
      io::QueueLimits limits={},SessionOptions options={},BuildOptions build={});
  [[nodiscard]] static Owner create_typed(CompiledProgram plan,const Database& initial,
      io::QueueLimits limits={},SessionOptions options={},BuildOptions build={});
  [[nodiscard]] static Owner create_windowed(PhysicalPlan plan,WindowOptions window,
      io::QueueLimits limits={},SessionOptions options={});
  [[nodiscard]] static Owner create_windowed(CompiledProgram plan,WindowOptions window,
      io::QueueLimits limits={},SessionOptions options={});
  [[nodiscard]] static Owner create_windowed(PhysicalPlan plan,const Database& initial,
      WindowOptions window,io::QueueLimits limits={},SessionOptions options={},BuildOptions build={});
  [[nodiscard]] static Owner create_windowed(CompiledProgram plan,const Database& initial,
      WindowOptions window,io::QueueLimits limits={},SessionOptions options={},BuildOptions build={});
  ~QuerySession();
  QuerySession(const QuerySession&)=delete;
  QuerySession& operator=(const QuerySession&)=delete;
  QuerySession(QuerySession&&)=delete;
  QuerySession& operator=(QuerySession&&)=delete;
  [[nodiscard]] SessionStatus status() const;
  [[nodiscard]] UpdatePatternStatus update_pattern_status() const;
  [[nodiscard]] SessionReportMetadata report_metadata() const;
  // Null while private session work exists or after runtime release. This
  // explicit allocating committed read never advances/drains the session.
  [[nodiscard]] std::optional<CommittedStateGauges> report_gauges() const;
  [[nodiscard]] std::optional<CapturedStateGauges> capture_state_gauges() const;
  [[nodiscard]] std::optional<statistics::OwnerCapture> capture_statistics(const statistics::OwnerRequest&,statistics::Limits limits={}) const;
  [[nodiscard]] std::optional<statistics::Freshness> statistics_freshness(const statistics::OwnerCapture&,std::uint64_t max_event_lag=0) const;
  [[nodiscard]] std::optional<statistics::CombinedCapture> capture_combined_statistics(const statistics::OwnerRequest&,statistics::Limits limits={}) const;
  [[nodiscard]] std::shared_ptr<const SessionRunContext> run_context() const;
  // Null after runtime release. Reports the native query account's actual
  // requested-byte usage, including retained owners; not process RSS.
  [[nodiscard]] std::optional<resource::MemoryStatistics> accounted_memory_statistics() const;
  [[nodiscard]] ObservationSnapshot observations() const;
  void configure_workload_statistics(const workload::Options&);
  void reset_workload_statistics();
  [[nodiscard]] std::optional<workload::Snapshot> workload_statistics() const;
  [[nodiscard]] workload::Options workload_statistics_options() const;
  [[nodiscard]] SessionStatisticsContext capture_statistics_context(
      const std::optional<statistics::OwnerRequest>& request=std::nullopt,statistics::Limits limits={}) const;
  [[nodiscard]] SessionStatisticsContext capture_statistics_context_view(
      const std::optional<statistics::OwnerRequestView>& request,statistics::Limits limits={}) const;
  [[nodiscard]] std::optional<CursorObservation> last_cursor_observation() const;
  [[nodiscard]] ObservationTrace observation_trace() const;
  [[nodiscard]] CapturedObservationTrace capture_observation_trace() const;
  [[nodiscard]] io::InputProgress progress() const;
  // Explicit candidate preparation on the original query account. The old
  // session keeps processing until the requested admission barrier is drained.
  // verified means exact source/result equality plus policy eligibility;
  // publication/recovery are separate barriers, never implied by preparation.
  void begin_reoptimization(const planner::MinimumHeightCandidate&,reoptimization::Options={});
  void request_reoptimization_barrier();
  [[nodiscard]] reoptimization::Status advance_reoptimization(std::uint64_t quantum=64);
  void cancel_reoptimization();
  [[nodiscard]] reoptimization::Status reoptimization_status() const;
  [[nodiscard]] reoptimization::Status publish_reoptimization(const io::CompilerPlanArtifact&,reoptimization::PublicationOptions={});
  void start();
  void pause();
  // Admission is allowed before start, but not while paused or terminal.
  [[nodiscard]] io::Admission enqueue(io::TransportBatch& batch);
  void finish_input();
  [[nodiscard]] SessionBegin begin_next_result();
  // False means validated EOF; open-empty typed input throws input_would_block.
  // Window metadata-only work uses an explicit private preparation barrier.
  [[nodiscard]] bool begin_next();
  [[nodiscard]] DeltaStep step();
  // Prepared only. All work after engine publication is nonthrowing.
  void commit();
  void start_drain();
  // Complete/discard only the current input/output; never reads another event.
  // May finish a paused epoch while leaving admission paused.
  void drain();
  [[nodiscard]] std::optional<SignedResult> next_output();
  // Actual committed results, including epoch-zero Boolean/nullary results.
  // Allowed with committed unread output; rejected with private pending work.
  [[nodiscard]] SessionSnapshot snapshot(std::optional<SnapshotLimits> limits=std::nullopt) const;
  [[nodiscard]] std::optional<WindowCanonicalState> window_state() const;
  // Enable durable input/decision writes at a quiescent barrier. The existing
  // durable checkpoint must exactly describe this session. No file is replaced.
  void enable_journal(std::string_view checkpoint_path,std::string_view journal_path,const SessionJournalOptions&);
  [[nodiscard]] SessionJournalState journal_state() const;
  [[nodiscard]] static Owner restore_journal(CompiledProgram,std::string_view checkpoint_path,std::string_view journal_path,
      const SessionJournalRecoveryOptions&,std::unique_ptr<std::istream> continuation={});
  // Validate the actual durable sink before replay. Already accepted complete
  // epochs are compared without writing or retaining a replay output backlog.
  [[nodiscard]] static Owner restore_journal_with_local_sink(CompiledProgram,std::string_view checkpoint_path,std::string_view journal_path,
      const SessionJournalRecoveryOptions&,std::string_view sink_path,const SessionLocalSinkOptions&,
      std::unique_ptr<std::istream> continuation={});
  [[nodiscard]] SessionJournalRecoveryStatus recovery_status() const;
  [[nodiscard]] std::optional<RecoveredResult> next_recovered_output();
  void discard_recovered_output();
  // Select a durable checkpoint/log pair through a separately locked root.
  // Rotation retains historical pairs; output consumption is not retirement.
  void enable_generation(std::string_view root_path,const SessionGenerationOptions&);
  void promote_journal(std::string_view root_path,const SessionGenerationOptions&);
  void rotate_generation();
  // Retire only generations before the selected durable checkpoint, after
  // the attached actual local sink has verified all committed delivery.
  void retire_generation_history();
  [[nodiscard]] SessionGenerationState generation_state() const;
  [[nodiscard]] static Owner restore_generation(CompiledProgram,std::string_view root_path,
      const SessionGenerationRecoveryOptions&,std::unique_ptr<std::istream> continuation={});
  [[nodiscard]] static Owner restore_generation_with_local_sink(CompiledProgram,std::string_view root_path,
      const SessionGenerationRecoveryOptions&,std::string_view sink_path,const SessionLocalSinkOptions&,
      std::unique_ptr<std::istream> continuation={});
  [[nodiscard]] static resource::AccountedUnique<LockedGenerationRecovery> lock_generation_recovery(
      CompiledProgram expected_source,std::string_view,const SessionGenerationRecoveryOptions&);
  [[nodiscard]] static Owner restore_selected_generation(resource::AccountedUnique<LockedGenerationRecovery>,
      const io::CompilerPlanArtifact&,std::unique_ptr<std::istream> continuation={});
  [[nodiscard]] static Owner restore_selected_generation_with_local_sink(resource::AccountedUnique<LockedGenerationRecovery>,
      const io::CompilerPlanArtifact&,std::string_view,const SessionLocalSinkOptions&,std::unique_ptr<std::istream> continuation={});
  void create_local_sink(std::string_view,const SessionLocalSinkOptions&);
  // Also reopens a poisoned attached sink. Keeps committed output until whole
  // epoch acceptance; ordinary transfer/discard cannot bypass this contract.
  void open_local_sink(std::string_view,const SessionLocalSinkOptions&);
  [[nodiscard]] SessionLocalSinkState local_sink_state() const;
  [[nodiscard]] LocalDelivery deliver_local_epoch();
  [[nodiscard]] recovery::sink::Epoch read_local_epoch(std::uint64_t);
  [[nodiscard]] recovery::sink::Receipt local_sink_receipt() const;
  [[nodiscard]] SessionCheckpoint checkpoint_state() const;
  [[nodiscard]] SessionCheckpoint checkpoint_state(const SessionCheckpointLimits&) const;
  [[nodiscard]] static Owner restore_state(CompiledProgram,const SessionCheckpoint&,
      std::unique_ptr<std::istream> continuation={});
  [[nodiscard]] static Owner restore_state(CompiledProgram,const SessionCheckpoint&,
      const SessionRestoreOptions&,std::unique_ptr<std::istream> continuation={});
  [[nodiscard]] recovery::SessionImage checkpoint_image() const;
  [[nodiscard]] recovery::SessionImage checkpoint_image(const SessionCheckpointLimits&,const recovery::SessionImageLimits&) const;
  [[nodiscard]] static Owner restore_image(CompiledProgram,std::string_view,std::unique_ptr<std::istream> continuation={});
  [[nodiscard]] static Owner restore_image(CompiledProgram,std::string_view,const SessionRestoreOptions&,
      std::unique_ptr<std::istream> continuation={});
  [[nodiscard]] static Owner restore_image(CompiledProgram,std::string_view,const SessionRestoreOptions&,
      const recovery::SessionImageLimits&,std::unique_ptr<std::istream> continuation={});
  [[nodiscard]] recovery::PublishedCheckpoint checkpoint_file(std::string_view path) const;
  [[nodiscard]] recovery::PublishedCheckpoint checkpoint_file(std::string_view path,const SessionCheckpointLimits&,
      const recovery::CheckpointFileLimits&) const;
  [[nodiscard]] static Owner restore_file(CompiledProgram,std::string_view path,std::unique_ptr<std::istream> continuation={});
  [[nodiscard]] static Owner restore_file(CompiledProgram,std::string_view path,const SessionRestoreOptions&,
      std::unique_ptr<std::istream> continuation={});
  [[nodiscard]] static Owner restore_file(CompiledProgram,std::string_view path,const SessionRestoreOptions&,
      const recovery::CheckpointFileLimits&,std::unique_ptr<std::istream> continuation={});
  // Stop is terminal; abort unpublished work, release source/output buffers,
  // retain committed runtime for snapshots. Drop releases runtime state too.
  // Public guards can report thread/reentrancy errors; cleanup never allocates.
  void stop();
  void drop();
 private:
  friend void selection::begin_reoptimization(QuerySession&,const selection::CurrentSelection&,reoptimization::Options);
  void begin_reoptimization_with_cost(const planner::MinimumHeightCandidate&,reoptimization::Options,std::uint64_t selection_ns);
  void local_sink_impl(std::string_view,const SessionLocalSinkOptions&,bool create);
  [[nodiscard]] static Owner restore_journal_selected(CompiledProgram,std::string_view,std::string_view,
      const SessionJournalRecoveryOptions&,std::unique_ptr<std::istream>,const recovery::GenerationRoot*,
      std::string_view={},const SessionLocalSinkOptions* =nullptr,const recovery::detail::GenerationOwner* =nullptr,
      std::shared_ptr<detail::StorageWorkContext> ={},const recovery::sink::Header* =nullptr,const recovery::ImageBinding* =nullptr);
  [[nodiscard]] static Owner restore_locked_generation(resource::AccountedUnique<LockedGenerationRecovery>,
      const io::CompilerPlanArtifact&,std::unique_ptr<std::istream>,std::string_view,const SessionLocalSinkOptions*);
  [[nodiscard]] static Owner restore_generation_impl(CompiledProgram,std::string_view,
      const SessionGenerationRecoveryOptions&,std::unique_ptr<std::istream>,std::string_view,const SessionLocalSinkOptions*);
  [[nodiscard]] static Owner restore_funded(CompiledProgram,const SessionCheckpoint&,const SessionRestoreOptions&,
      std::unique_ptr<std::istream>,std::shared_ptr<detail::StorageWorkContext>,std::string_view);
#ifdef CROWN_RUNTIME_TESTING
  friend class RuntimeTestProbe;
#endif
  struct Impl;
  explicit QuerySession(resource::AccountedUnique<Impl> data) noexcept;
  using PlanSource=std::variant<PhysicalPlan,CompiledProgram>;
  [[nodiscard]] static Owner create_impl(PlanSource,const Database*,std::unique_ptr<std::istream>,
      std::optional<io::QueueLimits>,SessionOptions,std::optional<WindowOptions>,BuildOptions);
  resource::AccountedUnique<Impl> data_;
};
}  // namespace crown::runtime
