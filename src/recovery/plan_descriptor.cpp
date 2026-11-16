#include "crown/recovery/plan_descriptor.hpp"
#include "crown/ir/digest.hpp"
#include "../runtime/checkpoint_policy.hpp"
#include <algorithm>
#include <limits>

namespace crown::recovery {
namespace {
[[noreturn]] void fail(ImageFault fault) {throw ImageFailure(fault);}
bool hex(std::span<const char> value) {
  return std::all_of(value.begin(),value.end(),[](char c){return (c>='0' && c<='9') || (c>='a' && c<='f');});
}
bool logical_binding(const ImageBinding& a,const ImageBinding& b) {
  return a.source_sha256==b.source_sha256 && a.catalog_version==b.catalog_version && a.policy==b.policy;
}
void binding(const ImageBinding& value) {
  if(!hex(value.physical_sha256) || !hex(value.source_sha256) || value.catalog_version==0)fail(ImageFault::binding);
  static_cast<void>(runtime::detail::checkpoint_options(value.policy,0));
}
void validate(const PlanSelection& value,const PlanDescriptorLimits& limits) {
  // Metadata continuity is separate from checked compiler/native equivalence
  // and the locked root/WAL/sink publication protocol.
  const auto& parent=value.predecessor;
  if(!hex(parent.query_id) || !hex(parent.checkpoint_sha256) || parent.first_generation==0 || parent.generation<parent.first_generation ||
      parent.generation==UINT64_MAX || value.generation!=parent.generation+1 || value.physical_sequence<parent.physical_sequence ||
      value.command_sequence<parent.command_sequence || (parent.plan_sha256 && !hex(*parent.plan_sha256)) ||
      (value.last_switch_epoch && *value.last_switch_epoch>value.physical_sequence))fail(ImageFault::binding);
  binding(value.source);binding(value.target);
  if(!logical_binding(value.source,value.target))fail(ImageFault::binding);
  if(parent.delivery && (!value.sink_origin || parent.delivery->sink_id!=value.sink_origin->sink_id ||
      !hex(parent.delivery->content_sha256) || parent.delivery->sequence!=parent.physical_sequence || parent.delivery->bytes==0))fail(ImageFault::binding);
  if(value.sink_origin) {
    const auto& origin=*value.sink_origin;binding(origin.binding);
    if(origin.query_id!=parent.query_id || !hex(origin.sink_id) || !hex(origin.schema_sha256) || !logical_binding(origin.binding,value.target) ||
        origin.first_generation==0 || origin.first_generation>parent.generation || origin.base_sequence>value.physical_sequence ||
        (parent.delivery && origin.base_sequence>parent.physical_sequence))fail(ImageFault::binding);
    if(origin.fields>limits.fields)fail(ImageFault::limit);
  }
}
std::uint64_t flags(const PlanSelection& value) {
  return (value.sink_origin?1U:0U)|(value.predecessor.delivery?2U:0U)|(value.predecessor.plan_sha256?4U:0U);
}
ImageStatistics statistics(std::uint64_t bytes,const PlanDescriptorLimits& limits) {
  if(bytes>limits.bytes || bytes>SIZE_MAX)fail(ImageFault::limit);
  if(bytes>UINT64_MAX/4 || bytes*4>limits.work)fail(ImageFault::work);
  return {bytes,bytes*4,0};
}
struct Writer {
  // encode_plan_descriptor sizes the complete layout before these direct stores.
  ImageVector<char>& bytes;
  std::size_t offset=0;
  void text(std::string_view value) {std::copy(value.begin(),value.end(),bytes.begin()+static_cast<std::ptrdiff_t>(offset));offset+=value.size();}
  template<std::size_t N> void text(const std::array<char,N>& value) {text({value.data(),value.size()});}
  void word(std::uint64_t value,unsigned width=8) {for(unsigned i=0;i<width;++i)bytes[offset++]=static_cast<char>((value>>(8*i))&255);}
  void image(const ImageBinding& value) {text(value.physical_sha256);text(value.source_sha256);word(value.catalog_version);for(const auto field:value.policy)word(field);}
};
struct Reader {
  std::string_view bytes;
  std::size_t offset=0;
  std::string_view text(std::uint64_t size) {
    if(offset>bytes.size() || size>bytes.size()-offset)fail(ImageFault::corrupt);
    const auto result=bytes.substr(offset,static_cast<std::size_t>(size));offset+=static_cast<std::size_t>(size);return result;
  }
  template<std::size_t N> void text(std::array<char,N>& value) {const auto part=text(N);std::copy(part.begin(),part.end(),value.begin());}
  std::uint64_t word(unsigned width=8) {
    const auto part=text(width);std::uint64_t result=0;
    for(unsigned i=0;i<width;++i)result|=std::uint64_t(static_cast<unsigned char>(part[i]))<<(8*i);
    return result;
  }
  void image(ImageBinding& value) {text(value.physical_sha256);text(value.source_sha256);value.catalog_version=word();for(auto& field:value.policy)field=word();}
};
void write_selection(Writer& w,const PlanSelection& value) {
  const auto& parent=value.predecessor;w.text(parent.query_id);w.word(parent.generation);w.word(parent.first_generation);w.text(parent.checkpoint_sha256);w.word(parent.physical_sequence);w.word(parent.command_sequence);
  if(parent.delivery){const auto& anchor=*parent.delivery;w.text(anchor.sink_id);w.word(anchor.sequence);w.word(anchor.bytes);w.text(anchor.content_sha256);}
  if(parent.plan_sha256)w.text(*parent.plan_sha256);
  w.image(value.source);w.image(value.target);w.word(value.generation);w.word(value.physical_sequence);w.word(value.command_sequence);
  if(value.last_switch_epoch)w.word(*value.last_switch_epoch);
  if(value.sink_origin){const auto& origin=*value.sink_origin;w.text(origin.query_id);w.text(origin.sink_id);w.image(origin.binding);w.word(origin.first_generation);w.word(origin.base_sequence);w.word(origin.fields);w.text(origin.schema_sha256);}
}
PlanSelection read_selection(Reader& r,std::uint64_t bits,bool switched_epoch) {
  PlanSelection value;auto& parent=value.predecessor;r.text(parent.query_id);parent.generation=r.word();parent.first_generation=r.word();r.text(parent.checkpoint_sha256);parent.physical_sequence=r.word();parent.command_sequence=r.word();
  if(bits&2U){GenerationDeliveryAnchor anchor;r.text(anchor.sink_id);anchor.sequence=r.word();anchor.bytes=r.word();r.text(anchor.content_sha256);parent.delivery=anchor;}
  if(bits&4U){std::array<char,64> hash{};r.text(hash);parent.plan_sha256=hash;}
  r.image(value.source);r.image(value.target);value.generation=r.word();value.physical_sequence=r.word();value.command_sequence=r.word();
  if(switched_epoch)value.last_switch_epoch=r.word();
  if(bits&1U){sink::Header origin;r.text(origin.query_id);r.text(origin.sink_id);r.image(origin.binding);origin.first_generation=r.word();origin.base_sequence=r.word();origin.fields=r.word();r.text(origin.schema_sha256);value.sink_origin=origin;}
  return value;
}
} // namespace
EncodedPlanDescriptor encode_plan_descriptor(const resource::MemoryAccount& account,const PlanSelection& value,
    std::string_view artifact,PlanDescriptorLimits limits) {
  if(artifact.empty() || artifact.size()>limits.artifact_bytes)fail(ImageFault::limit);
  const std::uint64_t overhead=932+(value.predecessor.delivery?112U:0U)+(value.predecessor.plan_sha256?64U:0U)+(value.sink_origin?496U:0U)+(value.last_switch_epoch?8U:0U);
  if(artifact.size()>UINT64_MAX-overhead)fail(ImageFault::limit);
  const auto stats=statistics(overhead+artifact.size(),limits);
  validate(value,limits);
  EncodedPlanDescriptor result{ImageVector<char>(image_allocator<char>(account)),stats};result.bytes.resize(static_cast<std::size_t>(stats.bytes));
  Writer w{result.bytes};w.text("CROWNPL1");w.word(value.last_switch_epoch?2:1,2);w.word(flags(value),2);w.word(stats.bytes-84);write_selection(w,value);w.word(artifact.size());w.text(artifact);
  if(w.offset!=result.bytes.size()-64)fail(ImageFault::corrupt);
  w.text(sha256_fixed({result.bytes.data(),w.offset}));return result;
}
InspectedPlanDescriptor inspect_plan_descriptor(std::string_view bytes,PlanDescriptorLimits limits) {
  const auto stats=statistics(bytes.size(),limits);
  if(bytes.size()<932 || bytes.substr(0,8)!="CROWNPL1")fail(ImageFault::corrupt);
  const auto digest=sha256_fixed(bytes.substr(0,bytes.size()-64));
  if(bytes.substr(bytes.size()-64)!=std::string_view(digest.data(),digest.size()))fail(ImageFault::corrupt);
  Reader header{bytes.substr(8,12)};const auto version=header.word(2),bits=header.word(2),body=header.word();
  if(version!=1 && version!=2)fail(ImageFault::version);
  if(bits>7 || body!=bytes.size()-84)fail(ImageFault::corrupt);
  Reader r{bytes.substr(20,bytes.size()-84)};auto selection=read_selection(r,bits,version==2);validate(selection,limits);
  const auto size=r.word();if(size==0 || size>limits.artifact_bytes)fail(ImageFault::limit);
  const auto artifact=r.text(size);if(r.offset!=r.bytes.size())fail(ImageFault::corrupt);
  return {std::move(selection),artifact,stats};
}
} // namespace crown::recovery
