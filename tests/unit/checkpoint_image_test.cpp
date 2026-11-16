#include "crown/recovery/image.hpp"
#include "crown/ir/digest.hpp"
#include "index_allocation.hpp"
#include <fstream>
#include <iostream>
#include <optional>
#include <stdexcept>
#include <tuple>

using namespace crown;
using namespace crown::recovery;
namespace {
void check(bool value,const char* message) {if(!value)throw std::runtime_error(message);}
std::string_view view(const EncodedImage& image) {return {image.bytes.data(),image.bytes.size()};}
template<class Action> void rejected(Action action,ImageFault fault) {
  try{action();}catch(const ImageFailure& error){check(error.fault()==fault,"wrong image rejection");return;}
  throw std::runtime_error("invalid image accepted");
}
void reseal(EncodedImage& image) {
  const auto size=image.bytes.size()-image_header_size;
  for(unsigned i=0;i<8;++i)image.bytes[12+i]=static_cast<char>(static_cast<std::uint64_t>(size)>>(8*i));
  const auto hash=sha256_fixed(view(image).substr(image_header_size));std::copy(hash.begin(),hash.end(),image.bytes.begin()+20);
}
void verify(const DecodedImage& image,const ImageManifest& manifest,const std::vector<Row>& expected) {
  check(image.manifest==manifest && image.tables.size()==2 && image.tables[0].size()==2 && image.tables[1].empty(),"image shape differs");
  for(std::size_t i=0;i<expected.size();++i)check(image.tables[0][i].values()==expected[i],"exact scalar roundtrip differs");
}
unsigned hex(char value) {
  if(value>='0' && value<='9')return static_cast<unsigned>(value-'0');
  check(value>='a' && value<='f',"invalid independent golden hex");return static_cast<unsigned>(value-'a'+10);
}
}
int main(int argc,char** argv) {
  try {
    check(argc==2,"golden fixture path missing");
    ImageManifest manifest;manifest.binding.physical_sha256.fill('a');manifest.binding.source_sha256.fill('b');
    manifest.binding.catalog_version=7;manifest.epoch=99;
    for(std::size_t i=0;i<manifest.binding.policy.size();++i)manifest.binding.policy[i]=i;
    const std::vector<Row> expected{{std::numeric_limits<std::int64_t>::min(),std::string("A\0\xff",3),true,
        Date::parse("1970-01-01"),Decimal::parse("-123.45")},{}};
    const auto account=resource::MemoryAccount::create(16*1024*1024);
    std::optional<EncodedImage> encoded;std::optional<DecodedImage> decoded;
    {
      ImageVector<storage::AccountedRow> native(image_allocator<storage::AccountedRow>(account));
      std::array<storage::RowView,2> rows;
      for(const auto& row:expected)native.push_back(storage::AccountedRow::copy_of(account,row,image_owner));
      for(std::size_t i=0;i<rows.size();++i)rows[i]=native[i].view();
      const std::array<ImageTableView,2> tables{{{rows},{{}}}};
      auto before=account.statistics();std::size_t encodes=0,decodes=0;
      {s04_alloc::Scope count;encoded=encode_image(account,manifest,tables);encodes=s04_alloc::calls;}
      check(encodes==1 && encodes==account.statistics().successful_allocations-before.successful_allocations,"encode escaped its account/preflight");
      std::ifstream input(argv[1]);std::string golden;input>>golden;
      check(golden.size()==encoded->bytes.size()*2,"golden image size differs");
      for(std::size_t i=0;i<encoded->bytes.size();++i)
        check(static_cast<unsigned char>(encoded->bytes[i])==hex(golden[2*i])*16+hex(golden[2*i+1]),"independent Python struct/hashlib image differs");
      before=account.statistics();
      {s04_alloc::Scope count;decoded=decode_image(account,view(*encoded),manifest.binding);decodes=s04_alloc::calls;}
      check(decodes>0 && decodes==account.statistics().successful_allocations-before.successful_allocations,"decode escaped its account");
      verify(*decoded,manifest,expected);
      for(const bool decoding:{false,true})for(std::size_t point=0;point<(decoding?decodes:encodes);++point) {
        const auto baseline=account.statistics().current;bool failed=false;
        {s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try {
          if(decoding){auto result=decode_image(account,view(*encoded),manifest.binding);}
          else {auto result=encode_image(account,manifest,tables);}
        }catch(const std::bad_alloc&){failed=true;}}
        check(failed && account.statistics().current==baseline,"image allocation fault retained partial storage");verify(*decoded,manifest,expected);
      }
      for(std::size_t size=0;size<encoded->bytes.size();++size) {
        s04_alloc::Scope deny(0);
        try{auto result=decode_image(account,view(*encoded).substr(0,size),manifest.binding);throw std::logic_error("truncated image accepted");}
        catch(const ImageFailure&){}
      }
      for(std::size_t byte=0;byte<encoded->bytes.size();++byte) {
        auto bad=*encoded;bad.bytes[byte]^=1;s04_alloc::Scope deny(0);
        try{auto result=decode_image(account,view(bad),manifest.binding);throw std::logic_error("flipped image accepted");}
        catch(const ImageFailure&){}
      }
      // Checksum-valid malformed payloads must also fail before allocating.
      for(const auto& [offset,value,fault]:std::array{
          std::tuple{std::size_t{228},2,ImageFault::version},std::tuple{std::size_t{230},1,ImageFault::binding},
          std::tuple{std::size_t{446},1,ImageFault::corrupt},std::tuple{std::size_t{470},99,ImageFault::scalar},
          std::tuple{std::size_t{492},2,ImageFault::scalar},std::tuple{std::size_t{500},static_cast<int>('+'),ImageFault::scalar},
          std::tuple{std::size_t{515},7,ImageFault::corrupt}}) {
        auto bad=*encoded;bad.bytes[offset]=static_cast<char>(value);reseal(bad);s04_alloc::Scope deny(0);
        rejected([&]{auto result=decode_image(account,view(bad),manifest.binding);},fault);
      }
      for(const auto offset:{std::size_t{438},std::size_t{454},std::size_t{462}}) {
        auto bad=*encoded;std::fill_n(bad.bytes.begin()+static_cast<std::ptrdiff_t>(offset),8,static_cast<char>(0xff));reseal(bad);
        s04_alloc::Scope deny(0);rejected([&]{auto result=decode_image(account,view(bad),manifest.binding);},ImageFault::limit);
      }
      {auto bad=*encoded;bad.bytes.push_back('x');reseal(bad);s04_alloc::Scope deny(0);
        rejected([&]{auto result=decode_image(account,view(bad),manifest.binding);},ImageFault::corrupt);}
      {auto bad=*encoded;std::fill_n(bad.bytes.begin()+494,4,static_cast<char>(0xff));bad.bytes[497]=0x7f;reseal(bad);
        s04_alloc::Scope deny(0);rejected([&]{auto result=decode_image(account,view(bad),manifest.binding);},ImageFault::scalar);}
      ImageLimits exact;exact.bytes=encoded->bytes.size();exact.work=encoded->statistics.work;
      check(encode_image(account,manifest,tables,exact).bytes==encoded->bytes,"exact encode boundary differs");
      {auto one=exact;--one.work;s04_alloc::Scope deny(0);rejected([&]{auto result=encode_image(account,manifest,tables,one);},ImageFault::work);}
      exact.work=decoded->statistics.work;verify(decode_image(account,view(*encoded),manifest.binding,exact),manifest,expected);
      {auto one=exact;--one.work;s04_alloc::Scope deny(0);rejected([&]{auto result=decode_image(account,view(*encoded),manifest.binding,one);},ImageFault::work);}
      --exact.bytes;
      {s04_alloc::Scope deny(0);rejected([&]{auto result=encode_image(account,manifest,tables,exact);},ImageFault::limit);
        rejected([&]{auto result=decode_image(account,view(*encoded),manifest.binding,exact);},ImageFault::limit);}
      for(const bool decoding:{false,true}) {
        std::uint64_t peak=0;
        {auto target=resource::MemoryAccount::create(16*1024*1024);
          if(decoding){auto result=decode_image(target,view(*encoded),manifest.binding);peak=target.statistics().peak_requested_bytes;}
          else {auto result=encode_image(target,manifest,tables);peak=target.statistics().peak_requested_bytes;}}
        {auto target=resource::MemoryAccount::create(peak);
          if(decoding){auto result=decode_image(target,view(*encoded),manifest.binding);verify(result,manifest,expected);}
          else {auto result=encode_image(target,manifest,tables);check(result.bytes==encoded->bytes,"exact query cap differs");}}
        {auto target=resource::MemoryAccount::create(peak-1);bool failed=false;
          try{if(decoding){auto result=decode_image(target,view(*encoded),manifest.binding);}else{auto result=encode_image(target,manifest,tables);}}
          catch(const resource::MemoryFailure& error){failed=error.fault()==resource::MemoryFault::limit;}
          check(failed && target.statistics().current.allocations==1,"one-under query cap retained image storage");}
      }
      // Extremal dates/integers/decimals, wide binary strings and zero limits.
      const Row rich{std::numeric_limits<std::int64_t>::max(),std::string(65536,'z')+std::string("\0\xff",2),false,
          Date::parse("0001-01-01"),Date::parse("9999-12-31"),Decimal::parse("-12345678901234567890123456789012345678"),
          Decimal::parse("0.00000000000000000000000000000000000001")};
      auto rich_row=storage::AccountedRow::copy_of(account,rich,image_owner);
      const std::array<storage::RowView,1> rich_values{rich_row.view()};
      const std::array<ImageTableView,1> rich_tables{{{rich_values}}};
      auto rich_blob=encode_image(account,manifest,rich_tables);auto rich_image=decode_image(account,view(rich_blob),manifest.binding);
      check(rich_image.tables[0][0].values()==rich,"extremal scalar or wide binary value differs");
      ImageLimits zero;zero.tables=0;zero.rows=0;zero.fields=0;zero.scalar_bytes=0;
      auto empty=encode_image(account,manifest,{},zero);auto empty_result=decode_image(account,view(empty),manifest.binding,zero);
      check(empty_result.tables.empty(),"zero-table limits rejected an empty image");
      for(unsigned dimension=0;dimension<4;++dimension) {
        ImageLimits low;
        if(dimension==0)low.tables=1;
        if(dimension==1)low.rows=1;
        if(dimension==2)low.fields=4;
        if(dimension==3)low.scalar_bytes=6;
        s04_alloc::Scope deny(0);
        rejected([&]{auto result=encode_image(account,manifest,tables,low);},ImageFault::limit);
        rejected([&]{auto result=decode_image(account,view(*encoded),manifest.binding,low);},ImageFault::limit);
      }
      std::cout<<"image codec: independent v1 bytes; all truncations/bit flips; checksum-valid scalar/count/version/binding errors; exact byte/work/query caps; "
          <<encodes<<" encode/"<<decodes<<" decode persistent allocation faults passed\n";
    }
    {s04_alloc::Scope deny(0);encoded.reset();}verify(*decoded,manifest,expected);
    {s04_alloc::Scope deny(0);decoded.reset();}
    check(account.statistics().current.allocations==1,"image lifetime retained payloads");account.check_invariants();
  }catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}
