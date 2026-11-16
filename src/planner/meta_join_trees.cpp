#include "crown/planner/meta_join_trees.hpp"
#include <algorithm>
#include <numeric>
#include <set>
#include <utility>

namespace crown::planner::meta {
namespace {
struct Halt { EnumerationStop reason; };
struct Budget {
  const EnumerationLimits& limits;
  EnumerationUsage& usage;
  void step() {
    if (usage.work == limits.work) throw Halt{EnumerationStop::work_limit};
    ++usage.work;
  }
  void cells(std::size_t count) {
    if (count > limits.cells-usage.cells) throw Halt{EnumerationStop::cell_limit};
    usage.cells += count;
  }
};
using Edge = std::pair<std::size_t,std::size_t>;
struct Fragment {
  std::vector<std::size_t> vertices;
  std::vector<Edge> edges;
  std::optional<std::size_t> dummy; // Own external parent, never a physical root.
};
struct Less {
  Budget* budget;
  bool operator()(const Fragment& a,const Fragment& c) const {
    budget->step();
    if (a.dummy != c.dummy) return a.dummy < c.dummy;
    if (a.vertices != c.vertices) return a.vertices < c.vertices;
    return a.edges < c.edges;
  }
};
using Family = std::set<Fragment,Less>;
bool contains(const Scope& large,const Scope& small,Budget& b) {
  b.step();
  return std::includes(large.begin(),large.end(),small.begin(),small.end());
}
void edge(Fragment& f,std::size_t a,std::size_t c,Budget& b) {
  b.step(); b.cells(2); f.edges.emplace_back(std::min(a,c),std::max(a,c));
}
void merge(Fragment& into,const Fragment& from,Budget& b) {
  b.step(); b.cells(from.vertices.size());
  into.vertices.insert(into.vertices.end(),from.vertices.begin(),from.vertices.end());
  for (auto [a,c] : from.edges) edge(into,a,c,b);
}
Fragment copy(const Fragment& f,Budget& b) {
  Fragment result; result.dummy = f.dummy; merge(result,f,b); return result;
}
void store(Family& family,Fragment f,Budget& b) {
  // One owning set entry, not a graph plus a duplicate retained key graph.
  b.step();
  std::sort(f.vertices.begin(),f.vertices.end());
  std::sort(f.edges.begin(),f.edges.end());
  if (family.find(f) != family.end()) return;
  if (b.usage.fragments == b.limits.fragments) throw Halt{EnumerationStop::fragment_limit};
  family.insert(std::move(f)); ++b.usage.fragments;
}
// Mixed-radix Cartesian product; no fixed-width masks or product-size overflow.
// Empty product calls once; an empty choice family calls zero times.
template<class F> void product(const std::vector<std::size_t>& sizes,Budget& b,F visit) {
  for (auto size : sizes) { b.step(); if (!size) return; }
  b.cells(sizes.size()); std::vector<std::size_t> digits(sizes.size());
  for (;;) {
    b.step(); visit(digits);
    std::size_t i = digits.size();
    while (i) { b.step(); --i; if (++digits[i] < sizes[i]) break; digits[i] = 0; }
    if (!i && (digits.empty() || digits[0] == 0)) return;
  }
}
std::vector<std::size_t> entries(const Fragment& f,const Scope& key,
                                 const Decomposition& m,Budget& b) {
  std::vector<std::size_t> result;
  for (auto v : f.vertices) if (contains(m.nodes[v].scope,key,b)) {
    b.cells(1); result.push_back(v);
  }
  return result;
}
// Standard labelled Prüfer decoding, independent of the erroneous source indices.
std::vector<Edge> skeleton(const std::vector<std::size_t>& code,std::size_t n,Budget& b) {
  b.cells(n); std::vector<std::size_t> degree(n,1); std::vector<Edge> result;
  for (auto value : code) { b.step(); ++degree[value]; }
  for (auto value : code) {
    std::size_t leaf = 0;
    while (leaf < n && degree[leaf] != 1) { b.step(); ++leaf; }
    if (leaf == n) throw Halt{EnumerationStop::invalid_expansion};
    b.step(); b.cells(2); result.emplace_back(leaf,value);
    --degree[leaf]; --degree[value];
  }
  std::optional<std::size_t> first;
  for (std::size_t i = 0; i < n; ++i) {
    b.step(); if (degree[i] != 1) continue;
    if (!first) first = i;
    else { b.cells(2); result.emplace_back(*first,i); }
  }
  return result;
}
// Remove ONLY the distinguished external parent, keeping its original neighbor
// as each branch's entry. A proper child never reroots its dummy into a native.
std::vector<Fragment> branches(const Fragment& f,Budget& b) {
  std::vector<Fragment> result;
  for (auto [a,c] : f.edges) {
    b.step(); std::optional<std::size_t> entry;
    if (a == *f.dummy) entry = c;
    if (c == *f.dummy) entry = a;
    if (!entry) continue;
    Fragment part; b.cells(1); part.vertices.push_back(*entry);
    std::set<std::size_t> seen{*f.dummy,*entry}; b.cells(2);
    for (std::size_t pos = 0; pos < part.vertices.size(); ++pos) {
      const auto v = part.vertices[pos];
      for (auto [x,y] : f.edges) {
        b.step(); const auto next = x == v ? y : y == v ? x : *f.dummy;
        if (seen.contains(next)) continue;
        b.cells(2); seen.insert(next); part.vertices.push_back(next); edge(part,v,next,b);
      }
    }
    result.push_back(std::move(part)); // Entry remains vertices.front().
  }
  return result;
}
Family proper(const Family& hosts,const Family& children,const Scope& key,
              const Decomposition& m,Budget& b) {
  Family next{Less{&b}};
  for (const auto& child : children) {
    b.step();
    if (child.dummy) {
      const auto parts = branches(child,b);
      for (const auto& host : hosts) {
        const auto eligible = entries(host,key,m,b); // Freeze ORIGINAL host.
        b.cells(parts.size()); const std::vector<std::size_t> sizes(parts.size(),eligible.size());
        product(sizes,b,[&](const auto& positions) {
          auto f = copy(host,b);
          for (std::size_t i = 0; i < parts.size(); ++i) {
            merge(f,parts[i],b); edge(f,eligible[positions[i]],parts[i].vertices.front(),b);
          }
          store(next,std::move(f),b);
        });
      }
    } else {
      const auto child_entries = entries(child,key,m,b);
      for (const auto& host : hosts) for (auto a : entries(host,key,m,b))
        for (auto c : child_entries) {
          auto f = copy(host,b); merge(f,child,b); edge(f,a,c,b); store(next,std::move(f),b);
        }
    }
  }
  return next;
}
Family minor(std::size_t v,const std::vector<std::size_t>& origin,
             const std::vector<Family>& families,const Decomposition& m,Budget& b) {
  const bool placeholder = v != m.root && m.nodes[v].scope == m.nodes[v].interface;
  if (origin.size() < 2) throw Halt{EnumerationStop::invalid_expansion};
  std::vector<std::vector<const Fragment*>> options;
  std::vector<std::size_t> sizes;
  for (auto c : origin) {
    b.step(); options.emplace_back();
    for (const auto& f : families[c]) {
      b.step(); if (f.dummy) throw Halt{EnumerationStop::invalid_expansion};
      b.cells(1); options.back().push_back(&f);
    }
    b.cells(1); sizes.push_back(options.back().size());
  }
  Fragment external;
  if (placeholder) {
    b.cells(1); external.vertices.push_back(v); external.dummy = v;
    options.push_back({&external}); sizes.push_back(1); b.cells(2);
  }
  Family result{Less{&b}};
  const auto n = options.size();
  b.cells(n > 2 ? n-2 : 0); const std::vector<std::size_t> code_sizes(n > 2 ? n-2 : 0,n);
  product(code_sizes,b,[&](const auto& code) {
    const auto links = skeleton(code,n,b);
    product(sizes,b,[&](const auto& choice) {
      std::vector<const Fragment*> blocks; b.cells(n);
      Fragment base; if (placeholder) base.dummy = v;
      for (std::size_t i = 0; i < n; ++i) {
        blocks.push_back(options[i][choice[i]]); merge(base,*blocks.back(),b);
      }
      std::vector<std::vector<Edge>> endpoints;
      std::vector<std::size_t> endpoint_sizes;
      for (auto [a,c] : links) {
        b.step(); endpoints.emplace_back();
        const auto left = entries(*blocks[a],m.nodes[v].scope,m,b);
        const auto right = entries(*blocks[c],m.nodes[v].scope,m,b);
        for (auto x : left) for (auto y : right) {
          b.step(); b.cells(2); endpoints.back().emplace_back(x,y);
        }
        b.cells(1); endpoint_sizes.push_back(endpoints.back().size());
      }
      product(endpoint_sizes,b,[&](const auto& positions) {
        auto f = copy(base,b);
        for (std::size_t i = 0; i < positions.size(); ++i) {
          auto [a,c] = endpoints[i][positions[i]]; edge(f,a,c,b);
        }
        store(result,std::move(f),b);
      });
    });
  });
  return result;
}
// Acyclicity/connectivity and variable-induced edge counts independently check
// the ordinary result, without trusting the recursive expansion decisions.
bool ordinary(const Fragment& f,const Decomposition& m,std::size_t n,Budget& b) {
  b.step();
  if (f.dummy || f.vertices.size() != n || f.edges.size() != n-1) return false;
  b.cells(n); std::vector<bool> covered(n);
  Scope variables;
  for (auto v : f.vertices) {
    b.step(); if (v >= m.nodes.size() || !m.nodes[v].occurrence) return false;
    const auto i = *m.nodes[v].occurrence;
    if (i >= n || covered[i]) return false;
    covered[i] = true;
    for (auto x : m.nodes[v].scope) if (!variables.contains(x)) {
      b.step(); b.cells(1); variables.insert(x);
    }
  }
  for (auto [a,c] : f.edges) {
    b.step();
    if (a == c || !std::binary_search(f.vertices.begin(),f.vertices.end(),a) ||
        !std::binary_search(f.vertices.begin(),f.vertices.end(),c)) return false;
  }
  std::set<std::size_t> reached{f.vertices.front()}; b.cells(1);
  std::vector<std::size_t> walk{f.vertices.front()}; b.cells(1);
  for (std::size_t i = 0; i < walk.size(); ++i) for (auto [a,c] : f.edges) {
    b.step(); const auto next = a == walk[i] ? c : c == walk[i] ? a : walk[i];
    if (!reached.contains(next)) { b.cells(2); reached.insert(next); walk.push_back(next); }
  }
  if (reached.size() != n) return false;
  for (auto x : variables) {
    std::size_t count = 0, links = 0;
    for (auto v : f.vertices) { b.step(); count += m.nodes[v].scope.contains(x); }
    for (auto [a,c] : f.edges) { b.step(); links += m.nodes[a].scope.contains(x) && m.nodes[c].scope.contains(x); }
    if (links != count-1) return false;
  }
  return true;
}
JoinTree orient(const Fragment& f,std::size_t root,const Decomposition& m,std::size_t n,Budget& b) {
  JoinTree result{*m.nodes[root].occurrence,{}};
  b.cells(n); result.parent.assign(n,n); result.parent[result.root] = result.root;
  b.cells(1); std::vector<std::size_t> walk{root};
  for (std::size_t i = 0; i < walk.size(); ++i) for (auto [a,c] : f.edges) {
    b.step(); const auto next = a == walk[i] ? c : c == walk[i] ? a : walk[i];
    const auto child = *m.nodes[next].occurrence;
    if (result.parent[child] == n) {
      result.parent[child] = *m.nodes[walk[i]].occurrence;
      b.cells(1); walk.push_back(next);
    }
  }
  return result;
}
} // namespace

Enumeration enumerate(const Catalog& catalog,const Query& query,const Decomposition& m,
                      EnumerationLimits limits) {
  Enumeration out;
  out.all_roots = limits.all_roots;
  out.metadata = check(catalog,query,m,limits.metadata);
  if (!out.metadata.valid) {
    const auto stop = out.metadata.stop;
    out.stop = stop == Stop::work_limit || stop == Stop::cell_limit || stop == Stop::node_limit ?
               EnumerationStop::metadata_limit : EnumerationStop::invalid_metadata;
    return out;
  }
  Budget b{limits,out.usage};
  try {
    // Algorithm1 lines17–18 place every equal-interface node at its unique
    // minor. Definition4.3 alone allows other layouts that lose expansions.
    for (std::size_t p = 0; p < m.nodes.size(); ++p)
      for (std::size_t q = 0; q < m.nodes.size(); ++q) {
        b.step();
        if (p != q && !m.nodes[q].occurrence && m.nodes[q].scope == m.nodes[p].interface &&
            m.nodes[p].parent != q) {
          out.stop = EnumerationStop::noncanonical_metadata; return out;
        }
      }
    std::vector<std::vector<std::size_t>> children(m.nodes.size());
    for (std::size_t i = 0; i < m.nodes.size(); ++i) if (m.nodes[i].parent) {
      b.step(); b.cells(1); children[*m.nodes[i].parent].push_back(i);
    }
    for (auto& group : children) std::sort(group.begin(),group.end(),[&](auto a,auto c) {
      b.step(); const auto& x = m.nodes[a].interface; const auto& y = m.nodes[c].interface;
      if (x.size() != y.size()) return x.size() > y.size();
      return x != y ? x < y : a < c;
    });
    b.cells(1); std::vector<std::size_t> order{m.root};
    for (std::size_t i = 0; i < order.size(); ++i) for (auto c : children[order[i]]) {
      b.step(); b.cells(1); order.push_back(c);
    }
    std::vector<Family> families; families.reserve(m.nodes.size());
    for (std::size_t i = 0; i < m.nodes.size(); ++i) families.emplace_back(Less{&b});
    for (auto pos = order.rbegin(); pos != order.rend(); ++pos) {
      b.step(); const auto v = *pos; Family hosts{Less{&b}};
      std::vector<std::size_t> origin;
      if (m.nodes[v].occurrence) {
        Fragment f; b.cells(1); f.vertices.push_back(v); store(hosts,std::move(f),b);
      } else {
        for (auto c : children[v]) if (m.nodes[c].interface == m.nodes[v].scope) {
          b.step(); b.cells(1); origin.push_back(c);
        }
        hosts = minor(v,origin,families,m,b);
      }
      for (auto c : children[v]) {
        b.step();
        if (std::find(origin.begin(),origin.end(),c) != origin.end()) continue;
        hosts = proper(hosts,families[c],m.nodes[c].interface,m,b);
      }
      families[v] = std::move(hosts);
      for (auto c : children[v]) families[c].clear();
    }
    for (const auto& f : families[m.root]) {
      if (!ordinary(f,m,query.atoms.size(),b)) throw Halt{EnumerationStop::invalid_expansion};
      // Physical occurrence order makes each unrooted tree's root0 come first.
      for (std::size_t r = 0; r < (limits.all_roots ? query.atoms.size() : 1); ++r) {
        b.step();
        if (out.trees.size() == limits.output_trees) throw Halt{EnumerationStop::output_limit};
        const auto v = *std::find_if(f.vertices.begin(),f.vertices.end(),[&](auto id) { return m.nodes[id].occurrence == r; });
        auto tree = orient(f,v,m,query.atoms.size(),b);
        out.trees.push_back(std::move(tree)); ++out.usage.output_trees;
      }
    }
    out.stop = EnumerationStop::complete;
  } catch (const Halt& halt) { out.stop = halt.reason; }
  return out;
}
} // namespace crown::planner::meta
