# `tests/integration/parse_sql.py` — block usage map

[Source](../../../../../tests/integration/parse_sql.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `09749c13934626b46db23d85ba65cd34fffa2277afa0bb965da173dfe2937b6e`. 239 lines partitioned into 19 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../tests/integration/parse_sql.py#L1) | Imports dependencies. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 14–17](../../../../../tests/integration/parse_sql.py#L14) | Callable definition: def require(condition: bool, message: str) -&gt; None: | calls RuntimeError; guard def require(condition: bool, message: str) -&gt; None:; source comment (unverified): # Keep validation active when this script is invoked with \`\`python -O\`\`. · [reviewed contract](#b0002) |
| [B0003 · 18–19](../../../../../tests/integration/parse_sql.py#L18) | Explanatory comments or spacing. |  |
| [B0004 · 20–27](../../../../../tests/integration/parse_sql.py#L20) | Callable definition: def read_json(path: Path) -&gt; Any: | calls reject_constant, ValueError, loads, read_text; returns json.loads(path.read_text(encoding="utf-8"), parse_constant=reject_constant) · [reviewed contract](#b0004) |
| [B0005 · 28–29](../../../../../tests/integration/parse_sql.py#L28) | Explanatory comments or spacing. |  |
| [B0006 · 30–33](../../../../../tests/integration/parse_sql.py#L30) | Callable definition: def canonical_json(value: Any) -&gt; str: | calls types, dumps; returns json.dumps(value, ensure_ascii=False, sort_keys=True, separators=(",", ":")); source comment (unverified): # JSON serialization preserves scalar types (unlike Python equality, where · [reviewed contract](#b0006) |
| [B0007 · 34–35](../../../../../tests/integration/parse_sql.py#L34) | Explanatory comments or spacing. |  |
| [B0008 · 36–41](../../../../../tests/integration/parse_sql.py#L36) | Callable definition: def compare(actual: Any, expected: Any, label: str) -&gt; None: | calls canonical_json, dumps, RuntimeError; returns actual_text = json.dumps(actual, ensure_ascii=False, sort_keys=True, indent=2) · [reviewed contract](#b0008) |
| [B0009 · 42–43](../../../../../tests/integration/parse_sql.py#L42) | Explanatory comments or spacing. |  |
| [B0010 · 44–48](../../../../../tests/integration/parse_sql.py#L44) | Callable definition: def decode_output(data: bytes, case_name: str, stream: str) -&gt; str: | calls decode, RuntimeError; returns data.decode("utf-8") · [reviewed contract](#b0010) |
| [B0011 · 49–50](../../../../../tests/integration/parse_sql.py#L49) | Explanatory comments or spacing. |  |
| [B0012 · 51–63](../../../../../tests/integration/parse_sql.py#L51) | Callable definition: def parse_output(case_name: str, process: subprocess.CompletedProcess\[bytes\]) -&gt; dict\[str, Any\]: | calls decode_output, loads, in, throw; guard require(isinstance(result, dict), f"{case_name}: parse-sql result must be an object"); returns result; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 64–65](../../../../../tests/integration/parse_sql.py#L64) | Explanatory comments or spacing. |  |
| [B0014 · 66–112](../../../../../tests/integration/parse_sql.py#L66) | Callable definition: def input_bytes(base: Path, case: Any) -&gt; bytes: | calls require, isinstance, get, resolve; guard require(isinstance(case, dict), "manifest case must be an object"); returns path.read_bytes(); bytes.fromhex(value) · [reviewed contract](#b0014) |
| [B0015 · 113–114](../../../../../tests/integration/parse_sql.py#L113) | Explanatory comments or spacing. |  |
| [B0016 · 115–195](../../../../../tests/integration/parse_sql.py#L115) | Callable definition: def run_case(executable: str, base: Path, temporary: Path, case: Any, successful: bool) -&gt; None: | calls require, isinstance, get, input_bytes; guard require(isinstance(case, dict), "manifest case must be an object"); returns require(set(actual) == set(common) \| {"syntax_valid", "diagnostic"},; 2 loop sites · [reviewed contract](#b0016) |
| [B0017 · 196–197](../../../../../tests/integration/parse_sql.py#L196) | Explanatory comments or spacing. |  |
| [B0018 · 198–231](../../../../../tests/integration/parse_sql.py#L198) | Callable definition: def main() -&gt; int: | calls len, RuntimeError, Path, resolve; guard require(isinstance(manifest, dict), "manifest must be an object"); returns 0; 2 loop sites · [reviewed contract](#b0018) |
| [B0019 · 232–239](../../../../../tests/integration/parse_sql.py#L232) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0019) |

## B0001

[Lines 1–13](../../../../../tests/integration/parse_sql.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L13:sha256:76508dac1d1dacd9fcb3551ec66c918883b4d3e2fb66b561d0b5c534249b631d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for parse_sql.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/integration/parse_sql.py](../../../../../tests/integration/parse_sql.py), [docs/sql_parser.md](../../../../sql_parser.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 14–17](../../../../../tests/integration/parse_sql.py#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(condition: bool, message: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce a parser-fixture expectation even with Python optimization enabled. |
| inputs / outputs | Takes condition/message and returns None or raises RuntimeError(message). |
| invariants | Explicit if cannot be disabled by -O, unlike assert. |
| ownership | Borrows compared data and does not edit ASTs, snapshots or files. |
| failure | False condition raises RuntimeError; errors evaluating the predicate occur before this call. |
| cost | One truth conversion, excluding any caller-built serialization/diagnostic. |
| Design | [tests/integration/parse_sql.py](../../../../../tests/integration/parse_sql.py), [docs/sql_parser.md](../../../../sql_parser.md), [schemas/sql-syntax-v1.schema.json](../../../../../schemas/sql-syntax-v1.schema.json) |

## B0004

[Lines 20–27](../../../../../tests/integration/parse_sql.py#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def read_json(path: Path) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one UTF-8 parser manifest/snapshot while rejecting JSON nonfinite numeric extensions. |
| inputs / outputs | Takes Path, returns any decoded JSON value using parse_constant that raises on NaN/Infinity/-Infinity. |
| invariants | Does not itself require an object or reject duplicate keys; callers check shape. Reads the complete file before parsing. |
| ownership | Path.read_text opens/closes file; decoded containers and full text are new and input path is unchanged. |
| failure | OSError, UnicodeError, JSONDecodeError and ValueError are chained into RuntimeError naming the path. |
| cost | Whole-file text allocation, UTF-8 decoding and complete JSON parse; parse_constant rejection can stop parsing early. |
| Design | [tests/integration/parse_sql.py](../../../../../tests/integration/parse_sql.py), [docs/sql_parser.md](../../../../sql_parser.md), [schemas/sql-syntax-v1.schema.json](../../../../../schemas/sql-syntax-v1.schema.json) |

## B0006

[Lines 30–33](../../../../../tests/integration/parse_sql.py#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def canonical_json(value: Any) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce type-sensitive compact text for parser snapshot comparisons. |
| inputs / outputs | Takes JSON-serializable value; returns sorted-key Unicode str with compact separators. |
| invariants | Preserves arrays and JSON scalar type spellings, so True differs from 1 and int 1 from float 1.0; no nonfinite guard is added here. |
| ownership | Creates complete text without modifying or deep-copying input containers. |
| failure | Unsupported/cyclic inputs or incompatible sorted keys raise json serialization errors. |
| cost | Full traversal/key sorting and retained serialization-sized string. |
| Design | [tests/integration/parse_sql.py](../../../../../tests/integration/parse_sql.py), [docs/sql_parser.md](../../../../sql_parser.md), [schemas/sql-syntax-v1.schema.json](../../../../../schemas/sql-syntax-v1.schema.json) |

## B0008

[Lines 36–41](../../../../../tests/integration/parse_sql.py#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def compare(actual: Any, expected: Any, label: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare parser output with a fixture using JSON scalar types and key-order normalization. |
| inputs / outputs | Takes actual,expected,label; returns None if compact canonical text matches, otherwise raises RuntimeError with pretty sorted expected/actual. |
| invariants | Object ordering is ignored; array order/types remain significant. The helper does not silently coerce bool/int equality through Python value comparison. |
| ownership | Reads both graphs and allocates their canonical strings; mismatch also allocates full pretty diagnostics. No mutation. |
| failure | Mismatch raises RuntimeError; serialization failures propagate before a comparison diagnostic is created. |
| cost | Serializes both entire values; mismatch adds two more full pretty serializations and large exception text. |
| Design | [tests/integration/parse_sql.py](../../../../../tests/integration/parse_sql.py), [docs/sql_parser.md](../../../../sql_parser.md), [schemas/sql-syntax-v1.schema.json](../../../../../schemas/sql-syntax-v1.schema.json) |

## B0010

[Lines 44–48](../../../../../tests/integration/parse_sql.py#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def decode_output(data: bytes, case_name: str, stream: str) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a child output channel to be valid UTF-8. |
| inputs / outputs | Takes bytes plus case/stream labels and returns decoded str using strict utf-8. |
| invariants | No replacement, trimming or newline normalization occurs. |
| ownership | Allocates decoded text while leaving supplied bytes unchanged. |
| failure | UnicodeDecodeError becomes chained RuntimeError identifying the case and stream. |
| cost | Linear decode in channel bytes with full text allocation. |
| Design | [tests/integration/parse_sql.py](../../../../../tests/integration/parse_sql.py), [docs/sql_parser.md](../../../../sql_parser.md), [schemas/sql-syntax-v1.schema.json](../../../../../schemas/sql-syntax-v1.schema.json) |

## B0012

[Lines 51–63](../../../../../tests/integration/parse_sql.py#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def parse_output(case_name: str, process: subprocess.CompletedProcess[bytes]) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse a parser CLI stdout object and reject non-JSON numeric constants. |
| inputs / outputs | Takes case label and bytes CompletedProcess; strictly decodes stdout, loads JSON with NaN/Infinity rejection and requires dict. Returns decoded object. |
| invariants | Does not check return code or empty stderr; run_case owns those checks. stderr is decoded only to diagnose JSON parse failure. |
| ownership | Creates new decoded text/object; borrows process buffers and never closes or mutates them. |
| failure | Bad stdout UTF-8 or shape gives RuntimeError; JSON/constant errors are chained with full channels. Invalid stderr UTF-8 during that diagnostic can replace the parse error with its own chained RuntimeError. |
| cost | Full stdout decode/parse; failure can decode and embed complete stderr/stdout, so diagnostics are not size-bounded. |
| Design | [tests/integration/parse_sql.py](../../../../../tests/integration/parse_sql.py), [docs/sql_parser.md](../../../../sql_parser.md), [schemas/sql-syntax-v1.schema.json](../../../../../schemas/sql-syntax-v1.schema.json) |

## B0014

[Lines 66–112](../../../../../tests/integration/parse_sql.py#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def input_bytes(base: Path, case: Any) -> bytes:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve a parser case’s literal/file/generated SQL payload without requiring valid UTF-8. |
| inputs / outputs | Takes base/case and returns bytes, preferring input file, then input_hex, then generated total-byte prefix/fill or repeated Unicode text. |
| invariants | File path resolve must stay inside resolved base; generated total/count are exact nonnegative ints (not bool), fill exactly one byte and prefix fits total. No maximum generated size is applied. |
| ownership | Borrows case, returns newly read/generated immutable bytes; file helper closes its handle. Repeated-text generation holds full str before UTF-8 bytes; it writes no files. |
| failure | Bad descriptors/checks and read/hex errors become RuntimeError; Unicode encoding/path-resolution and allocation errors can propagate separately. |
| cost | Whole-file read, full hex decode or count-sized repeated allocation; total_bytes/repeat_count directly control memory/time without streaming. |
| Design | [tests/integration/parse_sql.py](../../../../../tests/integration/parse_sql.py), [docs/sql_parser.md](../../../../sql_parser.md), [schemas/sql-syntax-v1.schema.json](../../../../../schemas/sql-syntax-v1.schema.json) |

## B0016

[Lines 115–195](../../../../../tests/integration/parse_sql.py#L115); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def run_case(executable: str, base: Path, temporary: Path, case: Any, successful: bool) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check one syntax-only CLI success AST snapshot or exact error diagnostic against pinned parser metadata. |
| inputs / outputs | Takes executable/base/existing temp directory/case/success flag; writes payload to &lt;name&gt;.sql, runs parse-sql timeout 20, and validates exact envelope keys/parser versions/source preservation or diagnostic snapshot. |
| invariants | Requires exit 0/1 and empty stderr; common admission_status stays not_checked. Success checks statement ranges and exactly one upstream RawStmt plus parser/Postgres versions, while failure compares all expected coordinates/message fields. Snapshot path is contained in base; case name is only nonempty, so source filename safety relies on trusted fixture names. |
| ownership | Owns payload/parsed AST and temporary source file; borrows directory lifetime/cleanup from caller. It does not mutate case/snapshots; generated source file remains until caller cleanup. |
| failure | TimeoutExpired is translated; checks/JSON/UTF-8 errors use RuntimeError, file/launch and unexpected types can propagate. A failed child or validation leaves the private source file present. |
| cost | One real parser child plus payload writing and full AST/snapshot materialization/comparison; comparisons may reserialize large ASTs several times. Native syntax parsing is additional work. |
| Design | [tests/integration/parse_sql.py](../../../../../tests/integration/parse_sql.py), [docs/sql_parser.md](../../../../sql_parser.md), [schemas/sql-syntax-v1.schema.json](../../../../../schemas/sql-syntax-v1.schema.json) |

## B0018

[Lines 198–231](../../../../../tests/integration/parse_sql.py#L198); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main() -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run all syntax success snapshots and failure-coordinate fixtures with unique names and temporary source files. |
| inputs / outputs | Takes executable/fixture-directory argv, loads manifest and schema marker, validates nonempty success/failure lists/version 1, invokes run_case for each, prints counts and returns 0. |
| invariants | Ensures names are unique across both lists and reads a JSON Schema 2020-12 document marker; it does not run a jsonschema validator. Acceptance remains syntax-only with admission not_checked. |
| ownership | TemporaryDirectory closes/removes all generated SQL files even on errors. Manifest/schema/snapshots are newly decoded; no fixture source is rewritten. |
| failure | RuntimeError is caught by entrypoint for stderr exit 1; read_json wraps its specified read/decode errors, while unwrapped file/launch/type errors may propagate. |
| cost | One parser subprocess per case, whole manifest/schema/snapshot I/O and full canonical AST comparison. Temporary lifetime cleanup adds file deletion, not runtime durability testing. |
| Design | [tests/integration/parse_sql.py](../../../../../tests/integration/parse_sql.py), [docs/sql_parser.md](../../../../sql_parser.md), [schemas/sql-syntax-v1.schema.json](../../../../../schemas/sql-syntax-v1.schema.json) |

## B0019

[Lines 232–239](../../../../../tests/integration/parse_sql.py#L232); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Run all syntax success snapshots and failure-coordinate fixtures with unique names and temporary source files. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Pass the delegated return value to Python SystemExit; main controls that explicit exit status. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | The process boundary formats only RuntimeError to stderr, as shown in the source, then raises SystemExit(1). SystemExit/KeyboardInterrupt and unlisted exceptions are not converted; diagnostic I/O/allocation failure can still propagate. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. Failure formatting costs its actual diagnostic bytes. |
| Design | [tests/integration/parse_sql.py](../../../../../tests/integration/parse_sql.py), [docs/development.md](../../../../development.md), [docs/sql_parser.md](../../../../sql_parser.md), [schemas/sql-syntax-v1.schema.json](../../../../../schemas/sql-syntax-v1.schema.json) |
