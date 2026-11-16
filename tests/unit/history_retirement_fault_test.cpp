#include "history_retirement_fixture.hpp"
#include "generation_file_probe.hpp"
#include "checkpoint_file_probe.hpp"
#include "journal_file_probe.hpp"
#include "local_sink_probe.hpp"
#include <cerrno>
#include <sys/wait.h>
using namespace crown;
using namespace crown::runtime;
using namespace crown::history_retirement_test;
namespace {
namespace jp=recovery::journal;
enum class Action {retire,resume};
struct Hook {
  std::uint64_t count=0,fail=0,crash=0;bool after=false,pause_cleanup=false,repeat=false,deny_allocations=false,allocation_barrier=false;
  bool intent_linked=false,intent_synced=false,root_renamed=false,root_synced=false,order_violation=false,already_absent=false;
  std::size_t maximum=SIZE_MAX,allocations_at_intent=0;
  void visit(bool done) noexcept {if(!done)++count;if(count==crash && done==after)::_exit(77);}
  template<class D> D decision(bool done) const noexcept {D result;if(!done){result.maximum_transfer=maximum;if(count==fail){if(after)result.error_after=EIO;else result.error_before=EIO;}}return result;}
  static recovery::testing::GenerationDecision generation(const recovery::testing::GenerationEvent& event,void* context) noexcept {
    auto& h=*static_cast<Hook*>(context);h.visit(event.after);const auto stage=event.stage;const auto target=event.target;const bool success=event.after && event.result>=0 && event.native_error==0;
    if(success && target==recovery::GenerationTarget::retirement && stage==recovery::GenerationStage::link_file)h.intent_linked=true;
    if(success && target==recovery::GenerationTarget::retirement && stage==recovery::GenerationStage::sync_directory && h.intent_linked)h.intent_synced=true;
    if(!event.after && target==recovery::GenerationTarget::root && stage==recovery::GenerationStage::rename_root && !h.intent_synced)h.order_violation=true;
    if(success && target==recovery::GenerationTarget::root && stage==recovery::GenerationStage::rename_root)h.root_renamed=true;
    if(success && target==recovery::GenerationTarget::root && stage==recovery::GenerationStage::sync_directory && h.root_renamed)h.root_synced=true;
    if(!event.after && stage==recovery::GenerationStage::unlink_history && h.intent_linked && !h.root_synced)h.order_violation=true;
    if(!event.after && target==recovery::GenerationTarget::retirement && stage==recovery::GenerationStage::link_file && h.deny_allocations){h.allocation_barrier=true;h.allocations_at_intent=s04_alloc::calls;s04_alloc::remaining=0;}
    if(event.after && h.after && h.count==h.fail && event.native_error==ENOENT)h.already_absent=true;
    auto result=h.decision<recovery::testing::GenerationDecision>(event.after);
    if(!event.after && h.pause_cleanup && stage==recovery::GenerationStage::unlink_history)result.error_before=EIO;
    if(!event.after && h.repeat && stage==recovery::GenerationStage::read_data)result.error_before=EINTR;
    return result;
  }
  static recovery::testing::FileDecision checkpoint(const recovery::testing::FileEvent& event,void* context) noexcept {auto& h=*static_cast<Hook*>(context);h.visit(event.after);return h.decision<recovery::testing::FileDecision>(event.after);}
  static jp::testing::FileDecision journal(const jp::testing::FileEvent& event,void* context) noexcept {auto& h=*static_cast<Hook*>(context);h.visit(event.after);return h.decision<jp::testing::FileDecision>(event.after);}
  static sk::testing::Decision sink(const sk::testing::Event& event,void* context) noexcept {auto& h=*static_cast<Hook*>(context);h.visit(event.after);return h.decision<sk::testing::Decision>(event.after);}
};
struct Installed {
  explicit Installed(Hook& h){recovery::testing::set_generation_hook(Hook::generation,&h);recovery::testing::set_file_hook(Hook::checkpoint,&h);jp::testing::set_file_hook(Hook::journal,&h);sk::testing::set_hook(Hook::sink,&h);}
  ~Installed(){recovery::testing::set_generation_hook(nullptr,nullptr);recovery::testing::set_file_hook(nullptr,nullptr);jp::testing::set_file_hook(nullptr,nullptr);sk::testing::set_hook(nullptr,nullptr);}
};
struct Saved {
  RetirementFixture f;
  std::vector<std::pair<std::string,std::string>> files;
  bool pending;
  explicit Saved(Action action):pending(action==Action::resume) {
    if(pending){Hook h;h.pause_cleanup=true;bool failed=false;{Installed installed(h);try{f.session->retire_generation_history();}catch(const recovery::GenerationFailure&){failed=true;}}check(failed && std::filesystem::exists(f.root+".retire") && f.session->generation_state().selected.first_generation==3,"retirement resume fixture did not leave durable intent before unlink");}
    f.session.reset();files.emplace_back(f.root,contents(f.root));files.emplace_back(f.sink,contents(f.sink));
    for(std::uint64_t generation=1;generation<=3;++generation)for(const auto suffix:{".ckpt",".wal"}){const auto path=f.path(generation,suffix);files.emplace_back(path,contents(path));}
    if(pending)files.emplace_back(f.root+".retire",contents(f.root+".retire"));
  }
  void reset(){for(const auto& [path,bytes]:files)generation_test::put(path,bytes);if(!pending)std::filesystem::remove(f.root+".retire");}
  QuerySession::Owner owner(Action action){if(action==Action::retire)return f.restore();return {};}
  void perform(Action action,QuerySession::Owner& value){if(action==Action::retire)value->retire_generation_history();else value=f.restore();}
  void intact() const {
    const auto selected=generation_test::root(f.root);check(selected.generation==3 && (selected.first_generation==1 || selected.first_generation==3) && selected.physical_sequence==2 && selected.command_sequence==2,"retirement failure/crash changed selected native anchor");
    for(const auto& [path,bytes]:files)if(path==f.sink || path==f.path(3,".ckpt") || path==f.path(3,".wal"))check(contents(path)==bytes,"retirement failure/crash changed selected pair or accepted local output");
  }
};
Hook trace(Action action){Saved saved(action);auto value=saved.owner(action);Hook h;{Installed installed(h);saved.perform(action,value);}check(!h.order_violation,"intent/root/deletion persistence order violated");return h;}
void failures() {
  std::size_t cases=0,absent=0;
  for(const auto action:{Action::retire,Action::resume}) {
    Saved saved(action);const auto baseline=trace(action);
    for(std::uint64_t point=1;point<=baseline.count;++point)for(const bool after:{false,true}) {
      saved.reset();const auto before=descriptors();auto value=saved.owner(action);Hook h;h.fail=point;h.after=after;bool failed=false;
      {Installed installed(h);try{saved.perform(action,value);}catch(const recovery::GenerationFailure&){failed=true;}catch(const recovery::FileFailure&){failed=true;}catch(const jp::FileFailure&){failed=true;}catch(const sk::Failure&){failed=true;}}
      check(failed || h.already_absent,"retirement syscall error ignored");if(failed)++cases;else ++absent;value.reset();check(descriptors()==before,"retirement file error leaked descriptor/lock");saved.intact();saved.f.verify();
    }
    saved.reset();auto value=saved.owner(action);Hook short_io;short_io.maximum=3;{Installed installed(short_io);saved.perform(action,value);}check(!short_io.order_violation,"short transfers bypassed retirement ordering");value.reset();saved.f.verify();
    std::cout<<"retirement I/O action="<<static_cast<unsigned>(action)<<" actual boundaries="<<baseline.count<<" before/after errors/short I/O/native continuation passed\n";
  }
  Saved saved(Action::resume);Hook h;h.repeat=true;auto limits=generation_test::recovery_options();limits.root.operations=30;bool bounded=false;
  {Installed installed(h);try{auto value=saved.f.restore(limits);}catch(const recovery::GenerationFailure& e){bounded=e.fault()==recovery::GenerationFault::limit;}}
  check(bounded,"retirement repeated interruptions bypassed finite root quota");saved.intact();
  std::cout<<"retirement actual syscall errors="<<cases<<" already-absent after boundaries="<<absent<<" native state/source/output/next update passed\n";
}
void crashes() {
  std::size_t cases=0;
  for(const auto action:{Action::retire,Action::resume}) {
    Saved saved(action);const auto baseline=trace(action);
    for(std::uint64_t point=1;point<=baseline.count;++point)for(const bool after:{false,true}) {
      saved.reset();const auto child=::fork();check(child>=0,"retirement crash fork failed");
      if(child==0){auto value=saved.owner(action);Hook h;h.crash=point;h.after=after;Installed installed(h);try{saved.perform(action,value);}catch(...){::_exit(3);}::_exit(4);}
      int status=0;check(::waitpid(child,&status,0)==child && WIFEXITED(status) && WEXITSTATUS(status)==77,"retirement process boundary missed");saved.intact();saved.f.verify();++cases;
    }
  }
  std::cout<<"retirement process exits="<<cases<<" every intent/root/unlink/sync/resume boundary/native state/source/output/next update passed (not power loss)\n";
}
void allocations() {
  for(const auto action:{Action::retire,Action::resume}) {
    Saved saved(action);std::size_t count=0;std::uint64_t peak=0;
    {auto value=saved.owner(action);{s04_alloc::Scope scope;saved.perform(action,value);count=s04_alloc::calls;}if(action==Action::resume){const auto account=value.get_deleter().account();check(count==account.statistics().successful_allocations,"retirement recovery escaped receiving account");peak=account.statistics().peak_requested_bytes;}}
    for(std::size_t point=0;point<count;++point) {
      saved.reset();const auto before=descriptors();auto value=saved.owner(action);bool failed=false;
      {s04_alloc::Scope scope(static_cast<std::ptrdiff_t>(point));try{saved.perform(action,value);}catch(const std::bad_alloc&){failed=true;}}
      check(failed,"retirement allocation fault missed");value.reset();check(descriptors()==before,"retirement OOM leaked writer locks");for(const auto& [path,bytes]:saved.files)check(contents(path)==bytes,"retirement OOM mutated a durable prefix");
    }
    if(action==Action::resume){saved.reset();auto limits=generation_test::recovery_options();limits.replay.memory_limit_bytes=peak;{auto value=saved.f.restore(limits);}saved.reset();--*limits.replay.memory_limit_bytes;bool under=false;try{auto value=saved.f.restore(limits);}catch(const resource::MemoryFailure& e){under=e.fault()==resource::MemoryFault::limit;}check(under,"retirement one-under receiving heap accepted");}
    saved.reset();saved.f.verify();std::cout<<"retirement allocations action="<<static_cast<unsigned>(action)<<" points="<<count<<" every fault/account ownership/exact-under receiving heap passed\n";
  }
  Saved saved(Action::retire);auto value=saved.owner(Action::retire);Hook h;h.deny_allocations=true;{Installed installed(h);s04_alloc::Scope scope;value->retire_generation_history();}
  check(h.allocation_barrier && !s04_alloc::triggered && s04_alloc::calls==h.allocations_at_intent && !h.order_violation,"retirement allocated after intent publication or violated persistence order");value.reset();saved.f.verify();
  std::cout<<"retirement completion allocation-free after intent publication passed\n";
}
}
int main(int argc,char** argv){try{check(argc==2,"expected retirement mode");if(std::string_view(argv[1])=="crash")crashes();else{allocations();failures();}}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
