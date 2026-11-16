#pragma once
#include "local_sink_fixture.hpp"
#include "generation_detail.hpp"
namespace crown::history_retirement_test {
using namespace local_sink_test;
struct RetirementFixture {
  Directory directory;
  typed::Case test;
  runtime::CompiledProgram program;
  runtime::QuerySession::Owner session;
  std::string root,sink;
  Database database;
  std::array<typed::Output,3> expected;
  explicit RetirementFixture(bool indexed=false,unsigned kind=1):test(typed::fixture(indexed,kind)),program(runtime::CompiledProgram::standalone(test.plan)),
      session(runtime::QuerySession::create_typed(test.plan,{},session_journal_test::session_options(kind))),root(directory.file("query.root")),sink(directory.file("output.sink")) {
    database.tables.resize(test.plan.source_catalog().tables.size());auto config=generation_test::options();config.retained_generations=3;
    session->start();session->enable_generation(root,config);session->create_local_sink(sink,options());
    for(std::size_t i=0;i<3;++i){const auto before=typed::oracle(test,database);apply(database,test.updates[i]);const auto after=typed::oracle(test,database);expected[i]=kind==2?typed::Output{}:typed::difference(before,after);
      commit(i);static_cast<void>(session->deliver_local_epoch());if(i<2)session->rotate_generation();}
  }
  void commit(std::size_t index){typed::enqueue(*session,io::InputEvent{test.updates[index],io::SourcePosition{"feed",test.updates[index].sequence*10}});check(session->begin_next(),"retirement source input missing");finish(*session);}
  runtime::QuerySession::Owner restore(const runtime::SessionGenerationRecoveryOptions& recovery=generation_test::recovery_options()) const {return runtime::QuerySession::restore_generation_with_local_sink(program,root,recovery,sink,options());}
  std::string path(std::uint64_t generation,std::string_view suffix) const {return generation_test::path(root,generation,suffix);}
  void history(bool retained) const {
    for(std::uint64_t generation=1;generation<3;++generation)for(const auto suffix:{".ckpt",".wal"})check(std::filesystem::exists(path(generation,suffix))==retained,"retirement changed wrong old generation range");
    check(std::filesystem::exists(path(3,".ckpt")) && std::filesystem::exists(path(3,".wal")),"retirement removed selected native pair");
  }
  void verify() {
    session.reset();auto value=restore();check(value->status().committed_sequence==3 && value->progress().sequence==3 && typed::rows(*value)==typed::oracle(test,database) && value->local_sink_receipt().sequence()==3,"retirement recovery changed native state/source/output");
    value->retire_generation_history();history(false);check(!std::filesystem::exists(root+".retire") && value->generation_state().selected.first_generation==3 && !value->generation_state().retirement_pending,"retirement did not finish exact cleanup intent");
    for(std::uint64_t sequence=1;sequence<=3;++sequence)check(output(value->read_local_epoch(sequence))==expected[static_cast<std::size_t>(sequence-1)],"retirement changed accepted local output");
    value->start();typed::enqueue(*value,io::InputEvent{test.updates[3],io::SourcePosition{"feed",40}});check(value->begin_next(),"post-retirement input missing");finish(*value);static_cast<void>(value->deliver_local_epoch());
    auto next=database;apply(next,test.updates[3]);check(value->local_sink_receipt().sequence()==4 && typed::rows(*value)==typed::oracle(test,next),"post-retirement next native update differs");
  }
};
inline std::string wire(const recovery::detail::RetirementIntent& intent){const auto bytes=recovery::detail::encode_retirement_intent(intent);return {bytes.data(),bytes.size()};}
inline recovery::detail::RetirementIntent intent(const RetirementFixture& fixture) {
  const auto sink=fixture.session->local_sink_state();return {fixture.session->generation_state().selected,sink.persisted.header,sink.persisted.generation,sink.verified_sequence};
}
// Requires a complete encoded intent; recomputed integrity does not grant authority.
inline void checksum(std::string& bytes){const auto hash=sha256_fixed(std::string_view(bytes).substr(0,bytes.size()-64));std::copy(hash.begin(),hash.end(),bytes.end()-64);}
} // namespace crown::history_retirement_test
