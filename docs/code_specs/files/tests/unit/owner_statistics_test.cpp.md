# `tests/unit/owner_statistics_test.cpp` — block usage map

[Source](../../../../../tests/unit/owner_statistics_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `d460601d9e6da8974dbacc12a5893ccb64e1ad6698107e12ee5963693f883057`. 207 lines partitioned into 2 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–14](../../../../../tests/unit/owner_statistics_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!std::is_default_constructible_v&lt;stats::OwnerCapture&gt;); · [reviewed contract](#b0001) |
| [B0002 · 15–207](../../../../../tests/unit/owner_statistics_test.cpp#L15) | Callable definition: int main() | calls plan, database, request, PhysicalRuntime::initialize; guard check(captured.stamp().owner==physical.owner() && captured.stamp().sequence==0 && captured.plan().p…; returns owner.capture_statistics(request(owner.plan())); growth insert, make_unique, push_back, resize; 16 loop sites; source comment (unverified): // 1. Actual owner stamp and literal scope/cardinality distinctions. · [reviewed contract](#b0002) |

## B0001

[Lines 1–14](../../../../../tests/unit/owner_statistics_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L14:sha256:c54e4f89a9d3185d9d85baf977a983469ad3e9b1ccd32504fee4c8e18e550347
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare owner_statistics_test.cpp: include "owner_statistics_fixture.hpp", "crown/runtime/session.hpp", "evaluator.hpp", "crown/api/error.hpp", &lt;map&gt;, &lt;sstream&gt;, &lt;iostream&gt;, &lt;type_traits&gt;; bind local aliases/name imports; require 5 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/owner_statistics_test.cpp](../../../../../tests/unit/owner_statistics_test.cpp), [docs/statistics.md](../../../../statistics.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 15–207](../../../../../tests/unit/owner_statistics_test.cpp#L15); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify physical owner-state statistics against literal facts across scope semantics, freshness, pending barriers, budgets, lifecycle and error cases. |
| inputs / outputs | Builds R(x,y,ignored), S(y), unused(u), captures eight source/occurrence/node/index selections, then exercises physical, replayed, rebuilt, SupportRuntime, DeltaRuntime, generalized and QuerySession owners. |
| invariants | Distinguishes source rows, derivation maps, S/P/E supports and reverse-index degrees; uses independent evaluator/maps; checks replay fact equality but foreign owner identity; private captures are metadata-only; no-op advances epoch without changing facts; old owning reports survive update/move/drop; shared limits preserve completed components and expose unknown prefixes; repeated/empty projections retain field order; invalid request/field/index/role throws; empty populations are exact zero. Compile-time assertions also require non-default OwnerCapture and const stamp/components/plan/limits accessors. |
| ownership | Capture reports own plan binding, selection descriptors and copied keys. Runtime/session storage remains owned by the active owner; saved captures are inspected after update, move or destruction. |
| failure | Invalid request and unsupported fields/index/projection errors are caught as crown::Error; budget exhaustion is explicit and not thrown; pending state suppresses components. Unhandled test errors fail main. |
| cost | Scans small fixed relations and sorts/maps exact oracle keys; loops over four budget dimensions and finite fixture variants. It is C01 correctness coverage, not benchmark timing or a completeness theorem for all plans. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |
