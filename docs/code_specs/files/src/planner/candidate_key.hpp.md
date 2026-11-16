# `src/planner/candidate_key.hpp` — block usage map

[Source](../../../../../src/planner/candidate_key.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Compute canonical candidate identity through a bounded resumable key machine.

Snapshot SHA-256: `92000b505fd7bff6bc210b9735fc2bc7bfa0d3f85ae58362ec847cb8e7d06809`. 71 lines partitioned into 7 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [search](../../../subsystem_contracts.md#search). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../src/planner/candidate_key.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 12–12](../../../../../src/planner/candidate_key.hpp#L12) | Type/record definition: enum class KeyEvent |  · [reviewed contract](#b0002) |
| [B0003 · 13–21](../../../../../src/planner/candidate_key.hpp#L13) | Type/record definition: enum class KeyStop |  · [reviewed contract](#b0003) |
| [B0004 · 22–26](../../../../../src/planner/candidate_key.hpp#L22) | Type/record definition: struct KeyStep |  · [reviewed contract](#b0004) |
| [B0005 · 27–32](../../../../../src/planner/candidate_key.hpp#L27) | Type/record definition: struct KeyStatistics |  · [reviewed contract](#b0005) |
| [B0006 · 33–65](../../../../../src/planner/candidate_key.hpp#L33) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Framed full tokens preserve root, kind, scopes and original occurrences; · [reviewed contract](#b0006) |
| [B0007 · 66–71](../../../../../src/planner/candidate_key.hpp#L66) | declares types or opens a type body. | source comment (unverified): // namespace crown::planner::candidate_detail · [reviewed contract](#b0007) |

## B0001

[Lines 1–11](../../../../../src/planner/candidate_key.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:4096ca473143c4978672ef72c6c5721678c71a59fc60c7cd24de1bcc133ff4dc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use #pragma once to suppress repeated header processing within a translation unit. Make #include "candidate_machine.hpp", #include &lt;cstddef&gt;, #include &lt;cstdint&gt;, #include &lt;memory&gt;, #include &lt;string&gt; available to src/planner/candidate_key.hpp; open crown::planner::candidate_detail. |
| inputs / outputs | Preprocessor directives resolve compile-time declarations. This block has no runtime call inputs or result. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | No runtime object is owned by the include or scope directives. Any state belongs to the types and functions declared after them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Adds preprocessing, parsing, and any later template-instantiation work in this translation unit. It adds no runtime timer, counter, branch, or allocation. |
| Design | [src/planner/candidate_key.hpp](../../../../../src/planner/candidate_key.hpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0002

[Lines 12–12](../../../../../src/planner/candidate_key.hpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class KeyEvent {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate token progress, ready output and resource/invalid stops. |
| inputs / outputs | Enum returned with KeyStep. |
| invariants | Ready means a complete structural token, not a checked query proof or optimum. |
| ownership | Scalar value; token owner stays in machine. |
| failure | Read reason only for stopped event. |
| cost | Fixed enum transfer. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0003

[Lines 13–21](../../../../../src/planner/candidate_key.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class KeyStop {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Name structural-token stop causes without equating them to exhaustion. |
| inputs / outputs | Depth/record/cell/overflow/cancelled/invalid reasons. |
| invariants | Record/cell/depth limits can be raised through their owners; counter overflow is terminal. |
| ownership | Value-only label. |
| failure | A stopped key does not publish partial bytes. |
| cost | Fixed metadata, no diagnostic text allocation. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0004

[Lines 22–26](../../../../../src/planner/candidate_key.hpp#L22); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct KeyStep {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return one structural-key transition outcome. |
| inputs / outputs | Event, reason and requested depth; defaults advanced/none/0. |
| invariants | Depth requests describe traversal allowance, not storage bytes. |
| ownership | Small independent value result. |
| failure | Caller must distinguish key_ready from stopped; no automatic proof implication. |
| cost | Fixed fields, no allocation. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0005

[Lines 27–32](../../../../../src/planner/candidate_key.hpp#L27); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct KeyStatistics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report successful token transitions and character comparisons. |
| inputs / outputs | Completed steps/nodes, compared characters and peak traversal depth. |
| invariants | These are key-worker counters, separate from provider attempted work and content bytes. |
| ownership | Machine-owned value fields; statistics accessor borrows them. |
| failure | Counter exhaustion is checked before the corresponding increment. |
| cost | Fixed metric reads; measured cells exclude allocator/capacity mechanics. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0006

[Lines 33–65](../../../../../src/planner/candidate_key.hpp#L33); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class StructuralKeyMachine {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Canonically encode an already P02-checked tree under retained content/depth limits. |
| inputs / outputs | Shared tree/budget to incremental steps, owning token and borrowed statistics. |
| invariants | Token preserves kind/scopes/native occurrence and rooted grouping, ignores display/vector/child order; caller binding/context is required for global cache identity. |
| ownership | Unique Impl retains immutable tree, budget, coroutine and scratch. Public moved-from accessors return documented defaults. |
| failure | bad_alloc escapes with pending operation; resource stops return typed reasons. Input envelope checks do not replace P02. |
| cost | Framed subtree bytes and insertion-sort comparisons can be quadratic in tree/key size. Capacity, input owners and teardown retain separate actual costs. |
| Design | [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/query_memory.md](../../../../query_memory.md) |

## B0007

[Lines 66–71](../../../../../src/planner/candidate_key.hpp#L66); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L66-L71:sha256:f8376a9d6679b627fb6ad64f65e84beead83e39e41cf86ba68b1d3cb10bf43dc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Complete StructuralKeyMachine with its private Impl forward declaration and unique_ptr PIMPL owner; close the class and candidate_detail namespace. |
| inputs / outputs | This PIMPL member stores the implementation for the public machine facade; its methods forward inputs and results to that implementation. |
| invariants | The facade uniquely owns one Impl; moved-from facades have no implementation and method validity is governed by their definitions. |
| ownership | data_ is a unique_ptr and exclusively owns Impl; the forward declaration keeps implementation details out of this header. |
| failure | Allocating Impl can fail in the out-of-line constructor. The unique_ptr itself adds no exception translation. |
| cost | One unique_ptr handle in the facade; Impl allocation and retained payload costs occur when a machine is constructed. |
| Design | [src/planner/candidate_key.hpp](../../../../../src/planner/candidate_key.hpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |
