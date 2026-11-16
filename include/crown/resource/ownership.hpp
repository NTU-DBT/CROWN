#pragma once

#include "crown/resource/allocator.hpp"
#include <memory>
#include <type_traits>
#include <utility>

namespace crown::resource {

// Accounted ownership bridge. These factories account object storage and,
// for shared ownership, the library's rebound control-block allocation. They
// do not inject an allocator into arbitrary members. Constructors must receive
// the same account explicitly for every nested allocation they own.
template<class T>
class MemoryDelete {
  static_assert(std::is_object_v<T> && !std::is_array_v<T> && !std::is_const_v<T>);
 public:
  MemoryDelete() noexcept = default;
  explicit MemoryDelete(const MemoryAllocator<T>& allocator) noexcept : allocator_(allocator) {}
  void operator()(T* pointer) noexcept {
    // Permit AccountedUnique<ForwardDeclaredData> in a public owner header;
    // T must be complete only where the out-of-line deletion is instantiated.
    static_assert(std::is_nothrow_destructible_v<T>);
    if (!pointer) return;
    std::destroy_at(pointer);
    allocator_.deallocate(pointer, 1);
  }
  [[nodiscard]] const MemoryAccount& account() const noexcept { return allocator_.account(); }
  [[nodiscard]] MemoryPurpose purpose() const noexcept { return allocator_.purpose(); }
  [[nodiscard]] MemoryAttribution attribution() const noexcept { return allocator_.attribution(); }
  void set_lifetime(T* pointer, AllocationLifetime lifetime) const {
    allocator_.set_allocation_lifetime(pointer, 1, lifetime);
  }
 private:
  MemoryAllocator<T> allocator_;
};
template<class T>
using AccountedUnique = std::unique_ptr<T, MemoryDelete<T>>;

template<class T, class... Args>
[[nodiscard]] AccountedUnique<T> make_accounted_unique(
    MemoryAttribution attribution, const MemoryAccount& account, MemoryPurpose purpose, Args&&... args) {
  static_assert(std::is_nothrow_destructible_v<T>);
  MemoryAllocator<T> allocator(account, purpose, attribution);
  T* object = allocator.allocate(1);
  try {
    std::construct_at(object, std::forward<Args>(args)...);
  } catch (...) {
    allocator.deallocate(object, 1);
    throw;
  }
  return AccountedUnique<T>(object, MemoryDelete<T>(allocator));
}
template<class T, class... Args>
[[nodiscard]] AccountedUnique<T> make_accounted_unique(
    const MemoryAccount& account, MemoryPurpose purpose, Args&&... args) {
  return make_accounted_unique<T>(MemoryAttribution{}, account, purpose, std::forward<Args>(args)...);
}

template<class T, class... Args>
[[nodiscard]] std::shared_ptr<T> make_accounted_shared(
    MemoryAttribution attribution, const MemoryAccount& account, MemoryPurpose purpose, Args&&... args) {
  static_assert(std::is_object_v<T> && !std::is_array_v<T> && !std::is_const_v<T>);
  static_assert(std::is_nothrow_destructible_v<T>);
  // Rebinding preserves account, purpose and attribution. The control block's stored
  // allocator and its raw allocation retain the controller through the final
  // weak release. Allocating shared ownership is never a fresh budget grant.
  return std::allocate_shared<T>(MemoryAllocator<T>(account, purpose, attribution), std::forward<Args>(args)...);
}
template<class T, class... Args>
[[nodiscard]] std::shared_ptr<T> make_accounted_shared(
    const MemoryAccount& account, MemoryPurpose purpose, Args&&... args) {
  return make_accounted_shared<T>(MemoryAttribution{}, account, purpose, std::forward<Args>(args)...);
}

}  // namespace crown::resource
