#include "crown/runtime/compact.hpp"

#include "crown/api/error.hpp"
#include "crown/storage/tuple_values.hpp"
#include <algorithm>
#include <array>
#include <bit>
#include <cstdint>
#include <cstring>
#include <limits>
#include <map>
#include <utility>
#include <vector>

// Layout of the kernel (see include/crown/runtime/compact.hpp for the contract
// and docs/handoff-performance.md for measurements and the reasons behind it).
//
// Every value is one 64-bit word: int64 and bool are stored directly, every
// other scalar is a dictionary id. A tuple is therefore `arity` words, and
// equality and hashing never look at types.
//
// Source rows.  One slab + hash index per base table. A row is
//                 [values | meta | state of every direct node fed by the table].
// Records.      A node whose only input keeps every source column without a
//               filter is *direct*: its record is the source row itself, so
//               the node has no slab and no index. Any other native node keeps
//               [tuple | meta(derivations) | state] rows behind a hash index;
//               a generalized node keeps its candidates in a slab only.
//               Record state is [child mask | (entry, position) per child slot
//               | (parent entry, position)].
// Separators.   A hash table keyed by the separator, shared by the tree edges
//               whose separators range over the same source columns (a group).
//               A row is [key | one section per member edge]; a section holds
//               the child's support count and up to three arrays in the shared
//               list pool:
//                 rev   every parent record with this key (flipped when the
//                       child's support appears or disappears);
//                 down  the child's visible members with this key;
//                 up    the parent's visible members with this key.
//               When the parent's visible tuple is its whole scope, `up` is not
//               a separate array: `rev` keeps the surviving records in a
//               prefix. Array elements are [member | onward entry][payload]:
//               the payload is the member's visible values outside the
//               separator, so enumeration reads rows from contiguous memory.
// Visible.      A connex node whose visible tuple is its whole scope uses its
//               surviving records as visible members. Any other connex node
//               keeps [visible tuple | count | state] rows behind a hash index.
//
// Every member stores its position in each array it belongs to, so removal is
// a swap with the last element. Storage is charged to one MemoryAccount.
//
// The update path is written for memory latency first: one update touches few
// distinct cache lines, and the batched entry point starts the loads of later
// updates early (see `lookahead`).
namespace crown::runtime::compact {
namespace {
using U32 = std::uint32_t;
constexpr U32 nil = std::numeric_limits<U32>::max();
constexpr std::size_t max_fields = 64;    // Scope/separator/source arity and children per node.
constexpr std::size_t max_result = 256;   // Result arity.
constexpr std::size_t max_depth = 64;     // Connex nodes in one enumeration.
constexpr Word low_half = 0xffffffffULL;

[[noreturn, gnu::cold, gnu::noinline]] void fail(const char* message) { throw Error("compact_runtime_contract", message); }
[[gnu::always_inline]] inline void require(bool value, const char* message) {
  if (!value) [[unlikely]] fail(message);
}
[[nodiscard]] constexpr U32 low(Word word) noexcept { return static_cast<U32>(word & low_half); }
[[nodiscard]] constexpr U32 high(Word word) noexcept { return static_cast<U32>(word >> 32); }
[[nodiscard]] constexpr Word pack(U32 lower, U32 upper) noexcept { return Word{lower} | (Word{upper} << 32); }
[[nodiscard]] U32 narrow(std::size_t value) {
  require(value < nil, "index exceeds the compact 32-bit domain");
  return static_cast<U32>(value);
}

[[nodiscard]] inline Word hash_words(const Word* words, std::size_t count) noexcept {
  Word hash = 0x9e3779b97f4a7c15ULL ^ (static_cast<Word>(count) * 0xff51afd7ed558ccdULL);
  for (std::size_t i = 0; i < count; ++i) {
    hash ^= words[i];
    hash *= 0xff51afd7ed558ccdULL;
    hash ^= hash >> 32;
  }
  hash *= 0xc4ceb9fe1a85ec53ULL;
  hash ^= hash >> 29;
  return hash;
}
[[nodiscard]] inline bool equal_words(const Word* left, const Word* right, std::size_t count) noexcept {
  for (std::size_t i = 0; i < count; ++i) if (left[i] != right[i]) return false;
  return true;
}

// Growable word array charged to the kernel account. Elements are trivially
// copyable words, so growth is one allocation and one memcpy.
class Words {
 public:
  [[nodiscard]] Word* data() noexcept { return data_; }
  [[nodiscard]] const Word* data() const noexcept { return data_; }
  [[nodiscard]] std::size_t capacity() const noexcept { return capacity_; }
  void reserve(const resource::MemoryAccount& account, std::size_t wanted, resource::MemoryPurpose purpose, bool zero) {
    if (wanted <= capacity_) return;
    auto next = std::max<std::size_t>({wanted, capacity_ * 2, 64});
    require(next <= std::numeric_limits<std::size_t>::max() / sizeof(Word), "compact storage size overflow");
    auto block = account.allocate(next * sizeof(Word), alignof(Word), purpose);
    auto* target = static_cast<Word*>(block.data());
    if (capacity_) std::memcpy(target, data(), capacity_ * sizeof(Word));
    if (zero) std::memset(target + capacity_, 0, (next - capacity_) * sizeof(Word));
    replace(std::move(block), next);
  }
  void replace(resource::MemoryBlock block, std::size_t capacity) noexcept {
    block_ = std::move(block);
    data_ = static_cast<Word*>(block_.data());
    capacity_ = capacity;
  }
 private:
  resource::MemoryBlock block_;
  Word* data_ = nullptr;   // Cached: MemoryBlock::data() is an out-of-line call.
  std::size_t capacity_ = 0;
};

// Fixed-stride rows with an intrusive free list. A released row keeps its
// next-free index in the upper half of word `free_link`, whose lower half is
// zero; owners keep a non-zero lower half there while the row is live.
struct Slab {
  Words words;
  std::size_t stride = 1, free_link = 0;
  U32 high_water = 0, free_head = nil, live = 0;
  resource::MemoryPurpose purpose = resource::MemoryPurpose::tuple_values;
  void configure(std::size_t row_words, std::size_t link_word, resource::MemoryPurpose use) {
    stride = std::max<std::size_t>(row_words, 1); free_link = link_word; purpose = use;
    require(free_link < stride, "compact slab free link lies outside its row");
  }
  [[nodiscard]] Word* at(U32 index) noexcept { return words.data() + static_cast<std::size_t>(index) * stride; }
  [[nodiscard]] const Word* at(U32 index) const noexcept { return words.data() + static_cast<std::size_t>(index) * stride; }
  [[nodiscard]] U32 allocate(const resource::MemoryAccount& account) {
    U32 index;
    if (free_head != nil) {
      index = free_head;
      free_head = high(at(index)[free_link]);
    } else {
      require(high_water < nil - 1, "compact slab exhausted its 32-bit index domain");
      words.reserve(account, (static_cast<std::size_t>(high_water) + 1) * stride, purpose, false);
      index = high_water++;
    }
    ++live;
    return index;
  }
  void release(U32 index) noexcept {
    at(index)[free_link] = pack(0, free_head);
    free_head = index;
    --live;
  }
};

// Open-addressing directory: slot = (hash tag << 32) | (row index + 1).
// Linear probing with backward-shift deletion, so there are no tombstones and
// lookups stay short under insert/delete churn.
struct Index {
  Words slots;
  std::size_t capacity = 0, used = 0;
  [[nodiscard]] static U32 tag(Word hash) noexcept { return high(hash); }
  template<class Equal>
  [[nodiscard]] U32 find(Word hash, Equal&& equal) const noexcept {
    if (!capacity) return nil;
    const auto mask = capacity - 1;
    const U32 wanted = tag(hash);
    const Word* table = slots.data();
    for (auto i = static_cast<std::size_t>(wanted) & mask;; i = (i + 1) & mask) {
      const Word slot = table[i];
      if (!slot) return nil;
      if (high(slot) == wanted) {
        const U32 index = low(slot) - 1;
        if (equal(index)) return index;
      }
    }
  }
  // Lookahead helpers for batched updates: touch the home slot, or guess the
  // row from the first matching tag without comparing keys.
  void prefetch(Word hash) const noexcept {
    if (capacity) __builtin_prefetch(slots.data() + (static_cast<std::size_t>(tag(hash)) & (capacity - 1)), 1, 3);
  }
  [[nodiscard]] U32 peek(Word hash) const noexcept {
    if (!capacity) return nil;
    const auto mask = capacity - 1;
    const U32 wanted = tag(hash);
    const auto home = static_cast<std::size_t>(wanted) & mask;
    const Word first = slots.data()[home], second = slots.data()[(home + 1) & mask];
    // An empty slot is zero, so its "row" is already nil.
    U32 guess = high(second) == wanted ? low(second) - 1 : nil;
    guess = high(first) == wanted ? low(first) - 1 : guess;
    return guess;
  }
  void insert(const resource::MemoryAccount& account, Word hash, U32 index) {
    if ((used + 1) * 4 > capacity * 3) grow(account);
    place(slots.data(), capacity, pack(index + 1, tag(hash)));
    ++used;
  }
  void erase(Word hash, U32 index) noexcept {
    const auto mask = capacity - 1;
    Word* table = slots.data();
    auto hole = static_cast<std::size_t>(tag(hash)) & mask;
    while (low(table[hole]) != index + 1) hole = (hole + 1) & mask;
    for (auto next = (hole + 1) & mask;; next = (next + 1) & mask) {
      const Word slot = table[next];
      if (!slot) break;
      const auto home = static_cast<std::size_t>(high(slot)) & mask;
      // Move the entry back unless its home lies cyclically in (hole, next].
      const bool stays = hole <= next ? (home > hole && home <= next) : (home > hole || home <= next);
      if (!stays) { table[hole] = slot; hole = next; }
    }
    table[hole] = 0;
    --used;
  }
 private:
  static void place(Word* table, std::size_t size, Word slot) noexcept {
    const auto mask = size - 1;
    auto i = static_cast<std::size_t>(high(slot)) & mask;
    while (table[i]) i = (i + 1) & mask;
    table[i] = slot;
  }
  void grow(const resource::MemoryAccount& account) {
    const auto next = capacity ? capacity * 2 : 16;
    require(next <= (std::size_t{1} << 32), "compact directory exceeds its 32-bit tag domain");
    auto block = account.allocate(next * sizeof(Word), alignof(Word), resource::MemoryPurpose::directory);
    auto* table = static_cast<Word*>(block.data());
    std::memset(table, 0, next * sizeof(Word));
    const Word* old = slots.data();
    for (std::size_t i = 0; i < capacity; ++i) if (old[i]) place(table, next, old[i]);
    slots.replace(std::move(block), next);
    capacity = next;
  }
};

// Storage for the per-key arrays: power-of-two blocks of words addressed by a
// 32-bit word offset, with one free list per size class. A free block keeps
// the next free offset in its first word.
struct Pool {
  static constexpr unsigned classes = 32;
  Words words;
  std::size_t high_water = 0;
  std::array<U32, classes> free_head;
  Pool() { free_head.fill(nil); }
  [[nodiscard]] Word* at(U32 offset) noexcept { return words.data() + offset; }
  [[nodiscard]] const Word* at(U32 offset) const noexcept { return words.data() + offset; }
  [[nodiscard]] U32 allocate(const resource::MemoryAccount& account, unsigned size_class) {
    require(size_class < classes, "compact list exceeds the pool's size classes");
    if (free_head[size_class] != nil) {
      const U32 offset = free_head[size_class];
      free_head[size_class] = low(words.data()[offset]);
      return offset;
    }
    const auto size = std::size_t{1} << size_class;
    require(high_water + size < nil, "compact list pool exhausted its 32-bit offset domain");
    words.reserve(account, high_water + size, resource::MemoryPurpose::secondary_node, false);
    const auto offset = static_cast<U32>(high_water);
    high_water += size;
    return offset;
  }
  void release(U32 offset, unsigned size_class) noexcept {
    words.data()[offset] = free_head[size_class];
    free_head[size_class] = offset;
  }
};

using Fields = std::vector<U32>;
inline void project(const Word* source, const Fields& fields, Word* target) noexcept {
  for (std::size_t i = 0; i < fields.size(); ++i) target[i] = source[fields[i]];
}
Fields fields_of(std::span<const FieldId> source) {
  Fields result;
  for (const auto field : source) result.push_back(narrow(field.value));
  require(result.size() <= max_fields, "projection is wider than the compact kernel supports");
  return result;
}
[[nodiscard]] Fields compose(const Fields& outer, const Fields& inner) {
  Fields result;
  for (const auto field : outer) { require(field < inner.size(), "projection names a field outside its tuple"); result.push_back(inner[field]); }
  return result;
}
[[nodiscard]] Fields complement(std::size_t arity, const Fields& removed) {
  Fields result;
  for (U32 field = 0; field < arity; ++field)
    if (std::find(removed.begin(), removed.end(), field) == removed.end()) result.push_back(field);
  return result;
}
[[nodiscard]] unsigned first_class(std::size_t stride) noexcept {
  return static_cast<unsigned>(std::bit_width(std::bit_ceil(stride * 2) - 1));  // Room for two elements.
}

// One array kind of a separator entry: head word [offset | length] plus a size
// class byte inside the entry's count word.
struct List {
  bool present = false;
  std::size_t word = 0, stride = 1;
  unsigned shift = 0, first = 0;
};
struct Bind { U32 from = 0, column = 0; };
// One enumeration step of a plan anchored at some connex node: reach `node`
// from the already bound step `from` across tree edge `edge`.
struct Step {
  U32 node = 0, from = 0, edge = nil;
  bool up = false;            // true: `node` is the parent of `from`'s node.
  bool inline_entry = false;  // The entry id is the upper half of `from`'s element.
  bool prefix = false;        // The members are the surviving prefix of a rev array.
  U32 entry_word = 0;         // Otherwise it is the lower half of this word of `from`'s member row.
  U32 list_word = 0, count_word = 0;
  std::size_t stride = 1;
  U32 warm = nil;             // A later step whose entry id rides in this step's elements.
  std::vector<Bind> bind;     // Element word -> result column.
};
struct NodeState {
  NodeKind kind = NodeKind::native;
  std::size_t arity = 0, children = 0;
  bool connex = false, direct = false, identity = false;
  U32 parent_edge = nil;
  std::vector<U32> child_edges;
  std::vector<std::size_t> scope_variables, visible_variables;
  Fields separator_raw, visible_raw;   // Scope -> own separator / visible tuple.
  // Records. `store` is this node's own slab or the source slab of a direct node.
  Slab own;
  Slab* store = nullptr;
  Index record_index;                  // Non-direct native nodes only.
  Fields position;                     // Scope field -> word of a store row.
  std::size_t meta = 0, w_mask = 0, w_child = 0, w_parent = 0;
  Word full_mask = 0;
  Fields separator, visible_fields;    // Store row -> own separator / visible tuple.
  // Visible members (connex nodes). `members` is `store` for an identity node.
  std::size_t visible_arity = 0;
  Slab visible;                        // [visible tuple | count | parent word | word per connex child]
  Index visible_index;
  Slab* members = nullptr;
  Fields member_position;              // Visible field -> word of a member row.
  std::size_t v_meta = 0, v_parent = 0;
  Fields v_child;                      // Per connex child: word holding (entry, position).
  Fields visible_separator_raw;        // Visible -> own separator.
  std::vector<U32> connex_children;
  std::vector<Fields> visible_child_raw;  // Visible -> separator of each connex child.
  std::vector<Step> anchored;
  std::vector<Bind> anchor_bind;       // Member row word -> result column.
};
struct EdgeState {
  U32 parent = 0, child = 0, slot = 0, ordinal = 0;
  std::size_t arity = 0;
  bool connex = false;       // The child (and so the parent) is a connex node.
  bool merged = false;       // Connex with an identity parent: `up` is the prefix of `rev`.
  Fields parent_raw;         // Parent scope -> separator.
  Fields parent_fields;      // Parent store row -> separator.
  U32 group = nil;
  Slab* entries = nullptr;   // The group's rows: [key | one section per member edge]. This edge's
  Index* index = nullptr;    // section is [count,classes | rev | down | survivors or up].
  std::size_t w_count = 0, w_survivors = 0;
  List rev, down, up;
  std::array<const List*, 3> lists{};   // The present ones.
  std::size_t list_count = 0;
  Fields up_raw, down_raw;        // Visible fields outside the separator (parent / child).
  Fields up_source, down_source;  // The same as words of a member row.
  U32 up_onward = nil, down_onward = nil;            // Edge whose entry id rides in an element.
  U32 up_onward_word = nil, down_onward_word = nil;  // Its word in the member row.
};
// Edges whose separators range over the same values share one table, so that
// the entries one update reaches for the same key value lie in one row.
struct Group {
  std::size_t arity = 0;
  Slab entries;
  Index index;
  std::vector<U32> edges;
};
// A separator row an update of this table will touch, and the edges it uses there.
// `crossing` lists the edges on which the update's own node is the child: its
// support for the key may appear or disappear there and reach the parent's rows.
struct Probe { U32 group = 0; Fields key; std::vector<U32> edges, crossing; };
struct SourceState {
  std::size_t arity = 0;
  Slab rows;                 // [values | meta | direct node states]
  Index index;
  std::vector<U32> occurrences;
  std::vector<Probe> probes;
};
struct InputState {
  U32 node = 0;
  bool direct = false;
  Fields fields;
  std::vector<std::pair<U32, U32>> equalities;
  std::vector<std::pair<U32, Word>> constants;
};
}  // namespace

struct Runtime::Impl {
  PhysicalPlan plan;
  resource::MemoryAccount account;
  std::vector<NodeState> nodes;
  std::vector<EdgeState> edges;
  std::vector<Group> groups;
  std::vector<SourceState> sources;
  std::vector<InputState> inputs;
  std::vector<ScalarType> result_types;
  Pool pool;
  // Non-integer scalars. This prototype dictionary is grow-only and uses
  // ordinary containers outside the account; see the hand-off notes.
  std::map<Value, Word> dictionary;
  std::vector<Value> values;
  U32 root = nil, connex_root = nil;
  std::uint64_t root_support = 0;
  Statistics counts;
  bool adapted = false, poisoned = false;

  Impl(const PhysicalPlan& source, Options options)
      : plan(source), account(resource::MemoryAccount::create(options.memory_limit_bytes)) {
    require(plan.route() == PhysicalRoute::tree, "compact kernel needs a tree-routed plan");
    adapted = plan.normalized().has_value();
    compile_tree();
    compile_connex();
    compile_stores();
    compile_edges(options.shared_separators);
    compile_enumeration();
    for (const auto& field : plan.result_layout().fields()) result_types.push_back(field.type);
    require(result_types.size() <= max_result, "result is wider than the compact kernel supports");
  }

  // ---- Compilation ---------------------------------------------------------
  void compile_tree() {
    const auto& tree_nodes = plan.nodes();
    nodes.resize(tree_nodes.size());
    for (std::size_t i = 0; i < tree_nodes.size(); ++i) {
      const auto& from = tree_nodes[i];
      auto& node = nodes[i];
      node.kind = from.kind;
      node.arity = from.scope.size();
      node.children = from.children.size();
      node.connex = from.connex;
      require(node.arity <= max_fields && node.children < max_fields, "node is wider than the compact kernel supports");
      node.full_mask = (Word{1} << node.children) - 1;
      node.child_edges.assign(node.children, nil);
      for (const auto variable : from.scope) node.scope_variables.push_back(variable.value);
      node.separator_raw = fields_of(from.parent_key.fields());
      if (!from.parent) { require(root == nil, "plan has several roots"); root = narrow(i); }
      if (!node.connex) continue;
      require(from.visible_projection.has_value(), "connex node has no visible projection");
      node.visible_raw = fields_of(from.visible_projection->fields());
      node.visible_arity = node.visible_raw.size();
      require(from.visible_scope.size() == node.visible_arity, "visible scope differs from its projection");
      for (std::size_t field = 0; field < node.visible_arity; ++field) {
        require(node.visible_raw[field] < node.arity && from.visible_scope[field].value == node.scope_variables[node.visible_raw[field]],
            "visible projection differs from its variables");
        node.visible_variables.push_back(from.visible_scope[field].value);
      }
      // Identity: the visible tuple is a permutation of the whole scope, so
      // visible members and surviving records are the same thing.
      auto sorted = node.visible_raw;
      std::sort(sorted.begin(), sorted.end());
      node.identity = node.visible_arity == node.arity && std::adjacent_find(sorted.begin(), sorted.end()) == sorted.end();
    }
    require(root != nil, "plan has no root");
    edges.resize(plan.edges().size());
    for (std::size_t i = 0; i < edges.size(); ++i) {
      const auto& from = plan.edges()[i];
      auto& edge = edges[i];
      edge.parent = narrow(from.parent.value); edge.child = narrow(from.child.value); edge.slot = narrow(from.child_slot);
      edge.parent_raw = fields_of(from.parent_key.fields());
      edge.arity = edge.parent_raw.size();
      auto& parent = nodes[edge.parent];
      auto& child = nodes[edge.child];
      require(edge.arity == child.separator_raw.size(), "edge endpoints disagree on the separator arity");
      for (std::size_t field = 0; field < edge.arity; ++field)
        require(edge.parent_raw[field] < parent.arity && child.separator_raw[field] < child.arity &&
            parent.scope_variables[edge.parent_raw[field]] == child.scope_variables[child.separator_raw[field]],
            "edge endpoints disagree on the separator variables");
      if (parent.kind != NodeKind::native) {
        auto sorted = edge.parent_raw;
        std::sort(sorted.begin(), sorted.end());
        require(edge.arity == parent.arity && std::adjacent_find(sorted.begin(), sorted.end()) == sorted.end(),
            "generalized parent does not equal its separator");
      }
      require(edge.slot < parent.children && parent.child_edges[edge.slot] == nil, "duplicate child slot");
      parent.child_edges[edge.slot] = narrow(i);
      require(child.parent_edge == nil, "node has several parents");
      child.parent_edge = narrow(i);
    }
    for (std::size_t i = 0; i < nodes.size(); ++i) {
      require((nodes[i].parent_edge == nil) == (i == root), "tree edges do not match node parents");
      for (const auto edge : nodes[i].child_edges) require(edge != nil, "node child has no edge");
    }
  }
  // Connex nodes form a root-connected subtree; take its shape and the
  // separators in visible coordinates from the enumeration program.
  void compile_connex() {
    const auto& program = plan.enumeration();
    require(program.steps.size() <= max_depth, "enumeration is deeper than the compact kernel supports");
    std::vector<bool> seen(nodes.size(), false);
    for (const auto& step : program.steps) {
      const auto id = narrow(step.node.value);
      auto& node = nodes[id];
      require(node.connex && !seen[id], "enumeration step does not name one connex node");
      seen[id] = true;
      if (!step.parent_step) {
        require(connex_root == nil && id == root, "enumeration does not start at the tree root");
        connex_root = id;
        continue;
      }
      require(step.parent_key && step.bucket_index, "enumeration step has no separator programs");
      const auto parent = narrow(program.steps[*step.parent_step].node.value);
      require(node.parent_edge != nil && edges[node.parent_edge].parent == parent, "enumeration parent is not the tree parent");
      auto& edge = edges[node.parent_edge];
      auto& above = nodes[parent];
      node.visible_separator_raw = fields_of(plan.indexes()[step.bucket_index->value].projection.fields());
      const auto parent_key = fields_of(step.parent_key->fields());
      require(node.visible_separator_raw.size() == edge.arity && parent_key.size() == edge.arity, "visible separator arity differs from its edge");
      for (std::size_t field = 0; field < edge.arity; ++field) {
        const auto variable = node.scope_variables[node.separator_raw[field]];
        require(node.visible_separator_raw[field] < node.visible_arity && parent_key[field] < above.visible_arity &&
            node.visible_variables[node.visible_separator_raw[field]] == variable && above.visible_variables[parent_key[field]] == variable,
            "visible separator differs from the edge separator");
      }
      edge.connex = true;
      edge.ordinal = narrow(above.connex_children.size());
      above.connex_children.push_back(id);
      above.visible_child_raw.push_back(parent_key);
    }
    for (std::size_t id = 0; id < nodes.size(); ++id) require(nodes[id].connex == seen[id], "connex node is missing from the enumeration");
  }
  // Decide where every node keeps its records and lay out the rows.
  void compile_stores() {
    const auto& tables = plan.source_catalog().tables;
    sources.resize(tables.size());
    require(plan.base_routes().size() <= sources.size(), "plan routes name an unknown base table");
    inputs.resize(plan.inputs().size());
    std::vector<std::size_t> feeders(nodes.size(), 0);
    for (const auto& from : plan.inputs()) { require(from.node.value < nodes.size(), "input names an unknown node"); ++feeders[from.node.value]; }
    std::vector<std::size_t> stride(sources.size());
    for (std::size_t i = 0; i < tables.size(); ++i) {
      sources[i].arity = tables[i].columns.size();
      require(sources[i].arity >= 1 && sources[i].arity <= max_fields, "source table arity is outside the compact kernel's range");
      stride[i] = sources[i].arity + 1;
    }
    const auto state_words = [&](const NodeState& node) { return (node.children ? 1U : 0U) + node.children + (node.parent_edge != nil ? 1U : 0U); };
    const auto place_state = [&](NodeState& node, std::size_t base) {
      node.w_mask = base;
      node.w_child = base + (node.children ? 1 : 0);
      node.w_parent = node.w_child + node.children;
    };
    for (std::size_t table = 0; table < plan.base_routes().size(); ++table) {
      for (const auto occurrence : plan.base_routes()[table]) {
        const auto id = narrow(occurrence.value);
        require(id < inputs.size(), "route names an unknown input");
        sources[table].occurrences.push_back(id);
        const auto& from = plan.inputs()[id];
        auto& input = inputs[id];
        input.node = narrow(from.node.value);
        auto& node = nodes[input.node];
        require(node.kind == NodeKind::native, "input feeds a generalized node");
        if (adapted) continue;  // SQL adapters run through PhysicalPlan::adapt_input.
        input.fields = fields_of(from.projection.fields());
        require(input.fields.size() == node.arity, "input projection differs from its node scope");
        for (const auto field : input.fields) require(field < sources[table].arity, "input field is outside its source row");
        for (const auto& pair : from.equalities) input.equalities.emplace_back(narrow(pair.left.value), narrow(pair.right.value));
        for (const auto& fixed : from.constants) input.constants.emplace_back(narrow(fixed.field.value), encode(fixed.value));
        auto sorted = input.fields;
        std::sort(sorted.begin(), sorted.end());
        input.direct = feeders[input.node] == 1 && input.equalities.empty() && input.constants.empty() &&
            node.arity == sources[table].arity && std::adjacent_find(sorted.begin(), sorted.end()) == sorted.end();
        if (!input.direct) continue;
        node.direct = true;
        node.store = &sources[table].rows;
        node.position = input.fields;
        node.meta = sources[table].arity;
        place_state(node, stride[table]);
        stride[table] += state_words(node);
      }
    }
    for (std::size_t i = 0; i < sources.size(); ++i) sources[i].rows.configure(stride[i], sources[i].arity, resource::MemoryPurpose::tuple_values);
    for (auto& node : nodes) {
      if (!node.direct) {
        node.store = &node.own;
        for (U32 field = 0; field < node.arity; ++field) node.position.push_back(field);
        node.meta = node.arity;
        place_state(node, node.arity + 1);
        node.own.configure(node.arity + 1 + state_words(node), node.arity, resource::MemoryPurpose::tuple_values);
      }
      node.separator = compose(node.separator_raw, node.position);
      if (!node.connex) continue;
      node.visible_fields = compose(node.visible_raw, node.position);
      const std::size_t parent_words = node.parent_edge != nil ? 1 : 0;
      if (node.identity) {
        node.members = node.store;
        node.member_position = node.visible_fields;
        node.v_meta = node.meta;
        node.v_parent = node.w_parent;
        for (const auto child : node.connex_children) node.v_child.push_back(narrow(node.w_child + edges[nodes[child].parent_edge].slot));
      } else {
        node.members = &node.visible;
        for (U32 field = 0; field < node.visible_arity; ++field) node.member_position.push_back(field);
        node.v_meta = node.visible_arity;
        node.v_parent = node.visible_arity + 1;
        for (std::size_t k = 0; k < node.connex_children.size(); ++k) node.v_child.push_back(narrow(node.visible_arity + 1 + parent_words + k));
        node.visible.configure(node.visible_arity + 1 + parent_words + node.connex_children.size(), node.visible_arity,
            resource::MemoryPurpose::secondary_node);
      }
    }
  }
  [[nodiscard]] U32 member_entry_word(const NodeState& node, U32 edge) const {
    if (edge == node.parent_edge) return narrow(node.v_parent);
    require(edges[edge].parent == static_cast<U32>(&node - nodes.data()) && edges[edge].connex, "member has no entry for this edge");
    return node.v_child[edges[edge].ordinal];
  }
  void compile_edges(bool share) {
    for (std::size_t id = 0; id < edges.size(); ++id) {
      auto& edge = edges[id];
      const auto& parent = nodes[edge.parent];
      const auto& child = nodes[edge.child];
      edge.parent_fields = compose(edge.parent_raw, parent.position);
      edge.rev = List{true, 0, 1, 40, 0};
      if (edge.connex) {
        require(parent.connex, "connex child has a parent outside the connex part");
        edge.merged = parent.identity;
        edge.up_raw = complement(parent.visible_arity, parent.visible_child_raw[edge.ordinal]);
        edge.down_raw = complement(child.visible_arity, child.visible_separator_raw);
        edge.up_source = compose(edge.up_raw, parent.member_position);
        edge.down_source = compose(edge.down_raw, child.member_position);
        edge.down = List{true, 0, 1 + edge.down_raw.size(), 32, 0};
        if (edge.merged) edge.rev.stride = 1 + edge.up_raw.size();
        else edge.up = List{true, 0, 1 + edge.up_raw.size(), 48, 0};
        // The entry id that rides along in each element is the one the usual
        // traversal needs next: towards the root if there is one, else the
        // first other connex branch.
        if (parent.parent_edge != nil) edge.up_onward = parent.parent_edge;
        else for (const auto other : parent.connex_children) if (other != edge.child) { edge.up_onward = nodes[other].parent_edge; break; }
        if (!child.connex_children.empty()) edge.down_onward = nodes[child.connex_children.front()].parent_edge;
        if (edge.up_onward != nil) edge.up_onward_word = member_entry_word(parent, edge.up_onward);
        if (edge.down_onward != nil) edge.down_onward_word = member_entry_word(child, edge.down_onward);
      }
      for (auto* list : {&edge.rev, &edge.down, &edge.up}) {
        list->first = first_class(list->stride);
        if (list->present) edge.lists[edge.list_count++] = list;
      }
    }
    // Two variables range over the same domain when some source column binds
    // both (a self-join, or one variable seen through several atoms). Edges
    // whose separators agree domain by domain share a table. Sharing is only a
    // layout choice: any grouping of equal-arity edges is correct.
    std::size_t variables = 0;
    for (const auto& node : nodes) for (const auto variable : node.scope_variables) variables = std::max(variables, variable + 1);
    std::vector<std::size_t> domain(variables);
    for (std::size_t i = 0; i < variables; ++i) domain[i] = i;
    const auto find = [&](std::size_t variable) {
      while (domain[variable] != variable) variable = domain[variable] = domain[domain[variable]];
      return variable;
    };
    if (!adapted) {
      std::map<std::pair<std::size_t, U32>, std::size_t> bound;
      for (std::size_t table = 0; table < sources.size(); ++table)
        for (const auto occurrence : sources[table].occurrences) {
          const auto& input = inputs[occurrence];
          for (std::size_t field = 0; field < input.fields.size(); ++field) {
            const auto variable = nodes[input.node].scope_variables[field];
            const auto [place, fresh] = bound.emplace(std::pair{table, input.fields[field]}, variable);
            if (!fresh) domain[find(variable)] = find(place->second);
          }
        }
    }
    std::vector<std::vector<std::size_t>> signatures;
    for (std::size_t id = 0; id < edges.size(); ++id) {
      auto& edge = edges[id];
      std::vector<std::size_t> signature;
      for (const auto field : edge.parent_raw) signature.push_back(find(nodes[edge.parent].scope_variables[field]));
      std::size_t group = groups.size();
      if (share) for (std::size_t other = 0; other < groups.size(); ++other) if (signatures[other] == signature) { group = other; break; }
      if (group == groups.size()) { groups.emplace_back(); groups.back().arity = edge.arity; signatures.push_back(std::move(signature)); }
      groups[group].edges.push_back(narrow(id));
      edge.group = narrow(group);
    }
    for (auto& group : groups) {
      std::size_t next = group.arity;
      for (const auto id : group.edges) {
        auto& edge = edges[id];
        edge.entries = &group.entries;
        edge.index = &group.index;
        edge.w_count = next++;
        edge.rev.word = next++;
        if (!edge.connex) continue;
        edge.down.word = next++;
        if (edge.merged) edge.w_survivors = next++; else edge.up.word = next++;
      }
      group.entries.configure(next, group.arity, resource::MemoryPurpose::secondary_node);
    }
    // The separator rows a source row reaches through its direct nodes depend
    // on the row alone, so a batch can fetch them ahead of time.
    for (auto& source : sources) {
      const auto add = [&](U32 edge, const Fields& key, bool child_side = false) {
        auto place = std::find_if(source.probes.begin(), source.probes.end(),
            [&](const Probe& probe) { return probe.group == edges[edge].group && probe.key == key; });
        if (place == source.probes.end()) place = source.probes.insert(place, Probe{edges[edge].group, key, {}, {}});
        if (std::find(place->edges.begin(), place->edges.end(), edge) == place->edges.end()) place->edges.push_back(edge);
        if (child_side && std::find(place->crossing.begin(), place->crossing.end(), edge) == place->crossing.end()) place->crossing.push_back(edge);
      };
      for (const auto occurrence : source.occurrences) {
        const auto& input = inputs[occurrence];
        if (!input.direct) continue;
        const auto& node = nodes[input.node];
        for (const auto edge : node.child_edges) add(edge, edges[edge].parent_fields);
        if (node.parent_edge == nil) continue;
        add(node.parent_edge, node.separator, true);
        // A generalized parent's candidate for this key also sits in the
        // entries of its other children, which creating or dropping it touches.
        const auto& above = edges[node.parent_edge];
        const auto& parent = nodes[above.parent];
        if (parent.kind == NodeKind::native) continue;
        for (const auto sibling : parent.child_edges) {
          if (sibling == node.parent_edge) continue;
          Fields key;
          for (const auto field : edges[sibling].parent_raw)
            key.push_back(node.separator[static_cast<std::size_t>(
                std::find(above.parent_raw.begin(), above.parent_raw.end(), field) - above.parent_raw.begin())]);
          add(sibling, key);
        }
      }
    }
  }
  // For every connex node, a traversal of the whole connex subtree anchored at
  // it, so that a visible membership change enumerates exactly its own rows.
  void compile_enumeration() {
    const auto& program = plan.enumeration();
    for (std::size_t anchor = 0; anchor < nodes.size(); ++anchor) {
      auto& node = nodes[anchor];
      if (!node.connex) continue;
      std::vector<U32> position(nodes.size(), nil);
      auto& steps = node.anchored;
      steps.push_back(Step{});
      steps.back().node = narrow(anchor);
      position[anchor] = 0;
      for (std::size_t at = 0; at < steps.size(); ++at) {
        const auto current = steps[at].node;
        const auto& here = nodes[current];
        const auto add = [&](U32 target, U32 edge_id, bool up) {
          if (position[target] != nil) return;
          const auto& edge = edges[edge_id];
          Step step;
          step.node = target; step.from = narrow(at); step.edge = edge_id; step.up = up;
          step.entry_word = member_entry_word(here, edge_id);
          if (at != 0) {
            const auto& via = steps[at];
            step.inline_entry = (via.up ? edges[via.edge].up_onward : edges[via.edge].down_onward) == edge_id;
          }
          const auto& list = !up ? edge.down : edge.merged ? edge.rev : edge.up;
          step.list_word = narrow(list.word);
          step.stride = list.stride;
          step.prefix = up && edge.merged;
          step.count_word = narrow(edge.w_survivors);
          position[target] = narrow(steps.size());
          steps.push_back(std::move(step));
        };
        if (here.parent_edge != nil) add(edges[here.parent_edge].parent, here.parent_edge, true);
        for (const auto child : here.connex_children) add(child, nodes[child].parent_edge, false);
      }
      require(steps.size() == program.steps.size(), "anchored traversal does not cover the connex subtree");
      for (std::size_t at = steps.size(); at-- > 1;)
        if (steps[at].inline_entry) steps[steps[at].from].warm = narrow(at);
      // A result column is read where its variable first appears: there it lies
      // outside the separator, so it is part of that step's element payload.
      for (std::size_t column = 0; column < program.output.size(); ++column) {
        const auto& slot = program.output[column];
        require(slot.step < program.steps.size(), "output slot names an unknown step");
        const auto& owner = nodes[program.steps[slot.step].node.value];
        require(slot.field.value < owner.visible_arity, "output slot is outside its visible tuple");
        const auto variable = owner.visible_variables[slot.field.value];
        bool bound = false;
        for (std::size_t at = 0; at < steps.size() && !bound; ++at) {
          const auto& holder = nodes[steps[at].node];
          const auto found = std::find(holder.visible_variables.begin(), holder.visible_variables.end(), variable);
          if (found == holder.visible_variables.end()) continue;
          const auto field = static_cast<U32>(found - holder.visible_variables.begin());
          if (at == 0) node.anchor_bind.push_back({holder.member_position[field], narrow(column)});
          else {
            const auto& payload = steps[at].up ? edges[steps[at].edge].up_raw : edges[steps[at].edge].down_raw;
            const auto place = std::find(payload.begin(), payload.end(), field);
            require(place != payload.end(), "result variable first appears inside a separator");
            steps[at].bind.push_back({narrow(1 + static_cast<std::size_t>(place - payload.begin())), narrow(column)});
          }
          bound = true;
        }
        require(bound, "result variable is not visible in the connex part");
      }
    }
  }

  [[nodiscard]] Word encode(const Value& value) {
    if (const auto* number = std::get_if<std::int64_t>(&value)) return static_cast<Word>(*number);
    if (const auto* flag = std::get_if<bool>(&value)) return *flag ? 1 : 0;
    const auto found = dictionary.find(value);
    if (found != dictionary.end()) return found->second;
    const auto id = static_cast<Word>(values.size());
    values.push_back(value);
    dictionary.emplace(value, id);
    ++counts.dictionary_values;
    return id;
  }

  // ---- Separator entries and their arrays ----------------------------------
  [[nodiscard]] U32 find_entry(const EdgeState& edge, const Word* key, Word hash) const noexcept {
    return edge.index->find(hash, [&](U32 index) { return equal_words(edge.entries->at(index), key, edge.arity); });
  }
  // The last few rows resolved for single-word keys. One update reaches the
  // same row through several nodes and edges, so most lookups end here. A row
  // id stays valid until release_entry drops it, which also clears it here.
  struct Recent { U32 group = nil, id = nil; Word key = 0; };
  std::array<Recent, 4> recent;
  unsigned recent_next = 0;
  [[nodiscard]] U32 entry(EdgeState& edge, const Word* key) {
    if (edge.arity == 1)
      for (const auto& hit : recent) if (hit.group == edge.group && hit.key == key[0]) return hit.id;
    const auto hash = hash_words(key, edge.arity);
    auto found = find_entry(edge, key, hash);
    if (found == nil) found = create_entry(edge, key, hash);
    if (edge.arity == 1) recent[recent_next++ % recent.size()] = {edge.group, found, key[0]};
    return found;
  }
  [[nodiscard]] U32 create_entry(EdgeState& edge, const Word* key, Word hash) {
    const auto found = edge.entries->allocate(account);
    auto* words = edge.entries->at(found);
    std::memcpy(words, key, edge.arity * sizeof(Word));
    for (const auto member : groups[edge.group].edges) {
      const auto& peer = edges[member];
      words[peer.w_count] = 0;
      for (std::size_t k = 0; k < peer.list_count; ++k) words[peer.lists[k]->word] = pack(nil, 0);
      if (peer.merged) words[peer.w_survivors] = 0;
    }
    edge.index->insert(account, hash, found);
    ++counts.separator_keys;
    return found;
  }
  void release_entry(EdgeState& edge, U32 index) noexcept {
    const auto* words = edge.entries->at(index);
    for (const auto member : groups[edge.group].edges) {
      const auto& peer = edges[member];
      if (low(words[peer.w_count]) != 0) return;
      for (std::size_t k = 0; k < peer.list_count; ++k) if (high(words[peer.lists[k]->word]) != 0) return;
    }
    edge.index->erase(hash_words(words, edge.arity), index);
    edge.entries->release(index);
    --counts.separator_keys;
    for (auto& hit : recent) if (hit.group == edge.group && hit.id == index) hit.group = nil;
  }
  [[nodiscard]] static unsigned class_of(Word count_word, const List& list) noexcept {
    return static_cast<unsigned>((count_word >> list.shift) & 0xffU);
  }
  static void set_class(Word& count_word, const List& list, unsigned value) noexcept {
    count_word = (count_word & ~(Word{0xff} << list.shift)) | (Word{value} << list.shift);
  }
  // Appends one element to an array of entry `at`; returns its position and
  // points `element` at its words.
  U32 push(EdgeState& edge, const List& list, U32 at, Word*& element) {
    Word* words = edge.entries->at(at);
    U32 block = low(words[list.word]);
    const U32 length = high(words[list.word]);
    const unsigned size_class = class_of(words[edge.w_count], list);
    if (block == nil) {
      block = pool.allocate(account, list.first);
      set_class(words[edge.w_count], list, list.first);
    } else if ((static_cast<std::size_t>(length) + 1) * list.stride > (std::size_t{1} << size_class)) {
      const U32 wider = pool.allocate(account, size_class + 1);
      std::memcpy(pool.at(wider), pool.at(block), static_cast<std::size_t>(length) * list.stride * sizeof(Word));
      pool.release(block, size_class);
      block = wider;
      set_class(words[edge.w_count], list, size_class + 1);
    }
    require(length < nil - 1, "compact list length overflow");
    words[list.word] = pack(block, length + 1);
    element = pool.at(block) + static_cast<std::size_t>(length) * list.stride;
    return length;
  }
  // Removes the element at `position` by moving the last one into its place;
  // returns the member that moved (its stored position must be updated) or nil.
  U32 pull(EdgeState& edge, const List& list, U32 at, U32 position) {
    Word* words = edge.entries->at(at);
    U32 block = low(words[list.word]);
    require(block != nil && position < high(words[list.word]), "removing a member that is not in its list");
    const U32 last = high(words[list.word]) - 1;
    const unsigned size_class = class_of(words[edge.w_count], list);
    Word* base = pool.at(block);
    U32 moved = nil;
    if (position != last) {
      std::memcpy(base + static_cast<std::size_t>(position) * list.stride, base + static_cast<std::size_t>(last) * list.stride,
          list.stride * sizeof(Word));
      moved = low(base[static_cast<std::size_t>(position) * list.stride]);
    }
    if (last == 0) {
      pool.release(block, size_class);
      block = nil;
    } else if (size_class > list.first && static_cast<std::size_t>(last) * list.stride * 4 <= (std::size_t{1} << size_class)) {
      const U32 narrower = pool.allocate(account, size_class - 1);
      std::memcpy(pool.at(narrower), pool.at(block), static_cast<std::size_t>(last) * list.stride * sizeof(Word));
      pool.release(block, size_class);
      block = narrower;
      set_class(words[edge.w_count], list, size_class - 1);
    }
    words[list.word] = pack(block, last);
    return moved;
  }

  // ---- Records ---------------------------------------------------------------
  [[nodiscard]] static bool survives(const NodeState& node, const Word* row) noexcept {
    return node.children == 0 || row[node.w_mask] == node.full_mask;
  }
  // Enters a new record into the rev array of each child edge and computes its
  // child-presence mask.
  void attach(U32 id, U32 record) {
    auto& node = nodes[id];
    Word mask = 0;
    for (std::size_t slot = 0; slot < node.children; ++slot) {
      auto& edge = edges[node.child_edges[slot]];
      std::array<Word, max_fields> key;
      project(node.store->at(record), edge.parent_fields, key.data());
      const auto found = entry(edge, key.data());
      Word* element;
      const auto position = push(edge, edge.rev, found, element);
      Word* row = node.store->at(record);
      element[0] = pack(record, nil);
      for (std::size_t i = 0; i + 1 < edge.rev.stride; ++i) element[1 + i] = row[edge.up_source[i]];
      row[node.w_child + slot] = pack(found, position);
      if (low(edge.entries->at(found)[edge.w_count]) != 0) mask |= Word{1} << slot;
    }
    if (node.children) node.store->at(record)[node.w_mask] = mask;
  }
  // Removes a record that does not survive from its rev arrays. Row
  // `keep_entry` of group `keep_group` is left for the caller to release.
  void detach(U32 id, U32 record, U32 keep_group = nil, U32 keep_entry = nil) {
    auto& node = nodes[id];
    for (std::size_t slot = 0; slot < node.children; ++slot) {
      auto& edge = edges[node.child_edges[slot]];
      const Word place = node.store->at(record)[node.w_child + slot];
      const auto moved = pull(edge, edge.rev, low(place), high(place));
      if (moved != nil) node.store->at(moved)[node.w_child + slot] = place;
      if (edge.group != keep_group || low(place) != keep_entry) release_entry(edge, low(place));
    }
  }
  // One child-presence bit of one record changes; survival changes only when
  // the mask becomes or stops being complete.
  void flip(U32 id, U32 record, std::size_t slot, bool add, RowSink* sink) {
    auto& node = nodes[id];
    Word& mask = node.store->at(record)[node.w_mask];
    const Word bit = Word{1} << slot;
    require(((mask & bit) != 0) != add, "child presence transition applied twice");
    const bool before = mask == node.full_mask;
    mask ^= bit;
    if (before != (mask == node.full_mask)) survive(id, record, add, sink);
  }
  // A record enters or leaves S: its support key may cross and reach the
  // parent, and in the connex part its visible member may appear or vanish.
  // Result rows are reported while the member is linked: after linking on the
  // way in, before unlinking on the way out.
  void survive(U32 id, U32 record, bool add, RowSink* sink) {
    auto& node = nodes[id];
    if (add) {
      ++counts.survivors;
      if (node.parent_edge == nil) {
        if (++root_support == 1 && sink && connex_root == nil) sink->row(nullptr);
      } else {
        auto& edge = edges[node.parent_edge];
        std::array<Word, max_fields> key;
        project(node.store->at(record), node.separator, key.data());
        const auto found = entry(edge, key.data());
        node.store->at(record)[node.w_parent] = pack(found, nil);
        Word& head = edge.entries->at(found)[edge.w_count];
        require(low(head) != nil, "support count overflow");
        ++head;
        if (low(head) == 1) crossing(node.parent_edge, found, true, sink);
      }
      if (node.connex) appear(id, record, sink);
      return;
    }
    --counts.survivors;
    if (node.connex) vanish(id, record, sink);
    if (node.parent_edge == nil) {
      if (--root_support == 0 && sink && connex_root == nil) sink->row(nullptr);
      return;
    }
    auto& edge = edges[node.parent_edge];
    const auto found = low(node.store->at(record)[node.w_parent]);
    Word& head = edge.entries->at(found)[edge.w_count];
    require(low(head) != 0, "removing an absent support key");
    --head;
    if (low(head) == 0) crossing(node.parent_edge, found, false, sink);
    release_entry(edge, found);
  }
  // The child's support for one separator key appears or disappears: every
  // parent record with that key gains or loses the child. Flips propagate
  // towards the root only, so this rev array keeps its members; with a merged
  // edge the members that change survival are moved across its boundary.
  void crossing(U32 edge_id, U32 found, bool add, RowSink* sink) {
    auto& edge = edges[edge_id];
    const auto parent = edge.parent;
    const auto slot = static_cast<std::size_t>(edge.slot);
    auto& node = nodes[parent];
    const bool generalized = node.kind != NodeKind::native;
    if (generalized && add && high(edge.entries->at(found)[edge.rev.word]) == 0) create_candidate(edge_id, found);
    const auto member = [&](U32 index) {
      return low(pool.at(low(edge.entries->at(found)[edge.rev.word]))[static_cast<std::size_t>(index) * edge.rev.stride]);
    };
    const U32 length = high(edge.entries->at(found)[edge.rev.word]);
    if (edge.merged && !add) {
      // Survivors leave from the back so each is already at the boundary.
      const U32 survivors = low(edge.entries->at(found)[edge.w_survivors]);
      for (U32 index = survivors; index-- > 0;) flip(parent, member(index), slot, false, sink);
      for (U32 index = survivors; index < length; ++index) flip(parent, member(index), slot, false, sink);
    } else {
      // A member promoted into the prefix trades places with an earlier one.
      for (U32 index = 0; index < length; ++index) flip(parent, member(index), slot, add, sink);
    }
    if (generalized && !add) {
      require(length == 1, "generalized key has several candidates");
      const auto candidate = member(0);
      if (node.store->at(candidate)[node.w_mask] == 0) {
        detach(parent, candidate, edge.group, found);
        node.own.release(candidate);
        --counts.records;
      }
    }
  }
  // A generalized node's candidate is its separator key; it exists exactly
  // while at least one child supplies that key.
  void create_candidate(U32 edge_id, U32 found) {
    auto& edge = edges[edge_id];
    auto& node = nodes[edge.parent];
    const auto record = node.own.allocate(account);
    Word* row = node.own.at(record);
    const Word* key = edge.entries->at(found);
    for (std::size_t i = 0; i < edge.arity; ++i) row[edge.parent_raw[i]] = key[i];
    row[node.meta] = pack(1, 0);
    ++counts.records;
    attach(edge.parent, record);
    // The crossing that created it reports this child itself.
    Word& mask = node.own.at(record)[node.w_mask];
    require(mask == (Word{1} << edge.slot), "new generalized candidate already had support");
    mask = 0;
  }

  // ---- Visible members -------------------------------------------------------
  void appear(U32 id, U32 record, RowSink* sink) {
    auto& node = nodes[id];
    U32 member = record;
    if (!node.identity) {
      std::array<Word, max_fields> key;
      const Word* row = node.store->at(record);
      project(row, node.visible_fields, key.data());
      const auto hash = hash_words(key.data(), node.visible_arity);
      member = node.visible_index.find(hash, [&](U32 index) { return equal_words(node.visible.at(index), key.data(), node.visible_arity); });
      if (member != nil) {
        Word& meta = node.visible.at(member)[node.v_meta];
        require(low(meta) != nil, "visible count overflow");
        ++meta;
        return;
      }
      member = node.visible.allocate(account);
      Word* words = node.visible.at(member);
      row = node.store->at(record);
      std::memcpy(words, key.data(), node.visible_arity * sizeof(Word));
      words[node.v_meta] = 1;
      if (node.parent_edge != nil) words[node.v_parent] = pack(low(row[node.w_parent]), nil);
      for (std::size_t k = 0; k < node.connex_children.size(); ++k)
        words[node.v_child[k]] = pack(low(row[node.w_child + edges[nodes[node.connex_children[k]].parent_edge].slot]), nil);
      node.visible_index.insert(account, hash, member);
    }
    ++counts.visible_keys;
    link(id, member);
    if (sink) emit(id, member, *sink);
  }
  void vanish(U32 id, U32 record, RowSink* sink) {
    auto& node = nodes[id];
    U32 member = record;
    Word hash = 0;
    if (!node.identity) {
      std::array<Word, max_fields> key;
      project(node.store->at(record), node.visible_fields, key.data());
      hash = hash_words(key.data(), node.visible_arity);
      member = node.visible_index.find(hash, [&](U32 index) { return equal_words(node.visible.at(index), key.data(), node.visible_arity); });
      require(member != nil, "removing an absent visible key");
      Word& meta = node.visible.at(member)[node.v_meta];
      if (--meta != 0) return;
      meta = 1;  // Still a live row while its result rows are reported.
    }
    if (sink) emit(id, member, *sink);
    unlink(id, member);
    --counts.visible_keys;
    if (node.identity) return;
    node.visible_index.erase(hash, member);
    node.visible.release(member);
  }
  // Exchanges two elements of a merged rev array and repairs the stored
  // position of the one that is not `member`.
  void exchange(NodeState& node, std::size_t word, const EdgeState& edge, U32 at, U32 member, U32 from, U32 to) {
    Word* base = pool.at(low(edge.entries->at(at)[edge.rev.word]));
    Word* left = base + static_cast<std::size_t>(from) * edge.rev.stride;
    Word* right = base + static_cast<std::size_t>(to) * edge.rev.stride;
    for (std::size_t i = 0; i < edge.rev.stride; ++i) std::swap(left[i], right[i]);
    node.store->at(low(left[0]))[word] = pack(at, from);
    node.store->at(member)[word] = pack(at, to);
  }
  void link(U32 id, U32 member) {
    auto& node = nodes[id];
    if (node.parent_edge != nil) {
      auto& edge = edges[node.parent_edge];
      const U32 at = low(node.members->at(member)[node.v_parent]);
      Word* element;
      const auto position = push(edge, edge.down, at, element);
      Word* row = node.members->at(member);
      element[0] = pack(member, edge.down_onward_word == nil ? nil : low(row[edge.down_onward_word]));
      for (std::size_t i = 0; i < edge.down_source.size(); ++i) element[1 + i] = row[edge.down_source[i]];
      row[node.v_parent] = pack(at, position);
    }
    for (std::size_t k = 0; k < node.connex_children.size(); ++k) {
      auto& edge = edges[nodes[node.connex_children[k]].parent_edge];
      const std::size_t word = node.v_child[k];
      Word* row = node.members->at(member);
      const U32 at = low(row[word]);
      const U32 onward = edge.up_onward_word == nil ? nil : low(row[edge.up_onward_word]);
      if (edge.merged) {
        Word* words = edge.entries->at(at);
        const U32 boundary = low(words[edge.w_survivors]);
        if (high(row[word]) != boundary) exchange(node, word, edge, at, member, high(row[word]), boundary);
        pool.at(low(words[edge.rev.word]))[static_cast<std::size_t>(boundary) * edge.rev.stride] = pack(member, onward);
        words[edge.w_survivors] = boundary + 1;
      } else {
        Word* element;
        const auto position = push(edge, edge.up, at, element);
        row = node.members->at(member);
        element[0] = pack(member, onward);
        for (std::size_t i = 0; i < edge.up_source.size(); ++i) element[1 + i] = row[edge.up_source[i]];
        row[word] = pack(at, position);
      }
    }
  }
  void unlink(U32 id, U32 member) {
    auto& node = nodes[id];
    for (std::size_t k = 0; k < node.connex_children.size(); ++k) {
      auto& edge = edges[nodes[node.connex_children[k]].parent_edge];
      const std::size_t word = node.v_child[k];
      const Word place = node.members->at(member)[word];
      if (edge.merged) {
        Word* words = edge.entries->at(low(place));
        const U32 boundary = low(words[edge.w_survivors]) - 1;
        if (high(place) != boundary) exchange(node, word, edge, low(place), member, high(place), boundary);
        words[edge.w_survivors] = boundary;
      } else {
        const auto moved = pull(edge, edge.up, low(place), high(place));
        if (moved != nil) node.members->at(moved)[word] = place;
      }
    }
    if (node.parent_edge == nil) return;
    auto& edge = edges[node.parent_edge];
    const Word place = node.members->at(member)[node.v_parent];
    const auto moved = pull(edge, edge.down, low(place), high(place));
    if (moved != nil) node.members->at(moved)[node.v_parent] = place;
  }
  // All result rows that contain visible member `member` of connex node `id`,
  // in the current state. Each further node is reached through one separator
  // entry, whose array already holds the values that node contributes.
  void emit(U32 id, U32 member, RowSink& sink) const {
    const auto& anchor = nodes[id];
    const auto& steps = anchor.anchored;
    const auto depth = steps.size();
    std::array<const Word*, max_depth> current, end;
    std::array<Word, max_result> row;
    const Word* origin = anchor.members->at(member);
    for (const auto& bind : anchor.anchor_bind) row[bind.column] = origin[bind.from];
    if (depth == 1) { sink.row(row.data()); return; }
    const Word* arrays = pool.words.data();
    const auto open = [&](std::size_t level) {
      const auto& step = steps[level];
      U32 at;
      if (step.from == 0) at = low(origin[step.entry_word]);
      else if (step.inline_entry) at = high(current[step.from][0]);
      else at = low(nodes[steps[step.from].node].members->at(low(current[step.from][0]))[step.entry_word]);
      const Word* words = edges[step.edge].entries->at(at);
      const Word head = words[step.list_word];
      const std::size_t length = step.prefix ? low(words[step.count_word]) : high(head);
      const Word* base = length ? arrays + low(head) : nullptr;
      current[level] = base;
      end[level] = base + length * step.stride;
      if (step.warm == nil || length < 2) return;
      // The next level opens one entry per element here; start those loads
      // together instead of meeting them one at a time.
      const auto& next = steps[step.warm];
      const auto& entries = *edges[next.edge].entries;
      const std::size_t ahead = std::min<std::size_t>(length, 16);
      for (std::size_t i = 0; i < ahead; ++i) __builtin_prefetch(entries.at(high(base[i * step.stride])) + next.list_word);
      for (std::size_t i = 0; i < ahead; ++i) {
        const Word list = entries.at(high(base[i * step.stride]))[next.list_word];
        if (low(list) != nil) __builtin_prefetch(arrays + low(list));
      }
    };
    // The lists reached from the anchor itself do not depend on any loop
    // variable: if one of them is empty there is no row at all.
    std::array<const Word*, max_depth> fixed;
    std::size_t direct = 1;
    for (; direct < depth && steps[direct].from == 0; ++direct) {
      open(direct);
      if (current[direct] == end[direct]) return;
      fixed[direct] = current[direct];
    }
    std::size_t level = 1;
    for (;;) {
      const auto& step = steps[level];
      if (current[level] == end[level]) {
        if (--level == 0) return;
        current[level] += steps[level].stride;
        continue;
      }
      if (level + 1 != depth) {
        for (const auto& bind : step.bind) row[bind.column] = current[level][bind.from];
        if (++level < direct) current[level] = fixed[level]; else open(level);
        continue;
      }
      const Word* element = current[level];
      const Word* const last = end[level];
      const auto stride = step.stride;
      const Bind* binds = step.bind.data();
      const auto bound = step.bind.size();
      do {
        for (std::size_t i = 0; i < bound; ++i) row[binds[i].column] = element[binds[i].from];
        sink.row(row.data());
        element += stride;
      } while (element != last);
      current[level] = last;
    }
  }

  // ---- Physical routing ------------------------------------------------------
  void route(U32 occurrence, const Word* source, const Row* row, bool add, RowSink* sink) {
    const auto& input = inputs[occurrence];
    auto& node = nodes[input.node];
    std::array<Word, max_fields> tuple;
    if (adapted) {
      require(row != nullptr, "an adapted plan needs the original row values");
      const auto adapted_tuple = plan.adapt_input(OccurrenceId{occurrence}, *row);
      if (!adapted_tuple) return;
      const auto exported = storage::export_row(adapted_tuple->values());
      require(exported.size() == node.arity, "adapted input differs from its node scope");
      for (std::size_t i = 0; i < exported.size(); ++i) tuple[i] = encode(exported[i]);
    } else {
      for (const auto& [left, right] : input.equalities) if (source[left] != source[right]) return;
      for (const auto& [field, value] : input.constants) if (source[field] != value) return;
      project(source, input.fields, tuple.data());
    }
    const auto hash = hash_words(tuple.data(), node.arity);
    auto record = node.record_index.find(hash, [&](U32 index) { return equal_words(node.own.at(index), tuple.data(), node.arity); });
    if (add) {
      if (record != nil) {
        Word& meta = node.own.at(record)[node.meta];
        require(high(meta) != nil, "derivation count overflow");
        meta = pack(1, high(meta) + 1);
        return;
      }
      record = node.own.allocate(account);
      Word* words = node.own.at(record);
      std::memcpy(words, tuple.data(), node.arity * sizeof(Word));
      words[node.meta] = pack(1, 1);
      node.record_index.insert(account, hash, record);
      ++counts.records;
      attach(input.node, record);
      if (survives(node, node.own.at(record))) survive(input.node, record, true, sink);
      return;
    }
    require(record != nil && high(node.own.at(record)[node.meta]) != 0, "erasing an input row without a derivation");
    Word& meta = node.own.at(record)[node.meta];
    meta = pack(1, high(meta) - 1);
    if (high(meta) != 0) return;
    if (survives(node, node.own.at(record))) survive(input.node, record, false, sink);
    detach(input.node, record);
    node.record_index.erase(hash, record);
    node.own.release(record);
    --counts.records;
  }
  bool apply(TableId table, SetOperation operation, const Word* words, const Row* row, RowSink* sink, Word hash) {
    auto& source = sources[table.value];
    const bool add = operation == SetOperation::insert;
    const auto found = source.index.find(hash, [&](U32 index) { return equal_words(source.rows.at(index), words, source.arity); });
    if (add == (found != nil)) return false;
    struct Guard { bool& flag; bool done = false; ~Guard() { if (!done) flag = true; } } guard{poisoned};
    U32 id = found;
    if (add) {
      id = source.rows.allocate(account);
      Word* target = source.rows.at(id);
      std::memcpy(target, words, source.arity * sizeof(Word));
      target[source.arity] = pack(1, 0);
      source.index.insert(account, hash, id);
      ++counts.source_rows;
    }
    for (const auto occurrence : source.occurrences) {
      const auto& input = inputs[occurrence];
      if (!input.direct) { route(occurrence, words, row, add, sink); continue; }
      auto& node = nodes[input.node];
      if (add) {
        ++counts.records;
        attach(input.node, id);
        if (survives(node, source.rows.at(id))) survive(input.node, id, true, sink);
      } else {
        if (survives(node, source.rows.at(id))) survive(input.node, id, false, sink);
        detach(input.node, id);
        --counts.records;
      }
    }
    if (!add) {
      source.index.erase(hash, id);
      source.rows.release(id);
      --counts.source_rows;
    }
    guard.done = true;
    return true;
  }
  // Lookahead for a batch. Stage 0 starts the loads of the directory slots an
  // update will probe, stage 1 follows them to the separator and source rows,
  // stage 2 follows the rows to their arrays, and stage 3 follows an expected
  // support change to the parent's records. Nothing here changes state or
  // is relied upon: a stale guess only costs the load it started. The stages
  // select addresses instead of branching, because whether a key exists yet
  // is not predictable.
  static constexpr std::size_t max_probes = 15;
  struct Ahead {
    std::array<Word, 1 + max_probes> hash;
    std::array<U32, max_probes> at;
  };
  inline static const std::array<Word, max_fields + 8> absent = [] {
    std::array<Word, max_fields + 8> words;
    words.fill(~Word{0});   // Every list head reads as "no block".
    return words;
  }();
  void lookahead(const Update& update, Ahead& ahead, int stage) const noexcept {
    if (update.table.value >= sources.size()) return;
    const auto& source = sources[update.table.value];
    const auto count = std::min(source.probes.size(), max_probes);
    if (stage == 0) {
      ahead.hash[0] = hash_words(update.row, source.arity);
      source.index.prefetch(ahead.hash[0]);
      for (std::size_t i = 0; i < count; ++i) {
        const auto& probe = source.probes[i];
        std::array<Word, max_fields> key;
        project(update.row, probe.key, key.data());
        ahead.hash[1 + i] = hash_words(key.data(), probe.key.size());
        groups[probe.group].index.prefetch(ahead.hash[1 + i]);
      }
      return;
    }
    if (stage == 1) {
      const auto row = source.index.peek(ahead.hash[0]);
      const Word* words = row != nil ? source.rows.at(row) : absent.data();
      __builtin_prefetch(words, 1, 3);
      __builtin_prefetch(words + (row != nil ? source.rows.stride - 1 : 0), 1, 3);
      for (std::size_t i = 0; i < count; ++i) {
        const auto& group = groups[source.probes[i].group];
        const auto at = group.index.peek(ahead.hash[1 + i]);
        ahead.at[i] = at;
        const Word* row = at != nil ? group.entries.at(at) : absent.data();
        __builtin_prefetch(row, 1, 3);
        __builtin_prefetch(row + (at != nil ? group.entries.stride - 1 : 0), 1, 3);
      }
      return;
    }
    for (std::size_t i = 0; i < count; ++i) {
      const auto& probe = source.probes[i];
      if (ahead.at[i] == nil) continue;
      const Word* words = groups[probe.group].entries.at(ahead.at[i]);
      if (stage == 2) {
        for (const auto id : probe.edges) {
          const auto& edge = edges[id];
          for (std::size_t k = 0; k < edge.list_count; ++k) {
            const auto& list = *edge.lists[k];
            const Word head = words[list.word];
            // Integer arithmetic: for "no block" the address is never formed as a pointer.
            const auto tail = reinterpret_cast<std::uintptr_t>(pool.words.data()) +
                (static_cast<std::uintptr_t>(low(head)) + static_cast<std::uintptr_t>(high(head)) * list.stride) * sizeof(Word);
            __builtin_prefetch(low(head) != nil ? reinterpret_cast<const void*>(tail) : static_cast<const void*>(absent.data()), 1, 3);
          }
        }
        continue;
      }
      // Stage 3: where this update will make the child's support for the key
      // appear or disappear, the parent's records with that key are next.
      const U32 turning = update.operation == SetOperation::insert ? 0 : 1;
      for (const auto id : probe.crossing) {
        const auto& edge = edges[id];
        const Word head = words[edge.rev.word];
        if (low(words[edge.w_count]) != turning || low(head) == nil) continue;
        const Word* base = pool.at(low(head));
        const auto& store = *nodes[edge.parent].store;
        const std::size_t members = std::min<std::size_t>(high(head), 4);
        for (std::size_t k = 0; k < members; ++k) {
          const U32 member = low(base[k * edge.rev.stride]);
          if (member >= store.high_water) continue;
          const Word* row = store.at(member);
          __builtin_prefetch(row, 1, 3);
          __builtin_prefetch(row + store.stride - 1, 1, 3);
        }
      }
    }
  }
  std::size_t apply_batch(std::span<const Update> updates, RowSink* sink) {
    constexpr std::size_t gap = 4, stages = 4, window = 32;
    std::array<Ahead, window> ring;
    std::size_t applied = 0;
    const auto count = updates.size();
    // The lookahead reads rows before their update is applied, so a malformed
    // batch is refused as a whole before anything is read or changed.
    for (const auto& update : updates) {
      require(update.row != nullptr, "batched update has no row");
      validate(update.table, update.operation, update.table.value < sources.size() ? sources[update.table.value].arity : 0);
    }
    for (std::size_t i = 0; i < count + stages * gap; ++i) {
      for (std::size_t stage = 0; stage < stages; ++stage)
        if (i >= stage * gap && i - stage * gap < count)
          lookahead(updates[i - stage * gap], ring[(i - stage * gap) % window], static_cast<int>(stage));
      if (i < stages * gap) continue;
      const auto& update = updates[i - stages * gap];
      if (apply(update.table, update.operation, update.row, nullptr, sink, ring[(i - stages * gap) % window].hash[0])) ++applied;
    }
    return applied;
  }
  void validate(TableId table, SetOperation operation, std::size_t arity) const {
    require(!poisoned, "compact kernel was abandoned by an earlier failure");
    require(table.value < sources.size(), "update names an unknown base table");
    require(arity == sources[table.value].arity, "update row arity differs from its base table");
    require(operation == SetOperation::insert || operation == SetOperation::erase, "unknown set operation");
  }
  void enumerate(RowSink& sink) const {
    require(!poisoned, "compact kernel was abandoned by an earlier failure");
    if (connex_root == nil) { if (root_support != 0) sink.row(nullptr); return; }
    const auto& node = nodes[connex_root];
    for (U32 index = 0; index < node.members->high_water; ++index) {
      const Word* row = node.members->at(index);
      if (low(row[node.v_meta]) != 0 && (!node.identity || survives(node, row))) emit(connex_root, index, sink);
    }
  }

  // ---- Diagnostic --------------------------------------------------------------
  // Rebuilds every derived structure from the live records alone and compares.
  using Key = std::vector<Word>;
  [[nodiscard]] static Key key_of(const Word* row, const Fields& fields) {
    Key key(fields.size());
    project(row, fields, key.data());
    return key;
  }
  [[nodiscard]] U32 lookup(const EdgeState& edge, const Key& key) const { return find_entry(edge, key.data(), hash_words(key.data(), edge.arity)); }
  void check() const {
    std::uint64_t source_rows = 0, records = 0, survivors = 0, roots = 0, visible_keys = 0;
    std::vector<std::map<Key, std::uint64_t>> derivations(nodes.size());
    for (std::size_t table = 0; table < sources.size(); ++table) {
      const auto& source = sources[table];
      std::uint64_t live = 0;
      for (U32 index = 0; index < source.rows.high_water; ++index) {
        const Word* row = source.rows.at(index);
        if (low(row[source.arity]) == 0) continue;
        ++live;
        require(source.index.find(hash_words(row, source.arity), [&](U32 other) { return other == index; }) == index, "source row is missing from its index");
        if (adapted) continue;
        for (const auto occurrence : source.occurrences) {
          const auto& input = inputs[occurrence];
          if (input.direct) continue;
          bool passes = true;
          for (const auto& [left, right] : input.equalities) passes = passes && row[left] == row[right];
          for (const auto& [field, value] : input.constants) passes = passes && row[field] == value;
          if (passes) ++derivations[input.node][key_of(row, input.fields)];
        }
      }
      require(live == source.rows.live && live == source.index.used, "source census differs");
      source_rows += live;
    }
    std::vector<std::vector<U32>> live(nodes.size()), alive(nodes.size());
    std::vector<std::map<Key, std::uint64_t>> support(edges.size()), visible(nodes.size());
    std::vector<std::map<Key, std::vector<U32>>> holders(edges.size()), below(edges.size()), above(edges.size());
    for (std::size_t id = 0; id < nodes.size(); ++id) {
      const auto& node = nodes[id];
      for (U32 index = 0; index < node.store->high_water; ++index) {
        const Word* row = node.store->at(index);
        if (low(row[node.meta]) == 0) continue;
        live[id].push_back(index);
        if (node.direct) continue;
        if (node.kind != NodeKind::native) { require(row[node.w_mask] != 0, "generalized candidate has no supplier"); continue; }
        require(node.record_index.find(hash_words(row, node.arity), [&](U32 other) { return other == index; }) == index, "record is missing from its index");
        require(high(row[node.meta]) != 0, "record has no derivation");
        if (adapted) continue;
        const auto expected = derivations[id].find(Key(row, row + node.arity));
        require(expected != derivations[id].end() && expected->second == high(row[node.meta]), "derivation count differs from the source rows");
      }
      if (!node.direct) {
        require(live[id].size() == node.own.live, "record census differs from its slab");
        if (node.kind == NodeKind::native) {
          require(live[id].size() == node.record_index.used, "record index population differs");
          if (!adapted) require(live[id].size() == derivations[id].size(), "record census differs from the source rows");
        }
      }
      records += live[id].size();
      for (const auto index : live[id]) {
        const Word* row = node.store->at(index);
        for (std::size_t slot = 0; slot < node.children; ++slot)
          holders[node.child_edges[slot]][key_of(row, edges[node.child_edges[slot]].parent_fields)].push_back(index);
        if (!survives(node, row)) continue;
        alive[id].push_back(index);
        ++survivors;
        if (node.parent_edge == nil) ++roots;
        else ++support[node.parent_edge][key_of(row, node.separator)];
        if (node.connex && !node.identity) ++visible[id][key_of(row, node.visible_fields)];
      }
    }
    require(source_rows == counts.source_rows && records == counts.records && survivors == counts.survivors && roots == root_support,
        "record census differs");
    // Record state: child masks, entry ids and array positions.
    for (std::size_t id = 0; id < nodes.size(); ++id) {
      const auto& node = nodes[id];
      for (const auto index : live[id]) {
        const Word* row = node.store->at(index);
        for (std::size_t slot = 0; slot < node.children; ++slot) {
          const auto& edge = edges[node.child_edges[slot]];
          const auto key = key_of(row, edge.parent_fields);
          const auto at = lookup(edge, key);
          require(at != nil && low(row[node.w_child + slot]) == at, "record lost its child separator entry");
          const Word* words = edge.entries->at(at);
          require(((row[node.w_mask] >> slot) & 1U) == (support[node.child_edges[slot]].count(key) ? 1U : 0U), "child presence bit differs from child support");
          const auto position = high(row[node.w_child + slot]);
          require(position < high(words[edge.rev.word]) &&
              low(pool.at(low(words[edge.rev.word]))[static_cast<std::size_t>(position) * edge.rev.stride]) == index, "record position differs from its rev array");
        }
        if (node.parent_edge != nil && survives(node, row))
          require(low(row[node.w_parent]) == lookup(edges[node.parent_edge], key_of(row, node.separator)), "survivor lost its parent separator entry");
      }
    }
    // Visible members and the keys under which the arrays must list them.
    for (std::size_t id = 0; id < nodes.size(); ++id) {
      const auto& node = nodes[id];
      if (!node.connex) continue;
      std::vector<U32> members;
      if (node.identity) members = alive[id];
      else {
        for (U32 index = 0; index < node.visible.high_water; ++index) {
          const Word* row = node.visible.at(index);
          if (low(row[node.v_meta]) == 0) continue;
          members.push_back(index);
          require(node.visible_index.find(hash_words(row, node.visible_arity), [&](U32 other) { return other == index; }) == index,
              "visible member is missing from its index");
          const auto expected = visible[id].find(Key(row, row + node.visible_arity));
          require(expected != visible[id].end() && expected->second == row[node.v_meta], "visible count differs from survivors");
        }
        require(members.size() == visible[id].size() && members.size() == node.visible.live && members.size() == node.visible_index.used,
            "visible census differs");
      }
      visible_keys += members.size();
      for (const auto member : members) {
        const Word* row = node.members->at(member);
        if (node.parent_edge != nil) {
          const auto key = key_of(row, compose(node.visible_separator_raw, node.member_position));
          require(low(row[node.v_parent]) == lookup(edges[node.parent_edge], key), "visible member lost its parent separator entry");
          below[node.parent_edge][key].push_back(member);
        }
        for (std::size_t k = 0; k < node.connex_children.size(); ++k) {
          const auto edge_id = nodes[node.connex_children[k]].parent_edge;
          const auto key = key_of(row, compose(node.visible_child_raw[k], node.member_position));
          require(low(row[node.v_child[k]]) == lookup(edges[edge_id], key), "visible member lost its child separator entry");
          above[edge_id][key].push_back(member);
        }
      }
    }
    require(visible_keys == counts.visible_keys, "visible census differs from its counter");
    // Separator entries and their arrays.
    std::uint64_t entries = 0;
    std::size_t listed_words = 0;
    for (std::size_t id = 0; id < edges.size(); ++id) {
      const auto& edge = edges[id];
      const auto& parent = nodes[edge.parent];
      const auto& child = nodes[edge.child];
      std::uint64_t found_entries = 0, supported = 0, held = 0, lower = 0, upper = 0;
      const auto verify = [&](const List& list, const Word* words, std::size_t length, const std::vector<U32>* wanted, const NodeState& owner,
          std::size_t place_word, const Fields& source, U32 onward_word, U32 at, const char* message) {
        // Elements [0, length) must be exactly `wanted`, each at its stored position.
        std::vector<U32> seen;
        const Word* base = high(words[list.word]) ? pool.at(low(words[list.word])) : nullptr;
        for (std::size_t i = 0; i < length; ++i) {
          const Word* element = base + i * list.stride;
          const U32 member = low(element[0]);
          seen.push_back(member);
          const Word* row = owner.members->at(member);
          require(row[place_word] == pack(at, static_cast<U32>(i)), message);
          require(high(element[0]) == (onward_word == nil ? nil : low(row[onward_word])), "array element carries a stale onward entry");
          for (std::size_t field = 0; field < source.size(); ++field) require(element[1 + field] == row[source[field]], "array element payload differs from its member");
        }
        std::sort(seen.begin(), seen.end());
        auto expected = wanted ? *wanted : std::vector<U32>{};
        std::sort(expected.begin(), expected.end());
        require(seen == expected, message);
      };
      for (std::size_t slot = 0; slot < edge.index->capacity; ++slot) {
        const Word packed = edge.index->slots.data()[slot];
        if (!packed) continue;
        ++found_entries;
        const auto at = low(packed) - 1;
        const Word* words = edge.entries->at(at);
        const Key key(words, words + edge.arity);
        const auto expected = support[id].find(key);
        const std::uint64_t count = low(words[edge.w_count]);
        require(count == (expected == support[id].end() ? 0 : expected->second), "support count differs from survivors");
        if (count) ++supported;
        for (const auto* list : {&edge.rev, &edge.down, &edge.up}) {
          if (!list->present) continue;
          const std::size_t length = high(words[list->word]);
          require((length == 0) == (low(words[list->word]) == nil), "empty array keeps a block or a used one has none");
          if (!length) continue;
          const auto size_class = class_of(words[edge.w_count], *list);
          require(size_class >= list->first && length * list->stride <= (std::size_t{1} << size_class), "array is longer than its block");
          listed_words += std::size_t{1} << size_class;
        }
        // rev: every parent record with this key.
        const auto holding = holders[id].find(key);
        std::vector<U32> listed;
        const std::size_t length = high(words[edge.rev.word]);
        for (std::size_t i = 0; i < length; ++i) listed.push_back(low(pool.at(low(words[edge.rev.word]))[i * edge.rev.stride]));
        std::sort(listed.begin(), listed.end());
        auto wanted = holding == holders[id].end() ? std::vector<U32>{} : holding->second;
        std::sort(wanted.begin(), wanted.end());
        require(listed == wanted, "rev array differs from the parent records");
        if (length) ++held;
        if (parent.kind != NodeKind::native) require(length <= 1, "generalized key has several candidates");
        if (!edge.connex) continue;
        const auto up_members = above[id].find(key);
        const auto down_members = below[id].find(key);
        if (edge.merged) {
          const std::size_t prefix = low(words[edge.w_survivors]);
          require(prefix <= length, "survivor prefix is longer than its array");
          verify(edge.rev, words, prefix, up_members == above[id].end() ? nullptr : &up_members->second, parent,
              parent.v_child[edge.ordinal], edge.up_source, edge.up_onward_word, at, "survivor prefix differs from the parent's visible members");
          for (std::size_t i = 0; i < length; ++i) {
            const Word* element = pool.at(low(words[edge.rev.word])) + i * edge.rev.stride;
            const Word* row = parent.store->at(low(element[0]));
            for (std::size_t field = 0; field < edge.up_source.size(); ++field) require(element[1 + field] == row[edge.up_source[field]], "rev element payload differs from its record");
          }
        } else {
          verify(edge.up, words, high(words[edge.up.word]), up_members == above[id].end() ? nullptr : &up_members->second, parent,
              parent.v_child[edge.ordinal], edge.up_source, edge.up_onward_word, at, "up array differs from the parent's visible members");
        }
        verify(edge.down, words, high(words[edge.down.word]), down_members == below[id].end() ? nullptr : &down_members->second, child,
            child.v_parent, edge.down_source, edge.down_onward_word, at, "down array differs from the child's visible members");
        if (up_members != above[id].end()) ++upper;
        if (down_members != below[id].end()) ++lower;
      }
      require(found_entries == edge.entries->live && found_entries == edge.index->used, "separator census differs from its slab");
      require(supported == support[id].size() && held == holders[id].size() && upper == above[id].size() && lower == below[id].size(),
          "a separator key has no entry");
    }
    for (const auto& group : groups) {
      for (std::size_t slot = 0; slot < group.index.capacity; ++slot) {
        const Word packed = group.index.slots.data()[slot];
        if (!packed) continue;
        ++entries;
        const Word* words = group.entries.at(low(packed) - 1);
        bool empty = true;
        for (const auto member : group.edges) {
          const auto& peer = edges[member];
          empty = empty && low(words[peer.w_count]) == 0;
          for (std::size_t k = 0; k < peer.list_count; ++k) empty = empty && high(words[peer.lists[k]->word]) == 0;
        }
        require(!empty, "empty separator row was retained");
      }
    }
    require(entries == counts.separator_keys, "key census differs");
    std::size_t free_words = 0;
    for (unsigned size_class = 0; size_class < Pool::classes; ++size_class)
      for (U32 block = pool.free_head[size_class]; block != nil; block = low(pool.words.data()[block])) {
        free_words += std::size_t{1} << size_class;
        require(free_words <= pool.high_water, "list pool free lists are corrupt");
      }
    require(listed_words + free_words == pool.high_water, "list pool lost or shares a block");
    account.check_invariants();
  }
};

Runtime::Runtime(const PhysicalPlan& plan, Options options) : impl_(std::make_unique<Impl>(plan, options)) {}
Runtime::~Runtime() = default;
Runtime::Runtime(Runtime&&) noexcept = default;
Runtime& Runtime::operator=(Runtime&&) noexcept = default;
bool Runtime::apply(TableId table, SetOperation operation, const Row& row, RowSink* delta) {
  impl_->validate(table, operation, row.size());
  std::array<Word, max_fields> words;
  for (std::size_t i = 0; i < row.size(); ++i) words[i] = impl_->encode(row[i]);
  return impl_->apply(table, operation, words.data(), &row, delta, hash_words(words.data(), row.size()));
}
bool Runtime::apply(TableId table, SetOperation operation, std::span<const Word> words, RowSink* delta) {
  impl_->validate(table, operation, words.size());
  require(!impl_->adapted, "an adapted plan needs the original row values");
  return impl_->apply(table, operation, words.data(), nullptr, delta, hash_words(words.data(), words.size()));
}
std::size_t Runtime::apply(std::span<const Update> updates, RowSink* delta) {
  require(!impl_->adapted, "an adapted plan needs the original row values");
  return impl_->apply_batch(updates, delta);
}
Word Runtime::encode(const Value& value) { return impl_->encode(value); }
void Runtime::enumerate(RowSink& sink) const { impl_->enumerate(sink); }
bool Runtime::has_answer() const { return impl_->root_support != 0; }
std::size_t Runtime::result_arity() const { return impl_->result_types.size(); }
Row Runtime::decode(const Word* words) const {
  Row result;
  result.reserve(impl_->result_types.size());
  for (std::size_t i = 0; i < impl_->result_types.size(); ++i) {
    switch (impl_->result_types[i]) {
      case ScalarType::int64: result.emplace_back(static_cast<std::int64_t>(words[i])); break;
      case ScalarType::boolean: result.emplace_back(words[i] != 0); break;
      default:
        require(words[i] < impl_->values.size(), "result word is not a dictionary value");
        result.push_back(impl_->values[static_cast<std::size_t>(words[i])]);
    }
  }
  return result;
}
Statistics Runtime::statistics() const { return impl_->counts; }
resource::MemoryStatistics Runtime::memory_statistics() const { return impl_->account.statistics(); }
void Runtime::check_invariants() const { impl_->check(); }

}  // namespace crown::runtime::compact
