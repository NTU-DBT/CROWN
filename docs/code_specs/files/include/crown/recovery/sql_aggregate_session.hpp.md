# `include/crown/recovery/sql_aggregate_session.hpp` — block usage map

[Source](../../../../../../include/crown/recovery/sql_aggregate_session.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `c9011140c42403dd123ea8d11c74bd0ae03a4f246c8877a16144e6c033d07541`. 95 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../../checkpoints.md), [docs/journal.md](../../../../../journal.md), [docs/journal-files.md](../../../../../journal-files.md), [docs/generations.md](../../../../../generations.md), [docs/local-sink.md](../../../../../local-sink.md), [docs/history-retirement.md](../../../../../history-retirement.md), [docs/update_patterns.md](../../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../../include/crown/recovery/sql_aggregate_session.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 7–7](../../../../../../include/crown/recovery/sql_aggregate_session.hpp#L7) | Type/record definition: struct SessionPaths | source comment (unverified): // Borrowed only by factories. · [reviewed contract](#b0002) |
| [B0003 · 8–8](../../../../../../include/crown/recovery/sql_aggregate_session.hpp#L8) | Type/record definition: struct SessionIdentity |  · [reviewed contract](#b0003) |
| [B0004 · 9–10](../../../../../../include/crown/recovery/sql_aggregate_session.hpp#L9) | Explanatory comments or spacing. | source comment (unverified): // Cold binder options can own ordinary parameter DTOs. Factories borrow this · [reviewed contract](#b0004) |
| [B0005 · 11–21](../../../../../../include/crown/recovery/sql_aggregate_session.hpp#L11) | Type/record definition: struct SessionLimits | source comment (unverified): // Cold binder options can own ordinary parameter DTOs. Factories borrow this · [reviewed contract](#b0005) |
| [B0006 · 22–22](../../../../../../include/crown/recovery/sql_aggregate_session.hpp#L22) | Type/record definition: enum class SessionFault : std::uint8_t |  · [reviewed contract](#b0006) |
| [B0007 · 23–30](../../../../../../include/crown/recovery/sql_aggregate_session.hpp#L23) | Type/record definition: class SessionFailure final : public std::exception | returns fault_; @ · [reviewed contract](#b0007) |
| [B0008 · 31–36](../../../../../../include/crown/recovery/sql_aggregate_session.hpp#L31) | Type/record definition: struct SessionState | source comment (unverified): // W is an Input's command sequence, not its WAL frame ordinal. Reject advances · [reviewed contract](#b0008) |
| [B0009 · 37–40](../../../../../../include/crown/recovery/sql_aggregate_session.hpp#L37) | Type/record definition: struct Decision | source comment (unverified): // No resource/contract-error tag. · [reviewed contract](#b0009) |
| [B0010 · 41–47](../../../../../../include/crown/recovery/sql_aggregate_session.hpp#L41) | Type/record definition: struct ReplayStatistics | source comment (unverified): // Successful native preparations only; original per-command grants, including · [reviewed contract](#b0010) |
| [B0011 · 48–83](../../../../../../include/crown/recovery/sql_aggregate_session.hpp#L48) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Synchronous single-writer owner over genuine SQL/native state and actual root, · [reviewed contract](#b0011) |
| [B0012 · 84–95](../../../../../../include/crown/recovery/sql_aggregate_session.hpp#L84) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // False if no spool; success confirms actual sink bytes/receipt. · [reviewed contract](#b0012) |

## B0001

[Lines 1–6](../../../../../../include/crown/recovery/sql_aggregate_session.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the public session header's direct dependency boundary and guard repeated inclusion. |
| inputs / outputs | Preprocessor input in; declarations using the R2 WAL/sink file and checkpoint APIs available to downstream code. |
| invariants | This header exposes the SQL aggregate session API and depends on the concrete files/checkpoint headers; it does not add a lower-level recovery dependency on the SQL frontend. |
| ownership | No runtime object or filesystem state is created by inclusion. |
| failure | Compilation fails if a declared dependency is unavailable or incompatible; no runtime failure behavior belongs to this region. |
| cost | Compile-time preprocessing and type declarations only; no runtime cost. |
| Design | [include/crown/recovery/sql_aggregate_files.hpp](../../../../../../include/crown/recovery/sql_aggregate_files.hpp), [include/crown/recovery/sql_aggregate_checkpoint.hpp](../../../../../../include/crown/recovery/sql_aggregate_checkpoint.hpp), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md) |

## B0002

[Lines 7–7](../../../../../../include/crown/recovery/sql_aggregate_session.hpp#L7); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionPaths {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry root and sink names into a synchronous session factory without owning them. |
| inputs / outputs | Borrowed root/sink string views in; a fixed pair of path views passed to create_into or recover_into. |
| invariants | Views are only factory-call inputs. The factory consumes paths synchronously to open/create actual root and sink owners and does not retain these string_views as path authority. |
| ownership | Both string_views borrow caller storage; keeping or moving SessionPaths does not extend either path's lifetime. |
| failure | Empty, oversized, malformed, or inaccessible paths are rejected by the corresponding root/file owner before a Session escapes. |
| cost | Two small view copies; filesystem open/validation cost occurs in the factory. |
| Design | [docs/sql_aggregate_session.md](../../../../../sql_aggregate_session.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/generations.md](../../../../../generations.md) |

## B0003

[Lines 8–8](../../../../../../include/crown/recovery/sql_aggregate_session.hpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionIdentity {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Supply the query and sink identifiers used to bind initial R2 root and sink owners. |
| inputs / outputs | Fixed query_id and sink_id Id arrays in; copied identity values for the session factory. |
| invariants | create_into checks both IDs as lowercase-hex identities before admission/publication. The record itself is only a value carrier and does not prove that an existing file belongs to these IDs. |
| ownership | Owns two fixed arrays; no string views or external buffers are retained. |
| failure | Malformed IDs raise SessionFailure(binding) at the factory; existing root/sink binding is checked by the actual owners. |
| cost | Fixed-size value copy and ID validation in the factory. |
| Design | [docs/sql_aggregate_session.md](../../../../../sql_aggregate_session.md), [docs/sql_aggregate_descriptor.md](../../../../../sql_aggregate_descriptor.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md) |

## B0004

[Lines 9–10](../../../../../../include/crown/recovery/sql_aggregate_session.hpp#L9); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L9-L10:sha256:97e576763a15084e416f82c5dcc28bf0c9272561e4f4b7b18965da81aa525530
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Design note for adjacent code: Cold binder options can own ordinary parameter DTOs. Factories borrow this configuration only for the call; the session retains fixed live limits. This is caller guidance recorded as prose, not an executable result. |
| inputs / outputs | No runtime interface is implemented by these comment-only lines. They sit at include/crown/recovery/sql_aggregate_session.hpp lines 7-12; the surrounding declaration/body defines its own inputs and outputs. |
| invariants | The words record the intended use boundary only. They do not add a guard, proof, capability, transaction, durability guarantee, or account charge; verify behavior in the referenced implementation. |
| ownership | Comment text owns no data. Object lifetimes, borrows, and account attribution remain those of the adjacent source objects and their constructors. |
| failure | No failure path is implemented here. Any mentioned failure or recovery rule belongs to the adjacent operation and its existing error carrier. |
| cost | No runtime work is performed by these lines; any cost/bound in the note is not certified by this comment-only card. |
| Design | [include/crown/recovery/sql_aggregate_session.hpp](../../../../../../include/crown/recovery/sql_aggregate_session.hpp), [docs/code_specs/files/include/crown/recovery/sql_aggregate_session.hpp.md](sql_aggregate_session.hpp.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/sql_aggregate_session.md](../../../../../sql_aggregate_session.md) |

## B0005

[Lines 11–21](../../../../../../include/crown/recovery/sql_aggregate_session.hpp#L11); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Collect the independent limits for one SQL aggregate session and its recovery work. |
| inputs / outputs | Caller-owned factory configuration in: admission/binder DTOs, checkpoint/capture/rebuild bounds, file/generation bounds and history/replay caps. Factories borrow const SessionLimits& only for their synchronous call. |
| invariants | replay_commands counts Input commands, not WAL frame ordinals. replay_codec_work cumulatively accounts Input decoding, canonical group output encoding, and full-output hash byte visits; WalFile's full scan has separate file limits. ReplayStatistics native/group/source counters are observations, not caps or CPU budgets. The original runtime Options remain caller supplied. |
| ownership | This public DTO can own ordinary vector/string parameter payloads. Data retains only its fixed LiveLimits projection; admission/rebuild/repair stay factory-local, while GenerationOwner owns its fixed generation limits. Original parameter identity comes from the genuine program or saved descriptor. |
| failure | Invalid values are rejected by the factory or the specific lower operation that consumes them; this record does not validate or normalize limits. |
| cost | Copying this caller DTO can allocate and scales with its binder payloads. Session factories do not copy the whole DTO: they copy seven fixed live groups/scalars. Existing cold descriptor rebinding can create a transient binder workspace; it is released before return. |
| Design | [docs/sql_aggregate_session.md](../../../../../sql_aggregate_session.md), [build/verification/w06-r2-protocol-review-v1/protocol.md](../../../../../../build/verification/w06-r2-protocol-review-v1/protocol.md), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md), [Refactor.md §11.9 W06](../../../../../../Refactor.md), [include/crown/frontend/sql_rows.hpp](../../../../../../include/crown/frontend/sql_rows.hpp), [include/crown/frontend/bind.hpp](../../../../../../include/crown/frontend/bind.hpp), [src/recovery/sql_aggregate_descriptor.cpp](../../../../../../src/recovery/sql_aggregate_descriptor.cpp) |

## B0006

[Lines 22–22](../../../../../../include/crown/recovery/sql_aggregate_session.hpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class SessionFault : std::uint8_t
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Give coordinator state/binding/progress/limit/transition/tail failures a fixed typed category. |
| inputs / outputs | One of six coordinator fault enumerators in; fixed SessionFailure::fault() value out. |
| invariants | These are session-contract failures, not durable RejectReason values. The enum deliberately contains no work/memory/contract semantic tag and does not absorb lower file/runtime exception types. |
| ownership | One byte-sized value copied into SessionFailure. |
| failure | No formatting or fallback category is performed by the enum; callers preserve the original typed failure boundary. |
| cost | Fixed scalar construction/read. |
| Design | [docs/sql_aggregate_session.md](../../../../../sql_aggregate_session.md), [docs/sql_aggregate_records.md](../../../../../sql_aggregate_records.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md) |

## B0007

[Lines 23–30](../../../../../../include/crown/recovery/sql_aggregate_session.hpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class SessionFailure final : public std::exception
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry a fixed SessionFault across coordinator contract checks without formatted diagnostic allocation. |
| inputs / outputs | Fixed SessionFault in; typed fault() and the constant what() string out. |
| invariants | Construction is noexcept and stores only the fault enum. what() is the same fixed text for every fault; consumers must inspect fault() for the category. |
| ownership | Owns one SessionFault value; returned what() pointer refers to static literal storage. |
| failure | This exception only represents coordinator checks; it is not a replacement for MemoryFailure, ImageFailure, FileFailure, GenerationFailure, or semantic SQL Error. |
| cost | Fixed object construction; no formatting, string copy, or allocation. |
| Design | [docs/sql_aggregate_session.md](../../../../../sql_aggregate_session.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/query_memory.md](../../../../../query_memory.md) |

## B0008

[Lines 31–36](../../../../../../include/crown/recovery/sql_aggregate_session.hpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct SessionState {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the four durable/session frontiers and whether the sole pending input or output spool exists. |
| inputs / outputs | A ready Session in; fixed scalar snapshot out: logged W, disposed I, native committed C, sink delivered D, selected generation, and pending/spool flags. |
| invariants | W is the last Input command sequence, not a WAL frame ordinal. I is AccountedInputProgress.sequence, C is the actual native runtime sequence, and D is the actual sink prefix sequence. pending means one owned Head; output_pending means one owned canonical Frame spool. |
| ownership | The result owns only scalar values and booleans; it does not retain Session, file, or runtime state. |
| failure | Session::state requires a ready owner and rejects poisoned, missing, or reopen-required members; this value is not an authority to edit any frontier. |
| cost | Fixed-size copy plus the owner-state reads; no source rows or WAL frames are scanned. |
| Design | [docs/sql_aggregate_session.md](../../../../../sql_aggregate_session.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [build/verification/w06-r2-protocol-review-v1/protocol.md](../../../../../../build/verification/w06-r2-protocol-review-v1/protocol.md) |

## B0009

[Lines 37–40](../../../../../../include/crown/recovery/sql_aggregate_session.hpp#L37); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Decision {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the disposition of one command with command and physical frontiers kept separate. |
| inputs / outputs | Decided command sequence, resulting physical sequence, and optional semantic RejectReason in; fixed Decision value out. |
| invariants | command_sequence identifies W/I command order; physical_sequence identifies C and does not advance on Reject. rejected carries only a wire-supported semantic reason; resource and contract failures throw instead. |
| ownership | Owns two uint64 values and one optional enum; it carries no input, output, receipt, or runtime owner. |
| failure | No failure is represented in Decision. If no durable Commit/Reject was confirmed, decide throws and returns no Decision. |
| cost | Fixed-size return value. |
| Design | [docs/sql_aggregate_session.md](../../../../../sql_aggregate_session.md), [docs/sql_aggregate_records.md](../../../../../sql_aggregate_records.md), [build/verification/w06-r2-protocol-review-v1/protocol.md](../../../../../../build/verification/w06-r2-protocol-review-v1/protocol.md) |

## B0010

[Lines 41–47](../../../../../../include/crown/recovery/sql_aggregate_session.hpp#L41); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ReplayStatistics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report replayed Input/codec accounting and observed native/source work. |
| inputs / outputs | A replayed Session in; fixed counters for Input commands, codec work, native work, group work, and source IndexWork out. |
| invariants | commands counts replayed Inputs; codec_work counts the session-level Input decode, canonical output encoding, and full-output hash visits under SessionLimits. native_work, group_work, and source_work are accumulated observations from successful replayed Commits; they do not preempt native replay or change original per-command grants. |
| ownership | The value owns only counters; reading it does not expose the runtime or a mutable allowance. |
| failure | Counter overflow or codec/command limit exhaustion fails replay before the recovered Session is exposed. |
| cost | Fixed-size copy. Counter additions are constant work per successful committed replay epoch. |
| Design | [docs/sql_aggregate_session.md](../../../../../sql_aggregate_session.md), [docs/sql_aggregate_records.md](../../../../../sql_aggregate_records.md), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md) |

## B0011

[Lines 48–83](../../../../../../include/crown/recovery/sql_aggregate_session.hpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Session {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Present the synchronous, single-writer owner for genuine SQL aggregate state, durable input/output, and selected recovery root. |
| inputs / outputs | A receiving MemoryAccount and either the genuine SQL program/tree/options or a selected query root/path in; one move-only Session owner out. Factory limits are borrowed by const reference through return; their fixed live bounds are retained by value. |
| invariants | The owner controls the actual SqlAggregateRuntime, GenerationOwner, WalFile, SinkFile, input progress, at most one logged Head, and at most one committed output spool. Calls and borrows are serialized. W/I/C/D are distinct and may diverge only at the documented pending/reject/delivery boundaries. |
| ownership | AccountedUnique&lt;Data&gt; retains the receiving account and all session members. Session is noncopyable; lvalue-qualified views borrow its funded members and rvalue overloads are deleted. The caller may mutate/destroy its SessionLimits after return; no host DTO reference or owning binder-vector copy is retained. |
| failure | Input/resource preparation can leave one logged head pending. Uncertain file/root publication requires reopen/recovery. The public class does not add a generic retry engine, an undo framework, CLI, or R2 history retirement. |
| cost | Snapshot/status access is bounded by the selected native API; command work includes native prepare, canonical epoch preparation, and durable file operations. This interface claims no CPU or preemptive replay budget. |
| Design | [docs/sql_aggregate_session.md](../../../../../sql_aggregate_session.md), [docs/sql_aggregate_runtime.md](../../../../../sql_aggregate_runtime.md), [docs/sql_aggregate_files.md](../../../../../sql_aggregate_files.md), [docs/generations.md](../../../../../generations.md), [Refactor.md §8.3](../../../../../../Refactor.md), [Refactor.md §11.7 O05](../../../../../../Refactor.md), [Refactor.md §11.9 W06](../../../../../../Refactor.md) |

## B0012

[Lines 84–95](../../../../../../include/crown/recovery/sql_aggregate_session.hpp#L84); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] Decision decide() &;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the lvalue-only public access and command operations for an already owning Session. |
| inputs / outputs | A live lvalue Session in; borrowed descriptor/progress/input/output views, fixed status/metrics, delegated snapshot/weight observations, or the result of log/decide/deliver/checkpoint. |
| invariants | Borrowed descriptor/progress/input/output APIs delete rvalue overloads so their storage cannot be obtained through a temporary Session. Mutating command methods are lvalue-qualified and follow W/I/C/D admission, disposition, and delivery boundaries. |
| ownership | Returned references/views borrow Session::Data and expire when its owner or backing Head/spool changes; scalar status/Decision/metrics values own their fields. |
| failure | The declarations do not translate lower-layer errors. Definitions preserve readiness, resource, semantic Reject, file uncertainty, and checkpoint selection boundaries. |
| cost | Declarations add no runtime cost; each definition's cost is specified at its own source block. |
| Design | [docs/sql_aggregate_session.md](../../../../../sql_aggregate_session.md), [include/crown/recovery/sql_aggregate_session.hpp](../../../../../../include/crown/recovery/sql_aggregate_session.hpp), [build/verification/w06-r2-protocol-review-v1/actual-apis.md](../../../../../../build/verification/w06-r2-protocol-review-v1/actual-apis.md) |
