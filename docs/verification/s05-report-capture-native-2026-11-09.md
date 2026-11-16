# S05 native retained trace, gauges and report controls — 9 November 2026

Status: **in progress**. Ledger41 verified /3 in progress /34 not started; full
78-card Refactor.md goal stays active. Artifacts: `build/verification/s05-report-capture-native-*`.

## Implemented ownership and focused proof

Root implements `s05-report-capture-native-*`; one Luna Max agent performed
read-only caller/remaining-owner census. No Astra used. Previous goal turn was
verified progress. CapturedObservationTrace/trace arrays, CapturedStateGauges
node/base arrays and CombinedCapture/ModeDescriptor/PlanExplanation/
StatisticsExplanation real object/shared controls now use the original query
account (capture:3/4/5/6/7/8). SessionStatisticsContext already uses capture:0 and
now retains native trace/combined children. Runtime wrappers propagate native
captures directly; no ordinary trace/gauge export mirror sits in the retained
query/report path. Existing public ObservationTrace/CommittedStateGauges exports
remain caller DTOs. Compile-only PhysicalPlan reports use an explicit standalone
component account; admitted CompiledProgram reports keep their existing grant.

Production source1 is unchanged through source3. Source2 adds/registers the new
actual memory test; source3 fixes only its loop formatting under unchanged strict
warnings-as-errors. Tested source3 freezes953 paths; final source4 changes documentation only (954). All11 original focused observation/
trace/gauge/combined/report/session/owner checks PASS source1 in7.66s. New actual
report memory test PASS source3 in0.72s, both backends:7 runtime capture families
and all12 live/pending/stopped/dropped session report/context families, exact real
request reconciliation, original-account retained controls/arrays, no-allocation
shared handle copies, native value copies, retained lifetime/controller-only final
release, exact/one-under query caps after hoarding genuine snapshots, same-cap
retry after release and every persistent allocation position. Native trace/gauge
cross-query assignments adopt source allocation and preserve old metadata/arrays
on failure. Gauge JSON matches the independent caller DTO export.

Runtime persistent fault counts: mode1, trace1, gauges2, compile-only native plan2,
combined59/61, plan5, statistics63/65 (reference/indexed). Runtime fixture peaks
440414..750049 reference /448151..757276 indexed and session statistics peaks
579842..828943 /586251..836655 bytes are Debug fixture values, not universal
bounds. Dropped-session cap tests retain83/84 genuine reports before the next
frontier. One old helper has2 exact type/export-range boundary substitutions;
all other bytes/reference assertions/models are preserved. Raw new-test formatting
failure/candidate/source2 are retained. No warning, flag, timeout, schema, frozen
verifier, test assertion or existing export interface is weakened.


The native runtime APIs are capture_observation_trace and capture_state_gauges;
retained report getters expose CapturedTraceRecords/CapturedStateGauges. Existing
ObservationTrace/CommittedStateGauges and text/JSON exports remain caller DTOs.
Gauge serialization uses the same algorithm for either read interface. Shared
report-handle copies allocate nothing; native trace/gauge value copies allocate
their one/two real arrays under the source account. Transactional assignment
preserves old metadata/arrays if either source request is denied. The retained
query path never materializes an ordinary trace/gauge export first. Mode/plan/
statistics factories take their existing account before moving payload handles.

C01-enabled statistics contexts still avoid the legacy gauge scan. Legacy v2
captures still reject enabled C01 collection. Pending sessions expose no committed
private gauges; stopped sessions retain readable runtime state; dropped sessions
have no fresh trace records/runtime gauges. Capture reads do not advance/drain,
commit, alter sampling or sample optional clocks. Supplied immutable proof/family/
benchmark aliases remain separate from query-created copied payload. Unsupported
legacy total-memory fields remain unavailable. Query allocation and encoded
byte/item caps have distinct meanings.

## Broad verification and provenance

Full source3 Debug build4 and CTest3 pass217/217 in907.06s. All81 selected
cases across73 actual native executables pass Release16.10s,
Clang18 97.42s and ASan+UBSan/leaks530.04s, including query
and CLI explanation outputs against frozen v2/v3 schemas/verifiers. Accepted
builds have zero compiler diagnostics. Complete detailed stdout, binary hashes
and source maps bind each scope. All recorded jobs are closed. These are
incremental scopes; full native/compiler/sanitizer/fresh-source acceptance remains
separately open. Source1 production is unchanged through tested source3 (953
paths); final source4 changes documentation only (954), with handoff independently
sealed. One old helper has only2 exact type/export-range substitutions; whole-file
reconstruction preserves every other byte/model/assertion. CMake adds only the
new actual memory test. Raw new-test strict-loop-formatting failure is preserved;
no warning, flag, timeout, old assertion, compiler limit, schema or verifier changed.

The actual memory test measures upstream new calls against successful original-
account requests and reconciles every retained control/array by attribution. Caller
requests/fixture inputs are prepared outside measured capture. Real engine updates
populate trace/gauge/workload data. It covers7 runtime families and12 session
family/phase combinations per backend, exact native handle/value copy requests,
retained readability after query release and controller-only final cleanup. Every
persistent allocation frontier preserves the old capture and accepted/pending
state, then retries the same input under the same grant. Native value cross-query
assignment preserves both accounts on failure and adopts the source on success.

Caps hoard fresh real captures until the next capture exceeds the actual earlier
query/setup peak; copying shared handles cannot substitute for that real storage.
Exact and one-byte-under caps have opposite outcomes. Releasing one held capture
permits retry under the unchanged allowance. Debug values below describe this
fixture, not universal limits. Pins and failures are reference/indexed respectively.

| Runtime boundary | Query peak bytes reference / indexed | Retained pins | Persistent failure positions |
| --- | ---: | ---: | ---: |
| ModeDescriptor | 440414 / 448336 | 31 / 32 | 1 / 1 |
| Native trace | 441454 / 448681 | 15 / 15 | 1 / 1 |
| Native gauges | 440574 / 448151 | 63 / 64 | 2 / 2 |
| Native compiled-program report | 441974 / 449201 | 3 / 3 | 2 / 2 |
| CombinedCapture | 734633 / 741860 | 1 / 1 | 59 / 61 |
| PlanExplanation | 441439 / 448666 | 2 / 2 | 5 / 5 |
| StatisticsExplanation | 750049 / 757276 | 1 / 1 | 63 / 65 |

| Session statistics phase | Query peak bytes reference / indexed | Retained pins |
| --- | ---: | ---: |
| Live | 764625 / 771852 | 1 / 1 |
| Pending | 828943 / 836655 | 1 / 1 |
| Stopped | 764162 / 771389 | 1 / 1 |
| Dropped | 579842 / 586251 | 83 / 84 |

## Remaining whole-goal scope

Runtime ranking EvidenceData/RuntimeEvidence controls, binding/weight/source
storage and runtime CurrentSelection/planner result graphs remain ordinary.
Supplied compiler/cache state is a distinct ownership boundary. Actual session,
input, pending/output and snapshot owners already have native evidence. Inspect
remaining diagnostic/work scratch separately from explicit canonical/invariant
caller snapshots. Authentic operator record/byte reconciliation and complete
overflow/no-op/churn/compiler/sanitizer/fresh-source native matrices remain open.
The focused next-owner inventory is not exhaustive acceptance. S05/whole-query
memory and full native acceptance remain false. See [handoff](../handoff.md),
[ledger](../task_ledger.md), [memory accounts](../memory_accounts.md),
[observability](../observability.md) and [statistics](../statistics.md).
