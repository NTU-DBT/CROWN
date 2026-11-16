# CROWN source publication

This private source snapshot preserves the maintained native C++23 implementation,
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
configure discovered the same 396 tests. GitHub API authentication remains pending
after an expired device-login flow; no repository or push is claimed here.

The [V73 validation summary](publication/v73-validation-summary.json) pins the
sealed master, source point, native inventory and both profiles' final build,
suite and JUnit receipts. Exact relocated text copies appear in the
[evidence map](publication/evidence-map.json). The master SHA-256 is
`56e77572afd49273107145281d52ec7f14ff1adea948001e52b5a5de21bb97ab`;
the V73 source-point SHA-256 is
`96af5ec3aa4041136d92b9b8b798696fe46061a2bb529f66297f68a28134a128`.

All 4,923 selected maintained/pinned source files match the current originals.
Of these, 4,922 match both the sealed V73 source-point hashes and their immutable
providers; the included paper PDF is pinned independently outside that source
inventory. The export omits 74 archived files under documentation build directories
from the source-point inventory. Full build/verification archives, frozen provider
copies, build outputs, benchmark run archives and SDK binaries remain excluded;
the compact relocated text selection is the explicit exception. Historical
references inside preserved documentation, cards and receipts retain their original
workspace paths and will not all resolve. These results support the stated finite
review and test scope; they do not establish universal correctness or qualify a
new release.
