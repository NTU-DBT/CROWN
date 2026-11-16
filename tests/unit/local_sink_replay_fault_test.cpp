#include "sink_replay_fixture.hpp"
#include "local_sink_probe.hpp"
#include "journal_file_probe.hpp"
#include <cerrno>
#include <sys/wait.h>
using namespace crown;
using namespace crown::runtime;
using namespace crown::sink_replay_test;
namespace {
namespace jp=recovery::journal;
enum class Channel {sink,journal};
struct Hook {
  std::uint64_t count=0,fail=0,crash=0;bool after=false,interrupt=false;
  std::size_t maximum=SIZE_MAX;
  void event(bool is_after) noexcept {if(!is_after)++count;if(count==crash && is_after==after)::_exit(77);}
  static sk::testing::Decision sink(const sk::testing::Event& event,void* context) noexcept {
    auto& h=*static_cast<Hook*>(context);h.event(event.after);sk::testing::Decision result;
    if(!event.after){result.maximum_transfer=h.maximum;if(h.interrupt && event.stage==sk::Stage::read_data)result.error_before=EINTR;if(h.count==h.fail){if(h.after)result.error_after=EIO;else result.error_before=EIO;}}return result;
  }
  static jp::testing::FileDecision journal(const jp::testing::FileEvent& event,void* context) noexcept {
    auto& h=*static_cast<Hook*>(context);h.event(event.after);jp::testing::FileDecision result;
    if(!event.after){result.maximum_transfer=h.maximum;if(h.interrupt && event.stage==jp::FileStage::read_data)result.error_before=EINTR;if(h.count==h.fail){if(h.after)result.error_after=EIO;else result.error_before=EIO;}}return result;
  }
};
struct Installed {
  Installed(Channel channel,Hook& hook){if(channel==Channel::sink)sk::testing::set_hook(Hook::sink,&hook);else jp::testing::set_file_hook(Hook::journal,&hook);}
  ~Installed(){sk::testing::set_hook(nullptr,nullptr);jp::testing::set_file_hook(nullptr,nullptr);}
};
struct Files {
  Saved saved;
  std::string sink,wal,clean_sink,clean_wal;
  explicit Files(bool torn) {
    saved.prefix(2,torn);sink=contents(saved.source.path);clean_wal=contents(saved.log);const auto frames=session_journal_test::frames(saved.sink);
    clean_sink=std::string(frames[0])+std::string(frames[1])+std::string(frames[2]);wal=clean_wal;
    if(torn){const auto entries=session_journal_test::frames(clean_wal);wal.append(entries[1].substr(0,85));}reset();
  }
  void reset(){generation_test::put(saved.source.path,sink);generation_test::put(saved.log,wal);}
  void intact() const {
    const auto actual_sink=contents(saved.source.path),actual_wal=contents(saved.log);
    check((actual_sink==sink || actual_sink==clean_sink) && (actual_wal==wal || actual_wal==clean_wal),"sink-aware failure/crash changed complete persisted prefixes");
  }
};
Hook trace(Files& files,Channel channel) {
  files.reset();Hook hook;std::optional<QuerySession::Owner> value;{Installed installed(channel,hook);value.emplace(files.saved.restore());}return hook;
}
void failures() {
  std::size_t cases=0;
  for(const bool torn:{false,true})for(const auto channel:{Channel::sink,Channel::journal}) {
    Files files(torn);const auto baseline=trace(files,channel);
    for(std::uint64_t point=1;point<=baseline.count;++point)for(const bool after:{false,true}) {
      files.reset();const auto before=descriptors();Hook hook;hook.fail=point;hook.after=after;bool failed=false;
      {Installed installed(channel,hook);try{auto value=files.saved.restore();}catch(const sk::Failure&){failed=channel==Channel::sink;}catch(const jp::FileFailure&){failed=channel==Channel::journal;}}
      check(failed && descriptors()==before,"sink-aware factory ignored file error or leaked locks");files.intact();files.saved.verify();++cases;
    }
    files.reset();Hook short_io;short_io.maximum=3;{Installed installed(channel,short_io);auto value=files.saved.restore();check(value->local_sink_state().verified_sequence==2,"short I/O changed verified prefix");}files.saved.verify();
    files.reset();Hook interruption;interruption.interrupt=true;auto recovery=generation_test::recovery_options();auto delivery=options();if(channel==Channel::sink)delivery.file.operations=30;else recovery.replay.journal.file.operations=30;bool bounded=false;
    {Installed installed(channel,interruption);try{auto value=files.saved.restore(recovery,delivery);}catch(const sk::Failure& e){bounded=channel==Channel::sink && e.fault()==sk::Fault::limit;}catch(const jp::FileFailure& e){bounded=channel==Channel::journal && e.fault()==jp::FileFault::limit;}}
    check(bounded && contents(files.saved.source.path)==files.sink && contents(files.saved.log)==files.wal,"sink-aware interrupted reads escaped copied finite quotas or repaired early");
    std::cout<<"sink-aware I/O channel="<<static_cast<unsigned>(channel)<<" torn="<<torn<<" actual boundaries="<<baseline.count<<" before/after errors/short I/O/finite interruptions passed\n";
  }
  std::cout<<"sink-aware actual syscall errors="<<cases<<" complete native state/source/output/dedup/next update passed\n";
}
void crashes() {
  std::size_t cases=0;
  for(const bool torn:{false,true})for(const auto channel:{Channel::sink,Channel::journal}) {
    Files files(torn);const auto baseline=trace(files,channel);
    for(std::uint64_t point=1;point<=baseline.count;++point)for(const bool after:{false,true}) {
      files.reset();const auto child=::fork();check(child>=0,"sink-aware crash fork failed");
      if(child==0){Hook hook;hook.crash=point;hook.after=after;Installed installed(channel,hook);try{auto value=files.saved.restore();}catch(...){::_exit(3);}::_exit(4);}
      int status=0;check(::waitpid(child,&status,0)==child && WIFEXITED(status) && WEXITSTATUS(status)==77,"sink-aware crash boundary missed");files.intact();files.saved.verify();++cases;
    }
  }
  std::cout<<"sink-aware process exits="<<cases<<" each actual sink/WAL boundary/native state/source/output/next update passed (not power loss)\n";
}
void allocations() {
  Files files(false);std::size_t count=0;std::uint64_t peak=0;
  {std::optional<QuerySession::Owner> value;{s04_alloc::Scope scope;value.emplace(files.saved.restore());count=s04_alloc::calls;}
    const auto account=value->get_deleter().account();check(count==account.statistics().successful_allocations,"sink-aware reconstruction escaped the receiving account");peak=account.statistics().peak_requested_bytes;
  }
  for(std::size_t point=0;point<count;++point) {
    const auto before=descriptors();bool failed=false;{s04_alloc::Scope scope(static_cast<std::ptrdiff_t>(point));try{auto value=files.saved.restore();}catch(const std::bad_alloc&){failed=true;}}
    check(failed && descriptors()==before && contents(files.saved.source.path)==files.sink && contents(files.saved.log)==files.wal,"sink-aware allocation failure leaked owner/output or changed files");
  }
  auto recovery=generation_test::recovery_options();recovery.replay.memory_limit_bytes=peak;{auto value=files.saved.restore(recovery);check(value->local_sink_state().verified_sequence==2,"sink-aware exact receiving memory cap rejected");}
  --*recovery.replay.memory_limit_bytes;bool under=false;try{auto value=files.saved.restore(recovery);}catch(const resource::MemoryFailure& e){under=e.fault()==resource::MemoryFault::limit;}check(under,"sink-aware one-under receiving memory cap accepted");
  files.saved.verify();std::cout<<"sink-aware receiving allocations="<<count<<" every fault/account ownership/exact-under heap/native retry passed\n";
}
}
int main(int argc,char** argv){try{check(argc==2,"expected sink-aware fault mode");if(std::string_view(argv[1])=="crash")crashes();else{allocations();failures();}}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
