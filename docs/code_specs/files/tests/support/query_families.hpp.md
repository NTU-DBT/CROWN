# `tests/support/query_families.hpp` — block usage map

[Source](../../../../../tests/support/query_families.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `16cdd08ea19833d88e4431eaf5215a16a90cd9ad2773200207332404d4bf3494`. 62 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../tests/support/query_families.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 8–14](../../../../../tests/support/query_families.hpp#L8) | Type/record definition: struct Fixture | source comment (unverified): // Test expectation only, never an input to QueryExplanation authority. · [reviewed contract](#b0002) |
| [B0003 · 15–16](../../../../../tests/support/query_families.hpp#L15) | Explanatory comments or spacing. | source comment (unverified): // Trusted small masks use only x0..x2 and head subset-of-union; this builds DTOs, · [reviewed contract](#b0003) |
| [B0004 · 17–31](../../../../../tests/support/query_families.hpp#L17) | Callable definition: inline Fixture hypergraph(std::vector&lt;unsigned&gt; scopes,unsigned head_mask,std::string name, std::optional&lt;bool&gt; expected={}) | calls std::move, size, push_back, std::to_string; returns f; growth emplace_back, push_back; 5 loop sites; source comment (unverified): // Trusted small masks use only x0..x2 and head subset-of-union; this builds DTOs, · [reviewed contract](#b0004) |
| [B0005 · 32–47](../../../../../tests/support/query_families.hpp#L32) | Callable definition: inline std::vector&lt;Fixture&gt; anchors() | calls push_back, hypergraph, std::move, emplace_back; returns out; growth emplace_back, push_back · [reviewed contract](#b0005) |
| [B0006 · 48–50](../../../../../tests/support/query_families.hpp#L48) | Explanatory comments or spacing. | source comment (unverified): // Finite family: 1..3 distinct nonempty scopes from subsets of {x0,x1,x2}, · [reviewed contract](#b0006) |
| [B0007 · 51–61](../../../../../tests/support/query_families.hpp#L51) | Callable definition: inline std::vector&lt;Fixture&gt; finite_three_variable_family() | calls std::popcount, push_back, hypergraph, std::to_string; returns out; growth push_back; 3 loop sites; source comment (unverified): // Finite family: 1..3 distinct nonempty scopes from subsets of {x0,x1,x2}, · [reviewed contract](#b0007) |
| [B0008 · 62–62](../../../../../tests/support/query_families.hpp#L62) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::query_explain_fixture · [reviewed contract](#b0008) |

## B0001

[Lines 1–7](../../../../../tests/support/query_families.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:763036923a72ff8709d0872411b79b8a20825518d1e0740bd0a7044da42de9f2
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare query_families.hpp: include "crown/ir/model.hpp", &lt;array&gt;, &lt;bit&gt;, &lt;optional&gt;, &lt;utility&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–14](../../../../../tests/support/query_families.hpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a named ordinary query input and optional independent test expectation. |
| inputs / outputs | name/catalog/query are editable owning DTOs; expected_admissible is optional bool asserted only against independent literal oracle output by the caller. |
| invariants | Expectation is never input to QueryExplanation/proof authority. No explicit special members: copies deep-copy nested strings/vectors/catalog/query; moves transfer ordinary payload ownership rather than typed proof state. |
| ownership | Owns independent ordinary metadata, no runtime/query account/proof handle or live producer. |
| failure | Construction/copy allocation failure propagates; no fallback expectation or admitted flag. |
| cost | Metadata/text/container copying costs scale with fixture payload; no generic shared/no-allocation fixture copy. |
| Design | [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0003

[Lines 15–16](../../../../../tests/support/query_families.hpp#L15); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L16:sha256:eeccd9f8296eadf56095b1852fd4f103a945279889c88cf2fd71e64e9400e79a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Trusted small masks use only x0..x2 and head subset-of-union; this builds DTOs, while the separate public search/replay and literal oracle establish outcomes. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 17–31](../../../../../tests/support/query_families.hpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline Fixture hypergraph(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a small literal catalog/query from three-bit atom/head scopes. |
| inputs / outputs | Maps used x0..x2 bits to dense VariableIds, creates one Table/Atom per supplied scope (including nullary0), typed int64 columns/terms and ordered head outputs; moves name and stores optional expectation. |
| invariants | Trusted callers supply only low three bits and a head subset of used variables; helper does not validate those preconditions, and higher bits are ignored. It does not run source admission, recognition or tree proof. |
| ownership | Returns owning ordinary names/vectors/catalog/query. Input scopes is by value; no caller vector or path is retained. |
| failure | Ordinary allocation failures propagate; malformed arbitrary masks are outside internal fixture precondition, no defensive normalization added. |
| cost | Loops three possible variables per atom/head plus vector/string growth and input vector copy if passed lvalue; not a native account operation. |
| Design | [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 32–47](../../../../../tests/support/query_families.hpp#L32); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::vector<Fixture> anchors()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create eleven explicit structural, constant-route and byte-transport anchor queries. |
| inputs / outputs | Includes empty/nullary/unary/projected single atom, full path, non-free-connex endpoint projection, disconnected product, triangle, contradiction-marked triangle, empty-body contradiction and raw0xff string constant. |
| invariants | Known bool expectations describe structural oracle outcome; contradiction does not erase a structurally negative body. Empty contradiction intentionally has no fixed expected flag here. Native binary scalar bytes are valid inputs and may later be rejected only by text transport. |
| ownership | Vector owns independent ordinary Fixture/source/scalar bytes; no proof is manufactured by labels or optional flags. |
| failure | Metadata/string/vector construction failure propagates; actual oracle/search/export rejection is checked by test caller. |
| cost | Fixed eleven fixture builds with real deep DTO/container/string allocations; no search/runtime execution inside anchors. |
| Design | [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 48–50](../../../../../tests/support/query_families.hpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L50:sha256:2399f3da802fc4d67bcfa35d17d12669e86194cc2d3f82de9b7e12358864e4a8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Finite family: 1..3 distinct nonempty scopes from subsets of {x0,x1,x2}, and every head subset of their union. No outcome is assumed for this family; compare with the separate literal reference::exhaustive_minimum_tree oracle. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/code_review.md](../../../../code_review.md) |

## B0007

[Lines 51–61](../../../../../tests/support/query_families.hpp#L51); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline std::vector<Fixture> finite_three_variable_family()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Enumerate the complete finite family used by independent structural explanation comparison. |
| inputs / outputs | Chooses1..3 distinct nonempty scopes from seven subsets of{x0,x1,x2}, then every head subset of their union, producing426 named ordinary fixtures with no assumed outcome. |
| invariants | No fixture is skipped by expected truth or production recognition. Actual caller compares with separate reference::exhaustive_minimum_tree and real search/replay; the finite family is not a proof for all query sizes. |
| ownership | Owns all ordinary fixture/name/catalog/query containers; scopes is copied into each hypergraph call. |
| failure | Ordinary allocation failure aborts construction; no capped-prefix success or silent test skip. |
| cost | Finite mask loops plus426 full metadata builds/copies and vector growth; no native query-account or correctness authority is created. |
| Design | [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [include/crown/ir/model.hpp](../../../../../include/crown/ir/model.hpp), [tests/unit/query_explain_test.cpp](../../../../../tests/unit/query_explain_test.cpp), [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/tree_plans.md](../../../../tree_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 62–62](../../../../../tests/support/query_families.hpp#L62); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L62-L62:sha256:57d8d26ab753835be02f3726a8bd2e8d21b8ccb6b139eeb9c868ec6694239c4a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in query_families.hpp: namespace crown::query_explain_fixture. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/support/query_families.hpp](../../../../../tests/support/query_families.hpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/code_review.md](../../../../code_review.md) |
