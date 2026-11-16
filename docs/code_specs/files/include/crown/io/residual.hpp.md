# `include/crown/io/residual.hpp` — block usage map

[Source](../../../../../../include/crown/io/residual.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `8d4908ca6da45be175592ab82a8225d8233584005c109345a2beeb3cfa826c83`. 13 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../../include/crown/io/residual.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Allocating report serialization is outside residual advance quanta. The · [reviewed contract](#b0001) |

## B0001

[Lines 1–13](../../../../../../include/crown/io/residual.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Json write_residual_trace(const planner::ResidualTrace&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare diagnostic serialization for checked residual traces/candidates and a live residual-search owner. |
| inputs / outputs | The overloads accept immutable trace or candidate artifacts, or a \`ResidualSearch\` whose progress/trace/candidate/exact result are read for export. |
| invariants | Progress export does not advance/replay search. Where present, proof fields come from typed checked values; editable JSON output is not authority. |
| ownership | The JSON DOM owns copied binding, trace, candidate, and nested certificate data; the owner/artifacts remain separate. |
| failure | Conflicting optimum and infeasibility in the same owner is rejected; malformed enum/state data or ordinary allocations can fail. |
| cost | Serialization copies nested trace/tree/proof data into an ordinary DOM and has no byte/item cap in this API. It is outside residual continuation quanta. |
| Design | [include/crown/io/residual.hpp §writer overloads](../../../../../../include/crown/io/residual.hpp), [src/io/residual.cpp §trace/candidate/progress export](../../../../../../src/io/residual.cpp), [src/planner/residual.cpp §owner state](../../../../../../src/planner/residual.cpp), [docs/residual_candidates.md §residual authority](../../../../../residual_candidates.md) |
