#pragma once

#include "crown/storage/index_work.hpp"
#include <cstddef>
#include <exception>
#include <utility>

namespace crown::storage::detail {

template <class Node>
struct LiveListHook {
  LiveListHook() = default;
  LiveListHook(const LiveListHook&) = delete;
  LiveListHook& operator=(const LiveListHook&) = delete;
  LiveListHook(LiveListHook&&) = delete;
  LiveListHook& operator=(LiveListHook&&) = delete;
  const void* owner = nullptr;
  Node* previous = nullptr;
  Node* next = nullptr;
};

// Nonowning live membership. A row can own its member nodes through one hook
// while a secondary key borrows the same nodes through another. No numerical
// annotation or payload value determines whether a node is linked.
// prepare_insert/erase admit capacity and fixed pointer work; prepaid methods
// allocate nothing. Saved neighbors are valid only under reverse-order undo.
template <class Node, LiveListHook<Node> Node::* Hook, class Errors = LegacyIndexErrors>
class LiveList {
 public:
  static constexpr std::uint64_t insert_actions = 5;
  static constexpr std::uint64_t erase_actions = 5;

  explicit LiveList(std::size_t maximum_nodes) noexcept : maximum_nodes_(maximum_nodes) {}
  LiveList(const LiveList&) = delete;
  LiveList& operator=(const LiveList&) = delete;
  LiveList(LiveList&&) = delete;
  LiveList& operator=(LiveList&&) = delete;
  ~LiveList() = default;  // Node lifetime belongs to the enclosing table state.

  [[nodiscard]] std::size_t size() const noexcept { return size_; }
  [[nodiscard]] Node* first() const noexcept { return first_; }
  [[nodiscard]] Node* last() const noexcept { return last_; }
  [[nodiscard]] static Node* next(const Node& node) noexcept { return hook(node).next; }
  [[nodiscard]] static Node* previous(const Node& node) noexcept { return hook(node).previous; }
  [[nodiscard]] bool contains(const Node& node) const noexcept { return hook(node).owner == this; }
  [[nodiscard]] std::pair<Node*, Node*> neighbors(const Node& node) const noexcept {
    if (!contains(node)) std::terminate();
    return {hook(node).previous, hook(node).next};
  }

  void prepare_insert(IndexWorkAllowance& allowance) const {
    allowance.admit(IndexWork{.structural_steps = 1, .link_actions = insert_actions});
    if (size_ >= maximum_nodes_)
      Errors::fail(IndexFault::capacity, "optimized live membership limit reached");
  }
  void prepare_erase(const Node& node, IndexWorkAllowance& allowance) const {
    allowance.admit(IndexWork{.structural_steps = 1, .link_actions = erase_actions});
    if (!contains(node))
      Errors::fail(IndexFault::contract, "node belongs to another live membership list");
  }

  void append_prepaid(Node& node) noexcept { insert_between_prepaid(node, last_, nullptr); }

  // Saved neighbors are restored in reverse undo order. This validates only
  // current neighbors, never a pointer into an old directory array.
  void insert_between_prepaid(Node& node, Node* previous_node, Node* next_node) noexcept {
    auto& link = hook(node);
    if (link.owner != nullptr || size_ >= maximum_nodes_) std::terminate();
    if (previous_node != nullptr) {
      if (!contains(*previous_node) || hook(*previous_node).next != next_node) std::terminate();
    } else if (first_ != next_node) std::terminate();
    if (next_node != nullptr) {
      if (!contains(*next_node) || hook(*next_node).previous != previous_node) std::terminate();
    } else if (last_ != previous_node) std::terminate();
    link.owner = this;
    link.previous = previous_node;
    link.next = next_node;
    if (previous_node != nullptr) hook(*previous_node).next = &node;
    else first_ = &node;
    if (next_node != nullptr) hook(*next_node).previous = &node;
    else last_ = &node;
    ++size_;
  }

  void erase_prepaid(Node& node) noexcept {
    auto& link = hook(node);
    if (link.owner != this || size_ == 0) std::terminate();
    if (link.previous != nullptr) hook(*link.previous).next = link.next;
    else first_ = link.next;
    if (link.next != nullptr) hook(*link.next).previous = link.previous;
    else last_ = link.previous;
    link.owner = nullptr;
    link.previous = nullptr;
    link.next = nullptr;
    --size_;
  }

  // Used by owning node destructors. The hook's concrete list type is fixed
  // by its template member pointer; its owner must outlive linked nodes.
  static void detach_prepaid(Node& node) noexcept {
    if (hook(node).owner != nullptr) {
      auto* owner = const_cast<LiveList*>(static_cast<const LiveList*>(hook(node).owner));
      owner->erase_prepaid(node);
    }
  }

  // Diagnostic only. Operational traversal follows one live link per step.
  void check_invariants() const {
    auto require = [](bool value) {
      if (!value) Errors::fail(IndexFault::contract, "inconsistent optimized live list");
    };
    require(size_ <= maximum_nodes_);
    std::size_t count = 0;const Node* previous_node = nullptr;
    for (auto* node = first_; node != nullptr; node = hook(*node).next) {
      require(count < size_ && hook(*node).owner == this && hook(*node).previous == previous_node);
      ++count;previous_node = node;
    }
    require(count == size_ && previous_node == last_ && (first_ == nullptr) == (last_ == nullptr));
  }

 private:
  [[nodiscard]] static LiveListHook<Node>& hook(Node& node) noexcept { return node.*Hook; }
  [[nodiscard]] static const LiveListHook<Node>& hook(const Node& node) noexcept { return node.*Hook; }
  const std::size_t maximum_nodes_;
  std::size_t size_ = 0;
  Node* first_ = nullptr;
  Node* last_ = nullptr;
};

}  // namespace crown::storage::detail
