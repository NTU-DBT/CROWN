# `tests/integration/catalog.py` — block usage map

[Source](../../../../../tests/integration/catalog.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `cc930b214e1081ba644a8a88cd747e288fce89d16ee7653547bcdbbb895a11f2`. 860 lines partitioned into 83 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–22](../../../../../tests/integration/catalog.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 23–26](../../../../../tests/integration/catalog.py#L23) | Callable definition: def require(condition: bool, message: str) -&gt; None: | calls RuntimeError; guard def require(condition: bool, message: str) -&gt; None:; source comment (unverified): # Keep all checks active under python -O. · [reviewed contract](#b0002) |
| [B0003 · 27–28](../../../../../tests/integration/catalog.py#L27) | Explanatory comments or spacing. |  |
| [B0004 · 29–30](../../../../../tests/integration/catalog.py#L29) | Callable definition: def json_text(value: Any) -&gt; str: | calls dumps; returns json.dumps(value, ensure_ascii=False, sort_keys=True, separators=(",", ":")) · [reviewed contract](#b0004) |
| [B0005 · 31–32](../../../../../tests/integration/catalog.py#L31) | Explanatory comments or spacing. |  |
| [B0006 · 33–37](../../../../../tests/integration/catalog.py#L33) | Callable definition: def compare(label: str, actual: Any, expected: Any) -&gt; None: | calls json_text, RuntimeError · [reviewed contract](#b0006) |
| [B0007 · 38–39](../../../../../tests/integration/catalog.py#L38) | Explanatory comments or spacing. |  |
| [B0008 · 40–41](../../../../../tests/integration/catalog.py#L40) | Callable definition: def short(value: str, limit: int = 1000) -&gt; str: | calls len; returns value if len(value) &lt;= limit else value\[:limit\] + "…" · [reviewed contract](#b0008) |
| [B0009 · 42–43](../../../../../tests/integration/catalog.py#L42) | Explanatory comments or spacing. |  |
| [B0010 · 44–45](../../../../../tests/integration/catalog.py#L44) | Callable definition: def quote_identifier(name: str) -&gt; str: | calls replace; returns '"' + name.replace('"', '""') + '"' · [reviewed contract](#b0010) |
| [B0011 · 46–47](../../../../../tests/integration/catalog.py#L46) | Explanatory comments or spacing. |  |
| [B0012 · 48–74](../../../../../tests/integration/catalog.py#L48) | Callable definition: def invoke( | calls write_text, dumps, run, str; returns process.returncode, payload, process.stdout, process.stderr · [reviewed contract](#b0012) |
| [B0013 · 75–76](../../../../../tests/integration/catalog.py#L75) | Explanatory comments or spacing. |  |
| [B0014 · 77–83](../../../../../tests/integration/catalog.py#L77) | Callable definition: def error_payload(stderr: str, label: str) -&gt; dict\[str, Any\]: | calls loads, RuntimeError, short, require; guard require(isinstance(payload, dict) and isinstance(payload.get("error"), dict), f"{label}: missing st…; returns payload\["error"\] · [reviewed contract](#b0014) |
| [B0015 · 84–85](../../../../../tests/integration/catalog.py#L84) | Explanatory comments or spacing. |  |
| [B0016 · 86–99](../../../../../tests/integration/catalog.py#L86) | Callable definition: def rejected( | calls invoke, require, error_payload, strip; guard require(status != 0, f"{label}: invalid input unexpectedly succeeded: {stdout!r}") · [reviewed contract](#b0016) |
| [B0017 · 100–101](../../../../../tests/integration/catalog.py#L100) | Explanatory comments or spacing. |  |
| [B0018 · 102–103](../../../../../tests/integration/catalog.py#L102) | Callable definition: def standalone(payload: dict\[str, Any\], version: int = 1) -&gt; dict\[str, Any\]: | calls ; returns {"schema_version": version, "catalog": payload} · [reviewed contract](#b0018) |
| [B0019 · 104–105](../../../../../tests/integration/catalog.py#L104) | Explanatory comments or spacing. |  |
| [B0020 · 106–153](../../../../../tests/integration/catalog.py#L106) | Callable definition: def rich_catalog() -&gt; dict\[str, Any\]: | calls ; returns { · [reviewed contract](#b0020) |
| [B0021 · 154–155](../../../../../tests/integration/catalog.py#L154) | Explanatory comments or spacing. |  |
| [B0022 · 156–169](../../../../../tests/integration/catalog.py#L156) | Callable definition: def canonical_catalog_payload(payload: dict\[str, Any\]) -&gt; dict\[str, Any\]: | calls deepcopy, setdefault; returns result; 2 loop sites · [reviewed contract](#b0022) |
| [B0023 · 170–171](../../../../../tests/integration/catalog.py#L170) | Explanatory comments or spacing. |  |
| [B0024 · 172–211](../../../../../tests/integration/catalog.py#L172) | Callable definition: def check_standalone_catalog(executable: str, temp: Path) -&gt; None: | calls rich_catalog, standalone, invoke, require; guard require(status == 0, f"validate-catalog rejected valid metadata; stdout={short(stdout)!r}; stderr={…; returns an object"); 4 loop sites; source comment (unverified): # New defaulted metadata is materialized, so a v1/v2 document can never · [reviewed contract](#b0024) |
| [B0025 · 212–213](../../../../../tests/integration/catalog.py#L212) | Explanatory comments or spacing. |  |
| [B0026 · 214–249](../../../../../tests/integration/catalog.py#L214) | Callable definition: def check_bad_catalogs(executable: str, temp: Path) -&gt; int: | calls mutate, deepcopy, rich_catalog, edit; returns len(cases); 2 loop sites · [reviewed contract](#b0026) |
| [B0027 · 250–251](../../../../../tests/integration/catalog.py#L250) | Explanatory comments or spacing. |  |
| [B0028 · 252–253](../../../../../tests/integration/catalog.py#L252) | Callable definition: def catalog_payload(tables: list\[dict\[str, Any\]\], version: int = 1) -&gt; dict\[str, Any\]: | calls ; returns {"version": version, "tables": tables} · [reviewed contract](#b0028) |
| [B0029 · 254–255](../../../../../tests/integration/catalog.py#L254) | Explanatory comments or spacing. |  |
| [B0030 · 256–272](../../../../../tests/integration/catalog.py#L256) | Callable definition: def cq_document( | calls dict, enumerate; returns {; 1 loop sites · [reviewed contract](#b0030) |
| [B0031 · 273–274](../../../../../tests/integration/catalog.py#L273) | Explanatory comments or spacing. |  |
| [B0032 · 275–285](../../../../../tests/integration/catalog.py#L275) | Callable definition: def normalize_decimal(text: str) -&gt; str: | calls require, fullmatch, startswith, partition; guard require(DECIMAL_GRAMMAR.fullmatch(text) is not None, f"test input has malformed decimal {text!r}"); returns "0"; ("-" if negative else "") + canonical · [reviewed contract](#b0032) |
| [B0033 · 286–287](../../../../../tests/integration/catalog.py#L286) | Explanatory comments or spacing. |  |
| [B0034 · 288–322](../../../../../tests/integration/catalog.py#L288) | Callable definition: def normalize_value(kind: str, value: Any, decimal_spec: dict\[str, int\] \| None = None) -&gt; Any: | calls require, isinstance, set, fromisoformat; guard require(isinstance(value, dict) and set(value) == {"date"} and isinstance(value\["date"\], str), "dat…; returns canonical; canonical · [reviewed contract](#b0034) |
| [B0035 · 323–324](../../../../../tests/integration/catalog.py#L323) | Explanatory comments or spacing. |  |
| [B0036 · 325–331](../../../../../tests/integration/catalog.py#L325) | Callable definition: def sql_value(kind: str, value: Any, decimal_spec: dict\[str, int\] \| None = None) -&gt; Any: | calls normalize_value, int; returns normalized; int(normalized) · [reviewed contract](#b0036) |
| [B0037 · 332–333](../../../../../tests/integration/catalog.py#L332) | Explanatory comments or spacing. |  |
| [B0038 · 334–341](../../../../../tests/integration/catalog.py#L334) | Callable definition: def output_value(kind: str, value: Any) -&gt; Any: | calls str, normalize_decimal, bool; returns {"date": str(value)}; {"decimal": normalize_decimal(str(value))} · [reviewed contract](#b0038) |
| [B0039 · 342–343](../../../../../tests/integration/catalog.py#L342) | Explanatory comments or spacing. |  |
| [B0040 · 344–353](../../../../../tests/integration/catalog.py#L344) | Callable definition: def output_sort_key(kind: str, value: Any) -&gt; Any: | calls fromisoformat, Decimal, encode; returns dt.date.fromisoformat(value\["date"\]); Decimal(value\["decimal"\]) · [reviewed contract](#b0040) |
| [B0041 · 354–358](../../../../../tests/integration/catalog.py#L354) | declares aliases; declares types or opens a type body. |  · [reviewed contract](#b0041) |
| [B0042 · 359–369](../../../../../tests/integration/catalog.py#L359) | Callable definition: def __init__(self, document: dict\[str, Any\]): | calls connect, execute, set, _create_tables; guard require(not check, f"valid fixture has SQLite foreign-key violations: {check!r}"); 2 loop sites · [reviewed contract](#b0042) |
| [B0043 · 370–370](../../../../../tests/integration/catalog.py#L370) | Explanatory comments or spacing. |  |
| [B0044 · 371–392](../../../../../tests/integration/catalog.py#L371) | Callable definition: def _create_tables(self) -&gt; None: | calls get, append, quote_identifier, join; 5 loop sites · [reviewed contract](#b0044) |
| [B0045 · 393–393](../../../../../tests/integration/catalog.py#L393) | Explanatory comments or spacing. |  |
| [B0046 · 394–395](../../../../../tests/integration/catalog.py#L394) | Callable definition: def _table_types(self, table_name: str) -&gt; list\[tuple\[str, dict\[str, int\] \| None\]\]: | calls get; returns \[(column\["type"\], column.get("decimal")) for column in self.tables\[table_name\]\["columns"\]\]; 1 loop sites · [reviewed contract](#b0046) |
| [B0047 · 396–396](../../../../../tests/integration/catalog.py#L396) | Explanatory comments or spacing. |  |
| [B0048 · 397–400](../../../../../tests/integration/catalog.py#L397) | Callable definition: def normalize_row(self, table_name: str, raw_row: list\[Any\]) -&gt; tuple\[Any, ...\]: | calls _table_types, require, len, tuple; guard require(len(raw_row) == len(types), f"fixture row arity mismatch in {table_name}: {raw_row!r}"); returns tuple(normalize_value(kind, value, spec) for (kind, spec), value in zip(types, raw_row)); 1 loop sites · [reviewed contract](#b0048) |
| [B0049 · 401–401](../../../../../tests/integration/catalog.py#L401) | Explanatory comments or spacing. |  |
| [B0050 · 402–405](../../../../../tests/integration/catalog.py#L402) | Callable definition: def sql_row(self, table_name: str, raw_row: list\[Any\]) -&gt; tuple\[Any, ...\]: | calls _table_types, require, len, tuple; guard require(len(raw_row) == len(types), f"fixture row arity mismatch in {table_name}: {raw_row!r}"); returns tuple(sql_value(kind, value, spec) for (kind, spec), value in zip(types, raw_row)); 1 loop sites · [reviewed contract](#b0050) |
| [B0051 · 406–406](../../../../../tests/integration/catalog.py#L406) | Explanatory comments or spacing. |  |
| [B0052 · 407–416](../../../../../tests/integration/catalog.py#L407) | Callable definition: def _has_row(self, table_name: str, normalized: tuple\[Any, ...\]) -&gt; bool: | calls join, quote_identifier, execute, sql_row; returns normalized in self.rows\[table_name\]; found is not None; 2 loop sites · [reviewed contract](#b0052) |
| [B0053 · 417–417](../../../../../tests/integration/catalog.py#L417) | Explanatory comments or spacing. |  |
| [B0054 · 418–433](../../../../../tests/integration/catalog.py#L418) | Callable definition: def _insert(self, table_name: str, raw_row: list\[Any\]) -&gt; bool: | calls normalize_row, sql_row, join, quote_identifier; returns False; True; 3 loop sites · [reviewed contract](#b0054) |
| [B0055 · 434–434](../../../../../tests/integration/catalog.py#L434) | Explanatory comments or spacing. |  |
| [B0056 · 435–445](../../../../../tests/integration/catalog.py#L435) | Callable definition: def _delete(self, table_name: str, raw_row: list\[Any\]) -&gt; bool: | calls normalize_row, join, quote_identifier, execute; returns False; True; 2 loop sites · [reviewed contract](#b0056) |
| [B0057 · 446–446](../../../../../tests/integration/catalog.py#L446) | Explanatory comments or spacing. |  |
| [B0058 · 447–454](../../../../../tests/integration/catalog.py#L447) | Callable definition: def _load_initial(self) -&gt; None: | calls get, visible, _insert, commit; 2 loop sites; source comment (unverified): # CROWN's exact full-row duplicate is a set no-op. For all · [reviewed contract](#b0058) |
| [B0059 · 455–455](../../../../../tests/integration/catalog.py#L455) | Explanatory comments or spacing. |  |
| [B0060 · 456–502](../../../../../tests/integration/catalog.py#L456) | Callable definition: def relation(self) -&gt; list\[list\[Any\]\]: | calls enumerate, append, quote_identifier, require; guard require(len(atom\["terms"\]) == len(table\["columns"\]), f"atom arity mismatch in oracle fixture {atom\[…; returns result; 6 loop sites · [reviewed contract](#b0060) |
| [B0061 · 503–503](../../../../../tests/integration/catalog.py#L503) | Explanatory comments or spacing. |  |
| [B0062 · 504–536](../../../../../tests/integration/catalog.py#L504) | Callable definition: def trace(self) -&gt; dict\[str, Any\]: | calls relation, get, json_text, execute; returns output; growth insert; 5 loop sites · [reviewed contract](#b0062) |
| [B0063 · 537–538](../../../../../tests/integration/catalog.py#L537) | Explanatory comments or spacing. |  |
| [B0064 · 539–566](../../../../../tests/integration/catalog.py#L539) | Callable definition: def check_valid_document(executable: str, document: dict\[str, Any\], temp: Path, label: str) -&gt; None: | calls SQLiteTrace, trace, invoke, require; guard require(status == 0, f"{label}: oracle exit {status}; stdout={short(stdout)!r}; stderr={short(stder…; returns an object"); 3 loop sites · [reviewed contract](#b0064) |
| [B0065 · 567–568](../../../../../tests/integration/catalog.py#L567) | Explanatory comments or spacing. |  |
| [B0066 · 569–582](../../../../../tests/integration/catalog.py#L569) | Callable definition: def check_query_binding(executable: str, document: dict\[str, Any\], temp: Path, label: str, expected_version: int) -&gt; None: | calls invoke, require, short, compare; guard require(status == 0, f"{label}: tree-oracle failed; stdout={short(stdout)!r}; stderr={short(stderr)…; 1 loop sites · [reviewed contract](#b0066) |
| [B0067 · 583–584](../../../../../tests/integration/catalog.py#L583) | Explanatory comments or spacing. |  |
| [B0068 · 585–613](../../../../../tests/integration/catalog.py#L585) | Callable definition: def join_catalog() -&gt; dict\[str, Any\]: | calls ; returns { · [reviewed contract](#b0068) |
| [B0069 · 614–615](../../../../../tests/integration/catalog.py#L614) | Explanatory comments or spacing. |  |
| [B0070 · 616–641](../../../../../tests/integration/catalog.py#L616) | Callable definition: def join_document() -&gt; dict\[str, Any\]: | calls join_catalog, cq_document; returns cq_document(; growth insert · [reviewed contract](#b0070) |
| [B0071 · 642–643](../../../../../tests/integration/catalog.py#L642) | Explanatory comments or spacing. |  |
| [B0072 · 644–666](../../../../../tests/integration/catalog.py#L644) | Callable definition: def self_reference_document() -&gt; dict\[str, Any\]: | calls catalog_payload, cq_document; returns cq_document(; growth insert · [reviewed contract](#b0072) |
| [B0073 · 667–668](../../../../../tests/integration/catalog.py#L667) | Explanatory comments or spacing. |  |
| [B0074 · 669–700](../../../../../tests/integration/catalog.py#L669) | Callable definition: def untrusted_metadata_document() -&gt; dict\[str, Any\]: | calls catalog_payload, cq_document; returns cq_document( · [reviewed contract](#b0074) |
| [B0075 · 701–702](../../../../../tests/integration/catalog.py#L701) | Explanatory comments or spacing. |  |
| [B0076 · 703–719](../../../../../tests/integration/catalog.py#L703) | Callable definition: def decimal_spec_document() -&gt; dict\[str, Any\]: | calls catalog_payload, cq_document; returns cq_document(; growth insert · [reviewed contract](#b0076) |
| [B0077 · 720–721](../../../../../tests/integration/catalog.py#L720) | Explanatory comments or spacing. |  |
| [B0078 · 722–755](../../../../../tests/integration/catalog.py#L722) | Callable definition: def check_format_compatibility(executable: str, temp: Path) -&gt; None: | calls in, cq_document, catalog_payload, invoke; guard require(status == 0, f"format {version} document rejected; stdout={short(stdout)!r}; stderr={short(…; growth insert; 2 loop sites; source comment (unverified): # Legacy documents omit all metadata and continue using their own format · [reviewed contract](#b0078) |
| [B0079 · 756–757](../../../../../tests/integration/catalog.py#L756) | Explanatory comments or spacing. |  |
| [B0080 · 758–823](../../../../../tests/integration/catalog.py#L758) | Callable definition: def check_constraint_rejections(executable: str, temp: Path) -&gt; int: | calls catalog_payload, cq_document, rejected, decimal_spec_document; returns len(cases) + 3; growth insert; 1 loop sites · [reviewed contract](#b0080) |
| [B0081 · 824–825](../../../../../tests/integration/catalog.py#L824) | Explanatory comments or spacing. |  |
| [B0082 · 826–852](../../../../../tests/integration/catalog.py#L826) | Callable definition: def main() -&gt; int: | calls len, RuntimeError, TemporaryDirectory, Path; returns 0; 1 loop sites · [reviewed contract](#b0082) |
| [B0083 · 853–860](../../../../../tests/integration/catalog.py#L853) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0083) |

## B0001

[Lines 1–22](../../../../../tests/integration/catalog.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L22:sha256:323b91f17a4940fe89db763984523f1cf86b62ff0635c699d9793bcca75ab729
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for catalog.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/integration/catalog.py](../../../../../tests/integration/catalog.py), [docs/catalog.md](../../../../catalog.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 23–26](../../../../../tests/integration/catalog.py#L23); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(condition: bool, message: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail immediately when a catalog fixture precondition is false. |
| inputs / outputs | Callable: def require(condition: bool, message: str) -&gt; None:. Inputs: Boolean condition and diagnostic message. Output: None on success. |
| invariants | The check remains active under Python optimization because it is an explicit conditional. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0004

[Lines 29–30](../../../../../tests/integration/catalog.py#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def json_text(value: Any) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize a value into deterministic compact JSON for test comparisons and row keys. |
| inputs / outputs | Callable: def json_text(value: Any) -&gt; str:. Input: a JSON-compatible Python value. Output: sorted-key compact UTF-8-capable JSON text. |
| invariants | Key order is sorted, separators are compact, and non-ASCII text remains literal. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Serializes the supplied JSON-compatible tree once. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0006

[Lines 33–37](../../../../../tests/integration/catalog.py#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def compare(label: str, actual: Any, expected: Any) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require deep equality through the fixture's stable JSON representation. |
| inputs / outputs | Callable: def compare(label: str, actual: Any, expected: Any) -&gt; None:. Inputs: label, actual value, expected value. Output: None or a mismatch exception. |
| invariants | Comparison is by serialized JSON text; it distinguishes JSON true from JSON integer 1. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0008

[Lines 40–41](../../../../../tests/integration/catalog.py#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def short(value: str, limit: int = 1000) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bound a diagnostic excerpt while preserving short values unchanged. |
| inputs / outputs | Callable: def short(value: str, limit: int = 1000) -&gt; str:. Inputs: text and maximum character count. Output: original text or a prefix plus ellipsis. |
| invariants | The limit counts Python characters, not encoded bytes. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0010

[Lines 44–45](../../../../../tests/integration/catalog.py#L44); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def quote_identifier(name: str) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Quote a SQLite identifier by doubling embedded double quotes. |
| inputs / outputs | Callable: def quote_identifier(name: str) -&gt; str:. Input: identifier text. Output: one double-quoted SQL identifier. |
| invariants | Only identifier quoting is performed; this is not SQL value escaping. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0012

[Lines 48–74](../../../../../tests/integration/catalog.py#L48); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def invoke(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write one catalog or CQ document fixture and invoke one CROWN CLI command. |
| inputs / outputs | Callable: def invoke(. Inputs: executable, command, document, temporary directory, and label. Output: exit status, parsed JSON or None, stdout, stderr. |
| invariants | The file uses compact UTF-8 JSON plus a final newline; the subprocess has a 20-second timeout. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | A subprocess timeout is converted to RuntimeError. JSON decode errors propagate from the explicit result parse; CLI rejection is asserted by rejected. |
| cost | Writes one input document, starts one CLI process and reads its captured streams. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0014

[Lines 77–83](../../../../../tests/integration/catalog.py#L77); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def error_payload(stderr: str, label: str) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract the nested error object from structured stderr JSON. |
| inputs / outputs | Callable: def error_payload(stderr: str, label: str) -&gt; dict\[str, Any\]:. Inputs: stderr text and diagnostic label. Output: the error object. |
| invariants | The envelope must be an object containing an object-valued error field. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0016

[Lines 86–99](../../../../../tests/integration/catalog.py#L86); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def rejected(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that one CLI document is rejected without partial stdout and optionally with a chosen error code. |
| inputs / outputs | Callable: def rejected(. Inputs: executable, command, document, temp path, label, optional expected code. Output: None. |
| invariants | A nonzero exit is required; stdout must be empty after stripping. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0018

[Lines 102–103](../../../../../tests/integration/catalog.py#L102); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def standalone(payload: dict[str, Any], version: int = 1) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Wrap a catalog payload in the standalone catalog schema envelope. |
| inputs / outputs | Callable: def standalone(payload: dict\[str, Any\], version: int = 1) -&gt; dict\[str, Any\]:. Inputs: catalog payload and root schema version. Output: a two-field document. |
| invariants | The root envelope version is independent of the payload's catalog version. |
| ownership | Returns a new envelope that refers to the caller's payload object; it does not copy or own nested catalog data. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0020

[Lines 106–153](../../../../../tests/integration/catalog.py#L106); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def rich_catalog() -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the valid multi-table fixture used for standalone metadata validation. |
| inputs / outputs | Callable: def rich_catalog() -&gt; dict\[str, Any\]:. Input: none. Output: a catalog with ordered unique keys, a composite foreign key, nullable/string/decimal columns, statistics and hints. |
| invariants | The fixture includes metadata defaults and nondefault examples but does not assert that estimates or hints are true. |
| ownership | Returns a newly allocated nested fixture tree whose lists/dictionaries belong to the returned object. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0022

[Lines 156–169](../../../../../tests/integration/catalog.py#L156); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def canonical_catalog_payload(payload: dict[str, Any]) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the expected canonical catalog payload after default materialization. |
| inputs / outputs | Callable: def canonical_catalog_payload(payload: dict\[str, Any\]) -&gt; dict\[str, Any\]:. Input: catalog payload. Output: a deep-copied payload with table, statistics, column and string-collation defaults. |
| invariants | Caller input is not mutated; supplied metadata and array order are preserved. |
| ownership | Returns a deep copy; nested catalog values in the result do not alias the caller's payload. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0024

[Lines 172–211](../../../../../tests/integration/catalog.py#L172); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_standalone_catalog(executable: str, temp: Path) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check CLI validation, canonicalization, defaults and a canonicalization fixed point for one rich catalog. |
| inputs / outputs | Callable: def check_standalone_catalog(executable: str, temp: Path) -&gt; None:. Inputs: executable and temporary directory. Output: None after validating command results. |
| invariants | The expected payload is derived from the local fixture; this checks the standalone catalog commands, not SQL binding. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Any nonzero CLI status, shape mismatch, missing default or changed canonical fixed point raises RuntimeError. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0026

[Lines 214–249](../../../../../tests/integration/catalog.py#L214); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_bad_catalogs(executable: str, temp: Path) -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assemble invalid standalone catalog fixtures and check each expected rejection. |
| inputs / outputs | Callable: def check_bad_catalogs(executable: str, temp: Path) -&gt; int:. Inputs: executable and temporary directory. Output: number of invalid catalog cases exercised. |
| invariants | Each mutation starts from a deep copy of the same rich fixture; expected codes are asserted only when specified. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Unexpected acceptance or a mismatched expected code raises RuntimeError; unexpected errors from invoke/JSON propagate. |
| cost | Builds and invokes one CLI case per mutation in the finite local case list. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0028

[Lines 252–253](../../../../../tests/integration/catalog.py#L252); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def catalog_payload(tables: list[dict[str, Any]], version: int = 1) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a versioned catalog payload from supplied table declarations. |
| inputs / outputs | Callable: def catalog_payload(tables: list\[dict\[str, Any\]\], version: int = 1) -&gt; dict\[str, Any\]:. Inputs: table list and payload version. Output: a catalog object. |
| invariants | No defaults or validation are added by this builder. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0030

[Lines 256–272](../../../../../tests/integration/catalog.py#L256); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def cq_document(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a set-semantics CQ document and stamp each update with the document version and one-based sequence. |
| inputs / outputs | Callable: def cq_document(. Inputs: catalog, variables, atoms, head, initial rows, updates, and root version. Output: a CQ document. |
| invariants | Input updates are copied before per-update schema_version and sequence are supplied. |
| ownership | Returns a new root and copied update dictionaries; catalog, variables, atoms, head and initial arrays are referenced from the caller. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0032

[Lines 275–285](../../../../../tests/integration/catalog.py#L275); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def normalize_decimal(text: str) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Canonicalize grammar-checked decimal text for SQLite fixture values. |
| inputs / outputs | Callable: def normalize_decimal(text: str) -&gt; str:. Input: signed decimal text using the local finite grammar. Output: no redundant leading/trailing zeros and normalized zero. |
| invariants | No exponent, whitespace, Unicode digits, rounding or fixed-column precision conversion is performed. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0034

[Lines 288–322](../../../../../tests/integration/catalog.py#L288); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def normalize_value(kind: str, value: Any, decimal_spec: dict[str, int] | None = None) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate one fixture scalar against its type and optional decimal specification. |
| inputs / outputs | Callable: def normalize_value(kind: str, value: Any, decimal_spec: dict\[str, int\] \| None = None) -&gt; Any:. Inputs: scalar kind, tagged or native value, optional precision/scale. Output: normalized native Python scalar. |
| invariants | Date text must round-trip to fixed-width ISO form; decimal fit must be exact at the declared fixed specification. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Malformed tags/types/date/decimal values fail via require or RuntimeError; decimal fit uses exact Decimal comparisons and does not round. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0036

[Lines 325–331](../../../../../tests/integration/catalog.py#L325); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def sql_value(kind: str, value: Any, decimal_spec: dict[str, int] | None = None) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert a validated fixture scalar into the Python value bound to SQLite. |
| inputs / outputs | Callable: def sql_value(kind: str, value: Any, decimal_spec: dict\[str, int\] \| None = None) -&gt; Any:. Inputs: scalar kind, value, optional decimal specification. Output: normalized SQL binding value. |
| invariants | Boolean values become integer 0/1; date, decimal and string values remain text. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0038

[Lines 334–341](../../../../../tests/integration/catalog.py#L334); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def output_value(kind: str, value: Any) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode one SQLite result scalar into the test's tagged JSON scalar form. |
| inputs / outputs | Callable: def output_value(kind: str, value: Any) -&gt; Any:. Inputs: scalar kind and SQL result. Output: tagged date/decimal, Boolean, or passthrough value. |
| invariants | This helper encodes known fixture result kinds; it does not validate an entire result row. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0040

[Lines 344–353](../../../../../tests/integration/catalog.py#L344); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def output_sort_key(kind: str, value: Any) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Choose a typed ordering key for sorting oracle result rows. |
| inputs / outputs | Callable: def output_sort_key(kind: str, value: Any) -&gt; Any:. Inputs: scalar kind and encoded value. Output: date, Decimal, UTF-8 bytes, Boolean, or native scalar key. |
| invariants | Text ordering is bytewise UTF-8 for this fixture; SQLite collation is separately declared binary. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0041

[Lines 354–358](../../../../../tests/integration/catalog.py#L354); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L354-L358:sha256:ee70464eb0d16d1c7ec5e2f5f7006fccf4fd371804555eb5b2c6a4235e7e5e1a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open the SQLiteTrace fixture class in catalog.py; method contracts describe instance effects. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/integration/catalog.py](../../../../../tests/integration/catalog.py), [docs/catalog.md](../../../../catalog.md), [docs/code_review.md](../../../../code_review.md) |

## B0042

[Lines 359–369](../../../../../tests/integration/catalog.py#L359); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def __init__(self, document: dict[str, Any]):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create the in-memory SQLite state used by the finite catalog trace oracle. |
| inputs / outputs | Callable: def __init__(self, document: dict\[str, Any\]):. Input: one CQ document. Output: initialized SQLiteTrace instance with table metadata, row sets and open connection. |
| invariants | Foreign-key enforcement is enabled before table creation; initial rows are loaded and checked before construction returns. |
| ownership | The instance retains the input document, a SQLite connection, table metadata and normalized row sets until the instance is released. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0044

[Lines 371–392](../../../../../tests/integration/catalog.py#L371); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _create_tables(self) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create SQLite tables and enforced unique/foreign-key constraints from one catalog. |
| inputs / outputs | Callable: def _create_tables(self) -&gt; None:. Input: initialized SQLiteTrace state. Output: committed table definitions. |
| invariants | Untrusted constraints are omitted; column SQL types and NOT NULL declarations are also derived from catalog metadata. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Creates one SQLite table per catalog table and adds the declared enforced constraints. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0046

[Lines 394–395](../../../../../tests/integration/catalog.py#L394); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _table_types(self, table_name: str) -> list[tuple[str, dict[str, int] | None]]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return the ordered scalar type and optional decimal spec for one table. |
| inputs / outputs | Callable: def _table_types(self, table_name: str) -&gt; list\[tuple\[str, dict\[str, int\] \| None\]\]:. Input: table name. Output: one pair per catalog column. |
| invariants | Column order matches the catalog declaration. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0048

[Lines 397–400](../../../../../tests/integration/catalog.py#L397); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def normalize_row(self, table_name: str, raw_row: list[Any]) -> tuple[Any, ...]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check row arity and normalize each cell using its declared fixture type. |
| inputs / outputs | Callable: def normalize_row(self, table_name: str, raw_row: list\[Any\]) -&gt; tuple\[Any, ...\]:. Inputs: table name and raw row. Output: immutable normalized tuple. |
| invariants | The number and order of values must match the table's column schema. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0050

[Lines 402–405](../../../../../tests/integration/catalog.py#L402); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def sql_row(self, table_name: str, raw_row: list[Any]) -> tuple[Any, ...]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check row arity and map fixture cells to values suitable for SQLite binding. |
| inputs / outputs | Callable: def sql_row(self, table_name: str, raw_row: list\[Any\]) -&gt; tuple\[Any, ...\]:. Inputs: table name and raw row. Output: tuple of SQLite parameters. |
| invariants | Boolean conversion and date/decimal normalization use the table's declared scalar types. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0052

[Lines 407–416](../../../../../tests/integration/catalog.py#L407); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _has_row(self, table_name: str, normalized: tuple[Any, ...]) -> bool:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check whether SQLite contains one fully specified row using IS comparisons. |
| inputs / outputs | Callable: def _has_row(self, table_name: str, normalized: tuple\[Any, ...\]) -&gt; bool:. Inputs: table name and normalized row. Output: Boolean membership result. |
| invariants | The empty-column case uses the oracle's row set; nonempty rows are matched across every declared column. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0054

[Lines 418–433](../../../../../tests/integration/catalog.py#L418); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _insert(self, table_name: str, raw_row: list[Any]) -> bool:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply one fixture row as set insertion while allowing SQLite constraints to reject conflicts. |
| inputs / outputs | Callable: def _insert(self, table_name: str, raw_row: list\[Any\]) -&gt; bool:. Inputs: table name and raw row. Output: True if newly inserted, False for a full-row duplicate. |
| invariants | The Python row set is updated only after SQLite insertion succeeds; INSERT OR IGNORE is not used. |
| ownership | Mutates the instance's SQLite connection and row set after successful insert; row argument is used during this call. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0056

[Lines 435–445](../../../../../tests/integration/catalog.py#L435); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _delete(self, table_name: str, raw_row: list[Any]) -> bool:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove one existing full physical row from SQLite and the oracle row set. |
| inputs / outputs | Callable: def _delete(self, table_name: str, raw_row: list\[Any\]) -&gt; bool:. Inputs: table name and raw row. Output: True if removed, False when absent. |
| invariants | A missing row is a set no-op; row identity includes every physical column. |
| ownership | Mutates the instance's SQLite connection and row set after successful deletion; row argument is used during this call. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0058

[Lines 447–454](../../../../../tests/integration/catalog.py#L447); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def _load_initial(self) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Load each document's initial rows through the same duplicate and constraint path as updates. |
| inputs / outputs | Callable: def _load_initial(self) -&gt; None:. Input: initialized document state. Output: committed initial SQLite rows. |
| invariants | A repeated full row is skipped; other rows use ordinary INSERT so unique and foreign-key errors remain visible. |
| ownership | Mutates the instance connection and row sets, then commits them; initial document rows remain referenced through the instance document. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0060

[Lines 456–502](../../../../../tests/integration/catalog.py#L456); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def relation(self) -> list[list[Any]]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute the query's finite set relation from the current SQLite tables. |
| inputs / outputs | Callable: def relation(self) -&gt; list\[list\[Any\]\]:. Input: current trace state. Output: typed, distinct, sorted JSON rows. |
| invariants | Repeated variables become equality predicates; constants are parameters; projection uses SELECT DISTINCT. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Builds and executes one SELECT for the current finite fixture relation, then converts and sorts returned rows. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0062

[Lines 504–536](../../../../../tests/integration/catalog.py#L504); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def trace(self) -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute initial output and every update's current relation and set delta. |
| inputs / outputs | Callable: def trace(self) -&gt; dict\[str, Any\]:. Input: initialized trace. Output: reference_recompute envelope with one epoch per update. |
| invariants | Each update is bracketed by a savepoint; SQLite integrity failure rolls back that update and propagates. |
| ownership | Uses and mutates the instance connection across savepoints; returns a separate result dictionary and retains no result history. |
| failure | sqlite3.IntegrityError rolls back to the savepoint and is re-raised; other SQLite/Python exceptions are not translated here. |
| cost | Recomputes relation before and after each update, performs one savepoint operation per update and builds one delta entry per update. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0064

[Lines 539–566](../../../../../tests/integration/catalog.py#L539); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_valid_document(executable: str, document: dict[str, Any], temp: Path, label: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare CROWN oracle output with SQLite and validate catalog canonicalization for one v3 document. |
| inputs / outputs | Callable: def check_valid_document(executable: str, document: dict\[str, Any\], temp: Path, label: str) -&gt; None:. Inputs: executable, document, temp directory and label. Output: None after all comparisons. |
| invariants | The check covers initial/epoch relation, canonical metadata defaults, canonicalization idempotence and round-trip output. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Runs four CLI commands per document: oracle, canonicalize, canonicalize again and oracle on canonical form. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0066

[Lines 569–582](../../../../../tests/integration/catalog.py#L569); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_query_binding(executable: str, document: dict[str, Any], temp: Path, label: str, expected_version: int) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check the tree-oracle certificate envelope and catalog binding version for one document. |
| inputs / outputs | Callable: def check_query_binding(executable: str, document: dict\[str, Any\], temp: Path, label: str, expected_version: int) -&gt; None:. Inputs: executable, document, temp directory, label and expected binding version. Output: None. |
| invariants | For v3 it also requires the composite foreign-key kind and target-column order to survive binding. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/io/binding.cpp](../../../../../src/io/binding.cpp) |

## B0068

[Lines 585–613](../../../../../tests/integration/catalog.py#L585); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def join_catalog() -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the parent/child fixture with composite target keys and an enforced foreign key. |
| inputs / outputs | Callable: def join_catalog() -&gt; dict\[str, Any\]:. Input: none. Output: catalog payload with metadata, a reordered FK target, statistics and key hint. |
| invariants | The referenced unique key and foreign-key columns have the same set, with order represented explicitly. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0070

[Lines 616–641](../../../../../tests/integration/catalog.py#L616); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def join_document() -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a join trace whose distinct child witnesses share projected parent values. |
| inputs / outputs | Callable: def join_document() -&gt; dict\[str, Any\]:. Input: none. Output: CQ v3 document with initial rows and an ordered insert/delete trace. |
| invariants | The query projects the shared parent key while a child witness column remains ignored. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0072

[Lines 644–666](../../../../../tests/integration/catalog.py#L644); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def self_reference_document() -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a self-referencing one-table CQ v3 trace with duplicate and missing-row operations. |
| inputs / outputs | Callable: def self_reference_document() -&gt; dict\[str, Any\]:. Input: none. Output: one-table document with enforced self-FK and four updates. |
| invariants | The foreign key targets the table's enforced unique id column; update sequences are assigned by cq_document. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0074

[Lines 669–700](../../../../../tests/integration/catalog.py#L669); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def untrusted_metadata_document() -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a valid trace containing intentionally inaccurate untrusted constraints, statistics and hints. |
| inputs / outputs | Callable: def untrusted_metadata_document() -&gt; dict\[str, Any\]:. Input: none. Output: CQ v3 document with two tables and an equality join. |
| invariants | Untrusted metadata is present as descriptive input only; the document's actual rows determine the result. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0076

[Lines 703–719](../../../../../tests/integration/catalog.py#L703); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def decimal_spec_document() -> dict[str, Any]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a CQ v3 fixture using a decimal column fixed at precision 5 and scale 2. |
| inputs / outputs | Callable: def decimal_spec_document() -&gt; dict\[str, Any\]:. Input: none. Output: document with exact decimals and alias spellings in initial/update values. |
| invariants | The fixture uses only values representable at the declared fixed specification. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0078

[Lines 722–755](../../../../../tests/integration/catalog.py#L722); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_format_compatibility(executable: str, temp: Path) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check v1/v2 compatibility and rejection when v2 would need to retain v3 catalog metadata. |
| inputs / outputs | Callable: def check_format_compatibility(executable: str, temp: Path) -&gt; None:. Inputs: executable and temp directory. Output: None. |
| invariants | Legacy documents keep their root versions; nondefault source metadata is not silently discarded. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Failed fixture requirements raise RuntimeError. Standard-library and conversion exceptions propagate unless this function wraps them at an explicit boundary; this helper does not emit CROWN diagnostics. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [docs/sql_binding.md § Binding and name scope](../../../../sql_binding.md), [src/io/binding.cpp](../../../../../src/io/binding.cpp) |

## B0080

[Lines 758–823](../../../../../tests/integration/catalog.py#L758); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_constraint_rejections(executable: str, temp: Path) -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check invalid initial and update states for enforced uniqueness, foreign keys, nullability and fixed-decimal bounds. |
| inputs / outputs | Callable: def check_constraint_rejections(executable: str, temp: Path) -&gt; int:. Inputs: executable and temp directory. Output: number of rejected trace cases. |
| invariants | Rejected trace cases assert constraint/scalar codes where specified; this is a finite fixture set. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Each case must reject; specified codes must match. Other exception paths propagate as test failures. |
| cost | Executes the fixed invalid-state list plus nullability and two fixed-decimal boundary cases. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp), [docs/catalog.md § Constraints](../../../../catalog.md), [src/io/physical.cpp](../../../../../src/io/physical.cpp) |

## B0082

[Lines 826–852](../../../../../tests/integration/catalog.py#L826); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main() -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run standalone catalog checks, valid SQLite-backed traces, binding/version cases and rejected trace fixtures. |
| inputs / outputs | Callable: def main() -&gt; int:. Input: exactly one executable path in argv. Output: zero after printing counts, or raises RuntimeError on misuse/failure. |
| invariants | A temporary directory contains per-command input files; the CLI is called serially for this runner. |
| ownership | Inputs are borrowed for this call; local Python values are released with the frame unless returned. The helper retains no CROWN runtime object or module-global mutable state. |
| failure | Argument misuse and failed fixture checks raise RuntimeError; the module guard prints it and exits 1. |
| cost | Work follows the fixture values, bytes, rows or subprocesses named above. This is test-helper work; it does not measure native query CPU time or establish a production cost bound. |
| Design | [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |

## B0083

[Lines 853–860](../../../../../tests/integration/catalog.py#L853); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Run standalone catalog checks, valid SQLite-backed traces, binding/version cases and rejected trace fixtures. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Pass the delegated return value to Python SystemExit; main controls that explicit exit status. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | The process boundary formats only RuntimeError to stderr, as shown in the source, then raises SystemExit(1). SystemExit/KeyboardInterrupt and unlisted exceptions are not converted; diagnostic I/O/allocation failure can still propagate. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. Failure formatting costs its actual diagnostic bytes. |
| Design | [tests/integration/catalog.py](../../../../../tests/integration/catalog.py), [docs/development.md](../../../../development.md), [docs/catalog.md § Validation and canonical writing](../../../../catalog.md), [src/io/catalog.cpp](../../../../../src/io/catalog.cpp) |
