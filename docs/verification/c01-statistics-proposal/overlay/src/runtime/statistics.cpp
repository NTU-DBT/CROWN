#include "crown/runtime/statistics.hpp"
#include "crown/api/error.hpp"
#include <algorithm>
#include <list>
#include <limits>

namespace crown::runtime::statistics {
namespace {
struct Exhausted {};
void charge(std::uint64_t& used,std::uint64_t cap,std::uint64_t n) {
  if (n>cap-used) throw Exhausted{};
  used+=n;
}
// Charged native lexicographic comparison. std::string ordering uses unsigned
// bytes, including embedded NUL and invalid UTF-8. Decimal work has a fixed
// conservative bound from its native 38-digit domain.
int compare(const Row& a,const Row& b,Budget& budget) {
  for (std::size_t i=0;i<std::min(a.size(),b.size());++i) {
    budget.work();
    if (a[i].index()!=b[i].index()) return a[i].index()<b[i].index()?-1:1;
    if (const auto* x=std::get_if<std::string>(&a[i])) {
      const auto& y=std::get<std::string>(b[i]); budget.work();
      for (std::size_t j=0;j<std::min(x->size(),y.size());++j) {
        budget.work(); auto l=static_cast<unsigned char>((*x)[j]), r=static_cast<unsigned char>(y[j]);
        if(l!=r)return l<r?-1:1;
      }
      if(x->size()!=y.size())return x->size()<y.size()?-1:1;
    } else {
      if(std::holds_alternative<Decimal>(a[i]))budget.work(256);
      if(a[i]<b[i])return -1;
      if(b[i]<a[i])return 1;
    }
  }
  budget.work(); return a.size()==b.size()?0:(a.size()<b.size()?-1:1);
}
void account_value(const Value& value,Budget& budget) {
  budget.work(); budget.bytes(sizeof(Value));
  if(const auto* s=std::get_if<std::string>(&value)) {
    budget.work(s->size()); budget.bytes(s->size()); budget.bytes(1);
  } else if(std::holds_alternative<Decimal>(value)) { budget.work(38); budget.bytes(38); }
}
Row copy(const Row& values,Budget& budget) {
  for(const auto& v:values)account_value(v,budget);
  Row result=values; budget.observe_capacities(result.capacity(),0,0); return result;
}
using Groups=std::list<HeavyKey>;
void admit(Groups& groups,Row key,std::uint64_t count,Budget& budget) {
  budget.key(); budget.bytes(sizeof(HeavyKey)+2*sizeof(void*));
  groups.push_back({std::move(key),count});
}
void finish(Distribution& out,Groups& groups,Budget& budget) {
  // list sort allocates no nodes; throwing comparator only affects local scratch.
  groups.sort([&](const auto& a,const auto& b) {
    budget.work(); return a.count!=b.count?a.count>b.count:compare(a.key,b.key,budget)<0;
  });
  std::vector<std::pair<std::uint64_t,std::uint64_t>> histogram;
  for(const auto& g:groups) {
    auto found=histogram.end();
    for(auto it=histogram.begin();it!=histogram.end();++it) {
      budget.work(); if(it->first==g.count){found=it;break;}
    }
    if(found!=histogram.end()) ++found->second;
    else {
      // Charge requested payload; actual capacity is observed separately.
      if(histogram.size()>=std::numeric_limits<std::uint64_t>::max()/sizeof(histogram[0]))throw Exhausted{};
      budget.bytes((histogram.size()+1)*sizeof(histogram[0]));
      budget.work(histogram.size()+1); histogram.reserve(histogram.size()+1); budget.observe_capacities(0,histogram.capacity(),0);
      histogram.emplace_back(g.count,1);
    }
  }
  std::sort(histogram.begin(),histogram.end(),[&](auto a,auto b){budget.work();return a.first<b.first;});
  std::vector<HeavyKey> heavy;
  auto n=std::min(groups.size(),budget.limits().heavy_keys);
  if(n>std::numeric_limits<std::uint64_t>::max()/sizeof(HeavyKey))throw Exhausted{};
  budget.bytes(n*sizeof(HeavyKey)); budget.work(n); heavy.reserve(n); budget.observe_capacities(0,0,heavy.capacity());
  for(auto& g:groups) { if(heavy.size()==n)break; heavy.push_back(std::move(g)); }
  out.ndv=groups.size(); out.histogram=std::move(histogram); out.heavy_keys=std::move(heavy);
  out.completion=Completion::exact;
}
Capture start(const storage::ReferenceTable& table) {
  return {{table.owner(),table.relation(),table.revision()},table.layout(),{},{},table.size(),{}};
}
}
void Budget::observe_capacities(std::size_t row,std::size_t histogram,std::size_t heavy) noexcept {
  usage_.max_row_capacity=std::max(usage_.max_row_capacity,row);
  usage_.max_histogram_capacity=std::max(usage_.max_histogram_capacity,histogram);
  usage_.max_heavy_capacity=std::max(usage_.max_heavy_capacity,heavy);
}
void Budget::work(std::uint64_t n){charge(usage_.work,limits_.work,n);}
void Budget::row(){charge(usage_.rows,limits_.rows,1);}
void Budget::key(){charge(usage_.distinct_keys,limits_.distinct_keys,1);}
void Budget::bytes(std::uint64_t n){charge(usage_.accounted_bytes,limits_.accounted_bytes,n);}
Capture projection(const storage::ReferenceTable& table,const storage::Projection& p,Budget& budget) {
  auto cursor=table.live(); // Also enforces quiescence before publishing cardinality.
  if(!table.layout().same_token(p.source()))throw Error("layout_mismatch","statistics projection has foreign source");
  auto result=start(table); result.projection=p;
  try {
    budget.work(); budget.bytes(sizeof(Capture));
    if(p.fields().size()>budget.limits().projection_width)throw Exhausted{};
    Groups groups;
    for(;;) {
      budget.work(); auto handle=cursor.next(); if(!handle)break;
      budget.row(); budget.work(); const auto& values=table.get(*handle)->values();
      for(auto f:p.fields()){budget.work();account_value(values[f.value],budget);}
      Row key; key.reserve(p.fields().size()); budget.observe_capacities(key.capacity(),0,0);
      for(auto f:p.fields())key.push_back(values[f.value]);
      auto found=groups.end();
      for(auto it=groups.begin();it!=groups.end();++it)if(compare(it->key,key,budget)==0){found=it;break;}
      if(found==groups.end())admit(groups,std::move(key),1,budget);else ++found->count;
      ++result.distribution.visited;
    }
    finish(result.distribution,groups,budget);
  } catch(const Exhausted&) {} // No prefix NDV/histogram/top-K is published.
  return result;
}
Capture index(const storage::ReferenceTable& table,IndexId id,Budget& budget) {
  auto cursor=table.index_keys(id); auto result=start(table); result.index=id; result.projection=table.projection(id);
  try {
    budget.work(); budget.bytes(sizeof(Capture)); Groups groups;
    if(result.projection->fields().size()>budget.limits().projection_width)throw Exhausted{};
    for(;;) {
      budget.work(); auto entry=cursor.next(); if(!entry)break;
      budget.row(); auto key=copy(entry->key.values(),budget);
      admit(groups,std::move(key),entry->degree,budget); ++result.distribution.visited;
    }
    finish(result.distribution,groups,budget);
  } catch(const Exhausted&) {}
  return result;
}
}
