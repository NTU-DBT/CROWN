# Original SQL aggregate binding

The separate CROWN::sql_aggregate component binds one original aggregate query
to an actual [SQL bag source](sql_rows_runtime.md), an actual
[aggregate kernel](aggregates.md), and an immutable decoder between them.
It supplies compiler metadata. The separate [runtime](sql_aggregate_runtime.md)
coordinates admitted source/tree/group execution. The [Session](sql_aggregate_session.md)
and [JSONL/CLI path](sql_aggregate_input.md) add durable ownership and source
resumption within the [bounded V33 acceptance](verification/human-inspection-v33-2026-11-13.md).
Repository-wide review and release remain open. Existing set-normalization
families retain their meaning.

## Usage and authority

Call frontend::bind_sql_aggregate(sql, catalog, options), or its _into form with
an existing receiving MemoryAccount. A successful SqlAggregateProgram owns the
original SQL, source/kernel programs, physical input origins, decoder, versioned
binding image and identity digests. Diagnostics distinguish original syntax from
derived source, origin and kernel admission. Locations in generated SQL are
cleared rather than presented as byte positions in the original query.

```cpp
auto bound = crown::frontend::bind_sql_aggregate(original_sql, catalog);
if (const auto* program = std::get_if<crown::frontend::SqlAggregateProgram>(&bound)) {
  const auto& source = program->source_program();
  const auto& kernel = program->kernel_program();
  // Metadata borrows the owning program; copy handles to retain it separately.
}
```

Only original SQL/catalog/options enter the factory. The compiler derives a
plain bag SELECT structurally, retaining original FROM/JOIN/WHERE and projecting
needed physical columns. It calls the genuine source factory. A genuine
pre-normalization bind of that exact SQL resolves each physical occurrence and
column; no edited BoundSql or fabricated opaque aggregate descriptor supplies
admission. The rewritten flat kernel then passes the actual aggregate factory.
Original output labels and constant argument types are preserved.

## Group identity and nullable decoding

Physical occurrence, column and complete SqlType identify a kernel input.
Normalized source equality is insufficient: WHERE x=id does not authorize
SELECT x ... GROUP BY id. Different physical columns remain distinct even when
their native payload or constant-NULL slot is equal. Qualified/unqualified names
of the same bound column share one input, including hundreds of repeated uses.

Merged unqualified USING/NATURAL references currently reject explicitly because
their grouping identity needs separate admission. Qualified physical references
follow the real binder. Grouped equal-value columns are retained separately;
decoder fields may therefore repeat without changing their original identity.

Each decoder input contains its original bound origin plus an actual source
payload/presence descriptor or constant ExpressionId. Read presence before a
nullable payload; constant slots come from the source's immutable initial values.
All actual native head fields must be covered. Genuine NULL payloads use the
adapter's unique typed default, so discarding an absent payload cannot merge
distinct genuine native facts. This injectivity is a producer invariant, not
permission for callers to manufacture arbitrary encoded tuples.

## Foreign AST ownership and costs

Original JSON parsing authenticates the SQL before protobuf transformation.
Two independently checked wire decodes create source/kernel trees in one owned
upb arena. Temporary source projections borrow kernel ColumnRef leaves only
through source deparse; source AST use ends before kernel remapping. The pinned
upb deep-copy APIs have unsafe allocation-failure paths and are not called.
One existing shared mutex gates JSON/protobuf/deparse calls into the C parser.

Parsing, JSON, upb/deparser and ordinary binder workspace remain explicit cold
frontend work. They are not all charged by the retained metadata account. Every
retained program array/text/constant uses the supplied compiler account; _into
creates no new cap. Composition, origin binding, source normalization and kernel
binding report separate selected work. Byte/depth/expression limits remain real
child boundaries; increasing an outer limit does not widen those policies.
These counters do not bound every allocator action, comparison or CPU operation.
The compiler adds no update-path instrumentation or result-row mirror.

Receiving failure probes redirect only the actual compiler's first upb arena:
all 8 Debug / 11 sanitizer allocation-denial positions unwind, restore the
receiving account to its controller, and permit same-receiver retry with the
identical binding identity. Other parser arenas, direct libc allocation and
C++ new remain separate mechanisms. The replacement decode path passes these
targeted checks; this is not universal upstream allocation-failure coverage.

## Scope and identity

COUNT/SUM/AVG, their existing exact type/scale policies and column GROUP BY
compose with admitted W05 inner source joins/predicates. Aggregate DISTINCT,
computed/cross-relation arguments, aggregate argument parameters, HAVING,
windows, ordering/grouping extensions and other unsupported clauses reject.
Source predicate parameters retain genuine source admission. Physical integer
columns remain bigint. An aggregate argument may narrow one to SQL integer:
`SUM(x::integer)` returns nullable bigint, while `SUM(x)` and
`SUM((x::integer)::bigint)` return nullable NUMERIC(38,0). The generated source
projects the raw column; the genuine kernel binder retains the cast semantics.
An inner narrowing cast still requires its range check after an outer widening
cast, including a COUNT argument. Raw GROUP BY columns keep their bigint type.

The immutable kernel stores sorted, distinct original column positions requiring
an integer check. Each contributing non-NULL value must fit INT32_MIN..INT32_MAX;
NULL passes. The shared runtime projection checks before changing group state.
These unconditional column/constant/cast arguments permit one check per column
across repeated measures. Conditional/computed expressions remain unsupported.
Foreign-account freeze copies the guard list; durable rebind derives it again
from the authenticated original SQL/catalog recipe.

COUNT(*) may have a nullary source projection. A zero-occurrence source reports
static_source_weight of zero or one, while its kernel starts as a named empty
input. The runtime authenticates and loads that static contribution once at
construction; this compiler does not mutate aggregate state. The separate
[cold rebuild](sql_source_images.md#closed-cold-reconstruction) rebinds durable source metadata before
constructing a receiving runtime.

Family CROWN-SQL-AGGREGATE;2 binds exact original SQL, actual catalog, source,
kernel/schema, decoder/origins, parameter declarations/values and parser archive.
The separate identity digests and exact CBOR binding image support authenticated
rebinding. They provide no checked CROWN tree, minimum-height certificate,
executable importer or durable decision. These composition rules are local
engineering for Refactor W06; no new paper theorem is claimed.
