# `tools/sqlite_component.py` — block usage map

[Source](../../../../tools/sqlite_component.py) · [Source index](../../README.md) · [Subsystem contracts](../../subsystem_contracts.md) · [Reviewed primitives](../../primitives.md)

Generate reproducible inputs or inspect/build/run evidence artifacts under explicit command-line arguments.

Snapshot SHA-256: `43985bea8579ea98f1ad182ae773618798bd4ca95dfa7f36d32f697d74786b8c`. 108 lines partitioned into 3 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tools](../../subsystem_contracts.md#tools). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/native_build.md](../../../native_build.md), [docs/measurement.md](../../../measurement.md), [docs/reference_fuzz.md](../../../reference_fuzz.md), [docs/workloads.md](../../../workloads.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–17](../../../../tools/sqlite_component.py#L1) | Imports dependencies. | 1 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 18–104](../../../../tools/sqlite_component.py#L18) | Callable definition: def run(path): | calls monotonic_ns, require, stat, loads; guard require(path.stat().st_size &lt;= 64*1024**2, 'SQLite request exceeds 64MiB'); returns {'schema_version':1,'implementation':'sqlite_recomputation_v1','case_id':request\['case_id'\],; 14 loop sites; source comment (unverified): # Only generated pair-table cohorts enter this experimental adapter. SQL · [reviewed contract](#b0002) |
| [B0003 · 105–108](../../../../tools/sqlite_component.py#L105) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |

## B0001

[Lines 1–17](../../../../tools/sqlite_component.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L17:sha256:b0fe088293ea74abafee98da61fb5205a1cda631eafb301cfaef3a0840aa97b2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the separate full SQLite recomputation control. |
| inputs / outputs | Uses standard SQLite/file/JSON/hash/monotonic clock support and the existing explicit require helper. |
| invariants | This Python/SQLite process is a whole implementation, not a CROWN native operator or optimized-count theorem. |
| ownership | Interpreter/SQLite memory is process-owned and has no CROWN query-account attribution. |
| failure | Missing SQLite/import support fails the process. |
| cost | Interpreter/import startup belongs to process wall/RSS; per-service clocks begin in run. |
| Design | [docs/component_evaluation.md](../../../component_evaluation.md), [tools/run_baseline_evaluation.py](../../../../tools/run_baseline_evaluation.py), [Refactor.md §14.4](../../../../Refactor.md) |

## B0002

[Lines 18–104](../../../../tools/sqlite_component.py#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L104:sha256:efdd1079862750e769a4d4bb72c8fdcfd0b60194f71d19431c8a9da57f8cefcb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute the exact original query after every physical unit-set pair edit. |
| inputs / outputs | One bounded request yields fresh-database passes, per-event apply/full-output clocks and actual verify observations or measured counters. |
| invariants | Pass grants are exact ints; valid insertion/deletion chains are admitted cold and discarded before execution. Pair primary keys preserve set facts. Cardinality counts the actual DISTINCT subquery; L3 fully fetches rows and derives signed differences from consecutive full sets; groups expose fixed first-two-column keys. Every event remains observed and output/capture grants bound reporting. |
| ownership | Each pass owns an in-memory SQLite database; previous full sets and fetched rows are explicit Python recomputation state. Close is timed teardown; memory/account fields are null because no native account exists. |
| failure | Malformed counters/events/catalog, SQL/resource/capture failure propagates as process failure; no native result or zero fallback substitutes for the query. Normal close completes after all inputs. |
| cost | Updates and full SQL evaluation/fetch/Python comparison are charged in their actual clocks. Default SQLite transaction stays open until close, so no WAL/fsync/durable commitment is claimed. Process RSS includes interpreter, every database/pass and report. |
| Design | [tools/component_workloads.py](../../../../tools/component_workloads.py), [docs/component_evaluation.md](../../../component_evaluation.md), [docs/legacy_baselines.md](../../../legacy_baselines.md), [tests/integration/baseline_evaluation.py](../../../../tests/integration/baseline_evaluation.py) |

## B0003

[Lines 105–108](../../../../tools/sqlite_component.py#L105); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L105-L108:sha256:990c6926aee3c5c9503a4ff29225ec39a705d4a59799f8bbfbc76bcb6f66ee51
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the direct finite SQLite request command. |
| inputs / outputs | The script guard calls run on argv request and serializes one JSON report. |
| invariants | No native CROWN planner/runtime is selected; stdout is a report, not delivery authority. |
| ownership | Process termination owns final Python/SQLite cleanup; report memory is outside a native account. |
| failure | Uncaught adapter/I/O errors remain nonzero diagnostics; no retry framework is installed. |
| cost | Final JSON encoding is outside recorded service stages but inside process wall/RSS. |
| Design | [tools/sqlite_component.py](../../../../tools/sqlite_component.py), [tools/run_baseline_evaluation.py](../../../../tools/run_baseline_evaluation.py) |
