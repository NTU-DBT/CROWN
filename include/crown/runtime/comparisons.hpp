#pragma once

#include "crown/planner/comparisons.hpp"
#include "crown/runtime/physical.hpp"
#include "crown/resource/owner_allocator.hpp"
#include <memory>
#include <span>
#include <variant>

namespace crown::runtime::comparisons {
using Operator = planner::comparisons::Operator;
using Operand = std::variant<VariableId, storage::ScalarView>;
struct Predicate { Operand left; Operator operation; Operand right; };
struct Limits {
  std::uint64_t work = 1'000'000; // One shared wrapper grant, including row/scalar/byte work.
  std::uint64_t producer_work = 1'000'000; // Cumulative whole-assignment cursor grant.
  std::uint64_t rows = 65536; // Maximum distinct retained snapshot rows.
};
struct Options { PhysicalRuntimeOptions sources; Limits recompute; };
struct Metrics {
  std::uint64_t work = 0, producer_work = 0, view_work = 0;
  std::uint64_t witnesses = 0, predicate_tests = 0, projected = 0, duplicates = 0;
  std::uint64_t scalar_fields = 0, scalar_bytes = 0, row_comparisons = 0;
  std::uint64_t outputs = 0, added = 0, removed = 0;
  bool recomputed = false;
};
class Runtime;

// Genuine equality-program provenance plus the ACTUAL comparison conjunction.
// Scalar/string views borrow this immutable original-account owner. Keeping a
// Binding preserves its schema and constants after the runtime is destroyed.
// program().guarantee() remains the original equality-only execution profile;
// this object is not a canonical comparison identity or durability authority.
class Binding {
  struct Data;
 public:
  Binding() noexcept = default;
  [[nodiscard]] explicit operator bool() const noexcept { return bool(data_); }
  [[nodiscard]] const CompiledProgram& program() const &;
  const CompiledProgram& program() const && = delete;
  [[nodiscard]] std::span<const Predicate> predicates() const &;
  std::span<const Predicate> predicates() const && = delete;
  [[nodiscard]] const resource::MemoryAccount& account() const &;
  const resource::MemoryAccount& account() const && = delete;
 private:
  friend class Runtime;
  explicit Binding(std::shared_ptr<const Data> data) noexcept : data_(std::move(data)) {}
  [[nodiscard]] const Data& data() const;
  std::shared_ptr<const Data> data_;
};
using TupleVector = std::vector<storage::Tuple, resource::OwnerAllocator<storage::Tuple>>;
struct Snapshot {
  std::uint64_t sequence;
  Binding binding;
  TupleVector rows; // Sorted distinct full-head rows; immutable native payloads are shared.
  Metrics metrics;
};
struct Epoch {
  PhysicalEpoch input; // Original source/support epoch, NOT comparison answer deltas.
  Binding binding;
  TupleVector added, removed; // Exact endpoint SET differences, original ordered/repeated head.
  Metrics metrics;
};

// Exact comparison wrapper over one genuine PhysicalRuntime. Updates use its
// ordinary propagation, then privately recompute from COMPLETE assignments,
// filter before projection and deduplicate. Source/result publication shares
// one barrier; no second undo journal or source/database clone is introduced.
// Calls on an owner, including diagnostics, must be serialized. Snapshots and
// epoch rows own their payloads and do not pin a future writable source epoch.
// Refusal leaves committed sources/results/sequence unchanged. Recomputation,
// ordered comparisons, scalar bytes, output copying, allocation and cleanup
// have their actual costs; no CQC/paper update bound or lazy-delay claim.
class Runtime {
  struct Data;
 public:
  explicit Runtime(const planner::comparisons::Plan&, Options = {});
  ~Runtime();
  Runtime(Runtime&&) noexcept;
  Runtime& operator=(Runtime&&) noexcept;
  Runtime(const Runtime&) = delete;
  Runtime& operator=(const Runtime&) = delete;
  [[nodiscard]] const CompiledProgram& program() const &;
  const CompiledProgram& program() const && = delete;
  [[nodiscard]] const Binding& binding() const &;
  const Binding& binding() const && = delete;
  [[nodiscard]] const resource::MemoryAccount& account() const &;
  const resource::MemoryAccount& account() const && = delete;
  [[nodiscard]] bool ready() const;
  [[nodiscard]] std::uint64_t sequence() const;
  [[nodiscard]] bool has_answer() const;
  [[nodiscard]] Epoch apply(const PhysicalSetUpdate&);
  // Eager funded handle copy; no witness recomputation or source reader lease.
  [[nodiscard]] Snapshot snapshot(Limits = {}) const;
  // Explicit diagnostic DTO export; standard Database/string copies belong
  // to the external caller, rather than the internal retained representation.
  [[nodiscard]] Database source_snapshot() const;
 private:
  [[nodiscard]] Data& data() const;
  resource::AccountedUnique<Data> data_;
};
} // namespace crown::runtime::comparisons
