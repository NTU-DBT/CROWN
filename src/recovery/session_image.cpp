#include "crown/recovery/session_image.hpp"
#include "crown/ir/digest.hpp"
#include "binary_detail.hpp"
#include "session_image_detail.hpp"
#include "session_pattern_wire.hpp"
#include "../runtime/checkpoint_policy.hpp"
#include "../io/checkpoint_detail.hpp"
#include <optional>

namespace crown::recovery {
namespace {
using namespace binary_detail;
using namespace runtime;
constexpr std::string_view magic="CROWNSI1";

bool utf8(std::string_view value) {
  for(std::size_t i=0;i<value.size();) {
    const auto a=static_cast<unsigned char>(value[i++]);if(a<0x80)continue;
    const unsigned count=a>=0xc2 && a<=0xdf?1:a>=0xe0 && a<=0xef?2:a>=0xf0 && a<=0xf4?3:0;
    if(!count || count>value.size()-i)return false;
    const auto b=static_cast<unsigned char>(value[i]);
    if((a==0xe0 && b<0xa0) || (a==0xed && b>0x9f) || (a==0xf0 && b<0x90) || (a==0xf4 && b>0x8f))return false;
    for(unsigned j=0;j<count;++j){const auto c=static_cast<unsigned char>(value[i++]);if(c<0x80 || c>0xbf)return false;}
  }
  return true;
}
void named(std::string_view value,bool empty,bool nul) {
  require((empty || !value.empty()) && (nul || value.find('\0')==std::string_view::npos) && utf8(value));
}
const io::AccountedInputProgress& progress(const SessionCheckpoint& value) {
  return std::visit([](const auto& source)->const io::AccountedInputProgress& {
    if constexpr(std::is_same_v<std::remove_cvref_t<decltype(source)>,io::AccountedInputProgress>)return source;
    else return source.progress;
  },value.source);
}
bool canonical_typed(const io::AccountedInputOptions::Values& value) {
  return value.format==io::InputFormat::jsonl && !value.table && value.delimiter==',' && value.header &&
      value.csv_operation==SetOperation::insert && value.relation_tokens.empty() && !value.null_token && !value.source &&
      value.byte_offset==0 && !value.limits.total_bytes;
}
struct Output:Writer {
  const SessionCheckpointLimits& state_limits;
  const SessionImageLimits& limits;
  std::uint64_t window_work=0;
  void window_charge(std::uint64_t amount) {
    require(window_work<=state_limits.window.work && amount<=state_limits.window.work-window_work,ImageFault::work);window_work+=amount;
  }
  template<class T> void enumeration(T value,T maximum) {
    require(static_cast<std::uint64_t>(value)<=static_cast<std::uint64_t>(maximum));integer(static_cast<std::uint64_t>(value),1);
  }
  void boolean(bool value){integer(value,1);}
  void optional(std::optional<std::uint64_t> value){boolean(value.has_value());if(value)integer(*value,8);}
  void text(std::string_view value,std::uint64_t cap,bool empty=true,bool nul=true) {
    require(value.size()<=cap && value.size()<=budget.limits.scalar_bytes,ImageFault::limit);
    budget.charge(value.size());named(value,empty,nul);integer(value.size(),8);put(value);
  }
  void hash(const std::array<char,64>& value){require(hex(value),ImageFault::binding);put({value.data(),value.size()});}
  void input_limits(const io::InputLimits& value) {
    for(const auto n:{value.record_bytes,value.field_bytes,value.columns,value.source_bytes,value.sources})integer(n,8);
    optional(value.total_bytes);optional(value.records);
  }
  void queue_limits(const io::QueueLimits& value){integer(value.batches,8);integer(value.events,8);integer(value.bytes,8);}
  void input(const io::AccountedInputOptions::Values& value) {
    enumeration(value.format,io::InputFormat::legacy_timestamp_flags);input_limits(value.limits);
    boolean(value.table.has_value());if(value.table)integer(value.table->value,8);
    integer(static_cast<unsigned char>(value.delimiter),1);boolean(value.header);enumeration(value.csv_operation,SetOperation::erase);
    require(value.relation_tokens.size()<=limits.relation_tokens,ImageFault::limit);integer(value.relation_tokens.size(),8);
    for(const auto& [name,table]:value.relation_tokens){text(name.view(),value.limits.field_bytes,false);integer(table.value,8);}
    boolean(value.null_token.has_value());if(value.null_token)text(value.null_token->view(),value.limits.field_bytes);
    boolean(value.source.has_value());if(value.source)text(value.source->view(),value.limits.source_bytes,false,false);
    integer(value.byte_offset,8);
  }
  void source_progress(const io::AccountedInputProgress& value,const io::InputLimits& cap) {
    require(value.source_positions.size()<=state_limits.source.positions && value.source_positions.size()<=cap.sources &&
        value.source_positions.size()<=value.sequence,ImageFault::limit);
    integer(value.sequence,8);integer(value.source_positions.size(),8);
    for(const auto& [name,offset]:value.source_positions){text(name.view(),cap.source_bytes,false,false);integer(offset,8);}
  }
  void row(storage::RowView value) {
    budget.row();window_charge(1);window_charge(value.size());require(value.size()<=budget.limits.fields,ImageFault::limit);integer(value.size(),8);
    for(const auto& cell:value.cells())scalar(cell);
  }
  void window(const WindowCheckpoint& value) {
    const auto& options=value.options;const auto& p=value.progress;
    require(state_limits.matching_work>0,ImageFault::work);window_charge(1);window_charge(options.managed_tables.size());
    require(!p.active_command_sequence && p.completed_steps==0 && p.total_steps==0);
    require(options.managed_tables.size()<=budget.limits.tables && options.managed_tables.capacity()<=limits.managed_capacity,ImageFault::limit);
    require(!options.managed_tables.empty() && options.managed_tables.capacity()>=options.managed_tables.size() && options.width>0 &&
        options.max_labels>0 && options.max_accounted_bytes>0 && options.command_work_limit>0 &&
        options.managed_tables.capacity()<=options.max_accounted_bytes/sizeof(TableId));
    require(value.last_command_work<=options.command_work_limit && value.counts.size()<=p.physical_sequence && value.labels.size()<=options.max_labels);
    if(p.completed_command_sequence==0)require(p.physical_sequence==0 && p.completed_watermark==0 && p.last_label==0 && value.counts.empty() && value.labels.empty());
    integer(options.managed_tables.size(),8);integer(options.managed_tables.capacity(),8);
    for(std::size_t i=0;i<options.managed_tables.size();++i) {
      const auto table=options.managed_tables[i];
      for(std::size_t j=0;j<i;++j){budget.charge(8);require(table!=options.managed_tables[j]);}
      integer(table.value,8);
    }
    integer(options.width,8);enumeration(options.fifo,WindowFifoPolicy::unrestricted);
    integer(options.max_labels,8);integer(options.max_accounted_bytes,8);integer(options.command_work_limit,8);
    integer(p.completed_command_sequence,8);integer(p.physical_sequence,8);integer(p.completed_watermark,8);integer(p.last_label,8);
    hash(value.catalog_sha256);integer(value.last_command_work,8);integer(value.work,8);boolean(value.stopped);
    require(value.counts.size()<=state_limits.window.counts && value.labels.size()<=state_limits.window.labels,ImageFault::limit);
    integer(value.counts.size(),8);std::uint64_t previous=0;
    for(const auto& count:value.counts) {
      require(count.id>previous && count.id<=p.last_label && count.count>0);previous=count.id;
      integer(count.id,8);integer(count.table.value,8);row(count.values.view());integer(count.count,8);
    }
    integer(value.labels.size(),8);previous=0;
    for(const auto& label:value.labels) {
      require(label.label>previous && label.label<=p.last_label && label.count_id>0 && label.count_id<=label.label &&
          label.timestamp<=UINT64_MAX-options.width && label.deadline==label.timestamp+options.width && label.deadline>p.completed_watermark);previous=label.label;
      integer(label.label,8);integer(label.table.value,8);row(label.values.view());
      integer(label.timestamp,8);integer(label.deadline,8);integer(label.count_id,8);
    }
  }
};
void write(Output& out,const SessionCheckpoint& value) {
  require(value.version==(value.update_patterns?SessionCheckpoint::current_version:SessionCheckpoint::legacy_version),ImageFault::version);
  require(value.update_patterns || (!value.pattern_violation && !value.pattern_origin_sequence && !value.pattern_origin_command_sequence));
  out.put(magic);out.integer(1,2);out.integer(0,2);out.integer(0,8);
  for(unsigned i=0;i<64;++i)out.integer(0,1);
  out.integer(value.version,4);out.enumeration(value.state,SessionState::stopped);out.enumeration(value.input_kind,SessionInputKind::typed_window);
  out.boolean(value.input_failed);out.boolean(value.end_of_input);out.integer(value.committed_sequence,8);
  const auto policy=runtime::detail::checkpoint_policy(value.delta,value.delta.mode);
  static_cast<void>(runtime::detail::checkpoint_options(policy,value.delta.physical.support.memory_limit_bytes));
  for(const auto word:policy)out.integer(word,8);
  out.integer(value.delta.physical.support.memory_limit_bytes,8);
  out.integer(value.snapshot.rows,8);out.integer(value.snapshot.bytes,8);out.optional(value.snapshot.cursor.work_limit);
  out.enumeration(value.workload.mode,workload::Mode::counters);out.integer(value.workload.max_cells,8);
  out.integer(value.workload.period,8);out.integer(value.workload.offset,8);out.integer(value.workload.detail_budget,8);
  const auto& input=value.input_options.get();out.input(input);
  io::checkpoint_detail::Budget source_budget{out.state_limits.source};source_budget.options(input);
  const bool stream=value.input_kind==SessionInputKind::owned_stream,stopped=value.state==SessionState::stopped;
  require(!value.input_failed || stopped);require(value.queue_limits.has_value()==!stream);
  require(value.window.has_value()==(value.input_kind==SessionInputKind::typed_window));
  const auto accepted=progress(value).sequence;require(!input.limits.records || accepted<=*input.limits.records);
  require(stream || canonical_typed(input));
  if(value.window)require(value.window->progress.completed_command_sequence==accepted && value.window->progress.physical_sequence==value.committed_sequence && value.window->stopped==stopped);
  else require(accepted==value.committed_sequence);
  if(value.state==SessionState::created)require(accepted==0 && value.committed_sequence==0 && !value.input_failed && !value.end_of_input);
  out.boolean(value.queue_limits.has_value());if(value.queue_limits)out.queue_limits(*value.queue_limits);
  const auto tag=value.source.index();require(tag==(stopped?2:stream?0:1));out.integer(tag,1);
  if(tag==1){io::checkpoint_detail::Budget positions{out.state_limits.source};positions.positions(progress(value),input.limits);}
  else source_budget.positions(progress(value),input.limits);
  out.source_progress(progress(value),input.limits);
  if(tag==0) {
    const auto& source=std::get<io::ReaderCheckpoint>(value.source);
    require(source.options.same_values(value.input_options) && source.records==source.progress.sequence && source.ended==value.end_of_input);
    require(!input.limits.total_bytes || source.bytes<=*input.limits.total_bytes);
    require(source.csv_fields.size()<=input.limits.columns,ImageFault::limit);
    if(input.format!=io::InputFormat::csv || !input.header)require(!source.header_read && source.csv_fields.empty());
    else require(source.header_read || (source.csv_fields.empty() && source.records==0));
    out.integer(source.bytes,8);out.integer(source.records,8);out.boolean(source.header_read);out.boolean(source.ended);
    require(source.csv_fields.size()<=out.state_limits.source.csv_fields,ImageFault::limit);out.integer(source.csv_fields.size(),8);
    source_budget.charge(source.csv_fields.size());
    for(std::size_t i=0;i<source.csv_fields.size();++i) {
      const auto field=source.csv_fields[i];require(field<source.csv_fields.size());out.integer(field,8);
      for(std::size_t j=0;j<i;++j){source_budget.charge(1);require(field!=source.csv_fields[j]);}
    }
    out.hash(source.catalog_sha256);out.integer(source.work,8);
  }else if(tag==1) {
    const auto& source=std::get<io::QueueCheckpoint>(value.source);
    require(source.limits==*value.queue_limits && source.input_limits==input.limits);
    require(source.mode==(value.window?io::QueueMode::window:io::QueueMode::physical));require(!value.end_of_input || source.closed);
    out.enumeration(source.mode,io::QueueMode::window);out.boolean(source.closed);out.hash(source.catalog_sha256);out.integer(source.work,8);
  }
  out.boolean(value.window.has_value());if(value.window)out.window(*value.window);
  if(value.version==SessionCheckpoint::current_version)detail::write_pattern_extension(out,value);
  const auto& bytes=value.runtime_image.bytes;require(bytes.size()<=out.state_limits.image.bytes,ImageFault::limit);
  out.integer(bytes.size(),8);out.put({bytes.data(),bytes.size()});
}

struct Input:Reader {
  const SessionCheckpointLimits& state_limits;
  const SessionImageLimits& limits;
  const resource::MemoryAccount& account;
  detail::DecodedSessionImage* result;
  std::uint64_t window_work=0;
  void source_charge(std::uint64_t& used,std::uint64_t amount) {
    require(used<=state_limits.source.work && amount<=state_limits.source.work-used,ImageFault::work);used+=amount;
  }
  void window_charge(std::uint64_t amount) {
    require(window_work<=state_limits.window.work && amount<=state_limits.window.work-window_work,ImageFault::work);window_work+=amount;
  }
  bool boolean(){const auto value=integer(1);require(value<=1);return value!=0;}
  std::optional<std::uint64_t> optional(){if(boolean())return integer(8);return std::nullopt;}
  template<class T> T enumeration(T maximum) {
    const auto value=integer(1);require(value<=static_cast<std::uint64_t>(maximum));return static_cast<T>(value);
  }
  std::string_view text(std::uint64_t cap,bool empty=true,bool nul=true) {
    const auto value=take(size(std::min(cap,budget.limits.scalar_bytes)));budget.charge(value.size());named(value,empty,nul);return value;
  }
  std::array<char,64> hash(){std::array<char,64> value{};const auto bytes=take(64);std::copy(bytes.begin(),bytes.end(),value.begin());require(hex(value),ImageFault::binding);return value;}
  io::InputLimits input_limits() {
    io::InputLimits value;value.record_bytes=size(SIZE_MAX);value.field_bytes=size(SIZE_MAX);value.columns=size(SIZE_MAX);
    value.source_bytes=size(SIZE_MAX);value.sources=size(SIZE_MAX);value.total_bytes=optional();value.records=optional();return value;
  }
  io::QueueLimits queue_limits(){return {size(SIZE_MAX),size(SIZE_MAX),size(SIZE_MAX)};}
  struct InputPolicy {io::InputLimits limits;io::InputFormat format;bool header;std::uint64_t work;bool canonical_typed;};
  InputPolicy input_options() {
    std::uint64_t work=0;source_charge(work,1);
    std::optional<io::AccountedInputOptions::Values> native;if(result)native.emplace(account);
    const auto format=enumeration(io::InputFormat::legacy_timestamp_flags);const auto cap=input_limits();
    const auto table=boolean()?std::optional<TableId>{TableId{size(SIZE_MAX)}}:std::nullopt;
    const auto delimiter=static_cast<char>(integer(1));const auto header=boolean();const auto operation=enumeration(SetOperation::erase);
    if(native){native->format=format;native->limits=cap;native->table=table;native->delimiter=delimiter;native->header=header;native->csv_operation=operation;}
    const auto count=size(limits.relation_tokens);source_charge(work,count);std::string_view previous;
    for(std::size_t i=0;i<count;++i) {
      const auto name=text(cap.field_bytes,false);source_charge(work,name.size());budget.charge(previous.size());budget.charge(name.size());require(i==0 || previous<name);previous=name;
      const TableId id{size(SIZE_MAX)};
      if(native)native->relation_tokens.emplace(resource::AccountedText::copy_of(account,name,io::input_detail::memory_owner),id);
    }
    const bool null_present=boolean();
    if(null_present){const auto value=text(cap.field_bytes);source_charge(work,value.size());if(native)native->null_token=resource::AccountedText::copy_of(account,value,io::input_detail::memory_owner);}
    const bool source_present=boolean();
    if(source_present){const auto value=text(cap.source_bytes,false,false);source_charge(work,value.size());if(native)native->source=resource::AccountedText::copy_of(account,value,io::input_detail::memory_owner);}
    const auto offset=integer(8);if(native){native->byte_offset=offset;result->state.input_options=detail::SessionImageAccess::input(account,std::move(*native));}
        const bool canonical=format==io::InputFormat::jsonl && !table && delimiter==',' && header && operation==SetOperation::insert &&
        count==0 && !null_present && !source_present && offset==0 && !cap.total_bytes;
    return {cap,format,header,work,canonical};
  }
  std::uint64_t source_progress(const io::InputLimits& cap,io::AccountedInputProgress* output,std::uint64_t& work) {
    source_charge(work,1);
    const auto sequence=integer(8);const auto count=size(std::min<std::uint64_t>({state_limits.source.positions,cap.sources,sequence}));
    if(output){*output=io::AccountedInputProgress(account);output->sequence=sequence;}
    std::string_view previous;
    for(std::size_t i=0;i<count;++i) {
      const auto name=text(cap.source_bytes,false,false);source_charge(work,1);source_charge(work,name.size());budget.charge(previous.size());budget.charge(name.size());require(i==0 || previous<name);previous=name;
      const auto offset=integer(8);if(output){auto prepared=output->source_positions.prepare(name,offset);output->source_positions.publish(prepared);}
    }
    return sequence;
  }
  storage::AccountedRow row() {
    budget.row();const auto count=size(budget.limits.fields);window_charge(1);window_charge(count);require(count<=input.size()-position);
    ImageVector<storage::ScalarView> cells;if(result){cells=ImageVector<storage::ScalarView>(image_allocator<storage::ScalarView>(account));cells.reserve(count);}
    for(std::size_t i=0;i<count;++i){const auto value=binary_detail::scalar(*this);if(result)cells.push_back(value);}
    return result?storage::AccountedRow::copy_of(account,storage::RowView::borrow(cells),image_owner):storage::AccountedRow{};
  }
  std::uint64_t at(std::size_t start) {
    budget.charge(8);require(start<=input.size() && input.size()-start>=8);std::uint64_t value=0;
    for(unsigned i=0;i<8;++i)value|=std::uint64_t(static_cast<unsigned char>(input[start+i]))<<(8*i);
    return value;
  }
  void window(SessionImageManifest& manifest) {
    require(state_limits.matching_work>0,ImageFault::work);
    const auto count=size(budget.limits.tables),capacity=size(limits.managed_capacity);require(count>0 && capacity>=count);
    window_charge(1);window_charge(count);
    const auto start=position;ImageVector<TableId> tables;if(result){tables=ImageVector<TableId>(image_allocator<TableId>(account));tables.reserve(count);}
    for(std::size_t i=0;i<count;++i) {
      const TableId table{size(SIZE_MAX)};
      for(std::size_t j=0;j<i;++j)require(table.value!=at(start+j*8));
      if(result)tables.push_back(table);
    }
    const auto width=integer(8);const auto fifo=enumeration(WindowFifoPolicy::unrestricted);
    const auto labels=size(SIZE_MAX),bytes=size(SIZE_MAX);const auto work=integer(8);
    require(width>0 && labels>0 && bytes>0 && work>0 && capacity<=bytes/sizeof(TableId));
    WindowProgress p;p.completed_command_sequence=integer(8);p.physical_sequence=integer(8);p.completed_watermark=integer(8);p.last_label=integer(8);
    require(p.completed_command_sequence==manifest.accepted_sequence && p.physical_sequence==manifest.committed_sequence);
    const auto catalog=hash();const auto last_work=integer(8),capture_work=integer(8);const auto stopped=boolean();
    require(last_work<=work && stopped==(manifest.state==SessionState::stopped));
    if(result) {
      auto options=detail::SessionImageAccess::window(WindowTables::copy_of(account,{tables.data(),tables.size()},capacity),width,fifo,labels,bytes,work);
      result->state.window.emplace(account,std::move(options));auto& value=*result->state.window;
      value.progress=p;value.catalog_sha256=catalog;value.last_command_work=last_work;value.work=capture_work;value.stopped=stopped;
    }
    const auto counts=size(state_limits.window.counts);require(counts<=p.physical_sequence);std::uint64_t previous=0;
    if(result)result->state.window->counts.reserve(counts);
    for(std::size_t i=0;i<counts;++i) {
      const auto id=integer(8);const TableId table{size(SIZE_MAX)};require(id>previous && id<=p.last_label);previous=id;
      auto values=row();const auto refs=integer(8);require(refs>0);
      if(result)result->state.window->counts.push_back({id,table,std::move(values),refs});
    }
    const auto entries=size(std::min<std::uint64_t>(state_limits.window.labels,labels));previous=0;
    if(result)result->state.window->labels.reserve(entries);
    for(std::size_t i=0;i<entries;++i) {
      const auto id=integer(8);const TableId table{size(SIZE_MAX)};require(id>previous && id<=p.last_label);previous=id;
      auto values=row();const auto timestamp=integer(8),deadline=integer(8),count_id=integer(8);
      require(timestamp<=UINT64_MAX-width && deadline==timestamp+width && deadline>p.completed_watermark && count_id>0 && count_id<=id);
      if(result)result->state.window->labels.push_back({id,table,std::move(values),timestamp,deadline,count_id});
    }
    if(p.completed_command_sequence==0)require(p.physical_sequence==0 && p.completed_watermark==0 && p.last_label==0 && counts==0 && entries==0);
  }
};
InspectedSessionImage read(Input& in) {
  InspectedSessionImage info;auto& m=info.manifest;
  m.state_version=static_cast<std::uint32_t>(in.integer(4));
  require(m.state_version==SessionCheckpoint::legacy_version || m.state_version==SessionCheckpoint::current_version,ImageFault::version);
  m.state=in.enumeration(SessionState::stopped);m.input_kind=in.enumeration(SessionInputKind::typed_window);
  m.input_failed=in.boolean();m.end_of_input=in.boolean();m.committed_sequence=in.integer(8);
  std::array<std::uint64_t,26> policy{};for(auto& word:policy)word=in.integer(8);
  info.delta=runtime::detail::checkpoint_options(policy,in.integer(8));
  SnapshotLimits snapshot;snapshot.rows=in.size(SIZE_MAX);snapshot.bytes=in.size(SIZE_MAX);snapshot.cursor.work_limit=in.optional();
  workload::Options workload;workload.mode=in.enumeration(workload::Mode::counters);workload.max_cells=in.size(SIZE_MAX);
  workload.period=in.integer(8);workload.offset=in.integer(8);workload.detail_budget=in.integer(8);
  const auto input=in.input_options();const bool stream=m.input_kind==SessionInputKind::owned_stream,stopped=m.state==SessionState::stopped;
  require(!m.input_failed || stopped);require(stream || input.canonical_typed);const bool queued=in.boolean();require(queued==!stream);
  const auto queue=queued?std::optional<io::QueueLimits>{in.queue_limits()}:std::nullopt;
  const auto tag=in.integer(1);require(tag==(stopped?2:stream?0:1));
  io::AccountedInputProgress* output=nullptr;
  if(in.result) {
    auto& state=in.result->state;state.version=m.state_version;state.state=m.state;state.input_kind=m.input_kind;
    state.input_failed=m.input_failed;state.end_of_input=m.end_of_input;state.committed_sequence=m.committed_sequence;
    state.delta=info.delta;state.snapshot=snapshot;state.workload=workload;state.queue_limits=queue;
    if(tag==0){state.source=io::ReaderCheckpoint{};auto& source=std::get<io::ReaderCheckpoint>(state.source);source.options=state.input_options;output=&source.progress;}
    else if(tag==1){state.source=io::QueueCheckpoint{};auto& source=std::get<io::QueueCheckpoint>(state.source);source.limits=*queue;source.input_limits=input.limits;output=&source.progress;}
    else {state.source=io::AccountedInputProgress{};output=&std::get<io::AccountedInputProgress>(state.source);}
  }
  std::uint64_t source_work=0;m.accepted_sequence=in.source_progress(input.limits,output,source_work);
  if(tag!=1)in.source_charge(source_work,input.work);
  require(!input.limits.records || m.accepted_sequence<=*input.limits.records);
  if(tag==0) {
    const auto bytes=in.integer(8),records=in.integer(8);const auto header=in.boolean(),ended=in.boolean();
    require(records==m.accepted_sequence && ended==m.end_of_input && (!input.limits.total_bytes || bytes<=*input.limits.total_bytes));
    const auto count=in.size(std::min<std::uint64_t>(in.state_limits.source.csv_fields,input.limits.columns));in.source_charge(source_work,count);const auto start=in.position;
    if(input.format!=io::InputFormat::csv || !input.header)require(!header && count==0);
    else {require(header || (count==0 && records==0));}
    if(in.result) {
      auto& source=std::get<io::ReaderCheckpoint>(in.result->state.source);source.bytes=bytes;source.records=records;source.header_read=header;source.ended=ended;
      source.csv_fields=ImageVector<std::size_t>(image_allocator<std::size_t>(in.account));source.csv_fields.reserve(count);
    }
    for(std::size_t i=0;i<count;++i) {
      const auto field=in.size(count?count-1:0);for(std::size_t j=0;j<i;++j){in.source_charge(source_work,1);require(field!=in.at(start+j*8));}
      if(in.result)std::get<io::ReaderCheckpoint>(in.result->state.source).csv_fields.push_back(field);
    }
    const auto hash=in.hash();const auto work=in.integer(8);
    if(in.result){auto& source=std::get<io::ReaderCheckpoint>(in.result->state.source);source.catalog_sha256=hash;source.work=work;}
  }else if(tag==1) {
    const auto mode=in.enumeration(io::QueueMode::window);const bool closed=in.boolean();
    require(mode==(m.input_kind==SessionInputKind::typed_window?io::QueueMode::window:io::QueueMode::physical) && (!m.end_of_input || closed));
    const auto hash=in.hash();const auto work=in.integer(8);
    if(in.result){auto& source=std::get<io::QueueCheckpoint>(in.result->state.source);source.mode=mode;source.closed=closed;source.catalog_sha256=hash;source.work=work;}
  }
  const bool window=in.boolean();require(window==(m.input_kind==SessionInputKind::typed_window));
  if(window)in.window(m);else require(m.accepted_sequence==m.committed_sequence);
  if(m.state==SessionState::created)require(m.accepted_sequence==0 && m.committed_sequence==0 && !m.end_of_input && !m.input_failed);
  if(m.state_version==SessionCheckpoint::current_version)detail::read_pattern_extension(in,m);
  const auto blob=in.take(in.size(in.state_limits.image.bytes));require(in.position==in.input.size());
  if(in.result)in.result->runtime_bytes=blob;
  else {
    const auto inner=inspect_image(blob,in.state_limits.image);in.budget.charge(inner.statistics.work);m.runtime_manifest=inner.manifest;
    require(inner.manifest.epoch==m.committed_sequence && inner.manifest.binding.policy==policy,ImageFault::binding);
  }
  return info;
}
} // namespace

SessionImage encode_session_image(const resource::MemoryAccount& account,const SessionCheckpoint& state,
    const SessionCheckpointLimits& native,SessionImageLimits limits) {
  // Size/validate both write passes before final account allocation. This
  // codec checks structure; the restoring session still admits native semantics.
  const auto& encoded=state.runtime_image.bytes;
  const auto inner=inspect_image({encoded.data(),encoded.size()},native.image);
  require(inner.manifest.epoch==state.committed_sequence && inner.manifest.binding.policy==runtime::detail::checkpoint_policy(state.delta,state.delta.mode),ImageFault::binding);
  Budget budget{limits.envelope};budget.charge(inner.statistics.work);const auto before=budget.used;
  Output preflight{{budget,nullptr},native,limits};write(preflight,state);
  const auto size=preflight.size;require(size<=SIZE_MAX,ImageFault::limit);budget.charge(budget.used-before);budget.charge(size-session_image_header_size);
  SessionImage image{ImageVector<char>(image_allocator<char>(account)),{size,budget.used,budget.rows},{}};image.bytes.reserve(static_cast<std::size_t>(size));
  Budget materialization{limits.envelope};Output writer{{materialization,&image.bytes},native,limits};write(writer,state);require(writer.size==size);
  for(unsigned i=0;i<8;++i)image.bytes[12+i]=static_cast<char>((size-session_image_header_size)>>(8*i));
  const auto checksum=sha256_fixed({image.bytes.data()+session_image_header_size,image.bytes.size()-session_image_header_size});
  std::copy(checksum.begin(),checksum.end(),image.bytes.begin()+20);
  // This manifest describes the validated wire structure. Program/source/window
  // semantic matching still belongs to the restoring session, including for
  // callers that construct SessionCheckpoint directly.
  image.manifest={inner.manifest,state.version,state.state,state.input_kind,state.input_failed,state.end_of_input,
      state.committed_sequence,progress(state).sequence};return image;
}
detail::ValidatedSessionImage detail::validate_session_image(std::string_view bytes,const SessionCheckpointLimits& native,SessionImageLimits limits) {
  // Validation builds no decoded heap graph. Keep these exact input bytes
  // alive and immutable through materialization and subsequent native restore.
  require(bytes.size()<=limits.envelope.bytes,ImageFault::limit);Budget budget{limits.envelope};Reader header{bytes,budget};
  require(header.take(8)==magic);require(header.integer(2)==1 && header.integer(2)==0,ImageFault::version);
  const auto size=header.integer(8);const auto checksum=header.take(64);require(size==bytes.size()-session_image_header_size && hex({checksum.data(),checksum.size()}));
  budget.charge(size);const auto actual=sha256_fixed(bytes.substr(session_image_header_size));require(std::equal(actual.begin(),actual.end(),checksum.begin()));
  const auto before=budget.used;const resource::MemoryAccount none;
  Input reader{{bytes.substr(session_image_header_size),budget},native,limits,none,nullptr};auto info=read(reader);
  budget.charge(budget.used-before);info.statistics={static_cast<std::uint64_t>(bytes.size()),budget.used,budget.rows};
  return {bytes,info,native,limits};
}
InspectedSessionImage inspect_session_image(std::string_view bytes,const SessionCheckpointLimits& native,SessionImageLimits limits) {
  return detail::validate_session_image(bytes,native,limits).inspected;
}
detail::DecodedSessionImage detail::materialize_session_image(const resource::MemoryAccount& account,const ValidatedSessionImage& validated) {
  // Adopt only a prior validation of unchanged bytes/limits. Native metadata
  // owns receiver storage; the runtime blob remains borrowed until restore.
  Budget budget{validated.limits.envelope};DecodedSessionImage result;
  Input reader{{validated.bytes.substr(session_image_header_size),budget},validated.state_limits,validated.limits,account,&result};
  static_cast<void>(read(reader));result.state.runtime_image.manifest=validated.inspected.manifest.runtime_manifest;return result;
}
} // namespace crown::recovery
