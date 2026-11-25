#pragma once

#include "crown/runtime/physical.hpp"
#include "crown/storage/keyed.hpp"
#include <string_view>

namespace crown::observability {class ModeDescriptor;}
namespace crown::runtime {
class QuerySession;
namespace ranking::detail {struct OwnerAccess;}
namespace reoptimization::detail {class Budget;struct Access;}
enum class DeltaMode { maintenance, delta };
// Execution core: the keyed core (docs/keyed_core.md) or the reference core.
// automatic selects keyed whenever the compiled program is supported.
enum class DeltaEngine { automatic, keyed, reference };
enum class LiveMaintenance { on_output, incremental, eager };
enum class DeltaCompletion { automatic, ordered_replay, anchored, root_first };
enum class DeltaBound { unclaimed, bounded_indexed_actions };
enum class DeltaPublication { no_delta_output, eager_atomic_spool };
enum class DeltaState { ready, pending_delta, paused, draining, epoch_prepared, committed_output, committed, aborted };
enum class DeltaStep { progress, core_result, prepared };
struct DeltaTimings {
  // Disjoint wall-clock phases, excluding user pause time. Sink time includes
  // callback CPU/wait; serialization records the optional codec callback.
  // Saturating diagnostic values do not participate in deterministic work caps.
  std::uint64_t propagation_ns=0, internal_delta_ns=0, output_mapping_ns=0;
  std::uint64_t serialization_ns=0, sink_wait_ns=0;
};
struct DeltaRuntimeProfile {
  DeltaMode mode=DeltaMode::maintenance;
  LiveMaintenance live_maintenance=LiveMaintenance::on_output;
  DeltaCompletion completion=DeltaCompletion::automatic;
  ResultView view=ResultView::sql;
  DeltaBound candidate_transitions=DeltaBound::unclaimed;
  DeltaBound accepted_transitions=DeltaBound::unclaimed;
  DeltaPublication publication=DeltaPublication::no_delta_output;
  bool public_first_record_constant_delay=false;
  std::size_t query_factors=0, spool_row_limit=0, spool_byte_limit=0;
  // All text refers to static storage; this value may outlive its facade.
  std::string_view semantics="exact_set", query_class="free_connex", arithmetic="exact-nonnull-v1";
  std::string_view update_contract="single physical full-row set event with atomic ordered aliases";
  std::string_view backend="reference_ordered_v1";
  std::string_view engine="reference_v1";  // keyed_v1 when the keyed core executes
  std::string_view state_bound, maintenance_bound, preparation_bound, candidate_bound, accepted_bound;
  std::string_view finalization_bound, public_startup_bound;
  std::string_view ordered_costs="map/set operations use O(log N) comparisons in the relevant state/patch/queue; scalar widths and allocator costs are additional";
  std::string_view assumptions="fixed verified query/tree; running intersection; downward totality; one writer; pinned endpoint E; monotone same-sign routes";
  // Legacy v2 text is byte-stable; actual spool charges include account framing.
  // DeltaOptions and the runtime guide state the current quota boundary.
  std::string_view output_accounting="one owning node per prepared record; node/value/payload quota; per-allocation allocator metadata and caller-owned records/journals are additional; unread-output and final-owner teardown are explicit cleanup";
};
struct DeltaOptions {
  PhysicalRuntimeOptions physical;
  DeltaMode mode = DeltaMode::delta;
  ResultView view = ResultView::sql;
  LiveMaintenance live_maintenance = LiveMaintenance::on_output;
  // Automatic selects replay for row-coupled live maintenance and anchored
  // canonical ownership for the eager/bucket comparison policies.
  DeltaCompletion completion = DeltaCompletion::automatic;
  std::optional<std::uint64_t> work_limit = 1000000;
  ResultCursorOptions cursor;
  EpochViewOptions epoch_view;
  // An epoch exceeding either finite spool limit aborts before publication.
  // Bytes include FIFO node and native tuple requests with account framing.
  // Shared query descriptors and candidate/mapping scratch are additional.
  std::size_t spool_row_limit = 65536;
  std::size_t spool_byte_limit = 64 * 1024 * 1024;
  DeltaEngine engine = DeltaEngine::automatic;
  storage::keyed::GcOptions gc{};  // keyed core only
};
struct DeltaMetrics {
  std::uint64_t work = 0, stages = 0, journal_records = 0, view_work = 0;
  std::uint64_t e_rows_scanned = 0, parent_live_rows = 0, separator_fields = 0, live_rows_copied = 0;
  std::uint64_t changed_keys = 0, live_witnesses = 0, dead_witnesses = 0;
  std::uint64_t candidates = 0, accepted = 0, rejected = 0, earlier_probes = 0;
  std::uint64_t binding_fields = 0, projection_fields = 0, output_fields = 0;
  std::uint64_t cursor_startup_work = 0, cursor_results_work = 0, cursor_termination_work = 0;
  std::uint64_t live_probes = 0, live_changes = 0, live_inserts = 0, live_erases = 0;
  std::uint64_t live_bucket_opens = 0, live_bucket_rows = 0;
  std::uint64_t live_separator_updates = 0, live_separator_crossings = 0, live_journal_entries = 0;
  std::uint64_t live_parent_index_updates = 0, live_parent_index_rows_copied = 0, live_parent_index_fields = 0;
  std::uint64_t live_parent_index_cleanup_rows = 0;
  std::uint64_t live_child_index_updates = 0, live_child_index_rows_copied = 0, live_child_index_fields = 0;
  std::uint64_t live_child_separator_fields = 0;
  std::uint64_t anchor_steps = 0, anchor_bucket_opens = 0, anchor_parent_lookups = 0;
  std::uint64_t anchor_parent_rows = 0, anchor_down_work = 0, anchor_down_rows = 0, anchor_fields = 0;
  std::uint64_t anchor_child_lookups = 0, anchor_child_rows = 0;
  std::uint64_t anchor_cursors = 0, anchor_max_startup_work = 0, anchor_max_result_work = 0, anchor_max_termination_work = 0;
  std::uint64_t replay_preparation_work = 0, replay_queue_inserts = 0, replay_queue_pops = 0;
  std::uint64_t replay_queue_lookups = 0, replay_queue_erases = 0, replay_queue_fields = 0, replay_factor_steps = 0;
  std::uint64_t replay_queue_releases = 0;
  std::uint64_t replay_witness_tests = 0;
  std::uint64_t replay_first_work = 0, replay_results_work = 0, replay_termination_work = 0;
  std::uint64_t replay_max_first_work = 0, replay_max_next_work = 0, replay_max_last_work = 0;
  std::uint64_t finalization_work = 0, finalization_changed_keys = 0, finalization_view_entry_bound = 0;
  std::uint64_t finalization_kernel_record_bound = 0, finalization_driver_changes = 0, finalization_undo_entries = 0;
  std::uint64_t finalization_image_rows = 0;
  std::size_t live_queue_peak = 0;
  std::size_t live_rows = 0, peak_live_rows = 0;
  std::size_t parent_index_rows = 0, peak_parent_index_rows = 0;
  std::size_t child_index_rows = 0, peak_child_index_rows = 0, replay_queue_peak = 0;
  std::size_t spool_rows = 0, spool_bytes = 0, spool_capacity_rows = 0;
  std::uint64_t discarded_records = 0;
};
struct SignedResult {
  std::uint64_t ordinal;
  SetOperation operation;
  storage::Tuple tuple;
};
struct DeltaStage {
  OccurrenceId occurrence;
  // One-based position in the physical table's full route list, including
  // preceding filtered/count-only routes. Summaries can therefore have gaps.
  std::uint64_t prefix;
  bool before_answer, after_answer;
  std::uint64_t changed_keys, candidates, accepted, rejected;
  // Zero-based interval in the committed spool. Scalar EXISTS replacement
  // records are prepared once at epoch end, outside these core route ranges.
  std::size_t output_begin, output_count, live_rows;
};
struct LiveSnapshot {
  std::uint64_t sequence;
  // Parent-before-child plan.enumeration().steps order, full E keys.
  std::vector<Relation> factors;
};

// Exact set deltas with ordered replay and canonical comparison strategies.
// profile() separates bounded post-preparation route producer actions from
// ordered/value costs, finalization and public eager atomic startup.
// Output remains private until the complete physical epoch commits.
// No constant public startup, durable delivery or spill guarantee is established.
class DeltaRuntime {
  friend struct memory::detail::Access;
  struct Impl;
 public:
  class PendingEpoch;
  class Epoch {
   public:
    Epoch(const Epoch&) = delete;
    Epoch& operator=(const Epoch&) = delete;
    Epoch(Epoch&&) noexcept;
    Epoch& operator=(Epoch&&) noexcept;
    ~Epoch();
    [[nodiscard]] bool active() const noexcept;
    [[nodiscard]] std::uint64_t sequence() const;
    [[nodiscard]] const PhysicalEpoch& input() const;
    [[nodiscard]] const DeltaMetrics& metrics() const;
    [[nodiscard]] const DeltaTimings& timings() const;
    [[nodiscard]] std::span<const DeltaStage> stages() const;
    [[nodiscard]] const storage::TupleLayout& layout() const;
    [[nodiscard]] std::size_t remaining() const;
    // Moves one already committed owning record without allocation. Finishing
    // or discarding output permits the next input; neither rolls back input.
    [[nodiscard]] std::optional<SignedResult> next();
    // Acknowledge only after callback success. An exception retains this row
    // for retry/discard. Records are borrowed until the callback returns; a sink
    // which accepts then throws may observe duplicates on retry.
    [[nodiscard]] bool deliver_one(const std::function<void(const SignedResult&)>& sink);
    [[nodiscard]] bool deliver_one(const std::function<void(const SignedResult&)>& serialize,
        const std::function<void(const SignedResult&)>& sink);
    void discard() noexcept;
   private:
    friend class QuerySession;
    void visit_complete(void(*)(const SignedResult&,void*),void*) const;
    void acknowledge_complete() noexcept;
    friend class DeltaRuntime;
    friend class PendingEpoch;
    struct Data;
    explicit Epoch(std::shared_ptr<Data> data) noexcept;
    std::shared_ptr<Data> data_;
  };
  class PendingEpoch {
   public:
    PendingEpoch(const PendingEpoch&) = delete;
    PendingEpoch& operator=(const PendingEpoch&) = delete;
    PendingEpoch(PendingEpoch&&) noexcept;
    PendingEpoch& operator=(PendingEpoch&&) noexcept;
    ~PendingEpoch();
    [[nodiscard]] bool active() const noexcept;
    [[nodiscard]] DeltaState state() const noexcept;
    [[nodiscard]] std::uint64_t sequence() const;
    [[nodiscard]] const DeltaMetrics& metrics() const;
    [[nodiscard]] const DeltaTimings& timings() const;
    [[nodiscard]] std::span<const DeltaStage> stages() const;
    // Stages at most one accepted core row. This is private progress, not a
    // published record. Propagation/preparation/finalization remain separate
    // potentially data-dependent phases; see profile().
    [[nodiscard]] DeltaStep step();
    void pause();
    void resume();
    // Disable output retention. Subsequent step/drain still runs every required
    // internal row/alias. Destruction/rollback instead abort unpublished input.
    void start_drain();
    // Finish preparation with the current retention policy, resuming a pause.
    // Only start_drain/discard disable retention; apply uses retaining drain.
    void drain();
    [[nodiscard]] Epoch commit();
    [[nodiscard]] Epoch discard();
    void rollback() noexcept;
   private:
    friend class DeltaRuntime;
    struct Data;
    explicit PendingEpoch(resource::AccountedUnique<Data> data) noexcept;
    resource::AccountedUnique<Data> data_;
  };
  explicit DeltaRuntime(PhysicalPlan plan, DeltaOptions options = {});
  explicit DeltaRuntime(CompiledProgram plan,DeltaOptions options = {});
  [[nodiscard]] static DeltaRuntime initialize(PhysicalPlan plan,const Database& database,
      DeltaOptions options={},BuildOptions build={});
  [[nodiscard]] static DeltaRuntime initialize(CompiledProgram plan,const Database& database,
      DeltaOptions options={},BuildOptions build={});
  [[nodiscard]] DeltaRuntime rebuilt(BuildOptions build={}) const;
  // Bootstrap a checked alternative at this exact committed epoch, under the
  // original query account while this owner remains intact. The candidate is
  // lowered from this owner's complete immutable source, not a caller image.
  // ReplanLimits bound compiler work; BuildOptions bound snapshot/build/live
  // work. This does not publish a session switch or perform ordered catch-up.
  [[nodiscard]] DeltaRuntime rebuilt_for(const planner::MinimumHeightCandidate&,
      BuildOptions build={},const program::ReplanLimits& replan={}) const;
  // Native runtime image component. Requires a writer-ready barrier with no
  // private epoch, result cursor or unread output. Restores source rows and
  // exact committed sequence by rebuilding support/index/live state. The
  // supplied immutable program and semantic options must match the image;
  // the receiving query's memory cap may differ. Diagnostic histories reset.
  // Session positions/windows and durable file publication are separate O04
  // integration work, not supplied by this runtime-only component.
  [[nodiscard]] recovery::EncodedImage checkpoint_image(recovery::ImageLimits limits={}) const;
  [[nodiscard]] static DeltaRuntime restore_image(CompiledProgram,std::string_view,
      DeltaOptions options={},BuildOptions build={},recovery::ImageLimits limits={});
  ~DeltaRuntime();
  DeltaRuntime(const DeltaRuntime&) = delete;
  DeltaRuntime& operator=(const DeltaRuntime&) = delete;
  DeltaRuntime(DeltaRuntime&&) noexcept;
  DeltaRuntime& operator=(DeltaRuntime&&) noexcept;
  [[nodiscard]] const CompiledProgram& plan() const;
  // Account-wide native requests; public exports and caller allocations are separate.
  [[nodiscard]] resource::MemoryStatistics accounted_memory_statistics() const;
  [[nodiscard]] ObservationSnapshot observations() const;
  void configure_workload_statistics(const workload::Options&);
  void reset_workload_statistics();
  [[nodiscard]] workload::Snapshot workload_statistics() const;
  [[nodiscard]] workload::Options workload_statistics_options() const;
  [[nodiscard]] std::optional<CursorObservation> last_cursor_observation() const;
  [[nodiscard]] CommittedStateGauges committed_state_gauges() const;
  [[nodiscard]] CapturedStateGauges capture_state_gauges() const;
  [[nodiscard]] statistics::OwnerCapture capture_statistics(const statistics::OwnerRequest&,statistics::Limits limits={}) const;
  [[nodiscard]] statistics::OwnerCapture capture_statistics_view(statistics::OwnerRequestView,statistics::Limits limits={}) const;
  [[nodiscard]] statistics::Freshness statistics_freshness(const statistics::OwnerCapture&,std::uint64_t max_event_lag=0) const;
  [[nodiscard]] statistics::CombinedCapture capture_combined_statistics(const statistics::OwnerRequest&,statistics::Limits limits={}) const;
  [[nodiscard]] statistics::CombinedCapture capture_combined_statistics_view(statistics::OwnerRequestView,statistics::Limits limits={}) const;
  // Explicit diagnostic declaration; affects only future attempt bindings.
  // Caller constructs immutable labels before mutation. No parsing or clocks.
  void declare_benchmark_context(std::shared_ptr<const DeclaredBenchmarkContext>);
  [[nodiscard]] ObservationTrace observation_trace() const;
  [[nodiscard]] CapturedObservationTrace capture_observation_trace() const;
  [[nodiscard]] const DeltaOptions& options() const;
  [[nodiscard]] DeltaCompletion completion() const;
  [[nodiscard]] DeltaRuntimeProfile profile() const;
  [[nodiscard]] SupportOwnerId owner() const;
  [[nodiscard]] std::uint64_t sequence() const;
  [[nodiscard]] DeltaMode mode() const;
  // Selected execution core (keyed unless the program or options need the reference core).
  [[nodiscard]] DeltaEngine engine() const;
  // Keyed core: collect retired keys now and release excess index capacity.
  void collect_garbage();
  [[nodiscard]] storage::keyed::GcStatistics gc_statistics() const;
  [[nodiscard]] bool ready() const;
  [[nodiscard]] DeltaState state() const;
  [[nodiscard]] bool has_answer() const;
  [[nodiscard]] const storage::TupleLayout& result_layout() const;
  [[nodiscard]] const DeltaMetrics& bootstrap_metrics() const;
  // Requires a quiescent writer-ready barrier. Failed bootstrap preserves the
  // previous mode/cache. Maintenance updates never use an old live image.
  [[nodiscard]] DeltaMetrics set_mode(DeltaMode mode);
  [[nodiscard]] PendingEpoch begin(const PhysicalSetUpdate& update);
  // Native adapters borrow row values only for this call; pending storage owns
  // its imported rows/pins before returning. No external Row export is needed.
  [[nodiscard]] PendingEpoch begin_view(const PhysicalUpdateView& update);
  [[nodiscard]] Epoch apply(const PhysicalSetUpdate& update);
  [[nodiscard]] Epoch apply_view(const PhysicalUpdateView& update);
  [[nodiscard]] SupportRuntime::ResultCursor results(ResultCursorOptions options = {}) const;
  [[nodiscard]] SupportRuntime::ResultCursor core_results(ResultCursorOptions options = {}) const;
  [[nodiscard]] SupportRuntime::EpochView current_view(EpochViewOptions options = {}) const;
  [[nodiscard]] PhysicalSnapshot snapshot() const;
  [[nodiscard]] std::optional<LiveSnapshot> live_snapshot() const;
  [[nodiscard]] PhysicalStorageStatistics storage_statistics() const;
  [[nodiscard]] const BuildMetrics& initialization_metrics() const;
  [[nodiscard]] InitializationContext initialization_context() const;
  [[nodiscard]] CanonicalDeltaState canonical_state() const;
  [[nodiscard]] InvariantReport inspect_invariants(InspectionOptions options={}) const;
  void check_invariants() const;
 private:
  friend class QuerySession;
  friend struct ranking::detail::OwnerAccess;
  friend struct reoptimization::detail::Access;
  [[nodiscard]] bool same_sources(const DeltaRuntime&,reoptimization::detail::Budget&) const;
  friend class ::crown::observability::ModeDescriptor;
  [[nodiscard]] const CompiledProgram& compiled_program() const;
  [[nodiscard]] recovery::ImageBinding checkpoint_binding() const;
  [[nodiscard]] static DeltaRuntime restore_session_image(CompiledProgram,std::string_view,
      DeltaOptions,BuildOptions,recovery::ImageLimits,const WindowCheckpoint*,std::uint64_t matching_work,
      const workload::Options*,std::shared_ptr<detail::StorageWorkContext> context={});
#ifdef CROWN_RUNTIME_TESTING
  friend class RuntimeTestProbe;
#endif
  DeltaRuntime(PhysicalRuntime physical,DeltaOptions options,BuildOptions build);
  [[nodiscard]] Impl& impl() const;
  std::shared_ptr<Impl> impl_;
};
}  // namespace crown::runtime
