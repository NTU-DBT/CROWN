#include "crown/frontend/normalize.hpp"

#include "crown/api/error.hpp"
#include "crown/catalog/catalog.hpp"
#include <algorithm>
#include <limits>
#include <map>
#include <numeric>
#include <set>
#include <utility>

namespace crown::frontend {
namespace {
struct Failure { std::string code; std::string message; std::optional<std::size_t> location; };
[[noreturn]] void fail(std::string code, std::string message, std::optional<std::size_t> location = {}) {
  throw Failure{std::move(code), std::move(message), location};
}
// All callers pass literals; construct owned diagnostic text only on failure.
void contract(bool condition, const char* message) {
  if (!condition) throw Error("normalization_contract", message);
}
SqlDiagnostic diagnostic(const Failure& failure, std::string_view source) {
  SqlDiagnostic result{failure.code, failure.message, failure.location, {}, {}, {}};
  if (!failure.location || *failure.location > source.size()) { result.byte_offset.reset(); return result; }
  result.character_position = 1; result.line = 1; result.column = 1;
  for (std::size_t i = 0; i < *failure.location; ++i) {
    if ((static_cast<unsigned char>(source[i]) & 0xc0U) == 0x80U) continue;
    ++*result.character_position;
    if (source[i] == '\n') { ++*result.line; result.column = 1; }
    else ++*result.column;
  }
  return result;
}
bool integer(SqlKind kind) { return kind == SqlKind::int32 || kind == SqlKind::int64; }
ScalarType scalar(SqlKind kind) {
  switch (kind) {
    case SqlKind::int32: case SqlKind::int64: return ScalarType::int64;
    case SqlKind::string: return ScalarType::string;
    case SqlKind::boolean: return ScalarType::boolean;
    case SqlKind::date: return ScalarType::date;
    case SqlKind::decimal: return ScalarType::decimal;
    case SqlKind::unknown: break;
  }
  throw Error("normalization_contract", "unresolved SQL type in normalized projection");
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
bool fits(const SqlValue& value, const SqlType& type) {
  if (!value) return type.nullable;
  if (type.kind == SqlKind::unknown || type_of(*value) != scalar(type.kind)) return false;
  if (type.kind == SqlKind::int32) {
    const auto number = std::get<std::int64_t>(*value);
    if (number < std::numeric_limits<std::int32_t>::min() || number > std::numeric_limits<std::int32_t>::max()) return false;
  }
  return !type.decimal || catalog::decimal_fits(std::get<Decimal>(*value), *type.decimal);
}
std::optional<bool> truth(const SqlValue& value) {
  if (!value) return {};
  contract(std::holds_alternative<bool>(*value), "non-Boolean predicate value");
  return std::get<bool>(*value);
}
SqlValue boolean(std::optional<bool> value) { return value ? SqlValue{Value{*value}} : SqlValue{}; }
SqlValue evaluate_operation(const BoundOperation& node, const std::vector<SqlValue>& values) {
  const auto arg = [&](std::size_t i) -> const SqlValue& { return values.at(node.arguments.at(i).value); };
  switch (node.operation) {
    case SqlOperator::identity_cast: case SqlOperator::literal_cast:
    case SqlOperator::widen_integer: case SqlOperator::using_value: return arg(0);
    case SqlOperator::is_null: case SqlOperator::is_unknown: return Value{!arg(0)};
    case SqlOperator::is_not_null: case SqlOperator::is_not_unknown: return Value{arg(0).has_value()};
    case SqlOperator::is_true: return Value{truth(arg(0)) == std::optional<bool>{true}};
    case SqlOperator::is_not_true: return Value{truth(arg(0)) != std::optional<bool>{true}};
    case SqlOperator::is_false: return Value{truth(arg(0)) == std::optional<bool>{false}};
    case SqlOperator::is_not_false: return Value{truth(arg(0)) != std::optional<bool>{false}};
    case SqlOperator::negation: { const auto value = truth(arg(0)); return value ? boolean(!*value) : SqlValue{}; }
    case SqlOperator::conjunction: case SqlOperator::disjunction: {
      const bool conjunction = node.operation == SqlOperator::conjunction;
      bool null_seen = false;
      for (const auto id : node.arguments) {
        const auto value = truth(values.at(id.value));
        if (!value) null_seen = true;
        else if (*value != conjunction) return Value{!conjunction};
      }
      return null_seen ? SqlValue{} : SqlValue{Value{conjunction}};
    }
    case SqlOperator::equal: case SqlOperator::not_equal: case SqlOperator::less:
    case SqlOperator::less_equal: case SqlOperator::greater: case SqlOperator::greater_equal: {
      if (!arg(0) || !arg(1)) return {};
      contract(arg(0)->index() == arg(1)->index(), "incompatible comparison representations");
      const auto order = *arg(0) <=> *arg(1);
      switch (node.operation) {
        case SqlOperator::equal: return Value{order == 0};
        case SqlOperator::not_equal: return Value{order != 0};
        case SqlOperator::less: return Value{order < 0};
        case SqlOperator::less_equal: return Value{order <= 0};
        case SqlOperator::greater: return Value{order > 0};
        case SqlOperator::greater_equal: return Value{order >= 0};
        default: break;
      }
      break;
    }
  }
  throw Error("normalization_contract", "unknown SQL operation");
}

class Normalizer {
 public:
  Normalizer(const BoundSql& bound, const NormalizeOptions& options) {
    result_.binding = bound; result_.parameters = options.parameters; result_.limits = options.limits;
    result_.schema_version = options.schema_version;
  }
  NormalizedSql run();
 private:
  void charge() {
    if (result_.work == std::numeric_limits<std::uint64_t>::max() ||
        (result_.limits.work_limit && result_.work >= *result_.limits.work_limit)) fail("resource_limit", "SQL normalization work limit exceeded");
    ++result_.work;
  }
  const BoundExpression& expression(ExpressionId id) const {
    contract(id.value < result_.binding.expressions.size(), "expression ID outside binding");
    return result_.binding.expressions[id.value];
  }
  std::size_t root(std::size_t column) {
    charge();
    std::size_t current = column;
    while (parent_[current] != current) { charge(); current = parent_[current]; }
    while (column != current) { const auto next = parent_[column]; parent_[column] = current; column = next; }
    return current;
  }
  void unite(std::size_t left, std::size_t right) {
    left = root(left); right = root(right);
    if (left == right) return;
    if (rank_[left] < rank_[right]) std::swap(left,right);
    parent_[right] = left;
    if (rank_[left] == rank_[right]) ++rank_[left];
  }
  void analyze_expressions();
  void predicate(ExpressionId id);
  void program(OccurrenceAdapter& adapter);
  VariableId variable(ScalarType type) {
    charge();
    const VariableId id{result_.core.variables.size()};
    result_.core.variables.push_back({"v" + std::to_string(id.value),type});
    return id;
  }
  NormalizedSql result_;
  std::vector<std::set<std::size_t>> dependencies_;
  std::vector<std::optional<std::size_t>> column_expression_;
  std::vector<std::optional<ExpressionId>> physical_expression_;
  std::vector<std::size_t> offsets_;
  std::vector<std::size_t> parent_;
  std::vector<std::size_t> rank_;
  std::vector<bool> needed_;
  std::vector<std::pair<std::size_t,Value>> equal_constants_;
};

void Normalizer::analyze_expressions() {
  const auto& binding = result_.binding;
  dependencies_.resize(binding.expressions.size());
  column_expression_.resize(binding.expressions.size());
  result_.constants.resize(binding.expressions.size());
  for (std::size_t i = 0; i < binding.expressions.size(); ++i) {
    charge();
    const auto& item = binding.expressions[i];
    if (const auto* column = std::get_if<BoundColumn>(&item.node)) {
      contract(column->occurrence.value < binding.occurrences.size(), "column occurrence outside binding");
      const auto& columns = binding.catalog.tables[binding.occurrences[column->occurrence.value].table.value].columns;
      contract(column->column.value < columns.size(), "column ID outside occurrence");
      contract(item.type == sql_type(columns[column->column.value]), "column type differs from catalog");
      dependencies_[i].insert(column->occurrence.value);
      const auto physical = offsets_[column->occurrence.value] + column->column.value;
      column_expression_[i] = physical;
      if (!physical_expression_[physical]) physical_expression_[physical] = ExpressionId{i};
    } else if (const auto* literal = std::get_if<BoundLiteral>(&item.node)) {
      // Unused pre-resolution string/NULL nodes may still have unknown kind.
      contract(item.type.kind == SqlKind::unknown || fits(literal->value,item.type), "invalid typed literal");
      result_.constants[i] = literal->value;
    } else if (const auto* parameter = std::get_if<BoundParameter>(&item.node)) {
      contract(parameter->number > 0 && parameter->number <= binding.parameters.size(), "parameter outside signature");
      contract(item.type == binding.parameters[parameter->number - 1], "parameter type differs from signature");
      result_.constants[i] = result_.parameters[parameter->number - 1];
    } else {
      const auto& node = std::get<BoundOperation>(item.node);
      const auto count = node.arguments.size();
      const bool variadic = node.operation == SqlOperator::conjunction || node.operation == SqlOperator::disjunction;
      const bool binary = node.operation == SqlOperator::using_value ||
          (node.operation >= SqlOperator::equal && node.operation <= SqlOperator::greater_equal);
      contract(variadic ? count > 0 : count == (binary ? 2U : 1U), "SQL operation arity mismatch");
      for (const auto child : node.arguments) { charge(); contract(child.value < i, "binding expressions must be topological"); }
      const auto& first = expression(node.arguments[0]);
      switch (node.operation) {
        case SqlOperator::identity_cast: case SqlOperator::literal_cast:
          contract(item.type == first.type, "cast changes representation or nullability");
          column_expression_[i] = column_expression_[node.arguments[0].value]; break;
        case SqlOperator::widen_integer:
          contract(first.type.kind == SqlKind::int32 && item.type.kind == SqlKind::int64 &&
              first.type.nullable == item.type.nullable && !first.type.decimal && !item.type.decimal, "invalid integer promotion");
          column_expression_[i] = column_expression_[node.arguments[0].value]; break;
        case SqlOperator::using_value:
          contract(item.type.kind == first.type.kind, "USING output kind differs from left input");
          column_expression_[i] = column_expression_[node.arguments[0].value]; break;
        case SqlOperator::equal: case SqlOperator::not_equal: case SqlOperator::less:
        case SqlOperator::less_equal: case SqlOperator::greater: case SqlOperator::greater_equal: {
          const auto& second = expression(node.arguments[1]);
          contract(first.type.kind == second.type.kind || (integer(first.type.kind) && integer(second.type.kind)), "comparison kinds differ");
          contract(item.type.kind == SqlKind::boolean, "comparison must be Boolean"); break;
        }
        case SqlOperator::is_null: case SqlOperator::is_not_null:
          contract(item.type.kind == SqlKind::boolean && !item.type.nullable, "NULL test must be non-null Boolean"); break;
        default:
          contract(item.type.kind == SqlKind::boolean, "Boolean operation has non-Boolean result");
          for (const auto child : node.arguments) contract(expression(child).type.kind == SqlKind::boolean, "Boolean operation has non-Boolean input");
          break;
      }
      // An inner USING value is the left value. The separate mandatory equality
      // predicate checks the right side; it is not a COALESCE or outer join.
      const auto arguments = node.operation == SqlOperator::using_value ? std::size_t{1} : count;
      for (std::size_t j = 0; j < arguments; ++j) {
        for (const auto dependency : dependencies_[node.arguments[j].value]) { charge(); dependencies_[i].insert(dependency); }
      }
      if (dependencies_[i].empty()) result_.constants[i] = evaluate_operation(node,result_.constants);
    }
  }
}

void Normalizer::predicate(ExpressionId id) {
  charge();
  const auto& item = expression(id);
  contract(item.type.kind == SqlKind::boolean, "predicate is not Boolean");
  const auto& dependencies = dependencies_[id.value];
  const auto* operation = std::get_if<BoundOperation>(&item.node);
  bool equality = false;
  if (operation && operation->operation == SqlOperator::equal) {
    const auto left = column_expression_[operation->arguments[0].value];
    const auto right = column_expression_[operation->arguments[1].value];
    if (left && right) {
      unite(*left,*right); needed_[*left] = true; needed_[*right] = true; equality = true;
    } else if (left || right) {
      const auto constant = operation->arguments[left ? 1 : 0];
      if (dependencies_[constant.value].empty()) {
        if (!result_.constants[constant.value]) result_.core.contradiction = true;
        else equal_constants_.emplace_back(left ? *left : *right,*result_.constants[constant.value]);
      }
    }
    if (left || right) {
      for (const auto physical : {left,right}) {
        if (!physical) continue;
        const auto occurrence = static_cast<std::size_t>(std::upper_bound(offsets_.begin(),offsets_.end(),*physical) - offsets_.begin() - 1);
        result_.adapters[occurrence].non_null_columns.push_back(ColumnId{*physical - offsets_[occurrence]});
      }
    }
  }
  if (dependencies.empty()) {
    if (truth(result_.constants[id.value]) != std::optional<bool>{true}) result_.core.contradiction = true;
  } else if (dependencies.size() == 1) {
    result_.adapters[*dependencies.begin()].predicates.push_back(id);
  } else if (!equality) {
    fail("unsupported_cross_relation_predicate", "only unconditional column equalities may span occurrences", item.location);
  }
}

void Normalizer::program(OccurrenceAdapter& adapter) {
  std::set<ExpressionId> needed;
  std::vector<ExpressionId> pending = adapter.predicates;
  for (const auto& projection : adapter.projection) pending.push_back(projection.expression);
  while (!pending.empty()) {
    charge();
    const auto id = pending.back(); pending.pop_back();
    if (dependencies_[id.value].empty() || !needed.insert(id).second) continue;
    contract(dependencies_[id.value].size() == 1 && *dependencies_[id.value].begin() == adapter.occurrence.value, "nonlocal expression in adapter");
    if (const auto* node = std::get_if<BoundOperation>(&expression(id).node)) {
      if (node->operation == SqlOperator::using_value) pending.push_back(node->arguments[0]);
      else for (const auto child : node->arguments) pending.push_back(child);
    }
  }
  adapter.program.assign(needed.begin(),needed.end());
}

NormalizedSql Normalizer::run() {
  charge();
  const auto& binding = result_.binding;
  catalog::validate_catalog(binding.catalog);
  if (binding.wrapper == SqlWrapper::rows && binding.semantics != SqlSemantics::set)
    fail("unsupported_semantics", "plain SELECT requires bag semantics; the current CQ normalization requires DISTINCT");
  if (result_.parameters.size() != binding.parameters.size()) fail("unbound_parameter", "one value is required for every declared parameter");
  for (std::size_t i = 0; i < result_.parameters.size(); ++i) {
    charge();
    if (!fits(result_.parameters[i],binding.parameters[i])) fail("invalid_parameter", "parameter $" + std::to_string(i + 1) + " does not match its declared exact type/nullability");
  }
  result_.base_routes.resize(binding.catalog.tables.size());
  std::size_t column_count = 0;
  for (std::size_t i = 0; i < binding.occurrences.size(); ++i) {
    charge();
    const auto& occurrence = binding.occurrences[i];
    contract(occurrence.table.value < binding.catalog.tables.size(), "base table outside catalog");
    offsets_.push_back(column_count);
    const auto& columns = binding.catalog.tables[occurrence.table.value].columns;
    for (const auto& column : columns) {
      charge();
      if (column.nullable) fail("unsupported_nullable_input", "the current SQL adapter requires non-null source columns: " + occurrence.alias + "." + column.name,occurrence.location);
      contract(column_count < std::numeric_limits<std::size_t>::max(), "column count overflow"); ++column_count;
    }
    result_.adapters.push_back({OccurrenceId{i},occurrence.table,{},{},{},{},{},{}});
    result_.base_routes[occurrence.table.value].push_back(OccurrenceId{i});
  }
  parent_.resize(column_count); std::iota(parent_.begin(),parent_.end(),std::size_t{0});
  rank_.resize(column_count); needed_.resize(column_count); physical_expression_.resize(column_count);
  analyze_expressions();
  // Only top-level AND is an unconditional conjunction. Equalities below OR,
  // NOT, Boolean tests, etc. stay within their local predicate or reject.
  std::vector<ExpressionId> pending(binding.predicates.rbegin(),binding.predicates.rend());
  while (!pending.empty()) {
    charge(); const auto id = pending.back(); pending.pop_back();
    const auto* node = std::get_if<BoundOperation>(&expression(id).node);
    if (node && node->operation == SqlOperator::conjunction) {
      for (auto i = node->arguments.rbegin(); i != node->arguments.rend(); ++i) pending.push_back(*i);
    } else predicate(id);
  }
  std::map<std::size_t,Value> constants;
  for (const auto& [column,value] : equal_constants_) {
    const auto representative = root(column);
    const auto [entry,inserted] = constants.emplace(representative,value);
    if (!inserted && entry->second != value) result_.core.contradiction = true;
  }
  if (binding.wrapper == SqlWrapper::rows) {
    for (const auto& output : binding.outputs) {
      charge(); static_cast<void>(expression(output.expression));
      if (column_expression_[output.expression.value]) needed_[*column_expression_[output.expression.value]] = true;
    }
  }
  std::set<std::size_t> live;
  for (std::size_t i = 0; i < needed_.size(); ++i) { charge(); if (needed_[i]) live.insert(root(i)); }
  std::map<std::size_t,VariableId> variables;
  for (auto& adapter : result_.adapters) {
    const auto& columns = binding.catalog.tables[adapter.base.value].columns;
    std::map<std::size_t,ColumnId> first;
    for (std::size_t c = 0; c < columns.size(); ++c) {
      const auto physical = offsets_[adapter.occurrence.value] + c;
      const auto representative = root(physical);
      if (result_.schema_version >= 2) {
        const auto fixed = constants.find(representative);
        if (fixed != constants.end()) {
          charge();
          adapter.constant_columns.push_back({ColumnId{c},fixed->second});
          adapter.column_classes.push_back({});
          continue;
        }
      }
      if (!live.contains(representative)) { adapter.column_classes.push_back({}); continue; }
      auto entry = variables.find(representative);
      if (entry == variables.end()) entry = variables.emplace(representative,variable(columns[c].type)).first;
      adapter.column_classes.push_back(entry->second);
      const auto [previous,inserted] = first.emplace(representative,ColumnId{c});
      if (inserted) {
        contract(physical_expression_[physical].has_value(), "physical column lacks bound expression");
        adapter.projection.push_back({entry->second,*physical_expression_[physical]});
      } else adapter.equal_columns.push_back({previous->second,ColumnId{c}});
    }
    std::sort(adapter.non_null_columns.begin(),adapter.non_null_columns.end());
    adapter.non_null_columns.erase(std::unique(adapter.non_null_columns.begin(),adapter.non_null_columns.end()),adapter.non_null_columns.end());
  }
  if (binding.wrapper == SqlWrapper::rows) {
    for (const auto& output : binding.outputs) {
      charge(); const auto id = output.expression; const auto& item = expression(id);
      const auto& dependencies = dependencies_[id.value];
      if (dependencies.empty()) {
        if (!result_.constants[id.value]) fail("unsupported_null_output", "NULL row outputs require a nullable result representation",item.location);
        auto type = item.type; type.nullable = false;
        result_.outputs.push_back({output.name,type,ConstantOutput{*result_.constants[id.value]}});
        continue;
      }
      std::optional<VariableId> selected;
      if (column_expression_[id.value]) {
        const auto representative = root(*column_expression_[id.value]);
        const auto fixed = constants.find(representative);
        if (result_.schema_version >= 2 && fixed != constants.end()) {
          result_.outputs.push_back({output.name,item.type,ConstantOutput{fixed->second}});
          continue;
        }
        selected = variables.at(representative);
      }
      else {
        if (dependencies.size() != 1) fail("unsupported_cross_relation_output", "a computed row output must depend on one occurrence",item.location);
        if (item.type.nullable) fail("unsupported_null_output", "nullable row outputs require a nullable result representation",item.location);
        selected = variable(scalar(item.type.kind));
        result_.adapters[*dependencies.begin()].projection.push_back({*selected,id});
      }
      const auto position = result_.core.head.size();
      result_.core.head.push_back({*selected,output.name});
      result_.outputs.push_back({output.name,item.type,CoreOutput{position}});
    }
  }
  result_.core_catalog.version = binding.catalog.version;
  for (auto& adapter : result_.adapters) {
    charge(); program(adapter);
    Table table{"occurrence_" + std::to_string(adapter.occurrence.value),{}};
    // Hidden join-input aliases may legally be reused by an outer FROM item.
    // Core occurrence names are IDs, while SQL labels remain in the binding.
    Atom atom{table.name,TableId{adapter.occurrence.value},{}};
    for (const auto& projection : adapter.projection) {
      charge();
      const auto& v = result_.core.variables[projection.variable.value];
      table.columns.push_back({v.name,v.type}); atom.terms.push_back(projection.variable);
    }
    result_.core_catalog.tables.push_back(std::move(table)); result_.core.atoms.push_back(std::move(atom));
  }
  validate(result_.core_catalog,result_.core);
  return std::move(result_);
}
}  // namespace

SqlNormalizeResult normalize_sql(const BoundSql& binding, const NormalizeOptions& options) {
  if (options.schema_version != 1 && options.schema_version != 2) throw Error("unsupported_version","normalized program format must be 1 or 2");
  try { return Normalizer(binding,options).run(); }
  catch (const Failure& failure) {
    const auto phase = failure.code == "invalid_parameter" || failure.code == "unbound_parameter" ? "parameters" : "normalization";
    return BindingDiagnostic{phase,diagnostic(failure,binding.source)};
  }
}

std::optional<Row> adapt_row(const NormalizedSql& query, OccurrenceId occurrence, const Row& physical) {
  const auto& adapter = query.adapters.at(occurrence.value);
  validate_row(query.binding.catalog,adapter.base,physical);
  for (const auto& fixed : adapter.constant_columns) if (physical.at(fixed.column.value) != fixed.value) return {};
  for (const auto& equality : adapter.equal_columns) if (physical.at(equality.left.value) != physical.at(equality.right.value)) return {};
  // Each call copies query-wide constant slots before its local evaluation.
  auto values = query.constants;
  for (const auto id : adapter.program) {
    const auto& node = query.binding.expressions.at(id.value).node;
    if (const auto* column = std::get_if<BoundColumn>(&node)) {
      contract(column->occurrence == occurrence, "foreign column in local adapter");
      values[id.value] = physical.at(column->column.value);
    } else if (const auto* operation = std::get_if<BoundOperation>(&node)) values[id.value] = evaluate_operation(*operation,values);
    else throw Error("normalization_contract", "constant node in nonconstant adapter program");
  }
  for (const auto id : adapter.predicates) if (truth(values.at(id.value)) != std::optional<bool>{true}) return {};
  Row result;
  for (const auto& projection : adapter.projection) {
    const auto& value = values.at(projection.expression.value);
    contract(value.has_value(), "adapter emitted NULL into the classical core"); result.push_back(*value);
  }
  return result;
}

Relation map_sql_result(const NormalizedSql& query, const Relation& core_result) {
  if (query.binding.wrapper == SqlWrapper::exists) return Relation{Row{Value{!core_result.empty()}}};
  Relation result;
  for (const auto& core : core_result) {
    contract(core.size() == query.core.head.size(), "core result arity differs from normalized head");
    Row row;
    for (const auto& output : query.outputs) {
      if (const auto* column = std::get_if<CoreOutput>(&output.value)) row.push_back(core.at(column->column));
      else row.push_back(std::get<ConstantOutput>(output.value).value);
    }
    result.insert(std::move(row));
  }
  return result;
}
}  // namespace crown::frontend
