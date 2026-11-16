# `src/storage/table_testing.hpp` — block usage map

[Source](../../../../../src/storage/table_testing.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `ce4e69ce6c8b2927e456aa011d3a3b573e87ac440778b1492e56a87625430981`. 13 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/storage/table_testing.hpp#L1) | Imports dependencies; guards repeated header inclusion; controls preprocessing; declares namespace scope; declares values/defaults or compile-time conditions. | source comment (unverified): // Delegation rejects the reference backend before changing indexed fixture state. · [reviewed contract](#b0001) |
| [B0002 · 9–12](../../../../../src/storage/table_testing.hpp#L9) | Type/record definition: class StorageTableTesting | source comment (unverified): // Delegation rejects the reference backend before changing indexed fixture state. · [reviewed contract](#b0002) |
| [B0003 · 13–13](../../../../../src/storage/table_testing.hpp#L13) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::storage::detail · [reviewed contract](#b0003) |

## B0001

[Lines 1–8](../../../../../src/storage/table_testing.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a coherent private testing interface only. |
| inputs / outputs | Compile guard requires CROWN_STORAGE_TESTING==1; imports actual backend headers and declares only private test helpers. |
| invariants | Not installed or serialized. Corresponding mutator definitions exist only in their coherent testing variants; this is not a production hash callback or admission API. |
| ownership | Declarations own no live backend; call-specific inputs are borrowed. |
| failure | Mismatched/missing macro triggers compile-time #error; declarations add no runtime exception layer. |
| cost | No runtime work at inclusion; testing definitions/inline construction run only in explicit tests. |
| Design | [src/storage/table_testing.hpp](../../../../../src/storage/table_testing.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp) |

## B0002

[Lines 9–12](../../../../../src/storage/table_testing.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class StorageTableTesting
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare controlled collision injection for the testing variant. |
| inputs / outputs | Mutator borrows actual backend; table facade delegates to its indexed alternative. |
| invariants | No configurable production callback; must use coherent fresh/unlocked indexed fixture. |
| ownership | No retained owner or input pointer after call. |
| failure | Wrong backend or invalid fixture mode/state is rejected by definitions; ordinary versus fixed diagnostics follow actual backend policy. |
| cost | Constant facade dispatch and fixture checks, no directory rebuild or row scan. |
| Design | [src/storage/table_testing.hpp](../../../../../src/storage/table_testing.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp) |

```text
static void collisions(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select deterministic collisions in the actual test backend. |
| inputs / outputs | Table facade checks indexed alternative, then backend validates fresh/unlocked state/mode and the same_bucket capacity domain. |
| invariants | Only explicit testing state is changed after checks; public/native operational grants remain separate. |
| ownership | Borrows mutable fixture for call; retains no handle. |
| failure | Contract/state failures propagate with existing legacy Error or native IndexFailure; no catch/retry. |
| cost | Fixed checks/set only; no row/hash callback allocation. |
| Design | [src/storage/table_testing.hpp](../../../../../src/storage/table_testing.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp) |

## B0003

[Lines 13–13](../../../../../src/storage/table_testing.hpp#L13); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L13:sha256:1e3632eae880239aa87e442a0a0179d95241534e7c445ee150a3c1c2e53599cd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage::detail\` at its lexical source position in src/storage/table_testing.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
