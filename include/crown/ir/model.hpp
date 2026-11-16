#pragma once

#include "crown/ir/scalar.hpp"
#include "crown/ir/ids.hpp"
#include <compare>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <set>
#include <string>
#include <variant>
#include <vector>

namespace crown {
namespace program {struct Catalog;}
enum class ScalarType { int64, string, boolean, date, decimal };
using Value = std::variant<std::int64_t, std::string, bool, Date, Decimal>;
using Row = std::vector<Value>;
using Relation = std::set<Row>;

enum class Collation { binary };
struct DecimalSpec {
  std::uint32_t precision;
  std::uint32_t scale;
  auto operator<=>(const DecimalSpec&) const = default;
};
struct Column {
  std::string name;
  ScalarType type;
  bool nullable = false;
  Collation collation = Collation::binary;
  std::optional<DecimalSpec> decimal = std::nullopt;
};
enum class ConstraintStatus { enforced, untrusted };
struct UniqueConstraint {
  std::string name;
  std::vector<ColumnId> columns;
  ConstraintStatus status = ConstraintStatus::untrusted;
};
struct ForeignKeyConstraint {
  std::string name;
  std::vector<ColumnId> columns;
  TableId referenced_table;
  std::vector<ColumnId> referenced_columns;
  ConstraintStatus status = ConstraintStatus::untrusted;
};
using Constraint = std::variant<UniqueConstraint, ForeignKeyConstraint>;
struct DistinctEstimate {
  std::vector<ColumnId> columns;
  std::uint64_t estimate;
};
struct TableStatistics {
  std::optional<std::uint64_t> row_count = std::nullopt;
  std::vector<DistinctEstimate> distinct_counts = {};
};
struct KeyHint {
  std::vector<ColumnId> columns;
  std::string reason;
};
struct Table {
  std::string name;
  std::vector<Column> columns;
  std::uint64_t source_schema_version = 1;
  std::vector<Constraint> constraints = {};
  TableStatistics statistics = {};
  std::vector<KeyHint> key_hints = {};
};
struct Catalog { std::uint64_t version = 1; std::vector<Table> tables; };
struct Variable { std::string name; ScalarType type; };
struct IgnoredColumn {};
using Term = std::variant<VariableId, Value, IgnoredColumn>;
struct Atom { std::string occurrence; TableId table; std::vector<Term> terms; };
struct Output { VariableId variable; std::string alias; };
struct Query {
  std::vector<Variable> variables;
  std::vector<Atom> atoms;
  std::vector<Output> head;
  bool contradiction = false;
};
struct Database { std::vector<Relation> tables; };
enum class SetOperation { insert, erase };
struct PhysicalSetUpdate {
  std::uint64_t sequence;
  TableId table;
  SetOperation operation;
  Row values;
};
struct SetDelta { Relation added; Relation removed; };
struct CommittedReferenceEpoch {
  std::uint64_t sequence;
  bool input_changed;
  Relation current;
  SetDelta delta;
};
struct Document {
  Catalog catalog;
  Query query;
  Database initial;
  std::vector<PhysicalSetUpdate> updates;
  std::uint64_t schema_version = 1;
};

[[nodiscard]] ScalarType type_of(const Value& value);
[[nodiscard]] std::string type_name(ScalarType type);
// Stable FNV-1a over tagged, length-delimited values and fixed little-endian
// integers. These are hash-table hashes, not cryptographic schema identities.
[[nodiscard]] std::uint64_t value_hash(const Value& value);
[[nodiscard]] std::uint64_t row_hash(const Row& row);
struct ValueHash {
  [[nodiscard]] std::size_t operator()(const Value& value) const { return static_cast<std::size_t>(value_hash(value)); }
};
struct RowHash {
  [[nodiscard]] std::size_t operator()(const Row& row) const { return static_cast<std::size_t>(row_hash(row)); }
};
void validate(const Catalog& catalog, const Query& query);
void validate_row(const Catalog& catalog, TableId table, const Row& row);
void validate_database(const Catalog& catalog, const Database& database);
void validate_row(const program::Catalog& catalog, TableId table, const Row& row);
void validate_database(const program::Catalog& catalog, const Database& database);
}  // namespace crown
