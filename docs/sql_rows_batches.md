# Prepared SQL source net batches

This W06 component prepares one atomic physical-source net command against the
actual frozen SqlRowsProgram and source ledger. It preserves the separate
single-row apply API and its immediate constraint checks. Aggregate coordination
uses the separate [original-SQL runtime](sql_aggregate_runtime.md); its
[Session](sql_aggregate_session.md) and [input/CLI path](sql_aggregate_input.md)
provide durable terminal outcomes, recovery and physical batch admission.
See the [task ledger](task_ledger.md) and [single-row contract](sql_rows_runtime.md).

## Usage and visibility

A sql_rows::NetBatch carries one next contiguous sequence and a borrowed span of
SourceReplacement values. Each replacement names a bound source TableId, the
complete nullable physical row, its expected before weight and its after weight.
It is distinct from an ordered transport batch: only its consolidated final
state is admitted, staged or published.

Call prepare_batch(batch, DeltaCapture::enabled) to prepare source/key changes
and genuine native projected deltas, or omit capture for the default disabled
mode. Preparation completes validation, funding and native arithmetic before
returning a move-only PreparedBatch. Then inspect the borrowed program, native
preview or encoded native delta span as needed, and commit or roll back.
Destroying or overwriting an active token rolls back through the existing native
epoch. No separate SQL undo framework is installed.

```cpp
namespace rows = crown::runtime::sql_rows;
namespace weighted = crown::runtime::weighted;
const std::array edits{rows::SourceReplacement{source, complete_row, before, after}};
auto prepared = runtime.prepare_batch({next_sequence, edits}, weighted::DeltaCapture::enabled);
// Copy any preview data needed after this active token closes.
auto epoch = prepared.commit();
```

Input cells and string bytes need survive only until prepare_batch returns.
The token retains its original SQL owner if the facade moves or is destroyed.
Program/preview references and delta spans borrow the active token and expire
at commit, rollback or destruction. source_work returns consumed counters by
value; it does not expose or refill an allowance. No additional native staging
method is exposed by this source token.

While preparation is private, ready is false. apply, prepare_batch, results,
root_weight and source_weight reject private state. Immutable program metadata,
committed sequence and explicit account diagnostics remain inspectable. A closed
or moved-from token rejects operations with invalid_sql_rows_batch; rollback is
nonthrowing and idempotent. Calls on one owner must remain serialized.
Explicit commit and rollback immediately destroy the token's backing Data and
native workspace. An empty closed facade can still retain its fixed allocator's
MemoryAccount handle; it does not retain proposal maps or pending vector capacity.

Commit returns source-change status, consumed source work and one committed
weighted Epoch. Source changed means at least one consolidated physical row
weight changed, including rows filtered from all occurrences. Canceled chains
can therefore produce changed=false. A changed source batch can have an empty
projected output net. An empty batch still commits its contiguous epoch.

## Expected chains and final constraints

Every row is validated against its real source schema. The first expected
weight for a complete (source,row) key must match the committed source ledger.
Later edits of that same key must match its latest proposed weight, including
no-op links. Only the final weight is checked against the configured source cap.
An unpublished intermediate chain weight may exceed that cap and then cancel.

Two private ordered maps retain touched source rows and touched constraint keys.
Borrowed probes avoid constructing owning lookup keys. Existing committed Tuple
handles are shared; only new keys freeze descriptors/string bytes. Nontrivial
chains that cancel may retain a touched proposal until the token closes. No
source table, full result bag or complete group map is copied or scanned.

Constraint shares are removed before any are added. UNIQUE counts complete row
multiplicities; FK reverse counters count presence of each distinct full row.
NULLS DISTINCT and MATCH SIMPLE omit a projected key containing any NULL. An
empty column list produces a present empty key, not NULL.

All affected counters exist before final validation. A positive final FK share
requires a positive final parent. Final UNIQUE count is at most one; if a parent
key becomes absent, every referenced child counter is checked against touched
final values or the untouched committed index. This supports final-valid key
swaps and self/cyclic changes regardless of input order while still rejecting
untouched children whose parent is removed.

## Native staging and publication

Detached destination-map nodes are funded before native mutation. The actual
compiled occurrence adapter then stages every source decrease across all aliases,
followed by every increase, inside one Weighted PendingEpoch. Each stage drains
under its original retained native allowance. Decreases-first avoids false
transient multiplicity overflow for a positive query; actual out-of-range final
native counts still reject. DISTINCT/EXISTS do not conceal native overflow.

Native previews expose encoded logical-core facts before SQL DISTINCT/EXISTS
presentation. They are not SQL aggregate contributions, source admission tokens
or checked-proof authority. The original-SQL coordinator uses the genuine
compiled source/output binding to decode those facts and prepare final groups.
The [weighted-delta contract](weighted_deltas.md) describes their ownership,
unsigned signs, causal telescope and traversal limits.

Commit performs no further allocating or arithmetic preparation. It commits the
native epoch, then publishes source/key counters through same-allocator detached
nodes, iterator erasure or scalar assignment. Touched keys are unique and the
exclusive token prevents intervening mutation, so saved iterators/absence proofs
remain valid. Other map iterators survive each distinct-key publication.
Standard allocator and reference-count teardown still perform real work.
Detached nodes avoid new allocation at commit; unhinted destination-map insertion
still performs logarithmic typed-key comparisons.

Any setup, constraint, arithmetic or resource failure before return destroys
private proposals and abandons the native token. Earlier native stages reverse
through the existing stage/RAII boundary. Source/key maps remain committed until
publication, so they need no additional inverse log or per-row catch.

## Actual cost and scope

One source allowance covers the entire command: every input validation, touched
key/counter operation and occurrence adapter. It is separate from the native
indexed allowance already retained by the single native epoch. Neither is
refilled per row or alias. Source counters are selected logical admissions,
not a CPU bound on every ordered-map/string comparison.

For N input replacements, R distinct touched physical rows and K touched
constraint keys, work follows actual validation bytes, ordered lookups, key
projection and alias/native changes. Metadata is proportional to R+K, plus
new key payloads and detached publication nodes. Existing-key probes share
committed payloads. Source scratch is reused and only its touched prefixes are
cleared. Enabled native capture has its separately documented prefix traversal,
lookup and retained vector-capacity costs.

The SQL owner now uses a single funded shared control under the same account,
with real fixed metadata/refcount cost. It creates no account, budget refill or
full persistent source mirror. Single-row calls retain their original preparation,
constraint and publication bodies. The receiving tests and source-index cards
must be read at their own source checkpoint; this contract does not declare
aggregate/session/recovery acceptance complete.

The receiving ordered-backend Release probe compares the actual v18 installed
library with the new implementation: the shared owner adds a fixed 48 accounted
payload/requested bytes; facade size changes from 40 to 16 bytes. Constructor and
five ordinary single-row cases preserve allocation/free/current-allocation counts,
source/native work and outputs. These are measured build-specific storage facts,
not portable ABI guarantees, CPU timing or a global-heap bound. See the
[executed checks](verification/w06-source-batches-2026-11-12.md).

Inspect [public tokens](code_specs/files/include/crown/runtime/sql_rows.hpp.md)
and [source/key preparation](code_specs/files/src/runtime/sql_rows.cpp.md).
The prepared counter/transaction protocol is local engineering for
Refactor.md W06; it is not an additional CROWN paper theorem.
