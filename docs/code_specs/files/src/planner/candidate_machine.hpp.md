# `src/planner/candidate_machine.hpp` — block usage map

[Source](../../../../../src/planner/candidate_machine.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Search the finite canonical tree space and retain resumable evidence for exact minimum-height claims.

Snapshot SHA-256: `8877f5d068cc6a42f463f4975301707b16752a7dab21fda951c79adf5b26b822`. 96 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [search](../../../subsystem_contracts.md#search). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/tree_oracle.md](../../../../tree_oracle.md), [docs/planner_continuations.md](../../../../planner_continuations.md), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../src/planner/candidate_machine.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 12–12](../../../../../src/planner/candidate_machine.hpp#L12) | Type/record definition: enum class GeneratorEvent |  · [reviewed contract](#b0002) |
| [B0003 · 13–13](../../../../../src/planner/candidate_machine.hpp#L13) | Type/record definition: enum class GeneratorStop |  · [reviewed contract](#b0003) |
| [B0004 · 14–18](../../../../../src/planner/candidate_machine.hpp#L14) | Type/record definition: struct Step |  · [reviewed contract](#b0004) |
| [B0005 · 19–22](../../../../../src/planner/candidate_machine.hpp#L19) | Type/record definition: struct ContentLimits |  · [reviewed contract](#b0005) |
| [B0006 · 23–23](../../../../../src/planner/candidate_machine.hpp#L23) | Explanatory comments or spacing. | source comment (unverified): // Every content preparation failure uses this type. bad_alloc is not translated. · [reviewed contract](#b0006) |
| [B0007 · 24–28](../../../../../src/planner/candidate_machine.hpp#L24) | Type/record definition: struct ContentStop final : std::exception | returns @; source comment (unverified): // Every content preparation failure uses this type. bad_alloc is not translated. · [reviewed contract](#b0007) |
| [B0008 · 29–33](../../../../../src/planner/candidate_machine.hpp#L29) | Explanatory comments or spacing. | source comment (unverified): // Cumulative logical construction only; never allocator-byte accounting. · [reviewed contract](#b0008) |
| [B0009 · 34–49](../../../../../src/planner/candidate_machine.hpp#L34) | Type/record definition: class ContentBudget | source comment (unverified): // Cumulative logical construction only; never allocator-byte accounting. · [reviewed contract](#b0009) |
| [B0010 · 50–51](../../../../../src/planner/candidate_machine.hpp#L50) | Explanatory comments or spacing. | source comment (unverified): // Committed enumeration activity only; draft publication is not P02 authority. · [reviewed contract](#b0010) |
| [B0011 · 52–59](../../../../../src/planner/candidate_machine.hpp#L52) | Type/record definition: struct GeneratorStatistics | source comment (unverified): // Committed enumeration activity only; draft publication is not P02 authority. · [reviewed contract](#b0011) |
| [B0012 · 60–95](../../../../../src/planner/candidate_machine.hpp#L60) | declares types or opens a type body; declares callable signatures; declares values/defaults or compile-time conditions. | source comment (unverified): // Enumerates labeled roots/parents, then dynamic native-anchor subset digits. · [reviewed contract](#b0012) |
| [B0013 · 96–96](../../../../../src/planner/candidate_machine.hpp#L96) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::candidate_detail · [reviewed contract](#b0013) |

## B0001

[Lines 1–11](../../../../../src/planner/candidate_machine.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:ac748eadc0b3f11efb4a7070137284a67a741a86e734d5332404aba46c98c607
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use #pragma once to suppress repeated header processing within a translation unit. Make #include "continuation_machine.hpp", #include &lt;cstdint&gt;, #include &lt;exception&gt;, #include &lt;memory&gt;, #include &lt;optional&gt; available to src/planner/candidate_machine.hpp; open crown::planner::candidate_detail. |
| inputs / outputs | Preprocessor directives resolve compile-time declarations. This block has no runtime call inputs or result. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | No runtime object is owned by the include or scope directives. Any state belongs to the types and functions declared after them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Adds preprocessing, parsing, and any later template-instantiation work in this translation unit. It adds no runtime timer, counter, branch, or allocation. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0002

[Lines 12–12](../../../../../src/planner/candidate_machine.hpp#L12); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class GeneratorEvent {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Separate yielded draft from actual finite exhaustion. |
| inputs / outputs | advanced/draft_ready/exhausted/stopped. |
| invariants | A draft is an unchecked proposal; it must be acknowledged before generation proceeds. |
| ownership | Value only. |
| failure | Stopped reason is separate GeneratorStop; cancellation may use none. |
| cost | Constant storage. |
| Design | [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0003

[Lines 13–13](../../../../../src/planner/candidate_machine.hpp#L13); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class GeneratorStop {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Represent generator depth/content/overflow stops. |
| inputs / outputs | none, depth_limit, record_limit, cell_limit, counter_overflow. |
| invariants | None does not signify feasible/infeasible; overflow is terminal in the provider. |
| ownership | Scalar protocol. |
| failure | bad_alloc escapes rather than being translated into this enum. |
| cost | Constant storage. |
| Design | [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0004

[Lines 14–18](../../../../../src/planner/candidate_machine.hpp#L14); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Step {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Return generator progress and blocked logical depth. |
| inputs / outputs | Default advanced event plus reason/requested_depth. |
| invariants | Requested push is not an owned depth frame. |
| ownership | Fixed values copied to caller. |
| failure | No allocation to construct result. |
| cost | Constant-size return. |
| Design | [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp) |

## B0005

[Lines 19–22](../../../../../src/planner/candidate_machine.hpp#L19); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ContentLimits {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Configure cumulative logical construction record/cell ceilings. |
| inputs / outputs | Two optional uint64 bounds, absent means unbounded. |
| invariants | Counts are cumulative even when drafts are discarded/consumed; they do not count allocator capacity. |
| ownership | Value copied into shared ContentBudget. |
| failure | Limits do not validate source or grant proof authority. |
| cost | Constant storage. |
| Design | [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0006

[Lines 23–23](../../../../../src/planner/candidate_machine.hpp#L23); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L23-L23:sha256:35182b94edde48966e8a0f9dd10d7ebcaba45a491ab01af4124aaade13b45c1b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ContentStop: Every content preparation failure uses this type. bad_alloc is not translated. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ContentStop; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ContentStop come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0007

[Lines 24–28](../../../../../src/planner/candidate_machine.hpp#L24); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ContentStop final : std::exception {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry a resource reason out of pending construction operations. |
| inputs / outputs | GeneratorStop and fixed what() text. |
| invariants | Every budget preparation failure uses this type; standard allocation failure remains bad_alloc. |
| ownership | Owns enum; returns static text. |
| failure | Constructor/what noexcept; no dynamic error message. |
| cost | Constant-size exception payload. |
| Design | [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp) |

## B0008

[Lines 29–33](../../../../../src/planner/candidate_machine.hpp#L29); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L33:sha256:809010f7be8bca945b95615aeeae5701a791315e13de908f346dd013414142be
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ContentBudget: Cumulative logical construction only; never allocator-byte accounting. Failed allocations commit no charge; discarded/consumed content is not refunded. Operations may relocate vectors or compare sets, so a cell is not a fixed physical-time unit. Admission binding copies, P02 scratch, capacity, allocator metadata, scalar/string widths and caller-retained history are excluded. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ContentBudget; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ContentBudget come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0009

[Lines 34–49](../../../../../src/planner/candidate_machine.hpp#L34); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ContentBudget {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Serialize preflight/commit accounting shared by generator, key machine and facade. |
| inputs / outputs | prepare/commit, monotone raises and scalar totals/limits. |
| invariants | Matching successful prepare precedes allocation and commit, with no intervening budget mutation. Discarded content is not refunded. |
| ownership | Shared mutable budget under exclusive provider calls. |
| failure | prepare throws ContentStop; commit unchecked/noexcept under precondition; invalid raises return false. |
| cost | Constant arithmetic per charge; no allocator-byte or hard-time claim. |
| Design | [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [src/planner/candidate_key.hpp](../../../../../src/planner/candidate_key.hpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0010

[Lines 50–51](../../../../../src/planner/candidate_machine.hpp#L50); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L50-L51:sha256:83f93a30be86a2720af05244a9b32baf1882a2dc68c74f9b7ff0e9663b17658b
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for GeneratorStatistics: Committed enumeration activity only; draft publication is not P02 authority. drafts_consumed &lt;= guarded drafts_ready; blocked pushes own no new frame. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies GeneratorStatistics; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for GeneratorStatistics come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |

## B0011

[Lines 52–59](../../../../../src/planner/candidate_machine.hpp#L52); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct GeneratorStatistics {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Track committed generator steps/topologies/drafts and peak owned depth. |
| inputs / outputs | Five uint64 counters and peak_depth. |
| invariants | drafts_consumed never exceeds guarded drafts_ready; blocked requested pushes do not inflate peak. |
| ownership | Value owned by generator, exposed by borrowed const reference. |
| failure | Guarded increments stop at exhaustion; acknowledgement relies on one live ready draft. |
| cost | Constant storage/access. |
| Design | [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md) |

## B0012

[Lines 60–95](../../../../../src/planner/candidate_machine.hpp#L60); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class NormalFormGenerator {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a retained enumeration of labeled parent trees and dynamic generalized-scope subset tuples. |
| inputs / outputs | Validated immutable binding, target height and shared budget; step/draft/consume/statistics/depth/cancel. |
| invariants | Target is a filter, not proof. g ranges 0..m-1, no generalized unary/leaf and no generalized below native. Subsets of native scopes cover local normal form; P02 remains mandatory. |
| ownership | Unique pimpl owns source/budget, dynamic digits, DFS stack, control task and current/ready tree. |
| failure | Null inputs reject. Allocation propagates with saved operation; content stops report reason; ready drafts block further advancement until consume. |
| cost | Topology enumeration exponential; naive DFS scans all labels per frame. Dynamic bits avoid fixed-width masks or eager power sets; logical content excludes capacity and widths. |
| Design | [src/planner/candidate_generator.cpp](../../../../../src/planner/candidate_generator.cpp), [src/planner/candidates.cpp](../../../../../src/planner/candidates.cpp), [docs/candidate_alternatives.md](../../../../candidate_alternatives.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0013

[Lines 96–96](../../../../../src/planner/candidate_machine.hpp#L96); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L96-L96:sha256:3ea00d71de03416591bb9844776a36ebb57b0e6adb064ec801803bb4199e2fb5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner::candidate_detail. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/candidate_machine.hpp](../../../../../src/planner/candidate_machine.hpp), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/planner_continuations.md](../../../../planner_continuations.md) |
