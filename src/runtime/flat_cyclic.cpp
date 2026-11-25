#include "crown/runtime/flat_cyclic.hpp"
#include "flat_table.hpp"

#include <algorithm>
#include <limits>
#include <vector>

namespace crown::runtime {
namespace {
using namespace flat_detail;
constexpr std::size_t no_index = std::numeric_limits<std::size_t>::max();

struct Term {
  enum Kind : std::uint8_t { variable, constant, ignored } kind = ignored;
  std::uint32_t variable_id = 0;
  Word value = 0;
};
}  // namespace

// Incremental exact-set maintenance by presence propagation (runtime::fallback):
// a connected prefix P binding every head variable is enumerated explicitly;
// the remaining occurrences form residual components, each a view counting its
// completions per key (its variables shared with P). An answer's support is the
// number of P-assignments projecting to it whose view keys are all present.
// Updates first maintain touched views, then propagate keys whose count crosses
// zero to the P-assignments carrying them (earlier views use updated presence,
// later ones committed presence), then P-assignments that use the changed row.
// Self-joins: when occurrence k is bound to the changed row, earlier
// occurrences of that table exclude it and later ones include it.
struct FlatCyclicRuntime::Impl {
  Query query;
  Dictionary dictionary;
  std::vector<std::vector<ScalarType>> types;
  std::vector<std::vector<Term>> atoms;
  std::vector<std::uint32_t> atom_table;
  std::vector<std::uint8_t> used;
  struct Index { std::uint32_t table; std::vector<std::uint32_t> positions; std::uint32_t slot = 0; };
  std::vector<Index> indices;
  std::vector<Table> tables;
  std::vector<std::size_t> prefix_atoms, prefix_local, prefix_order, prefix_steps;
  std::vector<std::size_t> view_atom_begin, view_atoms, view_key_begin, view_keys, view_plan_begin, view_order,
      view_steps, key_order, key_steps;
  std::vector<Table> views, view_delta;
  std::vector<std::vector<std::uint32_t>> delta_ids;
  Table answers, supports;
  std::vector<std::uint32_t> support_ids;
  std::vector<ScalarType> head_types;
  // Walk state.
  std::vector<Word> assignment;
  std::vector<std::uint8_t> bound;
  std::vector<std::uint32_t> trail;
  struct Cursor { std::uint32_t id = none; std::uint8_t phase = 0; std::size_t mark = 0; };
  std::vector<Cursor> cursors;
  std::vector<Word> key, projected;
  // Current update.
  bool insert_ = true;
  std::uint32_t table_ = 0, stored_ = none;
  const Word* row_ = nullptr;
  std::vector<std::uint8_t> touched;

  Impl(const Catalog& catalog, const Query& source) : query(source) {
    if (auto problem = FlatCyclicRuntime::unsupported(catalog, source); !problem.empty()) fail(problem.c_str());
    for (const auto& table : catalog.tables) {
      types.emplace_back();
      for (const auto& column : table.columns) types.back().push_back(column.type);
    }
    used.assign(types.size(), 0);
    for (const auto& atom : query.atoms) {
      std::vector<Term> terms;
      for (const auto& term : atom.terms) {
        Term code;
        if (const auto* variable = std::get_if<VariableId>(&term)) { code.kind = Term::variable; code.variable_id = static_cast<std::uint32_t>(variable->value); }
        else if (const auto* value = std::get_if<Value>(&term)) { code.kind = Term::constant; code.value = dictionary.encode(*value); }
        terms.push_back(code);
      }
      atoms.push_back(std::move(terms));
      atom_table.push_back(static_cast<std::uint32_t>(atom.table.value));
      used[atom.table.value] = 1;
    }
    for (const auto& field : query.head) head_types.push_back(query.variables.at(field.variable.value).type);
    build_plan();
    std::vector<std::vector<std::vector<std::uint32_t>>> secondary(types.size());
    for (auto& index : indices) {
      index.slot = static_cast<std::uint32_t>(secondary[index.table].size());
      secondary[index.table].push_back(index.positions);
    }
    for (std::size_t t = 0; t < types.size(); ++t)
      tables.emplace_back(static_cast<std::uint32_t>(types[t].size()), 0, std::move(secondary[t]));
    const auto view_count = view_atom_begin.size() - 1;
    for (std::size_t v = 0; v < view_count; ++v) {
      const auto width = static_cast<std::uint32_t>(view_key_begin[v + 1] - view_key_begin[v]);
      views.emplace_back(width, 1, std::vector<std::vector<std::uint32_t>>{});
      view_delta.emplace_back(width, 1, std::vector<std::vector<std::uint32_t>>{});
    }
    delta_ids.resize(view_count);
    touched.assign(view_count, 0);
    const auto head = static_cast<std::uint32_t>(query.head.size());
    answers = Table(head, 1, {});
    supports = Table(head, 1, {});
    assignment.assign(query.variables.size(), 0);
    bound.assign(query.variables.size(), 0);
    cursors.resize(atoms.size() + 1);
    // All relations start empty: a nonempty body has no witness, the empty
    // noncontradictory body has exactly one (the nullary answer).
    if (!query.contradiction && query.atoms.empty()) { Word empty[1]{}; answers.payload(answers.insert(empty))[0] = 1; }
  }

  // ------------------------------------------------------------------ plan
  bool fixed(std::size_t atom, std::size_t field, const std::vector<std::uint8_t>& is_bound) const {
    const auto& term = atoms[atom][field];
    if (term.kind == Term::constant) return true;
    return term.kind == Term::variable && is_bound[term.variable_id];
  }
  void bind_all(std::size_t atom, std::vector<std::uint8_t>& is_bound) const {
    for (const auto& term : atoms[atom]) if (term.kind == Term::variable) is_bound[term.variable_id] = 1;
  }
  std::size_t index_for(std::uint32_t table, const std::vector<std::uint32_t>& positions) {
    for (std::size_t i = 0; i < indices.size(); ++i)
      if (indices[i].table == table && indices[i].positions == positions) return i;
    indices.push_back({table, positions, 0});
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
        if (owner[term.variable_id] == no_index) owner[term.variable_id] = a;
        else parent[root(a)] = root(owner[term.variable_id]);
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
    for (int pass = 0; pass < 2; ++pass) {
      for (std::size_t a = 0; a < count_atoms; ++a) {
        if (!selected[a]) continue;
        bool has_head = false;
        for (const auto& term : atoms[a]) if (term.kind == Term::variable && head[term.variable_id]) has_head = true;
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
        if (term.kind != Term::variable || prefix_bound[term.variable_id]) continue;
        if (owner[term.variable_id] == no_index) owner[term.variable_id] = a;
        else parent[root(a)] = root(owner[term.variable_id]);
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
        for (const auto& term : atoms[a]) if (term.kind == Term::variable && prefix_bound[term.variable_id]) keyed[term.variable_id] = 1;
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
  bool match(std::size_t atom, const Word* row) {
    const auto& terms = atoms[atom];
    for (std::size_t field = 0; field < terms.size(); ++field) {
      const auto& term = terms[field];
      if (term.kind == Term::variable) {
        const auto v = term.variable_id;
        if (bound[v]) { if (assignment[v] != row[field]) return false; }
        else { assignment[v] = row[field]; bound[v] = 1; trail.push_back(v); }
      } else if (term.kind == Term::constant) {
        if (row[field] != term.value) return false;
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
    if (index == no_index) {
      cursor.id = 0;
      return;
    }
    const auto& spec = indices[index];
    key.clear();
    for (const auto field : spec.positions) {
      const auto& term = atoms[atom][field];
      key.push_back(term.kind == Term::constant ? term.value : assignment[term.variable_id]);
    }
    cursor.id = tables[spec.table].bucket(spec.slot, key.data());
  }
  const Word* next_candidate(std::size_t depth, std::size_t anchor, bool delta_rule, std::size_t atom, std::size_t index) {
    auto& cursor = cursors[depth];
    const auto table = atom_table[atom];
    const bool same = delta_rule && table == table_;
    const auto skip = (!insert_ && same && atom < anchor) ? stored_ : none;
    const auto& rows = tables[table];
    if (cursor.phase == 0) {
      if (index == no_index) {
        while (cursor.id < rows.ids()) {
          const auto id = cursor.id++;
          if (rows.used(id) && id != skip) return rows.key(id);
        }
      } else {
        const auto slot = indices[index].slot;
        while (cursor.id != none) {
          const auto id = cursor.id;
          cursor.id = rows.next(slot, id);
          if (id != skip) return rows.key(id);
        }
      }
      cursor.phase = 1;
    }
    if (cursor.phase == 1) {
      cursor.phase = 2;
      if (insert_ && same && atom > anchor) return row_;
    }
    return nullptr;
  }
  template<class Done>
  void walk(std::size_t anchor, bool delta_rule, const std::size_t* order, const std::size_t* steps,
      std::size_t start, std::size_t length, Done&& done) {
    if (start >= length) { done(); return; }
    const auto entry = trail.size();
    std::size_t depth = start;
    open(depth, order[depth], steps[depth]);
    for (;;) {
      const Word* candidate = next_candidate(depth, anchor, delta_rule, order[depth], steps[depth]);
      if (!candidate) {
        if (depth == start) break;
        --depth;
        continue;
      }
      restore(cursors[depth].mark);
      if (!match(order[depth], candidate)) continue;
      if (depth + 1 == length) done();
      else { ++depth; open(depth, order[depth], steps[depth]); }
    }
    restore(entry);
  }
  void view_key(std::size_t v) {
    key.clear();
    for (auto k = view_key_begin[v]; k < view_key_begin[v + 1]; ++k) key.push_back(assignment[view_keys[k]]);
  }
  bool present(std::size_t v, bool updated) {
    view_key(v);
    const auto found = views[v].find(key.data());
    std::uint64_t count = found == none ? 0 : static_cast<std::uint64_t>(views[v].payload(found)[0]);
    if (updated && touched[v]) {
      const auto delta = view_delta[v].find(key.data());
      if (delta != none) {
        const auto change = static_cast<std::uint64_t>(view_delta[v].payload(delta)[0]);
        count = insert_ ? count + change : count - change;
      }
    }
    return count > 0;
  }
  void support() {
    projected.clear();
    for (const auto& field : query.head) projected.push_back(assignment[field.variable.value]);
    const auto found = supports.find(projected.data());
    if (found != none) { ++supports.payload(found)[0]; return; }
    const auto id = supports.insert(projected.data());
    supports.payload(id)[0] = 1;
    support_ids.push_back(id);
  }
  void view_witness(std::size_t v) {
    view_key(v);
    auto& table = view_delta[v];
    const auto found = table.find(key.data());
    if (found != none) { ++table.payload(found)[0]; return; }
    const auto id = table.insert(key.data());
    table.payload(id)[0] = 1;
    delta_ids[v].push_back(id);
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
        walk(anchor, true, &view_order[base], &view_steps[base], 1, m, [&] { view_witness(v); });
      }
    }
    restore(0);
  }
  void propagate_flips() {
    const auto p = prefix_atoms.size();
    const auto view_count = views.size();
    std::vector<Word> entry;
    for (std::size_t v = 0; v < view_count; ++v) {
      for (const auto id : delta_ids[v]) {
        const Word* delta_key = view_delta[v].key(id);
        const auto delta = static_cast<std::uint64_t>(view_delta[v].payload(id)[0]);
        const auto found = views[v].find(delta_key);
        const std::uint64_t before = found == none ? 0 : static_cast<std::uint64_t>(views[v].payload(found)[0]);
        require(insert_ || before >= delta, "view count underflow");
        const auto after = insert_ ? before + delta : before - delta;
        if ((before == 0) == (after == 0)) continue;
        restore(0);
        entry.assign(delta_key, delta_key + view_delta[v].arity());
        std::size_t field = 0;
        for (auto k = view_key_begin[v]; k < view_key_begin[v + 1]; ++k, ++field) {
          const auto variable = view_keys[k];
          assignment[variable] = entry[field];
          bound[variable] = 1;
          trail.push_back(static_cast<std::uint32_t>(variable));
        }
        walk(0, false, key_order.data() + v * p, key_steps.data() + v * p, 0, p, [&] {
          for (std::size_t j = 0; j < view_count; ++j) if (j != v && !present(j, j < v)) return;
          support();
        });
        restore(0);
      }
    }
  }
  void propagate_prefix() {
    const auto p = prefix_atoms.size();
    const auto view_count = views.size();
    for (std::size_t i = 0; i < p; ++i) {
      const auto anchor = prefix_atoms[i];
      if (atom_table[anchor] != table_) continue;
      restore(0);
      if (!match(anchor, row_)) continue;
      walk(anchor, true, prefix_order.data() + i * p, prefix_steps.data() + i * p, 1, p, [&] {
        for (std::size_t j = 0; j < view_count; ++j) if (!present(j, true)) return;
        support();
      });
    }
    restore(0);
  }

  void apply(TableId table, SetOperation operation, const Word* row, FlatSink sink) {
    const auto t = static_cast<std::uint32_t>(table.value);
    auto& rows = tables.at(t);
    insert_ = operation == SetOperation::insert;
    const auto existing = rows.find(row);
    if (insert_ ? existing != none : existing == none) return;
    if (used[t] && !query.contradiction) {
      table_ = t;
      row_ = row;
      stored_ = existing;
      for (std::size_t v = 0; v < touched.size(); ++v) {
        touched[v] = 0;
        for (auto i = view_atom_begin[v]; i < view_atom_begin[v + 1]; ++i)
          if (atom_table[view_atoms[i]] == t) touched[v] = 1;
      }
      maintain_views();
      propagate_flips();
      propagate_prefix();
      const auto width = query.head.size();
      for (const auto id : support_ids) {
        const Word* answer = supports.key(id);
        const auto count = static_cast<std::uint64_t>(supports.payload(id)[0]);
        const auto found = answers.find(answer);
        if (insert_) {
          if (found != none) { answers.payload(found)[0] += static_cast<Word>(count); continue; }
          answers.payload(answers.insert(answer))[0] = static_cast<Word>(count);
          if (sink.row) sink.row(sink.context, SetOperation::insert, supports.key(id), width);
        } else {
          require(found != none && static_cast<std::uint64_t>(answers.payload(found)[0]) >= count, "support underflow");
          answers.payload(found)[0] -= static_cast<Word>(count);
          if (answers.payload(found)[0] == 0) {
            if (sink.row) sink.row(sink.context, SetOperation::erase, answers.key(found), width);
            answers.erase(found);
          }
        }
      }
      for (const auto id : support_ids) supports.erase(id);
      support_ids.clear();
      for (std::size_t v = 0; v < views.size(); ++v) {
        auto& view = views[v];
        for (const auto id : delta_ids[v]) {
          const Word* delta_key = view_delta[v].key(id);
          const auto delta = view_delta[v].payload(id)[0];
          const auto found = view.find(delta_key);
          if (insert_) {
            if (found != none) view.payload(found)[0] += delta;
            else view.payload(view.insert(delta_key))[0] = delta;
          } else {
            view.payload(found)[0] -= delta;
            if (view.payload(found)[0] == 0) view.erase(found);
          }
        }
        for (const auto id : delta_ids[v]) view_delta[v].erase(id);
        delta_ids[v].clear();
      }
    }
    if (insert_) rows.insert(row);
    else rows.erase(existing);
  }
};

std::string FlatCyclicRuntime::unsupported(const Catalog& catalog, const Query& query) {
  for (const auto& table : catalog.tables)
    for (const auto& column : table.columns)
      if (!Dictionary::supported(column.type)) return "column types other than int64, string and boolean";
  for (const auto& variable : query.variables)
    if (!Dictionary::supported(variable.type)) return "variable types other than int64, string and boolean";
  for (const auto& atom : query.atoms) {
    if (atom.table.value >= catalog.tables.size()) return "atom names a missing table";
    if (atom.terms.size() != catalog.tables[atom.table.value].columns.size()) return "atom arity differs from its table";
    for (const auto& term : atom.terms)
      if (const auto* value = std::get_if<Value>(&term);
          value && !std::holds_alternative<std::int64_t>(*value) && !std::holds_alternative<std::string>(*value) &&
          !std::holds_alternative<bool>(*value))
        return "constant types other than int64, string and boolean";
  }
  return {};
}
FlatCyclicRuntime::FlatCyclicRuntime(const Catalog& catalog, const Query& query)
    : impl_(std::make_unique<Impl>(catalog, query)) {}
FlatCyclicRuntime::~FlatCyclicRuntime() = default;
FlatCyclicRuntime::FlatCyclicRuntime(FlatCyclicRuntime&&) noexcept = default;
FlatCyclicRuntime& FlatCyclicRuntime::operator=(FlatCyclicRuntime&&) noexcept = default;
void FlatCyclicRuntime::encode(TableId table, const Row& row, std::int64_t* out) {
  require(row.size() == impl_->types.at(table.value).size(), "row arity differs from the table");
  for (std::size_t i = 0; i < row.size(); ++i) out[i] = impl_->dictionary.encode(row[i]);
}
std::size_t FlatCyclicRuntime::arity(TableId table) const { return impl_->types.at(table.value).size(); }
void FlatCyclicRuntime::apply(TableId table, SetOperation operation, const std::int64_t* row, FlatSink sink) {
  impl_->apply(table, operation, row, sink);
}
void FlatCyclicRuntime::snapshot(FlatSink sink) const {
  const auto& answers = impl_->answers;
  const auto width = impl_->query.head.size();
  if (!sink.row) return;
  for (std::uint32_t id = 0; id < answers.ids(); ++id)
    if (answers.used(id)) sink.row(sink.context, SetOperation::insert, answers.key(id), width);
}
std::size_t FlatCyclicRuntime::answers() const { return impl_->answers.size(); }
std::size_t FlatCyclicRuntime::result_arity() const { return impl_->head_types.size(); }
Value FlatCyclicRuntime::decode(std::size_t column, std::int64_t value) const {
  return impl_->dictionary.decode(impl_->head_types.at(column), value);
}

}  // namespace crown::runtime
