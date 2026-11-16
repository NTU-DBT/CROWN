#pragma once

#include "crown/resource/allocator.hpp"

namespace crown::resource {

// For transferable result ownership. Assignment/swap adopt the source's
// original account and attribution along with its storage; no new allowance is
// created. Maintained tables/state must keep using nonpropagating MemoryAllocator
// so assigning another value cannot replace their bound query budget.
template<class T>
class OwnerAllocator:public MemoryAllocator<T> {
 public:
  using MemoryAllocator<T>::MemoryAllocator;
  using propagate_on_container_copy_assignment=std::true_type;
  using propagate_on_container_move_assignment=std::true_type;
  using propagate_on_container_swap=std::true_type;
  using is_always_equal=std::false_type;
  template<class U>struct rebind {using other=OwnerAllocator<U>;};
  OwnerAllocator() noexcept=default;
  OwnerAllocator(const OwnerAllocator&) noexcept=default;
  OwnerAllocator& operator=(const OwnerAllocator&) noexcept=default;
  template<class U>
  OwnerAllocator(const OwnerAllocator<U>& other) noexcept
      :MemoryAllocator<T>(static_cast<const MemoryAllocator<U>&>(other)) {}
  [[nodiscard]] OwnerAllocator select_on_container_copy_construction() const noexcept {return *this;}
  template<class U>[[nodiscard]] bool operator==(const OwnerAllocator<U>& other) const noexcept {
    return MemoryAllocator<T>::operator==(static_cast<const MemoryAllocator<U>&>(other));
  }
  template<class U>[[nodiscard]] bool operator!=(const OwnerAllocator<U>& other) const noexcept {return !(*this==other);}
};

} // namespace crown::resource
