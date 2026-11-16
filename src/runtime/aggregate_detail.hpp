#pragma once

// Private shared W04 group arithmetic. This is not an input admission port.
// Immutable factory programs and authenticated callers establish scalar/count
// preconditions; owners provide scratch and the same receiving-account budget.
#include "crown/runtime/aggregate.hpp"
#include "crown/api/error.hpp"
#include "aggregate_integer.hpp"
#include <algorithm>
#include <cassert>
#include <map>
#include <utility>

namespace crown::runtime::aggregate::detail {
using frontend::AggregateOutputKind;
using frontend::SqlKind;
template<class T> using Items = std::vector<T, resource::MemoryAllocator<T>>;
template<class T> resource::MemoryAllocator<T> allocator(const resource::MemoryAccount& account,
    resource::MemoryPurpose purpose) { return resource::MemoryAllocator<T>(account, purpose); }
[[noreturn]] inline void fail(const char* code, const char* message) { throw Error(code, message); }

// Keys are immutable owned tuples; temporary probes borrow the per-call cells.
// NULL sorts before a present value, and byte strings retain exact equality.
struct Less {
  using is_transparent = void;
  static bool compare(std::span<const Cell> a, std::span<const Cell> b) noexcept {
    return std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end());
  }
  bool operator()(const Tuple& a, const Tuple& b) const noexcept { return compare(a.view(), b.view()); }
  bool operator()(const Tuple& a, std::span<const Cell> b) const noexcept { return compare(a.view(), b); }
  bool operator()(std::span<const Cell> a, const Tuple& b) const noexcept { return compare(a, b.view()); }
};
struct State {
  std::uint64_t count = 0;
  aggregate::detail::IntegerSum sum;
};
struct Group {
  std::uint64_t rows = 0;
  Items<State> values;
  Group(const resource::MemoryAccount& account, std::size_t size,
      resource::MemoryPurpose purpose = resource::MemoryPurpose::support_metadata)
      : values(size, State{}, allocator<State>(account, purpose)) {}
  // A touched proposal uses the exact persistent vector allocator so commit
  // can swap buffers. Copy only that group's states, without zero-then-copy.
  Group(const resource::MemoryAccount& account, const Group& source)
      : rows(source.rows), values(source.values.begin(), source.values.end(),
            allocator<State>(account, resource::MemoryPurpose::support_metadata)) {}
};
struct Budget {
  std::optional<std::uint64_t> limit;
  Metrics metrics;
  void take(std::uint64_t amount = 1) {
    if (amount > UINT64_MAX - metrics.work || (limit && amount > *limit - metrics.work))
      fail("aggregate_work_limit", "aggregate logical work limit exceeded");
    metrics.work += amount;
  }
};

// The temporary map uses the destination allocator. Extracted nodes can then
// publish without allocation; all throwing preparation remains private.
template<class Map, class Value>
typename Map::node_type node_for(Map& target, Tuple key, Value value) {
  Map prepared(target.key_comp(), target.get_allocator());
  const auto item = prepared.emplace(std::move(key), std::move(value)).first;
  return prepared.extract(item);
}
inline bool decimal_fits(const storage::InlineDecimal& value, DecimalSpec type) noexcept {
  const auto parts = value.parts();
  if (parts.digits == "0") return true;
  const auto integral = parts.digits.size() > parts.scale ? parts.digits.size() - parts.scale : 0;
  return parts.scale <= type.scale && integral <= type.precision - type.scale;
}

struct Borrows {
  std::span<Cell> first, second;
  ~Borrows() noexcept {
    std::fill(first.begin(), first.end(), Cell{});
    std::fill(second.begin(), second.end(), Cell{});
  }
};

inline void validate(const frontend::AggregateProgram& program, std::span<const Cell> values, Budget& budget) {
  const auto types = program.input_types();
  if (values.size() != types.size()) fail("invalid_aggregate_row", "aggregate row arity differs from its input schema");
  for (std::size_t i = 0; i < values.size(); ++i) {
    budget.take(); ++budget.metrics.input_fields;
    if (!values[i]) {
      if (!types[i].nullable) fail("invalid_aggregate_row", "NULL entered a non-null aggregate input");
      continue;
    }
    const auto& value = *values[i]; bool valid = false;
    switch (types[i].kind) {
      case SqlKind::int32:
        valid = std::holds_alternative<std::int64_t>(value) &&
            std::get<std::int64_t>(value) >= INT32_MIN && std::get<std::int64_t>(value) <= INT32_MAX; break;
      case SqlKind::int64: valid = std::holds_alternative<std::int64_t>(value); break;
      case SqlKind::string:
        valid = std::holds_alternative<std::string_view>(value);
        if (valid) { const auto bytes = std::get<std::string_view>(value).size(); budget.take(bytes); budget.metrics.input_bytes += bytes; }
        break;
      case SqlKind::boolean: valid = std::holds_alternative<bool>(value); break;
      case SqlKind::date: valid = std::holds_alternative<Date>(value); break;
      case SqlKind::decimal:
        valid = std::holds_alternative<storage::InlineDecimal>(value);
        if (valid && types[i].decimal) valid = decimal_fits(std::get<storage::InlineDecimal>(value), *types[i].decimal);
        break;
      case SqlKind::unknown: break;
    }
    if (!valid) fail("invalid_aggregate_row", "aggregate input scalar has an incompatible type or decimal range");
  }
}
inline void project(const frontend::AggregateProgram& program, std::span<const Cell> values,
    std::span<Cell> key, Budget& budget) {
  // Validate contributing integer casts once per distinct input column. The
  // physical schema/decode has already established int64 storage. NULL passes;
  // failure precedes group mutation and uses the owner's existing rollback.
  for (const auto column : program.checked_int32_columns()) {
    budget.take();
    const auto& cell = values[column.value];
    if (cell) {
      const auto value = std::get<std::int64_t>(*cell);
      if (value < INT32_MIN || value > INT32_MAX)
        fail("aggregate_overflow", "aggregate integer cast exceeds its signed 32-bit range");
    }
  }
  const auto columns = program.group_columns();
  for (std::size_t i = 0; i < columns.size(); ++i) { budget.take(); key[i] = values[columns[i].value]; }
}
inline const Cell& argument(const frontend::AggregateMeasure& measure, std::span<const Cell> values) {
  if (const auto* column = std::get_if<ColumnId>(&measure.argument)) return values[column->value];
  return std::get<Cell>(measure.argument);
}
// The count and numerator change together from the same non-NULL argument.
// The group count was already admitted, establishing the private 127-bit bound.
template<bool CheckInt64 = true>
inline void adjust(const frontend::AggregateProgram& program, std::span<State> states,
    std::span<const Cell> values, std::uint64_t amount, bool erase, Budget& budget) {
  const auto measures = program.measures();
  for (std::size_t i = 0; i < measures.size(); ++i) {
    budget.take(); ++budget.metrics.measures;
    const auto& cell = argument(measures[i], values);
    if (!cell) continue;
    auto& state = states[i];
    if (erase) { assert(amount <= state.count); state.count -= amount; }
    else state.count += amount;
    if (measures[i].sum) state.sum.replace(std::get<std::int64_t>(*cell), amount, erase);
    if constexpr (CheckInt64) {
      if (measures[i].int64_sum && !state.sum.fits_int64())
        fail("aggregate_overflow", "SUM(integer) exceeds its bigint result range");
    }
  }
}
inline Tuple render(const resource::MemoryAccount& account, const frontend::AggregateProgram& program,
    std::span<Cell> output, std::span<const Cell> group_key, std::uint64_t count, std::span<const State> states,
    Budget& budget) {
  Borrows borrowed{output, {}};
  const auto outputs = program.outputs();
  for (std::size_t i = 0; i < outputs.size(); ++i) {
    budget.take(); ++budget.metrics.output_fields;
    const auto& item = outputs[i];
    switch (item.kind) {
      case AggregateOutputKind::group: output[i] = group_key[item.index]; break;
      case AggregateOutputKind::count_all: output[i] = storage::ScalarView{static_cast<std::int64_t>(count)}; break;
      case AggregateOutputKind::count_value:
        output[i] = storage::ScalarView{static_cast<std::int64_t>(states[item.index].count)}; break;
      case AggregateOutputKind::sum:
        if (!states[item.index].count) output[i].reset();
        else if (item.type.kind == SqlKind::int64) output[i] = storage::ScalarView{states[item.index].sum.int64_value()};
        else output[i] = storage::ScalarView{states[item.index].sum.value()};
        break;
      case AggregateOutputKind::average:
        if (!states[item.index].count) output[i].reset();
        else output[i] = storage::ScalarView{states[item.index].sum.average(states[item.index].count,
            static_cast<std::uint8_t>(item.type.decimal->scale))};
        break;
    }
  }
  return Tuple::copy_of(account, output, resource::MemoryPurpose::output_buffer);
}

// Final-only SUM(integer) check, shared by genuine prepared contributors and
// the standalone authenticated-row batch. Single-row adjust keeps its default.
inline void check_sums(const frontend::AggregateProgram& program, std::span<const State> states, Budget& budget) {
  const auto measures = program.measures();
  for (std::size_t i = 0; i < measures.size(); ++i) {
    budget.take(); ++budget.metrics.measures;
    if (measures[i].int64_sum && !states[i].sum.fits_int64())
      fail("aggregate_overflow", "final SUM(integer) exceeds its bigint result range");
  }
}
}  // namespace crown::runtime::aggregate::detail
