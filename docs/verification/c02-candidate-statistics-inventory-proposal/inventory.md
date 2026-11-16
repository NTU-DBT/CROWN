# Existing candidate and statistics surfaces

This is an API inventory for future C02 discussion. It records what the
repository currently exposes and how to obtain it. It does not rank candidates
or estimate their maintenance cost.

## 1. Obtain admitted minimum-height candidates

The authority input is `planner::VerifiedOptimum`, not an arbitrary tree, a
`HeightCertificate` aggregate, an `OracleResult`, or a successful P02 check by
itself. `ExactSearch::optimum()` publishes the handle after proof completion.
For an external certificate, `CertificateReplay::checked()` publishes a
`CheckedCertificate`; its `optimum()` can return the typed optimum. A
`ValidatedIncumbent` is only a checked upper bound.

Create `planner::CandidateProvider` with that handle. Its explicit admission
also checks the optional residual seed and cached prefix against the exact
Catalog/Query binding and `CandidateContext`. The default context is the
versioned `mixed_full_row_set_v1`, `exact-nonnull-v1`, `crown-tree-v1`,
`structural-height-v1`, `no-cost-v1`, and `structural-tree-key-v1` combination.
The `no-cost-v1` name does not imply a cost score or cost guarantee.

`advance(WorkQuantum)` can return `candidate_ready` repeatedly. Read each
published member with `candidate(i)` or `candidate_count()`. A published
`MinimumHeightCandidate` exposes:

| Accessor | Existing contract |
| --- | --- |
| `tree()` | The immutable candidate tree. |
| `height()` | Its P02-checked native height. It must equal the original proof height. |
| `structural_key()` | The complete versioned structural key string. |
| `provenance()` | Exact witness, residual seed, or normal-form source. |
| `original_proof()` | The original optimum handle; an alternative tree does not replace its witness. |

Every proposal passes independent P02 validation before publication. Taller
trees are excluded; a validated tree below the certified height is an internal
consistency failure. Deduplication uses the full structural key. The provider
order is exact witness, optional residual, cached prefix, then fresh
normal-form enumeration; this order is not a score or ranking policy.

`candidate_count()` is only the published prefix. A ready candidate, a count
limit, or any resource stop does not mean the family is complete. For a full
declared-family inventory, continue until `CandidateStop::exhausted` and
`progress().family_exhausted` are both observed. Exhaustion covers the finite
seed and declared normal-form family; it does not cover every valid tree shape
or a global maintenance-cost search.

## 2. Height, per-occurrence root depth, and stable structural tie keys

`VerifiedOptimum::height()` is the certified minimum native height. Every
admitted candidate's `MinimumHeightCandidate::height()` must equal it, and
`CandidateProgress::verified_original_height` carries the same target in
provider progress. `ValidationReport` also exposes global `edge_depth`, but
neither it nor `MinimumHeightCandidate` exposes a per-node or per-occurrence
native depth.
For a candidate, derive that map by traversing its own `tree()` from `root`:
carry the parent count, add one when the current node is `NodeKind::native`,
and record the resulting count against that native node's `occurrence`. A
generalized node adds zero. This is a per-tree traversal, not a stored C01
statistic. P02 separately checks native occurrence coverage, native scopes,
tree shape, separators/guards/connectivity, and the claimed global height.

The `structural_key()` is a suitable deterministic tie key only within an exact
Catalog/Query binding and compatible `CandidateContext`. Its versioned full
encoding preserves root, node kind, scope, topology, and the original occurrence
identity on native nodes. It canonicalizes child order by sorting complete child
tokens; display node IDs and node-vector order are not identity. Equal key bytes
are not proof authority, and the key alone is not a global identifier. The
provider does not define a score or prescribe lexicographic ranking; a consumer
can use the full string as a deterministic tie key after its own ranking rule.

### Fixture-derived examples

These are manual native-node counts along existing fixture trees, not new
admission or proof results. Existing `candidates_test.cpp` compares complete
Boolean R/S/T and three-occurrence self-join normal-form families (3 and 4
normal-form members respectively).

| Existing tree fixture | Root-to-occurrence native depths | Global native height |
| --- | --- | ---: |
| `boolean_rst_native_s_root.tree.json` | `S=1`, `R=2`, `T=2` | 2 |
| `boolean_rst_generalized_x_root.tree.json` | `R=1`, `S=1`, `T=2` | 2 |
| `boolean_rst_generalized_y_root.tree.json` | `T=1`, `S=1`, `R=2` | 2 |
| `self_join_left_direct.tree.json` | `left=1`, `right=1`, `third=1` | 1 |

The self-join query has three distinct atom occurrence IDs (`left`, `right`,
`third`) over the same catalog table `Edge`. The fixture tree keeps those
occurrences separate even when their physical base is shared. The numeric IDs
assigned by a compiled plan are obtained from that plan, not inferred from
these fixture labels.

## 3. Lower each candidate and map occurrence to physical table

For each admitted tree, `planner::lower_tree(catalog, query, candidate.tree(),
options, limits)` independently validates and constructs a `PhysicalPlan`.
This lowering proves only that supplied tree is a valid upper plan; minimum
height comes from the separately held `VerifiedOptimum`/candidate gate.

Use `PhysicalPlan::inputs()` and `base_routes()` for the concrete mapping:

* Each `PhysicalInput` carries `occurrence`, `node`, `base`, and
  `logical_table`. `base` identifies the original physical catalog table,
  including SQL aliases; `logical_table` identifies the core table after
  numeric filtering/projection normalization.
* `base_routes()[table_id]` lists the `OccurrenceId`s routed from that physical
  base. Repeated query occurrences remain separate routes; they are not
  collapsed merely because they name the same table.
* `nodes()`, `edges()`, and `indexes()` describe this compiled tree's node,
  edge, and `IndexRequirementId` domains. These IDs are plan-local.

For the existing self-join fixture, all three occurrence IDs map to `Edge` in
the physical catalog, while the selected tree assigns separate native nodes
to `left`, `right`, and `third`. A different candidate can place those native
occurrences at different nodes/depths and can compile a different edge/index
layout. Re-lower and read the mapping from each candidate's own plan.

## 4. Current owner-state scopes

`PhysicalRuntime`, `DeltaRuntime`, and `SupportRuntime` expose
`capture_statistics(OwnerRequest, Limits)`. The `OwnerCapture` owns a copy of
the actual `PhysicalPlan`, exposes its owner stamp, component vector, global
availability, usage, limits, and `physical_source_scope()`. The selection
union is explicitly typed:

| Selection scope | Current meaning and candidate-local binding |
| --- | --- |
| `SourceScope{TableId}` | Physical source table. With no `fields`, `cardinality` is its current full-row set size. Explicit fields request an ordered projected distribution/NDV. Only a physical owner has this scope. |
| `OccurrenceScope{OccurrenceId}` | Actual native derivation population for that occurrence: cardinality is the number of adapted native keys, and the distribution weights each complete key by its derivation multiplicity. Projection fields are rejected. `node_kind` reports the owning plan node kind. |
| `NodeScope{NodeId, SupportRole}` | One native or generalized plan node selected by its plan-local NodeId. `Component::node_kind` distinguishes kind. Roles are `records`, `survivors` (S), `parent_support` (P), and `visible` (E); P/E distributions use complete stored keys with multiplicities. `visible` is `not_applicable` if the node has no visible relation. |
| `IndexScope{IndexRequirementId}` | One compiled index in this plan. Cardinality is its key count and its distribution describes degrees/multiplicities; another projection is rejected. |

`OwnerRequest` allows at most 256 selections. Each component reports an
availability (`available`, `budget_exhausted`, `pending_private_state`,
`unavailable`, or `not_applicable`), optional layout/cardinality/distribution,
and optional storage invalidation stamp. Distribution completion is
`exact` or `budget_exhausted`; NDV and heavy-key detail are optional. A single
`statistics::Limits` budget is shared across the ordered capture request
(`work`, `rows`, `distinct_keys`, `accounted_bytes`, projection width and
heavy-key capacity). Earlier components can consume budget needed by later
components. Incomplete output is not an exact candidate estimate.

`SupportRuntime` is lower-only: physical source and occurrence scopes are
unavailable there. `PhysicalRuntime` and `DeltaRuntime` expose the physical
source mapping; Delta delegates these state captures to its underlying physical
runtime. `CombinedCapture` packages `state()` and `workload()` together while
retaining their separate availability/stamp domains.

The workload side has its own typed descriptor fields. Physical roots use a
physical `table` plus insert/erase operation. Detail descriptors retain the
plan-local occurrence/node/edge/index, with roles `adapter`, `derivation`,
`survivor`, `parent_support`, `visible_support`, `native_touched_degree`, or
`generalized_probe` as applicable. The native-touched-degree and generalized
probe roles distinguish different edge work; neither is a cross-plan scope ID.

### Freshness is not storage invalidation

`OwnerCapture::stamp()` is `{SupportOwnerId, committed sequence, OwnerLayer}`.
`statistics_freshness(capture, max_event_lag)` compares that committed owner
and sequence: possible results include `current`, `within_lag`, `stale`,
`foreign_owner`, `future_sequence`, and `scope_mismatch`. A committed no-op
still advances owner sequence, so an earlier capture can become stale despite
unchanged source cardinality.

`Component::storage_invalidation` instead carries storage owner, relation, and
storage revision. It is a storage invalidation cursor, not the owner epoch;
rollback may advance it without a committed event. Do not use it in place of
`OwnerStamp` freshness. An in-progress physical update yields
`pending_private_state`, not tentative owner facts.

## 5. Current workload input strata

`PhysicalRuntime` and `DeltaRuntime` expose `configure_workload_statistics`,
`reset_workload_statistics`, and `workload_statistics`. Their configured plan
is physical-owner mode: each physical source table has insert and erase root
descriptors (`Kind::physical`, `Role::input`, `InputScope::physical_table`).
The committed root-cell totals report `inputs`, `changed`, and `noop` for that
exact table/operation stratum. A physical no-op contributes an input and noop;
it has no actual support/occurrence event. Delta delegates configuration to
the physical runtime, and its outer transaction controls final publication.

`SupportRuntime` counts lower-only native epochs, so its root is `Kind::logical`
with `InputScope::logical_epoch`; source table cardinality and physical input
denominators remain unavailable. Do not manufacture a table ID or compare its
logical denominator to a physical input stratum.

`workload::Options` selects `Mode::off` or `Mode::counters`, with `period`,
`offset`, `detail_budget`, and `max_cells`. Counters read no clocks. Root
physical input/changed/noop totals include every committed input regardless of
sampling or detailed-event truncation. Detailed occurrence, support, and
degree cells are selected by the collector's attempt ordinal
`ordinal % period == offset`; this ordinal includes retry/abort/no-op attempts,
and a snapshot does not expose an event-by-event ordinal. Aborts do not publish
their scratch facts. Selected no-ops are included in complete sample-input
denominators; truncated or aborted attempts are not.

The exact fraction contracts are:

| Snapshot API | Numerator / denominator | Constraints |
| --- | --- | --- |
| `input_share(id)` | Physical root `inputs` / all committed physical root inputs across tables and operations. | Full-population input share, independent of detail sampling. Saturation or zero total makes the ratio unavailable. |
| `events_per_physical_input(id)` for a physical root | Root inputs / matching root table+operation inputs. | Committed physical stratum. |
| `events_per_physical_input(id)` for physical-table detail | Occurrence visits, support changes, or degree observations / matching root `complete_detail_inputs`. | Denominator is completed selected detail samples for the same initiating table and operation; selected no-ops count, aborts/truncation do not. No population extrapolation is made. |
| `crossing_fraction(id)` | Support zero-to-positive plus positive-to-zero crossings / observed support changes. | Observed changes only; zero denominator or saturation is unavailable. |
| `adapter_selectivity(id)` | Accepted / visited routes. | Observed route events only; zero denominator or saturation is unavailable. |
| `arrival_per_second()` | Always unavailable. | No C01 clocks or upstream arrival interval are provided. |

`detail_availability()` is `disabled` when off; `lower_bound` after counter
saturation; `incomplete` when committed work is truncated or the collector
reports degraded coverage; otherwise it is `exact` for period 1 and `sampled`
for a larger period. A `Fraction` whose counters saturate is unavailable even
when raw capped counts remain visible. `Metadata` separates attempts,
committed/aborted, selected/complete, aborted-selected, truncated and
committed-truncated counts. Changed/noop and detail events therefore have
different populations, coverage, and valid denominators.

## 6. Facts that stay plan-local

Do not carry these values from one candidate to another by vector position or
structural key alone:

* `NodeId`, `OccurrenceId`, `IndexRequirementId`, relation IDs, edges, routes,
  and native root-depth maps belong to one lowered `PhysicalPlan`.
* `OwnerCapture` is tied to its actual owner, layer, committed sequence, and
  copied plan. An owner report from another runtime is foreign even if the
  Catalog/Query inputs match.
* Workload descriptor/cell positions are generated from the configured plan's
  exact routes and update policy. Obtain descriptor IDs and cells from that
  snapshot's own spans.
* Exact structural key bytes are namespaced by exact Catalog/Query binding and
  `CandidateContext`; key equality alone does not transplant proof, physical
  mapping, runtime data, or capture freshness.
* Even if candidates use the same source database, source cardinality and
  captured distributions must be read from or explicitly validated against
  the actual owner being described. Do not assume one candidate's runtime
  state/capture is the other's.

These existing APIs supply descriptive facts and constraints only. This packet
does not choose a composite score, extrapolate sampled events, compare
maintenance cost, estimate allocator bytes, or predict future runtime cost.
