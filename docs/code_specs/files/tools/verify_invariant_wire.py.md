# `tools/verify_invariant_wire.py` — block usage map

[Source](../../../../tools/verify_invariant_wire.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `303042a163f4130140394b446e7603ad73228491c78026acce368e24139a12f7`. 31 lines partitioned into 1 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–31](../../../../tools/verify_invariant_wire.py#L1) | Imports dependencies; declares callable signatures; declares values/defaults or compile-time conditions. | 3 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |

## B0001

[Lines 1–31](../../../../tools/verify_invariant_wire.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
print('All210 native invariant reports match independently compiled reference bytes and the unchanged schema')
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export and validate the fixed native invariant-report corpus in a temporary directory. |
| inputs / outputs | Parses --executable during import, reads the digest manifest/schema, runs the exporter and hashes/parses/schema-validates each JSON report. With Python assertions enabled, it checks exactly the 210 expected names and raw digests. |
| invariants | No __main__ guard: import also parses argv and launches the child. The digest match is only for the pinned finite report fixture set. |
| ownership | TemporaryDirectory attempts export-tree cleanup on normal or exceptional unwinding; Python owns schema/DOM/validator state. JSON Schema behavior remains an imported-package dependency. |
| failure | Argparse, read/JSON/schema, assertion, child-exit, and validation failures propagate; context cleanup removes the temporary corpus. |
| cost | One child without an explicit wrapper timeout or output-byte cap, schema-store reads and per-report reads/hash/JSON/schema checks; the intended finite corpus has 210 reports. |
| Design | [tools/verify_invariant_wire.py](../../../../tools/verify_invariant_wire.py), [tests/runtime/inspection/wire-v1.json](../../../../tests/runtime/inspection/wire-v1.json), [schemas/runtime-diagnostic-v1.schema.json](../../../../schemas/runtime-diagnostic-v1.schema.json), CMakeLists.txt:972, tools/verify_invariant_wire.py:1-31 |
