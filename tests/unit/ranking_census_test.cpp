#include "ranking_fixture.hpp"
#include "ranking_evidence_detail.hpp"
#include "workload_statistics_detail.hpp"
#include "runtime_probe.hpp"
#include <iostream>

namespace crown::runtime::statistics_collection {
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
}
namespace crown::runtime::workload::detail {
struct StateTestAccess {
  static void change(State& state,unsigned test){statistics_collection::CollectorTestAccess::change(state.collector_,test);if(test==10){state.configuration_saturated_=true;}}
};
}
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
