#include "generation_detail.hpp"
#include "posix_compat.hpp"
#include "crown/ir/digest.hpp"
#include "../runtime/checkpoint_policy.hpp"
#include <algorithm>
#include <cerrno>
#include <sys/stat.h>

namespace crown::recovery::detail {
namespace {
[[noreturn]] void fail(GenerationFault fault,GenerationStage stage=GenerationStage::state,GenerationOutcome outcome=GenerationOutcome::unchanged,int error=0) {
  throw GenerationFailure(fault,stage,outcome,error);
}
bool hex(std::span<const char> bytes) {
  return std::all_of(bytes.begin(),bytes.end(),[](char c){return (c>='0' && c<='9') || (c>='a' && c<='f');});
}
void valid(const RetirementIntent& value) {
  const auto& root=value.before;const auto& sink=value.sink;
  if(!hex(root.query_id) || !hex(root.checkpoint_sha256) || root.first_generation==0 || root.first_generation>=root.generation ||
      sink.query_id!=root.query_id || !hex(sink.sink_id) || !hex(sink.binding.physical_sha256) || !hex(sink.binding.source_sha256) ||
      !hex(sink.schema_sha256) || sink.binding.catalog_version==0 || sink.first_generation==0 || sink.first_generation>root.generation ||
      sink.base_sequence>root.physical_sequence || value.acknowledged_generation<sink.first_generation || value.acknowledged_generation>root.generation ||
      value.acknowledged_sequence<root.physical_sequence)fail(GenerationFault::binding);
  if(root.plan_sha256 && !hex(*root.plan_sha256))fail(GenerationFault::binding);
  static_cast<void>(runtime::detail::checkpoint_options(sink.binding.policy,0));
}
// The intent omits delivery; retain the actual selected root delivery anchor.
bool anchor(const RetirementIntent& intent,const GenerationRoot& selected) {
  auto before=intent.before;before.delivery=selected.delivery;auto after=before;after.first_generation=after.generation;return selected==before || selected==after;
}
void proof(const RetirementIntent& intent,const sink::Header& header,std::uint64_t generation,std::uint64_t sequence) {
  if(intent.sink!=header || generation<intent.acknowledged_generation || sequence<intent.acknowledged_sequence)fail(GenerationFault::binding);
}
bool same(const struct stat& a,const struct stat& b) {
  return posix::same_file_state(a,b);
}
// Fixed layouts fit 724/788 bytes; internal field helpers rely on those sizes.
struct Writer {
  std::array<char,retirement_plan_intent_size> bytes{};std::size_t offset=0;
  void text(std::span<const char> value){std::copy(value.begin(),value.end(),bytes.begin()+static_cast<std::ptrdiff_t>(offset));offset+=value.size();}
  void integer(std::uint64_t value,unsigned width=8){for(unsigned i=0;i<width;++i)bytes[offset++]=static_cast<char>((value>>(8*i))&255);}
};
struct Reader {
  std::string_view bytes;std::size_t offset=0;
  template<std::size_t N> void text(std::array<char,N>& value){std::copy_n(bytes.begin()+static_cast<std::ptrdiff_t>(offset),N,value.begin());offset+=N;}
  std::uint64_t integer(unsigned width=8){std::uint64_t value=0;for(unsigned i=0;i<width;++i)value|=std::uint64_t(static_cast<unsigned char>(bytes[offset++]))<<(8*i);return value;}
};
}
// Plan-aware v2 appends 64 bytes; legacy v1 keeps its exact layout.
RetirementBytes encode_retirement_intent(const RetirementIntent& intent) {
  valid(intent);RetirementBytes result;if(intent.before.plan_sha256)result.length=retirement_plan_intent_size;
  Writer w;constexpr std::string_view magic="CROWNRT1";w.text(magic);w.integer(intent.before.plan_sha256?2:1,2);w.integer(0,2);w.integer(result.length-84);
  const auto& r=intent.before;w.text(r.query_id);w.integer(r.generation);w.integer(r.first_generation);w.text(r.checkpoint_sha256);w.integer(r.physical_sequence);w.integer(r.command_sequence);
  const auto& s=intent.sink;w.text(s.query_id);w.text(s.sink_id);w.text(s.binding.physical_sha256);w.text(s.binding.source_sha256);w.integer(s.binding.catalog_version);for(const auto word:s.binding.policy)w.integer(word);
  w.integer(s.first_generation);w.integer(s.base_sequence);w.integer(s.fields);w.text(s.schema_sha256);w.integer(intent.acknowledged_generation);w.integer(intent.acknowledged_sequence);
  if(r.plan_sha256)w.text(*r.plan_sha256);
  if(w.offset!=result.length-64)fail(GenerationFault::state);
  w.text(sha256_fixed({w.bytes.data(),w.offset}));result.bytes=w.bytes;return result;
}
RetirementIntent inspect_retirement_intent(std::string_view bytes) {
  if(bytes.size()!=retirement_intent_size && bytes.size()!=retirement_plan_intent_size)fail(bytes.size()<retirement_intent_size?GenerationFault::truncated:GenerationFault::corrupt,GenerationStage::read_data);
  const auto digest=sha256_fixed(bytes.substr(0,bytes.size()-64));
  if(bytes.substr(0,8)!="CROWNRT1" || bytes.substr(bytes.size()-64)!=std::string_view(digest.data(),digest.size()))fail(GenerationFault::corrupt,GenerationStage::read_data);
  Reader v{bytes,8};const auto version=v.integer(2),flags=v.integer(2),body=v.integer();
  if(flags!=0 || !((version==1 && body==640 && bytes.size()==retirement_intent_size) ||
      (version==2 && body==704 && bytes.size()==retirement_plan_intent_size)))fail(GenerationFault::corrupt,GenerationStage::read_data);
  RetirementIntent result;auto& r=result.before;v.text(r.query_id);r.generation=v.integer();r.first_generation=v.integer();v.text(r.checkpoint_sha256);r.physical_sequence=v.integer();r.command_sequence=v.integer();
  auto& s=result.sink;v.text(s.query_id);v.text(s.sink_id);v.text(s.binding.physical_sha256);v.text(s.binding.source_sha256);s.binding.catalog_version=v.integer();for(auto& word:s.binding.policy)word=v.integer();
  s.first_generation=v.integer();s.base_sequence=v.integer();s.fields=v.integer();v.text(s.schema_sha256);result.acknowledged_generation=v.integer();result.acknowledged_sequence=v.integer();
  if(version==2){std::array<char,64> hash{};v.text(hash);r.plan_sha256=hash;}
  if(v.offset!=bytes.size()-64)fail(GenerationFault::corrupt,GenerationStage::read_data);
  valid(result);return result;
}
std::array<char,256> GenerationOwner::retirement_name() const {
  std::array<char,256> value{};const std::string_view root(root_name_.data());auto out=std::copy(root.begin(),root.end(),value.begin());std::copy_n(".retire",7,out);return value;
}
void GenerationOwner::read_retirement() {
  target_=GenerationTarget::retirement;const auto name=retirement_name();FileDescriptor file;std::int64_t opened=-1;
  do{opened=call(GenerationStage::open_retirement,0,directory_.get(),name.data());}while(opened<0 && errno==EINTR);
  if(opened<0){if(errno==ENOENT){retirement_.reset();return;}fail(GenerationFault::io,GenerationStage::open_retirement,outcome_,errno);}file.reset(static_cast<int>(opened));
  struct stat original{},current{};static_cast<void>(checked(GenerationStage::stat_file,0,file.get(),nullptr,nullptr,nullptr,0,&original));
  if(!S_ISREG(original.st_mode))fail(GenerationFault::not_regular,GenerationStage::stat_file,outcome_);
  if(original.st_size!=static_cast<off_t>(retirement_intent_size) && original.st_size!=static_cast<off_t>(retirement_plan_intent_size))fail(original.st_size<static_cast<off_t>(retirement_intent_size)?GenerationFault::truncated:GenerationFault::corrupt,GenerationStage::read_data,outcome_);
  const auto size=static_cast<std::size_t>(original.st_size);consume_work(2*size);std::array<char,retirement_plan_intent_size> bytes{};transfer(false,file.get(),bytes.data(),size);
  char extra=0;if(checked(GenerationStage::read_data,1,file.get(),nullptr,nullptr,&extra,size)!=0)fail(GenerationFault::changed,GenerationStage::read_data,outcome_);
  static_cast<void>(checked(GenerationStage::stat_file,0,file.get(),nullptr,nullptr,nullptr,0,&current));if(!same(original,current))fail(GenerationFault::changed,GenerationStage::stat_file,outcome_);
  const auto intent=inspect_retirement_intent({bytes.data(),size});if(!anchor(intent,selected_) || intent.before.query_id!=query_id_)fail(GenerationFault::binding,GenerationStage::read_data,outcome_);
  static_cast<void>(checked(GenerationStage::sync_file,0,file.get()));static_cast<void>(checked(GenerationStage::sync_directory,0,directory_.get()));
  static_cast<void>(checked(GenerationStage::close_file,0,file.release()));retirement_=intent;
}
void GenerationOwner::validate_retirement(const sink::File& file) const {
  if(!retirement_)return;
  const auto state=file.state();if(state.recovery_required || !anchor(*retirement_,selected_))fail(GenerationFault::binding);
  if(selected_.delivery){const auto prefix=file.prefix(selected_.physical_sequence);if(selected_.delivery->sink_id!=state.header.sink_id || selected_.delivery->bytes!=prefix.bytes || selected_.delivery->content_sha256!=prefix.content_sha256)fail(GenerationFault::binding);}
  else if(state.header.base_sequence!=selected_.physical_sequence)fail(GenerationFault::binding);
  proof(*retirement_,state.header,state.generation,state.sequence);
}
// Caller just read and validated bytes under the generation lock.
// Rehash and sync the selected inode/name here; no checkpoint reread occurs.
void GenerationOwner::confirm_checkpoint(std::string_view bytes) {
  if(bytes.size()>limits_.checkpoint_bytes)fail(GenerationFault::limit);
  consume_work(bytes.size());if(sha256_fixed(bytes)!=selected_.checkpoint_sha256)fail(GenerationFault::binding);
  target_=GenerationTarget::checkpoint;const auto name=this->name(selected_.generation,".ckpt");FileDescriptor file;
  file.reset(static_cast<int>(checked(GenerationStage::open_root,0,directory_.get(),name.data())));struct stat state{};
  static_cast<void>(checked(GenerationStage::stat_file,0,file.get(),nullptr,nullptr,nullptr,0,&state));
  if(!S_ISREG(state.st_mode) || state.st_size<0 || static_cast<std::uint64_t>(state.st_size)!=bytes.size())fail(GenerationFault::changed,GenerationStage::stat_file,outcome_);
  static_cast<void>(checked(GenerationStage::sync_file,0,file.get()));static_cast<void>(checked(GenerationStage::sync_directory,0,directory_.get()));
  static_cast<void>(checked(GenerationStage::close_file,0,file.release()));
}
// Session first checks quiescence and privately verified native delivery.
// The durable intent fixes cleanup scope; select its root floor before unlinking.
void GenerationOwner::retire_history(const sink::Receipt& receipt,std::string_view checkpoint_bytes,const resource::MemoryAccount& account) {
  healthy();
  outcome_=GenerationOutcome::unchanged;if(!has_selection() || read_root(false,true)!=selected_)fail(GenerationFault::changed);
  read_retirement();const auto header=receipt.header();
  if(header.query_id!=query_id_ || header.first_generation>selected_.generation || header.base_sequence>selected_.physical_sequence ||
      receipt.generation()>selected_.generation || receipt.sequence()<selected_.physical_sequence)fail(GenerationFault::binding);
  if(!selected_.delivery && header.base_sequence!=selected_.physical_sequence)fail(GenerationFault::binding);
  if(retirement_)proof(*retirement_,header,receipt.generation(),receipt.sequence());
  else if(selected_.first_generation==selected_.generation)return;
  if(selected_.plan_sha256)static_cast<void>(read_plan(account));
  confirm_checkpoint(checkpoint_bytes);
  if(!retirement_) {
    const RetirementIntent intent{selected_,header,receipt.generation(),receipt.sequence()};const auto bytes=encode_retirement_intent(intent);consume_work(bytes.size());const auto name=retirement_name();target_=GenerationTarget::retirement;
    publish({bytes.data(),bytes.size()},name.data(),false,false);retirement_=intent;
  }
  select_retirement_floor();
  for(auto generation=retirement_->before.first_generation;generation<retirement_->before.generation;++generation)for(const auto target:{GenerationTarget::checkpoint,GenerationTarget::journal,GenerationTarget::plan}) {
    target_=target;const auto name=this->name(generation,target==GenerationTarget::checkpoint?".ckpt":target==GenerationTarget::journal?".wal":".plan");
    for(;;){if(call(GenerationStage::unlink_history,0,directory_.get(),name.data())>=0 || errno==ENOENT)break;if(errno!=EINTR)fail(GenerationFault::io,GenerationStage::unlink_history,outcome_,errno);}
    static_cast<void>(checked(GenerationStage::sync_directory,0,directory_.get()));
  }
  const auto name=retirement_name();target_=GenerationTarget::retirement;static_cast<void>(checked(GenerationStage::unlink_retirement,0,directory_.get(),name.data()));
  static_cast<void>(checked(GenerationStage::sync_directory,0,directory_.get()));retirement_.reset();
}
} // namespace crown::recovery::detail
