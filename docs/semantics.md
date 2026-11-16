# Executable reference semantics (schema versions 1, 2 and 3)

This is the A03/A04 foundation from Refactor.md §16.2. It defines the reference
contract, not completion of R0 or the optimized R1 engine. Admission status is
listed in [sql_support.md](sql_support.md). The normative target and all later
gates remain in [Refactor.md](../Refactor.md).

## Tables, occurrences and values

Every catalog table is a set of **full physical rows**. Row identity is exact
typed value equality across all columns. A duplicate insertion and deletion of
an absent row are no-ops. Catalog identifiers are nonempty, case-sensitive
strings; table, per-table column, variable, and atom-occurrence names are unique
in their respective scopes. A table may have zero columns.

An atom occurrence references a physical table and has exactly one term per
physical column. A term is a variable, typed constant, or ignored column.
Different occurrences, including aliases of one base table and equal/contained
scopes from different tables, remain separate conjuncts. Variables repeated
within one atom require equality between those positions. Constants filter
rows before conjunction. Ignored columns do not bind variables but remain part
of the physical row identity. Deleting one of two distinct full rows projecting
to the same logical tuple leaves that tuple present.

Version 1 admits signed `int64`, `string`, and `bool`. Integer JSON
tokens are checked for signed 64-bit range and never converted through double.
Strings have exact binary equality and lexicographic byte ordering; no locale,
case folding or Unicode normalization is applied. Boolean values are distinct
from integers. Column, variable, and constant types must match exactly. All
physical cells, including ignored cells, are non-null. Version 2 additionally
admits exact finite `decimal` and Gregorian `date` values with explicit tagged
JSON encoding. [scalars.md](scalars.md) defines their ranges, canonicalization,
numeric/chronological ordering, and stable typed hashes. The decimal domain
does not implement SQL `DECIMAL(p,s)` coercion or arithmetic. Separate verified
[annotation policy kernels](annotations.md) provide exact bounded arithmetic
without enabling SQL aggregate/expression execution. NULL,
floating-point tokens (including `1.0`), implicit casts, timestamps and
locale-dependent collations remain rejected. Version 1 keeps its original
type set and serialization; new scalar types require version 2 or 3. Format 3
adds explicit catalog metadata, including fixed decimal precision/scale,
source schema versions and constraints. [catalog.md](catalog.md) defines the
metadata and name/type lookup API. Identity casts preserve both scalar kind
and fixed decimal specification; other casts are explicitly unsupported.

An `enforced` unique key or foreign key is a condition on every committed
database, including tables unused by the query. Initial data and complete
candidate after-states must satisfy those conditions. A violation aborts the
event before database or sequence commit, including a deletion from a
referenced table. There is no automatic cascade. Untrusted declarations,
estimates and key hints never establish a fact or authorize atom elimination.
Standalone catalogs may describe nullable source columns; direct-CQ catalogs
reject them with `unsupported_nullability` pending an explicit adapter. Core
values themselves have no NULL alternative.

## Answers and Boolean queries

Evaluate each occurrence over the same committed physical database. Join
compatible variable assignments, enforce repeated variables/constants, and
project to the ordered head. Insert projected rows into an exact set. Hidden
witnesses cannot create duplicates. Output positions, repeated head variables,
and aliases are independent of the unique head-variable set used by a future
structural planner. Every declared variable must be bound in the body.

An empty head returns either `[]` (false, no tuples) or `[[]]` (true, one
nullary tuple). The empty conjunction is true, with height-zero planning to be
handled separately later. The explicit `contradiction:true` flag gives the
empty answer, including for an empty body. SQL `SELECT EXISTS` output wrapping is specified at the frontend boundary in
[SQL normalization](sql_normalization.md), separately from the core's nullary
relation. This reference-CQ contract does not establish SQL parsing, binding,
admission, allocation, or runtime behavior.

The reference evaluator accepts cyclic and non-free-connex CQs as well. That
is useful oracle coverage and provides no native-engine admission or complexity
guarantee. `validate-cq` checks typing and well-formedness only and explicitly
reports `structural_admission:not_checked`.

## Updates, epochs and failure atomicity

Initial tables represent epoch zero. Initial duplicate full rows collapse
under set semantics. Updates have a schema version, sequence, table, operation
(`insert` or `delete`) and full typed values. Sequence numbers start at 1 and
are contiguous. Every valid event, including a no-op, advances the sequence.
External CDC row IDs, UPDATE/replacement events and strict duplicate errors
remain unsupported here. The A03 reference document format has no window
commands or transaction mode. O03 adds ordered typed library queues and
operational windows, now acceptance-verified. All 79 tests pass in the
five-configuration matrix, including transport/boundary, window/failure and
existing session targeted suites. The prior R06 75-test matrix and source seal
are historical after O03. See the
[O03 verification packet](verification/batches-windows-2026-11-06.md), the
[R06 packet](verification/runtime-initialization-2026-11-06.md), and the
[batch and window guide](batches_windows.md) for their respective records and
contracts.

An array of physical events is ordered transport, with one observable epoch
per element; events are never coalesced. O03 `TransportBatch` preserves the
same per-event physical boundary. Optional R2 atomic net batches are explicitly
disabled, so transport batching adds no transaction or netting semantics.

For each committed physical update:

```
added   = Q(after) - Q(before)
removed = Q(before) - Q(after)
```

Both delta sets are exact, duplicate-free and disjoint. They describe answer
membership rather than witness counts or multiplicities. All self-join aliases
see one after-state, including a new–new combination created by one edge
insertion. There is no intermediate committed alias update.
O03 window commands may expand into zero or multiple physical row transitions;
each actual physical transition still follows this same delta definition.

`reference::Session::apply` validates first, evaluates into temporary database
and output state, then commits by swap. Invalid sequence/type/operation or an
allocation/evaluation exception leaves the database and sequence unchanged.
There is no fixed-width support arithmetic in this evaluator; data values are
not arithmetic accumulators. Sequence overflow is an explicit failure before
commit. Capacity/allocation failures are errors, never wrapped counters or
approximate results.

Reference snapshots and epochs own their rows and remain valid after later
updates or session destruction. There are no borrowed/lazy cursors or concurrent
session access. Future runtime cursors must satisfy D06/O02 rather than inherit
a lifetime guarantee from an unrelated reference container. A caller may drop
any owning reference result without pending liveness work.

The CLI validates the complete document before evaluating and buffers the full
result before writing stdout. Rejected input yields nonzero exit and structured
JSON on stderr. Individual library updates commit separately; a later rejected
event does not roll back earlier successful library calls.

## Copyable exact examples and encoding

For `Q(x):R(x,z)`, insert `(a,1)`, insert `(a,2)`, delete `(a,1)`, delete
`(a,2)`: answer deltas are `+a`, empty, empty, `-a`. For `Q(x):R(x)` with
`R={a}`, inserting `b` emits only `+b`. For `Q(x,y):R(x),S(x,y)` with one
matching witness, deleting that S row emits one deletion. For
`Q(a,b,c):Edge(a,b),Edge(b,c)`, inserting `(u,u)` into empty Edge emits exactly
one `(u,u,u)`. Hand-calculated fixtures live in `tests/regression/`.

Results encode rows as arrays and relations as lexicographically sorted arrays
of unique rows. JSON object keys are sorted on serialization; declaration,
occurrence, head and event array order is retained. Canonicalization is
deterministic for the same document and idempotent. It is not yet an
alias-independent semantic hash or a plan-cache key (F05).

Unknown fields, incompatible versions, duplicate JSON object keys, malformed
rows, undeclared variables/tables, and incompatible types fail explicitly.
JSON nesting has an operational limit of 256, reported as `resource_limit`;
there is no 64-variable or runtime fan-out semantic cap. The reference path
materializes intermediate assignments and before/after outputs. Its time and
memory can grow with witness count; it makes no CROWN maintenance or
constant-delay claim. No durability, sink-delivery or performance claim is made.
