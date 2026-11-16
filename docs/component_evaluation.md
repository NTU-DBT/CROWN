# Component experiments

B04 separates the ten axes in [Refactor.md §14.4](../Refactor.md). The current
applications expose genuine engine operations and qualified legacy observers;
their correctness checks do not by themselves establish a speedup or complete
the experimental matrix. Query maintenance remains independent. Approximation
and parallel/distributed engine execution remain deferred.

The [V61 review](verification/full-scope-review-v61-2026-11-15.md) joins the
received finite controls below. Each study retains its own source, machine,
output obligations and units. Cross-vintage timings are not pooled.

| Axis | Received comparison and limits |
| --- | --- |
| Storage | Reference versus indexed storage within matched source/tree/trace pairs; B05, V59 and V60 remain separate cohorts. |
| Runtime | V61 interpreter versus automatically prepared SQL input program on identical actual engine/tree/backend/trace/output. [Preparation, size, cache and reproduction](input_specialization.md) describe the extra costs. V60 legacy comparisons retain whole-implementation confounders. |
| Structure | V59 independently minimum generalized trees versus checked ordinary upper trees; actual heights are reported separately from the original minimum certificate. |
| Planner | V59 height, weighted-depth and event-cost choices frozen before held-out evaluation. All six C03 fits remain underdetermined; fallbacks are retained. |
| Search | V60 literal, P06, residual and meta families with explicit work, stop and tiny-reference coverage limits. |
| Statistics | V59 exact, sampled, stale and absent observations, with unknown/unavailable scores retained. |
| Output | Maintenance, discard, encoding and local durable delivery; synthetic wait and cursor setup/termination retain their own boundaries. |
| Updates | Single events, ordered transport and atomic-net batches, with distinct observation and transaction obligations. |
| Recovery | Volatile, WAL, checkpoint and clean-owner reconstruction; no process-crash or power-loss latency claim. |
| SQL semantics | Exact set/bag/COUNT/SUM/AVG pipelines with SQLite/Fraction checks; totals include their differing source/output obligations. |

The V61 runtime study has 21 case/scale combinations, 84 gates, 4,620 independent
SQLite prefixes, 252 measured process invocations and 42 paired contrasts.
Paired loop ratios range approximately 0.937–1.034 (prepared/interpreted), with
extra cold copy/preparation and metadata costs. This finite result establishes
no broad benefit; interpretation remains the default. The
[reproducible report](experimental_report.md) retains raw links, variability,
adverse outcomes and exact source/build qualification for all six studies.

## Build the diagnostic applications

```sh
cmake -S . -B build/component-study -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DBUILD_TESTING=OFF
cmake --build build/component-study --parallel 2 --target \
  crown crown_measure_workload crown_export_components crown_component_set \
  crown_component_rows crown_component_session crown_component_aggregate \
  crown_search_components
```

The installed `component-planning` and `component-runtime` examples have
standalone CMake builds using `find_package(Crown 0.1 CONFIG REQUIRED)`.
The set and Session clients link `CROWN::runtime`, SQL rows links
`CROWN::sql_rows`, and aggregation links `CROWN::sql_aggregate_runtime`.
These applications add no hooks, retained row mirrors or exception framework to
the production update path.

The optional legacy C++ target needs all three explicit CMake paths:
`CROWN_LEGACY_CPP_SOURCE` (the original `dynagox_cpp/implement` source),
`CROWN_LEGACY_CPP_BUILD` (its qualified original build), and
`CROWN_LEGACY_FMT_SOURCE` (the matching fmt source). It links unchanged original
archives and owns concrete query classes. The Scala observer uses the original
qualified classes/JARs with a separately compiled `ComponentReplay.scala`.
See [baseline provenance and restrictions](legacy_baselines.md). Baseline
parsing, formatting, JVM and allocator costs remain included where executed;
cross-system measurements alone do not isolate generic dispatch.

## Planning and held-out scoring

```sh
PYTHONDONTWRITEBYTECODE=1 python3 tools/run_component_planning.py \
  --source . --build-dir build/component-study \
  --crown build/component-study/crown \
  --collector build/component-study/crown_measure_workload \
  --exporter build/component-study/crown_export_components \
  --output build/b04-planning --repetitions 3 --warmups 1
```

The output directory must be new. `--preflight-only` exercises native correctness
and freezes choices without held-out timing. Optional query/backend filters,
finite planner/process/output grants and CPU affinity are explicit in `--help`.
The default study uses the three existing [disjoint trace families](../benchmarks/ranking/manifest.json).
Their independent SQLite/assignment oracles cover every physical prefix.

The cold exporter receives SQL, catalog, bound training input, bound calibration
input and the [planning request](../schemas/component-planning-request-v1.schema.json).
It exports exact, residual and meta candidate families, valid ordinary trees,
search stops/work, actual heights, real statistics captures and C03 estimates.
A V3 ordinary artifact preserves the independently checked original lower proof
and separately checked actual upper. It never becomes a minimum-height claim.
V1/V2 collector paths retain their original equality/witness requirements.

The runner first exports proposals, checks every retained artifact envelope on
every split, then obtains the final calibration/export. Preliminary calibration
is unqualified preparation; its clocks/model are discarded from experimental
comparisons. Both setup passes remain charged and retained. Final source,
proof, family and artifact identities must match the preflighted proposals.
Physical plans may share a measured replay; family/control provenance is kept.
No failed candidate is silently removed to produce a passing experiment.

One final pooled calibration serves all family/statistics variants for a given
query/backend. Choices and calibration are serialized and hashed before held-out
measurement and checked throughout it. C03 selection uses exact rational
nanoseconds with structural-key ties. Missing scores, incomplete native attempts
or captured-memory exclusions trigger an explicit height fallback; the fallback
cannot select a known over-budget candidate. Current-state memory is not a
future-memory prediction. Stale stamps and unknown strata remain visible.

Demand comes from the training input mix, including zero table/operation strata.
Prediction error compares that declared forecast with actual held-out input
costs, preserving workload shifts. C02 height/depth scores retain structural
units; they do not become nanoseconds through an invented conversion. C03 is an
offline conditional model: C05 `maintenance_cost` remains unsupported. Fit rank,
unidentified columns and residuals remain reported; fitting is not evidence of
held-out accuracy or a global cost optimum.

Raw reports separate proof/setup, native prepare/commit and epoch release,
whole-event cost, requested account bytes and target-process RSS. Calibration
and measured native phases use maintenance-only, workload counters on and
optional observations off, with no output/encoding/WAL/sink demand. Warmups are
retained and excluded from summaries. Caches and CPU frequency are observed,
not guaranteed constant. Concurrent correctness/build clocks are ineligible for
controlled comparisons.

## Runtime, output and recovery controls

Each runtime application accepts one
[component request](../schemas/component-runtime-request-v1.schema.json).
The common transport contains valid unit-set `+`/`-` edits of int64 pairs;
duplicate insertion and absent deletion reject before native timing. The
program contains actual SQL/catalog metadata. Native set and Session clients
can replay a complete supplied physical source, compare its original SQL
normalization and re-lower its tree under the requested backend.

| Application | Operation and observation |
| --- | --- |
| `crown_component_set` | Genuine unweighted SQL set program. DISTINCT cardinality folds actual signed projected-set records into one checked scalar; maintenance cardinality drains current results. `delta_and_snapshot` drains both ports after every input. |
| `crown_component_rows` | Genuine weighted SQL rows. Compressed tuples carry multiplicity; this is separate from the unweighted set arm, including when SQL uses DISTINCT. Atomic net batches use the public source-replacement transaction. |
| `crown_component_aggregate` | Original admitted aggregate SQL, full groups or replacements. Optional guarded COUNT-source presentation uses the compiler's coordinate mapping. Aggregate DISTINCT remains unsupported. |
| `crown_component_session` | Actual typed Session queue, per-event commit, output drain/serialization or durable local delivery, optional WAL/generation checkpoints and clean-owner recovery. |

Transport batches preserve each physical input's transaction and output boundary.
Atomic net batches expose endpoint states: match observation intervals with the
singleton control and charge source-vector preparation plus native consolidation.
Source-input offsets, transaction sequences and compressed/expanded output units
are distinct. A faster run with fewer observation obligations is not a pure
transport-batching improvement.

WAL includes its initial checkpoint. Periodic generation rotation and recovery
occur only at empty-queue transport boundaries, including a declared final
partial batch. The adapter keeps committed generation files and requires fresh
per-pass state directories. Durable local delivery requires WAL; compare it
with nondurable output on the same journaled Session. Plain JSON serialization
into a counting sink is not durable file output. A clean-owner reconstruction
does not demonstrate process-crash or power-loss latency.
The before-teardown native-account sample belongs to the final owner. After
reconstruction it is not a whole-pass account peak across destroyed owners;
the target-process RSS observation has its separate process-wide scope. Session
reports also retain account samples before/after each reconstruction boundary
and the maximum of sampled owner peak counters. Neither is process RSS. RSS
includes compilation, all warmup/measured owners, reporting and teardown.

`session.consumer_delay_us` is a bounded synthetic consumer wait while the
committed epoch remains retained. `consumer_wait_ns` is included in output and
loop wall time; do not add it again as a disjoint phase. This control establishes
no network, queue-saturation or power-loss guarantee. Serialization uses a
counting sink; durable delivery uses the actual local sink on the same WAL basis
as its nondurable comparator.

The annotation cohort groups `r0.c0` and computes `COUNT(*)`, `SUM(r0.c1)` and
`AVG(r0.c1)`, keeping the derived source head in the complete `r0` scope. Its oracle
uses SQLite integer SUM/non-NULL COUNT and exact Fraction rounding for AVG at
the admitted default scale 18, with half ties away from zero. SQLite floating
AVG is not an oracle. See [aggregate numeric semantics](aggregates.md).
Full-head output controls have a peak of `2*w^3+w` rows: the transient extra
`r1(100,0)` fact adds `w` rows to the loaded `2*w^3` result. Total record/byte
grants still apply across the whole pass.

The native adapters have real SQLite prefix/endpoint checks, negative controls
and repeated-owner clock/output checks in
[the runtime regression](../tests/integration/component_runtime.py).
[Collector artifact checks](../tests/integration/measurement_artifacts.py) keep
the experimental upper route separate from the minimum gates.

## Run the operational cohorts

Generate explicit finite requests, then run the four genuine native clients:

```sh
mkdir -p build/b04-inputs
PYTHONDONTWRITEBYTECODE=1 python3 tools/component_workloads.py \
  --width 2 --width 4 --width 8 --cycles 2 \
  --output build/b04-inputs/operational.json
PYTHONDONTWRITEBYTECODE=1 python3 tools/run_operational_evaluation.py \
  --source . --build-dir build/component-study \
  --crown build/component-study/crown \
  --collector build/component-study/crown_measure_workload \
  --set-adapter build/component-study/crown_component_set \
  --rows-adapter build/component-study/crown_component_rows \
  --session-adapter build/component-study/crown_component_session \
  --aggregate-adapter build/component-study/crown_component_aggregate \
  --cohorts build/b04-inputs/operational.json \
  --output build/b04-operational --cpu 0 --warmups 1 --repetitions 3
```

Choose an available CPU; controlled timing requires explicit affinity. Generated
files and output directories must be new. `--preflight-only` completes the
correctness gates without timing. Event, process-time and raw-output grants are
finite; raw stdout/stderr bytes are checked after child exit, while retained
WAL/checkpoint/sink files have a separate storage scope.

Every primary arm passes independent physical-prefix/endpoint checks before any
timing invocation. Service variants with output `none` also have separate signed-output
and snapshot verification controls; those extra reads are excluded from measured
none-output obligations. One-factor declarations name every changed request
path. Transport contrasts keep each physical commit; atomic-net contrasts keep
the same observation interval and charge source-vector preparation and native
consolidation, including cancelling edits and deletions.

`--repetitions` counts fresh processes. Each process performs the same declared
fresh-owner warmups followed by one measured owner; warmups are retained and
excluded. Shared SQL/proof setup is paid once per invocation and reported
separately. Raw stage/phase distributions distinguish physical inputs, atomic
transactions, transport batches and observations. Unavailable work counters stay
null; requested account bytes and process RSS remain distinct.

## Run matched implementation controls

`build_baseline_cohorts` supplies the fixed original L3, L5 DISTINCT and L5
grouped-COUNT programs. This self-contained example keeps their native and
SQLite arms; qualified legacy arms can be retained for the full comparison:

```sh
PYTHONDONTWRITEBYTECODE=1 PYTHONPATH=tools python3 - <<'PY'
import json
from pathlib import Path
from component_workloads import build_baseline_cohorts
cases = build_baseline_cohorts((2, 4, 8), 2)
cases['arms'] = [a for a in cases['arms']
                 if a['adapter'] in ('set', 'aggregate', 'sqlite')]
names = {a['id'] for a in cases['arms']}
cases['comparisons'] = [c for c in cases['comparisons']
                        if c['baseline'] in names and c['variant'] in names]
with Path('build/b04-inputs/matched.json').open('x') as output:
    output.write(json.dumps(cases, indent=2) + '\n')
PY
PYTHONDONTWRITEBYTECODE=1 python3 tools/run_baseline_evaluation.py \
  --source . --build-dir build/component-study \
  --crown build/component-study/crown \
  --collector build/component-study/crown_measure_workload \
  --set-adapter build/component-study/crown_component_set \
  --aggregate-adapter build/component-study/crown_component_aggregate \
  --cohorts build/b04-inputs/matched.json \
  --output build/b04-matched --cpu 0 --warmups 1 --repetitions 3
```

For the unfiltered manifest, supply `--legacy-cpp` and `--legacy-provenance`, plus
`--java`, `--scala-classes`, `--scala-classpath` and `--scala-provenance` from the
[qualified baseline inputs](legacy_baselines.md). Expected Java/class/JAR bytes
must match the inherited qualification inventory. Original classes, archives
and old build prefixes remain read-only; JVM home/tmp and process side effects
use the new study directory. The complete actual V60 launch arguments are in
`build/verification/component-evaluation-v60-v1/controlled-study-commands-v1.json`.

The runner locks original SQL, physical column mapping and output obligations.
L3 processes and fully drains after every input. L5 DISTINCT folds genuine signed
set changes into one checked cardinality scalar; it does not substitute witness
COUNT or perform a full snapshot drain to obtain the count. L5 grouped COUNT
reads full groups. The finite matched inputs use positive pair facts; original
L5 DISTINCT is insert-only, while L3 and grouped COUNT include deletions and
reinsertions. SQLite executes the same query after each physical edit,
using an in-memory database whose transaction remains open until close. It
has no durability/fsync claim. Exact gates precede every measured cohort.

These are bounded whole-implementation comparisons. Selected plans, layouts,
parsers, scalar representations, formatting, allocators, JVM startup/JIT and
frameworks can all affect costs. A matched answer and schedule do not isolate
generic dispatch or establish steady-state JVM performance. C++ legacy archives
remain unsanitized Release artifacts.

## Current conditional receiving

The [V60 receiving report](verification/component-evaluation-v60-2026-11-15.md)
records sequential terminal Release studies on CPU 0, widths 2/4/8 and
`cycles=2` where deletions are supported, with one excluded warmup owner before
each measured owner:

| Study | Primary arms | Preflight invocations | Measured invocations | Contrasts |
| --- | ---: | ---: | ---: | ---: |
| Operational native | 96 | 144 (96 primary, 48 signed-service) | 288 | 72 |
| Original/native/SQLite matched | 36 | 36 | 108 | 36 |

All 432 operational and 144 matched child commands exited zero. Across both
verification passes per invocation, the operational study checks 17,632 primary
and 9,728 supplemental signed/snapshot prefix observations; the matched study
checks 14,304. Input, source/build/harness, raw-report and qualification hashes
remain bound. All 477 expected Scala runtime/classpath files agree with their
V59 parent pins, current bytes and the matched study. The 370-file production
core is unchanged by these experiment additions.

The receiving also checks 48 operational and 9 matched backend pairs. Programs,
events, output/mode, transaction/observation schedules and nonbackend grants
match; only backend envelope/index configuration and case labels differ.
Fifteen pairs export equal actual trees. Set/Session reports do not export a
separate tree, so this receiving does not infer tree equality from their
backend-specific physical hashes. Per-pair ratios remain finite workload
observations, including layout/accounting/cache and Session filesystem effects.

The separate [finite literal-search driver](../tools/run_search_evaluation.py)
uses `crown_search_components`; `--preflight-only` provides a correctness
diagnostic. Literal topology/power-set search, optimized/residual/meta attempts
and ordinary-family enumeration retain their own caps, stops and completeness
domains. Runtime receiving does not promote a stopped search to an exact family.

The [V59 planning/packaging evidence](verification/component-evaluation-v59-2026-11-15.md)
remains historical evidence. Current conditional results add measured
output/update/recovery/SQL and matched implementation observations; all ten
B04 axes and release acceptance remain open. C03 stays an offline conditional
model, and C05 `maintenance_cost` remains unsupported.
