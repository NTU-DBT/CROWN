#include "memory_report_detail.hpp"
#include <limits>

namespace crown::runtime::memory {
const Snapshot& Report::snapshot() const noexcept{return data_->snapshot;}
const Vector<resource::AttributedMemoryStatistics>& Report::owners() const noexcept{return data_->owners;}
const Vector<Table>& Report::tables() const noexcept{return data_->tables;}
const Vector<Operator>& Report::operators() const noexcept{return data_->operators;}
const Usage& Report::usage() const noexcept{return data_->usage;}
const resource::MemoryAccount& Report::account() const & noexcept{return data_->account;}
namespace detail {
namespace {
void require(bool value){if(!value)throw Failure{Stop::inconsistent};}
void sum(resource::MemoryUsage& to,const resource::MemoryUsage& value) {
  to.allocations=Builder::add(to.allocations,value.allocations);
  to.requested_bytes=Builder::add(to.requested_bytes,value.requested_bytes);
  to.payload_bytes=Builder::add(to.payload_bytes,value.payload_bytes);
}
resource::MemoryAttribution attribution(const Operator& value) {
  return std::visit([](const auto& v){return v.attribution;},value);
}
void arena(const storage::ArenaMemoryStatistics& value) {
  resource::MemoryUsage total;
  for(const auto usage:{value.state_control,value.directory,value.live_slots,value.retained_slots,value.free_slots,
      value.exhausted_slots,value.live_values,value.retained_values})sum(total,usage);
  require(total==value.owner.current && value.live_slots.allocations==value.records.live_records &&
      value.live_values.allocations==value.records.live_records && value.retained_slots.allocations==value.records.retained_records &&
      value.retained_values.allocations==value.records.retained_records && value.free_slots.allocations==value.records.free_slots &&
      value.exhausted_slots.allocations==value.records.exhausted_slots);
}
}
std::uint64_t Builder::add(std::uint64_t a,std::uint64_t b) {
  if(b>UINT64_MAX-a)throw Failure{Stop::overflow};
  return a+b;
}
Builder::Builder(const resource::MemoryAccount& account,Layer layer,Availability availability,std::uint64_t owner,
    std::uint64_t sequence,std::string_view hash,Limits limits,Usage& usage):limits_(limits),usage_(usage) {
  work();data_=resource::make_accounted_shared<Data>(report_owner,account,resource::MemoryPurpose::capture,
      account,layer,availability,owner,sequence,hash);
}
void Builder::work(std::uint64_t amount) {
  if(usage_.work>limits_.work || amount>limits_.work-usage_.work)throw Failure{Stop::work_limit};
  usage_.work+=amount;
}
void Builder::operation(Operator value) {
  work();if(data_->operators.size()==limits_.operators)throw Failure{Stop::operator_limit};
  data_->operators.push_back(std::move(value));usage_.operators=data_->operators.size();
}
std::uint64_t Builder::records(TableScope scope,RelationId relation) {
  // A recorded-table join is a metered linear scan, not a maintained index.
  for(const auto& row:data_->tables){work();if(row.scope==scope && row.relation==relation)return row.live_records;}
  throw Failure{Stop::inconsistent};
}
void Builder::table(TableScope scope,const storage::AccountedStorageTable& table,RelationRole role,
    std::optional<NodeId> node,std::optional<TableId> base) {
  if(data_->tables.size()==limits_.tables)throw Failure{Stop::table_limit};
  // Explicit diagnostics scan owner ledgers and resident arena/index storage.
  // Each table node/member is backed by an account allocation; this finite
  // conservative reservation covers those scans before they begin.
  const auto allocations=data_->account.statistics().current.allocations;
  const auto records=table.arena_statistics();
  work(add(add(allocations,allocations),add(allocations,static_cast<std::uint64_t>(records.slots))));
  auto value=table.memory_statistics();
  std::visit([&](const auto& memory) {
    const auto live=[&] {
      if constexpr(requires{memory.live_records;})return memory.live_records;
      else return memory.records.rows;
    }();
    require(live==table.size() && memory.arena.records==records && records.live_records==live);
    arena(memory.arena);auto owned=memory.table.current;sum(owned,memory.arena.owner.current);require(owned==memory.owned);
  },value);
  data_->tables.push_back(Table{scope,table.relation(),role,node,base,table.owner(),table.backend(),
      static_cast<std::uint64_t>(table.size()),std::move(value)});usage_.tables=data_->tables.size();
}
Report Builder::finish() {
  // Build the account-wide owner inventory privately, then release scratch
  // before sampling. Report storage itself belongs to the captured instant.
  const auto& account=data_->account;
  {
    using Keys=std::vector<resource::MemoryAttribution,resource::MemoryAllocator<resource::MemoryAttribution>>;
    Keys keys(resource::MemoryAllocator<resource::MemoryAttribution>(account,resource::MemoryPurpose::scratch,report_owner));
    const auto n=account.statistics().current.allocations;
    const auto capacity=add(add(n,static_cast<std::uint64_t>(data_->operators.size())),1);
    if(capacity>SIZE_MAX)throw Failure{Stop::overflow};
    work(add(add(n,n),2));keys.reserve(static_cast<std::size_t>(capacity));keys.resize(static_cast<std::size_t>(add(n,1)));
    const auto used=account.copy_attributions(keys);keys.resize(used);
    for(const auto& item:data_->operators){work();keys.push_back(attribution(item));}
    std::sort(keys.begin(),keys.end(),[&](auto a,auto b){work();return a<b;});
    work(static_cast<std::uint64_t>(keys.size()));keys.erase(std::unique(keys.begin(),keys.end()),keys.end());
    if(keys.size()>limits_.owners)throw Failure{Stop::owner_limit};
    data_->owners.reserve(keys.size());
    for(const auto key:keys) {resource::AttributedMemoryStatistics row;row.attribution=key;data_->owners.push_back(row);}
  } // Release all diagnostic scratch before taking the reported account instant.
  data_->snapshot.account=account.statistics();
  resource::MemoryUsage total;
  std::array<resource::MemoryUsage,resource::memory_purpose_count> purposes{};
  std::array<resource::MemoryUsage,resource::allocation_lifetime_count> lifetimes{};
  for(auto& row:data_->owners) {
    work(data_->snapshot.account.current.allocations);row=account.statistics_for(row.attribution);sum(total,row.current);
    for(std::size_t i=0;i<purposes.size();++i)sum(purposes[i],row.by_purpose[i]);
    for(std::size_t i=0;i<lifetimes.size();++i)sum(lifetimes[i],row.by_lifetime[i]);
  }
  require(total==data_->snapshot.account.current && purposes==data_->snapshot.account.by_purpose &&
      lifetimes==data_->snapshot.account.by_lifetime);
  const auto owner=[&](const resource::AttributedMemoryStatistics& expected) {
    const auto found=std::lower_bound(data_->owners.begin(),data_->owners.end(),expected.attribution,
        [](const auto& row,auto key){return row.attribution<key;});
    require(found!=data_->owners.end() && *found==expected);
  };
  for(const auto& table:data_->tables)std::visit([&](const auto& value){work(add(static_cast<std::uint64_t>(data_->owners.size()),1));owner(value.table);owner(value.arena.owner);},table.memory);
  usage_.owners=data_->owners.size();data_->usage=usage_;return Report(data_);
}
} // namespace detail
Attempt capture(const SupportRuntime& owner,Limits limits) noexcept{return detail::Access::capture(owner,limits);}
Attempt capture(const PhysicalRuntime& owner,Limits limits) noexcept{return detail::Access::capture(owner,limits);}
Attempt capture(const DeltaRuntime& owner,Limits limits) noexcept{return detail::Access::capture(owner,limits);}
Attempt capture(const QuerySession& owner,Limits limits) noexcept{return detail::Access::capture(owner,limits);}
} // namespace crown::runtime::memory
