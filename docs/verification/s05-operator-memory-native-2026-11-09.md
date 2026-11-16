# S05 operator record and byte reconciliation

9 November 2026. Incremental implementation of Refactor.md S05. The full goal
remains active; ledger: 41 verified, 3 in progress (A02/S05/O06), 34 not started.
Whole-query memory and full native/fresh-source acceptance remain false.

## Implemented result

The native report joins actual operator counts to actual account allocations,
table/index statistics and tuple-arena slot/value lifetimes. Its persistent and
temporary storage uses the original query account under capture:14. A bounded,
nonallocating attribution inventory walks existing allocation records without
adding a permanent owner registry. Account-wide owner, purpose and lifetime
partitions are checked before publication. Scratch is released before the final
snapshot, which includes the report's own retained storage.

Support records/survivors/P/E, physical derivations and Delta live row/bucket/
membership counts are read from the actual runtime and checked against table
or maintained counts. Pending/released owners have account totals without
committed operator claims. Hidden E and unmaterialized live images are nullable.
The actual Delta coordinator attribution moves from node0 to UINT64_MAX, avoiding
a collision with factor0. One existing delta-memory summation adapter includes
that reserved coordinator; its values and assertions are unchanged.

The separate version1 JSON export and runtime/session `--format memory-json`
CLI are explicit caller-owned boundaries. The encoded-byte cap is checked before
stdout publication, after JSON construction. It does not bound export temporaries.
See [the public contract](../memory_reports.md). Frozen existing report schemas
and encoders are unchanged.

## Focused verification

Source7 freezes 973 input paths. Debug passes all four focused cases in 1.52s:
operator_memory_report, operator_memory_schema, operator_memory_cli and delta_memory.
The native test covers both storage backends, all four owner kinds and three
native tree shapes; global allocation requests reconcile with the original
account. Every persistent capture allocation is faulted (11–14 positions in the
core fixtures), with no partial report or resident leak. Exact/one-under work,
owner/table/operator and real query-byte caps, release/retry under the same cap,
held snapshots and controller-only final release pass.

Additional checks cover retained erased records, allocation-free journal release,
free-pool distinctions, 20 duplicate/churn cycles without growth after warmup,
wide string values with NUL, composite parent buckets, all three live-maintenance
policies, normalized SQL plans, pending/stopped/dropped phases and rejection of
corrupted maintained totals/bucket degrees. Eight actual native exports satisfy
the strict schema and independently summed account/table/arena identities. The
real CLI covers epochs, private/released states and empty stdout on limit failure.

Source8 adds documentation only and freezes 976 paths. Its broad results are:

| Mode | Scope | Result | Seconds |
| --- | --- | --- | ---: |
| Debug | Full registration | 225/225 PASS | 917.93 |
| Release | Selected native consumers | 115/115 PASS | 18.66 |
| Clang18 Debug | Selected native consumers | 115/115 PASS | 99.41 |
| ASan+UBSan/leaks | Selected native consumers | 115/115 PASS | 544.62 |

The selected set uses 104 actual native targets per mode; Python schema/CLI
drivers map to their native executables. The full Debug registration names 189
direct native executables. No predecessor result is presented as a rerun of this
new code. Final source9 changes documentation only from source8 (976 paths).

All nine successful build attempts have zero diagnostics. Twenty generated
compiler/link records confirm strict C++23 warnings, enabled test assertions in
Release, and ASan+UBSan instrumentation of the account core, both runtime
libraries and the actual report test. Leak detection and halt-on-error settings
are explicit in the sanitizer runner. The executable inventory pins all 189 full
Debug binaries and 104 selected binaries per alternate mode (501 total), plus
four actual build caches. The independent readback checks those on-disk bytes.

## Preserved evidence

The sealed predecessor is
[native ranking/selection](s05-ranking-selection-native-2026-11-09.md). All 964
predecessor source paths were checked and preserved, plus the handoff (965
preimages). Source maps, raw build/test failures and executed helper versions
remain under `build/verification/s05-operator-memory-native-*`.

Source2's new test compilation failed on optional canonical visibility access;
source3 corrected the test. Source4's new schema case was BAD_COMMAND because
Python was discovered later in CMake; source5 moved registration after discovery.
The failed raw receipts remain. Helper v3 adds tools/apps to the frozen source
scope before the new Python verifiers first execute in source6. Source7 adds
the extended fixtures; all production changes were already present in source5.
The first matrix-preparation helper saved registration and terminal stdout before
its exact-adapter audit expected `const auto` instead of the actual explicit
`const std::uint64_t`. Its failed helper/repair receipt remains; the second audit
checks the exact two-loop substitution, with no test-source change. Registration
from that first helper is complete and maps every selected driver to a real
native target.

All24 recorded jobs are closed. Detailed terminal stdout was saved for each run
before further CTest use. Immutable earlier maps/helpers/raw failures, the exact
adapter audit, actual generated compiler/link options and remaining-diagnostics
review remain available. The final
[progress](../../build/verification/s05-operator-memory-native-progress-v1.json),
[source map](../../build/verification/s05-operator-memory-native-inputs-v9.json),
[executable inventory](../../build/verification/s05-operator-memory-native-binary-inventory-v1.json)
and [checkpoint seal](../../build/verification/s05-operator-memory-native-checkpoint-seal-v1.json)
bind the scoped results. The separate post-seal-audit-v1.json records independent
source/artifact/executable/build-option and documentation-link readback.

The remaining-diagnostics-review-v1.json names ordinary expected-state
sets/maps/rows in Support/Physical/Delta inspect/check_invariants and owning
InspectionContext issue storage. Those paths, remaining work audits and full
native/fresh-source acceptance keep S05 open. Passing this cohort does not close
the full78-card goal.

Root implements and verifies the work. A small Luna Max task supplied a read-only
census/review; no Astra was used. Keep terminal CTest stdout before subsequent
runs/enumeration and do not build while CTest is active in that build directory.
Continue from [the handoff](../handoff.md); the complete S05 card remains open.
