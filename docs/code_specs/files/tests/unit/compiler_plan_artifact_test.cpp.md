# `tests/unit/compiler_plan_artifact_test.cpp` — block usage map

[Source](../../../../../tests/unit/compiler_plan_artifact_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `186ca8187140cdc17950ff9127b5ab1d45e30e697a45e358762bedb8b8c01138`. 64 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../tests/unit/compiler_plan_artifact_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases. |  · [reviewed contract](#b0001) |
| [B0002 · 8–11](../../../../../tests/unit/compiler_plan_artifact_test.cpp#L8) | Callable definition: template&lt;class Function&gt; void rejected(Function&& function,std::string_view expected) | calls function, check, code, std::runtime_error; guard try{function();}catch(const Error& failure){check(failure.code()==expected,"compiler artifact rejec… · [reviewed contract](#b0002) |
| [B0003 · 12–47](../../../../../tests/unit/compiler_plan_artifact_test.cpp#L12) | Callable definition: void exercise(const PhysicalPlan& plan) | calls resource::MemoryAccount::create, statistics, io::CompilerPlanArtifact::prepare, check; guard check(prepared.program().account().statistics().owner==account.statistics().owner && prepared.stati… · [reviewed contract](#b0003) |
| [B0004 · 48–48](../../../../../tests/unit/compiler_plan_artifact_test.cpp#L48) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0004) |
| [B0005 · 49–64](../../../../../tests/unit/compiler_plan_artifact_test.cpp#L49) | Callable definition: int main() | calls window_checkpoint_test::plan, exercise, frontend::admit_sql, source_catalog; guard check(admitted.status==frontend::AdmissionStatus::admitted,"compiler artifact SQL fixture rejected"…; returns 0; 1; growth insert; 3 loop sites · [reviewed contract](#b0005) |

## B0001

[Lines 1–7](../../../../../tests/unit/compiler_plan_artifact_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:6c46984230f10164fa1371f34a3cb726b6497254248b2280f89118288cd22746
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare compiler_plan_artifact_test.cpp: include "crown/io/compiler_plan_artifact.hpp", "crown/frontend/admission.hpp", "window_checkpoint_test_fixture.hpp"; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/compiler_plan_artifact_test.cpp](../../../../../tests/unit/compiler_plan_artifact_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–11](../../../../../tests/unit/compiler_plan_artifact_test.cpp#L8); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Function> void rejected(Function&& function,std::string_view expected)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check that a plan-artifact action rejects with the expected error code. |
| inputs / outputs | Receives Function&& and expected code; invokes function() and returns on matching Error. |
| invariants | The named forwarding-reference parameter is an lvalue inside the function; the call is not forwarded. |
| ownership | The action remains a caller-owned object referred to for this call; expected code is borrowed. |
| failure | Wrong error or no Error throws std::runtime_error; unrelated exceptions propagate. |
| cost | One action invocation. |
| Design | [tests/unit/compiler_plan_artifact_test.cpp](../../../../../tests/unit/compiler_plan_artifact_test.cpp), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/code_review.md](../../../../code_review.md), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp) |

## B0003

[Lines 12–47](../../../../../tests/unit/compiler_plan_artifact_test.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void exercise(const PhysicalPlan& plan)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise one compiled-plan artifact through preparation, serialization, replay, accounting, and tampering checks. |
| inputs / outputs | Reads a PhysicalPlan; builds a prepared plan/program and compares bytes, hashes, bindings, clocks, and replay outcomes. |
| invariants | The compiler account is 8 MiB and is distinct from the separately supplied receiving execution grant. The two-clock assertion appears on the first prepare only; exported program checks do not repeat it. |
| ownership | Plan is borrowed; artifacts, accounts, storage, and replay objects are owned locally. |
| failure | Failed checks throw std::runtime_error; serialization/replay Errors are asserted at their specific points. |
| cost | Serializes and replays one plan; checks bounded artifact bytes and one explicit indexed-work grant when indexed storage is present. |
| Design | [tests/unit/compiler_plan_artifact_test.cpp](../../../../../tests/unit/compiler_plan_artifact_test.cpp), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/code_review.md](../../../../code_review.md), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp) |

## B0004

[Lines 48–48](../../../../../tests/unit/compiler_plan_artifact_test.cpp#L48); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L48-L48:sha256:533f16bca7d58f44b3103b92e3485d22cfbb34bbad5ea3f3fa3b5a9dcb24ec89
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in compiler_plan_artifact_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/compiler_plan_artifact_test.cpp](../../../../../tests/unit/compiler_plan_artifact_test.cpp), [docs/physical_plans.md](../../../../physical_plans.md), [docs/code_review.md](../../../../code_review.md) |

## B0005

[Lines 49–64](../../../../../tests/unit/compiler_plan_artifact_test.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main()
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run six compiler-artifact profiles. |
| inputs / outputs | Exercises direct plans and two SQL-derived plans with both indexed=false and indexed=true. |
| invariants | The six runs are two backends times one direct plus two SQL profiles; each run owns its compiler account, and indexed execution uses an explicit receiving grant. |
| ownership | Each profile’s plans, accounts, and artifacts are local to exercise; no artifact is retained globally. |
| failure | Catches std::exception, prints the diagnostic, and returns 1. |
| cost | Exactly six exercise calls; each performs bounded serialization/replay checks for its fixture. |
| Design | [tests/unit/compiler_plan_artifact_test.cpp](../../../../../tests/unit/compiler_plan_artifact_test.cpp), [include/crown/io/compiler_plan_artifact.hpp](../../../../../include/crown/io/compiler_plan_artifact.hpp), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp), [docs/code_review.md](../../../../code_review.md), [src/io/compiler_plan_artifact.cpp](../../../../../src/io/compiler_plan_artifact.cpp) |
