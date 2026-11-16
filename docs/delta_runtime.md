# Delta runtime and live maintenance

Status: D04 and integrated R05 output acceptance are verified. All 53 tests
pass GCC Debug/Release, ASan/UBSan, Clang18 and a fresh source-only Release
build; see the [verification packet](verification/delta-runtime-2026-11-06.md).
The current tree adds verified D05 ordered E replay, enumerable parent/child
live indexes, productive witness queues and a runtime guarantee profile.
The historical 64-test checkpoint passed the same five configurations; see the
[ordered replay packet](verification/ordered-delta-2026-11-06.md) and
[proof/cost argument](ordered_delta.md). The preceding
[anchor](verification/anchored-delta-2026-11-06.md) and
[live](verification/incremental-live-2026-11-06.md) packets are historical.
Verified D06 [pending lifecycle](delta_lifecycle.md) adds real resumable route
production and recoverable committed callbacks. All 66 tests passed the
[D06 matrix](verification/delta-lifecycle-2026-11-06.md).
The full Refactor.md goal and O work remain active. The
[D03 packet](verification/delta-spec-2026-11-06.md) records the preceding proof/model checkpoint.

`DeltaRuntime` owns a `PhysicalRuntime`, an optional committed L image and one
output owner. Its default constructor starts with empty physical source
tables; R06 also adds
`DeltaRuntime::initialize(plan, database, options, build_options)`
for a complete starting snapshot and `rebuilt(build_options)` for a fresh
owner at the current committed sequence. Initialization creates no public
input epoch or output, and rebuild preserves the current mode and options while
leaving the old owner intact. Full snapshot, build-work and failure semantics
are in the [runtime initialization contract](runtime_initialization.md).
R06 acceptance passed its historical 75-test five-configuration
matrix. See the [R06 verification packet](verification/runtime-initialization-2026-11-06.md)
for the configurations and timings; the earlier D04/D06 packets above are
historical checkpoints.
The current [O03 matrix](verification/batches-windows-2026-11-06.md) passes
all 79 tests with typed batches and operational windows.

It implements the
[D03 partition](delta_transition_spec.md) with three live-maintenance policies.
Its default producer has bounded fixed-query indexed actions per internal
first/next/last result after route preparation. Public atomic startup, cleanup,
ordered dictionary costs and durable sink work have separate qualifications.

## One physical input

`begin` prepares the source row and returns a private `PendingEpoch` before
all occurrence routes/output are finished. `step` advances actual unfinished
work and yields at most one accepted core row. It can pause with its current
cursor, complete anchor, productive queue, endpoint views and undo intact.
Retaining `drain` completes preparation; `commit` requires prepared state.
`apply` uses begin/drain/commit and preserves its complete atomic spool contract.

Physical staging prepares each occurrence's derivation counts in
the existing physical transaction. A native zero crossing drains the logical
support queue. Before the next occurrence, an internal observer runs with
adjacent-prefix before/after views and that stage's retained journal records.
Only true visible-E membership crossings enter each changed-key set; optional
causal trace capture is not used.

Root L equals root E. Each child retains E rows whose separator has a parent-L
match, with an exact count of distinct live parent keys at that separator.
Shared separators remain positive until their last live parent disappears.
The supplied-tree/running-intersection/downward-totality conditions are the
D03 preconditions established by support maintenance at drained boundaries.

The default `LiveMaintenance::on_output` updates full L projections while
processing accepted core delta rows, visiting parents before children and
immediately adjusting child separator counts. An insertion adds absent
projections. In ordered replay, deletion removes the current full anchor key
and descendants whose current parent support is zero; it must not prematurely
test future changed E keys. Canonical reference paths use endpoint E absence.
It opens no child E
buckets and does not copy or rebuild the full L cache. Its deletion
completeness argument uses a fresh ancestor-path certificate; simply seeing
each dead key once would be insufficient when several parents share a key.

`LiveMaintenance::incremental` is a bucket-based comparison policy: seed
changed E keys, then propagate actual L changes down the tree. Only support
0↔1 visits the matching child E bucket. `LiveMaintenance::eager` retains the
D04 comparison path, rebuilding L by top-down E-factor semijoins on each
route. Initial delta-mode construction and explicit invariant checking build
the complete L image under every policy. The [live-maintenance argument](incremental_live.md) gives the
invariants, undo details, conditional proof and component costs.

`DeltaCompletion::automatic` resolves to `ordered_replay` with `on_output`,
and `anchored` with the other live policies. Explicit replay requires
`on_output`; `completion()` exposes the effective strategy, while `options()`
retains the requested option. Replay visits insertion factors in reverse rank
order and deletion factors in forward rank order, preserving intermediate
downward totality. Preparation filters initially dead anchors; actual L
erasures immediately prune future productive queues. Each remaining anchor
has a result and owns every row it emits, with no canonical rejection.

The replay cursor binds the full E key, reads endpoint E inside its original
subtree and exact current live-parent/live-child buckets outside. Outside
buckets are immutable during that fragment. Frames own their selected keys
and use fresh successor lookups across callbacks. This preserves D03's
earliest-factor ownership, with reverse owner visitation on insertion, and
uses no stage-before L copies. See the [replay proof](ordered_delta.md).

Explicit canonical [anchored](anchored_delta.md) and `root_first` remain
comparison paths. They use E-after/L-after on insertion and E-before/L-before
on deletion, restoring stage-removed live keys for non-eager before views.
Anchored traversal uses target E downward and live-parent indexes upward;
root-first uses general D02 completions. They reject a candidate if an earlier
changed factor owns it, so their candidate bound does not imply bounded
accepted-output gaps. Accepted mapped rows append directly to the unpublished
spool. No policy retains an output deduplication relation.

Non-eager policies tentatively mutate L and separator counts behind the busy
barrier with affected-node undo. The eager policy retains separate old/new
prefix images. All stage views/cursors close before the next native stage.
No-op, filtered, count-only and unused-table changes still consume an accepted
physical sequence; unchanged L memberships receive the new committed tag.

Any private view, cursor, work, allocation or spool failure unwinds stage
readers, then uses the existing logical/count/source rollback. The committed
L/P/B state, source rows, support and sequence are restored. No output epoch
is returned on failure. The physical commit barrier runs after all throwing
output/live preparation; committing live undo, installing the sequence tag
and returning the prepared artifact then use no allocation.

## Views and prefix identity

Public `PendingEpoch::view(before)` and `PendingUpdate::view(before)` retain
their D02 whole-epoch-start meaning. A private checkpoint records the journal
offset, previous truth, runtime owner, epoch and logical prefix. The internal
stage view applies inverse patches only from that offset. It retains the
**cumulative** journal for pins and active table writers: slicing the records
into a separate journal would lose tentative reader access to an earlier
stage's still-active storage transaction.

Prefix groups share the existing lease and intrusive cursor-abort behavior.
Staging rejects while an external prefix view/cursor remains. Before-sequence
is n for the initial logical state and n+1 for later changed logical prefixes;
internal checkpoint IDs distinguish these contexts. The observer additionally
carries the physical route ordinal, including filtered/count-only routes that
leave the same logical state in place. Ordinary
committed views and E-factor scans block every writer until their leases end.

## Output, mapping and ownership

`DeltaOptions::view` selects core or SQL output. Direct CQ plans use their
ordered/repeated core head. Normalized DISTINCT output maps every accepted
core row through ordered/repeated fields and constants. Scalar EXISTS output
has one Boolean row even for a false body. A physical truth flip appends an
erasure of the old Boolean and an insertion of the new Boolean, in that
order, after all occurrence routes succeed. These two SQL signs do not have
to equal the physical input sign. A constant source-free query is separate
and does not create input deltas.

`Epoch` is move-only and contains a committed `PhysicalEpoch`, immutable
metrics/layout/stage summaries, and an owning spool. `next()` moves one signed
record with a one-based accepted-output ordinal, without allocation. It
returns null repeatedly after exhaustion or discard. Returning the last record,
`discard`, destruction or replacement of the artifact releases its output
owner. A record already returned owns its values independently. Moving a
facade or destroying it does not invalidate outstanding output.

New input and mode changes require both physical writer-readiness and no
committed output owner. Ordinary committed reads remain available during
output delivery and can themselves acquire read leases. An empty output
artifact holds no delivery barrier. Discarding committed output leaves the
accepted input committed; it never rewinds the query. All internal work was
already drained before publication. The pending lifecycle can pause before
that point, discard by finishing internal work without retaining output, or
abort through rollback/destruction. It blocks public state reads and new input
throughout tentative ownership; a later alias cannot stage until the active
route's cursors/views close. See [delta_lifecycle.md](delta_lifecycle.md).
An external subscriber that drops unread records needs a fresh result snapshot
before it can maintain a complete external copy again.

Committed `deliver_one` borrows a front record and acknowledges it only after
the sink callback succeeds. An optional first callback serializes separately;
its failure does not invoke the sink. Failure preserves the tuple/ordinal for
retry or discard, unless the callback explicitly discards/destroys its final
owner. Callback moves keep the borrowed row alive; reentrant output consumption
reports busy, and reentrant discard defers release until the borrow ends.
An external side effect followed by failure may duplicate on retry. O06 durable
sink/recovery guarantees are not established by this in-memory protocol.

`Epoch::stages()` records each real native-zero-crossing route in occurrence
order: the one-based physical route prefix, old/new truth, changed/candidate/accepted/rejected counts,
its zero-based spool interval and resulting live-row count. Scalar EXISTS
replacement records are prepared at epoch end outside those core route
intervals. Prefix numbers include preceding filtered/count-only routes, so
summaries can have gaps; `metrics.stages` counts actual native crossings.
The summaries do not retain historical L images. The input artifact
retains affected journal/source pins for diagnostics until its destruction,
independently of the released delivery barrier.

## Modes and bounded spool

The default mode is delta. Maintenance mode uses physical/support drain with
no L image or output enumeration. `set_mode(delta)` requires a quiescent
writer barrier and builds L from the current E state. Its successful metrics
are returned and retained as `bootstrap_metrics`. Failure preserves the prior
mode/cache. Leaving delta mode drops L; maintenance updates cannot silently
reuse it. `options().mode` records the initial option; `mode()` is current.

The spool has finite row and accounted-byte limits, with atomic rejection
instead of spill or external backpressure. Zero limits accept empty output
only. Each prepared record owns one FIFO node; append links one new node and
never moves a result-dependent record buffer. Accounted bytes include each
node's real allocator request, including its link/padding and account framing,
and the native tuple's actual compact scalar and shared object/control requests.
Binary string bytes and inline exact decimals reside in that compact payload;
there is no retained standard Row/string mirror. The original query account
funds these allocations. Shared immutable program/layout allocations are charged
once to that account and are outside the per-spool sublimit. This is not a
process-RSS quota. Prepared record counts and retained payload bytes are bounded
by configuration.
`DeltaRuntimeProfile::output_accounting` retains the historical v2 description
byte for byte. Its statement about additional allocator metadata is legacy text;
the actual quota includes the framing described above. The header comments and
this contract state the current resource boundary. Changing that descriptive
wire field requires a separately versioned compatibility change.
`spool_capacity_rows` equals prepared row nodes. Consumption frees one node;
discard/destruction detaches unread nodes iteratively. A cursor-owned
candidate and SQL mapping scalar-view scratch have additional per-row width
costs and can be constructed before spool admission. They use the same query
account while remaining outside the spool sublimit. Returned public tuples and
their read-only values views retain their original charged payloads after
consumption or facade destruction. Releasing the FIFO node does not release a
caller-retained tuple payload. Retained support journals are separate from the
spool sublimit and remain charged to the query account. S05 acceptance verifies the shared native runtime account, including session,
queue, capture and retained-report allocations; see the [query memory contract](query_memory.md)
and [S05 acceptance record](verification/s05-native-acceptance-2026-11-09.md).
Caller-owned DTOs and explicit serialization exports remain outside that account.

The immutable plan prepares a fixed teardown inventory for its canonical JSON
identity during lowering. Releasing the final facade/output/cursor owner clears
child containers before parents, avoiding the JSON library's allocating
destructor stack. This is a query-metadata dependency fix; its storage and
linear final-teardown cost are separate from delta work. Partial inventory
construction uses an allocation-free leaf-removal fallback with additional
traversal/array-shift costs.

No durable, retrying or remote sink is implemented here. O06 must supply its
own prepare/commit/recovery protocol and demonstrated delivery semantics.

## Work and space accounting

Delta metrics are additional to `PhysicalEpoch::input.metrics` and nested
support work. Its aggregate work limit counts stage/view/journal work,
E scans, live-parent scans, separator fields, copied live rows, changed-key
discovery, live/dead witnesses, completion startup/results/termination,
candidates, earlier-rank probes/projection fields, live probes/mutations,
separator updates/crossings, bucket opens/rows, live undo entries, output
fields and spool append actions. Cursor/view sublimits remain independently enforced. Ordered
container comparisons, scalar widths/copies, allocations and fixed query
compilation retain their separate costs. Replay queue tests/inserts/pops/prunes,
parent/child-index actions, mapping and spool-node appends are included in
its production phases. Preparation, first/result/termination work and explicit
finalization reconcile to total delta work (with scalar EXISTS final mapping
separate). Finalization charges C/view retirement, physical/support/driver
cleanup bounds and exact live undo entries before publication. Eager mode also
charges retired full L/P/B images, including an unchanged-answer route.

`live_rows` counts the final cache. For non-eager policies, `peak_live_rows`
also charges extracted old nodes and stage-local removed-key copies; eager
mode counts simultaneously retained committed/old/new L rows without
double-counting shared images. Separator-map and undo metadata have additional
key-width/allocation costs.
`parent_index_rows` counts enumerable complete parent keys across child edges;
`peak_parent_index_rows` includes extracted old entries and stage copies, or
eager old/new images. `child_index_rows` counts nonroot L keys indexed by their
parent separator, with its own peak/update/copy/field counters. Index
update/copy/field/cleanup counters are separate.
Anchored phase work classifies already charged traversal actions, with
separate maximum startup/result/termination candidate actions. Bucket descriptor
search is explicit `CursorWork::descriptor_steps`; accepted-output rejection
and transaction cleanup remain outside the canonical candidate-transition
bound. Replay additionally records maximum successful first/next/last producer
work, including immediate coupling, queue operations, mapping and spool append.
`spool_rows`, `spool_capacity_rows` and `spool_bytes` retain prepared-output
high-water evidence; they do not decrease as callers consume records and are
not a current-outstanding-byte report. The account's current bytes track actual
release, including caller-retained tuples/views. Bootstrap cost is separate from
per-input cost. Only eager mode
rebuilds L on every changing native route. Both other policies charge actual
live changes and parent-count updates; row-coupled mode additionally projects
each accepted core row even when its L keys are already present/removed.
Globally unlive changed keys still incur discovery/eligibility work.
Diagnostic `snapshot`, `live_snapshot`, and `check_invariants` have their own
owning-copy/scan costs and are not called by the update algorithm.

`initialization_metrics()` includes physical snapshot validation/construction
and, in delta mode, construction of the initial live image. Its cumulative
`BuildOptions.work_limit` is independent of the ordinary physical and delta
per-update limits, and includes the full constraint pass and rebuild snapshot
copy. These counters remain work bounds, not memory-byte measures. S05 verifies actual
post-admission native runtime allocation requests under the shared query account;
explicit JSON/text exports and supplied immutable artifacts remain boundaries. See
the [query memory contract](query_memory.md), [tuple and arena scope](tuple_arenas.md),
and full [runtime initialization contract](runtime_initialization.md).
`canonical_state()` and `inspect_invariants()` expose typed diagnostic state
and localized reports for the support and live indexes.
Inspection has independent work and issue limits. Trust a report only when
`complete` is true; `valid()` also requires that the issue list is empty. The
versioned JSON writers in `crown/io/inspection.hpp` are diagnostic formats,
not checkpoint or restore formats. See the full
[runtime initialization contract](runtime_initialization.md).

Pending `discarded_records` counts already prepared nodes cleared and future
mapped records skipped while required core work still runs. Spool statistics
retain prepared high-water evidence; discarded epochs have zero output-stage
intervals. Clearing private nodes is separately charged finalization, not
double-counted inside an open replay producer transition. `timings()` separately
samples physical work, internal delta work, output mapping, serialization and
sink callbacks; it excludes client pause time and is independent of deterministic
work counters. It is not an exhaustive total-runtime clock.

`profile()` returns a detached runtime guarantee profile with typed effective
mode, completion/live policy, candidate/accepted bound and publication type;
its explanatory text has static storage. Replay's accepted bound is explicitly
post-preparation and per logical route. Constraint checking can scan/copy the
full database; bootstrap scans E; alias maintenance is separate; ordered
map/set actions have logarithmic comparison costs plus value widths. Public
`apply` prepares the whole atomic epoch before returning its first record,
including all route maintenance, production and finalization. It has no
constant public-startup claim. The serialized physical-plan profile remains
compile-only; no runtime bound is inferred from that artifact.
