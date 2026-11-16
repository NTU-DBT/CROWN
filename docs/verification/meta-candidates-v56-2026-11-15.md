# Full source review and C04 acceptance — V56

C04 is technically verified within the explicit domain and family below. The
[implementation guide](../meta_candidate_adapter.md) connects each operation to
its paper or local argument, public API, limits and consumer. The overall
Refactor goal and release gates remain open.

## Review scope and findings

The [V55 review](meta-adapter-review-v55-2026-11-15.md) is the baseline. V56
receives all 370 maintained production paths and all 425 primary production,
build, tool and example paths, with zero unread primary paths. Byte-identical
source retains its prior full read; all eight changed or added primary files
have successor reads. All 366 prior production files are unchanged. The three
new test files have separately reviewed independent oracles and controls. This
is not a fresh full read of every inherited test file or a universal correctness
proof.

Parallel workhorse reviews covered ordinary enumeration, mapper construction,
independent oracles and usage contracts. One Astra Max review checked the local
inverse-contraction argument conditional on complete ordinary input. Root
received the final canonical-mode and metadata-domain changes separately; older
review pins retain their historical source versions.

| Finding | Correction and check |
| --- | --- |
| Structural metadata validity alone permits incomplete enumeration | A literal edited graph passed Definition 4.3 checks but returned only 32 of 64 valid rooted trees with complete status. Enforce Algorithm 1's minor-first parenting, returning `noncanonical_metadata` for that graph; the constructor-produced representation of the same query returns all 64. The original failing native control is retained. |
| Preparation materialized ordinary rootings that mapping discarded | Default preparation emits one physical-root-0 record per undirected tree. Inverse fibers still cover all normalized CROWN rootings. Explicit all-root mode produces the same checked family and remains available for inspection. |
| Paper pseudocode has unsafe identity/composition interpretations | Preserve tagged external-parent placeholders, all descendant variants and Cartesian endpoints; freeze the original host when releasing a dummy's branches. Independent exact family comparisons exercise these cases. |
| Ordinary-tree height can overstate generalized height | Mapping enumerates generalized prefixes and uses the supplied original minimum proof. Boolean R(x),S(y) has ordinary height 2 and admitted generalized height 1 in the installed example. |

## C04 acceptance criteria

| Refactor requirement | Received implementation and evidence |
| --- | --- |
| Source-grounded adapter and ordinary-to-CROWN mapping | P3v2 Definition 4.3/Algorithms 1, 2 and 5 supply metadata/ordinary expansion; the guide explicitly identifies repaired pseudocode and the local inverse-contraction construction. The optional installed `CROWN::meta_candidates` target exposes both APIs. |
| Generalized nodes and head constraints explicit | Generalized scopes are forced intersections of first-native root scopes. Enumerate all connected root sets and recursive branch partitions, with at least two children per generalized node. Final P02 checks Cover/Connect/Guard/Above/Connex, including valid hidden root variables and nonhead separators. |
| Every published candidate passes P02 | Raw drafts pass the existing original-binding finite-proposal provider, measured native height, structural key and publication gates. Each result retains its genuine original certificate; tests replay every admitted candidate independently through P02. |
| Ordinary-only results never establish global generalized minimum | A genuine original `VerifiedOptimum` is required; ordinary height/radius, paper cardinality and metadata do not supply it. No exact-witness, residual or normal-form fallback is inserted into meta coverage. |
| Family coverage and local exact/heuristic status | Report ordinary exhaustion, returned inverse-fiber exhaustion and actual provider progress separately. Exact/one-short/zero grants, partial batches and admission-capacity continuation are checked. No hidden fanout heuristic is used. |
| Small-instance comparisons expose missing families | Exact ordinary edge/root sets, normalized minimum-tree signatures, four-leaf generalized hierarchies and the retained 32/64 counterexample are compared with independent controls. |

Supported bodies have nonempty occurrence scopes and canonical constructed
metadata. Empty bodies/nullary occurrences return explicit construction status
without a provider; the original planner still supports those queries. Coverage
is the normalized CROWN family at the independently proved original minimum.
Unary generalized shapes are excluded under the existing height-preserving
normalization. This does not preserve every maintenance cost or physical layout,
and no global maintenance-cost optimum or paper delay theorem is claimed.

The ordinary family argument follows P3 Appendix C.7 with explicit local repairs.
The inverse proof contracts generalized nodes toward their minimum first-native
descendants and reverses those contractions. Written source/invariant review and
finite independent comparisons support these claims; neither is a machine proof.

## Native verification

All four selected registrations pass on final source in Debug and
ASan/UBSan/leak profiles: `meta_join_trees`, `meta_candidates`,
`installed_meta_candidates` and `clean_source_snapshot`. There are 361 current
registrations, including three new C04 registrations. The unchanged engine retains
its prior evidence; V56 does not claim two newly repeated full 361-test suites.

Each ordinary suite compares 7,750 calls over 3,875 nonempty scope multisets in
forward/reverse occurrence order: 7,114 acyclic and 636 cyclic calls, with 112,286
exact rooted keys. Thirteen literal fixtures cover placeholders, endpoint
choices and child variants. Its suffix-based Prüfer oracle is cross-checked
against independent spanning-edge subsets for all 146 labelled trees of sizes
1 through 5. Exact/one-short/zero expansion grants, metadata grants, permutations
and canonical mode have separate controls.

An additional separately compiled six-occurrence oracle passes in Debug and
under sanitizers: the literal equal-scope case has all 1,296 labelled trees;
128 deterministic acyclic families bring the total to 129 exact families and
10,281 undirected keys per profile. The fixed seed, host trees, scopes and raw
counts are retained in the logs.

The mapper suite matches complete normalized minimum families for 12 independent
small reference cases, including head variants, disconnected bodies, nested
generalized prefixes, hidden roots and physical-table aliases. A separate
set-partition oracle checks all 26 normalized four-leaf generalized hierarchies.
Limits, source proof retention, P02 replay, finite-family identity, C02/C05
selection, typed EXPLAIN and upstream-versus-batch exhaustion controls pass.

Both full C04 suites also pass through a moved Release/tests-OFF public SDK;
the public example separately passes installed Debug, sanitizer and production
Release runs, including failed-output handling via `/dev/full`. These builds
use installed headers/targets and exclude source/build header leakage. Native
receipts distinguish earlier supporting source versions from exact final inputs.

## Human inspection and performance scope

The index maps 785 files /179,462 lines /20,070 blocks. All 17,120 nonblank blocks
have 19,555 seven-field usage contracts; 2,950 regions are blank spacing. V56
adds 173 cards, receives 1,531 prior CMake/install attachments and updates 45
numeric CMake references. Generated maps, source hashes, independent registry
coverage and guide links are checked separately.

This adapter is optional cold planning work. It adds no runtime update hook,
retained row/index graph, shared-query state or runtime error framework. Each
private preparation stage has one small budget-stop boundary; admission/OOM
errors propagate. Canonical ordinary storage avoids an unnecessary factor of
query size. Enumeration and mapping can still grow combinatorially; their
selected operation/fragment/cell/depth grants are not allocator-byte, total-CPU
or wall-clock bounds. The guide states library comparison, relocation, width,
copy and cleanup costs explicitly.

Evidence: `build/verification/meta-enumeration-v56-v1`, including
`native-validation-final-v56-v1.json`, `family-coverage-v56-v1.json` and
`full-source-review-receiving-v56-v1.json`. The final seal is
`build/verification/human-inspection-v56-progress-v1.json`; the
[handoff](../handoff.md) records continuation steps. Ledger: 62 verified /
1 in progress (A02) /15 not started =78. Rights/notices and predecessor evidence
are preserved; licensing checks remain deferred under the user's instruction.
