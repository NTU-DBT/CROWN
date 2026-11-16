#include "crown/planner/oracle.hpp"
#include "crown/planner/verify.hpp"
#include "planner_probe.hpp"
#include "tree_oracle.hpp"

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <variant>
#include <vector>

namespace {
using namespace crown;

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

struct VarRef { std::size_t value; };
struct Ignored {};
using Slot = std::variant<VarRef, std::int64_t, Ignored>;
using Occurrence = std::vector<Slot>;

struct Fixture {
  Catalog catalog;
  Query query;
};

Slot v(std::size_t value) { return VarRef{value}; }
Slot c(std::int64_t value) { return value; }
Slot ignored() { return Ignored{}; }

Fixture fixture_for(const std::vector<Occurrence>& occurrences,
                    const std::vector<std::size_t>& head,
                    bool contradiction = false) {
  Fixture fixture;
  std::set<std::size_t> variable_names;
  for (const auto& occurrence : occurrences) {
    for (const auto& slot : occurrence) {
      if (const auto* variable = std::get_if<VarRef>(&slot)) variable_names.insert(variable->value);
    }
  }
  variable_names.insert(head.begin(), head.end());
  std::map<std::size_t, VariableId> ids;
  for (const auto name : variable_names) {
    const auto id = VariableId{fixture.query.variables.size()};
    ids.emplace(name, id);
    fixture.query.variables.push_back({"v" + std::to_string(name), ScalarType::int64});
  }
  for (std::size_t i = 0; i < occurrences.size(); ++i) {
    Table table{"T" + std::to_string(i), {}};
    Atom atom{"a" + std::to_string(i), TableId{i}, {}};
    for (std::size_t column = 0; column < occurrences[i].size(); ++column) {
      table.columns.push_back({"c" + std::to_string(column), ScalarType::int64});
      const auto& slot = occurrences[i][column];
      if (const auto* variable = std::get_if<VarRef>(&slot)) atom.terms.emplace_back(ids.at(variable->value));
      else if (const auto* value = std::get_if<std::int64_t>(&slot))
        atom.terms.emplace_back(std::in_place_type<Value>,std::in_place_type<std::int64_t>,*value);
      else atom.terms.emplace_back(IgnoredColumn{});
    }
    fixture.catalog.tables.push_back(std::move(table));
    fixture.query.atoms.push_back(std::move(atom));
  }
  for (std::size_t i = 0; i < head.size(); ++i) fixture.query.head.push_back({ids.at(head[i]), "out" + std::to_string(i)});
  fixture.query.contradiction = contradiction;
  return fixture;
}

Fixture scoped_fixture(const std::vector<std::vector<std::size_t>>& scopes,
                       const std::vector<std::size_t>& head,
                       bool contradiction = false) {
  std::vector<Occurrence> occurrences;
  occurrences.reserve(scopes.size());
  for (const auto& scope : scopes) {
    Occurrence occurrence;
    occurrence.reserve(scope.size());
    for (const auto variable : scope) occurrence.push_back(v(variable));
    occurrences.push_back(std::move(occurrence));
  }
  return fixture_for(occurrences, head, contradiction);
}

std::vector<std::set<std::size_t>> native_scopes(const Query& query) {
  std::vector<std::set<std::size_t>> scopes(query.atoms.size());
  for (std::size_t occurrence = 0; occurrence < query.atoms.size(); ++occurrence) {
    for (const auto& term : query.atoms[occurrence].terms) {
      if (const auto* variable = std::get_if<VariableId>(&term)) scopes[occurrence].insert(variable->value);
    }
  }
  return scopes;
}

bool proper_subset(const std::set<std::size_t>& left, const std::set<std::size_t>& right) {
  return left.size() < right.size() && std::includes(right.begin(), right.end(), left.begin(), left.end());
}

// Independent implementation of the incidence-set definition in the P04
// preflight. Occurrences are indices, so duplicate native scopes stay distinct.
bool independently_q_hierarchical(const Query& query) {
  const auto scopes = native_scopes(query);
  std::vector<std::set<std::size_t>> incidence(query.variables.size());
  for (std::size_t occurrence = 0; occurrence < scopes.size(); ++occurrence) {
    for (const auto variable : scopes[occurrence]) incidence[variable].insert(occurrence);
  }
  std::vector<bool> free(query.variables.size(), false);
  for (const auto& output : query.head) free[output.variable.value] = true;
  for (std::size_t x = 0; x < incidence.size(); ++x) {
    for (std::size_t y = x + 1; y < incidence.size(); ++y) {
      const auto& a = incidence[x];
      const auto& b = incidence[y];
      if (!proper_subset(a, b) && !proper_subset(b, a) && a != b) {
        const bool disjoint = std::none_of(a.begin(), a.end(), [&](const auto occurrence) { return b.contains(occurrence); });
        if (!disjoint) return false;
      }
      if (free[x] && proper_subset(a, b) && !free[y]) return false;
      if (free[y] && proper_subset(b, a) && !free[x]) return false;
    }
  }
  return true;
}

planner::HeightCertificate certificate_of(const planner::OracleResult& result) {
  return {result.algorithm, result.minimum_height, result.tree, result.lower_bounds};
}

void check_native_occurrences_once(const Fixture& fixture, const FreeConnexTree& tree,
                                   const std::string& context) {
  std::vector<std::size_t> native;
  for (const auto& node : tree.nodes) {
    if (node.kind == NodeKind::native) {
      check(node.occurrence.has_value(), context + ": native node lost its occurrence id");
      native.push_back(*node.occurrence);
    }
  }
  std::sort(native.begin(), native.end());
  std::vector<std::size_t> expected(fixture.query.atoms.size());
  std::iota(expected.begin(), expected.end(), std::size_t{0});
  check(native == expected, context + ": native occurrences were merged, dropped, or duplicated");
}

planner::OracleResult require_minimum(const Fixture& fixture, std::size_t expected,
                                      const planner::SearchLimits& limits = {},
                                      const std::string& context = "query") {
  const auto result = planner::minimum_tree(fixture.catalog, fixture.query, limits);
  check(result.status == planner::OracleStatus::proven_minimum, context + ": optimized search did not prove a minimum: " + result.reason);
  check(result.minimum_height == expected && result.tree.has_value(), context + ": optimized height differs from the expected minimum");
  check(result.algorithm == "crown_partition_exact_v2", context + ": optimized proof did not use v2");
  check(planner::validate_tree(fixture.catalog, fixture.query, *result.tree).valid, context + ": optimized upper tree is invalid");
  check(planner::verify_height_certificate(fixture.catalog, fixture.query, certificate_of(result)).valid,
        context + ": independently replayed optimized certificate is invalid");
  check(result.certificate_verified, context + ": completed result was not marked independently verified");
  check_native_occurrences_once(fixture, *result.tree, context);
  return result;
}

void compare_all_three(const Fixture& fixture, const std::string& context) {
  const auto optimized = planner::minimum_tree(fixture.catalog, fixture.query);
  const auto baseline = planner::testing::minimum_tree_baseline(fixture.catalog, fixture.query);
  const auto frozen = reference::exhaustive_minimum_tree(fixture.catalog, fixture.query);
  check(optimized.status != planner::OracleStatus::resource_limit &&
        baseline.status != planner::OracleStatus::resource_limit &&
        frozen.status != planner::OracleStatus::resource_limit,
        context + ": feasible small differential case exhausted a budget");
  check(optimized.status == baseline.status && optimized.minimum_height == baseline.minimum_height,
        context + ": optimized search disagrees with private v1 baseline");
  check(optimized.status == frozen.status && optimized.minimum_height == frozen.minimum_height,
        context + ": optimized search disagrees with frozen P03 enumeration");
  if (optimized.status == planner::OracleStatus::proven_minimum) {
    check(optimized.tree && planner::validate_tree(fixture.catalog, fixture.query, *optimized.tree).valid,
          context + ": optimized differential witness is invalid");
    check(planner::verify_height_certificate(fixture.catalog, fixture.query, certificate_of(optimized)).valid,
          context + ": optimized differential proof replay failed");
    check(baseline.certificate_verified && planner::verify_height_certificate(fixture.catalog, fixture.query, certificate_of(baseline)).valid,
          context + ": private baseline proof replay failed");
  }
}

void exhaustive_small_differential_and_hierarchy_predicate() {
  std::size_t comparisons = 0;
  std::size_t recognized_nonempty = 0;
  for (std::size_t count = 0; count <= 2; ++count) {
    std::size_t combinations = 1;
    for (std::size_t i = 0; i < count; ++i) combinations *= 8;
    for (std::size_t code = 0; code < combinations; ++code) {
      auto residue = code;
      std::vector<std::vector<std::size_t>> scopes(count);
      std::set<std::size_t> variables;
      for (auto& scope : scopes) {
        const auto mask = residue % 8;
        residue /= 8;
        for (std::size_t variable = 0; variable < 3; ++variable) {
          if ((mask & (std::size_t{1} << variable)) != 0) {
            scope.push_back(variable);
            variables.insert(variable);
          }
        }
      }
      for (std::size_t head_mask = 0; head_mask < 8; ++head_mask) {
        bool invalid_head = false;
        for (std::size_t variable = 0; variable < 3; ++variable) {
          if ((head_mask & (std::size_t{1} << variable)) != 0 && !variables.contains(variable)) invalid_head = true;
        }
        if (invalid_head) continue;
        std::vector<std::size_t> head;
        for (std::size_t variable = 0; variable < 3; ++variable) {
          if ((head_mask & (std::size_t{1} << variable)) != 0) head.push_back(variable);
        }
        const auto fixture = scoped_fixture(scopes, head);
        const bool q_hierarchical = independently_q_hierarchical(fixture.query);
        const auto optimized = planner::minimum_tree(fixture.catalog, fixture.query);
        const auto baseline = planner::testing::minimum_tree_baseline(fixture.catalog, fixture.query);
        const auto frozen = reference::exhaustive_minimum_tree(fixture.catalog, fixture.query);
        check(optimized.status != planner::OracleStatus::resource_limit &&
              baseline.status != planner::OracleStatus::resource_limit &&
              frozen.status != planner::OracleStatus::resource_limit,
              "small P04 differential family unexpectedly exhausted resources");
        check(optimized.status == baseline.status && optimized.minimum_height == baseline.minimum_height,
              "optimized small family differs from test-only v1 search");
        check(optimized.status == frozen.status && optimized.minimum_height == frozen.minimum_height,
              "optimized small family differs from frozen P03 enumeration");
        check(optimized.algorithm == "crown_partition_exact_v2", "optimized small family did not emit v2");
        if (q_hierarchical && !scopes.empty()) {
          check(optimized.status == planner::OracleStatus::proven_minimum && optimized.minimum_height == 1 && optimized.tree,
                "independently recognized nonempty q-hierarchical query did not have height one");
          check(planner::validate_tree(fixture.catalog, fixture.query, *optimized.tree).valid,
                "q-hierarchical shortcut emitted an invalid tree");
          check(planner::verify_height_certificate(fixture.catalog, fixture.query, certificate_of(optimized)).valid,
                "q-hierarchical shortcut did not emit an independently replayable proof");
          check(optimized.certificate_verified, "q-hierarchical result was not marked certified");
          ++recognized_nonempty;
        }
        if (!q_hierarchical && optimized.status == planner::OracleStatus::proven_minimum) {
          check(planner::verify_height_certificate(fixture.catalog, fixture.query, certificate_of(optimized)).valid,
                "negative hierarchy recognition failed exact fallback proof replay");
        }
        ++comparisons;
      }
    }
  }
  check(comparisons == 371, "small differential family no longer covers all ordered one/two-scope masks and valid heads");
  check(recognized_nonempty > 0, "small differential family did not exercise q-hierarchical proof construction");

  const auto negative = scoped_fixture({{0, 1}, {1}}, {0});
  check(!independently_q_hierarchical(negative.query), "strict upward free-closure violation was misclassified by the independent predicate");
  const auto fallback = planner::minimum_tree(negative.catalog, negative.query);
  check(fallback.status == planner::OracleStatus::proven_minimum && fallback.minimum_height == 2,
        "negative hierarchy recognition did not fall back to the exact search");
  check(fallback.statistics.hierarchy_tests > 0,
        "negative hierarchy witness did not record a tested miss before fallback");
  check(fallback.statistics.states > 0, "negative hierarchy witness skipped exact search");
}

std::vector<std::vector<std::size_t>> seven_atom_residual_scopes() {
  return {{0, 1, 2, 3}, {0, 1, 2, 4}, {3}, {4}, {1, 5}, {5}, {0, 6}};
}

std::vector<std::vector<std::size_t>> nine_atom_residual_scopes() {
  return {{0, 1, 2, 3}, {0, 1, 2, 4}, {3}, {4},
          {1, 5, 6}, {1, 5, 7}, {6}, {7}, {0, 8}};
}

Fixture disjoint_components(const std::vector<std::pair<std::vector<std::vector<std::size_t>>, std::vector<std::size_t>>>& components,
                            const std::vector<std::size_t>& order) {
  std::vector<std::vector<std::size_t>> scopes;
  std::vector<std::size_t> head;
  std::size_t offset = 0;
  for (const auto component_index : order) {
    const auto& [component_scopes, component_head] = components.at(component_index);
    std::size_t width = 0;
    for (const auto& scope : component_scopes) {
      for (const auto variable : scope) width = std::max(width, variable + 1);
    }
    for (const auto variable : component_head) width = std::max(width, variable + 1);
    for (const auto& scope : component_scopes) {
      auto shifted = scope;
      for (auto& variable : shifted) variable += offset;
      scopes.push_back(std::move(shifted));
    }
    for (const auto variable : component_head) head.push_back(variable + offset);
    offset += width;
  }
  return scoped_fixture(scopes, head);
}

Fixture permuted_scopes(const std::vector<std::vector<std::size_t>>& scopes,
                        const std::vector<std::size_t>& head,
                        const std::vector<std::size_t>& atom_order,
                        const std::vector<std::size_t>& variable_map) {
  std::vector<std::vector<std::size_t>> permuted;
  permuted.reserve(atom_order.size());
  for (const auto atom : atom_order) {
    auto scope = scopes.at(atom);
    for (auto& variable : scope) variable = variable_map.at(variable);
    std::sort(scope.begin(), scope.end());
    permuted.push_back(std::move(scope));
  }
  std::vector<std::size_t> mapped_head = head;
  for (auto& variable : mapped_head) variable = variable_map.at(variable);
  std::sort(mapped_head.begin(), mapped_head.end());
  return scoped_fixture(permuted, mapped_head);
}

void singleton_empty_and_structural_semantics() {
  const auto empty_true = scoped_fixture({}, {});
  const auto true_result = require_minimum(empty_true, 0, {}, "empty-body truth");
  check(true_result.statistics.empty_body_hits > 0, "empty body did not use its dedicated path");
  const auto empty_false = scoped_fixture({}, {}, true);
  const auto false_result = require_minimum(empty_false, 0, {}, "empty-body contradiction");
  check(false_result.statistics.empty_body_hits > 0, "contradictory empty body did not use its dedicated path");

  const auto singleton = scoped_fixture({{0, 1}}, {0});
  const auto singleton_result = require_minimum(singleton, 1, {}, "single native occurrence");
  check(singleton_result.statistics.singleton_hits > 0, "one-occurrence query missed its dedicated path");
  check(singleton_result.tree->root && singleton_result.tree->nodes.at(singleton_result.tree->root->value).kind == NodeKind::native,
        "one-occurrence fast path did not keep the native occurrence at the root");
  const auto singleton_nullary = scoped_fixture({{}}, {});
  const auto singleton_nullary_result = require_minimum(singleton_nullary, 1, {}, "single nullary occurrence");
  check(singleton_nullary_result.tree->root &&
        singleton_nullary_result.tree->nodes.at(singleton_nullary_result.tree->root->value).kind == NodeKind::native,
        "single nullary occurrence did not remain a native root");

  const auto multiple_nullary = scoped_fixture({{}, {}, {}}, {});
  const auto nullary_result = require_minimum(multiple_nullary, 1, {}, "multiple nullary occurrences");
  check_native_occurrences_once(multiple_nullary, *nullary_result.tree, "multiple nullary occurrences");
  check(nullary_result.tree->root &&
        nullary_result.tree->nodes.at(nullary_result.tree->root->value).kind == NodeKind::generalized &&
        nullary_result.tree->nodes.at(nullary_result.tree->root->value).scope.empty(),
        "multiple nullary occurrences were not joined under an empty generalized root");

  const auto equal_incidence = scoped_fixture({{0, 1}, {0, 1}}, {0});
  check(independently_q_hierarchical(equal_incidence.query), "equal incidence sets with mixed free/hidden variables must remain q-hierarchical");
  const auto equal_result = require_minimum(equal_incidence, 1, {}, "equal incidence with hidden variable");
  check(equal_result.statistics.hierarchy_hits > 0, "equal-incidence mixed free/hidden query missed the hierarchy path");

  const auto contradictory = scoped_fixture({{0, 1}, {1}}, {0}, true);
  check(!independently_q_hierarchical(contradictory.query), "contradictory nonempty fixture should violate strict free closure");
  const auto contradiction_result = require_minimum(contradictory, 2, {}, "contradictory nonempty structural query");
  check(contradiction_result.minimum_height >= 1 && contradiction_result.tree->nodes.size() >= contradictory.query.atoms.size(),
        "contradiction erased retained structural occurrences");

  const auto repeated_constants_ignored = fixture_for(
      {{v(0), v(0), c(7), ignored(), v(1)}, {v(0), c(7), v(1)}, {v(1), ignored()}}, {0});
  check(native_scopes(repeated_constants_ignored.query) ==
        std::vector<std::set<std::size_t>>{{0, 1}, {0, 1}, {1}},
        "constant, ignored or repeated positions changed native incidence scopes");
  check(!independently_q_hierarchical(repeated_constants_ignored.query),
        "repeated/constants/ignored incidence fixture has unexpected hierarchy");
  compare_all_three(repeated_constants_ignored, "constants, ignored columns and repeated variable positions");
  const auto repeated_result = require_minimum(repeated_constants_ignored, 2, {}, "constants/repeated/ignored structural query");
  check_native_occurrences_once(repeated_constants_ignored, *repeated_result.tree, "duplicate mutable occurrences");
}

void fast_path_statistics_and_components() {
  const auto duplicate_scopes = scoped_fixture({{0, 1}, {0, 1}, {1}}, {0});
  check(!independently_q_hierarchical(duplicate_scopes.query), "symmetry witness should not pass hierarchy shortcut");
  const auto duplicate_result = require_minimum(duplicate_scopes, 2, {}, "duplicate equal-scope mutable occurrences");
  check(duplicate_result.statistics.symmetry_skips > 0, "equal-scope symmetry reduction never skipped an equivalent branch");

  const auto height_one = std::pair{std::vector<std::vector<std::size_t>>{{0}}, std::vector<std::size_t>{0}};
  const auto height_two = std::pair{std::vector<std::vector<std::size_t>>{{0, 1}, {1}}, std::vector<std::size_t>{0}};
  const auto height_three = std::pair{seven_atom_residual_scopes(), std::vector<std::size_t>{0, 1, 6}};
  require_minimum(scoped_fixture(height_one.first, height_one.second), 1, {}, "height-one component");
  require_minimum(scoped_fixture(height_two.first, height_two.second), 2, {}, "height-two component");
  require_minimum(scoped_fixture(height_three.first, height_three.second), 3, {}, "height-three component");
  const std::vector<std::pair<std::vector<std::vector<std::size_t>>, std::vector<std::size_t>>> components{
      height_one, height_two, height_three};

  const auto component_fixture = disjoint_components(components, {0, 1});
  const auto component_result = require_minimum(component_fixture, 2, {}, "disconnected height-one and height-two components");
  check(component_result.statistics.component_splits > 0, "disconnected nonhierarchical query missed component decomposition");

  const auto three_heights = disjoint_components(components, {0, 1, 2});
  const auto split_result = require_minimum(three_heights, 3, {}, "disconnected components of heights one, two and three");
  check(split_result.statistics.component_splits > 0, "three-component query did not use maximum-of-components proof");

  const auto permuted = disjoint_components(components, {2, 0, 1});
  const auto permuted_result = require_minimum(permuted, 3, {}, "permuted disconnected components");
  check(permuted_result.statistics.component_splits > 0, "component permutation bypassed the split proof");

  std::vector<std::size_t> reverse_atoms(seven_atom_residual_scopes().size());
  std::iota(reverse_atoms.begin(), reverse_atoms.end(), std::size_t{0});
  std::reverse(reverse_atoms.begin(), reverse_atoms.end());
  const std::vector<std::size_t> reverse_variables{6, 5, 4, 3, 2, 1, 0};
  const auto relabelled = permuted_scopes(seven_atom_residual_scopes(), {0, 1, 6}, reverse_atoms, reverse_variables);
  require_minimum(relabelled, 3, {}, "atom and variable permutation of seven-atom residual");
}

void residual_counterexamples_and_branch_bound() {
  planner::SearchLimits limits;
  limits.work_limit = 50'000'000;
  limits.recursion_limit = 512;
  limits.literal_scope_limit = 4096;
  const auto seven = scoped_fixture(seven_atom_residual_scopes(), {0, 1, 6});
  const auto seven_result = require_minimum(seven, 3, limits, "seven-atom residual counterexample");
  check(seven_result.statistics.bound_prunes > 0,
        "branch-and-bound did not prune a dominated candidate on the seven-atom residual fixture");

  const auto nine = scoped_fixture(nine_atom_residual_scopes(), {0, 1, 8});
  require_minimum(nine, 3, limits, "nine-atom residual counterexample");
}

void large_dynamic_representations() {
  planner::SearchLimits limits;
  limits.work_limit = 50'000'000;
  limits.recursion_limit = 1024;
  limits.literal_scope_limit = 4096;

  std::vector<std::vector<std::size_t>> singleton_scopes;
  std::vector<std::size_t> singleton_head;
  for (std::size_t variable = 0; variable < 75; ++variable) {
    singleton_scopes.push_back({variable});
    singleton_head.push_back(variable);
  }
  const auto singletons = scoped_fixture(singleton_scopes, singleton_head);
  const auto singleton_result = require_minimum(singletons, 1, limits, "75 disjoint singleton scopes");
  check(singletons.query.variables.size() > 64 && singletons.query.atoms.size() > 64,
        "wide singleton fixture must exceed both legacy fixed widths");
  check(singleton_result.statistics.hierarchy_hits > 0, "wide singleton family missed hierarchy recognition");

  std::vector<std::vector<std::size_t>> star_scopes;
  constexpr std::size_t star_leaves = 75;
  for (std::size_t leaf = 0; leaf < star_leaves; ++leaf) star_scopes.push_back({0, leaf + 1});
  const auto star = scoped_fixture(star_scopes, {0});
  const auto star_result = require_minimum(star, 1, limits, "wide q-hierarchical star");
  check(star.query.variables.size() > 64 && star.query.atoms.size() > 64,
        "wide star fixture must exceed both legacy fixed widths");
  check(star_result.statistics.hierarchy_hits > 0, "wide star family missed hierarchy recognition");

  constexpr std::size_t chain_width = 70;
  std::vector<std::vector<std::size_t>> chain_scopes(chain_width);
  std::vector<std::size_t> chain_head;
  for (std::size_t variable = 0; variable < chain_width; ++variable) {
    chain_head.push_back(variable);
    for (std::size_t occurrence = variable; occurrence < chain_width; ++occurrence) {
      chain_scopes[occurrence].push_back(variable);
    }
  }
  const auto chain = scoped_fixture(chain_scopes, chain_head);
  const auto chain_result = require_minimum(chain, 1, limits, "70-level laminar incidence chain");
  check(chain_result.statistics.hierarchy_hits > 0, "deep laminar family missed hierarchy recognition");
  check(chain.query.variables.size() > 64 && chain.query.atoms.size() > 64,
        "deep laminar fixture must exceed both legacy fixed widths");
  check(chain_scopes.back().size() > 64, "deep laminar fixture must also contain a native scope wider than 64 variables");
  check(std::count_if(chain_result.tree->nodes.begin(), chain_result.tree->nodes.end(), [](const auto& node) {
          return node.kind == NodeKind::generalized;
        }) > 2,
        "deep laminar construction lost its nested generalized levels");
}

std::optional<std::size_t> find_bound(std::vector<planner::LowerBoundEntry>& entries,
                                      const std::vector<std::size_t>& occurrences,
                                      bool generalized_allowed, bool connex_reachable) {
  const auto found = std::find_if(entries.begin(), entries.end(), [&](const auto& entry) {
    return entry.occurrences == occurrences && entry.generalized_allowed == generalized_allowed &&
           entry.connex_reachable == connex_reachable;
  });
  if (found == entries.end()) return std::nullopt;
  return static_cast<std::size_t>(std::distance(entries.begin(), found));
}

void certificate_malformations() {
  const auto duplicate_scopes = scoped_fixture({{0, 1}, {0, 1}, {1}}, {0});
  const auto duplicate_result = require_minimum(duplicate_scopes, 2, {}, "certificate orbit fixture");
  const auto good_duplicate = certificate_of(duplicate_result);

  auto bad = good_duplicate;
  const auto orbit_entry = std::find_if(bad.lower_bounds.begin(), bad.lower_bounds.end(), [](const auto& entry) {
    const auto zero = std::count(entry.occurrences.begin(), entry.occurrences.end(), std::size_t{0});
    const auto one = std::count(entry.occurrences.begin(), entry.occurrences.end(), std::size_t{1});
    return zero + one == 1;
  });
  check(orbit_entry != bad.lower_bounds.end(), "symmetry proof did not expose a one-member equal-scope orbit state");
  auto alternate = *orbit_entry;
  for (auto& occurrence : alternate.occurrences) {
    if (occurrence == 0) occurrence = 1;
    else if (occurrence == 1) occurrence = 0;
  }
  std::sort(alternate.occurrences.begin(), alternate.occurrences.end());
  bad.lower_bounds.push_back(std::move(alternate));
  check(!planner::verify_height_certificate(duplicate_scopes.catalog, duplicate_scopes.query, bad).valid,
        "duplicate orbit claim with a different equal-scope representative was accepted");

  bad = good_duplicate;
  check(!bad.lower_bounds.empty(), "optimized proof unexpectedly has no state entries");
  bad.lower_bounds.front().occurrences.push_back(bad.lower_bounds.front().occurrences.front());
  check(!planner::verify_height_certificate(duplicate_scopes.catalog, duplicate_scopes.query, bad).valid,
        "state with duplicate occurrence membership was accepted");
  bad = good_duplicate;
  bad.lower_bounds.front().occurrences.push_back(duplicate_scopes.query.atoms.size());
  check(!planner::verify_height_certificate(duplicate_scopes.catalog, duplicate_scopes.query, bad).valid,
        "state with out-of-range occurrence membership was accepted");

  const auto disconnected = scoped_fixture({{0, 1}, {1}, {2}}, {0, 2});
  const auto disconnected_result = require_minimum(disconnected, 2, {}, "certificate component fixture");
  const auto good = certificate_of(disconnected_result);
  check(disconnected_result.statistics.component_splits > 0, "certificate fixture did not split into components");

  bad = good;
  const auto root_index = find_bound(bad.lower_bounds, {0, 1, 2}, true, true);
  check(root_index.has_value(), "component certificate omitted its all-occurrences root state");
  bad.lower_bounds[*root_index].bound = 3;
  check(!planner::verify_height_certificate(disconnected.catalog, disconnected.query, bad).valid,
        "false full-root bound was accepted");

  bad = good;
  const auto component_index = find_bound(bad.lower_bounds, {0, 1}, true, true);
  if (component_index) bad.lower_bounds[*component_index].bound = 3;
  else bad.lower_bounds.push_back({{0, 1}, true, true, 3});
  check(!planner::verify_height_certificate(disconnected.catalog, disconnected.query, bad).valid,
        "false induced-component bound was accepted");

  bad = good;
  if (const auto index = find_bound(bad.lower_bounds, {0, 1}, true, true)) {
    bad.lower_bounds.erase(bad.lower_bounds.begin() + static_cast<std::ptrdiff_t>(*index));
  } else {
    check(false, "component certificate omitted the required height-two component proof");
  }
  check(!planner::verify_height_certificate(disconnected.catalog, disconnected.query, bad).valid,
        "missing required component proof was accepted");

  bad = good;
  const auto wrong_flags = find_bound(bad.lower_bounds, {0, 1, 2}, true, true);
  check(wrong_flags.has_value(), "component certificate omitted its root state for flag mutation");
  bad.lower_bounds[*wrong_flags].connex_reachable = false;
  check(!planner::verify_height_certificate(disconnected.catalog, disconnected.query, bad).valid,
        "root proof with a false connex-reachability flag was accepted");

  bad = good;
  const auto wrong_generalized_flag = find_bound(bad.lower_bounds, {0, 1, 2}, true, true);
  check(wrong_generalized_flag.has_value(), "component certificate omitted its root state for generalized-flag mutation");
  bad.lower_bounds[*wrong_generalized_flag].generalized_allowed = false;
  check(!planner::verify_height_certificate(disconnected.catalog, disconnected.query, bad).valid,
        "root proof with a false generalized-permission flag was accepted");

  const auto transport_fixture = scoped_fixture({{0, 1}, {0, 1}, {1}, {0}}, {0});
  auto transport_result = planner::minimum_tree(transport_fixture.catalog, transport_fixture.query);
  check(transport_result.status == planner::OracleStatus::proven_minimum,
        "non-equivalent transport fixture did not finish exact search");
  const auto order_bounds = [](planner::HeightCertificate& certificate) {
    std::stable_sort(certificate.lower_bounds.begin(), certificate.lower_bounds.end(), [](const auto& left, const auto& right) {
      return left.occurrences.size() < right.occurrences.size();
    });
  };

  // The full query gives the two repeated {x,y} occurrences a global
  // boundary of {x,y}. Their residual still has a height-one generalized
  // root with that shared scope, so a bound of two is false.
  auto shared_scope = certificate_of(transport_result);
  auto& shared_entries = shared_scope.lower_bounds;
  shared_entries.erase(std::remove_if(shared_entries.begin(), shared_entries.end(), [](const auto& entry) {
    return entry.occurrences == std::vector<std::size_t>{0, 1} && entry.generalized_allowed && entry.connex_reachable;
  }), shared_entries.end());
  shared_entries.push_back({{0, 1}, true, true, 1});
  order_bounds(shared_scope);
  check(planner::verify_height_certificate(transport_fixture.catalog, transport_fixture.query, shared_scope).valid,
        "valid augmented height-one bound for repeated scopes was rejected");
  const auto shared_index = find_bound(shared_scope.lower_bounds, {0, 1}, true, true);
  check(shared_index.has_value(), "augmented equal-scope state disappeared during ordering");
  shared_scope.lower_bounds[*shared_index].bound = 2;
  check(!planner::verify_height_certificate(transport_fixture.catalog, transport_fixture.query, shared_scope).valid,
        "false transported bound on the shared-scope residual was accepted");

  // Occurrences 2 and 3 have scopes {y} and {x}. The outside occurrences
  // keep {x,y} on their global boundary, so this residual has no completion;
  // any finite lower bound, including two, remains valid.
  auto boundary_port = certificate_of(transport_result);
  auto port_index = find_bound(boundary_port.lower_bounds, {2, 3}, true, true);
  if (port_index) boundary_port.lower_bounds[*port_index].bound = 2;
  else boundary_port.lower_bounds.push_back({{2, 3}, true, true, 2});
  order_bounds(boundary_port);
  check(planner::verify_height_certificate(transport_fixture.catalog, transport_fixture.query, boundary_port).valid,
        "finite lower bound for a globally infeasible residual was incorrectly rejected");

  auto corrupt_tree = good;
  check(corrupt_tree.tree.has_value(), "component proof has no upper witness");
  const auto native = std::find_if(corrupt_tree.tree->nodes.begin(), corrupt_tree.tree->nodes.end(),
                                   [](const auto& node) { return node.kind == NodeKind::native; });
  check(native != corrupt_tree.tree->nodes.end(), "upper witness has no native node");
  native->occurrence = disconnected.query.atoms.size();
  check(!planner::verify_height_certificate(disconnected.catalog, disconnected.query, corrupt_tree).valid,
        "upper-tree native id outside the query was accepted");
}

void budget_exhaustion_stays_explicit() {
  const auto fixture = scoped_fixture({{0, 1}, {1}}, {0});
  auto limits = planner::SearchLimits{};
  limits.work_limit = 0;
  const auto no_work = planner::minimum_tree(fixture.catalog, fixture.query, limits);
  check(no_work.status == planner::OracleStatus::resource_limit && !no_work.minimum_height && !no_work.tree &&
        no_work.lower_bounds.empty() && !no_work.certificate_verified,
        "zero work budget published a partial result or false unsupported status");

  limits = {};
  limits.time_limit = std::chrono::milliseconds{0};
  const auto no_time = planner::minimum_tree(fixture.catalog, fixture.query, limits);
  check(no_time.status == planner::OracleStatus::resource_limit && !no_time.minimum_height && !no_time.tree &&
        no_time.lower_bounds.empty() && !no_time.certificate_verified,
        "zero time budget published a partial result or false unsupported status");

  limits = {};
  limits.recursion_limit = 0;
  const auto no_recursion = planner::minimum_tree(fixture.catalog, fixture.query, limits);
  check(no_recursion.status == planner::OracleStatus::resource_limit && !no_recursion.minimum_height && !no_recursion.tree &&
        no_recursion.lower_bounds.empty() && !no_recursion.certificate_verified,
        "zero recursion budget published a partial result or false unsupported status");

  const auto complete = planner::minimum_tree(fixture.catalog, fixture.query);
  check(complete.status == planner::OracleStatus::proven_minimum, "budget replay fixture should have a complete certificate");
  limits = {};
  limits.work_limit = 0;
  const auto replay = planner::verify_height_certificate(fixture.catalog, fixture.query, certificate_of(complete), limits);
  check(replay.resource_limit && !replay.valid, "zero proof-replay budget did not report resource exhaustion");
}

}  // namespace

int main() {
  try {
    exhaustive_small_differential_and_hierarchy_predicate();
    singleton_empty_and_structural_semantics();
    fast_path_statistics_and_components();
    residual_counterexamples_and_branch_bound();
    large_dynamic_representations();
    certificate_malformations();
    budget_exhaustion_stays_explicit();
    std::cout << "P04 fast paths, exact fallback, dynamic query sizes and v2 proof replay passed\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
