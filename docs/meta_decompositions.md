# Meta-decomposition construction

The library constructs and checks body metadata in
[meta.hpp](../include/crown/planner/meta.hpp) and
[meta.cpp](../src/planner/meta.cpp). The [companion adapter](meta_candidate_adapter.md) now enumerates ordinary join
trees and maps canonical inverse contractions into normalized CROWN candidates.
The existing candidate provider remains an independent minimum-height route
within its documented family.

The source is P3, Jiang, Wang and Koch, *Succinct Structure Representations for
Efficient Query Optimization*, [arXiv:2603.15465v2](https://arxiv.org/html/2603.15465v2),
Definition 4.3 and Algorithm 1, PDF pages 10–12. P3's intermediate-cardinality
objective does not establish CROWN maintenance cost. The pinned primary-source
review is `build/verification/v55-meta-primary-review-v1`.

## Data and usage

`meta::construct(catalog, query, limits)` returns a `Build`. Inspect `stop` before
using its optional `decomposition`; only `complete` publishes one.
`meta::check(catalog, query, decomposition, limits)` independently checks the
returned or edited metadata. Its `valid` flag requires `complete`.
Catalog/query admission uses the existing `crown::validate` contract and can
throw. Allocation failures propagate; budget stops discard unpublished work.

Each node has the following fields:

| Field | Meaning |
| --- | --- |
| `occurrence` | Original atom index for a physical node; absent for a minor |
| `scope` | P3's chi, the variables represented by the node |
| `interface` | P3's kappa, variables shared outside the node's subtree |
| `parent` | Parent node index; absent only for the root |

Physical scope equals its original occurrence's complete variable set. Repeated
tables and equal scopes keep separate occurrence indices. A special reduction
edge refers to its canonical minor, even when an original occurrence has the
same scope. It never acquires physical identity through scope equality.

For example, `R(x,a), S(x,b)` reduces to two physical children below a minor
with scope `{x}` and empty interface. Both children have interface `{x}`.
The minor groups possible join structures; it is not an executable CROWN node.

## Construction and independent checks

Each reduction round computes overlaps from a frozen active set. Equal-overlap
groups collapse to a special edge; grouping repeats to a fixed point before
all remaining ears are removed using another frozen snapshot. Replacements can
create another equal-overlap group, as `R(x), S(x,y), T(x,y)` demonstrates.
A minor reused by a later reduction receives its final
interface; retaining its provisional interface would create incorrect parents.
After reduction, parents follow Algorithm 1's minor-first/highest-parent rule.

The checker rebuilds occurrence coverage, rooted topology, running intersection,
actual interfaces, Definition 4.3 C4(b)'s highest-parent condition and C5's unique
minor condition. It does not trust the constructor's reduction trace. It also
rejects scopes containing variables absent from the body.

Checking also requires each minor's whole scope to be contained in one original
physical scope, a stronger Algorithm 1 domain invariant. With coverage and
running intersection, every minor can contract toward such an anchor, leaving
an ordinary join tree. This rules out an artificial unguarded bag hiding a
cyclic body without running a second full recognition pass.

P3 excludes empty hyperedges. Empty bodies and occurrences with no variables
therefore return `empty_body` and `nullary_occurrence`, respectively, from both
APIs. Existing CROWN planning still handles those queries. Disconnected bodies
with nonempty scopes use an explicit empty-scope minor root, an adapter extension
whose future enumeration requires a separate no-external-parent rule. Cyclic
bodies stop with `cyclic`; limit exhaustion makes no acyclicity claim.

## Costs and remaining work

These are cold planning operations. `work` counts selected metadata steps;
`nodes` caps the highest admitted decomposition node count, including an append
whose later allocation or scope charge fails; `scope_cells` counts cumulative
explicit scope copies and inserts, including checker scratch. The public usage
returns actual consumed charges. Exact and one-short grants are regression
tested separately for construction and checking.

The counters do not cover allocating input admission, allocator capacity,
scalar width or total CPU. Overlaps and structural checks are recomputed with
simple scans. This implementation claims neither P3's construction complexity
nor its enumeration-delay bound. It adds no runtime update hook, retained row
index or shared-query machinery.

The [adapter guide](meta_candidate_adapter.md) documents bounded ordinary
join-tree expansion, generalized/head mapping, local coverage and completion.
A minor scope can fail CROWN's every-child generalized guard: copying metadata
directly is insufficient. Every published CROWN candidate still passes original
P02 and independently proved height gates; ordinary-tree coverage alone supplies
neither global generalized height nor maintenance-cost authority.

The appendix's enumeration pseudocode has inconsistencies recorded in the
primary-source review. The implementation preserves typed external-parent
placeholders, composes every child variant and handles disconnected roots
explicitly. Local exponential search stops at explicit grants; no fanout
heuristic is silently substituted. The adapter guide qualifies its actual
family, cost boundaries and completion status.
