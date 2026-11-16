# AntiGravity / coding-agent handoff

Updated 11 November 2026. Full [Refactor.md](../Refactor.md) implementation remains
active, uncommitted at `e369a623517723b3be3ea3e9806779f3c591e7f9`. The [ledger](task_ledger.md)
is **52 verified, 3 in progress (A02, C02, C05), 23 not started; 78 total**.
C02/C05 were reopened from a confirmed counterexample; do not mark them verified
from the passing inspection tests. No release acceptance is claimed.

## Verified scoped checkpoint: human inspection v7

The user requests individually authored primitive/block usage specs, clear
comments/references, direct code, necessary exception boundaries and low runtime
overhead. Use current-model reviewers for substantial work, Luna Max for bounded
simple work; reduce Astra Max. One focused Astra Max design audit was used for
the confirmed cross-component constant-route defect; root owns implementation.

V7 integrates 485 new contracts: lowering 115, selection 218 and ranking 152. There
are 2,163 cards in 1,893 mapped blocks across 664 files, 153,203 lines and 17,048 blocks.
All 382 selected production blocks in 18 assigned files have cards; 3,484 selected
production gaps plus broader tests/tools remain. Structural maps are not complete
individual semantic review. Source/API/cost/ownership/failure fields are scoped
to unique anchored code with current hashes and narrow design references.

Root applied 155 comments in 17 native files: all executable tokens unchanged.
Selection uses 114 of 218 proposals, keeping trivial getter/equality specs external;
the remaining comments explain ownership, accounting, source binding and private
publication. No helper/state/catch/throw/operation/interface/test change. One
selection-accounting table correction describes existing InlineDecimal stack
rendering, preserving logical 41-unit and encoded-byte debits.

The ranking audit read all 152 cards and all 706 lines. Root applied 82 field corrections
across 46 cards plus one comment into derived files; preserve raw material. Costs now
distinguish per-primitive noexcept/failure behavior, metadata length debits from
actual scans/worklists, and reused producer credits from rerun compilation.
Copy-like Evidence/Result/Selection moves preserve source validity; assignment
can tear down large prior payloads. Slot proxies are not allocator bytes.

Fresh strict Debug and ASan/UBSan/leak builds pass on 1,101 identical stable inputs.
All 13 selected tests pass each profile in 84.12 s and 313.99 s. Both raw LastTest.log
files are archived. Separate fault cohorts per profile: construction 697,
replan 1,816, admission copies 2,876, ranking memory 4,798 and selection memory 4,779.
No globally unique summed count is claimed. Inventory: 54 maintained linked
artifacts and 258 actual C++ objects; vendor C excluded. 35,758 spec links, current hashes
and partitions pass. All 314 same-profile registrations/commands/properties and
CMake/install/tools remain unchanged. No full 314-test, Release or speedup claim.

Read [the verification record](verification/human-inspection-v7-2026-11-11.md),
[source index](code_specs/README.md) and [primitive cards](code_specs/primitives.md).
Final native receipts are `inspection-v7-build-final-*-v1` and
`inspection-v7-ctest-final-*-v1`. Acceptance/source closure:
`build/verification/inspection-v7-acceptance-v1.json` and
`build/verification/inspection-v7-progress-v1.json`; frozen source:
`build/inspection-v7-source-v1`. All recorded v7 jobs are terminal.
Never rebuild/rerun CTest/mutate sealed source or evidence; use new paths.
V6 before-images: `inspection-v7-preimages-v1` (2,450 paths); 92 prior artifacts intact.
Derived ranking: `inspection-v7-root-ranking-final-v1`; raw/audit/corrections and
integration packet remain preserved. Build/verification names are local paths.

## Next: repair the confirmed constant-route regression

Read [the regression record](verification/constant-route-regression-2026-11-11.md)
and `build/verification/constant-route-design-v1/{review.md,fix-test-outline.md}`.
The probe in `inspection-v8-constant-route-probe-v1` linked sealed v6 libraries:
one-atom contradiction yields original structural candidate h=1, but native false
operator retains tree 1/report 1 and no runtime nodes. Physical replay rejects
invalid_plan; empty-body control roundtrips. Existing tests miss this case.

Coordinate four sites: native replan operator tree/report, DirectCQ winner input,
compiled expected-tree binding, and both ranking models. Prefer substitution
only for nonempty contradiction to preserve old empty-body claims/hashes. Keep
original selected tree/height/proof/binding/cache context intact. Operator h=0 is
not original minimum h=0. Depth reports 0/W with actual weights; slots 0 still require
evidence, modeled-plan lowering, identity and payload admission. Keep public
lower_tree rejecting nonempty supplied false-route trees. Avoid ternaries mixing
temporary trees with candidate lvalue references (they can deep-copy trees).
PlanExplanation uses evidence-free checked_constant_operator; positive original
body proof stays in Selection/QueryExplanation and must not attach to operator h=0.

Run the outlined direct/normalized, reference/indexed, multi-candidate, cache,
roundtrip, resource/fault/receiving-account and ordinary/empty compatibility tests.
Preserve v7 before-images first. Raw read-only v8 program (238 cards) and physical/AVL
reviews are staged separately; the bug fix will require rechecking affected
program cards/hashes before integrating. They are outside v7acceptance.

Then implement W04 COUNT/SUM/AVG from `w04-inventory-v1/handoff.md`; W05/W06 remain
distinct. Do not replace SQL binder/group/null/global-empty/oracle requirements
with arithmetic kernels alone. Licensing, later implementation/experiments and
external theorem/release gates remain open. Preserve the full 78-card goal.

Previous handoff: [handoff-history-v6-2026-11-11.md](handoff-history-v6-2026-11-11.md),
byte-identical archive linking the complete earlier evidence chain.
