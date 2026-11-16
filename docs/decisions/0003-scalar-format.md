# Decision 0003: exact scalar domains and document format 2

The catalog extension in [Decision 0004](0004-catalog-contract.md) adds format
3 and extends minimal certificate binding selection while preserving the
formats established here.

Version-1 CQ documents and their certificate bindings retain their original
integer/string/Boolean encoding. Format 2 adds tagged date and decimal values;
readers reject unknown versions and each update must use its document's
format version. Writers retain the input document version and reject an
attempt to encode new scalar types as format 1. No automatic cast or lossy
format downgrade is implemented.

Dates use the finite proleptic Gregorian calendar from 0001-01-01 through
9999-12-31. Decimals use a canonical exact coefficient of at most 38 digits
and scale at most 38. Both domains have exact equality and ordering. Decimal
normalization removes insignificant spelling differences before set identity
or hashing. [scalars.md](../scalars.md) defines the full contract. SQL
`DECIMAL(p,s)` typmods, rounding, arithmetic, timestamps, timezone conversion,
NULL adapters and locale collations require separate admission rules; they
are not inferred from these scalar values.

Stable typed value and row hashes use FNV-1a with fixed little-endian integer
encoding and length-delimited strings. Equal values and rows hash equally.
These hash-table functions do not provide a cryptographic canonical query
identity; F05 remains open.

Structural proof algorithms remain independent of scalar payloads. Their
query binding chooses format 2 for a catalog containing any new scalar type,
and format 1 otherwise. That rule preserves existing primitive certificate
bindings even if a primitive query arrives in a format-2 input document.
Tree and certificate envelopes remain at their existing version 1.

F01 remains in progress until catalog constraint provenance, declared
collations, and the relevant name/type binding diagnostics satisfy its full
acceptance criteria. This decision records the scalar subset, not completion
of the frontend or a release gate.
