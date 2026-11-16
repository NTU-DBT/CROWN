# `include/crown/io/catalog.hpp` — block usage map

[Source](../../../../../../include/crown/io/catalog.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `ce4219fed00a9ee7eb06aa369f99ba48a45ba014e66bccb5aa891784d0b64cab`. 12 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–12](../../../../../../include/crown/io/catalog.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // A standalone catalog has {schema_version:1,catalog:{version,tables}}. · [reviewed contract](#b0001) |

## B0001

[Lines 1–12](../../../../../../include/crown/io/catalog.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Catalog read_catalog(std::string_view text);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare strict read/write functions for standalone catalog documents and embedded catalog payloads. |
| inputs / outputs | Readers accept JSON text or a parsed payload and return \`Catalog\`; writers emit its standalone envelope or payload DOM. |
| invariants | Catalog validation checks schema metadata, names, types, FK references, constraints, statistics, and hints. \`enforced\` metadata is not proof that any row set currently satisfies it. |
| ownership | Read results own all strings, columns, constraint vectors, statistics, and hints. Writer results own copied JSON fields. |
| failure | Unknown/missing fields, unsupported scalar/collation/constraint forms, invalid references, or catalog validation errors are rejected. |
| cost | Parsing and output use ordinary DOM/vector/map allocations and traverse declared metadata. No row data is scanned or validated by these catalog functions. |
| Design | [include/crown/io/catalog.hpp §public declarations](../../../../../../include/crown/io/catalog.hpp), [src/io/catalog.cpp §read/write payload](../../../../../../src/io/catalog.cpp), [src/catalog/catalog.cpp §catalog validation](../../../../../../src/catalog/catalog.cpp), [docs/catalog.md §standalone and embedded catalog](../../../../../catalog.md) |
