# Pending delta epochs and recoverable delivery (D06)

Status: D06 is implemented and verified. Independent source/acceptance review
and all 66 tests pass GCC Debug/Release, ASan/UBSan, Clang18 and a fresh
source-only Release build; see the
[verification packet](verification/delta-lifecycle-2026-11-06.md).
The preceding [D05 packet](verification/ordered-delta-2026-11-06.md) records the
historical 64-test snapshot. The complete 78-card goal and O work remain open.

`DeltaRuntime::begin` returns a move-only `PendingEpoch`. It owns a private
physical source/count/support transaction, tentative L/P/B undo, a bounded
output spool and at most one heap-stable route producer. It does not expose
tentative records as ordinary public output. Existing `apply` is implemented
as `begin`, output-retaining `drain`, then `commit`.

## States and operations

| Pending state | Permitted progress / ownership |
| --- | --- |
| `pending_delta` | `step` stages a physical alias/prepares its route, processes at most one accepted core row, retires a completed route, or finishes epoch preparation. `pause`, `drain`, `start_drain`, `discard` and rollback are available. |
| `paused` | Retains the exact producer, endpoint views, selected witness, queue and undo. `resume` restores `pending_delta`; retaining `drain` resumes implicitly. `start_drain`/`discard` disable output retention. A direct `step` reports `delta_paused` without aborting. |
| `draining` | Delivery/retention is disabled, but `step`/`drain` still executes every required core projection, live/index update, queue prune, cursor termination and subsequent alias. It cannot resume delivery. |
| `epoch_prepared` | All aliases, cursors and views are finished and every throwing finalization check passed. `step` is idempotently prepared. `commit` publishes; `discard` drops output then commits; rollback still aborts. |
| `committed` | Closed pending token. Public input is accepted and a separate `Epoch` owns any committed records. |
| `aborted` | Closed token after rollback, destruction/move replacement, or preparation/production failure. Sequence/state remain at the previous commit. |

`DeltaStep::core_result` means one core result has been coupled to private L
and mapped/spooled when appropriate. `progress` and `prepared` expose phase
progress, not tuples. Scalar EXISTS can have a core result without a SQL
record and prepares its two opposite-sign replacement records at epoch end.
Source-free and unchanged/filter/count-only routes can finish without core
results. No-op events still consume their accepted sequence at commit.

Public `DeltaRuntime::state()` distinguishes ready, pending, paused, draining,
prepared and committed-output ownership. Its `ready()` additionally checks
physical reader leases. A closed pending token's committed/aborted state is
separate from that runtime state. One caller thread owns mutation; these are
ownership rules, not a thread-safe concurrent execution protocol.

During pending ownership, snapshots, current-result/view reads, invariants,
input and mode changes report `runtime_busy`; immutable identity/options,
committed sequence, mode, profile and lifecycle remain available. Early commit
reports `runtime_busy` and preserves the token. Invalid pause/resume reports
`invalid_delta_state`; closed/moved tokens report `invalid_delta_epoch`.
Pause/resume/polling performs no producer work and never reconstructs a cursor.

## Drain, disconnect and rollback

`drain()` finishes preparation under the current retention policy. It keeps
normal output private and bounded, and resumes a pause automatically.
`start_drain()` disables retention, clears any existing unpublished nodes and
sets every stage output interval to zero. It can then be stepped incrementally
or completed by `drain()`. `discard()` combines that operation, complete
internal draining and commit, returning an empty committed artifact.

Discard is not dropping an unfinished producer. Even with no records retained,
accepted core rows still run L/P/B coupling, future-witness pruning and every
later physical alias. Successful discard therefore accepts the same input
and final maintained state as normal production. Work/allocation/support
failure while draining instead aborts the whole unpublished input. Disabling
retention avoids future spool quota/allocation costs, while earlier spool work
and actual internal production remain charged.

Explicit rollback and token destruction choose abort rather than implicit
draining. The caller can use this policy on disconnect or choose explicit
discard to accept the input without delivery. Abort closes stage cursors and
their endpoint leases, then rolls back support/count/source and live/index
undo before public readiness. The same sequence can be retried. No noexcept
destructor starts potentially throwing production. Pending tokens retain the
runtime through facade moves/destruction; replacing a token first aborts its
old epoch. The complete source row is owned through a pin, independent of
the caller's input values after `begin` returns.

## Publication and committed delivery

Only `epoch_prepared` can commit. All throwing preparation/cleanup precharges,
SQL mapping and output construction finish before physical publication.
Actual nonthrowing source/support/driver/live cleanup runs within the commit
barrier. Commit, sequence tagging and ownership transfer allocate nothing.
A failed alias or resource check exposes no public fragment.
Committed input cannot be rolled back by a delivery error.

`Epoch::next()` moves one already committed owning row. `deliver_one(sink)`
instead borrows the front record for a callback and removes it only after
success. An exception retains the same tuple/ordinal and remaining spool for
retry or discard. The two-callback overload runs a serializer first and then
the sink, allowing their costs/errors to be measured separately. A serializer
failure does not call the sink. Callbacks own any external serialization
buffers and must apply their own resource policy; the engine's finite spool
does not cap arbitrary client allocations.

The callback holds a strong internal output owner, keeping its row alive
through facade moves/replacement/destruction. Reentrant `next`/`deliver_one`
reports `runtime_busy`. `discard()` during a callback defers release until the
borrow ends. If a callback explicitly discards or destroys the final output
owner, its exception does not preserve the output for later retry.

An external side effect followed by an exception may be repeated on retry.
This callback contract does not establish exactly-once or durable delivery.
Dropping unread committed changes leaves the input committed and requires a
fresh result snapshot before a subscriber can reconstruct a complete copy.
O06 still requires operational sink queues, bounded transport buffering,
durable prepare/commit/recovery and demonstrated delivery guarantees.

## Cost and mode boundaries

`step` yields real unfinished work rather than a precomputed public artifact.
Route support propagation/preparation and finalization can be data-dependent;
the API does not label every call constant-delay. The
[D05 bound](ordered_delta.md) applies to post-preparation producer transitions,
with explicit first/next/last accounting and separately charged finalization.
Pausing retains heap-stable endpoint views, cursor frames and extracted queue
keys. The route is fully retired before another physical alias stages.

`discarded_records` counts existing unpublished records cleared and future
mapped records skipped. Spool rows/bytes/capacity retain their prepared
high-water evidence even after discard. Clearing existing records/stage ranges
is finalization work and excluded from an open replay transition interval;
future skipped appends remain bounded producer actions. It does not reset
earlier work or pretend discarded output required no enumeration.

Separate `timings()` diagnostics report nanoseconds for physical propagation
(source/constraint/support/prefix-view setup and physical commit/abort),
internal delta work, native output mapping/spool construction, optional
serialization and sink callbacks. Nested phases are subtracted from their
parents. User pause time is excluded; sink time includes its CPU and wait.
Failed calls are timed too. These saturating wall-clock observations are
separate from deterministic abstract-work caps and mathematical bounds.
These instrumented phase samples do not exhaust total wall time: caller-side
callback construction, API dispatch and final owner/artifact teardown can have
additional costs. A serialized transport format and its allocation policy
remain the caller's responsibility until O06 supplies concrete sinks.

Maintenance mode stages/drains physical support without L/P/B or delta output.
Changing mode requires a writer-ready barrier with no pending or committed
output owner/read lease. Entering delta mode bootstraps validated live state;
failure keeps the previous mode and cache. Leaving drops all delta-only state.
This lifecycle does not supply O02 sessions, crash persistence or O06 sinks.
