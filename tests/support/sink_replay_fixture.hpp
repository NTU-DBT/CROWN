#pragma once
#include "local_sink_fixture.hpp"
namespace crown::sink_replay_test {
using namespace local_sink_test;
// Full ordinary sink snapshot and oracle data; source session is closed before restore.
struct Saved {
  Fixture source;
  runtime::CompiledProgram program;
  std::string sink,log,checkpoint;
  std::array<typed::Output,3> expected;
  Database database;
  explicit Saved(bool indexed=false,unsigned kind=1):source(indexed,kind),program(runtime::CompiledProgram::standalone(source.query.test.plan)),
      log(generation_test::path(source.query.name,1,".wal")),checkpoint(generation_test::path(source.query.name,1,".ckpt")) {
    database.tables.resize(source.query.test.plan.source_catalog().tables.size());
    for(std::size_t i=0;i<3;++i) {
      const auto before=typed::oracle(source.query.test,database);apply(database,source.query.test.updates[i]);
      const auto after=typed::oracle(source.query.test,database);expected[i]=kind==2?typed::Output{}:typed::difference(before,after);
      source.commit(i);static_cast<void>(source.query.session->deliver_local_epoch());
    }
    source.query.session.reset();sink=contents(source.path);
  }
  // accepted is 0..3 for this known four-frame sink; this deliberately writes a torn file.
  void prefix(std::size_t accepted,bool torn=false) {
    const auto frames=session_journal_test::frames(sink);std::string value;
    for(std::size_t i=0;i<=accepted;++i)value.append(frames[i]);
    if(torn)value.append(frames[accepted<3?accepted+1:3].substr(0,85));
    generation_test::put(source.path,value);
  }
  runtime::QuerySession::Owner restore(const runtime::SessionGenerationRecoveryOptions& recovery=generation_test::recovery_options(),
      const runtime::SessionLocalSinkOptions& delivery=options(),bool direct=false) {
    if(direct)return runtime::QuerySession::restore_journal_with_local_sink(program,checkpoint,log,recovery.replay,source.path,delivery);
    return runtime::QuerySession::restore_generation_with_local_sink(program,source.query.name,recovery,source.path,delivery);
  }
  void verify() {
    auto value=restore();check(value->status().committed_sequence==3 && value->progress().sequence==3 && typed::rows(*value)==typed::oracle(source.query.test,database),"sink-aware restart lost native state/source");
    while(value->deliver_local_epoch().kind!=runtime::LocalDeliveryKind::idle){}
    check(value->local_sink_receipt().sequence()==3 && contents(source.path)==sink,"sink-aware retry lost or duplicated durable output");
    for(std::uint64_t sequence=1;sequence<=3;++sequence)check(output(value->read_local_epoch(sequence))==expected[static_cast<std::size_t>(sequence-1)],"sink-aware retry output differs from oracle");
    value->start();typed::enqueue(*value,io::InputEvent{source.query.test.updates[3],io::SourcePosition{"feed",40}});check(value->begin_next(),"sink-aware next event unavailable");finish(*value);static_cast<void>(value->deliver_local_epoch());
    auto next=database;apply(next,source.query.test.updates[3]);check(typed::rows(*value)==typed::oracle(source.query.test,next) && value->local_sink_receipt().sequence()==4,"sink-aware next update changed live state");
  }
};
} // namespace crown::sink_replay_test
