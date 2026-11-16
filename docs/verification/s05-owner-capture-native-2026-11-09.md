# S05 native owner capture ownership — 9 November 2026

Status: **in progress**. Ledger41 verified /3 in progress /34 not started; full
78-card Refactor.md goal stays active. Root implemented the cohort; one Luna Max
agent did read-only census. No Astra used. Artifacts: `build/verification/s05-owner-capture-native-*`.

## Real ownership and public boundaries

OwnerCapture's real component and ordered FieldId arrays, histograms, top-K buffers
and compact scalar/string/decimal key blocks consume its original CompiledProgram
account under capture:2. Native scan group list nodes and weighted builder object/
control use the same finite grant. Ordered projection gathers directly into one
AccountedRow block. Accounted controls/arrays retain no ordinary Row/string mirror
and create no new query allowance. Plan/layout handles share native immutable
metadata. Scope, cardinality, NDV, ordering, partial-budget and freshness rules
remain intact. CapturedSelection/CapturedDistribution/CapturedKey expose native
read interfaces; key views borrow their containing key. Caller OwnerRequest/
Selection and standalone table Capture/Distribution values remain explicit DTO
boundaries. Native scalar serialization preserves canonical decimal/date and binary
hex JSON without an owning Row export. The existing frozen schema stays unchanged.

Deep value copies fund every nested block under the source account. Cross-query
assignment constructs the complete replacement before moving it into the target;
any failure preserves its old stamp, facts and account. Held captures survive
runtime destruction and release all charged data. Logical C01 work/row/key/payload
limits remain distinct from actual query requests, including framing, controls,
capacity, temporary overlap and held captures. Allocation failure releases private
scratch/candidates and preserves the accepted epoch. Logical-budget exhaustion
still publishes no prefix NDV/histogram/top-K. Pending captures retain metadata
only; indexed reads acquire their existing native work grant's two lease/allowance
object/control requests. Both denial points preserve pending/accepted state.
Reference pending reads, rollback and final release allocate nothing.

## Verification and provenance

Source1's allocator factory required an explicit constructor correction, producing
production source2. Source3–7 change only new-test/registration boundaries plus one
indexed helper comparison. Source7 freezes951 paths; source8 changes documentation
only (952 paths, with handoff separately sealed). All11 original focused checks
pass source2 in7.69s. New actual owner memory and registered indexed owner/session
checks pass source7 3/3 in1.31s. Full source7 Debug build8 and CTest5 pass216/216
in908.13s. Selected78 cases across70 native executables pass
Release16.26s, Clang18 98.65s and ASan+UBSan/leaks540.16s.
Accepted builds have zero compiler diagnostics; complete detailed stdout and binary
hashes bind each scope. All recorded jobs are closed. These are incremental scoped
results; full native compiler/sanitizer/fresh-source acceptance remains open.

The new actual test exercises both backends, all5 scalars, long binary/NUL/invalid-
UTF-8 strings, repeated/reordered projections and inline38-digit decimals. Global
allocation calls reconcile with original-account successes for capture and deep
copy; retained block totals include components, fields, arrays and every compact
heavy key. Mutating the caller request does not alter retained fields. Old values
remain readable after runtime closure; final release leaves only the controller.
Stress caps retain two earlier captures before the next capture/copy. Exact and
one-byte-under limits have opposite outcomes, preserving prior state and allowance;
releasing one held capture permits the same operation to retry under the unchanged
limit. Persistent sweeps cover every capture and source-account/cross-query copy
request; failed assignment preserves both query accounts and destination facts.

| Boundary | Reference | Indexed |
| --- | ---: | ---: |
| Capture query peak bytes | 6757073 | 6776116 |
| Copy query peak bytes | 6750074 | 6768687 |
| Persistent capture failure positions | 90 | 92 |
| Persistent cross-query copy failure positions | 49 | 49 |

These Debug values describe this fixture, not universal limits. Both indexed
pending grant-control failure positions and same-source retry pass. Existing
owner exception tests additionally retain independent canonical-state/freshness
and same-owner copy-assignment checks. Three old helpers have9 exact boundary type/
range substitutions; whole-file reconstruction preserves every other byte and
all independent expected algorithms/assertions. CMake reconstruction permits only
the native source and new test registration. No flag, timeout, compiler budget,
schema or frozen verifier is weakened. The registered indexed owner and session
cases are confirmed through CMake's foreach loop and explicitly selected.

Raw allocator-constructor compile failure, new-harness private-accessor/runtime-
option mistakes, pending allocation-assumption failures and GDB trace are preserved.
The trace identifies the existing native StorageWorkState and AccountedIndexWork
controls; the harness accounts for both rather than claiming an allocation-free
indexed read. Production stays unchanged from source2. Preimages, source maps,
all raw attempts and executed helpers remain reviewable.

## Remaining scope

CombinedCapture's ordinary shared control retains native state/workload children.
ObservationTrace exports become ordinary retained payload inside session/report
graphs. ModeDescriptor/PlanExplanation/StatisticsExplanation controls, trace/gauge
arrays and runtime evidence graphs need their own original-account disposition.
Standalone exports and caller-supplied immutable aliases are separate boundaries.
Async/diagnostic/invariant scratch, authentic operator record/byte reconciliation
and complete overflow/no-op/churn/compiler/sanitizer/fresh-source matrices remain.
The focused next-owner inventory is not exhaustive whole-goal acceptance.
See [handoff](../handoff.md), [ledger](../task_ledger.md),
[memory contract](../memory_accounts.md) and [statistics](../statistics.md).
