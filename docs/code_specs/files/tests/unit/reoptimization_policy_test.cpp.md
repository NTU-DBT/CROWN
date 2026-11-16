# `tests/unit/reoptimization_policy_test.cpp` — block usage map

[Source](../../../../../tests/unit/reoptimization_policy_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `2450455363e7ce1664b08e91a4c03a0f08b33b79bda5a361463663062d4a14f9`. 52 lines partitioned into 4 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../tests/unit/reoptimization_policy_test.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 8–8](../../../../../tests/unit/reoptimization_policy_test.cpp#L8) | Callable definition: void check(bool value,const char* message) | calls std::runtime_error; guard void check(bool value,const char* message) {if(!value)throw std::runtime_error(message);} · [reviewed contract](#b0002) |
| [B0003 · 9–9](../../../../../tests/unit/reoptimization_policy_test.cpp#L9) | Closes surrounding scope/type. |  · [reviewed contract](#b0003) |
| [B0004 · 10–52](../../../../../tests/unit/reoptimization_policy_test.cpp#L10) | Callable definition: int main() | calls r::evaluate, check, max, what; guard check(exact.stop==r::PolicyStop::eligible && exact.saving_ns_per_input==20 && exact.charged_and_res…; returns 0; 1 · [reviewed contract](#b0004) |

## B0001

[Lines 1–7](../../../../../tests/unit/reoptimization_policy_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:3efbdf8032a2214de82f9d53df4c78671fbf512c1bfd939344acb6abdc2fa76d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare reoptimization_policy_test.cpp: include "crown/runtime/reoptimization.hpp", &lt;iostream&gt;, &lt;limits&gt;, &lt;stdexcept&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/reoptimization_policy_test.cpp](../../../../../tests/unit/reoptimization_policy_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–8](../../../../../tests/unit/reoptimization_policy_test.cpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool value,const char* message) {if(!value)throw std::runtime_error(message);}
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Throw on a failed arithmetic-policy assertion with the supplied diagnostic. |
| inputs / outputs | Boolean and C string message in; no result. |
| invariants | Used only for the explicit evaluate() boundary assertions in this file. |
| ownership | Message pointer is borrowed only during the exception construction; runtime_error owns its diagnostic copy. |
| failure | Throws std::runtime_error when condition is false. |
| cost | Constant predicate; diagnostic copy occurs only on failure. |
| Design | [tests/unit/reoptimization_policy_test.cpp § void check(bool value,const char* message) (lines 8-8)](../../../../../tests/unit/reoptimization_policy_test.cpp) |

## B0003

[Lines 9–9](../../../../../tests/unit/reoptimization_policy_test.cpp#L9); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L9-L9:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in reoptimization_policy_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/reoptimization_policy_test.cpp](../../../../../tests/unit/reoptimization_policy_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 10–52](../../../../../tests/unit/reoptimization_policy_test.cpp#L10); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise exact, fractional, zero, maximal, overflow, hysteresis and forecast boundaries of pure payback arithmetic. |
| inputs / outputs | No arguments; constructs fixed Policy, Forecast and PreparationCosts values and calls evaluate across the 20 listed assertions. |
| invariants | Checks exact required input counts, ceil thresholds, invalid policy/epoch/forecast, insufficient savings/horizon and arithmetic overflow. It never constructs a session, selects a tree or authorizes a switch. |
| ownership | All inputs/results are stack value objects; evaluate is declared noexcept and allocation-free. |
| failure | Each mismatch throws runtime_error; catch prints and returns 1. |
| cost | Twenty constant-size arithmetic calls; the maximal uint64 cases check overflow-safe formulas, not runtime performance. |
| Design | [tests/unit/reoptimization_policy_test.cpp § int main() (lines 10-52)](../../../../../tests/unit/reoptimization_policy_test.cpp), [src/runtime/reoptimization.cpp § evaluate (lines 8-44)](../../../../../src/runtime/reoptimization.cpp), [include/crown/runtime/reoptimization.hpp § Forecast, Policy, PreparationCosts and evaluate (lines 11-45)](../../../../../include/crown/runtime/reoptimization.hpp), [docs/reoptimization.md § Policy units and boundaries (lines 42-57)](../../../../reoptimization.md), [CMakeLists.txt § reoptimization_policy registration (lines 653-657)](../../../../../CMakeLists.txt) |
