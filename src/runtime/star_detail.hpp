#pragma once

#include "crown/runtime/star.hpp"
#include "star_hindex.hpp"
#include "crown/api/error.hpp"
#include <array>
#include <cstring>
#include <map>
#include <set>
#include <type_traits>
#include <variant>

namespace crown::runtime::star::detail {
inline constexpr resource::MemoryAttribution memory{resource::MemoryOwnerKind::support_node, 0};
template<class T> using Vector = std::vector<T, resource::MemoryAllocator<T>>;
template<class T> auto allocator(const resource::MemoryAccount& account,
    resource::MemoryPurpose purpose = resource::MemoryPurpose::support_metadata) {
  return resource::MemoryAllocator<T>(account, purpose, memory);
}
inline void require(bool value, const char* message) {
  if (!value) throw Error("star_invariant", message);
}
struct Budget {
  Metrics& metrics;
  std::uint64_t limit;
  void take() {
    if (metrics.work == limit) throw Error("star_work_limit", "star work grant exhausted");
    ++metrics.work;
  }
};
struct RowLess {
  using is_transparent = void;
  bool operator()(const storage::AccountedRow& a, const storage::AccountedRow& b) const noexcept { return a.view() < b.view(); }
  bool operator()(const storage::AccountedRow& a, storage::RowView b) const noexcept { return a.view() < b; }
  bool operator()(storage::RowView a, const storage::AccountedRow& b) const noexcept { return a < b.view(); }
};
template<class T> using Set = std::set<T*, std::less<T*>, resource::MemoryAllocator<T*>>;
template<class T> Set<T> set(const resource::MemoryAccount& account) {
  return Set<T>(std::less<T*>{}, allocator<T*>(account));
}
template<class V> using Rows = std::map<storage::AccountedRow, V, RowLess,
    resource::MemoryAllocator<std::pair<const storage::AccountedRow, V>>>;
template<class V> Rows<V> rows(const resource::MemoryAccount& account) {
  return Rows<V>(RowLess{}, allocator<std::pair<const storage::AccountedRow, V>>(account));
}
struct Fact;
struct Key;
struct Group;
using Facts = Rows<Fact>;
using Keys = Rows<Key>;
using Groups = Rows<Group>;
using Projections = Rows<std::uint64_t>;
struct Fact {
  const storage::AccountedRow* values = nullptr; // Own map key, stable until journal retirement.
  Vector<Key*> keys;
  std::size_t missing = 0;
  Group* group = nullptr;
  Fact(const resource::MemoryAccount& account, std::size_t dimension)
      : keys(dimension, nullptr, allocator<Key*>(account)) {}
};
struct Key {
  const storage::AccountedRow* values = nullptr; // One typed cell in the owning key map.
  std::uint64_t degree = 0;
  bool heavy = false, present;
  Key* previous = nullptr;
  Key* next = nullptr;
  Set<Fact> facts;
  Set<Group> groups;
  Key(const resource::MemoryAccount& account, bool source_present)
      : present(source_present), facts(set<Fact>(account)), groups(set<Group>(account)) {}
};
struct Group {
  const storage::AccountedRow* identity = nullptr;
  Vector<Key*> heavy;
  Projections projections;
  std::uint64_t supports = 0;
  std::size_t missing = 0;
  Group(const resource::MemoryAccount& account, std::span<Key* const> keys)
      : heavy(keys.begin(), keys.end(), allocator<Key*>(account)), projections(rows<std::uint64_t>(account)) {
    for (const auto* key : heavy) missing += !key->present;
  }
};
// The degree directory owns only one head/count per OCCUPIED positive degree.
// Key records carry the intrusive links. It can enumerate a threshold interval
// without scanning all source keys or enormous unchanged heavy row buckets.
struct Bucket { Key* head = nullptr; std::uint64_t count = 0; };
using Buckets = std::map<std::uint64_t, Bucket, std::less<std::uint64_t>,
    resource::MemoryAllocator<std::pair<const std::uint64_t, Bucket>>>;
struct Dimension {
  Keys keys;
  Buckets buckets;
  Set<Key> heavy;
  HIndex h;
  std::uint64_t scale = 1;
  std::optional<std::uint64_t> threshold;
  bool satellite;
  Dimension(const resource::MemoryAccount& account, std::size_t d, bool real_satellite)
      : keys(rows<Key>(account)), buckets(std::less<std::uint64_t>{},
            allocator<std::pair<const std::uint64_t, Bucket>>(account)),
        heavy(set<Key>(account)), h(account, d), threshold(HIndex::power(2, d - 1)), satellite(real_satellite) {}
  Dimension(Dimension&&) noexcept = default;
  Dimension(const Dimension&) = delete;
};

// One inverse journal covers only touched view records. Detached map nodes keep
// erased payloads alive; insertion undo retains a stable key/value pointer and
// reacquires its iterator after reverse reinsertion. Scalar edits are
// restricted to small trivially copyable counters/links. No virtual undo object,
// per-edit heap allocation, retry layer or full-state copy is needed.
struct ScalarUndo {
  void* target;
  std::array<std::byte, 16> old{};
  std::size_t bytes;
  void rollback() noexcept { std::memcpy(target, old.data(), bytes); }
};
template<class C> struct EditUndo {
  C* container;
  const typename C::value_type* inserted;
  typename C::node_type removed;
  bool insertion;
  void rollback() noexcept {
    if (insertion) {
      // Later extraction undo has restored this exact node. Its pointers are
      // usable again, but extraction permanently invalidated old iterators.
      if constexpr (requires { typename C::mapped_type; })
        container->erase(container->find(inserted->first));
      else container->erase(container->find(*inserted));
    } else container->insert(std::move(removed));
  }
};
using Undo = std::variant<ScalarUndo, EditUndo<Facts>, EditUndo<Keys>, EditUndo<Groups>,
    EditUndo<Projections>, EditUndo<Buckets>, EditUndo<Set<Fact>>, EditUndo<Set<Key>>, EditUndo<Set<Group>>>;
static_assert(std::is_nothrow_move_constructible_v<Undo>);
class Journal {
 public:
  Journal(const resource::MemoryAccount& account, Budget& budget)
      : entries_(allocator<Undo>(account, resource::MemoryPurpose::journal_undo)), budget_(budget) {}
  ~Journal() {
    if (active_) for (auto it = entries_.rbegin(); it != entries_.rend(); ++it)
      std::visit([](auto& value) noexcept { value.rollback(); }, *it);
  }
  Journal(const Journal&) = delete;
  Journal& operator=(const Journal&) = delete;
  void commit() noexcept { active_ = false; }
  template<class T> void assign(T& target, T value) {
    static_assert(std::is_trivially_copyable_v<T> && sizeof(T) <= 16);
    if (target == value) return;
    prepare();
    ScalarUndo undo{&target, {}, sizeof(T)};
    std::memcpy(undo.old.data(), &target, sizeof(T));
    entries_.emplace_back(undo);
    target = value;
  }
  template<class C, class... Args> typename C::iterator emplace(C& container, Args&&... args) {
    // Prepare both node and journal capacity before the no-fail insertion.
    C pending(container.key_comp(), container.get_allocator());
    auto staged = pending.emplace(std::forward<Args>(args)...).first;
    auto node = pending.extract(staged);
    prepare();
    auto inserted = container.insert(std::move(node));
    require(inserted.inserted, "duplicate private index insertion");
    entries_.emplace_back(EditUndo<C>{&container, &*inserted.position, {}, true});
    return inserted.position;
  }
  template<class C> void erase(C& container, typename C::iterator position) {
    require(position != container.end(), "missing private index removal");
    prepare();
    auto node = container.extract(position);
    entries_.emplace_back(EditUndo<C>{&container, {}, std::move(node), false});
  }
 private:
  void prepare() {
    budget_.take();
    if (entries_.size() == entries_.capacity()) {
      const auto old = entries_.capacity();
      if (old > SIZE_MAX / 2) throw Error("star_overflow", "star journal capacity overflow");
      entries_.reserve(old ? 2 * old : 16);
    }
  }
  Vector<Undo> entries_;
  Budget& budget_;
  bool active_ = true;
};

// Borrowed scalar/pointer buffers are reused across all rows of one input.
// Every retained map key imports its own compact payload before reuse.
struct Scratch {
  Vector<storage::ScalarView> group, head;
  Vector<Key*> heavy;
  Scratch(const resource::MemoryAccount& account, std::size_t d, std::size_t width)
      : group(allocator<storage::ScalarView>(account, resource::MemoryPurpose::scratch)),
        head(allocator<storage::ScalarView>(account, resource::MemoryPurpose::scratch)),
        heavy(allocator<Key*>(account, resource::MemoryPurpose::scratch)) {
    if (d > SIZE_MAX / 2) throw Error("star_overflow", "star group arity overflow");
    group.reserve(2 * d); head.reserve(width); heavy.reserve(d);
  }
};
} // namespace crown::runtime::star::detail

namespace crown::runtime::star {
struct Runtime::Data {
  resource::MemoryAccount account;
  CompiledProgram program;
  PhysicalRuntime sources;
  std::uint64_t work_limit;
  TableId center;
  detail::Vector<detail::Dimension> dimensions;
  detail::Vector<std::optional<std::size_t>> routes;
  detail::Vector<FieldId> head;
  detail::Vector<std::uint8_t> free;
  detail::Facts facts;
  detail::Groups groups;
  detail::Set<detail::Group> live;
  std::uint64_t readers = 0;
  bool updating = false;
  Data(PhysicalRuntime, const planner::star::Plan&, std::uint64_t, storage::IndexWork);
  void readable() const;
  [[nodiscard]] storage::RowView head_key(const detail::Fact&, detail::Scratch&) const;
  [[nodiscard]] storage::RowView group_key(const detail::Fact&, detail::Scratch&) const;
  void attach(detail::Fact&, detail::Journal&, detail::Budget&, detail::Scratch&);
  void detach(detail::Fact&, detail::Journal&, detail::Budget&, detail::Scratch&);
  void degree(detail::Dimension&, detail::Key&, std::uint64_t, detail::Journal&, detail::Budget&);
  void relabel(detail::Dimension&, detail::Key&, bool, detail::Journal&, detail::Budget&, detail::Scratch&);
  void rebalance(detail::Dimension&, detail::Key&, std::uint64_t, detail::Journal&, detail::Budget&, detail::Scratch&);
  void satellite(std::size_t, storage::RowView, bool, detail::Journal&, detail::Budget&, detail::Scratch&);
  void center_change(storage::RowView, bool, detail::Journal&, detail::Budget&, detail::Scratch&,
      detail::Vector<detail::HIndex::Prepared>&);
};
} // namespace crown::runtime::star
