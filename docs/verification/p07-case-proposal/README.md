# P07 alternative-plan fixture proposals

Status: proposal only, 2026-11-07. P07 remains not_started. These files are
isolated under this new directory and are not registered in a test manifest.
P05's full matrix and historical manifests remain untouched. No native
implementation is authorized here, and no build, test, CLI, or runtime
validation was run.

The query and tree documents use the existing strict CQ v1 and tree v1 JSON
shapes. Occurrence IDs are kept exactly as declared in each query. Expected
P02 validity and canonical-key relationships below are proposals for root
review, not observed results.

## Authority

The exact-minimum expectation for the R/S/T family is based on Refactor.md
sections 5.1, 5.4, 5.6, and 9.1, together with the normal-form and verifier
reasoning in docs/planner_proofs.md. The only authority claimed before root
runs independent P02/P03 validation is that stated manual reasoning. The
fixtures do not claim an oracle run or a P07 implementation.

For the Boolean query R(x), S(x,y), T(y), the native S-root tree has native
height two. A height-one tree would have all native occurrences as leaves:
native leaves are required, and a native internal node would have a native
descendant because generalized nodes cannot occur below natives. In a
height-one tree, the least common ancestor of R and S must contain x by
running intersection. If that ancestor is generalized, Guard propagates x to
every native leaf below it, so its descendant-leaf set cannot also contain T.
Thus {R,S} must form a clade. The same reasoning for y makes {S,T} a clade.
Rooted-tree leaf clades are disjoint or nested, but these two overlap at S and
neither contains the other. Height one is impossible. The supplied native
S-root, generalized x-root, and generalized y-root witnesses each have
height two; together these give a concrete three-member minimum family by
manual reasoning, pending P02/P03.

This follows the P07 acceptance boundary in Refactor.md: P02 decides
admissibility, P03 supplies the shared minimum-height authority, and P07
returns distinct valid candidates at that height. Structural optimality is
not inferred from a provider's enumeration status or from a cost score.

## Fixture map

| Fixture | Proposed expected result |
| --- | --- |
| queries/boolean_rst.cq.json + trees/boolean_rst_native_s_root.tree.json | P02-valid; native height 2; manual h*=2 witness |
| Same query + trees/boolean_rst_generalized_x_root.tree.json | P02-valid; native height 2; key differs from native S-root and generalized y-root |
| Same query + trees/boolean_rst_generalized_y_root.tree.json | P02-valid; native height 2; key differs from the other two |
| Same query + trees/boolean_rst_native_s_root_permuted.tree.json | Same canonical key as native S-root after node-vector, child-vector, display-ID, and scope-array permutations |
| Same query + trees/boolean_rst_scope_probe_empty.tree.json and boolean_rst_scope_probe_x.tree.json | Same topology and native identities, different generalized scope; after P02 acceptance, keys differ. These unary-generalized probes test canonical scope identity only; P03 normal-form enumeration contracts unary generalized nodes, so they are not promised provider outputs. |
| queries/self_join_equal_scope_three.cq.json + trees/self_join_left_direct.tree.json | P02-valid normal-form shape, native height 1; three equal-scope native occurrences retain distinct IDs |
| Same query + trees/self_join_left_direct_permuted.tree.json | Same canonical key as self_join_left_direct after node/child/display-ID permutations; occurrence-to-position mapping is unchanged |
| Same query + trees/self_join_right_direct.tree.json | Different canonical key: the original occurrence identity at the direct branch differs from the occurrence under the nested generalized branch. This is not a node-order permutation. |

Canonical tree identity is local to a checked tree. A cache or published
candidate identity must also remain namespaced by the complete exact query
binding and supported planning context. A hash may index full canonical-token
equality; it is not equality evidence.

## Cache-fence proposals

These are acceptance scenarios, not an implemented context schema.

| Fence | Proposed comparison | Expected result |
| --- | --- | --- |
| Head | boolean_rst.cq.json versus boolean_rst_head_x.cq.json, using the native S-root tree as a proposal for each | Exact-binding cache miss because the ordered head changed. Recheck the target binding with P02; do not transplant an optimum proof. Head order, repeated outputs, and aliases are also binding data. |
| Type/catalog | boolean_rst.cq.json versus boolean_rst_type_x_int64.cq.json | Cache miss because x and its source columns have a different scalar type, even if the tree's occurrence topology is unchanged. Include the full catalog and query binding, not catalog version alone. |
| Update assumptions | Repeat a lookup under the same admitted update profile, then change the profile or FIFO scope | Same supported profile may hit. Two separately admitted profiles or FIFO scopes must not mix. If the requested profile is unsupported in the first implementation, reject it before lookup instead of treating it as a hit or a cache miss with usable candidates. The initial proposal follows the preflight boundary: support the current full-row set-event/mixed-update profile and reject unknown profiles. |
| Arithmetic | Repeat with exact-nonnull-v1, then submit a different supported arithmetic policy if one exists | Same policy may hit; distinct admitted arithmetic policies must miss. Unsupported policy input is explicitly rejected and never silently normalized to exact-nonnull-v1. |
| Same-version catalog mutation | Keep the version number but alter a source table schema/type | Cache miss because exact source schema is part of binding identity. |

The preflight also requires planner/optimization/provider/cost versions and
selection policy where relevant. If rankings are cached, the complete
workload/cost inputs and statistics version belong in that namespace. The
candidate-set cache need not store CBO rankings.

## Proposed validation order

1. Root independently loads each strict JSON v1 query/tree pair and runs P02;
   failures or corrections are recorded here or in root's review, without
   changing P05's frozen matrix.
2. Root supplies the R/S/T binding to P03 and confirms the minimum is two.
   The expected family is the three listed witnesses, modulo canonical
   identity. No count beyond these witnesses is claimed by this proposal.
3. The implementation's canonicalizer is compared to the independent
   normal-form oracle, including these key equalities and distinctions.
4. Cache tests compare exact binding/context fields before any candidate or
   proof reuse. Structural-key equality alone is never cache authority.

Until those steps occur, all table entries above remain expected results only.

## Root's observed preflight checks

After the proposal was saved, root ran the existing P02 CLI on all nine tree
files and the two head/type query fences: all11 query/tree pairs are valid.
The R/S/T witnesses have native height2; the equal-scope self-join witnesses
have native height1. The independent frozen literal P03 oracle separately
confirmed minimum2 for Boolean R/S/T and minimum1 for the three-occurrence
equal-scope self-join. Results are retained under ignored
`build/verification/p07-case-validation-preflight.json` and
`build/verification/p07-case-oracle-preflight.log`.

These observed validity/minimum checks supersede those pending expectations
only. P07 canonical identity, cache fencing, enumeration and API checks still
require their implementation and independent tests. P07 remains not started;
none of these files changed the frozen P05 verification inputs.

