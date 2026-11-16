#include "crown/io/binding.hpp"

#include "crown/io/catalog.hpp"
#include "json.hpp"
#include <limits>
#include <type_traits>

namespace crown::io {
namespace {
Json type_json(const frontend::SqlType& type) {
  Json output{{"kind",frontend::sql_kind_name(type.kind)},{"nullable",type.nullable}};
  if (type.decimal) output["decimal"] = {{"precision",type.decimal->precision},{"scale",type.decimal->scale}};
  return output;
}
Json optional_offset(std::optional<std::size_t> offset) { return offset ? Json(*offset) : Json(nullptr); }
std::string semantics(frontend::SqlSemantics mode) { return mode == frontend::SqlSemantics::set ? "set" : "bag"; }
}  // namespace

Json write_sql_binding(const frontend::SqlBindResult& result) {
  Json output{{"schema_version",1},{"admission_status","not_checked"}};
  if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&result)) {
    const auto& diagnostic = failure->diagnostic;
    output["binding_valid"] = false;
    output["phase"] = failure->phase;
    output["diagnostic"] = {{"code",diagnostic.code},{"message",diagnostic.message},
        {"byte_offset",optional_offset(diagnostic.byte_offset)},{"character_position",optional_offset(diagnostic.character_position)},
        {"line",optional_offset(diagnostic.line)},{"column",optional_offset(diagnostic.column)}};
    return output;
  }
  const auto& bound = std::get<frontend::BoundSql>(result);
  output["binding_valid"] = true;
  output["source"] = bound.source;
  output["catalog_binding"] = write_catalog(bound.catalog);
  output["catalog_inheritance"] = "none";
  output["requested_semantics"] = semantics(bound.semantics);
  output["inner_semantics"] = bound.inner_semantics ? Json(semantics(*bound.inner_semantics)) : Json(nullptr);
  output["result_wrapper"] = bound.wrapper == frontend::SqlWrapper::rows ? "rows" : "exists";
  output["wrapper_alias"] = bound.wrapper_alias;
  output["parameters"] = Json::array();
  for (const auto& parameter : bound.parameters) output["parameters"].push_back(type_json(parameter));
  output["occurrences"] = Json::array();
  for (const auto& occurrence : bound.occurrences) {
    output["occurrences"].push_back({{"table",bound.catalog.tables.at(occurrence.table.value).name},
        {"table_id",occurrence.table.value},{"alias",occurrence.alias},{"column_names",occurrence.column_names},
        {"location",optional_offset(occurrence.location)},{"include_descendants",occurrence.include_descendants}});
  }
  output["expressions"] = Json::array();
  for (std::size_t i = 0; i < bound.expressions.size(); ++i) {
    const auto& expression = bound.expressions[i];
    Json item{{"id",i},{"type",type_json(expression.type)},{"location",optional_offset(expression.location)}};
    std::visit([&](const auto& node) {
      using T = std::decay_t<decltype(node)>;
      if constexpr (std::is_same_v<T,frontend::BoundColumn>) {
        item["kind"] = "column"; item["occurrence"] = node.occurrence.value; item["column"] = node.column.value;
      } else if constexpr (std::is_same_v<T,frontend::BoundLiteral>) {
        item["kind"] = "literal"; item["value"] = node.value ? write_scalar(*node.value) : Json(nullptr);
      } else if constexpr (std::is_same_v<T,frontend::BoundParameter>) {
        item["kind"] = "parameter"; item["number"] = node.number;
      } else {
        item["kind"] = "operation"; item["operator"] = frontend::sql_operator_name(node.operation);
        item["arguments"] = Json::array();
        for (const auto id : node.arguments) item["arguments"].push_back(id.value);
      }
    },expression.node);
    output["expressions"].push_back(std::move(item));
  }
  output["predicates"] = Json::array();
  for (const auto id : bound.predicates) output["predicates"].push_back(id.value);
  output["outputs"] = Json::array();
  for (const auto& column : bound.outputs) output["outputs"].push_back({{"name",column.name},{"expression",column.expression.value}});
  output["limits"] = {{"work_limit",bound.limits.work_limit ? Json(*bound.limits.work_limit) : Json(nullptr)},
      {"expression_limit",bound.limits.expression_limit},{"recursion_limit",bound.limits.recursion_limit}};
  output["work"] = bound.work;
  return output;
}

// Every encoded binding field is an assertion checked by complete source/catalog
// replay. Parsed flags and expression IDs are not admission authority.
frontend::BoundSql read_sql_binding(std::string_view text, frontend::BindLimits replay_limits) {
  const auto input = detail::parse_json(text);
  detail::fields(input,"$",{"schema_version","admission_status","binding_valid","source","catalog_binding","catalog_inheritance",
      "requested_semantics","inner_semantics","result_wrapper","wrapper_alias","parameters","occurrences","expressions","predicates","outputs","limits","work"});
  detail::version(input.at("schema_version"),"$.schema_version");
  if (!input.at("binding_valid").is_boolean() || !input.at("binding_valid").get<bool>()) detail::fail("$.binding_valid","expected a successful binding artifact");
  const auto source = detail::string(input.at("source"),"$.source");
  const auto catalog = read_catalog(input.at("catalog_binding").dump());
  auto signature = Json::array();
  for (const auto& type : detail::array(input.at("parameters"),"$.parameters")) {
    detail::fields(type,"parameter",{"kind","nullable"},{"decimal"});
    const auto name = detail::string(type.at("kind"),"parameter.kind");
    if (name == "unknown" || name == "int32") detail::fail("parameter.kind","parameter signatures use catalog scalar types");
    Json column{{"type",name},{"nullable",type.at("nullable")}};
    if (type.contains("decimal")) column["decimal"] = type.at("decimal");
    signature.push_back(std::move(column));
  }
  auto options = read_bind_options(Json{{"schema_version",1},{"parameters",std::move(signature)}}.dump());
  const auto& encoded = input.at("limits");
  detail::fields(encoded,"$.limits",{"work_limit","expression_limit","recursion_limit"});
  frontend::BindLimits stored;
  stored.work_limit = encoded.at("work_limit").is_null() ? std::optional<std::uint64_t>{} : detail::unsigned_integer(encoded.at("work_limit"),"$.limits.work_limit");
  const auto size = [&](const char* key) {
    const auto number = detail::unsigned_integer(encoded.at(key),std::string("$.limits.") + key);
    if (number > std::numeric_limits<std::size_t>::max()) detail::fail("$.limits","limit exceeds host size_t range");
    return static_cast<std::size_t>(number);
  };
  stored.expression_limit = size("expression_limit"); stored.recursion_limit = size("recursion_limit");
  options.limits = stored;
  if (replay_limits.work_limit && (!options.limits.work_limit || *replay_limits.work_limit < *options.limits.work_limit)) options.limits.work_limit = replay_limits.work_limit;
  options.limits.expression_limit = std::min(options.limits.expression_limit,replay_limits.expression_limit);
  options.limits.recursion_limit = std::min(options.limits.recursion_limit,replay_limits.recursion_limit);
  auto result = frontend::bind_sql(source,catalog,options);
  if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&result)) {
    if (failure->diagnostic.code == "resource_limit") throw Error("resource_limit","binding replay: " + failure->diagnostic.message);
    detail::fail("$","binding replay rejected source: " + failure->diagnostic.code);
  }
  auto bound = std::get<frontend::BoundSql>(std::move(result)); bound.limits = stored;
  if (write_sql_binding(bound).dump() != input.dump()) detail::fail("$","binding artifact differs from its complete source/catalog replay");
  return bound;
}

frontend::BindOptions read_bind_options(std::string_view text) {
  const auto input = detail::parse_json(text);
  detail::fields(input,"$",{"schema_version","parameters"});
  detail::version(input.at("schema_version"),"$.schema_version");
  auto columns = Json::array();
  std::size_t index = 0;
  for (const auto& parameter : detail::array(input.at("parameters"),"parameters")) {
    detail::fields(parameter,"parameter",{"type"},{"nullable","collation","decimal"});
    auto column = parameter;
    column["name"] = "$" + std::to_string(++index);
    columns.push_back(std::move(column));
  }
  const auto catalog = read_catalog_payload({{"version",1},{"tables",Json::array({{{"name","parameters"},{"columns",std::move(columns)}}})}});
  frontend::BindOptions options;
  options.parameters = catalog.tables[0].columns;
  return options;
}
}  // namespace crown::io
