# `src/planner/meta_candidates.cpp` — block usage map

[Source](../../../../../src/planner/meta_candidates.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Search the finite canonical tree space and retain resumable evidence for exact minimum-height claims.

Snapshot SHA-256: `d58b425012805cd621fb1d0c8698e51206013aa7dcb525034affa230b6681830`. 375 lines partitioned into 39 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [search](../../../subsystem_contracts.md#search). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/planner/meta_candidates.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 9–9](../../../../../src/planner/meta_candidates.cpp#L9) | Type/record definition: struct Halt |  · [reviewed contract](#b0002) |
| [B0003 · 10–32](../../../../../src/planner/meta_candidates.cpp#L10) | Type/record definition: struct Budget | source comment (unverified): // One admitted logical recursion frame, not stack-byte accounting. · [reviewed contract](#b0003) |
| [B0004 · 33–37](../../../../../src/planner/meta_candidates.cpp#L33) | Callable definition: template&lt;class T&gt; void append(std::vector&lt;T&gt;& into, T value, Budget& b) | calls step, cells, size, max_size; growth push_back · [reviewed contract](#b0004) |
| [B0005 · 38–41](../../../../../src/planner/meta_candidates.cpp#L38) | Callable definition: void variable(Scope& into, VariableId value, Budget& b) | calls step, contains, cells, insert; growth insert · [reviewed contract](#b0005) |
| [B0006 · 42–44](../../../../../src/planner/meta_candidates.cpp#L42) | Callable definition: Scope copied(const Scope& from, Budget& b) | calls step, cells, size; returns from · [reviewed contract](#b0006) |
| [B0007 · 45–53](../../../../../src/planner/meta_candidates.cpp#L45) | Callable definition: bool covers(const Scope& large, const Scope& small, Budget& b) | calls begin, step, end; returns false; true; 2 loop sites · [reviewed contract](#b0007) |
| [B0008 · 54–56](../../../../../src/planner/meta_candidates.cpp#L54) | Callable definition: bool equal(const Scope& a, const Scope& c, Budget& b) | calls step, size, covers; returns a.size() == c.size() && covers(a, c, b) · [reviewed contract](#b0008) |
| [B0009 · 57–67](../../../../../src/planner/meta_candidates.cpp#L57) | Callable definition: Scope intersection(const Scope& a, const Scope& c, Budget& b) | calls begin, end, step, variable; returns result; 1 loop sites · [reviewed contract](#b0009) |
| [B0010 · 68–69](../../../../../src/planner/meta_candidates.cpp#L68) | Explanatory comments or spacing. | source comment (unverified): // Descending dynamic binary subsets: visit the full set first, then every · [reviewed contract](#b0010) |
| [B0011 · 70–81](../../../../../src/planner/meta_candidates.cpp#L70) | Callable definition: bool previous(std::vector&lt;unsigned char&gt;& digits, Budget& b) | calls size, step; returns true; false; 2 loop sites; source comment (unverified): // Descending dynamic binary subsets: visit the full set first, then every · [reviewed contract](#b0011) |
| [B0012 · 82–82](../../../../../src/planner/meta_candidates.cpp#L82) | Explanatory comments or spacing. |  |
| [B0013 · 83–87](../../../../../src/planner/meta_candidates.cpp#L83) | Type/record definition: struct PrefixNode | source comment (unverified): // Only generalized nodes store a scope; native scopes are shared. · [reviewed contract](#b0013) |
| [B0014 · 88–88](../../../../../src/planner/meta_candidates.cpp#L88) | Type/record definition: struct Prefix |  · [reviewed contract](#b0014) |
| [B0015 · 89–89](../../../../../src/planner/meta_candidates.cpp#L89) | declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0015) |
| [B0016 · 90–90](../../../../../src/planner/meta_candidates.cpp#L90) | Type/record definition: struct Branch |  · [reviewed contract](#b0016) |
| [B0017 · 91–102](../../../../../src/planner/meta_candidates.cpp#L91) | declares types or opens a type body; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0017) |
| [B0018 · 103–110](../../../../../src/planner/meta_candidates.cpp#L103) | Callable definition: void scopes() | calls step, cells, size, resize; growth resize; 2 loop sites · [reviewed contract](#b0018) |
| [B0019 · 111–113](../../../../../src/planner/meta_candidates.cpp#L111) | Callable definition: void sort(std::vector&lt;std::size_t&gt;& values) | calls std::sort, begin, end, step; returns a &lt; c · [reviewed contract](#b0019) |
| [B0020 · 114–115](../../../../../src/planner/meta_candidates.cpp#L114) | Explanatory comments or spacing. | source comment (unverified): // Parent references are checked before indexing. Connectivity and induced · [reviewed contract](#b0020) |
| [B0021 · 116–146](../../../../../src/planner/meta_candidates.cpp#L116) | Callable definition: void graph(const JoinTree& tree) | calls size, cells, assign, step; 6 loop sites; source comment (unverified): // Parent references are checked before indexing. Connectivity and induced · [reviewed contract](#b0021) |
| [B0022 · 147–156](../../../../../src/planner/meta_candidates.cpp#L147) | Callable definition: bool connected(const std::vector&lt;std::size_t&gt;& selected) | calls cells, size, seen, append; returns walk.size() == selected.size(); 2 loop sites · [reviewed contract](#b0022) |
| [B0023 · 157–158](../../../../../src/planner/meta_candidates.cpp#L157) | Explanatory comments or spacing. | source comment (unverified): // Removing R--R edges leaves one native component per first-native root. · [reviewed contract](#b0023) |
| [B0024 · 159–178](../../../../../src/planner/meta_candidates.cpp#L159) | Callable definition: std::size_t forest(const std::vector&lt;std::size_t&gt;& selected) | calls size, cells, assign, depth; returns height; 3 loop sites; source comment (unverified): // Removing R--R edges leaves one native component per first-native root. · [reviewed contract](#b0024) |
| [B0025 · 179–187](../../../../../src/planner/meta_candidates.cpp#L179) | Callable definition: Scope common(const std::vector&lt;std::size_t&gt;& selected) | calls copied, front, size, begin; returns result; 2 loop sites · [reviewed contract](#b0025) |
| [B0026 · 188–199](../../../../../src/planner/meta_candidates.cpp#L188) | Callable definition: std::vector&lt;std::size_t&gt; branch(std::size_t anchor, std::size_t entry, const std::vector&lt;unsigned char&gt;& member) | calls cells, size, seen, append; returns result; 2 loop sites · [reviewed contract](#b0026) |
| [B0027 · 200–201](../../../../../src/planner/meta_candidates.cpp#L200) | Explanatory comments or spacing. | source comment (unverified): // Copy a child into one disjoint block. Input indices stay stable; checked · [reviewed contract](#b0027) |
| [B0028 · 202–215](../../../../../src/planner/meta_candidates.cpp#L202) | Callable definition: std::size_t merge(Prefix& into, const Prefix& child) | calls size, empty, max_size, step; returns offset + child.root; 2 loop sites; source comment (unverified): // Copy a child into one disjoint block. Input indices stay stable; checked · [reviewed contract](#b0028) |
| [B0029 · 216–249](../../../../../src/planner/meta_candidates.cpp#L216) | Callable definition: void emit(const Prefix& prefix) | calls step, size, cells, positions; 4 loop sites · [reviewed contract](#b0029) |
| [B0030 · 250–252](../../../../../src/planner/meta_candidates.cpp#L250) | Callable definition: void retain(Prefix prefix, Family& family, bool top) | calls emit, append, std::move · [reviewed contract](#b0030) |
| [B0031 · 253–256](../../../../../src/planner/meta_candidates.cpp#L253) | Callable definition: Family descend(const std::vector&lt;std::size_t&gt;& selected, std::size_t depth) | calls enter, lift; returns lift(selected, depth + 1, false) · [reviewed contract](#b0031) |
| [B0032 · 257–259](../../../../../src/planner/meta_candidates.cpp#L257) | Explanatory comments or spacing. | source comment (unverified): // For a generalized cluster S, Guard/RIP force chi=intersection(scope\[r\],r∈S). · [reviewed contract](#b0032) |
| [B0033 · 260–322](../../../../../src/planner/meta_candidates.cpp#L260) | Callable definition: Family lift(const std::vector&lt;std::size_t&gt;& selected, std::size_t depth, bool top) | calls step, size, fragment, append; returns result; result; 14 loop sites; source comment (unverified): // For a generalized cluster S, Guard/RIP force chi=intersection(scope\[r\],r∈S). · [reviewed contract](#b0033) |
| [B0034 · 323–333](../../../../../src/planner/meta_candidates.cpp#L323) | Callable definition: void root_sets() | calls size, cells, assign, step; 3 loop sites · [reviewed contract](#b0034) |
| [B0035 · 334–337](../../../../../src/planner/meta_candidates.cpp#L334) | Callable definition: public: Mapper(const Query& q, std::size_t height, const MetaMappingLimits& limits, MetaCandidateReport& diagnostics, std::vector… | calls query, required_height, report, output · [reviewed contract](#b0035) |
| [B0036 · 338–347](../../../../../src/planner/meta_candidates.cpp#L338) | Callable definition: void run(const std::vector&lt;JoinTree&gt;& trees) | calls scopes, step, size, graph; 1 loop sites; source comment (unverified): // One orientation represents each undirected J. · [reviewed contract](#b0036) |
| [B0037 · 348–350](../../../../../src/planner/meta_candidates.cpp#L348) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0037) |
| [B0038 · 351–374](../../../../../src/planner/meta_candidates.cpp#L351) | Callable definition: PreparedMetaCandidates prepare_meta_candidates(VerifiedOptimum proof, MetaCandidateLimits limits) | calls valid, Error, binding, construct; returns result; result; growth emplace · [reviewed contract](#b0038) |
| [B0039 · 375–375](../../../../../src/planner/meta_candidates.cpp#L375) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::meta · [reviewed contract](#b0039) |

## B0001

[Lines 1–8](../../../../../src/planner/meta_candidates.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:1fe91178bb882e24ae0bae47bebdfa644efbc4266e80a8314fa82a1cad5d43c7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the implementation to its public API and isolate its budget and inverse-contraction helpers in an anonymous namespace. |
| inputs / outputs | The includes supply planner/error types, sorting/max, numeric sentinels and move support for the definitions below. |
| invariants | Only the public preparation function has API linkage. These declarations create no fallback producer, runtime registration or shared planner state. |
| ownership | No live source binding, candidate or graph owner is created by these directives and namespace openings. |
| failure | Dependency or linkage errors fail compilation; this scaffolding has no runtime error handling. |
| cost | Compile/link parsing only; no executable mapping or update operation is charged to these directives and braces. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0002

[Lines 9–9](../../../../../src/planner/meta_candidates.cpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L9-L9:sha256:7ff07fbdfe89eb6b99229fb89b50f5bc3ca8d923f22155f969fa28355e174385
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry one selected mapping stop to the single public mapping catch boundary. |
| inputs / outputs | Private helpers throw Halt with one MappingStop; prepare_meta_candidates catches exactly this private payload. |
| invariants | The payload does not turn OOM, crown::Error or arbitrary exceptions into a successful or merely incomplete result. |
| ownership | Halt owns one scalar enum and retains neither a partial draft nor an allocated diagnostic message. |
| failure | Unwinding releases current local scratch. Previously appended complete drafts survive in the caller-owned output vector until provider transfer. |
| cost | Fixed-size payload declaration; throwing/unwinding is cold stop-path work outside the logical selected-checkpoint counter. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0003

[Lines 10–32](../../../../../src/planner/meta_candidates.cpp#L10); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L10-L32:sha256:be6039f03cc673d2631b1d4f21686be7bd190f0908a7dedcb59d45a475daaa85
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enforce mapping work, cumulative explicit cells/fragments and logical recursion-depth caps before admitting each corresponding operation. |
| inputs / outputs | Budget borrows one MetaMappingLimits and one zero-initialized MetaMappingUsage. step increments work; cells admits count; fragment also steps; enter also steps, checks depth, charges one logical frame and updates peak_depth. |
| invariants | Usage never exceeds grants under this private lifecycle: equality checks precede unit increments, cells subtracts from an unexceeded cap, and every actual recursive descent is pre-admitted. A logical frame is not a stack-byte measurement. |
| ownership | The helper holds references valid for the synchronous mapper lifetime; it neither owns allocations nor shares mutable state across calls. |
| failure | Each denied operation throws its named Halt before changing that counter; a later denial may retain earlier work charges in the same method. General allocator failures remain untouched. |
| cost | Each check uses fixed scalar arithmetic. Fragment/cell charges are cumulative construction counts; allocator requests, capacity, cleanup and total CPU are excluded. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0004

[Lines 33–37](../../../../../src/planner/meta_candidates.cpp#L33); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L33-L37:sha256:ccb1707aa21ca267cce2ec80c4b1b2c5b7c835beaaf0475dc71fda7dffc5fbb7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Append one owned vector entry only after charging its logical work/cell and checking representable container growth. |
| inputs / outputs | append takes a mutable vector, a by-value element and Budget, then moves the element into the vector on success. |
| invariants | The max_size guard precedes push_back; no element is published into the destination before the append succeeds. Constructing the by-value argument can already have incurred separately charged work/storage. |
| ownership | The vector owns a moved-in element after success. The local argument is cleaned up on denial or allocation failure; no borrowed reference to it is retained. |
| failure | Work/cell denial throws Halt; maximum representable vector size maps to cell_limit. push_back allocation or element exceptions propagate instead of becoming completion. |
| cost | One selected work unit and one explicit vector cell, plus standard-vector growth/relocation and element move/destruction costs outside that logical count. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0005

[Lines 38–41](../../../../../src/planner/meta_candidates.cpp#L38); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L41:sha256:5ee879566c2805695267bc209c423e3a1e024d65a9caac435b44bae5c66ccef3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Insert one variable into an ordered scope without charging duplicate members as new cells. |
| inputs / outputs | A borrowed Scope, VariableId and Budget yield the same set with value present after success. |
| invariants | The helper charges a work checkpoint for every request; only an absent value consumes a cell, and that charge precedes insertion. |
| ownership | The destination owns any newly allocated set node. VariableId is scalar; neither source query terms nor external set storage is retained. |
| failure | Denied work/cell charges throw Halt before insertion. Set allocation failure propagates and does not fabricate the missing member. |
| cost | One charged request and at most one new cell; ordered-set lookup/insertion comparisons and allocator overhead remain additional costs. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0006

[Lines 42–44](../../../../../src/planner/meta_candidates.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L42-L44:sha256:723dfd7a3e27debfb3716167a5d5844d47ec9e5373aabff21094719488991cc2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an independent scope copy after admitting all its explicit variable cells. |
| inputs / outputs | A borrowed Scope and Budget produce an owning equal Scope value on success. |
| invariants | The complete source cardinality is cell-charged before the copy. A copied native or generalized scope never aliases the original set storage. |
| ownership | Returned scope owns its set nodes; source remains unchanged. Standard container cleanup handles any failed partial allocation. |
| failure | Work/cell denial throws Halt before copying. Scope allocation failures propagate; no empty-scope replacement is returned. |
| cost | One selected work step and k cumulative cells for a k-member scope, plus actual set copy/allocation/destruction costs. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0007

[Lines 45–53](../../../../../src/planner/meta_candidates.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L53:sha256:9aeb91449e5b2dabfdedaee531e15402e309617d60780fcef9287b3c8415eb25
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test ordered scope containment for graph and inverse-fiber constraints without creating a scope copy. |
| inputs / outputs | covers(large,small,budget) returns whether every unique member of small occurs in large. |
| invariants | The large iterator advances monotonically; inputs are unchanged, and an empty small scope is contained. Returning false is a predicate outcome rather than a query error. |
| ownership | Only scalar IDs and borrowed set iterators live on the stack; no container is owned or retained after return. |
| failure | A work stop throws Halt instead of returning a partially evaluated answer. Ordinary noncontainment returns false. |
| cost | Linear ordered-iterator traversal in the two scope sizes, with selected member/advance checkpoints; no set allocation or global CPU bound. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/pdf/2301.04003v2) |

## B0008

[Lines 54–56](../../../../../src/planner/meta_candidates.cpp#L54); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L54-L56:sha256:5d96766d7ac3568884bcd33c0ad37d24504d6428a08570bd2e83d5b7742fcb2c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Test exact scope equality with a cardinality short circuit followed by ordered containment. |
| inputs / outputs | Two borrowed scopes and Budget produce true precisely when their unique variable sets agree. |
| invariants | For ordered sets, equal cardinality and containment imply equality; equal scope does not merge physical occurrence identity. |
| ownership | The helper creates no owning container and updates only the borrowed usage ledger. |
| failure | A checkpoint can throw Halt; unequal size or missing member returns false without an exception. |
| cost | One selected initial step, plus the containment traversal only when sizes agree; no scope-copy allocation. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/pdf/2301.04003v2) |

## B0009

[Lines 57–67](../../../../../src/planner/meta_candidates.cpp#L57); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L57-L67:sha256:3b0dba0fb815e8daad24b788d0fefb1dbd64ebd7b669468287c7c0a6a0d8468d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build the actual separator scope shared by two native bags for boundary and eligible-cut tests. |
| inputs / outputs | Two borrowed ordered scopes and Budget produce a new owning intersection scope. |
| invariants | Both iterators advance monotonically, and a value is inserted exactly when present in both input scopes. This is a local set operation, not CROWN admission. |
| ownership | The result owns its set nodes; input scopes remain borrowed and unchanged. |
| failure | Work/cell stops throw Halt; set allocation failure propagates and standard unwinding releases the partial result. |
| cost | Linear merge scan in input cardinalities, selected comparison steps and one charged cell per distinct intersection member; actual ordered-set insertion adds separate work. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/pdf/2301.04003v2) |

## B0010

[Lines 68–69](../../../../../src/planner/meta_candidates.cpp#L68); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L68-L69:sha256:36e836781e87118810f594012f7cd2ac57d2a4c038f4aae598ef708cbab93ec9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Describe the dynamic subset enumeration order and avoid any machine-word-width family restriction. |
| inputs / outputs | The following previous helper consumes a nonempty unsigned-byte digit vector initialized to all ones by its callers. |
| invariants | Full set comes first, followed by descending binary subsets; zero is a terminating state rather than an emitted subset. No power-set cardinality or fixed-width mask is computed. |
| ownership | The comments own no digits; the subsequent helper mutates a caller-owned local vector. |
| failure | The comments introduce no failure path or fallback when a subset family is large. |
| cost | No runtime cost for comments; actual subset generation and its exponential family are charged in the helper and callers. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0011

[Lines 70–81](../../../../../src/planner/meta_candidates.cpp#L70); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L70-L81:sha256:48a16cbfd20b466ca1aae60c7e8aa07b1f36c20ecf443bda90b549df8db83ea1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance a local dynamic binary counter to the next descending nonempty subset. |
| inputs / outputs | previous mutates a nonempty byte vector containing only 0/1 digits and returns true iff the resulting subset is nonzero. |
| invariants | Borrowing through trailing zeros and clearing the rightmost one visits every smaller subset once from an initial all-ones vector. Reverse indexing tests i before decrement, avoiding unsigned underflow. |
| ownership | The caller owns digits; only indices and a byte copy are local. No word-sized representation or extra vector allocation is used. |
| failure | Work exhaustion may leave this private vector partly changed, then aborts the nonresumable mapping pass through Halt. No resumed cursor is promised. |
| cost | Linear digit traversal per advance in the worst case and selected checkpoint charges; repeated calls enumerate exponentially many subsets until capped. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0013

[Lines 83–87](../../../../../src/planner/meta_candidates.cpp#L83); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L83-L87:sha256:76fbdd32a0e6c29a7f8d8932ac0f5ff8925808a5705d5a3cdf88c4490a343d0f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent a raw native leaf or generalized node while constructing an inverse-contraction prefix. |
| inputs / outputs | An engaged occurrence stores an original atom index including zero; absent occurrence denotes generalized. scope stores only a generalized bag, and children are indices in its containing Prefix. |
| invariants | Native scopes are obtained from Mapper.native at emission rather than duplicated here. These raw nodes are private drafts, not admitted CROWN tree nodes. |
| ownership | Each value owns its generalized scope and child-index vector. The optional index retains physical identity without retaining an external atom pointer. |
| failure | Raw aggregate construction does not validate graph invariants; allocation/copy errors propagate. Later merge/emission checks reject malformed internal indices. |
| cost | Scalar fields are fixed-size; owning scope/vector copy and destruction visit stored members and may allocate/free storage during cold planning. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/pdf/2301.04003v2) |

## B0014

[Lines 88–88](../../../../../src/planner/meta_candidates.cpp#L88); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L88-L88:sha256:d1fad1578a6a4a6721ee5f2410d83ecfeb6ba24e6cf92f3a775bf2df2af90d4d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one completed raw generalized-prefix fragment and its root index. |
| inputs / outputs | Prefix contains a vector of PrefixNode values and root, defaulting to zero for the subsequently built nonempty fragment. |
| invariants | Every retained fragment has a nonempty vector and valid root; construction may temporarily be empty. Root is an index within this owner, not an external NodeId or proof. |
| ownership | The value owns all nested node scopes and child vectors; moves transfer the fragment and copies duplicate its containers. |
| failure | Container growth/copy failures propagate. Internal malformed fragments are rejected by merge or downstream P02 rather than accepted through the default root. |
| cost | Fragment copying/destruction scales with its nodes, children and generalized scope members; the declaration itself performs no search. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0015

[Lines 89–89](../../../../../src/planner/meta_candidates.cpp#L89); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L89-L89:sha256:d90a3ad55fb72ef0845a65ccf6fac0d8e718af39b59b42b5b1829ce6b862dee3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name an owning collection of all raw prefix variants produced for one recursive cluster. |
| inputs / outputs | Family is exactly std::vector&lt;Prefix&gt;, used as a recursive result and Cartesian-choice domain. |
| invariants | An empty family means that branch/center has no admissible local lift, not that a checked global plan was disproved. |
| ownership | The vector owns each independent Prefix and all of its nested containers; no variant borrows another variant's node storage. |
| failure | Allocation failures follow standard vector behavior and propagate; the alias adds no fallback or exception translation. |
| cost | Collection growth/relocation and destruction depend on all stored fragments; aliasing a type name adds no per-update work. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0016

[Lines 90–90](../../../../../src/planner/meta_candidates.cpp#L90); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L90-L90:sha256:3c00b964ece193306a9e79a7deae4a3cd0f6e31ec0534ab0456a5411283967d0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep one eligible whole branch's sorted first-native leaves together with every recursively prepared prefix variant. |
| inputs / outputs | leaves owns occurrence indices for one component of the cluster after deleting its anchor; family owns that component's nonempty lift choices. |
| invariants | Retained branches attach at their minimum occurrence and have the forced crossing separator; equal scopes do not coalesce their leaves. |
| ownership | Both vectors and all nested prefixes belong to Branch. Later choices borrow pointers only while the enclosing stable branch vector is no longer growing. |
| failure | Construction/moves may allocate in prior preparation; invalid or empty branch families are excluded by lift before retention. General OOM propagates. |
| cost | Storage and cleanup scale with leaf entries and all variants. Precomputing a branch once avoids repeating its recursion for every selected-cut subset. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0017

[Lines 91–102](../../../../../src/planner/meta_candidates.cpp#L91); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L91-L102:sha256:128c7e6fa0d0a335d448b2b86227b10636af62e7b58f4e2b5b7c61eaf7ddd0e0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Define the mapper's synchronous borrowed inputs and independently owned graph, scope and orientation scratch. |
| inputs / outputs | Mapper binds Query, required original height, report, output vector and Budget, then owns native scopes, undirected adjacency, root membership bits and native-parent indices. |
| invariants | The mapper is private, per call and nonresumable. required_height comes from the supplied original proof; scratch contains no lower-bound authority or runtime row/index state. |
| ownership | Borrowed references outlive Mapper within prepare_meta_candidates; its vectors own scratch. Completed drafts belong to the borrowed output vector and can survive mapper destruction. |
| failure | Default vector construction creates no graph. Later named helper stops unwind mapper-owned scratch without deleting previously appended output drafts. |
| cost | Member/reference initialization is small; storage grows only through later charged methods. No background worker, cross-query cache or update hook is created. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0018

[Lines 103–110](../../../../../src/planner/meta_candidates.cpp#L103); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L103-L110:sha256:bc91ce79621d38a2bfb392195d26f72dc5042f06b9341668782957592d48cb53
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract one complete variable scope for each original atom while preserving occurrence order and identity. |
| inputs / outputs | Borrowed query terms populate Mapper.native: VariableId terms contribute unique variables; constants and ignored columns do not. |
| invariants | native.size equals query.atoms.size and index i always denotes original occurrence i. Equal scopes or repeated tables remain distinct entries; repeated variables within an atom are set-unique. |
| ownership | Mapper owns the scope vector and new set nodes; Query and its terms remain borrowed and unchanged. |
| failure | Vector cells are admitted before resize and unique variable cells before insertion. Work/cell Halt stops or OOM propagate out of this private pass. |
| cost | One explicit cell per scope slot plus cells for new variable members and selected term checkpoints. Standard set lookup and vector allocation add costs outside those counters. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/pdf/2301.04003v2) |

## B0019

[Lines 111–113](../../../../../src/planner/meta_candidates.cpp#L111); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L111-L113:sha256:b9c673250312287748d82cbff8922c7512301179d016fc9b6e42fe61e79ea101
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Put occurrence-index vectors into deterministic ascending order for graph traversal and canonical anchors. |
| inputs / outputs | sort mutates a borrowed index vector using std::sort and a numeric comparator that charges each invocation. |
| invariants | When it returns, indices are ascending and their multiset is unchanged. A comparator returning normally is the strict order a&lt;c; the work grant is checked before each comparison result. |
| ownership | The caller retains vector ownership. The comparator borrows Budget only for the duration of sorting and retains no elements. |
| failure | A work-limit Halt can leave private scratch partially permuted; the entire nonresumable preparation then stops. No sorted-result claim is made after an exception. |
| cost | Standard comparison-sort work with selected comparator charges. Library moves, recursion/internal storage and destruction are not exact CPU or byte charges. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0020

[Lines 114–115](../../../../../src/planner/meta_candidates.cpp#L114); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L114-L115:sha256:99a0a29a0ece565b68939e93d9ee12473dd7a1a065d8fa8db9aef77ed5bbb866
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the independent ordinary-input topology and running-intersection checks performed by graph. |
| inputs / outputs | The following helper reads one occurrence-labelled ordinary parent vector rather than trusting producer metadata alone. |
| invariants | References are checked before index use; connectivity plus variable-induced edge counts establish an ordinary join tree, not head feasibility or a height optimum. |
| ownership | Comments do not retain the input or create a checked capability; graph owns only per-call scratch. |
| failure | The comments introduce no recovery path; malformed ordinary inputs will take invalid_join_tree in the helper. |
| cost | No comment execution cost; actual topology/RIP scans have explicit graph checkpoints and allocations. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [include/crown/planner/meta_join_trees.hpp](../../../../../include/crown/planner/meta_join_trees.hpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm5) |

## B0021

[Lines 116–146](../../../../../src/planner/meta_candidates.cpp#L116); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L116-L146:sha256:bf66cbafe06e0efbe8539a8495998bb284c0c080434fb48c2b590d148cb66150
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rebuild and independently validate each canonical ordinary tree before enumerating its inverse fiber. |
| inputs / outputs | graph consumes JoinTree root/parent indices and Mapper.native, producing sorted undirected adjacency or throwing a named stop. |
| invariants | Size, root and every nonroot parent are checked before indexing; n-1 nonself parent edges plus full connectivity give a tree. For each query variable, induced edge count vertices-1 then establishes running intersection. Physical occurrences remain indexed independently of scope equality. |
| ownership | Mapper owns rebuilt adjacency; local seen/walk vectors own checker scratch. The input parent vector and native scopes remain borrowed and unchanged. |
| failure | Malformed topology or RIP throws invalid_join_tree. Work/cell stops unwind scratch; allocation failure propagates. This check creates no P02 or minimum-height capability. |
| cost | Adjacency, connectivity and per-variable/per-occurrence scans with selected checkpoints, plus neighbor sorting. Explicit vector cells are charged; set lookup, container capacity and total CPU are not fully metered. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [include/crown/planner/meta_join_trees.hpp](../../../../../include/crown/planner/meta_join_trees.hpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm5) |

## B0022

[Lines 147–156](../../../../../src/planner/meta_candidates.cpp#L147); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L147-L156:sha256:ebb65c0ef6b82cf839e60a5b8dfb3549bd34ea16d27a4258064b9504b80ba7f3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recognize whether a proposed first-native root set induces a connected subtree of the current ordinary tree. |
| inputs / outputs | selected is a nonempty sorted vector matching roots bits; connected traverses only roots-marked neighbors and compares reached count to selected.size. |
| invariants | The helper relies on graph having established a tree and all selected indices being valid. For this private caller, selected.front is defined and traversal cannot leave the selected set. |
| ownership | Local seen and walk vectors own temporary BFS state; adjacency, roots and selected remain borrowed without mutation. |
| failure | Disconnected root sets return false and are skipped normally. Work/cell stops throw Halt; scratch allocation failure propagates. |
| cost | Selected-subtree traversal plus full-size seen initialization; explicit scratch slots and walk entries are cell-charged, with selected edge checkpoints. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/pdf/2301.04003v2) |

## B0023

[Lines 157–158](../../../../../src/planner/meta_candidates.cpp#L157); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L157-L158:sha256:3f6c2a38ce1b4ab6fb31ae8f1555185e95cc7c10016081bd797037b60ebd6293
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State why native-only forest height is the correct early pruning measure for a connected first-native root set. |
| inputs / outputs | The following forest helper deletes exactly ordinary edges with both endpoints in R, then orients all remaining components at their unique selected root. |
| invariants | In a tree with connected nonempty R, every remaining component contains exactly one R vertex. Generalized-prefix nodes contribute zero native height, so their topology cannot change this forest height. |
| ownership | The comments introduce no tree owner; the helper stores only the native parent orientation needed for later draft emission. |
| failure | This local argument assumes the graph and connected-root checks succeeded. It is not a replacement for final P02 or independent original-minimum proof. |
| cost | No comment execution cost; orientation and height computation are charged by the subsequent graph traversal. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/pdf/2301.04003v2) |

## B0024

[Lines 159–178](../../../../../src/planner/meta_candidates.cpp#L159); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L159-L178:sha256:dc2949c1250e68d3c5e34bf5012d5a0da6cac885ff06ff833279df99e5a46d47
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Orient the native forest below a connected selected root set and compute its maximum root-to-leaf native count. |
| inputs / outputs | forest assigns native_parent and local depth via multi-source BFS after excluding R--R edges, returning the measured maximum starting at one. |
| invariants | Each selected root parents itself; every other native occurrence receives exactly one valid native parent. Connectivity of R ensures one root per component, and depth cannot exceed the representable allocated occurrence count. |
| ownership | Mapper owns native_parent for emission; local depth/walk vectors own transient storage. Selected roots and ordinary adjacency remain borrowed. |
| failure | Failure to visit all occurrences throws invalid_join_tree. Denied vector/work charges throw Halt; allocation failures propagate. The returned height is only a measured draft constraint until P02. |
| cost | Linear forest traversal plus n-sized parent/depth initialization and explicit walk cells. These logical charges exclude allocator capacity and complete machine-instruction accounting. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/pdf/2301.04003v2), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp) |

## B0025

[Lines 179–187](../../../../../src/planner/meta_candidates.cpp#L179); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L179-L187:sha256:23da04da960a4ded242ce3cdb2acaa694ad3b76fe47a883222c86e2049275e2f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compute the forced generalized scope for one nonempty first-native cluster by intersecting all its complete native bags. |
| inputs / outputs | common takes sorted valid selected indices and returns an owned Scope equal to their intersection I(S). |
| invariants | A copied first scope is only reduced by erasure; no variable absent from any selected native bag can remain. The equality with a valid normalized generalized bag follows from the local Guard/RIP argument, not a P3 enumeration theorem. |
| ownership | The result owns its independent set storage. Mapper.native remains borrowed and unchanged. |
| failure | Work/cell stops can abort copying or intersection checks. Allocation failure from the initial copy propagates; erasure uses ordinary container cleanup. |
| cost | One charged complete first-bag copy, then selected membership/erase checkpoints across remaining bags. Set membership and freeing erased nodes add separate costs. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/pdf/2301.04003v2), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp) |

## B0026

[Lines 188–199](../../../../../src/planner/meta_candidates.cpp#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L188-L199:sha256:fc47fd74678cbaa8d9f91ecb7dfee4565a03feff43ff8ddb4f3190601f965a5f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Extract one whole component of the current cluster after its canonical anchor is removed. |
| inputs / outputs | branch receives valid distinct anchor/entry neighbors and a cluster membership vector, then returns sorted occurrence IDs reachable from entry without the anchor. |
| invariants | The caller ensures entry belongs to the connected cluster. In an ordinary tree, blocking the anchor isolates exactly one incident whole branch; the nonempty sorted result identifies its minimum occurrence. |
| ownership | Local seen/result vectors own the traversal and returned leaf IDs. They retain no pointer into adjacency or member storage. |
| failure | Work/cell stops abort through Halt and OOM propagates. The caller, rather than this helper, filters branches whose cut endpoint is not their minimum. |
| cost | Full-size seen initialization, component edge traversal and deterministic sort; explicit vector entries and selected graph/comparator checkpoints are charged. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0027

[Lines 200–201](../../../../../src/planner/meta_candidates.cpp#L200); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L200-L201:sha256:84608b11636083f254776a398122f4ab79b2c0c18b523aacd3d6c1cde1e02ee0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Document the index-offset and ownership obligations for composing disjoint child fragments. |
| inputs / outputs | The following merge helper appends an independent child-node block to a parent prefix and remaps child indices by the old parent size. |
| invariants | Room must be representable before any offset addition. Existing input indices remain unchanged, and appended blocks cannot alias child storage. |
| ownership | Comments establish no owner; the parent will own copied scopes and vectors after a successful merge. |
| failure | The explanatory region performs no catch; malformed or overlarge fragments are rejected by merge before unsafe arithmetic. |
| cost | No execution cost for comments. Actual copying, append growth and cleanup remain proportional to fragment data. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0028

[Lines 202–215](../../../../../src/planner/meta_candidates.cpp#L202); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L202-L215:sha256:4e53f757942680e0c297c0fd607dd89c622b1fe570995f522d18752bb420d43f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Clone a completed child prefix into a disjoint parent-node block and return its translated root index. |
| inputs / outputs | merge mutates into using a borrowed nonempty child. It copies each node scope and adds offset to every checked child index and the checked child root. |
| invariants | The private call sites use distinct parent/child owners. child.size &lt;= into.max_size-offset bounds all additions; child root and child indices must be within the child block. Existing parent indices remain stable even if vector storage relocates. |
| ownership | The destination owns all cloned node scopes and child vectors. The source is unchanged; no destination pointer into the source survives. |
| failure | Empty/bad-root/overlarge fragments stop as fragment_limit; bad child indices stop as invalid_join_tree. Budget or allocation failure can leave only local parent scratch partly built, never a published partial tree. |
| cost | Linear clone of nodes, scope members and child edges with explicit append/copy charges; vector capacity/relocation and cleanup are additional cold costs. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0029

[Lines 216–249](../../../../../src/planner/meta_candidates.cpp#L216); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L216-L249:sha256:bf9db78d91bdaa5e02a4952bf909c20a6d872fb01a2d058c1373cac57f5880a0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize one complete raw CROWN tree by attaching the native forest below a constructed generalized prefix. |
| inputs / outputs | emit reads a private valid Prefix and native_parent, creates unique meta-lift-index node IDs, copies full native/generalized scopes, appends missing native occurrences and then appends one complete output draft. |
| invariants | Output cap is checked before building. Every occurrence appears once; prefix child indices are checked and native forest indices rely on the prior validated orientation. A missing occurrence optional is distinguished from occurrence zero. No P02/head/height authority is minted; those gates occur later. |
| ownership | Local tree and positions own construction state. Successful output append transfers the whole independent tree; output_trees is updated only after that append. No child-prefix or query storage is borrowed by the draft. |
| failure | Invalid/duplicate occurrence or invalid prefix child index throws invalid_join_tree. Caps or OOM release the unfinished local tree while preserving earlier complete drafts; allocator/string errors propagate. |
| cost | Visits prefix nodes, scope members, native occurrences and forest edges; charges explicit vectors/scopes and selected work. ID formatting, string bytes, capacity, relocation and destruction remain additional costs. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/pdf/2301.04003v2), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp) |

## B0030

[Lines 250–252](../../../../../src/planner/meta_candidates.cpp#L250); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L250-L252:sha256:a5db423bf8103232eb9cc734483cbb21d039e554a4d420bd7325c9267bfe832f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route a completed prefix either to immediate top-level draft emission or into an owned recursive variant family. |
| inputs / outputs | retain consumes one Prefix, borrows a Family and top flag, and either invokes emit or appends the moved prefix to family. |
| invariants | Top-level variants are streamed into complete output drafts without retaining an additional Family copy. Recursive variants stay available for full Cartesian composition. |
| ownership | The by-value argument owns the fragment until emission cleanup or transfer into family; no variant is shared by mutable reference. |
| failure | emit/append stops propagate. A failed top-level emission does not append a partial draft; a stopped recursive append discards only its local pending fragment. |
| cost | One branch plus underlying full emission or charged vector append; by-value moves and nested destruction have their ordinary container costs. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0031

[Lines 253–256](../../../../../src/planner/meta_candidates.cpp#L253); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L253-L256:sha256:9f06976b1310c29b50811ce5bc5e1070792e9a228daad541ff7fc9ae9fbb31d4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit the next logical recursion level before calling lift for a strict child cluster. |
| inputs / outputs | descend borrows a nonempty selected cluster and current admitted depth, checks the next depth and returns the complete recursive Family. |
| invariants | Private callers maintain depth&lt;=limit. Equality is tested before depth+1, preventing size_t overflow at a maximal grant; Budget.enter checks work, next-depth cap and logical frame cells before the recursive push. |
| ownership | Selected remains borrowed only for the recursive call. The returned family owns all produced fragments; no persistent recursion cursor is kept. |
| failure | A depth/work/cell denial throws Halt before the recursive call. OOM or deeper stops unwind all current private scratch; preparation is nonresumable. |
| cost | Fixed scalar preflight plus the full recursive lift cost. One charged logical frame is not a measured stack-byte bound or a guarantee that arbitrary caller depth limits fit the process stack. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0032

[Lines 257–259](../../../../../src/planner/meta_candidates.cpp#L257); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L257-L259:sha256:320ca061f9c3b6f908c448f29878f68d3090a258ada9a619f843b8e64cf4f731
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | State the local forced-scope and canonical whole-branch characterization used by the generalized-prefix recursion. |
| inputs / outputs | For a non-singleton first-native cluster S, the next helper uses I(S) and the minimum occurrence anchor to enumerate inverse contractions. |
| invariants | P1 Definition 3.2 Guard and running intersection force chi=I(S); canonical contraction makes noncentral child blocks whole branches with separator I(S). This characterization is a local proof obligation, not P3 Algorithm 2/5 authority. |
| ownership | Comments own no cluster, scope or family; the following helper creates its own copies and borrowed traversal views. |
| failure | No executable failure mechanism appears here. Final original-binding P02 remains authoritative even for drafts generated by this argument. |
| cost | No comment execution cost; the subsequent exhaustive recursion may be exponential and is stopped by its explicit grants. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/pdf/2301.04003v2), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm5) |

## B0033

[Lines 260–322](../../../../../src/planner/meta_candidates.cpp#L260); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L260-L322:sha256:f792f1c87bd906e4b0e2f0f213b84fa818e6b2b993f0cac2059b308d8a2626a9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate every canonical normalized inverse-contraction prefix for one connected first-native cluster, or stream its top-level raw trees. |
| inputs / outputs | lift receives a nonempty sorted connected selected subset, admitted depth and top flag. Singleton becomes a native leaf; otherwise it uses I(S), outside-root boundary, eligible anchor branches, all nonempty cut subsets, recursive center/branch families and their full Cartesian products. |
| invariants | Outside boundary must fit I(S). An eligible cut separator equals I(S) and reaches the child block's minimum occurrence. Selected cuts leave a nonempty center containing min(S); every child cluster strictly shrinks, every generalized parent has at least two children, and disjoint child blocks cover S. Nonempty cut digits and choice families make mixed-radix indexing defined. No head-only root condition is imposed; final P02 decides Connex. |
| ownership | The function owns local scopes, membership bits, branch families, center variants, digits and assembled parent fragments. choices borrows stable local families only after branch growth ends; merge clones before retention, so emitted drafts borrow no local storage. |
| failure | A failed boundary or absent recursive choices returns an empty local family. Work/cell/fragment/output/depth Halt unwinds unfinished scratch and keeps only earlier complete drafts. OOM and container failures propagate; no heuristic, witness or normal-form fallback is substituted. |
| cost | Potentially exponential subset, recursive and Cartesian enumeration with selected checkpoint, cumulative fragment/cell and pre-push depth caps. Branch variants are precomputed once per cluster; copying, set operations, capacity, allocator overhead, strings and cleanup remain additional costs. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/pdf/2301.04003v2), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm5) |

## B0034

[Lines 323–333](../../../../../src/planner/meta_candidates.cpp#L323); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L323-L333:sha256:ff6de0bed038fd15730895f7d407a8956498ff605cdd70e06f9786f0c4f99ab4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Visit every nonempty first-native root subset of one canonical ordinary tree and prune only disconnected or wrong-native-height subsets. |
| inputs / outputs | root_sets initializes dynamic roots digits to all ones, collects selected occurrences in ascending order, checks connectivity, orients/measures the native forest and invokes lift at admitted depth one for the required original height. |
| invariants | Root bits never publish the zero subset. A connected R ensures exactly one root per native component; generalized prefix topology adds zero native height. required_height is the supplied independently verified original minimum, not a value inferred from ordinary enumeration. |
| ownership | Mapper owns mutable roots/native_parent; selected and recursive families are local. Complete drafts are owned by output. No fixed-width subset mask or persistent resume cursor exists. |
| failure | Disconnected or wrong-height subsets are ordinary skips; the latter increments height_pruned_root_sets. Other caps stop through Halt and OOM propagates, retaining earlier completed drafts only. |
| cost | Exponential dynamic subset search, connectivity/forest scans and recursive lifting. Each root_set counter increment follows a charged work step, bounding it by nonwrapping work usage; selected vector/frame cells are charged separately. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [exact paper reference](https://arxiv.org/pdf/2301.04003v2), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp) |

## B0035

[Lines 334–337](../../../../../src/planner/meta_candidates.cpp#L334); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L334-L337:sha256:f3915edee3781db28d6366502e730aef3c566c8d5bb03f29086cf19cd3a3e581
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind a private mapper to one synchronous preparation call without starting its search. |
| inputs / outputs | The constructor receives Query, required original height, mapping limits, mutable diagnostics and completed-draft output references. |
| invariants | Required height and diagnostic/output references belong to the current call. Budget references the same limits and report.mapping_usage used by all mapper helpers. |
| ownership | References are borrowed until Mapper destruction within prepare_meta_candidates. Scratch vectors default-construct as mapper-owned empty containers; drafts stay owned by the outer call. |
| failure | The constructor does not admit the query or validate a graph, and adds no catch or recovery behavior. |
| cost | Fixed scalar/reference initialization plus default empty containers; no search, allocation of graph contents or runtime update work begins here. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0036

[Lines 338–347](../../../../../src/planner/meta_candidates.cpp#L338); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L338-L347:sha256:4a172332446cdbf1a1254d8cb18f7322dc99599323739d3d87c342f42e9f64b2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Process each returned undirected ordinary tree once while retaining complete CROWN rooting coverage in its inverse fiber. |
| inputs / outputs | run first builds native scopes, then reads the ordinary JoinTree vector; after basic root/parent checks it maps only records with physical root zero. |
| invariants | Canonical enumeration supplies exactly those root-0 records; all_roots=true additionally supplies orientations deliberately skipped here. graph independently checks each mapped record, and root_sets covers every eligible CROWN first-native root set regardless of the ordinary record's root. |
| ownership | The input vector remains borrowed and unchanged; Mapper owns scopes/adjacency/orientations and appends owned drafts to outer output. |
| failure | Malformed basic shape rejects even a skipped orientation; mapped topology/RIP failures stop as invalid_join_tree. Budget and allocation failures preserve only earlier complete output drafts. |
| cost | One scope extraction, one selected checkpoint per returned rooted record, then full graph and inverse-fiber work only for root-0 records. Explicit all-root mode pays additional upstream storage and skipped-record checks. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [include/crown/planner/meta_join_trees.hpp](../../../../../include/crown/planner/meta_join_trees.hpp), [exact paper reference](https://arxiv.org/pdf/2301.04003v2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm5) |

## B0037

[Lines 348–350](../../../../../src/planner/meta_candidates.cpp#L348); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L348-L350:sha256:541ca4662199bffe3f912de13f8b1ab771d4a11eda1505f186633d834b6af8a4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the private mapper type and anonymous helper namespace before the public API definition. |
| inputs / outputs | These closing braces end member/helper definition scope; the next function remains in crown::planner::meta. |
| invariants | Only declared API functions are externally callable. Closing a class/namespace does not itself finalize a runtime Mapper instance or validate its output. |
| ownership | No live object is created or destroyed by these lexical closures; actual automatic-object lifetimes end at their call scopes. |
| failure | This structural region has no executable failure, stop conversion or cleanup operation. |
| cost | No runtime instruction cost; helper object destruction remains charged separately at actual call exits. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |

## B0038

[Lines 351–374](../../../../../src/planner/meta_candidates.cpp#L351); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L351-L374:sha256:f4188d6ec6f338b32324ece868ec6835246a0919b03acc5c63a7c54b1eeff90b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare a bounded paper-derived ordinary family and local normalized inverse fibers, then transfer only completed raw drafts into the existing finite proposal admission route. |
| inputs / outputs | The public call consumes a real VerifiedOptimum and stage limits, obtains its exact binding/height, constructs metadata, independently enumerates ordinary trees, maps them and optionally returns a CandidateProvider with diagnostics. |
| invariants | Invalid proof is rejected before binding access. Noncomplete construction returns no provider. Ordinary stop/mode/usage and actual rooted count are copied independently; ordinary_exhausted requires complete. Successful mapping, including an empty returned ordinary prefix, attests only those supplied fibers. The provider is finite-proposals-v1 with the unchanged original proof and no seed/fallback; P02, equal-height, full-key dedup and publication happen only when advanced. |
| ownership | Binding retains exact source ownership during the call. Built metadata, ordinary records and mapper scratch are local; drafts and the proof move into the returned provider. The public report/provider pair remains mutable, so combined exhaustion assumes callers preserve that pair. |
| failure | Only private Halt is translated into mapping_stop, preserving complete raw drafts; other exceptions, including OOM/admission, propagate. Preparation cannot resume after a cap. A later provider can resume its own existing admission continuation; finite-batch exhaustion alone does not repair upstream incompleteness. |
| cost | Cold construction, independent metadata check, ordinary enumeration, mapping and provider input admission have separate work/storage costs and limits. Canonical mode avoids redundant rooted storage; no candidate advance, row processing or per-update hook occurs here. Destruction, allocator bytes and total CPU are not bounded by mapping counters. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md), [docs/meta_decompositions.md](../../../../meta_decompositions.md), [exact paper reference](https://arxiv.org/pdf/2301.04003v2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm2), [exact paper reference](https://arxiv.org/html/2603.15465v2#algorithm5), [include/crown/planner/meta_join_trees.hpp](../../../../../include/crown/planner/meta_join_trees.hpp), [include/crown/planner/candidates.hpp](../../../../../include/crown/planner/candidates.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp) |

## B0039

[Lines 375–375](../../../../../src/planner/meta_candidates.cpp#L375); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L375-L375:sha256:64c12aa1b75937a9f02928dc49559700cb3ed0d85658387b856ef97ff0af1a2f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the public meta namespace after the preparation entry point. |
| inputs / outputs | This lexical brace ends crown::planner::meta definitions for this translation unit. |
| invariants | The closure changes name lookup scope only; it does not mark a report, fiber or provider exhausted. |
| ownership | No source binding, scratch graph or candidate owner is created, transferred or destroyed by this namespace closure. |
| failure | There is no executable error handling, stop conversion or exception swallowing in this region. |
| cost | No runtime instruction or per-update cost is introduced by the closing namespace brace. |
| Design | [docs/meta_candidate_adapter.md](../../../../meta_candidate_adapter.md) |
