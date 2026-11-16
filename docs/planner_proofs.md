# Structural foundation and remaining proof obligations

The implemented P01 module uses classical GYO reduction on occurrence scopes.
For each remaining hypergraph it removes an empty edge, a variable appearing
in only one remaining edge, or an edge contained in another remaining edge.
It repeats until no rule applies. Complete reduction characterizes
alpha-acyclicity. Edge identity is the original occurrence index, including
duplicate scopes; these reductions do not mutate the query or remove mutable
inputs from evaluation.

`classify` checks both the body H and H augmented with the unique head-variable
set F. The body must itself reduce completely. In particular, a universal
synthetic head may make a cyclic body's augmented hypergraph acyclic; this
does not make the body admissible. The head edge is only a recognition device
and never enters the physical database, reference evaluator or runtime tree.
Empty separators, empty heads, empty scopes and empty bodies have no special
fixed-width representation or arity restriction.

Each reduction returns a deterministic, replayable list of edge removals and
variable removals, including containment anchors. Failure retains the reduced
core with original edge IDs. The independent test replay checks every operation
against current scopes. A separate test implementation enumerates undirected
spanning trees and directly checks each variable's connected subtree, without
GYO helpers. The finite audit covers all ordered bodies with 0–4 edges over
three variables (4,681 bodies, including duplicate/empty scopes) and every
head scope for 0–3-edge bodies (4,680 augmented hypergraphs). This validates
the implementation in that finite scope; the classical characterization,
rather than the finite test count, is the algorithm's general basis.

P02's independent tree verifier is implemented as `validate_tree` and exposed
through `validate-plan`. It returns a checked tree height and valid upper
bound only. P03's literal oracle and complete partition search are now
implemented, with independently replayed lower bounds. P04 fast paths and
P06 owned continuations are now acceptance-verified; their preservation and
resumption arguments follow below. Alpha-acyclicity recognition proves neither
a CROWN-tree height nor an optimal plan. CLI classification therefore still
reports `height_status:not_checked`.

The P03 search preserves all rules in Refactor.md §5.1, including
native-occurrence cover, native leaves, running intersection, generalized
guards, the prohibition of generalized descendants below natives, and the
root-connected output subtree. Use the m−1 generalized-node normal form and
all native-scope subsets with its contraction proof. Keep the seven- and
nine-atom residual-height counterexamples as fixtures. Ear-round counts cannot
be used as an optimum certificate. No novel scalable planner or residual
reconstruction proof has been discharged at this checkpoint.

P05 has a verified [candidate construction implementation](residual_candidates.md).
Independent frozen-trace replay proves only the reduction;
final original-binding P02 validation proves an upper tree. The greedy
native/generalized/graft family makes no completeness claim. Failed prefix
construction invokes owned exact repair, and only a completed original-query
P06 proof establishes its minimum or infeasibility. Neither the number of
rounds nor a height-one residual enters an original lower-bound certificate.

P07 consumes the supplied original `VerifiedOptimum`; it creates no new lower
bound. Each proposed alternative passes original-binding P02 and must have
exactly that proved height. Combining that checked upper with the retained
original lower proof establishes its minimum height without substituting the
alternative into the certificate's original witness. Root/parent digits visit
every rooted labelled topology for each generalized count through m−1, and
dynamic native-anchor subset digits visit every allowed generalized scope.
Independent P02 plus full structural-key equality filters invalid/duplicate
representations. Exhaustion covers this normal form plus explicitly admitted
seeds, including non-normal-form verified witnesses. It does not establish
global maintenance-cost optimality. Exact binding/context comparison fences
cached upper reuse; every reused tree passes the same checks under the new
provider's unchanged original proof. See the
[alternative-plan contract](candidate_alternatives.md); native acceptance is
recorded separately in its verification packet.

## Free-connex class and tree existence

For a nonempty finite, well-formed occurrence-labelled body H and head set F
contained in its variables, H and H+F are alpha-acyclic exactly when an admitted
Cover/Connect/Guard/Above/Connex tree exists. A native-only witness already
suffices for existence; generalized nodes can still improve native height.
The empty body uses its separate constant operator.

For the forward direction, root an augmented join tree at F. In each body branch,
its root contains every free variable occurring in that branch; intersections
between branches contain only free variables. Project a body join tree onto F
and contract contained auxiliary scopes until only the branch roots remain.
Joining the original native branches by that projected tree preserves running
intersection and gives a connected output separator region covering F.

For the reverse direction, Guard and native leaves give each generalized node a
native anchor containing its scope. Contracting these anchored scopes yields a
body join tree. Rewiring the connex region through a new F node preserves
running intersection: hidden variables stay in one component and free variables
connect through F. Contract the anchored generalized nodes to obtain a join
tree for H+F. The checked argument handles duplicate/contained/nullary scopes,
disconnected bodies and self-join occurrences.

The [independent class-bridge report](../build/verification/v02-freeconnex-class-bridge-review-v1/report.txt)
gives the contractions and source/host limits in detail. It uses corrected
P1 v2 Appendix A, Lemma A.1 (PDF p.17), alongside P2 v1 §2.1.3 (PDF p.5).
Together with the finite normal form and complete exact recurrence below, this
connects the recognized class to the admitted tree family. It does not claim
that finite machine limits admit unlimited input or that a resource stop proves
infeasibility. Height minimization and release acceptance remain separate.

## Independent tree verification (P02)

The verifier accepts an explicit tree and the typed query. It does not call
GYO, a tree constructor, an exact search, or a runtime index/projection helper.
Native occurrence scopes are derived directly from atom terms, and all native
occurrences must be covered exactly once. Native scopes cannot be replaced
by their output projections. Generalized nodes have no external occurrence,
and leaves must be native. Unary generalized nodes remain valid here; P03's
normal form is a search normalization, not an extra admission rule.

Before structural traversals, the checker establishes unique node identities,
in-range edges, root indegree zero, all other indegrees one, and reachability
of every node from the root. These conditions imply a finite rooted tree:
a reachable directed cycle would give a node a second incoming edge or give
the root a parent, and an isolated cycle fails reachability. Failed topology
does not produce invented separators or heights.

For each variable, the checker traverses only nodes containing that variable
in the undirected parent/child graph; every containing node must be reachable.
It separately tests each generalized guard against every child, and propagates
native-ancestor identity along root paths to enforce Above. Actual separators
are computed by parent/child scope intersection, without trusting input claims.

The maximal connex traversal implements the lemma from Refactor.md §5.2.
Let C* be the root plus all nodes reachable through separators contained in F.
Every possible root-connected output subtree can cross only those edges,
so it is contained in C*. Conversely, C* itself is such a connected subtree;
therefore head coverage of its scopes is necessary and sufficient. This
handles empty heads and empty separators directly. An optional supplied
connex subtree can be smaller than C*: it is checked for root inclusion,
parent closure, output-only separators and head coverage independently.

Native height is the maximum root-to-leaf native count, with generalized
weight zero. Ordinary edge depth is a separate maximum and may arise on a
different path. A nonempty nullary occurrence still has native weight one;
the empty-body constant alone uses an empty tree with height/depth zero.
Optional separator and native-height claims must equal the computed metrics;
both underclaims and overclaims are rejected. A valid tree supplies an upper
bound on the optimum, not an optimality certificate.

Tests independently enumerate every parent-closed root-containing subset of
a four-node example for all 16 head subsets and compare existence of a valid
output subtree to C*. Hand fixtures cover native/generalized/disconnected
roots, duplicate scopes, projection, Boolean/empty queries, and both residual
counterexample upper witnesses at height three. Targeted corruptions exercise
every core rule and each claim. Dynamic tests include 70 variables, nine
native children and a 1,500-node native chain; a separate example makes the
native-height and edge-depth maxima occur on different paths. These are
finite implementation checks; no minimum-height or runtime complexity gate
is claimed by P02.

## Validation cursor and cost boundary

The independent checker in [verify.cpp](../src/planner/verify.cpp) implements
the P02 rules through 63 named switch cases. The
[usage cards](code_specs/primitives.md) describe each case separately, including
the saved cursor, preparation failure and actual container cost. The public
blocking adapter uses this same checker with unlimited frame allowance; it
validates/copies inputs before stepping and copies the final report afterward.

| Phase family | What is established before continuing |
| --- | --- |
| Empty-body checks | An empty tree, empty optional connex list and height zero. |
| Node/occurrence checks | Labels, scope IDs, native complete scopes, exact occurrence cover, generalized occurrence/leaf rules. |
| Root, edges, parents, reachability | Numeric graph safety, rooted indegrees and full root reachability. Unsafe topology skips later indexed traversals. |
| Parent-before-child properties | Actual separators, native-ancestor restriction, every generalized-child guard, optional separator claims, independent path metrics. |
| Per-variable connectivity | All containing nodes are connected through containing parent/child neighbors. |
| Maximal connex C* | Traverse output-only separators and check head coverage. Root scope may contain hidden variables. |
| Optional supplied connex witness | Independently check IDs, root inclusion, parent closure, separators and head coverage. |
| Height and publication | Check optional exact height, prepare diagnostic export and allocate checked-upper ownership before publishing validity. |

These phases establish feasibility and measured height, not minimum-height
evidence. The full admissible family and height convention use corrected
[P1 v2 §3.2, Definition 3.2, pp. 3–4](https://arxiv.org/pdf/2301.04003v2#page=3),
with Definition 3.1's tree notation. Definition 3.2 supplies Guard and Above;
Definition 3.1 alone is not the full five-rule family checked here. Classical
GYO recognition is a separate alpha-acyclicity argument. P2 §2.1.1 p. 4 states
the native-anchor generalized-scope convention; see the
[exact paper versions](code_review.md#exact-paper-versions).
The maximal-C* test is the local lemma in [Refactor.md §5.2](../Refactor.md).
Exact normal-form search and independent lower replay below are separate local
arguments; neither follows merely from a valid tree report.

Each successful step commits a cursor transition. Set/map lookup, comparison,
allocator activity and vector capacity admission still have their real costs.
Deques preserve existing elements on append but can allocate or maintain their
internal maps. Report vectors reserve capacity before incremental export. The
saved scans and scratch-clearing loops avoid restarting completed traversals;
final owner destruction and a caller's report copy remain size-dependent work
outside continuation steps. A work grant is not a byte cap or a hard time bound.

## Complete normal-form family (P03)

These arguments concern exactly the Cover/Connect/Guard/Above/Connex family
specified in Refactor.md. They do not use the residual-ear height recipe.
Let m be the number of distinct native occurrences, including aliases and
equal/contained scopes. For m=0 the empty tree has native height zero.

For m>0, contract a unary generalized node g into its only child c. Guard
gives scope(g) ⊆ scope(c). Its parent p, when present, is generalized by
Above, and scope(p) ⊆ scope(g) ⊆ scope(c). The new edge preserves Guard
and Above. Running intersection is preserved: g's variables remain in c,
and variables occurring on both sides already had to occur on the old path.
The incoming separator becomes scope(p), exactly as before contraction;
if g was output-reachable, c is now reachable across that same separator
and covers at least g's output variables. At the root, replacing g by c
also retains all old root variables. Native path counts are unchanged.

There are no generalized leaves. Repeated contraction therefore yields a
minimum-height tree in which every generalized node has at least two
children. Such nodes number at most leaves−1 ≤ m−1. Following Guard down
generalized descendants reaches a native node containing the generalized
scope, so every generalized scope belongs to the union of native power sets.
`tests/reference/tree_oracle.cpp` freezes the literal enumeration of this
finite family: every labelled root/parent topology, generalized counts
0…m−1, and that entire scope universe including the empty set. Native path
height is searched in increasing order. Scope/topology pruning only removes
non-trees, unary generalized nodes, Above violations and paths above the
current height bound. Every remaining labelled candidate goes through P02.
No pairwise-atom-separator restriction is used.

## Equivalent exhaustive branch partitions

The production search memoizes the same normal-form family through native
occurrence subsets. The following extra lemmas justify its enumeration;
they are original engineering arguments here, not attributed paper results.

For a subtree containing native set S, let U(S) be the union of its native
scopes, and let

```
B(S) = U(S) ∩ U(all natives outside S)
E(S) = F ∩ (U(S) − U(all natives outside S)).
```

B(S) must be in its root scope, since every path from an inside to an outside
native occurrence crosses that root. In a normal-form tree its incoming
separator is **exactly B(S)**. One inclusion is running intersection. For the
other, a shared parent/child variable belongs to a native outside S if the
parent is native. If the parent is generalized, its second child and Guard
provide an outside native containing that variable. Guard also ensures that
any variable in a generalized subtree root appears in some native inside S.
Thus a separator cannot contain a variable absent from B(S).

For a generalized root with child-native blocks C1,…,Ck, k≥2, define G as
the variables present in at least two child unions U(Ci). Running intersection
forces G into the root. Conversely, every root variable must, by Guard,
occur in every child and hence in every child union. Therefore the root scope
is exactly G, and G must be contained in **each** U(Ci). This determines a
normal-form generalized scope uniquely from a partition. It considers shared
variables of arbitrary child unions, not just original-atom intersections;
the literal power-set oracle remains a separate cross-check of this lemma.

A state also records whether its root is in C*. If it is outside C* and
E(S) is nonempty, the state is impossible. Indeed no node inside that subtree
is output-reachable, while an ancestor containing such an exclusive variable
would itself be an outside native or, through Guard and another child, force
an outside native containing it. Neither is possible. Conversely, if a head
variable is missing from C*, take the least common ancestor of all its native
occurrences (the unique native itself when there is one). It contains the
variable by Connect and is outside C*. The first blocked subtree above it
contains every native occurrence of the variable, so its E(S) is nonempty.
Therefore rejecting exactly these blocked exclusive-head states establishes
head coverage. Child reachability is parent reachability AND B(child) ⊆ F.

The complete recurrence is:

- Choose any native root r∈S with B(S) ⊆ scope(r). Partition S−{r} into
  any number of nonempty child blocks, including zero blocks. Each B(Ci)
  must be contained in scope(r). Children forbid generalized nodes, and the
  height is 1 + maximum child height (maximum of no children is zero).
- If there is no native ancestor, partition S into k≥2 nonempty child
  blocks. Compute G as above and require B(S) ⊆ G and G ⊆ U(Ci) for each
  child. Children still allow generalized nodes, and the height is their
  maximum. Each child root includes G because G ⊆ B(Ci), establishing Guard.
- Reject a non-reachable state with E(S) nonempty. Return the minimum over
  all remaining choices; no choices means infinity/infeasible.

Necessity follows by decomposing any normal-form tree at its root. For
sufficiency, child witnesses use disjoint native blocks; their boundary
variables in the chosen root connect all cross-block/external occurrences.
The generalized construction satisfies Guard, and the native flag enforces
Above. Native coverage/leaves follow inductively, and the reachability lemma
gives Connex. Hence the recurrence optimizes exactly the normalized family,
whose optimum equals the original family's optimum by contraction. Every
recursive child is a strictly smaller nonempty occurrence set. Generalized
branching automatically retains the m−1 bound. Complexity remains exponential
in query size: memoization does not imply a polynomial planning theorem.

The original baseline early optimality stop is height one for a nonempty state. Every
admissible nonempty subtree has a native leaf and hence native height at least
one. Other pruning rules above are admissibility conditions, not heuristic
cost/lower estimates. No residual-round number enters this algorithm.

## Independent lower-bound evidence and strict limits

A minimum result includes its P02-checked upper tree; completed infeasibility
has no upper tree. Both include a query-bound table of state lower bounds,
with null denoting infinity. The certificate checker is separate
from search. It derives inside/outside unions independently of producer counts
and enumerates partitions by choosing the block containing the smallest
remaining occurrence, rather than the producer's insertion enumeration.
It processes states in increasing native-set size. Bound one is universally
valid, and blocked-exclusive-head states have infinite bound. For every other
claimed bound, it independently examines **every** admissible native/generalized
root and child partition and verifies that the option's child lower bounds
establish the claim. An omitted child state supplies only the universally
safe lower bound one. Claimed provided states must themselves be proved;
duplicate/invalid states are rejected. All dependencies are strictly smaller.

Induction thus establishes every recorded lower bound. The full-query state
must have matching generalized-allowed/reachable flags and the claimed root
bound. A matching checked upper-tree height proves the minimum. An infinite
full-query bound with no upper tree proves absence of an admissible tree.
For an empty body, the empty height-zero tree needs no state table. The JSON
binding is the exact canonical catalog/query document with empty physical
tables and no events; type-sensitive comparison prevents bool/int/float
coercions. Alias-independent hashes and general plan-cache canonicalization
are separate F05 contracts; the certificate retains this exact binding.

Public search emits `proven_minimum` only after this independent replay.
Work, tracked-recursion and optional time exhaustion are `resource_limit`,
with no minimum/tree/certificate and incomplete search status. They never mean
infeasible. Work/deadline limits apply separately to search and replay; counters
measure defined charge boundaries, not all CPU instructions, parsing work or
hard real-time latency. Literal/reference test-oracle scope materialization
has a separate explicit operational limit; production partition search does
not generate that power-set universe. P04's preservation arguments follow;
P06 adds actual owned producer, validation and independent replay continuations
with distinct strict/best-found authority, as described in its section below.

The implementation is cross-checked against the frozen labelled-topology/
full-power-set oracle for all 371 ordered 0–2-atom CQs over three variables and
all body-bound heads, plus seven three-atom shapes, including a height-one
nested-scope query requiring two generalized nodes. Analytic CLI cases include
both residual minimums at three, full four-edge path at two, generalized
height-one and projected height-two cases, stars, nullary/disconnected queries,
and renaming/permutation. Certificate mutations, resource stops and wide keys
have separate tests. This is finite implementation evidence, not a substitute
for the normal-form/completeness arguments or the later external G2/V02 review.

## P04 hierarchy, component and symmetry rules

The optimized implementation uses `crown_partition_exact_v2`. The v1 baseline
and independent exhaustive replay remain available for compatibility and
comparison. These rules preserve one optimum; they do not enumerate all ties
for the later P07 candidate interface. P04 acceptance is recorded separately in
[the working record](verification/planner-fast-paths-2026-11-06.md).

For a bound variable x, let A(x) be its set of occurrence indices. Occurrences
are distinct even when their complete variable scopes are equal. Q-hierarchy
requires every two A sets to be nested or disjoint, and requires y to be free
whenever x is free and A(x) is a **proper** subset of A(y). Equal incidence
sets may contain both free and hidden variables. Constants, ignored columns,
repeated variable positions and unused declarations add no variable incidences.

The constructor groups equal incidence sets, orders their laminar forest by
least strict superset and attaches each occurrence below its smallest containing
group. A group of at least two occurrences becomes a generalized node whose
scope contains its own variable class and all ancestor classes. Singleton
groups use the native leaf directly; empty native scopes are independent
leaves. Multiple roots are joined by an empty generalized root. A proper child
group cannot cover its entire parent group, and equal groups are merged, so
generalized nodes have at least two children. The implementation uses dynamic
sets/vectors and constructs this forest iteratively.

Cover follows from one original occurrence per native leaf. Every descendant
occurrence belongs to each ancestor incidence set, so every generalized scope
is contained in its children, proving Guard. A variable appears exactly in its
group's descendant region, proving Connect. Generalized nodes precede all native
leaves, proving Above. For a free variable x, the incoming separators on the
path to its group/native node contain only strictly ancestral variable classes.
Upward closure makes all those variables free. Hidden variables sharing x's
own incidence class first appear at that same node and do not block its incoming
edge. Thus the maximal root-connected output region covers every free variable.
All paths have one native, and a nonempty covered tree needs a native leaf,
so the checked witness has exact height one. Its certificate needs only the
independent universal root lower bound one, without trusting recognition.
Failure of recognition falls through to the complete recurrence.

An empty body retains the empty height-zero tree. One occurrence, including
nullary, retains its complete native root. Multiple nullary occurrences remain
separate native leaves. A contradiction-marked nonempty body is still optimized
as supplied structure; it is not silently replaced by height zero. P08/frontend
constant normalization is a separate contract.

For disconnected handling, components are the connected components of the
occurrence graph that joins scopes sharing a variable. Nullary occurrences are
singleton components, and each component's head is F intersect its variable
union. Component witnesses combine under an empty generalized root, giving
whole height at most their maximum.

For the converse, restrict an arbitrary whole witness to a component C.
Project generalized scopes to C's variables, retain C's complete native scopes,
and delete each outside native, splicing its children into its parent. Deleting
an outside root may produce a forest. Remove generalized leaves that become
empty; contract unary generalized nodes; join multiple remaining roots under an
empty generalized root. An outside native contains no C variable, so it cannot
lie between two kept nodes containing the same C variable in a valid connected
witness. Splicing therefore preserves Connect, and any newly spliced separator
is empty. Projection only removes separator variables; unary contraction respects
Guard by scope inclusion. These operations preserve Above and cannot reduce
free-variable reachability or coverage. Native height cannot increase because
outside natives are removed and added/contracted roots are generalized. Thus
every component optimum lower-bounds the whole optimum, proving equality with
their maximum. One impossible component proves whole-query infeasibility.

The v2 checker applies this component rule **only** to the full-query state with
both flags true. It derives the actual components itself and recomputes their
ports: outside components share no variable, so their global boundaries are
empty and their exclusive heads are precisely the induced heads. Missing child
proofs supply only one; an infinite root requires a verified infinite component.
No serialized producer partition or asserted component coverage is trusted.

For symmetry, any permutation within equal **complete** native-scope classes
is a bijection of structural witnesses: it only renames occurrence IDs at native
nodes, preserving scope, coverage, edges, separators and height. It does not
merge mutable sources, predicates or aliases. Thus native-root alternatives
need one representative per equal-scope class within a search state. For proof
states, counts of members in each class determine the inside/outside variable
unions, boundary and exclusive head. Both state flags are retained. V2 proof
keys choose the first k global indices per class as a canonical representative;
actual witness choices keep their original IDs.

The checker derives these classes independently, proves each supplied claim
on its actual stated member set and only then transports that bound to its
orbit key. It rejects duplicate orbit claims. Normalization preserves member
count; every recurrence/component dependency is strictly smaller, so transport
cannot create a circular justification. Induction plus the checked upper tree
establishes the result. V1 continues to use ordinary keys and exhaustive root
alternatives, with no orbit or component shortcuts.

Incumbent pruning uses only the recurrence's native root cost one/generalized
cost zero and universal child lower bound one or completed exact child values.
Once root cost plus a checked child maximum reaches incumbent U, no remaining
child can make that candidate improve U. The candidate may be skipped, including
ties, while a search state is memoized only after all alternatives are solved
or safely dominated. A cutoff is never cached as infeasible. Residual rounds,
cost scores and heuristic estimates are not lower bounds. The independent
checker still verifies every applicable alternative using checked smaller
bounds and the universal default for omitted children.

Counters record hierarchy attempts/hits, empty/singleton routes, component
splits, root symmetry skips and incumbent cuts. A separately compiled private
baseline disables the new paths and emits v1 proofs; production exposes no
baseline control. P06 now separately exposes P02-validated best-found upper
witnesses without minimum authority. These counters establish
which paths ran without elapsed-time correctness assertions.

At the historical P04 checkpoint, work units covered explicit scan/frame/
construction/export/replay charges; validation and container costs had additional
exclusions. P06 now meters controlled validation, copying and traversal transitions
as well, using continuation_v1. Admission and ordinary storage/comparison/scalar
width costs remain separate. Cooperative active-time checkpoints are not hard
CPU deadlines or complete S05 memory caps. Owned strict/best-found exploration
and independent resumption are implemented; external G2/V02 review remains open.

## P08 lowering preserves the checked tree

The lowering factories consume the actual catalog, core query and tree. They
run the independent P02 checks again, rather than accepting a caller's mutable
report. Normalized SQL is first rebuilt from its complete source artifact and
grounded to format 2. The only structural exception is an explicit constant
contradiction: its physical operator requires the empty tree, keeps the
original source atoms in its binding, and produces no rows for any input.
An empty noncontradictory body similarly becomes one nullary constant row.
Neither case infers a valid CROWN tree for a retained cyclic body.

For a tree route, order each logical scope by its variable IDs and compile
numeric field selections in that order. Direct input programs test constants
and repeated columns before projecting away ignored columns. Fixed decimal
fields can widen to the generic exact domain without changing their values.
Thus a native input tuple is exactly the assignment defined by its atom.
Physical full-row storage and occurrence relations retain distinct identities;
support counts for multiple physical derivations remain a later runtime task.

For every parent/child edge, the checked separator is their scope intersection.
Both endpoint projections target the same immutable ordered layout. Equal
typed separator values can therefore probe the child's parent-support relation
or the native parent's reverse index directly. If the parent is generalized,
Guard makes that separator exactly the parent's whole scope. Its candidate
records consequently range over child support keys, without a Cartesian
relation. Reusing an identical index requirement within a relation does not
merge child ports: each edge still retains its child ID and child slot.

For a noncontradictory `tree` route, the enumeration argument is conditional
on the later runtime maintaining the
specified exact survivor sets S_v and visible sets E_v = pi_(F intersect B_v) S_v.
It proves the emitted program's meaning, not update correctness or delay bounds.
For an edge inside C*, its separator K is contained in F and in both endpoint
scopes. Hence K is contained in both visible layouts, and the compiled parent
probe and child visible bucket projection are well typed. Nodes outside C*
need no E relation: their existential support is already represented in the
survivors of the C* nodes.

The natural join of all E_v for v in C* is exactly the full query projected to F.
A full witness supplies compatible visible assignments, proving one inclusion.
Conversely, choose one survivor witnessing each compatible visible assignment.
Adjacent C* survivors agree on their entire separator because it contains only
head variables. Attach each survivor's supported branches outside C*. Running
intersection rules out a hidden variable crossing two such fragments through
a C* edge, since that edge has no hidden separator variable. The fragments
therefore combine to a full witness. Head coverage of C* supplies every output
variable, proving the other inclusion. This also covers a hidden-variable root
projected to a Boolean/nullary visible assignment.

For any one full head assignment, its restriction to each visible scope is
unique. Each E relation has set membership, so it determines at most one choice
at every step of the parent-before-child program. Thus this program does not
repeat answers merely because hidden witnesses collide. Output assembly reads
the original ordered/repeated head positions and checks precompiled equalities
between shared assignment fields. Its result tuple preserves the declared
types and repeated-variable invariant. This is a semantic enumeration argument;
lazy product implementation, startup/delay/termination, epoch ownership and
pinned deletions remain D01 onward.

Only validated factories can create the immutable physical-plan type.
`ReferencePlanStorage` accepts that type and uses its actual layout/projection
tokens. Artifact import independently rebuilds the source, tree, layouts,
relations, routes, indexes, assembly slots and guarantee profile, then compares
the complete typed serialization. A digest or imported validity/optimality
flag alone is not authority. Exact source-artifact, F05 identity, local-ID-map,
tree and lowerer-version bindings complement this comparison; physical data
and events are excluded. On tree routes this preserves P02's checked
upper-bound height evidence without upgrading it to minimum-height evidence.
The constant-false route records a checked constant operator with zero height;
it makes no CROWN-tree claim for its retained body. The external
G2/V02 mathematical review remains open.

## P06 retained execution and authority

P06 changes the execution representation and accounting, not the P03/P04 state
recurrence, structural shortcuts or v1/v2 proof meaning. A continuation owns its
validated catalog/query, enumeration frames, partially constructed records and
next transition. No grant replaces that binding or reconstructs a completed
prefix by running the algorithm again.

At each controlled transition, potentially throwing preparation precedes cursor
publication. Failure leaves the same semantic next action and existing complete
prefix. Standard allocation may prepare capacity or private scratch; that does
not publish an alternative, memo value, bound or certificate claim. Root work and
allocation-failure counters record attempted transitions, including failed ones.
Induction on committed transitions therefore gives the same deterministic search
and proof traversal under one large grant, unit grants or any finite schedule
that eventually supplies enough resources. Retry may change attempted totals,
not the completed transition sequence or mathematical result.

Producer coroutine control flow between suspension points does not allocate.
Allocating operations, including creation of child coroutine frames, execute as
saved pending operations outside resume. An allocation exception therefore does
not destroy the suspended coroutine or skip its operation. Independent replay
instead uses explicit manual jobs and its own block/complement enumerator; P02
uses saved scans/traversal frames. Neither borrows producer proof assumptions.

The exact memo contains only completed exact choices. Dominated alternatives
remain justified by P04 bounds, rather than by a suspension. Choice records are
immutable after publication and have stable addresses in a flat arena with
nonowning child references. Frozen candidates/witness builders retain arena
ownership. A better candidate does not replace an exposed upper witness until
its complete concrete tree passes independent P02 validation and its owning
control block is ready. Resource failure preserves the previous upper witness.

The public lower bound remains universal zero for an empty body and one for a
nonempty unfinished family. A child result, visited alternatives alone or a
validated incumbent cannot increase this whole-family bound. Final lower
authority requires complete independent v1/v2 replay, including root matching.
Provided claims enter the verified table only after their own proof succeeds;
missing child claims retain universal one and unfinished claims remain unusable.
The independent ports cache contains only completed records derived from actual
members, with immutable owning keys. Caching changes work, not derived ports.

Only after replay completes and owning result preparation succeeds can the
facade publish VerifiedOptimum or VerifiedInfeasible. The former has a matching
checked upper and lower proof; the latter has a complete infinite root claim and
no upper tree. ValidatedIncumbent is a distinct privately constructed type and
establishes only an upper bound. Strict policy withholds it. Mutable progress
snapshots confer no authority, and progress/upper JSON always contains a null
certificate. Completed typed exports retain exact owned CQ/catalog bindings.

Resource ceilings never change state semantics. Logical depth is checked before
owned frame pushes; empty-body administrative work has depth zero. Monotone
extensions preserve consumed counters. Zero grants take the no-op path before
clock sampling or lazy-machine creation. Active clocks measure only execution
inside nonzero advances, excluding caller pauses. Clock checks are cooperative;
standard container/allocator and scalar-width costs remain explicit abstract
operation costs, not a hard CPU or memory bound. Legacy aggregate conversion,
input admission, cancellation and destruction are separately documented costs.

Cancellation detaches active coroutine frames leaf-first. Flat choice ownership
prevents recursive child-payload teardown; concrete tree edges are numeric IDs.
Cancelled owners release live frames, report current depth zero and retain peak,
work, structural and checked-claim history plus already published handles.
Published handles own their immutable payloads independently of facade lifetime.
The no-allocation cleanup claim does not assert constant-time deallocation.
