# AntiGravity / coding-agent handoff

Updated 12 November 2026. Full [Refactor.md](../Refactor.md) implementation remains
active and uncommitted at `e369a623517723b3be3ea3e9806779f3c591e7f9`.
The [ledger](task_ledger.md) is **54 verified, 2 in progress (A02, W04), 22 not
started; 78 total**. C02/C05 are reverified after the nonempty constant-route repair.
No release acceptance is claimed.

## Verified checkpoint: constant-route repair and program inspection

Read [the repair record](verification/constant-route-repair-2026-11-12.md),
[source index](code_specs/README.md) and [primitive cards](code_specs/primitives.md).
The confirmed old defect, sealed negative probe, independent design and all prior
artifacts remain unchanged. New regression inputs retain real nonempty bodies
and original structural h1/h2; do not replace them with easy empty-body cases.

Native replan freezes canonical empty operator tree/report only after exact
candidate/source and retained identity/SQL credit admission. Initial DirectCQ
lowering and compiled-input binding use the same admitted-query-derived geometry.
Depth is exact 0/W with actual table weights; slots zero still require full
source/lowering/identity/payload/model admission. Candidate tree, positive body
minimum, original proof/key/provenance and cache family remain separate and
unchanged. Public lower_tree still rejects nonempty supplied false-route trees.
PlanExplanation describes operator zero; QueryExplanation retains body height.

Five primitives change in four production files. No production try/catch/throw
sites, persistent recovery state or wrapper framework are added. Borrowed
lvalue geometry avoids ordinary-tree copies; empty operator branches skip unused
node/population scratch while retaining real source and metadata costs. No speedup
or allocator-byte claim follows from zero slots.

Root integrates 268 new contracts (238 program, 19 test, 11 CMake) and rechecks
122 existing planner cards, semantically rewriting four. There are 2,431 cards
in 2,063 mapped blocks across 665 files, 153,655 lines and 17,087 blocks. All 508
selected production blocks in 21 assigned files have cards; 3,358 other selected
production blocks plus broader tests/tools remain. The 141 substantive program
regions include 126 selected kinds and 15 other declaration regions. Six concise
comment occurrences in four native files
preserve executable tokens. Paper proof refs and local engineering costs remain
distinct; structural maps are not completed individual semantic reviews.

Final strict Debug and ASan/UBSan/leak builds pass on 1,102 identical stable inputs.
All 14 selected tests pass per profile: 147.91 s Debug and 550.58 s sanitizer.
Raw LastTest.log files are archived. New fault calibration cohorts per profile:
CQ/SQL native reference 42/45, indexed 43/46; depth/slot cache replacement
reference 192/174, indexed 195/177. Do not sum them into a global unique fault count.
Exact/one-under receiver/work and retained producer credits, source/account
ownership, old results/cache state, pending/stale/released owners, SQL rows/EXISTS,
full artifact/compiler replay and ordinary/empty controls pass.
The first new test's SQL double-mapping error and exact failed source remain
preserved; corrected SQL cursor assertions pass. All 314 predecessor test
definitions remain with only constant_routes appended (315 total). Actual linked
inventory: 60 artifacts and 276 C++ objects (30/138 per profile), vendor C excluded.
All 36,807 spec links pass. No full 315-test, Release, Clang or timing comparison
is claimed.

Final receipts: `constant-route-build-final-*-v1` and
`constant-route-ctest-final-*-v1`. Acceptance/progress:
`build/verification/constant-route-acceptance-v1.json` and
`build/verification/constant-route-progress-v1.json`. Frozen source:
`build/constant-route-source-v1`. All recorded jobs are terminal; one historical
failed test is retained with its correction, while all final gates pass.
Never mutate sealed source/build/evidence or rerun CTest there; use new versions.
Before-images preserve 2,453 v7 paths; 110 prior artifacts still match. Raw program,
human-spec,code-review and earlier Astra design packets remain unchanged.

## Active W04 work

The constant-route checkpoint above is sealed; current W04 work starts from
`build/verification/w04-start-v1/progress.json`. Its before-images preserve all
2,457 checkpoint source paths and all 160 evidence artifacts. W04 design and
implementation are in progress; aggregate acceptance remains incomplete.

Implement W04 COUNT/SUM/AVG using `build/verification/w04-inventory-v1/handoff.md`:
aggregate binder rules, group state, sufficient statistics, change events,
global-empty behavior and independent SQL-oracle cases. Arithmetic kernels alone
do not complete W04. W05 general bag/NULL/type admission and W06 aggregate
transactions/recovery remain separate. Keep the full 78-card objective active.

Continue individual human inspection. Raw v8 physical/AVL 330-contract packet is
staged at `build/verification/inspection-v8-physical-v1`; recheck current inputs
before integration. Do not silently bless stale program/ranking/selection hashes.
Use current-model reviewers for substantive work and Luna Max for bounded simple
work; reduce Astra Max. Root owns implementation and final native verification.
A02 license disposition remains pending; do not repeatedly ask while independent
work remains. Later implementation/experiments and external theorem/release gates
are open.

Previous handoff: [handoff-history-v7-2026-11-12.md](handoff-history-v7-2026-11-12.md),
byte-identical v7 archive with the complete preceding evidence chain.
