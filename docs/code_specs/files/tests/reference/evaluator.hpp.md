# `tests/reference/evaluator.hpp` — block usage map

[Source](../../../../../tests/reference/evaluator.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `2f2e947ea5dcdec6a607b9f1a3aa96b0aad3ceb194a45b42c24422a843a4f24a`. 22 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../tests/reference/evaluator.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // A slow, materializing relational definition. No planner/support/cursor helpers. · [reviewed contract](#b0001) |
| [B0002 · 9–21](../../../../../tests/reference/evaluator.hpp#L9) | Type/record definition: class Session | returns sequence_; database_ · [reviewed contract](#b0002) |
| [B0003 · 22–22](../../../../../tests/reference/evaluator.hpp#L22) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::reference · [reviewed contract](#b0003) |

## B0001

[Lines 1–8](../../../../../tests/reference/evaluator.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:4e4fa8d9a777d9e1aefeed00a33cfdad4cbf81549d33ec2444c07bbd4e12a13c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare evaluator.hpp: include "crown/ir/model.hpp"; declare helper function signatures without invoking them. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. Function prototypes declare the shown reference/helper API; invocation and any default-argument evaluation occur at the caller. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/semantics.md](../../../../semantics.md), [docs/code_review.md](../../../../code_review.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0002

[Lines 9–21](../../../../../tests/reference/evaluator.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class Session {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Expose owning snapshot/update semantics for the simple reference engine. |
| inputs / outputs | Constructor owns Catalog/Query/Database; snapshot returns an owning Relation, apply returns an owning committed epoch, sequence returns fixed data and database returns a const borrowed reference. |
| invariants | This session is an exact set-CQ baseline and oracle-CLI component, not the accounted/native incremental runtime. Only a successful apply publishes database/sequence. |
| ownership | The database() reference is valid only while this owner lives and may observe subsequent successful replacement; never retain a reference obtained from a temporary Session. |
| failure | Validation/evaluation/container failures are throwing operations; const scalar/reference accessors are noexcept and perform no validation. |
| cost | Owns a full ordinary database; snapshot reevaluates and apply copies/recomputes whole state. Getter cost is constant, not the mutation cost. |
| Design | [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/semantics.md](../../../../semantics.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |

## B0003

[Lines 22–22](../../../../../tests/reference/evaluator.hpp#L22); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L22-L22:sha256:e6b42e4915271f267594118fd022698431af47758d71d1b08d7db51a0d7f1921
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in evaluator.hpp: namespace crown::reference. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/reference/evaluator.hpp](../../../../../tests/reference/evaluator.hpp), [docs/semantics.md](../../../../semantics.md), [docs/code_review.md](../../../../code_review.md), [tests/reference/evaluator.cpp](../../../../../tests/reference/evaluator.cpp) |
