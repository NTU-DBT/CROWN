#include "crown/io/batch.hpp"

#include "crown/api/error.hpp"
#include "crown/catalog/catalog.hpp"
#include "catalog_source.hpp"
#include "input_native.hpp"
#include "checkpoint_detail.hpp"
#include "native_input.hpp"
#include "crown/resource/text.hpp"
#include <limits>
#include <type_traits>
#include <utility>

namespace crown::io {
namespace {
void require(bool condition,std::string_view code,std::string_view message) {
  if (!condition) throw Error(std::string(code),std::string(message));
}
std::size_t add(std::size_t a,std::size_t b) {
  require(b<=std::numeric_limits<std::size_t>::max()-a,"resource_limit","typed input size accounting exhausted");
  return a+b;
}
std::size_t slots(std::size_t n,std::size_t width) {
  require(n<=std::numeric_limits<std::size_t>::max()/width,"resource_limit","typed input capacity accounting exhausted");
  return n*width;
}
std::size_t row_bytes(const Row& row) {
  auto bytes=slots(row.capacity(),sizeof(Value));
  for (const auto& value : row) {
    if (const auto* text=std::get_if<std::string>(&value)) bytes=add(bytes,add(text->capacity(),1));
    else if (std::holds_alternative<Decimal>(value)) bytes=add(bytes,64);
  }
  return bytes;
}
std::size_t item_payload(const InputItem& item) {
  return std::visit([](const auto& event) {
    std::size_t bytes=0;
    using T=std::decay_t<decltype(event)>;
    if constexpr (std::is_same_v<T,InputEvent>) bytes=row_bytes(event.update.values);
    else if (const auto* insert=std::get_if<WindowInsert>(&event.command)) bytes=row_bytes(insert->values);
    if (event.source_position) bytes=add(bytes,add(event.source_position->source.capacity(),1));
    return bytes;
  },item);
}
std::uint64_t sequence_of(const InputItemView& item) noexcept {
  if (const auto* event=std::get_if<InputEventView>(&item)) return event->update.sequence;
  return std::get<WindowCommandView>(item).sequence;
}
const std::optional<SourcePositionView>& position_of(const InputItemView& item) noexcept {
  if (const auto* event=std::get_if<InputEventView>(&item)) return event->source_position;
  return std::get<WindowCommandView>(item).source_position;
}
}  // namespace

struct TransportBatch::Data {
  struct Item { InputItem value; std::size_t bytes; };
  std::list<Item> items;
  std::size_t bytes=sizeof(Data);
};
// Ordered transport preserves each event barrier; it is not a net transaction.
TransportBatch::TransportBatch(std::vector<InputItem> items,BatchLimits limits) {
  require(items.size()<=limits.events,"resource_limit","transport batch event limit exceeded");
  if (items.empty()) return;
  data_=std::make_unique<Data>();
  require(data_->bytes<=limits.bytes,"resource_limit","transport batch descriptor limit exceeded");
  // Admit the full DTO capacity model before event-node allocation or moving
  // payloads. Allocator framing and constructor input overlap remain separate.
  auto bytes=data_->bytes;
  for (const auto& item : items) {
    require(!item.valueless_by_exception(),"invalid_input_kind","transport item has no payload");
    bytes=add(bytes,add(sizeof(Data::Item)+2*sizeof(void*),item_payload(item)));
    require(bytes<=limits.bytes,"resource_limit","transport batch byte limit exceeded");
  }
  for (auto& item : items) {
    const auto owned=add(sizeof(Data::Item)+2*sizeof(void*),item_payload(item));
    data_->items.push_back({std::move(item),owned});
  }
  data_->bytes=bytes;
}
TransportBatch::~TransportBatch()=default;
TransportBatch::TransportBatch(TransportBatch&&) noexcept=default;
TransportBatch& TransportBatch::operator=(TransportBatch&&) noexcept=default;
bool TransportBatch::empty() const noexcept { return !data_ || data_->items.empty(); }
std::size_t TransportBatch::size() const noexcept { return data_?data_->items.size():0; }
std::size_t TransportBatch::accounted_bytes() const noexcept { return data_?data_->bytes:0; }

struct TypedQueue::Data {
  struct Item {
    resource::AccountedUnique<Item> next;
    storage::AccountedRow row;
    resource::AccountedText source;
    InputItemView value;
    input_detail::RowIssue issue;
    std::size_t bytes=0;
    static const Row* row_of(const InputItem& input) noexcept {
      if(const auto* event=std::get_if<InputEvent>(&input))return &event->update.values;
      if(const auto* insert=std::get_if<WindowInsert>(&std::get<WindowCommand>(input).command))return &insert->values;
      return nullptr;
    }
    static TableId table_of(const InputItem& input) noexcept {
      if(const auto* event=std::get_if<InputEvent>(&input))return event->update.table;
      if(const auto* insert=std::get_if<WindowInsert>(&std::get<WindowCommand>(input).command))return insert->table;
      return TableId{0};
    }
    static InputItemView borrow(const InputItem& input) noexcept {
      if(const auto* event=std::get_if<InputEvent>(&input))return InputEventView::borrow(*event);
      return WindowCommandView::borrow(std::get<WindowCommand>(input));
    }
    static std::size_t request(std::uint64_t bytes) {
      require(bytes<=std::numeric_limits<std::size_t>::max(),"resource_limit","typed input capacity accounting exhausted");
      return static_cast<std::size_t>(bytes);
    }
    static std::size_t owned_bytes(const InputItem& input,input_detail::RowIssue issue) {
      auto bytes=request(resource::MemoryAccount::allocation_bytes(sizeof(Item),alignof(Item)));
      if(const auto* row=row_of(input);row && issue.problem==input_detail::RowProblem::none)
        bytes=add(bytes,request(storage::AccountedRow::allocation_usage_for(*row).requested_bytes));
      const auto value=borrow(input);
      if(const auto& position=position_of(value))
        bytes=add(bytes,request(resource::AccountedText::allocation_usage_for(position->source).requested_bytes));
      return bytes;
    }
    Item(const resource::MemoryAccount& account,const InputItemView& input):value(input) {
      const auto* physical=std::get_if<InputEventView>(&input);
      const auto* insert=physical?nullptr:std::get_if<WindowInsertView>(&std::get<WindowCommandView>(input).command);
      issue.arity=physical?physical->update.values.size():insert?insert->values.size():0;
      if(physical || insert)row=storage::AccountedRow::copy_view(account,physical?physical->update.values:insert->values,input_detail::memory_owner);
      if(const auto& position=position_of(input))source=resource::AccountedText::copy_of(account,position->source,input_detail::memory_owner);
      bytes=request(resource::MemoryAccount::allocation_bytes(sizeof(Item),alignof(Item)));
      bytes=add(bytes,request(row.memory_usage().requested_bytes));bytes=add(bytes,request(source.memory_usage().requested_bytes));
      const auto native=storage::TupleValuesView::borrow(row.view());
      if(auto* event=std::get_if<InputEventView>(&value)){event->update.values=native;if(event->source_position)event->source_position->source=source.view();}
      else {auto& command=std::get<WindowCommandView>(value);if(auto* item=std::get_if<WindowInsertView>(&command.command))item->values=native;if(command.source_position)command.source_position->source=source.view();}
    }
    // Keep a permanent malformed-row issue instead of freezing unusable values.
    // The original envelope/column-limit/head diagnostic order is checked at peek.
    Item(const resource::MemoryAccount& account,const InputItem& input,input_detail::RowIssue problem)
        :value(borrow(input)),issue(problem),bytes(owned_bytes(input,problem)) {
      if(const auto* values=row_of(input);values && issue.problem==input_detail::RowProblem::none)
        row=storage::AccountedRow::copy_of(account,*values,input_detail::memory_owner);
      if(const auto& position=position_of(value))source=resource::AccountedText::copy_of(account,position->source,input_detail::memory_owner);
      const auto native=storage::TupleValuesView::borrow(row.view());
      if(auto* event=std::get_if<InputEventView>(&value)) {
        event->update.values=native;
        if(event->source_position)event->source_position->source=source.view();
      }else {
        auto& command=std::get<WindowCommandView>(value);
        if(auto* insert=std::get_if<WindowInsertView>(&command.command))insert->values=native;
        if(command.source_position)command.source_position->source=source.view();
      }
    }
  };
  struct Batch {
    resource::AccountedUnique<Batch> next;
    resource::AccountedUnique<Item> head;
    Item* tail=nullptr;
    std::size_t bytes=0;
    ~Batch() noexcept {
      // Detach each link before destruction: a large offered batch must not
      // turn teardown or failed import into recursive stack growth.
      while(head){auto item=std::move(head);head=std::move(item->next);}
    }
  };
  resource::MemoryAccount account;
  CatalogSource catalog;
  QueueMode mode;
  QueueLimits limits;
  InputLimits input_limits;
  resource::AccountedUnique<Batch> head;
  Batch* tail=nullptr;
  AccountedInputProgress accepted;
  InputPositions::Prepared prepared_position;
  QueueStats stats;
  bool cached=false;
  Data(const resource::MemoryAccount& memory,CatalogSource schema,QueueMode kind,QueueLimits cap,InputLimits input_cap,bool admitted)
      :account(memory),catalog(std::move(schema)),mode(kind),limits(cap),input_limits(input_cap),accepted(account) {
    if(!admitted)catalog_source_detail::read(catalog,[](const auto& value){catalog::validate_catalog(value);});
    require(mode==QueueMode::physical || mode==QueueMode::window,"invalid_input_options","unknown typed queue mode");
    require(!input_limits.total_bytes,"invalid_input_options","wire total byte limits do not apply to typed queues; use queue and batch byte limits");
  }
  ~Data() noexcept {while(head){auto batch=std::move(head);head=std::move(batch->next);}}
  input_detail::RowIssue row_issue(const InputItem& input) const {
    const auto* values=Item::row_of(input);if(!values)return {};
    return catalog_source_detail::read(catalog,[&](const auto& schema){return input_detail::row_issue(
        schema,Item::table_of(input),storage::TupleValuesView::borrow(*values));});
  }
};
TypedQueue::TypedQueue(CatalogSource catalog,QueueMode mode,QueueLimits limits,InputLimits input_limits)
    :TypedQueue(resource::MemoryAccount::create(std::numeric_limits<std::uint64_t>::max()),
        std::move(catalog),mode,limits,input_limits,false) {}
TypedQueue::TypedQueue(const resource::MemoryAccount& account,CatalogSource catalog,QueueMode mode,
    QueueLimits limits,InputLimits input_limits,bool admitted)
    :data_(resource::make_accounted_unique<Data>(input_detail::memory_owner,account,resource::MemoryPurpose::support_metadata,
        account,std::move(catalog),mode,limits,input_limits,admitted)) {}
TypedQueue::~TypedQueue()=default;
TypedQueue::TypedQueue(const resource::MemoryAccount& account,CatalogSource catalog,const QueueCheckpoint& state,const SourceStateLimits& limits,bool admitted)
    :data_([&] {
      checkpoint_detail::Budget budget{limits};budget.positions(state.progress,state.input_limits);
      checkpoint_detail::require(!state.input_limits.records || state.progress.sequence<=*state.input_limits.records);
      checkpoint_detail::require(state.progress.source_positions.size()<=state.progress.sequence);
      auto result=resource::make_accounted_unique<Data>(input_detail::memory_owner,account,resource::MemoryPurpose::support_metadata,
          account,std::move(catalog),state.mode,state.limits,state.input_limits,admitted);
      checkpoint_detail::require(checkpoint_detail::hash(input_detail::catalog_fingerprint(account,result->catalog,true).view())==state.catalog_sha256,
          recovery::ImageFault::binding);
      result->accepted=AccountedInputProgress(account,state.progress);result->stats.closed=state.closed;return result;
    }()) {}
QueueCheckpoint TypedQueue::checkpoint_state() const {return checkpoint_state(SourceStateLimits{});}
QueueCheckpoint TypedQueue::checkpoint_state(const SourceStateLimits& limits) const {
  checkpoint_detail::require(bool(data_));const auto& d=*data_;
  checkpoint_detail::require(!d.head && !d.cached && !d.stats.failed);
  checkpoint_detail::Budget budget{limits};budget.positions(d.accepted,d.input_limits);
  const auto hash=checkpoint_detail::hash(input_detail::catalog_fingerprint(d.account,d.catalog,true).view());
  return {AccountedInputProgress(d.account,d.accepted),d.mode,d.limits,d.input_limits,d.stats.closed,hash,budget.used};
}
TypedQueue::TypedQueue(TypedQueue&&) noexcept=default;
TypedQueue& TypedQueue::operator=(TypedQueue&&) noexcept=default;
Admission TypedQueue::enqueue(TransportBatch& batch) {
  require(bool(data_),"invalid_input_reader","closed typed input queue");auto& d=*data_;
  require(!d.stats.closed,"input_closed","typed input has been finished");
  require(!d.stats.failed,"input_failed","typed input failed at its current head");
  if(batch.empty()){batch.data_.reset();return Admission::accepted;}
  if(d.stats.batches>=d.limits.batches || batch.size()>d.limits.events-d.stats.events)return Admission::full;
  auto bytes=Data::Item::request(resource::MemoryAccount::allocation_bytes(sizeof(Data::Batch),alignof(Data::Batch)));
  const auto remaining=d.limits.bytes-d.stats.accounted_bytes;
  if(bytes>remaining)return Admission::full;
  for(const auto& item:batch.data_->items) {
    bytes=add(bytes,Data::Item::owned_bytes(item.value,d.row_issue(item.value)));
    if(bytes>remaining)return Admission::full;
  }
  const auto before=d.account.current_usage().requested_bytes;
  auto prepared=resource::make_accounted_unique<Data::Batch>(input_detail::memory_owner,d.account,resource::MemoryPurpose::support_metadata);
  prepared->bytes=bytes;
  for(const auto& item:batch.data_->items) {
    auto imported=resource::make_accounted_unique<Data::Item>(input_detail::memory_owner,d.account,
        resource::MemoryPurpose::support_metadata,d.account,item.value,d.row_issue(item.value));
    auto* tail=imported.get();
    if(prepared->tail)prepared->tail->next=std::move(imported);
    else prepared->head=std::move(imported);
    prepared->tail=tail;
  }
  // Reconcile the preflight against actual retained requests before publication.
  // Every allocation since 'before' belongs to this native graph; no shadow
  // containers, global capacity ticket or replacement query account exists.
  if(d.account.current_usage().requested_bytes-before!=bytes)
    throw resource::MemoryFailure(resource::MemoryFault::contract);
  const auto count=batch.size();auto* tail=prepared.get();
  if(d.tail)d.tail->next=std::move(prepared);else d.head=std::move(prepared);
  d.tail=tail;++d.stats.batches;d.stats.events+=count;d.stats.accounted_bytes+=bytes;
  batch.data_.reset();return Admission::accepted;
}
// Private restoration publishes its imported head before peek preparation.
// A later peek failure can retain that head; failed session restore discards it.
std::uint64_t TypedQueue::stage_replay(const InputItemView& input,const SourceStateLimits& limits) {
  checkpoint_detail::require(bool(data_));auto& d=*data_;checkpoint_detail::require(!d.head && !d.cached && !d.stats.closed && !d.stats.failed);
  checkpoint_detail::require((d.mode==QueueMode::physical)==std::holds_alternative<InputEventView>(input));
  checkpoint_detail::Budget budget{limits};checkpoint_detail::replay_input(budget,input,d.input_limits,d.accepted.source_positions);
  catalog_source_detail::read(d.catalog,[&](const auto& schema){
    if(const auto* event=std::get_if<InputEventView>(&input))input_detail::validate(*event,schema,d.input_limits,input_detail::row_issue(schema,event->update.table,event->update.values));
    else {const auto& command=std::get<WindowCommandView>(input);const auto* item=std::get_if<WindowInsertView>(&command.command);input_detail::validate(command,schema,d.input_limits,item?input_detail::row_issue(schema,item->table,item->values):input_detail::RowIssue{});}
  });
  checkpoint_detail::require(d.limits.batches>0 && d.limits.events>0,recovery::ImageFault::limit);
  auto batch=resource::make_accounted_unique<Data::Batch>(input_detail::memory_owner,d.account,resource::MemoryPurpose::support_metadata);
  batch->head=resource::make_accounted_unique<Data::Item>(input_detail::memory_owner,d.account,resource::MemoryPurpose::support_metadata,d.account,input);batch->tail=batch->head.get();
  batch->bytes=add(Data::Item::request(resource::MemoryAccount::allocation_bytes(sizeof(Data::Batch),alignof(Data::Batch))),batch->head->bytes);
  checkpoint_detail::require(batch->bytes<=d.limits.bytes,recovery::ImageFault::limit);
  d.stats.batches=1;d.stats.events=1;d.stats.accounted_bytes=batch->bytes;d.tail=batch.get();d.head=std::move(batch);
  static_cast<void>(peek()); // Same continuity/record/source-position preparation as live input.
  return budget.used;
}
void TypedQueue::finish() noexcept {if(data_)data_->stats.closed=true;}
const InputItemView* TypedQueue::peek() {
  require(bool(data_),"invalid_input_reader","closed typed input queue");auto& d=*data_;
  require(!d.stats.failed,"input_failed","typed input failed at its current head");
  if(!d.head)return nullptr;
  const auto& owned=*d.head->head;const auto& item=owned.value;
  if(d.cached)return &item;
  try {
    require((d.mode==QueueMode::physical && std::holds_alternative<InputEventView>(item)) ||
        (d.mode==QueueMode::window && std::holds_alternative<WindowCommandView>(item)),
        "invalid_input_kind","transport item does not match the session source mode");
    catalog_source_detail::read(d.catalog,[&](const auto& schema) {
      if(const auto* event=std::get_if<InputEventView>(&item))input_detail::validate(*event,schema,d.input_limits,owned.issue);
      else input_detail::validate(std::get<WindowCommandView>(item),schema,d.input_limits,owned.issue);
    });
    require(d.accepted.sequence!=std::numeric_limits<std::uint64_t>::max() && sequence_of(item)==d.accepted.sequence+1,
        "invalid_sequence","typed input sequence must be contiguous");
    require(!d.input_limits.records || d.accepted.sequence<*d.input_limits.records,
        "resource_limit","typed input record limit exceeded");
    if(const auto& position=position_of(item)) {
      const auto found=d.accepted.source_positions.find(position->source);
      if(found!=d.accepted.source_positions.end()) {
        require(position->offset>found->second,"invalid_source_position","source offsets must increase strictly for each source");
      }else require(d.accepted.source_positions.size()<d.input_limits.sources,"resource_limit","retained source-position limit exceeded");
      d.prepared_position=d.accepted.source_positions.prepare(position->source,position->offset);
    }
    d.cached=true;return &item;
  // Semantic errors are sticky; native MemoryFailure/bad_alloc bypasses this
  // catch so the same owned head and accepted prefix remain retryable.
  }catch(const Error&){d.stats.failed=true;throw;}
}
// Publish prepared source acceptance, then retire exactly one counted head.
void TypedQueue::acknowledge() noexcept {
  if(!data_ || !data_->cached)return;
  auto& d=*data_;auto& batch=*d.head;const auto& item=*batch.head;
  if(position_of(item.value))d.accepted.source_positions.publish(d.prepared_position);
  d.accepted.sequence=sequence_of(item.value);
  d.stats.accounted_bytes-=item.bytes;batch.bytes-=item.bytes;--d.stats.events;
  auto retired=std::move(batch.head);batch.head=std::move(retired->next);retired.reset();
  d.cached=false;d.prepared_position=InputPositions::Prepared{};
  if(!batch.head) {
    d.stats.accounted_bytes-=batch.bytes;--d.stats.batches;
    auto old=std::move(d.head);d.head=std::move(old->next);
    if(!d.head)d.tail=nullptr;
  }
}
const AccountedInputProgress& TypedQueue::progress() const {
  require(bool(data_),"invalid_input_reader","closed typed input queue");return data_->accepted;
}
bool TypedQueue::failed() const noexcept {return data_ && data_->stats.failed;}
bool TypedQueue::closed() const noexcept {return !data_ || data_->stats.closed;}
bool TypedQueue::empty() const noexcept {return !data_ || !data_->head;}
QueueStats TypedQueue::stats() const noexcept {return data_?data_->stats:QueueStats{0,0,0,true,false};}
AccountedInputProgress TypedQueue::close() noexcept {
  static_assert(std::is_nothrow_move_constructible_v<AccountedInputProgress>);
  if(!data_)return {};
  auto result=std::move(data_->accepted);data_.reset();return result;
}
} // namespace crown::io
