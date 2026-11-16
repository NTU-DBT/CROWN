#include "crown/planner/meta_join_trees.hpp"

#include <algorithm>
#include <array>
#include <bit>
#include <compare>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace {
using namespace crown;
using crown::planner::Scope;
namespace meta = crown::planner::meta;
using Edge = std::pair<std::size_t, std::size_t>;
using Edges = std::vector<Edge>;
using Trees = std::set<Edges>;

void require(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

const char* stop_name(meta::EnumerationStop stop) {
  switch (stop) {
    case meta::EnumerationStop::complete: return "complete";
    case meta::EnumerationStop::invalid_metadata: return "invalid_metadata";
    case meta::EnumerationStop::metadata_limit: return "metadata_limit";
    case meta::EnumerationStop::work_limit: return "work_limit";
    case meta::EnumerationStop::fragment_limit: return "fragment_limit";
    case meta::EnumerationStop::cell_limit: return "cell_limit";
    case meta::EnumerationStop::output_limit: return "output_limit";
    case meta::EnumerationStop::invalid_expansion: return "invalid_expansion";
    case meta::EnumerationStop::noncanonical_metadata: return "noncanonical_metadata";
  }
  return "unknown";
}

Edges canonical(Edges edges) {
  for (auto& [a, b] : edges) if (b < a) std::swap(a, b);
  std::sort(edges.begin(), edges.end());
  return edges;
}

// Expected-family keys retain atom labels and a physical root. An undirected
// tree plus its root uniquely fixes all parent directions; minors never enter.
struct Key {
  std::size_t root;
  Edges edges;
  auto operator<=>(const Key&) const = default;
};
using Keys = std::set<Key>;

std::string describe(const Key& key) {
  std::ostringstream text;
  text << "root=" << key.root << ':';
  for (auto [a, b] : key.edges) text << ' ' << a << '-' << b;
  return text.str();
}

void same_keys(const Keys& actual, const Keys& expected, const std::string& label) {
  if (actual == expected) return;
  std::string detail;
  for (const auto& key : expected) if (!actual.contains(key)) { detail = " missing " + describe(key); break; }
  for (const auto& key : actual) if (!expected.contains(key)) { detail += " extra " + describe(key); break; }
  throw std::runtime_error(label + ": expected " + std::to_string(expected.size()) +
                           " rooted keys, got " + std::to_string(actual.size()) + detail);
}

// Independent graph oracle: breadth-first reachability restricted to allowed
// occurrence vertices. Production uses induced edge counts for RIP instead.
bool connected(const std::vector<bool>& allowed, const Edges& edges) {
  const auto first = std::find(allowed.begin(), allowed.end(), true);
  if (first == allowed.end()) return true;
  const auto start = static_cast<std::size_t>(first - allowed.begin());
  std::vector<bool> seen(allowed.size());
  std::vector<std::size_t> queue{start};
  seen[start] = true;
  for (std::size_t position = 0; position < queue.size(); ++position) {
    for (auto [a, b] : edges) {
      const auto next = a == queue[position] ? b : b == queue[position] ? a : allowed.size();
      if (next < allowed.size() && allowed[next] && !seen[next]) { seen[next] = true; queue.push_back(next); }
    }
  }
  return seen == allowed;
}

bool tree(std::size_t count, const Edges& edges) {
  if (!count || edges.size() != count - 1) return false;
  for (auto [a, b] : edges) if (a >= count || b >= count || a == b) return false;
  return connected(std::vector<bool>(count, true), edges);
}

// Ordinary join-tree definition, P3v2 §2.2 (PDF pp.4–5): every variable's
// containing occurrences must induce a connected subtree. No meta/GYO calls.
bool running_intersection(const std::vector<Scope>& scopes, const Edges& edges) {
  Scope variables;
  for (const auto& scope : scopes) variables.insert(scope.begin(), scope.end());
  for (auto variable : variables) {
    std::vector<bool> allowed;
    for (const auto& scope : scopes) allowed.push_back(scope.contains(variable));
    if (!connected(allowed, edges)) return false;
  }
  return true;
}

// Exhaust all labelled Prüfer codes, n<=5. Decode by absence from the remaining
// suffix, independently of production's degree counters/minimum-leaf decoder.
// P3v2 Appendix C.1.2, p.32 motivates labelled trees; its printed indices are
// not used here. A separate edge-subset oracle checks this decoder below.
Trees prufer_trees(std::size_t count) {
  require(count >= 1 && count <= 5, "Pruefer oracle exceeds its explicit small domain");
  if (count == 1) return {Edges{}};
  std::size_t combinations = 1;
  for (std::size_t i = 0; i < count - 2; ++i) combinations *= count;
  Trees trees;
  for (std::size_t encoded = 0; encoded < combinations; ++encoded) {
    std::vector<std::size_t> code(count - 2);
    auto residue = encoded;
    for (auto& label : code) { label = residue % count; residue /= count; }
    std::set<std::size_t> remaining;
    for (std::size_t i = 0; i < count; ++i) remaining.insert(i);
    Edges edges;
    for (std::size_t position = 0; position < code.size(); ++position) {
      const auto suffix = code.begin() + static_cast<std::ptrdiff_t>(position);
      const auto leaf = std::find_if(remaining.begin(), remaining.end(), [&](auto vertex) {
        return std::find(suffix, code.end(), vertex) == code.end();
      });
      require(leaf != remaining.end() && *leaf != code[position], "Pruefer suffix has no legal leaf");
      edges.emplace_back(*leaf, code[position]);
      remaining.erase(leaf);
    }
    require(remaining.size() == 2, "Pruefer decoder did not leave two vertices");
    edges.emplace_back(*remaining.begin(), *remaining.rbegin());
    edges = canonical(std::move(edges));
    require(tree(count, edges), "Pruefer code decoded to a non-tree");
    require(trees.insert(std::move(edges)).second, "two Pruefer codes decoded to one labelled tree");
  }
  return trees;
}

// This second topology oracle enumerates subsets of complete-graph edges,
// using at most ten edges (n<=5). It shares no Prüfer reduction/degree logic.
Trees edge_subset_trees(std::size_t count) {
  require(count >= 1 && count <= 5, "edge-subset oracle exceeds its small domain");
  Edges choices;
  for (std::size_t a = 0; a < count; ++a) for (std::size_t b = a + 1; b < count; ++b) choices.emplace_back(a, b);
  require(choices.size() <= 10, "test bit mask exceeds its explicit ten-edge bound");
  Trees trees;
  for (std::uint32_t bits = 0; bits < (std::uint32_t{1} << choices.size()); ++bits) {
    if (static_cast<std::size_t>(std::popcount(bits)) != count - 1) continue;
    Edges edges;
    for (std::size_t i = 0; i < choices.size(); ++i) if (bits & (std::uint32_t{1} << i)) edges.push_back(choices[i]);
    if (tree(count, edges)) trees.insert(std::move(edges));
  }
  return trees;
}

using Universe = std::array<Trees, 6>;
Universe checked_universe() {
  const std::array<std::size_t, 6> counts{0, 1, 1, 3, 16, 125};
  Universe result;
  std::size_t total = 0;
  for (std::size_t count = 1; count <= 5; ++count) {
    result[count] = prufer_trees(count);
    require(result[count] == edge_subset_trees(count), "Pruefer and edge-subset topology oracles disagree");
    require(result[count].size() == counts[count], "labelled Cayley count mismatch");
    total += result[count].size();
  }
  require(total == 146, "topology cross-check did not cover all 146 small labelled trees");
  return result;
}

Trees ordinary_oracle(const std::vector<Scope>& scopes, const Universe& universe) {
  require(!scopes.empty() && scopes.size() <= 5, "ordinary oracle requires one to five atoms");
  Trees expected;
  for (const auto& edges : universe[scopes.size()]) if (running_intersection(scopes, edges)) expected.insert(edges);
  return expected;
}

Keys all_roots(std::size_t count, const Trees& trees) {
  Keys result;
  for (const auto& edges : trees) for (std::size_t root = 0; root < count; ++root) result.insert({root, edges});
  return result;
}

struct Fixture { Catalog catalog; Query query; std::vector<Scope> scopes; };

// The supplied incidence lists determine expected scopes before any meta API.
// Dense renaming preserves incidence and atom order, including duplicate scopes.
Fixture query_for(const std::vector<std::vector<std::size_t>>& input) {
  Fixture fixture;
  std::map<std::size_t, VariableId> variables;
  for (const auto& scope : input) for (auto v : scope) variables.emplace(v, VariableId{0});
  for (auto& [label, id] : variables) {
    id = VariableId{fixture.query.variables.size()};
    fixture.query.variables.push_back({"v" + std::to_string(label), ScalarType::int64});
  }
  for (std::size_t i = 0; i < input.size(); ++i) {
    Table table{"T" + std::to_string(i), {}};
    Atom atom{"a" + std::to_string(i), TableId{i}, {}};
    Scope scope;
    for (std::size_t column = 0; column < input[i].size(); ++column) {
      table.columns.push_back({"c" + std::to_string(column), ScalarType::int64});
      const auto id = variables.at(input[i][column]);
      atom.terms.emplace_back(id); scope.insert(id);
    }
    fixture.catalog.tables.push_back(std::move(table));
    fixture.query.atoms.push_back(std::move(atom));
    fixture.scopes.push_back(std::move(scope));
  }
  validate(fixture.catalog, fixture.query);
  return fixture;
}

meta::Decomposition metadata_for(const Fixture& fixture, const std::string& label) {
  auto built = meta::construct(fixture.catalog, fixture.query);
  require(built.stop == meta::Stop::complete && built.decomposition, label + ": metadata construction failed");
  return std::move(*built.decomposition);
}

// Inspect every returned parent vector independently, before forming its key.
// Root-self is the only sentinel. All occurrence IDs must survive exactly once
// as vector positions; no metadata node, dummy or child-fragment root can leak.
Key inspect(const meta::JoinTree& actual, const Fixture& fixture, const std::string& label) {
  const auto count = fixture.scopes.size();
  require(actual.parent.size() == count && actual.root < count, label + ": wrong atom count or root");
  require(actual.parent[actual.root] == actual.root, label + ": missing root-self sentinel");
  Edges edges;
  for (std::size_t i = 0; i < count; ++i) {
    const auto parent = actual.parent[i];
    require(parent < count && (i == actual.root || parent != i), label + ": nonphysical/extra root parent");
    if (i != actual.root) edges.emplace_back(i, parent);
  }
  edges = canonical(std::move(edges));
  require(tree(count, edges), label + ": output parent graph is not a labelled tree");
  for (std::size_t start = 0; start < count; ++start) {
    auto position = start;
    std::size_t steps = 0;
    while (position != actual.root && steps < count) { position = actual.parent[position]; ++steps; }
    require(position == actual.root, label + ": output parent cycle misses root");
  }
  require(running_intersection(fixture.scopes, edges), label + ": output violates independent RIP");
  return {actual.root, std::move(edges)};
}

void within(const meta::Enumeration& run, const meta::EnumerationLimits& limits, const std::string& label) {
  require(run.usage.work <= limits.work && run.usage.fragments <= limits.fragments && run.usage.cells <= limits.cells &&
          run.usage.output_trees <= limits.output_trees, label + ": enumeration counter exceeded its grant");
  require(run.metadata.usage.work <= limits.metadata.work && run.metadata.usage.nodes <= limits.metadata.nodes &&
          run.metadata.usage.scope_cells <= limits.metadata.scope_cells, label + ": metadata counter exceeded its separate grant");
  require(run.usage.output_trees == run.trees.size(), label + ": published-tree counter differs from owned output");
}

std::vector<Key> output_keys(const meta::Enumeration& run, const Fixture& fixture, const std::string& label) {
  std::vector<Key> result;
  Keys unique;
  for (const auto& actual : run.trees) {
    auto key = inspect(actual, fixture, label);
    if (!unique.insert(key).second)
      throw std::runtime_error(label + ": duplicate rooted occurrence-labelled tree " + describe(key));
    result.push_back(std::move(key));
  }
  return result;
}

void complete_family(const meta::Enumeration& run, const Fixture& fixture, const Keys& expected,
                     const std::string& label) {
  require(run.metadata.stop == meta::Stop::complete && run.metadata.valid, label + ": metadata not admitted");
  require(run.stop == meta::EnumerationStop::complete, label + ": enumeration stopped at " + stop_name(run.stop));
  const auto ordered = output_keys(run, fixture, label);
  same_keys(Keys(ordered.begin(), ordered.end()), expected, label);
}

struct Case { std::string label; Fixture fixture; Trees expected; };

std::vector<Case> literal_cases(const Universe& universe) {
  std::vector<Case> cases;
  cases.push_back({"singleton/current root", query_for({{0}}), {Edges{}}});
  auto aliases = query_for({{0}, {0}, {0,1}});
  aliases.query.atoms[1].table = TableId{0};
  validate(aliases.catalog, aliases.query);
  cases.push_back({"duplicate scopes and table aliases", std::move(aliases),
                   {{{0,1},{0,2}}, {{0,1},{1,2}}, {{0,2},{1,2}}}});
  cases.push_back({"four equal scopes retain all labels", query_for({{0},{0},{0},{0}}), universe[4]});
  cases.push_back({"disconnected empty root", query_for({{0},{1}}), {{{0,1}}}});
  cases.push_back({"two disconnected pairs", query_for({{0,1},{0,2},{3,4},{3,5}}),
                   {{{0,1},{0,2},{2,3}}, {{0,1},{0,3},{2,3}},
                    {{0,1},{1,2},{2,3}}, {{0,1},{1,3},{2,3}}}});
  cases.push_back({"special chi equals original chi", query_for({{0},{0,1}}), {{{0,1}}}});
  cases.push_back({"nested overlap masks1,3,3", query_for({{0},{0,1},{0,1}}),
                   {{{0,1},{1,2}}, {{0,2},{1,2}}}});
  // Full-interface nonroot minor needs a typed external parent. Removing its
  // dummy must preserve the third case, where both A and B attach to C.
  cases.push_back({"external-parent dummy", query_for({{0,1},{0,2},{0,3,4},{3,5},{5}}),
                   {{{0,1},{0,2},{2,3},{3,4}}, {{0,1},{1,2},{2,3},{3,4}},
                    {{0,2},{1,2},{2,3},{3,4}}}});
  cases.push_back({"early disconnected root", query_for({{0},{1,2},{2,3},{3,4},{4,5}}),
                   {{{0,1},{1,2},{2,3},{3,4}}, {{0,2},{1,2},{2,3},{3,4}},
                    {{0,3},{1,2},{2,3},{3,4}}, {{0,4},{1,2},{2,3},{3,4}}}});
  // P3v2 Examples 4.4/4.11, pp.10–14: edges 01,12,23 are forced by x2/x3/x4;
  // R5 may attach to any of four physical hosts, including the lower branches.
  cases.push_back({"P3 Example4.4 rebranching", query_for({{0,1,5},{0,1,2,6},{0,2,3,7},{0,3,8},{0,4}}),
                   {{{0,1},{0,4},{1,2},{2,3}}, {{0,1},{1,2},{1,4},{2,3}},
                    {{0,1},{1,2},{2,3},{2,4}}, {{0,1},{1,2},{2,3},{3,4}}}});
  // P3v2 Example 4.6, pp.11–12: anchors 0/4 must be adjacent. Each remaining
  // occurrence independently chooses either anchor, giving 8 unrooted/40 roots.
  cases.push_back({"P3 Example4.6 special preservation", query_for({{0,1,2,3},{0,1,4},{0,2,5},{1,2,6},{0,1,2,7}}),
                   {{{0,1},{0,2},{0,3},{0,4}}, {{0,1},{0,2},{0,4},{3,4}},
                    {{0,1},{0,3},{0,4},{2,4}}, {{0,1},{0,4},{2,4},{3,4}},
                    {{0,2},{0,3},{0,4},{1,4}}, {{0,2},{0,4},{1,4},{3,4}},
                    {{0,3},{0,4},{1,4},{2,4}}, {{0,4},{1,4},{2,4},{3,4}}}});
  // Distinct y/z pairs force 01 and 23. Three blocks of sizes 2,2,1 have
  // 8+8+4 endpoint combinations across their three labelled skeletons.
  Trees endpoints, variants;
  for (const auto& edges : universe[5]) {
    if (std::binary_search(edges.begin(), edges.end(), Edge{0,1}) &&
        std::binary_search(edges.begin(), edges.end(), Edge{2,3})) endpoints.insert(edges);
    std::size_t internal = 0;
    for (auto [a, b] : edges) internal += a < 3 && b < 3;
    if (internal == 2) variants.insert(edges);
  }
  require(endpoints.size() == 20 && variants.size() == 45, "hand-derived Cartesian/variant counts disagree");
  cases.push_back({"Cartesian endpoints on multiple skeleton edges", query_for({{0,1},{0,1},{0,2},{0,2},{0}}), std::move(endpoints)});
  // The three y-occurrences have three internal trees; the two remaining
  // x-occurrences can rebranch. This retains all 45 unrooted/225 rooted choices.
  cases.push_back({"retained child variants", query_for({{0,1},{0,1},{0,1},{0},{0}}), std::move(variants)});
  require(cases.size() == 13, "literal fixture inventory changed");
  return cases;
}

// Metadata node indices are separate from atom labels. Reverse only the former
// and remap parent/root indices; ordinary output families must stay unchanged.
meta::Decomposition reversed_metadata(const meta::Decomposition& original) {
  auto result = original;
  const auto count = original.nodes.size();
  for (std::size_t i = 0; i < count; ++i) {
    result.nodes[count - 1 - i] = original.nodes[i];
    if (original.nodes[i].parent) result.nodes[count - 1 - i].parent = count - 1 - *original.nodes[i].parent;
  }
  result.root = count - 1 - original.root;
  return result;
}

void literal_families(const std::vector<Case>& cases, const Universe& universe) {
  const std::array<std::size_t, 13> rooted_counts{1,9,64,2,16,2,6,15,20,20,40,100,225};
  for (std::size_t i = 0; i < cases.size(); ++i) {
    const auto& test = cases[i];
    const auto expected = all_roots(test.fixture.scopes.size(), test.expected);
    require(expected.size() == rooted_counts[i], test.label + ": literal rooted count changed");
    same_keys(all_roots(test.fixture.scopes.size(), ordinary_oracle(test.fixture.scopes, universe)), expected,
              test.label + " independent/literal oracle agreement");
    const auto metadata = metadata_for(test.fixture, test.label);
    const auto run = meta::enumerate(test.fixture.catalog, test.fixture.query, metadata);
    within(run, {}, test.label);
    complete_family(run, test.fixture, expected, test.label);
    const auto remapped = meta::enumerate(test.fixture.catalog, test.fixture.query, reversed_metadata(metadata));
    within(remapped, {}, test.label + " reversed metadata");
    complete_family(remapped, test.fixture, expected, test.label + " reversed metadata");
  }
  // Ordinary body coverage is independent of the later CROWN/head admission.
  auto projected = cases.at(9).fixture;
  projected.query.head = {{VariableId{0}, "x"}};
  const auto metadata = metadata_for(projected, "projected ordinary body");
  const auto run = meta::enumerate(projected.catalog, projected.query, metadata);
  complete_family(run, projected, all_roots(5, cases.at(9).expected), "head-independent ordinary family");
}

void metadata_controls(const Case& test) {
  const auto good = metadata_for(test.fixture, test.label);
  auto bad = good;
  bad.root = bad.nodes.size();
  auto run = meta::enumerate(test.fixture.catalog, test.fixture.query, bad);
  require(run.stop == meta::EnumerationStop::invalid_metadata && !run.metadata.valid && run.trees.empty(),
          "invalid root must fail metadata admission before expansion");
  const auto triangle = query_for({{0,1},{1,2},{0,2}});
  const Scope ab{VariableId{0},VariableId{1}}, bc{VariableId{1},VariableId{2}}, ac{VariableId{0},VariableId{2}};
  const meta::Decomposition hidden_cycle{{{0,ab,ab,3}, {1,bc,bc,3}, {2,ac,ac,3},
                                         {{}, {VariableId{0},VariableId{1},VariableId{2}}, {}, {}}}, 3};
  run = meta::enumerate(triangle.catalog, triangle.query, hidden_cycle);
  require(run.stop == meta::EnumerationStop::invalid_metadata && !run.metadata.valid && run.trees.empty(),
          "unguarded minor must not hide a cyclic input from enumeration");
  const auto empty = query_for({});
  run = meta::enumerate(empty.catalog, empty.query, {});
  require(run.stop == meta::EnumerationStop::invalid_metadata && run.metadata.stop == meta::Stop::empty_body && run.trees.empty(),
          "empty body must retain its explicit metadata domain stop");
  const auto nullary = query_for({{}});
  const meta::Decomposition nullary_tree{{{0, {}, {}, {}}}, 0};
  run = meta::enumerate(nullary.catalog, nullary.query, nullary_tree);
  require(run.stop == meta::EnumerationStop::invalid_metadata && run.metadata.stop == meta::Stop::nullary_occurrence && run.trees.empty(),
          "nullary body must retain its explicit metadata domain stop");

  const auto baseline = meta::enumerate(test.fixture.catalog, test.fixture.query, good);
  require(baseline.stop == meta::EnumerationStop::complete && baseline.metadata.valid, "metadata grant baseline failed");
  meta::EnumerationLimits exact;
  exact.metadata = {baseline.metadata.usage.work, baseline.metadata.usage.nodes, baseline.metadata.usage.scope_cells};
  require(exact.metadata.work && exact.metadata.nodes && exact.metadata.scope_cells,
          "separate metadata grant fixture must consume each dimension");
  run = meta::enumerate(test.fixture.catalog, test.fixture.query, good, exact);
  require(run.stop == meta::EnumerationStop::complete, "exact separate metadata grants must complete");
  for (const auto stop : {meta::Stop::work_limit, meta::Stop::node_limit, meta::Stop::cell_limit}) {
    for (bool zero : {false, true}) {
      auto limits = exact;
      if (stop == meta::Stop::work_limit) limits.metadata.work = zero ? 0 : limits.metadata.work - 1;
      if (stop == meta::Stop::node_limit) limits.metadata.nodes = zero ? 0 : limits.metadata.nodes - 1;
      if (stop == meta::Stop::cell_limit) limits.metadata.scope_cells = zero ? 0 : limits.metadata.scope_cells - 1;
      run = meta::enumerate(test.fixture.catalog, test.fixture.query, good, limits);
      require(run.stop == meta::EnumerationStop::metadata_limit && run.metadata.stop == stop && !run.metadata.valid && run.trees.empty(),
              "metadata exhaustion must stop separately without publishing a family");
      require(!run.usage.work && !run.usage.fragments && !run.usage.cells && !run.usage.output_trees,
              "expansion must not consume its grants before metadata admission succeeds");
      within(run, limits, "separate metadata grant");
    }
  }
}

void valid_prefix(const meta::Enumeration& run, const Fixture& fixture, const std::vector<Key>& baseline,
                  const meta::EnumerationLimits& limits, const std::string& label) {
  require(run.metadata.stop == meta::Stop::complete && run.metadata.valid, label + ": metadata grant was conflated with expansion");
  within(run, limits, label);
  const auto prefix = output_keys(run, fixture, label);
  require(prefix.size() <= baseline.size() && std::equal(prefix.begin(), prefix.end(), baseline.begin()),
          label + ": partial output is not a valid prefix of the same completed enumeration");
}

// These budgets count selected checkpoints, cumulative fragments/vector cells
// and published trees. Exact grants say nothing about allocator bytes or CPU.
void expansion_limits(const Case& test) {
  const auto metadata = metadata_for(test.fixture, test.label);
  const auto baseline = meta::enumerate(test.fixture.catalog, test.fixture.query, metadata);
  const auto expected = all_roots(test.fixture.scopes.size(), test.expected);
  complete_family(baseline, test.fixture, expected, "expansion grant baseline");
  const auto keys = output_keys(baseline, test.fixture, "expansion baseline keys");
  require(keys.size() > 1 && baseline.usage.work && baseline.usage.fragments && baseline.usage.cells,
          "resource fixture must exercise every expansion grant");
  meta::EnumerationLimits exact;
  exact.metadata = {baseline.metadata.usage.work, baseline.metadata.usage.nodes, baseline.metadata.usage.scope_cells};
  exact.work = baseline.usage.work; exact.fragments = baseline.usage.fragments; exact.cells = baseline.usage.cells;
  exact.output_trees = baseline.trees.size();
  auto run = meta::enumerate(test.fixture.catalog, test.fixture.query, metadata, exact);
  complete_family(run, test.fixture, expected, "exact expansion grants");
  within(run, exact, "exact expansion grants");
  for (const auto stop : {meta::EnumerationStop::work_limit, meta::EnumerationStop::fragment_limit, meta::EnumerationStop::cell_limit}) {
    auto limits = exact;
    if (stop == meta::EnumerationStop::work_limit) --limits.work;
    if (stop == meta::EnumerationStop::fragment_limit) --limits.fragments;
    if (stop == meta::EnumerationStop::cell_limit) --limits.cells;
    run = meta::enumerate(test.fixture.catalog, test.fixture.query, metadata, limits);
    require(run.stop == stop, std::string("one-short expansion grant returned ") + stop_name(run.stop));
    valid_prefix(run, test.fixture, keys, limits, "one-short expansion grant");
    if (stop == meta::EnumerationStop::work_limit)
      require(!run.trees.empty(), "late work exhaustion must retain already published rooted trees");
    auto zero = meta::EnumerationLimits{};
    if (stop == meta::EnumerationStop::work_limit) zero.work = 0;
    if (stop == meta::EnumerationStop::fragment_limit) zero.fragments = 0;
    if (stop == meta::EnumerationStop::cell_limit) zero.cells = 0;
    run = meta::enumerate(test.fixture.catalog, test.fixture.query, metadata, zero);
    require(run.stop == stop && run.trees.empty(), "zero expansion grant must stop before publication");
    valid_prefix(run, test.fixture, keys, zero, "zero expansion grant");
  }
  for (const auto cap : {std::size_t{0}, std::size_t{1}, keys.size() - 1, keys.size()}) {
    auto limits = exact; limits.output_trees = cap;
    run = meta::enumerate(test.fixture.catalog, test.fixture.query, metadata, limits);
    const auto stop = cap == keys.size() ? meta::EnumerationStop::complete : meta::EnumerationStop::output_limit;
    require(run.stop == stop && run.trees.size() == cap, "output grant must preserve exactly its admitted rooted prefix");
    valid_prefix(run, test.fixture, keys, limits, "output cap");
  }
  // Raising grants is a new call, not a continuation and not a duplicated prefix.
  run = meta::enumerate(test.fixture.catalog, test.fixture.query, metadata);
  complete_family(run, test.fixture, expected, "fresh enumeration after resource stops");
}

// A canonical root is sufficient for inverse fibers. This mode must preserve
// every undirected tree without allocating the discarded n-1 orientations.
void canonical_families(const std::vector<Case>& cases) {
  for (const auto& test : cases) {
    const auto metadata = metadata_for(test.fixture, test.label);
    meta::EnumerationLimits limits; limits.all_roots = false;
    limits.output_trees = test.expected.size();
    const auto run = meta::enumerate(test.fixture.catalog, test.fixture.query, metadata, limits);
    require(run.stop == meta::EnumerationStop::complete && !run.all_roots && run.trees.size() == test.expected.size(),
            test.label + ": canonical mode lost undirected coverage or kept discarded roots");
    Keys actual, expected;
    for (const auto& tree : run.trees) {
      const auto key = inspect(tree, test.fixture, test.label);
      require(key.root == 0 && actual.insert(key).second, test.label + ": canonical root or uniqueness");
    }
    for (const auto& edges : test.expected) expected.insert({0, edges});
    same_keys(actual, expected, test.label + " canonical exact family");
    auto invalid = metadata; invalid.root = invalid.nodes.size();
    const auto rejected = meta::enumerate(test.fixture.catalog, test.fixture.query, invalid, limits);
    require(rejected.stop == meta::EnumerationStop::invalid_metadata && !rejected.all_roots,
            "invalid metadata lost requested root mode");
    limits.work = 0;
    const auto stopped = meta::enumerate(test.fixture.catalog, test.fixture.query, metadata, limits);
    require(stopped.stop == meta::EnumerationStop::work_limit && !stopped.all_roots && stopped.trees.empty(),
            "resource stop lost requested root mode");
  }
}

// Literal Definition4.3 permits this layout, but Algorithm1 minor-first
// parenting does not. Expanding it used to report32/64 rooted trees complete.
void noncanonical_parenting(const Universe& universe) {
  const auto f = query_for({{0,1},{0,2},{0,3},{0,4}});
  const meta::Decomposition m{{
      {0,{VariableId{0},VariableId{1}},{},{}},
      {1,{VariableId{0},VariableId{2}},{VariableId{0}},4},
      {2,{VariableId{0},VariableId{3}},{VariableId{0}},4},
      {3,{VariableId{0},VariableId{4}},{VariableId{0}},0},
      {{},{VariableId{0}},{VariableId{0}},0}},0};
  require(meta::check(f.catalog,f.query,m).valid,"noncanonical literal no longer satisfies structural checker");
  const auto expected = all_roots(4,ordinary_oracle(f.scopes,universe));
  require(expected.size() == 64,"noncanonical counterexample's independent family");
  const auto rejected = meta::enumerate(f.catalog,f.query,m);
  require(rejected.stop == meta::EnumerationStop::noncanonical_metadata && rejected.metadata.valid && rejected.trees.empty(),
          "noncanonical graph again labeled a complete ordinary family");
  // The query remains supported via its actual constructed representation.
  const auto canonical = metadata_for(f,"canonical replacement");
  complete_family(meta::enumerate(f.catalog,f.query,canonical),f,expected,"canonical replacement");
}

void exhaustive_families(const Universe& universe) {
  std::size_t tested = 0, acyclic = 0, cyclic = 0, unrooted = 0, rooted = 0;
  // All 3,875 multisets of 1..4 nonempty scopes over 4 variables. Forward/reverse
  // invocations retain labels; they are not all possible occurrence orders.
  for (std::size_t count = 1; count <= 4; ++count) {
    std::size_t combinations = 1;
    for (std::size_t i = 0; i < count; ++i) combinations *= 15;
    for (std::size_t code = 0; code < combinations; ++code) {
      std::vector<std::size_t> masks(count);
      auto residue = code;
      for (auto& mask : masks) { mask = residue % 15 + 1; residue /= 15; }
      if (!std::is_sorted(masks.begin(), masks.end())) continue;
      std::vector<std::vector<std::size_t>> edges;
      for (auto mask : masks) {
        std::vector<std::size_t> scope;
        for (std::size_t variable = 0; variable < 4; ++variable)
          if (mask & (std::size_t{1} << variable)) scope.push_back(variable);
        edges.push_back(std::move(scope));
      }
      for (int order = 0; order != 2; ++order) {
        if (order) std::reverse(edges.begin(), edges.end());
        const auto fixture = query_for(edges);
        const auto ordinary = ordinary_oracle(fixture.scopes, universe);
        const auto expected = all_roots(count, ordinary);
        const auto label = "corpus n=" + std::to_string(count) + " code=" + std::to_string(code) + " order=" + std::to_string(order);
        const auto built = meta::construct(fixture.catalog, fixture.query);
        if (ordinary.empty()) {
          ++cyclic;
          require(built.stop == meta::Stop::cyclic && !built.decomposition, label + ": no ordinary join tree but constructor did not stop cyclic");
        } else {
          ++acyclic;
          require(built.stop == meta::Stop::complete && built.decomposition, label + ": ordinary oracle found trees but metadata construction failed");
          const auto run = meta::enumerate(fixture.catalog, fixture.query, *built.decomposition);
          within(run, {}, label);
          complete_family(run, fixture, expected, label);
          rooted += run.trees.size();
          unrooted += ordinary.size();
        }
        ++tested;
      }
    }
  }
  require(tested == 7750 && acyclic == 7114 && cyclic == 636 && unrooted == 28814 && rooted == 112286,
          "independent corpus totals changed or coverage was skipped");
  std::cout << tested << " exact ordinary families (" << acyclic << " acyclic, " << cyclic << " cyclic), "
            << rooted << " rooted keys checked independently\n";
}
} // namespace

int main() {
  try {
    const auto universe = checked_universe();
    const auto cases = literal_cases(universe);
    literal_families(cases, universe);
    metadata_controls(cases.at(7));
    expansion_limits(cases.at(11));
    canonical_families(cases);
    noncanonical_parenting(universe);
    exhaustive_families(universe);
    return 0;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
