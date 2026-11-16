# V65 full-scope correctness review

The review covers the current 858-path maintained code/configuration inventory:
472 primary paths, including all 389 production files, and 386 test/helper paths.
Every primary path received a full or targeted semantic implementation/interface
inspection. Per-file ranges and depth remain explicit; most test bodies retain
prior source-bound review and full-suite authority. This is not a fresh every-line
semantic reread of all tests or a universal correctness proof.

## Findings and direct corrections

**REC-01 — aggregate receiver work refusal was misclassified.** A genuine
aggregate descriptor rebinds successfully with default receiver limits, but
`binding.work_limit=0` produced `ImageFault::binding`. The direct binder returned
`resource_limit`; the row sibling correctly produced `ImageFault::work`.
The [preserved reproduction](../../build/verification/v65-full-scope-review-v1/recovery-review-followup-v1/classification-probe/receiving.json)
compiles against the actual pre-fix archives and retains descriptor bytes.

The [aggregate descriptor](../../src/recovery/sql_aggregate_descriptor.cpp)
now inspects the existing `BindingDiagnostic`: resource refusal becomes work,
while semantic failure remains binding. It uses the same direct branch as rows.
No catch/retry layer or query-update operation was added. The
[regression](../../tests/unit/sql_aggregate_descriptor_test.cpp) denies each of
four independent receiver binding-work domains and requires the work fault plus
unchanged retained account state, across both backends and opaque metadata.
The [independent rebuilt-archive probe](../../build/verification/v65-full-scope-review-v1/corrections-v1/independent-classification-v1/receiving.json)
receives the corrected category, successful defaults and exact pre/post descriptor
bytes. The [usage guide](../sql_aggregate_descriptor.md) states the distinction.

**RUNTIME-DOC-01 — stale FIFO wording.** The
[window header](../../include/crown/runtime/window.hpp) described only label FIFO.
Its comment and class contract now distinguish label FIFO, full-row lifetime FIFO
and unrestricted order. Labels for the same row share set presence; label IDs
remain distinct. The two-line correction preserves all executable tokens,
literals and line numbers. The [window policy guide](../update_patterns.md)
retains the exact five-mode contract.

## Scope and reasoning

| Partition | Production | Other primary | Evidence |
| --- | ---: | ---: | --- |
| Runtime, storage, resources, observations | 149 | 8 examples | [Semantic coverage and invariant notes](../../build/verification/v65-full-scope-review-v1/runtime-review/README.md) |
| IO, recovery and public error boundary | 130 | 0 | [Complete production follow-up](../../build/verification/v65-full-scope-review-v1/recovery-review-followup-v1/findings.md) |
| Frontend, IR, planner, catalog and annotations | 100 | 16 examples/build files | [Semantic coverage and caller arguments](../../build/verification/v65-full-scope-review-v1/compiler-review-followup-v1/findings.md) |
| CLI, build, packaging and offline tools | 10 | 59 | [Root implementation review](../../build/verification/v65-full-scope-review-v1/root-review/findings.md) |

The [combined receiver](../../build/verification/v65-full-scope-review-v1/coverage-receiver-v1/receiving.json)
checks unique assignment, original source hashes, actual semantic depth and closed
review packets. Initial limited passes and runner-selection errors are preserved;
successor source inspections close their primary-code gaps. Failed runner
selection is not relabeled as a failed engine assertion.

Review arguments trace occurrence identity, support zero crossings, weighted
products, aggregate signed arithmetic, transaction publication/rollback, shared
operation grants, FIFO row lifetimes, borrowed ownership, W/I/C/D replay and
complete descriptor/checkpoint/output binding. Cold compiler admission,
fixed diagnostics and file uncertainty remain at their owning boundaries.
No additional ownership layer, parallel executor or shared mutable query state
was introduced. Comparisons/top-k/difference remain ordinary exact propagation
or recomputation work; approximation, shared-query optimization and parallel/
distributed execution remain deferred.

The [paper/design map](../code_review.md) retains exact paper versions and
separates paper context from local compiler, proof, allocator and durability
arguments. No new theorem, hardware power-loss or performance claim is made.

## Validation and source vintages

At the V64 baseline, independent SQLite recomputation matches 619 row queries
on both backends: 1,238 cases, 21,046 snapshots and 16 epochs per case.
Independent Python integer/Fraction checks match 1,000 aggregate cases and 23,523
observations. An independent window model matches 25 cases and 4,000 commands
across all five policies. Inputs, raw outputs, oracle code and executable hashes
are retained in the runtime/compiler review packets.

Selected direct registered-command cohorts pass: runtime/storage 20, recovery 20,
compiler/planner 18 Release plus 18 sanitizer, and root CLI/tooling nine.
After the behavioral fix, both profiles rebuild the affected aggregate-recovery
and consuming targets and run six selected checks: descriptor, checkpoint,
Session, Session faults, transaction crashes and aggregate CLI. Exact results are
in [Release corrections](../../build/verification/v65-full-scope-review-v1/corrections-v1/release/receiving.json) and
[sanitizer corrections](../../build/verification/v65-full-scope-review-v1/corrections-v1/sanitizer/receiving.json).
These are direct script/binary executions; CTest supplies registration discovery.

The actual V63 full 383-test Release and 383-test ASan/UBSan executions retain
their original source point. This review does not rename them as a current full
suite. The window comment correction is joined by token/literal equality to the
header used by current native validation. Original archived R1/R2 images and
closed evidence remain preserved. V65 corrected source is a separate successor
to the V64 accepted image; the preserved archive retains its original category
behavior until a separately qualified successor image is assembled.

The [independent fix/card receiver](../../build/verification/v65-full-scope-review-v1/post-fix-independent-v1/findings.md)
checks the three edited source files and all 115 affected cards. Three semantic
contracts are amended; all 20,566 unrelated records retain exact identity.
Source-bound block maps, local links and final source hashes are received in the
[V65 receiver](../../build/verification/v65-full-scope-review-v1/final-receiving.json).

The implementation goal remains active. Ledger state remains 69 verified,
one in progress and eight not started; this review adds no feature or new
release decision. The [handoff](../handoff.md) gives the current source authority.
