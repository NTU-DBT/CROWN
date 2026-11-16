# Excluded O07 EXPLAIN/report proposal

**O07NS. This is an unapplied preparatory report slice; O07 remains
`not_started`.** Only this new directory is authored by this task. Native
P07 sources, CMake, tests, existing schemas, ordinary docs, historical seals,
and the frozen runtime observation proposal are unchanged.

The new C++ units are compiled and linked into `/tmp`; **no resulting binary,
CLI invocation, report fixture, benchmark, CTest or runtime test is executed
by this proposal's author**. Root owns later execution and acceptance.
Compilation evidence is interface/link evidence, not behavioral validation.

## Included implementation

- `observability::ModeDescriptor`: immutable owning current runtime descriptor,
  captured from a real `DeltaRuntime`; or a distinct compile-only descriptor.
- `observability::PlanExplanation`: immutable selected physical plan, typed
  original-query height evidence, optional typed candidate-family snapshot and
  copied runtime observation. No constructor accepts report proof flags.
- Bounded human and JSON EXPLAIN and DOT selected-tree export, sharing the same
  owning model. New renderers use a direct string writer, not a JSON DOM.
- A closed Draft 2020-12 report-v1 schema, including null-only unavailable metric
  payloads and explicit height/family/cost/observation scopes.
- A read-only standalone `crown-explain-proposal` CLI accepting an existing
  physical-plan artifact and optional independently replayed certificate.
- A compatible adapter for the separate per-attempt mode-binding proposal.
  It compiles with the older runtime header as well, retaining explicit unknowns.

`o07-explain.patch` adds six paths (two headers, two implementation units, one
standalone CLI and one schema). It is **not applied**. Future integration needs
a separate library/target linked to `crown_runtime`/planner IO and the native
CLI's `explain` dispatch. No native CMake or command dispatch is edited here.

## Authority and ownership

`PlanExplanation::create(plan, evidence, family, limits)` accepts a P08
`PhysicalPlan`, whose independent validation is already sealed in its immutable
handle. The evidence variant is closed: none, `ValidatedIncumbent`,
`VerifiedOptimum`, or `MinimumHeightCandidate`. A checked upper remains an upper;
only the checked original optimum or a candidate retaining that optimum can
establish the selected tree's minimum height.

Admission compares complete original native Catalog/Query fields, including
catalog/source versions, names/raw bytes, nullable/collation/decimal metadata,
all constraints and statuses, row/NDV input estimates, key hints, ordered atoms,
term variant tags and values, variable types/names, contradiction and
ordered/repeated head aliases. It uses neither JSON nor alpha-equivalence nor
digest-only matching. This matches P07's binding fence at the source-field level;
no private cache token is exported or repurposed as proof authority.

A supplied incumbent or selected candidate must match the selected tree exactly,
including its declared metadata. A `VerifiedOptimum` may accompany a different
P02-valid selected tree of the same height and exact original core binding:
its lower bound applies to that same family, while the certificate retains its
own original witness. The report exports that original witness separately;
it never replaces the certificate tree with the selected alternative.

Candidate contexts must match the plan's arithmetic/planner/optimization/cost
policy and known update/canonicalization versions. A candidate-family snapshot
requires explicit original minimum-height evidence. Family exhaustion covers
admitted seeds and the named normal-form family only; it never establishes global
cost completeness. Cost ranking, maintained C01 statistics and estimated state
remain unavailable/not implemented, regardless of configured policy strings or
catalog input hints.

`capture(runtime, ...)` captures a plan, current options/profile and observation
from one exclusively owned runtime without stepping, draining, reoptimizing,
inspecting state or advancing proof search. The report owns its handles and
snapshot; it can outlive the runtime. Mode profile text refers to documented
static runtime strings. No callback or mutable external lookup is retained.

The serialized report is explicitly `diagnostic_export_only`. Schema-valid JSON
is never a checked artifact and there is no report importer that can mint
P06/P07 authority. Digests identify report navigation, not native binding equality.
The report is not accepted by the native certificate reader.

## Modes and historical metric attribution

The current descriptor records actual mode, requested initial mode, requested
and resolved completion, live-maintenance strategy, core/SQL result view,
FIFO/LIFO propagation, exact arithmetic/backend, legacy full transition capture,
all nested support/physical/delta/cursor/view work/count limits, spool limits,
and observation mode/capacity/period/offset/timing options. Current runtime
profile guarantees retain their existing preparation/production/finalization/
ordered-cost/public-startup qualifications. Compile-only reports do not borrow
stale compile-time guarantee strings to claim running-engine performance.

The original observation overlay did not record attempt configuration. Against
that header, each current/last summary has `mode_binding: not_recorded` and
`configuration: null`; a subsequent `set_mode` does not relabel old numbers.

The separate [mode-binding proposal](../o07-mode-binding-proposal/README.md)
adds immutable `ObservationConfiguration` values. The generic adapter detects
that concrete interface and exports `snapshot.current_configuration` separately
from each summary's own `configuration`. The latter becomes
`mode_binding: exact_begin_configuration` and includes exact reconstructed full
`DeltaOptions`, resolved mode/completion/live/view, query factors, support owner,
generation and generation-saturation flag. Owner/generation is process-local,
not durable or proof identity; saturated generations are not unique identifiers.
Lower-only and off observations retain the not-recorded/null fallback.
Historical guarantee prose is never copied from the current runtime profile.

**This still does not discharge every benchmark-mode distinction.** The native
runtime has no retained initialization-method tag: empty direct and insertion
replay builds cannot be distinguished from `BuildMetrics` counters. DeltaRuntime
has no input-adapter identity. QuerySession accepts `InputOptions` but exposes
progress/status, not an exact retained input-format descriptor. Private output
retention/drain policy is not recoverable from an empty committed spool, and
callbacks have no external codec/sink implementation identity. Reports therefore
state `not_recorded`, `per_attempt_not_recorded` or `external_unmeasured` for these
fields. Integration must record these at construction/attempt boundaries or
attach separately labeled benchmark-runner declarations. It must not infer them
from counters or pretend arbitrary caller flags were engine observations.

## Metrics and text transport

Every JSON metric registry entry includes stable ID/name, unit, accounting
version, kind, layer, scope and inclusions. Available zeros stay numeric zero.
Disabled and unavailable fields emit **`value: null` and `saturated: null`**,
even when the internal POD retains a stale numeric payload (e.g. partial physical
work4). Human output prints unavailable/disabled, never that stale value. An
available saturated metric is labeled saturated, not claimed exact.

Physical inclusive work contains successfully charged support work; its
exclusive companion is the coordinator partition. On incomplete nested charge,
both are unavailable. Delta/replay phase subsets cannot be added to their parent
total again. Aborted summaries describe attempted accounting, not committed
changes. Prepared spool bytes remain declared accounted bytes, not RSS/live or
reserved allocator totals. Trace metadata reports truncation and dropped-count
saturation; actual causal records are not copied by EXPLAIN.

New admission/comparison code performs no text serialization. Native values
remain typed arbitrary-byte strings under the existing PhysicalPlan admission
contract. The new exporters require valid UTF-8 only for text actually emitted;
overlong/truncated/surrogate/out-of-range sequences fail with `text_encoding`.
Embedded NUL/control bytes are escaped. Quotes/backslashes cannot inject JSON or
DOT structure; graph IDs are generated numeric `n<ID>` identifiers, never labels.
DOT is diagnostic text, not a semantic round-trip or shell/Graphviz invocation.
No implicit SVG renderer is installed or run.

The writer enforces an encoded-byte limit before every append (default16MiB),
returning a complete string or throwing without touching the runtime/report.
Selected and original proof witness node counts have admission limits. Selected
C* membership is precomputed once; tree export is linear in nodes/edges instead
of scanning the connex vector for every node. The bit-vector, returned text,
proof handle history and encoder allocations are explicit diagnostic resources;
the byte limit is not S05 peak process memory. No new JSON DOM is created during
report admission, rendering or their unwind. Existing native artifact readers
and PhysicalPlan internals retain their existing implementation contracts.

## Standalone CLI proposal

The linked binary accepts:

```text
crown-explain-proposal PLAN.json [--format text|json|dot]
  [--certificate FILE] [--max-bytes N]
```

Inputs are bounded to16MiB. `read_physical` rebuilds and independently checks the
stored plan rather than trusting imported verification flags. Optional certificate
input is read against that exact core binding and independently replayed through
`CertificateReplay` under its native finite default limits before an optimum
handle can enter report admission. Replay is explicit CLI work, not work hidden
inside `PlanExplanation::create`. An infeasibility certificate cannot certify an
executable plan and is rejected. The CLI does not run the maintained query.

Status codes:0 success;2 usage;3 strict text encoding;4 allocation/output-byte
resource failure;1 other artifact/IO/evidence failure. Errors print a sanitized
code, not untrusted query/diagnostic bytes. Output is built before writing to
stdout; OS stream delivery can still fail/partially write and is not transactional
or durable output. No server, checkpoint, restore or benchmark command is claimed.

## Compiler/link evidence and reproducibility

The exact dependency closures and original/overlay hashes are in
`baseline-dependencies.json` and `baseline-dependencies-mode-binding.json`.
Each pins42 inputs, including native model/IO behavior and vendored JSON header.
Separate archive hashes are recorded in compile evidence. No existing source is
patched by the build scripts. Do not rerun `pin_sources.py` to silently bless a
changed dependency; review/rebase deliberately.

Old runtime compatibility build:

```sh
python3 docs/verification/o07-explain-proposal/build_proposal.py /tmp/crown-o07-explain-proposal
```

New per-attempt mode-binding build:

```sh
python3 docs/verification/o07-explain-proposal/build_proposal.py /tmp/crown-o07-explain-mode-binding --mode-binding
```

Both rebuild all three report/CLI consumers with the selected header ABI, then
link the matching **complete nine-unit** replacement runtime archive plus the
unchanged baseline plan/SQL/PG/core archives. They never mix a new observation
header with an old runtime archive. `CROWN_RUNTIME_TESTING` matches these specific
isolated archives; it is not a production CLI requirement. Commands, hashes,
compiler dependency files and logs are retained under the respective `/tmp`
folder and `compile-evidence*.json`. The scripts do not execute the linked binary.

No generated report has yet been validated against the schema by this author.
The schema encodes structural shape, closed enums, authority labels and null/
status relationships; cross-field selected-height equality, graph IDs, registry
ID relationships and proof validity still need independent semantic checks.
Schema validation alone never certifies these properties.

## Remaining root-owned checks and full O07 gates

Root should execute independent fixtures for checked upper versus verified
minimum, a different selected minimum tree retaining the original certificate,
candidate-family exhaustion/capacity, catalog/head/constraint/context mismatch,
constant true/false, generalized/disconnected/high-arity/projection/self-join and
SQL repeated/constant/EXISTS outputs. Compare actual selected graph/C*/separators
and normalized outputs to literal independent expectations, not a second writer.

Text checks need invalid UTF-8, NUL/quotes/backslashes/newlines, exact byte-limit
boundaries, no partial return on allocation failure, DOT injection fixtures and
large-tree scaling. Compare human and JSON height/cost/mode meaning. Validate
actual emitted JSON, then mutate missing enums, false minimum flags, unavailable
numeric payloads, family/global-cost claims and configuration-binding nullness.
Native-report exception sweeps and same-owner query reuse are still required.

Mode integration requires root-run switches showing old generation/config beside
new current configuration, failed/no-op switch preservation, generation saturation,
initialization/rebuild limit restoration, off/lower-only null binding and owner
lifetime/drop. Benchmark identity still needs initialization, input adapter/window,
retention and codec/sink context described above. Search-progress/replay status
attachments and rejected/infeasible-query EXPLAIN are not implemented by this
physical-plan report factory and remain explicit gaps.

Full O07 still requires native integration, diagnostic causal-trace export,
full metric availability/source coverage (including cursor timing, input/queue/
window/build/inspection), independent report/failure/schema fixtures and the
established frozen five-configuration matrix/audit. S05 allocator budgets,
O04/O05 recovery, O06 durable sinks, C01/C02 ranking and B03 benchmark conclusions
remain separate. This packet changes no card status or release gate.
