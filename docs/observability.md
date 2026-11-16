# Native observation and EXPLAIN

EXPLAIN schema v2 preserves historical `open_gates`,
`durable_delivery:not_implemented` and output-accounting prose for compatibility. They describe
that frozen report contract, not current project completion or actual sink
state. Use the [ledger](task_ledger.md) and session delivery/recovery APIs for
current facts. The [review guide](code_review.md) records this remaining
versioning issue; the original wire fixtures remain unchanged.
The legacy output prose excludes allocator metadata, while the actual spool
quota includes account framing. Use the [current spool contract](delta_runtime.md)
for requested-byte accounting; a wording correction must not silently change
frozen v2 report bytes.

`crown explain` creates an owning diagnostic view of a validated physical plan,
a runtime or session, or a real exact-search/replay owner. Capturing a report
does not advance an update, cursor, search, or certificate replay. Export is a
separate operation.

The separate library-only `StatisticsExplanation` API adds explicit C01 state
and workload facts in a closed v3 artifact; see [runtime statistics](statistics.md).
The CLI and its existing v2 options are unchanged. C01 collection is independently
off by default, while O07 defaults to timed observation. O07 `off` alone does not
disable an explicitly enabled C01 collector.

## Commands

```text
crown explain {physical|runtime|session} PLAN.json [OPTIONS]
crown explain {query|progress} DOCUMENT.json [--work N] [--height-policy strict|best-found]
crown explain replay DOCUMENT.json --certificate FILE [--work N]
```

- `physical` validates and reports an imported physical plan; optional
  `--certificate FILE [--proof-work N]` explicitly replays a certificate before
  report capture. `--proof-work` without a certificate is an error.
- `runtime` constructs a fresh runtime over an empty database and captures it.
- `session` constructs an owned-stream session. Its event count defaults to
  zero; `--input`, `--input-format jsonl|binary`, `--events`, `--steps`,
  `--consume discard|transfer|retain`, and
  `--lifecycle preserve|stop|drop` select explicit session work and lifecycle.
- `query` and `progress` create an exact-search owner. `--work N` performs one
  explicit search quantum; it defaults to zero. `--height-policy` selects the
  search policy. `replay` requires a certificate and optionally advances that
  replay by one explicit work quantum.

All forms accept `--format text|json|dot|tree-json` and `--max-bytes N`. Runtime
and session forms additionally accept `--mode maintenance|delta`,
`--observe off|counters|timed|trace`, the live/completion/view controls, and
their documented work and spool limits. See `crown explain --help` for the
complete option list.

For example, lower an existing query/tree pair and report the resulting plan:

```sh
crown lower-plan QUERY.json TREE.json > /tmp/plan.json
crown explain physical /tmp/plan.json --format text
```

Inspect actual search progress after one explicit quantum:

```sh
crown explain progress QUERY.json --work 100 --height-policy best-found --format json
```

Capture a newly constructed empty runtime with optional observation disabled:

```sh
crown explain runtime /tmp/plan.json --observe off --format json
```

## Observation modes and metric values

`ObservationOptions.mode` defaults to `timed`, preserving legacy delta phase
clocks. The CLI uses that default unless `--observe` is supplied.

| Mode | Optional observations |
| --- | --- |
| `off` | Disabled. Mandatory work limits and accounting still apply. |
| `counters` | Counters and high-water values; no optional clock reads or causal trace. |
| `timed` | Counters plus timing observations, including the legacy delta clocks. |
| `trace` | A bounded, sampled numeric causal trace; counters are collected and timings are collected when `trace_timings` is enabled. |

The CLI selects a mode but does not expose trace sampling controls. Library
defaults are capacity 256, `sample_period = 1`, `sample_offset = 0`, and
`trace_timings = true`. Library callers can set the sample period/offset,
capacity, and trace timing option through `ObservationOptions`. A sequence is
selected when `sequence % sample_period == sample_offset`.

Metrics carry an availability state as well as a value. `available` with value
`0` means the measurement was made and its result was zero. `disabled` means
that the selected mode deliberately did not collect that optional metric.
`unavailable` means no valid value is available, for example because a nested
charge was incomplete or a fact does not apply. JSON emits a numeric payload
only for `available`; disabled and unavailable payloads are `null`. Mandatory
accounting remains active in `off`. The separate legacy
`capture_transitions` debug option cannot be combined with explicit
`ObservationMode::off`.

For `Q(x) = R(x,y), S(y)`, use a native R root and native S child. Initialize
R with `(7,9)` and S empty, then insert `S(9)`. This complete update has:

| Counter | Value | Meaning |
| --- | ---: | --- |
| `support.work` | 40 | Support-layer work charged by the operation. |
| `physical.work_inclusive` | 44 | Physical work including the successfully charged support work. |
| `physical.work_exclusive` | 4 | Physical work with support work excluded. |

Thus `44 = 40 + 4`. Do not add the inclusive 44 to the support 40 again. If a
nested charge is incomplete, the inclusive/exclusive observation is unavailable
rather than a fabricated or clamped total.

Cursor clocks can run inside a delta attempt. During that attempt, the global
clock-read count reconciles as `delta.clock_reads + cursor.nested_clock_reads`.
Those two counts cover disjoint calls within the attempt. The nested count is
already a subset of that cursor's `clock_reads`; do not add it again to a
per-cursor total. Later cursor reads after the attempt are reported separately,
and nested timing intervals are not additive to the enclosing delta phase.

Current runtime configuration and a historical attempt's configuration have
different scopes. The report's current configuration describes the owner at
capture. Each outer delta attempt retains the exact immutable configuration
bound when it began; a later mode change does not relabel its `current` or
`last` summary. A lower-layer summary without a delta begin has no delta
configuration binding.

## Reports, ownership, and committed gauges

The C++ API exposes `crown::observability::PlanExplanation::create` for a
compile-only physical report and `PlanExplanation::capture` for
`DeltaRuntime` or `QuerySession` owners. A `PlanExplanation` owns its typed
physical plan and evidence, plus any copied gauges, cursor value, and numeric
trace records; it does not borrow rows or retain the mutable runtime.
Full runtime/session `PlanExplanation::capture` requires C01 collection to be
off. When it is enabled, capture throws `explain_statistics_version` and callers
must select `StatisticsExplanation`; a full v2 report must not silently omit
enabled instrumentation. C01-off v2 bytes and schemas are preserved. Explicit
compile-only structural/tree exports retain their declared structural scope.
`QueryExplanation::capture` accepts an actual `ExactSearch` or
`CertificateReplay` owner and owns that producer's typed progress and evidence.
Session capture uses the plan from the actual owning session, not a
caller-supplied plan joined by a hash. Capture may allocate the report and
explicit gauge/trace copies; that diagnostic cost is outside mutation work
accounting. Retained runtime/session report allocations consume the existing
query memory grant, as described below.

Committed gauges describe stored state at a readable barrier. If a runtime or
session has pending private work, capture still reports its lifecycle and
marks gauges `pending_private_state`; it does not drain or commit the work. A
stopped session retains its runtime, so readable committed gauges can remain
available. Dropping a session releases runtime tables and reports gauges as
`runtime_released`; its immutable plan metadata remains. A report captured
before stop or drop keeps its own copied values.

The latest cursor value is one enabled cursor lifecycle publication, not a
total over cursors or updates. It contains numeric identifiers and bounded
metrics, not tuple payloads. A sampled trace is also diagnostic, not a complete
causal history: it may be `not_sampled`, `aborted`, or truncated by its record
capacity. Trace records contain numeric IDs and enums only; they retain no
tuple values, string pointers, callback, or row pin. The report exposes trace
disposition, retained/dropped counts, and truncation status so a partial trace
is not mistaken for a full history.

## Height, cost, and proof scope

A P08 `constant_false` plan has executable operator height `0`. That says the
chosen physical plan is a constant-false operator; by itself it does not prove
that the original nonempty CQ has structural height zero, an upper bound, or an
optimum. Without original structural evidence, those original-query claims are
null. Genuine original-query proof handles remain separately bound to the
exact typed query. Structural infeasibility is a distinct query/search result
and can be reported without a physical plan.

Plan height and planning cost are separate facts. The legacy v2 report labels
cost selection `not_implemented`, statistics and estimated state as
`unavailable`, and global cost optimality as false. Height or structural
proof evidence does not imply a cost ranking.
The separate v3 statistics report exposes observed local populations while
leaving cost selection, total estimated state bytes and global cost optimality
unavailable. It grants no new structural proof authority and carries no repository
task-acceptance claim; acceptance status belongs in the ledger and evidence.

## Encodings and schemas

The v2 EXPLAIN report and tree schemas are closed: unknown fields are rejected.
The standalone query/search and typed witness schemas remain their own closed
v1 formats. These shapes describe diagnostic artifacts; JSON fields do not
create typed proof authority.

Input artifact reads are capped at 16 MiB. Encoded output is capped at 16 MiB
by default and can be lowered with `--max-bytes N`. The cap counts encoded
bytes and applies to text, JSON, DOT, and tree-JSON output; a nested encoder is
given the remaining budget. Export either returns the complete artifact or
fails without returning partial stdout. The cap does not bound report-copy
allocation, total memory, or CPU work.

UTF-8 is an output encoding constraint for the existing EXPLAIN formats, not a
new native-value admission rule. Their string fields must be valid UTF-8 when emitted; an encoding failure
does not rewrite or mutate the native value or its owner. Native callers may
hold arbitrary byte strings, but a value that cannot be encoded as valid text
cannot be emitted as an EXPLAIN string.
The v3 statistics key encoding instead uses explicit scalar type tags and
hexadecimal string bytes, preserving NUL and arbitrary bytes exactly. Its
independent byte/item caps and unknown-value rules are described in the
[statistics guide](statistics.md).

## Native retained report ownership

Runtime/session captures now use their existing CompiledProgram MemoryAccount for
ModeDescriptor/PlanExplanation/StatisticsExplanation/CombinedCapture object and
shared-control blocks, copied trace records and committed node/base gauge arrays.
SessionStatisticsContext likewise retains native trace/combined children beneath
its funded outer control. CapturedObservationTrace/CapturedTraceRecords and
CapturedStateGauges are the retained read interfaces. Shared report handles copy
without allocating; native trace/gauge value copies use the source query account.
A failed cross-query value assignment preserves the old metadata and arrays.
Reports remain readable after runtime/session destruction and release their
charged storage when the final owner drops them.

The existing ObservationTrace/CommittedStateGauges runtime exports remain ordinary
caller DTOs. Native gauge encoding preserves their exact output shape. Compiler-
only PhysicalPlan reports use an explicit standalone component account, while an
admitted CompiledProgram report uses its original grant. Explicitly supplied
immutable proof/family/benchmark aliases are separate ownership boundaries.
Encoded byte/item limits remain distinct from actual report allocation requests
and retained/temporary overlap under the query cap. The legacy unavailable total-
memory fields are not changed into estimates. Full S05/operator reconciliation
and native acceptance remain open. See
[retained report graph evidence](verification/s05-report-capture-native-2026-11-09.md)
and [memory accounts](memory_accounts.md).
