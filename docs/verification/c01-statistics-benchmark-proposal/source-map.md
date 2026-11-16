# Source map

| Benchmark package file | Role | Build/runtime placement |
|---|---|---|
| `benchmark.cpp` | Standalone deterministic consumer, semantic reference, four profile runner, JSON report | Compiled only into `/tmp/crown-c01-benchmark-component-20261107`; not registered in CMake or tests |
| `README.md` | Input provenance, exact build/run commands, workload and measurement contract | Documentation only |
| `input-pins.sha256` | Frozen API package and warning-only build-input pins | Documentation only |
| `package.sha256` | Hash manifest for this benchmark proposal's files | Documentation only |

The frozen collector package remains at `../c01-statistics-collection-proposal/`. Strict benchmark compilation uses the API-identical warning-only source copy at `../c01-statistics-collection-warning-proposal/`. No native source, collector package, target, test registration, schema, report type, or CMake file is changed by this benchmark proposal.
