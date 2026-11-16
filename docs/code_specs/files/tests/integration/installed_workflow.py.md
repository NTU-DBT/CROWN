# `tests/integration/installed_workflow.py` — block usage map

[Source](../../../../../tests/integration/installed_workflow.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `47f164ce798581741c86fbe262604ec3f4e9d09c0e121867bc98dc3b10200b82`. 54 lines partitioned into 5 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../tests/integration/installed_workflow.py#L1) | Imports dependencies. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 6–7](../../../../../tests/integration/installed_workflow.py#L6) | Callable definition: def require(value,message): | calls RuntimeError; guard def require(value,message): · [reviewed contract](#b0002) |
| [B0003 · 8–8](../../../../../tests/integration/installed_workflow.py#L8) | Callable definition: def key(value):return json.dumps(value,ensure_ascii=False,sort_keys=True,separators=(',',':')) | calls dumps; returns json.dumps(value,ensure_ascii=False,sort_keys=True,separators=(',',':')) · [reviewed contract](#b0003) |
| [B0004 · 9–51](../../../../../tests/integration/installed_workflow.py#L9) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, Path; guard require(result.returncode==0,f'{command}: {result.stderr\[-2500:\]} {result.stdout\[-2500:\]}'); returns result; 0; growth new; 11 loop sites · [reviewed contract](#b0004) |
| [B0005 · 52–54](../../../../../tests/integration/installed_workflow.py#L52) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0005) |

## B0001

[Lines 1–5](../../../../../tests/integration/installed_workflow.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#!/usr/bin/env python3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define an offline acceptance entry point and its explicit process/file dependencies. |
| inputs / outputs | Caller-supplied native executable and fixture paths; actual campaign is started only by module entry guard. |
| invariants | Source review is not a new execution result. Existing v14 campaign evidence is historical; this packet adds no runtime instrumentation. |
| ownership | Python module owns imported bindings, source constants and helper definitions; native ownership is exercised only in child processes. |
| failure | Import/dependency/encoding failures can precede the main diagnostic boundary. |
| cost | Import/definition and later explicit test work only; no production query cost. |
| Design | [tests/integration/installed_workflow.py](../../../../../tests/integration/installed_workflow.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md), [docs/code_review.md](../../../../code_review.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json), [schemas/compiled-workflow-v1.schema.json](../../../../../schemas/compiled-workflow-v1.schema.json), [schemas/workflow-report-v1.schema.json](../../../../../schemas/workflow-report-v1.schema.json), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp) |

## B0002

[Lines 6–7](../../../../../tests/integration/installed_workflow.py#L6); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(value,message):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail one workflow acceptance condition. |
| inputs / outputs | Condition/message to None or RuntimeError. |
| invariants | This is a test assertion, not native runtime admission. |
| ownership | Borrows condition/message until diagnostic construction. |
| failure | False raises RuntimeError. |
| cost | Constant branch apart from message construction. |
| Design | [tests/integration/installed_workflow.py](../../../../../tests/integration/installed_workflow.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md), [docs/code_review.md](../../../../code_review.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json), [schemas/compiled-workflow-v1.schema.json](../../../../../schemas/compiled-workflow-v1.schema.json), [schemas/workflow-report-v1.schema.json](../../../../../schemas/workflow-report-v1.schema.json), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp) |

## B0003

[Lines 8–8](../../../../../tests/integration/installed_workflow.py#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def key(value):return json.dumps(value,ensure_ascii=False,sort_keys=True,separators=(',',':'))
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode deterministic JSON identity for workflow values. |
| inputs / outputs | JSON value to sorted compact Unicode string. |
| invariants | Object order normalized; row/list order and JSON boolean/number syntax remain. |
| ownership | Owns encoded string; does not clone native data. |
| failure | JSON serialization/allocation failures propagate. |
| cost | Full value serialization and object-key sorting. |
| Design | [tests/integration/installed_workflow.py](../../../../../tests/integration/installed_workflow.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md), [docs/code_review.md](../../../../code_review.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json), [schemas/compiled-workflow-v1.schema.json](../../../../../schemas/compiled-workflow-v1.schema.json), [schemas/workflow-report-v1.schema.json](../../../../../schemas/workflow-report-v1.schema.json), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp) |

## B0004

[Lines 9–51](../../../../../tests/integration/installed_workflow.py#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Install then relocate a fresh SDK and execute a separately built public consumer. |
| inputs / outputs | Source/build/compiler/sanitizer arguments to moved-package and restart checks. |
| invariants | Original prefix disappears; compile commands exclude source/build headers; link text excludes testing/reference archives. Consumer run/restore is checked against fixture expectations and source positions. |
| ownership | TemporaryDirectory owns install, relocated prefix, external source/build and native state; all are removed on exit. |
| failure | Install/configure/build/run or oracle mismatch fails; outer test wrapper renders one failure and exits nonzero. |
| cost | Installation/copy, external compilation and child processes for every fixture; explicit offline acceptance cost, not query hot-path overhead. |
| Design | [tests/integration/installed_workflow.py](../../../../../tests/integration/installed_workflow.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md), [docs/code_review.md](../../../../code_review.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json), [schemas/compiled-workflow-v1.schema.json](../../../../../schemas/compiled-workflow-v1.schema.json), [schemas/workflow-report-v1.schema.json](../../../../../schemas/workflow-report-v1.schema.json), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp) |

```text
def run(command):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Capture one SDK/tool/consumer subprocess and require zero status. |
| inputs / outputs | Command sequence to CompletedProcess; appends command/exit record. |
| invariants | Every argument is converted to text; record appended only after subprocess returns. |
| ownership | Owns captured output and records; retains no child after completed run. |
| failure | 240-second timeout/launch errors propagate; nonzero gets bounded output-tail diagnostic. |
| cost | One child with complete captured streams; diagnostic tail limit does not bound capture memory. |
| Design | [tests/integration/installed_workflow.py](../../../../../tests/integration/installed_workflow.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md), [docs/code_review.md](../../../../code_review.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json), [schemas/compiled-workflow-v1.schema.json](../../../../../schemas/compiled-workflow-v1.schema.json), [schemas/workflow-report-v1.schema.json](../../../../../schemas/workflow-report-v1.schema.json), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp) |

## B0005

[Lines 52–54](../../../../../tests/integration/installed_workflow.py#L52); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__=='__main__':
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke the test campaign once when launched as a script. |
| inputs / outputs | Module execution mode to main invocation and process exit. |
| invariants | Native executable is not launched by importing these definitions; entry wrappers only translate test failure status. |
| ownership | Process owns campaign temporaries; persistent EXPLAIN evidence remains, workflow TemporaryDirectory data is scoped. |
| failure | Exception is rendered to stdout and status 1; SystemExit passes through. |
| cost | One explicit campaign; no native hot-path handler or retry added. |
| Design | [tests/integration/installed_workflow.py](../../../../../tests/integration/installed_workflow.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md), [docs/code_review.md](../../../../code_review.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json), [schemas/compiled-workflow-v1.schema.json](../../../../../schemas/compiled-workflow-v1.schema.json), [schemas/workflow-report-v1.schema.json](../../../../../schemas/workflow-report-v1.schema.json), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp) |
