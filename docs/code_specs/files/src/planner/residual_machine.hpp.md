# `src/planner/residual_machine.hpp` — block usage map

[Source](../../../../../src/planner/residual_machine.hpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Generate and replay residual-reduction/reconstruction candidates as a structural aid to the exact planner.

Snapshot SHA-256: `af31b0d06fe90662a4837152fd6bef071c961833448893a87cd42ba357fdd1ff`. 103 lines partitioned into 14 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [residual](../../../subsystem_contracts.md#residual). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/residual_candidates.md](../../../../residual_candidates.md), [docs/planner_proofs.md](../../../../planner_proofs.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–8](../../../../../src/planner/residual_machine.hpp#L1) | Imports dependencies; guards repeated header inclusion; declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 9–13](../../../../../src/planner/residual_machine.hpp#L9) | Type/record definition: struct Limited : std::exception | returns @ · [reviewed contract](#b0002) |
| [B0003 · 14–17](../../../../../src/planner/residual_machine.hpp#L14) | Explanatory comments or spacing. | source comment (unverified): // Cumulative logical construction, including discarded drafts and replay. · [reviewed contract](#b0003) |
| [B0004 · 18–29](../../../../../src/planner/residual_machine.hpp#L18) | Type/record definition: struct ConstructionBudget | source comment (unverified): // Cumulative logical construction, including discarded drafts and replay. · [reviewed contract](#b0004) |
| [B0005 · 30–30](../../../../../src/planner/residual_machine.hpp#L30) | Type/record definition: enum class Event |  · [reviewed contract](#b0005) |
| [B0006 · 31–36](../../../../../src/planner/residual_machine.hpp#L31) | Type/record definition: struct Step |  · [reviewed contract](#b0006) |
| [B0007 · 37–40](../../../../../src/planner/residual_machine.hpp#L37) | Type/record definition: struct TraceData |  · [reviewed contract](#b0007) |
| [B0008 · 41–42](../../../../../src/planner/residual_machine.hpp#L41) | Explanatory comments or spacing. | source comment (unverified): // Private payload: exactly one of checked/exact_upper supplies an original- · [reviewed contract](#b0008) |
| [B0009 · 43–49](../../../../../src/planner/residual_machine.hpp#L43) | Type/record definition: struct CandidateData | source comment (unverified): // Private payload: exactly one of checked/exact_upper supplies an original- · [reviewed contract](#b0009) |
| [B0010 · 50–61](../../../../../src/planner/residual_machine.hpp#L50) | Type/record definition: class InducedViewMachine |  · [reviewed contract](#b0010) |
| [B0011 · 62–75](../../../../../src/planner/residual_machine.hpp#L62) | Type/record definition: class ReductionMachine |  · [reviewed contract](#b0011) |
| [B0012 · 76–85](../../../../../src/planner/residual_machine.hpp#L76) | Type/record definition: class TraceReplayMachine |  · [reviewed contract](#b0012) |
| [B0013 · 86–102](../../../../../src/planner/residual_machine.hpp#L86) | Type/record definition: class ReconstructionMachine |  · [reviewed contract](#b0013) |
| [B0014 · 103–103](../../../../../src/planner/residual_machine.hpp#L103) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::residual_detail · [reviewed contract](#b0014) |

## B0001

[Lines 1–8](../../../../../src/planner/residual_machine.hpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L8:sha256:2dcfc2d741479453e27585c5f7a97fad354166b53f2b225ca9fccc857a2acedf
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use #pragma once to suppress repeated header processing within a translation unit. Make #include "crown/planner/residual.hpp", #include "continuation_machine.hpp", #include &lt;exception&gt;, #include &lt;limits&gt; available to src/planner/residual_machine.hpp; open crown::planner::residual_detail. In this span, bind cd = continuation_detail. |
| inputs / outputs | Includes supply declarations; the listed namespace aliases bind names, and any listed constexpr bounds are constant-initialized metadata. These declarations do not run a planner search or validate a query. |
| invariants | Includes, namespace openings, aliases, and forward declarations determine C++ name visibility and type availability; they do not validate planner data or grant proof authority. |
| ownership | Namespace aliases own no runtime object. Any constexpr bounds in this span are fixed scalar metadata; no query owner, mutable counter or allocation grant is created by them. |
| failure | A missing header, incompatible declaration, or ill-formed type use fails during compilation; runtime failures remain in the called code. |
| cost | Preprocessing, name lookup and compile-time constant evaluation; constexpr bounds require no dynamic initialization and can occupy fixed constant storage when used. Included definitions retain their own call/construction costs. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0002

[Lines 9–13](../../../../../src/planner/residual_machine.hpp#L9); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Limited : std::exception {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Carry a fixed residual resource reason through saved operations to the facade. |
| inputs / outputs | Explicit ResidualStopReason constructor and constant what() text. |
| invariants | Limit exceptions do not change mathematical state; overflow is distinguished from resumable ceilings. |
| ownership | Owns one enum and static string pointer only. |
| failure | Construction/what are noexcept; throwing/catching does not allocate a user diagnostic string. |
| cost | Constant-size exception payload. |
| Design | [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0003

[Lines 14–17](../../../../../src/planner/residual_machine.hpp#L14); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L14-L17:sha256:e1fec3dbc192a3d8e8708c5d2d0d0f070a6eca9cac2ee93af2801ae13549f528
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for ConstructionBudget: Cumulative logical construction, including discarded drafts and replay. Call prepare before throwing work and commit only after its success, with exclusive access between them. Capacity, delegated storage and whole binding admission copies are outside this record/cell account (see residual_candidates). Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies ConstructionBudget; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for ConstructionBudget come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0004

[Lines 18–29](../../../../../src/planner/residual_machine.hpp#L18); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct ConstructionBudget {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Preflight and commit cumulative logical residual construction charges. |
| inputs / outputs | limits plus uint64 records/cells; prepare(r,c) checks, commit(r,c) adds. |
| invariants | Every caller must prepare before its throwing construction, then commit only after success; no concurrent mutation between them. Consumed totals never decrement. |
| ownership | Shared among residual workers under one exclusive facade; copied limits are updated on accepted raises. |
| failure | prepare throws Limited on overflow/record/cell ceiling. commit is unchecked/noexcept and relies on successful matching preparation. |
| cost | Constant arithmetic checks/additions; logical charges exclude capacity, whole binding admission, validator scratch and exact storage. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp) |

## B0005

[Lines 30–30](../../../../../src/planner/residual_machine.hpp#L30); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
enum class Event {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report one private worker transition to its parent owner. |
| inputs / outputs | advanced, complete, stopped, need_original_exact, checked_upper or invalid_trace. |
| invariants | checked_upper means final original P02 only in reconstruction; need_original_exact carries no partial infeasibility authority. |
| ownership | Value-only protocol. |
| failure | Does not itself validate or throw; facade/worker interprets events. |
| cost | Constant storage. |
| Design | [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_reduce.cpp](../../../../../src/planner/residual_reduce.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [src/planner/residual_reconstruct.cpp](../../../../../src/planner/residual_reconstruct.cpp) |

## B0006

[Lines 31–36](../../../../../src/planner/residual_machine.hpp#L31); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct Step {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bundle worker status with residual/delegated stop and requested logical depth. |
| inputs / outputs | Defaults to advanced with no reasons/depth. |
| invariants | requested_depth is diagnostic for a blocked operation; exact_reason is meaningful for delegated exact stops. |
| ownership | Owns fixed scalar values. |
| failure | No allocation or exceptions constructing the result. |
| cost | Constant-size copy/return. |
| Design | [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_reduce.cpp](../../../../../src/planner/residual_reduce.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [src/planner/residual_reconstruct.cpp](../../../../../src/planner/residual_reconstruct.cpp) |

## B0007

[Lines 37–40](../../../../../src/planner/residual_machine.hpp#L37); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct TraceData {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Retain one original binding with its independently replayed reduction record. |
| inputs / outputs | Two shared const owners consumed by ResidualTrace. |
| invariants | Facade constructs this only after complete valid TraceReplayMachine report; record cannot be edited through the handle. |
| ownership | Owns binding and trace transitively; survives facade move/cancel/destruction. |
| failure | Aggregate alone provides no verification; private publication path is responsible for nonnull consistent owners. |
| cost | Constant payload pointers plus transitive binding/record storage. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp) |

## B0008

[Lines 41–42](../../../../../src/planner/residual_machine.hpp#L41); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L41-L42:sha256:cfc942b32610b6c56d1a7be9e39c812b9b3f49800d501a76eee9b28fbb7f1926
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Use the adjacent note for CandidateData: Private payload: exactly one of checked/exact_upper supplies an original- query upper witness. Neither a prefix proof nor caller-edited data enters it. Confirm behavior against the declaration and implementation; comment text alone does not enforce or prove it. |
| inputs / outputs | This comment has no inputs or outputs. It accompanies CandidateData; use the adjacent declaration and implementation for the actual values and result. |
| invariants | This is static guidance only. The comment cannot alter state or guarantee that its wording holds. |
| ownership | The note owns no storage and changes no lifetime; ownership and borrowing for CandidateData come from its actual types and implementation. |
| failure | Reading the comment has no runtime failure path. Compile or link errors, exceptions, and resource stops belong to the adjacent code. |
| cost | The comment adds no runtime instructions, allocation, clock read, counter debit, or engine hook; only source-text processing is added. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |

## B0009

[Lines 43–49](../../../../../src/planner/residual_machine.hpp#L43); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CandidateData {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Store original-bound upper authority and construction provenance for one immutable candidate. |
| inputs / outputs | Binding, verified trace, either CheckedUpper or optional ValidatedIncumbent, plus origin. |
| invariants | Private constructors populate exactly one upper representation. Prefix CheckedUpper is never stored here; final P02 uses original binding identity. |
| ownership | Shares immutable owning payloads; no bare tree pointer escapes without an owner. |
| failure | Facade rejects missing/inconsistent original checked data before publication; fields are not a public arbitrary-tree authority factory. |
| cost | Constant owner record; tree/catalog/query/proof content is held transitively. |
| Design | [include/crown/planner/residual.hpp](../../../../../include/crown/planner/residual.hpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [src/planner/residual_reconstruct.cpp](../../../../../src/planner/residual_reconstruct.cpp) |

## B0010

[Lines 50–61](../../../../../src/planner/residual_machine.hpp#L50); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class InducedViewMachine {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own a suspensible dense-query constructor over a trusted ordered occurrence subset. |
| inputs / outputs | Binding, sorted unique original member vector and shared budget; step/context, view and depth access. |
| invariants | Caller supplies valid ascending indexes. Only a fully built view is published; local IDs are ascending originals and all active head positions survive. |
| ownership | Unique pimpl and saved coroutine retain shared input/member/budget owners; result is shared const. |
| failure | Allocations/Limited escape step while its exact pending operation remains retryable. No semantic validation of arbitrary member indexes is provided here. |
| cost | One saved operation per step after lazy start; maps scan original sizes and selected contents. Moves are constant except target cleanup. |
| Design | [src/planner/residual_view.cpp](../../../../../src/planner/residual_view.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0011

[Lines 62–75](../../../../../src/planner/residual_machine.hpp#L62); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ReductionMachine {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own frozen-ear reduction through a checked-shape terminal dense view. |
| inputs / outputs | Original immutable binding/budget; step, phase/statistics/depth and complete trace_record. |
| invariants | Eligibility is frozen before deletion. Producer trace is not replay authority; facade must independently replay it before handle publication. |
| ownership | Unique pimpl, saved coroutine and child view own their complete unfinished state. |
| failure | step propagates resumable allocation/Limited and reports depth stops; destructor cancels frames. Moved-from internal machine methods require a nonnull pimpl. |
| cost | Full original scope construction; repeated hierarchy/pair/deletion scans and retained layer storage, not a linear-time recognition promise. |
| Design | [src/planner/residual_reduce.cpp](../../../../../src/planner/residual_reduce.cpp), [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp) |

## B0012

[Lines 76–85](../../../../../src/planner/residual_machine.hpp#L76); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class TraceReplayMachine {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Independently rederive every frozen trace obligation and terminal mapping. |
| inputs / outputs | Owned binding/claim/budget, stepped context, diagnostic report/depth. |
| invariants | Uses generic suspension only; no reducer, induced-view semantic helper or reconstruction helper. Success concerns trace consistency, not heights. |
| ownership | Unique pimpl retains shared immutable claim and source plus its own scratch. |
| failure | Depth/resource/allocation stops retain the machine; invalid trace finishes with an explicit failing rule. Destructor cancels live frames. |
| cost | Rebuilds scopes/incidences/eligible pairs and scans every claimed record/query cell; may exceed producer work and memory. |
| Design | [src/planner/residual_trace.cpp](../../../../../src/planner/residual_trace.cpp), [src/planner/residual_reduce.cpp](../../../../../src/planner/residual_reduce.cpp), [src/planner/residual_view.cpp](../../../../../src/planner/residual_view.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md) |

## B0013

[Lines 86–102](../../../../../src/planner/residual_machine.hpp#L86); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
class ReconstructionMachine {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own greedy restoration, full P02 checking and prefix exact repair behind one retained execution cursor. |
| inputs / outputs | Binding/replayed trace/shared budget; step/status/upper/origin/exact progress and delegated raises. |
| invariants | Only final original P02 creates exported upper; exhausted/infeasible prefix requests facade original exact search. Greedy proposals are incomplete. |
| ownership | Unique pimpl retains view aliases, private trees, validator and exact owner until release; shares the same construction budget. |
| failure | Resumable allocation/resource stops preserve pending operations. Inner irrecoverable failures propagate to terminal facade failure. Internal moved-from methods require valid pimpl. |
| cost | Potentially many whole-tree drafts/checks and catalog/query admission copies; delegated exact storage/time are separately accounted. |
| Design | [src/planner/residual_reconstruct.cpp](../../../../../src/planner/residual_reconstruct.cpp), [src/planner/residual.cpp](../../../../../src/planner/residual.cpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [src/planner/producer_cursor.hpp](../../../../../src/planner/producer_cursor.hpp), [src/planner/verify.cpp](../../../../../src/planner/verify.cpp) |

## B0014

[Lines 103–103](../../../../../src/planner/residual_machine.hpp#L103); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L103-L103:sha256:3a68bcc8b8d41255077e4487a74e137ae7062dbc0b927d6b564f310ddb7ba239
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | This block close namespace crown::planner::residual_detail. |
| inputs / outputs | A scope delimiter has no call inputs or outputs; it controls which following declarations belong to the C++ namespace, class, or helper scope. |
| invariants | The braces set lexical visibility and type boundaries only. Any attached note is documentation and does not enforce behavior. |
| ownership | The delimiter and note acquire, release, or transfer no runtime object. Member lifetimes come from the enclosed type definitions. |
| failure | An unmatched or misplaced brace fails compilation; this block adds no runtime exception or resource-stop path. |
| cost | No runtime work or allocation is added. The compiler parses the scope boundary and comment. |
| Design | [src/planner/residual_machine.hpp](../../../../../src/planner/residual_machine.hpp), [docs/residual_candidates.md](../../../../residual_candidates.md), [Refactor.md §5.3](../../../../../Refactor.md) |
