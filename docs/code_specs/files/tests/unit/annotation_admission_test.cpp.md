# `tests/unit/annotation_admission_test.cpp` — block usage map

[Source](../../../../../tests/unit/annotation_admission_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `c389a4354cdefacb63f367d7456864a3d2fab5c9a4bbab96752975a090a9b7a0`. 42 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../tests/unit/annotation_admission_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 9–16](../../../../../tests/unit/annotation_admission_test.cpp#L9) | Callable definition: template&lt;class F&gt; void rejects(F action, std::string_view code) | calls action, code, std::runtime_error · [reviewed contract](#b0002) |
| [B0003 · 17–37](../../../../../tests/unit/annotation_admission_test.cpp#L17) | Callable definition: void run() | calls planner::lower_tree, guarantee, std::runtime_error, std::string_view; 2 loop sites · [reviewed contract](#b0003) |
| [B0004 · 38–38](../../../../../tests/unit/annotation_admission_test.cpp#L38) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 39–42](../../../../../tests/unit/annotation_admission_test.cpp#L39) | Callable definition: int main() | calls run, what; returns 1 · [reviewed contract](#b0005) |

## B0001

[Lines 1–8](../../../../../tests/unit/annotation_admission_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:cdd4b97cb3821468da7f16ec83e8d7359002790a0fa672d45fe4df183ee33923
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare annotation_admission_test.cpp: include "crown/annotations/policy.hpp", "crown/io/physical.hpp", "crown/planner/lower.hpp", &lt;iostream&gt;, &lt;stdexcept&gt;; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/annotation_admission_test.cpp](../../../../../tests/unit/annotation_admission_test.cpp), [docs/sql_admission.md](../../../../sql_admission.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 9–16](../../../../../tests/unit/annotation_admission_test.cpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class F> void rejects(F action, std::string_view code)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Asserts that a supplied policy surface rejects with a specific Error code. |
| inputs / outputs | Takes a callable by value and expected code; calls the named local action as an lvalue and checks caught crown::Error.code(). |
| invariants | Only the six explicit invalid-policy probes are covered; successful action return is itself a failure. |
| ownership | Callable and code view live through the call; callable-owned captures follow ordinary value semantics. |
| failure | Wrong code or no exception raises std::runtime_error; non-Crown exceptions propagate. |
| cost | One invocation per probe; there is no allocation-attempt counter or denial assertion. |
| Design | [tests/unit/annotation_admission_test.cpp](../../../../../tests/unit/annotation_admission_test.cpp), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp) |

## B0003

[Lines 17–37](../../../../../tests/unit/annotation_admission_test.cpp#L17); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void run()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Confirms annotation arithmetic names fail closed at all three physical admission surfaces. |
| inputs / outputs | Builds one tree plan for each of the reference and indexed backend options; for six policy values it probes lower_tree, query_identity, and read_physical_options using serialized options. |
| invariants | There are 2×6×3=36 expected invalid_policy failures; the base exact-set/exact-nonnull policy is the admitted baseline, and no runtime is launched. |
| ownership | Plan, catalog, query, and JSON text are ordinary local fixtures; read options returns a value only on a non-rejecting path. |
| failure | The helper checks exact invalid_policy codes; other errors fail the test rather than counting as expected rejection. |
| cost | Two backend plans plus 36 fail-closed calls and their option serialization; no physical query execution or allocation measurement. |
| Design | [tests/unit/annotation_admission_test.cpp](../../../../../tests/unit/annotation_admission_test.cpp), [include/crown/annotations/policy.hpp](../../../../../include/crown/annotations/policy.hpp), [src/io/physical.cpp](../../../../../src/io/physical.cpp), [src/io/identity.cpp](../../../../../src/io/identity.cpp), [docs/annotations.md](../../../../annotations.md) |

## B0004

[Lines 38–38](../../../../../tests/unit/annotation_admission_test.cpp#L38); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L38:sha256:c7bfe2f3de133d78a2bc8bb1c4a08450563986ee8254facee698e1dcc57e8162
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in annotation_admission_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/annotation_admission_test.cpp](../../../../../tests/unit/annotation_admission_test.cpp), [docs/sql_admission.md](../../../../sql_admission.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 39–42](../../../../../tests/unit/annotation_admission_test.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Runs the annotation admission assertions as a small standalone test entry point. |
| inputs / outputs | No arguments; invokes run, prints success on return, and catches std::exception. |
| invariants | The entry point covers only the source-defined invalid-policy matrix. |
| ownership | All state is local to run and released on return. |
| failure | Caught exceptions are printed and produce nonzero status. |
| cost | One run of run(); no performance metric is collected. |
| Design | [tests/unit/annotation_admission_test.cpp](../../../../../tests/unit/annotation_admission_test.cpp), [docs/annotations.md](../../../../annotations.md) |
