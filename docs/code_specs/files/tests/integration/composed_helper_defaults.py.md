# `tests/integration/composed_helper_defaults.py` — block usage map

[Source](../../../../../tests/integration/composed_helper_defaults.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `d7eb874ac5b059d948b67929089eb40e30c9ae3d8a0c9c183827922083e852af`. 74 lines partitioned into 5 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../tests/integration/composed_helper_defaults.py#L1) | Imports dependencies; declares aliases. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 16–50](../../../../../tests/integration/composed_helper_defaults.py#L16) | Callable definition: def query_fixture(): | calls in, enumerate; returns {"schema_version": 2, "artifact": "crown_explain", "kind": "query",; 6 loop sites · [reviewed contract](#b0002) |
| [B0003 · 51–52](../../../../../tests/integration/composed_helper_defaults.py#L51) | Explanatory comments or spacing. |  |
| [B0004 · 53–68](../../../../../tests/integration/composed_helper_defaults.py#L53) | Callable definition: def check(source): | calls TemporaryDirectory, Path, mkdir, write_text; guard def check(source):; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 69–74](../../../../../tests/integration/composed_helper_defaults.py#L69) | declares values/defaults or compile-time conditions. | guard check(parser.parse_args().source.resolve()) · [reviewed contract](#b0005) |

## B0001

[Lines 1–15](../../../../../tests/integration/composed_helper_defaults.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:6640162ac13e3217fd5ce367e580284e57776c1eb9765a7f4d148d45f09a97d6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Import standalone checker-path test dependencies and state transport scope. |
| inputs / outputs | Stdlib CLI/JSON/subprocess/path/temp helpers become available. |
| invariants | Fixture JSON tests closed shape and invocation only; its editable certificate labels confer no native proof authority. |
| ownership | Module names only; temporary values are created in later functions. |
| failure | Import failures propagate. |
| cost | Import-time module setup; no native execution. |
| Design | [tests/integration/composed_helper_defaults.py](../../../../../tests/integration/composed_helper_defaults.py), [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [docs/observability.md](../../../../observability.md) |

## B0002

[Lines 16–50](../../../../../tests/integration/composed_helper_defaults.py#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L50:sha256:d35ab283b136bbe3fce96a6e22b3c5c3ac5b9c1d33c9b2db8fd1ed931f657d82
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a synthetic structural-negative query transport fixture. |
| inputs / outputs | Return one closed v2 query explain object with triangle binding, explicit synthetic certificate label and fixed scope metadata. |
| invariants | This is editable transport for schema/path checks; typed proof authority is not manufactured or passed to a planner. |
| ownership | Returned Python containers own all fixture values. |
| failure | Allocation/encoding consumer failures propagate; this constructor performs no validation. |
| cost | Fixed small object construction with three tables/atoms. |
| Design | [tests/integration/composed_helper_defaults.py](../../../../../tests/integration/composed_helper_defaults.py), [schemas/explain-report-v2.schema.json](../../../../../schemas/explain-report-v2.schema.json), [schemas/query-explain-v1.schema.json](../../../../../schemas/query-explain-v1.schema.json) |

## B0004

[Lines 53–68](../../../../../tests/integration/composed_helper_defaults.py#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L68:sha256:fecd397bb21597860163932aaf1354b028beba22fdcec0f0c41616e6b06678de
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise standalone defaults and absolute/relative schema overrides away from repository cwd. |
| inputs / outputs | Write one synthetic corpus member; run actual checker three times with inherited environment and bytecode disabled; require exit0 and exact pass count. |
| invariants | Only path resolution and closed transport checks are tested. Both default repo-root and schema-dir must follow the script; explicit relative schema path follows supplied repo-root. |
| ownership | TemporaryDirectory owns corpus/cwd; subprocess captures remain Python-owned until each assertion. |
| failure | Subprocess launch/30-second timeout/I/O failures propagate; unexpected status/output fails assertions. |
| cost | Three offline Python processes and complete small schema/fixture reads; no native producer or query maintenance. |
| Design | [tests/integration/composed_helper_defaults.py](../../../../../tests/integration/composed_helper_defaults.py), [tools/support/check_composed_reports.py](../../../../../tools/support/check_composed_reports.py), [docs/observability.md](../../../../observability.md) |

## B0005

[Lines 69–74](../../../../../tests/integration/composed_helper_defaults.py#L69); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L69-L74:sha256:75c2fec67937b62bc171ba7804f884a8a734b0e4c13a96208684989ed408f362
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the standalone checker regression as a source-root CLI. |
| inputs / outputs | Main guard parses source Path, resolves it and invokes check. |
| invariants | Importing this module does not run the regression. |
| ownership | Parser/path values have process lifetime. |
| failure | Argparse and uncaught check errors fail the process. |
| cost | Fixed dispatch plus check. |
| Design | [tests/integration/composed_helper_defaults.py](../../../../../tests/integration/composed_helper_defaults.py), [CMakeLists.txt](../../../../../CMakeLists.txt) |
