# `include/crown/recovery/sql_rows_files.hpp` — block usage map

[Source](../../../../../../include/crown/recovery/sql_rows_files.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `3a7cf6e87310b3448a1e3f158b6d94b0b7079d3d1c07359cbdb095f751022e97`. 104 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../../checkpoints.md), [docs/journal.md](../../../../../journal.md), [docs/journal-files.md](../../../../../journal-files.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/history-retirement.md](../../../../../history-retirement.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../../include/crown/recovery/sql_rows_files.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases. | source comment (unverified): // The existing R2 byte/file limits and fixed transport observations are shared. · [reviewed contract](#b0001) |
| [B0002 · 18–51](../../../../../../include/crown/recovery/sql_rows_files.hpp#L18) | declares aliases; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // No retained command copy: append borrows an immutable pre-funded Frame for · [reviewed contract](#b0002) |
| [B0003 · 52–57](../../../../../../include/crown/recovery/sql_rows_files.hpp#L52) | declares aliases. | source comment (unverified): // Prefixes describe actual synced bytes; only the typed owner mints receipts. · [reviewed contract](#b0003) |
| [B0004 · 58–71](../../../../../../include/crown/recovery/sql_rows_files.hpp#L58) | Type/record definition: class SinkReceipt | returns header_; prefix_; source comment (unverified): // Only a healthy, untorn actual SinkFile mints this evidence. Copies preserve · [reviewed contract](#b0004) |
| [B0005 · 72–104](../../../../../../include/crown/recovery/sql_rows_files.hpp#L72) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // One bounded offset/fingerprint entry per complete epoch; no retained output · [reviewed contract](#b0005) |

## B0001

[Lines 1–17](../../../../../../include/crown/recovery/sql_rows_files.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:b898cba6b2fb393643edb111ccfb50a32cfc930d784adc2ca265e668abb18ee4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Include typed row descriptors and alias existing neutral file policy/diagnostic observations. |
| inputs / outputs | Alias FileStage,FileFault,FileOutcome,FileFailure,FileLimits,FileStatistics and WalFileState from sql_aggregate. |
| invariants | Aliases share transport DTOs only; they create no aggregate/native/row admission or open file. |
| ownership | No runtime owner or backing allocation is created by these declarations. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../../Refactor.md) |

## B0002

[Lines 18–51](../../../../../../include/crown/recovery/sql_rows_files.hpp#L18); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L51:sha256:edfd1f98173861bb6af934afcd6654d4972823e40846f56a15727cd5bbb149a5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the move-only typed rows WAL file owner and its private replay path. |
| inputs / outputs | Declare create/open,state,requires_reopen,append,repair_tail,close; private ReplayVisitor/open_replay/data/validate/AccountedUnique&lt;Data&gt;, with Session friendship. |
| invariants | Declarations expose no native-state import; complete typed frame validation and actual POSIX durability occur only in bodies. |
| ownership | Unique private Data owns the actual file lock/program/cursor/scratch; append Frame is borrowed only during a call. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../../Refactor.md) |

## B0003

[Lines 52–57](../../../../../../include/crown/recovery/sql_rows_files.hpp#L52); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L57:sha256:e653f47d17fe111c733b500b450162402ac8dce10186704d5fe52b8d3cb1d163
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Alias descriptive sink-prefix/state metadata and document receipt provenance. |
| inputs / outputs | Alias sql_aggregate::SinkPrefix and SinkFileState. |
| invariants | Aliases/DTOs do not create SinkReceipt, retain a lock or waive current-owner checks. |
| ownership | No runtime owner or backing allocation is created by these declarations. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../../Refactor.md) |

## B0004

[Lines 58–71](../../../../../../include/crown/recovery/sql_rows_files.hpp#L58); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L71:sha256:1d44fc2a8c7909929ad4431938f3b254bdd0a665adfdd079fa05e5f0ccacba02
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define a privately minted fixed sink observation and its borrowing accessors. |
| inputs / outputs | Private SinkFile constructor copies SinkHeader and SinkPrefix; header()/prefix() return const references, with rvalue overloads deleted. |
| invariants | Only SinkFile can mint the object; inline methods perform no physical-file validation or acknowledgment. |
| ownership | Receipt owns const fixed header/prefix values; references borrow that receipt, which retains no FD or lock. |
| failure | Fixed private constructor/accessors are noexcept; assignment is deleted and ordinary copy is default. |
| cost | O(1) fixed copies/reference returns; no syscall, hashing, payload scan or allocation. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../../Refactor.md) |

## B0005

[Lines 72–104](../../../../../../include/crown/recovery/sql_rows_files.hpp#L72); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L72-L104:sha256:9f36ad8dc9e55d7b226a0ad387161ac39021f54b6c1f54cb76524fd66f04c54c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the move-only typed rows sink owner and exact retry/verify interface. |
| inputs / outputs | Declare create/open,state,prefix,receipt,requires_reopen,append,verify,repair_tail,close and private data/validate/accept/AccountedUnique&lt;Data&gt;. |
| invariants | Methods are signatures here; bodies enforce complete-byte retry identity, limits and whole-session repair premises. |
| ownership | Unique private Data owns real FD/program/index/scratch; caller Frames are borrowed for calls, not queued. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../../Refactor.md) |
