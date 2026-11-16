# Human inspection continuation V28 — 2026-11-13

The [source map](../code_specs/README.md) now contains **14,497 scoped usage
contracts** within 12,111 reviewed blocks, across **723 code files,
167,259 lines and 18,865 mapped blocks**. This pass adds 557
contracts across 63 existing test/reference/example files. All selected
production, example and tool regions have cards; **1,666 selected existing-test
regions remain**. Structural line coverage and field presence are not a complete
semantic specification or correctness proof. The inspection remains in progress.

## Concrete changes

The pass reviews all scoped comments and authors individual purpose, input/output,
invariant, ownership/lifetime, failure, cost and local-reference fields. It adds:

| Scope | Files | Contracts | Review boundary |
| --- | ---: | ---: | --- |
| Arena/reference/indexed storage tests | 19 | 261 | Luna authored; root checked critical hook/lifetime/work/ownership/fault cases and all mechanical identities |
| Python verification/generators/oracles and C++ usage examples | 33 | 213 | Initial generic batch rejected; normal-model reviewer individually rewrote every card; root checked challenging examples and complete mechanical identities |
| Legacy journal/generation file tests | 5 | 52 | Root authored; normal-model reviewer checked every card and source, resolving six findings across five cards |
| Materializing reference engine and adapters | 6 | 31 | Root source/model/export/search review and mechanical coverage checks; no separate semantic reviewer |

Seven test/helper files change through **15 exact wording substitutions**: seven
comment blocks and eight diagnostic/output string literals. The C++ token streams
are identical except for those eight enumerated literals; the Python AST,
including constants/docstrings, is identical. All 1,167 previous native input
paths are checked; production source is unchanged. No branch, statement, owner,
allocator path, catch, runtime field or system design is added or removed.

Comments distinguish narrow scalar/array replacement-new hooks from the S04
hook that also replaces aligned/nothrow overloads. A one-shot failure helper
does not count attempts and cannot prove zero allocation if a callback catches
its injected failure. Legacy reference inputs borrow, while native program/view
adapters produce owning exports. The schema test constructs equivalent CQs but
gets baseline result rows through the CROWN oracle CLI. Accurate existing
comments remain intact; rewriting them adds no inspection value.

## Quality and assertion boundaries

The original Python packet has useful exact sources and a comment census, but
188 invariants and 172 ownership fields were generic templates. Root adopted
none of it. A fresh immutable amendment preserves all 213 original objects and
supplies 213 substantive replacements. It fixes actual result types, sharing
versus deep copying, subprocess/SQL/file costs, arbitrary-precision arithmetic,
exponential reference joins, direct fixture-write failure and exact assertions.
The C02 ranking example has no mandatory slot constraint; that belongs to the
separate selection example. Presence of an Attempt still requires inspecting
its result/stop. Repeated field text remains only where the operations themselves
are equivalent, such as fixed-width packers. Uniqueness statistics do not certify
the prose.

The independent 52-card review narrows six claims: enable recovery has separate
zero-state branches; hooks borrow their registration context; requested
open-after errors are remapped by the test wrapper; registration cost counts
setter calls; EIO sweeps and special controls assert different subsets; successful
tail checks compare lengths rather than every preserved byte. The actual factory
retains its stronger validation-before-repair obligation.

Root also corrects storage construction costs and index adoption of a returned
raw key pointer. Fresh storage amendment1 makes the journal retry's revision
normalization explicit: prepared cursors check the saved prefix revision, while
the final Image comparison overwrites actual.revision with the successful
baseline. It does not prove equal raw revisions across aborted trials. The
completed author packet stays unchanged.

The [reference evaluator](../../tests/reference/evaluator.cpp) deliberately
copies a complete candidate database and materializes answers. The
[delta model](../../tests/reference/delta_model.cpp) computes full subtree joins
and top-down live semijoins under an explicit downward-totality precondition.
The [literal tree oracle](../../tests/reference/tree_oracle.cpp) shares P02
validation and exhausts the locally proved normal-form family. Those expensive
reference operations do not add work to native updates or import P1/P2 runtime
bounds. See [semantics](../semantics.md), [delta contracts](../delta_runtime.md)
and [normal-form proof](../planner_proofs.md#complete-normal-form-family-p03).

## Verification and handoff

Root independently verifies complete recursive payloads, V27 preimages/current
captures, exact original-card projections, all required fields, 557 scoped
anchors/regions, 2,378 local reference occurrences and global key uniqueness.
Existing 13,940 records and master order remain unchanged. The generated checker
passes **111,246 local links**; the separate fixed
52-guide audit checks current local destinations/fragments. Source links and
line bounds aid inspection; they do not establish semantic relevance by themselves.

No native executable, test, build, configure, install or fixture generator ran
for this reversible wording/documentation pass. Existing native acceptance stays
bound to immutable [V27 sources](human-inspection-v27-2026-11-13.md): strict Debug
8/8, full ASan/UBSan/leak 8/8, OFF Release and relocated 224-file SDK checkpoint
acceptance. The current production code is unchanged. No new timing, allocation,
full-suite, Clang or actual R2 durability claim follows.

The root packet is `build/verification/existing-tests-inspection-v28-implementation-v1`.
Review/card packets and fresh amendments have exact digests in its
`review-seal-pins.json`; rejected/failed packaging evidence is retained. All
completed packets are immutable. The V28 seal is
`build/verification/human-inspection-v28-progress-v1.json`, with frozen source
`build/verification/human-inspection-v28-source-v1`.

The [handoff](../handoff.md) preserves the next work. The full goal remains active;
ledger **56 verified / 2 in progress (A02/W06) / 20 not started**. A02 blocks
C04/B01. Actual R2 WAL/sink ownership, coordinator/replay, nullable ingress/CLI,
varying-int32 admission, the remaining individual test review and full release
reviews remain open.
