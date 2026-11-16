# W05 SQL bag inventory v1

Captured 2026-11-12 from the active W05 contract and current source. This was a
read-only source inventory; no source, build output, test, or maintained-document
changes were made.

## Current boundary

`BoundSql` preserves the SQL distinction: a plain row-producing `SELECT` is
`bag`, while `SELECT DISTINCT` is `set`. This is not silently rewritten. The
current normalizer then rejects a row-producing bag before constructing a CQ;
there is no end-to-end admitted SQL bag path yet.

SQL NULL exists as `optional<Value>` at the SQL boundary, and the existing
normalizer evaluates comparison-to-NULL and Boolean expressions with SQL
three-valued logic. But every column of each referenced source table must be
declared non-null, even if unused, and NULL-valued row outputs are rejected.
The classical core stores non-null `Value` rows. W04 has a separate nullable
aggregate tuple contract; its NULL grouping and aggregate-argument rules must
remain distinct from general SQL equality.

## Entry points and responsibilities

| Entry points | Already implemented | W05 still requires | Existing evidence |
|---|---|---|---|
| `Refactor.md:333-355,391-397,1321-1324`; `docs/handoff.md:19-26,77-82` | The target is explicit: plain SELECT bags, general NULL/type rules, documented equality versus DISTINCT/grouping, and preservation of set fixtures. Frontend admission must track implemented runtime rules. | Complete the declared W05 SQL behavior and source admission without changing set-mode meaning. | W03/W04 scope limits are stated in `docs/weighted_enumeration.md:3-9` and `docs/handoff.md:19-26`. |
| `include/crown/frontend/parser.hpp:38-40`; `src/frontend/parser.cpp:85-147`; `include/crown/io/sql.hpp:5-7`; `src/io/sql.cpp:4-21`; `include/crown/frontend/bind.hpp:9-42,52-76`; `src/frontend/bind.cpp:135-241,272-346,381-459,476-546` | The parser owns one PostgreSQL 18.6 AST (libpg_query 18.1.0) and syntax diagnostics; the IO form labels parse output `not_checked`. Binding resolves catalog names, aliases, outputs and a bounded typed expression tree. `BoundSql::semantics` defaults to bag; `Binder::select` sets DISTINCT to set and plain SELECT to bag. Types are int32/int64, string, Boolean, date, decimal. Expressions include comparisons, Boolean logic/tests, NULL tests, parameters and restricted casts. FROM is flat catalog relations plus inner/cross joins, ON/USING/NATURAL expansion. | Add only types, casts, operators and expressions whose runtime behavior is defined; keep unsupported syntax diagnostic. Current bounded subset has no timestamp, arithmetic/function execution, general nested SQL, schema-qualified names, outer joins, set operations, ORDER BY or LIMIT. | `tests/unit/binding_test.cpp:87-121` checks bag-vs-set preservation, width promotion, cast/type diagnostics, NULL literals, parameters, EXISTS semantics, and rejection of arithmetic/order/limit/outer join/schema qualification. `tests/unit/admission_test.cpp:50-56` includes timestamp and nullable-source rejection. |
| `include/crown/frontend/normalize.hpp:6-7,56-63`; `src/frontend/normalize.cpp:57-110,234-268,287-312,370-399,429-450` | SQL values and constants can be nullable before the core. Comparisons with NULL produce unknown; predicates keep only TRUE. Local Boolean/NULL tests are evaluated. Ordered and repeated outputs are mapped for admitted set queries. | Admit plain bags through a runtime that carries multiplicity. Define nullable source/output handling and DISTINCT NULL equivalence if nullable rows are admitted. Do not use ordinary equality for SQL NULL. | `tests/unit/normalization_test.cpp:148-177` covers `x = NULL`, OR/Boolean three-valued behavior, NULL outputs, and nullable source rejection. |
| `include/crown/frontend/adapter.hpp:7-28`; `src/frontend/adapter.cpp:9-30,33-68`; `include/crown/ir/model.hpp:16-32,74-88` | The reference SQL adapter routes physical set updates to aliases, evaluates projections/filters, and counts distinct physical rows that collapse to one logical tuple. Its physical database is `Relation = std::set<Row>` and updates are full-row insert/erase events. | Define the admitted bag source boundary and preserve source multiplicity/identity. This adapter cannot represent duplicate identical physical rows as separate source records; it is a set-source adapter. | `tests/unit/normalization_test.cpp:128-146` exercises self-join alias routing and projected support transitions; it is not a raw physical bag test. |
| `include/crown/runtime/weighted.hpp:28-46,141-160,214-236`; `src/runtime/weighted_cursor.cpp:122-135`; `docs/weighted_enumeration.md:5-9,132-140` | W03 maintains exact nonnegative weights on logical native CQ tuples and returns one core tuple plus multiplicity. Its input is `Replacement{NodeId, Row, before, after}`; its cursor has compressed output. | Connect admitted SQL source rows and occurrence adapters to W03 logical weights. W03 itself does not admit SQL, physical bag sources, nullable values, or SQL recovery. | `tests/unit/weighted_bag_test.cpp:67-87` covers duplicate input rows folded to logical weights. `tests/integration/weighted_bag.py:1-6,57-83,112-133` checks every epoch against an arbitrary-precision full-assignment oracle and explicitly excludes SQL/source routing. |
| `include/crown/frontend/aggregate.hpp:13-33,38-76`; `src/frontend/aggregate.cpp:219-236,238-327`; `include/crown/runtime/aggregate.hpp:11-19,47-60,82-105` | W04 binds one flat logical input relation (or no-FROM singleton), grouping by input columns, and COUNT/SUM/AVG. Runtime rows/groups can contain NULL; `COUNT(expr)` skips NULL, grouping distinguishes an absent group from a group with NULL key, and W03 compressed tuples can enter through `apply_weighted`. DISTINCT aggregates reject. | Reuse the existing aggregate NULL and weight behavior where applicable; keep its grouping rules separate from general SQL `=`. W04 has no physical bag-source router or general SELECT frontend and accepts only its admitted aggregate query shape. | `tests/unit/aggregate_runtime_test.cpp:50-96` checks empty global/grouped results, NULL keys/arguments and sufficient statistics. `tests/integration/aggregate_sql_oracle.py:1-9` uses SQLite for W04 GROUP BY/COUNT/integer SUM cases and exact Python `Fraction` for AVG. |

## Existing oracle limits

The W03 arbitrary-precision oracle validates projected multiplicities for direct
logical CQ weights. The W04 SQLite/Python oracle validates the separate aggregate
contract. Neither currently compares general SQL bag rows, nullable-source
equality, DISTINCT NULL grouping, and the supported expression/type subset
against a mature SQL engine. That comparison is part of the W05 acceptance in
`Refactor.md:1321-1324`.
