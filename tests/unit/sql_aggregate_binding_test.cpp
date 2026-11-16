#include "crown/frontend/sql_aggregate.hpp"
#include "crown/api/error.hpp"
#include "crown/io/catalog.hpp"
#include <cassert>
#include <iostream>

namespace {
using namespace crown;
using namespace crown::frontend;
Catalog schema() {
  return {1, {{"r", {{"id", ScalarType::int64, true}, {"g", ScalarType::string, true},
      {"x", ScalarType::int64, true}, {"flag", ScalarType::boolean}}},
      {"s", {{"id", ScalarType::int64, true}, {"y", ScalarType::int64, true}}}}};
}
SqlAggregateProgram compile(std::string_view sql, const Catalog& catalog = schema(),
    const SqlAggregateBindOptions& options = {}) {
  auto result = bind_sql_aggregate(sql, catalog, options);
  if (const auto* failure = std::get_if<BindingDiagnostic>(&result)) throw Error(failure->diagnostic.code, failure->diagnostic.message);
  return std::get<SqlAggregateProgram>(std::move(result));
}
void reject(std::string_view sql, std::string_view code, const SqlAggregateBindOptions& options = {}) {
  const auto result = bind_sql_aggregate(sql, schema(), options);
  const auto* failure = std::get_if<BindingDiagnostic>(&result);
  assert(failure && failure->diagnostic.code == code);
}
void controller_only(const resource::MemoryAccount& account) {
  account.check_invariants();
  assert(account.statistics().current.allocations == 1 &&
      account.statistics().current.requested_bytes == resource::MemoryAccount::control_bytes());
}

// Only original SQL reaches the factory; no BoundSql/opaque descriptor editing
// or manually supplied aggregate logical rows occur in these binding controls.
void joined_nullable_binding() {
  const auto program = compile("SELECT a.id,a.g,COUNT(*),COUNT(b.y),SUM(b.y),AVG(b.y),SUM(1) "
      "FROM r a JOIN s b ON a.id=b.id WHERE a.flag GROUP BY a.id,a.g");
  assert(program.inputs().size() == 3 && program.reference_columns().size() == 7);
  assert(program.source_program().occurrences().size() == 2 && program.source_program().outputs().size() == 7);
  assert(program.native_fields() == program.source_program().export_core().query.head.size());
  assert(program.source_program().semantics() == SqlSemantics::bag && program.source_program().wrapper() == SqlWrapper::rows);
  assert(program.source_program().source() != program.original_sql() && !program.static_source_weight());
  const auto& kernel = program.kernel_program();
  assert(kernel.has_input() && kernel.input_types().size() == 3 && kernel.group_columns().size() == 2);
  assert(kernel.measures().size() == 2 && kernel.measures()[0].sum && kernel.measures()[1].int64_sum);
  assert(kernel.outputs()[0].name == "id" && kernel.outputs()[1].name == "g" && kernel.outputs()[4].name == "sum");
  for (std::size_t i = 0; i < program.inputs().size(); ++i) {
    const auto& input = program.inputs()[i]; const auto& actual = program.source_program().outputs()[input.source_output];
    assert(input.type == actual.type && input.type == kernel.input_types()[i]);
    if (const auto* field = std::get_if<SqlRowsResultField>(&input.value)) {
      const auto& expected = std::get<SqlRowsResultField>(actual.value);
      assert(field->payload == expected.payload && field->presence == expected.presence);
    }
  }
  const auto value = std::get<SqlRowsResultField>(program.inputs()[2].value);
  assert(program.inputs()[2].type.nullable && value.presence);
  const auto rebound = bind_sql_rows(program.source_program().source(), schema());
  assert(std::get<SqlRowsProgram>(rebound).source_sha256() == program.source_program().source_sha256());
}

void aliases_names_and_identity() {
  const std::string sql = "SELECT x,COUNT(x),SUM(r.x),AVG(x) FROM r GROUP BY r.x";
  const auto a = compile(sql), b = compile(sql), comment = compile(sql + " /* retained original */");
  assert(a.inputs().size() == 1 && a.reference_columns().size() == 5 && a.kernel_program().measures().size() == 1);
  for (const auto column : a.reference_columns()) assert(column == 0);
  assert(a.kernel_program().outputs()[0].name == "x");
  assert(a.identity().binding == b.identity().binding && a.identity().decode == b.identity().decode);
  assert(a.identity().original_sql != comment.identity().original_sql && a.identity().binding != comment.identity().binding);
  assert(a.identity().source == comment.identity().source && a.identity().kernel == comment.identity().kernel);
  SqlAggregateBindOptions scale; scale.kernel.average_scale = 0;
  const auto rounded = compile(sql, schema(), scale);
  assert(a.identity().source == rounded.identity().source && a.identity().kernel != rounded.identity().kernel);
  auto changed = schema(); ++changed.tables[0].source_schema_version;
  const auto revised = compile(sql, changed);
  assert(a.identity().catalog != revised.identity().catalog && a.identity().binding != revised.identity().binding);
  const Catalog quoted{1, {{"r", {{"odd name", ScalarType::string, true}}}}};
  const auto named = compile("SELECT \"r\".\"odd name\",COUNT(*) AS total FROM \"r\" GROUP BY \"odd name\"", quoted);
  assert(named.inputs().size() == 1 && named.kernel_program().outputs()[0].name == "odd name" &&
      named.kernel_program().outputs()[1].name == "total");
}

// Equal values from WHERE/JOIN/NULL normalization are not SQL grouping identity.
// Every case enters the genuine public SQL factory; no descriptors are edited.
void grouping_origin_controls() {
  reject("SELECT x,COUNT(*) FROM r WHERE x=id GROUP BY id", "ungrouped_column");
  reject("SELECT x,COUNT(*) FROM r WHERE x IS NULL AND id IS NULL GROUP BY id", "ungrouped_column");
  reject("SELECT a.x,COUNT(*) FROM r a JOIN r b ON a.x=b.x GROUP BY b.x", "ungrouped_column");
  const auto alias = compile("SELECT x,COUNT(*) FROM r GROUP BY r.x");
  assert(alias.inputs().size() == 1 && alias.inputs()[0].origin.occurrence == OccurrenceId{0} &&
      alias.inputs()[0].origin.column == ColumnId{2});
  const auto equal = compile("SELECT id,x,COUNT(*) FROM r WHERE x=id GROUP BY id,x");
  assert(equal.inputs().size() == 2 && equal.kernel_program().group_columns().size() == 2 && equal.native_fields() == 1);
  assert(equal.inputs()[0].origin.column != equal.inputs()[1].origin.column);
  const auto left = std::get<SqlRowsResultField>(equal.inputs()[0].value);
  const auto right = std::get<SqlRowsResultField>(equal.inputs()[1].value);
  assert(left.payload == right.payload && left.presence == right.presence);
  const auto nulls = compile("SELECT id,x,COUNT(*) FROM r WHERE x IS NULL AND id IS NULL GROUP BY id,x");
  assert(nulls.inputs().size() == 2 && nulls.kernel_program().group_columns().size() == 2 && nulls.native_fields() == 0);
  assert(std::get<ExpressionId>(nulls.inputs()[0].value) == std::get<ExpressionId>(nulls.inputs()[1].value));
  const auto self = compile("SELECT a.x,b.x,COUNT(*) FROM r a JOIN r b ON a.x=b.x GROUP BY a.x,b.x");
  assert(self.inputs().size() == 2 && self.inputs()[0].origin.occurrence != self.inputs()[1].origin.occurrence);
  assert(self.kernel_program().group_columns().size() == 2 && self.native_fields() == 1);
  reject("SELECT x,COUNT(*) FROM r a JOIN r b USING(x) GROUP BY x", "unsupported_aggregate_join_column");
  reject("SELECT x,COUNT(*) FROM r a NATURAL JOIN r b GROUP BY x", "unsupported_aggregate_join_column");
  const auto qualified = compile("SELECT a.x,COUNT(*) FROM r a JOIN r b USING(x) GROUP BY a.x");
  assert(qualified.inputs().size() == 1 && qualified.inputs()[0].origin.occurrence == OccurrenceId{0});
  std::string sql = "SELECT x";
  for (unsigned i = 0; i < 512; ++i) sql += ",COUNT(x) AS n" + std::to_string(i);
  const auto repeated = compile(sql + " FROM r GROUP BY r.x");
  assert(repeated.inputs().size() == 1 && repeated.reference_columns().size() == 514 && repeated.native_fields() == 2);
  for (const auto column : repeated.reference_columns()) assert(column == 0);
}

void count_star_constants_and_bootstrap() {
  const auto count = compile("SELECT COUNT(*) FROM r");
  assert(count.inputs().empty() && count.source_program().outputs().empty());
  assert(count.source_program().occurrences().size() == 1 && count.source_program().export_core().query.head.empty());
  assert(count.kernel_program().has_input() && count.kernel_program().input_types().empty() && !count.static_source_weight());
  const auto constants = compile("SELECT SUM(1),COUNT(NULL),AVG(1),SUM(NULL::bigint) FROM r");
  assert(constants.inputs().empty() && constants.kernel_program().outputs()[0].type.kind == SqlKind::int64);
  assert(constants.kernel_program().measures()[0].int64_sum);
  const auto fixed = compile("SELECT x,COUNT(x) FROM r WHERE x IS NULL GROUP BY r.x");
  assert(fixed.inputs().size() == 1 && fixed.native_fields() == 0 && !fixed.static_source_weight());
  const auto slot = std::get<ExpressionId>(fixed.inputs()[0].value);
  assert(fixed.inputs()[0].type.nullable && !fixed.source_program().initial_values()[slot.value]);
  const auto singleton = compile("SELECT COUNT(*),SUM(1)");
  const auto empty = compile("SELECT COUNT(*) WHERE FALSE");
  assert(singleton.static_source_weight() == 1 && empty.static_source_weight() == 0);
  assert(singleton.source_program().occurrences().empty() && singleton.kernel_program().has_input());
  assert(empty.source_program().contradiction() && empty.kernel_program().has_input());
  // Neither kernel was implicitly loaded: the real coordinator owns the
  // authenticated static-source bootstrap and its epoch/recovery treatment.
}

// Genuine source binding keeps the raw bigint column and its origin. Only the
// kernel carries the deduplicated integer-cast guard and SQL result type.
void varying_integer_binding() {
  const auto program = compile("SELECT x,SUM(x),SUM(x::integer),AVG(x::integer),"
      "COUNT((x::integer)::bigint),SUM((x::integer)::bigint) FROM r GROUP BY x");
  assert(program.inputs().size() == 1 && program.inputs()[0].type.kind == SqlKind::int64);
  const auto& kernel = program.kernel_program();
  assert(kernel.input_types()[0].kind == SqlKind::int64 && kernel.outputs()[0].type.kind == SqlKind::int64);
  assert(kernel.checked_int32_columns().size() == 1 && kernel.checked_int32_columns()[0] == ColumnId{0});
  assert(kernel.measures().size() == 2 && !kernel.measures()[0].int64_sum && kernel.measures()[1].int64_sum);
  assert(kernel.outputs()[1].type.kind == SqlKind::decimal && kernel.outputs()[2].type.kind == SqlKind::int64);
  assert(kernel.outputs()[5].type.kind == SqlKind::decimal);
  const auto rebound = compile(program.original_sql());
  assert(program.identity().binding == rebound.identity().binding && program.binding_image() == rebound.binding_image());
}

void parameters_and_rejections() {
  SqlAggregateBindOptions options;
  options.source.binding.parameters = {{"p", ScalarType::int64, true}};
  options.source.parameters = {Value{std::int64_t{5}}};
  const auto first = compile("SELECT COUNT(*) FROM r WHERE x=$1", schema(), options);
  options.source.parameters = {Value{std::int64_t{6}}};
  const auto second = compile("SELECT COUNT(*) FROM r WHERE x=$1", schema(), options);
  assert(first.identity().original_sql == second.identity().original_sql && first.identity().kernel == second.identity().kernel);
  assert(first.identity().source != second.identity().source && first.identity().binding != second.identity().binding);
  assert(first.work().origin_binding > 0 && first.work().origin_binding == second.work().origin_binding);
  options.source.parameters.clear();
  const auto missing_value = bind_sql_aggregate("SELECT COUNT(*) FROM r WHERE x=$1", schema(), options);
  const auto& missing = std::get<BindingDiagnostic>(missing_value);
  assert(missing.diagnostic.code == "unbound_parameter" && missing.phase == "aggregate_source/parameters");
  options.source.parameters = {Value{std::int64_t{6}}};
  reject("SELECT SUM($1) FROM r", "unsupported_argument", options);
  reject("SELECT COUNT(DISTINCT x) FROM r", "unsupported_distinct_aggregate");
  reject("SELECT SUM(x::text) FROM r", "unsupported_cast");
  reject("SELECT SUM(r.x+s.y) FROM r JOIN s ON r.id=s.id", "unsupported_expression");
  reject("SELECT COUNT(*) FROM r LEFT JOIN s ON r.id=s.id", "unsupported_join");
  reject("SELECT DISTINCT COUNT(*) FROM r", "unsupported_sql");
  reject("SELECT COUNT(*) FROM r HAVING COUNT(*)>0", "unsupported_sql");
  reject("SELECT COUNT(*) FILTER (WHERE flag) FROM r", "unsupported_sql");
  reject("SELECT COUNT(*) OVER () FROM r", "unsupported_sql");
  reject("SELECT COUNT(*) FROM r ORDER BY 1", "unsupported_sql");
  reject("SELECT COUNT(*) FROM r GROUP BY 1", "unsupported_expression");
  const auto rejected = bind_sql_aggregate("SELECT SUM(x::text) FROM r", schema());
  const auto& diagnostic = std::get<BindingDiagnostic>(rejected);
  assert(diagnostic.phase.starts_with("aggregate_kernel/") && !diagnostic.diagnostic.byte_offset);
}

void receiver_work_and_lifetime() {
  const std::string sql = "SELECT g,COUNT(*),SUM(x),AVG(x) FROM r WHERE flag GROUP BY g";
  SqlAggregateBindOptions options; options.work_limit.reset();
  const auto calibration = resource::MemoryAccount::create(32ULL * 1024 * 1024);
  std::uint64_t work = 0;
  {
    const auto result = bind_sql_aggregate_into(calibration, sql, schema(), options);
    work = std::get<SqlAggregateProgram>(result).work().composition;
  }
  const auto peak = calibration.statistics().peak_requested_bytes; controller_only(calibration);
  const auto binding = compile(sql, schema(), options).work().origin_binding;
  for (const bool exact : {true, false}) {
    auto bounded = options; bounded.source.binding.limits.work_limit = exact ? binding : binding - 1;
    const auto result = bind_sql_aggregate(sql, schema(), bounded);
    if (exact) assert(std::get<SqlAggregateProgram>(result).work().origin_binding == binding);
    else assert(std::get<BindingDiagnostic>(result).diagnostic.code == "resource_limit");
  }
  for (const bool exact : {true, false}) {
    options.work_limit = exact ? work : work - 1;
    const auto account = resource::MemoryAccount::create(32ULL * 1024 * 1024);
    {
      const auto result = bind_sql_aggregate_into(account, sql, schema(), options);
      if (exact) assert(std::get<SqlAggregateProgram>(result).work().composition == work);
      else assert(std::get<BindingDiagnostic>(result).diagnostic.code == "resource_limit");
    }
    controller_only(account);
  }
  options.work_limit.reset();
  for (const bool exact : {true, false}) {
    const auto account = resource::MemoryAccount::create(exact ? peak : peak - 1); bool denied = false;
    try { const auto result = bind_sql_aggregate_into(account, sql, schema(), options); assert(std::holds_alternative<SqlAggregateProgram>(result)); }
    catch (const resource::MemoryFailure& failure) { assert(failure.fault() == resource::MemoryFault::limit); denied = true; }
    assert(denied != exact); controller_only(account);
  }
  const auto account = resource::MemoryAccount::create(32ULL * 1024 * 1024);
  SqlAggregateProgram held;
  {
    auto mutable_sql = sql; auto catalog = schema();
    held = std::get<SqlAggregateProgram>(bind_sql_aggregate_into(account, mutable_sql, catalog, options));
    mutable_sql.assign(1000, 'z'); catalog.tables.clear();
  }
  assert(held.original_sql() == sql && held.kernel_program().outputs()[0].name == "g");
  assert(!held.binding_image().empty() && held.inputs()[0].type.kind == SqlKind::string);
  held = {}; controller_only(account);
}
}  // namespace
int main() {
  try {
    joined_nullable_binding(); aliases_names_and_identity(); grouping_origin_controls();
    count_star_constants_and_bootstrap(); varying_integer_binding();
    parameters_and_rejections(); receiver_work_and_lifetime();
    std::cout << "SQL aggregate binding: authentic source/kernel factories, physical grouping origins, checked decode and explicit bootstrap passed\n";
    return 0;
  } catch (const std::exception& failure) { std::cerr << failure.what() << '\n'; return 1; }
}
