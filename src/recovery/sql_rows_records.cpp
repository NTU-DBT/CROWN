#include "crown/recovery/sql_rows_records.hpp"
#include "crown/ir/digest.hpp"
#include "binary_detail.hpp"
#include "../frontend/sql_rows_value.hpp"
#include <algorithm>

namespace crown::recovery::sql_rows {
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
using Program = frontend::SqlRowsProgram;
constexpr std::string_view magic = "CROWNRW2";

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
      static_cast<unsigned>(value.reason)<=static_cast<unsigned>(RejectReason::abandoned));
  require(hex(value.input_sha256),ImageFault::binding);
}
void valid(const RowInfo& value) {
  require(value.generation>0 && value.physical_sequence>0 && value.physical_sequence<=value.input_sequence);
  require(value.output_changed==(value.rows!=0) && (!value.output_changed || value.changed));
  require(hex(value.input_sha256),ImageFault::binding);
}
void program_valid(const Program& program,const Limits& limits) {
  require(bool(program),ImageFault::binding);
  require(!program.binding_image().empty(),ImageFault::binding);
  require(program.sources().size()<=limits.record.tables,ImageFault::limit);
}
// The genuine source/output supply SqlTypes without allocating a schema copy.
auto source_columns(const Program& program,std::uint64_t table) {
  const auto sources=program.sources();
  require(table<sources.size() && sources[static_cast<std::size_t>(table)].table.value==table,ImageFault::binding);
  return sources[static_cast<std::size_t>(table)].columns;
}
std::size_t fields(const Program& program) { return program.outputs().size(); }
frontend::SqlType field_type(const Program& program,std::size_t i) { return program.outputs()[i].type; }
void cell_valid(Budget& budget,const Cell& cell,const frontend::SqlType& type) {
  if(cell && std::holds_alternative<std::string_view>(*cell))
    budget.charge(std::get<std::string_view>(*cell).size()); // UTF8 pass in fits.
  require(frontend::rows_detail::fits(cell,type),ImageFault::scalar);
}
bool ordered(Budget& budget,std::string_view a,std::string_view b) {
  budget.charge(std::min(a.size(),b.size()));return a<b;
}
struct KeySlice { std::size_t begin,size; runtime::weighted::SignedMagnitude change; };
struct EncodedRows {
  ImageVector<char> keys;
  ImageVector<KeySlice> order;
  explicit EncodedRows(const resource::MemoryAccount& account)
      : keys(image_allocator<char>(account)),order(image_allocator<KeySlice>(account)) {}
};
void constant_valid(Budget& budget,const Program& program,std::size_t i,const Cell& cell) {
  if(const auto* id=std::get_if<frontend::ExpressionId>(&program.outputs()[i].value)) {
    const auto& expected=program.initial_values()[id->value];budget.charge(1);
    if(cell && expected && std::holds_alternative<std::string_view>(*cell) &&
        std::holds_alternative<std::string_view>(*expected))
      budget.charge(std::min(std::get<std::string_view>(*cell).size(),std::get<std::string_view>(*expected).size()));
    require(cell==expected,ImageFault::scalar);
  }
}
void change_valid(const Program& program,const runtime::weighted::SignedMagnitude& change) {
  require(change.magnitude.value>0,ImageFault::scalar);
  if(program.semantics()==frontend::SqlSemantics::set || program.wrapper()==frontend::SqlWrapper::exists)
    require(change.magnitude.value==1,ImageFault::scalar);
}


// Count-only and materializing passes share validation and byte/work admissions.
// Every cell has a presence byte; row deltas use a signed uint64 magnitude.
struct Output : Writer {
  const Program& program;
  const Limits& limits;
  const EncodedRows* encoded;
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
  void output_row(std::span<const Cell> cells) {
    row(cells,fields(program),[&](std::size_t i){return field_type(program,i);});
    for(std::size_t i=0;i<cells.size();++i)constant_valid(budget,program,i,cells[i]);
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
  void write(const RowEpochView& value) {
    require(encoded!=nullptr,ImageFault::binding);const auto count=encoded->order.size();
    valid(RowInfo{value.generation,value.input_sequence,value.physical_sequence,count,
        value.input_sha256,value.changed,count!=0});
    integer(value.generation,8);integer(value.input_sequence,8);integer(value.physical_sequence,8);
    hash(value.input_sha256);integer(value.changed,1);integer(count!=0,1);integer(count,8);
    for(const auto& item:encoded->order) {
      budget.row();put({encoded->keys.data()+item.begin,item.size});
      integer(item.change.negative,1);integer(item.change.magnitude.value,8);
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
      else if constexpr(std::is_same_v<T,RowEpochView>) {
        require(value.physical_sequence==ordinal);
        result.payload=RowInfo{value.generation,value.input_sequence,value.physical_sequence,
            encoded->order.size(),value.input_sha256,value.changed,!encoded->order.empty()};
      }
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
  RowInfo rows() {
    RowInfo value;value.generation=integer(8);value.input_sequence=integer(8);value.physical_sequence=integer(8);
    value.input_sha256=hash<64>();value.changed=boolean();value.output_changed=boolean();value.rows=size(limits.record.rows);
    valid(value);std::string_view previous;std::array<bool,2> signs{},booleans{};
    if(program.wrapper()==frontend::SqlWrapper::exists)require(value.rows==0 || value.rows==2);
    for(std::uint64_t i=0;i<value.rows;++i) {
      // Parse one typed row inline: inspection uses no row-sized allocation.
      budget.row();const auto start=position;const auto count=size(limits.record.fields);
      require(count==fields(program),ImageFault::binding);bool scalar_boolean=false;
      for(std::size_t j=0;j<count;++j) {
        Cell cell;if(boolean())cell=binary_detail::scalar(*this);
        cell_valid(budget,cell,field_type(program,j));constant_valid(budget,program,j,cell);
        if(program.wrapper()==frontend::SqlWrapper::exists) {
          require(count==1 && cell && std::holds_alternative<bool>(*cell),ImageFault::binding);
          scalar_boolean=std::get<bool>(*cell);
        }
      }
      const auto key=input.substr(start,position-start);
      if(i)require(ordered(budget,previous,key));
      previous=key;
      const runtime::weighted::SignedMagnitude change{boolean(),{integer(8)}};change_valid(program,change);
      if(program.wrapper()==frontend::SqlWrapper::exists) {
        signs[static_cast<std::size_t>(i)]=change.negative;booleans[static_cast<std::size_t>(i)]=scalar_boolean;
      }
    }
    if(program.wrapper()==frontend::SqlWrapper::exists && value.rows)
      require(signs[0]!=signs[1] && booleans[0]!=booleans[1]);
    return value;
  }
  Inspected body() {
    const auto tag=integer(1);require(tag<=static_cast<unsigned>(Kind::row_epoch));
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
        const auto reason=integer(1);require(reason<=static_cast<unsigned>(RejectReason::abandoned));
        v.reason=static_cast<RejectReason>(reason);valid(v);require(v.input_ordinal<value.ordinal);value.payload=v;break;
      }
      case Kind::row_epoch:{auto output=rows();require(output.physical_sequence==value.ordinal);value.payload=output;break;}
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

// Decode genuine SQL output once into one borrowed scratch row. Retain packed
// canonical key bytes for sorting and final serialization, not owning SQL rows.
EncodedRows output_rows(const resource::MemoryAccount& account,const Program& program,
    const PayloadView& payload,const Limits& limits,Budget& budget) {
  EncodedRows result(account);const auto* epoch=std::get_if<RowEpochView>(&payload);if(!epoch)return result;
  require(epoch->output && epoch->output->active(),ImageFault::binding);
  const auto count=epoch->output->output_size();require(count.has_value(),ImageFault::binding);
  require(*count<=limits.record.rows && fields(program)<=limits.record.fields,ImageFault::limit);
  const auto a=epoch->output->program().binding_image(),b=program.binding_image();
  require(!a.empty() && !b.empty(),ImageFault::binding);
  // Normal Session handles share this immutable backing: no SQL/catalog scan.
  // Distinct genuine handles retain the exact charged byte-comparison fallback.
  if(a.data()!=b.data() || a.size()!=b.size()) {
    budget.charge(std::min(a.size(),b.size()));require(a==b,ImageFault::binding);
  }
  require(epoch->output->sequence()==epoch->physical_sequence &&
      epoch->output->changed()==epoch->changed,ImageFault::binding);
  if(program.wrapper()==frontend::SqlWrapper::exists)require(*count==0 || *count==2);
  ImageVector<Cell> scratch(image_allocator<Cell>(account));scratch.resize(fields(program));result.order.reserve(*count);
  Output writer{{budget,&result.keys},program,limits,nullptr};std::array<bool,2> signs{},booleans{};
  for(std::size_t i=0;i<*count;++i) {
    const auto output=epoch->output->output_change(i,scratch);change_valid(program,output.change);
    const auto begin=result.keys.size();writer.output_row(output.values);
    result.order.push_back({begin,result.keys.size()-begin,output.change});
    if(program.wrapper()==frontend::SqlWrapper::exists) {
      require(output.values.size()==1 && output.values[0] && std::holds_alternative<bool>(*output.values[0]),ImageFault::binding);
      signs[i]=output.change.negative;booleans[i]=std::get<bool>(*output.values[0]);
    }
  }
  if(program.wrapper()==frontend::SqlWrapper::exists && *count)require(signs[0]!=signs[1] && booleans[0]!=booleans[1]);
  const auto key=[&](const KeySlice& item){return std::string_view(result.keys.data()+item.begin,item.size);};
  std::sort(result.order.begin(),result.order.end(),[&](const KeySlice& a,const KeySlice& b){return ordered(budget,key(a),key(b));});
  for(std::size_t i=1;i<result.order.size();++i)require(ordered(budget,key(result.order[i-1]),key(result.order[i])));
  return result;
}
} // namespace

Frame encode(const resource::MemoryAccount& account,const Program& program,std::uint64_t ordinal,
    const PayloadView& payload,Limits limits) {
  program_valid(program,limits);Budget budget{limits.record};const auto encoded=output_rows(account,program,payload,limits,budget);
  budget.rows=0;Output measure{{budget,nullptr},program,limits,&encoded};static_cast<void>(measure.frame(ordinal,payload));
  require(measure.size<=SIZE_MAX,ImageFault::limit);ImageVector<char> bytes(image_allocator<char>(account));
  bytes.reserve(static_cast<std::size_t>(measure.size));budget.rows=0;
  Output writer{{budget,&bytes},program,limits,&encoded};auto info=writer.frame(ordinal,payload);
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
} // namespace crown::recovery::sql_rows
