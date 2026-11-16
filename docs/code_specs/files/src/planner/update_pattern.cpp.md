# `src/planner/update_pattern.cpp` — block usage map

[Source](../../../../../src/planner/update_pattern.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Recognize structural query classes, check a proposed CROWN tree and lower checked structure into physical metadata.

Snapshot SHA-256: `fda47c453e3c73bd9a8a9dd31ab86a76f881c5649c0322537e3247b5cbb7973f`. 238 lines partitioned into 20 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [planner](../../../subsystem_contracts.md#planner). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_plans.md](../../../../tree_plans.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../src/planner/update_pattern.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 6–11](../../../../../src/planner/update_pattern.cpp#L6) | Callable definition: template&lt;class T&gt; void reserve(Vector&lt;T&gt;& values, std::size_t count, detail::rd::Budget& budget) | calls cells, bytes; growth reserve · [reviewed contract](#b0002) |
| [B0003 · 12–12](../../../../../src/planner/update_pattern.cpp#L12) | Explanatory comments or spacing. | source comment (unverified): // Charge the actual logarithmic declaration lookup, without a second index. · [reviewed contract](#b0003) |
| [B0004 · 13–22](../../../../../src/planner/update_pattern.cpp#L13) | Callable definition: const TableRule* find_rule(const Declaration& declaration, TableId table, detail::rd::Budget& budget) | calls rules, std::lower_bound, begin, end; returns rule.table &lt; key; found != rules.end() && found-&gt;table == table ? &*found : nullptr; source comment (unverified): // Charge the actual logarithmic declaration lookup, without a second index. · [reviewed contract](#b0004) |
| [B0005 · 23–25](../../../../../src/planner/update_pattern.cpp#L23) | Explanatory comments or spacing. | source comment (unverified): // Each admitted input maps one physical row to zero/one occurrence row. Inserts · [reviewed contract](#b0005) |
| [B0006 · 26–34](../../../../../src/planner/update_pattern.cpp#L26) | Callable definition: bool all_sources_insertion_only(const CompiledProgram& source, const Declaration& declaration, detail::rd::Budget& budget) | calls inputs, work, find_rule; returns false; true; 1 loop sites; source comment (unverified): // Each admitted input maps one physical row to zero/one occurrence row. Inserts · [reviewed contract](#b0006) |
| [B0007 · 35–37](../../../../../src/planner/update_pattern.cpp#L35) | Explanatory comments or spacing. | source comment (unverified): // A verified tree needs no visited set. Build a parent-before-child order, then · [reviewed contract](#b0007) |
| [B0008 · 38–67](../../../../../src/planner/update_pattern.cpp#L38) | Callable definition: Vector&lt;std::uint8_t&gt; insertion_subtrees(const MinimumHeightCandidate& candidate, const Declaration& declaration, const resource::… | calls tree, order, flags, reserve; returns flags; growth push_back, reserve, resize; 4 loop sites; source comment (unverified): // A verified tree needs no visited set. Build a parent-before-child order, then · [reviewed contract](#b0008) |
| [B0009 · 68–68](../../../../../src/planner/update_pattern.cpp#L68) | Closes surrounding scope/type. |  · [reviewed contract](#b0009) |
| [B0010 · 69–79](../../../../../src/planner/update_pattern.cpp#L69) | Callable definition: std::string_view name(SufficientCase value) noexcept | calls ; returns @; @ · [reviewed contract](#b0010) |
| [B0011 · 80–93](../../../../../src/planner/update_pattern.cpp#L80) | Callable definition: std::string_view name(Transfer value) noexcept | calls ; returns @; @ · [reviewed contract](#b0011) |
| [B0012 · 94–102](../../../../../src/planner/update_pattern.cpp#L94) | Callable definition: std::string_view name(EdgeBasis value) noexcept | calls ; returns @; @ · [reviewed contract](#b0012) |
| [B0013 · 103–105](../../../../../src/planner/update_pattern.cpp#L103) | Callable definition: Analysis::Analysis(const resource::MemoryAccount& account, const MinimumHeightCandidate& checked, const Declaration& requested) :… | calls candidate, declaration, edges · [reviewed contract](#b0013) |
| [B0014 · 106–107](../../../../../src/planner/update_pattern.cpp#L106) | Explanatory comments or spacing. | source comment (unverified): // Bind the full typed CQ before analysing an independently supplied candidate. · [reviewed contract](#b0014) |
| [B0015 · 108–118](../../../../../src/planner/update_pattern.cpp#L108) | Callable definition: Analysis detail::analyse(const resource::MemoryAccount& account, const CompiledProgram& source, const MinimumHeightCandidate& can… | calls valid, work, matches, rd::score_binding; returns analyse_bound(account, source, candidate, declaration, budget); source comment (unverified): // Bind the full typed CQ before analysing an independently supplied candidate. · [reviewed contract](#b0015) |
| [B0016 · 119–124](../../../../../src/planner/update_pattern.cpp#L119) | Explanatory comments or spacing. | source comment (unverified): // Native adapters give zero/one crossing per routed occurrence. Monotone sources · [reviewed contract](#b0016) |
| [B0017 · 125–214](../../../../../src/planner/update_pattern.cpp#L125) | Callable definition: Analysis detail::analyse_bound(const resource::MemoryAccount& account, const CompiledProgram& source, const MinimumHeightCandidat… | calls work, result, height, route; returns result; result; growth push_back, reserve; 6 loop sites; source comment (unverified): // Native adapters give zero/one crossing per routed occurrence. Monotone sources · [reviewed contract](#b0017) |
| [B0018 · 215–217](../../../../../src/planner/update_pattern.cpp#L215) | Explanatory comments or spacing. | source comment (unverified): // One translation boundary; private visitors use the existing ranking failures · [reviewed contract](#b0018) |
| [B0019 · 218–237](../../../../../src/planner/update_pattern.cpp#L218) | Callable definition: Attempt analyse(const resource::MemoryAccount& account, const CompiledProgram& source, const MinimumHeightCandidate& candidate, c… | calls emplace, detail::analyse, time, std::move; returns out; growth emplace; source comment (unverified): // One translation boundary; private visitors use the existing ranking failures · [reviewed contract](#b0019) |
| [B0020 · 238–238](../../../../../src/planner/update_pattern.cpp#L238) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::patterns · [reviewed contract](#b0020) |

## B0001

[Lines 1–5](../../../../../src/planner/update_pattern.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L5:sha256:35f70e63d51ca8802912ef53687d892afc96d6dfc41062be97200ef97f201197
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Include private planner helpers and algorithm support, then establish the local helper namespace. |
| inputs / outputs | Uses \`std::lower_bound\` and private ranking budget facilities. |
| invariants | The implementation reuses existing ranking resource semantics. |
| ownership | No object owner is created by this setup. |
| failure | No runtime failure path. |
| cost | Compile-time setup only. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/selection.md](../../../../selection.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0002

[Lines 6–11](../../../../../src/planner/update_pattern.cpp#L6); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L6-L11:sha256:6aa923e88930c6f0a3183b2add9dbe4e0b586ccdc46d0ccfacc053e9ae4fe6d4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reserve scratch/edge vectors after charging planner budget cells and payload. |
| inputs / outputs | Checks count*sizeof(T), charges Budget cells and bytes, then calls vector.reserve. |
| invariants | Overflow or planner byte limit is rejected before allocation; actual receiving account remains independently enforced. |
| ownership | Vector allocator belongs to the caller’s receiving account. |
| failure | rd::Failure signals byte limit; account denial/std::bad_alloc propagates to public noexcept boundary. |
| cost | O(1) charge plus reserve; charges count cells and count*sizeof(T) payload. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/selection.md](../../../../selection.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0003

[Lines 12–12](../../../../../src/planner/update_pattern.cpp#L12); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L12-L12:sha256:33b462731e785236c732be792373edb37018fd307971029c2d89a906aa127b40
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain that declaration lookup charges real logarithmic comparisons without constructing a second index. |
| inputs / outputs | find_rule uses the sorted rule span directly. |
| invariants | No group/scope index or uncharged copied directory is constructed. |
| ownership | Lookup borrows Declaration storage. |
| failure | Budget stop propagates through rd::Failure. |
| cost | O(log R) comparisons with each comparison charged. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0004

[Lines 13–22](../../../../../src/planner/update_pattern.cpp#L13); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L22:sha256:15569d7a70837005e8bf5f3908332d13d3bd84c3d3b47d25adb99efb3a2727c1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Find a TableRule while charging every binary-search comparison. |
| inputs / outputs | Reads Declaration::rules and uses lower_bound by TableId; returns matching pointer or nullptr. |
| invariants | Rules are canonical sorted values; no second lookup structure or allocation is used; one final work unit is charged after the search. |
| ownership | Returned pointer borrows the Declaration handle’s original-account Data. |
| failure | Work exhaustion raises rd::Failure; no allocation in lookup. |
| cost | O(log R) charged comparisons, O(1) scratch. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0005

[Lines 23–25](../../../../../src/planner/update_pattern.cpp#L23); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L25:sha256:86bfa0fca4ac17fe15e8d680c7f6d205559e0de2407eced810658457d5f45b60
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain why source monotonicity uses actual physical input IDs. |
| inputs / outputs | Comments state the deterministic zero/one occurrence mapping and finite alias fanout used below. |
| invariants | PhysicalInput.base may differ from a normalized core table ID. This argument gives bounded sign-preserving membership crossings, not arbitrary FIFO lifetime preservation. |
| ownership | Source text only. |
| failure | No runtime failure behavior. |
| cost | No execution cost. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md), [build/verification/v53-taller-mixed-proof-v1/proof.md](../../../../../build/verification/v53-taller-mixed-proof-v1/proof.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp) |

## B0006

[Lines 26–34](../../../../../src/planner/update_pattern.cpp#L26); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L34:sha256:5cc859503dde4f0b246ba71b0439b41222456660efd93eee6b6ca529ddf799fe
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check insertion-only assumptions for every participating physical source. |
| inputs / outputs | Borrow source/declaration and mutable analysis budget; return true exactly when every compiled input base has an insertion-only rule. |
| invariants | Every input uses PhysicalInput.base. Unused physical tables impose no condition; absent rules fail; repeated aliases are checked without creating a second index. This checks declared premises, not an actual trace. |
| ownership | All handles and rule pointers are synchronous borrows; no retained data or allocation. |
| failure | Existing budget work/time failure propagates to the single public attempt boundary; false is an ordinary unproved premise. |
| cost | For I compiled inputs and R rules, at most O(I log(R+1)) charged visits/comparisons; early false and constant auxiliary storage. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md), [build/verification/v53-taller-mixed-proof-v1/proof.md](../../../../../build/verification/v53-taller-mixed-proof-v1/proof.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf), [src/ir/program.cpp](../../../../../src/ir/program.cpp), [src/runtime/physical.cpp](../../../../../src/runtime/physical.cpp) |

## B0007

[Lines 35–37](../../../../../src/planner/update_pattern.cpp#L35); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L35-L37:sha256:7082196718de9a90184cd89745bf579dce1f665d319510feb60381eb6f48258b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the checked-tree ordering and temporary ownership of subtree analysis. |
| inputs / outputs | Comments introduce the parent-before-child traversal and reverse fold below. |
| invariants | Existing candidate validation supplies a rooted tree; this visitor supplies no new structural certificate. |
| ownership | Source text only; the adjacent callable separately funds both scratch vectors. |
| failure | No runtime failure behavior. |
| cost | No execution cost. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md), [build/verification/v53-taller-mixed-proof-v1/proof.md](../../../../../build/verification/v53-taller-mixed-proof-v1/proof.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0008

[Lines 38–67](../../../../../src/planner/update_pattern.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L67:sha256:2dababf7fa449233968caca0242beff538fcace0cd3f5e9712dd6bab7345e8be
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute whether every native relation in each checked child subtree is declared insertion-only. |
| inputs / outputs | Borrow genuine candidate, declaration and receiving account/budget; return node-ID-indexed byte flags. Build a parent-before-child NodeId order, initialize flags true, then fold native rules and all child flags in reverse. |
| invariants | The checked rooted tree needs neither recursion nor a visited set; IDs need not be topological. Generalized nodes contribute only their descendants. A true native flag includes that node and every native descendant. Missing rules fail. Higher mixed source gates ensure atom table IDs identify the physical bases before this helper is called. |
| ownership | NodeId order and byte flags are funded as scratch by the receiving account. Order is destroyed on return; flags move to the caller and are destroyed before analysis returns. No row mirror, retained index or runtime update work. |
| failure | Cells/element bytes are admitted before reserve; initialization and each explicit traversal/comparison are charged. Existing budget or allocator failures unwind local vectors and reach the existing public boundary without a partial report. |
| cost | For T tree nodes, Q native occurrences and R rules, O(T+Q log(R+1)) charged work and T NodeId plus T byte logical cells/payload. Allocator frames/capacity are separately enforced. Called only for height greater than two. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md), [build/verification/v53-taller-mixed-proof-v1/proof.md](../../../../../build/verification/v53-taller-mixed-proof-v1/proof.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0009

[Lines 68–68](../../../../../src/planner/update_pattern.cpp#L68); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L68-L68:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the translation-unit-private allocation, source-rule and subtree visitors before public diagnostic-name definitions. |
| inputs / outputs | No inputs/outputs. |
| invariants | Budget/reserve, physical-source rule checks and subtree helpers remain private; the following enum-name functions are in the public patterns namespace. |
| ownership | No ownership effect. |
| failure | No failure path. |
| cost | No runtime cost. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0010

[Lines 69–79](../../../../../src/planner/update_pattern.cpp#L69); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L69-L79:sha256:4bf008fa3371f50020f9195f7da1035c2dae394ad3a9a5bc398f566c95cbc8b4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name a sufficient case for human diagnostics. |
| inputs / outputs | Map the typed enum to exact static text; unrecognized values return unrecognized. |
| invariants | No numeric enum values or admission rules change. Presentation text cannot enable a guarantee. |
| ownership | Returned string_view refers to static storage. |
| failure | Noexcept; no allocation or error-construction path. |
| cost | Fixed finite switch, O(1) work and storage. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0011

[Lines 80–93](../../../../../src/planner/update_pattern.cpp#L80); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L80-L93:sha256:8d5d8e0a2c1b81603a234ca46c5537434766683e17756fea493f0cd5c9c8462b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name a source-transfer status for human diagnostics. |
| inputs / outputs | Map the typed enum to exact static text; unrecognized values return unrecognized. |
| invariants | No numeric enum values or admission rules change. Presentation text cannot enable a guarantee. |
| ownership | Returned string_view refers to static storage. |
| failure | Noexcept; no allocation or error-construction path. |
| cost | Fixed finite switch, O(1) work and storage. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0012

[Lines 94–102](../../../../../src/planner/update_pattern.cpp#L94); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L94-L102:sha256:b19974a5e23c1d53d9049c4a9ef9b3b895dad36c404c2af2a144f25d98b9ab86
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name a native edge basis for human diagnostics. |
| inputs / outputs | Map the typed enum to exact static text; unrecognized values return unrecognized. |
| invariants | No numeric enum values or admission rules change. Presentation text cannot enable a guarantee. |
| ownership | Returned string_view refers to static storage. |
| failure | Noexcept; no allocation or error-construction path. |
| cost | Fixed finite switch, O(1) work and storage. |
| Design | docs/update_patterns.md#support-action-guarantee-profile, [docs/selection.md](../../../../selection.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0013

[Lines 103–105](../../../../../src/planner/update_pattern.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L103-L105:sha256:e59021135001913bd62afe0b57b1ee97756429599e9848640c8561be354ef1fd
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Initialize a diagnostic Analysis by retaining the checked candidate/declaration handles and binding its edge vector to the receiving account. |
| inputs / outputs | Copies the two handles and constructs \`edges\` with \`detail::allocator&lt;EdgeCondition&gt;(account)\`. |
| invariants | Called after input binding by the analyser/selector; direct public construction itself performs no validation. Candidate/declaration copies share existing owners under their own allocation contracts. |
| ownership | Only the two handles are retained here. The empty edge vector stores a receiving-account allocator; later edge cells use that account. |
| failure | No heap growth occurs in this body. Later analysis allocations may fail; the public analyse boundary translates those failures. |
| cost | O(1) handle copies plus initial empty vector setup; later O(E) growth. |
| Design | [docs/selection.md](../../../../selection.md), [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0014

[Lines 106–107](../../../../../src/planner/update_pattern.cpp#L106); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L106-L107:sha256:3f0f7564916cc964f00f032d253c72560dc777b749135055f8b4ddf958315d83
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document that private analysis binds the complete typed CQ before considering a supplied candidate. |
| inputs / outputs | The following method checks source-to-candidate identity. |
| invariants | Matching shape or height alone is insufficient; full typed binding is required before transfer conditions. |
| ownership | No storage is introduced by the comment. |
| failure | Mismatch returns existing binding_mismatch stop through the outer boundary. |
| cost | Full binding work is accounted separately from pattern analysis. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0015

[Lines 108–118](../../../../../src/planner/update_pattern.cpp#L108); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L108-L118:sha256:08c021aa8c9da83e6f408880fc8c3535a799d8858b94c6d0e3414f76379ea78b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate source/declaration handles and compare complete source and candidate catalog/query bindings before using a candidate. |
| inputs / outputs | Reject empty source/candidate/declaration; admit fixed digest work; check declaration.matches; encode source and candidate catalog/query bindings under the existing budget/account, then compare character buffers. |
| invariants | A same-shaped but foreign typed CQ must fail binding; only exact binding reaches analyse_bound. |
| ownership | Temporary score-binding buffers use the receiving account/budget; input handles are borrowed. |
| failure | Invalid handles or mismatches raise existing ranking Stop via rd::Failure; allocation/work stops propagate to public boundary. |
| cost | Binding encoder work plus comparison of max(expected,actual) elements; not repeated in the already-bound visitor. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf), [docs/selection.md](../../../../selection.md), [docs/update_patterns.md](../../../../update_patterns.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0016

[Lines 119–124](../../../../../src/planner/update_pattern.cpp#L119); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L119-L124:sha256:841228bd182af5d164b23937bb1cefd0917d02ad9a9ec8ca7470c5c5e0f0869d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain source-event transfer, the higher mixed lifetime gate and actual planning scratch/work. |
| inputs / outputs | Source comment describes Q atoms, C columns/terms, R rules and T checked tree nodes; it performs no algorithm. |
| invariants | All-insertion and height-one cases use bounded occurrence events; higher mixed cases retain injective/self-join-free transfer. The note does not establish a CPU/delay theorem. |
| ownership | The prose creates no owner. The adjacent implementation separately funds table/order/flag scratch and retained edge cells. |
| failure | Comments do not throw; actual grant/allocation failures use the neighboring public attempt boundary. |
| cost | No runtime instruction from prose. Analysis is O(C+Q log Q+Q log(R+1)+T) visitor work plus full binding, and O(Q+T) cells in the worst taller case. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0017

[Lines 125–214](../../../../../src/planner/update_pattern.cpp#L125); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L125-L214:sha256:c82c5e1dce3df48d98f7af0fc531aa78ae5ea2b13668f2ce913ebd247e88a988
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Apply proved source-event cases and native subtree/FIFO-leaf conditions to an already bound genuine candidate. |
| inputs / outputs | Borrow compiled source/candidate/declaration and receiving budget; return an ordinary Analysis with exact handles, case/transfer/height and native edge premises. |
| invariants | Constant routes need no transfer. All participating actual PhysicalInput.base rules insertion-only prove monotone occurrences; arbitrary height&lt;=1 needs only zero/one occurrence events. Other mixed cases require direct non-null no-ignored-column self-join-free lifetime transfer. Every native edge then needs a wholly insertion-only child subtree or a leaf sharing its parent's positive scope. Taller success is subtree_edges; unproved edges remain inspectable and overall unknown. No Trim/MixDetect or new height authority. |
| ownership | Candidate/declaration copies retain existing immutable owners. New edge data uses the receiving account. Table scratch and taller NodeId order/byte-flag vectors use receiving scratch; the order vector dies before edge evaluation and flags die before return. |
| failure | Existing budget/allocator failures unwind unpublished scratch/result; the public noexcept boundary returns no partial report. No private catch, retry, row mirror or runtime index. |
| cost | Beyond full binding, O(C+Q log Q+Q log(R+1)+T) charged visits/comparisons and O(Q+T) scratch/edge cells. All-source lookup can stop early; height&lt;=1 returns before scratch, height&lt;=2 allocates no subtree vectors, and leaf parents skip rule lookup. Scalar/encoder/allocator costs remain additional. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf) |

## B0018

[Lines 215–217](../../../../../src/planner/update_pattern.cpp#L215); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L215-L217:sha256:2deb363e39e251203a860a1224a42e402681a7896571315d40325554ca6782eb
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Clarify that the public boundary translates existing failures once and failed work never yields partial conditional context. |
| inputs / outputs | The following noexcept function returns Attempt. |
| invariants | Private visitors do not add catch layers; result publication occurs only after complete success. |
| ownership | Only a completed Analysis is moved into Attempt; inputs retain their owners. |
| failure | Existing ranking/resource, allocation, and unexpected errors map to stop codes. |
| cost | No independent cost beyond boundary dispatch and result wrapper. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf), [docs/selection.md](../../../../selection.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0019

[Lines 218–237](../../../../../src/planner/update_pattern.cpp#L218); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L218-L237:sha256:6e8e18cc69f7c1dc93728c902d4703adaeb2e435da7f2a1859da963b42696496
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the nonthrowing public attempt boundary for conditional candidate analysis. |
| inputs / outputs | Emplaces a ranking Budget with caller limits/account; invokes private analyse; records timing/usage; publishes optional Analysis only on complete success. |
| invariants | No partial Analysis escapes on work, binding, memory, or internal failure; the report remains conditional metadata, not live enforcement or delay proof. |
| ownership | Budget is stack state. New binding/table scratch and edge storage use the receiving account. Source is borrowed synchronously; report retains only the existing candidate and declaration handles plus its edge vector. |
| failure | Maps rd::Failure to its stop, bad_alloc to allocation_failure, and other exceptions to internal_error; usage is retained if budget initialized. |
| cost | Processes binding plus O(C + Q log Q + Q log(R+1) + tree size) analyzer checkpoints and O(Q) scratch/edges; no per-update execution. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf), [docs/selection.md](../../../../selection.md), [docs/update_patterns.md](../../../../update_patterns.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0020

[Lines 238–238](../../../../../src/planner/update_pattern.cpp#L238); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L238-L238:sha256:ea189de99fbaf38e66b3d928a8089b5973fe52ce5b68f5b6bcef8c87f8dc374e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the public planner-pattern implementation namespace. |
| inputs / outputs | No inputs/outputs. |
| invariants | Namespace closure adds no new behavior. |
| ownership | No ownership effect. |
| failure | No failure path. |
| cost | No runtime cost. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |
