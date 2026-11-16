#pragma once

#include "crown/resource/ownership.hpp"
#include "crown/storage/index_work.hpp"
#include <memory>

namespace crown::storage {
// An owning composed-operation work grant, with object/control storage funded
// by its query account. Copies retain exactly the same remaining allowance.
class AccountedIndexWork {
  struct Control {
    resource::MemoryAccount account;
    IndexWorkAllowance work;
    Control(const resource::MemoryAccount& owner, IndexWork limit, bool fixed) noexcept
        : account(owner), work(limit, fixed) {}
  };
 public:
  AccountedIndexWork() noexcept = default;
  [[nodiscard]] static AccountedIndexWork create(const resource::MemoryAccount& account, IndexWork limit,
      bool fixed_diagnostics = true) {
    return AccountedIndexWork(resource::make_accounted_shared<Control>(account,
        resource::MemoryPurpose::support_metadata, account, limit, fixed_diagnostics));
  }
  [[nodiscard]] explicit operator bool() const noexcept { return bool(control_); }
  // Const handles still share a mutable balance; retain an owner while
  // using this borrow. Sharing the handle supplies no thread synchronization.
  [[nodiscard]] IndexWorkAllowance* get() const & noexcept { return control_ ? &control_->work : nullptr; }
  IndexWorkAllowance* get() const && = delete;
  [[nodiscard]] IndexWorkAllowance& operator*() const & {
    if (!control_) throw IndexFailure(IndexFault::contract);
    return control_->work;
  }
  IndexWorkAllowance& operator*() const && = delete;
  [[nodiscard]] bool same_account(const resource::MemoryAccount& account) const noexcept {
    return control_ && account && resource::MemoryAllocator<unsigned char>(control_->account) ==
        resource::MemoryAllocator<unsigned char>(account);
  }
 private:
  explicit AccountedIndexWork(std::shared_ptr<Control> control) noexcept : control_(std::move(control)) {}
  std::shared_ptr<Control> control_;
};
}
