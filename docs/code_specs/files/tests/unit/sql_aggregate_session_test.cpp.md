# `tests/unit/sql_aggregate_session_test.cpp` — block usage map

[Source](../../../../../tests/unit/sql_aggregate_session_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `2635146178cc756f247cd4e47c4ed430e68cfd3e5d78f391469ade05fc44921e`. 320 lines partitioned into 28 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../tests/unit/sql_aggregate_session_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(std::is_same_v&lt;decltype(&ar::Session::create_into),CreateFactory&gt;);; source comment (unverified): // Real WAL decisions couple nullable physical weights, native groups, source/ · [reviewed contract](#b0001) |
| [B0002 · 16–43](../../../../../tests/unit/sql_aggregate_session_test.cpp#L16) | Callable definition: void lifecycle(bool indexed) | calls f, emplace, create, state; guard assert(s-&gt;selected_root().plan_sha256 && s-&gt;selected_root().delivery);; growth emplace; source comment (unverified): // Real WAL decisions couple nullable physical weights, native groups, source/ · [reviewed contract](#b0002) |
| [B0003 · 44–45](../../../../../tests/unit/sql_aggregate_session_test.cpp#L44) | Explanatory comments or spacing. | source comment (unverified): // Every supported rejection is produced by the genuine native factory. Resource · [reviewed contract](#b0003) |
| [B0004 · 46–72](../../../../../tests/unit/sql_aggregate_session_test.cpp#L46) | Callable definition: void semantic_rejections() | calls schema, push_back, f, emplace; guard assert(result.rejected==expected);state(*owner,1,1,0,0);assert(owner-&gt;source_weight(edits\[0\].source…; growth emplace, push_back; 1 loop sites; source comment (unverified): // Every supported rejection is produced by the genuine native factory. Resource · [reviewed contract](#b0004) |
| [B0005 · 73–75](../../../../../tests/unit/sql_aggregate_session_test.cpp#L73) | Explanatory comments or spacing. | source comment (unverified): // Integer guards are reconstructed from original SQL during descriptor rebind. · [reviewed contract](#b0005) |
| [B0006 · 76–139](../../../../../tests/unit/sql_aggregate_session_test.cpp#L76) | Callable definition: void varying_integer_recovery(bool indexed) | calls f, schema, text, number; guard auto owner = f.create(); assert(!step(owner, seed).rejected);; source comment (unverified): // Integer guards are reconstructed from original SQL during descriptor rebind. · [reviewed contract](#b0006) |
| [B0007 · 140–141](../../../../../tests/unit/sql_aggregate_session_test.cpp#L140) | Explanatory comments or spacing. | source comment (unverified): // Pending logged input survives a resource failure and cold reopen without a · [reviewed contract](#b0007) |
| [B0008 · 142–152](../../../../../tests/unit/sql_aggregate_session_test.cpp#L142) | Callable definition: void pending_and_progress() | calls number, create, log, deny; guard assert(failed && !s.requires_reopen());state(s,1,0,0,0);assert(s.pending_input() && s.progress().so…; 1 loop sites; source comment (unverified): // Pending logged input survives a resource failure and cold reopen without a · [reviewed contract](#b0008) |
| [B0009 · 153–154](../../../../../tests/unit/sql_aggregate_session_test.cpp#L153) | Explanatory comments or spacing. | source comment (unverified): // A recorded Reject is evidence to verify, never permission to skip the native · [reviewed contract](#b0009) |
| [B0010 · 155–178](../../../../../tests/unit/sql_aggregate_session_test.cpp#L155) | Callable definition: void semantic_corruption() | calls number, create, log, assert; guard {auto s=f.create();s.log({1,edit,ar::SourcePosition{"feed",10},ar::ReaderPosition{10,1}});assert(s.…; growth copy_of; source comment (unverified): // A recorded Reject is evidence to verify, never permission to skip the native · [reviewed contract](#b0010) |
| [B0011 · 179–180](../../../../../tests/unit/sql_aggregate_session_test.cpp#L179) | Explanatory comments or spacing. | source comment (unverified): // A later pending Input or Reject also proves the previous output was delivered. · [reviewed contract](#b0011) |
| [B0012 · 181–189](../../../../../tests/unit/sql_aggregate_session_test.cpp#L181) | Callable definition: void final_sink_floor() | calls number, create, assert, step; guard {auto s=f.create();assert(!step(s,edit).rejected);edit\[0\].before=9;edit\[0\].after=0;s.log({2,edit,{}…; 1 loop sites; source comment (unverified): // A later pending Input or Reject also proves the previous output was delivered. · [reviewed contract](#b0012) |
| [B0013 · 190–191](../../../../../tests/unit/sql_aggregate_session_test.cpp#L190) | Explanatory comments or spacing. | source comment (unverified): // Recovery owns only one final missing output. A later Input proves prior D=C; · [reviewed contract](#b0013) |
| [B0014 · 192–207](../../../../../tests/unit/sql_aggregate_session_test.cpp#L192) | Callable definition: void sink_floor_and_repair() | calls number, create, assert, step; guard {auto s=f.create();assert(!step(s,edits).rejected);edits\[0\].before=1;edits\[0\].after=2;assert(!step(…; source comment (unverified): // Recovery owns only one final missing output. A later Input proves prior D=C; · [reviewed contract](#b0014) |
| [B0015 · 208–209](../../../../../tests/unit/sql_aggregate_session_test.cpp#L208) | Explanatory comments or spacing. | source comment (unverified): // Cold-only codec/command bounds are cumulative; original normal policies can · [reviewed contract](#b0015) |
| [B0016 · 210–220](../../../../../tests/unit/sql_aggregate_session_test.cpp#L210) | Callable definition: void cold_limits_and_history() | calls reset, number, create, assert; guard {auto s=f.create();assert(!step(s,edits).rejected);}; source comment (unverified): // Cold-only codec/command bounds are cumulative; original normal policies can · [reviewed contract](#b0016) |
| [B0017 · 221–222](../../../../../tests/unit/sql_aggregate_session_test.cpp#L221) | Explanatory comments or spacing. | source comment (unverified): // Detection of a changed actual selected root invalidates the old owner even · [reviewed contract](#b0017) |
| [B0018 · 223–226](../../../../../tests/unit/sql_aggregate_session_test.cpp#L223) | Callable definition: void stale_root() | calls create, contents, put, refused; guard assert(s.requires_reopen());refused(\[&\]{static_cast&lt;void&gt;(s.state());});refused(\[&\]{s.log({1,{},{},…; source comment (unverified): // Detection of a changed actual selected root invalidates the old owner even · [reviewed contract](#b0018) |
| [B0019 · 227–228](../../../../../tests/unit/sql_aggregate_session_test.cpp#L227) | Explanatory comments or spacing. | source comment (unverified): // Complete original filtered/unused rows survive an actual selected checkpoint; · [reviewed contract](#b0019) |
| [B0020 · 229–243](../../../../../tests/unit/sql_aggregate_session_test.cpp#L229) | Callable definition: void complete_source() | calls f, number, text, create; guard {auto s=f.create();assert(s.snapshot().groups.size()==1);assert(!step(s,edits).rejected);assert(s.c…; 1 loop sites; source comment (unverified): // Complete original filtered/unused rows survive an actual selected checkpoint; · [reviewed contract](#b0020) |
| [B0021 · 244–245](../../../../../tests/unit/sql_aggregate_session_test.cpp#L244) | Explanatory comments or spacing. | source comment (unverified): // A fresh receiver owns all retained native/schema/output state. Exact observed · [reviewed contract](#b0021) |
| [B0022 · 246–264](../../../../../tests/unit/sql_aggregate_session_test.cpp#L246) | Callable definition: void receiving_account() | calls number, create, assert, step; guard {auto s=f.create();assert(!step(s,edits).rejected);if(pending) {edits\[0\].before=2;edits\[0\].after=3;…; returns ar::Session::recover_into(receiver,{f.root,f.sink},f.identity.query_id,f.limits); 1 loop sites; source comment (unverified): // A fresh receiver owns all retained native/schema/output state. Exact observed · [reviewed contract](#b0022) |
| [B0023 · 265–266](../../../../../tests/unit/sql_aggregate_session_test.cpp#L265) | Explanatory comments or spacing. | source comment (unverified): // Initial candidates are never auto-cleaned or overwritten. A failed create · [reviewed contract](#b0023) |
| [B0024 · 267–272](../../../../../tests/unit/sql_aggregate_session_test.cpp#L267) | Callable definition: void initial_collisions() | calls generation_file, put, refused, create; guard refused(\[&\]{auto s=f.create();});assert(contents(path)=="preexisting" && !std::filesystem::exists(f…; 1 loop sites; source comment (unverified): // Initial candidates are never auto-cleaned or overwritten. A failed create · [reviewed contract](#b0024) |
| [B0025 · 273–274](../../../../../tests/unit/sql_aggregate_session_test.cpp#L273) | Explanatory comments or spacing. | source comment (unverified): // Host binder payloads are cold caller DTOs. Session must add no extra copies: · [reviewed contract](#b0025) |
| [B0026 · 275–314](../../../../../tests/unit/sql_aggregate_session_test.cpp#L275) | Callable definition: void host_options() | calls push_back, std::string, emplace_back, create; guard assert(cp==ce && bp&gt;=be && rp&gt;=re && rp-re==bp-be);; returns s04_alloc::calls; s04_alloc::calls; growth emplace, emplace_back, push_back; 2 loop sites; source comment (unverified): // Host binder payloads are cold caller DTOs. Session must add no extra copies: · [reviewed contract](#b0026) |
| [B0027 · 315–315](../../../../../tests/unit/sql_aggregate_session_test.cpp#L315) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0027) |
| [B0028 · 316–320](../../../../../tests/unit/sql_aggregate_session_test.cpp#L316) | Callable definition: int main() | calls lifecycle, varying_integer_recovery, semantic_rejections, pending_and_progress; 1 loop sites · [reviewed contract](#b0028) |

## B0001

[Lines 1–15](../../../../../tests/unit/sql_aggregate_session_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using CreateFactory=ar::Session(*)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require both public factories to borrow the caller configuration instead of copying its owning DTO. |
| inputs / outputs | Explicit create/recover function-pointer types and decltype of the actual API must match const SessionLimits& signatures. |
| invariants | These compile-time contracts protect entry-call copying separately from the runtime payload/lifetime regression; they introduce no test-only product API. |
| ownership | Type aliases/assertions own no state or payload. |
| failure | A by-value signature regression fails compilation. |
| cost | Compile-time only; zero runtime instrumentation. |
| Design | [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [tests/unit/sql_aggregate_session_test.cpp](../../../../../tests/unit/sql_aggregate_session_test.cpp) |

## B0002

[Lines 16–43](../../../../../tests/unit/sql_aggregate_session_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void lifecycle(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise the real ordered and indexed Session lifecycle across pending input, commit, delivery, Reject, checkpoint rotation and cold recovery. |
| inputs / outputs | Indexed-mode selector in; assertions over real Session state, snapshots, WAL and sink frames out. |
| invariants | Caller row/source buffers may change after \`log\` without changing the owned pending input. A logged head and committed spool block the next input. Recovery preserves output and physical weights. Reject advances W/I but not C/D; the next command's transport ordinal differs from the runtime sequence. Checkpoint root stores physical C separately from command I. |
| ownership | Fixture owns the account and immutable binding; Session owns pending input, runtime and locked files; frame inspection is borrowed test evidence. |
| failure | Assertions or genuine binding/runtime/file/recovery errors fail the test. |
| cost | Two bounded lifecycle traces (ordered and indexed), a few small row replacements, multiple actual reopens and two generation checkpoints; not a latency or power-loss measurement. |
| Design | [tests/support/sql_aggregate_session_fixture.hpp](../../../../../tests/support/sql_aggregate_session_fixture.hpp), [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md), Refactor.md:1325, [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0003

[Lines 44–45](../../../../../tests/unit/sql_aggregate_session_test.cpp#L44); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L44-L45:sha256:055f746419a35092c65cf1cdaf143b4292e15447ee75a477c514fd57d655714a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Every supported rejection is produced by the genuine native factory. Resource failures have no Reject tag and cannot advance I/C. A valid retry follows each. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_session_test.cpp](../../../../../tests/unit/sql_aggregate_session_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 46–72](../../../../../tests/unit/sql_aggregate_session_test.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void semantic_rejections()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the explicit native semantic-Reject allowlist and atomic multi-source rollback using genuine Session decisions. |
| inputs / outputs | Fresh bounded fixtures for multiplicity, count, UNIQUE, FK and mixed-source annotation cases in; Reject reason, W/I/C/D, unchanged physical weights, recovery and valid-retry assertions out. |
| invariants | The tested Reject cases advance W/I only and emit no group output; recovery reproduces the same semantic decision. An annotation overflow in a mixed batch publishes none of its source edits. The next valid replacement succeeds. This does not authorize arbitrary \`*_overflow\`, internal or resource failures as Reject. |
| ownership | Every case is independently created/recovered through the real receiving-account Session factories; rows are borrowed only for log and then Session-owned. |
| failure | Unexpected Reject code, partial source mutation, changed frontier or failed recovery/retry fails an assertion or propagates the native error. |
| cost | Four small single-source reject/retry scenarios and one two-source mixed-batch reject/retry scenario, each with genuine replay. |
| Design | [src/recovery/sql_aggregate_session.cpp](../../../../../src/recovery/sql_aggregate_session.cpp), [include/crown/runtime/sql_aggregate.hpp](../../../../../include/crown/runtime/sql_aggregate.hpp), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0005

[Lines 73–75](../../../../../tests/unit/sql_aggregate_session_test.cpp#L73); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L73-L75:sha256:a8c501d6b8761c8d6472d74a304396d821e75ae32ea72cc62542b8d5586c1043
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Integer guards are reconstructed from original SQL during descriptor rebind. A pending cast refusal disposes I/reader progress without C/D; a later signed cancellation commits atomically and survives a complete selected checkpoint. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_session_test.cpp](../../../../../tests/unit/sql_aggregate_session_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 76–139](../../../../../tests/unit/sql_aggregate_session_test.cpp#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void varying_integer_recovery(bool indexed)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check authentic integer-cast rebind, pending Reject, progress and checkpoint semantics. |
| inputs / outputs | Filtered out-of-range source, pending visible overflow, checksum-valid wrong Reject with torn suffixes, balanced large signed batch, unbalanced final refusal and final erase on both backends. |
| invariants | Reject advances W/I/reader while C/D stay. Reopen recomputes the actual failure before repair. Complete checkpoints retain filtered original rows and checked guards; later valid commits reach the real sink. |
| ownership | Fixture owns actual Session files/account; snapshots and encoded records own receiving buffers. |
| failure | False reason blocks both WAL/sink repair; valid overflow maps to aggregate_overflow; state/source/output mismatches assert. |
| cost | Finite actual WAL/recovery/checkpoint/sink operations; no host power-loss or history-retirement claim. |
| Design | [tests/support/sql_aggregate_session_fixture.hpp](../../../../../tests/support/sql_aggregate_session_fixture.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [src/frontend/aggregate.cpp](../../../../../src/frontend/aggregate.cpp), [src/runtime/aggregate_detail.hpp](../../../../../src/runtime/aggregate_detail.hpp) |

## B0007

[Lines 140–141](../../../../../tests/unit/sql_aggregate_session_test.cpp#L140); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L140-L141:sha256:5b077a62235ff6bd0f1db4f1a80376fd816a541d700ef7bfb875f0f5ef5ae656
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Pending logged input survives a resource failure and cold reopen without a second Input record. Source/reader and log ordinals are asserted separately. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_session_test.cpp](../../../../../tests/unit/sql_aggregate_session_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 142–152](../../../../../tests/unit/sql_aggregate_session_test.cpp#L142); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void pending_and_progress()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify a resource failure leaves one durably logged command pending with unpublished source and reader progress. |
| inputs / outputs | One logged physical replacement plus source/reader position in; W/I/C/D, pending head, cold recovery and same-head retry assertions out. |
| invariants | The injected \`std::bad_alloc\` is not encoded as Reject; W advances while I/C/D and published positions remain unchanged. Reopen recovers the same logged Input without a second append. Source offsets, reader record/byte positions and the transport command ordinal remain distinct. |
| ownership | Fixture owns its account; Session owns the persisted pending head and prepared position until a successful decision. |
| failure | The expected allocation failure is caught locally; wrong exception, published progress, lost pending input or failed retry fails the assertions. |
| cost | One C++-new denial, one cold recovery, one successful retry/delivery and two small position advances. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [include/crown/io/input_progress.hpp](../../../../../include/crown/io/input_progress.hpp), [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0009

[Lines 153–154](../../../../../tests/unit/sql_aggregate_session_test.cpp#L153); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L153-L154:sha256:2e6f00ee2758a77009e5756d694f7c7518dc0809cda875335f6bc8f0cc338ba1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: A recorded Reject is evidence to verify, never permission to skip the native attempt. False reasons/successful Inputs and false sink values block all repair. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_session_test.cpp](../../../../../tests/unit/sql_aggregate_session_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 155–178](../../../../../tests/unit/sql_aggregate_session_test.cpp#L155); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void semantic_corruption()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require genuine semantic replay to reject checksum-valid false decisions and false sink output before repairing any torn suffix. |
| inputs / outputs | Valid session histories plus resealed or freshly encoded wrong Reject/GroupEpoch records and torn suffixes in; refusal and byte-for-byte WAL/sink preservation assertions out. |
| invariants | Transport-valid checksums do not authorize a false Reject reason, a false group before/after image or a Reject contradicting a successful Commit. Recovery tests the actual native decision/output and must finish the selected-set validation barrier before tail repair. |
| ownership | The fixture owns files/account; encoded tampered frames and snapshots are test-owned; production recovery reopens and validates the actual selected files. |
| failure | Each hostile history must be refused without changing either file; valid restored files then recover and accept the intended next command. |
| cost | Three bounded hostile histories, including real checksum/frame encoding, production recovery attempts and exact file comparisons. |
| Design | [tests/support/sql_aggregate_session_fixture.hpp](../../../../../tests/support/sql_aggregate_session_fixture.hpp), [src/recovery/sql_aggregate_session_replay.cpp](../../../../../src/recovery/sql_aggregate_session_replay.cpp), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0011

[Lines 179–180](../../../../../tests/unit/sql_aggregate_session_test.cpp#L179); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L179-L180:sha256:c4043ce268afd52d26bd6dbe7c7aaf1660b0d0d139e1802bdd1c210d1a055c72
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: A later pending Input or Reject also proves the previous output was delivered. Removing that actual epoch must fail before a torn WAL/sink can be repaired. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_session_test.cpp](../../../../../tests/unit/sql_aggregate_session_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 181–189](../../../../../tests/unit/sql_aggregate_session_test.cpp#L181); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void final_sink_floor()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify a later pending Input or Reject proves that every earlier committed sink epoch was delivered. |
| inputs / outputs | One committed epoch followed by a pending or rejected command in; removal of the prior real sink epoch plus torn suffixes and refusal assertions out. |
| invariants | The prior output cannot be omitted just because the terminal WAL record is pending or Reject. Restoring the exact sink prefix allows recovery; the pending case remains pending for the same decision. |
| ownership | Actual WAL/sink files and Session locks remain under the fixture's temporary directory and receiving account. |
| failure | Recovery must refuse a sink below the recorded floor without truncating either torn suffix; restored authoritative bytes must recover. |
| cost | Two small one-commit traces, one with a pending head and one with Reject, with bounded file edits and reopen. |
| Design | [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0013

[Lines 190–191](../../../../../tests/unit/sql_aggregate_session_test.cpp#L190); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L190-L191:sha256:98e3cd072cc6bc3e58dd9d30fd138dbd1d22cc9e5586c707cb708161f7056e2a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Recovery owns only one final missing output. A later Input proves prior D=C; missing earlier output or a sink ahead of genuine WAL replay is rejected. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_session_test.cpp](../../../../../tests/unit/sql_aggregate_session_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 192–207](../../../../../tests/unit/sql_aggregate_session_test.cpp#L192); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void sink_floor_and_repair()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the one-final-output-spool recovery bound, output-prefix consistency and the complete validation barrier before tail repair. |
| inputs / outputs | Two committed epochs plus selected WAL/sink truncations, torn suffixes and a resealed false output identity in; exact recovered W/I/C/D/output or refusal/file-preservation assertions out. |
| invariants | Only the final committed epoch may be absent and retained for delivery. Missing an earlier epoch, a sink ahead of genuine WAL replay, or a checksum-valid Commit with false output identity is refused. Complete frames are semantically replayed before repair; disabling repair leaves incomplete tails unchanged and refuses recovery. |
| ownership | Session owns at most its final output spool; file bytes and mutations are controlled by the fixture; no recovered output queue is accumulated. |
| failure | Impossible prefix/identity combinations fail recovery before either file changes; a permitted final missing epoch is delivered once and the actual sink bytes match. |
| cost | Two committed epochs, a bounded set of prefix/tail mutations and full replay of each tiny WAL/sink on every reopen. |
| Design | [src/recovery/sql_aggregate_session_replay.cpp](../../../../../src/recovery/sql_aggregate_session_replay.cpp), [include/crown/recovery/sql_aggregate_files.hpp](../../../../../include/crown/recovery/sql_aggregate_files.hpp), [docs/sql_aggregate_checkpoint.md](../../../../sql_aggregate_checkpoint.md), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0015

[Lines 208–209](../../../../../tests/unit/sql_aggregate_session_test.cpp#L208); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L208-L209:sha256:5e12a8cbf40c93de7c7fe4706068fcd8f8b292a9dd8be0da6984f17e83ad6e7b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Cold-only codec/command bounds are cumulative; original normal policies can remain disabled. Root rotation never resets the durable history cap. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_session_test.cpp](../../../../../tests/unit/sql_aggregate_session_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 210–220](../../../../../tests/unit/sql_aggregate_session_test.cpp#L210); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cold_limits_and_history()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check cumulative cold-replay command/codec limits and that repeated checkpoint rotation cannot reset the configured history-generation cap. |
| inputs / outputs | One committed session with normal operational work limits disabled in the fixture; exact-limit and one-under replay grants plus a small history cap in; replay-statistic and checkpoint-refusal assertions out. |
| invariants | Cold codec/command work is separately bounded from original per-command policies. A failed over-cap checkpoint does not poison the still-selected owner; reopening does not replenish the durable generation history allowance. |
| ownership | Fixture account and actual root/WAL/sink are reused; each recovery reconstructs state through the genuine Session factory. |
| failure | Exact limits must admit, one-under and zero-command limits must refuse, and rotations beyond the history cap must be refused. |
| cost | One short committed trace and repeated bounded recovery/checkpoint attempts at the selected frontiers. |
| Design | [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0017

[Lines 221–222](../../../../../tests/unit/sql_aggregate_session_test.cpp#L221); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L221-L222:sha256:5aff6921a131d6ddc6615677f669d738f8bc62dafa5ed4da2d6d5aaaf5d260e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Detection of a changed actual selected root invalidates the old owner even if the failure occurs before any new root selection was attempted. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_session_test.cpp](../../../../../tests/unit/sql_aggregate_session_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 223–226](../../../../../tests/unit/sql_aggregate_session_test.cpp#L223); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void stale_root()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify that changing the selected root invalidates an existing Session owner before later operations can trust it. |
| inputs / outputs | Created Session and exact root bytes in; modified selected root, checkpoint refusal, reopen-required flag and rejected old-owner reads/writes out. |
| invariants | The check covers root staleness discovered before this owner attempts another root selection; it does not treat the prior in-memory selected DTO as authority after the actual root changes. |
| ownership | The fixture mutates only its disposable root file; the old Session retains its lock until scope exit but becomes unusable. |
| failure | Checkpoint, state and log calls must refuse after the root change; unexpected old-owner use fails an assertion. |
| cost | One small root read/check and three refused owner operations. |
| Design | [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0019

[Lines 227–228](../../../../../tests/unit/sql_aggregate_session_test.cpp#L227); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L227-L228:sha256:807d5e9a915e305f7078d8ecb077c3a248a59b85add87a4356544284aa5fee53
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Complete original filtered/unused rows survive an actual selected checkpoint; global-empty output is reconstructed independently of the surviving source bag. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_session_test.cpp](../../../../../tests/unit/sql_aggregate_session_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 229–243](../../../../../tests/unit/sql_aggregate_session_test.cpp#L229); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void complete_source()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify checkpoint/recovery preserves the complete original physical image even when rows are filtered from the aggregate and a table is unused, and reconstructs global-empty results. |
| inputs / outputs | Nullable filtered row and unused-table row with positive weights, followed by two no-table aggregate fixtures, in; actual checkpoint/reopen snapshots, source weights and W/I/C/D assertions out. |
| invariants | The filtered and unused source rows survive at their exact weights while the query result remains one global group with COUNT zero and SUM NULL. No-table COUNT and WHERE FALSE cases each commit an empty physical command, checkpoint, reopen and assert their distinct global counts. |
| ownership | Each case uses its genuine bound program, actual selected checkpoint and Session recovery; snapshot tuples remain account-owned by the receiving Session. |
| failure | Any lost source row, altered global-empty value, wrong frontier or failed checkpoint/recovery fails an assertion or propagates the native error. |
| cost | Three small fixtures: one filtered/unused two-table image and two no-table global aggregate cases, each with one command, one checkpoint and one cold recovery. |
| Design | [tests/support/sql_aggregate_session_fixture.hpp](../../../../../tests/support/sql_aggregate_session_fixture.hpp), [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md) |

## B0021

[Lines 244–245](../../../../../tests/unit/sql_aggregate_session_test.cpp#L244); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L244-L245:sha256:47b7fbdc941693137fcecca2176e4ba8667b44e3061375dd79627fd8f64e9b06
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: A fresh receiver owns all retained native/schema/output state. Exact observed factory peak succeeds; one byte less refuses before either torn suffix repair. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_session_test.cpp](../../../../../tests/unit/sql_aggregate_session_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 246–264](../../../../../tests/unit/sql_aggregate_session_test.cpp#L246); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void receiving_account()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify cold recovery builds all retained descriptor, native, group and pending-input state in the fresh receiving account, with exact observed-peak admission and no repair on one-byte-under failure. |
| inputs / outputs | Committed delivered fixture, optionally followed by a logged pending Input; measured successful recovery peak; then exact-peak and one-byte-under receiver accounts plus torn WAL/sink tails in; ownership, refusal, tail-preservation and final recovery assertions out. |
| invariants | Descriptor program and returned group key/value owners belong to the receiver. Exact observed peak succeeds; one byte under refuses and leaves both torn tails unchanged. At the exact limit recovery repairs admissible tails and restores either the committed state or the still-pending, unprepared final Input. |
| ownership | Every recovery uses a new MemoryAccount and the real Session::recover_into factory; account lifetime encloses its Session and only the account controller remains after owner destruction. |
| failure | Wrong allocation owner, leaked account allocations, incorrect pending state, early tail repair or failed exact/one-under behavior fails an assertion/refusal check. |
| cost | Two bounded histories (pending and no-pending), one generous measurement recovery and exact/one-under/final receivers per history; each recovery rebuilds/replays the genuine selected image. |
| Design | [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [include/crown/resource/memory.hpp](../../../../../include/crown/resource/memory.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md) |

## B0023

[Lines 265–266](../../../../../tests/unit/sql_aggregate_session_test.cpp#L265); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L265-L266:sha256:886ce37f274e129d195e22771d584ad9981dc4e96f3d608c756f1eba4d31565b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Initial candidates are never auto-cleaned or overwritten. A failed create can retain its own earlier unselected files but must select no new root. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_session_test.cpp](../../../../../tests/unit/sql_aggregate_session_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0024

[Lines 267–272](../../../../../tests/unit/sql_aggregate_session_test.cpp#L267); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void initial_collisions()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify initial Session creation preserves preexisting generation-one descriptor, checkpoint or WAL candidates and selects no root after collision. |
| inputs / outputs | One fixture for each .plan, .ckpt and .wal path prepopulated with sentinel bytes; attempted genuine create in; refusal, unchanged sentinel and absent root assertions out. |
| invariants | Initial creation does not overwrite or auto-delete an existing candidate. Its own earlier unselected candidates may remain after a later-stage collision; without a selected root they do not authorize a session. |
| ownership | Mutations are confined to each fresh temporary fixture directory; failed factory unwinds its Session/file resources. |
| failure | Create must refuse each collision while the original bytes remain exact and the selected root remains absent. |
| cost | Three small creation failures at successive candidate stages. |
| Design | [include/crown/recovery/sql_aggregate_session.hpp](../../../../../include/crown/recovery/sql_aggregate_session.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md) |

## B0025

[Lines 273–274](../../../../../tests/unit/sql_aggregate_session_test.cpp#L273); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L273-L274:sha256:19fb490f5372a269afa07885be59a62c2535964a437212cad332f1c91ad0b0bd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Host binder payloads are cold caller DTOs. Session must add no extra copies: create ignores them; recover has exactly direct rebind's transient delta. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/sql_aggregate_session_test.cpp](../../../../../tests/unit/sql_aggregate_session_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0026

[Lines 275–314](../../../../../tests/unit/sql_aggregate_session_test.cpp#L275); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void host_options() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Detect extra session host-DTO copies independently from legitimate transient descriptor-rebind work, and detect retained caller references. |
| inputs / outputs | Empty and long-name/TEXT host configurations, identical genuine program/descriptor and fresh receivers enter. Counted create/rebind/recover allocation pairs and real commands after caller mutation/destruction must succeed. |
| invariants | Warm both profiles and all factories before counting. Populated create must add zero covered-new attempts; populated-minus-empty recover must equal direct rebind delta, without hard-coding that delta. Paths/receivers/payloads are prepared outside counters and samples occur while results remain live. Caller mutation destroys binder payloads and sets live caps to zero before log/decide/deliver/checkpoint on both created and recovered owners. |
| ownership | Existing single-TU replacement-new Scope measures attempts only, separate from malloc/bytes/account charges. Actual Session owns its fixed copied caps/files/native state; caller DTOs and test paths stay outside the product owner. |
| failure | Old by-value/Data copies fail allocation-delta assertions; a retained reference fails actual commands after caller mutation/lifetime ends. Ordinary native/file/admission errors remain visible. |
| cost | One real create obtains the descriptor; six warm and six counted create/rebind/recover calls follow. Three further factory calls establish the two caller-lifetime scenarios. Fixture compiler/path/account setup occurs outside the counted scopes; these verification costs do not describe ordinary update cost. |
| Design | [tests/support/index_allocation.hpp](../../../../../tests/support/index_allocation.hpp), [src/recovery/sql_aggregate_descriptor.cpp](../../../../../src/recovery/sql_aggregate_descriptor.cpp), [src/recovery/sql_aggregate_session_detail.hpp](../../../../../src/recovery/sql_aggregate_session_detail.hpp), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |

## B0027

[Lines 315–315](../../../../../tests/unit/sql_aggregate_session_test.cpp#L315); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L315-L315:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in sql_aggregate_session_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/sql_aggregate_session_test.cpp](../../../../../tests/unit/sql_aggregate_session_test.cpp), [docs/aggregates.md](../../../../aggregates.md), [docs/code_review.md](../../../../code_review.md) |

## B0028

[Lines 316–320](../../../../../tests/unit/sql_aggregate_session_test.cpp#L316); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the real Session lifecycle/resource/semantic tests, including host-options copy and caller-lifetime regression. |
| inputs / outputs | No input; runs ordered/indexed lifecycle variants and each listed test group, then prints a completion line. host_options additionally compares create/rebind/recover allocation deltas and mutates/destroys caller configuration before real commands/checkpoint. |
| invariants | The completion line is reachable only if every assertion/operation returns; source review alone does not establish execution. |
| ownership | Each test group owns and releases its own Fixture/Session scope. |
| failure | Assertion, allocation, compiler/runtime or file failure prevents successful completion. |
| cost | Sum of the finite fixture scenarios and their genuine file reopens, full-source checkpoint/rebuild and account admission work; not a benchmark. |
| Design | [tests/unit/sql_aggregate_session_test.cpp](../../../../../tests/unit/sql_aggregate_session_test.cpp), [build/verification/w06-r2-protocol-review-v1/decisive-tests.md](../../../../../build/verification/w06-r2-protocol-review-v1/decisive-tests.md), [docs/sql_aggregate_session.md](../../../../sql_aggregate_session.md) |
