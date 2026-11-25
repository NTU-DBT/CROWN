// Differential test of the keyed cyclic core: fallback::Runtime on its default
// keyed engine against the reference engine (CROWN_FALLBACK_ENGINE=reference)
// on random insert/erase streams over cyclic, self-join, constant, string and
// wide-row queries; plus the engine's own recount invariants and atomicity of
// rejected events (row limit) on both engines.
#include "crown/runtime/keyed_cyclic.hpp"
#include "crown/runtime/fallback.hpp"
#include "crown/planner/fallback.hpp"
#include "crown/api/error.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using namespace crown;
namespace fr = runtime::fallback;

std::uint64_t checks = 0, delta_rows = 0, snapshot_rows = 0, rejected = 0;
void check(bool value, const std::string& message) {
  if (!value) throw std::runtime_error(message);
  ++checks;
}
struct Fixture {
  std::string name;
  Catalog catalog;
  Query query;
};
Term var(std::size_t id) { return VariableId{id}; }

// Tables as column type lists; variables typed by the first column that binds them.
Fixture make(std::string name, std::vector<std::pair<std::string, std::vector<ScalarType>>> tables,
    std::vector<std::pair<std::size_t, std::vector<Term>>> atoms, std::vector<std::size_t> head) {
  Fixture f;
  f.name = std::move(name);
  for (const auto& [table, columns] : tables) {
    Table t{table, {}};
    for (std::size_t c = 0; c < columns.size(); ++c) t.columns.push_back({"c" + std::to_string(c), columns[c]});
    f.catalog.tables.push_back(std::move(t));
  }
  std::vector<std::optional<ScalarType>> types;
  for (const auto& [table, terms] : atoms)
    for (std::size_t c = 0; c < terms.size(); ++c)
      if (const auto* v = std::get_if<VariableId>(&terms[c])) {
        if (types.size() <= v->value) types.resize(v->value + 1);
        if (!types[v->value]) types[v->value] = tables[table].second[c];
      }
  for (std::size_t v = 0; v < types.size(); ++v) f.query.variables.push_back({"v" + std::to_string(v), types[v].value_or(ScalarType::int64)});
  std::size_t occurrence = 0;
  for (auto& [table, terms] : atoms) f.query.atoms.push_back({"o" + std::to_string(occurrence++), TableId{table}, std::move(terms)});
  for (const auto v : head) f.query.head.push_back({VariableId{v}, "h" + std::to_string(f.query.head.size())});
  return f;
}
Value value_of(ScalarType type, int x) {
  switch (type) {
    case ScalarType::string: return std::string(x % 2 ? "long-string-value-" : "s") + std::to_string(x);
    case ScalarType::boolean: return x % 2 == 1;
    default: return static_cast<std::int64_t>(x - 1);
  }
}
std::vector<Row> rows_of(const fr::TupleVector& tuples) {
  std::vector<Row> out;
  for (const auto& tuple : tuples) out.push_back(storage::export_row(tuple.values()));
  return out;
}

struct Engines {
  std::optional<fr::Runtime> keyed, reference;
};
Engines build(const planner::fallback::Plan& plan, const fr::Options& options) {
  Engines out;
  ::unsetenv("CROWN_FALLBACK_ENGINE");
  out.keyed.emplace(plan, options);
  ::setenv("CROWN_FALLBACK_ENGINE", "reference", 1);
  out.reference.emplace(plan, options);
  ::unsetenv("CROWN_FALLBACK_ENGINE");
  return out;
}

void run(const Fixture& f, std::uint32_t seed, int events, int domain, std::uint64_t row_limit) {
  const auto plan = planner::fallback::admit(f.catalog, f.query, PhysicalOptions{});
  check(runtime::keyed::CyclicEngine::unsupported(plan.originalcatalog(), plan.query()).empty(), f.name + " unsupported");
  fr::Options options;
  options.sources.support.memory_limit_bytes = std::uint64_t{1} << 32;
  options.sources.work_limit = std::uint64_t{1} << 40;
  options.sources.support.work_limit = std::uint64_t{1} << 40;
  options.recompute = {std::uint64_t{1} << 40, 1u << 20, row_limit};
  auto engines = build(plan, options);
  auto& keyed = *engines.keyed;
  auto& reference = *engines.reference;
  // A standalone engine on the same stream checks the recount invariants.
  runtime::keyed::CyclicEngine engine(plan.originalcatalog(), plan.query(), {.answer_limit = row_limit});
  // Decomposable queries take the GHD path (bags + keyed set engine).
  if (f.name.starts_with("dumbbell") || f.name.starts_with("pendant"))
    check(engine.algorithm() == "ghd" && keyed.algorithm() == "ghd", f.name + " takes the GHD path");
  std::mt19937 random(seed);
  std::vector<std::vector<Row>> present(f.catalog.tables.size());
  std::uint64_t sequence = 0;
  for (int event = 0; event < events; ++event) {
    const auto t = std::uniform_int_distribution<std::size_t>(0, f.catalog.tables.size() - 1)(random);
    Row row;
    const bool erase = !present[t].empty() && std::uniform_int_distribution<int>(0, 9)(random) < (seed % 3 == 0 ? 2 : 4);
    if (erase && std::uniform_int_distribution<int>(0, 9)(random) < 9)
      row = present[t][std::uniform_int_distribution<std::size_t>(0, present[t].size() - 1)(random)];
    else
      for (const auto& column : f.catalog.tables[t].columns)
        row.push_back(value_of(column.type, std::uniform_int_distribution<int>(1, domain)(random)));
    const auto operation = erase ? SetOperation::erase : SetOperation::insert;
    ++sequence;
    std::optional<fr::Epoch> want, got;
    std::string want_error, got_error;
    try { want.emplace(reference.apply({sequence, TableId{t}, operation, row})); }
    catch (const Error& error) { want_error = std::string(error.code()); }
    try { got.emplace(keyed.apply({sequence, TableId{t}, operation, row})); }
    catch (const Error& error) { got_error = std::string(error.code()); }
    check(want_error == got_error, f.name + " error differs at event " + std::to_string(event) + ": ref '" + want_error +
        "' keyed '" + got_error + "'");
    std::vector<storage::ScalarView> cells;
    for (const auto& value : row) cells.push_back(storage::borrow_scalar(value));
    if (!want) {
      // Rejected by both: nothing changed, and the sequence is not consumed.
      ++rejected; --sequence;
      bool threw = false;
      try { static_cast<void>(engine.prepare(TableId{t}, operation, storage::RowView::borrow(cells), nullptr)); }
      catch (const Error&) { threw = true; }
      check(threw && !engine.pending(), "standalone engine rejects the same event");
      engine.check_invariants();
      continue;
    }
    auto found = std::find(present[t].begin(), present[t].end(), row);
    if (!erase && found == present[t].end()) present[t].push_back(row);
    if (erase && found != present[t].end()) present[t].erase(found);
    check(rows_of(want->added) == rows_of(got->added) && rows_of(want->removed) == rows_of(got->removed),
        f.name + " seed " + std::to_string(seed) + " delta differs at event " + std::to_string(event));
    check(got->metrics.added == got->added.size() && got->metrics.removed == got->removed.size(), "delta metrics");
    delta_rows += want->added.size() + want->removed.size();
    if (engine.prepare(TableId{t}, operation, storage::RowView::borrow(cells), nullptr)) engine.publish();
    if (event % 7 == 0 || event + 1 == events) {
      const fr::Limits limits{std::uint64_t{1} << 40, 1u << 20, 1u << 20};
      const auto expected = rows_of(reference.snapshot(limits).rows);
      check(expected == rows_of(keyed.snapshot(limits).rows), f.name + " snapshot differs at event " + std::to_string(event));
      check(keyed.has_answer() == !expected.empty() && keyed.explain().result_rows == expected.size(), "answer summary");
      check(engine.answers() == expected.size(), "standalone engine answer count");
      check(keyed.source_snapshot().tables == reference.source_snapshot().tables, "source snapshot");
      engine.check_invariants();
      snapshot_rows += expected.size();
    }
  }
  engine.collect();
  engine.check_invariants();
}
}  // namespace

int main() try {
  using enum ScalarType;
  const std::vector<ScalarType> ii{int64, int64}, ss{string, string}, is{int64, string}, iii{int64, int64, int64};
  const std::vector<Fixture> fixtures = {
      make("triangle-full", {{"R", ii}, {"S", ii}, {"T", ii}},
           {{0, {var(0), var(1)}}, {1, {var(1), var(2)}}, {2, {var(2), var(0)}}}, {0, 1, 2}),
      make("triangle-project", {{"R", ii}, {"S", ii}, {"T", ii}},
           {{0, {var(0), var(1)}}, {1, {var(1), var(2)}}, {2, {var(2), var(0)}}}, {0}),
      make("triangle-self", {{"E", ii}}, {{0, {var(0), var(1)}}, {0, {var(1), var(2)}}, {0, {var(2), var(0)}}}, {0, 2}),
      make("triangle-strings", {{"R", ss}, {"S", ss}, {"T", ss}},
           {{0, {var(0), var(1)}}, {1, {var(1), var(2)}}, {2, {var(2), var(0)}}}, {0, 2}),
      make("four-cycle-mixed", {{"A", is}, {"B", {string, int64}}, {"C", ii}, {"D", ii}},
           {{0, {var(0), var(1)}}, {1, {var(1), var(2)}}, {2, {var(2), var(3)}}, {3, {var(3), var(0)}}}, {0, 1}),
      make("dumbbell-full", {{"m", ii}, {"lbc", ii}, {"lca", ii}, {"rde", ii}, {"rfd", ii}, {"lab", ii}, {"ref", ii}},
           {{0, {var(2), var(3)}}, {1, {var(1), var(2)}}, {2, {var(2), var(0)}}, {3, {var(3), var(4)}},
            {4, {var(5), var(3)}}, {5, {var(0), var(1)}}, {6, {var(4), var(5)}}}, {0, 1, 2, 3, 4, 5}),
      make("dumbbell-project", {{"m", ii}, {"lbc", ii}, {"lca", ii}, {"rde", ii}, {"rfd", ii}, {"lab", ii}, {"ref", ii}},
           {{0, {var(2), var(3)}}, {1, {var(1), var(2)}}, {2, {var(2), var(0)}}, {3, {var(3), var(4)}},
            {4, {var(5), var(3)}}, {5, {var(0), var(1)}}, {6, {var(4), var(5)}}}, {2, 3}),
      // A triangle with a pendant edge: the triangle bag is projected onto its
      // needed variables (head 0, shared 2); the contained edge stays in it.
      make("pendant-project", {{"R", ii}, {"S", ii}, {"T", ii}, {"U", ii}},
           {{0, {var(0), var(1)}}, {1, {var(1), var(2)}}, {2, {var(2), var(0)}}, {3, {var(2), var(3)}}}, {0, 3}),
      make("pendant-full", {{"R", ii}, {"S", ii}, {"T", ii}, {"U", ii}},
           {{0, {var(0), var(1)}}, {1, {var(1), var(2)}}, {2, {var(2), var(0)}}, {3, {var(2), var(3)}}}, {0, 1, 2, 3}),
      make("wide-rows", {{"R", iii}, {"S", {int64, int64, string}}},
           {{0, {var(0), var(1), var(2)}}, {1, {var(1), var(2), var(3)}}}, {0, 3}),
      make("constant-ignored", {{"R", iii}, {"S", ii}, {"T", ii}},
           {{0, {var(0), var(1), Value{std::int64_t{1}}}}, {1, {var(1), var(2)}}, {2, {var(2), IgnoredColumn{}}}}, {0, 2}),
      make("string-constant", {{"R", is}, {"S", is}},
           {{0, {var(0), Value{std::string("long-string-value-1")}}}, {1, {var(0), var(1)}}}, {1}),
      make("repeated", {{"R", ii}, {"S", ii}}, {{0, {var(0), var(0)}}, {1, {var(0), var(1)}}}, {1}),
  };
  for (const auto& f : fixtures) {
    const auto before_delta = delta_rows, before_snapshot = snapshot_rows;
    for (std::uint32_t seed = 1; seed <= 5; ++seed) run(f, seed * 104729U, seed <= 2 ? 250 : 700, seed % 2 ? 3 : 4, 1u << 20);
    run(f, 7919U, 400, 3, 3);  // a tight distinct-answer grant rejects events atomically
    std::cout << f.name << ": delta_rows=" << delta_rows - before_delta << " snapshot_rows=" << snapshot_rows - before_snapshot << "\n";
  }
  std::cout << "keyed cyclic checks=" << checks << " delta_rows=" << delta_rows << " snapshot_rows=" << snapshot_rows
            << " rejected=" << rejected << "\n";
  return 0;
} catch (const std::exception& failure) {
  std::cerr << "FAIL: " << failure.what() << "\n";
  return 1;
}
