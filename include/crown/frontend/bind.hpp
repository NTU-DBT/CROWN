#pragma once

#include "crown/frontend/parser.hpp"
#include "crown/ir/model.hpp"

namespace crown::frontend {
using OccurrenceId = crown::OccurrenceId;
struct ExpressionId { std::size_t value; auto operator<=>(const ExpressionId&) const = default; };
enum class SqlKind { unknown, int32, int64, string, boolean, date, decimal };
struct SqlType {
  SqlKind kind = SqlKind::unknown;
  bool nullable = false;
  std::optional<DecimalSpec> decimal = std::nullopt;
  auto operator<=>(const SqlType&) const = default;
};
struct BoundColumn { OccurrenceId occurrence; ColumnId column; };
// NULL belongs only to the SQL boundary. It is not a crown::Value.
struct BoundLiteral { std::optional<Value> value; };
struct BoundParameter { std::size_t number; };  // One based.
enum class SqlOperator {
  equal, not_equal, less, less_equal, greater, greater_equal,
  conjunction, disjunction, negation, is_null, is_not_null,
  is_true, is_not_true, is_false, is_not_false, is_unknown, is_not_unknown,
  identity_cast, literal_cast, widen_integer, using_value
};
struct BoundOperation { SqlOperator operation; std::vector<ExpressionId> arguments; };
using BoundNode = std::variant<BoundColumn, BoundLiteral, BoundParameter, BoundOperation>;
struct BoundExpression {
  SqlType type;
  BoundNode node;
  std::optional<std::size_t> location;
};
struct BoundOccurrence {
  TableId table;
  std::string alias;
  std::vector<std::string> column_names;
  std::optional<std::size_t> location;
  bool include_descendants = true;  // Requested SQL scan; this catalog has no inheritance edges.
};
struct BoundOutput { std::string name; ExpressionId expression; };
enum class SqlSemantics { set, bag };
enum class SqlWrapper { rows, exists };
struct BindLimits {
  std::optional<std::uint64_t> work_limit = 1000000;
  std::size_t expression_limit = 100000;
  std::size_t recursion_limit = 128;
};
struct BindOptions {
  std::vector<Column> parameters;
  BindLimits limits;
};
struct BoundSql {
  std::string source;
  Catalog catalog;
  std::vector<SqlType> parameters;
  SqlSemantics semantics = SqlSemantics::bag;
  std::optional<SqlSemantics> inner_semantics = std::nullopt;
  SqlWrapper wrapper = SqlWrapper::rows;
  std::string wrapper_alias = "exists";
  std::vector<BoundOccurrence> occurrences;
  std::vector<BoundExpression> expressions;
  std::vector<ExpressionId> predicates;
  std::vector<BoundOutput> outputs;  // Ordered SELECT outputs; inner outputs for EXISTS, whose outer name is wrapper_alias.
  BindLimits limits;
  std::uint64_t work = 0;
};
struct BindingDiagnostic { std::string phase; SqlDiagnostic diagnostic; };
using SqlBindResult = std::variant<BoundSql, BindingDiagnostic>;

// Parse and resolve one SELECT against an owned catalog snapshot. The returned
// alternative owns its data; caller source, catalog and options may then expire.
// Diagnostics distinguish syntax, catalog, parameter and binding rejection.
// Parser-contract failures and allocations outside Binder construction/run may
// escape as exceptions. This does not normalize, admit, plan or execute SQL.
// Catalog entries are flat physical relations, with no inheritance hierarchy.
[[nodiscard]] SqlBindResult bind_sql(std::string_view source, const Catalog& catalog, const BindOptions& options = {});
[[nodiscard]] std::string sql_kind_name(SqlKind kind);
[[nodiscard]] std::string sql_operator_name(SqlOperator operation);
}  // namespace crown::frontend
