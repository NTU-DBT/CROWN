#pragma once
// Keyed CROWN set engine (docs/keyed_core.md): exact-set maintenance, live
// sets and delta/snapshot enumeration of one compiled free-connex program over
// typed tuples of any width. Every index is keyed by storage::keyed::Key;
// updates mutate entries in place under an undo log, and retired keys are
// reclaimed by an epoch Collector (blocking, background or manual).
#include "crown/ir/program.hpp"
#include "crown/storage/keyed.hpp"

#include <array>
#include <functional>
#include <memory>
#include <optional>
#include <string>

namespace crown::runtime::keyed {

struct EngineOptions {
  bool delta = false;  // maintain live sets and emit signed deltas while staging
  storage::keyed::GcOptions gc{};
  bool sql_view = true;  // SQL output list when the program came from SQL, else the core head
  // Index capacity plus interned keys; exceeding it throws MemoryFailure(limit)
  // before the staged change applies (the transaction can then roll back).
  std::size_t memory_limit_bytes = static_cast<std::size_t>(-1);
  // Bag semantics (WeightedRuntime): native records carry multiplicities that
  // callers replace with stage_weight(); every head tuple has an exact count
  // (the product of its C* visible weights) and changes report before/after
  // counts. Arithmetic is checked against multiplicity_limit.
  bool bag = false;
  std::uint64_t multiplicity_limit = UINT64_MAX;
};
struct EngineStatistics {
  std::uint64_t events = 0, changed_events = 0, routes = 0, route_changes = 0;
  std::uint64_t changed_keys = 0, delta_rows = 0, snapshot_rows = 0;
  std::uint64_t commits = 0, rollbacks = 0, undo_entries = 0;
  std::size_t index_bytes = 0, interned_keys = 0, memory_bytes = 0, peak_memory_bytes = 0;
};

// Receives result rows in the program's result view (SQL outputs when the
// program came from SQL, otherwise the core head). Cells are borrowed for the
// duration of the call.
class RowSink {
 public:
  virtual ~RowSink() = default;
  virtual void row(SetOperation operation, storage::RowView values) = 0;
};

// One accepted occurrence route of a staged event (after its delta work).
struct RouteReport {
  std::uint32_t occurrence = 0, node = 0;
  std::uint64_t prefix = 0;            // 1-based position in the table's route list
  storage::RowView record;             // native node scope, borrowed for the call
  std::uint64_t before = 0, after = 0; // derivation counts
  bool crossing = false;               // 0 <-> 1: native membership changed
  bool before_answer = false, after_answer = false;
  std::uint64_t changed_keys = 0, rows = 0;  // E crossings and signed rows of this route
  std::size_t live_rows = 0;                 // live E keys after the route (delta mode)
};
// Bag mode: a head tuple whose count changed in the staged route (delta mode),
// or one snapshot row (before = 0). Values are borrowed for the call.
class WeightSink {
 public:
  virtual ~WeightSink() = default;
  virtual void change(storage::RowView values, std::uint64_t before, std::uint64_t after) = 0;
};
class RouteObserver {
 public:
  virtual ~RouteObserver() = default;
  virtual void route(const RouteReport& report) = 0;
};

class SetEngine {
 public:
  // Empty when supported, else the first unsupported feature.
  [[nodiscard]] static std::string unsupported(const CompiledProgram& program);
  SetEngine(const CompiledProgram& program, EngineOptions options = {});
  ~SetEngine();
  SetEngine(const SetEngine&) = delete;
  SetEngine& operator=(const SetEngine&) = delete;

  // One transaction per physical event. stage() routes the row to every
  // occurrence in order and emits signed rows (delta mode) before returning;
  // it returns false for a duplicate insert or an absent erase. Exceptions
  // leave the transaction open: rollback() restores the committed state.
  void begin();
  bool stage(TableId table, SetOperation operation, storage::RowView row, RowSink* sink,
      RouteObserver* observer = nullptr);
  // Step-wise staging of one event: the source change, then each occurrence
  // route in order (each emits its own signed rows). stage() does all of it.
  bool stage_source(TableId table, SetOperation operation, storage::RowView row);
  [[nodiscard]] std::size_t routes(TableId table) const;
  void stage_route(TableId table, std::size_t index, SetOperation operation, storage::RowView row,
      RowSink* sink, RouteObserver* observer = nullptr);
  // Bag mode: replace one contribution to native `node`'s record (values in
  // node scope order): its multiplicity becomes total - before + after. In
  // delta mode each changed head tuple goes to `sink`.
  void stage_weight(std::uint32_t node, storage::RowView record, std::uint64_t before, std::uint64_t after,
      WeightSink* sink);
  [[nodiscard]] std::uint64_t weight(std::uint32_t node, storage::RowView record) const;
  // Bag mode: the full join's total count (the root's subtree sum).
  [[nodiscard]] std::uint64_t root_weight() const noexcept;
  // Bag mode: every native record with its multiplicity.
  void for_each_record(const std::function<void(std::uint32_t, storage::RowView, std::uint64_t)>& visit) const;
  void snapshot(WeightSink& sink) const;
  void commit();
  void rollback() noexcept;
  [[nodiscard]] bool active() const noexcept;
  // begin + stage + commit, rolling back on failure.
  bool apply(TableId table, SetOperation operation, storage::RowView row, RowSink* sink);

  void snapshot(RowSink& sink) const;
  // Resumable snapshot enumeration. While any cursor is open the engine
  // refuses transactions (readers block the writer) and pins its GC epoch.
  class Cursor {
   public:
    ~Cursor();
    Cursor(const Cursor&) = delete;
    Cursor& operator=(const Cursor&) = delete;
    // The next result row (borrowed until the next call), or nullopt at the end.
    [[nodiscard]] std::optional<storage::RowView> next();
    [[nodiscard]] std::uint64_t rows() const noexcept { return rows_; }
    // Bag mode: the count of the row last returned by next().
    [[nodiscard]] std::uint64_t weight() const noexcept { return weight_; }
   private:
    friend class SetEngine;
    Cursor(const SetEngine& owner, bool alternate);
    const SetEngine* owner_;
    bool alternate_ = false;  // the view other than EngineOptions::sql_view
    storage::keyed::Collector::Pin pin_;
    std::uint32_t root_ = 0;
    std::size_t depth_ = 0;
    bool started_ = false, done_ = false;
    std::uint64_t rows_ = 0, weight_ = 0;
    std::array<std::uint32_t, 64> current_{};
    // Per step, cached at the first next(): the engine cannot change while a
    // reader is open.
    std::array<const storage::keyed::KeyMap*, 64> maps_{};
    std::array<const storage::keyed::KeyDomain*, 64> domains_{};
    std::array<storage::ScalarView, 256> out_{}, scratch_{};
  };
  [[nodiscard]] std::unique_ptr<Cursor> open_cursor() const;
  // A cursor over the SQL output view (true) or the core head (false),
  // whichever the engine's own result view is.
  [[nodiscard]] std::unique_ptr<Cursor> open_cursor(bool sql_view) const;
  [[nodiscard]] std::size_t readers() const noexcept;
  [[nodiscard]] bool has_answer() const;
  // Every retained physical source row, by source table (checkpoints,
  // snapshots, rebuilds and reference diagnostics are derived from these).
  [[nodiscard]] Database sources() const;
  // Whether the source table retains the row (staged changes included), and
  // how many rows it retains.
  [[nodiscard]] bool contains(TableId table, storage::RowView row) const;
  [[nodiscard]] std::uint64_t rows(TableId table) const;
  [[nodiscard]] bool delta() const noexcept;
  // Switch modes between transactions; entering delta mode bootstraps live sets.
  void set_delta(bool delta);
  [[nodiscard]] std::span<const ScalarType> result_types() const noexcept;
  [[nodiscard]] storage::keyed::Collector& collector() noexcept;
  // Collect eligible garbage now and release excess index capacity.
  void collect();
  [[nodiscard]] EngineStatistics statistics() const;
  void check_invariants() const;

 private:
  struct Impl;
  std::unique_ptr<Impl> impl_;
};

}  // namespace crown::runtime::keyed
