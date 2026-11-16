# `tests/integration/measurement_harness.py` — block usage map

[Source](../../../../../tests/integration/measurement_harness.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `352c63fb2b1c82742761407f502cd2b162804d9dcf26d95dfca5ffc94e5e96cf`. 105 lines partitioned into 4 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../tests/integration/measurement_harness.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | 1 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 8–9](../../../../../tests/integration/measurement_harness.py#L8) | Callable definition: def require(value,message): | calls RuntimeError; guard def require(value,message): · [reviewed contract](#b0002) |
| [B0003 · 10–102](../../../../../tests/integration/measurement_harness.py#L10) | Callable definition: def main(): | calls require, len, map, Path; guard require(len(sys.argv) in \[5,6\],'usage: measurement_harness.py CROWN COLLECTOR SOURCE BUILD \[ARTIFAC…; returns result; growth insert; 23 loop sites · [reviewed contract](#b0003) |
| [B0004 · 103–105](../../../../../tests/integration/measurement_harness.py#L103) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0004) |

## B0001

[Lines 1–7](../../../../../tests/integration/measurement_harness.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
sys.dont_write_bytecode=True
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Disable Python bytecode writes in the measurement integration process. |
| inputs / outputs | Sets sys.dont_write_bytecode=True before the separately guarded measurement main parses its executable/source/build arguments. |
| invariants | This affects the current interpreter only; it is not evidence that observations or measurement files are suppressed. |
| ownership | The process owns interpreter state; delegated main owns command processes and artifacts. |
| failure | Dependency imports can fail before the process-setting assignment. This span has no local catch; later guarded main failures retain their separate entry contract. |
| cost | Imports and one interpreter-state assignment; no explicit fixture write, build or child-process launch in this setup span. Import machinery can read/cache modules. |
| Design | [tests/integration/measurement_harness.py](../../../../../tests/integration/measurement_harness.py), CMakeLists.txt:1171, tests/integration/measurement_harness.py:1-7 |

## B0002

[Lines 8–9](../../../../../tests/integration/measurement_harness.py#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(value,message):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject a measurement protocol, provenance or distribution mismatch. |
| inputs / outputs | Truth-tests value; returns None or raises RuntimeError(message). |
| invariants | Explicit checks remain enabled under -O; individual conditions define the finite acceptance claim. |
| ownership | Borrows inputs without changing reports, packets or child records. |
| failure | False predicate raises RuntimeError; errors constructing/evaluating it happen in the caller. |
| cost | One truth conversion after the caller performs traversal or hashing. |
| Design | [tests/integration/measurement_harness.py](../../../../../tests/integration/measurement_harness.py), [docs/measurement.md](../../../../measurement.md), [schemas/measurement-experiment-v1.schema.json](../../../../../schemas/measurement-experiment-v1.schema.json) |

## B0003

[Lines 10–102](../../../../../tests/integration/measurement_harness.py#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify B03 controlled measurement gates, v2 raw accounting, target-RSS isolation, disabled metrics and explicit failures. |
| inputs / outputs | CTest binary/source/build arguments in; fresh controlled packet, raw reports and command ledgers under build-owned or temporary artifacts. |
| invariants | Validates raw reports with schema v2 while experiment packet/request schemas keep their own versions. Exercises 12 mode/backend cases x3 retained runs, independent rows, accounting, disabled metrics, timeout, and two RSS probes around a retained 64 MiB Python buffer. \`checks\` in the PASS text counts top-level wrapper calls plus the separately invoked timeout and two RSS probes. |
| ownership | Test owns/captures report files and subprocess outputs; temporary directory is explicitly cleaned on successful completion. |
| failure | Predicate failures raise RuntimeError; subprocess timeout/status/JSON/schema/file errors propagate and can leave artifacts. Target RSS must not inherit the retained parent buffer; launcher RSS remains separately recorded. |
| cost | Runs selected finite native configurations and helper probes; allocates 64 MiB in the parent for the RSS isolation check. This is test overhead, not measurement-engine overhead. |
| Design | [tests/integration/measurement_harness.py](../../../../../tests/integration/measurement_harness.py), [tools/run_measurements.py](../../../../../tools/run_measurements.py), [schemas/workload-measurement-v2.schema.json](../../../../../schemas/workload-measurement-v2.schema.json), [schemas/measurement-experiment-v1.schema.json](../../../../../schemas/measurement-experiment-v1.schema.json), [CMakeLists.txt](../../../../../CMakeLists.txt) |

## B0004

[Lines 103–105](../../../../../tests/integration/measurement_harness.py#L103); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__=='__main__':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Verify controlled measurement correctness gates, raw accounting, disabled-observation behavior and explicit failure records. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Ignore the delegated return value; a normal return completes through the interpreter. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | The process boundary formats only Exception to stderr, as shown in the source, then raises SystemExit(1). SystemExit/KeyboardInterrupt and unlisted exceptions are not converted; diagnostic I/O/allocation failure can still propagate. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. Failure formatting costs its actual diagnostic bytes. |
| Design | [tests/integration/measurement_harness.py](../../../../../tests/integration/measurement_harness.py), [docs/development.md](../../../../development.md), [docs/measurement.md](../../../../measurement.md), [schemas/measurement-experiment-v1.schema.json](../../../../../schemas/measurement-experiment-v1.schema.json) |
