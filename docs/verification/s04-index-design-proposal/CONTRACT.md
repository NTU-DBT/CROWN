# Proposed optimized index contract

## Existing authority and proposed shape

Refactor.md S04 requires native primary/secondary indices, collision handling,
an explicit bucket iterator contract, exact membership independent of payload
arithmetic, differential S02 tests and traversal of live records only.
S01 supplies immutable TupleLayout/Projection tokens and exact typed tuples.
S03 supplies TupleArena ownership, generational allocations and explicit pins.
Those authorities are retained.

Proposed new type: `storage::IndexedTable`, owning and noncopyable, with moves
that preserve its storage owner and existing handles/pins. It mirrors the
semantic operations of ReferenceTable, including journals, rather than
changing that oracle in place. This is a proposed API name, not an existing
declaration. Exact signatures and integration defaults require root design
review before implementation.

A row node contains its TupleId, ArenaHandle, borrowed immutable tuple address,
cached full-row hash, primary-chain and ID-chain links, live-row links and
per-index membership links. The arena remains the only tuple-payload owner.
Logical TupleHandle continues to contain StorageOwnerId, RelationId and the
monotonic logical TupleId; it is not replaced by a raw node pointer or arena
slot. Published IDs do not wrap or get reused after committed deletion/clear.
The existing unpublished tentative-ID reuse rule after journal rollback stays
explicit.

ReferenceTable currently allocates StorageOwnerId from a private static atomic
in reference.cpp. IndexedTable must share that same nonwrapping authority;
creating a second counter could make cross-backend handles appear same-owner.
Factor it into an internal shared allocator without exposing a public raw-owner
constructor. Reference-only allocation order and error behavior must remain
unchanged. ArenaOwnerId is a separate typed authority and remains with S03.
Construction may consume an owner ID before a later allocation fails, as in
the existing implementation. That process-wide ID is never recycled; the
failure-atomic row-mutation contract does not promise gap-free global IDs.

Each secondary index owns its original Projection token, a hash directory of
key nodes, a list of currently nonempty key nodes, and one membership node per
live row in that index. A key node owns an immutable projected Tuple and its
cached hash. A membership node references its row node and has bucket links;
the row node records the reverse membership pointer. Empty keys are removed
from public membership and live-key traversal immediately. Index registration
is idempotent only for the same Projection token, as today; separate equal
programs retain independent IndexIds. P08's existing sharing rule is not
broadened.

The table owns row/key/member nodes through bounded pools or explicit owning
containers; intrusive links are nonowning. Do not use a recursively owned
next-node chain whose destruction depth follows input size. Retirement and
owner destruction walk their finite owned-node populations iteratively.

Primary equality, logical-ID and secondary-key directories use separately
chained buckets. Their arrays contain node pointers, not movable tuple payloads.
Rehash therefore changes directory links without relocating arena tuples or
row/key/member nodes. It is an explicitly charged mutation phase, not hidden
inside cursor advance. A value lookup checks the full cached hash and then
exact equality; a hash collision never establishes equality or presence.

Each resident directory node keeps a nonowning predecessor link (or a
pointer to the link that names it), in addition to its next link. Removing a
known row/key/index node therefore does not search a collision chain during
commit. Rehash rewrites every affected directory link before retiring its old
array. Undo uses the current array and cached hash, never a saved pointer into
an obsolete bucket array. Live/member-list neighbors are separate from these
directory links.

## Scalar and layout semantics

Every operation accepting a row Tuple first checks its source layout token.
Handle operations instead check the actual storage owner/relation. Every bucket probe
first checks the projection target token. Equal reconstructed descriptors do
not acquire token compatibility. Shared target tokens continue to permit
cross-source projections, including empty, repeated, reordered and composite
keys. A repeated logical variable must still satisfy S01 tuple validation.

Keys retain the current Value alternatives: int64, byte string, Boolean, Date
and canonical Decimal. Equality uses exact variant/type and value equality.
Strings include embedded NUL and high bytes and are not interpreted as text.
Dates use their exact epoch-day value. Decimal sign/scale/coefficient semantics
remain canonical, with up to 38 coefficient digits; no floating-point
conversion, epsilon comparison, rounding or locale rule is introduced.
Presence is whether a live membership node exists. An external exact support
count or annotation is never used as a hash-table empty/tombstone sentinel.

Initially reuse the existing typed row_hash framing, with its current versioned
behavior; it is an equality filter, not a proof or security primitive. Its
Decimal path calls allocating to_string(), so calculate and charge it during
throwing preparation and cache the result. Do not call it during commit,
rollback, rehash or reclamation. String lengths/fields and the bounded Decimal
formatting allowance must be admitted before invoking a whole hash/projection
helper. Cached hashes belong to immutable values and cannot become stale.
An independently checked allocation-free scalar visitor is a possible later
optimization, not assumed available in this draft.

Use the current exact equality implementation on hash matches. It does not
format Decimal or allocate. Comparison/key-copy costs remain proportional to
the fields and bytes inspected; a fixed-query argument does not make arbitrary
string widths free. The private hash distribution rule and capacity/load rule
must be pinned and tested. With the existing deterministic hash, expected
lookup claims are conditional on a stated distribution assumption; adversarial
collisions have linear chain cost. A finite comparison/work grant stops an
attempt honestly. Mixing a seed into an already colliding hash does not remove
that collision and must not be advertised as an adversarial guarantee.

## Iteration and lifetime

Live row, live key and bucket-member cursors follow their dedicated links.
They visit exactly current membership, never empty hash slots, retired arena
slots, free nodes or tombstones. Empty detection and first/next/end link steps
are constant structural actions, independent of retained directory capacity.
Bucket startup additionally pays exact key hashing/equality and its chain
search. This is not a constant wall-time or allocator bound.

The proposed new backend uses deterministic insertion order for live rows and
first-live-key order for key traversal. Bucket members follow logical TupleId
order induced by insertion and exact rollback restoration. This differs from
ReferenceTable's lexicographic live-row/key traversal and is an explicit new
backend contract. Rehash does not change live traversal order. An owning
canonical snapshot may sort copied rows/keys, with its full work/copy cost
explicit; the live iterator itself must not hide sorting or a capacity scan.

Cursors keep weak table ownership and an invalidation revision, not record
pins. Moves preserve state; destruction, real mutation, index add/drop and a
nonempty clear invalidate cursors before any pointer can be dereferenced.
Duplicate inserts, absent erases and other true no-ops do not invalidate them
or trigger rehash. Borrowed index-key entries expire on next traversal,
mutation or destruction. TupleArena::Pin retains tuple payload after erase,
clear, facade replacement and destruction without retaining membership.
Moved-from facades/cursors and foreign owners/layouts retain explicit errors.

There is no new concurrent-reader/writer contract. All operations and journal
reads obey the existing exclusive single-writer boundary. Starting another
journal blocks a previously committed owner cursor even if no row changed.
Rollback invalidates an owner cursor before inverse mutation. Revision is a
storage invalidation stamp, not a committed owner epoch.

## Owning copies

Keep an owning table/plan-storage copy distinct from a vector snapshot and a
cursor. Native ReferencePlanStorage::snapshot_copy currently creates fresh
storage/arena owners while preserving live TupleIds, IndexIds, their last-ID
counters, layout/projection tokens and the numerical storage revision. It
rejects an active source journal and copies all live rows and index memberships.
The optimized counterpart must preserve these same identity boundaries plus
its documented live-row, key and bucket-member order. Old handles must fail
against the new owner even when their logical IDs are equal.

Use a private checked copy builder to preserve sparse logical IDs and rebind
all arena addresses, directory links, reverse members and list neighbors.
Replaying public inserts alone can renumber surviving rows and is insufficient.
Copy only live payloads and registered indexes: external pins and retired
source allocations remain with their original owners. The same finite backend
configuration applies, but the copy may choose the smallest permitted capacity
for its live population rather than duplicate free shells or historical peak
capacity. Its own copy-work report is separate from the source's diagnostics.

Admit the complete row/key/member copy and directory construction through one
finite grant. Any allocation or work failure destroys the unpublished copy
and preserves the source, its cursors and old pins. The copy is not a cheaper
transaction substitute and cannot hide a full-state rebuild inside update or
cursor cost claims. This is a proposed private utility and facade obligation;
no new public raw-ID or storage-owner factory is needed.

## Preparation, commit and rollback

For each normal mutation, preparation validates all layouts/handles, hashes and
copies all needed keys, allocates row/key/member/undo nodes, obtains payload
pins where needed, and prepares any larger directory arrays. It admits all
remaining work/capacity before publishing links. Commit consists of bounded
pointer/link changes, checked counter assignments and nonthrowing ownership
moves. It performs no hashing, equality lookup, projection, payload copying or
allocation. Failed preparation leaves published rows, indexes, logical IDs,
revision and committed-operation counters unchanged. Separate attempt/abort
diagnostics may advance and must be labeled accordingly. S03's disclosed temporary arena
generation/high-water metadata behavior is retained, not claimed reversible.

Inside a journal, structural counts describe its tentative owner-only state.
Accumulate committed primitive-action counters privately until the journal
commits; discard that accumulation on rollback. A committed sequence may have
nonzero insert/erase work even if its final row set is unchanged. These are
storage-operation counters, not physical root-update, derivation or C01 event
counts. Attempt-work diagnostics remain separately labeled and do not become
committed statistics merely because an internal table mutation succeeded.

Journal undo cannot rely on std::map node handles, because the new backend does
not own those containers. It retains the actual detached stable nodes, arena
pins, original live/member neighbor links and prior logical-ID counters. Reverse
undo reinserts those same nodes and revives the same pinned allocations.
Cached hashes select current directory heads without formatting/comparing a
key. LIFO restoration makes the saved live-list neighbors valid again before
they are needed; this is a proof obligation for interacting insert/erase traces,
not an assumption to skip testing.

During one journal, a key whose degree becomes zero may retain its key node
privately in the directory so later changes and undo reuse the same identity.
It is absent from key_count, live-key links and public bucket membership. These
retained empty nodes are tracked and capped separately. Commit/rollback visits
the affected-node list to reclaim them; it never scans the hash array. Every
pointer retained by undo remains owned until that undo record is retired.
Index add/drop/clear remain prohibited during an active journal.

Rehash prepares a complete replacement pointer array and pre-admits traversal
of all affected live/retained nodes. At a successful mutation's commit it
relinks cached hashes and swaps arrays without throwing. Journal rollback may
retain the successfully enlarged capacity, like other admitted high-water
metadata, while restoring exact logical state, IDs and live order. That
capacity-retention rule must be separately visible in statistics and tests.
An ordinary failed preparation does not silently commit a rehash. No automatic
shrink is proposed; repeated bounded-population churn must recycle node shells
and release key/string payloads instead of growing with historical insertions.

## Finite limits and counters

Proposed construction limits are explicit finite maxima for live rows, indexes,
live keys, memberships, retained journal nodes, node-pool slots and directory
slots. Per-operation grants bound visited nodes, hash/equality bytes, copied
fields/bytes, projections, rehash slots and staged nodes. Checked products and
sums are admitted before allocation; no zero-as-unlimited convention is used.
`WORK_MODEL.md` proposes required finite construction limits, lazy eight-slot
power-of-two arrays, doubling and a 3/4 admitted load for review; no production
default is accepted yet. Resource failure is distinct from duplicate/absent success.
Rollback/commit have already admitted inverse/finalization work and cannot
fail halfway because a fresh grant was exhausted.

Maintain exact structural counts for live rows, live/nonempty keys, memberships,
free/retained node shells, directory slots and journal-retained empties.
Structural counts and IDs reject overflow before mutation. Optional operational
counters distinguish probes, hash/equality bytes, collision-chain visits,
rehashes/moved nodes, actual insert/erase, duplicate/absent no-op and attempts/
aborts; diagnostic saturation must be flagged and must not decide membership.
No clocks or scalar formatting are required when diagnostics are off.

These are logical component/capacity counters, not total allocator live,
reserved or peak bytes. Old and staged rehash arrays, arenas, pins, strings,
journals and free shells remain distinct populations. S05's per-query byte
budget and allocator reconciliation are not implemented or claimed by S04.
