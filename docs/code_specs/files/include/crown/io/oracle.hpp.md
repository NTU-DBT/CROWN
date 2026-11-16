# `include/crown/io/oracle.hpp` — block usage map

[Source](../../../../../../include/crown/io/oracle.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `0062112d6f22c210e296445880d64d23c1bb65d864a675551f39741c188e32ad`. 10 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../../include/crown/io/oracle.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0001) |

## B0001

[Lines 1–10](../../../../../../include/crown/io/oracle.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Json write_oracle(const planner::OracleResult& result, const Catalog& catalog, const Query& query);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare oracle/certificate report export and height-certificate DTO import bound to a typed query. |
| inputs / outputs | The writer accepts an oracle result plus catalog/query; the reader accepts certificate JSON plus that catalog/query; the report writer formats a certificate report. |
| invariants | The writer checks the supplied status/verification flag and supported algorithm but does not replay the proof. The reader validates schema, algorithm/version, canonical query binding, and typed fields before returning a \`HeightCertificate\`; independent replay is separate. |
| ownership | Imported certificate owns tree/lower-bound vectors; output DOM owns serialized certificate/report fields. |
| failure | Unsupported versions/algorithms, mismatched canonical query binding, malformed or non-representable typed fields, and unverified non-resource oracle results are rejected. Tree-name references are resolved by \`read_tree\`; lower-bound ID consistency and proof acceptance remain the independent replay checker’s job. |
| cost | Import parses and builds ordinary vectors and may reparse embedded query/tree binding. Export traverses tree, lower bounds, and search statistics into an allocating DOM. |
| Design | [include/crown/io/oracle.hpp §declarations](../../../../../../include/crown/io/oracle.hpp), [src/io/document.cpp §oracle and certificate codecs](../../../../../../src/io/document.cpp), [src/planner/certificate.cpp §independent replay](../../../../../../src/planner/certificate.cpp), [docs/tree_oracle.md §height certificate](../../../../../tree_oracle.md), [docs/planner_proofs.md §certificate replay](../../../../../planner_proofs.md) |
