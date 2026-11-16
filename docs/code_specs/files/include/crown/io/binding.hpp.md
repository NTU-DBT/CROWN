# `include/crown/io/binding.hpp` — block usage map

[Source](../../../../../../include/crown/io/binding.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `f5f9eae2bc4c415f7131da217d29e60b9c3d0357e9d14e0bfbf63c839076d803`. 12 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../../include/crown/io/binding.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // A success artifact is accepted only after bounded replay matches every field. · [reviewed contract](#b0001) |

## B0001

[Lines 1–12](../../../../../../include/crown/io/binding.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Json write_sql_binding(const frontend::SqlBindResult& result);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare serialization and replay-validated import for SQL binding artifacts and parameter options. |
| inputs / outputs | \`write_sql_binding\` emits a success binding or diagnostic. \`read_sql_binding\` returns a \`BoundSql\` after source/catalog replay; \`read_bind_options\` parses positional parameter type declarations. |
| invariants | Imported success fields are assertions: the reader rebinds source against the encoded catalog and requires complete serialized equality. Admission remains not checked; parser success or imported JSON does not become native/proof authority. |
| ownership | The replayed \`BoundSql\` owns source, catalog, and all bound vectors; the returned JSON/options own ordinary copied data. |
| failure | Malformed fields, unsupported types, binding rejection, stricter replay limits, or output mismatch throw \`Error\`; diagnostic resource exhaustion is surfaced as resource failure. |
| cost | Export creates a full JSON DOM. Import parses the DOM, rebuilds binding, serializes it again for equality, and incurs ordinary parser/compiler/copy costs separate from replay counters. |
| Design | [include/crown/io/binding.hpp §public declarations](../../../../../../include/crown/io/binding.hpp), [src/io/binding.cpp §replay and equality](../../../../../../src/io/binding.cpp), [src/frontend/bind.cpp §binder](../../../../../../src/frontend/bind.cpp), [docs/sql_binding.md §binding result](../../../../../sql_binding.md) |
