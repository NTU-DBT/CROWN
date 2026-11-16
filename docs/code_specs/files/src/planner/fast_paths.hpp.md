# `src/planner/fast_paths.hpp` — block usage map

[Source](../../../../../src/planner/fast_paths.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Retain source-list compatibility while fast-path continuation implementation is owned by search_session.cpp.

Snapshot SHA-256: `1e15390505690d3f51dca554e05d62fbb1c16388a56aa300605f0a7c1e01d30d`. 7 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [search](../../../subsystem_contracts.md#search). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../src/planner/fast_paths.hpp#L1) | guards repeated header inclusion. | source comment (unverified): // Private compatibility header; use ProducerMachine for owned fast analysis and construction. · [reviewed contract](#b0001) |

## B0001

[Lines 1–7](../../../../../src/planner/fast_paths.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preserve the private fast-path include boundary after coroutine consolidation. |
| inputs / outputs | The header declares no callable fast-path API; its comment points maintainers to exact.cpp. |
| invariants | Hierarchy, component and choice construction remain owned producer coroutines, not blocking WorkBudget adapters. |
| ownership | Introduces no runtime owner or borrowed input. |
| failure | No independent runtime status or exception contract exists at this include boundary. |
| cost | Contains documentation and an include guard only; algorithm cost belongs to ProducerMachine. |
| Design | [docs/planner_continuations.md §Grants and retained state](../../../../planner_continuations.md), [docs/planner_proofs.md §P04 hierarchy, component and symmetry rules](../../../../planner_proofs.md), [src/planner/exact.cpp](../../../../../src/planner/exact.cpp) |
