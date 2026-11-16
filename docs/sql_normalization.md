# SQL normalization and occurrence adapters (F04)

F04 is verified at the bounded normalization/adapter boundary. Its original
[verification packet](verification/normalization-2026-11-05.md) records the
finite evidence and all 19 tests passing across the compiler/sanitizer/clean
build matrix. [Schema evolution](schema_evolution.md) defines the complete v1
program readers/validators and migration policy; [query identity](query_identity.md)
defines canonical semantic/output/cost/cache hashes.
The later [F06 packet](verification/admission-2026-11-05.md) records grounded
format 2, preserved v1 replay and the current 23-test matrix.

F04 follows [SQL binding (F03)](sql_binding.md). Binding owns the parsed
statement, catalog snapshot, occurrence identities, typed expressions,
predicates, outputs, and parameter declarations. Normalization specializes
that bound program, forms a direct equality CQ plus local occurrence adapters,
and preserves SQL output behavior. It does not check free-connex admission,
construct or certify a CROWN plan, or claim execution by a maintained runtime.
See [Refactor.md](../Refactor.md) §§2, 11.2 for the wider product and task
contracts.

The source catalog is flat. The F03 `include_descendants` scan request is
preserved as binding intent; it does not expand relations through PostgreSQL
inheritance.

## Command and inputs

```text
crown normalize-sql INPUT.sql CATALOG.json [PARAMETER_TYPES.json [PARAMETER_VALUES.json]]
```

`CATALOG.json` is the standalone version-1 flat catalog described in
[catalog.md](catalog.md). `PARAMETER_TYPES.json` uses the F03 version-1
`parameter_types_document`; it is needed when the statement refers to
positional parameters. `PARAMETER_VALUES.json` specializes those parameters
for this normalization. Its document shape is:

```json
{"schema_version":1,"values":[27,{"decimal":"12.5"},null]}
```

Each array position corresponds to the same one-based `$n` parameter position
in the type document. Values use the declared parameter type and the scalar
encodings in [scalars.md](scalars.md): integer JSON tokens, exact strings,
JSON booleans, tagged dates and decimals, or JSON `null`. A null value is
valid only when that parameter is declared nullable. Array length, value
type, nullability, and exact scalar bounds are checked; floating-point JSON
numbers and implicit conversions are not accepted. When the statement has no
parameters, omit both parameter files. A values file requires its matching
type file.

The parameter values specialize the normalized program. Changing one
requires a new normalization and a new `AdapterState`; an existing state does
not support rebinding parameter values. This keeps predicate results,
constant reductions, and any derived outputs tied to the same specialization.

The command reports a normalized program as JSON on success (exit 0). Parser,
binding, normalization and bounded-work diagnostics are JSON on stdout (exit 1). Usage,
file, catalog, and parameter-document configuration errors are JSON on stderr
(exit 2). An internal parser/binding/normalization invariant failure is reported
on stderr (exit 3), with no partial normalized program. The
[version-2 program schema](../schemas/sql-normalization-v2.schema.json) defines
the current producer; format-1 replay remains supported unchanged. The native reader additionally replays complete binding and
normalization, rejecting any artifact that differs from its owned source,
catalog, parameter specialization and emitted program.

## Equality CQ normalization

The source catalog is flat. Each bound `FROM` item remains a distinct atom
occurrence, identified by its occurrence ID even when two items refer to the
same physical table. Normalization creates one core atom per occurrence and
retains the ordered route from each base table to all its occurrences. Equal
or contained scopes, repeated aliases, and self-joins are not removed by
scope containment or by physical table identity.

Equality classes use `(occurrence ID, physical column index)` as column
identity. Before unioning any columns, normalization checks the bound operand
types, explicit casts, nullability, and any supported lossless widening. A
cast is not erased merely because the core has a coarser scalar representation;
type width and decimal precision/scale remain relevant. Only a direct,
unconditional column equality may add a cross-occurrence equality class. An
equality beneath `OR` or `NOT` is not unconditional and cannot become a CQ
edge. Equality of columns from the same occurrence becomes a row-local check
on that occurrence. Constants and specialized parameter values are checked
exactly and remain filters or constant results; a SQL `NULL` never becomes a
classical `crown::Value`.

Format 2 also propagates a final class constant to every physical column in
that class, including other aliases. Explicit `constant_columns` guards run
before projection. Fixed variables leave the core scopes/head and ordered
outputs use their constant values. For example, `Q(1,z): R(1,y),S(y,z)` has
free set `{z}`, with both mutable atoms retained. This prevents a fixed head
column from creating a false free-connex obstruction. Version 1 keeps its
original geometry for exact replay; admission upgrades it to version 2.

The local predicate subset is scalar comparison and Boolean/NULL testing over
expressions whose column references all belong to one occurrence (or none).
It uses SQL three-valued logic. `WHERE` and `JOIN ... ON` retain a row only
when the predicate is `TRUE`; `FALSE` and `UNKNOWN` both filter it out.
Boolean composition such as `AND`, `OR`, and `NOT`, plus the bound `IS [NOT]
NULL` and Boolean truth tests, follows that same logic. An unconditional
direct column equality is handled by equality normalization; cross-occurrence
non-equality comparisons and Boolean expressions that depend on multiple
occurrences are rejected by this contract rather than evaluated as local
filters. Arithmetic and function calls remain outside the F03 expression
subset.

Each occurrence adapter checks local predicates and repeated-column
equalities against a full physical row, evaluates its bounded local expression
program, and projects the values needed by that occurrence's core atom. A
repeated variable within one atom therefore requires equal physical column
values. Unused physical columns are still part of full-row identity even when
they do not enter the core projection.

## NULLs, output mapping, and SQL row semantics

The classical core has no NULL value. Every column in a referenced physical
source table must be declared non-nullable. If a referenced table contains a
nullable column, normalization rejects it even when that column is unused by
the statement. The same source rule applies inside `EXISTS`.

NULL literals and nullable specialized parameters may be used in local filter
logic, where they produce ordinary SQL `UNKNOWN` results as appropriate.
They may not produce a nullable SQL row output: constant outputs are checked
after specialization, and nonconstant outputs must have a non-null bound SQL
type. The initial normalizer does not refine nonconstant nullability using
filters or specialized Boolean operands. Nonconstant computed row
outputs are admitted only when their column dependencies are confined to one
occurrence and the expression is in the bounded local subset. A computed
output that depends on multiple occurrences is rejected. Constant outputs,
core-variable outputs, output names, SQL types, select-list ordering, and
repeated output positions are retained by the SQL output mapping even when
equality normalization merges core variables.

The local Boolean and comparison behavior follows the PostgreSQL 18
[logical operators](https://www.postgresql.org/docs/18/functions-logical.html)
and [comparison predicates](https://www.postgresql.org/docs/18/functions-comparison.html)
contracts. These are semantic references, not additional build dependencies.

Plain row-producing `SELECT` requests bag semantics and is rejected; the
normalizer does not insert `DISTINCT` or silently change the request. A
`SELECT DISTINCT` row query uses set semantics. A whole-result `SELECT
EXISTS (...)` is treated separately: its inner query may be marked `set` or
`bag`, because the wrapper observes only whether any row exists. Inner select
list values are ignored, and the SQL wrapper returns one Boolean scalar row,
`FALSE` for an empty core result or `TRUE` for a nonempty one. That scalar
wrapper is separate from the core's nullary relation, whose values remain no
tuple or one empty tuple.

## Projection supports and physical update routing

Projecting full physical rows into an occurrence can map different physical
rows to the same logical core row. Each occurrence therefore keeps a support
count keyed by its full logical row. A physical row contributes one support;
the logical set row is present while its support is positive. Removing one
physical row does not remove a projected logical row while another distinct
full physical row still supports it. No unused source column is discarded
from physical row identity.

`AdapterState` owns the specialized normalized program, the physical
database, occurrence-level logical relations, and those support counts. One
public physical update routes to every occurrence of its base table in stable
occurrence-ID order. Candidate physical state, all affected aliases, and
their support changes are prepared together and become visible as one
copy-commit; no intermediate alias state is observable. Catalog-enforced
constraint failures leave the physical state, all logical occurrence state,
supports, and sequence unchanged. Valid set updates, including duplicate
inserts and absent deletes, follow the reference event policy: they are
no-ops on rows but still consume one committed sequence number.

This adapter boundary is not the maintained join runtime. It defines how one
physical source row is normalized per occurrence and how aliases share a
physical event; it does not promise query delta enumeration, cursor behavior,
recovery, or a CROWN update bound.

## Implementation and cost

The compiler owns ordinary temporary containers, separate from the native query
memory account. It copies the complete binding, catalog, source and specialized
parameters before its first work charge. The work limit counts selected steps;
catalog validation, every container allocation and all copying are not covered
by that counter. Dependency sets, union-find paths and ordered maps also have
their actual size-dependent costs. These frontend limits are not a total CPU,
memory or RSS cap.

`adapt_row` validates a full source row, checks fixed/repeated-column guards,
copies the query-wide constant-expression slots, evaluates its local program
and copies the projected cells. Its work therefore includes the complete
constant-slot vector even when the selected projection is narrow. SQL result
mapping copies ordered outputs into a set; the whole-result `EXISTS` wrapper
constructs one Boolean row from core emptiness.

`AdapterState` is the independent correctness reference. Each update copies the
complete physical, logical and support collections, including valid set no-ops,
and checks candidate database constraints before committing by swaps. Candidate
owners provide cleanup without a catch/rethrow wrapper. This simple transaction
does not have the native maintained runtime's update bound. Its member getters
borrow the owner, and later commits replace collection contents; callers needing
a historical snapshot must own their copy.

## Verified bounded coverage

The unit and SQL fixtures exercise the following F04 contract. Exact commands,
fixture counts and limits are recorded in the verification packet:

- Direct unconditional equalities form typed classes; repeated columns are
  checked within their occurrence. Equality under `OR` or `NOT` does not form
  a class. Cast, type-width, decimal-specification, and NULL checks happen
  before any merge.
- Same-table aliases and equal or contained occurrence scopes remain
  separate atoms. Routing lists every occurrence in a deterministic order.
- Local predicates cover comparison, Boolean composition, and NULL/Boolean
  tests under three-valued logic, including a NULL literal or nullable
  parameter. Only `TRUE` passes a filter; nullable row outputs and
  cross-occurrence computed outputs are rejected.
- Plain bag row queries are rejected; `DISTINCT` rows and Boolean `EXISTS`
  are distinguished. An inner bag `EXISTS` query ignores inner output values
  and still maps to the scalar Boolean wrapper.
- Multiple full physical rows that project to one occurrence row keep that
  logical row alive until its final support is removed. A physical update to
  a self-join table updates every alias atomically. A constraint failure
  leaves state and sequence unchanged.
- Parameter values are validated against positional type declarations and
  require a new normalized program/state when changed. CLI success,
  diagnostic, configuration-error, and internal-invariant-failure paths
  follow the documented exit channels.

SQL and independently handwritten CQ paths agree under A04's reference
semantics, including 576 seeded self-join update comparisons. Seventeen SQL
success cases, seven diagnostics and four CLI errors pass, with 16 applicable
SQLite crosschecks. This evidence does not establish maintained runtime bounds
or integrated SQL admission.
