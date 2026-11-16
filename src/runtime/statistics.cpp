#include "crown/runtime/statistics.hpp"
#include "crown/api/error.hpp"
#include "crown/storage/accounted_table.hpp"
#include <type_traits>
#include <algorithm>
#include <list>
#include <limits>

namespace crown::runtime::statistics {
namespace {
using detail::Exhausted;
void charge(std::uint64_t& used,std::uint64_t cap,std::uint64_t n) {
  if (n>cap-used) throw Exhausted{};
  used+=n;
}
std::uint64_t payload_bytes(std::size_t count,std::size_t width) {
  if(count>std::numeric_limits<std::size_t>::max()/width ||
      count>std::numeric_limits<std::uint64_t>::max()/width)throw Exhausted{};
  return static_cast<std::uint64_t>(count)*static_cast<std::uint64_t>(width);
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
void account_value(const storage::ScalarView& value,Budget& budget) {
  budget.work();budget.bytes(sizeof(Value));
  if(const auto* text=std::get_if<std::string_view>(&value)) {
    budget.work(text->size());budget.bytes(text->size());budget.bytes(1);
  } else if(std::holds_alternative<storage::InlineDecimal>(value)) { budget.work(38);budget.bytes(38); }
}
Value exported_value(const storage::ScalarView& value) { return storage::export_scalar(value); }
Row copy(storage::RowView values,Budget& budget) {
  for(const auto& value:values.cells())account_value(value,budget);
  auto result=storage::export_row(values);budget.observe_capacities(result.capacity(),0,0);return result;
}
Row copy(storage::TupleValuesView values,Budget& budget) {
  for(const auto& value:values)account_value(value,budget);
  auto result=storage::export_row(std::move(values));budget.observe_capacities(result.capacity(),0,0);return result;
}
using Groups=std::list<HeavyKey>;
void admit(Groups& groups,Row key,std::uint64_t count,Budget& budget) {
  budget.key(); budget.bytes(sizeof(HeavyKey)+2*sizeof(void*));
  groups.push_back({std::move(key),count});
}
void finish(Distribution& out,Groups& groups,Budget& budget) {
  // Standalone ordinary exports stay private until complete facts publish.
  // Query-owned native capture has its separate accounted implementation.
  // list sort allocates no nodes; throwing comparator only affects local scratch.
  groups.sort([&](const auto& a,const auto& b) {
    budget.work(); return a.count!=b.count?a.count>b.count:compare(a.key,b.key,budget)<0;
  });
  std::vector<std::pair<std::uint64_t,std::uint64_t>> histogram;
  for(const auto& g:groups) {
    auto found=histogram.end();
    if(!histogram.empty()) {
      budget.work();
      if(histogram.back().first==g.count)found=histogram.end()-1;
    }
    if(found!=histogram.end()) ++found->second;
    else {
      // Charge requested payload; actual capacity is observed separately.
      if(histogram.size()==std::numeric_limits<std::size_t>::max())throw Exhausted{};
      budget.bytes(payload_bytes(histogram.size()+1,sizeof(histogram[0])));
      budget.work(histogram.size()+1); histogram.reserve(histogram.size()+1); budget.observe_capacities(0,histogram.capacity(),0);
      histogram.emplace_back(g.count,1);
    }
  }
  std::sort(histogram.begin(),histogram.end(),[&](auto a,auto b){budget.work();return a.first<b.first;});
  std::vector<HeavyKey> heavy;
  auto n=std::min(groups.size(),budget.limits().heavy_keys);
  budget.bytes(payload_bytes(n,sizeof(HeavyKey))); budget.work(n); heavy.reserve(n); budget.observe_capacities(0,0,heavy.capacity());
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
Distribution detail::projected_fields(const storage::ReferenceTable& table,std::span<const FieldId> fields,Budget& budget) {
  auto cursor=table.live(); // Also enforces quiescence before publishing cardinality.
  Distribution result;
  try {
    budget.work(); budget.bytes(sizeof(Distribution));
    if(fields.size()>budget.limits().projection_width)throw Exhausted{};
    for(auto f:fields) {
      budget.work();
      if(f.value>=table.layout().fields().size())throw Error("invalid_statistics_request","projection field outside source layout");
    }
    Groups groups;
    for(;;) {
      budget.work(); auto handle=cursor.next(); if(!handle)break;
      budget.row(); budget.work(); const auto& values=table.get(*handle)->values();
      for(auto f:fields){budget.work();account_value(values[f.value],budget);}
      Row key; key.reserve(fields.size()); budget.observe_capacities(key.capacity(),0,0);
      for(auto f:fields)key.push_back(exported_value(values[f.value]));
      auto found=groups.end();
      for(auto it=groups.begin();it!=groups.end();++it)if(compare(it->key,key,budget)==0){found=it;break;}
      if(found==groups.end())admit(groups,std::move(key),1,budget);else ++found->count;
      ++result.visited;
    }
    finish(result,groups,budget);
  } catch(const Exhausted&) {} // No prefix NDV/histogram/top-K is published.
  return result;
}
Capture projection(const storage::ReferenceTable& table,const storage::Projection& p,Budget& budget) {
  if(!table.layout().same_token(p.source()))throw Error("layout_mismatch","statistics projection has foreign source");
  auto distribution=detail::projected_fields(table,p.fields(),budget);
  auto result=start(table); result.projection=p;
  result.distribution=std::move(distribution);
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
template<class Table> Distribution table_projected_fields(const Table& table,std::span<const FieldId> fields,
    Budget& budget,storage::IndexWorkAllowance* work) {
  // This compatibility path exports ordinary keys and groups linearly. The
  // native table cursor grant and logical statistics budget remain separate.
  Distribution result;
  try {
    auto cursor=table.live(work);
    budget.work();budget.bytes(sizeof(Distribution));
    if (fields.size()>budget.limits().projection_width) throw detail::Exhausted{};
    for (auto field : fields) {
      budget.work();
      if (field.value>=table.layout().fields().size())
        throw Error("invalid_statistics_request","projection field outside source layout");
    }
    Groups groups;
    for (;;) {
      budget.work();const auto entry=cursor.next_entry(work);if (!entry) break;
      budget.row();budget.work();const auto& values=entry->tuple.values();
      for (auto field : fields) { budget.work();account_value(values[field.value],budget); }
      Row key;key.reserve(fields.size());budget.observe_capacities(key.capacity(),0,0);
      for (auto field : fields) key.push_back(exported_value(values[field.value]));
      auto found=groups.end();
      for (auto it=groups.begin();it!=groups.end();++it)
        if (compare(it->key,key,budget)==0) { found=it;break; }
      if (found==groups.end()) admit(groups,std::move(key),1,budget);else ++found->count;
      ++result.visited;
    }
    finish(result,groups,budget);
  } catch (const detail::Exhausted&) {
  } catch (const storage::IndexFailure& failure) {
    if(failure.code()!="storage_work_limit")throw;
  } catch (const Error& failure) {
    if (failure.code()!="storage_work_limit") throw;
  }
  return result;
}
Distribution detail::projected_fields(const storage::StorageTable& table,std::span<const FieldId> fields,
    Budget& budget,storage::IndexWorkAllowance* work) { return table_projected_fields(table,fields,budget,work); }
Distribution detail::projected_fields(const storage::AccountedStorageTable& table,std::span<const FieldId> fields,
    Budget& budget,storage::IndexWorkAllowance* work) { return table_projected_fields(table,fields,budget,work); }
Capture projection(const storage::StorageTable& table,const storage::Projection& p,Budget& budget,
    storage::IndexWorkAllowance* work) {
  if (!table.layout().same_token(p.source())) throw Error("layout_mismatch","statistics projection has foreign source");
  auto distribution=detail::projected_fields(table,p.fields(),budget,work);
  return {{table.owner(),table.relation(),table.revision()},table.layout(),p,{},table.size(),std::move(distribution)};
}
Capture index(const storage::StorageTable& table,IndexId id,Budget& budget,storage::IndexWorkAllowance* work) {
  // The caller may catch admission failure before metadata is complete. No
  // prefix NDV, histogram or heavy keys escape a later exhausted traversal.
  auto cursor=table.index_keys(id,work);
  Capture result{{table.owner(),table.relation(),table.revision()},table.layout(),table.projection(id,work),id,table.size(),{}};
  try {
    budget.work();budget.bytes(sizeof(Capture));Groups groups;
    if (result.projection->fields().size()>budget.limits().projection_width) throw Exhausted{};
    for (;;) {
      budget.work();const auto entry=cursor.next(work);if (!entry) break;
      budget.row();auto key=copy(entry->key.values(),budget);
      admit(groups,std::move(key),entry->degree,budget);++result.distribution.visited;
    }
    finish(result.distribution,groups,budget);
  } catch (const Exhausted&) {
  } catch (const Error& failure) {
    if (failure.code()!="storage_work_limit") throw;
  }
  return result;
}
Capture index(const storage::AccountedStorageTable& table,IndexId id,const storage::Projection& legacy,
    Budget& budget,storage::IndexWorkAllowance* work) {
  auto cursor=table.index_keys(id,work);
  const auto actual=table.projection(id,work).descriptor();
  // Export the admitted index definition even if its diagnostic scan exhausts.
  // Legacy/native freeze recreates tokens, so compare complete descriptors and
  // ordered fields; equal widths alone cannot bind the reported population.
  Capture result{{table.owner(),table.relation(),table.revision()},actual.source(),actual,id,table.size(),{}};
  try {
    budget.work();budget.bytes(sizeof(Capture));Groups groups;
    if(actual.fields().size()>budget.limits().projection_width)throw Exhausted{};
    const auto same_layout=[&](const storage::TupleLayout& left,const storage::TupleLayout& right) {
      // Precharge the full field/binding scans. Shared descriptor handles add
      // no payload allocation to the existing logical report-byte model.
      budget.work();budget.work(left.fields().size());budget.work(right.fields().size());
      budget.work(left.context().binding.size());budget.work(right.context().binding.size());
      return left.same_descriptor(right);
    };
    budget.work(actual.fields().size());budget.work(legacy.fields().size());
    if(!same_layout(actual.source(),legacy.source()) || !same_layout(actual.target(),legacy.target()) ||
        !std::ranges::equal(actual.fields(),legacy.fields()))
      throw Error("invalid_statistics_request","statistics metadata differs from the actual index definition");
    for(;;) {
      budget.work();const auto entry=cursor.next(work);if(!entry)break;
      budget.row();auto key=copy(entry->key.values(),budget);
      admit(groups,std::move(key),entry->degree,budget);++result.distribution.visited;
    }
    finish(result.distribution,groups,budget);
  }catch(const Exhausted&){}
  catch(const storage::IndexFailure& failure){if(failure.code()!="storage_work_limit")throw;}
  return result;
}

}

