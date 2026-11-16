# `src/planner/ranking_payload.hpp` — block usage map

[Source](../../../../../src/planner/ranking_payload.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Rank or select within a checked candidate family using exact binding, explicit evidence and bounded local score policies.

Snapshot SHA-256: `bd81a25cc30e4c7874827da161493c73858650a2d603fb49536d868e5224f74a`. 13 lines partitioned into 1 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [ranking](../../../subsystem_contracts.md#ranking). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/ranking.md](../../../../ranking.md), [docs/selection.md](../../../../selection.md), [docs/selection_binding.md](../../../../selection_binding.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [docs/selection_accounting.md](../../../../selection_accounting.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../src/planner/ranking_payload.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Logical owned component payload, not allocator capacity or a peak bound. · [reviewed contract](#b0001) |

## B0001

[Lines 1–13](../../../../../src/planner/ranking_payload.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void plan_source_payload(const MinimumHeightCandidate&,const CompiledProgram&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit native candidate-source logical components. |
| inputs / outputs | Synchronous declaration of the matching payload visitor. |
| invariants | Logical owned component model, not allocator capacity/peak bound; each newly lowered candidate plan is admitted separately. |
| ownership | Borrows immutable model and mutable Budget; retains no model pointer after call. |
| failure | Budget/allocator failures propagate to the single ranking boundary. |
| cost | Delegated full visitor cost; no independent traversal in this declaration. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
void plan_source_payload(const MinimumHeightCandidate&,const PhysicalPlan&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit legacy DTO candidate-source logical components. |
| inputs / outputs | Synchronous declaration of the matching payload visitor. |
| invariants | Logical owned component model, not allocator capacity/peak bound; each newly lowered candidate plan is admitted separately. |
| ownership | Borrows immutable model and mutable Budget; retains no model pointer after call. |
| failure | Budget/allocator failures propagate to the single ranking boundary. |
| cost | Delegated full visitor cost; no independent traversal in this declaration. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
void plan_compiled_payload(const PhysicalPlan&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit legacy compiled program logical components. |
| inputs / outputs | Synchronous declaration of the matching payload visitor. |
| invariants | Logical owned component model, not allocator capacity/peak bound; each newly lowered candidate plan is admitted separately. |
| ownership | Borrows immutable model and mutable Budget; retains no model pointer after call. |
| failure | Budget/allocator failures propagate to the single ranking boundary. |
| cost | Delegated full visitor cost; no independent traversal in this declaration. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
void plan_compiled_payload(const CompiledProgram&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit native compiled program logical components. |
| inputs / outputs | Synchronous declaration of the matching payload visitor. |
| invariants | Logical owned component model, not allocator capacity/peak bound; each newly lowered candidate plan is admitted separately. |
| ownership | Borrows immutable model and mutable Budget; retains no model pointer after call. |
| failure | Budget/allocator failures propagate to the single ranking boundary. |
| cost | Delegated full visitor cost; no independent traversal in this declaration. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |

```text
void plan_identity_payload(const program::QueryIdentity&
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit native query identity logical components. |
| inputs / outputs | Synchronous declaration of the matching payload visitor. |
| invariants | Logical owned component model, not allocator capacity/peak bound; each newly lowered candidate plan is admitted separately. |
| ownership | Borrows immutable model and mutable Budget; retains no model pointer after call. |
| failure | Budget/allocator failures propagate to the single ranking boundary. |
| cost | Delegated full visitor cost; no independent traversal in this declaration. |
| Design | [docs/ranking.md](../../../../ranking.md), [docs/query_memory.md](../../../../query_memory.md) |
