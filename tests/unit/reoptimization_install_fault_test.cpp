#include "selection_independent_fixture.hpp"
#include "indexed_runtime_fixture.hpp"
#include "local_sink_fixture.hpp"
#include "generation_file_probe.hpp"
#include "journal_file_probe.hpp"
#include "crown/io/compiler_plan_artifact.hpp"
#include "crown/runtime/session_reoptimization.hpp"
#include <cerrno>
#include <iostream>
#include <sys/wait.h>

namespace {
using namespace crown;
using namespace crown::runtime;
using c05_independent::check;
reoptimization::Options options() {
  reoptimization::Options value;value.forecast=reoptimization::Forecast{1'000'000'000,1,UINT64_MAX};return value;
}
Relation rows(QuerySession& session) {
  Relation result;for(const auto& row:session.snapshot().rows)result.insert(storage::export_row(row.values()));return result;
}
struct Fixture {
  session_file_test::Directory directory;
  std::string root=directory.file("query.root"),sink=directory.file("query.sink");
  QuerySession::Owner session;
  std::string before,checkpoint,wal,sink_bytes;
  SupportOwnerId old_owner{};
  Fixture(const PhysicalPlan& plan,const planner::MinimumHeightCandidate& candidate,const Database& initial)
      :session(QuerySession::create_typed(plan,initial)) {
    session->start();session->enable_generation(root,generation_test::options());session->create_local_sink(sink,local_sink_test::options());
    commit(1,TableId{0},SetOperation::insert,*initial.tables[0].begin());
    check(session->read_local_epoch(1).rows.empty(),"install fault fixture lost its physical no-op epoch");
    session->begin_reoptimization(candidate,options());
    commit(2,TableId{1},SetOperation::erase,*initial.tables[1].begin());
    commit(3,TableId{1},SetOperation::insert,*initial.tables[1].begin());
    session->request_reoptimization_barrier();const auto ready=session->advance_reoptimization(100000);
    check(ready.phase==reoptimization::Phase::verified && ready.snapshot_epoch==1 && ready.target_epoch==3 && ready.replayed_records==2 &&
        session->local_sink_state().verified_sequence==3,"install fault fixture did not catch up and deliver through nonzero B");
    before=session_file_test::contents(root);checkpoint=session_file_test::contents(generation_test::path(root,1,".ckpt"));
    wal=session_file_test::contents(generation_test::path(root,1,".wal"));sink_bytes=session_file_test::contents(sink);old_owner=session->report_metadata().owner();
  }
  void commit(std::uint64_t sequence,TableId table,SetOperation operation,const Row& row) {
    io::TransportBatch batch({io::InputEvent{{sequence,table,operation,row},io::SourcePosition{"wire",sequence*10}}});
    check(session->enqueue(batch)==io::Admission::accepted && session->begin_next(),"install fault prefix input missing");
    local_sink_test::finish(*session);check(session->deliver_local_epoch().sequence==sequence,"install fault prefix delivery missing");
  }
  void historical() const {
    check(session_file_test::contents(generation_test::path(root,1,".ckpt"))==checkpoint &&
        session_file_test::contents(generation_test::path(root,1,".wal"))==wal && session_file_test::contents(sink)==sink_bytes,
        "installation fault changed rollback files/sink prefix");
  }
  void recover(const PhysicalPlan& original,const Database& initial) {
    session.reset();auto locked=QuerySession::lock_generation_recovery(CompiledProgram::standalone(original),root,generation_test::recovery_options());
    const auto compiler=resource::MemoryAccount::create(16*1024*1024);
    auto artifact=locked->has_plan()?io::CompilerPlanArtifact::replay(compiler,locked->compiler_artifact()):io::CompilerPlanArtifact::prepare(compiler,original);
    session=QuerySession::restore_selected_generation_with_local_sink(std::move(locked),artifact,sink,local_sink_test::options());
    const auto selected=session->generation_state().selected;
    check((selected.generation==1 || selected.generation==2) && session->status().committed_sequence==3 && session->progress().sequence==3 &&
        session->local_sink_state().verified_sequence==3 && rows(*session)==Relation{Row{}},
        "installation fault recovered a partial plan/epoch");
    session->start();io::TransportBatch batch({io::InputEvent{{4,TableId{1},SetOperation::erase,*initial.tables[1].begin()},{}}});
    check(session->enqueue(batch)==io::Admission::accepted && session->begin_next(),"installation fault lost next input");
    local_sink_test::finish(*session);const auto output=session->deliver_local_epoch();
    check(output.generation==selected.generation && output.sequence==4 && output.rows==1 && rows(*session).empty() && session->progress().sequence==4,
        "installation fault next update differs");
  }
};
struct Hook {
  std::uint64_t count=0,fail=0,crash=0;
  bool after=false,plan_synced=false,checkpoint_synced=false,wal_synced=false,order_violation=false,deny=false,reached=false,absent=false;
  void visit(bool done) noexcept {if(!done)++count;if(count==crash && done==after)::_exit(77);}
  template<class Decision> Decision decision(bool done) const noexcept {
    Decision result;if(!done && count==fail){if(after)result.error_after=EIO;else result.error_before=EIO;}return result;
  }
  static recovery::testing::GenerationDecision generation(const recovery::testing::GenerationEvent& event,void* context) noexcept {
    auto& self=*static_cast<Hook*>(context);self.visit(event.after);
    if(event.after && event.stage==recovery::GenerationStage::unlink_candidate && event.native_error==ENOENT && self.count==self.fail && self.after)self.absent=true;
    if(event.after && event.result>=0 && event.native_error==0 && event.stage==recovery::GenerationStage::sync_directory) {
      if(event.target==recovery::GenerationTarget::plan)self.plan_synced=true;
      if(event.target==recovery::GenerationTarget::checkpoint)self.checkpoint_synced=true;
    }
    if(!event.after && event.target==recovery::GenerationTarget::root && event.stage==recovery::GenerationStage::rename_root) {
      self.reached=true;if(!self.plan_synced || !self.checkpoint_synced || !self.wal_synced)self.order_violation=true;
      if(self.deny)s04_alloc::remaining=0;
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
std::uint64_t trace(const PhysicalPlan& original,const planner::MinimumHeightCandidate& candidate,const Database& initial,const io::CompilerPlanArtifact& artifact) {
  Fixture fixture(original,candidate,initial);Hook hook;hook.deny=true;bool triggered=false;
  {s04_alloc::Scope count;Installed installed(hook);check(fixture.session->publish_reoptimization(artifact).phase==reoptimization::Phase::complete,"fault trace did not complete");triggered=s04_alloc::triggered;}
  check(hook.reached && !hook.order_violation && !triggered,"native installation allocated after root selection or selected unsynced files");return hook.count;
}
std::size_t io_cuts(const PhysicalPlan& original,const planner::MinimumHeightCandidate& candidate,const Database& initial,const io::CompilerPlanArtifact& artifact,std::uint64_t boundaries) {
  std::size_t cuts=0;
  for(std::uint64_t point=1;point<=boundaries;++point)for(const bool after:{false,true}) {
    Fixture fixture(original,candidate,initial);Hook hook;hook.fail=point;hook.after=after;bool failed=false;
    {Installed installed(hook);try{static_cast<void>(fixture.session->publish_reoptimization(artifact));}
      catch(const recovery::GenerationFailure&){failed=true;}catch(const recovery::journal::FileFailure&){failed=true;}}
    check(failed || hook.absent,"native installation ignored a syscall failure");fixture.historical();
    if(fixture.session->journal_state().recovery_required)check(fixture.session->reoptimization_status().phase==reoptimization::Phase::recovery_required,"ambiguous selection left a reusable target");
    else if(failed) {
      check(fixture.session->report_metadata().owner()==fixture.old_owner && session_file_test::contents(fixture.root)==fixture.before,"preselection fault replaced old owner/root");
      check(fixture.session->publish_reoptimization(artifact).phase==reoptimization::Phase::complete,"preselection fault could not retry");
    }
    fixture.recover(original,initial);++cuts;
  }
  return cuts;
}
std::size_t crash_cuts(const PhysicalPlan& original,const planner::MinimumHeightCandidate& candidate,const Database& initial,const io::CompilerPlanArtifact& artifact,std::uint64_t boundaries) {
  std::size_t cuts=0;
  for(std::uint64_t point=1;point<=boundaries;++point)for(const bool after:{false,true}) {
    Fixture fixture(original,candidate,initial);const auto child=::fork();check(child>=0,"native installation fork failed");
    if(child==0){Hook hook;hook.crash=point;hook.after=after;Installed installed(hook);static_cast<void>(fixture.session->publish_reoptimization(artifact));::_exit(0);}
    int status=0;check(::waitpid(child,&status,0)==child && WIFEXITED(status) && WEXITSTATUS(status)==77,"native installation crash boundary was not reached");
    fixture.historical();fixture.recover(original,initial);++cuts;
  }
  return cuts;
}
std::size_t allocations(const PhysicalPlan& original,const planner::MinimumHeightCandidate& candidate,const Database& initial,const io::CompilerPlanArtifact& artifact) {
  std::size_t count=0;
  {
    Fixture fixture(original,candidate,initial);const auto account=fixture.session->report_metadata().plan().account();
    const auto before=account.statistics().successful_allocations;
    {s04_alloc::Scope scope;static_cast<void>(fixture.session->publish_reoptimization(artifact));count=s04_alloc::calls;}
    check(count==account.statistics().successful_allocations-before,"native publication allocated outside the original query account");
  }
  check(count>0 && count<10000,"native installation allocation bound invalid");
  for(std::size_t point=0;point<count;++point) {
    Fixture fixture(original,candidate,initial);bool failed=false,triggered=false;
    {s04_alloc::Scope scope(static_cast<std::ptrdiff_t>(point));try{static_cast<void>(fixture.session->publish_reoptimization(artifact));}catch(const std::bad_alloc&){failed=true;}triggered=s04_alloc::triggered;}
    check(triggered && failed && !fixture.session->journal_state().recovery_required && fixture.session->report_metadata().owner()==fixture.old_owner &&
        session_file_test::contents(fixture.root)==fixture.before,"native installation allocation failure changed selection/old owner");
    fixture.historical();check(fixture.session->publish_reoptimization(artifact).phase==reoptimization::Phase::complete,"native installation allocation failure could not retry");
    fixture.recover(original,initial);
  }
  return count;
}
} // namespace
int main(int argc,char** argv) {
  try {
    check(argc==3,"usage: reoptimization_install_fault SOURCE io|crash|allocation");const auto fixture=c05_independent::boolean_fixture(argv[1]);std::size_t cuts=0;
    for(const bool indexed:{false,true}) {
      const auto physical=indexed?s04_runtime::options():PhysicalOptions{};
      const auto original=c05_independent::lower(*fixture.all.candidate(0),physical),target=c05_independent::lower(*fixture.all.candidate(1),physical);
      const auto compiler=resource::MemoryAccount::create(16*1024*1024);auto artifact=io::CompilerPlanArtifact::prepare(compiler,target);
      const auto boundaries=trace(original,*fixture.all.candidate(1),fixture.initial,artifact);
      if(std::string_view(argv[2])=="io")cuts+=io_cuts(original,*fixture.all.candidate(1),fixture.initial,artifact,boundaries);
      else if(std::string_view(argv[2])=="crash")cuts+=crash_cuts(original,*fixture.all.candidate(1),fixture.initial,artifact,boundaries);
      else cuts+=allocations(original,*fixture.all.candidate(1),fixture.initial,artifact);
    }
    std::cout<<"C06 native installation "<<argv[2]<<" PASS: "<<cuts<<" actual cuts across both backends at B=3 after snapshot1/two replayed records and three durable output epochs; original files, exact old/new recovery and next update, retry and no allocation after root selection.\n";return 0;
  }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
