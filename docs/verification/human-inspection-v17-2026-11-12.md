# Inspectable build commands and a smaller test-disabled build

The source index now contains **10,816 usage contracts in 8,465 blocks**, across
693 maintained files / 159,432 lines / 17,884 mapped blocks. Every inventoried
line has a structural map. Start with the [source index](../code_specs/README.md),
[primitive contracts](../code_specs/primitives.md) and [review guide](../code_review.md).
Contracts describe purpose, inputs/outputs, invariants, ownership, failures,
costs and source/design references. Structural mapping is not universal semantic
or execution proof; 4,549 selected test scopes still need individual review.

The [root CMake review](../../build/verification/root-cmake-human-contracts-v1/report.md)
contributes 1,147 command contracts. All 1,254 selected root commands now have
cards; the additional existing comment card remains. The receiving integration
preserves unrelated records, updates source pins and explicitly corrects the
12 moved command cards and five contextual anchors. Tools, examples and CMake
modules retain their complete selected coverage. All 5,468 selected production
scopes retain contracts.

## Keep collision libraries inside the testing boundary

Five S04 collision-only storage libraries were unconditional default-build
members despite having only guarded test consumers. Their existing declarations,
definitions and dependency links now live inside the following BUILD_TESTING
branch. Production storage declarations and links remain outside it. No command,
argument or conditional was added: the 1,254-command multiset is unchanged after
normalizing leading indentation. Three obsolete comments now describe the actual
build, and a short comment identifies the collision variants.

Actual CMake file-api and generated make metadata show 28 targets before and
23 after with BUILD_TESTING off: exactly the five private testing libraries
are removed. Both testing macros are absent from that compilation database.
Testing-on Debug and sanitizer builds retain all five targets and their matching
PUBLIC macro/dependency chains. All 325 test commands and execution properties
match the predecessor after excluding only source-line backtrace metadata.
The source-line metadata changes with the moved declarations and comments.

## Construct derived terms directly

The fresh strict Release default build found GCC's maybe-uninitialized diagnostic
while moving a temporary nested variant in SqlRowsProgram::export_core.
Constructing the known VariableId alternative directly with in-place emplace
removes that temporary, and the complete test-disabled default build succeeds
with warnings treated as errors. No warning suppression or exception handler
was added. The exported variable, catalog/query shape and validation remain.
This is cold compiler/export work; no runtime speed measurement is claimed.
Of the 326 production include/src/apps files, 325 remain byte-identical to v16;
only this compiler source changes.

Four collision regressions pass per profile: Debug 1.64 seconds and
ASan/UBSan/leaks 5.94 seconds. The three SQL binding/runtime/independent-oracle
regressions also pass per profile: Debug 53.47 seconds and sanitizer 62.15 seconds.
The narrow source diff, original failed Release attempt, successful retry,
configuration graphs, source maps and terminal CTest logs remain preserved.
Each recorded command has no in-command input drift; earlier commands precede
the compiler fix and their distinct source cohorts are explicit.

## Evidence and next work

Root evidence is `build/verification/inspection-build-scope-v1`; the independent
read-only review is `build/verification/build-scope-independent-review-v1`.
The documentation checker passes 96,284 generated local links, source hashes
and contiguous partitions. This checkpoint does not rerun all 325 tests or
claim a release, latency improvement or installed-consumer gate.

Seal: `build/verification/human-inspection-v17-progress-v1.json`; frozen source:
`build/verification/human-inspection-v17-source-v1`. Preserve the immutable
[v16 predecessor](human-inspection-v16-2026-11-12.md) and its evidence.
Full Refactor implementation remains active. W06 still needs actual projected
bag deltas, physical-source/aggregate atomic batches and recovery integration;
its private proposal is not yet implemented or verified here.
