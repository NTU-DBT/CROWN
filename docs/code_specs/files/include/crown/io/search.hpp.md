# `include/crown/io/search.hpp` — block usage map

[Source](../../../../../../include/crown/io/search.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `0acaee533dfaf525bd52ef19c19c08d9e372e0e6b39a11b99e1636bfeeb6ea75`. 13 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../../include/crown/io/search.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Allocating IO is outside advance quanta. Authority is accepted only through · [reviewed contract](#b0001) |

## B0001

[Lines 1–13](../../../../../../include/crown/io/search.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Json write_verified_optimum(const planner::VerifiedOptimum&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export typed checked search results and read-only progress from exact-search or certificate-replay owners. |
| inputs / outputs | Overloads format a checked incumbent, verified optimum/infeasibility, live \`ExactSearch\` progress, or live \`CertificateReplay\` progress. |
| invariants | Progress serialization reads owner snapshots and does not advance. Checked proof authority comes from typed values; the emitted JSON remains an editable DTO. |
| ownership | Returned DOM owns copied query binding, trees, counters, limits, and certificate fields; owner and checked tokens retain their original lifetimes. |
| failure | Moved/invalid owner state or unsupported enum/tree data may throw; report generation itself does not convert invalid progress into verified status. |
| cost | Builds ordinary JSON objects/arrays and compatibility proof payloads; work is outside search/replay continuation grants and no output cap is declared. |
| Design | [include/crown/io/search.hpp §writer overloads](../../../../../../include/crown/io/search.hpp), [src/io/search.cpp §typed result/progress serialization](../../../../../../src/io/search.cpp), [src/planner/certificate.cpp §checked proof tokens](../../../../../../src/planner/certificate.cpp), [docs/planner_proofs.md §checked results](../../../../../planner_proofs.md) |
