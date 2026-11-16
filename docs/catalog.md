# Catalogs and column metadata (F01)

This page describes the versioned catalog formats, typed column metadata, and
the checks used by the current reference core. F01 is verified at this API
boundary; [catalog evidence](verification/catalog-2026-11-05.md) records its
acceptance checks. This
page does not define SQL binding or query admission, which are later frontend
steps, and it does not authorize a rewrite.

## Standalone catalog and embedded catalog

A standalone catalog has its own envelope:

```json
{
  "schema_version": 1,
  "catalog": {
    "version": 8,
    "tables": [
      {
        "name": "orders",
        "columns": [
          {"name": "order_id", "type": "int64", "nullable": false},
          {"name": "amount", "type": "decimal", "decimal": {"precision": 12, "scale": 2}},
          {"name": "label", "type": "string", "collation": "binary"}
        ],
        "source_schema_version": 3,
        "constraints": [],
        "statistics": {"distinct_counts": []},
        "key_hints": []
      }
    ]
  }
}
```

The strict shape is defined by
[`catalog-v1.schema.json`](../schemas/catalog-v1.schema.json). Its
`schema_version` is always 1. The embedded `catalog` object is the payload
used by CQ document version 3 and has the same catalog schema.

There are three independent version numbers:

| Field | Meaning |
| --- | --- |
| Root `schema_version` | The standalone catalog envelope version (1), or the CQ document format (1, 2, or 3). |
| `catalog.version` | The caller's version for the logical catalog. It must be a positive unsigned 64-bit integer. |
| `table.source_schema_version` | The source system's schema version for that table. It is independent of `catalog.version` and defaults to 1. |

Typed table/column IDs are scoped to their catalog version. The catalog owner
must advance `catalog.version` when the schema changes; reference sessions own
their catalog copy. No online schema migration is implemented.

CQ format 3 keeps the query, variable, atom, head, row, and tagged-value forms
from CQ format 2. Its root `schema_version` and every update's
`schema_version` are 3, and its embedded catalog accepts the metadata described
here. Variables remain `{ "name", "type" }`; physical catalog metadata is not
copied into logical variables. The shape is specified in
[`cq-v3.schema.json`](../schemas/cq-v3.schema.json). Existing CQ format 1 and
2 documents keep their old catalog shape and scalar/version rules.

## Columns and scalar types

Columns require nonempty `name` and `type` strings. Names are case-sensitive.
Within a table, names must be unique. The supported types are `int64`,
`string`, `bool`, `date`, and `decimal`; the exact scalar encodings and generic
value domains are in [scalars.md](scalars.md).

| Metadata | Allowed form | Meaning |
| --- | --- | --- |
| `nullable` | Optional Boolean; defaults to `false` | Whether the source column may contain SQL NULL. A standalone catalog can describe nullable source data. The direct-CQ core rejects a query catalog if any declared column is nullable, with `unsupported_nullability`, until an explicit adapter proves the needed non-null condition. JSON `null` is still not a core value. |
| `collation` | Optional `"binary"` on `string` columns only | String identity and ordering use exact bytes. Locale collations, case folding, and Unicode normalization are not implemented. A different collation, or a collation on a non-string column, returns `unsupported_collation`. |
| `decimal` | Optional `{ "precision": P, "scale": S }` on `decimal` columns only | Declares fixed decimal bounds: `1 <= P <= 38` and `0 <= S <= P`. Missing metadata leaves the generic exact `Decimal` domain in effect. |

The generic decimal value domain has a canonical coefficient of at most 38
digits and scale 0 through 38. A fixed specification accepts a value only when
it is exactly representable at `(P,S)`; values are never rounded or truncated.
For example, `12.3` is representable at `(4,2)` as a value with a scale of at
most two, while `12.345` is not. Decimal equality compares canonical numeric
values, so columns with different compatible `(P,S)` specifications can join
without converting stored values. Each value must still fit its own column's
specification. An explicit cast that changes the fixed `(P,S)` specification
is rejected. The fixed specification does not add SQL arithmetic,
aggregation, or implicit casts. A value that does not fit fails with
`scalar_overflow`.

## Constraints

`constraints` is an optional array, defaulting to empty. Constraint names must
be nonempty and unique within a table. The format has two tagged forms:

```json
{"kind":"unique","name":"orders_pk","columns":["order_id"],"status":"enforced"}
```

```json
{
  "kind":"foreign_key",
  "name":"orders_customer_fk",
  "columns":["customer_id"],
  "status":"untrusted",
  "references":{"table":"customers","columns":["id"]}
}
```

Only these constraint fields are accepted. Column arrays contain distinct
names that resolve in their containing table. Empty arrays are permitted: an
enforced unique constraint on `[]` allows at most one row, and an enforced
foreign key on `[]` requires a referenced row whenever the source has a row.

Foreign-key source and target arrays must have equal arity, and corresponding
columns must have the same scalar type. An `enforced` foreign key must refer to
the same column set as an `enforced` unique constraint on the target table;
column order does not matter for this target-set check. Both forward and
backward table references are allowed because tables are resolved after all
table declarations have been read.

`enforced` declarations are checked against data when the native constraint
validator receives a database. Enforced unique keys must contain no duplicate
projected rows, and every enforced foreign-key value must exist in its target.
The reference session validates its initial database and each candidate
after-state before committing an update. Violations return
`constraint_violation`. `untrusted` declarations still
require valid names, columns, arity, scalar types, and table references, but
they do not assert that data satisfies the constraint. They never authorize a
rewrite. The same rule applies to metadata hints below.

## Statistics and key hints

`statistics` is optional and accepts an optional unsigned 64-bit `row_count`
and an optional `distinct_counts` array, which defaults to empty. Each distinct
count has a unique-column-set `columns` array and an unsigned 64-bit `estimate`;
the estimate may be zero. There may be only one estimate for a column set,
regardless of the order used to write that set. Statistics are estimates, not
constraints. The reader validates their field shapes and column references but
does not check their truth against table contents or use them to change query
semantics.

`key_hints` is an optional array, defaulting to empty. Each item requires a
distinct `columns` array and a nonempty `reason`. A hint records caller
knowledge without asserting uniqueness. Hints do not enforce data properties
and cannot enable a semantic rewrite or query-admission decision.

## Validation and canonical writing

The native reader rejects unknown or duplicate JSON object fields, wrong field
types, empty or duplicate table/column/constraint names, invalid metadata
combinations, unresolved column/table references, duplicate columns within a
key, incompatible foreign-key types or arities, and an enforced foreign key
without an enforced unique target. JSON Schema checks the nested shape and
basic ranges; native validation is authoritative for names, cross-references,
exact integer tokens, type matching, and data constraints.

`read_catalog` parses the standalone envelope. `read_catalog_payload` handles
the embedded version-3 payload. `write_catalog` and `write_catalog_payload`
write canonical forms. Canonical tables include `source_schema_version`,
`constraints`, `statistics` with `distinct_counts`, and `key_hints`; the
statistics object includes `row_count` only when it is present. Canonical
columns include `nullable`, and string columns include `collation: "binary"`.
An optional decimal specification is written when present. Array declaration
order is preserved.

CQ format 3 is preserved when a version-3 document is serialized. A v1 or v2
writer cannot discard nondefault catalog metadata; it rejects such a value
instead. Nondefault metadata includes a source schema version other than 1,
`nullable: true`, a fixed decimal specification, any constraint, a present
row-count estimate, any distinct-count estimate, or any key hint. Explicit
default values such as `nullable: false`, `collation: "binary"`, an empty
constraint/hint/estimate list, and source version 1 do not require format 3.
When a query binding is constructed for a height certificate, it uses the
minimal compatible format: v3 for nondefault catalog metadata, else v2 when
any column uses `date` or `decimal`, else v1. This keeps old primitive
bindings canonical while ensuring metadata participates in certificate
binding.

## Name lookup and current limits

Catalog and column lookups use exact, case-sensitive names. A table binding
provides its visible qualifier; self-join bindings remain distinct. An
explicit relation alias hides the base table name. An unqualified name that
matches multiple visible bindings returns `ambiguous_column`; unknown table,
qualifier, or column references are also errors.

The initial cast boundary permits identity casts only, preserving declared
nullability as well as scalar kind and decimal specification. An identity
cast cannot establish non-nullness; an explicit adapter must do that.
A cast between different scalar types returns `unsupported_cast`; metadata does not imply an
implicit conversion. Catalog declaration errors use `invalid_catalog` or
`unsupported_type`/`unsupported_constraint` for unknown types or constraint
kinds. Malformed documents and unknown JSON fields use `invalid_document`, and
unsupported format versions use `unsupported_version`.

The CLI entry points are `crown validate-catalog CATALOG.json` and
`crown canonicalize-catalog CATALOG.json`. They validate or serialize a
catalog without binding SQL. SQL parsing, catalog binding, equality-CQ
normalization, structural admission, and runtime planning remain separate
steps. No catalog constraint, estimate, or key hint by itself admits a SQL
query or proves a query rewrite safe.
