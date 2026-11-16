# `src/recovery/sql_rows_session_detail.hpp` — block usage map

[Source](../../../../../src/recovery/sql_rows_session_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `dbd42afd4b5804ca48ed87c0a79b88211c81fb15baa9b5fb128521b7e7dc7e21`. 58 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../src/recovery/sql_rows_session_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | guard void require(bool,SessionFault=SessionFault::state);; source comment (unverified): // Private ownership order closes head/spool and file locks before native/root · [reviewed contract](#b0001) |
| [B0002 · 18–23](../../../../../src/recovery/sql_rows_session_detail.hpp#L18) | Type/record definition: struct LiveLimits | source comment (unverified): // Retain only bounds needed by operations/replay. Caller-owned cold binder · [reviewed contract](#b0002) |
| [B0003 · 24–24](../../../../../src/recovery/sql_rows_session_detail.hpp#L24) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_trivially_copyable_v&lt;LiveLimits&gt;); · [reviewed contract](#b0003) |
| [B0004 · 25–28](../../../../../src/recovery/sql_rows_session_detail.hpp#L25) | Type/record definition: struct Head |  · [reviewed contract](#b0004) |
| [B0005 · 29–32](../../../../../src/recovery/sql_rows_session_detail.hpp#L29) | Type/record definition: struct Prepared |  · [reviewed contract](#b0005) |
| [B0006 · 33–58](../../../../../src/recovery/sql_rows_session_detail.hpp#L33) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::recovery::sql_rows · [reviewed contract](#b0006) |

## B0001

[Lines 1–17](../../../../../src/recovery/sql_rows_session_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:1bc525251ced93ee83d9fe0784b3a611c33ab371a0a28c1b8fe27dccea300db9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Include Session/private-generation definitions and declare three local helpers. |
| inputs / outputs | Declare require(bool,SessionFault=state), semantic(string_view), anchor(SinkReceipt); open Session::Data and document member teardown order. |
| invariants | Only declarations/comments here; no native preparation, file validation or receipt observation executes. |
| ownership | No runtime owner or backing allocation is created by these declarations. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0002

[Lines 18–23](../../../../../src/recovery/sql_rows_session_detail.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L23:sha256:ba7c725170734b19156f8627642dbe8f6a4e963ed9ff716b9b7e276cf5017628
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the fixed live-policy subset retained after the cold factory returns. |
| inputs / outputs | LiveLimits contains checkpoint,capture,wal,sink and history_generations/replay_commands/replay_codec_work. |
| invariants | No cold binder parameters, admission DTO or rebuild options are members; declaration neither validates nor spends these limits. |
| ownership | Plain fixed policy values; no parameter vector or extra account owner. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0003

[Lines 24–24](../../../../../src/recovery/sql_rows_session_detail.hpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L24:sha256:f5b72fd376ce6c7aa1f8770a63033fe9bf5f8e4b78bdc907a72887f3a91919de
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check at compile time that retained live policy has trivial copy semantics. |
| inputs / outputs | static_assert(is_trivially_copyable_v&lt;LiveLimits&gt;). |
| invariants | Compilation fails if the trait becomes false; this establishes no runtime policy validity. |
| ownership | No runtime owner or backing allocation is created by these declarations. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0004

[Lines 25–28](../../../../../src/recovery/sql_rows_session_detail.hpp#L25); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L28:sha256:ede7f96d4bcb340633ec2caaeb98d6c5fddc6c9fd1d40ddd8b97fc93ba8b158b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Pair the one owned logged input with its prepaid source-position publication. |
| inputs / outputs | Head contains DecodedInput input and InputPositions::Prepared position. |
| invariants | Member declaration alone does not decode Input, validate progress or publish the prepared position. |
| ownership | DecodedInput owns frame/view arrays; Prepared retains its separately funded position node until publish or destruction. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0005

[Lines 29–32](../../../../../src/recovery/sql_rows_session_detail.hpp#L29); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L32:sha256:c0179fa80d916dbf367a0b6cc1404c596e5c75cce6a96a183c92b3273a7026c3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry either genuine native preparation or the allowlisted semantic rejection. |
| inputs / outputs | Prepared contains optional SqlRowsRuntime::PreparedBatch token and optional RejectReason rejected. |
| invariants | This DTO does not enforce exclusivity or classify an exception; Data::prepare constructs the actual alternatives. |
| ownership | An engaged token owns rollback responsibility; the rejection enum is a value. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |

## B0006

[Lines 33–58](../../../../../src/recovery/sql_rows_session_detail.hpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L58:sha256:0550ca8b70aaa5210efb04219324bb133113c773d1b452f01d4f82b5f7b32896
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare Session Data ownership order, pending state and internal method signatures. |
| inputs / outputs | Members are account,LiveLimits,root,descriptor,native,progress,reader,optional wal/sink/head/spool,replayed and poisoned=false; declare constructor/ready/own/prepare/epoch/publish/codec/observe methods. |
| invariants | Reverse destruction releases pending head/spool and file owners before native/root, with account last; declarations alone perform no durable transition. |
| ownership | Each actual member retains its own account/lock/row/frame backing; no parallel scheduler, history queue or database mirror is declared. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../Refactor.md) |
