#pragma once

#include "crown/ir/physical.hpp"
#include "crown/storage/reference.hpp"
#include "crown/runtime/initialization.hpp"
#include "crown/runtime/inspection.hpp"
#include "crown/runtime/observation.hpp"
#include <limits>
#include <memory>

namespace crown::runtime {
class PhysicalRuntime;
struct SatisfiedChildCount { std::size_t value = 0; auto operator<=>(const SatisfiedChildCount&) const = default; };
struct ProjectionSupportCount { std::uint64_t value = 0; auto operator<=>(const ProjectionSupportCount&) const = default; };
[[nodiscard]] ProjectionSupportCount increment_support(ProjectionSupportCount value, std::uint64_t limit = std::numeric_limits<std::uint64_t>::max());
[[nodiscard]] ProjectionSupportCount decrement_support(ProjectionSupportCount value);

struct SupportOwnerId { std::uint64_t value; auto operator<=>(const SupportOwnerId&) const = default; };
enum class SupportRole { records, survivors, parent_support, visible };
struct SupportHandle {
  SupportOwnerId owner;
  NodeId node;
  SupportRole role;
  TupleId tuple;
  auto operator<=>(const SupportHandle&) const = default;
};
enum class PropagationOrder { fifo, lifo };
struct SupportOptions {
  std::optional<std::uint64_t> work_limit = 1000000;
  std::uint64_t support_limit = std::numeric_limits<std::uint64_t>::max();
  PropagationOrder order = PropagationOrder::fifo;
  bool capture_transitions = false;
  ObservationOptions observation = {};
};
struct NativeSetUpdate {
  std::uint64_t sequence;
  NodeId node;
  SetOperation operation;
  Row values;  // Complete logical scope, ascending variable ID; not a physical row.
};
struct SupportMetrics {
  std::uint64_t work = 0;
  // Historical whole-state copy counters. Journal backend keeps these zero.
  std::uint64_t copied_rows = 0;
  std::uint64_t copied_index_memberships = 0;
  std::uint64_t copied_metadata_entries = 0;
  std::uint64_t copied_child_flags = 0;
  std::uint64_t native_record_visits = 0;
  std::uint64_t child_key_probes = 0;
  std::uint64_t child_key_events = 0;
  std::uint64_t survivor_transitions = 0;
  std::uint64_t parent_key_transitions = 0;
  std::uint64_t visible_key_transitions = 0;
  std::uint64_t candidates_created = 0;
  std::uint64_t candidates_reclaimed = 0;
  std::uint64_t storage_changes = 0;
  std::uint64_t metadata_changes = 0;
  std::uint64_t saved_child_flags = 0;
  std::uint64_t journal_records = 0;
  std::uint64_t events_enqueued = 0;
  std::uint64_t events_applied = 0;
  std::uint64_t queue_peak = 0;
};
struct MembershipTransition {
  SupportHandle handle;
  SetOperation operation;
  storage::Tuple tuple;  // Owns a deleted key too; no borrowed record pointer.
  std::uint64_t cause = 0;
};
struct SupportValueState {
  bool member = false;
  std::optional<SatisfiedChildCount> satisfied;
  std::vector<bool> child_present;
  std::optional<ProjectionSupportCount> support;
};
struct JournalRecord {
  std::uint64_t ordinal;
  std::uint64_t cause;
  SupportHandle handle;
  SupportValueState before, after;
  storage::TupleArena::Pin retained;
  [[nodiscard]] const storage::Tuple& tuple() const { return retained.get(); }
};
enum class SupportEventKind { native_update, child_key };
struct PropagationEvent {
  std::uint64_t id, cause, sequence, applied_ordinal;
  SupportEventKind kind;
  NodeId target;
  std::optional<std::size_t> child_slot;
  SupportHandle source;
  SetOperation operation;
  storage::Tuple key;
  bool before, after;
};
struct SupportJournal {
  SupportJournal() = default;
  SupportJournal(const SupportJournal&) = delete;
  SupportJournal& operator=(const SupportJournal&) = delete;
  std::uint64_t sequence = 0;
  std::vector<JournalRecord> records;
  // Optional causal trace; accounting and record retention are always active.
  std::vector<PropagationEvent> events;
 private:
  friend class SupportRuntime;
  std::vector<std::pair<RelationId,storage::ReferenceTable::Journal>> storage_;
};
struct SupportEpoch {
  std::uint64_t sequence;
  bool native_changed;
  bool has_answer;
  SupportMetrics metrics;
  // Local membership changes, not full-answer deltas. The journal owns the
  // affected before/after values and optional causal trace.
  std::vector<MembershipTransition> transitions;
  std::shared_ptr<const SupportJournal> journal;
};
struct SupportRecordSnapshot {
  storage::Tuple tuple;
  SupportHandle handle;
  SatisfiedChildCount satisfied;
  std::vector<bool> child_present;
  bool survives;
};
struct ProjectionKeySnapshot {
  storage::Tuple key;
  SupportHandle handle;
  ProjectionSupportCount support;
};
struct NodeSupportSnapshot {
  NodeId node;
  NodeKind kind;
  std::vector<SupportRecordSnapshot> records;
  std::vector<storage::Tuple> survivors;
  std::vector<ProjectionKeySnapshot> parent_keys;
  std::optional<std::vector<ProjectionKeySnapshot>> visible_keys;
};
struct SupportSnapshot {
  std::uint64_t sequence;
  bool has_answer;
  std::vector<NodeSupportSnapshot> nodes;
};

enum class ResultView { core, sql };
enum class SnapshotSide { before, after };
struct VariableBinding { VariableId variable; Value value; };
using FixedAssignment = std::vector<VariableBinding>;
// Nullopt selects the complete C* program and original core head. A subtree
// root selects its C* descendants and outputs their sorted visible variables.
struct VisibleFragment { std::optional<NodeId> root; };
// Full-assignment traversal over survivor factors. A root selects its entire
// subtree, including nodes outside C*. Alternatively nodes selects an exact
// set of factors; an empty set is the nullary identity. If both are absent,
// select the whole tree. Root and nodes are mutually exclusive. Variables are
// sorted, with hidden witnesses retained rather than projected away.
struct WitnessFragment {
  std::optional<NodeId> root = std::nullopt;
  std::optional<std::vector<NodeId>> nodes = std::nullopt;
};
struct EpochViewOptions { std::optional<std::uint64_t> work_limit = 1000000; };
struct EpochViewMetrics {
  std::uint64_t work = 0, journal_records = 0, membership_changes = 0;
  std::uint64_t restored_rows = 0, excluded_rows = 0;
  std::uint64_t restored_key_entries = 0, restored_bucket_entries = 0, key_fields = 0;
};
enum class ResultCursorState { active, exhausted, cancelled, failed };
struct ResultCursorOptions { std::optional<std::uint64_t> work_limit = 1000000; };
struct CursorWork {
  std::uint64_t work = 0, calls = 0, route_checks = 0, descriptor_steps = 0, frame_initializations = 0;
  std::uint64_t cursor_opens = 0, cursor_advances = 0, frame_closes = 0;
  std::uint64_t tuple_lookups = 0, selected_rows = 0, bucket_lookups = 0;
  std::uint64_t key_fields = 0, equality_checks = 0, output_fields = 0, rows_emitted = 0;
  std::uint64_t binding_checks = 0, binding_rejections = 0, direct_lookups = 0, overlay_rows = 0;
  std::uint64_t fragment_steps = 0, binding_values = 0;
  std::uint64_t witness_probes = 0, witness_rows = 0, join_rejections = 0;
};
struct ResultCursorMetrics {
  CursorWork startup, results, termination, failed, last;
  std::uint64_t total_work = 0, max_result_work = 0;
  // Uncharged, mandatory cleanup on cancellation/failure, at most frame count.
  std::size_t cleanup_frames = 0;
};

enum class CursorObservationSource { committed_results, epoch_visible, epoch_witnesses, epoch_keys, epoch_bucket };
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

// Logical support kernel with affected-record metadata/storage undo. Returned
// journals retain affected values, not a frozen snapshot of the whole query.
class SupportRuntime {
  struct Impl;
 public:
  class EpochView;
  class PendingEpoch;
  // Lazy N-ary product over compiled relations (live E for results()). A read lease blocks mutations,
  // including no-ops, until exhaustion/cancellation; ordinary reads still work.
  // Rows are owning values. No whole relation/result snapshot is constructed.
  class ResultCursor {
   public:
    ResultCursor(const ResultCursor&) = delete;
    ResultCursor& operator=(const ResultCursor&) = delete;
    ResultCursor(ResultCursor&&) noexcept;
    ResultCursor& operator=(ResultCursor&&) noexcept;
    ~ResultCursor();
    [[nodiscard]] bool active() const noexcept;
    [[nodiscard]] ResultCursorState state() const;
    [[nodiscard]] std::uint64_t sequence() const;
    [[nodiscard]] SupportOwnerId owner() const;
    [[nodiscard]] const storage::TupleLayout& layout() const;
    [[nodiscard]] const ResultCursorMetrics& metrics() const;
    [[nodiscard]] CursorObservation observation() const;
    // Exhausted/cancelled cursors return nullopt repeatedly. A next failure
    // closes the lease; a failed or moved-from cursor rejects further next().
    [[nodiscard]] std::optional<storage::Tuple> next();
    void cancel() noexcept;
   private:
    friend class SupportRuntime;
    friend class EpochView;
    struct Data;
    explicit ResultCursor(std::unique_ptr<Data> data) noexcept;
    std::unique_ptr<Data> data_;
  };
  // Journal-backed immutable relation context. Copies and cursors
  // share one read lease. Pending rollback invalidates and closes its cursors;
  // commit preserves them and blocks subsequent inputs until all views close.
  class EpochView {
   public:
    EpochView(const EpochView&) noexcept = default;
    EpochView& operator=(const EpochView&) noexcept = default;
    EpochView(EpochView&&) noexcept = default;
    EpochView& operator=(EpochView&&) noexcept = default;
    [[nodiscard]] bool valid() const noexcept;
    [[nodiscard]] bool tentative() const noexcept;
    [[nodiscard]] SnapshotSide side() const;
    [[nodiscard]] std::uint64_t sequence() const;
    [[nodiscard]] SupportOwnerId owner() const;
    [[nodiscard]] const EpochViewMetrics& metrics() const;
    [[nodiscard]] bool has_answer() const;
    [[nodiscard]] ResultCursor results(ResultCursorOptions options = {}) const;
    // Projected completions retain the core/visible-fragment output schema.
    // Hidden bindings are existential witness restrictions, not extra output.
    [[nodiscard]] ResultCursor completions(const FixedAssignment& fixed, VisibleFragment fragment = {}, ResultCursorOptions options = {}) const;
    // Local survivor-factor assignments; no outside-parent restriction.
    // Bindings absent from the selected factors are validated then ignored.
    [[nodiscard]] ResultCursor witnesses(const FixedAssignment& fixed = {}, WitnessFragment fragment = {}, ResultCursorOptions options = {}) const;
    // Owner-only factor scan in this context, including globally unlive keys.
    // Outputs the node's complete sorted E key, without joining other factors.
    [[nodiscard]] ResultCursor visible_keys(NodeId node, ResultCursorOptions options = {}) const;
    // Full local E keys matching this nonroot node's parent separator, in
    // sorted separator-variable order. Uses its compiled separator index.
    [[nodiscard]] ResultCursor visible_bucket(NodeId node, const Row& separator, ResultCursorOptions options = {}) const;
    void close() noexcept;
   private:
    friend class SupportRuntime;
    friend class PendingEpoch;
    friend class ResultCursor;
    struct Group;
    struct Data;
    explicit EpochView(std::shared_ptr<Data> data) noexcept;
    std::shared_ptr<Data> data_;
  };
  // Owner-only tentative epoch. All staged rows have one polarity; every
  // stage drains its upward work while public state readers report busy.
  // Failed staging closes/rolls back the whole epoch, except that a view-held
  // prefix reports busy and stays active. Commit is the only publication
  // boundary. Preview/snapshot values must remain unpublished.
  class PendingEpoch {
   public:
    PendingEpoch(const PendingEpoch&) = delete;
    PendingEpoch& operator=(const PendingEpoch&) = delete;
    PendingEpoch(PendingEpoch&&) noexcept;
    PendingEpoch& operator=(PendingEpoch&&) noexcept;
    ~PendingEpoch();
    [[nodiscard]] bool active() const noexcept;
    [[nodiscard]] bool stage(NodeId node, const Row& values);
    [[nodiscard]] const SupportEpoch& preview() const;
    [[nodiscard]] SupportSnapshot snapshot() const;
    // Freeze a drained prefix. Further stages reject while a view/cursor is
    // held. Releasing every view allows staging to resume. View construction
    // failures leave the pending epoch active; staging failures other than
    // this prefix-busy rejection auto-abort.
    [[nodiscard]] EpochView view(SnapshotSide side, EpochViewOptions options = {});
    // Invalid/closed tokens reject before publication. Once active, commit
    // only moves prepared output, commits noexcept undo scopes, and advances
    // sequence; no allocation is performed.
    [[nodiscard]] SupportEpoch commit();
    void rollback() noexcept;
   private:
    friend class SupportRuntime;
    friend class PhysicalRuntime;
    struct Checkpoint {
      SupportOwnerId owner;
      std::uint64_t sequence, prefix;
      std::size_t records;
      bool has_answer;
    };
    [[nodiscard]] Checkpoint checkpoint() const;
    [[nodiscard]] EpochView stage_view(const Checkpoint& before, SnapshotSide side, EpochViewOptions options);
    [[nodiscard]] std::span<const JournalRecord> stage_records(const Checkpoint& before) const;
    struct Data;
    explicit PendingEpoch(std::unique_ptr<Data> data) noexcept;
    std::unique_ptr<Data> data_;
  };
  explicit SupportRuntime(PhysicalPlan plan, SupportOptions options = {});
  ~SupportRuntime();
  SupportRuntime(const SupportRuntime&) = delete;
  SupportRuntime& operator=(const SupportRuntime&) = delete;
  SupportRuntime(SupportRuntime&&) noexcept;
  SupportRuntime& operator=(SupportRuntime&& other) noexcept;
  [[nodiscard]] const PhysicalPlan& plan() const;
  [[nodiscard]] ObservationSnapshot observations() const;
  // Latest enabled cursor lifecycle publication; not an aggregate or update metric.
  [[nodiscard]] std::optional<CursorObservation> last_cursor_observation() const;
  // Explicit allocating read of committed relation cardinalities, even when off.
  [[nodiscard]] CommittedStateGauges committed_state_gauges() const;
  [[nodiscard]] ObservationTrace observation_trace() const;
  [[nodiscard]] const SupportOptions& options() const;
  [[nodiscard]] SupportOwnerId owner() const;
  [[nodiscard]] std::uint64_t sequence() const;
  [[nodiscard]] bool ready() const;
  [[nodiscard]] bool has_answer() const;
  [[nodiscard]] PendingEpoch begin_epoch(std::uint64_t sequence, SetOperation operation);
  [[nodiscard]] const storage::TupleLayout& result_layout(ResultView view = ResultView::core) const;
  [[nodiscard]] SupportEpoch apply(const NativeSetUpdate& update);
  [[nodiscard]] ResultCursor results(ResultCursorOptions options = {}, ResultView view = ResultView::core) const;
  [[nodiscard]] EpochView current_view(EpochViewOptions options = {}) const;
  [[nodiscard]] ResultCursor completions(const FixedAssignment& fixed, VisibleFragment fragment = {}, ResultCursorOptions options = {}) const;
  [[nodiscard]] ResultCursor witnesses(const FixedAssignment& fixed = {}, WitnessFragment fragment = {}, ResultCursorOptions options = {}) const;
  [[nodiscard]] SupportSnapshot snapshot() const;  // Owning diagnostic copy.
  [[nodiscard]] std::optional<SupportHandle> find(NodeId node, SupportRole role, const Row& values) const;
  [[nodiscard]] std::optional<storage::Tuple> get(SupportHandle handle) const;
  [[nodiscard]] storage::ArenaStatistics storage_statistics() const;
  [[nodiscard]] CanonicalSupportState canonical_state() const;
  [[nodiscard]] InvariantReport inspect_invariants(InspectionOptions options={}) const;
  void check_invariants() const;
 private:
  friend class PhysicalRuntime;
#ifdef CROWN_RUNTIME_TESTING
  friend class RuntimeTestProbe;
#endif
  void initialize_native(std::span<const detail::NativeSeed> seeds,BuildOptions options,BuildMetrics& metrics);
  void seed_sequence(std::uint64_t sequence) noexcept;
  [[nodiscard]] Relation record_rows(NodeId node) const;
  [[nodiscard]] std::shared_ptr<detail::ObservationState> observation_state() const;
  [[nodiscard]] Impl& impl() const;
  std::shared_ptr<Impl> impl_;
};
}  // namespace crown::runtime
