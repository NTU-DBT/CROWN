# `src/planner/meta_join_trees.cpp` — block usage map

[Source](../../../../../src/planner/meta_join_trees.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Recognize structural query classes, check a proposed CROWN tree and lower checked structure into physical metadata.

Snapshot SHA-256: `d8607492096e92ee22494a22754d7bfa66349411f67af3b0cd074259cea12aa6`. 328 lines partitioned into 27 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [planner](../../../subsystem_contracts.md#planner). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_plans.md](../../../../tree_plans.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/planner/meta_join_trees.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 9–9](../../../../../src/planner/meta_join_trees.cpp#L9) | Type/record definition: struct Halt |  · [reviewed contract](#b0002) |
| [B0003 · 10–21](../../../../../src/planner/meta_join_trees.cpp#L10) | Type/record definition: struct Budget |  · [reviewed contract](#b0003) |
| [B0004 · 22–22](../../../../../src/planner/meta_join_trees.cpp#L22) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0004) |
| [B0005 · 23–27](../../../../../src/planner/meta_join_trees.cpp#L23) | Type/record definition: struct Fragment | source comment (unverified): // Own external parent, never a physical root. · [reviewed contract](#b0005) |
| [B0006 · 28–36](../../../../../src/planner/meta_join_trees.cpp#L28) | Type/record definition: struct Less | returns a.dummy &lt; c.dummy; a.vertices &lt; c.vertices · [reviewed contract](#b0006) |
| [B0007 · 37–37](../../../../../src/planner/meta_join_trees.cpp#L37) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0007) |
| [B0008 · 38–41](../../../../../src/planner/meta_join_trees.cpp#L38) | Callable definition: bool contains(const Scope& large,const Scope& small,Budget& b) | calls step, std::includes, begin, end; returns std::includes(large.begin(),large.end(),small.begin(),small.end()) · [reviewed contract](#b0008) |
| [B0009 · 42–44](../../../../../src/planner/meta_join_trees.cpp#L42) | Callable definition: void edge(Fragment& f,std::size_t a,std::size_t c,Budget& b) | calls step, cells, emplace_back, std::min; growth emplace_back · [reviewed contract](#b0009) |
| [B0010 · 45–49](../../../../../src/planner/meta_join_trees.cpp#L45) | Callable definition: void merge(Fragment& into,const Fragment& from,Budget& b) | calls step, cells, size, insert; growth insert; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 50–52](../../../../../src/planner/meta_join_trees.cpp#L50) | Callable definition: Fragment copy(const Fragment& f,Budget& b) | calls merge; returns result · [reviewed contract](#b0011) |
| [B0012 · 53–61](../../../../../src/planner/meta_join_trees.cpp#L53) | Callable definition: void store(Family& family,Fragment f,Budget& b) | calls step, std::sort, begin, end; growth insert; source comment (unverified): // One owning set entry, not a graph plus a duplicate retained key graph. · [reviewed contract](#b0012) |
| [B0013 · 62–63](../../../../../src/planner/meta_join_trees.cpp#L62) | Explanatory comments or spacing. | source comment (unverified): // Mixed-radix Cartesian product; no fixed-width masks or product-size overflow. · [reviewed contract](#b0013) |
| [B0014 · 64–73](../../../../../src/planner/meta_join_trees.cpp#L64) | Callable definition: template&lt;class F&gt; void product(const std::vector&lt;std::size_t&gt;& sizes,Budget& b,F visit) | calls step, cells, size, digits; 3 loop sites; source comment (unverified): // Mixed-radix Cartesian product; no fixed-width masks or product-size overflow. · [reviewed contract](#b0014) |
| [B0015 · 74–81](../../../../../src/planner/meta_join_trees.cpp#L74) | Callable definition: std::vector&lt;std::size_t&gt; entries(const Fragment& f,const Scope& key, const Decomposition& m,Budget& b) | calls contains, cells, push_back; returns result; growth push_back; 1 loop sites · [reviewed contract](#b0015) |
| [B0016 · 82–82](../../../../../src/planner/meta_join_trees.cpp#L82) | Explanatory comments or spacing. | source comment (unverified): // Standard labelled Prüfer decoding, independent of the erroneous source indices. · [reviewed contract](#b0016) |
| [B0017 · 83–100](../../../../../src/planner/meta_join_trees.cpp#L83) | Callable definition: std::vector&lt;Edge&gt; skeleton(const std::vector&lt;std::size_t&gt;& code,std::size_t n,Budget& b) | calls cells, degree, step, emplace_back; returns result; growth emplace_back; 4 loop sites; source comment (unverified): // Standard labelled Prüfer decoding, independent of the erroneous source indices. · [reviewed contract](#b0017) |
| [B0018 · 101–102](../../../../../src/planner/meta_join_trees.cpp#L101) | Explanatory comments or spacing. | source comment (unverified): // Remove ONLY the distinguished external parent, keeping its original neighbor · [reviewed contract](#b0018) |
| [B0019 · 103–123](../../../../../src/planner/meta_join_trees.cpp#L103) | Callable definition: std::vector&lt;Fragment&gt; branches(const Fragment& f,Budget& b) | calls step, cells, push_back, size; returns result; growth insert, push_back; 3 loop sites; source comment (unverified): // Remove ONLY the distinguished external parent, keeping its original neighbor · [reviewed contract](#b0019) |
| [B0020 · 124–151](../../../../../src/planner/meta_join_trees.cpp#L124) | Callable definition: Family proper(const Family& hosts,const Family& children,const Scope& key, const Decomposition& m,Budget& b) | calls step, branches, entries, cells; returns next; 6 loop sites; source comment (unverified): // Freeze ORIGINAL host. · [reviewed contract](#b0020) |
| [B0021 · 152–203](../../../../../src/planner/meta_join_trees.cpp#L152) | Callable definition: Family minor(std::size_t v,const std::vector&lt;std::size_t&gt;& origin, const std::vector&lt;Family&gt;& families,const Decomposition& m,Bud… | calls size, step, emplace_back, cells; returns result; growth emplace_back, push_back; 7 loop sites · [reviewed contract](#b0021) |
| [B0022 · 204–205](../../../../../src/planner/meta_join_trees.cpp#L204) | Explanatory comments or spacing. | source comment (unverified): // Acyclicity/connectivity and variable-induced edge counts independently check · [reviewed contract](#b0022) |
| [B0023 · 206–239](../../../../../src/planner/meta_join_trees.cpp#L206) | Callable definition: bool ordinary(const Fragment& f,const Decomposition& m,std::size_t n,Budget& b) | calls step, size, cells, covered; returns false; false; growth insert, push_back; 8 loop sites; source comment (unverified): // Acyclicity/connectivity and variable-induced edge counts independently check · [reviewed contract](#b0023) |
| [B0024 · 240–253](../../../../../src/planner/meta_join_trees.cpp#L240) | Callable definition: JoinTree orient(const Fragment& f,std::size_t root,const Decomposition& m,std::size_t n,Budget& b) | calls cells, assign, size, step; returns result; growth push_back; 2 loop sites · [reviewed contract](#b0024) |
| [B0025 · 254–255](../../../../../src/planner/meta_join_trees.cpp#L254) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0025) |
| [B0026 · 256–327](../../../../../src/planner/meta_join_trees.cpp#L256) | Callable definition: Enumeration enumerate(const Catalog& catalog,const Query& query,const Decomposition& m, EnumerationLimits limits) | calls check, size, step, children; guard out.metadata = check(catalog,query,m,limits.metadata);; returns out; out; growth emplace_back, push_back, reserve; 13 loop sites; source comment (unverified): // Algorithm1 lines17–18 place every equal-interface node at its unique · [reviewed contract](#b0026) |
| [B0027 · 328–328](../../../../../src/planner/meta_join_trees.cpp#L328) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::meta · [reviewed contract](#b0027) |

## B0001

[Lines 1–8](../../../../../src/planner/meta_join_trees.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:3eea4e29bc2b6c4e05cc64b90de3065b7b6a1d0643aa177769f612200f9a1332
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the implementation to its public declaration and local standard-library helpers, then open implementation namespaces. |
| inputs / outputs | The public header supplies enumeration and metadata types; algorithm, numeric, set, and utility headers supply local operations. |
| invariants | The anonymous namespace below keeps fragment machinery private; this block creates no static cache or runtime owner. |
| ownership | Includes and namespace openings retain no query or enumeration state. |
| failure | Missing or incompatible declarations are compile-time failures; there is no runtime path here. |
| cost | Preprocessing and compilation only. |
| Design | [include/crown/planner/meta_join_trees.hpp](../../../../../include/crown/planner/meta_join_trees.hpp), [include/crown/planner/meta.hpp](../../../../../include/crown/planner/meta.hpp), [docs/meta_decompositions.md](../../../../meta_decompositions.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0002

[Lines 9–9](../../../../../src/planner/meta_join_trees.cpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L9-L9:sha256:9768db641499b7390d5ab5d94c3486f35e49f6b4e0d7f0ce4cde03cb5d9c310a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry a private controlled-stop reason through nested expansion helpers. |
| inputs / outputs | Halt contains one EnumerationStop and is thrown when a Budget grant or internal expansion check stops traversal. |
| invariants | Only enumerate catches Halt; it converts the reason to the returned stop while preserving the usage counters. |
| ownership | The exception value owns no graph data; each unwinding frame releases local containers by RAII. |
| failure | This is private control flow, not a public exception contract. Other exceptions, including allocation failure, remain uncaught. |
| cost | Throw/catch and small reason-value work; the selected charge is made by the caller before throwing. |
| Design | [include/crown/planner/meta_join_trees.hpp](../../../../../include/crown/planner/meta_join_trees.hpp), [docs/meta_decompositions.md](../../../../meta_decompositions.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0003

[Lines 10–21](../../../../../src/planner/meta_join_trees.cpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L10-L21:sha256:08f74f2fc402c546bd970f3c59cf8b31f19867acec2578783ebf68d0ea5f2266
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply finite selected-work and explicit-cell grants shared by every nested enumeration helper. |
| inputs / outputs | Budget borrows EnumerationLimits and EnumerationUsage; step charges one selected checkpoint, and cells(count) charges count explicit entries. |
| invariants | Each charge checks its corresponding grant before incrementing; cells uses the remaining-grant difference so an admitted count cannot pass the cap. |
| ownership | The references point to enumerate's stack-owned limits and output usage and remain valid only for that call. |
| failure | Exhaustion throws private Halt with work_limit or cell_limit. Allocation failures elsewhere are not converted here. |
| cost | Each step is O(1); cells(count) charges count in O(1). These charges do not meter allocator capacity, comparison internals, or total CPU. |
| Design | [include/crown/planner/meta_join_trees.hpp](../../../../../include/crown/planner/meta_join_trees.hpp), [docs/meta_decompositions.md](../../../../meta_decompositions.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0004

[Lines 22–22](../../../../../src/planner/meta_join_trees.cpp#L22); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L22:sha256:82f52318dbecc750a7cf70cda1abe7a422a6375c20d3fbd26447916b671e886a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name the canonical undirected edge representation used inside fragments. |
| inputs / outputs | Edge is a pair of meta-decomposition node indices; edge() inserts endpoints in increasing order. |
| invariants | This internal ID space is not the public atom-occurrence index space; orient() maps physical nodes to occurrences. |
| ownership | The alias creates no storage; each use is stored in an owning Fragment edge vector. |
| failure | Invalid endpoint use is prevented by validated metadata and internally generated blocks; the alias performs no check. |
| cost | No runtime work beyond the underlying pair operations. |
| Design | [include/crown/planner/meta_join_trees.hpp](../../../../../include/crown/planner/meta_join_trees.hpp), [include/crown/planner/meta.hpp](../../../../../include/crown/planner/meta.hpp), [docs/meta_decompositions.md](../../../../meta_decompositions.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0005

[Lines 23–27](../../../../../src/planner/meta_join_trees.cpp#L23); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L27:sha256:be919af02954e821e183e2146915f50b63747a812c35650ca69d940c2c05d1d3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent a partial undirected tree fragment over metadata-node IDs, optionally tagged with its external parent. |
| inputs / outputs | vertices and edges hold fragment contents; dummy identifies the one temporary external-parent node when present. |
| invariants | A dummy is a structural placeholder, not an input occurrence or an output join-tree vertex; completed ordinary roots have no dummy. |
| ownership | Each fragment owns its vectors and optional tag. Families own stored fragments; temporary fragments are moved or copied within the call. |
| failure | Vector allocation failures propagate. Semantic malformed-fragment detection occurs in expansion/check helpers, not in this aggregate. |
| cost | Storage grows with explicit vertex and edge entries; cells are charged at selected creation, copy, and merge sites, not per allocated byte. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), P3v2 §4.2, Algorithm 2; Appendix C.1.1, Algorithm 5, P3v2 Appendix C.1.2, Prüfer-sequence enumeration; C.1.3, rerootings, [exact paper reference](https://arxiv.org/html/2603.15465v2), [build/verification/v55-meta-primary-review-v1/REVIEW.md](../../../../../build/verification/v55-meta-primary-review-v1/REVIEW.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0006

[Lines 28–36](../../../../../src/planner/meta_join_trees.cpp#L28); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L28-L36:sha256:840d9e371ca7db2af7ec91742eefb97dec24b64b60c9395a8f79d3ad3a1c1a18
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Order partial fragments for deterministic set deduplication and membership lookup. |
| inputs / outputs | Less compares dummy tag, then sorted vertex IDs, then sorted canonical edges; its Budget pointer charges comparisons. |
| invariants | Stored keys are sorted before set insertion, so equality of this tuple identifies duplicate fragments without dropping occurrence IDs. |
| ownership | The comparator borrows the call-local Budget; it must not escape the Family that uses it. |
| failure | A work-limit Halt can arise during set comparison and unwinds to enumerate; comparison allocation/other exceptions propagate. |
| cost | One work step is charged per comparator invocation, not per element inspected by vector lexicographic comparison. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), P3v2 §4.2, Algorithm 2; Appendix C.1.1, Algorithm 5, P3v2 Appendix C.1.2, Prüfer-sequence enumeration; C.1.3, rerootings, [exact paper reference](https://arxiv.org/html/2603.15465v2), [build/verification/v55-meta-primary-review-v1/REVIEW.md](../../../../../build/verification/v55-meta-primary-review-v1/REVIEW.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0007

[Lines 37–37](../../../../../src/planner/meta_join_trees.cpp#L37); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L37:sha256:5df63c3b5509c00cf5c54081e587db01d64ba91496bcf53e588aa1d85103da70
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define a family as a comparator-ordered set of unique partial fragments. |
| inputs / outputs | Family stores Fragment keys using Less and the active Budget. |
| invariants | Deduplication is local to each Family; the same shape in a different recursion node is a distinct admission event. |
| ownership | The set owns each stored key until it is cleared or destroyed; the comparator only borrows Budget. |
| failure | Set allocation exceptions propagate; work-limit stops can propagate from Less. |
| cost | Each successful new insertion is charged to the cumulative fragments counter by store; live set size and allocator bytes are not the same measure. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), P3v2 §4.2, Algorithm 2; Appendix C.1.1, Algorithm 5, P3v2 Appendix C.1.2, Prüfer-sequence enumeration; C.1.3, rerootings, [exact paper reference](https://arxiv.org/html/2603.15465v2), [build/verification/v55-meta-primary-review-v1/REVIEW.md](../../../../../build/verification/v55-meta-primary-review-v1/REVIEW.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0008

[Lines 38–41](../../../../../src/planner/meta_join_trees.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L41:sha256:fe26c04c910403fb0f1fcc636098f2e93da091dddbd3ecab342b5a11589db687
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test whether one sorted metadata scope contains another scope. |
| inputs / outputs | contains receives large and small Scope references and returns std::includes(large, small). |
| invariants | Scope ordering is the ordered-set relation supplied by the metadata types; the result is a subset predicate for interface attachment. |
| ownership | Both scopes and Budget are borrowed; no result storage is retained. |
| failure | A charged work stop propagates as Halt; invalid scope representation is outside this helper's contract. |
| cost | One selected work step per call; individual element comparisons in std::includes are not separately charged. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), P3v2 §4.2, Algorithm 2; Appendix C.1.1, Algorithm 5, P3v2 Appendix C.1.2, Prüfer-sequence enumeration; C.1.3, rerootings, [exact paper reference](https://arxiv.org/html/2603.15465v2), [build/verification/v55-meta-primary-review-v1/REVIEW.md](../../../../../build/verification/v55-meta-primary-review-v1/REVIEW.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0009

[Lines 42–44](../../../../../src/planner/meta_join_trees.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L44:sha256:14533b1691a6894fb7229a28283e1cda64374dc25638519c4b8aac171ba4b00f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one normalized undirected edge to a partial fragment. |
| inputs / outputs | edge accepts a Fragment and two metadata-node IDs and appends (min(a,c), max(a,c)). |
| invariants | Endpoint order is canonical; duplicate and tree-shape validation are deferred to family deduplication or ordinary(). |
| ownership | The fragment owns the appended pair; Budget is borrowed for the call. |
| failure | Work/cell exhaustion propagates as Halt; vector allocation failure propagates unchanged. |
| cost | Charges one work step and two cells before appending; cells do not describe vector capacity or allocator bytes. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), P3v2 §4.2, Algorithm 2; Appendix C.1.1, Algorithm 5, P3v2 Appendix C.1.2, Prüfer-sequence enumeration; C.1.3, rerootings, [exact paper reference](https://arxiv.org/html/2603.15465v2), [build/verification/v55-meta-primary-review-v1/REVIEW.md](../../../../../build/verification/v55-meta-primary-review-v1/REVIEW.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0010

[Lines 45–49](../../../../../src/planner/meta_join_trees.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L49:sha256:15247f40d939cca8672f1db863b6178552e95078026fe1007cbeed5d7881e274
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Merge a source fragment's vertices and edges into an owning destination fragment. |
| inputs / outputs | merge appends every source vertex, then routes each source edge through edge() for canonical storage and charging. |
| invariants | The destination may later be sorted/deduplicated; merge itself does not reject overlap or validate a tree. |
| ownership | Source is borrowed; destination owns appended entries. The source remains available to its family. |
| failure | Any work/cell Halt or allocation failure interrupts the local construction and unwinds to enumerate. |
| cost | One merge work step plus V cells for copied vertices; each copied edge adds one work step and two cells. Vector insert/capacity and scalar-width CPU costs are separate. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), P3v2 §4.2, Algorithm 2; Appendix C.1.1, Algorithm 5, P3v2 Appendix C.1.2, Prüfer-sequence enumeration; C.1.3, rerootings, [exact paper reference](https://arxiv.org/html/2603.15465v2), [build/verification/v55-meta-primary-review-v1/REVIEW.md](../../../../../build/verification/v55-meta-primary-review-v1/REVIEW.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0011

[Lines 50–52](../../../../../src/planner/meta_join_trees.cpp#L50); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L50-L52:sha256:7e0c593ccf4fff59bab491936b3779d1957fc862247ced5125a5187ad9f7ac0a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an owning fragment copy while preserving its optional external-parent tag. |
| inputs / outputs | copy takes a const Fragment reference, copies dummy, merges vertices and edges into a new result, and returns it. |
| invariants | The source is unchanged; copied endpoints are canonicalized through edge(). |
| ownership | The returned Fragment owns fresh vectors; the source and Budget are borrowed only during the call. |
| failure | Budget exhaustion uses private Halt; allocation failure propagates. |
| cost | One merge checkpoint, V vertex cells and one checkpoint/two cells per copied edge; no separate charge per vertex scan and no allocator-byte guarantee. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), P3v2 §4.2, Algorithm 2; Appendix C.1.1, Algorithm 5, P3v2 Appendix C.1.2, Prüfer-sequence enumeration; C.1.3, rerootings, [exact paper reference](https://arxiv.org/html/2603.15465v2), [build/verification/v55-meta-primary-review-v1/REVIEW.md](../../../../../build/verification/v55-meta-primary-review-v1/REVIEW.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0012

[Lines 53–61](../../../../../src/planner/meta_join_trees.cpp#L53); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L53-L61:sha256:2e4bb91e00f6cf13ccaf1536baf3b8f86283913d16bbce9b8c7e5e9d0741ca69
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Canonicalize a fragment and admit it once into a destination Family. |
| inputs / outputs | store sorts vertex/edge vectors, performs set membership, and inserts a moved key only when it is new. |
| invariants | Duplicate keys consume no fragment admission; a new key is rejected before insertion when the cumulative fragment grant is already reached. |
| ownership | On a new admission the Family owns the moved Fragment; on duplicate the local value is destroyed. |
| failure | fragment_limit or work-limit Halt stops enumeration; sorting and set/vector allocation exceptions propagate. |
| cost | Charges one step directly, plus comparator steps from find/insert. Sorting comparisons and vector capacities are not individually charged; each successful unique insert increments cumulative fragments once. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), P3v2 §4.2, Algorithm 2; Appendix C.1.1, Algorithm 5, P3v2 Appendix C.1.2, Prüfer-sequence enumeration; C.1.3, rerootings, [exact paper reference](https://arxiv.org/html/2603.15465v2), [build/verification/v55-meta-primary-review-v1/REVIEW.md](../../../../../build/verification/v55-meta-primary-review-v1/REVIEW.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0013

[Lines 62–63](../../../../../src/planner/meta_join_trees.cpp#L62); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L62-L63:sha256:309442927eeb02903eaad2cf0c696957a07e1ad2abd4554f3342fe1370854d00
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the product helper's mixed-radix traversal and the two boundary cases needed by empty compositions. |
| inputs / outputs | The following helper receives one choice count per dimension and invokes a visitor for each index tuple. |
| invariants | An empty product has one empty tuple; if any dimension has zero choices, the product has no tuples. |
| ownership | This comment introduces no state or ownership. |
| failure | No runtime failure path; actual budget and allocation stops are in product(). |
| cost | The comment states semantics only. Product enumeration is combinatorial and governed by finite grants, not a delay claim. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), P3v2 §4.2, Algorithm 2; Appendix C.1.1, Algorithm 5, P3v2 Appendix C.1.2, Prüfer-sequence enumeration; C.1.3, rerootings, [exact paper reference](https://arxiv.org/html/2603.15465v2), [build/verification/v55-meta-primary-review-v1/REVIEW.md](../../../../../build/verification/v55-meta-primary-review-v1/REVIEW.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0014

[Lines 64–73](../../../../../src/planner/meta_join_trees.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L73:sha256:6c1aec1c2196541a96e78b27e9687dab7b86e318dadcedb07a999c43c8b6934c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Visit the Cartesian product of choice dimensions using a mixed-radix digit vector. |
| inputs / outputs | sizes supplies each dimension's cardinality; visit receives the current vector of zero-based choices. |
| invariants | A zero-sized dimension returns without visits; no dimensions call visit once with an empty vector. Increment order is deterministic and uses no fixed-width product-size calculation. |
| ownership | The helper owns digits during traversal and borrows sizes, Budget, and the visitor; callback captures must remain valid for the call. |
| failure | work/cell Halt interrupts visitation; vector or callback exceptions propagate. |
| cost | Charges one step per dimension check, digit-vector length cells, one step per tuple, and steps for mixed-radix increments. It does not precompute or bound product cardinality. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), P3v2 §4.2, Algorithm 2; Appendix C.1.1, Algorithm 5, P3v2 Appendix C.1.2, Prüfer-sequence enumeration; C.1.3, rerootings, [exact paper reference](https://arxiv.org/html/2603.15465v2), [build/verification/v55-meta-primary-review-v1/REVIEW.md](../../../../../build/verification/v55-meta-primary-review-v1/REVIEW.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0015

[Lines 74–81](../../../../../src/planner/meta_join_trees.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L74-L81:sha256:32cf415baa0489e9602358247fb65a032fbe4dc643b195dc847c601f91f87306
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find the fragment's metadata vertices whose scopes contain an attachment key. |
| inputs / outputs | entries scans fragment vertex IDs, tests m.nodes\[v\].scope ⊇ key, and returns matching metadata-node IDs. |
| invariants | The result preserves the fragment's sorted vertex order; it does not add grafted neighbors to the source fragment. |
| ownership | Fragment, key, decomposition, and Budget are borrowed; the returned vector owns its IDs. |
| failure | work/cell Halt or result-vector allocation failure stops the current construction. |
| cost | Each candidate invokes contains (one selected step); each match charges one cell. Scope element comparisons and capacity are not metered individually. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), P3v2 §4.2, Algorithm 2; Appendix C.1.1, Algorithm 5, P3v2 Appendix C.1.2, Prüfer-sequence enumeration; C.1.3, rerootings, [exact paper reference](https://arxiv.org/html/2603.15465v2), [build/verification/v55-meta-primary-review-v1/REVIEW.md](../../../../../build/verification/v55-meta-primary-review-v1/REVIEW.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0016

[Lines 82–82](../../../../../src/planner/meta_join_trees.cpp#L82); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L82-L82:sha256:0b616336436ef99d7aaa7d5861b5405c77b76b8856217af86c852fb42a61f6e6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Record that skeleton generation uses labelled Prüfer decoding rather than the paper listing's inconsistent indices. |
| inputs / outputs | The next helper maps a generated sequence over local block labels to undirected skeleton edges. |
| invariants | Labels are zero-based local indices; caller-generated values lie in \[0,n). This repair is an implementation choice, not a proof of the full enumeration theorem. |
| ownership | The comment owns no data. |
| failure | Malformed internal sequences are reported by invalid_expansion; ordinary allocation failures propagate. |
| cost | No execution cost from the comment. Prüfer code length is n−2; actual work is charged in skeleton(). |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), P3v2 Appendix C.1.2, Prüfer-sequence enumeration; C.1.3, rerootings, [exact paper reference](https://arxiv.org/html/2603.15465v2), [build/verification/v55-meta-primary-review-v1/REVIEW.md](../../../../../build/verification/v55-meta-primary-review-v1/REVIEW.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0017

[Lines 83–100](../../../../../src/planner/meta_join_trees.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L100:sha256:372121447f25e8247802842cd12d9e7f444b19bf6e22a086975e15a45184acb4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Decode one labelled Prüfer sequence into a canonical undirected tree skeleton over n local block labels. |
| inputs / outputs | code has n−2 labels for generated nontrivial cases; the result is a vector of local-index Edge values. |
| invariants | Degree counts and leaf selection follow the standard labelled decoding; endpoints are block indices, not metadata node IDs until callers resolve blocks. |
| ownership | The helper owns degree and result vectors and borrows code and Budget; its result is moved into the caller's local expansion. |
| failure | An impossible leaf state returns invalid_expansion via Halt; work/cell stops and allocation exceptions propagate. |
| cost | Admit n degree cells and two cells per appended edge. Degree initialization, leaf scans and edge processing have selected checkpoints; vector capacity/library CPU remain outside a total bound. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), P3v2 Appendix C.1.2, Prüfer-sequence enumeration; C.1.3, rerootings, [exact paper reference](https://arxiv.org/html/2603.15465v2), [build/verification/v55-meta-primary-review-v1/REVIEW.md](../../../../../build/verification/v55-meta-primary-review-v1/REVIEW.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0018

[Lines 101–102](../../../../../src/planner/meta_join_trees.cpp#L101); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L101-L102:sha256:45caed01b9e31a3c6dd6bc32c45a44fed7cde379da56a5aa2d01250e7602a072
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the typed-placeholder rule used when a child fragment has an external parent. |
| inputs / outputs | branches() removes only the distinguished dummy and preserves its original neighbor as each branch's entry vertex. |
| invariants | The dummy is never treated as a physical occurrence or arbitrarily moved to a different root; each resulting branch keeps its entry at vertices.front(). |
| ownership | This comment owns no data; the helper returns owning branch fragments. |
| failure | No runtime path here. Malformed placeholder assumptions are guarded by the surrounding recursion invariant, not this comment. |
| cost | No comment work. Branch construction charges selected traversal and explicit cells in branches(). |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), P3v2 §4.2, Algorithm 2; Appendix C.1.1, Algorithm 5, P3v2 Appendix C.1.2, Prüfer-sequence enumeration; C.1.3, rerootings, [exact paper reference](https://arxiv.org/html/2603.15465v2), [build/verification/v55-meta-primary-review-v1/REVIEW.md](../../../../../build/verification/v55-meta-primary-review-v1/REVIEW.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0019

[Lines 103–123](../../../../../src/planner/meta_join_trees.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L103-L123:sha256:07354925af7bfdc0f915970842626107d117e2de374ce8f3a63d00475e9756c5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Remove a fragment's distinguished external-parent placeholder and split the remaining tree into entry-rooted branches. |
| inputs / outputs | branches scans edges incident to f.dummy; for each neighbor it walks that component and returns a Fragment whose first vertex is the original neighbor. |
| invariants | Only the placeholder is removed; physical metadata IDs and branch edges remain. The helper is called only for dummy-tagged fragments. |
| ownership | The result vector owns each branch; the source fragment and Budget are borrowed. |
| failure | A work/cell Halt or allocation exception aborts the partial branch result and unwinds the batch. |
| cost | Charges edge scans and visits as selected steps and explicit seen/vertex/edge entries as cells. std::set node bytes and allocator capacity are not counted. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), P3v2 §4.2, Algorithm 2; Appendix C.1.1, Algorithm 5, P3v2 Appendix C.1.2, Prüfer-sequence enumeration; C.1.3, rerootings, [exact paper reference](https://arxiv.org/html/2603.15465v2), [build/verification/v55-meta-primary-review-v1/REVIEW.md](../../../../../build/verification/v55-meta-primary-review-v1/REVIEW.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0020

[Lines 124–151](../../../../../src/planner/meta_join_trees.cpp#L124); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L124-L151:sha256:2a9a049f34c8737fc164905f666d9328ff25685a36813c1452df53262c4bd810
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Attach one child Family to each host Family at the child's interface, including all branch attachments for a dummy child. |
| inputs / outputs | For ordinary children it chooses eligible host and child entry vertices; for a dummy child it decomposes into branches and takes a Cartesian choice of eligible original-host entries. |
| invariants | Eligibility for a dummy child's branches is frozen from the original host; for a later proper child, hosts already contain prior proper grafts, allowing re-branching. New fragments are deduplicated in a fresh Family. |
| ownership | Inputs are borrowed sets; returned Family owns its output fragments. Temporary branch/choice vectors live only during this call. |
| failure | Budget limits throw Halt; vector/set allocation errors propagate. An empty eligible set yields no product results rather than an invented attachment. |
| cost | Nested family, entry, and Cartesian enumeration can grow exponentially; work, fragment, and cell grants stop it. These are selected charges, not a polynomial or delay guarantee. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), P3v2 §4.2, Algorithm 2; Appendix C.1.1, Algorithm 5, P3v2 Appendix C.1.2, Prüfer-sequence enumeration; C.1.3, rerootings, [exact paper reference](https://arxiv.org/html/2603.15465v2), [build/verification/v55-meta-primary-review-v1/REVIEW.md](../../../../../build/verification/v55-meta-primary-review-v1/REVIEW.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0021

[Lines 152–203](../../../../../src/planner/meta_join_trees.cpp#L152); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L152-L203:sha256:71986b5579325a0d580462bf3e566a87cccfb6672d6fa826a3a0794c4ce96d65
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a minor's partial host family by combining origin-child fragments through every labelled skeleton and legal endpoint assignment. |
| inputs / outputs | v and origin identify a minor and its origin children; families supplies already-expanded child choices; m supplies scopes. A non-root minor with scope equal to interface receives a typed dummy placeholder. |
| invariants | Origin must contain at least two children; origin fragments must be ordinary. The top-level root has no external-parent dummy. Every skeleton edge chooses endpoints from the two original blocks' vertices containing the minor scope; all edge endpoint choices are combined as a Cartesian product. |
| ownership | Child options are borrowed by pointer while families remain alive; the result Family owns constructed fragments. The placeholder is local to this synchronous call. |
| failure | Missing origin children, an unexpected child dummy, or invalid skeleton construction returns invalid_expansion through Halt; resource stops and allocation failures propagate through normal unwinding. |
| cost | Enumerates Prüfer skeletons, one fragment choice per origin, and endpoint products. Each path charges selected work, cumulative cells, and unique Family inserts; family size can be exponential and counters do not bound allocator bytes or total CPU. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), P3v2 §4.2, Algorithm 2; Appendix C.1.1, Algorithm 5, P3v2 Appendix C.1.2, Prüfer-sequence enumeration; C.1.3, rerootings, [exact paper reference](https://arxiv.org/html/2603.15465v2), [build/verification/v55-meta-primary-review-v1/REVIEW.md](../../../../../build/verification/v55-meta-primary-review-v1/REVIEW.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0022

[Lines 204–205](../../../../../src/planner/meta_join_trees.cpp#L204); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L204-L205:sha256:f66a964d9f14bdd9a03fc5f6e3bd4707e9089a8470d623422540498ec0c833ca
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain why completed fragments are checked independently before they become public ordinary join trees. |
| inputs / outputs | The next helper checks physical occurrence coverage, tree topology, and variable-induced connectivity from the fragment and metadata. |
| invariants | The check does not trust the recursive expansion choices; it is a finite implementation validation, not an independent proof that every valid tree was generated. |
| ownership | This comment retains no state. |
| failure | No runtime error path here; ordinary() returns false and the caller reports invalid_expansion. |
| cost | No comment cost. The checker has selected work/cell charges and can be interrupted by the same finite Budget. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), P3v2 §4.2, Algorithm 2; Appendix C.1.1, Algorithm 5, P3v2 Appendix C.1.2, Prüfer-sequence enumeration; C.1.3, rerootings, [exact paper reference](https://arxiv.org/html/2603.15465v2), [build/verification/v55-meta-primary-review-v1/REVIEW.md](../../../../../build/verification/v55-meta-primary-review-v1/REVIEW.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0023

[Lines 206–239](../../../../../src/planner/meta_join_trees.cpp#L206); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L206-L239:sha256:8ab58389a5699ee8144ef1e28b0c62d211a3095a6157529527b39042cb20a93d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that a fragment is an ordinary join tree over exactly one copy of every physical occurrence. |
| inputs / outputs | ordinary receives a fragment, checked Decomposition, atom count n, and Budget; it returns true only after coverage, edge, connectivity, and variable-induced edge-count checks pass. |
| invariants | It rejects dummies, wrong vertex/edge counts, minor/non-occurrence vertices, repeated or missing occurrence indices, self/foreign edges, disconnected graphs, and any variable with links != containing-nodes−1. |
| ownership | All input objects and Budget are borrowed; the helper owns temporary coverage, variable, reached, and traversal containers. |
| failure | A structural rejection returns false; the caller converts it to invalid_expansion. Budget Halt and allocation failures interrupt traversal. |
| cost | The checker uses O(n plus visited entries) temporary containers and repeated edge/variable scans. Selected steps/cells are charged, but set comparisons, capacity, allocator bytes, and total CPU are not bounded by those counters. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), P3v2 §4.2, Algorithm 2; Appendix C.1.1, Algorithm 5, P3v2 Appendix C.1.2, Prüfer-sequence enumeration; C.1.3, rerootings, [exact paper reference](https://arxiv.org/html/2603.15465v2), [build/verification/v55-meta-primary-review-v1/REVIEW.md](../../../../../build/verification/v55-meta-primary-review-v1/REVIEW.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0024

[Lines 240–253](../../../../../src/planner/meta_join_trees.cpp#L240); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L240-L253:sha256:b51a504ee58cefbb3157e783947a9401e24b7b662c63824d2dfe7959f8693f17
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Orient an already validated undirected fragment at one physical metadata node and produce occurrence-indexed parent links. |
| inputs / outputs | orient takes a fragment, root metadata-node ID, decomposition, atom count, and Budget; it returns a JoinTree whose root is the physical occurrence ID. |
| invariants | The root parent points to itself; traversal assigns each other physical occurrence's parent once. Caller must first pass ordinary(). |
| ownership | The returned parent vector owns its storage; fragment/decomposition and Budget are borrowed during construction. |
| failure | Budget Halt or vector allocation failure aborts the current output; invalid root/occurrence assumptions indicate an internal expansion error. |
| cost | Charges n parent cells, one walk seed, one work step per scanned edge, and one cell per newly queued node. Edge scan cost and allocator capacity remain outside a total CPU/bytes claim. |
| Design | [include/crown/planner/meta_join_trees.hpp](../../../../../include/crown/planner/meta_join_trees.hpp), [docs/meta_decompositions.md](../../../../meta_decompositions.md), P3v2 §4.2, Algorithm 2; Appendix C.1.1, Algorithm 5, [exact paper reference](https://arxiv.org/html/2603.15465v2), [build/verification/v55-meta-primary-review-v1/REVIEW.md](../../../../../build/verification/v55-meta-primary-review-v1/REVIEW.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0025

[Lines 254–255](../../../../../src/planner/meta_join_trees.cpp#L254); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L254-L255:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the anonymous namespace containing fragment, budget, and expansion helpers. |
| inputs / outputs | The public enumerate() definition follows outside this private namespace but remains inside crown::planner::meta. |
| invariants | Helper names and internal representation are not exported as public planner API; this delimiter changes linkage scope only. |
| ownership | Namespace closure retains no runtime state or objects. |
| failure | Mismatched braces or declarations are compile-time errors; there is no runtime failure path. |
| cost | Compilation/linkage organization only; no call-time cost. |
| Design | [include/crown/planner/meta_join_trees.hpp](../../../../../include/crown/planner/meta_join_trees.hpp), [docs/meta_decompositions.md](../../../../meta_decompositions.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0026

[Lines 256–327](../../../../../src/planner/meta_join_trees.cpp#L256); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L256-L327:sha256:acf2732721f976632781c933a4e04e66c1d8e56c2a6a965bc93a5c2b6a882547
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate metadata, expand per-node fragment families, independently check root fragments, and emit rooted ordinary join-tree values. |
| inputs / outputs | enumerate borrows catalog/query/decomposition, calls meta::check with limits.metadata, then builds child lists, bottom-up node order, Families, and output parent vectors. |
| invariants | Invalid metadata exits before fragment work; check work is separate. Each candidate root fragment passes ordinary() before its physical roots are oriented. A non-complete stop may expose only an already completed rooted prefix; subtree expansion stops can expose none. Check Algorithm1 minor-first parent choices before expansion and reject noncanonical graphs explicitly. Set requested mode before any early return; canonical mode emits root0 only and full mode emits every physical root. |
| ownership | All maps, families, fragments, work queues, and temporary vectors are local to one call; inputs are not retained. The returned Enumeration owns output trees and reports consumed counters. |
| failure | Metadata failures map to invalid_metadata or metadata_limit. Private Halt maps to the relevant stop reason. Allocation and uncaught library exceptions propagate. invalid_expansion is not a completeness or CROWN admissibility proof. |
| cost | The whole family and root orientations can be exponential. work/fragments/cells/output_trees are finite selected grants; metadata checking has separate limits. They do not bound allocator bytes, vector capacity, every primitive comparison/sort operation, or total CPU. No incremental maintenance or paper delay theorem is claimed. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), P3v2 §4.2, Algorithm 2; Appendix C.1.1, Algorithm 5, P3v2 Appendix C.1.2, Prüfer-sequence enumeration; C.1.3, rerootings, [exact paper reference](https://arxiv.org/html/2603.15465v2), [build/verification/v55-meta-primary-review-v1/REVIEW.md](../../../../../build/verification/v55-meta-primary-review-v1/REVIEW.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0027

[Lines 328–328](../../../../../src/planner/meta_join_trees.cpp#L328); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L328-L328:sha256:64c12aa1b75937a9f02928dc49559700cb3ed0d85658387b856ef97ff0af1a2f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the public planner metadata namespace after the single enumeration entry point. |
| inputs / outputs | No additional declarations or execution follow this delimiter. |
| invariants | The translation unit exports only the declarations from the public header and enumerate definition; private helpers remain anonymous-namespace implementation details. |
| ownership | The delimiter retains no objects or state. |
| failure | Brace or linkage errors are compile-time failures only. |
| cost | No runtime cost; compilation/linkage only. |
| Design | [include/crown/planner/meta_join_trees.hpp](../../../../../include/crown/planner/meta_join_trees.hpp), [docs/meta_decompositions.md](../../../../meta_decompositions.md), [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |
