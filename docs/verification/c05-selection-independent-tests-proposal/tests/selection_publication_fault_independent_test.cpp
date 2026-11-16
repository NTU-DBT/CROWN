#include "selection_independent_fixture.hpp"

#include <cstdlib>
#include <iostream>
#include <limits>
#include <new>

namespace {
thread_local bool measuring=false;
thread_local std::size_t calls=0;
thread_local std::size_t remaining=std::numeric_limits<std::size_t>::max();
thread_local bool triggered=false;
[[gnu::noinline]] void before_allocation() {
  if (!measuring) return;
  ++calls;
  if (remaining==0) {triggered=true;throw std::bad_alloc{};}
  if (remaining!=std::numeric_limits<std::size_t>::max()) --remaining;
}
[[gnu::noinline]] void* allocate(std::size_t size) {
  before_allocation();
  if (void* result=std::malloc(size?size:1)) return result;
  throw std::bad_alloc{};
}
[[gnu::noinline]] void* allocate_aligned(std::size_t size,std::size_t alignment) {
  before_allocation();void* result=nullptr;
  if (posix_memalign(&result,alignment,size?size:1)!=0) throw std::bad_alloc{};
  return result;
}
struct Measure {
  explicit Measure(std::size_t fail=std::numeric_limits<std::size_t>::max()) {
    calls=0;remaining=fail;triggered=false;measuring=true;
  }
  ~Measure(){measuring=false;remaining=std::numeric_limits<std::size_t>::max();}
};
} // namespace
[[gnu::noinline]] void* operator new(std::size_t n){return allocate(n);}
[[gnu::noinline]] void* operator new[](std::size_t n){return allocate(n);}
[[gnu::noinline]] void* operator new(std::size_t n,std::align_val_t a){return allocate_aligned(n,static_cast<std::size_t>(a));}
[[gnu::noinline]] void* operator new[](std::size_t n,std::align_val_t a){return allocate_aligned(n,static_cast<std::size_t>(a));}
void* operator new(std::size_t n,const std::nothrow_t&) noexcept{try{return allocate(n);}catch(...){return nullptr;}}
void* operator new[](std::size_t n,const std::nothrow_t&) noexcept{try{return allocate(n);}catch(...){return nullptr;}}
void* operator new(std::size_t n,std::align_val_t a,const std::nothrow_t&) noexcept{try{return allocate_aligned(n,static_cast<std::size_t>(a));}catch(...){return nullptr;}}
void* operator new[](std::size_t n,std::align_val_t a,const std::nothrow_t&) noexcept{try{return allocate_aligned(n,static_cast<std::size_t>(a));}catch(...){return nullptr;}}
[[gnu::noinline]] void operator delete(void* p) noexcept{std::free(p);}
[[gnu::noinline]] void operator delete[](void* p) noexcept{std::free(p);}
void operator delete(void* p,std::size_t) noexcept{std::free(p);}
void operator delete[](void* p,std::size_t) noexcept{std::free(p);}
void operator delete(void* p,std::align_val_t) noexcept{std::free(p);}
void operator delete[](void* p,std::align_val_t) noexcept{std::free(p);}
void operator delete(void* p,std::size_t,std::align_val_t) noexcept{std::free(p);}
void operator delete[](void* p,std::size_t,std::align_val_t) noexcept{std::free(p);}
void operator delete(void* p,const std::nothrow_t&) noexcept{std::free(p);}
void operator delete[](void* p,const std::nothrow_t&) noexcept{std::free(p);}
void operator delete(void* p,std::align_val_t,const std::nothrow_t&) noexcept{std::free(p);}
void operator delete[](void* p,std::align_val_t,const std::nothrow_t&) noexcept{std::free(p);}

namespace {
using namespace c05_independent;
s::Request request(unsigned id) {
  auto value=depth();value.limits.aggregate.score_bits=500U+id;return value;
}
current::CurrentSelection select(const BooleanFixture& f,r::PhysicalRuntime& owner,s::PlanCache& cache,
                                 unsigned id,s::CacheUse use=s::CacheUse::read_write) {
  const auto attempt=current::select_current(f.all,s::Source{s::DirectCQ{}},owner,request(id),{},&cache,use);
  return complete(attempt);
}
struct Scenario {
  s::PlanCache cache;
  current::CurrentSelection a,b;
  Scenario(const BooleanFixture& f,r::PhysicalRuntime& owner):
      cache(s::PlanCache::create({2,8*1024*1024,32*1024*1024})),
      a(select(f,owner,cache,0)),b(select(f,owner,cache,1)) {}
};
struct FaultSummary {std::size_t positions{},publication_failures{},completed_fault_positions{};};
FaultSummary focused(const BooleanFixture& f,r::PhysicalRuntime& owner,bool warm) {
  const auto canonical=owner.canonical_state();
  const auto workload=owner.workload_statistics();
  const auto owner_id=owner.owner();
  const unsigned wanted=warm?0U:2U;
  const s::Source source{s::DirectCQ{}};
  const auto wanted_request=request(wanted);
  Scenario trial(f,owner);
  current::Attempt successful;
  std::size_t measured_calls=0;
  {
    Measure counting;
    successful=current::select_current(f.all,source,owner,wanted_request,{},&trial.cache,s::CacheUse::read_write);
    measured_calls=calls;
  }
  check(successful.selection && measured_calls>8 && measured_calls<100'000,"focused publication baseline failed or exceeded its finite guard");
  const auto expected_key=successful.selection->selection().selected().structural_key();
  const auto expected_plan=successful.selection->selection().plan().physical_sha256();
  const auto expected_statistics=trial.cache.statistics();
  const auto expected_usage=successful.usage;
  std::set<std::size_t> positions{0,1,measured_calls/2};
  for (std::size_t back=1;back<=8;++back) positions.insert(measured_calls-back);
  FaultSummary summary;
  for (const auto position:positions) {
    Scenario value(f,owner);
    const auto before=value.cache.statistics();
    const auto old_key=value.a.selection().selected().structural_key();
    const auto old_plan=value.a.selection().plan().physical_sha256();
    const auto old_binding=value.a.selection().cache_binding();
    const auto old_usage=value.a.selection().usage();
    const auto old_workload=value.a.capture().captured()->workload();
    current::Attempt failed;
    {
      Measure fault(position);
      failed=current::select_current(f.all,source,owner,wanted_request,{},&value.cache,s::CacheUse::read_write);
    }
    check(triggered,"focused persistent allocation position was not reached");
    check(owner.owner()==owner_id && owner.canonical_state()==canonical && same_workload(workload,owner.workload_statistics()),
          "selection OOM changed canonical owner or complete workload context");
    check(value.a.selection().selected().structural_key()==old_key && value.a.selection().plan().physical_sha256()==old_plan &&
          value.a.selection().cache_binding()==old_binding && value.a.selection().usage()==old_usage &&
          same_workload(old_workload,value.a.capture().captured()->workload()) && f.all.original_proof().valid() && f.all.candidate_count()==3,
          "persistent OOM changed old result, capture or factory proof");
    if (failed.selection) {
      // A recovered allocation after publication is not falsely classified as
      // a failed transaction. It must still publish the entire exact result and
      // counters; root reviews any such observed position explicitly.
      check(failed.stop==s::Stop::complete && failed.selection->selection().selected().structural_key()==expected_key &&
            failed.selection->selection().plan().physical_sha256()==expected_plan && value.cache.statistics()==expected_statistics &&
            failed.usage==expected_usage,"fault recovery published a partial result/cache transaction");
      ++summary.completed_fault_positions;
    } else {
      check(failed.stop==s::Stop::allocation_failure && value.cache.statistics()==before,
            "failed publication changed cache counters or converted OOM to fallback");
      if (failed.stage==s::Stage::publication) ++summary.publication_failures;
      // These successful diagnostic hits do not reorder FIFO. Account for them
      // explicitly instead of comparing their changed counters with pre-read values.
      check(select(f,owner,value.cache,0,s::CacheUse::read_only).selection().cache_observation().disposition==s::CacheDisposition::hit &&
            select(f,owner,value.cache,1,s::CacheUse::read_only).selection().cache_observation().disposition==s::CacheDisposition::hit,
            "failed selection lost either preexisting FIFO entry");
      const auto retried=select(f,owner,value.cache,wanted);
      check(retried.selection().selected().structural_key()==expected_key && retried.selection().plan().physical_sha256()==expected_plan,
            "same-owner retry changed exact selected artifact");
      check(retried.selection().cache_observation().disposition==(warm?s::CacheDisposition::hit:s::CacheDisposition::inserted),
            "retry observed a partially installed artifact");
    }
    if (!warm) {
      const auto oldest=select(f,owner,value.cache,0,s::CacheUse::read_only);
      const auto middle=select(f,owner,value.cache,1,s::CacheUse::read_only);
      const auto newest=select(f,owner,value.cache,2,s::CacheUse::read_only);
      check(oldest.selection().cache_observation().disposition==s::CacheDisposition::miss_read_only &&
            middle.selection().cache_observation().disposition==s::CacheDisposition::hit &&
            newest.selection().cache_observation().disposition==s::CacheDisposition::hit,
            "failed/retried publication changed FIFO order");
    }
    auto retained=r::PhysicalRuntime::initialize(value.a.selection().plan(),f.initial);
    check(answers(retained)==Relation{Row{}},"retained old artifact is unusable after fault/retry/eviction");
    ++summary.positions;
  }
  check(summary.publication_failures>0,"focused final positions did not exercise an actual late publication failure");
  return summary;
}
} // namespace
int main(int argc,char** argv) {
  try {
    check(argc==2,"usage: selection_publication_fault_independent_test REPOSITORY_ROOT");
    const auto fixture=boolean_fixture(argv[1]);
    auto owner=r::PhysicalRuntime::initialize(lower(fixture.by_label.at("native_s")),fixture.initial);
    hot(owner,fixture);
    const auto cold=focused(fixture,owner,false);
    const auto warm=focused(fixture,owner,true);
    std::cout<<"C05 focused atomic OOM groups=2 positions="<<cold.positions+warm.positions
             <<" publication_failures="<<cold.publication_failures+warm.publication_failures
             <<" completed_fault_positions="<<cold.completed_fault_positions+warm.completed_fault_positions<<'\n';
  } catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
