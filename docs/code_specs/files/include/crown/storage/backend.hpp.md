# `include/crown/storage/backend.hpp` — block usage map

[Source](../../../../../../include/crown/storage/backend.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `92b53fde7d47ecf9deadcf3317f3467db0e8d718c822ce1a8d1a6269df44cf41`. 32 lines partitioned into 7 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/storage.md](../../../../../storage.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../../include/crown/storage/backend.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 8–8](../../../../../../include/crown/storage/backend.hpp#L8) | Type/record definition: enum class StorageBackend |  · [reviewed contract](#b0002) |
| [B0003 · 9–10](../../../../../../include/crown/storage/backend.hpp#L9) | Explanatory comments or spacing. | source comment (unverified): // Finite per-table component counts, including detached undo-owned records. · [reviewed contract](#b0003) |
| [B0004 · 11–22](../../../../../../include/crown/storage/backend.hpp#L11) | Type/record definition: struct IndexedLimits | source comment (unverified): // Finite per-table component counts, including detached undo-owned records. · [reviewed contract](#b0004) |
| [B0005 · 23–26](../../../../../../include/crown/storage/backend.hpp#L23) | Explanatory comments or spacing. | source comment (unverified): // Pre-admission configuration record. The immutable admitted plan binds · [reviewed contract](#b0005) |
| [B0006 · 27–31](../../../../../../include/crown/storage/backend.hpp#L27) | Type/record definition: struct IndexedBackendSpec | source comment (unverified): // Pre-admission configuration record. The immutable admitted plan binds · [reviewed contract](#b0006) |
| [B0007 · 32–32](../../../../../../include/crown/storage/backend.hpp#L32) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0007) |

## B0001

[Lines 1–7](../../../../../../include/crown/storage/backend.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:9dabf46015fb42887c1c205f0240646d1ceeb5dbb1ef20829425958fa32dce53
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/storage/backend.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/storage/index_work.hpp"\`, \`&lt;compare&gt;\`, \`&lt;cstddef&gt;\` for compilation; opens namespace \`crown::storage\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0002

[Lines 8–8](../../../../../../include/crown/storage/backend.hpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class StorageBackend { reference_ordered_v1, indexed_chained_v1 };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select the concrete table representation explicitly. |
| inputs / outputs | reference_ordered_v1 names ordered reference storage; indexed_chained_v1 names the finite chained indexed implementation. |
| invariants | Backend choice participates in physical options/bindings; the enum alone neither changes a live owner nor proves byte accounting. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | A declaration/value copy does not validate the represented configuration or grant authority to publish mutations. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/backend.hpp](../../../../../../include/crown/storage/backend.hpp), [src/storage/plan.cpp](../../../../../../src/storage/plan.cpp), [src/storage/indexed.cpp](../../../../../../src/storage/indexed.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 9–10](../../../../../../include/crown/storage/backend.hpp#L9); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L9-L10:sha256:710c3f92e4e56f157f7660b57dd32a9ac2b8dbfb021b22355c2b012b37234438
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct IndexedLimits\`: Finite per-table component counts, including detached undo-owned records. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/storage/backend.hpp:L11; use that declaration for the actual input/output shape. |
| invariants | The source note states: Finite per-table component counts, including detached undo-owned records. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0004

[Lines 11–22](../../../../../../include/crown/storage/backend.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IndexedLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure finite per-table component population caps. |
| inputs / outputs | Nine fields bound rows, indices, keys, memberships, nodes, directory slots, arena slots, arena pins and journal entries. |
| invariants | Zero permits no object of that component. Detached undo-owned objects and retained/pinned history remain relevant to the caps. These are not allocator bytes. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | A declaration/value copy does not validate the represented configuration or grant authority to publish mutations. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/backend.hpp](../../../../../../include/crown/storage/backend.hpp), [src/storage/plan.cpp](../../../../../../src/storage/plan.cpp), [src/storage/indexed.cpp](../../../../../../src/storage/indexed.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0005

[Lines 23–26](../../../../../../include/crown/storage/backend.hpp#L23); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L26:sha256:6e30ee314fefcb1f62737a2f7ceffb057106cb69ff26c572ddd146a3b8711e61
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`struct IndexedBackendSpec\`: Pre-admission configuration record. The immutable admitted plan binds these values. Work is one aggregate allowance per composed operation, not a per-table reset or an allocator-byte guarantee. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at include/crown/storage/backend.hpp:L27; use that declaration for the actual input/output shape. |
| invariants | The source note states: Pre-admission configuration record. The immutable admitted plan binds these values. Work is one aggregate allowance per composed operation, not a per-table reset or an allocator-byte guarantee. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The note states a local cost boundary: Pre-admission configuration record. The immutable admitted plan binds these values. Work is one aggregate allowance per composed operation, not a per-table reset or an allocator-byte guarantee. Treat it as usage guidance; actual work follows the implementation and input. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0006

[Lines 27–31](../../../../../../include/crown/storage/backend.hpp#L27); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct IndexedBackendSpec {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle the indexed component caps and one composed-operation work ceiling. |
| inputs / outputs | per_table applies to each selected table; per_operation is the five-dimensional work maximum for one composed operation. |
| invariants | The public record is mutable before admission. The admitted immutable plan binds actual values; copying the record must not mint per-table/per-step grants. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | A declaration/value copy does not validate the represented configuration or grant authority to publish mutations. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/backend.hpp](../../../../../../include/crown/storage/backend.hpp), [src/storage/plan.cpp](../../../../../../src/storage/plan.cpp), [src/storage/indexed.cpp](../../../../../../src/storage/indexed.cpp), [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0007

[Lines 32–32](../../../../../../include/crown/storage/backend.hpp#L32); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L32-L32:sha256:a925daf8c493848e231ff86cf03ec96eebbfe0f1e72bb404adf6ae3a25cd1b86
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage\` at its lexical source position in include/crown/storage/backend.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/code_specs/primitives.md](../../../../primitives.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |
