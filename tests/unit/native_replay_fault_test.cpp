#include "session_journal_fixture.hpp"
#include "journal_file_probe.hpp"
#include <sys/wait.h>
#include <fstream>
#include <cerrno>
using namespace crown;
using namespace crown::runtime;
using namespace crown::session_journal_test;
namespace {
struct Saved {
  Fixture fixture{false,1};
  CompiledProgram compiler;
  std::string bytes;
  explicit Saved(bool torn=false):compiler(CompiledProgram::standalone(fixture.test.plan)) {
    for(std::size_t i=0;i<2;++i){fixture.offer(i);fixture.prepare();fixture.session->commit();while(fixture.session->next_output()){}}
    fixture.offer(2);fixture.prepare();fixture.session.reset();bytes=contents(fixture.log);
    if(torn){const auto records=frames(bytes);const auto input=jp::inspect(records.back());jp::Commit decision{input.ordinal,input.body_sha256,jp::CommitKind::physical,3,3,0,true};auto account=resource::MemoryAccount::create(1024*1024);const auto encoded=jp::encode(account,6,jp::PayloadView{decision});bytes.append(encoded.bytes.data(),20);write(bytes);}
  }
  void write(std::string_view data){std::ofstream out(fixture.log,std::ios::binary|std::ios::trunc);out.write(data.data(),static_cast<std::streamsize>(data.size()));check(static_cast<bool>(out),"fault fixture write failed");}
  SessionJournalRecoveryOptions options() const {SessionJournalRecoveryOptions result;result.journal=session_journal_test::options();return result;}
  QuerySession::Owner restore() const {return QuerySession::restore_journal(compiler,fixture.checkpoint,fixture.log,options());}
};
struct Hook {
  std::uint64_t count=0,fail=0,crash=0;bool after=false,repeat_interrupt=false;
  std::size_t maximum=SIZE_MAX;
  static jp::testing::FileDecision call(const jp::testing::FileEvent& event,void* context) noexcept {
    auto& hook=*static_cast<Hook*>(context);if(!event.after)++hook.count;
    if(hook.count==hook.crash && event.after==hook.after)::_exit(77);
    jp::testing::FileDecision result;if(!event.after){result.maximum_transfer=hook.maximum;if(hook.repeat_interrupt && event.stage==jp::FileStage::read_data)result.error_before=EINTR;if(hook.count==hook.fail){if(hook.after)result.error_after=EIO;else result.error_before=EIO;}}return result;
  }
};
struct Installed {explicit Installed(Hook& h){jp::testing::set_file_hook(Hook::call,&h);}~Installed(){jp::testing::set_file_hook(nullptr,nullptr);}};
void verify(QuerySession& session) {
  check(session.status().state==SessionState::paused && session.progress().sequence==2 && session.status().committed_sequence==2 && session.recovery_status().pending_input_sequence==3,"recovery fault changed native/source boundary");
  std::size_t outputs=0;while(auto value=session.next_recovered_output()){check(value->physical_sequence==2 && value->value.tuple.values()==Row{std::int64_t{1},std::int64_t{2},std::int64_t{3}},"recovered fault output differs");++outputs;}check(outputs==1,"recovered fault lost staged output");
}
void allocation_faults() {
  Saved saved;std::size_t allocations=0;std::uint64_t peak=0;
  {std::optional<QuerySession::Owner> result;{s04_alloc::Scope count;result.emplace(saved.restore());allocations=s04_alloc::calls;}
    const auto account=result->get_deleter().account();check(allocations==account.statistics().successful_allocations,"native recovery escaped receiving memory account");peak=account.statistics().peak_requested_bytes;verify(**result);}
  for(std::size_t i=0;i<allocations;++i){const auto fds=descriptors();bool failed=false;
    {s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(i));try{auto value=saved.restore();}catch(const std::bad_alloc&){failed=true;}}
    check(failed && descriptors()==fds && contents(saved.fixture.log)==saved.bytes,"recovery OOM leaked or mutated log");
  }
  auto exact=saved.options();exact.memory_limit_bytes=peak;{auto value=QuerySession::restore_journal(saved.compiler,saved.fixture.checkpoint,saved.fixture.log,exact);verify(*value);}
  --*exact.memory_limit_bytes;bool under=false;try{auto value=QuerySession::restore_journal(saved.compiler,saved.fixture.checkpoint,saved.fixture.log,exact);}catch(const resource::MemoryFailure& e){under=e.fault()==resource::MemoryFault::limit;}check(under,"one-under native recovery receiving cap accepted");
  std::cout<<"native recovery allocations="<<allocations<<" every allocation fault/exact-under query memory/descriptor/account ownership passed\n";
}
Hook trace(Saved& saved){saved.write(saved.bytes);Hook h;{Installed installed(h);auto value=saved.restore();}return h;}
void io_faults() {
  std::size_t cases=0;
  for(const bool torn:{false,true}) {
    Saved saved(torn);const auto baseline=trace(saved);
    for(std::uint64_t point=1;point<=baseline.count;++point)for(const bool after:{false,true}) {
      saved.write(saved.bytes);const auto fds=descriptors();Hook h;h.fail=point;h.after=after;bool failed=false;
      {Installed installed(h);try{auto value=saved.restore();}catch(const jp::FileFailure&){failed=true;}}
      check(failed && descriptors()==fds,"recovery syscall error escaped/leaked descriptor");const auto actual=contents(saved.fixture.log);
      check(actual==saved.bytes || (torn && actual==saved.bytes.substr(0,saved.bytes.size()-20)),"recovery failure discarded complete input or changed committed prefix");
      {auto value=saved.restore();verify(*value);}++cases;
    }
    saved.write(saved.bytes);Hook short_read;short_read.maximum=3;{Installed installed(short_read);auto value=saved.restore();verify(*value);}
    saved.write(saved.bytes);Hook interrupted;interrupted.repeat_interrupt=true;auto limits=saved.options();limits.journal.file.operations=30;bool bounded=false;
    {Installed installed(interrupted);try{auto value=QuerySession::restore_journal(saved.compiler,saved.fixture.checkpoint,saved.fixture.log,limits);}catch(const jp::FileFailure& e){bounded=e.fault()==jp::FileFault::limit;}}
    check(bounded && contents(saved.fixture.log)==saved.bytes,"repeated recovery interruption bypassed quota or mutated log");
    std::cout<<"native recovery I/O torn="<<torn<<" actual boundaries="<<baseline.count<<" before/after errors, short reads and interruption quota passed\n";
  }
  std::cout<<"native recovery actual syscall failure cases="<<cases<<" full prefix/native re-open/output validation passed\n";
}
void crashes() {
  std::size_t cases=0;
  for(const bool torn:{false,true}) {
    Saved saved(torn);const auto baseline=trace(saved);
    for(std::uint64_t point=1;point<=baseline.count;++point)for(const bool after:{false,true}) {
      saved.write(saved.bytes);const auto child=::fork();check(child>=0,"fork failed");
      if(child==0){Hook h;h.crash=point;h.after=after;Installed installed(h);try{auto value=saved.restore();}catch(...){::_exit(3);}::_exit(4);}
      int status=0;check(::waitpid(child,&status,0)==child && WIFEXITED(status) && WEXITSTATUS(status)==77,"recovery crash boundary missed");
      auto value=saved.restore();verify(*value);++cases;
    }
  }
  std::cout<<"native recovery process exits before/after actual syscalls="<<cases<<" state/source/replayed output and pending-input recovery passed (not power-loss simulation)\n";
}
}
int main(int argc,char** argv){try{check(argc==2,"expected mode");if(std::string_view(argv[1])=="crash")crashes();else{allocation_faults();io_faults();}}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
