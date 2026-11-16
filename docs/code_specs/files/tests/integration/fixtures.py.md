# `tests/integration/fixtures.py` — block usage map

[Source](../../../../../tests/integration/fixtures.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `6bf42fb38ba53a36c78f70db4e57d45a1fa2e0882ee49db123fb6a3ed1bbf321`. 129 lines partitioned into 9 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../tests/integration/fixtures.py#L1) | Imports dependencies. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 14–18](../../../../../tests/integration/fixtures.py#L14) | Callable definition: def load_json(path: Path) -&gt; Any: | calls loads, read_text, except, RuntimeError; returns json.loads(path.read_text(encoding="utf-8")) · [reviewed contract](#b0002) |
| [B0003 · 19–20](../../../../../tests/integration/fixtures.py#L19) | Explanatory comments or spacing. |  |
| [B0004 · 21–40](../../../../../tests/integration/fixtures.py#L21) | Callable definition: def invoke(executable: str, command: str, document: Path, label: str) -&gt; Any: | calls run, str, RuntimeError, loads; returns json.loads(result.stdout) · [reviewed contract](#b0004) |
| [B0005 · 41–42](../../../../../tests/integration/fixtures.py#L41) | Explanatory comments or spacing. |  |
| [B0006 · 43–53](../../../../../tests/integration/fixtures.py#L43) | Callable definition: def compare(actual: Any, expected: Any, label: str) -&gt; None: | calls dumps, RuntimeError; returns raise RuntimeError(; source comment (unverified): # Python equality equates True with 1. Canonical JSON retains value types. · [reviewed contract](#b0006) |
| [B0007 · 54–55](../../../../../tests/integration/fixtures.py#L54) | Explanatory comments or spacing. |  |
| [B0008 · 56–121](../../../../../tests/integration/fixtures.py#L56) | Callable definition: def main() -&gt; int: | calls len, RuntimeError, Path, sorted; returns 0; 2 loop sites; source comment (unverified): # A canonical document must be a fixed point and preserve the · [reviewed contract](#b0008) |
| [B0009 · 122–129](../../../../../tests/integration/fixtures.py#L122) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0009) |

## B0001

[Lines 1–13](../../../../../tests/integration/fixtures.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

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
| Design | [tests/integration/fixtures.py](../../../../../tests/integration/fixtures.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 14–18](../../../../../tests/integration/fixtures.py#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def load_json(path: Path) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one UTF8 fixture as ordinary JSON. |
| inputs / outputs | Path to decoded JSON value. |
| invariants | Filesystem/JSON failures gain path context; UnicodeDecodeError is not translated. |
| ownership | Owns source text and JSON tree. |
| failure | OSError/JSONDecodeError become chained RuntimeError; other failures propagate. |
| cost | Whole-file read and parse; memory proportional to fixture bytes. |
| Design | [tests/integration/fixtures.py](../../../../../tests/integration/fixtures.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 21–40](../../../../../tests/integration/fixtures.py#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def invoke(executable: str, command: str, document: Path, label: str) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one direct-CQ CLI command and decode its complete JSON stdout. |
| inputs / outputs | Executable, command, document and diagnostic label to parsed value. |
| invariants | Requires zero exit; does not set a subprocess timeout or validate stderr on success. |
| ownership | Owns complete captured stdout/stderr and parsed JSON. |
| failure | Nonzero exit or malformed JSON becomes contextual RuntimeError; launch/encoding failures propagate. |
| cost | One child process plus whole captured streams and JSON decode; no native-work or byte cap. |
| Design | [tests/integration/fixtures.py](../../../../../tests/integration/fixtures.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 43–53](../../../../../tests/integration/fixtures.py#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def compare(actual: Any, expected: Any, label: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare canonical pretty JSON while preserving boolean versus numeric spelling. |
| inputs / outputs | Actual/expected values and label to success or mismatch. |
| invariants | JSON text equality avoids Python True==1; object order is sorted, list order retained. |
| ownership | Owns both formatted JSON strings and mismatch diagnostic. |
| failure | Mismatch raises RuntimeError; serialization/encoding/allocation failures propagate. |
| cost | Serializes both full trees and sorts object keys; retained text proportional to both encodings. |
| Design | [tests/integration/fixtures.py](../../../../../tests/integration/fixtures.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 56–121](../../../../../tests/integration/fixtures.py#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main() -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check hand-calculated direct-CQ fixtures and canonicalization fixed points. |
| inputs / outputs | CLI and fixture-directory arguments to count of passed fixtures and process result. |
| invariants | Each input has a separate expected document; four child invocations check original oracle, canonical export, fixed point and repeated oracle. |
| ownership | TemporaryDirectory owns rewritten canonical files; expected trees remain ordinary Python values. |
| failure | Missing arguments/fixtures/expected data or mismatch fails; temporary files clean up on unwind. |
| cost | Sorted fixture discovery; four child processes per fixture, full JSON comparisons; no performance theorem. |
| Design | [tests/integration/fixtures.py](../../../../../tests/integration/fixtures.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 122–129](../../../../../tests/integration/fixtures.py#L122); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke the test campaign once when launched as a script. |
| inputs / outputs | Module execution mode to main invocation and process exit. |
| invariants | Native executable is not launched by importing these definitions; entry wrappers only translate test failure status. |
| ownership | Process owns campaign temporaries; persistent EXPLAIN evidence remains, workflow TemporaryDirectory data is scoped. |
| failure | RuntimeError is rendered to stderr and status 1; other exception types propagate. |
| cost | One explicit campaign; no native hot-path handler or retry added. |
| Design | [tests/integration/fixtures.py](../../../../../tests/integration/fixtures.py), [CMakeLists.txt](../../../../../CMakeLists.txt), [docs/cli.md](../../../../cli.md), [docs/code_review.md](../../../../code_review.md) |
