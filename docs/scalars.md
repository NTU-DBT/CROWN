# Scalar values (F01)

This page specifies the version-2 scalar encodings and the exact date and
decimal value domains. [catalog.md](catalog.md) defines catalog constraints,
column policies and name/cast checking. [SQL support](sql_support.md) states the
admitted binding/expression boundary. Date and Decimal value classes supply
parsing, equality and ordering. Current SQL bags and aggregates have separate
[rows](sql_rows_runtime.md) and [aggregate runtime](sql_aggregate_runtime.md)
contracts. The [annotation policies](annotations.md) specify bounded numeric
payload arithmetic. This scalar contract
covers typed values, set identity, ordering and the reference oracle.

Version 2 keeps the version-1 direct-CQ document shape and adds `date` and
`decimal` to the scalar type set. The root `schema_version` and each update's
`schema_version` are both `2`. The separate
[`cq-v2.schema.json`](../schemas/cq-v2.schema.json) expresses the JSON shape
and lexical forms. The reader is authoritative for token type, value
validation, type matching and references: JSON Schema cannot reliably tell a
JSON integer token from a floating-point token such as `1.0`, validate the
Gregorian calendar, enforce decimal precision and scale, or check that a
tagged value matches its declared column type.

Format 3 keeps these scalar encodings and adds catalog metadata, including an
optional fixed `(precision,scale)` decimal specification. Exact representability
is checked for both physical values and constant terms. Rvalue construction
and assignment preserve valid canonical Decimal values in both objects;
moving its coefficient alone would invalidate the source's scale/sign invariant.

## Typed JSON values

Existing version-1 values retain their forms: signed 64-bit integer JSON
integer tokens, strings, and booleans. Version 2 represents each added value
with exactly one tagged object:

```json
{"date":"2024-02-29"}
{"decimal":"-12.34"}
```

The object must have exactly the one expected key and its value must be a
string. A tagged scalar in an `int64`, `string`, or `bool` column, or a raw
integer/string/boolean in a `date` or `decimal` column, is a type error. JSON
`null` is not a value in any column. JSON floating-point numbers, including
`1.0`, are rejected; decimal input is never accepted as a JSON number and is
never converted through binary floating point. No implicit casts are made.
The same encoding is used in rows, constants, and update values.

Version 1 continues to accept only `int64`, `string`, and `bool`. It rejects
date and decimal column types and tagged values. Canonicalizing a version-2
document retains version 2 and writes canonical scalar spellings. A version-1
document cannot be written with either new scalar type.

## Date

A date is a finite Gregorian calendar day from `0001-01-01` through
`9999-12-31`, serialized as exactly ten ASCII characters in `YYYY-MM-DD`
form. The year has four digits, month and day have two digits, and separators
are ASCII hyphens. Calendar validity is checked, including leap years: 2000 is
a leap year and 1900 is not. Year zero, invalid month/day combinations, BC
dates, timestamps, timezone suffixes, and infinity sentinels are rejected as
`invalid_scalar`. Dates compare in chronological order. Their canonical form
is the same fixed-width spelling.

## Decimal

A decimal is an exact finite base-10 value. Its input grammar is
`[+-]?[0-9]+(\.[0-9]+)?`: an optional ASCII sign, at least one integer digit,
and, if present, a decimal point followed by at least one digit. Whitespace,
exponents, a missing integer or fractional part, and non-ASCII digits are not
accepted. Examples such as `.5`, `5.`, `1e3`, and ` 1.0` are invalid.

Canonicalization removes leading coefficient zeroes, removes trailing zeroes
from the fractional part, omits a plus sign, and writes every zero as `0`.
Examples:

| Input | Canonical spelling |
| --- | --- |
| `+001.2300` | `1.23` |
| `-0.000` | `0` |
| `0001200.00` | `1200` |
| `0.00000000000000000000000000000000000001` | unchanged |

After canonicalization, the coefficient has at most 38 digits and the scale
(fractional digits) is from 0 through 38. Integer zeroes within a nonzero
coefficient count toward its precision; leading zeroes do not. Trailing
fractional zeroes are removed before checking scale. Exact precision or scale
overflow is `scalar_overflow`; a malformed spelling is `invalid_scalar`.
No rounding or truncation occurs. Canonical spellings are unique for equal
values, so aliases compare equal and collapse to one physical set row.
Ordering is exact numeric order, including negative values and fractions;
it does not use lexicographic string order.

## Document and artifact versions

Value and row hashes use stable 64-bit FNV-1a. Each value starts with its
variant tag (`int64=0`, `string=1`, `bool=2`, `date=3`, `decimal=4`). Integers
use eight little-endian bytes after unsigned conversion; negative integers
therefore use their two's-complement representation. A Boolean contributes
one zero/one byte. Strings use an eight-byte length followed by exact bytes,
including embedded NUL. Dates hash signed days from 1970-01-01 using the
integer encoding; decimals hash their canonical text using the string
encoding. Rows start with their length and then encode each typed value.
Equal typed values and rows consequently hash equally. Collisions are
resolved by exact equality; these functions are not cryptographic hashes or
semantic plan-cache identities.

Each update version must match the root document version. Tree envelopes remain
at version 1. Height certificates use version 1 for the original exact algorithm
and version 2 for `crown_partition_exact_v2`. The reader enforces the v1/v2
compatibility rule for that algorithm; independent proof replay validates the
algorithm claim. A parsed version-1 DTO can still contain an unknown algorithm. Query bindings use version 3 for nondefault
catalog metadata, otherwise version 2 when their catalog contains any extended
scalar type, and version 1 otherwise. The version-1 binding representation
remains byte-for-byte canonical for old catalogs.
These envelope and binding rules do not change the scalar JSON encodings.

The versioned schema describes allowed tagged object shapes and decimal/date
lexical patterns. The native reader additionally rejects impossible calendar
dates, out-of-range precision or scale, a tag/type mismatch, raw floating
point, null, unknown fields, and invalid references. It is not accurate to
claim that schema validation alone enforces the full scalar contract.
