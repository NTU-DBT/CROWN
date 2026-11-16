# Anchored delta completion: D05 component

Status: this component is implemented and independently reviewed. All 61 tests
pass GCC Debug/Release, ASan/UBSan, Clang18 and a fresh source-only Release
build; see the [packet](verification/anchored-delta-2026-11-06.md).
This is the historical component checkpoint. D05 now also includes verified
[ordered replay](ordered_delta.md) for bounded internal accepted-output
production and the runtime guarantee profile; its current
[66-test lifecycle packet](verification/delta-lifecycle-2026-11-06.md)
supersedes this component's matrix. The preceding verified
checkpoint is [live maintenance](verification/incremental-live-2026-11-06.md).

`DeltaCompletion::automatic` selects ordered replay with row-coupled live
maintenance and `anchored` with the eager/bucket comparison policies.
Explicit `anchored` and `root_first` retain the canonical comparison paths.
This is a delta-specific
full-E-key cursor; general D02 partial/hidden `completions` keeps its existing
semantics and cost qualifications. Serialized physical plans are unchanged.

## Traversal and assumptions

Use the drained E tree, running intersection, downward totality and exact
ownership partition from [D03](delta_transition_spec.md). Changed keys remain
true visible E membership crossings, in fixed factor/key order. Eligibility
and core/SQL mapping are unchanged from [live maintenance](incremental_live.md).

For each live changed full key at factor i, derive an iterative traversal of
the undirected C* tree rooted at i. The anchor is a fixed typed tuple. Only
the path from i to the original root reverses direction:

| Traversal edge | Source of matching complete keys |
| --- | --- |
| Original parent→child | Target E child's compiled separator bucket |
| Original child→parent | Target live-parent keys indexed by this child's separator |

Insertion reads E-after. At factor i, all strict ancestors already equal
L-after by the live-coupling frontier argument: newly live ancestors have a
changed E cause at an earlier rank, whose accepted answers have finished.
Their parent-key buckets remain complete and stable during this witness.
Deletion reads E-before and the exact stage L-before parent index view below.
Eager/bucket comparison policies supply their equivalent endpoint images.

Every selected partial assignment extends. The anchor is globally live.
A downward choice matches a live parent's separator and has a subtree
completion by downward totality. An upward choice is a globally live parent
key matching the selected child. Running intersection permits replacing its
chosen child branch without changing the outside completion. Induct over
the rerooted tree. Edge matches also propagate every anchor variable wherever
it occurs; no additional fixed-binding rejection is needed.

Thus every newly opened bucket has a first row. After a complete assignment,
one backward carry exhausts at most m−1 frames and opens at most m−1 suffix
frames, each nonempty on its first selection. Original `enumeration.output`
slots assemble the ordered/repeated core head through the reroot-position
map. Nullary anchors, empty separators and a one-factor Boolean query follow
the same product rules. There is no answer-history deduplication set.

## Enumerable parent state and stable deletion

For each child c and its separator y, retain:

```text
P_c[y].rows  = distinct complete L_parent(c) keys projecting to y
P_c[y].value = |P_c[y].rows|
```

Bootstrap copies one parent key per outgoing edge. Every actual parent L
crossing changes one such index entry per child, preserving the count. The
index contains local complete keys, not answer assignments.

During one deletion route, copy each removed parent index key into that
stage's `removed_parents[c][y]` before extraction. At every cursor advance:

```text
stage-before bucket = current P_c[y].rows union removed_parents[c][y]
```

This union is invariant and the sets are disjoint between callbacks. The
upward frame owns its separator and last selected typed tuple. Each next
operation finds both buckets afresh, takes `upper_bound(last_key)` in each,
and copies the smaller successor. It retains no iterator or reference across
the callback that may extract the selected key or the whole separator bucket.
A key moving from current to removed therefore cannot disappear, duplicate
or move relative to the strictly increasing last key.

Stage scratch is cleared only after all witness cursors close. Earlier
aliases' removed rows never reappear in a later stage. Ordinary source/E
views retain the cumulative journal and existing D02 lease/rollback rules.
Downward cursors read immutable drained E while L changes. Insertion's after
view uses live E; deletion's before view has only restored E memberships, not
excluded E rows. Thus these bucket walks do not hide an unrelated excluded-row
tail. This qualification is specific to monotone delta routes, not arbitrary
mixed or partial view queries.

## Failure and retention

One prepared separator undo entry covers its count and parent-row membership:

- A new outer separator node is journal-owned before its inner row allocation.
- A positive insertion saves the inner iterator and previous scalar count.
- A positive erasure extracts the inner node and saves the previous scalar.
- Last-parent erasure extracts the entire outer node with its final row intact.

The previous count is a scalar, never a copy of the row bucket. Reverse undo
reinserts later-extracted outer nodes before using earlier saved mapped-value
addresses or reinserting inner nodes. Same-sign monotonicity prevents an
inserted node from subsequently being erased in the epoch. Comparisons over
the admitted scalar domain allocate nothing; node reinsertion/iterator erase
and scalar restoration require no allocation. Persistent fault sweeps verify
the whole physical/support/L/index state through `check_invariants` and retry.

Cursor/key/layout/allocation, work and spool failures unwind all E readers
before physical undo, then restore L/index state before public readiness.
`end_stage` charges and frees all stage parent copies, including the final
stage, before publication. This O(U) cleanup and whole-epoch undo teardown are
real additional work; candidate termination does not make them constant.

Let R=Σ edges |L_parent|. Current indexes own R full parent keys plus separator
keys. Non-eager extra index retention is extracted old entries and stage-local
removed copies, each bounded by affected edge changes U. Eager mode retains
its committed/needed old/new index images. `parent_index_rows` measures R;
`peak_parent_index_rows` includes extracted entries and stage copies, or eager
retained images. Row payload widths, map/set nodes and allocator metadata are
additional byte costs. No-op epochs still report current index rows. Cursor
frames own O(m) selected tuples/keys plus nested fixed-query cursor metadata.

## Work and remaining obligations

`anchor_steps`, `anchor_bucket_opens`, `anchor_parent_lookups`,
`anchor_parent_rows`, `anchor_down_work`, `anchor_down_rows` and `anchor_fields`
charge traversal actions. Anchored startup/result/termination counters classify
these already charged actions; they do not charge them twice. The aggregate
delta work cap and the cursor-wide cap both apply, alongside nested E cursor
and view caps. `CursorWork::descriptor_steps` charges each inspected compiled
descriptor in a visible-bucket constructor.
`anchor_cursors` counts live witness owners; separate maximum startup/result/
termination work fields record the largest individual candidate action in
each phase, in addition to the aggregate cursor-phase work.

Candidate startup/advance/termination use O(m) indexed/cursor actions, with
query-dependent descriptor/layout construction and explicit scalar widths.
A suffix can perform O(m²) descriptor checks across its bucket constructors;
those checks are now recorded. Ordered lookups/successors retain their
logarithmic/value-comparison costs. This is a fixed-query, data-independent
number of indexed actions per candidate, not a literal constant wall-time
guarantee for the ordered backend.

Parent-index update/copy/field counters reconcile with U, the degree-weighted
number of actual L changes. Per-stage cleanup charges U on erasure and zero
on insertion. Bootstrap/invariant rebuilds retain their full scan/copy costs.
Changed-key discovery K, journal/view preparation M and dead witnesses remain
additional work, including when the true delta is empty.

Canonical ownership still filters candidates after completion. Although
T≤mD, D accepted rows can be followed by D rejected copies; local exclusion
alone can create empty partial subtrees. Bounded **accepted-output** gaps and
termination are not bounded by this canonical component. Verified
[ordered replay](ordered_delta.md) removes those gaps with productive queues
and exact current child-side live indexes. The
public artifact still spools all output atomically, so public first-row latency
includes the whole preparation. The separate verified
[D06 lifecycle](delta_lifecycle.md) adds pause/resume/draining. O06 local
delivery and set-session retirement are verified; release gates remain open.

## Ordered replay refinement

The earlier ordered E replay proposal is now implemented and independently
reviewed; see [ordered_delta.md](ordered_delta.md) for its mixed-state proof,
productive queues, child-side index, anchor-specific deletion and complete
preparation/production/finalization ledger. Its
[64-test matrix](verification/ordered-delta-2026-11-06.md) preserves the canonical
anchor/root-first comparison paths. The canonical component's accepted-output
gaps are not attributed to replay. D05 is verified for that qualified internal
producer contract. Verified [D06 lifecycle](delta_lifecycle.md) supplies
retained ownership and draining. O06 has separate verified local-delivery and
set-session-retirement acceptance; release gates remain open.
