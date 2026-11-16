# V40 — remaining selected test usage specifications

V40 adds **257 block usage cards across 49 test files**, including all 47 mains.
Completed generation checks the actual formerly missing path/block set. Every
selected callable, inline cluster and type now has a scoped usage card, including
all 5,461 selected test regions. All 1,196 native inputs and 355 production paths
remain byte-identical to V39; this review adds no runtime handler, wrapper,
allocation, work checkpoint or native execution.

The [source index](../code_specs/README.md) now has **16,609 contracts in 14,193
blocks**, mapping 751 files /172,040 lines /19,412 blocks. The other **5,219 blocks**
retain structural facts and linked context. Zero selected gaps does not certify
every retained comment or make those structural blocks individually reviewed
semantic specifications. The [structural audit](../../build/verification/inspection-remaining-tests-v40-v1/structural-scope-audit-v1/report.md) separates 725 declaration/control blocks and 104 alias/using clusters for further review. The broader Refactor goal remains active: **57 verified /
1 in progress A02 /20 not started**, 78 total. W06 retains its bounded profile;
A02 still blocks C04/B01, and R2 retirement, V04 and release gates remain open.

Each card gives purpose, inputs/outputs, invariants, ownership, failure, cost and
concrete references. [Paper context](../code_review.md) distinguishes theorem
scope from local engineering contracts. A parsed document, copied DTO, signature,
or diagnostic record does not grant typed proof or execution authority.

| Source | New cards |
| --- | ---: |
| [admission_test.cpp](../code_specs/files/tests/unit/admission_test.cpp.md) | 11 |
| [annotation_admission_test.cpp](../code_specs/files/tests/unit/annotation_admission_test.cpp.md) | 3 |
| [binding_test.cpp](../code_specs/files/tests/unit/binding_test.cpp.md) | 9 |
| [catalog_test.cpp](../code_specs/files/tests/unit/catalog_test.cpp.md) | 9 |
| [layout_test.cpp](../code_specs/files/tests/unit/layout_test.cpp.md) | 8 |
| [parser_test.cpp](../code_specs/files/tests/unit/parser_test.cpp.md) | 7 |
| [physical_backend_plan_test.cpp](../code_specs/files/tests/unit/physical_backend_plan_test.cpp.md) | 11 |
| [scalar_test.cpp](../code_specs/files/tests/unit/scalar_test.cpp.md) | 7 |
| [schema_test.cpp](../code_specs/files/tests/unit/schema_test.cpp.md) | 13 |
| [semantics_test.cpp](../code_specs/files/tests/unit/semantics_test.cpp.md) | 9 |
| [candidate_set.hpp](../code_specs/files/tests/reference/candidate_set.hpp.md) | 4 |
| [residual_oracle.cpp](../code_specs/files/tests/reference/residual_oracle.cpp.md) | 12 |
| [annotation_oracle_driver.cpp](../code_specs/files/tests/unit/annotation_oracle_driver.cpp.md) | 3 |
| [annotation_policy_test.cpp](../code_specs/files/tests/unit/annotation_policy_test.cpp.md) | 7 |
| [compiler_plan_artifact_test.cpp](../code_specs/files/tests/unit/compiler_plan_artifact_test.cpp.md) | 3 |
| [exact_oracle_test.cpp](../code_specs/files/tests/unit/exact_oracle_test.cpp.md) | 8 |
| [planner_certificate_codec_test.cpp](../code_specs/files/tests/unit/planner_certificate_codec_test.cpp.md) | 4 |
| [recognition_test.cpp](../code_specs/files/tests/unit/recognition_test.cpp.md) | 6 |
| [residual_io_test.cpp](../code_specs/files/tests/unit/residual_io_test.cpp.md) | 11 |
| [tree_verifier_test.cpp](../code_specs/files/tests/unit/tree_verifier_test.cpp.md) | 12 |
| [weighted_bag_oracle_driver.cpp](../code_specs/files/tests/unit/weighted_bag_oracle_driver.cpp.md) | 5 |
| [weighted_bag_test.cpp](../code_specs/files/tests/unit/weighted_bag_test.cpp.md) | 9 |
| [weighted_oracle_driver.cpp](../code_specs/files/tests/unit/weighted_oracle_driver.cpp.md) | 4 |
| [maintenance_cost_fit_test.cpp](../code_specs/files/tests/unit/maintenance_cost_fit_test.cpp.md) | 3 |
| [maintenance_cost_statistics_test.cpp](../code_specs/files/tests/unit/maintenance_cost_statistics_test.cpp.md) | 7 |
| [maintenance_cost_test.cpp](../code_specs/files/tests/unit/maintenance_cost_test.cpp.md) | 5 |
| [ranking_binding_test.cpp](../code_specs/files/tests/unit/ranking_binding_test.cpp.md) | 4 |
| [ranking_census_test.cpp](../code_specs/files/tests/unit/ranking_census_test.cpp.md) | 3 |
| [ranking_contract_test.cpp](../code_specs/files/tests/unit/ranking_contract_test.cpp.md) | 1 |
| [ranking_empty_test.cpp](../code_specs/files/tests/unit/ranking_empty_test.cpp.md) | 1 |
| [ranking_normalized_exception_test.cpp](../code_specs/files/tests/unit/ranking_normalized_exception_test.cpp.md) | 1 |
| [ranking_payload_time_test.cpp](../code_specs/files/tests/unit/ranking_payload_time_test.cpp.md) | 4 |
| [ranking_pure_link_test.cpp](../code_specs/files/tests/unit/ranking_pure_link_test.cpp.md) | 1 |
| [report_memory_schema_test.cpp](../code_specs/files/tests/unit/report_memory_schema_test.cpp.md) | 2 |
| [selection_backend_binding_test.cpp](../code_specs/files/tests/unit/selection_backend_binding_test.cpp.md) | 4 |
| [selection_binding_test.cpp](../code_specs/files/tests/unit/selection_binding_test.cpp.md) | 6 |
| [selection_cache_independent_test.cpp](../code_specs/files/tests/unit/selection_cache_independent_test.cpp.md) | 8 |
| [selection_cache_test.cpp](../code_specs/files/tests/unit/selection_cache_test.cpp.md) | 4 |
| [selection_census_test.cpp](../code_specs/files/tests/unit/selection_census_test.cpp.md) | 1 |
| [selection_contract_test.cpp](../code_specs/files/tests/unit/selection_contract_test.cpp.md) | 1 |
| [selection_current_test.cpp](../code_specs/files/tests/unit/selection_current_test.cpp.md) | 1 |
| [selection_exception_test.cpp](../code_specs/files/tests/unit/selection_exception_test.cpp.md) | 1 |
| [selection_indexed_owner_test.cpp](../code_specs/files/tests/unit/selection_indexed_owner_test.cpp.md) | 6 |
| [selection_normalized_exception_test.cpp](../code_specs/files/tests/unit/selection_normalized_exception_test.cpp.md) | 1 |
| [selection_public_independent_test.cpp](../code_specs/files/tests/unit/selection_public_independent_test.cpp.md) | 8 |
| [selection_pure_link_test.cpp](../code_specs/files/tests/unit/selection_pure_link_test.cpp.md) | 1 |
| [selection_resources_independent_test.cpp](../code_specs/files/tests/unit/selection_resources_independent_test.cpp.md) | 4 |
| [selection_resources_test.cpp](../code_specs/files/tests/unit/selection_resources_test.cpp.md) | 3 |
| [selection_source_test.cpp](../code_specs/files/tests/unit/selection_source_test.cpp.md) | 1 |

## Source and performance findings

Frontend tests distinguish parser syntax, bound SQL, grounded normalization,
structural admission and native lowering. Occurrence identity, physical source
identity, repeated output slots and scalar types stay explicit. Layout context
values and runtime layout tokens have different compatibility checks. Catalog
metadata can roundtrip while core nullability/collation remains unsupported;
untrusted keys, statistics and hints cannot replace mutable input witnesses.

Reference oracles deliberately use expensive ordinary test containers and
exhaustive enumeration. Exact-oracle fixture labels are remapped through a dense
ID map; the separate tree-verifier fixture requires dense input labels. Frozen
residual layers freeze ears/anchor conditions per round, and terminal maps retain
ordered aliases, literals and contradiction. Trace/candidate reports remain
separate from verified original-query minimum or infeasibility. The residual
executable performs in-process search before emitting schema-labeled records;
a separate Python driver validates schemas and authority mutations.

Weighted test transports serialize counts as decimal strings and structural
node IDs as JSON numbers. Record child multiplicities are not node IDs. Snapshot
intermediates retain account-funded arrays while JSON/maps are ordinary exports.
Per-update versus process-level parser failures differ between drivers. Bag
comparison checks distinct emitted rows and exact multiplicities; ordinary set
comparison can collapse duplicates if insertion success is ignored.

Selection separates current-owner freshness from immutable as-of evidence.
Cache hits can reuse a compiled artifact while retaining fresh proof and capture
context. Raw tree order/names, request limits and source tags remain bound. FIFO
hits do not promote; read-only misses do not insert; failed capacity/counter
publication preserves cache state. Modeled payload/slot values differ from
allocator usage and CPU cost. Synthetic calibration/rates and biased sampled
forecasts carry their explicit assumptions; zero observed detail is not the same
as zero declared demand. Logical work, active time and carried preparation have
separate histories and no universal preemption guarantee.

## Review and verification scope

Three Luna Max authors and three separate Luna Max peers cover all seven fields
of all 257 cards. Root independently reads all 49 target files /6,160 lines:
39 files /4,627 lines before proposals, then the 10 frontend files after peer
amendments. Root checks complex oracle, ownership/resource and selected final
field claims directly. Exact field replay covers 155 peer
amendments plus 6 root receiving amendments. Source
geometry, every anchor, hashes, actual region sets and all 47 mains are checked.
No Astra Max agent is used in this batch.

The [receiving packet](../../build/verification/inspection-remaining-tests-v40-v1/README.md)
pins large V39 coverage and registry directly, preserves the six immutable
packets, checks completed generation and records local links with external URLs
explicitly skipped by local audits. No native build, CTest, SDK, benchmark or
release run occurs here. [V39](human-inspection-v39-2026-11-13.md) retains its
actual affected Debug/SAN descriptor execution; earlier broader receipts retain
their own dated attribution.

## Required diagnostic follow-up

The backend-binding test varies fourteen option fields for both source tags,
producing 32 cold insertions and 32 exact hits. Only row and structural-step
limits start above 2^53. Its existing success banner suggests all fourteen are
wide-valued. The [recorded follow-up](../../build/verification/inspection-remaining-tests-v40-v1/required-backend-binding-diagnostic-followup-v1.json)
corrects that wording in a fresh native packet after V40 is sealed, re-reviews
four affected cards and runs the strict affected Debug/ASan/UBSan/leak gates.

Latest seal: build/verification/human-inspection-v40-progress-v1.json; frozen
source: build/verification/human-inspection-v40-source-v1. Exact prior handoff:
[V39 history](../handoff-history-v39-2026-11-14.md). Keep the structural usage
scope and full Refactor requirements open after the narrow native correction.
