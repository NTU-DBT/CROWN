# CROWN continuation handoff

The full Refactor.md goal remains active. The [ledger](task_ledger.md) remains
**56 verified / 2 in progress (A02/W06) / 20 not started**, 78 total. A02 blocks
C04/B01; W06 can continue. No full release is claimed.

Latest [V29 checkpoint](verification/human-inspection-v29-2026-11-13.md):
`build/verification/human-inspection-v29-progress-v1.json`, frozen source
`build/verification/human-inspection-v29-source-v1`, root packet
`build/verification/w06-r2-file-owners-implementation-v1`.
The exact prior handoff is [V28 history](handoff-history-v28-2026-11-13.md).

## Actual implementation

The composed original-SQL runtime, complete physical source capture, genuine
cold reconstruction, typed R2 records, genuine descriptor and physical checkpoint
remain implemented. They preserve full original nullable bags, original operational
policies and separate physical C / disposed I / source / reader progress.

The new [actual R2 files](sql_aggregate_files.md) freeze genuine descriptor schema
into one receiving account and own regular-file FDs/flocks. WAL append borrows the
already owned Frame, stages fixed spent cursor state and publishes only after
fsync/final stat. Sink append prepays its offset index/hash; duplicate verification
compares whole actual bytes in chunks, including empty epochs. Sink ordinal is
absolute C, including nonzero bases; I strictly increases, generation never falls.
Only a healthy untorn actual SinkFile mints its fixed receipt observation; header-
only baselines prove no earlier epochs. Metadata DTOs remain data.

Public repair_tail is intentionally a lower caller obligation: the future
receiving session must finish selected-root/native replay/output/sink-coverage and
EOF/stamp validation first. Open never repairs. Complete corruption and complete
pending Inputs are never discarded as tails. Failed admitted I/O poisons getters;
pre-I/O validation/resource refusal may leave a reusable owner.

The review also found/fixed the legacy journal/sink/generation ordinary-unlink
EINTR quota escape. Only the fixed eight-attempt failure cleanup passes the private
emergency flag; normal post-link unlink spends its ordinary cap. There is no new
ordinary update field, second undo layer, command copy or output queue.

## Receiving evidence

Affected Debug 30/30 passes (800.95s), with final affected 11/11 (89.44s) after nine
private libc pointer preconditions and comment-only corrections. Final full
ASan/UBSan/leak selected 30/30 passes (710.61s, j=2). Production OFF Release builds
completely; relocated 225-file SDK compiles/runs the complete public file-owner suite.
The new fault matrix includes 310 injected errors and 60 real process-exit cuts.
The inherited-owner regression checks 32+8, actual linked bytes, FDs and accounts.

All 339 prior definitions/properties are preserved, 342 registered. Nine commands
omitted from predecessor JSON because executables were unbuilt are now resolved
and checked against exact unchanged parent CMake source. Thirty native jobs are
retained, 26 successful and four initial failures/fixes preserved; all have zero
in-command source drift. Final native input map has 1,177 paths, ten additions and
eight changed existing inputs versus V28. Nineteen existing installed archives are
byte-identical; runtime/recovery archives, CLI and three existing headers change
within the documented quota/upper-file scope. No current Clang, full 342-test suite,
CPU timing, power-loss or complete R2-session acceptance is claimed.

Completed packets, SDKs and private builds are immutable. Astra's static packet
and a fresh exact root delta amendment are separate; final source-aware production
contracts cover the pointer guards and precise work/failure wording.

## Human inspection

The [map](code_specs/README.md) now has **14,770 contracts**, **733 files**,
**168,682 lines**, **19,056 blocks**, with 12,364 blocks carrying scoped contracts.
All selected non-test regions have cards; **1,559 selected existing-test regions
remain**. Structural partitioning/card presence is not complete semantic proof.
This pass adds 273 cards: 104 production, 37 new tests/support, 107 existing tests and
25 build commands. Root rechecked exact source deltas and corrected two wording
fields in a fresh amendment; 117 R1 source-line references were rebased.

Root implements/verifies; Luna Max handles bounded test review, a normal-model
lane supplies source specs and one Astra Max agent reviews the complex authority
boundary. Use own model substantially and keep Astra Max use sparse. No agent
edits source during root native jobs. The final source/card/link audits and all
parent frozen/protected hashes must be revalidated at the next entry.

## Next work

Read this root packet's `next-implementation.md` and immutable
`w06-r2-protocol-review-v1/{protocol,actual-apis,decisive-tests}.md`.

Implement a separate upper R2 Session, not R1 QuerySession alternatives or a
new generic recovery engine. WalFile::open_replay is private friend access for
crown::recovery::sql_aggregate::Session; visitor effects stay private through the
whole open. Continue with actual W logged / I disposition / C native / D sink:
log only W=I,D=C, one owned logged head and at most one committed canonical spool.
Fund Input/progress before Input fsync; prepare the real token/output/Commit before
Commit fsync, then publish the same funded token/frontiers without allocation.
Stable semantic Reject advances I only; resource denial retains the identical head.

Open actual sink before genuine WAL replay. Require selected v3 descriptor hash,
C<=I, actual checkpoint D=C anchor and no R1 retirement intent. Each Input proves
prior sink_floor=C. Validate all complete frames and native decisions/output,
EOF/stamps/root and actual sink coverage before either lower repair. Only one
missing final Commit output may remain a spool. Sync descriptor/checkpoint/new
WAL before root selection and keep finite history until actual R2 retirement.
Then add nullable JSONL/CLI resumption from logged W (including pending reader
position), exact varying-int32 admission, and remaining release work. Continue
individual existing-test specs alongside implementation.

## Working rules

No maintained native edits during recorder jobs. No overlapping build/CTest/
enumeration in one build directory. Archive terminal LastTest before the next
native action. Main Debug/SAN/OFF builds are reusable; sealed evidence, snapshots,
private builds and SDKs are immutable. Corrections use fresh amendment paths.
Never rerun old live-source postchecks after authorized edits. Adopt fresh writes;
do not stage/reset/commit Git. Exec commands need sandbox escalation in this
environment. Generate maps before checking and retain original failed receipts.
Goal remains active.
