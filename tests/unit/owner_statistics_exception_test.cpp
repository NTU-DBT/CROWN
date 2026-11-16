#include "owner_statistics_fixture.hpp"
#include <cstdlib>
#include <new>
#include <iostream>
namespace {
bool injecting=false;std::size_t remaining=0,allocations=0;
[[gnu::noinline]] void* allocate(std::size_t n){
  if(injecting){++allocations;if(remaining==0)throw std::bad_alloc{};--remaining;}
  if(auto* p=std::malloc(n?n:1))return p;
  throw std::bad_alloc{};
}
}
void* operator new(std::size_t n){return allocate(n);}
void* operator new[](std::size_t n){return allocate(n);}
void operator delete(void* p) noexcept{std::free(p);}
void operator delete[](void* p) noexcept{std::free(p);}
void operator delete(void* p,std::size_t) noexcept{std::free(p);}
void operator delete[](void* p,std::size_t) noexcept{std::free(p);}
using namespace owner_fixture;
template<class Runtime> std::size_t sweep(Runtime& runtime,const stats::OwnerRequest& request){
  const auto before=runtime.canonical_state();const auto owner=runtime.owner();const auto seq=runtime.sequence();
  const auto baseline=runtime.capture_statistics(request);std::size_t failures=0;bool succeeded=false;
  for(std::size_t position=0;position<1024;++position){
    injecting=true;remaining=position;allocations=0;
    try{auto output=runtime.capture_statistics(request);injecting=false;same_facts(output,baseline);succeeded=true;}
    catch(const std::bad_alloc&){injecting=false;++failures;}
    catch(...){injecting=false;throw;}
    check(runtime.owner()==owner && runtime.sequence()==seq && runtime.canonical_state()==before);
    check(runtime.statistics_freshness(baseline)==stats::Freshness::current);runtime.check_invariants();
    same_facts(runtime.capture_statistics(request),baseline);
    if(succeeded){check(position>0);break;}
    check(allocations==position+1);
  }
  check(succeeded);return failures;
}
std::size_t copy_sweep(const stats::OwnerCapture& before,const stats::OwnerCapture& after){
  std::size_t failures=0;bool succeeded=false;
  for(std::size_t position=0;position<1024;++position){
    auto target=before;injecting=true;remaining=position;allocations=0;
    try{target=after;injecting=false;succeeded=true;}
    catch(const std::bad_alloc&){injecting=false;++failures;}
    catch(...){injecting=false;throw;}
    if(succeeded){same_facts(target,after);check(target.stamp().sequence==after.stamp().sequence);break;}
    check(allocations==position+1);same_facts(target,before);
    check(target.stamp().owner==before.stamp().owner && target.stamp().sequence==before.stamp().sequence);
  }
  check(succeeded && failures>0);return failures;
}
int main(){
  const auto p=plan();const auto r=request(p);auto physical=PhysicalRuntime::initialize(p,database());
  auto failures=sweep(physical,r);
  SupportRuntime support{p};
  static_cast<void>(support.apply({1,NodeId{0},SetOperation::insert,{n(1),n(7)}}));
  static_cast<void>(support.apply({2,NodeId{0},SetOperation::insert,{n(2),n(7)}}));
  static_cast<void>(support.apply({3,NodeId{1},SetOperation::insert,{n(7)}}));
  failures+=sweep(support,r);
  const auto before=physical.capture_statistics(r);
  static_cast<void>(physical.apply({1,TableId{1},SetOperation::insert,{n(8)}}));
  failures+=copy_sweep(before,physical.capture_statistics(r));
  std::cout<<"2 owner capture and 1 owning-report copy allocation sweeps passed; injected failures="<<failures<<'\n';
}
