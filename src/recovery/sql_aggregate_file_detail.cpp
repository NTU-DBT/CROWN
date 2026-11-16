#include "sql_aggregate_file_detail.hpp"
#include "binary_detail.hpp"
#include "crown/ir/digest.hpp"
#ifdef CROWN_SQL_AGGREGATE_FILE_TESTING
#include "sql_aggregate_file_probe.hpp"
#endif
#include <algorithm>
#include <cerrno>
#include <fcntl.h>
#include <limits>
#include <sys/file.h>
#include <sys/random.h>
#include <unistd.h>

namespace crown::recovery::sql_aggregate {
#ifdef CROWN_SQL_AGGREGATE_FILE_TESTING
namespace testing {
namespace { thread_local FileHook hook=nullptr; thread_local void* context=nullptr; }
void set_file_hook(FileHook value,void* data) noexcept { hook=value;context=data; }
} // namespace testing
#endif
namespace file_detail {
using binary_detail::require;
namespace {
bool closing(FileStage stage) noexcept { return stage==FileStage::close_file || stage==FileStage::close_directory; }
bool same(const struct stat& a,const struct stat& b) noexcept {
  return a.st_dev==b.st_dev && a.st_ino==b.st_ino && a.st_size==b.st_size &&
      a.st_mtim.tv_sec==b.st_mtim.tv_sec && a.st_mtim.tv_nsec==b.st_mtim.tv_nsec &&
      a.st_ctim.tv_sec==b.st_ctim.tv_sec && a.st_ctim.tv_nsec==b.st_ctim.tv_nsec;
}
} // namespace
[[noreturn]] void fail(FileFault fault,FileStage stage,FileOutcome outcome,int error) {
  throw FileFailure(fault,stage,outcome,error);
}
void raw_close(int fd) noexcept {
  if(fd>=0) { const int saved=errno;static_cast<void>(::close(fd));errno=saved; }
}
Directory::Directory(Directory&& other) noexcept : fd(other.release()) {}
Directory::~Directory() { raw_close(fd); }
int Directory::release() noexcept { const int old=fd;fd=-1;return old; }
Path::Path(std::string_view path,const FileLimits& limits) {
  if(limits.path_bytes>=parent.size() || limits.chunk_bytes==0 || limits.operations==0 ||
      limits.chunk_bytes>static_cast<std::size_t>(std::numeric_limits<ssize_t>::max()) ||
      limits.scan.frame.record.bytes<frame_header_size+9 ||
      limits.scan.bytes>static_cast<std::uint64_t>(std::numeric_limits<off_t>::max()))
    fail(FileFault::limit,FileStage::path,FileOutcome::unchanged);
  if(path.empty() || path.size()>limits.path_bytes || path.find('\0')!=std::string_view::npos)
    fail(FileFault::path,FileStage::path,FileOutcome::unchanged);
  const auto slash=path.rfind('/');
  const auto base=slash==std::string_view::npos?path:path.substr(slash+1);
  const auto directory=slash==std::string_view::npos?std::string_view{"."}:slash==0?path.substr(0,1):path.substr(0,slash);
  if(base.empty() || base=="." || base=="..")fail(FileFault::path,FileStage::path,FileOutcome::unchanged);
  std::copy(base.begin(),base.end(),name.begin());std::copy(directory.begin(),directory.end(),parent.begin());
}
std::string_view view(const ImageVector<char>& bytes) noexcept { return {bytes.data(),bytes.size()}; }
void binding(const Descriptor& descriptor,const Binding& expected) {
  require(bool(descriptor) && expected.descriptor_sha256==descriptor.sha256(),ImageFault::binding);
}
std::uint64_t envelope(std::string_view bytes,const Limits& limits,std::string_view magic) {
  require(magic.size()==8,ImageFault::binding);
  require(bytes.size()<=frame_header_size);
  const auto have=std::min<std::size_t>(magic.size(),bytes.size());
  require(bytes.substr(0,have)==magic.substr(0,have));
  for(std::size_t i=8;i<std::min<std::size_t>(12,bytes.size());++i)
    require(static_cast<unsigned char>(bytes[i])==(i==8?1U:0U),ImageFault::version);
  std::uint64_t body=0;
  if(bytes.size()>=20) {
    for(unsigned i=0;i<8;++i)body|=std::uint64_t(static_cast<unsigned char>(bytes[12+i]))<<(8*i);
    require(body>=9);
    require(body<=limits.record.bytes-frame_header_size && body<=SIZE_MAX-frame_header_size,ImageFault::limit);
  }
  require(binary_detail::hex(bytes.substr(std::min<std::size_t>(20,bytes.size()))));
  if(bytes.size()>frame_prefix_size) {
    const auto digest=sha256_fixed(bytes.substr(0,frame_prefix_size));
    require(bytes.substr(frame_prefix_size)==std::string_view(digest.data(),bytes.size()-frame_prefix_size));
  }
  return frame_header_size+body;
}
void tail(std::string_view bytes,std::uint64_t ordinal,bool input,bool decision,bool group) {
  require(input || decision || group); // No next record is possible at a terminal frontier.
  if(bytes.size()<=frame_header_size)return;
  const auto kind=static_cast<Kind>(static_cast<unsigned char>(bytes[frame_header_size]));
  require((input && kind==Kind::input) || (decision && (kind==Kind::commit || kind==Kind::reject)) ||
      (group && kind==Kind::group_epoch));
  // A torn body cannot contradict the already visible record ordinal or the
  // mandatory fixed payload length. Remaining typed content needs full replay.
  for(std::size_t i=0;i<8 && frame_header_size+1+i<bytes.size();++i)
    require(static_cast<unsigned char>(bytes[frame_header_size+1+i])==static_cast<unsigned char>(ordinal>>(8*i)));
  std::uint64_t body=0;
  for(unsigned i=0;i<8;++i)body|=std::uint64_t(static_cast<unsigned char>(bytes[12+i]))<<(8*i);
  if(kind==Kind::commit)require(body==169);
  else if(kind==Kind::reject)require(body==98);
  else require(body>=(kind==Kind::input?27U:107U));
}
Hash chain(const Hash& previous,const char* checksum) {
  std::array<char,128> bytes{};
  std::copy(previous.begin(),previous.end(),bytes.begin());std::copy_n(checksum,64,bytes.begin()+64);
  return sha256_fixed({bytes.data(),bytes.size()});
}

Io::Io(FileLimits value,std::string_view frame_magic) : limits(value) {
  require(frame_magic.size()==magic.size(),ImageFault::binding);
  std::copy(frame_magic.begin(),frame_magic.end(),magic.begin());
}
Io::~Io() { raw_close(fd); }
void Io::ready() const { if(fd<0 || poisoned)fail(FileFault::state,FileStage::state,FileOutcome::unchanged); }
void Io::consume(std::uint64_t amount) {
  require(work<=limits.scan.work && amount<=limits.scan.work-work,ImageFault::work);work+=amount;
}
Limits Io::record_limits() const {
  require(work<=limits.scan.work,ImageFault::work);
  auto result=limits.scan.frame;result.record.work=std::min(result.record.work,limits.scan.work-work);return result;
}
FileStatistics Io::statistics() const noexcept { return {operations,work}; }
std::int64_t Io::call(FileStage stage,std::size_t requested,int descriptor,const char* name,int other_fd,
    const char* other_name,void* buffer,std::uint64_t offset,struct stat* status,bool emergency_cleanup) {
  if(operations==UINT64_MAX || (!emergency_cleanup && operations>=limits.operations)) {
    if(closing(stage))raw_close(descriptor);
    fail(FileFault::limit,stage,outcome);
  }
  ++operations;std::size_t count=requested;int before=0,after=0;
#ifdef CROWN_SQL_AGGREGATE_FILE_TESTING
  bool zero_entropy=false;
  if(testing::hook) {
    const auto choice=testing::hook({stage,false,operations,requested,0,0},testing::context);
    before=choice.error_before;after=choice.error_after;zero_entropy=choice.zero_entropy;
    count=std::min(count,choice.maximum_transfer);
  }
#endif
  // A hook cannot acquire an FD and hide it from its guard. Inject acquisition
  // failures before open; close always consumes its actual FD, even on EINTR.
  if(after!=0 && (stage==FileStage::open_directory || stage==FileStage::open_file || stage==FileStage::create_temporary)) {
    before=after;after=0;
  }
  if(stage==FileStage::write_data || stage==FileStage::truncate_tail || stage==FileStage::link_file)
    outcome=FileOutcome::unknown;
  std::int64_t result=-1;int error=0;
  if(before!=0 && !closing(stage))error=before;
  else {
    // State the private argument preconditions at the libc boundary. They also
    // keep optimized inlining from passing nullable irrelevant-stage arguments
    // to functions whose declarations require nonnull pointers.
    switch(stage) {
      case FileStage::open_directory:if(!name)fail(FileFault::state,stage,outcome);result=::open(name,O_RDONLY|O_DIRECTORY|O_CLOEXEC);break;
      case FileStage::entropy:
        if(!buffer)fail(FileFault::state,stage,outcome);
        result=::getrandom(buffer,count,GRND_NONBLOCK);
#ifdef CROWN_SQL_AGGREGATE_FILE_TESTING
        if(zero_entropy && result>0)std::fill_n(static_cast<unsigned char*>(buffer),static_cast<std::size_t>(result),static_cast<unsigned char>(0));
#endif
        break;
      case FileStage::create_temporary:if(!name)fail(FileFault::state,stage,outcome);result=::openat(descriptor,name,O_RDWR|O_CREAT|O_EXCL|O_CLOEXEC|O_NOFOLLOW,0600);break;
      case FileStage::open_file:if(!name)fail(FileFault::state,stage,outcome);result=::openat(descriptor,name,O_RDWR|O_CLOEXEC|O_NOFOLLOW|O_NONBLOCK);break;
      case FileStage::stat_file:if(!status)fail(FileFault::state,stage,outcome);result=::fstat(descriptor,status);break;
      case FileStage::lock_file:result=::flock(descriptor,LOCK_EX|LOCK_NB);break;
      case FileStage::read_data:if(!buffer)fail(FileFault::state,stage,outcome);result=::pread(descriptor,buffer,count,static_cast<off_t>(offset));break;
      case FileStage::write_data:if(!buffer)fail(FileFault::state,stage,outcome);result=::pwrite(descriptor,buffer,count,static_cast<off_t>(offset));break;
      case FileStage::sync_file:case FileStage::sync_directory:result=::fsync(descriptor);break;
      case FileStage::link_file:if(!name || !other_name)fail(FileFault::state,stage,outcome);result=::linkat(descriptor,name,other_fd,other_name,0);break;
      case FileStage::unlink_temporary:if(!name)fail(FileFault::state,stage,outcome);result=::unlinkat(descriptor,name,0);break;
      case FileStage::truncate_tail:result=::ftruncate(descriptor,static_cast<off_t>(offset));break;
      case FileStage::close_file:case FileStage::close_directory:result=::close(descriptor);break;
      case FileStage::path:case FileStage::state:fail(FileFault::state,stage,outcome);
    }
    if(result<0)error=errno;
    if(closing(stage) && before!=0) { result=-1;error=before; }
    else if(result>=0 && after!=0) { result=-1;error=after; }
  }
#ifdef CROWN_SQL_AGGREGATE_FILE_TESTING
  if(testing::hook)static_cast<void>(testing::hook({stage,true,operations,requested,result,error},testing::context));
#endif
  errno=error;return result;
}
std::int64_t Io::checked(FileStage stage,std::size_t count,int descriptor,const char* name,int other_fd,
    const char* other_name,void* buffer,std::uint64_t offset,struct stat* status) {
  for(;;) {
    const auto result=call(stage,count,descriptor,name,other_fd,other_name,buffer,offset,status);
    if(result>=0)return result;
    const int error=errno;
    if(error==EINTR && !closing(stage) && stage!=FileStage::link_file)continue;
    fail(stage==FileStage::lock_file && (error==EWOULDBLOCK || error==EAGAIN)?FileFault::busy:FileFault::io,stage,outcome,error);
  }
}
void Io::transfer(bool write,char* bytes,std::size_t size,std::uint64_t offset) {
  std::size_t done=0;
  while(done<size) {
    const auto stage=write?FileStage::write_data:FileStage::read_data;
    const auto count=checked(stage,std::min(limits.chunk_bytes,size-done),fd,nullptr,-1,nullptr,bytes+done,offset+done);
    if(count==0)fail(write?FileFault::io:FileFault::truncated,stage,outcome,write?EIO:0);
    done+=static_cast<std::size_t>(count);
  }
}
bool Io::cleanup(int directory,const char* name) noexcept {
  // Mandatory temporary cleanup has eight attempts outside the normal op cap;
  // failure is reported in fixed metadata, never by a nested retry framework.
  for(unsigned i=0;i<8;++i) {
    try { if(call(FileStage::unlink_temporary,0,directory,name,-1,nullptr,nullptr,0,nullptr,true)==0 || errno==ENOENT)return true; }
    catch(...) { return false; }
    if(errno!=EINTR)return false;
  }
  return false;
}
void Io::create(const Path& path,std::string_view header) {
  Directory directory;
  directory.fd=static_cast<int>(checked(FileStage::open_directory,0,-1,path.parent.data()));
  std::array<char,64> temporary{};bool exists=false,published=false;
  try {
    constexpr std::string_view prefix=".crown-r2-",digits="0123456789abcdef";
    for(unsigned attempt=0;attempt<16;++attempt) {
      std::array<unsigned char,16> random{};std::size_t have=0;
      while(have<random.size()) {
        const auto count=checked(FileStage::entropy,random.size()-have,-1,nullptr,-1,nullptr,random.data()+have);
        if(count==0)fail(FileFault::io,FileStage::entropy,outcome,EIO);
        have+=static_cast<std::size_t>(count);
      }
      std::copy(prefix.begin(),prefix.end(),temporary.begin());
      for(std::size_t i=0;i<random.size();++i) {
        temporary[prefix.size()+2*i]=digits[random[i]>>4];temporary[prefix.size()+2*i+1]=digits[random[i]&15];
      }
      if(std::string_view(temporary.data())==std::string_view(path.name.data()))continue;
      std::int64_t created=-1;
      do { created=call(FileStage::create_temporary,0,directory.fd,temporary.data()); } while(created<0 && errno==EINTR);
      if(created>=0) { fd=static_cast<int>(created);exists=true;break; }
      if(errno!=EEXIST)fail(FileFault::io,FileStage::create_temporary,outcome,errno);
    }
    if(!exists)fail(FileFault::io,FileStage::create_temporary,outcome,EEXIST);
    static_cast<void>(checked(FileStage::lock_file,0,fd));
    transfer(true,const_cast<char*>(header.data()),header.size(),0);
    static_cast<void>(checked(FileStage::sync_file,0,fd));
    // No-replace publication of a fully synced inode. An uncertain link is
    // never retried or rolled back; reopening decides what actually survived.
    static_cast<void>(checked(FileStage::link_file,0,directory.fd,temporary.data(),directory.fd,path.name.data()));published=true;
    static_cast<void>(checked(FileStage::unlink_temporary,0,directory.fd,temporary.data()));exists=false;
    static_cast<void>(checked(FileStage::sync_directory,0,directory.fd));outcome=FileOutcome::durable;
    refresh();
    if(stamp.st_size!=static_cast<off_t>(header.size()))fail(FileFault::changed,FileStage::stat_file,outcome);
    static_cast<void>(checked(FileStage::close_directory,0,directory.release()));
  } catch(const FileFailure& error) {
    const bool cleaned=!exists || cleanup(directory.fd,temporary.data());
    const auto observed=!published && error.stage()!=FileStage::link_file?FileOutcome::unchanged:error.outcome();
    throw FileFailure(error.fault(),error.stage(),observed,error.native_error(),!cleaned);
  }
}
Directory Io::open(const Path& path) {
  Directory directory;
  directory.fd=static_cast<int>(checked(FileStage::open_directory,0,-1,path.parent.data()));
  fd=static_cast<int>(checked(FileStage::open_file,0,directory.fd,path.name.data()));refresh();
  if(!S_ISREG(stamp.st_mode))fail(FileFault::not_regular,FileStage::stat_file,outcome);
  static_cast<void>(checked(FileStage::lock_file,0,fd));refresh();
  if(stamp.st_size<static_cast<off_t>(frame_header_size))fail(FileFault::truncated,FileStage::read_data,outcome);
  if(static_cast<std::uint64_t>(stamp.st_size)>limits.scan.bytes || static_cast<std::uint64_t>(stamp.st_size)>SIZE_MAX)
    fail(FileFault::limit,FileStage::stat_file,outcome);
  return directory;
}
void Io::finish_open(Directory& directory) {
  char extra=0;
  if(checked(FileStage::read_data,1,fd,nullptr,-1,nullptr,&extra,static_cast<std::uint64_t>(stamp.st_size))!=0)
    fail(FileFault::changed,FileStage::read_data,outcome);
  unchanged();static_cast<void>(checked(FileStage::sync_file,0,fd));
  static_cast<void>(checked(FileStage::sync_directory,0,directory.fd));outcome=FileOutcome::durable;
  unchanged();
  static_cast<void>(checked(FileStage::close_directory,0,directory.release()));
}
bool Io::read_frame(std::uint64_t offset,ImageVector<char>& scratch) {
  const auto available=static_cast<std::uint64_t>(stamp.st_size)-offset;
  std::array<char,frame_header_size> prefix{};
  const auto have=static_cast<std::size_t>(std::min<std::uint64_t>(prefix.size(),available));
  read(prefix.data(),have,offset);consume(have+(have>frame_prefix_size?frame_prefix_size:0));
  const auto total=envelope({prefix.data(),have},limits.scan.frame,{magic.data(),magic.size()});
  if(have<frame_header_size) {
    if(offset==0)fail(FileFault::truncated,FileStage::read_data,outcome);
    scratch.assign(prefix.begin(),prefix.begin()+static_cast<std::ptrdiff_t>(have));torn=true;return false;
  }
  require(total<=limits.scan.bytes-offset,ImageFault::limit);
  const auto actual=static_cast<std::size_t>(std::min(total,available));
  // An incomplete body's typed payload cannot be authenticated. Retain only
  // its kind/ordinal evidence; stat/EOF still cover the actual whole file size.
  const auto retained=actual<total?std::min(actual,frame_header_size+9):actual;
  scratch.resize(retained);std::copy(prefix.begin(),prefix.end(),scratch.begin());
  read(scratch.data()+frame_header_size,retained-frame_header_size,offset+frame_header_size);
  if(actual<total)consume(retained-frame_header_size);
  if(actual<total) {
    if(offset==0)fail(FileFault::truncated,FileStage::read_data,outcome);
    torn=true;return false;
  }
  return true;
}
void Io::unchanged() {
  struct stat current{};
  static_cast<void>(checked(FileStage::stat_file,0,fd,nullptr,-1,nullptr,nullptr,0,&current));
  if(!same(stamp,current))fail(FileFault::changed,FileStage::stat_file,outcome);
}
void Io::refresh() { static_cast<void>(checked(FileStage::stat_file,0,fd,nullptr,-1,nullptr,nullptr,0,&stamp)); }
void Io::validate() {
  // A receiving session rechecks both locked files after semantic replay and
  // before authorizing either tail repair. Even read uncertainty poisons it.
  ready();outcome=FileOutcome::unchanged;poisoned=true;unchanged();char extra=0;
  if(checked(FileStage::read_data,1,fd,nullptr,-1,nullptr,&extra,static_cast<std::uint64_t>(stamp.st_size))!=0)
    fail(FileFault::changed,FileStage::read_data,outcome);
  unchanged();poisoned=false;
}
void Io::read(char* bytes,std::size_t size,std::uint64_t offset) { transfer(false,bytes,size,offset); }
void Io::append(std::string_view bytes,std::uint64_t offset) {
  // Caller has completed validation, hashing and all growth. The latch precedes
  // even the first stamp check; every later failure forbids in-place retry.
  ready();require(offset==static_cast<std::uint64_t>(stamp.st_size),ImageFault::binding);
  outcome=FileOutcome::unchanged;poisoned=true;unchanged();
  transfer(true,const_cast<char*>(bytes.data()),bytes.size(),offset);
  static_cast<void>(checked(FileStage::sync_file,0,fd));outcome=FileOutcome::durable;
  refresh();
  if(stamp.st_size!=static_cast<off_t>(offset+bytes.size()))fail(FileFault::changed,FileStage::stat_file,outcome);
}
void Io::repair(std::uint64_t bytes) {
  ready();outcome=FileOutcome::unchanged;if(!torn)return;
  poisoned=true;unchanged();
  static_cast<void>(checked(FileStage::truncate_tail,0,fd,nullptr,-1,nullptr,nullptr,bytes));
  static_cast<void>(checked(FileStage::sync_file,0,fd));outcome=FileOutcome::durable;
  refresh();
  if(stamp.st_size!=static_cast<off_t>(bytes))fail(FileFault::changed,FileStage::stat_file,outcome);
  torn=false;poisoned=false;
}
void Io::close() {
  if(fd<0)fail(FileFault::state,FileStage::state,FileOutcome::unchanged);
  const int old=fd;fd=-1;static_cast<void>(checked(FileStage::close_file,0,old));
}
} // namespace file_detail
} // namespace crown::recovery::sql_aggregate
