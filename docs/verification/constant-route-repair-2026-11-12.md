# Constant-false route repair and human inspection

C02/C05 are reverified for the confirmed nonempty contradiction regression.
The full 78-card Refactor.md goal remains active: 54 verified, A02 in progress,
23 not started. This packet supplies scoped regression and documentation
acceptance; it does not claim a full 315-test, Release, Clang or release review.

## Trigger and authority

The [sealed counterexample](constant-route-regression-2026-11-11.md) retains
body `R(x)`, head `x` and `contradiction=true`. Original structural search
produces a checked height-one candidate. Public P08 lowering with an explicit
empty tree produces an empty constant-false operator at height zero. The old
native replan combined that route with the original one-node tree/report;
export succeeded and physical replay rejected `invalid_plan`.

The repair keeps these separate:

| Record | Meaning after repair |
| --- | --- |
| P07 candidate, selected key, snapshot and original proof | Original retained body and its positive structural minimum; unchanged. |
| Compiled tree/report | Canonical empty executable operator, valid report, height/depth zero and empty arrays. |
| Compiled source and options | Original complete Catalog/Query, normalized SQL when present, output contract, producer credits and backend. |
| Depth score | Empty occurrence depths, actual physical table weights, zero contributions and exact `0/W` with eligible positive W. |
| Slot score | Exact zero after evidence, source, lowering, identity, payload and modeled-plan admission. |
| Artifact cache key | Original family, checked heights, raw candidate trees, selected full key, source/request/evidence context. |
| Explanations | PlanExplanation reports checked constant operator zero; incompatible original candidate/proof/family attachments are rejected. QueryExplanation retains original body height. |

[Candidate authority](../candidate_alternatives.md#original-proof-and-checked-alternatives)
and [paper provenance](../code_review.md) ground the structural proof. Canonical
artifact bytes, score proxies, allocation accounting and exception cleanup are
local engineering contracts, not new paper theorems.

## Direct implementation and cost

Five primitives change in four production files. `NativeLowering::compile`
substitutes the empty tree/report only for a nonempty contradiction, after exact
source/candidate and retained producer-credit admission. `lower_winner` chooses
that explicit input for initial DirectCQ compilation. `compiled_binding`
derives expected operator geometry from the admitted query. `depth_score`
models that empty geometry while retaining actual W. `memory_score` formats zero
only after normal admission and retention of the canonical modeled program.

The public lowerer still rejects a nonempty caller-supplied false-route tree.
Ordinary trees and existing empty-body optional raw claims retain their prior
branches. Named lvalues selected through const references avoid an ordinary
candidate-tree copy. No production catch, throw site, recovery framework,
persistent state or helper layer was added. Empty operator selection allocates
no heap payload by itself; source encoding, native construction, metadata,
result/source layouts, accounting and teardown still have real costs. Slot
modeling skips unused population scratch; depth still walks table weights.
Zero slots do not establish zero bytes or a speedup.

Read [routes](../physical_plans.md#admission-and-routes),
[score reconstruction](../ranking.md#exact-score-reconstruction),
[compiled and cache binding](../selection_binding.md#physical-source-and-artifact-frames)
and [memory boundaries](../query_memory.md#boundaries). The
[exact implemented diff](../../build/verification/constant-route-fix-v1/implemented.diff)
and [final source audit](../../build/verification/constant-route-final-source-audit-v1.json)
identify semantic changes separately from comment-only changes.

## Native verification

Fresh strict C++23 Debug and ASan/UBSan/leak builds and their 14 selected tests
pass on the same 1,102 stable code/build/test inputs. Every built maintained C++
object has Wall/Wextra/Wpedantic/Wconversion/Wsign-conversion/Werror; sanitizer
objects also have address/undefined instrumentation. The actual inventory is
60 linked artifacts and 276 C++ objects, 30/138 per profile; vendor C is excluded.

| Final profile | Selected tests | Wall time | Receipt and raw CTest log |
| --- | ---: | ---: | --- |
| Debug | 14/14 | 147.91 s | [receipt](../../build/verification/constant-route-ctest-final-debug-v1.json), [raw log](../../build/verification/constant-route-ctest-final-debug-v1.LastTest.log) |
| ASan/UBSan/leaks | 14/14 | 550.58 s | [receipt](../../build/verification/constant-route-ctest-final-sanitizer-v1.json), [raw log](../../build/verification/constant-route-ctest-final-sanitizer-v1.LastTest.log) |

These are correctness runs, not comparable performance measurements. The suite
covers physical_lowering, physical_api, native_program, native_replanning,
ranking_binding, ranking_integer_independent, ranking_public_independent,
ranking_result_memory, selection_public_independent,
selection_binding_independent, selection_cache_independent,
selection_resources_independent, selection_result_memory and constant_routes.

The [new test](../../tests/unit/constant_route_test.cpp) requires nonempty
unary/multi-candidate bodies at h1/h2, real bind/normalize SQL row and EXISTS
queries, both storage backends, full artifact equality with the unchanged public
lowerer, physical/compiler replay, tampering rejection, original proof/key/
provenance preservation, whole-family tie order and cold/read-only cache reuse.
Literal duplicate/absent/unused-table traffic fixes W=4 independently of scoring.
Current-owner checks cover disabled/empty census, explicit fallback, stale
no-op input, private Delta state and released sessions. Ordinary and empty-body
artifacts remain explicit compatibility controls.

Every observed native and selection allocation position is denied and retried,
including a success sentinel. Receiver funding, source lifetime, old result and
cache publication are checked. Exact/one-under receiver and lowering limits,
identity credits, SQL replay/normalization credits and aggregate processing/
lowering limits remain enforced. Calibration positions per profile are:

| Backend | Native CQ | Native normalized SQL | Depth/cache replacement | Slot/cache replacement |
| --- | ---: | ---: | ---: | ---: |
| Reference | 42 | 45 | 192 | 174 |
| Indexed | 43 | 46 | 195 | 177 |

These are separate calibration cohorts, not globally unique allocation faults.
Receiving-account peaks, including the controller, are 8,521 requested bytes
for CQ and 8,338 for normalized SQL, with
physical work 13 and 16 respectively in these small fixtures; these are not
runtime memory or general complexity bounds.

The first new Debug run exposed a test-oracle mistake: PhysicalRuntime results
already use the SQL view, so remapping EXISTS again turns its false row into
true. The corrected test asserts SQL cursor rows directly. The
[failed receipt](../../build/verification/constant-route-ctest-debug-v1.json),
[exact failed source](../../build/verification/constant-route-fix-v1/test-before-oracle-correction.cpp)
and [correction](../../build/verification/constant-route-fix-v1/test-oracle-correction.json)
remain preserved; this was not a production failure.

## Human inspection and preserved evidence

Three independent current-model static reviews cover the implementation,
program contracts and planner/test contracts. One earlier focused Astra Max
design review is preserved; no additional Astra review was used here.
The [program review](../../build/verification/constant-route-program-contracts-v1/review.md)
adds 238 individually re-reviewed contracts; 114 cards correct raw semantic
fields and 124 retain their fields after review. The
[planner/test review](../../build/verification/constant-route-human-specs-v1/review.md)
rewrites four affected planner cards, preserves 118 after same-block token
checks, and adds 19 test plus 11 CMake cards. Root applied six concise comment
occurrences across four native files, with identical executable tokens for
those comment edits. The raw proposals remain unchanged.

The [source index](../code_specs/README.md) now has 2,431 contracts in 2,063
mapped blocks: 665 files, 153,655 lines and 17,087 blocks. All 508 selected
production blocks in the 21 assigned files have cards. The program review's
141 substantive blocks include 126 selected callable/type/inline-cluster
blocks plus 15 other declaration regions. There remain 3,358 selected production
blocks (696 include, 2,605 src, 57 apps), plus broader tests/tools. Line maps are
structural partitions; they are not a claim of individual semantic review.
The offline checker passes 36,807 local links, current hashes and partitions.

The [registration audit](../../build/verification/constant-route-registration-v1/result.json)
preserves all 314 predecessor emitted test names/commands/properties after
same-profile build-path substitution. Only constant_routes is appended, with
900-second timeout, C02/C05 labels and required sanitizer environment. Removing
the exact added CMake block reproduces the preimage. No test was weakened or
removed. All 2,453 prior source paths are preserved in before-images and all 110
v7 artifacts, including the sealed negative probe/design, retain exact hashes.

Final acceptance/source closure is recorded in
`build/verification/constant-route-acceptance-v1.json` and
`build/verification/constant-route-progress-v1.json`; the frozen source is
`build/constant-route-source-v1`. Never rebuild or retest sealed build directories.
Use new paths for later work. Raw v8 physical/AVL review remains staged separately.
W04 is next; W05/W06, A02 licensing, later experiments and release gates remain open.
