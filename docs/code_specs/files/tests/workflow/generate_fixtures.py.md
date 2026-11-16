# `tests/workflow/generate_fixtures.py` — block usage map

[Source](../../../../../tests/workflow/generate_fixtures.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `dfe86a0056d0ea680fb34a909e0261ea6f92db785750f0ef05aa6e8b9d27c7a1`. 327 lines partitioned into 28 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../tests/workflow/generate_fixtures.py#L1) | Imports dependencies; declares aliases; declares values/defaults or compile-time conditions. | source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 12–17](../../../../../tests/workflow/generate_fixtures.py#L12) | Callable definition: def digest(path: Path) -&gt; str: | calls sha256, open, iter, read; returns h.hexdigest(); 1 loop sites · [reviewed contract](#b0002) |
| [B0003 · 18–19](../../../../../tests/workflow/generate_fixtures.py#L18) | Explanatory comments or spacing. |  |
| [B0004 · 20–26](../../../../../tests/workflow/generate_fixtures.py#L20) | Callable definition: def canonical_decimal(value: Decimal) -&gt; str: | calls format, rstrip, in; returns "0"; text · [reviewed contract](#b0004) |
| [B0005 · 27–28](../../../../../tests/workflow/generate_fixtures.py#L27) | Explanatory comments or spacing. |  |
| [B0006 · 29–46](../../../../../tests/workflow/generate_fixtures.py#L29) | Callable definition: def typed(kind: str, raw): | calls isinstance, set, Decimal, AssertionError; returns (kind, raw); (kind, raw) · [reviewed contract](#b0006) |
| [B0007 · 47–48](../../../../../tests/workflow/generate_fixtures.py#L47) | Explanatory comments or spacing. |  |
| [B0008 · 49–55](../../../../../tests/workflow/generate_fixtures.py#L49) | Callable definition: def encode_scalar(cell): | calls canonical_decimal; returns {"date": raw}; {"decimal": canonical_decimal(raw)} · [reviewed contract](#b0008) |
| [B0009 · 56–57](../../../../../tests/workflow/generate_fixtures.py#L56) | Explanatory comments or spacing. |  |
| [B0010 · 58–59](../../../../../tests/workflow/generate_fixtures.py#L58) | Callable definition: def encode_rows(rows): | calls encode_scalar, sorted; returns \[\[encode_scalar(value) for value in row\] for row in sorted(rows)\]; 2 loop sites · [reviewed contract](#b0010) |
| [B0011 · 60–61](../../../../../tests/workflow/generate_fixtures.py#L60) | Explanatory comments or spacing. |  |
| [B0012 · 62–69](../../../../../tests/workflow/generate_fixtures.py#L62) | Callable definition: def oracle_path(db): | calls ; returns {; 2 loop sites · [reviewed contract](#b0012) |
| [B0013 · 70–71](../../../../../tests/workflow/generate_fixtures.py#L70) | Explanatory comments or spacing. |  |
| [B0014 · 72–73](../../../../../tests/workflow/generate_fixtures.py#L72) | Callable definition: def oracle_projection(db): | calls ; returns {(projected_key,) for (projected_key, witness) in db\["records"\]}; 1 loop sites · [reviewed contract](#b0014) |
| [B0015 · 74–75](../../../../../tests/workflow/generate_fixtures.py#L74) | Explanatory comments or spacing. |  |
| [B0016 · 76–78](../../../../../tests/workflow/generate_fixtures.py#L76) | Callable definition: def oracle_exists(db): | calls any; returns {(('bool', found),)}; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 79–80](../../../../../tests/workflow/generate_fixtures.py#L79) | Explanatory comments or spacing. |  |
| [B0018 · 81–86](../../../../../tests/workflow/generate_fixtures.py#L81) | Callable definition: def oracle_product(db): | calls ; returns {; 2 loop sites · [reviewed contract](#b0018) |
| [B0019 · 87–88](../../../../../tests/workflow/generate_fixtures.py#L87) | Explanatory comments or spacing. |  |
| [B0020 · 89–90](../../../../../tests/workflow/generate_fixtures.py#L89) | Callable definition: def oracle_all_scalars(db): | calls ; returns {row for row in db\["scalar_values"\]}; 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 91–126](../../../../../tests/workflow/generate_fixtures.py#L91) | declares callable signatures; declares values/defaults or compile-time conditions. | growth insert, new · [reviewed contract](#b0021) |
| [B0022 · 127–162](../../../../../tests/workflow/generate_fixtures.py#L127) | declares callable signatures; declares values/defaults or compile-time conditions. | growth insert · [reviewed contract](#b0022) |
| [B0023 · 163–183](../../../../../tests/workflow/generate_fixtures.py#L163) | Module statements. | growth insert · [reviewed contract](#b0023) |
| [B0024 · 184–201](../../../../../tests/workflow/generate_fixtures.py#L184) | Callable definition: def catalog_for(case): | calls items, append; returns {"schema_version": 1, "catalog": {"version": 1, "tables": tables}}; 2 loop sites · [reviewed contract](#b0024) |
| [B0025 · 202–203](../../../../../tests/workflow/generate_fixtures.py#L202) | Explanatory comments or spacing. |  |
| [B0026 · 204–287](../../../../../tests/workflow/generate_fixtures.py#L204) | Callable definition: def build_case(case): | calls mkdir, write_text, catalog_for, dumps; returns {; growth insert; 12 loop sites · [reviewed contract](#b0026) |
| [B0027 · 288–303](../../../../../tests/workflow/generate_fixtures.py#L288) | declares values/defaults or compile-time conditions. | 2 loop sites · [reviewed contract](#b0027) |
| [B0028 · 304–327](../../../../../tests/workflow/generate_fixtures.py#L304) | declares values/defaults or compile-time conditions. | 5 loop sites · [reviewed contract](#b0028) |

## B0001

[Lines 1–11](../../../../../tests/workflow/generate_fixtures.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
ROOT = OUT.parents[1]
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set the O08 generator’s output and source-root variables from its script directory. |
| inputs / outputs | Sets OUT to the script directory and ROOT to OUT.parents\[1\]. In the supported repo/tests/workflow layout this resolves the containing repository used for documentation hashes. |
| invariants | Paths are derived from __file__, independently of cwd. Importing the module executes later case/README/manifest writes under OUT; the supported repository layout supplies the named docs under ROOT. |
| ownership | Module retains two Path values; no files are opened in this block. |
| failure | Import/path-resolution errors propagate. Later file/hash/write failures retain their own partial-output behavior; this setup makes no explicit fixture write. |
| cost | Module imports and source-relative path calculations; no engine/update-path operation. |
| Design | [tests/workflow/generate_fixtures.py](../../../../../tests/workflow/generate_fixtures.py), [tests/workflow/README.md](../../../../../tests/workflow/README.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json), tests/workflow/generate_fixtures.py:1-11 |

## B0002

[Lines 12–17](../../../../../tests/workflow/generate_fixtures.py#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def digest(path: Path) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute SHA-256 of a fixture/specification file using bounded read chunks. |
| inputs / outputs | Accepts Path; opens binary and returns lowercase hex str after consuming EOF in 1 MiB blocks. |
| invariants | Hashes exact current file bytes without JSON normalization or relying on a prior manifest. It does not detect concurrent file changes. |
| ownership | Context manager closes file on success/error; each block is temporary and the hasher retains digest state rather than all input bytes. |
| failure | Open/read OSError and hashing failures propagate; no missing-file fallback. |
| cost | O(file bytes) I/O/hash time with at most one 1 MiB read block plus digest state, excluding filesystem buffering. |
| Design | [tests/workflow/generate_fixtures.py](../../../../../tests/workflow/generate_fixtures.py), [docs/semantics.md](../../../../semantics.md), [docs/ingestion.md](../../../../ingestion.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json) |

## B0004

[Lines 20–26](../../../../../tests/workflow/generate_fixtures.py#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def canonical_decimal(value: Decimal) -> str:
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render fixture Decimal values in fixed notation without removable fractional zeros. |
| inputs / outputs | Takes Decimal-compatible format(value,"f") input; returns str, stripping trailing fractional zeros/dot and mapping empty/-0/+0 text to 0. |
| invariants | Only strips when a decimal point exists, preserving integer trailing zeros. It does not validate precision, finite value or canonical native-decimal domain. |
| ownership | Creates formatted/trimmed strings; does not mutate Decimal or decimal context. |
| failure | Formatting/type errors propagate; nonfinite Decimal may produce text rather than rejection. |
| cost | Fixed-format rendering/allocation scales with coefficient digits and exponent expansion, which can be much larger than the compact Decimal representation. |
| Design | [tests/workflow/generate_fixtures.py](../../../../../tests/workflow/generate_fixtures.py), [docs/semantics.md](../../../../semantics.md), [docs/ingestion.md](../../../../ingestion.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json) |

## B0006

[Lines 29–46](../../../../../tests/workflow/generate_fixtures.py#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def typed(kind: str, raw):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Convert raw fixture scalar spelling to a hashable tagged value used by independent set oracles. |
| inputs / outputs | Takes kind and raw; returns (kind,raw) for int64/string/bool, (date,date-field), or (decimal,Decimal(decimal-field)). |
| invariants | Assertions check int64/nonbool/range, string/bool types and exact single-key date/decimal dictionaries; dates are not calendar-validated and Decimal constructor supplies its own grammar. python -O removes these assertions; unknown kind still raises AssertionError. |
| ownership | Creates tuple; primitive/date raw value is shared, while decimal creates a Decimal. Caller dictionaries are not mutated or retained as tuple containers. |
| failure | AssertionError for enabled checks/unknown kind; missing keys/type failures and Decimal conversion errors propagate. |
| cost | Constant-size tagging/range checks except Decimal parsing depends on digit count; no native scalar codec or SQL binder is invoked. |
| Design | [tests/workflow/generate_fixtures.py](../../../../../tests/workflow/generate_fixtures.py), [docs/semantics.md](../../../../semantics.md), [docs/ingestion.md](../../../../ingestion.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json) |

## B0008

[Lines 49–55](../../../../../tests/workflow/generate_fixtures.py#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def encode_scalar(cell):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map a typed independent-oracle cell back to public fixture JSON scalar representation. |
| inputs / outputs | Unpacks (kind,raw); date returns new {date:raw}, decimal new {decimal:canonical_decimal(raw)}, other kinds return raw. |
| invariants | Preserves date spelling and untagged scalar values; only decimal spelling is canonicalized. It does not validate kind or scalar type. |
| ownership | Tagged results allocate a dict and share date raw; decimal contains new text. Untagged result is the exact raw reference. |
| failure | Tuple-unpack or decimal-format errors propagate; unknown kind is passed through as raw. |
| cost | Constant-size branching/dict allocation except full decimal formatting and text storage. |
| Design | [tests/workflow/generate_fixtures.py](../../../../../tests/workflow/generate_fixtures.py), [docs/semantics.md](../../../../semantics.md), [docs/ingestion.md](../../../../ingestion.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json) |

## B0010

[Lines 58–59](../../../../../tests/workflow/generate_fixtures.py#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def encode_rows(rows):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Produce deterministically ordered JSON-ready rows from an iterable of typed tuples. |
| inputs / outputs | Sorts rows with Python tuple ordering and returns list of lists encoded cell by cell. |
| invariants | Relies on comparable homogeneous typed values at each slot; it does not deduplicate rows beyond the caller’s set semantics. Typed kind tags take part in ordering before raw values. |
| ownership | Creates the sorted materialization and all outer/row lists; untagged immutable cells remain shared, tagged scalar dictionaries are new. Input rows are unchanged. |
| failure | Incomparable row components, malformed cells or decimal encoding errors propagate. |
| cost | O(n log n) row comparisons plus complete cell encoding; retains sorted input references and full encoded output concurrently. |
| Design | [tests/workflow/generate_fixtures.py](../../../../../tests/workflow/generate_fixtures.py), [docs/semantics.md](../../../../semantics.md), [docs/ingestion.md](../../../../ingestion.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json) |

## B0012

[Lines 62–69](../../../../../tests/workflow/generate_fixtures.py#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def oracle_path(db):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate the two-alias Edge path query using an independent finite set comprehension. |
| inputs / outputs | Reads db\[edge\] of typed (src,dst) tuples and returns set of (src,mid,dst) triples where first edge mid equals second edge source. |
| invariants | Allows the same physical edge in both aliases, including one newly inserted loop; set result eliminates duplicate witness triples. |
| ownership | Creates set and triple tuples sharing typed scalar cells; does not mutate the physical edge set. |
| failure | Missing table or malformed tuple widths raise KeyError/unpack errors. |
| cost | Nested Cartesian scan of m*m edge choices with tuple equality and output-set storage up to quadratic size. |
| Design | [tests/workflow/generate_fixtures.py](../../../../../tests/workflow/generate_fixtures.py), [docs/semantics.md](../../../../semantics.md), [docs/ingestion.md](../../../../ingestion.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json) |

## B0014

[Lines 72–73](../../../../../tests/workflow/generate_fixtures.py#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def oracle_projection(db):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate DISTINCT projection of records onto projected_key. |
| inputs / outputs | Reads two-cell records rows and returns a set of unary typed-key tuples. |
| invariants | Different witness values collapse to one key; an answer remains while any record with that projected key exists. |
| ownership | Creates set/unary tuples sharing key cells; caller physical set and witness cells are untouched. |
| failure | Missing records table or wrong tuple widths raise normally. |
| cost | One pass over records with expected set insertion; output memory is number of distinct projected keys. |
| Design | [tests/workflow/generate_fixtures.py](../../../../../tests/workflow/generate_fixtures.py), [docs/semantics.md](../../../../semantics.md), [docs/ingestion.md](../../../../ingestion.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json) |

## B0016

[Lines 76–78](../../../../../tests/workflow/generate_fixtures.py#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def oracle_exists(db):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate scalar EXISTS over flags filtered to typed Boolean true. |
| inputs / outputs | Reads unary flags and returns a singleton set containing one typed Boolean cell row, true or false. |
| invariants | Uses equality to (bool,True), so false and other typed scalars do not satisfy the filter; even no witnesses returns one false row. |
| ownership | Creates output singleton/tuples and borrows flags without mutation. |
| failure | Missing table or malformed unary row unpacking raises; generator can stop at first true witness. |
| cost | Short-circuit scan of at most all flags with constant-size output. |
| Design | [tests/workflow/generate_fixtures.py](../../../../../tests/workflow/generate_fixtures.py), [docs/semantics.md](../../../../semantics.md), [docs/ingestion.md](../../../../ingestion.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json) |

## B0018

[Lines 81–86](../../../../../tests/workflow/generate_fixtures.py#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def oracle_product(db):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate the independent disconnected left/right set product. |
| inputs / outputs | Reads unary left_rel/right_rel and returns set of two-cell tuples for every pair. |
| invariants | Empty either relation gives empty result; typed cells and left/right output order are preserved. |
| ownership | Allocates new pair tuples/set, sharing typed scalar cells; neither input set is mutated. |
| failure | Missing tables or incorrect row widths raise lookup/unpack errors. |
| cost | O(left_rows*right_rows) pair generation and potentially equally large output materialization. |
| Design | [tests/workflow/generate_fixtures.py](../../../../../tests/workflow/generate_fixtures.py), [docs/semantics.md](../../../../semantics.md), [docs/ingestion.md](../../../../ingestion.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json) |

## B0020

[Lines 89–90](../../../../../tests/workflow/generate_fixtures.py#L89); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def oracle_all_scalars(db):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Copy the current full-head scalar relation as the independent query result set. |
| inputs / outputs | Reads db\[scalar_values\] and returns a set containing each supplied typed row. |
| invariants | Preserves every cell and relies on the physical set to fold typed duplicate insertions; performs no projection or scalar normalization here. |
| ownership | New set shell shares immutable row tuples/typed cells with the physical table; not a deep copy. |
| failure | Missing table or unhashable/nonconforming rows raise normally. |
| cost | One traversal and expected hashing/insertion per row; O(number of rows) new set entries with shared row storage. |
| Design | [tests/workflow/generate_fixtures.py](../../../../../tests/workflow/generate_fixtures.py), [docs/semantics.md](../../../../semantics.md), [docs/ingestion.md](../../../../ingestion.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json) |

## B0021

[Lines 91–126](../../../../../tests/workflow/generate_fixtures.py#L91); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L91-L126:sha256:9933b13523af2ed85f530904c5f088d8e10dff472889687c24e7cddd6ef9ea6a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define self-join and projected-witness workflow cases and begin the scalar-EXISTS case in the module CASES literal. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/workflow/generate_fixtures.py](../../../../../tests/workflow/generate_fixtures.py), [docs/quickstart.md](../../../../quickstart.md), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 127–162](../../../../../tests/workflow/generate_fixtures.py#L127); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L127-L162:sha256:7a10df43363712c11e82268d9eb2c0c75831a56ab6453200c20b2ae5b2e12483
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Continue scalar-EXISTS/disconnected-product workflow data and begin the typed scalar catalog in CASES. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/workflow/generate_fixtures.py](../../../../../tests/workflow/generate_fixtures.py), [docs/quickstart.md](../../../../quickstart.md), [docs/code_review.md](../../../../code_review.md) |

## B0023

[Lines 163–183](../../../../../tests/workflow/generate_fixtures.py#L163); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L163-L183:sha256:b89c0e05cb4c6ff26a036ef3a35a70b47fef2071aff4bee2e2095dfc3b330039
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Complete the typed scalar workflow case with int64/date/decimal/UTF-8/NUL inputs and ordered duplicate/delete events. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/workflow/generate_fixtures.py](../../../../../tests/workflow/generate_fixtures.py), [docs/quickstart.md](../../../../quickstart.md), [docs/code_review.md](../../../../code_review.md) |

## B0024

[Lines 184–201](../../../../../tests/workflow/generate_fixtures.py#L184); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def catalog_for(case):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a standalone public catalog for a workflow case’s declared tables/columns. |
| inputs / outputs | Reads case\[tables\] name-to-(column,kind) lists; returns new schema_version/catalog version 1 document with nonnullable columns, source version 1 and empty constraints/statistics hints. |
| invariants | Adds binary collation exactly for string columns and preserves table/column iteration order; no enforced key or nullable support is inferred. |
| ownership | Builds fresh nested catalog/list/dict containers while sharing supplied immutable names/kind strings; case is not mutated. |
| failure | Missing/malformed case entries raise KeyError/unpack/iteration errors; unsupported kind text is emitted rather than validated. |
| cost | Linear in number of tables/columns with a new object graph proportional to that declaration size. |
| Design | [tests/workflow/generate_fixtures.py](../../../../../tests/workflow/generate_fixtures.py), [docs/semantics.md](../../../../semantics.md), [docs/ingestion.md](../../../../ingestion.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json) |

## B0026

[Lines 204–287](../../../../../tests/workflow/generate_fixtures.py#L204); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def build_case(case):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Write one workflow SQL/catalog/event template and independently computed set-state/delta fixture, returning its manifest entry. |
| inputs / outputs | Takes a case with name/sql/tables/events/oracle; creates or reuses OUT/name, writes query/catalog then applies physical set updates, writes events.template.jsonl and expected_oracle.json, and returns relative paths, counts/source offsets and empty-delta/initial data. |
| invariants | Contiguous sequence starts at 1 and logical offsets are sequence*100; duplicates/missing deletes are set no-ops, deltas are after-before/before-after and scalar EXISTS can change its singleton row. Templates intentionally omit catalog_sha256. Enabled assertions check row width/delete operation and final sequence/offset shape; -O removes those checks. |
| ownership | Owns physical table sets and oracle result sets; event/expected records share raw_values lists from case (not deep copies) and returned initial_current_rows shares the local encoded list. Writes directly overwrite files with no transactional rollback or cleanup on failure; all work is under module-global OUT. |
| failure | Lookup/type/assertion/oracle/JSON/file errors propagate and may leave query/catalog or later files partially written. An invalid operation under -O follows the delete branch; short rows can be truncated by zip when width assertion is disabled. |
| cost | For each event recomputes the full case oracle (path/product may be quadratic), differences sets and repeatedly sorts/materializes current/added/removed rows. Retains all event/expected states, serializes whole outputs and performs multiple file writes; this is fixture generation, not native acceptance. |
| Design | [tests/workflow/generate_fixtures.py](../../../../../tests/workflow/generate_fixtures.py), [docs/semantics.md](../../../../semantics.md), [docs/ingestion.md](../../../../ingestion.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json) |

## B0027

[Lines 288–303](../../../../../tests/workflow/generate_fixtures.py#L288); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
(OUT / "README.md").write_text(readme, encoding="utf-8")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Invoke build_case for each of the five fixed O08 workflows and overwrite the generated README. |
| inputs / outputs | Creates case_manifest from CASES; each build_case call writes its case query/catalog/event-template/expected-oracle files; then writes README.md under OUT. |
| invariants | The finite set/oracle construction details belong to the separately reviewed build_case contract. This block is an eager caller and does not invoke CROWN or prove CLI acceptance. |
| ownership | OUT’s case files and README are fixed fixture outputs; writes replace existing files and are not staged as a group. |
| failure | Any build_case assertion/write failure stops later cases and can leave a partial mixture of old/new files; README failure leaves prior case outputs. |
| cost | Runs build_case once per literal case, then serializes one README; cost is the finite fixture work and file writes, not a performance result. |
| Design | [tests/workflow/generate_fixtures.py](../../../../../tests/workflow/generate_fixtures.py), [tests/workflow/README.md](../../../../../tests/workflow/README.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json), [CMakeLists.txt](../../../../../CMakeLists.txt), tests/workflow/generate_fixtures.py:288-303 |

## B0028

[Lines 304–327](../../../../../tests/workflow/generate_fixtures.py#L304); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
print(f"wrote {len(CASES)} workflows; {sum(v['event_count'] for v in case_manifest.values())} events; {len(files)} source-hashed files")
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hash the O08 fixture directory and source specifications, then overwrite manifest.json. |
| inputs / outputs | Recursively enumerates every file under OUT except manifest.json, hashes each, hashes the listed docs, and writes the nested manifest. |
| invariants | The scan includes any extra/stale file already under OUT; it excludes only manifest.json. This block does not clean or stage the directory. |
| ownership | The script reads fixture/spec files and replaces manifest.json; no persistent staging copy is kept. |
| failure | File/hash/JSON/write errors propagate; earlier README/case writes from B0027 remain, and manifest replacement is not rolled back. |
| cost | Reads and hashes all selected directory files in chunks through digest(), then writes one JSON manifest; cost scales with existing file count and bytes. |
| Design | [tests/workflow/generate_fixtures.py](../../../../../tests/workflow/generate_fixtures.py), [tests/workflow/README.md](../../../../../tests/workflow/README.md), [tests/workflow/manifest.json](../../../../../tests/workflow/manifest.json), [docs/sql_support.md](../../../../sql_support.md), [docs/catalog.md](../../../../catalog.md), [docs/semantics.md](../../../../semantics.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_binding.md](../../../../sql_binding.md), tests/workflow/generate_fixtures.py:304-327 |
