# Memory accounts and storage migration

S05 is verified. The current [query memory contract](query_memory.md) defines
the original-account budget, statistics, rollback and caller/export boundaries.
The [acceptance record](verification/s05-native-acceptance-2026-11-09.md) records
all five complete227-test matrices and independent source/binary readback.

## Historical migration overview

This file preserves the scoped migration checkpoints. Remaining-work statements
below describe their recorded checkpoint; use the current contract above for
the completed S05 boundary.

During the migration, S05 was in progress. Native `crown_core` contains the allocation account,
compact owned rows, immutable metadata, tuple arenas and an accounted reference
table. `crown_accounted_indexed` adds optimized storage under the same account.
Both backends include cursors, collections, same-account copies and journals.
`crown_accounted_storage_table` provides native dispatch over those backends
through `AccountedStorageTable`, with compact owned values and borrowed entries.
`crown_accounted_plan_storage` adds `AccountedPlanStorage`, whose public
constructor binds an actual borrowed compiled plan to those accounted tables.
`StorageTable` and `PlanStorage` still use their earlier value interfaces.
Actual Support/Physical/Delta runtimes share a finite memory account for
controls, operation grants and support metadata. Physical source tables, source
pins/owning exports, and derivation keys now use compact accounted storage.
Logical support now uses compact native tables, frozen programs, propagation
values and journal pins under the same owner. View overlay keys/nested maps,
cursor fixed scalars and operational startup/init scratch are funded too.
Retained native program metadata and actual Delta live/index/undo/queue owners
also use the original account. Public result tuples now own compact native
payloads and shared controls under that account, with read-only retaining views.
Snapshot collection controls/capacity and session facade/implementation controls
now use that same account too. Run-context and session-capture outer controls,
and native window facade/implementation controls, are funded. Published event,
transition/derivation capacities and retained journal child flags now use the
original account too. Physical input row/domain validation, enforced constraint
snapshots and projected key storage, and native initialization/rebuild staging
now use that account. Actual window options, label/count rows, expiration/FIFO/
relation nodes, active expansion capacity and prepared controls/update payloads
are funded too. Actual typed queue controls/batches/items/rows/source text and
prepared/committed/stopped progress now share that account. Streaming reader
controls, framing/decoder scratch, cached compact rows, source progress and shared
session input options now use that grant too. Native observation/workload
controls, arrays and immutable workload snapshots now share that grant too.
Native OwnerCapture component/field/distribution/compact-key ownership and scan
scratch now use the original account too. Retained trace/gauge arrays and report controls now use it too. Runtime ranking/
selection evidence/results, other diagnostic/work paths and complete operator
record/byte reconciliation remain open. A query does not yet have complete byte-limit enforcement.
Later sections retain the evidence and limitations of earlier migration
checkpoints; the public-result, session, epoch, constraint, window, typed-input, stream-input and instrumentation sections below record the current boundary.

## Account and ownership contract

[`MemoryAccount`](../include/crown/resource/memory.hpp) has one immutable finite
limit. Copies share that limit. Rows, allocator rebinds, object/control blocks,
tables, cursors and journals receive the same existing account; constructing a
table or copying its state cannot mint another allowance. Mutation uses one
thread or external synchronization.

An admitted allocation charges the actual ordinary `operator new` request,
including the account's own header and alignment allowance. The query controller
also consumes its actual request. Payload bytes, current requested bytes and
historical successful/freed counts are separate. The metric does not include
allocator usable-size, RSS, C++ exception-runtime storage or allocations that
have not been routed through the account.

[`MemoryAllocator`](../include/crown/resource/allocator.hpp) charges actual
standard-container node/capacity allocations. Arbitrary nested owning members
need explicit account propagation. Compact `AccountedRow` owns its scalar
descriptors and binary string bytes in one block, with inline exact decimals.
There is no retained standard `Row` mirror. Layout and projection freezing owns
the fields, binding bytes and mapping/control storage it retains.

[`OwnerAllocator`](../include/crown/resource/owner_allocator.hpp) is the explicit
variant for transferable result storage. Copy assignment adopts the source
account/attribution and funds the new capacity there; move assignment and swap
transfer that allocator with its existing storage. Rebinds preserve account,
purpose and attribution, including packed child-bit buffers. No copy or move
creates another allowance. Maintained tables and record state continue using
nonpropagating MemoryAllocator so another value cannot replace their bound query
account.

## Native public result tuples

Actual runtime `storage::Tuple` results retain an immutable `AccountedTuple`
and an account-allocated shared object/control block. `Tuple::from_accounted`
moves the existing compact row and preserves its layout token and query account;
it does not reimport scalar descriptors or string bytes. `memory_usage()` records
the row's real allocations plus the shared owner's real allocation requests,
including account framing. Shared immutable layout/program metadata is charged
once to the account and is not duplicated in each tuple's payload usage.

`Tuple::values()` returns `TupleValuesView`. A view obtained from a tuple, and
iterators copied from that view, retain the immutable payload without another
allocation. Native tuple copies share that payload. Values, hashes and comparisons
stay readable after the tuple or runtime facade is destroyed, while the retained
owner continues consuming its original finite query budget. A returned scalar's
string view still borrows from its values-view owner; retain the tuple, view or
iterator while reading those bytes. Explicit `TupleValuesView::borrow` inputs
require their source to remain alive. `export_row` and `export_scalar` create
ordinary owning caller values at the explicit external boundary. Standalone
compiler/tool layouts retain their earlier owning Row behavior.

Public native layout/projection descriptors create tuples directly under their
original account and preserve metadata tokens. Public result cursor output,
Delta SQL/scalar mapping and physical derivation payloads use that path. Native
projection avoids a temporary owning standard Row/string mirror. Prepared
commit, output transfer, native copy/view/hash and final release allocate nothing.

The Delta spool sublimit now uses each tuple's actual compact row/shared-owner
request plus each FIFO node's actual allocation request and account framing.
Shared metadata and construction scratch remain outside that spool sublimit,
while consuming the same query account. Prepared spool counters retain high-water
evidence; current account bytes decrease as actual owners release. A caller-held
tuple or view can therefore reject a subsequent update under the original query
cap; releasing it permits a same-sequence retry without changing the allowance.

Session snapshot payload limits use the same native tuple usage. Their outer
collection now has funded immutable ownership as described below. Full S05
acceptance remains open. See the scoped
[public-result evidence](verification/s05-public-tuples-2026-11-09.md) and the
[current handoff](handoff.md).

## Native session and snapshot owners

Session factories return `QuerySession::Owner`, an AccountedUnique whose deleter
retains the runtime's original account. The facade and stable implementation are
real allocator-backed objects under session attribution. Runtime construction
establishes that account before allocating those objects; the session does not
create a second allowance. Creator-thread/reentrancy guards, owned-stream order,
and nonallocating publication/stop/drop/destruction remain in force.

`SessionSnapshot::rows` is a read-only `SessionRows` collection. Its actual shared
object/control and vector capacity allocations use the same account as its native
tuples. `rows.memory_usage()` reports these stored real requests, including
framing. `accounted_bytes` adds them to the native tuple requests, excluding shared
program/layout metadata that is already charged once. Empty row collections
allocate neither a shared collection control nor capacity storage.

Row-collection copies and cross-account handle assignments share or transfer
their original immutable owner without allocating, cloning row buffers or
refilling a grant. Their iterators and references borrow from a live collection
handle. Copying the full SessionSnapshot can still allocate its ordinary progress
map; that graph remains migration work. Native rows and collection ownership
survive session destruction, remain charged while held, and release without
allocation. A caller-retained snapshot can exhaust the original query budget on
another snapshot; release permits a retry at the same committed sequence.

The retained snapshot sublimit includes collection/control/capacity and native
tuple requests. Growing capacity temporarily keeps old and new blocks alive;
both real requests consume the original query account while the sublimit records
the accepted retained storage. Cursor candidates/scratch and shared immutable
metadata also consume that account outside this snapshot sublimit. Row caps can
change the chosen growth capacity, so byte-boundary comparisons must preserve
the same growth schedule.

Run-context and session statistics-context outer shared object/control allocations
are funded too. Native window construction borrows the compiled catalog during
construction and funds its stable facade/implementation controls under the same
session account. Their nested input options, window options/maps/sets/rows and
prepared controls, transport/reader bodies, progress maps and capture graphs
still need routing. Published SupportJournal event, SupportEpoch transition and
PhysicalPreview derivation capacity now have native ownership as described below.

The session-owner evidence records actual exact/one-under caps, retained lifetime,
23/25 persistent snapshot faults, unchanged independent tests, and compiler/
sanitizer scopes. See [session evidence](verification/s05-session-owners-2026-11-09.md).
Whole-query memory-budget completion and full S05 acceptance remain false.

## Funded epoch arrays and retained child flags

Actual `SupportJournal.events`, `SupportEpoch.transitions` and
`PhysicalPreview.derivations` now use OwnerAllocator with the original query
account. Their capacities are real charged allocation requests, including
framing. Pending and no-op result construction bind the allocator before any
growth; empty and trace-disabled arrays allocate no capacity. Vector APIs remain
available, but their allocator specialization is part of the public type.
External ordinary-vector DTOs use explicit iterator-range exports.

`SupportValueState.child_present` also owns an original-account packed bit buffer.
Before/after journal values copy the authoritative native record flags into that
buffer without retaining an ordinary uncharged mirror. Record/snapshot/canonical
diagnostic flag types remain separate external DTOs. Independent test models
likewise export ordinary flags explicitly rather than consuming the query's
allowance for their reference state.

Array and bit-buffer rebind/copy/move/swap preserve their source account and
attribution. Result copies may need a new charged capacity block; moves and
publication allocate nothing even when the receiving result previously belonged
to another query. Source values remain valid after a failed copy. These result
semantics do not change the fixed allocator rules for maintained tables or
operational record metadata.

Retained causal events, transitions, child flags and physical derivations remain
readable and charged after the runtime facade is destroyed. Destroying their
final owners releases the real capacity, native tuple payloads and pins without
allocation. A retained earlier epoch can exhaust the original finite account;
denial preserves the prior committed state, and releasing history permits a
same-sequence retry. Tentative arrays may retain cleared capacity until the
pending owner itself closes; that capacity remains charged throughout.

The new actual-runtime test covers both backends, trace on/off, exact/one-under
history peaks,109/123 persistent failures, allocator rebind/transfers and final
controller-only release. See [epoch-array evidence](verification/s05-epoch-arrays-2026-11-09.md).
Whole-query completion still requires nested input/options/progress/transport/
reader/capture/diagnostic/async graphs, authentic operator record/byte
reconciliation and full native matrices. Operational constraint/rebuild scratch
has the scoped native ownership described next.

## Operational constraint validation and rebuild scratch

Physical updates validate row shape, scalar type and decimal domains through
borrowed native scalar views. Decimal digits remain valid for the entire check;
validation does not create an ordinary formatting string. The immutable catalog
was validated when its compiled program was admitted. Runtime checks use that
same frozen metadata without rebuilding ordinary catalog sets or strings.
The standalone public catalog/reference checker keeps its existing contract.

After-state constraint checking takes native compact source snapshots, including
unused tables and self references. Snapshot capacity, projected scalar capacity,
ordered unique/FK key nodes and owned key payloads consume the original query
account with scratch attribution. Child FK probes borrow projected fields;
there is no internal ordinary whole-Database/Row/string mirror. All rows are
checked before constraints, and enforced constraints retain declaration order,
exact diagnostics, binary comparison and empty-key behavior. Untrusted keys
remain hints. Constraint-free and no-op updates retain their existing bypasses.

Initialization borrows the caller's external Database, validates through native
scratch and imports compact native rows/seeds. Rebuild captures native source
rows under the same existing account and sorts full rows to preserve deterministic
reference input order in either backend. The old owner, snapshot scratch and
unpublished replacement share one finite allowance. Original cumulative work
precharges are still consulted before copying. Denial releases partial scratch
and replacement state while preserving the old committed owner and sequence.
Public snapshot/canonical exports and internal diagnostic checker scratch are
separate remaining ownership boundaries.

The actual-runtime constraint_memory test covers both backends, all five scalar
types, 38-digit decimals, long binary keys, trusted/untrusted and empty keys,
reference diagnostic parity, exact/one-under caps, persistent failures and
same-input retry. Allocation counts reconcile real engine requests against the
original account. These are scoped checks; they do not establish whole-query
memory enforcement. See [constraint evidence](verification/s05-validation-scratch-2026-11-09.md).

## Native operational window ownership

Query sessions pass their existing MemoryAccount into WindowController. Its
compact label/count rows, expiration/global/relation FIFO nodes, active watermark
capacity, transient preflight cursors and Prepared object/update payload all use
that same account. There is no ordinary operational Row/string/container mirror.
The original session outer controls retain session:0 attribution; nested window
storage uses session:1. WindowTables owns real immutable control/capacity storage;
AccountedWindowOptions copies share it without allocating, including in retained
SessionRunContext values after facade destruction.

WindowOptions remains the caller input DTO. options() returns a read-only
AccountedWindowOptions reference. Prepared::update() returns a borrowed
PhysicalUpdateView over its own compact payload, which stays valid until that
Prepared owner is destroyed, including after publish. DeltaRuntime::begin_view
borrows input only during admission and imports native ownership before returning.
External PhysicalSetUpdate paths use the same native boundary. Canonical window
labels/counts/active commands remain explicit owning external DTO exports.

WindowMetrics.accounted_bytes and max_accounted_bytes describe native retained
payload/index descriptors and active-command capacity. Their numbers differ
from the earlier ordinary Row-capacity estimate. They remain a component sublimit;
the original query account additionally funds real allocation framing, tree links,
controls, temporary rows and preparation overlap. It does not mint a new allowance
for window data or retained option handles. Standalone controller construction
has its own account; query sessions always use their explicit original account.

Preparation preserves full-row duplicate reference counts, global/per-relation
FIFO and complete watermark preflight. Only the last expansion step acknowledges
the command/watermark. Denial releases tentative nodes/payload/cursors/expansion,
leaves committed physical and label state intact and permits same-input retry.
Publication, stop and teardown allocate nothing. Stop frees actual expansion
capacity while retaining committed prefix scalars. Published prepared values and
copied native options retain their original charged ownership after facades close.
See [window memory evidence](verification/s05-window-native-2026-11-09.md).
Whole-query completion still requires transport/reader/input/progress/capture/
diagnostic/async ownership, authentic operator record/byte reconciliation and
complete native matrices.

## Native typed input and accepted progress

Typed query sessions construct TypedQueue from their admitted CompiledProgram.
A thin crown_plan bridge derives both the original account and immutable source
catalog owner; core storage does not link back to the planner. Queue control,
intrusive batch/item owners, compact row payloads and source text consume that
same finite grant. Offered TransportBatch construction is a separate external
DTO boundary. Full or failed import leaves that caller batch intact; success
empties it only after every native allocation and byte reconciliation succeeds.
No ordinary retained InputItem/Row/string shadow exists after native admission.

Exact request preflight covers real batch/item framing, row descriptor/string
blocks and source bytes/terminators. AccountedRow copy and preflight share one
sizing implementation. The actual current-byte increase is checked before queue
publication. QueueStats.accounted_bytes and QueueLimits.bytes now describe those
retained native requests; numerical values change from the earlier ordinary DTO
capacity estimate. Fixed queue/progress/catalog ownership and temporary source
nodes are additional, funded requests under the same original query limit.
BatchLimits.bytes still bounds the offered external DTO footprint.

Peek returns stable InputItemView/Native event/window views. Native validators
preserve envelope/row/field/source diagnostic order without decimal formatting
allocation. Permanent malformed-row shape/type/domain/scalar issues can be
retained as deferred diagnostics instead of unusable Row payloads. They still
fail only when they reach the head; semantic errors are sticky, while allocation
failure and engine rejection retain the same head for retry. Native window and
physical/delta admission use borrowed fields until native ownership is imported.

InputPositions/AccountedInputProgress funds actual map controls/nodes/key text
under session:2. Detached source nodes prepare before engine work. Ack links a
node or changes an offset and never allocates. Value snapshots deep-copy under
the source's original account, with strong copy assignment; moves/close/stop
transfer storage without allocating or minting a budget. Accepted native progress
survives facade destruction, and final release returns actual charged storage.
Batch/item destruction detaches chains iteratively to bound teardown stack depth.

Session hot-path sequence checks read native progress without exporting a map.
Public progress/snapshot DTO exports remain explicit external boundaries.
EventReader now also retains native framing/decoder/cached row/progress storage.
Both source modes move native progress through the session footer. Standalone
queue/reader CatalogSource construction has its own adapter account; query
execution uses the compiled-program constructor. See
[typed-input evidence](verification/s05-typed-input-2026-11-09.md). Whole-query
acceptance also needs instrumentation/capture/report/diagnostic/async ownership, authentic
operator record/byte reconciliation and complete native matrices.

`MemoryBlock::usage()` and allocator `allocation_usage(pointer, count)` return
stored real requests. The allocator lookup requires a still-live adapter
allocation and its original count, such as vector capacity. It does not inspect
arbitrary addresses. Standard-container node lifetime classification instead
searches the account ledger for a live value address without dereferencing that
address. This costs O(outstanding account allocations). The reference backend
uses that explicit cost during undo. Optimized nodes store their actual typed
allocator and use `set_allocation_lifetime(pointer, count, lifetime)` with the
original live allocation/count. This validates the allocation header and
updates its existing ledger partitions directly in O(1). It performs no ledger
scan, allocation or allowance refill.

## Native table and journal behavior

[`AccountedReferenceTable`](../include/crown/storage/accounted_reference.hpp)
owns accounted ordered primary/ID maps, secondary key maps and membership sets.
Its State/control, cursors, journal reader/control, undo list, projected keys and
temporary preparation buffers also use the account. Table and arena attribution
comes from their actual native owner IDs. Legacy and accounted owners share the
same monotone authorities. Binding the remaining compiled operator identities
is still runtime integration work.

Insert prepares detached primary, ID and secondary nodes before allocating the
arena row. Once preparation succeeds, publication links already-owned nodes.
Single-operation allocation failure releases temporary ownership and preserves
existing row addresses, IDs and index membership. Historical allocation/peak
counters record actual temporary requests even when the operation fails.

A journal retains affected rows with pins and extracts ordered-container nodes
for deletion. Undo reinserts those same nodes and revives the original pinned
arena generation without allocation. Tentative handles remain private; rollback
may reuse their IDs. Real mutation invalidates existing cursors, including when
the mutation is later rolled back. A journal cursor is invalid after rollback;
commit preserves its usual revision fence.

Reference-table commit closes the writer but retains its change payloads and
detached nodes until journal destruction. Optimized commit releases detached
structural nodes/keys and retains the pinned change payloads and inert undo
history. Multiple committed histories are counted separately. An active journal
can retain unpublished state after its table facade is destroyed and still roll
it back; ordinary cursors reject the destroyed facade.

Snapshots, keys and handle collections returned by the accounted table use
accounted containers. Deep exported tuple values have a derived output owner
and retain the same account. `snapshot_copy()` creates a fresh table owner under
that account, preserving logical tuple/index IDs and revision. Existing and new
state must fit together within the one limit while the copy is built.

## Optimized table work and ownership

[`AccountedIndexedTable`](../include/crown/storage/accounted_indexed.hpp) reuses
the indexed hash-directory and intrusive live-list algorithms. Its table State/
control, rows, keys, memberships, indices, directory blocks, arena, undo records,
cursor state and owning exports use the layout's existing account. Shared
templates retain their legacy allocator/error defaults for the earlier backend.
The optimized directory owns an accounted pointer block whose release does not
walk historical capacity. Payloads use compact `AccountedTuple`; no standard
`Row` mirror is retained.

Ordinary indexed calls borrow a finite `IndexWorkAllowance` with fixed
diagnostics enabled. Each admission checks all five work domains before
consuming any of that admission. A denial does not refund previously consumed
work. [`AccountedIndexWork`](../include/crown/storage/accounted_index_work.hpp)
funds an owning grant/control through the same query account. Copies share the
exact remaining allowance. Composed table journals must receive that same
handle; a journal cursor rejects another grant. No table or cursor creates a
replacement allowance.

Journal growth prepares replacement entry storage privately. Publication moves
already-owned entries and appends the prepared record only after the mutation
succeeds. Failed growth leaves both logical state and current allocated-byte
partitions unchanged. Rollback restores original row generations and live-link
order without allocation or another work admission. Successful tentative
operations may retain reusable capacity after rollback.

Live cursor startup uses fixed state. Each successful `next`, including end
detection, admits one live-link step; it performs no hash, ID lookup, payload
copy or allocation. Explicit invariant checks may scan high-water directories
and retained histories and are separate from ordinary operational grants.

## Native accounted dispatch

[`AccountedStorageTable`](../include/crown/storage/accounted_table.hpp) stores a
variant of the two accounted backends. Construction takes an existing frozen
layout and optionally explicit indexed component limits. It allocates no
dispatch control, creates no account/grant and retains no standard `Row` mirror.
Probes, collections, pins, copies and index operations keep the selected backend.
Reference live traversal keeps lexical order; indexed traversal keeps live-link
order. The returned entries borrow the same native tuple objects.

Indexed ordinary calls require the caller's finite fixed-diagnostic grant.
Reference calls retain their existing work contract. A journal's optional
reference grant or required indexed grant must belong to the table's account.
Indexed journal cursors retain that exact owning grant and reject a replacement.
Two dispatched journals can share one grant; exhausting it in one transaction
does not create another allowance for the second table. Rollback consumes no new
work and does not refill spent work.

Dispatch memory statistics preserve the underlying reference/indexed report in
a variant, without inventing another owner or summing shared metadata again.
The reference backend now exposes its existing arena record counters directly
for O(1) `arena_statistics()`. Returning table values/metadata from a temporary
owner is rejected by lvalue-qualified/deleted borrow overloads.

The maintained physical source and logical support paths now adopt this
interface. Complete query metadata, overlay/export and downstream ownership and
full native acceptance remain open.

## Accounted compiled-plan storage binding

[`AccountedPlanStorage`](../include/crown/storage/accounted_plan.hpp) borrows a
`PhysicalPlan` during construction. It retains its route, fixed identity bytes,
accounted frozen layout/projection tokens, numeric relation/index bindings and
accounted native tables. It retains no original `PhysicalPlan`, standard Row
mirror or source span. This is storage metadata; the complete IR/catalog/query/
normalization graph is still separate runtime integration work.

The funded construction registry preserves layout aliases. Source layout IDs
must match the canonical inventory and exact source tokens. Shared projection
tokens stay shared; descriptor-equal projections with distinct tokens remain
distinct. Every table and index uses its corresponding frozen token.

Construction and `snapshot_copy()` borrow one fixed-diagnostic indexed grant
no larger than the compiled operation allowance. No table receives a replacement
grant. Initialization charges token scans, descriptor fields/binding bytes,
controlled handle-array words and native storage steps. Metadata compilation
and its standard-container internals are separate from the ordinary indexed
path guarantees. Reference work keeps its existing contract.

A snapshot copy shares immutable metadata and creates new table owners and
instance buffers under the same existing account. Both old and new state must
fit during construction. Move assignment transfers differing allocator owners
without allocation; it does not perform an allocating unequal-allocator vector
assignment. Borrowed table/layout/projection/identity access rejects temporary
owners. Retained native pins keep required frozen layout bytes charged after
all storage-binding objects are destroyed.

`PlanStorageMemoryStatistics` separates the real shared metadata owner from the
instance-buffer owner; `owned` sums those two once within that report. Native
table/arena payloads are reported by each table. Copies expose the same metadata
owner, so aggregate reports must deduplicate that physical owner. The tracer
checks metadata + instance + tables/arenas + owned input rows + controller against
the account's actual current requests. Historical temporary requests remain in
allocation/peak counters after failure releases their current ownership.

The real compiled-plan test invokes the public constructor for reference and
indexed plans, including SQL-normalized aliases, exact scalar rows, index/key/
bucket identities and sparse copies. The allocation tracer's test-only borrowed
description invokes the same native constructor implementation without linking
the SQL compiler into its three memory profiles. The construction shim is absent
from production libraries. Full runtime adoption and query accounting remain open.

## Live, retained and reserved state

`TableMemoryStatistics` and `AccountedIndexedMemoryStatistics` report logical
records and actual ownership. The indexed report retains the existing component/
action counters and adds table/arena/directory bytes and retained history entries.
Physical table and arena owners are reported separately, then summed once.
Shared frozen metadata and exported collections have their own owners in the
query account. Lifetime categories describe physical allocation ownership;
they do not imply that every field of a retained shared control is logically live.

Arena reports distinguish live and retained values/slots, reusable free slot
metadata, exhausted generations, State/control and actual directory allocation.
Directory spare payload is part of its one existing allocation. Erase removes
logical membership immediately; the last pin releases a retained row. Free
slot metadata and directory high-water capacity stay physically charged until
real deallocation. Weak shared controls likewise remain charged until their
final weak release. Lifetime classification never refills the limit.

The invariant check uses no new bookkeeping allocations. It validates primary,
ID, arena and projected membership consistency and actual account partitions.
It is an explicit diagnostic, not an ordinary indexed operation.

## Verification boundary and remaining work

The native fixture retains all 26 earlier component checks and five reference-
table/ledger checks, five optimized checks, two native dispatch checks and two
compiled-plan storage checks (40 total). The reference fixture fails
all 91 observed positions across 13 operations. The optimized fixture fails all
104 observed positions across 23 operations, including private journal growth;
zero-allocation operations have zero positions. Both check measured exact/
one-byte-under admission, smaller retries, replacement chains, multiple histories,
retained ownership and a 256-step legacy-table differential model. Optimized
tests also cover 44 work boundaries, all nine component limits, fixed diagnostic/
overflow denials and eight-live traversal after populations of eight and 64.
See the historical [reference storage record](verification/memory-storage-2026-11-08.md)
and the [optimized storage record](verification/memory-indexed-2026-11-08.md).
Dispatch additionally fails all 134 observed positions across seven operations
per backend, and checks borrowed addresses, output ownership, retained teardown,
foreign-grant denial and composed work exhaustion. See the
[dispatch record](verification/memory-dispatch-2026-11-08.md); its local records
use the `s05-accounted-dispatch-` prefix under `build/verification/`.
Compiled-plan fixtures add persistent constructor/copy failure, alias/source/
pin lifetimes, cross-account moves, five initialization work boundaries and
measured exact/one-under peaks. The [compiled-plan record](verification/memory-plan-2026-11-08.md)
accepts all 14 selected tests in four modes, including the real compiled-plan/
SQL path. Complete native runtime gates are still pending.
The complete native runtime suite remains pending.

The remaining S05 work includes completion of runtime value-view migration,
complete plan/IR/catalog metadata ownership, exported support/physical values,
remaining delta/session state and cursor/capture/output/rebuild/async lifetime,
authenticated operator attribution and record/byte reconciliation. Existing
logical row/output/work limits do not establish a complete query memory limit.
Full native query failure/churn/overflow checks and the complete native matrix
remain required before S05 can be verified.


## Actual runtime owner and support metadata

`SupportOptions::memory_limit_bytes` defaults to 256 MiB. Construction creates
one account for reference as well as indexed plans. The existing private work
context now owns that account independently of its optional indexed policy.
Support, physical and delta implementations use accounted shared controls.
QuerySession forwards the same runtime options and exposes its runtime's routed
statistics while the runtime exists. `accounted_memory_statistics()` is scoped
to actual routed allocations; its name is not a whole-query coverage claim.

A fresh indexed operation funds its lease and one `AccountedIndexWork` control
through that account. Nested and resumed work reuses the same remaining grant.
Compact sources use the canonical fixed-diagnostic allowance. Legacy support
uses a private nonowning diagnostic view of that same canonical balance. Its
union stores a root pointer instead of another remaining allowance. It creates
no allocation, copied limit or refill. The lease owns the canonical control for
the entire borrowed view lifetime; compact cursor grant identity stays exact.
Reference operations retain the memory owner and allocate no indexed grant.
The outer guard breaks the active-context/lease cycle. A closed pending token
may retain its original lease until the token is actually destroyed, and those
bytes remain charged. Rollback and commit never replenish a grant or a limit.

Rebuild creates a separate target work context under the original memory account.
Old/new routed runtime state must fit together. A caller cannot substitute an
unrelated account in the private rebuild path. This currently includes the
migrated ownership below; materialized source rows and remaining legacy rebuild
buffers still need their own migration before it is a full rebuild peak cap.

Actual support node records, exact counter maps, byte-valued child flags, node
arrays, child/incoming routing arrays, pending/applied arrays, undo pointer arrays,
undo objects and SupportJournal shared controls now allocate through the account.
Their nested legacy tuple/trace/output members are separate remaining work.
Node metadata receives privately generated component IDs. Saved flags preserve
the original node allocator/purpose/attribution; extracted map nodes retain the
same allocator. Their lifetime classification changes to retained and back to
active without moving ownership to a different journal allocator. Undo restores
the original nodes and flags without allocation. Standard map node classification
uses the documented O(outstanding account allocations) ledger search; this is a
known cost of the present metadata bridge, with no uniform runtime speed/delay
claim. Typed direct allocation handles remain a possible later replacement.

Custom memory limits survive logical trace, immutable observation configuration,
session run-context, cursor and statistics/explanation exports. The default stays
implicit in existing report bytes; pinned v2 fixtures and original checkers stay
unchanged. Schemas admit the optional custom setting.

The actual-runtime fixture checks exact/one-under routed epoch peaks, persistent
allocation failures, allocation-free undo, retained owners, no-op/churn, shared
rebuild accounts and public session forwarding. This owner-stage evidence
preceded the compact physical/support adoption below. Complete retained program
freezing, imported queue/output ownership, operator reports and full S05 native
acceptance remain open. See the scoped
[runtime adoption evidence](verification/runtime-memory-2026-11-08.md).


## Compact maintained physical sources

PhysicalRuntime now selects `AccountedStorageTable` for both compiled backends.
It freezes the physical source layouts under the existing query account and
owns no earlier source StorageTable or standard source Row mirror. The source
array, legacy descriptor handle array, derivation map arrays/nodes and compact
`AccountedRow` keys, physical pending control and count undo array are funded.
Per-table limits and ordinary native index work remain enforced. Source metadata
fields, binding bytes and controlled array words use the shared finite work.

`SourceRowChange::retained` is an `AccountedTupleArena::Pin`; `tuple()` borrows an
AccountedTuple. `get_source()` returns a move-only owning AccountedTuple under
the same account with output attribution. RowView supports borrowed comparisons
with the public Row without allocating. Explicit `export_scalar/export_row`
create standard owning values only at remaining legacy/presentation boundaries;
those allocations are not silently counted as funded. Binary strings and inline
exact decimals preserve their values across this boundary.

Source routing still exports a transient Row for the earlier compiled adapter
and support APIs. Legacy PhysicalPlan and source-layout metadata descriptors
remain retained. `source_layout()` still returns the legacy descriptor used by
current capture/metadata consumers; the actual compact row's `layout()` returns
its funded frozen token. Full plan/program, support, delta/session and output
ownership remains in progress. Do not infer a full query or rebuild peak cap.

Deleted count keys and extracted map nodes keep their original account/purpose/
attribution while their lifetime changes to retained. Rollback restores those
same nodes/keys and physical arena generations without allocation or another
work grant. Map-node classification retains its explicit ledger-scan cost.
Fixed native index/reference failures format the established public Error only
after operation locals and prepared state unwind; memory failures stay fixed.

Actual source fixtures retain an 8 KB binary payload in an ignored physical
column, exercise exact/one-under admission with a smaller successful retry,
retain pins after facade destruction and check final routed deallocation.
Integrated physical propagation also fails every allocation position and retries
for both backends. Fixture peaks include testing runtime controls and are not
universal production peaks. See the scoped
[compact source evidence](verification/compact-sources-2026-11-08.md).


## Compact maintained logical support

Actual SupportRuntime now uses AccountedPlanStorage and native compact tables,
propagation tuples and retained journal pins for both backends. Frozen node/edge/
enumeration arrays and their construction memo use the existing query account;
array words and reservations consume its canonical finite native work grant.
Journal record/writer arrays, pending/transaction controls, cursor/frame/condition/
lookup/probe-child buffers and view controls/patch arrays are funded. Each native
journal tuple uses the borrowed authoritative relation_layout() token.

Current focused Debug resource checks pass exact/one-under epoch and concurrent
cursor peaks, preserve existing leases through denied cursor construction,
release partial controls, admit smaller retry and release the account to its
controller after final retained owners close. Rollback preserves exact canonical
state and compact payload ownership; native reusable capacity remains charged
and must stabilize under warmed churn. Persistent upstream fault sweeps and
no-allocation rollback assertions remain active.

All 48 selected integration names pass four incremental configurations,
including ASan+UBSan/leaks and original strict report/CLI fixtures. Full S05 remains
open: original plan/catalog/query/SQL metadata and legacy output descriptors,
public outputs and child-flag exports, remaining metadata/capture/diagnostic
buffers, delta/session/queues/output/rebuild buffers
and complete operator reconciliation/native acceptance still need migration or
validation. The compact source adapter still explicitly exports a temporary Row.
See [support evidence](verification/compact-support-2026-11-08.md).


## Funded cursor/view overlays and bindings

Actual before-view map/set nodes at every level and full/projected key copies now
use the original account. Keys own AccountedRow; transparent RowView probes avoid
standard Row exports. Fixed bindings likewise own compact scalar/byte copies;
duplicate bindings compare borrowed scalar views. Cursor fragment/variable/map/
stack and initialization postorder/stack scratch are funded. Nested maps and empty
outer contexts receive explicit allocators. Patch::memory returns an account by
value so no reference escapes a temporary allocator.

New direct tests charge 8,194-byte binary bindings and full/nested index overlay
keys, pass measured exact/one-under peaks, preserve prepared state and existing
canonical state after denial, roll back without allocation, admit smaller retry
and retain ghost/direct results after input/facade destruction. All 48 selected
integration tests pass four incremental modes including ASan+UBSan/leaks and
original strict report/CLI fixtures. See [overlay evidence](verification/cursor-overlays-2026-11-08.md).

Full retained program/catalog/query/SQL/identity JSON and output descriptors,
public output/child-flag/capture/diagnostic buffers, actual input-adapter and delta/
session/queue/output/rebuild/async ownership and complete operator reconciliation/
native acceptance remain open. No complete query memory cap is claimed yet.

## Native streaming input ownership

Query sessions derive EventReader account/catalog authority from their admitted
CompiledProgram. AccountedInputOptions owns real immutable control/map/key/source/
null-token storage under session:2 and is shared with SessionRunContext. Framing
capacity, JSON token/metadata/column scratch, binary/delimited cells, CSV header
permutations, cached compact rows, source bytes and prepared/accepted progress
consume that same finite grant. There is no ordinary operational Row, JSON DOM,
string shadow, accounting-only ticket or replacement execution allowance.

Native JSON parsing uses the fixed event schema to bound nesting, with native
UTF-8/escape/number/scalar decoding. InlineDecimal::parse and fixed SHA-256 output
avoid ordinary coefficient/digest strings. Canonical catalog serialization uses
funded capacity. Lookup borrows the already admitted immutable catalog rather than
revalidating it with ordinary scratch on every record. Public DTO codecs keep
their independent parser and wire encoding. Schema/domain/binding/limit/source
codes retain their behavior; malformed native JSON syntax has a stable
invalid_document message rather than third-party parser internals.

Peek prepares a complete owned event and source-map publication before returning
a stable InputEventView. Only explicit acknowledgement advances accepted progress.
Reader parse/order/allocation failures remain sticky and require explicit source
recreation; engine rejection keeps the same cached event for retry. Ack, native
close, session stop and publication allocate nothing. Value progress snapshots
clone under the source grant; native stopped progress and immutable options can
outlive the reader/runtime without ordinary retained DTO mirrors. Session public
progress/snapshot exports are explicit caller boundaries. OrderedReplay uses
native physical/delta apply_view and funds its own shell from its reader account.

See [stream-input evidence](verification/s05-stream-input-2026-11-09.md). Actual
all-eight-format tests reconcile upstream requests, exact/one-under query caps,
persistent failures, retained ownership and controller-only final release. This
is scoped progress. The instrumentation section below records the subsequent
observer/workload migration. Other retained capture/report/diagnostic/async graphs,
authentic operator record/byte reconciliation and complete native acceptance
remain open.

## Native observation and workload ownership

SupportRuntime passes its original StorageWorkContext account into the one
ObservationState shared by physical/delta/session wrappers and into its inline
workload State/Collector. ObservationState shared control/object and fixed trace
capacity use observation:0. Workload routes, retained descriptor/committed/attempt/
previous arrays and candidate configuration requests use observation:1. Numeric
immutable workload Snapshot control/arrays use capture:1. No operational shadow
vectors, accounting-only capacity ticket or replacement execution allowance is
created. Private standalone Collector/State adapters have their own explicit
component account; query execution always supplies its existing grant.

Quiescent configuration prepares all candidate routing/descriptors/cells before
publication. Equal fixed allocators make the final swaps nonallocating; denial
preserves old options, history, accepted epochs and capacity. Off configuration
releases working arrays. Observation hooks and collector admit/nest/finish/reset/
rotation do not grow arrays. Publication, reset and cleanup allocate nothing.

Factory workload snapshots own real numeric arrays and a funded program alias.
Copies of a public snapshot handle retain its immutable storage without allocation.
Fresh capture and the private pending-session copy allocate under the original
grant; the public pending path funds both temporary and retained graphs. Failed
capture/copy leaves the old query and returned snapshots intact. Snapshots remain
readable after runtime/session destruction, and final release returns all charged
storage. MemoryAccount still uses global operator new, so existing failure
injectors cover these native requests too.

Snapshot::memory() continues to report the mutable collector's object and real
capacity payloads, including routes. Native allocator headers, temporary old/new
configuration overlap and retained snapshot copies are additional real requests
under the query cap. Component payload figures are not whole-query/peak bytes.
See [instrumentation evidence](verification/s05-instrumentation-native-2026-11-09.md).
The owner-capture section below records the subsequent component/distribution
migration. ObservationTrace exports, CombinedCapture and retained session/report/
evidence payloads still need ownership disposition/funding. Authentic record/byte reconciliation, asynchronous/
diagnostic/invariant graphs and complete native matrices remain open. S05 and
whole-query memory acceptance remain false.

## Native owner captures and distribution scans

OwnerCapture now retains its real component capacity, copied ordered FieldIds,
histogram/top-K buffers and compact heavy-key rows under its CompiledProgram's
original query MemoryAccount. Attribution capture:2 identifies these arrays and
rows. Weighted builder controls and scan list nodes also use that account; keys
are gathered directly into one AccountedRow block, including binary string bytes
and inline 38-digit decimals. There is no retained ordinary Row/string mirror.
Plan/layout values share already-funded immutable metadata.

CapturedSelection, CapturedDistribution and CapturedKey provide the query-owned
read interfaces. CapturedKey::view borrows from that key; retain the capture/key
while reading it. Deep capture copies allocate under the source's same account.
Copy assignment stages the complete value before moving it into the destination,
including across different query accounts, so denial preserves the destination's
old stamp/facts/account. Caller OwnerRequest/Selection and standalone projection/
index Capture/Distribution values remain explicit ordinary DTO boundaries.

C01 work/row/distinct/logical payload limits retain their named report meaning;
actual native rows, allocator framing, controls, capacities, held captures and
old/new overlap also consume the original query cap. Failed scans/copies release
tentative storage and preserve the accepted epoch and older captures. Partial
logical-budget exhaustion still publishes no prefix NDV/histogram/top-K. Retained
captures remain readable after runtime destruction and release all charged data.
Pending captures retain only metadata. Reference pending reads allocate nothing;
indexed reads acquire the existing temporary work grant's two real object/control
requests. Both grant-denial positions preserve pending/accepted state. Rollback
and final release allocate nothing.

See [owner-capture evidence](verification/s05-owner-capture-native-2026-11-09.md).
The retained-report section below records the subsequent control/trace/gauge
migration. Runtime ranking/selection evidence and other diagnostic/work paths,
authentic operator record/byte reconciliation
and complete native/overflow/no-op/churn matrices remain open. S05 and whole-query
memory acceptance remain false.

## Native retained trace, gauge and report graphs

CapturedObservationTrace copies live numeric records directly into original-account
capacity (capture:3). CapturedStateGauges funds node/base arrays (capture:4).
CombinedCapture, ModeDescriptor, PlanExplanation and StatisticsExplanation fund
both object/shared-control storage under capture:5/6/7/8. SessionStatisticsContext
keeps its existing capture:0 control and now retains native trace/combined children.
No ordinary trace/gauge export mirror is retained inside the query/report path.
All nested values derive the same existing CompiledProgram account before moving
factory arguments. Compiler-only PhysicalPlan reports have an explicit standalone
component account; reports from admitted CompiledProgram values retain that
program's original grant.

Shared report-handle copies allocate nothing. Native trace/gauge value copies
allocate their real arrays under the source account; staged copy assignment also
preserves old metadata/arrays when copying between query accounts fails. Held
reports remain readable after runtime/session closure and release all charged
data. Every allocating capture prepares private storage before returning a value;
failure preserves accepted epochs, pending state and older reports. Session
live/pending/stopped/dropped captures retain their established visibility rules.
Dropped sessions export no fresh trace records or runtime gauges. Legacy v2
capture still requires C01 collection off; C01 captures do not invoke the legacy
gauge scan. No clock/sampling/order/availability/schema contract changes.

ObservationTrace, CommittedStateGauges and standalone table/text exports remain
explicit caller values. Caller-supplied immutable proof/family/benchmark handles
are distinct from query-created copied payload. Numeric cursor/configuration/
summary values remain fixed or funded aliases. Encoded byte caps are separate
from the query's actual allocation cap. Unsupported legacy total-memory facts
remain unavailable; authentic operator record/byte reconciliation is still open.
See [report graph evidence](verification/s05-report-capture-native-2026-11-09.md).
Ranking result/selection storage and remaining diagnostic/work paths need
disposition/funding, together with complete native/overflow/no-op/churn matrices.
Whole-query S05 acceptance remains false.

## Native runtime ranking evidence

Runtime ranking capture now derives the original account from the admitted
CompiledProgram. Evidence object/shared-control storage, retained binding and
weight/source/observation arrays use capture:9. RuntimeEvidence object/shared
control uses capture:10. Both binding encodings and census/source bitmap/root
scratch use the same existing grant, with scratch classified separately from
retained capture storage. Fixed 38-digit decimal formatting creates no temporary
ordinary string. Fixed source-selection storage is bounded at the established
256-component capture limit and is borrowed only during the synchronous call.
OwnerRequest DTO overloads remain available. Retained captures keep native
copies, never the borrowed request span.

EvidenceVector/ EvidenceText use OwnerAllocator so even empty values bind the
source account; immutable Evidence/RuntimeEvidence handles share storage without
allocation. Failed capture returns allocation_failure with no evidence and
restores private storage, preserving accepted/pending owner state and older
evidence. Retained evidence stays readable after owner closure and releases all
charged storage with its last alias. The actual test reconciles every upstream
request with original-account requests, sums retained capture attributions0..10,
exercises exact/one-under caps after hoarding genuine captures, retries at the
same cap after release, and faults every request on both storage backends.
Frozen binding bytes and logical admissions remain independent of actual byte
admission. [Evidence](verification/s05-ranking-evidence-native-2026-11-09.md).

Ranking score/result vectors/text/lowering and runtime/planner selection graphs
remain open, as do authentic operator record/byte reconciliation, remaining work
paths and full native/fresh-source matrices. This checkpoint does not establish
whole-query S05 acceptance.

## Native ranking results and physical selection

C02 Result controls, CandidateScore inventories, all score/decimal/key text and
depth/population/slot-term arrays now use the original account (capture:11).
C05 Selection controls, captured DirectCQ policy and constraint text, assessment/
decision arrays and cache keys/nodes use capture:12. CurrentSelection controls
use capture:13. All binding, ordering, canonical-JSON visitor and native compiler
scratch uses the receiving account as well. Empty/SBO result text and empty
containers retain that allocator. Shared result-handle copies allocate nothing.

New candidate programs are CompiledProgram graphs. Replanning reuses checked
candidate validation and immutable admitted source/identity fields, preserving
complete physical formats, work counts and layout/projection aliasing. It retains
the canonical source owner, so replacing a plan does not retain a chain of old
graphs. Explicit supplied compiler/proof/family/cache artifacts remain immutable
input aliases; freshly generated programs and copied result payload are funded.
Source/request/PhysicalPlan/physical-JSON exports are explicit caller operations.

Native runtime/session factories deep-admit compiler/cache programs into one new
query account; the source can close independently. Indexed program admission,
mutable table initialization and live bootstrap share the same outer operation
grant. Native compiler metadata uses compiler counters and logical lowering/
identity/replay/normalization limits, separately from execution's advertised update
allowance. Creating a compiler artifact cannot bypass later execution admission.
Pure DirectCQ without evidence is the initial compiler API; its compiler workspace
precedes execution admission, and its published artifact uses a component account.

Cache keys/nodes retain the account that funded their insertion. FIFO movement,
publication, clear and final graph release allocate nothing; cleanup is iterative.
A cache hit can alias a previously funded immutable program from another query.
New selection/capture/result payload still consumes the receiving owner's cap.
Allocation denial preserves the previous epoch, older results and cache FIFO/
counters; held results survive owner closure and release their charged storage.

Actual C02/C05 memory tests reconcile every new request with original-account
requests on both backends, exercise every persistent failure position, retained
lifetime, exact/one-under caps and same-cap release/retry. C05 additionally covers
direct/compiler/native sources, dual assessment, cache hit/miss/disabled/eviction
and session boundaries. An admission-only work allowance proves initialization
does not refill the grant. See [the current handoff](handoff.md) for the precise
accepted source/check scope. Authentic operator record/byte reconciliation,
remaining diagnostic/work paths and full native/fresh-source acceptance remain
open; S05 whole-query acceptance is false.

## Actual operator record and byte reconciliation

Native Support/Physical/Delta/Session memory reports now join actual operator
counts to the original account's allocation owners, table/index statistics and
tuple-arena lifetimes. Result and scratch storage use capture:14. The captured
owner, purpose and lifetime partitions sum exactly to the whole account; each
table/arena owner joins that partition. The report includes its own resident
storage after diagnostic scratch closes, and remains readable after runtime
closure. Account-wide bytes can include older held generations; operator counts
describe the captured current runtime. Shared bindings do not duplicate bytes in
the owner partition. The Delta coordinator now uses delta_node:UINT64_MAX rather
than colliding with factor0.

Pending/released owners omit committed operator/table facts. Hidden E and
unmaterialized live images are unavailable rather than fabricated zero counts.
Finite diagnostic work/owner/table/operator caps and original-account byte caps
produce a fixed stop without a partial report. All persistent capture faults,
exact/one-under caps, original upstream allocation requests, held lifetimes,
retained/free journal records, churn, wide/composite values and SQL cases are
checked on both backends. See the [public contract](memory_reports.md) and
[current verification scope](verification/s05-operator-memory-native-2026-11-09.md).

The separate version1 JSON and CLI memory-json format are explicit caller-owned
exports. Their output-byte cap is checked before publication after construction;
it does not fund or bound ordinary JSON export temporaries. Existing schemas and
report meanings remain intact. Remaining invariant-report issue graphs and
independent expected-state maps/sets/row scratch are still ordinary owning
diagnostics. They, remaining work-path audits and full native/fresh-source
acceptance keep whole-query S05 acceptance open.


## Native invariant diagnostic ownership

Invariant issue arrays and compact keys now use the original query account under
capture:15. Independent Support candidate/survivor/projection sets, Physical
source validation/derivation/native-record comparisons, and Delta expected live
factors/separator buckets use accounted native collections and values. Both
inspect_invariants and check_invariants fund their temporary graphs. The physical
checker no longer creates an ordinary full support snapshot internally.

All42 owner/backend/tree/scalar cases reconcile actual upstream requests with
original-account requests, sweep22–171 inspection fault positions plus all report
copy positions, test exact/one-under work/issue/actual-byte limits and same-cap
retry, and retain reports through runtime closure with nonallocating final
release. All210 independently compiled predecessor packets match exact native
bytes, work counters, localized keys/order and partial prefixes. Frozen schema,
existing test assertions and existing tools are unchanged.

Source5 full Debug227/227 and selected117/117 each in Release, Clang18 and
ASan+UBSan/leaks pass. An independent source-only Release build/full227-case run
also passes, with334 strict project C++ objects and96 parser C objects rebuilt
locally. See [the contract](invariant_memory.md) and
[verification](verification/s05-invariant-diagnostics-native-2026-11-09.md).
The bounded runtime caller census is preserved separately. Remaining compiler/I/O
ownership/work review and full Clang/sanitizer registration keep whole-query S05
acceptance open; this checkpoint does not close the full Refactor.md goal.
