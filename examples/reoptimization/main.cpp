#include "crown/frontend/admission.hpp"
#include "crown/io/compiler_plan_artifact.hpp"
#include "crown/planner/search.hpp"
#include "crown/runtime/selection.hpp"
#include "crown/runtime/session_local_sink.hpp"
#include "crown/runtime/session_reoptimization.hpp"
#include <filesystem>
#include <iostream>

namespace {
using namespace crown;
using namespace crown::runtime;
void check(bool value,const char* message) {if(!value)throw std::runtime_error(message);}
planner::CandidateSnapshot candidates(const Catalog& catalog,const Query& query) {
  auto search=planner::ExactSearch::create(catalog,query);std::optional<planner::VerifiedOptimum> proof;
  for(unsigned call=0;call<2000 && !proof;++call) {
    const auto next=search.advance({10000,{}});
    if(next.progress.result==planner::ResultKind::verified_optimum)proof=search.optimum();
    else check(next.stopped_for==planner::StopReason::quantum_work,"example exact search exhausted its finite grant");
  }
  check(proof.has_value(),"example exact search call bound exhausted");auto provider=planner::CandidateProvider::create(*proof);
  for(unsigned call=0;call<2000;++call) {
    const auto next=provider.advance({10000,{}});if(next.stopped_for==planner::CandidateStop::exhausted)return provider.snapshot();
    check(next.stopped_for==planner::CandidateStop::candidate_ready || next.stopped_for==planner::CandidateStop::quantum_work,"example candidate enumeration exhausted its finite grant");
  }
  throw std::runtime_error("example candidate call bound exhausted");
}
PhysicalOptions physical_options(bool indexed) {
  PhysicalOptions value;
  if(indexed)value.indexed_storage=storage::IndexedBackendSpec{
      {4096,64,32768,65536,131072,524288,8192,32768,8192},
      {1'000'000'000,1'000'000'000,1'000'000'000,1'000'000'000,1'000'000'000}};
  return value;
}
SessionGenerationOptions generation_options() {
  SessionGenerationOptions value;constexpr std::string_view id="0123456789abcdef0123456789abcdef";
  std::copy(id.begin(),id.end(),value.journal.query_id.begin());value.retained_generations=3;return value;
}
SessionLocalSinkOptions sink_options() {
  SessionLocalSinkOptions value;constexpr std::string_view id="fedcba9876543210fedcba9876543210";
  std::copy(id.begin(),id.end(),value.sink_id.begin());value.file.epochs=64;return value;
}
void update(QuerySession& session,std::uint64_t sequence,TableId table,SetOperation operation,Row row) {
  io::TransportBatch batch({io::InputEvent{{sequence,table,operation,std::move(row)},io::SourcePosition{"wire",sequence*10}}});
  check(session.enqueue(batch)==io::Admission::accepted && session.begin_next(),"example update was not admitted");
  while(session.step()!=DeltaStep::prepared){}session.commit();check(session.deliver_local_epoch().sequence==sequence,"example output epoch was not delivered");
}
// Fixed data, IDs and forecast values are demo inputs; all native admission still runs.
void execute(std::string_view action,const std::filesystem::path& directory,bool indexed) {
  const Catalog catalog{41,{{"R",{{"x",ScalarType::string}}},{"S",{{"x",ScalarType::string},{"y",ScalarType::string}}},{"T",{{"y",ScalarType::string}}}}};
  const auto admitted=frontend::admit_sql("SELECT EXISTS(SELECT 1 FROM \"R\" r CROSS JOIN \"S\" s CROSS JOIN \"T\" t WHERE r.x=s.x AND s.y=t.y);",catalog);
  check(admitted.status==frontend::AdmissionStatus::admitted,"example SQL was not admitted");const auto family=candidates(admitted.program->core_catalog,admitted.program->core);
  std::size_t original_index=0;
  for(std::size_t i=0;i<family.candidate_count();++i) {
    const auto member=family.candidate(i);const auto& tree=member->tree();
    if(tree.root && tree.nodes[tree.root->value].kind==NodeKind::native){original_index=i;break;}
  }
  const auto original=planner::lower_normalized(*admitted.program,family.candidate(original_index)->tree(),physical_options(indexed));
  const auto root=(directory/"query.root").string(),sink=(directory/"results.sink").string();QuerySession::Owner session;
  io::Json report;report["backend"]=indexed?"indexed":"reference";
  if(action=="run") {
    std::filesystem::create_directories(directory);Database initial;initial.tables={Relation{Row{std::string("x")}},Relation{Row{std::string("x"),std::string("y")}},Relation{Row{std::string("y")}}};
    SessionOptions config;config.delta.mode=DeltaMode::delta;config.delta.physical.support.memory_limit_bytes=32*1024*1024;
    session=QuerySession::create_typed(original,initial,{},config);session->start();session->enable_generation(root,generation_options());session->create_local_sink(sink,sink_options());
    workload::Options counters;counters.mode=workload::Mode::counters;counters.detail_budget=0;session->configure_workload_statistics(counters);
    for(std::uint64_t sequence=1;sequence<=8;++sequence)update(*session,sequence,TableId{0},SetOperation::insert,Row{std::string("x")});
    planner::selection::Request request;request.fallback=planner::ranking::Fallback::require_evidence;
    const planner::selection::Source source=planner::selection::PhysicalBasis{session->report_metadata().plan()};
    auto selected=selection::select_for_reoptimization(family,source,*session,request);check(selected.selection && selected.stop==planner::selection::Stop::complete,"example measured C05 selection failed");
    reoptimization::Options migration;migration.forecast=reoptimization::Forecast{1'000'000,1,1'000'000}; // Declared prediction, not measured C02 cost.
    session->pause();selection::begin_reoptimization(*session,*selected.selection,migration);session->request_reoptimization_barrier();
    check(session->advance_reoptimization(100000).phase==reoptimization::Phase::verified,"example candidate did not verify");
    // This explicit compiler boundary measures DTO export and canonical replay.
    const auto compiler=resource::MemoryAccount::create(32*1024*1024);auto artifact=io::CompilerPlanArtifact::prepare(compiler,selected.selection->selection().plan());
    const auto installed=session->publish_reoptimization(artifact);check(installed.phase==reoptimization::Phase::complete,"example plan publication failed");
    check(session->status().state==SessionState::paused && original.physical_sha256()!=session->report_metadata().plan().physical_sha256(),"example did not preserve pause while changing physical trees");
    report["selection_ns"]=installed.costs.selection_prepare_ns;report["compiler_ns"]=installed.costs.compiler_artifact_ns;report["switched"]=true;
    session->start();update(*session,9,TableId{1},SetOperation::erase,Row{std::string("x"),std::string("y")});session->rotate_generation();session->retire_generation_history();
  }else {
    check(action=="resume","usage: crown_reoptimization run|resume DIRECTORY reference|indexed");SessionGenerationRecoveryOptions recovery;recovery.replay.journal=generation_options().journal;
    // Keep this exact root lock through compiler replay and receiving-account admission.
    auto locked=QuerySession::lock_generation_recovery(CompiledProgram::standalone(original),root,recovery);
    auto artifact=io::CompilerPlanArtifact::replay(resource::MemoryAccount::create(32*1024*1024),locked->compiler_artifact());
    session=QuerySession::restore_selected_generation_with_local_sink(std::move(locked),artifact,sink,sink_options());
    session->start();update(*session,10,TableId{1},SetOperation::insert,Row{std::string("x"),std::string("y")});
  }
  const auto snapshot=session->snapshot();check(snapshot.rows.size()==1 && snapshot.rows.front().values().size()==1,"example EXISTS result shape differs");
  const auto state=session->generation_state().selected;const auto delivery=session->local_sink_state();
  report["sequence"]=snapshot.sequence;report["sink_sequence"]=delivery.verified_sequence;report["generation"]=state.generation;report["first_generation"]=state.first_generation;
  report["exists"]=std::get<bool>(snapshot.rows.front().values()[0]);report["origin_generation"]=delivery.persisted.header.first_generation;
  report["source_offset"]=session->progress().source_positions.at("wire");std::cout<<report.dump()<<'\n';
}
} // namespace
int main(int argc,char** argv) {
  try {check(argc==4,"usage: crown_reoptimization run|resume DIRECTORY reference|indexed");const std::string_view backend=argv[3];check(backend=="reference" || backend=="indexed","unknown example backend");execute(argv[1],argv[2],backend=="indexed");std::cout.flush();return std::cout?0:1;}
  catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}
