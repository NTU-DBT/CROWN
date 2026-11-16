# Reference support maintenance

Status: R01–R04 verified; see the [runtime journal audit](verification/runtime-journal-2026-11-05.md).
The R05 prepared logical-epoch foundation is documented in
[prepared epochs](prepared_epochs.md). The separate
[physical coordinator](physical_runtime.md) supplies full-row routing and
derivation counts. R05 prepared output acceptance and its integrated delta-runtime
checks are verified; see the [ledger](task_ledger.md).
Release and runtime-performance gates remain open. This page describes the
current C++ reference support kernel in
[`support.hpp`](../include/crown/runtime/support.hpp) and
[`support.cpp`](../src/runtime/support.cpp). The logical support boundary is
specified in [Refactor.md §§6.1 and 6.3](../Refactor.md), with physical node
layouts and `C*` defined in [physical plans](physical_plans.md).

## Input contract

`SupportRuntime` is constructed from an immutable, validated `PhysicalPlan`
and starts with empty node state. One `apply` call accepts one
`NativeSetUpdate`: a contiguous logical sequence number beginning at 1, a
native `NodeId`, an `insert` or `erase`, and one complete logical tuple for
that node's scope. Tuple values follow ascending core variable ID in the
compiled scope layout. They are not physical source rows or physical column
positions.

Mutations require a writer-ready runtime. A
[current-result cursor](result_cursors.md) pins its committed epoch and blocks
all mutations, including no-ops, until terminal null, cancellation or failure.
Other committed reads remain available while cursor leases exist. The
[epoch-view foundation](epoch_views.md) adds shared leases for before/after
projected and full-witness fragment cursors. A held view blocks mutations even if all of its
cursors have finished; its copies share that group lease.

Each operation changes the set of logical rows at that native node. An
insertion of a present row and an erasure of an absent row are no-ops: they
return `native_changed: false`, consume the valid sequence number, perform no
support propagation, report zero metrics, and have `journal: null`. A real
insertion or erasure returns `native_changed: true` and a journal. Sequence
gaps, repeats, overflow, invalid rows, and updates to generalized nodes are
rejected. Generalized nodes have no external write port.

`apply` remains a one-update, one-sequence API. Its real-update path is one
stage in a prepared epoch, preserving the historical accounting: the native
input is event 1 and `events_enqueued == events_applied == 1 +
child_key_events`. Its no-op fast path consumes the sequence without opening a
transaction and leaves every metric zero. The separate explicit
`begin_epoch(sequence, operation)` API accepts multiple stages of that one
operation under one sequence, shared undo/work accounting, and one commit
barrier; see [prepared epochs](prepared_epochs.md).

`SupportRuntime` has no physical-table routing or base-row identity. A caller can
explicitly stage logical rows for several native nodes in one `PendingEpoch`,
but that does not route a physical update, evaluate source constraints, adjust
alias derivation counts, or coordinate base-table changes. `PhysicalRuntime`
now supplies those responsibilities around this logical kernel. The logical set API also cannot combine
multiple physical derivations of one logical row into derivation multiplicity.
Calls to `apply` do not implicitly combine updates. There is no bulk
initializer.

## Maintained state

For each node `v`, `S_v` is its survivor set and `P_v` is its parent-key
projection. A native row is in `S_v` exactly when every child separator key
has positive presence in that child's `P`. Its record keeps a distinct
`SatisfiedChildCount` and one presence flag per ordered child. Inserting a row
probes the current child supports; a later child-key transition visits only
matching rows in the node's reverse separator bucket.

A generalized node stores candidates from the union of its children's
projected keys. Its per-candidate child flags and satisfied-child count make
the candidate a survivor exactly when every child supports that key. The
candidate is erased as soon as its child-presence count reaches zero. This
uses no Cartesian intermediate, and an empty separator is an ordinary key
with value `[]`.

Every node has its own exact parent-support relation `P_v`: the support count
for a key is the number of surviving local tuples that project to it. Nodes
inside the physical plan's maximal root-connected connex subtree `C*` also
have a separate visible-projection relation `E_v`, for `F ∩ B_v`. Its support
count is the number of survivors projecting to that visible key. The `P_v`
and `E_v` relations, metadata maps, roles, and handles remain distinct even
when their layouts happen to match. Counter changes propagate only when a key
crosses between zero and positive support; positive-to-positive changes do
not emit a membership transition.

`C*` contains exactly the nodes reachable from the root across edges whose
separator is contained in the distinct core head `F`. `visible_keys` in a
snapshot is absent (`nullopt`) outside `C*`; inside `C*` it is an owning list,
including an empty list when no visible key is live. In particular, for an
empty head, an edge with empty separator is traversable because `∅ ⊆ F`.
Thus a nullary generalized root with disconnected unary children has all
children in `C*`; each child's `E_v` uses the nullary key and its exact
survivor support. Empty children have no key, while one or two surviving
child rows give `[{key: [], support: 1}]` or
`[{key: [], support: 2}]`. The Boolean root's nullary visible key has support
zero or one for this empty-scope generalized root. A Boolean native root still
has at most one nullary visible key, but that key's support can count several
distinct local survivors.

`has_answer()` is a boolean convenience: for a tree route it is true exactly
when the root survivor relation is nonempty; constant routes return their
constant value. Constant routes have no tree nodes or native update ports. It
does not enumerate the result or report a full-answer delta.

## Propagation and transition capture

Propagation uses a local `std::deque` work queue. `SupportOptions.order`
selects deterministic FIFO or LIFO draining. The runtime does not recurse
through the C++ call stack. A child `P_v` key appearance or disappearance queues
the corresponding child event; a native parent visits the matching reverse
index bucket, and a generalized parent updates its candidate-presence flags.
Survivor membership changes update both parent support and, when present,
visible support. The parent relation propagates only on its zero crossings;
the visible relation records its own crossings and does not propagate them
through the tree.

`SupportOptions.capture_transitions` is off by default. When enabled,
`SupportEpoch.transitions` owns the keys for local membership changes in this
response, including erased keys. For a pending epoch, the response aggregates
the changes from all stages. Each transition identifies the node, role, tuple
ID, operation, and causal event ID. These transitions cover record, survivor,
parent-key, visible-key, and generalized-candidate membership crossings. They
do not describe complete-query answer changes.

Every committed real `apply` or changed pending epoch returns an
affected-record `SupportJournal`, regardless of `capture_transitions`. Its
records describe each affected membership or metadata change, including
changes to support counts that do not cross zero. A pending epoch's journal
aggregates these records across stages. The optional `events` vector in that
journal is populated only when `capture_transitions` is true. Event accounting
and journal-record retention remain active with capture disabled.

## Handles and snapshots

`SupportHandle` is the logical public identity
`(SupportOwnerId, NodeId, SupportRole, TupleId)`. Its owner is the runtime
owner, not a private storage-backend owner. A positive-to-positive `P_v` or
`E_v` count update retains the same key and tuple ID, so its handle remains
usable across a successful update. Removal at zero invalidates the handle; a
later reinsertion receives a new tuple ID. Real updates use the same backend
tables under private storage journals, and backend `TupleHandle`s are not the
public API. `find` looks up a row/key and `get` returns an owning tuple copy
when that handle is still live.

`snapshot()` returns an owning diagnostic copy of the committed state:
node records and child flags, survivor tuples, parent keys and exact support
counts, and visible keys for nodes in `C*`. It is not a cursor. The separate
[result/fragment cursors](epoch_views.md) and [delta owner](delta_runtime.md)
use guarded relation access. Successful update journals
have their own tuple pins and can outlive later updates or the runtime; the
engine itself retains no journal history.

## Atomicity and accounting

Support counts use exact `uint64_t` `ProjectionSupportCount` values, including
values above 2^53. The configured `support_limit` must be positive; it defaults
to `uint64_t` maximum. An increment beyond that limit fails instead of
wrapping or approximating. The sequence and work counters are also exact
64-bit integers.

The default abstract `work_limit` is 1,000,000; `nullopt` disables it. On a
real update, the runtime mutates the active state under a transaction. It opens
a `ReferenceTable::Journal` lazily the first time each storage relation is
changed. Each table journal records inverse operations for row and index
membership changes. Node metadata uses a separate undo stack. A prepared epoch
keeps these same journals and this same undo stack open across stages. Before
changing a record or support counter, the runtime prepares its inverse: an
insertion is undone by erasing the new map entry, a change retains the old
value, and an erase extracts the existing map node so rollback can reinsert it
without allocating. Record changes save the previous child-presence flags in
that undo entry.

For every affected state change, the runtime appends a public `JournalRecord`
with its local ordinal, causal event ID, support handle,
logical tuple values, and owning before/after state values. Its tuple arena pin
keeps inserted or erased values readable even if the live table entry is
removed. The `before`/`after` values describe membership, satisfied-child
count, ordered child flags, and/or projection support count as applicable.
These records are produced for every real update, including support-counter
changes that do not emit a membership transition.

All allocations and other throwing preparation for propagation and public
output finish before commit. If an operation or stage fails, the runtime first
applies metadata inverses in reverse order, then rolls back all opened storage
journals. Both restoration paths are allocation-free. For a `PendingEpoch`,
they undo changes from every earlier drained stage too, restoring the rows,
indexes, logical tuple IDs, metadata, and answer from before `begin_epoch`;
the committed sequence was not advanced. Its token destructor follows the same
allocation-free rollback path.

For `apply`, the one drained queue is followed by one commit barrier. A
prepared epoch drains the queue after each changed stage but retains all undo
through those drains; a later stage starts from the preceding stage's tentative
state. At final commit, the runtime calls each table journal's no-throw commit,
destroys the private storage scopes and metadata undo nodes, and advances the
sequence once. A valid token with no changed stages still commits its sequence
once with zero metrics and no journal. No copied table state or metadata map is
kept for the update or epoch.

The public journal survives later updates and can survive destruction of the
runtime when its caller retains a committed `SupportEpoch` or journal pointer.
For `PendingEpoch` it aggregates records and optional events from all stages.
After commit, no private table journal objects or undo nodes remain in it. Its
logical retained payload is the public record pins and before/after values,
plus an optional event trace. When transition capture is enabled,
`SupportEpoch.transitions` also owns the local membership keys. Neither payload
retains a pre-update table snapshot, an old metadata map, or a query-wide frozen
state. The runtime itself keeps no history of successful journals; callers
control the lifetime and storage cost of returned epochs and their retained
values.

A failed update may leave arena high-water slot counts, table revisions, or
private arena generations advanced. With no caller-retained tentative preview
journal, a later `storage_statistics()` call reports the previous
live/retained/pinned state. Caller-held tentative pins can prolong aborted
payload lifetime. The runtime preserves its sequence and all previously valid
public support handles. Aggregate storage
statistics count arena slots and records across plan tables; they do not report
allocator bytes.

## Update metrics

`SupportEpoch.metrics` contains 20 exact unsigned counters. The four historical
whole-state-copy fields remain in the report for compatibility and are always
zero in this backend. `saved_child_flags` counts only flags copied into
metadata undo entries; it does not count the before/after flag snapshots held
by public journal records. None of these counters measure bytes, allocator
calls, strings, JSON encoding, or CPU time.

| Metric | Counted items |
| --- | --- |
| `work` | Abstract charged work during mutation, undo/journal preparation, and propagation, aggregated across the explicit epoch stages. |
| `copied_rows` | Deprecated; always zero. |
| `copied_index_memberships` | Deprecated; always zero. |
| `copied_metadata_entries` | Deprecated; always zero. |
| `copied_child_flags` | Deprecated; always zero. |
| `native_record_visits` | Native records processed directly or from a matching reverse-index bucket. |
| `child_key_probes` | Child support lookups for a native record's separator keys. |
| `child_key_events` | Child-key propagation events applied from the queue. |
| `survivor_transitions` | Survivor relation membership crossings. |
| `parent_key_transitions` | Parent-support relation zero crossings. |
| `visible_key_transitions` | Visible-projection relation zero crossings. |
| `candidates_created` | Generalized candidate records created from child support. |
| `candidates_reclaimed` | Generalized candidate records removed at zero child presence. |
| `storage_changes` | Insertions and erasures in reference relation storage. |
| `metadata_changes` | Record or projection-count metadata insertions, changes, and erasures. |
| `saved_child_flags` | Previous child-presence flags copied into metadata undo entries. |
| `journal_records` | Public affected-state records appended to the update journal. |
| `events_enqueued` | Changed native stage event(s) plus enqueued child-key events. |
| `events_applied` | Native stage event(s) plus child-key events applied by the scheduler. |
| `queue_peak` | Largest number of pending child-key events in the local queue. |

For a successful real single-call `apply`, `events_enqueued` and
`events_applied` are both `1 + child_key_events`. The native input update is
event 1; each child-key event gets an ID when enqueued. A prepared epoch
aggregates these counters across stages: each changed native stage contributes
one native event, event IDs continue across the token, and each child event's
cause links it to the event that enqueued it. Thus the batch totals are
`events_enqueued == events_applied == changed_native_stages +
child_key_events`. No-op stages add no events. A no-op `apply` has no journal
and all metrics, including `work`, are zero. The work limit bounds only this
abstract count and applies to the whole prepared epoch; it is not an allocator,
memory-byte, or time quota.

Sequence, support-counter, work-limit, allocation, or propagation failures
leave the previously committed logical state, sequence, and live public
handles unchanged. A stage failure aborts all earlier stages of its pending
epoch. A successful no-op `apply`, or a committed pending epoch containing
only no-op stages, consumes its sequence once. `apply` is failure-atomic per
call; `PendingEpoch` is failure-atomic across its explicit stages. Neither
provides durable recovery.

## Logical trace diagnostic

```sh
crown support-trace PLAN.physical.json LOGICAL_TRACE.json
```

The [version-1 trace schema](../schemas/support-trace-v1.schema.json) defines
input and retains the historical v1 report definition. Input requires
`schema_version:1` and an
`updates` array; each entry has `sequence`, a native tree-label `node`,
`operation` (`insert` or `erase`), and typed scalar `values` in logical scope
order. Optional `options` fields are `work_limit` (integer or null), positive
`support_limit`, `order` (`fifo` or `lifo`), and boolean `capture_transitions`.
The default host trace-length cap is 100,000 updates, independent of the
serialized per-update work limit.

The reader validates the complete trace before starting. Success returns a
`complete` report and exit 0. A work/support cap returns exit 1,
`status:update_rejected`, its rejected sequence and the unchanged previous
committed state. Malformed inputs use stderr/exit 2; internal invariant
failures use exit 3. Output is a v2 report validated by
[support-report-v2.schema.json](../schemas/support-report-v2.schema.json); it
labels the backend `reference_incremental_journal` and the contract
`logical_native_set`. Each completed epoch includes local transitions, 20
metrics, a journal object or `null`, and an owning state snapshot. A real
update's journal contains a sequence and retained records with ordinal, cause,
handle, tuple values, and before/after support state. Its `events` array
contains event IDs, causes, update and application ordinals, target/source,
operation, key, and before/after membership when `capture_transitions` is
enabled. Otherwise that array is empty. Records and cause IDs remain available
when event tracing is disabled. Full diagnostic snapshots, invariant scans,
JSON encoding, and caller-retained journal history have separate costs; they
are not kernel metrics. The report is not a resumable checkpoint, recovery
journal, or physical input protocol.

The physical artifact's `GuaranteeProfile` continues to describe compilation
and empty storage construction. This logical support kernel does not change
that frozen artifact into a physical SQL executor or a certified cursor.

## Scope and verification

This is a single-writer C++ reference kernel. `PendingEpoch` adds an explicit
same-sign, multi-stage logical transaction. The separate physical coordinator
adds source adapters and alias routing, and the
[result cursor](result_cursors.md) provides committed current answers. The
[delta owner](delta_runtime.md) supplies eager-live exact delta enumeration
and bounded private output. Bulk initialization, optimized delay, durable
recovery and general memory-byte accounting remain separate work.
[Epoch views and fragments](epoch_views.md) supply
journal-backed before/after context, all-variable projected completions and
full assignments over survivor subtrees or exact factor sets.
The transaction's private undo scopes provide per-call rollback for `apply`
and whole-epoch rollback for a pending token; the returned journal is in-memory
diagnostics, not durable recovery or an engine-maintained history. The journal
is not a global before/after query snapshot or a frozen outside-context object, and it
does not supply the D01/D02 result cursor or liveness protocol. Journal record
pins retain affected tuple payloads, while snapshots and captured transition
keys own their copies through [S03 tuple arenas](tuple_arenas.md).

The affected-record design establishes no general CROWN update bound or
output-sensitive complexity guarantee. `work` is an abstract per-`apply` or
per-epoch limit, not a time or memory quota. `check_invariants()` checks
internal child presence, survivors, candidate unions, and P/E counts; it is
not an independent subtree evaluator. External G2/V02 proof review remains
outstanding.

All 53 tests pass GCC Debug/Release, ASan/UBSan, Clang18 and a fresh source-only
Release build; the [D04 packet](verification/delta-runtime-2026-11-06.md)
records the current maintained-output checkpoint. The
[D03 packet](verification/delta-spec-2026-11-06.md) records the preceding
proof and model checkpoint.
The [fragment-cursor packet](verification/fragment-cursors-2026-11-06.md)
records D02 verification. The
[epoch-view packet](verification/epoch-views-2026-11-06.md) records its predecessor foundation.
The
[result cursor packet](verification/result-cursors-2026-11-06.md) records D01.
The
[physical coordinator packet](verification/physical-runtime-2026-11-06.md)
records the prior physical foundation and the remaining R05 output acceptance. The
[prepared epoch packet](verification/prepared-epochs-2026-11-06.md) records the
earlier logical batch foundation.
The [R04 packet](verification/runtime-journal-2026-11-05.md) records the earlier
single-update journal audit. The original logical and storage contracts remain in
[Refactor.md](../Refactor.md), [semantics.md](semantics.md), and
[storage.md](storage.md). The historical initial design is recorded in
[decision 0011](decisions/0011-reference-support.md); the current journal
architecture is [decision 0013](decisions/0013-support-journals.md).
