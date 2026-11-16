# Runtime statistics

This guide describes the C01 library integration: explicit owner-state capture,
optional transactional workload observations, and the separately selected v3
statistics report. **The complete native C01 matrix is pending.** State and
workload retain independent availability,
budget and interval domains. O07's verified observation contract remains separate.

## Two different questions

Owner-state capture asks what a selected committed population looks like at one read. A caller supplies typed selections to an initialized `PhysicalRuntime` or `DeltaRuntime`. The capture reads actual tables, support maps, derivation maps, or indexes and returns an owning value. It does not advance an update, drain delta output, reset the runtime, or change its configuration. The scan may allocate and throw; its separate finite budget limits the requested work and payload model.

Workload observation asks what happened during physical input transactions. After explicit configuration, hooks record actual inputs and changed work while updates run. Scratch detail is private to an attempt and is published only by the outer successful commit. A nested rollback, aborted root, invalid route, or truncated selected sample cannot publish a prefix of that sample. This is a numeric summary of update events, not a second copy of the runtime's current tables.

Neither API estimates the global query answer count. A source projection's NDV, an occurrence's derivation multiplicities, an S/P/E support distribution, and an index's bucket degrees describe different local populations. Their counts and sums are not interchangeable with the number of query results.

## Owner-state selections

The state-capture API uses `crown::runtime::statistics::OwnerRequest`. Each `Selection` contains a typed `Scope` and optional ordered `FieldId` list. IDs must come from the actual `PhysicalPlan`, its source catalog, or its compiled occurrence/node/index identities. Resolve fields against the selected population's real layout. Do not infer IDs or field order from query text, display names, or a prior report.

| Scope | Population | Selection behavior |
| --- | --- | --- |
| `SourceScope{TableId}` | Physical source rows in the original source catalog, including unused catalog tables | No `fields` requests cardinality. A present ordered field list requests a projected distribution. |
| `OccurrenceScope{OccurrenceId}` | That actual input occurrence's derivation-count map, keyed by its complete native node key | No `fields` requests positive derivation multiplicities. Another projection is rejected. |
| `NodeScope{NodeId, SupportRole}` | A node's `records`, `survivors` (S), `parent_support` (P), or `visible` (E) population | `records` and S accept table projections. P/E expose stored positive support multiplicities over full keys; another projection is rejected. |
| `IndexScope{IndexRequirementId}` | The actual admitted nonempty buckets for that plan index | Cardinality is the number of nonempty keys; the distribution is bucket degree. Another projection is rejected. |

`NodeScope` also returns `node_kind`: `NodeKind::native` means native records, and `NodeKind::generalized` means a generalized candidate union. The `SupportRole` enumerators are `records`, `survivors`, `parent_support`, and `visible`; S/P/E are population names, not enum values. If a node has no visible E relation, its E component is `not_applicable`, not an exact zero-cardinality table. The storage-only Support owner cannot provide physical source or occurrence facts, so those scopes are `unavailable` there.

For a table with `fields`, the report retains the population's existing `TupleLayout` and the exact ordered field IDs used for the projection. It creates no temporary layout or projection metadata. The empty field list and repeated fields are valid ordered projections. Index scopes refer to already admitted indexes; capture does not register or build a new index.

An exact completed distribution has `Distribution::completion == Completion::exact`; its NDV, multiplicity histogram and top-K are known for that selected population. The histogram groups equal positive multiplicities as `(multiplicity, key_count)`. Top-K orders by multiplicity descending and then native row order. An exactly empty population is known: cardinality and NDV are zero, and the histogram/top-K are empty.

The owner API separates exactness from whether a component applies. `Component::availability` can be `available`, `budget_exhausted`, `pending_private_state`, `unavailable`, or `not_applicable`. On budget exhaustion, retain `Distribution::visited` only as progress; NDV and top-K are unknown and the histogram is empty. A missing optional value is unknown, not zero. A component may retain exact table cardinality even when its requested projected distribution ran out of budget. If metadata itself exhausts the shared budget, later requested components may be absent; `OwnerCapture::requested_components()` records the request count.

## Transactional workload observations

The online collection API uses `crown::runtime::workload`. The plan-derived descriptor list distinguishes `Kind`, `Role`, `Operation`, `InputScope`, and actual table/node/occurrence/edge/index identity. Physical plans include the source-table insert/erase strata and required roles. A Support-only owner uses logical-epoch roots: `Descriptor::initiating_table()` is empty for those roots, so no physical-input denominator is available.

`Role::adapter` and `Role::derivation` identify actual input occurrences. `Role::survivor`, `Role::parent_support`, and `Role::visible_support` describe S, P, and E updates. `Role::native_touched_degree` records the existing reverse-index bucket length for each applied child event, including zero and repeated events. `Role::generalized_probe` is a separate pre-probe presence observation with value 0 or 1; it is not a reverse-index degree. Every hook corresponds to an actual attempted operation or changed transition; the component does not deduplicate repeated values.

The collector starts in `Mode::off`. `Mode::off` retains no descriptor, route, or numeric-slab payload and performs no optional collection. `Mode::counters` enables numeric counters and bounded detail observations. Both modes read no C01 clocks. The C01 mode does not set `ObservationOptions.mode`: O07's observation mode is independent and defaults to `timed`. Leaving O07 at that default can still cause O07 clock reads even though the C01 collector itself reads none.

The workload snapshot's `Availability` values distinguish `disabled`, `unavailable`, `exact`, `sampled`, `incomplete`, and `lower_bound`. Period 1 with no loss/degradation is a census (`exact`); a larger period gives a deterministic sample (`sampled`). Selected attempt ordinals are zero-based and use `(ordinal % period) == offset`. Retries, aborted attempts, and no-op attempts advance the ordinal. This is systematic selection, not a random sample or a confidence interval. No inverse-probability expansion is done.

On an outer commit, physical input and change/no-op counters publish independently of sample selection and detail budgets; aborted attempts do not merge into committed cells. `Metadata` separately records attempts, commits, aborts, selection, completed samples, and truncation. `complete` counts committed selected untruncated attempts, including no-ops; aborted and truncated attempts do not count as complete. `input_share(descriptor)` divides one physical table/operation's committed inputs by all committed physical inputs. Detail ratios use stricter matched denominators:

- `events_per_physical_input(descriptor)` divides a detail count by `complete_detail_inputs` for the same initiating table and operation. That denominator is committed, selected, untruncated attempts, including selected no-ops. Aborted and truncated attempts are excluded. The result is an observed sample mean, not a population estimate.
- `crossing_fraction(descriptor)` uses observed unequal support-count changes as its denominator.
- `adapter_selectivity(descriptor)` uses visited routes as its denominator.

Each `Fraction` reports its denominator scope. Empty denominators are unavailable. Saturated raw counters remain visible as lower bounds, but ratios involving capped counters are unavailable; a ratio of two lower bounds is not meaningful. `arrival_per_second()` is always `unavailable`: the C01 collector has no clock or active-time scope.

Support histograms observe the after-values of changed support-count events, including zero. They are not a scan of the current positive-key population. Degree histograms record one bucket-size observation for each actual touched child event, retaining repeated and zero degrees.

## Requests, budgets, and byte accounting

An owner request holds at most 256 selections. `statistics::Limits` bounds shared `work`, `rows`, `distinct_keys`, modeled `accounted_bytes`, `projection_width`, and `heavy_keys`. One `OwnerBuilder` budget is shared sequentially across every selected layer and component. Counts are charged before the corresponding copies or insertions. Exhausting one component does not erase earlier completed components; the top-level capture reports `budget_exhausted` when any component exhausts. `OwnerCapture::usage()` and `limits()` let the caller inspect the requested bounds and usage.

`accounted_bytes` is a logical payload model, not allocator bytes, peak live bytes, or S05 total memory. It includes named report/component/requested-field and weighted-distribution payloads. It excludes allocator bookkeeping and spare capacity, caller-owned requests and report copies, existing plan/layout metadata, engine storage, fixed cursor startup allocation, stack/scratch costs, and cleanup/deallocation work.

Workload collection has a different bound. `Options::max_cells` admits all required descriptor strata together or leaves the previous configuration intact. Each selected attempt has a finite `detail_budget`; exceeding it by one action discards that attempt's staged detail while exact physical counters can still publish. `Snapshot::memory()` reports the collector object's and actual vector-capacity payloads, including route storage. It excludes allocator metadata/rounding, engine storage, caller-retained snapshots, and temporary old/new configuration overlap. This is component accounting, not total process memory or S05 evidence.

## Freshness and lifecycle

Owner captures carry an `OwnerStamp` made from the actual `SupportOwnerId`, committed sequence, and `OwnerLayer` (`support` or `physical`). `statistics_freshness(capture, max_event_lag)` compares that stamp with the current owner. Its results distinguish `current`, `within_lag`, `stale`, `foreign_owner`, `future_sequence`, and `scope_mismatch`. Equal rows or plans in a rebuilt, replayed, or different owner do not make an older capture current.

Owner components may also carry a storage `Stamp` (`StorageOwnerId`, relation, revision) as invalidation evidence. Storage revision can advance during rollback while the committed owner sequence does not. Treat it as a cursor/storage invalidation stamp, not as committed-data freshness.

Workload snapshots expose their own `Stamp`: owner, committed epoch, interval-start epoch, reset generation, configuration generation, and segment. The complete unsaturated tuple describes the snapshot's collection interval. One matching generation field alone does not establish interval identity: segment labels restart on configure/reset. It is not a method that automatically declares an old snapshot current; compare owner/epoch and all interval fields with the live runtime if needed.

Capture and update collection have different barriers:

- Owner capture is an explicit synchronous read. If a physical, Delta, or session operation has private state, the returned report is metadata-only with `pending_private_state`; it does not read tentative tables or drain work. A committed Delta epoch with unread published output remains a committed state capture.
- Workload configure and reset are explicit quiescent writer barriers. They reject pending work and other prohibited readers/output states. `workload_statistics()` remains readable during private work and committed unread output, but marks `Snapshot::pending()` and exposes committed counters only. Updates do not allocate in the C01 collection hooks. Snapshot creation may allocate.
- A successful semantic Delta mode change rotates the workload interval after publication. Failed or no-op mode changes do not rotate it. Constructor mode binding is not a measured segment.
- Reset clears current and prior interval data and sample ordinals without changing the query's committed epoch. Reconfiguration has a strong guarantee: a failed request leaves the prior configuration and counters intact.
- Factory-produced owner captures and workload snapshots own their copied plan/metadata and values. Later updates, reset, reconfiguration, or segment rotation do not rewrite an earlier handle.
- `capture_combined_statistics(request, limits)` is available on the combined Support, Physical, and Delta owners. It returns `statistics::CombinedCapture`; `state()` and `workload()` expose the two owning handles without merging their statuses or interval semantics. The factory checks that owner, committed sequence, plan identity, and pending status agree. The QuerySession form uses one session guard and returns `std::optional<CombinedCapture>` so a dropped owner remains disengaged.
- A stopped `QuerySession` retains its runtime and can still expose committed statistics. After drop, `capture_statistics`, `capture_combined_statistics`, and `workload_statistics` return disengaged `std::optional`; already returned owning values remain readable. The separate `snapshot()` API throws `session_dropped`. `capture_statistics_context()` still returns retained metadata, and `StatisticsExplanation::capture()` returns a released report with unavailable state/workload facts, as described below.

## C++ use

The following examples operate on initialized runtime objects. The caller has already created them through the normal `PhysicalRuntime::initialize(plan, database)` or `DeltaRuntime::initialize(plan, database, options)` path. `source_table`, `node`, `field`, and descriptor identities are supplied from that runtime's actual validated plan/catalog. This guide does not invent a SQL string, numeric ID, field order, or index that may not exist in a caller's plan.

### Capture a local committed population

```cpp
#include "crown/runtime/owner_statistics.hpp"
#include "crown/runtime/physical.hpp"

#include <optional>
#include <vector>

void inspect_state(crown::runtime::PhysicalRuntime& physical,
                   crown::TableId source_table,
                   crown::NodeId node,
                   crown::FieldId field_from_node_layout) {
  namespace statistics = crown::runtime::statistics;
  statistics::OwnerRequest request;
  request.selections.push_back(
      statistics::Selection{statistics::SourceScope{source_table}, std::nullopt});
  request.selections.push_back(statistics::Selection{
      statistics::NodeScope{node, crown::runtime::SupportRole::survivors},
      std::vector<crown::FieldId>{field_from_node_layout}});

  const statistics::OwnerCapture captured =
      physical.capture_statistics(request, statistics::Limits{});
  if (captured.availability() == statistics::Availability::pending_private_state) {
    return;
  }
  const statistics::Freshness freshness = physical.statistics_freshness(captured, 0);
  (void)freshness; // Use the result before treating an older value as current.

  for (const statistics::Component& component : captured.components()) {
    if (component.availability != statistics::Availability::available) {
      continue;
    }
    if (component.cardinality.has_value()) {
      const std::uint64_t keys_or_rows = *component.cardinality;
      (void)keys_or_rows;
    }
    if (component.distribution.has_value() &&
        component.distribution->completion == statistics::Completion::exact &&
        component.distribution->ndv.has_value()) {
      const std::uint64_t ndv = *component.distribution->ndv;
      (void)ndv;
    }
  }
}
```

`SourceScope` here asks for source cardinality. `NodeScope` asks for the node's S population and projects it to the supplied field. Replace `SupportRole::survivors` with a role that exists on the selected node. The copied `FieldId` must be valid in that population's layout and the desired order must be explicit.

### Read workload observations from a Delta owner

```cpp
#include "crown/runtime/delta.hpp"
#include "crown/runtime/combined_statistics.hpp"
#include "crown/runtime/workload_statistics.hpp"
#include "crown/runtime/owner_statistics.hpp"

#include <optional>

void inspect_updates(crown::runtime::DeltaRuntime& delta,
                    crown::TableId source_table) {
  namespace workload = crown::runtime::workload;
  namespace statistics = crown::runtime::statistics;
  workload::Options options{};
  options.mode = workload::Mode::counters;
  options.period = 64;
  options.offset = 0;
  delta.configure_workload_statistics(options); // Call at a quiescent barrier.

  statistics::OwnerRequest request;
  request.selections.push_back(
      statistics::Selection{statistics::SourceScope{source_table}, std::nullopt});
  const statistics::CombinedCapture combined =
      delta.capture_combined_statistics(request, statistics::Limits{});
  const statistics::OwnerCapture& state = combined.state();
  const auto freshness = delta.statistics_freshness(state, 0);
  (void)freshness;
  const workload::Snapshot& snapshot = combined.workload();
  if (state.availability() == statistics::Availability::pending_private_state) {
    return;
  }
  if (snapshot.pending()) {
    return;
  }

  std::optional<std::size_t> physical_insert;
  std::optional<std::size_t> first_adapter_insert;
  const auto descriptors = snapshot.descriptors();
  for (std::size_t i = 0; i < descriptors.size(); ++i) {
    const workload::Descriptor& descriptor = descriptors[i];
    const auto table = descriptor.initiating_table();
    if (!table.has_value() || *table != source_table ||
        descriptor.operation != workload::Operation::insert) {
      continue;
    }
    if (descriptor.kind == workload::Kind::physical) {
      physical_insert = i;
    } else if (descriptor.kind == workload::Kind::occurrence &&
               descriptor.role == workload::Role::adapter && !first_adapter_insert.has_value()) {
      first_adapter_insert = i;
    }
  }

  const auto cells = snapshot.cells();
  if (physical_insert.has_value() && *physical_insert < cells.size()) {
    const workload::Fraction share = snapshot.input_share(*physical_insert);
    (void)share; // Numerator/denominator describe this stratum/all physical inputs.
  }
  if (first_adapter_insert.has_value() && *first_adapter_insert < cells.size()) {
    const workload::Fraction sample_mean =
        snapshot.events_per_physical_input(*first_adapter_insert);
    const workload::Fraction selectivity =
        snapshot.adapter_selectivity(*first_adapter_insert);
    (void)sample_mean; // Uses matching complete samples for this table/operation.
    (void)selectivity;
  }
  const workload::Availability arrival = snapshot.arrival_per_second();
  (void)arrival; // The current API always returns unavailable; it reads no clock.
}
```

`configure_workload_statistics` derives the admitted descriptors from the actual plan; the code searches the owning snapshot's descriptor list instead of assuming descriptor numbers. Increase `max_cells` explicitly if the complete plan strata do not fit. A physical share uses all committed physical inputs, while a detail mean uses matching complete-sample physical inputs and must be read together with its `Availability` and `DenominatorScope`.

## Statistics-aware reports

`observability::StatisticsExplanation::capture` accepts an actual `DeltaRuntime`
or `QuerySession`. The factory binds its own `CombinedCapture` to the actual
owner, committed sequence, physical plan, pending barrier, and O07/mode/session
facts. It accepts no caller-made stamps, exactness flags or arbitrary paired
snapshots. Reports own immutable values and retain no runtime pointer, cursor
lease or row pin. Later updates, reset, mode changes, move, stop and drop cannot
rewrite a previously returned report.

With default `StatisticsCaptureOptions`, capture requests no state components
and performs no state traversal; state is `not_requested`, not zero. Workload
and O07 metadata copies may allocate. Set `options.state` and `state_limits`
explicitly to select and bound a state scan. Updates and ordinary report capture
never initiate a silent whole-state statistics scan.

```cpp
#include "crown/io/statistics_explain.hpp"

#include <optional>

crown::io::StatisticsText export_statistics(
    const crown::runtime::DeltaRuntime& owner, crown::TableId source_table,
    const crown::observability::StatisticsExplanation* previous = nullptr) {
  namespace statistics = crown::runtime::statistics;
  crown::observability::StatisticsCaptureOptions options;
  options.state.emplace();
  options.state->selections.push_back(
      statistics::Selection{statistics::SourceScope{source_table}, std::nullopt});
  options.state_limits = statistics::Limits{};
  const auto report = crown::observability::StatisticsExplanation::capture(
      owner, options, previous, 0); // Explicit zero committed-event lag.
  return crown::io::write_statistics_json(report, {16 * 1024 * 1024, 1000000});
}
```

The v3 scope is owner statistics with current and begin-bound mode context. It
includes admitted plan identity and checked native height, rather than replacing
the existing complete query/tree/proof document. O07 mode/options and C01
mode/options, including independently disabled collection, appear explicitly.
Caller benchmark labels are declarations, not measured instrumentation. There
is no C01 arrival-rate clock, cost ranking, estimated total state size, global
cost optimum, or new structural proof authority. Runtime capabilities do not
encode repository task acceptance.

The original `PlanExplanation::capture` for a full runtime/session report throws
`explain_statistics_version` if actual C01 mode is counters, including a dropped
session retaining that option. Choose the statistics API explicitly. With C01
off, legacy v2 bytes and all existing schemas are unchanged. Structural
`PlanExplanation::create(plan)` and tree-only exports retain their compile-only
scope. This integration adds no CLI flags or new operational workflow.

Session capture obtains one guarded runtime-only `SessionStatisticsContext`.
Report construction consumes it in the observability layer; runtime remains
independent of report IO. The context includes metadata-only window private
work in its pending barrier. Pending capture exposes committed workload counters
and marks state `pending_private_state`; it never reads tentative tables or
drains work. Published unread output is committed. A stopped session retains
its owner; after drop, a new v3 report has null state/workload facts with
`runtime_released`, while fixed retained options/status remain explicitly scoped
as historical metadata. Drop does not allocate a new C01 state snapshot.

An optional previous factory report and explicit event-lag bound request a
comparison against the newly captured actual owner. Data freshness is separate
from workload configuration/reset/segment comparisons. A successful no-op
advances the data epoch. Reset/configuration/mode changes can change the workload
interval without changing that epoch. Equal rebuilt data is still a foreign
owner. A pending or incomplete capture can carry a current stamp without having
exact component facts. Inspect all generation domains and saturation flags;
`segment == same` alone is not interval identity.

## Export, unknown values and errors

`io::write_statistics_json` and `io::write_statistics_text` return an owning
`StatisticsText` with `text` and the JSON value-item count `items`. Their
`StatisticsTextLimits` defaults are 16 MiB and 1,000,000 items. Each object,
array, scalar and null counts as one item; field names do not. Human export is
a fixed explanatory preface followed by the same complete JSON artifact and
a newline; all its bytes count toward the cap. These output limits are separate
from the state scan budget. Exact-boundary output succeeds; a one-under or zero
bound that cannot hold the artifact fails with `resource_limit`. Failure returns
no partial string and leaves the owner and earlier reports unchanged.

The closed [v3 schema](../schemas/statistics-explain-v3.schema.json) represents
unknown/incomplete numeric facts, NDV, histogram and top-K as null with a reason.
An exact empty population is zero or an empty array. Raw saturated counters are
lower bounds; derived ratios involving clipping are unavailable. Support-event
after-value histograms, generalized pre-probe 0/1 presence, and touched-index
event degrees are distinct from current-state multiplicity histograms.

Native values retain type tags. Int64 uses exact integer tokens, Bool a boolean,
Date its finite canonical spelling, and Decimal its exact canonical decimal
string. Readers must preserve integer precision. Strings and native byte labels
use lowercase hexadecimal bytes, preserving embedded NUL and arbitrary bytes
without UTF-8 replacement. Ordered/repeated/empty projections are preserved.
Native scalars do not acquire SQL NULL; report nulls mean explicit unknowns.

Malformed state selection/projection requests use `invalid_statistics_request`
or the relevant native layout/ID diagnostic. Workload sampling requires a
positive period and `offset < period`; invalid options throw
`std::invalid_argument`, and descriptor/capacity admission failure throws
`std::length_error`. Existing owner lifecycle, read-lease and Session thread/
reentry guards still apply. Configure/reset require a quiescent writer boundary;
Session rejects private work with `session_pending_epoch` and released owners
with `session_dropped`. A failed configuration preserves its prior collector.
Capture/copy/export may throw `std::bad_alloc`; failures do not advance or mutate
the owner. `statistics_binding` rejects an inconsistent captured report boundary;
`statistics_encoding` rejects an unsupported internal encoding value.

Output caps do not bound total allocator use or CPU instructions. Formatting,
spare string capacity, report/session controls, copied O07 traces, numeric
snapshots, and caller-retained history are outside the state payload budget.
Ratio lookup can be quadratic in the bounded admitted descriptor count; export
does not traverse engine tables. The state payload and workload vector-capacity
models remain separate component accounting, not total/peak allocator memory or
S05 evidence.

## Evidence and remaining acceptance

Accepted excluded evidence is preserved under `docs/verification`: the combined
package manifest is `cb0ecb64935f80bf4915aa069de1bf01bcf1ea2f22a591f6f7408d405fcf4cfe`;
its root attempt 1 covers production/testing and full sanitizers. The policy
order package `c3f11fa66b1fdb205cb1f0a094cc593f8b39e7ba744b27b68db99e61ba5e9f40`
passes seven selected FIFO and seven analogous LIFO policy/replay/window cases
in root policy attempts 3/4. The scalar package
`5fbbbc598fa724eda5042a680d3c34789a6c17a698c7ecbd102a4f7ad0008a48` passes seven
typed-domain/constraint groups in strict and complete sanitizer closures.
These are selected policies, not an exhaustive Cartesian product.

The report package `730a7488e53a749b024b307dab27c09d58a324ae7603bccc8831364af289f947`
passes both strict producer, allocation-recovery, runtime-only-link, legacy-byte
and independent schema/mutation suites in
`build/verification/c01-statistics-report-root-attempt-1.json`; that exact record
is `strict_only`. Its accepted complete sanitizer continuation is
`build/verification/c01-statistics-report-root-attempt-2.json`, summarized in
`docs/verification/c01-statistics-report-root-results-2026-11-07.md`. Each build
uses matching production/testing closures; four report allocation sweeps cover
61/14/11/13 failure positions per variant. The independent Astra report review
records no blocker. The guide's earlier four extracted compile
units are recorded in the guide compile revision; compilation is not execution.

Native CMake registration and the full compiler/sanitizer/clean-source/legacy
matrix remain to be accepted separately.
The task ledger and root evidence, rather than the existence of APIs, schemas
or registered tests, determine C01 acceptance. C02 ranking, total allocator
accounting and O08 recovery remain separate work.

## Scoped actual-engine collection costs

Root accepted the separate actual-engine benchmark metadata package
`ec56c17328662ebf3470e86c50f1249de03deee390f1897cf9a1ed454c3741c9`.
The complete record is
`docs/verification/c01-statistics-native-benchmark-root-results-2026-11-07.md`;
summary and raw durations are in
`build/verification/c01-statistics-native-benchmark-root-attempt-3.json` and
its `-raw.json` sibling. This is an excluded measurement of the frozen combined
candidate, not a benchmark of the later integrated native build.

Each profile used 5,000 prebuilt events, two untimed warmups and nine measured
repetitions, seed `2026110707`, fresh owners, O07 off and transition capture
false. Median milliseconds for the full stream were:

| Actual path | C01 off | Census | Period 64, offset 0 |
| --- | ---: | ---: | ---: |
| Physical apply | 26.488 | 54.699 | 43.542 |
| Delta maintenance | 36.288 | 64.639 | 53.900 |

Collection costs are substantial on this small synthetic engine workload.
Sampling reduces detail work while still paying physical-census and dense
scratch/merge costs. Delta measured begin/drain/commit with pull-draining in
maintenance mode, without signed output. Initialization, configuration, parsing,
plan lowering, capture/export, sink delivery, and other output/maintenance
policies were outside the timer. All profiles matched independent semantic and
mandatory-work guards. The preserved record includes every duration, dispersion,
hardware/load context and the corrected original oracle failure.

The 62 enabled cells retain 126,608 bytes of descriptor/route/slab capacity,
plus a 624-byte State object. Off retains zero such vector payload but the same
624-byte State object. Period-64 sampling retains the same capacities as census.
These are component payloads with the exclusions already described, not total
or peak memory. The off path is the candidate's disabled collector, not an
engine built without C01; no zero-off-overhead claim follows. Shared-host timing,
fixed profile order and this one workload establish no performance threshold,
production prediction, arrival rate, cost model or S05 acceptance.
