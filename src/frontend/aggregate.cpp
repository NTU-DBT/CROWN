#include "crown/frontend/aggregate.hpp"
#include "crown/api/error.hpp"
#include "crown/catalog/catalog.hpp"
#include "crown/resource/ownership.hpp"
#include <algorithm>
#include <array>
#include <charconv>
#include <limits>
#include <map>
#include <set>
#include <utility>

namespace crown::frontend {
namespace {
template<class T> using Items = std::vector<T, resource::MemoryAllocator<T>>;
using Text = std::basic_string<char, std::char_traits<char>, resource::MemoryAllocator<char>>;
template<class T> resource::MemoryAllocator<T> allocator(const resource::MemoryAccount& account) {
  return resource::MemoryAllocator<T>(account, resource::MemoryPurpose::immutable_metadata,
      resource::MemoryAttribution{resource::MemoryOwnerKind::immutable_metadata, 0});
}
[[noreturn]] void fail(std::string code, std::string message) {
  throw Error(std::move(code), std::move(message));
}
bool integer(SqlKind kind) { return kind == SqlKind::int32 || kind == SqlKind::int64; }
bool int32(std::int64_t value) { return value >= INT32_MIN && value <= INT32_MAX; }
std::optional<std::int64_t> integer_text(std::string_view text) {
  std::int64_t value = 0;
  const auto [end, error] = std::from_chars(text.data(), text.data() + text.size(), value);
  if (error != std::errc{} || end != text.data() + text.size()) return {};
  return value;
}
SqlType column_type(const Column& column) {
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
}  // namespace

struct AggregateProgram::Data {
  resource::MemoryAccount account;
  Text source;
  bool has_input = false, full_input_key = false;
  Items<SqlType> inputs;
  Items<ColumnId> groups;
  Items<ColumnId> checked_int32;
  // Backing rows/names precede their borrowed views and remain stable.
  Items<storage::AccountedRow> literals;
  Items<Text> names;
  Items<AggregateMeasure> measures;
  Items<AggregateOutput> outputs;
  std::uint8_t scale = 18;
  std::uint64_t work = 0;
  explicit Data(const resource::MemoryAccount& value)
      : account(value), source(allocator<char>(value)), inputs(allocator<SqlType>(value)),
        groups(allocator<ColumnId>(value)), checked_int32(allocator<ColumnId>(value)),
        literals(allocator<storage::AccountedRow>(value)),
        names(allocator<Text>(value)), measures(allocator<AggregateMeasure>(value)),
        outputs(allocator<AggregateOutput>(value)) {}
};

namespace detail {
class AggregateCompiler {
  using Json = nlohmann::json;
  struct Argument {
    SqlType type;
    std::variant<ColumnId, std::optional<Value>> value;
  };
  struct MeasureKey {
    SqlType type;
    AggregateArgument argument;
    auto operator<=>(const MeasureKey&) const = default;
  };
  const SqlSyntax& syntax_;
  const Catalog& catalog_;
  const AggregateBindOptions& options_;
  resource::MemoryAccount account_;
  std::shared_ptr<AggregateProgram::Data> result_;
  std::optional<catalog::RelationBinding> input_;
  std::map<ColumnId, std::size_t> group_positions_;
  std::map<MeasureKey, std::size_t> measure_positions_;
  // Compiler-only deduplication. One retained guard per original column also
  // preserves an inner narrowing cast when an outer cast widens it again.
  std::set<ColumnId> checked_int32_;
  std::uint64_t work_ = 0;
  bool aggregate_ = false;

  // Selected compiler checkpoints and retained text lengths, not all parser,
  // catalog validation, ordered-map comparisons or allocator CPU work.
  void charge(std::uint64_t amount = 1) {
    if (amount > UINT64_MAX - work_ ||
        (options_.limits.work_limit && amount > *options_.limits.work_limit - work_))
      fail("resource_limit", "aggregate binding work limit exceeded");
    work_ += amount;
  }
  void keys(const Json& node, std::initializer_list<std::string_view> allowed) {
    charge();
    if (!node.is_object()) fail("invalid_ast", "expected an aggregate SQL object");
    for (const auto& [key, unused] : node.items()) {
      static_cast<void>(unused);
      if (std::find(allowed.begin(), allowed.end(), key) == allowed.end())
        fail("unsupported_sql", "unsupported aggregate SQL field: " + key);
    }
  }
  const Json& tagged(const Json& node, std::string_view tag) const {
    if (!node.is_object() || node.size() != 1 || !node.contains(tag) || !node.at(tag).is_object())
      fail("unsupported_expression", "expected " + std::string(tag) + " in aggregate SQL");
    return node.at(tag);
  }
  std::string identifier(const Json& node) const {
    return tagged(node, "String").value("sval", std::string{});
  }
  ColumnId column(const Json& expression) {
    const auto& node = tagged(expression, "ColumnRef");
    keys(node, {"fields", "location"});
    const auto& names = node.at("fields");
    if (!input_) fail("unknown_column", "aggregate query has no input columns");
    if (names.empty() || names.size() > 2)
      fail("unsupported_qualification", "aggregate columns use name or alias.name");
    std::optional<std::string> qualifier;
    if (names.size() == 2) qualifier = identifier(names[0]);
    return catalog::resolve_column(catalog_, std::span<const catalog::RelationBinding>(&*input_, 1),
        qualifier ? std::optional<std::string_view>{*qualifier} : std::nullopt,
        identifier(names.back())).column;
  }
  Argument literal(const Json& node) {
    keys(node, {"ival", "fval", "sval", "boolval", "isnull", "location"});
    if (node.value("isnull", false)) return {{SqlKind::unknown, true, {}}, std::optional<Value>{}};
    if (node.contains("ival")) {
      const auto value = node.at("ival").value("ival", std::int64_t{0});
      return {{int32(value) ? SqlKind::int32 : SqlKind::int64, false, {}}, std::optional<Value>{Value{value}}};
    }
    if (node.contains("fval")) {
      const auto text = node.at("fval").at("fval").get<std::string>();
      if (text.find_first_of(".eE") == std::string::npos)
        if (const auto value = integer_text(text))
          return {{SqlKind::int64, false, {}}, std::optional<Value>{Value{*value}}};
      return {{SqlKind::decimal, false, {}}, std::optional<Value>{Value{Decimal::parse(text)}}};
    }
    if (node.contains("boolval"))
      return {{SqlKind::boolean, false, {}}, std::optional<Value>{Value{node.at("boolval").value("boolval", false)}}};
    if (node.contains("sval"))
      return {{SqlKind::string, false, {}}, std::optional<Value>{Value{node.at("sval").value("sval", std::string{})}}};
    fail("unsupported_literal", "unsupported aggregate literal");
  }
  SqlType cast_type(const Json& node) {
    keys(node, {"names", "typemod", "typmods", "location"});
    if (node.contains("typmods")) fail("unsupported_cast", "aggregate argument type modifiers are not admitted");
    const auto& names = node.at("names");
    if (names.empty() || names.size() > 2 || (names.size() == 2 && identifier(names[0]) != "pg_catalog"))
      fail("unsupported_type", "unsupported aggregate cast qualification");
    const auto name = identifier(names.back());
    if (name == "int8" || name == "bigint") return {SqlKind::int64, false, {}};
    if (name == "int4" || name == "integer") return {SqlKind::int32, false, {}};
    if (name == "text") return {SqlKind::string, false, {}};
    if (name == "bool" || name == "boolean") return {SqlKind::boolean, false, {}};
    if (name == "date") return {SqlKind::date, false, {}};
    if (name == "numeric" || name == "decimal") return {SqlKind::decimal, false, {}};
    fail("unsupported_type", "unsupported aggregate argument cast: " + name);
  }
  Argument argument(const Json& expression, std::size_t depth = 0) {
    charge();
    if (depth >= options_.limits.recursion_limit) fail("resource_limit", "aggregate cast depth limit exceeded");
    if (expression.contains("ColumnRef")) {
      const auto id = column(expression);
      return {result_->inputs[id.value], id};
    }
    if (expression.contains("A_Const")) return literal(tagged(expression, "A_Const"));
    if (!expression.contains("TypeCast")) fail("unsupported_expression", "aggregate arguments use columns or constants");
    const auto& cast = tagged(expression, "TypeCast");
    keys(cast, {"arg", "typeName", "location"});
    auto target = cast_type(cast.at("typeName"));
    auto value = argument(cast.at("arg"), depth + 1);
    target.nullable = value.type.nullable;
    if (const auto* id = std::get_if<ColumnId>(&value.value)) {
      if (value.type != target && !(integer(value.type.kind) && integer(target.kind)))
        fail("unsupported_cast", "aggregate column casts require the same type or an integer conversion");
      if (value.type.kind == SqlKind::int64 && target.kind == SqlKind::int32)
        checked_int32_.insert(*id);
    } else if (auto& scalar = std::get<std::optional<Value>>(value.value); scalar) {
      if (integer(target.kind)) {
        std::optional<std::int64_t> number;
        if (const auto* text = std::get_if<std::string>(&*scalar)) number = integer_text(*text);
        else if (const auto* number_value = std::get_if<std::int64_t>(&*scalar)) number = *number_value;
        if (!number || (target.kind == SqlKind::int32 && !int32(*number)))
          fail("unsupported_cast", "aggregate integer cast is not exactly representable");
        scalar = Value{*number};
      } else if (target.kind == SqlKind::date && std::holds_alternative<std::string>(*scalar))
        scalar = Value{Date::parse(std::get<std::string>(*scalar))};
      else if (target.kind == SqlKind::decimal && std::holds_alternative<std::string>(*scalar))
        scalar = Value{Decimal::parse(std::get<std::string>(*scalar))};
      else if (value.type.kind != target.kind) fail("unsupported_cast", "unsupported aggregate constant conversion");
    }
    value.type = target;
    return value;
  }
  // Find with an ephemeral borrowed literal. Only the first distinct argument
  // copies its literal into stable accounted backing retained by the program.
  std::size_t measure(Argument value) {
    AggregateArgument borrowed;
    if (const auto* id = std::get_if<ColumnId>(&value.value)) borrowed = *id;
    else {
      const auto& constant = std::get<std::optional<Value>>(value.value);
      borrowed = constant ? std::optional<storage::ScalarView>{storage::borrow_scalar(*constant)} : std::nullopt;
    }
    const MeasureKey key{value.type, borrowed};
    if (const auto found = measure_positions_.find(key); found != measure_positions_.end()) return found->second;
    if (result_->measures.size() >= options_.limits.expression_limit)
      fail("resource_limit", "aggregate argument limit exceeded");
    auto stable = borrowed;
    if (const auto* constant = std::get_if<std::optional<Value>>(&value.value); constant && *constant) {
      const std::array cell{storage::borrow_scalar(**constant)};
      result_->literals.push_back(storage::AccountedRow::copy_of(account_, storage::RowView::borrow(cell),
          {resource::MemoryOwnerKind::immutable_metadata, 0}));
      stable = std::optional<storage::ScalarView>{result_->literals.back().view()[0]};
    }
    const auto index = result_->measures.size();
    result_->measures.push_back({value.type, stable, false, false});
    measure_positions_.emplace(MeasureKey{value.type, stable}, index);
    return index;
  }
  void from(const Json& node) {
    const auto& from = tagged(node, "RangeVar");
    keys(from, {"relname", "inh", "relpersistence", "alias", "location", "schemaname", "catalogname"});
    if (from.contains("schemaname") || from.contains("catalogname"))
      fail("unsupported_qualification", "aggregate input uses a flat logical relation");
    const auto name = from.at("relname").get<std::string>();
    const auto table = catalog::find_table(catalog_, name);
    std::string qualifier = name;
    if (from.contains("alias")) {
      keys(from.at("alias"), {"aliasname"});
      qualifier = from.at("alias").at("aliasname").get<std::string>();
    }
    input_ = catalog::RelationBinding{table, std::move(qualifier)};
    result_->has_input = true;
    const auto& columns = catalog_.tables[table.value].columns;
    charge(static_cast<std::uint64_t>(columns.size()));
    result_->inputs.reserve(columns.size());
    for (const auto& value : columns) result_->inputs.push_back(column_type(value));
  }
  void output(const Json& expression) {
    const auto& target = tagged(expression, "ResTarget");
    keys(target, {"name", "val", "location"});
    const auto& node = target.at("val");
    AggregateOutput value{};
    std::string name;
    if (node.contains("FuncCall")) {
      aggregate_ = true;
      const auto& call = tagged(node, "FuncCall");
      keys(call, {"funcname", "args", "agg_star", "agg_distinct", "funcformat", "location"});
      if (call.value("agg_distinct", false)) fail("unsupported_distinct_aggregate", "DISTINCT aggregates require value reference counts");
      if (call.at("funcname").size() != 1) fail("unsupported_function", "aggregate functions must be unqualified");
      name = identifier(call.at("funcname")[0]);
      if (name != "count" && name != "sum" && name != "avg") fail("unsupported_function", "only COUNT, SUM and AVG are admitted");
      if (call.value("agg_star", false)) {
        if (name != "count" || (call.contains("args") && !call.at("args").empty()))
          fail("unsupported_argument", "only COUNT(*) admits the star argument");
        value = {{}, {SqlKind::int64, false, {}}, AggregateOutputKind::count_all, 0};
      } else {
        if (!call.contains("args") || call.at("args").size() != 1)
          fail("unsupported_argument", "aggregate requires exactly one scalar argument");
        auto arg = argument(call.at("args")[0]);
        if (name != "count" && !integer(arg.type.kind))
          fail("type_mismatch", "SUM/AVG initially require an integer argument; type NULL explicitly");
        const auto type = arg.type;
        const auto index = measure(std::move(arg));
        if (name == "count") value = {{}, {SqlKind::int64, false, {}}, AggregateOutputKind::count_value, index};
        else {
          result_->measures[index].sum = true;
          if (name == "sum" && type.kind == SqlKind::int32) {
            result_->measures[index].int64_sum = true;
            value = {{}, {SqlKind::int64, true, {}}, AggregateOutputKind::sum, index};
          } else {
            const auto scale = name == "avg" ? options_.average_scale : std::uint8_t{0};
            value = {{}, {SqlKind::decimal, true, DecimalSpec{38, scale}},
                name == "avg" ? AggregateOutputKind::average : AggregateOutputKind::sum, index};
          }
        }
      }
    } else {
      const auto id = column(node);
      const auto found = group_positions_.find(id);
      if (found == group_positions_.end()) fail("ungrouped_column", "output column must appear in GROUP BY");
      name = catalog_.tables[input_->table.value].columns[id.value].name;
      value = {{}, result_->inputs[id.value], AggregateOutputKind::group, found->second};
    }
    const auto label = target.value("name", name);
    result_->names.emplace_back(label.begin(), label.end(), allocator<char>(account_));
    value.name = result_->names.back();
    result_->outputs.push_back(value);
  }
 public:
  AggregateCompiler(const SqlSyntax& syntax, const Catalog& catalog, const AggregateBindOptions& options,
      const resource::MemoryAccount& account) : syntax_(syntax), catalog_(catalog), options_(options), account_(account) {}
  AggregateProgram run() {
    if (options_.average_scale > 18) fail("invalid_options", "AVG scale must be in 0..18");
    charge(static_cast<std::uint64_t>(syntax_.source.size()));
    const auto& statement = tagged(syntax_.ast.at("stmts")[0].at("stmt"), "SelectStmt");
    keys(statement, {"targetList", "fromClause", "groupClause", "limitOption", "op"});
    if (statement.value("op", std::string{"SETOP_NONE"}) != "SETOP_NONE" ||
        statement.value("limitOption", std::string{"LIMIT_OPTION_DEFAULT"}) != "LIMIT_OPTION_DEFAULT")
      fail("unsupported_sql", "aggregate set/limit operations are not admitted");
    if (!statement.contains("targetList") || statement.at("targetList").empty())
      fail("unsupported_sql", "aggregate query requires an output");
    const auto targets = statement.at("targetList").size();
    if (targets > options_.limits.expression_limit) fail("resource_limit", "aggregate output limit exceeded");
    result_ = resource::make_accounted_shared<AggregateProgram::Data>(
        resource::MemoryAttribution{resource::MemoryOwnerKind::immutable_metadata, 0}, account_,
        resource::MemoryPurpose::immutable_metadata, account_);
    result_->source.assign(syntax_.source.begin(), syntax_.source.end());
    result_->scale = options_.average_scale;
    result_->outputs.reserve(targets);
    // Name views may point into SSO storage: reserve once before any view exists.
    result_->names.reserve(targets);
    if (statement.contains("fromClause") && !statement.at("fromClause").empty()) {
      if (statement.at("fromClause").size() != 1) fail("unsupported_source", "aggregate requires one logical input relation");
      from(statement.at("fromClause")[0]);
    }
    if (statement.contains("groupClause")) for (const auto& item : statement.at("groupClause")) {
      const auto id = column(item);
      const auto position = result_->groups.size();
      if (group_positions_.emplace(id, position).second) result_->groups.push_back(id);
    }
    for (const auto& target : statement.at("targetList")) output(target);
    if (!aggregate_) fail("unsupported_sql", "query has no admitted aggregate");
    charge(static_cast<std::uint64_t>(checked_int32_.size()));
    result_->checked_int32.assign(checked_int32_.begin(), checked_int32_.end());
    result_->full_input_key = result_->groups.size() == result_->inputs.size();
    for (std::size_t i = 0; i < result_->groups.size(); ++i)
      if (result_->groups[i].value != i) result_->full_input_key = false;
    result_->work = work_;
    return AggregateProgram(std::move(result_));
  }
};
}  // namespace detail

AggregateProgram AggregateProgram::freeze(const resource::MemoryAccount& account, const AggregateProgram& source) {
  if (!account) throw resource::MemoryFailure(resource::MemoryFault::contract);
  const auto& old = source.data();
  if (account.statistics().owner == old.account.statistics().owner) return source;
  auto out = resource::make_accounted_shared<Data>(account, resource::MemoryPurpose::immutable_metadata, account);
  out->source.assign(old.source.begin(), old.source.end());
  out->has_input = old.has_input; out->full_input_key = old.full_input_key;
  out->scale = old.scale; out->work = old.work; // Historic compilation work, not copy-work metering.
  out->inputs.assign(old.inputs.begin(), old.inputs.end()); out->groups.assign(old.groups.begin(), old.groups.end());
  out->checked_int32.assign(old.checked_int32.begin(), old.checked_int32.end());
  out->literals.reserve(old.literals.size()); out->names.reserve(old.outputs.size());
  out->measures.reserve(old.measures.size()); out->outputs.reserve(old.outputs.size());
  for (auto measure : old.measures) {
    if (auto* constant = std::get_if<std::optional<storage::ScalarView>>(&measure.argument); constant && *constant) {
      const std::array cell{**constant};
      out->literals.push_back(storage::AccountedRow::copy_of(account, storage::RowView::borrow(cell),
          {resource::MemoryOwnerKind::immutable_metadata, 0}));
      *constant = out->literals.back().view()[0];
    }
    out->measures.push_back(std::move(measure));
  }
  for (auto output : old.outputs) {
    out->names.emplace_back(output.name.begin(), output.name.end(), allocator<char>(account));
    output.name = out->names.back(); // Reserved vector keeps even SSO character addresses stable.
    out->outputs.push_back(std::move(output));
  }
  return AggregateProgram(std::move(out));
}

const AggregateProgram::Data& AggregateProgram::data() const {
  if (!data_) fail("invalid_aggregate_program", "aggregate program handle is empty");
  return *data_;
}
std::string_view AggregateProgram::source() const & { return data().source; }
bool AggregateProgram::has_input() const { return data().has_input; }
bool AggregateProgram::full_input_group_key() const { return data().full_input_key; }
std::span<const SqlType> AggregateProgram::input_types() const & { return data().inputs; }
std::span<const ColumnId> AggregateProgram::group_columns() const & { return data().groups; }
std::span<const ColumnId> AggregateProgram::checked_int32_columns() const & { return data().checked_int32; }
std::span<const AggregateMeasure> AggregateProgram::measures() const & { return data().measures; }
std::span<const AggregateOutput> AggregateProgram::outputs() const & { return data().outputs; }
std::uint8_t AggregateProgram::average_scale() const { return data().scale; }
std::uint64_t AggregateProgram::work() const { return data().work; }
const resource::MemoryAccount& AggregateProgram::account() const & { return data().account; }

AggregateBindResult bind_aggregate_sql_into(const resource::MemoryAccount& account, std::string_view source,
    const Catalog& catalog_value, const AggregateBindOptions& options) {
  const auto parsed = parse_sql(source);
  if (const auto* error = std::get_if<SqlDiagnostic>(&parsed)) return BindingDiagnostic{"syntax", *error};
  std::string_view phase = "catalog";
  try {
    catalog::validate_catalog(catalog_value);
    phase = "aggregate_binding";
    if (!account) fail("invalid_account", "aggregate compiler needs a receiving account");
    return detail::AggregateCompiler(std::get<SqlSyntax>(parsed), catalog_value, options, account).run();
  } catch (const Error& error) {
    return BindingDiagnostic{std::string(phase), {error.code(), error.what(), {}, {}, {}, {}}};
  }
}
AggregateBindResult bind_aggregate_sql(std::string_view source, const Catalog& catalog_value,
    const AggregateBindOptions& options) {
  return bind_aggregate_sql_into(resource::MemoryAccount::create(options.memory_limit_bytes), source, catalog_value, options);
}
}  // namespace crown::frontend
