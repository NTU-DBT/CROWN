# `tests/integration/binding.py` — block usage map

[Source](../../../../../tests/integration/binding.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `8d131da892cb8d93cc39a1b9b5332a6a1a88c377c30e26353b55011089fd4452`. 639 lines partitioned into 63 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–35](../../../../../tests/integration/binding.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 36–39](../../../../../tests/integration/binding.py#L36) | Callable definition: def require(condition: bool, message: str) -&gt; None: | calls RuntimeError; guard def require(condition: bool, message: str) -&gt; None:; source comment (unverified): # Keep validation active when invoked with \`\`python -O\`\`. · [reviewed contract](#b0002) |
| [B0003 · 40–41](../../../../../tests/integration/binding.py#L40) | Explanatory comments or spacing. |  |
| [B0004 · 42–49](../../../../../tests/integration/binding.py#L42) | Callable definition: def read_json(path: Path) -&gt; Any: | calls reject_constant, ValueError, loads, read_text; returns json.loads(path.read_text(encoding="utf-8"), parse_constant=reject_constant) · [reviewed contract](#b0004) |
| [B0005 · 50–51](../../../../../tests/integration/binding.py#L50) | Explanatory comments or spacing. |  |
| [B0006 · 52–53](../../../../../tests/integration/binding.py#L52) | Callable definition: def json_text(value: Any) -&gt; str: | calls dumps; returns json.dumps(value, ensure_ascii=False, sort_keys=True, separators=(",", ":")) · [reviewed contract](#b0006) |
| [B0007 · 54–55](../../../../../tests/integration/binding.py#L54) | Explanatory comments or spacing. |  |
| [B0008 · 56–64](../../../../../tests/integration/binding.py#L56) | Callable definition: def compare(label: str, actual: Any, expected: Any) -&gt; None: | calls sensitive, json_text, RuntimeError, dumps; source comment (unverified): # JSON encoding makes comparisons type-sensitive (True is not integer 1). · [reviewed contract](#b0008) |
| [B0009 · 65–66](../../../../../tests/integration/binding.py#L65) | Explanatory comments or spacing. |  |
| [B0010 · 67–71](../../../../../tests/integration/binding.py#L67) | Callable definition: def decode_output(data: bytes, label: str, stream: str) -&gt; str: | calls decode, RuntimeError; returns data.decode("utf-8") · [reviewed contract](#b0010) |
| [B0011 · 72–73](../../../../../tests/integration/binding.py#L72) | Explanatory comments or spacing. |  |
| [B0012 · 74–85](../../../../../tests/integration/binding.py#L74) | Callable definition: def parse_stdout(process: subprocess.CompletedProcess\[bytes\], label: str) -&gt; dict\[str, Any\]: | calls decode_output, loads, in, throw; guard require(isinstance(result, dict), f"{label}: command result must be an object"); returns result; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 86–87](../../../../../tests/integration/binding.py#L86) | Explanatory comments or spacing. |  |
| [B0014 · 88–94](../../../../../tests/integration/binding.py#L88) | Callable definition: def invoke(executable: str, arguments: list\[str\], label: str) -&gt; subprocess.CompletedProcess\[bytes\]: | calls run, RuntimeError; returns subprocess.run( · [reviewed contract](#b0014) |
| [B0015 · 95–96](../../../../../tests/integration/binding.py#L95) | Explanatory comments or spacing. |  |
| [B0016 · 97–102](../../../../../tests/integration/binding.py#L97) | Callable definition: def decode_scalar(value: Any) -&gt; Any: | calls isinstance, set, Decimal, fromisoformat; returns Decimal(value\["decimal"\]); dt.date.fromisoformat(value\["date"\]) · [reviewed contract](#b0016) |
| [B0017 · 103–104](../../../../../tests/integration/binding.py#L103) | Explanatory comments or spacing. |  |
| [B0018 · 105–108](../../../../../tests/integration/binding.py#L105) | Callable definition: def table_data_rows(data: dict\[str, list\[list\[Any\]\]\], table_name: str) -&gt; list\[list\[Any\]\]: | calls items, casefold, require, len; guard require(len(matches) == 1, f"fixture data must define exactly one entry for table {table_name!r}"); returns matches\[0\]; 2 loop sites · [reviewed contract](#b0018) |
| [B0019 · 109–110](../../../../../tests/integration/binding.py#L109) | Explanatory comments or spacing. |  |
| [B0020 · 111–117](../../../../../tests/integration/binding.py#L111) | Callable definition: def canonical_decimal(value: Decimal) -&gt; str: | calls format, rstrip; returns "0"; rendered · [reviewed contract](#b0020) |
| [B0021 · 118–119](../../../../../tests/integration/binding.py#L118) | Explanatory comments or spacing. |  |
| [B0022 · 120–127](../../../../../tests/integration/binding.py#L120) | Callable definition: def json_scalar(value: Any) -&gt; Any: | calls isinstance, canonical_decimal, isoformat; returns {"decimal": canonical_decimal(value)}; {"date": value.isoformat()}; 1 loop sites · [reviewed contract](#b0022) |
| [B0023 · 128–129](../../../../../tests/integration/binding.py#L128) | Explanatory comments or spacing. |  |
| [B0024 · 130–131](../../../../../tests/integration/binding.py#L130) | Callable definition: def value_key(value: Any) -&gt; str: | calls json_text, json_scalar; returns json_text(json_scalar(value)) · [reviewed contract](#b0024) |
| [B0025 · 132–133](../../../../../tests/integration/binding.py#L132) | Explanatory comments or spacing. |  |
| [B0026 · 134–135](../../../../../tests/integration/binding.py#L134) | Callable definition: def rows_key(rows: list\[tuple\[Any, ...\]\]) -&gt; collections.Counter\[str\]: | calls Counter, value_key; returns collections.Counter(value_key(row) for row in rows); 1 loop sites · [reviewed contract](#b0026) |
| [B0027 · 136–137](../../../../../tests/integration/binding.py#L136) | Explanatory comments or spacing. |  |
| [B0028 · 138–189](../../../../../tests/integration/binding.py#L138) | Callable definition: def validate_expression_arena(result: dict\[str, Any\], label: str, source: str) -&gt; None: | calls require, isinstance, enumerate, type; guard require(isinstance(expressions, list), f"{label}: expressions must be an array"); 4 loop sites · [reviewed contract](#b0028) |
| [B0029 · 190–191](../../../../../tests/integration/binding.py#L190) | Explanatory comments or spacing. |  |
| [B0030 · 192–196](../../../../../tests/integration/binding.py#L192) | Callable definition: def sql_truth(value: Any) -&gt; bool \| None: | calls require, type; guard require(type(value) is bool, f"SQL predicate evaluated to non-Boolean value {value!r}"); returns None; value · [reviewed contract](#b0030) |
| [B0031 · 197–198](../../../../../tests/integration/binding.py#L197) | Explanatory comments or spacing. |  |
| [B0032 · 199–267](../../../../../tests/integration/binding.py#L199) | Callable definition: def eval_expression( | calls decode_scalar, len, sql_truth, RuntimeError; returns memo\[expression_id\]; result; 3 loop sites · [reviewed contract](#b0032) |
| [B0033 · 268–269](../../../../../tests/integration/binding.py#L268) | Explanatory comments or spacing. |  |
| [B0034 · 270–304](../../../../../tests/integration/binding.py#L270) | Callable definition: def interpret( | calls table_data_rows, decode_scalar, require, all; guard require(all(len(item) == len(table\["columns"\]) for item in converted),; returns \[\], bool(projected); projected, None; 9 loop sites · [reviewed contract](#b0034) |
| [B0035 · 305–306](../../../../../tests/integration/binding.py#L305) | Explanatory comments or spacing. |  |
| [B0036 · 307–310](../../../../../tests/integration/binding.py#L307) | Callable definition: def expected_rows(case: dict\[str, Any\], fixture: dict\[str, Any\]) -&gt; list\[tuple\[Any, ...\]\]: | calls tuple, decode_scalar; returns \[tuple(decode_scalar(value) for value in row) for row in fixture\["expected_rows"\]\]; \[\]; 2 loop sites · [reviewed contract](#b0036) |
| [B0037 · 311–312](../../../../../tests/integration/binding.py#L311) | Explanatory comments or spacing. |  |
| [B0038 · 313–317](../../../../../tests/integration/binding.py#L313) | Callable definition: def validate_expected_rows(case: dict\[str, Any\], fixture: dict\[str, Any\], actual_rows: list\[tuple\[Any, ...\]\]) -&gt; None: | calls expected_rows, compare, rows_key; returns expected = expected_rows(case, fixture) · [reviewed contract](#b0038) |
| [B0039 · 318–319](../../../../../tests/integration/binding.py#L318) | Explanatory comments or spacing. |  |
| [B0040 · 320–326](../../../../../tests/integration/binding.py#L320) | Callable definition: def offset_coordinates(source: str, byte_offset: int) -&gt; tuple\[int, int, int\]: | calls encode, decode, count, len; returns character_position, line, column · [reviewed contract](#b0040) |
| [B0041 · 327–328](../../../../../tests/integration/binding.py#L327) | Explanatory comments or spacing. |  |
| [B0042 · 329–342](../../../../../tests/integration/binding.py#L329) | Callable definition: def check_location_marker(case: dict\[str, Any\], diagnostic: dict\[str, Any\], source: str) -&gt; None: | calls get, require, isinstance, find; guard require(isinstance(marker, str) and marker, f"{case\['name'\]}: invalid location marker"); returns require(isinstance(marker, str) and marker, f"{case\['name'\]}: invalid location marker"); 1 loop sites · [reviewed contract](#b0042) |
| [B0043 · 343–344](../../../../../tests/integration/binding.py#L343) | Explanatory comments or spacing. |  |
| [B0044 · 345–361](../../../../../tests/integration/binding.py#L345) | Callable definition: def run_binding(executable: str, base: Path, case: dict\[str, Any\], catalog_path: Path) -&gt; tuple\[dict\[str, Any\], str\]: | calls resolve, require, is_relative_to, read_text; guard require(source_path.is_relative_to(base.resolve()), f"{case\['name'\]}: SQL path escapes fixture dire…; returns parse_stdout(process, case\["name"\]), source · [reviewed contract](#b0044) |
| [B0045 · 362–363](../../../../../tests/integration/binding.py#L362) | Explanatory comments or spacing. |  |
| [B0046 · 364–380](../../../../../tests/integration/binding.py#L364) | Callable definition: def validate_occurrences(result: dict\[str, Any\], expected: list\[dict\[str, Any\]\], label: str) -&gt; None: | calls require, len, enumerate, zip; guard require(len(actual) == len(expected), f"{label}: expected {len(expected)} occurrences, got {len(act…; 2 loop sites · [reviewed contract](#b0046) |
| [B0047 · 381–382](../../../../../tests/integration/binding.py#L381) | Explanatory comments or spacing. |  |
| [B0048 · 383–450](../../../../../tests/integration/binding.py#L383) | Callable definition: def validate_success( | calls run_binding, require, keys, sorted; guard require(result.keys() == SUCCESS_FIELDS, f"{label}: unexpected success fields: {sorted(result)}"); returns one Boolean"); rows; 10 loop sites · [reviewed contract](#b0048) |
| [B0049 · 451–452](../../../../../tests/integration/binding.py#L451) | Explanatory comments or spacing. |  |
| [B0050 · 453–460](../../../../../tests/integration/binding.py#L453) | Callable definition: def sqlite_value(value: Any) -&gt; Any: | calls isinstance, format, isoformat, int; returns format(value, "f"); value.isoformat() · [reviewed contract](#b0050) |
| [B0051 · 461–462](../../../../../tests/integration/binding.py#L461) | Explanatory comments or spacing. |  |
| [B0052 · 463–473](../../../../../tests/integration/binding.py#L463) | Callable definition: def sqlite_typed_value(value: Any, sql_type: dict\[str, Any\]) -&gt; Any: | calls bool, Decimal, str, fromisoformat; returns None; bool(value) · [reviewed contract](#b0052) |
| [B0053 · 474–475](../../../../../tests/integration/binding.py#L474) | Explanatory comments or spacing. |  |
| [B0054 · 476–477](../../../../../tests/integration/binding.py#L476) | Callable definition: def quote_identifier(name: str) -&gt; str: | calls replace; returns '"' + name.replace('"', '""') + '"' · [reviewed contract](#b0054) |
| [B0055 · 478–479](../../../../../tests/integration/binding.py#L478) | Explanatory comments or spacing. |  |
| [B0056 · 480–524](../../../../../tests/integration/binding.py#L480) | Callable definition: def run_sqlite( | calls connect, enumerate, require, bool; guard require(bool(columns), f"{case\['name'\]}: SQLite oracle cannot create a zero-column table"); returns rows, names; 10 loop sites · [reviewed contract](#b0056) |
| [B0057 · 525–526](../../../../../tests/integration/binding.py#L525) | Explanatory comments or spacing. |  |
| [B0058 · 527–542](../../../../../tests/integration/binding.py#L527) | Callable definition: def validate_failure(executable: str, base: Path, catalog_path: Path, case: dict\[str, Any\]) -&gt; None: | calls run_binding, require, keys, sorted; guard require(result.keys() == FAILURE_FIELDS, f"{label}: unexpected failure fields: {sorted(result)}"); 1 loop sites · [reviewed contract](#b0058) |
| [B0059 · 543–544](../../../../../tests/integration/binding.py#L543) | Explanatory comments or spacing. |  |
| [B0060 · 545–580](../../../../../tests/integration/binding.py#L545) | Callable definition: def validate_cli_errors(executable: str, base: Path, catalog_path: Path, | calls get, append, str, isinstance; guard require(relative.is_relative_to(base), f"{label}: fixture path escapes fixture directory"); 2 loop sites · [reviewed contract](#b0060) |
| [B0061 · 581–582](../../../../../tests/integration/binding.py#L581) | Explanatory comments or spacing. |  |
| [B0062 · 583–631](../../../../../tests/integration/binding.py#L583) | Callable definition: def main() -&gt; int: | calls len, RuntimeError, Path, resolve; guard require(isinstance(manifest, dict) and type(manifest.get("schema_version")) is int; returns 0; 3 loop sites · [reviewed contract](#b0062) |
| [B0063 · 632–639](../../../../../tests/integration/binding.py#L632) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0063) |

## B0001

[Lines 1–35](../../../../../tests/integration/binding.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L35:sha256:762fb7470c4f8957ff07472bb8b5c9a76d5ffc6c9efd0c04ffbaf8f836685525
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for binding.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/integration/binding.py](../../../../../tests/integration/binding.py), [docs/sql_binding.md](../../../../sql_binding.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 36–39](../../../../../tests/integration/binding.py#L36); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(condition: bool, message: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Raise a fixture failure when one SQL binding expectation is false. |
| inputs / outputs | Callable: def require(condition: bool, message: str) -&gt; None:. Inputs: condition and message. Output: None on success. |
| invariants | A false condition raises RuntimeError immediately; Python assert optimization cannot disable it. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0004

[Lines 42–49](../../../../../tests/integration/binding.py#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def read_json(path: Path) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read fixture JSON while rejecting nonstandard numeric constants. |
| inputs / outputs | Callable: def read_json(path: Path) -&gt; Any:. Input: path. Output: decoded Python value. |
| invariants | NaN/Infinity-style JSON constants are rejected via parse_constant; the exception message names the path. |
| ownership | Returns a new Python object tree decoded from file bytes; the path and file are not retained. |
| failure | File, Unicode, JSON syntax and nonstandard numeric constant errors are wrapped as RuntimeError with the path. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0006

[Lines 52–53](../../../../../tests/integration/binding.py#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def json_text(value: Any) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce compact deterministic JSON text for type-sensitive equality keys. |
| inputs / outputs | Callable: def json_text(value: Any) -&gt; str:. Input: JSON-compatible value. Output: sorted-key compact string. |
| invariants | Object keys are sorted and output separators are compact; Unicode is not ASCII-escaped. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0008

[Lines 56–64](../../../../../tests/integration/binding.py#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def compare(label: str, actual: Any, expected: Any) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare actual and expected values through the canonical local JSON encoding. |
| inputs / outputs | Callable: def compare(label: str, actual: Any, expected: Any) -&gt; None:. Inputs: label, actual, expected. Output: None or detailed mismatch exception. |
| invariants | Equality is defined by the module's JSON serialization, so true and 1 remain distinct. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0010

[Lines 67–71](../../../../../tests/integration/binding.py#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def decode_output(data: bytes, label: str, stream: str) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one subprocess byte stream as UTF-8 with a labeled error. |
| inputs / outputs | Callable: def decode_output(data: bytes, label: str, stream: str) -&gt; str:. Inputs: bytes, case label, stream name. Output: decoded text. |
| invariants | UTF-8 must decode strictly; replacement characters are not substituted. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0012

[Lines 74–85](../../../../../tests/integration/binding.py#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def parse_stdout(process: subprocess.CompletedProcess[bytes], label: str) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse one command's UTF-8 stdout as a JSON object. |
| inputs / outputs | Callable: def parse_stdout(process: subprocess.CompletedProcess\[bytes\], label: str) -&gt; dict\[str, Any\]:. Inputs: CompletedProcess bytes and case label. Output: decoded object. |
| invariants | The parsed root must be a dictionary; invalid UTF-8, JSON constants and non-object roots fail. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Invalid UTF-8, invalid JSON, nonstandard numeric constants or non-object results fail as RuntimeError. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0014

[Lines 88–94](../../../../../tests/integration/binding.py#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def invoke(executable: str, arguments: list[str], label: str) -> subprocess.CompletedProcess[bytes]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run one CROWN command with captured byte streams and a fixed timeout. |
| inputs / outputs | Callable: def invoke(executable: str, arguments: list\[str\], label: str) -&gt; subprocess.CompletedProcess\[bytes\]:. Inputs: executable, argv suffix and label. Output: CompletedProcess bytes. |
| invariants | The executable and argument vector are passed directly to subprocess.run without a shell and with a 20-second timeout. |
| ownership | Returns the CompletedProcess that owns captured stdout/stderr bytes; subprocess lifetime ends before return. |
| failure | A subprocess timeout becomes RuntimeError; completed nonzero statuses are returned for the case validator to interpret. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0016

[Lines 97–102](../../../../../tests/integration/binding.py#L97); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def decode_scalar(value: Any) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode the fixture's tagged decimal/date values to Decimal/date objects. |
| inputs / outputs | Callable: def decode_scalar(value: Any) -&gt; Any:. Input: arbitrary JSON value. Output: decoded scalar or original value. |
| invariants | Only a dictionary with exactly the decimal or date tag is decoded; other objects pass through unchanged. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0018

[Lines 105–108](../../../../../tests/integration/binding.py#L105); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def table_data_rows(data: dict[str, list[list[Any]]], table_name: str) -> list[list[Any]]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find exactly one case-insensitive table entry in binding fixture data. |
| inputs / outputs | Callable: def table_data_rows(data: dict\[str, list\[list\[Any\]\]\], table_name: str) -&gt; list\[list\[Any\]\]:. Inputs: data object and catalog table name. Output: its list of rows. |
| invariants | Exactly one key must casefold-match the requested table; ambiguity and absence fail. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0020

[Lines 111–117](../../../../../tests/integration/binding.py#L111); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def canonical_decimal(value: Decimal) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render a Decimal without redundant fractional or trailing zeros. |
| inputs / outputs | Callable: def canonical_decimal(value: Decimal) -&gt; str:. Input: Decimal. Output: fixed-point decimal text; numeric zero becomes 0. |
| invariants | Canonical text is fixed-point; numeric zero is rendered as 0 and redundant fractional zeros are removed. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0022

[Lines 120–127](../../../../../tests/integration/binding.py#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def json_scalar(value: Any) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recursively encode Decimal/date values into tagged JSON scalars. |
| inputs / outputs | Callable: def json_scalar(value: Any) -&gt; Any:. Input: scalar, list or tuple. Output: JSON-compatible value. |
| invariants | Lists and tuples are recursively rebuilt; Decimal/date are tagged and other scalar values pass through. |
| ownership | Builds new list values recursively and tagged date/decimal dictionaries; other scalar inputs pass through. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0024

[Lines 130–131](../../../../../tests/integration/binding.py#L130); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def value_key(value: Any) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the deterministic JSON identity for one scalar or row. |
| inputs / outputs | Callable: def value_key(value: Any) -&gt; str:. Input: value. Output: compact JSON string after scalar tagging. |
| invariants | Row identity uses json_scalar followed by the same sorted-key JSON encoder used by comparisons. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0026

[Lines 134–135](../../../../../tests/integration/binding.py#L134); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def rows_key(rows: list[tuple[Any, ...]]) -> collections.Counter[str]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Count typed row identities without losing duplicate multiplicity. |
| inputs / outputs | Callable: def rows_key(rows: list\[tuple\[Any, ...\]\]) -&gt; collections.Counter\[str\]:. Input: sequence of tuple rows. Output: Counter keyed by canonical JSON. |
| invariants | Counter multiplicity is retained; this is a bag key for the manual fixture comparison. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0028

[Lines 138–189](../../../../../tests/integration/binding.py#L138); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def validate_expression_arena(result: dict[str, Any], label: str, source: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check shape, IDs, types, source locations and reference order in a SQL binder expression result. |
| inputs / outputs | Callable: def validate_expression_arena(result: dict\[str, Any\], label: str, source: str) -&gt; None:. Inputs: result object, label and original SQL source. Output: None. |
| invariants | Column/parameter/predicate/output references must point into declared result arrays; operation arguments point backward. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Visits each returned expression, predicate, output and argument reference in the finite result. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0030

[Lines 192–196](../../../../../tests/integration/binding.py#L192); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def sql_truth(value: Any) -> bool | None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a SQL predicate value to be Boolean or NULL and preserve UNKNOWN. |
| inputs / outputs | Callable: def sql_truth(value: Any) -&gt; bool \| None:. Input: value. Output: bool or None. |
| invariants | Only None or an object whose exact type is bool is accepted; integer 0/1 is rejected. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0032

[Lines 199–267](../../../../../tests/integration/binding.py#L199); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def eval_expression(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate one binder expression node against an occurrence row and parameter vector, memoizing by node ID. |
| inputs / outputs | Callable: def eval_expression(. Inputs: expression ID, arena, joined row, parameter values and memo. Output: scalar or NULL. |
| invariants | The helper trusts a previously validated arena, memoizes each visited expression ID, and treats comparison with NULL as UNKNOWN. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0034

[Lines 270–304](../../../../../tests/integration/binding.py#L270); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def interpret(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate the returned binder arena over the finite product of fixture occurrence rows. |
| inputs / outputs | Callable: def interpret(. Inputs: binder result, table data and parameter values. Output: projected tuple rows and optional EXISTS value. |
| invariants | A predicate keeps a row only when its evaluated value is exactly True; set semantics deduplicate by canonical JSON and EXISTS reduces to Boolean presence. |
| ownership | Returns newly assembled projected tuple rows; its table data, binder result and parameter values are borrowed during evaluation. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Enumerates the Cartesian product of rows for bound occurrences, evaluates predicates and outputs, then applies set or EXISTS semantics. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json), [tests/frontend/binding/catalog.json](../../../../../tests/frontend/binding/catalog.json), [tests/frontend/binding/data.json](../../../../../tests/frontend/binding/data.json) |

## B0036

[Lines 307–310](../../../../../tests/integration/binding.py#L307); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def expected_rows(case: dict[str, Any], fixture: dict[str, Any]) -> list[tuple[Any, ...]]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode optional manually listed expected rows from one case fixture. |
| inputs / outputs | Callable: def expected_rows(case: dict\[str, Any\], fixture: dict\[str, Any\]) -&gt; list\[tuple\[Any, ...\]\]:. Inputs: case and fixture expectation. Output: tuple rows, or empty list when absent. |
| invariants | Absence of expected_rows yields an empty list; callers use the key-presence test to distinguish absent expectation from explicit empty expectation. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0038

[Lines 313–317](../../../../../tests/integration/binding.py#L313); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def validate_expected_rows(case: dict[str, Any], fixture: dict[str, Any], actual_rows: list[tuple[Any, ...]]) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the interpreted output multiset with manually supplied expected rows when present. |
| inputs / outputs | Callable: def validate_expected_rows(case: dict\[str, Any\], fixture: dict\[str, Any\], actual_rows: list\[tuple\[Any, ...\]\]) -&gt; None:. Inputs: case, fixture expectation and actual rows. Output: None. |
| invariants | No manual comparison runs when expected_rows is absent; present rows are compared as a multiset. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0040

[Lines 320–326](../../../../../tests/integration/binding.py#L320); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def offset_coordinates(source: str, byte_offset: int) -> tuple[int, int, int]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert a UTF-8 byte offset into one-based character position, line and character column. |
| inputs / outputs | Callable: def offset_coordinates(source: str, byte_offset: int) -&gt; tuple\[int, int, int\]:. Inputs: source text and byte offset. Output: three integer coordinates. |
| invariants | The offset must end on a valid UTF-8 boundary; returned character, line and column positions are one-based. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0042

[Lines 329–342](../../../../../tests/integration/binding.py#L329); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_location_marker(case: dict[str, Any], diagnostic: dict[str, Any], source: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check byte and Unicode-aware source coordinates for an optional diagnostic marker. |
| inputs / outputs | Callable: def check_location_marker(case: dict\[str, Any\], diagnostic: dict\[str, Any\], source: str) -&gt; None:. Inputs: case, diagnostic and SQL source. Output: None; absent markers skip the check. |
| invariants | Only the first occurrence of the marker determines the expected byte offset; no marker means no coordinate assertion. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | A missing marker, wrong byte offset or wrong character/line/column coordinate raises RuntimeError. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json), [docs/sql_binding.md § Result shape and diagnostics](../../../../sql_binding.md) |

## B0044

[Lines 345–361](../../../../../tests/integration/binding.py#L345); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def run_binding(executable: str, base: Path, case: dict[str, Any], catalog_path: Path) -> tuple[dict[str, Any], str]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Resolve fixture SQL/parameter paths under the fixture root and invoke bind-sql. |
| inputs / outputs | Callable: def run_binding(executable: str, base: Path, case: dict\[str, Any\], catalog_path: Path) -&gt; tuple\[dict\[str, Any\], str\]:. Inputs: executable, base directory, case and canonical catalog path. Output: result object and original SQL text. |
| invariants | Resolved SQL and parameter paths must remain under the fixture root; a successful bind must write no stderr. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Escaping fixture paths, unreadable SQL, stderr on successful binding and invalid stdout fail as RuntimeError. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0046

[Lines 364–380](../../../../../tests/integration/binding.py#L364); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def validate_occurrences(result: dict[str, Any], expected: list[dict[str, Any]], label: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare binder occurrence table/alias/inheritance and basic ID/column/location shapes. |
| inputs / outputs | Callable: def validate_occurrences(result: dict\[str, Any\], expected: list\[dict\[str, Any\]\], label: str) -&gt; None:. Inputs: result, expected occurrence list and label. Output: None. |
| invariants | Occurrence order must equal manifest order; table/alias/inheritance are compared, IDs are nonnegative, and source location may be absent. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0048

[Lines 383–450](../../../../../tests/integration/binding.py#L383); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def validate_success(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a successful bind result against manifest expectations and independent finite interpreters. |
| inputs / outputs | Callable: def validate_success(. Inputs: executable, fixture roots, canonical catalog, data and case. Output: interpreted output rows. |
| invariants | The success result must have exactly SUCCESS_FIELDS and preserve the original SQL/catalog; optional expectations are checked only when declared. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Validates one binder result, interprets its fixture product and optionally runs the SQLite comparison. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json), [docs/sql_binding.md § Result shape and diagnostics](../../../../sql_binding.md), [tests/frontend/binding/catalog.json](../../../../../tests/frontend/binding/catalog.json), [tests/frontend/binding/data.json](../../../../../tests/frontend/binding/data.json) |

## B0050

[Lines 453–460](../../../../../tests/integration/binding.py#L453); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def sqlite_value(value: Any) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert Decimal, date and Boolean model scalars into SQLite bind values. |
| inputs / outputs | Callable: def sqlite_value(value: Any) -&gt; Any:. Input: typed model value. Output: fixed text, ISO date, integer Boolean, or passthrough value. |
| invariants | Decimal/date are converted before the Boolean branch; Boolean uses integer 0/1 and other values pass through. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0052

[Lines 463–473](../../../../../tests/integration/binding.py#L463); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def sqlite_typed_value(value: Any, sql_type: dict[str, Any]) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert a SQLite result back to the scalar kind declared by the binder result. |
| inputs / outputs | Callable: def sqlite_typed_value(value: Any, sql_type: dict\[str, Any\]) -&gt; Any:. Inputs: value and binder SQL type. Output: typed Decimal/date/bool or passthrough value. |
| invariants | NULL remains None; Boolean/decimal/date conversion is selected from the bound output type. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0054

[Lines 476–477](../../../../../tests/integration/binding.py#L476); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def quote_identifier(name: str) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Quote one SQLite table or column identifier by doubling embedded quotes. |
| inputs / outputs | Callable: def quote_identifier(name: str) -&gt; str:. Input: identifier. Output: double-quoted SQL identifier. |
| invariants | Every embedded quote is doubled and the result is enclosed in double quotes. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0056

[Lines 480–524](../../../../../tests/integration/binding.py#L480); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def run_sqlite(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the fixture SQL against an in-memory SQLite copy of only the bound table occurrences. |
| inputs / outputs | Callable: def run_sqlite(. Inputs: case, SQL source, catalog, row data, parameters and bound result. Output: typed rows and output names. |
| invariants | Only catalog tables referenced by bound occurrences are created; zero-column tables are rejected and SQL parameters are bound positionally. |
| ownership | Owns a temporary SQLite connection and closes it in finally on success or failure; returned rows/names are Python values. |
| failure | SQLite execution errors are wrapped with the case label; the connection closes in finally. |
| cost | Creates the used in-memory tables, inserts fixture rows, executes one SQL statement and fetches its result. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json), [tests/frontend/binding/catalog.json](../../../../../tests/frontend/binding/catalog.json), [tests/frontend/binding/data.json](../../../../../tests/frontend/binding/data.json) |

## B0058

[Lines 527–542](../../../../../tests/integration/binding.py#L527); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def validate_failure(executable: str, base: Path, catalog_path: Path, case: dict[str, Any]) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the binder's failure envelope, exact diagnostic fields/code and optional source location. |
| inputs / outputs | Callable: def validate_failure(executable: str, base: Path, catalog_path: Path, case: dict\[str, Any\]) -&gt; None:. Inputs: executable, fixture paths, canonical catalog and failure case. Output: None. |
| invariants | The failure object must have exactly six diagnostic fields and the envelope phase/code must match the manifest. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | The function requires the exact failure envelope and diagnostic keys; optional location mismatch fails through check_location_marker. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json), [docs/sql_binding.md § Result shape and diagnostics](../../../../sql_binding.md) |

## B0060

[Lines 545–580](../../../../../tests/integration/binding.py#L545); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def validate_cli_errors(executable: str, base: Path, catalog_path: Path,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run manifest-defined CLI usage/file errors and check exit code, empty stdout and structured stderr code. |
| inputs / outputs | Callable: def validate_cli_errors(executable: str, base: Path, catalog_path: Path,. Inputs: executable, fixture root, catalog path and manifest. Output: None. |
| invariants | Every CLI error requires exit status 2, empty stdout and an object-valued nested error with the expected code. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Wrong exit, stdout, JSON envelope or diagnostic code raises RuntimeError. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0062

[Lines 583–631](../../../../../tests/integration/binding.py#L583); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main() -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load the binder manifest and run all success, failure and CLI error cases. |
| inputs / outputs | Callable: def main() -&gt; int:. Input: executable and fixture directory in argv. Output: zero after printing case counts. |
| invariants | Success case names are unique across success/failure lists; row-equivalence links are checked only after all success rows exist. |
| ownership | Owns manifest/model dictionaries, subprocess results and row caches only for the runner lifetime. |
| failure | Argument and fixture validation failures raise RuntimeError; the module guard writes the message and exits 1. |
| cost | Runs each manifest success, failure and CLI error entry once, then checks declared row-equivalence pairs. |
| Design | [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |

## B0063

[Lines 632–639](../../../../../tests/integration/binding.py#L632); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Load the binder manifest and run all success, failure and CLI error cases. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Pass the delegated return value to Python SystemExit; main controls that explicit exit status. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | The process boundary formats only RuntimeError to stderr, as shown in the source, then raises SystemExit(1). SystemExit/KeyboardInterrupt and unlisted exceptions are not converted; diagnostic I/O/allocation failure can still propagate. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. Failure formatting costs its actual diagnostic bytes. |
| Design | [tests/integration/binding.py](../../../../../tests/integration/binding.py), [docs/development.md](../../../../development.md), [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/frontend/bind.cpp](../../../../../src/frontend/bind.cpp), [tests/frontend/binding/manifest.json](../../../../../tests/frontend/binding/manifest.json) |
