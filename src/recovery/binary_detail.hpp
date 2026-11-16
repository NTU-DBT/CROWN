#pragma once

#include "crown/recovery/image.hpp"
#include <algorithm>
#include <bit>
#include <chrono>
#include <limits>

namespace crown::recovery::binary_detail {
inline void require(bool condition,ImageFault fault=ImageFault::corrupt) {
  if(!condition)throw ImageFailure(fault);
}
inline bool hex(std::span<const char> text) {
  return std::all_of(text.begin(),text.end(),[](char c){return (c>='0' && c<='9') || (c>='a' && c<='f');});
}
struct Budget {
  ImageLimits limits;
  std::uint64_t used=0,rows=0;
  void charge(std::uint64_t count) {
    require(used<=limits.work && count<=limits.work-used,ImageFault::work);used+=count;
  }
  void row() {require(rows<limits.rows,ImageFault::limit);++rows;}
};
struct Writer {
  Budget& budget;
  ImageVector<char>* output;
  std::uint64_t size=0;
  void put(std::string_view text) {
    // Failed insertion leaves charged progress; discard this private writer.
    require(size<=budget.limits.bytes && text.size()<=budget.limits.bytes-size,ImageFault::limit);
    budget.charge(text.size());size+=text.size();
    if(output)output->insert(output->end(),text.begin(),text.end());
  }
  void integer(std::uint64_t value,unsigned width) {
    // Internal callers supply only widths 1, 2, 4 or 8.
    std::array<char,8> data{};
    for(unsigned i=0;i<width;++i)data[i]=static_cast<char>(value>>(8*i));
    put({data.data(),width});
  }
  void scalar(const storage::ScalarView& value) {
    integer(value.index(),1);
    std::visit([&](const auto& cell) {
      using T=std::remove_cvref_t<decltype(cell)>;
      if constexpr(std::is_same_v<T,std::int64_t>)integer(std::bit_cast<std::uint64_t>(cell),8);
      else if constexpr(std::is_same_v<T,std::string_view>) {
        require(cell.size()<=budget.limits.scalar_bytes,ImageFault::limit);integer(cell.size(),8);put(cell);
      } else if constexpr(std::is_same_v<T,bool>)integer(cell,1);
      else if constexpr(std::is_same_v<T,Date>)integer(std::bit_cast<std::uint32_t>(cell.epoch_days()),4);
      else {
        std::array<char,storage::InlineDecimal::text_capacity> data{};const auto size=cell.render(data);
        require(size<=budget.limits.scalar_bytes,ImageFault::limit);integer(size,1);put({data.data(),size});
      }
    },value);
  }
};
class Reader {
 public:
  // String results borrow these bytes; keep input unchanged through both passes.
  std::string_view input;
  Budget& budget;
  std::size_t position=0;
  std::string_view take(std::size_t count) {
    require(position<=input.size() && count<=input.size()-position);budget.charge(count);
    const auto value=input.substr(position,count);position+=count;return value;
  }
  std::uint64_t integer(unsigned width) {
    const auto bytes=take(width);std::uint64_t value=0;
    for(unsigned i=0;i<width;++i)value|=std::uint64_t(static_cast<unsigned char>(bytes[i]))<<(8*i);
    return value;
  }
  std::size_t size(std::uint64_t maximum) {
    const auto value=integer(8);require(value<=maximum && value<=SIZE_MAX,ImageFault::limit);
    return static_cast<std::size_t>(value);
  }
};
inline bool canonical_decimal(std::string_view text) {
  if(text.empty() || text.size()>storage::InlineDecimal::text_capacity)return false;
  const std::size_t start=text.front()=='-'?1:0;if(start==text.size())return false;
  const auto dot=text.find('.',start),end=dot==std::string_view::npos?text.size():dot;
  if(end==start || (end-start>1 && text[start]=='0'))return false;
  if(dot!=std::string_view::npos && (dot+1==text.size() || text.back()=='0' || text.size()-dot-1>38))return false;
  std::size_t significant=0;bool nonzero=false;
  for(std::size_t i=start;i<text.size();++i) {
    if(i==dot)continue;
    if(text[i]<'0' || text[i]>'9')return false;
    nonzero=nonzero || text[i]!='0';if(nonzero)++significant;
  }
  return significant<=38 && (nonzero || text=="0");
}
inline Date date(std::uint32_t bits) {
  const std::chrono::sys_days point{std::chrono::days{std::bit_cast<std::int32_t>(bits)}};
  const std::chrono::year_month_day value{point};const int year=static_cast<int>(value.year());
  require(value.ok() && year>=1 && year<=9999 && std::chrono::sys_days{value}==point,ImageFault::scalar);
  std::array<char,10> text{};auto number=static_cast<unsigned>(year);
  for(unsigned i=0;i<4;++i){text[3-i]=static_cast<char>('0'+number%10);number/=10;}
  text[4]='-';text[7]='-';number=static_cast<unsigned>(value.month());
  text[5]=static_cast<char>('0'+number/10);text[6]=static_cast<char>('0'+number%10);
  number=static_cast<unsigned>(value.day());text[8]=static_cast<char>('0'+number/10);text[9]=static_cast<char>('0'+number%10);
  return Date::parse({text.data(),text.size()});
}
inline storage::ScalarView scalar(Reader& reader) {
  switch(reader.integer(1)) {
    case 0:return std::bit_cast<std::int64_t>(reader.integer(8));
    case 1:return reader.take(reader.size(reader.budget.limits.scalar_bytes));
    case 2:{const auto value=reader.integer(1);require(value<=1,ImageFault::scalar);return value!=0;}
    case 3:return date(static_cast<std::uint32_t>(reader.integer(4)));
    case 4:{
      const auto size=reader.integer(1);require(size<=storage::InlineDecimal::text_capacity && size<=reader.budget.limits.scalar_bytes,ImageFault::limit);
      const auto text=reader.take(static_cast<std::size_t>(size));require(canonical_decimal(text),ImageFault::scalar);
      return storage::InlineDecimal::parse(text);
    }
    default:throw ImageFailure(ImageFault::scalar);
  }
}
} // namespace crown::recovery::binary_detail
