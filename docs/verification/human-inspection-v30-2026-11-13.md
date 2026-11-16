# R2 Session and human inspection — V30

The [Session API](../../include/crown/recovery/sql_aggregate_session.hpp) now owns
the synchronous genuine SQL/native/root/WAL/sink lifecycle. The
[usage guide](../sql_aggregate_session.md) specifies W/I/C/D, borrowing, semantic
Reject, pending retry, canonical output, recovery barriers, checkpoint selection
and separate work/memory costs. W06 remains in progress for operational source/CLI
integration and varying-int32 admission; this is not a full release gate.

## Implementation and review

One logged decoded Input owns rows/TEXT and one prepaid source-position update.
One real native batch token supplies rollback. Commit output/hash/decision are
funded before decision sync; the same token and prepaid progress publish
afterward without new allocation. Reject advances I/progress while C/D stay;
resource failure retains the same head. Successful empty epochs still advance C
and require actual sink closure. No later command bypasses pending output.

Cold recovery rebinds the genuine saved descriptor, releases its temporary C0
runtime, and restores the complete physical checkpoint. It opens the actual sink
before WAL replay, reproduces each decision/reason and canonical whole output,
checks delivered full bytes and sink floor, and retains at most one missing final
epoch. Full opening scans/replay precede stamp/EOF/root continuity checks and
either repair; these final barriers do not rescan histories. Complete corruption
or semantic disagreement aborts before either truncate.

The reachable stale-root bug found in review now poisons the old owner before
another command can proceed. A confirmed-delivery postcondition also reuses the
existing fail-stop latch. Three narrow catches serve semantic translation,
selected-root validation and uncertain root selection. The
[disposition guide](../code_specs/error_handling.md) distinguishes them from
unnecessary wrappers. Native cleanup and ordered-map comparisons still cost
work: nonallocating publication is not constant-time publication.

Root's final cost review found that SessionLimits contains owning binder vectors,
despite an early draft calling it fixed-size. Factories now borrow const limits;
Data projects only seven fixed operation/replay groups. The old regression
observed create 2912/2924, direct rebind 5915/5919 and recover 8339/8355 covered C++ new
attempts for empty/populated host data. Final Debug/SAN/SDK observe
2912/2912, 5915/5919, 8339/8343. It removes 12 session-added allocations in both
tested factories without changing legitimate transient compiler work. Caller
mutation/destruction and compile-time const-reference/trivial-projection guards
also verify the ownership boundary. No new allocation-tracking framework was
introduced.

## Executed checks and exact scope

| Check | Receiving result |
| --- | --- |
| Broader affected Debug | 31/31, 1267.42s |
| Full selected ASan/UBSan/leaks | 34/34, 2527.69s, two independent tests at a time |
| Independent SQL per profile | 99 cases / 198 backend cases, 3,634 snapshots, 3,436 atomic epochs |
| Actual durable replay per SQL profile | 13,744 reopens, 3,634 selected checkpoints |
| Final options-corrected Debug | unit 4.24s, fault 103.67s |
| Final options-corrected sanitizer | unit 6.91s, fault 350.19s |
| New fault matrix per profile | 504 injected EIO, 118 real process cuts, 8,502 covered C++ new cuts |
| Complete production OFF Release | passes; zero test registrations |
| Fresh relocated SDK | 226 unchanged-on-move files; public full session and standalone header 2/2, 2.33s |
| Existing registration preservation | 342 definitions/properties preserved; 345 total |
| Actual flags/symbols | 18 strict records; no production file/generation hooks |

The full corpus executions precede the final copy-only options projection.
Exact source/callee review and 34 byte-identical method bodies support reuse for
unchanged encoding, replay, I/O and native semantics. Current resource/lifetime,
fault, production and SDK gates were rerun after that correction. The full prior
oracle is not reported as a current-source execution. DuckDB 1.5.4 supplies this
turn's independent SQL checks; varying-int32 columns remain excluded.

Four retained failures are the unsupported preset name, a make-target discovery
attempt during regeneration, the initial 900-second fault timeout and the old
host-copy regression. The fault harness retains all cut points but now restores
genuine captured fixture bytes through real recovery and avoids redundant
baseline publications/reopens. Its revised sweep verifies live same-owner
rollback/retry and cold-file/account preservation. Real process exits are not
power-loss experiments.

All 20 non-recovery archives and the CLI exactly match the prior SDK. Only the
recovery archive and existing file header change, and one session header is added.
Ordinary source/native/group code gets no new field, branch or handler. No CPU
benchmark, current Clang, full 345-test, full W06 or release claim is made.

## Human-readable specifications

The [source map](../code_specs/README.md) has 15,054 contracts across 742 maintained
files, 170,216 lines and 19,239 blocks; 12,643 blocks carry scoped usage contracts.
This pass adds 284 cards, including 140 old checkpoint/input/window-test regions,
new session/source/test primitives and build commands. All selected non-test
regions have cards; 1,419 selected existing-test regions remain. Every maintained
line is structurally mapped, which is distinct from a complete semantic proof.

Root implements and verifies; a normal-model lane reviews authority/options;
Luna Max supplies bounded source/test cards. No Astra call was needed here.
Completed author packets remain immutable. Fresh root amendments correct
publication/barrier costs, owned versus borrowed position nodes, caller DTO
ownership and specific fixture counts. Weighted context comes through the
[corrected paper/source map](../code_review.md); durability, configuration,
allocation and test protocols are local engineering, not paper delay theorems.

## Concurrent additions and provenance

Two untracked benchmark draft tools appeared while the earlier SAN run was in
progress. Root preserved their exact bytes, reviewed 14 usage/setup cards and
recorded their limitations in
`build/verification/concurrent-benchmark-tools-review-v1`. They were not executed
or imported by this selected native cohort and do not establish B01/B05 acceptance.
The B05 draft recursively replaces output directories and emits fixed performance
conclusions; these are not measured findings. Fix those limitations before use.

The final inventory also found a [concurrent report](b01-b05-readiness-and-baseline-inspection-2026-11-13.md)
and existing legacy/adversarial JSON outputs. These are preserved as concurrent
observations in `build/verification/concurrent-benchmark-provenance-amendment1`.
The JSON records a failed legacy build and six wrapper successes; this Session
cohort does not establish their execution provenance or accept their measurement
claims. Mixed java/javac observations do not establish the report's Java 8-only
conclusion. The source inspection of the two tools remains valid; earlier packet
wording about non-execution refers to this cohort, not all concurrent activity.

The recorder checks mutation of keys present at command start; it does not
detect later additions. Accordingly the receiving audit makes no global
no-additions claim. All original recorded keys remain unchanged in-command;
the final 1,186-input map adds nine paths and changes ten versus V29. Seven added
paths are Session code/tests and two are the concurrent tools. There are 45 native
jobs, 41 successful, with all failure evidence retained.

## Evidence and continuation

Root: `build/verification/w06-r2-session-implementation-v1`, including final
receiving/input cohorts, actual flags/SDK comparisons, preserved terminal logs,
contract adoption proofs and fresh options-amendment1 SDK/build. Ten review seals
are pinned separately. The V30 seal is
`build/verification/human-inspection-v30-progress-v1.json`; frozen source is
`build/verification/human-inspection-v30-source-v1`. See the
[handoff](../handoff.md) and exact [V29 history](../handoff-history-v29-2026-11-13.md).

The full 78-card ledger remains 56 verified / 2 in progress / 20 not started. A02
still blocks C04/B01. Continue W06 source/CLI and varying-int32 work, existing-test
inspection, and draft-tool disposition. Completed evidence/private builds remain
immutable; corrections require fresh amendments. Goal remains active.
