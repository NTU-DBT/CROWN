# Excluded O07 runtime observation proposal

**O07NS: design/implementation proposal only; O07 remains `not_started`.**
The native P07 inputs remain frozen. This directory contains an unapplied
source overlay and unified patch, not a native integration or acceptance seal.
No CMake configuration, native build target, CTest, benchmark or runtime test
was invoked by this proposal's author. Direct compiler-only checks are listed
below. Root owns any later standalone execution and its independent evidence.

The preceding [design preflight](../o07-design-preflight-2026-11-07.md) describes
full O07. The [baseline probe](../o07-baseline-probe/README.md) observed the
*unmodified* runtime's support40/physical44 and unary21/25 counters and duplicate0.
Those baseline results are not results for this overlay.

## What is implemented in the isolated overlay

- One `ObservationOptions` field on `SupportOptions`, inherited through existing
  physical/delta/session nested options; no competing wrapper configuration.
- Fixed descriptor registry and POD current/last attempt summaries, explicit
  availability, units, ownership scope, inclusiveness and saturation.
- Actual optional hooks in support propagation/journals/reverse-index visits,
  physical source/alias coordination, delta production/preparation/drain/
  commit/rollback/output transfer/callback retry, and session epoch release.
- Real off/counters/timed/trace branches. `PhaseTimer` evaluates no clock
  expression when disabled. Default timed preserves legacy timing availability.
- A trace buffer allocated and sized once at owner admission, retaining only
  numeric IDs/counts. Event writes, summary copies, abort/commit and final output
  cleanup allocate nothing and never format text. Sampling/truncation and
  committed/aborted/unsampled/released status are explicit.
- Session retention of the bounded latest epoch summary before empty output,
  last-row transfer, discard, stop and drop release the relevant owner.

The overlay does not implement EXPLAIN, CLI, JSON/DOT export or every future
metric. It is a substantive first runtime slice. O07's complete gates remain
below; none is marked verified here.

## Files and baseline

`overlay/include/crown/runtime/observation.hpp` and
`overlay/src/runtime/observation.cpp` are new. Eight mirrored native files
modify the support, physical, delta and session headers/implementations.
`o07-runtime-observation.patch` is a unified patch with repository-relative
`a/` / `b/` names; it is **not applied**. The patch changes only those ten source
paths. Native CMake must eventually add `src/runtime/observation.cpp` to
`CROWN_RUNTIME_SOURCES`, which also feeds the runtime-testing library. No native
CMake edit accompanies this preparation.

`baseline-sha256.json` pins 43 original files needed by the source/interface
baseline. `overlay-sha256.json` identifies the ten proposal inputs.
`make_patch.py` refuses to regenerate a patch against a changed native file.
`audit_sources.py` writes a static include-closure audit and records baseline
hashes; do not rerun it to silently bless a different baseline. After any native
change, inspect the differences and explicitly rebase the proposal first.
Historical P05/P06/P07 manifests are untouched.

## Configuration and API

```cpp
SupportOptions support;
support.observation.mode = ObservationMode::trace;
support.observation.trace_capacity = 256;
support.observation.sample_period = 4;
support.observation.sample_offset = 1;
support.observation.trace_timings = false;

PhysicalRuntimeOptions physical;
physical.support = support;
DeltaOptions delta;
delta.physical = physical;
SessionOptions session;
session.delta = delta;
```

Default mode is `timed`. `off` creates no collector/buffer and rejects the
contradictory `capture_transitions=true` legacy full-debug option. Modes and
sampling parameters are validated before a runtime escapes. `counters` collects
optional observations without clocks or trace; `timed` additionally enables
legacy delta phase clocks; `trace` additionally samples whole attempts and
optionally clocks according to `trace_timings` (default true).

`SupportRuntime`, `PhysicalRuntime`, `DeltaRuntime` and `QuerySession` expose:

```cpp
ObservationSnapshot observations() const;
ObservationTrace observation_trace() const;
```

The first returns fixed-size owned metadata. The second explicitly allocates
an owned vector copy of at most the configured trace capacity. It is not called
from any mutation hook. Session methods use the existing creator-thread and
reentrancy guard. Direct runtime methods retain their existing exclusive-caller
contract; they add no thread safety. There is no observer callback in production.

Enabled snapshots carry the actual support owner ID, options, lifetime attempt/
commit/abort counts, optional current and last summaries, and independent trace
attempt/sequence metadata. A summary is one admitted attempt, not a cumulative
query total. `last` remains while `current` is pending and is replaced at the
next close. Late output transfer/callback observations update that same last
summary while its output lease still blocks the next update. No epoch/journal
is retained just to keep these numbers.

Off snapshots have no current/last summaries. Their zero lifetime counters mean
uncollected; do not treat them as measured no activity. Existing mandatory
runtime metrics remain available through their original APIs and still enforce
all budgets. Enabled layer counters are available even when zero; unentered
layers are unavailable; disabled timing fields say disabled. Registry values
must not be summed blindly. The fixed enum `MetricId::count` is a sentinel;
public `summary.metric()` returns unavailable for an out-of-range enum.

`observation_registry()` returns static descriptors. Fields named `work` report
legacy mandatory accounting; new optional reverse visits, callback counts,
mapped/transferred/discarded counts and clock reads are observation-v1 values.
Clock values and collector totals saturate without throwing; saturation is
explicit. Mandatory legacy counters retain their existing overflow errors.

## Work and lifecycle boundaries

Support's original counters, cap checks, enqueue IDs, applied ordinals and
journals are unchanged. Physical work includes the support charges. For the
independent Q(x)=R(x,y),S(y) fixture, the intended overlay reconciliation is
support_work40, physical_work_inclusive44, physical_work_exclusive4, and optional
reverse_index_records_visited1. Reverse visits are measured in the real bucket
loop, not inferred from native_record_visits2. They add no legacy work charge.

The physical observer tracks the exact sum of successfully charged nested support
work and a stage/charge-completed flag. It does not infer inclusion from numeric
counter magnitudes. Before each logical stage the flag becomes incomplete; only
successful stage completion *and* successful coordinator charge restore it. A
failure in either keeps both inclusive/exclusive work unavailable. This remains
true when an unrelated enforced-constraint scan already makes raw physical work
larger than support work. Available exclusive work subtracts the recorded charged
subset, never an independently observed value. An aborted
attempt's counters describe attempted work; they are not committed state changes.
Physical and delta work are separate accounting domains; delta work includes its
own view/cursor operations and excludes the coordinator/support total. Replay
preparation/first/result/termination/finalization fields are subsets, not extra
terms to add to delta work. Prepared spool rows/bytes are historical prepared
accounting, not current remaining memory.

The outermost admitted support/physical/delta scope owns the attempt ticket.
Nested begin calls mark the relevant metric layer available but cannot publish
or abort the outer summary. Physical commit and support commit remain atomic
inside the delta publication barrier. Failure cleanup closes views/cursors and
restores mandatory state in the existing order, then publishes one aborted
summary. Timers finish before the summary is copied. A pending object's setup
allocation failure before its observation ticket is created is not an admitted
attempt and does not fabricate a summary.

Direct and insertion-replay initialization are excluded from update observation:
initialization temporarily moves out the support collector and restores it on
all exits. Its seed operations do not become aborted sequence-zero updates.
Existing `BuildMetrics`/bootstrap metrics remain their own source of accounting.
Mode-change bootstrap similarly has no new claimed observation phase in this
slice. No result production or required drain is skipped by observation off.

Mapped records are counted when `append` receives an already mapped tuple;
retained spool records can be fewer after a quota failure or deliberate drain.
Discard counts cover output-disabled mapped records, explicit retained-output
drain, and final spool release. On an aborted attempt they include unpublished
retained records released by rollback. Existing `DeltaMetrics.discarded_records`
is unchanged; the registry's broader discard field is explicitly observation-v1.
Transfer through `Epoch::next()` means caller ownership, not sink delivery.
Callbacks count codec/sink attempts, successful returns, failures and acknowledged
row removals independently. Codec-success/sink-failure retry can encode twice.
A callback that accepts then throws can have duplicate external effects. Deferred
callback discard is recorded as discard, not a claimed successful row pop.

## Sampled trace contract

An admitted sequence is selected iff `sequence % sample_period == sample_offset`.
Each retry gets a new observation attempt ID. Trace sampling is independent of
clock, tuple bytes, container iteration and query decisions. Lifetime attempt
counter saturation disables further sampling and marks lifetime counts saturated
rather than silently claiming unique new attempt IDs.

Every new attempt replaces the trace buffer's logical prefix, including an
unsampled attempt (`not_sampled`, zero records). A sampled pending attempt becomes
committed or aborted independently of whether its terminal event fit. At capacity
exhaustion the prefix is retained, dropped count increases and `trace_truncated`
is true. Dropped-count overflow sets `trace_dropped_saturated`; it is distinct
from ordinary trace truncation. Capacity zero is valid. A truncated trace is never a complete causal
proof. Trace disposition alone does not imply completeness.

Records contain kind, event/cause ID, node, occurrence, one-based alias route
prefix, before/after count, support role and monotonic local tuple ID where
applicable. The snapshot supplies support owner, attempt and physical sequence.
Support journal event IDs/cause IDs are the source of causal linkage; physical
route context is inherited by nested support records. `child_applied` refers to
the same ID as its earlier `child_enqueued`, which carries the parent cause.
Journal IDs and event IDs are distinct namespaces selected by record kind.
No row values, addresses, strings or pins are retained; a deleted tuple's numeric
ID is diagnostic only, never dereferenced by the exporter.

No-op updates still have an admitted begin/commit trace and zero mandatory work.
On session stop, fixed metadata and available trace remain with the retained
runtime. Drop releases the runtime/buffer, keeps the last POD summary, marks
trace `released`, and reports zero retained trace records. An explicitly copied
`ObservationTrace` remains caller-owned across drop.

## Direct compilation and ABI rule

Appending options changes the public layout of SupportOptions and therefore
PhysicalRuntimeOptions, DeltaOptions, SessionOptions and IO SupportTrace. **Never
mix modified runtime objects with the old native runtime archive.** All eight
original runtime translation units plus the new observation unit must be compiled
with overlay headers first, and with a consistent `CROWN_RUNTIME_TESTING` flag:

```sh
python3 docs/verification/o07-runtime-proposal/build_overlay.py /tmp/crown-o07-runtime-overlay-compile --testing
```

This script directly invokes the compiler and archiver, checks baseline hashes,
and permits outputs only under `/tmp`. It does not configure CMake, invoke a
native target or execute a test. It emits commands/logs/dependency files and
`compile-results.json`. The replacement archive is
`/tmp/crown-o07-runtime-overlay-compile/libcrown_runtime_o07_overlay.a`.

Recompiled unchanged runtime inputs are `src/io/support.cpp`,
`src/io/inspection.cpp`, `src/runtime/replay.cpp` and `src/runtime/window.cpp`.
The modified four runtime units and new observation unit use the overlay copies.
The original IO support JSON codec still exports only its historical options;
it is not an O07 execution descriptor or a round trip for observation options.
That new reporting work is deliberately a remaining gate.

`abi-source-audit.json` checks quoted project include closure for 49 non-runtime
translation units: no changed runtime option header is reachable from current
core/plan/sql/reference implementation units. In particular core
`src/io/batch.cpp -> include/crown/io/batch.hpp -> io/ingest.hpp -> IR` does not
construct/pass a changed options type; window.hpp goes through batch.hpp, while
replay.hpp goes through delta.hpp and is in the rebuilt runtime set. Existing
core/plan/sql/reference archives can be used with this exact pinned baseline.
This is a source dependency audit, not a general ABI guarantee for future edits.
Every probe/test/application itself must also compile against overlay headers.

For zero-clock tests, compile the entire replacement runtime and the probe with
`CROWN_RUNTIME_TESTING`. `detail::set_observation_clock_for_testing` accepts a
nonthrowing uint64-nanosecond clock function; nullptr restores steady_clock.
Installation is an exclusive test operation, not a thread-safe production API.
Off/counters/trace-without-times must never invoke it. Do not instrument planner
budget clocks through this hook; they are a different mandatory subsystem.

## Compiler evidence and remaining acceptance

The initial five changed/new CPPs compiled individually with C++23 and
`-Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Werror`. The complete
nine-unit runtime also compiled together under `CROWN_RUNTIME_TESTING` in `/tmp`.
These are object/interface checks only. There is no author-run overlay execution,
failure sweep, sanitizer result, full matrix or performance result in this packet.
Root's subsequent standalone evidence must identify its exact overlay hash set.

Before native integration/verification, root must execute the independent literal
40/44,21/25,duplicate0 fixtures through every observation mode, comparing raw
outputs/canonical state/mandatory metrics and checking trace IDs/availability.
Mandatory independent tests also include tight resource boundaries (including
constraint-heavy failed nested charges with raw coordinator work above support), initialized
state, wrong input, sampled/unsampled/truncated/zero-capacity attempts, persistent
allocation failure and same-owner retry, final summaries after abort and output
release, callback failures/deferred discard, and runtime/facade lifetimes. The
new observation hooks must be proven allocation-free during publication/rollback
and must never consume mandatory work budgets. Native failure sweeps may have
new admission allocation positions; rerun them instead of reusing old counts.

Full O07 additionally still needs authority-aware human/JSON EXPLAIN, readable
JSON/DOT tree export, versioned schemas and independent mutation checking,
resolved execution/benchmark mode identity and mode-change segments, fuller
cursor startup/advance/end/cleanup timing, queue/window/input/inspection/build
metrics and explicit unknown/unimplemented fields. Drain/final-owner timing
needs its own declared inclusive versus disjoint phase treatment; existing delta
phase clocks do not claim that every teardown cost is now timed. A historical
prepared spool byte count is not peak allocator memory.

Native strings remain typed arbitrary bytes throughout hooks/admission/unwind;
there is no JSON serialization or UTF-8 validation added to those paths. Future
text exporters must keep their codec boundary separate and must not narrow native
binding semantics. C01 statistics/ranking authority, S05 full live/reserved byte
accounting, O04/O05 checkpoint/recovery, O06 durable delivery and B03 benchmark
claims remain open. No source seal, card status, historical handoff or release
gate is changed by this proposal.
