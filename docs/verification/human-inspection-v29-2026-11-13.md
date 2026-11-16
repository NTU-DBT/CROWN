# Concrete R2 files and human inspection — V29

The new [R2 file API](../../include/crown/recovery/sql_aggregate_files.hpp) owns
actual locked WAL and group-sink files. Its [usage contract](../sql_aggregate_files.md)
specifies receiving-account schema ownership, confirmed prefixes, ordering,
uncertainty, duplicate delivery, costs and the caller's tail-repair obligation.
W06 remains in progress: these lower primitives do not supply the synchronous
session, selected-root/native replay or CLI integration.

## Implementation and inspection

The WAL stages one fixed cursor candidate with its spent grants, writes borrowed
prepaid frame bytes, and publishes only after fsync and final stat. The sink
prepays its bounded offset index and fingerprints; duplicates compare every
actual byte in chunks, including empty epochs. It privately mints receipts only
from a healthy untorn owner. Header-only nonzero baselines describe that file's
declared baseline and prove no earlier output epochs. Neither owner retains a
second pending-command copy or an output queue.

The [private dispatcher](../../src/recovery/sql_aggregate_file_detail.cpp) is
shared by the two concrete owners. Main publication paths have no catch layer;
create has its cleanup boundary. Failed I/O poisons authority getters, including
failure at the first stamp check or after a successful fsync. Pre-I/O validation
refusal can leave an owner usable. Charged work checkpoints, failed validation
costs, raw best-effort close and kernel latency are distinguished explicitly.

Review exposed a pre-existing quota escape: ordinary post-link temporary unlink
was exempt from the operation cap, allowing repeated EINTR to bypass that cap.
Only the fixed eight-attempt emergency cleanup now requests the exemption. The
same private correction applies to the existing journal, local sink and generation
owner. The [regression](../../tests/unit/file_cleanup_quota_test.cpp) checks the
32+8 bound, actual surviving linked bytes, locks, FDs and account release.
No ordinary update/runtime data member or reverse recovery dependency is added.

This pass adds **273 individual contracts**: 104 production-file cards, 37 new
test/support cards, 107 existing replay/sink/retirement-test cards and 25 build
cards. The master has **14,770 contracts** across **733 maintained files,
168,682 lines and 19,056 blocks**; 12,364 blocks contain scoped contracts.
All selected production/example/tool regions have cards. **1,559 selected existing
test regions remain**, so this is not a completed review of every block/comment.
The [map](../code_specs/README.md) distinguishes structural inventory from actual
per-region usage/invariant/ownership/failure/cost review.

Root implemented and verified. One normal-model lane reviewed production specs,
Luna Max handled bounded test specs, and one Astra Max agent reviewed the complex
file-authority boundary. Root retained sealed author packets, made two small
contract wording corrections in a fresh amendment, and rebased 117 source-line
references. Existing source-delta review refreshes 1,635 old cards: 14 semantic
updates and 1,621 hash-only updates. Initial failures and corrected postimages
remain available; completed packets were not rewritten.

Weighted aggregate context is P1 §7.3, equations (10)–(14), via the
[corrected paper/source map](../code_review.md). POSIX durability, wire formats,
budgets, ownership and repair are local engineering contracts, not paper delay
or minimum-height theorems.

## Executed receiving checks

| Check | Result |
| --- | --- |
| Broader affected Debug recovery/SQL cohort | 30/30, 800.95s |
| Final affected Debug cohort after the dispatcher preconditions | 11/11, 89.44s |
| Final ASan/UBSan with leaks/halt/stacktrace | 30/30, 710.61s, two independent tests at a time |
| Production `BUILD_TESTING=OFF` Release | Complete build passes; zero test registrations |
| Relocated SDK | 225 unchanged-on-move files; full public file suite compiles/runs in Release |
| New fault suite | 310 injected failures, 60 real process-exit cuts, quotas/EINTR/short I/O |
| Definitions | All 339 predecessors preserved; 342 registered in Debug/SAN |
| Source map | Checker passes 112,559 local links; final checker/audit receipts are retained |

The final dispatcher delta adds nine private libc pointer preconditions required
by optimized strict compilation; the API/test comment corrections preserve all
C++ tokens. Legacy source after the broader Debug run is unchanged. Its affected
R2 cohort was rerun; the final sanitizer run covers the full selected 30.

All previous properties and resolved commands match. The predecessor CTest JSON
omitted nine unbuilt executable commands per profile; their newly resolved commands
were checked against the exact unchanged parent CMake definitions. No JSON command
equality is claimed for those formerly absent fields.

There are 30 native recorder jobs, 26 successful. Four retained initial failures
cover test API/fixture mistakes and the optimized dispatcher preconditions; none
was bypassed by relaxed flags. Every job has zero in-command source drift. The
final 1,177 native inputs add ten files and change eight existing paths relative
to V28. Fourteen flag records retain C++23, strict warnings and test assertions;
the installed SDK contains production symbols and no testing archive/hook.

Nineteen existing archives are byte-identical to the prior SDK, including source,
aggregate runtime, native plan and storage libraries. The runtime/recovery archives,
CLI and three existing public headers change within the documented private quota
and upper-file scope; one public file header is added. There is no CPU timing,
current Clang, full 342-test, power-loss, complete W06 or release claim.

## Evidence and continuation

Root packet: `build/verification/w06-r2-file-owners-implementation-v1`.
Its `receiving-acceptance-v1.json`, `input-cohorts-v1.json`, exact source/card
proofs, archived terminal logs, SDK and `next-implementation.md` are the receiving
record. Sealed author packets and fresh root amendments remain separate.

The V29 source/evidence checkpoint is
`build/verification/human-inspection-v29-progress-v1.json`; its frozen source is
`build/verification/human-inspection-v29-source-v1`. The complete prior handoff is
preserved in [V28 history](../handoff-history-v28-2026-11-13.md).

Continue W06 with one actual synchronous R2 session: W/I/C/D authority, one logged
head, prepaid native/Commit publication, one output spool, genuine selected-root
replay and sink-floor validation before any repair, then JSONL/CLI and varying-int32
admission. Continue individual existing-test inspection. The full ledger remains
**56 verified / 2 in progress / 20 not started**, 78 total; A02 still blocks C04/B01.
