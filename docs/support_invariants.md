# Reference support maintenance invariants

This argument covers the logical-native interface of R01–R04 and its
same-sign, multi-stage composition through the R05 `PendingEpoch` foundation.
Inputs are complete typed node-scope tuples after any physical
filtering/projection and derivation counting. The physical coordinator's
composition and committed-enumeration arguments appear below. Before/after
fragments, deltas, versioned query snapshots and recovery remain separate tasks.
Affected values are pinned by the returned epoch journal. Every tree is already
P02 checked.

Initially native relations are empty. Generalized candidate unions, all S/P/E
relations and their metadata are empty. Constant operators independently have
their declared truth value and no native ports. For a tree route, the following
invariants hold after each completed update and work-queue drain, including
after each drained stage of an active `PendingEpoch` and at its commit barrier.

- A native record has one flag per ordered child, true exactly when that
  child's P relation contains the compiled separator key. Its satisfied-child
  count is the number of true flags; it belongs to S exactly when all are true.
- A generalized candidate exists exactly in the union of its child P keys.
  Guard makes every such key an assignment to the complete generalized scope.
  Its flags count distinct child presences, not the children's witness counts.
  It belongs to S exactly when all children are present, and is reclaimed when
  none are. The empty scope follows the same rule with one possible empty key.
- Every P key has a positive exact count of the distinct local S tuples that
  project to it. Every E key has the analogous count for F intersect B, and E
  exists only for C* nodes. Their identities and counter maps remain separate.
  They do not count full subtree witnesses or physical derivations.

Insertion of a new native tuple probes the current child P sets, initializes
all flags, and inserts into S only if they are all satisfied. In a pending
epoch these are the sets after the preceding stage's queue has drained, so
they may include earlier unpublished stages.
Deletion performs the inverse S transition when needed, then erases the native
record. Duplicate insertion and absent deletion change neither support nor
flags. Children are descendants, so a direct native change cannot change its
own child's support during the upward propagation that follows.

A child P membership crossing visits exactly matching native records through
the compiled reverse separator index and changes one child slot. An unchanged
flag is an internal error rather than another counted application. A generalized
parent changes the analogous bit of the one candidate key. A missing candidate
on appearance has no earlier child support, by the candidate-union invariant;
its initial flags can therefore be false. A missing candidate on disappearance
is an error. Last-presence deletion removes the candidate only after any S
withdrawal. No Cartesian relation is needed.

Every S insertion/deletion changes each applicable P/E count by exactly one.
Membership is inserted only at count 0 to 1 and erased only at 1 to 0. Positive
count changes retain the same key record and emit no membership event. Only P
crossings queue work for the parent. Thus each child flag eventually agrees
with actual child P membership, and the counting invariants are restored.
The tree is finite and all queued work moves strictly toward its root. This
establishes termination without recursion on the host call stack. FIFO and LIFO
can change processing order, but the final sets/flags/counts are determined by
the same native relations and recursive subtree definitions. Physical tuple
IDs allocated to newly appearing keys need not agree between schedules.

For one logical set insertion all support changes are monotone additions; for
one deletion they are monotone removals. The same holds across a
`PendingEpoch`, because its operation sign is fixed for every stage. Each
stage starts from the invariant state left by the previous drained stage, so
the one-stage argument composes by induction. No local membership can cross
more than once over that same-sign epoch. Captured local record/S/P/E events
therefore equal the corresponding before/after set differences, without
duplicate crossings. They are not full-answer deltas: E is local subtree
visibility, not the later global live-view relation. Root S nonemptiness
establishes query existence; P08's conditional C* argument describes how exact
E sets can later enumerate the projected answers.

Projection counters use checked uint64 arithmetic. Overflow, a configured
support cap, a work cap, and allocation exceptions occur before publication.
Real updates change the current tables under lazy exclusive per-relation
journals. New tuples/keys, erased tuples/keys and matching reverse-bucket rows
are the affected records. There is no whole-state copy. Each table journal
retains its undo keys and extracted container nodes; deletion pins the exact
allocation before extraction. Reverse undo restores its original ID, arena
generation/address and memberships without allocating replacement nodes.
Pending events own their keys even after source membership vanishes.

Metadata undo is prepared before each map/flag/count mutation. Insertions save
their ID for removal; changes save the previous exact value; removals extract
the original metadata node. The undo vector has capacity before any change
is made, and moving its prepared owning entry into that capacity does not
allocate. Before/after record descriptions and their pins are also prepared
before the metadata mutation. If a later allocation fails, reverse metadata
undo restores the original map contents and values, then table undo restores
membership and tuple identities. Temporary references to absent rows during
these destructor phases cannot be observed through this synchronous,
single-writer, externally synchronized API.

All potentially throwing maintenance, work checks, return-artifact construction
and answer detection finish before commit. `apply` has one drained stage.
`PendingEpoch` drains after each stage but shares the same transaction, metadata
undo stack, lazy table journals, work cap, event IDs, and cause forest across
all of them. The next stage therefore starts only after the previous queue is
empty, while its inverse records remain available. One final commit barrier
commits each table scope with no-throw operations, releases low-level undo
fragments/extra pins and old metadata nodes, and advances one sequence once.
Moving the prepared output and completing a valid commit allocate nothing.

If any staged operation fails before that barrier, one destructor rollback
applies metadata inverses in reverse order across every stage, then rolls back
all opened table journals without allocation. It restores the previous
sequence, logical state, counts, truth and public handles; no partial epoch is
returned. A valid no-op `apply` takes its fast path and consumes its sequence
with zero metrics and no journal. A pending epoch containing only no-op stages
has the same zero metrics and no journal when committed, and consumes one
sequence once. Private revisions can stay advanced to invalidate cursors, and
aborted allocations can leave free high-water slot metadata/generations; these
do not alter logical state.

Public support handles use a stable runtime owner plus node, role and tuple
ID. An existing positive key retains its ID through commits and positive count
changes. Committed erase/reinsert allocates a new ID. Aborted tentative IDs
are restored and remain unpublished. Foreign runtimes cannot resolve handles.

For a real single-call `apply`, event 1 is the native operation, with cause 0.
For a prepared epoch, each changed stage contributes one native event with the
next epoch-wide ID and cause 0; no-op stages contribute none. Each P crossing
with a parent enqueues one event with a new ID and the current event as its
cause. Queue entries are popped once; an applied-ID flag rejects reapplication.
Each stage drain checks every event enqueued so far was applied once; the
aggregate committed counts satisfy
`events_enqueued == events_applied == changed_native_stages +
child_key_events`. With tracing enabled, applied ordinals form a permutation,
every child event identifies its physical parent/child slot and source P
handle, and its cause precedes it in application order. Disabled tracing skips
payload capture but retains the same epoch-wide ID flags and accounting.

Each affected-record description has a mutation ordinal and causal event ID.
Its before/after membership, child flags/count or projection count describes
that local mutation; multiple descriptions may share a handle/cause. In
particular, generalized candidate creation can briefly record all-false flags
before the causing child's flag is set. The complete-epoch invariants above
are required after queue drain, not at every microstep. Applying descriptions
in ordinal order reconstructs the after-state from the before-state.

The returned immutable shared journal owns pins on affected tuple allocations
and copies of their before/after metadata, with optional causal trace. A
prepared epoch's journal aggregates affected records and events from all its
stages. A committed deletion removes index membership immediately; pins keep
its value readable through later updates and owner destruction. The runtime
does not retain returned journals itself. Retaining one does not freeze
unrelated outside-context state. D01 supplies a committed busy lease; the
[D02 cursor](epoch_views.md) combines a shared lease with journal patches
for before/after projected and full-witness fragment reads.

For a fixed query, candidate keys are bounded by child-support unions and P/E
keys by local survivors. Zero-presence generalized candidates and zero-count
P/E keys/metadata entries are reclaimed. Native records remain while their
logical rows exist, even with no satisfied children. No historical
event list is retained by the runtime. Undo/journal space follows affected
operations, child widths, index keys and caller-held pins; it is reclaimed
when the transaction and returned journals are released. Arena metadata keeps
its declared high-water allocation. Metrics report abstract work, storage/
metadata changes, flags saved for metadata undo, journal records and queue
counts. The old whole-copy counters are zero. Allocator bytes, value widths,
ordered-container comparisons, pointer-vector growth, cleanup and wall time
have additional costs; these counters are not a complete memory/time bound.
Optimized storage, integrated physical delta/output acceptance, cursor delay
and external mathematical review retain separate S04/S05/R05/D/G2/V02 obligations.
No CROWN update/delay or release claim follows from this conditional argument.

## Physical source and occurrence composition

The [physical coordinator](physical_runtime.md) begins with empty source
tables and empty derivation maps. For each occurrence, its count for a final
native tuple equals the number of distinct complete source rows whose
adapter accepts and projects to that tuple. A full-row set insertion/erasure
changes each affected occurrence's count by exactly one, or leaves it alone
when filtered. Exact duplicate insertion and absent erasure change no count.
Counts are scoped to occurrences, so two aliases with the same tuple do not
share a derivation counter.

The coordinator changes native membership only at count 0 to 1 or 1 to 0.
Therefore each native relation equals the set image of its occurrence's
adapter once all routes finish. Routing each crossing through the drained
logical stage above restores support invariants after each prefix. A later
alias sees earlier alias changes, including new–new self-join terms; it does
not separately publish or consume a sequence. Prefixes may temporarily differ
from the final physical database's complete alias image, which is why public
source, count and logical readers all remain busy until close.

Constraint checking sees the complete proposed physical after-state, including
unused tables and the row just inserted into a self-referencing FK target.
The temporary full database image is validation work, not retained rollback
state. Any failure reverses logical changes, then count-map changes, then the
source table journal. Erased count-map nodes are retained for allocation-free
reinsertion; vector capacity exists before a map mutation. The no-allocation
commit barrier publishes source, counts and support together, with one
sequence. Thus the complete committed state satisfies both the source-to-alias
image invariant and the logical support invariants.

This argument establishes maintained state and atomic publication for one
physical input. It does not turn local support transitions into global answer
deltas, prove a witness partition, or provide result/sink liveness. Those
remain D03–D06/O06 obligations; the full constraint scan and ordered-container
costs remain explicit reference-backend costs.

## Current-result enumeration

A result cursor acquires a read lease on one committed logical Impl. Writers,
including no-op inputs, reject while any such lease exists. Public committed
reads and other result cursors remain allowed. The lease keeps tables alive
through facade moves/destruction, so the storage cursors' iterators and borrowed
selected tuples remain valid until close. Construction performs only fixed
query metadata work. It does not copy E sets or materialize answers.

The compiled C* program orders each parent before its children. Its root uses
a live E cursor; every other step uses the E bucket selected by the parent's
visible separator. A selected parent E row has a local survivor witness. Every
child in C* has a separator contained in F, so that key is fixed by the parent
visible row and has a nonempty matching child E bucket. Repeating the same
argument below the child gives completions. Branches outside C* are supported
by local survivors and introduce no independent output assignment. Connect
makes shared variables agree along their tree paths; compiled cross-assignment
equality checks validate that agreement at assembly.

The iterative frame stack advances one live cursor at a time and resets an
exhausted frame before backtracking. Thus each compatible combination of E
tuples is visited exactly once, including arbitrary fan-out and disconnected
products with nullary separator buckets. The C* coverage property includes
every free variable. A complete F assignment determines exactly one tuple in
each set-valued E relation, so two different combinations cannot project to
the same head row. Repeated/reordered head columns preserve that uniqueness;
positive E support counts and hidden survivor witnesses are not re-enumerated.
The verified SQL mapping retains every unfixed output variable, adds constant
columns and preserves column order. Scalar EXISTS instead emits its one
Boolean row, even for an empty core result.

Each returned tuple owns its values and output layout token. Exhaustion,
cancellation or failure destroys all frame cursors and releases the lease
without allocation. Other active leases still block writes. A failed stream
does not resume; a fresh cursor can read the same unchanged committed epoch.
Closing retains metrics and immutable query/output metadata, not the old data
state. D01 uses a busy read lease rather than a copied or versioned database.
The [D02 cursor](epoch_views.md) adds before/after fragment context
with one shared lease and an inverse journal overlay. Deleted memberships
come from pinned tuples; inserted memberships are excluded from before-side
walks. Positive-to-positive support changes do not alter visibility. Rollback
closes linked cursors before undo; commit preserves the overlay and lease.
Projected completions still enumerate each E assignment once. A hidden
binding adds an existential survivor-subtree test correlated to all selected
visible values. By the S invariant, a row has a full subtree witness exactly
when every child has a compatible witness. Running intersection implies that
different children share variables only through their fixed parent row, so
successful child witnesses need not be revisited when a later child fails.
The iterative test filters the projected candidate without enumerating hidden
witness products or keeping output history.

The separate full-assignment cursor joins a selected set of S factors and
outputs every variable in their union. A union assignment determines at most
one row in each set-valued factor; therefore distinct compatible row choices
cannot emit the same complete assignment. This covers rooted subtrees and
nonadjacent/disconnected factor sets. An S factor retains its original
descendant-existence restriction even when those descendants are omitted from
the selection; such a selection is not a raw-atom subset query.

Startup, successful-result, terminal-null and failed actions have separate
abstract counters. Live advances, bucket lookups, selected tuples, numeric
keys, equality checks and copied output fields are measured. Ordered index
comparison costs, field width, allocation and mandatory cleanup (especially
release of a last facadeless Impl) have separate costs. The counters and finite
oracle checks establish no S04/D05 constant-delay or byte-budget guarantee.
