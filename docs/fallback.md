# Explicit exact-set fallback

`CROWN::fallback` supplies an explicit public-IR backend for validated non-null
exact-set conjunctive queries, including cyclic bodies and acyclic
non-free-connex heads. Include `crown/planner/fallback.hpp` and
`crown/runtime/fallback.hpp`. Each Runtime owns independent sources and results.
The [V71 acceptance](verification/general-query-fallback-v71-2026-11-16.md)
records the checked source and actual verification scope.

## Admission and interface

`planner::fallback::admit(catalog, query, physical_options, limits)` copies the
original catalog and query after bounded cold metadata admission. Recognition
validates that input and reports its actual structural class. An exhausted
recognition grant is a refusal, never a structural class. `Plan::profile()`
retains `cyclic_body`, `non_free_connex_head`, `explicit_reference_choice` or
`contradiction` as its reason. All three structural classes are supported through
this explicit backend choice; ordinary equality SQL admission is unchanged.

```cpp
namespace pf = crown::planner::fallback;
namespace rf = crown::runtime::fallback;
auto plan = pf::admit(catalog, query); // Original classical public IR.
rf::Runtime owner(plan);             // Initially empty physical sources.
auto epoch = owner.apply(update);    // Contiguous physical set-update sequence.
auto current = owner.snapshot();
auto explanation = owner.explain();
```

Variables, constants, ignored columns, repeated variables, self-join aliases,
disconnected components and ordered/repeated output variables retain their
classical meanings. A true empty-body query yields one empty tuple; a
contradiction yields none. Boolean queries stop after their first witness.
Int64, binary strings, Boolean, finite Date and bounded exact Decimal values use
the existing typed scalar semantics. SQL NULL and bag-result semantics remain
outside this interface.

`Plan::source_only()` is a genuine empty-body physical plan over the full
original catalog, including unused sources, constraints and backend options.
Its identity and tree belong to source coordination. They are not an
original-query CROWN tree or GHD certificate. `Binding::query()` retains the
actual original query separately; keep the Binding alive while borrowing its
views. `Binding::sources()` exposes the source-only compiled program.

## Evaluation and publication

One PhysicalRuntime enforces original full-row set identity and UNIQUE/FK
constraints. A changed source used by the original query triggers full
recomputation from a private [accounted source after-image](source_images.md).
Duplicate insertions, absent deletions, unused-source updates and contradictions
preserve the committed answer without a join recomputation. Inputs still advance
the source sequence according to the ordinary physical update contract.

An iterative nested-loop evaluator matches every original atom and term. A
binding trail restores variables when backtracking; execution does not recurse
with query depth. Projection follows complete matching, then an ordered funded
DISTINCT set produces sorted native answers. Multiple witnesses contribute one
projected answer; only the last witness's removal retracts it.

The owner prepares the complete result, owning endpoint delta handles and exact
old/new set differences before committing the source token. Source commit and a
same-allocator result swap publish the prepared epoch without allocation. One
busy guard spans preparation, publication and retirement of old state. Native
RAII and the existing physical token unwind a refusal; there is no second source
owner or source rollback journal.

`Epoch::input` describes the physical/support epoch, not the query answer delta.
`added` and `removed` contain exact projected endpoint set differences.
Snapshot and delta payloads retain the original query account and survive owner
teardown. `snapshot()` copies owning answer handles without source enumeration
or a reader lease. `source_snapshot()` explicitly exports an ordinary full-source
Database for caller diagnostics; that export is outside retained native state.
Calls on one owner require external serialization.

## Limits, observations and costs

`Options::sources` retains existing physical/storage limits. `recompute.work` is
one balance for metadata freezing plus initial answers during construction, and
one balance per later apply. Source capture receives only its remaining work.
Row/term/equality/scalar-byte visits, projection, ordered deduplication, answer
materialization and endpoint merging spend that balance. `source_rows` bounds
all physical rows in a private image; `rows` bounds distinct retained answers,
not witness count. Snapshot copying has its own explicit Limits. Resource or
row/work refusal preserves committed sources, results and sequence.

`Plan::estimates(table_counts)` counts each physical source once and repeats
Cartesian factors for query aliases. Its optional bounds describe source rows,
assignments, output rows and committed logical state rows. They exclude image,
journal and simultaneous old/new scratch space, so they are not peak-byte
estimates. `overflow` records unavailable integer bounds; zero factors still
make the complete assignment product zero.

`Runtime::explain()` reports the actual structural profile, committed source
cardinalities, actual result rows and native account statistics. Its optional
`witness_product` and `prefix_product_sum` are advisory Cartesian bounds;
`nullopt` means overflow. A later empty atom can make the complete product zero
while earlier prefixes remain large or overflow. Metrics record actual selected
work categories, not elapsed time or hardware instructions.

An update pays ordinary full-source validation/maintenance, complete source
capture and nested-loop prefix matching, then DISTINCT comparisons, native
output materialization and endpoint merging. Scalar widths matter. Memory can
hold old answers, source images, distinct candidates, new answers and deltas at
once. Owning snapshots and final-owner cleanup retain their real costs. No
constant startup, delay, termination or specialized GHD/update bound is claimed.

The algorithm here is the conservative evaluator requested by
[Refactor X06](../Refactor.md), implemented as local engineering. The CROWN
paper's admitted structural scope and support propagation are described in
[the review guide](code_review.md); they do not establish a guarantee for this
fallback. SQL grammar expansion, automatic backend choice, approximation,
shared-query state and parallel/distributed execution remain deferred.
