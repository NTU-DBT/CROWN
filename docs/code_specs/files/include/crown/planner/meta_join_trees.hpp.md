# `include/crown/planner/meta_join_trees.hpp` — block usage map

[Source](../../../../../../include/crown/planner/meta_join_trees.hpp) · [Source index](../../../../README.md) · [Subsystem contracts](../../../../subsystem_contracts.md) · [Reviewed primitives](../../../../primitives.md)

Recognize structural query classes, check a proposed CROWN tree and lower checked structure into physical metadata.

Snapshot SHA-256: `a179cfa6fdda7db1ed082df1a6ff45ce37a0b1a2b91bacc3bdadf303bd8e6ef2`. 45 lines partitioned into 7 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [planner](../../../../subsystem_contracts.md#planner). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../../planner_proofs.md), [docs/tree_plans.md](../../../../../tree_plans.md), [docs/physical_plans.md](../../../../../physical_plans.md), [docs/code_review.md](../../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../../include/crown/planner/meta_join_trees.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. | source comment (unverified): // Occurrence-labelled ordinary rooted join tree, not a CROWN height capability. · [reviewed contract](#b0001) |
| [B0002 · 7–7](../../../../../../include/crown/planner/meta_join_trees.hpp#L7) | Type/record definition: struct JoinTree | source comment (unverified): // Occurrence-labelled ordinary rooted join tree, not a CROWN height capability. · [reviewed contract](#b0002) |
| [B0003 · 8–13](../../../../../../include/crown/planner/meta_join_trees.hpp#L8) | Type/record definition: struct EnumerationLimits | source comment (unverified): // Independent admission/checking grants, reported below. · [reviewed contract](#b0003) |
| [B0004 · 14–17](../../../../../../include/crown/planner/meta_join_trees.hpp#L14) | Type/record definition: struct EnumerationUsage |  · [reviewed contract](#b0004) |
| [B0005 · 18–21](../../../../../../include/crown/planner/meta_join_trees.hpp#L18) | Type/record definition: enum class EnumerationStop |  · [reviewed contract](#b0005) |
| [B0006 · 22–28](../../../../../../include/crown/planner/meta_join_trees.hpp#L22) | Type/record definition: struct Enumeration | source comment (unverified): // Requested mode, including on early/resource stops. · [reviewed contract](#b0006) |
| [B0007 · 29–45](../../../../../../include/crown/planner/meta_join_trees.hpp#L29) | declares values/defaults or compile-time conditions. | source comment (unverified): // P3v2 Algorithms2/5, with the reviewed placeholder/Cartesian/reroot repairs. · [reviewed contract](#b0007) |

## B0001

[Lines 1–6](../../../../../../include/crown/planner/meta_join_trees.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L6:sha256:a5059a35baf09011f092a53742eb19dbd7c0d03c9a1514a1a0a25a6c0ae01dce
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the public cold meta join-tree enumeration values and entry point while importing the validated metadata API. |
| inputs / outputs | Including this header provides Catalog, Query, Decomposition, Limits, and the declarations in crown::planner::meta. |
| invariants | The include guard prevents repeated declarations; metadata and an ordinary join tree remain distinct from an executable CROWN tree. |
| ownership | Preprocessor directives and the namespace opening retain no query, plan, or mutable state. |
| failure | Missing or incompatible declarations fail during compilation; this block has no runtime error path. |
| cost | Include parsing and dependency compilation only; no planning work or per-update operation is added. |
| Design | [include/crown/planner/meta.hpp](../../../../../../include/crown/planner/meta.hpp), [docs/meta_decompositions.md](../../../../../meta_decompositions.md), [docs/meta_candidate_adapter.md](../../../../../meta_candidate_adapter.md) |

## B0002

[Lines 7–7](../../../../../../include/crown/planner/meta_join_trees.hpp#L7); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L7-L7:sha256:a45cccbb06c28b40646a1872e16a0c5489eb1d5a54c3fe10f0366460151d954b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent an occurrence-labelled ordinary rooted join tree returned by the enumerator. |
| inputs / outputs | root is the original atom occurrence used as root; parent has one parent occurrence index per atom. |
| invariants | For a returned tree, parent\[root\] equals root and each other entry names its parent; occurrence indices preserve aliases and repeated tables. |
| ownership | The value owns its parent vector; it borrows no metadata nodes after enumerate returns. |
| failure | The aggregate type validates nothing when caller-constructed; enumerate creates it only from a checked and internally validated fragment. |
| cost | The struct itself performs no work; each oriented output owns an O(atom-count) parent vector, counted as explicit cells by orient. |
| Design | [include/crown/planner/meta.hpp](../../../../../../include/crown/planner/meta.hpp), [docs/meta_decompositions.md](../../../../../meta_decompositions.md), P3v2 §4.2, Algorithm 2; Appendix C.1.1, Algorithm 5, [exact paper reference](https://arxiv.org/html/2603.15465v2), [docs/meta_candidate_adapter.md](../../../../../meta_candidate_adapter.md) |

## B0003

[Lines 8–13](../../../../../../include/crown/planner/meta_join_trees.hpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L8-L13:sha256:55536d1ced74545516ac410b63cc5ad6e2b07f1b4d8af724b6b9ecbfdd9effc9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set independent admission grants for metadata checking, fragment expansion, and returned rooted-tree count. |
| inputs / outputs | metadata is passed to meta::check; work, fragments, and cells bound selected enumerator counters; output_trees caps oriented results. all_roots defaults true; false returns one canonical root0 representative per undirected tree. |
| invariants | These grants are independent: check usage is reported in metadata, while EnumerationUsage reports the other four counters. |
| ownership | enumerate receives this limits value by value and retains no caller-owned grant object. |
| failure | A reached enumerator grant produces its matching EnumerationStop; metadata check exhaustion maps to metadata_limit. Allocation exceptions propagate. |
| cost | Defaults are finite. work counts selected checkpoints, fragments counts cumulative unique Family insertions, and cells counts cumulative charged scratch/container entries; none measures allocator bytes or total CPU. |
| Design | [include/crown/planner/meta.hpp](../../../../../../include/crown/planner/meta.hpp), [docs/meta_decompositions.md](../../../../../meta_decompositions.md), P3v2 §4.2, Algorithm 2; Appendix C.1.1, Algorithm 5, [exact paper reference](https://arxiv.org/html/2603.15465v2), [docs/meta_candidate_adapter.md](../../../../../meta_candidate_adapter.md) |

## B0004

[Lines 14–17](../../../../../../include/crown/planner/meta_join_trees.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L17:sha256:a4c90e82762ab1f47cc64718185e6053184c2212b50fb305468ea334d13b7a7a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report the actual charged work, fragment insertions, explicit cells, and rooted outputs consumed by one call. |
| inputs / outputs | enumerate fills usage as it advances; metadata-check work is returned separately through Enumeration.metadata.usage. |
| invariants | Counters describe this invocation only, including a stopped invocation; they are not reservations or estimates of remaining work. |
| ownership | The caller receives the counters by value in Enumeration; no shared counter survives the call. |
| failure | Counter values remain available for controlled stop results; an allocation exception prevents returning Enumeration. |
| cost | Updating a counter is constant-time; the units are the selected Budget checkpoints and cell/fragment admission rules, not all machine operations. |
| Design | [include/crown/planner/meta.hpp](../../../../../../include/crown/planner/meta.hpp), [docs/meta_decompositions.md](../../../../../meta_decompositions.md), [docs/meta_candidate_adapter.md](../../../../../meta_candidate_adapter.md) |

## B0005

[Lines 18–21](../../../../../../include/crown/planner/meta_join_trees.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L21:sha256:4a2054e9d654d557ea1f7a4c0198a5870ddcfa73a387f919f0b2097248e9b9da
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Distinguish completed traversal, rejected metadata, budget stops, output truncation, and an internal expansion inconsistency. |
| inputs / outputs | Enumeration.stop is complete, invalid_metadata, metadata_limit, work_limit, fragment_limit, cell_limit, output_limit, or invalid_expansion. |
| invariants | complete means this implementation reached the end of its traversal; this status alone is not an independently proved completeness theorem for all mathematical join trees. noncanonical_metadata explicitly rejects a structurally checked graph that violates Algorithm1 minor-first parenting; it is not a claim the query has no join tree. |
| ownership | The enum is a value-only status shared with the caller; it owns no resources. |
| failure | Non-complete values are explicit stop reasons. Allocation failures are exceptions and do not become enum values. |
| cost | No per-status work is performed; the reason records which bounded traversal branch stopped. |
| Design | [docs/meta_decompositions.md](../../../../../meta_decompositions.md), P3v2 §4.2, Algorithm 2; Appendix C.1.1, Algorithm 5, [exact paper reference](https://arxiv.org/html/2603.15465v2), [build/verification/v55-meta-primary-review-v1/REVIEW.md](../../../../../../build/verification/v55-meta-primary-review-v1/REVIEW.md), [docs/meta_candidate_adapter.md](../../../../../meta_candidate_adapter.md) |

## B0006

[Lines 22–28](../../../../../../include/crown/planner/meta_join_trees.hpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L28:sha256:163724e492a2656aab2fc1c31465d65487d1f2924203b6663f5ba562ebbb6c24
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return metadata-check evidence, enumerator usage, a stop reason, and the rooted ordinary trees produced so far. |
| inputs / outputs | metadata is the existing Check result; usage counts enumerator work; trees contains JoinTree values. |
| invariants | An invalid metadata check returns no trees. Limit stops expose only trees completed before the stop; a stop while building subtree families may return an empty vector. The batch is not resumable. |
| ownership | Enumeration owns its returned vector and each parent vector. Internal fragments and families are destroyed when enumerate exits. |
| failure | Invalid metadata and controlled budget/internal stops are returned. std::bad_alloc and other uncaught allocation failures propagate. |
| cost | Retained output is proportional to the number of returned trees times atom count, but output_trees counts trees rather than vector bytes or capacity. |
| Design | [include/crown/planner/meta.hpp](../../../../../../include/crown/planner/meta.hpp), [docs/meta_decompositions.md](../../../../../meta_decompositions.md), P3v2 §4.2, Algorithm 2; Appendix C.1.1, Algorithm 5, [exact paper reference](https://arxiv.org/html/2603.15465v2), [docs/meta_candidate_adapter.md](../../../../../meta_candidate_adapter.md) |

## B0007

[Lines 29–45](../../../../../../include/crown/planner/meta_join_trees.hpp#L29); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L45:sha256:a59261d5693fbd4a3cad0adb15bfcfffd71e62877cc9e69dc4f5b2e7093a8960
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the cold batch enumerator and document the reviewed P3v2 Algorithm 2/5 translation boundary. |
| inputs / outputs | enumerate borrows catalog, query, and decomposition for the call, takes finite EnumerationLimits by value, and returns an owning Enumeration. |
| invariants | It first calls meta::check; completed ordinary fragments are independently checked and each physical occurrence is rooted. Reviewed placeholder, Cartesian-composition, and rerooting repairs do not by themselves establish the paper's nonduplication or delay theorem. Algorithm1 canonical minor-first parenting is required beyond literal Definition4.3; full-root versus canonical-root completion is explicit. No general completeness claim is made for rearranged noncanonical DTOs. |
| ownership | Inputs are not retained or mutated by this interface; only the result survives the call. Each call starts from the beginning. |
| failure | Metadata and resource stops are returned; OOM/admission exceptions propagate. The result is an ordinary join-tree family, not head/guard/height authority for CROWN lifting. |
| cost | The counters cover selected work and cumulative explicit entries only. Allocator capacity, every primitive comparison/sort operation, total CPU, paper delay, and incremental maintenance are outside this contract. |
| Design | [docs/meta_decompositions.md](../../../../../meta_decompositions.md), P3v2 §4.2, Algorithm 2; Appendix C.1.1, Algorithm 5, P3v2 Appendix C.1.2, Prüfer-sequence enumeration; C.1.3, rerootings, [exact paper reference](https://arxiv.org/html/2603.15465v2), [build/verification/v55-meta-primary-review-v1/REVIEW.md](../../../../../../build/verification/v55-meta-primary-review-v1/REVIEW.md), [docs/meta_candidate_adapter.md](../../../../../meta_candidate_adapter.md) |
