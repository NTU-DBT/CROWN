#include "generation_detail.hpp"
#include "posix_compat.hpp"
#include "crown/ir/digest.hpp"
#if defined(CROWN_RUNTIME_TESTING) || defined(CROWN_GENERATION_FILE_TESTING)
#include "generation_file_probe.hpp"
#endif
#include <algorithm>
#include <cerrno>
#include <charconv>
#include <fcntl.h>
#include <limits>
#include <sys/file.h>
#include <unistd.h>

namespace crown::recovery {
#if defined(CROWN_RUNTIME_TESTING) || defined(CROWN_GENERATION_FILE_TESTING)
namespace testing {
namespace {thread_local GenerationHook hook=nullptr;thread_local void* hook_context=nullptr;}
void set_generation_hook(GenerationHook value,void* context) noexcept {hook=value;hook_context=context;}
}
#endif
namespace {
[[noreturn]] void fail(GenerationFault fault,GenerationStage stage,GenerationOutcome outcome,int error=0) {
  throw GenerationFailure(fault,stage,outcome,error);
}
bool hex(std::string_view value) {
  return std::all_of(value.begin(),value.end(),[](char c){return (c>='0' && c<='9') || (c>='a' && c<='f');});
}
bool valid(const GenerationRoot& root) {
  return hex({root.query_id.data(),root.query_id.size()}) && hex({root.checkpoint_sha256.data(),root.checkpoint_sha256.size()}) &&
      root.first_generation>0 && root.generation>=root.first_generation &&
      (!root.plan_sha256 || hex({root.plan_sha256->data(),root.plan_sha256->size()})) && (!root.delivery ||
      (hex({root.delivery->sink_id.data(),root.delivery->sink_id.size()}) && hex({root.delivery->content_sha256.data(),64}) && root.delivery->sequence==root.physical_sequence && root.delivery->bytes>0));
}
bool same(const struct stat& a,const struct stat& b) {
  return posix::same_file_state(a,b);
}
template<std::size_t N> void put(std::array<char,N>& bytes,std::size_t& offset,std::uint64_t value,unsigned width) {
  for(unsigned i=0;i<width;++i)bytes[offset++]=static_cast<char>((value>>(8*i))&255);
}
std::uint64_t get(std::string_view bytes,std::size_t& offset,unsigned width) {
  std::uint64_t value=0;for(unsigned i=0;i<width;++i)value|=std::uint64_t(static_cast<unsigned char>(bytes[offset++]))<<(8*i);return value;
}
struct RootBytes {std::array<char,generation_root_plan_delivery_size> bytes{};std::size_t size=generation_root_size;};
RootBytes encode(const GenerationRoot& root) {
  if(!valid(root))fail(GenerationFault::corrupt,GenerationStage::state,GenerationOutcome::unchanged);
  RootBytes result;if(root.delivery)result.size=generation_root_delivery_size;
  if(root.plan_sha256)result.size=root.delivery?generation_root_plan_delivery_size:generation_root_plan_size;
  auto& bytes=result.bytes;std::size_t offset=0;
  const auto copy=[&](std::string_view value){std::copy(value.begin(),value.end(),bytes.begin()+static_cast<std::ptrdiff_t>(offset));offset+=value.size();};
  copy("CROWNGR1");put(bytes,offset,root.plan_sha256?3:root.delivery?2:1,2);
  put(bytes,offset,root.plan_sha256 && root.delivery?1:0,2);put(bytes,offset,result.size-84,8);
  copy({root.query_id.data(),root.query_id.size()});put(bytes,offset,root.generation,8);put(bytes,offset,root.first_generation,8);
  copy({root.checkpoint_sha256.data(),root.checkpoint_sha256.size()});put(bytes,offset,root.physical_sequence,8);put(bytes,offset,root.command_sequence,8);
  if(root.delivery){const auto& anchor=*root.delivery;copy({anchor.sink_id.data(),anchor.sink_id.size()});put(bytes,offset,anchor.sequence,8);put(bytes,offset,anchor.bytes,8);copy({anchor.content_sha256.data(),64});}
  if(root.plan_sha256)copy({root.plan_sha256->data(),root.plan_sha256->size()});
  const auto digest=sha256_fixed({bytes.data(),offset});copy({digest.data(),digest.size()});return result;
}
std::array<char,16> generation_hex(std::uint64_t generation) {
  std::array<char,16> result{},digits{};result.fill('0');const auto converted=std::to_chars(digits.data(),digits.data()+digits.size(),generation,16);
  const auto count=static_cast<std::size_t>(converted.ptr-digits.data());std::copy_n(digits.begin(),count,result.end()-static_cast<std::ptrdiff_t>(count));return result;
}
} // namespace
GenerationRoot inspect_generation_root(std::string_view bytes) {
  if(bytes.size()!=generation_root_size && bytes.size()!=generation_root_delivery_size &&
      bytes.size()!=generation_root_plan_size && bytes.size()!=generation_root_plan_delivery_size)
    fail(bytes.size()<generation_root_size?GenerationFault::truncated:GenerationFault::corrupt,GenerationStage::read_data,GenerationOutcome::unchanged);
  const auto digest=sha256_fixed(bytes.substr(0,bytes.size()-64));
  if(bytes.substr(0,8)!="CROWNGR1" || bytes.substr(bytes.size()-64)!=std::string_view(digest.data(),digest.size()))
    fail(GenerationFault::corrupt,GenerationStage::read_data,GenerationOutcome::unchanged);
  std::size_t offset=8;
  const auto version=get(bytes,offset,2),flags=get(bytes,offset,2),body=get(bytes,offset,8);
  if(!((version==1 && flags==0 && body==128 && bytes.size()==generation_root_size) ||
      (version==2 && flags==0 && body==240 && bytes.size()==generation_root_delivery_size) ||
      (version==3 && ((flags==0 && body==192 && bytes.size()==generation_root_plan_size) ||
          (flags==1 && body==304 && bytes.size()==generation_root_plan_delivery_size)))))
    fail(GenerationFault::corrupt,GenerationStage::read_data,GenerationOutcome::unchanged);
  GenerationRoot result;std::copy_n(bytes.begin()+static_cast<std::ptrdiff_t>(offset),32,result.query_id.begin());offset+=32;
  result.generation=get(bytes,offset,8);result.first_generation=get(bytes,offset,8);
  std::copy_n(bytes.begin()+static_cast<std::ptrdiff_t>(offset),64,result.checkpoint_sha256.begin());offset+=64;
  result.physical_sequence=get(bytes,offset,8);result.command_sequence=get(bytes,offset,8);
  if(version==2 || (version==3 && flags==1)){GenerationDeliveryAnchor anchor;std::copy_n(bytes.begin()+static_cast<std::ptrdiff_t>(offset),32,anchor.sink_id.begin());offset+=32;anchor.sequence=get(bytes,offset,8);anchor.bytes=get(bytes,offset,8);std::copy_n(bytes.begin()+static_cast<std::ptrdiff_t>(offset),64,anchor.content_sha256.begin());offset+=64;result.delivery=anchor;}
  if(version==3){std::array<char,64> hash{};std::copy_n(bytes.begin()+static_cast<std::ptrdiff_t>(offset),64,hash.begin());offset+=64;result.plan_sha256=hash;}
  if(offset!=bytes.size()-64)fail(GenerationFault::corrupt,GenerationStage::read_data,GenerationOutcome::unchanged);
  if(!valid(result))fail(GenerationFault::corrupt,GenerationStage::read_data,GenerationOutcome::unchanged);
  return result;
}

namespace detail {
GenerationOwner::GenerationOwner(std::string_view path,const std::array<char,32>& query,bool create,GenerationLimits limits)
    :limits_(limits),query_id_(query) {
  if(limits.path_bytes>=root_path_.size() || limits.chunk_bytes==0 || limits.operations==0 ||
      limits.chunk_bytes>static_cast<std::size_t>(std::numeric_limits<ssize_t>::max()) ||
      limits.checkpoint_bytes>static_cast<std::uint64_t>(std::numeric_limits<off_t>::max()) ||
      limits.plan_bytes>static_cast<std::uint64_t>(std::numeric_limits<off_t>::max()))
    fail(GenerationFault::limit,GenerationStage::path,outcome_);
  if(path.empty() || path.size()>limits.path_bytes || limits.path_bytes-path.size()<23 || path.find('\0')!=std::string_view::npos)
    fail(GenerationFault::path,GenerationStage::path,outcome_);
  const auto slash=path.rfind('/');const auto base=slash==std::string_view::npos?path:path.substr(slash+1);
  const auto parent=slash==std::string_view::npos?std::string_view{"."}:slash==0?path.substr(0,1):path.substr(0,slash);
  if(base.empty() || base=="." || base==".." || base.size()>232 || !hex({query.data(),query.size()}))
    fail(GenerationFault::path,GenerationStage::path,outcome_);
  std::array<char,4096> directory{};std::copy(parent.begin(),parent.end(),directory.begin());
  std::copy(path.begin(),path.end(),root_path_.begin());std::copy(base.begin(),base.end(),root_name_.begin());
  directory_.reset(static_cast<int>(checked(GenerationStage::open_directory,0,-1,directory.data())));
  std::array<char,256> lock_name{};std::copy(base.begin(),base.end(),lock_name.begin());std::copy_n(".lock",5,lock_name.begin()+static_cast<std::ptrdiff_t>(base.size()));
  target_=GenerationTarget::lock;lock_.reset(static_cast<int>(checked(GenerationStage::open_lock,0,directory_.get(),lock_name.data())));
  struct stat status{};static_cast<void>(checked(GenerationStage::stat_file,0,lock_.get(),nullptr,nullptr,nullptr,0,&status));
  if(!S_ISREG(status.st_mode))fail(GenerationFault::not_regular,GenerationStage::stat_file,outcome_);
  static_cast<void>(checked(GenerationStage::lock_file,0,lock_.get()));
  static_cast<void>(checked(GenerationStage::sync_file,0,lock_.get()));static_cast<void>(checked(GenerationStage::sync_directory,0,directory_.get()));
  target_=GenerationTarget::root;selected_=read_root(create,true);
  if(create && has_selection())fail(GenerationFault::state,GenerationStage::state,outcome_);
  read_retirement();
}
GenerationOwner::GenerationOwner(GenerationOwner&& other) noexcept
    :limits_(other.limits_),root_path_(other.root_path_),root_name_(other.root_name_),selected_(other.selected_),retirement_(other.retirement_),query_id_(other.query_id_),
      operations_(other.operations_),work_(other.work_),candidate_generation_(other.candidate_generation_),candidate_sha256_(other.candidate_sha256_),
      candidate_plan_generation_(other.candidate_plan_generation_),candidate_plan_sha256_(other.candidate_plan_sha256_),
      outcome_(other.outcome_),target_(other.target_),attempted_(other.attempted_) {
  directory_.reset(other.directory_.release());lock_.reset(other.lock_.release());other.selected_={};
}
void GenerationOwner::consume_work(std::uint64_t amount) {
  if(amount>limits_.validation_work-work_)fail(GenerationFault::limit,GenerationStage::state,outcome_);
  work_+=amount;
}
void GenerationOwner::healthy() const {
  if(attempted_)fail(GenerationFault::state,GenerationStage::state,outcome_);
}
std::int64_t GenerationOwner::call(GenerationStage stage,std::size_t requested,int fd,const char* name,
    const char* other_name,void* buffer,std::uint64_t offset,struct stat* status,bool emergency_cleanup) {
  const bool closing=stage==GenerationStage::close_file;
  if(operations_==UINT64_MAX || (!emergency_cleanup && operations_>=limits_.operations)) {
    if(closing)static_cast<void>(::close(fd));
    fail(GenerationFault::limit,stage,outcome_);
  }
  ++operations_;std::size_t transfer=requested;int before=0,after=0;
#if defined(CROWN_RUNTIME_TESTING) || defined(CROWN_GENERATION_FILE_TESTING)
  bool zero_entropy=false;
  if(testing::hook) {
    const auto choice=testing::hook({stage,target_,false,operations_,requested,0,0},testing::hook_context);
    before=choice.error_before;after=choice.error_after;transfer=std::min(transfer,choice.maximum_transfer);zero_entropy=choice.zero_entropy;
  }
#endif
  if(after && (stage==GenerationStage::open_directory || stage==GenerationStage::open_lock || stage==GenerationStage::open_root || stage==GenerationStage::open_retirement || stage==GenerationStage::create_temporary)) {before=after;after=0;}
  if(stage==GenerationStage::rename_root || (stage==GenerationStage::link_file && target_==GenerationTarget::root)) {outcome_=GenerationOutcome::unknown;attempted_=true;}
  std::int64_t result=-1;int error=0;
  if(before && !closing)error=before;
  else {
    switch(stage) {
      case GenerationStage::open_directory:if(!name)fail(GenerationFault::state,stage,outcome_);result=::open(name,O_RDONLY|O_DIRECTORY|O_CLOEXEC);break;
      case GenerationStage::open_lock:if(!name)fail(GenerationFault::state,stage,outcome_);result=::openat(fd,name,O_RDWR|O_CREAT|O_NOFOLLOW|O_CLOEXEC|O_NONBLOCK,0600);break;
      case GenerationStage::stat_file:if(!status)fail(GenerationFault::state,stage,outcome_);result=::fstat(fd,status);break;
      case GenerationStage::lock_file:result=::flock(fd,LOCK_EX|LOCK_NB);break;
      case GenerationStage::open_root:case GenerationStage::open_retirement:if(!name)fail(GenerationFault::state,stage,outcome_);result=::openat(fd,name,O_RDONLY|O_NOFOLLOW|O_CLOEXEC|O_NONBLOCK);break;
      case GenerationStage::read_data:if(!buffer)fail(GenerationFault::state,stage,outcome_);result=::pread(fd,buffer,transfer,static_cast<off_t>(offset));break;
      case GenerationStage::entropy:
        if(!buffer)fail(GenerationFault::state,stage,outcome_);
        result=posix::random_bytes(buffer,transfer);
#if defined(CROWN_RUNTIME_TESTING) || defined(CROWN_GENERATION_FILE_TESTING)
        if(zero_entropy && result>0)std::fill_n(static_cast<unsigned char*>(buffer),static_cast<std::size_t>(result),static_cast<unsigned char>(0));
#endif
        break;
      case GenerationStage::create_temporary:if(!name)fail(GenerationFault::state,stage,outcome_);result=::openat(fd,name,O_WRONLY|O_CREAT|O_EXCL|O_NOFOLLOW|O_CLOEXEC,0600);break;
      case GenerationStage::write_data:if(!buffer)fail(GenerationFault::state,stage,outcome_);result=::pwrite(fd,buffer,transfer,static_cast<off_t>(offset));break;
      case GenerationStage::sync_file:case GenerationStage::sync_directory:result=::fsync(fd);break;
      case GenerationStage::close_file:result=::close(fd);break;
      case GenerationStage::link_file:if(!name || !other_name)fail(GenerationFault::state,stage,outcome_);result=::linkat(fd,name,fd,other_name,0);break;
      case GenerationStage::rename_root:if(!name || !other_name)fail(GenerationFault::state,stage,outcome_);result=::renameat(fd,name,fd,other_name);break;
      case GenerationStage::unlink_temporary:case GenerationStage::unlink_candidate:case GenerationStage::unlink_history:case GenerationStage::unlink_retirement:if(!name)fail(GenerationFault::state,stage,outcome_);result=::unlinkat(fd,name,0);break;
      case GenerationStage::path:case GenerationStage::state:fail(GenerationFault::state,stage,outcome_);
    }
    if(result<0)error=errno;
    if(closing && before){result=-1;error=before;}else if(result>=0 && after){result=-1;error=after;}
  }
#if defined(CROWN_RUNTIME_TESTING) || defined(CROWN_GENERATION_FILE_TESTING)
  if(testing::hook)static_cast<void>(testing::hook({stage,target_,true,operations_,requested,result,error},testing::hook_context));
#endif
  errno=error;return result;
}
std::int64_t GenerationOwner::checked(GenerationStage stage,std::size_t count,int fd,const char* name,const char* other_name,void* buffer,
    std::uint64_t offset,struct stat* status) {
  for(;;) {
    const auto result=call(stage,count,fd,name,other_name,buffer,offset,status);if(result>=0)return result;
    const int error=errno;
    if(error==EINTR && stage!=GenerationStage::close_file && stage!=GenerationStage::link_file && stage!=GenerationStage::rename_root)continue;
    fail(stage==GenerationStage::lock_file && (error==EWOULDBLOCK || error==EAGAIN)?GenerationFault::busy:GenerationFault::io,stage,outcome_,error);
  }
}
void GenerationOwner::transfer(bool write,int fd,char* data,std::size_t size,std::uint64_t offset) {
  std::size_t done=0;const auto stage=write?GenerationStage::write_data:GenerationStage::read_data;
  while(done<size) {
    const auto count=checked(stage,std::min(limits_.chunk_bytes,size-done),fd,nullptr,nullptr,data+done,offset+done);
    if(count==0)fail(write?GenerationFault::io:GenerationFault::truncated,stage,outcome_,write?EIO:0);
    done+=static_cast<std::size_t>(count);
  }
}
GenerationRoot GenerationOwner::read_root(bool missing_ok,bool adopt) {
  target_=GenerationTarget::root;FileDescriptor file;
  std::int64_t opened=-1;
  do{opened=call(GenerationStage::open_root,0,directory_.get(),root_name_.data());}while(opened<0 && errno==EINTR);
  if(opened<0) {
    const int error=errno;if(missing_ok && error==ENOENT)return {};
    fail(GenerationFault::io,GenerationStage::open_root,outcome_,error);
  }else file.reset(static_cast<int>(opened));
  struct stat original{},current{};static_cast<void>(checked(GenerationStage::stat_file,0,file.get(),nullptr,nullptr,nullptr,0,&original));
  if(!S_ISREG(original.st_mode))fail(GenerationFault::not_regular,GenerationStage::stat_file,outcome_);
  if(original.st_size!=static_cast<off_t>(generation_root_size) && original.st_size!=static_cast<off_t>(generation_root_delivery_size) &&
      original.st_size!=static_cast<off_t>(generation_root_plan_size) && original.st_size!=static_cast<off_t>(generation_root_plan_delivery_size))
    fail(original.st_size<static_cast<off_t>(generation_root_size)?GenerationFault::truncated:GenerationFault::corrupt,GenerationStage::read_data,outcome_);
  const auto size=static_cast<std::size_t>(original.st_size);consume_work(2*size);std::array<char,generation_root_plan_delivery_size> bytes{};transfer(false,file.get(),bytes.data(),size);
  char extra=0;if(checked(GenerationStage::read_data,1,file.get(),nullptr,nullptr,&extra,size)!=0)fail(GenerationFault::changed,GenerationStage::read_data,outcome_);
  static_cast<void>(checked(GenerationStage::stat_file,0,file.get(),nullptr,nullptr,nullptr,0,&current));
  if(!same(original,current))fail(GenerationFault::changed,GenerationStage::stat_file,outcome_);
  const auto result=inspect_generation_root({bytes.data(),size});
  if(result.query_id!=query_id_)fail(GenerationFault::binding,GenerationStage::read_data,outcome_);
  if(adopt){static_cast<void>(checked(GenerationStage::sync_file,0,file.get()));static_cast<void>(checked(GenerationStage::sync_directory,0,directory_.get()));outcome_=GenerationOutcome::durable;}
  static_cast<void>(checked(GenerationStage::close_file,0,file.release()));return result;
}
std::array<char,4096> GenerationOwner::path(std::uint64_t generation,std::string_view suffix) const {
  std::array<char,4096> result{};const std::string_view root(root_path_.data());const auto digits=generation_hex(generation);auto out=result.begin();
  out=std::copy(root.begin(),root.end(),out);out=std::copy_n(".g",2,out);out=std::copy(digits.begin(),digits.end(),out);std::copy(suffix.begin(),suffix.end(),out);return result;
}
std::array<char,256> GenerationOwner::name(std::uint64_t generation,std::string_view suffix) const {
  std::array<char,256> result{};const std::string_view root(root_name_.data());const auto digits=generation_hex(generation);auto out=result.begin();
  out=std::copy(root.begin(),root.end(),out);out=std::copy_n(".g",2,out);out=std::copy(digits.begin(),digits.end(),out);std::copy(suffix.begin(),suffix.end(),out);return result;
}
std::array<char,4096> GenerationOwner::checkpoint_path(std::uint64_t generation) const {return path(generation,".ckpt");}
std::array<char,4096> GenerationOwner::journal_path(std::uint64_t generation) const {return path(generation,".wal");}
std::array<char,4096> GenerationOwner::plan_path(std::uint64_t generation) const {return path(generation,".plan");}
void GenerationOwner::prepare_next(std::uint64_t generation) {
  // Only the immediate unselected checkpoint/WAL/plan candidate names may
  // be removed under the stable root lock; selected history is untouched.
  healthy();
  outcome_=GenerationOutcome::unchanged;candidate_generation_=0;candidate_plan_generation_=0;
  if(retirement_ || !has_selection() || selected_.generation==UINT64_MAX || generation!=selected_.generation+1)fail(GenerationFault::state,GenerationStage::state,outcome_);
  if(read_root(false,false)!=selected_)fail(GenerationFault::changed,GenerationStage::state,outcome_);
  for(const auto target:{GenerationTarget::checkpoint,GenerationTarget::journal,GenerationTarget::plan}) {
    target_=target;const auto candidate=name(generation,target==GenerationTarget::checkpoint?".ckpt":target==GenerationTarget::journal?".wal":".plan");
    for(;;){if(call(GenerationStage::unlink_candidate,0,directory_.get(),candidate.data())>=0 || errno==ENOENT)break;if(errno!=EINTR)fail(GenerationFault::io,GenerationStage::unlink_candidate,outcome_,errno);}
  }
  static_cast<void>(checked(GenerationStage::sync_directory,0,directory_.get()));
}
bool GenerationOwner::cleanup_temporary(const char* name) noexcept {
  for(unsigned i=0;i<8;++i){try{if(call(GenerationStage::unlink_temporary,0,directory_.get(),name,nullptr,nullptr,0,nullptr,true)==0 || errno==ENOENT)return true;}catch(...){return false;}if(errno!=EINTR)return false;}return false;
}
void GenerationOwner::publish(std::string_view bytes,const char* destination,bool replace,bool selection) {
  // Private candidate publication does not select a root. Root link/rename
  // admission latches uncertainty until directory sync and final handoff.
  FileDescriptor file;std::array<char,64> temporary{};bool exists=false;
  try {
    constexpr std::string_view prefix=".crown-generation-",digits="0123456789abcdef";
    for(unsigned attempt=0;attempt<16;++attempt) {
      std::array<unsigned char,16> random{};std::size_t have=0;
      while(have<random.size()){const auto count=checked(GenerationStage::entropy,random.size()-have,-1,nullptr,nullptr,random.data()+have);if(!count)fail(GenerationFault::io,GenerationStage::entropy,outcome_,EIO);have+=static_cast<std::size_t>(count);}
      std::copy(prefix.begin(),prefix.end(),temporary.begin());for(std::size_t i=0;i<random.size();++i){temporary[prefix.size()+2*i]=digits[random[i]>>4];temporary[prefix.size()+2*i+1]=digits[random[i]&15];}
      if(std::string_view(temporary.data())==destination)continue;
      std::int64_t created=-1;do{created=call(GenerationStage::create_temporary,0,directory_.get(),temporary.data());}while(created<0 && errno==EINTR);
      if(created>=0){file.reset(static_cast<int>(created));exists=true;break;}
      if(errno!=EEXIST)fail(GenerationFault::io,GenerationStage::create_temporary,outcome_,errno);
    }
    if(!exists)fail(GenerationFault::io,GenerationStage::create_temporary,outcome_,EEXIST);
    transfer(true,file.get(),const_cast<char*>(bytes.data()),bytes.size());static_cast<void>(checked(GenerationStage::sync_file,0,file.get()));
    static_cast<void>(checked(GenerationStage::close_file,0,file.release()));
    if(replace){static_cast<void>(checked(GenerationStage::rename_root,0,directory_.get(),temporary.data(),destination));exists=false;}
    else {static_cast<void>(checked(GenerationStage::link_file,0,directory_.get(),temporary.data(),destination));static_cast<void>(checked(GenerationStage::unlink_temporary,0,directory_.get(),temporary.data()));exists=false;}
    static_cast<void>(checked(GenerationStage::sync_directory,0,directory_.get()));if(selection)outcome_=GenerationOutcome::durable;
  }catch(const GenerationFailure& error) {
    file.reset();const bool cleaned=!exists || cleanup_temporary(temporary.data());
    throw GenerationFailure(error.fault(),error.stage(),error.outcome(),error.native_error(),!cleaned);
  }catch(...){if(exists)static_cast<void>(cleanup_temporary(temporary.data()));throw;}
}
void GenerationOwner::publish_checkpoint(std::uint64_t generation,std::string_view bytes) {
  healthy();
  outcome_=GenerationOutcome::unchanged;
  if(generation==0 || (has_selection() && (selected_.generation==UINT64_MAX || generation!=selected_.generation+1)))fail(GenerationFault::state,GenerationStage::state,outcome_);
  if(bytes.size()>limits_.checkpoint_bytes)fail(GenerationFault::limit,GenerationStage::state,outcome_);
  consume_work(bytes.size());const auto hash=sha256_fixed(bytes);target_=GenerationTarget::checkpoint;const auto destination=name(generation,".ckpt");
  publish(bytes,destination.data(),false,false);candidate_generation_=generation;candidate_sha256_=hash;
}
void GenerationOwner::publish_plan(std::uint64_t generation,std::string_view bytes) {
  healthy();
  outcome_=GenerationOutcome::unchanged;
  if(generation==0 || bytes.empty() || (has_selection() && (selected_.generation==UINT64_MAX || generation!=selected_.generation+1)))
    fail(GenerationFault::state,GenerationStage::state,outcome_);
  if(bytes.size()>limits_.plan_bytes)fail(GenerationFault::limit,GenerationStage::state,outcome_);
  consume_work(bytes.size());const auto hash=sha256_fixed(bytes);target_=GenerationTarget::plan;const auto destination=name(generation,".plan");
  publish(bytes,destination.data(),false,false);candidate_plan_generation_=generation;candidate_plan_sha256_=hash;
}
ImageVector<char> GenerationOwner::read_plan(const resource::MemoryAccount& account) {
  return read_selected(account,true);
}
ImageVector<char> GenerationOwner::read_checkpoint(const resource::MemoryAccount& account) {
  return read_selected(account,false);
}
ImageVector<char> GenerationOwner::read_selected(const resource::MemoryAccount& account,bool plan) {
  // Both selected files use the same lock/root/stamp/EOF discipline. Selection
  // of cap/hash/path is fixed before I/O; this does not decode either format.
  healthy();
  if(!has_selection() || (plan && !selected_.plan_sha256))fail(GenerationFault::state,GenerationStage::state,outcome_);
  if(read_root(false,false)!=selected_)fail(GenerationFault::changed,GenerationStage::state,outcome_);
  const auto cap=plan?limits_.plan_bytes:limits_.checkpoint_bytes;
  const auto expected=plan?*selected_.plan_sha256:selected_.checkpoint_sha256;
  target_=plan?GenerationTarget::plan:GenerationTarget::checkpoint;
  const auto source=name(selected_.generation,plan?".plan":".ckpt");FileDescriptor file;
  file.reset(static_cast<int>(checked(GenerationStage::open_root,0,directory_.get(),source.data())));
  struct stat original{},current{};static_cast<void>(checked(GenerationStage::stat_file,0,file.get(),nullptr,nullptr,nullptr,0,&original));
  if(!S_ISREG(original.st_mode))fail(GenerationFault::not_regular,GenerationStage::stat_file,outcome_);
  if(original.st_size<0 || (plan && original.st_size==0) || static_cast<std::uint64_t>(original.st_size)>cap ||
      static_cast<std::uint64_t>(original.st_size)>SIZE_MAX)fail(GenerationFault::limit,GenerationStage::read_data,outcome_);
  const auto size=static_cast<std::size_t>(original.st_size);consume_work(2*static_cast<std::uint64_t>(size));
  ImageVector<char> bytes(image_allocator<char>(account));bytes.resize(size);transfer(false,file.get(),bytes.data(),size);
  char extra=0;if(checked(GenerationStage::read_data,1,file.get(),nullptr,nullptr,&extra,size)!=0)fail(GenerationFault::changed,GenerationStage::read_data,outcome_);
  static_cast<void>(checked(GenerationStage::stat_file,0,file.get(),nullptr,nullptr,nullptr,0,&current));
  if(!same(original,current))fail(GenerationFault::changed,GenerationStage::stat_file,outcome_);
  if(sha256_fixed({bytes.data(),bytes.size()})!=expected)fail(GenerationFault::binding,GenerationStage::read_data,outcome_);
  static_cast<void>(checked(GenerationStage::close_file,0,file.release()));
  if(read_root(false,false)!=selected_)fail(GenerationFault::changed,GenerationStage::state,outcome_);
  return bytes;
}
void GenerationOwner::publish_root(const GenerationRoot& next) {
  // Select only privately bound durable candidates. All throwing account
  // preparation belongs before this root publication boundary.
  healthy();
  if(next.query_id!=query_id_ || next.generation!=candidate_generation_ || next.checkpoint_sha256!=candidate_sha256_ ||
      (!has_selection() && next.first_generation!=next.generation) ||
      (has_selection() && (next.first_generation!=selected_.first_generation || next.physical_sequence<selected_.physical_sequence || next.command_sequence<selected_.command_sequence)))
    fail(GenerationFault::binding,GenerationStage::state,outcome_);
  if((next.plan_sha256 && (candidate_plan_generation_!=next.generation || *next.plan_sha256!=candidate_plan_sha256_)) ||
      (!next.plan_sha256 && (candidate_plan_generation_!=0 || selected_.plan_sha256)))
    fail(GenerationFault::binding,GenerationStage::state,outcome_);
  const auto bytes=encode(next);consume_work(bytes.size);target_=GenerationTarget::root;
  publish({bytes.bytes.data(),bytes.size},root_name_.data(),has_selection(),true);selected_=next;candidate_generation_=0;candidate_plan_generation_=0;attempted_=false;
}
void GenerationOwner::select_retirement_floor() {
  if(!retirement_)fail(GenerationFault::state,GenerationStage::state,outcome_);
  auto next=retirement_->before;next.delivery=selected_.delivery;next.first_generation=next.generation;
  if(selected_==next)return;
  auto before=retirement_->before;before.delivery=selected_.delivery;if(selected_!=before)fail(GenerationFault::binding,GenerationStage::state,outcome_);
  const auto bytes=encode(next);consume_work(bytes.size);target_=GenerationTarget::root;
  publish({bytes.bytes.data(),bytes.size},root_name_.data(),true,true);selected_=next;attempted_=false;
}
} // namespace detail
} // namespace crown::recovery
