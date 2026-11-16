# `tests/unit/indexed_owner_statistics_test.cpp` — block usage map

[Source](../../../../../tests/unit/indexed_owner_statistics_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `4eb655818a3732448a23d893e17913b97c7a84bc4573b4820b961a2c4efe0cf4`. 233 lines partitioned into 3 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–15](../../../../../tests/unit/indexed_owner_statistics_test.cpp#L1) | Imports dependencies; declares namespace scope; declares aliases; declares callable signatures; declares values/defaults or compile-time conditions. | guard static_assert(!std::is_default_constructible_v&lt;stats::OwnerCapture&gt;); · [reviewed contract](#b0001) |
| [B0002 · 16–42](../../../../../tests/unit/indexed_owner_statistics_test.cpp#L16) | Callable definition: void native_projection_work_exhaustion() | calls plan, s04_runtime::options, runtime, planner::lower_tree; guard check(captured.components().size()==256 && captured.components()\[0\].availability==stats::Availabili…; growth insert, push_back; 3 loop sites · [reviewed contract](#b0002) |
| [B0003 · 43–233](../../../../../tests/unit/indexed_owner_statistics_test.cpp#L43) | Callable definition: int main() | calls native_projection_work_exhaustion, plan, database, request; guard check(captured.stamp().owner==physical.owner() && captured.stamp().sequence==0 && captured.plan().p…; returns owner.capture_statistics(request(owner.plan())); growth insert, make_unique, push_back, resize; 15 loop sites; source comment (unverified): // 1. Actual owner stamp and literal scope/cardinality distinctions. · [reviewed contract](#b0003) |

## B0001

[Lines 1–15](../../../../../tests/unit/indexed_owner_statistics_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L15:sha256:3045f1920711ce0d34b8d4f19fa5687662ac14b17a8422d69b1490fc3894d676
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare indexed_owner_statistics_test.cpp: include "indexed_runtime_fixture.hpp", "indexed_owner_statistics_fixture.hpp", "crown/runtime/session.hpp", "evaluator.hpp", "crown/api/error.hpp", &lt;map&gt;, &lt;sstream&gt;, &lt;iostream&gt;, &lt;type_traits&gt;; bind local aliases/name imports; require 5 compile-time type/ABI conditions. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. Static assertions establish only their listed C++ type properties, not query/result/recovery correctness or test execution. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/indexed_owner_statistics_test.cpp](../../../../../tests/unit/indexed_owner_statistics_test.cpp), [docs/indexed_storage.md](../../../../indexed_storage.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 16–42](../../../../../tests/unit/indexed_owner_statistics_test.cpp#L16); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
void native_projection_work_exhaustion() {
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise repeated indexed visible-population projection until the shared statistics budget is exhausted. |
| inputs / outputs | Builds an indexed SupportRuntime with per-operation structural-step grant 4096; inserts 32 matching R/S keys; requests one root records component and 255 duplicate visible components with work=100,000,000. |
| invariants | The first records result stays exact; every visible component retains exact cardinality 32, while distribution results are either complete NDV=32 or budget_exhausted with no NDV/top-K/histogram prefix. Runtime sequence remains 64 and answer exists. |
| ownership | Runtime owns the indexed support graph; the returned OwnerCapture owns requested copies after the local test call. |
| failure | Native operation-work denial is recorded as a component budget result, not a thrown C++ allocation error; unexpected runtime errors fail the test. |
| cost | Per request the engine revisits indexed keys and builds ordered distributions until the finite storage-work grant is spent; the test is a bounded-work correctness fixture, not a throughput benchmark. |
| Design | [docs/statistics.md](../../../../statistics.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md), [Refactor.md](../../../../../Refactor.md) |

## B0003

[Lines 43–233](../../../../../tests/unit/indexed_owner_statistics_test.cpp#L43); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(){
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Verify indexed and physical owner captures against literal facts across lifecycle, scope, budget, projection, and error boundaries. |
| inputs / outputs | Runs the shared eight-selection fixture on a physical owner, plus indexed native-exhaustion, support-only, generalized/hidden-separator, DeltaRuntime, and QuerySession scenarios. |
| invariants | Checks actual owner/sequence/plan stamps; independent R/S grouping; replay/rebuild foreign identity; pending metadata-only captures; no-op staleness and lag; source derivation-only changes; shared exact/one-under limits; projection order; empty exact populations; C*-eligible output separators and not-applicable hidden E; request validation; moved/dropped owner/report lifetimes. |
| ownership | Every capture is an owning value; live runtime/session objects are local and may be moved/dropped while saved captures and their plan bindings remain inspectable. |
| failure | Invalid requests must raise crown::Error; budget exhaustion is explicit unknown, not error or zero; pending captures suppress private component facts; unanticipated errors escape the test. |
| cost | Uses fixed small databases and literal maps, with extra bounded repeated indexed scans in B0002; compile-time checks require non-default OwnerCapture and const stamp/components/plan/limits accessors. No timing, production theorem, or general free-connex coverage is claimed. |
| Design | [docs/statistics.md](../../../../statistics.md), [Refactor.md](../../../../../Refactor.md), [docs/verification/c01-statistics-preflight-2026-11-07.md](../../../../verification/c01-statistics-preflight-2026-11-07.md) |
