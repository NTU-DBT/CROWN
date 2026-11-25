#include "crown/runtime/keyed_cyclic.hpp"
#include "crown/runtime/keyed_engine.hpp"
#include "crown/planner/lower.hpp"
#include "crown/planner/oracle.hpp"

#include "crown/api/error.hpp"

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <string_view>
#include <deque>
#include <limits>
#include <map>
#include <vector>

namespace crown::runtime::keyed {
namespace {
using storage::RowView;
using storage::ScalarView;
using namespace storage::keyed;
constexpr std::size_t no_index = std::numeric_limits<std::size_t>::max();

void require(bool value, const char* message) {
  if (!value) [[unlikely]] throw Error("runtime_contract", message);
}
// Scalar equality with the dominant int64 pair compared directly.
inline bool same(const ScalarView& a, const ScalarView& b) noexcept {
  const auto* x = std::get_if<std::int64_t>(&a);
  const auto* y = std::get_if<std::int64_t>(&b);
  if (x && y) return *x == *y;
  return a == b;
}

struct Term {
  enum Kind : std::uint8_t { variable, constant, ignored } kind = ignored;
  std::uint32_t id = 0;  // variable id or constant slot
};
}  // namespace

// Incremental exact-set maintenance by presence propagation (runtime::fallback):
// a connected prefix P binding every head variable is enumerated explicitly;
// the remaining occurrences form residual components, each a view counting its
// completions per key (its variables shared with P). An answer's support is the
// number of P-assignments projecting to it whose view keys are all present.
// An event first counts the witnesses of touched views (view deltas), then
// re-enumerates P for view keys whose count crosses zero (earlier views use
// updated presence, later ones committed presence), then P-assignments using
// the changed row. Self-joins: when occurrence k is bound to the changed row,
// earlier occurrences of that table exclude it and later ones include it.
// Everything is computed into pending maps; publishing applies them.
struct CyclicEngine::Impl {
  CyclicOptions options;
  Query query;
  Collector collector;
  Budget budget;
  std::vector<std::vector<ScalarType>> types;
  std::vector<std::vector<Term>> atoms;
  std::vector<std::uint32_t> atom_table;
  std::vector<std::uint8_t> used;
  std::deque<std::string> constant_text;  // stable string storage
  std::vector<ScalarView> constants;
  struct Index {
    std::uint32_t table;
    std::vector<std::uint32_t> positions;
    std::uint32_t slot = 0;
    std::unique_ptr<KeyDomain> domain;
  };
  std::vector<Index> indices;
  struct Table {
    std::unique_ptr<KeyDomain> domain;
    KeyMap rows;
    std::vector<std::size_t> indexes;  // index ids in slot order
  };
  std::vector<Table> tables;
  std::vector<std::uint32_t> identity;
  std::vector<std::size_t> prefix_atoms, prefix_local, prefix_order, prefix_steps;
  std::vector<std::size_t> view_atom_begin, view_atoms, view_key_begin, view_keys, view_plan_begin, view_order,
      view_steps, key_order, key_steps;
  struct View {
    std::unique_ptr<KeyDomain> domain;
    std::vector<std::uint32_t> variables;  // key variables (positions into the assignment)
    KeyMap counts, delta;
    std::vector<std::uint32_t> delta_ids;
  };
  std::vector<View> views;
  std::unique_ptr<KeyDomain> head_domain;
  std::vector<std::uint32_t> head_variables;
  std::vector<ScalarType> head_types;
  KeyMap answers, supports;
  std::vector<std::uint32_t> support_ids;
  // Walk state.
  std::vector<ScalarView> assignment;
  std::vector<std::uint8_t> bound;
  std::vector<std::uint32_t> trail;
  struct Cursor {
    std::uint32_t id = no_entry;
    std::uint8_t phase = 0;
    std::size_t mark = 0;
    std::array<ScalarView, 2> scratch{};
  };
  std::vector<Cursor> cursors;
  std::vector<ScalarView> key_cells;
  std::array<ScalarView, 2> key_scratch{};
  // Pending event.
  bool pending = false, insert_ = true;
  std::uint32_t table_ = 0, stored_ = no_entry;
  RowView row_;
  Key row_key_{};
  std::vector<Key> row_secondary_;  // sized per event in prepare (publish never allocates)
  bool row_key_owned_ = false;
  std::size_t secondary_owned_ = 0;  // acquired secondary keys of an inserted row
  std::size_t fresh_answers_ = 0, removed_answers_ = 0;
  bool unlimited_ = false;  // diagnostics recount without the event work grant
  std::vector<std::uint8_t> touched;
  CyclicMetrics scratch_metrics;
  CyclicMetrics* metrics_ = &scratch_metrics;
  std::uint64_t answer_root = 0;  // the nullary answer's presence (empty body)

  Impl(const Catalog& catalog, const Query& source, CyclicOptions value)
      : options(value), query(source), collector(value.gc), budget(value.memory_limit_bytes),
        answers(1, 0, &budget), supports(1, 0, &budget) {
    budget.set_reclaimer(&collector);
    if (auto problem = CyclicEngine::unsupported(catalog, source); !problem.empty()) throw Error("keyed_engine_unsupported", problem);
    for (const auto& table : catalog.tables) {
      types.emplace_back();
      for (const auto& column : table.columns) types.back().push_back(column.type);
    }
    used.assign(types.size(), 0);
    for (const auto& atom : query.atoms) {
      std::vector<Term> terms;
      for (const auto& term : atom.terms) {
        Term code;
        if (const auto* variable = std::get_if<VariableId>(&term)) {
          code.kind = Term::variable; code.id = static_cast<std::uint32_t>(variable->value);
        } else if (const auto* value = std::get_if<Value>(&term)) {
          code.kind = Term::constant; code.id = static_cast<std::uint32_t>(constants.size());
          constants.push_back(intern(*value));
        }
        terms.push_back(code);
      }
      atoms.push_back(std::move(terms));
      atom_table.push_back(static_cast<std::uint32_t>(atom.table.value));
      used[atom.table.value] = 1;
    }
    std::size_t widest = 2;
    for (const auto& columns : types) widest = std::max(widest, columns.size());
    for (std::uint32_t i = 0; i < std::max<std::size_t>(widest, query.variables.size()) + 1; ++i) identity.push_back(i);
    for (const auto& field : query.head) {
      head_variables.push_back(static_cast<std::uint32_t>(field.variable.value));
      head_types.push_back(query.variables.at(field.variable.value).type);
    }
    head_domain = std::make_unique<KeyDomain>(head_types, &collector, &budget);
    build_plan();
    std::vector<std::size_t> per_table(types.size(), 0);
    for (auto& index : indices) {
      index.slot = static_cast<std::uint32_t>(per_table[index.table]++);
      std::vector<ScalarType> key_types;
      for (const auto position : index.positions) key_types.push_back(types[index.table][position]);
      index.domain = std::make_unique<KeyDomain>(std::move(key_types), &collector, &budget);
    }
    for (std::size_t t = 0; t < types.size(); ++t) {
      Table table;
      table.domain = std::make_unique<KeyDomain>(types[t], &collector, &budget);
      table.rows = KeyMap(0, static_cast<std::uint32_t>(per_table[t]), &budget);
      tables.push_back(std::move(table));
    }
    for (std::size_t i = 0; i < indices.size(); ++i) tables[indices[i].table].indexes.push_back(i);
    const auto view_count = view_atom_begin.size() - 1;
    for (std::size_t v = 0; v < view_count; ++v) {
      View view;
      std::vector<ScalarType> key_types;
      for (auto k = view_key_begin[v]; k < view_key_begin[v + 1]; ++k) {
        view.variables.push_back(static_cast<std::uint32_t>(view_keys[k]));
        key_types.push_back(query.variables.at(view_keys[k]).type);
      }
      view.domain = std::make_unique<KeyDomain>(std::move(key_types), &collector, &budget);
      view.counts = KeyMap(1, 0, &budget);
      view.delta = KeyMap(1, 0, &budget);
      views.push_back(std::move(view));
    }
    touched.assign(view_count, 0);
    assignment.assign(query.variables.size(), ScalarView{});
    bound.assign(query.variables.size(), 0);
    cursors.resize(atoms.size() + 1);
    // All relations start empty: a nonempty body has no witness, the empty
    // noncontradictory body has exactly one (the nullary answer).
    if (!query.contradiction && query.atoms.empty()) answer_root = 1;
  }
  ScalarView intern(const Value& value) {
    if (const auto* text = std::get_if<std::string>(&value)) {
      constant_text.push_back(*text);
      return std::string_view(constant_text.back());
    }
    return storage::borrow_scalar(value);
  }

  // ------------------------------------------------------------------ plan
  bool fixed(std::size_t atom, std::size_t field, const std::vector<std::uint8_t>& is_bound) const {
    const auto& term = atoms[atom][field];
    if (term.kind == Term::constant) return true;
    return term.kind == Term::variable && is_bound[term.id];
  }
  void bind_all(std::size_t atom, std::vector<std::uint8_t>& is_bound) const {
    for (const auto& term : atoms[atom]) if (term.kind == Term::variable) is_bound[term.id] = 1;
  }
  std::size_t index_for(std::uint32_t table, const std::vector<std::uint32_t>& positions) {
    for (std::size_t i = 0; i < indices.size(); ++i)
      if (indices[i].table == table && indices[i].positions == positions) return i;
    indices.push_back({table, positions, 0, nullptr});
    return indices.size() - 1;
  }
  // Greedy connected order: most fixed fields, then fewest new variables.
  void extend_order(const std::vector<std::size_t>& pool, std::vector<std::uint8_t>& taken,
      std::vector<std::uint8_t>& is_bound, std::vector<std::size_t>& order_out, std::vector<std::size_t>& steps_out) {
    std::vector<std::uint32_t> positions;
    for (;;) {
      std::size_t best = no_index, best_fixed = 0, best_new = 0;
      for (std::size_t j = 0; j < pool.size(); ++j) {
        if (taken[j]) continue;
        std::size_t fixed_fields = 0, new_variables = 0;
        for (std::size_t field = 0; field < atoms[pool[j]].size(); ++field) {
          if (fixed(pool[j], field, is_bound)) ++fixed_fields;
          else if (atoms[pool[j]][field].kind == Term::variable) ++new_variables;
        }
        if (best == no_index || fixed_fields > best_fixed || (fixed_fields == best_fixed && new_variables < best_new)) {
          best = j; best_fixed = fixed_fields; best_new = new_variables;
        }
      }
      if (best == no_index) return;
      const auto atom = pool[best];
      positions.clear();
      for (std::size_t field = 0; field < atoms[atom].size(); ++field)
        if (fixed(atom, field, is_bound)) positions.push_back(static_cast<std::uint32_t>(field));
      order_out.push_back(atom);
      steps_out.push_back(positions.empty() ? no_index : index_for(atom_table[atom], positions));
      taken[best] = 1;
      bind_all(atom, is_bound);
    }
  }
  std::size_t component_count(const std::vector<std::uint8_t>& selected) const {
    const auto count_atoms = atoms.size();
    std::vector<std::size_t> parent(count_atoms), owner(query.variables.size(), no_index);
    for (std::size_t a = 0; a < count_atoms; ++a) parent[a] = a;
    const auto root = [&](std::size_t x) { while (parent[x] != x) x = parent[x] = parent[parent[x]]; return x; };
    for (std::size_t a = 0; a < count_atoms; ++a) {
      if (!selected[a]) continue;
      for (const auto& term : atoms[a]) {
        if (term.kind != Term::variable) continue;
        if (owner[term.id] == no_index) owner[term.id] = a;
        else parent[root(a)] = root(owner[term.id]);
      }
    }
    std::size_t count = 0;
    for (std::size_t a = 0; a < count_atoms; ++a) if (selected[a] && root(a) == a) ++count;
    return count;
  }
  void build_plan() {
    const auto count_atoms = atoms.size(), variables = query.variables.size();
    std::vector<std::uint8_t> selected(count_atoms, 1), head(variables, 0);
    for (const auto& field : query.head) head[field.variable.value] = 1;
    const auto covers = [&] {
      std::vector<std::uint8_t> seen(variables, 0);
      for (std::size_t a = 0; a < count_atoms; ++a) if (selected[a]) bind_all(a, seen);
      for (std::size_t v = 0; v < variables; ++v) if (head[v] && !seen[v]) return false;
      return true;
    };
    for (int pass = 0; pass < 2 && options.residual_views; ++pass) {
      for (std::size_t a = 0; a < count_atoms; ++a) {
        if (!selected[a]) continue;
        bool has_head = false;
        for (const auto& term : atoms[a]) if (term.kind == Term::variable && head[term.id]) has_head = true;
        if (pass == 0 && has_head) continue;
        const auto before = component_count(selected);
        selected[a] = 0;
        if (!covers() || component_count(selected) > before) selected[a] = 1;
      }
    }
    prefix_local.assign(count_atoms, no_index);
    for (std::size_t a = 0; a < count_atoms; ++a) if (selected[a]) { prefix_local[a] = prefix_atoms.size(); prefix_atoms.push_back(a); }
    const auto p = prefix_atoms.size();
    std::vector<std::uint8_t> prefix_bound(variables, 0);
    for (const auto a : prefix_atoms) bind_all(a, prefix_bound);
    std::vector<std::size_t> parent(count_atoms), owner(variables, no_index);
    for (std::size_t a = 0; a < count_atoms; ++a) parent[a] = a;
    const auto root = [&](std::size_t x) { while (parent[x] != x) x = parent[x] = parent[parent[x]]; return x; };
    for (std::size_t a = 0; a < count_atoms; ++a) {
      if (selected[a]) continue;
      for (const auto& term : atoms[a]) {
        if (term.kind != Term::variable || prefix_bound[term.id]) continue;
        if (owner[term.id] == no_index) owner[term.id] = a;
        else parent[root(a)] = root(owner[term.id]);
      }
    }
    std::vector<std::uint8_t> keyed(variables, 0);
    view_atom_begin.push_back(0);
    view_key_begin.push_back(0);
    for (std::size_t first = 0; first < count_atoms; ++first) {
      if (selected[first] || root(first) != first) continue;
      std::fill(keyed.begin(), keyed.end(), std::uint8_t{0});
      for (std::size_t a = 0; a < count_atoms; ++a) {
        if (selected[a] || root(a) != first) continue;
        view_atoms.push_back(a);
        for (const auto& term : atoms[a]) if (term.kind == Term::variable && prefix_bound[term.id]) keyed[term.id] = 1;
      }
      for (std::size_t v = 0; v < variables; ++v) if (keyed[v]) view_keys.push_back(v);
      view_atom_begin.push_back(view_atoms.size());
      view_key_begin.push_back(view_keys.size());
    }
    const auto view_count = view_atom_begin.size() - 1;
    std::vector<std::uint8_t> is_bound, taken;
    for (std::size_t i = 0; i < p; ++i) {
      is_bound.assign(variables, 0); taken.assign(p, 0); taken[i] = 1;
      prefix_order.push_back(prefix_atoms[i]); prefix_steps.push_back(no_index); bind_all(prefix_atoms[i], is_bound);
      extend_order(prefix_atoms, taken, is_bound, prefix_order, prefix_steps);
    }
    std::vector<std::size_t> pool;
    for (std::size_t v = 0; v < view_count; ++v) {
      is_bound.assign(variables, 0); taken.assign(p, 0);
      for (auto k = view_key_begin[v]; k < view_key_begin[v + 1]; ++k) is_bound[view_keys[k]] = 1;
      extend_order(prefix_atoms, taken, is_bound, key_order, key_steps);
      const auto first = view_atom_begin[v], m = view_atom_begin[v + 1] - first;
      pool.assign(view_atoms.begin() + static_cast<std::ptrdiff_t>(first), view_atoms.begin() + static_cast<std::ptrdiff_t>(first + m));
      view_plan_begin.push_back(view_order.size());
      for (std::size_t i = 0; i < m; ++i) {
        is_bound.assign(variables, 0); taken.assign(m, 0); taken[i] = 1;
        view_order.push_back(pool[i]); view_steps.push_back(no_index); bind_all(pool[i], is_bound);
        extend_order(pool, taken, is_bound, view_order, view_steps);
      }
    }
    view_plan_begin.push_back(view_order.size());
  }

  // ------------------------------------------------------------------ walk
  void work(std::uint64_t amount = 1) {
    metrics_->work += amount;
    if (options.work_limit && !unlimited_ && metrics_->work > *options.work_limit)
      throw Error("fallback_work_limit", "fallback work grant exhausted");
  }
  bool match(std::size_t atom, RowView row) {
    const auto& terms = atoms[atom];
    for (std::size_t field = 0; field < terms.size(); ++field) {
      const auto& term = terms[field];
      if (term.kind == Term::variable) {
        const auto v = term.id;
        ++metrics_->term_tests;
        if (bound[v]) { if (!same(assignment[v], row[field])) return false; }
        else { assignment[v] = row[field]; bound[v] = 1; trail.push_back(v); ++metrics_->assignments; }
      } else if (term.kind == Term::constant) {
        ++metrics_->term_tests;
        if (!same(row[field], constants[term.id])) return false;
      }
    }
    return true;
  }
  void restore(std::size_t mark) {
    while (trail.size() > mark) { bound[trail.back()] = 0; trail.pop_back(); }
  }
  // Phase 0: committed rows (bucket chain or scan); phase 1: the inserted row
  // for later occurrences of the changed table under the delta rule; 2: done.
  void open(std::size_t depth, std::size_t atom, std::size_t index) {
    auto& cursor = cursors[depth];
    cursor.mark = trail.size();
    cursor.phase = 0;
    if (index == no_index) { cursor.id = 0; return; }
    const auto& spec = indices[index];
    key_cells.clear();
    for (const auto field : spec.positions) {
      const auto& term = atoms[atom][field];
      key_cells.push_back(term.kind == Term::constant ? constants[term.id] : assignment[term.id]);
    }
    const auto key = spec.domain->find(key_cells.data(), identity.data());
    cursor.id = key ? tables[spec.table].rows.bucket(spec.slot, *key) : no_entry;
  }
  std::optional<RowView> next_candidate(std::size_t depth, std::size_t anchor, bool delta_rule, std::size_t atom, std::size_t index) {
    auto& cursor = cursors[depth];
    const auto table = atom_table[atom];
    const bool same = delta_rule && table == table_;
    const auto skip = (!insert_ && same && atom < anchor) ? stored_ : no_entry;
    const auto& source = tables[table];
    const auto& rows = source.rows;
    if (cursor.phase == 0) {
      if (index == no_index) {
        while (cursor.id < rows.ids()) {
          const auto id = cursor.id++;
          if (rows.live(id) && id != skip) { work(); ++metrics_->row_visits; return source.domain->view(rows.key(id), cursor.scratch.data()); }
        }
      } else {
        const auto slot = indices[index].slot;
        while (cursor.id != no_entry) {
          const auto id = cursor.id;
          cursor.id = rows.next(slot, id);
          rows.prefetch(cursor.id);
          if (id != skip) { work(); ++metrics_->row_visits; return source.domain->view(rows.key(id), cursor.scratch.data()); }
        }
      }
      cursor.phase = 1;
    }
    if (cursor.phase == 1) {
      cursor.phase = 2;
      if (insert_ && same && atom > anchor) { work(); ++metrics_->row_visits; return row_; }
    }
    return std::nullopt;
  }
  template<class Done>
  void walk(std::size_t anchor, bool delta_rule, const std::size_t* order, const std::size_t* steps,
      std::size_t start, std::size_t length, Done&& done) {
    if (start >= length) { done(); return; }
    const auto entry = trail.size();
    std::size_t depth = start;
    open(depth, order[depth], steps[depth]);
    for (;;) {
      const auto candidate = next_candidate(depth, anchor, delta_rule, order[depth], steps[depth]);
      if (!candidate) {
        if (depth == start) break;
        --depth;
        continue;
      }
      restore(cursors[depth].mark);
      if (!match(order[depth], *candidate)) continue;
      if (depth + 1 == length) done();
      else { ++depth; open(depth, order[depth], steps[depth]); }
    }
    restore(entry);
  }
  // Key-holding pending entries: count one witness of `key_variables` in `map`.
  void count_witness(KeyDomain& domain, const std::vector<std::uint32_t>& key_variables, KeyMap& map,
      std::vector<std::uint32_t>& ids) {
    work();
    ++metrics_->witnesses;
    if (const auto key = domain.find(assignment.data(), key_variables.data())) {
      if (const auto found = map.find(*key); found != no_entry) { ++map.payload(found)[0]; return; }
    }
    collector.reserve(1);  // a later release (publish/discard) cannot allocate
    const auto key = domain.acquire(assignment.data(), key_variables.data());
    std::uint32_t id;
    try { id = map.insert(key); }
    catch (...) { domain.release(key); throw; }
    map.payload(id)[0] = 1;
    try { ids.push_back(id); }
    catch (...) { map.erase(id); domain.release(key); throw; }
  }
  bool present(std::size_t v, bool updated) {
    auto& view = views[v];
    const auto key = view.domain->find(assignment.data(), view.variables.data());
    if (!key) return false;
    const auto found = view.counts.find(*key);
    std::uint64_t count = found == no_entry ? 0 : view.counts.payload(found)[0];
    if (updated && touched[v]) {
      const auto delta = view.delta.find(*key);
      if (delta != no_entry) {
        const auto change = view.delta.payload(delta)[0];
        count = insert_ ? count + change : count - change;
      }
    }
    return count > 0;
  }
  void maintain_views() {
    for (std::size_t v = 0; v < touched.size(); ++v) {
      if (!touched[v]) continue;
      const auto first = view_atom_begin[v], m = view_atom_begin[v + 1] - first;
      for (std::size_t i = 0; i < m; ++i) {
        const auto anchor = view_atoms[first + i];
        if (atom_table[anchor] != table_) continue;
        restore(0);
        if (!match(anchor, row_)) continue;
        const auto base = view_plan_begin[v] + i * m;
        walk(anchor, true, &view_order[base], &view_steps[base], 1, m,
            [&] { count_witness(*views[v].domain, views[v].variables, views[v].delta, views[v].delta_ids); });
      }
    }
    restore(0);
  }
  void propagate_flips() {
    const auto p = prefix_atoms.size();
    for (std::size_t v = 0; v < views.size(); ++v) {
      auto& view = views[v];
      for (const auto id : view.delta_ids) {
        const auto key = view.delta.key(id);
        const auto delta = view.delta.payload(id)[0];
        const auto found = view.counts.find(key);
        const std::uint64_t before = found == no_entry ? 0 : view.counts.payload(found)[0];
        require(insert_ || before >= delta, "view count underflow");
        if (insert_) require(before <= std::numeric_limits<std::uint64_t>::max() - delta, "view count overflow");
        const auto after = insert_ ? before + delta : before - delta;
        if ((before == 0) == (after == 0)) continue;
        restore(0);
        const auto cells = view.domain->view(key, key_scratch.data());
        for (std::size_t field = 0; field < view.variables.size(); ++field) {
          const auto variable = view.variables[field];
          assignment[variable] = cells[field];
          bound[variable] = 1;
          trail.push_back(variable);
        }
        walk(0, false, key_order.data() + v * p, key_steps.data() + v * p, 0, p, [&] {
          for (std::size_t j = 0; j < views.size(); ++j) if (j != v && !present(j, j < v)) return;
          count_witness(*head_domain, head_variables, supports, support_ids);
        });
        restore(0);
      }
    }
  }
  void propagate_prefix() {
    const auto p = prefix_atoms.size();
    for (std::size_t i = 0; i < p; ++i) {
      const auto anchor = prefix_atoms[i];
      if (atom_table[anchor] != table_) continue;
      restore(0);
      if (!match(anchor, row_)) continue;
      walk(anchor, true, prefix_order.data() + i * p, prefix_steps.data() + i * p, 1, p, [&] {
        for (std::size_t j = 0; j < views.size(); ++j) if (!present(j, true)) return;
        count_witness(*head_domain, head_variables, supports, support_ids);
      });
    }
    restore(0);
  }

  // ---------------------------------------------------------------- events
  bool prepare(TableId table, SetOperation operation, RowView row, AnswerSink* sink, CyclicMetrics* metrics) {
    require(!pending, "keyed cyclic event already pending");
    require(table.value < tables.size(), "unknown source table");
    auto& source = tables[table.value];
    require(row.size() == types[table.value].size(), "row width differs from its table");
    scratch_metrics = {};
    metrics_ = metrics ? metrics : &scratch_metrics;
    insert_ = operation == SetOperation::insert;
    table_ = static_cast<std::uint32_t>(table.value);
    row_ = row;
    const auto existing_key = source.domain->find(row.cells());
    const auto existing = existing_key ? source.rows.find(*existing_key) : no_entry;
    if (insert_ ? existing != no_entry : existing == no_entry) return false;
    stored_ = existing;
    pending = true;
    try {
      if (used[table_] && !query.contradiction) {
        for (std::size_t v = 0; v < touched.size(); ++v) {
          touched[v] = 0;
          for (auto i = view_atom_begin[v]; i < view_atom_begin[v + 1]; ++i)
            if (atom_table[view_atoms[i]] == table_) touched[v] = 1;
        }
        maintain_views();
        propagate_flips();
        propagate_prefix();
        report(sink);
      }
      reserve_publication();
    } catch (...) {
      discard();
      throw;
    }
    return true;
  }
  // Answer changes in support order; publication capacity is reserved after.
  void report(AnswerSink* sink) {
    std::size_t fresh = 0, removed = 0;
    std::array<ScalarView, 2> scratch{};
    for (const auto id : support_ids) {
      const auto key = supports.key(id);
      const auto count = supports.payload(id)[0];
      const auto found = answers.find(key);
      if (insert_) {
        if (found != no_entry) {
          require(answers.payload(found)[0] <= std::numeric_limits<std::uint64_t>::max() - count, "answer support overflow");
          continue;
        }
        ++fresh;
        if (answers.size() + fresh > options.answer_limit)
          throw Error("fallback_row_limit", "fallback distinct-result row limit exceeded");
        ++metrics_->added;
        if (sink) sink->answer(SetOperation::insert, head_domain->view(key, scratch.data()));
      } else {
        require(found != no_entry && answers.payload(found)[0] >= count, "answer support underflow");
        if (answers.payload(found)[0] == count) {
          ++removed;
          ++metrics_->removed;
          if (sink) sink->answer(SetOperation::erase, head_domain->view(key, scratch.data()));
        }
      }
    }
    fresh_answers_ = fresh; removed_answers_ = removed;
  }
  void reserve_publication() {
    auto& source = tables[table_];
    std::size_t releases = support_ids.size() + (insert_ ? 0 : 1 + source.indexes.size());
    row_secondary_.resize(source.indexes.size());
    if (insert_) {
      answers.reserve(fresh_answers_);
      for (auto& view : views) {
        std::size_t fresh = 0;
        for (const auto id : view.delta_ids) if (view.counts.find(view.delta.key(id)) == no_entry) ++fresh;
        view.counts.reserve(fresh);
        releases += view.delta_ids.size();
      }
      source.rows.reserve(1);
      collector.reserve(1 + source.indexes.size());  // the row's keys, released if discarded
      row_key_ = source.domain->acquire(row_.cells().data(), identity.data());
      row_key_owned_ = true;
      for (std::size_t s = 0; s < source.indexes.size(); ++s) {
        const auto& index = indices[source.indexes[s]];
        row_secondary_[s] = index.domain->acquire(row_.cells().data(), index.positions.data());
        ++secondary_owned_;
      }
    } else {
      for (auto& view : views) releases += 2 * view.delta_ids.size();
    }
    collector.reserve(releases + removed_answers_);
  }
  void clear_pending() noexcept {
    for (const auto id : support_ids) { const auto key = supports.key(id); supports.erase(id); head_domain->release(key); }
    support_ids.clear();
    for (auto& view : views) {
      for (const auto id : view.delta_ids) { const auto key = view.delta.key(id); view.delta.erase(id); view.domain->release(key); }
      view.delta_ids.clear();
    }
    restore(0);
  }
  void discard() noexcept {
    if (!pending) return;
    clear_pending();
    auto& source = tables[table_];
    if (row_key_owned_) source.domain->release(row_key_);
    for (std::size_t s = 0; s < secondary_owned_; ++s) indices[source.indexes[s]].domain->release(row_secondary_[s]);
    row_key_owned_ = false; secondary_owned_ = 0;
    pending = false;
    collector.seal();
  }
  void publish() noexcept {
    if (!pending) return;
    auto& source = tables[table_];
    for (const auto id : support_ids) {
      const auto key = supports.key(id);
      const auto count = supports.payload(id)[0];
      const auto found = answers.find(key);
      if (insert_) {
        if (found != no_entry) { answers.payload(found)[0] += count; continue; }
        head_domain->retain(key);
        answers.payload(answers.insert(key))[0] = count;  // capacity reserved
      } else {
        answers.payload(found)[0] -= count;
        if (answers.payload(found)[0] == 0) { answers.erase(found); head_domain->release(key); }
      }
    }
    for (auto& view : views) {
      for (const auto id : view.delta_ids) {
        const auto key = view.delta.key(id);
        const auto delta = view.delta.payload(id)[0];
        const auto found = view.counts.find(key);
        if (insert_) {
          if (found != no_entry) view.counts.payload(found)[0] += delta;
          else { view.domain->retain(key); view.counts.payload(view.counts.insert(key))[0] = delta; }
        } else {
          view.counts.payload(found)[0] -= delta;
          if (view.counts.payload(found)[0] == 0) { view.counts.erase(found); view.domain->release(key); }
        }
      }
    }
    clear_pending();
    if (insert_) {
      source.rows.insert(row_key_, row_secondary_.data());  // capacity reserved; the keys move in
      row_key_owned_ = false; secondary_owned_ = 0;
    } else {
      const auto key = source.rows.key(stored_);
      for (std::size_t s = 0; s < source.indexes.size(); ++s) row_secondary_[s] = source.rows.secondary(stored_, s);
      source.rows.erase(stored_);
      source.domain->release(key);
      for (std::size_t s = 0; s < source.indexes.size(); ++s) indices[source.indexes[s]].domain->release(row_secondary_[s]);
    }
    pending = false;
    collector.seal();
  }

  // ------------------------------------------------------------ diagnostics
  // Recount every view and every answer support from the committed rows.
  void check_invariants() const {
    require(!pending, "invariants are checked between events");
    for (const auto& table : tables) { table.domain->check_invariants(); table.rows.check_invariants(); }
    for (const auto& view : views) { view.domain->check_invariants(); view.counts.check_invariants(); }
    head_domain->check_invariants();
    answers.check_invariants();
    auto& self = const_cast<Impl&>(*this);
    std::vector<std::map<Row, std::uint64_t>> counted(views.size());
    std::array<ScalarView, 2> scratch{};
    self.insert_ = true; self.table_ = static_cast<std::uint32_t>(-1); self.stored_ = no_entry;
    self.metrics_ = &self.scratch_metrics; self.unlimited_ = true;
    struct Limited { bool& flag; ~Limited() { flag = false; } } limited{self.unlimited_};
    for (std::size_t v = 0; v < views.size(); ++v) {
      const auto first = view_atom_begin[v], m = view_atom_begin[v + 1] - first;
      const auto base = view_plan_begin[v];
      self.walk(0, false, &view_order[base], &view_steps[base], 0, m, [&] {
        Row key;
        for (const auto variable : views[v].variables) key.push_back(storage::export_scalar(assignment[variable]));
        ++counted[v][key];
      });
      std::size_t live = 0;
      for (std::uint32_t id = 0; id < views[v].counts.ids(); ++id) {
        if (!views[v].counts.live(id)) continue;
        ++live;
        const auto cells = views[v].domain->view(views[v].counts.key(id), scratch.data());
        const auto expected = counted[v].find(storage::export_row(cells));
        require(expected != counted[v].end() && expected->second == views[v].counts.payload(id)[0], "view count differs from a recount");
      }
      require(live == counted[v].size(), "view key set differs from a recount");
      static_cast<void>(first);
    }
    std::map<Row, std::uint64_t> support;
    const auto p = prefix_atoms.size();
    if (p == 0) { if (!query.contradiction && query.atoms.empty()) support[Row{}] = 1; }
    else self.walk(0, false, prefix_order.data(), prefix_steps.data(), 0, p, [&] {
      for (std::size_t j = 0; j < views.size(); ++j) if (!self.present(j, false)) return;
      Row key;
      for (const auto variable : head_variables) key.push_back(storage::export_scalar(assignment[variable]));
      ++support[key];
    });
    std::size_t live = 0;
    for (std::uint32_t id = 0; id < answers.ids(); ++id) {
      if (!answers.live(id)) continue;
      ++live;
      const auto cells = head_domain->view(answers.key(id), scratch.data());
      const auto expected = support.find(storage::export_row(cells));
      require(expected != support.end() && expected->second == answers.payload(id)[0], "answer support differs from a recount");
    }
    require(live == support.size(), "answer set differs from a recount");
  }
};


// ------------------------------------------------------------------ GHD
// A generalized hypertree decomposition of the query: a partition of its
// atoms into bags such that the bag-level query (one atom per bag over the
// bag's needed variables: head variables and variables shared with another
// bag) is free-connex acyclic. Each multi-atom bag keeps the projection of its
// join onto its needed variables on a support-count engine (support counts
// cover the projected-away local variables); its tuple changes, and the source
// changes of single-atom bags, feed one keyed set engine (delta mode) over the
// bag-level query, whose row changes are the query's answer changes.
namespace {
using VariableSet = std::vector<std::uint32_t>;  // sorted, distinct
VariableSet atom_variables(const Atom& atom) {
  VariableSet out;
  for (const auto& term : atom.terms)
    if (const auto* variable = std::get_if<VariableId>(&term)) out.push_back(static_cast<std::uint32_t>(variable->value));
  std::sort(out.begin(), out.end());
  out.erase(std::unique(out.begin(), out.end()), out.end());
  return out;
}
// GYO reduction: alpha-acyclic iff ear removal empties the hypergraph.
bool alpha_acyclic(std::vector<VariableSet> edges) {
  for (;;) {
    if (edges.size() <= 1) return true;
    bool changed = false;
    std::map<std::uint32_t, std::uint32_t> occurrences;
    for (const auto& edge : edges) for (const auto v : edge) ++occurrences[v];
    for (auto& edge : edges) {
      const auto end = std::remove_if(edge.begin(), edge.end(), [&](std::uint32_t v) { return occurrences[v] == 1; });
      if (end != edge.end()) { edge.erase(end, edge.end()); changed = true; }
    }
    for (std::size_t i = 0; i < edges.size(); ++i) {
      bool contained = edges[i].empty();
      for (std::size_t j = 0; j < edges.size() && !contained; ++j)
        if (j != i && std::includes(edges[j].begin(), edges[j].end(), edges[i].begin(), edges[i].end()) &&
            (edges[j] != edges[i] || j < i)) contained = true;
      if (contained) { edges.erase(edges.begin() + static_cast<std::ptrdiff_t>(i)); changed = true; break; }
    }
    if (!changed) return false;
  }
}
// Each bag keeps only the variables needed outside it: head variables and
// variables shared with another bag (its other variables are projected away,
// with support counts, inside the bag).
std::vector<VariableSet> needed_variables(const std::vector<VariableSet>& edges, const VariableSet& head) {
  std::vector<VariableSet> needed(edges.size());
  for (std::size_t b = 0; b < edges.size(); ++b) {
    for (const auto v : edges[b]) {
      bool keep = std::binary_search(head.begin(), head.end(), v);
      for (std::size_t o = 0; o < edges.size() && !keep; ++o)
        keep = o != b && std::binary_search(edges[o].begin(), edges[o].end(), v);
      if (keep) needed[b].push_back(v);
    }
  }
  return needed;
}
// The best partition (smallest largest bag, then fewest atoms in multi-atom
// bags), or nothing when no partition into two or more connected bags gives a
// free-connex acyclic bag-level query. Exhaustive over set partitions.
std::optional<std::vector<std::vector<std::uint32_t>>> decompose(const Query& query) {
  const auto n = query.atoms.size();
  if (n < 3 || n > 10 || query.head.empty() || query.contradiction) return std::nullopt;
  std::vector<VariableSet> variables(n);
  for (std::size_t i = 0; i < n; ++i) variables[i] = atom_variables(query.atoms[i]);
  VariableSet head;
  for (const auto& output : query.head) head.push_back(static_cast<std::uint32_t>(output.variable.value));
  std::sort(head.begin(), head.end());
  head.erase(std::unique(head.begin(), head.end()), head.end());
  std::vector<std::uint32_t> label(n, 0);
  std::optional<std::vector<std::vector<std::uint32_t>>> best;
  std::tuple<std::size_t, std::size_t> best_score{SIZE_MAX, SIZE_MAX};
  auto bag_variables_of = [&](const std::vector<std::uint32_t>& group) {
    VariableSet edge;
    for (const auto atom : group) edge.insert(edge.end(), variables[atom].begin(), variables[atom].end());
    std::sort(edge.begin(), edge.end());
    edge.erase(std::unique(edge.begin(), edge.end()), edge.end());
    return edge;
  };
  auto evaluate = [&](std::uint32_t bags) {
    if (bags < 2) return;
    std::vector<std::vector<std::uint32_t>> groups(bags);
    for (std::uint32_t i = 0; i < n; ++i) groups[label[i]].push_back(i);
    // A single atom whose variables lie inside a multi-atom bag joins it: it
    // only filters that bag's join (a wedge bag plus its closing edge is the
    // triangle), never widens it.
    for (std::size_t g = 0; g < groups.size(); ++g) {
      if (groups[g].size() != 1) continue;
      for (std::size_t h = 0; h < groups.size(); ++h) {
        if (h == g || groups[h].size() < 2) continue;
        const auto host = bag_variables_of(groups[h]);
        const auto& own = variables[groups[g][0]];
        if (std::includes(host.begin(), host.end(), own.begin(), own.end())) {
          groups[h].push_back(groups[g][0]); std::sort(groups[h].begin(), groups[h].end()); groups[g].clear(); break;
        }
      }
    }
    groups.erase(std::remove_if(groups.begin(), groups.end(), [](const auto& group) { return group.empty(); }), groups.end());
    if (groups.size() < 2) return;
    std::size_t largest = 0, shared = 0;
    std::vector<VariableSet> edges;
    for (const auto& group : groups) {
      largest = std::max(largest, group.size());
      if (group.size() > 1) shared += group.size();
      VariableSet edge;
      for (const auto atom : group) edge.insert(edge.end(), variables[atom].begin(), variables[atom].end());
      std::sort(edge.begin(), edge.end());
      edge.erase(std::unique(edge.begin(), edge.end()), edge.end());
      // A multi-atom bag must be connected through shared variables.
      if (group.size() > 1) {
        std::vector<bool> reached(group.size(), false);
        std::vector<std::size_t> stack{0};
        reached[0] = true;
        while (!stack.empty()) {
          const auto at = stack.back(); stack.pop_back();
          for (std::size_t j = 0; j < group.size(); ++j) {
            if (reached[j]) continue;
            const auto& a = variables[group[at]];
            const auto& b = variables[group[j]];
            std::vector<std::uint32_t> common;
            std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::back_inserter(common));
            if (!common.empty()) { reached[j] = true; stack.push_back(j); }
          }
        }
        if (std::find(reached.begin(), reached.end(), false) != reached.end()) return;
      }
      edges.push_back(std::move(edge));
    }
    const std::tuple<std::size_t, std::size_t> score{largest, shared};
    if (!(score < best_score)) return;
    // The bag-level query joins the bags' projections.
    edges = needed_variables(edges, head);
    for (std::size_t b = 0; b < edges.size(); ++b)
      if (edges[b].empty() && groups[b].size() > 1) return;  // a detached multi-atom bag
    if (!alpha_acyclic(edges)) return;
    edges.push_back(head);
    if (!alpha_acyclic(edges)) return;
    best_score = score;
    best = std::move(groups);
  };
  std::function<void(std::uint32_t, std::uint32_t)> assign = [&](std::uint32_t i, std::uint32_t used) {
    if (i == n) { evaluate(used); return; }
    for (std::uint32_t value = 0; value <= used && value < n; ++value) {
      label[i] = value;
      assign(i + 1, std::max(used, value + 1));
    }
  };
  assign(0, 0);
  return best;
}
bool support_forced() {
  const char* forced = std::getenv("CROWN_CYCLIC_ENGINE");
  return forced && std::string_view(forced) == "support";
}
}  // namespace

struct CyclicEngine::Ghd {
  struct Bag {
    std::unique_ptr<CyclicEngine> engine;  // multi-atom bags only
    std::vector<std::uint32_t> local;      // original table -> bag table (none if absent)
    TableId derived{};                     // the bag's table in the bag-level catalog
  };
  // Answer rows of the bag-level engine go to the caller's sink and are counted.
  struct Answers final : RowSink {
    AnswerSink* out = nullptr;
    std::uint64_t added = 0, removed = 0;
    void row(SetOperation operation, storage::RowView values) override {
      (operation == SetOperation::insert ? added : removed) += 1;
      if (out) out->answer(operation, values);
    }
  };
  // A bag's tuple changes stage into the bag-level engine as they are reported.
  struct Forward final : AnswerSink {
    Ghd& owner;
    TableId derived;
    Forward(Ghd& ghd, TableId table) noexcept : owner(ghd), derived(table) {}
    void answer(SetOperation operation, storage::RowView row) override {
      const bool staged = owner.top->stage(derived, operation, row, &owner.answers_sink);
      require(staged, "bag tuple change disagrees with the bag-level engine");
    }
  };
  CyclicOptions options;
  std::vector<std::vector<ScalarType>> table_types;
  std::vector<ScalarType> head_types;
  std::vector<Bag> bags;                                 // multi-atom bags
  std::vector<std::vector<std::uint32_t>> table_bags;   // original table -> multi-atom bags
  std::vector<bool> staged_directly;                     // original table -> rows go to the bag-level engine
  std::unique_ptr<SetEngine> top;
  Answers answers_sink;
  std::uint64_t committed = 0;
  bool pending = false;
  std::vector<std::uint32_t> prepared;

  static std::unique_ptr<Ghd> create(const Catalog& catalog, const Query& query, const CyclicOptions& options) {
    const auto partition = decompose(query);
    if (!partition) return nullptr;
    auto out = std::make_unique<Ghd>();
    out->options = options;
    for (const auto& table : catalog.tables) {
      auto& types = out->table_types.emplace_back();
      for (const auto& column : table.columns) types.push_back(column.type);
    }
    for (const auto& field : query.head) out->head_types.push_back(query.variables[field.variable.value].type);
    // The bag-level query: original single-atom bags, one derived table per
    // multi-atom bag (its variables, in variable order).
    Catalog top_catalog = catalog;
    for (auto& table : top_catalog.tables) table.constraints.clear();
    Query top_query;
    top_query.variables = query.variables;
    top_query.head = query.head;
    out->table_bags.resize(catalog.tables.size());
    out->staged_directly.assign(catalog.tables.size(), true);
    std::vector<bool> in_atom(catalog.tables.size(), false), single(catalog.tables.size(), false);
    VariableSet head;
    for (const auto& field : query.head) head.push_back(static_cast<std::uint32_t>(field.variable.value));
    std::sort(head.begin(), head.end());
    head.erase(std::unique(head.begin(), head.end()), head.end());
    std::vector<VariableSet> group_edges;
    for (const auto& group : *partition) {
      VariableSet edge;
      for (const auto atom : group) {
        const auto vars = atom_variables(query.atoms[atom]);
        edge.insert(edge.end(), vars.begin(), vars.end());
      }
      std::sort(edge.begin(), edge.end());
      edge.erase(std::unique(edge.begin(), edge.end()), edge.end());
      group_edges.push_back(std::move(edge));
    }
    const auto group_needed = needed_variables(group_edges, head);
    if (std::getenv("CROWN_GHD_DEBUG")) {
      for (std::size_t g = 0; g < partition->size(); ++g) {
        std::fprintf(stderr, "ghd bag %zu atoms:", g);
        for (const auto atom : (*partition)[g]) std::fprintf(stderr, " %s", query.atoms[atom].occurrence.c_str());
        std::fprintf(stderr, " needed:");
        for (const auto v : group_needed[g]) std::fprintf(stderr, " %s", query.variables[v].name.c_str());
        std::fprintf(stderr, "\n");
      }
    }
    std::size_t group_index = 0;
    for (const auto& group : *partition) {
      const auto& needed = group_needed[group_index++];
      if (group.size() == 1) {
        top_query.atoms.push_back(query.atoms[group[0]]);
        single[query.atoms[group[0]].table.value] = true;
        in_atom[query.atoms[group[0]].table.value] = true;
        continue;
      }
      VariableSet bag_variables;
      for (const auto atom : group) {
        const auto vars = atom_variables(query.atoms[atom]);
        bag_variables.insert(bag_variables.end(), vars.begin(), vars.end());
      }
      std::sort(bag_variables.begin(), bag_variables.end());
      bag_variables.erase(std::unique(bag_variables.begin(), bag_variables.end()), bag_variables.end());
      std::vector<std::uint32_t> local_variable(query.variables.size(), UINT32_MAX);
      for (std::uint32_t i = 0; i < bag_variables.size(); ++i) local_variable[bag_variables[i]] = i;
      // The bag's own query: its atoms over their tables, head = its variables.
      Catalog bag_catalog;
      Query bag_query;
      Bag bag;
      bag.local.assign(catalog.tables.size(), UINT32_MAX);
      std::vector<bool> nullable(bag_variables.size(), false);
      for (const auto atom_index : group) {
        const auto& atom = query.atoms[atom_index];
        const auto t = static_cast<std::uint32_t>(atom.table.value);
        in_atom[t] = true;
        if (bag.local[t] == UINT32_MAX) {
          bag.local[t] = static_cast<std::uint32_t>(bag_catalog.tables.size());
          auto table = catalog.tables[t];
          table.constraints.clear();
          bag_catalog.tables.push_back(std::move(table));
        }
        Atom local{atom.occurrence, TableId{bag.local[t]}, {}};
        for (std::size_t c = 0; c < atom.terms.size(); ++c) {
          const auto& term = atom.terms[c];
          if (const auto* variable = std::get_if<VariableId>(&term)) {
            const auto v = local_variable[variable->value];
            local.terms.emplace_back(VariableId{v});
            if (catalog.tables[t].columns[c].nullable) nullable[v] = true;
          } else local.terms.push_back(term);
        }
        bag_query.atoms.push_back(std::move(local));
      }
      // The bag's head (and derived table) is its needed variables, in order.
      Table derived;
      derived.name = "__crown_ghd_bag_" + std::to_string(out->bags.size());
      for (std::uint32_t i = 0; i < bag_variables.size(); ++i) bag_query.variables.push_back(query.variables[bag_variables[i]]);
      for (const auto v : needed) {
        const auto i = local_variable[v];
        bag_query.head.push_back({VariableId{i}, "v" + std::to_string(v)});
        Column column{"v" + std::to_string(v), query.variables[v].type};
        column.nullable = nullable[i];
        derived.columns.push_back(std::move(column));
      }
      bag.derived = TableId{top_catalog.tables.size()};
      Atom derived_atom{derived.name, bag.derived, {}};
      for (const auto v : needed) derived_atom.terms.emplace_back(VariableId{v});
      top_catalog.tables.push_back(std::move(derived));
      top_query.atoms.push_back(std::move(derived_atom));
      CyclicOptions sub = options;
      sub.decompose = false;
      sub.residual_views = false;
      sub.answer_limit = std::numeric_limits<std::uint64_t>::max();
      if (sub.gc.mode == storage::keyed::GcMode::background) sub.gc.mode = storage::keyed::GcMode::manual;  // one collector thread at most
      if (const auto problem = CyclicEngine::unsupported(bag_catalog, bag_query); !problem.empty()) {
        if (std::getenv("CROWN_GHD_DEBUG")) std::fprintf(stderr, "ghd: bag: %s\n", problem.c_str());
        return nullptr;
      }
      bag.engine = std::make_unique<CyclicEngine>(bag_catalog, bag_query, sub);
      for (std::size_t t = 0; t < bag.local.size(); ++t)
        if (bag.local[t] != UINT32_MAX) out->table_bags[t].push_back(static_cast<std::uint32_t>(out->bags.size()));
      out->bags.push_back(std::move(bag));
    }
    // Tables of no single-atom bag keep their rows in their multi-atom bags.
    for (std::size_t t = 0; t < catalog.tables.size(); ++t) out->staged_directly[t] = single[t] || !in_atom[t];
    // The bag-level query declares only the variables its atoms use (bags
    // project their local variables away), renumbered in order.
    {
      std::vector<std::uint32_t> renumber(query.variables.size(), UINT32_MAX);
      std::vector<Variable> used;
      for (auto& atom : top_query.atoms)
        for (auto& term : atom.terms)
          if (auto* variable = std::get_if<VariableId>(&term)) {
            auto& slot = renumber[variable->value];
            if (slot == UINT32_MAX) { slot = static_cast<std::uint32_t>(used.size()); used.push_back(query.variables[variable->value]); }
            *variable = VariableId{slot};
          }
      for (auto& field : top_query.head) {
        if (renumber[field.variable.value] == UINT32_MAX) return nullptr;  // a head variable outside every bag
        field.variable = VariableId{renumber[field.variable.value]};
      }
      top_query.variables = std::move(used);
    }
    try {
      const bool debug = std::getenv("CROWN_GHD_DEBUG") != nullptr;
      const auto tree = planner::minimum_tree(top_catalog, top_query);
      if (tree.status != planner::OracleStatus::proven_minimum || !tree.tree) {
        if (debug) std::fprintf(stderr, "ghd: no bag-level tree: %s\n", tree.reason.c_str());
        return nullptr;
      }
      const auto program = CompiledProgram::standalone(planner::lower_tree(top_catalog, top_query, *tree.tree));
      if (const auto problem = SetEngine::unsupported(program); !problem.empty()) {
        if (debug) std::fprintf(stderr, "ghd: set engine: %s\n", problem.c_str());
        return nullptr;
      }
      EngineOptions engine;
      engine.delta = true; engine.gc = options.gc; engine.sql_view = false;
      engine.memory_limit_bytes = options.memory_limit_bytes;
      out->top = std::make_unique<SetEngine>(program, engine);
    } catch (const Error& failure) {
      if (std::getenv("CROWN_GHD_DEBUG")) std::fprintf(stderr, "ghd: %s\n", failure.what());
      return nullptr;  // no bag-level plan: the support-count engine runs the query
    }
    return out;
  }

  bool contains(TableId table, storage::RowView row) const {
    if (staged_directly[table.value]) return top->contains(table, row);
    const auto& bag = bags[table_bags[table.value].front()];
    return bag.engine->contains(TableId{bag.local[table.value]}, row);
  }
  bool prepare(TableId table, SetOperation operation, storage::RowView row, AnswerSink* sink, CyclicMetrics* metrics) {
    require(!pending, "keyed cyclic event already pending");
    require(table.value < table_types.size(), "unknown source table");
    require(row.size() == table_types[table.value].size(), "row width differs from its table");
    const bool insert = operation == SetOperation::insert;
    if (contains(table, row) == insert) return false;
    pending = true;
    answers_sink = Answers{};
    answers_sink.out = sink;
    CyclicMetrics total;
    try {
      top->begin();
      if (staged_directly[table.value]) {
        const bool staged = top->stage(table, operation, row, &answers_sink);
        require(staged, "source change disagrees with the bag-level engine");
      }
      for (const auto b : table_bags[table.value]) {
        auto& bag = bags[b];
        Forward forward(*this, bag.derived);
        CyclicMetrics work;
        prepared.push_back(b);
        const bool staged = bag.engine->prepare(TableId{bag.local[table.value]}, operation, row, &forward, &work);
        require(staged, "source change disagrees with its bag");
        total.work += work.work; total.row_visits += work.row_visits; total.term_tests += work.term_tests;
        total.assignments += work.assignments; total.witnesses += work.witnesses;
      }
      if (answers_sink.added > answers_sink.removed &&
          committed + (answers_sink.added - answers_sink.removed) > options.answer_limit)
        throw Error("fallback_row_limit", "fallback distinct-result row limit exceeded");
    } catch (...) {
      discard();
      throw;
    }
    total.added = answers_sink.added; total.removed = answers_sink.removed;
    if (metrics) *metrics = total;
    return true;
  }
  void publish() noexcept {
    if (!pending) return;
    for (const auto b : prepared) bags[b].engine->publish();
    top->commit();
    committed = committed + answers_sink.added - answers_sink.removed;
    pending = false;
    for (const auto b : prepared) {
      auto& engine = *bags[b].engine;
      // Manual bag collectors (background mode): collect when their pool fills.
      if (options.gc.mode == storage::keyed::GcMode::background &&
          engine.collector().statistics().pending_bytes >= options.gc.retired_bytes) {
        try { engine.collector().collect(); } catch (...) {}
      }
    }
    prepared.clear();
  }
  void discard() noexcept {
    for (const auto b : prepared) bags[b].engine->discard();
    prepared.clear();
    if (top->active()) top->rollback();
    pending = false;
  }
  void snapshot(AnswerSink& sink) const {
    struct Adapter final : RowSink {
      AnswerSink& out;
      explicit Adapter(AnswerSink& target) noexcept : out(target) {}
      void row(SetOperation, storage::RowView values) override { out.answer(SetOperation::insert, values); }
    } adapter(sink);
    top->snapshot(adapter);
  }
  std::uint64_t rows(TableId table) const {
    if (staged_directly[table.value]) return top->rows(table);
    const auto& bag = bags[table_bags[table.value].front()];
    return bag.engine->rows(TableId{bag.local[table.value]});
  }
  Database sources() const {
    Database out;
    out.tables.resize(table_types.size());
    const auto direct = top->sources();
    for (std::size_t t = 0; t < table_types.size(); ++t) {
      if (staged_directly[t]) { out.tables[t] = direct.tables[t]; continue; }
      const auto& bag = bags[table_bags[t].front()];
      out.tables[t] = bag.engine->sources().tables[bag.local[t]];
    }
    return out;
  }
  void collect() {
    top->collect();
    for (auto& bag : bags) bag.engine->collect();
  }
  void check_invariants() const {
    top->check_invariants();
    for (const auto& bag : bags) bag.engine->check_invariants();
  }
};

std::string CyclicEngine::unsupported(const Catalog& catalog, const Query& query) {
  for (const auto& atom : query.atoms) {
    if (atom.table.value >= catalog.tables.size()) return "atom names a missing table";
    if (atom.terms.size() != catalog.tables[atom.table.value].columns.size()) return "atom arity differs from its table";
    for (const auto& term : atom.terms)
      if (const auto* variable = std::get_if<VariableId>(&term); variable && variable->value >= query.variables.size())
        return "atom names a missing variable";
  }
  for (const auto& table : catalog.tables)
    if (table.columns.size() > 64) return "more than 64 columns";
  for (const auto& field : query.head)
    if (field.variable.value >= query.variables.size()) return "head names a missing variable";
  return {};
}
CyclicEngine::CyclicEngine(const Catalog& catalog, const Query& query, CyclicOptions options) {
  if (options.decompose && !support_forced() && unsupported(catalog, query).empty())
    ghd_ = Ghd::create(catalog, query, options);
  if (!ghd_) impl_ = std::make_unique<Impl>(catalog, query, options);
}
CyclicEngine::~CyclicEngine() = default;
std::string_view CyclicEngine::algorithm() const noexcept { return ghd_ ? "ghd" : "support"; }
bool CyclicEngine::prepare(TableId table, SetOperation operation, storage::RowView row, AnswerSink* sink, CyclicMetrics* metrics) {
  if (ghd_) return ghd_->prepare(table, operation, row, sink, metrics);
  return impl_->prepare(table, operation, row, sink, metrics);
}
void CyclicEngine::publish() noexcept { if (ghd_) ghd_->publish(); else impl_->publish(); }
void CyclicEngine::discard() noexcept { if (ghd_) ghd_->discard(); else impl_->discard(); }
bool CyclicEngine::pending() const noexcept { return ghd_ ? ghd_->pending : impl_->pending; }
std::size_t CyclicEngine::answers() const noexcept {
  if (ghd_) return static_cast<std::size_t>(ghd_->committed);
  return impl_->answers.size() + impl_->answer_root;
}
bool CyclicEngine::has_answer() const noexcept { return answers() > 0; }
void CyclicEngine::snapshot(AnswerSink& sink) const {
  if (ghd_) { ghd_->snapshot(sink); return; }
  const auto& d = *impl_;
  if (d.answer_root) sink.answer(SetOperation::insert, storage::RowView{});
  std::array<ScalarView, 2> scratch{};
  for (std::uint32_t id = 0; id < d.answers.ids(); ++id)
    if (d.answers.live(id)) sink.answer(SetOperation::insert, d.head_domain->view(d.answers.key(id), scratch.data()));
}
std::uint64_t CyclicEngine::rows(TableId table) const {
  if (ghd_) return ghd_->rows(table);
  return impl_->tables.at(table.value).rows.size();
}
bool CyclicEngine::contains(TableId table, storage::RowView row) const {
  if (ghd_) return ghd_->contains(table, row);
  const auto& source = impl_->tables.at(table.value);
  const auto key = source.domain->find(row.cells());
  return key && source.rows.find(*key) != no_entry;
}
Database CyclicEngine::sources() const {
  if (ghd_) return ghd_->sources();
  const auto& d = *impl_;
  Database out;
  out.tables.resize(d.tables.size());
  std::array<ScalarView, 2> scratch{};
  for (std::size_t t = 0; t < d.tables.size(); ++t) {
    const auto& table = d.tables[t];
    for (std::uint32_t id = 0; id < table.rows.ids(); ++id)
      if (table.rows.live(id)) out.tables[t].insert(storage::export_row(table.domain->view(table.rows.key(id), scratch.data())));
  }
  return out;
}
std::span<const ScalarType> CyclicEngine::result_types() const noexcept {
  return ghd_ ? std::span<const ScalarType>(ghd_->head_types) : std::span<const ScalarType>(impl_->head_types);
}
storage::keyed::Collector& CyclicEngine::collector() noexcept { return ghd_ ? ghd_->top->collector() : impl_->collector; }
void CyclicEngine::collect() {
  if (ghd_) { ghd_->collect(); return; }
  auto& d = *impl_;
  d.collector.collect();
  for (auto& table : d.tables) table.rows.shrink();
  for (auto& view : d.views) { view.counts.shrink(); view.delta.shrink(); }
  d.answers.shrink(); d.supports.shrink();
}
void CyclicEngine::check_invariants() const { if (ghd_) ghd_->check_invariants(); else impl_->check_invariants(); }

}  // namespace crown::runtime::keyed
