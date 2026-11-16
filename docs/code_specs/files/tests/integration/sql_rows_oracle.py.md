# `tests/integration/sql_rows_oracle.py` — block usage map

[Source](../../../../../tests/integration/sql_rows_oracle.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `268535082d5824fe50a38dbf7d8da95371c4427b760ea0f0bc9c033015232e3a`. 338 lines partitioned into 45 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–27](../../../../../tests/integration/sql_rows_oracle.py#L1) | Imports dependencies; declares aliases; declares values/defaults or compile-time conditions. | 2 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 28–29](../../../../../tests/integration/sql_rows_oracle.py#L28) | Callable definition: def key(value): | calls dumps; returns json.dumps(value, sort_keys=True, ensure_ascii=False, separators=(",", ":")) · [reviewed contract](#b0002) |
| [B0003 · 30–31](../../../../../tests/integration/sql_rows_oracle.py#L30) | Explanatory comments or spacing. |  |
| [B0004 · 32–40](../../../../../tests/integration/sql_rows_oracle.py#L32) | Callable definition: def canonical(value): | calls isinstance, format, rstrip, isoformat; returns {"decimal": "0" if value == 0 else text}; {"date": value.isoformat()} · [reviewed contract](#b0004) |
| [B0005 · 41–42](../../../../../tests/integration/sql_rows_oracle.py#L41) | Explanatory comments or spacing. |  |
| [B0006 · 43–46](../../../../../tests/integration/sql_rows_oracle.py#L43) | Callable definition: def type_info(name): | calls fullmatch, int; returns {"kind": 6, "decimal": \[int(decimal\[1\]), int(decimal\[2\])\]} if decimal else { · [reviewed contract](#b0006) |
| [B0007 · 47–48](../../../../../tests/integration/sql_rows_oracle.py#L47) | Explanatory comments or spacing. |  |
| [B0008 · 49–52](../../../../../tests/integration/sql_rows_oracle.py#L49) | Callable definition: def parameter(value): | calls isinstance, Decimal, fromisoformat; returns Decimal(value\["decimal"\]) if "decimal" in value else datetime.date.fromisoformat(value\["date"\]); va… · [reviewed contract](#b0008) |
| [B0009 · 53–54](../../../../../tests/integration/sql_rows_oracle.py#L53) | Explanatory comments or spacing. |  |
| [B0010 · 55–59](../../../../../tests/integration/sql_rows_oracle.py#L55) | Callable definition: def column(name, kind, decimal=None): | calls ; returns result · [reviewed contract](#b0010) |
| [B0011 · 60–61](../../../../../tests/integration/sql_rows_oracle.py#L60) | Explanatory comments or spacing. |  |
| [B0012 · 62–65](../../../../../tests/integration/sql_rows_oracle.py#L62) | Callable definition: def catalog(scale=2): | calls column, in; returns {"version": 1, "tables": \[{"name": name, "columns": columns} for name in ("r", "t")\]}; 1 loop sites · [reviewed contract](#b0012) |
| [B0013 · 66–67](../../../../../tests/integration/sql_rows_oracle.py#L66) | Explanatory comments or spacing. |  |
| [B0014 · 68–78](../../../../../tests/integration/sql_rows_oracle.py#L68) | Callable definition: def inputs(scale=2, generic=False): | calls ; returns \[\[None\] * 6, \[0, 0, "", False, {"date": "1970-01-01"}, {"decimal": "0"}\], · [reviewed contract](#b0014) |
| [B0015 · 79–80](../../../../../tests/integration/sql_rows_oracle.py#L79) | Explanatory comments or spacing. |  |
| [B0016 · 81–97](../../../../../tests/integration/sql_rows_oracle.py#L81) | Callable definition: def updates(pool): | calls Random, range, enumerate, append; returns result; 3 loop sites · [reviewed contract](#b0016) |
| [B0017 · 98–99](../../../../../tests/integration/sql_rows_oracle.py#L98) | Explanatory comments or spacing. |  |
| [B0018 · 100–143](../../../../../tests/integration/sql_rows_oracle.py#L100) | Callable definition: def cases(engine): | calls add, len, catalog, updates; returns result; 7 loop sites · [reviewed contract](#b0018) |
| [B0019 · 144–145](../../../../../tests/integration/sql_rows_oracle.py#L144) | Explanatory comments or spacing. |  |
| [B0020 · 146–153](../../../../../tests/integration/sql_rows_oracle.py#L146) | Callable definition: def type_sql(col, engine): | calls get, DECIMAL; returns f"DECIMAL(38,{spec\['scale'\]})" if spec else "NUMERIC"; 'TEXT COLLATE "C"' if engine == "postgres" e… · [reviewed contract](#b0020) |
| [B0021 · 154–155](../../../../../tests/integration/sql_rows_oracle.py#L154) | Explanatory comments or spacing. |  |
| [B0022 · 156–159](../../../../../tests/integration/sql_rows_oracle.py#L156) | Callable definition: def ddl(case, engine): | calls join, type_sql; returns \[f"CREATE TABLE {table\['name'\]} (" + ",".join(; 2 loop sites · [reviewed contract](#b0022) |
| [B0023 · 160–161](../../../../../tests/integration/sql_rows_oracle.py#L160) | Explanatory comments or spacing. |  |
| [B0024 · 162–170](../../../../../tests/integration/sql_rows_oracle.py#L162) | Callable definition: def states(case): | calls get, key, values, range; 4 loop sites · [reviewed contract](#b0024) |
| [B0025 · 171–172](../../../../../tests/integration/sql_rows_oracle.py#L171) | Explanatory comments or spacing. |  |
| [B0026 · 173–192](../../../../../tests/integration/sql_rows_oracle.py#L173) | Callable definition: def duckdb_trace(case): | calls connect, execute, current_setting, fetchone; returns types, trace; 9 loop sites; source comment (unverified): # Required: no install, skip, or fallback. · [reviewed contract](#b0026) |
| [B0027 · 193–194](../../../../../tests/integration/sql_rows_oracle.py#L193) | Explanatory comments or spacing. |  |
| [B0028 · 195–205](../../../../../tests/integration/sql_rows_oracle.py#L195) | Callable definition: def literal(value): | calls type, str, isinstance, replace; returns "NULL"; "TRUE" if value else "FALSE" · [reviewed contract](#b0028) |
| [B0029 · 206–207](../../../../../tests/integration/sql_rows_oracle.py#L206) | Explanatory comments or spacing. |  |
| [B0030 · 208–220](../../../../../tests/integration/sql_rows_oracle.py#L208) | Callable definition: def pg_value(value, kind): | calls in, int, canonical, Decimal; returns None; int(value) · [reviewed contract](#b0030) |
| [B0031 · 221–223](../../../../../tests/integration/sql_rows_oracle.py#L221) | declares types or opens a type body. |  · [reviewed contract](#b0031) |
| [B0032 · 224–228](../../../../../tests/integration/sql_rows_oracle.py#L224) | Callable definition: def __init__(self, binaries): | calls Path, resolve, mkdtemp, mkdir · [reviewed contract](#b0032) |
| [B0033 · 229–229](../../../../../tests/integration/sql_rows_oracle.py#L229) | Explanatory comments or spacing. |  |
| [B0034 · 230–234](../../../../../tests/integration/sql_rows_oracle.py#L230) | Callable definition: def run(self, command, **options): | calls RuntimeError, Path; returns result.stdout · [reviewed contract](#b0034) |
| [B0035 · 235–235](../../../../../tests/integration/sql_rows_oracle.py#L235) | Explanatory comments or spacing. |  |
| [B0036 · 236–247](../../../../../tests/integration/sql_rows_oracle.py#L236) | Callable definition: def start(self): | calls run, str, with, open · [reviewed contract](#b0036) |
| [B0037 · 248–248](../../../../../tests/integration/sql_rows_oracle.py#L248) | Explanatory comments or spacing. |  |
| [B0038 · 249–253](../../../../../tests/integration/sql_rows_oracle.py#L249) | Callable definition: def sql(self, text, csv_output=False): | calls run, str; returns self.run(\[str(self.bin / "psql"), "--no-psqlrc", *formatting, "--quiet", · [reviewed contract](#b0038) |
| [B0039 · 254–254](../../../../../tests/integration/sql_rows_oracle.py#L254) | Explanatory comments or spacing. |  |
| [B0040 · 255–281](../../../../../tests/integration/sql_rows_oracle.py#L255) | Callable definition: def trace(self, case): | calls get, sub, literal, int; returns actual_types, \[Counter(key(\[pg_value(value, info\["kind"\]) for value, info in zip(row, actual_types)…; 12 loop sites; source comment (unverified): # Fixture SQL uses placeholders only as expressions, never in quotes. · [reviewed contract](#b0040) |
| [B0041 · 282–282](../../../../../tests/integration/sql_rows_oracle.py#L282) | Explanatory comments or spacing. |  |
| [B0042 · 283–291](../../../../../tests/integration/sql_rows_oracle.py#L283) | Callable definition: def close(self): | calls exists, run, str, not; 1 loop sites; source comment (unverified): # A timed-out start can still have created a server; probe its own data · [reviewed contract](#b0042) |
| [B0043 · 292–293](../../../../../tests/integration/sql_rows_oracle.py#L292) | Explanatory comments or spacing. |  |
| [B0044 · 294–334](../../../../../tests/integration/sql_rows_oracle.py#L294) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, cases; 11 loop sites · [reviewed contract](#b0044) |
| [B0045 · 335–338](../../../../../tests/integration/sql_rows_oracle.py#L335) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0045) |

## B0001

[Lines 1–27](../../../../../tests/integration/sql_rows_oracle.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L27:sha256:282d2da869ff06b4a6f109b2557684cc8abbacd117dbbd181ebc42933d5fe2a7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide the import, module documentation and declared fixture constants for sql_rows_oracle.py. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 28–29](../../../../../tests/integration/sql_rows_oracle.py#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def key(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Encode typed nullable rows for bag comparison. |
| inputs / outputs | JSON-compatible row to deterministic string. |
| invariants | JSON distinguishes false, zero, text and NULL; this does not evaluate SQL. |
| ownership | Owns returned Python text. |
| failure | Unserializable fixture fails directly. |
| cost | Linear JSON/scalar bytes; test comparison only. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |

## B0004

[Lines 32–40](../../../../../tests/integration/sql_rows_oracle.py#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def canonical(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Normalize exact engine scalars without floating conversion. |
| inputs / outputs | Decimal/date/other engine value to tagged JSON-compatible value. |
| invariants | Decimal spelling changes only; fixed formatting performs no rounding, and negative zero becomes zero. |
| ownership | Owns strings/tags; no native storage reference. |
| failure | Invalid unsupported values fail downstream rather than being coerced. |
| cost | Linear scalar bytes, outside production operation costs. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |

## B0006

[Lines 43–46](../../../../../tests/integration/sql_rows_oracle.py#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def type_info(name):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve actual engine scalar kind and decimal typmods. |
| inputs / outputs | Independent SQL type spelling to kind plus optional \[precision,scale\]. |
| invariants | Fixed decimal metadata is retained; generic numeric has no typmod. This parses only the explicit fixture vocabulary. |
| ownership | Owning small dict/list. |
| failure | Unknown spelling fails; no widening fallback. |
| cost | Bounded type-name match and integer parsing. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |

## B0008

[Lines 49–52](../../../../../tests/integration/sql_rows_oracle.py#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def parameter(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct independent exact engine input values. |
| inputs / outputs | Tagged decimal/date or JSON scalar to Python engine parameter. |
| invariants | Never parses decimal through float; bool and integer remain distinct. |
| ownership | Owns converted Decimal/date values; borrows immutable scalar objects. |
| failure | Malformed tags/date/number fail directly. |
| cost | Scalar parsing bytes only. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |

## B0010

[Lines 55–59](../../../../../tests/integration/sql_rows_oracle.py#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def column(name, kind, decimal=None):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build one nullable native schema declaration. |
| inputs / outputs | Name/type/optional scale to catalog column. |
| invariants | Boolean uses actual wire spelling bool; fixed decimals use precision 38; absent scale means generic numeric. |
| ownership | Owns fixture dict. |
| failure | Invalid kinds are rejected by actual reader/DDL mapping. |
| cost | Fixed fixture object construction. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |

## B0012

[Lines 62–65](../../../../../tests/integration/sql_rows_oracle.py#L62); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def catalog(scale=2):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the same declared scalar types in both source tables. |
| inputs / outputs | Scale to r/t catalog. |
| invariants | Physical integer fields are bigint; every column is nullable; immutable shared Python column list is serialized for the native factory. |
| ownership | Ordinary test metadata only. |
| failure | Native catalog admission remains authoritative. |
| cost | Fixed two-table/six-column fixture. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |

## B0014

[Lines 68–78](../../../../../tests/integration/sql_rows_oracle.py#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def inputs(scale=2, generic=False):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Supply a finite typed NULL/text/numeric corpus. |
| inputs / outputs | Scale/generic selection to nine full rows. |
| invariants | Contains NULL/zero/false/empty, case and NFC/NFD distinctions, valid dates, and matching fixed/generic decimal domains. |
| ownership | Owns ordinary fixture values. |
| failure | Bad fixture admission fails the driver; no case is skipped. |
| cost | Fixed small corpus; not exhaustive scalar-domain coverage. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |

## B0016

[Lines 81–97](../../../../../tests/integration/sql_rows_oracle.py#L81); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def updates(pool):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Generate reproducible full physical-row replacements. |
| inputs / outputs | Finite row pool to old/new nonnegative weights. |
| invariants | Before is tracked independently by exact full-row JSON identity; seeded replacements include deletion/no-op and both sources. |
| ownership | Owns test state and update list. |
| failure | Unexpected state mismatch fails during replay. |
| cost | Linear finite update count; only small expanded weights are used. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |

## B0018

[Lines 100–143](../../../../../tests/integration/sql_rows_oracle.py#L100); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def cases(engine):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare actual admitted SQL comparisons. |
| inputs / outputs | Engine name to deterministic scenario suite. |
| invariants | No unsupported query is silently filtered. PostgreSQL adds untyped-NULL inference and generic mixed-scale numeric beyond DuckDB fixed-decimal domain. |
| ownership | Owns SQL/schema/update fixtures. |
| failure | Native/engine rejection fails the suite. |
| cost | Cold finite fixture generation; no production overhead. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |

## B0020

[Lines 146–153](../../../../../tests/integration/sql_rows_oracle.py#L146); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def type_sql(col, engine):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Map fixture types to matching engine declarations. |
| inputs / outputs | Catalog column and engine to DDL type. |
| invariants | PostgreSQL text explicitly uses C collation; bigint/Boolean/date/fixed or generic numeric preserve declared domains. |
| ownership | Owns short DDL string. |
| failure | Unknown fixture type fails directly. |
| cost | Fixed mapping plus bounded scale rendering. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |

## B0022

[Lines 156–159](../../../../../tests/integration/sql_rows_oracle.py#L156); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def ddl(case, engine):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create only the controlled fixture tables. |
| inputs / outputs | Catalog to CREATE TABLE statements. |
| invariants | Table/column names are fixed trusted fixture identifiers, not a public SQL string API. |
| ownership | Owns test SQL text. |
| failure | Actual engine validates statements. |
| cost | Linear schema width, outside native work accounting. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |

## B0024

[Lines 162–170](../../../../../tests/integration/sql_rows_oracle.py#L162); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def states(case):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expand physical source bags independently. |
| inputs / outputs | Before/after full-row updates to complete small table rows. |
| invariants | Checks expected prior weights; Python reconstructs physical data only, never joins/predicates/DISTINCT results. |
| ownership | Owns small source map and yielded expanded lists. |
| failure | Malformed before value fails assertion. |
| cost | Sum of small expanded weights per snapshot; test-only full recomputation. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |

## B0026

[Lines 173–192](../../../../../tests/integration/sql_rows_oracle.py#L173); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def duckdb_trace(case):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Evaluate original SQL and actual metadata in DuckDB. |
| inputs / outputs | Scenario to independent typed result bags. |
| invariants | Requires installed DuckDB, asserts empty default_collation, fetches complete result width, and preserves fixed decimal precision/scale. |
| ownership | Private in-memory connection closes in finally; output is ordinary test data. |
| failure | No install/skip/fallback; SQL or settings mismatch fails. |
| cost | Full reference recomputation per snapshot, excluded from runtime update costs. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |

## B0028

[Lines 195–205](../../../../../tests/integration/sql_rows_oracle.py#L195); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def literal(value):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize trusted scalar fixtures for PostgreSQL. |
| inputs / outputs | NULL/bool/int/date/decimal/text to SQL expression. |
| invariants | Text quotes double; standard_conforming_strings is checked on startup; fixture numeric/date spellings are trusted and typed explicitly. |
| ownership | Owns SQL literal text. |
| failure | Malformed fixtures fail parsing/admission; not a general untrusted-input serializer. |
| cost | Linear literal bytes; test-only. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |

## B0030

[Lines 208–220](../../../../../tests/integration/sql_rows_oracle.py#L208); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def pg_value(value, kind):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode text by independently described PostgreSQL kind. |
| inputs / outputs | Nullable text and actual SQL kind to tagged comparable value. |
| invariants | Bool accepts only true/false; numeric stays Decimal-exact; date keeps a date tag rather than becoming plain text. |
| ownership | Owns decoded Python objects. |
| failure | Unsupported value spelling fails directly. |
| cost | Linear scalar bytes, no SQL evaluation. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |

## B0031

[Lines 221–223](../../../../../tests/integration/sql_rows_oracle.py#L221); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L221-L223:sha256:5102d7301c8ba76421b439d06bcb6f83c50bdf487255f1725bb4b5e7d8601cef
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Open the Postgres fixture class in sql_rows_oracle.py; method contracts describe instance effects. |
| inputs / outputs | The exact Python source fragment in; module names, class/data declarations or a continued docstring/fixture literal out. A fragment can continue syntax from its neighboring block and is not a standalone script. |
| invariants | Module imports execute trusted dependency initialization; fixture literals and function references are data, not native admission or oracle results. Explicit replay/generation belongs to the later callable or top-level statements. |
| ownership | Python module/class namespace owns imported objects and constructed containers/strings; callable references share their function objects. This storage is outside native query-account ownership. |
| failure | Import/dependency, syntax/name, allocation and any explicitly evaluated initializer errors propagate. Merely listing a timeout/schema/key set does not enforce it. |
| cost | Import/definition work and literal/regex/path setup occur at module execution; import caches follow interpreter policy. Later class construction, SQL/oracle replay, subprocesses and file emission retain their own costs; this fragment supplies their declarations/data. |
| Design | [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [docs/sql_rows_batches.md](../../../../sql_rows_batches.md), [docs/code_review.md](../../../../code_review.md) |

## B0032

[Lines 224–228](../../../../../tests/integration/sql_rows_oracle.py#L224); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def __init__(self, binaries):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create one private PostgreSQL fixture root. |
| inputs / outputs | Explicit binary directory to task-owned data/socket paths. |
| invariants | mkdtemp and 0700 socket permissions isolate the instance; failure does not trigger automatic deletion before shutdown verification. |
| ownership | Owns only a new temporary root. |
| failure | Filesystem/binary failures propagate. |
| cost | One small directory setup; no server starts here. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |

## B0034

[Lines 230–234](../../../../../tests/integration/sql_rows_oracle.py#L230); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def run(self, command, **options):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Execute one bounded oracle-tool command. |
| inputs / outputs | Argument vector/input to captured stdout. |
| invariants | No shell interpolation; nonzero exits expose actual stderr, not a fallback result. |
| ownership | Subprocess capture belongs to the test. |
| failure | Timeout or explicit RuntimeError propagates to finally cleanup. |
| cost | Tool runtime and captured output; no production dependency. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |

## B0036

[Lines 236–247](../../../../../tests/integration/sql_rows_oracle.py#L236); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def start(self):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Start and validate one local UTF8/C PostgreSQL instance. |
| inputs / outputs | Explicit toolchain to a private ready server. |
| invariants | No TCP listener; socket/port/auth are task-local; actual encoding, database datcollate and string settings are checked. |
| ownership | Own data/log directories; main finally owns shutdown even after partial startup. |
| failure | Any startup/settings failure reaches finally; no started flag hides a live PID. |
| cost | Cold initdb/pg_ctl/settings queries only. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |

## B0038

[Lines 249–253](../../../../../tests/integration/sql_rows_oracle.py#L249); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def sql(self, text, csv_output=False):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Query only the private socket with checked failure status. |
| inputs / outputs | SQL/meta-command text to plain or CSV output. |
| invariants | Explicit host/port/user/db override ambient connection defaults; ON_ERROR_STOP is mandatory. |
| ownership | Owns subprocess output; no external application writes. |
| failure | Server/psql failure propagates with stderr. |
| cost | One subprocess/query batch; test-only. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |

## B0040

[Lines 255–281](../../../../../tests/integration/sql_rows_oracle.py#L255); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def trace(self, case):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Obtain full independent PostgreSQL metadata and bags. |
| inputs / outputs | Actual SQL, fixture tables and physical states to types/results. |
| invariants | gdesc determines full width/typmods before aliases are built; native width never controls the reference projection. Snapshot indices and complete bags are checked. |
| ownership | Owns reference SQL/results; no native row or expression evaluator is used. |
| failure | Arity/type/query/format failures fail the scenario; no prefix comparison or fallback. |
| cost | Full small-bag recomputation plus independent describe and JSON export; not an update-path benchmark. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |

## B0042

[Lines 283–291](../../../../../tests/integration/sql_rows_oracle.py#L283); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def close(self):
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Stop this private service before deleting its files. |
| inputs / outputs | Own data/socket root to checked termination/cleanup. |
| invariants | A PID is probed even after failed startup; successful stop must remove PID/socket files. Shutdown failure preserves the directory. |
| ownership | Touches only this newly created instance. |
| failure | Stop/verification failure propagates before rmtree. |
| cost | Bounded pg_ctl wait and private directory cleanup. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |

## B0044

[Lines 294–334](../../../../../tests/integration/sql_rows_oracle.py#L294); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
def main():
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require complete typed SQL agreement over the configured finite fixture suite on both native backends. |
| inputs / outputs | Explicit driver/engine arguments to success counts. |
| invariants | Checks full native response count, sequence, kind/decimal metadata, positive integer weights and unique compressed keys against engine bags. Nullable metadata is retained but not independently asserted. |
| ownership | Owns native subprocess data; private PostgreSQL lifecycle is finally-covered. |
| failure | Missing engine/toolchain, mismatch or shutdown failure prevents a success receipt. |
| cost | Finite expanded-bag oracle suite; no broad large-weight, latency or complete SQL-feature claim. |
| Design | [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |

## B0045

[Lines 335–338](../../../../../tests/integration/sql_rows_oracle.py#L335); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
if __name__ == "__main__":
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch the script-only finite SQL-row fixture suite on both native backends and require complete agreement for its configured cases and snapshots. |
| inputs / outputs | When __name__ is __main__, invoke main(). Arguments parsed by main retain its existing contract. Ignore the delegated return value; a normal return completes through the interpreter. |
| invariants | This block runs only under the script entry-name guard. Importing the module skips this block; that does not certify the rest of module import as side-effect free. The called function retains its separately reviewed algorithm/fixture obligations. |
| ownership | The Python process owns argv, streams and interpreter state; delegated code retains responsibility for its temporary files/child processes. This wrapper creates no native query account, grant, engine state or retained callback. |
| failure | No presentation catch is added here: main/fixture failures and SystemExit propagate through the interpreter. This block supplies no extra retry or rollback. |
| cost | One entry-name guard and one delegated main invocation. Main owns fixture generation, subprocess/oracle and I/O costs; this wrapper does not bound them. |
| Design | [tests/integration/sql_rows_oracle.py](../../../../../tests/integration/sql_rows_oracle.py), [docs/development.md](../../../../development.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [Refactor.md §W05](../../../../../Refactor.md), [build/verification/w05-rows-oracle-human-review-v1/README.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/README.md), [build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md](../../../../../build/verification/w05-rows-oracle-human-review-v1/CORRECTION-1.md) |
