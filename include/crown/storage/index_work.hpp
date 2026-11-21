#pragma once

#include "crown/api/error.hpp"
#include "crown/storage/index_failure.hpp"
#include <exception>
#include <compare>
#include <cstdint>

namespace crown::storage {
namespace detail { struct IndexWorkAlias; }

// Conservative admissions, not elapsed time or allocator bytes. A single
// allowance is passed through a composed operation; reservations for its undo
// and finalization are consumed before tentative publication and never refunded.
struct IndexWork {
  // Fixed structural startup/end actions and actual directory/list visits.
  std::uint64_t structural_steps = 0;
  std::uint64_t scalar_fields = 0;
  std::uint64_t scalar_bytes = 0;
  // Pointer-sized metadata slots initialized/reserved, excluding owned bodies.
  std::uint64_t pointer_slots = 0;
  std::uint64_t link_actions = 0;
  auto operator<=>(const IndexWork&) const = default;
};

class IndexWorkAllowance {
 public:
  explicit IndexWorkAllowance(IndexWork limit, bool fixed_diagnostics = false) noexcept
      : budget_(limit), fixed_diagnostics_(fixed_diagnostics) {}
  IndexWorkAllowance(const IndexWorkAllowance&) = delete;
  IndexWorkAllowance& operator=(const IndexWorkAllowance&) = delete;
  IndexWorkAllowance(IndexWorkAllowance&&) = delete;
  IndexWorkAllowance& operator=(IndexWorkAllowance&&) = delete;

  // Borrow the canonical balance. A diagnostic alias never refills it.
  [[nodiscard]] const IndexWork& remaining() const noexcept { return balance(); }
  [[nodiscard]] bool fixed_diagnostics() const noexcept { return fixed_diagnostics_; }
  void admit(IndexWork amount) {
    auto& remaining_=balance();
    // Check every domain before consuming any of them. A failed multi-domain
    // reservation cannot accidentally consume the allowance for earlier fields.
    if (amount.structural_steps > remaining_.structural_steps ||
        amount.scalar_fields > remaining_.scalar_fields ||
        amount.scalar_bytes > remaining_.scalar_bytes ||
        amount.pointer_slots > remaining_.pointer_slots ||
        amount.link_actions > remaining_.link_actions) {
      if (fixed_diagnostics_) throw IndexFailure(IndexFault::work_limit);
      throw Error("storage_work_limit", "optimized index work allowance exhausted");
    }
    remaining_.structural_steps -= amount.structural_steps;
    remaining_.scalar_fields -= amount.scalar_fields;
    remaining_.scalar_bytes -= amount.scalar_bytes;
    remaining_.pointer_slots -= amount.pointer_slots;
    remaining_.link_actions -= amount.link_actions;
  }

 private:
  friend struct detail::IndexWorkAlias;
  // An internal diagnostic view borrows the canonical balance. It neither
  // copies a limit nor creates/refills a grant. Its owner retains the root.
  IndexWorkAllowance(IndexWorkAllowance& root, bool fixed) noexcept
      :budget_(&root),fixed_diagnostics_(fixed),alias_(true) {
    if (root.alias_) std::terminate();
  }
  [[nodiscard]] IndexWork& balance() noexcept { return alias_ ? budget_.root->budget_.remaining : budget_.remaining; }
  [[nodiscard]] const IndexWork& balance() const noexcept { return alias_ ? budget_.root->budget_.remaining : budget_.remaining; }
  union Budget {
    IndexWork remaining;
    IndexWorkAllowance* root;
    explicit Budget(IndexWork limit) noexcept:remaining(limit) {}
    explicit Budget(IndexWorkAllowance* owner) noexcept:root(owner) {}
  } budget_;
  bool fixed_diagnostics_;
  bool alias_=false;
};

}  // namespace crown::storage
