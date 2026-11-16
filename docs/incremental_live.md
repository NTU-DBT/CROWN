# Incremental live maintenance: D05 implementation work

Status: this component is implemented and verified. All 59 tests pass GCC
Debug/Release, ASan/UBSan, Clang18 and a fresh source-only Release build, with
independent source/proof review; see the
[verification packet](verification/incremental-live-2026-11-06.md).
That packet is the historical component checkpoint. D05 now also includes
[anchored completions](anchored_delta.md) and verified
[ordered replay](ordered_delta.md), with productive queues, child-side live
indexes and a qualified first/next/last runtime profile. All 66 tests pass
the current [lifecycle matrix](verification/delta-lifecycle-2026-11-06.md). No constant
public startup claim is made for eager atomic spooling.

The canonical reference policies below use the same E-key partition and
core/SQL output mapping. Default ordered replay refines the visitation order;
its single-key mixed-state coupling and deletion proof are in
[ordered_delta.md](ordered_delta.md).
`LiveMaintenance::on_output` updates L while processing each accepted core
delta row. `incremental` drains affected child buckets before enumeration;
`eager` retains the D04 full-rebuild reference path. Full E scans remain in
delta-mode bootstrap and explicit invariant checking, with their costs recorded.

## Maintained state

Use the [D03 notation](delta_transition_spec.md): E_i has complete visible
schema X_i; L_i is its globally live subset. For each nonroot factor i with
parent p and separator Y_i, retain a separate exact live-parent support map:

```text
P_i[y] = number of l in L_p with projection_Y_i(l) = y
L_root = E_root
L_i = { e in E_i : P_i[projection_Y_i(e)] > 0 }
```

Zero-count entries are absent. The count denotes distinct live parent keys,
not physical derivations, local survivors, E projection supports or answer
multiplicity. Parent rows sharing a separator therefore preserve child
liveness until the last such row disappears. Bootstrap constructs these maps
while performing the D03 top-down semijoins.

The later [anchored component](anchored_delta.md) enriches these maps with
enumerable full parent keys and matching count/index invariants. It records
their copied fields, affected undo, stage cleanup and retained index rows;
the recurrence and live-coupling proof below are unchanged.

## One drained route: row-coupled maintenance

The support journal supplies only actual E membership crossings C_i with the
route's sign. All E tables already describe the drained after-prefix. The
before-prefix view restores only this stage's interval while retaining the
cumulative storage writers/pins.

The `on_output` policy performs no initial L rebuild or live-event drain.
Changed keys are visited in parent-before-child factor order with the D03
earliest-changed-factor ownership test. Insertion eligibility checks the
root or the current positive parent-separator support. Deletion eligibility
uses current L union this stage's removed keys, reconstructing L-before.
Completions read E-after for insertion and E-before for deletion.

For each accepted core delta row, before SQL mapping/spooling:

1. Visit all factors in parent-before-child order and project their full keys.
2. On insertion, add any absent projected L key. On deletion, remove a
   present key if its own E-after membership is absent or its current parent
   support is zero. Since this row comes from E-before, the first condition
   is exactly membership in that factor's changed-key set.
3. Immediately apply each actual L crossing to its children's separator
   counts, before examining any descendant projection. Do not open E buckets.

The root has no parent-support condition. Each deletion retains an affected
key in the stage's removed set; repeated projections make no second change.
All accepted **core** rows run this procedure, including scalar SQL EXISTS
whose public replacement records are prepared separately. No additional
answer relation or output deduplication set is retained.

### Insertion argument

Throughout insertion, current L is a subset of exact L-after: inserted
projections come from actual new answers. Before a changed witness in factor
i is tested, every ancestor's L and the corresponding parent support are
already exact after-state values. Prove this along factor order. A newly live
ancestor key either changes its own E membership or gains a live parent;
following this recurrence reaches a changed E key on its ancestor path.
Every after-answer containing that newly live key therefore has an owner
rank no later than that ancestor. Its accepted row has already been processed
before rank i, and has installed the ancestor projection and its support.
Unchanged live ancestor keys were present initially. Thus the eligibility
test is exact, with no circular dependence on the witness's own L insertion.

Every newly live key projects from at least one new answer. Exact D03
enumeration accepts that answer once, so all such keys are inserted by route
end. Projecting accepted rows cannot add a key outside L-after.

### Deletion argument

At all times, L-after is a subset of current L, which is a subset of
L-before. Removing a key absent from E-after is safe. Otherwise removal at
zero current parent support is safe because current parent L still contains
all of L-after. Parent counts are exact for the current tentative sets after
each immediate count update. Current L union stage-removed keys is always
exactly L-before, so witness eligibility and canonical ownership do not depend
on which previous answers have already been processed.

Completeness needs more than merely seeing each dead key once: an early
answer may see it while another parent still has support. Use this removal
certificate. Whenever an L key is removed while processing row a, there is a
consistent binding B on a connected ancestor path ending in that full key,
containing an E key absent after, such that no accepted row before this
removal matched B.

- If its own E key is absent after, take B to be that key. The first accepted
  row containing it removes it, so no earlier accepted row matched B.
- Otherwise its parent support is zero. Select the last matching parent key
  removed. Extend that parent's certificate with this child's full key.
  Running intersection makes the binding consistent. Start with a before
  completion of the parent certificate and replace the selected child branch
  with a subtree completion of this child key; downward totality provides
  that subtree and running intersection preserves the other branches.
  Before the parent's removal
  no row matched its certificate. Between that removal and the child's
  removal, a matching row would already have removed this child at zero
  support. The parent-before-child visit order includes the case where both
  removals occur on the same row. Thus the extended certificate has the
  required freshness property and still contains an after-absent E key.

Now induct on depth for any key in L-before minus L-after. If its own E key
is absent after, some deleted before-answer contains it and its first such
accepted row removes it. Otherwise all matching before-live parent keys must
be absent from L-after, and by induction all are eventually removed. Extend
the certificate of the last such removal with the child's key. A before
completion exists and is a deleted answer because the certificate contains
an after-absent E key. Its accepted row cannot precede that last parent
removal. When this row visits the child, the support is zero, so the child
is removed if it has not already been removed. This proves exact final L,
independent of the within-owner answer order.

These arguments use the drained monotone E endpoints, tree/running-intersection
and downward-totality assumptions from D03, and complete duplicate-free D03
delta enumeration. They establish this implementation's live coupling, not
the completion cursor's delay. The coupling is consistent with the live-view
approach in [P1, section 5.2](https://arxiv.org/pdf/2301.04003v2); the D03 E-key
partition and the above deletion certificate are the local proof obligations.

## Bucket policy

1. Seed every changed E key in factor order. An insertion adds it to L if it
   is the root or its parent support is positive. A deletion removes it from
   L if present. Actual membership changes enqueue one signed live event.
2. Drain the live events iteratively. For each changed parent L row, adjust
   the support of its separator in each child. Positive-to-positive changes
   do not scan the child.
3. On support 0→1, visit just that child E **after** bucket and add its keys
   to child L. On 1→0, visit just its E **before** bucket and remove the keys.
   Only a real L crossing enqueues another event; an already seeded key is a
   no-op. Continue until no live event remains.
4. Enumerate the unchanged D03 ownership partition. Insertion eligibility uses
   the final L. Deletion eligibility uses final L union this stage's removed
   L keys, which reconstructs precisely the preceding prefix's membership.
   Completions still read the corresponding E before/after context.

The stage's removed-key sets own affected values only and are destroyed before
the next alias. The transaction retains extracted L/count nodes and scalar undo
until the whole physical epoch commits or aborts.

### Bucket correctness argument

At route start the preceding L/P state satisfies the recurrence. All E changes
and all resulting global L changes have one sign. During draining, a pending
parent event is a signed contribution not yet applied to its child's count:

```text
stored P_i[y] = current parent-L count at y
                - sum of pending parent event signs at y
```

Processing that event preserves the equation. No duplicate membership change
can contribute twice: the L set is checked before mutation/enqueue. At queue
exhaustion P again equals the exact parent-L projection count.

For a child key whose own E membership changes, seeding handles the change if
its parent separator already has support. Insertion deferred at zero support
is handled if/when that support crosses to positive. For unchanged E keys,
eligibility can change only at that parent-support crossing. The corresponding
indexed bucket visits every such key. Multiple parent rows on one separator
cause only one threshold crossing, so no other row affects eligibility.
Deletion uses E-before so removed E rows remain available for the inverse
transition and descendant support effects.

Induct from the root down the factor tree. Root L follows E exactly. Assuming
the parent's final L is correct, its drained support counts are exact and the
seed/crossing rules produce precisely the child's semijoin. Thus every final
L is the D03 global-answer projection. Directed child propagation terminates;
each key changes at most once under the same sign. The partition's target E,
full witness binding and earliest-owner test are unchanged. Deletion's removed
keys are stage-local, so they restore the immediately preceding alias context
without reviving rows already removed by an earlier route.

## Atomicity and storage

Both non-eager policies use tentative in-place L/count mutation behind the delta
owner's busy barrier, matching the kernel's journaled transaction model. It
does not clone the committed image. Undo is prepared before each mutation:
insert undo retains an iterator; erasure extracts the existing node; count
changes retain its prior value. Same-sign monotonicity prevents an inserted
node from subsequently being extracted in the same epoch. On deletion, reverse
undo reinserts a later-extracted count node before restoring earlier saved
value pointers into that node. Ordinary owning snapshots remain independent.

Output/live/view failures unwind stage cursors first, then the physical token
restores kernel/count/source state. Live undo restores its own independent
sets/maps before the delta owner becomes readable again. Rollback uses node
insertion, iterator erasure and scalar restoration without allocation. After
all throwing output work succeeds, physical publication and live undo commit
perform no allocating work. The live sequence tag advances only at that barrier.

Cache state uses local L memberships and separator keys. Additional epoch
storage is affected undo/events plus stage-local removed keys, not a full L
copy. Deleted nodes remain owned by undo until publication/abort; pending
events refer to stable inserted/extracted rows. The eager policy retains its
separate committed/old/new images and original scan/copy costs.

## Cost claim for this component

For one route let K=Σ|C_i|, J be actual L membership changes, B be rows visited
by the threshold-triggered child buckets and U be child-separator count
updates. Let D be the exact core answer difference and m the number of factors.

Each changed L key is a projection of at least one difference assignment, so
J≤mD. A threshold bucket contains only keys live on the selected side: on
insertion it had no live parent before and now has one; on erasure it loses
its last live parent. Every visited key is therefore in that child's L
difference, even if direct E seeding already removed it. Each child key has
one separator and each support key crosses at most once. Hence B≤J. Finally
U is the sum of child degrees over changed parent rows, so U≤(m−1)J.
More tightly, each individual factor has at most D changed L keys. Weighting
these by its child degree gives U≤(m−1)D for a nonempty tree (zero for no
factors). The oracle suite checks the exact degree-weighted count and both
the factor/edge bounds against the physical epoch's exact core difference.

The bucket live component performs O(K+J+B+U) set/map/queue actions plus
their projection/copy widths. With D=0 it makes no live mutation and opens no
threshold bucket; changed dead E keys still cost discovery/eligibility work.
Journal scans and patch-index construction remain additional O(M) preparation
with fixed-query index/width factors. Ordered dictionary operations include
their logarithmic, value-comparison costs; allocations and owned payload
widths are real costs. The bucket policy may drain all J changes before the
first candidate; its total bound is not a first-output bound.

For `on_output`, B=0. Each accepted row visits m factor projections and makes
at most one mutation per factor; its immediate separator updates total at
most m−1. Therefore its live component takes O(mD+J+U) map/projection/undo
actions with explicit field widths. It does no output-sensitive L work before
the first accepted core row. Each accepted row still incurs fixed-query
projection/lookups even if it introduces no further L changes. This does not
bound E-change discovery, journal/index construction, the reference root-first
walk, canonical-rejection delay or atomic public spooling of all D rows.

`live_changes`, `live_inserts`, `live_erases`, `live_separator_updates`,
`live_separator_crossings`, `live_bucket_opens`, `live_bucket_rows`,
`live_probes` and `live_journal_entries` record these actions. The event vector
in the bucket policy retains processed pointer slots until the stage finishes;
in the row-coupled policy it is cleared after each projected key's immediate
count updates. `live_queue_peak` records that retained slot high-water mark.
`e_rows_scanned` and
`parent_live_rows` measure full rebuild/bootstrap scans, not these bucket visits.
`peak_live_rows` also charges extracted old keys and stage removed-key copies;
separator-map and journal metadata have separate width/allocation costs.

The original root-first comparison for R(a,x)→S(x,z) cost 21→273 result
units at N=1→64, despite unchanged live actions. The later verified
[anchored component](anchored_delta.md) replaces that default scan: the
original-head fixture now stays 13→13. Its independent repeated-head insert/
erase fixture records flat 5/14/4 and 5/15/5 startup/result/termination units.
The root-first strategy remains available as a comparison.

## Ordered replay refinement

The canonical anchor component and its earlier residual-scheduler investigation
are historical. Default [ordered E replay](ordered_delta.md) is now implemented
and verified in the [64-test packet](verification/ordered-delta-2026-11-06.md).
Bottom-up insertion/top-down deletion preserve intermediate downward totality.
Endpoint E serves the anchor's original subtree; current parent/child live
indexes serve its unchanged outside context. Productive queues remove dead
witness tails, and each single-key crossing owns all its rows without canonical
rejection. Its deletion predicate is restricted to the current anchor, with
the freshness argument applied to that mixed single-key transition.

The replay argument adds exact child-index undo/space counters and accounts
for preparation, bounded first/next/last production and separate finalization.
The phase numbers earlier on this page refer to their historical fixture
snapshot; current canonical termination also charges frame closure.
Public atomic startup still includes the whole spool. Verified
[D06 lifecycle](delta_lifecycle.md) adds retained pause/resume and required
draining; operational delivery/recovery remain O work.
