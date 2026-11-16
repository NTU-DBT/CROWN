# `tests/unit/tree_verifier_test.cpp` — block usage map

[Source](../../../../../tests/unit/tree_verifier_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `e1e777f8b5d8e26a5ce576c8f5d2add8ede2302d4f60d589377e88f612f5cd30`. 278 lines partitioned into 18 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../tests/unit/tree_verifier_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 16–16](../../../../../tests/unit/tree_verifier_test.cpp#L16) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { if (!condition) throw std::runtime_error(m… · [reviewed contract](#b0002) |
| [B0003 · 17–17](../../../../../tests/unit/tree_verifier_test.cpp#L17) | Type/record definition: struct Fixture |  · [reviewed contract](#b0003) |
| [B0004 · 18–39](../../../../../tests/unit/tree_verifier_test.cpp#L18) | Callable definition: Fixture query_for(const std::vector&lt;std::vector&lt;std::size_t&gt;&gt;& scopes, const std::vector&lt;std::size_t&gt;& head) | calls insert, begin, end, check; guard check(variable == fixture.query.variables.size(), "test fixture variable IDs must be dense");; returns fixture; growth emplace_back, insert, push_back; 5 loop sites · [reviewed contract](#b0004) |
| [B0005 · 40–46](../../../../../tests/unit/tree_verifier_test.cpp#L40) | Callable definition: TreeNode node(std::string name, NodeKind kind, std::initializer_list&lt;std::size_t&gt; scope, std::initializer_list&lt;std::size_t&gt; child… | calls std::move, insert, push_back; returns result; growth insert, push_back; 2 loop sites · [reviewed contract](#b0005) |
| [B0006 · 47–51](../../../../../tests/unit/tree_verifier_test.cpp#L47) | Callable definition: FreeConnexTree joined_tree() | calls node; returns {NodeId{0}, {node(@ , NodeKind::generalized, {1}, {1, 2}), · [reviewed contract](#b0006) |
| [B0007 · 52–57](../../../../../tests/unit/tree_verifier_test.cpp#L52) | Callable definition: void has_rule(const planner::ValidationReport& report, const std::string& rule) | calls check, std::find_if, begin, end; guard check(!report.valid && !report.native_height && !report.edge_depth, "invalid tree must not advertis…; returns issue.rule == rule · [reviewed contract](#b0007) |
| [B0008 · 58–62](../../../../../tests/unit/tree_verifier_test.cpp#L58) | Callable definition: void rejects(const std::function&lt;void()&gt;& action, const std::string& code) | calls void, action, check, code; guard catch (const Error& error) { check(error.code() == code, "wrong input rejection: " + error.code());… · [reviewed contract](#b0008) |
| [B0009 · 63–63](../../../../../tests/unit/tree_verifier_test.cpp#L63) | Explanatory comments or spacing. |  |
| [B0010 · 64–129](../../../../../tests/unit/tree_verifier_test.cpp#L64) | Callable definition: void valid_and_corrupt() | calls query_for, joined_tree, validate_tree, check; guard check(report.valid && report.native_height == 1 && report.edge_depth == 1, "generalized root has ze…; returns issue.rule == @ && issue.variable == VariableId{1} && issue.node; growth insert, push_back · [reviewed contract](#b0010) |
| [B0011 · 130–130](../../../../../tests/unit/tree_verifier_test.cpp#L130) | Explanatory comments or spacing. |  |
| [B0012 · 131–194](../../../../../tests/unit/tree_verifier_test.cpp#L131) | Callable definition: void constants_and_dynamic_sizes() | calls query_for, validate_tree, check, has_rule; guard check(zero.valid && zero.native_height == 0 && zero.edge_depth == 0, "constant has empty height-zer…; growth insert, push_back; 5 loop sites · [reviewed contract](#b0012) |
| [B0013 · 195–195](../../../../../tests/unit/tree_verifier_test.cpp#L195) | Explanatory comments or spacing. |  |
| [B0014 · 196–226](../../../../../tests/unit/tree_verifier_test.cpp#L196) | Callable definition: void connex_lemma() | calls query_for, node, clear, insert; guard check(report.valid == exists, "maximal connex disagrees with explicit subtree enumeration");; growth insert, push_back; 6 loop sites; source comment (unverified): // Independent check: enumerate every root-containing parent-closed subset, · [reviewed contract](#b0014) |
| [B0015 · 227–227](../../../../../tests/unit/tree_verifier_test.cpp#L227) | Explanatory comments or spacing. |  |
| [B0016 · 228–269](../../../../../tests/unit/tree_verifier_test.cpp#L228) | Callable definition: void codec() | calls query_for, joined_tree, io::write_tree, io::read_tree; guard check(io::write_tree(decoded, fixture.catalog, fixture.query) == encoded, "plan roundtrip preserves…; growth push_back · [reviewed contract](#b0016) |
| [B0017 · 270–271](../../../../../tests/unit/tree_verifier_test.cpp#L270) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0017) |
| [B0018 · 272–278](../../../../../tests/unit/tree_verifier_test.cpp#L272) | Callable definition: int main() | calls valid_and_corrupt, constants_and_dynamic_sizes, connex_lemma, codec; returns 0; 1 · [reviewed contract](#b0018) |

## B0001

[Lines 1–15](../../../../../tests/unit/tree_verifier_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:cdecdec9735633ad20a3d108070a6b3a4248c57d208dbf4984bfe4fb3122a13a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare tree_verifier_test.cpp: include "crown/api/error.hpp", "crown/io/tree.hpp", &lt;algorithm&gt;, &lt;cstdint&gt;, &lt;functional&gt;, &lt;iostream&gt;, &lt;limits&gt;, &lt;stdexcept&gt;, &lt;string&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/tree_verifier_test.cpp](../../../../../tests/unit/tree_verifier_test.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 16–16](../../../../../tests/unit/tree_verifier_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail a verifier assertion with its message. |
| inputs / outputs | Accepts Boolean and borrowed string. |
| invariants | False is the only failure condition. |
| ownership | Message is borrowed. |
| failure | Throws std::runtime_error on false. |
| cost | One condition branch; callers form std::string message arguments before entry, and failure copies text into std::runtime_error. |
| Design | [tests/unit/tree_verifier_test.cpp](../../../../../tests/unit/tree_verifier_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/unit/tree_verifier_test.cpp](../../../../../tests/unit/tree_verifier_test.cpp) |

## B0003

[Lines 17–17](../../../../../tests/unit/tree_verifier_test.cpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Hold a catalog/query pair for tree-verifier fixtures. |
| inputs / outputs | Owns Catalog and Query values. |
| invariants | The fixture builder uses dense zero-based variable labels; this aggregate adds no validation. |
| ownership | Members are owned values. |
| failure | Aggregate allocation may fail. |
| cost | Storage follows the fixture. |
| Design | [tests/unit/tree_verifier_test.cpp](../../../../../tests/unit/tree_verifier_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp) |

## B0004

[Lines 18–39](../../../../../tests/unit/tree_verifier_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture query_for(const std::vector<std::vector<std::size_t>>& scopes, const std::vector<std::size_t>& head)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a catalog/query from scope and head index vectors. |
| inputs / outputs | Reads vectors and returns a Fixture with generated variables, tables, atoms, and head aliases. |
| invariants | Variable indices must be dense zero-based because the builder indexes its variable array by the original label. |
| ownership | Returns owned Catalog and Query; inputs are borrowed. |
| failure | Non-dense scope IDs fail the fixture check with std::runtime_error; invalid head IDs are rejected by validate. Allocation may fail. |
| cost | Work follows the number of scopes and their terms. |
| Design | [tests/unit/tree_verifier_test.cpp](../../../../../tests/unit/tree_verifier_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp) |

## B0005

[Lines 40–46](../../../../../tests/unit/tree_verifier_test.cpp#L40); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
TreeNode node(std::string name, NodeKind kind, std::initializer_list<std::size_t> scope, std::initializer_list<std::size_t> children, std::optional<std::size_t> occurrence = {})
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a typed tree node from compact test indices. |
| inputs / outputs | Returns a TreeNode with converted scope/child IDs and optional occurrence. |
| invariants | The scope is a VariableSet, so repeated IDs collapse and iteration is sorted; child IDs are appended to a vector in initializer-list order. The supplied kind is retained. |
| ownership | Returned node owns name, scope, and children; input lists are borrowed for construction. |
| failure | Allocation may fail; invalid indices are checked later by validation. |
| cost | Moves the by-value name into the node and inserts each listed variable and child ID into owned containers; work follows initializer-list lengths. |
| Design | [tests/unit/tree_verifier_test.cpp](../../../../../tests/unit/tree_verifier_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp) |

## B0006

[Lines 47–51](../../../../../tests/unit/tree_verifier_test.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
FreeConnexTree joined_tree()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a three-node tree with a generalized root and native children. |
| inputs / outputs | Returns a FreeConnexTree used to test generalized-node validation. |
| invariants | The root scope is {1}; each native child contributes a separate occurrence. |
| ownership | Returns owned node vector/tree. |
| failure | Allocation may fail; structural validity is checked by the verifier. |
| cost | Constant three-node fixture. |
| Design | [tests/unit/tree_verifier_test.cpp](../../../../../tests/unit/tree_verifier_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0007

[Lines 52–57](../../../../../tests/unit/tree_verifier_test.cpp#L52); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void has_rule(const planner::ValidationReport& report, const std::string& rule)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Assert that a validation report contains a named rule. |
| inputs / outputs | Reads a ValidationReport and rule; first requires invalid status with no checked native height or edge depth, then finds the named violation and requires a nonempty message. |
| invariants | It checks invalid status, absence of native-height/edge-depth claims, and a nonempty matching violation message; it does not check issue ordering or uniqueness. |
| ownership | Report and string are borrowed. |
| failure | Missing rule throws std::runtime_error. |
| cost | Checks report flags, eagerly constructs the missing-rule diagnostic, scans the issue list once with find_if, and checks the matched diagnostic string. |
| Design | [tests/unit/tree_verifier_test.cpp](../../../../../tests/unit/tree_verifier_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp) |

## B0008

[Lines 58–62](../../../../../tests/unit/tree_verifier_test.cpp#L58); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void rejects(const std::function<void()>& action, const std::string& code)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require a verifier action to fail with one Error code. |
| inputs / outputs | Receives std::function by const reference and expected code; invokes action and returns on match. |
| invariants | Only crown::Error is caught; no match or a different code fails. |
| ownership | Callable and code are borrowed for the call. |
| failure | Wrong code or missing Error throws std::runtime_error; unrelated exceptions propagate. |
| cost | Invokes the action once; if it throws Error, the helper constructs the dynamic wrong-code diagnostic before checking the expected code, even on a match. Failure paths then build std::runtime_error; unrelated exceptions propagate. |
| Design | [tests/unit/tree_verifier_test.cpp](../../../../../tests/unit/tree_verifier_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp) |

## B0010

[Lines 64–129](../../../../../tests/unit/tree_verifier_test.cpp#L64); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void valid_and_corrupt()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check valid tree reports and deliberately corrupted proof/tree structures. |
| inputs / outputs | Covers valid/corrupt height, depth, separators, connex, cover, connect, guard, topology, claims, root, and generalized-node cases. The bottom-generalized fixture also removes its occurrence and asserts a cover failure, so it does not isolate a leaf-specific rule. |
| invariants | A valid report is tied to the supplied Query/Catalog; individual corruption checks establish only the named rejection. |
| ownership | Trees, reports, and mutations are local. |
| failure | Expected verifier errors are checked with rejects; failed assertions throw runtime_error. |
| cost | Finite hand-built variants of a small fixture. |
| Design | [tests/unit/tree_verifier_test.cpp](../../../../../tests/unit/tree_verifier_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0012

[Lines 131–194](../../../../../tests/unit/tree_verifier_test.cpp#L131); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void constants_and_dynamic_sizes()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check constants, dynamic scopes, and deep iterative traversal. |
| inputs / outputs | Covers empty/nullary trees, height/depth distinction, disconnected products, 9 native leaves, 70 variables, and a 1,500-node chain. |
| invariants | The deep-chain case checks iterative validation behavior on this fixture, not an unbounded stack guarantee. |
| ownership | All large scope/tree values are owned locally. |
| failure | Any invalid report or assertion fails the test. |
| cost | Finite fixtures up to 1,500 nodes and 70 variables. |
| Design | [tests/unit/tree_verifier_test.cpp](../../../../../tests/unit/tree_verifier_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0014

[Lines 196–226](../../../../../tests/unit/tree_verifier_test.cpp#L196); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void connex_lemma()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare verifier connex claims with an independent parent-closed subset check. |
| inputs / outputs | Tests 16 head variants over a fixed four-node tree and compares existence with report.valid. |
| invariants | The small subset enumeration is independent of the verifier’s C* implementation; it does not prove a general theorem by itself. |
| ownership | Fixed tree and reports are local. |
| failure | Mismatch throws std::runtime_error. |
| cost | 16 heads times eight root-containing subsets of the four-node tree. |
| Design | [tests/unit/tree_verifier_test.cpp](../../../../../tests/unit/tree_verifier_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |

## B0016

[Lines 228–269](../../../../../tests/unit/tree_verifier_test.cpp#L228); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void codec()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Round-trip typed trees and reject malformed tree JSON. |
| inputs / outputs | Checks valid roundtrip and invalid version/catalog/semantics/fields/types/IDs/scopes/claims/duplicate keys plus uint64 catalog version. |
| invariants | Codec acceptance is separate from P02 validity; loaded claims still pass through verifier checks. |
| ownership | JSON and tree values are owned locally. |
| failure | Expected schema errors are asserted by rejects; unexpected failures fail the test. |
| cost | Finite codec cases over fixed trees; checks the uint64 catalog-version and native-height size_t boundaries. |
| Design | [tests/unit/tree_verifier_test.cpp](../../../../../tests/unit/tree_verifier_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp) |

## B0017

[Lines 270–271](../../../../../tests/unit/tree_verifier_test.cpp#L270); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L270-L271:sha256:c2bd7638f09d52cb034ed574f539304035fc6fab162bf8d5fa20a35d8c7288a1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in tree_verifier_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/tree_verifier_test.cpp](../../../../../tests/unit/tree_verifier_test.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md) |

## B0018

[Lines 272–278](../../../../../tests/unit/tree_verifier_test.cpp#L272); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run all tree verifier and codec test groups. |
| inputs / outputs | Calls valid/corrupt, constants/dynamic, connex lemma, and codec. |
| invariants | The success message follows all four groups. |
| ownership | All state is local to the called groups. |
| failure | Catches std::exception and returns 1. |
| cost | Runs four fixed groups. |
| Design | [tests/unit/tree_verifier_test.cpp](../../../../../tests/unit/tree_verifier_test.cpp), [include/crown/planner/verify.hpp](../../../../../include/crown/planner/verify.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_proofs.md](../../../../planner_proofs.md) |
