#pragma once

#include "crown/frontend/sql_aggregate.hpp"
#include "crown/runtime/sql_rows.hpp"

namespace crown::runtime::sql_aggregate {
struct Options {
  sql_rows::Options source;
  std::optional<std::uint64_t> group_work_limit = 1000000;
  std::uint64_t count_limit = INT64_MAX;
  std::uint64_t memory_limit_bytes = 256ULL * 1024 * 1024;
  bool capture_changes = false;
  // Fused batches (keyed core, no key constraints; else ignored): SQL source
  // edits stage straight into the keyed bag engine and every changed head
  // tuple folds into its group as it changes (SqlRowsRuntime::prepare_fused),
  // instead of through the SqlRows/Weighted prepared epochs and captured bag
  // deltas. Same groups and changes; epochs carry no source work or native
  // metrics, and native.bag_deltas stays empty.
  bool fused = false;
};
struct Metrics : aggregate::BatchMetrics {
  std::uint64_t native_deltas = 0;
};
struct Epoch {
  std::uint64_t sequence;
  bool changed = false; // Normalized physical-source weights changed, including filtered/unused sources.
  bool group_changed = false; // Genuine nonzero native bag facts, even if rendered values compare equal.
  bool captured = false;
  storage::IndexWork source_work{};
  // Native summary/work and explicitly requested journals only; bag_deltas is
  // always empty. Required internal D-fact capture is freed after consumption.
  weighted::Epoch native;
  Metrics metrics; // One cumulative group/decode budget; row_probes stays zero.
  frontend::SqlAggregateProgram program;
  aggregate::OutputVector<aggregate::GroupChange> output;
  Epoch(const resource::MemoryAccount&, std::uint64_t, frontend::SqlAggregateProgram, bool);
};
struct Snapshot {
  std::uint64_t sequence;
  frontend::SqlAggregateProgram program;
  aggregate::OutputVector<aggregate::GroupResult> groups;
  Snapshot(const resource::MemoryAccount&, std::uint64_t, frontend::SqlAggregateProgram);
};
// Build-only grants remain separate from the operational runtime options.
struct RebuildLimits {
  sql_rows::RebuildLimits source;
  std::uint64_t group_work = 1000000;
};
struct RebuildMetrics {
  sql_rows::RebuildMetrics source;
  aggregate::Metrics groups; // Includes authenticated static bootstrap and seed.
};
// Genuine original binding plus its complete physical source image. This is
// in-memory capture; a durable descriptor/checkpoint factory remains separate.
struct SourceSnapshot {
  frontend::SqlAggregateProgram program;
  sql_rows::SourceSnapshot source;
};
}  // namespace crown::runtime::sql_aggregate

namespace crown::runtime {
// Genuine SQL/source/native composition. Only complete physical source edits
// enter publicly; logical native facts remain inside one same-owner token.
// Calls on one owner, including diagnostics, must be serialized. Snapshot is
// eager and owning, so it creates no reader lease. No durable/WAL claim is made.
class SqlAggregateRuntime {
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
    // Borrowed only while this token remains active and unmoved. Copy the
    // program/Tuple handles explicitly for independent output/metadata lifetime.
    [[nodiscard]] const sql_aggregate::Epoch& preview() const &;
    const sql_aggregate::Epoch& preview() const && = delete;
    [[nodiscard]] sql_aggregate::Epoch commit();
    void rollback() noexcept;
   private:
    friend class SqlAggregateRuntime;
    explicit PreparedBatch(resource::AccountedUnique<Data>) noexcept;
    [[nodiscard]] Data& data() const;
    resource::AccountedUnique<Data> data_;
  };
  explicit SqlAggregateRuntime(frontend::SqlAggregateProgram, const FreeConnexTree&,
      const PhysicalOptions& = {}, sql_aggregate::Options = {});
  [[nodiscard]] static SqlAggregateRuntime create_into(const resource::MemoryAccount&,
      frontend::SqlAggregateProgram, const FreeConnexTree&, const PhysicalOptions& = {}, sql_aggregate::Options = {});
  [[nodiscard]] static SqlAggregateRuntime rebuild_into(const resource::MemoryAccount&,
      const sql_aggregate::SourceSnapshot&, sql_aggregate::Options,
      const sql_aggregate::RebuildLimits&, sql_aggregate::RebuildMetrics* = nullptr);
  SqlAggregateRuntime(const SqlAggregateRuntime&) = delete;
  SqlAggregateRuntime& operator=(const SqlAggregateRuntime&) = delete;
  SqlAggregateRuntime(SqlAggregateRuntime&&) noexcept;
  SqlAggregateRuntime& operator=(SqlAggregateRuntime&&) noexcept;
  ~SqlAggregateRuntime();
  [[nodiscard]] const frontend::SqlAggregateProgram& program() const &;
  const frontend::SqlAggregateProgram& program() const && = delete;
  [[nodiscard]] const resource::MemoryAccount& account() const &;
  const resource::MemoryAccount& account() const && = delete;
  [[nodiscard]] std::uint64_t sequence() const;
  // The native core under the composed SQL layers (WeightedRuntime::engine()).
  [[nodiscard]] std::string_view engine() const;
  // Whether batches take the fused path (Options::fused on a capable source).
  [[nodiscard]] bool fused() const;
  [[nodiscard]] bool ready() const noexcept;
  [[nodiscard]] weighted::Multiplicity root_weight() const;
  [[nodiscard]] resource::MemoryStatistics accounted_memory_statistics() const;
  [[nodiscard]] std::uint64_t source_weight(TableId, std::span<const sql_rows::Cell>) const;
  // All source/native/group/output preparation is complete before return.
  // Empty/no-op batches still advance one contiguous epoch when committed.
  [[nodiscard]] PreparedBatch prepare_batch(const sql_rows::NetBatch&);
  [[nodiscard]] sql_aggregate::Snapshot snapshot(aggregate::SnapshotLimits = {}) const;
  [[nodiscard]] sql_aggregate::SourceSnapshot source_snapshot(sql_rows::SourceSnapshotLimits = {}) const;
 private:
  explicit SqlAggregateRuntime(std::shared_ptr<Data>) noexcept;
  [[nodiscard]] Data& data() const;
  std::shared_ptr<Data> data_;
};
}  // namespace crown::runtime
