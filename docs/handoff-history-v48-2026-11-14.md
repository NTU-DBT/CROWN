# CROWN continuation handoff

The full Refactor goal remains active: **60 verified / 1 in progress (A02) /
17 not started**, 78 total. B05 is now verified for its finite native stress
matrix. V01, conditional V02 and bounded V33 W06 remain verified. The previous
handoff is preserved exactly in [V47 history](handoff-history-v47-2026-11-14.md).

## Current result

Read the [B05 receiving report](verification/b05-adversarial-scalability-2026-11-14.md),
[methodology](adversarial_scalability.md) and [measurement contract](measurement.md).
The complete run covers 19 families × four scales × two backends × three modes:
76 points, 456 configurations, 456 correctness preflights, 1,368 measured reports
and 456 retained warmups. Independent relational/SQLite per-epoch expectations
and measured JSONL sinks agree. Scale, fan-out, checked height, arity, skew,
empty/small/large outputs and six fixed-live churn shapes remain distinct.

All 108 largest-scale churn sentinel series have stable query-current bytes,
source/support slots and cursor work from cycle 4 through 1,024. Star source
capacity first reaches 12 slots across three tables; simultaneous live population
peaks at 10. The 432 final empty probes have zero live source rows. Slot counts
are populations, not a direct tombstone-visit counter or an unbounded proof.

The report explains output-sensitive delta preparation and full-snapshot cost.
Target RSS grows with trace length while native query state plateaus; the
collector retains event records and later frame/encoded-report buffers outside
the query grant. No whole-process constant-memory claim is made.

A genuine RSS runner defect was fixed before the full matrix. GNU time now
records hashed target-resource sidecars; outer wait4 RSS is launcher scope.
A 96 MiB parent buffer changes target RSS only 8,708→8,740 KiB while launcher
RSS grows 25,732→124,036 KiB. Old wait4-only RSS is not clean target-memory
curve evidence. The runner retains report paths and loads one repetition group
for summaries, rather than retaining all raw report DOMs.

## Human inspection and performance boundaries

The [source index](code_specs/README.md) maps 755 files /172,803 lines /
19,462 blocks. There are 16,844 contracts in 14,413 blocks; selected callable,
type and inline-cluster gaps are zero. This turn adds 51 contracts, amends 23,
removes three obsolete cards and drops eight overlapping draft proposals.
The 1,530 source-hash-only rebindings preserve their original authors. Four
[schema contracts](code_specs/schema_contracts.md) use checked JSON pointers.
Five independent wording findings and one request-hash precision note are received.
The 5,049 remaining structural blocks include 2,901 blanks; all 2,148 remaining
nonblank block bodies match V47. Mapping does not certify every semantic claim.

All 355 apps/include/src files remain byte-identical to V47. There is no new
engine field, catch, update hook or instrumentation. The example collector adds
an ordinary arena snapshot in diagnostics after ack/active timing. Both verify
and measure retain these diagnostics; only measure serializes event frames.
Raw report v2 and request v1 have separate contracts; raw report v1 stays intact.
Keep primitives direct, forward existing ownership/account/operation grants,
and state real cost boundaries instead of adding recovery frameworks.

## Evidence and exact cohorts

Root packet: `build/verification/b05-adversarial-acceptance-v1`.
Raw matrix: `build/verification/b05-adversarial-native-v1`.
Independent [raw receiving](../build/verification/b05-raw-receiving-review-v1/report.md)
hashes all 1,824 reports (7,016,550,036 bytes), checks every terminal C01 object,
and compares 11 complete raw JSON samples /90 probe rows for O07. Full aggregate
availability is checked separately. Independent [contract receiving](../build/verification/b05-contract-receiving-review-v1/review.md)
and [correction replay](../build/verification/b05-contract-corrections-review-v2/review.md)
remain immutable. Root receives the final normalized-request cost clarification.

Focused B05 controls pass 72 configurations in Release and 72 under ASan/UBSan;
each has 72 preflight plus 72 measured collector runs, zero warmups. Corrected
B03 controls, C07 ranking and moved public-only installed consumers pass.
The installed collector covers 12 cases/33 commands and ranking covers
48 candidate/mode checks/62 commands. There are 349 CTest registrations;
the previous 348 definitions are preserved. No new whole-suite, Debug or Clang
execution is claimed. Older full-suite receipts retain their original cohorts.

The full experiment input barrier has 1,201 paths, with 15 changed/new inputs
relative to V47. Its exact source delta is preserved. After native/plot jobs
finish, one generator docstring is corrected; AST without docstrings is equal.
That changes the self-hashed generator/manifest provenance for new packs. Use
the preserved input image to replay the historical packet; do not silently
validate it with the current generator or relabel it as a successor rerun.

V48 checkpoint paths are `build/verification/human-inspection-v48-progress-v1.json`,
`build/verification/human-inspection-v48-source-v1`, and
`build/verification/human-inspection-v48-postseal-check-v1.json`. Its raw seal
hash is recorded by the postcheck. Parent V47 raw seal SHA is
`66cab2924859991edc45b4e8b9e4b80af42305ba7fe7dd58811f2a8152347275`.
HEAD remains `e369a623517723b3be3ea3e9806779f3c591e7f9`.

## Continue without mutating completed evidence

Completed snapshots, packets, isolated plotting tools and private builds/SDKs
are immutable. Reusable main builds are `build/inspection-build-scope-off-v1`
(Release), `build/w05-sanitizer` and `build/w05-debug`. Release/SAN collector
outputs are current; Debug was not rebuilt this turn. The private V01 Release
and relocated SDK remain immutable. The .git directory is read-only;
no stage/reset/commit action was used. No native job remains live at closure.

A02's project-license choice, C04/B01 acceptance, B04/B06, R2 retirement,
remaining extensions and release gates remain open. B04 depends on B01/A02;
B06 also depends on B04. Old B01 and fixed-wrapper B05 drafts stay unaccepted
historical drafts; the new B05 gate rests on its named current evidence.
