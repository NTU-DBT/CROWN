#pragma once
// Flat exact-set executor for general (including cyclic) conjunctive queries:
// the incremental support-count algorithm of runtime::fallback (docs/fallback.md)
// over the flat word tables of runtime::FlatRuntime. Single writer; no memory,
// work or row grants, journals or rollback. See docs/flat_runtime.md.
#include "crown/ir/model.hpp"
#include "crown/runtime/flat.hpp"

#include <cstdint>
#include <memory>
#include <string>

namespace crown::runtime {

class FlatCyclicRuntime {
 public:
  [[nodiscard]] static std::string unsupported(const Catalog& catalog, const Query& query);
  FlatCyclicRuntime(const Catalog& catalog, const Query& query);
  ~FlatCyclicRuntime();
  FlatCyclicRuntime(FlatCyclicRuntime&&) noexcept;
  FlatCyclicRuntime& operator=(FlatCyclicRuntime&&) noexcept;
  FlatCyclicRuntime(const FlatCyclicRuntime&) = delete;
  FlatCyclicRuntime& operator=(const FlatCyclicRuntime&) = delete;

  void encode(TableId table, const Row& row, std::int64_t* out);
  [[nodiscard]] std::size_t arity(TableId table) const;
  // One physical set event; duplicate inserts and absent erases are no-ops.
  // Every answer that appears (insert) or disappears (erase) goes to sink.
  void apply(TableId table, SetOperation operation, const std::int64_t* row, FlatSink sink = {});
  void snapshot(FlatSink sink) const;
  [[nodiscard]] std::size_t answers() const;
  [[nodiscard]] std::size_t result_arity() const;
  [[nodiscard]] Value decode(std::size_t column, std::int64_t value) const;

 private:
  struct Impl;
  std::unique_ptr<Impl> impl_;
};

}  // namespace crown::runtime
