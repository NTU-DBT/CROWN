#pragma once

#include "crown/resource/allocator.hpp"
#include <exception>
#include <algorithm>
#include <limits>
#include <memory>
#include <type_traits>
#include <utility>

namespace crown::storage::detail {
// Directory slots have trivial lifetimes. Releasing their actual allocation
// never walks a sparse historical capacity, even in unoptimized builds. New
// slot initialization is still admitted by HashDirectory before assign().
template<class Node> class AccountedPointerArray {
 public:
  explicit AccountedPointerArray(const resource::MemoryAllocator<Node*>& allocator) noexcept : allocator_(allocator) {}
  AccountedPointerArray(const AccountedPointerArray&) = delete;
  AccountedPointerArray& operator=(const AccountedPointerArray&) = delete;
  AccountedPointerArray(AccountedPointerArray&& other) noexcept
      : allocator_(other.allocator_), block_(std::move(other.block_)), size_(std::exchange(other.size_, 0)) {}
  AccountedPointerArray& operator=(AccountedPointerArray&&) = delete;
  [[nodiscard]] bool empty() const noexcept { return size_ == 0; }
  [[nodiscard]] std::size_t size() const noexcept { return size_; }
  [[nodiscard]] std::size_t capacity() const noexcept { return size_; }
  [[nodiscard]] constexpr std::size_t max_size() const noexcept { return std::numeric_limits<std::size_t>::max() / sizeof(Node*); }
  [[nodiscard]] Node** data() noexcept { return static_cast<Node**>(block_.data()); }
  [[nodiscard]] Node* const* data() const noexcept { return static_cast<Node* const*>(block_.data()); }
  Node*& operator[](std::size_t i) noexcept { return data()[i]; }
  Node* const& operator[](std::size_t i) const noexcept { return data()[i]; }
  [[nodiscard]] auto get_allocator() const noexcept { return allocator_; }
  void assign(std::size_t count, Node* value) {
    if (count > max_size()) throw resource::MemoryFailure(resource::MemoryFault::overflow);
    if (count == 0) { block_.reset();size_ = 0;return; }
    // Keep the old block until every replacement slot is initialized;
    // the existing account therefore funds both real requests at this peak.
    auto block = allocator_.account().allocate(count * sizeof(Node*), alignof(Node*), allocator_.purpose(), allocator_.attribution());
    std::uninitialized_fill_n(static_cast<Node**>(block.data()), count, value);
    block_ = std::move(block);size_ = count;
  }
  // Compatibility includes account, purpose and attribution; slots never
  // adopt ownership of the Node objects they point to.
  void swap(AccountedPointerArray& other) noexcept {
    if (allocator_ != other.allocator_) std::terminate();
    std::swap(block_, other.block_);std::swap(size_, other.size_);
  }
 private:
  static_assert(std::is_trivially_destructible_v<Node*>);
  resource::MemoryAllocator<Node*> allocator_;
  resource::MemoryBlock block_;
  std::size_t size_ = 0;
};
}
