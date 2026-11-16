# V37 — continuation, delta and independent reference usage

This review adds **178 source-bound usage cards in nine files**. All 1,196
native inputs, including 355 production paths, remain byte-identical to V36.
The change adds no runtime handler, wrapper, allocation or work checkpoint.
No native build, CTest, SDK test or timing experiment runs in this packet.

The full Refactor.md goal remains active: **57 verified / 1 in progress (A02) /
20 not started**, 78 total. W06 retains its bounded verified profile. A02 still
blocks C04/B01; R2 retirement, V04 packaging and release gates remain open.

## Usage coverage

The [source index](../code_specs/README.md) maps 751 files /
172,040 lines / 19,412 blocks, with 16,132
contracts in 13,716 blocks. All selected non-test regions have
usage cards; **477 selected test regions remain**. Other unreviewed scaffolding
keeps structural facts only. Mapping and card presence do not certify every
semantic claim or every existing comment.

| Source | New cards | Usage inspected |
| --- | ---: | --- |
| [Continuation semantics](../code_specs/files/tests/unit/planner_continuation_test.cpp.md) | 21 | Slicing, proof phases, ownership, authority and resource extension. |
| [Continuation edges](../code_specs/files/tests/unit/planner_continuation_edge_test.cpp.md) | 22 | Depth zero, cancellation history, corrupt v1, idle time and retained uppers. |
| [Planner reports](../code_specs/files/tests/unit/planner_progress_test.cpp.md) | 12 | Typed proof writers, honest progress, binding versions and local schema handoff. |
| [Delta specification](../code_specs/files/tests/unit/delta_spec_test.cpp.md) | 28 | Exact projected before/after difference, witness ownership and independent model. |
| [Replay scale comparison](../code_specs/files/tests/unit/delta_replay_scale_test.cpp.md) | 24 | Raw production output, live factors, producer counters and growing preparation. |
| [Reference candidate set](../code_specs/files/tests/reference/candidate_set.cpp.md) | 24 | Finite requested-height enumeration, literal signatures and resource-limited prefixes. |
| [Candidate reports](../code_specs/files/tests/unit/candidates_io_test.cpp.md) | 15 | Original-proof binding, frozen prefixes, failure reports and residual provenance. |
| [SQL normalization](../code_specs/files/tests/unit/normalization_test.cpp.md) | 18 | Support counts, alias staging, SQL semantics, exact values and ownership. |
| [Physical lowering](../code_specs/files/tests/unit/physical_lowering_test.cpp.md) | 14 | Static instruction interpretation, independent subtree joins and invalid-tree boundaries. |

Each card records purpose, inputs/outputs, invariants, ownership, failure, cost
and real references. [Paper context](../code_review.md),
[planner continuations](../planner_continuations.md),
[delta transition specification](../delta_transition_spec.md),
[delta runtime](../delta_runtime.md), [SQL normalization](../sql_normalization.md)
and [physical plans](../physical_plans.md) explain which obligations belong to
the paper and which belong to local execution, publication and storage.

## Planner authority and failure boundaries

Strict search withholds incumbent handles. Best-found exposes a complete P02
upper before final proof. Only completed independent replay publishes optimum
or empty-family authority. Progress, including complete progress, serializes
with a null certificate; explicit typed writers emit certificates. A validated
upper carries no minimum claim. Original-query proof remains separate from
alternative candidate and trace-only residual provenance.

The four small differential fixtures compare production v2, private v1 and
frozen P03; one-shot, unit and varied grants compare checked heights and
committed transitions. The height-three residual exposes the listed phases.
The 70-variable/occurrence case and 150-scope hierarchy cross old width/depth
assumptions in finite fixtures; they do not prove arbitrary-input complexity.
Scope fixture builders require dense zero-based numeric names.

Empty body can finish at logical depth zero. Nonempty owners create a shell
then stop before a forbidden frame; repeated attempts charge attempts without
commits. Raising work/time/depth retains history. Producer completion with
replay work denied is still unfinished. Cancellation clears active depth while
retaining work/checked-prefix history and already published immutable uppers.

Zero-work/time grants are inert before clock sampling; negative time is invalid.
The two explicit 2.5-second idle waits are source schedules, not V37 timing runs.
Step guards bound loop iterations, and several finish/ownership loops have no
step guard. Active time and transition counters are not full CPU/byte budgets.
The public continuation boundary distinguishes retryable bad allocation from
terminal unexpected failure; removing either handler changes that contract.

## Reference work and production work

The normal-form collector is a blocking reference routine. Native/active-variable
caps of three are operational stops. It enumerates labeled Prüfer shapes, roots,
zero through m−1 generalized nodes and relevant native-scope subsets. Requested
height filters this finite family; it does not prove a minimum. P02 checks each
accepted draft before its claims are copied. Structural NFREF1 signatures retain
literal occurrences/variables and establish only local equality. Public signing
requires a previously validated finite tree and performs unchecked recursion.
Work charges selected transitions, not every byte, sort, allocation or validator
instruction. Partial results remain explicitly non-exhausted.

The delta specification test fully materializes E/L snapshots, subtree joins,
candidate fragments and before/after A04 answers. It checks exact raw output
cardinality before set comparison, earliest witness ownership, alias prefixes,
projection collisions, Boolean/constant routes and 3/8-child products. Its tiny
domain loops describe 2,504 transitions. Cardinality inequalities involving
factor count times delta size are not complete work/delay bounds.

The scale test uses real DeltaRuntime on R(a,x)→S(x,y), with N=2 and N=64.
Ordered replay accepts N candidates; the anchored comparison visits 2N and
rejects N. Raw signed rows, contiguous ordinals, layout tokens, spool drain,
current results and global live projections are checked against A04.
First/next/last successful producer-work maxima match between those two N values;
preparation and finalization must grow. apply() drains the producer before
returning the committed output spool. epoch.next() consumes that spool. These
manual counters do not measure user-consumption latency or establish a general
wall-clock constant-delay bound.

SQL adapter assertions use a correctness baseline that copies physical/logical/
support state before atomic swaps. They cover 12×48 deterministic seeded updates,
selected failure-state fields, NULL/OR/parameter behavior and 70-column ownership.
The physical-lowering interpreter uses reference tables and independent subtree
joins; it does not execute the incremental runtime. Its 128-native chain checks
compiled depths and empty storage, rather than a populated deep cursor.

## Receiving review and preserved evidence

Three author packets and three independent reviewer packets remain immutable.
Root reads all 4,369 target lines and relevant callers before the cards, checks
the actual frozen missing-region set, and replays field amendments explicitly.
All eight executable mains are covered; candidate_set.cpp is a library and has
no main. Large frozen inventory/registry files are pinned without duplicate
copies. Seal-file and canonical payload digests retain separate meanings.

The [receiving packet](../../build/verification/inspection-continuation-tests-v37-v1/README.md)
contains source notes, exact amendments, native identity, regenerated coverage
and local link checks. Generation completes before validation. Source hashes,
unique anchors, actual region sets, no stale/unused cards and local destinations/
fragments are checked. External URLs retain explicit skipped status.

Latest boundary: build/verification/human-inspection-v37-progress-v1.json,
frozen source build/verification/human-inspection-v37-source-v1. The exact prior
handoff is [V36 history](../handoff-history-v36-2026-11-13.md).
[V33 native acceptance](human-inspection-v33-2026-11-13.md) and V32's broader
SQL/installed receipts retain their dated attribution. No fresh full 348-test,
Clang, benchmark or release claim follows from source identity.
