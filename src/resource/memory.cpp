#include "crown/resource/memory.hpp"

#include <algorithm>
#include <cstdlib>
#include <atomic>
#include <exception>
#include <limits>
#include <memory>
#include <new>
#include <utility>

namespace crown::resource {
namespace {
static_assert(sizeof(std::size_t) <= sizeof(std::uint64_t));
constexpr auto maximum = std::numeric_limits<std::uint64_t>::max();
std::uint64_t new_owner() {
  static std::atomic<std::uint64_t> last{0};
  auto value = last.load(std::memory_order_relaxed);
  for (;;) {
    if (value == maximum) throw MemoryFailure(MemoryFault::overflow);
    if (last.compare_exchange_weak(value, value + 1, std::memory_order_relaxed)) return value + 1;
  }
}
[[noreturn, gnu::cold, gnu::noinline]] void contract_failure() { throw MemoryFailure(MemoryFault::contract); }
inline void require(bool value, const char* /*source diagnostic*/) {
  if (!value) [[unlikely]] contract_failure();
}
std::size_t purpose_index(MemoryPurpose purpose) {
  const auto value = static_cast<std::size_t>(purpose);
  require(value < memory_purpose_count, "unknown memory purpose");
  return value;
}
std::size_t lifetime_index(AllocationLifetime lifetime) {
  const auto value = static_cast<std::size_t>(lifetime);
  require(value < allocation_lifetime_count, "unknown allocation lifetime");
  return value;
}
void add(MemoryUsage& total, const MemoryUsage& value) noexcept {
  // Every term is a disjoint subset of the already admitted account total.
  total.allocations += value.allocations;
  total.requested_bytes += value.requested_bytes;
  total.payload_bytes += value.payload_bytes;
}
void subtract(MemoryUsage& total, const MemoryUsage& value) noexcept {
  if (total.allocations < value.allocations || total.requested_bytes < value.requested_bytes ||
      total.payload_bytes < value.payload_bytes) std::terminate();
  total.allocations -= value.allocations;
  total.requested_bytes -= value.requested_bytes;
  total.payload_bytes -= value.payload_bytes;
}
// Open-addressing index of live payload start addresses for the purposes that
// set_lifetime_containing() classifies. It resolves an interior address with
// one or two hash probes instead of walking every live block of the account
// (which made each table erase O(live allocations)). Slots hold payload
// addresses; 0 marks empty. Keys hash by 64-byte region: every block header
// exceeds 64 bytes, so live payload starts are more than 64 bytes apart and a
// region holds at most one start. Linear probing with backward-shift deletion
// keeps the table tombstone-free. The index is allocator-internal bookkeeping,
// like the malloc chunk header: its slot table (at most 16 bytes per indexed
// live block at the 1/2 maximum load) comes from libc calloc, is not charged
// to the account, and leaves every account-visible C++ allocation unchanged.
constexpr unsigned region_shift = 6;
class AddressIndex {
 public:
  AddressIndex() noexcept = default;
  AddressIndex(const AddressIndex&) = delete;
  AddressIndex& operator=(const AddressIndex&) = delete;
  ~AddressIndex() { release_slots(slots_, capacity()); }
  // Makes room for one more key. May throw std::bad_alloc, leaving the index
  // unchanged, so callers grow before publishing any other state.
  void reserve_one() {
    if (slots_ && (size_ + 1) * 2 <= capacity()) return;
    const auto old_capacity = capacity();
    const auto new_bits = slots_ ? bits_ + 1 : std::size_t{6};
    const auto new_capacity = std::size_t{1} << new_bits;
    auto* fresh = static_cast<std::uintptr_t*>(std::calloc(new_capacity, sizeof(std::uintptr_t)));
    if (!fresh) throw std::bad_alloc{};
    auto* old = std::exchange(slots_, fresh);
    bits_ = new_bits;
    for (std::size_t i = 0; i < old_capacity; ++i)
      if (old[i]) place(old[i]);
    release_slots(old, old_capacity);
  }
  void insert(std::uintptr_t key) noexcept {
    if (!slots_ || (size_ + 1) * 2 > capacity()) std::terminate();  // reserve_one() precedes insert.
    place(key);
    ++size_;
  }
  void erase(std::uintptr_t key) noexcept {
    if (!slots_) std::terminate();
    const auto mask = capacity() - 1;
    auto hole = home(key >> region_shift);
    while (slots_[hole] != key) {
      if (!slots_[hole]) std::terminate();  // Every indexed live block is present.
      hole = (hole + 1) & mask;
    }
    // Backward-shift deletion: move later members of the probe run into the
    // hole when their home position does not lie cyclically in (hole, next].
    for (auto next = (hole + 1) & mask; slots_[next]; next = (next + 1) & mask) {
      const auto ideal = home(slots_[next] >> region_shift);
      const bool stays = hole <= next ? (hole < ideal && ideal <= next) : (hole < ideal || ideal <= next);
      if (stays) continue;
      slots_[hole] = slots_[next];
      hole = next;
    }
    slots_[hole] = 0;
    --size_;
  }
  [[nodiscard]] std::size_t size() const noexcept { return size_; }
  // The indexed payload start inside one 64-byte region, or 0.
  [[nodiscard]] std::uintptr_t find_region(std::uintptr_t region) const noexcept {
    if (!slots_) return 0;
    const auto mask = capacity() - 1;
    for (auto at = home(region); slots_[at]; at = (at + 1) & mask)
      if ((slots_[at] >> region_shift) == region) return slots_[at];
    return 0;
  }
  [[nodiscard]] bool contains(std::uintptr_t key) const noexcept { return key && find_region(key >> region_shift) == key; }

 private:
  [[nodiscard]] std::size_t capacity() const noexcept { return slots_ ? std::size_t{1} << bits_ : 0; }
  [[nodiscard]] std::size_t home(std::uintptr_t region) const noexcept {
    // Fibonacci hashing of the region number; keep the high bits.
    return static_cast<std::size_t>((static_cast<std::uint64_t>(region) * 0x9E3779B97F4A7C15ull) >> (64 - bits_));
  }
  void place(std::uintptr_t key) noexcept {
    const auto mask = capacity() - 1;
    auto at = home(key >> region_shift);
    while (slots_[at]) at = (at + 1) & mask;
    slots_[at] = key;
  }
  static void release_slots(std::uintptr_t* slots, std::size_t /*count*/) noexcept { std::free(slots); }
  std::uintptr_t* slots_ = nullptr;
  std::size_t bits_ = 0;
  std::size_t size_ = 0;
};
// Purposes whose blocks are classified through interior addresses: table,
// support and source-count container nodes, journal undo records and cursor
// control blocks. Other purposes (tuple values, output, scratch, ...) are the
// bulk of allocations and are resolved by the full scan if ever queried.
constexpr bool indexed_purpose(MemoryPurpose purpose) noexcept {
  switch (purpose) {
    case MemoryPurpose::primary_node: case MemoryPurpose::secondary_node:
    case MemoryPurpose::support_metadata: case MemoryPurpose::source_counts:
    case MemoryPurpose::journal_undo: case MemoryPurpose::cursor: return true;
    default: return false;
  }
}
// Interior addresses passed to set_lifetime_containing() are node values,
// node-handle keys, shared/unique control blocks and vector buffers: all lie a
// few dozen bytes past their payload start. Larger offsets use the full scan.
constexpr std::size_t containing_probe_bytes = 512;
}  // namespace

struct MemoryAccount::Control {
  std::uint64_t references = 1;
  BlockData* first = nullptr;
  bool allocating = false;
  MemoryStatistics statistics;
  AddressIndex payloads;
  Control(std::uint64_t limit, std::uint64_t owner) noexcept {
    statistics.owner = owner;
    statistics.limit_bytes = limit;
    statistics.current = {1, sizeof(Control), 0};
    statistics.peak_requested_bytes = sizeof(Control);
    statistics.successful_allocations = 1;
    statistics.by_purpose[static_cast<std::size_t>(MemoryPurpose::control)] = statistics.current;
    statistics.by_lifetime[static_cast<std::size_t>(AllocationLifetime::active)] = statistics.current;
  }
};
struct MemoryAccount::BlockData {
  Control* owner;
  BlockData* previous;
  BlockData* next;
  void* payload;
  std::size_t payload_size;
  std::size_t raw_size;
  std::size_t alignment;
  MemoryPurpose purpose;
  AllocationLifetime lifetime;
  MemoryAttribution attribution;
  [[nodiscard]] MemoryUsage usage() const noexcept {
    return {1, static_cast<std::uint64_t>(raw_size), static_cast<std::uint64_t>(payload_size)};
  }
};

std::uint64_t MemoryAccount::control_bytes() noexcept { return sizeof(Control); }
std::uint64_t MemoryAccount::allocation_bytes(std::size_t bytes, std::size_t alignment) {
  require(alignment != 0 && (alignment & (alignment - 1)) == 0, "alignment must be a nonzero power of two");
  const auto effective = std::max(alignment, alignof(BlockData*));
  const auto payload = std::max(bytes, std::size_t{1});
  constexpr auto header = sizeof(BlockData) + sizeof(BlockData*);
  constexpr auto largest = std::numeric_limits<std::size_t>::max();
  if (effective - 1 > largest - header || payload > largest - header - (effective - 1))
    throw MemoryFailure(MemoryFault::overflow);
  return static_cast<std::uint64_t>(header + (effective - 1) + payload);
}

MemoryAccount::MemoryAccount(Control* control) noexcept : control_(control) {}
MemoryAccount MemoryAccount::create(std::uint64_t limit) {
  if (limit < control_bytes()) throw MemoryFailure(MemoryFault::limit);
  void* raw = ::operator new(sizeof(Control));
  try {
    return MemoryAccount(std::construct_at(static_cast<Control*>(raw), limit, new_owner()));
  } catch (...) {
    ::operator delete(raw);
    throw;
  }
}
void MemoryAccount::retain(Control* control) noexcept {
  if (!control) return;
  // Reference overflow is an invalid internal lifetime state. Supported RAII
  // handles/blocks each occupy addressable storage; accounting counters below
  // have separate checked limits for unbounded historical churn.
  if (control->references == maximum) std::terminate();
  ++control->references;
}
void MemoryAccount::release(Control* control) noexcept {
  if (!control) return;
  if (control->references == 0) std::terminate();
  if (--control->references != 0) return;
  const auto& current = control->statistics.current;
  if (control->first || current != MemoryUsage{1, sizeof(Control), 0}) std::terminate();
  std::destroy_at(control);
  ::operator delete(control);
}
MemoryAccount::MemoryAccount(const MemoryAccount& other) noexcept : control_(other.control_) { retain(control_); }
MemoryAccount& MemoryAccount::operator=(const MemoryAccount& other) noexcept {
  if (this != &other) { retain(other.control_);release(control_);control_ = other.control_; }
  return *this;
}
MemoryAccount::MemoryAccount(MemoryAccount&& other) noexcept : control_(std::exchange(other.control_, nullptr)) {}
MemoryAccount& MemoryAccount::operator=(MemoryAccount&& other) noexcept {
  if (this != &other) { release(control_);control_ = std::exchange(other.control_, nullptr); }
  return *this;
}
MemoryAccount::~MemoryAccount() { release(control_); }
MemoryAccount::Control& MemoryAccount::required() const {
  require(control_ != nullptr, "empty memory account");
  return *control_;
}
MemoryStatistics MemoryAccount::statistics() const { return required().statistics; }
MemoryUsage MemoryAccount::current_usage() const { return required().statistics.current; }
AttributedMemoryStatistics MemoryAccount::statistics_for(MemoryAttribution attribution) const {
  require(attribution.valid(), "unknown memory attribution");
  const auto& control = required();
  AttributedMemoryStatistics result;
  result.account_owner = control.statistics.owner;
  result.attribution = attribution;
  if (attribution == MemoryAttribution{}) {
    result.current = {1, sizeof(Control), 0};
    result.by_purpose[static_cast<std::size_t>(MemoryPurpose::control)] = result.current;
    result.by_lifetime[static_cast<std::size_t>(AllocationLifetime::active)] = result.current;
  }
  for (const auto* block = control.first; block; block = block->next) {
    if (block->attribution != attribution) continue;
    const auto usage = block->usage();
    add(result.current, usage);
    add(result.by_purpose[static_cast<std::size_t>(block->purpose)], usage);
    add(result.by_lifetime[static_cast<std::size_t>(block->lifetime)], usage);
  }
  return result;
}
// Caller-funded inventory, not a unique-owner registry: several allocations
// can carry the same attribution. No addresses or retained history are exported.
std::size_t MemoryAccount::copy_attributions(std::span<MemoryAttribution> output) const {
  const auto& control=required();
  require(!control.allocating && output.size()>=control.statistics.current.allocations,
      "allocation attribution inventory requires quiescent caller capacity");
  std::size_t used=0;output[used++]={};
  for(const auto* block=control.first;block;block=block->next)output[used++]=block->attribution;
  require(used==control.statistics.current.allocations,"allocation attribution inventory differs from account");
  return used;
}

void MemoryAccount::set_lifetime_containing(const void* address, MemoryPurpose purpose,
    MemoryAttribution attribution, AllocationLifetime lifetime) const {
  auto& control = required();
  require(!control.allocating && address != nullptr && attribution.valid(), "invalid containing allocation lookup");
  static_cast<void>(purpose_index(purpose));
  const auto category = lifetime_index(lifetime);
  const auto value = reinterpret_cast<std::uintptr_t>(address);
  auto classify = [&](BlockData* block) {
    require(block->purpose == purpose && block->attribution == attribution, "containing allocation ownership differs");
    const auto previous = lifetime_index(block->lifetime);
    if (previous != category) {
      subtract(control.statistics.by_lifetime[previous], block->usage());
      add(control.statistics.by_lifetime[category], block->usage());
      block->lifetime = lifetime;
    }
  };
  // Live payloads never overlap, so the nearest indexed start at or below the
  // address is the only indexed block that can contain it. A non-indexed block
  // there has a different purpose and fails the ownership check below too.
  if (indexed_purpose(purpose)) {
    static_assert(sizeof(BlockData) + sizeof(BlockData*) > (std::size_t{1} << region_shift));
    const auto region = value >> region_shift;
    for (std::uintptr_t offset = 0; offset <= (containing_probe_bytes >> region_shift) && offset <= region; ++offset) {
      const auto start = control.payloads.find_region(region - offset);
      if (!start || start > value) continue;
      auto* block = *(reinterpret_cast<BlockData**>(start) - 1);
      if (block->owner != &control || reinterpret_cast<std::uintptr_t>(block->payload) != start) std::terminate();
      if (value - start >= block->payload_size) throw MemoryFailure(MemoryFault::contract);
      classify(block);
      return;
    }
  }
  for (auto* block = control.first; block; block = block->next) {
    const auto start = reinterpret_cast<std::uintptr_t>(block->payload);
    if (value < start || value - start >= block->payload_size) continue;
    classify(block);
    return;
  }
  throw MemoryFailure(MemoryFault::contract);
}

MemoryBlock MemoryAccount::allocate(std::size_t bytes, std::size_t alignment, MemoryPurpose purpose,
                                   MemoryAttribution attribution) const {
  auto& control = required();
  if (control.allocating) throw std::bad_alloc{};
  MemoryAccount keep_alive(*this);
  struct AllocationGuard {
    Control& control;
    explicit AllocationGuard(Control& value) noexcept : control(value) { control.allocating = true; }
    ~AllocationGuard() { control.allocating = false; }
  } guard(control);
  const auto category = purpose_index(purpose);
  require(purpose != MemoryPurpose::control, "controller purpose is reserved");
  require(attribution.valid(), "unknown memory attribution");
  const auto charge = allocation_bytes(bytes, alignment);
  auto& statistics = control.statistics;
  if (charge > statistics.limit_bytes - statistics.current.requested_bytes)
    throw MemoryFailure(MemoryFault::limit);
  if (statistics.successful_allocations == maximum)
    throw MemoryFailure(MemoryFault::overflow);
  static_assert(alignof(BlockData) <= alignof(std::max_align_t));
  const auto raw_size = static_cast<std::size_t>(charge);
  const bool indexed = indexed_purpose(purpose);
  if (indexed) control.payloads.reserve_one();  // Growth failure leaves every account counter unchanged.
  void* raw = ::operator new(raw_size);  // Failure leaves every account counter unchanged.
  auto* block = std::construct_at(static_cast<BlockData*>(raw), BlockData{&control, nullptr, control.first,
      nullptr, bytes, raw_size, alignment, purpose, AllocationLifetime::active, attribution});
  void* payload = static_cast<std::byte*>(raw) + sizeof(BlockData) + sizeof(BlockData*);
  auto space = raw_size - sizeof(BlockData) - sizeof(BlockData*);
  if (!std::align(std::max(alignment, alignof(BlockData*)), std::max(bytes, std::size_t{1}), payload, space))
    std::terminate();
  block->payload = payload;
  std::construct_at(static_cast<BlockData**>(payload) - 1, block);
  if (indexed) control.payloads.insert(reinterpret_cast<std::uintptr_t>(payload));
  retain(&control);  // Every block independently keeps its controller alive.
  if (control.first) control.first->previous = block;
  control.first = block;
  const auto usage = block->usage();
  add(statistics.current, usage);
  add(statistics.by_purpose[category], usage);
  add(statistics.by_lifetime[static_cast<std::size_t>(AllocationLifetime::active)], usage);
  ++statistics.successful_allocations;
  statistics.peak_requested_bytes = std::max(statistics.peak_requested_bytes, statistics.current.requested_bytes);
  return MemoryBlock(block);
}
void* MemoryAccount::allocate_raw(std::size_t bytes, std::size_t alignment, MemoryPurpose purpose,
                                MemoryAttribution attribution) const {
  auto block = allocate(bytes, alignment, purpose, attribution);
  auto* header = std::exchange(block.data_, nullptr);
  // Ownership transfers to the allocator's caller. The header retains the
  // controller independently until the matching deallocation reaches free().
  return header->payload;
}
MemoryUsage MemoryAccount::allocation_usage_raw(const void* pointer, std::size_t bytes, std::size_t alignment,
    MemoryPurpose purpose, MemoryAttribution attribution) const {
  const auto& control = required();
  require(pointer != nullptr, "empty raw allocation lookup");
  // As for allocator deallocation, pointer must name a still-live allocation
  // obtained through this adapter. Arbitrary addresses are not introspectable.
  const auto* block = *(static_cast<BlockData* const*>(pointer) - 1);
  require(block->owner == &control && block->payload == pointer && block->payload_size == bytes &&
      block->alignment == alignment && block->purpose == purpose && block->attribution == attribution,
      "allocator allocation lookup ownership/size mismatch");
  return block->usage();
}
void MemoryAccount::set_lifetime_raw(void* pointer, std::size_t bytes, std::size_t alignment,
    MemoryPurpose purpose, MemoryAttribution attribution, AllocationLifetime lifetime) const {
  const auto destination = lifetime_index(lifetime);
  static_cast<void>(allocation_usage_raw(pointer, bytes, alignment, purpose, attribution));
  auto* block = *(static_cast<BlockData**>(pointer) - 1);
  require(!block->owner->allocating, "allocation classification reentry");
  if (block->lifetime == lifetime) return;
  auto& statistics = block->owner->statistics;
  subtract(statistics.by_lifetime[static_cast<std::size_t>(block->lifetime)], block->usage());
  add(statistics.by_lifetime[destination], block->usage());block->lifetime = lifetime;
}
void MemoryAccount::deallocate_raw(void* pointer, std::size_t bytes, std::size_t alignment,
                                 MemoryPurpose purpose, MemoryAttribution attribution) const noexcept {
  if (!pointer) return;
  auto* block = *(static_cast<BlockData**>(pointer) - 1);
  if (!control_ || block->owner != control_ || block->payload != pointer || block->payload_size != bytes ||
      block->alignment != alignment || block->purpose != purpose || block->attribution != attribution)
    std::terminate();  // Standard allocator ownership/size mismatch is invalid.
  free(block);
}
void MemoryAccount::free(BlockData* block) noexcept {
  if (!block) return;
  auto* control = block->owner;
  if (control->allocating) std::terminate();  // Invalid upstream deallocation reentry.
  if (indexed_purpose(block->purpose)) control->payloads.erase(reinterpret_cast<std::uintptr_t>(block->payload));
  const auto usage = block->usage();
  if (block->previous) block->previous->next = block->next;
  else control->first = block->next;
  if (block->next) block->next->previous = block->previous;
  auto& statistics = control->statistics;
  subtract(statistics.current, usage);
  subtract(statistics.by_purpose[static_cast<std::size_t>(block->purpose)], usage);
  subtract(statistics.by_lifetime[static_cast<std::size_t>(block->lifetime)], usage);
  if (statistics.freed_allocations >= statistics.successful_allocations) std::terminate();
  ++statistics.freed_allocations;
  std::destroy_at(static_cast<BlockData**>(block->payload) - 1);
  std::destroy_at(block);
  ::operator delete(block);
  release(control);
}

MemoryBlock::MemoryBlock(MemoryAccount::BlockData* data) noexcept : data_(data) {}
MemoryBlock::MemoryBlock(MemoryBlock&& other) noexcept : data_(std::exchange(other.data_, nullptr)) {}
MemoryBlock& MemoryBlock::operator=(MemoryBlock&& other) noexcept {
  if (this != &other) { reset();data_ = std::exchange(other.data_, nullptr); }
  return *this;
}
MemoryBlock::~MemoryBlock() { reset(); }
void MemoryBlock::reset() noexcept { MemoryAccount::free(std::exchange(data_, nullptr)); }
void* MemoryBlock::data() noexcept { return data_ ? data_->payload : nullptr; }
const void* MemoryBlock::data() const noexcept { return data_ ? data_->payload : nullptr; }
std::size_t MemoryBlock::size() const noexcept { return data_ ? data_->payload_size : 0; }
MemoryUsage MemoryBlock::usage() const noexcept { return data_ ? data_->usage() : MemoryUsage{}; }
MemoryAccount::BlockData& MemoryBlock::required() const {
  require(data_ != nullptr, "empty memory allocation");
  return *data_;
}
MemoryPurpose MemoryBlock::purpose() const { return required().purpose; }
MemoryAttribution MemoryBlock::attribution() const { return required().attribution; }
AllocationLifetime MemoryBlock::lifetime() const { return required().lifetime; }
MemoryStatistics MemoryBlock::account_statistics() const { return required().owner->statistics; }
void MemoryBlock::set_lifetime(AllocationLifetime lifetime) const {
  const auto destination = lifetime_index(lifetime);
  auto& block = required();
  if (block.owner->allocating) throw std::bad_alloc{};
  if (block.lifetime == lifetime) return;
  auto& statistics = block.owner->statistics;
  const auto usage = block.usage();
  subtract(statistics.by_lifetime[static_cast<std::size_t>(block.lifetime)], usage);
  add(statistics.by_lifetime[destination], usage);
  block.lifetime = lifetime;
}

void MemoryAccount::check_invariants() const {
  const auto& control = required();
  const auto& statistics = control.statistics;
  const BlockData* slow = control.first;
  const BlockData* fast = control.first;
  while (fast && fast->next) {
    slow = slow->next;fast = fast->next->next;
    require(slow != fast, "cyclic memory allocation list");
  }
  MemoryUsage total{1, sizeof(Control), 0};
  std::array<MemoryUsage, memory_purpose_count> purposes{};
  std::array<MemoryUsage, allocation_lifetime_count> lifetimes{};
  purposes[static_cast<std::size_t>(MemoryPurpose::control)] = total;
  lifetimes[static_cast<std::size_t>(AllocationLifetime::active)] = total;
  const BlockData* previous = nullptr;
  std::size_t indexed_blocks = 0;
  for (const auto* block = control.first; block; block = block->next) {
    require(block->owner == &control && block->previous == previous, "memory allocation owner/link mismatch");
    require(block->purpose != MemoryPurpose::control, "data allocation uses controller purpose");
    require(block->attribution.valid(), "invalid memory allocation attribution");
    const auto category = purpose_index(block->purpose), lifetime = lifetime_index(block->lifetime);
    require(allocation_bytes(block->payload_size, block->alignment) == block->raw_size, "allocation size metadata mismatch");
    require(*(static_cast<BlockData* const*>(block->payload) - 1) == block, "invalid memory allocation back pointer");
    const bool indexed = indexed_purpose(block->purpose);
    require(control.payloads.contains(reinterpret_cast<std::uintptr_t>(block->payload)) == indexed, "memory allocation index mismatch");
    indexed_blocks += indexed ? 1 : 0;
    const auto usage = block->usage();
    require(total.requested_bytes <= statistics.limit_bytes &&
        usage.requested_bytes <= statistics.limit_bytes - total.requested_bytes, "allocation list exceeds memory limit");
    add(total, usage);add(purposes[category], usage);add(lifetimes[lifetime], usage);previous = block;
  }
  require(statistics.owner != 0 && total == statistics.current && purposes == statistics.by_purpose &&
      lifetimes == statistics.by_lifetime, "memory allocation totals differ");
  require(statistics.peak_requested_bytes >= total.requested_bytes && statistics.peak_requested_bytes <= statistics.limit_bytes,
      "memory allocation peak/limit mismatch");
  require(statistics.freed_allocations <= statistics.successful_allocations &&
      statistics.successful_allocations - statistics.freed_allocations == total.allocations,
      "memory allocation history differs");
  require(control.payloads.size() == indexed_blocks, "memory allocation index differs");
  require(control.references >= total.allocations - 1, "memory allocation controller lifetime lost");
}

}  // namespace crown::resource
