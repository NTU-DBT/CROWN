# `tests/unit/combined_statistics_test.cpp` — block usage map

[Source](../../../../../tests/unit/combined_statistics_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `7221b1c7a0d6e1936d3ac14c028148a1fd54d8fa05bfb5243fe86fd51aca467c`. 124 lines partitioned into 2 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–10](../../../../../tests/unit/combined_statistics_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!std::is_default_constructible_v&lt;stats::CombinedCapture&gt;); · [reviewed contract](#b0001) |
| [B0002 · 11–124](../../../../../tests/unit/combined_statistics_test.cpp#L11) | Callable definition: int main() | calls plan, database, request, PhysicalRuntime::initialize; guard check(off.workload().options().mode==ws::Mode::off && off.workload().descriptors().empty());; growth insert, make_unique; 3 loop sites; source comment (unverified): // 1. Actual bindings agree even while workload collection is off; success and no-op are distinct. · [reviewed contract](#b0002) |

## B0001

[Lines 1–10](../../../../../tests/unit/combined_statistics_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L10:sha256:8e9245bee26087f511156b81f287c6d891bf1510c00da6a5be1a156beecbc9f0
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare combined_statistics_test.cpp: include "combined_statistics_fixture.hpp", &lt;iostream&gt;, &lt;sstream&gt;, &lt;type_traits&gt;; bind local aliases/name imports; require 5 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/combined_statistics_test.cpp](../../../../../tests/unit/combined_statistics_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 11–124](../../../../../tests/unit/combined_statistics_test.cpp#L11); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify one-boundary combined captures across off/counters modes, transactions, lifecycle, and output parity. |
| inputs / outputs | Builds the shared R/S plan and eight-scope request; runs physical and Delta runtimes, SupportRuntime, and QuerySession through nine groups of updates/captures. |
| invariants | State and workload always bind to actual owner/sequence/plan; successful and duplicate events differ in input/noop counts; private captures expose no state facts; failed mode/spool work does not publish mixed state; reset changes workload generation but not data freshness; support-only denominators unavailable; state and workload caps/samples are independent; rebuild is foreign owner and move preserves identity; all-off and counters-on canonical state and signed output agree per event. |
| ownership | Each returned CombinedCapture owns both halves, plan and keys; live owners/sessions maintain separate state and may be moved, reset, or dropped after a saved report exists. |
| failure | Expected work errors are checked by exact error code; pending capture is metadata-only; output cursors are discarded after use. Unexpected errors fail main. |
| cost | Nine groups use a fixed source fixture, multiple full captures, map oracles and output-parity comparisons; compile-time checks require factory-only, privately paired CombinedCapture with nothrow copy and const accessors. This validates C01 behavior, not measured overhead or universal capture guarantees. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/verification/c01-statistics-combined-root-results-2026-11-07.md](../../../../verification/c01-statistics-combined-root-results-2026-11-07.md), [Refactor.md](../../../../../Refactor.md) |
