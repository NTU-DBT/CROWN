#pragma once

#include "crown/planner/star.hpp"
#include "crown/runtime/physical.hpp"
#include "crown/resource/owner_allocator.hpp"
#include "crown/storage/index_work.hpp"

namespace crown::runtime::star {
struct Options {
  PhysicalRuntimeOptions sources; // Original full-source validation/storage grant.
  std::uint64_t work = 1'000'000; // One separate heavy/light grant per input epoch.
  // One separate cold import grant for original query/schema metadata, capped
  // by the genuine indexed plan policy. Never recreated during updates.
  storage::IndexWork metadata_work{1'000'000, 1'000'000, 1'000'000, 1'000'000, 1'000'000};
};
struct Metrics {
  std::uint64_t work = 0, center_changes = 0, satellite_changes = 0;
  // center_visits counts both migration passes; group_visits counts heavy
  // satellite reverse-index visits. migrated_rows counts one row per relabel.
  std::uint64_t center_visits = 0, group_visits = 0, projection_changes = 0;
  std::uint64_t key_relabels = 0, migrated_rows = 0, scale_resets = 0;
};
struct Epoch {
  std::uint64_t sequence;
  bool physical_changed;
  PhysicalMetrics source_metrics;
  Metrics maintenance;
};
struct DimensionState {
  std::uint64_t h, scale, keys, heavy_keys;
  std::optional<std::uint64_t> threshold; // nullopt: mathematical power exceeds uint64.
};
struct KeyState {
  std::uint64_t degree;
  bool heavy, present; // present is the real satellite, or true if none exists.
};
struct State {
  std::uint64_t sequence, center_rows, groups, live_groups;
  std::vector<DimensionState, resource::OwnerAllocator<DimensionState>> dimensions;
};
struct CursorOptions {
  std::uint64_t work = 1'000'000; // Shared across this cursor's complete lifetime.
};
struct CursorMetrics {
  std::uint64_t work = 0, candidates = 0, duplicates = 0, outputs = 0;
  std::uint64_t group_advances = 0, cleanup_items = 0, candidate_quantum = 1;
};

// Opt-in, initially empty, serial exact-set star owner. It maintains the real
// heavy/light groups of P2 v1 Def4.5 / pp16-17, with the explicit local H-index,
// sparse reset and projection-scheduler repairs documented in docs/star.md.
// The full original source coordinator has no generic occurrence routes: heavy
// satellite updates visit groups, light satellite updates visit their own rows.
// Every retained index, journal, cursor and result uses its original account.
//
// apply() maintains a snapshot view and source epoch, not full signed query
// deltas, a durable session, or an automatic SQL/C05 policy. An ordinary general
// runtime remains an independent comparison backend. Compilation/execution and
// complete source-constraint costs are separate from the heavy/light counters.
class Runtime {
  struct Data;
 public:
  class Cursor {
   public:
    ~Cursor();
    Cursor(Cursor&&) noexcept;
    Cursor& operator=(Cursor&&) noexcept;
    Cursor(const Cursor&) = delete;
    Cursor& operator=(const Cursor&) = delete;
    [[nodiscard]] std::optional<storage::Tuple> next();
    void cancel() noexcept;
    [[nodiscard]] CursorMetrics metrics() const noexcept;
   private:
    struct Data;
    explicit Cursor(resource::AccountedUnique<Data>) noexcept;
    resource::AccountedUnique<Data> data_;
    CursorMetrics closed_;
    friend class Runtime;
  };
  explicit Runtime(const planner::star::Plan&, Options = {});
  ~Runtime();
  Runtime(Runtime&&) noexcept;
  Runtime& operator=(Runtime&&) noexcept;
  Runtime(const Runtime&) = delete;
  Runtime& operator=(const Runtime&) = delete;
  // Original query/schema/comparison authority. Its general execution profile
  // does not describe this star owner; candidate pacing/costs are stated below.
  [[nodiscard]] const CompiledProgram& program() const &;
  const CompiledProgram& program() const && = delete;
  [[nodiscard]] const resource::MemoryAccount& account() const &;
  const resource::MemoryAccount& account() const && = delete;
  [[nodiscard]] std::uint64_t sequence() const;
  [[nodiscard]] bool ready() const;
  [[nodiscard]] bool has_answer() const;
  [[nodiscard]] Epoch apply(const PhysicalSetUpdate&);
  [[nodiscard]] Cursor results(CursorOptions = {}) const;
  [[nodiscard]] State state() const; // Owning original-account diagnostic gauges.
  [[nodiscard]] std::optional<KeyState> key(std::size_t coordinate, storage::ScalarView) const;
  // Explicit ordinary caller DTO export, with full source scan/copy cost.
  [[nodiscard]] Database source_snapshot() const;
  // Bounded cold inspection of internal heavy/light/index/H invariants.
  void check_invariants(std::uint64_t work = 1'000'000) const;
 private:
  [[nodiscard]] Data& data() const;
  std::shared_ptr<Data> data_;
};

// A cursor deduplicates counted per-group head projections. Its quantum is
// min(center_rows, product_hidden(1 + heavy_keys_i)), with the empty-state value
// one. Under the stated label invariant this is O_d((h+1)^(d-j)) candidates per
// first/next/end call; full-head quantum is one. j counts DISTINCT head variables.
// Ordered-map comparisons, scalar widths, tuple copying/allocation and final
// seen/queue teardown remain real additional costs. Cancellation/end cleanup is
// O(cursor scratch), not a P2 end-to-end constant-delay promise. Keep the cursor
// through terminal null or cancel before updating. Owning outputs survive both
// cursor and runtime. Failure closes the cursor and releases its reader lease.
} // namespace crown::runtime::star
