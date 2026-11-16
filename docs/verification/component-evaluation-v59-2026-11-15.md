# Component integration — V59

V59 continues B04 after the [full V58 correctness review](full-scope-review-v58-2026-11-15.md).
The implementation goal and all ten B04 axes remain open. This record separates
current-source correctness, installed-consumer qualification and controlled
experiments. The [component guide](../component_evaluation.md) documents actual
commands, interfaces, units and remaining controls.

## Entry and source authority

The [entry audit](../../build/verification/continuation-v59-entry-v1/README.md)
verifies 4,732 live/frozen source pairs, 121,160 protected artifacts, 61,023
external pins and all 4,701 immutable private-baseline files. Parent seal SHA256:
`d2116dc1b5bd462e5ab8a1922b8fe3bc4401b919dc9e05e1fda6223222517cdb`.
The audit's integrity SHA256 is
`db3b17efeee915e982518622ae1ed1ec23e753a51d3821f2c50270be37328c17`.
No old completed packet, snapshot, SDK, baseline source/archive or `.git` file
was changed. All 370 production files retain V58 bytes.

## Implemented boundaries

The collector accepts a separately tagged V3 experimental upper artifact. It
reconstructs and validates the actual physical tree, replays the original lower
certificate against the actual original query, and checks original minimum
height no greater than actual upper height. V1/V2 retain their exact-height
requirements, including V1 witness-tree equality. Constant false remains
V1/null-proof only. V3 adds explicit upper-only metadata and never creates a
`MinimumHeightCandidate` from caller flags.

New native clients use genuine public APIs:

- Unweighted set cardinality folds actual signed DISTINCT projected records,
  not joined-witness COUNT(*). Delta/full observation and maintenance/full
  observation perform their actual advertised work.
- SQL rows retain compressed multiplicities. Atomic source-net batching uses
  real prepared source replacements and reports source offsets separately from
  transaction sequence. Singleton and net controls share observation endpoints.
- Typed Session transport retains every physical commit. Output drain,
  serialization and durable local delivery are separate controls. WAL includes
  initial setup, generation rotation and actual clean-owner reconstruction.

The new planning runner retains exact/residual/meta provenance and all valid
ordinary artifacts. It preflights every retained envelope on all trace splits,
then obtains a final identical candidate/proof export and one pooled calibration.
Choices and calibration are serialized/hash-bound before held-out measurement.
The exact rational selector preserves unknown scores, captured-memory limits,
stale stamps and explicit height fallback; its nested evidence is copied once
at the cold boundary. C03 remains offline; C05 event-cost installation is not
enabled. No new engine update hook, retained row mirror or error framework is
introduced.

## Actual correctness checks

Both integrated Release and ASan/UBSan builds pass. An initial root CMake link
omission for `crown_sql_rows` is preserved in the failed v1 logs and corrected
in v2; the 606 new C++ source lines required no implementation correction.

The [native receiving record](../../build/verification/component-evaluation-v59-v1/native-validation-v59-v1.json)
binds all four new checks. Release runs them directly against the production
`BUILD_TESTING=OFF` binaries; the sanitizer profile passes all four CTest
registrations. Its planning test takes 334.85 seconds. An initial Release
CTest invocation found zero tests and is explicitly excluded from passing
evidence. There are now 366 registrations: the prior 362 are retained; this
turn does not relabel selected execution as a repeated full suite.

- Artifact admission: 19 accepted and 22 rejected controls, both backends and
  snapshot/delta demands, with 20 independent SQLite prefixes.
- Offline selection: 18 pure cases include uint64 rational ordering, ties,
  partial/absent/native-stop/budget fallback, foreign keys, calibration identity
  and independence from later caller mutation.
- Runtime v2: **57 actual commands / 280 SQLite prefix or endpoint comparisons**
  per profile, 11 Session arms and both backends. DISTINCT endpoint witnesses,
  signed/full set results, bag multiplicity, cancelling net edits, transport,
  serialization, WAL, checkpoint/recovery, durable delivery, rejected state
  reuse and repeated logical-owner controls pass.
- All eight bare/durable WAL-tail reports across profiles/backends have no
  checkpoint rotation, reconstruction after input three, final WAL record count
  13 and physical sequence six. Bare recovery consumes the one expected replay
  row; verified durable recovery has no replay backlog. The
  [separate receiver](../../build/verification/component-evaluation-v59-v1/nonempty-wal-replay-receiving-v1.json)
  checks those fields. This is not a pre-reconstruction byte-size, crash or
  power-loss measurement.
- The existing B03 measurement harness passes in Release and ASan/UBSan:
  12 mode/backend cases with three retained runs, owned timeout, disabled
  metrics, failure/wait controls and target-RSS probes remain compatible.

Concurrent build/correctness clocks in those packets are ineligible for
performance comparisons. The Session final-owner account sample is not a
whole-pass peak across destroyed owners. Process RSS has a separate scope.

## Human inspection and review

The maintained index has **805 files / 183,069 lines / 20,383 regions**,
with **19,824 cards covering all 17,377 nonblank regions**. Blank spacing accounts
for the other 3,006 regions. Receiving adopts 156 authored cards, replaces two
obsolete collector cards, rebinds 1,552 unchanged CMake cards and 57 unchanged
collector cards, and updates 26 exact CMake references. The optional legacy
consumer's external-header diagnostic correction has a separately received
33-card successor with one semantic amendment.

The [independent native review](../../build/verification/v59-b04-native-review-v1/review.md)
fully reads the four new native files and final runtime oracle: 910 lines,
with source spans, API arguments and retained replay checks. It finds no
concrete blocker within that scope. Separate source-author and independent
selector/CMake reviews keep their exact limits; unchanged production authority
comes from the full V58 review. Finite checks do not constitute an exhaustive
formal proof or predictive-performance guarantee.

## Installed-consumer and controlled receiving

Fresh moved SDKs build all four native runtime clients and the planning client
under both Release and ASan/UBSan; the optional unchanged-archive legacy C++
observer also builds in Release. Eleven actual invocations and 84 independent
prefix comparisons pass. Each SDK has 145 exact-current public headers and
22 archives matching the corresponding producer bytes. An optional legacy
consumer build exposed warnings in unchanged upstream/fmt
headers; the target now marks only those external include paths SYSTEM while
retaining strict warnings on its own wrapper. Failed predecessor inputs/logs
remain preserved, and final installed-source qualification uses the successor.

The [controlled planning study](../../build/verification/component-evaluation-v59-v1/controlled-planning-receiving-v59-v1.json)
completes all three query families on both backends, with no unavailable group:
66 retained physical plans, 330 all-split preflights and 792 retained runs.
The runs contain 198 warmups and 594 measured repetitions, yielding 198
configuration summaries and 648 policy/statistics/evaluation rows. Choices and
calibration remained frozen; the runner rechecks compiled/harness hashes at
completion. Other owned native jobs and heavy worker hashing were held during
the window, and each child was pinned to CPU zero. Hardware caches, frequency
and unrelated shared-machine activity retain the stated limits.

All six fits are underdetermined: numerical rank four to six over eleven
observed features. Full-census C03 scores are available for the 54 family/
evaluation rows; sampled, stale and absent profiles each produce 54 explicit
height fallbacks. Absent weighted-depth ranking stays unavailable. These are
finite availability outcomes, not independent statistical replicates or an
accuracy/speedup claim. The
[descriptive summary](../../build/verification/component-evaluation-v59-v1/planning-descriptive-summary-v59-v1.json)
and raw records retain actual prediction errors and measured regret.

The complete matrix still requires matched runtime/baseline measurements,
finite literal-search controls, SQL annotation cases and operational
batch/output/recovery studies. No B04 or release acceptance is claimed. Rights
and notices are preserved while licensing review stays deferred. Approximation,
shared-query algorithms and parallel/distributed engine execution remain
deferred; every query is maintained independently.
