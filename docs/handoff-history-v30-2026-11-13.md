# CROWN continuation handoff

The full Refactor.md goal remains active. The [ledger](task_ledger.md) remains
**56 verified / 2 in progress (A02/W06) / 20 not started**, 78 total. A02 blocks
C04/B01. No full W06 or release acceptance is claimed.

Latest [V30 inspection](verification/human-inspection-v30-2026-11-13.md):
`build/verification/human-inspection-v30-progress-v1.json`, frozen source
`build/verification/human-inspection-v30-source-v1`, implementation packet
`build/verification/w06-r2-session-implementation-v1`.
The exact previous handoff is [V29 history](handoff-history-v29-2026-11-13.md).

## Actual implementation

The new [R2 Session](sql_aggregate_session.md) connects the genuine original-SQL
runtime to actual root/WAL/sink locks. It owns one logged Input and one canonical
committed output frame. W is logged command sequence, I is disposition, C is
native commit, D is actual sink delivery; WAL frame ordinal is separate.
Log owns/funds Input and progress before I/O. Decide prepares the genuine token
and canonical output/decision before sync, then publishes that same token and
prepaid positions. Only six explicit semantic errors become Reject; resource
failure retains the same pending head. A later Input requires W=I,D=C.

Recovery restores the actual selected v3 descriptor/checkpoint, opens the sink,
replays genuine native decisions, verifies complete canonical output and actual
sink bytes/coverage, then checks root/stamps/EOF before either admissible tail
repair. Only one final missing epoch can remain a spool. Checkpoint syncs the
next descriptor/image/matching WAL before root selection. History is bounded
from generation one; R2 retirement is not implemented.

Review fixed a reachable stale-root path that left the old owner usable, and
added a fail-stop latch after confirmed delivery for unexpected private
postcondition failure. The main code has three narrow exception boundaries and
uses the existing token for rollback. Publication allocates nothing new but can
traverse prepared cleanup and ordered-map comparisons; continuity barriers use
stat/EOF/stat and a bounded root reread, not full history rescans.

Root also removed whole owning SessionLimits copies. Factories now borrow
const configuration; Data retains only seven fixed live groups/scalars. The
fixture removes 12 extra session allocations from both create/recover; the four
transient descriptor-rebind allocations remain. Caller mutation/destruction and
exact/one-under receiving-account tests pass. No ordinary update field or second
database/output queue is introduced.

## Receiving evidence

Broader Debug 31/31 passes (1267.42s); full selected ASan/UBSan/leaks 34/34 passes
(2527.69s). Each SQL profile compares 99 cases / 198 backend cases / 3,634 snapshots,
3,436 atomic epochs, 13,744 actual reopens and 3,634 selected checkpoints. After the
copy-only options correction, final Debug unit/fault gates pass 4.24s/103.67s and
SAN 6.91s/350.19s. Each fault profile covers 504 EIO reports, 118 real process cuts
and 8,502 covered C++ new cuts. These are process cuts, not power-loss evidence.

The full prior SQL execution is reused only for unchanged semantics through exact
source/callee review and 34 byte-identical method bodies; it is not relabeled as
a post-correction run. Current resource/lifetime/fault checks and a fresh complete
production OFF Release plus relocated 226-file SDK 2/2 pass after the correction.
Twenty non-recovery archives and the CLI are byte-identical to V29; only the
recovery archive and file header change, with the new session header added.
All 342 prior registrations/properties are preserved, 345 registered; OFF has zero.
No full 345, current Clang, CPU timing, full W06 or release claim.

## Human inspection and concurrent drafts

The [map](code_specs/README.md) has 15,054 contracts across 742 files, 170,216 lines
and 19,239 blocks, 12,643 blocks with scoped contracts. This pass adds 284 cards,
including 140 existing checkpoint/input/window-test cards. All selected non-test
regions have usage cards; 1,419 selected existing-test regions remain. Structural
maps/card presence are not proof of complete semantic correctness.

Root implemented/verified and reviewed actual costs. A normal-model lane reviewed
authority/options deltas; Luna Max handled bounded source/test cards. No Astra
invocation was needed this continuation. Completed author packets are preserved;
fresh root amendments correct specific costs/ownership/count wording.

Concurrent tools/run_legacy_baseline.py and tools/run_adversarial_scalability.py
were preserved unchanged and source-reviewed separately. Their cards record known
limits: destructive output replacement, missing-artifact success, heuristic
environment observations and hard-coded benchmark conclusions. This Session
verification did not execute either script or adopt B01/B05 acceptance.
A [concurrent report](verification/b01-b05-readiness-and-baseline-inspection-2026-11-13.md)
and existing JSON outputs were also found. They record a failed legacy build and
six wrapper successes; this cohort does not establish their execution provenance,
full scale/memory acceptance, or the report's claim that Java 8 is strictly
required. The legacy report contains mixed java/javac version observations.
Do not run the B05 wrapper on sealed evidence. A02/B01 and B05 remain open.

There are 45 native recorder jobs, 41 successful; all four initial failures are
retained, including the reproducing host-copy regression. Original tracked input
keys have zero in-command mutation. The two concurrent tools appeared during the
earlier SAN interval, which the recorder's old-key check does not detect. Final
inputs 1,186 = nine additions / ten changes versus V29. The audit records these
additions explicitly; it makes no global no-additions claim.

## Next work and working rules

Continue W06 source/JSONL/CLI integration and exact varying-int32 admission.
Resume from logged W, including a pending Input's reader continuation; do not log
a second copy. Dispose that head, deliver before reading the next command, and
keep semantic Reject separate from resource failure. Recheck the original W06
acceptance scope. R2 retirement and full release work remain separate.
Continue existing-test inspection and resolve the concurrent draft limitations
before operational adoption. Details are in the root packet's next-implementation.md.

No maintained native edits during recorder jobs. No overlapping build/CTest/
enumeration in one directory. Archive LastTest before the next native action.
Main Debug/SAN/OFF builds are reusable. Completed packets, SDKs/private builds
and snapshots are immutable; corrections use fresh amendment paths. Do not rerun
old live-source postchecks after authorized edits. Generate maps before checking.
Never stage/reset/commit Git. Exec commands require sandbox escalation here.
Revalidate the saved source/evidence at the next entry. Goal remains active.
