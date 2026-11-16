#include "selection_independent_fixture.hpp"
#include "indexed_runtime_fixture.hpp"
#include "local_sink_fixture.hpp"
#include "crown/frontend/admission.hpp"
#include <map>
#include <set>
#include <sstream>

namespace {
using namespace crown;
using namespace crown::runtime;
using c05_independent::check;
using Output=std::set<std::pair<SetOperation,Row>>;
using Outputs=std::map<std::uint64_t,Output>;
template<class Action> void code(Action&& action,std::string_view expected) {
  try{action();}catch(const Error& failure){check(failure.code()==expected,"session candidate rejected with wrong error");return;}
  throw std::runtime_error("session candidate accepted a forbidden barrier");
}
reoptimization::Options options() {
  reoptimization::Options result;result.forecast=reoptimization::Forecast{1'000'000'000,1,UINT64_MAX};return result;
}
SessionOptions session_options(DeltaMode mode) {
  SessionOptions result;result.delta.mode=mode;result.delta.physical.support.memory_limit_bytes=32U*1024U*1024U;return result;
}
void enqueue(QuerySession& session,io::InputItem item) {
  std::vector<io::InputItem> items;items.push_back(std::move(item));io::TransportBatch batch(std::move(items));
  check(session.enqueue(batch)==io::Admission::accepted && batch.empty(),"session candidate input was not admitted");
}
void collect(QuerySession& session,Outputs& outputs) {
  const auto state=session.status();if(state.pending_sequence || state.pending_command_sequence)return;
  const auto sequence=state.committed_sequence;
  while(auto row=session.next_output())check(outputs[sequence].emplace(row->operation,storage::export_row(row->tuple.values())).second,"duplicate session output");
}
void finish(QuerySession& session,Outputs& outputs) {
  while(session.step()!=DeltaStep::prepared){}session.commit();collect(session,outputs);
}
void apply(QuerySession& session,const PhysicalSetUpdate& update,Outputs& outputs) {
  enqueue(session,io::InputEvent{update,io::SourcePosition{"feed",update.sequence*10}});
  check(session.begin_next(),"session input missing");finish(session,outputs);
}
Relation results(QuerySession& session) {
  Relation result;for(const auto& row:session.snapshot().rows)result.insert(storage::export_row(row.values()));return result;
}
reoptimization::Status barrier(QuerySession& session,Outputs& outputs) {
  for(std::size_t i=0;i<10000;++i) {
    const auto status=session.advance_reoptimization(1);collect(session,outputs);
    if(status.phase==reoptimization::Phase::verified || status.phase==reoptimization::Phase::failed || status.phase==reoptimization::Phase::rejected)return status;
  }
  throw std::runtime_error("bounded candidate barrier did not finish");
}
void ordinary(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,const Database& initial,DeltaMode mode,BuildMethod method) {
  auto session=QuerySession::create_typed(plan,initial,{},session_options(mode));
  auto reference=QuerySession::create_typed(plan,initial,{},session_options(mode));session->start();reference->start();
  auto config=options();config.build.method=method;
  const auto owner=session->report_metadata().owner();const auto memory=*session->accounted_memory_statistics();
  config.expected=reoptimization::Boundary{owner.value,0};session->begin_reoptimization(*family.candidate(1),config);
  const auto prepared=session->reoptimization_status();
  check(prepared.phase==reoptimization::Phase::catching_up && prepared.source_owner==owner.value && prepared.target_owner!=owner.value &&
      prepared.query_memory.owner==memory.owner && prepared.query_memory.current.requested_bytes>memory.current.requested_bytes,"candidate bootstrap escaped ownership or shared memory");
  Outputs actual,expected;
  const std::vector<PhysicalSetUpdate> updates{
    {1,TableId{0},SetOperation::insert,Row{std::string("x")}},
    {2,TableId{1},SetOperation::erase,Row{std::string("x"),std::string("y")}},
    {3,TableId{1},SetOperation::insert,Row{std::string("x"),std::string("y")}},
    {4,TableId{2},SetOperation::erase,Row{std::string("y")}},
    {5,TableId{2},SetOperation::insert,Row{std::string("y")}},
    {6,TableId{0},SetOperation::insert,Row{std::string("unmatched")}}};
  for(std::size_t i=0;i<4;++i) {
    apply(*session,updates[i],actual);apply(*reference,updates[i],expected);
    const auto previous=session->reoptimization_status().catch_up_steps;const auto status=session->advance_reoptimization(1);
    check(status.catch_up_steps-previous<=1 && status.source_epoch==i+1,"catch-up quantum/order changed");
  }
  for(std::size_t i=4;i<updates.size();++i){enqueue(*session,io::InputEvent{updates[i],io::SourcePosition{"feed",updates[i].sequence*10}});apply(*reference,updates[i],expected);}
  check(session->begin_next(),"admitted pending barrier input missing");session->pause();session->request_reoptimization_barrier();
  const auto status=barrier(*session,actual);
  check(status.phase==reoptimization::Phase::verified && status.admission_frozen && status.source_epoch==6 && status.target_epoch==6 &&
      status.backlog_records==0 && status.replayed_records==6 && status.staged_records==6 && status.source_rows_compared==8 && status.result_rows_compared==2 &&
      status.lowering_work>0 && status.build_work>0 && status.catch_up_steps>0 && status.catch_up_native_work>0 && status.equivalence_work>0 &&
      status.clock_reads>0 && status.decision.stop==reoptimization::PolicyStop::eligible,"candidate did not establish complete bounded equivalence");
  check(session->status().state==SessionState::paused && session->progress()==reference->progress() && actual==expected && results(*session)==results(*reference),"barrier changed pause, progress, outputs or results");
  check(session->report_metadata().owner()==owner,"preparation published a native plan");session->start();
  check(session->begin_next_result()==SessionBegin::would_block,"verified barrier admitted a new input");
  code([&]{enqueue(*session,io::InputEvent{updates.front(),{}});},"reoptimization_barrier");
  const auto dual=status.query_memory.current.requested_bytes;session->cancel_reoptimization();
  check(session->reoptimization_status().phase==reoptimization::Phase::cancelled && !session->reoptimization_status().admission_frozen &&
      session->accounted_memory_statistics()->current.requested_bytes<dual,"cancel did not release private target/ledger");
  apply(*session,{7,TableId{0},SetOperation::erase,Row{std::string("unmatched")}},actual);
  apply(*reference,{7,TableId{0},SetOperation::erase,Row{std::string("unmatched")}},expected);check(actual==expected,"cancel damaged the current plan");
}
void failures(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,const Database& initial) {
  for(unsigned fault=0;fault<8;++fault) {
    auto session=QuerySession::create_typed(plan,initial,{},session_options(DeltaMode::delta));session->start();auto config=options();
    if(fault==0)config.limits.backlog_records=0;
    if(fault==1)config.limits.staging_work=0;
    if(fault==2)config.limits.catch_up_steps=0;
    if(fault==3)config.limits.equivalence_work=0;
    if(fault==4)config.limits.equivalence_rows=0;
    if(fault==5)config.forecast.reset();
    if(fault==7)config.limits.equivalence_cursor_work=0;
    session->begin_reoptimization(*family.candidate(1),config);Outputs output;
    if(fault==6) {
      enqueue(*session,io::InputEvent{{1,TableId{1},SetOperation::erase,Row{std::string("x"),std::string("y")}},{}});
      const auto account=session->report_metadata().plan().account();const auto state=account.statistics();
      const auto framing=resource::MemoryAccount::allocation_bytes(0,alignof(std::max_align_t));
      auto reserve=account.allocate(static_cast<std::size_t>(state.limit_bytes-state.current.requested_bytes-framing-16));
      // Freeing the candidate supplies the original writer's ordinary grant.
      check(session->begin_next(),"funded queue head missing after staging failure");finish(*session,output);
    }else apply(*session,{1,TableId{1},SetOperation::erase,Row{std::string("x"),std::string("y")}},output);
    auto status=session->reoptimization_status();
    if((fault>=2 && fault<=5) || fault==7){session->request_reoptimization_barrier();status=barrier(*session,output);}
    const auto expected=fault==0?reoptimization::Stop::backlog_limit:fault==1?reoptimization::Stop::staging_limit:
        fault==2?reoptimization::Stop::catch_up_limit:fault==6?reoptimization::Stop::allocation_failure:reoptimization::Stop::equivalence_limit;
    check(status.phase==(fault==5?reoptimization::Phase::rejected:reoptimization::Phase::failed) && !status.admission_frozen &&
        (fault==5?status.decision.stop==reoptimization::PolicyStop::forecast_unavailable:status.stop==expected),"migration resource/policy failure was hidden");
    check(session->status().committed_sequence==1,"migration failure rolled back a committed original update");
    apply(*session,{2,TableId{1},SetOperation::insert,Row{std::string("x"),std::string("y")}},output);
    session->begin_reoptimization(*family.candidate(1),options());session->request_reoptimization_barrier();
    check(barrier(*session,output).phase==reoptimization::Phase::verified,"failed candidate cannot retry");session->cancel_reoptimization();
  }
  auto session=QuerySession::create_typed(plan,initial,{},session_options(DeltaMode::delta));session->start();auto stale=options();
  stale.expected=reoptimization::Boundary{session->report_metadata().owner().value,1};
  code([&]{session->begin_reoptimization(*family.candidate(1),stale);},"reoptimization_stale_source");
  check(session->reoptimization_status().phase==reoptimization::Phase::inactive,"stale preparation left an active target");
}
void ledger_bytes(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,const Database& initial) {
  auto session=QuerySession::create_typed(plan,initial,{},session_options(DeltaMode::delta));session->start();Outputs output;
  const auto account=session->report_metadata().plan().account();constexpr resource::MemoryAttribution owner{resource::MemoryOwnerKind::session,1};
  session->begin_reoptimization(*family.candidate(1),options());const auto before=account.statistics_for(owner).current.requested_bytes;
  apply(*session,{1,TableId{0},SetOperation::insert,Row{std::string("x")}},output);
  const auto bytes=session->reoptimization_status().backlog_bytes;
  check(bytes>0 && account.statistics_for(owner).current.requested_bytes-before==bytes,"ledger bytes differ from actual original-account record/row allocations");
  session->cancel_reoptimization();auto config=options();config.limits.backlog_bytes=bytes-1;
  session->begin_reoptimization(*family.candidate(1),config);apply(*session,{2,TableId{0},SetOperation::insert,Row{std::string("x")}},output);
  check(session->reoptimization_status().stop==reoptimization::Stop::backlog_limit,"one-byte-short ledger grant was exceeded");
  config.limits.backlog_bytes=bytes;session->begin_reoptimization(*family.candidate(1),config);
  apply(*session,{3,TableId{0},SetOperation::insert,Row{std::string("x")}},output);
  check(session->reoptimization_status().phase==reoptimization::Phase::catching_up && session->reoptimization_status().backlog_bytes==bytes,
      "exact real ledger allocation grant was rejected");
  apply(*session,{4,TableId{0},SetOperation::insert,Row{std::string("x")}},output);
  check(session->reoptimization_status().stop==reoptimization::Stop::backlog_limit && session->status().committed_sequence==4,"ledger overflow prevented original no-op publication");
  session->drop();check(account.statistics_for(owner).current.allocations==0,"drop retained candidate control/ledger allocations");
}
void projected(const Catalog& catalog,PhysicalOptions physical,DeltaMode mode) {
  const auto admitted=frontend::admit_sql("SELECT DISTINCT r.c0 AS a, s.c1 AS b, r.c0 AS repeated, 7 AS fixed FROM \"R\" r CROSS JOIN \"S\" s CROSS JOIN \"T\" t WHERE r.c0=s.c0 AND s.c1=t.c0;",catalog);
  check(admitted.status==frontend::AdmissionStatus::admitted,"projected/repeated/constant SQL candidate rejected");
  const auto family=c05_independent::candidates(admitted.program->core_catalog,admitted.program->core);
  const auto plan=planner::lower_normalized(*admitted.program,family.candidate(0)->tree(),physical);
  Database initial;initial.tables.resize(3);initial.tables[0]={{std::string("x")},{std::string("z")}};
  initial.tables[1]={{std::string("x"),std::string("y")},{std::string("z"),std::string("y")},{std::string("x"),std::string("w")},{std::string("z"),std::string("w")}};
  initial.tables[2]={{std::string("y")},{std::string("w")}};
  auto session=QuerySession::create_typed(plan,initial,{},session_options(mode)),reference=QuerySession::create_typed(plan,initial,{},session_options(mode));
  session->start();reference->start();check(results(*session).size()==4,"projected candidate fixture lost a result");
  session->begin_reoptimization(*family.candidate(family.candidate_count()>1?1:0),options());Outputs actual,expected;
  const std::vector<PhysicalSetUpdate> updates{
    {1,TableId{1},SetOperation::erase,Row{std::string("x"),std::string("y")}},
    {2,TableId{2},SetOperation::erase,Row{std::string("w")}},
    {3,TableId{1},SetOperation::insert,Row{std::string("x"),std::string("y")}},
    {4,TableId{0},SetOperation::erase,Row{std::string("z")}},
    {5,TableId{0},SetOperation::insert,Row{std::string("x")}},
    {6,TableId{0},SetOperation::insert,Row{std::string("unmatched")}}};
  for(const auto& update:updates){apply(*session,update,actual);apply(*reference,update,expected);static_cast<void>(session->advance_reoptimization(2));}
  session->request_reoptimization_barrier();const auto status=barrier(*session,actual);
  const Relation literal{Row{std::string("x"),std::string("y"),std::string("x"),std::int64_t{7}}};
  check(status.phase==reoptimization::Phase::verified,"multirow SQL candidate did not verify");
  check(status.target_epoch==6 && status.result_rows_compared==2,"multirow SQL candidate epoch/result visit count differs");
  check(results(*session)==literal && results(*reference)==literal,"multirow SQL literal repeated/constant projection differs");
  check(actual==expected,"multirow SQL exact deltas differ from non-switching reference");
  check(mode==DeltaMode::maintenance || expected[2].size()==2,"multirow SQL fixture did not delete two rows");session->cancel_reoptimization();
}
void stream(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,const Database& initial) {
  auto input=std::make_unique<std::istringstream>("+ R x\n"); // Barrier must not decode it, irrespective of its codec.
  auto* borrowed=input.get();auto session=QuerySession::create(plan,initial,std::move(input),session_options(DeltaMode::delta));session->start();
  session->begin_reoptimization(*family.candidate(1),options());session->request_reoptimization_barrier();Outputs output;
  check(barrier(*session,output).phase==reoptimization::Phase::verified && borrowed->tellg()==std::streampos{0} && session->progress().sequence==0,
      "owned-stream barrier consumed an unadmitted byte");session->cancel_reoptimization();
}
void command(QuerySession& session,io::WindowCommand item,Outputs& output) {
  const auto sequence=item.sequence;enqueue(session,std::move(item));
  for(std::size_t i=0;i<100 && session.progress().sequence<sequence;++i) {
    check(session.begin_next(),"window candidate command missing");finish(session,output);
  }
  check(session.progress().sequence==sequence,"window candidate command did not complete");
}
void window(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,WindowFifoPolicy fifo) {
  WindowOptions config;config.managed_tables={TableId{0},TableId{1},TableId{2}};config.width=10;config.fifo=fifo;
  auto session=QuerySession::create_windowed(plan,config,{},session_options(DeltaMode::delta));
  auto reference=QuerySession::create_windowed(plan,config,{},session_options(DeltaMode::delta));session->start();reference->start();Outputs actual,expected;
  const std::vector<io::WindowCommand> commands{
    {1,io::WindowInsert{1,TableId{0},Row{std::string("x")},1},{}},
    {2,io::WindowInsert{2,TableId{0},Row{std::string("x")},1},{}},
    {3,io::WindowInsert{3,TableId{1},Row{std::string("x"),std::string("y")},1},{}},
    {4,io::WindowInsert{4,TableId{2},Row{std::string("y")},1},{}}};
  for(const auto& item:commands){command(*session,item,actual);command(*reference,item,expected);}
  check(session->status().committed_sequence==3 && session->progress().sequence==4,"duplicate label created a physical epoch");
  session->begin_reoptimization(*family.candidate(1),options());
  const io::WindowCommand watermark{5,io::AdvanceWatermark{30},{}};enqueue(*session,watermark);command(*reference,watermark,expected);
  check(session->begin_next(),"window barrier head missing");session->pause();session->request_reoptimization_barrier();
  const auto status=barrier(*session,actual);
  check(status.phase==reoptimization::Phase::verified && status.snapshot_epoch==3 && status.target_epoch==6 && status.source_epoch==6 &&
      status.replayed_records==3 && status.staged_records==3 && session->progress().sequence==5 && !session->status().window->active_command_sequence &&
      session->status().queue->events==0 && session->status().state==SessionState::paused,"window barrier verified a partial watermark or fabricated physical metadata epochs");
  check(actual==expected && session->window_state()==reference->window_state() && results(*session)==results(*reference),"window candidate changed output/controller state");
  session->cancel_reoptimization();
}
void durable(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,const Database& initial) {
  session_file_test::Directory directory;const auto root=directory.file("candidate.root"),sink=directory.file("candidate.sink");
  auto session=QuerySession::create_typed(plan,initial,{},session_options(DeltaMode::delta));session->start();
  session->enable_generation(root,generation_test::options());session->create_local_sink(sink,local_sink_test::options());
  const auto selected=session_file_test::contents(root);const auto origin=session->local_sink_state().persisted.header;
  session->begin_reoptimization(*family.candidate(1),options());
  enqueue(*session,io::InputEvent{{1,TableId{0},SetOperation::insert,Row{std::string("x")}},io::SourcePosition{"feed",10}});
  enqueue(*session,io::InputEvent{{2,TableId{1},SetOperation::erase,Row{std::string("x"),std::string("y")}},io::SourcePosition{"feed",20}});
  session->request_reoptimization_barrier();reoptimization::Status status;std::uint64_t delivered=0;bool empty=false;
  for(std::size_t i=0;i<10000;++i) {
    status=session->advance_reoptimization(1);
    if(session->status().phase==SessionPhase::output) {
      const auto result=session->deliver_local_epoch();check(result.kind==LocalDeliveryKind::published && result.sequence==++delivered && result.generation==1,"candidate barrier bypassed normal sink identity");
      if(result.sequence==1)empty=result.rows==0;
    }
    if(status.phase==reoptimization::Phase::verified || status.phase==reoptimization::Phase::failed || status.phase==reoptimization::Phase::rejected)break;
  }
  check(status.phase==reoptimization::Phase::verified && empty && delivered==2 && session->local_sink_state().verified_sequence==2 &&
      session->journal_state().physical_sequence==2 && !session->journal_state().pending_input &&
      session_file_test::contents(root)==selected && session->local_sink_state().persisted.header==origin,
      "candidate preparation changed durable selection/header or skipped an empty epoch");
  session->cancel_reoptimization();session.reset();
  auto restored=QuerySession::restore_generation_with_local_sink(CompiledProgram::standalone(plan),root,generation_test::recovery_options(),sink,local_sink_test::options());
  check(restored->status().committed_sequence==2 && restored->progress().sequence==2 && restored->local_sink_state().verified_sequence==2,
      "candidate-only preparation damaged original generation recovery");
}
} // namespace
int main(int argc,char** argv) {
  try {
    check(argc==2,"usage: reoptimization_session SOURCE");const auto fixture=c05_independent::boolean_fixture(argv[1]);std::size_t cases=0;
    for(const bool indexed:{false,true}) {
      const auto physical=indexed?s04_runtime::options():PhysicalOptions{};
      const auto cq=c05_independent::lower(fixture.by_label.at("native_s"),physical);
      const auto admitted=frontend::admit_sql("SELECT EXISTS(SELECT 1 FROM \"R\" r CROSS JOIN \"S\" s CROSS JOIN \"T\" t WHERE r.c0=s.c0 AND s.c1=t.c0);",fixture.document.catalog);
      check(admitted.status==frontend::AdmissionStatus::admitted,"SQL session candidate fixture rejected");
      const auto family=c05_independent::candidates(admitted.program->core_catalog,admitted.program->core);
      const auto sql=planner::lower_normalized(*admitted.program,family.candidate(0)->tree(),physical);
      for(const auto mode:{DeltaMode::maintenance,DeltaMode::delta})for(const auto method:{BuildMethod::direct,BuildMethod::insertion_replay}) {
        ordinary(cq,fixture.all,fixture.initial,mode,method);ordinary(sql,family,fixture.initial,mode,method);cases+=2;
      }
      failures(cq,fixture.all,fixture.initial);ledger_bytes(cq,fixture.all,fixture.initial);stream(sql,family,fixture.initial);
      for(const auto mode:{DeltaMode::maintenance,DeltaMode::delta})projected(fixture.document.catalog,physical,mode);
      for(const auto fifo:{WindowFifoPolicy::global,WindowFifoPolicy::per_relation})window(cq,fixture.all,fifo);
      durable(sql,family,fixture.initial);
    }
    std::cout<<"C06 candidate session preparation PASS: "<<cases<<" SQL/CQ/backend/mode/build cases, ordered noops, paused queue drain, exact source/results, limits/OOM/retry and unread stream barrier. Publication remains separate.\n";
    return 0;
  }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
