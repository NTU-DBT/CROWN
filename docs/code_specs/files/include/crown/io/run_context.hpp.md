# `include/crown/io/run_context.hpp` — block usage map

[Source](../../../../../../include/crown/io/run_context.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `1d3a88ec600224454046a503edd81b9c09001127e320c6ef8b1678c3381848a0`. 8 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../../include/crown/io/run_context.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Explicit allocating export outside mutation. Strict UTF-8; native bytes are · [reviewed contract](#b0001) |

## B0001

[Lines 1–8](../../../../../../include/crown/io/run_context.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::string write_run_context_json(const runtime::ObservationSnapshot&,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export a caller-owned observation snapshot as run-context JSON text. |
| inputs / outputs | The function accepts an \`ObservationSnapshot\` and a default 16 MiB maximum for appended encoded bytes. |
| invariants | Only supplied metadata is visited; missing fields remain null. Caller-declared callback labels do not authenticate callback targets or prove unmeasured guarantees. |
| ownership | The returned ordinary string owns the output. Snapshot/session metadata and any shared labels remain owned by the supplied observation handles. |
| failure | Invalid UTF-8 or exceeding encoded-byte limit throws; source/native metadata values are otherwise formatted without altering execution state. |
| cost | Visits recorded initialization/session/attempt/configuration fields and text bytes. Output capacity and transient buffers are ordinary allocations not bounded by the encoded-byte limit. |
| Design | [include/crown/io/run_context.hpp §writer declaration](../../../../../../include/crown/io/run_context.hpp), [src/io/run_context.cpp §UTF-8 and output writer](../../../../../../src/io/run_context.cpp), [src/runtime/session.cpp §observation snapshots](../../../../../../src/runtime/session.cpp), [docs/measurement.md §run context](../../../../../measurement.md) |
