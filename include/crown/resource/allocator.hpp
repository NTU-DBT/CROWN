#pragma once

#include "crown/resource/memory.hpp"
#include <exception>
#include <limits>
#include <new>
#include <type_traits>
#include <utility>

namespace crown::resource {

// Standard-container allocator used by maintained native state. It charges
// the container's own allocations,
// including node/array capacity and this account's framing. It does not make
// nested std::string/Row/Decimal/member allocations use the same allocator.
// Copies share the account. Container assignment keeps the destination
// allocator; standard container swap requires equal allocators. A default
// allocator has no account and cannot silently allocate without a byte limit.
// Equality/rebind also preserve immutable operator attribution; relabeling an
// allocator must never let a container steal another operator's storage.
template<class T>
class MemoryAllocator {
  static_assert(std::is_object_v<T> && !std::is_const_v<T>);
  template<class U> friend class MemoryAllocator;
 public:
  using value_type = T;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using propagate_on_container_copy_assignment = std::false_type;
  using propagate_on_container_move_assignment = std::false_type;
  using propagate_on_container_swap = std::false_type;
  using is_always_equal = std::false_type;
  template<class U> struct rebind { using other = MemoryAllocator<U>; };

  MemoryAllocator() noexcept = default;
  explicit MemoryAllocator(const MemoryAccount& account, MemoryPurpose purpose = MemoryPurpose::scratch,
                           MemoryAttribution attribution = {})
      : account_(account), purpose_(purpose), attribution_(attribution) {
    if (!account_ || purpose == MemoryPurpose::control ||
        static_cast<std::size_t>(purpose) >= memory_purpose_count || !attribution.valid())
      throw MemoryFailure(MemoryFault::contract);
  }
  MemoryAllocator(const MemoryAllocator&) noexcept = default;
  MemoryAllocator& operator=(const MemoryAllocator&) noexcept = default;
  // Allocator moves use the copy constructor/assignment, leaving the source
  // usable for a valid moved-from container without minting another budget.
  template<class U>
  MemoryAllocator(const MemoryAllocator<U>& other) noexcept
      : account_(other.account_), purpose_(other.purpose_), attribution_(other.attribution_) {}

  [[nodiscard]] T* allocate(std::size_t count) {
    if (!account_) throw std::bad_alloc{};
    if (count > max_size()) throw std::bad_array_new_length{};
    return static_cast<T*>(account_.allocate_raw(count * sizeof(T), alignof(T), purpose_, attribution_));
  }
  void deallocate(T* pointer, std::size_t count) noexcept {
    if (!pointer) return;
    if (count > max_size()) std::terminate();
    account_.deallocate_raw(pointer, count * sizeof(T), alignof(T), purpose_, attribution_);
  }
  [[nodiscard]] constexpr std::size_t max_size() const noexcept {
    return std::numeric_limits<std::size_t>::max() / sizeof(T);
  }
  [[nodiscard]] MemoryAllocator select_on_container_copy_construction() const noexcept { return *this; }
  [[nodiscard]] const MemoryAccount& account() const noexcept { return account_; }
  [[nodiscard]] MemoryPurpose purpose() const noexcept { return purpose_; }
  [[nodiscard]] MemoryAttribution attribution() const noexcept { return attribution_; }
  // Nonallocating diagnostics for a still-live allocation from this allocator,
  // using the exact original element count (a vector passes capacity()).
  [[nodiscard]] MemoryUsage allocation_usage(const T* pointer, std::size_t count) const {
    if (!pointer && count == 0) return {};
    if (count > max_size()) throw MemoryFailure(MemoryFault::contract);
    return account_.allocation_usage_raw(pointer, count * sizeof(T), alignof(T), purpose_, attribution_);
  }
  // O(1) classification for the exact still-live allocation owned by this
  // allocator. No ledger scan, allocation or admission refill.
  void set_allocation_lifetime(T* pointer, std::size_t count, AllocationLifetime lifetime) const {
    if (!pointer && count == 0) return;
    if (count > max_size()) throw MemoryFailure(MemoryFault::contract);
    account_.set_lifetime_raw(pointer, count * sizeof(T), alignof(T), purpose_, attribution_, lifetime);
  }

  template<class U>
  [[nodiscard]] bool operator==(const MemoryAllocator<U>& other) const noexcept {
    return account_.control_ == other.account_.control_ && purpose_ == other.purpose_ &&
        attribution_ == other.attribution_;
  }
  template<class U>
  [[nodiscard]] bool operator!=(const MemoryAllocator<U>& other) const noexcept { return !(*this == other); }
 private:
  MemoryAccount account_;
  MemoryPurpose purpose_ = MemoryPurpose::scratch;
  MemoryAttribution attribution_;
};

}  // namespace crown::resource
