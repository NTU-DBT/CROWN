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
using Output=std::set<std::pair<SetOperation,Row>>;
using Outputs=std::map<std::uint64_t,Output>;
struct SteadyMemory {std::uint64_t bytes,allocations;bool operator==(const SteadyMemory&) const=default;};
reoptimization::Options options(std::uint64_t round) {
  reoptimization::Options value;value.policy.minimum_epoch_gap=0;value.forecast=reoptimization::Forecast{1'000'000+round*100,1,UINT64_MAX};return value;
}
void enqueue(QuerySession& session,const PhysicalSetUpdate& update) {
  io::TransportBatch batch({io::InputEvent{update,io::SourcePosition{"wire",update.sequence*10}}});
  check(session.enqueue(batch)==io::Admission::accepted,"churn input was not admitted");
}
void reference_update(QuerySession& session,const PhysicalSetUpdate& update,Outputs& output) {
  enqueue(session,update);check(session.begin_next(),"churn reference event missing");local_sink_test::finish(session);
  auto& rows=output[update.sequence];while(auto row=session.next_output())check(rows.emplace(row->operation,storage::export_row(row->tuple.values())).second,"churn reference duplicated output");
}
void run(const PhysicalPlan& original,const planner::CandidateSnapshot& family,const Database& initial,const PhysicalOptions& physical,DeltaMode mode) {
  session_file_test::Directory directory;const auto root=directory.file("query.root"),sink=directory.file("results.sink");
  SessionOptions config;config.delta.mode=mode;config.delta.physical.support.memory_limit_bytes=32*1024*1024;
  auto session=QuerySession::create_typed(original,initial,{},config),reference=QuerySession::create_typed(original,initial,{},config);session->start();reference->start();
  auto generation=generation_test::options();generation.retained_generations=2;session->enable_generation(root,generation);
  auto sink_options=local_sink_test::options();sink_options.file.epochs=32;session->create_local_sink(sink,sink_options);
  const auto origin=session->local_sink_state().persisted.header;const auto account=session->report_metadata().plan().account();Outputs actual,expected;
  std::array<std::optional<SteadyMemory>,2> resident;
  for(std::uint64_t round=1;round<=16;++round) {
    const std::size_t selected=round%2?1:0;const auto member=*family.candidate(selected);
    session->begin_reoptimization(member,options(round));
    const PhysicalSetUpdate changed{round*2-1,TableId{1},round%2?SetOperation::erase:SetOperation::insert,*initial.tables[1].begin()},
        noop{round*2,TableId{0},SetOperation::insert,*initial.tables[0].begin()};
    for(const auto& update:{changed,noop}){enqueue(*session,update);reference_update(*reference,update,expected);}
    const bool paused=round%3==0;if(paused)session->pause();session->request_reoptimization_barrier();reoptimization::Status ready;
    for(std::size_t step=0;step<10000;++step) {
      ready=session->advance_reoptimization(1);
      if(session->status().phase==SessionPhase::output) {
        const auto delivered=session->deliver_local_epoch();const auto epoch=session->read_local_epoch(delivered.sequence);
        check(actual.emplace(delivered.sequence,local_sink_test::output(epoch)).second,"churn repeated a public delivery");
      }
      if(ready.phase==reoptimization::Phase::verified)break;
    }
    check(ready.phase==reoptimization::Phase::verified && ready.replayed_records==2 && ready.source_epoch==round*2 && actual==expected,
        "churn lost exact catch-up/output through changing plans/data");
    workload::Options counters;counters.mode=workload::Mode::counters;counters.period=round%2?1:3;session->configure_workload_statistics(counters);
    {
      const auto target=planner::lower_tree(member.catalog(),member.query(),member.tree(),physical);
      auto artifact=io::CompilerPlanArtifact::prepare(resource::MemoryAccount::create(32*1024*1024),target);
      check(session->publish_reoptimization(artifact).phase==reoptimization::Phase::complete,"churn native installation failed");
    }
    check(session->status().state==(paused?SessionState::paused:SessionState::running) && session->workload_statistics_options()==counters &&
        session->report_metadata().plan().account().statistics().owner==account.statistics().owner && session->local_sink_state().persisted.header==origin,
        "churn changed pause/configuration/account or immutable sink origin");
    session->retire_generation_history();const auto state=session->generation_state().selected;
    check(state.first_generation==state.generation && state.generation==round+1 && !std::filesystem::exists(generation_test::path(root,round,".plan")) &&
        !std::filesystem::exists(generation_test::path(root,round,".ckpt")) && !std::filesystem::exists(generation_test::path(root,round,".wal")),
        "churn retained historical plan dependencies or exhausted its two-generation budget");
    const auto memory=account.statistics();check(memory.peak_requested_bytes<=32*1024*1024,"churn escaped finite original heap");
    // Refactor.md permits a declared retained recovery log. Subtract only the
    // sink's actual reported vector requests; they remain in the heap cap/peak.
    const auto log_buffers=session->local_sink_state().persisted.buffer_bytes;
    check(log_buffers<=memory.current.requested_bytes,"sink buffers exceed original-account current bytes");
    const SteadyMemory steady{memory.current.requested_bytes-log_buffers,memory.current.allocations};
    if(round>=5) {
      if(resident[selected])check(steady==*resident[selected],"repeated switch/retirement grew native ownership beyond declared sink buffers");
      else resident[selected]=steady;
    }
    account.check_invariants();session->start();
  }
  check(actual==expected && session->progress()==reference->progress() && session->snapshot().rows.size()==reference->snapshot().rows.size(),"churn final source/results differ");
  session.reset();const auto released=account.statistics();
  check(released.current==released.by_purpose[static_cast<std::size_t>(resource::MemoryPurpose::control)],"churn retained native state after complete owner release");
  auto locked=QuerySession::lock_generation_recovery(CompiledProgram::standalone(original),root,generation_test::recovery_options());
  auto artifact=io::CompilerPlanArtifact::replay(resource::MemoryAccount::create(32*1024*1024),locked->compiler_artifact());
  session=QuerySession::restore_selected_generation_with_local_sink(std::move(locked),artifact,sink,local_sink_test::options());
  check(session->status().committed_sequence==32 && session->progress()==reference->progress() && session->snapshot().rows.size()==1 &&
      session->local_sink_state().persisted.header==origin,"churn recovery required retired plans or lost its final native boundary");
}
} // namespace
int main(int argc,char** argv) {
  try {
    check(argc==2,"usage: reoptimization_churn SOURCE");const auto fixture=c05_independent::boolean_fixture(argv[1]);
    for(const bool indexed:{false,true}) {
      const auto physical=indexed?s04_runtime::options():PhysicalOptions{};const auto original=c05_independent::lower(*fixture.all.candidate(0),physical);
      for(const auto mode:{DeltaMode::maintenance,DeltaMode::delta})run(original,fixture.all,fixture.initial,physical,mode);
    }
    std::cout<<"C06 churn PASS:64 switches,128 physical inputs across both backends/modes; exact non-switching output, changing forecasts/configuration/pause,32MiB original heap, two-generation/32-epoch sink limits, steady native ownership excluding actual reported sink buffers, complete release and recovery after historical plan deletion.\n";return 0;
  }catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}
