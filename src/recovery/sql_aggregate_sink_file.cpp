#include "sql_aggregate_file_detail.hpp"
#include "binary_detail.hpp"
#include <algorithm>

namespace crown::recovery::sql_aggregate {
using binary_detail::require;
struct SinkFile::Data {
  struct Index { SinkPrefix prefix;std::uint64_t offset,size; };
  file_detail::Io io;
  frontend::SqlAggregateProgram program;
  SinkHeader header;
  SinkPrefix baseline;
  ImageVector<Index> index;
  ImageVector<char> scratch;
  Data(const resource::MemoryAccount& account,const Descriptor& descriptor,const SinkHeader& value,FileLimits limits)
      : io(limits),program(frontend::SqlAggregateProgram::freeze(account,descriptor.program())),header(value),
        index(image_allocator<Index>(account)),scratch(image_allocator<char>(account)) {}
  [[nodiscard]] const SinkPrefix& latest() const noexcept { return index.empty()?baseline:index.back().prefix; }
  void header_frame(std::string_view bytes,const Inspected& info) {
    require(io.limits.scan.records>0,ImageFault::limit);
    require(info.kind==Kind::sink_header && info.ordinal==0 && std::get<SinkHeader>(info.payload)==header,ImageFault::binding);
    io.consume(64);baseline.physical_sequence=header.base_sequence;baseline.bytes=bytes.size();
    std::copy_n(bytes.data()+frame_prefix_size,64,baseline.content_sha256.begin());
  }
  // New epoch admission and index growth finish before any append I/O. A
  // header-only baseline contains no prior generation or command observation.
  [[nodiscard]] Index next(std::string_view bytes,const Inspected& info) {
    require(info.kind==Kind::group_epoch,ImageFault::binding);
    const auto& group=std::get<GroupInfo>(info.payload);const auto& previous=latest();
    require(previous.physical_sequence<UINT64_MAX && group.physical_sequence==previous.physical_sequence+1 &&
        info.ordinal==group.physical_sequence && group.input_sequence>previous.input_sequence &&
        group.generation>=previous.generation,ImageFault::binding);
    require(index.size()<io.limits.scan.records-1 && bytes.size()<=io.limits.scan.bytes-previous.bytes,ImageFault::limit);
    io.consume(256); // 128 copied bytes and one fixed 128-byte chained SHA pass.
    Index result{{group.generation,group.input_sequence,group.physical_sequence,previous.bytes+bytes.size(),
        file_detail::chain(previous.content_sha256,bytes.data()+frame_prefix_size)},previous.bytes,bytes.size()};
    if(index.size()==index.capacity()) {
      const auto maximum=static_cast<std::size_t>(std::min<std::uint64_t>(io.limits.scan.records-1,SIZE_MAX));
      const auto capacity=index.capacity()>maximum/2?maximum:std::max<std::size_t>(1,2*index.capacity());
      index.reserve(capacity);
    }
    return result;
  }
};
SinkFile::SinkFile(resource::AccountedUnique<Data> value) noexcept : data_(std::move(value)) {}
SinkFile::~SinkFile()=default;
SinkFile::SinkFile(SinkFile&&) noexcept=default;
SinkFile::Data& SinkFile::data() const {
  if(!data_)file_detail::fail(FileFault::state,FileStage::state,FileOutcome::unchanged);
  data_->io.ready();return *data_;
}
bool SinkFile::requires_reopen() const noexcept { return !data_ || data_->io.fd<0 || data_->io.poisoned; }
SinkFileState SinkFile::state() const {
  const auto& d=data();return {d.header,d.latest(),d.index.size()+1,d.io.statistics(),d.io.torn};
}
SinkPrefix SinkFile::prefix(std::uint64_t sequence) const {
  const auto& d=data();require(sequence>=d.header.base_sequence && sequence-d.header.base_sequence<=d.index.size(),ImageFault::binding);
  return sequence==d.header.base_sequence?d.baseline:d.index[static_cast<std::size_t>(sequence-d.header.base_sequence-1)].prefix;
}
SinkReceipt SinkFile::receipt() const {
  const auto& d=data();if(d.io.torn)file_detail::fail(FileFault::state,FileStage::state,FileOutcome::unchanged);
  return SinkReceipt(d.header,d.latest());
}
SinkFile SinkFile::create(const resource::MemoryAccount& account,std::string_view path,
    const Descriptor& descriptor,const SinkHeader& header,FileLimits limits) {
  const file_detail::Path parsed(path,limits);file_detail::binding(descriptor,header.binding);
  auto owner=resource::make_accounted_unique<Data>(account,resource::MemoryPurpose::recovery_log,account,descriptor,header,limits);
  auto frame=encode(account,owner->program,0,header,owner->io.record_limits());owner->io.consume(frame.info().statistics.work);
  require(frame.bytes().size()<=limits.scan.bytes,ImageFault::limit);owner->header_frame(frame.bytes(),frame.info());
  owner->io.create(parsed,frame.bytes());return SinkFile(std::move(owner));
}
SinkFile SinkFile::open(const resource::MemoryAccount& account,std::string_view path,
    const Descriptor& descriptor,const SinkHeader& expected,FileLimits limits) {
  const file_detail::Path parsed(path,limits);file_detail::binding(descriptor,expected.binding);
  auto owner=resource::make_accounted_unique<Data>(account,resource::MemoryPurpose::recovery_log,account,descriptor,expected,limits);
  auto directory=owner->io.open(parsed);std::uint64_t offset=0;
  while(offset<static_cast<std::uint64_t>(owner->io.stamp.st_size)) {
    require((offset==0?0:owner->index.size()+1)<limits.scan.records,ImageFault::limit);
    if(!owner->io.read_frame(offset,owner->scratch)) {
      require(owner->latest().physical_sequence<UINT64_MAX && owner->latest().input_sequence<UINT64_MAX);
      file_detail::tail(file_detail::view(owner->scratch),owner->latest().physical_sequence+1,false,false,true);break;
    }
    const auto info=inspect(owner->program,file_detail::view(owner->scratch),owner->io.record_limits());owner->io.consume(info.statistics.work);
    if(offset==0)owner->header_frame(file_detail::view(owner->scratch),info);
    else owner->index.push_back(owner->next(file_detail::view(owner->scratch),info));
    offset+=owner->scratch.size();
  }
  owner->io.finish_open(directory);
  ImageVector<char>(image_allocator<char>(account)).swap(owner->scratch);
  return SinkFile(std::move(owner));
}
bool SinkFile::append(const Frame& frame) & { return accept(frame,false); }
void SinkFile::verify(const Frame& frame) & { static_cast<void>(accept(frame,true)); }
bool SinkFile::accept(const Frame& frame,bool verify_only) {
  auto& d=data();
  if(d.io.torn && !verify_only)file_detail::fail(FileFault::state,FileStage::state,FileOutcome::unchanged);
  const auto bytes=frame.bytes();const auto info=inspect(d.program,bytes,d.io.record_limits());d.io.consume(info.statistics.work);
  require(info.kind==Kind::group_epoch,ImageFault::binding);
  const auto& group=std::get<GroupInfo>(info.payload);
  require(info.ordinal==group.physical_sequence && group.physical_sequence>d.header.base_sequence,ImageFault::binding);
  const auto ordinal=group.physical_sequence-d.header.base_sequence;
  if(ordinal<=d.index.size()) {
    const auto entry=d.index[static_cast<std::size_t>(ordinal-1)];
    require(entry.size==bytes.size() && entry.prefix.generation==group.generation &&
        entry.prefix.input_sequence==group.input_sequence,ImageFault::binding);
    require(entry.size<=UINT64_MAX/2,ImageFault::work);d.io.consume(2*entry.size);
    // Compare the whole real epoch in bounded chunks; no second owned output
    // frame or digest-only acceptance. All scratch/work is prepaid before I/O.
    d.scratch.resize(static_cast<std::size_t>(std::min<std::uint64_t>(entry.size,d.io.limits.chunk_bytes)));
    d.io.rebase();d.io.outcome=FileOutcome::unchanged;d.io.poisoned=true;d.io.unchanged();bool equal=true;
    std::size_t done=0;
    while(done<bytes.size()) {
      const auto size=std::min(d.scratch.size(),bytes.size()-done);
      d.io.read(d.scratch.data(),size,entry.offset+done);
      if(std::string_view(d.scratch.data(),size)!=bytes.substr(done,size))equal=false;
      done+=size;
    }
    d.io.unchanged();d.io.poisoned=false;require(equal,ImageFault::binding);return false;
  }
  require(!verify_only,ImageFault::binding);
  const auto entry=d.next(bytes,info);d.io.append(bytes,entry.offset);
  d.index.push_back(entry);d.io.poisoned=false;return true; // Reserved fixed entry only.
}
void SinkFile::repair_tail() & { auto& d=data();d.io.repair(d.latest().bytes); }
void SinkFile::validate() & { data().io.validate(); }
void SinkFile::close() & {
  if(!data_)file_detail::fail(FileFault::state,FileStage::state,FileOutcome::unchanged);
  data_->io.close();
}
} // namespace crown::recovery::sql_aggregate
