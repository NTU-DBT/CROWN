# `tests/integration/normalization.py` — block usage map

[Source](../../../../../tests/integration/normalization.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `169534c4d6cd1634bbc7a20ec505862385f53cc7b948a2d80adeaf5b7509b7a5`. 615 lines partitioned into 40 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–34](../../../../../tests/integration/normalization.py#L1) | Imports dependencies. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 35–45](../../../../../tests/integration/normalization.py#L35) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0002) |
| [B0003 · 46–49](../../../../../tests/integration/normalization.py#L46) | Callable definition: def require(condition: bool, message: str) -&gt; None: | calls RuntimeError; guard def require(condition: bool, message: str) -&gt; None:; source comment (unverified): # Fixture checks must stay enabled under \`\`python -O\`\`. · [reviewed contract](#b0003) |
| [B0004 · 50–51](../../../../../tests/integration/normalization.py#L50) | Explanatory comments or spacing. |  |
| [B0005 · 52–58](../../../../../tests/integration/normalization.py#L52) | Callable definition: def canonical_decimal(value: Decimal) -&gt; str: | calls format, rstrip; returns "0"; rendered · [reviewed contract](#b0005) |
| [B0006 · 59–60](../../../../../tests/integration/normalization.py#L59) | Explanatory comments or spacing. |  |
| [B0007 · 61–72](../../../../../tests/integration/normalization.py#L61) | Callable definition: def canonical_json_scalar(value: Any) -&gt; Any: | calls isinstance, canonical_decimal, isoformat, set; returns {"decimal": canonical_decimal(value)}; {"date": value.isoformat()}; 1 loop sites · [reviewed contract](#b0007) |
| [B0008 · 73–74](../../../../../tests/integration/normalization.py#L73) | Explanatory comments or spacing. |  |
| [B0009 · 75–117](../../../../../tests/integration/normalization.py#L75) | Callable definition: def check_success_binding(binding: dict\[str, Any\], source: str, label: str) -&gt; None: | calls require, keys, sorted, compare; guard require(binding.keys() == BINDING_SUCCESS_FIELDS,; 3 loop sites · [reviewed contract](#b0009) |
| [B0010 · 118–119](../../../../../tests/integration/normalization.py#L118) | Explanatory comments or spacing. |  |
| [B0011 · 120–123](../../../../../tests/integration/normalization.py#L120) | Callable definition: def case_path(base: Path, relative: str, label: str) -&gt; Path: | calls resolve, require, is_relative_to; guard require(result.is_relative_to(base.resolve()), f"{label}: fixture path escapes fixture directory"); returns result · [reviewed contract](#b0011) |
| [B0012 · 124–125](../../../../../tests/integration/normalization.py#L124) | Explanatory comments or spacing. |  |
| [B0013 · 126–149](../../../../../tests/integration/normalization.py#L126) | Callable definition: def invoke_normalize(executable: str, base: Path, catalog: Path, case: dict\[str, Any\]) -&gt; tuple\[dict\[str, Any\], str\]: | calls case_path, read_text, except, RuntimeError; guard require(type_path is not None, f"{label}: parameter values require a parameter type document"); returns result, source · [reviewed contract](#b0013) |
| [B0014 · 150–151](../../../../../tests/integration/normalization.py#L150) | Explanatory comments or spacing. |  |
| [B0015 · 152–243](../../../../../tests/integration/normalization.py#L152) | Callable definition: def validate_routes(result: dict\[str, Any\], expected_occurrences: list\[dict\[str, str\]\], | calls require, len, enumerate, zip; guard require(len(actual_occurrences) == len(expected_occurrences),; 16 loop sites · [reviewed contract](#b0015) |
| [B0016 · 244–245](../../../../../tests/integration/normalization.py#L244) | Explanatory comments or spacing. |  |
| [B0017 · 246–260](../../../../../tests/integration/normalization.py#L246) | Callable definition: def validate_core_document(core: dict\[str, Any\], label: str) -&gt; None: | calls require, get, compare, isinstance; guard require(core.get("schema_version") == 3, f"{label}: normalized core must use CQ document schema ver…; 1 loop sites · [reviewed contract](#b0017) |
| [B0018 · 261–262](../../../../../tests/integration/normalization.py#L261) | Explanatory comments or spacing. |  |
| [B0019 · 263–300](../../../../../tests/integration/normalization.py#L263) | Callable definition: def run_adapters(result: dict\[str, Any\], data: dict\[str, Any\], parameter_values: list\[Any\], label: str) -&gt; dict\[str, list\[list\[An… | calls len, enumerate, table_data_rows, decode_scalar; guard require(all(len(row) == len(base_schema\["columns"\]) for row in source_rows),; returns adapted; 13 loop sites · [reviewed contract](#b0019) |
| [B0020 · 301–302](../../../../../tests/integration/normalization.py#L301) | Explanatory comments or spacing. |  |
| [B0021 · 303–321](../../../../../tests/integration/normalization.py#L303) | Callable definition: def invoke_core_oracle(executable: str, core: dict\[str, Any\], adapted: dict\[str, list\[list\[Any\]\]\], label: str) -&gt; list\[list\[Any\]\]: | calls deepcopy, json_scalar, get, TemporaryDirectory; guard require(process.returncode == 0,; returns set semantics"); rows; 2 loop sites · [reviewed contract](#b0021) |
| [B0022 · 322–323](../../../../../tests/integration/normalization.py#L322) | Explanatory comments or spacing. |  |
| [B0023 · 324–346](../../../../../tests/integration/normalization.py#L324) | Callable definition: def map_outputs(result: dict\[str, Any\], core_rows: list\[list\[Any\]\], label: str) -&gt; list\[list\[Any\]\]: | calls require, all, bool, get; guard require(result\["outputs"\] == \[\], f"{label}: EXISTS wrapper must not invent core output columns"); returns \[\[bool(core_rows)\]\]; mapped; 3 loop sites · [reviewed contract](#b0023) |
| [B0024 · 347–348](../../../../../tests/integration/normalization.py#L347) | Explanatory comments or spacing. |  |
| [B0025 · 349–356](../../../../../tests/integration/normalization.py#L349) | Callable definition: def sqlite_value(value: Any) -&gt; Any: | calls isinstance, canonical_decimal, isoformat, int; returns canonical_decimal(value); value.isoformat() · [reviewed contract](#b0025) |
| [B0026 · 357–358](../../../../../tests/integration/normalization.py#L357) | Explanatory comments or spacing. |  |
| [B0027 · 359–368](../../../../../tests/integration/normalization.py#L359) | Callable definition: def sqlite_typed_value(value: Any, kind: str) -&gt; Any: | calls bool, Decimal, str, fromisoformat; returns None; bool(value) · [reviewed contract](#b0027) |
| [B0028 · 369–370](../../../../../tests/integration/normalization.py#L369) | Explanatory comments or spacing. |  |
| [B0029 · 371–372](../../../../../tests/integration/normalization.py#L371) | Callable definition: def quote_identifier(name: str) -&gt; str: | calls replace; returns '"' + name.replace('"', '""') + '"' · [reviewed contract](#b0029) |
| [B0030 · 373–374](../../../../../tests/integration/normalization.py#L373) | Explanatory comments or spacing. |  |
| [B0031 · 375–414](../../../../../tests/integration/normalization.py#L375) | Callable definition: def run_sqlite(case: dict\[str, Any\], source: str, catalog: dict\[str, Any\], data: dict\[str, Any\], | calls connect, casefold, require, bool; guard require(bool(columns), f"{label}: SQLite crosscheck does not create zero-column tables"); returns rows, names; 11 loop sites · [reviewed contract](#b0031) |
| [B0032 · 415–416](../../../../../tests/integration/normalization.py#L415) | Explanatory comments or spacing. |  |
| [B0033 · 417–505](../../../../../tests/integration/normalization.py#L417) | Callable definition: def validate_success(executable: str, base: Path, catalog_path: Path, catalog: dict\[str, Any\], | calls invoke_normalize, require, keys, sorted; guard require(result.keys() == NORMALIZATION_SUCCESS_FIELDS,; returns mapped_rows; 15 loop sites · [reviewed contract](#b0033) |
| [B0034 · 506–507](../../../../../tests/integration/normalization.py#L506) | Explanatory comments or spacing. |  |
| [B0035 · 508–537](../../../../../tests/integration/normalization.py#L508) | Callable definition: def validate_failure(executable: str, base: Path, catalog_path: Path, case: dict\[str, Any\]) -&gt; None: | calls invoke_normalize, require, keys, sorted; guard require(result.keys() == NORMALIZATION_FAILURE_FIELDS,; 2 loop sites · [reviewed contract](#b0035) |
| [B0036 · 538–539](../../../../../tests/integration/normalization.py#L538) | Explanatory comments or spacing. |  |
| [B0037 · 540–568](../../../../../tests/integration/normalization.py#L540) | Callable definition: def validate_cli_errors(executable: str, base: Path, catalog_path: Path, manifest: dict\[str, Any\]) -&gt; int: | calls get, append, str, startswith; guard require(not process.stdout, f"{label}: CLI error wrote stdout"); returns count; 2 loop sites · [reviewed contract](#b0037) |
| [B0038 · 569–570](../../../../../tests/integration/normalization.py#L569) | Explanatory comments or spacing. |  |
| [B0039 · 571–607](../../../../../tests/integration/normalization.py#L571) | Callable definition: def main() -&gt; int: | calls len, RuntimeError, Path, resolve; guard require(isinstance(manifest, dict) and type(manifest.get("schema_version")) is int; returns 0; 2 loop sites · [reviewed contract](#b0039) |
| [B0040 · 608–615](../../../../../tests/integration/normalization.py#L608) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0040) |

## B0001

[Lines 1–34](../../../../../tests/integration/normalization.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L34:sha256:276d81c73e22e4947716cac0e4db1ff2ad9aa6319268df09c3b0bb5ac414295f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for normalization.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/integration/normalization.py](../../../../../tests/integration/normalization.py), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 35–45](../../../../../tests/integration/normalization.py#L35); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L45:sha256:8d9d434f2610a893f4d3e8d81357a30fcff10b2edee31d05601a48320a3da0d8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for normalization.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/integration/normalization.py](../../../../../tests/integration/normalization.py), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 46–49](../../../../../tests/integration/normalization.py#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def require(condition: bool, message: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce normalization fixture conditions independently of Python assert optimization. |
| inputs / outputs | Falsey input raises RuntimeError(message); otherwise returns None. |
| invariants | Checks remain active under python -O, including schema and oracle mismatches. |
| ownership | Borrows arguments; no fixture or result graph is changed. |
| failure | Raises RuntimeError only for a failed condition. |
| cost | One truth test; failure exception/message allocation is additional. |
| Design | [tests/integration/normalization.py](../../../../../tests/integration/normalization.py), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/catalog.md](../../../../catalog.md) |

## B0005

[Lines 52–58](../../../../../tests/integration/normalization.py#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def canonical_decimal(value: Decimal) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce fixed-point, trailing-zero-free Decimal spelling for scalar comparison. |
| inputs / outputs | Returns "0" for any zero; otherwise formats without exponent and strips fractional trailing zeros and a trailing point. |
| invariants | Integer trailing zeros are retained; negative zero normalizes to 0. Caller supplies a finite Decimal for the intended fixture domain. |
| ownership | Returns new text and leaves the immutable Decimal unchanged. |
| failure | Decimal formatting/type errors propagate; no SQL-domain precision check occurs here. |
| cost | Work/storage scale with rendered digits and exponent-expanded output length, not constant numeric width. |
| Design | [tests/integration/normalization.py](../../../../../tests/integration/normalization.py), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/catalog.md](../../../../catalog.md) |

## B0007

[Lines 61–72](../../../../../tests/integration/normalization.py#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def canonical_json_scalar(value: Any) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert supported decoded SQL values into comparable JSON scalar/row representations. |
| inputs / outputs | Decimal/date become one-key canonical dictionaries; lists/tuples recurse into new lists; exact date/decimal wrapper dictionaries are normalized; other objects pass through. |
| invariants | Only dictionaries with exactly one recognized wrapper key are interpreted; tuple row shape becomes list shape. |
| ownership | Creates new wrapper/list containers, but shares all unrecognized leaf objects and dictionaries; this is not a general deep copy. |
| failure | Invalid Decimal/date spellings and recursive input failures propagate. |
| cost | Visits nested list/tuple elements and renders decimal/date text; cost follows element count, nesting and digit lengths. |
| Design | [tests/integration/normalization.py](../../../../../tests/integration/normalization.py), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/catalog.md](../../../../catalog.md) |

## B0009

[Lines 75–117](../../../../../tests/integration/normalization.py#L75); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def check_success_binding(binding: dict[str, Any], source: str, label: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the successful bound-SQL envelope and expression graph used by normalization checks. |
| inputs / outputs | Reads binding and original SQL, verifies exact binding fields/source, collection types, contiguous expression IDs, SQL types and legal expression references. |
| invariants | Operation arguments refer only to earlier expressions; column occurrence/column IDs and one-based parameter numbers are checked against declared ranges. |
| ownership | Reads caller dictionaries/lists and builds only small projected comparison dictionaries; does not rewrite binding. |
| failure | Malformed structure or comparison raises RuntimeError; absent required nested fields may raise KeyError rather than a native binding diagnostic. |
| cost | Traverses expressions and argument edges plus serialized comparison data; cost depends on graph and metadata widths. |
| Design | [tests/integration/normalization.py](../../../../../tests/integration/normalization.py), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/catalog.md](../../../../catalog.md) |

## B0011

[Lines 120–123](../../../../../tests/integration/normalization.py#L120); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def case_path(base: Path, relative: str, label: str) -> Path:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Confine a fixture-relative path to its resolved fixture directory. |
| inputs / outputs | Resolves base/relative and returns a Path only if it remains under resolved base. |
| invariants | Resolution follows filesystem path/symlink semantics; an escape fails the explicit is_relative_to check. |
| ownership | Returns a new Path, borrows base/name, and opens no file. |
| failure | Escapes raise RuntimeError; path resolution OSError or invalid path errors propagate. |
| cost | Path normalization and filesystem resolution work depend on path components and symlinks. |
| Design | [tests/integration/normalization.py](../../../../../tests/integration/normalization.py), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/catalog.md](../../../../catalog.md) |

## B0013

[Lines 126–149](../../../../../tests/integration/normalization.py#L126); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def invoke_normalize(executable: str, base: Path, catalog: Path, case: dict[str, Any]) -> tuple[dict[str, Any], str]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read one SQL fixture and execute normalize-sql with its optional typed parameters. |
| inputs / outputs | Resolves constrained SQL/parameter paths, reads UTF-8 SQL, invokes the native child and returns parsed result plus original source text. |
| invariants | Values require a type document; stderr must be empty; cases declaring a diagnostic code expect exit 1, all others exit 0. |
| ownership | Owns read source/result/argument list and child captured bytes; case/catalog/base remain borrowed. No fixture file is modified. |
| failure | SQL read/Unicode errors become labeled RuntimeError; imported invoke converts a 20-second timeout to RuntimeError; channel/exit/JSON checks also fail explicitly. |
| cost | Includes filesystem reads/resolution, a captured subprocess and full JSON/UTF-8 decoding; it is not a small in-memory conversion. |
| Design | [tests/integration/normalization.py](../../../../../tests/integration/normalization.py), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/catalog.md](../../../../catalog.md), [tests/integration/binding.py](../../../../../tests/integration/binding.py) |

## B0015

[Lines 152–243](../../../../../tests/integration/normalization.py#L152); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def validate_routes(result: dict[str, Any], expected_occurrences: list[dict[str, str]],
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check occurrence-to-base routes and complete adapter/core correspondence. |
| inputs / outputs | Compares expected table/alias identities, reconstructs routes, validates each adapter field set, column classes, filters, expression references and ordered projection. |
| invariants | Every catalog table has a route entry; each occurrence has one adapter/core table/atom. Predicates/program/non-null checks are sorted unique and projection order matches the atom. |
| ownership | Builds expected route/name lists and set/sort scratch; caller result/expected graphs are read only. |
| failure | Invalid identities, ranges, shape or fixture-specific equality/null-class expectations raise RuntimeError; missing mandatory fields may raise KeyError. |
| cost | Traverses occurrences, physical columns, projections and expression references; sorted/set checks and full comparisons add metadata-size costs. |
| Design | [tests/integration/normalization.py](../../../../../tests/integration/normalization.py), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/catalog.md](../../../../catalog.md) |

## B0017

[Lines 246–260](../../../../../tests/integration/normalization.py#L246); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def validate_core_document(core: dict[str, Any], label: str) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an empty schema-v3 classical set CQ as normalized core input. |
| inputs / outputs | Checks core envelope, catalog/query dictionaries, empty updates and initial relations, and variable/atom/head list shapes. |
| invariants | Every initial row list is empty; validation here is shape/empty-state checking rather than complete native plan admission. |
| ownership | Borrows the core graph and allocates only comparison/diagnostic scratch. |
| failure | Failed shape or nonempty-state conditions raise RuntimeError. |
| cost | Linear in initial-relation entries plus small envelope checks; query arrays are type-checked, not semantically enumerated here. |
| Design | [tests/integration/normalization.py](../../../../../tests/integration/normalization.py), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/catalog.md](../../../../catalog.md) |

## B0019

[Lines 263–300](../../../../../tests/integration/normalization.py#L263); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def run_adapters(result: dict[str, Any], data: dict[str, Any], parameter_values: list[Any], label: str) -> dict[str, list[list[Any]]]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently evaluate each occurrence adapter over full physical fixture rows. |
| inputs / outputs | Decodes source values, enforces fixed/non-null/repeated-column filters, evaluates predicates/projections and returns deduplicated occurrence_N relations. |
| invariants | Only SQL-true predicates survive; NULL may not enter the classical core. Memoization is per physical row and deduplication is per occurrence using canonical row text. |
| ownership | Creates decoded/projected lists, contexts and memo dictionaries; borrowed result/data/parameters are not mutated. Unsupported scalar leaves may be shared. |
| failure | Wrong physical arity or projected NULL raises RuntimeError; imported expression/scalar evaluation failures propagate. |
| cost | Scans each occurrence’s physical rows, evaluates reachable expression work per row and serializes projected keys; aliases may repeat the same base scan. |
| Design | [tests/integration/normalization.py](../../../../../tests/integration/normalization.py), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/catalog.md](../../../../catalog.md), [tests/integration/binding.py](../../../../../tests/integration/binding.py) |

## B0021

[Lines 303–321](../../../../../tests/integration/normalization.py#L303); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def invoke_core_oracle(executable: str, core: dict[str, Any], adapted: dict[str, list[list[Any]]], label: str) -> list[list[Any]]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Populate a private copy of the normalized core and ask the native set oracle for its initial rows. |
| inputs / outputs | Deep-copies core, fills all initial relations from adapted rows, writes a temporary UTF-8 JSON document and returns the child result’s initial list. |
| invariants | Updates are cleared; child must exit 0 with no stderr, set semantics and list-valued initial output. |
| ownership | Caller core is protected by deepcopy; TemporaryDirectory removes its file even on failure; returned parsed rows outlive the temporary path. |
| failure | Child timeout/JSON/channel/schema/exit failures raise labeled RuntimeError; file errors propagate. |
| cost | Copies/serializes the complete core and adapted rows, performs file I/O and a subprocess oracle evaluation, then parses all output. |
| Design | [tests/integration/normalization.py](../../../../../tests/integration/normalization.py), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/catalog.md](../../../../catalog.md), [tests/integration/binding.py](../../../../../tests/integration/binding.py) |

## B0023

[Lines 324–346](../../../../../tests/integration/normalization.py#L324); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def map_outputs(result: dict[str, Any], core_rows: list[list[Any]], label: str) -> list[list[Any]]:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map classical core results back to the SQL-visible output positions and constants. |
| inputs / outputs | EXISTS requires nullary core rows and returns one Boolean row; normal output selects bounded columns or decoded constants for each row. |
| invariants | EXISTS has no invented output mappings; core indices must be exact integers in range; unknown mapping kinds reject. |
| ownership | Builds new outer/visible lists but core selected cell objects are shared; decoded constants may allocate wrapper values. |
| failure | Mapping or nullary-EXISTS shape violations raise RuntimeError; missing fields and scalar decode errors propagate. |
| cost | O(core rows × output fields) selections plus constant decoding; materializes every visible row. |
| Design | [tests/integration/normalization.py](../../../../../tests/integration/normalization.py), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/catalog.md](../../../../catalog.md) |

## B0025

[Lines 349–356](../../../../../tests/integration/normalization.py#L349); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def sqlite_value(value: Any) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Adapt decoded SQL values to SQLite parameter/insertion values. |
| inputs / outputs | Decimal becomes canonical decimal text, date ISO text and bool integer; other values including None are returned unchanged. |
| invariants | Boolean conversion follows Decimal/date tests and prevents binding Python bool as a separate comparison type. |
| ownership | Returns new strings/integers where converted and shares unchanged objects. |
| failure | Formatting/type errors propagate; this is not a SQL range validator. |
| cost | Constant type dispatch plus output digit/date rendering and any big-number text cost. |
| Design | [tests/integration/normalization.py](../../../../../tests/integration/normalization.py), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/catalog.md](../../../../catalog.md) |

## B0027

[Lines 359–368](../../../../../tests/integration/normalization.py#L359); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def sqlite_typed_value(value: Any, kind: str) -> Any:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore SQLite result cells to the declared comparison kind. |
| inputs / outputs | None stays None; bool uses truth conversion, decimal uses Decimal(str(value)), date parses ISO text; other kinds pass through. |
| invariants | The requested kind comes from normalized output types, with a synthetic bool kind for EXISTS. |
| ownership | Creates converted scalar objects, otherwise returns the original value reference. |
| failure | Invalid date/decimal text or conversion errors propagate. |
| cost | Type dispatch plus text parsing/rendering cost; arbitrary decimal digit length matters. |
| Design | [tests/integration/normalization.py](../../../../../tests/integration/normalization.py), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/catalog.md](../../../../catalog.md) |

## B0029

[Lines 371–372](../../../../../tests/integration/normalization.py#L371); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def quote_identifier(name: str) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Quote a SQLite identifier without interpreting it as SQL syntax. |
| inputs / outputs | Returns a double-quoted name with each embedded double quote doubled. |
| invariants | The result is an identifier fragment, not a literal-value placeholder or whole-statement sanitizer. |
| ownership | Creates a new string; caller name is immutable and unchanged. |
| failure | Non-string attribute/type errors propagate. |
| cost | Scans and copies the complete identifier, potentially doubling quote characters. |
| Design | [tests/integration/normalization.py](../../../../../tests/integration/normalization.py), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/catalog.md](../../../../catalog.md) |

## B0031

[Lines 375–414](../../../../../tests/integration/normalization.py#L375); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def run_sqlite(case: dict[str, Any], source: str, catalog: dict[str, Any], data: dict[str, Any],
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Crosscheck selected fixture SQL in an isolated in-memory SQLite database. |
| inputs / outputs | Creates only used catalog tables, inserts decoded/coerced rows, binds named parameters, executes source and returns typed rows plus cursor column names. |
| invariants | Used tables must have columns; output conversion follows normalized output kinds or EXISTS bool. Decimal columns are stored as TEXT under this fixture comparison. |
| ownership | Owns the SQLite connection and closes it in finally on every path; materializes insertion and fetchall results without mutating caller graphs. |
| failure | Query execution sqlite3.Error becomes labeled RuntimeError; setup SQL, type-map, decode and conversion errors propagate while finally still closes the connection. |
| cost | Includes schema creation, all row insertion, SQL execution and complete result materialization; join/query cost is SQLite-dependent. |
| Design | [tests/integration/normalization.py](../../../../../tests/integration/normalization.py), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/catalog.md](../../../../catalog.md) |

## B0033

[Lines 417–505](../../../../../tests/integration/normalization.py#L417); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def validate_success(executable: str, base: Path, catalog_path: Path, catalog: dict[str, Any],
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a successful normalizer result against manual adapter/core and optional SQLite results. |
| inputs / outputs | Invokes normalization, validates exact binding/output/limits/core/routes, runs adapters and core oracle, maps SQL outputs and returns mapped rows. |
| invariants | Mapped rows must equal manual expectations; optional EXISTS/output-name and SQLite multiset checks apply only when requested by the case. Work metadata is nonnegative with null or positive configured limit. |
| ownership | Borrows fixture graphs; helper-created lists/results and temporary oracle database/files are owned locally and cleaned by their helpers. |
| failure | Any envelope/type/routing/oracle discrepancy raises RuntimeError; imported I/O, scalar and database errors propagate. |
| cost | Combines full metadata traversal, occurrence-row adaptation, a second native oracle child, output comparisons and optional complete SQLite execution. |
| Design | [tests/integration/normalization.py](../../../../../tests/integration/normalization.py), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/catalog.md](../../../../catalog.md), [tests/integration/binding.py](../../../../../tests/integration/binding.py) |

## B0035

[Lines 508–537](../../../../../tests/integration/normalization.py#L508); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def validate_failure(executable: str, base: Path, catalog_path: Path, case: dict[str, Any]) -> None:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check one expected normalizer diagnostic and its optional source byte location. |
| inputs / outputs | Runs the failing case, requires exact failure fields/phase/code and diagnostic schema, then verifies null/nonnegative coordinates and optional UTF-8 marker offset. |
| invariants | Line/column are one-based when present; marker position is converted from Python characters to UTF-8 byte count. |
| ownership | Borrows case inputs; owns native parsed result/source and coordinate comparison scratch. |
| failure | Unexpected channel/exit/diagnostic or missing marker raises RuntimeError; file and imported invocation errors propagate. |
| cost | One normalizer subprocess plus source/JSON decoding, fixed diagnostic traversal and optional source search/UTF-8 prefix encoding. |
| Design | [tests/integration/normalization.py](../../../../../tests/integration/normalization.py), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/catalog.md](../../../../catalog.md), [tests/integration/binding.py](../../../../../tests/integration/binding.py) |

## B0037

[Lines 540–568](../../../../../tests/integration/normalization.py#L540); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def validate_cli_errors(executable: str, base: Path, catalog_path: Path, manifest: dict[str, Any]) -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise manifest-defined malformed normalize-sql invocations. |
| inputs / outputs | Expands catalog/missing-file/path placeholders, runs each child, requires exit 2 with empty stdout and structured stderr error code, and returns number checked. |
| invariants | Case-relative paths remain confined; native stderr must parse as an error object rather than normal normalization output. |
| ownership | Owns per-case arguments/captured diagnostics; caller manifest and existing fixture files remain unchanged. |
| failure | Invalid stderr JSON becomes labeled RuntimeError; wrong status/channel/code and timeout fail via imported helpers. |
| cost | One child per listed error case, path resolution and complete stderr decoding/JSON parsing. |
| Design | [tests/integration/normalization.py](../../../../../tests/integration/normalization.py), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/catalog.md](../../../../catalog.md), [tests/integration/binding.py](../../../../../tests/integration/binding.py) |

## B0039

[Lines 571–607](../../../../../tests/integration/normalization.py#L571); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main() -> int:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the normalization success, diagnostic and CLI-error fixture corpus. |
| inputs / outputs | Requires executable and fixture directory; validates manifest/catalog/data, unique nonempty case names and expected payloads, then prints counts and returns 0. |
| invariants | Success/failure collections are nonempty; names are unique across both; fixture paths are confined before execution. |
| ownership | Owns loaded JSON graphs and per-case helper results; nested oracle temp files and SQLite connections have helper-managed lifetimes. |
| failure | Wrong usage/schema/case/checks raise RuntimeError and the entrypoint prints a fixture diagnostic/exits 1; other uncaught I/O/type errors retain their Python behavior. |
| cost | Traverses the complete manifest and delegates subprocess, adapter, oracle and optional SQL work for every case; this is corpus verification, not update timing. |
| Design | [tests/integration/normalization.py](../../../../../tests/integration/normalization.py), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/catalog.md](../../../../catalog.md) |

## B0040

[Lines 608–615](../../../../../tests/integration/normalization.py#L608); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only entry for this module: Run the normalization success, diagnostic and CLI-error fixture corpus. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Pass the delegated return value to Python SystemExit; main controls that explicit exit status. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | The process boundary formats only RuntimeError to stderr, as shown in the source, then raises SystemExit(1). SystemExit/KeyboardInterrupt and unlisted exceptions are not converted; diagnostic I/O/allocation failure can still propagate. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. Failure formatting costs its actual diagnostic bytes. |
| Design | [tests/integration/normalization.py](../../../../../tests/integration/normalization.py), [docs/development.md](../../../../development.md), [docs/sql_normalization.md](../../../../sql_normalization.md), [docs/sql_binding.md](../../../../sql_binding.md), [docs/catalog.md](../../../../catalog.md) |
