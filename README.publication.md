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
its 902 code/configuration inputs are byte-identical to the current V72 source
lineage. The compact evidence below retains each report's original date, scope
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

The [V73 original-scope review](docs/verification/completion-v73-2026-11-16.md)
records the received requirement review and the complete Release suite: 396 tests
pass, with no failures or skips. At this documentation snapshot, the complete
Debug ASan/UBSan suite remains pending and GitHub API authentication remains
pending after an expired device-login flow. The native 902 inputs remain exact
V72. This publication export has configured and discovered the 396 tests; it has
not executed a separate native build or test suite. The source report keeps its
original historical evidence links and scope qualifications. The full evidence
archives remain omitted as explained above.
