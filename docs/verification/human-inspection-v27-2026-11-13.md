# Human inspection continuation V27 — 2026-11-13

The [inspection map](../code_specs/README.md) now contains **13,940 contracts across 723 code files, 167,254 lines and 18,865 mapped blocks**.
Its 11,554 reviewed blocks contain scoped seven-field usage
contracts. All selected production, example and tool regions have contracts;
**2,223 selected existing-test regions remain**. Every maintained code line is
structurally mapped, but mapping is not a complete semantic specification or
correctness proof. The user-requested human inspection remains in progress.

## Actual changes

The [physical checkpoint](../sql_aggregate_checkpoint.md) is implemented and
validated through actual serialized images and genuine whole-image restoration.
It keeps original nullable rows, filtered/unused sources, C/I/progress and reader
positions. It adds no ordinary-update field or handler. Cold temporary decoded
rows overlap rebuilding live rows; codec and build grants remain separate.
The [receiving evidence](w06-r2-checkpoint-2026-11-13.md) records the full scope.

This pass adds **187 contracts**: 119 for four existing rollback/cursor test
files and 68 for the new checkpoint API/implementation/tests, the mature SQL
driver/oracle and CMake. It updates 1,400 existing keyed records: six behavior/
build contracts, three inherited aggregation section labels and one inherited
CLI anchor/context correction; the remaining 1,390 refresh source hashes after
body/command review. Existing master order is retained.

The 119 old-test contracts describe actual ordinary-global-new interception,
rollback-restored tuple IDs, retained row/cursor lifetimes and independent test
comparisons. Six source wording substitutions remove broader allocation/copy
claims. Their original/current source captures and exact substitutions are
preserved. Contract authors ran no native tests; no test result is inferred from
the presence of a card.

## Review and adoption

Root implemented the code, ran receiving gates and independently checked the
review packets. Luna Max authored contracts; a normal-model reviewer checked
the checkpoint implementation. No Astra call was used. Pre-seal review corrected
packed-buffer/index lifetimes, all four row passes, fixed schema access, shallow
Python request ownership and the exact successful/failing restore calls.

The combined-canonical check then found an inherited CLI closing anchor that
matched the new checkpoint closing block. It rejected adoption before writing.
Fresh root amendment1 moves that CLI contract to its actual delimiter and fixes
the stale prefix invariant. The completed author packet remains immutable.
Final adoption verifies 1,468 scoped anchors, all required fields, V26 originals,
current source hashes, exact old record projections, 4,789 local references
(paths, line bounds and named sections), and complete canonical key uniqueness.
Line bounds alone do not prove semantic relevance; current source anchors supply
the primary exact block location.

Root packet: `build/verification/w06-r2-checkpoint-implementation-v1`.
Review packets: `journal-cursor-tests-human-contracts-v1`,
`r2-checkpoint-human-contracts-v1`, its fresh `-amendment1`, and
`w06-r2-checkpoint-review-v1`, all beneath `build/verification`.
The generated map checker passes **108,533 local links**;
the fixed current-guide audit has its separate pinned result. Source pages link
the compact [primitive index](../code_specs/primitives.md) and actual local/paper
context without claiming native durability/allocator bounds from P1/P2.

## Verification and remaining work

Strict Debug and full ASan/UBSan/leak profiles each pass all eight selected
checkpoint/rebuild/descriptor/record/SQL tests. Each checkpoint SQL profile
performs 3,634 real serialized reconstructions. Complete OFF Release and the
relocated 224-file public SDK pass, including producer/descriptor/frame lifetime
and exact next removal. All 336 prior registrations are preserved; 339 are now
registered. The 23 native jobs are terminal (21 successful); both original
failures and their fixes remain. There is no full-339, Clang, CPU speedup or
actual durable R2 recovery claim.

The V27 seal is `build/verification/human-inspection-v27-progress-v1.json`,
with frozen source at `build/verification/human-inspection-v27-source-v1`.
The [handoff](../handoff.md) identifies the actual next owners/coordinator/replay
work. Ledger remains **56 verified / 2 in progress / 20 not started**; A02/W06
remain in progress. A02 blocks C04/B01. W06 and the full Refactor.md goal stay active.
