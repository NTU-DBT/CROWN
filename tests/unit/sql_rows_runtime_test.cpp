#include "crown/runtime/sql_rows.hpp"
#include "crown/planner/oracle.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include <array>
#include <cassert>
#include <iostream>
#include <map>

namespace {
using namespace crown;
using namespace crown::runtime;
using Cell = sql_rows::Cell;
using Cells = std::vector<Cell>;
using Row = aggregate::Row;
using Bag = std::map<Row, std::uint64_t>;
Cell n(std::int64_t value) { return storage::ScalarView{value}; }
Cell s(std::string_view value) { return storage::ScalarView{value}; }
Value v(std::int64_t value) { return value; }
frontend::SqlRowsProgram compile_rows(std::string_view sql, const Catalog& catalog) {
  auto result = frontend::bind_sql_rows(sql, catalog);
  if (const auto* error = std::get_if<frontend::BindingDiagnostic>(&result))
    throw Error(error->diagnostic.code, error->diagnostic.message);
  return std::get<frontend::SqlRowsProgram>(std::move(result));
}
FreeConnexTree tree_for(const frontend::SqlRowsProgram& program) {
  if (program.contradiction()) return {};
  const auto core = program.export_core();
  const auto result = planner::minimum_tree(core.catalog, core.query);
  assert(result.status == planner::OracleStatus::proven_minimum && result.tree);
  return *result.tree;
}
SqlRowsRuntime create(const frontend::SqlRowsProgram& program, bool indexed, sql_rows::Options options = {}) {
  return SqlRowsRuntime(program, tree_for(program), indexed ? s04_runtime::options() : PhysicalOptions{}, options);
}
Bag drain(SqlRowsRuntime::ResultCursor& cursor) {
  Bag result;
  while (const auto row = cursor.next()) {
    const auto [item, fresh] = result.emplace(row->tuple.export_values(), row->multiplicity);
    static_cast<void>(item); assert(fresh); // Compressed output must already be unique.
  }
  return result;
}
Bag results(const SqlRowsRuntime& runtime) { auto cursor = runtime.results(); return drain(cursor); }
sql_rows::Epoch replace(SqlRowsRuntime& runtime, std::size_t source, const Cells& row,
    std::uint64_t before, std::uint64_t after) {
  return runtime.apply({runtime.sequence() + 1, TableId{source}, row, before, after});
}
template<class Action> void error(Action action, std::string_view expected) {
  try { action(); } catch (const Error& failure) { assert(failure.code() == expected); return; }
  assert(false);
}
Catalog rows_schema() {
  return {1, {{"r", {{"x", ScalarType::int64, true}, {"s", ScalarType::string, true}}}}};
}

// Full rows differing only in hidden columns contribute to the same native
// row; changing one source share must preserve all the other shares.
void projection_and_nulls(bool indexed) {
  const auto catalog = rows_schema();
  auto bag = create(compile_rows("SELECT x, x, NULL::text AS k FROM r", catalog), indexed);
  const Cells a{n(0), s("a")}, b{n(0), s("b")}, null{Cell{}, s("a")};
  assert(replace(bag, 0, a, 0, 2).changed); replace(bag, 0, b, 0, 3); replace(bag, 0, null, 0, 7);
  assert((results(bag) == Bag{{Row{v(0), v(0), std::nullopt}, 5},
      {Row{std::nullopt, std::nullopt, std::nullopt}, 7}}));
  replace(bag, 0, a, 2, 1); assert(bag.source_weight(TableId{0}, b) == 3);
  assert((results(bag).at(Row{v(0), v(0), std::nullopt}) == 4));
  error([&] { replace(bag, 0, b, 2, 1); }, "sql_rows_weight_mismatch");
  assert(bag.sequence() == 4 && bag.ready());
  auto distinct = create(compile_rows("SELECT DISTINCT x FROM r", catalog), indexed);
  replace(distinct, 0, a, 0, 2); replace(distinct, 0, b, 0, 3); replace(distinct, 0, null, 0, 7);
  assert((results(distinct) == Bag{{Row{v(0)}, 1}, {Row{std::nullopt}, 1}}));
  auto filtered = create(compile_rows("SELECT x FROM r WHERE x > 0", catalog), indexed);
  const auto ignored = replace(filtered, 0, a, 0, 8);
  assert(ignored.changed && !ignored.native.changed && ignored.native.metrics.native_inputs == 0);
  assert(filtered.source_weight(TableId{0}, a) == 8 && results(filtered).empty());
  const auto noop = replace(filtered, 0, a, 8, 8);
  assert(!noop.changed && noop.native.metrics.native_inputs == 0 && filtered.sequence() == 2);
}

void aliases_and_lifetime(bool indexed) {
  const auto program = compile_rows("SELECT a.x, a.s FROM r a JOIN r b ON a.x = b.x", rows_schema());
  auto runtime = create(program, indexed);
  std::string original(256, 'q'); const auto old = original;
  const Cells a{n(7), s(original)}, b{n(7), s("")}, null{Cell{}, s("null")};
  replace(runtime, 0, a, 0, 2); replace(runtime, 0, b, 0, 3); replace(runtime, 0, null, 0, 11);
  assert(runtime.root_weight().value == 25);
  assert((results(runtime) == Bag{{Row{v(7), Value{old}}, 10}, {Row{v(7), Value{std::string{}}}, 15}}));
  original.assign(256, 'z');
  const Cells old_row{n(7), s(old)}; assert(runtime.source_weight(TableId{0}, old_row) == 2);
  auto first = runtime.results(), second = runtime.results();
  error([&] { replace(runtime, 0, b, 3, 3); }, "runtime_busy");
  const auto retained = first.next(); assert(retained);
  const auto retained_values = retained->tuple.export_values(); first.cancel();
  assert(!runtime.ready()); second.cancel(); assert(runtime.ready());
  replace(runtime, 0, old_row, 2, 0); assert(retained->tuple.export_values() == retained_values);
  auto cursor = runtime.results(); const auto last = cursor.next(); assert(last && !runtime.ready());
  assert(!cursor.next() && runtime.ready());
  assert(last->tuple.export_values() == Row({v(7), Value{std::string{}}}));
}

void constants_exists_and_types(bool indexed) {
  for (const bool present : {false, true}) {
    auto runtime = create(compile_rows(present ? "SELECT NULL::text, TRUE" : "SELECT NULL::text, TRUE WHERE FALSE", {}), indexed);
    assert((results(runtime) == (present ? Bag{{Row{std::nullopt, Value{true}}, 1}} : Bag{})));
  }
  auto exists = create(compile_rows("SELECT EXISTS(SELECT FROM r WHERE x IS NULL)", rows_schema()), indexed);
  assert((results(exists) == Bag{{Row{Value{false}}, 1}}));
  const Cells null{Cell{}, s("")}; replace(exists, 0, null, 0, 9);
  assert((results(exists) == Bag{{Row{Value{true}}, 1}}));
  auto empty = create(compile_rows("SELECT x FROM r WHERE x = NULL", rows_schema()), indexed);
  const Cells row{n(1), s("kept")}; replace(empty, 0, row, 0, 5);
  assert(empty.source_weight(TableId{0}, row) == 5 && results(empty).empty());
  const Catalog typed{1, {{"t", {{"b", ScalarType::boolean, true}, {"d", ScalarType::date, true},
      {"n", ScalarType::decimal, true}, {"s", ScalarType::string, true}}}}};
  auto native = create(compile_rows("SELECT b, d, n, s FROM t", typed), indexed);
  const auto date = Date::parse("2024-02-29");
  const auto large = storage::InlineDecimal::parse("99999999999999999999999999999999999999");
  const auto tiny = storage::InlineDecimal::parse("0.00000000000000000000000000000000000001");
  const Cells wide{storage::ScalarView{false}, storage::ScalarView{date}, storage::ScalarView{large}, s("")};
  const Cells small{storage::ScalarView{true}, Cell{}, storage::ScalarView{tiny}, Cell{}};
  replace(native, 0, wide, 0, 2); replace(native, 0, small, 0, 3);
  assert(results(native).size() == 2 && native.root_weight().value == 5);
  const std::string nul("a\0b", 3), invalid("\xc0\x80", 2);
  for (const auto& text : {nul, invalid}) {
    auto bad = wide; bad[3] = s(text);
    error([&] { replace(native, 0, bad, 0, 1); }, "invalid_sql_rows_row");
  }
  assert(native.sequence() == 2 && native.ready());
}

void constraints(bool indexed) {
  Catalog catalog{1, {{"p", {{"id", ScalarType::int64, true}}}, {"c", {{"pid", ScalarType::int64, true}}}}};
  catalog.tables[0].constraints.push_back(UniqueConstraint{"pk", {ColumnId{0}}, ConstraintStatus::enforced});
  catalog.tables[1].constraints.push_back(ForeignKeyConstraint{"fk", {ColumnId{0}}, TableId{0}, {ColumnId{0}}, ConstraintStatus::enforced});
  auto runtime = create(compile_rows("SELECT pid FROM c", catalog), indexed);
  const Cells one{n(1)}, null{Cell{}};
  error([&] { replace(runtime, 1, one, 0, 3); }, "foreign_key_violation");
  assert(runtime.sequence() == 0 && runtime.source_weight(TableId{1}, one) == 0);
  replace(runtime, 0, one, 0, 1); replace(runtime, 1, one, 0, 9);
  replace(runtime, 1, one, 9, 100); // A weight change still represents one live FK row.
  error([&] { replace(runtime, 0, one, 1, 2); }, "unique_violation");
  error([&] { replace(runtime, 0, one, 1, 0); }, "foreign_key_violation");
  replace(runtime, 0, null, 0, 5); replace(runtime, 1, null, 0, 7);
  replace(runtime, 1, one, 100, 0); replace(runtime, 0, one, 1, 0);
  assert((results(runtime) == Bag{{Row{std::nullopt}, 7}}));

  Catalog self{1, {{"node", {{"id", ScalarType::int64}, {"parent", ScalarType::int64, true}}}}};
  self.tables[0].constraints = {UniqueConstraint{"pk", {ColumnId{0}}, ConstraintStatus::enforced},
      ForeignKeyConstraint{"self", {ColumnId{1}}, TableId{0}, {ColumnId{0}}, ConstraintStatus::enforced}};
  auto nodes = create(compile_rows("SELECT id FROM node", self), indexed);
  const Cells loop{n(1), n(1)}, root{n(1), Cell{}}, child{n(2), n(1)};
  replace(nodes, 0, loop, 0, 1); replace(nodes, 0, loop, 1, 0);
  replace(nodes, 0, root, 0, 1); replace(nodes, 0, child, 0, 1);
  error([&] { replace(nodes, 0, root, 1, 0); }, "foreign_key_violation");
  replace(nodes, 0, child, 1, 0); replace(nodes, 0, root, 1, 0); assert(results(nodes).empty());

  // Empty local key lists are the existing catalog extension: UNIQUE means
  // at most one physical row; FK means a parent must exist even for NULL cells.
  catalog.tables[0].constraints = {UniqueConstraint{"unit", {}, ConstraintStatus::enforced}};
  catalog.tables[1].constraints = {ForeignKeyConstraint{"unit_fk", {}, TableId{0}, {}, ConstraintStatus::enforced}};
  auto unit = create(compile_rows("SELECT pid FROM c", catalog), indexed);
  error([&] { replace(unit, 1, null, 0, 1); }, "foreign_key_violation");
  replace(unit, 0, null, 0, 1); replace(unit, 1, null, 0, 1);
  error([&] { replace(unit, 0, one, 0, 1); }, "unique_violation");
  error([&] { replace(unit, 0, null, 1, 0); }, "foreign_key_violation");
}

// Fail every allocation in a two-alias insertion, including after the first
// alias has changed tentative state. Retry verifies source and native rollback.
void allocation_failures(bool indexed, bool capture) {
  const auto program = compile_rows("SELECT a.x, a.s FROM r a JOIN r b ON a.x = b.x", rows_schema());
  sql_rows::Options options; options.native.capture_changes = capture;
  const Cells old{n(7), s("old")}, added{n(7), s("new")};
  std::size_t calls = 0;
  {
    auto runtime = create(program, indexed, options); replace(runtime, 0, old, 0, 2);
    { s04_alloc::Scope measure; replace(runtime, 0, added, 0, 3); calls = s04_alloc::calls; }
    assert(runtime.root_weight().value == 25);
  }
  for (std::size_t cut = 0; cut < calls; ++cut) {
    auto runtime = create(program, indexed, options); replace(runtime, 0, old, 0, 2);
    bool failed = false;
    { s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(cut));
      try { replace(runtime, 0, added, 0, 3); } catch (const std::bad_alloc&) { failed = true; }
    }
    assert(failed && runtime.ready() && runtime.sequence() == 1 && runtime.root_weight().value == 4);
    assert(runtime.source_weight(TableId{0}, old) == 2 && runtime.source_weight(TableId{0}, added) == 0);
    assert((results(runtime) == Bag{{Row{v(7), Value{std::string("old")}}, 4}}));
    replace(runtime, 0, added, 0, 3); assert(runtime.root_weight().value == 25);
  }
  std::cout << "SQL rows allocation cuts: indexed=" << indexed << " capture=" << capture << " count=" << calls << '\n';
}

void source_work_limits(bool indexed) {
  const auto program = compile_rows("SELECT a.x FROM r a JOIN r b ON a.x = b.x WHERE a.x > 0 AND b.x > 0", rows_schema());
  const Cells row{n(7), s(std::string_view("some bytes"))};
  auto probe = create(program, indexed); const auto epoch = replace(probe, 0, row, 0, 3);
  sql_rows::Options exact; exact.source_work_limit = epoch.source_work;
  auto accepted = create(program, indexed, exact); replace(accepted, 0, row, 0, 3);
  for (unsigned dimension = 0; dimension < 3; ++dimension) {
    auto limited = exact;
    auto& value = dimension == 0 ? limited.source_work_limit.structural_steps :
        dimension == 1 ? limited.source_work_limit.scalar_fields : limited.source_work_limit.scalar_bytes;
    assert(value); --value;
    auto rejected = create(program, indexed, limited); bool failed = false;
    try { replace(rejected, 0, row, 0, 3); }
    catch (const storage::IndexFailure& fault) { assert(fault.code() == "storage_work_limit"); failed = true; }
    assert(failed && rejected.ready() && rejected.sequence() == 0 && rejected.root_weight().value == 0);
    assert(rejected.source_weight(TableId{0}, row) == 0);
  }
}

void receiving_account_and_output_failures(bool indexed) {
  const auto program = compile_rows("SELECT x, s FROM r", rows_schema());
  const auto tree = tree_for(program);
  const auto physical = indexed ? s04_runtime::options() : PhysicalOptions{};
  const auto compiler_before = program.account().statistics();
  const std::string text(256, 'r'); const Cells row{n(7), s(text)};
  const auto exercise = [&](std::uint64_t limit) {
    auto account = resource::MemoryAccount::create(limit);
    auto sentinel = account.allocate(128);
    sql_rows::Options options; options.native.memory_limit_bytes = 1;
    auto runtime = SqlRowsRuntime::create_into(account, program, tree, physical, options);
    assert(runtime.program().account().statistics().owner == account.statistics().owner);
    assert(runtime.accounted_memory_statistics().limit_bytes == limit);
    replace(runtime, 0, row, 0, 2);
    auto cursor = runtime.results(); const auto result = cursor.next(); assert(result);
    assert(result->tuple.account().statistics().owner == account.statistics().owner);
    assert(!cursor.next()); return account.statistics().peak_requested_bytes;
  };
  const auto peak = exercise(8ULL * 1024 * 1024); assert(exercise(peak) == peak);
  bool rejected = false;
  try { static_cast<void>(exercise(peak - 1)); }
  catch (const resource::MemoryFailure& failure) { assert(failure.fault() == resource::MemoryFault::limit); rejected = true; }
  assert(rejected && program.account().statistics() == compiler_before);

  auto runtime = create(program, indexed); replace(runtime, 0, row, 0, 2);
  std::size_t calls = 0;
  { auto cursor = runtime.results();
    { s04_alloc::Scope measure; const auto result = cursor.next(); assert(result); calls = s04_alloc::calls; }
  }
  for (std::size_t cut = 0; cut < calls; ++cut) {
    auto cursor = runtime.results(); bool failed = false;
    { s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(cut));
      try { static_cast<void>(cursor.next()); } catch (const std::bad_alloc&) { failed = true; }
    }
    assert(failed && cursor.state() == weighted::CursorState::failed && runtime.ready());
    error([&] { static_cast<void>(cursor.next()); }, "invalid_cursor");
    assert(runtime.source_weight(TableId{0}, row) == 2);
  }
  // Native product overflow after one alias has changed must abort the source
  // replacement, even though the individual source weight fits its limit.
  auto aliases = create(compile_rows("SELECT a.x FROM r a JOIN r b ON a.x = b.x", rows_schema()), indexed);
  replace(aliases, 0, row, 0, 2);
  error([&] { replace(aliases, 0, row, 2, UINT64_MAX); }, "annotation_overflow");
  assert(aliases.sequence() == 1 && aliases.root_weight().value == 4 && aliases.source_weight(TableId{0}, row) == 2);
  std::cout << "SQL rows receiver peak: indexed=" << indexed << " bytes=" << peak
      << " output_allocation_cuts=" << calls << '\n';
}

void result_schema_lifetime(bool indexed) {
  const auto retained = [&] {
    auto program = compile_rows("SELECT x AS value, s AS label, NULL::numeric(10,2) AS amount FROM r", rows_schema());
    auto runtime = create(program, indexed);
    const std::string text(256, 'l'); replace(runtime, 0, Cells{n(7), s(text)}, 0, 3);
    auto cursor = runtime.results(); auto result = cursor.next(); assert(result); return std::move(*result);
  }();
  assert(retained.multiplicity == 3 && retained.tuple.size() == 3);
  const auto fields = retained.schema.outputs();
  assert(fields[0].name == "value" && fields[0].type.kind == frontend::SqlKind::int64);
  assert(fields[1].name == "label" && fields[1].type.nullable && fields[2].name == "amount");
  assert(fields[2].type.decimal == std::optional<DecimalSpec>(DecimalSpec{10, 2}));
  assert(std::get<std::string_view>(*retained.tuple.view()[1]) == std::string(256, 'l'));
  assert(retained.tuple.account().statistics().owner == retained.schema.account().statistics().owner);
}

void cursor_ownership(bool indexed) {
  const auto program = compile_rows("SELECT x, s FROM r", rows_schema());
  const Cells row{n(7), s("retained")};
  auto runtime = create(program, indexed); replace(runtime, 0, row, 0, 2);
  std::size_t calls = 0;
  { s04_alloc::Scope measure; auto cursor = runtime.results(); calls = s04_alloc::calls; }
  for (std::size_t cut = 0; cut < calls; ++cut) {
    bool failed = false;
    { s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(cut));
      try { auto cursor = runtime.results(); } catch (const std::bad_alloc&) { failed = true; }
    }
    assert(failed && runtime.ready() && runtime.sequence() == 1);
  }
  auto detached = [&] {
    auto owner = create(program, indexed); replace(owner, 0, row, 0, 3); return owner.results();
  }();
  const auto retained = detached.next(); assert(retained && retained->multiplicity == 3);
  assert(retained->tuple.export_values() == Row({v(7), Value{std::string("retained")}}));
  assert(!detached.next());
  for (const bool present : {false, true}) {
    auto exists = create(compile_rows("SELECT EXISTS(SELECT x FROM r)", rows_schema()), indexed);
    if (present) replace(exists, 0, row, 0, 2);
    auto cursor = exists.results(); const auto result = cursor.next();
    assert(result && std::get<bool>(*result->tuple.view()[0]) == present && !exists.ready());
    assert(!cursor.next() && exists.ready());
  }
  std::cout << "SQL rows cursor constructor cuts: indexed=" << indexed << " count=" << calls << '\n';
}
}  // namespace

int main() {
  try {
    for (const bool indexed : {false, true}) {
      projection_and_nulls(indexed); aliases_and_lifetime(indexed); constants_exists_and_types(indexed);
      constraints(indexed); source_work_limits(indexed); receiving_account_and_output_failures(indexed);
      result_schema_lifetime(indexed);
      cursor_ownership(indexed);
      for (const bool capture : {false, true}) allocation_failures(indexed, capture);
    }
    std::cout << "SQL physical rows: nullable bags, shared projections, aliases, constraints, leases and rollback passed\n";
  } catch (const std::exception& failure) { std::cerr << failure.what() << '\n'; return 1; }
}
