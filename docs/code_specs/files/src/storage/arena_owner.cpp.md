# `src/storage/arena_owner.cpp` — block usage map

[Source](../../../../../src/storage/arena_owner.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Keep stable tuple handles and retained deleted payloads for live readers and inverse operations.

Snapshot SHA-256: `78fda8798c1a4160c78d0e5b7205ea0453e549b42f8a5522d2ae3f86067acd3e`. 17 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [arena](../../../subsystem_contracts.md#arena). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../src/storage/arena_owner.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 7–16](../../../../../src/storage/arena_owner.cpp#L7) | Callable definition: std::optional&lt;ArenaOwnerId&gt; try_new_arena_owner() noexcept | calls load, max, compare_exchange_weak; returns {}; ArenaOwnerId{value + 1}; 1 loop sites; source comment (unverified): // Relaxed ordering allocates unique IDs; it does not synchronize arena · [reviewed contract](#b0002) |
| [B0003 · 17–17](../../../../../src/storage/arena_owner.cpp#L17) | Closes surrounding scope/type. |  · [reviewed contract](#b0003) |

## B0001

[Lines 1–6](../../../../../src/storage/arena_owner.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L6:sha256:753fbcc47b6805b5f78ffcef34de4f19fa3ba7dd083dee29ab989d22aa4f2107
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/arena_owner.cpp: imports \`"arena_owner.hpp"\`, \`&lt;atomic&gt;\`, \`&lt;limits&gt;\` for compilation; opens namespace \`crown::storage::detail\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 7–16](../../../../../src/storage/arena_owner.cpp#L7); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<ArenaOwnerId> try_new_arena_owner() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate a fresh nonzero process-local ArenaOwnerId without wrap or reuse. |
| inputs / outputs | Reads a function-static atomic uint64 and retries relaxed compare_exchange_weak(value,value+1); returns nullopt after UINT64_MAX has been assigned. |
| invariants | Each successful CAS linearizes one unique increasing ID. Failed/spurious CAS updates/retries the expected value; failed later owner construction may consume an unpublished ID. Relaxed order establishes identity uniqueness only, not table/arena thread safety. |
| ownership | Only one process-local atomic counter is retained; optional result is an inline typed ID. Arena and storage authorities are distinct typed domains shared across their legacy/accounted implementations. |
| failure | The function is noexcept and exhaustion returns nullopt without formatted error text. No rollback or ID recycling occurs. |
| cost | One successful atomic increment with a contention/spurious-failure retry loop; no bounded iteration or portable lock-free guarantee is asserted. No custom heap registry or per-ID allocation is introduced. |
| Design | [src/storage/arena_owner.cpp](../../../../../src/storage/arena_owner.cpp), [src/storage/arena_owner.hpp](../../../../../src/storage/arena_owner.hpp), [src/storage/arena.cpp](../../../../../src/storage/arena.cpp), [src/storage/accounted_arena.cpp](../../../../../src/storage/accounted_arena.cpp), [tests/unit/arena_storage_test.cpp](../../../../../tests/unit/arena_storage_test.cpp), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 17–17](../../../../../src/storage/arena_owner.cpp#L17); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L17-L17:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage::detail\` at its lexical source position in src/storage/arena_owner.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
