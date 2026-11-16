# V35 — selection, ranking and planner usage specifications

This continuation adds **181 source-bound usage cards** in seven test files.
All **1,196 native inputs**, including **355 production paths**, are byte-identical
to V34. The engine acquires no wrapper, exception handler, allocation, traversal
or work checkpoint from this documentation change. There are no new native
builds, CTests, SDK tests, timing runs or benchmark claims.

The full Refactor.md goal remains active: **57 verified / 1 in progress (A02) /
20 not started**, 78 total. W06 keeps its documented bounded verified profile;
A02 still blocks C04/B01. R2 retirement, V04 and release gates remain open.

## Human inspection coverage

The [source index](../code_specs/README.md) maps 751 files /
172,040 lines / 19,412 blocks, with 15,778
scoped contracts in 13,362 blocks. Every maintained line has a
structural location. All selected non-test regions have usage cards;
**831 selected test regions remain**. Other unreviewed scaffolding retains
structural facts only. Mapping and card presence do not certify all semantics
or all comments.

| Source | New cards | Inspected usage |
| --- | ---: | --- |
| [Selection publication faults](../code_specs/files/tests/unit/selection_publication_fault_independent_test.cpp.md) | 31 | Sampled replacement-new failures, cache publication, retained selections and owner invariants. |
| [Selection result memory](../code_specs/files/tests/unit/selection_result_memory_test.cpp.md) | 22 | Original-account storage, 288 lifetime combinations, persistent faults, finite caps and admission. |
| [Ranking result memory](../code_specs/files/tests/unit/ranking_result_memory_test.cpp.md) | 19 | Shared result/candidate handles, account allocators, lifecycle availability and operation-grant refusals. |
| [Public independent ranking](../code_specs/files/tests/unit/ranking_public_independent_test.cpp.md) | 28 | Literal geometry, workload scores, alias/base routing, modeled slots, freshness and payload limits. |
| [Independent integers](../code_specs/files/tests/unit/ranking_integer_independent_test.cpp.md) | 18 | Separate decimal oracle, 512-bit limits, exact work/byte boundaries and alias transactionality. |
| [Candidate provider](../code_specs/files/tests/unit/candidates_test.cpp.md) | 34 | Exact-seed authority, finite complete reference families, keys, residual/cache provenance and bounded continuation. |
| [Planner fast paths](../code_specs/files/tests/unit/planner_fast_paths_test.cpp.md) | 29 | Hierarchy/component paths, exact fallback, dynamic widths, certificate mutation and explicit resource stops. |

Every card gives purpose, inputs/outputs, invariants, ownership, failure, cost
and source/design references. [Paper context](../code_review.md) remains distinct
from local allocator, SQL, output, rollback and persistence obligations. No test
helper or numeric score is promoted to proof authority.

## Independent review and corrections

Three Luna Max agents author and cross-review bounded packets; root performs
the complex receiving review and independently reads all seven target files,
relevant fixtures and implementation callers. No Astra is used. Exact recursive
path/hash/byte checks preserve all three author and three reviewer packets.
Root compares the actual missing-selected-region set from frozen V34 with the
actual source anchors: all 181 intended regions match, including entrypoints,
without substituting scaffolding aliases. Patch arrays are replayed against
original fields before the merged cards enter the maintained registry.

The accepted cards distinguish these source behaviors:

- Publication faults use at most eleven distinct sampled positions; they do not
  sweep every allocation. That test checks owner/workload/cache/proof facts but
  does not directly snapshot query-account current bytes. Measurement scopes rely
  on nonnested use; their type has no nesting/copy guard.
- Selection's persistent helper reconstructs fixtures and makes 2N+2 target
  selections; ranking retains one fixture and makes 2N+3 ranks including baseline
  and calibration. These counts exclude owner/cache setup calls. Cap helpers
  make D+2*pins+3 explicit calls. The 288 selection lifetime cases do not imply
  every fault/cap profile covers every cache mode; all selection caps bypass cache.
- Score allocator equality checks account binding. Equal current-byte totals
  for result/modeled-plan handles do not prove owner-ID equality. Immutable
  candidate handles pin payloads; account-funded score text/vectors are separate.
- Native indexed admission uses one aggregate grant with five dimensions. Its
  two rejection profiles make six refused runtime constructions, not six successful
  initializations. Only the first profile separately asserts source-account totals.
- Ranking height-only skips live evidence capture; valid current-selection
  height-only still captures and checks its owner boundary. Availability fallback
  does not hide binding or resource failures. Pure historical evidence stays as-of.
- Candidate completeness compares the normal-form reference family UNION the
  admitted original exact witness, which can be non-normal. Cached alternatives
  preserve residual provenance while attaching the new provider's original proof.
  Two 1,000-work grants on mandatory/wide fixtures are bounded continuation checks,
  not completed family enumeration. Logical work/slot metrics do not measure CPU,
  all copying, allocator overhead or RSS.
- The independent integer corpus has 54 unique decimal strings and 2,916 ordered
  pairs. Its set order is lexical, and printed boundaries=16 means the sixteen
  32-bit checkpoints. Driver operand construction uses production UInt operations;
  expected arithmetic uses separate decimal addition/shift/division. Exact-work
  helpers invoke the operation three times. Default limits are finite.
- Diagnostics passed as const std::string& can be constructed even on success.
  Tree fingerprints need valid finite acyclic trees; query incidence predicates
  instead need valid IDs and allow cyclic incidence. Outer std::exception catches
  do not catch every thrown type. A failed JSON dump can allocate before rejection.

Root corrects additional source descriptions: a void comparator returns no
CandidateRun, cancellation/clear differs from owner destruction, six compared
progress fields do not cover every diagnostic, certificate mutation has two
positive cases, and the budget group makes five planner calls including its
healthy certificate-producing search. The ties/binding group makes four ranking
attempts, including the final moved-from handle rejection omitted by the peer.
Root's initial query-predicate wording
incorrectly required acyclicity; the receiving amendment removes that condition.
The private receiver also normalizes the actual author schema differences.
These documentation/checker corrections are retained with reasons; they are
not native test failures.

## Validation and continuation

The [receiving packet](../../build/verification/inspection-selection-tests-v35-v1/README.md)
contains original hashes, independent source notes, replayed amendments, exact
region comparison, native-input identity, regenerated coverage and link checks.
Generation finishes before checks. There are no stale or unused contracts;
generated local links and current guide destinations/fragments pass. External
URLs are skipped by the guide checker, not asserted freshly reachable.

The boundary is `build/verification/human-inspection-v35-progress-v1.json`, with
frozen source `build/verification/human-inspection-v35-source-v1`. The exact
previous handoff is [V34 history](../handoff-history-v34-2026-11-13.md). Completed
packets and snapshots remain immutable; later amendments require fresh paths.

[V33 native acceptance](human-inspection-v33-2026-11-13.md) retains its actual
Debug/SAN interruption matrix, testing-OFF Release and 229-file moved-SDK identity.
V32's broader SQL/installed-test receipts retain their dated attribution. Source
identity does not turn those into V35 executions. No whole-current 348-test-suite,
fresh Clang, host power-loss, CPU or release claim follows. Continue individual
usage review and the original open implementation/release tasks.
