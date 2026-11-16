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
    out.push_back(score.structural_key);out.push_back(std::to_string(score.height));out.push_back(score.numerator);out.push_back(score.denominator);out.push_back(score.slots);
    for(const auto& d:score.depths){out.push_back(std::to_string(d.occurrence.value));out.push_back(std::to_string(d.table.value));out.push_back(std::to_string(d.depth));}
    for(const auto& t:score.table_depths){out.push_back(std::to_string(t.table.value));out.push_back(std::to_string(t.inserts));out.push_back(std::to_string(t.erases));out.push_back(t.depth_sum);out.push_back(t.contribution);}
    for(const auto& p:score.populations){out.push_back(std::to_string(p.node.value));out.push_back(p.records);out.push_back(p.survivors);out.push_back(p.parent_support);out.push_back(p.visible.value_or("unavailable"));}
    for(const auto& t:score.slot_terms){out.push_back(std::to_string(t.relation.value));out.push_back(t.index?std::to_string(t.index->value):"relation");out.push_back(std::to_string(t.width));out.push_back(t.population);out.push_back(t.contribution);}
    if(score.modeled_plan)out.push_back(score.modeled_plan->physical_sha256());
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
