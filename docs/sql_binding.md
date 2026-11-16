# SQL binding result (F03)

`crown bind-sql SQLFILE CATALOG.json [PARAMETER_TYPES.json]` parses one SQL
statement, resolves its names against an owned catalog snapshot, checks the
supported scalar types and builds a typed expression-and-occurrence binding.
The output follows
[`sql-binding-v1.schema.json`](../schemas/sql-binding-v1.schema.json).
This is a binding result only. It does not normalize the bound program to a
direct CQ, prove free-connex admission, choose a plan, or execute SQL. Both
successful bindings and binding diagnostics report
`admission_status: "not_checked"`.

F03's stated binding/desugaring acceptance checks pass the complete compiler,
sanitizer and clean-source matrix. [Verification evidence](verification/binding-2026-11-05.md)
records that historical bounded coverage. Later normalization/admission are
defined in [F04](sql_normalization.md) and [F06](sql_admission.md).

The parser is the pinned PostgreSQL 18 parser described in
[`sql_parser.md`](sql_parser.md). The binder requires exactly one nonempty
statement. Source locations are zero-based UTF-8 byte offsets; diagnostic
character positions and line/column fields use the conventions in that parser
contract. The bound result owns its source, catalog snapshot, expressions,
occurrences, predicates, and outputs. It retains table occurrences and SQL
output positions; it is not a CQ-normalized form.

## Binding and name scope

The catalog input uses the standalone version-1 catalog document. Catalog
table order is retained in `catalog_binding`; `table_id` refers to the
zero-based table position in that snapshot. Each table reference receives a
distinct occurrence even if another occurrence names the same base table.
An explicit relation alias is the visible qualifier for that occurrence and
hides the base table name. Unqualified references must resolve uniquely;
unknown and ambiguous names are diagnostics.
The catalog currently uses one global table-name scope; SQL catalog/schema
qualifiers are not implemented.
Unquoted SQL identifiers follow PostgreSQL's lowercase folding before catalog
lookup; quoted identifiers retain their exact spelling.

The successful result marks `catalog_inheritance: "none"`: catalogs here are flat
physical relations and do not describe PostgreSQL table-inheritance edges.
Each occurrence still records the SQL scan request as `include_descendants`.
It is `true` for an ordinary `FROM table` reference and `false` for
`FROM ONLY table`. PostgreSQL normally scans descendant tables for a parent
table reference unless `ONLY` is specified ([PostgreSQL 18 table references](https://www.postgresql.org/docs/18/queries-table-expressions.html)).
Because this catalog has no inheritance hierarchy, either request binds to
the one declared relation in this F03 result; the flag preserves SQL intent
for a later adapter. Importers must not treat this flat binding catalog as a
PostgreSQL server inheritance catalog or expand descendants from it. The flag
does not change SQL `bag`/`set` semantics.

`JOIN ... ON` resolves names in the two joined inputs. A preceding comma item
does not become visible to an `ON` clause just because it appears earlier in
the `FROM` list; PostgreSQL gives `JOIN` tighter binding than comma. The binder
keeps those scopes distinct. PostgreSQL's table-expression rules also define
that `USING` emits the listed merged columns first, then the remaining left
columns, then the remaining right columns; the bound occurrence data retains
the physical references needed for qualified names. `NATURAL` derives a
`USING` list from the common input names. These rules follow the PostgreSQL 18
[`FROM` and join rules](https://www.postgresql.org/docs/18/queries-table-expressions.html).

Output entries retain select-list order, aliases, and repeated expressions.
Repeated output columns are not coalesced. `USING`/`NATURAL` merge only the
unqualified joined-table view; a qualified reference remains tied to its
physical input occurrence. Occurrence column names include any explicit
column-name list on a relation alias; expression column indexes continue to
identify positions in the bound occurrence.

## SQL forms in this binding subset

The binder records whether the request asks for SQL bag semantics or set
semantics. A plain `SELECT` remains `bag`; `SELECT DISTINCT` is `set`. It does
not silently insert `DISTINCT`. A top-level `SELECT EXISTS (...)` is recorded
with the `exists` wrapper and its output alias. PostgreSQL defines `EXISTS` by
whether the subquery returns at least one row; it is a Boolean wrapper around
the inner query, not a CQ nullary result row. See the PostgreSQL 18
[`EXISTS` definition](https://www.postgresql.org/docs/18/functions-subquery.html).
For an EXISTS wrapper, `requested_semantics` records the outer SELECT's mode
and `inner_semantics` records the inner SELECT's mode.

The initial expression subset includes column references, literals,
positional parameters, scalar comparisons, `AND`/`OR`/`NOT`, `IS [NOT] NULL`,
and Boolean `IS [NOT] TRUE`, `FALSE`, and `UNKNOWN` tests. `WHERE` and `JOIN
... ON` conditions remain separate predicate expression IDs. The binding IR
does not apply three-valued predicates as if they were ordinary C++ booleans.

Joins supported for binding are comma/cross joins, inner joins with `ON`,
`USING`, and `NATURAL`. `*` and `alias.*` expand in the current visible column
order. The top-level `EXISTS` form is a whole-result wrapper with one
`EXISTS (SELECT ...)` target and no outer `FROM` or `WHERE`; the inner select
list is still bound, and an absent alias defaults to `exists`. Outer joins,
grouping and aggregates, `DISTINCT ON`, ordering, limits, set operations,
CTEs, and nested subqueries are outside this initial subset. Unsupported SQL
returns a binding diagnostic; parser success does not imply support.

Arithmetic and function calls are not yet bound. This expression IR is a
bounded input for later F04 local-predicate handling. F03 binding does not
declare those predicates safe for direct-CQ normalization or runtime use.

## Types, casts, nulls, and parameters

Each expression carries a `SqlType`: `unknown`, `int32`, `int64`, `string`,
`bool`, `date`, or `decimal`, a nullability bit, and an optional fixed decimal
precision/scale. String collation is binary. Decimal precision and scale
remain part of type identity.

Catalog nullability is preserved in binding. Nullable catalog columns can be
bound, but the direct-CQ core rejects a catalog containing any nullable
column until an explicit SQL adapter accounts for SQL `NULL`. A `NULL`
literal is represented at the SQL boundary and is not a `crown::Value`.
Binding a nullable or NULL-bearing expression does not mean it can enter the
classical non-null reference evaluator.

Casts are explicit binding nodes. Identity casts preserve the full type,
including integer width and decimal precision/scale. A literal cast is
accepted only when that literal can be validated exactly as the target type.
The implemented literal casts cover exact string/date/decimal/integer
validation and identity literals; fixed-decimal casts also have to fit their
precision and scale without rounding. An `int32` integer literal can be
widened to `int64` with an explicit widening node when it is compared with an
`int64` expression. A narrowing cast of a column, or an implicit conversion
between unrelated types, is unsupported; the binder does not erase a cast or
reinterpret the referenced value. Other implicit casts, locale-aware
collations, and representation-changing casts are not introduced.

Parameters use PostgreSQL positional spelling (`$1`, `$2`, ...). When any
parameter is used, pass `PARAMETER_TYPES.json` with schema version 1 and a
`parameters` array in positional order. Each entry declares a canonical
catalog scalar type (`int64`, `string`, `bool`, `date`, or `decimal`), with
optional nullability (default false), binary string collation, and decimal
precision/scale. Collation can be declared only as `binary` on string
parameters. A decimal specification is accepted only on a decimal parameter
and has precision 1 through 38 and scale 0 through precision. Parameter names
are not accepted. A reference without a declaration is an error; the bound
output includes the inferred positional parameter types.
Parameter numbers in expression nodes are one-based, while expression IDs are
zero-based. The input shape is exposed as the
[`parameter_types_document` definition](../schemas/sql-binding-v1.schema.json#/$defs/parameter_types_document)
in the binding schema.

The success result groups expressions as a dense ID-indexed list. Every node
has its SQL type and optional source location, then one discriminator:

| Expression kind | Payload | Meaning |
| --- | --- | --- |
| `column` | occurrence ID and physical column index | A resolved physical reference |
| `literal` | A typed scalar value or SQL `null` | A checked literal; dates and decimals use tagged strings |
| `parameter` | One-based parameter number | A declared positional parameter |
| `operation` | Operator name and argument expression IDs | Comparison, Boolean/null test, cast, or merged `USING` value |

The exact machine-readable fields and operator names are specified by the
versioned output schema. Catalog bindings use the independent
[`catalog-v1.schema.json`](../schemas/catalog-v1.schema.json) contract.

## Bounded work and status

`limits` reports the applied binder bounds: a work limit of 1,000,000 steps,
an expression limit of 100,000 nodes, and recursion depth 128 by default. The
parser also applies its 1 MiB source and 256-level AST bounds. These are
operational limits, not a semantic variable or atom cap. A larger query is
rejected with a structured diagnostic; the binder does not return a partial
query as if it were complete.

## Result shape and diagnostics

Every result has `schema_version: 1` and `admission_status: "not_checked"`.
A successful result has `binding_valid: true`, the original `source`, a
canonical standalone version-1 `catalog_binding` with catalog defaults
materialized, `catalog_inheritance: "none"`, `requested_semantics`,
`inner_semantics`, `result_wrapper`, `wrapper_alias`, inferred `parameters`,
`occurrences`, `expressions`, `predicates`, `outputs`, `limits`, and `work`.
`inner_semantics` is null for a `rows` result and is the inner SELECT's
`set`/`bag` mode for an `exists` result. `requested_semantics` records the
outer SELECT mode. The `exists` wrapper's `outputs` are the bound inner select
list; they do not replace the Boolean wrapper result.

Occurrences identify the table name and catalog `table_id`, visible alias,
visible column names, source location, and the `include_descendants` scan
request. Expression IDs and occurrence indexes are zero-based; parameter
numbers are one-based. Every expression
records its `SqlType`, a byte `location` or null, and one node kind. A column
node has occurrence and physical column indexes, a literal has its tagged
scalar value or JSON null, a parameter has its number, and an operation has
an operator name and argument IDs. Predicate IDs include SQL `ON`/`WHERE`
conditions and equality predicates synthesized from `USING`/`NATURAL` joins.
Output entries preserve select-list order and names.

`limits` reports the work bound (or null when unlimited), expression bound,
and recursion bound; `work` is the steps consumed. Exact property names,
operator names, tagged scalar forms, and allowed extra fields are defined by
the result schema.

A binding diagnostic has `binding_valid: false`, a top-level `phase` (`syntax`,
`catalog`, `parameters`, or `binding`), and a nested `diagnostic` with the
existing SQL diagnostic fields: `code`, `message`, `byte_offset`,
`character_position`, `line`, and `column`. Coordinates are null when there is
no source location. A binding result, including a source syntax diagnostic,
is printed as JSON on stdout; CLI exit status is 0 for a valid binding and 1
for a binding diagnostic. Failure to read or validate the catalog or optional
parameter file is a CLI input error instead, reported as structured JSON on
stderr with exit status 2.

`binding_valid: true` means name resolution and the implemented binding checks
succeeded. `admission_status` remains `not_checked` in both cases. Direct-CQ
normalization is a separate [F04 boundary](sql_normalization.md); SQL semantic
admission is a separate [F06 check](sql_admission.md). Binding does not execute a
query; the separately implemented maintained path is described in the
[CLI and public API guide](cli.md).
