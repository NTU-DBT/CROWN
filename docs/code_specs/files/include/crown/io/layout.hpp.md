# `include/crown/io/layout.hpp` — block usage map

[Source](../../../../../../include/crown/io/layout.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `11546f65d35312a04860d5ad822caa64e4a4da59203a0a9839cf20ff02a928ef`. 13 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../../include/crown/io/layout.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Bind an artifact to the caller's immutable layout tokens after checking the · [reviewed contract](#b0001) |

## B0001

[Lines 1–13](../../../../../../include/crown/io/layout.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Json write_layout(const storage::TupleLayout& layout);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare JSON export/import for tuple layouts and projections. |
| inputs / outputs | Writers emit layout/projection descriptions; \`read_layout\` builds an ordinary layout descriptor and \`read_projection\` accepts caller source/target layouts for binding. |
| invariants | Projection import checks complete parsed descriptors against the supplied layouts and, on success, retains the supplied actual layout handles. JSON IDs do not replace those bindings. |
| ownership | Parsed descriptors and field-index vectors are ordinary owning values. A returned \`Projection\` stores copies of the supplied \`TupleLayout\` handles; those shared handles keep immutable layout data alive after the caller’s wrapper objects expire. |
| failure | Bad version/types/precision, out-of-range host indexes, descriptor mismatch, or invalid field selections fail through document/layout errors. |
| cost | Parsing allocates JSON DOM and field vectors; writers traverse fields. No bounded byte/work parameter is declared for these functions. |
| Design | [include/crown/io/layout.hpp §public declarations](../../../../../../include/crown/io/layout.hpp), [src/io/layout.cpp §descriptor comparison and binding](../../../../../../src/io/layout.cpp), [src/storage/layout.cpp §layout validation](../../../../../../src/storage/layout.cpp), [docs/physical_runtime.md §compiled layout tokens](../../../../../physical_runtime.md) |
