# V38 — memory, journal and recovery boundary usage

This source review adds **220 block usage cards in 20 test files**. Three author
groups and three independent reviews are followed by root source/caller checks.
All 1,196 native inputs, including 355 production paths, remain byte-identical
to V37. No runtime handler, wrapper, allocation or work checkpoint is added.
No native build, CTest, SDK test or timing experiment runs in this packet.

The full Refactor.md goal remains active: **57 verified / 1 in progress (A02) /
20 not started**, 78 total. W06 retains its bounded verified profile. A02 still
blocks C04/B01; R2 history retirement, V04 and release gates remain open.

## Usage coverage

The [source index](../code_specs/README.md) maps 751 files /
172,040 lines / 19,412 blocks, with 16,352
contracts in 13,936 blocks. All selected non-test regions have
cards; **257 selected test regions remain**. Other unreviewed scaffolding keeps
structural facts only. Mapping/card presence does not certify every comment or
semantic claim. Each card records purpose, inputs/outputs, invariants, ownership,
failure, cost and concrete references.

| Source | New cards |
| --- | ---: |
| [constraint_memory_test.cpp](../code_specs/files/tests/unit/constraint_memory_test.cpp.md) | 14 |
| [instrumentation_memory_test.cpp](../code_specs/files/tests/unit/instrumentation_memory_test.cpp.md) | 13 |
| [epoch_memory_test.cpp](../code_specs/files/tests/unit/epoch_memory_test.cpp.md) | 13 |
| [invariant_memory_test.cpp](../code_specs/files/tests/unit/invariant_memory_test.cpp.md) | 7 |
| [runtime_inspection_test.cpp](../code_specs/files/tests/unit/runtime_inspection_test.cpp.md) | 16 |
| [session_image_test.cpp](../code_specs/files/tests/unit/session_image_test.cpp.md) | 13 |
| [reoptimization_fault_test.cpp](../code_specs/files/tests/unit/reoptimization_fault_test.cpp.md) | 13 |
| [reoptimization_promotion_fault_test.cpp](../code_specs/files/tests/unit/reoptimization_promotion_fault_test.cpp.md) | 12 |
| [reoptimization_descriptor_test.cpp](../code_specs/files/tests/unit/reoptimization_descriptor_test.cpp.md) | 8 |
| [reoptimization_recovery_budget_test.cpp](../code_specs/files/tests/unit/reoptimization_recovery_budget_test.cpp.md) | 8 |
| [reoptimization_rebuild_test.cpp](../code_specs/files/tests/unit/reoptimization_rebuild_test.cpp.md) | 7 |
| [reoptimization_selection_test.cpp](../code_specs/files/tests/unit/reoptimization_selection_test.cpp.md) | 9 |
| [reoptimization_recovery_admission_test.cpp](../code_specs/files/tests/unit/reoptimization_recovery_admission_test.cpp.md) | 7 |
| [reoptimization_churn_test.cpp](../code_specs/files/tests/unit/reoptimization_churn_test.cpp.md) | 6 |
| [reoptimization_policy_test.cpp](../code_specs/files/tests/unit/reoptimization_policy_test.cpp.md) | 2 |
| [journal_test.cpp](../code_specs/files/tests/unit/journal_test.cpp.md) | 14 |
| [epoch_index_test.cpp](../code_specs/files/tests/unit/epoch_index_test.cpp.md) | 12 |
| [delta_factor_test.cpp](../code_specs/files/tests/unit/delta_factor_test.cpp.md) | 11 |
| [runtime_storage_work_test.cpp](../code_specs/files/tests/unit/runtime_storage_work_test.cpp.md) | 11 |
| [maintenance_cost_fit_exception_test.cpp](../code_specs/files/tests/unit/maintenance_cost_fit_exception_test.cpp.md) | 24 |

[Paper context](../code_review.md) stays separate from local engineering
contracts. [Query memory](../query_memory.md), [invariant reports](../invariant_memory.md),
[indexed storage](../indexed_storage.md), [journal framing](../journal.md),
[maintenance costs](../maintenance_cost.md) and [reoptimization](../reoptimization.md)
provide the relevant design boundaries.

## Memory and work contracts

MemoryAccount retains its controller; concrete native arrays, tuples, reports
and snapshots retain their payloads. OwnerAllocator move/swap transfers the
actual account, attribution and buffer. Copies can allocate a distinct buffer
under the same account. SupportEpoch copies duplicate transition capacity while
sharing a journal. Report/key copies deep-copy; workload pending marking copies
the report arrays. These are different ownership operations.

Tests distinguish exact accounted requests from broad heap claims. Attribution
queries scan the live allocation list and cover selected owner IDs. Buffer usage
uses capacity. Equal totals do not establish owner identity. A denial guard alone
does not assert zero attempts; explicit calls/triggered checks and source evidence
are recorded separately. Current-state, purpose-bucket and canonical comparisons
also have different scopes.

| Boundary | Concrete source contract |
| --- | --- |
| Constraint validation | Validates every physical row before enforced key/FK projection; original-account scratch and reference diagnostic order. |
| Observation | Fixed admitted trace capacity, truncation on overflow; off/counters/timed/trace request counts are fixture-specific. |
| Workload reports | Four allocations per ordinary capture; pending public capture has eight attempts and four retained blocks in this fixture. |
| Invariant reports | Complete/issue-empty public flags determine valid(); partial work or issue stops cannot report clean. |
| Indexed work | Fresh startup consumes one structural unit; nested aliases/resumed leases share the remaining five-domain allowance without refill. |
| Calibration | Persistent failures return no partial Calibration; synthetic rates and selected image fields are not measured CPU or global fit guarantees. |

The runtime inspection fixture localizes real private counter corruption, then
restores it and requires clean inspection. A matching issue among several is
different from asserting exactly one issue. Canonical/JSON exports materialize
ordinary diagnostic DTOs. Byte output caps do not cap all receiving heap work.

## Journal, recovery and performance scope

Journal codec tests compare independent hex fixtures, all strict truncations,
single-byte XOR positions and selected checksum-valid structural corruptions.
Cursor feed preserves private continuation/quota on rejection; a copied diagnostic
state cannot refill it. Decoded lvalue views borrow live owned rows. Command and
physical sequences, pending watermark substeps and torn tails stay distinct.
These codec checks do not constitute a new persistence/replay execution.

Before-side index tests separate a seven-row matching bucket from 41 unrelated
restored rows, and local full-key lookup from additional whole-query root work.
Those are selected overlay counters. The eager live-factor test intentionally
shows growing E scans at N=1/8, including empty deltas; it is a labeled baseline.
Prepared producer work, output spool consumption, real allocations and elapsed
CPU remain separate costs. Fixed transition counters do not prove constant delay.

Reoptimization tests separate private preparation, original durable Input/decision,
promotion and native plan selection. Syscall EIO/forked exits cover observed
before/after boundaries, not all instructions or host power loss. Promotion
requires checkpoint/WAL synchronization before root linking and retains the
uncertain root lock. Selected recovery admits the correct compiler/sink binding
before repairing validated tails; cached-reader barriers drain an already decoded
prefix without reading an unadmitted continuation.

The C05 bridge includes explicit selection/freshness preparation in payback;
ordinary untimed selections cannot manufacture timing evidence. Bootstrap rebuilds
share the original query account while retaining distinct runtime owner IDs.
Churn covers 64 switches/128 inputs across two backends/modes under finite budgets.
Its steady-byte comparison subtracts reported sink buffer bytes; its allocation
count remains whole-account. Low-level retirement tests do not close R2/V04.

## Required diagnostic correction

The descriptor variants loop has **12 accepted combinations**, including the
last-switch flag. Its existing success message still says six. The usage cards
record the actual loop; the [required follow-up](../../build/verification/inspection-memory-fault-tests-v38-v1/required-descriptor-diagnostic-followup-v1.json)
corrects that test diagnostic after this source-bound review is sealed, then runs
the affected strict Debug/sanitizer checks and re-reviews changed source hashes.
The opaque descriptor fixture is framing evidence, not compiler admission.

## Receiving evidence

Root reads all 3,655 target lines and relevant callers before the proposals,
then checks every seven-field card and exact source-region set, including all
20 mains. Peer amendments and root receiving amendments remain separate; the
six author/reviewer packets are immutable. Large V37 coverage/registry inputs
are pinned separately and protected without duplicate copies.

The [receiving packet](../../build/verification/inspection-memory-fault-tests-v38-v1/README.md)
contains source observations, exact field replay, native identity, completed
coverage and link checks. Generation finishes before checks. Stale/unused cards,
actual missing-region equality and local destinations/fragments are verified;
external URLs retain explicit skipped status in local link audits.

Latest seal: build/verification/human-inspection-v38-progress-v1.json; frozen
source: build/verification/human-inspection-v38-source-v1. The exact preceding
handoff is [V37 history](../handoff-history-v37-2026-11-13.md).
[V33 native acceptance](human-inspection-v33-2026-11-13.md) and V32's broader
SQL/installed receipts retain their dated attribution. No fresh full 348-test,
Clang, benchmark or release claim follows from this documentation review.
