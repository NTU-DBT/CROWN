#include "crown/planner/meta.hpp"

#include <algorithm>
#include <cstdint>
#include <initializer_list>
#include <iostream>
#include <map>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace {
using namespace crown;
using crown::planner::Scope;
namespace meta = crown::planner::meta;

void require(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

const char* stop_name(meta::Stop stop) {
  switch (stop) {
    case meta::Stop::complete: return "complete";
    case meta::Stop::empty_body: return "empty_body";
    case meta::Stop::nullary_occurrence: return "nullary_occurrence";
    case meta::Stop::cyclic: return "cyclic";
    case meta::Stop::invalid_decomposition: return "invalid_decomposition";
    case meta::Stop::work_limit: return "work_limit";
    case meta::Stop::node_limit: return "node_limit";
    case meta::Stop::cell_limit: return "cell_limit";
  }
  return "unknown";
}

Scope scope(std::initializer_list<std::size_t> variables) {
  Scope result;
  for (auto variable : variables) result.insert(VariableId{variable});
  return result;
}

struct Fixture {
  Catalog catalog;
  Query query;
  std::vector<Scope> scopes;
};

// Build a valid direct-CQ input. Sparse test labels are renamed densely; each
// atom retains its own occurrence index even when two scopes or tables agree.
Fixture query_for(const std::vector<std::vector<std::size_t>>& input) {
  Fixture fixture;
  std::map<std::size_t, VariableId> variables;
  for (const auto& edge : input) for (auto variable : edge) variables.emplace(variable, VariableId{0});
  for (auto& [label, id] : variables) {
    id = VariableId{fixture.query.variables.size()};
    fixture.query.variables.push_back({"v" + std::to_string(label), ScalarType::int64});
  }
  for (std::size_t i = 0; i < input.size(); ++i) {
    Table table{"T" + std::to_string(i), {}};
    Atom atom{"a" + std::to_string(i), TableId{i}, {}};
    Scope edge;
    for (std::size_t column = 0; column < input[i].size(); ++column) {
      table.columns.push_back({"c" + std::to_string(column), ScalarType::int64});
      const auto id = variables.at(input[i][column]);
      atom.terms.emplace_back(id);
      edge.insert(id);
    }
    fixture.catalog.tables.push_back(std::move(table));
    fixture.query.atoms.push_back(std::move(atom));
    fixture.scopes.push_back(std::move(edge));
  }
  validate(fixture.catalog, fixture.query);
  return fixture;
}

meta::Node node(std::optional<std::size_t> occurrence,
                std::initializer_list<std::size_t> chi,
                std::initializer_list<std::size_t> kappa,
                std::optional<std::size_t> parent = {}) {
  return {occurrence, scope(chi), scope(kappa), parent};
}

bool covers(const Scope& large, const Scope& small) {
  return std::includes(large.begin(), large.end(), small.begin(), small.end());
}

// Inspect actual fields rather than treating either API's success flag as a
// certificate. Definition 4.3 (P3v2, PDF p.10): labelled coverage, tree/RIP,
// exact outside-subtree kappa, highest parent, and the unique equal-kappa hub.
// Edge counts in each variable-induced forest check RIP without reduction.
void inspect(const Fixture& fixture, const meta::Decomposition& m, const std::string& label) {
  const auto count = m.nodes.size();
  require(count != 0 && m.root < count, label + ": missing root");
  std::vector<bool> occurrences(fixture.scopes.size());
  std::map<Scope, std::size_t> minors;
  std::map<Scope, std::size_t> interfaces;
  for (std::size_t i = 0; i < count; ++i) {
    const auto& p = m.nodes[i];
    for (auto variable : p.scope)
      require(variable.value < fixture.query.variables.size(), label + ": scope outside query domain");
    require(covers(p.scope, p.interface), label + ": interface outside node scope");
    if (p.occurrence) {
      const auto occurrence = *p.occurrence;
      require(occurrence < occurrences.size() && !occurrences[occurrence], label + ": occurrence identity lost");
      occurrences[occurrence] = true;
      require(p.scope == fixture.scopes[occurrence], label + ": physical scope changed");
    } else {
      require(minors.emplace(p.scope, i).second, label + ": duplicate minor scope");
    }
    ++interfaces[p.interface];
    if (i == m.root) {
      require(!p.parent && p.interface.empty(), label + ": root has parent or interface");
    } else {
      require(p.parent && *p.parent < count && *p.parent != i, label + ": invalid parent");
    }
  }
  require(std::all_of(occurrences.begin(), occurrences.end(), [](bool present) { return present; }),
          label + ": original occurrence omitted");

  // subtree[a][b] records ancestry by bounded parent walks, independently of
  // the implementation's DFS and descendant predicate.
  std::vector<std::vector<bool>> subtree(count, std::vector<bool>(count));
  for (std::size_t start = 0; start < count; ++start) {
    auto current = start;
    std::size_t visited = 0;
    for (;;) {
      require(++visited <= count, label + ": parent cycle");
      subtree[current][start] = true;
      if (!m.nodes[current].parent) break;
      current = *m.nodes[current].parent;
    }
    require(current == m.root, label + ": node cannot reach root");
  }
  for (std::size_t variable = 0; variable < fixture.query.variables.size(); ++variable) {
    const auto id = VariableId{variable};
    std::size_t vertices = 0, edges = 0;
    for (const auto& p : m.nodes) if (p.scope.contains(id)) {
      ++vertices;
      if (p.parent && m.nodes[*p.parent].scope.contains(id)) ++edges;
    }
    require(vertices != 0 && edges + 1 == vertices, label + ": running intersection broken");
  }
  for (std::size_t i = 0; i < count; ++i) {
    const auto& p = m.nodes[i];
    Scope outside;
    for (std::size_t j = 0; j < count; ++j) if (!subtree[i][j])
      outside.insert(m.nodes[j].scope.begin(), m.nodes[j].scope.end());
    Scope actual;
    for (auto variable : p.scope) if (outside.contains(variable)) actual.insert(variable);
    require(actual == p.interface, label + ": kappa differs from actual outside scope");
    if (p.parent) {
      const auto parent = *p.parent;
      require(covers(m.nodes[parent].scope, p.interface), label + ": parent omits interface");
      if (p.interface != m.nodes[parent].scope)
        for (std::size_t j = 0; j < count; ++j) if (!subtree[parent][j])
          require(!covers(m.nodes[j].scope, p.interface), label + ": parent is not highest eligible node");
    }
  }
  for (const auto& [interface, members] : interfaces) if (members >= 2)
    require(minors.contains(interface), label + ": equal interfaces lack canonical minor");
}

// Match by lambda (physical occurrence) or chi (minor), so an implementation
// may number its nodes freely. The expected fields below are hand-derived.
void expect_structure(const meta::Decomposition& actual, const meta::Decomposition& expected,
                      const std::string& label) {
  require(actual.nodes.size() == expected.nodes.size(), label + ": wrong node count");
  std::vector<std::size_t> matching(expected.nodes.size());
  for (std::size_t i = 0; i < expected.nodes.size(); ++i) {
    const auto& wanted = expected.nodes[i];
    std::optional<std::size_t> found;
    for (std::size_t j = 0; j < actual.nodes.size(); ++j) {
      const auto& candidate = actual.nodes[j];
      if (candidate.occurrence != wanted.occurrence || (!wanted.occurrence && candidate.scope != wanted.scope)) continue;
      require(!found, label + ": ambiguous node identity");
      found = j;
    }
    require(found.has_value(), label + ": expected occurrence or minor missing");
    matching[i] = *found;
    require(actual.nodes[*found].scope == wanted.scope && actual.nodes[*found].interface == wanted.interface,
            label + ": wrong chi or kappa");
  }
  require(actual.root == matching[expected.root], label + ": wrong root identity");
  for (std::size_t i = 0; i < expected.nodes.size(); ++i) {
    const auto expected_parent = expected.nodes[i].parent;
    const auto actual_parent = actual.nodes[matching[i]].parent;
    require(expected_parent ? actual_parent == std::optional<std::size_t>{matching[*expected_parent]} : !actual_parent,
            label + ": wrong parent identity");
  }
}

struct Case { std::string name; Fixture fixture; meta::Decomposition expected; };

std::vector<Case> paper_cases() {
  std::vector<Case> cases;
  // Algorithm 1, p.12: a scope-interned special{x} reappears in a later round.
  // Its initial kappa={x} must finally become empty; Y/Z keep frozen y/z ears.
  cases.push_back({"minor reactivation", query_for({{0,1}, {0,2}, {0,3}, {0,4}, {3,5}, {4,6}}),
                   {{node(0,{0,1},{0},6), node(1,{0,2},{0},6), node(2,{0,3},{0},6),
                     node(3,{0,4},{0},6), node(4,{3,5},{3},2), node(5,{4,6},{4},3),
                     node({}, {0}, {})}, 6}});
  // Example 4.6, pp.11–12: removing both 123-anchors without their special
  // hyperedge leaves a cyclic triangle. Paper x1..x8 are numbered 0..7 here.
  cases.push_back({"P3 Example4.6", query_for({{0,1,2,3}, {0,1,4}, {0,2,5}, {1,2,6}, {0,1,2,7}}),
                   {{node(0,{0,1,2,3},{0,1,2},5), node(1,{0,1,4},{0,1},5),
                     node(2,{0,2,5},{0,2},5), node(3,{1,2,6},{1,2},5),
                     node(4,{0,1,2,7},{0,1,2},5), node({}, {0,1,2}, {})}, 5}});
  // Algorithm 1, lines17–20: minor{x} has kappa=chi yet is not the root.
  // Its parent is C, not itself. The final y-minor joins C and D above it.
  cases.push_back({"nonroot full-interface minor", query_for({{0,1}, {0,2}, {0,3,4}, {3,5}, {5}}),
                   {{node(0,{0,1},{0},5), node(1,{0,2},{0},5), node(2,{0,3,4},{3},6),
                     node(3,{3,5},{3},6), node(4,{5},{5},3), node({}, {0}, {0},2),
                     node({}, {3}, {})}, 6}});
  // A special edge retains minor identity even when chi equals an original.
  cases.push_back({"special equals original scope", query_for({{0}, {0,1}}),
                   {{node(0,{0},{0},2), node(1,{0,1},{0},2), node({}, {0}, {})}, 2}});
  // A replacement creates a new equal-overlap group in the same reduction.
  // Removing both new ears directly would leave every kappa nonempty.
  cases.push_back({"nested equal-overlap groups", query_for({{0}, {0,1}, {0,1}}),
                   {{node(0,{0},{0},4), node(1,{0,1},{0,1},3), node(2,{0,1},{0,1},3),
                     node({}, {0,1}, {0},4), node({}, {0}, {})}, 4}});
  // Occurrence-labelled extension: aliases of one physical table stay separate.
  auto duplicates = query_for({{0}, {0}, {0,1}});
  duplicates.query.atoms[1].table = TableId{0};
  validate(duplicates.catalog, duplicates.query);
  cases.push_back({"duplicate scopes and physical-table aliases", std::move(duplicates),
                   {{node(0,{0},{0},3), node(1,{0},{0},3), node(2,{0,1},{0},3), node({}, {0}, {})}, 3}});
  cases.push_back({"singleton", query_for({{0,1}}), {{node(0,{0,1},{})}, 0}});
  // Explicit disconnected extension: the empty minor is metadata, not a
  // physical occurrence or the external-parent dummy used by enumeration.
  cases.push_back({"disconnected singletons", query_for({{0}, {1}}),
                   {{node(0,{0},{},2), node(1,{1},{},2), node({}, {}, {})}, 2}});
  cases.push_back({"disconnected nontrivial components", query_for({{0,1}, {0,2}, {3,4}, {3,5}}),
                   {{node(0,{0,1},{0},4), node(1,{0,2},{0},4), node(2,{3,4},{3},5),
                     node(3,{3,5},{3},5), node({}, {0}, {},6), node({}, {3}, {},6),
                     node({}, {}, {})}, 6}});
  // The empty minor is created before the long component's final c-minor.
  // That later terminal minor must not replace the disconnected root.
  cases.push_back({"early disconnected root", query_for({{0}, {1,2}, {2,3}, {3,4}, {4,5}}),
                   {{node(0,{0},{},5), node(1,{1,2},{2},2), node(2,{2,3},{3},6),
                     node(3,{3,4},{3},6), node(4,{4,5},{4},3), node({}, {}, {}),
                     node({}, {3}, {},5)}, 5}});
  // Example 4.4 / Figure6b, pp.10–11: R5 belongs at the highest x1-covering
  // node, the x1,x3 minor, although lower join-tree attachments remain valid.
  cases.push_back({"P3 Example4.4 highest parent", query_for({{0,1,5}, {0,1,2,6}, {0,2,3,7}, {0,3,8}, {0,4}}),
                   {{node(0,{0,1,5},{0,1},1), node(1,{0,1,2,6},{0,2},5),
                     node(2,{0,2,3,7},{0,2},5), node(3,{0,3,8},{0,3},2),
                     node(4,{0,4},{0},5), node({}, {0,2}, {})}, 5}});
  return cases;
}

void source_fixtures(const std::vector<Case>& cases) {
  for (const auto& test : cases) {
    inspect(test.fixture, test.expected, test.name + " hand fixture");
    const auto built = meta::construct(test.fixture.catalog, test.fixture.query);
    require(built.stop == meta::Stop::complete && built.decomposition,
            test.name + ": construction stopped at " + stop_name(built.stop));
    inspect(test.fixture, *built.decomposition, test.name + " constructed");
    expect_structure(*built.decomposition, test.expected, test.name);
    const auto checked = meta::check(test.fixture.catalog, test.fixture.query, test.expected);
    require(checked.stop == meta::Stop::complete && checked.valid, test.name + ": hand fixture rejected");
  }
}

void expect_build_stop(const Fixture& fixture, meta::Stop expected, const std::string& label) {
  const auto built = meta::construct(fixture.catalog, fixture.query);
  require(built.stop == expected && !built.decomposition,
          label + ": expected " + stop_name(expected) + ", got " + stop_name(built.stop));
}

void domain_cases() {
  // Paper §2.1, p.4 excludes empty hyperedges. These are explicit provider
  // domain stops, not evidence that the general engine cannot run the query.
  const auto empty = query_for({});
  expect_build_stop(empty, meta::Stop::empty_body, "empty body");
  const auto nullary = query_for({{}});
  expect_build_stop(nullary, meta::Stop::nullary_occurrence, "one nullary occurrence");
  expect_build_stop(query_for({{}, {0}}), meta::Stop::nullary_occurrence, "nullary before nonnullary");
  // Literal Definition4.3 permits an unguarded minor spanning a cyclic body.
  // The stronger Algorithm1-domain anchor condition must reject this bag.
  const auto triangle = query_for({{0,1}, {1,2}, {0,2}});
  const meta::Decomposition unguarded{{node(0,{0,1},{0,1},3), node(1,{1,2},{1,2},3),
                                      node(2,{0,2},{0,2},3), node({}, {0,1,2}, {})}, 3};
  const auto triangle_check = meta::check(triangle.catalog, triangle.query, unguarded);
  require(triangle_check.stop == meta::Stop::invalid_decomposition && !triangle_check.valid,
          "unguarded minor must not hide cyclic body");
  expect_build_stop(query_for({{0}, {}}), meta::Stop::nullary_occurrence, "nullary after nonnullary");
  const auto empty_check = meta::check(empty.catalog, empty.query, {});
  require(empty_check.stop == meta::Stop::empty_body && !empty_check.valid, "checker must enforce empty-body domain");
  const meta::Decomposition nullary_tree{{node(0,{}, {})}, 0};
  const auto nullary_check = meta::check(nullary.catalog, nullary.query, nullary_tree);
  require(nullary_check.stop == meta::Stop::nullary_occurrence && !nullary_check.valid,
          "checker must enforce nullary domain even for a structurally valid singleton");
  const auto cyclic = query_for({{0,1}, {1,2}, {0,2}});
  require(!crown::planner::gyo_reduce(cyclic.scopes).acyclic, "triangle fixture must be independently cyclic");
  expect_build_stop(cyclic, meta::Stop::cyclic, "triangle");
}

void reject(const Fixture& fixture, const meta::Decomposition& bad, const std::string& label) {
  const auto result = meta::check(fixture.catalog, fixture.query, bad);
  require(result.stop == meta::Stop::invalid_decomposition && !result.valid,
          label + ": malformed decomposition accepted or wrong stop " + stop_name(result.stop));
}

void tampered_cases(const std::vector<Case>& cases) {
  const auto& test = cases.at(2); // Nonroot full-interface minor has all roles.
  const auto& fixture = test.fixture;
  const auto& good = test.expected;
  auto bad = good;
  bad.root = bad.nodes.size(); reject(fixture, bad, "out-of-range root");
  bad = good; bad.nodes[good.root].parent = 0; reject(fixture, bad, "root parent");
  bad = good; bad.nodes[0].parent.reset(); reject(fixture, bad, "second root");
  bad = good; bad.nodes[0].parent = bad.nodes.size(); reject(fixture, bad, "out-of-range parent");
  bad = good; bad.nodes[5].parent = 5; reject(fixture, bad, "minor self parent");
  bad = good; bad.nodes[0].parent = 1; bad.nodes[1].parent = 0;
  reject(fixture, bad, "disconnected parent cycle");
  bad = good; bad.nodes[0].interface.clear(); reject(fixture, bad, "missing shared interface");
  bad = good; bad.nodes[good.root].interface = scope({3}); reject(fixture, bad, "nonempty root interface");
  bad = good; bad.nodes[0].interface.insert(VariableId{1}); reject(fixture, bad, "private variable in interface");
  bad = good; bad.nodes[0].scope.erase(VariableId{1}); reject(fixture, bad, "shortened physical scope");
  bad = good; bad.nodes[0].scope.insert(VariableId{3}); reject(fixture, bad, "foreign physical variable");
  bad = good; bad.nodes[good.root].scope.insert(VariableId{fixture.query.variables.size()});
  reject(fixture, bad, "minor variable outside query domain");
  bad = good; bad.nodes[0].interface.insert(VariableId{fixture.query.variables.size()});
  reject(fixture, bad, "interface variable outside query domain");
  bad = good; bad.nodes[0].occurrence = fixture.query.atoms.size(); reject(fixture, bad, "out-of-range occurrence");
  bad = good; bad.nodes[1].occurrence = 0; reject(fixture, bad, "duplicate occurrence");
  bad = good; bad.nodes[0].occurrence.reset(); reject(fixture, bad, "missing physical occurrence");
  bad = good; std::swap(bad.nodes[0].occurrence, bad.nodes[1].occurrence);
  reject(fixture, bad, "occurrence attached to wrong scope");
  bad = good; bad.nodes.push_back(good.nodes[5]); reject(fixture, bad, "duplicate minor scope");
  // Delete the x-hub but retain a valid tree, scopes, interfaces and RIP.
  // Only C5 forces A/B's common interface to have its own canonical minor.
  const meta::Decomposition missing_hub{{node(0,{0,1},{0},2), node(1,{0,2},{0},2),
                                         node(2,{0,3,4},{3},5), node(3,{3,5},{3},5),
                                         node(4,{5},{5},3), node({}, {3}, {})}, 5};
  reject(fixture, missing_hub, "missing equal-interface hub");
  const auto& highest = cases.back();
  bad = highest.expected; bad.nodes[4].parent = 0;
  reject(highest.fixture, bad, "Example4.4 lower eligible parent violates C4b");
}

void within(const meta::Usage& usage, const meta::Limits& limits, const std::string& label) {
  require(usage.work <= limits.work && usage.nodes <= limits.nodes && usage.scope_cells <= limits.scope_cells,
          label + ": usage exceeded granted metadata budget");
}

// Exact/one-short limits concern only the header's selected metadata work,
// peak node count and cumulative scope-cell charges, not total CPU or bytes.
// Baseline usage measures a grant boundary; it never supplies semantic truth.
void budgets(const Case& test) {
  const auto baseline = meta::construct(test.fixture.catalog, test.fixture.query);
  require(baseline.stop == meta::Stop::complete && baseline.decomposition, "budget baseline must complete");
  const meta::Limits exact{baseline.usage.work, baseline.usage.nodes, baseline.usage.scope_cells};
  require(exact.work != 0 && exact.nodes != 0 && exact.scope_cells != 0, "nonzero constructor budget fixture");
  auto built = meta::construct(test.fixture.catalog, test.fixture.query, exact);
  require(built.stop == meta::Stop::complete && built.decomposition, "exact construction grants must complete");
  within(built.usage, exact, "exact construct");
  expect_structure(*built.decomposition, test.expected, "exact-grant construction");
  for (const auto stop : {meta::Stop::work_limit, meta::Stop::node_limit, meta::Stop::cell_limit}) {
    auto tight = exact;
    if (stop == meta::Stop::work_limit) --tight.work;
    if (stop == meta::Stop::node_limit) --tight.nodes;
    if (stop == meta::Stop::cell_limit) --tight.scope_cells;
    built = meta::construct(test.fixture.catalog, test.fixture.query, tight);
    require(built.stop == stop && !built.decomposition, "one-short construction grant must stop at requested budget");
    within(built.usage, tight, "one-short construct");
  }
  const auto checked = meta::check(test.fixture.catalog, test.fixture.query, test.expected);
  require(checked.stop == meta::Stop::complete && checked.valid, "checker budget baseline must complete");
  const meta::Limits check_exact{checked.usage.work, checked.usage.nodes, checked.usage.scope_cells};
  require(check_exact.work && check_exact.nodes && check_exact.scope_cells, "nonzero checker budget fixture");
  auto result = meta::check(test.fixture.catalog, test.fixture.query, test.expected, check_exact);
  require(result.stop == meta::Stop::complete && result.valid, "exact checker grants must complete");
  within(result.usage, check_exact, "exact check");
  for (const auto stop : {meta::Stop::work_limit, meta::Stop::node_limit, meta::Stop::cell_limit}) {
    auto tight = check_exact;
    if (stop == meta::Stop::work_limit) --tight.work;
    if (stop == meta::Stop::node_limit) --tight.nodes;
    if (stop == meta::Stop::cell_limit) --tight.scope_cells;
    result = meta::check(test.fixture.catalog, test.fixture.query, test.expected, tight);
    require(result.stop == stop && !result.valid, "one-short checker grant must stop without a valid claim");
    within(result.usage, tight, "one-short check");
  }
  for (const auto stop : {meta::Stop::work_limit, meta::Stop::node_limit, meta::Stop::cell_limit}) {
    auto zero = meta::Limits{};
    if (stop == meta::Stop::work_limit) zero.work = 0;
    if (stop == meta::Stop::node_limit) zero.nodes = 0;
    if (stop == meta::Stop::cell_limit) zero.scope_cells = 0;
    built = meta::construct(test.fixture.catalog, test.fixture.query, zero);
    require(built.stop == stop && !built.decomposition, "zero construction grant must stop");
    within(built.usage, zero, "zero construct");
    result = meta::check(test.fixture.catalog, test.fixture.query, test.expected, zero);
    require(result.stop == stop && !result.valid, "zero checker grant must stop");
    within(result.usage, zero, "zero check");
  }
}

void independent_corpus() {
  std::size_t tested = 0, acyclic = 0, cyclic = 0;
  // All 3,875 multisets of 1..4 nonempty edges over four variables, each in
  // forward and reverse occurrence order. GYO supplies expected acyclicity;
  // neither meta API participates in that decision. No random sampling.
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
        std::vector<std::size_t> edge;
        for (std::size_t variable = 0; variable < 4; ++variable)
          if ((mask & (std::size_t{1} << variable)) != 0) edge.push_back(variable);
        edges.push_back(std::move(edge));
      }
      for (int order = 0; order != 2; ++order) {
        if (order) std::reverse(edges.begin(), edges.end());
        const auto fixture = query_for(edges);
        const auto expected_acyclic = crown::planner::gyo_reduce(fixture.scopes).acyclic;
        const auto built = meta::construct(fixture.catalog, fixture.query);
        const auto label = "corpus n=" + std::to_string(count) + " code=" + std::to_string(code) + " order=" + std::to_string(order);
        if (expected_acyclic) {
          ++acyclic;
          require(built.stop == meta::Stop::complete && built.decomposition,
                  label + ": GYO-acyclic input stopped at " + stop_name(built.stop));
          inspect(fixture, *built.decomposition, label);
          const auto checked = meta::check(fixture.catalog, fixture.query, *built.decomposition);
          require(checked.stop == meta::Stop::complete && checked.valid, label + ": constructed metadata rejected");
        } else {
          ++cyclic;
          require(built.stop == meta::Stop::cyclic && !built.decomposition,
                  label + ": GYO-cyclic input did not stop cyclic");
        }
        ++tested;
      }
    }
  }
  require(tested == 7750 && acyclic != 0 && cyclic != 0, "bounded independent corpus did not cover both classes");
  std::cout << tested << " GYO comparisons (" << acyclic << " acyclic, " << cyclic << " cyclic)\n";
}
} // namespace

int main() {
  try {
    const auto cases = paper_cases();
    source_fixtures(cases);
    domain_cases();
    tampered_cases(cases);
    budgets(cases.front());
    independent_corpus();
    return 0;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
