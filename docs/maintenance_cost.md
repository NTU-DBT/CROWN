# Maintenance cost model (C03)

The opt-in `CROWN::ranking_runtime` library exposes
`crown/runtime/maintenance_cost.hpp`. It captures actual candidate-bound
workload profiles and produces a decomposed rational estimate for every retained
minimum-height candidate. C03 is verified against its stated acceptance criteria;
see the [acceptance record](verification/c03-maintenance-cost-acceptance-2026-11-10.md).
The model is not enabled as an automatic C05 selection policy.

## Inputs and authority

`cost::capture(snapshot, candidate_index, owner)` accepts a PhysicalRuntime,
DeltaRuntime or QuerySession. It captures native statistics and re-lowers the
checked candidate against the actual owner's admitted source. The resulting
physical binding must match the owner's plan; statistics from another tree
cannot silently price it. The account is recorded before profiling allocations.
Profiles retain immutable observations, with no query rows or mutable runtime
pointers exported.

Profiles in one estimate share source, semantic and output bindings.
`cost::revalidate(profile, owner)` reports owner/sequence/interval/mode freshness
reasons. Estimates are **as-of** forecasts; advancing an owner does not make an
older profile current. Results retain profiles, calibration and copied demand.
No cost optimum or future performance proof follows.

The caller supplies future input counts by physical table and insertion/deletion
for a declared horizon, listing every table/operation, including zero demand.
C01 observes counts rather than arrivals per second. Full-snapshot requests and
rows, delta epochs/rows, encoded bytes, checkpoint requests/bytes and annotation
changes are separate assumptions. `snapshot_rows_total` supports varying result
sizes; when absent the model uses requests times rows per request.

## Conditional work and decomposition

Each initiating table/operation and signed child-edge descriptor uses its
complete sampled-input denominator. The model scales the **number of actual
events** and **sum of actually touched bucket sizes**, preserving repeated events
and zero-sized buckets. It never substitutes a uniform average over static keys.

Terms separate physical input/change, adapter visits, derivation changes,
survivor transitions, parent and visible count updates/presence transitions,
edge lookups, native bucket touches and generalized hits. Annotation changes
never become support events. Full/delta startup, rows and termination, encoding
and checkpoint components remain separate from maintenance.

Each term records its descriptor, expected units, estimated nanoseconds,
observed event count, sample denominator, availability and basis. Sample status
and size are not statistical confidence intervals. Saturation, truncation,
disabled collection, missing profiles, unsampled strata, absent coefficients
and incompatible modes remain explicit unknowns. They cannot manufacture a
complete zero-cost estimate. `cost::features` accepts only exact, committed,
full-detail physical counters as timing features; sampled, truncated, saturated,
private and logical-only intervals are rejected.

## Calibration measurements and assumptions

`cost::calibrate` fits summed isolated measured time divided by summed units for
each component, retaining sample counts and totals. These are caller-supplied
measurements with an explicit environment/layout/backend/instrumentation label.
The factory does not certify measurement quality or disjoint scopes.

`cost::fit` instead consumes whole-phase timings and observed feature vectors.
It uses zero-initialized, fixed-order nonnegative coordinate descent on normalized
columns, with a declared ridge penalty and convergence/rank tolerances. This
step uses approximate IEEE floating arithmetic. Published rates are quantized
exact fractions; estimate arithmetic remains reduced, checked 64-bit rational
arithmetic. Unrepresentable intermediates or exhausted work/iteration/allocation
budgets stop the attempt without a partial Calibration or Result.

Fitted attributions are tagged `fitted_linear_assumption`. Raw vectors/timings,
options, sample counts, numerical rank and errors after quantization are retained.
The numerical rank is a tolerance-dependent diagnostic, not an exact rank proof.
Correlated features can have many equally good rate assignments; an inferred zero
rate does not prove a free operation. Unobserved columns remain unavailable.
Explicit mode bindings prevent a fitted delta-owner context from silently
pricing a physical-only maintenance owner.

The five current real replay fixtures have numerical rank 6–9 across 15–17
observed features. Their individual event rates are therefore not all identified.
The reports expose that fact. Calibration-data residuals are reproducible;
held-out C03 event-cost prediction quality remains unverified. The verified
[C07 depth/slot baseline](ranking_evaluation.md) explicitly excludes this event-cost
model. No causal or statistical confidence claim follows from matching calibration
data. The [independent C03 argument](../build/verification/v02-cost-model-review-v1/report.md)
separates exact forecast arithmetic from approximate fitting and future accuracy.

## Runnable SQL-only measurement example

Build the diagnostic example with the source tree:

```sh
cmake --build BUILD --target crown_cost_calibrate
BUILD/crown_cost_calibrate query.sql catalog.json updates.jsonl 64 3 3 > calibration.json
```

Arguments after the input file are event limit (1–256), repetitions (1–5) and
retained candidate limit (1–8); defaults are 64, 3 and 3. Input uses the same
catalog-bound ordered JSONL format and preparation helper as the [CLI](cli.md).
The example uses an empty initial state and proved-height tree candidates.
Constant-empty operators and traces with no physical inputs have no calibration
workload here. A retained candidate prefix does not claim family exhaustion.

The example records separate clocks for input decoding/native preparation/commit,
reading committed output spools, and materializing full committed snapshots.
Statistics capture, fitting, JSON reporting and returned snapshot destruction are
outside these intervals. Workload counters are enabled, O07 observation is off,
input is buffered in memory, and there is no WAL or sink. Encoding, checkpoint
and annotation coefficients stay unavailable because those operations are not
measured. Their future demand needs separate calibrated inputs.

The version1 report contains raw phase records, query/input hashes, physical
binding, actual backend/modes, collector compiler/language/pointer information,
kernel/machine, repetition counts, coefficients, fit diagnostics and exact
replay-horizon estimates. Its closed transport definition is
[cost-calibration-v1.schema.json](../schemas/cost-calibration-v1.schema.json).
Reports grant no plan, acknowledgment or retirement authority.

Keep build manifests with calibration data: compiler fields describe the
collector, and runtime archive flags are not introspected by this example.
There is no CPU affinity, cache control or discarded warm-up phase. This is
measured model calibration with recorded limitations, not a controlled benchmark
or a performance qualification. Compare contexts before reusing coefficients.

The package installs the source example at `share/crown/examples/cost-calibration`.
Copy it, configure with `-DCMAKE_PREFIX_PATH=PREFIX`, then build
`crown_cost_calibrate`. It inherits C++23 and links installed production APIs
only. A moved-prefix outside build runs all five SQL/oracle cases in the test.

## Memory and verification

A declared byte budget is a separate constraint. Account current/peak bytes at
capture are observations; passing a current-state check does not predict future
peak memory. `future_memory_unknown` stays true. Bytes are never added to time.
Native runtime accounts independently enforce actual allocation admission.

New profiles use their owner's original account; coefficient/result arrays and
text use the explicit receiving account. Retained handles keep their original
accounted storage. No process/RSS guarantee follows. Existing processing work,
binding, payload, lowering and arithmetic ceilings apply.

Eight C03 tests pass in GCC Debug/Release, Clang18 Debug, ASan+UBSan/leaks Debug
and a clean source-only Release build. They cover independent literal fits,
conditional-work arithmetic, all three owner types, normalized SQL/self-joins,
real full/delta timing reports, closed schemas and moved installed APIs.
Persistent allocation failure sweeps cover all four fitting and three isolated
calibration allocations, preserve earlier results/account usage and allow retry.
The five SQL fixtures reproduce exact score arithmetic and quantized residuals
from their raw records.

Both reference and indexed storage pass statistics coverage, including
an exact-census/no-op trace with sampled forecasts60/12 versus complete-detail36,
explicit unknown delete strata, truncation, pending-state rejection, backend
mismatch and injected test-ABI saturation. The saturation check is a boundary
injection, not a claim to execute UINT64_MAX events. Persistent capture/result
failure sweeps cover428/32 allocation positions in GCC Debug, keep older records
immutable and restore account/current/runtime/workload state. Four existing
ranking/census/memory tests also pass after linking the testing bridge.

The selected31-test matrix passes in all five configurations: eight C03 tests,
four existing ranking/memory tests and19 CLI/package regressions. All266 prior
test definitions and existing runtime implementations/tests are preserved;
274 tests are registered. The final audit binds1155 tested source paths and1285
actual build artifacts and reviews eight requirements. This selected matrix is
separate from the full274-test release gate.
C03 `maintenance_cost` selection through C05 remains unsupported; held-out
evaluation of this C03 event-cost model and full release gates remain open.
C07's verified depth/slot baseline has its separate scope. The full Refactor.md
goal remains active.
