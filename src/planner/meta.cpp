#include "crown/planner/meta.hpp"
#include <algorithm>
#include <utility>

namespace crown::planner::meta {
namespace {
struct Limit { Stop stop; };
struct Budget {
  Limits limits;
  Usage usage;
  void step() {
    if (usage.work == limits.work) throw Limit{Stop::work_limit};
    ++usage.work;
  }
  void cells(std::size_t count) {
    if (count > limits.scope_cells - usage.scope_cells) throw Limit{Stop::cell_limit};
    usage.scope_cells += count;
  }
  void nodes(std::size_t count) {
    if (count > limits.nodes) throw Limit{Stop::node_limit};
    usage.nodes = std::max(usage.nodes, count);
  }
};
bool contains(const Scope& large, const Scope& small, Budget& b) {
  auto i = large.begin();
  for (auto v : small) {
    b.step();
    while (i != large.end() && *i < v) { b.step(); ++i; }
    if (i == large.end() || *i != v) return false;
  }
  return true;
}
bool equal(const Scope& a, const Scope& c, Budget& b) {
  b.step();
  return a.size() == c.size() && contains(a, c, b);
}
Scope copied(const Scope& scope, Budget& b) {
  b.cells(scope.size());
  return scope;
}
std::vector<Scope> scopes(const Query& q, Budget& b) {
  std::vector<Scope> result;
  for (const auto& atom : q.atoms) {
    b.step();
    Scope scope;
    for (const auto& term : atom.terms) {
      b.step();
      if (const auto* v = std::get_if<VariableId>(&term); v && !scope.contains(*v)) {
        b.cells(1); scope.insert(*v);
      }
    }
    result.push_back(std::move(scope));
  }
  return result;
}
// Recompute overlaps from one frozen round. This simple implementation does not
// claim the paper's incremental construction time or enumeration delay bounds.
std::vector<Scope> overlaps(const Decomposition& m, const std::vector<std::size_t>& active, Budget& b) {
  std::vector<Scope> result(active.size());
  for (std::size_t i = 0; i < active.size(); ++i)
    for (auto v : m.nodes[active[i]].scope) {
      b.step();
      for (std::size_t j = 0; j < active.size(); ++j) {
        b.step();
        if (i != j && m.nodes[active[j]].scope.contains(v)) {
          b.cells(1); result[i].insert(v); break;
        }
      }
    }
  return result;
}
std::size_t minor(Decomposition& m, const Scope& scope, Budget& b) {
  for (std::size_t i = 0; i < m.nodes.size(); ++i) {
    b.step();
    if (!m.nodes[i].occurrence && equal(m.nodes[i].scope, scope, b)) return i;
  }
  b.nodes(m.nodes.size() + 1);
  m.nodes.push_back({{}, copied(scope,b), copied(scope,b), {}});
  return m.nodes.size()-1;
}
// Definition checker is independent of the reduction trace: rebuild topology,
// actual outside-subtree interfaces, running intersection and C4(b)/C5 checks.
bool definition(const Query& q, const Decomposition& m, Budget& b) {
  b.nodes(m.nodes.size());
  const auto n = m.nodes.size();
  if (!n || m.root >= n) return false;
  auto original = scopes(q,b);
  Scope variables;
  for (const auto& scope : original) for (auto v : scope) {
    b.step();
    if (!variables.contains(v)) { b.cells(1); variables.insert(v); }
  }
  std::vector<bool> seen(original.size());
  std::vector<std::vector<std::size_t>> children(n);
  for (std::size_t i = 0; i < n; ++i) {
    b.step(); const auto& p = m.nodes[i];
    if (!contains(variables,p.scope,b)) return false;
    if (p.occurrence) {
      const auto index = *p.occurrence;
      if (index >= original.size() || seen[index] || !equal(original[index],p.scope,b)) return false;
      seen[index] = true;
    } else {
      // Algorithm 1 creates only intersections of existing scopes. Requiring
      // one original anchor prevents an unguarded minor from hiding a cycle:
      // RIP lets each minor contract toward its anchor to form a join tree.
      bool anchored = false;
      for (const auto& scope : original) {
        b.step();
        if (contains(scope,p.scope,b)) { anchored = true; break; }
      }
      if (!anchored) return false;
      for (std::size_t j = 0; j < i; ++j) {
        b.step();
        if (!m.nodes[j].occurrence && equal(p.scope,m.nodes[j].scope,b)) return false;
      }
    }
    if (i == m.root) { if (p.parent || !p.interface.empty()) return false; }
    else {
      if (!p.parent || *p.parent >= n || *p.parent == i) return false;
      children[*p.parent].push_back(i);
    }
  }
  for (bool value : seen) { b.step(); if (!value) return false; }
  std::vector<bool> reached(n);
  std::vector<std::size_t> stack{m.root};
  while (!stack.empty()) {
    b.step(); const auto p = stack.back(); stack.pop_back();
    if (reached[p]) return false;
    reached[p] = true;
    for (auto c : children[p]) { b.step(); stack.push_back(c); }
  }
  for (bool value : reached) { b.step(); if (!value) return false; }
  const auto below = [&](std::size_t parent, std::size_t p) {
    for (;;) {
      b.step();
      if (parent == p) return true;
      if (!m.nodes[p].parent) return false;
      p = *m.nodes[p].parent;
    }
  };
  for (std::size_t i = 0; i < n; ++i) {
    b.step(); const auto& p = m.nodes[i]; Scope actual;
    for (auto v : p.scope) {
      b.step();
      for (std::size_t j = 0; j < n; ++j) {
        b.step();
        if (!below(i,j) && m.nodes[j].scope.contains(v)) {
          b.cells(1); actual.insert(v); break;
        }
      }
    }
    if (!equal(actual,p.interface,b)) return false;
    if (p.parent) {
      const auto parent = *p.parent;
      if (!contains(m.nodes[parent].scope,p.interface,b)) return false;
      if (!equal(p.interface,m.nodes[parent].scope,b))
        for (std::size_t j = 0; j < n; ++j) {
          b.step();
          if (!below(parent,j) && contains(m.nodes[j].scope,p.interface,b)) return false;
        }
    }
    // Connectedness: every occurrence of a variable reaches its highest one
    // without crossing an edge whose parent omits that variable.
    for (auto v : p.scope) {
      b.step();
      for (std::size_t j = i+1; j < n; ++j) {
        b.step();
        if (!m.nodes[j].scope.contains(v)) continue;
        auto x = i, y = j;
        while (!below(x,y)) {
          b.step();
          if (!m.nodes[x].scope.contains(v) || !m.nodes[x].parent) return false;
          x = *m.nodes[x].parent;
        }
        for (;;) {
          b.step(); if (!m.nodes[y].scope.contains(v)) return false;
          if (y == x) break;
          y = *m.nodes[y].parent;
        }
      }
    }
    std::size_t same = 0, minors = 0;
    for (const auto& other : m.nodes) {
      b.step();
      same += equal(p.interface,other.interface,b);
      minors += !other.occurrence && equal(p.interface,other.scope,b);
    }
    if (same >= 2 && minors != 1) return false;
  }
  return true;
}
} // namespace

Build construct(const Catalog& catalog, const Query& query, Limits limits) {
  crown::validate(catalog,query);
  Budget b{limits,{}};
  try {
    const auto original = scopes(query,b);
    if (original.empty()) return {Stop::empty_body,b.usage,{}};
    Decomposition m;
    std::vector<std::size_t> active;
    for (std::size_t i = 0; i < original.size(); ++i) {
      b.step();
      if (original[i].empty()) return {Stop::nullary_occurrence,b.usage,{}};
      b.nodes(m.nodes.size()+1);
      m.nodes.push_back({i,copied(original[i],b),{}, {}}); active.push_back(i);
    }
    while (!active.empty()) {
      b.step(); const auto before = active.size();
      auto overlap = overlaps(m,active,b);
      std::vector<bool> grouped(active.size());
      std::vector<std::size_t> next;
      // Algorithm 1, lines 4–8: group equal overlaps simultaneously. Specials
      // are node identities distinct from physical occurrences with equal chi.
      for (std::size_t i = 0; i < active.size(); ++i) {
        b.step(); if (grouped[i]) continue;
        std::vector<std::size_t> group;
        for (std::size_t j = i; j < active.size(); ++j) {
          b.step(); if (!grouped[j] && equal(overlap[i],overlap[j],b)) group.push_back(j);
        }
        if (group.size() < 2) { next.push_back(active[i]); continue; }
        for (auto j : group) {
          b.step(); grouped[j] = true;
          m.nodes[active[j]].interface = copied(overlap[i],b);
        }
        next.push_back(minor(m,overlap[i],b));
      }
      active = std::move(next);
      // A replacement can itself share an overlap with an untouched edge.
      // Exhaust those new groups before freezing the ear-removal snapshot.
      if (active.size() < before) continue;
      overlap = overlaps(m,active,b);
      std::vector<bool> ears(active.size());
      for (std::size_t i = 0; i < active.size(); ++i) {
        b.step(); ears[i] = active.size() == 1;
        for (std::size_t j = 0; j < active.size() && !ears[i]; ++j) {
          b.step(); ears[i] = i != j && contains(m.nodes[active[j]].scope,overlap[i],b);
        }
      }
      next.clear();
      // Lines 9–14: record all ears against the same remaining hypergraph.
      // A previously created special/minor receives its final reduced kappa.
      for (std::size_t i = 0; i < active.size(); ++i) {
        b.step();
        if (ears[i]) m.nodes[active[i]].interface = copied(overlap[i],b);
        else next.push_back(active[i]);
      }
      for (std::size_t i = 0; i < active.size(); ++i) if (ears[i]) {
        b.step(); std::size_t count = 0;
        for (const auto& p : m.nodes) {
          b.step(); count += equal(p.interface,overlap[i],b);
        }
        if (count >= 2) static_cast<void>(minor(m,overlap[i],b));
      }
      active = std::move(next);
      if (active.size() >= before) return {Stop::cyclic,b.usage,{}};
    }
    // Lines 15–21: root and highest eligible parent. An empty-scope minor is
    // the explicit disconnected extension; it remains metadata, not a native.
    std::optional<std::size_t> root;
    for (std::size_t i = 0; i < m.nodes.size(); ++i) {
      b.step();
      if (m.nodes[i].interface.empty() &&
          (!root || (!m.nodes[i].occurrence && m.nodes[i].scope.empty()))) root = i;
    }
    if (!root) return {Stop::invalid_decomposition,b.usage,{}};
    m.root = *root;
    for (std::size_t i = 0; i < m.nodes.size(); ++i) if (i != m.root) {
      b.step(); const auto& interface = m.nodes[i].interface;
      for (std::size_t j = 0; j < m.nodes.size(); ++j) {
        b.step();
        if (i != j && !m.nodes[j].occurrence && equal(m.nodes[j].scope,interface,b)) {
          m.nodes[i].parent = j; break;
        }
      }
      if (!m.nodes[i].parent)
        for (std::size_t j = 0; j < m.nodes.size(); ++j) {
          b.step();
          if (i != j && contains(m.nodes[j].scope,interface,b) && !contains(m.nodes[j].interface,interface,b)) {
            m.nodes[i].parent = j; break;
          }
        }
    }
    if (!definition(query,m,b)) return {Stop::invalid_decomposition,b.usage,{}};
    return {Stop::complete,b.usage,std::move(m)};
  } catch (const Limit& stop) { return {stop.stop,b.usage,{}}; }
}
Check check(const Catalog& catalog, const Query& query, const Decomposition& m, Limits limits) {
  crown::validate(catalog,query);
  Budget b{limits,{}};
  try {
    if (query.atoms.empty()) return {Stop::empty_body,b.usage,false};
    for (const auto& atom : query.atoms) {
      b.step(); bool nonempty = false;
      for (const auto& term : atom.terms) {
        b.step();
        if (std::holds_alternative<VariableId>(term)) { nonempty = true; break; }
      }
      if (!nonempty) return {Stop::nullary_occurrence,b.usage,false};
    }
    const auto valid = definition(query,m,b);
    return {valid ? Stop::complete : Stop::invalid_decomposition,b.usage,valid};
  } catch (const Limit& stop) { return {stop.stop,b.usage,false}; }
}
} // namespace crown::planner::meta
