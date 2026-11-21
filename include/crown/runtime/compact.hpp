#pragma once

// Compact maintenance kernel for a lowered free-connex plan (PhysicalRoute::tree).
//
// It maintains the same S/P/E support state as SupportRuntime and produces the
// same signed result deltas as DeltaRuntime, but stores every relation as
// fixed-width 64-bit words: source rows and records in pooled slabs behind
// open-addressing hash indexes, and the members of every separator key in one
// contiguous array. A steady-state update performs no heap allocation: storage
// grows only when a slab, pool or hash directory doubles, and all of it is
// charged to one MemoryAccount.
//
// This is the fast path, not a replacement for the full runtime. It has no
// journal, no rollback, no epoch views, no checkpoint image, no observation
// trace and no work admission. See docs/handoff-performance.md for what is and
// is not covered and how it is checked against DeltaRuntime.
#include "crown/ir/physical.hpp"
#include "crown/resource/memory.hpp"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <span>

namespace crown::runtime::compact {

using Word = std::uint64_t;

struct Options {
  // Byte limit of the kernel's own account (slabs, list pool, directories).
  // The dictionary of non-integer scalars is outside it.
  std::uint64_t memory_limit_bytes = std::uint64_t{1} << 40;
  // Tree edges whose separators range over the same source columns (as in a
  // self-join) keep their per-key state in one shared row, so an update that
  // reaches several of them for one key value touches one row. Purely a
  // layout choice; false gives every edge its own table.
  bool shared_separators = true;
};

struct Statistics {
  std::uint64_t source_rows = 0;     // Live physical source rows over all base tables.
  std::uint64_t records = 0;         // Live native records and generalized candidates.
  std::uint64_t survivors = 0;
  std::uint64_t separator_keys = 0;  // Live separator rows (depends on Options::shared_separators).
  std::uint64_t visible_keys = 0;    // Live E entries over all connex nodes.
  std::uint64_t dictionary_values = 0;
  auto operator<=>(const Statistics&) const = default;
};

// Receives one result row as `result_arity()` encoded words, valid only during
// the call. Decode with Runtime::decode when owning values are needed.
class RowSink {
 public:
  virtual void row(const Word* words) = 0;
 protected:
  ~RowSink() = default;
};

// One encoded physical set event of a batch. `row` holds the table's arity in
// words and must stay valid for the call.
struct Update {
  TableId table;
  SetOperation operation = SetOperation::insert;
  const Word* row = nullptr;
};

class Runtime {
 public:
  explicit Runtime(const PhysicalPlan& plan, Options options = {});
  ~Runtime();
  Runtime(const Runtime&) = delete;
  Runtime& operator=(const Runtime&) = delete;
  Runtime(Runtime&&) noexcept;
  Runtime& operator=(Runtime&&) noexcept;

  // One physical full-row set event. Returns false, changing nothing, for a
  // duplicate insert or an absent erase. With a sink, every result row that
  // enters (insert) or leaves (erase) the query output is reported exactly
  // once, in an unspecified order; without one only the state is maintained.
  // A throwing sink or an exhausted memory limit leaves the kernel unusable:
  // there is no rollback on this path.
  bool apply(TableId table, SetOperation operation, const Row& row, RowSink* delta = nullptr);
  // The same event for a row that is already encoded: an int64 is its own
  // word, a bool is 0 or 1, and any other scalar is the word `encode` returns.
  // Not available for SQL-normalized plans, whose inputs need the row values.
  bool apply(TableId table, SetOperation operation, std::span<const Word> row, RowSink* delta = nullptr);
  [[nodiscard]] Word encode(const Value& value);
  // Applies encoded events in order with exactly the effect, and the same
  // delta rows in the same order, as one call of the word-level `apply` per
  // event; returns how many changed the state. Knowing the next events lets
  // the kernel start their memory loads early, which is what makes this
  // faster on states larger than the CPU cache. A batch that names an unknown
  // table or operation, or has a null row, is refused before any event of it
  // is applied.
  std::size_t apply(std::span<const Update> updates, RowSink* delta = nullptr);

  // Current complete result, each row once, in an unspecified order.
  void enumerate(RowSink& sink) const;
  [[nodiscard]] bool has_answer() const;

  [[nodiscard]] std::size_t result_arity() const;
  [[nodiscard]] Row decode(const Word* words) const;
  [[nodiscard]] Statistics statistics() const;
  [[nodiscard]] resource::MemoryStatistics memory_statistics() const;
  // Explicit diagnostic: rebuilds every derived structure (derivation counts,
  // presence masks, support counts, visible members, every per-key array with
  // its positions and payloads, the list pool) from the live rows alone and
  // throws Error on a difference.
  void check_invariants() const;

 private:
  struct Impl;
  std::unique_ptr<Impl> impl_;
};

}  // namespace crown::runtime::compact
