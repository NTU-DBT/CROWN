# `tests/unit/runtime_storage_work_test.cpp` — block usage map

[Source](../../../../../tests/unit/runtime_storage_work_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `78e690c0aa14dfa0044cdd52ac00e17fb3b0dac6058db6be3051ef2dba4c7980`. 203 lines partitioned into 21 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../tests/unit/runtime_storage_work_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | growth new · [reviewed contract](#b0001) |
| [B0002 · 18–20](../../../../../tests/unit/runtime_storage_work_test.cpp#L18) | Callable definition: void verify(bool value, std::string_view message) | calls std::runtime_error, std::string · [reviewed contract](#b0002) |
| [B0003 · 21–21](../../../../../tests/unit/runtime_storage_work_test.cpp#L21) | Explanatory comments or spacing. |  |
| [B0004 · 22–31](../../../../../tests/unit/runtime_storage_work_test.cpp#L22) | Callable definition: template &lt;class Function&gt; void rejects(std::string_view code, Function&& function) | calls function, verify, code · [reviewed contract](#b0004) |
| [B0005 · 32–32](../../../../../tests/unit/runtime_storage_work_test.cpp#L32) | Explanatory comments or spacing. |  |
| [B0006 · 33–36](../../../../../tests/unit/runtime_storage_work_test.cpp#L33) | Callable definition: IndexWork declared_limit() | calls ; returns IndexWork{.structural_steps = 3, .scalar_fields = 4, .scalar_bytes = 5, · [reviewed contract](#b0006) |
| [B0007 · 37–37](../../../../../tests/unit/runtime_storage_work_test.cpp#L37) | Explanatory comments or spacing. |  |
| [B0008 · 38–41](../../../../../tests/unit/runtime_storage_work_test.cpp#L38) | Callable definition: IndexWork fresh_remaining() | calls ; returns IndexWork{.structural_steps = 2, .scalar_fields = 4, .scalar_bytes = 5, · [reviewed contract](#b0008) |
| [B0009 · 42–46](../../../../../tests/unit/runtime_storage_work_test.cpp#L42) | Callable definition: std::shared_ptr&lt;detail::StorageWorkContext&gt; make_context(IndexWork limit) | calls crown::resource::MemoryAccount::create; returns crown::resource::make_accounted_shared&lt;detail::StorageWorkContext&gt;(account,; growth make_accounted_shared · [reviewed contract](#b0009) |
| [B0010 · 47–47](../../../../../tests/unit/runtime_storage_work_test.cpp#L47) | Explanatory comments or spacing. |  |
| [B0011 · 48–61](../../../../../tests/unit/runtime_storage_work_test.cpp#L48) | Callable definition: void reference_scope_is_allocation_free() | calls operation, lease, detail::shared_storage_work, verify · [reviewed contract](#b0011) |
| [B0012 · 62–62](../../../../../tests/unit/runtime_storage_work_test.cpp#L62) | Explanatory comments or spacing. |  |
| [B0013 · 63–126](../../../../../tests/unit/runtime_storage_work_test.cpp#L63) | Callable definition: void nested_alias_and_resume_share_one_allowance() | calls make_context, declared_limit, outer, lease · [reviewed contract](#b0013) |
| [B0014 · 127–127](../../../../../tests/unit/runtime_storage_work_test.cpp#L127) | Explanatory comments or spacing. |  |
| [B0015 · 128–167](../../../../../tests/unit/runtime_storage_work_test.cpp#L128) | Callable definition: void ownership_rejections_and_unwinding() | calls make_context, declared_limit, active, lease · [reviewed contract](#b0015) |
| [B0016 · 168–168](../../../../../tests/unit/runtime_storage_work_test.cpp#L168) | Explanatory comments or spacing. |  |
| [B0017 · 169–177](../../../../../tests/unit/runtime_storage_work_test.cpp#L169) | Callable definition: void failed_admission_leaves_context_inactive() | calls make_context, rejects, operation, verify · [reviewed contract](#b0017) |
| [B0018 · 178–178](../../../../../tests/unit/runtime_storage_work_test.cpp#L178) | Explanatory comments or spacing. |  |
| [B0019 · 179–193](../../../../../tests/unit/runtime_storage_work_test.cpp#L179) | Callable definition: void failed_allocation_leaves_context_inactive() | calls make_context, declared_limit, allocation_guard, operation · [reviewed contract](#b0019) |
| [B0020 · 194–195](../../../../../tests/unit/runtime_storage_work_test.cpp#L194) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0020) |
| [B0021 · 196–203](../../../../../tests/unit/runtime_storage_work_test.cpp#L196) | Callable definition: int main() | calls reference_scope_is_allocation_free, nested_alias_and_resume_share_one_allowance, ownership_rejections_and_unwinding, failed_admission_leaves_context_inactive · [reviewed contract](#b0021) |

## B0001

[Lines 1–17](../../../../../tests/unit/runtime_storage_work_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:f5194f20dc5225faae6eb6e107350fb4112fdf39d1cb7a3174e5fddc6e3beffe
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare runtime_storage_work_test.cpp: include "storage_work.hpp", "index_allocation.hpp", &lt;cstdint&gt;, &lt;iostream&gt;, &lt;memory&gt;, &lt;new&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;string_view&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 18–20](../../../../../tests/unit/runtime_storage_work_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void verify(bool value, std::string_view message) {
  if (!value) throw std::runtime_error(std::string(message));
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | String-view verification helper that constructs diagnostics only on failure. |
| inputs / outputs | Accepts a Boolean and string_view; on false constructs std::string(message) for std::runtime_error, otherwise returns. |
| invariants | The view is consumed synchronously; no diagnostic string is built by this body on the true path. |
| ownership | Borrows the message view for the call; exception owns its text. |
| failure | False throws std::runtime_error; no exception is caught. |
| cost | One branch. Message copying/allocation is failure-only in the helper; the caller may create the underlying view separately. |
| Design | [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0004

[Lines 22–31](../../../../../tests/unit/runtime_storage_work_test.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
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

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require one callable operation to throw the expected storage error code. |
| inputs / outputs | Binds Function&& but calls the named function() lvalue, catches crown::Error, and verifies its code against a string_view. |
| invariants | A matching code sets rejected=true; missing errors and mismatched codes fail through verify. |
| ownership | Function captures and code view remain caller-owned; this helper retains neither after returning. |
| failure | Catches Error only. A verify exception, bad_alloc, or unrelated exception propagates; it is not reclassified. |
| cost | One operation invocation and one code comparison. The forwarded-reference parameter is not invoked with std::forward; no allocation counter wraps this helper. |
| Design | [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0006

[Lines 33–36](../../../../../tests/unit/runtime_storage_work_test.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWork declared_limit() {
  return IndexWork{.structural_steps = 3, .scalar_fields = 4, .scalar_bytes = 5,
      .pointer_slots = 6, .link_actions = 7};
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the fixture five-domain indexed-work ceiling. |
| inputs / outputs | Returns IndexWork{structural_steps=3, scalar_fields=4, scalar_bytes=5, pointer_slots=6, link_actions=7}. |
| invariants | All five independent domains have fixed literal ceilings; this is the fixture’s fresh-operation grant. |
| ownership | Returns a small value object; it owns no StorageWorkContext or allowance. |
| failure | No failure branch is present in the returned literal construction. |
| cost | Five scalar assignments; no indexed operation or allocation is performed. |
| Design | [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0008

[Lines 38–41](../../../../../tests/unit/runtime_storage_work_test.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
IndexWork fresh_remaining() {
  return IndexWork{.structural_steps = 2, .scalar_fields = 4, .scalar_bytes = 5,
      .pointer_slots = 6, .link_actions = 7};
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return expected remaining balance after fresh startup admission. |
| inputs / outputs | Returns expected remaining IndexWork{structural_steps=2, scalar_fields=4, scalar_bytes=5, pointer_slots=6, link_actions=7}. |
| invariants | Only structural_steps is one below declared_limit, matching the new operation’s startup admission; other domains remain equal. |
| ownership | Returns a value for comparison and retains no grant. |
| failure | No failure branch is present in the helper. |
| cost | Five scalar assignments; the value encodes expected test state, not a runtime refill. |
| Design | [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0009

[Lines 42–46](../../../../../tests/unit/runtime_storage_work_test.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::shared_ptr<detail::StorageWorkContext> make_context(IndexWork limit) {
  auto account=crown::resource::MemoryAccount::create(1024*1024);
  return crown::resource::make_accounted_shared<detail::StorageWorkContext>(account,
      crown::resource::MemoryPurpose::support_metadata,account,std::optional<IndexWork>{limit});
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a one-megabyte accounted indexed StorageWorkContext. |
| inputs / outputs | Creates a 1 MiB MemoryAccount and returns an accounted shared StorageWorkContext with support_metadata purpose and the supplied optional IndexWork limit. |
| invariants | The context is initialized with that finite grant and becomes shared through make_accounted_shared. |
| ownership | Returned shared_ptr owns the accounted context and retains its MemoryAccount; the function argument is only a value limit. |
| failure | Account/context allocation or construction failure propagates; it is outside any Scope used by later fault tests. |
| cost | One account setup and one accounted shared-object construction. This fixture setup is not counted as work in the tested operation scopes. |
| Design | [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0011

[Lines 48–61](../../../../../tests/unit/runtime_storage_work_test.cpp#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
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

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check reference-backend operation accessors create no indexed lease under the declared C++ new hook. |
| inputs / outputs | Uses a null StorageWorkContext to construct StorageOperation, reads its lease/work accessors and shared_storage_work, then records hook calls. |
| invariants | The reference scope must expose no lease, no work pointer and no shared allowance; the default allocation hook must report zero C++ new calls. |
| ownership | The null shared_ptr is local; the operation is scoped and no allowance/context is created. |
| failure | Any exception propagates. The final verify fails if accessors expose indexed state or hook count is nonzero. |
| cost | Constructs one reference-mode operation and reads four accessors. Hook evidence covers its defined C++ new overload set only, not malloc, requested bytes, CPU or all library internals. |
| Design | [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0013

[Lines 63–126](../../../../../tests/unit/runtime_storage_work_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
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

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify nested and resumed scopes share one five-domain allowance and one lease. |
| inputs / outputs | Creates one limited context, enters an outer operation, performs two nested admissions, checks a shared alias, then resumes the retained lease and opens a fresh operation. |
| invariants | Fresh startup reduces structural 3 to 2. The two nested admissions consume the same five-domain balance; alias and compact pointer identify that lease. Resume does not refill; a later fresh operation receives a different lease and the original balance. |
| ownership | The outer operation installs and clears context.active; retained shared lease survives the scope. alias is another shared_ptr to retained legacy allowance; context and lease remain distinct owners. |
| failure | Each mismatch throws through verify. Destruction must clear active state after outer, resumed and fresh scopes; the test does not inject constructor allocation failure here. |
| cost | Two explicit admissions across five domains and repeated accessor/equality checks. Nested and resumed blocks assert zero C++ new attempts; no byte, CPU or allocator-wide grant interpretation is measured. |
| Design | [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0015

[Lines 128–167](../../../../../tests/unit/runtime_storage_work_test.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
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

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check foreign/conflicting lease rejection and RAII cleanup during unwinding. |
| inputs / outputs | Uses two contexts to reject a foreign retained lease, then a same-context stale lease conflict; finally throws a marker inside an active scope and checks RAII cleanup. |
| invariants | Rejected construction leaves the active owner unchanged or foreign context inactive; destructor clears active state during normal exit and stack unwinding. |
| ownership | Contexts own their accounted state; active and retained handles share lease state. Scope objects temporarily set active ownership. |
| failure | The two constructor failures must carry storage_contract. The local UnwindMarker is caught only by this test to confirm destructor behavior. |
| cost | Creates three contexts, makes two rejected StorageOperation attempts, and unwinds one active scope. No allocation hook or exhaustive fault sweep is present. |
| Design | [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0017

[Lines 169–177](../../../../../tests/unit/runtime_storage_work_test.cpp#L169); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void failed_admission_leaves_context_inactive() {
  const auto context = make_context(IndexWork{
      .scalar_fields = 1, .scalar_bytes = 1, .pointer_slots = 1, .link_actions = 1});
  rejects("storage_work_limit", [&] {
    detail::StorageOperation operation(context);
    static_cast<void>(operation);
  });
  verify(!context->active(), "zero startup budget installed an active lease");
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Show zero structural startup allowance fails before activating a lease. |
| inputs / outputs | Creates a context with zero structural_steps but positive other domains; rejects fresh StorageOperation with storage_work_limit and checks it stayed inactive. |
| invariants | A fresh operation must consume structural startup before publishing an active lease; a later check observes no active context. |
| ownership | The context remains owned by local shared_ptr and is not activated on the failure path. |
| failure | rejects catches the expected Error code; if construction succeeds or reports another code, verify throws. |
| cost | One failed admission using a prebuilt context. The helper asserts inactive state but does not count allocations or measure remaining domains beyond their setup literals. |
| Design | [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0019

[Lines 179–193](../../../../../tests/unit/runtime_storage_work_test.cpp#L179); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
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

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Inject failure at the first covered allocation in a fresh indexed operation. |
| inputs / outputs | Prebuilds a limited context, sets Scope(0), attempts one fresh StorageOperation, catches bad_alloc, and checks trigger=true, calls=1, and inactive context. |
| invariants | Only the first covered allocation point is faulted; successful context/account setup occurs before the scope. |
| ownership | Local context owns storage; failed operation must not leave an installed lease. |
| failure | Expected exception is std::bad_alloc from the hook; a different error or successful construction fails the final verify. |
| cost | One attempted indexed-operation construction at failure position zero. This proves one first-allocation cleanup case, not every allocation position or allocator ABI path. |
| Design | [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |

## B0020

[Lines 194–195](../../../../../tests/unit/runtime_storage_work_test.cpp#L194); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L194-L195:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in runtime_storage_work_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [docs/storage.md](../../../../storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0021

[Lines 196–203](../../../../../tests/unit/runtime_storage_work_test.cpp#L196); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
  reference_scope_is_allocation_free();
  nested_alias_and_resume_share_one_allowance();
  ownership_rejections_and_unwinding();
  failed_admission_leaves_context_inactive();
  failed_allocation_leaves_context_inactive();
  std::cout << "S04 runtime storage work: shared scopes, retained leases, rejection and allocation boundaries passed\n";
}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the storage-work scope, alias, ownership, admission, and allocation cases. |
| inputs / outputs | Runs the null reference scope, nested/resume allowance, ownership/unwinding, failed admission and first-allocation failure fixtures in sequence. |
| invariants | There is no outer try/catch; all helper assertions must return before the success line is printed. |
| ownership | Each fixture owns local context/lease state and releases it before the next helper begins. |
| failure | Exceptions escape main and fail the process; this test does not translate failures at top level. |
| cost | Orchestrates five finite scenarios; only the named Scope checks use the C++ new hook. No native execution is performed in this review. |
| Design | [tests/unit/runtime_storage_work_test.cpp](../../../../../tests/unit/runtime_storage_work_test.cpp), [src/runtime/storage_work.hpp](../../../../../src/runtime/storage_work.hpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md) |
