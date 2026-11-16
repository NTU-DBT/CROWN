# `tests/integration/cost_calibration.py` — block usage map

[Source](../../../../../tests/integration/cost_calibration.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `73087294fabd72c9752d7510bf753f266f0b43bba41a93814ebbf58617e4774b`. 81 lines partitioned into 7 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../tests/integration/cost_calibration.py#L1) | Imports dependencies. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 8–9](../../../../../tests/integration/cost_calibration.py#L8) | Callable definition: def require(value,message): | calls RuntimeError; guard def require(value,message): · [reviewed contract](#b0002) |
| [B0003 · 10–10](../../../../../tests/integration/cost_calibration.py#L10) | Callable definition: def key(value):return json.dumps(value,sort_keys=True,ensure_ascii=False,separators=(',',':')) | calls dumps; returns json.dumps(value,sort_keys=True,ensure_ascii=False,separators=(',',':')) · [reviewed contract](#b0003) |
| [B0004 · 11–15](../../../../../tests/integration/cost_calibration.py#L11) | Callable definition: def run(command,raw_path=None): | calls str, require, write_text, loads; guard require(result.returncode==0,f'{command}: {result.stderr\[-1500:\]}'); returns json.loads(result.stdout); 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 16–16](../../../../../tests/integration/cost_calibration.py#L16) | Callable definition: def fraction(value):return Fraction(value\['numerator'\],value\['denominator'\]) | calls Fraction; returns Fraction(value\['numerator'\],value\['denominator'\]) · [reviewed contract](#b0005) |
| [B0006 · 17–78](../../../../../tests/integration/cost_calibration.py#L17) | Callable definition: def main(): | calls require, len, Path, resolve; guard require(len(sys.argv) in \[4,5\],'usage: CALIBRATOR CROWN SOURCE \[ARTIFACT_DIRECTORY\]'); returns 0; 15 loop sites · [reviewed contract](#b0006) |
| [B0007 · 79–81](../../../../../tests/integration/cost_calibration.py#L79) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |

## B0001

[Lines 1–7](../../../../../tests/integration/cost_calibration.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:c08c07c7ff9de6464982842e54208e780657e21c24c43822f389753ce1b1ea1d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for cost_calibration.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/integration/cost_calibration.py](../../../../../tests/integration/cost_calibration.py), [docs/maintenance_cost.md](../../../../maintenance_cost.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–9](../../../../../tests/integration/cost_calibration.py#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(value,message):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce a calibration-test expectation with an explicit runtime check. |
| inputs / outputs | Truth-tests value and returns None on success; message becomes the RuntimeError text on failure. |
| invariants | Uses an if statement, so checks remain active under python -O. |
| ownership | Borrows value and message; does not change the compared report or fixture. |
| failure | Raises RuntimeError only when value is false; truth conversion itself may raise. |
| cost | One truth conversion; message formatting has already happened at the caller. |
| Design | [tests/integration/cost_calibration.py](../../../../../tests/integration/cost_calibration.py), [docs/measurement.md](../../../../measurement.md), [schemas/cost-calibration-v1.schema.json](../../../../../schemas/cost-calibration-v1.schema.json) |

## B0003

[Lines 10–10](../../../../../tests/integration/cost_calibration.py#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def key(value):return json.dumps(value,sort_keys=True,ensure_ascii=False,separators=(',',':'))
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize fixture/report values to compact sorted-key JSON text for hashing and row comparisons. |
| inputs / outputs | Accepts JSON-serializable value; returns str with Unicode characters unescaped and no separator whitespace. |
| invariants | Object keys are sorted; list order and JSON scalar types remain significant. Default json.dumps nonfinite-number behavior is not tightened here. |
| ownership | Creates text without modifying value; nested input containers remain caller-owned. |
| failure | json.dumps raises for unsupported values, cycles or incompatible keys. |
| cost | Traverses the serialized value, sorts each object and allocates the complete string. |
| Design | [tests/integration/cost_calibration.py](../../../../../tests/integration/cost_calibration.py), [docs/measurement.md](../../../../measurement.md), [schemas/cost-calibration-v1.schema.json](../../../../../schemas/cost-calibration-v1.schema.json) |

## B0004

[Lines 11–15](../../../../../tests/integration/cost_calibration.py#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def run(command,raw_path=None):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute a calibration/CLI command and decode its successful stdout report. |
| inputs / outputs | Stringifies each command element, runs with captured text streams and a 180-second timeout; optionally writes stdout to raw_path before JSON decoding. Returns the decoded JSON value. |
| invariants | Requires exit code zero; it does not require empty stderr or a top-level object. A raw artifact can exist even if JSON decoding later fails. |
| ownership | Subprocess.run waits and closes its communication pipes; returned JSON is newly decoded. Caller owns any raw output file and command sequence. |
| failure | TimeoutExpired, process-launch OSError, file-write errors and JSONDecodeError propagate; nonzero exit becomes RuntimeError including the stderr suffix. |
| cost | One child process plus full stdout/stderr buffering, optional file I/O and a full JSON parse; child calibration work dominates conversion overhead. |
| Design | [tests/integration/cost_calibration.py](../../../../../tests/integration/cost_calibration.py), [docs/measurement.md](../../../../measurement.md), [schemas/cost-calibration-v1.schema.json](../../../../../schemas/cost-calibration-v1.schema.json) |

## B0005

[Lines 16–16](../../../../../tests/integration/cost_calibration.py#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def fraction(value):return Fraction(value['numerator'],value['denominator'])
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read an exact report coefficient or estimate as a Python rational. |
| inputs / outputs | Expects mapping fields numerator and denominator accepted by Fraction; returns a reduced Fraction. |
| invariants | Does not round through float; zero denominator is invalid and normalization may change the stored pair representation. |
| ownership | Reads fields and creates a new rational, leaving the report unchanged. |
| failure | Missing fields, unsupported operands or zero denominator propagate KeyError, type/value errors or ZeroDivisionError. |
| cost | Arbitrary-precision integer conversion and gcd reduction; cost depends on numerator/denominator bit lengths. |
| Design | [tests/integration/cost_calibration.py](../../../../../tests/integration/cost_calibration.py), [docs/measurement.md](../../../../measurement.md), [schemas/cost-calibration-v1.schema.json](../../../../../schemas/cost-calibration-v1.schema.json) |

## B0006

[Lines 17–78](../../../../../tests/integration/cost_calibration.py#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check each workflow calibration report against independent SQL fixtures, raw phase counters and reproducible exact coefficient arithmetic. |
| inputs / outputs | Takes CALIBRATOR CROWN SOURCE and optional new artifact directory; loads manifest/schema/order, binds catalog hashes into temporary event files, validates all candidate reports and prints one success line per case. Returns 0. |
| invariants | Checks backend/mode, event/delta/snapshot counts, per-phase units, coefficient provenance, fit rank/residuals and decomposed rational totals; explicitly checks the report disclaims WAL/sink and held-out claims. This verifies the replay profile, not predictive performance. |
| ownership | Decoded fixture events are locally mutated to set catalog_sha256; report data is read. TemporaryDirectory removes generated update files on normal/exceptional exit; explicit artifacts persist and are not rolled back. |
| failure | Usage/assertion failures use RuntimeError; schema, JSON, file, subprocess and numeric errors propagate to the entrypoint broad Exception handler, which prints and exits 1. exist_ok=False rejects an existing artifact directory. |
| cost | Per manifest case, runs catalog canonicalization and one calibrator child with two candidates/repetitions caps, fully reads fixtures/reports and scans every observation for each component; exact rational arithmetic grows with integer sizes and residual checks use floats. |
| Design | [tests/integration/cost_calibration.py](../../../../../tests/integration/cost_calibration.py), [docs/measurement.md](../../../../measurement.md), [schemas/cost-calibration-v1.schema.json](../../../../../schemas/cost-calibration-v1.schema.json) |

## B0007

[Lines 79–81](../../../../../tests/integration/cost_calibration.py#L79); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__=='__main__':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Check each workflow calibration report against independent SQL fixtures, raw phase counters and reproducible exact coefficient arithmetic. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Pass the delegated return value to Python SystemExit; main controls that explicit exit status. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | The process boundary formats only Exception to stdout, as shown in the source, then raises SystemExit(1). SystemExit/KeyboardInterrupt and unlisted exceptions are not converted; diagnostic I/O/allocation failure can still propagate. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. Failure formatting costs its actual diagnostic bytes. |
| Design | [tests/integration/cost_calibration.py](../../../../../tests/integration/cost_calibration.py), [docs/development.md](../../../../development.md), [docs/measurement.md](../../../../measurement.md), [schemas/cost-calibration-v1.schema.json](../../../../../schemas/cost-calibration-v1.schema.json) |
