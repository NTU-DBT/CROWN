# `src/planner/comparisons.cpp` — block usage map

[Source](../../../../../src/planner/comparisons.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Check operator/variable/type and literal-byte admission while preserving the original equality query and plan authority.

Snapshot SHA-256: `8f9741bf45fb99c0de1d58d58a801e214ef587894cf02f98ed361e458178744b`. 73 lines partitioned into 13 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [comparisons](../../../subsystem_contracts.md#comparisons). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/comparisons.md](../../../../comparisons.md), [docs/query_memory.md](../../../../query_memory.md), [docs/code_review.md](../../../../code_review.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../src/planner/comparisons.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 7–14](../../../../../src/planner/comparisons.cpp#L7) | Type/record definition: struct Budget |  · [reviewed contract](#b0002) |
| [B0003 · 15–17](../../../../../src/planner/comparisons.cpp#L15) | Callable definition: void require(bool condition, const char* message) | calls Error; guard void require(bool condition, const char* message) { · [reviewed contract](#b0003) |
| [B0004 · 18–24](../../../../../src/planner/comparisons.cpp#L18) | Callable definition: void validate_operator(Operator operation) | calls require; guard require(false, "comparison operator is invalid"); · [reviewed contract](#b0004) |
| [B0005 · 25–37](../../../../../src/planner/comparisons.cpp#L25) | Callable definition: ScalarType operand_type(const Operand& operand, const Query& query, const std::vector&lt;bool&gt;& bound, Budget& budget) | calls take, require, size, valueless_by_exception; guard require(variable-&gt;value &lt; bound.size() && bound\[variable-&gt;value\],; returns query.variables\[variable-&gt;value\].type; type_of(*literal) · [reviewed contract](#b0005) |
| [B0006 · 38–39](../../../../../src/planner/comparisons.cpp#L38) | Closes surrounding scope/type. | source comment (unverified): // namespace · [reviewed contract](#b0006) |
| [B0007 · 40–44](../../../../../src/planner/comparisons.cpp#L40) | Type/record definition: struct Plan::Data |  · [reviewed contract](#b0007) |
| [B0008 · 45–45](../../../../../src/planner/comparisons.cpp#L45) | Callable definition: const PhysicalPlan& Plan::general() const & noexcept | calls ; returns data_-&gt;general · [reviewed contract](#b0008) |
| [B0009 · 46–46](../../../../../src/planner/comparisons.cpp#L46) | Callable definition: std::span&lt;const Predicate&gt; Plan::predicates() const & noexcept | calls ; returns data_-&gt;predicates · [reviewed contract](#b0009) |
| [B0010 · 47–47](../../../../../src/planner/comparisons.cpp#L47) | Callable definition: std::uint64_t Plan::work() const noexcept | calls ; returns data_-&gt;work · [reviewed contract](#b0010) |
| [B0011 · 48–48](../../../../../src/planner/comparisons.cpp#L48) | Explanatory comments or spacing. |  |
| [B0012 · 49–72](../../../../../src/planner/comparisons.cpp#L49) | Callable definition: Plan admit(const PhysicalPlan& general, std::span&lt;const Predicate&gt; predicates, const Limits& limits) | calls take, require, normalized, query; guard require(!general.normalized(), "comparison admission requires a direct CQ without SQL adapters");; returns Plan(std::make_shared&lt;Plan::Data&gt;(Plan::Data{general,; growth make_shared; 4 loop sites; source comment (unverified): // Copy only after all guards and payload-byte admissions have succeeded. · [reviewed contract](#b0012) |
| [B0013 · 73–73](../../../../../src/planner/comparisons.cpp#L73) | Closes surrounding scope/type. | source comment (unverified): // namespace crown::planner::comparisons · [reviewed contract](#b0013) |

## B0001

[Lines 1–6](../../../../../src/planner/comparisons.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L6:sha256:dc69682a0875a2258dc65328502d6269e385f4681d327a8de0cfe50c6d0dce3c
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Bind the comparison implementation to its public typed plan and native error vocabulary. |
| inputs / outputs | Implementation includes/namespaces; no operation invoked by scaffolding. |
| invariants | Implementation remains opt-in and does not modify existing equality normalization. |
| ownership | No retained owner in these declarations. |
| failure | Ordinary compile/link failures only. |
| cost | Compile-time scaffolding. |
| Design | [src/planner/comparisons.cpp](../../../../../src/planner/comparisons.cpp), [include/crown/planner/comparisons.hpp](../../../../../include/crown/planner/comparisons.hpp) |

## B0002

[Lines 7–14](../../../../../src/planner/comparisons.cpp#L7); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L7-L14:sha256:084655048077b1049f4d4fbae928b48683946d0636c727654bf188cfe3a7931a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Spend one nonrefillable selected cold-admission grant. |
| inputs / outputs | Remaining/used uint64 counters and requested amount; successful take updates both. |
| invariants | Reject before mutation when amount exceeds remaining; used+remaining stays initial grant, so accepted additions cannot overflow. |
| ownership | Builder-local inline counters; no secondary account or allowance. |
| failure | Throws comparison_work_limit directly on exhaustion; no catch/retry. |
| cost | O(1) arithmetic per take; charged scalar bytes describe admitted copying rather than CPU timing. |
| Design | [src/planner/comparisons.cpp](../../../../../src/planner/comparisons.cpp), [include/crown/planner/comparisons.hpp](../../../../../include/crown/planner/comparisons.hpp) |

## B0003

[Lines 15–17](../../../../../src/planner/comparisons.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L15-L17:sha256:a583354c6eb5514d91ea2f9a813d6b11aeed7e8812c42cf014ab4c5c31ec75e9
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Reject an unsupported comparison premise with its explicit admission code. |
| inputs / outputs | Boolean condition and static message in; returns only if true. |
| invariants | False means comparison_admission, not an accepted fallback or resource infeasibility proof. |
| ownership | Borrows message synchronously; Error owns its diagnostic. |
| failure | Throws crown::Error without local handling. |
| cost | One conditional plus actual failure-diagnostic construction. |
| Design | [src/planner/comparisons.cpp](../../../../../src/planner/comparisons.cpp), [include/crown/api/error.hpp](../../../../../include/crown/api/error.hpp) |

## B0004

[Lines 18–24](../../../../../src/planner/comparisons.cpp#L18); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L18-L24:sha256:52075b2897196c6623e45e7f99ba28c215099aba4ecc1784619860a3ae2bbf71
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Validate even forged public Operator values. |
| inputs / outputs | One enum value in; returns only for six declared comparisons. |
| invariants | No default comparison, truth folding or equality-class rewrite is selected for unknown bits. |
| ownership | Inline enum input; no retained allocation. |
| failure | Out-of-enumerator value uses comparison_admission. |
| cost | Bounded switch work. |
| Design | [src/planner/comparisons.cpp](../../../../../src/planner/comparisons.cpp), [include/crown/planner/comparisons.hpp](../../../../../include/crown/planner/comparisons.hpp) |

## B0005

[Lines 25–37](../../../../../src/planner/comparisons.cpp#L25); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L25-L37:sha256:72d711ea8d5eebb620a4abf5e6befcbff8ab71f4388c17114f3e178d8865a708
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check one operand and determine its exact scalar kind before any retained predicate copy. |
| inputs / outputs | Operand, genuine query, bound-ID vector and shared Budget in; ScalarType out. |
| invariants | Variable IDs must be in range and body-bound. A literal must be a live Value variant. String extent is charged before copying; type_of uses existing exact scalar alternatives, with no coercion or collation change. |
| ownership | Borrows caller DTO/query; no scalar bytes are retained by this helper. |
| failure | Invalid/valueless/unbound operand gives comparison_admission; shared work refusal propagates. No resource recovery. |
| cost | One selected operand step plus literal string-byte grant; type inspection and bounded scalar operations are additional. |
| Design | [src/planner/comparisons.cpp](../../../../../src/planner/comparisons.cpp), [include/crown/planner/comparisons.hpp](../../../../../include/crown/planner/comparisons.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp) |

## B0006

[Lines 38–39](../../../../../src/planner/comparisons.cpp#L38); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L38-L39:sha256:c929980d95efc152dc886ac42af0f045075441dd18a8f886364828ead327bbd3
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the private admission-helper namespace. |
| inputs / outputs | Namespace delimiter only. |
| invariants | No helper becomes public authority. |
| ownership | No owner. |
| failure | No runtime failure branch. |
| cost | No runtime work. |
| Design | [src/planner/comparisons.cpp](../../../../../src/planner/comparisons.cpp) |

## B0007

[Lines 40–44](../../../../../src/planner/comparisons.cpp#L40); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L40-L44:sha256:41c24215c5ea21944e3d15eaf74d66d354afe6b099c3c21d41cb950073c5be00
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Own the original general plan, immutable copied conjunction and admission work. |
| inputs / outputs | Private Plan::Data aggregates PhysicalPlan, vector&lt;Predicate&gt; and used-work counter. |
| invariants | Original equality query/profile and comparison predicates remain separate; published access is const only. |
| ownership | Ordinary cold shared Data retains plan handle and all predicate literal bytes. |
| failure | Partial construction unwinds normally on allocation failure before Plan publication. |
| cost | One shared control, predicate descriptors/literals and retained original-plan lifetime. |
| Design | [src/planner/comparisons.cpp](../../../../../src/planner/comparisons.cpp), [include/crown/planner/comparisons.hpp](../../../../../include/crown/planner/comparisons.hpp) |

## B0008

[Lines 45–45](../../../../../src/planner/comparisons.cpp#L45); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L45-L45:sha256:547203c3ad89d4aacd38d6b74e3ffe3cbcf23fb962088b67d874fc7c387604fc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the unchanged genuine original general plan. |
| inputs / outputs | Live Plan in; const PhysicalPlan reference out. |
| invariants | No original comparison guarantee or rewritten equality query is synthesized. |
| ownership | Reference borrows shared Data. |
| failure | Noexcept on valid admitted Plan. |
| cost | O(1) getter. |
| Design | [src/planner/comparisons.cpp](../../../../../src/planner/comparisons.cpp), [include/crown/planner/comparisons.hpp](../../../../../include/crown/planner/comparisons.hpp) |

## B0009

[Lines 46–46](../../../../../src/planner/comparisons.cpp#L46); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L46-L46:sha256:4395e78b11a6a151d84c2f9b6053e679dc9173a01b51f06a2b3d1de81603ebf4
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Borrow the admitted conjunction in original caller order. |
| inputs / outputs | Live Plan in; span&lt;const Predicate&gt; out. |
| invariants | No literal mutation or reordering through this span. |
| ownership | Span borrows shared Data and literal payloads. |
| failure | Noexcept on valid admitted Plan. |
| cost | O(1) getter. |
| Design | [src/planner/comparisons.cpp](../../../../../src/planner/comparisons.cpp), [include/crown/planner/comparisons.hpp](../../../../../include/crown/planner/comparisons.hpp) |

## B0010

[Lines 47–47](../../../../../src/planner/comparisons.cpp#L47); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L47-L47:sha256:37eaf0d09ce2f0e5205c069fc6e63fa9e3ff5c684ff694835880e5116cfa43b7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Report the actual selected admission work used. |
| inputs / outputs | Live Plan in; uint64 spent counter out. |
| invariants | This reports cold admission, not runtime/paper complexity. |
| ownership | Inline value copied from shared Data. |
| failure | Noexcept on valid admitted Plan. |
| cost | O(1) getter. |
| Design | [src/planner/comparisons.cpp](../../../../../src/planner/comparisons.cpp), [include/crown/planner/comparisons.hpp](../../../../../include/crown/planner/comparisons.hpp) |

## B0012

[Lines 49–72](../../../../../src/planner/comparisons.cpp#L49); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L49-L72:sha256:f7aaf4059c14dca92f8b07496b88f63210ad93a2d2d3b5de09ebc7c41b86db9e
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Admit exact typed predicate metadata without altering original query semantics or provenance. |
| inputs / outputs | Genuine direct PhysicalPlan, predicate span and finite Limits in; completed immutable Plan out. |
| invariants | Reject normalized SQL; retain every genuine route including contradiction/constant. Scan original atom-variable binding. Validate every operation and both operand kinds before the sole predicate-vector copy. Empty conjunction and constant predicates are retained exactly, never folded into Query or head. |
| ownership | Builder owns ordinary bound-bit scratch and unpublished copied predicates; resulting shared-const Data retains caller-independent literals and original plan handle. |
| failure | Admission/work errors and allocation failures unwind unpublished state, leaving caller inputs unchanged. Genuine PhysicalPlan validity and atom ID/type validation are inherited premises, not freshly re-proved. |
| cost | Selected work is exactly 1+variables+atoms+terms+3*predicates+literal string bytes. Bit-vector allocation, one predicate/literal copy, shared control and final plan teardown have actual additional costs. |
| Design | [src/planner/comparisons.cpp](../../../../../src/planner/comparisons.cpp), [include/crown/planner/comparisons.hpp](../../../../../include/crown/planner/comparisons.hpp), [src/ir/model.cpp](../../../../../src/ir/model.cpp), [src/planner/lower.cpp](../../../../../src/planner/lower.cpp), [Refactor.md](../../../../../Refactor.md), [docs/comparisons.md](../../../../comparisons.md) |

## B0013

[Lines 73–73](../../../../../src/planner/comparisons.cpp#L73); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L73-L73:sha256:b3e675e468bf7eeff252c302206c873aa3401962ff4daf5fa57e79ff9f4ee8d8
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the comparisons implementation namespace. |
| inputs / outputs | Namespace delimiter only. |
| invariants | No implicit registration or global runtime state is added. |
| ownership | No owner. |
| failure | No runtime branch. |
| cost | No runtime work. |
| Design | [src/planner/comparisons.cpp](../../../../../src/planner/comparisons.cpp) |
