#include "crown/storage/arena.hpp"

#include "crown/api/error.hpp"
#include "arena_owner.hpp"
#include <exception>
#include <limits>
#include <utility>

namespace crown::storage {
namespace {
constexpr auto none = std::numeric_limits<std::size_t>::max();
constexpr auto last_generation = std::numeric_limits<std::uint64_t>::max();
ArenaOwnerId new_arena_owner() {
  const auto owner = detail::try_new_arena_owner();
  if (!owner) throw Error("storage_overflow", "arena owner IDs exhausted");
  return *owner;
}
void require(bool value, std::string_view message) {
  if (!value) throw Error("arena_contract", std::string(message));
}
}  // namespace

struct TupleArena::State {
  struct Slot {
    std::optional<Tuple> tuple;
    std::uint64_t generation = 1;
    std::size_t pins = 0;
    std::size_t next_free = none;
    std::size_t previous_live = none, next_live = none;
    bool live = true;
    explicit Slot(const Tuple& value) : tuple(value) {}
  };
  ArenaOwnerId owner = new_arena_owner();
  TupleLayout layout;
  // Individual slot allocation keeps payload addresses stable when the vector
  // grows. Free/live links are intrusive so reclamation never allocates.
  std::vector<std::unique_ptr<Slot>> slots;
  std::size_t free_head = none, live_head = none;
  ArenaStatistics counts;
  explicit State(TupleLayout value) : layout(std::move(value)) { static_cast<void>(layout.id()); }
  State(const State&) = delete;
  State& operator=(const State&) = delete;

  void owned(ArenaHandle handle) const {
    if (handle.owner != owner) throw Error("foreign_handle", "tuple handle belongs to another arena");
  }
  bool contains(ArenaHandle handle) const {
    owned(handle);
    return handle.slot.value < slots.size() && slots[handle.slot.value]->live &&
           slots[handle.slot.value]->generation == handle.generation;
  }
  Slot& live(ArenaHandle handle) const {
    if (!contains(handle)) throw Error("stale_handle", "tuple arena handle is no longer live");
    return *slots[handle.slot.value];
  }
  void link_live(std::size_t position, Slot& slot) noexcept {
    slot.live = true;
    slot.previous_live = none;
    slot.next_live = live_head;
    if (live_head != none) slots[live_head]->previous_live = position;
    live_head = position;
    ++counts.live_records;
  }
  void reclaim(std::size_t position, Slot& slot) noexcept {
    slot.tuple.reset();
    if (slot.generation == last_generation) {
      ++counts.exhausted_slots;
    } else {
      slot.next_free = free_head;
      free_head = position;
      ++counts.free_slots;
    }
  }
  void erase(std::size_t position, Slot& slot) noexcept {
    if (slot.previous_live == none) live_head = slot.next_live;
    else slots[slot.previous_live]->next_live = slot.next_live;
    if (slot.next_live != none) slots[slot.next_live]->previous_live = slot.previous_live;
    slot.previous_live = slot.next_live = none;
    slot.live = false;
    --counts.live_records;
    if (slot.pins != 0) ++counts.retained_records;
    else reclaim(position, slot);
  }
  void clear() noexcept {
    while (live_head != none) erase(live_head, *slots[live_head]);
  }
  void unpin(ArenaHandle handle) noexcept {
    auto& slot = *slots[handle.slot.value];
    --slot.pins;
    --counts.pins;
    if (!slot.live && slot.pins == 0) {
      --counts.retained_records;
      reclaim(handle.slot.value, slot);
    }
  }
};

TupleArena::TupleArena(TupleLayout layout) : state_(std::make_shared<State>(std::move(layout))) {}
TupleArena::~TupleArena() { if (state_) state_->clear(); }
TupleArena::TupleArena(TupleArena&&) noexcept = default;
TupleArena& TupleArena::operator=(TupleArena&& other) noexcept {
  if (this != &other) {
    if (state_) state_->clear();
    state_ = std::move(other.state_);
  }
  return *this;
}
TupleArena::State& TupleArena::state() const {
  if (!state_) throw Error("invalid_arena", "moved-from tuple arena");
  return *state_;
}
ArenaOwnerId TupleArena::owner() const { return state().owner; }
const TupleLayout& TupleArena::layout() const { return state().layout; }
ArenaStatistics TupleArena::statistics() const { return state().counts; }

ArenaHandle TupleArena::insert(const Tuple& tuple) {
  auto& s = state();
  if (!s.layout.same_token(tuple.layout())) throw Error("layout_mismatch", "tuple belongs to another arena layout");
  std::size_t position;
  if (s.free_head != none) {
    position = s.free_head;
    auto& slot = *s.slots[position];
    // Copy first. optional remains disengaged if a value/string allocation
    // fails; generation, free links and all counters are still unchanged.
    slot.tuple.emplace(tuple);
    ++slot.generation;
    s.free_head = slot.next_free;
    slot.next_free = none;
    --s.counts.free_slots;
    s.link_live(position, slot);
  } else {
    if (s.slots.size() == none || s.slots.size() == s.slots.max_size())
      throw Error("storage_overflow", "tuple arena slots exhausted");
    position = s.slots.size();
    // Both payload construction and vector growth precede publication. Slot
    // objects never move; vector reallocation moves only unique_ptr values.
    auto slot = std::make_unique<State::Slot>(tuple);
    s.slots.push_back(std::move(slot));
    ++s.counts.slots;
    s.link_live(position, *s.slots[position]);
  }
  return {s.owner, TupleSlotId{position}, s.slots[position]->generation};
}
bool TupleArena::contains(ArenaHandle handle) const { return state().contains(handle); }
const Tuple& TupleArena::get(ArenaHandle handle) const { return *state().live(handle).tuple; }
TupleArena::Pin TupleArena::pin(ArenaHandle handle) const {
  auto& s = state();
  auto& slot = s.live(handle);
  if (slot.pins == none || s.counts.pins == none) throw Error("storage_overflow", "tuple arena pins exhausted");
  ++slot.pins;
  ++s.counts.pins;
  return Pin(state_, handle);
}
bool TupleArena::erase(ArenaHandle handle) {
  auto& s = state();
  if (!s.contains(handle)) return false;
  s.erase(handle.slot.value, *s.slots[handle.slot.value]);
  return true;
}
void TupleArena::clear() { state().clear(); }
void TupleArena::revive(const Pin& pin) noexcept {
  if (!state_ || state_!=pin.state_ || pin.handle_.slot.value>=state_->slots.size()) std::terminate();
  auto& slot=*state_->slots[pin.handle_.slot.value];
  if (slot.live || slot.pins==0 || slot.generation!=pin.handle_.generation || !slot.tuple) std::terminate();
  --state_->counts.retained_records;
  state_->link_live(pin.handle_.slot.value,slot);
}

TupleArena::Pin::Pin(std::shared_ptr<State> state, ArenaHandle handle) noexcept
    : state_(std::move(state)), handle_(handle) {}
TupleArena::Pin::Pin(Pin&&) noexcept = default;
TupleArena::Pin& TupleArena::Pin::operator=(Pin&& other) noexcept {
  if (this != &other) { reset(); state_ = std::move(other.state_); handle_ = other.handle_; }
  return *this;
}
TupleArena::Pin::~Pin() { reset(); }
// Pin bookkeeping is constant; the final closed-State release can destroy
// all high-water slot metadata after its last retained payload is reclaimed.
void TupleArena::Pin::reset() noexcept {
  if (state_) { state_->unpin(handle_); state_.reset(); }
}
ArenaHandle TupleArena::Pin::handle() const {
  if (!state_) throw Error("invalid_pin", "empty or moved-from tuple pin");
  return handle_;
}
const Tuple& TupleArena::Pin::get() const {
  static_cast<void>(handle());
  return *state_->slots[handle_.slot.value]->tuple;
}
bool TupleArena::Pin::is_live() const {
  static_cast<void>(handle());
  return state_->contains(handle_);
}

// Explicit diagnostic: scans all high-water slots and allocates two visited
// arrays, then validates retained tuples. This is separate from mutation work.
void TupleArena::check_invariants() const {
  const auto& s = state();
  ArenaStatistics expected;
  expected.slots = s.slots.size();
  std::vector<bool> free(s.slots.size(), false), live(s.slots.size(), false);
  for (auto position = s.free_head; position != none; position = s.slots[position]->next_free) {
    require(position < s.slots.size() && !free[position], "invalid/cyclic arena free list");
    free[position] = true;
    ++expected.free_slots;
  }
  auto previous = none;
  for (auto position = s.live_head; position != none; position = s.slots[position]->next_live) {
    require(position < s.slots.size() && !live[position], "invalid/cyclic arena live list");
    require(s.slots[position]->previous_live == previous, "inconsistent arena live links");
    live[position] = true;
    previous = position;
    ++expected.live_records;
  }
  for (std::size_t position = 0; position < s.slots.size(); ++position) {
    const auto& slot = *s.slots[position];
    require(slot.generation > 0, "zero arena generation");
    require(live[position] == slot.live, "arena live list/membership mismatch");
    require(slot.pins <= none - expected.pins, "arena pin count overflow");
    expected.pins += slot.pins;
    if (slot.live || slot.pins != 0) {
      require(slot.tuple.has_value() && !free[position] && slot.next_free == none, "missing or freed live/pinned tuple");
      require(s.layout.same_token(slot.tuple->layout()), "foreign arena tuple layout");
      s.layout.validate_view(slot.tuple->values());
      if (!slot.live) ++expected.retained_records;
    } else {
      require(!slot.tuple.has_value(), "unpinned erased tuple payload retained");
      if (slot.generation == last_generation) {
        require(!free[position] && slot.next_free == none, "exhausted arena slot reused");
        ++expected.exhausted_slots;
      } else require(free[position], "reusable arena slot missing from free list");
    }
    if (!slot.live) require(slot.previous_live == none && slot.next_live == none, "erased tuple remains in live list");
  }
  require(expected == s.counts, "arena counters differ from slots/lists");
}
}  // namespace crown::storage
