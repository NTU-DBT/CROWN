# Prepared logical support epochs

Status: the R05 prepared logical-epoch foundation is implemented and verified.
At this foundation's checkpoint, all 41 tests passed GCC Debug/Release,
ASan/UBSan, Clang18 and a fresh source-only Release build; see the
[verification packet](verification/prepared-epochs-2026-11-06.md).
The later [physical coordinator](physical_runtime.md) uses this token for
full-row routing and derivation counts. R05 remains in progress for integrated
full-query output acceptance.

This page documents `SupportRuntime::PendingEpoch` in
[`support.hpp`](../include/crown/runtime/support.hpp). It extends the R01–R04
logical-native support kernel with a single unpublished transaction spanning
multiple native logical rows. See [reference support maintenance](runtime_support.md)
for the maintained relations and [support invariants](support_invariants.md)
for their meaning. The physical-input requirements that remain in R05 are
listed below and in the [task ledger](task_ledger.md).

## API and ownership

`begin_epoch(sequence, operation)` opens one pending epoch at the next valid
logical sequence. The `insert` or `erase` operation is fixed for the entire
epoch. `stage(node, row)` supplies one complete logical tuple for one native
node, using the same ascending-variable-ID scope order as `NativeSetUpdate`.
Each stage performs one native set update and drains its upward propagation
queue before returning. Later stages see earlier tentative changes. An epoch
can contain multiple caller-supplied stages, including rows for different
native nodes, but it cannot mix insertions and erasures. This is logical
staging; it does not route a physical update to aliases.

`stage` returns whether that native row changed membership. Inserting a row
already present or erasing one that is absent is a valid no-op: it adds no
native event or propagation trace. If every staged row is a no-op, committing
the valid epoch still consumes its single sequence once. The epoch preview's
`native_changed` reports whether any staged native row changed.

While an epoch is open, `ready()` is false. Public runtime state reads
(`snapshot`, `find`, `get`, `has_answer`, `storage_statistics`, and
`check_invariants`) and public mutations (`apply` and another `begin_epoch`)
fail with a busy error. `plan()`, `options()`, and `owner()` remain readable as
immutable runtime information, and `sequence()` remains readable as the last
committed sequence until commit. Tentative state is available only through the
pending token's `preview()` and `snapshot()` methods. They are owner-only
diagnostic views and must remain unpublished until commit succeeds. Neither is
a full global answer delta: the preview reports aggregate metrics, a boolean
`has_answer`, the affected-record journal, and optional captured local
transitions; the snapshot is an owning copy of tentative support state.
Snapshot construction and other diagnostic inspection are not support-kernel
work metrics. `preview()` returns a reference into the active token and can
reflect later stages; do not retain it across commit or rollback. `snapshot()`
returns an owning copy.

A caller that copies the preview's journal pointer can prolong tentative
payload lifetime after abort. Such a journal remains aborted diagnostic data,
not committed output. Rollback releases the engine's own pins; caller-held
tentative pins have the same separate retention cost as other caller history.

The token is move-only and has `noexcept` move operations. While active, it
shares the runtime implementation so the pending epoch remains valid if the
facade is moved or destroyed. `rollback()` and token destruction undo the
whole epoch through the allocation-free inverse path. Rollback is idempotent
for inactive tokens. After commit or rollback, the token releases the
implementation and keeps no historical state on its own. A returned
`SupportEpoch` may retain its public journal; that journal pins only affected
row values and the records/traces for this epoch, under the existing
[R04 journal retention rules](runtime_support.md#atomicity-and-accounting).
It is not a frozen copy of the query state.

## Staging, rollback, and publication

An epoch validates its sequence and operation before opening. A failed
`begin_epoch` leaves the runtime unchanged. Each successful stage mutates the
live internal tables under one shared R04 metadata undo stack and set of lazy
storage journals, but the runtime's public readers remain locked for the
duration. Work accounting and the journal output also continue across stages.
Stage propagation finishes before the next stage starts, so no queued event
from one stage is pending when another stage begins.

If row validation, propagation, resource limits, allocation, or invariant
checking fails during `stage`, the runtime rolls back every earlier stage,
closes the token, and then rethrows. No sequence is consumed and no partial
epoch output is published. Explicit rollback and token destruction use the
same allocation-free R04 inverse path.

For a valid active token, `commit()` performs no allocation: it transfers the
already prepared epoch output, commits the no-throw storage journals once,
and advances the committed sequence exactly once for the whole token. Calling
`commit()` on a closed, moved-from, or otherwise invalid token is rejected as
an invalid epoch before publication. The commit boundary is the only point at
which any staged state becomes visible through public runtime readers.

Metadata and relation rollback remain row-scoped, following the existing
`SupportJournal` memory rules. Neither the pending token nor its returned
journal retains a whole pre-epoch table image. The explicit owner-only
`PendingEpoch::snapshot()` copy is an unpublished diagnostic output, not a
published snapshot or a retained rollback structure; neither it nor
`preview()` supplies full global answer deltas.

## Batch event and resource accounting

Epoch metrics aggregate work across all stages. The configured resource work
cap applies to the whole epoch and is not reset between stages. Propagation
queues drain between stages, while event and work accounting continues across
the batch.

Each changed native stage contributes one `native_update` event. Event IDs
advance across the whole epoch, so a later stage does not restart its native
event ID at 1. No-op stages contribute no trace event. Native events have cause
0. Each child-key event names the event that enqueued it as its cause; nested
propagation therefore forms a cause chain back to the native event for that
stage. Its source handle identifies the child support key that crossed.
Across a committed batch,
`events_enqueued == events_applied == changed_native_stages + child_key_events`.
The aggregate `child_key_events` count covers the drained propagation for all
stages. A batch containing only no-op stages has no native or child-key events.

Scalar row validation, construction of previews, explicit snapshot copies,
invariant scans, and serialization are separate caller-facing costs. They are
not represented by the support work counter or by the batch propagation
metrics. Optional causal event capture also follows the existing support
options; journal record retention and accounting remain active independently
of trace capture.

## Compatibility and remaining R05 work

The existing single-update `apply(NativeSetUpdate)` contract is unchanged.
The generic `crown support-trace` input remains one trace-schema-v1 JSON
envelope with an `updates` array; each array entry is one native logical
input. Its output remains report schema v2. The prepared epoch API does not
change either trace format or make trace replay a physical-table update
interface.

This token is a logical batch foundation. `PhysicalRuntime` now wraps it with
full source-row identity, constraints, per-occurrence final-native derivation
counts, deterministic alias fan-out and a prepared publication boundary. Its
real physical-row tests compare maintained support and reconstructed results
against full recomputation. R05 still needs integrated full-query delta tests
and a bounded unpublished output spool or transactional sink; those are not
supplied by logical membership traces or diagnostic snapshots.

No physical routing, derivation-count, global-delta, or sink guarantee is
provided by `PendingEpoch`. Its preview, local transitions, and support
snapshot do not stage or publish full-query deltas. R06 bulk initialization,
delta cursors, durable recovery, and memory-byte
accounting also remain separate work. [Current-result cursors](result_cursors.md)
use a separate committed read lease and cannot open during a pending writer.
The [D02 cursor](epoch_views.md) supplies owner-only before/after projected
completions and full witness fragments through `view(side)`. Holding a view or
its cursor seals the drained prefix: a further `stage()` reports `runtime_busy`
and leaves the token active. Other staging failures still abort the epoch.
View/cursor construction failures leave it active; commit preserves its views,
and rollback closes their cursors before undo.
