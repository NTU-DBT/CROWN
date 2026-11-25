#pragma once
// Flat CROWN executor: a lean, single-writer implementation of the exact-set
// free-connex maintenance and delta/snapshot enumeration algorithms for the
// same compiled program (tree, C*, separators and enumeration program) that
// DeltaRuntime executes. Values are encoded as fixed-width 64-bit words, every
// relation is an open-addressing hash table over pooled entries with intrusive
// separator buckets (the F-IVM/DynaGox layout), and each route mutates state in
// place. It deliberately omits the reference runtime's memory/work accounting,
// epoch journals, undo/rollback, observation and recovery: an exception leaves
// the executor unusable. See docs/flat_runtime.md.
#include "crown/ir/program.hpp"

#include <cstddef>
#include <cstdint>
#include <memory>
#include <span>
#include <string>

namespace crown::runtime {

struct FlatOptions {
  // Maintain globally-live (L) keys and emit one signed row per answer change
  // during apply(). Snapshot enumeration works in either mode.
  bool delta = false;
};

// Called once per emitted row with the encoded core-head values.
struct FlatSink {
  void* context = nullptr;
  void (*row)(void* context, SetOperation operation, const std::int64_t* values, std::size_t size) = nullptr;
};

struct FlatStatistics {
  std::uint64_t physical_events = 0, changed_events = 0, routes = 0, route_changes = 0;
  std::uint64_t changed_keys = 0, delta_rows = 0, snapshot_rows = 0;
};

class FlatRuntime {
 public:
  // Empty when supported; otherwise the first unsupported feature.
  [[nodiscard]] static std::string unsupported(const CompiledProgram& program);
  explicit FlatRuntime(const CompiledProgram& program, FlatOptions options = {});
  ~FlatRuntime();
  FlatRuntime(FlatRuntime&&) noexcept;
  FlatRuntime& operator=(FlatRuntime&&) noexcept;
  FlatRuntime(const FlatRuntime&) = delete;
  FlatRuntime& operator=(const FlatRuntime&) = delete;

  // Encode one physical source row (source catalog column order) into words.
  // Strings are interned; the dictionary is append-only.
  void encode(TableId table, const Row& row, std::int64_t* out);
  [[nodiscard]] std::size_t arity(TableId table) const;
  // Apply one physical set event to every occurrence route in order. Duplicate
  // inserts and absent erases are no-ops. In delta mode every signed answer
  // change is passed to sink before this returns.
  void apply(TableId table, SetOperation operation, const std::int64_t* row, FlatSink sink = {});
  // Enumerate the complete current answer.
  void snapshot(FlatSink sink) const;
  [[nodiscard]] std::size_t result_arity() const;
  [[nodiscard]] Value decode(std::size_t column, std::int64_t value) const;
  [[nodiscard]] const FlatStatistics& statistics() const;
  [[nodiscard]] FlatOptions options() const;

 private:
  struct Impl;
  std::unique_ptr<Impl> impl_;
};

}  // namespace crown::runtime
