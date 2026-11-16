# `tests/unit/annotation_policy_test.cpp` — block usage map

[Source](../../../../../tests/unit/annotation_policy_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `764df4fcbe5293c1c36edc7cdf7a1ea295ab8d1f15c17b9b5814b514235d3992`. 146 lines partitioned into 9 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../tests/unit/annotation_policy_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 9–11](../../../../../tests/unit/annotation_policy_test.cpp#L9) | Callable definition: void check(bool condition, const char* message) | calls std::runtime_error; guard void check(bool condition, const char* message) { · [reviewed contract](#b0002) |
| [B0003 · 12–16](../../../../../tests/unit/annotation_policy_test.cpp#L12) | Callable definition: template&lt;class F&gt; void rejects(F action, std::string_view code) | calls action, check, code, std::runtime_error; guard catch (const Error& error) { check(error.code() == code, "wrong annotation error"); return; } · [reviewed contract](#b0003) |
| [B0004 · 17–17](../../../../../tests/unit/annotation_policy_test.cpp#L17) | Callable definition: DecimalPayload d(std::string_view text) | calls Decimal::parse; returns {Decimal::parse(text)} · [reviewed contract](#b0004) |
| [B0005 · 18–73](../../../../../tests/unit/annotation_policy_test.cpp#L18) | Callable definition: void support_and_payload() | calls static_assert, replace_contribution, check, present; guard static_assert(!std::is_convertible_v&lt;Multiplicity, IntegerPayload&gt;); · [reviewed contract](#b0005) |
| [B0006 · 74–97](../../../../../tests/unit/annotation_policy_test.cpp#L74) | Callable definition: void decimals() | calls policy, check, add, d; guard check(policy.add(d("1.2"), d("-0.21")) == d("0.99"), "exact scale alignment"); · [reviewed contract](#b0006) |
| [B0007 · 98–135](../../../../../tests/unit/annotation_policy_test.cpp#L98) | Callable definition: void admission() | calls admit, check, admitted, rejects; guard check(set.admitted() && set.policy == "exact-nonnull-v1" && set.capabilities.zero_sum_free &&; 4 loop sites · [reviewed contract](#b0007) |
| [B0008 · 136–136](../../../../../tests/unit/annotation_policy_test.cpp#L136) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0008) |
| [B0009 · 137–146](../../../../../tests/unit/annotation_policy_test.cpp#L137) | Callable definition: int main() | calls support_and_payload, decimals, admission, what; returns 1 · [reviewed contract](#b0009) |

## B0001

[Lines 1–8](../../../../../tests/unit/annotation_policy_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:e0908e6f64fc5aaa2290d086e9d89f00c6146c74d265f4a9b92721087836917c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare annotation_policy_test.cpp: include "crown/annotations/policy.hpp", &lt;iostream&gt;, &lt;stdexcept&gt;, &lt;type_traits&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/annotation_policy_test.cpp](../../../../../tests/unit/annotation_policy_test.cpp), [docs/annotations.md](../../../../annotations.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 9–11](../../../../../tests/unit/annotation_policy_test.cpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void check(bool condition, const char* message)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Turn a failed assertion into the test’s runtime-error diagnostic. |
| inputs / outputs | Accepts a Boolean and borrowed message; returns normally when true. |
| invariants | False is the sole failure condition. |
| ownership | Message is borrowed for the call. |
| failure | Throws std::runtime_error(message) when the condition is false. |
| cost | One condition branch; on failure, constructing std::runtime_error copies the diagnostic text. Callers pass C-string literals. |
| Design | [tests/unit/annotation_policy_test.cpp](../../../../../tests/unit/annotation_policy_test.cpp), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp), [src/annotations/policy.cpp](../../../../../src/annotations/policy.cpp), [docs/annotations.md](../../../../annotations.md), [tests/unit/annotation_policy_test.cpp](../../../../../tests/unit/annotation_policy_test.cpp) |

## B0003

[Lines 12–16](../../../../../tests/unit/annotation_policy_test.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class F> void rejects(F action, std::string_view code)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Require an action to throw the expected annotation Error code. |
| inputs / outputs | Accepts callable F by value and expected code; calls named action() and returns on matching Error. |
| invariants | F is passed by value, not as a forwarding reference. Inside the helper, named action is an lvalue; only crown::Error is matched. |
| ownership | Callable is owned by this helper for the call; code is a borrowed string_view. |
| failure | Mismatched Error codes fail via check; no Error causes a runtime_error; unrelated exceptions propagate. |
| cost | One callable value is passed by value and invoked once; any cost to construct its captures occurs at the call site. |
| Design | [tests/unit/annotation_policy_test.cpp](../../../../../tests/unit/annotation_policy_test.cpp), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp), [src/annotations/policy.cpp](../../../../../src/annotations/policy.cpp), [docs/annotations.md](../../../../annotations.md), [tests/unit/annotation_policy_test.cpp](../../../../../tests/unit/annotation_policy_test.cpp) |

## B0004

[Lines 17–17](../../../../../tests/unit/annotation_policy_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
DecimalPayload d(std::string_view text)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse a decimal test payload. |
| inputs / outputs | Reads decimal text and returns a DecimalPayload. |
| invariants | Calls Decimal::parse(text) and wraps the parsed Decimal in DecimalPayload. |
| ownership | Returns an owned value; input text is borrowed. |
| failure | Malformed decimal input propagates the parser error. |
| cost | One parse over the supplied text. |
| Design | [tests/unit/annotation_policy_test.cpp](../../../../../tests/unit/annotation_policy_test.cpp), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp), [src/annotations/policy.cpp](../../../../../src/annotations/policy.cpp), [docs/annotations.md](../../../../annotations.md), [tests/unit/annotation_policy_test.cpp](../../../../../tests/unit/annotation_policy_test.cpp) |

## B0005

[Lines 18–73](../../../../../tests/unit/annotation_policy_test.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void support_and_payload()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check support accounting separately from signed payload updates. |
| inputs / outputs | Exercises add/update/remove operations against integer annotation policies and checks support and payload results. |
| invariants | Positive support count and signed payload are separate quantities; changing a payload does not imply a support-membership change. |
| ownership | All policy fixtures and values are local; no state escapes the function. |
| failure | Any failed assertion throws std::runtime_error; expected policy Errors are checked by rejects. |
| cost | A finite set of hand-written annotation values and arithmetic/contribution cases; this helper does not construct a runtime row set. |
| Design | [tests/unit/annotation_policy_test.cpp](../../../../../tests/unit/annotation_policy_test.cpp), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp), [src/annotations/policy.cpp](../../../../../src/annotations/policy.cpp), [docs/annotations.md](../../../../annotations.md), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp) |

## B0006

[Lines 74–97](../../../../../tests/unit/annotation_policy_test.cpp#L74); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void decimals()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check decimal arithmetic and exact decimal payload behavior. |
| inputs / outputs | Runs fixed-decimal alignment, add/multiply, replacement, overflow, canonical-zero, and multiplicity-scaling cases. |
| invariants | Assertions use parsed DecimalPayload values rather than floating-point approximations. |
| ownership | Decimal and policy objects are local values. |
| failure | Assertion failures throw std::runtime_error; rejected policy operations are checked by rejects. |
| cost | Finite fixed cases; each operation processes one decimal value. |
| Design | [tests/unit/annotation_policy_test.cpp](../../../../../tests/unit/annotation_policy_test.cpp), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp), [src/annotations/policy.cpp](../../../../../src/annotations/policy.cpp), [docs/annotations.md](../../../../annotations.md), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp) |

## B0007

[Lines 98–135](../../../../../tests/unit/annotation_policy_test.cpp#L98); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void admission()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check annotation admission limits and rejection codes. |
| inputs / outputs | Builds requests at allowed and denied boundaries, then verifies the returned decisions or Error codes. |
| invariants | The assertions cover configured policy/admission cases only; they do not establish behavior for every input size. |
| ownership | Fixture requests and results are local. |
| failure | Unexpected or wrong Error codes fail the test; expected errors are caught by rejects. |
| cost | Finite hand-authored boundary cases. |
| Design | [tests/unit/annotation_policy_test.cpp](../../../../../tests/unit/annotation_policy_test.cpp), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp), [src/annotations/policy.cpp](../../../../../src/annotations/policy.cpp), [docs/annotations.md](../../../../annotations.md), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp) |

## B0008

[Lines 136–136](../../../../../tests/unit/annotation_policy_test.cpp#L136); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L136-L136:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in annotation_policy_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/annotation_policy_test.cpp](../../../../../tests/unit/annotation_policy_test.cpp), [docs/annotations.md](../../../../annotations.md), [docs/code_review.md](../../../../code_review.md) |

## B0009

[Lines 137–146](../../../../../tests/unit/annotation_policy_test.cpp#L137); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run the three annotation policy test groups. |
| inputs / outputs | Calls support/payload, decimal, and admission checks; returns zero on success. |
| invariants | Any exception prevents the success line. |
| ownership | All test state is stack-local to called groups. |
| failure | Catches std::exception, writes its message, and returns 1. |
| cost | Runs three fixed groups. |
| Design | [tests/unit/annotation_policy_test.cpp](../../../../../tests/unit/annotation_policy_test.cpp), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp), [src/annotations/policy.cpp](../../../../../src/annotations/policy.cpp), [docs/annotations.md](../../../../annotations.md), [docs/annotations.md](../../../../annotations.md) |
