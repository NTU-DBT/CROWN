# CROWN continuation handoff

The full Refactor.md goal remains active: **57 verified / 1 in progress (A02) /
20 not started**, 78 total. W06 stays verified within its bounded SQL/native/local-sink
profile. A02 still blocks C04/B01. R2 retirement, V04 and full release gates remain open.

Latest [V36 inspection](verification/human-inspection-v36-2026-11-13.md):
`build/verification/human-inspection-v36-progress-v1.json`, frozen source
`build/verification/human-inspection-v36-source-v1`, receiving packet
`build/verification/inspection-replanning-tests-v36-v1`.
Exact preceding handoff: [V35 history](handoff-history-v35-2026-11-13.md).

## Current usage and source boundary

The [source index](code_specs/README.md) contains 15,954 contracts
in 13,538 blocks across 751 files / 172,040 lines /
19,412 blocks. V36 fills 176 actual selected gaps in ten replanning,
installation and memory/budget test files, including all ten mains. All selected
non-test regions have usage cards; **655 selected test regions remain**.
Unreviewed scaffolding keeps structural facts only. Mapping/card presence does
not certify every semantic claim or every comment.

All 1,196 native input paths, including all 355 production paths, tests/fixtures,
CMake/install definitions and offline tools, equal V35 exactly. No runtime
handler, wrapper, allocation or checkpoint is added. There is no new native
build/CTest/SDK/timing execution. Existing tool source remains
`cc31de0ea2d2b3e667c07d834ac781e9925aac982f712b5fd11274b368d9254f`.

Three author packets (57 native replanning, 67 reoptimization, 52 runtime grants)
and their independent reviews are preserved with exact recursive hashes. Root
reads all 2,225 target lines plus callers and validates full actual gap sets,
unique anchors and exact patch replay. Large V35 inventory/registry files are
pinned rather than duplicated. Canonical payload hash differs from seal hash.
See adoption-final-v1, coverage-final-v1, code-specs-final-v1,
review-seal-pins-final-v1, native-source-comparison-final-v1 and
receiving-acceptance-v1 in the receiving packet. Root handles complex review;
Luna Max agents handle bounded authorship/review. No Astra is used.

## Findings to preserve

Native replan_into funds new graph data in the receiving account while retaining
the canonical compiler basis, possibly in another account. Later replans flatten
to that same source rather than retaining prior graphs. Deep freeze admission
is a separate copy path whose source account can close while the copy is held.
Account-current equality is not owner-ID equality. Projection inventories borrow
plan addresses; their indexes()[0] type expression is unevaluated.

Raw byte-record fixtures are not admitted SQL/trees. Independent literal framing
covers scalar/tree/core records; changed-record comparisons cover 17 tree,
38 core and 79 normalized mutations. The normalized baseline is production output,
not an independent full expected record. Native persistent
calls 2N+3, native copy fault staging 2N+2; discovery caps use at most 1,024 calls.
Fault/cap helpers mainly use candidate zero; equivalence/churn cover families.
Ranking faults cover unaligned new and retry after the whole sweep; image fields
and old-result usage have distinct scopes.

Three Delta attribution queries are three live-block scans and cover selected
IDs, not all accounts/nodes. MemoryAccount retains the controller, not every
payload. Snapshot capacity reproduces growth and immutable collection copies
share buffers/accounts. Three typed/five window control allocations are local
fixtures. Denial guards without counter assertions do not prove zero attempts.
One aggregate IndexWork allowance has five dimensions; compiler metadata is a
separate allowance. Indexed repair lowers fanout 48 to 47. The above-2^53 case
seeds/restores private metadata rather than materializing that many rows.

Preparation verifies/cancels without publication. Main ordinary counts are 16
preparation and 24 installation profiles; installation adds 12 helper calls.
Generation descriptor tests use opaque strings, while install-fault tests replay
real compiler artifacts. Syscall cuts/_exit cover observed boundaries, not all
instructions or host power loss. Preserve synchronization order, uncertain
selection latch, benign ENOENT and the next valid input. Indexed-budget main has
no outer catch; unknown mode strings follow their actual fallback branches.

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
none become V36 executions. Full current-suite/Clang/CPU/release gates remain open.

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
