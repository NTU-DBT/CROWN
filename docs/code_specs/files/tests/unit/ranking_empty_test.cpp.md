# `tests/unit/ranking_empty_test.cpp` — block usage map

[Source](../../../../../tests/unit/ranking_empty_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `a2fa51ebc78d442d9c00efcbef2a19a909242331ae18d4a0688e0c9b1fce8dca`. 36 lines partitioned into 2 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–3](../../../../../tests/unit/ranking_empty_test.cpp#L1) | Imports dependencies. |  · [reviewed contract](#b0001) |
| [B0002 · 4–36](../../../../../tests/unit/ranking_empty_test.cpp#L4) | Callable definition: int main() | calls emplace_back, push_back, std::move, candidates; guard const auto ranked=rr::rank_current(set,owner,request);check(ranked.result.has_value(),"single-atom …; returns 1; growth emplace_back, push_back; 2 loop sites · [reviewed contract](#b0002) |

## B0001

[Lines 1–3](../../../../../tests/unit/ranking_empty_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L3:sha256:53351eb45ff3daa3bd5caa1e58454875f26f74138debacb8235ad36f5c4980bc
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ranking_empty_test.cpp: include "ranking_fixture.hpp", "crown/runtime/ranking_evidence.hpp", &lt;iostream&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/ranking_empty_test.cpp](../../../../../tests/unit/ranking_empty_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 4–36](../../../../../tests/unit/ranking_empty_test.cpp#L4); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(){try{
  using namespace c02_test;namespace pr=planner::ranking;namespace rr=runtime::ranking;
  for(bool nullary:{false,true}){
    Fixture f;f.catalog.tables={{"T",{{"x",ScalarType::int64}}}};
    if(!nullary){f.query.variables={{"x",ScalarType::int64}};}
    Atom atom{"t",TableId{0},{}};
    if(nullary){atom.terms.emplace_back(IgnoredColumn{});}else{atom.terms.emplace_back(VariableId{0});}
    f.query.atoms.push_back(std::move(atom));
    f.database.tables={Relation{Row{std::int64_t{1}},Row{std::int64_t{2}},Row{std::int64_t{3}}}};
    const auto set=candidates(f,1,0);const auto plan=planner::lower_tree(f.catalog,f.query,set.candidate(0)->tree());
    auto owner=runtime::PhysicalRuntime::initialize(plan,f.database);pr::Request request;request.policy=pr::Policy::tuple_index_slots;
    const auto ranked=rr::rank_current(set,owner,request);check(ranked.result.has_value(),"single-atom memory unavailable");
    check(ranked.result->scores()[ranked.result->selected_index()].slots==(nullary?"4":"14"),"nullary/unary slot oracle");
    rr::CaptureOptions options;options.state_limits.rows=0;options.state_limits.distinct_keys=0;
    const auto cardinality=rr::capture(set,owner,options);check(cardinality.evidence && cardinality.evidence->inputs().memory_reasons()==0,"cardinality capture scanned rows/keys");
    options.state_limits.work=0;const auto unavailable=rr::capture(set,owner,options);
    check(unavailable.evidence && (unavailable.evidence->inputs().memory_reasons()&pr::reason(pr::Reason::source_budget_exhausted)),"source work budget lost reason");
    check(unavailable.evidence->inputs().capture_accounting().state==pr::CaptureState::budget_exhausted,"source budget status lost");
    const auto strict=pr::rank(set,request,unavailable.evidence->inputs());check(strict.stop==pr::Stop::evidence_unavailable && !strict.result,"source-budget require-evidence");
    request.fallback=pr::Fallback::height_only;const auto fallback=pr::rank(set,request,unavailable.evidence->inputs());check(fallback.result && fallback.result->fallback_reasons()&pr::reason(pr::Reason::source_budget_exhausted),"source-budget configured fallback");
    request.limits.work=0;const auto resource=rr::rank_current(set,owner,request);check(resource.stop==pr::Stop::work_limit && !resource.result,"processing zero work fell back");
    request.limits.work=1'000'000;f.database.tables[0].clear();auto empty=runtime::PhysicalRuntime::initialize(plan,f.database);
    const auto zero=rr::rank_current(set,empty,request);check(zero.result && zero.result->scores()[zero.result->selected_index()].slots=="0","empty source is not exact zero");
  }
  for(bool contradiction:{false,true}){
    Fixture f;f.query.contradiction=contradiction;const auto set=candidates(f,0,0);
    auto owner=runtime::PhysicalRuntime::initialize(planner::lower_tree(f.catalog,f.query,set.candidate(0)->tree()),f.database);
    pr::Request memory;memory.policy=pr::Policy::tuple_index_slots;const auto zero=rr::rank_current(set,owner,memory);
    check(zero.result && zero.result->selected().height()==0 && zero.result->scores()[zero.result->selected_index()].slots=="0","constant operator did not have exact zero slot proxy");
    check(owner.has_answer()==!contradiction,"ranking changed constant operator answer");
  }
  std::cout<<"C02 nullary/unary/empty/constant and capture-vs-processing budgets passed\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Check ranking facts for empty sources and zero-node constant routes. |
| inputs / outputs | Builds nullary/unary fixtures with empty and nonempty rows, captures zero-cardinality sources, then ranks under source-work and C02 processing limits. |
| invariants | Zero source rows/keys do not erase exact cardinality; zero-node true and false constants retain their Boolean results; a processing work stop is distinct from source evidence unavailability. |
| ownership | Captured Evidence is an as-of copy; candidate snapshots and Results retain their own handles. |
| failure | Zero C01 work can make source facts unavailable; zero C02 processing work returns work_limit, not a partial result. |
| cost | Four cardinality shapes plus two constant routes and several bounded rank calls; empty scans do not imply no capture/setup cost. |
| Design | [tests/unit/ranking_empty_test.cpp](../../../../../tests/unit/ranking_empty_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp) |
