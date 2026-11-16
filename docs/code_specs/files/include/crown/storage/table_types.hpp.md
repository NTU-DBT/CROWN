# `include/crown/storage/table_types.hpp` — block usage map

[Source](../../../../../../include/crown/storage/table_types.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `1f2762902ae024b29d6cd5bc834caf67158cfceec94b5d22e260a5aba4fa8e7f`. 7 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../../indexed_storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/storage.md](../../../../../storage.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../../include/crown/storage/table_types.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 6–6](../../../../../../include/crown/storage/table_types.hpp#L6) | Type/record definition: struct InsertResult |  · [reviewed contract](#b0002) |
| [B0003 · 7–7](../../../../../../include/crown/storage/table_types.hpp#L7) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::storage · [reviewed contract](#b0003) |

## B0001

[Lines 1–5](../../../../../../include/crown/storage/table_types.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L5:sha256:18512a88c3104a732c35422247f8747be88fa9a7e840f522a57c3bc57f7c6056
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in include/crown/storage/table_types.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/ir/ids.hpp"\` for compilation; opens namespace \`crown::storage\`. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | The exact import, alias, namespace and member declarations determine the local compile/link surface; stronger behavior belongs to their constructors and operations. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/storage.md](../../../../../storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |

## B0002

[Lines 6–6](../../../../../../include/crown/storage/table_types.hpp#L6); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct InsertResult { bool inserted; TupleHandle handle; };
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return set insertion outcome with the table-local logical handle. |
| inputs / outputs | inserted says whether a new logical row was published; handle is either the new handle or the existing equal tuple's handle. |
| invariants | The handle encodes its owner/relation identity and does not pin, borrow or copy row values. Tentative journal handles must stay internal until commit. |
| ownership | The scalar/metadata result retains no row, account or runtime ownership; plain record declarations here own only their shown inline fields. |
| failure | The record itself performs no validation; insert can reject before constructing a returned outcome. |
| cost | Fixed-size metadata copy/read/comparison; no dynamic allocation or population traversal. |
| Design | [include/crown/storage/table_types.hpp](../../../../../../include/crown/storage/table_types.hpp), [src/storage/reference.cpp](../../../../../../src/storage/reference.cpp), [src/storage/indexed.cpp](../../../../../../src/storage/indexed.cpp), [docs/storage.md](../../../../../storage.md), [docs/code_review.md](../../../../../code_review.md) |

## B0003

[Lines 7–7](../../../../../../include/crown/storage/table_types.hpp#L7); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L7-L7:sha256:a925daf8c493848e231ff86cf03ec96eebbfe0f1e72bb404adf6ae3a25cd1b86
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the \`namespace crown::storage\` scope at this exact source boundary. |
| inputs / outputs | This token introduces no callable inputs or outputs. Declarations inside \`namespace crown::storage\` define the available names, members and operations. |
| invariants | The closing brace matches the opening \`namespace crown::storage\` at its lexical source position in include/crown/storage/table_types.hpp; it preserves C++ namespace/type nesting. |
| ownership | The closing delimiter creates no owner. Types closed by \`namespace crown::storage\` retain the lifetimes and allocator rules of their own fields and operations. |
| failure | No failure path executes at this closing delimiter. Failure and cleanup behavior belong to enclosed functions and owning types. |
| cost | The delimiter itself performs no runtime work; the enclosed initializers, methods and destructors carry their own costs. |
| Design | [docs/storage.md](../../../../../storage.md), [docs/storage_journal.md](../../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../../subsystem_contracts.md) |
