# `src/planner/update_pattern_detail.hpp` — block usage map

[Source](../../../../../src/planner/update_pattern_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Recognize structural query classes, check a proposed CROWN tree and lower checked structure into physical metadata.

Snapshot SHA-256: `b14a2d6d9aa4510238aacca2debad5aded4842aa145a7b106b71641ac9b4b4d6`. 19 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [planner](../../../subsystem_contracts.md#planner). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_plans.md](../../../../tree_plans.md), [docs/physical_plans.md](../../../../physical_plans.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/planner/update_pattern_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 9–12](../../../../../src/planner/update_pattern_detail.hpp#L9) | Callable definition: template&lt;class T&gt; resource::OwnerAllocator&lt;T&gt; allocator(const resource::MemoryAccount& account, resource::MemoryPurpose purpose =… | calls ; returns resource::OwnerAllocator&lt;T&gt;(account, purpose, owner) · [reviewed contract](#b0002) |
| [B0003 · 13–19](../../../../../src/planner/update_pattern_detail.hpp#L13) | declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Selection already checked full snapshot/source binding and the declaration · [reviewed contract](#b0003) |

## B0001

[Lines 1–8](../../../../../src/planner/update_pattern_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:f0bf92fa878cf8926a946161fbd0839af541eeae473623430485ac8f1b1c3b3f
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Set up private planner-pattern helpers and reuse ranking’s private budget/failure vocabulary. |
| inputs / outputs | Includes public update-pattern declarations and ranking_detail; aliases rd to planner::ranking::detail. |
| invariants | Internal helpers operate under ranking’s existing limits and failure categories; this layer adds no separate budget authority. |
| ownership | No ownership is created by the namespace/alias setup. |
| failure | No runtime failure path. |
| cost | Compile-time only. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md), [docs/selection.md](../../../../selection.md), [docs/update_patterns.md](../../../../update_patterns.md) |

## B0002

[Lines 9–12](../../../../../src/planner/update_pattern_detail.hpp#L9); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L9-L12:sha256:eb6c87aa318d2e55b1031e20bf6d162a8afbcb871805758bd6e7beac3d713c41
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Create an account-aware allocator for private Analysis vectors. |
| inputs / outputs | T, MemoryAccount, and optional purpose enter; returns OwnerAllocator&lt;T&gt; with capture owner attribution. |
| invariants | The allocator uses the receiving account passed to analysis; it does not alter the original owners of candidate/declaration handles. |
| ownership | Allocation is attributed to capture component 16 and funded by the supplied account. |
| failure | Container allocation can fail at the account cap. |
| cost | O(1) allocator setup; allocation occurs only on growth. |
| Design | [docs/query_memory.md](../../../../query_memory.md), [docs/memory_accounts.md](../../../../memory_accounts.md) |

## B0003

[Lines 13–19](../../../../../src/planner/update_pattern_detail.hpp#L13); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L13-L19:sha256:bcda3edc447a378b83fc64d6f2f9b30844f8a6f5352de415f7492d6f2d269496
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare the checked and already-bound analysis paths, sharing the existing ranking Budget. |
| inputs / outputs | analyse takes source/candidate/declaration and Budget; analyse_bound takes the same handles plus an already-funded Budget after binding checks. |
| invariants | analyse must validate source and full typed candidate binding; analyse_bound relies on that checked invariant and avoids reserializing source per candidate. |
| ownership | Both APIs borrow inputs; returned Analysis copies only existing handles and allocates edges in the supplied account. |
| failure | Private visitors report existing ranking::Stop failures via rd::Failure; public analyse translates them. |
| cost | The bound path avoids repeat source encoding; candidate work follows documented Q/C/R/tree bounds. |
| Design | [docs/update_patterns.md](../../../../update_patterns.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [exact paper reference](https://cs.uwaterloo.ca/~xiaohu/papers/pods25-update.pdf), [docs/selection.md](../../../../selection.md), [docs/update_patterns.md](../../../../update_patterns.md) |
