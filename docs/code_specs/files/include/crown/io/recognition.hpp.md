# `include/crown/io/recognition.hpp` — block usage map

[Source](../../../../../../include/crown/io/recognition.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `fd0a7d616b9c5015403e001c15e329b92b38755867352a4044d5a6131da24e43`. 8 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../../include/crown/io/recognition.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::io · [reviewed contract](#b0001) |

## B0001

[Lines 1–8](../../../../../../include/crown/io/recognition.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Json write_structural_analysis(const planner::StructuralAnalysis& analysis, const Query& query);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a structural recognition result with names from its associated query. |
| inputs / outputs | The writer accepts \`StructuralAnalysis\` and \`Query\`, returning body/augmented reduction witnesses and failed cores. |
| invariants | The document explicitly reports \`height_status:not_checked\`; a GYO classification/witness does not establish exact minimum height or native execution. |
| ownership | Returned DOM copies names, witness steps, scopes, and flags from caller-owned result/query. |
| failure | Out-of-range witness/core variable IDs fail through checked query indexing; DOM allocation failures may escape. |
| cost | Visits witness/core steps and their scopes and creates ordinary JSON arrays/objects; no work or byte cap is in this API. |
| Design | [include/crown/io/recognition.hpp §writer declaration](../../../../../../include/crown/io/recognition.hpp), [src/io/recognition.cpp §reduction serialization](../../../../../../src/io/recognition.cpp), [src/planner/recognize.cpp §recognition result](../../../../../../src/planner/recognize.cpp), [docs/tree_oracle.md §structural classification](../../../../../tree_oracle.md) |
