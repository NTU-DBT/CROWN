# Native accounted storage dispatch checkpoint — 8 November 2026

This is the historical frozen dispatch checkpoint. The successor
[compiled-plan storage record](memory-plan-2026-11-08.md) covers later native
implementation. Statements below apply to this packet's own source and runs.

S05 is **in progress**. Production `crown_accounted_storage_table` now builds
`AccountedStorageTable`, dispatching directly to the existing accounted reference
and optimized backends. Construction receives a frozen layout carrying the
existing account. Dispatch owns a variant and shared accounted work handles;
it creates no extra account/control, replacement grant or standard Row mirror.
The actual earlier StorageTable/PlanStorage/runtime interfaces still need to
adopt accounted values; full query-byte enforcement and native acceptance remain
open.

Frozen input is `build/verification/s05-accounted-dispatch-source-attempt-1/`
(879 files). Each selected build compiles 60 actual C++ commands from 52 distinct
sources into nine native production/testing libraries and 13 test executables.
The main memory fixture and two collision profiles each run all 38 checks,
retaining all previous 36/31/26 fixture populations. Ten existing layout/arena/
reference/journal/facade regressions remain selected.

All four runs and their source/command/object/archive/link/test audits pass:

| Mode | Actual build seconds | CTest real seconds | Selected tests |
| --- | ---: | ---: | ---: |
| GCC Debug | 109.868 | 29.70 | 13/13 |
| GCC Release | 143.717 | 2.97 | 13/13 |
| Clang Debug | 93.658 | 21.71 | 13/13 |
| GCC ASan+UBSan/leaks | 191.776 | 108.86 | 13/13 |

All compiler/test handles are closed. The accepted matrix is
`build/verification/s05-accounted-dispatch-matrix-accepted-v1.json`. Current jobs
are recorded in `build/verification/s05-accounted-dispatch-jobs.json`.

Two new top-level checks verify native dispatch:

- Both permanent backend choices, owner/relation/layout/projection identities,
  all probes/index/collection/copy/erase paths, actual memory reports and stable
  borrowed row/pin addresses. Reference lexical live order and indexed live-link
  order are checked separately; native bucket order is retained.
- Persistent failure at all **134** observed positions across seven operations
  per backend: second-table construction, index creation, insertion, journal
  creation, journal insertion, same-account copy and owning snapshot collection.
  Every failure releases temporary ownership, preserves current purpose/lifetime
  byte partitions and logical table/journal state, then retries successfully.

The lifecycle check also covers same-account owning exports, reference/indexed
statistics, foreign work-control denial, required indexed grants, original
journal-cursor grant identity, rollback of replacement rows, retained committed
change values/pins and allocation-free final release after facade destruction.
Two indexed table journals share one owning grant: after its remaining work is
consumed, the second mutation fails; both roll back without allocation or a
refill. This is a composed storage check, not the full native query epoch gate.

Compile-time checks reject both forms of borrowed `get` on a temporary owner,
including the default-work-argument form. The reference table exposes its
existing arena counters directly for O(1) `arena_statistics()`; complete memory
diagnostics retain their documented account-ledger scan.

Every profile still executes the earlier 91 reference and 104 optimized fault
positions, exact/one-under fixture byte limits, 44 work boundaries, nine component
limits, 256-step differential models and eight-live traversal after eight/64
populations. No new dispatch-specific peak-byte or runtime speedup claim is made.

Root auditor v4 preserves earlier source/tool/strict-command/object/archive/
link/hook/sanitizer/terminal checks and adds the two actual dispatch libraries,
their coherent private testing symbols/defines and each profile's new output.
Production exposes no dispatch collision authority or allocating global new/
delete replacements. All 20 test-only replacement hooks are bound to each
memory fixture object/executable. Actual CMake links repeat the same native core
archive as a dependency; every occurrence is checked against the native graph.
CTest's shortened JUnit prefixes are still checked against complete per-test
verbose output, with all selected successful testcase identities required.

Evidence uses the `s05-accounted-dispatch-` prefix under `build/verification/`:
source/freeze attempt1, per-mode records/audit-v4 summaries/actual terminal
closures, reviewed collectors, source-binding receipts and preimages. The
historical [optimized checkpoint](memory-indexed-2026-11-08.md), earlier reference
record and S04 source/matrix seals remain as-of evidence for their own immutable
inputs. Do not compare historical input hashes with successor code.

Root implemented/reviewed the code and owns execution. A bounded Luna Max agent
only inventoried lowering/layout tokens and the next plan-storage test boundary;
no new Astra was used. See the [memory contract](../memory_accounts.md) and
[handoff](../handoff.md) for actual runtime/plan migration and the unchanged full
78-card objective.
