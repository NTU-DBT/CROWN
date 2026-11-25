// FlatCountRuntime against a brute-force bag-join oracle: per physical event,
// the net (before, after) count of every changed group, and full snapshots.
#pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#include "crown/runtime/flat_count.hpp"
#include "crown/planner/lower.hpp"
#include "crown/planner/oracle.hpp"

#include <algorithm>
#include <functional>
#include <iostream>
#include <map>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

namespace {
using namespace crown;
std::uint64_t checks = 0, changes = 0, groups = 0;
void check(bool value, const std::string& message) {
  if (!value) throw std::runtime_error(message);
  ++checks;
}
using Key = std::vector<std::int64_t>;
using Counts = std::map<Key, std::uint64_t>;

struct Shape {
  std::string name;
  std::vector<std::size_t> widths;  // per table
  std::size_t variables;
  std::vector<std::pair<std::size_t, std::vector<std::size_t>>> atoms;  // table, variable per column
  std::vector<std::size_t> head;
};

Counts oracle(const Shape& shape, const std::vector<std::map<Key, std::uint64_t>>& bags) {
  Counts out;
  std::vector<std::int64_t> value(shape.variables);
  std::vector<bool> bound(shape.variables, false);
  std::function<void(std::size_t, std::uint64_t)> go = [&](std::size_t a, std::uint64_t weight) {
    if (a == shape.atoms.size()) {
      Key key;
      for (const auto v : shape.head) key.push_back(value[v]);
      out[key] += weight;
      return;
    }
    const auto& [table, vars] = shape.atoms[a];
    for (const auto& [row, multiplicity] : bags[table]) {
      std::vector<std::size_t> newly;
      bool ok = true;
      for (std::size_t c = 0; c < vars.size() && ok; ++c) {
        const auto v = vars[c];
        if (bound[v]) ok = value[v] == row[c];
        else { bound[v] = true; value[v] = row[c]; newly.push_back(v); }
      }
      if (ok) go(a + 1, weight * multiplicity);
      for (const auto v : newly) bound[v] = false;
    }
  };
  go(0, 1);
  return out;
}

struct Collector {
  std::map<Key, std::pair<std::uint64_t, std::uint64_t>> net;  // first before, last after
  Counts all;
  static void change(void* context, const std::int64_t* key, std::size_t size, std::uint64_t before, std::uint64_t after) {
    auto& self = *static_cast<Collector*>(context);
    Key k(key, key + size);
    auto [it, fresh] = self.net.try_emplace(k, before, after);
    if (!fresh) {
      if (it->second.second != before) throw std::runtime_error("route changes do not chain");
      it->second.second = after;
    }
  }
  static void snapshot(void* context, const std::int64_t* key, std::size_t size, std::uint64_t before, std::uint64_t after) {
    auto& self = *static_cast<Collector*>(context);
    if (before != 0) throw std::runtime_error("snapshot reported a before count");
    if (!self.all.emplace(Key(key, key + size), after).second) throw std::runtime_error("snapshot repeated a group");
  }
};

void run(const Shape& shape, bool delta, std::uint32_t seed, int events, int domain) {
  Catalog catalog;
  for (std::size_t t = 0; t < shape.widths.size(); ++t) {
    Table table{"t" + std::to_string(t), {}};
    for (std::size_t c = 0; c < shape.widths[t]; ++c) table.columns.push_back({"c" + std::to_string(c), ScalarType::int64});
    catalog.tables.push_back(std::move(table));
  }
  Query query;
  for (std::size_t v = 0; v < shape.variables; ++v) query.variables.push_back({"v" + std::to_string(v), ScalarType::int64});
  std::size_t occurrence = 0;
  for (const auto& [table, vars] : shape.atoms) {
    std::vector<Term> terms;
    for (const auto v : vars) terms.emplace_back(std::in_place_type<VariableId>, VariableId{v});
    query.atoms.push_back(Atom{"o" + std::to_string(occurrence++), TableId{table}, std::move(terms)});
  }
  for (const auto v : shape.head) query.head.push_back({VariableId{v}, "h" + std::to_string(v)});
  const auto selected = planner::minimum_tree(catalog, query);
  check(selected.tree.has_value(), shape.name + ": no free-connex tree");
  const auto program = CompiledProgram::standalone(planner::lower_tree(catalog, query, *selected.tree));
  const auto reason = runtime::FlatCountRuntime::unsupported(program);
  check(reason.empty(), shape.name + ": unsupported: " + reason);
  runtime::FlatCountRuntime flat(program, {delta});
  std::vector<std::map<Key, std::uint64_t>> bags(shape.widths.size());
  std::mt19937 random(seed);
  Counts previous;
  for (int event = 0; event < events; ++event) {
    const auto t = std::uniform_int_distribution<std::size_t>(0, shape.widths.size() - 1)(random);
    Key row;
    std::int64_t sign = 1;
    if (!bags[t].empty() && std::uniform_int_distribution<int>(0, 9)(random) < 4) {
      auto it = bags[t].begin();
      std::advance(it, std::uniform_int_distribution<std::size_t>(0, bags[t].size() - 1)(random));
      row = it->first;
      sign = -1;
    } else {
      for (std::size_t c = 0; c < shape.widths[t]; ++c) row.push_back(std::uniform_int_distribution<int>(0, domain - 1)(random));
    }
    if (sign > 0) ++bags[t][row];
    else if (--bags[t][row] == 0) bags[t].erase(row);
    Collector collector;
    flat.apply(TableId{t}, sign, row.data(), {&collector, &Collector::change});
    const auto current = oracle(shape, bags);
    if (delta) {
      std::map<Key, std::pair<std::uint64_t, std::uint64_t>> expected;
      for (const auto& [key, count] : previous) {
        const auto found = current.find(key);
        const auto after = found == current.end() ? 0 : found->second;
        if (after != count) expected[key] = {count, after};
      }
      for (const auto& [key, count] : current) if (!previous.contains(key)) expected[key] = {0, count};
      std::erase_if(collector.net, [](const auto& item) { return item.second.first == item.second.second; });
      check(expected == collector.net, shape.name + " seed " + std::to_string(seed) + " group changes differ at event " +
          std::to_string(event) + " (" + std::to_string(expected.size()) + " vs " + std::to_string(collector.net.size()) + ")");
      changes += expected.size();
    } else {
      check(collector.net.empty(), "maintenance mode reported changes");
    }
    if (event % 5 == 0 || event + 1 == events) {
      Collector all;
      flat.snapshot({&all, &Collector::snapshot});
      check(all.all == current, shape.name + " snapshot differs at event " + std::to_string(event));
      groups += current.size();
    }
    previous = current;
  }
}
}  // namespace

int main() try {
  const std::vector<Shape> shapes = {
      {"star", {2, 2, 2, 2}, 5, {{0, {0, 1}}, {1, {0, 2}}, {2, {0, 3}}, {3, {0, 4}}}, {0}},
      {"path3-middle", {2, 2, 2}, 4, {{0, {0, 1}}, {1, {1, 2}}, {2, {2, 3}}}, {1, 2}},
      {"path3-left", {2, 2, 2}, 4, {{0, {0, 1}}, {1, {1, 2}}, {2, {2, 3}}}, {0, 1}},
      {"path3-full", {2, 2, 2}, 4, {{0, {0, 1}}, {1, {1, 2}}, {2, {2, 3}}}, {0, 1, 2, 3}},
      {"path4-middle", {2, 2, 2, 2}, 5, {{0, {0, 1}}, {1, {1, 2}}, {2, {2, 3}}, {3, {3, 4}}}, {1, 2, 3}},
      {"total", {2, 2}, 3, {{0, {0, 1}}, {1, {1, 2}}}, {}},
      {"self-join", {2}, 3, {{0, {0, 1}}, {0, {1, 2}}}, {1}},
      {"self-join-full", {2}, 3, {{0, {0, 1}}, {0, {1, 2}}}, {0, 1, 2}},
      {"branch", {2, 2, 1, 1}, 3, {{0, {0, 1}}, {1, {1, 2}}, {2, {0}}, {3, {2}}}, {0, 1, 2}},
  };
  for (const auto& shape : shapes)
    for (const bool delta : {false, true})
      for (std::uint32_t seed = 1; seed <= 4; ++seed)
        run(shape, delta, seed * 7907U + delta, seed <= 2 ? 200 : 450, seed % 2 ? 3 : 4);
  std::cout << "flat count checks=" << checks << " changes=" << changes << " groups=" << groups << "\n";
  return 0;
} catch (const std::exception& failure) {
  std::cerr << "FAIL: " << failure.what() << "\n";
  return 1;
}
