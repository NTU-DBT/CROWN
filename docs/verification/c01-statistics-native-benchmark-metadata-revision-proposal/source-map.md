# Source map

| File | Role | Boundary |
| --- | --- | --- |
| `native_benchmark.cpp` | Byte-identical corrected benchmark consumer from the frozen oracle revision | Included for a self-contained proposal; no C++ source change |
| `build-only.sh` | Strictly checks the full input manifest, object identities, and archive identities; optionally recompiles/relinks if needed | Not run for this metadata-only revision |
| `oracle-correction.diff` | Exact preserved source diff that fixes the child-P oracle | Historical source correction; unchanged here |
| `metadata-correction.diff` | Exact input-pin and strict-check changes against the frozen oracle revision | Review record |
| `README.md` | Metadata failure, corrected identity, and scope | Proposal only |
| `build-evidence.md` | Root preflight provenance and existing binary identity | No benchmark execution or timing evidence |
| `input-pins.sha256` | Original and corrected proposal inputs, root preflight record, existing binary, objects, and archives | Strictly validated by optional build script |
| `source-map.md` | File roles and exclusion boundary | Proposal only |
| `package.sha256` | Hash manifest for all proposal files except itself | Immutable metadata revision identity |
