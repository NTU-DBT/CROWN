# `tests/examples/ranking_usage.cpp` — block usage map

[Source](../../../../../tests/examples/ranking_usage.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `3c7f715a6df2a34060a2259ac4e5d44739cf9a53985d19702acc58c5c6365f3c`. 56 lines partitioned into 7 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–11](../../../../../tests/examples/ranking_usage.cpp#L1) | Imports dependencies; declares namespace scope; declares values/defaults or compile-time conditions. |  · [reviewed contract](#b0001) |
| [B0002 · 12–18](../../../../../tests/examples/ranking_usage.cpp#L12) | Callable definition: \[\[nodiscard\]\] pr::Attempt height_only( const crown::planner::CandidateSnapshot& candidates) noexcept | calls pr::rank; returns pr::rank(candidates, request) · [reviewed contract](#b0002) |
| [B0003 · 19–19](../../../../../tests/examples/ranking_usage.cpp#L19) | Explanatory comments or spacing. |  |
| [B0004 · 20–37](../../../../../tests/examples/ranking_usage.cpp#L20) | Callable definition: \[\[nodiscard\]\] pr::Attempt current_native_depth( const crown::planner::CandidateSnapshot& candidates, const crown::runtime::Physic… | calls rr::rank_current, effective_policy, fallback_reasons; returns attempt; attempt · [reviewed contract](#b0004) |
| [B0005 · 38–38](../../../../../tests/examples/ranking_usage.cpp#L38) | Explanatory comments or spacing. |  |
| [B0006 · 39–55](../../../../../tests/examples/ranking_usage.cpp#L39) | Callable definition: \[\[nodiscard\]\] std::optional&lt;pr::Attempt&gt; current_tuple_index_slots( const crown::planner::CandidateSnapshot& candidates, const cr… | calls rr::revalidate, usable, inputs, pr::rank; returns std::nullopt; std::optional&lt;pr::Attempt&gt;{pr::rank(candidates, request, as_of)} · [reviewed contract](#b0006) |
| [B0007 · 56–56](../../../../../tests/examples/ranking_usage.cpp#L56) | Closes surrounding scope/type. | source comment (unverified): // namespace c02_guide · [reviewed contract](#b0007) |

## B0001

[Lines 1–11](../../../../../tests/examples/ranking_usage.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L11:sha256:e80787007399904a413bfcacbd324e1bd5427a656618f6c1b2dfaaa54158f7fa
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ranking_usage.cpp: include &lt;optional&gt;, "crown/planner/candidates.hpp", "crown/planner/ranking.hpp", "crown/runtime/physical.hpp", "crown/runtime/ranking_evidence.hpp"; bind local aliases/name imports. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/examples/ranking_usage.cpp](../../../../../tests/examples/ranking_usage.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 12–18](../../../../../tests/examples/ranking_usage.cpp#L12); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] pr::Attempt height_only(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rank the supplied checked minimum-height candidate prefix by deterministic structural key. |
| inputs / outputs | Borrows CandidateSnapshot; creates default finite C02 request with height_only/require_evidence and returns pr::Attempt. No runtime owner or Evidence is passed. |
| invariants | Height-only policy needs no statistical evidence despite the configured fallback enum; the complete retained prefix must be assessed or no Result publishes. Does not resume provider search, compile/install a live plan or prove family exhaustion. |
| ownership | Snapshot is borrowed during the call; successful Result is an owning shared immutable handle retaining snapshot/proof and score storage. Local request does not escape as a borrowed pointer. |
| failure | noexcept rank reports invalid handles/bindings/empty family/resource/allocation failures in Attempt.stop/result; wrapper adds no catch, retry or policy change. |
| cost | Fixed request construction plus bounded complete-prefix validation/key ranking inside rank; score/key storage and comparisons scale with retained candidate structure under default finite limits. No measurement occurs here. |
| Design | [tests/examples/ranking_usage.cpp](../../../../../tests/examples/ranking_usage.cpp), [docs/ranking.md](../../../../ranking.md), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0004

[Lines 20–37](../../../../../tests/examples/ranking_usage.cpp#L20); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] pr::Attempt current_native_depth(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Rank candidates from current committed-input native-depth evidence with explicit whole-prefix height fallback. |
| inputs / outputs | Borrows candidates/PhysicalRuntime, calls rank_current with committed_input_native_depth and height_only fallback, returns its Attempt unchanged. Reads fallback_reasons only when effective policy is height_only, then discards that local value. |
| invariants | Caller preserves owner’s exclusive synchronous access through capture/rank; owner counters are not enabled/reset by wrapper. Statistical unavailability may choose height on the same prefix; processing/resource failures do not trigger fallback, and returned capture cannot promise future freshness. |
| ownership | Owner/candidates are borrowed; successful Result retains owning evidence/snapshot rather than a live-owner lease. Local Attempt is returned, with shared result lifetime independent of this stack. |
| failure | noexcept path preserves evidence_unavailable/no-result and all other reported stops/reasons; it neither throws custom errors nor retries/captures again after return. |
| cost | One actual bounded current evidence capture plus full-prefix ranking and possible fallback under shared default processing limits; branches/read of reason bits are fixed wrapper work. Depth score is a workload proxy, not elapsed time. |
| Design | [tests/examples/ranking_usage.cpp](../../../../../tests/examples/ranking_usage.cpp), [docs/ranking.md](../../../../ranking.md), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0006

[Lines 39–55](../../../../../tests/examples/ranking_usage.cpp#L39); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
[[nodiscard]] std::optional<pr::Attempt> current_tuple_index_slots(
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Revalidate retained source-cardinality evidence, then rank by the tuple/index-slot proxy when the actual boundary and required facts remain usable. |
| inputs / outputs | Borrows candidates/owner/retained RuntimeEvidence and overwrites caller current_check with revalidate. Returns nullopt on boundary reasons or unusable memory facts; otherwise returns optional&lt;Attempt&gt; from pure rank with owning Evidence handle copy. |
| invariants | Requires exclusive owner access across revalidation and ranking. Checks policy-specific memory facts rather than requiring depth facts. C02 request has no mandatory slot cap: it ranks by slots with require_evidence; optional presence does not imply Attempt.result success. |
| ownership | current_check is caller-owned output and changes even on rejection. as_of shares immutable retained.inputs ownership; successful Result owns retained evidence/proof storage without borrowing owner. No recapture or owner mutation. |
| failure | noexcept returns nullopt for freshness/fact rejection; entered rank reports its separate stops in Attempt. Caller can inspect current_check boundary/memory reasons and must inspect the nested Attempt result. |
| cost | One current-owner revalidation/read then, if admitted, complete candidate slot assessments that can lower candidate-local plans under default finite limits; evidence handle copy is shared ownership rather than full graph copy. |
| Design | [tests/examples/ranking_usage.cpp](../../../../../tests/examples/ranking_usage.cpp), [docs/ranking.md](../../../../ranking.md), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp) |

## B0007

[Lines 56–56](../../../../../tests/examples/ranking_usage.cpp#L56); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L56-L56:sha256:ac96e7deda3e0fa5c6feca7437095299f7566dbddc42175ab425f42252c7a976
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in ranking_usage.cpp: namespace c02_guide. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/examples/ranking_usage.cpp](../../../../../tests/examples/ranking_usage.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |
