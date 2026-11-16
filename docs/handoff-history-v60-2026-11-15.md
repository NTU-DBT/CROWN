# CROWN continuation handoff — V60

V60 completes the current source review and three conditional component studies.
The full Refactor implementation goal remains **ACTIVE**. The exact prior handoff is
[preserved](handoff-history-v59-2026-11-15.md). Parent seal:
build/verification/human-inspection-v59-progress-v1.json, SHA256
3a3099b8d61f28e332363c1879918703bf923ae5adcb6bef1ae44c2d16f57018.
Entry audit passes 4,760 source pairs, 134,551 protected artifacts and 67,924
external pins, including the entire V59 private prefix and V57 baseline.
Integrity SHA256 fcbc7693f086614e214b2dd8cfbd10fce9b444690657c8c563b2a9d20920a292.

Current results and commands are in the
[V60 review](verification/component-evaluation-v60-2026-11-15.md) and
[component guide](component_evaluation.md). The inventory has 817 paths: 446
primary paths and 371 test-code paths; all 370 production files retain V59 bytes.
All 19,932 usage cards cover 17,485 nonblank regions across 815 files/185,544 lines;
the canonical checker passes 145,117 local links. Four new regressions pass
Release and ASan/UBSan; existing runtime controls pass 57 commands/280 prefixes
in both main and both newly built standalone profiles.

Three sequential CPU0 studies complete with unchanged inputs and 2,332 recorded
commands: operational 96 arms/144 gates/288 measured invocations; matched 36 arms/
36 gates/108 measured invocations; search 23 queries/353 gates+23 wire proofs/
1,380 processes (345 warmups+1,035 measured). Operational/matched measured processes
each contain one excluded fresh-owner warmup and one measured pass. Exact
resource stops, adverse C02 gaps and whole-implementation confounders are retained.

Measured build bytes are frozen under
`build/component-evaluation-v60-v1/frozen-measured-release-v1`: 789 mutable inputs,
7 native binaries, 21 archives, 151 C++ units and 798 frozen files. Its receiving record
is `build/verification/v60-controlled-build-archive-v1/receiving-v1.json`.
The continuation authority is `build/verification/human-inspection-v60-progress-v1.json`
and its terminal post-seal check. Preserve completed V60/V59/older private
prefixes, source snapshots, SDKs and packets. Use new versioned outputs for
continuation; main Release/SAN producer builds remain reusable. All owned native
jobs are terminal. Do not repeat the full unchanged 362-check engine suites.

Next: receive the complete ten-axis component-attribution matrix and prepare
B06's reproducible report, then continue remaining exact extensions and release
qualification. C05 `maintenance_cost` is unsupported; C03 stays offline with the
V59 underdetermined fits/fallbacks. Comparisons/top-k/difference may use ordinary
change propagation or exact recomputation. Approximation and parallel/distributed
execution are deferred; retain independent serial query runtimes/budgets behind
the multi-query interface. Licensing checks are deferred; preserve rights/notices.

The sections below preserve the V59 history and its original next-work notes.
Use the V60 review and current section above for continuation decisions.

The full Refactor implementation goal is ACTIVE. The ledger remains 63 verified,
two in progress (A02/B04), 13 not started, 78 total. B04 and release acceptance
remain open. Licensing checks are deferred; preserve rights and notices.

[Component guide](component_evaluation.md) ·
[V59 evidence](verification/component-evaluation-v59-2026-11-15.md) ·
[Exact prior handoff](handoff-history-v58-2026-11-15.md)

## Authority and completed review

Parent seal: build/verification/human-inspection-v58-progress-v1.json,
SHA256 d2116dc1b5bd462e5ab8a1922b8fe3bc4401b919dc9e05e1fda6223222517cdb.
The V59 entry audit verifies 4,732 live/frozen source pairs, 121,160 protected
artifacts, 61,023 external pins and 4,701 private baseline files. Integrity SHA:
db3b17efeee915e982518622ae1ed1ec23e753a51d3821f2c50270be37328c17.

All 370 production files retain V58 bytes. The
[full V58 review](verification/full-scope-review-v58-2026-11-15.md)
closes its 433 primary paths; V59 adds separately read successors and clients.
V58 passed all 362 existing Debug checks and all 362 ASan/UBSan checks.
Do not repeat that expensive suite for unchanged engine code.

Root receiving packet: build/verification/component-evaluation-v59-v1.
Current primary inventory: 440 paths (438 code plus two build/provenance JSON).
Final source closure is in v59-full-source-closure-v1. It distinguishes inherited
full reads, exact-diff changes and new reads.

## Implemented this turn

- The workload collector accepts explicitly tagged V3 experimental upper trees
  after checking the actual tree and replaying the original lower proof. V1/V2
  keep strict minimum/witness gates. Constant false stays V1/null only.
- New native_request.hpp, native_set.cpp, native_rows.cpp and session.cpp contain
  606 lines of direct public-API adapters. DISTINCT cardinality uses real signed
  set records; bag output retains multiplicity; net batching uses real source
  transactions; typed Session handles transport, output, WAL and recovery.
- component_analysis.py freezes genuine C03 rational scores with explicit
  unknown/budget/stop fallback and one cold copy of nested evidence.
- run_component_planning.py verifies every retained envelope on all splits,
  obtains a final identical export/calibration, freezes choices before evaluation
  and preserves family/control provenance while sharing identical physical runs.
- CMake targets, standalone installed examples, request schemas and four new
  tests are integrated. There are 366 registrations; all prior 362 remain.

C05 maintenance_cost is still unsupported. C03 here is an offline conditional
forecast, not a new installed policy. The engine gains no update hook, retained
row mirror or error-handling framework.

## Actual validation and studies

Main Release/OFF and ASan/UBSan builds pass all seven CLI/diagnostic targets.
The initial rows link omission was fixed by linking crown_sql_rows; new C++
implementations did not change after their 606-line source-final snapshot.

All four new checks pass in Release (direct scripts against BUILD_TESTING=OFF)
and SAN (4/4 CTest). Initial Release CTest found zero tests and was not counted.
Artifact admission has 19 accepted/22 rejected cases; selector has 18 pure cases.
The final runtime oracle passes 57 commands and 280 SQLite prefix/endpoint
comparisons per profile, across 11 Session arms and both backends.

WAL-tail recovery uses checkpoint_interval=0, reconstruction after input three,
then the next correct input. Eight retained reports show WAL record count 13,
physical sequence six, bare replay row count one and durable replay backlog zero.
The separate nonempty-wal-replay-receiving-v1.json checks those reported fields;
it makes no pre-recovery byte-size or power-loss claim.

Existing B03 measurement_harness passes both profiles, including target RSS,
timeout, output modes and failure controls. Clean-source CTest passes in 5.37s.
Those concurrent correctness clocks are not controlled performance evidence.

Moved installed examples pass 22 final jobs, 11 actual invocations and 84 prefix
comparisons. Each SDK has 145 exact-current public headers and 22 producer-matching
archives. Final 590 frozen paths exclude mutable producers. The optional legacy
build first failed on unchanged upstream header warnings; only external include
paths became SYSTEM PRIVATE, retaining strict own-wrapper warnings. Final
standalone CMake SHA:
e71215107b8ff3050c00e744b433123c4d0e863a8680423e680ef9c8c0d4d818.

The controlled planning study completes all three queries and both backends:
66 physical plans, 330 preflights and 792 runs (198 warmups, 594 measured).
There are 198 summaries and 648 policy/statistics/evaluation rows. All six groups
are available. Choices, calibration and compiled/harness bytes remain unchanged.
Children were pinned to CPU zero; other workers held builds and heavy hashing.
All six fits are underdetermined, with rank four to six over eleven features.
Sampled, stale and absent C03 profiles use explicit height fallback.

Raw study: root packet/controlled-planning-v1.
Receiving: root packet/controlled-planning-receiving-v59-v1.json.
Descriptive outcomes: root packet/planning-descriptive-summary-v59-v1.json.
Do not infer a fixed speedup, global CBO optimum or full B04 acceptance.

## Inspection, frozen artifacts and resumption

All 19,824 adopted cards cover 805 files, 183,069 lines and 17,377 nonblank
regions; 3,006 blank regions retain structural descriptions. There are 20,383
regions total. Checker v3 passes 144,170 local links with no errors. Receiving
adopts 156 authored cards, replaces two obsolete collector cards, rebinds 1,552
CMake and 57 collector cards, and updates 26 exact numeric references. The
SYSTEM successor rebinds 33 cards with one semantic amendment; 61 stale proposal
labels were normalized after explicit adoption. Scopes and code stayed unchanged.

Immutable V59 packets include the collector, selector, native adapters, planning
runner, integration specs, runtime oracle specs, independent native review,
installed examples and controlled build archive. Independent native review reads
all native 606 lines plus the 304-line oracle and receives the eight WAL reports.
All completed jobs are terminal.

The actual measured build is frozen under
build/component-evaluation-v59-v1/frozen-measured-release-v1.
v59-controlled-build-archive-v1 manifest SHA:
7b3ec1088169f1c6470a362fa093e91bad15bcd17226bde9c674b300473f4478.
It retains 743 frozen pins: actual source/build inputs, three measured binaries,
21 archives and 147 recorded C++ objects. System/compiler observations and
unarchived dynamic-library limits remain explicit. Mutable original build paths
are not protected by that archive.

The continuation authority is build/verification/human-inspection-v59-progress-v1.json
and its human-inspection-v59-postseal-check-v1.json. The root receiving packet
becomes immutable when that seal is written. Check their terminal status before
starting another study, and use new workspaces and output paths.

## Next work toward the complete goal

Finish the complete Refactor 14.1–14.4 matrix: storage, generic/specialized runtime,
ordinary/generalized structure, height/depth/event-cost, exact/residual/meta search,
statistics, output, updates, recovery and set/bag/aggregate semantics. Still needed:
the finite literal-search control, matched scaled legacy/native runtime studies,
operational output/backpressure/batch/WAL/checkpoint costs and annotation cases.
Then continue B06, remaining current-scope extensions and release qualification.

Use qualified baseline modes unchanged: line5cd is insert-only with positive
uint32 IDs; line5gc replacements are absolute counts including zero; Scala must
drain actual full results after every event. Preserve its original parser-test
failure. Cross-framework parsing, formatting, JVM/GC and allocation costs prevent
dispatch-only attribution. Final restored-owner account memory is not a whole-pass
peak; target RSS is separate. Never substitute COUNT(*) for DISTINCT cardinality.

Main builds build/inspection-build-scope-off-v1 (Release/OFF) and
build/w05-sanitizer remain reusable, with compile_commands enabled. Old completed
V59/V58/V57 workspaces, SDKs, binaries, packets and all of
build/legacy-baselines-v57-v1 are immutable after their seals. Future work should
use a new versioned workspace, such as build/component-evaluation-v60-v1.

.git is read-only: never stage/reset/commit. exec_command requires
require_escalated; Python uses PYTHONDONTWRITEBYTECODE=1. Keep direct code and
necessary ownership/rollback boundaries. Maintain exact seven-field cards and
regenerate/check maps after source changes. Use own model power, parallel
workhorses and Luna Max for simple work; Astra Max sparingly.

Comparisons/top-k/difference may use ordinary propagation or exact recomputation.
Approximation, shared-query algorithms and parallel/distributed engine execution
stay deferred. Maintain each query independently behind the interface.
