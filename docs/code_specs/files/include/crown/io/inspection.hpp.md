# `include/crown/io/inspection.hpp` — block usage map

[Source](../../../../../../include/crown/io/inspection.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Admit bounded external documents/records and serialize explicit public representations at the engine boundary.

Snapshot SHA-256: `a32876961aed3f02a5359fea8b385bbc1044de5da9d080f39d77fd1610628568`. 13 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../../include/crown/io/inspection.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Versioned deterministic diagnostics, not a checkpoint/restore format. · [reviewed contract](#b0001) |

## B0001

[Lines 1–13](../../../../../../include/crown/io/inspection.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::string write_runtime_state(const runtime::CanonicalPhysicalState&,std::size_t max_bytes=64*1024*1024);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare bounded string serialization for canonical physical/delta state and invariant diagnostics. |
| inputs / outputs | Each overload consumes an already captured state/report and returns versioned JSON text; the default maximum encoded size is 64 MiB. |
| invariants | These deterministic diagnostic formats are not checkpoint/restore formats. The limit concerns encoded bytes, not caller state, allocator capacity, or scalar scratch. |
| ownership | The result string owns encoded bytes; captured input objects are read-only and remain owned elsewhere. |
| failure | Invalid values/encoding or exceeding the writer byte limit throws; diagnostic generation and serialization are separate from capture and invariant-check work. |
| cost | Serialization traverses physical/delta fields and report issues; issue keys are exported into ordinary rows before output. String and per-issue temporary allocations are not covered by the byte cap. |
| Design | [include/crown/io/inspection.hpp §writer declarations](../../../../../../include/crown/io/inspection.hpp), [src/io/inspection.cpp §state/report writer](../../../../../../src/io/inspection.cpp), [docs/invariant_memory.md §diagnostic report](../../../../../invariant_memory.md), [docs/checkpoints.md §checkpoint distinction](../../../../../checkpoints.md) |
