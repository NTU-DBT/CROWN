# `src/storage/owner.cpp` — block usage map

[Source](../../../../../src/storage/owner.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `aae1b28366445960ae019acfa6857ead7eab3c19cade2769e3a399715149e333`. 28 lines partitioned into 4 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–9](../../../../../src/storage/owner.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 10–21](../../../../../src/storage/owner.cpp#L10) | Callable definition: std::optional&lt;StorageOwnerId&gt; try_new_storage_owner() noexcept | calls load, max, compare_exchange_weak; returns {}; StorageOwnerId{value + 1}; 1 loop sites; source comment (unverified): // Only identity uniqueness is synchronized here, not table payloads. · [reviewed contract](#b0002) |
| [B0003 · 22–26](../../../../../src/storage/owner.cpp#L22) | Callable definition: StorageOwnerId new_storage_owner() | calls try_new_storage_owner, Error; returns *owner · [reviewed contract](#b0003) |
| [B0004 · 27–28](../../../../../src/storage/owner.cpp#L27) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::storage::detail · [reviewed contract](#b0004) |

## B0001

[Lines 1–9](../../../../../src/storage/owner.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L9:sha256:3552a4dd50f1db59108c484d98b7b98978b01b8fbba41eef4cc0ed737330dbfc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/owner.cpp: imports \`"owner.hpp"\`, \`"crown/api/error.hpp"\`, \`&lt;atomic&gt;\`, \`&lt;cstdint&gt;\`, \`&lt;limits&gt;\` for compilation; opens namespace \`crown::storage::detail\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0002

[Lines 10–21](../../../../../src/storage/owner.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::optional<StorageOwnerId> try_new_storage_owner() noexcept {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Allocate a fresh nonzero process-local StorageOwnerId without wrap or reuse. |
| inputs / outputs | Reads a function-static atomic uint64 and retries relaxed compare_exchange_weak(value,value+1); returns nullopt after UINT64_MAX has been assigned. |
| invariants | Each successful CAS linearizes one unique increasing ID. Failed/spurious CAS updates/retries the expected value; failed later owner construction may consume an unpublished ID. Relaxed order establishes identity uniqueness only, not table/arena thread safety. |
| ownership | Only one process-local atomic counter is retained; optional result is an inline typed ID. Arena and storage authorities are distinct typed domains shared across their legacy/accounted implementations. |
| failure | The function is noexcept and exhaustion returns nullopt without formatted error text. No rollback or ID recycling occurs. |
| cost | One successful atomic increment with a contention/spurious-failure retry loop; no bounded iteration or portable lock-free guarantee is asserted. No custom heap registry or per-ID allocation is introduced. |
| Design | [src/storage/owner.cpp](../../../../../src/storage/owner.cpp), [src/storage/owner.hpp](../../../../../src/storage/owner.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [tests/unit/arena_storage_test.cpp](../../../../../tests/unit/arena_storage_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 22–26](../../../../../src/storage/owner.cpp#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
StorageOwnerId new_storage_owner() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate storage identity exhaustion at the standalone public diagnostic boundary. |
| inputs / outputs | Calls try_new_storage_owner; returns its typed ID or throws Error(storage_overflow). |
| invariants | This wrapper does not own a second counter, reuse exhausted identities or roll back an ID consumed before a later construction failure. |
| ownership | The success result is inline; failure Error owns its code/message text. |
| failure | Exhaustion throws the public owning diagnostic, which can itself fail allocation; there is no catch or retry layer. |
| cost | Success adds one optional test to the shared CAS authority. Only failure constructs diagnostic strings/exception state; no success heap allocation is added by this wrapper. |
| Design | [src/storage/owner.cpp](../../../../../src/storage/owner.cpp), [src/storage/owner.hpp](../../../../../src/storage/owner.hpp), [src/storage/reference.cpp](../../../../../src/storage/reference.cpp), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp), [tests/unit/arena_storage_test.cpp](../../../../../tests/unit/arena_storage_test.cpp), [include/crown/storage/index_work.hpp](../../../../../include/crown/storage/index_work.hpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 27–28](../../../../../src/storage/owner.cpp#L27); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L27-L28:sha256:05825db20eae5643716749fd9f1dad1a40400e47f28da6432edfadc3bbd3864e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage::detail\` at its lexical source position in src/storage/owner.cpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
