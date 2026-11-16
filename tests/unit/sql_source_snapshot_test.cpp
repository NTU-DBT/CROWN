#include "crown/runtime/sql_aggregate.hpp"
#include "crown/planner/oracle.hpp"
#include "indexed_runtime_fixture.hpp"
#include "index_allocation.hpp"
#include <array>
#include <cassert>
#include <iostream>
#include <optional>
#include <string>

namespace {
using namespace crown;
using namespace crown::runtime;
using Cells = std::vector<sql_rows::Cell>;
using Row = aggregate::Row;
sql_rows::Cell n(std::int64_t x) { return storage::ScalarView{x}; }
sql_rows::Cell s(std::string_view x) { return storage::ScalarView{x}; }
Catalog catalog() {
  return {1, {{"r", {{"id", ScalarType::int64, false}, {"g", ScalarType::string, true},
      {"x", ScalarType::int64, true}, {"flag", ScalarType::boolean, true}}},
      {"t", {{"id", ScalarType::int64, false}, {"y", ScalarType::int64, true}}},
      {"unused", {{"text", ScalarType::string, true}}}}};
}
template<class Program> FreeConnexTree tree(const Program& program) {
  const auto core = program.export_core();
  const auto choice = planner::minimum_tree(core.catalog, core.query);
  assert(choice.status == planner::OracleStatus::proven_minimum && choice.tree);
  return *choice.tree;
}
auto rows_program() {
  auto binding = frontend::bind_sql_rows("SELECT g,x FROM r WHERE flag", catalog());
  assert(std::holds_alternative<frontend::SqlRowsProgram>(binding));
  return std::get<frontend::SqlRowsProgram>(std::move(binding));
}
auto aggregate_program() {
  auto binding = frontend::bind_sql_aggregate("SELECT g,COUNT(*),SUM(x) FROM r WHERE flag GROUP BY g", catalog());
  assert(std::holds_alternative<frontend::SqlAggregateProgram>(binding));
  return std::get<frontend::SqlAggregateProgram>(std::move(binding));
}
template<class Action> void error(Action action, std::string_view code) {
  bool caught = false;
  try { action(); } catch (const Error& failure) { assert(failure.code() == code); caught = true; }
  assert(caught);
}
void controller_only(const resource::MemoryAccount& account) {
  account.check_invariants(); assert(account.statistics().current.allocations == 1);
  assert(account.statistics().current.requested_bytes == resource::MemoryAccount::control_bytes());
}

// The image uses complete physical identities, including invisible columns,
// filtered rows, SQL NULLs and catalog sources absent from the query body.
void source_image(bool indexed) {
  const auto program = rows_program();
  auto runtime = SqlRowsRuntime(program, tree(program), indexed ? s04_runtime::options() : PhysicalOptions{});
  auto account = runtime.program().account();
  const auto initial = runtime.source_snapshot({.rows = 0});
  assert(initial.sequence == 0 && initial.rows.empty());
  assert(initial.native_program.physical_sha256() == std::string_view(initial.native_binding.shape_sha256.data(), 64));
  assert(initial.native_binding.multiplicity_limit == UINT64_MAX);
  const std::string original(256, 'q'); std::string text = original;
  const Cells a{n(1),s(text),n(5),storage::ScalarView{true}};
  const Cells filtered{n(2),{}, {},storage::ScalarView{false}}, hidden{n(7),{}}, unused{s("unused")};
  const std::array edits{sql_rows::SourceReplacement{TableId{2},unused,0,4},
      sql_rows::SourceReplacement{TableId{0},filtered,0,3},
      sql_rows::SourceReplacement{TableId{1},hidden,0,9},
      sql_rows::SourceReplacement{TableId{0},a,0,2}};
  {
    auto pending = runtime.prepare_batch({1, edits});
    error([&] { static_cast<void>(runtime.source_snapshot()); }, "sql_rows_busy");
    static_cast<void>(pending.commit());
  }
  text.assign(256, 'x');
  std::optional<sql_rows::SourceSnapshot> retained(runtime.source_snapshot());
  assert(retained->sequence == 1 && retained->rows.size() == 4 && runtime.root_weight().value == 2);
  assert((retained->work == storage::IndexWork{12,11,262,0,0}));
  assert(retained->program.account().statistics().owner == account.statistics().owner);
  assert(retained->native_program.account().statistics().owner == account.statistics().owner);
  assert((retained->rows[0].row.export_values() == Row{Value{std::int64_t{1}},Value{original},Value{std::int64_t{5}},Value{true}}));
  assert(retained->rows[0].source == TableId{0} && retained->rows[0].weight == 2);
  assert(retained->rows[1].source == TableId{0} && retained->rows[1].weight == 3);
  assert(retained->rows[1].row.view()[1] == std::nullopt && retained->rows[1].row.view()[2] == std::nullopt);
  assert(retained->rows[2].source == TableId{1} && retained->rows[2].weight == 9);
  assert(retained->rows[3].source == TableId{2} && retained->rows[3].weight == 4);

  // One cumulative row/field/string-extent allowance, with exact and each
  // independent one-under boundary. Failure releases incomplete output only.
  sql_rows::SourceSnapshotLimits exact{4,retained->work};
  assert(runtime.source_snapshot(exact).work == retained->work);
  auto row_limit = exact; row_limit.rows = 3;
  error([&] { static_cast<void>(runtime.source_snapshot(row_limit)); }, "sql_rows_source_limit");
  for (int dimension = 0; dimension != 3; ++dimension) {
    auto low = exact;
    auto& cap = dimension == 0 ? low.work_limit.structural_steps : dimension == 1 ? low.work_limit.scalar_fields : low.work_limit.scalar_bytes;
    --cap; const auto baseline = account.statistics().current;
    bool denied = false;
    try { static_cast<void>(runtime.source_snapshot(low)); }
    catch (const storage::IndexFailure& failure) { assert(failure.code() == "storage_work_limit"); denied = true; }
    assert(denied && account.statistics().current == baseline && runtime.sequence() == 1);
  }
  std::size_t allocations = 0;
  { s04_alloc::Scope measure; const auto image = runtime.source_snapshot(); allocations = s04_alloc::calls; }
  assert(allocations > 0);
  for (std::size_t cut = 0; cut != allocations; ++cut) {
    const auto baseline = account.statistics().current; bool denied = false;
    {
      s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(cut));
      try { static_cast<void>(runtime.source_snapshot()); } catch (const std::bad_alloc&) { denied = true; }
      assert(s04_alloc::triggered == denied);
    }
    assert(denied && account.statistics().current == baseline && runtime.sequence() == 1);
    assert(runtime.source_snapshot().rows.size() == 4);
  }
  {
    auto cursor = runtime.results();
    error([&] { static_cast<void>(runtime.source_snapshot()); }, "sql_rows_busy");
    cursor.cancel();
  }
  const Cells lookup{n(1),s(original),n(5),storage::ScalarView{true}};
  static_cast<void>(runtime.apply({2,TableId{0},lookup,2,0}));
  assert(runtime.source_snapshot().rows.size() == 3 && retained->rows.size() == 4);
  assert(retained->rows[0].row.export_values()[1] == Value{original});
  std::cout << "source snapshot " << indexed << ": covered-new failure positions=" << allocations << '\n';
}

// Composite capture retains the original genuine binding and source recipe
// independently of mutable runtime state or every facade's lifetime.
void composed_lifetime(bool indexed) {
  std::optional<sql_aggregate::SourceSnapshot> image;
  resource::MemoryAccount account;
  const std::string original(256, 'g');
  {
    auto program = aggregate_program();
    auto runtime = SqlAggregateRuntime(program, tree(program.source_program()),
        indexed ? s04_runtime::options() : PhysicalOptions{});
    account = runtime.account();
    const Cells row{n(1),s(original),n(8),storage::ScalarView{true}};
    const std::array edits{sql_rows::SourceReplacement{TableId{0},row,0,3}};
    auto pending = runtime.prepare_batch({1,edits});
    error([&] { static_cast<void>(runtime.source_snapshot()); }, "sql_aggregate_busy");
    static_cast<void>(pending.commit()); image.emplace(runtime.source_snapshot());
    assert(image->program.identity().binding == runtime.program().identity().binding);
    assert(image->source.sequence == runtime.sequence() && image->source.rows.size() == 1);
    const auto snapshot_allocations = account.statistics().successful_allocations;
    { s04_alloc::Scope deny(0); auto moved = std::move(*image); image.emplace(std::move(moved)); assert(s04_alloc::calls == 0); }
    assert(account.statistics().successful_allocations == snapshot_allocations);
    program = {};
  }
  assert(image->source.rows[0].row.export_values()[1] == Value{original});
  assert(image->source.rows[0].weight == 3 && image->source.native_binding.multiplicity_limit == UINT64_MAX);
  assert(!image->program.original_sql().empty() && !image->source.native_program.nodes().empty());
  image.reset(); controller_only(account);
}

// Constant zero/one native routes still retain authoritative unused physical
// rows. Their image cannot be reconstructed from native/group results alone.
void constant_sources(bool indexed) {
  for (const auto sql : {"SELECT COUNT(*)", "SELECT COUNT(*) FROM r WHERE FALSE"}) {
    auto binding = frontend::bind_sql_aggregate(sql, catalog());
    assert(std::holds_alternative<frontend::SqlAggregateProgram>(binding));
    const auto program = std::get<frontend::SqlAggregateProgram>(std::move(binding));
    FreeConnexTree selected;
    if (!program.source_program().contradiction()) selected = tree(program.source_program());
    auto runtime = SqlAggregateRuntime(program, selected, indexed ? s04_runtime::options() : PhysicalOptions{});
    const auto root = runtime.root_weight();
    assert(runtime.source_snapshot().source.rows.empty());
    const Cells row{s("raw")};
    const std::array edits{sql_rows::SourceReplacement{TableId{2},row,0,7}};
    static_cast<void>(runtime.prepare_batch({1,edits}).commit());
    const auto image = runtime.source_snapshot();
    assert(image.source.sequence == 1 && image.source.rows.size() == 1);
    assert(image.source.rows[0].source == TableId{2} && image.source.rows[0].weight == 7);
    assert(runtime.root_weight() == root);
  }
}
} // namespace
int main() {
  for (const auto indexed : {false,true}) { source_image(indexed); composed_lifetime(indexed); constant_sources(indexed); }
  std::cout << "physical source snapshot ownership, bindings, limits and failure controls passed\n";
}
