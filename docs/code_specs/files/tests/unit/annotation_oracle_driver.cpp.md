# `tests/unit/annotation_oracle_driver.cpp` — block usage map

[Source](../../../../../tests/unit/annotation_oracle_driver.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `25a0ab09f82c2a68d7e670d416423960f767413593c80add2c839553cb5260ca`. 60 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../tests/unit/annotation_oracle_driver.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 9–15](../../../../../tests/unit/annotation_oracle_driver.cpp#L9) | Callable definition: template&lt;class T, class P&gt; T calculate(const std::string& operation, const P& policy, T a, T b, T c) | calls add, multiply, remove, replace; returns policy.add(a, b); policy.multiply(a, b) · [reviewed contract](#b0002) |
| [B0003 · 16–53](../../../../../tests/unit/annotation_oracle_driver.cpp#L16) | Callable definition: void execute(std::istringstream& input) | calls calculate, MultiplicityPolicy, IntegerPolicy::multiply, policy · [reviewed contract](#b0003) |
| [B0004 · 54–54](../../../../../tests/unit/annotation_oracle_driver.cpp#L54) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 55–60](../../../../../tests/unit/annotation_oracle_driver.cpp#L55) | Callable definition: int main() | calls std::getline, input, execute, code; 1 loop sites · [reviewed contract](#b0005) |

## B0001

[Lines 1–8](../../../../../tests/unit/annotation_oracle_driver.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:4d5dd68eb70740677dc5a17225e4ad7570ffc449aee71d1a7756972978cb4ded
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare annotation_oracle_driver.cpp: include "crown/annotations/policy.hpp", &lt;iostream&gt;, &lt;sstream&gt;, &lt;stdexcept&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/annotation_oracle_driver.cpp](../../../../../tests/unit/annotation_oracle_driver.cpp), [docs/annotations.md](../../../../annotations.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 9–15](../../../../../tests/unit/annotation_oracle_driver.cpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class T, class P> T calculate(const std::string& operation, const P& policy, T a, T b, T c)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Dispatch one parsed add, multiply, remove, or replace operation through its policy. |
| inputs / outputs | Receives operation, policy, and three scalar operands; returns the policy result. |
| invariants | replace consumes all three operands; add, multiply, and remove use the first two. Integer and decimal scale are handled directly in execute, outside this dispatcher. |
| ownership | Operands/results are values; policy is borrowed for the call. |
| failure | Unsupported operations are rejected by the dispatch path; policy errors propagate to execute. |
| cost | One policy call plus a fixed operation dispatch. |
| Design | [tests/unit/annotation_oracle_driver.cpp](../../../../../tests/unit/annotation_oracle_driver.cpp), [tests/integration/annotation_arithmetic.py](../../../../../tests/integration/annotation_arithmetic.py), [docs/annotations.md](../../../../annotations.md), [tests/integration/annotation_arithmetic.py](../../../../../tests/integration/annotation_arithmetic.py) |

## B0003

[Lines 16–53](../../../../../tests/unit/annotation_oracle_driver.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void execute(std::istringstream& input)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Parse and run one line-oriented annotation request. |
| inputs / outputs | Consumes the stream’s domain and operation records, invokes calculate or the special scale path, and writes one textual result. |
| invariants | It accepts multiplicity, signed-integer, and decimal domains with operation-specific fields; it prints ok before its late input.fail check and does not reject trailing tokens. |
| ownership | The input stream is borrowed; parser temporaries and result are local. |
| failure | Only crown::Error is caught by main; malformed stream state and unknown operation/domain throw std::runtime_error, while std::stoull conversion failures throw std::invalid_argument or std::out_of_range and also escape. |
| cost | Parses one request and performs one policy operation; input length determines parsing work. |
| Design | [tests/unit/annotation_oracle_driver.cpp](../../../../../tests/unit/annotation_oracle_driver.cpp), [tests/integration/annotation_arithmetic.py](../../../../../tests/integration/annotation_arithmetic.py), [docs/annotations.md](../../../../annotations.md), [tests/integration/annotation_arithmetic.py](../../../../../tests/integration/annotation_arithmetic.py) |

## B0004

[Lines 54–54](../../../../../tests/unit/annotation_oracle_driver.cpp#L54); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L54-L54:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in annotation_oracle_driver.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/annotation_oracle_driver.cpp](../../../../../tests/unit/annotation_oracle_driver.cpp), [docs/annotations.md](../../../../annotations.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 55–60](../../../../../tests/unit/annotation_oracle_driver.cpp#L55); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run annotation requests from standard input and map policy errors to text. |
| inputs / outputs | Reads each line, calls execute, prints an error code for caught crown::Error, and returns a process status. |
| invariants | The catch covers crown::Error only; it does not catch parser runtime errors. The driver does not reject trailing tokens after a valid request. |
| ownership | Owns only line-local streams and strings. |
| failure | Only crown::Error is converted to an error line; other std::exception types may terminate through the runtime. |
| cost | Processes each input line once; no explicit line-count or time cap. |
| Design | [tests/unit/annotation_oracle_driver.cpp](../../../../../tests/unit/annotation_oracle_driver.cpp), [tests/integration/annotation_arithmetic.py](../../../../../tests/integration/annotation_arithmetic.py), [docs/annotations.md](../../../../annotations.md), [tests/integration/annotation_arithmetic.py](../../../../../tests/integration/annotation_arithmetic.py) |
