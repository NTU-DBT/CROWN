# `tests/integration/workflow.py` — block usage map

[Source](../../../../../tests/integration/workflow.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `a5da6a10752b40aa52b23674d1db8c5cb8a47efcaed3dce9ea13825219ba4eb9`. 131 lines partitioned into 9 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../tests/integration/workflow.py#L1) | Imports dependencies. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 7–8](../../../../../tests/integration/workflow.py#L7) | Callable definition: def require(value,message): | calls RuntimeError; guard def require(value,message): · [reviewed contract](#b0002) |
| [B0003 · 9–9](../../../../../tests/integration/workflow.py#L9) | Callable definition: def key(value):return json.dumps(value,ensure_ascii=False,sort_keys=True,separators=(',',':')) | calls dumps; returns json.dumps(value,ensure_ascii=False,sort_keys=True,separators=(',',':')) · [reviewed contract](#b0003) |
| [B0004 · 10–10](../../../../../tests/integration/workflow.py#L10) | Callable definition: def rowset(rows):return {key(row) for row in rows} | calls key; returns {key(row) for row in rows}; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 11–11](../../../../../tests/integration/workflow.py#L11) | Callable definition: def digest(path):return hashlib.sha256(path.read_bytes()).hexdigest() | calls sha256, read_bytes, hexdigest; returns hashlib.sha256(path.read_bytes()).hexdigest() · [reviewed contract](#b0005) |
| [B0006 · 12–12](../../../../../tests/integration/workflow.py#L12) | Callable definition: def native_files(directory):return {p.name:digest(p) for p in directory.iterdir() if p.is_file() and (p.name.startswith('state.ro… | calls digest, iterdir, is_file, and; returns {p.name:digest(p) for p in directory.iterdir() if p.is_file() and (p.name.startswith('state.root') …; 1 loop sites · [reviewed contract](#b0006) |
| [B0007 · 13–13](../../../../../tests/integration/workflow.py#L13) | Explanatory comments or spacing. |  |
| [B0008 · 14–128](../../../../../tests/integration/workflow.py#L14) | Callable definition: def main(): | calls require, len, Path, resolve; guard require(len(sys.argv)==3,'usage: workflow.py EXECUTABLE SOURCE'); returns result; 0; 17 loop sites; source comment (unverified): # Constant false is an admitted empty operator, with no forged height proof. · [reviewed contract](#b0008) |
| [B0009 · 129–131](../../../../../tests/integration/workflow.py#L129) | declares callable signatures; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0009) |

## B0001

[Lines 1–6](../../../../../tests/integration/workflow.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

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
| Design | [tests/integration/workflow.py](../../../../../tests/integration/workflow.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md), [docs/code_review.md](../../../../code_review.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json), [schemas/compiled-workflow-v1.schema.json](../../../../../schemas/compiled-workflow-v1.schema.json), [schemas/workflow-report-v1.schema.json](../../../../../schemas/workflow-report-v1.schema.json), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp) |

## B0002

[Lines 7–8](../../../../../tests/integration/workflow.py#L7); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/integration/workflow.py](../../../../../tests/integration/workflow.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md), [docs/code_review.md](../../../../code_review.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json), [schemas/compiled-workflow-v1.schema.json](../../../../../schemas/compiled-workflow-v1.schema.json), [schemas/workflow-report-v1.schema.json](../../../../../schemas/workflow-report-v1.schema.json), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp) |

## B0003

[Lines 9–9](../../../../../tests/integration/workflow.py#L9); `callable`; `contains_scoped_manual_contract`.

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
| Design | [tests/integration/workflow.py](../../../../../tests/integration/workflow.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md), [docs/code_review.md](../../../../code_review.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json), [schemas/compiled-workflow-v1.schema.json](../../../../../schemas/compiled-workflow-v1.schema.json), [schemas/workflow-report-v1.schema.json](../../../../../schemas/workflow-report-v1.schema.json), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp) |

## B0004

[Lines 10–10](../../../../../tests/integration/workflow.py#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def rowset(rows):return {key(row) for row in rows}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare fixture rows using JSON identities. |
| inputs / outputs | Rows to set of key(row) strings. |
| invariants | Duplicates collapse here; call sites needing multiplicity also compare list lengths. |
| ownership | Owns encoded row strings and hash set. |
| failure | Malformed JSON-compatible values or allocation failures propagate. |
| cost | Touches every row/encoded byte; memory proportional to distinct encoded rows. |
| Design | [tests/integration/workflow.py](../../../../../tests/integration/workflow.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md), [docs/code_review.md](../../../../code_review.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json), [schemas/compiled-workflow-v1.schema.json](../../../../../schemas/compiled-workflow-v1.schema.json), [schemas/workflow-report-v1.schema.json](../../../../../schemas/workflow-report-v1.schema.json), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp) |

## B0005

[Lines 11–11](../../../../../tests/integration/workflow.py#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def digest(path):return hashlib.sha256(path.read_bytes()).hexdigest()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash exact on-disk workflow bytes. |
| inputs / outputs | Path to SHA256 hex. |
| invariants | Uses raw bytes without newline normalization. |
| ownership | Owns whole read buffer and digest string. |
| failure | Filesystem/allocation failures propagate. |
| cost | Whole-file read/hash; buffer proportional to file size. |
| Design | [tests/integration/workflow.py](../../../../../tests/integration/workflow.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md), [docs/code_review.md](../../../../code_review.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json), [schemas/compiled-workflow-v1.schema.json](../../../../../schemas/compiled-workflow-v1.schema.json), [schemas/workflow-report-v1.schema.json](../../../../../schemas/workflow-report-v1.schema.json), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp) |

## B0006

[Lines 12–12](../../../../../tests/integration/workflow.py#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def native_files(directory):return {p.name:digest(p) for p in directory.iterdir() if p.is_file() and (p.name.startswith('state.root') or p.name=='results.sink')}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Snapshot selected durable-file byte identities for rejection tests. |
| inputs / outputs | Directory to filename/hash dictionary. |
| invariants | Only top-level state.root-prefixed files and exact results.sink are included; this is not a whole-directory/sink-lock audit. |
| ownership | Owns Path iteration metadata, per-file buffers and digest map. |
| failure | Directory/read/hash failures propagate. |
| cost | Enumerates directory and reads the selected files completely. |
| Design | [tests/integration/workflow.py](../../../../../tests/integration/workflow.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md), [docs/code_review.md](../../../../code_review.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json), [schemas/compiled-workflow-v1.schema.json](../../../../../schemas/compiled-workflow-v1.schema.json), [schemas/workflow-report-v1.schema.json](../../../../../schemas/workflow-report-v1.schema.json), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp) |

## B0008

[Lines 14–128](../../../../../tests/integration/workflow.py#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise compiled SQL workflow, exact set epochs, restart and rejection immutability. |
| inputs / outputs | Executable/repository arguments to public CLI checks and final status. |
| invariants | Fixture hashes protect independent expectations; row counts plus JSON sets check duplicate-sensitive epochs/deltas. Repeated restore crosses real processes. |
| ownership | TemporaryDirectory owns generated events/artifacts/native files; Python owns schema and expected rows. |
| failure | Any failed predicate, child timeout, schema rejection or IO error reaches the script failure boundary. |
| cost | Many child processes per fixture and full file hashes/JSON validation; timing partition assertions are not a latency benchmark. |
| Design | [tests/integration/workflow.py](../../../../../tests/integration/workflow.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md), [docs/code_review.md](../../../../code_review.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json), [schemas/compiled-workflow-v1.schema.json](../../../../../schemas/compiled-workflow-v1.schema.json), [schemas/workflow-report-v1.schema.json](../../../../../schemas/workflow-report-v1.schema.json), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp) |

```text
def run(args,expected=0,code=None):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke one public workflow command and check its output channel/schema. |
| inputs / outputs | Argument list, expected success class and optional diagnostic code to CompletedProcess. |
| invariants | expected compares zero versus nonzero, not a particular nonzero code. Successful workflow report commands and all errors get schema validation; successful stderr must be empty. |
| ownership | Owns child stdout/stderr and parsed JSON; increments enclosing checks only after validation. |
| failure | 120-second timeout/launch/decode/schema/predicate failure propagates to main. |
| cost | One captured child plus complete output decode/validation; timeout is wall time, not a native work grant. |
| Design | [tests/integration/workflow.py](../../../../../tests/integration/workflow.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md), [docs/code_review.md](../../../../code_review.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json), [schemas/compiled-workflow-v1.schema.json](../../../../../schemas/compiled-workflow-v1.schema.json), [schemas/workflow-report-v1.schema.json](../../../../../schemas/workflow-report-v1.schema.json), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp) |

## B0009

[Lines 129–131](../../../../../tests/integration/workflow.py#L129); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

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
| failure | Exception is rendered to stderr and status 1; SystemExit passes through. |
| cost | One explicit campaign; no native hot-path handler or retry added. |
| Design | [tests/integration/workflow.py](../../../../../tests/integration/workflow.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md), [docs/code_review.md](../../../../code_review.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json), [schemas/compiled-workflow-v1.schema.json](../../../../../schemas/compiled-workflow-v1.schema.json), [schemas/workflow-report-v1.schema.json](../../../../../schemas/workflow-report-v1.schema.json), [examples/native-workflow/main.cpp](../../../../../examples/native-workflow/main.cpp) |
