# Physical runtime transaction

Status: the `PhysicalRuntime` transaction and alias-count foundation is
implemented and integrated R05 output acceptance is verified. The
[D04 delta owner](delta_runtime.md) supplies per-route full-query output and
bounded private spooling. Its historical 53-test five-configuration matrix passed;
see the [D04 packet](verification/delta-runtime-2026-11-06.md).
Standalone `PhysicalRuntime` returns local support changes.
R06 adds validated snapshot initialization, quiescent rebuild and localized
inspection APIs. R06 acceptance passed its historical 75-test
five-configuration matrix. See the [R06 verification packet](verification/runtime-initialization-2026-11-06.md)
for the configurations and timings, and the full
[runtime initialization contract](runtime_initialization.md).
The historical [O03 matrix](verification/batches-windows-2026-11-06.md) passed
79 tests with typed batches and operational windows. Later scoped verification
packets apply to their own source seals; these counts are not the current suite.

This page documents [`PhysicalRuntime`](../include/crown/runtime/physical.hpp)
and its implementation in
[`physical.cpp`](../src/runtime/physical.cpp). It sits above the logical
[`SupportRuntime`](runtime_support.md) and its prepared
[`PendingEpoch`](prepared_epochs.md). The physical transaction routes one
source-table set update to zero or more compiled occurrences while holding
source, derivation-count, and logical support changes behind one commit
barrier.

The [current-result cursor](result_cursors.md) now traverses the maintained
logical E state. `results()` applies SQL output mapping; `core_results()`
uses the core head. Active cursor leases block physical updates and make
`ready()` false while ordinary committed reads remain allowed. These public
current-result factories cannot open on a pending update's tentative state.
The separate [D02 cursor](epoch_views.md) exposes owner-only
before/after core cursors through `PendingUpdate::view(side)`, plus committed
`current_view()`, all-variable projected `completions()` and full S-factor
`witnesses()`. View cursors use the core schema; SQL mapping is supplied by
`results()` and the separate delta owner. View leases survive commit and
block the next physical update until every view/cursor releases the group.
`has_answer()` continues to report core CQ truth; SQL EXISTS still returns
its one Boolean output row when that truth is false.

## Input and source-row identity

The default `PhysicalRuntime(plan, options)` constructor still starts empty.
R06 adds `PhysicalRuntime::initialize(plan, database, options, build_options)`
for a complete starting snapshot and `rebuilt(build_options)` for a separate
owner reconstructed from a quiescent current state. Initialization returns a
ready owner at sequence zero without a public epoch, output delta, or fabricated
input/source position; the first later external update is sequence one.
Rebuild preserves the committed sequence and runtime options while leaving the
original owner intact. Direct construction and rebuild details, including
failure behavior, are in the
[runtime initialization contract](runtime_initialization.md).

Both build paths validate the entire source `Database` against the
plan catalog before constructing state: table count, typed complete rows, set
identity, and all enforced unique and foreign-key constraints, including
unused tables and constant routes. Valid cyclic foreign keys are supported
because the snapshot is checked as a whole rather than as public insertion
prefixes. `BuildOptions` selects `direct` (the default) or `insertion_replay`
and applies a cumulative build-work limit independently of the per-update
limits below. It accounts for constraint validation, construction work, and
the snapshot copy used by rebuild. These work counters are not a memory-byte
quota. The implemented native memory-byte boundary is documented in
[query memory](query_memory.md) and [tuple/arena ownership](tuple_arenas.md),
including retained state and output costs.

After initialization, each `prepare` or `apply` call accepts one
`PhysicalSetUpdate` with a contiguous sequence number, a catalog `TableId`, an
`insert` or `erase`, and a complete physical row in that table's declared
column order.

Source membership uses the complete physical row as its set key. Two rows
that differ in an ignored, filtered, or otherwise unprojected source column
are distinct physical rows. Conversely, inserting an exact row already
present, or erasing an absent exact row, is a physical no-op. Alias projection
does not redefine source identity: a row can change physical membership while
only incrementing or decrementing an existing logical derivation count.

The runtime owns source storage for every catalog table, including tables with
no compiled input route and plans on constant-true or constant-false routes.
When the frozen plan has a physical-base relation for a table, runtime source
storage uses that layout. Tables without one receive a supplementary private
source layout from the catalog. These runtime descriptors do not modify the
compiled plan, its frozen physical artifact, or its identity. An update to an
unused table still changes the runtime's physical database and consumes its
sequence.

The first valid update uses sequence 1. Every successful commit consumes one
sequence, including exact duplicate inserts, absent-row erasures, updates
filtered from all aliases, positive-to-positive projection count changes,
and updates to tables with no routes. A duplicate insert or absent erase has
`physical_changed == false`, no source handle, no alias visits, and zero
metrics. Filtered, unused-table, and projection-only updates are physical
source changes: their source and routing metrics describe that work even when
they cause no logical membership change. Invalid rows, operations, tables, or
sequences fail without consuming a sequence.

## Compiled alias routing and final-native counts

The runtime visits the plan's compiled `base_routes` for the changed source
table, in their stable occurrence order. Each occurrence independently runs
its compiled adapter. Constants, repeated-variable equalities, and SQL-local
filters can reject a row for one alias while another alias accepts it.

For every accepted occurrence, the runtime counts the adapted tuple in that
occurrence's final native-node scope. Counts are exact positive `uint64_t`
values and are kept per occurrence, even when several physical rows or
several aliases project to the same final native tuple. The configured
`derivation_limit` rejects an increment before it can overflow that limit.

Only zero crossings stage logical set updates:

| Per-occurrence count change | Logical action |
| --- | --- |
| 0 to 1 | Insert the final native tuple |
| positive to positive | Keep native membership; do not stage a logical update |
| 1 to 0 | Erase the final native tuple |

This distinction lets the source relation retain full-row set semantics while
the logical kernel retains set semantics after projection. In particular, a
positive-to-positive change can have physical source and derivation metrics
with no support journal or native crossing. `PhysicalPreview.derivations`
reports each routed occurrence's before/after count and crossing status.

## Borrowed native update admission

PhysicalUpdateView describes sequence, table, operation and read-only tuple values.
Typed queues, EventReader and window adapters pass compact native fields into DeltaRuntime::begin_view without
an owning ordinary Row export. Admission borrows those values only for the call;
physical/delta pending state owns imported native rows and pins before returning.
External PhysicalSetUpdate entry points borrow caller DTO values through the same
boundary. Sequence, shape/type/decimal validation and atomic rollback remain the
same. A window Prepared owner separately keeps its own update payload alive
through publication and until Prepared destruction.

## Constraints and validation cost

If the source catalog contains no enforced constraint, the update does not
build a proposed whole-database image for constraint validation. If any
constraint is enforced, the runtime applies the proposed source mutation
under its open source journal and takes native compact snapshots of every
source table in the proposed after-state. The native validator checks the
complete proposed database, including unused tables, constant routes and
self references. Row/type/decimal checks precede enforced constraints in
declaration order; exact reference diagnostics and untrusted-key behavior
remain unchanged. A validation failure rolls back the source row and every
alias/kernel change.

Snapshot capacity, projected fields, ordered constraint nodes and owned keys
consume the original finite query memory account. Incoming row validation uses
borrowed scalar views without decimal formatting allocation. This scratch is
released after validation. Rollback remains backed by the source table journal,
derivation-count undo and logical pending epoch. Public diagnostic exports and
internal invariant-checker scratch retain separate ownership limitations; see
[memory accounts](memory_accounts.md).

## Prepare, busy reads, and commit

`prepare(update)` validates the input and then keeps three kinds of tentative
state together until close:

1. a source `ReferenceTable::Journal` for the full physical-row change;
2. per-occurrence derivation counts with reverse-order undo entries; and
3. a logical `SupportRuntime::PendingEpoch` containing only native zero
   crossings.

An allocation, adapter, constraint, counter, or work-limit failure during
`prepare` rolls back all three and returns no token. The previous sequence and
public handles remain usable, and the same sequence can be retried. Rollback
can grow free high-water arena metadata while restoring live state.

The facade becomes busy while the token is active. Public state reads such as
`snapshot`, `has_answer`, source/support lookups, derivation counts, storage
statistics, and invariant checking reject with `runtime_busy`; another
`prepare` or `apply` is rejected too. `ready()` reports false and `sequence()`
continues to report the last committed sequence. Immutable plan information,
options, owner identity, and source layouts remain readable.

The token's `preview()`, `support()`, and `snapshot()` methods provide
owner-only diagnostics for the unpublished update. The physical preview
describes the changed source row, alias derivations, and metrics. The support
preview and journal describe local logical support changes. The token snapshot
is an owning diagnostic copy of tentative physical, derivation, and support
state. These views are not full-query answer deltas. A reference returned by
`preview()` or `support()` expires when the token closes.

Callers must finish any throwing output preparation before `commit()`. For a
valid token, commit allocates nothing: it commits the logical epoch and source
journal, drops the derivation undo entries, moves the prepared result, and
publishes the new sequence/readiness. The token destructor, `rollback()`, and
pending-token move operations also use allocation-free cleanup. If caller
output preparation throws, the caller can roll back or let the pending token
destruct; the source, counts, and kernel remain unpublished to facade readers
until that happens.

The token owns a shared reference to the runtime implementation. It remains
usable after a `PhysicalRuntime` facade move or destruction. In particular,
an active token can commit after its facade has been destroyed; the returned
source pin and logical journal keep their retained payloads readable after
the implementation's source/support tables are released.

## Retained source rows and logical journals

For a committed physical source change, `PhysicalPreview.source` contains the
public `TupleHandle` and a pin to the complete physical row. The pin keeps the
row payload readable after a later erase or runtime destruction; it does not
keep the row in the source set or indexes. Exact physical no-ops have no source
change or source pin.

The nested `SupportEpoch` may retain its affected-record `SupportJournal`.
That journal pins the logical tuples it describes and owns before/after
support state and any configured transition trace. Caller-held committed
epochs can therefore remain readable across later physical updates. The
runtime itself retains no prior epoch history. Keeping old `PhysicalEpoch`
objects intentionally adds their source and logical pin counts to storage
statistics. `PhysicalEpoch` is move-only because its source pin has unique
ownership. Pins retain affected payloads; retained arena metadata has its
existing high-water cost and is not a whole-query frozen snapshot.

## Work and resource limits

`PhysicalMetrics.work` charges coordinator work, including source changes,
constraint row/validation accounting, alias visits and derivation changes,
plus the logical `SupportEpoch.metrics.work` delta from each staged native
crossing. The optional `PhysicalRuntimeOptions.work_limit` caps this aggregate
coordinator work. `PhysicalRuntimeOptions.support.work_limit` is also enforced
by the nested logical epoch; either limit can reject the update. The
`derivation_limit` separately bounds each exact occurrence count.

These are abstract work counters. Constraint comparisons and other details of
the full after-state validator, allocator bytes, and elapsed time are not
fully charged. `constraint_rows` reports the source rows materialized for a
full constraint validation, and `constraint_validations` reports that check;
they are not byte, comparison, or latency bounds.

Initialization and inspection have separate limits. `BuildOptions.work_limit`
covers cumulative snapshot validation and construction, including the extra
copy work when rebuilding; it does not replace or reset
`PhysicalRuntimeOptions.work_limit` for later updates. `initialization_metrics()`
reports the build counters. `canonical_state()` returns typed diagnostic state,
and `inspect_invariants(InspectionOptions)` recomputes invariants with its own
work and issue limits. A report is trustworthy only when `complete` is true;
`valid()` additionally requires no issues. The versioned JSON from
`io::write_runtime_state` and `io::write_invariant_report` is diagnostic, not a
checkpoint or restore format. The value types are declared in
[`initialization.hpp`](../include/crown/runtime/initialization.hpp) and
[`inspection.hpp`](../include/crown/runtime/inspection.hpp); the deterministic
writers are in [`io/inspection.hpp`](../include/crown/io/inspection.hpp). The
same inspection and serialization APIs are available on `DeltaRuntime`;
details are in the [runtime initialization contract](runtime_initialization.md).

The frozen plan's `GuaranteeProfile` still describes compilation/storage
construction. Constructing this reference coordinator does not upgrade that
artifact to a certified maintenance or cursor-delay guarantee.

## Validation and integration

`physical_runtime_test.cpp` contains an independent semantic checker. It
recomputes occurrence mappings and derivation counts from source rows, joins
full subtree assignments, and compares survivors, child flags, candidate
membership, parent/visible support counts, and complete results. For its raw
atom cases it also compares with the A04 reference evaluator. SQL-filter and
constraint cases add explicit adapter, unused-table, constant-route, and
nullary checks. This is executable implementation evidence, not an external
mathematical review or a formal proof.

The allocation-injection test exhaustively sweeps each operation's allocation
points through prepare and checks rollback plus same-sequence retry against a
clean run:

| Case | Injected allocation failures |
| --- | ---: |
| Insert creating a new final-native tuple | 204 |
| Erase its last derivation | 124 |
| Insert another full row with an existing final projection | 21 |
| Erase one of multiple rows sharing a final projection | 16 |

The same test checks allocation-free commit, rollback, token destruction,
move assignment, cancellation after facade destruction, and commit after
facade destruction while retaining the returned source pin and support
journal. D01 extended the suite to 45 tests; full D02 now passes all 49 tests
in GCC Debug/Release, ASan/UBSan, Clang18 and a fresh source-only Release build.
See the [fragment-cursor packet](verification/fragment-cursors-2026-11-06.md),
[epoch-view packet](verification/epoch-views-2026-11-06.md),
[D01 cursor packet](verification/result-cursors-2026-11-06.md) and
[physical foundation packet](verification/physical-runtime-2026-11-06.md) for
timings and source fingerprints for those historical checkpoints.

The new delta owner uses a private observer after every native zero-crossing
route and before the next alias. It receives the full physical route ordinal,
adjacent-prefix views and the stage journal interval. Filtered/count-only
routes leave the same logical state and are still included in that ordinal.
All observer cursors/views close before staging resumes. Its bounded spool
and private live image finish before the no-fail physical commit barrier;
observer or later epoch-final output failures use the same whole-epoch undo.
This integration is documented in [delta_runtime.md](delta_runtime.md).
Standalone `prepare`/`commit` do not implement a transactional sink. R06
initialization/rebuild and inspection are verified library APIs. Implemented
[ordered delta scheduling](ordered_delta.md), [query memory accounting](query_memory.md)
and [durable session delivery](session-journal.md) have separate contracts;
their guarantees do not follow from this physical commit barrier alone.
[Epoch views and fragments](epoch_views.md)
cover hidden-variable restrictions, visible C* subtrees and full survivor
assignments at any physical root or an exact factor set.

OrderedReplay uses PhysicalRuntime::apply_view and DeltaRuntime::apply_view for
its native reader values. These prepare/import pending state before commit and
then acknowledge the already prepared source position without allocating.
