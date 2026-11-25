#pragma once

#include "crown/frontend/bind.hpp"

namespace crown::frontend {
using SqlValue = std::optional<Value>;  // NULL stays outside the classical core.
// Counts selected compiler steps; catalog validation, copies and allocations
// are not bounded by this counter.
struct NormalizeLimits { std::optional<std::uint64_t> work_limit = 1000000; };
struct NormalizeOptions {
  // Parameter specialization is part of this normalized program's identity.
  // One entry per declared parameter; nullopt means SQL NULL, not unbound.
  std::vector<SqlValue> parameters;
  NormalizeLimits limits;
  std::uint64_t schema_version = 2;
};
struct AdapterProjection { VariableId variable; ExpressionId expression; };
struct ColumnEquality { ColumnId left; ColumnId right; };
struct ColumnConstant { ColumnId column; Value value; };
struct OccurrenceAdapter {
  OccurrenceId occurrence;
  TableId base;
  std::vector<ExpressionId> predicates;
  std::vector<ColumnId> non_null_columns;
  std::vector<ColumnEquality> equal_columns;
  std::vector<std::optional<VariableId>> column_classes;
  std::vector<AdapterProjection> projection;
  // Topologically ordered resolved expressions needed by this adapter.
  std::vector<ExpressionId> program;
  std::vector<ColumnConstant> constant_columns = {};
};
struct CoreOutput { std::size_t column; };
struct ConstantOutput { Value value; };
struct NormalizedOutput {
  std::string name;
  SqlType type;
  std::variant<CoreOutput, ConstantOutput> value;
};
struct NormalizedSql {
  BoundSql binding;
  std::vector<SqlValue> parameters;
  // Query-wide folded values, including SQL NULL. Nonconstant slots also hold
  // unused NULL sentinels; dependency metadata distinguishes those at compile time.
  std::vector<SqlValue> constants;
  Catalog core_catalog;
  Query core;
  std::vector<OccurrenceAdapter> adapters;
  std::vector<std::vector<OccurrenceId>> base_routes;
  std::vector<NormalizedOutput> outputs;
  NormalizeLimits limits;
  std::uint64_t work = 0;
  std::uint64_t schema_version = 2;
};
using SqlNormalizeResult = std::variant<NormalizedSql, BindingDiagnostic>;

// Equality normalization and executable input adapters, before structural
// admission/planning. The source catalog is flat and referenced inputs must
// declare every column non-null, including unused columns of referenced tables.
// Plain row-producing bags are explicitly rejected.
[[nodiscard]] SqlNormalizeResult normalize_sql(const BoundSql& binding, const NormalizeOptions& options = {});
[[nodiscard]] std::optional<Row> adapt_row(const NormalizedSql& query, OccurrenceId occurrence, const Row& physical);
// adapt_row into caller storage: `result` receives the core row (false when the
// occurrence filters the row out); `scratch` holds the expression slots. Both
// keep their capacity across calls, so a replay loop allocates nothing.
[[nodiscard]] bool adapt_row_into(const NormalizedSql& query, OccurrenceId occurrence, const Row& physical,
    Row& result, std::vector<std::optional<Value>>& scratch);
// Preserve ordered/repeated/constant outputs and the scalar EXISTS wrapper.
[[nodiscard]] Relation map_sql_result(const NormalizedSql& query, const Relation& core_result);
}  // namespace crown::frontend
