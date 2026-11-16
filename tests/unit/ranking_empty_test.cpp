#include "ranking_fixture.hpp"
#include "crown/runtime/ranking_evidence.hpp"
#include <iostream>
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
