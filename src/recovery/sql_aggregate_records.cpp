#include "crown/recovery/sql_aggregate_records.hpp"
#include "crown/ir/digest.hpp"
#include "binary_detail.hpp"
#include "../frontend/sql_rows_value.hpp"
#include <algorithm>

namespace crown::recovery::sql_aggregate {
namespace detail {
// Only validated codec factories construct immutable owned frames/borrow sets.
struct FrameAccess {
  static Frame frame(ImageVector<char> bytes,Inspected info) {
    return Frame(std::move(bytes),std::move(info));
  }
  static DecodedInput input(Frame frame,ImageVector<runtime::sql_rows::Cell> cells,
      ImageVector<runtime::sql_rows::SourceReplacement> replacements) {
    return DecodedInput(std::move(frame),std::move(cells),std::move(replacements));
  }
  static void work(Frame& frame,std::uint64_t value) noexcept { frame.info_.statistics.work=value; }
};
} // namespace detail
namespace {
using namespace binary_detail;
using Cell = runtime::sql_rows::Cell;
using Program = frontend::SqlAggregateProgram;
constexpr std::string_view magic = "CROWNAG2";

// Fixed-size metadata validators do not allocate or infer native provenance.
void valid(const Binding& value) {
  require(hex(value.query_id) && hex(value.descriptor_sha256),ImageFault::binding);
}
void valid(const WalHeader& value) {
  valid(value.binding);
  require(value.generation>0 && hex(value.checkpoint_sha256) &&
      value.physical_sequence<=value.command_sequence,ImageFault::binding);
}
void valid(const SinkHeader& value) { valid(value.binding);require(hex(value.sink_id),ImageFault::binding); }
void valid(const Commit& value) {
  require(value.input_ordinal>0 && value.physical_sequence>0 &&
      value.physical_sequence<=value.command_sequence && value.output_bytes>=frame_header_size+107);
  require(hex(value.input_sha256) && hex(value.output_sha256),ImageFault::binding);
}
void valid(const Reject& value) {
  require(value.input_ordinal>0 && value.physical_sequence<value.command_sequence &&
      static_cast<unsigned>(value.reason)<=static_cast<unsigned>(RejectReason::annotation_overflow));
  require(hex(value.input_sha256),ImageFault::binding);
}
void valid(const GroupInfo& value) {
  require(value.generation>0 && value.physical_sequence>0 && value.physical_sequence<=value.input_sequence);
  require(!value.group_changed || value.changed);
  require(value.groups==0 || (value.changed && value.group_changed));
  require(hex(value.input_sha256),ImageFault::binding);
}
void program_valid(const Program& program,const Limits& limits) {
  require(bool(program),ImageFault::binding);
  require(program.source_program().sources().size()<=limits.record.tables,ImageFault::limit);
}
// The genuine source/kernel supply SqlTypes without allocating a schema copy.
auto source_columns(const Program& program,std::uint64_t table) {
  const auto sources=program.source_program().sources();
  require(table<sources.size() && sources[static_cast<std::size_t>(table)].table.value==table,ImageFault::binding);
  return sources[static_cast<std::size_t>(table)].columns;
}
std::size_t fields(const Program& program,bool key) {
  const auto& kernel=program.kernel_program();
  return key?kernel.group_columns().size():kernel.outputs().size();
}
frontend::SqlType field_type(const Program& program,bool key,std::size_t i) {
  const auto& kernel=program.kernel_program();
  return key?kernel.input_types()[kernel.group_columns()[i].value]:kernel.outputs()[i].type;
}
void cell_valid(Budget& budget,const Cell& cell,const frontend::SqlType& type) {
  if(cell && std::holds_alternative<std::string_view>(*cell))
    budget.charge(std::get<std::string_view>(*cell).size()); // UTF8 pass in fits.
  require(frontend::rows_detail::fits(cell,type),ImageFault::scalar);
}
bool ordered(Budget& budget,std::string_view a,std::string_view b) {
  budget.charge(std::min(a.size(),b.size()));return a<b;
}
struct KeySlice { std::size_t index,begin,size; };

// Count-only and materializing passes share validation and byte/work admissions.
// Every row gets one presence byte per cell; absent tuples use a separate byte.
struct Output : Writer {
  const Program& program;
  const Limits& limits;
  std::span<const KeySlice> order;
  InputInfo input_info{};
  void hash(std::span<const char> value) {
    require(hex(value),ImageFault::binding);put({value.data(),value.size()});
  }
  template<class TypeAt> void row(std::span<const Cell> cells,std::size_t expected,TypeAt type_at) {
    budget.row();require(cells.size()==expected,ImageFault::binding);
    require(expected<=limits.record.fields,ImageFault::limit);integer(expected,8);
    for(std::size_t i=0;i<expected;++i) {
      cell_valid(budget,cells[i],type_at(i));integer(cells[i].has_value(),1);
      if(cells[i])scalar(*cells[i]);
    }
  }
  void group_row(const runtime::aggregate::Tuple& tuple,bool key) {
    require(bool(tuple));row(tuple.view(),fields(program,key),[&](std::size_t i){return field_type(program,key,i);});
  }
  void write(const WalHeader& value) {
    valid(value);hash(value.binding.query_id);hash(value.binding.descriptor_sha256);integer(value.generation,8);
    hash(value.checkpoint_sha256);integer(value.physical_sequence,8);integer(value.command_sequence,8);
  }
  void write(const SinkHeader& value) {
    valid(value);hash(value.binding.query_id);hash(value.binding.descriptor_sha256);hash(value.sink_id);integer(value.base_sequence,8);
  }
  void write(const InputView& value) {
    require(value.command_sequence>0);integer(value.command_sequence,8);
    require(value.replacements.size()<=limits.record.rows,ImageFault::limit);integer(value.replacements.size(),8);
    input_info.command_sequence=value.command_sequence;input_info.replacements=value.replacements.size();
    for(const auto& edit:value.replacements) {
      const auto columns=source_columns(program,edit.source.value);integer(edit.source.value,8);
      row(edit.values,columns.size(),[&](std::size_t i){return columns[i].type;});
      require(columns.size()<=UINT64_MAX-input_info.cells,ImageFault::limit);input_info.cells+=columns.size();
      integer(edit.before,8);integer(edit.after,8); // Arithmetic/constraints belong to native prepare.
    }
    integer(value.source.has_value(),1);
    if(value.source) {
      const auto name=value.source->source;require(name.size()<=limits.source_bytes,ImageFault::limit);
      budget.charge(name.size());require(!name.empty() && frontend::rows_detail::text_fits(name));
      integer(name.size(),8);input_info.source_present=true;input_info.source_begin=static_cast<std::size_t>(size);
      input_info.source_size=name.size();input_info.source_offset=value.source->offset;
      put(name);integer(value.source->offset,8);
    }
    integer(value.reader.has_value(),1);
    if(value.reader) {
      require(value.reader->bytes>0 && value.reader->records>0);
      integer(value.reader->bytes,8);integer(value.reader->records,8);
      input_info.reader=value.reader;
    }
  }
  void write(const Commit& value) {
    valid(value);integer(value.input_ordinal,8);hash(value.input_sha256);
    integer(value.command_sequence,8);integer(value.physical_sequence,8);
    integer(value.output_bytes,8);hash(value.output_sha256);
  }
  void write(const Reject& value) {
    valid(value);integer(value.input_ordinal,8);hash(value.input_sha256);
    integer(value.command_sequence,8);integer(value.physical_sequence,8);integer(static_cast<unsigned>(value.reason),1);
  }
  void write(const GroupEpochView& value) {
    valid(GroupInfo{value.generation,value.input_sequence,value.physical_sequence,value.groups.size(),
        value.input_sha256,value.changed,value.group_changed});
    require(order.size()==value.groups.size());integer(value.generation,8);integer(value.input_sequence,8);
    integer(value.physical_sequence,8);hash(value.input_sha256);integer(value.changed,1);integer(value.group_changed,1);
    integer(value.groups.size(),8);
    for(const auto& item:order) {
      const auto& group=value.groups[item.index];require(group.before || group.after);
      group_row(group.key,true);integer(group.before.has_value(),1);
      if(group.before)group_row(*group.before,false);
      integer(group.after.has_value(),1);if(group.after)group_row(*group.after,false);
      if(group.before && group.after) {
        const auto a=group.before->view(),b=group.after->view();budget.charge(a.size());
        for(std::size_t i=0;i<a.size();++i)
          if(a[i] && b[i] && std::holds_alternative<std::string_view>(*a[i]) && std::holds_alternative<std::string_view>(*b[i]))
            budget.charge(std::min(std::get<std::string_view>(*a[i]).size(),std::get<std::string_view>(*b[i]).size()));
        require(*group.before!=*group.after);
      }
    }
  }
  Inspected frame(std::uint64_t ordinal,const PayloadView& payload) {
    const auto kind=static_cast<Kind>(payload.index());
    require((kind==Kind::wal_header || kind==Kind::sink_header)==(ordinal==0));
    if(const auto* value=std::get_if<Commit>(&payload))require(value->input_ordinal<ordinal);
    if(const auto* value=std::get_if<Reject>(&payload))require(value->input_ordinal<ordinal);
    put(magic);integer(1,2);integer(0,2);integer(0,8);
    std::array<char,64> blank{};blank.fill('0');put({blank.data(),blank.size()});put({blank.data(),blank.size()});
    integer(payload.index(),1);integer(ordinal,8);Inspected result{};result.kind=kind;result.ordinal=ordinal;
    std::visit([&](const auto& value) {
      write(value);using T=std::remove_cvref_t<decltype(value)>;
      if constexpr(std::is_same_v<T,InputView>)result.payload=input_info;
      else if constexpr(std::is_same_v<T,GroupEpochView>)result.payload=GroupInfo{value.generation,value.input_sequence,
          value.physical_sequence,value.groups.size(),value.input_sha256,value.changed,value.group_changed};
      else result.payload=value;
    },payload);
    return result;
  }
};

// Parser borrows bytes. Null output pointers keep inspection allocation-free;
// decode reserves both flat arrays before this same typed parsing pass.
struct Input : Reader {
  const Program& program;
  const Limits& limits;
  ImageVector<Cell>* cells = nullptr;
  ImageVector<runtime::sql_rows::SourceReplacement>* replacements = nullptr;
  bool boolean() { const auto value=integer(1);require(value<=1);return value!=0; }
  template<std::size_t N> std::array<char,N> hash() {
    std::array<char,N> result{};const auto text=take(N);
    std::copy(text.begin(),text.end(),result.begin());require(hex(result),ImageFault::binding);return result;
  }
  Binding binding() { return {hash<32>(),hash<64>()}; }
  template<class TypeAt> std::string_view row(std::size_t expected,TypeAt type_at) {
    budget.row();const auto start=position;const auto count=size(limits.record.fields);
    require(count==expected,ImageFault::binding);
    for(std::size_t i=0;i<count;++i) {
      Cell value;if(boolean())value=binary_detail::scalar(*this);
      cell_valid(budget,value,type_at(i));if(cells)cells->push_back(value);
    }
    return input.substr(start,position-start);
  }
  std::string_view group_row(bool key) {
    return row(fields(program,key),[&](std::size_t i){return field_type(program,key,i);});
  }
  InputInfo item() {
    InputInfo value;value.command_sequence=integer(8);require(value.command_sequence>0);
    value.replacements=size(limits.record.rows);
    // Even zero-column replacements need table/field-count/before/after words.
    require(value.replacements<=(input.size()-position)/32);
    for(std::uint64_t i=0;i<value.replacements;++i) {
      const auto table=integer(8);const auto columns=source_columns(program,table);
      const auto begin=cells?cells->size():0;
      row(columns.size(),[&](std::size_t j){return columns[j].type;});
      require(columns.size()<=UINT64_MAX-value.cells,ImageFault::limit);value.cells+=columns.size();
      const auto before=integer(8),after=integer(8);
      if(replacements)replacements->push_back({TableId{static_cast<std::size_t>(table)},
          std::span<const Cell>(*cells).subspan(begin,columns.size()),before,after});
    }
    value.source_present=boolean();
    if(value.source_present) {
      value.source_size=size(limits.source_bytes);value.source_begin=position;const auto name=take(value.source_size);
      budget.charge(name.size());require(!name.empty() && frontend::rows_detail::text_fits(name));value.source_offset=integer(8);
    }
    if(boolean()) {
      value.reader=ReaderPosition{integer(8),integer(8)};require(value.reader->bytes>0 && value.reader->records>0);
    }
    return value;
  }
  GroupInfo groups() {
    GroupInfo value;value.generation=integer(8);value.input_sequence=integer(8);value.physical_sequence=integer(8);
    value.input_sha256=hash<64>();value.changed=boolean();value.group_changed=boolean();value.groups=size(limits.record.rows);
    valid(value);std::string_view previous;
    for(std::uint64_t i=0;i<value.groups;++i) {
      const auto key=group_row(true);if(i>0)require(ordered(budget,previous,key));previous=key;
      const bool before=boolean();std::string_view a;if(before)a=group_row(false);
      const bool after=boolean();std::string_view b;if(after)b=group_row(false);
      require(before || after);
      if(before && after){budget.charge(std::min(a.size(),b.size()));require(a!=b);}
    }
    return value;
  }
  Inspected body() {
    const auto tag=integer(1);require(tag<=static_cast<unsigned>(Kind::group_epoch));
    Inspected value{};value.kind=static_cast<Kind>(tag);value.ordinal=integer(8);
    require((value.kind==Kind::wal_header || value.kind==Kind::sink_header)==(value.ordinal==0));
    switch(value.kind) {
      case Kind::wal_header:{
        WalHeader v{binding(),integer(8),hash<64>(),integer(8),integer(8)};valid(v);value.payload=v;break;
      }
      case Kind::sink_header:{SinkHeader v{binding(),hash<32>(),integer(8)};valid(v);value.payload=v;break;}
      case Kind::input:value.payload=item();break;
      case Kind::commit:{
        Commit v{integer(8),hash<64>(),integer(8),integer(8),integer(8),hash<64>()};
        valid(v);require(v.input_ordinal<value.ordinal);value.payload=v;break;
      }
      case Kind::reject:{
        Reject v;v.input_ordinal=integer(8);v.input_sha256=hash<64>();v.command_sequence=integer(8);v.physical_sequence=integer(8);
        const auto reason=integer(1);require(reason<=static_cast<unsigned>(RejectReason::annotation_overflow));
        v.reason=static_cast<RejectReason>(reason);valid(v);require(v.input_ordinal<value.ordinal);value.payload=v;break;
      }
      case Kind::group_epoch:value.payload=groups();break;
    }
    require(position==input.size());return value;
  }
};

// Protect the length before using it. Exact frames reject trailing bytes;
// complete corruption is distinct from a file owner's future torn-tail policy.
Inspected inspect_frame(const Program& program,std::string_view bytes,const Limits& limits,Budget& budget) {
  program_valid(program,limits);require(bytes.size()<=limits.record.bytes,ImageFault::limit);
  Reader header{bytes,budget};require(header.take(8)==magic,ImageFault::version);
  require(header.integer(2)==1 && header.integer(2)==0,ImageFault::version);
  const auto size=header.integer(8);const auto body_hash=header.take(64),prefix_hash=header.take(64);
  budget.charge(frame_prefix_size);const auto actual_prefix=sha256_fixed(bytes.substr(0,frame_prefix_size));
  require(prefix_hash==std::string_view(actual_prefix.data(),actual_prefix.size()));
  require(size==bytes.size()-frame_header_size);budget.charge(size);
  const auto body=bytes.substr(frame_header_size);const auto actual_body=sha256_fixed(body);
  require(body_hash==std::string_view(actual_body.data(),actual_body.size()));
  Input input{{bytes,budget,frame_header_size},program,limits};auto info=input.body();info.body_sha256=actual_body;
  info.statistics={bytes.size(),budget.used,budget.rows};return info;
}

// One compact key buffer plus one index vector; no per-group owning allocation.
// Sorting compares full nullable typed wire keys, independent of producer order.
ImageVector<KeySlice> key_order(const resource::MemoryAccount& account,const Program& program,
    const PayloadView& payload,const Limits& limits,Budget& budget) {
  ImageVector<KeySlice> order(image_allocator<KeySlice>(account));
  const auto* epoch=std::get_if<GroupEpochView>(&payload);if(!epoch)return order;
  require(epoch->groups.size()<=limits.record.rows,ImageFault::limit);
  Output measure{{budget,nullptr},program,limits,{}};
  for(const auto& group:epoch->groups)measure.group_row(group.key,true);
  require(measure.size<=SIZE_MAX,ImageFault::limit);
  ImageVector<char> keys(image_allocator<char>(account));keys.reserve(static_cast<std::size_t>(measure.size));
  order.reserve(epoch->groups.size());budget.rows=0;Output writer{{budget,&keys},program,limits,{}};
  for(std::size_t i=0;i<epoch->groups.size();++i) {
    const auto start=keys.size();writer.group_row(epoch->groups[i].key,true);order.push_back({i,start,keys.size()-start});
  }
  const auto key=[&](const KeySlice& entry){return std::string_view(keys.data()+entry.begin,entry.size);};
  std::sort(order.begin(),order.end(),[&](const KeySlice& a,const KeySlice& b){return ordered(budget,key(a),key(b));});
  for(std::size_t i=1;i<order.size();++i)require(ordered(budget,key(order[i-1]),key(order[i])));
  return order;
}
} // namespace

Frame encode(const resource::MemoryAccount& account,const Program& program,std::uint64_t ordinal,
    const PayloadView& payload,Limits limits) {
  program_valid(program,limits);Budget budget{limits.record};const auto order=key_order(account,program,payload,limits,budget);
  budget.rows=0;Output measure{{budget,nullptr},program,limits,order};static_cast<void>(measure.frame(ordinal,payload));
  require(measure.size<=SIZE_MAX,ImageFault::limit);ImageVector<char> bytes(image_allocator<char>(account));
  bytes.reserve(static_cast<std::size_t>(measure.size));budget.rows=0;
  Output writer{{budget,&bytes},program,limits,order};auto info=writer.frame(ordinal,payload);
  const auto body_size=bytes.size()-frame_header_size;
  for(unsigned i=0;i<8;++i)bytes[12+i]=static_cast<char>(std::uint64_t(body_size)>>(8*i));
  budget.charge(body_size);const auto body_hash=sha256_fixed({bytes.data()+frame_header_size,body_size});
  std::copy(body_hash.begin(),body_hash.end(),bytes.begin()+20);
  budget.charge(frame_prefix_size);const auto prefix_hash=sha256_fixed({bytes.data(),frame_prefix_size});
  std::copy(prefix_hash.begin(),prefix_hash.end(),bytes.begin()+frame_prefix_size);
  info.body_sha256=body_hash;info.statistics={bytes.size(),budget.used,budget.rows};
  return detail::FrameAccess::frame(std::move(bytes),std::move(info));
}
Inspected inspect(const Program& program,std::string_view bytes,Limits limits) {
  Budget budget{limits.record};return inspect_frame(program,bytes,limits,budget);
}
DecodedInput decode_input(const resource::MemoryAccount& account,const Program& program,
    std::string_view bytes,Limits limits) {
  Budget budget{limits.record};auto info=inspect_frame(program,bytes,limits,budget);require(info.kind==Kind::input);
  const auto metadata=std::get<InputInfo>(info.payload);require(metadata.cells<=SIZE_MAX,ImageFault::limit);
  budget.charge(bytes.size());ImageVector<char> owned(image_allocator<char>(account));owned.assign(bytes.begin(),bytes.end());
  ImageVector<Cell> cells(image_allocator<Cell>(account));cells.reserve(static_cast<std::size_t>(metadata.cells));
  ImageVector<runtime::sql_rows::SourceReplacement> replacements(image_allocator<runtime::sql_rows::SourceReplacement>(account));
  replacements.reserve(static_cast<std::size_t>(metadata.replacements));budget.rows=0;
  Input input{{{owned.data(),owned.size()},budget,frame_header_size},program,limits,&cells,&replacements};
  static_cast<void>(input.body());info.statistics={owned.size(),budget.used,budget.rows};
  return detail::FrameAccess::input(detail::FrameAccess::frame(std::move(owned),std::move(info)),
      std::move(cells),std::move(replacements));
}
DecodedInput encode_input(const resource::MemoryAccount& account,const Program& program,
    std::uint64_t ordinal,const InputView& view,Limits limits) {
  auto frame=encode(account,program,ordinal,PayloadView{view},limits);
  const auto metadata=std::get<InputInfo>(frame.info().payload);require(metadata.cells<=SIZE_MAX,ImageFault::limit);
  ImageVector<Cell> cells(image_allocator<Cell>(account));cells.reserve(static_cast<std::size_t>(metadata.cells));
  ImageVector<runtime::sql_rows::SourceReplacement> replacements(image_allocator<runtime::sql_rows::SourceReplacement>(account));
  replacements.reserve(static_cast<std::size_t>(metadata.replacements));
  Budget budget{limits.record};budget.used=frame.info().statistics.work;
  Input input{{frame.bytes(),budget,frame_header_size},program,limits,&cells,&replacements};static_cast<void>(input.body());
  // The encoded frame is already owned; only flat views are materialized here.
  detail::FrameAccess::work(frame,budget.used);
  return detail::FrameAccess::input(std::move(frame),std::move(cells),std::move(replacements));
}
DecodedInput::DecodedInput(Frame frame,ImageVector<Cell> cells,
    ImageVector<runtime::sql_rows::SourceReplacement> replacements) noexcept
    :frame_(std::move(frame)),cells_(std::move(cells)),replacements_(std::move(replacements)) {}
InputView DecodedInput::view() const & {
  const auto& info=std::get<InputInfo>(frame_.info().payload);std::optional<SourcePosition> source;
  if(info.source_present)source=SourcePosition{frame_.bytes().substr(info.source_begin,info.source_size),info.source_offset};
  return {info.command_sequence,replacements_,source,info.reader};
}
} // namespace crown::recovery::sql_aggregate
