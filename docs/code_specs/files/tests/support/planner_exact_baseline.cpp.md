# `tests/support/planner_exact_baseline.cpp` — block usage map

[Source](../../../../../tests/support/planner_exact_baseline.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `e859c3150a484b546913a6da50fd8cd47a932bed22bd467b59da20a24755cf70`. 357 lines partitioned into 25 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../tests/support/planner_exact_baseline.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. | growth new · [reviewed contract](#b0001) |
| [B0002 · 17–22](../../../../../tests/support/planner_exact_baseline.cpp#L17) | Type/record definition: struct Key |  · [reviewed contract](#b0002) |
| [B0003 · 23–23](../../../../../tests/support/planner_exact_baseline.cpp#L23) | Explanatory comments or spacing. |  |
| [B0004 · 24–28](../../../../../tests/support/planner_exact_baseline.cpp#L24) | Type/record definition: struct Metadata |  · [reviewed contract](#b0004) |
| [B0005 · 29–29](../../../../../tests/support/planner_exact_baseline.cpp#L29) | Explanatory comments or spacing. |  |
| [B0006 · 30–36](../../../../../tests/support/planner_exact_baseline.cpp#L30) | Type/record definition: struct Choice |  · [reviewed contract](#b0006) |
| [B0007 · 37–41](../../../../../tests/support/planner_exact_baseline.cpp#L37) | declares types or opens a type body. | source comment (unverified): // Frozen pre-P06 labelled-state recurrence: every native root and unordered · [reviewed contract](#b0007) |
| [B0008 · 42–63](../../../../../tests/support/planner_exact_baseline.cpp#L42) | Callable definition: public: PartitionSearch(const Query& query, baseline_detail::WorkBudget& budget) : budget_(budget) | calls budget_, charge, insert, push_back; growth insert, push_back; 4 loop sites · [reviewed contract](#b0008) |
| [B0009 · 64–65](../../../../../tests/support/planner_exact_baseline.cpp#L64) | Explanatory comments or spacing. | source comment (unverified): // Borrowed map value stays stable under insertions and ends with this search. · [reviewed contract](#b0009) |
| [B0010 · 66–142](../../../../../tests/support/planner_exact_baseline.cpp#L66) | Callable definition: const Choice& solve(const Key& key) | calls frame, find, end, metadata; returns cached-&gt;second; choices_.emplace(key, std::move(best)).first-&gt;second; growth emplace, insert, push_back; 8 loop sites; source comment (unverified): // Borrowed map value stays stable under insertions and ends with this search. · [reviewed contract](#b0010) |
| [B0011 · 143–143](../../../../../tests/support/planner_exact_baseline.cpp#L143) | Explanatory comments or spacing. |  |
| [B0012 · 144–164](../../../../../tests/support/planner_exact_baseline.cpp#L144) | Callable definition: FreeConnexTree build(const Key& root) | calls NodeId, frame, at, charge; returns id; tree; growth push_back; 2 loop sites · [reviewed contract](#b0012) |
| [B0013 · 165–165](../../../../../tests/support/planner_exact_baseline.cpp#L165) | Explanatory comments or spacing. |  |
| [B0014 · 166–186](../../../../../tests/support/planner_exact_baseline.cpp#L166) | Callable definition: std::vector&lt;LowerBoundEntry&gt; proof() | calls charge, emplace, Error, push_back; returns entries; growth emplace, push_back; 3 loop sites; source comment (unverified): // Identity keys retain the complete v1 state set and its map order. There · [reviewed contract](#b0014) |
| [B0015 · 187–187](../../../../../tests/support/planner_exact_baseline.cpp#L187) | Explanatory comments or spacing. |  |
| [B0016 · 188–195](../../../../../tests/support/planner_exact_baseline.cpp#L188) | Callable definition: private: bool contains_all(const VariableSet& scope, const VariableSet& required) | calls charge, contains; returns false; true; 1 loop sites · [reviewed contract](#b0016) |
| [B0017 · 196–196](../../../../../tests/support/planner_exact_baseline.cpp#L196) | Explanatory comments or spacing. |  |
| [B0018 · 197–219](../../../../../tests/support/planner_exact_baseline.cpp#L197) | Callable definition: const Metadata& metadata(const Members& members) | calls charge, find, end, insert; returns found-&gt;second; metadata_.emplace(members, std::move(value)).first-&gt;second; growth emplace, insert; 3 loop sites · [reviewed contract](#b0018) |
| [B0019 · 220–220](../../../../../tests/support/planner_exact_baseline.cpp#L220) | Explanatory comments or spacing. |  |
| [B0020 · 221–243](../../../../../tests/support/planner_exact_baseline.cpp#L221) | Callable definition: void partitions(const Members& members, const std::function&lt;bool(const std::vector&lt;Members&gt;&)&gt;& accept) | calls bool, frame, size, accept; returns accept(blocks); true; growth push_back; 1 loop sites · [reviewed contract](#b0020) |
| [B0021 · 244–253](../../../../../tests/support/planner_exact_baseline.cpp#L244) | Member/declaration region. | source comment (unverified): // Actual caller keeps one uncopied search; budget is borrowed, containers own data. · [reviewed contract](#b0021) |
| [B0022 · 254–346](../../../../../tests/support/planner_exact_baseline.cpp#L254) | Callable definition: OracleResult run_baseline(const Catalog& catalog, const Query& query, const SearchLimits& limits) | calls validate, budget, charge, empty; returns result; 6 loop sites; source comment (unverified): // Preserve v1 payload accounting and the strict, independent public replay. · [reviewed contract](#b0022) |
| [B0023 · 347–350](../../../../../tests/support/planner_exact_baseline.cpp#L347) | controls preprocessing; declares namespace scope. | source comment (unverified): // namespace · [reviewed contract](#b0023) |
| [B0024 · 351–354](../../../../../tests/support/planner_exact_baseline.cpp#L351) | Callable definition: OracleResult minimum_tree_baseline(const Catalog& catalog, const Query& query, const SearchLimits& limits) | calls run_baseline; returns run_baseline(catalog, query, limits) · [reviewed contract](#b0024) |
| [B0025 · 355–357](../../../../../tests/support/planner_exact_baseline.cpp#L355) | controls preprocessing. | source comment (unverified): // namespace testing · [reviewed contract](#b0025) |

## B0001

[Lines 1–16](../../../../../tests/support/planner_exact_baseline.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
using Members =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent one frozen labelled occurrence subset in deterministic order. |
| inputs / outputs | Vector&lt;size_t&gt; contains original query atom indices and becomes part of map/proof identity. |
| invariants | No scope-orbit canonicalization or occurrence relabelling; callers construct unique valid occurrence indices. |
| ownership | Ordinary owning vector; key/proof copies duplicate index storage. |
| failure | Allocation failures propagate; alias supplies no validation. |
| cost | O(member count) copy/lexicographic compare as used in maps. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 17–22](../../../../../tests/support/planner_exact_baseline.cpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Key
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Identify a labelled subproblem and its root/reachability restrictions. |
| inputs / outputs | members plus generalized/reachable flags; default spaceship compares vector then flags. |
| invariants | Different flags and occurrence identities remain separate states, even when scopes are isomorphic. |
| ownership | Owns Members vector; copies deep-copy vector and scalar flags. |
| failure | Editable test state; ordinary container allocation/copy failures propagate; no native admission. |
| cost | O(member count) key copy/compare. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 24–28](../../../../../tests/support/planner_exact_baseline.cpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Metadata
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain per-subproblem variable unions and interface/head restrictions. |
| inputs / outputs | variables is union, boundary appears outside subset, private_head is head variable wholly inside subset. |
| invariants | Computed from occurrence incidence, not row data or native execution. |
| ownership | Owns three ordered VariableSets; copies allocate their nodes. |
| failure | Editable test state; ordinary container allocation/copy failures propagate; no native admission. |
| cost | Storage/copy proportional to subset variables. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 30–36](../../../../../tests/support/planner_exact_baseline.cpp#L30); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Choice
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own an optional minimum-height solution and selected upper-tree recurrence. |
| inputs / outputs | Absent height means infeasible; present stores kind, optional occurrence, scope and ordered child Keys. |
| invariants | Strictly lower candidate replaces best; first equal-height witness remains. Generalized contributes zero native height. |
| ownership | Owns variable set/vector/deep child keys; not a typed VerifiedOptimum capability. |
| failure | Editable test state; ordinary container allocation/copy failures propagate; no native admission. |
| cost | Copy/move cost follows owned scopes and child member vectors. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 37–41](../../../../../tests/support/planner_exact_baseline.cpp#L37); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class PartitionSearch
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the frozen pre-P06 labelled exhaustive partition recurrence as a comparison baseline. |
| inputs / outputs | Borrows WorkBudget, owns per-occurrence scopes/head/incidence and memo maps; solve/build/proof produce editable candidate evidence. |
| invariants | No optimized component split/symmetry/incumbent/hierarchy shortcut. Height1 early stop uses the universal nonempty lower bound. Actual certificate replay is still mandatory before reporting exactness. |
| ownership | Implicit copy would deep-copy containers while retaining the same budget reference; actual caller creates one uncopied lexical search. Returned map-value references borrow this search. |
| failure | Work/depth/time stop or ordinary allocation propagates to run_baseline narrow handlers; invalid witness/certificate errors intentionally escape. |
| cost | Bell-number partition enumeration plus recursive memo/search/map work and owned proof/tree copies; charged work is an explicit model, not total CPU/allocations. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 42–63](../../../../../tests/support/planner_exact_baseline.cpp#L42); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
PartitionSearch(const Query&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build labelled atom scopes, global incidence and head-variable set. |
| inputs / outputs | For each atom collects VariableId terms, charges visits, increments incidence once per atom-scope variable and records output variables. |
| invariants | Catalog/Query validation happens at run_baseline before construction. Constants/Ignored do not add variables; duplicate terms collapse in VariableSet. |
| ownership | Borrows budget for lifetime; owns deep ordinary scopes/head/maps, not Query references. |
| failure | Charge/Frame stop, map/vector allocation or copy failure unwinds construction. |
| cost | Visits all terms/distinct atom variables/head outputs with charges plus real set/map insertion and allocations. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 64–65](../../../../../tests/support/planner_exact_baseline.cpp#L64); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L64-L65:sha256:1e299495061b7167f87f1006f2d21c641b0903bd1442d126c2c366a050ef6989
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Borrowed map value stays stable under insertions and ends with this search. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 66–142](../../../../../tests/support/planner_exact_baseline.cpp#L66); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Choice& solve(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Memoize minimum native height over every allowed labelled root/sibling partition. |
| inputs / outputs | Charges a frame even on cache hits; rejects unreachable private head; considers native roots and allowed generalized shared guards; caches complete best Choice. |
| invariants | Children recurse on proper blocks; root guard covers boundary. Infeasible state has absent height; completed memo references stay stable under map insertions, only while search lives. |
| ownership | Returns const borrow into choices_; local candidate vectors/scopes are owned and moved into memo. |
| failure | Stop/allocation can unwind before complete state insertion; no partial result gains certificate authority. |
| cost | Potential exponential/Bell search with map key/scopes copies and recursion; per-charge units exclude comparison/allocator/whole CPU costs. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

```text
const auto consider =
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Combine feasible child subproblem heights into one local best candidate. |
| inputs / outputs | Charges candidate; child reachable requires parent reachable and boundary contained in head; increments max-child height only for native root; replaces on strict improvement. |
| invariants | An infeasible child abandons candidate; generalized permission for children depends on this candidate kind. |
| ownership | Synchronous lambda borrows key/meta/search/best; child Keys own vectors; no callable retained. |
| failure | Charge stops, invalid internal lookups and ordinary allocation errors propagate to the enclosing search boundary. |
| cost | One recursive solve per child plus map/set membership, vector copies and fixed max/height arithmetic. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

```text
for (const auto root : key.members)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate every labelled native root and sibling partition. |
| inputs / outputs | Requires root scope covers boundary; partitions remaining occurrences, checks every child boundary subset root scope, then considers native candidate. |
| invariants | Only exact height1 may short-circuit this nonempty recurrence; no heuristic upper bound is reported minimum. |
| ownership | Remaining Members and partition blocks are private ordinary owners. |
| failure | Charge stops, invalid internal lookups and ordinary allocation errors propagate to the enclosing search boundary. |
| cost | Every possible native root and unordered partition until exact height1; substantial recursive/owned copy cost. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

```text
if (key.generalized)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate generalized roots using shared block-variable guards. |
| inputs / outputs | For partitions with&gt;=2 blocks counts cross-block incidence, collects shared variables, covers boundary and requires guard contained in every block before considering candidate. |
| invariants | Generalized root adds zero native depth but cannot invent arbitrary guard variables; no symmetry merging. |
| ownership | Incidence/shared/private blocks own ordinary values, callback borrows during enumeration. |
| failure | Charge stops, invalid internal lookups and ordinary allocation errors propagate to the enclosing search boundary. |
| cost | All unordered partitions and repeated metadata/set/map scans; exponential search despite explicit work charges. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 144–164](../../../../../tests/support/planner_exact_baseline.cpp#L144); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
FreeConnexTree build(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Materialize the selected upper witness after solve completed. |
| inputs / outputs | Recursive append finds cached Choice, charges frame/scope visits, appends nodeN with kind/scope/occurrence and child IDs, returns root. |
| invariants | Only feasible selected Choices are used; resulting editable raw tree must still pass validate_tree and independent certificate replay. |
| ownership | Returns owning tree; scope/label/child arrays copied into it. Lambda borrows search/tree only during build. |
| failure | Absent memo/precondition, stop or ordinary allocation throws; partial private tree unwinds. |
| cost | O(selected nodes/scopes/edges) explicit visits plus host recursive frames, std::function/string/tree allocations. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

```text
std::function<NodeId(const Key&)> append
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recursively append one selected witness subtree. |
| inputs / outputs | Uses stable Choice borrow, obtains new dense NodeId, appends child subtrees then writes child IDs via index. |
| invariants | Reacquires tree.nodes\[id\] after recursion, avoiding retained references across vector reallocation; IDs follow append order. |
| ownership | Lambda borrows tree/search/budget; returned IDs are scalars, no owner lifetime extension. |
| failure | Frame/charge/allocation or missing choice failure aborts private tree build. |
| cost | Recursive traversal with ordinary string/scope/vector copies and actual host-stack depth. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0014

[Lines 166–186](../../../../../tests/support/planner_exact_baseline.cpp#L166); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
std::vector<LowerBoundEntry> proof()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Export the full frozen v1 labelled memo state set as replay evidence. |
| inputs / outputs | Copies choices keys/heights to ordered proof_states, checks duplicate consistency, then emits original member/flags/height entries with charges. |
| invariants | No v2 scope orbit/transport; proof DTO alone does not establish optimality. Ordered map identity preserves exercised v1 state set. |
| ownership | Returned entries own copied occurrence vectors; intermediate map duplicates owned keys. |
| failure | Work/allocation failures propagate; inconsistent duplicate height throws invalid_search_proof. |
| cost | Full memo traversal, map duplication/comparison and all occurrence-vector copies plus explicit charges. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0016

[Lines 188–195](../../../../../tests/support/planner_exact_baseline.cpp#L188); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool contains_all(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check ordered-set containment with baseline visit charges. |
| inputs / outputs | Charges each required variable and returns false at first missing member. |
| invariants | Empty required set is contained; no allocation or graph/source validation is added by the membership operation itself. |
| ownership | Borrows both sets synchronously; returns scalar only. |
| failure | Charge may stop before completion and allocate its stop diagnostic; set lookups use valid IDs. |
| cost | O(required*log scope) set membership and one model charge per inspected variable. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 197–219](../../../../../tests/support/planner_exact_baseline.cpp#L197); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
const Metadata& metadata(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Memoize the variable interface for a labelled member subset. |
| inputs / outputs | Charges/cache-checks; counts variable occurrences inside, union variables, boundary if count&lt;global total, otherwise private head if projected. |
| invariants | Members must be unique valid query atom indices. Map insertion preserves references; returned Metadata borrows search lifetime. |
| ownership | Owns map key/value containers; return is const borrowed reference, not an independent copy. |
| failure | Charge, map at/invalid caller input or ordinary allocation failures propagate; unfinished private metadata is not cached. |
| cost | Scan all subset scopes plus incidence/map/set operations, copied member vector and variable sets. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0020

[Lines 221–243](../../../../../tests/support/planner_exact_baseline.cpp#L221); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void partitions(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate unordered set partitions without permuting block labels. |
| inputs / outputs | Restricted-growth recursion appends each next member to every existing block then one new block; callback true terminates traversal. |
| invariants | Input member order determines deterministic enumeration; callback borrows current blocks only. Empty input invokes callback once with empty blocks. |
| ownership | Private blocks and std::function own local storage; callbacks are synchronous and never retained. |
| failure | On callback/charge/allocation exception local push/pop state need not be restored because entire enumeration unwinds; no source/native mutation. |
| cost | Bell-number partition count, recursive host frames/depth charges and vector/std::function allocations; not bounded by result count alone. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

```text
std::function<bool(std::size_t)> next
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Advance one restricted-growth partition prefix. |
| inputs / outputs | Charges Frame; at end increments partitions and calls accept; explores existing blocks then a new singleton, popping on normal return. |
| invariants | existing count is captured before branch growth; no duplicate block-order permutations. Early true propagates immediately. |
| ownership | Lambda borrows members,blocks,accept,budget only during partitions; no external borrow survives. |
| failure | Exceptions unwind whole private traversal rather than completing pop restoration. |
| cost | Depth proportional to member count, exponential branches and vector growth; exact budget charges are distinct from all CPU. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0021

[Lines 244–253](../../../../../tests/support/planner_exact_baseline.cpp#L244); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
baseline_detail::WorkBudget& budget_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow one finite baseline search budget across scopes/solves/tree/proof. |
| inputs / outputs | Reference binds caller-local WorkBudget until search destruction. |
| invariants | Copying search would share budget reference while copying containers; actual run uses uncopied search. |
| ownership | budget_ alone borrows; all container members own ordinary data with deep-copy semantics and no native query account. |
| failure | Members have no individual catch; container growth and budget stops propagate to run_baseline. |
| cost | Fixed reference storage; charges/clock checks are real budget helper operations. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

```text
std::vector<VariableSet> scopes_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own per-occurrence variable scopes in original atom order. |
| inputs / outputs | Vector index is labelled query occurrence number; scope contains variable terms only. |
| invariants | Scope order/IDs derive from validated Query; no physical table deduplication. |
| ownership | budget_ alone borrows; all container members own ordinary data with deep-copy semantics and no native query account. |
| failure | Members have no individual catch; container growth and budget stops propagate to run_baseline. |
| cost | O(total atom-variable incidences) ordered-set storage and deep copies. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

```text
VariableSet head_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain projected variables independent of alias/repetition. |
| inputs / outputs | Set includes every query output variable once. |
| invariants | Private-head feasibility uses set membership, while full Query validation handles original output semantics. |
| ownership | budget_ alone borrows; all container members own ordinary data with deep-copy semantics and no native query account. |
| failure | Members have no individual catch; container growth and budget stops propagate to run_baseline. |
| cost | O(distinct head variables) set storage. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

```text
std::map<VariableId, std::size_t> total_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain whole-query atom incidence for boundary classification. |
| inputs / outputs | Counts each variable once per atom scope. |
| invariants | Inside-subset count below total marks external boundary. |
| ownership | budget_ alone borrows; all container members own ordinary data with deep-copy semantics and no native query account. |
| failure | Members have no individual catch; container growth and budget stops propagate to run_baseline. |
| cost | Ordered map storage and O(log variables) accesses. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

```text
std::map<Members, Metadata> metadata_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Memoize interface metadata by exact labelled subset. |
| inputs / outputs | Members vector keys own occurrence indices and Metadata owns three sets. |
| invariants | Entries are stable until search destruction and are not public proof authority. |
| ownership | budget_ alone borrows; all container members own ordinary data with deep-copy semantics and no native query account. |
| failure | Members have no individual catch; container growth and budget stops propagate to run_baseline. |
| cost | Deep key/set ownership and ordered-map lookup/copy costs. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

```text
std::map<Key, Choice> choices_;
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own completed recurrence choices and stable borrowed solve results. |
| inputs / outputs | Caches exact members/generalized/reachable keys to owning Choice. |
| invariants | Only complete best/infeasible choices are inserted; no heuristic unfinished minimum exposed. |
| ownership | budget_ alone borrows; all container members own ordinary data with deep-copy semantics and no native query account. |
| failure | Members have no individual catch; container growth and budget stops propagate to run_baseline. |
| cost | Potential exponential state retention plus deep key/scope/children allocation. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0022

[Lines 254–346](../../../../../tests/support/planner_exact_baseline.cpp#L254); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
OracleResult run_baseline(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run frozen search and strict independent certificate replay before reporting a minimum/unsupported result. |
| inputs / outputs | Validates source and constructs budget before try; builds/validates witness, exports proof, precharges payload visits, copies HeightCertificate and calls verify_height_certificate with limits. |
| invariants | Only successful public replay sets certificate_verified and exact status. OracleResult remains editable descriptive evidence, not VerifiedOptimum capability. Replay has separate finite work accounting. |
| ownership | Owns result/source copies/tree/proof and local budget/search; returned containers own independent data. |
| failure | SearchStopped and bad_alloc map in-try failures to resource_limit with exactness cleared; invalid source/negative-limit construction occurs outside try, invalid witness/certificate errors propagate. Diagnostic assignment can allocate under persistent new denial. |
| cost | Exponential baseline plus proof/tree copies and full independent replay; work/certificate_work are explicit models, not whole-operation CPU or allocations. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

```text
validate(catalog, query);
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate source and initialize finite budget before recoverable search phase. |
| inputs / outputs | Catalog/Query validation and WorkBudget(limits) precede result construction/try. |
| invariants | Invalid input/negative time is not silently reclassified as exhausted valid search. |
| ownership | Only local ordinary evidence/budget is owned; no native source/runtime owner is mutated. |
| failure | These pre-try errors/allocation failures propagate directly. |
| cost | Complete source validation plus budget clock/limit setup. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

```text
const Key root{members, true, true};
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Solve every labelled atom from a generalized-allowed reachable root. |
| inputs / outputs | Members0..n-1, solve, copy optional min, build feasible tree, export proof then validate selected upper witness. |
| invariants | Positive exactness is not published here; replay remains required. |
| ownership | Only local ordinary evidence/budget is owned; no native source/runtime owner is mutated. |
| failure | Search/validation/ordinary allocation errors propagate to appropriate outer boundary. |
| cost | Full search, proof export, tree build and tree verification. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

```text
const HeightCertificate certificate
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Recheck frozen result through the independent public height-certificate verifier. |
| inputs / outputs | Copies algorithm/min/tree/lower bounds, invokes verify_height_certificate, records separate work, rejects resource/invalid results. |
| invariants | Editable v1 payload gets exact status only after complete verifier success; replay cannot borrow search memo as proof truth. |
| ownership | Only local ordinary evidence/budget is owned; no native source/runtime owner is mutated. |
| failure | Replay resource stops become SearchStopped; invalid certificate throws public Error; certificate copy/allocation may fail. |
| cost | Deep payload copy plus actual verifier recurrence/upper validation with its own finite limit. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

```text
} catch (const baseline_detail::SearchStopped& stopped)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Translate expected finite-search/replay exhaustion without claiming a minimum. |
| inputs / outputs | Sets resource_limit/reason, clears min/tree/proof, certificate_verified=false; preserves separately recorded replay work. |
| invariants | No accepted partial minimum or unsupported claim escapes; container clear may retain capacity. |
| ownership | Only local ordinary evidence/budget is owned; no native source/runtime owner is mutated. |
| failure | Message assignment can allocate and propagate; this is not a noexcept total OOM response. |
| cost | Private payload destruction/clear, statistics copy and ordinary diagnostic copy. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

```text
} catch (const std::bad_alloc&)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return a non-exact resource result for allocation failure within the search try. |
| inputs / outputs | Clears optional tree/min, releases proof via empty-vector swap, clears verified flag, copies statistics and assigns reason. |
| invariants | The reason assignment may still allocate under persistent denial; handler does not promise all-allocation-failures recovery. |
| ownership | Only local ordinary evidence/budget is owned; no native source/runtime owner is mutated. |
| failure | Any exception thrown by the handler itself propagates; no retry/rebuild or generic recovery layer. |
| cost | Cleanup/destruction of accumulated private state and ordinary diagnostic construction. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0023

[Lines 347–350](../../../../../tests/support/planner_exact_baseline.cpp#L347); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L347-L350:sha256:942cd0ba6f393fbaa2f0e845b3091cfb715e303937b1b40a54475ea1b7763d2d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare planner_exact_baseline.cpp: select the recorded test ABI/preprocessor branch. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |

## B0024

[Lines 351–354](../../../../../tests/support/planner_exact_baseline.cpp#L351); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
OracleResult minimum_tree_baseline(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose the frozen recurrence only in the planner testing build. |
| inputs / outputs | CROWN_PLANNER_TESTING wrapper forwards catalog,query,limits to run_baseline. |
| invariants | Declared by testing probe; not a production planner admission API or a proof capability constructor. |
| ownership | Inputs borrow for the call; return owns editable OracleResult payload. |
| failure | Exactly run_baseline failure classification/propagation, no additional catch. |
| cost | One forwarding call plus actual baseline/search/replay costs. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [tests/support/planner_baseline_budget.hpp](../../../../../tests/support/planner_baseline_budget.hpp), [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [tests/unit/planner_continuation_test.cpp](../../../../../tests/unit/planner_continuation_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0025

[Lines 355–357](../../../../../tests/support/planner_exact_baseline.cpp#L355); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L355-L357:sha256:1d46ba7151ddaa8dccd38da3ab117cdd31cdad6d5323d1ddfdafcc3f658db6d3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare planner_exact_baseline.cpp: declare the recorded helper API/type boundary. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/planner_exact_baseline.cpp](../../../../../tests/support/planner_exact_baseline.cpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |
