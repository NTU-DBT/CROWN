# `tests/integration/ranking_evaluation.py` — block usage map

[Source](../../../../../tests/integration/ranking_evaluation.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `3bccc8a6695b544a40b18c670b5fe25f765f0a9a77d8fc63af7261298ff8f12b`. 106 lines partitioned into 6 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../tests/integration/ranking_evaluation.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | 1 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 8–9](../../../../../tests/integration/ranking_evaluation.py#L8) | Callable definition: def require(value,message): | calls RuntimeError; guard def require(value,message): · [reviewed contract](#b0002) |
| [B0003 · 10–10](../../../../../tests/integration/ranking_evaluation.py#L10) | Callable definition: def fraction(value):return Fraction(int(value\['numerator'\]),int(value\['denominator'\])) | calls Fraction, int; returns Fraction(int(value\['numerator'\]),int(value\['denominator'\])) · [reviewed contract](#b0003) |
| [B0004 · 11–11](../../../../../tests/integration/ranking_evaluation.py#L11) | Callable definition: def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest() | calls sha256, read_bytes, hexdigest; returns hashlib.sha256(path.read_bytes()).hexdigest() · [reviewed contract](#b0004) |
| [B0005 · 12–103](../../../../../tests/integration/ranking_evaluation.py#L12) | Callable definition: def main(): | calls require, len, map, Path; guard require(len(sys.argv) in \[6,7\],'usage: ranking_evaluation.py CROWN EXPORTER COLLECTOR SOURCE BUILD …; returns result; jsonschema.Draft202012Validator(schema,resolver=resolver); growth insert; 30 loop sites · [reviewed contract](#b0005) |
| [B0006 · 104–106](../../../../../tests/integration/ranking_evaluation.py#L104) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0006) |

## B0001

[Lines 1–7](../../../../../tests/integration/ranking_evaluation.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
sys.dont_write_bytecode=True
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Disable Python bytecode writes in the ranking-evaluation integration process. |
| inputs / outputs | Sets sys.dont_write_bytecode=True before the separately guarded main reads executable/source/build arguments. |
| invariants | This describes interpreter setup only; it asserts no train/evaluation split or ranking result. |
| ownership | Python owns this process setting; delegated main owns its child processes and files. |
| failure | Dependency imports can fail before the process-setting assignment. This span has no local catch; later guarded main failures retain their separate entry contract. |
| cost | Imports and one interpreter-state assignment; no explicit fixture write, build or child-process launch in this setup span. Import machinery can read/cache modules. |
| Design | [tests/integration/ranking_evaluation.py](../../../../../tests/integration/ranking_evaluation.py), CMakeLists.txt:1179, tests/integration/ranking_evaluation.py:1-7 |

## B0002

[Lines 8–9](../../../../../tests/integration/ranking_evaluation.py#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(value,message):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce a held-out evaluation acceptance predicate. |
| inputs / outputs | Returns None when value is truthy, otherwise raises RuntimeError(message). |
| invariants | Uses an explicit runtime if rather than an optimizable assertion. |
| ownership | Borrows its operands; no report or artifact state is changed here. |
| failure | RuntimeError marks the supplied mismatch; truth conversion can propagate its own error. |
| cost | One condition test, excluding caller computation. |
| Design | [tests/integration/ranking_evaluation.py](../../../../../tests/integration/ranking_evaluation.py), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/measurement.md](../../../../measurement.md) |

## B0003

[Lines 10–10](../../../../../tests/integration/ranking_evaluation.py#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def fraction(value):return Fraction(int(value['numerator']),int(value['denominator']))
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recover an exact rational from serialized ranking cost/error fields. |
| inputs / outputs | Reads numerator and denominator, converts each with int, and returns Fraction. |
| invariants | No float intermediate is introduced; int conversion is permissive according to Python and this helper performs no schema/type validation itself. |
| ownership | Creates new integer/rational values and leaves the report mapping unchanged. |
| failure | Missing keys, int conversion errors and zero denominator propagate. |
| cost | Integer parsing plus gcd reduction and allocation scale with the operand bit/digit lengths. |
| Design | [tests/integration/ranking_evaluation.py](../../../../../tests/integration/ranking_evaluation.py), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/measurement.md](../../../../measurement.md) |

## B0004

[Lines 11–11](../../../../../tests/integration/ranking_evaluation.py#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash the complete current bytes of a report/provenance file. |
| inputs / outputs | Accepts a Path-like object exposing read_bytes; returns lowercase SHA-256 hex str. |
| invariants | Hashes raw file bytes, so whitespace or newline changes affect the digest. |
| ownership | Reads into a new complete bytes object and returns new text; file is opened/closed by Path.read_bytes. |
| failure | File I/O errors propagate; no missing-file fallback or digest authority is supplied. |
| cost | O(file bytes) read/hash time with full-file input allocation. |
| Design | [tests/integration/ranking_evaluation.py](../../../../../tests/integration/ranking_evaluation.py), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/measurement.md](../../../../measurement.md) |

## B0005

[Lines 12–103](../../../../../tests/integration/ranking_evaluation.py#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute held-out ranking evidence from controlled raw-v2 frames and frozen choices/calibration on disjoint physical-tuple splits. |
| inputs / outputs | CROWN EXPORTER COLLECTOR SOURCE BUILD and optional new persistent artifact directory; run the entire controlled C07 matrix, then independently validate split/choice/calibration/provenance/schema and exact rational regret/error values. |
| invariants | Every candidate is preflighted on five traces in three modes before calibration/evaluation timing; choices/calibration are frozen before held-out use. Current cohort has16 candidates across6 groups,240 preflights and576 retained warmup/measured runs,162 analyses and486 objective checks. No timing result changes native C05 choice or becomes proof of global runtime optimality. |
| ownership | Default TemporaryDirectory cleans artifacts on unwind; an explicit unused artifact directory retains partial or complete outputs for inspection. Python owns reports, exact Fractions and captured child streams. |
| failure | Each invoke uses the existing bounded subprocess path with1800-second wall limit; the enclosing CTest allows2400seconds. Status/schema/hash/independent recomputation mismatches fail directly. Root isolated sanitizer rerun uses an explicit persistent directory; no retry, skipped cohort or fallback is added to main. |
| cost | One full controlled runner (current240 native preflights plus576 retained measured/warmup runs and setup/exports), four subsequent malformed/constraint protocol controls, full report/schema/hash scans and486 exact rational regret/error checks. Offline acceptance work; raising wall limits adds no production engine overhead. |
| Design | [tests/integration/ranking_evaluation.py](../../../../../tests/integration/ranking_evaluation.py), [schemas/workload-measurement-v2.schema.json](../../../../../schemas/workload-measurement-v2.schema.json), [schemas/ranking-evaluation-v1.schema.json](../../../../../schemas/ranking-evaluation-v1.schema.json), [schemas/ranking-export-v1.schema.json](../../../../../schemas/ranking-export-v1.schema.json) |

## B0006

[Lines 104–106](../../../../../tests/integration/ranking_evaluation.py#L104); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__=='__main__':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Recompute the controlled ranking experiment evidence from raw frames and frozen choices/calibration on disjoint physical-tuple splits. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Ignore the delegated return value; a normal return completes through the interpreter. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | The process boundary formats only Exception to stderr, as shown in the source, then raises SystemExit(1). SystemExit/KeyboardInterrupt and unlisted exceptions are not converted; diagnostic I/O/allocation failure can still propagate. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. Failure formatting costs its actual diagnostic bytes. |
| Design | [tests/integration/ranking_evaluation.py](../../../../../tests/integration/ranking_evaluation.py), [docs/development.md](../../../../development.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/ranking.md](../../../../ranking.md), [docs/measurement.md](../../../../measurement.md), [tools/ranking_analysis.py](../../../../../tools/ranking_analysis.py) |
