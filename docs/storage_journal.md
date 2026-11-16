# Reference table journals

Status: the storage undo primitive and R04 logical epoch integration are
verified. Its historical 39-test matrix passed GCC Debug/Release, ASan/UBSan,
Clang18 and a clean source-only Release build; see
[the dated verification](verification/runtime-journal-2026-11-05.md).
The original foundation evidence remains in [storage undo verification](verification/journal-storage-2026-11-05.md).
This page describes the low-level `ReferenceTable::Journal` undo primitive.
The API is declared
in [`reference.hpp`](../include/crown/storage/reference.hpp) and implemented in
[`reference.cpp`](../src/storage/reference.cpp); private arena allocation
revival is implemented in [`arena.cpp`](../src/storage/arena.cpp).

## Accounted native interfaces

Runtime native state uses [AccountedReferenceTable](../include/crown/storage/accounted_reference.hpp)
or [AccountedIndexedTable](../include/crown/storage/accounted_indexed.hpp), dispatched
by [AccountedStorageTable](../include/crown/storage/accounted_table.hpp). These
interfaces retain the layout's original query account. The engineering protocol
is preparation, nonallocating publication, then commit or reverse undo. These
are native ownership/resource rules, separate from the paper's relational
support and enumeration algorithms.

| Operation | Ownership and cost |
| --- | --- |
| `get`, cursor `next_entry` | Borrow the original native tuple. Mutation or table-facade loss ends that borrow. Low-level cursors hold weak state; runtime result/view cursors add a strong owner and reader lease. |
| `pin`, journal `change(i)` | Retain the original arena payload. A change view borrows its journal-owned pin: commit preserves it, while rollback/history destruction releases it. Reference history uses O(i) list access; indexed history uses vector access. |
| `bucket` | Allocate an original-account O(matches) handle buffer. Handles do not pin rows. |
| `bucket_cursor`, `live`, `index_keys` | Prepare lazy native traversal. Reference bucket tuple access additionally looks up its logical ID; indexed traversal follows live links and debits a native step even on repeated end detection. |
| `keys`, `snapshot` | Copy explicit owning native values and deep bytes. These are output-sensitive collection operations. |
| `snapshot_copy` | Build a new table/arena owner under the same account, preserving live sparse logical IDs, high-water marks and revision. Source handles do not authorize the new owner. |

Indexed journals require an original-account `AccountedIndexWork`; composed
runtime transactions share its exact remaining allowance. Journal cursors retain
that grant and reject replacement. Ordinary indexed cursors instead receive
their caller's allowance on each call. Ordered storage has no indexed work
debits; an optional journal grant still has its account checked and retained.
The dispatch facade creates no replacement account, allowance or state mirror.

Low-level `find`, `get`, copied buckets and snapshots can observe the installed
tentative contents. Runtime epoch/view owners enforce query-level visibility.
Native journals reject ordinary mutators and ordinary cursor factories while
active. Rollback aborts journal cursor authority before restoring nodes, and it
does not reset the cursor revision. Successful tentative growth can leave
visible accounted directory capacity after rollback even though logical rows,
memberships and tentative ID high-water are restored.

Preparation funds keys, nodes, inverse records, payload pins and required work
before mutation. Ordered undo reuses extracted map/set nodes; indexed undo
reuses retained rows/member nodes and saved live neighbors. Commit and rollback
allocate nothing, but their comparison, ledger-classification and destruction
costs remain real. Indexed retirement work admissions can be conservative;
they do not imply an actual payload copy during erase. Memory reports and
whole-table invariant checks have their separate scan costs in the
[primitive cards](code_specs/primitives.md) and [memory contract](query_memory.md).

## Purpose and API

`ReferenceTable::journal()` opens one exclusive mutation scope for that
table's shared state and returns a movable, noncopyable `ReferenceTable::Journal`.
The journal accepts row `insert` and handle `erase` operations. Successful
operations are recorded in order; duplicate inserts and erasures of absent
rows are no-ops and add no change. `size()` reports the number of recorded
changes while active or committed. `change(i)` returns a `ChangeView` with the
operation direction (`inserted`), tuple handle, and a borrowed tuple reference.
For an erase, `inserted` is false.

`commit()` keeps the current table contents and ends the exclusive scope.
`rollback()` reverses recorded changes in reverse order and ends the scope.
Both calls are idempotent. Destroying an active journal rolls it back; move
assignment also destroys and rolls back any active journal already held by the
destination. After rollback the change list is cleared. After commit the change
list and its tuple pins remain available until the journal itself is destroyed.

```cpp
auto journal = table.journal();
const auto inserted = journal.insert(row);  // handle is tentative
// Keep the handle and any reads of the tentative state internal here.
journal.commit();
// The handle may now be published as committed table state.
```

The table APIs apply their ordinary layout and handle ownership checks inside
the journal. The journal is for one table state only; it does not coordinate
multiple tables or provide a shared multi-table visibility/commit API.

## Exclusive mutation and tentative reads

Only one journal can be active for a table state. Starting a second journal
while one is active, using an ordinary table mutator, creating an ordinary
live or bucket cursor, or advancing an ordinary cursor during the journal
reports `storage_busy`. Journal operations are the permitted mutations during
that scope.

The [D02 epoch-view foundation](epoch_views.md) adds owner-only
`Journal::live()` and `Journal::bucket_cursor()` reads of a drained tentative
state. These cursors share a lazily allocated journal reader token. Commit
preserves the token; rollback marks it aborted before undo, so a subsequent
`next()` rejects without touching invalidated iterators. A real forward
mutation still invalidates the cursor by revision. Starting a different
journal blocks a previously committed owner cursor, including when the new
journal has made no changes. These low-level cursors hold weak table ownership;
the runtime view supplies the strong state/read lease and prevents further
staging while its prefix is held.

This is an exclusive writer guard, not reader isolation. Reads such as
`find`, `get`, `bucket`, `snapshot`, and `check_invariants` can inspect the
currently installed tentative contents. Such observations, tuple pointers,
and handles must remain internal until commit. In particular, a tentative
handle can become valid again for a later insert after rollback, so callers
must never publish it or use it as durable identity before commit. An existing
cursor cannot advance during the journal; after a real journal mutation its
revision is still changed, so it remains invalid after commit or rollback.
As with the rest of reference storage, callers must externally synchronize
concurrent access.

`journal()` allocates its journal data before setting the state's active flag.
The journal then holds a `shared_ptr` to the table state: moving the
`ReferenceTable` facade preserves the state, and destroying the facade does
not destroy an active journal's state. Commit or rollback clears the active
flag and releases this state reference. Commit does not keep the whole table
alive: the journal retains only its affected payload pins and detached
container nodes until the journal is destroyed.

Each `change(i)` tuple reference is backed by a pin owned by its journal
entry. It stays readable while the journal is active and, after commit, until
the journal is destroyed. Rollback clears the entries and releases their pins,
so views obtained from a rolled-back journal must no longer be used. Both
inserted and erased rows are pinned: an inserted row stays readable if it is
later tentatively erased, and an erased row stays readable for the change
view.

## Undo records and identity restoration

Before mutating, the journal prepares typed projected keys for every current
secondary index. For a deletion it also pins the arena allocation, then
extracts the row's nodes from the primary map, ID map, and affected secondary
maps/sets. Extracted nodes retain their allocated container storage. For an
insertion, the journal records the previous logical tuple-ID high-water mark,
then pins the inserted arena allocation after normal table insertion.

Rollback walks these records backward. An insertion is undone by removing its
secondary memberships and primary/ID records, erasing its arena membership,
and restoring the previous logical tuple-ID counter. A deletion is undone by
calling private `TupleArena::revive` on the retained pin and reinserting the
extracted primary, ID, bucket, and set-member nodes. The ID record's primary
iterator is updated to the iterator returned by reinsertion. This restores the
same logical tuple ID, arena slot and generation, and tuple address; it does
not copy a replacement tuple or allocate replacement index nodes.

Undo does not retain bucket or set iterators for later use. A later journal
operation may extract and reinsert a bucket, invalidating such iterators, so
undo looks the bucket up again with the precomputed typed key. The ordered
container comparator compares the fixed typed tuple values directly and does
not allocate. Preparation and normal forward mutations may allocate; reverse
undo uses the retained pins and extracted nodes and does not allocate. Internal
invariant violations during the `noexcept` undo path terminate the process.

Arena revival is private undo support, not a public resurrection operation.
Only an allocation retained by its pin can be revived by this path. A committed
delete remains absent and its ordinary handle stays stale; a public
`TupleArena::erase` likewise does not become reversible through this API.

## Revisions and allocation metadata

Each real journal insertion or deletion advances the table revision using the
ordinary mutation path. No-op operations do not. Neither commit nor rollback
decrements the revision. Thus cursors that predate a real tentative mutation
remain invalid even when rollback restores the same visible rows. A journal
that makes no real changes leaves the revision unchanged.

Rollback restores the logical tuple-ID counter for aborted inserts, but it
does not rewind arena allocation history. Inserting into a free arena slot
advances that slot's generation; inserting into a new slot can grow the arena's
slot high-water metadata. Undo retires the tentative allocation while its pin
is held; when the change entries are cleared, pin release reclaims the payload
and makes the slot reusable where its generation permits. Arena statistics
can therefore show a larger slot count or later generation after an aborted
insert even though table contents, indexes, and the logical tuple-ID counter
were restored. Since a tentative logical handle may be reused after abort,
it must not escape to public callers before commit.

## Scope boundary

Each entry retains typed keys for all current indexes and a pin on its tuple.
Deleted map/set nodes retain their existing allocations. Journal storage grows
with affected operations, key/value sizes and index memberships; it does not
copy unrelated table rows. The current insert path prepares projected keys
once for undo and again in the normal reference insertion. Vector growth,
ordered-container comparisons, string widths and retained arena metadata have
costs; this layer supplies no byte budget or CROWN complexity claim.

`SupportRuntime` now combines these scopes with affected metadata undo and
causal before/after records for one logical native update. After all throwing
work finishes, it commits every touched scope, releases storage undo fragments,
and retains only its public record pins/metadata and optional event trace.
The separate physical coordinator and result/view cursors build on these
scopes. Full-query delta delivery and recovery remain open.
See [reference storage](storage.md), [tuple arenas](tuple_arenas.md),
and [runtime support](runtime_support.md) for the surrounding contracts.
