#include "ranking_detail.hpp"
#include <algorithm>
#include <bit>

namespace crown::planner::ranking::detail {
unsigned UInt::bits() const noexcept {
  for(std::size_t i=limbs_.size();i>0;--i)if(limbs_[i-1])return static_cast<unsigned>((i-1)*32)+static_cast<unsigned>(std::bit_width(limbs_[i-1]));
  return 0;
}
bool UInt::zero() const noexcept {return bits()==0;}
void UInt::check(const Budget& b) const {if(bits()>b.limits.score_bits)throw Failure{Stop::bit_limit};}
UInt UInt::from(std::uint64_t value,Budget& b) {
  b.work(18);UInt out;out.limbs_[0]=static_cast<std::uint32_t>(value);out.limbs_[1]=static_cast<std::uint32_t>(value>>32);out.check(b);return out;
}
UInt UInt::add(const UInt& x,const UInt& y,Budget& b) {
  b.work(33);UInt out;std::uint64_t carry=0;
  for(std::size_t i=0;i<16;++i){const auto v=static_cast<std::uint64_t>(x.limbs_[i])+y.limbs_[i]+carry;out.limbs_[i]=static_cast<std::uint32_t>(v);carry=v>>32;}
  if(carry){throw Failure{Stop::bit_limit};}
  out.check(b);return out;
}
// Fixed 16x16 limb work with 32 inline scratch limbs; reject high limbs or
// the requested bit ceiling instead of truncating the exact product.
UInt UInt::multiply(const UInt& x,const UInt& y,Budget& b) {
  b.work(304);std::array<std::uint32_t,32> scratch{};
  for(std::size_t i=0;i<16;++i){std::uint64_t carry=0;
    for(std::size_t j=0;j<16;++j){const auto v=static_cast<std::uint64_t>(x.limbs_[i])*y.limbs_[j]+scratch[i+j]+carry;scratch[i+j]=static_cast<std::uint32_t>(v);carry=v>>32;}
    scratch[i+16]=static_cast<std::uint32_t>(carry);
  }
  for(std::size_t i=16;i<32;++i)if(scratch[i])throw Failure{Stop::bit_limit};
  UInt out;std::copy_n(scratch.begin(),16,out.limbs_.begin());out.check(b);return out;
}
int UInt::compare(const UInt& x,const UInt& y,Budget& b) {
  b.work(16);for(std::size_t i=16;i>0;--i){if(x.limbs_[i-1]<y.limbs_[i-1])return -1;if(x.limbs_[i-1]>y.limbs_[i-1])return 1;}return 0;
}
// At most 155 decimal digits for 512 bits. Render into bounded stack scratch
// first; a later budget/output-allocation failure cannot alter the source UInt.
UInt::Digits UInt::digits(Budget& b) const {
  b.work(16);Digits output;auto& digits=output.bytes;auto& count=output.count;auto value=limbs_;
  do{b.work(17);std::uint64_t remainder=0;for(std::size_t i=16;i>0;--i){const auto n=(remainder<<32)+value[i-1];value[i-1]=static_cast<std::uint32_t>(n/10);remainder=n%10;}
    digits[count++]=static_cast<char>('0'+remainder);
  }while(std::any_of(value.begin(),value.end(),[](auto v){return v!=0;}));
  b.bytes(static_cast<std::uint64_t>(count));b.work(static_cast<std::uint64_t>(count));
  return output;
}
std::string UInt::decimal(Budget& b) const {
  const auto value=digits(b);return std::string(value.bytes.rend()-static_cast<std::ptrdiff_t>(value.count),value.bytes.rend());
}
ScoreText UInt::decimal(Budget& b,const resource::MemoryAccount& account) const {
  const auto value=digits(b);return ScoreText(value.bytes.rend()-static_cast<std::ptrdiff_t>(value.count),value.bytes.rend(),score_allocator<char>(account));
}
} // namespace crown::planner::ranking::detail
