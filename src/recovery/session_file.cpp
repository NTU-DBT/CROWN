#include "crown/recovery/session_file.hpp"
#include "posix_compat.hpp"
#include "session_file_detail.hpp"
#include "binary_detail.hpp"
#include "../runtime/checkpoint_policy.hpp"
#ifdef CROWN_RUNTIME_TESTING
#include "checkpoint_file_probe.hpp"
#endif
#include <algorithm>
#include <cerrno>
#include <fcntl.h>
#include <limits>
#include <stdio.h>
#include <unistd.h>

namespace crown::recovery {
#ifdef CROWN_RUNTIME_TESTING
namespace testing {
namespace {thread_local FileHook current_hook=nullptr;thread_local void* hook_context=nullptr;}
void set_file_hook(FileHook hook,void* context) noexcept {current_hook=hook;hook_context=context;}
}
#endif
namespace {
[[noreturn]] void fail(FileFault fault,FileStage stage,PublicationState state,int error=0) {
  throw FileFailure(fault,stage,state,error);
}
bool closing(FileStage stage) {
  return stage==FileStage::close_file || stage==FileStage::close_directory || stage==FileStage::close_read;
}
struct Path {
  std::array<char,detail::file_path_capacity> directory{},name{};
  Path(std::string_view path,const CheckpointFileLimits& limits) {
    if(limits.path_bytes>=detail::file_path_capacity || limits.chunk_bytes==0 ||
        limits.chunk_bytes>static_cast<std::size_t>(std::numeric_limits<ssize_t>::max()) || limits.operations==0)
      fail(FileFault::limit,FileStage::path,PublicationState::not_published);
    if(path.empty() || path.size()>limits.path_bytes || path.find('\0')!=std::string_view::npos)
      fail(FileFault::path,FileStage::path,PublicationState::not_published);
    const auto slash=path.rfind('/');const auto parent=slash==std::string_view::npos?std::string_view{"."}:slash==0?path.substr(0,1):path.substr(0,slash);
    const auto base=slash==std::string_view::npos?path:path.substr(slash+1);
    if(base.empty() || base=="." || base=="..")fail(FileFault::path,FileStage::path,PublicationState::not_published);
    std::copy(parent.begin(),parent.end(),directory.begin());std::copy(base.begin(),base.end(),name.begin());
  }
};
std::int64_t checked(detail::FileIo& io,FileStage stage,std::size_t count,int fd,const char* name=nullptr,
    int other_fd=-1,const char* other_name=nullptr,void* buffer=nullptr,struct stat* status=nullptr,bool retry=true) {
  for(;;) {
    const auto value=io.call(stage,count,fd,name,other_fd,other_name,buffer,status);
    if(value>=0)return value;
    const int error=errno;if(error==EINTR && retry && !closing(stage))continue;
    fail(FileFault::io,stage,io.publication,error);
  }
}
void read_exact(detail::FileIo& io,int fd,char* output,std::size_t size) {
  std::size_t offset=0;
  while(offset<size) {
    const auto request=std::min(io.limits.chunk_bytes,size-offset);
    const auto value=checked(io,FileStage::read_data,request,fd,nullptr,-1,nullptr,output+offset);
    if(value==0)fail(FileFault::truncated,FileStage::read_data,io.publication);
    offset+=static_cast<std::size_t>(value);
  }
}
bool unlink_temporary(detail::FileIo& io,int directory,const char* name) noexcept {
  // Mandatory cleanup has a fixed retry bound outside the ordinary I/O budget.
  for(unsigned i=0;i<8;++i) {
    try {
      if(io.call(FileStage::unlink_temporary,0,directory,name)==0 || errno==ENOENT)return true;
    }catch(...){return false;}
    if(errno!=EINTR)return false;
  }
  return false;
}
bool same_file(const struct stat& a,const struct stat& b) {
  return posix::same_file_state(a,b);
}
} // namespace

namespace detail {
FileDescriptor::~FileDescriptor(){reset();}
void FileDescriptor::reset(int value) noexcept {
  const int previous=fd_;fd_=value;
  // Linux releases descriptors even when close reports EINTR/EIO. Retrying
  // could close an unrelated descriptor that has since reused the number.
  if(previous>=0){const int saved=errno;static_cast<void>(::close(previous));errno=saved;}
}
std::int64_t FileIo::call(FileStage stage,std::size_t requested,int fd,const char* name,
    int other_fd,const char* other_name,void* buffer,struct stat* status) {
  // Counts admitted attempts. Raw fd cleanup, including a quota-rejected close,
  // is separate; mandatory unlink cleanup can exceed the ordinary quota.
  if(operations==UINT64_MAX || (operations>=limits.operations && stage!=FileStage::unlink_temporary)) {
    if(closing(stage))static_cast<void>(::close(fd));
    fail(FileFault::limit,stage,publication);
  }
  ++operations;std::size_t transfer=requested;int before=0,after=0;
#ifdef CROWN_RUNTIME_TESTING
  bool zero_entropy=false;
  if(testing::current_hook) {
    const auto decision=testing::current_hook({stage,false,operations,requested,0,0},testing::hook_context);
    before=decision.error_before;after=decision.error_after;
    zero_entropy=decision.zero_entropy;
    if(stage==FileStage::read_data || stage==FileStage::write_data || stage==FileStage::entropy)transfer=std::min(transfer,decision.maximum_transfer);
  }
#endif
  // A failed open never hands an undisclosed descriptor to its caller. Model
  // injected open failures before resource creation; post-open crash hooks
  // still observe the successful syscall before the descriptor is adopted.
  if(after!=0 && (stage==FileStage::open_directory || stage==FileStage::open_read || stage==FileStage::create_temporary)) {
    before=after;after=0;
  }
  if(stage==FileStage::rename_file)publication=PublicationState::unknown;
  std::int64_t result=-1;int error=0;
  if(before!=0 && !closing(stage))error=before;
  else {
    switch(stage) {
      case FileStage::open_directory:result=::open(name,O_RDONLY|O_DIRECTORY|O_CLOEXEC);break;
      case FileStage::entropy:
        result=posix::random_bytes(buffer,transfer);
#ifdef CROWN_RUNTIME_TESTING
        if(zero_entropy && result>0)std::fill_n(static_cast<unsigned char*>(buffer),static_cast<std::size_t>(result),static_cast<unsigned char>(0));
#endif
        break;
      case FileStage::create_temporary:result=::openat(fd,name,O_WRONLY|O_CREAT|O_EXCL|O_CLOEXEC|O_NOFOLLOW,0600);break;
      case FileStage::write_data:result=::write(fd,buffer,transfer);break;
      case FileStage::sync_file:case FileStage::sync_directory:result=::fsync(fd);break;
      case FileStage::close_file:case FileStage::close_directory:case FileStage::close_read:result=::close(fd);break;
      case FileStage::rename_file:result=::renameat(fd,name,other_fd,other_name);break;
      case FileStage::open_read:result=::openat(fd,name,O_RDONLY|O_CLOEXEC|O_NOFOLLOW|O_NONBLOCK);break;
      case FileStage::stat_read:result=::fstat(fd,status);break;
      case FileStage::read_data:result=::read(fd,buffer,transfer);break;
      case FileStage::unlink_temporary:result=::unlinkat(fd,name,0);break;
      case FileStage::path:fail(FileFault::path,stage,publication);
    }
    if(result<0)error=errno;
    if(closing(stage) && before!=0){result=-1;error=before;}
    else if(result>=0 && after!=0){result=-1;error=after;}
  }
#ifdef CROWN_RUNTIME_TESTING
  if(testing::current_hook)static_cast<void>(testing::current_hook({stage,true,operations,requested,result,error},testing::hook_context));
#endif
  errno=error;return result;
}
SessionFileReader::SessionFileReader(std::string_view path,CheckpointFileLimits limits):io_{limits} {
  // This fixed preamble exposes the captured cap before receiving allocation.
  // Its checksum and native binding are validated only after the full read.
  const Path parsed(path,limits);
  directory_.reset(static_cast<int>(checked(io_,FileStage::open_directory,0,-1,parsed.directory.data())));
  file_.reset(static_cast<int>(checked(io_,FileStage::open_read,0,directory_.get(),parsed.name.data())));
  static_cast<void>(checked(io_,FileStage::stat_read,0,file_.get(),nullptr,-1,nullptr,nullptr,&original_));
  if(!S_ISREG(original_.st_mode))fail(FileFault::not_regular,FileStage::stat_read,io_.publication);
  if(original_.st_size<static_cast<off_t>(session_preamble_size))fail(FileFault::truncated,FileStage::read_data,io_.publication);
  const auto size=static_cast<std::uint64_t>(original_.st_size);
  if(size>limits.image.envelope.bytes || size>SIZE_MAX)fail(FileFault::limit,FileStage::stat_read,io_.publication);
  size_=static_cast<std::size_t>(size);read_exact(io_,file_.get(),prefix_.data(),prefix_.size());
  binary_detail::Budget budget{limits.image.envelope};binary_detail::Reader reader{{prefix_.data(),prefix_.size()},budget};
  binary_detail::require(reader.take(8)=="CROWNSI1");binary_detail::require(reader.integer(2)==1 && reader.integer(2)==0,ImageFault::version);
  binary_detail::require(reader.integer(8)==size-session_image_header_size);
  const auto checksum=reader.take(64);binary_detail::require(binary_detail::hex({checksum.data(),checksum.size()}));
  const auto state_version=reader.integer(4);
  binary_detail::require(state_version==runtime::SessionCheckpoint::legacy_version ||
      state_version==runtime::SessionCheckpoint::current_version,ImageFault::version);
  binary_detail::require(reader.integer(1)<=static_cast<std::uint64_t>(runtime::SessionState::stopped));
  binary_detail::require(reader.integer(1)<=static_cast<std::uint64_t>(runtime::SessionInputKind::typed_window));
  binary_detail::require(reader.integer(1)<=1 && reader.integer(1)<=1);static_cast<void>(reader.integer(8));
  std::array<std::uint64_t,26> policy{};for(auto& word:policy)word=reader.integer(8);memory_limit_=reader.integer(8);
  static_cast<void>(runtime::detail::checkpoint_options(policy,memory_limit_));
}
ImageVector<char> SessionFileReader::read(const resource::MemoryAccount& account) {
  // One-shot sequential read: after partial progress/fd release, reconstruct
  // the loader on failure. The result still needs full image/native validation.
  ImageVector<char> result(image_allocator<char>(account));result.resize(size_);std::copy(prefix_.begin(),prefix_.end(),result.begin());
  read_exact(io_,file_.get(),result.data()+prefix_.size(),result.size()-prefix_.size());
  char extra=0;const auto tail=checked(io_,FileStage::read_data,1,file_.get(),nullptr,-1,nullptr,&extra);
  if(tail!=0)fail(FileFault::changed,FileStage::read_data,io_.publication);
  struct stat current{};static_cast<void>(checked(io_,FileStage::stat_read,0,file_.get(),nullptr,-1,nullptr,nullptr,&current));
  if(!same_file(original_,current))fail(FileFault::changed,FileStage::stat_read,io_.publication);
  static_cast<void>(checked(io_,FileStage::close_read,0,file_.release(),nullptr,-1,nullptr,nullptr,nullptr,false));
  static_cast<void>(checked(io_,FileStage::close_directory,0,directory_.release(),nullptr,-1,nullptr,nullptr,nullptr,false));
  return result;
}
} // namespace detail

PublishedCheckpoint publish_session_image(std::string_view path,const SessionImage& image,
    const runtime::SessionCheckpointLimits& native,CheckpointFileLimits limits) {
  // Reinspect actual bytes; mutable SessionImage reports do not authorize them.
  const Path parsed(path,limits);const auto info=inspect_session_image({image.bytes.data(),image.bytes.size()},native,limits.image);
  detail::FileIo io{limits};detail::FileDescriptor directory,file;
  directory.reset(static_cast<int>(checked(io,FileStage::open_directory,0,-1,parsed.directory.data())));
  std::array<char,64> temporary{};bool exists=false;
  try {
    constexpr std::string_view prefix=".crown-checkpoint-";constexpr std::string_view hex="0123456789abcdef";
    for(unsigned attempt=0;attempt<16;++attempt) {
      std::array<unsigned char,16> random{};std::size_t have=0;
      while(have<random.size()) {
        const auto count=checked(io,FileStage::entropy,random.size()-have,-1,nullptr,-1,nullptr,random.data()+have);
        if(count==0){fail(FileFault::io,FileStage::entropy,io.publication,EIO);}
        have+=static_cast<std::size_t>(count);
      }
      std::copy(prefix.begin(),prefix.end(),temporary.begin());
      for(std::size_t i=0;i<random.size();++i){temporary[prefix.size()+2*i]=hex[random[i]>>4];temporary[prefix.size()+2*i+1]=hex[random[i]&15];}
      if(std::string_view(temporary.data())==std::string_view(parsed.name.data()))continue;
      std::int64_t created=-1;
      do {created=io.call(FileStage::create_temporary,0,directory.get(),temporary.data());}while(created<0 && errno==EINTR);
      if(created>=0){file.reset(static_cast<int>(created));exists=true;break;}
      if(errno!=EEXIST)fail(FileFault::io,FileStage::create_temporary,io.publication,errno);
    }
    if(!exists)fail(FileFault::io,FileStage::create_temporary,io.publication,EEXIST);
    std::size_t offset=0;
    while(offset<image.bytes.size()) {
      const auto requested=std::min(limits.chunk_bytes,image.bytes.size()-offset);
      const auto count=checked(io,FileStage::write_data,requested,file.get(),nullptr,-1,nullptr,const_cast<char*>(image.bytes.data()+offset));
      if(count==0){fail(FileFault::io,FileStage::write_data,io.publication,EIO);}
      offset+=static_cast<std::size_t>(count);
    }
    static_cast<void>(checked(io,FileStage::sync_file,0,file.get()));
    static_cast<void>(checked(io,FileStage::close_file,0,file.release(),nullptr,-1,nullptr,nullptr,nullptr,false));
    static_cast<void>(checked(io,FileStage::rename_file,0,directory.get(),temporary.data(),directory.get(),parsed.name.data(),nullptr,nullptr,false));
    // Rename is visible now; only directory sync establishes durable publication.
    exists=false;io.publication=PublicationState::published_unsynced;
    static_cast<void>(checked(io,FileStage::sync_directory,0,directory.get()));io.publication=PublicationState::durable;
    static_cast<void>(checked(io,FileStage::close_directory,0,directory.release(),nullptr,-1,nullptr,nullptr,nullptr,false));
    return {info.manifest,static_cast<std::uint64_t>(image.bytes.size()),io.operations,PublicationState::durable};
  }catch(const FileFailure& error) {
    file.reset();const bool cleanup_failed=exists && !unlink_temporary(io,directory.get(),temporary.data());
    throw FileFailure(error.fault(),error.stage(),error.publication(),error.native_error(),cleanup_failed);
  }
}
} // namespace crown::recovery
