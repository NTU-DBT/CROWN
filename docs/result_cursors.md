# Current result cursors (D01)

Status: D01 implemented and verified. At that checkpoint, all 45 tests passed GCC Debug/Release,
ASan/UBSan, Clang18 and a fresh source-only Release build; see the
[verification packet](verification/result-cursors-2026-11-06.md). The later
[D02 cursor](epoch_views.md) adds separate before/after fragment views,
all-variable projected completions and full local witness assignments.
The [D04 delta owner](delta_runtime.md) reuses its completion cursors for
projected deltas; optimized delay and operational delivery remain D05–D06/O work.

This page describes the committed-result cursor exposed by
[`SupportRuntime`](../include/crown/runtime/support.hpp) and
[`PhysicalRuntime`](../include/crown/runtime/physical.hpp), implemented in
[`support.cpp`](../src/runtime/support.cpp) and
[`physical.cpp`](../src/runtime/physical.cpp). A cursor reads one committed
logical epoch. It does not expose a pending update's tentative state.

## Traversal and output rows

`SupportRuntime::results()` defaults to the core view. On a tree route, the
cursor walks the compiled enumeration steps over the current live `E` tables.
It keeps one frame per step. The root frame opens a `ReferenceTable::live()`
cursor; a child frame projects the selected parent tuple to its separator key
and opens a `bucket_cursor()` on the compiled index. Native `next_entry()` yields the borrowed tuple together with its handle;
selection uses that tuple directly. These storage cursors hold native traversal
state; result enumeration does not call `snapshot()` or `bucket()` to build
owning vectors. The historical `tuple_lookups` work category counts selected
tuple accesses here, rather than an additional native handle-to-row lookup.

The cursor does not build a result relation, retain emitted rows, or keep a
deduplication history. Once a complete assignment is reached, it constructs
that output row and returns it. Each returned `storage::Tuple` owns its values,
so it remains valid after the cursor closes or a later update changes runtime
membership.

The core view emits slots in the plan's core result order and uses the core
result layout. For a normalized SQL plan, `PhysicalRuntime::results()` emits
the declared SQL output order: core-column mappings may repeat, and constant
outputs are copied into their positions. `core_results()` bypasses that SQL
mapping. The SQL output layout descriptor is made once in the runtime and
copied into each cursor; its identity is stable across that runtime's cursors,
and cursor creation does not change the plan artifact. For an SQL `EXISTS`
wrapper, SQL view returns exactly one Boolean row, including a `false` row
when the committed query has no answer.

The order of output tuples is unspecified. Output columns follow the declared
core, SQL or fragment schema, including repeated SQL columns.

## Read lease and runtime lifetime

Creating a cursor requires that no prepared update is active. A successful
cursor holds a read lease on the logical runtime. `ready()` is therefore
false while any cursor is leased. Multiple cursors and ordinary reads can
coexist, including `has_answer`, lookups, storage statistics, invariant
checks, and diagnostic snapshots.

Calls to the reference runtime remain externally synchronized. A read lease
is a lifecycle guard; it does not add inter-thread locking.

Every update is blocked while a cursor lease is active, including duplicate
inserts and absent-row erasures that would otherwise be no-ops. This applies
to logical and physical updates. Conversely, while a prepared writer is
active, the runtime is not readable and result-cursor creation fails. A
cursor's read lease lets the table iterators and selected tuple references
remain valid without pinning every result row.

Returning the last row does not close the cursor. Consume its terminal null
or call `cancel()` when stopping early so the next update can proceed.

The active cursor holds a shared reference to the logical `SupportRuntime`
implementation. It therefore remains usable after its runtime facade is
moved or destroyed. A cursor obtained from `PhysicalRuntime` retains the
logical support state it traverses; physical source tables belong to the
physical facade's implementation and need not stay alive for cursor reads.

## Cursor states and close behavior

The public states are `active`, `exhausted`, `cancelled`, and `failed`.

- `next()` returns an owning tuple while a row is available.
- When traversal ends, `next()` returns null and releases the lease. Repeated
  calls on an exhausted cursor return null.
- `cancel()` releases the lease immediately. Repeated `next()` calls on a
  cancelled cursor return null. Destroying an active cursor cancels it.
- If `next()` throws, the cursor records the failure, closes the lease, then
  rethrows. Later `next()` calls on that failed cursor throw `invalid_cursor`.
  Rows returned by earlier calls remain valid.
- If cursor creation fails during option validation or startup, it has not yet
  registered a reader lease, so runtime reader state is unchanged.
- A moved-from cursor reports inactive from `active()`; its state, sequence,
  owner, layout, metrics, and `next()` accessors throw `invalid_cursor`.

Close and cursor moves are `noexcept` and do not allocate. Closing clears the
traversal frames and drops the cursor's shared reference to the logical
runtime. The closed cursor retains its state/sequence/owner, output layout,
metrics, and retained immutable compiled program until the cursor object is destroyed; it does not
retain the runtime `State`. If a facade has already been destroyed and the
cursor releases the last reference to the logical implementation, destroying
that whole query state is outside the cursor's abstract work counter.

## Work accounting

`ResultCursorOptions::work_limit` defaults to 1,000,000 abstract work units;
`nullopt` disables the limit. One cursor's limit is cumulative across startup
and all calls to `next()`. It is not reset after each row. Startup records one
route check and, except for SQL `EXISTS`, one frame initialization per
enumeration step. This does not visit result records. The cursor also retains
the immutable compiled program and creates its frame storage; these costs are
not represented as record visits in the cursor counters.

`ResultCursorMetrics` separates startup, row-producing calls, termination,
and failed-call work. `last` describes the most recent active `next()` call;
`max_result_work` is the largest counted work for a call that returned a row.
The per-call counter includes cursor opens and advances, bucket lookups and
key fields, tuple lookups, selected rows, frame closes, equality checks,
output fields, and emitted rows. `total_work` aggregates those counted units
over startup and subsequent calls. Mandatory frame cleanup is uncharged and
reported separately by `cleanup_frames` (at most the number of frames).

These counters describe abstract operations. Ordered table/index lookups,
iterator costs, descriptor/frame preparation, tuple construction, and copies of variable-width
values have costs beyond the counter. The work limit and `max_result_work`
therefore do not certify constant delay or a wall-clock bound.
