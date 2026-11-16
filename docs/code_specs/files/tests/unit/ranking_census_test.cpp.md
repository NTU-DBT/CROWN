# `tests/unit/ranking_census_test.cpp` — block usage map

[Source](../../../../../tests/unit/ranking_census_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `0ad730d80e1f7b3502426011d7195c2ad3ad6c471fdc465466130bca1916b120`. 62 lines partitioned into 6 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–7](../../../../../tests/unit/ranking_census_test.cpp#L1) | Imports dependencies; declares namespace scope. |  · [reviewed contract](#b0001) |
| [B0002 · 8–23](../../../../../tests/unit/ranking_census_test.cpp#L8) | Type/record definition: struct CollectorTestAccess | guard c02_test::check(roots.size()&gt;=2 && detail.has_value(),"census fixture strata");; growth push_back; 2 loop sites · [reviewed contract](#b0002) |
| [B0003 · 24–25](../../../../../tests/unit/ranking_census_test.cpp#L24) | declares namespace scope. |  · [reviewed contract](#b0003) |
| [B0004 · 26–28](../../../../../tests/unit/ranking_census_test.cpp#L26) | Type/record definition: struct StateTestAccess |  · [reviewed contract](#b0004) |
| [B0005 · 29–29](../../../../../tests/unit/ranking_census_test.cpp#L29) | Closes surrounding scope/type. |  · [reviewed contract](#b0005) |
| [B0006 · 30–62](../../../../../tests/unit/ranking_census_test.cpp#L30) | Callable definition: int main() | calls fixture, candidates, planner::lower_tree, candidate; guard if(test==0 \|\| test==2 \|\| test==3 \|\| test==7){check(actual.reasons==0,"irrelevant saturation poisone…; returns 1; growth insert, make_shared; 2 loop sites; source comment (unverified): // This is deliberately an internal pipeline boundary injection, not a · [reviewed contract](#b0006) |

## B0001

[Lines 1–7](../../../../../tests/unit/ranking_census_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L7:sha256:27cd38a9350e318eb38648a94092bd138a7bf4229e8da4f63524ffd2c0a00eef
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ranking_census_test.cpp: include "ranking_fixture.hpp", "ranking_evidence_detail.hpp", "workload_statistics_detail.hpp", "runtime_probe.hpp", &lt;iostream&gt;. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/ranking_census_test.cpp](../../../../../tests/unit/ranking_census_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 8–23](../../../../../tests/unit/ranking_census_test.cpp#L8); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct CollectorTestAccess {
  static void change(Collector& c,unsigned test){
    std::vector<std::size_t> roots;std::optional<std::size_t> detail;
    for(std::size_t i=0;i<c.descriptors_.size();++i){if(c.descriptors_[i].kind==workload::Kind::physical){roots.push_back(i);}else if(!detail){detail=i;}}
    c02_test::check(roots.size()>=2 && detail.has_value(),"census fixture strata");
    if(test==1){c.committed_[roots[0]].saturated=true;}
    if(test==2){c.committed_[*detail].saturated=true;}
    if(test==3){c.meta_.saturated=true;}
    if(test==4){c.meta_.protocol_error=true;}
    if(test==5){c.meta_.invalid_descriptor=true;}
    if(test==6){c.meta_.ordinal_exhausted=true;}
    if(test==7 || test==8){for(auto& x:c.committed_){x={};}auto& a=c.committed_[roots[0]];a.inputs=UINT64_MAX;a.noop=UINT64_MAX;
      if(test==8){auto& b=c.committed_[roots[1]];b.inputs=1;b.noop=1;}}
    if(test==9){c.descriptors_[roots[1]]=c.descriptors_[roots[0]];}
  }
};

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Provide test-only mutations for selected Collector census rows and diagnostic flags. |
| inputs / outputs | Scans collector descriptors to collect physical-root indexes and the first detail index, checks for at least two roots and one detail descriptor, then seeds selected committed counters/metadata for cases 1–9. Cases 7–8 clear committed rows and set maximum input/no-op totals; case 9 duplicates a root descriptor. |
| invariants | Only private Collector state is changed; the seam synthesizes root/detail saturation, metadata protocol flags, denominator overflow and duplicate-root structure without replaying public commits. |
| ownership | Collector references are borrowed; values are written into the test owner state. |
| failure | The helper requires at least two physical roots and one detail descriptor before applying a case; an incompatible fixture fails that check. |
| cost | Scans the descriptor vector, allocates a root-index vector, records a detail index, and for cases 7–8 clears and rewrites all committed cells; its work is not just scalar assignments. |
| Design | [tests/unit/ranking_census_test.cpp](../../../../../tests/unit/ranking_census_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp) |

## B0003

[Lines 24–25](../../../../../tests/unit/ranking_census_test.cpp#L24); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L24-L25:sha256:477aaf0b44b91b27658e7d6f37950525b8a961ff8ef768593271b2f52da2ed0a
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ranking_census_test.cpp: declare the recorded helper API/type boundary. |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/ranking_census_test.cpp](../../../../../tests/unit/ranking_census_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0004

[Lines 26–28](../../../../../tests/unit/ranking_census_test.cpp#L26); `type`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
struct StateTestAccess {
  static void change(State& state,unsigned test){statistics_collection::CollectorTestAccess::change(state.collector_,test);if(test==10){state.configuration_saturated_=true;}}
};

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Route a State test fixture through the collector mutation seam and add the configuration-saturation case. |
| inputs / outputs | Calls CollectorTestAccess::change(state.collector_, test); only for test==10 it also sets state.configuration_saturated_ to true. |
| invariants | Cases 0–9 delegate to collector boundary edits; case 10 marks configuration saturation. No StateStore counter is set to its maximum and no memory-account saturation API is used. |
| ownership | State is borrowed and mutated in place; the delegated seam edits its private Collector, and case 10 writes the State configuration flag. |
| failure | The delegated CollectorTestAccess check fails if root/detail fixture strata are absent; otherwise the seam sets the requested test state. |
| cost | Delegates descriptor scanning, root-vector allocation and committed-cell edits; case 10 adds one configuration-flag write. No maximum-length update sequence is run. |
| Design | [tests/unit/ranking_census_test.cpp](../../../../../tests/unit/ranking_census_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp) |

## B0005

[Lines 29–29](../../../../../tests/unit/ranking_census_test.cpp#L29); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L29-L29:sha256:412ca345ccf75bf9c0806bce695be8de808b79984251a7a54d202cf6101dd451
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Close the recorded declaration scopes in ranking_census_test.cpp: namespace crown::runtime::workload::detail. |
| inputs / outputs | Preceding namespace, type or initializer declarations in; completed lexical boundary out. |
| invariants | Brace-opening context is recorded in root-scope-context-v1.json. These are declaration/initializer boundaries, not an independent update, validation or recovery operation. |
| ownership | Enclosing objects and borrowed fields keep their declared ownership. This punctuation creates no new owner. |
| failure | Malformed scope syntax is a compile error. Any initializer/constructor failure belongs to the enclosing object declaration. |
| cost | No separate loop, guard or engine call is introduced by the delimiter; enclosing initialization and object lifetime still have their actual costs. |
| Design | [tests/unit/ranking_census_test.cpp](../../../../../tests/unit/ranking_census_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0006

[Lines 30–62](../../../../../tests/unit/ranking_census_test.cpp#L30); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(){try{
  using namespace c02_test;namespace pr=planner::ranking;namespace rr=runtime::ranking;namespace ws=runtime::workload;
  const auto f=fixture();const auto set=candidates(f);const auto plan=planner::lower_tree(f.catalog,f.query,set.candidate(0)->tree());
  runtime::PhysicalRuntime metadata_owner(plan);const auto metadata=metadata_owner.workload_statistics();
  for(unsigned test=0;test<=10;++test){ws::detail::State state;ws::Options options;options.mode=ws::Mode::counters;options.period=64;options.detail_budget=0;
    state.configure(plan,true,options,0);const auto ticket=state.physical(TableId{0},SetOperation::insert);state.physical_fact(false);state.finish(ticket,true);
    ws::detail::StateTestAccess::change(state,test);const auto snapshot=state.snapshot(metadata.plan(),runtime::SupportOwnerId{1},1);
    pr::detail::Budget budget(pr::Limits{});const auto actual=rr::detail::classify_census(snapshot,budget);
    if(test==0 || test==2 || test==3 || test==7){check(actual.reasons==0,"irrelevant saturation poisoned exact root census");check(actual.total==(test==7?UINT64_MAX:1),"exact root denominator changed");}
    else if(test==1){check(actual.reasons&pr::reason(pr::Reason::root_saturated),"root saturation lost");}
    else if(test>=4 && test<=6){check(actual.reasons&pr::reason(pr::Reason::protocol),"protocol degradation lost");}
    else if(test==8){check(actual.reasons&pr::reason(pr::Reason::denominator_unavailable),"denominator overflow accepted");check(actual.total==0,"unavailable denominator published partial sum");}
    else if(test==9){check(actual.reasons&pr::reason(pr::Reason::root_incomplete),"duplicate/missing root accepted");}
    else{check(actual.reasons&pr::reason(pr::Reason::interval_saturated),"interval saturation accepted");}
    if(test==7){
      // This is deliberately an internal pipeline boundary injection, not a
      // claim that UINT64_MAX commits were executed on a public runtime.
      auto input=std::make_shared<pr::detail::EvidenceData>(plan);input->binding=pr::detail::binding(f.catalog,f.query,budget);
      input->weights=actual.weights;input->denominator=actual.total;input->depth_reasons=actual.reasons;input->preparation=budget.usage;
      const auto exact=pr::detail::Factory::evidence(std::move(input));pr::Request request;request.policy=pr::Policy::committed_input_native_depth;
      const auto wide=pr::rank(set,request,exact);check(wide.result && wide.evaluated==3,"exact maximum census was narrowed to u64 scores");
      for(const auto& score:wide.result->scores())check(score.denominator=="18446744073709551615" &&
          score.numerator==(shape(score.candidate.tree())==1?"18446744073709551615":"36893488147419103230"),"wide census/depth product changed");
      request.limits.score_bits=64;request.fallback=pr::Fallback::height_only;
      const auto narrow=pr::rank(set,request,exact);check(!narrow.result && narrow.stop==pr::Stop::bit_limit,"wide complete-set resource stop selected a fitting prefix or fallback");
    }
  }
  auto owner=runtime::DeltaRuntime::initialize(plan,f.database);ws::Options enabled;enabled.mode=ws::Mode::counters;owner.configure_workload_statistics(enabled);
  runtime::RuntimeTestProbe::seed_c01_report_saturation(owner);const auto actual=rr::capture(set,owner);
  check(actual.evidence && (actual.evidence->inputs().depth_reasons()&pr::reason(pr::Reason::root_saturated)) &&
      (actual.evidence->inputs().depth_reasons()&pr::reason(pr::Reason::interval_saturated)) && actual.evidence->inputs().memory_reasons()==0,"actual-owner saturation/source separation");
  std::cout<<"C02 census: 11 isolated classifier boundaries, wide score pipeline, actual-owner saturation passed\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Exercise census completeness, saturation, and ranking refusal paths. |
| inputs / outputs | Loops over test values 0–10 to classify eleven isolated collector states, including maximum-root, denominator-overflow, duplicate-root and configuration-saturation cases; test 7 also sends the exact maximum census through ranking. It then separately captures one actual Delta owner after the runtime probe seeds C01 report saturation. |
| invariants | Census facts are independent of sampled detail; a saturated denominator or root is unavailable, and a score-width stop does not become height fallback. |
| ownership | Test seams alter private owner counters only for designated boundary cases; Evidence and Results are immutable captured copies. |
| failure | Every case asserts its explicit stop/reason; no failed score publishes a partial Result. |
| cost | Eleven isolated synthetic collector states plus a separate actual-owner saturation capture; one maximum-root case reaches the wide-score/bit-stop ranking path. Descriptor and candidate work is fixture-bounded, not a huge commit run. |
| Design | [tests/unit/ranking_census_test.cpp](../../../../../tests/unit/ranking_census_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp) |
