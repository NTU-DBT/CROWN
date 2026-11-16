# `src/runtime/weighted_detail.hpp` — block usage map

[Source](../../../../../src/runtime/weighted_detail.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Maintain exact full-subtree messages and local visible factors, then enumerate projected core tuples with multiplicities.

Snapshot SHA-256: `2c75df28ed344244f7470863dc4f0e0b9c3ce48a7972484a618c87b2fffaf604`. 71 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [weighted](../../../subsystem_contracts.md#weighted). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/annotations.md](../../../../annotations.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–13](../../../../../src/runtime/weighted_detail.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares aliases; declares types or opens a type body; declares values/defaults or compile-time conditions. | source comment (unverified): // Internal shared state for maintenance and committed cursor translation units. · [reviewed contract](#b0001) |
| [B0002 · 14–16](../../../../../src/runtime/weighted_detail.hpp#L14) | Callable definition: inline void require(bool condition, std::string_view code, std::string_view message) | calls Error, std::string; guard inline void require(bool condition, std::string_view code, std::string_view message) { · [reviewed contract](#b0002) |
| [B0003 · 17–25](../../../../../src/runtime/weighted_detail.hpp#L17) | Type/record definition: struct Node |  · [reviewed contract](#b0003) |
| [B0004 · 26–28](../../../../../src/runtime/weighted_detail.hpp#L26) | Explanatory comments or spacing. | source comment (unverified): // The exact existing iterative backtracking kernel, shared by the two native · [reviewed contract](#b0004) |
| [B0005 · 29–42](../../../../../src/runtime/weighted_detail.hpp#L29) | Callable definition: template&lt;class Walker, class Steps&gt; bool advance_visible(Walker& walker, const Steps& steps) | calls size, select, close_frame; returns true; false; 1 loop sites; source comment (unverified): // The exact existing iterative backtracking kernel, shared by the two native · [reviewed contract](#b0005) |
| [B0006 · 43–71](../../../../../src/runtime/weighted_detail.hpp#L43) | declares namespace scope; declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // namespace crown::runtime::weighted_detail · [reviewed contract](#b0006) |

## B0001

[Lines 1–13](../../../../../src/runtime/weighted_detail.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
#pragma once
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share the private weighted numeric state between maintenance and cursor translation units. |
| inputs / outputs | Weighted/storage-work/error dependencies and accounted Vector/Map aliases. |
| invariants | No second owner registry, allocator authority or exception framework. |
| ownership | Container instances use the existing account/attribution supplied at construction. |
| failure | Compile-time dependencies only; operation errors propagate normally. |
| cost | No runtime initialization; map operations have their ordinary ordered-container costs. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0002

[Lines 14–16](../../../../../src/runtime/weighted_detail.hpp#L14); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
inline void require(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the existing formatted API error boundary for weighted contract checks. |
| inputs / outputs | Condition plus code/message; successful checks return, false throws crown::Error. |
| invariants | No retry, logging, fallback or nested translation is introduced. |
| ownership | Success borrows string_views; failure creates Error's owning presentation strings. |
| failure | Original exception propagates to the caller's existing stage boundary. |
| cost | Fixed branch on success; only failure formats/allocates diagnostics under documented presentation boundaries. |
| Design | [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/query_memory.md](../../../../query_memory.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [Refactor.md §10.2; W05 foundation only](../../../../../Refactor.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0003

[Lines 17–25](../../../../../src/runtime/weighted_detail.hpp#L17); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Node {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own one node numeric metadata and immutable child-to-edge lookup. |
| inputs / outputs | Tuple IDs map to inline records, full separator sums and distinct visible-factor sums. Child slots map to immutable edges; factor_begin/end address the owner flat outside-slot list. |
| invariants | Metadata entries correspond to matching storage memberships. |
| ownership | All maps/child lookup use original account and node attribution. |
| failure | Allocation errors propagate into epoch rollback; lifetime scan is used at detach/restore. |
| cost | Ordered map O(log rows); no duplicated child array per numeric edit. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

## B0004

[Lines 26–28](../../../../../src/runtime/weighted_detail.hpp#L26); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L26-L28:sha256:f8a0668337a239971cb8738b13acff3b470668acf50856ce0c6bc92cf207cb84
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Usage note immediately before \`template&lt;class Walker, class Steps&gt; bool advance_visible(Walker& walker, const Steps& steps)\`: The exact existing iterative backtracking kernel, shared by the two native walkers. It opens no engine/reader/grant; select/close remain concrete methods. |
| inputs / outputs | This comment introduces no parameter, field or return value. It documents the adjacent construct beginning at src/runtime/weighted_detail.hpp:L29; use that declaration for the actual input/output shape. |
| invariants | The source note states: The exact existing iterative backtracking kernel, shared by the two native walkers. It opens no engine/reader/grant; select/close remain concrete methods. It is prose guidance; the adjacent implementation is the place to check enforcement. |
| ownership | The note states no ownership relation and retains no value. The adjacent declaration or function controls the actual owner and borrowed-view lifetime. |
| failure | This comment adds no branch or handler. Any failure behavior remains in the adjacent callable implementation and its callers. |
| cost | The prose adds no executable work. Runtime cost belongs to the adjacent operation; the note does not establish a measured or global complexity bound. |
| Design | [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_specs/subsystem_contracts.md](../../../subsystem_contracts.md) |

## B0005

[Lines 29–42](../../../../../src/runtime/weighted_detail.hpp#L29); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
template<class Walker, class Steps>
bool advance_visible
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Share the existing iterative backtracking loop between two concrete walkers. |
| inputs / outputs | Walker position/resume/frames and checked ordered steps produce one complete selected assignment or exhaustion. |
| invariants | Caller excludes empty frames; select and close retain caller-specific semantics. |
| ownership | Borrows existing frames and steps; creates no reader, allocator or grant. |
| failure | Caller select/close exceptions propagate to its existing boundary. |
| cost | Actual backtracking transitions; no recursion, virtual dispatch, callbacks or row history. |
| Design | [docs/weighted_deltas.md](../../../../weighted_deltas.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [Refactor.md §10.2 and W06](../../../../../Refactor.md), [P1 arXiv:2301.04003v2 §7.3 aggregation context; telescope, lifetime, grants and transactions are local engineering](https://arxiv.org/pdf/2301.04003v2) |

## B0006

[Lines 43–71](../../../../../src/runtime/weighted_detail.hpp#L43); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct WeightedRuntime::Impl
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own admitted direct-CQ shape, native storage and committed weighted state. |
| inputs / outputs | Freeze a checked shape in a fresh standalone account or supplied receiving account; compile child/edge/outside-slot mappings once. |
| invariants | Normalized SQL rejects. Explicit empty root key, separate weighted binding and serialized callers remain. A receiver's actual cap replaces the requested standalone cap; no independent count mirror. |
| ownership | One context/account funds the newly frozen program, native storage and stable metadata. The compiler artifact can be foreign or funded by that same account; imported runtime metadata owns its lifetime. |
| failure | Admission failures publish no runtime; ordinary reads reject a private epoch. |
| cost | Admission O(plan nodes+edges plus storage capacities), including one flat outside-slot list. No list allocation when no outside edges; root summary reads at most one message. |
| Design | [Refactor.md §10.2 and W02/W03](../../../../../Refactor.md), [docs/weighted_messages.md](../../../../weighted_messages.md), [docs/weighted_enumeration.md](../../../../weighted_enumeration.md), [P1 arXiv:2301.04003v2 §7.3 equations(10)–(14); local engineering contracts are distinguished from paper theorems](https://arxiv.org/pdf/2301.04003v2), [docs/weighted_deltas.md](../../../../weighted_deltas.md) |

```text
} // namespace crown::runtime::weighted_detail namespace crown::runtime {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Declare a second Impl constructor for only already materialized tables and a private base. |
| inputs / outputs | The overload adds AccountedPlanStorage and initial_sequence parameters to the hidden Impl declaration. |
| invariants | Only friend bridge calls it for a fresh unpublished load; the ordinary constructor remains. No \`sequence\` setter or public factory is exposed. |
| ownership | Declaration describes move-owned table/context/program args. |
| failure | Access/type errors are compile-time; construction errors are handled by the cold factory. |
| cost | No runtime cost from declaration; base is an inline scalar. |
| Design | [src/runtime/weighted_detail.hpp](../../../../../src/runtime/weighted_detail.hpp), [src/runtime/weighted.cpp](../../../../../src/runtime/weighted.cpp) |
