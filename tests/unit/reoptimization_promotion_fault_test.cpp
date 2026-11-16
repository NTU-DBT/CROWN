#include "selection_independent_fixture.hpp"
#include "indexed_runtime_fixture.hpp"
#include "local_sink_fixture.hpp"
#include "generation_file_probe.hpp"
#include "journal_file_probe.hpp"
#include "crown/runtime/session_reoptimization.hpp"
#include <cerrno>
#include <iostream>
#include <sys/wait.h>

namespace {
using namespace crown;
using namespace crown::runtime;
using c05_independent::check;
struct Fixture {
  session_file_test::Directory directory;
  std::string root=directory.file("query.root"),checkpoint=directory.file("original.ckpt"),wal=directory.file("original.wal"),sink=directory.file("results.sink");
  QuerySession::Owner session;
  std::string old_checkpoint,old_wal,old_sink;
  recovery::sink::Header origin;
  Fixture(const PhysicalPlan& plan,const Database& initial):session(QuerySession::create_typed(plan,initial)) {
    session->start();static_cast<void>(session->checkpoint_file(checkpoint));session->enable_journal(checkpoint,wal,session_journal_test::options());
    session->create_local_sink(sink,local_sink_test::options());origin=session->local_sink_state().persisted.header;
    commit(1,TableId{0},SetOperation::insert,*initial.tables[0].begin());
    commit(2,TableId{1},SetOperation::erase,*initial.tables[1].begin());
    commit(3,TableId{1},SetOperation::insert,*initial.tables[1].begin());session->pause();
    old_checkpoint=session_file_test::contents(checkpoint);old_wal=session_file_test::contents(wal);old_sink=session_file_test::contents(sink);
  }
  void commit(std::uint64_t sequence,TableId table,SetOperation operation,const Row& row) {
    io::TransportBatch batch({io::InputEvent{{sequence,table,operation,row},io::SourcePosition{"wire",sequence*10}}});
    check(session->enqueue(batch)==io::Admission::accepted && session->begin_next(),"promotion input missing");
    local_sink_test::finish(*session);check(session->deliver_local_epoch().sequence==sequence,"promotion prefix delivery missing");
  }
  void promote() {session->promote_journal(root,generation_test::options());}
  void original() const {
    check(session_file_test::contents(checkpoint)==old_checkpoint && session_file_test::contents(wal)==old_wal &&
        session_file_test::contents(sink)==old_sink,"promotion changed original durable bytes");
  }
  void recover(const PhysicalPlan& plan,const Database& initial) {
    session.reset();const auto program=CompiledProgram::standalone(plan);const bool selected=std::filesystem::exists(root);
    if(selected)session=QuerySession::restore_generation_with_local_sink(program,root,generation_test::recovery_options(),sink,local_sink_test::options());
    else {SessionJournalRecoveryOptions options;options.journal=session_journal_test::options();session=QuerySession::restore_journal_with_local_sink(program,checkpoint,wal,options,sink,local_sink_test::options());}
    original();
    check(session->status().committed_sequence==3 && session->progress().sequence==3 && session->status().state==SessionState::paused &&
        session->snapshot().rows.size()==1 && session->local_sink_state().verified_sequence==3 && session->local_sink_state().persisted.header==origin,
        "promotion recovered a partial input/result/sink boundary");
    if(selected)check(session->generation_state().selected.generation==2 && session->generation_state().selected.first_generation==2 &&
        session->generation_state().selected.delivery.has_value(),"promotion recovered a wrong managed floor/prefix");
    session->start();commit(4,TableId{1},SetOperation::erase,*initial.tables[1].begin());
    const auto epoch=session->read_local_epoch(4);
    check(epoch.generation==(selected?2U:1U) && epoch.rows.size()==1 && session->snapshot().rows.empty(),"promotion next native output differs");
  }
};
struct Hook {
  std::uint64_t count=0,fail=0,crash=0;
  bool after=false,checkpoint_synced=false,wal_synced=false,reached=false,order_violation=false,deny=false;
  void visit(bool done) noexcept {if(!done)++count;if(count==crash && done==after)::_exit(77);}
  template<class Decision> Decision decision(bool done) const noexcept {
    Decision result;if(!done && count==fail){if(after)result.error_after=EIO;else result.error_before=EIO;}return result;
  }
  static recovery::testing::GenerationDecision generation(const recovery::testing::GenerationEvent& event,void* context) noexcept {
    auto& self=*static_cast<Hook*>(context);self.visit(event.after);
    if(event.after && event.result>=0 && event.native_error==0 && event.target==recovery::GenerationTarget::checkpoint && event.stage==recovery::GenerationStage::sync_directory)self.checkpoint_synced=true;
    if(!event.after && event.target==recovery::GenerationTarget::root && event.stage==recovery::GenerationStage::link_file) {
      self.reached=true;if(!self.checkpoint_synced || !self.wal_synced)self.order_violation=true;if(self.deny)s04_alloc::remaining=0;
    }
    return self.decision<recovery::testing::GenerationDecision>(event.after);
  }
  static recovery::journal::testing::FileDecision journal(const recovery::journal::testing::FileEvent& event,void* context) noexcept {
    auto& self=*static_cast<Hook*>(context);self.visit(event.after);
    if(event.after && event.result>=0 && event.native_error==0 && event.stage==recovery::journal::FileStage::sync_directory)self.wal_synced=true;
    return self.decision<recovery::journal::testing::FileDecision>(event.after);
  }
};
struct Installed {
  explicit Installed(Hook& hook) {recovery::testing::set_generation_hook(Hook::generation,&hook);recovery::journal::testing::set_file_hook(Hook::journal,&hook);}
  ~Installed() {recovery::testing::set_generation_hook(nullptr,nullptr);recovery::journal::testing::set_file_hook(nullptr,nullptr);}
};
std::uint64_t trace(const PhysicalPlan& plan,const Database& initial) {
  Fixture fixture(plan,initial);Hook hook;hook.deny=true;bool triggered=false;
  {s04_alloc::Scope count;Installed installed(hook);fixture.promote();triggered=s04_alloc::triggered;}
  check(hook.reached && !hook.order_violation && !triggered && fixture.session->status().state==SessionState::paused,"promotion selected unsynced files, allocated after selection or changed pause");
  fixture.original();fixture.recover(plan,initial);return hook.count;
}
std::size_t io_cuts(const PhysicalPlan& plan,const Database& initial,std::uint64_t boundaries) {
  std::size_t cuts=0;
  for(std::uint64_t point=1;point<=boundaries;++point)for(const bool after:{false,true}) {
    Fixture fixture(plan,initial);Hook hook;hook.fail=point;hook.after=after;bool failed=false;
    {Installed installed(hook);try{fixture.promote();}catch(const recovery::GenerationFailure&){failed=true;}catch(const recovery::journal::FileFailure&){failed=true;}}
    check(failed,"promotion ignored a persistence failure");fixture.original();
    if(fixture.session->journal_state().recovery_required) {
      bool blocked=false;try{static_cast<void>(fixture.session->begin_next());}catch(const SessionJournalFailure& failure){blocked=failure.fault()==SessionJournalFault::recovery_required;}
      check(blocked,"ambiguous promotion admitted input");
      bool busy=false;try{static_cast<void>(QuerySession::lock_generation_recovery(CompiledProgram::standalone(plan),fixture.root,generation_test::recovery_options()));}
      catch(const recovery::GenerationFailure& failure){busy=failure.fault()==recovery::GenerationFault::busy;}
      check(busy,"ambiguous promotion released the root lock");
    }else check(!fixture.session->generation_state().enabled && fixture.session->status().committed_sequence==3,"preselection promotion fault changed managed owner");
    fixture.recover(plan,initial);++cuts;
  }
  return cuts;
}
std::size_t crash_cuts(const PhysicalPlan& plan,const Database& initial,std::uint64_t boundaries) {
  std::size_t cuts=0;
  for(std::uint64_t point=1;point<=boundaries;++point)for(const bool after:{false,true}) {
    Fixture fixture(plan,initial);const auto child=::fork();check(child>=0,"promotion fork failed");
    if(child==0){Hook hook;hook.crash=point;hook.after=after;Installed installed(hook);fixture.promote();::_exit(0);}
    int status=0;check(::waitpid(child,&status,0)==child && WIFEXITED(status) && WEXITSTATUS(status)==77,"promotion process crash was not exercised");
    fixture.original();fixture.recover(plan,initial);++cuts;
  }
  return cuts;
}
std::size_t allocations(const PhysicalPlan& plan,const Database& initial) {
  std::size_t count=0;
  {Fixture fixture(plan,initial);const auto account=fixture.session->report_metadata().plan().account();const auto before=account.statistics().successful_allocations;
    {s04_alloc::Scope scope;fixture.promote();count=s04_alloc::calls;}
    check(count==account.statistics().successful_allocations-before,"promotion allocations escaped original query account");}
  check(count>0 && count<10000,"promotion allocation count invalid");
  for(std::size_t point=0;point<count;++point) {
    Fixture fixture(plan,initial);bool failed=false,triggered=false;
    {s04_alloc::Scope scope(static_cast<std::ptrdiff_t>(point));try{fixture.promote();}catch(const std::bad_alloc&){failed=true;}triggered=s04_alloc::triggered;}
    check(failed && triggered && !fixture.session->generation_state().enabled && !fixture.session->journal_state().recovery_required,
        "promotion allocation failure changed authoritative state");fixture.original();fixture.recover(plan,initial);
  }
  return count;
}
} // namespace
int main(int argc,char** argv) {
  try {
    check(argc==3,"usage: reoptimization_promotion_fault SOURCE io|crash|allocation");const auto fixture=c05_independent::boolean_fixture(argv[1]);std::size_t cuts=0;
    for(const bool indexed:{false,true}) {
      const auto plan=c05_independent::lower(*fixture.all.candidate(0),indexed?s04_runtime::options():PhysicalOptions{});
      const auto boundaries=trace(plan,fixture.initial);
      if(std::string_view(argv[2])=="io")cuts+=io_cuts(plan,fixture.initial,boundaries);
      else if(std::string_view(argv[2])=="crash")cuts+=crash_cuts(plan,fixture.initial,boundaries);
      else cuts+=allocations(plan,fixture.initial);
    }
    std::cout<<"C06 journal promotion "<<argv[2]<<" PASS: "<<cuts<<" actual cuts across both backends at delivered B=3; immutable unmanaged files/sink origin, retained uncertain root lock, exact old/new recovery and next output, original account and no allocation after selection.\n";return 0;
  }catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}
