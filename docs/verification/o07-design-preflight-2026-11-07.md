# O07 design preflight — 2026-11-07

**Design only. O07 remains `not_started` (O07NS). No configure, build, CTest,
benchmark, or runtime execution was performed for this packet.** This is an
excluded preparation document, not implementation or acceptance evidence.
P07's active five-configuration matrix has frozen native/execution inputs;
this packet changes none of those inputs, ordinary documentation, task ledger,
handoff, or historical seals. Read the current handoff before integration;
P07's eventual status must come from its own terminal matrix/audit evidence.

O07 depends on verified P06/P08/R04/D01. Its independent branch can proceed
once the current freeze ends; S04 remains behind A02's license disposition.
O07 enables C01, which with P07 enables C02. This does not close S05,
O04/O05/O06, B03, or the 78-card goal.

## Acceptance interpretation

[Refactor.md](../../Refactor.md), O07 (line 1265), §§8.5 and 9 requires one
coherent observability implementation: human/JSON EXPLAIN, tree export,
metrics registry and sampled causal trace, an identifiable execution mode,
hand-reconciled counters, and instrumentation-off result equivalence.
A serializer over existing status structs alone is insufficient: the current
runtime always measures some wall times, the session loses epoch diagnostics
when releasing output, reverse-index visits are conflated with native visits,
and there is no bounded sampled trace or uniform metric scope/availability.

Separate structural validity, original-query minimum-height authority,
candidate-family exhaustion, cost ranking, and runtime guarantees. An
independently proved minimum height is not minimum maintenance cost. Explicitly
report `cost_selection: not_implemented`, `statistics: unavailable` until C01/C02;
never convert candidate count or a cache hit into cost-search coverage.

## Existing source map and gaps

All paths below are existing unless labeled proposed. Line references are
navigation anchors from the frozen source, not immutable future numbering.

| Layer | Existing seams | What O07 must add/preserve |
|---|---|---|
| Height authority | `include/crown/planner/search.hpp`: `SearchBinding`, `ValidatedIncumbent`, `VerifiedOptimum`, `VerifiedInfeasible`, `CheckedCertificate`; `SearchProgress`/`ReplayProgress`; `src/io/search.cpp` | Immutable authority handles; progress aggregates are diagnostic only. Separate producer/replay completion, bounds/evidence, stop/limits and active time. Exporting must not advance/replay a search. |
| Candidate provenance | `include/crown/planner/candidates.hpp`; `src/io/candidates.cpp:65–142`; `src/planner/candidates.cpp:45–222,583–601,744` | Original proof is retained separately from an alternative upper. Exhaustion covers admitted seeds plus the named normal-form family only; saved prefix is not continuation state. Keep exact catalog/query/context binding, arithmetic/update profile, provenance and cache scope. P07 is still pending its independent matrix while this is written. |
| Physical plan | `include/crown/ir/physical.hpp`; `include/crown/planner/lower.hpp`; `src/planner/lower.cpp:240–330`; `src/io/physical.cpp` | Already has source/core catalogs, normalized program, original head, validated tree, separators, C*, native height in validation, physical layouts/indexes, enumeration program, identity/policy. Supplied-tree lowering provides an upper bound only. `GuaranteeProfile` is compile-time metadata and its historical runtime-not-implemented strings must not masquerade as an attached running engine's current profile. |
| Support/journal | `include/crown/runtime/support.hpp:27–111`; `src/runtime/support.cpp:161–362` | Typed support work, membership transitions, retained before/after records, causal event IDs already exist. `capture_transitions` captures complete allocating event/tuple vectors; it is neither sampling nor a bounded best-effort observer. `native_record_visits` includes direct native changes and reverse-bucket visits. Add a separately named reverse-index-record visit observation at the actual bucket loop (`:337`), without silently changing historical work charges. |
| Physical coordinator | `include/crown/runtime/physical.hpp`; `src/runtime/physical.cpp:108–199,240` | Source changes, alias visits/filtering, derivations/native crossings and constraint scans are measured. Coordinator work includes child support work; do not add both to produce a claimed total. Route prefix includes filtered/count-only aliases. Publication includes all aliases atomically. |
| Cursor/view | `include/crown/runtime/support.hpp:160–181`; `src/runtime/support.cpp:683–704,868`; `EpochViewMetrics` | Startup/results/termination/failed/last, max-result work, cleanup frames and before-view restoration already exist. `last` is a view, not a summable extra phase. Add optional startup/advance/end/cleanup time observations, including empty cursors and explicit failed/cancelled terminal status. Mandatory lease release still occurs with observation off. |
| Delta | `include/crown/runtime/delta.hpp`; `src/runtime/delta.cpp:28–42,136–156,630–690,915–1119` | Extensive candidate/live/replay/finalization/spool work; resolved profile/completion; distinct propagation/internal/mapping/codec/sink clocks. `PhaseTimer` currently samples `steady_clock` unconditionally. Private accepted core rows, SQL mapped rows, retained spool records and delivered rows differ. Existing `spool_rows/bytes/capacity` are prepared accounting, not current remaining bytes. |
| Session/input/window | `include/crown/runtime/session.hpp`; `src/runtime/session.cpp:126–161,295–375`; `include/crown/io/{ingest,batch}.hpp`; `include/crown/runtime/window.hpp` | Session status shows pending work/remaining/queue/progress, but not retained per-epoch metrics/timings/profile. `publish`/`next_output` release journals and inactive output. Preserve a bounded POD diagnostic summary before release; avoid keeping entire Epoch solely for reporting. Command sequence, physical sequence, expansion steps and source position are distinct. Queue full is not EOF. |
| Build/inspection/state | `include/crown/runtime/{initialization,inspection}.hpp`; `src/io/inspection.cpp`; `include/crown/storage/arena.hpp` | Build metrics separate direct/replay/bootstrap. Inspection has actual bounded state statistics but scans and allocates; never invoke it invisibly for every update or call it a cheap gauge. Arena statistics count slots/records/pins, not allocator bytes. Existing diagnostic text writer deliberately enforces UTF-8. |
| CLI/build | `apps/crown/main.cpp:196–245`; `CMakeLists.txt:31–55,64–65,141–144,328–330` | Lower/validate/support-trace exist; no integrated EXPLAIN or benchmark report. Keep all lower/read independent validation. Runtime source list also feeds instrumented testing library; wire new runtime files through that list. O08's broad command/install workflow and B03's controlled benchmark runner remain separate. |

## Proposed minimal coherent API and implementation

These are implementation decisions to review after the freeze, not new public
API promises or files delivered by this packet.

1. **Owned plan explanation.** Add `include/crown/observability/explain.hpp`
   and `src/observability/explain.cpp` to `crown_plan`, plus
   `include/crown/io/explain.hpp` / `src/io/explain.cpp`. An immutable
   `PlanExplanation::create(PhysicalPlan, ExplainEvidence, ExplainLimits)`
   owns the plan and optional existing typed proof/candidate handles.
   `ExplainEvidence` uses a closed variant of no proof, validated incumbent,
   verified optimum or checked candidate, with a separately owned search or
   candidate progress snapshot. No caller-supplied `minimum=true`/height
   aggregate is authority. An infeasible query has a distinct explanation
   factory from `VerifiedInfeasible`; it cannot carry an executable plan.
   Limits cover nodes, records and encoded bytes; report construction is
   explicit allocating admission work outside mutation/publication.
2. **Binding fence.** Compare all original Catalog/Query fields with native
   typed equality before associating evidence with a plan's *core* catalog/query;
   preserve original normalized/source metadata independently. Use a small
   explicit nonserializing binding comparison helper, with field completeness
   tests against P07's private native v2 token, rather than exposing that cache
   token or dumping JSON for equality. Require proof's admitted query, candidate
   context and tree-to-selected-plan relationship, not just equal height/hash.
   A verified optimum can certify an alternative selected P02-validated tree
   only when exact binding and equal height hold. The certificate keeps its
   original witness. A mismatch rejects explanation creation; it never relowers
   or changes the running query. Report digests are navigation IDs, not authority.
3. **Fixed metric catalog and runtime observation.** Add
   `include/crown/runtime/observation.hpp` / `src/runtime/observation.cpp`
   to `CROWN_RUNTIME_SOURCES`. Define static `MetricDescriptor` entries with
   stable ID/name, accounting version, unit, counter/gauge/high-water/timing
   kind, scope, source, inclusiveness and availability. Avoid dynamic name maps,
   unbounded tuple/key labels or user callbacks in the update loop. A
   query-owned `ObservationState` has fixed-size aggregates and a preallocated
   bounded trace buffer, configured at query admission by `ObservationOptions`.
   Owners/cursors share this state through lifetime-safe internal ownership;
   no observer borrows a session that may be destroyed first. Direct support,
   physical, delta and session construction all accept/propagate the same
   configuration. Nested layers share one state; parent wrapping must not
   register duplicate events. Session configuration rejects contradictory
   nested modes rather than silently enabling a lower observer.
4. **Concrete runtime changes, not just registry export.** Wire hooks into
   support start/enqueue/apply/note/presence, physical route/source publication,
   cursor construction/next/close, delta append/prepare/commit/rollback/drain/
   delivery, and session acknowledge/queue/stop/drop. Add optional reverse-index
   visit counts, output lifecycle counts and phase clocks where the current
   structs do not distinguish them. Use existing completed per-layer accounting
   snapshots for legacy operation metrics; do not reinstrument every old
   increment or charge registry overhead against historical work ceilings.
   Record initialization and bootstrap separately from updates. A cheap
   observation snapshot returns fixed fields and availability; explicit
   `inspect_invariants` remains a separately labeled diagnostic operation.
5. **Persistent summary without retained runtime rows.** Add guarded
   `QuerySession::observations()` and direct runtime/cursor equivalents returning
   an owned fixed-size `ObservationSnapshot` (committed totals, current attempt,
   last closed attempt, current status/phase, generation and resolved profile).
   No implicit drain/commit/inspection. Copy authoritative summary before
   `publish` discards empty epoch output and before `next_output` releases the
   final row. Copy/merge must be allocation-free after commit. Output lifecycle
   updates continue through the retained ObservationState even when Epoch has
   released its runtime owner. A fixed scalar terminal summary survives stop;
   drop releases runtime/trace payload while retaining only documented metadata.
6. **Report/graph adapters.** Add `include/crown/io/observation.hpp` and
   `src/io/observation.cpp` to the runtime source list; versioned proposed
   `explain-v1`, `metrics-report-v1`, `causal-trace-v1` schemas. Human and JSON
   render from the same owned explanation/report. DOT uses numeric internal
   node IDs, escaped labels, native/generalized styling, C* marker, separators,
   height and source occurrence IDs. Output DOT directly with no shell command
   or Graphviz runtime dependency. DOT satisfies the tree-export seam; SVG is
   a later optional renderer, not silently promised. JSON must include the
   complete graph structure so visualization is never semantic input.
7. **Narrow CLI surface.** Add `crown explain PLAN.json [--format text|json|dot]`
   using `read_physical`, and an explicit optional checked certificate input
   whose parsing/replay is charged and reported *before* explanation. Without
   it the label remains checked upper only. Runtime JSON reports are available
   through the library and a small diagnostic trace/run adapter reusing input
   and session APIs, with explicit options/report mode. Do not invent an O08
   SQL-to-checkpoint CLI or declare B03's benchmark runner done. The same
   `ExecutionDescriptor` must be used by every existing runtime comparison
   test and future benchmark reporter so modes cannot be inferred from filenames.

## Instrumentation-off contract and accounting invariants

Use `ObservationMode::{off,counters,timed,trace}` with trace explicitly also
selecting whether clocks are enabled. The effective configuration is immutable
within an attempt; changes, if offered, require a writer-ready barrier and
increment `observation_generation`. Default compatibility can retain existing
DeltaTimings behavior, but the explicit off option must traverse a real code
branch that avoids all new collector updates, trace writes/allocations and
clock reads. Change `PhaseTimer` to conditionally initialize/read its clock;
an unused clock result computed before checking enabled is not off behavior.

**Mandatory deterministic accounting is not optional telemetry.** Preserve
all existing cap checks and work counters: support IDs/applied ordinals and
queue checks use metrics (`support.cpp:240–362`); physical work incorporates
support work (`physical.cpp:176`); delta phase accounting derives differences;
cursor budgets use total work (`support.cpp:683`). Legacy public accounting
structs retain their meaning in off mode. Off reports explicitly distinguish
`mandatory_accounting_v1: active` from `optional_observation: disabled`.
This is a transparent contract, not a claim that all integer increments vanish.
Optional metrics/time/trace fields are unavailable with reason `disabled`,
not numeric zero. Structural proof/search budget clocks stay active when
required to enforce a requested time limit; report them as mandatory budget
measurement, not disabled runtime telemetry.

The new observer must not influence ordering, canonical keys, hashes, plan
choice, sampling of query data, result values or visibility, limits, rollback,
required drain, lease closure or sink acknowledgement. Neither mandatory
journals nor undo can be removed with observation off. Legacy
`capture_transitions` remains an explicit full-debug facility with its existing
allocating failure behavior; reject off + capture as conflicting configuration
at admission, or expose it as independently enabled and never label that
combination fully off. Do not implement sampled tracing by switching on
unbounded legacy capture for every update.

New aggregation uses nonthrowing saturation with per-field `saturated=true`;
an exact reconciled total is unavailable once saturated. It must not create a
new runtime failure. Mandatory counters keep their checked-error semantics.
Attempt work (including failed attempts) and committed semantic changes are
different scopes; rollback preserves the previous committed aggregate/state
but retains a bounded failed-attempt diagnostic. No negative correction by
subtracting unsigned cumulative counters. Trace allocation fails only during
explicit creation/configuration before engine ownership starts; collection
itself uses fixed capacity. Report encoding/inspection allocation failure
fails that read only; no observer failure may occur after the commit barrier.

## Report identity and phase model

Every run report needs a versioned **resolved**, not merely requested,
ExecutionDescriptor. Include query/source/core identity and selected physical
plan, exact arithmetic/set semantics, backend, build method, compile-only or
initialized/live state, physical input format/adapter, result view (`core` or
`sql`), delta versus maintenance, requested and resolved completion strategy,
live maintenance (`on_output`, `incremental`, `eager`), propagation FIFO/LIFO,
retention/drain/consume policy, current-result enumeration, codec and sink
participation, observation mode/sampling and all finite resource limits.
Include command versus physical event semantics, window FIFO/late policy when
present, and acknowledged source/epoch positions. IDs/positions are process
observations, not durable delivery identities. Separate an initial descriptor
from explicit mode-change/bootstrap segments, so an aggregate over toggles
cannot be mislabeled as a single strategy. Unknown caller-owned sink/encoding
work must read `external_unmeasured`, not zero.

| Phase/count | Required meaning |
|---|---|
| Compile / proof / candidate enumeration | Separate costs and coverage; do not amortize them into maintenance without an explicit policy. |
| Input decoding / queue admission | Decoded records may be unacknowledged; accepted transport batch is not a committed atomic database batch. |
| Initialization / live bootstrap | Direct, insertion replay and mode-switch rebuild are distinct; no hidden setup. |
| Support propagation | Physical source/alias/derivation and support events; coordinator total includes support work. |
| Delta preparation | Changed-key discovery, endpoint views, productive queues/live-image work; can be data dependent before first producer row. |
| Core result production | Accepted/rejected candidates and bounded producer transitions per declared policy; private rows are not public output. |
| SQL mapping / spool retention | SQL EXISTS replacements may be two rows outside core stage ranges. One core row is not necessarily one mapped or retained row. |
| Required drain / finalization | Output-disabled drain still completes rows/aliases and live work; preparation/finalization remain charged. Drain wall time is an inclusive span, never added to the child phase sum. |
| Commit / rollback / cleanup | Commit is the atomic visibility barrier. Failure/cancellation closes cursors before undo. Unread output and last-owner teardown are explicit cleanup; precharged bounds are not measured CPU counts. |
| Current-result cursors | Startup, successful next, exhausted next, failed calls and cleanup separately; empty/nullary/Boolean cases still have distinct terminal behavior. |
| Encoding | Codec invocations/bytes/success/failure and optional duration, before sink callback. Retrying after sink failure can re-encode. |
| Sink / caller transfer | `Epoch::next` transfers ownership, not external delivery. Count callback attempts, callback returns/successes, failed callbacks, acknowledged removals and discards separately. A sink may accept then throw; retry can duplicate effects. |
| Pause / backpressure | User pause not active CPU phase time; queue occupancy and full admission are available, durable backpressure is not implemented. Sink wait field includes callback CPU and wait as today; no claim to isolate sleeping. |
| Checkpoint / recovery | Availability `not_implemented` for bytes/time/replay-length metrics until O04/O05; zero would falsely imply an implemented operation measured empty. |

Existing propagation/internal/mapping durations are disjoint by their nesting
rules; preserve compatibility when exposing more subphases. Add a dedicated
phase enum and explicit parent/child relationships to descriptors. A phase
sum must include no parent twice. Timing tests use an injected deterministic
clock at the observer seam, not strict real-nanosecond values. Future B03 must
record environment/repetitions/warmup/correctness and actual output policy;
O07 creates the report contract, not a performance conclusion.

## Sampled causal trace

Select whole physical attempts by a deterministic documented function, e.g.
`sequence % period == offset`, with period > 0 and offset < period. Record
sampling version, period/offset, attempt ordinal, physical sequence and window
command/expansion mapping. Retries share the physical sequence but have distinct
attempt IDs. Do not sample on clock time, pointer address, tuple hash or container
iteration order. Trace capture must not consume planner randomness or work.

Use preallocated fixed-width records for event type, phase, node/occurrence,
route prefix, journal/event ordinal, cause ID, before/after membership/counts,
operation, result ordinal and terminal outcome. Native root cause, child
propagation, journal changes, alias prefix, accepted-result production,
preparation, commit/rollback, output discard/delivery attempts are connected.
Support IDs are already unique within the support epoch; include attempt/owner
scope so old IDs cannot be mistaken for current ones. Existing journal cause
IDs are the ground truth; do not infer causes from coincident timestamps.
Reverse visits are a new event/count at the actual loop, not the combined
native visit counter renamed. Raw TupleHandle values are diagnostic identity
only and must never be dereferenced by a later exporter.

Retain one bounded sampled-attempt buffer plus its fixed terminal summary;
copy/export is explicit, owned and read-only. Preallocate at admission. On
capacity exhaustion retain a prefix, count dropped records and mark
`complete=false`, `truncated=true`; later records may refer to omitted causes,
so exporters report missing-parent/truncated and never claim a complete causal
proof. An observed but unsampled attempt is `not_sampled`, not an empty complete
trace. Never retain journal pins, row payloads or failed owner's pointers solely
for the trace. Optional keys require a separate bounded owned payload arena and
explicit byte policy; the minimal implementation omits row values and uses
stable local IDs plus optional explicit inspection outside update work.
Export cannot change whether an epoch commits. A rollback trace is marked
aborted; it is not counted as committed support/output history.

## Independent hand-traced acceptance fixture

This is a **paper-derived expected ledger**, not an observed run. Keep a literal
fixture and expected table independent of the implementation and registry
serializer. The later reviewer must reconcile exact operation IDs and source
increments, not generate expectations by copying the observed report.

Use `Q(x) = R(x,y), S(y)`, native R root with native S child, exact integer values,
FIFO support queue, no source constraints. C* contains only R because the edge
separator y is hidden (`verify.cpp:330–350`). R parent key is empty, its visible
key is x; S parent key is y and it has no E relation. Initialize `R={(7,9)}`,
`S={}` and begin measurement after initialization. R has one unsatisfied record
and no survivors; output is empty. Insert physical S(9):

1. One source row, one alias, one derivation 0→1 and one native crossing.
2. Native support event 1 inserts S record, survivor and P(9), producing event
   2 with cause 1. S's leaf has no child probes.
3. Event 2 visits exactly the R(7,9) reverse-index record. Its flag changes
   false→true, satisfaction 0→1; R survivor, P(()) and E(7) appear. No further
   parent event exists. Every R journal change has cause 2.
4. The atomic result difference is exactly `+(7)`. Before publication the
   caller sees no row; after commit a current-result cursor returns (7) once.

| Support metric | Expected increment | Independent reason |
|---|---:|---|
| events_enqueued / events_applied | 2 / 2 | Native root cause and one child event |
| queue_peak | 1 | One queued child event |
| native_record_visits | 2 | Direct S native visit plus one R reverse visit |
| new reverse_index_records_visited | 1 | Only R bucket visit; an additional optional observation |
| child_key_probes / child_key_events | 0 / 1 | S is leaf; one propagated P crossing |
| survivor / parent / visible key transitions | 2 / 2 / 1 | S and R survivors/P; only R has E |
| storage_changes | 6 | S record/S/P plus R S/P/E |
| metadata_changes | 5 | S record/P; R record/P/E |
| saved_child_flags | 1 | Existing R metadata saves its one flag |
| journal_records | 7 | S record/S/P plus R record/S/P/E |
| candidates_created / reclaimed | 0 / 0 | No generalized node |
| historical whole-state copy counters | all 0 | Affected-record journal backend |

All charged metric increments above sum to **32**, excluding the new optional
reverse-visit observation. Unnamed deterministic charges contribute **8**:
S survivor + S P count (2), R presence + survivor + P count + E count (4),
and two applied-event checks (2). Thus existing `SupportMetrics.work = 40`.
Physical work adds source/alias/derivation/native-crossing (4), so
`PhysicalMetrics.work = 44`, including that 40, not 84. Constraint counters
remain zero. The source derivation change and support journal must reconcile
with these independent before/after records. Registry totals must not count
optional reverse observation as another charged work operation.

A second minimal sanity fixture is one native unary `U(x)`, head x, initially
empty. Insert U(7): four storage changes, three metadata changes, four journal
records, one native visit, one survivor/P/E crossing each, one enqueue/apply,
no queue/probes/child events. Charged metric increments 17 plus survivor/P/E/
applied-check charges 4 give support work **21**, physical work **25**. A
physical duplicate insert commits the next accepted sequence with no source,
derivation or support change, no delta, and zero physical/support work under
this no-constraint fixture. Erase U(7) restores empty membership.

For integrated delta acceptance, keep the support/physical counts above but
derive an additional literal per-operation ledger for the chosen resolved
ordered-replay policy before executing it: endpoint/preparation, accepted
candidate, mapping/spool, finalization, commit, one successful transfer and
terminal cleanup. Check the phase partitions used by existing D05 fixtures;
never assert delta total equals 44 because it includes a different accounting
scope. Independently derive D01 startup/one successful next/exhausted next
counts for the selected compiled enumeration; `last` duplicates a phase sample,
not additional work. Produce a trace-to-ledger explanation for every nonzero
field and every omitted/unavailable field. These additional ledgers remain a
mandatory implementation acceptance gate, not something this design packet
claims to have executed or proved numerically.

## Mandatory acceptance matrix after implementation

- **Authority/report fixtures:** unfinished strict search, validated best-found
  upper, verified minimum, infeasible query, interrupted independent replay,
  exact seed and alternate candidate, exhausted and truncated family, cache hit
  with a new proof owner. Reject changed catalog version/constraints/head order/
  parameters/arithmetic/update context and unproved mutable flag injection.
  Include P05's distinct `N(),R(x,y),S(x) -> y` alternatives: original certificate
  witness remains untouched even when a different validated height-two tree
  is selected. Generalized height-one examples cannot be called ordinary-tree
  complete. Human/JSON must agree on the height/cost distinction.
- **Tree fixtures:** native/generalized, empty/nullary true/false, projection,
  repeated/constant SQL outputs, self-join aliases, disconnected products,
  three/eight-child plans. Compare exported graph IDs/edges/separators/C* to
  independently inspected source trees, not to another invocation of exporter.
  DOT labels with quotes/backslashes/newlines cannot create extra graph nodes.
- **Counter/trace fixtures:** literal hand ledger above; projection collision
  where P/E support changes without zero crossing; generalized candidate
  creation/reclamation; multi-alias loop edge; FIFO and LIFO cause order; no-op;
  empty output; parent bucket with two records. Trace on selected and unselected
  sequences, retries, period boundaries, capacity 0/1/exact/full, dropped-parent
  markers, overflow/saturation and owner destruction. Trace completeness is not
  a proof of query correctness.
- **Off equivalence:** run identical initial state and ordered inputs through
  off/counters/timed/trace, all implemented delta completion/live-maintenance
  modes and core/SQL/current-result paths. Compare raw signed rows (including
  duplicates/order where contract promises it), snapshots, canonical state,
  accepted positions, stage/sequence barriers and mandatory work-limit errors.
  Include tight limits at the 40/44 fixture boundaries. Inject a counting clock
  and observer allocation probe to prove *zero optional* clock calls/trace
  allocation/collector work in off mode, not merely missing fields. Do not
  assert wall-clock speedup. Same external callback script must make identical
  acknowledgement/retry decisions across observation settings.
- **Lifecycle/mode identity:** pause/resume, partially retained then drained,
  prepared commit, abort before commit, stop/drop, unread output destructor,
  standalone epoch/cursor outliving facade, mode switch/bootstrap, initialization
  direct/replay, typed full queue/open-empty/EOF, window metadata-only steps and
  expansion. Deliberately toggle output and codec/sink participation and require
  a changed descriptor. Production, serialization and external transfer counts
  cannot all be one `rows` field. Callback throw before success retains the row;
  encode-success/sink-failure then retry records two encode attempts, two sink
  attempts, one acknowledged row. External side effects are not asserted once.
- **Failure isolation:** allocation sweeps at report admission/encoding/trace
  setup; persistent OOM through rollback/commit/output cleanup; insufficient
  report byte limit; disabled/overflow metrics; reentrant/wrong-thread reporting;
  moved owners; stale snapshots. Query state/previous epoch remains valid and
  report creation cannot change original bindings or proof handles. Newly
  instrumented cleanup must still allocate nothing. Borrowed callback lifetimes
  and deferred discard behavior remain as D06.
- **Independent schemas:** JSON validation plus targeted mutations rejecting
  missing mode identity, unknown enum/version, contradictory height evidence,
  fake family/global cost completeness, unavailable value represented as known,
  double-counted phase relationships, missing truncation and scope labels.
  Use a separate Python checker/literal golden records, not a production writer
  parsed back by its own reader. Static fixture set must cover every metric ID,
  units and availability. Keep report comparison independent of nanosecond values.
- **Integration evidence:** focused tests first, then root-owned five-configuration
  matrix and clean-source audit at the established workflow. Independent source/
  proof review must sign off on accounting noninterference and authority fences.
  Do not mutate execution inputs during a new matrix or reseal historical inputs.

Proposed new tests: `tests/unit/explain_test.cpp`, `observation_test.cpp`,
`observation_exception_test.cpp`, `observation_report_test.cpp`, with literal
fixtures under `tests/observability/`; `tools/verify_observation_reports.py` and
`tests/integration/explain.py`. Add through existing CMake test/library patterns,
including `crown_runtime_testing` only where a test probe is genuinely needed.
Reuse the independent A04 evaluator and existing delta/cursor/lifecycle/failure
fixtures; do not introduce a second production executor or duplicate oracle.

## Byte boundaries, text encoding, and deferred gates

Native strings remain arbitrary bytes. P07 specifically removed JSON dumping
from admission to preserve this fact (`src/planner/candidates.cpp:45–222`).
Explanation/trace collection must never round-trip native strings through JSON,
normalize invalid UTF-8, or replace bytes to establish binding equality.
Current text writers such as `src/io/inspection.cpp:28` reject invalid UTF-8;
keep that codec boundary explicit. Minimal O07 JSON text export may return a
specific text-encoding error without affecting the native explanation/query;
permit bounded escaped-byte display in human/DOT output. If lossless JSON
bytes are added later, use a versioned tagged hex/base64 representation and
independent tests, not lossy substitution in existing certificate schemas.
Test embedded NUL, high bytes, invalid UTF-8 and distinct decimal/string/date
variants. Availability of native candidate handles does not imply every
existing text artifact accepts their bytes.

Resource descriptors must state concrete accounted scope and exclusions:

| Component | Known accounting | Excluded/unavailable |
|---|---|---|
| Arena/source/support | live/retained/free/exhausted records, slots, pins, index memberships | Allocator live/reserved bytes; scalar widths, arena high-water metadata, tree/index node overhead |
| Delta spool | allocated spool nodes, row Value capacity, string capacity+1, 64-byte decimal coefficient allowance; row quota | Allocator metadata, compiled descriptors, caller-owned rows, retained journals/pins; prepared gauges are not remaining bytes |
| Session snapshot | Tuple vector capacity, Value capacities, strings+1 and decimal allowance | Peak simultaneous old/new vector allocations, one produced row, progress-map/layout/query metadata, allocator headers, caller-retained snapshots |
| Transport queue/batch | retained list nodes/Value slots/string capacities/decimal allowance | Constructor input, transient allocations, allocator overhead; queued head remains counted through acknowledgement |
| Window | declared retained payload/index/active-watermark accounting | Tree links/allocator headers/transient prepared copies; operational label FIFO is not a proved physical lifetime pattern |
| Planner candidates | cumulative logical records/cells and bounded retained candidates | Binding admission/P02 scratch/capacity/scalar widths/retained historical handles; not allocator bytes |
| New observation | fixed summary cells + preallocated trace record capacity; separately known buffer bytes | Shared ownership overhead, allocator headers, explicit export scratch/results; not a per-query peak memory cap |
| Initialization/inspection/rebuild | explicit work and logical state records | Scratch, old/new runtime overlap, retained history and arbitrary payload bytes |

Expose unavailable total live/reserved allocator bytes as unknown with S05
pending; do not multiply records by `sizeof` and call it measured memory.
Observed logical state can be sampled via explicit bounded inspection tagged
with sequence/completeness/work. An incomplete inspection is not a current
exact gauge and must not be reused as cost statistics. C01 still owes bounded
cardinality/NDV/degree/heavy-key/rate collection, sampling cost and reset/staleness
policy; C02 still owes reproducible scoring inputs and ranking. O07 should
reserve a versioned attachment seam, not fabricate estimates or estimates of
unknown memory. Annotation changes are unavailable under Boolean exact-set
execution, not a synonym for support-count changes.

Checkpoint bytes/time, recovery replay length, durable output identity,
exactly-once sinks, spill, full S05 quotas and B03 performance conclusions remain
open. O07 can expose their `not_implemented` status and current in-process
codec/sink callbacks; it cannot strengthen their guarantees.

## Recommended first implementation slice and exit

After P07's freeze is released, implement the observation mode/state/registry
and conditional clocks together with the unary and two-node literal ledgers,
nonallocating commit summary retention and off-equivalence checks. This is a
small but substantive vertical slice proving the runtime seam before report
polish. Then add bounded causal records and execution descriptor; finally
owned authority-aware EXPLAIN + human/JSON/DOT and CLI/report checks. A slice
may be tested independently, but O07 stays in progress until all four artifacts
and the complete acceptance matrix pass. Preparation here changes no status.

No source changes or runtime checks accompany this packet. Its numbers are
static ledger expectations to challenge in implementation, not a matrix result,
benchmark, source seal, or claim of O07 verification.

## Subsequent excluded baseline observation

Root later ran the separate [public-API hand-trace probe](o07-baseline-probe/README.md)
against already built Release archives. Q's literal support/physical work
40/44 and unary work 21/25 match in the observed baseline; duplicate work is
zero and exact journal/result/reference checks pass. This observation does
not supply the proposed new reverse-visit metric, registry, disabled-telemetry,
sampled-trace, EXPLAIN or full O07 acceptance. O07 remains not started and
the P07 source freeze is unchanged.
