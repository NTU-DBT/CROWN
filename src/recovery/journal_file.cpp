#include "crown/recovery/journal_file.hpp"
#include "posix_compat.hpp"
#ifdef CROWN_RUNTIME_TESTING
#include "journal_file_probe.hpp"
#endif
#include <algorithm>
#include <cerrno>
#include <fcntl.h>
#include <limits>
#include <sys/file.h>
#include <unistd.h>

namespace crown::recovery::journal {
#ifdef CROWN_RUNTIME_TESTING
namespace testing {
namespace {thread_local FileHook hook=nullptr;thread_local void* context=nullptr;}
void set_file_hook(FileHook value,void* data) noexcept {hook=value;context=data;}
}
#endif
namespace {
[[noreturn]] void fail(FileFault fault,FileStage stage,FileOutcome outcome,int error=0) {
  throw FileFailure(fault,stage,outcome,error);
}
bool closing(FileStage stage) {return stage==FileStage::close_file || stage==FileStage::close_directory;}
void raw_close(int fd) noexcept {if(fd>=0){const int saved=errno;static_cast<void>(::close(fd));errno=saved;}}
struct Descriptor {
  int fd=-1;
  ~Descriptor(){raw_close(fd);}
  int release() noexcept {const int value=fd;fd=-1;return value;}
};
struct Path {
  std::array<char,4096> parent{},name{};
  Path(std::string_view path,const FileLimits& limits) {
    if(limits.path_bytes>=parent.size() || limits.chunk_bytes==0 || limits.operations==0 ||
        limits.chunk_bytes>static_cast<std::size_t>(std::numeric_limits<ssize_t>::max()) ||
        limits.scan.record.record.bytes<frame_header_size+9 || limits.scan.bytes>static_cast<std::uint64_t>(std::numeric_limits<off_t>::max()))
      fail(FileFault::limit,FileStage::path,FileOutcome::unchanged);
    if(path.empty() || path.size()>limits.path_bytes || path.find('\0')!=std::string_view::npos)
      fail(FileFault::path,FileStage::path,FileOutcome::unchanged);
    const auto slash=path.rfind('/');const auto base=slash==std::string_view::npos?path:path.substr(slash+1);
    const auto directory=slash==std::string_view::npos?std::string_view{"."}:slash==0?path.substr(0,1):path.substr(0,slash);
    if(base.empty() || base=="." || base=="..")fail(FileFault::path,FileStage::path,FileOutcome::unchanged);
    std::copy(base.begin(),base.end(),name.begin());std::copy(directory.begin(),directory.end(),parent.begin());
  }
};
bool same(const struct stat& a,const struct stat& b) {
  return posix::same_file_state(a,b);
}
std::string_view view(const ImageVector<char>& bytes) {return {bytes.data(),bytes.size()};}
} // namespace
File::File(const resource::MemoryAccount& account,const Header& header,FileLimits limits)
    :limits_(limits),cursor_(limits.scan,&header),scratch_(image_allocator<char>(account)),pending_(image_allocator<char>(account)) {}
File::~File(){raw_close(fd_);}
File::File(File&& other) noexcept
    :limits_(other.limits_),cursor_(std::move(other.cursor_)),scratch_(std::move(other.scratch_)),pending_(std::move(other.pending_)),
      fd_(other.fd_),stamp_(other.stamp_),operations_(other.operations_),outcome_(other.outcome_),poisoned_(other.poisoned_),torn_(other.torn_) {
  other.fd_=-1;other.poisoned_=true;
}
std::int64_t File::call(FileStage stage,std::size_t requested,int fd,const char* name,int other_fd,const char* other_name,
    void* buffer,std::uint64_t offset,struct stat* status,bool emergency_cleanup) {
  if(operations_==UINT64_MAX || (!emergency_cleanup && operations_>=limits_.operations)) {
    if(closing(stage))raw_close(fd);
    fail(FileFault::limit,stage,outcome_);
  }
  ++operations_;std::size_t transfer=requested;int before=0,after=0;
#ifdef CROWN_RUNTIME_TESTING
  bool zero_entropy=false;
  if(testing::hook) {
    const auto choice=testing::hook({stage,false,operations_,requested,0,0},testing::context);
    before=choice.error_before;after=choice.error_after;zero_entropy=choice.zero_entropy;
    transfer=std::min(transfer,choice.maximum_transfer);
  }
#endif
  if(after!=0 && (stage==FileStage::open_directory || stage==FileStage::open_file || stage==FileStage::create_temporary)){before=after;after=0;}
  // Even an interrupted/failed mutation can have a filesystem effect. Admission
  // of its syscall makes the outcome uncertain until the required sync succeeds.
  if(stage==FileStage::write_data || stage==FileStage::truncate_tail || stage==FileStage::link_file)outcome_=FileOutcome::unknown;
  std::int64_t result=-1;int error=0;
  if(before!=0 && !closing(stage))error=before;
  else {
    switch(stage) {
      case FileStage::open_directory:if(!name)fail(FileFault::state,stage,outcome_);result=::open(name,O_RDONLY|O_DIRECTORY|O_CLOEXEC);break;
      case FileStage::entropy:
        if(!buffer)fail(FileFault::state,stage,outcome_);
        result=posix::random_bytes(buffer,transfer);
#ifdef CROWN_RUNTIME_TESTING
        if(zero_entropy && result>0)std::fill_n(static_cast<unsigned char*>(buffer),static_cast<std::size_t>(result),static_cast<unsigned char>(0));
#endif
        break;
      case FileStage::create_temporary:if(!name)fail(FileFault::state,stage,outcome_);result=::openat(fd,name,O_RDWR|O_CREAT|O_EXCL|O_CLOEXEC|O_NOFOLLOW,0600);break;
      case FileStage::open_file:if(!name)fail(FileFault::state,stage,outcome_);result=::openat(fd,name,O_RDWR|O_CLOEXEC|O_NOFOLLOW|O_NONBLOCK);break;
      case FileStage::stat_file:if(!status)fail(FileFault::state,stage,outcome_);result=::fstat(fd,status);break;
      case FileStage::lock_file:result=::flock(fd,LOCK_EX|LOCK_NB);break;
      case FileStage::read_data:if(!buffer)fail(FileFault::state,stage,outcome_);result=::pread(fd,buffer,transfer,static_cast<off_t>(offset));break;
      case FileStage::write_data:if(!buffer)fail(FileFault::state,stage,outcome_);result=::pwrite(fd,buffer,transfer,static_cast<off_t>(offset));break;
      case FileStage::sync_file:case FileStage::sync_directory:result=::fsync(fd);break;
      case FileStage::link_file:if(!name || !other_name)fail(FileFault::state,stage,outcome_);result=::linkat(fd,name,other_fd,other_name,0);break;
      case FileStage::unlink_temporary:if(!name)fail(FileFault::state,stage,outcome_);result=::unlinkat(fd,name,0);break;
      case FileStage::truncate_tail:result=::ftruncate(fd,static_cast<off_t>(offset));break;
      case FileStage::close_file:case FileStage::close_directory:result=::close(fd);break;
      case FileStage::path:case FileStage::state:fail(FileFault::state,stage,outcome_);
    }
    if(result<0)error=errno;
    if(closing(stage) && before!=0){result=-1;error=before;}
    else if(result>=0 && after!=0){result=-1;error=after;}
  }
#ifdef CROWN_RUNTIME_TESTING
  if(testing::hook)static_cast<void>(testing::hook({stage,true,operations_,requested,result,error},testing::context));
#endif
  errno=error;return result;
}
std::int64_t File::checked(FileStage stage,std::size_t count,int fd,const char* name,int other_fd,const char* other_name,
    void* buffer,std::uint64_t offset,struct stat* status) {
  for(;;) {
    const auto result=call(stage,count,fd,name,other_fd,other_name,buffer,offset,status);
    if(result>=0)return result;
    const int error=errno;
    if(error==EINTR && !closing(stage) && stage!=FileStage::link_file)continue;
    fail(stage==FileStage::lock_file && (error==EWOULDBLOCK || error==EAGAIN)?FileFault::busy:FileFault::io,stage,outcome_,error);
  }
}
void File::transfer(bool write,char* data,std::size_t size,std::uint64_t offset) {
  std::size_t done=0;
  while(done<size) {
    const auto stage=write?FileStage::write_data:FileStage::read_data;
    const auto count=checked(stage,std::min(limits_.chunk_bytes,size-done),fd_,nullptr,-1,nullptr,data+done,offset+done);
    if(count==0)fail(write?FileFault::io:FileFault::truncated,stage,outcome_,write?EIO:0);
    done+=static_cast<std::size_t>(count);
  }
}
bool File::cleanup_temporary(int directory,const char* name) noexcept {
  for(unsigned i=0;i<8;++i) {
    try{if(call(FileStage::unlink_temporary,0,directory,name,-1,nullptr,nullptr,0,nullptr,true)==0 || errno==ENOENT)return true;}catch(...){return false;}
    if(errno!=EINTR)return false;
  }
  return false;
}
void File::ready() const {if(fd_<0 || poisoned_)fail(FileFault::state,FileStage::state,FileOutcome::unchanged);}
Scanned File::state() const & {
  ready();auto result=cursor_.state();result.torn_tail=torn_;
  if(result.pending)result.pending->frame=view(pending_);
  return result;
}
void File::refresh(){static_cast<void>(checked(FileStage::stat_file,0,fd_,nullptr,-1,nullptr,nullptr,0,&stamp_));}
void File::unchanged_file() {
  struct stat current{};static_cast<void>(checked(FileStage::stat_file,0,fd_,nullptr,-1,nullptr,nullptr,0,&current));
  if(!same(stamp_,current))fail(FileFault::changed,FileStage::stat_file,outcome_);
}
void File::retain_pending(std::uint64_t old_records) {
  const auto after=cursor_.state();
  if(after.pending && after.pending->ordinal==old_records)pending_.swap(scratch_);
  else if(!after.pending)pending_.clear();
}
File File::create(const resource::MemoryAccount& account,std::string_view path,const Header& header,FileLimits limits) {
  const Path parsed(path,limits);File result(account,header,limits);
  auto encoded=encode(account,0,PayloadView{header},limits.scan.record);result.scratch_=std::move(encoded.bytes);
  static_cast<void>(result.cursor_.feed(view(result.scratch_)));
  Descriptor directory;directory.fd=static_cast<int>(result.checked(FileStage::open_directory,0,-1,parsed.parent.data()));
  std::array<char,64> temporary{};bool exists=false,published=false;
  try {
    constexpr std::string_view prefix=".crown-journal-",hex="0123456789abcdef";
    for(unsigned attempt=0;attempt<16;++attempt) {
      std::array<unsigned char,16> random{};std::size_t have=0;
      while(have<random.size()) {
        const auto count=result.checked(FileStage::entropy,random.size()-have,-1,nullptr,-1,nullptr,random.data()+have);
        if(count==0)fail(FileFault::io,FileStage::entropy,result.outcome_,EIO);
        have+=static_cast<std::size_t>(count);
      }
      std::copy(prefix.begin(),prefix.end(),temporary.begin());
      for(std::size_t i=0;i<random.size();++i){temporary[prefix.size()+2*i]=hex[random[i]>>4];temporary[prefix.size()+2*i+1]=hex[random[i]&15];}
      if(std::string_view(temporary.data())==std::string_view(parsed.name.data()))continue;
      std::int64_t created=-1;
      do{created=result.call(FileStage::create_temporary,0,directory.fd,temporary.data());}while(created<0 && errno==EINTR);
      if(created>=0){result.fd_=static_cast<int>(created);exists=true;break;}
      if(errno!=EEXIST)fail(FileFault::io,FileStage::create_temporary,result.outcome_,errno);
    }
    if(!exists)fail(FileFault::io,FileStage::create_temporary,result.outcome_,EEXIST);
    static_cast<void>(result.checked(FileStage::lock_file,0,result.fd_));
    result.transfer(true,result.scratch_.data(),result.scratch_.size(),0);
    static_cast<void>(result.checked(FileStage::sync_file,0,result.fd_));
    // linkat installs a complete synced inode without overwriting any existing
    // destination. Interrupted publication is not retried or rolled back.
    static_cast<void>(result.checked(FileStage::link_file,0,directory.fd,temporary.data(),directory.fd,parsed.name.data()));published=true;
    static_cast<void>(result.checked(FileStage::unlink_temporary,0,directory.fd,temporary.data()));exists=false;
    static_cast<void>(result.checked(FileStage::sync_directory,0,directory.fd));result.outcome_=FileOutcome::durable;
    result.refresh();static_cast<void>(result.checked(FileStage::close_directory,0,directory.release()));
    return result;
  }catch(const FileFailure& error) {
    const bool cleaned=!exists || result.cleanup_temporary(directory.fd,temporary.data());
    const auto outcome=!published && error.stage()!=FileStage::link_file?FileOutcome::unchanged:error.outcome();
    throw FileFailure(error.fault(),error.stage(),outcome,error.native_error(),!cleaned);
  }catch(...) {if(exists)static_cast<void>(result.cleanup_temporary(directory.fd,temporary.data()));throw;}
}
File File::open(const resource::MemoryAccount& account,std::string_view path,const Header& expected,FileLimits limits) {
  return open_replay(account,path,expected,limits,nullptr,nullptr);
}
File File::open_replay(const resource::MemoryAccount& account,std::string_view path,const Header& expected,FileLimits limits,ReplayVisitor visitor,void* context) {
  // Visitor effects belong to the private receiving factory until the whole
  // prefix, EOF/stamp and file/directory sync have passed. No tail repair here.
  const Path parsed(path,limits);File result(account,expected,limits);Descriptor directory;
  directory.fd=static_cast<int>(result.checked(FileStage::open_directory,0,-1,parsed.parent.data()));
  result.fd_=static_cast<int>(result.checked(FileStage::open_file,0,directory.fd,parsed.name.data()));result.refresh();
  if(!S_ISREG(result.stamp_.st_mode))fail(FileFault::not_regular,FileStage::stat_file,result.outcome_);
  static_cast<void>(result.checked(FileStage::lock_file,0,result.fd_));result.refresh();
  if(result.stamp_.st_size<static_cast<off_t>(frame_header_size))fail(FileFault::truncated,FileStage::read_data,result.outcome_);
  const auto size=static_cast<std::uint64_t>(result.stamp_.st_size);
  if(size>limits.scan.bytes || size>SIZE_MAX)fail(FileFault::limit,FileStage::stat_file,result.outcome_);
  std::uint64_t offset=0;
  while(offset<size) {
    std::array<char,frame_header_size> prefix{};const auto prefix_size=static_cast<std::size_t>(std::min<std::uint64_t>(prefix.size(),size-offset));
    result.transfer(false,prefix.data(),prefix_size,offset);
    if(prefix_size<frame_header_size){static_cast<void>(result.cursor_.finish_tail({prefix.data(),prefix_size}));result.torn_=true;break;}
    std::uint64_t body_size=0;for(unsigned i=0;i<8;++i)body_size|=std::uint64_t(static_cast<unsigned char>(prefix[12+i]))<<(8*i);
    if(body_size<9)throw Failure(Fault::corrupt);
    if(body_size>limits.scan.record.record.bytes-frame_header_size || body_size>SIZE_MAX-frame_header_size)throw Failure(Fault::limit);
    const auto total=frame_header_size+body_size;const auto actual=static_cast<std::size_t>(std::min(total,size-offset));
    result.scratch_.resize(actual);std::copy(prefix.begin(),prefix.end(),result.scratch_.begin());
    result.transfer(false,result.scratch_.data()+frame_header_size,actual-frame_header_size,offset+frame_header_size);
    if(actual<total){static_cast<void>(result.cursor_.finish_tail(view(result.scratch_)));result.torn_=true;break;}
    const auto records=result.cursor_.state().records;const auto state=result.cursor_.feed(view(result.scratch_));
    if(visitor)visitor(view(result.scratch_),state,context);
    result.retain_pending(records);offset+=total;
  }
  char extra=0;if(result.checked(FileStage::read_data,1,result.fd_,nullptr,-1,nullptr,&extra,size)!=0)fail(FileFault::changed,FileStage::read_data,result.outcome_);
  result.unchanged_file();static_cast<void>(result.checked(FileStage::sync_file,0,result.fd_));
  static_cast<void>(result.checked(FileStage::sync_directory,0,directory.fd));result.outcome_=FileOutcome::durable;
  static_cast<void>(result.checked(FileStage::close_directory,0,directory.release()));return result;
}
void File::append(std::string_view frame) & {
  // Cursor validation is strong before publication. Once it advances, later
  // I/O failure poisons this owner: reopen the surviving prefix before retry.
  ready();outcome_=FileOutcome::unchanged;
  if(torn_)fail(FileFault::state,FileStage::state,outcome_);
  const auto before=cursor_.state();
  if(frame.size()>limits_.scan.record.record.bytes || frame.size()>limits_.scan.bytes-before.consumed)throw Failure(Fault::limit);
  scratch_.assign(frame.begin(),frame.end());
  static_cast<void>(cursor_.feed(view(scratch_)));poisoned_=true;
  unchanged_file();transfer(true,scratch_.data(),scratch_.size(),before.consumed);
  static_cast<void>(checked(FileStage::sync_file,0,fd_));outcome_=FileOutcome::durable;
  refresh();retain_pending(before.records);poisoned_=false;
}
void File::repair_tail() & {
  // Truncate only the validated incomplete suffix; complete pending inputs
  // and window commits remain part of recovery authority.
  ready();outcome_=FileOutcome::unchanged;
  if(!torn_)return;
  poisoned_=true;unchanged_file();static_cast<void>(checked(FileStage::truncate_tail,0,fd_,nullptr,-1,nullptr,nullptr,cursor_.state().consumed));
  static_cast<void>(checked(FileStage::sync_file,0,fd_));outcome_=FileOutcome::durable;refresh();torn_=false;poisoned_=false;
}
void File::close() & {
  if(fd_<0)fail(FileFault::state,FileStage::state,FileOutcome::unchanged);
  const int old=fd_;fd_=-1;static_cast<void>(checked(FileStage::close_file,0,old));
}
} // namespace crown::recovery::journal
