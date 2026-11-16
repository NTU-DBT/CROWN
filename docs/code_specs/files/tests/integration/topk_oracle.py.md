# `tests/integration/topk_oracle.py` — block usage map

[Source](../../../../../tests/integration/topk_oracle.py) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `f672bcc9a2f622f1cc48fb137bace413022ae512f643d5101ca7d3dc4ee1bdaa`. 290 lines partitioned into 43 blocks using `python_ast`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–20](../../../../../tests/integration/topk_oracle.py#L1) | Imports dependencies; declares values/defaults or compile-time conditions. | 1 loop sites; source comment (unverified): #!/usr/bin/env python3 · [reviewed contract](#b0001) |
| [B0002 · 21–22](../../../../../tests/integration/topk_oracle.py#L21) | Callable definition: def key(value): | calls dumps; returns json.dumps(value,sort_keys=True,ensure_ascii=False,separators=(',',':')) · [reviewed contract](#b0002) |
| [B0003 · 23–24](../../../../../tests/integration/topk_oracle.py#L23) | Explanatory comments or spacing. |  |
| [B0004 · 25–32](../../../../../tests/integration/topk_oracle.py#L25) | Callable definition: def scalar(value): | calls type, isinstance, encode, set; returns (-1,None); (2,value) · [reviewed contract](#b0004) |
| [B0005 · 33–34](../../../../../tests/integration/topk_oracle.py#L33) | Explanatory comments or spacing. |  |
| [B0006 · 35–36](../../../../../tests/integration/topk_oracle.py#L35) | Callable definition: def compare(a,b): | calls ; returns (a&gt;b)-(a&lt;b) · [reviewed contract](#b0006) |
| [B0007 · 37–38](../../../../../tests/integration/topk_oracle.py#L37) | Explanatory comments or spacing. |  |
| [B0008 · 39–49](../../../../../tests/integration/topk_oracle.py#L39) | Callable definition: def row_compare(a,b,order): | calls compare, scalar, tuple, map; returns result; compare(tuple(map(scalar,a\['identity'\])),tuple(map(scalar,b\['identity'\]))); 1 loop sites · [reviewed contract](#b0008) |
| [B0009 · 50–51](../../../../../tests/integration/topk_oracle.py#L50) | Explanatory comments or spacing. |  |
| [B0010 · 52–58](../../../../../tests/integration/topk_oracle.py#L52) | Callable definition: def topk(records,request): | calls sorted, cmp_to_key, row_compare, min; returns {'selected_rows':request\['k'\]-remaining,'entries':result}; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 59–60](../../../../../tests/integration/topk_oracle.py#L59) | Explanatory comments or spacing. |  |
| [B0012 · 61–64](../../../../../tests/integration/topk_oracle.py#L61) | Callable definition: def numeric(coefficient,scale): | calls str, abs, rjust, else; returns {'decimal':'0' if not coefficient else sign+text} · [reviewed contract](#b0012) |
| [B0013 · 65–66](../../../../../tests/integration/topk_oracle.py#L65) | Explanatory comments or spacing. |  |
| [B0014 · 67–73](../../../../../tests/integration/topk_oracle.py#L67) | Callable definition: def decimal(value): | calls Fraction, str, ValueError, max; returns numeric(number.numerator*(10**scale//number.denominator),scale); 2 loop sites · [reviewed contract](#b0014) |
| [B0015 · 74–75](../../../../../tests/integration/topk_oracle.py#L74) | Explanatory comments or spacing. |  |
| [B0016 · 76–80](../../../../../tests/integration/topk_oracle.py#L76) | Callable definition: def average(total,count,scale): | calls divmod, abs, numeric; returns None; numeric(-coefficient if total&lt;0 else coefficient,scale) · [reviewed contract](#b0016) |
| [B0017 · 81–82](../../../../../tests/integration/topk_oracle.py#L81) | Explanatory comments or spacing. |  |
| [B0018 · 83–88](../../../../../tests/integration/topk_oracle.py#L83) | Callable definition: def decode(value,kind): | calls bool, decimal; returns None; bool(value) · [reviewed contract](#b0018) |
| [B0019 · 89–90](../../../../../tests/integration/topk_oracle.py#L89) | Explanatory comments or spacing. |  |
| [B0020 · 91–94](../../../../../tests/integration/topk_oracle.py#L91) | Callable definition: def catalog(): | calls ; returns {'version':1,'tables':\[{'name':'r','columns':columns}\]}; 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 95–96](../../../../../tests/integration/topk_oracle.py#L95) | Explanatory comments or spacing. |  |
| [B0022 · 97–104](../../../../../tests/integration/topk_oracle.py#L97) | Callable definition: def pool(): | calls ; returns \[\[1,None,'b',False,{'date':'0001-01-01'},{'decimal':'-10'}\], · [reviewed contract](#b0022) |
| [B0023 · 105–106](../../../../../tests/integration/topk_oracle.py#L105) | Explanatory comments or spacing. |  |
| [B0024 · 107–113](../../../../../tests/integration/topk_oracle.py#L107) | Callable definition: def updates(): | calls pool, len, put, append; returns result; 2 loop sites · [reviewed contract](#b0024) |
| [B0025 · 114–115](../../../../../tests/integration/topk_oracle.py#L114) | Explanatory comments or spacing. |  |
| [B0026 · 116–124](../../../../../tests/integration/topk_oracle.py#L116) | Callable definition: def rankings(width): | calls range, append; returns \[{'order':order,'k':k} for order in orders for k in \[0,1,2,7,MAXIMUM\]\]; 5 loop sites · [reviewed contract](#b0026) |
| [B0027 · 125–126](../../../../../tests/integration/topk_oracle.py#L125) | Explanatory comments or spacing. |  |
| [B0028 · 127–171](../../../../../tests/integration/topk_oracle.py#L127) | Callable definition: def cases(): | calls rows, append, updates, all; returns result; 3 loop sites · [reviewed contract](#b0028) |
| [B0029 · 172–173](../../../../../tests/integration/topk_oracle.py#L172) | Explanatory comments or spacing. |  |
| [B0030 · 174–176](../../../../../tests/integration/topk_oracle.py#L174) | Callable definition: def physical(value): | calls isinstance, get, int, type; returns value.get('decimal',value.get('date')); int(value) if type(value) is bool else value · [reviewed contract](#b0030) |
| [B0031 · 177–178](../../../../../tests/integration/topk_oracle.py#L177) | Explanatory comments or spacing. |  |
| [B0032 · 179–195](../../../../../tests/integration/topk_oracle.py#L179) | Callable definition: def query_records(case,database): | calls execute, decode, zip, key; returns list(grouped.values()); records; 5 loop sites · [reviewed contract](#b0032) |
| [B0033 · 196–197](../../../../../tests/integration/topk_oracle.py#L196) | Explanatory comments or spacing. |  |
| [B0034 · 198–209](../../../../../tests/integration/topk_oracle.py#L198) | Callable definition: def sql_rank(case,database,request): | calls range, len, q, join; returns grouped; 6 loop sites · [reviewed contract](#b0034) |
| [B0035 · 210–211](../../../../../tests/integration/topk_oracle.py#L210) | Explanatory comments or spacing. |  |
| [B0036 · 212–233](../../../../../tests/integration/topk_oracle.py#L212) | Callable definition: def expected(case): | calls connect, execute, r, range; returns trace,sql_crosschecks; 3 loop sites · [reviewed contract](#b0036) |
| [B0037 · 234–235](../../../../../tests/integration/topk_oracle.py#L234) | Explanatory comments or spacing. |  |
| [B0038 · 236–238](../../../../../tests/integration/topk_oracle.py#L236) | Callable definition: def native(case,indexed): | calls dict, items; returns {name:value for name,value in dict(case,indexed=indexed).items(); 1 loop sites · [reviewed contract](#b0038) |
| [B0039 · 239–240](../../../../../tests/integration/topk_oracle.py#L239) | Explanatory comments or spacing. |  |
| [B0040 · 241–257](../../../../../tests/integration/topk_oracle.py#L241) | Callable definition: def check(case,observed,reference): | calls len, AssertionError, zip, key; guard def check(case,observed,reference):; returns comparisons; 5 loop sites · [reviewed contract](#b0040) |
| [B0041 · 258–259](../../../../../tests/integration/topk_oracle.py#L258) | Explanatory comments or spacing. |  |
| [B0042 · 260–287](../../../../../tests/integration/topk_oracle.py#L260) | Callable definition: def main(): | calls ArgumentParser, add_argument, parse_args, mkdir; guard compared=sum(check(case,result,references\[case\['id'\]\]) for (case,_),result in zip(requests,observed…; 5 loop sites · [reviewed contract](#b0042) |
| [B0043 · 288–290](../../../../../tests/integration/topk_oracle.py#L288) | declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0043) |

## B0001

[Lines 1–20](../../../../../tests/integration/topk_oracle.py#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L20:sha256:2dca1c75133a7293c2916fc35c6ed5fe8169253fa4ad9074f3406f141d348500
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare isolated test dependencies, exact fixture types and constants. |
| inputs / outputs | Imports/includes and local aliases configure this one test module; they are not a production query primitive. |
| invariants | Python oracle imports no CROWN implementation. Native unit replacement new is confined to its one test translation unit and standard assertions must remain enabled. |
| ownership | Ordinary module definitions own no active native query or subprocess. |
| failure | Missing dependencies or build errors prevent this test from starting. |
| cost | Module/build setup only; no update-path or ranking-time charge is implied. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/integration/topk_oracle.py](../../../../../tests/integration/topk_oracle.py) |

## B0002

[Lines 21–22](../../../../../tests/integration/topk_oracle.py#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L21-L22:sha256:d10540d9ceb14c3abd465d591325398ec6ac8261eacb2be6e07934fd1a502a39
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Canonicalize test transport without scalar type conflation. |
| inputs / outputs | A JSON-compatible value becomes deterministic UTF8 JSON text. |
| invariants | Boolean true and integer1 serialize differently; dictionaries are key-sorted. |
| ownership | The returned Python string owns its bytes. |
| failure | Invalid JSON objects fail normally. |
| cost | Linear ordinary serialization outside query memory. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/integration/topk_oracle.py](../../../../../tests/integration/topk_oracle.py) |

## B0004

[Lines 25–32](../../../../../tests/integration/topk_oracle.py#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L32:sha256:9e89f1ec1103cfb44fcfcaddb8795c6324b2dacbd2afe50a0627eb2fb2c2a437
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build independent exact typed comparison keys. |
| inputs / outputs | NULL,int,TEXT,bool,date and decimal wire cells become type-separated exact Python values. |
| invariants | Decimal uses Fraction, dates ordinal days and strings UTF8 bytes; no binary float enters ordering. |
| ownership | All comparison keys are ordinary Python values. |
| failure | Unsupported fixture types raise rather than silently coerce. |
| cost | Linear scalar text/decimal parsing as independent oracle work. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/integration/topk_oracle.py](../../../../../tests/integration/topk_oracle.py) |

## B0006

[Lines 35–36](../../../../../tests/integration/topk_oracle.py#L35); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L36:sha256:2e5d5479a10acf5e173725752b5be17080c81e6c8c562879375c3c2cddad83fc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return an ordinary three-way exact comparison result. |
| inputs / outputs | Comparable independent values produce -1,0,1. |
| invariants | Only the sign of exact native Python comparisons is used. |
| ownership | Arguments are borrowed synchronously. |
| failure | Incomparable fixture values fail the oracle. |
| cost | Scalar/tuple comparison cost belongs to the external oracle. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/integration/topk_oracle.py](../../../../../tests/integration/topk_oracle.py) |

## B0008

[Lines 39–49](../../../../../tests/integration/topk_oracle.py#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L39-L49:sha256:90dd93bef7c4fb8d9f59757720e7c864e157775b9b845542e348728d754b266e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Implement the declared independent key/identity order. |
| inputs / outputs | Two independently computed records and rank keys produce a comparator sign. |
| invariants | NULL placement is independent of direction; remaining ties use ONLY identity ASC NULLS FIRST, never unranked aggregate values. |
| ownership | Only fixture records are borrowed; no production comparator is imported. |
| failure | Malformed key/type metadata fails the test. |
| cost | Requested keys then identity fields/bytes, using exact Python types. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/integration/topk_oracle.py](../../../../../tests/integration/topk_oracle.py) |

## B0010

[Lines 52–58](../../../../../tests/integration/topk_oracle.py#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L52-L58:sha256:c5348d830bd85587b0c387bd9887b35dec58c60f8a6fb9a00f305d76b5090c59
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sort independent records and take compressed logical copies. |
| inputs / outputs | Expected records plus k/order produce ordered selected entries and selected_rows. |
| invariants | Selection subtracts min(weight,remaining); no weight expansion or fixed-width total sum is used. |
| ownership | The result owns Python record dictionaries while sharing immutable fixture scalar values. |
| failure | Malformed expected fixtures propagate as failure. |
| cost | Ordinary external full sort plus one selected prefix; no native cost claim. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/integration/topk_oracle.py](../../../../../tests/integration/topk_oracle.py) |

## B0012

[Lines 61–64](../../../../../tests/integration/topk_oracle.py#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L61-L64:sha256:95b27bb014d14b2367717b00da2f655c7c0037146ded429570e81a3cda444d76
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Render a rounded exact decimal coefficient canonically. |
| inputs / outputs | Signed integer coefficient and scale produce a decimal-tagged JSON cell. |
| invariants | Zero is positive canonical0; fractional trailing zeros are removed without float conversion. |
| ownership | The result owns a Python string/dictionary. |
| failure | Invalid fixture scale would fail ordinary operations. |
| cost | Linear coefficient digit formatting; oracle presentation work. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/integration/topk_oracle.py](../../../../../tests/integration/topk_oracle.py) |

## B0014

[Lines 67–73](../../../../../tests/integration/topk_oracle.py#L67); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L67-L73:sha256:8f2bb373ddbcffa9249acecdb5dede8597f22f535863221a0c33f27773a0a4b7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Canonicalize independently stored exact finite decimals. |
| inputs / outputs | SQLite integer/TEXT decimal values become Fraction and a finite base10 representation. |
| invariants | Only denominators composed of2 and5 are accepted; canonical result matches numeric equality. |
| ownership | Ordinary Python exact integers/Fraction/string own their state. |
| failure | A nonterminating denominator is rejected. |
| cost | Bounded finite fixture factorization/digit formatting; no native helper is reused. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/integration/topk_oracle.py](../../../../../tests/integration/topk_oracle.py) |

## B0016

[Lines 76–80](../../../../../tests/integration/topk_oracle.py#L76); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L76-L80:sha256:4a12f970b0a8ece2a6ec16a2686876bab219ef4551b38ceee30bf7b13fdce095
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Quantize SQL SUM/COUNT at the declared display scale. |
| inputs / outputs | Exact integer total,count,scale produce NULL or rounded decimal output. |
| invariants | Round half away from zero before top-k comparison; equal displayed AVG values use identity ties. SQLite AVG/double is never authority. |
| ownership | Ordinary Python unbounded integers own the arithmetic state. |
| failure | Invalid positive-count input fails; count0 returns NULL before inspecting a NULL total. |
| cost | Exact integer multiply/divide/remainder and digit rendering; external oracle cost. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/integration/topk_oracle.py](../../../../../tests/integration/topk_oracle.py) |

## B0018

[Lines 83–88](../../../../../tests/integration/topk_oracle.py#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L88:sha256:9ce1f9611591bf377850884a17a8a440cd570f6a77a6f1a0bd39eb9f5224e62a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Restore explicit fixture output scalar types. |
| inputs / outputs | An independent SQLite value and declared case kind produce tagged date/decimal or Boolean/integer/TEXT. |
| invariants | NULL stays NULL; types come from fixture specification, not native program metadata. |
| ownership | Decoded Python values own their payload. |
| failure | Unexpected value/type errors propagate. |
| cost | Scalar conversion only; no production casts or comparator calls. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/integration/topk_oracle.py](../../../../../tests/integration/topk_oracle.py) |

## B0020

[Lines 91–94](../../../../../tests/integration/topk_oracle.py#L91); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L91-L94:sha256:ef2fbafb20c3d3cc53fb2f77648278d4ca5d9dac5059ae4b9c1261829688dec3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the independent six-column physical fixture catalog. |
| inputs / outputs | Returns one r table with non-null id and nullable scalar fields. |
| invariants | The SQL string domain remains UTF8 without U+0000; generic decimals are projected unchanged. |
| ownership | The returned Python DTO is request data, not factory authority. |
| failure | Invalid catalog admission is a native failure. |
| cost | Fixed ordinary fixture allocation. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/integration/topk_oracle.py](../../../../../tests/integration/topk_oracle.py) |

## B0022

[Lines 97–104](../../../../../tests/integration/topk_oracle.py#L97); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L97-L104:sha256:cece697ed4f681eefee07f6dfeb1d12ee887f7c928b7aaa61ea8b70db22608c4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide exact typed source rows for finite update traces. |
| inputs / outputs | Returns six full rows including NULL, signs, valid control/non-ASCII TEXT, date boundaries and tiny decimals. |
| invariants | All positive TEXT fixtures are valid UTF8 and NUL-free; no source-domain extension is asserted. |
| ownership | The fixture owns all Python scalars. |
| failure | A source-domain rejection fails native validation rather than being excluded silently. |
| cost | Fixed tiny data set; not a workload/performance claim. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/integration/topk_oracle.py](../../../../../tests/integration/topk_oracle.py) |

## B0024

[Lines 107–113](../../../../../tests/integration/topk_oracle.py#L107); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L107-L113:sha256:77c69e94b0023bf1109ef5881fe92cb9ee51aa539657a5cb18a741c847cea8cc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a valid complete physical before/after chain. |
| inputs / outputs | Fixed row pool becomes insertions, replacements, deletions and one no-op. |
| invariants | Every old weight is tracked independently; removing one projected witness does not erase another. |
| ownership | Returned update DTOs own data shared with the fixed pool. |
| failure | A broken expected source chain is checked again by expected(). |
| cost | Finite fixed event list; no hidden native state access. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/integration/topk_oracle.py](../../../../../tests/integration/topk_oracle.py) |

## B0026

[Lines 116–124](../../../../../tests/integration/topk_oracle.py#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L116-L124:sha256:02e85a21e1f90f2900103ab55845f364df11fab85dfd5f0fcb17319858481d4f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate the declared rank/cutoff controls. |
| inputs / outputs | Output width yields empty, ASC/DESC/NULL, per-field, mixed and repeated-key requests. |
| invariants | k includes0,small cutoffs and UINT64_MAX; field indices remain within the specified output width. |
| ownership | Ordinary request lists own their descriptors. |
| failure | A changed native output arity is exposed by public admission or result comparison. |
| cost | Finite descriptor construction, not selection work. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/integration/topk_oracle.py](../../../../../tests/integration/topk_oracle.py) |

## B0028

[Lines 127–171](../../../../../tests/integration/topk_oracle.py#L127); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L127-L171:sha256:6c0df5210a1d3cf9e603d4d89de44a39ede156727b4c940dbf68ae9011ea2f5a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Specify independent SQL/result-family cases and focused tie counterexamples. |
| inputs / outputs | Returns actual SQL/catalog/updates plus separate SQLite reference SQL/type/output maps. |
| invariants | Omitted group keys, unranked SUM opposing identity and AVG1.003/1.004 display ties discriminate incorrect fallbacks. Symbolic huge bags are separately marked. |
| ownership | All expectations remain Python/SQL fixture data and are stripped from native requests. |
| failure | Any invalid source/planner/query fixture fails visibly. |
| cost | Thirteen fixed query cases; no claim of arbitrary SQL coverage. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/integration/topk_oracle.py](../../../../../tests/integration/topk_oracle.py) |

## B0030

[Lines 174–176](../../../../../tests/integration/topk_oracle.py#L174); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L174-L176:sha256:3240b1f71cdbcc9cc1af8c0c103b8a0895374985962bab0eeb64cbeb677f95d7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind exact fixture cells into SQLite storage. |
| inputs / outputs | Tagged date/decimal become their exact strings and Boolean becomes SQLite integer. |
| invariants | DECIMAL is stored as TEXT only for unchanged projection; numeric rank is independently Fraction-based. SQL joins/predicates/COUNT/SUM operate on admitted integer/TEXT fields. |
| ownership | Returned SQLite binding values are ordinary Python owned values. |
| failure | Unsupported value shapes fail the fixture. |
| cost | Scalar adaptation only; not native SQL type admission evidence. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/integration/topk_oracle.py](../../../../../tests/integration/topk_oracle.py) |

## B0032

[Lines 179–195](../../../../../tests/integration/topk_oracle.py#L179); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L179-L195:sha256:56ef5ef0c0af72dc0291bb8823066848081faaafb2ef5a4c40f516040ef64d82
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recompute independent query rows/groups from SQLite. |
| inputs / outputs | Actual current source database and reference SQL yield compressed expected records. |
| invariants | Rows compress by complete rendered tuple; aggregates retain full key and use SQL SUM/COUNT plus exact displayed AVG. No native snapshot enters expectations. |
| ownership | Python dictionaries own expected rows/groups independently of the native process. |
| failure | SQL/type/rounding errors abort the corpus. |
| cost | Full external query execution plus compression/rendering; explicitly recomputation. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/integration/topk_oracle.py](../../../../../tests/integration/topk_oracle.py) |

## B0034

[Lines 198–209](../../../../../tests/integration/topk_oracle.py#L198); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L198-L209:sha256:43b2424e8aca813fa787f1f9c14c78912c648d4df03da2189d8c67da68331827
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Cross-check the independent row sorter with SQLite ORDER BY. |
| inputs / outputs | Nondecimal representable row cases and rank request yield ordered compressed SQL rows. |
| invariants | Requested keys and full-row identity tie columns use explicit NULL policies. Clamping huge LIMIT is equivalent for the tiny bounded expanded source cases. |
| ownership | The SQLite cursor is consumed into Python-owned expected records. |
| failure | Any order discrepancy fails before native acceptance. |
| cost | Full external SQL sort on small expanded bags; never used for symbolic huge weights. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/integration/topk_oracle.py](../../../../../tests/integration/topk_oracle.py) |

## B0036

[Lines 212–233](../../../../../tests/integration/topk_oracle.py#L212); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L212-L233:sha256:03b42dfa63f55b6df21199d66c311c5a569ea2770ac1bbea7000acf2738b12e8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct every independent committed-epoch expectation. |
| inputs / outputs | A case drives a fresh SQLite database through actual complete-row replacements and ranks each query result. |
| invariants | Before weights are checked; all initial/update epochs are retained. Huge symbolic single-row weights avoid expansion. Mature-SQL rank crosschecks run where types permit. |
| ownership | The helper owns a private SQLite connection and Python expectation lists; normal completion explicitly closes the database. |
| failure | SQL/chain/rank errors propagate and prevent a native pass; no expected data are taken from native output. |
| cost | Finite external full recomputation and sorts; native/SQL work scopes stay separate. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/integration/topk_oracle.py](../../../../../tests/integration/topk_oracle.py) |

## B0038

[Lines 236–238](../../../../../tests/integration/topk_oracle.py#L236); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L236-L238:sha256:e79e53ba79d47e4b9c22b6b7d4af6d9e15199ba8beb5c031aba1edef9164414c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Strip oracle-only data before native execution. |
| inputs / outputs | A case and backend flag produce only SQL/catalog/update/rank/family execution inputs. |
| invariants | Reference SQL,type/output maps and symbolic markers never enter the C++ driver. |
| ownership | The returned ordinary DTO is serialized for the subprocess. |
| failure | Malformed request data fails native decode/admission. |
| cost | Linear fixture descriptor filtering. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/integration/topk_oracle.py](../../../../../tests/integration/topk_oracle.py) |

## B0040

[Lines 241–257](../../../../../tests/integration/topk_oracle.py#L241); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L241-L257:sha256:e913d39d6ec942e6f3db568f3e240a95b17f39d1190256ce7811cbf938061453
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare actual ordered public output against independent expectations. |
| inputs / outputs | A native trace and expected trace must agree in id,epoch,count,ordered identities,values and weights. |
| invariants | Canonical JSON equality preserves Boolean/integer distinctions; unique identity and exact selected-weight totals are checked. k0 must collect no candidates. |
| ownership | Actual/expected DTOs are borrowed for synchronous comparison. |
| failure | Any semantic/shape/type/metric mismatch raises and prevents summary acceptance. |
| cost | Linear transported records plus exact Python sums; not native performance work. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/integration/topk_oracle.py](../../../../../tests/integration/topk_oracle.py) |

## B0042

[Lines 260–287](../../../../../tests/integration/topk_oracle.py#L260); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L260-L287:sha256:aca872b6a6e1dcd302542291dcd8afb404c2a311f60ff07326567c96a53429be
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the finite independent corpus on both storage backends with optional raw retention. |
| inputs / outputs | --driver and optional new --artifacts directory produce native requests/results and a pass summary only after all checks. |
| invariants | Reference data are computed independently first; exact result count is required. Raw stdout/stderr are saved before exit/output assertions. No empty/subset corpus may pass. |
| ownership | The process owns request/expected JSON; optional artifacts preserve raw bytes and normal summary. |
| failure | SQLite/native/timeout/decode/comparison errors fail. Existing artifact directories reject reuse; no fallback engine or catch/retry wrapper is added. |
| cost | Finite13query/two-backend corpus and300s subprocess deadline; validation timings imply no speedup or full-suite claim. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/integration/topk_oracle.py](../../../../../tests/integration/topk_oracle.py) |

## B0043

[Lines 288–290](../../../../../tests/integration/topk_oracle.py#L288); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L288-L290:sha256:05c8c1199f125d611f92c51da7d3b3a7fdbe1084a54d2b4b2a2bc10686bb2a34
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch direct script execution to the independent corpus runner. |
| inputs / outputs | The __main__ guard calls main; importing exposes oracle helpers without running native tests. |
| invariants | All pass output comes after main completes its independent comparisons. |
| ownership | The runner owns its subprocess and ordinary fixture data. |
| failure | Uncaught validation/timeout errors yield a failing test process. |
| cost | Fixed dispatch plus the explicit main corpus work. |
| Design | [include/crown/runtime/topk.hpp](../../../../../include/crown/runtime/topk.hpp), [Refactor.md](../../../../../Refactor.md), [docs/scalars.md](../../../../scalars.md), [docs/sql_rows_runtime.md](../../../../sql_rows_runtime.md), [docs/sql_aggregate_runtime.md](../../../../sql_aggregate_runtime.md), [tests/integration/topk_oracle.py](../../../../../tests/integration/topk_oracle.py) |
