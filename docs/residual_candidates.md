# Residual candidates and proof status

P05 supplies a separate `ResidualSearch` library owner. It records a faithful
frozen-ear reduction, reconstructs admissible original-query trees, and uses
owned P06 exact searches when its candidate family needs repair. This family
is deliberately incomplete. A checked tree establishes an upper bound;
minimum height and infeasibility require a completed proof for the original
query. Integration and acceptance are recorded in the
[P05 packet](verification/residual-candidates-2026-11-07.md).

## Frozen reduction

Occurrences retain their original positions even for self-joins or equal
scopes. Each scope is a set of variable IDs: repeating a variable in one atom
does not increase its occurrence count. Constants and ignored columns are
preserved in query views but contribute no scope variable.

For current members M, V is their variable union, F is the original head
intersected with V, and U contains variables present in exactly one member.
For distinct current occurrences e and a, eligibility records both applicable
conditions:

1. The shared scope e minus U is contained in a, and e's unique variables
   contain no variable in F.
2. The shared scope e minus U is contained in both a and F.

Before deleting anything, the worker freezes every eligible ear, its shared
and unique sets, every supporting anchor, and the condition bits. It repeatedly
deletes the smallest original ear ID having a still-live frozen anchor,
choosing the smallest such anchor. Deletion never discovers a new ear within
that round. An anchor is distinct from its ear; therefore mutual ears retain
a representative. Each deletion is appended successfully before liveness
changes, preserving the pending pair after an allocation failure.

The worker checks q-hierarchy before each round. Incidence sets must be nested
or disjoint; when a free variable's incidence is properly contained in
another variable's incidence, that other variable must also be free. An empty
or hierarchical residual ends reduction. A nonhierarchical round with no
deletion is retained as a stalled layer and transfers to complete search.
Stalling is never an infeasibility result.

The immutable trace includes original scopes, complete pre-round metadata,
the ordered deletions and chosen anchors, remaining members, induced heads,
and a terminal dense query. Its forward and inverse occurrence/variable maps
make the distinct bindings explicit. Dense variables and occurrences use
ascending original IDs. Terms, source table IDs, variable types/names,
occurrence names, ordered/repeated output aliases and contradiction markers
are preserved. Only output positions whose variables remain visible belong
to the induced head.

An independent replay worker rederives scopes, incidence, eligibility,
deletion order, termination, maps and dense-query content from the original
binding. It shares the generic suspension mechanism with the producer, but
calls no reduction, view-construction or reconstruction semantic helper.
The strict public `verify_residual_trace` adapter checks caller-owned records;
successful trace replay proves no tree height or reconstruction completeness.

## Reconstruction and its soundness boundary

The terminal query receives an owned P06 exact seed search. A hierarchical
nonempty seed must have native height one; an empty seed has height zero.
A stalled seed uses the same complete search without assuming height one.
Only the checked seed tree is translated back to original IDs. Seed proof
authority remains about the induced query.

Deleted occurrences return in reverse layer and reverse deletion order.
At each step, the restored query has the original terms of exactly the
restored occurrences and the original ordered output positions still present.
Let S be the restored ear's intersection with variables already restored.
The constructor first tries its recorded anchor, then all other native
placements, guarded generalized leaves, and generalized forks:

- A native leaf attaches below a node whose scope contains S.
- A generalized leaf attachment additionally requires the generalized
  parent's complete scope to be contained in the ear's complete scope.
- A fork has scope S and children consisting of the ear and an existing
  subtree t. It requires S to be contained in t's scope. The old parent, if
  present, must be generalized with scope contained in S. This preserves
  the guard at both new edges and prevents a generalized node below a native
  ancestor.

These are proposal rules. Every private draft is translated to its induced
query and checked by the independent P02 verifier, including Cover, Connect,
Guard, Above, actual native height and reachability of the restored head in
the maximal output-connected subtree. Scope compatibility alone never
accepts a draft. The first valid proposal becomes the next restored tree.
Choosing it can exclude other valid reconstructions, so this greedy family
has no completeness or optimality claim.

If proposals fail, an owned P06 exact search solves the enlarged restored
query. Its checked tree replaces the prefix tree. If that partial query is
infeasible, reconstruction requests a complete exact search of the original
query. It never exports partial-query infeasibility. Finally, the fully
restored tree is checked again against the original binding before an
immutable candidate is published.

Soundness of published upper bounds follows directly from this last P02
check: every original native occurrence appears once, the full original head
is reachable as required, and the reported height is derived from the tree.
The generalized graft addresses the P(a,z,x), R(a,z,y), L(x), U(y), S(a,c)
augmentation example without attaching S below the incompatible {a,z} scope.
Trying other native placements addresses the wrong-anchor example. Neither
repair is asserted to be a general minimum-height theorem.

## Exactness and owning artifacts

`candidates_with_exact_repair` may finish with a checked upper bound after
successful reconstruction. `require_exact_original`, the default, also runs
a separate owned P06 search over the complete original query and independently
replays its proof. If reconstruction cannot supply a candidate, both modes
use this original search. A partial proof cannot satisfy this requirement.

Only completion of that original search exposes `VerifiedOptimum` or
`VerifiedInfeasible`. If its optimum improves the candidate, a new immutable
candidate is published; older handles retain their original checked upper
bounds. A completed optimum equal to the candidate retains the candidate's
construction provenance. A candidate contradicting an infeasibility proof
or claiming a height below the proved minimum is an internal failure.
The origin enum names the last successful operation producing that tree;
the trace and statistics retain earlier reduction/restoration/graft/repair
activity. For example, a graft followed by native restorations has a native
last-step origin and a nonzero generalized-graft counter.

Progress bounds refer to the original query. Until original proof completion,
the lower bound remains universal (zero for an empty body, one otherwise)
and the upper bound exists only after a full original tree is checked and
published. Exact prefix diagnostics are explicitly scope-qualified and
cannot raise the global lower bound. Trace verification, checked upper-only
status, and exact original proof status remain distinct.

The mandatory seven- and nine-atom queries have one productive frozen round
and a height-one residual, but original minimum three. Round counts and
residual minimums are diagnostic facts; neither rounds plus one nor the
terminal minimum certifies an original lower bound. The independent P03
oracle and P06 proof retain the original minimum-height authority.

Trace and candidate handles own immutable original bindings and remain
usable after their search owner is moved, cancelled or destroyed. No public
constructor converts edited trace/tree/progress data into checked authority.
The allocating report writers operate outside search quanta.
Each search owner requires one exclusive caller. It may move between threads
under exclusive ownership; its methods are not concurrency-safe.

## Work and resource accounting

Each `advance` retains actual reduction, view, replay, reconstruction, P02 and
delegated exact execution positions. Delegated exact search receives one work
unit per outer operation; no compatibility call drains or restarts a search.
Work/time/record/cell/depth stops and allocation failures retain the same
owner for retry or monotone limit extension. Zero work or zero active-time
quanta are inert. Cancellation retains published immutable artifacts and
diagnostic history while releasing unfinished workers.
Counter exhaustion is terminal, including exhaustion in a delegated exact
owner; an irrecoverable inner failure cannot appear as a resumable grant stop.

The residual ledger counts attempted and committed outer transitions,
allocation failures, active nanoseconds and residual logical depth. Delegated
P06 owners keep separate producer/replay work and depth ledgers. Residual
logical-depth limits cover residual, view and P02 frames; exact owners use
their own depth ceiling. Record/cell counters charge cumulative logical
construction, including discarded drafts and independent replay work.

`ResidualSearch::create` owns and validates its input before metering begins.
Delegated owner admission copies/validates whole Catalog/Query bindings;
these explicit variable-width costs are not per-cell transitions. Admission
counters record successful delegated P02/exact owner publication during
`advance`, and the outer active clock includes those calls.
Residual record/cell ceilings exclude these admission copies, delegated P02
validator scratch and delegated exact storage. Standard-container allocation capacity, scalar/string widths,
cleanup and caller-retained immutable history are separate costs. These ceilings are neither a global allocator-byte cap nor a hard CPU deadline.
S05 separately verifies the post-admission native runtime query byte account;
standalone search/compiler work and explicit exports remain outside it. See the
[query memory contract](query_memory.md).
