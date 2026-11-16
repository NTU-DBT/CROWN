#pragma once

#include "crown/frontend/aggregate.hpp"
#include "crown/resource/owner_allocator.hpp"
#include "crown/resource/ownership.hpp"
#include "crown/storage/tuple_values.hpp"
#include <optional>
#include <span>
#include <vector>

namespace crown::runtime::aggregate {
using Cell = std::optional<storage::ScalarView>;
using SqlValue = std::optional<crown::Value>;
using Row = std::vector<SqlValue>;
template<class T> using OutputVector = std::vector<T, resource::OwnerAllocator<T>>;

// SQL NULL cells stay outside the classical core row type. One owned payload
// block contains all cells/string bytes; the shared Data control is accounted
// too. Exporting ordinary values is explicit caller-owned work.
class Tuple {
  struct Data;
 public:
  Tuple() noexcept = default;
  [[nodiscard]] explicit operator bool() const noexcept { return bool(data_); }
  [[nodiscard]] static Tuple copy_of(const resource::MemoryAccount&, std::span<const Cell>,
      resource::MemoryPurpose = resource::MemoryPurpose::tuple_values);
  [[nodiscard]] std::size_t size() const;
  [[nodiscard]] std::span<const Cell> view() const &;
  std::span<const Cell> view() const && = delete;
  [[nodiscard]] Row export_values() const;
  [[nodiscard]] const resource::MemoryAccount& account() const &;
  const resource::MemoryAccount& account() const && = delete;
  [[nodiscard]] bool operator==(const Tuple&) const;
 private:
  explicit Tuple(std::shared_ptr<const Data> value) noexcept : data_(std::move(value)) {}
  [[nodiscard]] const Data& data() const;
  std::shared_ptr<const Data> data_;
};

struct Options {
  std::optional<std::uint64_t> work_limit = 1000000;
  std::uint64_t count_limit = INT64_MAX;
  // Used only for standalone construction. _into keeps its receiving grant.
  std::uint64_t memory_limit_bytes = 256ULL * 1024 * 1024;
  bool capture_changes = false;
};
struct Update {
  std::uint64_t sequence;
  std::span<const SqlValue> values;  // Borrowed for the synchronous call only.
  std::uint64_t before, after;
};
// A decoded logical bag delta. Inputs must have unique complete nullable row
// keys and nonzero magnitudes; all cell/string borrows end at prepare_batch's
// return. This record carries no physical-source or compiler authority.
struct RowDelta {
  std::span<const Cell> values;
  std::uint64_t magnitude;
  bool erase;
};
struct NetBatch {
  std::uint64_t sequence;
  std::span<const RowDelta> deltas;
};
struct Metrics {
  // Selected logical charges; not elapsed CPU or every map/string comparison.
  std::uint64_t work = 0, input_fields = 0, input_bytes = 0;
  std::uint64_t row_probes = 0, group_probes = 0, measures = 0, output_fields = 0;
  std::uint64_t groups_created = 0, groups_removed = 0;
};
// Keep batch-only counters out of the single-row Metrics/Epoch value layout.
struct BatchMetrics : Metrics {
  std::uint64_t copied_fields = 0, copied_bytes = 0, state_fields_prepared = 0;
  std::uint64_t groups_finalized = 0;
};
struct GroupChange {
  Tuple key;
  std::optional<Tuple> before, after; // Absent group differs from NULL cells.
};
struct Epoch {
  std::uint64_t sequence;
  bool changed = false; // Input weight changed, independently of rounded output.
  bool captured = false;
  Metrics metrics;
  std::optional<GroupChange> output;
};
struct BatchEpoch {
  std::uint64_t sequence;
  bool changed = false, captured = false;
  BatchMetrics metrics;
  frontend::AggregateProgram program;
  OutputVector<GroupChange> output;
  BatchEpoch(const resource::MemoryAccount&, std::uint64_t,
      frontend::AggregateProgram, bool captured);
};
struct GroupResult { Tuple key, values; };
struct Snapshot {
  std::uint64_t sequence;
  frontend::AggregateProgram program;
  OutputVector<GroupResult> groups;
  Snapshot(const resource::MemoryAccount&, std::uint64_t, frontend::AggregateProgram);
};
struct SnapshotLimits {
  std::uint64_t groups = 65536;
  std::optional<std::uint64_t> work_limit = 1000000;
};
}  // namespace crown::runtime::aggregate

namespace crown::runtime {
// Logical bag rows maintain aggregate groups. Single-row calls keep immediate
// SUM checks; prepare_batch seals every final touched group before publication.
// This component installs no physical source or cross-runtime/recovery binding.
// Serialize calls on one runtime, including const diagnostics: they reuse
// scratch and share the receiving allocation account.
class AggregateRuntime {
  struct Data;
 public:
  class PreparedBatch {
    struct Data;
   public:
    PreparedBatch(const PreparedBatch&) = delete;
    PreparedBatch& operator=(const PreparedBatch&) = delete;
    PreparedBatch(PreparedBatch&&) noexcept;
    PreparedBatch& operator=(PreparedBatch&&) noexcept;
    ~PreparedBatch();
    [[nodiscard]] bool active() const noexcept;
    // Borrowed until this token moves, commits, rolls back, or dies. Copy the
    // program/Tuple handles explicitly if independent ownership is required.
    [[nodiscard]] const aggregate::BatchEpoch& preview() const &;
    const aggregate::BatchEpoch& preview() const && = delete;
    [[nodiscard]] aggregate::BatchEpoch commit();
    void rollback() noexcept;
   private:
    friend class AggregateRuntime;
    explicit PreparedBatch(resource::AccountedUnique<Data>) noexcept;
    [[nodiscard]] Data& data() const;
    resource::AccountedUnique<Data> data_;
  };
  explicit AggregateRuntime(frontend::AggregateProgram, aggregate::Options = {});
  [[nodiscard]] static AggregateRuntime create_into(const resource::MemoryAccount&,
      frontend::AggregateProgram, aggregate::Options = {});
  AggregateRuntime(const AggregateRuntime&) = delete;
  AggregateRuntime& operator=(const AggregateRuntime&) = delete;
  AggregateRuntime(AggregateRuntime&&) noexcept;
  AggregateRuntime& operator=(AggregateRuntime&&) noexcept;
  ~AggregateRuntime();
  [[nodiscard]] const frontend::AggregateProgram& program() const &;
  const frontend::AggregateProgram& program() const && = delete;
  [[nodiscard]] std::uint64_t sequence() const;
  [[nodiscard]] aggregate::Epoch apply(const aggregate::Update&);
  // W03's compressed tuples can enter without an owning nullable DTO export.
  [[nodiscard]] aggregate::Epoch apply_weighted(std::uint64_t sequence,
      storage::TupleValuesView values, std::uint64_t before, std::uint64_t after);
  // One receiving account/work budget; authenticate each unique nonzero delta
  // against this runtime's logical row ledger. Empty batches advance one epoch.
  // Active tokens retain this owner after facade move/death and block updates,
  // snapshots and invariant checks; committed sequence/program/stats may be read.
  [[nodiscard]] PreparedBatch prepare_batch(const aggregate::NetBatch&);
  [[nodiscard]] aggregate::Snapshot snapshot(aggregate::SnapshotLimits = {}) const;
  [[nodiscard]] resource::MemoryStatistics accounted_memory_statistics() const;
  // Explicit full recomputation diagnostic, not update-path work.
  void check_invariants() const;
 private:
  explicit AggregateRuntime(std::shared_ptr<Data>) noexcept;
  [[nodiscard]] Data& data() const;
  std::shared_ptr<Data> data_;
};
}  // namespace crown::runtime
