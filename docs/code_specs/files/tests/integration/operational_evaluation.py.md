# `tests/integration/operational_evaluation.py` — block usage map

[Source](../../../../../tests/integration/operational_evaluation.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `6565b67dfd495bc5c7e2b1837ee43be2996c423c75ffa02bb37f583583e7159a`. 123 lines partitioned into 5 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–19](../../../../../tests/integration/operational_evaluation.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | growth insert; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 20–22](../../../../../tests/integration/operational_evaluation.py#L20) | Callable definition: def hashes(directory): | calls str, relative_to, sha256, read_bytes; returns {str(path.relative_to(directory)): hashlib.sha256(path.read_bytes()).hexdigest(); 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 23–24](../../../../../tests/integration/operational_evaluation.py#L23) | Explanatory comments or spacing. |  |
| [B0004 · 25–119](../../../../../tests/integration/operational_evaluation.py#L25) | Callable definition: def main(): | calls require, len, in, Path; guard require(len(sys.argv) in (8, 9), 'usage: operational_evaluation.py BUILD CROWN COLLECTOR SET ROWS S…; returns child; growth new; 13 loop sites; source comment (unverified): # Corrupt an actual native cardinality frame, retaining its real source and · [reviewed contract](#b0004) |
| [B0005 · 120–123](../../../../../tests/integration/operational_evaluation.py#L120) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0005) |

## B0001

[Lines 1–19](../../../../../tests/integration/operational_evaluation.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L19:sha256:baa2776478eaee1498bad43c10e4ca97955e4ce38606799045c9ac3d7bff25a4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the actual native/oracle integration regression and local helper dependencies. |
| inputs / outputs | Imports standard file/process/hash support and current cohort/evaluator/report-check APIs. |
| invariants | Later tests use real compiled adapters, not source grep, invented timing or assertions-only checks. |
| ownership | Test DTOs/files belong to the Python process; native queries remain child-owned. |
| failure | Import failures fail the test rather than skipping it. |
| cost | Cold regression setup, outside performance acceptance. |
| Design | [tests/integration/component_runtime.py](../../../../../tests/integration/component_runtime.py), [tools/run_operational_evaluation.py](../../../../../tools/run_operational_evaluation.py), [tools/component_workloads.py](../../../../../tools/component_workloads.py), [docs/component_evaluation.md](../../../../component_evaluation.md) |

## B0002

[Lines 20–22](../../../../../tests/integration/operational_evaluation.py#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L22:sha256:7750dcd655588c87ea26437917f2c436aba4c1c6787474a86fb27ee3fbfb8c61
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot accepted packet and durable-state bytes before rejected reuse. |
| inputs / outputs | Directory produces relative regular-file SHA256 entries. |
| invariants | Content checks include raw reports, experiment and actual state, not only status flags. |
| ownership | Read-only input tree and a parent digest dictionary. |
| failure | Read/hash failure fails the regression. |
| cost | One traversal of retained file bytes; test-only cost. |
| Design | [tests/integration/operational_evaluation.py](../../../../../tests/integration/operational_evaluation.py), [docs/component_evaluation.md](../../../../component_evaluation.md) |

## B0004

[Lines 25–119](../../../../../tests/integration/operational_evaluation.py#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L119:sha256:ed697bbb6a36ce3df6aa62b16c576470a0eb4e93cc1bc757248ad47f6b6c089c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise all operational adapters, gates and essential rejection controls with actual binaries. |
| inputs / outputs | Build/crown/collector/four-client paths and optional new artifact directory generate tiny cohorts and retain subprocess outputs/commands. |
| invariants | Requires all four adapters/axes, every primary/signed-service gate before timing, explicit owner/RSS sample scopes and no B04 acceptance. Corrupts a real cardinality frame to prove oracle rejection. Undeclared second factor rejects cold; genuine zero-memory preflight failure must retain diagnostics and launch no timing; completed output reuse preserves every byte. |
| ownership | Owns only fresh/temporary test artifacts. Report corruption touches a test-local copy, never native state; actual children own queries/WAL/sinks. |
| failure | Explicit require checks and expected ValueError are active without assertions. Unexpected child/timeout/oracle failure stops with diagnostics; temporary cleanup follows success only. |
| cost | Tiny finite invocations include diagnostic measure clocks, SHA and SQLite costs; this is behavioral/clock-path coverage, not controlled timing or the full production suite. |
| Design | [tools/run_operational_evaluation.py](../../../../../tools/run_operational_evaluation.py), [tools/component_workloads.py](../../../../../tools/component_workloads.py), [tests/integration/component_runtime.py](../../../../../tests/integration/component_runtime.py), [docs/component_evaluation.md](../../../../component_evaluation.md), [Refactor.md §14.4](../../../../../Refactor.md) |

## B0005

[Lines 120–123](../../../../../tests/integration/operational_evaluation.py#L120); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L120-L123:sha256:239f34ccf0a25c3afeefe82507f70b0ffbbcbf03dd6930292ca35d6b41937a29
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the integration test only as a script. |
| inputs / outputs | Module guard invokes main. |
| invariants | Importing definitions starts no child test. |
| ownership | Only interpreter-global definitions exist at this boundary. |
| failure | Uncaught test errors remain nonzero exits. |
| cost | Constant dispatch; no engine claim. |
| Design | [tests/integration/operational_evaluation.py](../../../../../tests/integration/operational_evaluation.py) |
