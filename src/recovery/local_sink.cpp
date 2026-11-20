#include "crown/recovery/local_sink.hpp"
#include "posix_compat.hpp"
#include "local_sink_codec.hpp"
#include "crown/ir/digest.hpp"
#ifdef CROWN_RUNTIME_TESTING
#include "local_sink_probe.hpp"
#endif
#include <algorithm>
#include <cerrno>
#include <fcntl.h>
#include <limits>
#include <sys/file.h>
#include <unistd.h>
namespace crown::recovery::sink {
#ifdef CROWN_RUNTIME_TESTING
namespace testing {
namespace {thread_local Hook hook=nullptr;thread_local void* context=nullptr;}
void set_hook(Hook value,void* data) noexcept {hook=value;context=data;}
}
#endif
namespace {
[[noreturn]] void fail(Fault fault,Stage stage,Outcome outcome,int error=0) {
  throw Failure(fault,stage,outcome,error);
}
bool closing(Stage stage) {return stage==Stage::close_file || stage==Stage::close_directory;}
void raw_close(int fd) noexcept {if(fd>=0){const int saved=errno;static_cast<void>(::close(fd));errno=saved;}}
struct Descriptor {
  int fd=-1;
  ~Descriptor(){raw_close(fd);}
  int release() noexcept {const int value=fd;fd=-1;return value;}
};
struct Path {
  std::array<char,4096> parent{},name{};
  Path(std::string_view path,const Limits& limits) {
    if(limits.path_bytes>=parent.size() || limits.chunk_bytes==0 || limits.operations==0 ||
        limits.chunk_bytes>static_cast<std::size_t>(std::numeric_limits<ssize_t>::max()) ||
        limits.record.bytes<frame_header_size+9 || limits.bytes>static_cast<std::uint64_t>(std::numeric_limits<off_t>::max()))
      fail(Fault::limit,Stage::path,Outcome::unchanged);
    if(path.empty() || path.size()>limits.path_bytes || path.find('\0')!=std::string_view::npos)
      fail(Fault::path,Stage::path,Outcome::unchanged);
    const auto slash=path.rfind('/');const auto base=slash==std::string_view::npos?path:path.substr(slash+1);
    const auto directory=slash==std::string_view::npos?std::string_view{"."}:slash==0?path.substr(0,1):path.substr(0,slash);
    if(base.empty() || base=="." || base=="..")fail(Fault::path,Stage::path,Outcome::unchanged);
    std::copy(base.begin(),base.end(),name.begin());std::copy(directory.begin(),directory.end(),parent.begin());
  }
};
bool same(const struct stat& a,const struct stat& b) {
  return posix::same_file_state(a,b);
}
std::string_view view(const ImageVector<char>& bytes) {return {bytes.data(),bytes.size()};}
std::array<char,64> chain(const std::array<char,64>& previous,const char* checksum) {
  std::array<char,128> bytes{};std::copy(previous.begin(),previous.end(),bytes.begin());std::copy_n(checksum,64,bytes.begin()+64);return sha256_fixed({bytes.data(),bytes.size()});
}
} // namespace
File::File(const resource::MemoryAccount& account,const Header& header,std::span<const ScalarType> schema,Limits limits)
    :account_(account),header_(header),limits_(limits),schema_(image_allocator<ScalarType>(account)),index_(image_allocator<Index>(account)),scratch_(image_allocator<char>(account)),other_(image_allocator<char>(account)) {
  if(schema.size()>limits.record.fields || schema.size()>(UINT64_MAX-1024)/4)throw ImageFailure(ImageFault::limit);
  consume(1024+4*schema.size());
  if(header.fields!=schema.size() || header.schema_sha256!=schema_sha256(account,schema))throw ImageFailure(ImageFault::binding);
  schema_.assign(schema.begin(),schema.end());
}
File::~File(){raw_close(fd_);}
File::File(File&& other) noexcept
    :account_(other.account_),header_(other.header_),limits_(other.limits_),schema_(std::move(other.schema_)),index_(std::move(other.index_)),scratch_(std::move(other.scratch_)),other_(std::move(other.other_)),fd_(other.fd_),stamp_(other.stamp_),operations_(other.operations_),work_(other.work_),bytes_(other.bytes_),budget_base_(other.budget_base_),header_bytes_(other.header_bytes_),header_sha256_(other.header_sha256_),outcome_(other.outcome_),poisoned_(other.poisoned_),torn_(other.torn_) {other.fd_=-1;other.poisoned_=true;}
void File::consume(std::uint64_t amount){if(amount>limits_.work-work_)throw ImageFailure(ImageFault::work);work_+=amount;}
ImageLimits File::record_limits() const {auto result=limits_.record;result.work=std::min(result.work,limits_.work-work_);return result;}
std::int64_t File::call(Stage stage,std::size_t requested,int fd,const char* name,int other_fd,const char* other_name,
    void* buffer,std::uint64_t offset,struct stat* status,bool emergency_cleanup) {
  if(operations_==UINT64_MAX || (!emergency_cleanup && operations_-budget_base_>=limits_.operations)) {
    if(closing(stage))raw_close(fd);
    fail(Fault::limit,stage,outcome_);
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
  if(after!=0 && (stage==Stage::open_directory || stage==Stage::open_file || stage==Stage::create_temporary)){before=after;after=0;}
  // Even an interrupted/failed mutation can have a filesystem effect. Admission
  // of its syscall makes the outcome uncertain until the required sync succeeds.
  if(stage==Stage::write_data || stage==Stage::truncate_tail || stage==Stage::link_file)outcome_=Outcome::unknown;
  std::int64_t result=-1;int error=0;
  if(before!=0 && !closing(stage))error=before;
  else {
    switch(stage) {
      case Stage::open_directory:if(!name)fail(Fault::state,stage,outcome_);result=::open(name,O_RDONLY|O_DIRECTORY|O_CLOEXEC);break;
      case Stage::entropy:
        if(!buffer)fail(Fault::state,stage,outcome_);
        result=posix::random_bytes(buffer,transfer);
#ifdef CROWN_RUNTIME_TESTING
        if(zero_entropy && result>0)std::fill_n(static_cast<unsigned char*>(buffer),static_cast<std::size_t>(result),static_cast<unsigned char>(0));
#endif
        break;
      case Stage::create_temporary:if(!name)fail(Fault::state,stage,outcome_);result=::openat(fd,name,O_RDWR|O_CREAT|O_EXCL|O_CLOEXEC|O_NOFOLLOW,0600);break;
      case Stage::open_file:if(!name)fail(Fault::state,stage,outcome_);result=::openat(fd,name,O_RDWR|O_CLOEXEC|O_NOFOLLOW|O_NONBLOCK);break;
      case Stage::stat_file:if(!status)fail(Fault::state,stage,outcome_);result=::fstat(fd,status);break;
      case Stage::lock_file:result=::flock(fd,LOCK_EX|LOCK_NB);break;
      case Stage::read_data:if(!buffer)fail(Fault::state,stage,outcome_);result=::pread(fd,buffer,transfer,static_cast<off_t>(offset));break;
      case Stage::write_data:if(!buffer)fail(Fault::state,stage,outcome_);result=::pwrite(fd,buffer,transfer,static_cast<off_t>(offset));break;
      case Stage::sync_file:case Stage::sync_directory:result=::fsync(fd);break;
      case Stage::link_file:if(!name || !other_name)fail(Fault::state,stage,outcome_);result=::linkat(fd,name,other_fd,other_name,0);break;
      case Stage::unlink_temporary:if(!name)fail(Fault::state,stage,outcome_);result=::unlinkat(fd,name,0);break;
      case Stage::truncate_tail:result=::ftruncate(fd,static_cast<off_t>(offset));break;
      case Stage::close_file:case Stage::close_directory:result=::close(fd);break;
      case Stage::path:case Stage::state:fail(Fault::state,stage,outcome_);
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
std::int64_t File::checked(Stage stage,std::size_t count,int fd,const char* name,int other_fd,const char* other_name,
    void* buffer,std::uint64_t offset,struct stat* status) {
  for(;;) {
    const auto result=call(stage,count,fd,name,other_fd,other_name,buffer,offset,status);
    if(result>=0)return result;
    const int error=errno;
    if(error==EINTR && !closing(stage) && stage!=Stage::link_file)continue;
    fail(stage==Stage::lock_file && (error==EWOULDBLOCK || error==EAGAIN)?Fault::busy:Fault::io,stage,outcome_,error);
  }
}
void File::transfer(bool write,char* data,std::size_t size,std::uint64_t offset) {
  std::size_t done=0;
  while(done<size) {
    const auto stage=write?Stage::write_data:Stage::read_data;
    const auto count=checked(stage,std::min(limits_.chunk_bytes,size-done),fd_,nullptr,-1,nullptr,data+done,offset+done);
    if(count==0)fail(write?Fault::io:Fault::truncated,stage,outcome_,write?EIO:0);
    done+=static_cast<std::size_t>(count);
  }
}
bool File::cleanup_temporary(int directory,const char* name) noexcept {
  for(unsigned i=0;i<8;++i) {
    try{if(call(Stage::unlink_temporary,0,directory,name,-1,nullptr,nullptr,0,nullptr,true)==0 || errno==ENOENT)return true;}catch(...){return false;}
    if(errno!=EINTR)return false;
  }
  return false;
}
File File::create(const resource::MemoryAccount& account,std::string_view path,const Header& header,std::span<const ScalarType> schema,Limits limits) {
  const Path parsed(path,limits);File result(account,header,schema,limits);
  auto encoded=detail::encode_header(account,result.header_,result.schema_,result.record_limits());result.consume(encoded.work);result.scratch_=std::move(encoded.bytes);result.bytes_=result.scratch_.size();
  if(64>limits.record.work-encoded.work)throw ImageFailure(ImageFault::work);
  result.consume(64);result.header_bytes_=result.bytes_;std::copy_n(result.scratch_.data()+frame_prefix_size,64,result.header_sha256_.begin());
  if(result.bytes_>limits.bytes)throw ImageFailure(ImageFault::limit);
  Descriptor directory;directory.fd=static_cast<int>(result.checked(Stage::open_directory,0,-1,parsed.parent.data()));
  std::array<char,64> temporary{};bool exists=false,published=false;
  try {
    constexpr std::string_view prefix=".crown-sink-",hex="0123456789abcdef";
    for(unsigned attempt=0;attempt<16;++attempt) {
      std::array<unsigned char,16> random{};std::size_t have=0;
      while(have<random.size()) {
        const auto count=result.checked(Stage::entropy,random.size()-have,-1,nullptr,-1,nullptr,random.data()+have);
        if(count==0)fail(Fault::io,Stage::entropy,result.outcome_,EIO);
        have+=static_cast<std::size_t>(count);
      }
      std::copy(prefix.begin(),prefix.end(),temporary.begin());
      for(std::size_t i=0;i<random.size();++i){temporary[prefix.size()+2*i]=hex[random[i]>>4];temporary[prefix.size()+2*i+1]=hex[random[i]&15];}
      if(std::string_view(temporary.data())==std::string_view(parsed.name.data()))continue;
      std::int64_t created=-1;
      do{created=result.call(Stage::create_temporary,0,directory.fd,temporary.data());}while(created<0 && errno==EINTR);
      if(created>=0){result.fd_=static_cast<int>(created);exists=true;break;}
      if(errno!=EEXIST)fail(Fault::io,Stage::create_temporary,result.outcome_,errno);
    }
    if(!exists)fail(Fault::io,Stage::create_temporary,result.outcome_,EEXIST);
    static_cast<void>(result.checked(Stage::lock_file,0,result.fd_));
    result.transfer(true,result.scratch_.data(),result.scratch_.size(),0);
    static_cast<void>(result.checked(Stage::sync_file,0,result.fd_));
    // linkat installs a complete synced inode without overwriting any existing
    // destination. Interrupted publication is not retried or rolled back.
    static_cast<void>(result.checked(Stage::link_file,0,directory.fd,temporary.data(),directory.fd,parsed.name.data()));published=true;
    static_cast<void>(result.checked(Stage::unlink_temporary,0,directory.fd,temporary.data()));exists=false;
    static_cast<void>(result.checked(Stage::sync_directory,0,directory.fd));result.outcome_=Outcome::durable;
    result.refresh();static_cast<void>(result.checked(Stage::close_directory,0,directory.release()));
    return result;
  }catch(const Failure& error) {
    const bool cleaned=!exists || result.cleanup_temporary(directory.fd,temporary.data());
    const auto outcome=!published && error.stage()!=Stage::link_file?Outcome::unchanged:error.outcome();
    throw Failure(error.fault(),error.stage(),outcome,error.native_error(),!cleaned);
  }catch(...) {if(exists)static_cast<void>(result.cleanup_temporary(directory.fd,temporary.data()));throw;}
}
void File::ready() const {if(fd_<0 || poisoned_)fail(Fault::state,Stage::state,Outcome::unchanged);}
State File::state() const {
  if(fd_<0)fail(Fault::state,Stage::state,Outcome::unchanged);
  const auto allocated=[](const auto& values){return values.get_allocator().allocation_usage(values.data(),values.capacity()).requested_bytes;};
  return {header_,static_cast<std::uint64_t>(index_.size()),index_.empty()?header_.first_generation:index_.back().generation,
      header_.base_sequence+index_.size(),bytes_,work_,operations_,allocated(schema_)+allocated(index_)+allocated(scratch_)+allocated(other_),torn_,poisoned_};
}
Prefix File::prefix(std::uint64_t sequence) const {
  ready();if(sequence<header_.base_sequence || sequence-header_.base_sequence>index_.size())throw ImageFailure(ImageFault::binding);
  if(sequence==header_.base_sequence)return {header_.first_generation,sequence,header_bytes_,header_sha256_};
  const auto& entry=index_[static_cast<std::size_t>(sequence-header_.base_sequence-1)];return {entry.generation,sequence,entry.offset+entry.size,entry.content_sha256};
}
Receipt File::receipt() const {ready();if(torn_)fail(Fault::state,Stage::state,outcome_);return Receipt(header_,prefix(header_.base_sequence+index_.size()));}
void File::refresh(){static_cast<void>(checked(Stage::stat_file,0,fd_,nullptr,-1,nullptr,nullptr,0,&stamp_));}
void File::unchanged_file() {
  struct stat current{};static_cast<void>(checked(Stage::stat_file,0,fd_,nullptr,-1,nullptr,nullptr,0,&current));
  if(!same(stamp_,current))fail(Fault::changed,Stage::stat_file,outcome_);
}
namespace {
void incomplete_prefix(std::string_view bytes,ImageLimits limits) {
  constexpr std::string_view signature="CROWNSK1";
  if(bytes.substr(0,std::min<std::size_t>(8,bytes.size()))!=signature.substr(0,std::min<std::size_t>(8,bytes.size())))throw ImageFailure(ImageFault::corrupt);
  for(std::size_t i=8;i<std::min<std::size_t>(12,bytes.size());++i)if(static_cast<unsigned char>(bytes[i])!=(i==8?1U:0U))throw ImageFailure(ImageFault::version);
  if(bytes.size()>=20){std::uint64_t size=0;for(unsigned i=0;i<8;++i)size|=std::uint64_t(static_cast<unsigned char>(bytes[12+i]))<<(8*i);if(size<9 || size>limits.bytes-frame_header_size)throw ImageFailure(ImageFault::limit);}
  for(std::size_t i=20;i<bytes.size();++i)if(!((bytes[i]>='0' && bytes[i]<='9') || (bytes[i]>='a' && bytes[i]<='f')))throw ImageFailure(ImageFault::corrupt);
  if(bytes.size()>frame_prefix_size) {
    const auto checksum=sha256_fixed(bytes.substr(0,frame_prefix_size));const auto have=bytes.size()-frame_prefix_size;
    if(bytes.substr(frame_prefix_size)!=std::string_view(checksum.data(),have))throw ImageFailure(ImageFault::corrupt);
  }
}
}
File File::open(const resource::MemoryAccount& account,std::string_view path,const Header& expected,std::span<const ScalarType> schema,Limits limits,HeaderMatch match) {
  // Open scans the whole admitted prefix and syncs its file/name before
  // returning. It can adopt a complete epoch previously reported as unknown.
  const auto binding=expected;const Path parsed(path,limits);File result(account,binding,schema,limits);Descriptor directory;
  directory.fd=static_cast<int>(result.checked(Stage::open_directory,0,-1,parsed.parent.data()));result.fd_=static_cast<int>(result.checked(Stage::open_file,0,directory.fd,parsed.name.data()));result.refresh();
  if(!S_ISREG(result.stamp_.st_mode))fail(Fault::not_regular,Stage::stat_file,result.outcome_);
  static_cast<void>(result.checked(Stage::lock_file,0,result.fd_));result.refresh();
  if(result.stamp_.st_size<static_cast<off_t>(frame_header_size))fail(Fault::truncated,Stage::read_data,result.outcome_);
  const auto size=static_cast<std::uint64_t>(result.stamp_.st_size);if(size>limits.bytes || size>SIZE_MAX)fail(Fault::limit,Stage::stat_file,result.outcome_);
  std::uint64_t offset=0;
  while(offset<size) {
    std::array<char,frame_header_size> prefix{};const auto have=static_cast<std::size_t>(std::min<std::uint64_t>(prefix.size(),size-offset));result.transfer(false,prefix.data(),have,offset);
    if(have<frame_header_size){
      if(offset==0)fail(Fault::truncated,Stage::read_data,result.outcome_);
      const auto work=have*(have>frame_prefix_size?2U:1U);if(work>result.record_limits().work)throw ImageFailure(ImageFault::work);
      result.consume(work);incomplete_prefix({prefix.data(),have},limits.record);result.torn_=true;break;
    }
    std::uint64_t prefix_work=0;const auto total=detail::frame_size({prefix.data(),prefix.size()},result.record_limits(),prefix_work);result.consume(prefix_work);
    const auto actual=static_cast<std::size_t>(std::min(total,size-offset));result.scratch_.resize(actual);std::copy(prefix.begin(),prefix.end(),result.scratch_.begin());
    result.transfer(false,result.scratch_.data()+frame_header_size,actual-frame_header_size,offset+frame_header_size);
    if(actual<total) {
      if(offset==0)fail(Fault::truncated,Stage::read_data,result.outcome_);
      if(actual>frame_header_size && result.scratch_[frame_header_size]!=1)throw ImageFailure(ImageFault::corrupt);
      result.torn_=true;break;
    }
    const auto info=detail::inspect(view(result.scratch_),result.schema_,result.record_limits());result.consume(info.work);
    if(offset==0){
      auto compared=info.binding;
      if(match==HeaderMatch::identity){compared.first_generation=binding.first_generation;compared.base_sequence=binding.base_sequence;}
      if(!info.header || compared!=binding)throw ImageFailure(ImageFault::binding);
      result.header_=info.binding;
      if(64>limits.record.work-info.work)throw ImageFailure(ImageFault::work);
      result.consume(64);result.header_bytes_=total;std::copy_n(prefix.data()+frame_prefix_size,64,result.header_sha256_.begin());
    }
    else {
      if(info.header || result.index_.size()>=limits.epochs || result.index_.size()>=UINT64_MAX-result.header_.base_sequence)throw ImageFailure(ImageFault::limit);
      const auto ordinal=static_cast<std::uint64_t>(result.index_.size())+1;const auto generation=result.index_.empty()?result.header_.first_generation:result.index_.back().generation;
      if(info.ordinal!=ordinal || info.sequence!=result.header_.base_sequence+ordinal || info.generation<generation)throw ImageFailure(ImageFault::binding);
      if(256>limits.record.work-info.work)throw ImageFailure(ImageFault::work);
      result.consume(256);const auto digest=chain(result.index_.empty()?result.header_sha256_:result.index_.back().content_sha256,prefix.data()+frame_prefix_size);
      result.index_.push_back({info.generation,offset,total,digest});
    }
    offset+=total;result.bytes_=offset;result.rebase();
  }
  char extra=0;if(result.checked(Stage::read_data,1,result.fd_,nullptr,-1,nullptr,&extra,size)!=0)fail(Fault::changed,Stage::read_data,result.outcome_);
  result.unchanged_file();static_cast<void>(result.checked(Stage::sync_file,0,result.fd_));static_cast<void>(result.checked(Stage::sync_directory,0,directory.fd));result.outcome_=Outcome::durable;
  static_cast<void>(result.checked(Stage::close_directory,0,directory.release()));return result;
}
bool File::append(std::uint64_t generation,std::uint64_t sequence,std::span<const RowView> rows) {
  return accept_epoch(generation,sequence,rows,false);
}
void File::verify_epoch(std::uint64_t generation,std::uint64_t sequence,std::span<const RowView> rows) {
  static_cast<void>(accept_epoch(generation,sequence,rows,true));
}
bool File::accept_epoch(std::uint64_t generation,std::uint64_t sequence,std::span<const RowView> rows,bool verify_only) {
  // Freeze canonical bytes and fund new index capacity before append I/O.
  // Existing epochs require full-byte comparison, not a digest-only retry.
  ready();outcome_=Outcome::unchanged;rebase();if(torn_ && !verify_only)fail(Fault::state,Stage::state,outcome_);
  if(sequence<=header_.base_sequence)throw ImageFailure(ImageFault::binding);
  const auto ordinal=sequence-header_.base_sequence;const bool duplicate=ordinal<=index_.size();
  if(verify_only && !duplicate)throw ImageFailure(ImageFault::binding);
  if(!duplicate && (ordinal!=index_.size()+1 || index_.size()>=limits_.epochs || generation<(index_.empty()?header_.first_generation:index_.back().generation)))throw ImageFailure(ImageFault::binding);
  auto encoded=detail::encode_epoch(account_,ordinal,generation,sequence,rows,schema_,record_limits());consume(encoded.work);
  if(duplicate) {
    const auto& entry=index_[static_cast<std::size_t>(ordinal-1)];if(entry.generation!=generation || entry.size!=encoded.bytes.size())throw ImageFailure(ImageFault::binding);
    other_.resize(static_cast<std::size_t>(entry.size));poisoned_=true;unchanged_file();transfer(false,other_.data(),other_.size(),entry.offset);unchanged_file();poisoned_=false;
    if(entry.size>UINT64_MAX/2)throw ImageFailure(ImageFault::work);
    consume(2*entry.size);
    if(other_!=encoded.bytes)throw ImageFailure(ImageFault::binding);
    return false;
  }
  if(encoded.bytes.size()>limits_.bytes-bytes_)throw ImageFailure(ImageFault::limit);
  if(256>limits_.record.work-encoded.work)throw ImageFailure(ImageFault::work);
  consume(256);const auto digest=chain(index_.empty()?header_sha256_:index_.back().content_sha256,encoded.bytes.data()+frame_prefix_size);
  if(index_.size()==index_.capacity()) {
    const auto maximum=static_cast<std::size_t>(std::min<std::uint64_t>(limits_.epochs,SIZE_MAX));
    const auto next=index_.capacity()>maximum/2?maximum:std::max<std::size_t>(1,2*index_.capacity());index_.reserve(next);
  }
  poisoned_=true;unchanged_file();transfer(true,encoded.bytes.data(),encoded.bytes.size(),bytes_);
  static_cast<void>(checked(Stage::sync_file,0,fd_));outcome_=Outcome::durable;refresh();index_.push_back({generation,bytes_,encoded.bytes.size(),digest});bytes_+=encoded.bytes.size();poisoned_=false;return true;
}
Epoch File::read_epoch(std::uint64_t sequence) {
  // The returned decoded rows own this account's payload independently of
  // File lifetime; scratch and codec work remain this owner's cumulative cost.
  ready();rebase();if(sequence<=header_.base_sequence || sequence-header_.base_sequence>index_.size())throw ImageFailure(ImageFault::binding);
  const auto entry=index_[static_cast<std::size_t>(sequence-header_.base_sequence-1)];scratch_.resize(static_cast<std::size_t>(entry.size));poisoned_=true;
  unchanged_file();transfer(false,scratch_.data(),scratch_.size(),entry.offset);unchanged_file();poisoned_=false;
  const auto info=detail::inspect(view(scratch_),schema_,record_limits());consume(info.work);
  if(info.header || info.generation!=entry.generation || info.sequence!=sequence || info.ordinal!=sequence-header_.base_sequence)throw ImageFailure(ImageFault::binding);
  if(info.work>UINT64_MAX/3)throw ImageFailure(ImageFault::work);
  const auto reserve=3*info.work;consume(reserve);
  auto limits=limits_.record;limits.work=std::min(limits.work,reserve);return detail::decode(account_,view(scratch_),schema_,limits);
}
void File::repair_tail() {
  ready();outcome_=Outcome::unchanged;rebase();if(!torn_)return;poisoned_=true;unchanged_file();
  static_cast<void>(checked(Stage::truncate_tail,0,fd_,nullptr,-1,nullptr,nullptr,bytes_));static_cast<void>(checked(Stage::sync_file,0,fd_));outcome_=Outcome::durable;refresh();torn_=false;poisoned_=false;
}
void File::close() {if(fd_<0)fail(Fault::state,Stage::state,Outcome::unchanged);rebase();const int old=fd_;fd_=-1;static_cast<void>(checked(Stage::close_file,0,old));}
} // namespace crown::recovery::sink
