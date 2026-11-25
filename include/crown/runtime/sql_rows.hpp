#pragma once

#include "crown/frontend/sql_rows.hpp"
#include "crown/runtime/aggregate.hpp"
#include "crown/runtime/weighted.hpp"

namespace crown::runtime::sql_rows {
using Cell = frontend::SqlRowCell;
using Tuple = aggregate::Tuple;
struct Options {
  weighted::Options native;
  // One source allowance per replacement, shared by validation, constraints
  // and every alias. Native storage keeps its separate, existing epoch grant.
  // Net-batch preparation shares one such allowance across every edit/alias.
  // These are selected logical admissions, not a bound on map comparisons.
  storage::IndexWork source_work_limit{1000000, 1000000, 64ULL * 1024 * 1024, 0, 0};
};
struct Update {
  std::uint64_t sequence;
  TableId source;
  std::span<const Cell> values; // Complete physical row; borrowed until return.
  std::uint64_t before, after;
};
// Distinct atomic net command; this is not an ordered transport batch.
struct SourceReplacement {
  TableId source;
  std::span<const Cell> values; // Borrowed only through prepare_batch return.
  std::uint64_t before, after; // Duplicate full-row edits must form an exact chain.
};
struct NetBatch { std::uint64_t sequence; std::span<const SourceReplacement> replacements; };
struct Epoch {
  bool changed; // Full source weight changed, even if every alias filters it.
  storage::IndexWork source_work;
  weighted::Epoch native;
};
// SQL-presented changes borrow one caller scratch row and the active token.
// A single finite decode allowance is shared across every output pass.
struct OutputLimits {
  std::uint64_t rows = 65536;
  std::uint64_t work = 1000000; // Selected row/field reads; serialized bytes are codec work.
  bool operator==(const OutputLimits&) const = default;
};
struct OutputChangeView {
  std::span<const Cell> values;
  weighted::SignedMagnitude change;
};
struct Result {
  Tuple tuple;
  std::uint64_t multiplicity;
  // Sharing immutable metadata preserves SQL names/types after owner teardown.
  frontend::SqlRowsProgram schema;
};
// An explicit physical-source image shares immutable complete row storage.
// It includes filtered/unused tables and retains the real source/native schema.
struct SourceEntry { TableId source; Tuple row; std::uint64_t weight; };
struct SourceSnapshotLimits {
  std::uint64_t rows = 65536;
  // Fields and retained string extents are admitted without UTF8 rescanning.
  storage::IndexWork work_limit{1000000, 1000000, 64ULL * 1024 * 1024, 0, 0};
};
// Whole-image load has distinct finite build admissions. Operational
// source/native/indexed limits and every arithmetic/table domain are unchanged.
struct RebuildLimits {
  std::uint64_t rows = 65536;
  storage::IndexWork source_work{1000000,1000000,64ULL*1024*1024,4000000,0};
  std::uint64_t native_work = 1000000;
  std::optional<storage::IndexWork> indexed_work; // Required exactly for indexed storage.
  PhysicalLimits lowering; // Finite cold host limits; original physical options stay bound.
};
struct RebuildMetrics {
  storage::IndexWork source_work{}, indexed_work{};
  std::uint64_t native_work = 0, lowering_work = 0;
};
struct SourceSnapshot {
  std::uint64_t sequence;
  frontend::SqlRowsProgram program;
  CompiledProgram native_program;
  weighted::Binding native_binding;
  storage::IndexWork work{};
  aggregate::OutputVector<SourceEntry> rows;
  SourceSnapshot(const resource::MemoryAccount&, std::uint64_t,
      const frontend::SqlRowsProgram&, const CompiledProgram&, const weighted::Binding&);
};
}  // namespace crown::runtime::sql_rows

namespace crown::runtime::keyed { class WeightSink; }
namespace crown::runtime {
// One physical bag-row replacement fans out to all SQL occurrences in one
// native epoch. Source rows and enforced-key counters publish after native
// preparation succeeds. Its RAII epoch owns rollback; source preparation stays
// private without a full database clone, scan, or additional undo framework.
// Calls on one owner, including diagnostics, must be serialized.
class SqlRowsRuntime {
  struct Data;
 public:
  class PreparedBatch {
    struct Data;
   public:
    PreparedBatch(const PreparedBatch&)=delete;
    PreparedBatch& operator=(const PreparedBatch&)=delete;
    PreparedBatch(PreparedBatch&&) noexcept;
    PreparedBatch& operator=(PreparedBatch&&) noexcept;
    ~PreparedBatch();
    [[nodiscard]] bool active() const noexcept;
    [[nodiscard]] std::uint64_t sequence() const;
    [[nodiscard]] bool changed() const; // Normalized physical-source change, including filtered rows.
    [[nodiscard]] const frontend::SqlRowsProgram& program() const &;
    const frontend::SqlRowsProgram& program() const &&=delete;
    [[nodiscard]] storage::IndexWork source_work() const;
    [[nodiscard]] const weighted::Epoch& native_preview() const &;
    const weighted::Epoch& native_preview() const &&=delete;
    // Native encoded core facts, before SQL DISTINCT/EXISTS presentation.
    // The span borrows this active token; no SQL/source/proof authority is added.
    [[nodiscard]] std::optional<std::span<const weighted::BagDelta>> native_bag_delta_preview() const &;
    std::optional<std::span<const weighted::BagDelta>> native_bag_delta_preview() const &&=delete;
    // nullopt on native-only prepare_batch. Values preserve SQL output order,
    // NULL, constants and exact bag/support units. All reads share output_work().
    [[nodiscard]] std::optional<std::size_t> output_size() const;
    [[nodiscard]] sql_rows::OutputChangeView output_change(std::size_t,
        std::span<sql_rows::Cell> scratch) const &;
    sql_rows::OutputChangeView output_change(std::size_t,
        std::span<sql_rows::Cell>) const && = delete;
    [[nodiscard]] std::uint64_t output_work() const;
    [[nodiscard]] sql_rows::Epoch commit();
    void rollback() noexcept;
   private:
    friend class SqlRowsRuntime;
    friend class detail::SqlColdRebuild;
    explicit PreparedBatch(resource::AccountedUnique<Data>) noexcept;
    [[nodiscard]] Data& data() const;
    resource::AccountedUnique<Data> data_;
  };
  class ResultCursor {
    struct Data;
   public:
    ResultCursor(const ResultCursor&) = delete;
    ResultCursor& operator=(const ResultCursor&) = delete;
    ResultCursor(ResultCursor&&) noexcept;
    ResultCursor& operator=(ResultCursor&&) noexcept;
    ~ResultCursor();
    [[nodiscard]] bool active() const noexcept;
    [[nodiscard]] weighted::CursorState state() const;
    [[nodiscard]] std::uint64_t sequence() const;
    // One owning nullable SQL row per distinct output; DISTINCT emits weight 1.
    // EXISTS always emits one Boolean row, including for an empty inner bag.
    // The reader lease blocks updates through the final result until terminal next(),
    // cancel(), or destruction. Output-copy failure closes and fails the cursor.
    [[nodiscard]] std::optional<sql_rows::Result> next();
    void cancel() noexcept;
   private:
    friend class SqlRowsRuntime;
    explicit ResultCursor(resource::AccountedUnique<Data>) noexcept;
    [[nodiscard]] Data& data() const;
    resource::AccountedUnique<Data> data_;
  };
  explicit SqlRowsRuntime(frontend::SqlRowsProgram, const FreeConnexTree&,
      const PhysicalOptions& = {}, sql_rows::Options = {});
  [[nodiscard]] static SqlRowsRuntime create_into(const resource::MemoryAccount&,
      frontend::SqlRowsProgram, const FreeConnexTree&, const PhysicalOptions& = {}, sql_rows::Options = {});
  // Untrusted physical rows are revalidated through the genuine source and
  // one unpublished native epoch at image.sequence. No live sequence mutator.
  [[nodiscard]] static SqlRowsRuntime rebuild_into(const resource::MemoryAccount&,
      const sql_rows::SourceSnapshot&, sql_rows::Options, const sql_rows::RebuildLimits&,
      sql_rows::RebuildMetrics* = nullptr);
  SqlRowsRuntime(const SqlRowsRuntime&) = delete;
  SqlRowsRuntime& operator=(const SqlRowsRuntime&) = delete;
  SqlRowsRuntime(SqlRowsRuntime&&) noexcept;
  SqlRowsRuntime& operator=(SqlRowsRuntime&&) noexcept;
  ~SqlRowsRuntime();
  [[nodiscard]] const frontend::SqlRowsProgram& program() const &;
  const frontend::SqlRowsProgram& program() const && = delete;
  [[nodiscard]] std::uint64_t sequence() const;
  // The native core under the SQL source layer (WeightedRuntime::engine()).
  [[nodiscard]] std::string_view engine() const;
  [[nodiscard]] bool ready() const;
  // Native inner/full-root weight before DISTINCT/EXISTS output transformation.
  [[nodiscard]] weighted::Multiplicity root_weight() const;
  [[nodiscard]] resource::MemoryStatistics accounted_memory_statistics() const;
  [[nodiscard]] sql_rows::Epoch apply(const sql_rows::Update&);
  // Final-state constraints and one native epoch; no committed partial rows.
  // Preparation owns the SQL owner even after this facade moves or dies.
  [[nodiscard]] PreparedBatch prepare_batch(const sql_rows::NetBatch&,
      weighted::DeltaCapture = weighted::DeltaCapture::disabled);
  // Prepare genuine SQL bag/DISTINCT/EXISTS endpoint changes before commit.
  // Output views borrow exact-width caller scratch and this active token;
  // scratch reuse or token close invalidates them. No SQL result graph is kept.
  [[nodiscard]] PreparedBatch prepare_output_batch(const sql_rows::NetBatch&,
      sql_rows::OutputLimits = {});
  [[nodiscard]] ResultCursor results(weighted::CursorOptions = {}) const;
  // Explicit borrowed lookup; validates the complete row but allocates nothing.
  [[nodiscard]] std::uint64_t source_weight(TableId, std::span<const sql_rows::Cell>) const;
  // Quiescent, eager and owning: no reader lease or update-path row mirror.
  // Rows follow original TableId then the source's exact nullable tuple order.
  // Failure releases the incomplete image without changing committed state.
  [[nodiscard]] sql_rows::SourceSnapshot source_snapshot(sql_rows::SourceSnapshotLimits = {}) const;
  // Fused batches: on the keyed core, for programs without key constraints.
  // The net batch is validated and chained as in prepare_batch; then every
  // changed native contribution goes straight into the keyed bag engine
  // (WeightedRuntime::fused_stage) and each changed head tuple is reported to
  // `sink` as it changes. No PendingEpoch, delta capture or work accounting.
  // The batch stays open until commit_fused (which publishes the source rows)
  // or rollback_fused. prepare_fused returns whether a source weight changed.
  [[nodiscard]] bool fused_available() const;
  bool prepare_fused(const sql_rows::NetBatch&, keyed::WeightSink& sink);
  [[nodiscard]] weighted::Epoch commit_fused();
  void rollback_fused() noexcept;
 private:
  friend class detail::SqlColdRebuild;
  explicit SqlRowsRuntime(std::shared_ptr<Data>) noexcept;
  [[nodiscard]] Data& data() const;
  std::shared_ptr<Data> data_;
};
}  // namespace crown::runtime
