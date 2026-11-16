#include "crown/runtime/statistics.hpp"
#include "crown/api/error.hpp"
#include "crown/storage/accounted_table.hpp"
#include <algorithm>
#include <list>
#include <limits>

namespace crown::runtime::statistics {
CapturedKey::CapturedKey(const resource::MemoryAccount& account,storage::AccountedRow row)
    :account_(account),row_(std::move(row)) {}
// Retained value copies deep-clone compact bytes on the source query account.
CapturedKey::CapturedKey(const CapturedKey& other)
    :account_(other.account_),row_(account_?other.row_.clone(account_):storage::AccountedRow{}) {}
namespace {
using detail::Exhausted;
using Groups=std::list<CapturedHeavyKey,resource::MemoryAllocator<CapturedHeavyKey>>;
Groups groups_for(const resource::MemoryAccount& account) {
  return Groups(resource::MemoryAllocator<CapturedHeavyKey>(account,resource::MemoryPurpose::scratch,detail::owner_capture_memory));
}
std::uint64_t payload_bytes(std::size_t count,std::size_t width) {
  if(count>std::numeric_limits<std::size_t>::max()/width ||
      count>std::numeric_limits<std::uint64_t>::max()/width)throw Exhausted{};
  return static_cast<std::uint64_t>(count)*static_cast<std::uint64_t>(width);
}
// The same charged scalar/unsigned-byte ordering as the standalone reference
// scan, operating directly on compact native cells without a Row/string export.
int compare(storage::RowView a,storage::RowView b,Budget& budget) {
  for(std::size_t i=0;i<std::min(a.size(),b.size());++i) {
    budget.work();
    if(a[i].index()!=b[i].index())return a[i].index()<b[i].index()?-1:1;
    if(const auto* x=std::get_if<std::string_view>(&a[i])) {
      const auto y=std::get<std::string_view>(b[i]);budget.work();
      for(std::size_t j=0;j<std::min(x->size(),y.size());++j) {
        budget.work();const auto left=static_cast<unsigned char>((*x)[j]),right=static_cast<unsigned char>(y[j]);
        if(left!=right)return left<right?-1:1;
      }
      if(x->size()!=y.size())return x->size()<y.size()?-1:1;
    }else {
      if(std::holds_alternative<storage::InlineDecimal>(a[i]))budget.work(256);
      if(a[i]<b[i])return -1;
      if(b[i]<a[i])return 1;
    }
  }
  budget.work();return a.size()==b.size()?0:(a.size()<b.size()?-1:1);
}
// C01 logical DTO payload charges differ from real native allocation requests.
void account_value(const storage::ScalarView& value,Budget& budget) {
  budget.work();budget.bytes(sizeof(Value));
  if(const auto* text=std::get_if<std::string_view>(&value)) {
    budget.work(text->size());budget.bytes(text->size());budget.bytes(1);
  }else if(std::holds_alternative<storage::InlineDecimal>(value)) {
    budget.work(38);budget.bytes(38);
  }
}
CapturedKey copy(storage::RowView values,Budget& budget,const resource::MemoryAccount& account) {
  for(const auto& value:values.cells())account_value(value,budget);
  budget.observe_capacities(values.size(),0,0);
  return {account,storage::AccountedRow::copy_of(account,values,detail::owner_capture_memory)};
}
void admit(Groups& groups,CapturedKey key,std::uint64_t count,Budget& budget) {
  budget.key();budget.bytes(sizeof(HeavyKey)+2*sizeof(void*));
  groups.push_back({std::move(key),count});
}
// Sorted multiplicities need only a final-bin check; reserve(size+1) and cumulative
// logical payload growth remain costs. Exact facts publish only after preparation.
void finish(CapturedDistribution& out,Groups& groups,Budget& budget,const resource::MemoryAccount& account) {
  // Sorting links does not allocate. If the charged comparator throws, the
  // entire private scratch graph is released without publishing prefix facts.
  groups.sort([&](const auto& a,const auto& b) {
    budget.work();return a.count!=b.count?a.count>b.count:compare(a.key.view(),b.key.view(),budget)<0;
  });
  CaptureVector<std::pair<std::uint64_t,std::uint64_t>> histogram(detail::capture_allocator<std::pair<std::uint64_t,std::uint64_t>>(account));
  for(const auto& group:groups) {
    auto found=histogram.end();
    if(!histogram.empty()) {
      budget.work();if(histogram.back().first==group.count)found=histogram.end()-1;
    }
    if(found!=histogram.end())++found->second;
    else {
      if(histogram.size()==std::numeric_limits<std::size_t>::max())throw Exhausted{};
      budget.bytes(payload_bytes(histogram.size()+1,sizeof(histogram[0])));
      budget.work(histogram.size()+1);histogram.reserve(histogram.size()+1);budget.observe_capacities(0,histogram.capacity(),0);
      histogram.emplace_back(group.count,1);
    }
  }
  std::sort(histogram.begin(),histogram.end(),[&](auto a,auto b){budget.work();return a.first<b.first;});
  CaptureVector<CapturedHeavyKey> heavy(detail::capture_allocator<CapturedHeavyKey>(account));
  const auto n=std::min(groups.size(),budget.limits().heavy_keys);
  // C01's named report payload model is separate from the query's actual
  // allocator requests; the native compact row/control overhead is charged by
  // MemoryAccount, not added a second time to this logical DTO model.
  budget.bytes(payload_bytes(n,sizeof(HeavyKey)));budget.work(n);heavy.reserve(n);budget.observe_capacities(0,0,heavy.capacity());
  for(auto& group:groups){if(heavy.size()==n)break;heavy.push_back(std::move(group));}
  out.ndv=groups.size();out.histogram=std::move(histogram);out.heavy_keys=std::move(heavy);
  out.completion=Completion::exact;
}
}

// Each row projection is copied before linear distinct-key lookup, including duplicates.
CapturedDistribution detail::native_projected_fields(const storage::AccountedStorageTable& table,
    std::span<const FieldId> fields,Budget& budget,storage::IndexWorkAllowance* work,const resource::MemoryAccount& account) {
  CapturedDistribution result(account);
  try {
    auto cursor=table.live(work);
    budget.work();budget.bytes(sizeof(Distribution));
    if(fields.size()>budget.limits().projection_width)throw Exhausted{};
    for(auto field:fields) {
      budget.work();
      if(field.value>=table.layout().fields().size())throw Error("invalid_statistics_request","projection field outside source layout");
    }
    auto groups=groups_for(account);
    for(;;) {
      budget.work();const auto entry=cursor.next_entry(work);if(!entry)break;
      budget.row();budget.work();const auto values=entry->tuple.values();
      for(auto field:fields){budget.work();account_value(values[field.value],budget);}
      budget.observe_capacities(fields.size(),0,0);
      CapturedKey key(account,storage::AccountedRow::project(account,values,fields,owner_capture_memory));
      auto found=groups.end();
      for(auto it=groups.begin();it!=groups.end();++it)if(compare(it->key.view(),key.view(),budget)==0){found=it;break;}
      if(found==groups.end())admit(groups,std::move(key),1,budget);else ++found->count;
      ++result.visited;
    }
    finish(result,groups,budget,account);
  }catch(const Exhausted&) {}
  catch(const storage::IndexFailure& failure){if(failure.code()!="storage_work_limit")throw;}
  catch(const Error& failure){if(failure.code()!="storage_work_limit")throw;}
  return result;
}
CapturedDistribution detail::native_index(const storage::AccountedStorageTable& table,IndexId id,
    const storage::Projection& projection,Budget& budget,storage::IndexWorkAllowance* work,const resource::MemoryAccount& account) {
  auto cursor=table.index_keys(id,work);
  CapturedDistribution result(account);
  try {
    budget.work();budget.bytes(sizeof(Capture));auto groups=groups_for(account);
    if(projection.fields().size()>budget.limits().projection_width)throw Exhausted{};
    for(;;) {
      budget.work();const auto entry=cursor.next(work);if(!entry)break;
      budget.row();auto key=copy(entry->key.values(),budget,account);
      admit(groups,std::move(key),entry->degree,budget);++result.visited;
    }
    finish(result,groups,budget,account);
  }catch(const Exhausted&) {}
  catch(const storage::IndexFailure& failure){if(failure.code()!="storage_work_limit")throw;}
  return result;
}

namespace detail {
struct WeightedBuilder::Data {
  Budget& budget;
  resource::MemoryAccount account;
  Groups groups;
  CapturedDistribution output;
  bool exhausted=false;
  Data(Budget& b,const resource::MemoryAccount& a):budget(b),account(a),groups(groups_for(a)),output(a) {}
};
WeightedBuilder::WeightedBuilder(Budget& budget,const resource::MemoryAccount& account) {
  budget.work();budget.bytes(sizeof(Data));
  data_=resource::make_accounted_unique<Data>(owner_capture_memory,account,resource::MemoryPurpose::scratch,budget,account);
}
WeightedBuilder::~WeightedBuilder()=default;
// Owner maps supply distinct positive weighted keys; add does not deduplicate.
bool WeightedBuilder::add(storage::RowView key,std::uint64_t count) {
  auto& d=*data_;if(d.exhausted)return false;
  if(count==0)throw Error("statistics_contract","stored multiplicity must be positive");
  try {
    d.budget.work();d.budget.row();
    if(key.size()>d.budget.limits().projection_width)throw Exhausted{};
    admit(d.groups,copy(key,d.budget,d.account),count,d.budget);++d.output.visited;return true;
  }catch(const Exhausted&){d.exhausted=true;return false;}
}
void WeightedBuilder::stop() noexcept {data_->exhausted=true;}
CapturedDistribution WeightedBuilder::finish() {
  auto& d=*data_;
  if(!d.exhausted)try{statistics::finish(d.output,d.groups,d.budget,d.account);}catch(const Exhausted&){}
  return std::move(d.output);
}
}
}
