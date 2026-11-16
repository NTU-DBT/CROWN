# O07 native documentation proposal — unapplied

This excluded documentation package is based on the reviewed native-integration
proposal (`ae3aee4c…104ee78`) and composed EXPLAIN proposal
(`a4e75996…310f30a`). It contains proposed native documentation only. It does
not edit `README.md`, `docs/native_build.md`, sources, schemas, build files, or
the task ledger, and it does not claim O07 verification.

## Contents

- `overlay/docs/observability.md` — user guide for native EXPLAIN and runtime
  observations.
- `overlay/README.md` — proposed short README addition.
- `overlay/docs/native_build.md` — proposed native CLI/build-guide addition.
- `baseline-sha256.json` — input-document and reviewed-source pins.
- `readiness.json` — proposal status and artifact hashes.

The documentation reflects the reviewed CLI and report layers. Root owns any
integration after CLI acceptance; native execution and the full test matrix
remain separate gates.
