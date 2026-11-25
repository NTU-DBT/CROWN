#pragma once

#include "crown/annotations/policy.hpp"
#include "crown/ir/program.hpp"
#include "crown/resource/owner_allocator.hpp"
#include "crown/storage/layout.hpp"
#include "crown/storage/keyed.hpp"
#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <span>
#include <string_view>
#include <utility>
#include <variant>
#include <vector>

namespace crown::runtime { class WeightedRuntime; namespace detail { class SqlColdRebuild; } }
namespace crown::runtime::weighted {
using annotations::Multiplicity;
template<class T> using OutputVector = std::vector<T, resource::OwnerAllocator<T>>;
struct Options {
  // Per logical epoch, shared across stages; nullopt disables this counter cap.
  std::optional<std::uint64_t> work_limit = 1000000;
  std::uint64_t multiplicity_limit = UINT64_MAX;
  std::uint64_t memory_limit_bytes = 256ULL * 1024 * 1024;
  // Owning diagnostic histories add copies/pins. Events imply change capture.
  bool capture_changes = false;
  bool capture_events = false;
  storage::keyed::GcOptions gc{};  // keyed core only
};
// Shapes are compiled/checked by the existing compiler. This binding explicitly
// changes the execution semantics; it is not an exact-set plan/cache identity.
struct Binding {
  std::array<char,64> shape_sha256, weighted_sha256;
  std::uint64_t multiplicity_limit;
  bool operator==(const Binding&) const = default;
};
struct Profile {
  std::string_view semantics = "exact_nonnegative_multiplicity";
  std::string_view arithmetic = annotations::MultiplicityPolicy::name;
  std::string_view input = "logical_native_tuple_weight_replacement_v1";
  std::string_view messages = "full_subtree_sum_product_with_empty_key_root_summary";
  std::string_view output = "distinct_core_tuple_and_exact_multiplicity_v1";
  std::string_view maintenance = "measured_affected_rows_and_numeric_events; no_Boolean_update_bound";
};
struct Replacement {
  NodeId node;
  Row values; // Complete native scope in ascending variable-ID order.
  Multiplicity before, after; // Zero means absent; before must match the owner.
};
struct Update {
  std::uint64_t sequence;
  Replacement replacement;
};
struct Metrics {
  std::uint64_t work = 0, native_inputs = 0, native_changes = 0;
  std::uint64_t row_visits = 0, separator_probes = 0, child_slots_copied = 0;
  std::uint64_t multiplications = 0, message_replacements = 0;
  std::uint64_t row_value_changes = 0, row_membership_changes = 0, message_membership_changes = 0;
  std::uint64_t candidates_created = 0, candidates_removed = 0;
  std::uint64_t metadata_changes = 0, storage_changes = 0, journal_records = 0;
  std::uint64_t factor_replacements = 0, factor_membership_changes = 0, factor_multiplications = 0;
  std::uint64_t factor_slots_visited = 0;
  std::uint64_t events_enqueued = 0, events_applied = 0, queue_peak = 0;
  // The one shared indexed grant consumed, including reserved undo work and
  // explicitly requested private capture. Ordered storage has no native grant.
  storage::IndexWork native_grant_consumed{};
};
enum class Phase { pending, committed, aborted };
struct Attempt { std::uint64_t sequence; Phase phase; Metrics metrics; };

// Live records own one cached array. Diagnostic copies are immutable through
// Record; they are made only on explicit capture. Generalized local weight is 1.
struct RecordValue {
  Multiplicity local, subtree, factor; // factor excludes enumerated C* children.
  std::size_t supported_children = 0;
  std::vector<Multiplicity,resource::MemoryAllocator<Multiplicity>> children;
  RecordValue(const resource::MemoryAccount&, resource::MemoryAttribution, std::size_t,
              resource::MemoryPurpose = resource::MemoryPurpose::support_metadata);
};
using Record = std::shared_ptr<const RecordValue>;
struct RowChange {
  NodeId node;
  storage::AccountedTupleArena::Pin tuple;
  Record before, after; // Null is absent, distinct from an existing zero-valued row.
  std::uint64_t cause;
};
struct MessageChange {
  NodeId node;
  storage::AccountedTupleArena::Pin key;
  Multiplicity before, after;
  std::uint64_t cause;
};
struct FactorChange {
  NodeId node;
  storage::AccountedTupleArena::Pin key;
  Multiplicity before, after;
  std::uint64_t cause;
};
using Change = std::variant<RowChange, MessageChange, FactorChange>;
enum class EventKind { native_weight, child_message };
// Committed native events contain logical row totals. An aborted journal is a
// partial attempt: its failing input may still contain requested replacement
// weights or contribution shares. applied_ordinal marks execution entry, not
// completion; do not replay aborted diagnostics as committed transitions.
struct Event {
  std::uint64_t id, cause, applied_ordinal;
  EventKind kind;
  NodeId target;
  std::optional<std::size_t> edge;
  std::optional<std::size_t> message_record;
  Multiplicity before, after;
};
struct Journal {
  std::uint64_t sequence;
  Phase phase = Phase::pending;
  OutputVector<Change> records;
  OutputVector<Event> events;
  Journal(const resource::MemoryAccount&, std::uint64_t);
};

// Logical-CQ output only. These facts confer no SQL source or checked-proof authority.
// Numeric bag capture and DISTINCT support capture are separate opt-in meanings.
// enabled keeps its existing exact numeric-difference contract.
enum class DeltaCapture { disabled, enabled, support };
struct SignedMagnitude { bool negative=false; Multiplicity magnitude{}; };
struct BagDelta { storage::AccountedTuple tuple; SignedMagnitude change; };
struct BagDeltaMetrics {
  std::uint64_t work=0, rows_visited=0, fields=0, scalar_bytes=0;
  // mutations counts charged insert/update/release units, including prefunded cleanup.
  std::uint64_t factor_reads=0, multiplications=0, comparisons=0, terms=0, mutations=0;
};
// A committed handle owns nonzero consolidated facts under the original account.
// Iterators/spans borrow this handle. Order is unspecified; no lookup index escapes.
class BagDeltas {
 public:
  struct Data;
  BagDeltas() noexcept=default;
  [[nodiscard]] explicit operator bool() const noexcept { return bool(data_); }
  [[nodiscard]] std::span<const BagDelta> entries() const &;
  std::span<const BagDelta> entries() const &&=delete;
  [[nodiscard]] const BagDeltaMetrics& metrics() const &;
  const BagDeltaMetrics& metrics() const &&=delete;
 private:
  friend class ::crown::runtime::WeightedRuntime;
  explicit BagDeltas(std::shared_ptr<const Data> value) noexcept:data_(std::move(value)) {}
  std::shared_ptr<const Data> data_;
};


// DISTINCT support only: each entry is an encoded native tuple with unit signed
// magnitude. This separate handle never replaces numeric BagDeltas authority.
// The shared accumulator is private to one epoch; no result-count graph exists.
class SupportDeltas {
 public:
  SupportDeltas() noexcept=default;
  [[nodiscard]] explicit operator bool() const noexcept { return bool(data_); }
  [[nodiscard]] std::span<const BagDelta> entries() const &;
  std::span<const BagDelta> entries() const &&=delete;
  [[nodiscard]] const BagDeltaMetrics& metrics() const &;
  const BagDeltaMetrics& metrics() const &&=delete;
 private:
  friend class ::crown::runtime::WeightedRuntime;
  explicit SupportDeltas(std::shared_ptr<const BagDeltas::Data> value) noexcept:data_(std::move(value)) {}
  std::shared_ptr<const BagDeltas::Data> data_;
};

struct Epoch {
  std::uint64_t sequence;
  bool changed = false;
  Multiplicity before, after; // Full-root summary, not projected bag output.
  Metrics metrics;
  std::shared_ptr<const Journal> journal; // Null when both capture options are off.
  BagDeltas bag_deltas{}; // Empty handle until commit, or outside numeric capture.
  SupportDeltas support_deltas{}; // Unit support changes only; empty outside support capture.
};

struct RowSnapshot { storage::AccountedTuple tuple; Record value; };
struct MessageSnapshot { storage::AccountedTuple key; Multiplicity value; };
struct NodeSnapshot {
  NodeId node;
  OutputVector<RowSnapshot> records;
  OutputVector<MessageSnapshot> messages;
  OutputVector<MessageSnapshot> factors; // Visible keys, not full separator messages.
  NodeSnapshot(const resource::MemoryAccount&, NodeId);
};
struct Snapshot {
  std::uint64_t owner, sequence;
  bool tentative;
  Binding binding;
  CompiledProgram shape;
  Multiplicity root;
  OutputVector<NodeSnapshot> nodes;
};
struct SnapshotLimits { std::uint64_t rows = 65536; };

// Compressed bag output: one owning row per distinct core tuple. The logical
// expanded size is the sum of multiplicities, not the number of cursor records.
struct Result { storage::Tuple tuple; Multiplicity multiplicity; };
enum class CursorState { active, exhausted, cancelled, failed };
struct CursorOptions { std::optional<std::uint64_t> work_limit = 1000000; };
struct CursorMetrics {
  std::uint64_t work=0, calls=0, frame_initializations=0, cursor_opens=0, advances=0;
  std::uint64_t key_fields=0, factor_reads=0, multiplications=0, equality_checks=0;
  std::uint64_t output_fields=0, rows_emitted=0, frame_closes=0, cleanup_frames=0;
  std::uint64_t startup_work=0, last_work=0, max_result_work=0, termination_work=0, failed_work=0;
  storage::IndexWork native_grant_consumed{};
};
}  // namespace crown::runtime::weighted

namespace crown::runtime::keyed { class WeightSink; }
namespace crown::runtime {
// Direct-CQ shapes maintain exact weighted subtrees and projected multiplicities.
// Nullable SQL source admission uses SqlRowsRuntime; recovery remains separate.
// See docs/weighted_enumeration.md for the local factor proof.
// Single caller, no recursion, no arbitrary-semiring backend registration.
class WeightedRuntime {
  struct Impl;
 public:
  class ResultCursor {
   public:
    // Unspecified tuple order; one caller may interleave readers. The last
    // result still holds its lease until terminal next(), cancel or destruction.
    ResultCursor(const ResultCursor&)=delete;
    ResultCursor& operator=(const ResultCursor&)=delete;
    ResultCursor(ResultCursor&&) noexcept;
    ResultCursor& operator=(ResultCursor&&) noexcept;
    ~ResultCursor();
    [[nodiscard]] bool active() const noexcept;
    [[nodiscard]] weighted::CursorState state() const;
    [[nodiscard]] std::uint64_t sequence() const;
    [[nodiscard]] std::uint64_t owner() const;
    [[nodiscard]] const weighted::Binding& binding() const &;
    const weighted::Binding& binding() const &&=delete;
    [[nodiscard]] const storage::TupleLayout& layout() const &;
    const storage::TupleLayout& layout() const &&=delete;
    [[nodiscard]] const weighted::CursorMetrics& metrics() const &;
    const weighted::CursorMetrics& metrics() const &&=delete;
    // Exhausted/cancelled => nullopt; failed => invalid_cursor. Returned rows
    // own their payload and survive cursor/runtime destruction.
    [[nodiscard]] std::optional<weighted::Result> next();
    void cancel() noexcept;
   private:
    friend class WeightedRuntime;
    struct Data;
    explicit ResultCursor(resource::AccountedUnique<Data>) noexcept;
    [[nodiscard]] Data& data() const;
    resource::AccountedUnique<Data> data_;
  };
  class PendingEpoch {
   public:
    PendingEpoch(const PendingEpoch&) = delete;
    PendingEpoch& operator=(const PendingEpoch&) = delete;
    PendingEpoch(PendingEpoch&&) noexcept;
    PendingEpoch& operator=(PendingEpoch&&) noexcept;
    ~PendingEpoch();
    [[nodiscard]] bool active() const noexcept;
    // Drains one replacement; any error aborts every stage in this token.
    [[nodiscard]] bool stage(const weighted::Replacement&);
    // Replace one adapter-owned contribution: total - before + after. The
    // adapter owns source-row identity; this port checks arithmetic, not source
    // ownership. Values borrow a complete native scope until this call returns.
    // All stages share the same transaction and indexed grant. No count mirror.
    [[nodiscard]] bool stage_contribution(NodeId, storage::TupleValuesView,
        weighted::Multiplicity before, weighted::Multiplicity after);
    // Borrowed until the next stage, rollback, commit or token destruction.
    // nullopt means disabled; an empty span means an exactly zero current net.
    [[nodiscard]] std::optional<std::span<const weighted::BagDelta>> bag_delta_preview() const;
    // Same active-token borrow; unit support deltas, never numeric bag facts.
    [[nodiscard]] std::optional<std::span<const weighted::BagDelta>> support_delta_preview() const;
    [[nodiscard]] const weighted::Epoch& preview() const;
    [[nodiscard]] weighted::Snapshot snapshot(weighted::SnapshotLimits = {}) const;
    // Publication and inverse operations use already funded undo/storage.
    [[nodiscard]] weighted::Epoch commit();
    void rollback() noexcept;
   private:
    friend class WeightedRuntime;
    struct Data;
    explicit PendingEpoch(resource::AccountedUnique<Data>) noexcept;
    [[nodiscard]] bool stage_native(NodeId, storage::TupleValuesView,
        weighted::Multiplicity, weighted::Multiplicity, bool contribution);
    resource::AccountedUnique<Data> data_;
  };
  // Freeze the shape into the supplied account. Its actual limit is
  // authoritative; options().memory_limit_bytes reports that limit. Empty
  // accounts reject, and no replacement account is created on this path.
  [[nodiscard]] static WeightedRuntime create_into(const resource::MemoryAccount&,
      const PhysicalPlan&, weighted::Options = {});
  [[nodiscard]] static WeightedRuntime create_into(const resource::MemoryAccount&,
      const CompiledProgram&, weighted::Options = {});
  explicit WeightedRuntime(PhysicalPlan, weighted::Options = {});
  explicit WeightedRuntime(CompiledProgram, weighted::Options = {});
  WeightedRuntime(const WeightedRuntime&) = delete;
  WeightedRuntime& operator=(const WeightedRuntime&) = delete;
  WeightedRuntime(WeightedRuntime&&) noexcept;
  WeightedRuntime& operator=(WeightedRuntime&&) noexcept;
  ~WeightedRuntime();
  [[nodiscard]] const CompiledProgram& structural_program() const &;
  const CompiledProgram& structural_program() const && = delete;
  [[nodiscard]] const weighted::Binding& binding() const &;
  const weighted::Binding& binding() const && = delete;
  [[nodiscard]] static constexpr weighted::Profile profile() noexcept { return {}; }
  [[nodiscard]] const weighted::Options& options() const;
  [[nodiscard]] std::uint64_t owner() const;
  [[nodiscard]] std::uint64_t sequence() const;
  [[nodiscard]] bool ready() const;
  // The maintaining core: "keyed_v1" (bag mode, docs/keyed_core.md) or "reference_v1".
  [[nodiscard]] std::string_view engine() const;
  [[nodiscard]] weighted::Multiplicity root_weight() const;
  [[nodiscard]] std::optional<weighted::Attempt> last_attempt() const;
  [[nodiscard]] resource::MemoryStatistics accounted_memory_statistics() const;
  [[nodiscard]] PendingEpoch begin_epoch(std::uint64_t);
  [[nodiscard]] PendingEpoch begin_epoch(std::uint64_t, weighted::DeltaCapture);
  [[nodiscard]] weighted::Epoch apply(const weighted::Update&);
  [[nodiscard]] weighted::Snapshot snapshot(weighted::SnapshotLimits = {}) const;
  [[nodiscard]] ResultCursor results(weighted::CursorOptions = {}) const;
  // Fused keyed epochs (SqlRowsRuntime::prepare_fused): native contributions
  // go straight into the keyed bag engine, without a PendingEpoch, journal,
  // delta capture or epoch metrics; every changed head tuple is reported to
  // the sink as it changes. Only on the keyed core (engine() == "keyed_v1").
  // fused_stage replaces one contribution to a native record (values in node
  // scope order), exactly as a PendingEpoch native contribution does.
  [[nodiscard]] bool fused_available() const noexcept;
  void fused_begin(std::uint64_t sequence);
  void fused_stage(NodeId, storage::RowView values, weighted::Multiplicity before,
      weighted::Multiplicity after, keyed::WeightSink* sink);
  // Commits the open fused epoch; the epoch carries its sequence, changed flag
  // and root summaries only (no metrics, journal or captured deltas).
  [[nodiscard]] weighted::Epoch fused_commit();
  void fused_rollback() noexcept;
 private:
  friend class detail::SqlColdRebuild;
  explicit WeightedRuntime(std::shared_ptr<Impl> value) noexcept : impl_(std::move(value)) {}
  [[nodiscard]] Impl& impl() const;
  std::shared_ptr<Impl> impl_;
};
}  // namespace crown::runtime
