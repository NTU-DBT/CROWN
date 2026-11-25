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
contradiction yields none. Boolean queries keep one support count for the empty answer.
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
constraints. Answers are maintained incrementally (22 November 2026; this
replaced per-update full recomputation, which made every update cost a complete
nested-loop join). Planning fixes a prefix P: a minimal connected set of
occurrences that binds every head variable. The remaining occurrences split
into residual components that share no variable outside P; each component is a
persistent view counting its completions per value of its variables that also
occur in P. Every answer keeps a support count

    S(ans) = sum over P-assignments p projecting to ans of
             prod over views j of [V_j(key_j(p)) > 0]

and exists exactly while S(ans) > 0. Each used original table keeps its full
physical rows plus ordered/hashed indexes on the fields that the join plans
bind. A changed row first updates the views that use its table by anchored
enumeration of their new or removed completions. Keys whose view count crosses
zero then adjust the supports of the committed P-assignments that carry them
(earlier views use updated presence, later views committed presence), and
finally the P-assignments that use the changed row adjust their supports with
updated presence. A view count that stays positive costs nothing outside that
view; for example, a dumbbell projection only revisits its bridge edges when a
vertex gains its first or loses its last triangle. Self-joins count every
completion once: when occurrence k is bound to the changed row, earlier
occurrences of that table exclude it and later ones include it. Duplicate
insertions, absent deletions, unused-source updates and contradictions preserve
the committed answer without evaluation.

All fallible work (enumeration, support/view deltas, detached result/index/view
nodes and hash capacity) precedes the source commit. Source commit, counter
updates and node relinking then publish the prepared epoch without allocation.
One busy guard spans preparation, publication and retirement of old state.
Native RAII and the existing physical token unwind a refusal; there is no second
source owner or source rollback journal.

`Epoch::input` describes the physical/support epoch, not the query answer delta.
`added` and `removed` contain exact projected endpoint set differences.
Snapshot and delta payloads retain the original query account and survive owner
teardown. `snapshot()` copies owning answer handles without source enumeration
or a reader lease. `source_snapshot()` explicitly exports an ordinary full-source
Database for caller diagnostics; that export is outside retained native state.
Calls on one owner require external serialization.

## Limits, observations and costs

`Options::sources` retains existing physical/storage limits. `recompute.work` is
one balance for metadata freezing and planning during construction, and one
balance per later apply. Candidate-row/term/equality/scalar-byte visits,
projection, support and view deltas, answer materialization and node
preparation spend that balance. `source_rows` bounds all committed physical rows
after an evaluated update (refused as `source_image_row_limit`, as before);
`rows` bounds distinct retained answers, not supports or witnesses. Snapshot copying has its own explicit Limits. Resource or
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

An update pays ordinary full-source validation/maintenance, index and view
maintenance proportional to the completions that use the changed row, and
P-assignment work proportional to the supports that change (zero-crossing keys
and P-assignments using the row). Retained state is one copy of every used
table's rows, their join indexes, the view counts and the answers with their
supports. Owning snapshots and final-owner cleanup retain their real costs. No
constant startup, delay, termination or specialized GHD/update bound is claimed:
a P-assignment enumeration or a view's completion enumeration can still be large
for high-degree values.

The algorithm here is the conservative evaluator requested by
[Refactor X06](../Refactor.md), implemented as local engineering. The CROWN
paper's admitted structural scope and support propagation are described in
[the review guide](code_review.md); they do not establish a guarantee for this
fallback. SQL grammar expansion, automatic backend choice, approximation,
shared-query state and parallel/distributed execution remain deferred.
