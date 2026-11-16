# `tests/integration/component_runtime.py` — block usage map

[Source](../../../../../tests/integration/component_runtime.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `3ae4fad27caef75d4703872eefd14d1d30b529ec0e47e9adf579b616aec9fbb4`. 304 lines partitioned into 11 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../tests/integration/component_runtime.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | growth insert; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 21–26](../../../../../tests/integration/component_runtime.py#L21) | Callable definition: def catalog(names, columns=('c0', 'c1')): | calls ; returns {'schema_version': 1, 'catalog': {'version': 1, 'tables': \[; 2 loop sites · [reviewed contract](#b0002) |
| [B0003 · 27–28](../../../../../tests/integration/component_runtime.py#L27) | Explanatory comments or spacing. |  |
| [B0004 · 29–54](../../../../../tests/integration/component_runtime.py#L29) | Callable definition: def sqlite_prefixes(sql, tables, events): | calls connect, join, execute, set; guard require(name in {table\['name'\] for table in tables\['catalog'\]\['tables'\]}, 'unexpected oracle table'); returns result; 8 loop sites · [reviewed contract](#b0004) |
| [B0005 · 55–56](../../../../../tests/integration/component_runtime.py#L55) | Explanatory comments or spacing. |  |
| [B0006 · 57–67](../../../../../tests/integration/component_runtime.py#L57) | Callable definition: def request(label, sql, tables, events, output, backend): | calls indexed_options; returns {'schema_version': 1, 'case_id': label, 'query_family': label, · [reviewed contract](#b0006) |
| [B0007 · 68–69](../../../../../tests/integration/component_runtime.py#L68) | Explanatory comments or spacing. |  |
| [B0008 · 70–71](../../../../../tests/integration/component_runtime.py#L70) | Callable definition: def event(operation, table, first, second): | calls ; returns {'operation': operation, 'table': table, 'values': \[first, second\], 'phase': 'oracle_control'} · [reviewed contract](#b0008) |
| [B0009 · 72–73](../../../../../tests/integration/component_runtime.py#L72) | Explanatory comments or spacing. |  |
| [B0010 · 74–300](../../../../../tests/integration/component_runtime.py#L74) | Callable definition: def main(): | calls require, len, in, Path; guard require(len(sys.argv) in (5, 6), 'usage: component_runtime.py SET ROWS SESSION CROWN \[NEW_ARTIFACT_…; returns json.loads(child.stdout); None; 40 loop sites; source comment (unverified): # Endpoint witnesses multiply walks while the DISTINCT internal quadruple · [reviewed contract](#b0010) |
| [B0011 · 301–304](../../../../../tests/integration/component_runtime.py#L301) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0011) |

## B0001

[Lines 1–20](../../../../../tests/integration/component_runtime.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:fcea74eec04e44396ef4c265095fcd37dfc81bb48e6bd8577a5e106d98606e30
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set up the bounded component-runtime oracle module and its shared helpers. |
| inputs / outputs | Imports Python standard-library facilities, JSON Schema validation, and the project measurement/canonicalization helpers; fixes the repository root and disables bytecode writes. |
| invariants | The script is invoked against already-built binaries. The module creates no native build, downloads no dependencies, and defines fixtures separately from the runtime implementation. |
| ownership | The harness owns its generated requests and temporary output directory; imported helpers supply deterministic request options and JSON canonicalization. |
| failure | Missing Python dependencies, helper imports, schema files, or invalid schema references stop the integration command. |
| cost | Module setup is once per process. The workload is in finite test invocations below; timing fields are functional controls and not performance evidence. |
| Design | [schemas/component-runtime-request-v1.schema.json](../../../../../schemas/component-runtime-request-v1.schema.json), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [tools/verify_workloads.py](../../../../../tools/verify_workloads.py) |

## B0002

[Lines 21–26](../../../../../tests/integration/component_runtime.py#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L26:sha256:c38e7201a7877b331fce5003b186edbe271ec363dc48d5363903315b0cb7f491
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build small version-1 catalog fixtures for the SQLite and native requests. |
| inputs / outputs | Takes table names and an optional column-name tuple; returns non-null int64 columns with empty constraints, hints, and distinct-count statistics. |
| invariants | The provided fixtures use the same catalog shape for the independent oracle and native request; this helper does not model arbitrary catalog features. |
| ownership | Returns a new Python dictionary owned by the caller. |
| failure | Invalid names or unsupported fixture dimensions are rejected downstream by SQL or request validation. |
| cost | Allocates a small catalog proportional to the listed tables and columns. |
| Design | [schemas/component-runtime-request-v1.schema.json](../../../../../schemas/component-runtime-request-v1.schema.json), [tests/integration/component_runtime.py](../../../../../tests/integration/component_runtime.py) |

## B0004

[Lines 29–54](../../../../../tests/integration/component_runtime.py#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L54:sha256:1948b5c9891397017608532f4db9606ee09ad059f1562081b6cca93c3d38b292
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute each event prefix with independent in-memory SQLite and retain set and bag views. |
| inputs / outputs | Creates fixture tables, evaluates the query from an empty state, applies each physical insert/delete, and returns sorted distinct rows, signed set deltas, and bag multiplicities for every prefix. |
| invariants | The event stream is applied in order and the function assumes the fixture's two-value row shape. Set deltas use previous/current distinct row sets; bag counts retain multiplicity. |
| ownership | A function-local SQLite connection owns the scratch database and is closed before returning ordinary Python result data. |
| failure | Unknown table names fail through \`require\`; malformed SQL, invalid table/value shape, or SQLite errors terminate the oracle. |
| cost | Runs the full SQL query after each event and materializes its prefix result; work and output scale with the finite fixture, query, and result cardinalities. |
| Design | [schemas/component-runtime-request-v1.schema.json](../../../../../schemas/component-runtime-request-v1.schema.json), [tests/integration/component_runtime.py](../../../../../tests/integration/component_runtime.py) |

## B0006

[Lines 57–67](../../../../../tests/integration/component_runtime.py#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L57-L67:sha256:30601acf2e6e39e91fa661697d7f4d7a4917046e2156e6c8723d4f7ae2d79c37
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a valid bounded verification request for one backend and output mode. |
| inputs / outputs | Combines SQL, catalog, events, selected output, backend-specific physical options, memory/work limits, and request/output caps into a version-1 JSON object. |
| invariants | For \`reference_ordered_v1\`, removes indexed-storage options and uses physical-options schema version 1; other options come from the project helper. Callers may then set mode and session controls for a case. |
| ownership | Returns a mutable dictionary owned by the caller; request creation and any later per-case mutations remain local to this test. |
| failure | Schema-invalid requests are caught by the validator on successful invocations; negative cases deliberately bypass schema admission to test native rejection. |
| cost | Creates a small fixed-shape object and includes explicit finite limits; it does not imply those caps are general performance bounds. |
| Design | [schemas/component-runtime-request-v1.schema.json](../../../../../schemas/component-runtime-request-v1.schema.json), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [tests/integration/component_runtime.py](../../../../../tests/integration/component_runtime.py) |

## B0008

[Lines 70–71](../../../../../tests/integration/component_runtime.py#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L71:sha256:d1b4b46d1c6a8d90f580adb146be13d18b1e3f8d1a29e0c9bc71a93989573ee0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create one physical insertion or deletion event in the oracle fixture format. |
| inputs / outputs | Takes operation, table, and two integer values; returns an event with the \`oracle_control\` phase marker. |
| invariants | Call sites use only \`+\` and \`-\` and pair each event with a two-column table fixture. |
| ownership | Returns a fresh Python dictionary; the caller owns it and may add it to a trace. |
| failure | The helper does not validate operation/table membership; SQLite and native request admission expose invalid cases. |
| cost | Constant-size dictionary construction per event. |
| Design | [schemas/component-runtime-request-v1.schema.json](../../../../../schemas/component-runtime-request-v1.schema.json), [tests/integration/component_runtime.py](../../../../../tests/integration/component_runtime.py) |

## B0010

[Lines 74–300](../../../../../tests/integration/component_runtime.py#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L74-L300:sha256:3849ba8179b0d0d0f1a27d0982b6f91c57c178c18f6424e8f18e939d78faa329
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run a finite end-to-end oracle and control matrix for native set, rows, and session adapters. |
| inputs / outputs | Consumes prebuilt set/rows/session/Crown executables and optionally a fresh artifact directory; emits per-command request/stdout/stderr files and a compact \`result.json\`. |
| invariants | Uses L5 DISTINCT witness and L3 path fixtures across \`reference_ordered_v1\` and \`indexed_chained_v1\`; compares SQLite prefixes, signed set output, compressed bags, supplied compiled source, session modes, rejection cases, schema integer boundaries, and result-capture controls. Eleven session arms include \`wal_replay\` and \`durable_replay\` with checkpoint interval 0 and recovery after physical event 3. The harness checks each replay once, zero checkpoints, and expected output prefixes. A separate receiving record inspects all eight Release/SAN raw reports and observes 13 WAL records at physical sequence 6 for those arms; the test itself does not assert \`wal_records\` directly. These finite fixtures do not establish arbitrary backend equivalence, pre-reconstruction WAL byte-size, power-loss durability, or universal input coverage. |
| ownership | The harness owns request and child-output files, SQLite scratch state, state directories, and its result summary. Native adapter processes own their runtime state and reports; SQLite owns its independent oracle database/results. |
| failure | Any schema, process-status, output, prefix, event-boundary, sequence, sink, checkpoint, reconstruction, or preserved-state mismatch fails via \`require\`. Successful children must emit no stderr; rejected children must emit no stdout. |
| cost | The direct run covers 57 commands, 280 SQLite prefix comparisons, 11 session arms, and two backends in each Release/SAN profile. Each child is time-limited; accumulated work depends on the finite SQL/result/trace sizes. Measurement repetitions assert reporting and capture suppression only; the result explicitly sets \`performance_claim\` false. |
| Design | [examples/component-runtime/native_request.hpp](../../../../../examples/component-runtime/native_request.hpp), [examples/component-runtime/native_set.cpp](../../../../../examples/component-runtime/native_set.cpp), [examples/component-runtime/native_rows.cpp](../../../../../examples/component-runtime/native_rows.cpp), [examples/component-runtime/session.cpp](../../../../../examples/component-runtime/session.cpp), [schemas/component-runtime-request-v1.schema.json](../../../../../schemas/component-runtime-request-v1.schema.json), [build/verification/component-evaluation-v59-v1/nonempty-wal-replay-receiving-v1.json](../../../../../build/verification/component-evaluation-v59-v1/nonempty-wal-replay-receiving-v1.json) |

## B0011

[Lines 301–304](../../../../../tests/integration/component_runtime.py#L301); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L301-L304:sha256:239f34ccf0a25c3afeefe82507f70b0ffbbcbf03dd6930292ca35d6b41937a29
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the test entry point only when this file is executed as a script. |
| inputs / outputs | Delegates directly to \`main()\` under the standard \`__main__\` guard. |
| invariants | Importing the module defines fixture/oracle helpers without launching native child processes. |
| ownership | The process entry point owns command-line execution; helper functions remain callable independently. |
| failure | Exceptions from the CLI test propagate as a failing process exit. |
| cost | No import-time workload; execution cost is the bounded matrix in \`main()\`. |
| Design | [tests/integration/component_runtime.py](../../../../../tests/integration/component_runtime.py), [CMakeLists.txt](../../../../../CMakeLists.txt) |
