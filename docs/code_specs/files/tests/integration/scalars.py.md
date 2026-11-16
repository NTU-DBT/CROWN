# `tests/integration/scalars.py` — block usage map

[Source](../../../../../tests/integration/scalars.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `8df5d5ec7df87dbcb14a0322a95c599c0561d0de1bbe86eb983013e9f9b88eec`. 584 lines partitioned into 59 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–23](../../../../../tests/integration/scalars.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | 1 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 24–27](../../../../../tests/integration/scalars.py#L24) | Callable definition: def require(condition: bool, message: str) -&gt; None: | calls RuntimeError; guard def require(condition: bool, message: str) -&gt; None:; source comment (unverified): # Avoid assert: this runner must keep checking when invoked with python -O. · [reviewed contract](#b0002) |
| [B0003 · 28–29](../../../../../tests/integration/scalars.py#L28) | Explanatory comments or spacing. |  |
| [B0004 · 30–31](../../../../../tests/integration/scalars.py#L30) | Callable definition: def json_text(value: Any) -&gt; str: | calls dumps; returns json.dumps(value, ensure_ascii=False, sort_keys=True, separators=(",", ":")) · [reviewed contract](#b0004) |
| [B0005 · 32–33](../../../../../tests/integration/scalars.py#L32) | Explanatory comments or spacing. |  |
| [B0006 · 34–41](../../../../../tests/integration/scalars.py#L34) | Callable definition: def compare(label: str, actual: Any, expected: Any) -&gt; None: | calls json_text, RuntimeError; source comment (unverified): # JSON text comparison preserves distinctions such as true versus 1. · [reviewed contract](#b0006) |
| [B0007 · 42–43](../../../../../tests/integration/scalars.py#L42) | Explanatory comments or spacing. |  |
| [B0008 · 44–45](../../../../../tests/integration/scalars.py#L44) | Callable definition: def short(value: str, limit: int = 1000) -&gt; str: | calls len; returns value if len(value) &lt;= limit else value\[:limit\] + "…" · [reviewed contract](#b0008) |
| [B0009 · 46–47](../../../../../tests/integration/scalars.py#L46) | Explanatory comments or spacing. |  |
| [B0010 · 48–53](../../../../../tests/integration/scalars.py#L48) | Callable definition: def encode_value(kind: str, value: Any) -&gt; Any: | calls canonical_spelling; returns {"date": canonical_spelling(kind, value)}; {"decimal": canonical_spelling(kind, value)} · [reviewed contract](#b0010) |
| [B0011 · 54–55](../../../../../tests/integration/scalars.py#L54) | Explanatory comments or spacing. |  |
| [B0012 · 56–70](../../../../../tests/integration/scalars.py#L56) | Callable definition: def decimal_key(spelling: Any) -&gt; Decimal: | calls isinstance, is_finite, RuntimeError, str; returns spelling; value · [reviewed contract](#b0012) |
| [B0013 · 71–72](../../../../../tests/integration/scalars.py#L71) | Explanatory comments or spacing. |  |
| [B0014 · 73–85](../../../../../tests/integration/scalars.py#L73) | Callable definition: def canonical_decimal(spelling: str) -&gt; str: | calls fullmatch, RuntimeError, startswith, partition; returns "0"; ("-" if negative else "") + canonical · [reviewed contract](#b0014) |
| [B0015 · 86–87](../../../../../tests/integration/scalars.py#L86) | Explanatory comments or spacing. |  |
| [B0016 · 88–96](../../../../../tests/integration/scalars.py#L88) | Callable definition: def typed_key(kind: str, spelling: Any) -&gt; Any: | calls fromisoformat, str, RuntimeError, decimal_key; returns dt.date.fromisoformat(str(spelling)); decimal_key(spelling) · [reviewed contract](#b0016) |
| [B0017 · 97–98](../../../../../tests/integration/scalars.py#L97) | Explanatory comments or spacing. |  |
| [B0018 · 99–105](../../../../../tests/integration/scalars.py#L99) | Callable definition: def canonical_spelling(kind: str, spelling: Any) -&gt; Any: | calls typed_key, isoformat, format, isinstance; returns typed_key(kind, spelling).isoformat(); canonical_decimal(text) · [reviewed contract](#b0018) |
| [B0019 · 106–107](../../../../../tests/integration/scalars.py#L106) | Explanatory comments or spacing. |  |
| [B0020 · 108–111](../../../../../tests/integration/scalars.py#L108) | Callable definition: def scalar_sort_key(kind: str, spelling: Any) -&gt; Any: | calls typed_key; returns typed_key(kind, spelling); spelling · [reviewed contract](#b0020) |
| [B0021 · 112–113](../../../../../tests/integration/scalars.py#L112) | Explanatory comments or spacing. |  |
| [B0022 · 114–116](../../../../../tests/integration/scalars.py#L114) | Callable definition: def relation_json(kind: str, values: set\[Any\]) -&gt; list\[list\[Any\]\]: | calls sorted, scalar_sort_key, encode_value, canonical_spelling; returns \[\[encode_value(kind, canonical_spelling(kind, value))\] for value in ordered\]; 1 loop sites · [reviewed contract](#b0022) |
| [B0023 · 117–118](../../../../../tests/integration/scalars.py#L117) | Explanatory comments or spacing. |  |
| [B0024 · 119–134](../../../../../tests/integration/scalars.py#L119) | Callable definition: def base_document(kind: str, version: int = 2) -&gt; dict\[str, Any\]: | calls ; returns { · [reviewed contract](#b0024) |
| [B0025 · 135–136](../../../../../tests/integration/scalars.py#L135) | Explanatory comments or spacing. |  |
| [B0026 · 137–153](../../../../../tests/integration/scalars.py#L137) | Callable definition: def single_document(kind: str, initial: list\[Any\], updates: list\[tuple\[str, Any\]\]) -&gt; dict\[str, Any\]: | calls base_document, enumerate; returns document; 2 loop sites; source comment (unverified): # Preserve raw spellings at the input boundary; the independent model alone · [reviewed contract](#b0026) |
| [B0027 · 154–155](../../../../../tests/integration/scalars.py#L154) | Explanatory comments or spacing. |  |
| [B0028 · 156–185](../../../../../tests/integration/scalars.py#L156) | Callable definition: def model_single(kind: str, initial: list\[Any\], updates: list\[tuple\[str, Any\]\]) -&gt; dict\[str, Any\]: | calls typed_key, relation_json, enumerate, set; returns result; growth insert; 2 loop sites · [reviewed contract](#b0028) |
| [B0029 · 186–187](../../../../../tests/integration/scalars.py#L186) | Explanatory comments or spacing. |  |
| [B0030 · 188–202](../../../../../tests/integration/scalars.py#L188) | Callable definition: def random_decimal(rng: random.Random, index: int) -&gt; str: | calls str, randrange, min, len; returns ("-" if index % 2 else "+") + whole + ("." + fraction if separator else ""); source comment (unverified): # Add harmless leading and fractional zeroes to exercise aliases. · [reviewed contract](#b0030) |
| [B0031 · 203–204](../../../../../tests/integration/scalars.py#L203) | Explanatory comments or spacing. |  |
| [B0032 · 205–259](../../../../../tests/integration/scalars.py#L205) | Callable definition: def generated_scalars(kind: str, seed: int) -&gt; tuple\[list\[Any\], list\[tuple\[str, Any\]\]\]: | calls Random, range, randrange, toordinal; returns initial, updates; growth insert; 5 loop sites; source comment (unverified): # A fixed trace includes fresh inserts, aliases, effective deletes, and no-ops. · [reviewed contract](#b0032) |
| [B0033 · 260–261](../../../../../tests/integration/scalars.py#L260) | Explanatory comments or spacing. |  |
| [B0034 · 262–270](../../../../../tests/integration/scalars.py#L262) | Callable definition: def decimal_schema_document_check() -&gt; None: | calls loads, read_text, except, RuntimeError; guard require(schema.get("properties", {}).get("schema_version", {}).get("const") == 2, "v2 schema root v… · [reviewed contract](#b0034) |
| [B0035 · 271–272](../../../../../tests/integration/scalars.py#L271) | Explanatory comments or spacing. |  |
| [B0036 · 273–293](../../../../../tests/integration/scalars.py#L273) | Callable definition: def call(executable: str, command: str, document: dict\[str, Any\], temp: Path, label: str) -&gt; tuple\[int, Any, str, str\]: | calls write_text, dumps, run, str; returns process.returncode, payload, process.stdout, process.stderr · [reviewed contract](#b0036) |
| [B0037 · 294–295](../../../../../tests/integration/scalars.py#L294) | Explanatory comments or spacing. |  |
| [B0038 · 296–330](../../../../../tests/integration/scalars.py#L296) | Callable definition: def canonical_document(document: dict\[str, Any\]) -&gt; dict\[str, Any\]: | calls deepcopy, get, canonical_row, zip; returns tuple(keys), values; canonical; 10 loop sites · [reviewed contract](#b0038) |
| [B0039 · 331–332](../../../../../tests/integration/scalars.py#L331) | Explanatory comments or spacing. |  |
| [B0040 · 333–353](../../../../../tests/integration/scalars.py#L333) | Callable definition: def check_valid_document( | calls call, require, short, compare; guard require(status == 0, f"{label}: oracle exit {status}; stdout={short(stdout)!r}; stderr={short(stder… · [reviewed contract](#b0040) |
| [B0041 · 354–355](../../../../../tests/integration/scalars.py#L354) | Explanatory comments or spacing. |  |
| [B0042 · 356–362](../../../../../tests/integration/scalars.py#L356) | Callable definition: def error_payload(stderr: str, label: str) -&gt; dict\[str, Any\]: | calls loads, RuntimeError, short, require; guard require(isinstance(result, dict) and isinstance(result.get("error"), dict), f"{label}: stderr lacks…; returns result\["error"\] · [reviewed contract](#b0042) |
| [B0043 · 363–364](../../../../../tests/integration/scalars.py#L363) | Explanatory comments or spacing. |  |
| [B0044 · 365–376](../../../../../tests/integration/scalars.py#L365) | Callable definition: def check_rejected( | calls call, require, error_payload, get; guard require(status != 0, f"{label}: invalid document unexpectedly succeeded: {stdout!r}") · [reviewed contract](#b0044) |
| [B0045 · 377–378](../../../../../tests/integration/scalars.py#L377) | Explanatory comments or spacing. |  |
| [B0046 · 379–382](../../../../../tests/integration/scalars.py#L379) | Callable definition: def single_invalid(kind: str, value: Any) -&gt; dict\[str, Any\]: | calls base_document; returns document · [reviewed contract](#b0046) |
| [B0047 · 383–384](../../../../../tests/integration/scalars.py#L383) | Explanatory comments or spacing. |  |
| [B0048 · 385–437](../../../../../tests/integration/scalars.py#L385) | Callable definition: def check_invalid_documents(executable: str, temp: Path) -&gt; int: | calls append, single_invalid, in, base_document; returns len(cases); growth insert; 3 loop sites · [reviewed contract](#b0048) |
| [B0049 · 438–439](../../../../../tests/integration/scalars.py#L438) | Explanatory comments or spacing. |  |
| [B0050 · 440–488](../../../../../tests/integration/scalars.py#L440) | Callable definition: def model_crossjoin( | calls typed_key, result_rows, sorted, encode_value; returns \[; output; growth insert; 10 loop sites · [reviewed contract](#b0050) |
| [B0051 · 489–490](../../../../../tests/integration/scalars.py#L489) | Explanatory comments or spacing. |  |
| [B0052 · 491–525](../../../../../tests/integration/scalars.py#L491) | Callable definition: def crossjoin_document( | calls encode_value, enumerate; returns {; 3 loop sites · [reviewed contract](#b0052) |
| [B0053 · 526–527](../../../../../tests/integration/scalars.py#L526) | Explanatory comments or spacing. |  |
| [B0054 · 528–541](../../../../../tests/integration/scalars.py#L528) | Callable definition: def check_crossjoin(executable: str, temp: Path) -&gt; None: | calls crossjoin_document, model_crossjoin, check_valid_document; growth insert · [reviewed contract](#b0054) |
| [B0055 · 542–543](../../../../../tests/integration/scalars.py#L542) | Explanatory comments or spacing. |  |
| [B0056 · 544–553](../../../../../tests/integration/scalars.py#L544) | Callable definition: def check_v1(executable: str, temp: Path) -&gt; None: | calls base_document, call, require, short; guard require(status == 0, f"version-one legacy document rejected; stdout={short(stdout)!r}; stderr={shor… · [reviewed contract](#b0056) |
| [B0057 · 554–555](../../../../../tests/integration/scalars.py#L554) | Explanatory comments or spacing. |  |
| [B0058 · 556–576](../../../../../tests/integration/scalars.py#L556) | Callable definition: def main() -&gt; int: | calls len, RuntimeError, decimal_schema_document_check, TemporaryDirectory; returns 0; 1 loop sites · [reviewed contract](#b0058) |
| [B0059 · 577–584](../../../../../tests/integration/scalars.py#L577) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0059) |

## B0001

[Lines 1–23](../../../../../tests/integration/scalars.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L23:sha256:4edc13861565fff1685e1bcfd07ac31f3c8413f24b43eebc67bde7f6dc93794d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for scalars.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/integration/scalars.py](../../../../../tests/integration/scalars.py), [docs/scalars.md](../../../../scalars.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 24–27](../../../../../tests/integration/scalars.py#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(condition: bool, message: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail one scalar-document precondition explicitly. |
| inputs / outputs | Callable: def require(condition: bool, message: str) -&gt; None:. Inputs: Boolean condition and diagnostic message. Output: None on success. |
| invariants | Uses an if statement, so the check remains active under Python -O. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0004

[Lines 30–31](../../../../../tests/integration/scalars.py#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def json_text(value: Any) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize expected scalar fixtures into stable compact JSON. |
| inputs / outputs | Callable: def json_text(value: Any) -&gt; str:. Input: JSON-compatible value. Output: sorted-key compact text. |
| invariants | The encoding distinguishes JSON booleans and numbers. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0006

[Lines 34–41](../../../../../tests/integration/scalars.py#L34); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def compare(label: str, actual: Any, expected: Any) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require equality of actual and expected scalar/oracle JSON. |
| inputs / outputs | Callable: def compare(label: str, actual: Any, expected: Any) -&gt; None:. Inputs: label, actual value, expected value. Output: None or mismatch RuntimeError. |
| invariants | Comparison uses the module's deterministic JSON text. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0008

[Lines 44–45](../../../../../tests/integration/scalars.py#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def short(value: str, limit: int = 1000) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Limit one subprocess diagnostic excerpt by character count. |
| inputs / outputs | Callable: def short(value: str, limit: int = 1000) -&gt; str:. Inputs: text and limit. Output: original text or truncated prefix with ellipsis. |
| invariants | The limit is a Python character count; values longer than it return the first limit characters plus one ellipsis. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0010

[Lines 48–53](../../../../../tests/integration/scalars.py#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def encode_value(kind: str, value: Any) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode date and decimal model values in the input document's tagged form. |
| inputs / outputs | Callable: def encode_value(kind: str, value: Any) -&gt; Any:. Inputs: kind and value. Output: tagged date/decimal object or unchanged value. |
| invariants | Canonical spelling is applied only to the date and decimal kinds. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0012

[Lines 56–70](../../../../../tests/integration/scalars.py#L56); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def decimal_key(spelling: Any) -> Decimal:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse and validate one finite decimal spelling for model equality. |
| inputs / outputs | Callable: def decimal_key(spelling: Any) -&gt; Decimal:. Input: Decimal or string-like spelling. Output: Decimal. |
| invariants | The accepted grammar is fixed-point signed ASCII digits; non-finite and malformed values fail. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Malformed or non-finite spellings become RuntimeError; Decimal conversion errors are wrapped where caught. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0014

[Lines 73–85](../../../../../tests/integration/scalars.py#L73); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def canonical_decimal(spelling: str) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Normalize one valid fixed-point spelling without calling the C++ parser. |
| inputs / outputs | Callable: def canonical_decimal(spelling: str) -&gt; str:. Input: decimal string. Output: canonical decimal text. |
| invariants | Leading zeros and fractional trailing zeros are removed; all numeric zero spellings become 0. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0016

[Lines 88–96](../../../../../tests/integration/scalars.py#L88); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def typed_key(kind: str, spelling: Any) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert date and decimal spellings to comparable standard-library values. |
| inputs / outputs | Callable: def typed_key(kind: str, spelling: Any) -&gt; Any:. Inputs: kind and spelling. Output: datetime.date, Decimal, or passthrough value. |
| invariants | Date and decimal values compare by datetime.date and Decimal semantics, so valid spelling aliases share a key. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Invalid dates and decimals raised during model construction become RuntimeError. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0018

[Lines 99–105](../../../../../tests/integration/scalars.py#L99); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def canonical_spelling(kind: str, spelling: Any) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render typed model values into canonical date or decimal fixture spelling. |
| inputs / outputs | Callable: def canonical_spelling(kind: str, spelling: Any) -&gt; Any:. Inputs: kind and value. Output: canonical date/decimal string or passthrough value. |
| invariants | Dates use isoformat; Decimal input is rendered with fixed-point format before decimal normalization. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0020

[Lines 108–111](../../../../../tests/integration/scalars.py#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def scalar_sort_key(kind: str, spelling: Any) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose the Python ordering key used for one scalar kind. |
| inputs / outputs | Callable: def scalar_sort_key(kind: str, spelling: Any) -&gt; Any:. Inputs: kind and spelling. Output: typed date/decimal key or original value. |
| invariants | Date/decimal order is semantic typed order; other kinds use their native Python order. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0022

[Lines 114–116](../../../../../tests/integration/scalars.py#L114); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def relation_json(kind: str, values: set[Any]) -> list[list[Any]]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sort a set of typed scalar values and encode each as a one-column relation row. |
| inputs / outputs | Callable: def relation_json(kind: str, values: set\[Any\]) -&gt; list\[list\[Any\]\]:. Inputs: scalar kind and value set. Output: nested JSON rows. |
| invariants | Set values are sorted by scalar_sort_key and each result row contains exactly one encoded cell. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0024

[Lines 119–134](../../../../../tests/integration/scalars.py#L119); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def base_document(kind: str, version: int = 2) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the minimal one-table CQ document for a scalar kind and schema version. |
| inputs / outputs | Callable: def base_document(kind: str, version: int = 2) -&gt; dict\[str, Any\]:. Inputs: kind and root version. Output: document with empty initial relation and updates. |
| invariants | The relation has set semantics, one source table/atom, one head variable, and empty initial/updates. |
| ownership | Returns a newly allocated nested document tree. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [schemas/cq-v2.schema.json](../../../../../schemas/cq-v2.schema.json), [docs/scalars.md § Document and artifact versions](../../../../scalars.md) |

## B0026

[Lines 137–153](../../../../../tests/integration/scalars.py#L137); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def single_document(kind: str, initial: list[Any], updates: list[tuple[str, Any]]) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Add raw scalar spellings and contiguous sequence-numbered updates to a v2 document. |
| inputs / outputs | Callable: def single_document(kind: str, initial: list\[Any\], updates: list\[tuple\[str, Any\]\]) -&gt; dict\[str, Any\]:. Inputs: kind, initial spellings and operation/value pairs. Output: CQ document. |
| invariants | Initial and update tagged strings retain their spelling before reaching the native reader. |
| ownership | Mutates the newly built base document; scalar spellings remain represented in its new tagged rows. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0028

[Lines 156–185](../../../../../tests/integration/scalars.py#L156); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def model_single(kind: str, initial: list[Any], updates: list[tuple[str, Any]]) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute initial and per-update set relations/deltas using Python typed values. |
| inputs / outputs | Callable: def model_single(kind: str, initial: list\[Any\], updates: list\[tuple\[str, Any\]\]) -&gt; dict\[str, Any\]:. Inputs: kind, initial spellings and operations. Output: reference_recompute result envelope. |
| invariants | Initial and update aliases collapse under typed set identity; absent deletes and duplicate inserts are no-ops. |
| ownership | Builds a fresh state set and result tree; input lists are read but not mutated. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Applies each supplied operation to a Python set and materializes current/added/removed relations per sequence. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0030

[Lines 188–202](../../../../../tests/integration/scalars.py#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def random_decimal(rng: random.Random, index: int) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create a seeded decimal alias with bounded digits, optional fraction, sign and extra zeros. |
| inputs / outputs | Callable: def random_decimal(rng: random.Random, index: int) -&gt; str:. Inputs: Random instance and index. Output: fixed-point decimal spelling. |
| invariants | The caller-provided Random state determines output; the index selects sign and the spelling adds leading/fractional zeros. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0032

[Lines 205–259](../../../../../tests/integration/scalars.py#L205); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def generated_scalars(kind: str, seed: int) -> tuple[list[Any], list[tuple[str, Any]]]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create deterministic date or decimal boundaries, aliases and a mixed update trace. |
| inputs / outputs | Callable: def generated_scalars(kind: str, seed: int) -&gt; tuple\[list\[Any\], list\[tuple\[str, Any\]\]\]:. Inputs: scalar kind and seed. Output: initial spellings and operation/value updates. |
| invariants | Date uses the date branch; all other callers are expected to request decimal. Returned traces contain an explicit fresh insert, its alias, and repeated delete. |
| ownership | Returns fresh initial/update lists and uses a local Random instance seeded by the caller. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Creates the fixed boundary values plus eight seeded dates or ten seeded decimals and a finite update sequence. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0034

[Lines 262–270](../../../../../tests/integration/scalars.py#L262); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def decimal_schema_document_check() -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check selected root/type/update version fields in the v2 JSON schema. |
| inputs / outputs | Callable: def decimal_schema_document_check() -&gt; None:. Input: none. Output: None after three schema assertions. |
| invariants | This is a focused field check, not full JSON Schema validation of generated documents. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [schemas/cq-v2.schema.json](../../../../../schemas/cq-v2.schema.json), [docs/scalars.md § Document and artifact versions](../../../../scalars.md) |

## B0036

[Lines 273–293](../../../../../tests/integration/scalars.py#L273); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def call(executable: str, command: str, document: dict[str, Any], temp: Path, label: str) -> tuple[int, Any, str, str]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write one CQ document to a temporary file and invoke a named CROWN CLI command. |
| inputs / outputs | Callable: def call(executable: str, command: str, document: dict\[str, Any\], temp: Path, label: str) -&gt; tuple\[int, Any, str, str\]:. Inputs: executable, command, document, temp directory and label. Output: status, parsed stdout JSON/None, stdout and stderr. |
| invariants | The command status is returned without asserting success; JSON is parsed only when stdout contains non-whitespace text. |
| ownership | Returns completed subprocess result values and owns no process after subprocess.run returns. |
| failure | A timeout becomes RuntimeError; malformed stdout JSON becomes a labeled RuntimeError; nonzero status is returned to the caller. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0038

[Lines 296–330](../../../../../tests/integration/scalars.py#L296); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def canonical_document(document: dict[str, Any]) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the expected canonical document by normalizing, deduplicating and ordering typed rows. |
| inputs / outputs | Callable: def canonical_document(document: dict\[str, Any\]) -&gt; dict\[str, Any\]:. Input: document. Output: deep-copied document with canonical row/value spellings and query defaults. |
| invariants | The input document is deep-copied; initial rows are canonicalized/deduplicated and updates keep sequence metadata while replacing values. |
| ownership | Deep-copies the supplied document before canonicalizing rows, updates and query defaults. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Visits each initial row and update, builds canonical typed keys, deduplicates initial rows and sorts them. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0040

[Lines 333–353](../../../../../tests/integration/scalars.py#L333); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_valid_document(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare CLI oracle output and canonicalization with the independent Python model. |
| inputs / outputs | Callable: def check_valid_document(. Inputs: executable, input document, expected result, temp directory and label. Output: None. |
| invariants | It checks oracle output, canonical form, fixed-point canonicalization and oracle round-trip. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Runs oracle, canonicalize, canonicalize-again and oracle-roundtrip commands for one fixture. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0042

[Lines 356–362](../../../../../tests/integration/scalars.py#L356); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def error_payload(stderr: str, label: str) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse structured stderr and require its nested error object. |
| inputs / outputs | Callable: def error_payload(stderr: str, label: str) -&gt; dict\[str, Any\]:. Inputs: stderr and label. Output: error object. |
| invariants | The JSON root and nested error value must both be dictionaries. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0044

[Lines 365–376](../../../../../tests/integration/scalars.py#L365); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_rejected(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require nonzero CLI rejection with a structured error and optional exact code. |
| inputs / outputs | Callable: def check_rejected(. Inputs: executable, document, temp directory, label and optional expected code. Output: None. |
| invariants | Only a nonzero exit and structured stderr are universal; stdout emptiness and exact code are not required unless separately asserted. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | The document must exit nonzero and stderr must contain a nested error object; exact code is checked when supplied. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0046

[Lines 379–382](../../../../../tests/integration/scalars.py#L379); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def single_invalid(kind: str, value: Any) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Place one raw scalar value into the minimal document's initial row. |
| inputs / outputs | Callable: def single_invalid(kind: str, value: Any) -&gt; dict\[str, Any\]:. Inputs: kind and value. Output: invalid-candidate document; rejection is checked separately. |
| invariants | The candidate raw value is inserted directly into the sole initial cell; no type tag or normalization is added. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0048

[Lines 385–437](../../../../../tests/integration/scalars.py#L385); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_invalid_documents(executable: str, temp: Path) -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run malformed tag, date, decimal, version, collation and scalar-boundary fixtures. |
| inputs / outputs | Callable: def check_invalid_documents(executable: str, temp: Path) -&gt; int:. Inputs: executable and temp directory. Output: number of invalid documents exercised. |
| invariants | Every case must fail, but code equality is asserted only for cases whose expected code is non-None. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Every listed candidate must reject, and each asserted error code must match the expected scalar/version code. |
| cost | Invokes the CLI once for each fixed malformed-document case. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0050

[Lines 440–488](../../../../../tests/integration/scalars.py#L440); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def model_crossjoin(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute the projected date/decimal product and deltas from two witness sets. |
| inputs / outputs | Callable: def model_crossjoin(. Inputs: initial row IDs/date values, row IDs/decimal values and updates. Output: model trace envelope. |
| invariants | Source row IDs distinguish physical rows; the projected output is a set of date/decimal pairs, and input_changed reflects source-row-set changes. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Builds the projected product of the two witness sets before and after every supplied update. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0052

[Lines 491–525](../../../../../tests/integration/scalars.py#L491); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def crossjoin_document(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a v2 document with independent date and decimal witness tables and a two-column head. |
| inputs / outputs | Callable: def crossjoin_document(. Inputs: initial source rows and typed operations. Output: CQ document. |
| invariants | The two atoms share no query variable, so the expected relation is a Cartesian product of distinct date and decimal witnesses. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0054

[Lines 528–541](../../../../../tests/integration/scalars.py#L528); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_crossjoin(executable: str, temp: Path) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the CLI oracle/canonicalizer to one explicit date/decimal product trace. |
| inputs / outputs | Callable: def check_crossjoin(executable: str, temp: Path) -&gt; None:. Inputs: executable and temp directory. Output: None. |
| invariants | The fixture values and updates are fixed literals; expected output is computed before CLI comparison by model_crossjoin. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0056

[Lines 544–553](../../../../../tests/integration/scalars.py#L544); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_v1(executable: str, temp: Path) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check legacy v1 int64 document oracle and canonicalization version preservation. |
| inputs / outputs | Callable: def check_v1(executable: str, temp: Path) -&gt; None:. Inputs: executable and temp directory. Output: None. |
| invariants | The v1 control uses legacy int64 cells and requires both oracle/canonicalizer root versions to remain 1. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp), [schemas/cq-v2.schema.json](../../../../../schemas/cq-v2.schema.json), [docs/scalars.md § Document and artifact versions](../../../../scalars.md) |

## B0058

[Lines 556–576](../../../../../tests/integration/scalars.py#L556); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main() -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the scalar schema, seeded date/decimal traces, crossjoin, invalid documents and v1 compatibility. |
| inputs / outputs | Callable: def main() -&gt; int:. Input: exactly one CROWN executable path. Output: zero and case counts after all assertions. |
| invariants | Only the fixed date/decimal seeds, one crossjoin, the enumerated invalid list and the v1 control are run. |
| ownership | Owns the temporary directory and all generated documents/models only during the runner call. |
| failure | Argument, model and CLI check failures raise RuntimeError; the module guard writes it and exits 1. |
| cost | Runs two seeded single-scalar documents, one crossjoin, the fixed invalid set and one v1 control. |
| Design | [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |

## B0059

[Lines 577–584](../../../../../tests/integration/scalars.py#L577); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Check the scalar schema, seeded date/decimal traces, crossjoin, invalid documents and v1 compatibility. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Pass the delegated return value to Python SystemExit; main controls that explicit exit status. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | The process boundary formats only RuntimeError to stderr, as shown in the source, then raises SystemExit(1). SystemExit/KeyboardInterrupt and unlisted exceptions are not converted; diagnostic I/O/allocation failure can still propagate. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. Failure formatting costs its actual diagnostic bytes. |
| Design | [tests/integration/scalars.py](../../../../../tests/integration/scalars.py), [docs/development.md](../../../../development.md), [docs/scalars.md § Date](../../../../scalars.md), [docs/scalars.md § Decimal](../../../../scalars.md), [src/ir/scalar.cpp](../../../../../src/ir/scalar.cpp), [src/io/document.cpp](../../../../../src/io/document.cpp) |
