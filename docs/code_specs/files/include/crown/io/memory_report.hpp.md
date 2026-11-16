# `include/crown/io/memory_report.hpp` — block usage map

[Source](../../../../../../include/crown/io/memory_report.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Declare explicit caller-owned memory-report JSON export; this header does not collect native memory.

Snapshot SHA-256: `dae3013b6b9f8a2ec1af0400ac672fe75d6c24f03535f074707eaff40df1c984`. 8 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [io](../../../../subsystem_contracts.md#io). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ingestion.md](../../../../../ingestion.md), [docs/query_identity.md](../../../../../query_identity.md), [docs/schema_evolution.md](../../../../../schema_evolution.md), [docs/cli.md](../../../../../cli.md), [docs/query_memory.md](../../../../../query_memory.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../../include/crown/io/memory_report.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Explicit caller-owned diagnostic export. Never an import/deployment capability. · [reviewed contract](#b0001) |

## B0001

[Lines 1–8](../../../../../../include/crown/io/memory_report.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Json write_memory_report(const runtime::memory::Report&);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose an explicit JSON export of an already captured native memory report. |
| inputs / outputs | \`write_memory_report\` accepts \`runtime::memory::Report\` and returns the versioned report DOM. |
| invariants | The formatter reads retained report rows and does not rescan live runtime/account state. The output is diagnostic, not an import or deployment capability. |
| ownership | Returned JSON owns copied counters, owner/table/operator details, and labels; the report retains its captured native snapshot independently. |
| failure | Unknown memory enum encodings throw. Ordinary JSON allocation failures are separate from report capture failure. |
| cost | It visits stored owners, tables, operators, purposes, and lifetimes and builds a full ordinary DOM. This API declares no output-byte limit and performs no capture. |
| Design | [include/crown/io/memory_report.hpp §writer](../../../../../../include/crown/io/memory_report.hpp), [src/io/memory_report.cpp §report formatting](../../../../../../src/io/memory_report.cpp), [src/runtime/memory_report.cpp §captured report](../../../../../../src/runtime/memory_report.cpp), [docs/memory_reports.md §explicit export](../../../../../memory_reports.md) |
