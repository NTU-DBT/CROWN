# `tests/integration/installed_ranking_evaluation.py` — block usage map

[Source](../../../../../tests/integration/installed_ranking_evaluation.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `0d1e406f7ffb8ae5115d5ef8c137ddd8c29ee61aec2c4fad30b25042fae78e7a`. 64 lines partitioned into 5 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../tests/integration/installed_ranking_evaluation.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 7–8](../../../../../tests/integration/installed_ranking_evaluation.py#L7) | Callable definition: def require(value,message): | calls RuntimeError; guard def require(value,message): · [reviewed contract](#b0002) |
| [B0003 · 9–9](../../../../../tests/integration/installed_ranking_evaluation.py#L9) | Callable definition: def key(value):return json.dumps(value,sort_keys=True,separators=(',',':'),ensure_ascii=False) | calls dumps; returns json.dumps(value,sort_keys=True,separators=(',',':'),ensure_ascii=False) · [reviewed contract](#b0003) |
| [B0004 · 10–61](../../../../../tests/integration/installed_ranking_evaluation.py#L10) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, Path; guard (base/'commands.json').write_text(json.dumps(commands,indent=2)+'\n');require(p.returncode==0,f'{co…; returns p; jsonschema.Draft202012Validator(schema,resolver=resolver); growth insert; 14 loop sites · [reviewed contract](#b0004) |
| [B0005 · 62–64](../../../../../tests/integration/installed_ranking_evaluation.py#L62) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0005) |

## B0001

[Lines 1–6](../../../../../tests/integration/installed_ranking_evaluation.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
sys.dont_write_bytecode=True
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Disable Python bytecode writes in the installed-ranking integration process. |
| inputs / outputs | Sets sys.dont_write_bytecode=True before the separately guarded main parses source/build/compiler/sanitizer arguments. |
| invariants | The setting is process-wide for this Python process and does not mean the native evaluator is disabled or import-safe. |
| ownership | Interpreter state is process-owned and disappears at process exit; delegated main owns its subprocess/artifacts. |
| failure | Dependency imports can fail before the process-setting assignment. This span has no local catch; later guarded main failures retain their separate entry contract. |
| cost | Imports and one interpreter-state assignment; no explicit fixture write, build or child-process launch in this setup span. Import machinery can read/cache modules. |
| Design | [tests/integration/installed_ranking_evaluation.py](../../../../../tests/integration/installed_ranking_evaluation.py), CMakeLists.txt:1181, tests/integration/installed_ranking_evaluation.py:1-6 |

## B0002

[Lines 7–8](../../../../../tests/integration/installed_ranking_evaluation.py#L7); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(value,message):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check an installed ranking/export acceptance predicate. |
| inputs / outputs | Truth-tests value and returns None, or raises RuntimeError(message). |
| invariants | Explicit runtime checking survives python -O. |
| ownership | Borrows message/value; no artifact or report mutation. |
| failure | False predicate raises RuntimeError; unusual truth-conversion errors propagate. |
| cost | One condition test; constructing caller diagnostics can cost more. |
| Design | [tests/integration/installed_ranking_evaluation.py](../../../../../tests/integration/installed_ranking_evaluation.py), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/measurement.md](../../../../measurement.md) |

## B0003

[Lines 9–9](../../../../../tests/integration/installed_ranking_evaluation.py#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def key(value):return json.dumps(value,sort_keys=True,separators=(',',':'),ensure_ascii=False)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode JSON request/artifact/row values as deterministic compact text. |
| inputs / outputs | Returns sorted-key str with literal Unicode and compact separators for JSON-serializable input. |
| invariants | Preserves arrays and scalar distinctions; default JSON float permissiveness is unchanged. |
| ownership | Creates text while sharing no new ownership of source containers. |
| failure | json.dumps rejects unsupported objects, cycles or incompatible key ordering. |
| cost | Traverses the value, sorts object keys and holds the full result string. |
| Design | [tests/integration/installed_ranking_evaluation.py](../../../../../tests/integration/installed_ranking_evaluation.py), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/measurement.md](../../../../measurement.md) |

## B0004

[Lines 10–61](../../../../../tests/integration/installed_ranking_evaluation.py#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify moved installed ranking exporter candidates with the moved collector and independent train-trace oracles. |
| inputs / outputs | Source/build/compiler/sanitizer arguments in; relocated prefix/consumer and ranking candidate raw/export records out. |
| invariants | Validates raw collector reports against v2 schema while request/reporting packet versions remain independently defined. Recomputes candidates over the finite installed train-trace cases. |
| ownership | Test owns temporary installed consumer/build/output files; source ranking pack is read-only. |
| failure | Install, schema, candidate or oracle mismatch fails; subprocess/IO/schema errors propagate. |
| cost | Builds/uses the relocated consumer and executes finite candidate/report checks. |
| Design | [tests/integration/installed_ranking_evaluation.py](../../../../../tests/integration/installed_ranking_evaluation.py), [schemas/workload-measurement-v2.schema.json](../../../../../schemas/workload-measurement-v2.schema.json), [schemas/ranking-export-v1.schema.json](../../../../../schemas/ranking-export-v1.schema.json), [examples/workload-measurement/CMakeLists.txt](../../../../../examples/workload-measurement/CMakeLists.txt) |

## B0005

[Lines 62–64](../../../../../tests/integration/installed_ranking_evaluation.py#L62); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__=='__main__':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Verify moved installed ranking exporter candidates with the moved collector and independent train-trace oracles. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Ignore the delegated return value; a normal return completes through the interpreter. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | The process boundary formats only Exception to stderr, as shown in the source, then raises SystemExit(1). SystemExit/KeyboardInterrupt and unlisted exceptions are not converted; diagnostic I/O/allocation failure can still propagate. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. Failure formatting costs its actual diagnostic bytes. |
| Design | [tests/integration/installed_ranking_evaluation.py](../../../../../tests/integration/installed_ranking_evaluation.py), [docs/development.md](../../../../development.md), [docs/ranking_evaluation.md](../../../../ranking_evaluation.md), [docs/measurement.md](../../../../measurement.md) |
