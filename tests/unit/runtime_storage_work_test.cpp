#include "storage_work.hpp"

#include "index_allocation.hpp"

#include <cstdint>
#include <iostream>
#include <memory>
#include <new>
#include <stdexcept>
#include <string>
#include <string_view>

using crown::Error;
using crown::storage::IndexWork;
namespace detail = crown::runtime::detail;

namespace {
void verify(bool value, std::string_view message) {
  if (!value) throw std::runtime_error(std::string(message));
}

template <class Function>
void rejects(std::string_view code, Function&& function) {
  bool rejected = false;
  try { function(); }
  catch (const Error& error) {
    verify(error.code() == code, "wrong error code");
    rejected = true;
  }
  verify(rejected, "operation unexpectedly succeeded");
}

IndexWork declared_limit() {
  return IndexWork{.structural_steps = 3, .scalar_fields = 4, .scalar_bytes = 5,
      .pointer_slots = 6, .link_actions = 7};
}

IndexWork fresh_remaining() {
  return IndexWork{.structural_steps = 2, .scalar_fields = 4, .scalar_bytes = 5,
      .pointer_slots = 6, .link_actions = 7};
}
std::shared_ptr<detail::StorageWorkContext> make_context(IndexWork limit) {
  auto account=crown::resource::MemoryAccount::create(1024*1024);
  return crown::resource::make_accounted_shared<detail::StorageWorkContext>(account,
      crown::resource::MemoryPurpose::support_metadata,account,std::optional<IndexWork>{limit});
}

void reference_scope_is_allocation_free() {
  const std::shared_ptr<detail::StorageWorkContext> context;
  std::size_t calls = 0;
  {
    s04_alloc::Scope allocation_guard;
    detail::StorageOperation operation(context);
    const auto lease = operation.lease();
    const auto shared = detail::shared_storage_work(context);
    verify(!lease && !detail::storage_lease(context) && !detail::storage_work(context) && !shared,
        "reference scope unexpectedly created an indexed lease");
    calls = s04_alloc::calls;
  }
  verify(calls == 0, "reference scope allocated work state");
}

void nested_alias_and_resume_share_one_allowance() {
  const auto context = make_context(declared_limit());
  detail::StorageWorkLease retained;
  std::shared_ptr<crown::storage::IndexWorkAllowance> alias;
  {
    detail::StorageOperation outer(context);
    retained = outer.lease();
    verify(retained && context->active() == retained, "outer operation did not install its lease");
    verify(retained->allowance.get()->remaining() == fresh_remaining(),
        "fresh operation did not consume its structural startup admission");

    std::size_t calls = 0;
    {
      s04_alloc::Scope allocation_guard;
      {
        detail::StorageOperation nested(context);
        verify(nested.lease() == retained, "nested scope created a second allowance");
        detail::storage_work(context)->admit(IndexWork{.structural_steps = 1, .scalar_fields = 1,
            .scalar_bytes = 1, .pointer_slots = 1, .link_actions = 1});
      }
      verify(retained->allowance.get()->remaining() == IndexWork{.structural_steps = 1, .scalar_fields = 3,
          .scalar_bytes = 4, .pointer_slots = 5, .link_actions = 6},
          "nested scope did not consume the outer allowance");
      {
        detail::StorageOperation nested(context);
        verify(nested.lease() == retained, "later nested scope did not reuse the active lease");
        detail::storage_work(context)->admit(IndexWork{.structural_steps = 1, .scalar_fields = 2,
            .scalar_bytes = 3, .pointer_slots = 4, .link_actions = 5});
      }
      verify(retained->allowance.get()->remaining() == IndexWork{.scalar_fields = 1, .scalar_bytes = 1,
          .pointer_slots = 1, .link_actions = 1}, "nested work domains were not shared");
      alias = detail::shared_storage_work(context);
      verify(alias.get() == &retained->legacy &&
          detail::compact_storage_work(context)==retained->allowance.get() &&
          alias->remaining()==retained->allowance.get()->remaining(),
          "shared and native storage work do not alias the same lease balance");
      calls = s04_alloc::calls;
    }
    verify(calls == 0, "nested scopes or shared allowance alias allocated");
  }
  verify(!context->active(), "outer scope did not clear the active lease");

  const auto before_resume = retained->allowance.get()->remaining();
  std::size_t resume_calls = 0;
  {
    s04_alloc::Scope allocation_guard;
    detail::StorageOperation resumed(context, retained);
    verify(resumed.lease() == retained && context->active() == retained,
        "resumed operation did not bind its retained lease");
    verify(retained->allowance.get()->remaining() == before_resume,
        "resuming an operation refilled or charged its retained allowance");
    resume_calls = s04_alloc::calls;
  }
  verify(resume_calls == 0, "resuming a retained lease allocated work state");
  verify(!context->active(), "resumed outer scope did not clear the active lease");

  {
    detail::StorageOperation fresh(context);
    verify(fresh.lease() != retained, "fresh outer operation reused a retained lease");
    verify(fresh.lease()->allowance.get()->remaining() == fresh_remaining(),
        "fresh outer operation did not receive its declared allowance");
  }
  verify(!context->active(), "fresh outer scope did not clear the active lease");
}

void ownership_rejections_and_unwinding() {
  const auto first_context = make_context(declared_limit());
  const auto foreign_context = make_context(declared_limit());
  {
    detail::StorageOperation active(first_context);
    const auto lease = active.lease();
    rejects("storage_contract", [&] {
      detail::StorageOperation foreign(foreign_context, lease);
      static_cast<void>(foreign);
    });
    verify(first_context->active() == lease && !foreign_context->active(),
        "foreign-context rejection changed active ownership");
  }

  const auto context = make_context(declared_limit());
  detail::StorageWorkLease previous;
  {
    detail::StorageOperation operation(context);
    previous = operation.lease();
  }
  {
    detail::StorageOperation active(context);
    const auto active_lease = active.lease();
    rejects("storage_contract", [&] {
      detail::StorageOperation conflict(context, previous);
      static_cast<void>(conflict);
    });
    verify(context->active() == active_lease, "conflicting-lease rejection changed the active lease");
  }

  const auto unwind_context = make_context(declared_limit());
  struct UnwindMarker {};
  bool unwound = false;
  try {
    detail::StorageOperation operation(unwind_context);
    verify(unwind_context->active() == operation.lease(), "unwinding fixture did not activate its lease");
    throw UnwindMarker{};
  } catch (const UnwindMarker&) { unwound = true; }
  verify(unwound && !unwind_context->active(), "exception unwinding left an active storage context");
}

void failed_admission_leaves_context_inactive() {
  const auto context = make_context(IndexWork{
      .scalar_fields = 1, .scalar_bytes = 1, .pointer_slots = 1, .link_actions = 1});
  rejects("storage_work_limit", [&] {
    detail::StorageOperation operation(context);
    static_cast<void>(operation);
  });
  verify(!context->active(), "zero startup budget installed an active lease");
}

void failed_allocation_leaves_context_inactive() {
  const auto context = make_context(declared_limit());
  bool caught_bad_alloc = false;
  {
    s04_alloc::Scope allocation_guard(0);
    try {
      detail::StorageOperation operation(context);
      static_cast<void>(operation);
    }
    catch (const std::bad_alloc&) { caught_bad_alloc = true; }
  }
  verify(caught_bad_alloc && s04_alloc::triggered && s04_alloc::calls == 1,
      "fresh indexed operation did not fail at its first allocation");
  verify(!context->active(), "failed lease allocation left the context active");
}
}  // namespace

int main() {
  reference_scope_is_allocation_free();
  nested_alias_and_resume_share_one_allowance();
  ownership_rejections_and_unwinding();
  failed_admission_leaves_context_inactive();
  failed_allocation_leaves_context_inactive();
  std::cout << "S04 runtime storage work: shared scopes, retained leases, rejection and allocation boundaries passed\n";
}
