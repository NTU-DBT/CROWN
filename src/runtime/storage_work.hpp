#pragma once

#include "crown/api/error.hpp"
#include "crown/ir/program.hpp"
#include "crown/storage/accounted_index_work.hpp"
#include "../storage/index_work_alias.hpp"
#include <exception>
#include <memory>
#include <utility>

namespace crown::runtime::detail {
class StorageWorkContext;
// A suspended update/view/cursor retains this same noncopyable allowance.
// The aliasing shared_ptr passed to storage journals owns the complete lease.
struct StorageWorkState {
  std::shared_ptr<StorageWorkContext> context;
  storage::AccountedIndexWork allowance;
  storage::IndexWorkAllowance legacy;
  StorageWorkState(std::shared_ptr<StorageWorkContext> owner,storage::IndexWork limit)
      :context(std::move(owner)),allowance(storage::AccountedIndexWork::create(memory(),limit)),
       legacy(storage::detail::IndexWorkAlias::legacy(*allowance.get())) {}
 private:
  [[nodiscard]] const resource::MemoryAccount& memory() const;
};
using StorageWorkLease=std::shared_ptr<StorageWorkState>;
class StorageWorkContext {
 public:
  StorageWorkContext(const resource::MemoryAccount& memory,std::optional<storage::IndexWork> limit)
      :memory_(memory),limit_(limit) {}
  [[nodiscard]] const resource::MemoryAccount& memory() const noexcept { return memory_; }
  [[nodiscard]] bool indexed() const noexcept { return limit_.has_value(); }
  // Requires indexed(); this is the immutable five-domain ceiling, not remaining work.
  [[nodiscard]] const storage::IndexWork& limit() const noexcept { return *limit_; }
  [[nodiscard]] const StorageWorkLease& active() const noexcept { return active_; }
#ifdef CROWN_RUNTIME_TESTING
  [[nodiscard]] storage::IndexWork observed_work() const noexcept {
    if (!active_) return last_consumed_;
    const auto& left=active_->allowance.get()->remaining();
    const auto& ceiling=limit();
    return {ceiling.structural_steps-left.structural_steps,ceiling.scalar_fields-left.scalar_fields,
        ceiling.scalar_bytes-left.scalar_bytes,ceiling.pointer_slots-left.pointer_slots,ceiling.link_actions-left.link_actions};
  }
  [[nodiscard]] std::uint64_t fresh_operations() const noexcept { return fresh_operations_; }
#endif
 private:
  friend class StorageOperation;
  resource::MemoryAccount memory_;
  std::optional<storage::IndexWork> limit_;
  StorageWorkLease active_;
#ifdef CROWN_RUNTIME_TESTING
  storage::IndexWork last_consumed_{};
  std::uint64_t fresh_operations_=0;
#endif
};
inline const resource::MemoryAccount& StorageWorkState::memory() const { return context->memory(); }
template<class Plan> [[nodiscard]] inline std::shared_ptr<StorageWorkContext> storage_context(const Plan& plan,
    std::uint64_t limit_bytes,const resource::MemoryAccount& existing={}) {
  auto account=[&] {
    if constexpr(requires{plan.account();}) {
      if(existing && existing.statistics().owner!=plan.account().statistics().owner)
        throw Error("storage_contract","native program and rebuild account differ");
      return plan.account();
    } else return existing ? existing : resource::MemoryAccount::create(limit_bytes);
  }();
  if (account.statistics().limit_bytes!=limit_bytes) throw resource::MemoryFailure(resource::MemoryFault::contract);
  const auto& spec=plan.options().indexed_storage;
  return resource::make_accounted_shared<StorageWorkContext>(account,resource::MemoryPurpose::support_metadata,
      account,spec ? std::optional<storage::IndexWork>{spec->per_operation} : std::nullopt);
}
template<class Plan> inline void validate_storage_context(const Plan& plan,const std::shared_ptr<StorageWorkContext>& context,
    std::uint64_t limit_bytes) {
  const auto& spec=plan.options().indexed_storage;
  if (!context || context->indexed()!=spec.has_value() ||
      (spec && context->limit()!=spec->per_operation) || context->memory().statistics().limit_bytes!=limit_bytes)
    throw Error("storage_contract","runtime work context differs from the immutable backend plan");
  if constexpr(requires{plan.account();})
    if(context->memory().statistics().owner!=plan.account().statistics().owner)
      throw Error("storage_contract","native program belongs to another query account");
}
// Public creation from a compiler/cache artifact starts a new query. Native
// admission then consumes this same account and the one outer operation grant;
// internal rebuilds continue using storage_context's existing-account path.
template<class Plan> [[nodiscard]] inline std::shared_ptr<StorageWorkContext> new_storage_context(const Plan& plan,
    std::uint64_t limit_bytes) {
  auto account=resource::MemoryAccount::create(limit_bytes);const auto& spec=plan.options().indexed_storage;
  return resource::make_accounted_shared<StorageWorkContext>(account,resource::MemoryPurpose::support_metadata,
      account,spec?std::optional<storage::IndexWork>{spec->per_operation}:std::nullopt);
}
// Single-writer internal composition. A fresh indexed operation funds a
// lease/control and its AccountedIndexWork; nested/resumed entries reuse them.
// This is a real admission cost, separate from tuple visits. Only the outer operation creates a
// grant. Nested entries reuse it; resumed entries bind their retained lease.
// Reference operations retain a memory owner but allocate no work grant.
class StorageOperation {
 public:
  explicit StorageOperation(std::shared_ptr<StorageWorkContext> context,StorageWorkLease retained={})
      :context_(std::move(context)) {
    if (!context_ || !context_->indexed()) {
      if (retained) throw Error("storage_contract","indexed lease has no runtime work context");
      return;
    }
    if (retained && retained->context!=context_)
      throw Error("storage_contract","indexed operation lease belongs to another owner");
    if (context_->active_) {
      if (retained && retained!=context_->active_)
        throw Error("storage_contract","a different indexed operation is already active");
      lease_=context_->active_;
    } else {
      const bool fresh=!retained;
      lease_=retained ? std::move(retained) : resource::make_accounted_shared<StorageWorkState>(
          context_->memory(),resource::MemoryPurpose::support_metadata,context_,context_->limit());
      // Admission precedes installing a newly minted operation. Rebinding a
      // suspended operation does not add or restore a single unit of work.
      if (fresh) lease_->legacy.admit(storage::IndexWork{.structural_steps=1});
#ifdef CROWN_RUNTIME_TESTING
      if (fresh && context_->fresh_operations_!=UINT64_MAX) ++context_->fresh_operations_;
#endif
      context_->active_=lease_;outer_=true;
    }
  }
  StorageOperation(const StorageOperation&)=delete;
  StorageOperation& operator=(const StorageOperation&)=delete;
  StorageOperation(StorageOperation&&)=delete;
  StorageOperation& operator=(StorageOperation&&)=delete;
  ~StorageOperation() noexcept {
    if (outer_) {
      if (context_->active_!=lease_) std::terminate();
#ifdef CROWN_RUNTIME_TESTING
      context_->last_consumed_=context_->observed_work();
#endif
      context_->active_.reset();
    }
  }
  [[nodiscard]] const StorageWorkLease& lease() const noexcept { return lease_; }
 private:
  std::shared_ptr<StorageWorkContext> context_;
  StorageWorkLease lease_;
  bool outer_=false;
};
[[nodiscard]] inline StorageWorkLease storage_lease(const std::shared_ptr<StorageWorkContext>& context) {
  if (!context || !context->indexed()) return {};
  if (!context->active()) throw Error("storage_contract","indexed runtime storage call has no active finite operation");
  return context->active();
}
[[nodiscard]] inline storage::IndexWorkAllowance* storage_work(const std::shared_ptr<StorageWorkContext>& context) {
  return context && context->indexed() ? &storage_lease(context)->legacy : nullptr;
}
[[nodiscard]] inline storage::IndexWorkAllowance* compact_storage_work(const std::shared_ptr<StorageWorkContext>& context) {
  return context && context->indexed() ? storage_lease(context)->allowance.get() : nullptr;
}
[[nodiscard]] inline storage::AccountedIndexWork owning_storage_work(const std::shared_ptr<StorageWorkContext>& context) {
  const auto lease=storage_lease(context);return lease ? lease->allowance : storage::AccountedIndexWork{};
}
// Aliasing ownership retains the complete lease without another control or allowance.
[[nodiscard]] inline std::shared_ptr<storage::IndexWorkAllowance> shared_storage_work(
    const std::shared_ptr<StorageWorkContext>& context) {
  auto lease=storage_lease(context);
  if (!lease) return {};
  auto* allowance=&lease->legacy;
  return {std::move(lease),allowance};
}
}  // namespace crown::runtime::detail
