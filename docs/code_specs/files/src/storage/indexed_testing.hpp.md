# `src/storage/indexed_testing.hpp` — block usage map

[Source](../../../../../src/storage/indexed_testing.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `0e14df520ecae19827e0c1f1cb3aaf1806570c3c9900f6c8be778f4a825420ce`. 21 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../src/storage/indexed_testing.hpp#L1) | Imports dependencies; guards repeated header inclusion; controls preprocessing; declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 11–11](../../../../../src/storage/indexed_testing.hpp#L11) | Type/record definition: enum class CollisionMode |  · [reviewed contract](#b0002) |
| [B0003 · 12–15](../../../../../src/storage/indexed_testing.hpp#L12) | Explanatory comments or spacing. | source comment (unverified): // Private to the testing storage variant. Not installed, serialized or defined · [reviewed contract](#b0003) |
| [B0004 · 16–19](../../../../../src/storage/indexed_testing.hpp#L16) | Type/record definition: class IndexedTesting | source comment (unverified): // Private to the testing storage variant. Not installed, serialized or defined · [reviewed contract](#b0004) |
| [B0005 · 20–21](../../../../../src/storage/indexed_testing.hpp#L20) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::storage::detail · [reviewed contract](#b0005) |

## B0001

[Lines 1–10](../../../../../src/storage/indexed_testing.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

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
| Design | [src/storage/indexed_testing.hpp](../../../../../src/storage/indexed_testing.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp) |

## B0002

[Lines 11–11](../../../../../src/storage/indexed_testing.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class CollisionMode
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name legacy indexed collision fixture modes. |
| inputs / outputs | native/same_bucket/same_full_hash match the testing implementation. |
| invariants | Same-bucket fixture requires directory capacity&lt;=65536; no production configuration API. |
| ownership | Fixed enum only. |
| failure | Compile-time declaration; runtime unknown modes reject in the implementation. |
| cost | No runtime work at declaration. |
| Design | [src/storage/indexed_testing.hpp](../../../../../src/storage/indexed_testing.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp) |

## B0003

[Lines 12–15](../../../../../src/storage/indexed_testing.hpp#L12); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L12-L15:sha256:be49d656b3328b9019d0426cb5212d45cd2a5bea60288250b5f272a761e806ef
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`class IndexedTesting\`: Private to the testing storage variant. Not installed, serialized or defined in the production binary; never a configurable production hash callback. The same-bucket fixture requires a maximum directory capacity &lt;=65536. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/storage/indexed_testing.hpp:L16; use that declaration for the actual input/output shape. |
| invariants | The source note states: Private to the testing storage variant. Not installed, serialized or defined in the production binary; never a configurable production hash callback. The same-bucket fixture requires a maximum directory capacity &lt;=65536. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0004

[Lines 16–19](../../../../../src/storage/indexed_testing.hpp#L16); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class IndexedTesting
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare controlled collision injection for the testing variant. |
| inputs / outputs | Mutator borrows actual backend; table facade delegates to its indexed alternative. |
| invariants | No configurable production callback; must use coherent fresh/unlocked indexed fixture. |
| ownership | No retained owner or input pointer after call. |
| failure | Wrong backend or invalid fixture mode/state is rejected by definitions; ordinary versus fixed diagnostics follow actual backend policy. |
| cost | Constant facade dispatch and fixture checks, no directory rebuild or row scan. |
| Design | [src/storage/indexed_testing.hpp](../../../../../src/storage/indexed_testing.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp) |

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
| Design | [src/storage/indexed_testing.hpp](../../../../../src/storage/indexed_testing.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [src/storage/indexed.cpp](../../../../../src/storage/indexed.cpp) |

## B0005

[Lines 20–21](../../../../../src/storage/indexed_testing.hpp#L20); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L21:sha256:05825db20eae5643716749fd9f1dad1a40400e47f28da6432edfadc3bbd3864e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage::detail\` at its lexical source position in src/storage/indexed_testing.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
