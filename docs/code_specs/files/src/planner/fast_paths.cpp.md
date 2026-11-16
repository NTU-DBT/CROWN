# `src/planner/fast_paths.cpp` — block usage map

[Source](../../../../../src/planner/fast_paths.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Retain source-list compatibility while fast-path continuation implementation is owned by search_session.cpp.

Snapshot SHA-256: `6ffa159d0d9d8cf147fba1b07eea53b51919e9f9fcdb5e2d079e540da1e260af`. 5 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [search](../../../subsystem_contracts.md#search). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../src/planner/fast_paths.cpp#L1) | Imports dependencies. | source comment (unverified): // Compatibility source-list unit only; P04 implementation and its costs live in exact.cpp. · [reviewed contract](#b0001) |

## B0001

[Lines 1–5](../../../../../src/planner/fast_paths.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#include "fast_paths.hpp"
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Keep the historical fast-path translation unit in the existing source list. |
| inputs / outputs | Includes the compatibility header; no fast-path entry point is defined here. |
| invariants | P04 algorithms live in ProducerMachine::Impl in exact.cpp and use the same owned operation scheduler. |
| ownership | This unit owns no runtime search state. |
| failure | No runtime error path exists in this unit; compile-time include/source-list issues remain ordinary build errors. |
| cost | No runtime algorithm is emitted here; actual fast-path work and storage belong to exact.cpp. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [docs/planner_proofs.md §P04 hierarchy, component and symmetry rules](../../../../planner_proofs.md), [CMakeLists.txt](../../../../../CMakeLists.txt), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp) |
