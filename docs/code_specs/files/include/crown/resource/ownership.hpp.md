# `include/crown/resource/ownership.hpp` — block usage map

[Source](../../../../../../include/crown/resource/ownership.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Fund native owners and nested storage from one finite requested-byte account.

Snapshot SHA-256: `daf3041154650172cc355a52e9b9f36e6c430b12d25ffcb5aefe8367d8aa3b5c`. 76 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [memory](../../../../subsystem_contracts.md#memory). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [docs/memory_reports.md](../../../../../memory_reports.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../../include/crown/resource/ownership.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Accounted ownership bridge. These factories account object storage and, · [reviewed contract](#b0001) |
| [B0002 · 14–36](../../../../../../include/crown/resource/ownership.hpp#L14) | Type/record definition: template&lt;class T&gt; class MemoryDelete | guard static_assert(std::is_object_v&lt;T&gt; && !std::is_array_v&lt;T&gt; && !std::is_const_v&lt;T&gt;);; returns allocator_.account(); allocator_.purpose(); source comment (unverified): // Accounted ownership bridge. These factories account object storage and, · [reviewed contract](#b0002) |
| [B0003 · 37–39](../../../../../../include/crown/resource/ownership.hpp#L37) | declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 40–53](../../../../../../include/crown/resource/ownership.hpp#L40) | Callable definition: template&lt;class T, class... Args&gt; \[\[nodiscard\]\] AccountedUnique&lt;T&gt; make_accounted_unique( MemoryAttribution attribution, const Mem… | calls static_assert, allocator, allocate, std::construct_at; guard static_assert(std::is_nothrow_destructible_v&lt;T&gt;);; returns AccountedUnique&lt;T&gt;(object, MemoryDelete&lt;T&gt;(allocator)); growth allocate, make_accounted_unique · [reviewed contract](#b0004) |
| [B0005 · 54–58](../../../../../../include/crown/resource/ownership.hpp#L54) | Callable definition: template&lt;class T, class... Args&gt; \[\[nodiscard\]\] AccountedUnique&lt;T&gt; make_accounted_unique( const MemoryAccount& account, MemoryPurp… | calls ; returns make_accounted_unique&lt;T&gt;(MemoryAttribution{}, account, purpose, std::forward&lt;Args&gt;(args)...); growth make_accounted_unique · [reviewed contract](#b0005) |
| [B0006 · 59–59](../../../../../../include/crown/resource/ownership.hpp#L59) | Explanatory comments or spacing. |  |
| [B0007 · 60–69](../../../../../../include/crown/resource/ownership.hpp#L60) | Callable definition: template&lt;class T, class... Args&gt; \[\[nodiscard\]\] std::shared_ptr&lt;T&gt; make_accounted_shared( MemoryAttribution attribution, const Mem… | calls static_assert; guard static_assert(std::is_object_v&lt;T&gt; && !std::is_array_v&lt;T&gt; && !std::is_const_v&lt;T&gt;);; returns std::allocate_shared&lt;T&gt;(MemoryAllocator&lt;T&gt;(account, purpose, attribution), std::forward&lt;Args&gt;(args)…; growth allocate_shared, make_accounted_shared; source comment (unverified): // Rebinding preserves account, purpose and attribution. The control block's stored · [reviewed contract](#b0007) |
| [B0008 · 70–74](../../../../../../include/crown/resource/ownership.hpp#L70) | Callable definition: template&lt;class T, class... Args&gt; \[\[nodiscard\]\] std::shared_ptr&lt;T&gt; make_accounted_shared( const MemoryAccount& account, MemoryPurp… | calls ; returns make_accounted_shared&lt;T&gt;(MemoryAttribution{}, account, purpose, std::forward&lt;Args&gt;(args)...); growth make_accounted_shared · [reviewed contract](#b0008) |
| [B0009 · 75–76](../../../../../../include/crown/resource/ownership.hpp#L75) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::resource · [reviewed contract](#b0009) |

## B0001

[Lines 1–13](../../../../../../include/crown/resource/ownership.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:c3a19d3d2756babb65214c78146c5544e65ef8c74b119d146d4cf4ee5d81e092
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/resource/ownership.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/resource/allocator.hpp"\`, \`&lt;memory&gt;\`, \`&lt;type_traits&gt;\`, \`&lt;utility&gt;\` for compilation; opens namespace \`crown::resource\`. Source comment: Accounted ownership bridge. These factories account object storage and, for shared ownership, the library's rebound control-block allocation. They do not inject an allocator into arbitrary members. Constructors must receive the same account explicitly for every nested allocation they own. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The source note says: Accounted ownership bridge. These factories account object storage and, for shared ownership, the library's rebound control-block allocation. They do not inject an allocator into arbitrary members. Constructors must receive the same account explicitly for every nested allocation they own. Prose alone does not enforce the rule. |
| ownership | The source comment describes this adjacent lifetime/account boundary: Accounted ownership bridge. These factories account object storage and, for shared ownership, the library's rebound control-block allocation. They do not inject an allocator into arbitrary members. Constructors must receive the same account explicitly for every nested allocation they own. The comment creates no owner; member types and callers determine actual retention. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0002

[Lines 14–36](../../../../../../include/crown/resource/ownership.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class MemoryDelete {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry the exact allocator required to destroy one accounted unique object. |
| inputs / outputs | A stored MemoryAllocator&lt;T&gt; destroys a nonnull complete T then deallocates one object; null is harmless. |
| invariants | T must be nothrow-destructible at deletion instantiation; forward declaration is permitted in the owning public header. |
| ownership | Deleter retains the original account/purpose/attribution until object destruction and raw release finish. |
| failure | Noexcept cleanup; invalid allocator ownership is an internal contract failure. |
| cost | One T destructor plus O(1) account deallocation; nested T cleanup retains its own actual costs. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/storage_journal.md](../../../../../storage_journal.md) |

```text
void set_lifetime(T* pointer,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reclassify a live accounted unique object through its embedded allocator. |
| inputs / outputs | Object pointer and destination lifetime classify the exact one-object allocation. |
| invariants | Pointer must still be owned by this deleter; T suballocations are not recursively relabeled. |
| ownership | No ownership transfer and no new account. |
| failure | The allocator validates lifetime and original metadata; may raise fixed contract failure. |
| cost | O(1) direct block classification, no ledger scan. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/storage_journal.md](../../../../../storage_journal.md) |

## B0003

[Lines 37–39](../../../../../../include/crown/resource/ownership.hpp#L37); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using AccountedUnique =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind a unique object pointer to the account-aware destruction/deallocation protocol. |
| inputs / outputs | AccountedUnique&lt;T&gt; names unique_ptr&lt;T, MemoryDelete&lt;T&gt;&gt;; factory-created values include the original allocator in the deleter. |
| invariants | Forward-declared T is allowed in an owner header, but deletion requires complete nothrow-destructible T. Raw pointer ownership must match that deleter. |
| ownership | The unique owner transfers T and its allocator together; the deleter retains the controller even if an external account facade closes. |
| failure | Deletion is noexcept under the stored allocator contract; T construction failures are handled by the factory before a unique owner is published. |
| cost | The alias adds no allocation/control block; destruction costs T's actual cleanup plus one direct account deallocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

## B0004

[Lines 40–53](../../../../../../include/crown/resource/ownership.hpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] AccountedUnique<T> make_accounted_unique(
    MemoryAttribution
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate and construct a single native owner with the allocator embedded in its deleter. |
| inputs / outputs | Attribution/account/purpose and forwarded constructor arguments in; AccountedUnique&lt;T&gt; out. |
| invariants | T must be nonthrowing-destructible. The factory does not inject allocators into arbitrary members. |
| ownership | The returned unique owner retains exactly the original MemoryAllocator and destroys/deallocates with it. |
| failure | If construction throws after allocation, the catch releases that unconstructed storage before rethrowing; this is necessary partial-construction cleanup. |
| cost | One object allocation plus T construction/nested costs. Move/destruction require no new owner allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md) |

## B0005

[Lines 54–58](../../../../../../include/crown/resource/ownership.hpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] AccountedUnique<T> make_accounted_unique(
    const MemoryAccount& account,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a query-attributed unique owner through the single attributed factory. |
| inputs / outputs | Account, purpose and perfectly forwarded constructor arguments use MemoryAttribution{} (query:0). |
| invariants | The overload introduces no account, extra allocation or duplicate error boundary; all T and allocator constraints come from the attributed implementation. |
| ownership | The returned owner retains the exact source allocator and cap; nested members still need explicit account arguments. |
| failure | The attributed factory performs allocation, partial-construction cleanup and rethrow unchanged. |
| cost | Fixed forwarding work plus the one-object factory and T/nested construction costs. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/ownership.hpp](../../../../../../include/crown/resource/ownership.hpp) |

## B0007

[Lines 60–69](../../../../../../include/crown/resource/ownership.hpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::shared_ptr<T> make_accounted_shared(
    MemoryAttribution
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct shared native ownership with its actual rebound control block funded. |
| inputs / outputs | Attribution/account/purpose and constructor arguments produce shared_ptr&lt;T&gt; through allocate_shared. |
| invariants | T is a nonarray, nonconst, nothrow-destructible object. Nested allocations must explicitly receive this same account; allocator rebinding does not reach arbitrary members. |
| ownership | Shared object/control allocation and stored allocator keep the original controller through final weak release. |
| failure | Allocation/construction exceptions propagate through allocate_shared cleanup; no duplicate manual catch layer. |
| cost | Actual implementation allocation(s) plus T construction; copying a resulting shared_ptr adds no payload allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/storage_journal.md](../../../../../storage_journal.md) |

## B0008

[Lines 70–74](../../../../../../include/crown/resource/ownership.hpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::shared_ptr<T> make_accounted_shared(
    const MemoryAccount& account,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct query-attributed shared ownership without another wrapper/control allocation. |
| inputs / outputs | Account, purpose and forwarded constructor arguments call the attributed allocate_shared bridge with query:0. |
| invariants | No fresh allowance or second catch is introduced; the attributed factory retains all object-type and destruction requirements. |
| ownership | The resulting shared/weak control ownership preserves the original account through the stored rebound allocator. |
| failure | Allocation/construction failures propagate through allocate_shared's existing cleanup. |
| cost | Fixed forwarding work plus actual allocate_shared/T construction costs; no second factory allocation. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [include/crown/resource/ownership.hpp](../../../../../../include/crown/resource/ownership.hpp) |

## B0009

[Lines 75–76](../../../../../../include/crown/resource/ownership.hpp#L75); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L75-L76:sha256:dac88a67995b7afa420dbeca9b79a3d6aa0eeffa831dda093f93c62eb2b7b46f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::resource\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::resource\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::resource\` at its lexical source position in include/crown/resource/ownership.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::resource\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |
