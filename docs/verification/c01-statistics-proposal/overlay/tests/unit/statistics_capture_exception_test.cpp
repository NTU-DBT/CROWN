#include "crown/runtime/statistics.hpp"
#include <cstdlib>
#include <new>
#include <stdexcept>
#include <iostream>
namespace {
bool injecting=false;
std::size_t remaining=0, allocations=0;
void* allocate(std::size_t n) {
  if(injecting){++allocations;if(remaining==0)throw std::bad_alloc{};--remaining;}
  if(auto* p=std::malloc(n?n:1))return p;
  throw std::bad_alloc{};
}
void check(bool b){if(!b)throw std::runtime_error("capture allocation exception assertion");}
}
void* operator new(std::size_t n){return allocate(n);}
void* operator new[](std::size_t n){return allocate(n);}
void operator delete(void* p) noexcept{std::free(p);}
void operator delete[](void* p) noexcept{std::free(p);}
void operator delete(void* p,std::size_t) noexcept{std::free(p);}
void operator delete[](void* p,std::size_t) noexcept{std::free(p);}
int main(){
  using namespace crown;using namespace crown::storage;namespace stats=crown::runtime::statistics;
  TupleLayout layout{LayoutId{1},{{ScalarType::string},{ScalarType::int64}}};
  TupleLayout keys{LayoutId{2},{{ScalarType::string}}};Projection p{layout,keys,{FieldId{0}}};
  ReferenceTable table{RelationId{1},layout};
  for(std::int64_t i=0;i<7;++i)static_cast<void>(table.insert(layout.tuple({std::string(128,static_cast<char>('a'+i%3)),i})));
  const auto id=table.add_index(p); const auto revision=table.revision();
  const auto before=table.snapshot();const auto owner=table.owner();
  stats::Budget baseline_budget;const auto baseline=stats::index(table,id,baseline_budget);
  std::size_t total_failures=0;
  // Each k fails the kth allocation in the SAME unchanged owner. The first
  // successful run proves every prior allocation point was visited and failed.
  for(bool use_index:{false,true}){
    bool reached_success=false;
    for(std::size_t k=0;k<512;++k){
      stats::Budget budget;remaining=k;allocations=0;injecting=true;
      bool failed=false;
      try {
        auto captured=use_index?stats::index(table,id,budget):stats::projection(table,p,budget);
        injecting=false;
        check(captured.distribution.completion==stats::Completion::exact && captured.distribution.ndv==3);
        reached_success=true;
      } catch(const std::bad_alloc&) {injecting=false;failed=true;++total_failures;}
      catch(...) {injecting=false;throw;}
      check(table.owner()==owner && table.revision()==revision && table.snapshot()==before);
      check(baseline.distribution.ndv==3 && baseline.distribution.heavy_keys->front().count==3);
      table.check_invariants();
      // Recovery capture after every failure, with fresh budget and no injector.
      stats::Budget recovery_budget;
      auto recovery=use_index?stats::index(table,id,recovery_budget):stats::projection(table,p,recovery_budget);
      check(recovery.distribution.ndv==3 && recovery.distribution.histogram==baseline.distribution.histogram);
      if(reached_success){check(k>0);break;}
      check(failed && allocations==k+1);
    }
    check(reached_success);
  }
  std::cout<<"2 capture allocation sweeps passed; injected failures="<<total_failures<<'\n';
}
