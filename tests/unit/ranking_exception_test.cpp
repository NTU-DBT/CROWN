#include "ranking_fixture.hpp"
#include "crown/runtime/ranking_evidence.hpp"
#include "candidate_binding.hpp"
#include "frozen_binding_v2.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <new>
#include <tuple>

namespace {
thread_local std::ptrdiff_t fail_after=-1;
thread_local std::size_t allocations=0;
thread_local bool triggered=false;
[[gnu::noinline]] void* allocate(std::size_t n){++allocations;if(fail_after==0){triggered=true;throw std::bad_alloc{};}if(fail_after>0){--fail_after;}if(auto* p=std::malloc(n?n:1)){return p;}throw std::bad_alloc{};}
struct Fault {explicit Fault(std::size_t i){triggered=false;fail_after=static_cast<std::ptrdiff_t>(i);}~Fault(){fail_after=-1;}};
namespace ws=crown::runtime::workload;
auto metadata(const ws::Metadata& m){return std::tuple{m.attempts,m.committed,m.aborted,m.selected,m.complete,m.aborted_selected,m.truncated,m.committed_truncated,m.guards,m.detail_actions,m.cleared_cells,m.merged_cells,m.saturated,m.invalid_descriptor,m.protocol_error,m.ordinal_exhausted};}
auto stamp(const ws::Stamp& s){return std::tuple{s.owner,s.committed_epoch,s.interval_start_epoch,s.reset_generation,s.configuration_generation,s.segment,s.format_version,s.reset_saturated,s.configuration_saturated,s.segment_saturated};}
auto memory(const ws::Memory& m){return std::tuple{m.object_bytes,m.descriptors_bytes,m.committed_bytes,m.attempt_bytes,m.previous_bytes,m.retained_payload_bytes,m.routes_bytes};}
template<class T> bool same(std::span<const T> a,std::span<const T> b){return a.size()==b.size() && std::equal(a.begin(),a.end(),b.begin());}
void same_workload_complete(const ws::Snapshot& a,const ws::Snapshot& b){
  c02_test::check(a.plan().physical_sha256()==b.plan().physical_sha256() && stamp(a.stamp())==stamp(b.stamp()) &&
      a.options()==b.options() && a.modes()==b.modes() && a.previous_modes()==b.previous_modes() &&
      same(a.descriptors(),b.descriptors()) && same(a.cells(),b.cells()) && same(a.previous_cells(),b.previous_cells()) &&
      metadata(a.metadata())==metadata(b.metadata()) && metadata(a.previous_metadata())==metadata(b.previous_metadata()) &&
      memory(a.memory())==memory(b.memory()) && a.pending()==b.pending() && a.has_previous()==b.has_previous() &&
      a.replaced_history()==b.replaced_history() && a.previous_interval_start_epoch()==b.previous_interval_start_epoch() &&
      a.previous_interval_end_epoch()==b.previous_interval_end_epoch() && a.detail_availability()==b.detail_availability(),
      "capture/rank failure changed complete workload snapshot");
}
std::vector<std::string> result_image(const crown::planner::ranking::Result& result){
  std::vector<std::string> out{result.selected().structural_key()};
  for(const auto& score:result.scores()){
    out.push_back(std::string(score.structural_key));out.push_back(std::to_string(score.height));out.push_back(std::string(score.numerator));out.push_back(std::string(score.denominator));out.push_back(std::string(score.slots));
    for(const auto& d:score.depths){out.push_back(std::to_string(d.occurrence.value));out.push_back(std::to_string(d.table.value));out.push_back(std::to_string(d.depth));}
    for(const auto& t:score.table_depths){out.push_back(std::to_string(t.table.value));out.push_back(std::to_string(t.inserts));out.push_back(std::to_string(t.erases));out.push_back(std::string(t.depth_sum));out.push_back(std::string(t.contribution));}
    for(const auto& p:score.populations){out.push_back(std::to_string(p.node.value));out.push_back(std::string(p.records));out.push_back(std::string(p.survivors));out.push_back(std::string(p.parent_support));out.push_back(std::string(p.visible.value_or("unavailable")));}
    for(const auto& t:score.slot_terms){out.push_back(std::to_string(t.relation.value));out.push_back(t.index?std::to_string(t.index->value):"relation");out.push_back(std::to_string(t.width));out.push_back(std::string(t.population));out.push_back(std::string(t.contribution));}
    if(score.modeled_plan)out.push_back(std::string(score.modeled_plan->physical_sha256()));
  }
  return out;
}
}
void* operator new(std::size_t n){return allocate(n);}void* operator new[](std::size_t n){return allocate(n);}
void* operator new(std::size_t n,const std::nothrow_t&) noexcept{try{return allocate(n);}catch(...){return nullptr;}}
void* operator new[](std::size_t n,const std::nothrow_t&) noexcept{try{return allocate(n);}catch(...){return nullptr;}}
void operator delete(void* p) noexcept{std::free(p);}void operator delete[](void* p) noexcept{std::free(p);}
void operator delete(void* p,std::size_t) noexcept{std::free(p);}void operator delete[](void* p,std::size_t) noexcept{std::free(p);}
void operator delete(void* p,const std::nothrow_t&) noexcept{std::free(p);}void operator delete[](void* p,const std::nothrow_t&) noexcept{std::free(p);}
int main(){try{
  using namespace c02_test;namespace pr=planner::ranking;namespace rr=runtime::ranking;
  const auto f=fixture();const auto set=candidates(f);const auto plan=planner::lower_tree(f.catalog,f.query,set.candidate(0)->tree());auto owner=runtime::PhysicalRuntime::initialize(plan,f.database);
  ws::Options enabled;enabled.mode=ws::Mode::counters;owner.configure_workload_statistics(enabled);
  const auto update=[&](std::size_t table,SetOperation op,Row row){static_cast<void>(owner.apply({owner.sequence()+1,TableId{table},op,std::move(row)}));};
  update(0,SetOperation::insert,Row{std::int64_t{1}});update(0,SetOperation::insert,Row{std::int64_t{2}});update(0,SetOperation::erase,Row{std::int64_t{2}});
  update(1,SetOperation::erase,Row{std::int64_t{2},std::int64_t{2}});update(2,SetOperation::insert,Row{std::int64_t{1}});
  update(2,SetOperation::erase,Row{std::int64_t{1}});update(2,SetOperation::insert,Row{std::int64_t{1}});
  const auto owner_id=owner.owner();const auto canonical=owner.canonical_state();const auto workload=owner.workload_statistics();
  check(canonical.sources==f.database.tables && workload.metadata().committed==7 && workload.metadata().attempts==7 && workload.metadata().aborted==0,"fault trace did not restore source state and populate census");
  std::vector<std::string> retained_keys;for(std::size_t i=0;i<set.candidate_count();++i)retained_keys.push_back(set.candidate(i)->structural_key());
  const auto verify=[&]{
    check(owner.owner()==owner_id && owner.sequence()==7 && owner.canonical_state()==canonical && owner.has_answer(),"capture/rank failure changed actual canonical owner");
    same_workload_complete(workload,owner.workload_statistics());
    check(set.valid() && set.original_proof().valid() && set.candidate_count()==retained_keys.size(),"fault changed retained P07 snapshot/proof");
    for(std::size_t i=0;i<retained_keys.size();++i)check(set.candidate(i)->valid() && set.candidate(i)->structural_key()==retained_keys[i],"fault changed candidate key");
  };
  const auto captured=rr::capture(set,owner);check(captured.evidence.has_value(),"baseline capture failed");const auto evidence=captured.evidence->inputs();
  check(evidence.depth_reasons()==0 && evidence.denominator()==7,"nonempty enabled depth census unavailable");
  allocations=0;const auto old=planner::frozen_binding_v2::binding_bytes(f.catalog,f.query);const auto old_count=allocations;
  allocations=0;const auto now=planner::binding_detail::encode(f.catalog,f.query);check(allocations==old_count && now.capacity()==old.capacity() && now==old,"P07 encoder allocation/byte profile changed");
  std::size_t positions=0,recovered=0;
  for(const auto policy:{pr::Policy::height_only,pr::Policy::committed_input_native_depth,pr::Policy::tuple_index_slots}){
    pr::Request request;request.policy=policy;allocations=0;const auto expected=pr::rank(set,request,evidence);const auto count=allocations;
    check(expected.result && count<20'000,"baseline rank/fault guard");
    const auto retained=result_image(*expected.result);const auto retained_usage=expected.result->usage();
    for(std::size_t i=0;i<count;++i){pr::Attempt failed;{Fault fault(i);failed=pr::rank(set,request,evidence);}
      check(triggered,"rank fault position was not reached");
      if(failed.result){check(failed.stop==pr::Stop::complete && result_image(*failed.result)==retained,"recovered cleanup allocation changed result");++recovered;}
      else{check(failed.stop==pr::Stop::allocation_failure,"rank allocation failure changed kind");}
      verify();check(result_image(*expected.result)==retained && expected.result->usage()==retained_usage,"rank failure changed prior Result keys/scores/usage");++positions;
    }
    const auto retry=pr::rank(set,request,evidence);check(retry.result && result_image(*retry.result)==retained,"rank retry changed selection/terms");verify();
  }
  allocations=0;const auto baseline=rr::capture(set,owner);const auto count=allocations;check(baseline.evidence && count<20'000,"capture fault guard");
  for(std::size_t i=0;i<count;++i){rr::CaptureAttempt failed;{Fault fault(i);failed=rr::capture(set,owner);}
    check(triggered && !failed.evidence && failed.stop==pr::Stop::allocation_failure,"capture allocation failure published");verify();++positions;
  }
  const auto retried=rr::capture(set,owner);check(retried.evidence && retried.evidence->inputs().denominator()==7 && retried.evidence->inputs().depth_reasons()==0,"capture retry did not reproduce census");
  check(baseline.evidence->captured().has_value() && retried.evidence->captured().has_value(),"physical capture lost native joint record");
  same_workload_complete(baseline.evidence->captured()->workload(),retried.evidence->captured()->workload());
  check(evidence.sources().size()==3 && set.candidate_count()==3,"input artifacts changed after failure sweeps");
  verify();std::cout<<"C02 transactional allocation positions="<<positions<<" recovered_cleanup_positions="<<recovered<<"; all policies/complete workload/canonical owner stable; P07 prefix allocation profile preserved\n";
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
