#include "crown/frontend/bind.hpp"
#include "crown/api/error.hpp"
#include "crown/io/binding.hpp"
#include "crown/io/catalog.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <string_view>

namespace {
using namespace crown;
using namespace crown::frontend;
void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}
const BoundSql& bound(const SqlBindResult& result) {
  if (const auto* value = std::get_if<BoundSql>(&result)) return *value;
  const auto& error = std::get<BindingDiagnostic>(result);
  throw std::runtime_error(error.diagnostic.code + ": " + error.diagnostic.message);
}
const BindingDiagnostic& rejected(const SqlBindResult& result, std::string_view code) {
  check(std::holds_alternative<BindingDiagnostic>(result), "expected binding rejection " + std::string(code));
  const auto& error = std::get<BindingDiagnostic>(result);
  check(error.diagnostic.code == code, "wrong rejection: " + error.diagnostic.code + ", expected " + std::string(code));
  return error;
}
Catalog catalog() {
  return {1,{
    {"r",{{"a",ScalarType::int64},{"b",ScalarType::string},{"key",ScalarType::int64}}},
    {"s",{{"key",ScalarType::int64},{"c",ScalarType::date},{"a",ScalarType::int64}}},
    {"flags",{{"f",ScalarType::boolean,true},{"n",ScalarType::int64,true}}},
    {"zero",{}}
  }};
}
std::vector<std::string> names(const BoundSql& query) {
  std::vector<std::string> result;
  for (const auto& output : query.outputs) result.push_back(output.name);
  return result;
}
void join_scopes_and_outputs() {
  const auto schema = catalog();
  const auto using_result = bind_sql("SELECT DISTINCT *, l.*, q.*, l.a AS again FROM r l JOIN s q USING(key,a)",schema);
  const auto& query = bound(using_result);
  check(names(query) == std::vector<std::string>{"key","a","b","c","a","b","key","key","c","a","again"}, "USING output, qualified stars and repeated columns preserve SQL order");
  check(query.occurrences.size() == 2 && query.predicates.size() == 2 && query.semantics == SqlSemantics::set, "USING adds both equality predicates without eliminating an occurrence");
  const auto natural = bind_sql("SELECT DISTINCT * FROM r NATURAL JOIN s",schema);
  check(names(bound(natural)) == std::vector<std::string>{"a","key","b","c"}, "NATURAL derives common columns in left-input order");
  const auto renamed = bind_sql("SELECT j.* FROM (r JOIN s USING(a,key)) j(x,y)",schema);
  check(names(bound(renamed)) == std::vector<std::string>{"x","y","b","c"}, "joined relation aliases can rename an ordered prefix");
  static_cast<void>(rejected(bind_sql("SELECT l.a FROM (r l JOIN s q USING(a,key)) j",schema),"unknown_qualifier"));
  const auto using_alias = bind_sql("SELECT j.*, r.*, s.* FROM r JOIN s USING(a,key) AS j",schema);
  check(names(bound(using_alias)).size() == 8, "USING alias exposes merged keys and retains input qualifiers");
  const auto self = bind_sql("SELECT l.a, q.a FROM r l, r q",schema);
  const auto& aliases = bound(self);
  check(aliases.occurrences.size() == 2 && aliases.occurrences[0].table == aliases.occurrences[1].table,
        "self-join occurrences retain common physical routing");
  const auto left = std::get<BoundColumn>(aliases.expressions[aliases.outputs[0].expression.value].node);
  const auto right = std::get<BoundColumn>(aliases.expressions[aliases.outputs[1].expression.value].node);
  check(left.occurrence != right.occurrence, "self-join identities stay distinct");
  const auto default_scan = bind_sql("SELECT * FROM r",schema);
  const auto only_scan = bind_sql("SELECT * FROM ONLY r",schema);
  check(bound(default_scan).occurrences[0].include_descendants && !bound(only_scan).occurrences[0].include_descendants,
        "requested inheritance scan flags are preserved");
  check(io::write_sql_binding(only_scan).at("catalog_inheritance") == "none" && names(bound(default_scan)) == names(bound(only_scan)),
        "flat catalog contract gives default and ONLY scans the same declared rows");
  auto hierarchy = io::write_catalog(schema);
  hierarchy["catalog"]["tables"][0]["inherits"] = "parent";
  bool hierarchy_rejected = false;
  try { static_cast<void>(io::read_catalog(hierarchy.dump())); }
  catch (const Error& error) { hierarchy_rejected = error.code() == "invalid_document"; }
  check(hierarchy_rejected, "the catalog format cannot silently accept inheritance edges");
  static_cast<void>(rejected(bind_sql("SELECT a FROM r l, s q",schema),"ambiguous_column"));
  static_cast<void>(rejected(bind_sql("SELECT r.a FROM r l",schema),"unknown_qualifier"));
  static_cast<void>(rejected(bind_sql("SELECT * FROM r l, r l",schema),"duplicate_alias"));
  const auto duplicate_names = bind_sql("SELECT * FROM r x(a,a)",schema);
  check(names(bound(duplicate_names)) == std::vector<std::string>{"a","a","key"}, "star expansion preserves duplicate visible column names");
  static_cast<void>(rejected(bind_sql("SELECT a FROM r x(a,a)",schema),"ambiguous_column"));
  static_cast<void>(rejected(bind_sql("SELECT * FROM r JOIN s USING(a,a)",schema),"duplicate_using_column"));
  static_cast<void>(rejected(bind_sql("SELECT * FROM r l, s q JOIN r t ON l.a=t.a",schema),"unknown_qualifier"));
  const auto correlated_on = bind_sql("SELECT l.a FROM r l CROSS JOIN s q JOIN r t ON l.a=t.a",schema);
  check(bound(correlated_on).occurrences.size() == 3, "explicit join input scope differs from comma precedence");
  check(bound(bind_sql("SELECT * FROM zero",schema)).outputs.empty(), "zero-arity star expansion remains nullary");
  static_cast<void>(rejected(bind_sql("SELECT *",schema),"wildcard_without_from"));
  check(bound(bind_sql("SELECT",schema)).outputs.empty(), "PostgreSQL nullary SELECT is preserved");
}
void types_parameters_and_wrappers() {
  const auto schema = catalog();
  const auto ordinary = bind_sql("SELECT a FROM r WHERE a=1",schema);
  check(bound(ordinary).semantics == SqlSemantics::bag, "plain SELECT does not become DISTINCT");
  const auto& query = bound(ordinary);
  check(std::any_of(query.expressions.begin(),query.expressions.end(),[](const auto& expression) {
    const auto* operation = std::get_if<BoundOperation>(&expression.node);
    return operation && operation->operation == SqlOperator::widen_integer;
  }), "integer width promotion is explicit in bound expressions");
  static_cast<void>(rejected(bind_sql("SELECT a::integer FROM r",schema),"unsupported_cast"));
  static_cast<void>(bound(bind_sql("SELECT a::bigint FROM r",schema)));
  static_cast<void>(rejected(bind_sql("SELECT a FROM r WHERE a='1'",schema),"unsupported_implicit_cast"));
  const auto literal = bind_sql("SELECT DATE '2024-02-29' AS d, NULL AS n, CAST('7' AS bigint) AS v",schema);
  const auto& values = bound(literal);
  check(values.expressions[values.outputs[0].expression.value].type.kind == SqlKind::date, "typed date literal is bound and validated");
  check(values.expressions[values.outputs[1].expression.value].type.nullable, "SQL NULL stays at the nullable SQL boundary");
  static_cast<void>(rejected(bind_sql("SELECT DATE '2023-02-29'",schema),"invalid_scalar"));
  static_cast<void>(rejected(bind_sql("SELECT CAST(1.234 AS numeric(5,2))",schema),"unsupported_cast"));
  const auto boolean = bind_sql("SELECT f IS NULL AS missing FROM flags WHERE f IS NOT FALSE OR NOT (n IS NULL)",schema);
  check(!bound(boolean).expressions[bound(boolean).outputs[0].expression.value].type.nullable, "IS NULL returns a non-null Boolean");
  static_cast<void>(rejected(bind_sql("SELECT a FROM r WHERE a",schema),"type_mismatch"));
  const auto parameter_missing = bind_sql("SELECT a FROM r WHERE a=$1",schema);
  check(rejected(parameter_missing,"unbound_parameter").diagnostic.byte_offset == 24, "unbound parameter diagnostic preserves its source location");
  const auto options = io::read_bind_options(R"({"schema_version":1,"parameters":[{"type":"int64"}]})");
  const auto parameter = bind_sql("SELECT a FROM r WHERE a=$1",schema,options);
  check(bound(parameter).parameters.size() == 1, "typed parameter declaration survives binding");
  const auto wrapper = bind_sql("SELECT EXISTS(SELECT DISTINCT a FROM r WHERE a=1) AS flag",schema);
  const auto& exists = bound(wrapper);
  check(exists.wrapper == SqlWrapper::exists && exists.wrapper_alias == "flag" && exists.semantics == SqlSemantics::bag && exists.inner_semantics == SqlSemantics::set,
        "EXISTS outer singleton mode and inner DISTINCT mode remain separate");
  const auto encoded = io::write_sql_binding(wrapper);
  check(encoded.at("admission_status") == "not_checked" && encoded.at("result_wrapper") == "exists", "binding is not structural/native admission");
  for (const auto& sql : {"SELECT a+1 FROM r", "SELECT count(*) FROM r", "SELECT a FROM r ORDER BY a", "SELECT a FROM r LIMIT 1", "SELECT DISTINCT ON(a) a FROM r", "SELECT * FROM r LEFT JOIN s USING(a)", "SELECT * FROM public.r"}) {
    check(std::holds_alternative<BindingDiagnostic>(bind_sql(sql,schema)), "unsupported SQL cannot be ignored: " + std::string(sql));
  }
}
void locations_ownership_and_limits() {
  Catalog schema{1,{{"左",{{"名",ScalarType::int64}}},{"右",{{"名",ScalarType::int64}}}}};
  const std::string sql = "/*名*/\nSELECT DISTINCT 名 FROM 左 l, 右 r";
  const auto result = bind_sql(sql,schema);
  const auto& error = rejected(result,"ambiguous_column").diagnostic;
  const auto offset = sql.find("名",sql.find("SELECT"));
  check(error.byte_offset == offset && error.character_position == offset - 1 && error.line == 2 && error.column == 17,
        "Unicode diagnostic maps byte offsets to code-point coordinates");
  check(error.message.find("l.名") != std::string::npos && error.message.find("r.名") != std::string::npos,
        "ambiguous diagnostic names both visible candidates");
  auto mutable_catalog = catalog();
  std::string source = "SELECT DISTINCT a FROM r";
  auto owned = bind_sql(source,mutable_catalog);
  const auto original = io::write_sql_binding(owned).dump();
  source.clear(); mutable_catalog.tables.clear();
  check(io::write_sql_binding(owned).dump() == original, "owned IR outlives and isolates caller source/catalog mutation");
  auto copy = owned; auto moved = std::move(owned);
  check(io::write_sql_binding(copy).dump() == original && io::write_sql_binding(moved).dump() == original, "bound IR has owning copy/move lifetimes");
  BindOptions limits; limits.limits.work_limit = 0;
  static_cast<void>(rejected(bind_sql("SELECT 1",catalog(),limits),"resource_limit"));
  limits = {}; limits.limits.expression_limit = 0;
  static_cast<void>(rejected(bind_sql("SELECT 1",catalog(),limits),"resource_limit"));
  limits = {}; limits.limits.recursion_limit = 0;
  static_cast<void>(rejected(bind_sql("SELECT 1",catalog(),limits),"resource_limit"));
  const auto malformed = bind_sql("SELECT FROM;",catalog());
  check(rejected(malformed,"sql_syntax_error").phase == "syntax", "syntax failure is distinguished from binding failure");
  auto wide = catalog(); Table table{"wide",{}};
  for (std::size_t i = 0; i < 70; ++i) table.columns.push_back({"x" + std::to_string(i),ScalarType::int64});
  wide.tables.push_back(std::move(table));
  check(bound(bind_sql("SELECT DISTINCT * FROM wide",wide)).outputs.size() == 70, "no word-sized column limit");
}
}  // namespace
int main() {
  try {
    join_scopes_and_outputs();
    types_parameters_and_wrappers();
    locations_ownership_and_limits();
    std::cout << "SQL binding scopes, types, ownership, diagnostics and limits passed\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
