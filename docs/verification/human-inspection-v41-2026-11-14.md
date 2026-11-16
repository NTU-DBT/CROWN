# V41 — backend-binding diagnostic correction

The [backend-binding test](../../tests/unit/selection_backend_binding_test.cpp#L67)
now says fourteen independent one-unit limit changes **include values above
2^53**. Only per_table.rows and per_operation.structural_steps start at 2^53+1;
the other twelve limits are small distinct values. The existing loops still
exercise 32 configurations across direct and physical source tags, each with
one cold insertion and one exact warm hit. One success-message literal changes;
test logic and all 355 production paths remain unchanged.

Root re-read all 69 source lines and all seven fields of four cards. The main
invariant now identifies the two wide fields; the check_source cost counts its
three physical serializations and one parse/replay. All four whole-file review
hashes/authorship notes refresh. The main's whole-function anchor follows the
new literal. No other registry card changes, and source geometry stays equal.

| Affected gate | Actual result |
| --- | --- |
| Strict Debug target build | PASS, C++23, warnings as errors, assertions enabled |
| Debug s04_selection_backend_binding | 1/1 PASS, 0.43 seconds |
| Strict ASan/UBSan target build | PASS, same strict flags |
| ASan/UBSan s04_selection_backend_binding | 1/1 PASS, 1.74 seconds, leak detection and halt enabled |

All four recorder commands pin the same 1,196 native inputs, with zero changes
during execution. Exactly one test source differs from V40; the other 1,195 inputs
are byte-identical. Pre/post LastTest logs, configuration and target flags are
archived. These affected tests add no full-suite, Clang, SDK, benchmark or release
claim. There is no new production handler, wrapper, branch, allocation or work
checkpoint and no claimed runtime speedup.

The pre-action archive caught a target-name error in V40's follow-up instructions.
The real CMake S04 wrapper creates crown_s04_selection_backend_binding_test and
s04_selection_backend_binding. No native command ran with the mistaken name.
The [correction receipt](../../build/verification/inspection-backend-diagnostic-v41-v1/entry-target-correction-v1.json)
supersedes that spelling while preserving all V40 bytes.

The [source index](../code_specs/README.md) retains **16,609 contracts in 14,193
blocks**, mapping 751 files /172,040 lines /19,412 blocks. Completed generation
confirms zero selected callable/type/inline-cluster gaps and no stale/unused cards.
The same **5,219 structural blocks in 693 files /16,103 lines** remain without
individual semantic cards. V40's [structural audit](../../build/verification/inspection-remaining-tests-v40-v1/structural-scope-audit-v1/report.md)
prioritizes 725 declaration/control blocks plus 104 alias/using clusters; these
are triage categories, not certification of all comments or declarations.

The [receiving packet](../../build/verification/inspection-backend-diagnostic-v41-v1/README.md)
contains exact source/card deltas, source-stable native receipts and current map
and link checks. [V40](human-inspection-v40-2026-11-14.md) and its six author/peer
packets remain immutable. External URLs are explicitly skipped by local audits.

Latest seal: build/verification/human-inspection-v41-progress-v1.json; frozen
source: build/verification/human-inspection-v41-source-v1. Exact prior handoff:
[V40 history](../handoff-history-v40-2026-11-14.md).

The full Refactor goal remains active: **57 verified /1 in progress A02 /
20 not started**. W06 retains its bounded profile. A02 still blocks C04/B01;
R2 history retirement, V04 and release gates remain open.
