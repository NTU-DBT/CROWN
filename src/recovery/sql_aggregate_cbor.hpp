#pragma once

#include "crown/recovery/sql_aggregate_descriptor.hpp"
#include "binary_detail.hpp"

namespace crown::recovery::sql_aggregate::detail {
// The factory's CBOR subset is definite integers/TEXT/arrays/maps/bool/NULL.
// Validate minimal widths, key UTF8, depth/items/work and strict map-key ordering
// before a DOM can allocate or erase duplicate keys. No tags/bytes/floats.
class Cbor {
 public:
  Cbor(binary_detail::Budget& budget,const DescriptorLimits& limits) : budget_(budget),limits_(limits) {}
  void inspect(std::string_view bytes) {
    binary_detail::Reader reader{bytes,budget_};value(reader,0);binary_detail::require(reader.position==bytes.size());
  }
 private:
  static bool utf8(std::string_view text) noexcept {
    // CBOR TEXT allows U+0000; SQL type/name validation is a later factory step.
    std::size_t i=0;
    while(i<text.size()) {
      const auto first=static_cast<unsigned char>(text[i++]);if(first<0x80)continue;
      const auto count=first>=0xc2 && first<=0xdf?1U:first>=0xe0 && first<=0xef?2U:first>=0xf0 && first<=0xf4?3U:0U;
      if(!count || text.size()-i<count)return false;
      const auto second=static_cast<unsigned char>(text[i]);
      if((first==0xe0 && second<0xa0) || (first==0xed && second>=0xa0) ||
          (first==0xf0 && second<0x90) || (first==0xf4 && second>=0x90))return false;
      for(unsigned j=0;j<count;++j)if((static_cast<unsigned char>(text[i++])&0xc0U)!=0x80U)return false;
    }
    return true;
  }
  std::pair<unsigned,std::uint64_t> head(binary_detail::Reader& reader) {
    using binary_detail::require;
    require(items_<limits_.cbor_items,ImageFault::limit);++items_;budget_.charge(1);
    const auto first=reader.integer(1);const auto major=static_cast<unsigned>(first>>5),additional=static_cast<unsigned>(first&31);
    if(additional<24)return {major,additional};
    require(additional>=24 && additional<=27);const auto width=1U<<(additional-24);
    std::uint64_t result=0;for(unsigned i=0;i<width;++i)result=(result<<8)|reader.integer(1);
    constexpr std::array<std::uint64_t,4> minimum{24,256,65536,4294967296ULL};
    require(result>=minimum[additional-24]);return {major,result};
  }
  std::string_view text(binary_detail::Reader& reader,std::uint64_t count,bool key) {
    binary_detail::require(count<=budget_.limits.scalar_bytes && count<=SIZE_MAX,ImageFault::limit);
    const auto result=reader.take(static_cast<std::size_t>(count));
    // Factory binding images retain opaque hint/name bytes as string values.
    // Preserve them exactly; genuine SQL/catalog admission checks their use.
    if(key){budget_.charge(count);binary_detail::require(utf8(result),ImageFault::scalar);}return result;
  }
  void value(binary_detail::Reader& reader,std::size_t depth) {
    using binary_detail::require;
    require(depth<=limits_.cbor_depth,ImageFault::limit);const auto [major,count]=head(reader);
    switch(major) {
      case 0:return;
      case 1:require(count<=INT64_MAX,ImageFault::scalar);return;
      case 3:static_cast<void>(text(reader,count,false));return;
      case 4:
        require(count<=limits_.cbor_items-items_,ImageFault::limit);
        for(std::uint64_t i=0;i<count;++i)value(reader,depth+1);
        return;
      case 5:{
        require(count<=(limits_.cbor_items-items_)/2,ImageFault::limit);std::string_view previous;
        for(std::uint64_t i=0;i<count;++i) {
          const auto [kind,size]=head(reader);require(kind==3);const auto key=text(reader,size,true);
          if(i>0){budget_.charge(std::min(previous.size(),key.size()));require(previous<key);}previous=key;
          value(reader,depth+1);
        }return;
      }
      case 7:require(count==20 || count==21 || count==22);return;
      default:require(false);
    }
  }
  binary_detail::Budget& budget_;
  const DescriptorLimits& limits_;
  std::uint64_t items_=0;
};
} // namespace crown::recovery::sql_aggregate::detail
