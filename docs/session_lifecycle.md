# Query/session lifecycle (O02 and O03)

O02 was implemented and verified. Its independent Astra source review and
71-test five-configuration matrix are historical. See the
[O02 packet](verification/session-lifecycle-2026-11-06.md) and
[500-input manifest](verification/session-lifecycle-sources.sha256).
The [O01 packet](verification/physical-input-2026-11-06.md) is the preceding
verified 69-test snapshot; its hashes do not describe these session edits.
R06 adds the initial-database session overload and runtime inspection. Its
75-test five-configuration matrix and source seal are historical after O03.
O03 typed queues and operational windows are acceptance-verified: all 79 tests
pass in the five-configuration matrix, including transport/boundary,
independent window/failure and existing session targeted checks. See the
[R06 verification packet](verification/runtime-initialization-2026-11-06.md)
for its historical matrix configurations and timings, the
[O03 verification packet](verification/batches-windows-2026-11-06.md) for the
current acceptance record, and the [runtime initialization contract](runtime_initialization.md).

The API is [session.hpp](../include/crown/runtime/session.hpp), implemented in
[session.cpp](../src/runtime/session.cpp). The existing
`QuerySession::create(plan, input, options)` factory still accepts a verified
physical plan and an owned `unique_ptr<istream>`, installs an empty database,
and starts at accepted sequence zero. R06 adds
`QuerySession::create(plan, initial_database, input, options, build_options)`;
it creates the runtime from that full snapshot while keeping accepted input
progress at zero and source-position metadata empty. The initial database is
not represented as fabricated stream events or positions, and the first later
external update is sequence one. SQL compilation remains upstream.
Native checkpoint/restore is described in
[the checkpoint guide](checkpoints.md); durable WAL/generation recovery is described
in [the journal guide](session-journal.md) and [generation guide](generations.md).
Both factory forms expose their actual
epoch-zero result, including native nullary truth and scalar SQL EXISTS false
where applicable.

O03 adds `create_typed` for bounded ordered `TransportBatch` input and
`create_windowed` for explicit operational window commands. Typed APIs remain
library-only. Their session, queue and window-specific behavior is summarized
in the [O03 batch and window guide](batches_windows.md); the O02 behavior below
continues to define the ordinary one-physical-event epoch lifecycle.

The session is synchronous, noncopyable and nonmovable, held by its returned
`QuerySession::Owner`. This AccountedUnique funds the facade and stable
implementation under the runtime's original finite account; its stored deleter
keeps that account alive through final deallocation. Existing `auto` factory
callers continue to work; explicit ordinary `unique_ptr<QuerySession>` declarations
must use `QuerySession::Owner`. Its creator thread owns every public operation, including
status/progress, stop and drop. A different thread reports
`session_wrong_thread` before reading mutable session state. A nested operation
on the creator thread reports `session_busy`, including reentry through an
owned stream. Destruction requires exclusive lifetime ownership and performs
private nonthrowing cleanup without public thread checks. An input callback
must not destroy the session whose operation is currently using that input.

## Control states and work phases

Control state is `created`, `running`, `paused`, terminal `stopped` or terminal
`dropped`. Separately, work phase is `ready`, `pending`, `paused_pending`,
`draining`, `prepared` or `output`. Thus a paused session can retain unfinished
private work or already committed output without confusing their visibility.

Every public operation first checks writer identity, then reentrancy. State
errors precede phase errors. In this table, phase rules below apply after the
control-state check:

| Operation | Created | Running | Paused | Stopped | Dropped |
| --- | --- | --- | --- | --- | --- |
| `status` | Status value | Status value | Status value | Final status | Tombstone status |
| `progress` | Empty accepted progress | Accepted progress | Accepted progress | Final accepted progress | `session_dropped` |
| `start` | Become running | Idempotent | Resume admission/private pending work | `session_stopped` | `session_dropped` |
| `pause` | `session_not_started` | Become paused | Idempotent | `session_stopped` | `session_dropped` |
| `begin_next`, `step`, `commit` | `session_not_started` | Phase rules | `session_paused` | `session_stopped` | `session_dropped` |
| `start_drain`, `drain`, `next_output` | `session_not_started` | Phase rules | Phase rules, retain paused control | `session_stopped` | `session_dropped` |
| `snapshot` | Actual epoch-zero result | Phase rules | Phase rules | Final committed result | `session_dropped` |
| `stop` | Become stopped | Become stopped | Become stopped | Idempotent | Idempotent, stay dropped |
| `drop` | Become dropped | Become dropped | Become dropped | Become dropped | Idempotent |

| Operation | Ready | Pending / paused pending / draining | Prepared | Committed output |
| --- | --- | --- | --- | --- |
| `begin_next` | Peek one validated event and begin private input; false at clean EOF | `session_pending_epoch` | `session_pending_epoch` | `session_output_pending` |
| `step` | `session_no_pending_epoch` | One genuine D06 private producer step, subject to the running control gate | Idempotent `DeltaStep::prepared` | `session_no_pending_epoch` |
| `commit` | `session_no_pending_epoch` | `session_epoch_not_prepared`, subject to the running control gate | Publish input and retained output, acknowledge source | `session_no_pending_epoch` |
| `start_drain` | `session_no_pending_epoch` | Disable retention and enter/continue draining | Disable retained output, remain prepared | `session_no_pending_epoch` |
| `drain` | Idempotent, reads nothing | Finish every internal row/alias, commit input and discard output | Commit input and discard output | Discard and destroy the committed output artifact |
| `next_output` | `nullopt` | `session_pending_epoch` | `session_pending_epoch` | Return one owning signed row; destroy the artifact when exhausted |
| `snapshot` | Current committed result | `session_pending_epoch` | `session_pending_epoch` | Current committed result, without consuming output |

`pause` on actual `pending` calls D06 `PendingEpoch::pause`; `start` resumes
that same cursor. Draining/prepared/output have no D06 pause state, so pause
there closes only the session admission/stepping gate. No background work runs.
Explicit `drain` may finish a paused input while leaving the control state
paused. `start_drain` may also disable retention while paused; later `start`
does not incorrectly call D06 resume on a draining/prepared token.

`drain` means the current input/output only. It never reads another record or
drains an entire file. Beginning the next event always requires an explicit
`begin_next` call. Repeated EOF returns false without advancing accepted
progress. No-op, filtered and count-only events still commit their sequence
and optional source position exactly once.

`status` returns control/phase, committed sequence, sticky input-failure and
observed-EOF flags, optional private sequence/work and retained output count.
O03 adds optional queue statistics, window progress and pending command
sequence. Private diagnostics are not public query results. After drop, status
retains only scalar diagnostic values; progress and snapshots reject.

## Ownership, commitment and failure

The stable session implementation owns its stream before its reader, so the
borrowed stream outlives `EventReader`, including construction failure. One
private `DeltaRuntime` and at most one pending/output token remain inaccessible
to callers. There is no returned lease, mutable runtime reference or callback
that could let another writer cross the ownership barrier.

`begin_next` validates source order/catalog binding before D06 begin, then
returns with genuine unfinished input. It does not call the eager
`OrderedReplay::apply_next`. Repeated `step` stages at most one accepted core
row per D06 step, preserving the qualified preparation/finalization costs.
Output stays private until prepared `commit` completes the whole physical
event. After engine publication, only nonthrowing source acknowledgement,
token/epoch moves and cleanup, and scalar updates occur. No progress copy,
user callback or report construction follows the publication barrier.

Input parse/order/allocation errors are sticky, without accepted-progress
changes. The original lower-level diagnostic is retained; later peeks report
`input_failed`. Engine begin/step/start-drain/drain failure aborts and destroys
the private token while retaining the decoded source event and old accepted
progress for retry. The running/paused control state remains unchanged.
Invalid control/phase calls do not abort legitimate pending work. Snapshot
failure closes its local cursor and preserves the session and unread output.

`next_output` moves an owning committed row. Its final row also destroys the
epoch object, releasing journals/source pins rather than merely opening the
next-input barrier. Caller-owned returned rows remain valid after later input
or drop, retaining their values and immutable layout metadata. Delivery is
the caller's responsibility and does not define a durable acknowledgement.

`stop` is terminal: roll back and destroy private input, discard and destroy
committed output, then release the cached input, decoder and owned stream.
Already committed data/progress remains available for stopped snapshots.
Stop never acknowledges unfinished input. `drop` also destroys committed
runtime/plan state and accepted progress. Valid cleanup allocates nothing;
public thread/reentrancy errors can still throw. User-provided stream
destructors have their own C++ nonthrowing destruction responsibilities.

The [reader API](../include/crown/io/ingest.hpp) adds
`EventReader::close() noexcept`: move accepted progress out, destroy decoder/
cached event and leave the borrowed stream alone. It does not accept a cached
event. Closed peeks/progress/catalog/counter accessors report
`invalid_input_reader`; acknowledgement remains a no-op, `failed()` is false
and repeated close returns empty progress. Session stop uses this move rather
than copying an allocating source map during cleanup.

## Bounded owning snapshots

`snapshot()` materializes actual committed results in configured core/SQL
output order through a local D01 cursor. Sequence, accepted progress, layout
and rows refer to one committed epoch. It is allowed during committed unread
output and after stop, and rejects every unpublished phase. It never silently
drains or commits input to obtain a snapshot.

`SessionSnapshot` owns its tuples, progress and immutable layout. Its read-only
`SessionRows` collection has a default 65,536-row / 64 MiB retained-storage quota, configured in
`SessionOptions.snapshot` or overridden for one call with `SnapshotLimits`.
`accounted_bytes` sums the actual shared collection/control and capacity requests
plus each native tuple's real compact scalar/shared-owner requests, including
account framing. Binary strings and exact decimals live in compact native
payloads. Shared program/layout metadata is charged once to the original query
account outside this sublimit. Zero rows/bytes accept only an empty result; a scalar
EXISTS false row or nullary true row is still a result row.

Collection copies share immutable native storage without allocating; use normal
read operations such as size, indexing and iteration. References/iterators borrow
from a live collection handle. Explicit mutable-vector callers need their own
external export. Copying a full snapshot can still allocate its progress map.

The quota describes retained snapshot storage. Cursor-produced candidates/scratch
and transient old/new capacity blocks during growth consume the same finite query
account outside that retained total. Caller-held snapshots stay charged after
session destruction and can reject another allocation under the original query
cap; releasing them permits a retry without changing the committed epoch or
allowance. Empty rows have no collection/control/capacity allocation. Source
count/name limits bound progress metadata. At the 9 November 2026 session-owners
checkpoint, ordinary progress-map copies were still listed for migration. Cursor work is separately bounded by `SnapshotLimits.cursor`.
Snapshot work and memory are output-sensitive. At that 9 November 2026 session-owners checkpoint, nested input/queue/window/capture
graphs and published epoch arrays were still listed for funding/reconciliation.
S05 was subsequently verified for the post-admission native query account, including
session/input/queue/window/capture storage; see the [query memory contract](query_memory.md)
and [S05 acceptance record](verification/s05-native-acceptance-2026-11-09.md). See
[session ownership evidence](verification/s05-session-owners-2026-11-09.md).

## O03 typed queues and operational windows (accepted)

O03 adds the typed factories `create_typed` and `create_windowed`, plus bounded
move-only `TransportBatch` admission. All 79 tests pass in the five-configuration
matrix. The 435-input native fingerprint is
`e035d699fe49312aea9307c43e597eb70af6989db295b84205baf85c806a64b0`.
The preceding R06 75-test matrix and source seal are historical. See the
[O03 verification packet](verification/batches-windows-2026-11-06.md) for
matrix results and the [batch and window guide](batches_windows.md) for queue
accounting and window policies.

`enqueue(batch)` returns `accepted` or `full`. Acceptance transfers the batch;
`full` leaves it with the caller. Empty batches are accepted without closing
input. A queued physical `InputEvent` retains its O02 begin/step/commit barrier,
so every event publishes its own physical delta. The optional R2 atomic net
batch mode is explicitly disabled.

Typed input stays open until `finish_input()`. `begin_next_result()` returns
`pending` when an item is available, `would_block` when the open queue is
empty, and `end` when the queue is finished and empty. The Boolean
`begin_next()` throws `input_would_block` in the open-empty case; false means
validated EOF. Finishing closes admission while retaining the queued prefix
for consumption. A paused session rejects both new admission and stepping.

`create_windowed` accepts explicit label, withdrawal and watermark commands
under `WindowOptions`. Event timestamps use a separate adapter `uint64` domain.
Watermark expansion may commit several physical row transitions while the
external command stays pending; queue/window progress and canonical state are
reported through the owning inspection APIs. The independent window/failure
and sequence-boundary suites pass. No CLI was added.

O04 checkpoint/restore, O05 WAL, O06 durable sinks/backpressure and O08 public
CLI release remain separate cards. R06 initialization/rebuild and inspection
are verified in the historical R06 snapshot; see the
[R06 verification packet](verification/runtime-initialization-2026-11-06.md).
A session snapshot is an owning result, not a checkpoint.

For a verified `plan` and owned `input`, a retaining loop is:

```cpp
auto session = QuerySession::create(plan, std::move(input));
session->start();
while (session->begin_next()) {
  while (session->step() != DeltaStep::prepared) {}
  session->commit();
  while (auto record = session->next_output()) {
    // The caller now owns record and its delivery/retry policy.
  }
}
auto final_result = session->snapshot();
session->stop();
```

To discard the current epoch's output, use `drain()` instead of retaining
stepping/commit; the next event still requires a new `begin_next()` call.

## Native typed input ownership

Typed and windowed sessions now admit compact native batches under the original
query account. The compiled program supplies both budget and catalog authority.
Admission leaves offered caller DTOs intact on full/OOM and releases them only
after native ownership is complete. Input views and prepared source-position
nodes stay owned through pending engine work and whole watermark expansion.
Acknowledgement/commit/close/stop allocate nothing. Stopped typed progress keeps
its native map/control/key storage; drop releases it. Public progress/snapshot
methods explicitly export their caller DTOs without retaining an ordinary
operational progress mirror in the typed path.

Stream readers now also own funded framing/native decoder/cached rows/source
positions/progress under the original CompiledProgram grant. Reader and immutable
run context share native input options; both stream and typed stop/close transfer
native accepted progress without allocation. Stream parse/order/allocation errors
remain sticky and require explicit recreation, while engine rejection retains
the cached event. At the 9 November 2026 stream-input checkpoint, operational instrumentation,
capture/report/diagnostic/async graphs and whole-query S05 acceptance were still
listed as open. S05 was subsequently verified for the post-admission native query
account, including funded stream/typed reader state and native capture/report/
diagnostic allocations. Caller-provided streams, standalone compiler/parser work
and explicit exports remain outside the account. See the [query memory contract](query_memory.md),
[S05 acceptance record](verification/s05-native-acceptance-2026-11-09.md),
[stream-input evidence](verification/s05-stream-input-2026-11-09.md), and [typed-input evidence](verification/s05-typed-input-2026-11-09.md).

Optional `SessionOptions::update_patterns` admits an actual source-bound
declaration at creation. Guards precede journal/native preparation; committed
status separates physical and command progress from private work. Window
contracts operate on full-row lifetimes; nonwindow insertion-only uses stronger
erase-command rejection. Recovery labels the prefix as trusted checkpoint history,
and replacement retains enforcement against the same source. See the
[usage and cost rules](update_patterns.md#enforce-a-declaration-through-querysession)
and [V52 controls](verification/update-pattern-runtime-v52-2026-11-14.md).
