#include "crown/api/error.hpp"
#include "crown/io/tree.hpp"

#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

namespace {
using namespace crown;
using crown::planner::validate_tree;
using crown::io::Json;
void check(bool condition, const std::string& message) { if (!condition) throw std::runtime_error(message); }
struct Fixture { Catalog catalog; Query query; };
Fixture query_for(const std::vector<std::vector<std::size_t>>& scopes, const std::vector<std::size_t>& head) {
  Fixture fixture;
  std::set<std::size_t> variables;
  for (const auto& scope : scopes) variables.insert(scope.begin(), scope.end());
  for (const auto variable : variables) {
    check(variable == fixture.query.variables.size(), "test fixture variable IDs must be dense");
    fixture.query.variables.push_back({"v" + std::to_string(variable), ScalarType::int64});
  }
  for (std::size_t i = 0; i < scopes.size(); ++i) {
    Table table{"T" + std::to_string(i), {}};
    Atom atom{"a" + std::to_string(i), TableId{i}, {}};
    for (std::size_t column = 0; column < scopes[i].size(); ++column) {
      table.columns.push_back({"c" + std::to_string(column), ScalarType::int64});
      atom.terms.emplace_back(VariableId{scopes[i][column]});
    }
    fixture.catalog.tables.push_back(std::move(table));
    fixture.query.atoms.push_back(std::move(atom));
  }
  for (const auto variable : head) fixture.query.head.push_back({VariableId{variable}, "out"});
  validate(fixture.catalog, fixture.query);
  return fixture;
}
TreeNode node(std::string name, NodeKind kind, std::initializer_list<std::size_t> scope,
              std::initializer_list<std::size_t> children, std::optional<std::size_t> occurrence = {}) {
  TreeNode result{std::move(name), kind, {}, {}, occurrence, {}};
  for (const auto variable : scope) result.scope.insert(VariableId{variable});
  for (const auto child : children) result.children.push_back(NodeId{child});
  return result;
}
FreeConnexTree joined_tree() {
  return {NodeId{0}, {node("g", NodeKind::generalized, {1}, {1, 2}),
                      node("r", NodeKind::native, {0, 1}, {}, 0),
                      node("s", NodeKind::native, {1, 2}, {}, 1)}, {}, {}};
}
void has_rule(const planner::ValidationReport& report, const std::string& rule) {
  check(!report.valid && !report.native_height && !report.edge_depth, "invalid tree must not advertise checked height");
  const auto found = std::find_if(report.violations.begin(), report.violations.end(), [&](const auto& issue) { return issue.rule == rule; });
  check(found != report.violations.end(), "expected violated property: " + rule);
  check(!found->message.empty(), "diagnostic needs a reason");
}
void rejects(const std::function<void()>& action, const std::string& code) {
  try { action(); }
  catch (const Error& error) { check(error.code() == code, "wrong input rejection: " + error.code()); return; }
  throw std::runtime_error("expected input rejection: " + code);
}

void valid_and_corrupt() {
  const auto fixture = query_for({{0, 1}, {1, 2}}, {0, 1, 2});
  auto tree = joined_tree();
  tree.claimed_native_height = 1;
  const auto report = validate_tree(fixture.catalog, fixture.query, tree);
  check(report.valid && report.native_height == 1 && report.edge_depth == 1, "generalized root has zero native weight");
  check(report.maximal_connex.size() == 3 && report.separators[0].empty() && report.separators[2] == VariableSet{VariableId{1}}, "actual separators and maximal connex");

  auto bad = tree;
  bad.nodes[2].occurrence = 0;
  has_rule(validate_tree(fixture.catalog, fixture.query, bad), "cover");
  bad = tree; bad.nodes[0].scope.clear();
  const auto disconnected_variable = validate_tree(fixture.catalog, fixture.query, bad);
  has_rule(disconnected_variable, "connect");
  check(std::any_of(disconnected_variable.violations.begin(), disconnected_variable.violations.end(), [](const auto& issue) { return issue.rule == "connect" && issue.variable == VariableId{1} && issue.node; }), "connect rejection needs a concrete variable/node");
  bad = tree; bad.nodes[0].scope.insert(VariableId{0});
  has_rule(validate_tree(fixture.catalog, fixture.query, bad), "guard");
  bad = tree; bad.nodes[1].scope.erase(VariableId{0});
  has_rule(validate_tree(fixture.catalog, fixture.query, bad), "scope");
  bad = tree; bad.claimed_native_height = 0;
  has_rule(validate_tree(fixture.catalog, fixture.query, bad), "height");
  bad.claimed_native_height = 2;
  has_rule(validate_tree(fixture.catalog, fixture.query, bad), "height");
  bad = tree; bad.nodes[2].claimed_separator = VariableSet{};
  has_rule(validate_tree(fixture.catalog, fixture.query, bad), "separator");
  bad = tree; bad.nodes[0].claimed_separator = VariableSet{VariableId{1}};
  has_rule(validate_tree(fixture.catalog, fixture.query, bad), "separator");
  bad = tree; bad.claimed_connex = std::vector<NodeId>{NodeId{1}, NodeId{2}};
  has_rule(validate_tree(fixture.catalog, fixture.query, bad), "connex_certificate");
  bad.claimed_connex = std::vector<NodeId>{NodeId{0}, NodeId{99}};
  const auto bad_claim = validate_tree(fixture.catalog, fixture.query, bad);
  has_rule(bad_claim, "connex_certificate");
  check(io::write_validation(bad_claim, bad, fixture.query).at("tree_valid") == false, "out-of-range typed claims serialize safely");
  bad = tree; bad.nodes[0].children.push_back(NodeId{1});
  has_rule(validate_tree(fixture.catalog, fixture.query, bad), "topology");
  bad = tree; bad.nodes[1].children.push_back(NodeId{0});
  has_rule(validate_tree(fixture.catalog, fixture.query, bad), "topology");
  bad = tree; bad.nodes[2].children.push_back(NodeId{99});
  has_rule(validate_tree(fixture.catalog, fixture.query, bad), "topology");
  bad = tree; bad.root.reset();
  has_rule(validate_tree(fixture.catalog, fixture.query, bad), "topology");
  bad = tree; bad.nodes[0].id = bad.nodes[1].id;
  has_rule(validate_tree(fixture.catalog, fixture.query, bad), "topology");

  auto projected = fixture;
  projected.query.head = {{VariableId{0}, "a"}};
  has_rule(validate_tree(projected.catalog, projected.query, tree), "connex");
  const FreeConnexTree native{NodeId{0}, {node("r", NodeKind::native, {0, 1}, {1}, 0), node("s", NodeKind::native, {1, 2}, {}, 1)}, {}, {}};
  const auto projected_report = validate_tree(projected.catalog, projected.query, native);
  check(projected_report.valid && projected_report.native_height == 2 && projected_report.maximal_connex == std::vector<NodeId>{NodeId{0}}, "head output does not imply child connex membership");
  auto hidden_claim = native;
  hidden_claim.claimed_connex = std::vector<NodeId>{NodeId{0}, NodeId{1}};
  has_rule(validate_tree(projected.catalog, projected.query, hidden_claim), "connex_certificate");

  const auto equal = query_for({{0}, {0}}, {0});
  FreeConnexTree below_native{NodeId{0}, {node("r", NodeKind::native, {0}, {1}, 0),
                                        node("g", NodeKind::generalized, {0}, {2}),
                                        node("s", NodeKind::native, {0}, {}, 1)}, {}, {}};
  has_rule(validate_tree(equal.catalog, equal.query, below_native), "above");
  FreeConnexTree unary{NodeId{0}, {node("g", NodeKind::generalized, {0}, {1}),
                                 node("r", NodeKind::native, {0}, {2}, 0),
                                 node("s", NodeKind::native, {0}, {}, 1)}, {}, {}};
  check(validate_tree(equal.catalog, equal.query, unary).valid, "valid unary generalized nodes are not forbidden by the checker");
  unary.nodes[2].kind = NodeKind::generalized; unary.nodes[2].occurrence.reset();
  has_rule(validate_tree(equal.catalog, equal.query, unary), "cover");
}

void constants_and_dynamic_sizes() {
  const auto constant = query_for({}, {});
  FreeConnexTree empty;
  empty.claimed_native_height = 0;
  const auto zero = validate_tree(constant.catalog, constant.query, empty);
  check(zero.valid && zero.native_height == 0 && zero.edge_depth == 0, "constant has empty height-zero tree");
  empty.claimed_native_height = 1;
  has_rule(validate_tree(constant.catalog, constant.query, empty), "height");

  const auto nullary = query_for({{}}, {});
  const FreeConnexTree nullary_input{NodeId{0}, {node("r", NodeKind::native, {}, {}, 0)}, {}, {}};
  check(validate_tree(nullary.catalog, nullary.query, nullary_input).native_height == 1, "nullary input still counts as a native occurrence");

  const auto equal = query_for({{0}, {0}, {0}}, {0});
  const FreeConnexTree two_depths{NodeId{0}, {node("g0", NodeKind::generalized, {0}, {1, 4}),
                                            node("g1", NodeKind::generalized, {0}, {2}),
                                            node("g2", NodeKind::generalized, {0}, {3}),
                                            node("n0", NodeKind::native, {0}, {}, 0),
                                            node("n1", NodeKind::native, {0}, {5}, 1),
                                            node("n2", NodeKind::native, {0}, {}, 2)}, {}, {}};
  const auto separate_metrics = validate_tree(equal.catalog, equal.query, two_depths);
  check(separate_metrics.valid && separate_metrics.native_height == 2 && separate_metrics.edge_depth == 3, "native height and edge depth are separate maxima");

  auto head_key = query_for({{0, 1}, {1, 2}}, {1});
  auto smaller_claim = joined_tree();
  smaller_claim.claimed_connex = std::vector<NodeId>{NodeId{0}};
  const auto smaller_report = validate_tree(head_key.catalog, head_key.query, smaller_claim);
  check(smaller_report.valid && smaller_report.maximal_connex.size() == 3, "a sufficient connex certificate may be smaller than C*");

  const auto disconnected = query_for({{0}, {1}}, {});
  const FreeConnexTree product{NodeId{0}, {node("g", NodeKind::generalized, {}, {1, 2}),
                                         node("r", NodeKind::native, {0}, {}, 0),
                                         node("s", NodeKind::native, {1}, {}, 1)}, {}, {}};
  check(validate_tree(disconnected.catalog, disconnected.query, product).valid, "empty-head/disconnected tree with empty keys");
  auto full = disconnected;
  full.query.head = {{VariableId{0}, "a"}, {VariableId{1}, "b"}};
  check(validate_tree(full.catalog, full.query, product).valid, "empty separators connect Cartesian output");

  std::vector<std::vector<std::size_t>> star_scopes(9, {0});
  const auto star = query_for(star_scopes, {0});
  FreeConnexTree fanout{NodeId{0}, {node("g", NodeKind::generalized, {0}, {})}, {}, {}};
  for (std::size_t i = 0; i < 9; ++i) {
    fanout.nodes[0].children.push_back(NodeId{i + 1});
    fanout.nodes.push_back(node("n" + std::to_string(i), NodeKind::native, {0}, {}, i));
  }
  check(validate_tree(star.catalog, star.query, fanout).native_height == 1, "nine native children with equal scopes retain all occurrences");

  std::vector<std::size_t> wide_scope;
  for (std::size_t i = 0; i < 70; ++i) wide_scope.push_back(i);
  const auto wide = query_for({wide_scope, wide_scope}, wide_scope);
  auto wide_tree = joined_tree();
  wide_tree.nodes[0].scope.clear(); wide_tree.nodes[1].scope.clear(); wide_tree.nodes[2].scope.clear();
  for (const auto variable : wide_scope) for (auto& item : wide_tree.nodes) item.scope.insert(VariableId{variable});
  check(validate_tree(wide.catalog, wide.query, wide_tree).valid, "dynamic scopes exceed 64 variables");

  const auto deep = query_for(std::vector<std::vector<std::size_t>>(1500, {0}), {0});
  FreeConnexTree chain{NodeId{0}, {}, {}, {}};
  for (std::size_t i = 0; i < 1500; ++i) {
    chain.nodes.push_back(node("n" + std::to_string(i), NodeKind::native, {0}, {}, i));
    if (i + 1 < 1500) chain.nodes.back().children.push_back(NodeId{i + 1});
  }
  const auto depth = validate_tree(deep.catalog, deep.query, chain);
  check(depth.valid && depth.native_height == 1500 && depth.edge_depth == 1499, "iterative traversal handles deep native chains");
}

void connex_lemma() {
  auto fixture = query_for({{0, 1}, {1, 2}, {2, 3}}, {});
  const FreeConnexTree tree{NodeId{0}, {node("g", NodeKind::generalized, {1}, {1, 2}),
                                      node("r", NodeKind::native, {0, 1}, {}, 0),
                                      node("s", NodeKind::native, {1, 2}, {3}, 1),
                                      node("t", NodeKind::native, {2, 3}, {}, 2)}, {}, {}};
  // Independent check: enumerate every root-containing parent-closed subset,
  // then test the separator/output definition directly (no C* traversal).
  for (std::uint32_t head_bits = 0; head_bits < 16; ++head_bits) {
    fixture.query.head.clear();
    VariableSet head;
    for (std::size_t v = 0; v < 4; ++v) if ((head_bits & (std::uint32_t{1} << v)) != 0) { head.insert(VariableId{v}); fixture.query.head.push_back({VariableId{v}, "out"}); }
    bool exists = false;
    for (std::uint32_t bits = 1; bits < 16; bits += 2) {
      bool good = true;
      VariableSet coverage;
      for (std::size_t i = 0; i < tree.nodes.size(); ++i) {
        if ((bits & (std::uint32_t{1} << i)) == 0) continue;
        coverage.insert(tree.nodes[i].scope.begin(), tree.nodes[i].scope.end());
        if (i == 0) continue;
        const std::size_t parent = i == 3 ? 2 : 0;
        if ((bits & (std::uint32_t{1} << parent)) == 0) { good = false; break; }
        for (const auto variable : tree.nodes[i].scope) if (tree.nodes[parent].scope.contains(variable) && !head.contains(variable)) good = false;
      }
      for (const auto variable : head) if (!coverage.contains(variable)) good = false;
      exists = exists || good;
    }
    const auto report = validate_tree(fixture.catalog, fixture.query, tree);
    check(report.valid == exists, "maximal connex disagrees with explicit subtree enumeration");
  }
}

void codec() {
  const auto fixture = query_for({{0, 1}, {1, 2}}, {0, 1, 2});
  auto tree = joined_tree();
  tree.claimed_native_height = 1;
  tree.claimed_connex = std::vector<NodeId>{NodeId{0}, NodeId{1}, NodeId{2}};
  tree.nodes[2].claimed_separator = VariableSet{VariableId{1}};
  const auto encoded = io::write_tree(tree, fixture.catalog, fixture.query);
  const auto decoded = io::read_tree(encoded.dump(), fixture.catalog, fixture.query);
  check(io::write_tree(decoded, fixture.catalog, fixture.query) == encoded, "plan roundtrip preserves claims and identity");
  check(validate_tree(fixture.catalog, fixture.query, decoded).valid, "decoded plan validates independently");
  const auto reject = [&](const Json& value, const std::string& code) { rejects([&] { static_cast<void>(io::read_tree(value.dump(), fixture.catalog, fixture.query)); }, code); };
  auto bad = encoded; bad["schema_version"] = 2; reject(bad, "unsupported_version");
  bad = encoded; bad["catalog_version"] = 2; reject(bad, "catalog_mismatch");
  bad = encoded; bad["semantics"] = "bag"; reject(bad, "unsupported_semantics");
  bad = encoded; bad["optimal"] = true; reject(bad, "invalid_document");
  bad = encoded; bad["nodes"][0]["occurrence"] = "a0"; reject(bad, "invalid_document");
  bad = encoded; bad["nodes"][1].erase("occurrence"); reject(bad, "invalid_document");
  bad = encoded; bad["nodes"][0]["children"].push_back("missing"); reject(bad, "invalid_document");
  bad = encoded; bad["root"] = "missing"; reject(bad, "invalid_document");
  bad = encoded; bad["nodes"][1]["occurrence"] = "missing"; reject(bad, "invalid_document");
  bad = encoded; bad["connex"] = {"missing"}; reject(bad, "invalid_document");
  bad = encoded; bad["nodes"][0]["scope"].push_back("v1"); reject(bad, "invalid_document");
  bad = encoded; bad["nodes"][0]["scope"] = {"unknown"}; reject(bad, "invalid_document");
  bad = encoded; bad["nodes"][1]["id"] = "g"; reject(bad, "invalid_document");
  bad = encoded; bad["native_height"] = -1; reject(bad, "invalid_document");
  bad = encoded; bad["native_height"] = 1.0; reject(bad, "invalid_document");
  bad = encoded; bad["native_height"] = true; reject(bad, "invalid_document");
  bad = encoded; bad["catalog_version"] = true; reject(bad, "invalid_document");
  auto max_catalog = fixture.catalog;
  max_catalog.version = std::numeric_limits<std::uint64_t>::max();
  auto max_version = encoded;
  max_version["catalog_version"] = max_catalog.version;
  check(validate_tree(max_catalog, fixture.query, io::read_tree(max_version.dump(), max_catalog, fixture.query)).valid, "catalog versions retain unsigned 64-bit precision");
  bad = encoded; bad["native_height"] = std::numeric_limits<std::uint64_t>::max();
  if constexpr (std::numeric_limits<std::size_t>::max() == std::numeric_limits<std::uint64_t>::max()) {
    has_rule(validate_tree(fixture.catalog, fixture.query, io::read_tree(bad.dump(), fixture.catalog, fixture.query)), "height");
  } else reject(bad, "invalid_document");
  auto invalid_names = tree;
  invalid_names.nodes[1].id = invalid_names.nodes[0].id;
  rejects([&] { static_cast<void>(io::write_tree(invalid_names, fixture.catalog, fixture.query)); }, "invalid_document");
  rejects([&] { static_cast<void>(io::read_tree("{\"root\":null,\"root\":null}", fixture.catalog, fixture.query)); }, "invalid_document");
}
}  // namespace

int main() {
  try {
    valid_and_corrupt(); constants_and_dynamic_sizes(); connex_lemma(); codec();
    std::cout << "cover/connect/guard/above, topology, claims, 16 head variants, wide/deep trees and strict plan codec passed\n";
    return 0;
  } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
