# `include/crown/recovery/sql_rows_session.hpp` — block usage map

[Source](../../../../../../include/crown/recovery/sql_rows_session.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `be79ac6acbbce1521c01a2235ffe21fe1d1360054ec3bd712b10c69c85bfa9b9`. 96 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../../checkpoints.md), [docs/journal.md](../../../../../journal.md), [docs/journal-files.md](../../../../../journal-files.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/history-retirement.md](../../../../../history-retirement.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../../include/crown/recovery/sql_rows_session.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 7–7](../../../../../../include/crown/recovery/sql_rows_session.hpp#L7) | Type/record definition: struct SessionPaths | source comment (unverified): // Borrowed only by factories. · [reviewed contract](#b0002) |
| [B0003 · 8–8](../../../../../../include/crown/recovery/sql_rows_session.hpp#L8) | Type/record definition: struct SessionIdentity |  · [reviewed contract](#b0003) |
| [B0004 · 9–10](../../../../../../include/crown/recovery/sql_rows_session.hpp#L9) | Explanatory comments or spacing. | source comment (unverified): // Cold binder options can own ordinary parameter DTOs. Factories borrow this · [reviewed contract](#b0004) |
| [B0005 · 11–21](../../../../../../include/crown/recovery/sql_rows_session.hpp#L11) | Type/record definition: struct SessionLimits | source comment (unverified): // Cold binder options can own ordinary parameter DTOs. Factories borrow this · [reviewed contract](#b0005) |
| [B0006 · 22–22](../../../../../../include/crown/recovery/sql_rows_session.hpp#L22) | Type/record definition: enum class SessionFault : std::uint8_t |  · [reviewed contract](#b0006) |
| [B0007 · 23–30](../../../../../../include/crown/recovery/sql_rows_session.hpp#L23) | Type/record definition: class SessionFailure final : public std::exception | returns fault_; @ · [reviewed contract](#b0007) |
| [B0008 · 31–36](../../../../../../include/crown/recovery/sql_rows_session.hpp#L31) | Type/record definition: struct SessionState | source comment (unverified): // W is an Input's command sequence, not its WAL frame ordinal. Reject advances · [reviewed contract](#b0008) |
| [B0009 · 37–40](../../../../../../include/crown/recovery/sql_rows_session.hpp#L37) | Type/record definition: struct Decision | source comment (unverified): // No resource/contract-error tag. · [reviewed contract](#b0009) |
| [B0010 · 41–47](../../../../../../include/crown/recovery/sql_rows_session.hpp#L41) | Type/record definition: struct ReplayStatistics | source comment (unverified): // Successful native preparations only; original per-command grants, including · [reviewed contract](#b0010) |
| [B0011 · 48–83](../../../../../../include/crown/recovery/sql_rows_session.hpp#L48) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Synchronous single-writer owner over genuine SQL/native state and actual root, · [reviewed contract](#b0011) |
| [B0012 · 84–96](../../../../../../include/crown/recovery/sql_rows_session.hpp#L84) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // log owns rows and prepays progress before Input I/O. decide retries only that · [reviewed contract](#b0012) |

## B0001

[Lines 1–6](../../../../../../include/crown/recovery/sql_rows_session.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L6:sha256:e88fd64993cfbdcb348ecfb0468e4c904c1a8b52eecb115d461822f2b73553dd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Include typed row files/checkpoints and open the Session namespace. |
| inputs / outputs | Make sql_rows_files.hpp and sql_rows_checkpoint.hpp declarations available. |
| invariants | No Session, file lock, checkpoint or runtime is constructed by including these headers. |
| ownership | No runtime owner or backing allocation is created by these declarations. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../../Refactor.md) |

## B0002

[Lines 7–7](../../../../../../include/crown/recovery/sql_rows_session.hpp#L7); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L7-L7:sha256:52b156c9aa3dabec001096f3ce6ad9e24838c5daaef8c634b15a0487b78ce5ef
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry root-directory and sink-path borrows into synchronous factories. |
| inputs / outputs | SessionPaths contains string_view root,sink. |
| invariants | The DTO itself does not validate paths or open files. |
| ownership | Caller owns path bytes and keeps them alive through the factory call; SessionPaths copies only descriptors. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../../Refactor.md) |

## B0003

[Lines 8–8](../../../../../../include/crown/recovery/sql_rows_session.hpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L8-L8:sha256:a27726e4b1c80a713030d43d21e86170d072ff772b26088b452c66bcb7ff51b7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry fixed query and sink labels into Session creation. |
| inputs / outputs | SessionIdentity contains default-zero Id query_id,sink_id. |
| invariants | Factories validate labels; default construction alone supplies no valid identity. |
| ownership | Owns two fixed arrays, with no file/native capability or dynamic backing. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../../Refactor.md) |

## B0004

[Lines 9–10](../../../../../../include/crown/recovery/sql_rows_session.hpp#L9); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L9-L10:sha256:97e576763a15084e416f82c5dcc28bf0c9272561e4f4b7b18965da81aa525530
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the adjacent reviewed ownership/barrier rule in this comment block. |
| inputs / outputs | No executable input/output; the nearby callable supplies the actual protocol. |
| invariants | The prose is guidance tied to the adjacent code and pinned bytes, not an independent correctness or delay proof. |
| ownership | No runtime object, borrow or FD is created by comments. |
| failure | No failure/repair behavior is installed by prose. |
| cost | No executable cost. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../../Refactor.md) |

## B0005

[Lines 11–21](../../../../../../include/crown/recovery/sql_rows_session.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L11-L21:sha256:1221a81ec9b17abcb885972a28e0d1857fdf447932edbca5d5399303f42256ee
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect cold admission/rebuild configuration and finite live/history/replay policy. |
| inputs / outputs | SessionLimits contains admission, checkpoint, capture, rebuild, wal/sink, generation, history_generations=128, replay_commands=65536, replay_codec_work=4GiB and repair_torn_tail=true. |
| invariants | Declaration neither enforces supplied limits nor spends/refills grants. Live Data later retains only its LiveLimits subset. |
| ownership | Cold admission includes ordinary owning parameter DTOs; callers retain this configuration for the factory call, while live limits are copied separately. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../../Refactor.md) |

## B0006

[Lines 22–22](../../../../../../include/crown/recovery/sql_rows_session.hpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L22:sha256:a439741a7d63b6cb6c7930633b20d9a88e97433888a7e9beef1556adcf813b19
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate fixed Session-level diagnostic categories. |
| inputs / outputs | SessionFault has state,binding,progress,limit,transition,tail values. |
| invariants | Enum construction does not validate a Session or classify a native Error. |
| ownership | One uint8-backed scalar only. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../../Refactor.md) |

## B0007

[Lines 23–30](../../../../../../include/crown/recovery/sql_rows_session.hpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L30:sha256:1c49313daa4a1a6f3c4e2adf50e3e103b011beaea388d9dd0f06fe4da643fa74
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store a fixed Session fault with constant exception accessors. |
| inputs / outputs | SessionFault -&gt; SessionFailure; fault() returns its enum and what() returns the static SQL rows rejection literal. |
| invariants | Constructor/accessors are noexcept and perform no file/native/progress validation. |
| ownership | Exception owns only the enum; what() borrows a static literal. |
| failure | These inline methods do not throw; throwing/catching the exception occurs elsewhere. |
| cost | O(1) scalar store/read and literal pointer return; no dynamic message allocation. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../../Refactor.md) |

## B0008

[Lines 31–36](../../../../../../include/crown/recovery/sql_rows_session.hpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L36:sha256:dc84eb0ca7f9ebe231f033186505ba59ac15ec64d6ee695b7b95f1169e4dab46
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry observed command/native/delivery frontiers and pending flags. |
| inputs / outputs | SessionState has logged W,disposed I,committed C,delivered D,generation initialized zero and pending/output_pending initialized false. |
| invariants | This editable value carrier does not enforce W&gt;=I&gt;=C&gt;=D or observe any file; state() supplies observations. |
| ownership | Owns fixed scalars and flags only. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../../Refactor.md) |

## B0009

[Lines 37–40](../../../../../../include/crown/recovery/sql_rows_session.hpp#L37); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L40:sha256:9c68d4bbeea88bf7ba32efa202085bff2113807c20ff58819ab066010d7205ae
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry the outcome of resolving one logged command. |
| inputs / outputs | Decision has command_sequence I, physical_sequence C and optional semantic RejectReason. |
| invariants | The struct itself does not resolve a command or turn resource/contract errors into Reject. |
| ownership | Owns fixed values; no token/frame/file backing. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../../Refactor.md) |

## B0010

[Lines 41–47](../../../../../../include/crown/recovery/sql_rows_session.hpp#L41); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L47:sha256:8551fa9926b39deab3a8cb92781d27c1b95b2be046f3d0eb11bfc9b05b92326a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry cumulative replay command, codec and successful preparation metrics. |
| inputs / outputs | ReplayStatistics stores commands/codec_work/native_work/output_work initialized zero and source_work IndexWork{}. |
| invariants | Counters are descriptive values; declaration neither spends grants nor establishes a CPU-time allowance. |
| ownership | Owns fixed counters only. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../../Refactor.md) |

## B0011

[Lines 48–83](../../../../../../include/crown/recovery/sql_rows_session.hpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L83:sha256:ebf5251fc6801183df46b2bb1bc942f9fb00377ba018ef19365ea0d1fde2e8ac
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare genuine Session factories, move-only ownership and public observations. |
| inputs / outputs | Declare create_into/recover_into, destructor/move constructor, state/metadata/progress/pending-output/result/source APIs and deleted borrowed rvalue overloads. |
| invariants | Calls/borrows are serialized; signatures themselves do not admit/recover SQL, observe actual files or acknowledge delivery. |
| ownership | Session is noncopyable; references/views require its live retained Data. Result cursor lifetime rules belong to its runtime implementation. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../../Refactor.md) |

## B0012

[Lines 84–96](../../../../../../include/crown/recovery/sql_rows_session.hpp#L84); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L84-L96:sha256:cae83de6b1e4f9c37efcb3b94007eace9f40f94ed474554807b84b6b7d2f44c6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare Session log/resolve/deliver/checkpoint operations and private ownership helpers. |
| inputs / outputs | Declare lvalue log,decide,deliver,checkpoint, private owning constructor/data/replay/validate_files/select_checkpoint and AccountedUnique&lt;Data&gt;. |
| invariants | The declarations do not append/fsync/publish/replay; those operations have source-bound implementation contracts. |
| ownership | The unique Data member owns live Session state; mutation methods require serialized lvalue use. |
| failure | Declaration/type checking only here; corresponding executable operations retain their own failure contracts. |
| cost | No executable work from this declaration region; actual construction/copy/call costs belong to the declared implementations. |
| Design | [include/crown/recovery/sql_rows_session.hpp](../../../../../../include/crown/recovery/sql_rows_session.hpp), [include/crown/recovery/sql_rows_records.hpp](../../../../../../include/crown/recovery/sql_rows_records.hpp), [docs/sql_rows_batches.md](../../../../../sql_rows_batches.md), [docs/sql_rows_runtime.md](../../../../../sql_rows_runtime.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../../query_memory.md), [Refactor.md §8.1, W05-W06, V04](../../../../../../Refactor.md) |
