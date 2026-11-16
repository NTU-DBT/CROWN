# `tests/integration/baseline_evaluation.py` — block usage map

[Source](../../../../../tests/integration/baseline_evaluation.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `fb0b4ea27d5da89a7166847a647f0fabec6f1e1905a9f1a9d6efea982d03e292`. 118 lines partitioned into 5 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–19](../../../../../tests/integration/baseline_evaluation.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | growth insert; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 20–21](../../../../../tests/integration/baseline_evaluation.py#L20) | Callable definition: def hashes(path): | calls str, relative_to, sha256, read_bytes; returns {str(child.relative_to(path)):hashlib.sha256(child.read_bytes()).hexdigest() for child in path.rglo…; 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 22–23](../../../../../tests/integration/baseline_evaluation.py#L22) | Explanatory comments or spacing. |  |
| [B0004 · 24–114](../../../../../tests/integration/baseline_evaluation.py#L24) | Callable definition: def main(): | calls require, len, in, Path; guard require(len(sys.argv) in (6,7), 'usage: baseline_evaluation.py BUILD CROWN COLLECTOR SET AGGREGATE …; returns child; 14 loop sites; source comment (unverified): # Validate published text decoders independently of native JSON paths. · [reviewed contract](#b0004) |
| [B0005 · 115–118](../../../../../tests/integration/baseline_evaluation.py#L115) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0005) |

## B0001

[Lines 1–19](../../../../../tests/integration/baseline_evaluation.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L19:sha256:92eb06d30c4ff4b687702574a2d98591a02fb0bb281d944a3b0647fc221ddde9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the self-contained matched native/SQLite integration test. |
| inputs / outputs | Imports current cohort builder and actual legacy decoder plus file/process/hash helpers. |
| invariants | Optional published legacy binaries/JVM are not required; decoder tests alone do not claim executing those frameworks. |
| ownership | Test artifacts belong to a new/temporary directory; native state stays child-owned. |
| failure | Import failure fails the regression. |
| cost | Cold regression setup only, with no controlled timing attribution. |
| Design | [tests/integration/baseline_evaluation.py](../../../../../tests/integration/baseline_evaluation.py), [tools/run_baseline_evaluation.py](../../../../../tools/run_baseline_evaluation.py), [tools/component_workloads.py](../../../../../tools/component_workloads.py) |

## B0002

[Lines 20–21](../../../../../tests/integration/baseline_evaluation.py#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L20-L21:sha256:d6a87f4b6ff7db7be24a0e7b03ede3f8e091ca1c1482545e8590a94c7e915398
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture accepted evidence bytes before a rejected output-reuse attempt. |
| inputs / outputs | Directory yields relative file SHA256 values for every regular descendant. |
| invariants | Comparison covers actual receiving and raw files rather than status alone. |
| ownership | Read-only traversal and an ordinary digest dictionary. |
| failure | Read/hash failure fails the test. |
| cost | Proportional to retained bytes; test-only cost. |
| Design | [tests/integration/baseline_evaluation.py](../../../../../tests/integration/baseline_evaluation.py), [docs/component_evaluation.md](../../../../component_evaluation.md) |

## B0004

[Lines 24–114](../../../../../tests/integration/baseline_evaluation.py#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L114:sha256:ab91051f1f6ae22b844fdd0ce5548731df3928810681c5b374f2c7211c9dc855
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise actual matched native/SQLite gates and essential rejection controls. |
| inputs / outputs | Build/native paths and optional new artifact directory run nine real tiny arms, retain commands, inspect status/gate order and test published-text decoder examples. |
| invariants | All nine preflights precede timing; only incremental-vs-recomputation comparisons enter the self-contained test. Actual punctuation is accepted; malformed scalar/duplicate group/extra named-field/garbage cases reject. Direct SQLite bool/float pass counts reject. Fixed-column swaps and sparse CD observations fail cold; real zero-memory native preflight prevents timing; existing-output reuse preserves every byte. |
| ownership | Only fresh/temporary test files are owned. Real children own runtime resources; optional framework correctness is separately received by root. |
| failure | Explicit require and expected ValueError checks remain active without assertions. Unexpected child/timeout/source/gate failures stop with retained diagnostics. |
| cost | Finite actual process invocations and diagnostic measure clocks test behavior, not controlled speedups or full baseline/framework coverage. Temporary cleanup follows success. |
| Design | [tools/run_baseline_evaluation.py](../../../../../tools/run_baseline_evaluation.py), [tools/sqlite_component.py](../../../../../tools/sqlite_component.py), [tools/component_workloads.py](../../../../../tools/component_workloads.py), [docs/component_evaluation.md](../../../../component_evaluation.md), [docs/legacy_baselines.md](../../../../legacy_baselines.md) |

## B0005

[Lines 115–118](../../../../../tests/integration/baseline_evaluation.py#L115); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L115-L118:sha256:239f34ccf0a25c3afeefe82507f70b0ffbbcbf03dd6930292ca35d6b41937a29
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the integration driver only when directly invoked. |
| inputs / outputs | Module-name guard invokes main. |
| invariants | Importing definitions launches no children. |
| ownership | Interpreter globals only at this boundary. |
| failure | Uncaught test failure remains nonzero. |
| cost | Constant dispatch, no query claim. |
| Design | [tests/integration/baseline_evaluation.py](../../../../../tests/integration/baseline_evaluation.py) |
