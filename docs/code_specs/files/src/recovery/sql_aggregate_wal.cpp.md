# `src/recovery/sql_aggregate_wal.cpp` — block usage map

[Source](../../../../../src/recovery/sql_aggregate_wal.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `339bc3b52f598d90c0a21c84dc0370bebe57bd86b91acc1b62caa9ac8add10c5`. 47 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../src/recovery/sql_aggregate_wal.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 6–46](../../../../../src/recovery/sql_aggregate_wal.cpp#L6) | Callable definition: Inspected WalCursor::feed(const frontend::SqlAggregateProgram& program,std::string_view frame) | calls require, size, std::min, inspect; guard require(state_.records&lt;limits_.records,ImageFault::limit);; returns info; source comment (unverified): // Admit cumulative transport bytes/work before parsing; no per-frame refill. · [reviewed contract](#b0002) |
| [B0003 · 47–47](../../../../../src/recovery/sql_aggregate_wal.cpp#L47) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery::sql_aggregate · [reviewed contract](#b0003) |

## B0001

[Lines 1–5](../../../../../src/recovery/sql_aggregate_wal.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L5:sha256:571480e13640509d8f9a3952ef42c7b455f4697800049a9171ba81c9d100c836
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Imports record codec and binary-budget helpers, then opens the aggregate recovery namespace for the cumulative WalCursor feed implementation. |
| inputs / outputs | No runtime inputs/outputs are declared by the import/scope lines themselves. |
| invariants | The listed headers and namespace membership determine compile-time name availability; any API behavior belongs to the declarations/definitions that follow. |
| ownership | No object ownership is created by the imports or namespace tokens. |
| failure | No runtime failure path. Missing/incompatible dependencies or a violated compile-time constraint fail translation/linking. |
| cost | Compile/preprocessor work only; no new per-operation runtime overhead. |
| Design | [src/recovery/sql_aggregate_wal.cpp](../../../../../src/recovery/sql_aggregate_wal.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_wal.cpp.md](sql_aggregate_wal.cpp.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0002

[Lines 6–46](../../../../../src/recovery/sql_aggregate_wal.cpp#L6); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Inspected WalCursor::feed(const frontend::SqlAggregateProgram& program,std::string_view frame) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate one complete frame against cumulative scan limits and publish a WAL candidate only when its ordered transport transition is valid. |
| inputs / outputs | Declaration: \`Inspected WalCursor::feed(const frontend::SqlAggregateProgram& program,std::string_view frame)\`. Inputs/outputs: Validate one complete frame against cumulative scan limits and publish a WAL candidate only when its ordered transport transition is valid. |
| invariants | One local WalState candidate is published only at the end; frames must have contiguous record ordinal, ordered header/input/commit/reject transitions, and cumulative byte/work/record budgets. |
| ownership | Program and input frame view are borrowed for the call; fixed cursor state is mutated only after successful validation. |
| failure | Malformed/order/limit/work failures raise ImageFailure. State assignment happens only after a complete candidate transition; allocation failure is not expected in this fixed-size cursor path. |
| cost | One parse plus constant-state transition; total byte/work/record admissions are cumulative and not a CPU-time bound. |
| Design | [src/recovery/sql_aggregate_wal.cpp](../../../../../src/recovery/sql_aggregate_wal.cpp), [include/crown/recovery/sql_aggregate_records.hpp](../../../../../include/crown/recovery/sql_aggregate_records.hpp), [src/recovery/binary_detail.hpp](../../../../../src/recovery/binary_detail.hpp), [docs/sql_aggregate_records.md § WAL state machine](../../../../sql_aggregate_records.md), [docs/sql_aggregate_records.md § Wire contract](../../../../sql_aggregate_records.md) |

## B0003

[Lines 47–47](../../../../../src/recovery/sql_aggregate_wal.cpp#L47); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L47-L47:sha256:92582b45ad46706cdfae3684126917692713a5a92eff88bf2e3bcc42f5a8da44
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Closes the namespace crown::recovery::sql_aggregate at this source boundary; this is a lexical delimiter, not an operation. |
| inputs / outputs | No runtime input or output. Declarations following the span leave the preceding C++ scope. |
| invariants | The delimiter ends the preceding scope's visibility/linkage region; it adds no validation, publication, ownership transfer, or runtime authority. |
| ownership | The delimiter adds no owner. If it ends a function/block with live automatic objects, their normal destructors release those objects; namespace and type-definition closes change no existing object's lifetime. |
| failure | No explicit failure translation or catch is added. If a function/block exit destroys automatic objects, exception behavior follows those destructors; namespace/type closes have no runtime failure path. |
| cost | The delimiter adds no algorithmic work. A function/block exit can run existing automatic-object destructors and cleanup; namespace/type closes have no runtime cost. |
| Design | [src/recovery/sql_aggregate_wal.cpp](../../../../../src/recovery/sql_aggregate_wal.cpp), [docs/code_specs/files/src/recovery/sql_aggregate_wal.cpp.md](sql_aggregate_wal.cpp.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |
