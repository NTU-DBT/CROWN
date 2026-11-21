#include "journal_file_fixture.hpp"
#include "journal_file_probe.hpp"
#include "index_allocation.hpp"
#include <sys/wait.h>
#include <cerrno>
using namespace crown;
using namespace crown::journal_file_test;
namespace {
struct Hook {
  std::array<jp::testing::FileEvent,8192> events{};std::size_t size=0,short_bytes=SIZE_MAX;
  std::uint64_t fail_at=0,crash_at=0;bool after=false,crash_after=false,zero_entropy=false;
  int error=EIO,cleanup_error=0;std::optional<jp::FileStage> short_stage,repeat_interrupt;
  static jp::testing::FileDecision call(const jp::testing::FileEvent& event,void* data) noexcept {
    auto& self=*static_cast<Hook*>(data);if(self.size<self.events.size())self.events[self.size++]=event;
    if(event.ordinal==self.crash_at && event.after==self.crash_after)::_exit(77);
    jp::testing::FileDecision result;
    if(!event.after) {
      if(!self.short_stage || *self.short_stage==event.stage){result.maximum_transfer=self.short_bytes;}
      result.zero_entropy=self.zero_entropy;
      if(self.repeat_interrupt && *self.repeat_interrupt==event.stage)result.error_before=EINTR;
      if(event.stage==jp::FileStage::unlink_temporary)result.error_before=self.cleanup_error;
      if(event.ordinal==self.fail_at){if(self.after)result.error_after=self.error;else result.error_before=self.error;}
    }
    return result;
  }
};
struct Installed {
  explicit Installed(Hook& hook){jp::testing::set_file_hook(Hook::call,&hook);}
  ~Installed(){jp::testing::set_file_hook(nullptr,nullptr);}
};
enum class Mode {create,open,append,repair};
const char* name(Mode mode){switch(mode){case Mode::create:return "create";case Mode::open:return "open";case Mode::append:return "append";case Mode::repair:return "repair";}return "invalid";}
std::string initial(Mode mode,const Frames& f) {
  if(mode==Mode::create)return {};
  if(mode==Mode::open)return f.header+f.input+f.commit;
  if(mode==Mode::repair)return f.header+f.input+f.commit.substr(0,20);
  return f.header+f.input;
}
void setup(Mode mode,const std::string& path,const Frames& f){std::filesystem::remove(path);if(mode!=Mode::create)put(path,initial(mode,f));}
void exercise(Mode mode,const std::string& path,const Frames& f,const resource::MemoryAccount& account,jp::FileLimits limits={}) {
  if(mode==Mode::create){auto file=jp::File::create(account,path,f.binding,limits);file.close();return;}
  auto file=jp::File::open(account,path,f.binding,limits);
  if(mode==Mode::append)file.append(f.commit);
  if(mode==Mode::repair)file.repair_tail();
  file.close();
}
void surviving(Mode mode,const std::string& path,const Frames& f,const resource::MemoryAccount& account) {
  if(!std::filesystem::exists(path)){check(mode==Mode::create,"existing journal disappeared");return;}
  const auto actual=contents(path);const auto prior=initial(mode,f);
  check(actual==prior || (mode==Mode::create && actual==f.header) || (mode==Mode::append && actual==prior+f.commit) ||
      (mode==Mode::repair && actual==f.header+f.input),"failure left an unexpected journal image");
  auto reopened=jp::File::open(account,path,f.binding);const auto state=reopened.state();
  if(mode==Mode::repair)check(state.pending && state.pending->frame==f.input && state.command_sequence==0,"failed repair lost complete input");
  else check(state.command_sequence<=1,"failure minted a committed command");
  reopened.close();
}
Hook trace(Mode mode,const std::string& path,const Frames& f,const resource::MemoryAccount& account) {
  setup(mode,path,f);Hook hook;{Installed install(hook);exercise(mode,path,f,account);}return hook;
}
jp::FileOutcome expected_outcome(Mode mode,const Hook& trace,std::uint64_t point) {
  std::uint64_t link=0,directory=0,mutation=0,sync=0;
  for(std::size_t k=0;k<trace.size;++k) {
    const auto& e=trace.events[k];if(e.after)continue;
    if(e.stage==jp::FileStage::link_file)link=e.ordinal;
    if(e.stage==jp::FileStage::sync_directory)directory=e.ordinal;
    if(e.stage==jp::FileStage::write_data || e.stage==jp::FileStage::truncate_tail)mutation=e.ordinal;
    if(e.stage==jp::FileStage::sync_file)sync=e.ordinal;
  }
  if(mode==Mode::create)return point<link?jp::FileOutcome::unchanged:point<=directory?jp::FileOutcome::unknown:jp::FileOutcome::durable;
  if(mode==Mode::open || point<mutation-1)return point<=directory?jp::FileOutcome::unchanged:jp::FileOutcome::durable;
  return point<mutation?jp::FileOutcome::unchanged:point<=sync?jp::FileOutcome::unknown:jp::FileOutcome::durable;
}
void faults(const Frames& f) {
  Directory dir;const auto path=dir.file();auto account=resource::MemoryAccount::create(4*1024*1024);
  std::size_t total=0;
  for(const auto mode:{Mode::create,Mode::open,Mode::append,Mode::repair}) {
    const Hook baseline=trace(mode,path,f,account);const auto operations=baseline.events[baseline.size-1].ordinal;
    for(std::uint64_t point=1;point<=operations;++point)for(const bool after:{false,true}) {
      setup(mode,path,f);Hook failure;failure.fail_at=point;failure.after=after;const auto fds=descriptors();const auto resident=account.statistics().current;bool rejected=false;
      {Installed install(failure);s04_alloc::Scope count;try{exercise(mode,path,f,account);}catch(const jp::FileFailure& e){rejected=true;check(e.outcome()==expected_outcome(mode,baseline,point),"syscall failure durability outcome differs");check(!e.temporary_cleanup_failed(),"ordinary failure orphaned temporary");}}
      check(rejected && descriptors()==fds && account.statistics().current==resident && temporaries(dir)==0,"syscall failure did not reject or leaked");
      surviving(mode,path,f,account);++total;
    }
    // The quota bounds each public call (and each scanned record), not the file's
    // lifetime: budgets below the busiest call's need fail cleanly with a limit and
    // every larger budget succeeds.
    std::uint64_t threshold=0;
    for(std::uint64_t budget=1;budget<operations;++budget) {
      setup(mode,path,f);auto limits=jp::FileLimits{};limits.operations=budget;const auto fds=descriptors();bool failed=false,limited=false;
      try{exercise(mode,path,f,account,limits);}catch(const jp::FileFailure& e){failed=true;limited=e.fault()==jp::FileFault::limit;}
      check((!failed || (limited && threshold==0)) && descriptors()==fds && temporaries(dir)==0,"operation quota leaked/accepted");
      if(!failed && threshold==0)threshold=budget;
      surviving(mode,path,f,account);
    }
    check(threshold!=1,"operation quota did not bound a single call");
    for(const auto stage:{jp::FileStage::entropy,jp::FileStage::read_data,jp::FileStage::write_data,jp::FileStage::sync_file,jp::FileStage::sync_directory,jp::FileStage::truncate_tail,jp::FileStage::lock_file}) {
      const auto event=std::find_if(baseline.events.begin(),baseline.events.begin()+static_cast<std::ptrdiff_t>(baseline.size),[&](const auto& e){return !e.after && e.stage==stage;});
      if(event==baseline.events.begin()+static_cast<std::ptrdiff_t>(baseline.size))continue;
      setup(mode,path,f);Hook interrupt;interrupt.fail_at=event->ordinal;interrupt.error=EINTR;{Installed install(interrupt);exercise(mode,path,f,account);}
    }
    setup(mode,path,f);Hook short_io;short_io.short_bytes=3;{Installed install(short_io);exercise(mode,path,f,account);}
    std::cout<<"journal "<<name(mode)<<" syscall boundaries="<<operations<<" before/after errors, quotas, EINTR, short transfers passed\n";
  }
  // Errors after an actual commit write leave that commit recoverable even
  // though the old writer cannot report success or be reused.
  setup(Mode::append,path,f);auto file=jp::File::open(account,path,f.binding);const auto before=file.operations();Hook failure;failure.fail_at=before+2;failure.after=true;
  bool unknown=false;{Installed install(failure);try{file.append(f.commit);}catch(const jp::FileFailure& e){unknown=e.outcome()==jp::FileOutcome::unknown;}}
  check(unknown,"post-write error lost indeterminate outcome");
  bool poisoned=false;try{file.append(f.commit);}catch(const jp::FileFailure& e){poisoned=e.fault()==jp::FileFault::state;}check(poisoned,"writer retried after uncertain append");file.close();
  {auto recovered=jp::File::open(account,path,f.binding);check(recovered.state().command_sequence==1,"recovery lost actual commit after uncertain append");recovered.close();}
  // A real short write followed by an error leaves only an incomplete tail.
  setup(Mode::append,path,f);
  {auto partial=jp::File::open(account,path,f.binding);Hook fault;fault.short_bytes=13;fault.fail_at=partial.operations()+3;bool failed=false;
    {Installed install(fault);try{partial.append(f.commit);}catch(const jp::FileFailure& e){failed=e.outcome()==jp::FileOutcome::unknown;}}
    check(failed && contents(path)==f.header+f.input+f.commit.substr(0,13),"short write/error did not preserve actual partial tail");partial.close();}
  {auto recovered=jp::File::open(account,path,f.binding);check(recovered.state().torn_tail && recovered.state().command_sequence==0,"short write minted a complete commit");recovered.repair_tail();recovered.append(f.commit);recovered.close();}
  for(const auto stage:{jp::FileStage::entropy,jp::FileStage::read_data,jp::FileStage::write_data}) {
    const auto mode=stage==jp::FileStage::read_data?Mode::open:Mode::create;setup(mode,path,f);Hook zero;zero.short_bytes=0;zero.short_stage=stage;bool rejected=false;
    {Installed install(zero);try{exercise(mode,path,f,account);}catch(const jp::FileFailure&){rejected=true;}}check(rejected && temporaries(dir)==0,"zero-progress I/O accepted or leaked");
  }
  setup(Mode::create,path,f);Hook interrupted;interrupted.repeat_interrupt=jp::FileStage::write_data;auto low=jp::FileLimits{};low.operations=16;bool bounded=false;
  {Installed install(interrupted);try{exercise(Mode::create,path,f,account,low);}catch(const jp::FileFailure& e){bounded=e.fault()==jp::FileFault::limit;}}
  check(bounded && !std::filesystem::exists(path) && temporaries(dir)==0,"repeated EINTR bypassed I/O quota/cleanup");
  // A deterministic private temporary name equal to the requested destination
  // must be skipped before creating anything; all 16 entropy attempts are bounded.
  const auto identical=dir.file(".crown-journal-00000000000000000000000000000000");Hook entropy;entropy.zero_entropy=true;bool skipped=false;
  {Installed install(entropy);try{auto value=jp::File::create(account,identical,f.binding);}catch(const jp::FileFailure& e){skipped=e.stage()==jp::FileStage::create_temporary;}}
  check(skipped && !std::filesystem::exists(identical) && temporaries(dir)==0,"temporary basename collision published partial target");
  // Check cleanup failure is explicit; cleanup's fixed retry bound survives the
  // ordinary operation cap. Nothing is published before the failed write.
  std::filesystem::remove(path);Hook cleanup;cleanup.fail_at=5;cleanup.cleanup_error=EACCES;bool flagged=false;
  {Installed install(cleanup);try{auto value=jp::File::create(account,path,f.binding);}catch(const jp::FileFailure& e){flagged=e.temporary_cleanup_failed();}}
  check(flagged && !std::filesystem::exists(path),"cleanup failure was hidden or published target");
  for(const auto& e:std::filesystem::directory_iterator(dir.name))if(e.path().filename().native().starts_with(".crown-journal-"))std::filesystem::remove(e.path());
  std::cout<<"journal actual syscall error cases="<<total<<" poison/reopen, uncertain commit and cleanup reporting passed\n";
}
void crashes(const Frames& f) {
  Directory dir;const auto path=dir.file();auto account=resource::MemoryAccount::create(4*1024*1024);std::size_t total=0;
  for(const auto mode:{Mode::create,Mode::open,Mode::append,Mode::repair}) {
    const Hook baseline=trace(mode,path,f,account);const auto operations=baseline.events[baseline.size-1].ordinal;
    for(std::uint64_t point=1;point<=operations;++point)for(const bool after:{false,true}) {
      setup(mode,path,f);const pid_t child=::fork();check(child>=0,"crash fork failed");
      if(child==0){Hook hook;hook.crash_at=point;hook.crash_after=after;Installed install(hook);try{exercise(mode,path,f,account);}catch(...){::_exit(3);}::_exit(4);}
      int status=0;check(::waitpid(child,&status,0)==child && WIFEXITED(status) && WEXITSTATUS(status)==77,"crash hook missed actual syscall");
      surviving(mode,path,f,account);
      for(const auto& e:std::filesystem::directory_iterator(dir.name))if(e.path().filename().native().starts_with(".crown-journal-"))std::filesystem::remove(e.path());
      ++total;
    }
  }
  std::cout<<"journal process exits before/after every actual syscall="<<total<<" surviving prefix/lock release passed (not power-loss simulation)\n";
}
}
int main(int argc,char** argv){try{check(argc==3,"expected mode and fixtures");const Frames f(argv[2]);if(std::string_view(argv[1])=="crash")crashes(f);else faults(f);}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
