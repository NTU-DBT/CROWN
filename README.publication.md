# CROWN source publication

This public review-branch source snapshot preserves the maintained native C++23 implementation,
its tests, schemas, examples, pinned third-party sources, paper PDF, human-inspection
specifications, and exact pinned legacy baseline inputs. Start with [README](README.md),
[Refactor plan and user decisions](Refactor.md), and [human inspection guide](docs/code_specs/README.md).
The source manifest and native inventory proof are in [publication/](publication/).

Build and test the native source in a new directory:

```sh
cmake -S . -B build/native -DCMAKE_BUILD_TYPE=Release
cmake --build build/native --parallel 2
ctest --test-dir build/native --output-on-failure
```

A C++23 compiler, CMake, Python 3 and the system build tools documented in the
project guides are required. Vendored dependency inputs remain available for the
offline native build. This publication has not itself run a new native build;
its 902 code/configuration inputs are byte-identical to the sealed V73 inventory,
which preserves the accepted V72 native implementation. The compact evidence below retains each report's original date, scope
and limitations; it does not qualify a new release or prove universal correctness.

Full historical build/verification archives, frozen source overlays, binary SDKs,
benchmark run outputs and legacy build trees are excluded. Historical links into
build/verification in the preserved documentation and code cards therefore refer
to the original workspace and will not all resolve in this source publication.
The documentation link checker requires those original evidence archives. A small
[relocated evidence selection](publication/evidence-map.json) is included for
inspection; its own historical references also retain their original workspace
paths. Complete historical Scala/DBToaster replay environments are not included;
the exact baseline source pins required by the native checks are retained.

Queries remain independent. Approximation, shared multi-query execution, parallel
and distributed query execution remain outside the accepted implementation scope.
The planner's recorded candidate/proof-budget status and source-only fallback
limits remain applicable; no stronger optimality guarantee is implied by publishing.

All existing rights and dependency notices are preserved. The user deferred the
project licensing decision; this snapshot does not grant a new project license.

## Current review snapshot

The sealed [V73 original-scope review](docs/verification/completion-v73-2026-11-16.md)
records complete Release and Debug ASan/UBSan suites: each executes all 396
registered tests, with 396 passes, zero failures and zero skips. These actual
runs bind the unchanged native 902 inputs in the original V73 source cohort.
This export has not repeated a native build or test suite. Its earlier offline
configure discovered the same 396 tests. The sealed technical records retain their original authentication-pending status.
The source snapshot has since been published through the verified SSH route
selected by the user; see the delivery record below.

The [V73 validation summary](publication/v73-validation-summary.json) pins the
sealed master, source point, native inventory and both profiles' final build,
suite and JUnit receipts. Exact relocated text copies appear in the
[evidence map](publication/evidence-map.json). The master SHA-256 is
`56e77572afd49273107145281d52ec7f14ff1adea948001e52b5a5de21bb97ab`;
the V73 source-point SHA-256 is
`96af5ec3aa4041136d92b9b8b798696fe46061a2bb529f66297f68a28134a128`.

The [current delivery source summary](publication/v74-delivery-source-summary.json)
pins the explicit V74 documentation successor, source-point SHA-256
`181d03d6e248d95f792041321edf5555371d4a5ca59e58aba48b1dee1916c12c`.
All 4,924 selected maintained/pinned source files match current originals; 4,923
also match the V74 hashes and immutable providers. The included paper PDF is
pinned independently outside that source-point inventory. The final handoff,
review guide and completion report are explicit documentation successors;
the unchanged native 902 inputs retain their V73 validation vintage.

The export omits 74 archived files under documentation build directories from
the source-point inventory. Full build/verification archives, frozen provider
copies, build outputs, benchmark run archives and SDK binaries remain excluded;
the compact relocated text selection is the explicit exception. Historical
references inside preserved documentation, cards and receipts retain their original
workspace paths and will not all resolve. These results support the stated finite
review and test scope; they do not establish universal correctness or qualify a
new release.

## GitHub delivery

The user selected the existing public `NTU-DBT/CROWN` repository, on the new branch
[`review/native-v73-f4732bac`](https://github.com/NTU-DBT/CROWN/tree/review/native-v73-f4732bac).
The initial published snapshot is commit
`f4732bacc7b5e7d692d7660fc83d2f11088fa6b4`. The normal SSH push and independent
remote-ref/API checks are preserved in the [initial delivery receipt](publication/evidence/github-delivery/initial-push-receiving.json).
The repository's `master` branch and default remain unchanged. Documentation-only
successors retain the exact 902 native inputs and the original technical evidence
vintages; their current branch head can be inspected at the link above.

The earlier proposed new private repository and device-login plan were superseded
by this explicit destination choice. No new private repository was created. The
unused device-login process was cancelled; no further GitHub API sign-in is
required for the verified SSH push route. Full historical evidence remains omitted
under the limits described above.
