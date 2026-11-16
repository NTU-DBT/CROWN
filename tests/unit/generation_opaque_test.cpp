#include "generation_detail.hpp"
#include "generation_file_probe.hpp"
#include "journal_file_fixture.hpp"
#include "index_allocation.hpp"
#include "crown/ir/digest.hpp"
#include <cassert>
#include <cerrno>
#include <fcntl.h>

namespace {
using namespace crown;
using namespace crown::recovery;
using journal_file_test::contents;
using journal_file_test::descriptors;
using journal_file_test::Directory;
std::array<char,32> id() { std::array<char,32> value{};value.fill('a');return value; }
void put(const std::string& path,std::string_view bytes) {
  std::ofstream out(path,std::ios::binary|std::ios::trunc);out.write(bytes.data(),static_cast<std::streamsize>(bytes.size()));assert(out);
}
std::string_view view(const ImageVector<char>& bytes) { return {bytes.data(),bytes.size()}; }
struct Fixture {
  Directory directory;
  std::string root=directory.file("opaque.root"),checkpoint=root+".g0000000000000001.ckpt",plan=root+".g0000000000000001.plan";
  std::string payload{"binary\0checkpoint",17},descriptor="opaque descriptor";
  explicit Fixture(bool with_plan=true,bool empty=false) {
    if(empty)payload.clear();
    detail::GenerationOwner owner(root,id(),true,{});
    owner.publish_checkpoint(1,payload);if(with_plan)owner.publish_plan(1,descriptor);
    GenerationRoot selected{id(),1,1,sha256_fixed(payload),0,1};if(with_plan)selected.plan_sha256=sha256_fixed(descriptor);
    owner.publish_root(selected); // Lower opaque publisher intentionally decodes no checkpoint/WAL.
  }
};
// Only read-operation hooks are installed, after the root/lock owner exists.
// Fixed records keep hook observation itself outside the allocation seam.
struct Hook {
  std::uint64_t count=0,fail=0;
  bool after=false;
  std::size_t maximum=SIZE_MAX;
  const char* mutate=nullptr;
  bool append=false,done=false;
  static testing::GenerationDecision call(const testing::GenerationEvent& event,void* context) noexcept {
    auto& self=*static_cast<Hook*>(context);testing::GenerationDecision result;
    if(!event.after) {
      ++self.count;result.maximum_transfer=self.maximum;
      if(self.count==self.fail){if(self.after)result.error_after=EIO;else result.error_before=EIO;}
    }
    if(self.mutate && !self.done && event.after && event.stage==GenerationStage::read_data &&
        event.target==GenerationTarget::checkpoint && event.result>0) {
      self.done=true;const int fd=::open(self.mutate,O_WRONLY|O_CLOEXEC);
      if(fd>=0){const char byte='!';const auto offset=self.append?::lseek(fd,0,SEEK_END):0;
        const auto written=::pwrite(fd,&byte,1,offset);const auto closed=::close(fd);
        assert(written==1 && closed==0);}
    }
    return result;
  }
};
struct Installed {
  explicit Installed(Hook& hook) { testing::set_generation_hook(Hook::call,&hook); }
  ~Installed() { testing::set_generation_hook(nullptr,nullptr); }
};
template<class Action> void rejected(Action action) {
  bool failed=false;try { action(); } catch(const GenerationFailure&) { failed=true; }assert(failed);
}
void round_trip_and_limits() {
  Fixture f;const auto account=resource::MemoryAccount::create(1024*1024);std::uint64_t operations=0,work=0,peak=0;
  {detail::GenerationOwner owner(f.root,id(),false,{});auto bytes=owner.read_checkpoint(account);
    assert(view(bytes)==f.payload && view(owner.read_plan(account))==f.descriptor);
    operations=owner.operations();work=owner.validation_work();peak=account.statistics().peak_requested_bytes;}
  assert(account.statistics().current.allocations==1);
  for(unsigned which=0;which<4;++which) {
    GenerationLimits limits;
    if(which==0)limits.operations=operations;
    if(which==1)limits.validation_work=work;
    if(which==2)limits.operations=operations-1;
    if(which==3)limits.validation_work=work-1;
    const auto before=descriptors();bool failed=false;
    try {detail::GenerationOwner owner(f.root,id(),false,limits);auto bytes=owner.read_checkpoint(account);auto plan=owner.read_plan(account);}
    catch(const GenerationFailure& error) {failed=error.fault()==GenerationFault::limit;}
    assert(failed==(which>=2) && descriptors()==before && account.statistics().current.allocations==1);
  }
  {auto exact=resource::MemoryAccount::create(peak);detail::GenerationOwner owner(f.root,id(),false,{});
    auto bytes=owner.read_checkpoint(exact);auto plan=owner.read_plan(exact);assert(exact.statistics().peak_requested_bytes==peak);}
  {auto low=resource::MemoryAccount::create(peak-1);bool failed=false;
    try {detail::GenerationOwner owner(f.root,id(),false,{});auto bytes=owner.read_checkpoint(low);auto plan=owner.read_plan(low);}
    catch(const resource::MemoryFailure& error) {failed=error.fault()==resource::MemoryFault::limit;}
    assert(failed && low.statistics().current.allocations==1);}
  {auto cap=GenerationLimits{};cap.checkpoint_bytes=f.payload.size()-1;detail::GenerationOwner owner(f.root,id(),false,cap);
    s04_alloc::Scope deny(0);rejected([&]{auto bytes=owner.read_checkpoint(account);});assert(s04_alloc::calls==0);}
  {Fixture empty(false,true);detail::GenerationOwner owner(empty.root,id(),false,{});
    assert(owner.read_checkpoint(account).empty());rejected([&]{auto bytes=owner.read_plan(account);});}
}
void failures_and_identity() {
  Fixture f;const auto account=resource::MemoryAccount::create(1024*1024);const auto root=contents(f.root);std::uint64_t count=0;
  {detail::GenerationOwner owner(f.root,id(),false,{});Hook h;{Installed installed(h);auto bytes=owner.read_checkpoint(account);assert(view(bytes)==f.payload);}count=h.count;}
  for(std::uint64_t point=1;point<=count;++point)for(const bool after:{false,true}) {
    const auto before=descriptors();
    {detail::GenerationOwner owner(f.root,id(),false,{});Hook h;h.fail=point;h.after=after;Installed installed(h);
      rejected([&]{auto bytes=owner.read_checkpoint(account);});}
    assert(descriptors()==before && account.statistics().current.allocations==1 && contents(f.checkpoint)==f.payload && contents(f.root)==root);
  }
  {detail::GenerationOwner owner(f.root,id(),false,{});Hook h;h.maximum=3;Installed installed(h);
    assert(view(owner.read_checkpoint(account))==f.payload);}
  for(unsigned kind=0;kind<3;++kind) {
    detail::GenerationOwner owner(f.root,id(),false,{});Hook h;h.mutate=kind==2?f.root.c_str():f.checkpoint.c_str();h.append=kind==1;
    {Installed installed(h);rejected([&]{auto bytes=owner.read_checkpoint(account);});}assert(h.done);
    put(f.checkpoint,f.payload);put(f.root,root);
  }
  for(const auto& bad:{f.payload.substr(0,3),f.payload+"extra",std::string(f.payload.size(),'x')}) {
    put(f.checkpoint,bad);detail::GenerationOwner owner(f.root,id(),false,{});rejected([&]{auto bytes=owner.read_checkpoint(account);});
  }
  put(f.checkpoint,f.payload);
  std::filesystem::remove(f.checkpoint);const auto victim=f.directory.file("victim");put(victim,f.payload);
  assert(::symlink(victim.c_str(),f.checkpoint.c_str())==0);
  {detail::GenerationOwner owner(f.root,id(),false,{});rejected([&]{auto bytes=owner.read_checkpoint(account);});}
  assert(contents(victim)==f.payload);std::filesystem::remove(f.checkpoint);std::filesystem::create_directory(f.checkpoint);
  {detail::GenerationOwner owner(f.root,id(),false,{});rejected([&]{auto bytes=owner.read_checkpoint(account);});}
  assert(account.statistics().current.allocations==1);account.check_invariants();
}
} // namespace
int main() {round_trip_and_limits();failures_and_identity();}
