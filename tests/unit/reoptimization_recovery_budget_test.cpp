#include "selection_independent_fixture.hpp"
#include "indexed_runtime_fixture.hpp"
#include "local_sink_fixture.hpp"
#include "crown/io/compiler_plan_artifact.hpp"
#include "crown/runtime/session_reoptimization.hpp"
#include <iostream>

namespace {
using namespace crown;
using namespace crown::runtime;
using c05_independent::check;
reoptimization::Options options() {
  reoptimization::Options value;value.forecast=reoptimization::Forecast{1'000'000'000,1,UINT64_MAX};return value;
}
struct Fixture {
  session_file_test::Directory directory;
  std::string root=directory.file("query.root"),sink=directory.file("results.sink"),wal;
  CompiledProgram source;
  io::CompilerPlanArtifact artifact;
  std::map<std::string,std::string> saved;
  recovery::sink::Header origin;
  Fixture(const PhysicalPlan& plan,const PhysicalPlan& target,const planner::MinimumHeightCandidate& candidate,const Database& initial)
      :source(CompiledProgram::standalone(plan)),artifact(io::CompilerPlanArtifact::prepare(resource::MemoryAccount::create(32*1024*1024),target)) {
    SessionOptions config;config.delta.physical.support.memory_limit_bytes=64*1024*1024;
    auto session=QuerySession::create_typed(plan,initial,{},config);session->start();session->enable_generation(root,generation_test::options());
    session->create_local_sink(sink,local_sink_test::options());origin=session->local_sink_state().persisted.header;
    session->begin_reoptimization(candidate,options());
    const auto commit=[&](std::uint64_t sequence,TableId table,SetOperation operation,const Row& row) {
      io::TransportBatch batch({io::InputEvent{{sequence,table,operation,row},io::SourcePosition{"wire",sequence*10}}});
      check(session->enqueue(batch)==io::Admission::accepted && session->begin_next(),"recovery budget input missing");local_sink_test::finish(*session);
      check(session->deliver_local_epoch().sequence==sequence,"recovery budget output missing");
    };
    commit(1,TableId{1},SetOperation::erase,*initial.tables[1].begin());commit(2,TableId{1},SetOperation::insert,*initial.tables[1].begin());
    session->request_reoptimization_barrier();check(session->advance_reoptimization(100000).phase==reoptimization::Phase::verified,"recovery budget candidate did not verify");
    check(session->publish_reoptimization(artifact).phase==reoptimization::Phase::complete,"recovery budget switch failed");
    commit(3,TableId{0},SetOperation::insert,*initial.tables[0].begin());session.reset();wal=generation_test::path(root,2,".wal");
    generation_test::put(wal,session_file_test::contents(wal)+"CROWN");generation_test::put(sink,session_file_test::contents(sink)+"CROWN");
    for(const auto& path:{root,sink,wal,generation_test::path(root,2,".ckpt"),generation_test::path(root,2,".plan")})saved.emplace(path,session_file_test::contents(path));
  }
  void reset() const {for(const auto& [path,bytes]:saved)generation_test::put(path,bytes);}
  void intact() const {for(const auto& [path,bytes]:saved)check(session_file_test::contents(path)==bytes,"recovery allocation/cap rejection repaired or changed durable bytes");}
  QuerySession::Owner restore(SessionGenerationRecoveryOptions config=generation_test::recovery_options()) {
    auto locked=QuerySession::lock_generation_recovery(source,root,config);
    return QuerySession::restore_selected_generation_with_local_sink(std::move(locked),artifact,sink,local_sink_test::options());
  }
  void verify(QuerySession& session) const {
    check(session.status().committed_sequence==3 && session.progress().sequence==3 && session.snapshot().rows.size()==1 &&
        session.local_sink_state().verified_sequence==3 && session.local_sink_state().persisted.header==origin,
        "selected recovery changed state/progress or immutable sink lineage");
    check(session_file_test::contents(wal).size()+5==saved.at(wal).size() && session_file_test::contents(sink).size()+5==saved.at(sink).size(),
        "valid selected recovery did not repair both validated tails");
  }
};
std::size_t sweep(Fixture& fixture) {
  std::size_t allocations=0;std::uint64_t peak=0;
  {
    QuerySession::Owner session;
    {s04_alloc::Scope count;session=fixture.restore();allocations=s04_alloc::calls;}
    const auto measured=session->accounted_memory_statistics();
    check(measured->successful_allocations==allocations,"locked/native recovery escaped the original receiving account");
    peak=measured->peak_requested_bytes;fixture.verify(*session);
  }
  check(allocations>0 && allocations<10000,"recovery allocation sweep has no finite measured bound");
  for(std::size_t point=0;point<allocations;++point) {
    fixture.reset();const auto descriptors=session_file_test::descriptors();bool failed=false,triggered=false;
    {s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{static_cast<void>(fixture.restore());}catch(const std::bad_alloc&){failed=true;}triggered=s04_alloc::triggered;}
    check(failed && triggered && session_file_test::descriptors()==descriptors,"locked/native recovery OOM was missed or retained a writer lock");fixture.intact();
    auto retry=fixture.restore();fixture.verify(*retry);
  }
  fixture.reset();auto exact=generation_test::recovery_options();exact.replay.memory_limit_bytes=peak;
  {auto session=fixture.restore(exact);fixture.verify(*session);check(session->accounted_memory_statistics()->peak_requested_bytes==peak,"exact receiving heap cap changed peak accounting");}
  fixture.reset();--*exact.replay.memory_limit_bytes;bool denied=false;
  try{static_cast<void>(fixture.restore(exact));}catch(const resource::MemoryFailure& failure){denied=failure.fault()==resource::MemoryFault::limit;}
  check(denied,"one-under receiving heap cap admitted selected recovery");fixture.intact();
  auto retry=fixture.restore();fixture.verify(*retry);return allocations;
}
} // namespace
int main(int argc,char** argv) {
  try {
    check(argc==2,"usage: reoptimization_recovery_budget SOURCE");const auto model=c05_independent::boolean_fixture(argv[1]);std::size_t points=0;
    for(const bool indexed:{false,true}) {
      const auto physical=indexed?s04_runtime::options():PhysicalOptions{};
      const auto original=c05_independent::lower(*model.all.candidate(0),physical),target=c05_independent::lower(*model.all.candidate(1),physical);
      Fixture fixture(original,target,*model.all.candidate(1),model.initial);points+=sweep(fixture);
    }
    std::cout<<"C06 selected recovery budget PASS: "<<points<<" actual allocation cuts across both backends; original receiving account, exact/one-under heap, complete rollback of rejected admission before WAL/sink tail repair, root-lock release and retry.\n";return 0;
  }catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}
