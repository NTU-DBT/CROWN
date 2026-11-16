# CROWN continuation handoff

The full Refactor.md goal remains active: **57 verified /1 in progress A02 /
20 not started**, 78 total. W06 retains its bounded SQL/native/local-sink profile.
A02 still blocks C04/B01. R2 retirement, V04 and release gates remain open.

Latest [V39 acceptance](verification/human-inspection-v39-2026-11-13.md):
build/verification/human-inspection-v39-progress-v1.json, frozen source
build/verification/human-inspection-v39-source-v1, receiving packet
build/verification/inspection-descriptor-diagnostic-v39-v1.
Exact previous handoff: [V38 history](handoff-history-v38-2026-11-13.md).

## Current usage and source boundary

The [source index](code_specs/README.md) retains 16,352 scoped contracts in
13,936 blocks across 751 files /172,040 lines /19,412 blocks. V38 added 220 cards
in 20 memory, storage/cost and reoptimization files. V39 re-reviews eight descriptor
cards and updates two stale-message descriptions, without adding cards. All selected
non-test regions have cards; **257 selected test regions in 49 files remain**.
Other scaffolding keeps structural facts; map/card presence is not universal
semantic certification.

Exactly one of 1,196 native inputs changes from V38: the descriptor-test success
literal says twelve instead of six. All other 1,195 inputs, including 355 production
paths, are unchanged. Root re-read all 92 source lines and eight seven-field cards,
then refreshed the whole-file review hashes. No production work, handler, wrapper,
checkpoint or runtime counter is introduced. The existing offline tool source is
cc31de0ea2d2b3e667c07d834ac781e9925aac982f712b5fd11274b368d9254f.

## Completed diagnostic follow-up

The V38-required correction is complete: the existing variant loop is four no-sink
plus eight sink cases, including last_switch_epoch. Strict Debug and ASan/UBSan
affected builds pass; reoptimization_descriptor passes 1/1 in each profile and
prints twelve. SAN has leak detection, halt and stacktrace enabled. Each of four
recorder commands pins the same 1,196-input cohort with no edits during execution.
Pre/post LastTest logs and flags are archived. No new full 348-test, Clang, SDK,
benchmark or release execution follows from this narrow check.

V38's six author/reviewer packets, 584 peer amendments and five root amendments
remain immutable. Root handles this one-literal native follow-up; no new agent
is needed. Completed maps and current-guide links pass before the V39 seal.

## First continuation

Continue the exact 257 remaining selected test regions across 49 files. The
coverage-final-v1.json in this packet retains their actual path/block set; the
V38 remaining-gaps-projection-v1.json also lists per-file counts. Derive fresh
sets and source pins before assigning bounded reviews. Keep block-local usage,
ownership, failure and cost specs with concrete design/source references, and
avoid copying broad module claims onto scalar helpers or mains. Preserve necessary
transaction/ownership boundaries while simplifying code; do not add runtime
inspection mechanisms. Keep A02/C04/B01, R2/V04 and release scopes explicit.

## Findings to preserve

MemoryAccount owns its controller; payload owners retain native buffers/tuples.
OwnerAllocator moves/swaps transfer exact ownership; copies can allocate.
SupportEpoch transition copies share a journal, while invariant/workload report
arrays have their own copy rules. Capacity and selected attribution totals differ
from row count/whole heap; statistics_for scans the allocation list. Denial guards
without counter assertions do not prove zero attempts. Canonical comparisons,
selected fields, purpose buckets and owner IDs have separate evidence scopes.

Fresh indexed work consumes one structural startup unit. Nested/resumed scopes
retain the same five-domain balance without refill. Calibration fit observations
are synthetic assumptions; its N-cut campaign retries once after the whole sweep.
The eager E-factor baseline intentionally scans growing dead factors, unlike
selective before-side index lookup. Neither selected counters nor finite fixture
equalities prove CPU/delay bounds.

Preparation, original durable Input/decision, journal promotion and selected-plan
publication are different boundaries. Promotion sync precedes root link; syscall
cuts/forked exits do not establish every-instruction or host-power-loss recovery.
Compiler/sink/retirement preflight occurs before WAL/sink tail repair. Cached
reader recovery drains admitted prefix before unread continuation. C05 explicitly
timed selection/freshness enters payback. Churn subtracts sink bytes only, keeps
whole-account allocation count, and checks 64 finite switches/128 inputs.
Descriptor opaque compiler text is framing-only. Session-image source has two
registered native executables; no execution is inferred from registration.

V37/V36 findings remain in exact histories, including progress versus proof,
canonical-source sharing versus deep admission copy, producer versus spool work,
snapshot/account ownership and exact raw byte/semantic admission scope.

## Preserved native acceptance

V33 Debug and ASan/UBSan/leaks each passed the preserved Session fault test and
new interrupted mixed nullable self-join matrix. Per profile the new matrix has
14 backend/action cases, 784 EIO cuts, 156 process exits and 28 independently
decoded healthy/probe tapes; old matrix separately has 504 EIO cuts, 118 exits
and 8,502 covered new cuts. Survivors check source weights, typed output, W/I/C/D,
progress, sink bytes, valid next update and another reopen. Process cuts surround
persistence syscalls; RAM-stage equivalence is source-derived.

V33 OFF Release configure/build/install passed. Debug/SAN registered 348 tests,
OFF zero; prior 347 definitions were preserved. The moved SDK's 229 files equal
the actually tested V32 SDK; V33 did not rerun SDK tests. V32 retains 21 affected
names and four 123-case SQL modes, with 3,952 snapshots/3,706 epochs per mode and
14,824 actual Session reopens/3,952 checkpoints per profile. Keep dated receipts;
none become V39 executions. Full current-suite/Clang/CPU/release gates remain open.

Preserve V32 sorted original-column int32 guards and unchanged physical bigint
schema. Final expression type decides SUM policy; COUNT and narrow-then-widen
keep guards, NULL passes, and filtered/unmatched/net-zero facts may not project.
Prior installed evidence accounts fixed Data+56 bytes and U selected guard
checkpoints per projected row/fact. Conditional/FILTER needs fresh scope review.

## Continuation rules

The [R2 input guide](sql_aggregate_input.md) is operational authority: drain spool,
resolve pending WAL Input before reading more, resume logged W/reader position.
Reject advances I/source/reader without C/D; report failure never permits relogging.
Consumed unterminated records remain terminal if LF is appended later. Retained
R2 history starts at generation one under its durable finite cap; reopen cannot
refill it. Separate low-level generation retirement tests do not close R2/V04.

Revalidate the latest sealed boundary before work. Completed packets, private
builds/SDKs and snapshots are immutable; amendments need fresh paths. V34's exact
restored 373454d9 peer and changed 20e8/cabd2243 amendment stay protected. Do not
rerun old live-registry validators after authorized edits and rewrite them to pass.
No native edits during recorder jobs; no overlapping build/CTest/enumeration in
one build directory. Archive terminal LastTest before another native action.
Main Debug/SAN/OFF builds are reusable. Finish generation before checking; read
unused_manual_overrides directly. Never stage/reset/commit. exec_command requires
sandbox escalation here. B01/B05 drafts remain unaccepted. Continue the remaining
individual usage review and original implementation/release tasks.
