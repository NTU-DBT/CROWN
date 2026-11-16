# Tuple arenas and generational handles (S03)

Status: S03 verified. All 36 tests pass GCC Debug/Release, ASan/UBSan, Clang18
and a fresh source-only Release build; see the
[verification audit](verification/arena-2026-11-05.md). This page records the code in
[`arena.hpp`](../include/crown/storage/arena.hpp),
[`arena.cpp`](../src/storage/arena.cpp), and the reference-table integration in
[`reference.hpp`](../include/crown/storage/reference.hpp) and
[`reference.cpp`](../src/storage/reference.cpp).

## Ownership and identity

`TupleArena` owns tuple payloads for one `TupleLayout`. It is noncopyable and
has `noexcept` move construction and assignment. A move transfers the arena
state and its owner identity; using a moved-from arena reports
`invalid_arena`. Destroying an arena closes it by clearing its live records.
Arena operations are single-threaded and require external synchronization.

Two handle types represent different identities:

| Handle | Identity | Allocation policy |
| --- | --- | --- |
| `TupleHandle` | `(StorageOwnerId, RelationId, TupleId)` | Public logical table identity; tuple IDs increase monotonically and are not reused within that table owner. |
| `ArenaHandle` | `(ArenaOwnerId, TupleSlotId, uint64 generation)` | Arena allocation identity; a slot can be reused after reclamation, with its generation advanced. |

`ReferenceTable` keeps this distinction private: its `by_id` entry stores the
exact `ArenaHandle` for each live logical tuple ID. The primary map borrows the
tuple address from the arena. Per-slot `unique_ptr` allocation keeps that
address stable when the slot vector grows. Secondary index buckets continue to
use the reference backend's standard containers; S03 does not replace them.

Arena owner IDs and logical storage IDs are separate from slot and tuple IDs.
An arena handle from another owner reports `foreign_handle`. For the same
owner, an out-of-range slot, erased allocation, or wrong generation is stale:
`contains` and `erase` return false, while `get` and `pin` throw
`stale_handle`. These checks apply in every build configuration. A tuple with a
different layout token is rejected with `layout_mismatch`.

## Slot lifecycle and reclamation

Each slot has a generation, an optional tuple payload, a pin count, and
intrusive links for the live and free lists. The slot vector retains its
high-water metadata after erase and clear. Reclaiming a payload does not shrink
the vector or release the slot object.

| State | Payload | Arena membership | Next transition |
| --- | --- | --- | --- |
| Live | Present | On the live list | Erase removes it from live membership immediately. |
| Retired and pinned | Present | Not live and not reusable | Last pin release destroys the payload and reclaims the slot. |
| Free | Absent | On the free list | Insert copies the new tuple, then advances the generation and publishes the slot as live. |
| Exhausted | Absent | Not reusable | Reached when the generation is `UINT64_MAX`; the slot is retained as metadata and never wraps. |

Erasing an unpinned live tuple destroys its payload and places the slot on the
free list. Erasing a pinned tuple immediately invalidates ordinary handles and
removes it from table/index membership, but retains its immutable payload in a
retired slot. That slot cannot be reused until its last pin is reset or
destroyed. Pinning an already retired record is not allowed.

`clear()` walks the intrusive live list, so its arena work is O(current live
records). Successful pin creation, erase, clear, reclamation, pin release,
membership checks, and statistics reads do not allocate. Error diagnostics may
allocate. A pin is movable, noncopyable,
and keeps the arena state alive. Its
`get()` remains valid after erase, clear, table destruction, arena destruction,
or replacement of the arena by move assignment. `is_live()` reports false once
its row is retired. Reset releases retention; a move transfers that retention
to the destination. Access through an empty pin reports `invalid_pin`.

When the arena owner closes, it retires every live row: unpinned payloads are
destroyed, while pinned payloads and all slot metadata remain in the shared
state. The last pin release reclaims its payload. If the owner has already
closed, releasing its last pin also releases the final state reference and
destroys the metadata. While the owner remains open, it keeps the metadata.
A pin preserves payload access only. It does not preserve table membership,
an index entry, a cursor, or a snapshot of other records.

## Allocation failure and inspection

`TupleArena::insert` publishes a slot only after tuple construction succeeds.
For a reused slot, a failed value copy leaves the slot free with its previous
generation and published counters unchanged. For a new slot, payload
construction and vector growth precede publication. If either fails, the
arena's published slots, generations, and counters remain unchanged.

`ReferenceTable::insert` first allocates an arena tuple, then updates its
primary map, ID map, and secondary buckets. If a later map operation fails,
those logical table changes and the public tuple-ID counter/revision are rolled
back. The successful temporary arena allocation is erased, but the arena
high-water slot metadata may have grown, and reuse may have advanced an
internal generation. Thus table contents and public IDs remain unchanged while
arena statistics can reflect retained slot history.

`ArenaStatistics` counts slots, live rows, retired pinned rows, pin objects,
free slots, and exhausted slots. It does not estimate bytes, allocator
overhead, reserved capacity, or historical allocation cost. `check_invariants`
checks arena counts, free/live-list membership, payload and generation rules,
and tuple layout/value validity. Its scan is O(total slots) and uses temporary
visited arrays; it is a diagnostic check, not a constant-time operation.
Growing the pointer vector can move O(total slots) pointers. Final state
destruction releases O(total slots) metadata; a pin can delay that cost past
owner destruction. These costs and allocator overhead belong to later memory
and runtime accounting, even though tuple addresses remain stable.

The slot partition is live, retired with pins, free, or generation-exhausted.
Insertion removes one free slot or appends one new slot only after value copy
succeeds, then links it live. Erase unlinks a live slot and either retires or
reclaims it. Releasing a live pin changes only pin counts; releasing the last
retired pin destroys its value and reclaims its slot. This preserves the
partition and counters. Reuse strictly advances the generation and never
wraps, so a publicly erased arena handle cannot become valid again. A pin prevents reuse,
which preserves its payload and address until reset. Reference-table erasure
removes borrowed map keys before arena reclamation; deep copies create fresh
payloads before publishing their own map pointers.
The reference-table journal has a private undo-only revival operation: an
uncommitted deletion can be reversed using its retained pin, original slot and
generation. This is not a public arena operation. Committed erasures remain
stale. See [storage journals](storage_journal.md) for tentative visibility and
identity rules.

## Reference table and copy behavior

`ReferenceTable::get` remains a borrowed pointer valid until erase, clear, or
table destruction. `ReferenceTable::pin` resolves a live logical
`TupleHandle` and returns an arena pin. Erase, clear, and destruction remove
the row from the primary and secondary indexes even if a pin keeps its payload
readable. Live and bucket cursors are still fail-fast weak-owner cursors; they
do not pin records.

`snapshot_copy()` rebuilds a separate table and arena from live tuples. The
copy gets fresh storage and arena owners, reconstructs live payloads and
indexes, and preserves the table's last allocated tuple/index IDs and revision.
Retired records and pins are not copied. This explicit comparison utility
remains available; the support runtime now uses R04 affected-record journals
instead of copying its state for each update.

Tuple values own their strings. The arena therefore needs no string interner
or separate dictionary lifetime. This implements the ownership needed by the
current tuple representation without adding dictionary IDs, a special
allocator, byte budgets, or exact memory accounting.

## Scope boundary

This is the S03 arena integrated beneath the existing reference backend. The
primary and secondary indexes are still standard maps and sets; optimized
indexes are S04 work. Capacity limits, byte accounting, and budgets are S05
work. Pins do not provide concurrent access, snapshot cursors, result/delta
cursors, R04 affected-record journals, persistent history, or recovery.

See [storage.md](storage.md) for the S01/S02 layout and reference-table
contract, [runtime_support.md](runtime_support.md) for the journal-backed
support-runtime behavior, and
[Decision 0012](decisions/0012-generational-arena.md) for the design record.
