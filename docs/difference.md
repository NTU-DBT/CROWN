# Explicit set and bag difference

`CROWN::difference` admits an explicit pair of positive non-null classical CQs
over one original source catalog. Include `crown/planner/difference.hpp` and
`crown/runtime/difference.hpp`. Each owner maintains independent sources,
sequence, finite resources and results. The [V72 acceptance](verification/difference-v72-2026-11-16.md)
records its exact source and verification scope.

## Admission and semantics

```cpp
namespace pd = crown::planner::difference;
namespace rd = crown::runtime::difference;
auto plan = pd::admit(catalog, left_query, right_query, pd::Mode::bag_except_all);
rd::Runtime owner(plan); // Initially empty physical SET sources.
auto epoch = owner.apply(update);
auto current = owner.snapshot();
```

The modes have distinct meanings for each projected key:

| Mode | Result multiplicity |
|---|---|
| `set_except` | 1 when the left has a witness and the right has none; otherwise 0 |
| `bag_except_all` | `max(left_count - right_count, 0)` |

Bag operands count every complete choice of physical rows before projection.
Distinct full rows with ignored columns or hidden variables can produce the same
key. Self-join aliases choose rows independently. Boolean bag queries count all
witnesses; Boolean set queries may stop at the first. Physical sources themselves
remain sets: inserting the same complete physical row twice is a no-op, not a
weight increment. Weighted source replacements and SQL NULL remain outside this
interface.

For example, three left witnesses and one right witness produce no set EXCEPT
row and bag EXCEPT ALL multiplicity two. Removing the sole right witness restores
set membership and changes the bag count from two to three. Removing one of
several right witnesses can change a positive bag count while membership stays
present. Results never contain negative counts or expanded duplicate tuple copies.

`planner::difference::admit` admits both original Catalog/Query operands through
bounded fallback admission. Ordered output positions must have equal arity and
ScalarType. Variable IDs, aliases and repeated/reordered head positions may
differ. Decimal precision/scale may differ: comparison uses exact canonical
values, while every residual tuple originates from the left operand and fits its
left result schema. Right-only values are never coerced into that schema.

Both operands are positive CQ values. There are no recursive, negative or nested
difference nodes, so unsupported negation cycles cannot be encoded in this API.
Positive cyclic bodies are admitted through conservative recomputation. Each
operand's actual structural class/reason stays in `Plan::profile()`. No combined
CROWN tree or GHD/P11 certificate is constructed. `source_only()` is a genuine
empty-query plan over the full original catalog, including unused tables and
UNIQUE/FK constraints; its identity belongs to source coordination.

Cold admission copies and lowers both operands separately. `Limits::left` and
`right` retain their own fallback metadata/recognition/lowering grants;
`Limits::work` bounds selected pair/head checks. Allocation, validation and copy
costs remain real cold work. Refusals use `difference_admission` or
`difference_work_limit`; native memory failures retain their own type. SQL
EXCEPT/anti-join grammar and default equality admission are unchanged.

## Source and result publication

One PhysicalRuntime coordinates full original sources and constraints. A changed
table used by either noncontradictory operand triggers one funded native
[source after-image](source_images.md). Duplicate/absent events and unused-source
updates preserve answers without recomputation, while source sequence follows
the normal physical update contract.

A shared internal freezer/iterative visitor retains the original positive query
and traverses complete physical witnesses. Its callbacks borrow projected scratch
only for the call. Set or bag consolidation belongs to the caller; the helper
supplies neither DISTINCT nor difference semantics itself. Templates introduce
no virtual dispatch, allocated callback or extra source owner.

One private ordered union-key map holds both operand counts. Set counts saturate
at presence; bag counts use the [W01 checked uint64 policy](annotations.md).
Only positive left residuals are materialized in the left layout. The owner
prepares all exact endpoint replacements before committing its physical source
token, then publishes counts and a same-allocator answer swap without allocation.
One busy guard spans preparation, source/result publication and old-state
retirement. Private RAII and the existing source token unwind refusal; there is
no second source rollback journal or catch/retry framework.

`Snapshot::rows` contains `Entry { tuple, multiplicity }`, one owning native tuple
per positive residual key in deterministic value order. `Epoch::changes` contains
`Change { tuple, before, after }` for every changed count, including positive to
positive transitions. These are exact nonnegative endpoint replacements, separate
from aggregate signed payloads. `Change::delta()` computes a difference-specific
sign and uint64 magnitude without narrowing to int64; zero-to-maximum and
maximum-to-zero are representable. Actual emitted changes have unequal endpoints.
`Epoch::input` describes the physical/support epoch, not the difference result.

Binding retains both actual native queries, profile, count limit, source schemas
and left result layout under the original account. Keep it alive while borrowing
views. Snapshots/epochs retain funded native payloads after owner teardown and
hold no source cursor lease. `snapshot()` copies compressed owning handles;
`source_snapshot()` explicitly exports an ordinary caller-owned Database for
diagnostics. Calls on one owner require external serialization. Bindings are not
serialized executable or recovery authority.

## Limits and observations

`Options::sources` retains physical/storage limits. `recompute.work` is one
balance through metadata freezing and initial results during construction, and
one balance per later apply. Image capture receives only its remaining work.
Both operands, key consolidation, residual construction and endpoint merging
spend that same balance. `source_rows` bounds every physical row in the single
image, including unused tables. `rows` caps distinct keys per operand; the union
can hold twice that many keys, and residual keys are a subset of the left.
Initial constant operands obey the cap even when their subtraction is empty.
Snapshot copying has its own explicit Limits.

`multiplicity_limit` is a positive per-key W01 uint64 limit. Each bag operand must
fit before subtraction, even if a later cancellation would make a small result.
Set mode saturates witness presence and does not overflow from repeated witnesses.
Work, row, source-image, arithmetic or allocation refusal preserves full sources,
answers and sequence; an allowed retry uses the same owner and sequence.

Metrics distinguish complete left/right assignments and distinct keys, total
selected work, source capture, scalar bytes, comparisons and output keys.
`changes` counts every numeric replacement; inherited `added`/`removed` count
membership appearances/disappearances. `EXPLAIN` reports actual source counts,
residual key count, count limit, account statistics and optional total result
multiplicity. Total sum overflow is reported as unknown, without invalidating
individually exact per-key counts. Per-operand Cartesian witness/prefix estimates
also report overflow as unknown; a later zero can make the final product zero
while earlier prefix bounds remain large or overflow.

`Plan::estimates(table_counts)` counts physical source rows once and reports both
operand bounds. Residual keys are bounded by left keys, and total residual
multiplicity by left witnesses in bag mode. Upper bounds are never subtracted to
invent a residual bound. State-row bounds cover committed sources and compressed
residual keys, not image/map/journal space or simultaneous old/new answers.

## Cost and research boundary

An update pays ordinary source validation/maintenance, full image capture, both
nested-loop prefix traversals, scalar/byte comparisons, ordered union-key work,
compressed output materialization and old/new merging. Result size can be zero
while witness work is large. Old answers, image rows, private operand keys, new
answers and delta handles can coexist under one finite account. Retained
snapshots and final-owner cleanup are additional real costs. Compressed output
cost counts keys and numeric weights, not expanded bag rows.

This is the ordinary exact recomputation contract requested by
[Refactor X08](../Refactor.md). P11 remains its research reference; no specialized
P11 maintenance, static-to-dynamic transfer, CROWN constant delay or general
negation guarantee is claimed. Approximation, shared-query optimization,
parallel/distributed execution, SQL grammar/NULL expansion and recovery remain
separate from this acceptance.
