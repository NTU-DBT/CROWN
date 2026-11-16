# `tests/unit/exact_oracle_test.cpp` — block usage map

[Source](../../../../../tests/unit/exact_oracle_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `52916ba791e1b1e524328816c52c8e9c234932418f969c201229c88ef2ba6d49`. 236 lines partitioned into 10 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–16](../../../../../tests/unit/exact_oracle_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 17–17](../../../../../tests/unit/exact_oracle_test.cpp#L17) | Callable definition: void check(bool condition, const std::string& message) | calls std::runtime_error; guard void check(bool condition, const std::string& message) { if (!condition) throw std::runtime_error(m… · [reviewed contract](#b0002) |
| [B0003 · 18–18](../../../../../tests/unit/exact_oracle_test.cpp#L18) | Type/record definition: struct Fixture |  · [reviewed contract](#b0003) |
| [B0004 · 19–40](../../../../../tests/unit/exact_oracle_test.cpp#L19) | Callable definition: Fixture query_for(const std::vector&lt;std::vector&lt;std::size_t&gt;&gt;& scopes, const std::vector&lt;std::size_t&gt;& head) | calls insert, begin, end, emplace; returns fixture; growth emplace, emplace_back, insert, push_back; 5 loop sites · [reviewed contract](#b0004) |
| [B0005 · 41–59](../../../../../tests/unit/exact_oracle_test.cpp#L41) | Callable definition: void literal_foundation() | calls query_for, reference::exhaustive_minimum_tree, check, planner::validate_tree; guard check(result.status == planner::OracleStatus::proven_minimum && result.minimum_height == expected &…; 1 loop sites · [reviewed contract](#b0005) |
| [B0006 · 60–62](../../../../../tests/unit/exact_oracle_test.cpp#L60) | Callable definition: planner::HeightCertificate certificate_for(const planner::OracleResult& result) | calls ; returns {result.algorithm, result.minimum_height, result.tree, result.lower_bounds} · [reviewed contract](#b0006) |
| [B0007 · 63–109](../../../../../tests/unit/exact_oracle_test.cpp#L63) | Callable definition: void independent_small_family() | calls scopes, push_back, query_for, reference::exhaustive_minimum_tree; guard check(exact.status != planner::OracleStatus::resource_limit && literal.status != planner::OracleSta…; returns node.kind == NodeKind::generalized; growth push_back; 8 loop sites; source comment (unverified): // Three-atom cases exercise multiple generalized nodes and cyclic failure. · [reviewed contract](#b0007) |
| [B0008 · 110–231](../../../../../tests/unit/exact_oracle_test.cpp#L110) | Callable definition: void proof_corruption_and_limits() | calls query_for, planner::minimum_tree, check, certificate_for; guard check(exact.minimum_height == 1, "full two-edge minimum");; growth push_back; 5 loop sites · [reviewed contract](#b0008) |
| [B0009 · 232–232](../../../../../tests/unit/exact_oracle_test.cpp#L232) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0009) |
| [B0010 · 233–236](../../../../../tests/unit/exact_oracle_test.cpp#L233) | Callable definition: int main() | calls literal_foundation, independent_small_family, proof_corruption_and_limits, what; returns 0; 1 · [reviewed contract](#b0010) |

## B0001

[Lines 1–16](../../../../../tests/unit/exact_oracle_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L16:sha256:eadf2d79d42ef365d07feb5bb84b984f46ea88156c59190cf18c5042e7aec842
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare exact_oracle_test.cpp: include "crown/planner/oracle.hpp", "crown/planner/search.hpp", "crown/planner/verify.hpp", "crown/io/oracle.hpp", "crown/api/error.hpp", "tree_oracle.hpp", &lt;algorithm&gt;, &lt;iostream&gt;, &lt;map&gt;, &lt;stdexcept&gt;, &lt;string&gt;, &lt;tuple&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/exact_oracle_test.cpp](../../../../../tests/unit/exact_oracle_test.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 17–17](../../../../../tests/unit/exact_oracle_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const std::string& message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Fail an exact-oracle assertion with its message. |
| inputs / outputs | Accepts a condition and borrowed string; returns if true. |
| invariants | False is the only failure condition. |
| ownership | Message is borrowed. |
| failure | Throws std::runtime_error on false. |
| cost | One condition branch in the helper; call sites construct std::string message arguments before entry, and failure copies the message into std::runtime_error. |
| Design | [tests/unit/exact_oracle_test.cpp](../../../../../tests/unit/exact_oracle_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/unit/exact_oracle_test.cpp](../../../../../tests/unit/exact_oracle_test.cpp) |

## B0003

[Lines 18–18](../../../../../tests/unit/exact_oracle_test.cpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Fixture
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Group the catalog and query used by exact-oracle fixtures. |
| inputs / outputs | Stores one Catalog and one Query by value. |
| invariants | query_for maps sorted distinct scope labels to dense zero-based VariableIds; input labels may be sparse and are not used directly as VariableIds. |
| ownership | Catalog and Query are owned members. |
| failure | Aggregate construction can fail through allocation; no semantic validation occurs in the type. |
| cost | Storage is proportional to its catalog/query fixture. |
| Design | [tests/unit/exact_oracle_test.cpp](../../../../../tests/unit/exact_oracle_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/unit/exact_oracle_test.cpp](../../../../../tests/unit/exact_oracle_test.cpp) |

## B0004

[Lines 19–40](../../../../../tests/unit/exact_oracle_test.cpp#L19); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Fixture query_for(const std::vector<std::vector<std::size_t>>& scopes, const std::vector<std::size_t>& head)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Build a Catalog/Query fixture from scope masks and head IDs. |
| inputs / outputs | Reads scope vectors and head indices; returns a Fixture with generated tables, variables, atoms, and output aliases. |
| invariants | The builder collects sorted distinct scope labels and maps them to dense VariableIds, then looks up each head label in that map; labels need not be contiguous, but every head label must occur in a scope. |
| ownership | Returns owned catalog/query values; inputs are borrowed. |
| failure | A head label absent from the collected scopes throws std::out_of_range from variables.at; sparse labels present in scopes are supported. Allocation may fail. |
| cost | Work scales with scopes, terms, and generated variable/table metadata. |
| Design | [tests/unit/exact_oracle_test.cpp](../../../../../tests/unit/exact_oracle_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp) |

## B0005

[Lines 41–59](../../../../../tests/unit/exact_oracle_test.cpp#L41); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void literal_foundation()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check literal exact-oracle cases and resource-stop statuses. |
| inputs / outputs | Runs seven analytic cases plus unsupported/projected-head examples and zero-work/zero-literal-scope limits. |
| invariants | A resource-limited result is distinguished from an exact optimum or infeasibility; the tests do not treat limits as semantic outcomes. |
| ownership | Queries, results, and certificates are local values. |
| failure | Assertion failure throws std::runtime_error; invalid fixture operations may propagate their own errors. |
| cost | Seven base analytic cases plus fixed unsupported and limit cases. |
| Design | [tests/unit/exact_oracle_test.cpp](../../../../../tests/unit/exact_oracle_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md) |

## B0006

[Lines 60–62](../../../../../tests/unit/exact_oracle_test.cpp#L60); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::HeightCertificate certificate_for(const planner::OracleResult& result)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Construct a public HeightCertificate replay input from selected OracleResult fields. |
| inputs / outputs | Copies algorithm, minimum_height, optional tree, and lower_bounds from OracleResult into HeightCertificate. |
| invariants | Copies the supplied public result fields without validating their claims. Constructing HeightCertificate creates no VerifiedOptimum authority; callers check outcomes and replay certificates separately. |
| ownership | The returned HeightCertificate owns copies of the optional tree and lower-bound vector; OracleResult is borrowed and unchanged. |
| failure | Copying the tree or lower-bound vector may fail through allocation; this helper performs no checked certificate access. |
| cost | Copies the optional tree and lower-bound vector in proportion to their proof representation size. |
| Design | [tests/unit/exact_oracle_test.cpp](../../../../../tests/unit/exact_oracle_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp) |

## B0007

[Lines 63–109](../../../../../tests/unit/exact_oracle_test.cpp#L63); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void independent_small_family()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Compare the exact oracle with a separate literal labelled-topology and full-scope-power-set tree enumeration. |
| inputs / outputs | Compares 371 generated zero-to-two-atom scope/head queries with literal labelled-topology enumeration, then compares seven selected three-atom cases; a final nested three-atom case checks height one and two generalized nodes. |
| invariants | The campaign covers 371 exact comparisons plus seven selected three-atom shapes; this is fixture evidence, not a general complexity bound. |
| ownership | All generated queries/results are local; reference collections are owned per case. |
| failure | Any mismatch or failed validity assertion throws std::runtime_error. |
| cost | The 371 family cases use at most two atoms, followed by seven three-atom literal-tree comparisons and one exact-search-only nested-shape check. Literal enumeration is confined to these small fixtures. |
| Design | [tests/unit/exact_oracle_test.cpp](../../../../../tests/unit/exact_oracle_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [tests/reference/candidate_set.cpp](../../../../../tests/reference/candidate_set.cpp) |

## B0008

[Lines 110–231](../../../../../tests/unit/exact_oracle_test.cpp#L110); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void proof_corruption_and_limits()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check proof corruption, stop limits, residual counterexamples, and continuation behavior. |
| inputs / outputs | Mutates certificates/trees and checks work/depth/time stops; exercises a seven-atom residual counterexample, stops a strict continuation at zero replay budget after production, raises that replay budget and resumes it; separately compares a 70-variable literal-scope cap with exact search. |
| invariants | The legacy recursion_limit name does not imply recursive implementation. The continuation is advanced in quanta of 4096 with a five-million-call loop ceiling; replay gets a separately raised ceiling. |
| ownership | Queries, oracle owners, continuation handles, and proof mutations are local to this test. |
| failure | Assertions fail with runtime_error; expected validation and resource outcomes are checked separately. |
| cost | Includes a 70-variable wide case; bounded loops allow at most five million advances per continuation segment, not a CPU-time guarantee. |
| Design | [tests/unit/exact_oracle_test.cpp](../../../../../tests/unit/exact_oracle_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp) |

## B0009

[Lines 232–232](../../../../../tests/unit/exact_oracle_test.cpp#L232); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L232-L232:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in exact_oracle_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/exact_oracle_test.cpp](../../../../../tests/unit/exact_oracle_test.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/code_review.md](../../../../code_review.md) |

## B0010

[Lines 233–236](../../../../../tests/unit/exact_oracle_test.cpp#L233); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the exact-oracle fixture groups. |
| inputs / outputs | Calls literal_foundation, independent_small_family, and proof_corruption_and_limits. |
| invariants | Success is printed only after all three groups return. |
| ownership | All state belongs to the called local test groups. |
| failure | Catches std::exception and returns 1 on failure. |
| cost | Runs three fixed groups; their inner bounds are stated by each test. |
| Design | [tests/unit/exact_oracle_test.cpp](../../../../../tests/unit/exact_oracle_test.cpp), [include/crown/planner/oracle.hpp](../../../../../include/crown/planner/oracle.hpp), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md) |
