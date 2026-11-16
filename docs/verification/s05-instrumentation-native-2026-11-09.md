# S05 native instrumentation ownership — 9 November 2026

Status: **in progress**. Ledger41 verified /3 in progress /34 not started; full
78-card Refactor.md goal remains active. Root implemented this cohort. One Luna
Max agent did read-only caller and remaining-owner census; no Astra was used.
Artifacts: `build/verification/s05-instrumentation-native-*`.

## Ownership and publication

SupportRuntime supplies its existing StorageWorkContext account to ObservationState
and inline workload State/Collector. Physical/delta/session wrappers borrow those
same states. ObservationState's real shared object/control and fixed trace buffer
use observation:0. Workload descriptor/committed/attempt/previous arrays, routing
capacity and private configure candidates use observation:1. Immutable workload
Snapshot controls and all three numeric arrays use capture:1. Its retained program
is a funded immutable alias. No replacement query allowance or accounting-only
capacity ticket is introduced. Standalone private Collector/State adapters have
an explicit component account; query execution supplies its original account.

Configuration performs throwing work before final equal-allocator swaps; failure
preserves prior options/history/epoch. Off releases working arrays. Hooks, staging,
publication, reset and cleanup do not grow arrays. Immutable snapshot handles
share native storage without allocation. Fresh capture and pending-marked copies
allocate under the original account; the public pending path funds its temporary
and retained graphs. Failed reads preserve accepted progress. Held snapshots
remain readable after runtime/session destruction and release all charged data.
Public spans/stamps/availability/sampling remain unchanged. Snapshot::memory()
still describes collector object and actual working capacity payload, including
routes; allocator framing, temporary overlap and held snapshots additionally
consume the same query cap. This does not redefine C01's logical payload model.

## Verification and provenance

Production source1 is unchanged through source4. Source2–4 add/register/correct
only the new test. Source4 freezes948 paths. Final source5 changes five documentation
paths only and freezes949. All8 unchanged focused checks pass source1 in3.83s;
the corrected new memory test passes source4 in4.12s. Full source4 Debug build5
and CTest4 pass215/215 in896.08s. Selected75 cases across67 actual native
executables pass Release16.20s, Clang18 92.94s and
ASan+UBSan/leaks528.50s. Complete detailed stdout and binary hashes
bind these scopes. Accepted builds have zero compiler diagnostics; all recorded
jobs are closed. Full native/fresh-source/compiler/sanitizer acceptance stays open.

The actual memory test covers both backends. Global allocation calls equal
successful original-account requests for observer construction, configuration,
capture and public pending capture. Observer modes retain0/1/2 blocks; working
state has5 real arrays; a fresh snapshot has4 blocks; public pending capture makes
8 allocations with4 retained. Trace capacity stays fixed under9000 attempted
records. Exact/one-under original query caps, smaller same-account trace retry,
persistent observer2/configure6/capture4/pending8 failures per applicable backend,
same-grant recovery, prior configuration/history/epoch/progress preservation,
nonallocating hooks/commit/reset/drop and retained snapshots/controller-only final
release pass. Debug measurements below are fixture values, not universal limits.

| Boundary | Reference peak bytes | Indexed peak bytes | Persistent failure positions |
| --- | ---: | ---: | ---: |
| Observation trace | 659326 | 659326 | 2 |
| Reconfigure | 8418950 | 8437811 | 6 |
| Immutable capture | 7302576 | 7321437 | 4 |
| Public pending capture/copy | 7316729 | 7335517 | 8 |

The trace object/control/buffer requests total658710 bytes; the peak also includes
its account controller. Held earlier snapshots remain live during relevant cap
checks. At a denied second-capture frontier, retained values/fixed runtime fields
are inspected; ample-budget persistent sweeps additionally compare fresh captures.
MemoryAccount's real requests still pass through global operator new, preserving
existing fault-injector coverage. Existing session:0 attribution assertions stay
unchanged. No old test, compiler limit, flag, timeout, schema or frozen verifier
changed. Exact CMake reconstruction allows only the new test registration.

Preserve raw new-test compile failure (private with_pending access) and initial
12-identical-alias canonicalization work-limit failure. The harness now exercises
the real public pending path and12 distinct source tables. The production change
was not altered to accommodate those fixture mistakes. Preimages/source maps/raw
attempts and all executed helpers remain available for review.

## Remaining work

OwnerCapture still owns ordinary components/selections/distributions/heavy-key
rows and scan scratch. ObservationTrace's explicit vector export becomes retained
inside session captures. CombinedCapture's shared control and nested owner graph,
retained report/evidence/diagnostic/async/invariant owners and authentic operator
record/byte reconciliation remain open. Cursor/configuration/summary values are
fixed data or funded aliases; do not count them as owning strings. Complete
overflow/no-op/churn/compiler/sanitizer/fresh-source native matrices remain.
The focused next-owner inventory is not exhaustive whole-goal acceptance.
See [handoff](../handoff.md), [memory contract](../memory_accounts.md),
[statistics](../statistics.md) and [ledger](../task_ledger.md).
