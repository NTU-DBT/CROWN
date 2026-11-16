#pragma once

#include "crown/storage/index_work.hpp"
#include <cstddef>
#include <cstdint>
#include <exception>
#include <limits>
#include <memory>
#include <type_traits>
#include <set>
#include <utility>
#include <vector>

namespace crown::storage::detail {

// One hook per directory membership. Node ownership and public live-order
// lists belong to the table; a directory may also contain private empty keys.
template <class Node>
struct HashDirectoryHook {
  HashDirectoryHook() = default;
  HashDirectoryHook(const HashDirectoryHook&) = delete;
  HashDirectoryHook& operator=(const HashDirectoryHook&) = delete;
  HashDirectoryHook(HashDirectoryHook&&) = delete;
  HashDirectoryHook& operator=(HashDirectoryHook&&) = delete;
  std::uint64_t hash = 0;
  const void* owner = nullptr;
  Node* next = nullptr;
  Node** previous = nullptr;
  Node* resident_previous = nullptr;
  Node* resident_next = nullptr;
  void reset() noexcept {
    // Immutable value hashes survive detachment for nonallocating journal undo.
    // Only owner/links determine membership; zero is also a valid hash.
    owner = nullptr;
    next = nullptr;
    previous = nullptr;
    resident_previous = nullptr;
    resident_next = nullptr;
  }
};

// Stable separately chained nodes; array entries are nonowning pointers.
// Usage: prepare_growth may allocate/throw, then publish_growth and prepaid
// link/unlink only rewrite admitted pointers. Nodes and their hooks outlive
// membership; live-order iteration is separate. See docs/code_specs/primitives.md.
// Expected lookup cost assumes distributed hashes. Full-hash collisions still
// invoke exact equality and may consume a linear number of admitted visits.
template <class Node, HashDirectoryHook<Node> Node::* Hook,
          class Allocator = std::allocator<Node*>, class Errors = LegacyIndexErrors,
          class Storage = std::vector<Node*, Allocator>>
class HashDirectory {
  static_assert(std::numeric_limits<std::size_t>::digits <= 64);
  using HookType = HashDirectoryHook<Node>;

 public:
  // Upper bounds on structural pointer writes; callers reserve these before
  // using the nonthrowing publication methods. Rehash reserves separately.
  static constexpr std::uint64_t link_actions = 9;
  static constexpr std::uint64_t unlink_actions = 12;
  static constexpr std::uint64_t rehash_actions_per_node = 5;

  class Growth {
   public:
    Growth(const Growth&) = delete;
    Growth& operator=(const Growth&) = delete;
    Growth(Growth&& other) noexcept
        : owner_(std::exchange(other.owner_, nullptr)),
          replacement_(std::move(other.replacement_)),
          original_capacity_(other.original_capacity_),
          admitted_nodes_(other.admitted_nodes_) {}
    Growth& operator=(Growth&&) = delete;
    ~Growth() = default;
    [[nodiscard]] bool active() const noexcept { return owner_ != nullptr; }
    [[nodiscard]] bool changes_capacity() const noexcept {
      return active() && !replacement_.empty();
    }
    // A consumed/moved-from token reports zero, not its retained obsolete array.
    [[nodiscard]] std::size_t new_capacity() const noexcept {
      return active() ? (replacement_.empty() ? original_capacity_ : replacement_.size()) : 0;
    }

   private:
    friend class HashDirectory;
    explicit Growth(HashDirectory* owner) noexcept
        : owner_(owner), replacement_(owner->buckets_.get_allocator()) {}
    HashDirectory* owner_;
    Storage replacement_;
    std::size_t original_capacity_ = 0;
    std::size_t admitted_nodes_ = 0;
  };

  explicit HashDirectory(std::size_t maximum_slots, const Allocator& allocator = Allocator{}) noexcept
      : maximum_slots_(maximum_slots), buckets_(allocator) {}
  HashDirectory(const HashDirectory&) = delete;
  HashDirectory& operator=(const HashDirectory&) = delete;
  HashDirectory(HashDirectory&&) = delete;
  HashDirectory& operator=(HashDirectory&&) = delete;
  // Does not own nodes. Their hooks must not be reused after this directory
  // dies without first unlinking them; the owning table controls destruction.
  ~HashDirectory() = default;

  [[nodiscard]] std::size_t size() const noexcept { return size_; }
  [[nodiscard]] std::size_t capacity() const noexcept { return buckets_.size(); }
  [[nodiscard]] std::size_t maximum_slots() const noexcept { return maximum_slots_; }
  [[nodiscard]] Node* first_resident() const noexcept { return first_; }
  [[nodiscard]] Node* last_resident() const noexcept { return last_; }
  [[nodiscard]] static Node* next_resident(const Node& node) noexcept {
    return hook(node).resident_next;
  }

  template <class Equal>
  [[nodiscard]] Node* find(std::uint64_t hash, Equal&& equal,
                           IndexWorkAllowance& allowance) const {
    allowance.admit(IndexWork{.structural_steps = 1});
    if (buckets_.empty()) return nullptr;
    auto* node = buckets_[bucket_for(hash, buckets_.size())];
    while (node != nullptr) {
      allowance.admit(IndexWork{.structural_steps = 1});
      const auto& link = hook(*node);
      if (link.hash == hash && equal(*node, allowance)) return node;
      node = link.next;
    }
    return nullptr;
  }

  // No published pointers change during preparation. Slot initialization and
  // every resident-node rehash are admitted before the replacement allocates.
  [[nodiscard]] Growth prepare_growth(std::size_t required_nodes,
                                      IndexWorkAllowance& allowance) {
    return prepare_growth(required_nodes, allowance, maximum_slots_);
  }

  // A composing table passes its remaining aggregate directory-slot capacity.
  // This is checked before allocating an otherwise valid per-directory array.
  [[nodiscard]] Growth prepare_growth(std::size_t required_nodes,
                                      IndexWorkAllowance& allowance,
                                      std::size_t additional_slot_room) {
    allowance.admit(IndexWork{.structural_steps = 1});
    if (required_nodes < size_)
      Errors::fail(IndexFault::contract, "directory growth omitted resident nodes");
    Growth result(this);
    result.original_capacity_ = buckets_.size();
    result.admitted_nodes_ = size_;
    const auto wanted = capacity_for(required_nodes);
    if (wanted == buckets_.size()) return result;
    if (wanted > buckets_.max_size())
      Errors::fail(IndexFault::overflow, "directory exceeds pointer container domain");
    if (wanted - buckets_.size() > additional_slot_room)
      Errors::fail(IndexFault::capacity, "aggregate optimized directory slot limit reached");
    const auto nodes = static_cast<std::uint64_t>(size_);
    if (nodes > std::numeric_limits<std::uint64_t>::max() / rehash_actions_per_node)
      Errors::fail(IndexFault::overflow, "directory rehash work overflow");
    allowance.admit(IndexWork{.structural_steps = nodes,
        .pointer_slots = static_cast<std::uint64_t>(wanted),
        .link_actions = nodes * rehash_actions_per_node});
    result.replacement_.assign(wanted, nullptr);
    return result;
  }

  // Caller has already admitted any aggregate table capacity and all remaining
  // mutation work. It must publish growth before inserting additional nodes.
  // The saved token contains no pointers into the old array or node chains.
  void publish_growth(Growth&& growth) noexcept {
    if (growth.owner_ != this || growth.original_capacity_ != buckets_.size() ||
        size_ > growth.admitted_nodes_)
      std::terminate();
    growth.owner_ = nullptr;
    if (growth.replacement_.empty()) return;
    if (size_ > load_limit(growth.replacement_.size())) std::terminate();
    buckets_.swap(growth.replacement_);
    for (auto* node = first_; node != nullptr; node = hook(*node).resident_next) {
      auto& link = hook(*node);
      auto& head = buckets_[bucket_for(link.hash, buckets_.size())];
      link.next = head;
      link.previous = &head;
      if (head != nullptr) hook(*head).previous = &link.next;
      head = node;
    }
    // The token now retains only the obsolete pointer array; its destruction
    // frees that array without touching nodes or any public traversal links.
  }

  void link_prepaid(Node& node, std::uint64_t hash) noexcept {
    link_between_prepaid(node, hash, last_, nullptr);
  }

  // Undo can restore the original resident position without comparing keys,
  // searching a chain or retaining a pointer into an obsolete bucket array.
  void link_between_prepaid(Node& node, std::uint64_t hash,
                             Node* previous, Node* next) noexcept {
    auto& link = hook(node);
    if (link.owner != nullptr || buckets_.empty() || size_ >= load_limit(buckets_.size()))
      std::terminate();
    if (previous != nullptr) {
      if (hook(*previous).owner != this || hook(*previous).resident_next != next) std::terminate();
    } else if (first_ != next) std::terminate();
    if (next != nullptr) {
      if (hook(*next).owner != this || hook(*next).resident_previous != previous) std::terminate();
    } else if (last_ != previous) std::terminate();
    auto& head = buckets_[bucket_for(hash, buckets_.size())];
    link.hash = hash;
    link.owner = this;
    link.next = head;
    link.previous = &head;
    if (head != nullptr) hook(*head).previous = &link.next;
    head = &node;
    link.resident_previous = previous;
    link.resident_next = next;
    if (previous != nullptr) hook(*previous).resident_next = &node;
    else first_ = &node;
    if (next != nullptr) hook(*next).resident_previous = &node;
    else last_ = &node;
    ++size_;
  }

  void unlink_prepaid(Node& node) noexcept {
    auto& link = hook(node);
    if (link.owner != this || link.previous == nullptr || size_ == 0)
      std::terminate();
    *link.previous = link.next;
    if (link.next != nullptr) hook(*link.next).previous = link.previous;
    if (link.resident_previous != nullptr)
      hook(*link.resident_previous).resident_next = link.resident_next;
    else first_ = link.resident_next;
    if (link.resident_next != nullptr)
      hook(*link.resident_next).resident_previous = link.resident_previous;
    else last_ = link.resident_previous;
    link.reset();
    --size_;
  }

  static void detach_prepaid(Node& node) noexcept {
    if (hook(node).owner != nullptr) {
      auto* owner = const_cast<HashDirectory*>(static_cast<const HashDirectory*>(hook(node).owner));
      owner->unlink_prepaid(node);
    }
  }

  // Available to allocator-aware owners. This reads the actual capacity block.
  [[nodiscard]] auto allocation_usage() const {
    return buckets_.get_allocator().allocation_usage(buckets_.data(), buckets_.capacity());
  }

  // Nonallocating diagnostic. Each resident must occur in its exact hash chain;
  // bounded walks reject cycles and prove both populations have the same size.
  void check_invariants_noalloc() const {
    const auto require = [](bool value) {
      if (!value) Errors::fail(IndexFault::contract, "inconsistent optimized hash directory");
    };
    require(buckets_.empty() || (buckets_.size() >= 8 && (buckets_.size() & (buckets_.size() - 1)) == 0));
    require(buckets_.size() <= maximum_slots_ && size_ <= load_limit(buckets_.size()));
    std::size_t chained = 0;
    for (std::size_t bucket = 0; bucket < buckets_.size(); ++bucket) {
      Node* const* previous = &buckets_[bucket];
      for (auto* node = buckets_[bucket]; node; node = hook(*node).next) {
        require(chained < size_);++chained;
        const auto& link = hook(*node);
        require(link.owner == this && link.previous == previous && bucket_for(link.hash, buckets_.size()) == bucket);
        previous = &link.next;
      }
    }
    const Node* previous = nullptr;std::size_t resident = 0;
    for (auto* node = first_; node; node = hook(*node).resident_next) {
      require(resident < size_);++resident;
      const auto& link = hook(*node);
      require(link.owner == this && link.resident_previous == previous);
      bool found = false;
      for (auto* other = buckets_[bucket_for(link.hash, buckets_.size())]; other; other = hook(*other).next)
        if (other == node) found = true;
      require(found);previous = node;
    }
    require(resident == size_ && chained == size_ && previous == last_ && (first_ == nullptr) == (last_ == nullptr));
  }

  // Explicit full diagnostic, separate from probes/cursors and their grants.
  // O(bucket capacity + n log n) time and O(n) temporary set storage; it scans
  // retained array capacity. Use check_invariants_noalloc for fixed scratch,
  // whose collision-heavy worst case is separately O(capacity + n*n).
  void check_invariants() const {
    auto require = [](bool value) {
      if (!value) Errors::fail(IndexFault::contract, "inconsistent optimized hash directory");
    };
    require(buckets_.empty() || (buckets_.size() >= 8 &&
        (buckets_.size() & (buckets_.size() - 1)) == 0));
    require(buckets_.size() <= maximum_slots_ && size_ <= load_limit(buckets_.size()));
    std::set<const Node*> chained, resident;
    for (std::size_t bucket = 0; bucket < buckets_.size(); ++bucket) {
      Node* const* previous = &buckets_[bucket];
      for (auto* node = buckets_[bucket]; node != nullptr; node = hook(*node).next) {
        const auto& link = hook(*node);
        require(chained.insert(node).second && link.owner == this && link.previous == previous);
        require(bucket_for(link.hash, buckets_.size()) == bucket);
        previous = &link.next;
      }
    }
    const Node* previous = nullptr;
    for (auto* node = first_; node != nullptr; node = hook(*node).resident_next) {
      const auto& link = hook(*node);
      require(resident.insert(node).second && link.owner == this && link.resident_previous == previous);
      previous = node;
    }
    require(previous == last_ && chained == resident && resident.size() == size_);
    require((first_ == nullptr) == (last_ == nullptr));
  }

 private:
  [[nodiscard]] static HookType& hook(Node& node) noexcept { return node.*Hook; }
  [[nodiscard]] static const HookType& hook(const Node& node) noexcept { return node.*Hook; }
  [[nodiscard]] static std::size_t load_limit(std::size_t slots) noexcept {
    return slots - slots / 4;
  }
  [[nodiscard]] static std::size_t bucket_for(std::uint64_t hash,
                                             std::size_t capacity) noexcept {
    return static_cast<std::size_t>(hash) & (capacity - 1);
  }
  [[nodiscard]] std::size_t capacity_for(std::size_t required_nodes) const {
    if (required_nodes <= load_limit(buckets_.size())) return buckets_.size();
    std::size_t wanted = buckets_.empty() ? 8 : buckets_.size();
    if (wanted > maximum_slots_)
      Errors::fail(IndexFault::capacity, "optimized directory slot limit reached");
    while (required_nodes > load_limit(wanted)) {
      if (wanted > maximum_slots_ / 2)
        Errors::fail(IndexFault::capacity, "optimized directory slot limit reached");
      wanted *= 2;
    }
    return wanted;
  }

  const std::size_t maximum_slots_;
  Storage buckets_;
  std::size_t size_ = 0;
  Node* first_ = nullptr;
  Node* last_ = nullptr;
};

}  // namespace crown::storage::detail
