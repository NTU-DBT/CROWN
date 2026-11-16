# `tests/unit/recognition_test.cpp` — block usage map

[Source](../../../../../tests/unit/recognition_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `971ddc171de6d828d809c5db2706c5c43bf2435dc2807edb8634b4025b94ad43`. 153 lines partitioned into 12 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/unit/recognition_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 15–15](../../../../../tests/unit/recognition_test.cpp#L15) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { if (!condition) throw std::runtime_error(m… · [reviewed contract](#b0002) |
| [B0003 · 16–19](../../../../../tests/unit/recognition_test.cpp#L16) | Explanatory comments or spacing. | source comment (unverified): // Independent ordinary join-tree criterion: enumerate undirected spanning · [reviewed contract](#b0003) |
| [B0004 · 20–59](../../../../../tests/unit/recognition_test.cpp#L20) | Callable definition: bool join_tree_exists(const std::vector&lt;Scope&gt;& scopes) | calls size, emplace_back, check, insert; guard check(pairs.size() &lt; 32, "test enumerator scope exceeded");; returns true; visited.size(); growth emplace_back, insert, push_back; 9 loop sites; source comment (unverified): // Independent ordinary join-tree criterion: enumerate undirected spanning · [reviewed contract](#b0004) |
| [B0005 · 60–60](../../../../../tests/unit/recognition_test.cpp#L60) | Explanatory comments or spacing. |  |
| [B0006 · 61–91](../../../../../tests/unit/recognition_test.cpp#L61) | Callable definition: void replay(const std::vector&lt;Scope&gt;& scopes, const GyoResult& result) | calls emplace_back, check, size, has_value; guard check(step.edge &lt; remaining.size() && remaining\[step.edge\].has_value(), "witness uses missing edge"…; growth emplace_back; 5 loop sites · [reviewed contract](#b0006) |
| [B0007 · 92–92](../../../../../tests/unit/recognition_test.cpp#L92) | Explanatory comments or spacing. |  |
| [B0008 · 93–126](../../../../../tests/unit/recognition_test.cpp#L93) | Callable definition: void exhaustive() | calls scopes, insert, gyo_reduce, check; guard check(result.acyclic == join_tree_exists(scopes), "body disagrees with independent join trees");; growth insert, push_back; 7 loop sites · [reviewed contract](#b0008) |
| [B0009 · 127–127](../../../../../tests/unit/recognition_test.cpp#L127) | Explanatory comments or spacing. |  |
| [B0010 · 128–147](../../../../../tests/unit/recognition_test.cpp#L128) | Callable definition: void classification() | calls check, analyze, push_back, size; guard check(analyze(catalog, query).query_class == QueryClass::acyclic_non_free_connex, "projected endpoi…; growth insert, push_back; 1 loop sites; source comment (unverified): // A universal synthetic head can make H+F acyclic while H remains cyclic. · [reviewed contract](#b0010) |
| [B0011 · 148–149](../../../../../tests/unit/recognition_test.cpp#L148) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0011) |
| [B0012 · 150–153](../../../../../tests/unit/recognition_test.cpp#L150) | Callable definition: int main() | calls exhaustive, classification, what; returns 0; 1 · [reviewed contract](#b0012) |

## B0001

[Lines 1–14](../../../../../tests/unit/recognition_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:b06fa775d43c74da32d6edd0cad9f30c079ba6f91a127dad33aa829dfd50d4b7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare recognition_test.cpp: include "crown/planner/recognize.hpp", &lt;algorithm&gt;, &lt;bit&gt;, &lt;cstdint&gt;, &lt;iostream&gt;, &lt;optional&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;utility&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/recognition_test.cpp](../../../../../tests/unit/recognition_test.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 15–15](../../../../../tests/unit/recognition_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a recognition assertion with its message. |
| inputs / outputs | Accepts a Boolean and borrowed string. |
| invariants | False is the only failure condition. |
| ownership | Message is borrowed. |
| failure | Throws std::runtime_error on false. |
| cost | One condition branch; callers pass string literals that form std::string arguments before entry, and failure copies the message into std::runtime_error. |
| Design | [tests/unit/recognition_test.cpp](../../../../../tests/unit/recognition_test.cpp), [include/crown/planner/recognize.hpp](../../../../../include/crown/planner/recognize.hpp), [src/planner/recognize.cpp](../../../../../src/planner/recognize.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/unit/recognition_test.cpp](../../../../../tests/unit/recognition_test.cpp) |

## B0003

[Lines 16–19](../../../../../tests/unit/recognition_test.cpp#L16); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L16-L19:sha256:95d1c3b77d202953609730fa1107736f03abe0f6a878a526d32a23f10425b3ea
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Explain the adjacent source contract: Independent ordinary join-tree criterion: enumerate undirected spanning trees, then check each variable's induced subgraph is connected. This code does not perform GYO, containment reduction, or production witness replay. |
| inputs / outputs | Human-readable source note in; no executable output or checked receipt. |
| invariants | This comment states context or a limitation. It does not itself enforce or prove the described behavior; use the adjacent implementation and its scoped contract. |
| ownership | Source text only; no object or resource lifetime is created. |
| failure | No runtime failure path in this comment; source encoding/comment syntax still belongs to compilation. |
| cost | No runtime operations from the comment. Any work described in the note belongs to the adjacent operation. |
| Design | [tests/unit/recognition_test.cpp](../../../../../tests/unit/recognition_test.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 20–59](../../../../../tests/unit/recognition_test.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
bool join_tree_exists(const std::vector<Scope>& scopes)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently decide whether a small scope family has a join tree. |
| inputs / outputs | Enumerates n-1 edge subsets, checks connectivity, then checks each variable’s induced nodes are connected. |
| invariants | Returns true for fewer than two scopes; checks that the possible-edge count is below 32 before bit-mask edge enumeration. |
| ownership | Adjacency and traversal state are local; scopes are borrowed. |
| failure | A check requires fewer than 32 possible edges before bit-mask enumeration; allocation may fail. |
| cost | Exponential in the number of possible edges; used only on at most four scopes. |
| Design | [tests/unit/recognition_test.cpp](../../../../../tests/unit/recognition_test.cpp), [include/crown/planner/recognize.hpp](../../../../../include/crown/planner/recognize.hpp), [src/planner/recognize.cpp](../../../../../src/planner/recognize.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0006

[Lines 61–91](../../../../../tests/unit/recognition_test.cpp#L61); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void replay(const std::vector<Scope>& scopes, const GyoResult& result)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Replay a GYO reduction certificate against the original scopes. |
| inputs / outputs | Reads scopes and GyoResult; checks private-variable, contained-edge, or empty-edge steps and reconstructs the residual core. |
| invariants | Every witness step is checked against the current residual; final acyclic status must agree with whether the core is empty. |
| ownership | Residual scopes and counters are owned local copies. |
| failure | Malformed steps or mismatched result throw std::runtime_error through check. |
| cost | Scans current edges/variables per witness step; bounded by the small generated cases. |
| Design | [tests/unit/recognition_test.cpp](../../../../../tests/unit/recognition_test.cpp), [include/crown/planner/recognize.hpp](../../../../../include/crown/planner/recognize.hpp), [src/planner/recognize.cpp](../../../../../src/planner/recognize.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [include/crown/planner/recognize.hpp](../../../../../include/crown/planner/recognize.hpp) |

## B0008

[Lines 93–126](../../../../../tests/unit/recognition_test.cpp#L93); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exhaustive()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare GYO recognition with exhaustive join-tree search over all small bodies. |
| inputs / outputs | Enumerates every body for up to four possible atoms over three variables, checks witness replay, and tests head masks for small cases. |
| invariants | The all-body comparison is finite and exponential; larger head-mask coverage is restricted to bodies with at most three edges. |
| ownership | Generated scope sets/results are local. |
| failure | Any disagreement between GYO, replay, and the independent tree oracle throws runtime_error. |
| cost | Finite exhaustive campaign: 4,681 bodies across up to four scopes, plus bounded head-mask cases. |
| Design | [tests/unit/recognition_test.cpp](../../../../../tests/unit/recognition_test.cpp), [include/crown/planner/recognize.hpp](../../../../../include/crown/planner/recognize.hpp), [src/planner/recognize.cpp](../../../../../src/planner/recognize.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp) |

## B0010

[Lines 128–147](../../../../../tests/unit/recognition_test.cpp#L128); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void classification()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check projected/free-connex classifications and a wide-variable case. |
| inputs / outputs | Checks a two-edge path under endpoint/middle heads, a cyclic triangle with acyclic head augmentation, and a 70-variable case. |
| invariants | The tests distinguish body acyclicity from head-augmented acyclicity; wide scope coverage is one structured fixture. |
| ownership | Fixtures and results are local. |
| failure | Assertion mismatch throws std::runtime_error. |
| cost | A few fixed shapes; the wide case has 70 variables but no exhaustive tree enumeration. |
| Design | [tests/unit/recognition_test.cpp](../../../../../tests/unit/recognition_test.cpp), [include/crown/planner/recognize.hpp](../../../../../include/crown/planner/recognize.hpp), [src/planner/recognize.cpp](../../../../../src/planner/recognize.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0011

[Lines 148–149](../../../../../tests/unit/recognition_test.cpp#L148); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L148-L149:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in recognition_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/recognition_test.cpp](../../../../../tests/unit/recognition_test.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0012

[Lines 150–153](../../../../../tests/unit/recognition_test.cpp#L150); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run exhaustive and classification recognition checks. |
| inputs / outputs | Calls exhaustive and classification, then returns zero. |
| invariants | Success output follows both groups. |
| ownership | All data is local to the groups. |
| failure | Catches std::exception and returns 1. |
| cost | Runs two fixed groups. |
| Design | [tests/unit/recognition_test.cpp](../../../../../tests/unit/recognition_test.cpp), [include/crown/planner/recognize.hpp](../../../../../include/crown/planner/recognize.hpp), [src/planner/recognize.cpp](../../../../../src/planner/recognize.cpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [include/crown/planner/recognize.hpp](../../../../../include/crown/planner/recognize.hpp) |
