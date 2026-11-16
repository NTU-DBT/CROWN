#pragma once

#include "crown/planner/difference.hpp"
#include "crown/runtime/fallback.hpp"
#include <memory>
#include <optional>

namespace crown::runtime::difference {
using Mode = planner::difference::Mode;
using Profile = planner::difference::Profile;
using annotations::Multiplicity;
struct Limits {
  std::uint64_t work = 1'000'000; // One metadata/image/both-operands/residual/delta balance.
  std::uint64_t source_rows = 65536; // All original physical rows in the one private image.
  std::uint64_t rows = 65536; // Distinct keys PER operand; residual is a subset of left keys.
};
struct Options {
  PhysicalRuntimeOptions sources;
  Limits recompute;
  std::uint64_t multiplicity_limit = UINT64_MAX; // Positive W01 checked-uint64 domain.
};
struct Metrics : fallback::Metrics {
  std::uint64_t left_assignments = 0, right_assignments = 0;
  std::uint64_t left_keys = 0, right_keys = 0, changes = 0;
};
struct SignedMagnitude { bool negative = false; Multiplicity magnitude{}; };
struct Entry { storage::Tuple tuple; Multiplicity multiplicity; };
struct Change {
  storage::Tuple tuple;
  Multiplicity before, after; // Exact nonnegative endpoint replacement; zero means absent.
  [[nodiscard]] SignedMagnitude delta() const noexcept {
    return {after < before, {after < before ? before.value - after.value : after.value - before.value}};
  }
};
class Runtime;

// Both actual original positive CQs, mode/arithmetic and the LEFT headed result
// schema are immutable account-backed semantics. The genuine source-only empty
// program supplies schemas/constraints, not a combined-query certificate.
class Binding {
  struct Data;
 public:
  Binding() noexcept = default;
  [[nodiscard]] explicit operator bool() const noexcept { return bool(data_); }
  [[nodiscard]] const program::Query& left() const &;
  const program::Query& left() const && = delete;
  [[nodiscard]] const program::Query& right() const &;
  const program::Query& right() const && = delete;
  [[nodiscard]] const Profile& profile() const &;
  const Profile& profile() const && = delete;
  [[nodiscard]] const CompiledProgram& sources() const &;
  const CompiledProgram& sources() const && = delete;
  [[nodiscard]] const storage::AccountedLayout& result_layout() const &;
  const storage::AccountedLayout& result_layout() const && = delete;
  [[nodiscard]] const resource::MemoryAccount& account() const &;
  const resource::MemoryAccount& account() const && = delete;
  [[nodiscard]] std::uint64_t multiplicity_limit() const;
 private:
  friend class Runtime;
  explicit Binding(std::shared_ptr<const Data> data) noexcept : data_(std::move(data)) {}
  [[nodiscard]] const Data& data() const;
  std::shared_ptr<const Data> data_;
};
template<class T> using OutputVector = std::vector<T, resource::OwnerAllocator<T>>;
using Cardinalities = fallback::Cardinalities;
struct Snapshot { std::uint64_t sequence; Binding binding; OutputVector<Entry> rows; Metrics metrics; };
struct Epoch { PhysicalEpoch input; Binding binding; OutputVector<Change> changes; Metrics metrics; };
struct Explain {
  Profile profile;
  Cardinalities table_rows;
  std::uint64_t result_rows, multiplicity_limit;
  std::optional<std::uint64_t> total_multiplicity;
  std::optional<std::uint64_t> left_witness_product, right_witness_product;
  std::optional<std::uint64_t> left_prefix_product_sum, right_prefix_product_sum;
  resource::MemoryStatistics memory;
};

// One full-catalog physical SET source owner. Complete physical-row choices
// define operand bags; ignored columns/aliases/projection can add multiplicity,
// while duplicate full physical inserts stay no-ops. SET EXCEPT uses presence;
// BAG EXCEPT ALL uses max(left-right,0). Results are compressed positive counts,
// never expanded copies. Changes are endpoint replacements, not aggregate
// signed payloads, SQL NULL semantics, weighted source inputs or negation cycles.
// Exact recomputation and all fallible result work precede the existing source
// commit and noexcept answer/count swap. Calls on one owner are serialized.
class Runtime {
  struct Data;
 public:
  explicit Runtime(const planner::difference::Plan&, Options = {});
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
  [[nodiscard]] Epoch apply(const PhysicalSetUpdate&);
  [[nodiscard]] Snapshot snapshot(Limits = {}) const;
  [[nodiscard]] Explain explain() const;
  // Explicit external diagnostic Database export; internal evaluation uses
  // only charged native SourceImage rows, never an ordinary database mirror.
  [[nodiscard]] Database source_snapshot() const;
 private:
  [[nodiscard]] Data& data() const;
  resource::AccountedUnique<Data> data_;
};
} // namespace crown::runtime::difference
