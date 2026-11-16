#include "sink_replay_fixture.hpp"
#include "session_journal_stream_cases.hpp"
#include "crown/api/error.hpp"
using namespace crown;
using namespace crown::runtime;
using namespace crown::sink_replay_test;
namespace {
void typed_case(bool indexed,unsigned kind,std::size_t accepted) {
  Saved saved(indexed,kind);saved.prefix(accepted);const auto old=contents(saved.source.path),wal=contents(saved.log);
  std::size_t remaining=0;for(std::size_t i=accepted;i<3;++i)remaining+=saved.expected[i].size();
  auto recovery=generation_test::recovery_options();recovery.replay.output_rows=remaining;if(remaining==0)recovery.replay.output_bytes=0;
  auto value=saved.restore(recovery,options(),accepted%2==0);const auto sink=value->local_sink_state();
  check(value->status().state==SessionState::paused && value->status().committed_sequence==3 && value->progress().sequence==3 &&
      typed::rows(*value)==typed::oracle(saved.source.query.test,saved.database),"sink-aware native state/source/control differs");
  check(sink.enabled && sink.verified_sequence==accepted && sink.persisted.sequence==accepted && sink.replaying==(accepted<3) &&
      value->recovery_status().output_remaining==remaining && (remaining!=0 || value->recovery_status().output_bytes==0),"acknowledged replay was buffered or missing replay lost");
  check(contents(saved.source.path)==old && contents(saved.log)==wal,"sink-aware reconstruction published new output or changed a complete journal");
  for(std::size_t i=accepted;i<3;++i) {
    const auto delivered=value->deliver_local_epoch();check(delivered.kind==LocalDeliveryKind::published && delivered.sequence==i+1,"sink-aware delivery repeated a previously durable epoch");
  }
  check(value->deliver_local_epoch().kind==LocalDeliveryKind::idle && value->local_sink_receipt().sequence()==3 && contents(saved.source.path)==saved.sink,"sink-aware full prefix differs");
  for(std::uint64_t sequence=1;sequence<=3;++sequence)check(output(value->read_local_epoch(sequence))==saved.expected[static_cast<std::size_t>(sequence-1)],"sink-aware canonical output differs from independent oracle");
  value.reset();saved.verify();
  std::cout<<"sink-aware typed indexed="<<indexed<<" query="<<kind<<" accepted="<<accepted<<" exact output cap/native identity/next update passed\n";
}
void rotation() {
  Fixture f;for(std::size_t i=0;i<3;++i){f.commit(i);static_cast<void>(f.query.session->deliver_local_epoch());}f.query.session->rotate_generation();f.commit(3);
  const auto expected=typed::rows(*f.query.session);f.query.session.reset();
  auto value=QuerySession::restore_generation_with_local_sink(CompiledProgram::standalone(f.query.test.plan),f.query.name,generation_test::recovery_options(),f.path,options());
  check(value->local_sink_state().verified_sequence==3 && value->local_sink_state().persisted.header.base_sequence==0 && typed::rows(*value)==expected,"older sink origin did not bind the selected generation");
  const auto delivery=value->deliver_local_epoch();check(delivery.kind==LocalDeliveryKind::published && delivery.generation==2 && delivery.sequence==4 && value->local_sink_receipt().sequence()==4,"sink-aware generation output identity differs");
  std::cout<<"sink-aware rotation preserves original sink baseline and current epoch generation passed\n";
}
void stream_case(bool indexed,const session_journal_stream_test::Case& profile,bool pending) {
  Directory dir;const auto test=typed::fixture(indexed,1);const auto root=dir.file("stream.root"),path=dir.file("output.sink");SessionOptions config;config.input=profile.options;
  auto source=QuerySession::create(test.plan,std::make_unique<std::istringstream>(profile.data),config);source->start();source->enable_generation(root,generation_test::options());source->create_local_sink(path,options());
  check(source->begin_next(),"sink-aware first stream input absent");finish(*source);static_cast<void>(source->deliver_local_epoch());check(source->begin_next(),"sink-aware second stream input absent");if(!pending)finish(*source);source.reset();
  auto recovery=generation_test::recovery_options();recovery.replay.seek_source_from_origin=true;if(pending){recovery.replay.output_rows=0;recovery.replay.output_bytes=0;}
  auto value=QuerySession::restore_generation_with_local_sink(CompiledProgram::standalone(test.plan),root,recovery,path,options(),std::make_unique<std::istringstream>(profile.data));
  check(value->recovery_status().reader_bytes==profile.bytes[1] && value->recovery_status().reader_records==2 && value->local_sink_state().verified_sequence==1,"sink-aware decoder/source prefix differs");
  if(!pending)check(value->deliver_local_epoch().kind==LocalDeliveryKind::published,"sink-aware stream output disappeared");
  value->start();if(pending){check(value->begin_next(),"sink-aware cached stream row lost");finish(*value);static_cast<void>(value->deliver_local_epoch());}
  check(!value->begin_next() && value->progress().sequence==2 && value->local_sink_receipt().sequence()==2 && output(value->read_local_epoch(2))==typed::Output{{SetOperation::insert,Row{std::int64_t{1},std::int64_t{2},std::int64_t{3}}}},"sink-aware stream resume lost/duplicated source or output");
  std::cout<<"sink-aware stream "<<profile.name<<" indexed="<<indexed<<" pending="<<pending<<" source/header/EOF passed\n";
}
void window_case(bool indexed,WindowFifoPolicy fifo,unsigned steps) {
  Directory dir;const auto root=dir.file("window.root"),path=dir.file("output.sink");const auto plan=window::plan(indexed);auto source=QuerySession::create_windowed(plan,window::config(fifo));source->start();source->enable_generation(root,generation_test::options());source->create_local_sink(path,options());
  for(std::uint64_t i=1;i<=3;++i){typed::enqueue(*source,io::WindowCommand{i,io::WindowInsert{i,TableId{0},Row{std::int64_t{1}},i},{}});check(source->begin_next(),"sink-aware window input absent");finish(*source);static_cast<void>(source->deliver_local_epoch());}
  typed::enqueue(*source,io::WindowCommand{4,io::AdvanceWatermark{30},{}});if(steps==0)check(source->begin_next(),"sink-aware pending watermark absent");
  for(unsigned i=0;i<steps;++i){check(source->begin_next(),"sink-aware window step absent");finish(*source);}source.reset();
  auto value=QuerySession::restore_generation_with_local_sink(CompiledProgram::standalone(plan),root,generation_test::recovery_options(),path,options());
  check(value->local_sink_state().verified_sequence==1,"window metadata manufactured a physical sink epoch");if(steps==3)static_cast<void>(value->deliver_local_epoch());value->start();
  for(unsigned i=steps;i<3;++i){check(value->begin_next(),"sink-aware resumed watermark absent");finish(*value);static_cast<void>(value->deliver_local_epoch());}
  check(value->status().committed_sequence==2 && value->progress().sequence==4 && value->local_sink_receipt().sequence()==2 && output(value->read_local_epoch(2))==typed::Output{{SetOperation::erase,Row{std::int64_t{1}}}},"sink-aware partial window state/output differs");
  std::cout<<"sink-aware window indexed="<<indexed<<" fifo="<<static_cast<unsigned>(fifo)<<" steps="<<steps<<" metadata/physical recovery passed\n";
}
void checksum(std::string& frame) {
  const auto body=sha256_fixed(std::string_view(frame).substr(sk::frame_header_size));std::copy(body.begin(),body.end(),frame.begin()+20);
  const auto head=sha256_fixed(std::string_view(frame).substr(0,sk::frame_prefix_size));std::copy(head.begin(),head.end(),frame.begin()+static_cast<std::ptrdiff_t>(sk::frame_prefix_size));
}
template<class F> void rejects_unchanged(Saved& saved,F&& run) {
  const auto sink=contents(saved.source.path),wal=contents(saved.log);const auto before=descriptors();bool rejected=false;
  try{auto value=run();}catch(const std::exception&){rejected=true;}
  check(rejected && contents(saved.source.path)==sink && contents(saved.log)==wal && descriptors()==before,"sink-aware rejection mutated files, leaked ownership or exposed native output");
}
void hostile_and_limits() {
  Saved saved;const auto wal=contents(saved.log);const auto frames=session_journal_test::frames(saved.sink);const auto log_frames=session_journal_test::frames(wal);
  auto recovery=generation_test::recovery_options();
  recovery.replay.outputs_after_physical_sequence=0;rejects_unchanged(saved,[&]{return saved.restore(recovery);});recovery=generation_test::recovery_options();
  auto changed=std::string(frames[2]);changed.back()^=1;checksum(changed);std::string wrong(frames[0]);wrong.append(frames[1]);wrong+=changed;wrong.append(frames[3].substr(0,85));
  generation_test::put(saved.source.path,wrong);rejects_unchanged(saved,[&]{return saved.restore();});
  saved.prefix(3,true);std::string shorter;for(std::size_t i=0;i<5;++i)shorter.append(log_frames[i]);generation_test::put(saved.log,shorter);
  rejects_unchanged(saved,[&]{return saved.restore();});generation_test::put(saved.log,wal);
  saved.prefix(2,true);auto corrupt=wal;corrupt.back()^=1;generation_test::put(saved.log,corrupt);rejects_unchanged(saved,[&]{return saved.restore();});generation_test::put(saved.log,wal);
  auto delivery=options();delivery.sink_id[0]='0';rejects_unchanged(saved,[&]{return saved.restore(recovery,delivery);});delivery=options();delivery.repair_torn_tail=false;rejects_unchanged(saved,[&]{return saved.restore(recovery,delivery);});
  delivery=options();delivery.delivery_work=2;rejects_unchanged(saved,[&]{return saved.restore(recovery,delivery);});
  saved.prefix(1);recovery.replay.output_rows=3;rejects_unchanged(saved,[&]{return saved.restore(recovery);});
  recovery=generation_test::recovery_options();recovery.replay.source_work=0;rejects_unchanged(saved,[&]{return saved.restore(recovery);});
  recovery=generation_test::recovery_options();recovery.replay.memory_limit_bytes=1;rejects_unchanged(saved,[&]{return saved.restore(recovery);});
  recovery=generation_test::recovery_options();saved.prefix(2,true);auto value=saved.restore(recovery);check(!value->local_sink_state().persisted.torn_tail && value->local_sink_state().verified_sequence==2 && value->local_sink_state().delivery_work==3,"valid prefix verification/repair lost cumulative work");
  check(value->deliver_local_epoch().sequence==3 && contents(saved.source.path)==saved.sink,"sink-aware repaired tail changed next epoch");
  std::cout<<"sink-aware canonical mismatch/ahead WAL/corruption/frontier/schema/caps reject unchanged; verified torn prefix repaired only after validation passed\n";
}
void source_failure_before_repair() {
  Directory dir;const auto test=typed::fixture(false,1);const auto root=dir.file("source.root"),path=dir.file("output.sink");const Catalog catalog{5,{{"e",{{"x",ScalarType::int64},{"y",ScalarType::int64}}}}};const auto profile=session_journal_stream_test::cases(catalog)[2];
  SessionOptions config;config.input=profile.options;auto source=QuerySession::create(test.plan,std::make_unique<std::istringstream>(profile.data),config);source->start();source->enable_generation(root,generation_test::options());source->create_local_sink(path,options());
  for(unsigned i=0;i<2;++i){check(source->begin_next(),"sink-aware source fixture absent");finish(*source);static_cast<void>(source->deliver_local_epoch());}source.reset();
  const auto sink=contents(path);const auto frames=session_journal_test::frames(sink);generation_test::put(path,sink+std::string(frames[2].substr(0,85)));const auto torn=contents(path);
  const auto log=generation_test::path(root,1,".wal"),wal=contents(log);const auto log_frames=session_journal_test::frames(wal);generation_test::put(log,wal+std::string(log_frames[1].substr(0,85)));const auto torn_wal=contents(log);
  auto recovery=generation_test::recovery_options();recovery.replay.seek_source_from_origin=true;const auto before=descriptors();bool rejected=false;
  try{auto value=QuerySession::restore_generation_with_local_sink(CompiledProgram::standalone(test.plan),root,recovery,path,options(),std::make_unique<std::istringstream>(""));}catch(const SessionJournalFailure& e){rejected=e.fault()==SessionJournalFault::continuation;}
  check(rejected && contents(path)==torn && contents(log)==torn_wal && descriptors()==before,"source validation failure repaired sink or journal before acceptance");
  auto value=QuerySession::restore_generation_with_local_sink(CompiledProgram::standalone(test.plan),root,recovery,path,options(),std::make_unique<std::istringstream>(profile.data));
  check(contents(path)==sink && contents(log)==wal && value->local_sink_receipt().sequence()==2,"fully validated source recovery did not repair both tails");
  std::cout<<"sink-aware source seek failure preserves both torn files; complete retry repairs both passed\n";
}
}
int main(){try{
  const Catalog catalog{5,{{"e",{{"x",ScalarType::int64},{"y",ScalarType::int64}}}}};
  for(const bool indexed:{false,true}){for(unsigned kind=0;kind<6;++kind)for(std::size_t accepted=0;accepted<=3;++accepted)typed_case(indexed,kind,accepted);
    for(const auto& profile:session_journal_stream_test::cases(catalog))for(const bool pending:{false,true})stream_case(indexed,profile,pending);
    for(const auto fifo:{WindowFifoPolicy::global,WindowFifoPolicy::per_relation})for(unsigned steps=0;steps<4;++steps)window_case(indexed,fifo,steps);
  }rotation();hostile_and_limits();source_failure_before_repair();
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
