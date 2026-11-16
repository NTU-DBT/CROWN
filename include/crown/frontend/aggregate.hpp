#pragma once

#include "crown/frontend/bind.hpp"
#include "crown/resource/memory.hpp"
#include "crown/storage/accounted_row.hpp"
#include <memory>
#include <span>
#include <string_view>

namespace crown::frontend {
namespace detail { class AggregateCompiler; }

// Argument views borrow the immutable program's accounted literal backing.
// A column alternative reads the resolved position in one logical input row.
using AggregateArgument = std::variant<ColumnId, std::optional<storage::ScalarView>>;
struct AggregateMeasure {
  SqlType type;
  AggregateArgument argument;
  bool sum = false;        // A SUM or AVG output needs the exact numerator.
  bool int64_sum = false;  // A requested SUM(int32) must fit its bigint output.
};
enum class AggregateOutputKind { group, count_all, count_value, sum, average };
struct AggregateOutput {
  std::string_view name;
  SqlType type;
  AggregateOutputKind kind;
  std::size_t index = 0;  // Group-key position or measure ID; unused for COUNT(*).
};
struct AggregateBindOptions {
  BindLimits limits;
  std::uint64_t memory_limit_bytes = 16ULL * 1024 * 1024;
  std::uint8_t average_scale = 18;
};

// Factory-owned aggregate descriptors; this grants no CROWN tree/height proof.
// Copies share the source owner, moves empty the source. Borrowed spans require
// a surviving handle. Final assignment/release can destroy all metadata.
class AggregateProgram {
  struct Data;
 public:
  AggregateProgram() noexcept = default;
  // Import genuine immutable metadata into one receiving account. Same-account
  // calls share; foreign programs clone/rebase constant and output-name backing.
  [[nodiscard]] static AggregateProgram freeze(const resource::MemoryAccount&, const AggregateProgram&);
  [[nodiscard]] explicit operator bool() const noexcept { return bool(data_); }
  [[nodiscard]] std::string_view source() const &;
  std::string_view source() const && = delete;
  [[nodiscard]] bool has_input() const;
  [[nodiscard]] bool full_input_group_key() const;
  [[nodiscard]] std::span<const SqlType> input_types() const &;
  std::span<const SqlType> input_types() const && = delete;
  [[nodiscard]] std::span<const ColumnId> group_columns() const &;
  std::span<const ColumnId> group_columns() const && = delete;
  // Original input positions whose contributing, non-NULL values must fit SQL
  // integer. Deduplicated even across nested casts; physical input types stay
  // unchanged. Shared projection checks these before any group state changes.
  [[nodiscard]] std::span<const ColumnId> checked_int32_columns() const &;
  std::span<const ColumnId> checked_int32_columns() const && = delete;
  [[nodiscard]] std::span<const AggregateMeasure> measures() const &;
  std::span<const AggregateMeasure> measures() const && = delete;
  [[nodiscard]] std::span<const AggregateOutput> outputs() const &;
  std::span<const AggregateOutput> outputs() const && = delete;
  [[nodiscard]] std::uint8_t average_scale() const;
  [[nodiscard]] std::uint64_t work() const;
  [[nodiscard]] const resource::MemoryAccount& account() const &;
  const resource::MemoryAccount& account() const && = delete;
 private:
  friend class detail::AggregateCompiler;
  explicit AggregateProgram(std::shared_ptr<const Data> value) noexcept : data_(std::move(value)) {}
  [[nodiscard]] const Data& data() const;
  std::shared_ptr<const Data> data_;
};
using AggregateBindResult = std::variant<AggregateProgram, BindingDiagnostic>;

// SQL errors return a diagnostic; parser contract failures propagate.
// Allocation/account failures also propagate. The standalone form creates a
// finite compiler account; _into preserves its supplied grant. Parser workspace
// is separate from retained metadata.
[[nodiscard]] AggregateBindResult bind_aggregate_sql(std::string_view, const Catalog&,
    const AggregateBindOptions& = {});
[[nodiscard]] AggregateBindResult bind_aggregate_sql_into(const resource::MemoryAccount&,
    std::string_view, const Catalog&, const AggregateBindOptions& = {});
}  // namespace crown::frontend
