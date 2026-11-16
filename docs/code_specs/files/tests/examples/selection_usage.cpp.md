# `tests/examples/selection_usage.cpp` — block usage map

[Source](../../../../../tests/examples/selection_usage.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `255855110b2d2bcf483d79bd9e0a2c970453c78f1989985bc71781e3b8269fbb`. 31 lines partitioned into 5 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–5](../../../../../tests/examples/selection_usage.cpp#L1) | Imports dependencies; declares namespace scope. | source comment (unverified): // Obtaining the typed proof/provider snapshot and initializing an owner remain · [reviewed contract](#b0001) |
| [B0002 · 6–11](../../../../../tests/examples/selection_usage.cpp#L6) | Callable definition: planner::selection::Attempt choose_height(const planner::CandidateSnapshot& candidates) | calls planner::selection::select; returns planner::selection::select(candidates, planner::selection::DirectCQ{}, request); source comment (unverified): // Obtaining the typed proof/provider snapshot and initializing an owner remain · [reviewed contract](#b0002) |
| [B0003 · 12–23](../../../../../tests/examples/selection_usage.cpp#L12) | Callable definition: runtime::selection::Attempt choose_current(const planner::CandidateSnapshot& candidates, const runtime::PhysicalRuntime& owner, p… | calls runtime::selection::select_current, plan; returns runtime::selection::select_current(candidates,; source comment (unverified): // Slots are a unitless source-cardinality proxy. This is not a byte cap. · [reviewed contract](#b0003) |
| [B0004 · 24–30](../../../../../tests/examples/selection_usage.cpp#L24) | Callable definition: planner::selection::Attempt choose_as_of(const planner::CandidateSnapshot& candidates, const PhysicalPlan& basis, const planner::… | calls planner::selection::select; returns planner::selection::select(candidates, planner::selection::PhysicalBasis{basis}, request, evidence) · [reviewed contract](#b0004) |
| [B0005 · 31–31](../../../../../tests/examples/selection_usage.cpp#L31) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::examples · [reviewed contract](#b0005) |

## B0001

[Lines 1–5](../../../../../tests/examples/selection_usage.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L5:sha256:b639a4c2a3a7de818f695c1609d8a39f1aef5c9fb92ef958852a86332ad86f45
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_usage.cpp: include "crown/runtime/selection.hpp". |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/examples/selection_usage.cpp](../../../../../tests/examples/selection_usage.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 6–11](../../../../../tests/examples/selection_usage.cpp#L6); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::selection::Attempt choose_height(const planner::CandidateSnapshot& candidates) {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select and compile one retained-prefix candidate from the checked direct-CQ proof source. |
| inputs / outputs | Borrows CandidateSnapshot; creates selection Request with height_only and retained_prefix, uses DirectCQ default PhysicalOptions, and returns planner selection Attempt. No evidence/cache/runtime owner supplied. |
| invariants | Selects best only among retained candidates; no provider advancement, live installation or new minimum-height proof. Pure height selection needs no statistical evidence; caller must already possess typed candidate snapshot. |
| ownership | Inputs are synchronous borrows; successful Selection owns immutable selected CompiledProgram, snapshot/proof, captured request/source and decision context. Local Source/Request do not remain dangling. |
| failure | Called noexcept select reports no candidates/invalid binding/request and processing/lowering/allocation stops in Attempt; wrapper has no catch/retry, though wrapper itself has no noexcept annotation. |
| cost | Fixed request/source construction plus full candidate validation/key ranking and selected-plan native lowering; finite defaults apply and no cache is consulted or timings measured. |
| Design | [tests/examples/selection_usage.cpp](../../../../../tests/examples/selection_usage.cpp), [docs/selection.md](../../../../selection.md), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp) |

## B0003

[Lines 12–23](../../../../../tests/examples/selection_usage.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
runtime::selection::Attempt choose_current(const planner::CandidateSnapshot& candidates,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select from the live owner’s physical source using depth ranking, mandatory 32-slot eligibility and an explicit read/write artifact cache. |
| inputs / outputs | Borrows candidates/owner and mutable PlanCache; sets committed_input_native_depth, height fallback, TupleIndexSlotLimit{"32"}, aggregate work 1,000,000 and calls runtime select_current with owner.plan basis/default capture limits. Returns runtime Attempt. |
| invariants | Caller keeps exclusive owner/cache access for whole call. Fresh capture is required; height fallback cannot bypass the slot cap. Slots are unitless source-cardinality proxy, not bytes; no selected plan is installed. |
| ownership | Owner is read but cache can be changed on successful read_write participation. Successful CurrentSelection owns capture/Selection/plan and may outlive owner access/cache eviction; constructing PhysicalBasis shares immutable native plan input. |
| failure | Attempt distinguishes unavailable boundary/facts, unsatisfied constraint and resource/lowering/cache failure; failed calls leave cache/owner unchanged under called API. No local catch or retry; nested attempts must be inspected. |
| cost | Fresh capture, complete slot and primary assessments share finite aggregate processing; slot scoring may lower every candidate even on cache hit. Cache keys/comparison/admission and retained selected plan storage add real work beyond the fixed wrapper. |
| Design | [tests/examples/selection_usage.cpp](../../../../../tests/examples/selection_usage.cpp), [docs/selection.md](../../../../selection.md), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp) |

## B0004

[Lines 24–30](../../../../../tests/examples/selection_usage.cpp#L24); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
planner::selection::Attempt choose_as_of(const planner::CandidateSnapshot& candidates,
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Select a candidate-local native plan from an explicit physical basis using retained slot evidence. |
| inputs / outputs | Borrows candidates/PhysicalPlan/evidence; requests tuple_index_slots with require_evidence and default retained-prefix/limits; returns pure planner selection Attempt with PhysicalBasis. |
| invariants | No live owner is supplied/revalidated, so evidence is historical as-of only. This sets a ranking policy, not a mandatory slot constraint; complete source must agree with evidence and proof snapshot. |
| ownership | Temporary basis variant/evidence optional copy share factory handles for synchronous input; successful Selection owns selected program, retained evidence/proof and captured request/source. Caller plan/evidence objects are not mutated. |
| failure | No local catches/fallback retry; select reports binding mismatch, unavailable evidence, resource/lowering/allocation failures in Attempt. require_evidence prevents statistical height fallback. |
| cost | Full retained-prefix slot evaluation can lower each candidate and retain modeled native plans; source binding/selected-plan admission use default finite budgets. No cache, native runtime state migration or timing measurement is requested. |
| Design | [tests/examples/selection_usage.cpp](../../../../../tests/examples/selection_usage.cpp), [docs/selection.md](../../../../selection.md), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [include/crown/runtime/selection.hpp](../../../../../include/crown/runtime/selection.hpp) |

## B0005

[Lines 31–31](../../../../../tests/examples/selection_usage.cpp#L31); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L31-L31:sha256:3d92a3bd78a6f3db401678e70f0f968b447eb5c98a871708d992f7ea9344ffe1
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in selection_usage.cpp: namespace crown::examples. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/examples/selection_usage.cpp](../../../../../tests/examples/selection_usage.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |
