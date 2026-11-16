#include "update_pattern_detail.hpp"
#include "crown/runtime/window.hpp"
#include "crown/api/error.hpp"
#include "crown/ir/program.hpp"
#include "crown/resource/ownership.hpp"
#include "crown/resource/owner_allocator.hpp"
#include "constraint_validation.hpp"
#include "../io/native_input.hpp"
#ifdef CROWN_RUNTIME_TESTING
#include "runtime_probe.hpp"
#endif
#include <algorithm>
#include <limits>
#include <map>
#include <set>
#include <utility>

namespace crown::runtime {
namespace {
void require(bool yes,std::string_view code,std::string_view message) {
  if (!yes) throw Error(std::string(code),std::string(message));
}
std::size_t add(std::size_t a,std::size_t b) {
  require(b<=std::numeric_limits<std::size_t>::max()-a,"resource_limit","window byte accounting overflow");
  return a+b;
}
std::size_t multiply(std::size_t a,std::size_t b) {
  require(!b || a<=std::numeric_limits<std::size_t>::max()/b,"resource_limit","window byte accounting overflow");
  return a*b;
}
// Session controls remain session:0; nested window ownership is session:1.
constexpr resource::MemoryAttribution window_memory{resource::MemoryOwnerKind::session,1};
template<class K,class V> using WindowMap=std::map<K,V,std::less<K>,resource::MemoryAllocator<std::pair<const K,V>>>;
template<class K> using WindowSet=std::set<K,std::less<K>,resource::MemoryAllocator<K>>;
using NativeLabel=WindowCheckpointLabel;
using NativeCount=WindowCheckpointCount;
struct NativeActiveCommand {
  std::uint64_t sequence,watermark;
  std::vector<std::uint64_t,resource::OwnerAllocator<std::uint64_t>> expiration_labels;
  std::size_t completed_steps=0,total_steps=0;
  std::uint64_t accounted_work=0;
  NativeActiveCommand(const resource::MemoryAccount& account,std::uint64_t seq,std::uint64_t mark)
      :sequence(seq),watermark(mark),expiration_labels(resource::OwnerAllocator<std::uint64_t>(
          account,resource::MemoryPurpose::support_metadata,window_memory)) {}
};
std::size_t label_bytes(const NativeLabel& label) {
  return add(sizeof(NativeLabel)+sizeof(std::pair<std::uint64_t,std::uint64_t>)+2*sizeof(std::uint64_t),label.values.stored_payload_bytes());
}
std::size_t count_bytes(const NativeCount& count) {return add(sizeof(NativeCount),count.values.stored_payload_bytes());}
} // namespace
struct WindowTables::Data {
  std::vector<TableId,resource::MemoryAllocator<TableId>> values;
  Data(const resource::MemoryAccount& account,std::span<const TableId> source,std::size_t capacity)
      :values(resource::MemoryAllocator<TableId>(account,resource::MemoryPurpose::immutable_metadata,window_memory)) {
    if(capacity<source.size())throw recovery::ImageFailure(recovery::ImageFault::corrupt);
    values.reserve(capacity);values.insert(values.end(),source.begin(),source.end());
  }
};
WindowTables WindowTables::copy_of(const resource::MemoryAccount& account,const std::vector<TableId>& source) {
  return copy_of(account,std::span<const TableId>(source),source.capacity());
}
WindowTables WindowTables::copy_of(const resource::MemoryAccount& account,std::span<const TableId> source,std::size_t capacity) {
  if(source.empty())return {};
  return WindowTables(resource::make_accounted_shared<Data>(window_memory,account,
      resource::MemoryPurpose::immutable_metadata,account,source,capacity));
}
std::size_t WindowTables::size() const noexcept {return data_?data_->values.size():0;}
std::size_t WindowTables::capacity() const noexcept {return data_?data_->values.capacity():0;}
const TableId* WindowTables::data() const noexcept {return data_?data_->values.data():nullptr;}
AccountedWindowOptions::AccountedWindowOptions(const resource::MemoryAccount& account,const WindowOptions& source)
    :managed_tables(WindowTables::copy_of(account,source.managed_tables)),width(source.width),fifo(source.fifo),
     max_labels(source.max_labels),max_accounted_bytes(source.max_accounted_bytes),command_work_limit(source.command_work_limit) {}
AccountedWindowOptions::AccountedWindowOptions(const resource::MemoryAccount& account,const AccountedWindowOptions& source)
    :managed_tables(WindowTables::copy_of(account,{source.managed_tables.data(),source.managed_tables.size()},source.managed_tables.capacity())),
     width(source.width),fifo(source.fifo),max_labels(source.max_labels),max_accounted_bytes(source.max_accounted_bytes),
     command_work_limit(source.command_work_limit) {}
struct WindowController::Impl {
  using Fifo=WindowSet<std::uint64_t>;
  resource::MemoryAccount account;
  AccountedWindowOptions options;
  std::array<char,64> catalog_sha256;
  WindowMap<std::uint64_t,NativeLabel> labels;
  WindowMap<std::uint64_t,NativeCount> counts;
  WindowSet<std::pair<std::uint64_t,std::uint64_t>> expirations;
  Fifo global;
  WindowMap<TableId,Fifo> relations;
  std::optional<NativeActiveCommand> active;
  std::uint64_t completed=0,physical=0,watermark=0,last_label=0,work=0;
  std::size_t bytes=0;
  bool prepared=false,stopped=false;
  template<class CatalogView,class Options> Impl(const resource::MemoryAccount& memory,const CatalogView& catalog,const Options& value)
      :account(memory),options(memory,value),catalog_sha256(io::input_detail::catalog_digest(memory,catalog,std::is_same_v<CatalogView,program::Catalog>)),
       labels(std::less<std::uint64_t>{},decltype(labels)::allocator_type(account,resource::MemoryPurpose::support_metadata,window_memory)),
       counts(std::less<std::uint64_t>{},decltype(counts)::allocator_type(account,resource::MemoryPurpose::support_metadata,window_memory)),
       expirations(std::less<std::pair<std::uint64_t,std::uint64_t>>{},decltype(expirations)::allocator_type(account,resource::MemoryPurpose::support_metadata,window_memory)),
       global(std::less<std::uint64_t>{},Fifo::allocator_type(account,resource::MemoryPurpose::support_metadata,window_memory)),
       relations(std::less<TableId>{},decltype(relations)::allocator_type(account,resource::MemoryPurpose::support_metadata,window_memory)) {
    require(options.width>0 && options.max_labels>0 && options.max_accounted_bytes>0 && options.command_work_limit>0,
        "invalid_window_options","window width and resource limits must be positive");
    require(options.fifo==WindowFifoPolicy::global || options.fifo==WindowFifoPolicy::per_relation ||
        options.fifo==WindowFifoPolicy::physical_global || options.fifo==WindowFifoPolicy::physical_per_relation ||
        options.fifo==WindowFifoPolicy::unrestricted,
        "invalid_window_options","unsupported window FIFO policy");
    require(!options.managed_tables.empty(),"invalid_window_options","window requires explicit managed tables");
    for (auto table:options.managed_tables) {
      require(table.value<catalog.tables.size(),"invalid_window_options","unknown managed window table");
      require(relations.try_emplace(table,std::less<std::uint64_t>{},Fifo::allocator_type(
          account,resource::MemoryPurpose::support_metadata,window_memory)).second,"invalid_window_options","duplicate managed window table");
    }
    bytes=add(multiply(options.managed_tables.capacity(),sizeof(TableId)),multiply(relations.size(),sizeof(TableId)));
    require(bytes<=options.max_accounted_bytes,"resource_limit","window options exceed byte limit");
  }
  // Opt-in combined preflight: one integer vector, no retained row/index copy.
  // Positive raw scopes group tables; only the physical-per-relation baseline
  // needs table-distinguished zero scopes. Global physical order dominates all scopes.
  // D live lifetimes require O(D) scratch; sorting/group lookup adds
  // O(D log D + (D+E) log R + E log D) comparisons for E expiring labels.
  template<class Charge> std::size_t preflight_patterns(std::uint64_t mark,
      const patterns::Declaration& declaration, std::uint64_t command,
      PatternViolation* violation, Charge& charge) const {
    if (expirations.empty() || expirations.begin()->first > mark) return 0;
    using Group = std::pair<std::uint64_t, TableId>;
    struct Count { std::pair<Group, std::uint64_t> key; std::uint64_t remaining; };
    const bool global_order = options.fifo == WindowFifoPolicy::physical_global;
    const bool table_order = options.fifo == WindowFifoPolicy::physical_per_relation;
    const auto group = [&](TableId table, const patterns::TableRule* rule) -> Group {
      if (global_order) return {0, TableId{0}};
      if (rule && rule->fifo_scope) return {rule->fifo_scope, TableId{0}};
      return {0, table_order ? table : TableId{0}};
    };
    std::vector<Count, resource::OwnerAllocator<Count>> remaining(
        resource::OwnerAllocator<Count>(account, resource::MemoryPurpose::scratch, window_memory));
    charge(static_cast<std::uint64_t>(counts.size()));
    remaining.reserve(counts.size());
    bool scoped_order = false;
    for (const auto& [id, count] : counts) {
      const auto* rule = pattern_detail::find(declaration, count.table, charge);
      scoped_order = scoped_order || (rule && rule->fifo_scope);
      remaining.push_back({{group(count.table, rule), id}, count.count});
    }
    if (!global_order && (table_order || scoped_order)) std::sort(remaining.begin(), remaining.end(), [&](const Count& a, const Count& b) {
      charge(); return a.key < b.key;
    });
    std::size_t expiring = 0;
    for (const auto& [deadline, id] : expirations) {
      charge(); if (deadline > mark) break;
      const auto& label = labels.find(id)->second;
      const auto* rule = pattern_detail::find(declaration, label.table, charge);
      const auto key = std::pair{group(label.table, rule), label.count_id};
      const auto current = std::lower_bound(remaining.begin(), remaining.end(), key,
          [&](const Count& a, const auto& b) { charge(); return a.key < b; });
      charge();
      if (current->remaining == 1) {
        pattern_detail::require(!rule || !rule->insertion_only, PatternViolationKind::physical_erase,
            label.table, command, id, violation);
        const bool ordered = global_order || table_order || (rule && rule->fifo_scope);
        if (ordered && current != remaining.begin()) {
          const auto previous = std::prev(current);
          // Earlier successful final removals form a zero prefix per group.
          // Its immediate predecessor is enough; partial label removals leave
          // the lifetime live, and therefore cannot advance that prefix.
          const bool front = previous->key.first != key.first || previous->remaining == 0;
          if (global_order || (table_order && (!rule || !rule->fifo_scope)))
            require(front, "window_fifo_violation", "watermark expiration violates physical row lifetime FIFO");
          else pattern_detail::require(front, PatternViolationKind::fifo_scope, label.table, command, id, violation);
        }
      }
      --current->remaining;
      ++expiring;
    }
    return expiring;
  }
  template<class Charge> std::size_t preflight_lifetimes(std::uint64_t mark,Charge& charge) const {
    if(expirations.empty() || expirations.begin()->first>mark)return 0;
    struct Count {std::pair<TableId,std::uint64_t> key;std::uint64_t remaining;};
    // One transient counter vector on the original account; native rows and
    // retained indexes are borrowed. The label policies never build this scratch.
    std::vector<Count,resource::OwnerAllocator<Count>> remaining(
        resource::OwnerAllocator<Count>(account,resource::MemoryPurpose::scratch,window_memory));
    charge(static_cast<std::uint64_t>(counts.size()));
    remaining.reserve(counts.size());
    const bool per_relation=options.fifo==WindowFifoPolicy::physical_per_relation;
    for(const auto& [id,count]:counts)
      remaining.push_back({{per_relation?count.table:TableId{0},id},count.count});
    if(per_relation)std::sort(remaining.begin(),remaining.end(),[&](const Count& a,const Count& b) {
      charge();return a.key<b.key;
    });
    std::size_t expiring=0;
    for(const auto& [deadline,id]:expirations) {
      charge();if(deadline>mark)break;
      const auto& label=labels.find(id)->second;
      const auto key=std::pair{per_relation?label.table:TableId{0},label.count_id};
      const auto current=std::lower_bound(remaining.begin(),remaining.end(),key,[&](const Count& a,const auto& b) {
        charge();return a.key<b;
      });
      // Validated label/count references make current present and positive.
      // Zero counters form a prefix in each group: the predecessor test is
      // exactly the oldest-live-lifetime condition on a final reference.
      charge();
      if(current->remaining==1 && current!=remaining.begin()) {
        const auto previous=std::prev(current);
        require(previous->key.first!=key.first || previous->remaining==0,
            "window_fifo_violation","watermark expiration violates physical row lifetime FIFO");
      }
      --current->remaining;++expiring;
    }
    return expiring;
  }
};
struct WindowController::Prepared::Data {
  Impl* owner;
  storage::AccountedRow update_values;
  std::optional<PhysicalUpdateView> update;
  decltype(Impl::labels)::node_type label_node;
  decltype(Impl::counts)::node_type count_node;
  decltype(Impl::expirations)::node_type expiration_node;
  Impl::Fifo::node_type global_node,relation_node;
  std::optional<NativeActiveCommand> new_active;
  std::uint64_t command=0,label=0,count=0,watermark=0,work=0;
  std::size_t bytes=0;
  bool insertion=false,removal=false,complete=true,is_watermark=false;
  explicit Data(Impl& d):owner(&d) {}
  ~Data() { if (owner) owner->prepared=false; }
};
WindowController::Prepared::Prepared(resource::AccountedUnique<Data> data) noexcept:data_(std::move(data)) {}
WindowController::Prepared::~Prepared()=default;
WindowController::Prepared::Prepared(Prepared&&) noexcept=default;
WindowController::Prepared& WindowController::Prepared::operator=(Prepared&&) noexcept=default;
const std::optional<PhysicalUpdateView>& WindowController::Prepared::update() const noexcept { return data_->update; }
bool WindowController::Prepared::completes_command() const noexcept { return data_->complete; }
void WindowController::Prepared::publish() noexcept {
  // Caller has committed the native step or metadata barrier. Funded integer
  // nodes move without allocation; erasures/searches still have their real cost.
  if (!data_ || !data_->owner) return;
  auto& p=*data_; auto& d=*p.owner;
  if (p.insertion) {
    const auto table=p.label_node.mapped().table;
    d.labels.insert(std::move(p.label_node));
    if (p.count_node) d.counts.insert(std::move(p.count_node));
    else ++d.counts.find(p.count)->second.count;
    d.expirations.insert(std::move(p.expiration_node));
    d.global.insert(std::move(p.global_node));
    d.relations.find(table)->second.insert(std::move(p.relation_node));
    d.last_label=p.label;
  } else if (p.removal) {
    const auto entry=d.labels.find(p.label);
    d.expirations.erase({entry->second.deadline,p.label});
    d.relations.find(entry->second.table)->second.erase(p.label);
    d.global.erase(p.label); d.labels.erase(entry);
    const auto count=d.counts.find(p.count);
    if (--count->second.count==0) d.counts.erase(count);
  }
  if (p.new_active) d.active=std::move(p.new_active);
  if (p.is_watermark) {
    if (d.active) ++d.active->completed_steps;
    if (p.complete) { d.watermark=p.watermark; d.active.reset(); }
  }
  if (p.complete) d.completed=p.command;
  if (p.update) d.physical=p.update->sequence;
  d.bytes=p.bytes; d.work=p.work; d.prepared=false; p.owner=nullptr;
}
WindowController::WindowController(Catalog catalog,WindowOptions options)
    :data_([&] {
      // Standalone adapter admission has its own finite account. Query sessions
      // always use the explicit original-account constructor below.
      const auto account=resource::MemoryAccount::create(std::numeric_limits<std::uint64_t>::max());
      return resource::make_accounted_shared<Impl>({resource::MemoryOwnerKind::session,0},account,
          resource::MemoryPurpose::support_metadata,account,catalog,options);
    }()) {}
WindowController::WindowController(const resource::MemoryAccount& account,const program::Catalog& catalog,const WindowOptions& options)
    :data_(resource::make_accounted_shared<Impl>({resource::MemoryOwnerKind::session,0},account,
        resource::MemoryPurpose::support_metadata,account,catalog,options)) {}
namespace {
void state_require(bool condition,recovery::ImageFault fault=recovery::ImageFault::corrupt) {
  if(!condition)throw recovery::ImageFailure(fault);
}
struct StateBudget {
  WindowStateLimits limits;
  std::uint64_t used=0;
  void charge(std::uint64_t amount=1) {
    state_require(used<=limits.work && amount<=limits.work-used,recovery::ImageFault::work);used+=amount;
  }
  void row(storage::RowView values) {charge();charge(values.size());}
};
struct StateKey {TableId table;storage::RowView values;};
struct StateKeyLess {
  StateBudget* budget;
  bool operator()(const StateKey& a,const StateKey& b) const {
    budget->charge();if(a.table!=b.table)return a.table<b.table;
    budget->charge(a.values.size());budget->charge(b.values.size());return a.values<b.values;
  }
};
}
WindowCheckpoint WindowController::checkpoint_state(WindowStateLimits limits) const {
  // Own cloned native rows on this account. A partial watermark, including a
  // stopped tombstone, is not a quiescent command checkpoint.
  const auto& d=*data_;state_require(!d.prepared && !d.active);
  state_require(d.labels.size()<=limits.labels && d.counts.size()<=limits.counts,recovery::ImageFault::limit);
  StateBudget budget{limits};budget.charge();budget.charge(d.options.managed_tables.size());
  for(const auto& [id,row]:d.labels){static_cast<void>(id);budget.row(row.values.view());}
  for(const auto& [id,row]:d.counts){static_cast<void>(id);budget.row(row.values.view());}
  WindowCheckpoint result(d.account,d.options);result.progress=progress();result.catalog_sha256=d.catalog_sha256;
  result.last_command_work=d.work;result.work=budget.used;result.stopped=d.stopped;
  result.labels.reserve(d.labels.size());result.counts.reserve(d.counts.size());
  for(const auto& [id,row]:d.labels)result.labels.push_back({id,row.table,row.values.clone(d.account,recovery::image_owner),row.timestamp,row.deadline,row.count_id});
  for(const auto& [id,row]:d.counts)result.counts.push_back({id,row.table,row.values.clone(d.account,recovery::image_owner),row.count});
  return result;
}
WindowController::WindowController(const resource::MemoryAccount& account,const program::Catalog& catalog,
    const WindowCheckpoint& source,WindowStateLimits limits)
    :data_([&] {
  // Rebuild private indexes and exact count references before publishing a
  // controller. Native base/window membership matching belongs to session restore.
      state_require(!source.progress.active_command_sequence && !source.progress.completed_steps && !source.progress.total_steps);
      state_require(source.labels.size()<=limits.labels && source.counts.size()<=limits.counts &&
          source.labels.size()<=source.options.max_labels,recovery::ImageFault::limit);
      state_require(source.last_command_work<=source.options.command_work_limit);
      state_require(source.progress.physical_sequence>=source.counts.size());
      state_require(source.options.managed_tables.capacity()<=source.options.max_accounted_bytes/sizeof(TableId),recovery::ImageFault::limit);
      StateBudget budget{limits};budget.charge();budget.charge(source.options.managed_tables.size());
      auto result=resource::make_accounted_shared<Impl>(window_memory,account,resource::MemoryPurpose::support_metadata,
          account,catalog,source.options);
      auto& d=*result;state_require(d.catalog_sha256==source.catalog_sha256,recovery::ImageFault::binding);
      using Unique=std::map<StateKey,std::uint64_t,StateKeyLess,resource::MemoryAllocator<std::pair<const StateKey,std::uint64_t>>>;
      Unique unique(StateKeyLess{&budget},Unique::allocator_type(account,resource::MemoryPurpose::scratch,window_memory));
      WindowMap<std::uint64_t,std::uint64_t> references(std::less<std::uint64_t>{},decltype(references)::allocator_type(
          account,resource::MemoryPurpose::scratch,window_memory));
      std::uint64_t previous=0;
      for(const auto& count:source.counts) {
        budget.row(count.values.view());
        state_require(count.id>previous && count.id<=source.progress.last_label && count.count>0 && d.relations.contains(count.table));previous=count.id;
        detail::validate_native_row(catalog,count.table,storage::TupleValuesView::borrow(count.values.view()));
        state_require(unique.emplace(StateKey{count.table,count.values.view()},count.id).second);
        d.bytes=add(d.bytes,count_bytes(count));state_require(d.bytes<=d.options.max_accounted_bytes,recovery::ImageFault::limit);
        d.counts.emplace(count.id,NativeCount{count.id,count.table,count.values.clone(account,window_memory),count.count});
        references.emplace(count.id,0);
      }
      previous=0;
      for(const auto& label:source.labels) {
        budget.row(label.values.view());
        state_require(label.label>previous && label.label<=source.progress.last_label && label.count_id<=label.label && d.relations.contains(label.table));previous=label.label;
        state_require(label.timestamp<=UINT64_MAX-d.options.width && label.deadline==label.timestamp+d.options.width && label.deadline>source.progress.completed_watermark);
        const auto count=d.counts.find(label.count_id);state_require(count!=d.counts.end());
        budget.row(count->second.values.view());state_require(count->second.table==label.table && count->second.values.view()==label.values.view());
        auto& referenced=references.find(label.count_id)->second;state_require(referenced<count->second.count);++referenced;
        d.bytes=add(d.bytes,label_bytes(label));state_require(d.bytes<=d.options.max_accounted_bytes,recovery::ImageFault::limit);
        d.labels.emplace(label.label,NativeLabel{label.label,label.table,label.values.clone(account,window_memory),label.timestamp,label.deadline,label.count_id});
        d.expirations.emplace(label.deadline,label.label);d.global.insert(label.label);d.relations.find(label.table)->second.insert(label.label);
      }
      for(const auto& [id,count]:d.counts){budget.charge();state_require(references.find(id)->second==count.count);}
      if(source.progress.completed_command_sequence==0)
        state_require(source.progress.physical_sequence==0 && source.progress.completed_watermark==0 && source.progress.last_label==0 && d.labels.empty() && d.counts.empty());
      d.completed=source.progress.completed_command_sequence;d.physical=source.progress.physical_sequence;
      d.watermark=source.progress.completed_watermark;d.last_label=source.progress.last_label;d.work=source.last_command_work;d.stopped=source.stopped;
      return result;
    }()) {}
WindowController::~WindowController()=default;
#ifdef CROWN_RUNTIME_TESTING
void RuntimeTestProbe::seed_window_sequence(WindowController& runtime,std::uint64_t sequence) {
  require(!runtime.data_->prepared && !runtime.data_->stopped,"invalid_probe","window sequence probe needs a writable owner");
  runtime.data_->physical=sequence;
}
#endif
const AccountedWindowOptions& WindowController::options() const noexcept { return data_->options; }
WindowMetrics WindowController::metrics() const noexcept {
  return {data_->labels.size(),data_->counts.size(),data_->bytes,data_->work};
}
WindowProgress WindowController::progress() const noexcept {
  const auto& d=*data_;
  WindowProgress p{d.completed,d.physical,d.watermark,d.last_label,std::nullopt,0,0};
  if (d.active) { p.active_command_sequence=d.active->sequence; p.completed_steps=d.active->completed_steps; p.total_steps=d.active->total_steps; }
  return p;
}
void WindowController::stop() noexcept {
  auto& d=*data_; d.stopped=true;
  if (d.active) {
    d.bytes-=d.active->expiration_labels.capacity()*sizeof(std::uint64_t);
    decltype(d.active->expiration_labels)(d.active->expiration_labels.get_allocator()).swap(d.active->expiration_labels);
  }
}
WindowCanonicalState WindowController::canonical_state() const {
  // Explicit external diagnostic: full ordinary Row/vector copies are outside
  // the native operational graph and have whole-state scan/allocation cost.
  const auto& d=*data_; WindowCanonicalState s;
  for (const auto& [id,label]:d.labels) { (void)id; s.labels.push_back({label.label,label.table,storage::export_row(label.values.view()),label.timestamp,label.deadline,label.count_id}); }
  for (const auto& [id,count]:d.counts) { (void)id; s.counts.push_back({count.id,count.table,storage::export_row(count.values.view()),count.count}); }
  s.expiration_index.assign(d.expirations.begin(),d.expirations.end());
  s.global_fifo.assign(d.global.begin(),d.global.end());
  for (const auto& [table,fifo]:d.relations) s.relation_fifo.push_back({table,{fifo.begin(),fifo.end()}});
  s.completed_command_sequence=d.completed; s.physical_sequence=d.physical;
  s.completed_watermark=d.watermark; s.last_label=d.last_label;
  if(d.active)s.active_command=WindowActiveCommand{d.active->sequence,d.active->watermark,
      {d.active->expiration_labels.begin(),d.active->expiration_labels.end()},d.active->completed_steps,d.active->total_steps,d.active->accounted_work};
  s.metrics=metrics();
  return s;
}
WindowController::Prepared WindowController::prepare(const io::WindowCommand& command,std::uint64_t next_physical_sequence) {
  return prepare_view(io::WindowCommandView::borrow(command),next_physical_sequence);
}
bool WindowController::manages(TableId table) const noexcept { return data_->relations.contains(table); }
WindowController::Prepared WindowController::prepare_view(const io::WindowCommandView& command,std::uint64_t next_physical_sequence) {
  return prepare_pattern_view(command,next_physical_sequence,nullptr,nullptr);
}
WindowController::Prepared WindowController::prepare_pattern_view(const io::WindowCommandView& command,
    std::uint64_t next_physical_sequence,const patterns::Declaration* declaration,PatternViolation* violation) {
  // Only distinct-row presence changes produce physical set epochs. Every
  // node/row and whole-watermark FIFO/work reservation precedes publication.
  auto& d=*data_;
  require(!d.stopped,"invalid_window_command","window controller is stopped");
  require(!d.prepared,"window_step_pending","only one prepared window step may exist");
  require(d.completed!=std::numeric_limits<std::uint64_t>::max() && command.sequence==d.completed+1,
      "invalid_window_command","window commands must have contiguous sequences");
  auto p=resource::make_accounted_unique<Prepared::Data>(window_memory,d.account,resource::MemoryPurpose::journal_undo,d);
  // Do not mark owner busy until every allocating preparation has succeeded.
  p->command=command.sequence; p->bytes=d.bytes;
  if (d.active) p->work=d.active->accounted_work;
  auto charge=[&](std::uint64_t n=1) {
    require(n<=d.options.command_work_limit-p->work,"resource_limit","window command work limit exceeded"); p->work+=n;
  };
  auto check_bytes=[&] { require(p->bytes<=d.options.max_accounted_bytes,"resource_limit","window retained byte limit exceeded"); };
  auto physical=[&](TableId table,SetOperation operation,storage::RowView row) {
    require(d.physical!=std::numeric_limits<std::uint64_t>::max(),"resource_limit","physical sequence exhausted");
    require(next_physical_sequence==d.physical+1,
        "invalid_window_command","physical transitions must have contiguous sequences");
    p->update_values=storage::AccountedRow::copy_of(d.account,row,window_memory);
    p->update.emplace(PhysicalUpdateView{next_physical_sequence,table,operation,storage::TupleValuesView::borrow(p->update_values.view())});
  };
  auto remove=[&](std::uint64_t id,bool check_fifo) {
    if (!p->is_watermark) charge();
    const auto found=d.labels.find(id);
    require(found!=d.labels.end(),"invalid_window_command","withdrawal names an unknown label");
    const auto& label=found->second;
    const auto& count=d.counts.find(label.count_id)->second;
    if (check_fifo && count.count == 1 && declaration && declaration->constrained()) {
      const auto* rule = pattern_detail::find(*declaration, label.table, charge);
      pattern_detail::require(!rule || !rule->insertion_only, PatternViolationKind::physical_erase,
          label.table, command.sequence, id, violation);
      if (rule && rule->fifo_scope && d.options.fifo != WindowFifoPolicy::physical_global) {
        for (const auto& [birth, live] : d.counts) {
          charge();
          const auto* member = pattern_detail::find(*declaration, live.table, charge);
          if (!member || member->fifo_scope != rule->fifo_scope) continue;
          pattern_detail::require(birth == label.count_id, PatternViolationKind::fifo_scope,
              label.table, command.sequence, id, violation);
          break;
        }
      }
    }
    if(check_fifo)switch(d.options.fifo) {
      case WindowFifoPolicy::unrestricted:break;
      case WindowFifoPolicy::global:
        require(*d.global.begin()==id,"window_fifo_violation","withdrawal is not the oldest live label");break;
      case WindowFifoPolicy::per_relation:
        require(*d.relations.find(label.table)->second.begin()==id,"window_fifo_violation","withdrawal is not the oldest live label");break;
      case WindowFifoPolicy::physical_global:
        require(count.count>1 || d.counts.begin()->first==label.count_id,
            "window_fifo_violation","withdrawal is not the oldest live physical row");break;
      case WindowFifoPolicy::physical_per_relation:
        if(count.count==1)for(const auto& [birth,live]:d.counts) {
          charge();if(live.table!=label.table)continue;
          require(birth==label.count_id,"window_fifo_violation","withdrawal is not the oldest live relation row");break;
        }
        break;
    }
    p->removal=true; p->label=id; p->count=label.count_id;
    p->bytes-=label_bytes(label);
    if (count.count==1) { physical(label.table,SetOperation::erase,label.values.view()); p->bytes-=count_bytes(count); }
  };
  const auto* wm=std::get_if<io::AdvanceWatermark>(&command.command);
  require(!d.active || (wm && command.sequence==d.active->sequence && wm->watermark==d.active->watermark),
      "invalid_window_command","an active watermark must complete before another command");
  if (const auto* insert=std::get_if<io::WindowInsertView>(&command.command)) {
    charge();
    require(insert->label>d.last_label,"invalid_window_command","insertion labels must be positive and strictly increasing");
    require(d.relations.contains(insert->table),"invalid_window_command","insertion table is not window managed");
    require(insert->timestamp>=d.watermark,"late_window_event","insertion precedes the completed watermark");
    require(insert->timestamp<=std::numeric_limits<std::uint64_t>::max()-d.options.width,
        "invalid_window_command","window expiration timestamp overflow");
    require(d.labels.size()<d.options.max_labels,"resource_limit","window live label limit exceeded");
    std::uint64_t count_id=insert->label;
    bool new_count=true;
    for (const auto& [id,count]:d.counts) {
      charge(); charge(static_cast<std::uint64_t>(insert->values.size()));
      if (count.table==insert->table && count.values.view()==insert->values) { count_id=id; new_count=false; break; }
    }
    if (new_count) {
      decltype(d.counts) nodes(d.counts.key_comp(),d.counts.get_allocator());
      auto it=nodes.emplace(count_id,NativeCount{count_id,insert->table,storage::AccountedRow::copy_view(d.account,insert->values,window_memory),1}).first;
      p->bytes=add(p->bytes,count_bytes(it->second)); p->count_node=nodes.extract(it);
      physical(insert->table,SetOperation::insert,it->second.values.view());
    } else require(d.counts.find(count_id)->second.count<std::numeric_limits<std::uint64_t>::max(),"resource_limit","window row count overflow");
    decltype(d.labels) nodes(d.labels.key_comp(),d.labels.get_allocator());
    auto it=nodes.emplace(insert->label,NativeLabel{insert->label,insert->table,storage::AccountedRow::copy_view(d.account,insert->values,window_memory),insert->timestamp,insert->timestamp+d.options.width,count_id}).first;
    p->bytes=add(p->bytes,label_bytes(it->second));
    decltype(d.expirations) expiration(d.expirations.key_comp(),d.expirations.get_allocator());
    expiration.emplace(it->second.deadline,insert->label); p->expiration_node=expiration.extract(expiration.begin());
    p->label_node=nodes.extract(it);
    Impl::Fifo fifo(d.global.key_comp(),d.global.get_allocator()); fifo.insert(insert->label); p->global_node=fifo.extract(fifo.begin());
    fifo.insert(insert->label); p->relation_node=fifo.extract(fifo.begin());
    p->insertion=true; p->label=insert->label; p->count=count_id;
  } else if (const auto* withdraw=std::get_if<io::WindowWithdraw>(&command.command)) remove(withdraw->label,true);
  else if (wm) {
    p->is_watermark=true; p->watermark=wm->watermark;
    require(wm->watermark>=d.watermark,"invalid_window_command","watermarks must not decrease");
    if (!d.active) {
      NativeActiveCommand active(d.account,command.sequence,wm->watermark);
      std::size_t expiring=0;
      const bool declared = declaration && declaration->constrained();
      const bool physical_order = d.options.fifo==WindowFifoPolicy::physical_global ||
          d.options.fifo==WindowFifoPolicy::physical_per_relation;
      if (declared) expiring = d.preflight_patterns(wm->watermark,*declaration,command.sequence,violation,charge);
      if (physical_order) {
        if (!declared) expiring=d.preflight_lifetimes(wm->watermark,charge);
      } else {
        // Existing label policies use only cursors into insertion indexes.
        auto global=d.global.begin();
        WindowMap<TableId,Impl::Fifo::const_iterator> cursors(std::less<TableId>{},
            resource::MemoryAllocator<std::pair<const TableId,Impl::Fifo::const_iterator>>(d.account,resource::MemoryPurpose::scratch,window_memory));
        if (d.options.fifo==WindowFifoPolicy::per_relation)
          for (const auto& [table,fifo]:d.relations) { charge(); cursors.emplace(table,fifo.begin()); }
        for (const auto& [deadline,id]:d.expirations) {
          charge(); if (deadline>wm->watermark) break;
          const auto& label=d.labels.find(id)->second;
          if (d.options.fifo==WindowFifoPolicy::global) {
            require(global!=d.global.end() && *global==id,"window_fifo_violation","watermark expiration violates global label FIFO"); ++global;
          } else if (d.options.fifo==WindowFifoPolicy::per_relation) {
            auto& cursor=cursors.find(label.table)->second;
            require(cursor!=d.relations.find(label.table)->second.end() && *cursor==id,"window_fifo_violation","watermark expiration violates relation label FIFO"); ++cursor;
          }
          if (!declared) ++expiring;
        }
      }
      if (expiring) {
        p->bytes=add(p->bytes,add(sizeof(NativeActiveCommand),multiply(expiring,sizeof(std::uint64_t)))); check_bytes();
        active.expiration_labels.reserve(expiring);
        for (const auto& [deadline,id]:d.expirations) { if (deadline>wm->watermark) break; charge(); active.expiration_labels.push_back(id); }
        // Account actual vector capacity, not the requested capacity.
        p->bytes=add(d.bytes,add(sizeof(NativeActiveCommand),multiply(active.expiration_labels.capacity(),sizeof(std::uint64_t)))); check_bytes();
        charge(static_cast<std::uint64_t>(expiring)); // Reserve all future removal work now.
        active.total_steps=expiring; active.accounted_work=p->work;
        p->new_active.emplace(std::move(active));
      }
    }
    const auto* active=d.active?&*d.active:(p->new_active?&*p->new_active:nullptr);
    if (active) {
      remove(active->expiration_labels[active->completed_steps],false);
      p->complete=active->completed_steps+1==active->expiration_labels.size();
      if (p->complete) p->bytes-=sizeof(NativeActiveCommand)+active->expiration_labels.capacity()*sizeof(std::uint64_t);
    } else charge();
  } else require(false,"invalid_window_command","unknown window command");
  check_bytes(); d.prepared=true;
  return Prepared(std::move(p));
}
}  // namespace crown::runtime
