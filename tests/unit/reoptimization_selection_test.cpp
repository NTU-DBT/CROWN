#include "selection_independent_fixture.hpp"
#include "indexed_runtime_fixture.hpp"
#include "local_sink_fixture.hpp"
#include "crown/frontend/admission.hpp"
#include "crown/io/compiler_plan_artifact.hpp"
#include <iostream>

namespace {
using namespace crown;
using namespace crown::runtime;
using c05_independent::check;
namespace rs=runtime::selection;
namespace ps=planner::selection;
using Output=std::set<std::pair<SetOperation,Row>>;
Relation rows(QuerySession& session) {
  Relation result;for(const auto& row:session.snapshot().rows)result.insert(storage::export_row(row.values()));return result;
}
reoptimization::Options options() {
  reoptimization::Options value;value.forecast=reoptimization::Forecast{1'000'000'000,1,UINT64_MAX};return value;
}
template<class Function> void rejected(Function&& function,std::string_view code) {
  try{function();}catch(const Error& failure){check(failure.code()==code,"C05 bridge rejected with wrong reason");return;}
  throw std::runtime_error("C05 bridge accepted an invalid selection boundary");
}
Output update(QuerySession& session,std::uint64_t sequence,TableId table,SetOperation operation,const Row& row) {
  io::TransportBatch batch({io::InputEvent{{sequence,table,operation,row},io::SourcePosition{"wire",sequence*10}}});
  check(session.enqueue(batch)==io::Admission::accepted && session.begin_next(),"C05 bridge input missing");local_sink_test::finish(session);
  Output result;while(auto value=session.next_output())check(result.emplace(value->operation,storage::export_row(value->tuple.values())).second,"C05 bridge repeated output");return result;
}
ps::Request request(ps::Policy policy) {
  ps::Request value;value.policy=policy;value.fallback=planner::ranking::Fallback::require_evidence;return value;
}
rs::CurrentSelection measured(QuerySession& session,const planner::CandidateSnapshot& family,ps::Policy policy=ps::Policy::height_only) {
  const ps::Source source=ps::PhysicalBasis{session.report_metadata().plan()};
  auto attempt=rs::select_for_reoptimization(family,source,session,request(policy));
  check(attempt.stop==ps::Stop::complete && attempt.selection && attempt.selection->preparation_nanoseconds().value_or(0)>0,
      "explicit C05 selection did not report complete wall preparation time");return *attempt.selection;
}
void stale(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,const Database& initial) {
  auto session=QuerySession::create_typed(plan,initial);session->start();const auto owner=session->report_metadata().owner();
  const ps::Source source=ps::PhysicalBasis{session->report_metadata().plan()};
  auto ordinary=rs::select_current(family,source,*session,request(ps::Policy::height_only));
  check(ordinary.selection && !ordinary.selection->preparation_nanoseconds(),"ordinary C05 selection gained implicit wall timing");
  rejected([&]{rs::begin_reoptimization(*session,*ordinary.selection,options());},"reoptimization_unmeasured_selection");
  auto choice=measured(*session,family);auto wrong=options();wrong.expected=reoptimization::Boundary{owner.value+1,0};
  rejected([&]{rs::begin_reoptimization(*session,choice,wrong);},"reoptimization_stale_source");
  auto foreign=QuerySession::create_typed(plan,initial);foreign->start();
  rejected([&]{rs::begin_reoptimization(*foreign,choice,options());},"reoptimization_stale_selection");
  static_cast<void>(update(*session,1,TableId{0},SetOperation::insert,*initial.tables[0].begin()));
  rejected([&]{rs::begin_reoptimization(*session,choice,options());},"reoptimization_stale_selection");
  choice=measured(*session,family);session->reset_workload_statistics();
  rejected([&]{rs::begin_reoptimization(*session,choice,options());},"reoptimization_stale_selection");
  choice=measured(*session,family);workload::Options counters;counters.mode=workload::Mode::counters;counters.period=2;session->configure_workload_statistics(counters);
  rejected([&]{rs::begin_reoptimization(*session,choice,options());},"reoptimization_stale_selection");
  choice=measured(*session,family);io::TransportBatch batch({io::InputEvent{{2,TableId{1},SetOperation::erase,*initial.tables[1].begin()},{}}});
  check(session->enqueue(batch)==io::Admission::accepted && session->begin_next(),"C05 bridge pending fixture missing");
  rejected([&]{rs::begin_reoptimization(*session,choice,options());},"reoptimization_stale_selection");
  check(session->status().committed_sequence==1 && session->status().pending_sequence==2,"stale selection altered the pending native epoch");
  local_sink_test::finish(*session);while(session->next_output()){}
  auto limits=request(ps::Policy::height_only);limits.limits.aggregate.work=0;
  const auto denied=rs::select_for_reoptimization(family,source,*session,limits);
  check(!denied.selection && denied.stop==ps::Stop::resource_limit && session->report_metadata().owner()==owner &&
      session->status().committed_sequence==2 && session->reoptimization_status().phase==reoptimization::Phase::inactive,
      "failed/stale C05 selection altered current native owner/state");
}
template<class Lower> void install(const PhysicalPlan& plan,const planner::CandidateSnapshot& family,const Database& initial,Lower&& lower) {
  session_file_test::Directory directory;const auto root=directory.file("selected.root");
  auto session=QuerySession::create_typed(plan,initial),reference=QuerySession::create_typed(plan,initial);session->start();reference->start();
  session->enable_generation(root,generation_test::options());workload::Options counters;counters.mode=workload::Mode::counters;counters.detail_budget=0;
  session->configure_workload_statistics(counters);
  for(std::uint64_t sequence=1;sequence<=8;++sequence) {
    check(update(*session,sequence,TableId{0},SetOperation::insert,*initial.tables[0].begin())==
        update(*reference,sequence,TableId{0},SetOperation::insert,*initial.tables[0].begin()),"C05 bridge prefix differs");
  }
  const auto account=session->report_metadata().plan().account();const auto before=account.statistics().successful_allocations;
  std::optional<rs::CurrentSelection> choice;std::size_t calls=0;
  {s04_alloc::Scope count;choice=measured(*session,family,ps::Policy::committed_input_native_depth);calls=s04_alloc::calls;}
  check(calls==account.statistics().successful_allocations-before,"measured C05 selection escaped the actual query account");
  session->pause();rs::begin_reoptimization(*session,*choice,options());
  check(session->reoptimization_status().costs.selection_prepare_ns>=*choice->preparation_nanoseconds() &&
      session->reoptimization_status().costs.selection_prepare_ns>0,"C05 selection/freshness preparation was omitted from native payback");
  session->request_reoptimization_barrier();const auto ready=session->advance_reoptimization(100000);
  check(ready.phase==reoptimization::Phase::verified && ready.source_epoch==8 && ready.target_epoch==8,"C05 checked choice failed native equivalence");
  const auto target=lower(choice->selection().selected().tree());const auto compiler=resource::MemoryAccount::create(32*1024*1024);
  auto artifact=io::CompilerPlanArtifact::prepare(compiler,choice->selection().plan());
  check(artifact.bytes()==io::write_physical(target).dump(),"native selection compiler export differs from independent canonical lowering");
  auto replay=io::CompilerPlanArtifact::replay(compiler,artifact.bytes());
  check(replay.program().physical_sha256()==choice->selection().plan().physical_sha256(),"native selection compiler input cannot replay its complete artifact");
  const auto installed=session->publish_reoptimization(artifact);
  check(installed.phase==reoptimization::Phase::complete && session->status().state==SessionState::paused &&
      session->report_metadata().plan().physical_sha256()==choice->selection().plan().physical_sha256() &&
      installed.query_memory.owner==account.statistics().owner && installed.decision.charged_and_reserved_ns>=installed.costs.selection_prepare_ns,
      "C05 choice installation changed pause/target/account or hid selection cost");
  rejected([&]{rs::begin_reoptimization(*session,*choice,options());},"reoptimization_stale_selection");session->start();
  check(update(*session,9,TableId{1},SetOperation::erase,*initial.tables[1].begin())==
      update(*reference,9,TableId{1},SetOperation::erase,*initial.tables[1].begin()) && rows(*session)==rows(*reference) &&
      session->progress()==reference->progress(),"C05 selected plan next output/epoch differs");
}
} // namespace
int main(int argc,char** argv) {
  try {
    check(argc==2,"usage: reoptimization_selection SOURCE");const auto fixture=c05_independent::boolean_fixture(argv[1]);
    for(const bool indexed:{false,true}) {
      const auto physical=indexed?s04_runtime::options():PhysicalOptions{};
      const auto plan=c05_independent::lower(fixture.by_label.at("native_s"),physical);stale(plan,fixture.all,fixture.initial);
      install(plan,fixture.all,fixture.initial,[&](const FreeConnexTree& tree){return planner::lower_tree(fixture.document.catalog,fixture.document.query,tree,physical);});
      const auto admitted=frontend::admit_sql("SELECT EXISTS(SELECT 1 FROM \"R\" r CROSS JOIN \"S\" s CROSS JOIN \"T\" t WHERE r.c0=s.c0 AND s.c1=t.c0);",fixture.document.catalog);
      check(admitted.status==frontend::AdmissionStatus::admitted,"C05 bridge SQL fixture rejected");
      const auto family=c05_independent::candidates(admitted.program->core_catalog,admitted.program->core);
      const auto original=planner::lower_normalized(*admitted.program,family.candidate(0)->tree(),physical);
      install(original,family,fixture.initial,[&](const FreeConnexTree& tree){return planner::lower_normalized(*admitted.program,tree,physical);});
    }
    std::cout<<"C06 optional C05 bridge PASS: measured CQ/SQL selections on both backends, original-account capture, complete selection/freshness cost in native payback, exact installation/next output, and unmeasured/foreign/stale/reset/configuration/private/budget rejection.\n";return 0;
  }catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}
