# `tests/integration/ingest.py` — block usage map

[Source](../../../../../tests/integration/ingest.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `02192da305b6615c54d08a020f38ecfdcf999ad2aafb151bc54870128feb086b`. 333 lines partitioned into 23 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–21](../../../../../tests/integration/ingest.py#L1) | Imports dependencies; declares types or opens a type body; declares values/defaults or compile-time conditions. | 1 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 22–24](../../../../../tests/integration/ingest.py#L22) | Callable definition: def require(condition: bool, message: str) -&gt; None: | calls RuntimeError; guard def require(condition: bool, message: str) -&gt; None: · [reviewed contract](#b0002) |
| [B0003 · 25–26](../../../../../tests/integration/ingest.py#L25) | Explanatory comments or spacing. |  |
| [B0004 · 27–28](../../../../../tests/integration/ingest.py#L27) | Callable definition: def json_text(value: Any) -&gt; str: | calls dumps; returns json.dumps(value, ensure_ascii=False, sort_keys=True, separators=(",", ":")) · [reviewed contract](#b0004) |
| [B0005 · 29–30](../../../../../tests/integration/ingest.py#L29) | Explanatory comments or spacing. |  |
| [B0006 · 31–43](../../../../../tests/integration/ingest.py#L31) | Callable definition: def run(executable: str, arguments: list\[str\]) -&gt; subprocess.CompletedProcess\[str\]: | calls RuntimeError; returns subprocess.run( · [reviewed contract](#b0006) |
| [B0007 · 44–45](../../../../../tests/integration/ingest.py#L44) | Explanatory comments or spacing. |  |
| [B0008 · 46–79](../../../../../tests/integration/ingest.py#L46) | Callable definition: def expect_summary( | calls str, append, run, require; guard require(result.returncode == 0, f"{fmt} rejected valid input: {result.stderr} {result.stdout\[:300\]}…; returns one JSON summary: {result.stdout\[:300\]!r}") from error · [reviewed contract](#b0008) |
| [B0009 · 80–81](../../../../../tests/integration/ingest.py#L80) | Explanatory comments or spacing. |  |
| [B0010 · 82–95](../../../../../tests/integration/ingest.py#L82) | Callable definition: def expect_rejection( | calls run, require, loads, except; guard require(result.returncode != 0, f"{label}: invalid input unexpectedly succeeded") · [reviewed contract](#b0010) |
| [B0011 · 96–97](../../../../../tests/integration/ingest.py#L96) | Explanatory comments or spacing. |  |
| [B0012 · 98–101](../../../../../tests/integration/ingest.py#L98) | Callable definition: def put_string(output: bytearray, value: str) -&gt; None: | calls encode, extend, pack, len · [reviewed contract](#b0012) |
| [B0013 · 102–103](../../../../../tests/integration/ingest.py#L102) | Explanatory comments or spacing. |  |
| [B0014 · 104–117](../../../../../tests/integration/ingest.py#L104) | Callable definition: def binary_value(value: Any) -&gt; bytes: | calls isinstance, pack, encode, len; returns b"\x02" + (b"\x01" if value else b"\x00"); b"\x00" + struct.pack("&lt;q", value) · [reviewed contract](#b0014) |
| [B0015 · 118–119](../../../../../tests/integration/ingest.py#L118) | Explanatory comments or spacing. |  |
| [B0016 · 120–144](../../../../../tests/integration/ingest.py#L120) | Callable definition: def binary_frame( | calls bytearray, extend, pack, encode; returns b"CROWNUPD" + struct.pack("&lt;HI", 1, len(payload)) + payload; growth insert; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 145–146](../../../../../tests/integration/ingest.py#L145) | Explanatory comments or spacing. |  |
| [B0018 · 147–166](../../../../../tests/integration/ingest.py#L147) | Callable definition: def event( | calls ; returns { · [reviewed contract](#b0018) |
| [B0019 · 167–168](../../../../../tests/integration/ingest.py#L167) | Explanatory comments or spacing. |  |
| [B0020 · 169–172](../../../../../tests/integration/ingest.py#L169) | Callable definition: def write_jsonl(path: Path, events: list\[dict\[str, Any\]\]) -&gt; bytes: | calls join, dumps, encode, write_bytes; returns data; 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 173–174](../../../../../tests/integration/ingest.py#L173) | Explanatory comments or spacing. |  |
| [B0022 · 175–325](../../../../../tests/integration/ingest.py#L175) | Callable definition: def main() -&gt; int: | calls require, len, str, Path; guard require(len(sys.argv) == 3, "usage: ingest.py CROWN_EXECUTABLE REPOSITORY"); returns 0; growth insert; 1 loop sites; source comment (unverified): # JSONL is hand-authored physical metadata with typed scalars and exact boundaries. · [reviewed contract](#b0022) |
| [B0023 · 326–333](../../../../../tests/integration/ingest.py#L326) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0023) |

## B0001

[Lines 1–21](../../../../../tests/integration/ingest.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L21:sha256:acbab4f0fddb6b701d558f61a65bb0f58b023df74d4aadfd8a5cb4fc28a294ec
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for ingest.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/integration/ingest.py](../../../../../tests/integration/ingest.py), [docs/ingestion.md](../../../../ingestion.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 22–24](../../../../../tests/integration/ingest.py#L22); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(condition: bool, message: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce one ingestion CLI expectation with an always-enabled check. |
| inputs / outputs | Takes condition/message, returning None or raising RuntimeError(message). |
| invariants | Uses an explicit if so python -O does not remove validation. |
| ownership | Borrows operands and does not change files, parsed summaries or subprocess results. |
| failure | False condition raises RuntimeError; predicate computation/truth conversion errors propagate separately. |
| cost | One truth test after the caller computes its condition/diagnostic. |
| Design | [tests/integration/ingest.py](../../../../../tests/integration/ingest.py), [docs/ingestion.md](../../../../ingestion.md) |

## B0004

[Lines 27–28](../../../../../tests/integration/ingest.py#L27); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def json_text(value: Any) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render compact sorted JSON text for expected/actual ingestion diagnostics. |
| inputs / outputs | Takes JSON-serializable value and returns unescaped-Unicode str. |
| invariants | Sorts object keys and preserves array order/types; does not enforce finite numbers beyond json.dumps defaults. |
| ownership | New complete string; input graph is read without copying/mutation. |
| failure | Unsupported/cyclic objects or incompatible keys raise JSON serialization errors. |
| cost | Full serialization/key sorting and full result-text allocation. |
| Design | [tests/integration/ingest.py](../../../../../tests/integration/ingest.py), [docs/ingestion.md](../../../../ingestion.md) |

## B0006

[Lines 31–43](../../../../../tests/integration/ingest.py#L31); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def run(executable: str, arguments: list[str]) -> subprocess.CompletedProcess[str]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke ingestion CLI while preserving status/channels for acceptance helpers. |
| inputs / outputs | Takes executable and argument strings; runs with UTF-8 text decoding/errors=replace, captured channels, timeout 60, check=False; returns CompletedProcess. |
| invariants | Nonzero exit is returned for caller inspection and invalid UTF-8 is replaced in captured text. This wrapper does not decide success. |
| ownership | Creates command list; subprocess.run waits and manages/closes communication pipes; caller receives buffered strings/result. Arguments are unchanged. |
| failure | Translates TimeoutExpired to chained RuntimeError mentioning arguments\[0\]; launch OSError propagates. Empty arguments can cause IndexError in the timeout diagnostic path. |
| cost | One actual child plus complete channel buffering/UTF-8 decode; the timeout is per invocation. |
| Design | [tests/integration/ingest.py](../../../../../tests/integration/ingest.py), [docs/ingestion.md](../../../../ingestion.md) |

## B0008

[Lines 46–79](../../../../../tests/integration/ingest.py#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def expect_summary(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that valid input produces exactly the expected validate-input summary and channel framing. |
| inputs / outputs | Builds validate-input args with optional table, runs CLI, parses stdout and compares schema/version/hash/record-byte counts/final sequence/source positions against supplied expectations. Returns None. |
| invariants | Requires exit 0, empty stderr, exact Python dict equality with no extra fields and a final stdout newline; JSON equality is not separately type-strict for numeric bool/int values. data contributes only len(data), not a recomputed hash. |
| ownership | Owns newly parsed summary/expected dict, sharing supplied positions in expected without mutation; does not write input/catalog files. |
| failure | Status/channel/mismatch uses RuntimeError; malformed stdout JSON is translated with cause, while other type/field formatting and process errors propagate. |
| cost | One child plus whole stdout parse and expected diagnostic serialization; comparison scans the summary/positions, independent of native file validation cost. |
| Design | [tests/integration/ingest.py](../../../../../tests/integration/ingest.py), [docs/ingestion.md](../../../../ingestion.md) |

## B0010

[Lines 82–95](../../../../../tests/integration/ingest.py#L82); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def expect_rejection(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check invalid ingestion CLI input yields a structured code and no partial summary. |
| inputs / outputs | Runs executable/arguments; requires nonzero status, empty stdout, stderr JSON with error member and expected error.code. label annotates diagnostics. |
| invariants | Does not require a particular nonzero exit or exact error object/line text; only the supplied code and output-channel behavior are checked. |
| ownership | Owns decoded error document and borrowed command/expected text; no caller/file mutation. |
| failure | Missing/malformed diagnostic JSON/error member is chained RuntimeError; mismatch RuntimeError. If error itself is not a mapping, later .get can raise AttributeError outside the parse catch. |
| cost | One child and full channel buffering/JSON parse, with bounded diagnostic suffixes only in error messages, not bounded captured output. |
| Design | [tests/integration/ingest.py](../../../../../tests/integration/ingest.py), [docs/ingestion.md](../../../../ingestion.md) |

## B0012

[Lines 98–101](../../../../../tests/integration/ingest.py#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def put_string(output: bytearray, value: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append the public binary fixture length-prefixed UTF-8 string representation. |
| inputs / outputs | Takes mutable bytearray and str; encodes UTF-8, appends little-endian uint32 byte length then encoded bytes, returning None. |
| invariants | Length counts UTF-8 bytes, not code points; no terminator or identifier validation is added. struct.pack enforces uint32 range. |
| ownership | Mutates caller bytearray in place and allocates encoded bytes/length prefix; no rollback if an extension fails after prior mutation. |
| failure | UnicodeEncodeError, struct.error or buffer/allocation errors propagate. Encoding/length packing finish before the first append. |
| cost | O(UTF-8 bytes) encoding/copy with temporary bytes and possible amortized bytearray growth. |
| Design | [tests/integration/ingest.py](../../../../../tests/integration/ingest.py), [docs/ingestion.md](../../../../ingestion.md) |

## B0014

[Lines 104–117](../../../../../tests/integration/ingest.py#L104); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def binary_value(value: Any) -> bytes:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one public CROWNUPD fixture scalar with its wire tag. |
| inputs / outputs | Bool uses tag 2 then 0/1; int tag 0+signed little-endian 64-bit; str tag 1+uint32 UTF-8 length; tagged date tag 3+ASCII text; tagged decimal tag 4+uint32 ASCII length. Returns bytes. |
| invariants | Tests bool before int; date wins when a mapping has both date/decimal. Does not validate date width/calendar, decimal grammar or exact tagged object keys; fixed fixture inputs supply those properties. |
| ownership | Allocates encoded scalar bytes and borrows input/value fields without mutation. |
| failure | Out-of-range int/length raises struct.error, encoding failures propagate; unsupported iterable/mapping falls through to RuntimeError, but None/other noniterables can raise TypeError at membership testing. |
| cost | Linear in string/date/decimal encoded bytes with concatenation copies; numeric/bool paths are fixed-width apart from Python type handling. |
| Design | [tests/integration/ingest.py](../../../../../tests/integration/ingest.py), [docs/ingestion.md](../../../../ingestion.md) |

## B0016

[Lines 120–144](../../../../../tests/integration/ingest.py#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def binary_frame(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble an independently encoded CROWNUPD version 1 physical update frame. |
| inputs / outputs | Accepts versions/hash/sequence/table/operation/optional(source,offset)/values; returns bytes with CROWNUPD magic, uint16 version, uint32 payload length and typed payload. |
| invariants | Uses uint64 metadata, optional-position flag and uint32 row count; operation==insert encodes 1, every other spelling encodes 2. Hash is only ASCII-encoded, not checked as 64 lowercase hex; this is fixture assembly, not admission. |
| ownership | Builds a private bytearray and returns new immutable concatenated bytes; caller values/source/table are read, never retained as mutable wire data. |
| failure | Packing/ASCII or UTF-8/unsupported scalar failures propagate; partial private payload is discarded and no caller buffer changes. |
| cost | Serializes/copies all scalar/metadata bytes, with private payload and final frame overlapping; fixed-width fields do not remove full-row/frame materialization cost. |
| Design | [tests/integration/ingest.py](../../../../../tests/integration/ingest.py), [docs/ingestion.md](../../../../ingestion.md) |

## B0018

[Lines 147–166](../../../../../tests/integration/ingest.py#L147); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def event(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct one Typed-table JSON physical-event fixture, including intentionally invalid variants. |
| inputs / outputs | Takes hash/sequence/operation/values plus source,offset,version defaults; returns schema metadata with catalog 41/source-schema 7 and source_position object. |
| invariants | Does not validate sequence/operation/version/types; callers deliberately use it for unsupported-operation/schema and malformed-scalar cases. |
| ownership | Allocates dicts but shares the caller values list and supplied scalar strings; source_position is newly allocated. Caller mutations to values affect event. |
| failure | Normal dictionary construction only; unusual argument objects are accepted for later JSON/native rejection. |
| cost | Constant-size object allocation with no traversal/copy of values. |
| Design | [tests/integration/ingest.py](../../../../../tests/integration/ingest.py), [docs/ingestion.md](../../../../ingestion.md) |

## B0020

[Lines 169–172](../../../../../tests/integration/ingest.py#L169); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def write_jsonl(path: Path, events: list[dict[str, Any]]) -> bytes:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write complete event fixtures as compact Unicode JSONL and return the exact bytes written. |
| inputs / outputs | Takes Path/events list; serializes each item with one trailing newline, joins and UTF-8-encodes all text, writes via write_bytes, returns data. Empty events writes empty bytes. |
| invariants | Preserves event/list order and dictionary insertion order; returned bytes include all line endings. No schema, hash or finite-number validation is added. |
| ownership | Borrows event containers, owns whole text/encoded bytes, overwrites caller path and closes file via Path helper. No rollback on I/O failure. |
| failure | Serialization/encoding failures precede file write; file write can fail after truncation/partial output. |
| cost | Materializes all per-line text plus joined text and complete bytes, then O(total bytes) file I/O; not a streaming serializer. |
| Design | [tests/integration/ingest.py](../../../../../tests/integration/ingest.py), [docs/ingestion.md](../../../../ingestion.md) |

## B0022

[Lines 175–325](../../../../../tests/integration/ingest.py#L175); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main() -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Accept valid physical ingestion formats and structured rejection behavior against an independently bound typed catalog. |
| inputs / outputs | Takes CLI/repository paths, creates temporary catalog/events, derives catalog SHA from native canonical output, checks JSONL/binary/CSV/three legacy formats and malformed metadata/scalars/truncation/usage/size caps, then prints count and returns 0. |
| invariants | Checks exact int64/scalar boundaries and final progress for valid formats; bad later record must suppress the whole summary. Size cases exceed 16 MiB catalog/1 MiB record and assert resource_limit, not allocation measurements or durability. Source markers are supplied logical offsets. |
| ownership | TemporaryDirectory encloses every created file and cleans on success/error; local fixture rows may be shared across event dictionaries, but native children receive encoded files. Canonical JSON/hash and entire encoded fixtures are separately materialized. |
| failure | RuntimeError checks/timeouts are caught by entrypoint for stderr exit 1; file/JSON/packing and other exceptions are not broadly caught. Every CLI run has its own 60-second timeout. |
| cost | Many actual CLI children plus full fixture encoding/writes, including &gt;16 MiB space and &gt;1 MiB record allocations. Native validation cost dominates helper conversions; no runtime commit, sink or recovery acceptance is tested. |
| Design | [tests/integration/ingest.py](../../../../../tests/integration/ingest.py), [docs/ingestion.md](../../../../ingestion.md) |

## B0023

[Lines 326–333](../../../../../tests/integration/ingest.py#L326); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Accept valid physical ingestion formats and structured rejection behavior against an independently bound typed catalog. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Pass the delegated return value to Python SystemExit; main controls that explicit exit status. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | The process boundary formats only RuntimeError to stderr, as shown in the source, then raises SystemExit(1). SystemExit/KeyboardInterrupt and unlisted exceptions are not converted; diagnostic I/O/allocation failure can still propagate. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. Failure formatting costs its actual diagnostic bytes. |
| Design | [tests/integration/ingest.py](../../../../../tests/integration/ingest.py), [docs/development.md](../../../../development.md), [docs/ingestion.md](../../../../ingestion.md) |
