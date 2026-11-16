# Ordered E replay and the runtime guarantee profile

Status: D05 is implemented and verified. Independent mathematical/source
review and all 64 tests pass GCC Debug/Release, ASan/UBSan, Clang18 and a
fresh source-only Release build; see the
[verification packet](verification/ordered-delta-2026-11-06.md).
This document is the D05 refinement of the
[D03 transition specification](delta_transition_spec.md). The preceding
[anchored checkpoint](verification/anchored-delta-2026-11-06.md) remains
historical evidence. Verified [D06 lifecycle](delta_lifecycle.md) retains this
producer across pause/resume and required draining; all 66 tests pass the
[current packet](verification/delta-lifecycle-2026-11-06.md).
O01–O08 are verified within their recorded scopes. The full 78-card
implementation goal and release gates remain open.

## Strategies and state

`DeltaCompletion::automatic` selects `ordered_replay` with row-coupled live
maintenance, and canonical `anchored` with the bucket/eager reference policies.
Explicit `ordered_replay` requires `LiveMaintenance::on_output`.
`DeltaRuntime::completion()` returns the resolved strategy; `options()` retains
the requested option. Canonical `anchored` and `root_first` remain comparison
paths and make no bounded accepted-output claim.

Use D03's factor schemas X_i, endpoint E_i^0/E_i^1, answer join A and complete
visible membership crossings C_i. All factor ranks are parent-before-child;
node IDs need not be ranks. Per physical occurrence, support propagation first
drains. The endpoints satisfy running intersection and downward totality.
Only actual E zero crossings enter C, independently of optional tracing.
No projection-of-witness-delta identity is used.

Source-free constant/contradictory plans without C* factors have no query
delta from source events and construct no replay cursor. Boolean/nullary
factors otherwise follow the same typed complete-key rules.

The cache retains exact global projections L and two kinds of live index:

```text
L_root = E_root
L_c = { e in E_c : some matching L_parent(c) key exists }
P_c[y].rows = complete L_parent(c) keys on separator y
B_c[y].rows = complete L_c keys on its parent separator y
bucket.value = number of distinct rows in that bucket
```

P and B own local complete keys, not full answer assignments. Root has no B
index. Bootstrap builds these sets by local E scans/top-down semijoins and is
checked against independent global-answer projections. Maintenance mode has
no L/P/B cache; entry into delta mode bootstraps at the writer barrier.

## Conceptual E replay

Insertion replays factors in reverse rank order; deletion uses forward rank
order. Within a factor, a fixed complete-key order is sufficient. Conceptual
E changes include every C key, even when its crossing is unproductive and no
enumeration is needed. Physical E storage is already at its drained endpoint;
the mixed state is represented by the traversal/index invariant below.

Every intermediate E tree remains downward-total:

- On insertion, a newly added parent key has its endpoint-after witnesses,
  since all descendants have already reached E-after. Unprocessed parent keys
  still have their before witnesses, and every child domain contains E-before.
- On deletion, strict ancestors have reached E-after. Every surviving parent
  key therefore has an E-after child witness, which remains present throughout
  that child's partial deletion. Remaining keys of the current factor are
  before keys with before witnesses in its unprocessed descendants.

This argument also covers skipped E keys and arbitrary key order within one
factor. A full assignment chooses one complete key from a factor, so two
different keys of that same factor cannot occur in one assignment.

At a fragment boundary, L equals the mixed join's global projections. Because
the mixed tree is downward-total, the top-down L recurrence is exact. Changing
only E_i therefore changes L only inside i's original subtree; ancestors and
all off-path branches retain their L memberships.

## Productive queues

Preparation scans all K changed keys once, after journal/view construction:

- Insert: keep root keys and nonroot keys whose separator has initial L-before
  parent support. Strict ancestors are unprocessed until this factor's reverse
  turn and their L stays unchanged, so this eligibility is static. A skipped
  key is globally dead at its conceptual crossing. It can later become live
  through a new ancestor, whose fragment includes it.
- Delete: initialize ordered queues from C intersect L-before. After every
  actual L erasure, erase that key from its future productive queue immediately.
  The invariant is queue = unprocessed C intersect current L, excluding the
  separately owned active anchor. Positive-to-positive support changes alone
  do not remove queued keys.

Pop/extract and own the complete anchor before constructing its cursor. Every
remaining queue head is productive. Initially dead and later-pruned keys still
cross conceptually at their factor's turn; being globally dead under monotone
deletion, they change no answer or L key. They need no later scan.
An empty route has bounded post-preparation detection, even when K is large.

## Fragment cursor and exact ownership

Reroot the traversal at the complete anchor key. Choose each next factor from:

| Region/edge | Source |
| --- | --- |
| Original subtree of anchor, downward | E-after for insert; E-before for delete |
| Upward path to original root | Current live-parent P bucket |
| Downward branch outside anchor subtree | Current live-child B bucket |

Endpoint E is correct inside the original subtree: descendants have already
finished insertion, or have not yet started deletion. The anchor's own key is
fixed, so other partially replayed keys at that same factor are irrelevant.
Every outside L bucket is exact and immutable throughout this fragment.

A downward E choice extends by totality; an outside L choice is already
globally live and matches the separator. Running intersection permits splicing
the selected branch with the outside completion. Thus every selected partial
assignment extends and every newly opened bucket has a first row. There are
no failed partial subtrees, excluded-row scans or canonical rejections.

The cursor owns its separator and selected tuple. Indexed successors are
looked up afresh; no borrowed iterator/reference survives a live mutation.
Endpoint E readers stay immutable and pinned until the fragment closes.
Insertion's after E ignores inverse patches; deletion's before E has matching
restored buckets with no newly inserted E exclusions in this monotone route.
Original output slots preserve ordered/repeated typed core heads.

Only one E key changes in a conceptual fragment. Its answers are exactly the
introduced/removed assignments containing that complete key. For an answer in
the endpoint difference, let i be its smallest-rank changed factor. Its last
inserted changed key, or first deleted changed key, is at i. It appears in
exactly that fragment. This is D03's earliest-factor owner; insertion visits
owners in reverse order. Native alias/prefix order is unchanged. Fragment and
alias differences telescope monotonically to the exact physical event delta.
No answer-history deduplication relation is retained.

## Coupling and deletion completeness

For each accepted core answer, visit factor projections parent-before-child.
Insertion adds missing projections. Deletion removes the current anchor key
and any descendant projection with zero current parent support. It must not
test the full route C for own-E removal: that would prematurely delete future
replay anchors. Every real L crossing immediately updates B and outgoing P
memberships/counts before a descendant projection is examined. Every L erasure
also prunes its queued witness, if any.

Insertion adds only projections of newly introduced answers and, by complete
fragment enumeration, installs every new projection. Outside projections were
already live. For deletion, current L remains between mixed-after and
mixed-before; both removal conditions are safe. Completeness uses the
[freshness certificate](incremental_live.md) for this **single-key mixed
transition**, rather than the original route endpoints:

1. The anchor disappears on its first accepted completion; its full key is a
   fresh binding absent from the fragment's E-after.
2. For removal at zero support, take the last matching parent key removed and
   extend its fresh ancestor-path binding with the child key. Running
   intersection and mixed-before downward totality give a compatible completion.
3. That completion is in this fragment's deletion and cannot precede the
   parent's removal. On its top-down visit the child sees zero support, so it
   is removed if not already removed. An earlier matching row after zero
   support would already have removed it.

Induct on depth to obtain exact L at fragment end. P/B counts equal their row
sets at each callback boundary. Outside buckets are unchanged, preserving
active cursor reads; future queue heads remain precisely productive.

## Bounded production and explicit finalization

For fixed query Q, let m be C* factors, M retained journal records, K actual
E crossings, D core delta answers, J L crossings, U degree-weighted outgoing
P changes, and V nonroot L crossings/B changes. Each factor has at most D
changed L keys, so J≤mD, U≤(m−1)D and V≤(m−1)D. K≤M because every C key comes
from at least one retained visible membership record.

After O_Q(1+M+K) indexed preparation, each first/next/last successful route
producer transition performs a bounded fixed-query number of actions:

- Exhaust a preceding fragment and scan at most m empty factor headers.
- Pop one productive anchor, derive its O(m) subtree/reroot program, and
  initialize a nonempty suffix. Candidate carry/reset touches at most m frames;
  bucket descriptor setup can inspect O(m²) compiled steps.
- Project at most m keys, change at most one L key per factor, and update at
  most m−1 P and m−1 B entries. At most m queue keys are inspected/pruned.
- Assemble/map output fields and append at most one owning spool node for an
  ordinary mapped core result. Scalar EXISTS replacements are a separate
  constant-sized epoch-final operation.

The on-output pending event buffer contains at most one pointer entry. Undo is
an intrusive owning stack with one prepared node per change; record is a
nonthrowing link operation. The spool appends one owning node per record.
Neither structure resizes/moves a D-dependent buffer during production.
Both teardown loops detach links iteratively, avoiding a D-deep destructor
stack. All data dictionaries are ordered: their operations have logarithmic
comparison costs, plus key/payload widths and allocator costs. The guarantee
is bounded indexed actions for a fixed verified query, not constant wall time
for the reference ordered backend.

`replay_preparation_work`, aggregate first/result/termination work and their
individual maxima classify already charged delta work. They include queue
changes, cursor exhaustion/frame closure, L/P/B coupling, SQL mapping and
spool-node append actions. The main oracle checks their sum with finalization
and scalar-EXISTS final work against total delta work.

Finalization is separately charged and is not a bounded-delay claim:

- `finalization_changed_keys` counts cleared C keys.
- `finalization_view_entry_bound` conservatively bounds retired shared view
  patch/key/index/container entries and copied key fields; it is a bound,
  not a measured CPU instruction count.
- `finalization_kernel_record_bound` and `finalization_driver_changes` expose
  physical/support/source/derivation cleanup bounds.
- `finalization_undo_entries` precharges the exact live/index journal length
  before publication; subsequent commit teardown cannot throw or allocate.
- Eager reference mode additionally charges all retired full L/P/B image rows,
  even with unchanged answers.

This is O_Q(1+M+K+J+U+V) affected cleanup for replay, with widths and allocator
costs, plus unread output/final-owner destruction. Eager mode also pays full
image sizes. Alias boundary maintenance/preparation can have data-dependent
cost; the producer bound is per route after that work, not across an arbitrary
physical maintenance boundary.

## Profile, memory and publication

`DeltaRuntime::profile()` returns effective mode/strategies, typed candidate
and accepted-bound classifications, backend/domain assumptions, preparation,
maintenance, finalization and public-startup statements, and spool limits.
Its static-storage text remains valid after facade destruction. Maintenance
has no delta bound/publication; root-first has no candidate bound; canonical
strategies do not inherit replay's accepted bound. Eager state/finalization
explicitly includes committed/needed old/new full image copies. Serialized
physical-plan v1 remains compile-only and unchanged.

Steady state is local source/support/E/L plus P and B, linear for fixed query.
Temporary state includes O_Q(M+K+J+U+V) journals/patches/queues/undo, fixed-query
cursor metadata and configured output nodes/payload. Index/queue row peaks and
copy/field counters are separate. Zero-support buckets are extracted and
reclaimed; no engine history of emitted answers is stored. Caller-held pins,
snapshots/returned rows and allocator/arena high-water metadata are additional.

The spool quota includes `sizeof(Node)` (link and padding), allocated value
slots and owned scalar payload. It has no vector-growth buffer;
`spool_capacity_rows` equals prepared nodes. Per-allocation allocator metadata,
candidate/mapping scratch and immutable query layouts are extra. Consumption
moves and frees one node without allocating; discard/destruction clears unread
nodes linearly. Final-owner query-state/journal destruction has its own cost.

Public `apply` still prepares every alias and the whole bounded atomic spool
before publication. Its public first record waits for physical maintenance,
constraint validation (which may scan/copy DB), all preparation/production and
finalization. It has no constant public-startup guarantee. No spill/durable
delivery is inferred. Unpublished pause/resume/draining is separately supplied
by [D06 lifecycle](delta_lifecycle.md); durable delivery remains O work.

All throwing work, including conservative finalization budget checks, precedes
the physical commit barrier. Allocation/work/cursor/spool failure closes E
readers, rolls physical/support state back, restores L/P/B through prepared
node/scalar undo and clears private output. Old sequence/state/pins survive
and the same event can be retried. Bootstrap failure leaves maintenance mode
and its previous state unchanged.
