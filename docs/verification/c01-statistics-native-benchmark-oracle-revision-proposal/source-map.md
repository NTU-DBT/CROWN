# Source map

| File | Role | Boundary |
| --- | --- | --- |
| `native_benchmark.cpp` | Frozen benchmark consumer with one corrected expected child-P population | Standalone proposal only; not part of the native product |
| `build-only.sh` | Strictly compiles the revised consumer, verifies/reuses 15 pinned O3 production runtime/collector/storage objects, and links pinned Release dependencies | Compile/link reproduction only; does not execute a program |
| `oracle-correction.diff` | Exact source diff from the preserved frozen benchmark | Review record |
| `README.md` | Contract evidence, correction rationale, scope, and reproduction command | Proposal only |
| `build-evidence.md` | Successful compile/link command and hashes plus root's preserved failed-attempt provenance | No benchmark timing claim |
| `input-pins.sha256` | Original package, combined API package, native contract sources/tests, artifacts, objects, and link dependencies | Input identity record |
| `source-map.md` | File roles and excluded boundary | Proposal only |
| `package.sha256` | Hash manifest for all proposal files except itself | Immutable package identity |
