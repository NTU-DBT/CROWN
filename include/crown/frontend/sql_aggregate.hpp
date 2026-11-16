#pragma once

#include "crown/frontend/aggregate.hpp"
#include "crown/frontend/sql_rows.hpp"
#include <array>

namespace crown::frontend {
namespace detail { class SqlAggregateCompiler; }

// One resolved physical SQL column, with separate normalized decode metadata.
// Equal decoded values do not merge different original grouping identities.
// Read presence before payload. ExpressionId reads source.initial_values().
struct SqlAggregateInput {
  SqlType type;
  BoundColumn origin;
  std::size_t source_output;
  std::variant<SqlRowsResultField, ExpressionId> value;
};
struct SqlAggregateIdentity {
  std::array<char, 64> original_sql, catalog, source, kernel, decode, binding;
};
struct SqlAggregateWork {
  std::uint64_t composition = 0, origin_binding = 0;
  std::uint64_t source_normalization = 0, kernel_binding = 0;
};
struct SqlAggregateBindOptions {
  SqlRowsBindOptions source;
  AggregateBindOptions kernel;
  ParseLimits parsing;
  std::optional<std::uint64_t> work_limit = 1000000;
  std::size_t derived_sql_bytes = 1024 * 1024;
  std::uint64_t memory_limit_bytes = 32ULL * 1024 * 1024;
};

// Created only from original SQL/catalog/options through actual row/aggregate
// factories. This metadata supplies no checked tree, plan, height or recovery
// authority. The coordinator must construct its source from source_program().
class SqlAggregateProgram {
  struct Data;
 public:
  SqlAggregateProgram() noexcept = default;
  // Cold import from an actual factory handle; no parsing or descriptor DTO.
  // Historic compiler identities/work remain unchanged by the funded copy.
  [[nodiscard]] static SqlAggregateProgram freeze(const resource::MemoryAccount&, const SqlAggregateProgram&);
  [[nodiscard]] explicit operator bool() const noexcept { return bool(data_); }
  [[nodiscard]] std::string_view original_sql() const &;
  std::string_view original_sql() const && = delete;
  [[nodiscard]] const SqlRowsProgram& source_program() const &;
  const SqlRowsProgram& source_program() const && = delete;
  [[nodiscard]] const AggregateProgram& kernel_program() const &;
  const AggregateProgram& kernel_program() const && = delete;
  [[nodiscard]] std::size_t native_fields() const;
  [[nodiscard]] std::span<const SqlAggregateInput> inputs() const &;
  std::span<const SqlAggregateInput> inputs() const && = delete;
  // Cold provenance: occurrence-order original references -> canonical inputs.
  [[nodiscard]] std::span<const std::size_t> reference_columns() const &;
  std::span<const std::size_t> reference_columns() const && = delete;
  [[nodiscard]] const SqlAggregateIdentity& identity() const &;
  const SqlAggregateIdentity& identity() const && = delete;
  // Exact versioned CBOR binding; binary bytes, not an editable program DTO.
  [[nodiscard]] std::string_view binding_image() const &;
  std::string_view binding_image() const && = delete;
  // Non-null only for an authenticated zero-occurrence source. Kernel always
  // starts FROM-empty; only the coordinator may bootstrap this source weight.
  [[nodiscard]] std::optional<std::uint64_t> static_source_weight() const;
  [[nodiscard]] SqlAggregateWork work() const;
  [[nodiscard]] const resource::MemoryAccount& account() const &;
  const resource::MemoryAccount& account() const && = delete;
 private:
  friend class detail::SqlAggregateCompiler;
  explicit SqlAggregateProgram(std::shared_ptr<const Data> value) noexcept : data_(std::move(value)) {}
  [[nodiscard]] const Data& data() const;
  std::shared_ptr<const Data> data_;
};
using SqlAggregateBindResult = std::variant<SqlAggregateProgram, BindingDiagnostic>;

// Parser/JSON/upb/deparser/cold binder workspace follows existing frontend
// allocation conventions; retained metadata uses this one receiving account.
// Parameters are admitted in source predicates by SqlRowsBindOptions; aggregate
// argument parameters remain unsupported. _into does not create a new grant.
[[nodiscard]] SqlAggregateBindResult bind_sql_aggregate(std::string_view, const Catalog&,
    const SqlAggregateBindOptions& = {});
[[nodiscard]] SqlAggregateBindResult bind_sql_aggregate_into(const resource::MemoryAccount&,
    std::string_view, const Catalog&, const SqlAggregateBindOptions& = {});
}  // namespace crown::frontend
