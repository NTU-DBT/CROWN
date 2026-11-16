#include "crown/recovery/journal.hpp"
#include "binary_detail.hpp"
#include "../runtime/checkpoint_policy.hpp"
#include "crown/ir/digest.hpp"
#include <algorithm>
#include <limits>

namespace crown::recovery::journal {
namespace {
using namespace binary_detail;
constexpr std::string_view magic="CROWNWAL";
bool utf8(std::string_view value) {
  for(std::size_t i=0;i<value.size();) {
    const auto a=static_cast<unsigned char>(value[i++]);if(a==0)return false;if(a<0x80)continue;
    const unsigned count=a>=0xc2 && a<=0xdf?1:a>=0xe0 && a<=0xef?2:a>=0xf0 && a<=0xf4?3:0;
    if(!count || count>value.size()-i)return false;
    const auto b=static_cast<unsigned char>(value[i]);
    if((a==0xe0 && b<0xa0) || (a==0xed && b>0x9f) || (a==0xf0 && b<0x90) || (a==0xf4 && b>0x8f))return false;
    for(unsigned j=0;j<count;++j){const auto c=static_cast<unsigned char>(value[i++]);if(c<0x80 || c>0xbf)return false;}
  }
  return true;
}
void source_name(std::string_view value) {require(!value.empty() && utf8(value));}
void valid_header(const Header& value) {
  require(hex(value.query_id) && value.generation>0 && hex(value.binding.physical_sha256) && hex(value.binding.source_sha256) &&
      value.binding.catalog_version>0 && hex(value.checkpoint_sha256),ImageFault::binding);
  require(static_cast<unsigned>(value.input_kind)<=2);
  require(value.input_kind==InputKind::window || value.physical_sequence==value.command_sequence);
  static_cast<void>(runtime::detail::checkpoint_options(value.binding.policy,0));
}
// A null output validates/counts; both encode passes borrow the same payload.
struct Output:Writer {
  const Limits& limits;
  void hash(std::span<const char> value){require(hex(value),ImageFault::binding);put({value.data(),value.size()});}
  void row(storage::TupleValuesView value) {
    budget.row();require(value.size()<=limits.record.fields,ImageFault::limit);integer(value.size(),8);
    for(std::size_t i=0;i<value.size();++i)scalar(value[i]);
  }
  void write(const Header& value) {
    valid_header(value);hash(value.query_id);integer(value.generation,8);hash(value.binding.physical_sha256);hash(value.binding.source_sha256);
    integer(value.binding.catalog_version,8);integer(1,2);for(auto word:value.binding.policy)integer(word,8);
    hash(value.checkpoint_sha256);integer(value.physical_sequence,8);integer(value.command_sequence,8);integer(static_cast<unsigned>(value.input_kind),1);
  }
  void write(const InputView& value) {
    integer(value.item.index(),1);std::uint64_t sequence=0;
    std::visit([&](const auto& item) {
      using T=std::remove_cvref_t<decltype(item)>;
      if constexpr(std::is_same_v<T,io::InputEventView>) {
        sequence=item.update.sequence;require(sequence>0);integer(sequence,8);
        integer(item.update.table.value,8);require(static_cast<unsigned>(item.update.operation)<=1);integer(static_cast<unsigned>(item.update.operation),1);row(item.update.values);
      }else {
        sequence=item.sequence;require(sequence>0 && item.command.index()>0 && item.command.index()<=3);integer(sequence,8);integer(item.command.index()-1,1);
        std::visit([&](const auto& command) {
          using C=std::remove_cvref_t<decltype(command)>;
          if constexpr(std::is_same_v<C,io::WindowInsertView>) {
            require(command.label>0);integer(command.label,8);integer(command.table.value,8);row(command.values);integer(command.timestamp,8);
          }else if constexpr(std::is_same_v<C,io::WindowWithdraw>){require(command.label>0);integer(command.label,8);}
          else if constexpr(std::is_same_v<C,io::AdvanceWatermark>)integer(command.watermark,8);
          else require(false);
        },item.command);
      }
      integer(item.source_position.has_value(),1);
      if(item.source_position) {
        const auto& source=*item.source_position;require(source.source.size()<=limits.source_bytes,ImageFault::limit);
        budget.charge(source.source.size());source_name(source.source);integer(source.source.size(),8);put(source.source);integer(source.offset,8);
      }
    },value.item);
    integer(value.reader.has_value(),1);
    if(value.reader) {
      require(std::holds_alternative<io::InputEventView>(value.item));const auto& reader=*value.reader;
      require(reader.records==sequence && (reader.header_read || reader.csv_fields.empty()));
      require(reader.csv_fields.size()<=limits.record.fields,ImageFault::limit);
      integer(reader.bytes,8);integer(reader.records,8);integer(reader.header_read,1);integer(reader.csv_fields.size(),8);
      for(std::size_t i=0;i<reader.csv_fields.size();++i) {
        require(reader.csv_fields[i]<reader.csv_fields.size());
        for(std::size_t j=0;j<i;++j){budget.charge(8);require(reader.csv_fields[j]!=reader.csv_fields[i]);}
        integer(reader.csv_fields[i],8);
      }
    }
  }
  void write(const Commit& value) {
    require(value.input_ordinal>0 && static_cast<unsigned>(value.kind)<=1);
    integer(value.input_ordinal,8);hash(value.input_sha256);integer(static_cast<unsigned>(value.kind),1);
    integer(value.physical_sequence,8);integer(value.command_sequence,8);integer(value.substep,8);integer(value.completes_input,1);
  }
  void write(const Checkpoint& value) {integer(value.physical_sequence,8);integer(value.command_sequence,8);hash(value.checkpoint_sha256);}
  void frame(std::uint64_t ordinal,const PayloadView& value) {
    require((value.index()==0)==(ordinal==0));
    if(const auto* commit=std::get_if<Commit>(&value))require(commit->input_ordinal<ordinal);
    put(magic);integer(1,2);integer(0,2);integer(0,8);std::array<char,64> blank{};blank.fill('0');put({blank.data(),blank.size()});put({blank.data(),blank.size()});
    integer(value.index(),1);integer(ordinal,8);std::visit([&](const auto& item){write(item);},value);
  }
};
struct Input:Reader {
  const Limits& limits;
  resource::MemoryAccount account;
  Decoded* output;
  bool boolean(){const auto value=integer(1);require(value<=1);return value!=0;}
  template<std::size_t N> std::array<char,N> hash() {
    std::array<char,N> value{};const auto text=take(N);std::copy(text.begin(),text.end(),value.begin());require(hex(value),ImageFault::binding);return value;
  }
  // Inspect keeps scalar views transient; decode copies them into a funded row.
  void row(InputMetadata& metadata) {
    budget.row();const auto fields=size(limits.record.fields);require(fields<=input.size()-position);metadata.fields=fields;
    ImageVector<storage::ScalarView> cells;
    if(output){cells=ImageVector<storage::ScalarView>(image_allocator<storage::ScalarView>(account));cells.reserve(fields);}
    for(std::size_t i=0;i<fields;++i){auto value=binary_detail::scalar(*this);if(output)cells.push_back(value);}
    if(output)output->row=storage::AccountedRow::copy_of(account,storage::RowView::borrow(cells),image_owner);
  }
  Header header() {
    Header value;value.query_id=hash<32>();value.generation=integer(8);value.binding.physical_sha256=hash<64>();value.binding.source_sha256=hash<64>();
    value.binding.catalog_version=integer(8);require(integer(2)==1,ImageFault::version);for(auto& word:value.binding.policy)word=integer(8);
    value.checkpoint_sha256=hash<64>();value.physical_sequence=integer(8);value.command_sequence=integer(8);
    const auto kind=integer(1);require(kind<=2);value.input_kind=static_cast<InputKind>(kind);valid_header(value);return value;
  }
  InputMetadata item() {
    InputMetadata value;const auto tag=integer(1);require(tag<=1);value.window=tag!=0;value.sequence=integer(8);require(value.sequence>0);
    if(!value.window) {
      value.table=size(SIZE_MAX);const auto operation=integer(1);require(operation<=1);value.operation=static_cast<SetOperation>(operation);row(value);
    }else {
      const auto kind=integer(1);require(kind<=2);value.window_kind=static_cast<std::uint8_t>(kind);
      if(kind==0){value.label=integer(8);require(value.label>0);value.table=size(SIZE_MAX);row(value);value.timestamp=integer(8);}
      else if(kind==1){value.label=integer(8);require(value.label>0);}
      else value.watermark=integer(8);
    }
    value.source_present=boolean();
    if(value.source_present) {
      const auto text=take(size(limits.source_bytes));budget.charge(text.size());source_name(text);value.source_size=text.size();value.source_offset=integer(8);
      if(output)output->source.assign(text.begin(),text.end());
    }
    value.reader_present=boolean();
    if(value.reader_present) {
      require(!value.window);value.reader_bytes=integer(8);value.reader_records=integer(8);require(value.reader_records==value.sequence);
      value.header_read=boolean();const auto count=size(limits.record.fields);require(value.header_read || count==0);require(count<=(input.size()-position)/8);value.csv_fields=count;
      if(output)output->csv_fields.reserve(count);
      const auto start=position;
      for(std::size_t i=0;i<count;++i) {
        const auto field=integer(8);require(field<count);
        for(std::size_t j=0;j<i;++j) {
          budget.charge(8);std::uint64_t previous=0;
          for(unsigned byte=0;byte<8;++byte)previous|=std::uint64_t(static_cast<unsigned char>(input[start+8*j+byte]))<<(8*byte);
          require(previous!=field);
        }
        if(output)output->csv_fields.push_back(field);
      }
    }
    return value;
  }
  Inspected read() {
    Inspected value;const auto kind=integer(1);require(kind<=3);value.kind=static_cast<Kind>(kind);value.ordinal=integer(8);require((kind==0)==(value.ordinal==0));
    switch(value.kind) {
      case Kind::header:value.header=header();break;
      case Kind::input:value.input=item();break;
      case Kind::commit:{
        auto& c=value.commit;c.input_ordinal=integer(8);require(c.input_ordinal>0 && c.input_ordinal<value.ordinal);c.input_sha256=hash<64>();
        const auto tag=integer(1);require(tag<=1);c.kind=static_cast<CommitKind>(tag);c.physical_sequence=integer(8);c.command_sequence=integer(8);c.substep=integer(8);c.completes_input=boolean();
        break;
      }
      case Kind::checkpoint:{auto& c=value.checkpoint;c.physical_sequence=integer(8);c.command_sequence=integer(8);c.checkpoint_sha256=hash<64>();break;}
    }
    require(position==input.size());return value;
  }
};
// Admit both structural passes and checksums before final-buffer allocation.
Encoded encode_impl(const resource::MemoryAccount& account,std::uint64_t ordinal,const PayloadView& value,Limits limits) {
  Budget budget{limits.record};Output preflight{{budget,nullptr},limits};preflight.frame(ordinal,value);
  const auto size=preflight.size,visits=budget.used;require(size<=SIZE_MAX,ImageFault::limit);budget.charge(visits);budget.charge(size-frame_header_size);budget.charge(frame_prefix_size);
  Encoded result{ImageVector<char>(image_allocator<char>(account)),{size,budget.used,budget.rows}};result.bytes.reserve(static_cast<std::size_t>(size));
  Budget materialization{limits.record};Output writer{{materialization,&result.bytes},limits};writer.frame(ordinal,value);require(writer.size==size && materialization.used==visits);
  for(unsigned i=0;i<8;++i)result.bytes[12+i]=static_cast<char>((size-frame_header_size)>>(8*i));
  const auto hash=sha256_fixed({result.bytes.data()+frame_header_size,result.bytes.size()-frame_header_size});std::copy(hash.begin(),hash.end(),result.bytes.begin()+20);
  const auto prefix_hash=sha256_fixed({result.bytes.data(),frame_prefix_size});std::copy(prefix_hash.begin(),prefix_hash.end(),result.bytes.begin()+frame_prefix_size);return result;
}
Inspected inspect_impl(std::string_view bytes,Limits limits) {
  require(bytes.size()<=limits.record.bytes,ImageFault::limit);Budget budget{limits.record};Reader frame{bytes,budget};require(frame.take(8)==magic);
  require(frame.integer(2)==1 && frame.integer(2)==0,ImageFault::version);const auto size=frame.integer(8);const auto expected=frame.take(64);const auto prefix_hash=frame.take(64);
  require(hex({prefix_hash.data(),prefix_hash.size()}));budget.charge(frame_prefix_size);
  const auto actual_prefix=sha256_fixed(bytes.substr(0,frame_prefix_size));require(std::equal(actual_prefix.begin(),actual_prefix.end(),prefix_hash.begin()));
  require(size==bytes.size()-frame_header_size && hex({expected.data(),expected.size()}));budget.charge(size);
  const auto actual=sha256_fixed(bytes.substr(frame_header_size));require(std::equal(actual.begin(),actual.end(),expected.begin()));
  const auto before=budget.used;Input body{{bytes.substr(frame_header_size),budget},limits,{},nullptr};auto value=body.read();
  budget.charge(budget.used-before);value.body_sha256=actual;value.statistics={bytes.size(),budget.used,budget.rows};return value;
}
Decoded decode_impl(const resource::MemoryAccount& account,std::string_view bytes,Limits limits) {
  const auto validated=inspect_impl(bytes,limits);Decoded result{validated,{},ImageVector<char>(image_allocator<char>(account)),ImageVector<std::uint64_t>(image_allocator<std::uint64_t>(account))};
  Budget materialization{limits.record};Input body{{bytes.substr(frame_header_size),materialization},limits,account,&result};static_cast<void>(body.read());return result;
}
// Structural continuity only; pending.frame borrows caller bytes.
// File repair and native transition validation belong to file/session owners.
bool next_record(Scanned& result,std::string_view tail,const ScanLimits& limits,const Header* expected,bool allow_torn) {
  require(result.consumed<=limits.bytes && tail.size()<=limits.bytes-result.consumed && limits.record.record.bytes>=frame_header_size+9,ImageFault::limit);
  if(expected && result.records>0)require(result.header==*expected,ImageFault::binding);
  const auto charge=[&](std::uint64_t count){require(result.work<=limits.work && count<=limits.work-result.work,ImageFault::work);result.work+=count;};
    require(result.records<limits.records,ImageFault::limit);
    charge(std::min(tail.size(),frame_header_size));
    constexpr std::string_view fixed{"CROWNWAL\1\0\0\0",12};
    const auto compared=std::min(tail.size(),fixed.size());require(tail.substr(0,compared)==fixed.substr(0,compared));
    std::uint64_t body_size=0;
    if(tail.size()>=20) {
      for(unsigned byte=0;byte<8;++byte)body_size|=std::uint64_t(static_cast<unsigned char>(tail[12+byte]))<<(8*byte);
      require(body_size>=9);require(body_size<=limits.record.record.bytes-frame_header_size && body_size<=SIZE_MAX-frame_header_size,ImageFault::limit);
      const auto hash=tail.substr(20,std::min<std::size_t>(64,tail.size()-20));require(hex({hash.data(),hash.size()}));
    }
    if(tail.size()>frame_prefix_size) {
      const auto hash=tail.substr(frame_prefix_size,std::min<std::size_t>(64,tail.size()-frame_prefix_size));require(hex({hash.data(),hash.size()}));
    }
    if(tail.size()>=frame_header_size) {
      charge(frame_prefix_size);const auto actual=sha256_fixed(tail.substr(0,frame_prefix_size));
      require(std::equal(actual.begin(),actual.end(),tail.begin()+frame_prefix_size));
    }
    if(tail.size()<frame_header_size || body_size>tail.size()-frame_header_size) {
      require(allow_torn && result.records>0);result.torn_tail=true;return false;
    }
    const auto size=frame_header_size+static_cast<std::size_t>(body_size);
    auto record_limits=limits.record;record_limits.record.work=std::min(record_limits.record.work,limits.work-result.work);
    const auto info=inspect_impl(tail.substr(0,size),record_limits);charge(info.statistics.work);require(info.ordinal==result.records);
    const auto end=result.consumed+size;
    if(result.records==0) {
      require(info.kind==Kind::header);result.header=info.header;
      if(expected)require(result.header==*expected,ImageFault::binding);
      result.physical_sequence=info.header.physical_sequence;result.command_sequence=info.header.command_sequence;
      result.last_commit_end=end;result.last_command_end=end;result.last_checkpoint_end=end;
    }else if(info.kind==Kind::input) {
      require(!result.pending && result.command_sequence<UINT64_MAX && info.input.sequence==result.command_sequence+1);
      const bool window=result.header.input_kind==InputKind::window;
      require(info.input.window==window && info.input.reader_present==(result.header.input_kind==InputKind::stream));
      if(result.reader_bytes && info.input.reader_present)require(info.input.reader_bytes>=*result.reader_bytes);
      result.pending=PendingView{info.ordinal,0,info.input,info.body_sha256,tail.substr(0,size)};
    }else if(info.kind==Kind::commit) {
      require(result.pending.has_value());auto& pending=*result.pending;const auto& commit=info.commit;
      require(commit.input_ordinal==pending.ordinal && commit.input_sha256==pending.input_sha256 && commit.substep==pending.next_substep);
      const bool physical=commit.kind==CommitKind::physical;
      if(physical)require(result.physical_sequence<UINT64_MAX && commit.physical_sequence==result.physical_sequence+1);
      else require(commit.physical_sequence==result.physical_sequence);
      if(!commit.completes_input)require(result.header.input_kind==InputKind::window && pending.input.window_kind==2);
      if(result.header.input_kind!=InputKind::window)require(physical && commit.completes_input && commit.substep==0 && commit.physical_sequence==pending.input.sequence);
      require(commit.command_sequence==(commit.completes_input?pending.input.sequence:result.command_sequence));
      result.physical_sequence=commit.physical_sequence;result.last_commit_end=end;
      if(commit.completes_input) {
        result.command_sequence=commit.command_sequence;result.last_command_end=end;
        if(pending.input.reader_present)result.reader_bytes=pending.input.reader_bytes;
        result.pending.reset();
      }else {require(pending.next_substep<UINT64_MAX);++pending.next_substep;}
    }else if(info.kind==Kind::checkpoint) {
      require(!result.pending && info.checkpoint.physical_sequence==result.physical_sequence && info.checkpoint.command_sequence==result.command_sequence);
      result.last_checkpoint_end=end;
    }else require(false);
    result.consumed=end;++result.records;
  return true;
}
Scanned scan_impl(std::string_view bytes,ScanLimits limits,const Header* expected) {
  require(bytes.size()<=limits.bytes && limits.record.record.bytes>=frame_header_size+9,ImageFault::limit);
  Scanned result;
  while(result.consumed<bytes.size())if(!next_record(result,bytes.substr(result.consumed),limits,expected,true))return result;
  require(result.records>0);return result;
}
Scanned advance_impl(const Scanned& before,std::string_view frame,ScanLimits limits,const Header* expected) {
  auto result=before;result.torn_tail=false;
  require(next_record(result,frame,limits,expected,false) && result.consumed-before.consumed==frame.size());
  return result;
}
template<class Action> auto guarded(Action&& action) {
  try{return action();}catch(const ImageFailure& error){throw Failure(error.fault());}
}
} // namespace
Encoded encode(const resource::MemoryAccount& account,std::uint64_t ordinal,const PayloadView& value,Limits limits) {
  return guarded([&]{return encode_impl(account,ordinal,value,limits);});
}
Inspected inspect(std::string_view bytes,Limits limits) {return guarded([&]{return inspect_impl(bytes,limits);});}
Decoded decode(const resource::MemoryAccount& account,std::string_view bytes,Limits limits) {
  return guarded([&]{return decode_impl(account,bytes,limits);});
}
Scanned scan(std::string_view bytes,ScanLimits limits,const Header* expected) {return guarded([&]{return scan_impl(bytes,limits,expected);});}
Cursor::Cursor(ScanLimits limits,const Header* expected):limits_(limits),expected_(expected?std::optional<Header>{*expected}:std::nullopt) {}
Cursor::Cursor(Cursor&& other) noexcept
    :limits_(other.limits_),expected_(other.expected_),state_(other.state_),active_(other.active_) {other.active_=false;other.state_={};}
Cursor& Cursor::operator=(Cursor&& other) noexcept {
  if(this!=&other){limits_=other.limits_;expected_=other.expected_;state_=other.state_;active_=other.active_;other.active_=false;other.state_={};}
  return *this;
}
// Publish the copied continuation only after one complete frame validates.
Scanned Cursor::feed(std::string_view frame) & {
  if(!active_)throw Failure(Fault::corrupt);
  auto next=guarded([&]{return advance_impl(state_,frame,limits_,expected_?&*expected_:nullptr);});
  state_=std::move(next);return state_;
}
Scanned Cursor::finish_tail(std::string_view tail) & {
  if(!active_)throw Failure(Fault::corrupt);
  if(tail.empty())return state_;
  auto next=state_;
  const bool complete=guarded([&]{return next_record(next,tail,limits_,expected_?&*expected_:nullptr,true);});
  if(complete)throw Failure(Fault::corrupt);
  state_=std::move(next);return state_;
}
// Returned views borrow Decoded storage; native admission checks actual policy.
InputView Decoded::input_view() const & {
  const auto& metadata=info.input;
  if(info.kind!=Kind::input || metadata.sequence==0 || metadata.table>SIZE_MAX || metadata.fields!=row.size() ||
      metadata.source_size!=source.size() || metadata.csv_fields!=csv_fields.size() ||
      (metadata.source_present && source.empty()) || (metadata.reader_present && metadata.window))throw Failure(Fault::corrupt);
  std::optional<io::SourcePositionView> position;
  if(metadata.source_present)position=io::SourcePositionView{source_name(),metadata.source_offset};
  InputView result;
  if(!metadata.window) {
    if(static_cast<unsigned>(metadata.operation)>1)throw Failure(Fault::corrupt);
    result.item=io::InputEventView{{metadata.sequence,TableId{static_cast<std::size_t>(metadata.table)},metadata.operation,
        storage::TupleValuesView::borrow(row.view())},position};
  }else {
    io::WindowCommandView command;command.sequence=metadata.sequence;command.source_position=position;
    switch(metadata.window_kind) {
      case 0:command.command=io::WindowInsertView{metadata.label,TableId{static_cast<std::size_t>(metadata.table)},storage::TupleValuesView::borrow(row.view()),metadata.timestamp};break;
      case 1:command.command=io::WindowWithdraw{metadata.label};break;
      case 2:command.command=io::AdvanceWatermark{metadata.watermark};break;
      default:throw Failure(Fault::corrupt);
    }
    result.item=std::move(command);
  }
  if(metadata.reader_present)result.reader=ReaderAdvanceView{metadata.reader_bytes,metadata.reader_records,metadata.header_read,csv_fields};
  return result;
}
} // namespace crown::recovery::journal
