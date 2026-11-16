#include "ranking_fixture.hpp"
#include "crown/runtime/ranking_evidence.hpp"
#include <array>
#include <iostream>
#include <type_traits>

int main(){try{
  using namespace c02_test;namespace pr=planner::ranking;namespace rr=runtime::ranking;
  static_assert(!std::is_default_constructible_v<pr::Evidence> && !std::is_default_constructible_v<pr::Result>);
  const auto f=fixture();const auto set=candidates(f);const auto plan=planner::lower_tree(f.catalog,f.query,set.candidate(0)->tree());
  auto owner=runtime::PhysicalRuntime::initialize(plan,f.database);
  auto off=rr::capture(set,owner);check(off.evidence.has_value(),"disabled evidence missing");
  check(off.evidence->inputs().memory_reasons()==0 && off.evidence->inputs().depth_reasons()!=0,"state/workload availability collapsed");
  const auto eligible=rr::revalidate(*off.evidence,owner);check(eligible.boundary==0 && eligible.usable(pr::Policy::tuple_index_slots) && !eligible.usable(pr::Policy::committed_input_native_depth),"policy revalidation collapsed");
  pr::Request memory;memory.policy=pr::Policy::tuple_index_slots;const auto m=pr::rank(set,memory,off.evidence->inputs());
  check(m.result && m.evaluated==3,"memory ranking incomplete");
  for(const auto& score:m.result->scores()){check(score.slots==(shape(score.candidate.tree())==0?"24":"32"),"literal slot oracle mismatch");check(!score.slot_terms.empty() && !score.populations.empty() && score.modeled_plan.has_value(),"slot derivation missing");}
  check(shape(m.result->selected().tree())==0,"memory preferred wrong shape");
  runtime::workload::Options collect;collect.mode=runtime::workload::Mode::counters;collect.period=64;collect.detail_budget=0;owner.configure_workload_statistics(collect);
  for(std::size_t table=0;table<3;++table){const std::size_t n=table==0?90:5;for(std::size_t i=0;i<n;++i){static_cast<void>(owner.apply({owner.sequence()+1,TableId{table},SetOperation::insert,*f.database.tables[table].begin()}));}}
  auto facts=rr::capture(set,owner);check(facts.evidence && facts.evidence->inputs().depth_reasons()==0,"sample/truncation invalidated census");
  pr::Request depth;depth.policy=pr::Policy::committed_input_native_depth;
  const auto d=pr::rank(set,depth,facts.evidence->inputs());check(d.result && d.evaluated==3,"depth ranking incomplete");
  const std::array<std::string,3> expected{"195","105","190"};
  for(const auto& score:d.result->scores()){check(score.numerator==expected[static_cast<std::size_t>(shape(score.candidate.tree()))] && score.denominator=="100","literal depth oracle mismatch");check(score.depths.size()==3 && score.table_depths.size()==3,"depth derivation missing");}
  check(shape(d.result->selected().tree())==1 && owner.has_answer(),"hot-R ranking or semantics");
  auto tiny=depth;tiny.limits.score_bits=1;tiny.fallback=pr::Fallback::height_only;
  const auto failed=pr::rank(set,tiny,facts.evidence->inputs());check(failed.stop==pr::Stop::bit_limit && !failed.result,"resource stop invoked fallback");
  auto work=memory;work.limits.lowering_work=0;const auto lower_stop=pr::rank(set,work,off.evidence->inputs());check(!lower_stop.result && lower_stop.stop==pr::Stop::lowering_limit,"lowering cap ignored");
  owner.reset_workload_statistics();const auto old=rr::revalidate(*facts.evidence,owner);
  check(old.boundary==0 && old.usable(pr::Policy::tuple_index_slots) && !old.usable(pr::Policy::committed_input_native_depth),"reset conflated state and interval freshness");
  const auto immutable=pr::rank(set,depth,facts.evidence->inputs());check(immutable.result && immutable.result->selected().structural_key()==d.result->selected().structural_key(),"as-of artifact changed on reset");
  const auto empty=rr::rank_current(set,owner,depth);check(empty.stop==pr::Stop::evidence_unavailable && !empty.result,"empty current interval reused old weights");
  depth.fallback=pr::Fallback::height_only;const auto fallback=rr::rank_current(set,owner,depth);check(fallback.result && fallback.result->effective_policy()==pr::Policy::height_only && fallback.result->fallback_reasons()!=0,"explicit fallback missing");
  auto pending=owner.prepare({owner.sequence()+1,TableId{0},SetOperation::insert,Row{std::int64_t{2}}});const auto p=rr::capture(set,owner);
  check(p.evidence && (p.evidence->inputs().memory_reasons()&pr::reason(pr::Reason::pending)),"pending state was exposed");pending.rollback();
  auto foreign=owner.rebuilt();check(rr::revalidate(*facts.evidence,foreign).boundary&pr::reason(pr::Reason::foreign_owner),"rebuilt owner was accepted as current");
  const auto h=pr::rank(set);check(h.result && h.result->scores().size()==3,"pure height ranking");
  for(const auto& score:h.result->scores()){check(score.structural_key>=h.result->selected().structural_key(),"height tie not full key order");}
  std::cout<<"C02 contract: typed complete-set policies, terms, current/as-of, caps passed\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
