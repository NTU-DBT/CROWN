# C01 native registration and publication proposal

2026-11-07. **Excluded preparation; native files remain unchanged and C01 remains
`not_started`.** This coherent overlay prepares the accepted statistics APIs,
versioned report, native build registration and public documentation for root
integration. It is not native matrix acceptance. No CMake, CTest, producer,
exception binary, checker, benchmark or symbol inspector was executed by the
author. [BUILD_RESULTS.md](BUILD_RESULTS.md) records the narrow direct compilation;
[ROOT_REPRODUCTION.md](ROOT_REPRODUCTION.md) gives application and execution notes.

The frozen report package is the runtime/storage/report base, manifest
`730a7488e53a749b024b307dab27c09d58a324ae7603bccc8831364af289f947`.
Root's [strict-only report result](../../../build/verification/c01-statistics-report-root-attempt-1.json)
passes both variants, including producers, fault sweeps, runtime-only consumers,
combined regressions, schema/semantic mutations and original-v2 byte comparisons.
The [complete sanitizer continuation](../../../build/verification/c01-statistics-report-root-attempt-2.json)
also passes both complete matching variants. The [report root record](../c01-statistics-report-root-results-2026-11-07.md)
separates those accepted excluded runs from the still-pending native matrix.
The [independent report review](../c01-statistics-report-independent-review-2026-11-07.md)
has no blocker. Accepted combined, selected policy/order, typed scalar, guide and
actual-engine benchmark evidence remains preserved in its original packages.

## Exact publication contents

[source-map.tsv](source-map.tsv) names all 62 overlay files and their explicit
native destinations, origins and allowed changes. Prefix removal is the only
path mapping; no file outside that list is to be copied. All 46 selected report
overlay files are copied unchanged except the two files in
[publication-gate-removal.diff](publication-gate-removal.diff). The old generalized
diagnostic and historical legacy-control producer are deliberately not published
or registered again. Their frozen source/evidence remains available.

The small diff removes `c01_project_gate` from the copied v3 writer and the
copied closed schema's required/property lists. Repository acceptance belongs
in the ledger/evidence, not runtime capabilities. Actual fact/cost/proof fields
are unchanged. All prior schemas and the native v2 writer are untouched.
The [copied semantic checker](overlay/tools/support/check_statistics_reports.py)
is byte-identical to the frozen report checker, SHA-256
`3c7a12c18c3e9b1eb1ff09e56ad620f966d02f6de41435aa3aa6d207fe9a426b`.
The new [wrapper](overlay/tools/verify_statistics_reports.py) checks baseline
checksums, runs a fresh matching producer corpus, invokes that checker, and
additionally requires the native schema to reject the removed project field.
Failure retains its temporary corpus; success removes it.

The two [legacy v2 baselines](overlay/tests/statistics/legacy-v2/README.md) are exact
copies of root's actual frozen-combined control outputs. Their hashes and
provenance are checked in; clean native tests need no historical `/tmp` build.
These immutable expected bytes are not regenerated from the implementation
under test. All frozen report producer and fault assertions are preserved.

## Build and test registration

[The CMake diff](cmake-registration.diff) adds five runtime units to the shared
source list for both matching runtime libraries and two report units to the
shared source list for both report libraries. Storage stays in `crown_core`;
runtime stays independent of observability/report IO. No executable links both
runtime variants. The runtime-only consumers explicitly link no report/query
explanation library. New numeric assertions remain enabled in Release through
consumer-local `-UNDEBUG`; existing targets and flags are unchanged.

All 99 original CTests and their commands remain. The 32 additions are listed
independently in [registered-ctests.tsv](registered-ctests.tsv) and described in
[CTEST_REGISTRATION.md](CTEST_REGISTRATION.md). [expected-ctests.txt](expected-ctests.txt)
contains the sorted expected full 131-test inventory; it is an authored
expectation, not output from a CMake/CTest run. The original 99-name inventory is
[legacy-ctests.txt](legacy-ctests.txt). Every new CTest has label `C01` and timeout
900 seconds and participates in the existing sanitizer environment assignment.

The opt-in [policy/order source package](../c01-statistics-policy-order-proposal/README.md)
is copied exactly, including its helper. The three original policy targets keep
acceptance macros absent. Six additional production executables select FIFO
or LIFO and supply 14 enabled executions: five delta policies, explicit replay
and window for each order. Old tests are not rerun through duplicate new
registrations. These selected cases do not cover the full Cartesian policy
product. The accepted scalar consumer is copied exactly and registered once
against production runtime.

## Documentation and evidence

[The public guide draft](overlay/docs/statistics.md) preserves the compiled
owner/workload examples and adds the actual report, lifecycle, unknown/error,
scalar transport and independent export-bound contracts. It separates state
payload, workload capacities, report copies and allocator exclusions. Narrow
README/build/observability additions explain explicit v3 selection and the
legacy guard. No CLI/O08 or cost-ranking scope is added.

The [accepted engine benchmark record](../c01-statistics-native-benchmark-root-results-2026-11-07.md)
is incorporated with its six medians, measured paths, fixed workload and
substantial observed collection costs. It is a measurement of the frozen
combined candidate, not integrated-native verification. No zero-off-overhead,
threshold, production prediction, arrival-rate or total-memory claim is added.

The source/input/package manifests are to be checked before application.
`PREEDIT_DESTINATIONS_SHA256SUMS` pins every existing destination; the separate
`NEW_DESTINATIONS.txt` names expected-absent files. The current O07 seal is pinned
as a historical input; only root verifies its 691 native entries immediately
before integration. Never recheck those old native entries after applying C01.
Native ledger/handoff/status updates, the full matrix, C01 testing-symbol audit,
final source seal and acceptance remain root work outside this overlay.
