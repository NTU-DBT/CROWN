# `src/recovery/sql_aggregate_session_replay.cpp` — block usage map

[Source](../../../../../src/recovery/sql_aggregate_session_replay.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Encode, validate and publish checkpoints, journals, generations and local delivery receipts with explicit durable authority.

Snapshot SHA-256: `223d6815cef3dfcaba06dc14d76f49aa203c220b196ef8e5b5edf1c75cf74b94`. 81 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [recovery](../../../subsystem_contracts.md#recovery). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/checkpoints.md](../../../../checkpoints.md), [docs/journal.md](../../../../journal.md), [docs/journal-files.md](../../../../journal-files.md), [docs/generations.md](../../../../generations.md), [docs/local-sink.md](../../../../local-sink.md), [docs/history-retirement.md](../../../../history-retirement.md), [docs/update_patterns.md](../../../../update_patterns.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../src/recovery/sql_aggregate_session_replay.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 6–34](../../../../../src/recovery/sql_aggregate_session_replay.cpp#L6) | Callable definition: void Session::replay(std::string_view bytes,const Inspected& info,const WalState& after,void* context) | calls state, require, sequence, decode_input; guard require(!d.head && !d.spool && d.native.sequence()&lt;=delivered,SessionFault::binding);; growth emplace; source comment (unverified): // Logging a later Input proves the previous C was already acknowledged. · [reviewed contract](#b0002) |
| [B0003 · 35–40](../../../../../src/recovery/sql_aggregate_session_replay.cpp#L35) | Callable definition: void Session::validate_files(Data& d) | calls validate, require, read_root, selected; guard require(d.root.read_root(false,false)==d.root.selected(),SessionFault::binding); · [reviewed contract](#b0003) |
| [B0004 · 41–80](../../../../../src/recovery/sql_aggregate_session_replay.cpp#L41) | Callable definition: Session Session::recover_into(const resource::MemoryAccount& account,SessionPaths paths,const Id& query_id,const SessionLimits& l… | calls require, root, selected, retirement; guard require(limits.history_generations&gt;0,SessionFault::limit);; returns std::move(admitted.descriptor); restore_checkpoint_into(account,descriptor,{bytes.data(),bytes.size…; growth emplace, make_accounted_unique; source comment (unverified): // Rebinding's empty/static C0 runtime dies before the actual checkpoint owner · [reviewed contract](#b0004) |
| [B0005 · 81–81](../../../../../src/recovery/sql_aggregate_session_replay.cpp#L81) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::recovery::sql_aggregate · [reviewed contract](#b0005) |

## B0001

[Lines 1–5](../../../../../src/recovery/sql_aggregate_session_replay.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "sql_aggregate_session_detail.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compile replay against the private session owner and exact R2 digest implementation. |
| inputs / outputs | Replay implementation translation unit in; Session::replay, file validation, and recovery-factory definitions out. |
| invariants | This file reuses Data, codecs, GenerationOwner, WalFile, SinkFile, and fixed SHA256 helpers; it does not implement alternate replay or digest authority. |
| ownership | Includes create no runtime state; Data owns every replayed object. |
| failure | Missing/incompatible dependencies fail at compile time. This setup region adds no exception translation. |
| cost | Compile-time only. |
| Design | [src/recovery/sql_aggregate_session_detail.hpp](../../../../../src/recovery/sql_aggregate_session_detail.hpp), [include/crown/ir/digest.hpp](../../../../../include/crown/ir/digest.hpp), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0002

[Lines 6–34](../../../../../src/recovery/sql_aggregate_session_replay.cpp#L6); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Session::replay(std::string_view bytes,const Inspected& info,const WalState& after,void* context)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replay each complete validated WAL frame against the genuine private runtime and actual sink coverage without exposing tentative state. |
| inputs / outputs | Complete frame bytes, validated R2 frame metadata, resulting WAL cursor state, and private Data context in; private replay state advanced or an exception out. |
| invariants | A later Input requires no Head/spool and proves current C is already covered by actual D. Reject is reproduced through the exact semantic allowlist and advances I only. Commit is prepared natively, canonically re-encoded and matched to decision size/hash; already delivered epochs compare full bytes through SinkFile, while only the next missing epoch becomes the one spool. C/I must match the WAL cursor after each decision. |
| ownership | Input frames become one owned Head; the native token is committed only after replay checks; a missing output Frame moves into Data. SinkFile is the real locked owner used for byte verification. |
| failure | Any malformed/mismatched frame, semantic mismatch, work/counter limit, output mismatch, or coverage contradiction aborts recovery; local private owners unwind and no Session is returned. |
| cost | O(all admitted WAL bytes and commands) plus genuine native work, canonical group encoding, and bounded full-byte sink checks for already present epochs. It retains no output backlog: at most one final spool. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/sql_aggregate_checkpoint.md](../../../../sql_aggregate_checkpoint.md), [build/verification/w06-r2-protocol-review-v1/protocol.md](../../../../../build/verification/w06-r2-protocol-review-v1/protocol.md), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md) |

## B0003

[Lines 35–40](../../../../../src/recovery/sql_aggregate_session_replay.cpp#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void Session::validate_files(Data& d)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail-stop while checking continuity of the actual held sink/WAL extents and selected root. |
| inputs / outputs | Private Data and its accepted full physical file stamps enter; stat/EOF/stat for each file and an exact bounded root reread must succeed before poison clears. |
| invariants | poisoned is set before either file check and clears only after the actual named root equals the held selection. These are continuity checks after full opening scans/replay, not new prefix scans, decoding or hashes of all file bytes. Recovery repeats them before and after repair. |
| ownership | Uses the actual locked file owners and GenerationOwner; it neither creates a receipt nor changes selected generation. |
| failure | Validation/stamp/root mismatch propagates with poisoned retained. In recover_into the owner is still private and is destroyed on failure. |
| cost | Two three-call stamp/EOF barriers plus the bounded selected-root read/validation and admitted retries. Constant stack space, no C++ allocation and no sink/WAL history-length rescan. File/generation attempt caps do not bound kernel latency. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/generations.md](../../../../generations.md), [build/verification/w06-r2-protocol-review-v1/protocol.md](../../../../../build/verification/w06-r2-protocol-review-v1/protocol.md) |

## B0004

[Lines 41–80](../../../../../src/recovery/sql_aggregate_session_replay.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Session Session::recover_into(const resource::MemoryAccount& account,SessionPaths paths,const Id& query_id,const SessionLimits& limits)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebuild and expose a session only after selected descriptor/checkpoint, actual sink, full WAL replay, coverage, and tail-repair barriers agree. |
| inputs / outputs | Receiving account, borrowed paths/const SessionLimits&, expected query ID and finite host caps enter; one ready Session returns after the complete recovery barrier. |
| invariants | Hold the actual GenerationOwner lock; require selected plan hash, delivery anchor, C&lt;=I, first_generation=1, generation&lt;=history_generations, and no R1 retirement intent. Rebind the saved descriptor through the genuine path, read the selected opaque checkpoint, restore through the actual cold runtime factory, open/validate the actual sink, then replay the selected WAL. Require sink_floor&lt;=D&lt;=final C and D=C when a Head remains. Validate all files/root before repairing either incomplete tail, then validate again before return. |
| ownership | A single receiver-account Data owns the reconstructed runtime, root/WAL/sink locks, progress, and at most one Head and one missing output spool. GenerationOwner::read_checkpoint returns opaque bounded bytes; SQL/native interpretation remains in restore_checkpoint_into and rebind. No caller configuration reference survives return. Only fixed live bounds are retained; genuine rebind can transiently copy caller binder options before replacing parameter identity with saved metadata. |
| failure | Any identity, source/native, semantic replay, output, coverage, tail, limit, or file/root failure destroys the private owner and returns no Session. Only validated incomplete tails may be repaired; complete malformed records and complete pending Input frames remain intact and decisive. |
| cost | Cold genuine descriptor rebind and whole-source/native rebuild, one complete sink opening scan and one complete WAL opening scan/replay, canonical output encoding/hash and full-byte checks of already delivered epochs. Two subsequent stamp/EOF/root continuity barriers do not rescan histories. Optional tail repair spends separate truncate/fsync/stat attempts under file caps. Command/codec/rebuild/file allowances remain separate; no CPU or kernel-latency bound is claimed. The Session adds no host-payload copies beyond that existing direct-rebind transient work; current differential allocation tests verify this without new instrumentation. |
| Design | [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [docs/sql_aggregate_descriptor.md](../../../../sql_aggregate_descriptor.md), [docs/sql_aggregate_checkpoint.md](../../../../sql_aggregate_checkpoint.md), [docs/sql_aggregate_records.md](../../../../sql_aggregate_records.md), [docs/sql_aggregate_files.md](../../../../sql_aggregate_files.md), [docs/generations.md](../../../../generations.md), [docs/verification/o05-session-journal-2026-11-10.md](../../../../verification/o05-session-journal-2026-11-10.md), [build/verification/w06-r2-protocol-review-v1/actual-apis.md](../../../../../build/verification/w06-r2-protocol-review-v1/actual-apis.md), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md), [Refactor.md §8.3](../../../../../Refactor.md), [Refactor.md §11.7 O05](../../../../../Refactor.md), [Refactor.md §11.9 W06](../../../../../Refactor.md) |

## B0005

[Lines 81–81](../../../../../src/recovery/sql_aggregate_session_replay.cpp#L81); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
} // namespace crown::recovery::sql_aggregate
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the replay implementation namespace after recovery and barrier definitions. |
| inputs / outputs | Open SQL aggregate recovery namespace in; translation-unit scope closed out. |
| invariants | This delimiter adds no state, file operation, replay authority, or error policy. |
| ownership | No object ownership. |
| failure | Malformed scope is a compile-time error only. |
| cost | Compile-time syntax only. |
| Design | [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp) |
