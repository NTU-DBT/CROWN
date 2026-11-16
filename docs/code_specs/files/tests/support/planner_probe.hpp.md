# `tests/support/planner_probe.hpp` — block usage map

[Source](../../../../../tests/support/planner_probe.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `10da0d74a57ca2cced15b24326c9df07e5e0e90a8373b486fcad392fdff3af9f`. 7 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../tests/support/planner_probe.hpp#L1) | Imports dependencies; guards repeated header inclusion; controls preprocessing; declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |

## B0001

[Lines 1–7](../../../../../tests/support/planner_probe.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:10da0d74a57ca2cced15b24326c9df07e5e0e90a8373b486fcad392fdff3af9f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare planner_probe.hpp: include "crown/planner/oracle.hpp"; declare helper function signatures without invoking them; select the recorded test ABI/preprocessor branch. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. Function prototypes declare the shown reference/helper API; invocation and any default-argument evaluation occur at the caller. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/support/planner_probe.hpp](../../../../../tests/support/planner_probe.hpp), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/code_review.md](../../../../code_review.md) |
