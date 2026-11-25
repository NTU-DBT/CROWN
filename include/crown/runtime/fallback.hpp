#pragma once

#include "crown/planner/fallback.hpp"
#include "crown/runtime/physical.hpp"
#include "crown/storage/keyed.hpp"
#include "crown/resource/owner_allocator.hpp"
#include <functional>
#include <memory>
#include <optional>
#include <span>

namespace crown::runtime::fallback {
using Profile = planner::fallback::Profile;
struct Limits {
  std::uint64_t work = 1'000'000; // Shared metadata/capture/join/dedup/difference admissions.
  std::uint64_t source_rows = 65536; // All physical rows in one private source image.
  std::uint64_t rows = 65536; // Distinct retained output rows, not witness count.
};
struct Options {
  PhysicalRuntimeOptions sources;
  Limits recompute;
  storage::keyed::GcOptions gc{};  // keyed core only
  // Keyed core: false maintains the answer without materializing each
  // epoch's answer changes (Epoch::added/removed stay empty; snapshots,
  // answer counts and limits are unchanged), as DeltaMode::maintenance.
  bool answer_changes = true;
};
struct Metrics {
  std::uint64_t work = 0, source_work = 0, source_rows = 0;
  std::uint64_t row_visits = 0, term_tests = 0, equality_tests = 0, assignments = 0;
  std::uint64_t projected = 0, duplicates = 0, scalar_fields = 0, scalar_bytes = 0;
  std::uint64_t row_comparisons = 0, outputs = 0, added = 0, removed = 0;
  bool recomputed = false;
};
class Runtime;

// The actual arbitrary original CQ is frozen separately from the genuine
// source-only coordinator program. Views borrow this immutable query-account
// owner; keeping Binding preserves terms, text, literals, schema and profile.
// sources().guarantee() describes Query{} source coordination, not this query.
class Binding {
  struct Data;
 public:
  Binding() noexcept = default;
  [[nodiscard]] explicit operator bool() const noexcept { return bool(data_); }
  [[nodiscard]] const program::Query& query() const &;
  const program::Query& query() const && = delete;
  [[nodiscard]] const Profile& profile() const &;
  const Profile& profile() const && = delete;
  [[nodiscard]] const CompiledProgram& sources() const &;
  const CompiledProgram& sources() const && = delete;
  [[nodiscard]] const storage::AccountedLayout& result_layout() const &;
  const storage::AccountedLayout& result_layout() const && = delete;
  [[nodiscard]] const resource::MemoryAccount& account() const &;
  const resource::MemoryAccount& account() const && = delete;
 private:
  friend class Runtime;
  explicit Binding(std::shared_ptr<const Data> data) noexcept : data_(std::move(data)) {}
  [[nodiscard]] const Data& data() const;
  std::shared_ptr<const Data> data_;
};
using TupleVector = std::vector<storage::Tuple, resource::OwnerAllocator<storage::Tuple>>;
using Cardinalities = std::vector<std::uint64_t, resource::OwnerAllocator<std::uint64_t>>;
struct Snapshot { std::uint64_t sequence; Binding binding; TupleVector rows; Metrics metrics; };
struct Epoch {
  PhysicalEpoch input; // Full-source epoch; local support events are not answer deltas.
  Binding binding;
  TupleVector added, removed; // Exact SET endpoint changes; own native payloads.
  Metrics metrics;
};
struct Explain {
  Profile profile;
  Cardinalities table_rows; // Actual committed original physical cardinalities.
  std::optional<std::uint64_t> witness_product;
  std::optional<std::uint64_t> prefix_product_sum;
  std::uint64_t result_rows;
  resource::MemoryStatistics memory;
};

// Explicit conservative exact-set fallback. One genuine source-only physical
// owner enforces the full original catalog/constraints. A private charged after
// image feeds an iterative nested-loop evaluator with DISTINCT projection.
// All fallible answer/delta work precedes source commit and a noexcept swap;
// no second source owner, database overlay or rollback journal is introduced.
// Calls on one owner are serialized. Output snapshots/deltas remain owning
// after teardown and do not hold source cursor leases. No CROWN constant-delay,
// GHD algorithm, AGM update theorem, bag or recovery guarantee is implied.
class Runtime {
  struct Data;
 public:
  explicit Runtime(const planner::fallback::Plan&, Options = {});
  ~Runtime();
  Runtime(Runtime&&) noexcept;
  Runtime& operator=(Runtime&&) noexcept;
  Runtime(const Runtime&) = delete;
  Runtime& operator=(const Runtime&) = delete;
  [[nodiscard]] const Binding& binding() const &;
  const Binding& binding() const && = delete;
  [[nodiscard]] const resource::MemoryAccount& account() const &;
  const resource::MemoryAccount& account() const && = delete;
  [[nodiscard]] bool ready() const;
  [[nodiscard]] std::uint64_t sequence() const;
  [[nodiscard]] bool has_answer() const;
  // The maintaining core: "keyed_v1" (docs/keyed_core.md) or "reference_v1".
  [[nodiscard]] std::string_view engine() const;
  // Keyed core: its cyclic algorithm ("ghd" or "support"); else "reference".
  [[nodiscard]] std::string_view algorithm() const;
  [[nodiscard]] Epoch apply(const PhysicalSetUpdate&);
  [[nodiscard]] Snapshot snapshot(Limits = {}) const;
  // Streaming snapshot: each answer as an owning result tuple (valid for the
  // call), in engine order rather than sorted, without materializing the
  // snapshot. Returns the number of answers visited.
  std::uint64_t visit(const std::function<void(const storage::Tuple&)>& visitor, Limits = {}) const;
  // Cold owning diagnostics. Product estimates are advisory Cartesian/prefix
  // upper bounds; nullopt denotes overflow, not wrapped or measured work.
  [[nodiscard]] Explain explain() const;
  // Explicit external diagnostic export; ordinary Database/Row/string DTO
  // allocations belong to the caller, outside internal retained native state.
  [[nodiscard]] Database source_snapshot() const;
 private:
  [[nodiscard]] Data& data() const;
  resource::AccountedUnique<Data> data_;
};
} // namespace crown::runtime::fallback
