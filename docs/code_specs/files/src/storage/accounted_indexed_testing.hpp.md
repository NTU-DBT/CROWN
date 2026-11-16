# `src/storage/accounted_indexed_testing.hpp` — block usage map

[Source](../../../../../src/storage/accounted_indexed_testing.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `b19059454d54a179806f84b2171a426e116ff0e23331779cc837d1aec7e002be`. 15 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../src/storage/accounted_indexed_testing.hpp#L1) | Imports dependencies; guards repeated header inclusion; controls preprocessing; declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 7–7](../../../../../src/storage/accounted_indexed_testing.hpp#L7) | Type/record definition: enum class AccountedCollisionMode |  · [reviewed contract](#b0002) |
| [B0003 · 8–8](../../../../../src/storage/accounted_indexed_testing.hpp#L8) | Explanatory comments or spacing. | source comment (unverified): // Collision setup requires fresh/unlocked state; counter seeding requires unlock. · [reviewed contract](#b0003) |
| [B0004 · 9–14](../../../../../src/storage/accounted_indexed_testing.hpp#L9) | Type/record definition: class AccountedIndexedTesting | source comment (unverified): // Collision setup requires fresh/unlocked state; counter seeding requires unlock. · [reviewed contract](#b0004) |
| [B0005 · 15–15](../../../../../src/storage/accounted_indexed_testing.hpp#L15) | Closes surrounding scope/type. |  · [reviewed contract](#b0005) |

## B0001

[Lines 1–6](../../../../../src/storage/accounted_indexed_testing.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose a coherent private testing interface only. |
| inputs / outputs | Compile guard requires CROWN_ACCOUNTED_INDEXED_TESTING==1; imports actual backend headers and declares only private test helpers. |
| invariants | Not installed or serialized. Corresponding mutator definitions exist only in their coherent testing variants; this is not a production hash callback or admission API. |
| ownership | Declarations own no live backend; call-specific inputs are borrowed. |
| failure | Mismatched/missing macro triggers compile-time #error; declarations add no runtime exception layer. |
| cost | No runtime work at inclusion; testing definitions/inline construction run only in explicit tests. |
| Design | [src/storage/accounted_indexed_testing.hpp](../../../../../src/storage/accounted_indexed_testing.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp) |

## B0002

[Lines 7–7](../../../../../src/storage/accounted_indexed_testing.hpp#L7); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class AccountedCollisionMode
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name private native collision fixture modes. |
| inputs / outputs | native/same_bucket/same_full_hash are fixture policies, not public hash callbacks. |
| invariants | Private coherent test use only; no runtime-source/proof authority is created. |
| ownership | Borrows actual mutable test backend during call. |
| failure | Enum declaration only. |
| cost | Fixed guards/field writes for injected mode/counter; later tested operations pay their real work. |
| Design | [src/storage/accounted_indexed_testing.hpp](../../../../../src/storage/accounted_indexed_testing.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp) |

## B0003

[Lines 8–8](../../../../../src/storage/accounted_indexed_testing.hpp#L8); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L8-L8:sha256:f7aea2dd76bba9233e797a4fa81fa7286f211847ae818aafd4a56292b7c2a574
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`class AccountedIndexedTesting\`: Collision setup requires fresh/unlocked state; counter seeding requires unlock. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/storage/accounted_indexed_testing.hpp:L9; use that declaration for the actual input/output shape. |
| invariants | The source note states: Collision setup requires fresh/unlocked state; counter seeding requires unlock. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0004

[Lines 9–14](../../../../../src/storage/accounted_indexed_testing.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class AccountedIndexedTesting
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Mutate controlled native backend fixtures. |
| inputs / outputs | Provides collision setup and counter exhaustion in the testing variant. |
| invariants | Private coherent test use only; no runtime-source/proof authority is created. |
| ownership | Borrows actual mutable test backend during call. |
| failure | Call-specific contract checks remain in definitions. |
| cost | Fixed guards/field writes for injected mode/counter; later tested operations pay their real work. |
| Design | [src/storage/accounted_indexed_testing.hpp](../../../../../src/storage/accounted_indexed_testing.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp) |

```text
static void collisions(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure a fresh unlocked native collision fixture. |
| inputs / outputs | Definition requires fresh empty row/index IDs and valid mode; same_bucket requires directory capacity&lt;=65536. |
| invariants | Private coherent test use only; no runtime-source/proof authority is created. |
| ownership | Borrows actual mutable test backend during call. |
| failure | Fixed IndexFailure on violated fixture contract; no mutation before checks. |
| cost | Fixed guards/field writes for injected mode/counter; later tested operations pay their real work. |
| Design | [src/storage/accounted_indexed_testing.hpp](../../../../../src/storage/accounted_indexed_testing.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp) |

```text
enum class Exhausted
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose the private diagnostic counter to saturate. |
| inputs / outputs | tuple_id/index_id/revision name the three explicit seeds. |
| invariants | Private coherent test use only; no runtime-source/proof authority is created. |
| ownership | Borrows actual mutable test backend during call. |
| failure | Enum declaration; unknown casts have no matching switch case in exhaust. |
| cost | Fixed guards/field writes for injected mode/counter; later tested operations pay their real work. |
| Design | [src/storage/accounted_indexed_testing.hpp](../../../../../src/storage/accounted_indexed_testing.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp) |

```text
static void exhaust(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed one diagnostic boundary counter in an unlocked test owner. |
| inputs / outputs | Sets selected tuple/index/revision counter to uint64 max; existing tuple payload is not cloned. |
| invariants | Private coherent test use only; no runtime-source/proof authority is created. |
| ownership | Borrows actual mutable test backend during call. |
| failure | State access/unlocked failures propagate; named enum switch has no added validation default. |
| cost | Fixed guards/field writes for injected mode/counter; later tested operations pay their real work. |
| Design | [src/storage/accounted_indexed_testing.hpp](../../../../../src/storage/accounted_indexed_testing.hpp), [CMakeLists.txt](../../../../../CMakeLists.txt), [cmake/CrownInstall.cmake](../../../../../cmake/CrownInstall.cmake), [src/storage/accounted_indexed.cpp](../../../../../src/storage/accounted_indexed.cpp) |

## B0005

[Lines 15–15](../../../../../src/storage/accounted_indexed_testing.hpp#L15); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L15:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage::detail\` at its lexical source position in src/storage/accounted_indexed_testing.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
