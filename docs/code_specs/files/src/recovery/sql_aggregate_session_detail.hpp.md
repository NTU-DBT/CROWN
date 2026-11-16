# `src/recovery/sql_aggregate_session_detail.hpp` — block usage map

[Source](../../../../../src/recovery/sql_aggregate_session_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `624e57897c8d83a340e676753c7a5c2e5e1b8e8362571ceda312167ef0d66adc`. 58 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../../src/recovery/sql_aggregate_session_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | guard void require(bool,SessionFault=SessionFault::state);; source comment (unverified): // Private ownership order closes head/spool and file locks before native/root · [reviewed contract](#b0001) |
| [B0002 · 18–23](../../../../../src/recovery/sql_aggregate_session_detail.hpp#L18) | Type/record definition: struct LiveLimits | source comment (unverified): // Retain only bounds needed by operations/replay. Caller-owned cold binder · [reviewed contract](#b0002) |
| [B0003 · 24–24](../../../../../src/recovery/sql_aggregate_session_detail.hpp#L24) | declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_trivially_copyable_v&lt;LiveLimits&gt;); · [reviewed contract](#b0003) |
| [B0004 · 25–28](../../../../../src/recovery/sql_aggregate_session_detail.hpp#L25) | Type/record definition: struct Head |  · [reviewed contract](#b0004) |
| [B0005 · 29–32](../../../../../src/recovery/sql_aggregate_session_detail.hpp#L29) | Type/record definition: struct Prepared |  · [reviewed contract](#b0005) |
| [B0006 · 33–58](../../../../../src/recovery/sql_aggregate_session_detail.hpp#L33) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::recovery::sql_aggregate · [reviewed contract](#b0006) |

## B0001

[Lines 1–17](../../../../../src/recovery/sql_aggregate_session_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the concrete Data layout and helpers private to the session implementation. |
| inputs / outputs | Public session/file/checkpoint declarations and private generation detail in; internal Head/Prepared/Data declarations available to the two implementation files. |
| invariants | The public API does not expose Session::Data, PreparedBatch, or GenerationOwner as caller-editable recovery authority. |
| ownership | Header inclusion creates no runtime owner; actual member ownership begins in Data construction. |
| failure | Unavailable or mismatched private dependencies fail at compile time; no runtime error is emitted by this region. |
| cost | Compile-time preprocessing and type declarations only. |
| Design | [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [src/recovery/generation_detail.hpp](../../../../../src/recovery/generation_detail.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0002

[Lines 18–23](../../../../../src/recovery/sql_aggregate_session_detail.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct LiveLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain only the fixed caps used by Session operations and private recovery replay. |
| inputs / outputs | Checkpoint/capture, WAL/sink, durable-history, replay-command and replay-codec values are projected from caller SessionLimits into seven fields/groups. |
| invariants | Declaration/constructor order matches the exact memberwise projection. Cold admission/rebuild/repair remain factory-local; GenerationOwner already retains generation limits. The compile-time trivial-copy guard rejects owning vector/string additions to this record. |
| ownership | Fixed values live inside the account-owned Data allocation; no caller reference, binder parameter payload or new configuration owner. |
| failure | The declaration has no runtime handler; factory/member construction failures keep existing owning cleanup. |
| cost | Fixed-size memberwise copying with no C++ allocation, indirection, virtual dispatch or per-row configuration bridge. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [src/recovery/sql_aggregate_session.cpp](../../../../../src/recovery/sql_aggregate_session.cpp), [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp) |

## B0003

[Lines 24–24](../../../../../src/recovery/sql_aggregate_session_detail.hpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L24:sha256:f5b72fd376ce6c7aa1f8770a63033fe9bf5f8e4b78bdc907a72887f3a91919de
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Requires LiveLimits to remain trivially copyable at compile time because the session stores/copies this fixed live-policy record. |
| inputs / outputs | No runtime values are exchanged; the compiler evaluates the assertion during translation and rejects the build if it is false. |
| invariants | The stated type/layout condition must remain true for this translation unit to compile. |
| ownership | Compile-time only; no object owner is created. |
| failure | A false condition is a compile-time diagnostic, not a runtime exception. |
| cost | Compile-time checking only; no runtime cost. |
| Design | [src/recovery/sql_aggregate_session_detail.hpp](../../../../../src/recovery/sql_aggregate_session_detail.hpp), [docs/code_specs/files/src/recovery/sql_aggregate_session_detail.hpp.md](sql_aggregate_session_detail.hpp.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md) |

## B0004

[Lines 25–28](../../../../../src/recovery/sql_aggregate_session_detail.hpp#L25); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Head {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the sole decoded, logged Input and the pre-funded but unpublished source-position change. |
| inputs / outputs | DecodedInput plus InputPositions::Prepared in; one move-only Head retaining the complete frame/rows and position candidate out. |
| invariants | The candidate belongs to the live progress map but is not published until durable Commit or Reject. The input view borrows the decoded frame and remains valid while this Head is alive. |
| ownership | DecodedInput owns its complete frame and flat cells/replacements. Prepared owns a detached funded node for a new source, or borrows an existing map iterator; that existing node remains owned by the live progress map, which outlives Head. |
| failure | Construction/preparation failures occur before WAL mutation. Destroying an unpublished Head releases the input and candidate without advancing I or source positions. |
| cost | Owns one encoded Input plus its decoded view storage and the single source-position candidate; it is not a command queue. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [build/verification/w06-r2-protocol-review-v1/actual-apis.md](../../../../../build/verification/w06-r2-protocol-review-v1/actual-apis.md) |

## B0005

[Lines 29–32](../../../../../src/recovery/sql_aggregate_session_detail.hpp#L29); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Prepared {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the genuine native batch token or one explicitly supported semantic Reject result private to the decision path. |
| inputs / outputs | A successful SqlAggregateRuntime::PreparedBatch token or an allowlisted RejectReason in; private preparation state out. |
| invariants | The token is the only native/source/group rollback authority and stays active through preview/output and durable decision append. A semantic error has already unwound the native preparation; resource and contract failures are not represented as Reject. |
| ownership | optional&lt;PreparedBatch&gt; owns the active move-only token until commit or RAII rollback; RejectReason is a fixed value. |
| failure | No generic exception-to-Reject conversion is permitted. Any failed pre-decision preparation destroys the token and leaves the logged Head available for retry. |
| cost | Fixed optional/value state plus the native token's already funded staging. No second journal or copied runtime state is created. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [build/verification/w06-r2-protocol-review-v1/protocol.md](../../../../../build/verification/w06-r2-protocol-review-v1/protocol.md) |

## B0006

[Lines 33–58](../../../../../src/recovery/sql_aggregate_session_detail.hpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
resource::MemoryAccount account;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the one private ownership aggregate and its fail-stop readiness boundary. |
| inputs / outputs | Receiver account, fixed LiveLimits projection, real root/descriptor/runtime/progress and optional reader initialize the private owner; it later owns actual WAL/sink and one Head/spool. |
| invariants | Declaration order makes Head/spool and SinkFile/WalFile destruct before native runtime and root, while the account is destroyed last. ready rejects poison, missing/reopen-required files, non-ready native state, or absent root selection. No second live database or replay output queue is stored. |
| ownership | Data owns the actual root lock, WAL/sink locks, native runtime, progress map, pending input, and canonical output Frame under the receiver account. Only fixed operation/replay caps are retained; caller admission/binder payloads and other cold-only configuration are not copied or referenced. |
| failure | poisoned latches uncertain native publication, root selection, or full-file validation; callers cannot use normal accessors while latched. Destruction releases owners in the declared order. |
| cost | Fixed owner/control state plus live native tables, one pending Input, one output Frame, and per-file indexes; cost scales with the actual retained state, not a shadow copy. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/query_memory.md](../../../../query_memory.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/generations.md](../../../../generations.md) |
