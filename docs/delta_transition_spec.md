# Projected delta transition specification (D03)

Status: D03 is verified. The conditional proof and independent internal review
are complete; its 50-test checkpoint passed GCC Debug/Release, ASan/UBSan,
Clang18 and a fresh source-only Release build. See the
[D03 packet](verification/delta-spec-2026-11-06.md). The
[D04 runtime](delta_runtime.md) implements this partition and passed
53 tests across the same matrix at that checkpoint. Verified D05
[ordered E replay](ordered_delta.md) refines this partition with productive
queues, exact live-parent/child indexes and qualified internal first/next/last
production bounds; its [64-test packet](verification/ordered-delta-2026-11-06.md)
preserves the D04 oracle traces. Canonical
[anchored traversal](anchored_delta.md) remains a comparison component.
This page specifies the proof/protocol; session, recovery and sink lifecycle
are separately implemented and component-verified O cards.
The target requirements are Refactor.md §§6.5 and 7.3–7.6 and card D03.
Verified [D06 lifecycle](delta_lifecycle.md) supplies pause/resume, required
internal draining and recovery boundaries. The full implementation goal and
full-release reviews remain open.

The research pin is [P1, corrected arXiv v2, §5.2](https://arxiv.org/pdf/2301.04003v2).
That section defines live views as global-answer projections and couples
their maintenance to enumeration. The partition below is independently
derived from set joins. It does not assume that projection commutes with a
delta or inherit Algorithm 6's delay bounds. The legacy local PDF is not
substituted for the explicitly versioned primary source.

Code evidence is the test-only [model](../tests/reference/delta_model.hpp),
its [implementation](../tests/reference/delta_model.cpp), and
[oracle cases](../tests/unit/delta_spec_test.cpp). The model materializes
subtree assignments for small inputs; the maintained executor must not do so.
Existing [D02 cursors](epoch_views.md) and [support invariants](support_invariants.md)
are prerequisites, not an existing implementation of this specification.

## State and assumptions

A physical epoch has sequence `n+1` and deterministic occurrence routes
`1..r`. Prefix `j` means exactly the first `j` routes have completed, including
their internal delta work. A filtered route or a derivation count that does
not cross zero is a no-change route. Duplicate physical inserts and absent
deletes have no changed routes. They still consume a valid sequence at commit.

For a changing route, the logical occurrence set changes by one insertion or
one erasure. Native support propagation drains completely before its delta
stage begins. Intermediate aliases are independent logical relations; their
prefix state need not correspond to any public physical database. Prefix 0
and prefix r do correspond to the physical before/after states. No prefix is
public. Drain route j before staging route j+1, as required by Refactor.md §7.6.

Fix one route and write `0`/`1` for its immediately preceding/following drained
prefix, not for the start/end of the whole physical epoch. Let `F` be the set
of free variables and choose the compiled parent-before-child C* order
`v_0..v_(m-1)`. Any fixed total order works for the partition; the chosen order
must remain fixed throughout the route. A node ID is not its rank.

| Symbol | Meaning |
| --- | --- |
| `X_i` | Sorted `scope(v_i) ∩ F`, the complete E-key schema, including an empty schema when appropriate. |
| `E_i^s` | Set of visible keys at prefix s, `π_(X_i) S_(v_i)^s`, maintained by exact support counts. |
| `A^s` | Full assignments to F in `⋈_i E_i^s`. |
| `h(a)` | Core output in its original ordered/repeated head schema. Every variable of F occurs, so h is injective. |
| `L_i^s` | Globally live keys, `π_(X_i) A^s`. |
| `C_i` | Actual changed E memberships: `E_i^1 \ E_i^0` on insertion, `E_i^0 \ E_i^1` on erasure. |

The R01–R04/D01 invariants establish that `h(A^s)` equals the core query
answer. E schemas cover F and satisfy running intersection on the C* tree.
They also satisfy downward totality: every parent E row has a compatible E
row in each C* child. A survivor has a witness in every child; on a C* edge
the separator is contained in F and survives projection. Thus the separator
key is determined by the parent's E row; the child's complete E key can still
contain additional variables and is bound separately. Outside-C* subtrees are already represented
by survivor existence. These facts hold at drained boundaries, not at arbitrary
microsteps in the propagation queue.

All accepted route changes have the physical event's single polarity.
Positive CQ joins, projection and existence support are monotone. Therefore
all E memberships and A grow on insertion and shrink on erasure, even when
some numeric support counts change without a membership crossing. No-op,
count-only and filtered routes have identical E sets. A mixed insert/delete
batch, replacement, parameter change or schema change is outside this contract.
The reference model rejects snapshots that violate the declared polarity.

## Live bootstrap and cache meaning

At either drained prefix, construct live sets without enumerating A:

```text
L_root := E_root
for each parent p -> child v in C* order:
    L_v := { e in E_v : e matches some key in L_p on their separator }
```

Root E rows have complete subtree witnesses, so all are globally live. If a
child row matches a live parent row, it has a descendant witness by downward
totality. Other child subtrees can be completed independently after fixing the
parent's variables, by running intersection. It therefore extends globally.
Conversely, every global assignment supplies that matching parent row. This
proves by induction that the recurrence equals `π_(X_v) A` at every node.
It is not valid for arbitrary unreduced factor sets; the model checks downward
totality and rejects that misuse.

The semijoin tests remaining parent support. Removing one live parent row
does not remove a child key while another parent row shares that separator.
Rebuilding a separator-key set handles this directly; an optimized maintained
index must preserve the same existence condition.

Maintenance-only mode has no required L cache. Entering delta mode requires a
quiescent writer-ready barrier at committed sequence n, with no outstanding
query cursor/view or output owner, and a successful bootstrap tagged
with that sequence. Failure leaves maintenance-only mode unchanged. An optional
initial result snapshot has its own output cost; bootstrap does not enumerate
it. Leaving delta mode also requires a quiescent barrier.

Maintenance-only epochs use the existing support/count/source drain without
delta enumeration. A retained but unused L image is absent or explicitly
invalidated as maintenance updates advance the sequence. Re-entering delta
mode bootstraps the current committed state; it never silently reuses a stale
cache from an earlier mode period.

The first D04 baseline may rebuild all working L sets privately after each
drained occurrence stage, using E scans and temporary separator indexes. Keep
the committed L image unchanged throughout the physical epoch; replace the
working image as prefixes finish. Retain only the prefix images needed by
the current stage, plus the committed image for whole-epoch rollback. This is
an explicitly charged eager-live baseline, not the final D05 schedule.

The current non-eager refinement journals tentative L/count mutations behind
the public busy barrier instead of retaining a full committed rollback copy.
Its bucket policy establishes L-after before enumeration. Its row-coupled
policy interleaves live maintenance with accepted core rows while preserving
the abstract side eligibility: insertion uses already-completed ancestor
support, and deletion uses current L union stage-local removed keys. The
[refinement argument](incremental_live.md) proves exact endpoint L, insertion
eligibility and deletion completeness; it leaves the partition unchanged.

An unchanged root does not imply an empty delta below it. An unchanged answer
does imply unchanged L memberships, since L is its projection; the engine must
still complete the work that establishes that fact and advance its valid
prefix/version tag. Do not bypass internal completion merely because nothing
has been delivered.

## Route algorithm

The following procedure applies after propagation for one route has drained.
Every cursor and live image has an owner, plan identity, physical epoch and
prefix tag. Both snapshot contexts remain immutable until this route finishes.

1. Capture the route's before/after E membership boundary. Derive C from true
   zero crossings, consolidated by node/key. Positive-to-positive count records
   and raw S changes do not create C entries. Use always-retained journal
   records or endpoint membership tests, not the optional transition trace.
2. Produce/validate working `L^1`; retain the preceding `L^0`. No public live
   state changes yet. A certified no-change route can reuse its L memberships
   while advancing the private prefix tag.
3. Choose context `E^1`, eligibility `L^1`, and output sign `+` for insertion.
   Choose context `E^0`, eligibility `L^0`, and sign `-` for erasure.
4. For increasing factor rank i, visit each `e ∈ C_i`. If `e ∉ L_i` on the
   chosen side, skip it. Otherwise open a whole-query projected completion
   cursor that fixes **all variables in X_i to e**, including variables beyond
   the parent separator. The empty root separator is not the witness binding.
5. For each candidate assignment a, test earlier factors. Emit `h(a)` exactly
   when `a[X_k] ∉ C_k` for every `k < i`. Append an owning signed record to the
   unpublished epoch spool or prepared transactional output participant. A
   rejected candidate does not change L or the public output.
6. Exhaust every internal cursor, including when delivery is discarded. Close
   all copied stage views and cursor references before advancing to route j+1.
   Its support state and working L must both describe prefix j. Keep the whole
   physical transaction unpublished.

```text
target := after if inserting else before
eligible := L_after if inserting else L_before
for i in rank order:
    for e in C[i]:
        if e not in eligible[i]: continue
        for a in completions(target, FULL_E_KEY_BINDING(i, e)):
            if all(a[X[k]] not in C[k] for k < i):
                append_unpublished(sign, h(a), stage=j, owner=(i,e))
```

No emitted-output deduplication dictionary is used. C and L are local factor
sets, not materialized full answers. Value keys are typed and node/role scoped;
different aliases with equal layouts never share membership sets.

The steps above describe abstract endpoint eligibility and the eager baseline.
A row-coupled implementation may refine steps 2–5 by the live-maintenance
argument above; it must still finish exact L-after before step 6 advances to
the next route. Its tentative sets are not advertised as an immutable L-after
image during enumeration.

## Partition proof

For an assignment a in the chosen target answer define
`changed(a) = { i : a[X_i] ∈ C_i }` and, when nonempty,
`owner(a) = min changed(a)`.

**Soundness.** An insertion candidate belongs to `A^1` and contains a key not
in its before E factor. It cannot belong to `A^0`. An erasure candidate belongs
to `A^0` and contains a key absent from its after E factor; it cannot belong to
`A^1`. Thus every candidate, accepted or rejected, is a true signed difference
assignment. In particular, surviving hidden witnesses do not cause a false
projected delta when C is empty.

**Completeness.** If `a ∈ A^1 \ A^0` on insertion, some before factor lacks its
projected key, so `changed(a)` is nonempty. The reverse argument holds for
`a ∈ A^0 \ A^1` on erasure. Let i be its owner. Because a is a target answer,
its key is in the target L_i. The cursor for that exact key enumerates a. No
earlier changed key occurs in a, so it is accepted. A prior changed key that
would reject a is also live (a itself is its completion), so eligibility
filtering cannot remove the true owner.

**Disjointness.** Within one factor, different E keys constrain different
assignments. The D02 completion cursor itself emits every projected assignment
once. Across factors, exactly one rank equals `owner(a)`; all others reject a.
Finally h is injective on F, including repeated/reordered core heads. Therefore
every output tuple is emitted exactly once without historical output state.

**Physical alias union.** For an insertion epoch,
`A^0 ⊆ A^1 ⊆ ... ⊆ A^r`; for erasure the inclusions reverse. Each route emits
its adjacent set difference. Those differences are pairwise disjoint and
telescope to the physical endpoint difference. Intermediate new–new alias
combinations are included in the first prefix that contains them. Their
ownership includes the route index as well as factor/key. Do not enumerate
every alias against the physical epoch's original before state.

## Required worked traces

1. **Projection collision.** For `Q(x): R(x,z)`, adding `(a,2)` while `(a,1)`
   exists changes S and the positive E support count, not E membership. All C
   sets are empty, so no delta is emitted. Erasing either witness while the
   other remains is also empty. Erasing the last witness emits `-a` once.
   If one child key activates two distinct `R(x,z,h)` rows sharing x, their
   visible support crosses from 0 to 2, still creating just one E-key witness.
2. **Empty root separator.** A one-atom full query with old rows `(a,b)` and
   `(c,d)` receives `(e,f)`. The root's C contains only `(e,f)` in schema `{x,y}`.
   Its parent separator is empty, but its completion binding is `{x=e,y=f}`.
   Exactly `(e,f)` is emitted, not all three after rows.
3. **Ancestor/child erasure.** For `R(a), S(a,b)` and `Q(x,y)`, erase `S(a,b)`.
   Both root E `{a}` and child E `{(a,b)}` disappear. Root rank 0 enumerates
   `(a,b)` in the before context and accepts it. Child rank 1 enumerates the
   same candidate but rejects it because its root key is in C_0. One erasure
   is emitted. Reading only after context would instead lose the row.
4. **Propagation stops below root.** Use `R(x,y), S(y,z), T(z,w)` with head
   `{x,y,z}`. Initially `R(a,1), S(1,10), T(10,u), T(20,u)`. Insert `S(1,20)`.
   Root E and its parent-support truth remain unchanged; S's E adds `(1,20)`.
   T's E already had 20, but its L now gains 20. The S-key completion emits
   `(a,1,20)`. Looking only at root changes, or updating L only for changed
   E keys at the same node, would miss required work.
5. **Unlive E change.** With R empty, insert `S(a,b)` in the ancestor/child
   query. Child E changes, but root L and child L are empty. The changed key is
   skipped and the delta is empty. Internal stage/version completion is still
   required. No partial cursor is left for the next route.
6. **Self-join new–new term.** For `E(x,z), E(z,y)` with full head `{x,z,y}`,
   start with edges `(a,b),(b,a)` and insert loop `(a,a)`. Route 1 inserts it
   into the first alias and emits `(a,a,b)`. Route 2 inserts it into the second
   alias and emits `(a,a,a)` and `(b,a,a)`. The loop combination appears once.
   Deletion in the same route order removes two rows at route 1 and the third
   at route 2; their union is exactly the reverse physical difference.

Boolean queries use nullary E keys and emit at most one core empty tuple.
Constant true/false routes have no changing factors and no input delta. Same-
scope aliases, disconnected products and filter/count-only routes obey the
same rules. These examples must pass both the model and an independent A04
before/after set-difference checker; correct final snapshots alone are not
acceptance evidence for delta emission.

## Lifecycle and publication state machine

This table is normative for D04/D06 integration. The current
[pending lifecycle implementation](delta_lifecycle.md) exposes these ownership
boundaries, with D05 row-coupled mixed-state replay refining the eager live-build
phase. Its [66-test verification](verification/delta-lifecycle-2026-11-06.md)
and independent acceptance review are complete. One state-mutating thread owns
the epoch. Public reads/writes cannot observe a tentative prefix.

| State | Required invariant / permitted next transition |
| --- | --- |
| `ready(maintenance,n)` | Kernel is committed at n; no delta L is required. Begin a maintenance epoch or enter delta mode through a successful bootstrap barrier. |
| `ready(delta,n)` | Committed L equals global E projections at n; no pending output. Starting a physical event creates a private working L/spool and enters `propagating`. |
| `propagating(n+1,j)` | Support/count/source changes are private. Finish native support propagation before reading stage E or advancing to `live_build`. |
| `live_build(n+1,j)` | Prepare/validate the route's live context and indexes. An eager reference builds L-after here; row-coupled replay finishes L during enumeration. Failure aborts the whole physical epoch. Completion enters `pending_delta`. |
| `pending_delta(n+1,j)` | Before/after stage views are pinned. L follows the in-progress coupling invariant; replay has exact mixed projections at fragment boundaries and exact endpoint L after the route finishes. Enumerate only this route into unpublished output. No next route/input is allowed. |
| `paused(n+1,j)` | Retain the same stage views, cursor position, witness rank and working state. Resume to `pending_delta`, explicitly discard to `draining`, or abort while unpublished. |
| `draining(n+1,j)` | Delivery is disabled, but finish all required stage work and subsequent routes. Dropping an ordinary result cursor is not a substitute for completing this state. |
| `epoch_prepared(n+1)` | Every route and internal cursor is finished, propagation queues are empty, working L describes the final prefix, and bounded output is prepared. Only now may publication begin. |
| `committed_output(n+1)` | Input/kernel/L are committed and the output artifact is public. Keep the artifact until consumed or discarded. A delivery error may resume/discard; it cannot roll back published input. |
| `ready(delta,n+1)` | Output ownership is finished; another input may start. The first session contract serializes inputs through this point. |

On an unpublished failure or explicit abort, close stage cursors/views first,
then roll back logical support, occurrence counts and physical source state.
Discard working L and unpublished output; committed L and sequence n remain
unchanged. Token destruction before publication chooses abort. Explicit
`discard` instead finishes internal work without delivery and advances the
accepted input after all routes succeed. A subscriber that discards changes
needs a new snapshot if it later wants a complete external result copy.

No publication step may throw after the kernel can no longer roll back.
For an in-memory prepared artifact this means preallocate all throwing work
and publish kernel/L/output under one owner barrier. A durable or external
sink requires a separately audited prepare/commit/recovery protocol in O06;
snapshot invisibility alone is not output atomicity. A spool must have a
bounded resident-memory budget with spill/backpressure or atomic resource-
limit rejection; an unbounded vector is not a production bounded-spool contract.

While output is committed but undelivered, kernel `ready()` alone is not the
session readiness condition. The higher-level delta owner must also check
this lifecycle. Maintenance/delta mode switches are forbidden while an epoch,
stage view, paused cursor or pending output is active. Bootstrap failure does
not partially install a live cache.

## D04 integration hooks

At the D03 checkpoint, `PendingEpoch::stage` drained support synchronously, but
`PendingEpoch::view(before)` reconstructs the **whole epoch's original** state
from its cumulative journal, not prefix j-1 for route j. `PhysicalRuntime`
prepared all alias routes before returning its pending token. That foundation
had no per-route delta observer, L cache or spool.

The [D04 implementation](delta_runtime.md) adds an internal checkpoint carrying
the journal-record interval,
preceding truth and prefix identity, plus owner-only E-factor iteration/key
lookup. A stage view must apply inverse patches only for its interval while
retaining the cumulative epoch journal for pins and active storage writers.
A sliced journal alone loses the writer used by tentative table cursors.
Keep the public D02 whole-epoch view semantics intact. Do not use a full
diagnostic support snapshot or enumerate the full answer to build L.

Invoke the delta-drain hook after each successful occurrence zero crossing
and before the next route. All copied views/active cursors must close before
staging resumes: the existing prefix lease rejects staging while held.
Route/spool/live-build failures must use the existing whole-epoch physical
rollback path. Output preparation belongs before `PendingUpdate::commit`;
that commit currently has no output participant and must not be treated as
an atomic sink commit. These source obligations are checked in the D04 runtime
checkpoint; they are not facilities established by the mathematical model.

## SQL output and event order

For admitted normalized DISTINCT output, every unfixed output-variable class
is retained in F. Reordering/repeating fields and adding constants is therefore
an injective map of core assignments: a difference in any F value appears at
some output position. Apply that map to each accepted signed core row.
Do not re-project raw S witness changes as a shortcut.

Scalar EXISTS always has one Boolean output row. If core truth changes, erase
the old Boolean row and insert the new one; otherwise emit nothing. Hence an
insertion input can have a negative SQL record, and an erasure can have a
positive SQL record. Monotonicity permits at most one truth flip in a same-sign
physical epoch, so alias staging does not duplicate this replacement. A source-
free constant output and scalar EXISTS are distinct cases.

These SQL mapping statements are analytical obligations here. The executable
delta model checks core CQ results; it does not execute a SQL delta-output
adapter. The separate D04 runtime suite now adds a mapped-output oracle,
including both signs of an EXISTS replacement; its evidence belongs to the
runtime checkpoint, not this reference model.

The proof concerns exact signed sets. Reference traces use fixed rank and
typed key order. A production ordinal is assigned only when accepting a
mapped output record. Recovery/idempotency must preserve the actual committed
spool or separately prove regeneration order; table IDs, ghost order and
propagation schedules are not automatically stable across rebuilds. Any
canonical sorting and durable buffering costs belong to O06's ledger.

## Complexity and retained-space ledger

Let `M` be affected journal records, `N_E=Σ|E_i|`, `K=Σ|C_i|`,
`D=|A^1\A^0|` on insertion or the reverse difference on erasure, and `m=|C*|`.
Let `H` count globally live changed keys, and `T` count all candidate completions
before rank rejection. Within one factor, a full assignment matches exactly
one key. Every live changed key has a difference assignment. Thus
`H ≤ m D` and `T ≤ m D`. Rank testing performs at most `m T` membership probes.
This bounds candidate duplication, not all cursor/maintenance work.

| Work / retention | Required accounting |
| --- | --- |
| Source adapters/counts/support | Existing R05/R01–R04 work, before/after pins and metadata undo; no full database rollback copy. Charge all aliases, including no-ops/filters as applicable. |
| C discovery and prefix patches | Scan M stage records, consolidate E zero crossings and retain typed local keys/pins. Ordered membership/container costs and value widths are additional. |
| Eager live rebuild | Scan E plus each needed parent L projection for each C* edge; build temporary separator membership indexes. Charge all scans, projections, ordered comparisons, copied L payloads and allocation, even when D=0. |
| Non-eager live maintenance | The [component argument](incremental_live.md) charges actual L changes/child-count updates, bucket rows for the bucket policy, and each accepted core row's projections for the row-coupled policy. Journal and removed-key storage remain explicit. |
| Live state | L is a subset of E per node. The eager baseline retains committed and needed old/new images; non-eager policies retain tentative sets, parent counts and affected undo/removed keys. Charge cache, key widths and journal space separately from kernel retention. |
| Witness discovery | Visit K changed keys, perform eligibility checks, start H live completion cursors. Dead keys cost work even though they emit nothing. |
| Candidate traversal | Charge the actual D02 startup/advance/termination work. Partial key walks/restored scans can inspect unrelated rows; T alone does not bound this cost. |
| Partition and mapping | At most mT earlier-key probes, then output width, SQL mapping and record ownership/serialization costs. No result-history deduplication table. |
| Spool/delivery | Output-sensitive storage/I/O, memory/disk caps, spill, consumer wait and abort cleanup. Public first-result latency in this eager baseline includes all private epoch preparation. |

Temporary ordered separator indexes can implement the bootstrap by scanning
each E child and the live parent once per edge, with explicit logarithmic key
costs. The slow model instead uses materialized joins and nested membership
tests; its counters certify finite traces, not the runtime bound. Larger
variable-width values, allocation/cleanup and comparisons remain real costs.
No O(1) first-result, per-result or termination-delay claim follows here.
This table describes the canonical partition/model baseline. Verified
[ordered replay](ordered_delta.md) supplies the D05 refinement: no canonical
rejections, bounded post-preparation first/next/last indexed actions, and
separately charged preparation/finalization. Verified [D06 lifecycle](delta_lifecycle.md) supplies cancellation/draining/
mode APIs; higher-level sessions and operational sinks remain O work.
