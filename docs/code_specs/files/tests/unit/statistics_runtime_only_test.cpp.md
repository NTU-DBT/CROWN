# `tests/unit/statistics_runtime_only_test.cpp` — block usage map

[Source](../../../../../tests/unit/statistics_runtime_only_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `937edb4a5dba502fbd98eab88918ea7f8cf5a6928ac2bee1ac6182eaa861f329`. 16 lines partitioned into 2 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–6](../../../../../tests/unit/statistics_runtime_only_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!std::is_default_constructible_v&lt;SessionStatisticsContext&gt;); · [reviewed contract](#b0001) |
| [B0002 · 7–16](../../../../../tests/unit/statistics_runtime_only_test.cpp#L7) | Callable definition: int main() | calls plan, database, workload_fixture::delta_options, QuerySession::create_typed; guard check(!empty.state_requested() && empty.combined()-&gt;state().components().empty() && empty.combined(… · [reviewed contract](#b0002) |

## B0001

[Lines 1–6](../../../../../tests/unit/statistics_runtime_only_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L6:sha256:507d20b55d597ce2114b36cbd25ea6035db81062cf21b1fdce8a377505ef1d6a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare statistics_runtime_only_test.cpp: include "owner_statistics_fixture.hpp", "workload_statistics_fixture.hpp", &lt;type_traits&gt;; bind local aliases/name imports; require 2 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/statistics_runtime_only_test.cpp](../../../../../tests/unit/statistics_runtime_only_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 7–16](../../../../../tests/unit/statistics_runtime_only_test.cpp#L7); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify SessionStatisticsContext is factory-created, bound to actual session owner/sequence, and remains owning after drop/move. |
| inputs / outputs | Creates typed QuerySession; captures default context and explicitly requested owner-state context; drops session and captures released status, then moves saved context. |
| invariants | Default context requests no state traversal; explicit combined context binds metadata owner/sequence and literal owner facts; dropped context has no combined report but retains fixed options/status; moved-from and moved-to context keep owner metadata usable. Compile-time checks require factory-only construction and const metadata access. |
| ownership | Context owns immutable metadata/capture payload rather than a QuerySession pointer; session/runtime are dropped independently. |
| failure | Capture/allocation/API failures propagate; no allocation-failure injection is performed in this runtime-only executable. |
| cost | Performs two context captures and fixed owner-map checks, then scalar metadata reads after drop/move; no report serialization. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/observability.md](../../../../observability.md), [docs/verification/c01-statistics-report-root-results-2026-11-07.md](../../../../verification/c01-statistics-report-root-results-2026-11-07.md), [Refactor.md](../../../../../Refactor.md) |
