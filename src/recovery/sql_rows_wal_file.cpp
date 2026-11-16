#include "sql_rows_file_detail.hpp"
#include "binary_detail.hpp"

namespace crown::recovery::sql_rows {
using binary_detail::require;
struct WalFile::Data {
  file_detail::Io io;
  frontend::SqlRowsProgram program;
  WalCursor cursor;
  ImageVector<char> scratch;
  Data(const resource::MemoryAccount& account,const Descriptor& descriptor,FileLimits limits)
      : io(limits,"CROWNRW2"),program(frontend::SqlRowsProgram::freeze(account,descriptor.program())),
        cursor(limits.scan),scratch(image_allocator<char>(account)) {}
};
WalFile::WalFile(resource::AccountedUnique<Data> value) noexcept : data_(std::move(value)) {}
WalFile::~WalFile()=default;
WalFile::WalFile(WalFile&&) noexcept=default;
WalFile::Data& WalFile::data() const {
  if(!data_)file_detail::fail(FileFault::state,FileStage::state,FileOutcome::unchanged);
  data_->io.ready();return *data_;
}
bool WalFile::requires_reopen() const noexcept { return !data_ || data_->io.fd<0 || data_->io.poisoned; }
WalFileState WalFile::state() const {
  const auto& d=data();return {d.cursor.state(),d.io.statistics(),d.io.torn};
}
WalFile WalFile::create(const resource::MemoryAccount& account,std::string_view path,
    const Descriptor& descriptor,const WalHeader& header,FileLimits limits) {
  const file_detail::Path parsed(path,limits);file_detail::binding(descriptor,header.binding);
  auto owner=resource::make_accounted_unique<Data>(account,resource::MemoryPurpose::recovery_log,account,descriptor,limits);
  auto frame=encode(account,owner->program,0,header,owner->io.record_limits());
  owner->io.consume(frame.info().statistics.work);
  owner->cursor.limits_.frame=owner->io.record_limits();
  const auto inspected=owner->cursor.feed(owner->program,frame.bytes());owner->io.consume(inspected.statistics.work);
  owner->io.create(parsed,frame.bytes());return WalFile(std::move(owner));
}
WalFile WalFile::open(const resource::MemoryAccount& account,std::string_view path,
    const Descriptor& descriptor,const WalHeader& expected,FileLimits limits) {
  return open_replay(account,path,descriptor,expected,limits,nullptr,nullptr);
}
WalFile WalFile::open_replay(const resource::MemoryAccount& account,std::string_view path,
    const Descriptor& descriptor,const WalHeader& expected,FileLimits limits,ReplayVisitor visitor,void* context) {
  const file_detail::Path parsed(path,limits);file_detail::binding(descriptor,expected.binding);
  auto owner=resource::make_accounted_unique<Data>(account,resource::MemoryPurpose::recovery_log,account,descriptor,limits);
  auto directory=owner->io.open(parsed);std::uint64_t offset=0;
  while(offset<static_cast<std::uint64_t>(owner->io.stamp.st_size)) {
    require(owner->cursor.state().records<limits.scan.records,ImageFault::limit);
    if(!owner->io.read_frame(offset,owner->scratch)) {
      const auto& state=owner->cursor.state();
      file_detail::tail(file_detail::view(owner->scratch),state.records,
          !state.pending && state.command_sequence<UINT64_MAX && state.physical_sequence<UINT64_MAX,
          state.pending.has_value(),false);
      break;
    }
    owner->cursor.limits_.frame=owner->io.record_limits();
    const auto info=owner->cursor.feed(owner->program,file_detail::view(owner->scratch));
    owner->io.consume(info.statistics.work);
    require(owner->cursor.state().header==expected,ImageFault::binding);
    if(visitor)visitor(file_detail::view(owner->scratch),info,owner->cursor.state(),context);
    offset+=owner->scratch.size();
  }
  owner->io.finish_open(directory);
  // Open scratch never retains the pending command; the receiving replay
  // visitor owns that one decoded head if its coordinator needs it.
  ImageVector<char>(image_allocator<char>(account)).swap(owner->scratch);
  return WalFile(std::move(owner));
}
void WalFile::append(const Frame& frame) & {
  auto& d=data();
  if(d.io.torn)file_detail::fail(FileFault::state,FileStage::state,FileOutcome::unchanged);
  // Private fixed-state staging preserves both cursor frontiers and its spent
  // grants. Frame.info() is not trusted: inspect the actual borrowed bytes under
  // this owner's genuine receiving schema, including moved-from input handles.
  WalCursor next(d.io.limits.scan);next.state_=d.cursor.state_;
  next.limits_.frame=d.io.record_limits();
  const auto info=next.feed(d.program,frame.bytes());d.io.consume(info.statistics.work);
  d.io.append(frame.bytes(),d.cursor.state().bytes);
  d.cursor=std::move(next);d.io.poisoned=false; // Fixed, nonallocating publication.
}
void WalFile::repair_tail() & { auto& d=data();d.io.repair(d.cursor.state().bytes); }
void WalFile::validate() & { data().io.validate(); }
void WalFile::close() & {
  if(!data_)file_detail::fail(FileFault::state,FileStage::state,FileOutcome::unchanged);
  data_->io.close();
}
} // namespace crown::recovery::sql_rows
