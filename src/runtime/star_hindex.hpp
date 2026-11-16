#pragma once

#include "crown/api/error.hpp"
#include "crown/resource/allocator.hpp"
#include <cstddef>
#include <cstdint>
#include <limits>
#include <map>
#include <optional>
#include <utility>

namespace crown::runtime::star::detail {

// Exact center-coordinate generalized H, not maximum degree or graph H for
// every arity: h=max{r : #{positive keys of degree >= r^(d-1)} >= r}.
// P2 arXiv:2603.14754v1, Definition 5.1 supplies the quantity. The two-suffix
// tracker below is the local repair in v68-star-proof-v1/audit.txt section 6,
// rather than P2's unspecified constant-time histogram assertion.
class HIndex {
  using Count = std::uint64_t;
  using Histogram = std::map<Count, Count, std::less<Count>,
      resource::MemoryAllocator<std::pair<const Count, Count>>>;
  struct State { Count h = 0, keys = 0, a = 0, b = 0; };

 public:
  // nullopt means a mathematical power above UINT64_MAX. The exponent-zero
  // convention is 1, including 0^0, because d=1 counts all positive keys.
  // Integer exponentiation uses bounded word arithmetic, never floating point.
  [[nodiscard]] static std::optional<Count> power(Count base, std::size_t exponent) noexcept {
    if (!exponent || base == 1) return Count{1};
    if (!base) return Count{0};
    if (exponent >= static_cast<std::size_t>(std::numeric_limits<Count>::digits)) return {};
    Count result = 1;
    while (exponent) {
      if (exponent & 1U) {
        if (result > UINT64_MAX / base) return {};
        result *= base;
      }
      exponent >>= 1U;
      if (!exponent) break;
      if (base > UINT64_MAX / base) return {};
      base *= base;
    }
    return result;
  }

  // A preparation borrows one stable index; the index must outlive it and
  // remain unchanged until commit/abandonment. The caller serializes tokens.
  // Only a possible detached destination bucket is owned. Abandonment cannot
  // change histogram frequencies, h or either suffix count.
  class Prepared {
   public:
    Prepared(const Prepared&) = delete;
    Prepared& operator=(const Prepared&) = delete;
    Prepared(Prepared&& other) noexcept
        : owner_(std::exchange(other.owner_, nullptr)), old_(other.old_),
          destination_(other.destination_), node_(std::move(other.node_)), next_(other.next_) {
      other.old_ = {}; other.destination_ = {};
    }
    Prepared& operator=(Prepared&& other) noexcept {
      if (this != &other) {
        // Reconstruct the optional node handle: tokens from unequal query
        // allocators must not use nonpropagating node-handle move assignment.
        node_.reset();
        if (other.node_) node_.emplace(std::move(*other.node_));
        owner_ = std::exchange(other.owner_, nullptr);
        old_ = other.old_; destination_ = other.destination_; next_ = other.next_;
        other.old_ = {}; other.destination_ = {};
      }
      return *this;
    }
    ~Prepared() = default;
    [[nodiscard]] Count next_h() const noexcept { return next_.h; }
    [[nodiscard]] Count next_keys() const noexcept { return next_.keys; }
    [[nodiscard]] Count next_a() const noexcept { return next_.a; }
    [[nodiscard]] Count next_b() const noexcept { return next_.b; }

    // Valid publication uses equal-allocator detached insertion and integer
    // updates only. Insert before erasing: the saved lower_bound hint may name
    // the old bucket. Integer comparisons, erasure/deallocation and account
    // bookkeeping retain their actual costs; no allocation or work refill.
    void commit() noexcept {
      if (!owner_) return;
      auto& histogram = owner_->histogram_;
      if (node_) histogram.insert(destination_, std::move(*node_));
      else if (destination_ != histogram.end()) ++destination_->second;
      if (old_ != histogram.end() && --old_->second == 0) histogram.erase(old_);
      owner_->state_ = next_;
      owner_ = nullptr;
      // Erasure invalidated old_. An inactive token must not copy that iterator
      // when moved later, nor retain iterator dependencies in moved-from tokens.
      old_ = {}; destination_ = {};
    }

   private:
    friend class HIndex;
    Prepared(HIndex& owner, Histogram::iterator old, Histogram::iterator destination,
        std::optional<Histogram::node_type> node, State next) noexcept
        : owner_(&owner), old_(old), destination_(destination),
          node_(std::move(node)), next_(next) {}
    HIndex* owner_;
    Histogram::iterator old_, destination_;
    std::optional<Histogram::node_type> node_;
    State next_;
  };

  explicit HIndex(const resource::MemoryAccount& account, std::size_t dimension,
      resource::MemoryAttribution attribution = {resource::MemoryOwnerKind::support_node, 0})
      : dimension_(dimension), histogram_(std::less<Count>{},
            Histogram::allocator_type(account, resource::MemoryPurpose::support_metadata, attribution)) {
    require(dimension != 0, "center arity must be positive");
  }
  HIndex(const HIndex&) = delete;
  HIndex& operator=(const HIndex&) = delete;
  // Move only between operations, with no live Prepared. A moved-from index
  // may be destroyed; its scalar summary does not describe the moved nodes.
  HIndex(HIndex&&) noexcept = default;
  HIndex& operator=(HIndex&&) = delete;
  [[nodiscard]] std::size_t dimension() const noexcept { return dimension_; }
  [[nodiscard]] Count h() const noexcept { return state_.h; }
  [[nodiscard]] Count keys() const noexcept { return state_.keys; }
  [[nodiscard]] Count a() const noexcept { return state_.a; }
  [[nodiscard]] Count b() const noexcept { return state_.b; }
  [[nodiscard]] std::size_t histogram_buckets() const noexcept { return histogram_.size(); }
  [[nodiscard]] std::optional<Count> threshold(Count base) const noexcept {
    return power(base, dimension_ - 1);
  }

  // One actual center-row change changes this coordinate's one key degree by
  // exactly +/-1; zero denotes absence and is never a stored histogram bucket.
  // Charge is the caller's single shared selected-work callback. All fallible
  // lookups, interval work and destination allocation finish before publication.
  template<class Charge>
  [[nodiscard]] Prepared prepare(Count old_degree, Count new_degree, Charge&& charge) {
    charge();
    const bool insertion = old_degree < new_degree;
    require(insertion ? old_degree != UINT64_MAX && new_degree == old_degree + 1 :
        old_degree != 0 && new_degree == old_degree - 1, "a degree change must be one incidence");
    State next = state_;
    if (!old_degree) next.keys = add(next.keys, 1);
    else if (!new_degree) next.keys = subtract(next.keys, 1);

    auto old = histogram_.end(), destination = histogram_.end();
    if (old_degree) {
      charge(); old = histogram_.find(old_degree);
      require(old != histogram_.end() && old->second != 0, "old degree is absent from the histogram");
    }
    if (new_degree) {
      charge(); destination = histogram_.lower_bound(new_degree);
    }
    const bool create = new_degree && (destination == histogram_.end() || destination->first != new_degree);
    if (new_degree && !create) require(destination->second != UINT64_MAX, "degree frequency overflow");

    if (dimension_ == 1) {
      // r^0 is 1 for every r, so h=A=B=number of positive-degree keys.
      next.h = next.a = next.b = next.keys;
    } else {
      next.a = adjusted(state_.a, threshold(state_.h), old_degree, new_degree);
      next.b = adjusted(state_.b, following_threshold(state_.h), old_degree, new_degree);
      if (state_.h != UINT64_MAX && next.b >= state_.h + 1) {
        next.h = state_.h + 1;
        next.a = next.b;
        next.b = subtract(next.b, interval(threshold(next.h), following_threshold(next.h),
            old_degree, new_degree, charge));
      } else if (next.a < state_.h) {
        next.h = state_.h - 1;
        next.b = next.a;
        next.a = add(next.a, interval(threshold(next.h), threshold(state_.h),
            old_degree, new_degree, charge));
      }
    }

    std::optional<Histogram::node_type> node;
    if (create) {
      charge();
      Histogram prepared(histogram_.key_comp(), histogram_.get_allocator());
      const auto item = prepared.emplace(new_degree, Count{1}).first;
      node.emplace(prepared.extract(item));
    }
    return Prepared(*this, old, destination, std::move(node), next);
  }

  // Explicit diagnostic scan, not an update primitive or complexity witness.
  // Verify positive sparse buckets, key total, both suffixes and maximality.
  void check_invariants() const {
    State actual;
    const auto low = threshold(state_.h), high = following_threshold(state_.h);
    for (const auto& [degree, frequency] : histogram_) {
      require(degree && frequency, "histogram contains a zero bucket");
      actual.keys = add(actual.keys, frequency);
      if (at_least(degree, low)) actual.a = add(actual.a, frequency);
      if (at_least(degree, high)) actual.b = add(actual.b, frequency);
    }
    require(actual.keys == state_.keys && actual.a == state_.a && actual.b == state_.b,
        "histogram and suffix counts disagree");
    require(state_.a >= state_.h && (state_.h == UINT64_MAX || state_.b < state_.h + 1),
        "H does not satisfy its exact threshold definition");
  }

 private:
  static void require(bool condition, const char* message) {
    if (!condition) throw Error("star_hindex_contract", message);
  }
  static Count add(Count value, Count amount) {
    require(amount <= UINT64_MAX - value, "histogram count overflow"); return value + amount;
  }
  static Count subtract(Count value, Count amount) {
    require(amount <= value, "histogram count underflow"); return value - amount;
  }
  [[nodiscard]] std::optional<Count> following_threshold(Count h) const noexcept {
    if (dimension_ == 1) return Count{1};
    return h == UINT64_MAX ? std::optional<Count>{} : threshold(h + 1);
  }
  static bool at_least(Count degree, std::optional<Count> bound) noexcept {
    return degree && bound && degree >= *bound;
  }
  static Count adjusted(Count value, std::optional<Count> bound, Count old_degree, Count new_degree) {
    if (at_least(old_degree, bound)) value = subtract(value, 1);
    if (at_least(new_degree, bound)) value = add(value, 1);
    return value;
  }
  static bool inside(Count degree, std::optional<Count> low, std::optional<Count> high) noexcept {
    return at_least(degree, low) && (!high || degree < *high);
  }
  template<class Charge>
  Count interval(std::optional<Count> low, std::optional<Count> high,
      Count old_degree, Count new_degree, Charge& charge) const {
    if (!low) return 0;
    charge();
    Count count = 0;
    for (auto item = histogram_.lower_bound(*low); item != histogram_.end() &&
        (!high || item->first < *high); ++item) {
      charge(); count = add(count, item->second);
    }
    if (inside(old_degree, low, high)) count = subtract(count, 1);
    if (inside(new_degree, low, high)) count = add(count, 1);
    return count;
  }

  // Only occupied degree buckets are traversed in a threshold interval. For
  // d>=2 its integer width is O_d((h+1)^(d-2)), not generally O(1). Sparse map
  // lookup/comparison, fixed-word powers, allocation and account costs remain
  // additional. An overflowing upper power caps this mathematical interval at
  // the word domain; it does not trigger a recount of all source keys.
  std::size_t dimension_;
  Histogram histogram_;
  State state_;
};
} // namespace crown::runtime::star::detail
