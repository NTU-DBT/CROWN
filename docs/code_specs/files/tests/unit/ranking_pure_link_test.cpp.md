# `tests/unit/ranking_pure_link_test.cpp` — block usage map

[Source](../../../../../tests/unit/ranking_pure_link_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `c5d25307209df9e5b687da7a2a59b982bc3f2a6d8cbbdc2c35e9796e650a9f45`. 3 lines partitioned into 2 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–2](../../../../../tests/unit/ranking_pure_link_test.cpp#L1) | Imports dependencies. |  · [reviewed contract](#b0001) |
| [B0002 · 3–3](../../../../../tests/unit/ranking_pure_link_test.cpp#L3) | Callable definition: int main() | calls c02_test::fixture, c02_test::candidates, crown::planner::ranking::rank, c02_test::check; guard int main(){try{const auto f=c02_test::fixture();const auto s=c02_test::candidates(f);const auto res…; returns 1 · [reviewed contract](#b0002) |

## B0001

[Lines 1–2](../../../../../tests/unit/ranking_pure_link_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L2:sha256:e58b580a1992cf764493f5f81cbdeb7343db9895a8dde9ec39ca3a1249f123e5
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ranking_pure_link_test.cpp: include "ranking_fixture.hpp", &lt;iostream&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/ranking_pure_link_test.cpp](../../../../../tests/unit/ranking_pure_link_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 3–3](../../../../../tests/unit/ranking_pure_link_test.cpp#L3); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(){try{const auto f=c02_test::fixture();const auto s=c02_test::candidates(f);const auto result=crown::planner::ranking::rank(s);c02_test::check(result.result.has_value(),"pure rank missing");std::cout<<"C02 pure link: no runtime/report archive\n";}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prove the pure ranking executable links and runs without runtime/report APIs. |
| inputs / outputs | Builds the C02 fixture family, invokes pure rank, and checks only that a Result exists; it does not assert which candidate was selected. |
| invariants | The call uses the pure planner surface; it does not capture an owner or write a report. |
| ownership | CandidateSnapshot and Result are local retained handles. |
| failure | An unexpected stop/check failure terminates the test executable. |
| cost | One pure ranking call over the small fixture family. |
| Design | [tests/unit/ranking_pure_link_test.cpp](../../../../../tests/unit/ranking_pure_link_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md) |
