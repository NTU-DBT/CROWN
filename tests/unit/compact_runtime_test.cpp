// Differential check of the compact fast-path kernel against DeltaRuntime.
//
// Every query shape is lowered once and driven by the same random stream of
// valid physical set updates through both engines. After every update the
// signed result delta must be the same multiset; periodically the complete
// result, the Boolean answer and the kernel's own invariants are compared too.
// A second kernel is maintained through the word-level entry point without a
// delta sink, and a third replays the whole stream through the batched entry
// point with one separator table per edge; both must end in the same result,
// and the third must report the same delta rows in the same order. Pass
// "indexed" to run the oracle on the indexed backend.
#include "crown/api/error.hpp"
#include "crown/planner/lower.hpp"
#include "crown/planner/oracle.hpp"
#include "crown/runtime/compact.hpp"
#include "crown/runtime/delta.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <random>
#include <stdexcept>
#include <span>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace {
using namespace crown;
using namespace crown::runtime;

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}
Column column(const char* name, ScalarType type = ScalarType::int64) { return Column{name, type}; }
Table table(const char* name, std::vector<Column> columns) {
  Table result;
  result.name = name;
  result.columns = std::move(columns);
  return result;
}
Variable variable(const char* name, ScalarType type = ScalarType::int64) { return Variable{name, type}; }
VariableId v(std::size_t id) { return VariableId{id}; }

struct Case {
  std::string name;
  Catalog catalog;
  Query query;
  std::int64_t domain = 5;
};

std::vector<Case> cases() {
  std::vector<Case> result;
  const auto binary = [](std::initializer_list<const char*> names) {
    Catalog catalog{1, {}};
    for (const auto* name : names) catalog.tables.push_back(table(name, {column("p"), column("q")}));
    return catalog;
  };
  {  // Q(x,y,z) :- R(x,y), S(x,z)
    Case c{"hierarchical_full", binary({"R", "S"}), {}, 5};
    c.query.variables = {variable("x"), variable("y"), variable("z")};
    c.query.atoms = {{"R", TableId{0}, {v(0), v(1)}}, {"S", TableId{1}, {v(0), v(2)}}};
    c.query.head = {{v(0), "x"}, {v(1), "y"}, {v(2), "z"}};
    result.push_back(c);
  }
  {  // Q(a,b,c,d) :- R(a,b), S(b,c), T(c,d)
    Case c{"path3_full", binary({"R", "S", "T"}), {}, 4};
    c.query.variables = {variable("a"), variable("b"), variable("c"), variable("d")};
    c.query.atoms = {{"R", TableId{0}, {v(0), v(1)}}, {"S", TableId{1}, {v(1), v(2)}}, {"T", TableId{2}, {v(2), v(3)}}};
    c.query.head = {{v(0), "a"}, {v(1), "b"}, {v(2), "c"}, {v(3), "d"}};
    result.push_back(c);
  }
  {  // Q(a,b) :- R(a,b), S(b,c), T(c,d)
    Case c{"path3_prefix", binary({"R", "S", "T"}), {}, 4};
    c.query.variables = {variable("a"), variable("b"), variable("c"), variable("d")};
    c.query.atoms = {{"R", TableId{0}, {v(0), v(1)}}, {"S", TableId{1}, {v(1), v(2)}}, {"T", TableId{2}, {v(2), v(3)}}};
    c.query.head = {{v(0), "a"}, {v(1), "b"}};
    result.push_back(c);
  }
  {  // Q(b) :- R(a,b), S(b,c), T(c,d)
    Case c{"path3_middle", binary({"R", "S", "T"}), {}, 4};
    c.query.variables = {variable("a"), variable("b"), variable("c"), variable("d")};
    c.query.atoms = {{"R", TableId{0}, {v(0), v(1)}}, {"S", TableId{1}, {v(1), v(2)}}, {"T", TableId{2}, {v(2), v(3)}}};
    c.query.head = {{v(1), "b"}};
    result.push_back(c);
  }
  {  // Q() :- R(a,b), S(b,c), T(c,d)
    Case c{"path3_boolean", binary({"R", "S", "T"}), {}, 4};
    c.query.variables = {variable("a"), variable("b"), variable("c"), variable("d")};
    c.query.atoms = {{"R", TableId{0}, {v(0), v(1)}}, {"S", TableId{1}, {v(1), v(2)}}, {"T", TableId{2}, {v(2), v(3)}}};
    result.push_back(c);
  }
  {  // Q(a,b,c,d,e) :- R(a,b), S(b,c), T(c,d), U(d,e)
    Case c{"path4_full", binary({"R", "S", "T", "U"}), {}, 3};
    c.query.variables = {variable("a"), variable("b"), variable("c"), variable("d"), variable("e")};
    c.query.atoms = {{"R", TableId{0}, {v(0), v(1)}}, {"S", TableId{1}, {v(1), v(2)}}, {"T", TableId{2}, {v(2), v(3)}},
                     {"U", TableId{3}, {v(3), v(4)}}};
    c.query.head = {{v(0), "a"}, {v(1), "b"}, {v(2), "c"}, {v(3), "d"}, {v(4), "e"}};
    result.push_back(c);
  }
  {  // Q(x,a,b,c) :- R(x,a), S(x,b), T(x,c)
    Case c{"star3_full", binary({"R", "S", "T"}), {}, 4};
    c.query.variables = {variable("x"), variable("a"), variable("b"), variable("c")};
    c.query.atoms = {{"R", TableId{0}, {v(0), v(1)}}, {"S", TableId{1}, {v(0), v(2)}}, {"T", TableId{2}, {v(0), v(3)}}};
    c.query.head = {{v(0), "x"}, {v(1), "a"}, {v(2), "b"}, {v(3), "c"}};
    result.push_back(c);
  }
  {  // Q(x,a) :- R(x,a), S(x,b), T(x,c)
    Case c{"star3_projected", binary({"R", "S", "T"}), {}, 4};
    c.query.variables = {variable("x"), variable("a"), variable("b"), variable("c")};
    c.query.atoms = {{"R", TableId{0}, {v(0), v(1)}}, {"S", TableId{1}, {v(0), v(2)}}, {"T", TableId{2}, {v(0), v(3)}}};
    c.query.head = {{v(0), "x"}, {v(1), "a"}};
    result.push_back(c);
  }
  {  // Q(x) :- R(x,a), S(x,b), T(x,c)
    Case c{"star3_center", binary({"R", "S", "T"}), {}, 4};
    c.query.variables = {variable("x"), variable("a"), variable("b"), variable("c")};
    c.query.atoms = {{"R", TableId{0}, {v(0), v(1)}}, {"S", TableId{1}, {v(0), v(2)}}, {"T", TableId{2}, {v(0), v(3)}}};
    c.query.head = {{v(0), "x"}};
    result.push_back(c);
  }
  {  // Self-join: Q(a,b,c) :- E(a,b), E(b,c)
    Case c{"self_join_path2", binary({"E"}), {}, 5};
    c.query.variables = {variable("a"), variable("b"), variable("c")};
    c.query.atoms = {{"E1", TableId{0}, {v(0), v(1)}}, {"E2", TableId{0}, {v(1), v(2)}}};
    c.query.head = {{v(0), "a"}, {v(1), "b"}, {v(2), "c"}};
    result.push_back(c);
  }
  {  // Self-join: Q(a,d) is not free-connex; use Q(a,b,c,d) :- E(a,b), E(b,c), E(c,d)
    Case c{"self_join_path3", binary({"E"}), {}, 4};
    c.query.variables = {variable("a"), variable("b"), variable("c"), variable("d")};
    c.query.atoms = {{"E1", TableId{0}, {v(0), v(1)}}, {"E2", TableId{0}, {v(1), v(2)}}, {"E3", TableId{0}, {v(2), v(3)}}};
    c.query.head = {{v(0), "a"}, {v(1), "b"}, {v(2), "c"}, {v(3), "d"}};
    result.push_back(c);
  }
  {  // The original experiments' shapes, every alias reading one edge table.
    Case c{"self_join_path4", binary({"E"}), {}, 4};
    c.query.variables = {variable("a"), variable("b"), variable("c"), variable("d"), variable("e")};
    c.query.atoms = {{"E1", TableId{0}, {v(0), v(1)}}, {"E2", TableId{0}, {v(1), v(2)}}, {"E3", TableId{0}, {v(2), v(3)}},
                     {"E4", TableId{0}, {v(3), v(4)}}};
    c.query.head = {{v(0), "a"}, {v(1), "b"}, {v(2), "c"}, {v(3), "d"}, {v(4), "e"}};
    result.push_back(c);
  }
  {
    Case c{"self_join_star4", binary({"E"}), {}, 4};
    c.query.variables = {variable("a"), variable("b"), variable("c"), variable("d"), variable("e")};
    c.query.atoms = {{"E1", TableId{0}, {v(0), v(1)}}, {"E2", TableId{0}, {v(0), v(2)}}, {"E3", TableId{0}, {v(0), v(3)}},
                     {"E4", TableId{0}, {v(0), v(4)}}};
    c.query.head = {{v(0), "a"}, {v(1), "b"}, {v(2), "c"}, {v(3), "d"}, {v(4), "e"}};
    result.push_back(c);
  }
  {  // Self-join with projection: Q(a,b) :- E(a,b), E(b,c), E(c,d)
    Case c{"self_join_path3_prefix", binary({"E"}), {}, 4};
    c.query.variables = {variable("a"), variable("b"), variable("c"), variable("d")};
    c.query.atoms = {{"E1", TableId{0}, {v(0), v(1)}}, {"E2", TableId{0}, {v(1), v(2)}}, {"E3", TableId{0}, {v(2), v(3)}}};
    c.query.head = {{v(0), "a"}, {v(1), "b"}};
    result.push_back(c);
  }
  {  // Self-join star with projection: Q(a,b) :- E(a,b), E(a,c), E(a,d)
    Case c{"self_join_star3_projected", binary({"E"}), {}, 4};
    c.query.variables = {variable("a"), variable("b"), variable("c"), variable("d")};
    c.query.atoms = {{"E1", TableId{0}, {v(0), v(1)}}, {"E2", TableId{0}, {v(0), v(2)}}, {"E3", TableId{0}, {v(0), v(3)}}};
    c.query.head = {{v(0), "a"}, {v(1), "b"}};
    result.push_back(c);
  }
  const auto ternary = [](std::initializer_list<const char*> names) {
    Catalog catalog{1, {}};
    for (const auto* name : names) catalog.tables.push_back(table(name, {column("p"), column("q"), column("r")}));
    return catalog;
  };
  {  // Two-column separator: Q(a,b,c,d) :- R(a,b,c), S(a,b,d)
    Case c{"wide_separator_full", ternary({"R", "S"}), {}, 3};
    c.query.variables = {variable("a"), variable("b"), variable("c"), variable("d")};
    c.query.atoms = {{"R", TableId{0}, {v(0), v(1), v(2)}}, {"S", TableId{1}, {v(0), v(1), v(3)}}};
    c.query.head = {{v(0), "a"}, {v(1), "b"}, {v(2), "c"}, {v(3), "d"}};
    result.push_back(c);
  }
  {  // The separator columns in a different order on each side, projected: Q(c,a) :- R(a,b,c), S(b,a,d)
    Case c{"wide_separator_reordered", ternary({"R", "S"}), {}, 3};
    c.query.variables = {variable("a"), variable("b"), variable("c"), variable("d")};
    c.query.atoms = {{"R", TableId{0}, {v(0), v(1), v(2)}}, {"S", TableId{1}, {v(1), v(0), v(3)}}};
    c.query.head = {{v(2), "c"}, {v(0), "a"}};
    result.push_back(c);
  }
  {  // Self-join on two columns with a third alias: Q(a,b,c,d,e) :- T(a,b,c), T(a,b,d), T(b,a,e)
    Case c{"wide_separator_self_join", ternary({"T"}), {}, 3};
    c.query.variables = {variable("a"), variable("b"), variable("c"), variable("d"), variable("e")};
    c.query.atoms = {{"T1", TableId{0}, {v(0), v(1), v(2)}}, {"T2", TableId{0}, {v(0), v(1), v(3)}}, {"T3", TableId{0}, {v(1), v(0), v(4)}}};
    c.query.head = {{v(0), "a"}, {v(1), "b"}, {v(2), "c"}, {v(3), "d"}, {v(4), "e"}};
    result.push_back(c);
  }
  {  // Disconnected: Q(a,c) :- R(a,b), S(c,d)
    Case c{"disconnected_projected", binary({"R", "S"}), {}, 4};
    c.query.variables = {variable("a"), variable("b"), variable("c"), variable("d")};
    c.query.atoms = {{"R", TableId{0}, {v(0), v(1)}}, {"S", TableId{1}, {v(2), v(3)}}};
    c.query.head = {{v(0), "a"}, {v(2), "c"}};
    result.push_back(c);
  }
  {  // Repeated variable, constant and ignored column: Q(a,c) :- R(a,a), S(a,c), T(3,_)
    Case c{"repeated_constant_ignored", binary({"R", "S", "T"}), {}, 5};
    c.query.variables = {variable("a"), variable("c")};
    c.query.atoms = {{"R", TableId{0}, {v(0), v(0)}}, {"S", TableId{1}, {v(0), v(1)}},
                     {"T", TableId{2}, {Value{std::int64_t{3}}, IgnoredColumn{}}}};
    c.query.head = {{v(0), "a"}, {v(1), "c"}};
    result.push_back(c);
  }
  {  // Projection inside one atom: Q(a) :- R(a,_), S(a,c)
    Case c{"ignored_with_derivations", binary({"R", "S"}), {}, 5};
    c.query.variables = {variable("a"), variable("c")};
    c.query.atoms = {{"R", TableId{0}, {v(0), IgnoredColumn{}}}, {"S", TableId{1}, {v(0), v(1)}}};
    c.query.head = {{v(0), "a"}};
    result.push_back(c);
  }
  {  // Strings and repeated head: Q(n,x,n) :- R(x,n), S(n,m)
    Case c{"strings", {1, {table("R", {column("x"), column("n", ScalarType::string)}),
                           table("S", {column("n", ScalarType::string), column("m", ScalarType::string)})}}, {}, 4};
    c.query.variables = {variable("x"), variable("n", ScalarType::string), variable("m", ScalarType::string)};
    c.query.atoms = {{"R", TableId{0}, {v(0), v(1)}}, {"S", TableId{1}, {v(1), v(2)}}};
    c.query.head = {{v(1), "n"}, {v(0), "x"}, {v(1), "n2"}};
    result.push_back(c);
  }
  {  // Wider tree: Q(a,b,c,e) :- R(a,b), S(b,c), T(b,d), U(c,e), W(c,f)
    Case c{"branching_projected", binary({"R", "S", "T", "U", "W"}), {}, 3};
    c.query.variables = {variable("a"), variable("b"), variable("c"), variable("d"), variable("e"), variable("f")};
    c.query.atoms = {{"R", TableId{0}, {v(0), v(1)}}, {"S", TableId{1}, {v(1), v(2)}}, {"T", TableId{2}, {v(1), v(3)}},
                     {"U", TableId{3}, {v(2), v(4)}}, {"W", TableId{4}, {v(2), v(5)}}};
    c.query.head = {{v(0), "a"}, {v(1), "b"}, {v(2), "c"}, {v(4), "e"}};
    result.push_back(c);
  }
  return result;
}

struct Collector final : compact::RowSink {
  const compact::Runtime* owner = nullptr;
  std::vector<Row> rows;
  void row(const compact::Word* words) override { rows.push_back(owner->decode(words)); }
};

Value make_value(ScalarType type, std::int64_t number) {
  if (type == ScalarType::string) return Value{std::string("s") + std::to_string(number)};
  return Value{number};
}

std::uint64_t run(const Case& input, bool indexed, std::uint64_t seed, std::size_t updates) {
  const auto tree = planner::minimum_tree(input.catalog, input.query);
  check(tree.status == planner::OracleStatus::proven_minimum && tree.tree.has_value(), input.name + ": no join tree: " + tree.reason);
  PhysicalOptions physical;
  if (indexed) {
    const std::size_t big = 1'000'000;
    const std::uint64_t work = 1'000'000'000'000ULL;
    physical.indexed_storage = storage::IndexedBackendSpec{{big, 64, big, big, big, big, big, big, big}, {work, work, work, work, work}};
  }
  const auto plan = planner::lower_tree(input.catalog, input.query, *tree.tree, physical);
  DeltaOptions options;
  options.mode = DeltaMode::delta;
  options.work_limit = std::nullopt;
  options.physical.work_limit = std::nullopt;
  options.physical.support.work_limit = std::nullopt;
  options.physical.support.observation.mode = ObservationMode::off;
  options.cursor.work_limit = std::nullopt;
  DeltaRuntime oracle(plan, options);
  compact::Runtime fast(plan), quiet(plan);
  Collector delta, full;
  delta.owner = &fast;
  check(fast.result_arity() == input.query.head.size(), input.name + ": result arity differs");

  const auto compare_full = [&](const compact::Runtime& candidate, const char* label) {
    std::vector<Row> expected;
    auto cursor = oracle.results(ResultCursorOptions{std::nullopt});
    while (auto tuple = cursor.next()) expected.push_back(storage::export_row(tuple->values()));
    full.owner = &candidate;
    full.rows.clear();
    candidate.enumerate(full);
    std::sort(expected.begin(), expected.end());
    std::sort(full.rows.begin(), full.rows.end());
    check(std::adjacent_find(full.rows.begin(), full.rows.end()) == full.rows.end(), input.name + ": " + label + " result repeats a row");
    check(expected == full.rows, input.name + ": " + label + " result differs after " + std::to_string(oracle.sequence()) + " updates (" +
        std::to_string(expected.size()) + " expected, " + std::to_string(full.rows.size()) + " found)");
    check(oracle.has_answer() == candidate.has_answer(), input.name + ": " + label + " answer differs");
    candidate.check_invariants();
  };

  std::mt19937_64 random(seed);
  std::vector<std::vector<Row>> live(input.catalog.tables.size());
  std::uint64_t sequence = 0, compared = 0;
  std::vector<std::tuple<std::size_t, SetOperation, Row>> history;  // Every update offered to the kernel.
  std::vector<Row> trace;                                           // Its delta rows, in the order reported.
  std::size_t valid = 0;
  for (std::size_t step = 0; step < updates; ++step) {
    const auto target = static_cast<std::size_t>(random() % input.catalog.tables.size());
    auto& rows = live[target];
    Row row;
    bool insert = rows.empty() || random() % 100 < 58;
    if (insert) {
      for (const auto& field : input.catalog.tables[target].columns)
        row.push_back(make_value(field.type, static_cast<std::int64_t>(random() % static_cast<std::uint64_t>(input.domain))));
      if (std::find(rows.begin(), rows.end(), row) != rows.end()) {
        check(!fast.apply(TableId{target}, SetOperation::insert, row, nullptr), input.name + ": duplicate insert changed the kernel");
        history.emplace_back(target, SetOperation::insert, row);
        continue;
      }
      rows.push_back(row);
    } else {
      const auto position = static_cast<std::size_t>(random() % rows.size());
      row = rows[position];
      rows[position] = rows.back();
      rows.pop_back();
    }
    const auto operation = insert ? SetOperation::insert : SetOperation::erase;
    std::vector<Row> expected;
    auto epoch = oracle.apply(PhysicalSetUpdate{++sequence, TableId{target}, operation, row});
    while (auto record = epoch.next()) {
      check(record->operation == operation, input.name + ": oracle delta sign differs from its update");
      expected.push_back(storage::export_row(record->tuple.values()));
    }
    delta.rows.clear();
    check(fast.apply(TableId{target}, operation, row, &delta), input.name + ": kernel rejected a valid update");
    history.emplace_back(target, operation, row);
    trace.insert(trace.end(), delta.rows.begin(), delta.rows.end());
    ++valid;
    // The second kernel takes pre-encoded words, so both entry points are covered.
    std::vector<compact::Word> words;
    for (const auto& value : row) words.push_back(quiet.encode(value));
    check(quiet.apply(TableId{target}, operation, std::span<const compact::Word>(words), nullptr), input.name + ": quiet kernel rejected a valid update");
    std::sort(expected.begin(), expected.end());
    std::sort(delta.rows.begin(), delta.rows.end());
    check(expected == delta.rows, input.name + ": delta differs at update " + std::to_string(sequence) + " (" +
        std::to_string(expected.size()) + " expected, " + std::to_string(delta.rows.size()) + " found)");
    compared += expected.size() + 1;
    if (step % 97 == 0) compare_full(fast, "delta-mode");
  }
  compare_full(fast, "delta-mode");
  compare_full(quiet, "maintenance-mode");
  // A third kernel replays the whole stream through the batched entry point,
  // including the refused duplicates, and must report the same delta rows in
  // the same order as the one-call-per-update kernel did.
  {
    compact::Options unshared;      // Also covers the layout with one table per edge.
    unshared.shared_separators = false;
    compact::Runtime batched(plan, unshared);
    std::vector<compact::Word> words;
    std::vector<std::size_t> starts;
    for (const auto& [target, operation, row] : history) {
      starts.push_back(words.size());
      for (const auto& value : row) words.push_back(batched.encode(value));
    }
    std::vector<compact::Update> updates;
    for (std::size_t i = 0; i < history.size(); ++i)
      updates.push_back({TableId{std::get<0>(history[i])}, std::get<1>(history[i]), words.data() + starts[i]});
    Collector replay;
    replay.owner = &batched;
    std::size_t accepted = 0;
    for (std::size_t from = 0; from < updates.size();) {
      const auto size = std::min<std::size_t>(1 + from % 37, updates.size() - from);
      accepted += batched.apply(std::span<const compact::Update>(updates.data() + from, size), &replay);
      from += size;
    }
    check(accepted == valid, input.name + ": batched kernel accepted a different number of updates");
    check(replay.rows == trace, input.name + ": batched kernel reported different delta rows");
    compare_full(batched, "batched");
    auto left = batched.statistics(), right = fast.statistics();
    left.separator_keys = right.separator_keys = 0;   // The one figure that depends on the layout.
    check(left == right, input.name + ": batched kernel statistics differ");
  }
  check(fast.statistics() == quiet.statistics(), input.name + ": statistics depend on the delta sink");
  // Draining every relation must return all pooled state to empty.
  for (std::size_t target = 0; target < live.size(); ++target)
    for (const auto& row : live[target]) {
      static_cast<void>(oracle.apply(PhysicalSetUpdate{++sequence, TableId{target}, SetOperation::erase, row}));
      check(fast.apply(TableId{target}, SetOperation::erase, row, &delta), input.name + ": kernel rejected a drain erase");
      check(!fast.apply(TableId{target}, SetOperation::erase, row, &delta), input.name + ": absent erase changed the kernel");
    }
  fast.check_invariants();
  const auto drained = fast.statistics();
  check(drained.source_rows == 0 && drained.records == 0 && drained.survivors == 0 && drained.separator_keys == 0 &&
      drained.visible_keys == 0 && !fast.has_answer(), input.name + ": drained kernel retained state");
  return compared;
}
}  // namespace

int main(int argc, char** argv) {
  try {
    const bool indexed = argc > 1 && std::string(argv[1]) == "indexed";
    std::uint64_t compared = 0;
    for (const auto& input : cases())
      for (std::uint64_t seed = 1; seed <= 3; ++seed) compared += run(input, indexed, seed, indexed ? 600 : 1200);
    // A wider value domain gives keys with many members and many keys with
    // one, so arrays grow, shrink and move between size classes and the
    // directories and slabs are rebuilt several times.
    for (auto input : cases()) {
      const bool wide = input.name.rfind("wide_separator", 0) == 0;
      if (input.name.rfind("self_join", 0) != 0 && !wide && input.name != "branching_projected" && input.name != "strings") continue;
      input.domain = wide ? 7 : 24;
      compared += run(input, indexed, 7, indexed ? 1500 : 4000);
    }
    std::cout << "compact runtime matches DeltaRuntime on " << cases().size() << " query shapes, " << compared << " compared records\n";
    return 0;
  } catch (const crown::Error& failure) {
    std::cerr << "compact_runtime_test: " << failure.code() << ": " << failure.what() << "\n";
  } catch (const std::exception& failure) {
    std::cerr << "compact_runtime_test: " << failure.what() << "\n";
  }
  return 1;
}
