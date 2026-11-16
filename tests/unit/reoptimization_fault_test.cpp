#include "selection_independent_fixture.hpp"
#include "indexed_runtime_fixture.hpp"
#include "session_journal_fixture.hpp"
#include "journal_file_probe.hpp"
#include <cerrno>
#include <iostream>

namespace {
using namespace crown;
using namespace crown::runtime;
using c05_independent::check;
reoptimization::Options options() {
  reoptimization::Options result;result.forecast=reoptimization::Forecast{1'000'000'000,1,UINT64_MAX};return result;
}
enum class Cut {snapshot,old_begin,catch_up,equivalence};
struct Fixture {
  QuerySession::Owner session;
  planner::MinimumHeightCandidate candidate;
  Fixture(const PhysicalPlan& plan,const Database& initial,planner::MinimumHeightCandidate target,Cut cut)
      :session(QuerySession::create_typed(plan,initial)),candidate(std::move(target)) {
    session->start();if(cut==Cut::snapshot)return;
    session->begin_reoptimization(candidate,options());
    if(cut==Cut::equivalence){session->request_reoptimization_barrier();return;}
    io::TransportBatch batch({io::InputEvent{{1,TableId{1},SetOperation::erase,Row{std::string("x"),std::string("y")}},{}}});
    check(session->enqueue(batch)==io::Admission::accepted,"fault input was not admitted");
    if(cut==Cut::catch_up){check(session->begin_next(),"fault input missing");finish();}
  }
  void finish() {
    while(session->step()!=DeltaStep::prepared){}session->commit();while(session->next_output()){}
  }
  void attempt(Cut cut) {
    if(cut==Cut::snapshot)session->begin_reoptimization(candidate,options());
    else if(cut==Cut::old_begin)static_cast<void>(session->begin_next());
    else static_cast<void>(session->advance_reoptimization(100000));
  }
  void verify_retry() {
    session->cancel_reoptimization();session->begin_reoptimization(candidate,options());session->request_reoptimization_barrier();
    const auto status=session->advance_reoptimization(100000);
    check(status.phase==reoptimization::Phase::verified && status.source_epoch==session->status().committed_sequence &&
        status.target_epoch==status.source_epoch,"allocation failure prevented exact candidate retry");session->cancel_reoptimization();
  }
};
Relation rows(QuerySession& session) {
  Relation result;for(const auto& row:session.snapshot().rows)result.insert(storage::export_row(row.values()));return result;
}
std::size_t sweep(const PhysicalPlan& plan,const Database& initial,const planner::MinimumHeightCandidate& candidate,Cut cut) {
  std::size_t allocations=0;
  {
    Fixture source(plan,initial,candidate,cut);
    {s04_alloc::Scope count;source.attempt(cut);allocations=s04_alloc::calls;}
    if(cut==Cut::old_begin)source.finish();
  }
  check(allocations>0 && allocations<10000,"allocation sweep has an invalid finite bound");
  for(std::size_t point=0;point<allocations;++point) {
    Fixture source(plan,initial,candidate,cut);const auto owner=source.session->report_metadata().owner();bool threw=false,triggered=false;
    {
      s04_alloc::Scope fail(static_cast<std::ptrdiff_t>(point));
      try{source.attempt(cut);}catch(const std::bad_alloc&){threw=true;}
      triggered=s04_alloc::triggered;
    }
    check(triggered,"allocation cut was not exercised");
    const auto status=source.session->reoptimization_status();
    check(source.session->report_metadata().owner()==owner && !source.session->journal_state().recovery_required,"allocation failure replaced/poisoned the current owner");
    if(cut==Cut::old_begin) {
      check(source.session->status().committed_sequence==0 && source.session->progress().sequence==0 && status.backlog_records==0,
          "failed old begin committed a ledger entry/input");
      if(threw)check(source.session->begin_next(),"old input could not retry after allocation failure");
      source.finish();
    } else {
      check(threw || status.phase==reoptimization::Phase::failed,"allocation failure was not reported");
    }
    const auto expected=cut==Cut::old_begin || cut==Cut::catch_up?Relation{}:Relation{Row{}};
    check(rows(*source.session)==expected && !source.session->reoptimization_status().admission_frozen,
        "allocation failure damaged committed results or left admission frozen");
    source.session->report_metadata().plan().account().check_invariants();source.verify_retry();
  }
  return allocations;
}
struct DenyAfterSync {
  bool synced=false;
  static recovery::journal::testing::FileDecision call(const recovery::journal::testing::FileEvent& event,void* context) noexcept {
    auto& self=*static_cast<DenyAfterSync*>(context);
    if(event.after && event.stage==recovery::journal::FileStage::sync_file && event.result==0){self.synced=true;s04_alloc::remaining=0;}
    return {};
  }
};
void durable_publication(const PhysicalPlan& plan,const Database& initial,const planner::MinimumHeightCandidate& candidate) {
  Fixture source(plan,initial,candidate,Cut::snapshot);session_journal_test::Directory directory;
  const auto checkpoint=directory.file("base.crown"),log=directory.file("current.wal");
  static_cast<void>(source.session->checkpoint_file(checkpoint));source.session->enable_journal(checkpoint,log,session_journal_test::options());
  source.session->begin_reoptimization(candidate,options());
  io::TransportBatch batch({io::InputEvent{{1,TableId{1},SetOperation::erase,Row{std::string("x"),std::string("y")}},{}}});
  check(source.session->enqueue(batch)==io::Admission::accepted && source.session->begin_next(),"journal candidate input missing");
  while(source.session->step()!=DeltaStep::prepared){}
  DenyAfterSync hook;bool triggered=false;
  {
    s04_alloc::Scope count;recovery::journal::testing::set_file_hook(DenyAfterSync::call,&hook);
    try{source.session->commit();}catch(...){recovery::journal::testing::set_file_hook(nullptr,nullptr);throw;}
    recovery::journal::testing::set_file_hook(nullptr,nullptr);triggered=s04_alloc::triggered;
  }
  check(hook.synced && !triggered && source.session->status().committed_sequence==1 && source.session->progress().sequence==1 &&
      source.session->reoptimization_status().backlog_records==1 && source.session->reoptimization_status().source_epoch==1,
      "ledger publication allocated after a durable original decision");
  while(source.session->next_output()){}source.session->request_reoptimization_barrier();
  check(source.session->advance_reoptimization(100000).phase==reoptimization::Phase::verified,"nonallocating journal publication lost catch-up input");
}
struct FailAfterSync {
  static recovery::journal::testing::FileDecision call(const recovery::journal::testing::FileEvent& event,void*) noexcept {
    recovery::journal::testing::FileDecision result;
    if(!event.after && event.stage==recovery::journal::FileStage::sync_file)result.error_after=EIO;
    return result;
  }
};
void uncertain_original_journal(const PhysicalPlan& plan,const Database& initial,const planner::MinimumHeightCandidate& candidate,bool decision) {
  Fixture source(plan,initial,candidate,Cut::snapshot);session_journal_test::Directory directory;
  const auto checkpoint=directory.file("base.crown"),log=directory.file("current.wal");
  static_cast<void>(source.session->checkpoint_file(checkpoint));source.session->enable_journal(checkpoint,log,session_journal_test::options());
  source.session->begin_reoptimization(candidate,options());
  io::TransportBatch batch({io::InputEvent{{1,TableId{1},SetOperation::erase,Row{std::string("x"),std::string("y")}},{}}});
  check(source.session->enqueue(batch)==io::Admission::accepted,"uncertain journal candidate input missing");
  if(decision){check(source.session->begin_next(),"uncertain journal head missing");while(source.session->step()!=DeltaStep::prepared){}}
  bool failed=false;recovery::journal::testing::set_file_hook(FailAfterSync::call,nullptr);
  try{if(decision)source.session->commit();else static_cast<void>(source.session->begin_next());}
  catch(const recovery::journal::FileFailure&){failed=true;}
  catch(...){recovery::journal::testing::set_file_hook(nullptr,nullptr);throw;}
  recovery::journal::testing::set_file_hook(nullptr,nullptr);
  check(failed && source.session->journal_state().recovery_required && source.session->reoptimization_status().phase==reoptimization::Phase::recovery_required &&
      source.session->reoptimization_status().backlog_records==0 && source.session->status().committed_sequence==0 && source.session->progress().sequence==0,
      "uncertain original journal left a reusable candidate or published native state");
  bool blocked=false;try{source.session->cancel_reoptimization();}catch(const SessionJournalFailure& failure){blocked=failure.fault()==SessionJournalFault::recovery_required;}
  check(blocked,"candidate cancellation bypassed original journal recovery");
  source.session.reset();SessionJournalRecoveryOptions restore;restore.journal=session_journal_test::options();
  auto recovered=QuerySession::restore_journal(CompiledProgram::standalone(plan),checkpoint,log,restore);
  check(recovered->status().committed_sequence==(decision?1U:0U) && recovered->reoptimization_status().phase==reoptimization::Phase::inactive,
      "original journal recovery selected private candidate state");
  if(decision)while(recovered->next_recovered_output()){}
  recovered->start();
  if(!decision){check(recovered->begin_next(),"durable uncommitted original input was lost");while(recovered->step()!=DeltaStep::prepared){}recovered->commit();while(recovered->next_output()){}}
  check(recovered->status().committed_sequence==1 && recovered->progress().sequence==1 && rows(*recovered).empty(),"original durable input/decision did not recover exactly once");
}
} // namespace
int main(int argc,char** argv) {
  try {
    check(argc==2,"usage: reoptimization_fault SOURCE");const auto fixture=c05_independent::boolean_fixture(argv[1]);std::size_t cuts=0;
    for(const bool indexed:{false,true}) {
      const auto plan=c05_independent::lower(fixture.by_label.at("native_s"),indexed?s04_runtime::options():PhysicalOptions{});
      for(const auto cut:{Cut::snapshot,Cut::old_begin,Cut::catch_up,Cut::equivalence})cuts+=sweep(plan,fixture.initial,*fixture.all.candidate(1),cut);
      durable_publication(plan,fixture.initial,*fixture.all.candidate(1));
      for(const bool decision:{false,true})uncertain_original_journal(plan,fixture.initial,*fixture.all.candidate(1),decision);
    }
    std::cout<<"C06 preparation every-allocation cuts PASS: "<<cuts<<" snapshot/old-begin/catch-up/equivalence cuts across both backends; old results, retry and no allocation after durable decision. Plan-selection crash cuts remain separate.\n";
    return 0;
  }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
