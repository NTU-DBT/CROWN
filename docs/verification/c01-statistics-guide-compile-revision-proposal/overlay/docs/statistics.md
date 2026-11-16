# Runtime statistics

**O07 is verified. C01 remains `not_started` and excluded from native builds and public report schemas.** This revision is reconciled to the current combined proposal overlay, which exposes explicit owner-state capture and transactional workload observations from the actual runtime owners. They still have independent availability, budget, and interval domains; their combined handle does not integrate them into native reports or schemas.

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

Workload snapshots expose their own `Stamp`: owner, committed epoch, interval-start epoch, reset generation, configuration generation, and segment. It identifies the snapshot's collection interval. It is not a method that automatically declares an old snapshot current; compare its owner/epoch with the live runtime if needed.

Capture and update collection have different barriers:

- Owner capture is an explicit synchronous read. If a physical, Delta, or session operation has private state, the returned report is metadata-only with `pending_private_state`; it does not read tentative tables or drain work. A committed Delta epoch with unread published output remains a committed state capture.
- Workload configure and reset are explicit quiescent writer barriers. They reject pending work and other prohibited readers/output states. `workload_statistics()` remains readable during private work and committed unread output, but marks `Snapshot::pending()` and exposes committed counters only. Updates do not allocate in the C01 collection hooks. Snapshot creation may allocate.
- A successful semantic Delta mode change rotates the workload interval after publication. Failed or no-op mode changes do not rotate it. Constructor mode binding is not a measured segment.
- Reset clears current and prior interval data and sample ordinals without changing the query's committed epoch. Reconfiguration has a strong guarantee: a failed request leaves the prior configuration and counters intact.
- Factory-produced owner captures and workload snapshots own their copied plan/metadata and values. Later updates, reset, reconfiguration, or segment rotation do not rewrite an earlier handle.
- `capture_combined_statistics(request, limits)` is available on the combined Support, Physical, and Delta owners. It returns `statistics::CombinedCapture`; `state()` and `workload()` expose the two owning handles without merging their statuses or interval semantics. The factory checks that owner, committed sequence, plan identity, and pending status agree. The QuerySession form uses one session guard and returns `std::optional<CombinedCapture>` so a dropped owner remains disengaged.
- A stopped `QuerySession` retains its runtime and can still expose committed statistics. After drop, session capture/snapshot methods return disengaged `std::optional`; already returned owning values remain readable.

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

## Native integration and evidence boundary

The existing O07 v2 EXPLAIN/report and tree schemas do not contain these C01 APIs. Compatible report and schema integration remains pending, as does native engine overhead measurement. The accepted component benchmark measured a synthetic replay of 50,000 attempts over 96 fixed slots/eight groups (seed `2026110701`, two warmups, nine runs): median times were 2.062 ms for no collector calls, 2.341 ms for off collector calls, 31.863 ms for census counters, and 19.956 ms for period-64 counters. These are component microbenchmark numbers under one deterministic synthetic workload, not engine throughput or query latency; they do not establish all-off engine parity, production representativeness, a performance threshold, or C01 acceptance.

C01 remains `not_started` and excluded preparation. Root will reconcile this guide against the frozen combined proposal before any native documentation or API publication.
