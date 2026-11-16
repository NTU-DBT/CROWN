# CROWN continuation handoff

The full Refactor.md goal remains active: **57 verified / 1 in progress (A02) /
20 not started**, 78 total. W06 stays verified within its bounded SQL/native/local-sink
profile. A02 still blocks C04/B01. R2 retirement, V04 and full release gates remain open.

Latest [V37 inspection](verification/human-inspection-v37-2026-11-13.md):
build/verification/human-inspection-v37-progress-v1.json, frozen source
build/verification/human-inspection-v37-source-v1, receiving packet
build/verification/inspection-continuation-tests-v37-v1.
Exact preceding handoff: [V36 history](handoff-history-v36-2026-11-13.md).

## Current usage and source boundary

The [source index](code_specs/README.md) contains 16,132 contracts
in 13,716 blocks across 751 files / 172,040 lines /
19,412 blocks. V37 fills 178 actual selected gaps in nine continuation,
delta and reference/lowering files, including all eight mains. The candidate-set
reference file has no main. All selected non-test regions have usage cards;
**477 selected test regions remain**. Unreviewed scaffolding retains structural
facts only. Mapping/card presence does not certify every comment or semantic claim.

All 1,196 native input paths, including 355 production paths, tests/fixtures,
CMake/install definitions and offline tools, equal V36 exactly. No runtime
handler, wrapper, allocation or checkpoint is added. No new native build, CTest,
SDK or timing execution occurs. Existing tool source remains
cc31de0ea2d2b3e667c07d834ac781e9925aac982f712b5fd11274b368d9254f.

Three bounded Luna Max author groups (55 planner, 52 delta, 71 reference/lowering)
and independent reviews are preserved. Root reads all 4,369 target lines and
callers before cards, checks actual missing-region sets and exact patch replay.
Root handles complex receiving review; no Astra is used. Frozen V36 inventory
and registry inputs are pinned separately and protected without duplicate copies.
See adoption-final-v1, coverage-final-v1, code-specs-final-v1,
review-seal-pins-final-v1, native-source-comparison-final-v1 and
receiving-acceptance-v1 in the receiving packet.

## Findings to preserve

Strict progress/scalar uppers, best-found validated handles, producer completion
and independently checked proof authority have different meanings. Only explicit
typed writers emit certificates; progress has a null certificate even when complete.
Resource stops remain unfinished. Cancellation preserves charged history and
published immutable uppers. Bad allocation is retryable at the noexcept boundary;
unexpected failure is terminal. Zero grants precede clock work. Dense numeric
scope names are a fixture precondition. The 70/150-scope fixtures and v1/v2
corruptions are finite checks, not arbitrary-input complexity proofs.

The blocking normal-form collector caps native/active variables at three for
resources, enumerates literal requested-height families and retains partial
non-exhausted results on resource stop. Its signatures are local equality after
P02, not production identity. Transition charges do not bound all bytes/CPU.
Candidate reports preserve original proof separately from trace-only residual
provenance. Local schema drivers are separate from native report generation.

Delta specification materializes full E/L joins and checks raw exact before/after
A04 differences, alias prefixes and projection collisions. Tiny-domain source
loops describe 2,504 transitions. The runtime scale comparison uses N=2/64,
N accepted replay versus 2N anchored candidates. Equal first/next/last producer
maxima do not include growing preparation/finalization or establish CPU delay.
apply() drains the producer before epoch.next() consumes its output spool.
SQL adapter staging copies physical/logical/support state. Static lowering
interpretation and a 128-native empty-storage depth test do not cover populated
incremental deep traversal. Preserve these costs in performance claims.

V36 findings remain in the exact history: canonical compiler source sharing
versus deep admission copy; selected account totals versus owner identity;
raw byte records versus semantic admission; snapshot capacity/shared buffers;
aggregate five-dimensional work grants; smaller-fanout indexed repair; private
barriers versus publication; and observed syscall cuts versus general crash claims.
Those source facts remain unchanged by V37.

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
none become V37 executions. Full current-suite/Clang/CPU/release gates remain open.

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
