#include "crown/io/normalization.hpp"

#include "crown/io/binding.hpp"
#include "json.hpp"

namespace crown::io {
namespace {
Json type_json(const frontend::SqlType& type) {
  Json result{{"kind",frontend::sql_kind_name(type.kind)},{"nullable",type.nullable}};
  if (type.decimal) result["decimal"] = {{"precision",type.decimal->precision},{"scale",type.decimal->scale}};
  return result;
}
}  // namespace

Json write_sql_normalization(const frontend::SqlNormalizeResult& result) {
  if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&result)) {
    auto output = write_sql_binding(*failure);
    output.erase("binding_valid"); output["normalization_valid"] = false;
    return output;
  }
  const auto& normalized = std::get<frontend::NormalizedSql>(result);
  Document document;
  document.schema_version = 3; document.catalog = normalized.core_catalog; document.query = normalized.core;
  document.initial.tables.resize(document.catalog.tables.size());
  if (normalized.schema_version != 1 && normalized.schema_version != 2) throw Error("unsupported_version","normalized program format must be 1 or 2");
  Json output{{"schema_version",normalized.schema_version},{"normalization_valid",true},{"admission_status","not_checked"},
      {"binding",write_sql_binding(normalized.binding)},{"core",write_document(document)},
      {"parameter_values",Json::array()},{"adapters",Json::array()},{"base_routes",Json::array()},{"outputs",Json::array()},
      {"limits",{{"work_limit",normalized.limits.work_limit ? Json(*normalized.limits.work_limit) : Json(nullptr)}}},{"work",normalized.work}};
  for (const auto& value : normalized.parameters) output["parameter_values"].push_back(value ? write_scalar(*value) : Json(nullptr));
  for (const auto& adapter : normalized.adapters) {
    Json item{{"occurrence",adapter.occurrence.value},{"base",adapter.base.value},
        {"predicates",Json::array()},{"non_null_columns",Json::array()},{"equal_columns",Json::array()},
        {"column_classes",Json::array()},{"projection",Json::array()},{"program",Json::array()}};
    if (normalized.schema_version == 1 && !adapter.constant_columns.empty()) throw Error("unsupported_version","constant guards require normalized format 2");
    if (normalized.schema_version >= 2) {
      item["constant_columns"] = Json::array();
      for (const auto& fixed : adapter.constant_columns) item["constant_columns"].push_back({{"column",fixed.column.value},{"value",write_scalar(fixed.value)}});
    }
    for (const auto predicate : adapter.predicates) item["predicates"].push_back(predicate.value);
    for (const auto column : adapter.non_null_columns) item["non_null_columns"].push_back(column.value);
    for (const auto& equality : adapter.equal_columns) item["equal_columns"].push_back({{"left",equality.left.value},{"right",equality.right.value}});
    for (const auto variable : adapter.column_classes) item["column_classes"].push_back(variable ? Json(variable->value) : Json(nullptr));
    for (const auto& projection : adapter.projection) item["projection"].push_back({{"variable",projection.variable.value},{"expression",projection.expression.value}});
    for (const auto expression : adapter.program) item["program"].push_back(expression.value);
    output["adapters"].push_back(std::move(item));
  }
  for (const auto& route : normalized.base_routes) {
    auto occurrences = Json::array();
    for (const auto occurrence : route) occurrences.push_back(occurrence.value);
    output["base_routes"].push_back(std::move(occurrences));
  }
  for (const auto& field : normalized.outputs) {
    Json item{{"name",field.name},{"type",type_json(field.type)}};
    if (const auto* column = std::get_if<frontend::CoreOutput>(&field.value)) { item["kind"] = "core"; item["column"] = column->column; }
    else { item["kind"] = "constant"; item["value"] = write_scalar(std::get<frontend::ConstantOutput>(field.value).value); }
    output["outputs"].push_back(std::move(item));
  }
  return output;
}

frontend::NormalizedSql read_sql_normalization(std::string_view text, const ProgramReadLimits& limits) {
  // Rebuild under host caps, restore stored policy, and compare every serialized field.
  const auto input = detail::parse_json(text);
  detail::fields(input,"$",{"schema_version","normalization_valid","admission_status","binding","core","parameter_values","adapters","base_routes","outputs","limits","work"});
  const auto format = detail::unsigned_integer(input.at("schema_version"),"$.schema_version");
  if (format != 1 && format != 2) throw Error("unsupported_version","normalized program format must be 1 or 2");
  if (!input.at("normalization_valid").is_boolean() || !input.at("normalization_valid").get<bool>()) detail::fail("$.normalization_valid","expected a successful normalized program");
  auto bound = read_sql_binding(input.at("binding").dump(),limits.binding);
  frontend::NormalizeOptions options;
  options.schema_version = format;
  options.parameters = read_parameter_values(Json{{"schema_version",1},{"values",input.at("parameter_values")}}.dump());
  detail::fields(input.at("limits"),"$.limits",{"work_limit"});
  const auto& encoded = input.at("limits").at("work_limit");
  const auto stored = encoded.is_null() ? std::optional<std::uint64_t>{} : detail::unsigned_integer(encoded,"$.limits.work_limit");
  options.limits.work_limit = stored;
  if (limits.normalization.work_limit && (!stored || *limits.normalization.work_limit < *stored)) options.limits.work_limit = limits.normalization.work_limit;
  auto result = frontend::normalize_sql(bound,options);
  if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&result)) {
    if (failure->diagnostic.code == "resource_limit") throw Error("resource_limit","normalization replay: " + failure->diagnostic.message);
    detail::fail("$","normalization replay rejected binding: " + failure->diagnostic.code);
  }
  auto normalized = std::get<frontend::NormalizedSql>(std::move(result)); normalized.limits.work_limit = stored;
  if (write_sql_normalization(normalized).dump() != input.dump()) detail::fail("$","normalized program differs from complete binding/normalization replay");
  return normalized;
}

frontend::NormalizedSql upgrade_sql_normalization(const frontend::NormalizedSql& program, std::uint64_t target_version, const ProgramReadLimits& limits) {
  if (target_version < program.schema_version || target_version < 1 || target_version > 2) throw Error("unsupported_version","normalized migration supports upward versions 1 through 2");
  auto original = read_sql_normalization(write_sql_normalization(program).dump(),limits);
  if (target_version == original.schema_version) return original;
  frontend::NormalizeOptions options;
  options.parameters = original.parameters; options.limits = original.limits; options.schema_version = target_version;
  if (limits.normalization.work_limit && (!options.limits.work_limit || *limits.normalization.work_limit < *options.limits.work_limit)) options.limits.work_limit = limits.normalization.work_limit;
  auto result = frontend::normalize_sql(original.binding,options);
  if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&result)) throw Error(failure->diagnostic.code,"normalized upgrade: " + failure->diagnostic.message);
  auto upgraded = std::get<frontend::NormalizedSql>(std::move(result)); upgraded.limits = original.limits;
  return upgraded;
}

std::vector<frontend::SqlValue> read_parameter_values(std::string_view text) {
  const auto input = detail::parse_json(text);
  detail::fields(input,"$",{"schema_version","values"});
  detail::version(input.at("schema_version"),"$.schema_version");
  std::vector<frontend::SqlValue> result;
  for (const auto& value : detail::array(input.at("values"),"$.values")) result.push_back(value.is_null() ? frontend::SqlValue{} : frontend::SqlValue{read_scalar(value)});
  return result;
}
}  // namespace crown::io
