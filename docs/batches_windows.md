# Ordered transport batches and operational windows (O03)

Status: O03 is verified. Independent transport, plain-label reference,
sequence-boundary and persistent-failure suites pass; all 79 tests pass GCC
Debug/Release, ASan/UBSan, Clang and a fresh source-only build. Astra source/
coverage acceptance is satisfied. See the
[acceptance record](verification/batches-windows-2026-11-06.md).
The existing [session lifecycle](session_lifecycle.md) and
[R06 initialization](runtime_initialization.md) remain the foundation.

## Typed ordered input

The [transport API](../include/crown/io/batch.hpp) owns typed `InputItem`s in
move-only `TransportBatch`s. An item is an ordinary full-row `InputEvent` or
an explicitly typed `WindowCommand`. A physical typed session accepts ordinary
events; a windowed session accepts commands. A mismatched item fails when it
reaches the head.

`QuerySession::create_typed` creates an open typed input. It also has an
initial-Database overload, using R06 full snapshot validation at sequence zero.
Stream-based factories retain their existing behavior.

```cpp
auto session = QuerySession::create_typed(plan);
io::TransportBatch batch(std::vector<io::InputItem>{
    io::InputEvent{{1, table, SetOperation::insert, row}, std::nullopt},
    io::InputEvent{{2, table, SetOperation::erase, row}, std::nullopt}});
session->enqueue(batch); // Check Admission::accepted or retry after full.
session->finish_input();
session->start();
// Each begin_next_result()/step()/commit()/output cycle accepts one event.
```

A batch packages ordered events; it does not consolidate them. The insert and
erase above produce two committed physical epochs and their individual deltas.
Each event still uses a genuine resumable D06 `PendingEpoch`. Unread output
blocks the next event, and snapshots describe the committed boundary.

Batch construction and admission enforce capacities. Catalog/domain/sequence/
source-position validation happens at the head, so malformed event k preserves
events 1 through k-1. Such semantic input errors are sticky. Allocation failure
in typed head preparation and engine rejection retain the same owned head and
queued tail for retry. Admission is allowed before start and while running;
paused, stopped and dropped sessions reject it precisely.

`enqueue(batch)` transfers ownership only on `Admission::accepted`. Full
rejection and allocation failure leave the caller's batch intact. Empty batches
are accepted and released immediately without becoming EOF. `finish_input()`
closes admission, while the queued prefix remains consumable. Later enqueues
fail with `input_closed`.

`begin_next_result()` returns `pending`, `would_block`, or `end`. An open empty
queue would block; a closed empty queue ends. The existing Boolean `begin_next`
throws `input_would_block` for an open empty queue and returns false only at EOF.
No background worker or arbitrary source callback participates in publication.

Queue limits now bound actual retained native batch/item allocation requests,
compact row descriptor/string blocks and source bytes/terminators, including
account framing. The current head remains counted through private work and whole
watermark expansion. Ack releases its node; batch descriptors remain until their
last item is released. Fixed queue/catalog/progress ownership and source-node
preparation are additional requests under the same original query account.
Offered TransportBatch limits still describe its external DTO storage. Numerical
queue byte totals change from the earlier ordinary Value/string-capacity/Decimal
estimate. Stream readers now also use native funded storage; instrumentation,
capture/report/diagnostic/async graphs remain open. This is not
complete S05 memory accounting. Source-position count/name limits still apply. Wire profile
settings and `InputLimits.total_bytes` are rejected for typed sources; batch/
queue bytes bound their typed storage. Input record limits count external
commands in window mode rather than derived physical transitions.

## Native typed queue admission

Execution constructs TypedQueue from the admitted CompiledProgram, sharing its
existing memory account and catalog owner. Admission preflights exact native
requests before copying, prepares the complete graph privately and reconciles
actual retained bytes before linking it. Full/OOM leaves the offered batch and
queue unchanged. Success empties the offered DTO after native rows/source text
and nodes are owned. No ordinary row mirror remains queued. Teardown detaches
links iteratively rather than recursively destroying long batch chains.

peek() returns a stable InputItemView until acknowledgement/close. Its event or
window values borrow native ownership; callers use InputEventView or
WindowCommandView and native runtime admission. Malformed row issues are deferred
without changing head-only validation/error order. Peek memory failure remains
retryable; semantic rejection remains sticky. AccountedInputProgress owns native
source-position controls/nodes/key text, prepares source nodes before engine work
and moves from close without allocation. Copies are charged value snapshots;
failed assignment preserves the old destination. Public session progress exports
remain caller-owned DTOs. See
[typed-input progress](verification/s05-typed-input-2026-11-09.md).

## Native window memory ownership

Window query sessions now fund actual label/count compact rows, expiration/FIFO/
relation nodes, active-command capacity, preflight cursors and prepared controls/
update payloads under their original query account. Retained managed-table options
share immutable WindowTables ownership. options() returns AccountedWindowOptions;
caller WindowOptions and canonical state exports retain their DTO roles.
Prepared updates expose native PhysicalUpdateView values valid through the
Prepared owner's lifetime. Native Delta admission imports its own row ownership
without creating an ordinary physical-update Row copy.

WindowMetrics.accounted_bytes and max_accounted_bytes measure native retained
payload/index descriptors plus active expansion capacity. Numerical values change
from the former ordinary Row-capacity estimate. These remain component payload
bounds. The query account also admits actual framing/tree/control/preparation
requests and rejects on its existing finite limit. This completes the scoped window graph. At the 9 November 2026 window-memory
checkpoint, input transport/reader/session/capture/diagnostic ownership and
whole-query S05 acceptance were still listed as open. S05 was subsequently
verified for the post-admission native runtime account, including reader, session,
window, capture and native report allocations. Caller-provided streams and their
existing I/O buffers, pre-import inputs and explicit exports remain outside that
account. See [window memory progress](verification/s05-window-native-2026-11-09.md),
[query memory contract](query_memory.md), and [S05 acceptance record](verification/s05-native-acceptance-2026-11-09.md).

## Window policy and full-row identity

`create_windowed(plan, window_options, ...)` enables explicit managed tables.
Each managed table must initially be empty; populated static tables outside the
managed set are allowed in the initial-Database overload. No timestamps or
labels are invented for R06 source rows.

Window event time is an adapter `uint64` domain, independent of SQL timestamp
types, processing order and source offsets. Width is positive. An insertion
has a positive strictly increasing label, a managed table, complete physical
row and timestamp. Deadline calculation checks `timestamp + width` for overflow.
Watermarks start at zero, cannot decrease, and expire deadlines less than or
equal to the requested watermark. Insertions before the completed watermark
fail with `late_window_event`. No allowed-lateness or correction policy is
enabled. Duplicate/reused/out-of-order label IDs and unknown withdrawals reject;
monotone IDs need only a scalar high-water mark, without historical tombstones.

Distinct labels for the same full row increase its reference count. Only a
zero-to-one count emits a physical insert; only one-to-zero emits a physical
erase. Other changes commit metadata without manufacturing a physical epoch.
Unused columns still distinguish physical rows even when their query projections
coincide. The controller scans its distinct full rows to find a matching count;
this is charged linear lookup, not an indexed-update performance claim.

Global FIFO permits withdrawing only the oldest still-live insertion label
across managed tables. Per-relation FIFO applies that rule within the label's
table. Insertion label order is distinct from timestamp order. Expiration uses
`(deadline, label)` order, with monotone labels also breaking equal deadlines.
The entire proposed expiration order is checked for FIFO before the watermark's
first effect. With A inserted before B but deadlines A=100 and B=10, watermark
10 rejects while A remains live under global FIFO. It never silently skips B
or reorders expiration to disguise the violation.

The original `global` and `per_relation` modes are label-FIFO policies. For A(label1), B(label2), A(label3),
FIFO label withdrawals can physically remove B before A. No physical-lifetime
FIFO theorem or X01 pattern-specific guarantee follows from this monitor.

The opt-in `physical_global` and `physical_per_relation` modes instead order
distinct full-row lifetimes using the existing count birth IDs. Metadata-only
label removals are allowed independently of label order; final-reference removal
checks the actual oldest row. Watermarks preflight all reference decrements in
one original-account counter vector before any effect. These modes preserve
their exact names and values through checkpoint/restore. See
[update patterns](update_patterns.md) for the prefix argument, costs, source-to-CQ
transfer limits and the remaining X01 planner work.

`unrestricted` (4) explicitly removes baseline FIFO ordering. Session
`update_patterns` can independently reject insertion-only lifetime endings and
enforce positive joint FIFO scopes. This path reuses native counts and one
whole-watermark counter vector, with no retained row mirror. The
[enforcement contract](update_patterns.md#enforce-a-declaration-through-querysession)
states stronger nonwindow erase-command rejection, origin, retry and cost rules.

## Steps, source progress and failure

External command sequence, committed physical sequence and watermark expansion
position are separate. Command sequences are contiguous; physical sequences
advance only for real full-row set transitions. A watermark may commit zero,
one or many label-removal steps. A zero-expiration watermark has an explicit
metadata-only step that advances its watermark and command progress.

For every step, label/count/index nodes, source progress and continuation
bookkeeping are prepared before engine work. A physical step owns a genuine
D06 pending epoch; metadata-only preparation has its own session phase. After
engine commit, window publication and final acknowledgement use nonthrowing
integer-keyed node transfers, erasures, scalar assignments and moves. Row-value
comparison is completed during preparation, before that publication barrier.

No later command passes an active watermark. Source positions and completed
command sequence advance only when its last step commits. Until then, snapshots
show the actual physical prefix plus active command sequence/completed/total
steps; they retain the preceding completed watermark. Every physical step has
the ordinary output barrier. `status().window`, `snapshot().window`, and owning
`window_state()` expose committed progress and label/count/expiration/FIFO state.
Private work rejects snapshots and window inspection.

Failure aborts only the current unpublished step. Earlier watermark steps
remain committed, and retry starts at the same unfinished step without early
source acknowledgement. Whole-watermark preflight checks policy and reserves
its abstract command work before the first withdrawal. Live-label and accounted
retained-byte limits include active expansion storage. Work limits count index
visits and row-column comparisons; ordered searches, scalar byte costs,
allocator overhead and transient prepared copies are additional. Initialization,
window control, physical maintenance and result production have distinct costs.

Pause stops admission and stepping. Explicit drain completes/discards only the
current step, and does not process the rest of a batch or watermark. Stop aborts
private work and releases queued/current-command storage without acknowledging
unfinished input. Committed runtime/label state and scalar active-command
progress remain inspectable; active expiration-vector storage is released.
Drop also releases runtime/window/progress state. Existing creator-thread and
reentry guards cover every new public session operation, with allocation-free
cleanup and no mutable owner/token escape.

## Extension boundary

Optional R2 atomic net batches are disabled. There is no flag that turns
`TransportBatch` into a transaction. A later separately typed atomic API must
validate whole-transaction constraints, consolidate signed changes, hide
intermediate output and account intermediate consolidation storage.

O04 must persist labels, counts, indexes, watermark and active expansion/source
progress under its own versioned restore contract. O05 owns interrupted-command
replay; O06 owns durable delivery/backpressure. Current owning snapshots and
canonical diagnostics do not provide recovery or exactly-once delivery.
