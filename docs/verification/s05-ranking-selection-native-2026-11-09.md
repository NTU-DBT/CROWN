# S05 native ranking and selection ownership checkpoint

9 November 2026. Incremental work toward S05; the complete Refactor.md goal stays
active. Ledger:41 verified,3 in progress (A02/S05/O06),34 not started,78 total.
Whole-query memory and full native/fresh-source acceptance remain false.

## Result and boundaries

CandidateScore/Result controls, text, reproduction-term arrays and modeled programs
now use the receiving query account (capture:11). Native replanning reads checked
candidate validation and admitted source/identity fields, with funded graph,
layout/projection controls, bindings and scratch. It retains the canonical source
owner rather than chains of older physical graphs. Deep native program admission
copies the complete source/token graph into a receiving runtime account.

Selection source/request text, assessment/decision arrays, controls and cache
keys/nodes use capture:12; CurrentSelection uses capture:13. Each FIFO node keeps
the query account that allocated it. Publication/clear/final native release
allocate nothing, and chain cleanup is iterative. A hit can alias an already
funded immutable artifact from another query; fresh result/capture storage still
uses the receiving account. Failed calls preserve the owner epoch, older results
and cache contents/order/counters.

Native runtime/session factories share one new query account and one indexed
operation allowance across program admission, initialization and live bootstrap.
Compiler metadata work is separate from the configured execution update limit;
creating a compiler artifact cannot bypass later execution admission. Native
candidate lowering retains finite logical lowering/identity/replay/normalization
admissions. Pure DirectCQ without evidence remains the initial pre-execution
compiler API. Supplied immutable compiler/proof/family/cache values and explicit
PhysicalPlan/JSON/source/request exports remain caller boundaries.

Selected plans and modeled plans are CompiledProgram values. Native result arrays
and text retain their original allocators even when empty or held in SBO. Public
runtime/session factories accept those artifacts. Frozen wire formats, score
values, structural proof requirements, policies, fallback behavior and logical
slot-versus-byte distinctions remain intact.

## Verification scope

| Checked code | Mode and scope | Result | Seconds |
| --- | --- | --- | ---: |
| source22 | Full Debug registration |221/221 PASS |876.17 |
| source22 | Selected Release |111/111 PASS |22.06 |
| source22 | Selected Clang18 Debug |111/111 PASS |104.41 |
| source22 | Selected ASan+UBSan/leaks |111/111 PASS |570.61 |
| source24 | Final selection/admission Debug regression |17/17 PASS |56.58 |
| source24 | Final selection/admission Release regression |17/17 PASS |6.44 |
| source24 | Final selection/admission Clang18 regression |17/17 PASS |42.44 |
| source24 | Final selection/admission ASan+UBSan/leaks regression |17/17 PASS |193.39 |

Source23 adds a reproducer without production changes. Source24 adds only two
empty-native-handle preconditions: standalone compiler input rejects before
creating a component account, and current/as-of input rejects before capture.
Valid paths add no allocation or logical charge. The four17-case final regressions
include the complete actual-memory selection test and old valid selection,
binding/cache/resource/publication/backend consumers. They supplement the broad
source22 runs; the broad runs are not presented as reruns on source24. The added
admission alias gives222 registered cases and112 selected names across103 native
targets; it reuses the existing selection memory executable. Final source25
changes documentation only from24 and freezes964 paths.

The new native compiler comparison checks full physical JSON, instructions,
validation/identity/normalized images, work/hash values and layout/projection
alias matrices against original lowering, including SQL DISTINCT/EXISTS and rich
scalar/metadata cases. It checks both backends, all persistent allocation faults,
exact/one-under query caps, same-cap release/retry, independent source closure,
controller-only final release and30 replacements without a history chain.

Actual ranking results reconcile every new request with the original account
across Physical/Delta/Session, ready/pending/stopped/dropped states and disabled
collection. Persistent positions span30–699. Actual selection covers all three
source kinds, three owner kinds, primary/dual assessments, cache bypass/disabled/
miss/hit/eviction, pending/stopped/dropped boundaries, no-allocation admission and
held results. Persistent positions are322/396/805/853 reference and328/401/813/861
indexed. Both tests exercise real hoarded-result exact/one-under caps, same-cap
release/retry and controller-only final release. A calibrated allowance that pays
only outer startup and native admission proves initialization cannot refill it.

These are correctness/resource checks, not performance benchmarks. All accepted
builds retain strict warnings; no timeout, assertion, fixture value or reference
encoder was weakened. Fourteen existing test files have exact type/allocator/
caller-export or direct integer-construction adapters, audited separately from
the new tests. Tools, schemas, vendored code and frozen reference encoders are
unchanged from the sealed predecessor.

## Preserved history and receipts

The predecessor is the sealed
[runtime evidence checkpoint](s05-ranking-evidence-native-2026-11-09.md).
All956 predecessor source files and the old handoff have957 verified preimages.
Root implements and verifies the change; small Luna Max tasks supplied explicit
caller exports and exact old-test adapters. No Astra was used.

All60 job records are closed. Raw failures, all source maps and executed helpers
remain in build/verification. This includes the first stale-predecessor freezer,
prototype compilation failures, new SQL-fixture quoting failure, intermediate
standalone admission errors, exact native test adapters, compiler/runtime work
separation, a new work-grant probe corrected for the existing outer startup step,
GCC13 temporary-variant diagnostics repaired by constructing the same alternatives
in place, and the failing empty-native-input reproducer before its guard fix.
Inventoryv1's Python-driver target mapping is an unused draft; correctedv2 binds
the broad runs andv3 records the final registration. No unaccepted helper/build
attempt is silently replaced by a later receipt.

Detailed terminal stdout is saved before further CTest runs or enumeration.
Binary inventoryv1 records the412 native executables used before the final input
guard;v2 pins the412 final native executables and four build caches. Final progress,
seal and independent readback bind source maps, preimages, actual executables,
raw receipts, adapter audits, handoff and predecessor artifacts.

Key local records are
[jobs](../../build/verification/s05-ranking-selection-native-jobs-v1.json),
[final tested inputs](../../build/verification/s05-ranking-selection-native-inputs-v24.json),
[final registration](../../build/verification/s05-ranking-selection-native-debug-inventory-v3.json),
[C02 adapters](../../build/verification/s05-ranking-selection-native-c02-test-adapters-v2.json),
[C05 adapters](../../build/verification/s05-ranking-selection-native-c05-test-adapters-v2.json),
[fixture construction repair](../../build/verification/s05-ranking-selection-native-release-fixture-repair-v1.json),
and [empty-handle repair](../../build/verification/s05-ranking-selection-native-empty-handle-repair-v1.json).

Authentic operator record/byte reconciliation, remaining diagnostic/work paths
and full native/fresh-source acceptance remain open. Continue from
[the handoff](../handoff.md); do not mark S05 or the full goal complete.
