#include "crown/runtime/sql_aggregate.hpp"
#include "crown/planner/oracle.hpp"
#include "crown/api/error.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <map>
#include <optional>
#include <string>
#include <tuple>
#include <vector>

namespace {
using namespace crown;
using namespace crown::runtime;
using Cells = std::vector<sql_rows::Cell>;
using SqlRow = aggregate::Row;
using Results = std::map<SqlRow, SqlRow>; // Full group key -> output (not projected-output identity).
using Program = frontend::SqlAggregateProgram;
constexpr std::uint64_t grant = 64ULL * 1024 * 1024;
sql_rows::Cell n(std::int64_t value) { return storage::ScalarView{value}; }
sql_rows::Cell s(std::string_view value) { return storage::ScalarView{value}; }
aggregate::SqlValue v(std::int64_t value) { return Value{value}; }
aggregate::SqlValue t(std::string value) { return Value{std::move(value)}; }
aggregate::SqlValue d(std::string_view value) { return Value{Decimal::parse(value)}; }
Catalog schema() {
  return {1, {{"r", {{"id", ScalarType::int64, true}, {"g", ScalarType::string, true},
      {"x", ScalarType::int64, true}, {"flag", ScalarType::boolean}}},
      {"s", {{"id", ScalarType::int64, true}, {"y", ScalarType::int64, true}}},
      {"unused", {{"z", ScalarType::int64}}}}};
}
Cells row(sql_rows::Cell id, sql_rows::Cell group, sql_rows::Cell x, bool flag = true) {
  return {id, group, x, storage::ScalarView{flag}};
}
Program compile(std::string_view sql, const Catalog& catalog = schema(),
    const frontend::SqlAggregateBindOptions& options = {}) {
  auto bound = frontend::bind_sql_aggregate(sql, catalog, options);
  if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&bound))
    throw Error(failure->diagnostic.code, failure->diagnostic.message);
  return std::get<Program>(std::move(bound));
}
FreeConnexTree tree_for(const Program& program) {
  const auto& source = program.source_program();
  if (source.contradiction()) return {};
  const auto core = source.export_core();
  const auto result = planner::minimum_tree(core.catalog, core.query);
  if (result.status != planner::OracleStatus::proven_minimum || !result.tree)
    std::cerr << "source planner rejected original SQL: " << program.original_sql()
              << "\nderived source: " << source.source() << "\nreason: " << result.reason << "\n";
  assert(result.status == planner::OracleStatus::proven_minimum && result.tree);
  return *result.tree;
}
SqlAggregateRuntime create(const Program& program, bool indexed, sql_aggregate::Options options = {}) {
  return SqlAggregateRuntime(program, tree_for(program), indexed ? s04_runtime::options() : PhysicalOptions{}, options);
}
Results results(const SqlAggregateRuntime& runtime) {
  const auto snapshot = runtime.snapshot(); Results result;
  for (const auto& group : snapshot.groups) assert(result.emplace(group.key.export_values(), group.values.export_values()).second);
  return result;
}
sql_rows::SourceReplacement edit(std::size_t source, const Cells& values, std::uint64_t before, std::uint64_t after) {
  return {TableId{source}, values, before, after};
}
template<std::size_t N> SqlAggregateRuntime::PreparedBatch prepare(SqlAggregateRuntime& runtime,
    const std::array<sql_rows::SourceReplacement, N>& edits) {
  return runtime.prepare_batch({runtime.sequence() + 1, edits});
}
sql_aggregate::Epoch replace(SqlAggregateRuntime& runtime, std::size_t source, const Cells& values,
    std::uint64_t before, std::uint64_t after) {
  const std::array edits{edit(source, values, before, after)}; return prepare(runtime, edits).commit();
}
template<class Action> void error(Action action, std::string_view expected) {
  try { action(); } catch (const Error& failure) { assert(failure.code() == expected); return; }
  assert(false && "expected composed runtime failure");
}
void controller_only(const resource::MemoryAccount& account) {
  account.check_invariants(); assert(account.statistics().current.allocations == 1);
  assert(account.statistics().current.requested_bytes == resource::MemoryAccount::control_bytes());
}

// Physical nullable join edits, unused sources and multiple groups share one
// genuine source/native token. NULL equality does not join; NULL grouping does.
void joined_groups(bool indexed) {
  auto program = compile("SELECT a.g,COUNT(*),COUNT(b.y),SUM(b.y),AVG(b.y),SUM(1) "
      "FROM r a JOIN s b ON a.id=b.id WHERE a.flag GROUP BY a.id,a.g");
  sql_aggregate::Options options; options.capture_changes = true;
  auto runtime = create(program, indexed, options);
  const Cells a = row(n(1), s("a"), n(17)), b = row(n(2), {}, {}), filtered = row(n(3), s("hidden"), n(9), false);
  const Cells null_id = row({}, s("not joined"), n(2));
  const Cells one{n(1), n(6)}, two{n(2), {}}, null_right{{}, n(99)}, unused{n(8)};
  const std::array seed{edit(1, one, 0, 3), edit(0, a, 0, 2), edit(0, b, 0, 1), edit(1, two, 0, 4),
      edit(0, filtered, 0, 7), edit(0, null_id, 0, 11), edit(1, null_right, 0, 13), edit(2, unused, 0, 5)};
  auto pending = prepare(runtime, seed);
  assert(!runtime.ready() && runtime.sequence() == 0 && pending.preview().sequence == 1);
  assert(pending.preview().changed && pending.preview().group_changed && pending.preview().output.size() == 2);
  assert(pending.preview().metrics.row_probes == 0 && pending.preview().metrics.groups_finalized == 2);
  error([&] { static_cast<void>(runtime.snapshot()); }, "sql_aggregate_busy");
  error([&] { static_cast<void>(prepare(runtime, seed)); }, "sql_aggregate_busy");
  const auto epoch = pending.commit();
  assert(!epoch.native.bag_deltas && epoch.sequence == epoch.native.sequence && runtime.sequence() == 1 && runtime.ready());
  assert((results(runtime) == Results{{SqlRow{v(1),t("a")}, SqlRow{t("a"),v(6),v(6),d("36"),d("6"),v(6)}},
      {SqlRow{v(2),{}}, SqlRow{{},v(4),v(0),{},{},v(4)}}}));
  // Additions precede deletions publicly. The result is one final group boundary.
  const Cells moved = row(n(1), s("b"), n(17));
  const std::array swap{edit(0, moved, 0, 2), edit(0, a, 2, 0), edit(1, two, 4, 0)};
  const auto changed = prepare(runtime, swap).commit();
  assert(changed.output.size() == 3 && runtime.sequence() == 2);
  assert((results(runtime) == Results{{SqlRow{v(1),t("b")}, SqlRow{t("b"),v(6),v(6),d("36"),d("6"),v(6)}}}));
  assert(epoch.output[0].key && epoch.program.original_sql() == program.original_sql());
  const auto snapshot = results(runtime);
  const std::array ignored{edit(0, filtered, 7, 8), edit(2, unused, 5, 6)};
  const auto invisible = prepare(runtime, ignored).commit();
  assert(invisible.changed && !invisible.group_changed && invisible.output.empty() && results(runtime) == snapshot);
  assert(runtime.source_weight(TableId{2}, unused) == 6);
  const std::array<sql_rows::SourceReplacement, 0> empty{};
  const auto noop = prepare(runtime, empty).commit();
  assert(!noop.changed && !noop.group_changed && noop.output.empty() && runtime.sequence() == 4 && noop.native.sequence == 4);
}

// Distinct physical rows with identical projected values and self-join aliases
// are consolidated by the genuine source/native producer, never a second ledger.
void aliases_and_group_identity(bool indexed) {
  auto program = compile("SELECT a.g,COUNT(*),COUNT(a.x),SUM(a.x),AVG(a.x) "
      "FROM r a JOIN r b ON a.id=b.id GROUP BY a.g");
  sql_aggregate::Options options; options.capture_changes = true;
  auto runtime = create(program, indexed, options);
  const Cells a = row(n(7), s("a"), n(6)), b = row(n(7), s("b"), {});
  const std::array seed{edit(0, a, 0, 2), edit(0, b, 0, 3)};
  static_cast<void>(prepare(runtime, seed).commit());
  assert((results(runtime) == Results{{SqlRow{t("a")}, SqlRow{t("a"),v(10),v(10),d("60"),d("6")}},
      {SqlRow{t("b")}, SqlRow{t("b"),v(15),v(0),{},{}}}}));
  const std::array change{edit(0, b, 3, 5), edit(0, a, 2, 1)};
  const auto epoch = prepare(runtime, change).commit();
  assert(epoch.metrics.groups_finalized == 2 && epoch.metrics.state_fields_prepared == 2);
  assert((results(runtime) == Results{{SqlRow{t("a")}, SqlRow{t("a"),v(6),v(6),d("36"),d("6")}},
      {SqlRow{t("b")}, SqlRow{t("b"),v(30),v(0),{},{}}}}));
  for (const auto sql : {"SELECT x,COUNT(*) FROM r WHERE x=id GROUP BY id",
      "SELECT x,COUNT(*) FROM r WHERE x IS NULL AND id IS NULL GROUP BY id",
      "SELECT a.x,COUNT(*) FROM r a JOIN r b ON a.x=b.x GROUP BY b.x"}) {
    const auto rejected = frontend::bind_sql_aggregate(sql, schema());
    assert(std::get<frontend::BindingDiagnostic>(rejected).diagnostic.code == "ungrouped_column");
  }
  auto equal = create(compile("SELECT id,x,COUNT(*) FROM r WHERE x=id GROUP BY id,x"), indexed);
  const Cells same = row(n(7), s("anything"), n(7));
  static_cast<void>(replace(equal, 0, same, 0, 2));
  assert((results(equal) == Results{{SqlRow{v(7),v(7)}, SqlRow{v(7),v(7),v(2)}}}));
  auto nulls = create(compile("SELECT id,x,COUNT(*) FROM r WHERE x IS NULL AND id IS NULL GROUP BY id,x"), indexed);
  const Cells both_null = row({}, s("anything"), {});
  static_cast<void>(replace(nulls, 0, both_null, 0, 2));
  assert((results(nulls) == Results{{SqlRow{{},{}}, SqlRow{{},{},v(2)}}}));
  auto qualified = create(compile("SELECT x,COUNT(*) FROM r GROUP BY r.x"), indexed);
  static_cast<void>(replace(qualified, 0, same, 0, 1));
  assert((results(qualified) == Results{{SqlRow{v(7)}, SqlRow{v(7),v(1)}}}));
  auto hidden = create(compile("SELECT COUNT(*) FROM r GROUP BY g"), indexed, options);
  static_cast<void>(prepare(hidden, seed).commit());
  const Cells projected_duplicate = row(n(8),s("a"),n(100),false);
  const auto merged = replace(hidden,0,projected_duplicate,0,1);
  assert(merged.metrics.native_deltas == 1);
  const auto full = hidden.snapshot();
  assert(full.groups.size() == 2 && full.groups[0].key != full.groups[1].key);
  assert(full.groups[0].values == full.groups[1].values); // Equal COUNT output, distinct full group identities.
}

void global_constants_and_rounding(bool indexed) {
  const auto program = compile("SELECT COUNT(*),COUNT(x),SUM(x),AVG(x) FROM r");
  sql_aggregate::Options options; options.capture_changes = true;
  auto runtime = create(program, indexed, options);
  assert((results(runtime) == Results{{SqlRow{}, SqlRow{v(0),v(0),{},{}}}}));
  const Cells a = row(n(1), {}, n(6)), b = row(n(2), {}, n(-6)), null = row(n(3), {}, {});
  const std::array seed{edit(0,a,0,3),edit(0,b,0,3),edit(0,null,0,2)};
  static_cast<void>(prepare(runtime, seed).commit());
  assert((results(runtime) == Results{{SqlRow{}, SqlRow{v(8),v(6),d("0"),d("0")}}}));
  const std::array remove{edit(0,a,3,0),edit(0,b,3,0),edit(0,null,2,0)};
  const auto empty = prepare(runtime, remove).commit();
  assert(empty.output.size() == 1 && empty.output[0].after);
  assert((results(runtime) == Results{{SqlRow{}, SqlRow{v(0),v(0),{},{}}}}));
  auto literal = create(compile("SELECT COUNT(*),SUM(1),AVG(1),COUNT(NULL)"), indexed, options);
  assert(literal.sequence() == 0 && literal.root_weight().value == 1);
  assert((results(literal) == Results{{SqlRow{}, SqlRow{v(1),v(1),d("1"),v(0)}}}));
  const std::array<sql_rows::SourceReplacement, 0> none{};
  const auto first = prepare(literal, none).commit();
  assert(first.sequence == 1 && first.native.sequence == 1 && !first.changed && !first.group_changed && first.output.empty());
  auto never = create(compile("SELECT COUNT(*),SUM(1) WHERE false"), indexed);
  assert(never.sequence() == 0 && never.root_weight().value == 0);
  assert((results(never) == Results{{SqlRow{}, SqlRow{v(0),{}}}}));
  const auto false_epoch = prepare(never,none).commit();
  assert(false_epoch.sequence == 1 && !false_epoch.group_changed && never.root_weight().value == 0);
  auto from_empty = create(compile("SELECT COUNT(*),SUM(1) FROM r"), indexed);
  assert((results(from_empty) == Results{{SqlRow{}, SqlRow{v(0),{}}}}));
  static_cast<void>(replace(from_empty, 0, a, 0, 3));
  assert((results(from_empty) == Results{{SqlRow{}, SqlRow{v(3),v(3)}}}));
  frontend::SqlAggregateBindOptions binding; binding.kernel.average_scale = 0;
  auto rounded = create(compile("SELECT AVG(x) FROM r", schema(), binding), indexed, options);
  const Cells zero = row(n(1), {}, n(0)), one = row(n(2), {}, n(1));
  static_cast<void>(replace(rounded, 0, zero, 0, 3));
  const auto equal = replace(rounded, 0, one, 0, 1);
  assert(equal.group_changed && equal.output.empty());
  assert((results(rounded) == Results{{SqlRow{}, SqlRow{d("0")}}}));
}

void arithmetic_constraints_and_rollback(bool indexed) {
  sql_aggregate::Options options; options.capture_changes = true; options.count_limit = 5;
  const auto program = compile("SELECT g,COUNT(*),SUM(x),AVG(x) FROM r GROUP BY g");
  auto runtime = create(program, indexed, options);
  const Cells a = row(n(1), s("a"), n(INT64_MIN)), b = row(n(2), s("b"), n(INT64_MAX));
  const std::array seed{edit(0,a,0,5),edit(0,b,0,5)};
  static_cast<void>(prepare(runtime, seed).commit());
  const auto baseline = results(runtime);
  const std::array bad{edit(0,a,5,4),edit(0,b,5,6)};
  error([&] { static_cast<void>(prepare(runtime,bad)); }, "aggregate_overflow");
  assert(runtime.ready() && runtime.sequence() == 1 && results(runtime) == baseline);
  assert(runtime.source_weight(TableId{0},a) == 5 && runtime.source_weight(TableId{0},b) == 5);
  const Cells next_a = row(n(3),s("a"),n(1)), next_b = row(n(4),s("b"),n(-1));
  const std::array swap{edit(0,next_a,0,5),edit(0,next_b,0,5),edit(0,a,5,0),edit(0,b,5,0)};
  const auto swapped = prepare(runtime,swap).commit();
  assert(swapped.metrics.groups_finalized == 2 && swapped.output.size() == 2);
  assert((results(runtime) == Results{{SqlRow{t("a")}, SqlRow{t("a"),v(5),d("5"),d("1")}},
      {SqlRow{t("b")}, SqlRow{t("b"),v(5),d("-5"),d("-1")}}}));
  auto literal = create(compile("SELECT SUM(2147483647) FROM r"), indexed);
  constexpr std::uint64_t boundary = 4294967298ULL;
  static_cast<void>(replace(literal,0,a,0,boundary));
  error([&] { static_cast<void>(replace(literal,0,a,boundary,boundary+1)); }, "aggregate_overflow");
  assert(literal.sequence() == 1 && literal.source_weight(TableId{0},a) == boundary);
  assert((results(literal) == Results{{SqlRow{}, SqlRow{v(INT64_MAX-1)}}}));
  auto count = create(compile("SELECT COUNT(*) FROM r"),indexed);
  const auto unsigned_amount = (std::uint64_t{1} << 63) + 17;
  error([&] { static_cast<void>(replace(count,0,a,0,unsigned_amount)); }, "aggregate_overflow");
  assert(count.sequence() == 0 && count.source_weight(TableId{0},a) == 0 && count.root_weight().value == 0);
  auto wide = create(compile("SELECT COUNT(*),SUM(x),AVG(x) FROM r"),indexed);
  static_cast<void>(replace(wide,0,a,0,INT64_MAX));
  assert((results(wide) == Results{{SqlRow{}, SqlRow{v(INT64_MAX),
      d("-85070591730234615856620279821087277056"),d("-9223372036854775808")}}}));
  auto unique_catalog = schema();
  unique_catalog.tables[0].constraints.push_back(UniqueConstraint{"pk",{ColumnId{0}},ConstraintStatus::enforced});
  auto unique = create(compile("SELECT g,COUNT(*) FROM r GROUP BY g",unique_catalog),indexed,options);
  const Cells old_a = row(n(1),s("a"),n(1)), old_b = row(n(2),s("b"),n(1));
  const Cells new_a = row(n(2),s("a"),n(1)), new_b = row(n(1),s("b"),n(1));
  const std::array unique_seed{edit(0,old_a,0,1),edit(0,old_b,0,1)};
  static_cast<void>(prepare(unique,unique_seed).commit());
  const auto old_unique = results(unique);
  const std::array unique_swap{edit(0,new_a,0,1),edit(0,new_b,0,1),edit(0,old_a,1,0),edit(0,old_b,1,0)};
  const auto unchanged = prepare(unique,unique_swap).commit();
  assert(unchanged.changed && !unchanged.group_changed && unchanged.output.empty() && results(unique) == old_unique);
  const std::array duplicate{edit(0,new_a,1,2)};
  error([&] { static_cast<void>(prepare(unique,duplicate)); }, "unique_violation");
  assert(unique.sequence() == 2 && results(unique) == old_unique);
  Catalog catalog{1,{{"p",{{"id",ScalarType::int64,false}}},
      {"c",{{"pid",ScalarType::int64,true},{"tag",ScalarType::string,false}}}}};
  catalog.tables[0].constraints.push_back(UniqueConstraint{"pk",{ColumnId{0}},ConstraintStatus::enforced});
  catalog.tables[1].constraints.push_back(ForeignKeyConstraint{"fk",{ColumnId{0}},TableId{0},{ColumnId{0}},ConstraintStatus::enforced});
  auto constrained = create(compile("SELECT tag,COUNT(*) FROM c JOIN p ON c.pid=p.id GROUP BY tag",catalog), indexed);
  const Cells parent{n(1)},child{n(1),s("c")};
  const std::array add{edit(1,child,0,2),edit(0,parent,0,1)};
  static_cast<void>(prepare(constrained,add).commit());
  const auto old = results(constrained); const std::array remove_parent{edit(0,parent,1,0)};
  error([&] { static_cast<void>(prepare(constrained,remove_parent)); }, "foreign_key_violation");
  assert(constrained.sequence() == 1 && results(constrained) == old);
  const std::array erase{edit(0,parent,1,0),edit(1,child,2,0)};
  static_cast<void>(prepare(constrained,erase).commit()); assert(results(constrained).empty());
}

// Physical edits reach the genuine source/native batch before the shared
// integer guard. Final-only arithmetic permits signed cancellation; a refused
// cast/final sum must unwind that same token, including every source weight.
void varying_integer_batches(bool indexed) {
  constexpr std::uint64_t amount = 4294967299ULL;
  const Cells positive = row(n(1), s("same"), n(INT32_MAX));
  const Cells negative = row(n(2), s("same"), n(-INT32_MAX));
  for (const bool capture : {false, true}) {
    sql_aggregate::Options options; options.capture_changes = capture;
    auto runtime = create(compile("SELECT COUNT(*),SUM(x::integer),SUM(x) FROM r"), indexed, options);
    error([&] { static_cast<void>(replace(runtime, 0, positive, 0, amount)); }, "aggregate_overflow");
    assert(runtime.sequence() == 0 && runtime.source_weight(TableId{0}, positive) == 0);
    const std::array add{edit(0, positive, 0, amount), edit(0, negative, 0, amount)};
    const auto epoch = prepare(runtime, add).commit();
    assert(epoch.captured == capture);
    assert((results(runtime) == Results{{SqlRow{}, SqlRow{v(static_cast<std::int64_t>(2 * amount)), v(0), d("0")}}}));
    const auto baseline = results(runtime);
    error([&] { static_cast<void>(replace(runtime, 0, negative, amount, 0)); }, "aggregate_overflow");
    assert(runtime.ready() && runtime.sequence() == 1 && results(runtime) == baseline);
    assert(runtime.source_weight(TableId{0}, positive) == amount && runtime.source_weight(TableId{0}, negative) == amount);
    const std::array erase{edit(0, positive, amount, 0), edit(0, negative, amount, 0)};
    static_cast<void>(prepare(runtime, erase).commit());
    assert((results(runtime) == Results{{SqlRow{}, SqlRow{v(0), {}, {}}}}));
    assert(runtime.ready());
  }
  auto count = create(compile("SELECT COUNT((x::integer)::bigint) FROM r WHERE flag"), indexed);
  const Cells minimum = row(n(1), {}, n(INT32_MIN)), maximum = row(n(2), {}, n(INT32_MAX));
  const Cells null = row(n(3), {}, {});
  const std::array seed{edit(0, minimum, 0, 1), edit(0, maximum, 0, 1), edit(0, null, 0, 1)};
  static_cast<void>(prepare(count, seed).commit());
  assert((results(count) == Results{{SqlRow{}, SqlRow{v(2)}}}));
  for (const auto outside : {std::int64_t{INT32_MIN} - 1, std::int64_t{INT32_MAX} + 1}) {
    const Cells bad = row(n(4), {}, n(outside));
    error([&] { static_cast<void>(replace(count, 0, bad, 0, 1)); }, "aggregate_overflow");
    assert(count.ready() && count.sequence() == 1 && count.source_weight(TableId{0}, bad) == 0);
    assert((results(count) == Results{{SqlRow{}, SqlRow{v(2)}}}));
  }
  // Source rows that produce no logical fact do not evaluate aggregate casts.
  // A consolidated transient also disappears before the guard is reached.
  const Cells hidden = row(n(5), {}, n(std::int64_t{INT32_MAX} + 1), false);
  const Cells visible = row(n(5), {}, n(std::int64_t{INT32_MAX} + 1));
  static_cast<void>(replace(count, 0, hidden, 0, 1));
  const std::array activate{edit(0, hidden, 1, 0), edit(0, visible, 0, 1)};
  error([&] { static_cast<void>(prepare(count, activate)); }, "aggregate_overflow");
  assert(count.sequence() == 2 && count.source_weight(TableId{0}, hidden) == 1 && count.source_weight(TableId{0}, visible) == 0);
  const std::array transient{edit(0, visible, 0, 1), edit(0, visible, 1, 0)};
  const auto cancelled = prepare(count, transient).commit();
  assert(!cancelled.changed && !cancelled.group_changed && count.sequence() == 3);
  auto joined = create(compile("SELECT COUNT((b.y::integer)::bigint) FROM r a JOIN s b ON a.id=b.id"), indexed);
  const Cells left = row(n(7), {}, n(1)), right{n(7), n(std::int64_t{INT32_MIN} - 1)};
  static_cast<void>(replace(joined, 1, right, 0, 2));
  error([&] { static_cast<void>(replace(joined, 0, left, 0, 3)); }, "aggregate_overflow");
  assert(joined.ready() && joined.sequence() == 1 && joined.root_weight().value == 0);
  assert(joined.source_weight(TableId{1}, right) == 2 && joined.source_weight(TableId{0}, left) == 0);
  assert(joined.ready() && count.ready());
  auto average = create(compile("SELECT AVG(x::integer) FROM r"), indexed);
  static_cast<void>(replace(average, 0, positive, 0, amount));
  assert((results(average) == Results{{SqlRow{}, SqlRow{d("2147483647")}}}));
}

void allocation_failure_commit_and_lifetime(bool indexed, bool integer) {
  auto program = compile(integer ?
      "SELECT a.g,COUNT(*),SUM(a.x::integer) FROM r a JOIN r b ON a.id=b.id GROUP BY a.g" :
      "SELECT a.g,COUNT(*),SUM(a.x) FROM r a JOIN r b ON a.id=b.id GROUP BY a.g");
  sql_aggregate::Options options; options.capture_changes = true;
  const Cells a = row(n(7),s("a"),n(6)), b = row(n(7),s("b"),n(9));
  const std::array update{edit(0,b,0,3)};
  std::size_t allocations = 0;
  {
    auto runtime = create(program,indexed,options); static_cast<void>(replace(runtime,0,a,0,2));
    s04_alloc::Scope measure; auto token = prepare(runtime,update); allocations = s04_alloc::calls; token.rollback();
  }
  assert(allocations > 0 && allocations < 4096);
  for (std::size_t cut=0; cut<allocations; ++cut) {
    auto runtime = create(program,indexed,options); static_cast<void>(replace(runtime,0,a,0,2));
    const auto baseline = results(runtime); bool failed = false;
    {
      s04_alloc::Scope deny(static_cast<std::ptrdiff_t>(cut));
      try { auto token = prepare(runtime,update); token.rollback(); }
      catch (const std::bad_alloc&) { failed = true; }
      assert(s04_alloc::triggered == failed);
    }
    assert(failed && runtime.ready() && runtime.sequence() == 1 && results(runtime) == baseline);
    assert(runtime.source_weight(TableId{0},b) == 0 && runtime.root_weight().value == 4);
    static_cast<void>(prepare(runtime,update).commit()); assert(runtime.sequence() == 2);
  }
  auto runtime = create(program,indexed,options); static_cast<void>(replace(runtime,0,a,0,2));
  const auto resident = runtime.accounted_memory_statistics().current.requested_bytes;
  auto rollback = prepare(runtime,update);
  const auto pending_bytes = runtime.accounted_memory_statistics().current.requested_bytes;
  { s04_alloc::Scope deny(0); rollback.rollback(); assert(s04_alloc::calls == 0); }
  assert(!rollback.active() && runtime.accounted_memory_statistics().current.requested_bytes < pending_bytes);
  assert(runtime.accounted_memory_statistics().current.requested_bytes >= resident); // Existing native high-water capacity is honest.
  auto token = prepare(runtime,update); std::optional<sql_aggregate::Epoch> saved;
  { s04_alloc::Scope deny(0); saved.emplace(token.commit()); assert(s04_alloc::calls == 0); }
  assert(!token.active() && saved->program.original_sql() == program.original_sql());
  auto account = runtime.account(); std::optional<SqlAggregateRuntime::PreparedBatch> surviving;
  std::string dynamic(256,'q'); const auto original = dynamic; const Cells c = row(n(7),s(dynamic),n(4));
  {
    auto temporary = create(program,indexed,options); const std::array change{edit(0,c,0,2)};
    account = temporary.account(); surviving.emplace(prepare(temporary,change));
    auto moved = std::move(temporary); assert(!temporary.ready() && !moved.ready());
    dynamic.assign(256,'x'); // Full source/group/output keys already own their bytes.
  }
  assert(surviving->active());
  std::optional<sql_aggregate::Epoch> retained;
  { s04_alloc::Scope deny(0); retained.emplace(surviving->commit()); assert(s04_alloc::calls == 0); }
  assert(retained->output.size() == 1 && retained->output[0].key.export_values() == SqlRow{t(original)});
  const auto closed = account.statistics().current; surviving.reset();
  assert(account.statistics().current == closed); // Closed facade retains only an account reference.
  retained.reset(); controller_only(account);
}

void receiving_freeze_and_work(bool indexed, bool integer) {
  auto foreign = compile(integer ?
      "SELECT g,COUNT('short') AS n,COUNT('a long constant argument for rebasing') AS long_name,SUM(x::integer),AVG(x::integer) FROM r GROUP BY g" :
      "SELECT g,COUNT('short') AS n,COUNT('a long constant argument for rebasing') AS long_name,SUM(x),AVG(x) FROM r GROUP BY g");
  auto receiver = resource::MemoryAccount::create(grant);
  auto frozen = Program::freeze(receiver,foreign);
  assert(frozen.identity().binding == foreign.identity().binding && frozen.work().composition == foreign.work().composition);
  assert(frozen.account().statistics().owner == receiver.statistics().owner);
  const auto copied = receiver.statistics().successful_allocations;
  auto shared = Program::freeze(receiver,frozen); assert(receiver.statistics().successful_allocations == copied);
  assert(shared.kernel_program().checked_int32_columns().size() == (integer ? 1U : 0U));
  foreign = {}; frozen = {}; // Only receiver-backed metadata remains reachable below.
  sql_aggregate::Options options; options.capture_changes = true;
  auto runtime = SqlAggregateRuntime::create_into(receiver,shared,tree_for(shared),indexed?s04_runtime::options():PhysicalOptions{},options);
  assert(runtime.account().statistics().limit_bytes == grant && runtime.program().kernel_program().outputs()[1].name == "n");
  const Cells a = row(n(1),s("a"),n(3));
  const std::array update{edit(0,a,0,2)};
  auto token = prepare(runtime,update); const auto work = token.preview().metrics.work;
  const auto source_work = token.preview().source_work; const auto native_work = token.preview().native.metrics.work;
  assert(work > 1 && source_work.structural_steps > 0 && native_work > 0); token.rollback();
  options.group_work_limit = work-1;
  auto low = create(shared,indexed,options);
  error([&] { static_cast<void>(prepare(low,update)); }, "aggregate_work_limit");
  assert(low.ready() && low.sequence() == 0 && low.source_weight(TableId{0},a) == 0 && results(low).empty());
  options.group_work_limit = work; auto exact = create(shared,indexed,options);
  const auto epoch = prepare(exact,update).commit(); assert(epoch.metrics.work == work && epoch.metrics.row_probes == 0);
  options.group_work_limit = work;
  options.source.source_work_limit = source_work;
  --options.source.source_work_limit.structural_steps;
  auto source_low = create(shared,indexed,options);
  bool source_denied = false;
  try { static_cast<void>(prepare(source_low,update)); }
  catch (const storage::IndexFailure& failure) {
    assert(failure.code() == "storage_work_limit"); source_denied = true;
  }
  assert(source_denied);
  assert(source_low.ready() && source_low.sequence() == 0 && source_low.source_weight(TableId{0},a) == 0);
  options.source.source_work_limit = source_work;
  options.source.native.work_limit = native_work-1;
  auto native_low = create(shared,indexed,options);
  error([&] { static_cast<void>(prepare(native_low,update)); }, "resource_limit");
  assert(native_low.ready() && native_low.sequence() == 0 && native_low.source_weight(TableId{0},a) == 0);
  const auto& argument = std::get<std::optional<storage::ScalarView>>(shared.kernel_program().measures()[0].argument);
  assert(argument && std::get<std::string_view>(*argument) == "short");
  const auto tiny = resource::MemoryAccount::create(resource::MemoryAccount::control_bytes()+128);
  bool denied = false;
  try { static_cast<void>(Program::freeze(tiny,shared)); }
  catch (const resource::MemoryFailure& failure) { assert(failure.fault() == resource::MemoryFault::limit); denied = true; }
  assert(denied); controller_only(tiny);
}
}  // namespace


// Fused batches (Options::fused) against the layered path: the same random
// net batches (chains, no-ops, NULLs, filters, joins, self-joins, globals and
// rejected stale weights) give the same groups, changes, source weights and
// root weights after every batch.
void fused_matches_layered() {
  const char* programs[] = {
      "SELECT a.g,COUNT(*),COUNT(b.y),SUM(b.y),AVG(b.y) FROM r a JOIN s b ON a.id=b.id WHERE a.flag GROUP BY a.id,a.g",
      "SELECT a.g,COUNT(*),SUM(a.x) FROM r a JOIN r b ON a.id=b.id GROUP BY a.g",
      "SELECT COUNT(*),SUM(x),AVG(x) FROM r",
      "SELECT a.id,b.y,COUNT(*),SUM(a.x) FROM r a JOIN s b ON a.id=b.id GROUP BY a.id,b.y"};
  std::uint64_t state = 0x9e3779b97f4a7c15ULL;
  auto next = [&](std::uint64_t bound) { state ^= state << 13; state ^= state >> 7; state ^= state << 17; return state % bound; };
  auto cell = [&](std::int64_t low, std::int64_t high, bool nullable) -> sql_rows::Cell {
    if (nullable && next(5) == 0) return {};
    return n(low + static_cast<std::int64_t>(next(static_cast<std::uint64_t>(high - low + 1))));
  };
  auto changes = [](const sql_aggregate::Epoch& epoch) {
    std::vector<std::tuple<SqlRow, std::optional<SqlRow>, std::optional<SqlRow>>> out;
    for (const auto& change : epoch.output)
      out.emplace_back(change.key.export_values(), change.before ? std::optional{change.before->export_values()} : std::nullopt,
          change.after ? std::optional{change.after->export_values()} : std::nullopt);
    std::sort(out.begin(), out.end());
    return out;
  };
  for (const auto* sql : programs) {
    auto program = compile(sql);
    sql_aggregate::Options layered_options; layered_options.capture_changes = true;
    auto fused_options = layered_options; fused_options.fused = true;
    auto layered = create(program, false, layered_options);
    auto fused = create(program, false, fused_options);
    assert(!layered.fused() && fused.fused());
    std::map<std::pair<std::size_t, Cells>, std::uint64_t> weights;
    for (int batch = 0; batch < 400; ++batch) {
      std::vector<Cells> rows;
      std::vector<sql_rows::SourceReplacement> edits;
      const auto count = 1 + next(4);
      rows.reserve(2 * count);
      bool stale = false;
      std::map<std::pair<std::size_t, Cells>, std::uint64_t> proposed;
      for (std::uint64_t e = 0; e < count; ++e) {
        const std::size_t table = next(3) == 0 ? 1 : 0;
        Cells values = table == 0 ? row(cell(1, 3, true), next(4) == 0 ? sql_rows::Cell{} : (next(2) ? s("a") : s("b")),
                                        cell(-3, 3, true), next(4) != 0)
                                  : Cells{cell(1, 3, true), cell(1, 3, true)};
        const auto key = std::pair{table, values};
        const auto found = proposed.find(key);
        const auto current = found != proposed.end() ? found->second : (weights.contains(key) ? weights.at(key) : 0);
        auto before = current;
        if (next(25) == 0) { before = current + 1; stale = true; }
        const auto after = next(3);
        proposed[key] = after;
        rows.push_back(std::move(values));
        edits.push_back(edit(table, rows.back(), before, after));
        if (next(4) == 0) {  // chain a second edit on the same row
          const auto again = next(3);
          rows.push_back(rows.back());
          edits.push_back(edit(table, rows.back(), after, again));
          proposed[key] = again;
        }
      }
      const sql_rows::NetBatch net{layered.sequence() + 1, edits};
      std::optional<std::string> layered_error, fused_error;
      std::optional<sql_aggregate::Epoch> a, b;
      try { a.emplace(layered.prepare_batch(net).commit()); } catch (const Error& failure) { layered_error = failure.code(); }
      try { b.emplace(fused.prepare_batch(net).commit()); } catch (const Error& failure) { fused_error = failure.code(); }
      assert(layered_error == fused_error);
      assert(!stale || layered_error);
      assert(layered.sequence() == fused.sequence() && layered.ready() && fused.ready());
      if (!layered_error) {
        for (const auto& [key, after] : proposed) weights[key] = after;
        assert(a->changed == b->changed && a->group_changed == b->group_changed);
        assert(changes(*a) == changes(*b));
        assert(b->native.sequence == b->sequence);
      }
      assert(results(layered) == results(fused));
      assert(layered.root_weight().value == fused.root_weight().value);
      for (const auto& [key, weight] : weights)
        assert(layered.source_weight(TableId{key.first}, key.second) == weight &&
               fused.source_weight(TableId{key.first}, key.second) == weight);
    }
    // The source image (checkpoints) is the same on both paths.
    assert(layered.source_snapshot().source.rows.size() == fused.source_snapshot().source.rows.size());
  }
}

int main() {
  for (const auto indexed : {false,true}) {
    joined_groups(indexed); aliases_and_group_identity(indexed); global_constants_and_rounding(indexed);
    arithmetic_constraints_and_rollback(indexed); varying_integer_batches(indexed);
    for (const bool integer : {false, true}) {
      allocation_failure_commit_and_lifetime(indexed, integer); receiving_freeze_and_work(indexed, integer);
    }
  }
  fused_matches_layered();
  std::cout << "composed SQL aggregate runtime controls passed\n";
}
