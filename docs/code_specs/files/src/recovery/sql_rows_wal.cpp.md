# `src/recovery/sql_rows_wal.cpp` — block usage map

[Source](../../../../../src/recovery/sql_rows_wal.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `d7e15095871d94a08f86a2f7613657c90a3be6922c444e93bf4bc26a26353a72`. 47 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../src/recovery/sql_rows_wal.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 6–46](../../../../../src/recovery/sql_rows_wal.cpp#L6) | Callable definition: Inspected WalCursor::feed(const frontend::SqlRowsProgram& program,std::string_view frame) | calls require, size, std::min, inspect; guard require(state_.records&lt;limits_.records,ImageFault::limit);; returns info; source comment (unverified): // Admit cumulative transport bytes/work before parsing; no per-frame refill. · [reviewed contract](#b0002) |
| [B0003 · 47–47](../../../../../src/recovery/sql_rows_wal.cpp#L47) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery::sql_rows · [reviewed contract](#b0003) |

## B0001

[Lines 1–5](../../../../../src/recovery/sql_rows_wal.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L5:sha256:541e909bc844a33094e4626f002f01e70a0404ca793989339c16b0d64207ab8a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Include row records/binary helpers and open the WAL implementation namespace. |
| inputs / outputs | These declarations make own WalCursor and bounded helper names available. |
| invariants | No frame/state/native operation executes in this span. |
| ownership | No new runtime backing storage from declarations; actual declared views/handles obey their named type lifetimes. |
| failure | Compile-time checking only in this span; invoked member/helper operations have separately specified failures. |
| cost | Include/type/signature/constant declarations only; no executed codec/binder/hash/sort/native work or backing allocation. |
| Design | [src/recovery/sql_rows_wal.cpp](../../../../../src/recovery/sql_rows_wal.cpp) |

## B0002

[Lines 6–46](../../../../../src/recovery/sql_rows_wal.cpp#L6); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L6-L46:sha256:0f26cdc06dbd920275f4d89182306d5ed22d2030ec997b8275da570f0044ce4f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate one complete row-family WAL frame into fixed candidate state; publish frontiers only after identity/order/cumulative grants pass. |
| inputs / outputs | Genuine program, one complete frame and retained ScanLimits/old WalState → Inspected plus a new published fixed WalState. |
| invariants | Checks cumulative bytes/work/records, exact ordinals, pending identity and C/I transitions before state_=next. Does not verify actual sink delivery, files or replay. |
| ownership | Frame/program borrowed; next/state are fixed-value copies and retain no command bytes. |
| failure | Fixed ImageFailure rejects the stated wire/domain/work checks; this block adds no catch or recovery action. Failure before final assignment preserves previous WalState. |
| cost | Full bounded inspect plus fixed state transition/copy; no allocation, native preparation or file I/O. |
| Design | [src/recovery/sql_rows_wal.cpp](../../../../../src/recovery/sql_rows_wal.cpp) |

## B0003

[Lines 47–47](../../../../../src/recovery/sql_rows_wal.cpp#L47); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L47-L47:sha256:5a88989d646de8c904ac4cbcd84db92dc85500003eb77614a29dedc10d8206dd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the stated namespace/type scope. |
| inputs / outputs | No runtime input or output. |
| invariants | No new checks or state transitions. |
| ownership | No ownership operation. |
| failure | No executable failure path. |
| cost | No runtime work/allocation. |
| Design | [src/recovery/sql_rows_wal.cpp](../../../../../src/recovery/sql_rows_wal.cpp) |
