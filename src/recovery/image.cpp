#include "crown/recovery/image.hpp"
#include "binary_detail.hpp"
#include "crown/ir/digest.hpp"
#include <algorithm>
#include <bit>
#include <chrono>
#include <limits>

namespace crown::recovery {
namespace {
using namespace binary_detail;
constexpr std::string_view magic="CROWNRI1";
void write(Writer& writer,const ImageManifest& manifest,std::span<const ImageTableView> tables) {
  writer.put(magic);writer.integer(1,2);writer.integer(0,2);writer.integer(0,8);
  for(unsigned i=0;i<64;++i)writer.integer(0,1);
  writer.put({manifest.binding.physical_sha256.data(),64});writer.put({manifest.binding.source_sha256.data(),64});
  writer.integer(manifest.binding.catalog_version,8);writer.integer(manifest.epoch,8);
  writer.integer(1,2); // exact-nonnull-v1
  for(const auto word:manifest.binding.policy)writer.integer(word,8);
  require(tables.size()<=writer.budget.limits.tables,ImageFault::limit);writer.integer(tables.size(),8);
  for(std::size_t i=0;i<tables.size();++i) {
    writer.integer(i,8);writer.integer(tables[i].rows.size(),8);
    for(const auto row:tables[i].rows) {
      writer.budget.row();require(row.size()<=writer.budget.limits.fields,ImageFault::limit);
      writer.integer(row.size(),8);for(const auto& value:row.cells())writer.scalar(value);
    }
  }
}
ImageManifest read(Reader& reader,const ImageBinding* expected,DecodedImage* result,const resource::MemoryAccount& account) {
  // This checks wire shape; runtime admission still checks schema and duplicates.
  // Materialization deep-copies borrowed scalar views into receiver-owned rows.
  ImageManifest manifest;
  auto text=reader.take(64);std::copy(text.begin(),text.end(),manifest.binding.physical_sha256.begin());
  text=reader.take(64);std::copy(text.begin(),text.end(),manifest.binding.source_sha256.begin());
  manifest.binding.catalog_version=reader.integer(8);manifest.epoch=reader.integer(8);
  require(reader.integer(2)==1,ImageFault::version);
  for(auto& word:manifest.binding.policy)word=reader.integer(8);
  if(expected)require(manifest.binding==*expected,ImageFault::binding);
  require(hex(manifest.binding.physical_sha256) && hex(manifest.binding.source_sha256) && manifest.binding.catalog_version>0,ImageFault::binding);
  const auto tables=reader.size(reader.budget.limits.tables);
  require(tables<=(reader.input.size()-reader.position)/16);
  if(result){result->manifest=manifest;result->tables.reserve(tables);}
  ImageVector<storage::ScalarView> cells;
  if(result)cells=ImageVector<storage::ScalarView>(image_allocator<storage::ScalarView>(account));
  for(std::size_t i=0;i<tables;++i) {
    require(reader.integer(8)==i);const auto rows=reader.size(reader.budget.limits.rows-reader.budget.rows);
    require(rows<=(reader.input.size()-reader.position)/8);
    if(result){result->tables.emplace_back(image_allocator<ImageRow>(account));result->tables.back().reserve(rows);}
    for(std::size_t row=0;row<rows;++row) {
      reader.budget.row();const auto fields=reader.size(reader.budget.limits.fields);
      require(fields<=reader.input.size()-reader.position);
      if(result){cells.clear();cells.reserve(fields);}
      for(std::size_t field=0;field<fields;++field) {
        const auto value=scalar(reader);if(result)cells.push_back(value);
      }
      if(result)result->tables.back().push_back({storage::AccountedRow::copy_of(account,storage::RowView::borrow(cells),image_owner)});
    }
  }
  require(reader.position==reader.input.size());return manifest;
}
void binding(const ImageBinding& value) {
  require(hex(value.physical_sha256) && hex(value.source_sha256) && value.catalog_version>0,ImageFault::binding);
}
InspectedImage inspect(std::string_view bytes,const ImageBinding* expected,ImageLimits limits) {
  require(bytes.size()<=limits.bytes,ImageFault::limit);Budget budget{limits};Reader header{bytes,budget};
  require(header.take(8)==magic);require(header.integer(2)==1 && header.integer(2)==0,ImageFault::version);
  const auto size=header.integer(8);const auto checksum=header.take(64);
  require(size==bytes.size()-image_header_size && hex({checksum.data(),checksum.size()}));
  budget.charge(size);const auto actual=sha256_fixed(bytes.substr(image_header_size));
  require(std::equal(actual.begin(),actual.end(),checksum.begin()));
  Reader preflight{bytes.substr(image_header_size),budget};const auto manifest=read(preflight,expected,nullptr,{});
  return {manifest,{static_cast<std::uint64_t>(bytes.size()),budget.used,budget.rows}};
}
} // namespace
EncodedImage encode_image(const resource::MemoryAccount& account,const ImageManifest& manifest,
    std::span<const ImageTableView> tables,ImageLimits limits) {
  binding(manifest.binding);Budget budget{limits};Writer preflight{budget,nullptr};write(preflight,manifest,tables);
  require(preflight.size<=SIZE_MAX,ImageFault::limit);
  // Admit all remaining deterministic byte work before the first allocation.
  const auto size=preflight.size;budget.charge(size);budget.charge(size-image_header_size);
  EncodedImage result{ImageVector<char>(image_allocator<char>(account)),{size,budget.used,budget.rows},manifest};
  result.bytes.reserve(static_cast<std::size_t>(size));
  Budget materialization{limits};Writer writer{materialization,&result.bytes};write(writer,manifest,tables);
  require(writer.size==size && materialization.rows==budget.rows);
  for(unsigned i=0;i<8;++i)result.bytes[12+i]=static_cast<char>((size-image_header_size)>>(8*i));
  const auto checksum=sha256_fixed({result.bytes.data()+image_header_size,result.bytes.size()-image_header_size});
  std::copy(checksum.begin(),checksum.end(),result.bytes.begin()+20);return result;
}
DecodedImage decode_image(const resource::MemoryAccount& account,std::string_view bytes,
    const ImageBinding& expected,ImageLimits limits) {
  binding(expected);const auto inspected=inspect(bytes,&expected,limits);
  Budget budget{limits};budget.used=inspected.statistics.work;budget.rows=inspected.statistics.rows;
  // Reserve the second payload visit before output growth. The caller keeps
  // the already validated bytes immutable throughout both passes.
  budget.charge(bytes.size()-image_header_size);
  DecodedImage result{inspected.manifest,ImageVector<DecodedImage::Rows>(image_allocator<DecodedImage::Rows>(account)),
      {static_cast<std::uint64_t>(bytes.size()),budget.used,budget.rows}};
  Budget materialization{limits};Reader reader{bytes.substr(image_header_size),materialization};
  static_cast<void>(read(reader,&expected,&result,account));return result;
}
InspectedImage inspect_image(std::string_view bytes,ImageLimits limits) {return inspect(bytes,nullptr,limits);}
} // namespace crown::recovery
