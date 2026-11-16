#include "crown/frontend/sql_rows.hpp"
#include "crown/frontend/normalize.hpp"
#include "crown/api/error.hpp"
#include "sql_rows_eval.hpp"
#include "index_allocation.hpp"
#include <array>
#include <cassert>
#include <iostream>

namespace {
using namespace crown;
using namespace crown::frontend;
Catalog schema() {
  return {1, {{"r", {{"a", ScalarType::int64, true}, {"b", ScalarType::int64, true},
      {"s", ScalarType::string, true}, {"unused", ScalarType::date, true}}},
      {"t", {{"x", ScalarType::int64, true}}}}};
}
SqlRowsProgram compile_rows(std::string_view sql, const Catalog& catalog = schema(), const SqlRowsBindOptions& options = {}) {
  auto result = bind_sql_rows(sql, catalog, options);
  if (const auto* failure = std::get_if<BindingDiagnostic>(&result)) throw Error(failure->diagnostic.code, failure->diagnostic.message);
  return std::get<SqlRowsProgram>(std::move(result));
}
bool adapt(const SqlRowsProgram& program, std::size_t occurrence, std::span<const SqlRowCell> input,
    std::vector<storage::ScalarView>& output) {
  const auto& plan = program.occurrences()[occurrence];
  std::vector<SqlRowCell> scratch(program.initial_values().begin(), program.initial_values().end());
  output.resize(plan.projection.size()); bool admitted = false; std::size_t calls = 0;
  {
    s04_alloc::Scope deny(0);
    admitted = rows_detail::adapt(program, plan, input, scratch, output); calls = s04_alloc::calls;
  }
  assert(calls == 0);
  for (const auto& read : plan.inputs) assert(!scratch[read.target.value]);
  for (const auto& operation : plan.operations) assert(!scratch[operation.target.value]);
  return admitted;
}
void nullable_outputs() {
  const auto program = compile_rows("SELECT a, a, s, NULL::bigint AS n, a = b AS eq FROM r");
  assert(program.semantics() == SqlSemantics::bag && program.sources()[0].columns.size() == 4);
  const auto core = program.export_core(); assert(core.query.head.size() == 6);
  assert(program.outputs().size() == 5 && std::get<SqlRowsResultField>(program.outputs()[0].value).payload ==
      std::get<SqlRowsResultField>(program.outputs()[1].value).payload);
  std::array<SqlRowCell, 4> row{}; std::vector<storage::ScalarView> projected;
  assert(adapt(program, 0, row, projected));
  for (const auto& field : program.occurrences()[0].projection) {
    const auto position = static_cast<std::size_t>(&field - program.occurrences()[0].projection.data());
    if (field.kind == SqlRowsFieldKind::presence) assert(!std::get<bool>(projected[position]));
  }
  const std::string text(256, 'x'); row[0] = storage::ScalarView{std::int64_t{7}};
  row[1] = storage::ScalarView{std::int64_t{7}}; row[2] = storage::ScalarView{std::string_view(text)};
  assert(adapt(program, 0, row, projected));
  bool borrowed = false;
  for (const auto& value : projected) if (const auto* s = std::get_if<std::string_view>(&value); s && *s == text)
    borrowed = s->data() == text.data();
  assert(borrowed);
  const auto set = compile_rows("SELECT DISTINCT a FROM r"); assert(set.semantics() == SqlSemantics::set);
  const auto old = bind_sql("SELECT a FROM r", schema());
  assert(std::get<BindingDiagnostic>(normalize_sql(std::get<BoundSql>(old))).diagnostic.code == "unsupported_semantics");
}
void guards_and_grounding() {
  const auto local = compile_rows("SELECT 1 FROM r WHERE a = b");
  assert(local.export_core().query.variables.empty() && local.occurrences()[0].projection.empty());
  const auto joined = compile_rows("SELECT r.a FROM r JOIN t ON r.a = t.x AND r.b = t.x");
  assert(joined.export_core().query.variables.size() == 1);
  assert(joined.occurrences()[0].equal_columns.size() == 1);
  std::array<SqlRowCell, 4> row{}; std::vector<storage::ScalarView> projected;
  assert(!adapt(joined, 0, row, projected));
  row[0] = storage::ScalarView{std::int64_t{3}}; row[1] = storage::ScalarView{std::int64_t{4}};
  assert(!adapt(joined, 0, row, projected)); row[1] = row[0]; assert(adapt(joined, 0, row, projected));
  const auto nulls = compile_rows("SELECT a, a IS NULL FROM r WHERE a IS NULL");
  assert(nulls.export_core().query.head.empty()); row[0].reset(); assert(adapt(nulls, 0, row, projected));
  row[0] = storage::ScalarView{std::int64_t{1}}; assert(!adapt(nulls, 0, row, projected));
  const auto fixed = compile_rows("SELECT a, a > 0 FROM r WHERE a = 7"); assert(fixed.export_core().query.head.empty());
  row[0] = storage::ScalarView{std::int64_t{7}}; assert(adapt(fixed, 0, row, projected));
  assert(compile_rows("SELECT a FROM r WHERE a = NULL").contradiction());
  assert(compile_rows("SELECT a FROM r WHERE a IS NULL AND a IS NOT NULL").contradiction());
  assert(compile_rows("SELECT a FROM r WHERE a = 1 AND a = 2").contradiction());
  const auto unsupported = bind_sql_rows("SELECT r.a FROM r, t WHERE r.a > t.x", schema());
  assert(std::get<BindingDiagnostic>(unsupported).diagnostic.code == "unsupported_cross_relation_predicate");
}
void constants_parameters_and_receivers() {
  const auto scalar = compile_rows("SELECT NULL::text, TRUE, DATE '2024-02-29'");
  assert(scalar.occurrences().empty() && scalar.outputs().size() == 3);
  const auto exists = compile_rows("SELECT EXISTS(SELECT FROM r WHERE a IS NULL) AS answer");
  assert(exists.wrapper() == SqlWrapper::exists && std::holds_alternative<SqlRowsExistsOutput>(exists.outputs()[0].value));
  SqlRowsBindOptions options; options.binding.parameters = {{"p", ScalarType::int64, true}};
  options.parameters = {Value{std::int64_t{5}}};
  const auto program = compile_rows("SELECT a, $1 FROM r WHERE a = $1", schema(), options);
  const auto source_before = program.account().statistics(); const auto receiver = resource::MemoryAccount::create(4ULL * 1024 * 1024);
  const auto owned = SqlRowsProgram::freeze(receiver, program);
  assert(owned.source_sha256() == program.source_sha256() && owned.account().statistics().owner == receiver.statistics().owner);
  assert(program.account().statistics() == source_before);
  assert(owned.export_core().query.head.empty());
  std::size_t calls = 0;
  {s04_alloc::Scope deny(0); const auto alias = SqlRowsProgram::freeze(receiver, owned); calls = s04_alloc::calls; assert(alias.source_sha256() == owned.source_sha256());}
  assert(calls == 0);
  options.parameters = {std::nullopt}; const auto null_parameter = compile_rows("SELECT $1", schema(), options);
  assert(null_parameter.source_sha256() != program.source_sha256());
  SqlRowsBindOptions missing; missing.binding = options.binding;
  const auto invalid = bind_sql_rows("SELECT $1", schema(), missing);
  assert(std::get<BindingDiagnostic>(invalid).diagnostic.code == "unbound_parameter");
}
void constraint_metadata() {
  auto catalog = schema();
  catalog.tables[0].constraints.push_back(UniqueConstraint{"ab", {ColumnId{1}, ColumnId{0}}, ConstraintStatus::enforced});
  catalog.tables[1].columns.push_back({"y", ScalarType::int64, true});
  catalog.tables[1].constraints.push_back(ForeignKeyConstraint{"fk", {ColumnId{0}, ColumnId{1}}, TableId{0},
      {ColumnId{1}, ColumnId{0}}, ConstraintStatus::enforced});
  const auto program = compile_rows("SELECT a FROM r", catalog); const auto keys = program.constraints();
  assert(keys.size() == 2 && !keys[0].parent && keys[1].parent == 0);
  assert(keys[0].columns[0] == ColumnId{0} && keys[1].columns[0] == ColumnId{1});
  assert(keys[0].referenced_by.size() == 1 && keys[0].referenced_by[0] == 1);
  assert(program.sources()[1].occurrences.empty() && program.sources()[1].constraints.size() == 1);
}
void clone_release_and_failure_borrows() {
  const Catalog catalog{1, {{"r", {{"s", ScalarType::string, true}}}}};
  const auto source = resource::MemoryAccount::create(4ULL * 1024 * 1024);
  const auto receiver = resource::MemoryAccount::create(4ULL * 1024 * 1024);
  const std::string text(256, 'p'); SqlRowsProgram clone;
  {
    SqlRowsBindOptions options; options.binding.parameters = {{"p", ScalarType::string, true}};
    options.parameters = {Value{text}};
    auto result = bind_sql_rows_into(source, "SELECT s AS label, $1 AS literal, s = $1 AS eq FROM r WHERE s = $1", catalog, options);
    clone = SqlRowsProgram::freeze(receiver, std::get<SqlRowsProgram>(result));
  }
  assert(source.statistics().current.requested_bytes == resource::MemoryAccount::control_bytes());
  assert(clone.sources()[0].name == "r" && clone.sources()[0].columns[0].name == "s");
  assert(clone.outputs()[0].name == "label" && clone.outputs()[1].name == "literal");
  for (std::size_t i = 0; i < 2; ++i) {
    const auto id = std::get<ExpressionId>(clone.outputs()[i].value);
    assert(std::get<std::string_view>(*clone.initial_values()[id.value]) == text);
  }
  const auto equal = std::get<ExpressionId>(clone.outputs()[2].value);
  assert(std::get<bool>(*clone.initial_values()[equal.value]));
  std::vector<storage::ScalarView> output;
  const std::array<SqlRowCell, 1> row{storage::ScalarView{std::string_view(text)}};
  assert(adapt(clone, 0, row, output) && output.empty());

  const auto dynamic = compile_rows("SELECT s, s = s FROM r WHERE s <> ''", catalog);
  const auto& occurrence = dynamic.occurrences()[0];
  std::vector<SqlRowCell> scratch(dynamic.initial_values().begin(), dynamic.initial_values().end());
  output.resize(occurrence.projection.size());
  storage::IndexWorkAllowance work({1000000, 0, 0, 0, 0}, true);
  bool failed = false; std::size_t calls = 0;
  { s04_alloc::Scope deny(0);
    try { static_cast<void>(rows_detail::adapt(dynamic, occurrence, row, scratch, output, &work)); }
    catch (const storage::IndexFailure& error) { assert(error.code() == "storage_work_limit"); failed = true; }
    calls = s04_alloc::calls;
  }
  assert(failed && calls == 0 && work.remaining().structural_steps < 1000000);
  for (const auto& input : occurrence.inputs) assert(!scratch[input.target.value]);
  for (const auto& operation : occurrence.operations) assert(!scratch[operation.target.value]);

  SqlRowsBindOptions options; options.binding.parameters = {{"p", ScalarType::int64, true}};
  options.parameters = {Value{std::int64_t{5}}};
  const auto first = compile_rows("SELECT $1", catalog, options), same = compile_rows("SELECT $1", catalog, options);
  options.parameters = {Value{std::int64_t{6}}}; const auto next = compile_rows("SELECT $1", catalog, options);
  options.parameters = {std::nullopt}; const auto null = compile_rows("SELECT $1", catalog, options);
  assert(first.source_sha256() == same.source_sha256() && first.source_sha256() != next.source_sha256());
  assert(first.source_sha256() != null.source_sha256());
  auto changed = catalog; ++changed.tables[0].source_schema_version;
  const auto revised = compile_rows("SELECT $1", changed, options);
  assert(revised.source_sha256() != null.source_sha256());
}
void retained_constant_memory() {
  const Catalog catalog{1, {{"r", {{"s", ScalarType::string, true}}}}};
  const std::string text(1U << 20, 'x');
  SqlRowsBindOptions options; options.binding.parameters = {{"p", ScalarType::string, true}};
  options.parameters = {Value{text}};
  const auto account = resource::MemoryAccount::create(3ULL * 1024 * 1024);
  const auto result = bind_sql_rows_into(account,
      "SELECT a.s,b.s,c.s,d.s FROM r a JOIN r b ON a.s=b.s JOIN r c ON a.s=c.s "
      "JOIN r d ON a.s=d.s WHERE a.s=$1", catalog, options);
  const auto& program = std::get<SqlRowsProgram>(result);
  std::size_t strings = 0, bytes = 0;
  for (const auto& value : program.initial_values()) if (value)
    if (const auto* string = std::get_if<std::string_view>(&*value)) { ++strings; bytes += string->size(); }
  assert(strings == 1 && bytes == text.size() && program.export_core().query.head.empty());
  const auto fixed = std::get<ExpressionId>(program.outputs()[0].value);
  for (const auto& output : program.outputs()) assert(std::get<ExpressionId>(output.value) == fixed);
  for (const auto& occurrence : program.occurrences())
    for (const auto& guard : occurrence.constant_columns) assert(guard.constant == fixed);
  assert(account.statistics().peak_requested_bytes < 2ULL * 1024 * 1024);
}
}  // namespace
int main() {
  try {
    nullable_outputs(); guards_and_grounding(); constants_parameters_and_receivers(); constraint_metadata();
    clone_release_and_failure_borrows();
    retained_constant_memory();
    std::cout << "SQL rows compiler: nullable head encoding, guards, constants, aliases, native clone and exact source identity passed\n";
  } catch (const std::exception& failure) { std::cerr << failure.what() << '\n'; return 1; }
}
