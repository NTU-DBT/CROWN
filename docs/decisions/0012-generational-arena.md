# Decision 0012: generational tuple arena ownership

The S03 ownership decision remains in effect. Its initial full-copy runtime
is superseded by [R04 support journals](0013-support-journals.md).

Status: S03 verified. The [verification audit](../verification/arena-2026-11-05.md)
records the complete 36-test compiler/sanitizer/clean-source matrix.

## Decision

Use a noncopyable, movable `TupleArena` as the owner of immutable tuple
payloads. Arena allocation identity is `(ArenaOwnerId, TupleSlotId,
generation)` and remains separate from the table's monotonic logical
`TupleHandle` identity. Keep slot objects at stable addresses in a vector of
`unique_ptr`s and maintain live and free membership with intrusive lists.

Erasure invalidates live membership immediately. Unpinned payloads are
destroyed and their slots become reusable; pinned payloads become retired,
remain readable through their pins, and cannot be reused until the final pin
is released. Closing or replacing an arena retires its live rows. Pins retain
the shared state so payload and metadata survive arena/table lifetime; after
the owner closes, the state is destroyed when its last pin releases it.
Generation exhaustion
prevents reuse instead of wrapping.

Keep `ReferenceTable` on the S02 standard-container primary and secondary
indexes. Its primary map borrows stable tuple addresses, and its ID map records
the exact arena allocation handle. Logical tuple and index IDs remain
monotonic and independent of arena slot reuse. Tuple values own strings, so
this implementation does not need a separate string dictionary or interner.

## Consequences and limits

Arena-level insert failure leaves every published slot, generation, and
counter unchanged. A later failure in `ReferenceTable::insert` rolls back
logical rows, indexes, public IDs, and revision, but a temporary successful
arena allocation can leave additional high-water metadata or an advanced
private slot generation. Slot metadata survives churn and clear. Statistics
count records, slots, and pins, not allocator bytes.

Foreign handles fail with `foreign_handle`; malformed or stale same-owner
handles behave as absent for `contains`/`erase` and throw `stale_handle` for
`get`/`pin`, in every build. Pin release, arena erase/clear, and counter reads
do not allocate. The invariant scan is O(total slots) and allocates temporary
visited arrays.

The arena is single-threaded and supplies payload retention only. Pins do not
preserve index membership, table cursors, or snapshots. `snapshot_copy()`
copies live rows into fresh storage/arena owners while preserving logical IDs
and index registrations; it omits retired payloads and pins. This does not
by itself reduce the initial support runtime's full-state copy cost or add R04 journals,
recovery, result cursors, or concurrency.

This stage adds no S04 optimized indexes, S05 byte budgets/accounting, special
allocator, dictionary ownership, or generation-exhaustion test strategy.
Generation wrap is guarded in code, but exhausting a 64-bit generation is not
a practical test path. See the [S03 arena contract](../tuple_arenas.md),
[storage contract](../storage.md), and [runtime support contract](../runtime_support.md).
