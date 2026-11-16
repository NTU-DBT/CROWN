# `tests/reference/tree_oracle.cpp` — block usage map

[Source](../../../../../tests/reference/tree_oracle.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `12549342b96d2cc114681ea9c5426085f8ce7d6b17e5ad4f2df6420967abbfd5`. 132 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../tests/reference/tree_oracle.cpp#L1) | Imports dependencies; declares namespace scope. | growth new · [reviewed contract](#b0001) |
| [B0002 · 12–131](../../../../../tests/reference/tree_oracle.cpp#L12) | Callable definition: planner::OracleResult exhaustive_minimum_tree(const Catalog& catalog, const Query& query, const planner::SearchLimits& limits) | calls validate, budget, size, charge; returns *universe; topology(position + 1); growth emplace, insert, push_back; 13 loop sites · [reviewed contract](#b0002) |
| [B0003 · 132–132](../../../../../tests/reference/tree_oracle.cpp#L132) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::reference · [reviewed contract](#b0003) |

## B0001

[Lines 1–11](../../../../../tests/reference/tree_oracle.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:bbe28270dca445ee63a982d3bf662c4995f3c2403f063bfc0f2a6d6747655183
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare tree_oracle.cpp: include "tree_oracle.hpp", "crown/api/error.hpp", "crown/planner/verify.hpp", "../../src/planner/search_budget.hpp", &lt;algorithm&gt;, &lt;functional&gt;, &lt;numeric&gt;, &lt;new&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 12–131](../../../../../tests/reference/tree_oracle.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::OracleResult exhaustive_minimum_tree(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate the literal complete normal-form tree family as a separate structural-search reference. |
| inputs / outputs | Validates catalog/query, copies native occurrence scopes, searches increasing native height,0…m−1 generalized nodes, all root/parent choices and generalized labels from the union of native power sets; shared P02 validates each surviving candidate. |
| invariants | Empty body returns height0; a contradiction flag does not erase a nonempty structural body. Completed enumeration reports minimum or unsupported; a stopped search clears tree/height and never proves infeasibility. This literal algorithm returns a DTO, not an installed program or public certificate capability. |
| ownership | Owns ordinary scope/topology/label/tree containers and recursive function objects. WorkBudget owns counters/active-frame limits; its stopped result does not fund a receiving native runtime. |
| failure | SearchStopped and in-try bad_alloc translate to resource_limit with no witness. Initial validation/result setup and allocating diagnostic assignment may still throw; no global noexcept/OOM-status guarantee is made. |
| cost | Potentially exponential scope materialization and much larger labelled topology/label enumeration, under declared checkpoint/frame/scope caps. Shared validator/copy/scalar/allocator costs remain real; no optimized P2 or runtime-delay bound is imported. |
| Design | [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md §Complete normal-form family (P03)](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [src/planner/search_budget.hpp](../../../../../src/planner/search_budget.hpp) |

## B0003

[Lines 132–132](../../../../../tests/reference/tree_oracle.cpp#L132); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L132-L132:sha256:e6b42e4915271f267594118fd022698431af47758d71d1b08d7db51a0d7f1921
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in tree_oracle.cpp: namespace crown::reference. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |
