#include "ranking_exception_support.hpp"

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
