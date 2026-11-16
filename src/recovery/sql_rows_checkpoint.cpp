#include "crown/recovery/sql_rows_checkpoint.hpp"
#include "crown/ir/digest.hpp"
#include "binary_detail.hpp"
#include "../frontend/sql_rows_value.hpp"
#include <algorithm>

namespace crown::recovery::sql_rows {
namespace detail {
struct CheckpointAccess {
  static Checkpoint make(ImageVector<char> bytes,InspectedCheckpoint info) {
    return Checkpoint(std::move(bytes),std::move(info));
  }
};
} // namespace detail
namespace {
using namespace binary_detail;
using Cell=runtime::sql_rows::Cell;
using Source=runtime::sql_rows::SourceSnapshot;
constexpr std::string_view magic="CROWNRC2";
void metadata_valid(const Descriptor& descriptor,const CheckpointMetadata& value) {
  require(bool(descriptor),ImageFault::binding);
  require(hex(value.binding.query_id) && value.binding.descriptor_sha256==descriptor.sha256() &&
      value.generation>0 && value.physical_sequence<=value.command_sequence,ImageFault::binding);
  require(hex(value.delivery.sink_id) && hex(value.delivery.content_sha256) &&
      value.delivery.sequence==value.physical_sequence && value.delivery.bytes>0,ImageFault::binding);
}
void reader_valid(const std::optional<ReaderPosition>& reader,std::uint64_t command) {
  if(reader)require(reader->records<=command && (reader->bytes>0 || reader->records==0));
}
auto columns(const Descriptor& descriptor,std::uint64_t table,const CheckpointLimits& limits) {
  const auto sources=descriptor.program().sources();
  require(sources.size()<=limits.image.tables,ImageFault::limit);
  require(table<sources.size() && sources[static_cast<std::size_t>(table)].table.value==table,ImageFault::binding);
  const auto result=sources[static_cast<std::size_t>(table)].columns;
  require(result.size()<=limits.image.fields,ImageFault::limit);return result;
}
void name_valid(Budget& budget,std::string_view name,const CheckpointLimits& limits) {
  require(!name.empty() && name.size()<=limits.source_bytes,ImageFault::limit);
  budget.charge(name.size());require(frontend::rows_detail::text_fits(name),ImageFault::scalar);
}
bool less(Budget& budget,std::string_view a,std::string_view b) {
  budget.charge(std::min(a.size(),b.size()));return a<b;
}
void cell_valid(Budget& budget,const Cell& cell,const frontend::SqlType& type) {
  if(cell && std::holds_alternative<std::string_view>(*cell))budget.charge(std::get<std::string_view>(*cell).size());
  require(frontend::rows_detail::fits(cell,type),ImageFault::scalar);
}
// Cold key scratch contains no ownership handles. Only index is used after its
// packed key buffer dies; encoding borrows the unchanged source rows throughout.
struct RowKey {std::size_t index,begin,size;};
struct Output : Writer {
  const Descriptor& descriptor;
  const CheckpointLimits& limits;
  std::uint64_t max_fields=0;
  void hash(std::span<const char> bytes) {require(hex(bytes),ImageFault::binding);put({bytes.data(),bytes.size()});}
  void row(const runtime::sql_rows::SourceEntry& entry) {
    budget.row();require(bool(entry.row));const auto types=columns(descriptor,entry.source.value,limits);
    const auto values=entry.row.view();require(values.size()==types.size(),ImageFault::binding);integer(values.size(),8);
    max_fields=std::max(max_fields,static_cast<std::uint64_t>(values.size()));
    for(std::size_t i=0;i<values.size();++i) {
      cell_valid(budget,values[i],types[i].type);integer(values[i].has_value(),1);if(values[i])scalar(*values[i]);
    }
  }
  void frame(const Source& source,const CheckpointMetadata& metadata,const io::AccountedInputProgress& progress,
      const std::optional<ReaderPosition>& reader,std::span<const RowKey> order) {
    metadata_valid(descriptor,metadata);require(source.sequence==metadata.physical_sequence &&
        progress.sequence==metadata.command_sequence,ImageFault::binding);reader_valid(reader,progress.sequence);
    require(order.size()==source.rows.size());
    require(source.sequence>0 || source.rows.empty());
    put(magic);integer(1,2);integer(0,2);integer(0,8);std::array<char,64> blank{};blank.fill('0');
    put({blank.data(),blank.size()});put({blank.data(),blank.size()});
    hash(metadata.binding.query_id);hash(metadata.binding.descriptor_sha256);integer(metadata.generation,8);
    integer(metadata.physical_sequence,8);integer(metadata.command_sequence,8);
    hash(metadata.delivery.sink_id);integer(metadata.delivery.sequence,8);integer(metadata.delivery.bytes,8);hash(metadata.delivery.content_sha256);
    integer(reader.has_value(),1);if(reader){integer(reader->bytes,8);integer(reader->records,8);}
    require(progress.source_positions.size()<=limits.sources,ImageFault::limit);integer(progress.source_positions.size(),8);
    std::string_view previous;bool first=true;
    for(const auto& [name,offset]:progress.source_positions) {
      const auto text=name.view();name_valid(budget,text,limits);if(!first)require(less(budget,previous,text));first=false;previous=text;
      integer(text.size(),8);put(text);integer(offset,8);
    }
    const auto tables=descriptor.program().sources().size();require(tables<=limits.image.tables,ImageFault::limit);
    integer(tables,8);require(source.rows.size()<=limits.image.rows,ImageFault::limit);integer(source.rows.size(),8);
    for(const auto& selected:order) {
      const auto& entry=source.rows[selected.index];integer(entry.source.value,8);row(entry);
      require(entry.weight>0 && entry.weight<=descriptor.native_binding().multiplicity_limit,ImageFault::scalar);integer(entry.weight,8);
    }
  }
};
// Inspection uses only transient scalar/string views. Materialization reuses one
// reserved cell vector, then gives each physical tuple its own receiving owner.
struct Input : Reader {
  const Descriptor& descriptor;
  const CheckpointLimits& limits;
  io::AccountedInputProgress* progress=nullptr;
  Source* source=nullptr;
  ImageVector<Cell>* cells=nullptr;
  const resource::MemoryAccount* receiving=nullptr;
  bool boolean() {const auto value=integer(1);require(value<=1);return value!=0;}
  template<std::size_t N> std::array<char,N> hash() {
    std::array<char,N> value{};const auto bytes=take(N);std::copy(bytes.begin(),bytes.end(),value.begin());require(hex(value),ImageFault::binding);return value;
  }
  std::string_view row(std::uint64_t table,InspectedCheckpoint& info) {
    budget.row();const auto begin=position;const auto types=columns(descriptor,table,limits);const auto count=size(limits.image.fields);
    require(count==types.size(),ImageFault::binding);info.max_fields=std::max(info.max_fields,static_cast<std::uint64_t>(count));
    if(cells)cells->clear();
    for(std::size_t i=0;i<count;++i) {
      Cell value;if(boolean())value=binary_detail::scalar(*this);
      if(!cells)cell_valid(budget,value,types[i].type); // Full prior inspection already checked the materializing pass.
      if(cells) {
        budget.charge(1);if(value && std::holds_alternative<std::string_view>(*value))budget.charge(std::get<std::string_view>(*value).size());
        cells->push_back(value); // Charges the later owning Tuple copy too.
      }
    }
    return input.substr(begin,position-begin);
  }
  InspectedCheckpoint body() {
    InspectedCheckpoint info{};auto& m=info.metadata;m.binding={hash<32>(),hash<64>()};
    m.generation=integer(8);m.physical_sequence=integer(8);m.command_sequence=integer(8);
    m.delivery.sink_id=hash<32>();m.delivery.sequence=integer(8);m.delivery.bytes=integer(8);m.delivery.content_sha256=hash<64>();
    metadata_valid(descriptor,m);
    if(boolean())info.reader=ReaderPosition{integer(8),integer(8)};
    reader_valid(info.reader,m.command_sequence);
    info.sources=size(limits.sources);std::string_view previous;
    for(std::uint64_t i=0;i<info.sources;++i) {
      const auto name=take(size(limits.source_bytes));name_valid(budget,name,limits);
      if(i)require(less(budget,previous,name));
      previous=name;const auto offset=integer(8);
      if(progress){auto node=progress->source_positions.prepare(name,offset);progress->source_positions.publish(node);}
    }
    const auto tables=integer(8);require(tables<=limits.image.tables,ImageFault::limit);
    require(tables==descriptor.program().sources().size(),ImageFault::binding);
    info.rows=size(limits.image.rows);require(m.physical_sequence>0 || info.rows==0);
    std::uint64_t previous_table=0;std::string_view previous_row;
    for(std::uint64_t i=0;i<info.rows;++i) {
      const auto table=integer(8);const auto key=row(table,info);
      if(i){budget.charge(8);require(table>previous_table || (table==previous_table && less(budget,previous_row,key)));}
      previous_table=table;previous_row=key;const auto weight=integer(8);
      require(weight>0 && weight<=descriptor.native_binding().multiplicity_limit,ImageFault::scalar);
      if(source)source->rows.push_back({TableId{static_cast<std::size_t>(table)},
          runtime::sql_rows::Tuple::copy_of(*receiving,*cells,resource::MemoryPurpose::recovery_log),weight});
    }
    require(position==input.size());if(progress)progress->sequence=m.command_sequence;return info;
  }
};
InspectedCheckpoint inspect(const Descriptor& descriptor,std::string_view bytes,const CheckpointLimits& limits,Budget& budget) {
  require(bool(descriptor),ImageFault::binding);require(bytes.size()<=limits.image.bytes,ImageFault::limit);
  Reader header{bytes,budget};require(header.take(8)==magic,ImageFault::version);
  require(header.integer(2)==1 && header.integer(2)==0,ImageFault::version);const auto size=header.integer(8);
  const auto body_hash=header.take(64),prefix_hash=header.take(64);budget.charge(frame_prefix_size);
  const auto prefix=sha256_fixed(bytes.substr(0,frame_prefix_size));require(prefix_hash==std::string_view(prefix.data(),prefix.size()));
  require(size==bytes.size()-frame_header_size);budget.charge(size);const auto body=sha256_fixed(bytes.substr(frame_header_size));
  require(body_hash==std::string_view(body.data(),body.size()));
  Input reader{{bytes,budget,frame_header_size},descriptor,limits};auto info=reader.body();budget.charge(bytes.size());
  info.sha256=sha256_fixed(bytes);info.statistics={bytes.size(),budget.used,budget.rows};return info;
}
ImageVector<RowKey> order_rows(const resource::MemoryAccount& account,const Descriptor& descriptor,const Source& source,
    const CheckpointLimits& limits,Budget& budget) {
  require(source.rows.size()<=limits.image.rows,ImageFault::limit);Output measure{{budget,nullptr},descriptor,limits};
  for(const auto& entry:source.rows)measure.row(entry);
  require(measure.size<=SIZE_MAX,ImageFault::limit);
  ImageVector<char> packed(image_allocator<char>(account));packed.reserve(static_cast<std::size_t>(measure.size));
  ImageVector<RowKey> order(image_allocator<RowKey>(account));order.reserve(source.rows.size());budget.rows=0;
  Output writer{{budget,&packed},descriptor,limits};
  for(std::size_t i=0;i<source.rows.size();++i){const auto begin=packed.size();writer.row(source.rows[i]);order.push_back({i,begin,packed.size()-begin});}
  const auto key=[&](const RowKey& entry){return std::string_view(packed.data()+entry.begin,entry.size);};
  const auto compare=[&](const RowKey& a,const RowKey& b) {
    budget.charge(8);const auto x=source.rows[a.index].source.value,y=source.rows[b.index].source.value;
    return x<y || (x==y && less(budget,key(a),key(b)));
  };
  std::sort(order.begin(),order.end(),compare);
  for(std::size_t i=1;i<order.size();++i)require(compare(order[i-1],order[i]));
  return order;
}
void source_binding(const Descriptor& descriptor,const Source& source,Budget& budget) {
  require(bool(descriptor) && bool(source.program) && bool(source.native_program),ImageFault::binding);
  budget.charge(std::min(source.program.binding_image().size(),descriptor.program().binding_image().size()));
  require(source.program.binding_image()==descriptor.program().binding_image() &&
      source.program.source_sha256()==descriptor.program().source_sha256() &&
      source.native_program.physical_sha256()==descriptor.native_program().physical_sha256() &&
      source.native_program.physical_source_sha256()==descriptor.native_program().physical_source_sha256() &&
      source.native_binding==descriptor.native_binding(),ImageFault::binding);
  budget.charge(64*5);
}
} // namespace

Checkpoint encode_checkpoint(const resource::MemoryAccount& account,const Descriptor& descriptor,const Source& source,
    const CheckpointMetadata& metadata,const io::AccountedInputProgress& progress,std::optional<ReaderPosition> reader,CheckpointLimits limits) {
  Budget budget{limits.image};source_binding(descriptor,source,budget);const auto order=order_rows(account,descriptor,source,limits,budget);
  budget.rows=0;Output measure{{budget,nullptr},descriptor,limits};measure.frame(source,metadata,progress,reader,order);
  require(measure.size<=SIZE_MAX,ImageFault::limit);ImageVector<char> bytes(image_allocator<char>(account));bytes.reserve(static_cast<std::size_t>(measure.size));
  budget.rows=0;Output writer{{budget,&bytes},descriptor,limits};writer.frame(source,metadata,progress,reader,order);
  const auto body_size=bytes.size()-frame_header_size;for(unsigned i=0;i<8;++i)bytes[12+i]=static_cast<char>(std::uint64_t(body_size)>>(8*i));
  budget.charge(body_size);const auto body=sha256_fixed({bytes.data()+frame_header_size,body_size});std::copy(body.begin(),body.end(),bytes.begin()+20);
  budget.charge(frame_prefix_size);const auto prefix=sha256_fixed({bytes.data(),frame_prefix_size});std::copy(prefix.begin(),prefix.end(),bytes.begin()+frame_prefix_size);
  budget.charge(bytes.size());InspectedCheckpoint info{metadata,reader,progress.source_positions.size(),
      source.rows.size(),writer.max_fields,sha256_fixed({bytes.data(),bytes.size()}),{bytes.size(),budget.used,budget.rows}};
  return detail::CheckpointAccess::make(std::move(bytes),std::move(info));
}
InspectedCheckpoint inspect_checkpoint(const Descriptor& descriptor,std::string_view bytes,CheckpointLimits limits) {
  Budget budget{limits.image};return inspect(descriptor,bytes,limits,budget);
}
RestoredCheckpoint restore_checkpoint_into(const resource::MemoryAccount& account,const Descriptor& descriptor,
    std::string_view bytes,const CheckpointMetadata& expected,const runtime::sql_rows::RebuildLimits& build,CheckpointLimits limits) {
  Budget budget{limits.image};auto info=inspect(descriptor,bytes,limits,budget);require(info.metadata==expected,ImageFault::binding);
  io::AccountedInputProgress progress(account);runtime::sql_rows::SourceSnapshot source(
      account,info.metadata.physical_sequence,descriptor.program(),descriptor.native_program(),descriptor.native_binding());
  source.rows.reserve(static_cast<std::size_t>(info.rows));ImageVector<Cell> cells(image_allocator<Cell>(account));cells.reserve(static_cast<std::size_t>(info.max_fields));
  budget.rows=0;Input input{{bytes,budget,frame_header_size},descriptor,limits,&progress,&source,&cells,&account};static_cast<void>(input.body());
  runtime::sql_rows::RebuildMetrics metrics;
  auto restored=runtime::SqlRowsRuntime::rebuild_into(account,source,descriptor.options(),build,&metrics);
  return {std::move(restored),std::move(progress),info.reader,info.metadata,{bytes.size(),budget.used,budget.rows},metrics};
}
} // namespace crown::recovery::sql_rows
