#include "statistics_collection.hpp"
#include <cassert>
#include <cstdlib>
#include <limits>
#include <new>
#include <stdexcept>
namespace crown::runtime::statistics_collection {
struct CollectorTestAccess {
  static void generation_max(Collector& c) { c.generation_=std::numeric_limits<U64>::max(); }
  static void ordinal_max(Collector& c) { c.ordinal_=std::numeric_limits<U64>::max(); }
  static void attempts_max(Collector& c) { c.meta_.attempts=std::numeric_limits<U64>::max(); }
};
}
using namespace crown::runtime::statistics_collection;
namespace {
long fail_after=-1;
std::size_t allocations=0;
void* allocate(std::size_t n) {
  if (fail_after==0) throw std::bad_alloc();
  if (fail_after>0) --fail_after;
  ++allocations;
  if (auto* p=std::malloc(n?n:1)) return p;
  throw std::bad_alloc();
}
constexpr Descriptor descriptors[] = {
  {Kind::physical,7,0,Operation::insert},
  {Kind::physical,7,0,Operation::erase},
  {Kind::degree,7,10,Operation::insert},
  {Kind::support,7,11,Operation::insert},
  {Kind::occurrence,7,12,Operation::insert},
  {Kind::degree,7,10,Operation::erase}
};
Options enabled() { Options o; o.mode=Mode::counters; return o; }
void transactions() {
  Collector c; c.configure(enabled(),descriptors);
  auto r=c.begin(0,true); auto n=c.nest(r);
  c.degree(2,5); assert(c.finish(n,true));
  assert(c.committed()[0].inputs==0 && c.metadata().committed==0);
  assert(!c.reset() && !c.rotate(1));
  assert(c.finish(r,true)); assert(c.committed()[2].sum==5);
  r=c.begin(0,true); n=c.nest(r); c.degree(2,99);
  assert(!c.finish(n,false)); assert(!c.finish(r,true));
  assert(c.committed()[2].sum==5 && c.metadata().aborted_selected==1);
  r=c.begin(0,true); n=c.nest(r);
  assert(!c.finish(r,true)); assert(!c.finish(n,true)); assert(!c.finish(r,true));
  assert(!c.pending() && c.metadata().committed==1);
  r=c.begin(0,true); n=c.nest(r); assert(c.finish(n,true));
  auto n2=c.nest(r); assert(!c.finish(n,true)); // stale same-depth ticket
  assert(!c.finish(n2,true)); assert(!c.finish(r,true));
}
void sampling_and_noops() {
  Collector c; auto o=enabled(); o.period=3; o.offset=1; c.configure(o,descriptors);
  for (int i=0;i<10;++i) {
    auto r=c.begin(0,i!=4); if (i!=4) c.degree(2,static_cast<U64>(i));
    c.finish(r,i!=7);
  }
  assert(c.metadata().attempts==10 && c.metadata().selected==3);
  assert(c.metadata().complete==2 && c.metadata().aborted_selected==1);
  assert(c.committed()[0].inputs==9 && c.committed()[0].noop==1);
  assert(c.committed()[0].changed==8);
  assert(c.committed()[2].count==1 && c.committed()[2].sum==1);
  c.reset(); auto r=c.begin(1,false); assert(c.finish(r,true));
  assert(c.committed()[1].noop==1 && c.committed()[0].inputs==0);
}
void truncation_and_invalid() {
  Collector c; auto o=enabled(); o.detail_budget=2; c.configure(o,descriptors);
  auto r=c.begin(0,true); c.degree(2,5); c.support(3,0,1); c.degree(2,6);
  assert(c.finish(r,true));
  assert(c.committed()[0].changed==1 && c.committed()[2].count==0 && c.committed()[3].changes==0);
  assert(c.metadata().committed_truncated==1 && c.metadata().detail_actions==2);
  r=c.begin(0,true); c.degree(100,1); assert(c.finish(r,true));
  assert(c.metadata().invalid_descriptor && c.committed()[0].inputs==2);
  r=c.begin(100,true); assert(!c.finish(r,true));
  r=c.begin(0,true); c.degree(5,1); assert(c.finish(r,true)); // wrong initiating op
  assert(c.committed()[5].count==0);
  r=c.begin(0,false); c.degree(2,1); assert(c.finish(r,true));
  assert(c.committed()[0].noop==1 && c.metadata().protocol_error);
  o.detail_budget=0; c.configure(o,descriptors);
  r=c.begin(0,true); c.degree(2,0); assert(c.finish(r,true));
  assert(c.metadata().committed_truncated==1);
}
void histogram_and_support() {
  Collector c; c.configure(enabled(),descriptors);
  auto r=c.begin(0,true);
  c.degree(2,0); c.degree(2,1); c.degree(2,2); c.degree(2,3); c.degree(2,4); c.degree(2,4);
  c.support(3,0,2); c.support(3,2,3); c.support(3,3,1); c.support(3,1,0); c.support(3,0,0);
  c.occurrence(4,true); c.occurrence(4,false); assert(c.finish(r,true));
  auto d=c.committed()[2];
  assert(d.count==6 && d.sum==14 && d.min==0 && d.max==4);
  assert(d.bins[0]==1 && d.bins[1]==1 && d.bins[2]==2 && d.bins[3]==2);
  auto s=c.committed()[3]; assert(s.changes==4 && s.zero_to_positive==1 && s.positive_to_zero==1);
  assert(s.count==4 && s.sum==6 && s.bins[0]==1);
  assert(c.committed()[4].visited==2 && c.committed()[4].accepted==1 && c.committed()[4].rejected==1);
  // Independent expected bin boundaries: every representable power of two
  // begins the next bin; its predecessor belongs to the preceding bin.
  for (unsigned b=1;b<=64;++b) {
    Cell x; const U64 lower=U64{1}<<(b-1); x.observe(lower);
    assert(x.bins[b]==1); x.observe(lower-1); assert(x.bins[b-1]==1);
  }
  Cell x; constexpr U64 max=std::numeric_limits<U64>::max(); x.observe(max); x.observe(1);
  assert(x.saturated && x.sum==max && x.count==2 && x.bins[64]==1);
  Cell y; y.count=max; y.inputs=max; y.bins[1]=max; y.min=1; y.max=1;
  Cell z; z.observe(1); z.inputs=1; y.merge(z);
  assert(y.saturated && y.count==max && y.inputs==max && y.bins[1]==max);
}
void lifecycle_memory_and_allocations() {
  Collector c; assert(c.memory().retained_payload_bytes==0);
  auto disabled=c.begin(999,true); c.degree(999,1); assert(c.finish(disabled,true));
  assert(c.metadata().guards==0); c.configure(enabled(),descriptors);
  const auto m=c.memory(); assert(m.descriptors_bytes>=sizeof(descriptors));
  assert(m.committed_bytes>=6*sizeof(Cell) && m.attempt_bytes==m.committed_bytes && m.previous_bytes==m.committed_bytes);
  assert(m.retained_payload_bytes==m.descriptors_bytes+m.committed_bytes+m.attempt_bytes+m.previous_bytes);
  const auto count=allocations; fail_after=0;
  auto r=c.begin(0,true); c.degree(2,3); auto n=c.nest(r); c.support(3,1,2);
  assert(c.finish(n,true)); assert(c.finish(r,true)); assert(c.rotate(1));
  assert(c.has_previous() && c.previous()[2].sum==3 && c.previous_metadata().committed==1);
  assert(c.configuration()==1 && c.previous_configuration()==0);
  assert(c.rotate(1) && c.previous()[2].sum==3 && !c.replaced_history());
  r=c.begin(1,false); assert(c.finish(r,true)); assert(c.rotate(2));
  assert(c.replaced_history() && c.previous()[1].noop==1 && c.previous()[2].sum==0);
  const auto generation=c.generation(); assert(c.reset()); assert(c.generation()==generation+1);
  assert(!c.has_previous() && c.metadata().attempts==0 && c.committed()[0].inputs==0);
  r=c.begin(0,true); assert(!c.finish(r,false));
  assert(allocations==count); fail_after=-1;
  c.configure(Options{},{}); assert(c.memory().retained_payload_bytes==0);
}
void saturation_boundaries() {
  Collector c; auto o=enabled(); o.detail_budget=2; c.configure(o,descriptors);
  auto r=c.begin(0,true); c.degree(2,2); c.degree(2,3); assert(c.finish(r,true));
  assert(c.metadata().complete==1 && c.committed()[2].sum==5);
  CollectorTestAccess::generation_max(c); assert(c.reset());
  assert(c.generation()==std::numeric_limits<U64>::max() && c.generation_saturated());
  CollectorTestAccess::attempts_max(c); CollectorTestAccess::ordinal_max(c);
  r=c.begin(0,true); assert(c.finish(r,true));
  assert(c.metadata().saturated && c.metadata().attempts==std::numeric_limits<U64>::max());
  assert(c.begin(0,true).serial==0 && c.metadata().ordinal_exhausted && !c.pending());
  assert(c.reset()); r=c.begin(0,true); assert(c.finish(r,true));
}
void configuration_faults() {
  Collector c; c.configure(enabled(),descriptors);
  auto r=c.begin(0,true); assert(c.finish(r,true));
  const auto generation=c.generation(); const auto bytes=c.memory().retained_payload_bytes;
  // Four independent allocation positions: descriptor vector and three slabs.
  for (long i=0;i<4;++i) {
    fail_after=i; bool failed=false;
    try { c.configure(enabled(),descriptors); } catch (const std::bad_alloc&) { failed=true; }
    fail_after=-1; assert(failed);
    assert(c.generation()==generation && c.committed()[0].inputs==1 && c.memory().retained_payload_bytes==bytes);
  }
  auto bad=enabled(); bad.period=0;
  bool failed=false; try { c.configure(bad,descriptors); } catch(const std::invalid_argument&) {failed=true;} assert(failed);
  bad=enabled(); bad.max_cells=5; failed=false;
  try { c.configure(bad,descriptors); } catch(const std::length_error&) {failed=true;} assert(failed);
  Descriptor duplicate[]={descriptors[0],descriptors[0]}; failed=false;
  try { c.configure(enabled(),duplicate); } catch(const std::invalid_argument&) {failed=true;} assert(failed);
  Descriptor orphan[]={descriptors[2]}; failed=false;
  try { c.configure(enabled(),orphan); } catch(const std::invalid_argument&) {failed=true;} assert(failed);
  assert(c.generation()==generation && c.committed()[0].inputs==1);
  c.configure(enabled(),descriptors); assert(c.generation()==generation+1);
}
}
void* operator new(std::size_t n) { return allocate(n); }
void* operator new[](std::size_t n) { return allocate(n); }
void operator delete(void* p) noexcept { std::free(p); }
void operator delete[](void* p) noexcept { std::free(p); }
void operator delete(void* p,std::size_t) noexcept { std::free(p); }
void operator delete[](void* p,std::size_t) noexcept { std::free(p); }
int main() {
  transactions(); sampling_and_noops(); truncation_and_invalid();
  histogram_and_support(); lifecycle_memory_and_allocations(); saturation_boundaries(); configuration_faults();
}
