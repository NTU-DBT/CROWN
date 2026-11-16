#include "combined_statistics_fixture.hpp"
#include <cstdlib>
#include <iostream>
#include <new>
namespace {
bool injecting=false;std::size_t remaining=0,allocations=0;
[[gnu::noinline]] void* allocate(std::size_t bytes){
  if(injecting){++allocations;if(remaining==0)throw std::bad_alloc{};--remaining;}
  if(auto* p=std::malloc(bytes?bytes:1))return p;
  throw std::bad_alloc{};
}
}
void* operator new(std::size_t n){return allocate(n);}
void* operator new[](std::size_t n){return allocate(n);}
void operator delete(void* p) noexcept{std::free(p);}
void operator delete[](void* p) noexcept{std::free(p);}
void operator delete(void* p,std::size_t) noexcept{std::free(p);}
void operator delete[](void* p,std::size_t) noexcept{std::free(p);}
using namespace combined_fixture;
int main(){
  const auto p=plan();const auto r=request(p);auto db=database();
  auto runtime=DeltaRuntime::initialize(p,db,wf::delta_options());runtime.configure_workload_statistics(wf::enabled());
  wf::apply(runtime,1,SetOperation::insert,{n(8)});db.tables[1].insert(Row{n(8)});
  static_cast<void>(runtime.set_mode(DeltaMode::maintenance));
  const auto before=runtime.canonical_state();const auto baseline=runtime.capture_combined_statistics(r);
  check(baseline.workload().has_previous());const auto owner=runtime.owner();std::size_t failures=0;bool complete=false;
  for(std::size_t position=0;position<1024;++position){
    injecting=true;remaining=position;allocations=0;
    try{auto result=runtime.capture_combined_statistics(r);injecting=false;facts(result,db,1);same_workload(baseline.workload(),result.workload());complete=true;}
    catch(const std::bad_alloc&){injecting=false;++failures;}
    catch(...){injecting=false;throw;}
    check(runtime.owner()==owner && runtime.sequence()==1 && runtime.canonical_state()==before);runtime.check_invariants();
    const auto recovered=runtime.capture_combined_statistics(r);facts(recovered,db,1);same_workload(baseline.workload(),recovered.workload());
    check(runtime.statistics_freshness(baseline.state())==stats::Freshness::current);facts(baseline,db,1);
    if(complete)break;
    check(allocations==position+1);
  }
  check(complete && failures>0);
  std::cout<<"1 combined capture allocation sweep passed; injected failures="<<failures<<'\n';
}
