# `src/planner/meta.cpp` — block usage map

[Source](../../../../../src/planner/meta.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Recognize structural query classes, check a proposed CROWN tree and lower checked structure into physical metadata.

Snapshot SHA-256: `f01332a980cb896b12819b61acd42e397bd5130dfa0a05db80248b02787dcc0e`. 305 lines partitioned into 16 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [planner](../../../subsystem_contracts.md#planner). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_plans.md](../../../../tree_plans.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../src/planner/meta.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 7–7](../../../../../src/planner/meta.cpp#L7) | Type/record definition: struct Limit |  · [reviewed contract](#b0002) |
| [B0003 · 8–23](../../../../../src/planner/meta.cpp#L8) | Type/record definition: struct Budget |  · [reviewed contract](#b0003) |
| [B0004 · 24–32](../../../../../src/planner/meta.cpp#L24) | Callable definition: bool contains(const Scope& large, const Scope& small, Budget& b) | calls begin, step, end; returns false; true; 2 loop sites · [reviewed contract](#b0004) |
| [B0005 · 33–36](../../../../../src/planner/meta.cpp#L33) | Callable definition: bool equal(const Scope& a, const Scope& c, Budget& b) | calls step, size, contains; returns a.size() == c.size() && contains(a, c, b) · [reviewed contract](#b0005) |
| [B0006 · 37–40](../../../../../src/planner/meta.cpp#L37) | Callable definition: Scope copied(const Scope& scope, Budget& b) | calls cells, size; returns scope · [reviewed contract](#b0006) |
| [B0007 · 41–55](../../../../../src/planner/meta.cpp#L41) | Callable definition: std::vector&lt;Scope&gt; scopes(const Query& q, Budget& b) | calls step, contains, cells, insert; returns result; growth insert, push_back; 2 loop sites · [reviewed contract](#b0007) |
| [B0008 · 56–57](../../../../../src/planner/meta.cpp#L56) | Explanatory comments or spacing. | source comment (unverified): // Recompute overlaps from one frozen round. This simple implementation does not · [reviewed contract](#b0008) |
| [B0009 · 58–71](../../../../../src/planner/meta.cpp#L58) | Callable definition: std::vector&lt;Scope&gt; overlaps(const Decomposition& m, const std::vector&lt;std::size_t&gt;& active, Budget& b) | calls result, size, step, contains; returns result; growth insert; 3 loop sites; source comment (unverified): // Recompute overlaps from one frozen round. This simple implementation does not · [reviewed contract](#b0009) |
| [B0010 · 72–80](../../../../../src/planner/meta.cpp#L72) | Callable definition: std::size_t minor(Decomposition& m, const Scope& scope, Budget& b) | calls size, step, equal, nodes; returns i; m.nodes.size()-1; growth push_back; 1 loop sites · [reviewed contract](#b0010) |
| [B0011 · 81–82](../../../../../src/planner/meta.cpp#L81) | Explanatory comments or spacing. | source comment (unverified): // Definition checker is independent of the reduction trace: rebuild topology, · [reviewed contract](#b0011) |
| [B0012 · 83–191](../../../../../src/planner/meta.cpp#L83) | Callable definition: bool definition(const Query& q, const Decomposition& m, Budget& b) | calls nodes, size, scopes, step; returns false; false; growth insert, push_back; 19 loop sites; source comment (unverified): // Definition checker is independent of the reduction trace: rebuild topology, · [reviewed contract](#b0012) |
| [B0013 · 192–193](../../../../../src/planner/meta.cpp#L192) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0013) |
| [B0014 · 194–287](../../../../../src/planner/meta.cpp#L194) | Callable definition: Build construct(const Catalog& catalog, const Query& query, Limits limits) | calls crown::validate, scopes, empty, size; returns {Stop::empty_body,b.usage,{}}; {Stop::nullary_occurrence,b.usage,{}}; growth push_back; 14 loop sites; source comment (unverified): // Algorithm 1, lines 4–8: group equal overlaps simultaneously. Specials · [reviewed contract](#b0014) |
| [B0015 · 288–304](../../../../../src/planner/meta.cpp#L288) | Callable definition: Check check(const Catalog& catalog, const Query& query, const Decomposition& m, Limits limits) | calls crown::validate, empty, step, definition; guard Check check(const Catalog& catalog, const Query& query, const Decomposition& m, Limits limits) {; returns {Stop::empty_body,b.usage,false}; {Stop::nullary_occurrence,b.usage,false}; 2 loop sites · [reviewed contract](#b0015) |
| [B0016 · 305–305](../../../../../src/planner/meta.cpp#L305) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::meta · [reviewed contract](#b0016) |

## B0001

[Lines 1–6](../../../../../src/planner/meta.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L6:sha256:1408429ac7e22cf90ac02e8988c7a239cf6e995790457ec5573abeaab6b30ac1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind this implementation to its public metadata API and keep reduction helpers in an anonymous namespace. |
| inputs / outputs | The header supplies the public values; algorithm/utility supply max and move for the helpers and entry points below. |
| invariants | Only construct/check have external API linkage. Opening namespaces and includes neither admits a query nor creates a shared planner cache. |
| ownership | This scaffolding defines no global graph, allocator owner or mutable cross-query state. |
| failure | Dependency/name errors are compile-time failures; there is no runtime recovery path in this region. |
| cost | Build-time parsing/linkage only, with no per-call or per-update executable work attributable to the directives/braces. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0002

[Lines 7–7](../../../../../src/planner/meta.cpp#L7); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L7-L7:sha256:fb4d5df1bf13e8326ab98e67b710bec03846f36a717806b1961117ae4960570a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry one private metadata-budget stop through helper stack frames to the public boundary. |
| inputs / outputs | Budget methods throw Limit containing work_limit, node_limit or cell_limit; construct/check catch that exact private type. |
| invariants | This is a local nonallocating payload declaration, not a catch-all for validation, allocation or arbitrary program faults. |
| ownership | Limit owns only its Stop enum; it retains no query, partial decomposition or diagnostic allocation. |
| failure | The throw is raised before the prohibited charge/growth and converted once at the public function boundary. Other exception types remain untouched. |
| cost | The payload is fixed-size; stack unwinding on exhausted grants is cold failure-path work and is not included in the logical selected-work counter. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0003

[Lines 8–23](../../../../../src/planner/meta.cpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L8-L23:sha256:4c2cfd525660f41f5a1120708f2a6353844f0b304d34c045f0d34485b42c8cf6
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce one call's selected-work, cumulative-cell and peak-node grants before increasing each corresponding counter. |
| inputs / outputs | Budget owns Limits and Usage. step charges one work unit; cells charges count explicit scope members; nodes admits a candidate resident node count. |
| invariants | Internal usage starts at zero and never exceeds limits. cells subtracts only from an unexceeded grant; nodes records max count rather than accumulating every visit. |
| ownership | Both members are scalar values owned by the call. The helper neither allocates scope containers nor owns the decomposition it budgets. |
| failure | An exhausted step/cells/nodes operation throws its specific Limit before changing that counter; previously consumed charges remain available to the public catch. |
| cost | Each method performs fixed arithmetic/comparison work. Grants do not cover uncharged vector capacity, set allocator overhead, validation or all CPU instructions. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0004

[Lines 24–32](../../../../../src/planner/meta.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L32:sha256:566ee2099d534b8dfce5e71792d86c4fd6e2687e78951b8c41199a2082c152e1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test ordered-scope containment while charging selected iterator/comparison checkpoints. |
| inputs / outputs | Borrowed large/small Scope sets and mutable Budget produce true iff every member of small occurs in large. |
| invariants | The large iterator advances monotonically and both sets remain unchanged. Empty small is contained without scanning large. |
| ownership | Only stack iterators and scalar variable IDs are local; the function allocates no scope copy and retains no input. |
| failure | Budget exhaustion throws Limit without a boolean result. Failed containment returns false rather than treating a missing member as an input error. |
| cost | At most linear ordered-iterator advances across the two sets plus charged small-member steps; this is selected comparison work, not a global CPU meter. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm1), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3) |

## B0005

[Lines 33–36](../../../../../src/planner/meta.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L36:sha256:da665e1bad44f790024ff80bb343212c8fca78d19cc99c8398dd503d2eb05742
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test scope equality using cardinality followed by charged containment. |
| inputs / outputs | Two borrowed Scope sets and Budget produce a boolean; unequal sizes short-circuit after the initial work charge. |
| invariants | Equal cardinality plus containment is sufficient for these unique ordered variable sets; input scope identity and storage are not conflated. |
| ownership | No owning data is created; the helper borrows both sets and updates only the budget. |
| failure | A false equality is an ordinary predicate result. The initial or nested containment charge may throw the private Limit. |
| cost | One explicit work unit plus the containment traversal when sizes agree; no full-scope copy or allocation is required. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3) |

## B0006

[Lines 37–40](../../../../../src/planner/meta.cpp#L37); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L37-L40:sha256:4c78fc90a50ece2e625d510d0dd2c56b83504bc44ad182bef80cfaa503b8bf78
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Charge every member of a requested explicit scope copy before making that copy. |
| inputs / outputs | A borrowed Scope and Budget produce an independent owning Scope with the same variable members. |
| invariants | The complete requested cell count is admitted first. Cells describe copied members rather than allocator-request bytes or retained capacity. |
| ownership | The returned ordered set owns copied nodes; the source remains unchanged. Normal container cleanup handles any incomplete copy on exception. |
| failure | A cell-limit stop precedes copying; allocation/copy exceptions propagate and are not converted into a successful empty scope. |
| cost | The charge is fixed arithmetic; copying a k-member Scope visits k members and allocates set storage beyond the logical cell counter. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0007

[Lines 41–55](../../../../../src/planner/meta.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L55:sha256:1f68f5141a772bd43b4a9ac62706732c005c40c0e8ad654210d179d6137b39a8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract each original occurrence's variable set without changing atom identity or query terms. |
| inputs / outputs | An admitted Query and Budget produce one Scope per atom in original atom order; literals and ignored columns contribute no variable. |
| invariants | Repeated variable terms in one atom are inserted once, while equal scopes across different atoms remain separate vector entries. |
| ownership | The result owns new scope sets and a vector; Query is borrowed. Unique member insertion is cell-charged before the insertion. |
| failure | Work/cell limits throw before their denied charge; allocation failure propagates. Empty scopes are represented here and interpreted by the public domain checks. |
| cost | Work is charged per atom and term; each new variable member consumes one cell. Set lookups, vector growth and allocator costs are not fully represented by those charges. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS1), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm1) |

## B0008

[Lines 56–57](../../../../../src/planner/meta.cpp#L56); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L56-L57:sha256:0d9d7038b5d8e485ecf4b14cf8464769601a1a916a4e53e5d391827f78f4c322
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the deliberate overlap-recomputation design and exclude unsupported paper complexity/delay claims. |
| inputs / outputs | This adjacent comment describes overlaps below; it has no executable input or return value. |
| invariants | Every overlap call reads a frozen active set. Recomputing correct metadata is separate from implementing P3's incremental maps or join-tree enumerator. |
| ownership | The comment owns no scope, index, runtime hook or shared state. |
| failure | No error is raised by the comment. Actual grant/allocation failures belong to the adjacent overlap implementation. |
| cost | No executable work is performed here; the documented scans below remain cold planning costs, with no imported asymptotic theorem. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm1), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS3) |

## B0009

[Lines 58–71](../../../../../src/planner/meta.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L58-L71:sha256:f414e61938a8802a4e18fa909988bf0e1bc44d67a27545d7ac3de99e2b9e2939
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute O(e)=chi(e) intersect the union of all other active scopes from one immutable snapshot. |
| inputs / outputs | Borrowed Decomposition plus valid active node indices and Budget produce a parallel vector of fresh overlap Scope values. |
| invariants | Self-index positions are excluded; a variable enters its overlap at most once and only after a distinct active edge witnesses it. The caller does not mutate active during the call. |
| ownership | The function owns its result vector/sets while borrowing graph scopes; every inserted overlap member is cell-charged first. |
| failure | Private work/cell exhaustion discards the partial return through unwinding. Allocation failures propagate; invalid active indices are an internal caller-contract violation. |
| cost | Nested active-edge/variable/other-edge scans with ordered-set membership checks, stopping at the first witness. Counter charges are selected steps and output cells, not total CPU or bytes. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm1), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem7) |

## B0010

[Lines 72–80](../../../../../src/planner/meta.cpp#L72); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L72-L80:sha256:e344511c6dffb222a9b53912ac38bff439fdbd1c1dd9a5ca4b1e44e5f9812649
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Intern a canonical minor by chi alone, keeping its identity distinct from all physical occurrences. |
| inputs / outputs | Mutable Decomposition, borrowed scope and Budget produce an existing or newly appended minor node index. |
| invariants | Only nodes with absent occurrence participate in lookup. Reuse does not reset kappa; a newly created minor starts with chi=kappa and may later receive its final kappa. |
| ownership | A new node owns two copied scopes inside the vector. Returning an index avoids keeping a reference across vector reallocation. |
| failure | The node count is admitted before append; each scope copy admits its own cell charge before that copy. A later failure discards any earlier temporary copy. Limit/allocation exceptions publish no Build; unequal candidates merely continue the scan. |
| cost | Linear scan of existing metadata with charged scope equality. Creation admits one node and two full-scope copies; no runtime hash index or per-update structure is added. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm1), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3) |

## B0011

[Lines 81–82](../../../../../src/planner/meta.cpp#L81); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L81-L82:sha256:38364998098fb508aec7f13b2cd63478e26f9c34f8d96f1a17fd625361a8ec04
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the checker's independence from the constructor's reduction trace. |
| inputs / outputs | This comment introduces definition, which consumes original query and proposed graph fields rather than recorded ear/group decisions. |
| invariants | Independent traversal checks are property validation; the comment does not certify the implementation or establish CROWN family/minimum-height authority. |
| ownership | No trace, graph or resource owner is created by this documentation region. |
| failure | No executable failure occurs here; definition below returns false or throws the private budget stop as documented. |
| cost | No executable work; recomputation and its scratch/selected charges belong to the adjacent callable. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS4) |

## B0012

[Lines 83–191](../../../../../src/planner/meta.cpp#L83); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L191:sha256:c10814e4c1b82ebf6264b9aa8f7ec7e44225a37181ff38536f72439c612e4849
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate the current proposed metadata by rebuilding its coverage, topology, interfaces, running intersection and C4b/C5 properties. |
| inputs / outputs | An already admitted Query, borrowed Decomposition and Budget produce a boolean after recomputing original scopes and inspecting actual fields. |
| invariants | Every original occurs once with exact chi; minors have unique chi contained wholly in one original scope. Parent indices/root are checked before ancestry walks. Reachability precedes subtree queries; actual outside interfaces, RIP, highest-parent and unique equal-kappa minors must all hold. |
| ownership | Inputs are read-only. Original scopes, variable union, seen/reached bits, child adjacency, DFS stack and per-node actual-interface sets are private scratch released on every exit. |
| failure | Malformed structure returns false; budget exhaustion throws Limit; allocation failures propagate. The anchored-minor rule strengthens literal Def4.3 to Algorithm1's acyclic domain; success is not an executable CROWN or height certificate. |
| cost | Repeated node/variable scans, scope comparisons and parent-chain walks can be large. Work charges selected checkpoints; cells charge extracted/union/interface members and nodes admits the graph size. Scratch vectors, allocator overhead, admission and total CPU are not byte/time-bounded here. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm1), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS4) |

## B0013

[Lines 192–193](../../../../../src/planner/meta.cpp#L192); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L192-L193:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close internal helper linkage before defining the public functions. |
| inputs / outputs | The anonymous namespace closure separates helper names from the public construct/check definitions that follow. |
| invariants | The closure neither publishes private scratch nor changes any decomposition. Public wrappers still call the internal helpers through ordinary lookup. |
| ownership | A namespace brace owns and destroys no runtime object; local lifetimes remain determined by function scopes. |
| failure | No runtime exception or result is produced by the closure. |
| cost | No executable instructions are required for this namespace boundary. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md) |

## B0014

[Lines 194–287](../../../../../src/planner/meta.cpp#L194); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L194-L287:sha256:277058ab2115569ae2293022a1545f4ab0fa1112a3d13f1e24c643266a37f5f9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct bounded body metadata using scope-interned special edges, fixed-point overlap grouping and simultaneous ear removal, then independently check it. |
| inputs / outputs | Borrowed Catalog/Query and copied Limits produce Build with consumed Usage and an owning Decomposition only on complete. |
| invariants | Admission precedes budgeting. Physical IDs remain original atom indices; only nonempty scopes enter reduction. A successful grouping shrinks active before any ear snapshot, so new equal-overlap groups are exhausted. Ear kappas use one frozen snapshot; reused minors receive final kappa. Root selection prefers the explicit empty minor for disconnected components; nonroot lookup excludes self and selects minor-first/highest parents. |
| ownership | The function owns all active/group/ear vectors and the proposed graph privately. The final checked graph moves into Build; no source table, runtime index or query-shared mutable state is retained. |
| failure | Empty/nullary bodies have explicit stops; a round with neither grouping nor ear progress stops cyclic. Missing root or failed independent definition stops invalid_decomposition. Only private Limit is caught into its specific stop/Usage; validation and allocation exceptions propagate with private state cleaned up. |
| cost | All passes consume the same finite Budget; successful grouping reduces active count and is not an unbounded retry. Overlaps, group matching, ear witnesses, parent scans and the final definition check are recomputed. Selected work/node/cell counters exclude total CPU, container capacity and admission; no P3 construction/delay bound is claimed. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm1), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem7), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS3), [exact paper reference](https://arxiv.org/html/2603.15465v2#A3.SS4) |

## B0015

[Lines 288–304](../../../../../src/planner/meta.cpp#L288); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L288-L304:sha256:f8b3012ec6631914be5824e457c035fca1794325597dc0046cf18cf114069b8b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check a caller-supplied graph under the same nonempty/non-nullary body domain as construction. |
| inputs / outputs | Borrowed Catalog, Query, Decomposition and copied Limits produce Check with current Usage and valid=true only after definition succeeds. |
| invariants | Catalog/query admission occurs first. An empty body or any atom lacking a variable is rejected explicitly before definition; literals/ignored terms do not make a nonempty hyperedge. |
| ownership | The proposal and query remain caller-owned and unchanged; the Budget and all definition scratch belong only to this call. |
| failure | empty_body/nullary_occurrence and resource stops have valid=false. Failed definition returns invalid_decomposition. Only private Limit is converted; admission and allocation exceptions propagate. |
| cost | Selected work includes the domain atom/term scan and definition checks, using one grant. Rebuilt scopes and checker scratch have their documented charges; this cold check is not an O(1) capability lookup or total-CPU meter. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/html/2603.15465v2#S2.SS1), [exact paper reference](https://arxiv.org/html/2603.15465v2#S4.Thmtheorem3), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm1) |

## B0016

[Lines 305–305](../../../../../src/planner/meta.cpp#L305); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L305-L305:sha256:64c12aa1b75937a9f02928dc49559700cb3ed0d85658387b856ef97ff0af1a2f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the public metadata implementation namespace. |
| inputs / outputs | This brace finishes crown::planner::meta after both public entry-point definitions. |
| invariants | No construction/checking behavior, status or API authority is introduced by this lexical boundary. |
| ownership | Namespace closure creates no owner and releases no function-local resource. |
| failure | There is no runtime failure path in this region. |
| cost | No executable work or dynamic storage is attributable to the closing namespace brace. |
| Design | [docs/meta_decompositions.md](../../../../meta_decompositions.md) |
