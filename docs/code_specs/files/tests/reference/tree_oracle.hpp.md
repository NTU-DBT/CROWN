# `tests/reference/tree_oracle.hpp` — block usage map

[Source](../../../../../tests/reference/tree_oracle.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `50636a3355d9181f761230a8a0def5cb12222b4a954469b2eaf5a9ea9b58e10b`. 10 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../tests/reference/tree_oracle.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares values/defaults or compile-time conditions. | source comment (unverified): // Deliberately literal §5.4 baseline: labelled topologies and the full union · [reviewed contract](#b0001) |

## B0001

[Lines 1–10](../../../../../tests/reference/tree_oracle.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:50636a3355d9181f761230a8a0def5cb12222b4a954469b2eaf5a9ea9b58e10b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare tree_oracle.hpp: include "crown/planner/oracle.hpp"; declare helper function signatures without invoking them. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. Function prototypes declare the shown reference/helper API; invocation and any default-argument evaluation occur at the caller. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/reference/tree_oracle.hpp](../../../../../tests/reference/tree_oracle.hpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md), [tests/reference/tree_oracle.cpp](../../../../../tests/reference/tree_oracle.cpp) |
