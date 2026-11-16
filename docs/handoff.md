# CROWN handoff — reviewed implementation and GitHub delivery

The implementation is published on the
[GitHub review branch](https://github.com/NTU-DBT/CROWN/tree/review/native-v73-f4732bac).
The first published commit is `f4732bacc7b5e7d692d7660fc83d2f11088fa6b4`;
later documentation-only commits preserve its native code. The existing remote
`master` and default branch remain unchanged. Publication uses an isolated Git
repository; the original checkout's Git metadata is preserved.

All 902 code/configuration paths, including 414 production files, retain the
accepted V72 bytes. Both complete V73 builds pass. Release and Debug ASan/UBSan
each execute all 396 registered tests: 396 pass, zero fail and zero skip, with
unchanged source and build metadata. Actual commands, JUnit, logs and bindings
remain in `build/verification/v73-full-regression-v1`. These finite executions
support the scoped review; they do not establish universal correctness or a speedup.

The [original-scope review](verification/completion-v73-2026-11-16.md) receives
all 78 task IDs, 777 requirement rows and 44 mandatory Q/U cases. Its three audit
lanes identify 770 complete rows and seven explicit deferred clauses; no outstanding
requirement within the agreed scope was found. The root separately receives 18
cross-cutting/user-scope rows. Both native profiles and the requirement joins have
independent receiving records. Historical source, benchmark, release and SDK
evidence retains its original vintage and limitations.

The [inspection guide](code_review.md) and [block index](code_specs/README.md)
cover 900 mapped files, 202,375 lines and 22,533 regions. All 19,205 nonblank
regions have source-bound usage/invariant/ownership/failure/cost/reference contracts;
3,328 blank regions retain structural descriptions. The 21,731-record registry
and all 158,448 generated local links pass their current checks. Coverage makes
code inspectable; it does not independently prove every block correct.

Ledger: 75 verified, one in progress and two not started out of 78. A02 project
licensing disposition, X07 approximation and X11 parallel/distributed execution
are user-deferred. Existing rights and notices remain preserved. Shared-query
optimization remains deferred; X10 owners maintain each query independently and
serially. Comparisons, top-k and difference retain their documented ordinary
propagation or exact recomputation costs. No new specialized paper bound is claimed.

The [exact V73 technical handoff](handoff-history-v73-2026-11-16.md) preserves the
pre-publication state. Its sealed master is
`build/verification/human-inspection-v73-progress-v1.json`, with 4,996 explicit
source/provider paths and a 10,930-file successful post-seal check. The user later
selected a new review branch in the existing public `NTU-DBT/CROWN` repository;
the earlier proposed private repository was never created. Device authentication
is no longer a delivery dependency.

The actual remote delivery records are in `build/verification/v73-github-delivery-v1`.
Final documentation lineage and root receiving are in
`build/verification/v74-github-delivery-root-v1`. The publication README and
relocated evidence map describe omitted historical archives and retained source
vintages. Preserve all closed evidence, SDKs, release images and source providers.
Future code changes need corresponding source/card/native verification; documentation
successors do not change the completed native cohort.
