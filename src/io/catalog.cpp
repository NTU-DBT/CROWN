#include "crown/io/catalog.hpp"

#include "crown/catalog/catalog.hpp"
#include "json.hpp"
#include <algorithm>
#include <string>

namespace crown::io {
namespace {
using namespace detail;
ScalarType scalar_type(const Json& input) {
  const auto name = string(input, "column.type");
  for (const auto type : {ScalarType::int64, ScalarType::string, ScalarType::boolean, ScalarType::date, ScalarType::decimal}) {
    if (name == type_name(type)) return type;
  }
  throw Error("unsupported_type", "unsupported scalar type " + name);
}
ConstraintStatus status(const Json& input) {
  const auto name = string(input, "constraint.status");
  if (name == "enforced") return ConstraintStatus::enforced;
  if (name == "untrusted") return ConstraintStatus::untrusted;
  throw Error("invalid_catalog", "constraint status must be enforced or untrusted");
}
std::vector<ColumnId> column_ids(const Table& table, const Json& input) {
  std::vector<ColumnId> result;
  for (const auto& item : array(input, "columns")) {
    const auto name = string(item, "column reference");
    const auto found = std::find_if(table.columns.begin(), table.columns.end(), [&](const auto& column) { return column.name == name; });
    if (found == table.columns.end()) throw Error("invalid_catalog", "unknown column " + table.name + "." + name);
    result.push_back(ColumnId{static_cast<std::size_t>(found - table.columns.begin())});
  }
  return result;
}
Json column_names(const Table& table, const std::vector<ColumnId>& columns) {
  auto result = Json::array();
  for (const auto column : columns) result.push_back(table.columns[column.value].name);
  return result;
}
}  // namespace

Catalog read_catalog_payload(const Json& input) {
  fields(input, "catalog", {"version", "tables"});
  Catalog catalog;
  catalog.version = unsigned_integer(input.at("version"), "catalog.version");
  const auto& inputs = array(input.at("tables"), "catalog.tables");
  for (const auto& item : inputs) {
    fields(item, "table", {"name", "columns"}, {"source_schema_version", "constraints", "statistics", "key_hints"});
    Table table{string(item.at("name"), "table.name"), {}};
    if (item.contains("source_schema_version")) table.source_schema_version = unsigned_integer(item.at("source_schema_version"), "table.source_schema_version");
    for (const auto& cell : array(item.at("columns"), "table.columns")) {
      fields(cell, "column", {"name", "type"}, {"nullable", "collation", "decimal"});
      Column column{string(cell.at("name"), "column.name"), scalar_type(cell.at("type"))};
      if (cell.contains("nullable")) {
        if (!cell.at("nullable").is_boolean()) fail("column.nullable", "expected bool");
        column.nullable = cell.at("nullable").get<bool>();
      }
      if (cell.contains("collation")) {
        const auto name = string(cell.at("collation"), "column.collation");
        if (column.type != ScalarType::string || name != "binary") throw Error("unsupported_collation", "only binary collation on string columns is implemented");
      }
      if (cell.contains("decimal")) {
        const auto& specification = cell.at("decimal");
        fields(specification, "column.decimal", {"precision", "scale"});
        const auto precision = unsigned_integer(specification.at("precision"), "decimal.precision");
        const auto scale = unsigned_integer(specification.at("scale"), "decimal.scale");
        if (precision > 38 || scale > 38) throw Error("invalid_catalog", "decimal precision/scale must not exceed 38");
        column.decimal = DecimalSpec{static_cast<std::uint32_t>(precision), static_cast<std::uint32_t>(scale)};
      }
      table.columns.push_back(std::move(column));
    }
    catalog.tables.push_back(std::move(table));
  }
  // Foreign keys may point forward or back to any declared physical relation.
  for (std::size_t i = 0; i < inputs.size(); ++i) {
    const auto& item = inputs[i];
    auto& table = catalog.tables[i];
    if (item.contains("constraints")) {
      for (const auto& constraint : array(item.at("constraints"), "table.constraints")) {
        if (!constraint.is_object() || !constraint.contains("kind")) fail("constraint", "expected object with kind");
        const auto kind = string(constraint.at("kind"), "constraint.kind");
        if (kind == "unique") {
          fields(constraint, "unique constraint", {"kind", "name", "columns", "status"});
          table.constraints.emplace_back(UniqueConstraint{string(constraint.at("name"), "constraint.name"),
              column_ids(table, constraint.at("columns")), status(constraint.at("status"))});
        } else if (kind == "foreign_key") {
          fields(constraint, "foreign key", {"kind", "name", "columns", "status", "references"});
          const auto& reference = constraint.at("references");
          fields(reference, "foreign key references", {"table", "columns"});
          const auto target_name = string(reference.at("table"), "references.table");
          const auto target = std::find_if(catalog.tables.begin(), catalog.tables.end(), [&](const auto& candidate) { return candidate.name == target_name; });
          if (target == catalog.tables.end()) throw Error("invalid_catalog", "unknown referenced table " + target_name);
          table.constraints.emplace_back(ForeignKeyConstraint{string(constraint.at("name"), "constraint.name"),
              column_ids(table, constraint.at("columns")), TableId{static_cast<std::size_t>(target - catalog.tables.begin())},
              column_ids(*target, reference.at("columns")), status(constraint.at("status"))});
        } else throw Error("unsupported_constraint", "unsupported constraint kind " + kind);
      }
    }
    if (item.contains("statistics")) {
      const auto& statistics = item.at("statistics");
      fields(statistics, "statistics", {}, {"row_count", "distinct_counts"});
      if (statistics.contains("row_count")) table.statistics.row_count = unsigned_integer(statistics.at("row_count"), "statistics.row_count");
      if (statistics.contains("distinct_counts")) {
        for (const auto& estimate : array(statistics.at("distinct_counts"), "statistics.distinct_counts")) {
          fields(estimate, "distinct estimate", {"columns", "estimate"});
          table.statistics.distinct_counts.push_back({column_ids(table, estimate.at("columns")), unsigned_integer(estimate.at("estimate"), "distinct estimate.estimate")});
        }
      }
    }
    if (item.contains("key_hints")) {
      for (const auto& hint : array(item.at("key_hints"), "table.key_hints")) {
        fields(hint, "key hint", {"columns", "reason"});
        table.key_hints.push_back({column_ids(table, hint.at("columns")), string(hint.at("reason"), "key hint.reason")});
      }
    }
  }
  // Schema declarations/statistics are metadata; no input row set is enforced here.
  catalog::validate_catalog(catalog);
  return catalog;
}

Json write_catalog_payload(const Catalog& catalog) {
  catalog::validate_catalog(catalog);
  auto tables = Json::array();
  for (const auto& table : catalog.tables) {
    auto columns = Json::array();
    for (const auto& column : table.columns) {
      Json output{{"name", column.name}, {"type", type_name(column.type)}, {"nullable", column.nullable}};
      if (column.type == ScalarType::string) output["collation"] = "binary";
      if (column.decimal) output["decimal"] = {{"precision", column.decimal->precision}, {"scale", column.decimal->scale}};
      columns.push_back(std::move(output));
    }
    auto constraints = Json::array();
    for (const auto& constraint : table.constraints) {
      std::visit([&](const auto& item) {
        constraints.push_back({{"name", item.name}, {"columns", column_names(table, item.columns)},
            {"status", item.status == ConstraintStatus::enforced ? "enforced" : "untrusted"}});
      }, constraint);
      if (const auto* foreign = std::get_if<ForeignKeyConstraint>(&constraint)) {
        constraints.back()["kind"] = "foreign_key";
        const auto& target = catalog.tables[foreign->referenced_table.value];
        constraints.back()["references"] = {{"table", target.name}, {"columns", column_names(target, foreign->referenced_columns)}};
      } else constraints.back()["kind"] = "unique";
    }
    Json statistics{{"distinct_counts", Json::array()}};
    if (table.statistics.row_count) statistics["row_count"] = *table.statistics.row_count;
    for (const auto& estimate : table.statistics.distinct_counts) {
      statistics["distinct_counts"].push_back({{"columns", column_names(table, estimate.columns)}, {"estimate", estimate.estimate}});
    }
    auto hints = Json::array();
    for (const auto& hint : table.key_hints) hints.push_back({{"columns", column_names(table, hint.columns)}, {"reason", hint.reason}});
    tables.push_back({{"name", table.name}, {"columns", std::move(columns)}, {"source_schema_version", table.source_schema_version},
        {"constraints", std::move(constraints)}, {"statistics", std::move(statistics)}, {"key_hints", std::move(hints)}});
  }
  return {{"version", catalog.version}, {"tables", std::move(tables)}};
}

Catalog read_catalog(std::string_view text) {
  const auto input = parse_json(text);
  fields(input, "$", {"schema_version", "catalog"});
  version(input.at("schema_version"), "$.schema_version");
  return read_catalog_payload(input.at("catalog"));
}
Json write_catalog(const Catalog& catalog) {
  return {{"schema_version", 1}, {"catalog", write_catalog_payload(catalog)}};
}
}  // namespace crown::io
