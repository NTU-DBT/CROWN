# V39 — descriptor diagnostic correction

The [descriptor test](../../tests/unit/reoptimization_descriptor_test.cpp#L90)
now reports **twelve optional-field combinations**. Its existing loop covers
four no-sink and eight sink combinations, including last_switch_epoch. The
single source edit replaces six with twelve in the success string. It adds no
branch, counter, wrapper, handler or production work.

The required follow-up recorded by [V38](human-inspection-v38-2026-11-13.md)
is complete. V38 and its six author/reviewer packets remain immutable. Root
re-read all 92 descriptor source lines and all seven fields of its eight usage
cards. Two stale-message descriptions changed; all eight whole-file review
hashes were refreshed after that reading. Anchors and source geometry stay equal.

| Affected gate | Actual result |
| --- | --- |
| Strict Debug target build | PASS, C++23, warnings as errors and assertions enabled |
| Debug reoptimization_descriptor | 1/1 PASS; output reports twelve |
| ASan/UBSan target build | PASS with the same strict flags |
| ASan/UBSan reoptimization_descriptor | 1/1 PASS; leak detection, halt and stacktrace enabled |

Each command is recorded with all 1,196 native inputs and zero changes during
execution. Exactly one test source differs from V38; all other 1,195 inputs,
including all 355 production paths, remain byte-identical. Pre-run LastTest and
configuration/flags are archived; post-run logs and flags are pinned. No full
348-test run, Clang, SDK, CPU benchmark or release execution is claimed.

The [source index](../code_specs/README.md) retains **16,352 contracts in 13,936
blocks**, across 751 files /172,040 lines /19,412 blocks. Completed generation
preserves the exact remaining set of **257 selected test regions in 49 files**;
all selected non-test regions have cards. Other scaffolding retains structural
facts. Maps have no stale or unused cards; generated local links pass. The current
guide audit checks local destinations/fragments and explicitly skips external
URLs. Numeric source references keep the same line positions.

The [receiving packet](../../build/verification/inspection-descriptor-diagnostic-v39-v1/README.md)
contains exact source/card deltas, four recorder receipts, archived test logs,
completed coverage and link checks. The descriptor golden remains opaque codec
framing evidence; compiler semantic admission is separate. Guard-versus-counter,
source/target ownership and cost qualifications from V38 remain in force.

Latest seal: build/verification/human-inspection-v39-progress-v1.json; frozen
source: build/verification/human-inspection-v39-source-v1. Exact prior handoff:
[V38 history](../handoff-history-v38-2026-11-13.md).

The full goal remains active: **57 verified /1 in progress A02 /20 not started**.
W06 retains its bounded profile. Continue the 257 test usage regions; A02 still
blocks C04/B01, and R2 history retirement, V04 and release gates remain open.
