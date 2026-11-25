#include "crown/runtime/fallback.hpp"
#include "crown/api/error.hpp"
#include "crown/runtime/keyed_cyclic.hpp"
#include "constraint_validation.hpp"
#include "cq_recompute.hpp"
#include <algorithm>
#include <cstdlib>
#include <string_view>
#include <array>
#include <compare>
#include <limits>
#include <map>
#include <set>
#include <type_traits>
#include <unordered_map>

namespace crown::runtime::fallback {
namespace {
constexpr resource::MemoryAttribution memory{resource::MemoryOwnerKind::support_node, 0};
constexpr std::size_t no_index = std::numeric_limits<std::size_t>::max();
template<class T> using Vector = std::vector<T, resource::MemoryAllocator<T>>;
template<class T> auto allocator(const resource::MemoryAccount& account,
    resource::MemoryPurpose purpose = resource::MemoryPurpose::scratch) {
  return resource::MemoryAllocator<T>(account, purpose, memory);
}
TupleVector output(const resource::MemoryAccount& account) {
  return TupleVector(resource::OwnerAllocator<storage::Tuple>(account, resource::MemoryPurpose::output_buffer, memory));
}
void require(bool condition, const char* message) {
  if (!condition) throw Error("fallback_invariant", message);
}

// One balance covers a constructor's metadata/initial answer, or one update's
// candidate traversal, witness projection and endpoint output. Byte units
// conservatively admit string/decimal extents; they are not elapsed time.
struct Budget {
  Metrics& metrics;
  std::uint64_t limit;
  void take(std::uint64_t amount = 1) {
    if (amount > limit - metrics.work) throw Error("fallback_work_limit", "fallback work grant exhausted");
    metrics.work += amount;
  }
  void scalar(const storage::ScalarView& value) {
    take(); ++metrics.scalar_fields;
    std::uint64_t bytes = 0;
    if (const auto* text = std::get_if<std::string_view>(&value)) bytes = text->size();
    else if (const auto* decimal = std::get_if<storage::InlineDecimal>(&value)) bytes = decimal->parts().digits.size();
    take(bytes); metrics.scalar_bytes += bytes;
  }
  void payload(storage::RowView row) { for (const auto& value : row.cells()) scalar(value); }
};
struct Writing {
  bool& flag;
  explicit Writing(bool& value) noexcept : flag(value) { flag = true; }
  ~Writing() { flag = false; }
};

// Stateless lexicographic native order (the same scalar order as before), so
// persistent node containers carry no borrowed budget context.
struct StoredLess {
  using is_transparent = void;
  bool operator()(const storage::AccountedRow& a, const storage::AccountedRow& b) const noexcept { return a.view() < b.view(); }
  bool operator()(const storage::AccountedRow& a, storage::RowView b) const noexcept { return a.view() < b; }
  bool operator()(storage::RowView a, const storage::AccountedRow& b) const noexcept { return a < b.view(); }
};
// Hashed lookup for index buckets and persistent view counts.
struct RowHash {
  using is_transparent = void;
  std::size_t operator()(const storage::AccountedRow& row) const noexcept { return static_cast<std::size_t>(row.view().hash()); }
  std::size_t operator()(storage::RowView row) const noexcept { return static_cast<std::size_t>(row.hash()); }
};
struct RowEqual {
  using is_transparent = void;
  bool operator()(const storage::AccountedRow& a, const storage::AccountedRow& b) const noexcept { return a.view() == b.view(); }
  bool operator()(const storage::AccountedRow& a, storage::RowView b) const noexcept { return a.view() == b; }
  bool operator()(storage::RowView a, const storage::AccountedRow& b) const noexcept { return a == b.view(); }
};
using StoredRows = std::set<storage::AccountedRow, StoredLess, resource::MemoryAllocator<storage::AccountedRow>>;
using Members = std::set<const storage::AccountedRow*, std::less<const storage::AccountedRow*>,
    resource::MemoryAllocator<const storage::AccountedRow*>>;
using Buckets = std::unordered_map<storage::AccountedRow, Members, RowHash, RowEqual,
    resource::MemoryAllocator<std::pair<const storage::AccountedRow, Members>>>;
using Counts = std::unordered_map<storage::AccountedRow, std::uint64_t, RowHash, RowEqual,
    resource::MemoryAllocator<std::pair<const storage::AccountedRow, std::uint64_t>>>;
struct Answer { std::uint64_t support = 0; storage::Tuple tuple; };
using Answers = std::map<storage::AccountedRow, Answer, StoredLess,
    resource::MemoryAllocator<std::pair<const storage::AccountedRow, Answer>>>;
using Witnesses = std::map<storage::AccountedRow, std::uint64_t, StoredLess,
    resource::MemoryAllocator<std::pair<const storage::AccountedRow, std::uint64_t>>>;

// A detached node owns its allocation; publishing it later only relinks.
template<class Map, class... Args>
typename Map::node_type prepare_node(const Map& owner, Args&&... args) {
  Map temporary(owner.key_comp(), owner.get_allocator());
  const auto [position, inserted] = temporary.emplace(std::forward<Args>(args)...);
  require(inserted, "fallback node preparation collided");
  return temporary.extract(position);
}
template<class Map, class... Args>
typename Map::node_type prepare_hashed(const Map& owner, Args&&... args) {
  Map temporary(1, owner.hash_function(), owner.key_eq(), owner.get_allocator());
  const auto [position, inserted] = temporary.emplace(std::forward<Args>(args)...);
  require(inserted, "fallback node preparation collided");
  return temporary.extract(position);
}
// Map insertion of a detached node relinks only; hashed callers reserve first.
template<class Map> auto publish_node(Map& owner, typename Map::node_type node) noexcept {
  auto result = owner.insert(std::move(node));
  if (!result.inserted) std::terminate();
  return result.position;
}

// Rows of one original physical table, grouped by the values at the fields a
// delta plan binds before visiting that occurrence. Members point at the
// stable stored rows of the same table.
struct Index {
  TableId table;
  Vector<std::size_t> positions;
  Buckets buckets;
  Index(const resource::MemoryAccount& account, TableId id, Vector<std::size_t> fields)
      : table(id), positions(std::move(fields)),
        buckets(0, RowHash{}, RowEqual{}, allocator<std::pair<const storage::AccountedRow, Members>>(account, resource::MemoryPurpose::secondary_node)) {}
};
} // namespace

struct Binding::Data {
  resource::MemoryAccount account;
  CompiledProgram sources;
  Profile profile;
  cq_recompute::FrozenQuery frozen;
  Data(const CompiledProgram& source, const planner::fallback::Plan& plan, Budget& budget)
      : account(source.account()), sources(source), profile(plan.profile()),
        frozen(source, plan.query(), cq_recompute::output_id(source, "fallback_overflow"),
            "fallback-original-head-v1", budget, "fallback_overflow") {}
};
const Binding::Data& Binding::data() const {
  if (!data_) throw Error("fallback_state", "empty fallback binding");
  return *data_;
}
const program::Query& Binding::query() const & { return data().frozen.query; }
const Profile& Binding::profile() const & { return data().profile; }
const CompiledProgram& Binding::sources() const & { return data().sources; }
const storage::AccountedLayout& Binding::result_layout() const & { return data().frozen.layout; }
const resource::MemoryAccount& Binding::account() const & { return data().account; }

// Incremental exact-set maintenance by presence propagation.
//
// A fixed prefix P (a minimal connected set of occurrences binding every head
// variable) is enumerated explicitly. The other occurrences split into
// residual components that share no variable outside P; each component is a
// persistent view V(key) counting its completions per value of its variables
// that also occur in P. An answer's support is
//   S(ans) = sum over P-assignments p projecting to ans of
//            prod over views j of [V_j(key_j(p)) > 0],
// so the answer exists exactly when S(ans) > 0. An update first maintains the
// views that use its table (anchored enumeration of their new or removed
// completions). Keys whose view count crosses zero then adjust the supports of
// the P-assignments that carry them, using already-updated presence for
// earlier views and committed presence for later ones; finally P-assignments
// that use the changed row adjust their supports with updated presence. A
// count change that keeps a view positive costs nothing outside that view.
// Self-joins count each completion once: when occurrence k is bound to the
// changed row, earlier occurrences of that table exclude it and later ones
// include it. All fallible work precedes the source commit; publication only
// relinks prepared nodes and updates counters.
struct Runtime::Data {
  resource::MemoryAccount account;
  PhysicalRuntime sources;
  Binding binding;
  Limits limits;
  Vector<std::uint64_t> cardinalities;
  Vector<std::uint8_t> used;
  Vector<StoredRows> tables;
  Vector<Index> indices;
  // P in ascending occurrence order; prefix_local maps an occurrence to its
  // position in P (no_index outside P). The plan anchored at P-position i is
  // prefix_order/prefix_steps[i*P .. i*P+P), position 0 being the anchor.
  Vector<std::size_t> prefix_atoms, prefix_local, prefix_order, prefix_steps;
  // View v: occurrences view_atoms[view_atom_begin[v] .. view_atom_begin[v+1])
  // ascending; key variables view_keys[view_key_begin[v] .. +1) ascending;
  // maintenance plan anchored at its local occurrence i is view_order/
  // view_steps[view_plan_begin[v] + i*m .. +m), m its occurrence count; the
  // key plan enumerating all of P with v's keys bound is key_order/
  // key_steps[v*P .. v*P+P).
  Vector<std::size_t> view_atom_begin, view_atoms, view_key_begin, view_keys,
      view_plan_begin, view_order, view_steps, key_order, key_steps;
  Vector<Counts> views;
  Answers answers;  // Answer::support is S(ans).
  // Keyed core (docs/keyed_core.md): the same support-count algorithm over
  // fixed-width keyed indexes. When present it owns the rows, views and
  // answers; the source-only physical owner still validates, enforces the
  // catalog and sequences every update.
  std::unique_ptr<keyed::CyclicEngine> keyed;
  std::optional<storage::TuplePool> pool;
  // Unconstrained catalogs: the keyed engine also coordinates the sources
  // (validation, sequencing, source image) instead of the physical owner.
  bool keyed_sources = false;
  bool answer_changes = true;  // Options::answer_changes
  std::uint64_t keyed_sequence = 0;
  std::vector<storage::ScalarView> cells;
  bool busy = false;
  class Change;
  Data(PhysicalRuntime source, const planner::fallback::Plan& plan, Limits selected, Budget& budget)
      : account(source.plan().account()), sources(std::move(source)),
        binding(resource::make_accounted_shared<Binding::Data>(memory, account,
            resource::MemoryPurpose::immutable_metadata, sources.plan(), plan, budget)), limits(selected),
        cardinalities(allocator<std::uint64_t>(account, resource::MemoryPurpose::support_metadata)),
        used(allocator<std::uint8_t>(account, resource::MemoryPurpose::immutable_metadata)),
        tables(allocator<StoredRows>(account, resource::MemoryPurpose::table_state)),
        indices(allocator<Index>(account, resource::MemoryPurpose::immutable_metadata)),
        prefix_atoms(metadata()), prefix_local(metadata()), prefix_order(metadata()), prefix_steps(metadata()),
        view_atom_begin(metadata()), view_atoms(metadata()), view_key_begin(metadata()), view_keys(metadata()),
        view_plan_begin(metadata()), view_order(metadata()), view_steps(metadata()), key_order(metadata()), key_steps(metadata()),
        views(allocator<Counts>(account, resource::MemoryPurpose::support_metadata)),
        answers(StoredLess{}, allocator<std::pair<const storage::AccountedRow, Answer>>(account, resource::MemoryPurpose::table_state)) {
    const auto table_count = sources.plan().source_catalog().tables.size();
    budget.take(table_count); cardinalities.assign(table_count, 0);
    budget.take(table_count); used.assign(table_count, 0);
    for (const auto& atom : binding.query().atoms) { budget.take(); used[atom.table.value] = 1; }
    budget.take(table_count); tables.reserve(table_count);
    for (std::size_t i = 0; i < table_count; ++i)
      tables.emplace_back(StoredLess{}, allocator<storage::AccountedRow>(account, resource::MemoryPurpose::table_state));
    build_plan(budget);
  }
  [[nodiscard]] Vector<std::size_t> metadata() const {
    return Vector<std::size_t>(allocator<std::size_t>(account, resource::MemoryPurpose::immutable_metadata));
  }
  void readable() const {
    if (busy || !sources.ready()) throw Error("fallback_busy", "fallback source/result publication is active");
  }
  [[nodiscard]] std::size_t prefix_size() const noexcept { return prefix_atoms.size(); }
  [[nodiscard]] static bool fixed(const program::Term& term, const Vector<std::uint8_t>& bound) noexcept {
    if (std::holds_alternative<storage::ScalarView>(term)) return true;
    const auto* variable = std::get_if<VariableId>(&term);
    return variable && bound[variable->value];
  }
  static void bind(const program::Atom& atom, Vector<std::uint8_t>& bound) noexcept {
    for (const auto& term : atom.terms) if (const auto* variable = std::get_if<VariableId>(&term)) bound[variable->value] = 1;
  }
  std::size_t index_for(TableId table, const Vector<std::size_t>& positions, Budget& budget) {
    for (std::size_t i = 0; i < indices.size(); ++i) {
      budget.take();
      if (indices[i].table == table && std::equal(indices[i].positions.begin(), indices[i].positions.end(),
              positions.begin(), positions.end())) return i;
    }
    budget.take(positions.size() + 1);
    Vector<std::size_t> fields(positions.begin(), positions.end(), allocator<std::size_t>(account, resource::MemoryPurpose::immutable_metadata));
    indices.emplace_back(account, table, std::move(fields));
    return indices.size() - 1;
  }
  // Appends the untaken pool occurrences in greedy connected order: most
  // fields fixed by constants or earlier bindings, then fewest new variables,
  // then lowest occurrence. Each position records the index on its fixed
  // fields, or no_index for a scan.
  void extend_order(const Vector<std::size_t>& pool, Vector<std::uint8_t>& taken, Vector<std::uint8_t>& bound,
      Vector<std::size_t>& order_out, Vector<std::size_t>& steps_out, Budget& budget) {
    const auto& query = binding.query();
    Vector<std::size_t> positions(allocator<std::size_t>(account));
    for (;;) {
      std::size_t best = no_index, best_fixed = 0, best_new = 0;
      for (std::size_t j = 0; j < pool.size(); ++j) {
        if (taken[j]) continue;
        const auto& atom = query.atoms[pool[j]];
        budget.take(atom.terms.size() + 1);
        std::size_t fixed_fields = 0, new_variables = 0;
        for (const auto& term : atom.terms) {
          if (fixed(term, bound)) ++fixed_fields;
          else if (std::holds_alternative<VariableId>(term)) ++new_variables;
        }
        if (best == no_index || fixed_fields > best_fixed || (fixed_fields == best_fixed && new_variables < best_new)) {
          best = j; best_fixed = fixed_fields; best_new = new_variables;
        }
      }
      if (best == no_index) return;
      const auto& atom = query.atoms[pool[best]];
      positions.clear();
      for (std::size_t field = 0; field < atom.terms.size(); ++field) if (fixed(atom.terms[field], bound)) positions.push_back(field);
      order_out.push_back(pool[best]);
      steps_out.push_back(positions.empty() ? no_index : index_for(atom.table, positions, budget));
      taken[best] = 1; bind(atom, bound);
    }
  }
  // Connected components of the selected occurrences (shared variables).
  [[nodiscard]] std::size_t component_count(const Vector<std::uint8_t>& selected, Budget& budget) const {
    const auto& query = binding.query(); const auto atoms = query.atoms.size();
    budget.take(atoms + query.variables.size());
    Vector<std::size_t> parent(atoms, 0, allocator<std::size_t>(account)), owner(query.variables.size(), no_index, allocator<std::size_t>(account));
    for (std::size_t a = 0; a < atoms; ++a) parent[a] = a;
    const auto root = [&](std::size_t x) { while (parent[x] != x) x = parent[x] = parent[parent[x]]; return x; };
    for (std::size_t a = 0; a < atoms; ++a) {
      if (!selected[a]) continue;
      budget.take(query.atoms[a].terms.size());
      for (const auto& term : query.atoms[a].terms) {
        const auto* variable = std::get_if<VariableId>(&term);
        if (!variable) continue;
        if (owner[variable->value] == no_index) owner[variable->value] = a;
        else parent[root(a)] = root(owner[variable->value]);
      }
    }
    std::size_t count = 0;
    for (std::size_t a = 0; a < atoms; ++a) if (selected[a] && root(a) == a) ++count;
    return count;
  }
  void build_plan(Budget& budget) {
    const auto& query = binding.query(); const auto atoms = query.atoms.size(), variables = query.variables.size();
    // P: drop occurrences while the head stays covered and P does not split
    // into more connected pieces; occurrences without head variables first.
    Vector<std::uint8_t> selected(atoms, 1, allocator<std::uint8_t>(account)), head(variables, 0, allocator<std::uint8_t>(account));
    for (const auto& field : query.head) head[field.variable.value] = 1;
    const auto covers = [&] {
      Vector<std::uint8_t> seen(variables, 0, allocator<std::uint8_t>(account));
      for (std::size_t a = 0; a < atoms; ++a) if (selected[a]) bind(query.atoms[a], seen);
      for (std::size_t v = 0; v < variables; ++v) if (head[v] && !seen[v]) return false;
      return true;
    };
    for (int pass = 0; pass < 2; ++pass) {
      for (std::size_t a = 0; a < atoms; ++a) {
        if (!selected[a]) continue;
        bool has_head = false;
        for (const auto& term : query.atoms[a].terms)
          if (const auto* variable = std::get_if<VariableId>(&term); variable && head[variable->value]) has_head = true;
        if (pass == 0 && has_head) continue;
        budget.take(atoms);
        const auto before = component_count(selected, budget);
        selected[a] = 0;
        if (!covers() || component_count(selected, budget) > before) selected[a] = 1;
      }
    }
    budget.take(atoms); prefix_local.assign(atoms, no_index);
    for (std::size_t a = 0; a < atoms; ++a) if (selected[a]) { prefix_local[a] = prefix_atoms.size(); prefix_atoms.push_back(a); }
    const auto p = prefix_atoms.size();
    Vector<std::uint8_t> prefix_bound(variables, 0, allocator<std::uint8_t>(account));
    for (const auto a : prefix_atoms) bind(query.atoms[a], prefix_bound);
    // Residual components joined by variables outside P.
    budget.take(atoms + variables);
    Vector<std::size_t> parent(atoms, 0, allocator<std::size_t>(account)), owner(variables, no_index, allocator<std::size_t>(account));
    for (std::size_t a = 0; a < atoms; ++a) parent[a] = a;
    const auto root = [&](std::size_t x) { while (parent[x] != x) x = parent[x] = parent[parent[x]]; return x; };
    for (std::size_t a = 0; a < atoms; ++a) {
      if (selected[a]) continue;
      for (const auto& term : query.atoms[a].terms) {
        const auto* variable = std::get_if<VariableId>(&term);
        if (!variable || prefix_bound[variable->value]) continue;
        if (owner[variable->value] == no_index) owner[variable->value] = a;
        else parent[root(a)] = root(owner[variable->value]);
      }
    }
    Vector<std::uint8_t> key(variables, 0, allocator<std::uint8_t>(account));
    view_atom_begin.push_back(0); view_key_begin.push_back(0);
    for (std::size_t first = 0; first < atoms; ++first) {
      if (selected[first] || root(first) != first) continue;
      budget.take(atoms + variables);
      std::fill(key.begin(), key.end(), std::uint8_t{0});
      for (std::size_t a = 0; a < atoms; ++a) {
        if (selected[a] || root(a) != first) continue;
        view_atoms.push_back(a);
        for (const auto& term : query.atoms[a].terms)
          if (const auto* variable = std::get_if<VariableId>(&term); variable && prefix_bound[variable->value]) key[variable->value] = 1;
      }
      for (std::size_t v = 0; v < variables; ++v) if (key[v]) view_keys.push_back(v);
      view_atom_begin.push_back(view_atoms.size()); view_key_begin.push_back(view_keys.size());
    }
    const auto view_count = view_atom_begin.size() - 1;
    Vector<std::uint8_t> bound(allocator<std::uint8_t>(account)), taken(allocator<std::uint8_t>(account));
    // Anchored plans over P.
    for (std::size_t i = 0; i < p; ++i) {
      budget.take(variables + p);
      bound.assign(variables, 0); taken.assign(p, 0); taken[i] = 1;
      prefix_order.push_back(prefix_atoms[i]); prefix_steps.push_back(no_index); bind(query.atoms[prefix_atoms[i]], bound);
      extend_order(prefix_atoms, taken, bound, prefix_order, prefix_steps, budget);
    }
    // Per view: key plan over P, and anchored maintenance plans over the view.
    budget.take(view_count + 1); views.reserve(view_count);
    Vector<std::size_t> pool(allocator<std::size_t>(account));
    for (std::size_t v = 0; v < view_count; ++v) {
      views.emplace_back(0, RowHash{}, RowEqual{}, allocator<std::pair<const storage::AccountedRow, std::uint64_t>>(account, resource::MemoryPurpose::support_metadata));
      budget.take(variables + p);
      bound.assign(variables, 0); taken.assign(p, 0);
      for (auto k = view_key_begin[v]; k < view_key_begin[v + 1]; ++k) bound[view_keys[k]] = 1;
      extend_order(prefix_atoms, taken, bound, key_order, key_steps, budget);
      const auto first = view_atom_begin[v], m = view_atom_begin[v + 1] - first;
      pool.assign(view_atoms.begin() + static_cast<std::ptrdiff_t>(first), view_atoms.begin() + static_cast<std::ptrdiff_t>(first + m));
      view_plan_begin.push_back(view_order.size());
      for (std::size_t i = 0; i < m; ++i) {
        budget.take(variables + m);
        bound.assign(variables, 0); taken.assign(m, 0); taken[i] = 1;
        view_order.push_back(pool[i]); view_steps.push_back(no_index); bind(query.atoms[pool[i]], bound);
        extend_order(pool, taken, bound, view_order, view_steps, budget);
      }
    }
    view_plan_begin.push_back(view_order.size());
  }
};

// Private evaluation of one physical update, prepared before the source
// commit. Destroying an unpublished Change releases only scratch and detached
// nodes; publish() is nonallocating.
class Runtime::Data::Change {
 public:
  Change(Runtime::Data& data, Budget& budget, SetOperation operation, TableId table, storage::RowView row)
      : d_(data), budget_(budget), insert_(operation == SetOperation::insert), table_(table),
        row_(storage::AccountedRow::copy_of(data.account, row, memory)) {
    if (!insert_) {
      stored_ = d_.tables[table_.value].find(row_.view());
      require(stored_ != d_.tables[table_.value].end(), "fallback stored row missing for deletion");
    }
    const auto view_total = d_.views.size();
    budget_.take(view_total + 1); touched_.assign(view_total, 0);
    for (std::size_t v = 0; v < view_total; ++v)
      for (auto i = d_.view_atom_begin[v]; i < d_.view_atom_begin[v + 1]; ++i)
        if (query().atoms[d_.view_atoms[i]].table == table_) touched_[v] = 1;
  }
  void prepare(TupleVector& added, TupleVector& removed) {
    budget_.metrics.recomputed = true;
    const auto atoms = query().atoms.size(), variables = query().variables.size();
    budget_.take(variables + 3 * atoms);
    assignment_.assign(variables, std::nullopt); trail_.reserve(variables);
    projected_.reserve(query().head.size());
    next_.assign(atoms, 0); marks_.assign(atoms, 0); lists_.reserve(atoms);
    while (lists_.size() < atoms) lists_.emplace_back(allocator<const storage::AccountedRow*>(d_.account));
    maintain_views();
    propagate_flips();
    propagate_prefix();
    const auto& layout = d_.binding.result_layout();
    std::size_t fresh_count = 0;
    for (auto& [answer, count] : supports_) {
      budget_.take();
      const auto found = d_.answers.find(answer.view());
      if (insert_) {
        if (found != d_.answers.end()) {
          if (found->second.support > std::numeric_limits<std::uint64_t>::max() - count)
            throw Error("fallback_overflow", "fallback support count overflow");
          updates_.emplace_back(found, found->second.support + count);
          continue;
        }
        if (d_.answers.size() + fresh_count >= d_.limits.rows) throw Error("fallback_row_limit", "fallback distinct-result row limit exceeded");
        ++fresh_count; budget_.payload(answer.view());
        auto tuple = storage::Tuple::from_accounted(layout.tuple(answer.view(), memory));
        added.push_back(tuple);
        fresh_.push_back(prepare_node(d_.answers, answer.clone(d_.account), Answer{count, std::move(tuple)}));
      } else {
        require(found != d_.answers.end() && found->second.support >= count, "fallback support count underflow");
        if (found->second.support == count) { removed.push_back(found->second.tuple); retired_.push_back(found); }
        else updates_.emplace_back(found, found->second.support - count);
      }
    }
    prepare_views();
    prepare_storage();
    retired_nodes_.reserve(retired_.size());  // publish() relinks without allocating.
    budget_.metrics.added = added.size(); budget_.metrics.removed = removed.size();
    budget_.metrics.outputs = d_.answers.size() + fresh_.size() - retired_.size();
  }
  void publish() noexcept {
    auto& rows = d_.tables[table_.value];
    if (insert_) {
      publish_node(rows, std::move(row_node_));
      for (auto& change : members_) {
        auto& index = d_.indices[change.index];
        if (change.bucket) publish_node(index.buckets, std::move(change.bucket));
        else publish_node(change.existing->second, std::move(change.member));
      }
    } else {
      for (auto& change : members_) {
        auto& index = d_.indices[change.index];
        if (change.existing->second.size() == 1) change.bucket = index.buckets.extract(change.existing);
        else change.member = change.existing->second.extract(change.position);
      }
      row_node_ = rows.extract(stored_);
    }
    for (auto& [answer, count] : updates_) answer->second.support = count;
    for (auto& node : fresh_) publish_node(d_.answers, std::move(node));
    for (auto answer : retired_) retired_nodes_.push_back(d_.answers.extract(answer));
    for (auto& change : view_changes_) {
      auto& view = d_.views[change.view];
      if (change.fresh) publish_node(view, std::move(change.fresh));
      else if (change.next) change.existing->second = change.next;
      else change.fresh = view.extract(change.existing);
    }
  }

 private:
  struct ViewChange {
    std::size_t view;
    Counts::iterator existing;
    std::uint64_t next;
    Counts::node_type fresh;  // Prepared insertion, or the extracted node of a retired key.
  };
  struct MemberChange {
    std::size_t index;
    Buckets::iterator existing;
    Members::iterator position;
    Buckets::node_type bucket;
    Members::node_type member;
  };
  [[nodiscard]] const program::Query& query() const noexcept { return d_.binding.query(); }
  // Binds or checks every term of one occurrence against one physical row.
  bool match(const program::Atom& atom, storage::RowView row) {
    for (std::size_t field = 0; field < atom.terms.size(); ++field) {
      budget_.take(); ++budget_.metrics.term_tests; const auto& term = atom.terms[field];
      if (std::holds_alternative<IgnoredColumn>(term)) continue;
      const auto& value = row[field];
      if (const auto* variable = std::get_if<VariableId>(&term)) {
        auto& bound = assignment_[variable->value];
        if (bound) { ++budget_.metrics.equality_tests; if (*bound != value) return false; }
        else { bound = value; trail_.push_back(*variable); }
      } else {
        ++budget_.metrics.equality_tests;
        if (std::get<storage::ScalarView>(term) != value) return false;
      }
    }
    return true;
  }
  void restore(std::size_t mark) {
    while (trail_.size() > mark) { assignment_[trail_.back().value].reset(); trail_.pop_back(); }
  }
  // Candidate rows of occurrence j. With the delta rule (anchor = occurrence
  // bound to the changed row), earlier occurrences of the changed table skip
  // a deleted row and later ones also see an inserted row; without it the
  // committed rows are used as they are.
  void candidates(std::size_t anchor, bool delta_rule, std::size_t j, std::size_t index, Vector<const storage::AccountedRow*>& out) {
    out.clear();
    const auto& atom = query().atoms[j];
    const bool same = delta_rule && atom.table == table_;
    const auto* skip = (!insert_ && same && j < anchor) ? &*stored_ : nullptr;
    const auto add = [&](const storage::AccountedRow* row) { if (row != skip) { budget_.take(); ++budget_.metrics.row_visits; out.push_back(row); } };
    if (index == no_index) {
      for (const auto& row : d_.tables[atom.table.value]) add(&row);
    } else {
      key_.clear();
      for (const auto field : d_.indices[index].positions) {
        const auto& term = atom.terms[field];
        if (const auto* variable = std::get_if<VariableId>(&term)) key_.push_back(*assignment_[variable->value]);
        else key_.push_back(std::get<storage::ScalarView>(term));
      }
      const auto& buckets = d_.indices[index].buckets;
      const auto found = buckets.find(storage::RowView::borrow(key_));
      if (found != buckets.end()) for (const auto* row : found->second) add(row);
    }
    if (insert_ && same && j > anchor) add(&row_);
  }
  void open_at(std::size_t slot, std::size_t anchor, bool delta_rule, std::size_t atom, std::size_t index) {
    marks_[slot] = trail_.size(); next_[slot] = 0;
    candidates(anchor, delta_rule, atom, index, lists_[slot]);
  }
  // Enumerates plan positions [start, length) under the current bindings and
  // calls done() for every complete match; bindings are restored afterwards.
  template<class Done> void walk(std::size_t anchor, bool delta_rule, const std::size_t* order, const std::size_t* steps,
      std::size_t start, std::size_t length, Done&& done) {
    if (start >= length) { done(); return; }
    const auto entry = trail_.size();
    std::size_t depth = start;
    open_at(depth, anchor, delta_rule, order[depth], steps[depth]);
    for (;;) {
      if (next_[depth] == lists_[depth].size()) {
        if (depth == start) break;
        --depth; continue;
      }
      restore(marks_[depth]);
      const auto* candidate = lists_[depth][next_[depth]++];
      if (!match(query().atoms[order[depth]], candidate->view())) continue;
      if (depth + 1 == length) done();
      else { ++depth; open_at(depth, anchor, delta_rule, order[depth], steps[depth]); }
    }
    restore(entry);
  }
  // key_ = [v, key values of view v under the current bindings].
  void view_key(std::size_t v) {
    key_.clear(); key_.push_back(static_cast<std::int64_t>(v));
    for (auto k = d_.view_key_begin[v]; k < d_.view_key_begin[v + 1]; ++k) key_.push_back(*assignment_[d_.view_keys[k]]);
  }
  // Completion count of view v at the current key: committed, or after this
  // update when `updated`.
  bool present(std::size_t v, bool updated) {
    budget_.take();
    view_key(v);
    const auto full = storage::RowView::borrow(key_);
    const auto& view = d_.views[v];
    const auto found = view.find(storage::RowView::borrow(full.cells().subspan(1)));
    auto count = found == view.end() ? 0 : found->second;
    if (updated && touched_[v]) {
      if (const auto delta = view_delta_.find(full); delta != view_delta_.end()) count = insert_ ? count + delta->second : count - delta->second;
    }
    return count > 0;
  }
  void support(std::uint64_t count) {
    budget_.take(); ++budget_.metrics.assignments; ++budget_.metrics.projected;
    projected_.clear();
    for (const auto& field : query().head) projected_.push_back(*assignment_[field.variable.value]);
    const auto view = storage::RowView::borrow(projected_);
    const auto found = supports_.find(view);
    if (found != supports_.end()) {
      if (found->second > std::numeric_limits<std::uint64_t>::max() - count) throw Error("fallback_overflow", "fallback support count overflow");
      found->second += count; ++budget_.metrics.duplicates; return;
    }
    budget_.payload(view);
    supports_.emplace(storage::AccountedRow::copy_of(d_.account, view, memory), count);
  }
  // View deltas: completions of each touched view that use the changed row,
  // keyed by [view, key values...].
  void maintain_views() {
    const auto row = row_.view();
    for (std::size_t v = 0; v < touched_.size(); ++v) {
      if (!touched_[v]) continue;
      const auto first = d_.view_atom_begin[v], m = d_.view_atom_begin[v + 1] - first;
      for (std::size_t i = 0; i < m; ++i) {
        const auto anchor = d_.view_atoms[first + i];
        if (query().atoms[anchor].table != table_) continue;
        budget_.take(); restore(0);
        if (!match(query().atoms[anchor], row)) continue;
        const auto base = d_.view_plan_begin[v] + i * m;
        walk(anchor, true, &d_.view_order[base], &d_.view_steps[base], 1, m, [&] { view_witness(v); });
      }
    }
    restore(0);
  }
  void view_witness(std::size_t v) {
    budget_.take();
    view_key(v);
    const auto view = storage::RowView::borrow(key_);
    if (const auto found = view_delta_.find(view); found != view_delta_.end()) {
      if (found->second == std::numeric_limits<std::uint64_t>::max()) throw Error("fallback_overflow", "fallback view count overflow");
      ++found->second; return;
    }
    view_delta_.emplace(storage::AccountedRow::copy_of(d_.account, view, memory), 1);
  }
  // Keys whose view count crosses zero change the supports of the committed
  // P-assignments carrying them (views in ascending order: earlier views use
  // updated presence, later views committed presence).
  void propagate_flips() {
    const auto p = d_.prefix_size(); const auto view_total = d_.views.size();
    for (const auto& [entry, delta] : view_delta_) {
      budget_.take();
      const auto cells = entry.view().cells();
      const auto v = static_cast<std::size_t>(std::get<std::int64_t>(cells[0]));
      const auto key = storage::RowView::borrow(cells.subspan(1));
      const auto& view = d_.views[v];
      const auto found = view.find(key);
      const auto before = found == view.end() ? 0 : found->second;
      require(insert_ || before >= delta, "fallback view count underflow");
      const auto after = insert_ ? before + delta : before - delta;
      if ((before == 0) == (after == 0)) continue;
      restore(0);
      std::size_t field = 1;
      for (auto k = d_.view_key_begin[v]; k < d_.view_key_begin[v + 1]; ++k, ++field) {
        assignment_[d_.view_keys[k]] = cells[field]; trail_.push_back(VariableId{d_.view_keys[k]});
      }
      walk(0, false, d_.key_order.data() + v * p, d_.key_steps.data() + v * p, 0, p, [&] {
        for (std::size_t j = 0; j < view_total; ++j) if (j != v && !present(j, j < v)) return;
        support(1);
      });
      restore(0);
    }
  }
  // P-assignments that use the changed row, with updated view presence.
  void propagate_prefix() {
    const auto p = d_.prefix_size(); const auto view_total = d_.views.size(); const auto row = row_.view();
    for (std::size_t i = 0; i < p; ++i) {
      const auto anchor = d_.prefix_atoms[i];
      if (query().atoms[anchor].table != table_) continue;
      budget_.take(); restore(0);
      if (!match(query().atoms[anchor], row)) continue;
      walk(anchor, true, d_.prefix_order.data() + i * p, d_.prefix_steps.data() + i * p, 1, p, [&] {
        for (std::size_t j = 0; j < view_total; ++j) if (!present(j, true)) return;
        support(1);
      });
    }
    restore(0);
  }
  void prepare_views() {
    // Rehash before taking iterators: publication then inserts without
    // allocating and every stored iterator stays valid.
    fresh_keys_.assign(d_.views.size(), 0);
    if (insert_) for (const auto& [entry, count] : view_delta_) {
      budget_.take(); static_cast<void>(count);
      const auto cells = entry.view().cells();
      const auto v = static_cast<std::size_t>(std::get<std::int64_t>(cells[0]));
      if (!d_.views[v].contains(storage::RowView::borrow(cells.subspan(1)))) ++fresh_keys_[v];
    }
    for (std::size_t v = 0; v < fresh_keys_.size(); ++v) if (fresh_keys_[v]) d_.views[v].reserve(d_.views[v].size() + fresh_keys_[v]);
    view_changes_.reserve(view_delta_.size());
    for (const auto& [entry, count] : view_delta_) {
      budget_.take();
      const auto cells = entry.view().cells();
      const auto v = static_cast<std::size_t>(std::get<std::int64_t>(cells[0]));
      const auto key = storage::RowView::borrow(cells.subspan(1));
      auto& view = d_.views[v];
      const auto found = view.find(key);
      if (insert_) {
        if (found != view.end()) {
          if (found->second > std::numeric_limits<std::uint64_t>::max() - count) throw Error("fallback_overflow", "fallback view count overflow");
          view_changes_.push_back({v, found, found->second + count, {}});
        } else view_changes_.push_back({v, view.end(), count,
            prepare_hashed(view, storage::AccountedRow::copy_of(d_.account, key, memory), count)});
      } else {
        require(found != view.end() && found->second >= count, "fallback view count underflow");
        view_changes_.push_back({v, found, found->second - count, {}});
      }
    }
  }
  void prepare_storage() {
    const auto row = row_.view();
    if (insert_) {
      row_node_ = prepare_node(d_.tables[table_.value], std::move(row_));
      const auto* stored = &row_node_.value();
      for (std::size_t i = 0; i < d_.indices.size(); ++i) {
        auto& index = d_.indices[i];
        if (index.table != table_) continue;
        budget_.take(index.positions.size() + 1);
        auto key = storage::AccountedRow::project(d_.account, stored->view(), project_fields(index), memory);
        MemberChange change{i, index.buckets.find(key.view()), {}, {}, {}};
        if (change.existing != index.buckets.end()) change.member = prepare_node(change.existing->second, stored);
        else {
          Members members(std::less<const storage::AccountedRow*>{}, index.buckets.get_allocator());
          members.insert(stored);
          change.bucket = prepare_hashed(index.buckets, std::move(key), std::move(members));
          index.buckets.reserve(index.buckets.size() + 1);  // Publication inserts without rehashing.
        }
        members_.push_back(std::move(change));
      }
    } else {
      const auto* stored = &*stored_;
      for (std::size_t i = 0; i < d_.indices.size(); ++i) {
        auto& index = d_.indices[i];
        if (index.table != table_) continue;
        budget_.take(index.positions.size() + 1);
        key_.clear();
        for (const auto field : index.positions) key_.push_back(row[field]);
        MemberChange change{i, index.buckets.find(storage::RowView::borrow(key_)), {}, {}, {}};
        require(change.existing != index.buckets.end(), "fallback index bucket missing");
        change.position = change.existing->second.find(stored);
        require(change.position != change.existing->second.end(), "fallback index member missing");
        members_.push_back(std::move(change));
      }
    }
  }
  std::span<const FieldId> project_fields(const Index& index) {
    fields_.clear();
    for (const auto position : index.positions) fields_.push_back(FieldId{position});
    return {fields_.data(), fields_.size()};
  }

  Runtime::Data& d_;
  Budget& budget_;
  bool insert_;
  TableId table_;
  storage::AccountedRow row_;
  StoredRows::iterator stored_{};
  Witnesses supports_{StoredLess{}, allocator<std::pair<const storage::AccountedRow, std::uint64_t>>(d_.account)};
  Witnesses view_delta_{StoredLess{}, allocator<std::pair<const storage::AccountedRow, std::uint64_t>>(d_.account)};
  Vector<std::uint8_t> touched_{allocator<std::uint8_t>(d_.account)};
  Vector<std::size_t> next_{allocator<std::size_t>(d_.account)}, marks_{allocator<std::size_t>(d_.account)};
  Vector<Vector<const storage::AccountedRow*>> lists_{allocator<Vector<const storage::AccountedRow*>>(d_.account)};
  Vector<std::pair<Answers::iterator, std::uint64_t>> updates_{allocator<std::pair<Answers::iterator, std::uint64_t>>(d_.account)};
  Vector<Answers::node_type> fresh_{allocator<Answers::node_type>(d_.account)};
  Vector<Answers::iterator> retired_{allocator<Answers::iterator>(d_.account)};
  Vector<MemberChange> members_{allocator<MemberChange>(d_.account)};
  Vector<ViewChange> view_changes_{allocator<ViewChange>(d_.account)};
  StoredRows::node_type row_node_;
  Vector<Answers::node_type> retired_nodes_{allocator<Answers::node_type>(d_.account)};
  Vector<std::optional<storage::ScalarView>> assignment_{allocator<std::optional<storage::ScalarView>>(d_.account)};
  Vector<VariableId> trail_{allocator<VariableId>(d_.account)};
  Vector<storage::ScalarView> projected_{allocator<storage::ScalarView>(d_.account)};
  Vector<storage::ScalarView> key_{allocator<storage::ScalarView>(d_.account)};
  Vector<FieldId> fields_{allocator<FieldId>(d_.account)};
  Vector<std::size_t> fresh_keys_{allocator<std::size_t>(d_.account)};
};

Runtime::Runtime(const planner::fallback::Plan& plan, Options options) {
  Metrics metrics; Budget budget{metrics, options.recompute.work}; budget.take();
  PhysicalRuntime sources(plan.source_only(), options.sources); const auto account = sources.plan().account();
  data_ = resource::make_accounted_unique<Data>(memory, account, resource::MemoryPurpose::support_metadata,
      std::move(sources), plan, options.recompute, budget);
  auto& d = data(); Writing writing(d.busy); budget.take();
  const char* forced = std::getenv("CROWN_FALLBACK_ENGINE");
  if (!(forced && std::string_view(forced) == "reference") &&
      keyed::CyclicEngine::unsupported(plan.originalcatalog(), plan.query()).empty()) {
    keyed::CyclicOptions engine;
    engine.gc = options.gc;
    engine.memory_limit_bytes = static_cast<std::size_t>(options.sources.support.memory_limit_bytes);
    engine.answer_limit = options.recompute.rows;
    engine.work_limit = options.recompute.work;
    d.keyed = std::make_unique<keyed::CyclicEngine>(plan.originalcatalog(), plan.query(), engine);
    d.answer_changes = options.answer_changes;
    d.pool.emplace(&d.account);
    d.keyed_sources = true;
    for (const auto& table : plan.originalcatalog().tables)
      for (const auto& constraint : table.constraints)
        if (std::visit([](const auto& value) { return value.status == ConstraintStatus::enforced; }, constraint)) d.keyed_sources = false;
    d.keyed_sequence = d.sources.sequence();
    if (!d.binding.query().contradiction && d.binding.query().atoms.empty() && !d.limits.rows)
      throw Error("fallback_row_limit", "fallback distinct-result row limit exceeded");
    return;
  }
  // All original physical relations start empty. A nonempty body has no
  // witness, including nullary atoms; the empty noncontradictory body has one.
  if (!d.binding.query().contradiction && d.binding.query().atoms.empty()) {
    if (!d.limits.rows) throw Error("fallback_row_limit", "fallback distinct-result row limit exceeded");
    budget.take();
    auto key = storage::AccountedRow::copy_of(d.account, storage::RowView{}, memory);
    auto tuple = storage::Tuple::from_accounted(d.binding.result_layout().tuple(storage::RowView{}, memory));
    d.answers.emplace(std::move(key), Answer{1, std::move(tuple)});
  }
}
Runtime::~Runtime() = default;
Runtime::Runtime(Runtime&&) noexcept = default;
Runtime& Runtime::operator=(Runtime&&) noexcept = default;
Runtime::Data& Runtime::data() const {
  if (!data_) throw Error("fallback_state", "moved-from fallback runtime");
  return *data_;
}
const Binding& Runtime::binding() const & { return data().binding; }
const resource::MemoryAccount& Runtime::account() const & { return data().account; }
bool Runtime::ready() const { const auto& d = data(); return !d.busy && d.sources.ready(); }
std::uint64_t Runtime::sequence() const {
  const auto& d = data(); d.readable(); return d.keyed_sources ? d.keyed_sequence : d.sources.sequence();
}
std::string_view Runtime::engine() const { return data().keyed ? "keyed_v1" : "reference_v1"; }
std::string_view Runtime::algorithm() const { return data().keyed ? data().keyed->algorithm() : std::string_view("reference"); }
bool Runtime::has_answer() const {
  const auto& d = data(); d.readable(); return d.keyed ? d.keyed->has_answer() : !d.answers.empty();
}

namespace {
// Keyed answer changes become owning result tuples (pooled payloads under the
// query account), in the reference engine's ascending value order.
struct KeyedAnswers final : keyed::AnswerSink {
  storage::TuplePool& pool;
  const storage::TupleLayout& layout;
  TupleVector& added;
  TupleVector& removed;
  KeyedAnswers(storage::TuplePool& tuples, const storage::TupleLayout& result, TupleVector& in, TupleVector& out)
      : pool(tuples), layout(result), added(in), removed(out) {}
  void answer(SetOperation operation, storage::RowView head) override {
    (operation == SetOperation::insert ? added : removed).push_back(pool.make(layout, head));
  }
};
// Ascending value order. Each tuple's row view is read once (no payload
// ownership copy per comparison); the permutation is then applied in place
// with nonthrowing moves.
void sort_rows(TupleVector& rows) {
  const auto count = rows.size();
  if (count < 2) return;
  // The leading int64 cells are copied into the item as order-preserving
  // unsigned words (int64 is the first variant alternative, so it sorts
  // before any other type), so most comparisons stay inside the item array.
  struct Item { std::uint64_t prefix[2]; std::uint8_t kind[2]; storage::RowView row; std::size_t index; };
  std::vector<Item> items;
  items.reserve(count);
  for (std::size_t i = 0; i < count; ++i) {
    const auto view = rows[i].values().native_view();
    require(view.has_value(), "fallback keyed result is not a native tuple");
    Item item{{0, 0}, {2, 2}, *view, i};
    for (std::size_t c = 0; c < 2 && c < view->size(); ++c) {
      const auto* value = std::get_if<std::int64_t>(&(*view)[c]);
      if (!value) { item.kind[c] = 1; break; }
      item.kind[c] = 0;
      item.prefix[c] = static_cast<std::uint64_t>(*value) ^ (std::uint64_t{1} << 63);
    }
    items.push_back(item);
  }
  // kind: 0 = int64 prefix word, 1 = another type (compare the rows), 2 = no cell.
  std::sort(items.begin(), items.end(), [](const Item& a, const Item& b) {
    for (std::size_t c = 0; c < 2; ++c) {
      if (a.kind[c] != 0 || b.kind[c] != 0) {
        if (a.kind[c] == 2 || b.kind[c] == 2) return a.kind[c] == 2 && b.kind[c] != 2;
        return a.row < b.row;
      }
      if (a.prefix[c] != b.prefix[c]) return a.prefix[c] < b.prefix[c];
    }
    return a.row < b.row;
  });
  // Position j receives rows[items[j].index]; follow each cycle once.
  for (std::size_t start = 0; start < count; ++start) {
    if (items[start].index == start || items[start].index == count) continue;
    auto held = std::move(rows[start]);
    auto at = start;
    while (items[at].index != start) {
      const auto from = items[at].index;
      rows[at] = std::move(rows[from]);
      items[at].index = count;
      at = from;
    }
    rows[at] = std::move(held);
    items[at].index = count;
  }
}
}  // namespace

namespace {
PhysicalEpoch keyed_input(const resource::MemoryAccount& account, const PhysicalSetUpdate& update, bool changed, bool answer) {
  const auto allocator = [&]<class T>(std::type_identity<T>) {
    return resource::OwnerAllocator<T>(account, resource::MemoryPurpose::output_buffer, {resource::MemoryOwnerKind::output, 0});
  };
  PhysicalPreview preview{update.sequence, update.table, update.operation, changed, {}, {},
      decltype(PhysicalPreview::derivations)(allocator(std::type_identity<DerivationChange>{}))};
  SupportEpoch support{update.sequence, changed, answer, {},
      decltype(SupportEpoch::transitions)(allocator(std::type_identity<MembershipTransition>{})), nullptr};
  return PhysicalEpoch{std::move(preview), std::move(support)};
}
}  // namespace

Epoch Runtime::apply(const PhysicalSetUpdate& update) {
  auto& d = data(); d.readable(); Writing writing(d.busy);
  Metrics metrics; Budget budget{metrics, d.limits.work}; budget.take();
  if (d.keyed_sources) {
    // The physical owner's validation, in its order and with its errors.
    if (d.keyed_sequence == std::numeric_limits<std::uint64_t>::max()) throw Error("sequence_overflow", "physical update sequence exhausted");
    if (update.sequence != d.keyed_sequence + 1) throw Error("invalid_sequence", "physical update sequence must be contiguous from one");
    if (update.operation != SetOperation::insert && update.operation != SetOperation::erase)
      throw Error("invalid_physical_update", "unknown physical set operation");
    if (update.table.value >= d.cardinalities.size()) throw Error("invalid_physical_update", "source table is outside the catalog");
    detail::validate_native_row(d.sources.plan().source_catalog(), update.table, storage::TupleValuesView::borrow(update.values));
    d.cells.clear();
    for (const auto& value : update.values) d.cells.push_back(storage::borrow_scalar(value));
    const auto row = storage::RowView::borrow(d.cells);
    const bool insert = update.operation == SetOperation::insert;
    const bool changed = d.keyed->contains(update.table, row) != insert;
    auto count = d.cardinalities[update.table.value];
    if (changed) {
      if (insert) {
        if (count == UINT64_MAX) throw Error("fallback_overflow", "fallback table cardinality overflow");
        ++count;
      } else --count;
    }
    auto added = output(d.account), removed = output(d.account);
    if (changed && d.used[update.table.value] && !d.binding.query().contradiction) {
      std::uint64_t total = 0;
      for (std::size_t i = 0; i < d.cardinalities.size(); ++i) {
        const auto rows = i == update.table.value ? count : d.cardinalities[i];
        if (rows > d.limits.source_rows - total) throw Error("source_image_row_limit", "physical source image row grant exhausted");
        total += rows;
      }
      metrics.source_rows = total;
    }
    bool prepared = false;
    std::uint64_t work_added = 0, work_removed = 0;
    if (changed) {
      const auto layout = d.binding.result_layout().descriptor();
      KeyedAnswers sink(*d.pool, layout, added, removed);
      keyed::CyclicMetrics work;
      prepared = d.keyed->prepare(update.table, update.operation, row, d.answer_changes ? &sink : nullptr, &work);
      work_added = work.added; work_removed = work.removed;
      require(prepared, "fallback keyed source change was not staged");
      metrics.work += work.work; metrics.row_visits = work.row_visits; metrics.term_tests = work.term_tests;
      metrics.assignments = work.assignments; metrics.added = work.added; metrics.removed = work.removed;
      metrics.recomputed = d.used[update.table.value] && !d.binding.query().contradiction;
    }
    std::optional<PhysicalEpoch> input;
    try {
      sort_rows(added); sort_rows(removed);
      input.emplace(keyed_input(d.account, update, changed,
          d.keyed->answers() + (d.answer_changes ? added.size() : work_added) != (d.answer_changes ? removed.size() : work_removed)));
    } catch (...) { d.keyed->discard(); throw; }
    if (prepared) d.keyed->publish();
    d.keyed_sequence = update.sequence; d.cardinalities[update.table.value] = count;
    metrics.outputs = d.keyed->answers();
    return {std::move(*input), d.binding, std::move(added), std::move(removed), metrics};
  }
  auto source = d.sources.prepare(update);
  const auto& preview = source.preview();
  const bool changed = preview.physical_changed;
  auto count = d.cardinalities[update.table.value];
  if (changed) {
    if (update.operation == SetOperation::insert) {
      if (count == UINT64_MAX) throw Error("fallback_overflow", "fallback table cardinality overflow");
      ++count;
    } else { require(count != 0, "fallback table cardinality underflow"); --count; }
  }
  auto added = output(d.account), removed = output(d.account);
  if (d.keyed) {
    bool prepared = false;
    if (changed) {
      if (d.used[update.table.value] && !d.binding.query().contradiction) {
        std::uint64_t total = 0;
        for (std::size_t i = 0; i < d.cardinalities.size(); ++i) {
          const auto rows = i == update.table.value ? count : d.cardinalities[i];
          if (rows > d.limits.source_rows - total) throw Error("source_image_row_limit", "physical source image row grant exhausted");
          total += rows;
        }
        metrics.source_rows = total;
      }
      require(preview.source.has_value(), "fallback physical change lost its source row");
      const auto layout = d.binding.result_layout().descriptor();
      KeyedAnswers sink(*d.pool, layout, added, removed);
      keyed::CyclicMetrics work;
      prepared = d.keyed->prepare(update.table, update.operation, preview.source->tuple().values(), &sink, &work);
      require(prepared, "fallback keyed rows disagree with the physical source owner");
      metrics.work += work.work; metrics.row_visits = work.row_visits; metrics.term_tests = work.term_tests;
      metrics.assignments = work.assignments; metrics.added = work.added; metrics.removed = work.removed;
      metrics.recomputed = d.used[update.table.value] && !d.binding.query().contradiction;
      try { sort_rows(added); sort_rows(removed); } catch (...) { d.keyed->discard(); throw; }
    }
    // Every fallible step is complete: source commit and keyed publication
    // do not fail.
    auto input = source.commit(); d.cardinalities[update.table.value] = count;
    if (prepared) d.keyed->publish();
    metrics.outputs = d.keyed->answers();
    return {std::move(input), d.binding, std::move(added), std::move(removed), metrics};
  }
  std::optional<Data::Change> change;
  // A source-only program has no derivation routes: physical change plus the
  // ORIGINAL query's table-use mask is the trigger, never native_changed.
  if (changed && d.used[update.table.value] && !d.binding.query().contradiction) {
    // The retained rows of all physical tables after this update stay within
    // the source-row grant, as the former private source image did.
    std::uint64_t total = 0;
    for (std::size_t i = 0; i < d.cardinalities.size(); ++i) {
      budget.take(); const auto rows = i == update.table.value ? count : d.cardinalities[i];
      if (rows > d.limits.source_rows - total) throw Error("source_image_row_limit", "physical source image row grant exhausted");
      total += rows;
    }
    metrics.source_rows = total;
    require(preview.source.has_value(), "fallback physical change lost its source row");
    change.emplace(d, budget, update.operation, update.table, preview.source->tuple().values());
    change->prepare(added, removed);
  } else metrics.outputs = d.answers.size();
  // Every fallible result/delta step is complete. Valid source commit, scalar
  // count publication and node relinking are nonallocating; the guard also
  // spans retired-node teardown.
  auto input = source.commit(); d.cardinalities[update.table.value] = count;
  if (change) change->publish();
  return {std::move(input), d.binding, std::move(added), std::move(removed), metrics};
}
Snapshot Runtime::snapshot(Limits limits) const {
  auto& d = data(); d.readable(); Writing writing(d.busy);
  Metrics metrics; Budget budget{metrics, limits.work}; budget.take();
  if (d.keyed) {
    const auto count = d.keyed->answers();
    if (count > limits.rows) throw Error("fallback_row_limit", "fallback snapshot row limit exceeded");
    auto rows = output(d.account); budget.take(count); rows.reserve(count);
    TupleVector unused = output(d.account);
    storage::TuplePool pool(&d.account);
    const auto layout = d.binding.result_layout().descriptor();
    KeyedAnswers sink(pool, layout, rows, unused);
    d.keyed->snapshot(sink);
    sort_rows(rows);
    metrics.outputs = rows.size();
    return {d.keyed_sources ? d.keyed_sequence : d.sources.sequence(), d.binding, std::move(rows), metrics};
  }
  if (d.answers.size() > limits.rows) throw Error("fallback_row_limit", "fallback snapshot row limit exceeded");
  auto rows = output(d.account); budget.take(d.answers.size()); rows.reserve(d.answers.size());
  for (const auto& [key, answer] : d.answers) { static_cast<void>(key); budget.take(); rows.push_back(answer.tuple); }
  metrics.outputs = rows.size(); return {d.sources.sequence(), d.binding, std::move(rows), metrics};
}
std::uint64_t Runtime::visit(const std::function<void(const storage::Tuple&)>& visitor, Limits limits) const {
  auto& d = data(); d.readable(); Writing writing(d.busy);
  if (d.keyed) {
    const auto count = d.keyed->answers();
    if (count > limits.rows) throw Error("fallback_row_limit", "fallback snapshot row limit exceeded");
    storage::TuplePool pool(&d.account);
    const auto layout = d.binding.result_layout().descriptor();
    struct Sink final : keyed::AnswerSink {
      storage::TuplePool& pool;
      const storage::TupleLayout& layout;
      const std::function<void(const storage::Tuple&)>& visitor;
      std::uint64_t rows = 0;
      Sink(storage::TuplePool& tuples, const storage::TupleLayout& result, const std::function<void(const storage::Tuple&)>& visit)
          : pool(tuples), layout(result), visitor(visit) {}
      void answer(SetOperation, storage::RowView head) override {
        const auto tuple = pool.make(layout, head);
        ++rows; visitor(tuple);
      }
    } sink(pool, layout, visitor);
    d.keyed->snapshot(sink);
    return sink.rows;
  }
  if (d.answers.size() > limits.rows) throw Error("fallback_row_limit", "fallback snapshot row limit exceeded");
  for (const auto& [key, answer] : d.answers) { static_cast<void>(key); visitor(answer.tuple); }
  return d.answers.size();
}
Explain Runtime::explain() const {
  auto& d = data(); d.readable(); Writing writing(d.busy);
  Cardinalities tables(resource::OwnerAllocator<std::uint64_t>(d.account, resource::MemoryPurpose::capture, memory));
  tables.assign(d.cardinalities.begin(), d.cardinalities.end());
  std::optional<std::uint64_t> product = 1, prefix = 0;
  for (const auto& atom : d.binding.query().atoms) {
    const auto count = d.cardinalities[atom.table.value];
    if (!count) product = 0; // A later zero makes the full product exactly zero even after overflow.
    else if (product) {
      if (*product > UINT64_MAX / count) product.reset(); else *product *= count;
    }
    if (prefix) {
      if (!product || *product > UINT64_MAX - *prefix) prefix.reset(); else *prefix += *product;
    }
  }
  return {d.binding.profile(), std::move(tables), product, prefix,
      static_cast<std::uint64_t>(d.keyed ? d.keyed->answers() : d.answers.size()), d.account.statistics()};
}
Database Runtime::source_snapshot() const {
  auto& d = data(); d.readable(); Writing writing(d.busy);
  if (d.keyed_sources) return d.keyed->sources();
  return d.sources.snapshot().physical;
}
static_assert(std::is_nothrow_move_constructible_v<Epoch>);
static_assert(std::is_nothrow_move_constructible_v<Snapshot>);
} // namespace crown::runtime::fallback
