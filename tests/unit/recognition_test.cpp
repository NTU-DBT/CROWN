#include "crown/planner/recognize.hpp"

#include <algorithm>
#include <bit>
#include <cstdint>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>

namespace {
using namespace crown;
using namespace crown::planner;
void check(bool condition, const std::string& message) { if (!condition) throw std::runtime_error(message); }

// Independent ordinary join-tree criterion: enumerate undirected spanning
// trees, then check each variable's induced subgraph is connected. This code
// does not perform GYO, containment reduction, or production witness replay.
bool join_tree_exists(const std::vector<Scope>& scopes) {
  const auto count = scopes.size();
  if (count < 2) return true;
  std::vector<std::pair<std::size_t, std::size_t>> pairs;
  for (std::size_t i = 0; i < count; ++i) for (std::size_t j = i + 1; j < count; ++j) pairs.emplace_back(i, j);
  check(pairs.size() < 32, "test enumerator scope exceeded");
  Scope variables;
  for (const auto& scope : scopes) variables.insert(scope.begin(), scope.end());
  for (std::uint32_t mask = 0; mask < (std::uint32_t{1} << pairs.size()); ++mask) {
    if (static_cast<std::size_t>(std::popcount(mask)) != count - 1) continue;
    std::vector<std::vector<std::size_t>> adjacent(count);
    for (std::size_t i = 0; i < pairs.size(); ++i) {
      if ((mask & (std::uint32_t{1} << i)) != 0) {
        const auto [left, right] = pairs[i];
        adjacent[left].push_back(right);
        adjacent[right].push_back(left);
      }
    }
    const auto reachable = [&](std::size_t start, std::optional<VariableId> variable) {
      std::set<std::size_t> visited{start};
      std::vector<std::size_t> queue{start};
      for (std::size_t position = 0; position < queue.size(); ++position) {
        for (const auto next : adjacent[queue[position]]) {
          if ((!variable || scopes[next].contains(*variable)) && visited.insert(next).second) queue.push_back(next);
        }
      }
      return visited.size();
    };
    if (reachable(0, {}) != count) continue;
    bool valid = true;
    for (const auto variable : variables) {
      std::size_t containing = 0;
      std::size_t first = 0;
      for (std::size_t i = 0; i < count; ++i) if (scopes[i].contains(variable)) { first = i; ++containing; }
      if (reachable(first, variable) != containing) { valid = false; break; }
    }
    if (valid) return true;
  }
  return false;
}

void replay(const std::vector<Scope>& scopes, const GyoResult& result) {
  std::vector<std::optional<Scope>> remaining;
  for (const auto& scope : scopes) remaining.emplace_back(scope);
  for (const auto& step : result.witness) {
    check(step.edge < remaining.size() && remaining[step.edge].has_value(), "witness uses missing edge");
    auto& scope = remaining[step.edge].value();
    if (step.kind == ReductionKind::private_variable) {
      check(step.variable.has_value() && !step.anchor && scope.contains(*step.variable), "private step missing variable");
      std::size_t incidence = 0;
      for (const auto& edge : remaining) if (edge && edge->contains(*step.variable)) ++incidence;
      check(incidence == 1, "private step removes shared variable");
      scope.erase(*step.variable);
    } else if (step.kind == ReductionKind::contained_edge) {
      check(step.anchor && *step.anchor < remaining.size() && remaining[*step.anchor] && *step.anchor != step.edge, "contained step missing anchor");
      for (const auto variable : scope) check(remaining[*step.anchor]->contains(variable), "contained step not contained");
      remaining[step.edge].reset();
    } else {
      check(scope.empty() && !step.anchor && !step.variable, "empty step nonempty");
      remaining[step.edge].reset();
    }
  }
  std::size_t active = 0;
  for (std::size_t i = 0; i < remaining.size(); ++i) {
    if (remaining[i]) {
      check(active < result.failed_core.size(), "missing residual edge");
      check(result.failed_core[active].edge == i && result.failed_core[active].scope == remaining[i], "wrong residual edge");
      ++active;
    }
  }
  check(active == result.failed_core.size() && result.acyclic == (active == 0), "wrong GYO status");
}

void exhaustive() {
  std::size_t bodies = 0;
  std::size_t augmented = 0;
  for (std::size_t edge_count = 0; edge_count <= 4; ++edge_count) {
    std::size_t combinations = 1;
    for (std::size_t i = 0; i < edge_count; ++i) combinations *= 8;
    for (std::size_t code = 0; code < combinations; ++code) {
      std::vector<Scope> scopes(edge_count);
      auto residue = code;
      for (auto& scope : scopes) {
        const auto bits = residue % 8;
        residue /= 8;
        for (std::size_t v = 0; v < 3; ++v) if ((bits & (std::size_t{1} << v)) != 0) scope.insert(VariableId{v});
      }
      const auto result = gyo_reduce(scopes);
      check(result.acyclic == join_tree_exists(scopes), "body disagrees with independent join trees");
      replay(scopes, result);
      ++bodies;
      if (edge_count <= 3) {
        for (std::size_t head_bits = 0; head_bits < 8; ++head_bits) {
          auto with_head = scopes;
          Scope head;
          for (std::size_t v = 0; v < 3; ++v) if ((head_bits & (std::size_t{1} << v)) != 0) head.insert(VariableId{v});
          with_head.push_back(std::move(head));
          const auto head_result = gyo_reduce(with_head);
          check(head_result.acyclic == join_tree_exists(with_head), "augmented body disagrees with independent join trees");
          replay(with_head, head_result);
          ++augmented;
        }
      }
    }
  }
  std::cout << bodies << " bodies and " << augmented << " augmented hypergraphs checked independently\n";
}

void classification() {
  const Catalog catalog{1, {{"R", {{"a", ScalarType::int64}, {"b", ScalarType::int64}}},
                            {"S", {{"b", ScalarType::int64}, {"c", ScalarType::int64}}},
                            {"T", {{"a", ScalarType::int64}, {"c", ScalarType::int64}}}}};
  Query query{{{"a", ScalarType::int64}, {"b", ScalarType::int64}, {"c", ScalarType::int64}},
              {{"r", TableId{0}, {VariableId{0}, VariableId{1}}}, {"s", TableId{1}, {VariableId{1}, VariableId{2}}}},
              {{VariableId{0}, "a"}, {VariableId{2}, "c"}}, false};
  check(analyze(catalog, query).query_class == QueryClass::acyclic_non_free_connex, "projected endpoints Q07");
  query.head.push_back({VariableId{1}, "b"});
  check(analyze(catalog, query).query_class == QueryClass::free_connex, "full path Q04");
  check(query.atoms.size() == 2, "recognizer inserted a phantom head atom");
  query.atoms.push_back({"t", TableId{2}, {VariableId{0}, VariableId{2}}});
  const auto cyclic = analyze(catalog, query);
  check(cyclic.query_class == QueryClass::cyclic && !cyclic.body.failed_core.empty(), "cyclic body Q08");
  // A universal synthetic head can make H+F acyclic while H remains cyclic.
  check(cyclic.augmented.acyclic, "classify both hypergraphs independently");
  Scope wide;
  for (std::size_t i = 0; i < 70; ++i) wide.insert(VariableId{i});
  check(gyo_reduce({wide}).acyclic, "dynamic scopes above 64 variables");
}
}  // namespace

int main() {
  try { exhaustive(); classification(); return 0; }
  catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
