#include "session_journal_fixture.hpp"
#include "journal_file_probe.hpp"
#include <sys/wait.h>
#include <cerrno>
using namespace crown;
using namespace crown::runtime;
using namespace crown::session_journal_test;
namespace {
struct Hook {
  std::uint64_t count=0,fail_at=0,crash_at=0;bool after=false,deny_after_sync=false;
  std::array<jp::testing::FileEvent,128> events{};std::size_t size=0;
  static jp::testing::FileDecision call(const jp::testing::FileEvent& event,void* data) noexcept {
    auto& h=*static_cast<Hook*>(data);if(!event.after)++h.count;if(h.size<h.events.size())h.events[h.size++]=event;
    if(h.crash_at==h.count && event.after==h.after)::_exit(77);
    if(h.deny_after_sync && event.after && event.stage==jp::FileStage::sync_file && event.result==0)s04_alloc::remaining=0;
    jp::testing::FileDecision result;if(!event.after && h.fail_at==h.count){if(h.after)result.error_after=EIO;else result.error_before=EIO;}return result;
  }
};
struct Installed {explicit Installed(Hook& hook){jp::testing::set_file_hook(Hook::call,&hook);}~Installed(){jp::testing::set_file_hook(nullptr,nullptr);}};
void attempt(Fixture& f,bool commit){if(commit)f.session->commit();else check(f.session->begin_next(),"journal input missing");}
Hook trace(bool commit) {Fixture f;f.offer();if(commit)f.prepare();Hook hook;{Installed installed(hook);attempt(f,commit);}return hook;}
struct WindowFixture {
  Directory directory;QuerySession::Owner session;
  std::string checkpoint,log;
  unsigned kind;
  std::optional<WindowCanonicalState> before_window;
  explicit WindowFixture(unsigned mode):session(QuerySession::create_windowed(window::plan(false),window::config(WindowFifoPolicy::global))),
      checkpoint(directory.file("base.crown")),log(directory.file("query.wal")),kind(mode) {
    session->start();static_cast<void>(window::command(*session,{1,io::WindowInsert{1,TableId{0},Row{std::int64_t{1}},1},{}}));
    static_cast<void>(window::command(*session,{2,io::WindowInsert{2,TableId{0},Row{std::int64_t{2}},2},{}}));
    static_cast<void>(session->checkpoint_file(checkpoint));session->enable_journal(checkpoint,log,options());
    const io::WindowCommand command=mode==1?io::WindowCommand{3,io::WindowInsert{3,TableId{0},Row{std::int64_t{1}},3},{}}:io::WindowCommand{3,io::AdvanceWatermark{30},{}};
    typed::enqueue(*session,command);before_window=session->window_state();
    if(mode>=1) {
      check(session->begin_next(),"window fault head missing");
      if(mode==3){static_cast<void>(typed::finish(*session));check(session->progress().sequence==2,"partial watermark prematurely accepted source");before_window=session->window_state();check(session->begin_next(),"second watermark step missing");}
      while(session->step()!=DeltaStep::prepared){}
    }
  }
  void attempt(){if(kind==0)check(session->begin_next(),"window input missing");else session->commit();}
};
Hook window_trace(unsigned kind){WindowFixture f(kind);Hook hook;{Installed installed(hook);f.attempt();}return hook;}
void window_faults() {
  std::size_t cases=0;
  for(unsigned kind=0;kind<4;++kind) {
    const auto baseline=window_trace(kind);
    for(std::uint64_t point=1;point<=baseline.count;++point)for(const bool after:{false,true}) {
      WindowFixture f(kind);const auto before=f.before_window;const auto sequence=f.session->status().committed_sequence;Hook hook;hook.fail_at=point;hook.after=after;bool failed=false;
      {Installed installed(hook);try{f.attempt();}catch(const jp::FileFailure&){failed=true;}}
      check(failed && f.session->journal_state().recovery_required && f.session->status().committed_sequence==sequence &&
          f.session->progress().sequence==2 && f.session->window_state()==before,"window I/O error published metadata/physical step or acknowledged command");
      const auto data=contents(f.log);const auto state=jp::scan(data);check(state.command_sequence>=2 && state.command_sequence<=3,"window failure lost base progress");++cases;
    }
    if(kind>0){WindowFixture f(kind);Hook hook;hook.deny_after_sync=true;{s04_alloc::Scope count;Installed installed(hook);f.attempt();}
      check(!f.session->journal_state().recovery_required,"window publication failed after durable sync");}
  }
  std::cout<<"session window actual before/after syscall errors="<<cases<<" input, metadata, first/final physical watermark and nonalloc publication passed\n";
}
void faults() {
  std::size_t cases=0;
  for(const bool commit:{false,true}) {
    const auto baseline=trace(commit);
    for(std::uint64_t point=1;point<=baseline.count;++point)for(const bool after:{false,true}) {
      Fixture f;f.offer();if(commit)f.prepare();Hook hook;hook.fail_at=point;hook.after=after;bool rejected=false;
      {Installed installed(hook);try{attempt(f,commit);}catch(const jp::FileFailure&){rejected=true;}}
      check(rejected && f.session->journal_state().recovery_required && f.session->status().committed_sequence==0 && f.session->progress().sequence==0,"journal I/O failure published native epoch or allowed reuse");
      bool blocked=false;try{static_cast<void>(f.session->next_output());}catch(const SessionJournalFailure& e){blocked=e.fault()==SessionJournalFault::recovery_required;}check(blocked,"uncertain journal exposed output");
      const auto saved=contents(f.log);const auto state=jp::scan(saved);check(state.command_sequence<=1 && (commit || state.command_sequence==0),"failed append minted invalid durable sequence");
      const auto header=jp::inspect(frames(saved).front()).header;const auto account=f.session.get_deleter().account();f.session.reset();auto reopened=jp::File::open(account,f.log,header);reopened.close();++cases;
    }
    Fixture f;f.offer();if(!commit){check(f.session->begin_next(),"nonalloc fixture missing");while(f.session->step()!=DeltaStep::prepared){}}
    else {f.prepare();}
    Hook nonalloc;nonalloc.deny_after_sync=true;
    {s04_alloc::Scope count;Installed installed(nonalloc);f.session->commit();}
    check(f.session->status().committed_sequence==1 && f.session->progress().sequence==1,"native publication allocated after durable decision");
  }
  {Fixture f(false,1);f.offer();check(f.session->begin_next(),"drain nonalloc fixture missing");f.session->pause();Hook hook;hook.deny_after_sync=true;
    {s04_alloc::Scope count;Installed installed(hook);f.session->start_drain();f.session->drain();}
    check(f.session->status().committed_sequence==1 && f.session->progress().sequence==1,"drain publication allocated after durable decision");}
  std::cout<<"session input/decision actual before/after syscall errors="<<cases<<" rollback/no-output/recovery-required, lock release and no-allocation durable publication passed\n";
}
void crashes() {
  std::size_t count=0;
  for(const bool commit:{false,true}) {
    const auto baseline=trace(commit);
    for(std::uint64_t point=1;point<=baseline.count;++point)for(const bool after:{false,true}) {
      Fixture f;f.offer();if(commit)f.prepare();const auto original=contents(f.log);const auto header=jp::inspect(frames(original).front()).header;
      // Parent releases its inherited lock after the child exits; its stale
      // native memory is discarded before a new owner opens the actual file.
      const pid_t child=::fork();check(child>=0,"fork failed");if(child==0){Hook hook;hook.crash_at=point;hook.after=after;Installed installed(hook);try{attempt(f,commit);}catch(...){::_exit(3);}::_exit(4);}
      int status=0;check(::waitpid(child,&status,0)==child && WIFEXITED(status) && WEXITSTATUS(status)==77,"session syscall crash hook missed");
      const auto account=f.session.get_deleter().account();f.session.reset();auto file=jp::File::open(account,f.log,header);const auto state=file.state();
      check(state.command_sequence<=1 && (commit || state.command_sequence==0) && (!commit || state.pending || state.command_sequence==1),"session crash lost valid input/decision boundary");file.close();++count;
    }
  }
  std::cout<<"session input/decision process exits before/after actual syscalls="<<count<<" durable prefix/lock release passed; native replay factory remains pending\n";
}
}
int main(int argc,char** argv){try{check(argc==2,"expected mode");if(std::string_view(argv[1])=="crash")crashes();else {faults();window_faults();}}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
