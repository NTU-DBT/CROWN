#include "local_sink_codec.hpp"
#include "binary_detail.hpp"
#include "../runtime/checkpoint_policy.hpp"
#include "crown/ir/digest.hpp"
#include <cstring>

namespace crown::recovery::sink {
namespace {
using namespace binary_detail;
constexpr std::string_view magic="CROWNSK1";
bool utf8(std::string_view value) {
  for(std::size_t i=0;i<value.size();) {
    const auto a=static_cast<unsigned char>(value[i++]);if(a<0x80)continue;
    const unsigned n=a>=0xc2 && a<=0xdf?1:a>=0xe0 && a<=0xef?2:a>=0xf0 && a<=0xf4?3:0;
    if(n==0 || n>value.size()-i)return false;
    const auto b=static_cast<unsigned char>(value[i]);
    if((a==0xe0 && b<0xa0) || (a==0xed && b>0x9f) || (a==0xf0 && b<0x90) || (a==0xf4 && b>0x8f))return false;
    for(unsigned j=0;j<n;++j){const auto c=static_cast<unsigned char>(value[i++]);if(c<0x80 || c>0xbf)return false;}
  }
  return true;
}
// File derives the schema hash; here check supplied identity/type data.
void header_valid(const Header& header,std::span<const ScalarType> schema) {
  require(hex(header.query_id) && hex(header.sink_id) && hex(header.binding.physical_sha256) && hex(header.binding.source_sha256) &&
      hex(header.schema_sha256) && header.binding.catalog_version>0 && header.first_generation>0 && header.fields==schema.size(),ImageFault::binding);
  static_cast<void>(runtime::detail::checkpoint_options(header.binding.policy,0));
  for(const auto type:schema)require(static_cast<unsigned>(type)<=4,ImageFault::scalar);
}
void hash(Writer& writer,std::span<const char> text) {writer.put({text.data(),text.size()});}
void framing(Writer& writer) {
  writer.put(magic);writer.integer(1,2);writer.integer(0,2);writer.integer(0,8);
  std::array<char,128> zeros{};zeros.fill('0');writer.put({zeros.data(),zeros.size()});
}
void header_body(Writer& writer,const Header& h,std::span<const ScalarType> schema) {
  writer.integer(0,1);writer.integer(0,8);hash(writer,h.query_id);hash(writer,h.sink_id);hash(writer,h.binding.physical_sha256);hash(writer,h.binding.source_sha256);
  writer.integer(h.binding.catalog_version,8);writer.integer(1,2);for(const auto word:h.binding.policy)writer.integer(word,8);
  writer.integer(h.first_generation,8);writer.integer(h.base_sequence,8);writer.integer(h.fields,8);hash(writer,h.schema_sha256);
  for(const auto type:schema)writer.integer(static_cast<unsigned>(type),1);
}
void epoch_prefix(Writer& writer,std::uint64_t ordinal,std::uint64_t generation,std::uint64_t sequence,std::uint64_t rows) {
  require(ordinal>0 && generation>0 && sequence>0);writer.integer(1,1);writer.integer(ordinal,8);writer.integer(generation,8);writer.integer(sequence,8);writer.integer(rows,8);
}
void row(Writer& writer,const RowView& value,std::span<const ScalarType> schema) {
  writer.budget.row();require(static_cast<unsigned>(value.operation)<=1 && value.values.size()==schema.size(),ImageFault::binding);
  require(schema.size()<=writer.budget.limits.fields,ImageFault::limit);writer.integer(static_cast<unsigned>(value.operation),1);writer.integer(schema.size(),8);
  for(std::size_t i=0;i<schema.size();++i) {
    const auto cell=value.values[i];require(storage::type_of(cell)==schema[i],ImageFault::binding);
    if(const auto* text=std::get_if<std::string_view>(&cell)){require(text->size()<=writer.budget.limits.scalar_bytes,ImageFault::limit);writer.budget.charge(text->size());require(utf8(*text),ImageFault::scalar);}
    writer.scalar(cell);
  }
}
void finish(ImageVector<char>& bytes,Budget& budget) {
  const auto body=bytes.size()-frame_header_size;budget.charge(body);budget.charge(frame_prefix_size+136);
  for(unsigned i=0;i<8;++i)bytes[12+i]=static_cast<char>((body>>(8*i))&255);
  const auto body_hash=sha256_fixed({bytes.data()+frame_header_size,body});std::copy(body_hash.begin(),body_hash.end(),bytes.begin()+20);
  const auto prefix_hash=sha256_fixed({bytes.data(),frame_prefix_size});std::copy(prefix_hash.begin(),prefix_hash.end(),bytes.begin()+static_cast<std::ptrdiff_t>(frame_prefix_size));
}
void compare_charge(Budget& budget,std::size_t size) {require(size<=(UINT64_MAX-1)/2,ImageFault::work);budget.charge(2*size+1);}
template<std::size_t N> std::array<char,N> read_hash(Reader& reader) {
  std::array<char,N> result{};const auto bytes=reader.take(N);require(hex({bytes.data(),bytes.size()}),ImageFault::binding);std::copy(bytes.begin(),bytes.end(),result.begin());return result;
}
std::uint64_t prefix(std::string_view bytes,Budget& budget) {
  require(bytes.size()>=frame_header_size);Reader reader{bytes,budget};require(reader.take(8)==magic);require(reader.integer(2)==1 && reader.integer(2)==0,ImageFault::version);
  const auto body=reader.integer(8);require(body>=9 && body<=budget.limits.bytes-frame_header_size && body<=SIZE_MAX-frame_header_size,ImageFault::limit);
  static_cast<void>(read_hash<64>(reader));const auto checksum=read_hash<64>(reader);budget.charge(frame_prefix_size);
  require(sha256_fixed(bytes.substr(0,frame_prefix_size))==checksum);return body+frame_header_size;
}
// Inspect checks canonical bytes; decoded native rows own deep payload copies.
detail::Inspected parse(std::string_view bytes,std::span<const ScalarType> schema,Budget& budget,Epoch* decoded,const resource::MemoryAccount& account) {
  require(budget.limits.bytes>=frame_header_size+9,ImageFault::limit);const auto total=prefix(bytes,budget);require(total==bytes.size());
  budget.charge(bytes.size()-frame_header_size);const auto hash=sha256_fixed(bytes.substr(frame_header_size));
  require(std::string_view(hash.data(),hash.size())==bytes.substr(20,64));Reader reader{bytes.substr(frame_header_size),budget};detail::Inspected info;
  const auto kind=reader.integer(1);require(kind<=1);info.header=kind==0;info.ordinal=reader.integer(8);require(info.header==(info.ordinal==0));
  if(info.header) {
    budget.charge(1024);budget.charge(schema.size());
    auto& h=info.binding;h.query_id=read_hash<32>(reader);h.sink_id=read_hash<32>(reader);h.binding.physical_sha256=read_hash<64>(reader);h.binding.source_sha256=read_hash<64>(reader);
    h.binding.catalog_version=reader.integer(8);require(reader.integer(2)==1,ImageFault::version);for(auto& word:h.binding.policy)word=reader.integer(8);
    h.first_generation=reader.integer(8);h.base_sequence=reader.integer(8);h.fields=reader.integer(8);h.schema_sha256=read_hash<64>(reader);
    require(h.fields<=budget.limits.fields && h.fields==schema.size(),ImageFault::binding);
    for(const auto type:schema)require(reader.integer(1)==static_cast<unsigned>(type),ImageFault::binding);
    header_valid(h,schema);
  }else {
    info.generation=reader.integer(8);info.sequence=reader.integer(8);info.rows=reader.integer(8);
    require(info.generation>0 && info.sequence>0 && info.rows<=budget.limits.rows,ImageFault::limit);
    require(info.rows<=(reader.input.size()-reader.position)/9);std::string_view previous;
    if(decoded){decoded->generation=info.generation;decoded->sequence=info.sequence;decoded->rows.reserve(static_cast<std::size_t>(info.rows));}
    ImageVector<storage::ScalarView> cells;
    if(decoded){cells=ImageVector<storage::ScalarView>(image_allocator<storage::ScalarView>(account));cells.reserve(schema.size());}
    for(std::uint64_t i=0;i<info.rows;++i) {
      budget.row();const std::size_t begin=reader.position;const auto operation=reader.integer(1),fields=reader.integer(8);require(operation<=1 && fields==schema.size(),ImageFault::binding);require(fields<=budget.limits.fields,ImageFault::limit);
      if(decoded)cells.clear();
      for(const auto type:schema) {
        const auto cell=binary_detail::scalar(reader);require(storage::type_of(cell)==type,ImageFault::binding);
        if(const auto* text=std::get_if<std::string_view>(&cell)){budget.charge(text->size());require(utf8(*text),ImageFault::scalar);}
        if(decoded)cells.push_back(cell);
      }
      const auto current=reader.input.substr(begin,reader.position-begin);
      if(i){compare_charge(budget,std::min(previous.size(),current.size()));require(previous<current);}
      previous=current;
      if(decoded)decoded->rows.push_back(Row{static_cast<SetOperation>(operation),storage::AccountedRow::copy_of(account,storage::RowView::borrow(cells),image_owner)});
    }
  }
  require(reader.position==reader.input.size());info.work=budget.used;return info;
}
} // namespace
std::array<char,64> schema_sha256(const resource::MemoryAccount& account,std::span<const ScalarType> schema) {
  ImageVector<char> bytes(image_allocator<char>(account));bytes.reserve(schema.size());
  for(const auto type:schema){binary_detail::require(static_cast<unsigned>(type)<=4,ImageFault::scalar);bytes.push_back(static_cast<char>(type));}
  return sha256_fixed({bytes.data(),bytes.size()});
}
namespace detail {
Encoded encode_header(const resource::MemoryAccount& account,const Header& header,std::span<const ScalarType> schema,ImageLimits limits) {
  Budget pre{limits};pre.charge(1024);require(schema.size()<=limits.fields,ImageFault::limit);pre.charge(schema.size());header_valid(header,schema);
  Writer sizing{pre,nullptr};framing(sizing);header_body(sizing,header,schema);require(sizing.size<=SIZE_MAX,ImageFault::limit);
  Encoded result{ImageVector<char>(image_allocator<char>(account)),0};result.bytes.reserve(static_cast<std::size_t>(sizing.size));Budget work{limits};work.charge(pre.used);
  Writer writer{work,&result.bytes};framing(writer);header_body(writer,header,schema);finish(result.bytes,work);result.work=work.used;return result;
}
// Sort views of complete signed row bytes. Scratch and final bytes overlap
// under the receiving account until assembly finishes.
Encoded encode_epoch(const resource::MemoryAccount& account,std::uint64_t ordinal,std::uint64_t generation,std::uint64_t sequence,std::span<const RowView> rows,std::span<const ScalarType> schema,ImageLimits limits) {
  require(rows.size()<=limits.rows && schema.size()<=limits.fields,ImageFault::limit);Budget pre{limits};Writer sizing{pre,nullptr};framing(sizing);epoch_prefix(sizing,ordinal,generation,sequence,rows.size());
  for(const auto& value:rows)row(sizing,value,schema);
  require(sizing.size<=SIZE_MAX,ImageFault::limit);
  struct Segment {std::size_t offset,size;};ImageVector<Segment> segments(image_allocator<Segment>(account));segments.reserve(rows.size());
  ImageVector<char> values(image_allocator<char>(account));values.reserve(static_cast<std::size_t>(sizing.size)-frame_header_size-33);Budget work{limits};work.charge(pre.used);Writer native{work,&values};
  for(const auto& value:rows){const auto begin=values.size();row(native,value,schema);segments.push_back({begin,values.size()-begin});}
  const auto text=[&](const Segment& segment){return std::string_view(values.data()+segment.offset,segment.size);};
  std::sort(segments.begin(),segments.end(),[&](const Segment& a,const Segment& b){compare_charge(work,std::min(a.size,b.size));return text(a)<text(b);});
  for(std::size_t i=1;i<segments.size();++i){compare_charge(work,std::min(segments[i-1].size,segments[i].size));require(text(segments[i-1])!=text(segments[i]));}
  Encoded result{ImageVector<char>(image_allocator<char>(account)),0};result.bytes.reserve(static_cast<std::size_t>(sizing.size));Writer writer{work,&result.bytes};framing(writer);epoch_prefix(writer,ordinal,generation,sequence,rows.size());
  for(const auto& segment:segments)writer.put(text(segment));
  finish(result.bytes,work);result.work=work.used;return result;
}
Inspected inspect(std::string_view bytes,std::span<const ScalarType> schema,ImageLimits limits) {Budget budget{limits};return parse(bytes,schema,budget,nullptr,{});}
// This path admits two complete parse/checksum passes in one record grant.
Epoch decode(const resource::MemoryAccount& account,std::string_view bytes,std::span<const ScalarType> schema,ImageLimits limits) {
  const auto info=inspect(bytes,schema,limits);require(!info.header);Budget budget{limits};budget.charge(info.work);Epoch result{0,0,ImageVector<Row>(image_allocator<Row>(account))};static_cast<void>(parse(bytes,schema,budget,&result,account));return result;
}
// Validate protected length without requiring or inspecting the whole body.
std::uint64_t frame_size(std::string_view bytes,ImageLimits limits,std::uint64_t& work) {
  require(limits.bytes>=frame_header_size+9,ImageFault::limit);Budget budget{limits};const auto result=prefix(bytes,budget);work=budget.used;return result;
}
} // namespace detail
} // namespace crown::recovery::sink
