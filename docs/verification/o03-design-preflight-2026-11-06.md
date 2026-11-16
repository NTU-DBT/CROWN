# O03 read-only design preflight, 2026-11-06

Historical proposal: O03 was not started at this preflight. Astra read requirements
and actual O01/O02/R06 code without edits, builds or tests; root preserved this handoff.
O03 subsequently passed [implementation acceptance](batches-windows-2026-11-06.md).
The original [Refactor.md](../../Refactor.md) acceptance remains mandatory.

Implement ordered transport batches and operational windows, preserving every
R1 per-event barrier. Optional separately typed R2 atomic net batches are
conditional; disabling them explicitly does not redefine R1 as a net batch.

## Source and session integration

Replace the session's hard-coded reader dependency with a closed owned source
variant: existing owned-stream/borrowing EventReader, or a bounded typed queue,
optionally expanded by window control. Preserve real D06 PendingEpoch ownership;
do not wrap eager `apply` in a loop or call arbitrary user code after commit.

Suggested types are move-only TransportBatch, BatchLimits, QueueLimits,
Admission {accepted, full}, and BeginResult {pending, would_block, end}.
`enqueue(TransportBatch&)` transfers ownership only on successful bounded
admission; full rejection leaves the caller's batch intact. Shape/capacity
checks happen at admission, but semantic/order validation happens at the head,
so a malformed later event preserves its already committed prefix. Count the
current event in retained memory, not neither queue nor pending ownership.
An open empty queue would block; only closed empty input is EOF. The existing
Boolean begin API must not silently conflate those conditions.

Each ordinary batch event begins/steps/commits/acknowledges independently;
unread output/snapshots remain barriers. Insert then delete must remain two
observable events. Engine failure keeps the current decoded event and tail
for retry; malformed input is sticky with the committed prefix intact.

## Window definitions and FIFO

Use separately typed insert(label, table, full row, event time), withdraw(label)
and advance-watermark commands, with contiguous external command sequence and
optional source positions. Event time is an explicitly checked adapter integer,
not an implicit SQL timestamp or a legacy source offset.

Own a live-label ledger (full row/time/deadline/insertion ordinal), full-row
reference counts, expiration index ordered by deadline/ordinal, a global or
per-relation live insertion-order index, current command/expansion cursor and
prepared changes for one step. Distinct labels for equal full rows increase
counts; physical presence changes only on 0→1/1→0. Unused row columns still
distinguish identity. Monotone insertion label IDs with no reuse avoid an
unbounded tombstone history; duplicate/out-of-order IDs and unknown withdrawal
must reject precisely. This is not source replay deduplication/exactly-once.

Proposed first policy: positive checked width; monotone watermarks; expire when
timestamp+width <= watermark; reject insertion timestamps before the committed
watermark. Other lateness/correction policies require their own executable
semantics rather than being silently accepted.

FIFO means withdrawing the oldest still-live insertion label in the declared
global or per-relation domain, not merely nondecreasing timestamps. Preflight a
watermark's entire proposed expiration order for FIFO validity before its first
effect. A then B with deadlines 100 and 10 cannot expire B at 10 while A remains
live under global FIFO. Reject rather than skip/reorder or falsely label it FIFO.

Label FIFO is weaker than physical-set lifetime FIFO: A(label1), B(label2),
A(label3) can withdraw labels FIFO while physically removing B before A. Claim
only operational label FIFO unless a separate actual row-lifetime monitor is
explicitly implemented/selected. X01's theorem audit remains separate.

## Sequence domains and atomic publication

Keep external command sequence, committed physical sequence and active-command
expansion position distinct. Count-only label changes are explicit metadata-only
committed barriers; do not fabricate physical inserts/deletes to advance a
sequence. One watermark may produce several physical and metadata-only steps.
Each physical step retains a genuine D06 output barrier. The command remains
active until expansion completes; no later input passes it. Source positions
advance only after the entire originating command completes. Snapshots during
expansion report the physical prefix plus active-command/step progress.

Prepare all label/count/index/source nodes, checked counters and continuation
bookkeeping before engine work. After engine commit, publication uses only
nonthrowing node transfers/erasures/scalar assignments/moves. Metadata-only
steps follow the same prepare/publish discipline without a fake engine epoch.
Failure aborts only the current unpublished step; earlier watermark steps remain
committed and retry resumes at the first unfinished step.

Pause closes admission/stepping. Explicit drain completes/discards only the
current step, never the rest of a watermark/batch. Output blocks the next step.
Snapshot rejects private work but can show committed prefixes. Stop aborts
current private work, releases queued suffix/current-command storage without
acknowledging unfinished input, and preserves committed runtime/window-prefix
state for inspection; drop releases all state. Cleanup and guards remain O02's.

Ordinary typed batches may use R06 nonempty initialization. Windowed managed
tables must initially be empty unless a later explicit InitialWindowState
validates all labels/times/counts against source rows. Do not invent timestamps
or labels for R06 rows. Non-windowed static tables may remain populated.

## Tests and remaining choices

Build an independent reference from a plain label list, timestamp filtering and
full-row counting; feed only true row transitions to the independent evaluator.
Test all partitions of short traces, cancellation that remains observable,
self-join/alias expirations, duplicate labels/equal rows/projection collisions,
global/per-relation FIFO, equal and out-of-order times, late/decreasing/overflow
watermarks, zero/one/many expiration steps, count-only steps, malformed/engine
failures inside batches, queue full/open/closed states, partial command/source
progress, initialized-state rejection, Boolean/EXISTS and empty deltas.

Persistent fault sweeps must compare runtime canonical state plus labels,
counts, FIFO order, expiration state, sequence domains and source progress
after admission, validation, node preparation, D06 work, metadata-only steps,
snapshot and cleanup failures. Retry must resume the same failed step.

Settle policy choices before coding: initial strict late rejection/boundary,
label FIFO versus optional stronger physical monitor, per-step watermark
visibility/completed-command acknowledgement, monotone IDs and initially empty
managed tables. Conditional R2 AtomicNetBatch must be a separate type with
whole-transaction constraint/net-delta/publication semantics if enabled; current
single-event epoch composition alone is insufficient. O04 must later persist
labels/expansion; O05 owns interrupted-command replay and O06 durable delivery.
