# `src/storage/arena_owner.hpp` — block usage map

[Source](../../../../../src/storage/arena_owner.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Keep stable tuple handles and retained deleted payloads for live readers and inverse operations.

Snapshot SHA-256: `46d5d380c9aa0f9e1e10acd9f2075ed65cf98dd43523749749e99eb80f7fd6cc`. 10 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [arena](../../../subsystem_contracts.md#arena). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/storage_journal.md](../../../../storage_journal.md), [docs/query_memory.md](../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../src/storage/arena_owner.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures. | source comment (unverified): // One authority for legacy and accounted arenas. Construction failure may · [reviewed contract](#b0001) |

## B0001

[Lines 1–10](../../../../../src/storage/arena_owner.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:46d5d380c9aa0f9e1e10acd9f2075ed65cf98dd43523749749e99eb80f7fd6cc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Source usage for this declaration span in src/storage/arena_owner.hpp: \`#pragma once\` makes this header idempotent within a translation unit; imports \`"crown/ir/ids.hpp"\`, \`&lt;optional&gt;\` for compilation; opens namespace \`crown::storage::detail\`; closes \`namespace crown::storage::detail\`. Source comment: One authority for legacy and accounted arenas. Construction failure may consume an unpublished ID; no successful owner identity is ever reused. |
| inputs / outputs | Compile inputs are the listed headers and namespace/type names. This span adds no result value unless a helper/type definition listed above is instantiated or called. |
| invariants | Every closing brace in the span closes the paired lexical namespace/type/block shown in the source. The source note says: One authority for legacy and accounted arenas. Construction failure may consume an unpublished ID; no successful owner identity is ever reused. Prose alone does not enforce the rule. |
| ownership | The source comment describes this adjacent lifetime/account boundary: One authority for legacy and accounted arenas. Construction failure may consume an unpublished ID; no successful owner identity is ever reused. The comment creates no owner; member types and callers determine actual retention. |
| failure | No explicit throw/catch appears in this exact span. Includes, constructors, inline members, static initialization and callees can still fail; follow their enclosing API contracts. |
| cost | The include directives affect compile dependencies. Any runtime initializer or cost in included definitions follows those definitions and is not inferred absent by this import block. |
| Design | [docs/storage.md](../../../../storage.md), [docs/tuple_arenas.md](../../../../tuple_arenas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |
