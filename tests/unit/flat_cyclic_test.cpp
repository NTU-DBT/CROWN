// Differential test: FlatCyclicRuntime against runtime::fallback::Runtime on
// random insert/erase streams over cyclic, self-join and constant queries.
#include "crown/runtime/flat_cyclic.hpp"
#include "crown/runtime/fallback.hpp"
#include "crown/planner/fallback.hpp"

#include <algorithm>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using namespace crown;
namespace fr = runtime::fallback;

std::uint64_t checks = 0, delta_rows = 0, snapshot_rows = 0;
void check(bool value, const std::string& message) {
  if (!value) throw std::runtime_error(message);
  ++checks;
}
struct Fixture {
  std::string name;
  Catalog catalog;
  Query query;
};
Column integer(std::string name) { return {std::move(name), ScalarType::int64}; }
Term var(std::size_t id) { return VariableId{id}; }

Fixture make(std::string name, std::vector<std::pair<std::string, std::size_t>> tables, std::size_t variables,
    std::vector<std::pair<std::size_t, std::vector<Term>>> atoms, std::vector<std::size_t> head) {
  Fixture f;
  f.name = std::move(name);
  for (const auto& [table, width] : tables) {
    Table t{table, {}};
    for (std::size_t c = 0; c < width; ++c) t.columns.push_back(integer("c" + std::to_string(c)));
    f.catalog.tables.push_back(std::move(t));
  }
  for (std::size_t v = 0; v < variables; ++v) f.query.variables.push_back({"v" + std::to_string(v), ScalarType::int64});
  std::size_t occurrence = 0;
  for (auto& [table, terms] : atoms) f.query.atoms.push_back({"o" + std::to_string(occurrence++), TableId{table}, std::move(terms)});
  for (const auto v : head) f.query.head.push_back({VariableId{v}, "h" + std::to_string(f.query.head.size())});
  return f;
}

std::vector<Row> sorted(std::vector<Row> rows) { std::sort(rows.begin(), rows.end()); return rows; }
struct Collector {
  const runtime::FlatCyclicRuntime* owner = nullptr;
  std::vector<Row> added, removed;
  static void row(void* context, SetOperation operation, const std::int64_t* values, std::size_t size) {
    auto& self = *static_cast<Collector*>(context);
    Row out;
    for (std::size_t i = 0; i < size; ++i) out.push_back(self.owner->decode(i, values[i]));
    (operation == SetOperation::insert ? self.added : self.removed).push_back(std::move(out));
  }
};

void run(const Fixture& f, std::uint32_t seed, int events, int domain) {
  const auto plan = planner::fallback::admit(f.catalog, f.query, PhysicalOptions{});
  const auto reason = runtime::FlatCyclicRuntime::unsupported(plan.originalcatalog(), plan.query());
  check(reason.empty(), f.name + " unsupported: " + reason);
  fr::Options options;
  options.sources.support.memory_limit_bytes = std::uint64_t{1} << 32;
  options.sources.work_limit = std::uint64_t{1} << 40;
  options.sources.support.work_limit = std::uint64_t{1} << 40;
  options.recompute = {std::uint64_t{1} << 40, 1u << 20, 1u << 20};
  fr::Runtime reference(plan, options);
  runtime::FlatCyclicRuntime flat(plan.originalcatalog(), plan.query());
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
      for (std::size_t c = 0; c < f.catalog.tables[t].columns.size(); ++c)
        row.emplace_back(static_cast<std::int64_t>(std::uniform_int_distribution<int>(0, domain - 1)(random)));
    const auto operation = erase ? SetOperation::erase : SetOperation::insert;
    auto found = std::find(present[t].begin(), present[t].end(), row);
    if (!erase && found == present[t].end()) present[t].push_back(row);
    if (erase && found != present[t].end()) present[t].erase(found);
    const auto epoch = reference.apply({++sequence, TableId{t}, operation, row});
    std::vector<Row> added, removed;
    for (const auto& tuple : epoch.added) added.push_back(storage::export_row(tuple.values()));
    for (const auto& tuple : epoch.removed) removed.push_back(storage::export_row(tuple.values()));
    Collector collector{&flat, {}, {}};
    std::vector<std::int64_t> words(flat.arity(TableId{t}));
    flat.encode(TableId{t}, row, words.data());
    flat.apply(TableId{t}, operation, words.data(), {&collector, &Collector::row});
    check(sorted(added) == sorted(collector.added) && sorted(removed) == sorted(collector.removed),
        f.name + " seed " + std::to_string(seed) + " delta differs at event " + std::to_string(event) + " (ref +" +
        std::to_string(added.size()) + "/-" + std::to_string(removed.size()) + ", flat +" +
        std::to_string(collector.added.size()) + "/-" + std::to_string(collector.removed.size()) + ")");
    delta_rows += added.size() + removed.size();
    if (event % 9 == 0 || event + 1 == events) {
      std::vector<Row> want;
      for (const auto& tuple : reference.snapshot({std::uint64_t{1} << 40, 1u << 20, 1u << 20}).rows) want.push_back(storage::export_row(tuple.values()));
      Collector all{&flat, {}, {}};
      flat.snapshot({&all, &Collector::row});
      check(sorted(want) == sorted(all.added), f.name + " snapshot differs at event " + std::to_string(event));
      check(flat.answers() == want.size(), "answer count differs");
      snapshot_rows += want.size();
    }
  }
}
}  // namespace

int main() try {
  const std::vector<Fixture> fixtures = {
      make("triangle-full", {{"R", 2}, {"S", 2}, {"T", 2}}, 3,
           {{0, {var(0), var(1)}}, {1, {var(1), var(2)}}, {2, {var(2), var(0)}}}, {0, 1, 2}),
      make("triangle-project", {{"R", 2}, {"S", 2}, {"T", 2}}, 3,
           {{0, {var(0), var(1)}}, {1, {var(1), var(2)}}, {2, {var(2), var(0)}}}, {0}),
      make("triangle-self", {{"E", 2}}, 3,
           {{0, {var(0), var(1)}}, {0, {var(1), var(2)}}, {0, {var(2), var(0)}}}, {0, 2}),
      make("four-cycle", {{"A", 2}, {"B", 2}, {"C", 2}, {"D", 2}}, 4,
           {{0, {var(0), var(1)}}, {1, {var(1), var(2)}}, {2, {var(2), var(3)}}, {3, {var(3), var(0)}}}, {0, 2}),
      // m(c,d), lbc(b,c), lca(c,a), rde(d,e), rfd(f,d), lab(a,b), ref(e,f)
      make("dumbbell-full", {{"m", 2}, {"lbc", 2}, {"lca", 2}, {"rde", 2}, {"rfd", 2}, {"lab", 2}, {"ref", 2}}, 6,
           {{0, {var(2), var(3)}}, {1, {var(1), var(2)}}, {2, {var(2), var(0)}}, {3, {var(3), var(4)}},
            {4, {var(5), var(3)}}, {5, {var(0), var(1)}}, {6, {var(4), var(5)}}}, {0, 1, 2, 3, 4, 5}),
      make("dumbbell-project", {{"m", 2}, {"lbc", 2}, {"lca", 2}, {"rde", 2}, {"rfd", 2}, {"lab", 2}, {"ref", 2}}, 6,
           {{0, {var(2), var(3)}}, {1, {var(1), var(2)}}, {2, {var(2), var(0)}}, {3, {var(3), var(4)}},
            {4, {var(5), var(3)}}, {5, {var(0), var(1)}}, {6, {var(4), var(5)}}}, {2, 3}),
      make("constant-ignored", {{"R", 3}, {"S", 2}, {"T", 2}}, 3,
           {{0, {var(0), var(1), Value{std::int64_t{1}}}}, {1, {var(1), var(2)}}, {2, {var(2), IgnoredColumn{}}}}, {0, 2}),
      make("repeated", {{"R", 2}, {"S", 2}}, 2, {{0, {var(0), var(0)}}, {1, {var(0), var(1)}}}, {1}),
  };
  for (const auto& f : fixtures) {
    const auto before_delta = delta_rows, before_snapshot = snapshot_rows;
    for (std::uint32_t seed = 1; seed <= 6; ++seed) run(f, seed * 104729U, seed <= 3 ? 300 : 1200, seed % 2 ? 3 : 4);
    std::cout << f.name << ": delta_rows=" << delta_rows - before_delta << " snapshot_rows=" << snapshot_rows - before_snapshot << "\n";
  }
  std::cout << "flat cyclic checks=" << checks << " delta_rows=" << delta_rows << " snapshot_rows=" << snapshot_rows << "\n";
  return 0;
} catch (const std::exception& failure) {
  std::cerr << "FAIL: " << failure.what() << "\n";
  return 1;
}
