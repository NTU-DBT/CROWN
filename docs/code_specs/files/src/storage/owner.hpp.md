# `src/storage/owner.hpp` — block usage map

[Source](../../../../../src/storage/owner.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain exact set rows, primary membership and secondary key buckets for compiled runtime relations.

Snapshot SHA-256: `ebfd536f545e7885a1f68c30d1e31994fe47fe43a5ebb6f394faa3d3f96ae0b0`. 13 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [storage](../../../subsystem_contracts.md#storage). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/storage.md](../../../../storage.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../src/storage/owner.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures. | source comment (unverified): // One process-wide authority shared by reference and optimized table owners. · [reviewed contract](#b0001) |

## B0001

[Lines 1–13](../../../../../src/storage/owner.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:ebfd536f545e7885a1f68c30d1e31994fe47fe43a5ebb6f394faa3d3f96ae0b0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/owner.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/ir/ids.hpp"\`, \`&lt;optional&gt;\` for compilation; opens namespace \`crown::storage::detail\`; closes \`namespace crown::storage::detail\`. Source comment: One process-wide authority shared by reference and optimized table owners. Private storage implementation API; construction failure may consume an ID. namespace crown::storage::detail |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: One process-wide authority shared by reference and optimized table owners. Private storage implementation API; construction failure may consume an ID. namespace crown::storage::detail Prose alone does not enforce the rule. |
| ownership | Imports, namespace aliases, forward declarations and compile guards create no object owner. Runtime ownership starts with declared object instances and their allocator/member types. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/storage.md](../../../../storage.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
