# `tests/unit/selection_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/selection_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `4a5f3ad6dc5e04aae74edd43cc9de4a744e4a33ac11ff8ee7433d3b8c7abe286`. 43 lines partitioned into 2 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–2](../../../../../tests/unit/selection_exception_test.cpp#L1) | Imports dependencies. |  · [reviewed contract](#b0001) |
| [B0002 · 3–43](../../../../../tests/unit/selection_exception_test.cpp#L3) | Callable definition: int main() | calls c02_test::fixture, c02_test::candidates, planner::lower_tree, candidate; guard check(owner.canonical_state().sources == f.database.tables && evidence.denominator() == 103 &&; returns ps::select(snapshot, source, selection_request,; ps::select(snapshot, source, both, evidence, &cach…; growth insert; 1 loop sites · [reviewed contract](#b0002) |

## B0001

[Lines 1–2](../../../../../tests/unit/selection_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L2:sha256:a67c785f1a79d5b295addb1f5a94e676d3f5a3dae9250f53e23d1d398c8b502d
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare selection_exception_test.cpp: include "selection_exception_support.hpp". |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [docs/selection.md](../../../../selection.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 3–43](../../../../../tests/unit/selection_exception_test.cpp#L3); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main() { try {
  using namespace c05_fault;
  const auto f = c02_test::fixture(); const auto snapshot = c02_test::candidates(f);
  const auto plan = planner::lower_tree(f.catalog, f.query, snapshot.candidate(0)->tree());
  auto owner = runtime::PhysicalRuntime::initialize(plan, f.database); heat(owner, f);
  const auto update = [&](SetOperation operation, Row row) {
    static_cast<void>(owner.apply({owner.sequence() + 1, TableId{0}, operation, std::move(row)}));
  };
  update(SetOperation::insert, Row{std::int64_t{2}}); update(SetOperation::erase, Row{std::int64_t{2}});
  update(SetOperation::erase, Row{std::int64_t{3}});
  const auto evidence = capture(snapshot, owner).inputs(); const ps::Source source = ps::DirectCQ{};
  check(owner.canonical_state().sources == f.database.tables && evidence.denominator() == 103 &&
      evidence.weights()[0].changed == 2 && evidence.weights()[0].noop == 91,
      "C05 fault setup lacks changed/erase/no-op census");
  Totals totals;
  for (const auto policy : {ps::Policy::height_only, ps::Policy::committed_input_native_depth, ps::Policy::tuple_index_slots}) {
    const auto selection_request = request(policy);
    sweep("C05 pure policy", snapshot, owner, source, evidence, [&](ps::PlanCache& cache) {
      return ps::select(snapshot, source, selection_request,
          policy == ps::Policy::height_only ? std::optional<pr::Evidence>{} : evidence, &cache, ps::CacheUse::read_write);
    }, false, totals);
  }
  auto both = request(ps::Policy::committed_input_native_depth); both.constraint = ps::TupleIndexSlotLimit{"31"};
  sweep("C05 pure dual assessment", snapshot, owner, source, evidence, [&](ps::PlanCache& cache) {
    return ps::select(snapshot, source, both, evidence, &cache, ps::CacheUse::read_write);
  }, false, totals);
  const auto height = request(ps::Policy::height_only);
  sweep("C05 warm pure artifact", snapshot, owner, source, evidence, [&](ps::PlanCache& cache) {
    return ps::select(snapshot, source, height, evidence, &cache, ps::CacheUse::read_write);
  }, true, totals);
  sweep("C05 current height late wrapper", snapshot, owner, source, evidence, [&](ps::PlanCache& cache) {
    return rs::select_current(snapshot, source, owner, height, {}, &cache, ps::CacheUse::read_write);
  }, false, totals);
  sweep("C05 current dual assessment late wrapper", snapshot, owner, source, evidence, [&](ps::PlanCache& cache) {
    return rs::select_current(snapshot, source, owner, both, {}, &cache, ps::CacheUse::read_write);
  }, false, totals);
  check(totals.publication_failures != 0 && totals.assessment_failures != 0 && totals.lowering_failures != 0,
      "C05 full fault sweep missed a required phase");
  std::cout << "C05 persistent positions=" << totals.positions << " recovered_cleanup_positions=" << totals.recovered
      << " publication_failures=" << totals.publication_failures << "; complete owner/workload/cache/old results preserved\n";
} catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; } }

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep persistent ordinary-new failures across pure and current selection stages. |
| inputs / outputs | Uses allocation-counted helper to measure and fail each allocation position for pure depth/slot, dual cap, warm-cache, and current wrappers. |
| invariants | Every measured position is tried; a failing allocation either recovers to the complete equivalent result or returns an allowed stop; one retry follows each whole sweep. |
| ownership | Test-only global new hook observes covered C++ new calls; prior cache image, owner/workload and existing immutable results are retained for comparison. |
| failure | Injected failures must not publish partial cache entries or mutate owners; cleanup and retry are explicitly checked. |
| cost | Seven sweeps: three pure policies, dual assessment, warm artifact, current height, and current dual wrapper. Each uses a measured allocation-count baseline and tests every observed position; counts depend on that invocation, not a fixed source-independent bound. |
| Design | [tests/unit/selection_exception_test.cpp](../../../../../tests/unit/selection_exception_test.cpp), [include/crown/planner/selection.hpp](../../../../../include/crown/planner/selection.hpp), [src/planner/selection.cpp](../../../../../src/planner/selection.cpp), [docs/selection.md](../../../../selection.md), [docs/selection_accounting.md](../../../../selection_accounting.md), [tests/support/selection_exception_support.hpp](../../../../../tests/support/selection_exception_support.hpp) |
