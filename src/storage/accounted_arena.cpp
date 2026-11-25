#include "crown/storage/accounted_arena.hpp"

#include "arena_owner.hpp"
#include "crown/resource/ownership.hpp"
#include <limits>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

namespace crown::storage {
namespace {
constexpr auto none = std::numeric_limits<std::size_t>::max();
constexpr auto last_generation = std::numeric_limits<std::uint64_t>::max();
[[noreturn, gnu::cold, gnu::noinline]] void fail(ArenaProblem issue) { throw ArenaValidationFailure(issue); }
inline void require(bool value, ArenaProblem issue = ArenaProblem::invariant) {
  if (!value) [[unlikely]] fail(issue);
}
void add(resource::MemoryUsage& to, resource::MemoryUsage value) noexcept {
  // Disjoint actual blocks of this account; their sum is already admitted.
  to.allocations += value.allocations;
  to.requested_bytes += value.requested_bytes;
  to.payload_bytes += value.payload_bytes;
}
}

std::string_view ArenaValidationFailure::code() const noexcept {
  switch (issue_) {
    case ArenaProblem::invalid_arena: return "invalid_arena";
    case ArenaProblem::invalid_pin: return "invalid_pin";
    case ArenaProblem::foreign_handle: return "foreign_handle";
    case ArenaProblem::stale_handle: return "stale_handle";
    case ArenaProblem::layout_mismatch: return "layout_mismatch";
    case ArenaProblem::invariant: return "arena_contract";
  }
  return "arena_contract";
}
const char* ArenaValidationFailure::what() const noexcept {
  switch (issue_) {
    case ArenaProblem::invalid_arena: return "empty or moved-from accounted arena";
    case ArenaProblem::invalid_pin: return "empty or moved-from accounted arena pin";
    case ArenaProblem::foreign_handle: return "tuple handle belongs to another arena owner";
    case ArenaProblem::stale_handle: return "tuple arena handle is no longer live";
    case ArenaProblem::layout_mismatch: return "tuple belongs to another immutable layout token";
    case ArenaProblem::invariant: return "accounted arena invariant differs";
  }
  return "invalid accounted arena state";
}

struct AccountedTupleArena::State {
  struct Slot {
    std::optional<AccountedTuple> tuple;
    std::uint64_t generation = 1;
    std::size_t pins = 0;
    std::size_t next_free = none, previous_live = none, next_live = none;
    bool live = false;
    explicit Slot(AccountedTuple value) noexcept : tuple(std::move(value)) {}
  };
  // A slot's address never moves. Only this block handle moves during directory
  // growth, and every constructed Slot is destroyed before its block is freed.
  struct SlotOwner {
    resource::MemoryBlock block;
    explicit SlotOwner(resource::MemoryBlock value) noexcept : block(std::move(value)) {}
    SlotOwner(const SlotOwner&) = delete;
    SlotOwner& operator=(const SlotOwner&) = delete;
    SlotOwner(SlotOwner&& other) noexcept : block(std::move(other.block)) {}
    SlotOwner& operator=(SlotOwner&& other) noexcept {
      if (this != &other) { reset();block = std::move(other.block); }
      return *this;
    }
    ~SlotOwner() { reset(); }
    [[nodiscard]] Slot* operator->() noexcept { return static_cast<Slot*>(block.data()); }
    [[nodiscard]] const Slot* operator->() const noexcept { return static_cast<const Slot*>(block.data()); }
    [[nodiscard]] Slot& operator*() noexcept { return *operator->(); }
    [[nodiscard]] const Slot& operator*() const noexcept { return *operator->(); }
    void reset() noexcept {
      if (block) { std::destroy_at(operator->());block.reset(); }
    }
  };
  static_assert(std::is_nothrow_move_constructible_v<SlotOwner>);
  resource::MemoryAccount account;
  AccountedLayout layout;
  ArenaOwnerId owner;
  resource::MemoryAttribution attribution;
  std::vector<SlotOwner, resource::MemoryAllocator<SlotOwner>> slots;
  std::size_t free_head = none, live_head = none;
  ArenaStatistics counts;
  State(resource::MemoryAccount value, AccountedLayout descriptor, ArenaOwnerId id) noexcept
      : account(std::move(value)), layout(std::move(descriptor)), owner(id),
        attribution{resource::MemoryOwnerKind::tuple_arena, id.value},
        slots(resource::MemoryAllocator<SlotOwner>(account, resource::MemoryPurpose::directory, attribution)) {}
  State(const State&) = delete;
  State& operator=(const State&) = delete;
  void owned(ArenaHandle handle) const {
    require(handle.owner == owner, ArenaProblem::foreign_handle);
  }
  [[nodiscard]] bool contains(ArenaHandle handle) const {
    owned(handle);
    return handle.slot.value < slots.size() && slots[handle.slot.value]->live &&
        slots[handle.slot.value]->generation == handle.generation;
  }
  [[nodiscard]] Slot& live(ArenaHandle handle) {
    require(contains(handle), ArenaProblem::stale_handle);
    return *slots[handle.slot.value];
  }
  void classify_slot(std::size_t position, resource::AllocationLifetime lifetime) noexcept {
    slots[position].block.set_lifetime(lifetime);
    if (slots[position]->tuple) AccountedTupleArena::classify(*slots[position]->tuple, lifetime);
  }
  void link_live(std::size_t position, Slot& slot) noexcept {
    classify_slot(position, resource::AllocationLifetime::active);
    slot.live = true;slot.previous_live = none;slot.next_live = live_head;
    if (live_head != none) slots[live_head]->previous_live = position;
    live_head = position;++counts.live_records;
  }
  void reclaim(std::size_t position, Slot& slot) noexcept {
    slot.tuple.reset();
    if (slot.generation == last_generation) {
      // Exhausted metadata is reserved but cannot rejoin the reusable pool.
      slots[position].block.set_lifetime(resource::AllocationLifetime::active);
      ++counts.exhausted_slots;
    } else {
      slots[position].block.set_lifetime(resource::AllocationLifetime::free_pool);
      slot.next_free = free_head;free_head = position;++counts.free_slots;
    }
  }
  void erase(std::size_t position, Slot& slot) noexcept {
    if (slot.previous_live == none) live_head = slot.next_live;
    else slots[slot.previous_live]->next_live = slot.next_live;
    if (slot.next_live != none) slots[slot.next_live]->previous_live = slot.previous_live;
    slot.previous_live = slot.next_live = none;slot.live = false;--counts.live_records;
    if (slot.pins != 0) {
      ++counts.retained_records;classify_slot(position, resource::AllocationLifetime::retained);
    } else reclaim(position, slot);
  }
  void clear() noexcept {
    while (live_head != none) erase(live_head, *slots[live_head]);
  }
  void unpin(ArenaHandle handle) noexcept {
    auto& slot = *slots[handle.slot.value];--slot.pins;--counts.pins;
    if (!slot.live && slot.pins == 0) { --counts.retained_records;reclaim(handle.slot.value, slot); }
  }
};

AccountedTupleArena::AccountedTupleArena(AccountedLayout layout) {
  require(bool(layout), ArenaProblem::layout_mismatch);
  auto account = layout.query_account();
  const auto owner = detail::try_new_arena_owner();
  if (!owner) throw resource::MemoryFailure(resource::MemoryFault::overflow);
  const resource::MemoryAttribution attribution{resource::MemoryOwnerKind::tuple_arena, owner->value};
  state_ = resource::make_accounted_shared<State>(attribution, account, resource::MemoryPurpose::table_state,
      account, std::move(layout), *owner);
}
AccountedTupleArena::~AccountedTupleArena() { if (state_) state_->clear(); }
AccountedTupleArena::AccountedTupleArena(AccountedTupleArena&&) noexcept = default;
AccountedTupleArena& AccountedTupleArena::operator=(AccountedTupleArena&& other) noexcept {
  if (this != &other) { if (state_) state_->clear();state_ = std::move(other.state_); }
  return *this;
}
AccountedTupleArena::State& AccountedTupleArena::state() const {
  require(bool(state_), ArenaProblem::invalid_arena);return *state_;
}
void AccountedTupleArena::classify(AccountedTuple& tuple, resource::AllocationLifetime lifetime) noexcept {
  tuple.set_lifetime(lifetime);
}
ArenaOwnerId AccountedTupleArena::owner() const { return state().owner; }
resource::MemoryAttribution AccountedTupleArena::attribution() const { return state().attribution; }
const AccountedLayout& AccountedTupleArena::layout() const & { return state().layout; }
ArenaStatistics AccountedTupleArena::statistics() const { return state().counts; }
resource::MemoryStatistics AccountedTupleArena::account_statistics() const { return state().account.statistics(); }
// Explicit diagnostic: the attribution query scans the whole account ledger,
// then this report visits all high-water slots, including retained/free slots.
ArenaMemoryStatistics AccountedTupleArena::memory_statistics() const {
  const auto& s = state();
  ArenaMemoryStatistics result;
  result.records = s.counts;result.owner = s.account.statistics_for(s.attribution);
  result.state_control = result.owner.by_purpose[static_cast<std::size_t>(resource::MemoryPurpose::table_state)];
  result.directory = s.slots.get_allocator().allocation_usage(s.slots.data(), s.slots.capacity());
  result.directory_capacity = s.slots.capacity();
  result.directory_spare_payload_bytes = static_cast<std::uint64_t>((s.slots.capacity() - s.slots.size()) * sizeof(State::SlotOwner));
  for (const auto& allocation : s.slots) {
    const auto& slot = *allocation;
    const auto usage = allocation.block.usage();
    if (slot.live) {
      add(result.live_slots, usage);add(result.live_values, slot.tuple->memory_usage());
    } else if (slot.tuple) {
      add(result.retained_slots, usage);add(result.retained_values, slot.tuple->memory_usage());
    } else if (slot.generation == last_generation) add(result.exhausted_slots, usage);
    else add(result.free_slots, usage);
  }
  return result;
}
ArenaHandle AccountedTupleArena::insert(const AccountedTuple& tuple) {
  auto& s = state();require(s.layout.same_token(tuple.layout()), ArenaProblem::layout_mismatch);
  std::size_t position;
  if (s.free_head != none) {
    position = s.free_head;auto& slot = *s.slots[position];
    auto copy = s.layout.tuple(tuple.values(), s.attribution);
    slot.tuple.emplace(std::move(copy));++slot.generation;
    s.free_head = slot.next_free;slot.next_free = none;--s.counts.free_slots;
    s.link_live(position, slot);
  } else {
    if (s.slots.size() == none || s.slots.size() == s.slots.max_size())
      throw resource::MemoryFailure(resource::MemoryFault::overflow);
    position = s.slots.size();
    auto block = s.account.allocate(sizeof(State::Slot), alignof(State::Slot), resource::MemoryPurpose::arena_slot, s.attribution);
    std::construct_at(static_cast<State::Slot*>(block.data()), s.layout.tuple(tuple.values(), s.attribution));
    State::SlotOwner slot(std::move(block));
    s.slots.push_back(std::move(slot));s.counts.slots = s.slots.size();
    s.link_live(position, *s.slots[position]);
  }
  return {s.owner, TupleSlotId{position}, s.slots[position]->generation};
}
bool AccountedTupleArena::contains(ArenaHandle handle) const { return state().contains(handle); }
const AccountedTuple& AccountedTupleArena::get(ArenaHandle handle) const & { return *state().live(handle).tuple; }
AccountedTupleArena::Pin AccountedTupleArena::pin(ArenaHandle handle) const {
  auto& s = state();auto& slot = s.live(handle);
  if (slot.pins == none || s.counts.pins == none) throw resource::MemoryFailure(resource::MemoryFault::overflow);
  ++slot.pins;++s.counts.pins;return Pin(state_, handle);
}
bool AccountedTupleArena::erase(ArenaHandle handle) {
  auto& s = state();if (!s.contains(handle)) return false;
  s.erase(handle.slot.value, *s.slots[handle.slot.value]);return true;
}
void AccountedTupleArena::clear() { state().clear(); }
void AccountedTupleArena::revive(const Pin& pin) noexcept {
  if (!state_ || state_ != pin.state_ || pin.handle_.slot.value >= state_->slots.size()) std::terminate();
  auto& slot = *state_->slots[pin.handle_.slot.value];
  if (slot.live || slot.pins == 0 || slot.generation != pin.handle_.generation || !slot.tuple) std::terminate();
  --state_->counts.retained_records;state_->link_live(pin.handle_.slot.value, slot);
}
AccountedTupleArena::Pin::Pin(std::shared_ptr<State> state, ArenaHandle handle) noexcept
    : state_(std::move(state)), handle_(handle) {}
AccountedTupleArena::Pin::Pin(Pin&&) noexcept = default;
AccountedTupleArena::Pin& AccountedTupleArena::Pin::operator=(Pin&& other) noexcept {
  if (this != &other) { reset();state_ = std::move(other.state_);handle_ = other.handle_; }
  return *this;
}
AccountedTupleArena::Pin::~Pin() { reset(); }
void AccountedTupleArena::Pin::reset() noexcept {
  if (state_) { state_->unpin(handle_);state_.reset(); }
}
ArenaHandle AccountedTupleArena::Pin::handle() const {
  require(bool(state_), ArenaProblem::invalid_pin);return handle_;
}
const AccountedTuple& AccountedTupleArena::Pin::get() const & {
  static_cast<void>(handle());return *state_->slots[handle_.slot.value]->tuple;
}
bool AccountedTupleArena::Pin::is_live() const { static_cast<void>(handle());return state_->contains(handle_); }

void AccountedTupleArena::check_invariants() const {
  const auto& s = state();ArenaStatistics expected;expected.slots = s.slots.size();
  for (auto position = s.free_head; position != none; position = s.slots[position]->next_free) {
    require(position < s.slots.size() && expected.free_slots < s.slots.size());
    const auto& slot = *s.slots[position];
    require(!slot.live && !slot.tuple && slot.generation < last_generation);++expected.free_slots;
  }
  auto previous = none;
  for (auto position = s.live_head; position != none; position = s.slots[position]->next_live) {
    require(position < s.slots.size() && expected.live_records < s.slots.size());
    const auto& slot = *s.slots[position];
    require(slot.live && slot.previous_live == previous);previous = position;++expected.live_records;
  }
  std::size_t live = 0, free = 0;
  for (const auto& allocation : s.slots) {
    const auto& slot = *allocation;require(slot.generation > 0 && slot.pins <= none - expected.pins);
    expected.pins += slot.pins;
    if (slot.live || slot.pins != 0) {
      require(slot.tuple.has_value() && slot.next_free == none && s.layout.same_token(slot.tuple->layout()) &&
          s.layout.validation_issue(slot.tuple->values()).ok() && slot.tuple->attribution() == s.attribution);
      if (slot.live) ++live;else ++expected.retained_records;
    } else {
      require(!slot.tuple);
      if (slot.generation == last_generation) { require(slot.next_free == none);++expected.exhausted_slots; }
      else ++free;
    }
    if (!slot.live) require(slot.previous_live == none && slot.next_live == none);
  }
  require(live == expected.live_records && free == expected.free_slots && expected == s.counts);
  const auto memory = memory_statistics();
  resource::MemoryUsage total;
  for (const auto usage : {memory.state_control, memory.directory, memory.live_slots, memory.retained_slots,
       memory.free_slots, memory.exhausted_slots, memory.live_values, memory.retained_values}) add(total, usage);
  require(total == memory.owner.current && memory.state_control.allocations == 1 &&
      memory.live_slots.allocations == s.counts.live_records && memory.live_values.allocations == s.counts.live_records &&
      memory.retained_slots.allocations == s.counts.retained_records && memory.retained_values.allocations == s.counts.retained_records &&
      memory.free_slots.allocations == s.counts.free_slots && memory.exhausted_slots.allocations == s.counts.exhausted_slots);
  const auto& lifetimes = memory.owner.by_lifetime;
  resource::MemoryUsage active, retained;
  for (const auto usage : {memory.state_control, memory.directory, memory.live_slots, memory.live_values, memory.exhausted_slots}) add(active, usage);
  add(retained, memory.retained_slots);add(retained, memory.retained_values);
  require(lifetimes[static_cast<std::size_t>(resource::AllocationLifetime::active)] == active &&
      lifetimes[static_cast<std::size_t>(resource::AllocationLifetime::retained)] == retained &&
      lifetimes[static_cast<std::size_t>(resource::AllocationLifetime::free_pool)] == memory.free_slots);
  s.account.check_invariants();
}
}
