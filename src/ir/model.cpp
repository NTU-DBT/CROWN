#include "crown/ir/model.hpp"

#include "crown/api/error.hpp"
#include "crown/catalog/catalog.hpp"
#include "crown/ir/program_model.hpp"
#include <set>

namespace crown {
namespace {
void require(bool condition, const std::string& message) {
  if (!condition) throw Error("invalid_cq", message);
}
void unique_name(std::set<std::string>& names, const std::string& name, const std::string& kind) {
  require(!name.empty(), kind + " name must not be empty");
  require(names.insert(name).second, "duplicate " + kind + " name: " + name);
}
}  // namespace

ScalarType type_of(const Value& value) {
  if (std::holds_alternative<std::int64_t>(value)) return ScalarType::int64;
  if (std::holds_alternative<std::string>(value)) return ScalarType::string;
  if (std::holds_alternative<bool>(value)) return ScalarType::boolean;
  if (std::holds_alternative<Date>(value)) return ScalarType::date;
  if (std::holds_alternative<Decimal>(value)) return ScalarType::decimal;
  throw Error("invalid_cq", "value has no scalar type");
}
std::string type_name(ScalarType type) {
  switch (type) {
    case ScalarType::int64: return "int64";
    case ScalarType::string: return "string";
    case ScalarType::boolean: return "bool";
    case ScalarType::date: return "date";
    case ScalarType::decimal: return "decimal";
  }
  throw Error("invalid_cq", "unknown scalar type");
}

namespace {
// Public-value hashing can allocate while rendering Decimal text. Native
// compact scalar views have a separate hashing/work path.
class ValueHasher {
 public:
  void byte(std::uint8_t value) { hash_ = (hash_ ^ value) * 1099511628211ULL; }
  void integer(std::uint64_t value) {
    for (unsigned i = 0; i < 8; ++i) { byte(static_cast<std::uint8_t>(value & 0xff)); value >>= 8; }
  }
  void text(std::string_view value) {
    integer(value.size());
    for (char character : value) byte(static_cast<std::uint8_t>(static_cast<unsigned char>(character)));
  }
  void value(const Value& cell) {
    byte(static_cast<std::uint8_t>(cell.index()));
    if (const auto* integer_cell = std::get_if<std::int64_t>(&cell)) integer(static_cast<std::uint64_t>(*integer_cell));
    else if (const auto* string_cell = std::get_if<std::string>(&cell)) text(*string_cell);
    else if (const auto* boolean_cell = std::get_if<bool>(&cell)) byte(*boolean_cell ? 1 : 0);
    else if (const auto* date_cell = std::get_if<Date>(&cell)) integer(static_cast<std::uint64_t>(date_cell->epoch_days()));
    else if (const auto* decimal_cell = std::get_if<Decimal>(&cell)) text(decimal_cell->to_string());
    else throw Error("invalid_cq", "cannot hash a value without a scalar type");
  }
  [[nodiscard]] std::uint64_t get() const { return hash_; }
 private:
  std::uint64_t hash_ = 14695981039346656037ULL;
};
}  // namespace
std::uint64_t value_hash(const Value& value) {
  ValueHasher hasher;
  hasher.value(value);
  return hasher.get();
}
std::uint64_t row_hash(const Row& row) {
  ValueHasher hasher;
  hasher.integer(row.size());
  for (const auto& value : row) hasher.value(value);
  return hasher.get();
}

void validate(const Catalog& catalog, const Query& query) {
  try { catalog::validate_catalog(catalog); }
  catch (const Error& error) {
    if (error.code() == "invalid_catalog") throw Error("invalid_cq", error.what());
    throw;
  }
  for (const auto& table : catalog.tables) {
    for (const auto& column : table.columns) {
      if (column.nullable) throw Error("unsupported_nullability", "direct-CQ core requires non-null columns; an explicit adapter is needed for " + table.name + "." + column.name);
    }
  }
  std::set<std::string> variable_names;
  for (const auto& variable : query.variables) {
    unique_name(variable_names, variable.name, "variable");
    static_cast<void>(type_name(variable.type));
  }
  std::set<std::string> occurrences;
  std::set<VariableId> bound;
  for (const auto& atom : query.atoms) {
    unique_name(occurrences, atom.occurrence, "occurrence");
    require(atom.table.value < catalog.tables.size(), "atom table ID out of range");
    const auto& columns = catalog.tables[atom.table.value].columns;
    require(atom.terms.size() == columns.size(), "atom arity differs from physical schema: " + atom.occurrence);
    for (std::size_t i = 0; i < atom.terms.size(); ++i) {
      const auto& term = atom.terms[i];
      if (const auto* variable = std::get_if<VariableId>(&term)) {
        require(variable->value < query.variables.size(), "variable ID out of range");
        require(query.variables[variable->value].type == columns[i].type, "incompatible variable type in " + atom.occurrence);
        bound.insert(*variable);
      } else if (const auto* literal = std::get_if<Value>(&term)) {
        require(type_of(*literal) == columns[i].type, "incompatible constant type in " + atom.occurrence);
        if (columns[i].decimal && !catalog::decimal_fits(std::get<Decimal>(*literal), *columns[i].decimal)) {
          throw Error("scalar_overflow", "constant cannot be represented exactly by decimal specification in " + atom.occurrence + "." + columns[i].name);
        }
      }
    }
  }
  for (const auto& output : query.head) require(bound.contains(output.variable), "head variable is not bound in the body");
  require(bound.size() == query.variables.size(), "declared variables must occur in the body");
}

// Shape/type/decimal checks only; collection constraints are a separate call.
template<class CatalogView> void validate_row_impl(const CatalogView& catalog, TableId table, const Row& row) {
  if (table.value >= catalog.tables.size()) throw Error("invalid_update", "table ID out of range");
  const auto& columns = catalog.tables[table.value].columns;
  if (row.size() != columns.size()) throw Error("invalid_update", "row arity differs from physical schema");
  for (std::size_t i = 0; i < row.size(); ++i) {
    if (type_of(row[i]) != columns[i].type) throw Error("invalid_update", "row type differs at column " + std::string(columns[i].name));
    if (columns[i].decimal && columns[i].type != ScalarType::decimal) throw Error("invalid_catalog", "decimal specification requires a decimal column");
    if (columns[i].decimal && !catalog::decimal_fits(std::get<Decimal>(row[i]), *columns[i].decimal)) {
      throw Error("scalar_overflow", "row cannot be represented exactly by decimal specification at column " + std::string(columns[i].name));
    }
  }
}

void validate_row(const Catalog& catalog,TableId table,const Row& row){validate_row_impl(catalog,table,row);}
void validate_row(const program::Catalog& catalog,TableId table,const Row& row){validate_row_impl(catalog,table,row);}

void validate_database(const Catalog& catalog, const Database& database) {
  catalog::validate_constraints(catalog, database);
}
void validate_database(const program::Catalog& catalog,const Database& database){catalog::validate_constraints(catalog,database);}

}  // namespace crown
