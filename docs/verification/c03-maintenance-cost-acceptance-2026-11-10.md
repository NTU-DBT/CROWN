# C03 maintenance cost model acceptance

C03 is verified on 10 November 2026. The complete [Refactor.md](../../Refactor.md)
goal remains active:47 cards verified, A02 in progress,30 not started;78 total.
Work is uncommitted on baseline `e369a623517723b3be3ea3e9806779f3c591e7f9`.
No R1 release, publication or automatic cost-based plan selection is claimed.

## Contract and implementation

The C03 card and Section9.2 require conditional bucket/transition estimates,
calibrated event costs, full/delta demand and confidence fields, separating facts
from assumptions. Every retained candidate needs a decomposition, annotation
changes must remain separate from support, and memory needs a declared budget
or explicit normalized penalty. The [model guide](../maintenance_cost.md)
describes the public `CROWN::ranking_runtime` API.

Profiles capture actual PhysicalRuntime, DeltaRuntime or QuerySession owners.
Native re-lowering verifies the candidate's physical binding. Conditional counts
use complete selected-input strata, including no-ops; event multisets and sums
of actually touched bucket sizes preserve repeated transitions. The source
census remains separate from sampled detail. Estimates retain their as-of
stamp/mode, immutable profiles and copied demand. Missing profiles and unavailable
strata remain explicit; no model score grants plan proof or selection authority.

The22 components separate base/index/adapters, derivation/survivor/count/presence
transitions, lookup/touched buckets, generalized hits, annotation, full/delta
startup/rows/termination, encoded bytes and checkpoints. Reduced uint64 rational
score arithmetic checks overflow and configured bit/work limits. Fitting uses
approximate floating arithmetic only to infer quantized rational coefficients;
unrepresentable or exhausted attempts return no partial result.

Isolated timing ratios retain measured units/time. Joint nonnegative linear fits
retain raw observations, fixed coordinate order, options, numerical rank and
quantized residuals, labeled `fitted_linear_assumption`. Unobserved features stay
unavailable. Correlated real features are underdetermined, not individually
identified costs. Full/delta/encoding/checkpoint/annotation demand is caller
assumption. Account current/peak bytes are observations; `future_memory_unknown`
stays true and byte budgets are not added to nanoseconds.

## Selected native acceptance

All31 selected tests pass in each configuration: eight C03, four ranking/memory
and19 existing CLI/package regressions. All266 predecessor generated commands
and properties are preserved after source/build path normalization. There are
274 registered tests; this matrix does not claim full274 release acceptance.
Earlier runtime implementations and tests are unchanged from the
[O08 checkpoint](o08-workflow-acceptance-2026-11-10.md).

| Configuration | Selected tests passed | Test wall time |
| --- | --- | --- |
| GCC13 Debug |31/31|61.55s|
| GCC13 Release |31/31|18.60s|
| Clang18 Debug |31/31|42.78s|
| GCC13 ASan+UBSan with leak detection |31/31|226.14s|
| Fresh source-only GCC13 Release |31/31|18.45s|

All compiled CROWN units use C++23 and the existing strict warning/error flags.
Unit checks remain enabled with `-UNDEBUG`. All274 sanitizer registrations retain
ASan leak/halt and UBSan halt/stacktrace settings. Parser archive instrumentation
and ASan/UBSan symbols are checked too. Test-only saturation/census executables
link both testing archives without mixing in production runtime/bridge ABIs.

## Independent numerical and lifecycle evidence

Literal skew-trace tests check nine touched records from seven physical events,
maintenance131, full6, delta21, encoding64, checkpoint129 and annotation55,
total406; variable full-row demand changes the total to407. Three retained
checked candidates receive terms or an explicit missing profile. Annotation
demand changes its own group without changing support-event work.

Both storage backends check a four-input/two-change census: selected changing
inputs predict60, complete detail36, and selected no-ops12. Denominators include
the selected no-ops. Tests cover unseen delete strata, truncation, disabled or
pending collection, stale/binding/backend/mode mismatches and zero demand.
Actual existing test-ABI saturation injection prevents complete forecasts and
timing features; this does not claim to execute UINT64_MAX events.

Per configuration, persistent allocation sweeps cover212 reference and216
indexed capture positions and16 estimate positions on each backend, plus four
fitting and three isolated-calibration allocations. Full independent images of
earlier profiles/results, candidate/evidence/source/workload/current rows and
account usage survive failures; retry succeeds. A new successful capture's
memory observation is checked at its own call, not against a previous call's
cumulative statistics. Lowering/binding/arithmetic/work limits remain enforced.

Independent synthetic fit fixtures check exact5/2/7 rates, collinear rank
deficiency, zero-duration observed features and unavailable columns. Five real
SQL/oracle cases contain34 physical events, including self-joins, projections,
Boolean/disconnected cases and native scalar coverage. Raw phase counters,
final rows, closed report schemas, coefficient provenance, exact score sums and
quantized fit residuals are independently reproduced. Initial preserved datasets
contain15 reports/612 phase observations across three compiler controls.

The runnable SQL-only calibration example measures disjoint input/native
prepare/commit, committed-spool reading and full snapshot materialization.
Statistics capture, fitting, reporting and returned snapshot destruction are
outside the clocks; input is in memory, O07 is off, and there is no WAL or sink.
A moved installation builds the copied public example outside the source/build
tree and runs all five cases using production headers/libraries only. Existing
CLI/package tests retain259 CLI checks and18 outside-consumer commands.

## Provenance and review

Evidence lives under `build/verification/`, prefix `c03-final-native-`:

- `inputs-v1.json` freezes1155 tested source/input/document paths. The fresh
  source tree contains exactly these paths and no old objects or CMake cache.
  `inputs-v2.json` adds this record and changes status documentation only.
- `matrix-audit-v1.json` binds1285 actual artifacts:800 C++ objects,60 selected
  native ELFs,90 CROWN archives, five parser archives,300 flags/link files and
  30 build metadata files. Each mode builds15 production plus reference/runtime
  testing/ranking-runtime testing archives. Test-only archives are not installed.
- Configure/build/CTest receipts retain commands, timestamps, exits and log
  hashes; CTest raw stdout is archived before later enumeration. All13 matrix
  phase jobs and five driver handles closed successfully, observed by root.
  No build overlapped CTest in the same directory.
- `requirement-audit-v2.json` and `root-review-v1.json` accept all eight reviewed
  requirements. Root implemented/reviewed the model; Luna Max supplied bounded
  independent fixtures and failure-test proposals. No Astra agent was used.
- `upstream-warning-review-v1.json` checks all native/development build logs
  against previously reviewed pinned vendor C/Make diagnostics. Vendor files
  match the pinned archive. PostgreSQL namestrcpy's bounded copy is immediately
  followed by its final NUL write. No project C++ warning or weakened policy
  was accepted. An auxiliary review check was corrected to use its actual
  NameStr macro spelling; production source was unchanged.
- Git provenance, documentation preimages, final progress, checkpoint seal and
  post-seal audit bind the final handoff. Historical development failures and
  corrections remain in their original receipts, including a schema-harness
  optional-import correction and the capture-memory image boundary correction.
  Assertions, caps and timeouts remain intact.

## Limits and remaining work

This interpretable model predicts work under declared demand and calibration
context. Five real fixtures have numerical rank6–9 across15–17 observed features;
the reported calibration residuals do not establish causal attribution, held-out
accuracy or optimal cost-based selection. The collector records its compiler
context, without introspecting runtime archive flags; keep the native build
manifest alongside reports. No affinity/cache controls or discarded warm-up
phase make this a controlled performance experiment.

C05 richer-policy integration, C07 held-out quality and B-stage experiments remain
separate. Native account bytes do not bound process RSS or predict future state.
A02 license disposition, other Refactor cards and full V-stage release gates
remain open. The full goal remains active.
