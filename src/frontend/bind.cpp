#include "crown/frontend/bind.hpp"

#include "crown/api/error.hpp"
#include "crown/catalog/catalog.hpp"
#include <algorithm>
#include <charconv>
#include <limits>
#include <map>
#include <set>
#include <utility>

namespace crown::frontend {
namespace {
using Json = nlohmann::json;
struct Failure { std::string code; std::string message; std::optional<std::size_t> location; };
[[noreturn]] void fail(std::string code, std::string message, std::optional<std::size_t> location = {}) {
  throw Failure{std::move(code), std::move(message), location};
}
SqlDiagnostic diagnostic(const Failure& failure, std::string_view source) {
  SqlDiagnostic result{failure.code, failure.message, failure.location, {}, {}, {}};
  if (!failure.location || *failure.location > source.size()) { result.byte_offset.reset(); return result; }
  result.character_position = 1; result.line = 1; result.column = 1;
  for (std::size_t i = 0; i < *failure.location; ++i) {
    const auto byte = static_cast<unsigned char>(source[i]);
    if ((byte & 0xc0U) == 0x80U) continue;
    ++*result.character_position;
    if (source[i] == '\n') { ++*result.line; result.column = 1; }
    else ++*result.column;
  }
  return result;
}
SqlType sql_type(const Column& column) {
  SqlKind kind = SqlKind::unknown;
  switch (column.type) {
    case ScalarType::int64: kind = SqlKind::int64; break;
    case ScalarType::string: kind = SqlKind::string; break;
    case ScalarType::boolean: kind = SqlKind::boolean; break;
    case ScalarType::date: kind = SqlKind::date; break;
    case ScalarType::decimal: kind = SqlKind::decimal; break;
  }
  return {kind, column.nullable, column.decimal};
}
bool integer_kind(SqlKind kind) { return kind == SqlKind::int32 || kind == SqlKind::int64; }
bool fits_int32(std::int64_t value) {
  return value >= std::numeric_limits<std::int32_t>::min() && value <= std::numeric_limits<std::int32_t>::max();
}
std::optional<std::int64_t> integer_text(std::string_view text) {
  std::int64_t result = 0;
  const auto [end, error] = std::from_chars(text.data(), text.data() + text.size(), result);
  if (error != std::errc{} || end != text.data() + text.size()) return {};
  return result;
}
struct VisibleColumn { std::string name; ExpressionId expression; };
struct Scope {
  std::vector<VisibleColumn> columns;
  std::map<std::string, std::vector<VisibleColumn>> qualifiers;
};

class Binder {
 public:
  Binder(const SqlSyntax& syntax, const Catalog& catalog, const BindOptions& options)
      : syntax_(syntax) {
    result_.source = syntax.source;
    result_.catalog = catalog;
    result_.limits = options.limits;
    for (const auto& parameter : options.parameters) result_.parameters.push_back(sql_type(parameter));
  }
  BoundSql run();
 private:
  class Frame {
   public:
    explicit Frame(Binder& binder) : binder_(binder) {
      if (binder_.depth_ >= binder_.result_.limits.recursion_limit) fail("resource_limit", "SQL binding recursion limit exceeded");
      ++binder_.depth_;
    }
    ~Frame() { --binder_.depth_; }
    Frame(const Frame&) = delete;
    Frame& operator=(const Frame&) = delete;
   private:
    Binder& binder_;
  };
  // Count selected binding checkpoints. Catalog validation, string work and
  // container allocation/copy costs are not all represented by this counter.
  void charge() {
    if (result_.work == std::numeric_limits<std::uint64_t>::max() ||
        (result_.limits.work_limit && result_.work >= *result_.limits.work_limit)) fail("resource_limit", "SQL binding work limit exceeded");
    ++result_.work;
  }
  std::optional<std::size_t> location(const Json& node) const {
    if (!node.is_object() || !node.contains("location")) return {};
    const auto value = node.at("location").get<std::int64_t>();
    if (value < 0) return {};
    const auto offset = static_cast<std::uint64_t>(value);
    if (offset > syntax_.source.size()) fail("invalid_ast", "AST location is outside its source");
    return static_cast<std::size_t>(offset);
  }
  void keys(const Json& node, std::initializer_list<std::string_view> allowed) {
    charge();
    if (!node.is_object()) fail("invalid_ast", "expected an AST object");
    for (const auto& [key, unused] : node.items()) {
      static_cast<void>(unused);
      if (std::find(allowed.begin(), allowed.end(), key) == allowed.end()) fail("unsupported_sql", "unsupported SQL field: " + key, location(node));
    }
  }
  const Json& tagged(const Json& node, std::string_view name) const {
    if (!node.is_object() || node.size() != 1 || !node.contains(name) || !node.at(name).is_object()) fail("invalid_ast", "expected " + std::string(name) + " node");
    return node.at(name);
  }
  std::string identifier(const Json& node) const { return tagged(node, "String").value("sval", std::string{}); }
  ExpressionId append(SqlType type, BoundNode node, std::optional<std::size_t> where) {
    charge();
    if (result_.expressions.size() >= result_.limits.expression_limit) fail("resource_limit", "SQL binding expression limit exceeded", where);
    const ExpressionId id{result_.expressions.size()};
    result_.expressions.push_back({type, std::move(node), where});
    return id;
  }
  const BoundExpression& expression(ExpressionId id) const { return result_.expressions[id.value]; }
  ExpressionId operation(SqlOperator op, std::vector<ExpressionId> arguments, SqlType type, std::optional<std::size_t> where) {
    return append(type, BoundOperation{op, std::move(arguments)}, where);
  }
  void resolve_unknown(ExpressionId id, SqlType target) {
    auto& item = result_.expressions[id.value];
    if (item.type.kind != SqlKind::unknown) return;
    const auto* literal = std::get_if<BoundLiteral>(&item.node);
    if (!literal) fail("invalid_ast", "unknown nonliteral type", item.location);
    if (literal->value && target.kind != SqlKind::string) fail("unsupported_implicit_cast", "string literal needs an explicit typed cast", item.location);
    target.nullable = !literal->value.has_value();
    item.type = target;
  }
  ExpressionId boolean(ExpressionId id) {
    resolve_unknown(id, {SqlKind::boolean, true, {}});
    if (expression(id).type.kind != SqlKind::boolean) fail("type_mismatch", "expected a Boolean expression", expression(id).location);
    return id;
  }
  // Comparisons require compatible kinds; same-kind decimals may retain
  // different declared precision/scale. Only integer width widening adds a node.
  void comparable(ExpressionId& left, ExpressionId& right, std::optional<std::size_t> where) {
    if (expression(left).type.kind == SqlKind::unknown && expression(right).type.kind == SqlKind::unknown) {
      resolve_unknown(left, {SqlKind::string, true, {}}); resolve_unknown(right, {SqlKind::string, true, {}});
    } else {
      resolve_unknown(left, expression(right).type); resolve_unknown(right, expression(left).type);
    }
    const auto left_type = expression(left).type;
    const auto right_type = expression(right).type;
    if (integer_kind(left_type.kind) && integer_kind(right_type.kind)) {
      if (left_type.kind == SqlKind::int32 && right_type.kind == SqlKind::int64) left = operation(SqlOperator::widen_integer, {left}, {SqlKind::int64, left_type.nullable, {}}, where);
      if (right_type.kind == SqlKind::int32 && left_type.kind == SqlKind::int64) right = operation(SqlOperator::widen_integer, {right}, {SqlKind::int64, right_type.nullable, {}}, where);
    } else if (left_type.kind != right_type.kind) {
      fail("unsupported_implicit_cast", "comparison requires an unsupported conversion between " + sql_kind_name(left_type.kind) + " and " + sql_kind_name(right_type.kind), where);
    }
  }
  ExpressionId comparison(SqlOperator op, ExpressionId left, ExpressionId right, std::optional<std::size_t> where) {
    comparable(left, right, where);
    const bool nullable = expression(left).type.nullable || expression(right).type.nullable;
    return operation(op, {left,right}, {SqlKind::boolean, nullable, {}}, where);
  }
  ExpressionId literal(const Json& node) {
    keys(node, {"ival","fval","sval","boolval","isnull","location"});
    const auto where = location(node);
    if (node.value("isnull", false)) return append({SqlKind::unknown,true,{}}, BoundLiteral{{}}, where);
    if (node.contains("ival")) {
      const auto value = node.at("ival").value("ival", std::int64_t{0});
      return append({fits_int32(value) ? SqlKind::int32 : SqlKind::int64,false,{}}, BoundLiteral{Value{value}}, where);
    }
    if (node.contains("fval")) {
      const auto text = node.at("fval").at("fval").get<std::string>();
      if (const auto value = integer_text(text)) return append({fits_int32(*value) ? SqlKind::int32 : SqlKind::int64,false,{}}, BoundLiteral{Value{*value}}, where);
      if (text.find_first_of(".eE") == std::string::npos) fail("unsupported_type", "integer literal exceeds the signed int64 domain", where);
      try { return append({SqlKind::decimal,false,{}}, BoundLiteral{Value{Decimal::parse(text)}}, where); }
      catch (const Error& error) { fail(error.code(), error.what(), where); }
    }
    if (node.contains("sval")) return append({SqlKind::unknown,false,{}}, BoundLiteral{Value{node.at("sval").value("sval", std::string{})}}, where);
    if (node.contains("boolval")) return append({SqlKind::boolean,false,{}}, BoundLiteral{Value{node.at("boolval").value("boolval", false)}}, where);
    fail("unsupported_literal", "unsupported SQL literal", where);
  }
  SqlType cast_type(const Json& node) {
    keys(node, {"names","typemod","typmods","location"});
    const auto where = location(node);
    const auto& names = node.at("names");
    if (names.empty() || names.size() > 2 || (names.size() == 2 && identifier(names[0]) != "pg_catalog")) fail("unsupported_type", "unsupported qualified cast type", where);
    const auto name = identifier(names.back());
    SqlType target;
    if (name == "int8" || name == "bigint") target.kind = SqlKind::int64;
    else if (name == "int4" || name == "integer") target.kind = SqlKind::int32;
    else if (name == "text") target.kind = SqlKind::string;
    else if (name == "bool" || name == "boolean") target.kind = SqlKind::boolean;
    else if (name == "date") target.kind = SqlKind::date;
    else if (name == "numeric" || name == "decimal") target.kind = SqlKind::decimal;
    else fail("unsupported_type", "unsupported cast type " + name, where);
    if (node.contains("typmods")) {
      const auto& modifiers = node.at("typmods");
      if (target.kind != SqlKind::decimal || modifiers.empty() || modifiers.size() > 2) fail("unsupported_cast", "unsupported type modifiers", where);
      const auto& precision_node = tagged(modifiers[0], "A_Const");
      if (!precision_node.contains("ival")) fail("unsupported_cast", "decimal precision must be an integer literal", where);
      const auto precision = precision_node.at("ival").value("ival", std::int64_t{0});
      std::int64_t scale = 0;
      if (modifiers.size() == 2) {
        const auto& scale_node = tagged(modifiers[1], "A_Const");
        if (!scale_node.contains("ival")) fail("unsupported_cast", "decimal scale must be an integer literal", where);
        scale = scale_node.at("ival").value("ival", std::int64_t{0});
      }
      if (precision < 1 || precision > 38 || scale < 0 || scale > precision) fail("unsupported_type", "decimal requires 1 <= precision <= 38 and 0 <= scale <= precision", where);
      target.decimal = DecimalSpec{static_cast<std::uint32_t>(precision), static_cast<std::uint32_t>(scale)};
    }
    return target;
  }
  ExpressionId cast(const Json& node, const Scope& scope) {
    keys(node, {"arg","typeName","location"});
    auto target = cast_type(node.at("typeName"));
    const auto where = location(node).has_value() ? location(node) : location(node.at("typeName"));
    const auto argument = bind_expression(node.at("arg"), scope);
    auto& item = result_.expressions[argument.value];
    target.nullable = item.type.nullable;
    // Validate and retag a literal leaf before retaining its explicit cast node.
    // An already-bound cast operation follows the nonliteral identity rule.
    if (auto* value = std::get_if<BoundLiteral>(&item.node)) {
      if (value->value) {
        const auto original = *value->value;
        const auto* text = std::get_if<std::string>(&original);
        try {
          if (target.kind == SqlKind::string && text) value->value = *text;
          else if (target.kind == SqlKind::date && text) value->value = Date::parse(*text);
          else if (target.kind == SqlKind::decimal && text) value->value = Decimal::parse(*text);
          else if (integer_kind(target.kind)) {
            std::optional<std::int64_t> number;
            if (text) number = integer_text(*text);
            else if (const auto* integer = std::get_if<std::int64_t>(&original)) number = *integer;
            if (!number || (target.kind == SqlKind::int32 && !fits_int32(*number))) fail("unsupported_cast", "integer literal cast is not exactly representable", where);
            value->value = *number;
          } else if (target.kind == SqlKind::boolean && std::holds_alternative<bool>(original)) value->value = original;
          else if (target.kind == SqlKind::decimal && std::holds_alternative<Decimal>(original)) value->value = original;
          else if (target.kind == SqlKind::date && std::holds_alternative<Date>(original)) value->value = original;
          else fail("unsupported_cast", "unsupported literal conversion", where);
          if (target.decimal && !catalog::decimal_fits(std::get<Decimal>(*value->value), *target.decimal)) fail("unsupported_cast", "rounding or overflowing decimal casts are not implemented", where);
        } catch (const Error& error) { fail(error.code(), error.what(), where); }
      }
      item.type = target;
      return operation(SqlOperator::literal_cast, {argument}, target, where);
    }
    if (item.type != target) fail("unsupported_cast", "only identity casts of nonliteral expressions are implemented (including width, scale and nullability)", where);
    return operation(SqlOperator::identity_cast, {argument}, target, where);
  }
  ExpressionId lookup(const Scope& scope, std::optional<std::string> qualifier, const std::string& name, std::optional<std::size_t> where) {
    const auto* columns = &scope.columns;
    if (qualifier) {
      const auto found = scope.qualifiers.find(*qualifier);
      if (found == scope.qualifiers.end()) fail("unknown_qualifier", "unknown relation qualifier " + *qualifier, where);
      columns = &found->second;
    }
    std::optional<ExpressionId> result;
    std::string first_candidate;
    const auto describe = [&](const VisibleColumn& column) {
      if (qualifier) return *qualifier + "." + name;
      for (const auto& [alias, visible] : scope.qualifiers) {
        for (const auto& candidate : visible) {
          charge();
          if (candidate.name == name && candidate.expression == column.expression) return alias + "." + name;
        }
      }
      return std::string("merged JOIN column ") + name;
    };
    for (const auto& column : *columns) {
      charge();
      if (column.name != name) continue;
      if (result) fail("ambiguous_column", "ambiguous column " + name + ": " + first_candidate + " and " + describe(column), where);
      result = column.expression;
      first_candidate = describe(column);
    }
    if (!result) fail("unknown_column", "unknown column " + (qualifier ? *qualifier + "." : "") + name, where);
    return *result;
  }
  ExpressionId bind_expression(const Json& node, const Scope& scope) {
    Frame frame(*this); charge();
    if (!node.is_object() || node.size() != 1) fail("invalid_ast", "expected one expression node");
    const auto entry = node.begin();
    const auto& tag = entry.key(); const auto& value = entry.value();
    const auto where = location(value);
    if (tag == "ColumnRef") {
      keys(value, {"fields","location"});
      const auto& fields = value.at("fields");
      if (fields.empty() || fields.size() > 2) fail("unsupported_qualification", "only column and alias.column references are implemented", where);
      for (const auto& field : fields) if (!field.contains("String")) fail("unsupported_expression", "wildcards are allowed only as select-list items", where);
      const auto selected = lookup(scope, fields.size() == 2 ? std::optional<std::string>{identifier(fields[0])} : std::nullopt, identifier(fields.back()), where);
      const auto definition = expression(selected);
      return append(definition.type,definition.node,where);
    }
    if (tag == "A_Const") return literal(value);
    if (tag == "ParamRef") {
      keys(value, {"number","location"});
      const auto number = value.at("number").get<std::int64_t>();
      if (number < 1 || static_cast<std::uint64_t>(number) > result_.parameters.size()) fail("unbound_parameter", "parameter $" + std::to_string(number) + " has no declared type", where);
      return append(result_.parameters[static_cast<std::size_t>(number - 1)], BoundParameter{static_cast<std::size_t>(number)}, where);
    }
    if (tag == "TypeCast") return cast(value, scope);
    if (tag == "A_Expr") {
      keys(value, {"kind","name","lexpr","rexpr","location"});
      if (value.value("kind", std::string{}) != "AEXPR_OP" || !value.contains("lexpr") || !value.contains("rexpr")) fail("unsupported_expression", "only binary scalar comparisons are implemented", where);
      const auto& names = value.at("name");
      if (names.empty() || names.size() > 2 || (names.size() == 2 && identifier(names[0]) != "pg_catalog")) fail("unsupported_operator", "unsupported qualified operator", where);
      const auto name = identifier(names.back());
      SqlOperator op;
      if (name == "=") op = SqlOperator::equal;
      else if (name == "<>" || name == "!=") op = SqlOperator::not_equal;
      else if (name == "<") op = SqlOperator::less;
      else if (name == "<=") op = SqlOperator::less_equal;
      else if (name == ">") op = SqlOperator::greater;
      else if (name == ">=") op = SqlOperator::greater_equal;
      else fail("unsupported_operator", "unsupported scalar operator " + name, where);
      const auto left = bind_expression(value.at("lexpr"), scope);
      const auto right = bind_expression(value.at("rexpr"), scope);
      return comparison(op, left, right, where);
    }
    if (tag == "BoolExpr") {
      keys(value, {"boolop","args","location"});
      const auto name = value.at("boolop").get<std::string>();
      const auto op = name == "AND_EXPR" ? SqlOperator::conjunction : name == "OR_EXPR" ? SqlOperator::disjunction : name == "NOT_EXPR" ? SqlOperator::negation : throw Failure{"unsupported_expression","unknown Boolean operator",where};
      std::vector<ExpressionId> arguments; bool nullable = false;
      for (const auto& item : value.at("args")) { const auto id = boolean(bind_expression(item, scope)); nullable = nullable || expression(id).type.nullable; arguments.push_back(id); }
      if (arguments.empty() || (op == SqlOperator::negation && arguments.size() != 1)) fail("invalid_ast", "invalid Boolean operator arity", where);
      return operation(op, std::move(arguments), {SqlKind::boolean, nullable, {}}, where);
    }
    if (tag == "NullTest" || tag == "BooleanTest") {
      keys(value, {"arg","nulltesttype","argisrow","booltesttype","location"});
      if (value.value("argisrow", false)) fail("unsupported_expression", "row NULL tests are not implemented", where);
      auto argument = bind_expression(value.at("arg"), scope);
      SqlOperator op;
      if (tag == "NullTest") {
        resolve_unknown(argument, {SqlKind::string,true,{}});
        const auto name = value.at("nulltesttype").get<std::string>();
        if (name == "IS_NULL") op = SqlOperator::is_null;
        else if (name == "IS_NOT_NULL") op = SqlOperator::is_not_null;
        else fail("unsupported_expression", "unknown NULL test", where);
      } else {
        argument = boolean(argument);
        const auto name = value.at("booltesttype").get<std::string>();
        if (name == "IS_TRUE") op = SqlOperator::is_true;
        else if (name == "IS_NOT_TRUE") op = SqlOperator::is_not_true;
        else if (name == "IS_FALSE") op = SqlOperator::is_false;
        else if (name == "IS_NOT_FALSE") op = SqlOperator::is_not_false;
        else if (name == "IS_UNKNOWN") op = SqlOperator::is_unknown;
        else if (name == "IS_NOT_UNKNOWN") op = SqlOperator::is_not_unknown;
        else fail("unsupported_expression", "unknown Boolean test", where);
      }
      return operation(op, {argument}, {SqlKind::boolean,false,{}}, where);
    }
    fail("unsupported_expression", "unsupported SQL expression " + tag, where);
  }
  Scope merge(Scope left, Scope right, std::optional<std::size_t> where);
  Scope from(const Json& node);
  Scope alias_scope(Scope scope, const Json& alias, std::optional<std::size_t> where);
  void select(const Json& node);
  std::string output_name(const Json& node) const;
  const SqlSyntax& syntax_;
  BoundSql result_;
  std::size_t depth_ = 0;
};

Scope Binder::merge(Scope left, Scope right, std::optional<std::size_t> where) {
  for (auto& [name, columns] : right.qualifiers) {
    charge();
    if (!left.qualifiers.emplace(name, std::move(columns)).second) fail("duplicate_alias", "duplicate visible relation alias " + name, where);
  }
  left.columns.insert(left.columns.end(), right.columns.begin(), right.columns.end());
  return left;
}

Scope Binder::alias_scope(Scope scope, const Json& alias, std::optional<std::size_t> where) {
  keys(alias, {"aliasname","colnames"});
  const auto name = alias.at("aliasname").get<std::string>();
  if (name.empty()) fail("invalid_ast", "empty relation alias", where);
  if (alias.contains("colnames")) {
    const auto& names = alias.at("colnames");
    if (names.size() > scope.columns.size()) fail("alias_column_count", "relation alias has more column names than its input", where);
    for (std::size_t i = 0; i < names.size(); ++i) { charge(); scope.columns[i].name = identifier(names[i]); }
  }
  scope.qualifiers.clear();
  scope.qualifiers.emplace(name, scope.columns);
  return scope;
}

Scope Binder::from(const Json& node) {
  Frame frame(*this); charge();
  if (!node.is_object() || node.size() != 1) fail("invalid_ast", "expected one FROM item");
  if (node.contains("RangeVar")) {
    const auto& range = node.at("RangeVar");
    keys(range, {"relname","inh","relpersistence","alias","location","schemaname","catalogname"});
    const auto where = location(range);
    if (range.contains("schemaname") || range.contains("catalogname")) fail("unsupported_namespace", "catalog currently has global relation names; qualified SQL namespaces are not implemented", where);
    const auto name = range.at("relname").get<std::string>();
    TableId table{0};
    try { table = catalog::find_table(result_.catalog, name); }
    catch (const Error& error) { fail(error.code(), error.what(), where); }
    const auto& physical = result_.catalog.tables[table.value];
    const auto alias = range.contains("alias") ? range.at("alias").at("aliasname").get<std::string>() : name;
    const OccurrenceId occurrence{result_.occurrences.size()};
    result_.occurrences.push_back({table,alias,{},where,range.value("inh",false)});
    Scope scope;
    for (std::size_t i = 0; i < physical.columns.size(); ++i) {
      const auto& column = physical.columns[i];
      scope.columns.push_back({column.name,append(sql_type(column),BoundColumn{occurrence,ColumnId{i}},where)});
    }
    if (range.contains("alias")) scope = alias_scope(std::move(scope), range.at("alias"), where);
    else scope.qualifiers.emplace(name, scope.columns);
    for (const auto& column : scope.columns) result_.occurrences[occurrence.value].column_names.push_back(column.name);
    return scope;
  }
  if (!node.contains("JoinExpr")) fail("unsupported_from", "only physical relations and inner/cross joins are implemented");
  const auto& join = node.at("JoinExpr");
  keys(join, {"jointype","isNatural","larg","rarg","usingClause","join_using_alias","quals","alias","rtindex"});
  const auto where = syntax_.statement.begin;
  if (join.value("jointype", std::string{}) != "JOIN_INNER") fail("unsupported_join", "outer/semi/anti joins are not implemented", where);
  auto left = from(join.at("larg"));
  auto right = from(join.at("rarg"));
  auto combined = merge(left, right, where);
  std::vector<std::string> using_names;
  if (join.value("isNatural", false)) {
    if (join.contains("usingClause") || join.contains("quals")) fail("invalid_ast", "NATURAL JOIN also contains an explicit condition", where);
    std::set<std::string> added;
    for (const auto& l : left.columns) {
      for (const auto& r : right.columns) {
        charge();
        if (l.name == r.name && added.insert(l.name).second) using_names.push_back(l.name);
      }
    }
  } else if (join.contains("usingClause")) {
    std::set<std::string> added;
    for (const auto& item : join.at("usingClause")) {
      const auto name = identifier(item);
      if (!added.insert(name).second) fail("duplicate_using_column", "duplicate USING column " + name, where);
      using_names.push_back(name);
    }
  }
  std::vector<VisibleColumn> merged_columns;
  for (const auto& name : using_names) {
    auto l = lookup(left, {}, name, where);
    auto r = lookup(right, {}, name, where);
    comparable(l,r,where);
    result_.predicates.push_back(comparison(SqlOperator::equal,l,r,where));
    auto type = expression(l).type;
    type.nullable = false;  // An INNER equality can be TRUE only for two non-NULL values.
    if (type.decimal != expression(r).type.decimal) type.decimal.reset();
    merged_columns.push_back({name,operation(SqlOperator::using_value,{l,r},type,where)});
  }
  const auto using_columns = merged_columns;
  for (const auto& column : left.columns) if (std::find(using_names.begin(),using_names.end(),column.name) == using_names.end()) merged_columns.push_back(column);
  for (const auto& column : right.columns) if (std::find(using_names.begin(),using_names.end(),column.name) == using_names.end()) merged_columns.push_back(column);
  combined.columns = std::move(merged_columns);
  if (join.contains("quals")) {
    if (!using_names.empty()) fail("invalid_ast", "JOIN has both USING and ON", where);
    result_.predicates.push_back(boolean(bind_expression(join.at("quals"),combined)));
  }
  if (join.contains("join_using_alias")) {
    const auto& alias = join.at("join_using_alias");
    keys(alias,{"aliasname"});
    const auto name = alias.at("aliasname").get<std::string>();
    if (!combined.qualifiers.emplace(name,using_columns).second) fail("duplicate_alias", "duplicate visible relation alias " + name,where);
  }
  if (join.contains("alias")) combined = alias_scope(std::move(combined),join.at("alias"),where);
  return combined;
}

std::string Binder::output_name(const Json& node) const {
  if (node.contains("ColumnRef")) {
    const auto& names = node.at("ColumnRef").at("fields");
    if (!names.empty() && names.back().contains("String")) return identifier(names.back());
  }
  if (node.contains("TypeCast")) {
    const auto* underlying = &node.at("TypeCast").at("arg");
    while (underlying->contains("TypeCast")) underlying = &underlying->at("TypeCast").at("arg");
    if (underlying->contains("ColumnRef")) return output_name(*underlying);
    return identifier(node.at("TypeCast").at("typeName").at("names").back());
  }
  return "?column?";
}

void Binder::select(const Json& node) {
  Frame frame(*this);
  keys(node,{"targetList","fromClause","whereClause","distinctClause","limitOption","op"});
  if (node.value("op",std::string{"SETOP_NONE"}) != "SETOP_NONE") fail("unsupported_set_operation", "SQL set operations are not implemented");
  if (node.value("limitOption",std::string{"LIMIT_OPTION_DEFAULT"}) != "LIMIT_OPTION_DEFAULT") fail("unsupported_sql", "SQL LIMIT options are not implemented");
  if (node.contains("distinctClause")) {
    const auto& distinct = node.at("distinctClause");
    if (distinct.size() != 1 || !distinct[0].is_object() || !distinct[0].empty()) fail("unsupported_distinct_on", "DISTINCT ON is not ordinary set projection");
    result_.semantics = SqlSemantics::set;
  } else result_.semantics = SqlSemantics::bag;
  Scope scope;
  if (node.contains("fromClause")) for (const auto& item : node.at("fromClause")) scope = merge(std::move(scope),from(item),syntax_.statement.begin);
  if (node.contains("whereClause")) result_.predicates.push_back(boolean(bind_expression(node.at("whereClause"),scope)));
  if (!node.contains("targetList")) return;  // PostgreSQL permits nullary SELECT.
  for (const auto& item : node.at("targetList")) {
    const auto& target = tagged(item,"ResTarget");
    keys(target,{"name","val","location"});
    const auto& value = target.at("val");
    if (value.contains("ColumnRef")) {
      const auto& reference = value.at("ColumnRef");
      keys(reference,{"fields","location"});
      const auto& names = reference.at("fields");
      if (!names.empty() && names.back().contains("A_Star")) {
        const auto where = location(reference);
        const auto* columns = &scope.columns;
        if (names.size() == 2) {
          const auto qualifier = identifier(names[0]);
          const auto found = scope.qualifiers.find(qualifier);
          if (found == scope.qualifiers.end()) fail("unknown_qualifier", "unknown wildcard qualifier " + qualifier,where);
          columns = &found->second;
        } else if (names.size() != 1) fail("unsupported_qualification", "only * and alias.* wildcards are implemented",where);
        if (scope.qualifiers.empty()) fail("wildcard_without_from", "SELECT * requires an input relation",where);
        // PostgreSQL expands wildcard targets before applying a scalar alias;
        // its per-column names remain the names in the visible relation.
        for (const auto& column : *columns) { charge(); result_.outputs.push_back({column.name,column.expression}); }
        continue;
      }
    }
    const auto id = bind_expression(value,scope);
    resolve_unknown(id,{SqlKind::string,true,{}});
    result_.outputs.push_back({target.value("name",output_name(value)),id});
  }
}

BoundSql Binder::run() {
  const auto& statement = syntax_.ast.at("stmts")[0].at("stmt");
  if (!statement.contains("SelectStmt")) fail("unsupported_statement", "only SELECT statements can be bound",syntax_.statement.begin);
  const auto& top = statement.at("SelectStmt");
  // Only a whole-result EXISTS wrapper is supported, with no outer FROM or
  // filters. Bind the inner target list for name/type errors, but preserve its
  // row-existence semantics separately from a nullary core CQ result.
  if (top.contains("targetList") && top.at("targetList").size() == 1) {
    const auto& target = tagged(top.at("targetList")[0],"ResTarget");
    const auto& value = target.at("val");
    if (value.contains("SubLink") && value.at("SubLink").value("subLinkType",std::string{}) == "EXISTS_SUBLINK") {
      keys(top,{"targetList","distinctClause","limitOption","op"});
      if (top.value("op",std::string{"SETOP_NONE"}) != "SETOP_NONE" || top.value("limitOption",std::string{"LIMIT_OPTION_DEFAULT"}) != "LIMIT_OPTION_DEFAULT") fail("unsupported_sql", "unsupported EXISTS wrapper clause");
      if (top.contains("distinctClause") && (top.at("distinctClause").size() != 1 || !top.at("distinctClause")[0].is_object() || !top.at("distinctClause")[0].empty())) fail("unsupported_distinct_on", "DISTINCT ON is not implemented");
      keys(target,{"name","val","location"});
      const auto& sublink = value.at("SubLink");
      keys(sublink,{"subLinkType","subselect","location"});
      select(tagged(sublink.at("subselect"),"SelectStmt"));
      result_.inner_semantics = result_.semantics;
      result_.semantics = top.contains("distinctClause") ? SqlSemantics::set : SqlSemantics::bag;
      result_.wrapper = SqlWrapper::exists;
      result_.wrapper_alias = target.value("name",std::string{"exists"});
      return std::move(result_);
    }
  }
  select(top);
  return std::move(result_);
}
}  // namespace

SqlBindResult bind_sql(std::string_view source, const Catalog& catalog, const BindOptions& options) {
  const auto parsed = parse_sql(source);
  if (const auto* failure = std::get_if<SqlDiagnostic>(&parsed)) return BindingDiagnostic{"syntax",*failure};
  try { catalog::validate_catalog(catalog); }
  catch (const Error& error) { return BindingDiagnostic{"catalog",{error.code(),error.what(),{},{},{},{}}}; }
  try {
    Catalog parameters;
    Table declaration{"parameters",options.parameters};
    for (std::size_t i = 0; i < declaration.columns.size(); ++i) declaration.columns[i].name = "$" + std::to_string(i + 1);
    parameters.tables.push_back(std::move(declaration));
    catalog::validate_catalog(parameters);
  } catch (const Error& error) { return BindingDiagnostic{"parameters",{error.code(),error.what(),{},{},{},{}}}; }
  // These handlers cover Binder construction/run. Parsing and declaration
  // validation above retain their own Error/allocation exception boundaries.
  try { return Binder(std::get<SqlSyntax>(parsed),catalog,options).run(); }
  catch (const Failure& failure) { return BindingDiagnostic{"binding",diagnostic(failure,source)}; }
  catch (const Json::exception& error) { return BindingDiagnostic{"binding",{"invalid_ast",error.what(),{},{},{},{}}}; }
  catch (const std::bad_alloc&) { return BindingDiagnostic{"binding",{"resource_limit","SQL binding allocation failed",{},{},{},{}}}; }
}

std::string sql_kind_name(SqlKind kind) {
  switch (kind) {
    case SqlKind::unknown: return "unknown";
    case SqlKind::int32: return "int32";
    case SqlKind::int64: return "int64";
    case SqlKind::string: return "string";
    case SqlKind::boolean: return "bool";
    case SqlKind::date: return "date";
    case SqlKind::decimal: return "decimal";
  }
  throw Error("binding_contract","unknown SQL type");
}
std::string sql_operator_name(SqlOperator op) {
  switch (op) {
    case SqlOperator::equal: return "equal";
    case SqlOperator::not_equal: return "not_equal";
    case SqlOperator::less: return "less";
    case SqlOperator::less_equal: return "less_equal";
    case SqlOperator::greater: return "greater";
    case SqlOperator::greater_equal: return "greater_equal";
    case SqlOperator::conjunction: return "conjunction";
    case SqlOperator::disjunction: return "disjunction";
    case SqlOperator::negation: return "negation";
    case SqlOperator::is_null: return "is_null";
    case SqlOperator::is_not_null: return "is_not_null";
    case SqlOperator::is_true: return "is_true";
    case SqlOperator::is_not_true: return "is_not_true";
    case SqlOperator::is_false: return "is_false";
    case SqlOperator::is_not_false: return "is_not_false";
    case SqlOperator::is_unknown: return "is_unknown";
    case SqlOperator::is_not_unknown: return "is_not_unknown";
    case SqlOperator::identity_cast: return "identity_cast";
    case SqlOperator::literal_cast: return "literal_cast";
    case SqlOperator::widen_integer: return "widen_integer";
    case SqlOperator::using_value: return "using_value";
  }
  throw Error("binding_contract","unknown SQL operator");
}
}  // namespace crown::frontend
