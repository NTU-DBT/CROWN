# `tests/unit/ranking_normalized_exception_test.cpp` — block usage map

[Source](../../../../../tests/unit/ranking_normalized_exception_test.cpp) · [Source index](../../../README.md) · [Subsystem contracts](../../../subsystem_contracts.md) · [Reviewed primitives](../../../primitives.md)

Exercise a named contract using assertions, fixtures, differential oracles or controlled fault injection.

Snapshot SHA-256: `e1b1a5d9b778b8b4d521b3ba8a21765ff17143eaf7c387ae58c9846f6d2f0dc3`. 52 lines partitioned into 2 blocks using `lexical_cpp`. Line ranges apply to these bytes; regenerate after a source edit.

Module context: [tests](../../../subsystem_contracts.md#tests). This context is not assigned as an invariant to imports, declarations or scope closures. Design: [docs/code_review.md](../../../../code_review.md), [docs/reference_fuzz.md](../../../../reference_fuzz.md), [docs/task_ledger.md](../../../../task_ledger.md).

The table is a structural inspection map, not a usage proof. Local calls/guards/returns/growth are syntax observations; full lists are in the coverage manifest. Separately reviewed seven-field contracts follow only where supplied.

| Block / lines | Observed role / declaration | Local body evidence |
| --- | --- | --- |
| [B0001 · 1–2](../../../../../tests/unit/ranking_normalized_exception_test.cpp#L1) | Imports dependencies. |  · [reviewed contract](#b0001) |
| [B0002 · 3–52](../../../../../tests/unit/ranking_normalized_exception_test.cpp#L3) | Callable definition: int main() | calls fixture, frontend::bind_sql, check, frontend::normalize_sql; guard auto bound=frontend::bind_sql(sql,f.catalog);check(std::holds_alternative&lt;frontend::BoundSql&gt;(bound…; returns 1; growth insert, push_back; 7 loop sites · [reviewed contract](#b0002) |

## B0001

[Lines 1–2](../../../../../tests/unit/ranking_normalized_exception_test.cpp#L1); `declarations-or-scaffolding`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
@source-span:L1-L2:sha256:ecb1ed23a7d2d96fbd1de54bbc3c7a3cdc672553869045fea4c1d523046e79ac
```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Prepare ranking_normalized_exception_test.cpp: include "ranking_exception_support.hpp". |
| inputs / outputs | Compiler-visible dependencies, names and the recorded declarations in; declarations available to the following fixture/CLI/example definitions out. |
| invariants | Declarations are scoped to this source/header and its selected ABI. Included code has its own effects; names and editable fixture values do not confer proof, admission or publication authority. |
| ownership | Aliases/includes do not create a query owner. Pointers/references/views are non-owning. Containers own their elements, which can themselves be borrowed pointers or numeric IDs. Only documented owning shared-control handles retain controls; IDs/slot-handle values do not independently keep an arena/runtime alive. |
| failure | Missing headers, ill-formed names/types, failed static assertions or active #error directives stop compilation. No runtime rejection/rollback mechanism is implemented by aliases or function prototypes. |
| cost | Preprocessing and type/constraint instantiation cost compilation. Alias/prototype syntax does not invoke the declared operation; any included definitions keep their own initialization effects. |
| Design | [tests/unit/ranking_normalized_exception_test.cpp](../../../../../tests/unit/ranking_normalized_exception_test.cpp), [docs/ranking.md](../../../../ranking.md), [docs/code_review.md](../../../../code_review.md) |

## B0002

[Lines 3–52](../../../../../tests/unit/ranking_normalized_exception_test.cpp#L3); `callable`; `contains_scoped_manual_contract`.

The contract is scoped to its anchor, not a proof of every declaration sharing this line range.

```text
int main(){try{
  using namespace c02_test;namespace pr=planner::ranking;namespace rr=runtime::ranking;
  const auto f=fixture();
  const std::string sql="SELECT EXISTS (SELECT 1 FROM \"R\" JOIN \"S\" ON \"R\".x=\"S\".x JOIN \"T\" ON \"S\".y=\"T\".y WHERE \"R\".x>=0)";
  auto bound=frontend::bind_sql(sql,f.catalog);check(std::holds_alternative<frontend::BoundSql>(bound),"normalized fault binding failed");
  auto normalized=frontend::normalize_sql(std::get<frontend::BoundSql>(bound));check(std::holds_alternative<frontend::NormalizedSql>(normalized),"normalized fault normalization failed");
  const auto program=std::get<frontend::NormalizedSql>(std::move(normalized));
  const Fixture logical{program.core_catalog,program.core,{}};const auto set=candidates(logical);
  const auto plan=planner::lower_normalized(program,set.candidate(0)->tree());auto owner=runtime::PhysicalRuntime::initialize(plan,f.database);
  ws::Options enabled;enabled.mode=ws::Mode::counters;owner.configure_workload_statistics(enabled);
  const auto update=[&](std::size_t table,SetOperation op,Row row){static_cast<void>(owner.apply({owner.sequence()+1,TableId{table},op,std::move(row)}));};
  update(0,SetOperation::insert,Row{std::int64_t{1}});update(0,SetOperation::insert,Row{std::int64_t{2}});update(0,SetOperation::erase,Row{std::int64_t{2}});
  update(1,SetOperation::erase,Row{std::int64_t{2},std::int64_t{2}});update(2,SetOperation::insert,Row{std::int64_t{1}});
  update(2,SetOperation::erase,Row{std::int64_t{1}});update(2,SetOperation::insert,Row{std::int64_t{1}});
  const auto id=owner.owner();const auto canonical=owner.canonical_state();const auto workload=owner.workload_statistics();
  check(canonical.sources==f.database.tables && workload.metadata().committed==7,"normalized trace changed final source set");
  std::vector<std::string> keys;for(std::size_t i=0;i<set.candidate_count();++i)keys.push_back(set.candidate(i)->structural_key());
  const auto verify=[&]{
    check(owner.owner()==id && owner.sequence()==7 && owner.canonical_state()==canonical && owner.has_answer(),"normalized fault changed canonical owner");
    same_workload_complete(workload,owner.workload_statistics());
    check(set.valid() && set.original_proof().valid() && set.candidate_count()==keys.size(),"normalized fault changed snapshot/proof");
    for(std::size_t i=0;i<keys.size();++i)check(set.candidate(i)->valid() && set.candidate(i)->structural_key()==keys[i],"normalized fault changed key");
  };
  const auto captured=rr::capture(set,owner);check(captured.evidence && captured.evidence->inputs().depth_reasons()==0,"normalized fault capture failed");
  const auto evidence=captured.evidence->inputs();std::size_t positions=0,recovered=0;
  for(const auto policy:{pr::Policy::height_only,pr::Policy::committed_input_native_depth,pr::Policy::tuple_index_slots}){
    pr::Request request;request.policy=policy;allocations=0;const auto expected=pr::rank(set,request,evidence);const auto count=allocations;
    check(expected.result && count<100'000,"normalized rank/fault position guard");
    const auto retained=result_image(*expected.result);const auto usage=expected.result->usage();
    if(policy==pr::Policy::tuple_index_slots){std::vector<std::string> scores;for(const auto& score:expected.result->scores()){
        check(score.modeled_plan && score.modeled_plan->normalized() && score.modeled_plan->normalized()->binding.source==sql,"normalized candidate lost owned replay program");scores.push_back(std::string(score.slots));}
      std::sort(scores.begin(),scores.end());check(scores==std::vector<std::string>{"24","32","32"},"normalized literal memory oracle changed");}
    if(policy==pr::Policy::committed_input_native_depth){std::vector<std::string> scores;for(const auto& score:expected.result->scores()){check(score.denominator=="7","normalized physical denominator changed");scores.push_back(std::string(score.numerator));}
      std::sort(scores.begin(),scores.end());check(scores==std::vector<std::string>{"10","10","13"},"normalized literal depth oracle changed");}
    for(std::size_t i=0;i<count;++i){pr::Attempt attempt;{Fault fault(i);attempt=pr::rank(set,request,evidence);}
      check(triggered,"normalized rank injection was not reached");
      if(attempt.result){check(attempt.stop==pr::Stop::complete && result_image(*attempt.result)==retained,"normalized cleanup recovery changed complete result");++recovered;}
      else{check(attempt.stop==pr::Stop::allocation_failure || attempt.stop==pr::Stop::lowering_limit,"normalized allocation failure changed resource kind");}
      verify();check(result_image(*expected.result)==retained && expected.result->usage()==usage,"normalized replay failure rewrote prior result");++positions;
    }
    const auto retry=pr::rank(set,request,evidence);check(retry.result && result_image(*retry.result)==retained,"normalized retry changed complete result");verify();
  }
  allocations=0;const auto baseline=rr::capture(set,owner);const auto count=allocations;check(baseline.evidence && count<100'000,"normalized capture position guard");
  for(std::size_t i=0;i<count;++i){rr::CaptureAttempt attempt;{Fault fault(i);attempt=rr::capture(set,owner);}
    check(triggered && !attempt.evidence && attempt.stop==pr::Stop::allocation_failure,"normalized capture failed nontransactionally");verify();++positions;
  }
  const auto retry=rr::capture(set,owner);check(retry.evidence && retry.evidence->captured() && baseline.evidence->captured(),"normalized capture retry lost native record");
  same_workload_complete(baseline.evidence->captured()->workload(),retry.evidence->captured()->workload());verify();
  std::cout<<"C02 normalized replay allocation positions="<<positions<<" recovered_cleanup_positions="<<recovered<<"; complete owner/workload/result preserved\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}

```

| Field | Reviewed usage contract |
| --- | --- |
| purpose | Sweep ordinary C++ new failure positions across normalized C02 ranking and standalone owner evidence capture. |
| inputs / outputs | Builds a normalized three-table R/S/T join, applies seven committed update attempts, then measures and sweeps height, depth and slot ranking separately. It then measures and sweeps rr::capture as a distinct fourth phase. |
| invariants | Each rank position either returns an equivalent complete Result (cleanup may recover) or an allowed allocation/lowering stop; capture-position failures return no Evidence. Owner, workload, snapshot and retained results stay unchanged, with a retry after each sweep. |
| ownership | The source owner/workload and earlier Result/Evidence snapshots remain the comparison baseline; fault state is test-only global instrumentation. |
| failure | The test-only replacement-new hook injects persistent failures at measured C++ new positions; three rank sweeps permit cleanup recovery, while the separate capture sweep requires allocation_failure and no partial Evidence. No raw malloc/realloc sweep is claimed. |
| cost | Three policy-specific rank sweeps plus one separate capture sweep; each counts its own observed C++ new positions under a 100,000-position guard and runs a retry after the sweep. This does not cover raw system allocation or power loss. |
| Design | [tests/unit/ranking_normalized_exception_test.cpp](../../../../../tests/unit/ranking_normalized_exception_test.cpp), [include/crown/planner/ranking.hpp](../../../../../include/crown/planner/ranking.hpp), [docs/ranking.md](../../../../ranking.md), [docs/ranking_accounting.md](../../../../ranking_accounting.md), [include/crown/runtime/ranking_evidence.hpp](../../../../../include/crown/runtime/ranking_evidence.hpp), [src/runtime/ranking_evidence.cpp](../../../../../src/runtime/ranking_evidence.cpp) |
