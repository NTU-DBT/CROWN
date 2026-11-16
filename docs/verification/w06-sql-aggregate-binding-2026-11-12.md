# Original SQL aggregate compiler: receiving checks

The separate `CROWN::sql_aggregate` compiler accepts original SQL, catalog and
options, then invokes the genuine source and aggregate binders. See the
[usage and ownership contract](../sql_aggregate_binding.md) and
[source cards](../code_specs/files/src/frontend/sql_aggregate.cpp.md).
This checkpoint verifies compiler metadata; W06 runtime and durable recovery
remain in progress.

The first proposal incorrectly treated normalized value equality as original
column identity. A focused Astra review found that issue, unsafe upstream upb
clone allocation paths, and one missing private UTF-8 include directory. Root
reproduced the grouping defect. The repaired compiler uses genuine
pre-normalization occurrence/column/full-type identity and two checked wire
decodes. It preserves distinct originally ungrouped columns even if WHERE or
join equality makes their normalized payloads equal. Three invalid queries now
reject with `ungrouped_column`; the qualified/unqualified valid control accepts.
The built compiler archive references checked decode, with no direct clone/copy
API references. Original failed evidence remains immutable.

Root executed 15 selected parser, binding, normalization, W04 aggregate and W05
source tests in strict Debug and ASan/UBSan/leak profiles: **15/15 in each**,
58.75 / 106.65 seconds. The test-disabled complete Release build passes. A
relocated 218-file installed SDK and strict C++23 consumer pass. All 327 prior
test commands and execution properties are preserved, excluding line backtraces;
one compiler test brings registration to 328. This is not execution of all 328.

A native allocation probe redirects only the compiler's first upb arena. All
8 Debug and 11 sanitizer denial positions throw, release receiving allocations
to the account controller and permit an identical same-receiver retry. This
does not cover every C parser arena, direct libc allocation or C++ new. Temporary
parser/deparser workspace remains an explicit cold cost outside retained metadata
accounting. The compiler adds no update-path instrumentation or joined-row state.

Root receipts, terminal LastTest copies, exact input cohorts, SDK pins and fault
probe sources live in
`build/verification/w06-sql-aggregate-compiler-implementation-v1`. Its 23 recorder
jobs preserve 21 successes and two expected setup failures. SDK native gates
passed before a separate artifact-index path correction; those outcomes are
retained separately. Current compiler native cohorts pin 1,136 maintained inputs
with no in-command drift. No failed attempt was replaced by its successful retry.

The repair package checksum is
`5ef04d0cb1e90a6a9c9169c36cb1e934f9664d1f1b284495a46dacbd1a3137a9`.
The canonical review adds 95 cards and reconciles 1,409 exact predecessor cards:
1,406 unchanged meanings with reviewed source-hash updates, and three semantic
updates for the common parser gate, installed target set and offline display
roles. The private review ran no native commands; execution claims above belong
to root receipts.

Genuine group-only runtime composition is being tested separately. The first
private fixture was outside CROWN tree admission because its source projected
both join sides without the separator. The receiving fixture now retains that
separator as a hidden grouping key and uses the actual fixed source-work fault
type. Strict private runtime and existing aggregate controls pass after those
test-only repairs. Production postimages are unchanged; sanitizer, independent
joined SQL, maintained adoption and durable integration are still separate gates.
