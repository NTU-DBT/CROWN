# `include/crown/resource/owner_allocator.hpp` — block usage map

[Source](../../../../../../include/crown/resource/owner_allocator.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Fund native owners and nested storage from one finite requested-byte account.

Snapshot SHA-256: `a4ffc6b125304784f3796a0e47597181a1c24a2e78c3577b00db263111d5476d`. 33 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [memory](../../../../subsystem_contracts.md#memory). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [docs/memory_reports.md](../../../../../memory_reports.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../../include/crown/resource/owner_allocator.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // For transferable result ownership. Assignment/swap adopt the source's · [reviewed contract](#b0001) |
| [B0002 · 11–31](../../../../../../include/crown/resource/owner_allocator.hpp#L11) | Type/record definition: template&lt;class T&gt; class OwnerAllocator:public MemoryAllocator&lt;T&gt; | returns *this; MemoryAllocator&lt;T&gt;::operator==(static_cast&lt;const MemoryAllocator&lt;U&gt;&&gt;(other)); source comment (unverified): // For transferable result ownership. Assignment/swap adopt the source's · [reviewed contract](#b0002) |
| [B0003 · 32–33](../../../../../../include/crown/resource/owner_allocator.hpp#L32) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::resource · [reviewed contract](#b0003) |

## B0001

[Lines 1–10](../../../../../../include/crown/resource/owner_allocator.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:fefa0adcfef2e7fc975a1a8cbc076a933caa300e6ddd840c899052b8087c2b6a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/resource/owner_allocator.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/resource/allocator.hpp"\` for compilation; opens namespace \`crown::resource\`. Source comment: For transferable result ownership. Assignment/swap adopt the source's original account and attribution along with its storage; no new allowance is created. Maintained tables/state must keep using nonpropagating MemoryAllocator so assigning another value cannot replace their bound query budget. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The source note says: For transferable result ownership. Assignment/swap adopt the source's original account and attribution along with its storage; no new allowance is created. Maintained tables/state must keep using nonpropagating MemoryAllocator so assigning another value cannot replace their bound query budget. Prose alone does not enforce the rule. |
| ownership | The source comment describes this adjacent lifetime/account boundary: For transferable result ownership. Assignment/swap adopt the source's original account and attribution along with its storage; no new allowance is created. Maintained tables/state must keep using nonpropagating MemoryAllocator so assigning another value cannot replace their bound query budget. The comment creates no owner; member types and callers determine actual retention. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0002

[Lines 11–31](../../../../../../include/crown/resource/owner_allocator.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class OwnerAllocator:public MemoryAllocator<T> {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allow transferable result containers to carry their original allocator with storage ownership. |
| inputs / outputs | Inherits bound allocation, declares true copy/move/swap propagation, preserves exact rebind type, and compares via the base account/purpose/attribution identity. |
| invariants | Assignment/swap can adopt a source allocator. Bound maintained state must use nonpropagating MemoryAllocator instead so another result cannot replace its query authority. |
| ownership | Allocator copying retains the existing account; container storage transfer never creates another allowance. Empty defaults stay unbound until supplied/adopted. |
| failure | Metadata operations are noexcept; inherited allocation/validation retains its checked behavior. Element construction/allocation failures belong to the actual container operation. |
| cost | O(1) allocator metadata/reference work; container copies can allocate/copy elements, move assignment may destroy old destination contents, and swap exchanges owners without cloning payload. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/verification/s05-epoch-arrays-2026-11-09.md](../../../../../verification/s05-epoch-arrays-2026-11-09.md), [include/crown/resource/allocator.hpp](../../../../../../include/crown/resource/allocator.hpp) |

## B0003

[Lines 32–33](../../../../../../include/crown/resource/owner_allocator.hpp#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L33:sha256:b7629116d5fd92de6aade250ce6a11a7bc7514263ea542158d2c251b26656e66
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::resource\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::resource\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::resource\` at its lexical source position in include/crown/resource/owner_allocator.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::resource\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/query_memory.md](../../../../../query_memory.md), [docs/memory_accounts.md](../../../../../memory_accounts.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |
