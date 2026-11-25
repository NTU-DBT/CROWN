#pragma once
// Flat bag-count executor: for a compiled free-connex CQ program it maintains
// COUNT(*) of every head tuple under signed base-row multiplicity changes
// (F-IVM-style cached child sums on the same tree, C* and enumeration program
// as runtime::FlatRuntime), and reports each changed group with its exact
// before/after count. Single writer; no accounting, journals or rollback.
#include "crown/ir/program.hpp"
#include "crown/runtime/flat.hpp"

#include <cstdint>
#include <memory>
#include <string>

namespace crown::runtime {

struct FlatCountSink {
  void* context = nullptr;
  // Counts are bag counts; 0 means the group is absent on that side.
  void (*group)(void* context, const std::int64_t* key, std::size_t size, std::uint64_t before,
      std::uint64_t after) = nullptr;
};

class FlatCountRuntime {
 public:
  [[nodiscard]] static std::string unsupported(const CompiledProgram& program);
  // options.delta: report every changed group during apply().
  explicit FlatCountRuntime(const CompiledProgram& program, FlatOptions options = {});
  ~FlatCountRuntime();
  FlatCountRuntime(FlatCountRuntime&&) noexcept;
  FlatCountRuntime& operator=(FlatCountRuntime&&) noexcept;
  FlatCountRuntime(const FlatCountRuntime&) = delete;
  FlatCountRuntime& operator=(const FlatCountRuntime&) = delete;

  void encode(TableId table, const Row& row, std::int64_t* out);
  [[nodiscard]] std::size_t arity(TableId table) const;
  // Adds delta (+1/-1) to the multiplicity of one base row; a multiplicity
  // may not become negative. Routes to every occurrence of the table in order.
  void apply(TableId table, std::int64_t delta, const std::int64_t* row, FlatCountSink sink = {});
  // Every current group with before = 0 and after = its count.
  void snapshot(FlatCountSink sink) const;
  [[nodiscard]] std::size_t result_arity() const;
  [[nodiscard]] Value decode(std::size_t column, std::int64_t value) const;

 private:
  struct Impl;
  std::unique_ptr<Impl> impl_;
};

}  // namespace crown::runtime
