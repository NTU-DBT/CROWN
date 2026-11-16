# `tests/unit/selection_pure_link_test.cpp` — block usage map

[Source](../../../../../tests/unit/selection_pure_link_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `bad739e50d29844a010224586ad5419bc15485e5cd939e2e39d275133f7f1a9b`. 20 lines partitioned into 2 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–4](../../../../../tests/unit/selection_pure_link_test.cpp#L1) | Imports dependencies. |  · [reviewed contract](#b0001) |
| [B0002 · 5–20](../../../../../tests/unit/selection_pure_link_test.cpp#L5) | Callable definition: int main() | calls c02_test::fixture, c02_test::candidates, ps::PlanCache::create, ps::select; guard check(first.selection && second.selection, "C05 pure selection failed");; returns 1 · [reviewed contract](#b0002) |

## B0001

[Lines 1–4](../../../../../tests/unit/selection_pure_link_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L4:sha256:42a7c511ef69e53a87f3dc691faad641ce24b314acdec4a25cc089269ae4e1f7
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_pure_link_test.cpp: include "ranking_fixture.hpp", "crown/planner/selection.hpp", &lt;iostream&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/selection_pure_link_test.cpp](../../../../../tests/unit/selection_pure_link_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 5–20](../../../../../tests/unit/selection_pure_link_test.cpp#L5); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() { try {
  using namespace c02_test; namespace ps = planner::selection;
  const auto f = c02_test::fixture(); const auto snapshot = c02_test::candidates(f);
  auto cache = ps::PlanCache::create(); const ps::Source source = ps::DirectCQ{};
  ps::Request request; request.policy = ps::Policy::height_only;
  const auto first = ps::select(snapshot, source, request, {}, &cache, ps::CacheUse::read_write);
  const auto second = ps::select(snapshot, source, request, {}, &cache, ps::CacheUse::read_only);
  check(first.selection && second.selection, "C05 pure selection failed");
  const auto& cold = *first.selection; const auto& warm = *second.selection;
  check(warm.cache_observation().disposition == ps::CacheDisposition::hit && warm.usage().lowering_work == 0 &&
      warm.cache_binding() == cold.cache_binding() && warm.selected().structural_key() == cold.selected().structural_key(),
      "C05 pure cache reuse failed");
  check(cold.evidence_use() == ps::EvidenceUse::absent && cold.plan().guarantee().height_status == "valid_upper_bound",
      "C05 pure link manufactured runtime/proof authority");
  std::cout << "C05 pure selection link without runtime/report passed\n";
} catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; } }

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Demonstrate the pure selection target needs no runtime bridge. |
| inputs / outputs | Builds a small candidate family, performs height-only selection with cache insert then read-only hit, and checks the warmed call does not lower again. |
| invariants | Calls the pure selection API without capturing a runtime owner. The cold result asserts absent Evidence and a valid_upper_bound compiled-plan guarantee. The warm result retains the same cache binding and structural choice with zero lowering work. These checks establish neither current-owner freshness nor a new minimum proof. |
| ownership | Candidate snapshot, cache, and Selection retain ordinary caller/result handles. |
| failure | Any stop, missing selection, or unexpected lower count fails the executable. |
| cost | Two pure selection calls run over the C02 fixture candidate family; the warm call still performs cache lookup/key work even though lowering_work is zero. |
| Design | [tests/unit/selection_pure_link_test.cpp](../../../../../tests/unit/selection_pure_link_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md) |
