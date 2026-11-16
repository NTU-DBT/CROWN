# `src/recovery/sql_rows_cbor.hpp` — block usage map

[Source](../../../../../src/recovery/sql_rows_cbor.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `c7fb191f72da653b3024848824d61feba78e07e37eaee46a37862f09be81e89f`. 7 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../src/recovery/sql_rows_cbor.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): // One bounded wire validator; exact limits alias adds no adapter or authority. · [reviewed contract](#b0001) |

## B0001

[Lines 1–7](../../../../../src/recovery/sql_rows_cbor.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:c7fb191f72da653b3024848824d61feba78e07e37eaee46a37862f09be81e89f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reuse the existing exact bounded CBOR validator through an exact neutral limits alias. |
| inputs / outputs | Include sql_aggregate_cbor.hpp and alias its Cbor class in row detail namespace. |
| invariants | Alias changes no validator rules/budget behavior and imports no native/program authority. |
| ownership | No new fields/storage/owners; instantiated validator borrows its existing Budget/limits. |
| failure | No executable failure in these declarations; called validator keeps its own ImageFailure rules. |
| cost | Compile-time include/type alias; no adapter, indirection, allocation or per-command work. |
| Design | [src/recovery/sql_rows_cbor.hpp](../../../../../src/recovery/sql_rows_cbor.hpp), [src/recovery/sql_aggregate_cbor.hpp](../../../../../src/recovery/sql_aggregate_cbor.hpp) |
