# Meta-decomposition candidate adapter

C04 adds the optional `crown_meta_candidates` library, exported as
`CROWN::meta_candidates`. It enumerates ordinary join trees and maps them into
normalized CROWN candidates under an independently supplied original minimum.
The [native acceptance and full review](verification/meta-candidates-v56-2026-11-15.md)
are received; the overall Refactor goal remains active.

[Ordinary enumeration](../include/crown/planner/meta_join_trees.hpp) and
[candidate preparation](../include/crown/planner/meta_candidates.hpp) are separate
interfaces. The [public example](../examples/meta-candidates/main.cpp) shows the
entire path: original exact proof, preparation, actual checked admission and
explicit coverage/cost scope. Existing ranking/selection can consume the
returned provider's snapshot.

## Paper source and ordinary family

P3 is Jiang, Wang and Koch, *Succinct Structure Representations for Efficient
Query Optimization*, [arXiv:2603.15465v2](https://arxiv.org/html/2603.15465v2).
Definition 4.3/Algorithm 1 supply the [metadata](meta_decompositions.md).
Section 4.2 Algorithm 2 and Appendix C.1.1 Algorithm 5, PDF pages 14 and 31,
supply the ordinary-tree expansion ideas. Their Prüfer/reroot helpers are in
Appendix C.1.2–C.1.3, page 32. The exact primary source and listing review are
pinned in the V55 evidence; do not transcribe its known index/placeholder and
Cartesian-composition mistakes literally.

The enumerator additionally enforces Algorithm 1's canonical minor-first
parenting: if a distinct minor's scope equals a node's interface, that minor
must be its parent. Literal Definition 4.3 alone permits rearranged graphs that
break this expansion's family partition. A native counterexample passed the
structural checker yet produced 32 of 64 valid rooted trees with complete status.
Such edited metadata now returns `noncanonical_metadata`; the same query's
constructor-produced representation still covers all 64. This is an explicit
input invariant, not a semantic rejection of that query.

The implementation retains occurrence labels, canonical labelled skeletons,
every descendant variant and independent endpoint choice. A full-interface
minor carries its own distinguished external-parent placeholder until the
parent removes it. Released branches attach to a frozen original host; a later
proper child may attach inside earlier branches. Scope equality never changes
physical identity. The empty root for disconnected components has no external
parent. Canonical sets suppress repeated complete fragment keys.

`meta::enumerate` independently checks metadata under its own grants, expands
bottom-up, checks each final ordinary tree's connectivity and running
intersection, and emits parent vectors. The root has `parent[root]==root`;
every other entry is an original occurrence index. Default `all_roots=true`
emits every physical root. Canonical mode emits only physical root 0 for each
undirected tree. `Enumeration::all_roots` reports the requested mode even after
an early stop; only `stop==complete` reports exhaustion of that mode.

Preparation defaults to canonical mode: inverse contractions already cover
all CROWN rootings, so materializing and discarding the other ordinary
orientations would multiply intermediate parent-vector storage by the query
size. Callers may explicitly request all ordinary orientations for inspection;
the mapping fibers are identical. The report's rooted count counts actual
returned records, not implicit rootings. A completed canonical run covers all
undirected ordinary trees.

For constructed canonical metadata, the recursive family argument follows the
P3 Appendix C.7 block decomposition, with local repairs made explicit. Ordinary
child blocks remain connected; a full-interface minor instead retains its
external-parent token. Contracting origin blocks gives a labelled skeleton,
and running intersection determines precisely the legal boundary-containing
endpoints. Enumerating every skeleton, descendant variant and Cartesian endpoint
choice recovers those possibilities. Descending interface order allows proper
children to attach inside previously installed larger-interface blocks. When a
placeholder is removed, each connected released branch has exactly one edge to
the connected original host; child-to-child connections already belong inside
that branch, so frozen-host attachment preserves coverage. No printed pseudocode
index or empty accumulator is used as authority.

Duplicate scopes retain distinct occurrence labels throughout this argument.
For disconnected bodies, each variable-overlap component is connected in any
ordinary join tree: union the running-intersection paths along its shared-variable
connections. Contracting these component blocks gives the empty-root skeleton;
its empty key permits every cross-component endpoint. The explicit no-parent
root rule therefore enumerates these extensions without retaining a dummy.
These are source/invariant arguments plus finite independent tests, not a
machine-checked proof or import of the paper's delay bound.

## Local generalized mapping

The inverse-contraction mapping is a local argument and implementation, not an
algorithm or optimal-substructure theorem claimed by P3. Its [source](../src/planner/meta_candidates.cpp)
and independent review spell out the following construction:

1. For each undirected ordinary join tree J, enumerate every nonempty connected
   set R of first-native roots. Delete only J edges whose endpoints both lie in
   R. The remaining forest has exactly one R root per component; orient each
   native component at that root. Its native height is independent of the
   zero-weight generalized prefix. Retain only the supplied proved height.
2. For a generalized cluster S of first-native roots, its scope is forced to the
   intersection I(S) of those roots' complete native scopes. Guard along each
   prefix path gives containment in I(S); running intersection across different
   children gives the reverse containment. No generalized scope powerset is
   needed.
3. Anchor the cluster at the minimum occurrence in S. Enumerate every nonempty
   subset of eligible whole branches incident to that anchor. A selected branch
   must meet its minimum occurrence at the cut edge; that edge's separator must
   equal I(S). The remaining center and all selected branches are recursively
   composed through their full Cartesian product. Singleton clusters are native
   roots; every generalized node has at least two children. Outside boundaries
   must fit I(S).
4. Reattach the native forest and submit the raw drafts to the existing
   [finite proposal provider](candidate_alternatives.md#supplied-finite-proposals).
   Original-binding P02, measured native height, full-key deduplication and
   transactional publication still decide every exported candidate.

For completeness within this normalized family, take any valid CROWN tree
whose generalized nodes have at least two children. Above makes those nodes a
prefix, with native-only components below its first-native roots. Canonically
contract each generalized node toward the minimum first-native descendant.
Guard and running intersection preserve an ordinary join tree J. The contracted
prefix induces connected J[R]; its noncentral child blocks are exactly the
whole branches described above. Reversing those contractions recovers the
original normalized tree and its forced scopes. Hence complete ordinary
coverage plus exhaustive inverse fibers covers the normalized minimum-height
family in the supported body domain. The separate finite normal-form reference
oracle tests this argument on small instances; it is not a machine-checked
all-input proof.

Unary generalized shapes are excluded. The established normalization argument
preserves feasibility and minimum height, not every maintenance cost or physical
layout. P3's static-cardinality objective is not CROWN event work. No global
maintenance-cost optimum, paper enumeration-delay bound or total-CPU theorem
follows from this adapter.

## Head, domain and authority

P02 supplies [CROWN validity](planner_proofs.md), including Guard, Above,
Connect, Cover and Connex. A root may contain hidden variables. Connex uses
root-connected output separators and head coverage; requiring every root scope
to be head-only would discard valid plans. The mapper therefore leaves final
head admission to the unchanged P02 gate.

A real original `VerifiedOptimum` is required. The adapter does not insert its
witness as a fallback, rerun the normal-form producer, create a new lower proof,
or label an ordinary tree as globally minimum in the generalized family.
Each candidate retains the original certificate unchanged and a separately
checked upper. Body constants, repeated tables and aliases keep the original
query binding. Empty bodies and occurrences with no variables are outside P3's
nonempty-hyperedge domain and return explicit construction statuses with no
provider; the existing original planner still handles these queries.

## Limits, completion and use

Construction, metadata rechecking, ordinary expansion, inverse mapping and
checked candidate admission have separate limits and usage. Expansion counts
selected checkpoints, cumulative unique family fragments and explicit vector
cells. Mapping additionally caps raw drafts and recursion depth before pushes.
Both preparations are bounded cold batches: extending a preparation grant means
a fresh call. A resource stop can retain a completed ordinary prefix or raw
mapped drafts, whose head/P02 validity is still pending checked admission.

`ordinary_exhausted` describes the requested ordinary mode;
`mapped_input_fibers_exhausted` describes all returned undirected input fibers.
The live `normalized_minimum_family_exhausted()` diagnostic additionally requires
the original returned provider's actual exhaustion. Advancing it is separate
from preparing it. A consumed partial supplied batch is not a completed meta
search. As with any public diagnostic aggregate, this method assumes the returned
report/provider have not been replaced. Moving the provider out makes the
remaining result unable to attest its progress. No edited report creates checked
height authority.

The C05 `require_exhausted_family` policy checks the retained finite batch, not
upstream coverage. Use the combined diagnostic when normalized meta coverage is
required. EXPLAIN correctly retains `finite-proposals-v1`, supplied-batch scope
and `global_cost_complete=false`; the example reports upstream coverage beside
that checked candidate report. There is no hidden fanout heuristic: search is
exhaustive until its declared grants stop it, and incomplete status is explicit.

Input admission, allocator capacity/headers, scalar/string widths, library
comparisons, container relocation and cleanup retain separate costs. Counters
are not S05 requested bytes, RSS or wall-clock deadlines. OOM/admission errors
propagate; two small private budget boundaries translate selected stops. The
module adds no runtime update hook, retained row/index graph, background worker
or shared-query state. Each call/provider owns its independent planning state.
