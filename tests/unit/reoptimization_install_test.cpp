#include "selection_independent_fixture.hpp"
#include "indexed_runtime_fixture.hpp"
#include "local_sink_fixture.hpp"
#include "crown/frontend/admission.hpp"
#include "crown/io/compiler_plan_artifact.hpp"
#include "crown/runtime/session_reoptimization.hpp"
#include <iostream>

namespace {
using namespace crown;
using namespace crown::runtime;
using c05_independent::check;
using Output=std::set<std::pair<SetOperation,Row>>;
using Outputs=std::map<std::uint64_t,Output>;
reoptimization::Options migration_options() {
  reoptimization::Options value;value.forecast=reoptimization::Forecast{1'000'000'000,1,UINT64_MAX};return value;
}
SessionOptions session_options(DeltaMode mode) {
  SessionOptions value;value.delta.mode=mode;value.delta.physical.support.memory_limit_bytes=64U*1024U*1024U;return value;
}
void enqueue(QuerySession& session,io::InputItem item) {
  std::vector<io::InputItem> items;items.push_back(std::move(item));io::TransportBatch batch(std::move(items));
  check(session.enqueue(batch)==io::Admission::accepted && batch.empty(),"install input admission failed");
}
void collect(QuerySession& session,Outputs& outputs,bool sink) {
  if(session.status().pending_sequence || session.status().pending_command_sequence)return;
  if(sink) {
    if(session.local_sink_state().verified_sequence==session.status().committed_sequence)return;
    const auto delivery=session.deliver_local_epoch();const auto epoch=session.read_local_epoch(delivery.sequence);
    check(outputs.emplace(delivery.sequence,local_sink_test::output(epoch)).second,"install repeated a delivered epoch");
    return;
  }
  auto& rows=outputs[session.status().committed_sequence];
  while(auto row=session.next_output())check(rows.emplace(row->operation,storage::export_row(row->tuple.values())).second,"install repeated an output row");
}
void finish(QuerySession& session,Outputs& outputs,bool sink=false) {
  while(session.step()!=DeltaStep::prepared){}session.commit();collect(session,outputs,sink);
}
void apply(QuerySession& session,const PhysicalSetUpdate& update,Outputs& outputs,bool sink=false) {
  enqueue(session,io::InputEvent{update,io::SourcePosition{"feed",update.sequence*10}});
  check(session.begin_next(),"install event missing");finish(session,outputs,sink);
}
Relation results(QuerySession& session) {
  Relation value;for(const auto& row:session.snapshot().rows)value.insert(storage::export_row(row.values()));return value;
}
reoptimization::Status verify(QuerySession& session,Outputs& outputs,bool sink=false) {
  session.request_reoptimization_barrier();
  for(std::size_t step=0;step<10000;++step) {
    const auto value=session.advance_reoptimization(1);collect(session,outputs,sink);
    if(value.phase==reoptimization::Phase::verified || value.phase==reoptimization::Phase::rejected || value.phase==reoptimization::Phase::failed)return value;
  }
  throw std::runtime_error("install bounded barrier did not finish");
}
template<class Function> void binding_rejected(Function&& function) {
  try{function();}catch(const recovery::GenerationFailure&){return;}
  throw std::runtime_error("install admitted a wrong recovery/compiler binding");
}
QuerySession::Owner recover(const PhysicalPlan& original,const std::string& root,const std::string& sink={}) {
  auto locked=QuerySession::lock_generation_recovery(CompiledProgram::standalone(original),root,generation_test::recovery_options());
  check(locked->has_plan() && !locked->compiler_artifact().empty(),"selected descriptor/compiler input missing");
  const auto receiving=locked->accounted_memory_statistics().owner;
  // Full compiler decode happens explicitly while the actual root lock remains owned.
  const auto compiler=resource::MemoryAccount::create(32*1024*1024);
  auto artifact=io::CompilerPlanArtifact::replay(compiler,locked->compiler_artifact());
  auto session=sink.empty()?QuerySession::restore_selected_generation(std::move(locked),artifact):
      QuerySession::restore_selected_generation_with_local_sink(std::move(locked),artifact,sink,local_sink_test::options());
  check(session->accounted_memory_statistics()->owner==receiving && receiving!=compiler.statistics().owner,
      "same-lock admission replaced the original receiving account");
  return session;
}
void ordinary(const PhysicalPlan& original,const PhysicalPlan& target,const planner::CandidateSnapshot& family,
    std::size_t member,const Database& initial,DeltaMode mode,bool sink) {
  session_file_test::Directory directory;const auto root=directory.file("query.root"),sink_path=directory.file("results.sink");
  auto session=QuerySession::create_typed(original,initial,{},session_options(mode));
  auto reference=QuerySession::create_typed(original,initial,{},session_options(mode));session->start();reference->start();
  session->enable_generation(root,generation_test::options());if(sink)session->create_local_sink(sink_path,local_sink_test::options());
  const auto origin=sink?session->local_sink_state().persisted.header:recovery::sink::Header{};
  const auto account=session->accounted_memory_statistics()->owner;const auto owner=session->report_metadata().owner();
  const auto compiler=resource::MemoryAccount::create(32*1024*1024);auto artifact=io::CompilerPlanArtifact::prepare(compiler,target);
  session->begin_reoptimization(*family.candidate(member),migration_options());Outputs actual,expected;
  const std::vector<PhysicalSetUpdate> updates{
      {1,TableId{0},SetOperation::insert,Row{std::string("x")}},
      {2,TableId{1},SetOperation::erase,Row{std::string("x"),std::string("y")}},
      {3,TableId{1},SetOperation::insert,Row{std::string("x"),std::string("y")}},
      {4,TableId{2},SetOperation::erase,Row{std::string("y")}}};
  apply(*session,updates[0],actual,sink);apply(*reference,updates[0],expected);
  for(std::size_t i=1;i<updates.size();++i) {
    enqueue(*session,io::InputEvent{updates[i],io::SourcePosition{"feed",updates[i].sequence*10}});apply(*reference,updates[i],expected);
  }
  session->pause();check(verify(*session,actual,sink).phase==reoptimization::Phase::verified,"install candidate did not verify");
  workload::Options counters;counters.mode=workload::Mode::counters;counters.period=3;counters.offset=1;
  session->configure_workload_statistics(counters);
  const auto historical_checkpoint=session_file_test::contents(generation_test::path(root,1,".ckpt"));
  const auto historical_log=session_file_test::contents(generation_test::path(root,1,".wal"));
  const auto installed=session->publish_reoptimization(artifact);
  check(installed.phase==reoptimization::Phase::complete && !installed.admission_frozen && installed.compiler_input_charged &&
      installed.costs.compiler_artifact_ns==artifact.statistics().preparation_ns && installed.costs.publication_prepare_ns>0 &&
      installed.publication_timings_complete && installed.publication_ns>0 && installed.cleanup_ns>0,
      "install did not complete/report actual compiler/preparation/publication costs");
  check(session->accounted_memory_statistics()->owner==account && session->report_metadata().owner()!=owner &&
      session->report_metadata().owner().value==installed.target_owner && session->report_metadata().plan().physical_sha256()==artifact.program().physical_sha256() &&
      session->status().state==SessionState::paused && session->status().committed_sequence==4 && session->progress()==reference->progress() &&
      session->workload_statistics_options()==counters && session->workload_statistics()->stamp().interval_start_epoch==4,
      "install changed pause/frontiers/configuration or native account/owner");
  check(actual==expected && results(*session)==results(*reference),"install output/results differ from non-switching reference");
  check(session_file_test::contents(generation_test::path(root,1,".ckpt"))==historical_checkpoint &&
      session_file_test::contents(generation_test::path(root,1,".wal"))==historical_log,"install modified the rollback pair");
  if(sink)check(session->local_sink_state().persisted.header==origin && actual.at(1).empty(),"install rewrote sink origin or skipped the no-op epoch");
  const auto selected=session->generation_state().selected;
  const auto descriptor=recovery::inspect_plan_descriptor(session_file_test::contents(generation_test::path(root,selected.generation,".plan")));
  check(selected.generation==2 && selected.plan_sha256 && descriptor.selection.last_switch_epoch==4 &&
      descriptor.selection.physical_sequence==4,"install descriptor/frontier differs");
  session->start();apply(*session,{5,TableId{2},SetOperation::insert,Row{std::string("y")}},actual,sink);
  apply(*reference,{5,TableId{2},SetOperation::insert,Row{std::string("y")}},expected);
  check(actual==expected && results(*session)==results(*reference),"installed plan next update differs");
  session->rotate_generation();check(session->generation_state().selected.generation==3,"installed plan rotation failed");
  const auto rotated=recovery::inspect_plan_descriptor(session_file_test::contents(generation_test::path(root,3,".plan")));
  check(rotated.selection.physical_sequence==5 && rotated.selection.last_switch_epoch==4,"rotation reset hysteresis to its checkpoint epoch");
  if(sink)session->retire_generation_history();
  session.reset();
  binding_rejected([&]{static_cast<void>(QuerySession::restore_generation(CompiledProgram::standalone(original),root,generation_test::recovery_options()));});
  session=recover(original,root,sink?sink_path:std::string{});
  check(session->status().committed_sequence==5 && session->progress()==reference->progress() && results(*session)==results(*reference),"same-lock selected-plan recovery differs");
  if(sink)check(session->local_sink_state().persisted.header==origin && !std::filesystem::exists(generation_test::path(root,2,".plan")),"retirement lost origin or retained an obsolete descriptor");
  session->start();apply(*session,{6,TableId{0},SetOperation::erase,Row{std::string("x")}},actual,sink);
  apply(*reference,{6,TableId{0},SetOperation::erase,Row{std::string("x")}},expected);
  check(actual==expected && results(*session)==results(*reference),"recovered installed plan next update differs");
  session->begin_reoptimization(*family.candidate(0),migration_options());
  check(verify(*session,actual,sink).decision.stop==reoptimization::PolicyStop::hysteresis,"recovered switch lost hysteresis");
  auto second=migration_options();second.policy.minimum_epoch_gap=0;
  session->begin_reoptimization(*family.candidate(0),second);
  check(verify(*session,actual,sink).phase==reoptimization::Phase::verified,"second candidate failed equivalence");
  // The original compiler artifact is independently admitted, rather than exported from execution state.
  auto original_artifact=io::CompilerPlanArtifact::prepare(compiler,original);
  check(session->publish_reoptimization(original_artifact).phase==reoptimization::Phase::complete,"second plan switch failed");
  check(results(*session)==results(*reference) && session->accounted_memory_statistics()->owner!=compiler.statistics().owner,"second switch changed results/account");
}
void promotion(const PhysicalPlan& original,const PhysicalPlan& target,const planner::CandidateSnapshot& family,std::size_t member,const Database& initial) {
  session_file_test::Directory directory;const auto root=directory.file("promoted.root"),checkpoint=directory.file("old.ckpt"),log=directory.file("old.wal"),sink=directory.file("old.sink");
  auto session=QuerySession::create_typed(original,initial,{},session_options(DeltaMode::delta));session->start();
  static_cast<void>(session->checkpoint_file(checkpoint));
  session->enable_journal(checkpoint,log,session_journal_test::options());session->create_local_sink(sink,local_sink_test::options());
  Outputs output;apply(*session,{1,TableId{0},SetOperation::insert,Row{std::string("x")}},output,true);
  const auto old_checkpoint=session_file_test::contents(checkpoint),old_log=session_file_test::contents(log);
  const auto old_sink=session->local_sink_state().persisted.header;
  session->promote_journal(root,generation_test::options());
  check(session->generation_state().selected.generation==2 && session->generation_state().selected.first_generation==2 &&
      session->local_sink_state().persisted.header==old_sink && session_file_test::contents(checkpoint)==old_checkpoint && session_file_test::contents(log)==old_log,
      "promotion changed unmanaged bytes/sink identity or generation floor");
  session->begin_reoptimization(*family.candidate(member),migration_options());check(verify(*session,output,true).phase==reoptimization::Phase::verified,"promoted candidate failed");
  const auto compiler=resource::MemoryAccount::create(32*1024*1024);auto artifact=io::CompilerPlanArtifact::prepare(compiler,target);
  check(session->publish_reoptimization(artifact).phase==reoptimization::Phase::complete,"promoted journal did not switch");
  const auto expected=results(*session);session.reset();session=recover(original,root,sink);
  check(results(*session)==expected && session->status().committed_sequence==1,"promoted selected-plan recovery failed");
}
void window_command(QuerySession& session,io::WindowCommand command,Outputs& output) {
  const auto sequence=command.sequence;enqueue(session,std::move(command));
  for(std::size_t step=0;step<100 && session.progress().sequence<sequence;++step) {
    check(session.begin_next(),"install window command missing");finish(session,output);
  }
  check(session.progress().sequence==sequence,"install window command did not finish");
}
void window(const PhysicalPlan& original,const PhysicalPlan& target,const planner::CandidateSnapshot& family,WindowFifoPolicy fifo) {
  session_file_test::Directory directory;const auto root=directory.file("window.root");
  WindowOptions config;config.managed_tables={TableId{0},TableId{1},TableId{2}};config.width=10;config.fifo=fifo;
  auto session=QuerySession::create_windowed(original,config,{},session_options(DeltaMode::delta));
  auto reference=QuerySession::create_windowed(original,config,{},session_options(DeltaMode::delta));session->start();reference->start();
  session->enable_generation(root,generation_test::options());Outputs actual,expected;
  for(const auto& command:std::vector<io::WindowCommand>{
      {1,io::WindowInsert{1,TableId{0},Row{std::string("x")},1},{}},
      {2,io::WindowInsert{2,TableId{0},Row{std::string("x")},1},{}},
      {3,io::WindowInsert{3,TableId{1},Row{std::string("x"),std::string("y")},1},{}},
      {4,io::WindowInsert{4,TableId{2},Row{std::string("y")},1},{}}}) {
    window_command(*session,command,actual);window_command(*reference,command,expected);
  }
  session->begin_reoptimization(*family.candidate(1),migration_options());
  const io::WindowCommand watermark{5,io::AdvanceWatermark{30},{}};enqueue(*session,watermark);window_command(*reference,watermark,expected);
  check(session->begin_next(),"install watermark missing");session->pause();
  check(verify(*session,actual).phase==reoptimization::Phase::verified,"install partial watermark did not drain");
  const auto compiler=resource::MemoryAccount::create(32*1024*1024);auto artifact=io::CompilerPlanArtifact::prepare(compiler,target);
  check(session->publish_reoptimization(artifact).phase==reoptimization::Phase::complete && session->status().state==SessionState::paused &&
      session->progress().sequence==5 && session->status().committed_sequence==6 && session->window_state()==reference->window_state() &&
      actual==expected && results(*session)==results(*reference),"window installation lost exact physical/command/controller boundary");
  session.reset();session=recover(original,root);
  check(session->status().state==SessionState::paused && session->window_state()==reference->window_state(),"selected window recovery changed pause/controller");
  session->start();const io::WindowCommand next{6,io::WindowInsert{5,TableId{0},Row{std::string("z")},31},{}};
  window_command(*session,next,actual);window_command(*reference,next,expected);
  check(actual==expected && session->window_state()==reference->window_state(),"recovered window next command differs");
}
void late_sink(const PhysicalPlan& original,const PhysicalPlan& target,const planner::CandidateSnapshot& family,const Database& initial) {
  session_file_test::Directory directory;const auto root=directory.file("late.root"),sink=directory.file("late.sink");
  auto session=QuerySession::create_typed(original,initial,{},session_options(DeltaMode::delta));session->start();
  session->enable_generation(root,generation_test::options());session->begin_reoptimization(*family.candidate(1),migration_options());Outputs output;
  check(verify(*session,output).phase==reoptimization::Phase::verified,"late-sink candidate failed");
  const auto compiler=resource::MemoryAccount::create(32*1024*1024);auto artifact=io::CompilerPlanArtifact::prepare(compiler,target);
  check(session->publish_reoptimization(artifact).phase==reoptimization::Phase::complete,"late-sink initial switch failed");
  session->create_local_sink(sink,local_sink_test::options());const auto origin=session->local_sink_state().persisted.header;
  // Recover once before any metadata selection persists the new sink origin.
  session.reset();session=recover(original,root,sink);session->start();session->rotate_generation();
  const auto descriptor=recovery::inspect_plan_descriptor(session_file_test::contents(generation_test::path(root,3,".plan")));
  check(descriptor.selection.sink_origin==origin && descriptor.selection.last_switch_epoch==0,"rotation did not bind late sink or retained switch epoch");
  session->retire_generation_history();session.reset();session=recover(original,root,sink);
  check(session->local_sink_state().persisted.header==origin && session->generation_state().selected.first_generation==3,"late-sink origin/retirement recovery failed");
}
void ended_input(const PhysicalPlan& original,const PhysicalPlan& target,const planner::CandidateSnapshot& family,const Database& initial,bool stream) {
  session_file_test::Directory directory;const auto root=directory.file("ended.root");
  auto session=stream?QuerySession::create(original,initial,std::make_unique<std::istringstream>(""),session_options(DeltaMode::delta)):
      QuerySession::create_typed(original,initial,{},session_options(DeltaMode::delta));session->start();
  session->enable_generation(root,generation_test::options());if(!stream)session->finish_input();
  check(session->begin_next_result()==SessionBegin::end,"EOF fixture did not reach input end");
  const auto before=session_file_test::contents(root);session->begin_reoptimization(*family.candidate(1),migration_options());Outputs output;
  check(verify(*session,output).phase==reoptimization::Phase::verified,"EOF candidate did not establish its old committed boundary");
  const auto compiler=resource::MemoryAccount::create(32*1024*1024);auto artifact=io::CompilerPlanArtifact::prepare(compiler,target);
  bool rejected=false;try{static_cast<void>(session->publish_reoptimization(artifact));}catch(const Error& failure){rejected=failure.code()=="reoptimization_input_state";}
  check(rejected && session_file_test::contents(root)==before,"EOF publication selected an unrecoverable root");
}
} // namespace
int main(int argc,char** argv) {
  try {
    check(argc==2,"usage: reoptimization_install SOURCE");const auto fixture=c05_independent::boolean_fixture(argv[1]);std::size_t cases=0;
    for(const bool indexed:{false,true}) {
      const auto physical=indexed?s04_runtime::options():PhysicalOptions{};
      const auto original=c05_independent::lower(*fixture.all.candidate(0),physical),target=c05_independent::lower(*fixture.all.candidate(1),physical);
      for(const auto mode:{DeltaMode::maintenance,DeltaMode::delta})for(const bool sink:{false,true}) {
        ordinary(original,target,fixture.all,1,fixture.initial,mode,sink);++cases;
      }
      promotion(original,target,fixture.all,1,fixture.initial);
      late_sink(original,target,fixture.all,fixture.initial);
      for(const bool stream:{false,true})ended_input(original,target,fixture.all,fixture.initial,stream);
      for(const auto fifo:{WindowFifoPolicy::global,WindowFifoPolicy::per_relation})window(original,target,fixture.all,fifo);
      for(const auto* sql:{
          "SELECT EXISTS(SELECT 1 FROM \"R\" r CROSS JOIN \"S\" s CROSS JOIN \"T\" t WHERE r.c0=s.c0 AND s.c1=t.c0);",
          "SELECT DISTINCT r.c0, s.c1, r.c0 AS repeated, 7 AS fixed FROM \"R\" r CROSS JOIN \"S\" s CROSS JOIN \"T\" t WHERE r.c0=s.c0 AND s.c1=t.c0;"}) {
        const auto admitted=frontend::admit_sql(sql,fixture.document.catalog);check(admitted.status==frontend::AdmissionStatus::admitted,"install SQL fixture rejected");
        const auto family=c05_independent::candidates(admitted.program->core_catalog,admitted.program->core);
        const auto member=family.candidate_count()>1?std::size_t{1}:std::size_t{0};
        const auto first=planner::lower_normalized(*admitted.program,family.candidate(0)->tree(),physical);
        const auto next=planner::lower_normalized(*admitted.program,family.candidate(member)->tree(),physical);
        for(const auto mode:{DeltaMode::maintenance,DeltaMode::delta})for(const bool sink:{false,true}) {
          ordinary(first,next,family,member,fixture.initial,mode,sink);++cases;
        }
      }
    }
    std::cout<<"C06 native installation PASS: "<<cases<<" CQ/SQL/backend/mode/sink cases; paused queued input, exact non-switching output, original account/configuration, immutable sink lineage, rotation/retirement, same-lock compiler recovery, hysteresis/repeated switch and journal promotion.\n";
    return 0;
  }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
