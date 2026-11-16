#include "local_sink_fixture.hpp"
#include "session_journal_stream_cases.hpp"
#include "crown/api/error.hpp"
#include <algorithm>
using namespace crown;
using namespace crown::runtime;
using namespace crown::local_sink_test;
static_assert(!std::is_trivially_copyable_v<sk::Receipt>);
namespace {
void typed_case(bool indexed,unsigned kind,bool crash_before_delivery) {
  Fixture f(indexed,kind);Database database;database.tables.resize(f.query.test.plan.source_catalog().tables.size());
  const auto compiler=CompiledProgram::standalone(f.query.test.plan);const auto mode=kind==2?DeltaMode::maintenance:DeltaMode::delta;
  for(std::size_t i=0;i<4;++i) {
    const auto before=typed::oracle(f.query.test,database);apply(database,f.query.test.updates[i]);const auto after=typed::oracle(f.query.test,database);
    f.commit(i);check(f.query.session->begin_next_result()==SessionBegin::would_block,"local sink did not hold producer backpressure");
    bool transfer=false;try{static_cast<void>(f.query.session->next_output());}catch(const Error&){transfer=true;}check(transfer,"ordinary transfer bypassed local delivery");
    if(crash_before_delivery) {
      f.query.session.reset();f.query.session=QuerySession::restore_generation(compiler,f.query.name,generation_test::recovery_options());f.query.session->open_local_sink(f.path,options());
      for(std::uint64_t sequence=1;sequence<=i;++sequence)check(f.query.session->deliver_local_epoch().kind==LocalDeliveryKind::duplicate,"replay did not deduplicate a durable prior epoch");
    }
    const auto delivered=f.query.session->deliver_local_epoch();check(delivered.kind==LocalDeliveryKind::published && delivered.sequence==i+1 && delivered.generation==1,"local epoch did not durably publish");
    const auto persisted=f.query.session->read_local_epoch(i+1);check(output(persisted)==(mode==DeltaMode::delta?typed::difference(before,after):typed::Output{}),"persisted output differs from independent definition");
    check(f.query.session->local_sink_receipt().sequence()==i+1 && typed::rows(*f.query.session)==after,"delivery changed native state or receipt frontier");
    f.query.session->start();
  }
  f.query.session->rotate_generation();const auto state=f.query.session->local_sink_state();f.query.session.reset();
  auto result=QuerySession::restore_generation(compiler,f.query.name,generation_test::recovery_options());result->open_local_sink(f.path,options());
  check(result->local_sink_state().persisted.header==state.persisted.header && result->local_sink_receipt().sequence()==4,"sink reopen across generation rotation lost original identity/baseline");
  auto epoch=result->read_local_epoch(4);result->drop();check(!epoch.rows.empty() || kind==2 || kind==3 || kind==5 || kind==4,"persisted epoch lifetime invalid");
  std::cout<<"local sink typed indexed="<<indexed<<" query="<<kind<<" restart="<<crash_before_delivery<<" state/durable output/backpressure/dedup/rotation passed\n";
}
void canonical_and_schema(const char* golden) {
  auto account=resource::MemoryAccount::create(32*1024*1024);Directory dir;const auto path=dir.file("native.sink");const std::array<ScalarType,5> schema{ScalarType::int64,ScalarType::string,ScalarType::boolean,ScalarType::date,ScalarType::decimal};
  generation_test::Fixture native;const auto journal=native.session->checkpoint_image().manifest.runtime_manifest.binding;
  sk::Header header{generation_test::options().journal.query_id,options().sink_id,journal,7,10,schema.size(),sk::schema_sha256(account,schema)};
  const std::array<Row,2> values{Row{std::int64_t{-7},std::string("a\0b",3),true,Date::parse("2024-02-29"),Decimal::parse("-12.5")},Row{std::int64_t{3},std::string("\xe4\xb8\xad"),false,Date::parse("0001-01-01"),Decimal::parse("0")}};
  std::array<sk::RowView,2> rows{{{SetOperation::insert,storage::TupleValuesView::borrow(values[0])},{SetOperation::erase,storage::TupleValuesView::borrow(values[1])}}};
  sk::Epoch retained;
  {auto file=sk::File::create(account,path,header,schema);check(file.append(7,11,rows),"first canonical epoch missing");const auto full=contents(path);const auto frames=session_journal_test::frames(full);
    const auto text=contents(golden);std::string expected;int high=-1;for(const char c:text){if(c=='\n' || c=='\r' || c==' ' || c=='\t')continue;const int digit=c>='0' && c<='9'?c-'0':c>='a' && c<='f'?c-'a'+10:-1;check(digit>=0,"invalid independent epoch hex");if(high<0)high=digit;else{expected.push_back(static_cast<char>(16*high+digit));high=-1;}}
    check(high<0 && expected.size()==265 && sha256(expected)=="6c89a8446a9accaa0530cd9967b49676d1aa744b341dcd24becdfcdf5352b235" && frames[1]==expected,"independent canonical output epoch differs");
    std::reverse(rows.begin(),rows.end());check(!file.append(7,11,rows) && contents(path)==full,"canonical retry depends on order");retained=file.read_epoch(11);
    auto changed=rows;changed[0].operation=SetOperation::insert;bool mismatch=false;try{static_cast<void>(file.append(7,11,changed));}catch(const recovery::ImageFailure&){mismatch=true;}check(mismatch && contents(path)==full,"different retry epoch replaced durable data");
    const std::array<sk::RowView,2> duplicate{rows[0],rows[0]};bool repeated=false;try{static_cast<void>(file.append(7,12,duplicate));}catch(const recovery::ImageFailure&){repeated=true;}check(repeated && contents(path)==full,"duplicate same-sign tuple accepted");
    check(file.append(8,12,{}) && file.receipt().sequence()==12,"empty epoch did not advance durable coverage");}
  check(retained.rows.size()==2 && output(retained)==typed::Output{{SetOperation::insert,values[0]},{SetOperation::erase,values[1]}},"native exact scalar/epoch lifetime differs");
  {auto file=sk::File::open(account,path,header,schema);check(file.read_epoch(12).rows.empty() && file.receipt().generation()==8,"durable empty epoch/reopen identity differs");}
  std::cout<<"local sink canonical typed scalars/empty epochs/whole-byte retry/duplicate rejection/lifetime passed\n";
}
void reject_incomplete_replay() {
  Fixture f;f.commit(0);static_cast<void>(f.query.session->deliver_local_epoch());f.commit(1);const auto compiler=CompiledProgram::standalone(f.query.test.plan);f.query.session.reset();
  for(const bool frontier:{false,true}) {
    auto restore=generation_test::recovery_options();if(frontier)restore.replay.outputs_after_physical_sequence=1;
    auto value=QuerySession::restore_generation(compiler,f.query.name,restore);if(!frontier)static_cast<void>(value->next_recovered_output());bool rejected=false;
    try{value->open_local_sink(f.path,options());}catch(const Error&){rejected=true;}check(rejected,"partial/frontier-suppressed replay fabricated durable delivery coverage");
  }
  std::cout<<"local sink partial-transfer and caller-frontier replay coverage rejected\n";
}
std::string third_record(const session_journal_stream_test::Case& profile,const Catalog& catalog) {
  switch(profile.options.format) {
    case io::InputFormat::jsonl:return io::write_input_json(io::InputEvent{{3,TableId{0},SetOperation::insert,Row{std::int64_t{3},std::int64_t{4}}},io::SourcePosition{"jsonl-source",30}},catalog)+"\n";
    case io::InputFormat::binary:return io::write_input_binary(io::InputEvent{{3,TableId{0},SetOperation::insert,Row{std::int64_t{3},std::int64_t{4}}},io::SourcePosition{"binary-source",50}},catalog);
    case io::InputFormat::csv:return "4;3\n";
    case io::InputFormat::legacy_signed:return "+,3,4\n";
    case io::InputFormat::legacy_relations:return "+,E,3,4\n";
    case io::InputFormat::legacy_insert_only:return "3,4\n";
    case io::InputFormat::legacy_flags:return "1,3,4\n";
    case io::InputFormat::legacy_timestamp_flags:return "30,1,3,4\n";
  }
  throw std::runtime_error("unknown local sink stream profile");
}
void stream_case(bool indexed,const session_journal_stream_test::Case& profile,bool pending) {
  Directory dir;const auto test=typed::fixture(indexed,1);const auto root=dir.file("stream.root"),path=dir.file("output.sink");const Catalog catalog{5,{{"e",{{"x",ScalarType::int64},{"y",ScalarType::int64}}}}};
  const auto input=profile.data+third_record(profile,catalog);SessionOptions config;config.input=profile.options;config.input.limits.records=3;config.input.limits.total_bytes=input.size();
  auto source=QuerySession::create(test.plan,std::make_unique<std::istringstream>(input),config);source->start();source->enable_generation(root,generation_test::options());source->create_local_sink(path,options());
  check(source->begin_next(),"sink first stream row missing");finish(*source);static_cast<void>(source->deliver_local_epoch());check(source->begin_next(),"sink second stream row missing");if(!pending)finish(*source);source.reset();
  auto restore=generation_test::recovery_options();restore.replay.seek_source_from_origin=true;auto value=QuerySession::restore_generation(CompiledProgram::standalone(test.plan),root,restore,std::make_unique<std::istringstream>(input));
  value->open_local_sink(path,options());check(value->deliver_local_epoch().kind==LocalDeliveryKind::duplicate,"stream replay repeated initial durable empty epoch");if(!pending)check(value->deliver_local_epoch().kind==LocalDeliveryKind::published,"stream replay lost committed undelivered output");
  value->start();if(pending){check(value->begin_next(),"sink retained stream row missing");finish(*value);static_cast<void>(value->deliver_local_epoch());}
  check(value->begin_next(),"sink unread third stream row missing");finish(*value);static_cast<void>(value->deliver_local_epoch());
  check(!value->begin_next() && value->progress().sequence==3 && value->local_sink_receipt().sequence()==3 && output(value->read_local_epoch(2))==typed::Output{{SetOperation::insert,Row{std::int64_t{1},std::int64_t{2},std::int64_t{3}}}} &&
      output(value->read_local_epoch(3))==typed::Output{{SetOperation::insert,Row{std::int64_t{2},std::int64_t{3},std::int64_t{4}}}},"durable stream decoder/source/output continuation differs");
  std::cout<<"local sink stream "<<profile.name<<" indexed="<<indexed<<" pending="<<pending<<" durable replay/source/next input passed\n";
}
void window_case(bool indexed,WindowFifoPolicy fifo,unsigned steps) {
  Directory dir;const auto root=dir.file("window.root"),path=dir.file("output.sink");const auto plan=window::plan(indexed);auto source=QuerySession::create_windowed(plan,window::config(fifo));source->start();source->enable_generation(root,generation_test::options());source->create_local_sink(path,options());
  for(std::uint64_t label=1;label<=3;++label){typed::enqueue(*source,io::WindowCommand{label,io::WindowInsert{label,TableId{0},Row{std::int64_t{1}},label},{}});check(source->begin_next(),"sink window insert missing");finish(*source);static_cast<void>(source->deliver_local_epoch());}
  typed::enqueue(*source,io::WindowCommand{4,io::AdvanceWatermark{30},{}});if(steps==0)check(source->begin_next(),"sink pending watermark missing");
  for(unsigned i=0;i<steps;++i){check(source->begin_next(),"sink window substep missing");finish(*source);}source.reset();
  auto value=QuerySession::restore_generation(CompiledProgram::standalone(plan),root,generation_test::recovery_options());value->open_local_sink(path,options());check(value->deliver_local_epoch().kind==LocalDeliveryKind::duplicate,"window replay repeated persisted insertion");
  if(steps==3)static_cast<void>(value->deliver_local_epoch());
  value->start();
  for(unsigned i=steps;i<3;++i){check(value->begin_next(),"sink resumed window substep missing");finish(*value);static_cast<void>(value->deliver_local_epoch());}
  check(value->progress().sequence==4 && value->status().committed_sequence==2 && value->local_sink_state().persisted.epochs==2 &&
      output(value->read_local_epoch(2))==typed::Output{{SetOperation::erase,Row{std::int64_t{1}}}},"window metadata created output epochs or lost final deletion");
  value->rotate_generation();typed::enqueue(*value,io::WindowCommand{5,io::WindowInsert{5,TableId{0},Row{std::int64_t{9}},31},{}});check(value->begin_next(),"post-rotation window update missing");finish(*value);static_cast<void>(value->deliver_local_epoch());
  check(value->read_local_epoch(3).generation==2 && value->local_sink_receipt().sequence()==3,"sink window generation identity changed");
  std::cout<<"local sink window indexed="<<indexed<<" fifo="<<static_cast<unsigned>(fifo)<<" steps="<<steps<<" partial metadata/physical delivery passed\n";
}
void cancellation_and_queue() {
  for(unsigned phase=0;phase<3;++phase) {
    Fixture f;f.commit(0);static_cast<void>(f.query.session->deliver_local_epoch());typed::enqueue(*f.query.session,io::InputEvent{f.query.test.updates[1],io::SourcePosition{"feed",20}});check(f.query.session->begin_next(),"cancelled sink input missing");
    if(phase){finish(*f.query.session);if(phase==2)static_cast<void>(f.query.session->deliver_local_epoch());}
    f.query.session->pause();f.query.session->stop();f.query.session->drop();f.query.session.reset();
    auto value=QuerySession::restore_generation(CompiledProgram::standalone(f.query.test.plan),f.query.name,generation_test::recovery_options());value->open_local_sink(f.path,options());const auto committed=value->status().committed_sequence;
    for(std::uint64_t i=1;i<=committed;++i)static_cast<void>(value->deliver_local_epoch());
    value->start();
    if(phase==0){check(value->begin_next(),"cancelled uncommitted input was lost");finish(*value);static_cast<void>(value->deliver_local_epoch());}
    check(value->local_sink_receipt().sequence()==2 && output(value->read_local_epoch(2)).size()==1,"cancel/stop/drop lost or duplicated an epoch");
  }
  Directory dir;const auto test=typed::fixture(false,1);io::QueueLimits queue;queue.batches=1;queue.events=1;queue.bytes=4096;
  auto value=QuerySession::create_typed(test.plan,queue);value->start();value->enable_generation(dir.file("bounded.root"),generation_test::options());value->create_local_sink(dir.file("bounded.sink"),options());
  typed::enqueue(*value,io::InputEvent{test.updates[0],io::SourcePosition{"feed",10}});check(value->begin_next(),"bounded sink first event missing");finish(*value);
  io::TransportBatch second({io::InputEvent{test.updates[1],io::SourcePosition{"feed",20}}}),third({io::InputEvent{test.updates[2],io::SourcePosition{"feed",30}}});
  check(value->enqueue(second)==io::Admission::accepted && value->enqueue(third)==io::Admission::full && !third.empty(),"slow sink queue exceeded cap or consumed rejected caller input");
  for(unsigned i=0;i<10;++i)check(value->begin_next_result()==SessionBegin::would_block && value->progress().sequence==1 && value->status().queue->events==1,"slow sink advanced input while delivery blocked");
  check(value->local_sink_state().blocked_inputs==10 && value->status().queue->accounted_bytes<=queue.bytes,"backpressure counters or bytes differ");
  static_cast<void>(value->deliver_local_epoch());check(value->begin_next(),"slow sink did not resume after durable acceptance");finish(*value);static_cast<void>(value->deliver_local_epoch());check(value->enqueue(third)==io::Admission::accepted && third.empty(),"slow sink retry lost caller ownership");
  check(value->begin_next(),"slow sink third event missing");finish(*value);static_cast<void>(value->deliver_local_epoch());check(value->local_sink_receipt().sequence()==3,"slow sink retry lost output frontier");
  std::cout<<"local sink cancellation/stop/drop and bounded slow-producer queue/backpressure passed\n";
}
void delivery_budget_and_private_barrier() {
  for(const bool under:{false,true}) {
    generation_test::Fixture f;const auto path=f.directory.file("budget.sink");auto limits=options();limits.delivery_work=under?2:3;f.session->create_local_sink(path,limits);limits.delivery_work=UINT64_MAX;
    typed::enqueue(*f.session,io::InputEvent{f.test.updates[0],io::SourcePosition{"feed",10}});check(f.session->begin_next(),"budget first input missing");const auto initial=contents(path);bool private_rejected=false;
    try{static_cast<void>(f.session->deliver_local_epoch());}catch(const Error&){private_rejected=true;}check(private_rejected && contents(path)==initial,"private fan-out exposed sink output");finish(*f.session);static_cast<void>(f.session->deliver_local_epoch());
    typed::enqueue(*f.session,io::InputEvent{f.test.updates[1],io::SourcePosition{"feed",20}});check(f.session->begin_next(),"budget second input missing");finish(*f.session);const auto before=contents(path);bool capped=false;
    try{static_cast<void>(f.session->deliver_local_epoch());}catch(const recovery::ImageFailure& e){capped=e.fault()==recovery::ImageFault::work;}
    check(capped==under,"copied cumulative delivery-work cap differed");
    if(under){check(contents(path)==before && f.session->status().output_remaining==1 && f.session->local_sink_state().verified_sequence==1,"delivery limit lost output or published bytes");limits.delivery_work=4;f.session->open_local_sink(path,limits);static_cast<void>(f.session->deliver_local_epoch());check(f.session->local_sink_state().delivery_work==4,"reopen reset consumed delivery work");}
    check(f.session->local_sink_receipt().sequence()==2,"finite delivery budget lost epoch coverage");
  }
  std::cout<<"local sink private fan-out barrier and copied exact/under cumulative delivery work passed\n";
}
void checksum(std::string& frame) {
  const auto body=sha256_fixed(std::string_view(frame).substr(sk::frame_header_size));std::copy(body.begin(),body.end(),frame.begin()+20);
  const auto prefix=sha256_fixed(std::string_view(frame).substr(0,sk::frame_prefix_size));std::copy(prefix.begin(),prefix.end(),frame.begin()+static_cast<std::ptrdiff_t>(sk::frame_prefix_size));
}
void hostile_and_caps() {
  Directory dir;const auto path=dir.file("corpus.sink");auto account=resource::MemoryAccount::create(32*1024*1024);generation_test::Fixture native;
  const std::array<ScalarType,1> schema{ScalarType::int64};sk::Header header{generation_test::options().journal.query_id,options().sink_id,native.session->checkpoint_image().manifest.runtime_manifest.binding,1,0,1,sk::schema_sha256(account,schema)};
  const Row row{std::int64_t{7}};const std::array<sk::RowView,1> rows{{{SetOperation::insert,storage::TupleValuesView::borrow(row)}}};std::uint64_t used=0;
  {auto file=sk::File::create(account,path,header,schema);check(file.append(1,1,rows) && file.append(1,2,{}),"sink corpus creation failed");used=file.state().work;}
  const auto full=contents(path);const auto frames=session_journal_test::frames(full);const auto first=frames[0].size(),second=first+frames[1].size();
  for(std::size_t cut=first;cut<=full.size();++cut) {
    generation_test::put(path,std::string_view(full).substr(0,cut));auto file=sk::File::open(account,path,header,schema);const auto expected=cut==full.size()?2U:cut>=second?1U:0U;
    check(file.state().sequence==expected,"torn sink exposed partial epoch");if(file.state().torn_tail)file.repair_tail();if(expected<1)static_cast<void>(file.append(1,1,rows));if(expected<2)static_cast<void>(file.append(1,2,{}));check(contents(path)==full,"sink tail repair/retry changed canonical prefix");
  }
  const auto reject=[&](std::string_view bytes){generation_test::put(path,bytes);bool bad=false;try{auto file=sk::File::open(account,path,header,schema);}catch(const sk::Failure&){bad=true;}catch(const recovery::ImageFailure&){bad=true;}check(bad && contents(path)==bytes,"corrupt sink was accepted or mutated");};
  for(std::size_t cut=0;cut<first;++cut)reject(std::string_view(full).substr(0,cut));
  for(std::size_t i=0;i<full.size();++i){auto changed=full;changed[i]^=1;reject(changed);}
  for(std::size_t cut=sk::frame_prefix_size+1;cut<sk::frame_header_size;++cut) {
    std::string tail(frames[1].substr(0,cut));tail.back()=tail.back()=='0'?'1':'0';std::string changed(frames[0]);changed+=tail;reject(changed);
  }
  for(const std::size_t field:{std::size_t{sk::frame_header_size+1},std::size_t{sk::frame_header_size+17},std::size_t{sk::frame_header_size+33},std::size_t{sk::frame_header_size+34},std::size_t{sk::frame_header_size+42}}) {
    std::string changed(frames[1]);changed[field]^=7;checksum(changed);std::string file(frames[0]);file+=changed;reject(file);
  }
  {auto changed=std::string(frames[0]);changed[sk::frame_header_size+9]='f';checksum(changed);changed.append(frames[1]);reject(changed);}
  for(const bool one_under:{false,true}) {
    const auto name=dir.file(one_under?"work-under.sink":"work-exact.sink");auto limits=sk::Limits{};limits.work=used-(one_under?1U:0U);auto file=sk::File::create(account,name,header,schema,limits);static_cast<void>(file.append(1,1,rows));bool capped=false;
    try{static_cast<void>(file.append(1,2,{}));}catch(const recovery::ImageFailure& e){capped=e.fault()==recovery::ImageFault::work;}
    check(capped==one_under && file.state().sequence==(one_under?1U:2U),"sink cumulative exact/under work cap differs");
  }
  for(const bool one_under:{false,true}) {
    const auto name=dir.file(one_under?"bytes-under.sink":"bytes-exact.sink");auto limits=sk::Limits{};limits.bytes=full.size()-(one_under?1U:0U);auto file=sk::File::create(account,name,header,schema,limits);static_cast<void>(file.append(1,1,rows));bool capped=false;
    try{static_cast<void>(file.append(1,2,{}));}catch(const recovery::ImageFailure& e){capped=e.fault()==recovery::ImageFault::limit;}
    check(capped==one_under && file.state().sequence==(one_under?1U:2U),"sink cumulative exact/under byte cap differs");
  }
  {const auto name=dir.file("header-under.sink");auto limits=sk::Limits{};limits.bytes=first-1;bool capped=false;try{auto file=sk::File::create(account,name,header,schema,limits);}catch(const recovery::ImageFailure& e){capped=e.fault()==recovery::ImageFault::limit;}check(capped && !std::filesystem::exists(name),"sink published header above file cap");}
  {generation_test::put(path,full);auto file=sk::File::open(account,path,header,schema);auto receipt=file.receipt();auto report=receipt.header();++report.base_sequence;check(receipt.header().base_sequence==0,"receipt report aliased durable authority");bool busy=false;
    try{auto other=sk::File::open(account,path,header,schema);}catch(const sk::Failure& e){busy=e.fault()==sk::Fault::busy;}check(busy,"sink allowed concurrent writer");}
  {const auto victim=dir.file("victim");generation_test::put(victim,"keep sink target");const auto link=dir.file("symlink.sink");check(::symlink(victim.c_str(),link.c_str())==0,"sink symlink fixture failed");bool rejected=false;try{auto file=sk::File::open(account,link,header,schema);}catch(const sk::Failure&){rejected=true;}check(rejected && contents(victim)=="keep sink target","sink followed symlink");}
  std::cout<<"local sink epoch cuts="<<full.size()-first+1<<" header cuts="<<first<<" byte flips="<<full.size()<<" semantic corruption/repair/cumulative caps/ownership passed\n";
}
}
int main(int argc,char** argv){try{check(argc==2,"expected independent epoch golden");for(const bool indexed:{false,true}){for(unsigned kind=0;kind<6;++kind)for(const bool restart:{false,true})typed_case(indexed,kind,restart);
  const Catalog catalog{5,{{"e",{{"x",ScalarType::int64},{"y",ScalarType::int64}}}}};for(const auto& profile:session_journal_stream_test::cases(catalog))for(const bool pending:{false,true})stream_case(indexed,profile,pending);
  for(const auto fifo:{WindowFifoPolicy::global,WindowFifoPolicy::per_relation})for(unsigned step=0;step<4;++step)window_case(indexed,fifo,step);
}canonical_and_schema(argv[1]);reject_incomplete_replay();cancellation_and_queue();delivery_budget_and_private_barrier();hostile_and_caps();}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
