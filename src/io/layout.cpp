#include "crown/io/layout.hpp"

#include "json.hpp"
#include <limits>

namespace crown::io {
namespace {
std::size_t index(const Json& value,std::string_view path) {
  const auto number=detail::unsigned_integer(value,std::string(path));
  if (number>std::numeric_limits<std::size_t>::max()) detail::fail(std::string(path),"ID exceeds host size_t range");
  return static_cast<std::size_t>(number);
}
ScalarType scalar(const Json& value) {
  const auto name=detail::string(value,"field.type");
  if (name=="int64") return ScalarType::int64;
  if (name=="string") return ScalarType::string;
  if (name=="bool") return ScalarType::boolean;
  if (name=="date") return ScalarType::date;
  if (name=="decimal") return ScalarType::decimal;
  throw Error("unsupported_type","unsupported layout scalar type: "+name);
}
}  // namespace
Json write_layout(const storage::TupleLayout& layout) {
  auto fields=Json::array();
  for (const auto& field : layout.fields()) {
    Json item{{"type",type_name(field.type)},{"variable",field.variable ? Json(field.variable->value) : Json(nullptr)},
        {"decimal",field.decimal ? Json{{"precision",field.decimal->precision},{"scale",field.decimal->scale}} : Json(nullptr)}};
    fields.push_back(std::move(item));
  }
  const auto origin=layout.origin() ? Json{{"table",layout.origin()->table.value},{"source_schema_version",layout.origin()->source_schema_version}} : Json(nullptr);
  return {{"schema_version",1},{"layout_id",layout.id().value},{"semantics","nonnull_exact_binary"},
      {"context",{{"catalog_version",layout.context().catalog_version},{"binding",layout.context().binding}}},{"origin",origin},{"fields",std::move(fields)}};
}
storage::TupleLayout read_layout(std::string_view text) {
  const auto input=detail::parse_json(text);
  detail::fields(input,"$",{"schema_version","layout_id","semantics","context","origin","fields"});
  detail::version(input.at("schema_version"),"$.schema_version");
  if (detail::string(input.at("semantics"),"$.semantics")!="nonnull_exact_binary") throw Error("unsupported_semantics","only nonnull_exact_binary tuple layouts are supported");
  const auto& context=input.at("context"); detail::fields(context,"$.context",{"catalog_version","binding"});
  storage::LayoutContext bound{detail::unsigned_integer(context.at("catalog_version"),"context.catalog_version"),detail::string(context.at("binding"),"context.binding")};
  std::optional<storage::LayoutOrigin> origin;
  if (!input.at("origin").is_null()) {
    const auto& source=input.at("origin"); detail::fields(source,"$.origin",{"table","source_schema_version"});
    origin=storage::LayoutOrigin{TableId{index(source.at("table"),"origin.table")},detail::unsigned_integer(source.at("source_schema_version"),"origin.source_schema_version")};
  }
  std::vector<storage::Field> fields;
  for (const auto& item : detail::array(input.at("fields"),"$.fields")) {
    detail::fields(item,"field",{"type","decimal","variable"});
    storage::Field field{scalar(item.at("type")),{}, {}};
    if (!item.at("variable").is_null()) field.variable=VariableId{index(item.at("variable"),"field.variable")};
    if (!item.at("decimal").is_null()) {
      const auto& spec=item.at("decimal"); detail::fields(spec,"field.decimal",{"precision","scale"});
      const auto precision=detail::unsigned_integer(spec.at("precision"),"precision"),scale=detail::unsigned_integer(spec.at("scale"),"scale");
      if (precision<1 || precision>38 || scale>precision) detail::fail("field.decimal","invalid precision/scale");
      field.decimal=DecimalSpec{static_cast<std::uint32_t>(precision),static_cast<std::uint32_t>(scale)};
    }
    fields.push_back(field);
  }
  return {LayoutId{index(input.at("layout_id"),"$.layout_id")},std::move(fields),std::move(bound),origin};
}
Json write_projection(const storage::Projection& projection) {
  auto fields=Json::array(); for (const auto field : projection.fields()) fields.push_back(field.value);
  return {{"schema_version",1},{"source",write_layout(projection.source())},{"target",write_layout(projection.target())},{"fields",std::move(fields)}};
}
storage::Projection read_projection(std::string_view text,const storage::TupleLayout& source,const storage::TupleLayout& target) {
  // Reparse both descriptors, then retain the supplied actual layout handles on success.
  const auto input=detail::parse_json(text); detail::fields(input,"$",{"schema_version","source","target","fields"});
  detail::version(input.at("schema_version"),"$.schema_version");
  const auto source_descriptor=read_layout(input.at("source").dump()),target_descriptor=read_layout(input.at("target").dump());
  if (!source.same_descriptor(source_descriptor) || !target.same_descriptor(target_descriptor)) throw Error("layout_mismatch","projection descriptors differ from the supplied layout bindings");
  std::vector<FieldId> fields; for (const auto& field : detail::array(input.at("fields"),"$.fields")) fields.push_back({index(field,"projection.field")});
  return {source,target,std::move(fields)};
}
}  // namespace crown::io
