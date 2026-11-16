# `src/storage/descriptor.hpp` — block usage map

[Source](../../../../../src/storage/descriptor.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `c7c3decb2a17063b19d5cc6bb83a7825fe6e29d9770dac920cc7c4018a9d1de0`. 23 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–4](../../../../../src/storage/descriptor.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 5–5](../../../../../src/storage/descriptor.hpp#L5) | Type/record definition: struct DescriptorEquality |  · [reviewed contract](#b0002) |
| [B0003 · 6–8](../../../../../src/storage/descriptor.hpp#L6) | Explanatory comments or spacing. | source comment (unverified): // Shared handles keep the original concrete control block/deleter. Compiler · [reviewed contract](#b0003) |
| [B0004 · 9–16](../../../../../src/storage/descriptor.hpp#L9) | Type/record definition: struct LayoutDescriptor | source comment (unverified): // Shared handles keep the original concrete control block/deleter. Compiler · [reviewed contract](#b0004) |
| [B0005 · 17–22](../../../../../src/storage/descriptor.hpp#L17) | Type/record definition: struct ProjectionDescriptor |  · [reviewed contract](#b0005) |
| [B0006 · 23–23](../../../../../src/storage/descriptor.hpp#L23) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::storage::detail · [reviewed contract](#b0006) |

## B0001

[Lines 1–4](../../../../../src/storage/descriptor.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare private descriptor records shared by ordinary and accounted public facades. |
| inputs / outputs | Includes the public typed layout/projection interfaces and opens the detail namespace. |
| invariants | These declarations add no SQL NULL, dynamic schema lookup or row admission. |
| ownership | No instance storage is allocated by this header scaffold. |
| failure | Compile-time dependency only; concrete factories supply valid record backing. |
| cost | No runtime work. |
| Design | [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §11.4 S01](../../../../../Refactor.md) |

## B0002

[Lines 5–5](../../../../../src/storage/descriptor.hpp#L5); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct DescriptorEquality
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record one compiled repeated-variable equality between two layout positions. |
| inputs / outputs | Stores first and repeated FieldIds; row validation later compares those positions. |
| invariants | Factory construction guarantees valid numeric positions and equal scalar kinds; this record does not prove a query join. |
| ownership | Two scalar IDs with no retained owner or string. |
| failure | No executable validation/failure path. |
| cost | Fixed inline descriptor per repeated position, no allocation or name lookup. |
| Design | [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §11.4 S01](../../../../../Refactor.md) |

## B0003

[Lines 6–8](../../../../../src/storage/descriptor.hpp#L6); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
// Shared handles keep the original concrete control block/deleter.
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain how one immutable descriptor view preserves its actual concrete backing owner. |
| inputs / outputs | The note distinguishes standard compiler backing from accounted runtime blocks and states the no-mirror policy. |
| invariants | Shared base handles retain the original concrete shared control block/deleter; merely storing a span is not ownership by itself. |
| ownership | Concrete derived Data owns the backing; the base fields below borrow its immutable ranges. |
| failure | No runtime fallback, catch or data conversion is installed by this comment. |
| cost | No runtime cost; native descriptor handles avoid array/string/control-block copies. |
| Design | [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §11.4 S01](../../../../../Refactor.md) |

## B0004

[Lines 9–16](../../../../../src/storage/descriptor.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct LayoutDescriptor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry the immutable layout view and optional native tuple factory used by public facades. |
| inputs / outputs | Stores layout ID, field/context/origin/equality views and a nullable make_native_tuple function pointer. |
| invariants | Concrete factories keep every range/binding byte alive; null callback selects ordinary legacy tuple construction, non-null callback must match the concrete native Data. |
| ownership | The record does not own its spans/text directly. Shared facade owners preserve concrete standard or accounted backing and its deleter. |
| failure | Declaration performs no admission; misuse of callback/backing invariants would be a private factory-contract violation. |
| cost | Fixed view/callback record with no virtual dispatch table, mirrored arrays, per-field strings or allocation by itself. |
| Design | [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §11.4 S01](../../../../../Refactor.md), [src/storage/accounted_layout.cpp](../../../../../src/storage/accounted_layout.cpp) |

## B0005

[Lines 17–22](../../../../../src/storage/descriptor.hpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ProjectionDescriptor {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry source/target token ownership, ordered fields and optional native projection dispatch. |
| inputs / outputs | Constructor moves the two layout handles; field_view and apply_native_tuple are populated by a concrete derived factory. |
| invariants | Null callback selects standard gather/export; native callback must correspond to compatible concrete Data and the already admitted mapping. |
| ownership | Retains source/target layout handles, while the field span borrows derived backing. Shared concrete control blocks preserve its correct destructor. |
| failure | Constructor owner moves are noexcept; declaration itself performs no mapping validation or allocation. |
| cost | Constant handle setup and fixed record storage; later final-owner release can tear down retained layouts, while actual apply costs depend on selected fields/output bytes. |
| Design | [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §11.4 S01](../../../../../Refactor.md), [src/storage/accounted_projection.cpp](../../../../../src/storage/accounted_projection.cpp) |

## B0006

[Lines 23–23](../../../../../src/storage/descriptor.hpp#L23); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L23:sha256:8c6e12fd0f642560c35ea21133123e754f7a1816cffadd4adb769a1efe131187
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage::detail\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage::detail\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage::detail\` at its lexical source position in src/storage/descriptor.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage::detail\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
