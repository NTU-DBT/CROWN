#include "selection_independent_fixture.hpp"
#include "indexed_runtime_fixture.hpp"
#include "history_retirement_fixture.hpp"
#include "generation_file_probe.hpp"
#include "journal_file_probe.hpp"
#include "crown/io/compiler_plan_artifact.hpp"
#include "crown/runtime/session_reoptimization.hpp"
#include <cerrno>
#include <iostream>

namespace {
using namespace crown;
using namespace crown::runtime;
using c05_independent::check;
reoptimization::Options options() {
  reoptimization::Options value;value.forecast=reoptimization::Forecast{1'000'000'000,1,UINT64_MAX};return value;
}
struct PauseCleanup {
  static recovery::testing::GenerationDecision call(const recovery::testing::GenerationEvent& event,void*) noexcept {
    recovery::testing::GenerationDecision result;if(!event.after && event.stage==recovery::GenerationStage::unlink_history)result.error_before=EIO;return result;
  }
};
void retirement_preflight(bool indexed) {
  history_retirement_test::RetirementFixture fixture(indexed);bool interrupted=false;
  recovery::testing::set_generation_hook(PauseCleanup::call,nullptr);
  try{fixture.session->retire_generation_history();}catch(const recovery::GenerationFailure&){interrupted=true;}
  recovery::testing::set_generation_hook(nullptr,nullptr);
  check(interrupted && std::filesystem::exists(fixture.root+".retire"),"retirement preflight fixture has no intent");fixture.session.reset();
  const auto wal=fixture.path(3,".wal");generation_test::put(wal,session_file_test::contents(wal)+"CROWN");
  const auto before=session_file_test::contents(wal);const auto compiler=resource::MemoryAccount::create(16*1024*1024);
  auto artifact=io::CompilerPlanArtifact::prepare(compiler,fixture.test.plan);
  auto locked=QuerySession::lock_generation_recovery(fixture.program,fixture.root,generation_test::recovery_options());bool rejected=false;
  try{static_cast<void>(QuerySession::restore_selected_generation(std::move(locked),artifact));}
  catch(const recovery::GenerationFailure& failure){rejected=failure.fault()==recovery::GenerationFault::state;}
  check(rejected && session_file_test::contents(wal)==before && std::filesystem::exists(fixture.root+".retire"),"missing retirement sink repaired WAL before rejecting recovery");
  auto recovered=fixture.restore();check(recovered->status().committed_sequence==3 && !std::filesystem::exists(fixture.root+".retire"),"valid sink recovery did not resume retirement");
}
struct DenyAfterInput {
  bool reached=false;
  static recovery::journal::testing::FileDecision call(const recovery::journal::testing::FileEvent& event,void* context) noexcept {
    auto& self=*static_cast<DenyAfterInput*>(context);
    if(event.after && event.result==0 && event.stage==recovery::journal::FileStage::sync_file){self.reached=true;s04_alloc::remaining=0;}
    return {};
  }
};
void cached_reader(const PhysicalPlan& original,const PhysicalPlan& target,const planner::CandidateSnapshot& family,const Database& initial) {
  session_file_test::Directory directory;const auto root=directory.file("cached.root");
  const io::InputEvent first{{1,TableId{1},SetOperation::erase,*initial.tables[1].begin()},io::SourcePosition{"wire",10}},
      second{{2,TableId{1},SetOperation::insert,*initial.tables[1].begin()},io::SourcePosition{"wire",20}};
  const auto prefix=io::write_input_json(first,original.source_catalog())+"\n",tail=io::write_input_json(second,original.source_catalog())+"\n";
  auto input=std::make_unique<std::istringstream>(prefix+tail);auto* borrowed=input.get();
  auto session=QuerySession::create(original,initial,std::move(input));session->start();session->enable_generation(root,generation_test::options());
  session->begin_reoptimization(*family.candidate(1),options());DenyAfterInput hook;bool failed=false;
  {s04_alloc::Scope count;recovery::journal::testing::set_file_hook(DenyAfterInput::call,&hook);
    try{static_cast<void>(session->begin_next());}catch(const std::bad_alloc&){failed=true;}
    recovery::journal::testing::set_file_hook(nullptr,nullptr);}
  check(failed && hook.reached && !session->status().input_failed && !session->journal_state().recovery_required &&
      session->progress().sequence==0 && borrowed->tellg()==std::streampos{static_cast<std::streamoff>(prefix.size())},"cached reader native-begin failure fixture differs");
  // Rebuild after the failed candidate; the barrier must drain the already decoded row.
  session->cancel_reoptimization();session->begin_reoptimization(*family.candidate(1),options());session->pause();session->request_reoptimization_barrier();
  reoptimization::Status status;
  for(std::size_t step=0;step<10000;++step) {
    status=session->advance_reoptimization(1);
    if(!session->status().pending_sequence)while(session->next_output()){}
    if(status.phase==reoptimization::Phase::verified)break;
  }
  check(status.phase==reoptimization::Phase::verified && status.replayed_records==1 && session->progress().sequence==1 &&
      borrowed->tellg()==std::streampos{static_cast<std::streamoff>(prefix.size())} && session->status().state==SessionState::paused,
      "barrier lost cached row or decoded an unadmitted continuation");
  const auto compiler=resource::MemoryAccount::create(16*1024*1024);auto artifact=io::CompilerPlanArtifact::prepare(compiler,target);
  const auto installed=session->publish_reoptimization(artifact);
  check(installed.phase==reoptimization::Phase::complete && installed.query_memory.current==session->accounted_memory_statistics()->current,
      "publication status was captured before scratch cleanup");session.reset();
  auto locked=QuerySession::lock_generation_recovery(CompiledProgram::standalone(original),root,generation_test::recovery_options());
  auto selected=io::CompilerPlanArtifact::replay(compiler,locked->compiler_artifact());
  session=QuerySession::restore_selected_generation(std::move(locked),selected,std::make_unique<std::istringstream>(tail));
  session->start();check(session->begin_next(),"selected stream lost first unread continuation");local_sink_test::finish(*session);
  while(session->next_output()){}
  check(session->progress().sequence==2 && session->status().committed_sequence==2 && session->snapshot().rows.size()==1,"selected stream continuation changed exact progress/results");
}
void lock_and_binding(const PhysicalPlan& original,const PhysicalPlan& target,const planner::CandidateSnapshot& family,const Database& initial) {
  session_file_test::Directory directory;const auto root=directory.file("locked.root");
  auto session=QuerySession::create_typed(original,initial);session->start();session->enable_generation(root,generation_test::options());
  session->begin_reoptimization(*family.candidate(1),options());session->request_reoptimization_barrier();
  check(session->advance_reoptimization(100000).phase==reoptimization::Phase::verified,"lock fixture candidate did not verify");
  const auto compiler=resource::MemoryAccount::create(16*1024*1024);auto artifact=io::CompilerPlanArtifact::prepare(compiler,target);
  check(session->publish_reoptimization(artifact).phase==reoptimization::Phase::complete,"lock fixture did not switch");session.reset();
  const auto wal=generation_test::path(root,2,".wal");generation_test::put(wal,session_file_test::contents(wal)+"CROWN");const auto before=session_file_test::contents(wal);
  auto locked=QuerySession::lock_generation_recovery(CompiledProgram::standalone(original),root,generation_test::recovery_options());bool busy=false;
  try{static_cast<void>(QuerySession::lock_generation_recovery(CompiledProgram::standalone(original),root,generation_test::recovery_options()));}
  catch(const recovery::GenerationFailure& failure){busy=failure.fault()==recovery::GenerationFault::busy;}
  check(busy,"compiler handoff released the actual root lock");
  auto wrong=io::CompilerPlanArtifact::prepare(compiler,original);bool rejected=false;
  try{static_cast<void>(QuerySession::restore_selected_generation(std::move(locked),wrong));}
  catch(const recovery::GenerationFailure& failure){rejected=failure.fault()==recovery::GenerationFault::binding;}
  check(rejected && session_file_test::contents(wal)==before,"wrong compiler input repaired WAL before binding rejection");
  locked=QuerySession::lock_generation_recovery(CompiledProgram::standalone(original),root,generation_test::recovery_options());
  auto selected=io::CompilerPlanArtifact::replay(compiler,locked->compiler_artifact());session=QuerySession::restore_selected_generation(std::move(locked),selected);
  check(session_file_test::contents(wal).size()+5==before.size() && session->snapshot().rows.size()==1,"valid selected-plan recovery did not repair its tail");
}
} // namespace
int main(int argc,char** argv) {
  try {
    check(argc==2,"usage: reoptimization_recovery_admission SOURCE");const auto fixture=c05_independent::boolean_fixture(argv[1]);
    for(const bool indexed:{false,true}) {
      const auto physical=indexed?s04_runtime::options():PhysicalOptions{};
      const auto original=c05_independent::lower(*fixture.all.candidate(0),physical),target=c05_independent::lower(*fixture.all.candidate(1),physical);
      retirement_preflight(indexed);cached_reader(original,target,fixture.all,fixture.initial);lock_and_binding(original,target,fixture.all,fixture.initial);
    }
    std::cout<<"C06 locked recovery admission PASS: both backends, retirement/sink preflight before WAL repair, actual lock through compiler decode, wrong-artifact rejection without repair, cached-reader native failure/barrier/continuation and post-cleanup accounting.\n";return 0;
  }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
