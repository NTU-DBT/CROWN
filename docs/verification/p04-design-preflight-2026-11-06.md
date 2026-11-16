# P04 read-only completion preflight, 2026-11-06

Proposal only. P04 remains in progress. Astra inspected actual code and
requirements without edits, builds, tests or status changes while O03's native
sources were frozen. Root preserved the findings for the next implementation.
The complete [Refactor.md](../../Refactor.md) scope remains mandatory.

The actual API is [oracle.hpp](../../include/crown/planner/oracle.hpp), not
an exact.hpp file. The implementation is
[exact.cpp](../../src/planner/exact.cpp); independent proof replay is in
[certificate.cpp](../../src/planner/certificate.cpp), and the frozen labelled
topology/full-power-set oracle is
[tree_oracle.cpp](../../tests/reference/tree_oracle.cpp).

## Remaining scope

Complete dedicated singleton/constant/disconnected handling, q-hierarchical
recognition and height-one construction, substantive symmetry reduction,
branch-and-bound, optimum-preservation arguments, independent P03 differential
coverage and dynamically sized representations. Existing search already has
the complete memoized branch-partition recurrence, boundary/head feasibility,
canonical unordered sibling partitions, empty-body handling and early stopping
at the universal nonempty lower bound one. P05 residual-ear candidates remain
separate and must not supply an unproved lower bound.

The main integration risk is proof export: a search shortcut must retain an
independently replayable certificate, including symmetric/disconnected states.
Faster search with missing proof entries is not a certified fast path.

## Q-hierarchical construction

For variable x, A(x) is the dynamically sized set of distinct occurrence
indices whose complete native scopes contain x. Q-hierarchy requires pairwise
nested/disjoint A sets, and: if A(x) is a **strict** subset of A(y) and x is
free, y is free. Equal incidence sets may mix free and hidden variables.
Aliases/duplicate scopes retain separate occurrence indices; constants,
ignored columns and repeated variable positions add no extra incidence.

Group equal incidence sets; parent each group by its least strict superset.
Attach each occurrence leaf beneath the smallest group containing it. A group
with at least two occurrences becomes a generalized node whose scope is the
union of variable classes on its ancestor chain, including itself. Singleton
groups use their native leaf directly. Empty-scope occurrences are independent
native leaves. Join multiple forest roots under an empty generalized root.
Every original occurrence appears exactly once, and no fixed-width mask is
needed. Generalized nodes have at least two children after normalization.

Cover follows from the occurrence leaves. Guard follows because all descendants
belong to every ancestor incidence set. Nodes containing each variable form
its group subtree, proving Connect. All generalized nodes precede native leaves,
proving Above. Upward closure of free variables over strict incidence ancestors
preserves maximal-connex output coverage; equal-incidence hidden variables at
the same node do not interrupt the path. Every path contains one native, and
every nonempty covered query requires one, proving exact height one.

Use the existing checked upper witness plus the single all-query lower-bound
entry of one. The independent checker can establish that universal bound
without trusting the recognizer. Negative recognition means fallback to exact
search, never unsupported/infeasible. Examples: R(x,y),S(y) with head x fails
q-hierarchy/minimum two; heads y or x,y have height one. R(x,y),S(x,y) with
head x is q-hierarchical despite hidden y. Boolean heads impose no upward rule.

Empty body keeps height zero. One occurrence, including nullary, uses a native
root of height one. Multiple nullary occurrences remain distinct leaves under
an empty generalized root. A contradiction-marked nonempty structural query
must not silently lose its retained body and become height zero; frontend/P08
constant routing is separate from the structural minimum_tree contract.

## Components, symmetry and bounds

Use connected components of the occurrence intersection graph; empty scopes
are singleton components. Component C has induced head F intersect U(C), and
the nonempty whole-query minimum is the maximum of component minima. Merge
upper trees under an empty generalized root. For the lower argument, restrict
any whole tree to C: project generalized scopes, delete/splice other native
nodes, remove empty generalized leaves, contract unary generalized nodes and
join multiple roots if needed. Outside native scopes contain no C variable,
so Connect/Guard/Above and output reachability survive; native height cannot
increase. Document root splicing and cleanup explicitly.

The current v1 checker enumerates whole-query roots/partitions. Component
proofs alone do not establish a whole-query bound above one. Recommended:
versioned compositional rules with independently recomputed disjoint coverage,
induced heads, checked component certificates and maximum/upper-tree validation,
preserving v1 decoding. Without this change, component witnesses may only seed
an incumbent until complete v1 replay proves optimality; label that limitation.

Equal complete native scopes permit structural occurrence permutations, even
with distinct tables/predicates/source identities. Never merge mutable inputs.
For root enumeration choose one canonical member per equal-scope class; swapping
IDs preserves scope, boundary, exclusive head, reachability, generalized
permission and height. Existing sibling ordering already removes permutations;
partition-orbit reduction is optional beyond the substantive root rule.
Either export orbit-transformed ordinary v1 state bounds (charged, potentially
exponential proof size), or add independently checked typed permutation rules.
Do not weaken the checker to trust constructor canonicalization.

For incumbent U, the native recurrence is 1+max(children), generalized is
max(children). A candidate whose established lower bound reaches U cannot
improve one optimum and may skip remaining children. Bounds may use one for
nonempty children, completed exact memo values, or proved infeasibility;
estimates/residual rounds/cost scores cannot prune. Missing child proof bounds
can default to one when already-solved children suffice. Never memoize cutoff
as infeasible; a state becomes exact only after every alternative is solved or
safely dominated. P07 all-optimum enumeration needs different tie handling.
Charge preprocessing, construction, pruning and certificate handling, including
wide incidence scans, through existing resource accounting.

## Implementation and acceptance plan

Keep minimum_tree compatible. Suggested private helpers are hierarchy analysis/
witness construction and component extraction/remapping, with exact.cpp owning
dispatch/incumbents/memo/symmetry, certificate.cpp owning independent new rules,
and versioned IO/schema changes only when necessary. An optional fast witness
means applicable/not-applicable; resource exhaustion must retain the existing
explicit stop status rather than becoming not-applicable/infeasible.

Preserve all 371 existing exhaustive cases and seven three-atom fixtures.
Extend exhaustive ordered small bodies/all bound heads, including duplicate/
empty scopes. Independently check q-hierarchy; recognized nonempty cases must
have optimum one, P02-valid trees and independently accepted certificates.
Negative cases still match P03 through fallback. Cover nested/equal incidence,
mixed free/hidden groups, disconnected height-one/two/three components, aliases,
constants, component permutations, Boolean/nullary cases, and seven-/nine-atom
residual counterexamples at height three. Test over 64 variables/occurrences,
wide scopes, stars and deep laminar families without semantic caps.

Compare optimized and baseline search through a private testing seam, both
against frozen P03 where feasible. Mutate component coverage/heads/bounds,
scope permutations and remapping in certificates. Exercise zero/time/work/
recursion limits during preprocessing, solve and proof replay; persistent OOM
must not produce a partial certificate or false infeasibility. Operation
counters should establish the shortcut ran; elapsed-time assertions are not
correctness evidence.

P06 remains separate: explicit strict/best-found result types, honest lower/
upper intervals and resumable owned enumeration frames. Current recursive
lambdas/stack-local partition iterators cannot resume after SearchStopped.
Owned handles must bind immutable query/catalog/options and preserve memo/
proof/incumbent/exploration state. OOM resumability requires its own atomicity
argument; strict mode must continue refusing uncertified minimum claims.

No mathematical blocker was found in this internal preflight. Proof-format
evolution versus expensive v1 expansion and the P06 continuation seam remain
implementation decisions. This is not external mathematical/release signoff.
