# P07 independent normal-form plan-set collector

**Proposal only. P07 remains `not_started`.** This isolated reference routine
does not change the frozen P05 inputs or ordinary/native source, CMake, tests,
schemas, or tools. It is not registered with a repository target. No generated
set counts below are reported as observed results.

The proposal follows the [P07 design preflight](../p07-design-preflight-2026-11-07.md),
[implementation seams](../p07-implementation-seams-2026-11-07.md), and the
literal minimum-only [frozen tree oracle](../../../tests/reference/tree_oracle.cpp).
The frozen oracle remains unchanged and continues to return one minimum
witness. This collector has a different job: enumerate every distinct
P02-valid member of the finite normal-form family for one caller-supplied
native height.

## Independence and boundary

`collector.cpp` has its own topology decoder, root orientation, scope-union
builder, tree construction, deduplication, and recursive structural signature.
It does not call a production generator, production plan-key implementation,
the frozen oracle's minimum search, or any proposal helper. It uses only the
existing independent `planner::validate_tree(catalog, query, tree)` at the
acceptance boundary. Each full draft is checked against the exact supplied
Catalog/Query before its signature is computed. Only a successful P02 report
with the requested native height enters the result set.

The API takes a Catalog, Query, and native height. This height merely selects
which members to collect. It is not proof that a valid tree exists, that the
height is minimum, or that any plan is globally cost-optimal. The output
signatures are local equality evidence for that binding and requested height;
they are not cache identities or proof artifacts.

## Enumeration order

For `m > 0`, native labels `0..m-1` retain the original query occurrence IDs.
For generalized count `g = 0..m-1`, generalized labels are `m..m+g-1`. The
collector visits:

1. `g` in ascending order.
2. Labeled undirected trees in ascending numeric lexicographic Prüfer-code
   order. A Prüfer digit ranges from `0` through `n-1`, where `n = m+g`.
3. Every root of each tree in ascending label order.
4. Generalized scopes in ascending generalized-label order, using the
   lexicographically sorted unique scope universe. The last generalized label
   varies fastest.

For `n >= 3`, the standard Prüfer decoder converts each code into one labeled
undirected tree. It then orients that tree once for each root. `n=1` uses its
single isolated vertex directly; `n=2` uses its one edge directly and still
visits both roots. Neither branch constructs a Prüfer digit or calculates a
fixed-width topology count.

Native scopes are derived in full from each atom's variable terms; constants
and ignored terms add no variables, while repeated terms collapse through
`VariableSet`. For a generalized scope, the allowed universe is the unique
union of every native scope's power set, including the empty set. The reference
builder visits each power set with dynamic recursion and stores unique
`VariableSet` values. It uses no integer masks, shifts, or arity-sized bit
integers. Each generalized node independently chooses one member of that
universe, so duplicate scope combinations reached from different native
anchors are naturally represented once in the universe.

Before assigning scopes, the collector rejects a rooted topology if any
generalized node has fewer than two children, any leaf is generalized, a
generalized node appears below a native node, or its native path height differs
from the supplied height. These are family filters. P02 still decides actual
tree validity, including coverage, running intersection, guards, head/connex
conditions, and its independently computed native height.

The empty body is handled separately: its sole tree is the empty tree, which
is passed through P02 and retained only when the report has the supplied
height (zero). For a nonempty body with no generalized nodes, no scope universe
is needed.

## Independent structural signature

After P02 acceptance, the collector recursively builds its own text signature.
Its grammar uses `NFREF1`, `node{...}` fields, explicit field separators,
scope and child counts, and byte lengths before nested child signatures. At
each node it sorts complete child signatures lexicographically before framing
them. A native node stores its original occurrence ID; every node stores kind
and its full sorted scope; the outer frame starts at the actual root. Thus the
signature preserves root, kind, native identity, scopes, and generalized
grouping while ignoring display names, node-vector order, child-vector order,
and derived claims. Claims are ignored only after P02 has checked the draft.

This is a recursive, human-readable grammar with `NFREF1<ROOT:...>` framing,
not the production proposal key's byte encoding. A duplicate signature keeps
the first representative in the deterministic traversal order. Distinct
native IDs preserve equal-scope self-join occurrences as separate plans.

`normal_form_reference_signature(tree)` exposes this same independent encoder
for a tree that the caller has already accepted with P02 against the intended
binding. The helper receives no Catalog/Query and performs no validation; the
checked-tree precondition is the caller's responsibility. Its result creates
no checked-tree, optimum, or minimum-height authority and is not a global
identity. This lets a separate small-case review sign each generator-accepted
tree and compare both complete signature sets and key-equivalence relations.

## Completion and resource limits

The collector is intentionally a blocking reference routine under two fixed
operational caps:

- At most 3 native occurrences.
- At most 3 distinct variables active in native atom scopes.

Exceeding either cap returns `resource_limited=true`, a corresponding stop
reason, and `exhausted=false`. These caps do not declare a query semantically
unsupported. A configurable work-unit limit bounds reference-level recursion,
topology and scope operations, candidate construction, each P02 call, signature
construction, and deduplication checks. Reaching it returns a partial set with
`resource_limited=true` and `exhausted=false`. Allocation and container limits
have the same incomplete status. The P02 call is blocking, but its inputs are
bounded by the explicit small caps; the work limit is not a hard time bound.

Only normal return after the `g`, Prüfer-code, root, and scope loops all finish
sets `exhausted=true`. A caller may treat the result as the complete set for
this finite family and exact supplied height only when `exhausted` is true and
`resource_limited` is false. Any returned prefix from a stopped call remains
useful for diagnosis, but it is never a complete-set claim.

The worst-case topology traversal visits `n^(n-2)` Prüfer codes and `n` roots
for each `n >= 3`, multiplied by `|U|^g` scope tuples on topologies passing the
structural filters, where `U` is the native power-set union. Code counts and
scope tuple totals are not precomputed in fixed-width integers. Prüfer decode,
root orientation, scope construction, P02 checking, recursive signatures and
exact duplicate comparisons add further work. The caps keep this routine
reviewable for independent small cases; they do not claim practical scaling.

Exhaustion covers every P02-admissible rooted tree in this finite family for
the supplied height, modulo the recursive signature. The P03 contraction
argument supports existence of a minimum-height representative in the normal
form family. This collector does not establish the minimum; it accepts no
`VerifiedOptimum`; and neither exhaustion nor the supplied height proves global
maintenance-cost optimality.

## Expected independent fixtures

These are expectations for the root-owned comparison, not results observed by
this proposal:

- Boolean `R(x), S(x,y), T(y)` at supplied height 2: 3 distinct normal-form
  trees.
- Equal-scope three-occurrence self-join at supplied height 1: 4 distinct
  normal-form trees.

The collector returns both full signatures and representative trees so the
root can compare its generated accepted-key set and key-equivalence relation
against independently collected representatives. Runtime invocation and
fixture checks remain outside this proposal.

## Root's observed comparison

The excluded [comparison probe](comparison-probe.cpp) passed a complete-set
comparison on all 225 three-atom/two-variable valid-head queries. The unchanged
literal P03 oracle supplied their minima: 177 at height one and 48 at height
two. The independently collected Prüfer family and generator-accepted family
have identical signature sets in every binding (516 distinct plans in total,
56,481 generator drafts and 5,685 P02-accepted drafts). Proposal structural
keys are bijective with the independent signatures across all those drafts;
duplicates and generalized-label permutations cause no observed false merge
or split. Both enumerators actually exhaust each family.

Five additional complete comparisons cover Boolean R/S/T (three plans),
equal-scope self-join (four), empty body, singleton and nullary singleton.
Ready observations are inert, retained drafts/keys stay valid, and zero-work,
native-cap and active-variable-cap reference stops remain explicitly
incomplete. Raw evidence is
`build/verification/p07-independent-family-comparison-preflight.json`.
The first five-case run is retained separately. An initial probe input kept
an unused variable after selecting a singleton atom; input validation rejected
it before that comparison, and the probe fixture was corrected.

This uses existing Release libraries and separately compiled proposal files;
it is not native P07 integration, sanitizer coverage or the full acceptance
matrix. P07 remains `not_started`.
