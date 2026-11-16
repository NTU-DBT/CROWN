# O07 cursor observation — excluded proposal, O07 NS

This unapplied layer implements optional cursor timing and explicit committed
state cardinality reads above frozen **run-context → mode-binding → runtime**
proposals. Native sources, tests, CMake, prior proposals, ordinary documentation
and historical seals remain unchanged. O07 remains **not_started**. Author
validation is compiler/linker only; no generated binary is executed.

## Cursor API and scope

`SupportRuntime::ResultCursor::observation()` returns an independent fixed-size
`CursorObservation`. It contains owner, sequence, per-owner cursor identifier,
construction status, view, source kind, optional snapshot side, whether the
source was tentative at creation, exact cursor work limit and observation options,
immutable begin-runtime `ObservationConfiguration` when recorded, current
terminal state/reason, copied mandatory `ResultCursorMetrics`, and a fixed metric
array. No tuple, native string, layout, plan, journal or callback is retained by
the copied value. Its static assertion requires trivial copyability.

Source kinds distinguish committed `results()` from epoch visible completion,
witness, visible-key and visible-bucket cursors. The latter can be private delta
implementation cursors, committed snapshot fragments, or tentative before/after
views; `side` and `tentative_at_creation` preserve that distinction. Binding a
cursor to a current runtime configuration does not claim it is delta output or
inherit a future mode-switch configuration. Lower support/physical-only cursors
and unpublished bootstrap cursors can have no delta configuration. Off also
leaves that optional binding absent. Requested options are preserved separately
from the resolved begin-mode/completion in the existing immutable descriptor.

`last_cursor_observation()` on SupportRuntime, PhysicalRuntime, DeltaRuntime and
QuerySession returns the latest **enabled cursor lifecycle publication**, not a
sum, latest input event, or global enumeration total. Concurrently live cursors
can publish in a different order from construction. Cursor IDs count admitted
constructions including internal/bootstrap cursors and failed constructors;
owner + ID has process-local diagnostic meaning only. IDs saturate with an
explicit flag instead of causing a semantic error. QuerySession retains this
fixed value at stop/drop before releasing its runtime. A copied value survives
all owner destruction; optional off retains no runtime last-cursor history.

A valid cursor remains inspectable after exhausted/cancelled/failed close, even
when its runtime facade has been destroyed. Moving a cursor preserves its heap
stable data and observation. The moved-from accessor rejects with the existing
`invalid_cursor` contract. Move assignment first closes the previous destination
with reason `move_replacement`. Explicit cancel, destructor cleanup, exhausted
next, active next failure, tentative-view invalidation and constructor failure
have separate terminal reasons. Repeated next on exhausted/cancelled cursors and
repeated cancel leave diagnostics unchanged. Rejected next on a previously
failed/moved cursor is not an active enumeration call and is not timed.

## Timing and accounting contract

`cursor_observation_registry()` declares fixed IDs, names, units and scopes:

| Measurement | Exact boundary |
| --- | --- |
| `startup_ns` | Allocation, cursor construction/preparation and lease/link acquisition after public admission guards, before return. Failed construction includes its unwind. |
| `successful_next_ns` | Sum of active next calls returning an owning row; includes traversal/output assembly and mandatory accounting. |
| `exhausted_next_ns` | First active next returning no row, before cleanup. |
| `failed_next_ns` | Active next which throws, before cleanup. |
| `cleanup_ns` | The admitted cursor's close: frame/probe/binding cleanup, unlinking and lease/context/runtime release; excludes final cursor-owned plan/layout/member destruction. |
| successful / exhausted / failed calls | Counts of the corresponding active calls; startup failures are separate. |
| cancel / cleanup calls | Explicit cancel while active / admitted cursor close. |
| clock reads / regressions | Optional clock invocations for this cursor / backward intervals. |

These are elapsed nanoseconds during active operations, not process CPU time.
Caller pause, user processing between next calls, and later serialization/sink
work are excluded. One cursor's admitted startup, active-call categories and
cleanup intervals are disjoint. Empty results still have startup, exhausted
advance and cleanup; nullary/Boolean cursors still distinguish emitted rows from
termination. Partial consumption followed by cancel preserves work and records
cleanup separately. No no-output shortcut bypasses mandatory enumeration work.

**Nested epoch-view cursor intervals may be contained in an enclosing delta
propagation/internal phase. They are not additive with that enclosing wall time.**
All timing registry scopes state this. `cursor.nested_clock_reads` in the delta
registry counts cursor clock calls only while that delta attempt is current.
For such an attempt, its global fake-clock calls reconcile as
`delta.clock_reads + cursor.nested_clock_reads`. The nested count is a subset of
per-cursor `clock_reads`; never add both. Current-result calls after publication
never increment an old last-attempt value. Calls during bootstrap or outside an
active delta attempt belong only to their per-cursor clock count.

The clock implementation reuses the existing exclusive testing clock override.
Raw reads avoid incrementing delta's own phase-clock counter. Counters and off
make **zero optional clock calls**; trace times cursors only if `trace_timings`
is enabled. Per-cursor timing/counters are not controlled by per-update trace
sampling and do not append per-tuple strings or cursor causal records. All new
hooks are nonallocating and nonthrowing. Diagnostic counters/times saturate with
an overflow flag. A backward test/platform clock makes the affected timing
unavailable, increments regressions, and never changes query execution or
silently asserts a zero duration. Available exact zero remains distinguishable
from disabled or unavailable values.

Mandatory startup/results/termination/failed/last work, lifetime total work,
maximum successful-result work, cursor limits and cleanup-frame counts retain
the existing charge sites and arithmetic. `last` is already part of the relevant
results/termination/failed subtotal and is not additive. Optional off still
returns these mandatory saved metrics and actual cursor state. It exposes
optional metrics as disabled and terminal reason as not recorded.

## Construction failure and ownership

The factory owns a fixed scratch summary during admission. Enabled constructor
work charges copy existing mandatory metrics into that scratch. A failure before
a cursor can be returned publishes failed startup via the runtime's last-cursor
read; no new exception classification or semantic validation is introduced.
A delegating-constructor failure also preserves its mandatory cleanup-frame
count. Failed startup has no separately measured cleanup interval: cleanup time
and cleanup-call measurement are **unavailable**, rather than fabricated zero,
because unwinding is included in startup. Public guard failures before cursor
construction (invalid view, closed view, unreadable runtime) do not create a
cursor identity or overwrite a prior observation.

Successful admission clears the scratch pointer before publication. Every cursor
owns the runtime's existing observer handle plus a weak diagnostic-owner handle.
Its copied summary has neither. Close may therefore release the last runtime
owner, finish its timing safely, and retain diagnostics in the cursor; it only
publishes to a runtime if that owner still exists. No new shared ownership cycle
or tuple pin is introduced. Explicit cancel and failure cleanup do not allocate.
Existing frame construction/output-row allocation remains necessary query work.

## Committed state gauges and unavailable facts

`committed_state_gauges()` on SupportRuntime, PhysicalRuntime and DeltaRuntime
performs an explicit allocating diagnostic read at a readable committed barrier.
It reserves only numeric metadata vectors and reads table cardinalities; it does
not materialize tuples, enumerate joins, mutate update accounting, read clocks,
or require optional telemetry. Pending private updates reject this read using
the existing readable guard. It is available with observation off.

Physical/delta reads give each owned source table's base tuples and their total,
counting each source table once despite aliases. Logical support-only reads have
no physical source authority, so base total remains unavailable. Per node the
read reports native/generalized kind, record tuples, survivors, projected parent
keys and visible **E-factor** assignments. Nodes outside C* have unavailable
visible counts. Per-node factor cardinalities are not full answer cardinality;
joins/products and projected aliases must not be inferred by summing them.
An exact zero in an applicable stored table is reported as available zero.

Full-result count, allocated/live bytes, checkpoint bytes/time and recovery
replay length are explicit unavailable `MetricValue`s. Existing S05 component
payload accounting cannot be promoted to total allocator memory. Metadata vector
allocation here is an additional diagnostic cost, outside update/spool/queue
payload caps. No durable/recovery, overall memory or performance claim follows.

## Export and integration boundary

`io::write_cursor_observation_json()` and
`io::write_committed_state_gauges_json()` produce version-1 bounded, owning JSON
companions outside mutation. Cursor export includes exact begin configuration,
all mandatory work fields, registry units/scopes and optional availability.
Disabled/unavailable measurements serialize value and saturation as null;
available zero remains numeric zero. Gauge export keeps unsupported facts null
and labels the E-factor/full-result distinction. These exporters receive only
numeric/enum diagnostics and constant descriptors; they introduce no native
value JSON conversion, admission hash, tuple formatting or failure-unwind JSON.

The frozen EXPLAIN CLI and its schema are rebuilt only as ABI consumers. They do
not silently acquire new CLI behavior or a different accepted schema. Native
human/JSON integration and schema extension remain required; the companion
functions are concrete library seams ready for independent output tests.

## Pinned build and ABI evidence

Include precedence is **cursor → run-context → mode-binding → runtime → EXPLAIN
→ native**. `cursor-observation.patch` is unapplied against that layered baseline.
`patch-baselines.json` names exact predecessor files; `baseline-sha256.json` pins
those packages, native dependencies and reused non-runtime archives.

The new registry entry changes `MetricId::count` and all observation snapshot
layouts. Rebuild **all nine runtime TUs and every app/test/report consumer**.
Do not link any old runtime/mode/run-context object or archive. The fresh layered
ABI audit rechecks 49 non-runtime TUs: core IO batch → ingest → IR still does not
consume these changed headers, so exact pinned core/plan/sql/PG archives can be
reused. Runtime replay/window/IO support/inspection are rebuilt as well as the
changed units. Compiler-generated dependency hashes accompany every object.

```sh
python3 docs/verification/o07-cursor-observation-proposal/build_proposal.py /tmp/crown-o07-cursor-observation-testing --testing --opt 0
python3 docs/verification/o07-cursor-observation-proposal/build_report.py /tmp/crown-o07-cursor-observation-report-testing --runtime-evidence /tmp/crown-o07-cursor-observation-testing/compile-evidence.json
python3 docs/verification/o07-cursor-observation-proposal/build_proposal.py /tmp/crown-o07-cursor-observation-production --opt 3
python3 docs/verification/o07-cursor-observation-proposal/build_report.py /tmp/crown-o07-cursor-observation-report-production --runtime-evidence /tmp/crown-o07-cursor-observation-production/compile-evidence.json
```

Strict C++23 conversion warnings and `-Werror` apply throughout. Testing builds
use `CROWN_RUNTIME_TESTING` consistently; production does not. The consumer
closure comprises the new exporter, prior run-context exporter, and all three
EXPLAIN/report/CLI units. All commands write to `/tmp`, without native CMake or
binary execution. Compiler success is not a test pass.

## Mandatory independent fixtures before integration

- Independently hand-trace unary, empty, constant true/false, nullary and SQL
  Boolean cursors; projected many-witness/single-output and disconnected/three-
  and eight-child products. Check rows, no duplicates, exact mandatory counts,
  per-call/max work and each optional phase/count against a deterministic clock.
- Read zero rows, partial rows, all rows and exhausted next; cancel before first
  call and after partial consumption; destructor, move construction/assignment,
  self move and cursor outliving facade. Verify lease release and idempotent
  terminal calls, immutable copied summaries, unchanged owner/sequence/binding.
- Startup cap/allocation failure, active-next cap failure, tentative-view abort,
  invalid/closed admission and rejected failed-cursor calls. Preserve mandatory
  charged work, cleanup counts, terminal reason, rollback state and last-summary
  scope; never equate failed construction with a returned exhausted cursor.
- Off/counters/timed/trace (trace timings on/off and unsampled updates): identical
  mandatory work/results/state/lease behavior; zero clocks in off/counters;
  zero versus disabled/unavailable; deterministic zero/backward/overflow clocks;
  phase partition and nested-clock reconciliation without double counting.
- Internal epoch-view cursors during delta and mode bootstrap, successful/failed/
  no-op mode switches, later current-result enumeration, multiple live cursors,
  QuerySession snapshots then stop/drop. Never relabel earlier configurations
  or increment an old last update with later cursor reads.
- Gauges at epoch zero and after insert/delete/no-op/rollback across aliases and
  generalized/projected nodes: independently count bases/S/P/E with scope-aware
  zeros/unavailable values; reject private-state reads; off read remains exact.
- Parse both companion JSON shapes, reconcile all mandatory fields and registry
  units/scopes, exact byte-cap boundaries, null disabled/unavailable metrics and
  explicit unknown memory/durable facts. No exporter is called during mutation.

## Remaining full O07 gaps

Live/interrupted `SearchProgress`, certificate replay progress and owned
`VerifiedInfeasible` EXPLAIN shapes remain separate work; no physical plan or
status flag may impersonate infeasibility proof. Native human/schema/CLI wiring,
independent reconciliation/causal fixtures and the full configuration matrix
remain required. This slice does not add cursor causal sampling, histograms,
per-result timing records, total-result-count collection, annotation metrics,
complete input/build/queue/window/drain registry coverage, allocator-byte
accounting or durable checkpoint/recovery metrics. Existing scoped metrics may
be exposed, but missing measurements must stay explicit. B03 benchmarking, O08
CLI/install and S05/durable gates are not discharged here.
