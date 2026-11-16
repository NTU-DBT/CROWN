#include "crown/catalog/catalog.hpp"
#include "crown/ir/program_model.hpp"

#include "crown/api/error.hpp"
#include <algorithm>
#include <set>
#include <string>

namespace crown::catalog {
namespace {
void require(bool condition, const std::string& message) {
  if (!condition) throw Error("invalid_catalog", message);
}
void unique_name(std::set<std::string>& names, std::string_view name, const std::string& kind) {
  require(!name.empty(), kind + " name must not be empty");
  require(names.insert(std::string(name)).second, "duplicate " + kind + " name: " + std::string(name));
}
std::set<ColumnId> column_set(const auto& table, const auto& columns) {
  std::set<ColumnId> seen;
  for (const auto column : columns) {
    require(column.value < table.columns.size(), "column ID out of range in table " + std::string(table.name));
    require(seen.insert(column).second, "duplicate key column in table " + std::string(table.name));
  }
  return seen;
}
void valid_status(ConstraintStatus status) {
  require(status == ConstraintStatus::enforced || status == ConstraintStatus::untrusted, "unknown constraint status");
}
void valid_decimal_spec(DecimalSpec specification) {
  require(specification.precision >= 1 && specification.precision <= 38 && specification.scale <= specification.precision,
          "decimal requires 1 <= precision <= 38 and 0 <= scale <= precision");
}
Row project(const Row& row, const auto& columns) {
  Row key;
  key.reserve(columns.size());
  for (const auto column : columns) key.push_back(row[column.value]);
  return key;
}
}  // namespace

bool decimal_fits(const Decimal& value, DecimalSpec specification) {
  valid_decimal_spec(specification);
  const auto text = value.to_string();
  const auto begin = text[0] == '-' ? 1U : 0U;
  const auto point = text.find('.');
  const auto integer_end = point == std::string::npos ? text.size() : point;
  const auto integer_digits = text[begin] == '0' ? 0 : integer_end - begin;
  const auto fractional_digits = point == std::string::npos ? 0 : text.size() - point - 1;
  return fractional_digits <= specification.scale && integer_digits + specification.scale <= specification.precision;
}

template<class CatalogView> void validate_catalog_impl(const CatalogView& catalog) {
  require(catalog.version > 0, "catalog version must be positive");
  std::set<std::string> tables;
  for (const auto& table : catalog.tables) {
    unique_name(tables, table.name, "table");
    require(table.source_schema_version > 0, "source schema version must be positive: " + std::string(table.name));
    std::set<std::string> columns;
    for (const auto& column : table.columns) {
      unique_name(columns, column.name, "column");
      try { static_cast<void>(type_name(column.type)); }
      catch (const Error&) { throw Error("invalid_catalog", "unknown scalar type at " + std::string(table.name) + "." + std::string(column.name)); }
      if (column.collation != Collation::binary) {
        throw Error("unsupported_collation", "only binary string collation is implemented at " + std::string(table.name) + "." + std::string(column.name));
      }
      if (column.decimal) {
        require(column.type == ScalarType::decimal, "decimal specification on non-decimal column " + std::string(table.name) + "." + std::string(column.name));
        valid_decimal_spec(*column.decimal);
      }
    }
    std::set<std::string> constraint_names;
    for (const auto& constraint : table.constraints) {
      std::visit([&](const auto& item) {
        unique_name(constraint_names, item.name, "constraint");
        valid_status(item.status);
        static_cast<void>(column_set(table, item.columns));
      }, constraint);
    }
    std::set<std::set<ColumnId>> estimates;
    for (const auto& estimate : table.statistics.distinct_counts) {
      require(estimates.insert(column_set(table, estimate.columns)).second,
              "duplicate distinct-count estimate for a column set in " + std::string(table.name));
    }
    for (const auto& hint : table.key_hints) {
      static_cast<void>(column_set(table, hint.columns));
      require(!hint.reason.empty(), "key hint requires a reason in " + std::string(table.name));
    }
  }
  // Resolve foreign targets only after all table declarations have been checked.
  for (const auto& table : catalog.tables) {
    for (const auto& constraint : table.constraints) {
      const auto* foreign = std::get_if<1>(&constraint);
      if (!foreign) continue;
      require(foreign->referenced_table.value < catalog.tables.size(), "foreign-key table ID out of range: " + std::string(foreign->name));
      const auto& target = catalog.tables[foreign->referenced_table.value];
      const auto target_columns = column_set(target, foreign->referenced_columns);
      require(foreign->columns.size() == foreign->referenced_columns.size(), "foreign-key column counts differ: " + std::string(foreign->name));
      for (std::size_t i = 0; i < foreign->columns.size(); ++i) {
        require(table.columns[foreign->columns[i].value].type == target.columns[foreign->referenced_columns[i].value].type,
                "foreign-key column types differ: " + std::string(foreign->name));
      }
      if (foreign->status == ConstraintStatus::enforced) {
        const bool unique_target = std::any_of(target.constraints.begin(), target.constraints.end(), [&](const auto& candidate) {
          const auto* unique = std::get_if<0>(&candidate);
          return unique && unique->status == ConstraintStatus::enforced &&
                 std::set<ColumnId>(unique->columns.begin(), unique->columns.end()) == target_columns;
        });
        require(unique_target, "enforced foreign key requires an enforced unique target: " + std::string(foreign->name));
      }
    }
  }
}
void validate_catalog(const Catalog& catalog){return validate_catalog_impl(catalog);}
void validate_catalog(const program::Catalog& catalog){return validate_catalog_impl(catalog);}


template<class CatalogView> void validate_constraints_impl(const CatalogView& catalog, const Database& database) {
  validate_catalog(catalog);
  if (database.tables.size() != catalog.tables.size()) throw Error("invalid_database", "database/catalog table count differs");
  // This public reference checker validates shape before projecting IDs. It is
  // intentionally a full scan; indexed constraint enforcement is later work.
  for (std::size_t i = 0; i < database.tables.size(); ++i) {
    for (const auto& row : database.tables[i]) validate_row(catalog, TableId{i}, row);
  }
  for (std::size_t i = 0; i < catalog.tables.size(); ++i) {
    const auto& table = catalog.tables[i];
    for (const auto& constraint : table.constraints) {
      if (const auto* unique = std::get_if<0>(&constraint)) {
        if (unique->status != ConstraintStatus::enforced) continue;
        Relation keys;
        for (const auto& row : database.tables[i]) {
          if (!keys.insert(project(row, unique->columns)).second) {
            throw Error("constraint_violation", "unique constraint " + std::string(table.name) + "." + std::string(unique->name) + " is violated");
          }
        }
      } else {
        const auto& foreign = std::get<1>(constraint);
        if (foreign.status != ConstraintStatus::enforced) continue;
        Relation target_keys;
        for (const auto& row : database.tables[foreign.referenced_table.value]) target_keys.insert(project(row, foreign.referenced_columns));
        for (const auto& row : database.tables[i]) {
          if (!target_keys.contains(project(row, foreign.columns))) {
            throw Error("constraint_violation", "foreign key " + std::string(table.name) + "." + std::string(foreign.name) + " is violated");
          }
        }
      }
    }
  }
}
void validate_constraints(const Catalog& catalog, const Database& database){return validate_constraints_impl(catalog,database);}
void validate_constraints(const program::Catalog& catalog, const Database& database){return validate_constraints_impl(catalog,database);}


template<class CatalogView> bool requires_format3_impl(const CatalogView& catalog) {
  for (const auto& table : catalog.tables) {
    if (table.source_schema_version != 1 || !table.constraints.empty() || table.statistics.row_count ||
        !table.statistics.distinct_counts.empty() || !table.key_hints.empty()) return true;
    for (const auto& column : table.columns) {
      if (column.nullable || column.collation != Collation::binary || column.decimal) return true;
    }
  }
  return false;
}
bool requires_format3(const Catalog& catalog){return requires_format3_impl(catalog);}
bool requires_format3(const program::Catalog& catalog){return requires_format3_impl(catalog);}


template<class CatalogView> TableId find_table_impl(const CatalogView& catalog, std::string_view name) {
  validate_catalog(catalog);
  for (std::size_t i = 0; i < catalog.tables.size(); ++i) {
    if (catalog.tables[i].name == name) return TableId{i};
  }
  throw Error("unknown_table", "unknown table: " + std::string(name));
}
TableId find_table(const Catalog& catalog, std::string_view name){return find_table_impl(catalog,name);}
TableId find_table(const program::Catalog& catalog, std::string_view name){return find_table_impl(catalog,name);}


ColumnReference resolve_column(const Catalog& catalog, std::span<const RelationBinding> bindings,
                               std::optional<std::string_view> qualifier, std::string_view name) {
  validate_catalog(catalog);
  std::set<std::string> qualifiers;
  for (const auto& binding : bindings) {
    if (binding.table.value >= catalog.tables.size() || binding.qualifier.empty()) throw Error("invalid_binding", "invalid table binding");
    if (!qualifiers.insert(binding.qualifier).second) throw Error("duplicate_alias", "duplicate relation alias: " + binding.qualifier);
  }
  if (qualifier && !qualifiers.contains(std::string(*qualifier))) throw Error("unknown_qualifier", "unknown relation qualifier: " + std::string(*qualifier));
  std::optional<ColumnReference> found;
  std::string candidate;
  for (std::size_t i = 0; i < bindings.size(); ++i) {
    const auto& binding = bindings[i];
    if (qualifier && binding.qualifier != *qualifier) continue;
    const auto& columns = catalog.tables[binding.table.value].columns;
    for (std::size_t j = 0; j < columns.size(); ++j) {
      if (columns[j].name != name) continue;
      const auto next_candidate = binding.qualifier + "." + std::string(name);
      if (found) throw Error("ambiguous_column", "ambiguous column " + std::string(name) + ": " + candidate + " and " + next_candidate);
      found = ColumnReference{i, ColumnId{j}};
      candidate = next_candidate;
    }
  }
  if (!found) throw Error("unknown_column", "unknown column: " + (qualifier ? std::string(*qualifier) + "." : "") + std::string(name));
  return *found;
}

void require_identity_cast(ScalarType source, ScalarType target) {
  const auto source_name = type_name(source);
  const auto target_name = type_name(target);
  if (source != target) throw Error("unsupported_cast", "cast from " + source_name + " to " + target_name + " is not implemented");
}
void require_identity_cast(const Column& source, const Column& target) {
  require_identity_cast(source.type, target.type);
  if (source.nullable != target.nullable) throw Error("unsupported_nullability", "identity casts preserve declared nullability; an explicit adapter must establish non-nullness");
  if (source.collation != Collation::binary || target.collation != Collation::binary) {
    throw Error("unsupported_collation", "only binary string collation is implemented");
  }
  for (const auto* column : {&source, &target}) {
    if (column->decimal) {
      require(column->type == ScalarType::decimal, "decimal specification requires a decimal type");
      valid_decimal_spec(*column->decimal);
    }
  }
  if (source.decimal != target.decimal) throw Error("unsupported_cast", "casts changing decimal precision or scale are not implemented");
}
}  // namespace crown::catalog
