# P04 certified planner fast paths, 2026-11-06

P04 is implemented and acceptance-verified. The full 78-card goal remains
active: 33 verified, three in progress (A02/P06/O06), 42 not started. This is
neither external V02 review nor a release/durability signoff.

Baseline is uncommitted master at
`e369a623517723b3be3ea3e9806779f3c591e7f9`. Original Refactor.md and legacy
trees are preserved. Original requirements are in
[Refactor.md](../../Refactor.md), P04. The
[completion preflight](p04-design-preflight-2026-11-06.md) and historical
[O03 packet](batches-windows-2026-11-06.md) retain their own scope.

## Implementation and preservation arguments

Astra implemented the [exact producer](../../src/planner/exact.cpp) and
[hierarchy/component helpers](../../src/planner/fast_paths.cpp). A separate
Astra author implemented the [independent checker](../../src/planner/certificate.cpp).
Root integrated codec/schema/build behavior; Luna Max authored differential,
corruption and persistent-failure cases. A fresh Astra reviewer accepted the
actual mathematics, source, written preservation arguments and coverage,
conditional on the final matrix which now passes.

Empty bodies return height zero. Singletons and q-hierarchical queries receive
complete height-one witnesses. Nonempty constant/nullary and contradictory
bodies retain their structural native occurrences. Hierarchy classes use actual
occurrence incidence, with strict free-variable upward closure; equal incidence
may contain both free and hidden variables. Dynamically sized scopes and
occurrence collections introduce no semantic 64-bit mask/arity limit.

Disconnected decomposition applies only to the full-query root, retaining
global occurrence identities and empty global component boundaries. A tree is
assembled under an empty generalized root and has maximum component height.
Equal complete scopes permit one root representative while preserving all
actual native labels in the upper witness. Incumbent pruning uses only the
universal child bound or already completed exact child bounds; cutoffs never
become cached infeasibility. These rules preserve at least one optimum.
See the actual [preservation proofs](../planner_proofs.md) and
[oracle contract](../tree_oracle.md).

Public search emits `crown_partition_exact_v2`. Certificate schema version 2
explicitly declares scope-orbit and full-root component rules; the outer oracle
envelope remains version 1 and CQ binding versions 1/2/3 retain their meaning.
The independent checker derives complete-scope classes and actual components
itself. Every provided claim is proved against its actual occurrence IDs before
transport to an orbit key, preserving both state flags and using strictly
smaller dependencies. Missing claims supply only universal one. V1 retains
exact labelled-state keys and exhaustive replay. Unsupported/corrupt versions,
flags, numeric fields, algorithm/schema mismatches and query bindings reject.

The private `CROWN_PLANNER_TESTING` baseline disables the P04 shortcuts,
symmetry, incumbent pruning and proof compression and emits v1 evidence. It is
compiled only into a separate testing archive. Production exposes no baseline
control function. P04 retains strict exact-or-resource-limit behavior; it adds
no resumed search or public uncertified incumbent. P06 remains open.

## Independent semantic, corruption and failure evidence

All 82 tests pass the final five-configuration matrix below. Retained successful
stdout includes the old 371+7 exact-oracle cases and the new 371-case small
q-hierarchy/P03/private-v1 comparison, structural constant/nullary/ignored/repeated/
contradictory bodies, mixed equal incidence, actual fast-path/prune counters,
component heights one/two/three and permutations, residual seven-/nine-atom
height-three cases, more than 64 variables/occurrences and a 70-level hierarchy.
Malicious state orbit/flag/component/bound/native-ID mutations and honest
producer/replay work/time/depth stops pass. Upper witnesses are checked with P02.

The initial malicious residual fixture wrongly dropped its global boundary.
It now checks both a valid finite lower bound on an infeasible boundary-aware
residual and rejection of a false height-two claim on a height-one residual.
No producer/checker rule was weakened.

Persistent allocation sweeps cover every observed successful-path position:

| Path | Fault positions / successful allocation calls |
| --- | --- |
| Hierarchy construction | 492 |
| Connected duplicate-scope search | 1029 |
| Disconnected height-two/nullary components | 833 |
| Independent v2 replay | 534 |
| Private v1 baseline | 985 |
| Independent v1 replay | 497 |

Failure stays armed through unwind and optional-buffer fallback. Every fault
returns an honest resource result or propagates bad_alloc without publishing a
partial tree/minimum/proof. Inputs and supplied certificates remain unchanged;
clean recovery matches, and typed move/destruction cleanup does not allocate.
These are observed counts, not stable API allocation guarantees.

Work charging covers controlled structural operations, not all standard-container
comparisons/copies, allocation CPU or scalar widths. Validation and checkpointed
clock exclusions are explicit in the proof/contract. No hard deadline or complete
S05 memory cap is claimed. The stricter owned continuation work belongs to P06.

## Final compiler, sanitizer and source-only matrix

All jobs are terminal/closed. No native/test input changed during the matrix.
Every before/after fingerprint matches the 441-input frozen snapshot:
`a197c3c6f58e361c70facbf3d39943f8b63dd5023800a3d40a3063e3bf765c60`.
Fingerprint order is sorted path/NUL/content/NUL over CMakeLists/CMakePresets
and include/src/apps/tests/cmake, excluding Python caches.

| Configuration | Result | CTest time |
| --- | --- | --- |
| GCC 13.3.0 Debug | 82/82 pass | 196.30 s |
| GCC 13.3.0 Release | 82/82 pass | 22.91 s |
| ASan/UBSan, including external parser C | 82/82 pass | 874.55 s |
| Clang 18.1.3 C/C++ Debug | 82/82 pass | 150.88 s |
| Fresh source-only Release | 82/82 pass | 22.23 s |

Clean verification took 402.45 s (402.52 s wrapper total) and removed
`/tmp/crown-clean-source-atwcuvnx`. Full successful raw CTest output, stage
logs, per-configuration/aggregate summaries and independent matrix audit are
retained under ignored `build/verification/planner-fast-paths-*`.
The clean-source log retains the complete 82/82 aggregate; detailed passing-test
stdout and counter rows are retained for the four in-place configurations.
The production core has zero private-baseline exports; the testing archive has
one. Production RuntimeTestProbe exports remain zero and testing exports eleven.
The compiler versions and sanitizer recipes, including all new planner/IO/test
sources and parser C, were independently inspected.

Final Release schema validation passes 21 meta checks, 26 normalized artifacts,
19 identity artifacts, 17 height certificates, 59 admission artifacts, two
layout/projection artifacts, 31 physical artifacts, three support reports,
two rejected updates, two physical inputs and three runtime diagnostics.
This includes actual legacy v1 schema/native reader/replay, rather than parsing
alone. Existing D04/D05 and O01/O02/R06/O03 oracle/fault evidence is retained.

## Failed attempts retained

Attempt one exposed two fixture gaps: catalog-v3 integration expected certificate
envelope 1, and optimized GCC diagnosed a nested temporary variant in the new
fixture builder. The tests now expect certificate 2 while preserving CQ binding
3, and construct the integer variant explicitly in place. No warning was disabled.
Debug/Clang reached 81/82, Release/clean stopped at compilation, and the remaining
sanitizer process group was explicitly stopped before edits. Failed logs and
source freeze are archived under `planner-fast-paths-attempt-1/`.

Attempt two passed four configurations but sanitizer reached 81/82: the new
fault fixture replaced ordinary new/delete but missed nonthrowing new used by
stable_sort. ASan correctly detected standard operator-new memory reaching the
test's free replacement. Scalar/array nonthrowing allocation/deallocation now
share the same tracked malloc/free family and persistent faults stay armed.
Focused ASan/UBSan passes in 5.40 s; the final full sanitizer pass above follows.
All five attempt-two jobs ended before edits. Their failed disposition, logs,
source freeze and provisional audit remain under `planner-fast-paths-attempt-2/`.
Neither failed attempt is acceptance proof; sanitizer checks stayed enabled.

## Final source seal and handoff

The [529-input source manifest](planner-fast-paths-sources.sha256) adds seven
ordinary inputs to the historical O03 inventory. It covers final code/tests,
schemas/tools/dependency inputs and ordinary documentation; verification files,
handoff/ledger and caches are excluded to avoid circular evidence hashes.
Manifest SHA-256:
`d831a4db6c9817ada2ade5171f12311cac072ffcb7dc306a358aeb549a799703`.
Original Refactor.md SHA-256 remains
`bb90e4a4e97e2817a0869ad86c5c8b00e571bb241f153fb44641c71f86fcd5ce`.
Historical manifests are preserved, never resealed against later source changes.
Fresh independent Luna Max validation passes every one of the 529 checksums,
exact rediscovered inventory, the native fingerprint, original requirements,
all five historical manifest-file hashes and the 78 unique ledger rows at
33 verified / three in progress / 42 not started. All 550 local destination
occurrences (223 unique) across 60 Markdown documents resolve, including the
P06 API proposal. Source-seal audit JSON and full checksum output are retained
as `planner-fast-paths-source-seal-audit.json` and
`planner-fast-paths-source-seal-sha256-check.log` under ignored build evidence.
The audit's historical-O03 wording finding was fixed only in the excluded
handoff/ledger; the new seal and all historical hashes remain unchanged.

Old CTest LastTestsFailed markers in Debug/Clang/sanitizer predate the fresh
all-pass LastTest logs and correspond to archived attempts one/two. They remain
historical artifacts; final summaries and full current raw output establish
zero failures. No failure marker was suppressed or treated as current proof.

Continue P06 with the saved [preflight](p06-design-preflight-2026-11-06.md),
[API proposal](p06-api-proposal-2026-11-06.hpp),
[transition plan](p06-transition-plan-2026-11-06.md) and
[implementation seams](p06-implementation-seams-2026-11-06.md).
The [baseline extraction proposal](p06-baseline-proposal/README.md) is uncompiled
preparation only. P06 must own real producer, validation and independent replay
continuations and distinguish immutable validated incumbents from verified
optima. No P06, P05, S05 or release completion is inferred from P04.
