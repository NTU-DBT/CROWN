# `tests/unit/reoptimization_clock_counter_test.cpp` — block usage map

[Source](../../../../../tests/unit/reoptimization_clock_counter_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `23baaf920c2fdacdf2f2af9accc0826325cc91f29c59b64c254541e2fbe87873`. 76 lines partitioned into 8 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../tests/unit/reoptimization_clock_counter_test.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 8–12](../../../../../tests/unit/reoptimization_clock_counter_test.cpp#L8) | Type/record definition: struct ClockCounterTestAccess |  · [reviewed contract](#b0002) |
| [B0003 · 13–20](../../../../../tests/unit/reoptimization_clock_counter_test.cpp#L13) | declares namespace scope; declares aliases; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0003) |
| [B0004 · 21–26](../../../../../tests/unit/reoptimization_clock_counter_test.cpp#L21) | Callable definition: Relation answers(DeltaRuntime& source) | calls core_results, next_native, insert, storage::export_row; returns result; growth insert; 1 loop sites · [reviewed contract](#b0004) |
| [B0005 · 27–27](../../../../../tests/unit/reoptimization_clock_counter_test.cpp#L27) | Explanatory comments or spacing. |  |
| [B0006 · 28–65](../../../../../tests/unit/reoptimization_clock_counter_test.cpp#L28) | Callable definition: void cancelled_clock_does_no_more_work(bool verify) | calls c05_independent::candidates, candidate, check, has_value; guard check(candidate.has_value(),"counter fixture has no checked candidate");; growth insert · [reviewed contract](#b0006) |
| [B0007 · 66–67](../../../../../tests/unit/reoptimization_clock_counter_test.cpp#L66) | Closes surrounding scope/type. |  · [reviewed contract](#b0007) |
| [B0008 · 68–76](../../../../../tests/unit/reoptimization_clock_counter_test.cpp#L68) | Callable definition: int main() | calls cancelled_clock_does_no_more_work, what; returns 1 · [reviewed contract](#b0008) |

## B0001

[Lines 1–7](../../../../../tests/unit/reoptimization_clock_counter_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:11be1c96bd96f906d9764d426a4f13b4eeb0fd78e4a0005f27ba2d6a62d4d0b4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare reoptimization_clock_counter_test.cpp: include "reoptimization_detail.hpp", "selection_independent_fixture.hpp", &lt;array&gt;, &lt;iostream&gt;, &lt;limits&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/reoptimization_clock_counter_test.cpp](../../../../../tests/unit/reoptimization_clock_counter_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–12](../../../../../tests/unit/reoptimization_clock_counter_test.cpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ClockCounterTestAccess {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Seed the exact private clock counter boundary. |
| inputs / outputs | Test-only helper sets clock_reads to uint64 max on a real State. |
| invariants | Does not fabricate proof, target, source, phase or tree; construction uses real checked candidate APIs. |
| ownership | Borrows State and stores nothing. |
| failure | Noexcept fixed assignment. |
| cost | Constant test-only work; no production fields. |
| Design | [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

```text
static void saturate(State& state) noexcept
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set only the diagnostic counter to its overflow edge. |
| inputs / outputs | Live test State receives uint64 max. |
| invariants | All native/source/candidate state remains constructed normally. |
| ownership | Borrowed reference, no retention. |
| failure | Noexcept assignment. |
| cost | One test-only scalar write. |
| Design | [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0003

[Lines 13–20](../../../../../tests/unit/reoptimization_clock_counter_test.cpp#L13); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L20:sha256:9c045a71175fbfdb2191a9bddd3fa1135552c4b9525bc144f40e030a568219e7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare reoptimization_clock_counter_test.cpp: bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/reoptimization_clock_counter_test.cpp](../../../../../tests/unit/reoptimization_clock_counter_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 21–26](../../../../../tests/unit/reoptimization_clock_counter_test.cpp#L21); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
Relation answers(DeltaRuntime& source)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Read old-owner results for independent preservation checks. |
| inputs / outputs | Drains a real core cursor into owning public Relation. |
| invariants | Native read lease is exhausted/released before candidate stage or next input. |
| ownership | Local cursor retains source; returned Rows own exported values. |
| failure | Cursor/export/set allocation failures reach the test process catch. |
| cost | Explicit test result enumeration/export, outside measured account-allocation interval. |
| Design | [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0006

[Lines 28–65](../../../../../tests/unit/reoptimization_clock_counter_test.cpp#L28); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void cancelled_clock_does_no_more_work(bool verify)
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reproduce cancellation lifecycle against a nonempty real old owner. |
| inputs / outputs | Real checked candidate and one-row source; stage or frozen verification runs at saturated clock. |
| invariants | Before-fix staging allocates after cancellation. Fixed branches stop work, leave terminal counter status, preserve old rows/owner/epoch and permit its next input. |
| ownership | Source/State/candidate local owners; borrowed one-cell input remains live synchronously. |
| failure | Assertions throw; pre-fix stage failure prevents reaching the unsafe old verification branch. |
| cost | Cold fixture/proof/build plus two controlled cases. Checks account successful allocations, no claim to measure every global allocator attempt. |
| Design | [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |

## B0007

[Lines 66–67](../../../../../tests/unit/reoptimization_clock_counter_test.cpp#L66); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L66-L67:sha256:938de74be97bf3aba7872a61ba0e42084008c81e8a202a612134c755aaf7fa06
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in reoptimization_clock_counter_test.cpp: namespace (anonymous). |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/reoptimization_clock_counter_test.cpp](../../../../../tests/unit/reoptimization_clock_counter_test.cpp), [docs/reoptimization.md](../../../../reoptimization.md), [docs/code_review.md](../../../../code_review.md) |

## B0008

[Lines 68–76](../../../../../tests/unit/reoptimization_clock_counter_test.cpp#L68); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Run both counter-edge cases and report test outcome. |
| inputs / outputs | Stage case then verification case print one success line or exception message. |
| invariants | Existing body constructs real source/proof; no mocked equivalence result. |
| ownership | Local fixtures own all state. |
| failure | One std::exception presentation boundary returns one. |
| cost | Sum of two explicit regression fixtures; no production instrumentation. |
| Design | [src/runtime/reoptimization.cpp](../../../../../src/runtime/reoptimization.cpp), [src/runtime/reoptimization_detail.hpp](../../../../../src/runtime/reoptimization_detail.hpp), [tests/support/selection_independent_fixture.hpp](../../../../../tests/support/selection_independent_fixture.hpp) |
