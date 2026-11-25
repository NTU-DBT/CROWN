#include "crown/recovery/session_image.hpp"
#include "crown/ir/digest.hpp"
#include "session_checkpoint_test_fixture.hpp"
#include "window_checkpoint_test_fixture.hpp"
#include <fstream>

using namespace crown;
using namespace crown::runtime;
namespace typed=crown::session_checkpoint_test;
namespace window=crown::window_checkpoint_test;
using typed::check;
namespace {
std::string_view bytes(const recovery::SessionImage& value){return {value.bytes.data(),value.bytes.size()};}
void typed_case(bool indexed,unsigned kind,SessionState control) {
  const auto test=typed::fixture(indexed,kind);const auto compiler=CompiledProgram::standalone(test.plan);
  SessionOptions options;options.delta.mode=kind==2?DeltaMode::maintenance:DeltaMode::delta;options.snapshot.rows=31;
  auto source=QuerySession::create_typed(test.plan,{},options);const auto original=source.get_deleter().account();
  workload::Options configured;configured.mode=workload::Mode::counters;configured.period=2;source->configure_workload_statistics(configured);
  Database database;database.tables.resize(test.plan.source_catalog().tables.size());
  if(control!=SessionState::created) {
    source->start();typed::step(*source,test,database,test.updates[0],options.delta.mode);typed::step(*source,test,database,test.updates[1],options.delta.mode);
    if(control==SessionState::paused){source->pause();}
    if(control==SessionState::stopped){source->stop();}
  }
  const auto expected=typed::rows(*source);const auto accepted=source->progress();const auto before=original.statistics();
  std::optional<recovery::SessionImage> image;std::size_t captures=0,restores=0;
  {s04_alloc::Scope count;image=source->checkpoint_image();captures=s04_alloc::calls;}
  check(captures==original.statistics().successful_allocations-before.successful_allocations,"binary capture escaped original account");
  {s04_alloc::Scope deny(0);const auto info=recovery::inspect_session_image(bytes(*image));
    check(info.manifest.committed_sequence==source->status().committed_sequence && info.manifest.accepted_sequence==accepted.sequence && s04_alloc::calls==0,
        "session inspection allocated or lost manifest progress");}
  std::optional<QuerySession::Owner> target;
  {s04_alloc::Scope count;target=QuerySession::restore_image(compiler,bytes(*image));restores=s04_alloc::calls;}
  auto& result=**target;typed::grant(result,indexed);const auto account=target->get_deleter().account();const auto peak=account.statistics().peak_requested_bytes;
  check(restores==account.statistics().successful_allocations,"binary restore escaped one receiving account");
  check(result.status().state==control && result.progress()==accepted && typed::rows(result)==expected &&
      result.workload_statistics_options()==configured && result.run_context()->snapshot.rows==31,"binary session lost state/policy/results");
  const auto resident=original.statistics().current;
  for(unsigned i=0;i<5;++i){auto repeated=source->checkpoint_image();check(repeated.bytes==image->bytes,"binary image is not deterministic");}
  check(original.statistics().current==resident,"repeated binary capture grew storage");
  if(kind==1 && control==SessionState::running) {
    for(std::size_t point=0;point<captures;++point) {
      bool failed=false;{s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{auto value=source->checkpoint_image();}catch(const std::bad_alloc&){failed=true;}}
      check(failed && original.statistics().current==resident && source->progress()==accepted && typed::rows(*source)==expected,"binary capture OOM changed state/leaked");
    }
    for(std::size_t point=0;point<restores;++point) {
      bool failed=false;{s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{auto value=QuerySession::restore_image(compiler,bytes(*image));}catch(const std::bad_alloc&){failed=true;}}
      check(failed && original.statistics().current==resident && typed::rows(*source)==expected,"binary restore OOM changed source");
    }
    SessionRestoreOptions exact;exact.memory_limit_bytes=peak;
    {auto value=QuerySession::restore_image(compiler,bytes(*image),exact);check(value.get_deleter().account().statistics().peak_requested_bytes==peak,"binary exact restore cap failed");}
    --*exact.memory_limit_bytes;bool failed=false;
    try{auto value=QuerySession::restore_image(compiler,bytes(*image),exact);}catch(const resource::MemoryFailure& error){failed=error.fault()==resource::MemoryFault::limit;}
    check(failed,"binary one-under restore cap accepted");
  }
  if(control!=SessionState::stopped) {
    source->start();result.start();auto other=database;
    for(std::size_t i=control==SessionState::created?std::size_t{0}:std::size_t{2};i<test.updates.size();++i)
      check(typed::step(*source,test,database,test.updates[i],options.delta.mode)==typed::step(result,test,other,test.updates[i],options.delta.mode),"binary next update deltas differ");
    source->finish_input();result.finish_input();check(!source->begin_next() && !result.begin_next(),"binary queue EOF differs");
  }
  std::cout<<"binary typed indexed="<<indexed<<" query="<<kind<<" control="<<static_cast<unsigned>(control)<<" capture/restore="<<captures<<'/'<<restores<<" passed\n";
}
void stream_case(bool indexed,io::InputFormat format) {
  const auto test=typed::fixture(indexed,0);const auto compiler=CompiledProgram::standalone(test.plan);SessionOptions options;options.input.format=format;
  options.input.limits.records=2;std::string first,tail;
  if(format==io::InputFormat::jsonl || format==io::InputFormat::binary) {
    const io::InputEvent a{test.updates[0],io::SourcePosition{"feed",10}},b{test.updates[1],io::SourcePosition{"feed",20}};
    if(format==io::InputFormat::jsonl){first=io::write_input_json(a,test.plan.source_catalog())+"\n";tail=io::write_input_json(b,test.plan.source_catalog())+"\n";}
    else {first=io::write_input_binary(a,test.plan.source_catalog());tail=io::write_input_binary(b,test.plan.source_catalog());}
  }else {
    options.input.source="stream";if(format!=io::InputFormat::legacy_relations)options.input.table=TableId{0};
    if(format==io::InputFormat::csv){first="x\n1\n";tail="2\n";options.input.byte_offset=123;}
    if(format==io::InputFormat::legacy_signed){first="+,1\n";tail="+,2\n";}
    if(format==io::InputFormat::legacy_relations){options.input.relation_tokens.emplace("R",TableId{0});first="+,R,1\n";tail="+,R,2\n";}
    if(format==io::InputFormat::legacy_insert_only){first="1\n";tail="2\n";}
    if(format==io::InputFormat::legacy_flags){first="1,1\n";tail="1,2\n";}
    if(format==io::InputFormat::legacy_timestamp_flags){first="10,1,1\n";tail="20,1,2\n";}
  }
  options.input.limits.total_bytes=first.size()+tail.size();auto source=QuerySession::create(test.plan,std::make_unique<std::istringstream>(first+tail),options);
  source->start();check(source->begin_next(),"binary stream fixture missing");typed::finish(*source);source->pause();auto image=source->checkpoint_image();
  auto target=QuerySession::restore_image(compiler,bytes(image),std::make_unique<std::istringstream>(tail));typed::grant(*target,indexed);
  check(target->status().state==SessionState::paused && target->progress()==source->progress() && typed::rows(*target)==typed::rows(*source),"binary stream paused state differs");
  source->start();target->start();check(source->begin_next() && target->begin_next(),"binary stream continuation missing");
  check(typed::finish(*source)==typed::finish(*target) && source->progress()==target->progress(),"binary stream next delta/position differs");
  check(!source->begin_next() && !target->begin_next(),"binary stream EOF differs");auto ended=target->checkpoint_image();
  auto eof=QuerySession::restore_image(compiler,bytes(ended),std::make_unique<std::istringstream>(first));check(!eof->begin_next(),"binary EOF read extra data");
  target->stop();auto stopped=target->checkpoint_image();auto terminal=QuerySession::restore_image(compiler,bytes(stopped));
  check(terminal->status().state==SessionState::stopped && typed::rows(*terminal)==typed::rows(*target),"binary stopped stream differs");
  std::cout<<"binary stream indexed="<<indexed<<" profile="<<static_cast<unsigned>(format)<<" paused/EOF/stopped passed\n";
}
void window_case(bool indexed,WindowFifoPolicy fifo,SessionState control) {
  const auto plan=window::plan(indexed);const auto compiler=CompiledProgram::standalone(plan);auto source=QuerySession::create_windowed(plan,window::config(fifo));
  if(control!=SessionState::created){window::seed(*source);}
  if(control==SessionState::paused){source->pause();}
  if(control==SessionState::stopped){source->stop();}
  auto image=source->checkpoint_image();auto target=QuerySession::restore_image(compiler,bytes(image));typed::grant(*target,indexed);
  check(target->status().state==control && target->window_state()==source->window_state() && target->progress()==source->progress() && typed::rows(*target)==typed::rows(*source),"binary window state differs");
  if(control!=SessionState::stopped) {
    source->start();target->start();if(control==SessionState::created){window::seed(*source);window::seed(*target);}
    check(window::command(*source,{6,io::AdvanceWatermark{20},{}})==window::command(*target,{6,io::AdvanceWatermark{20},{}}),"binary window expiration differs");
    check(window::command(*source,window::insertion(7,4,TableId{0},3,20))==window::command(*target,window::insertion(7,4,TableId{0},3,20)),"binary window next insertion differs");
    check(target->window_state()==source->window_state() && typed::rows(*target)==typed::rows(*source),"binary next window state differs");
  }
  std::cout<<"binary window indexed="<<indexed<<" fifo="<<static_cast<unsigned>(fifo)<<" control="<<static_cast<unsigned>(control)<<" passed\n";
}
void golden(const char* path) {
  const auto account=resource::MemoryAccount::create(16*1024*1024);SessionCheckpoint state;state.state=SessionState::stopped;
  state.input_kind=SessionInputKind::typed_physical;state.end_of_input=true;state.committed_sequence=99;
  // The independent fixture encodes an explicit 1,000,000-record input limit
  // (the earlier default); the current default is unbounded.
  io::InputOptions input;input.limits.records=1'000'000;
  state.input_options=io::AccountedInputOptions(account,input);state.queue_limits=io::QueueLimits{};
  io::InputProgress accepted{99,{{"alpha",0},{"z",UINT64_MAX}}};state.source=io::AccountedInputProgress(account,accepted);
  recovery::ImageManifest manifest;manifest.binding.physical_sha256.fill('a');manifest.binding.source_sha256.fill('b');manifest.binding.catalog_version=7;manifest.epoch=99;
  // Construct policy independently from the encoder, using the public defaults.
  manifest.binding.policy={1,1'000'000,UINT64_MAX,0,0,2,256,1,0,1,0,1,1'000'000,UINT64_MAX,1,1,0,0,1,1'000'000,1,1'000'000,1,1'000'000,65536,64*1024*1024};
  auto values=storage::AccountedRow::copy_of(account,Row{INT64_MIN,std::string("A\0\xff",3),true,Date::parse("1970-01-01"),Decimal::parse("-123.45")});
  const std::array<storage::RowView,2> rows{{values.view(),{}}};const std::array<recovery::ImageTableView,2> tables{{{rows},{{}}}};
  state.runtime_image=recovery::encode_image(account,manifest,tables);const auto image=recovery::encode_session_image(account,state);
  std::ifstream file(path);std::string expected;file>>expected;check(expected.size()==2*image.bytes.size(),"session golden size differs");
  const auto hex=[](char c){return c>='0' && c<='9'?static_cast<unsigned>(c-'0'):static_cast<unsigned>(c-'a'+10);};
  for(std::size_t i=0;i<image.bytes.size();++i)check(static_cast<unsigned char>(image.bytes[i])==16*hex(expected[2*i])+hex(expected[2*i+1]),"independent Python session fixture differs");
  {s04_alloc::Scope deny(0);const auto info=recovery::inspect_session_image(bytes(image));check(info.manifest.accepted_sequence==99 && s04_alloc::calls==0,"golden inspection allocated/lost sequence");}
  for(std::size_t size=0;size<image.bytes.size();++size) {
    bool failed=false;s04_alloc::Scope deny(0);try{static_cast<void>(recovery::inspect_session_image(bytes(image).substr(0,size)));}catch(const recovery::ImageFailure&){failed=true;}
    check(failed && s04_alloc::calls==0,"truncated session accepted or allocated");
  }
  for(std::size_t i=0;i<image.bytes.size();++i) {
    auto bad=image;bad.bytes[i]^=1;bool failed=false;s04_alloc::Scope deny(0);
    try{static_cast<void>(recovery::inspect_session_image(bytes(bad)));}catch(const recovery::ImageFailure&){failed=true;}
    check(failed && s04_alloc::calls==0,"flipped session accepted or allocated");
  }
  std::cout<<"independent session fixture "<<image.bytes.size()<<" bytes and all truncations/bit flips passed\n";
}
void reseal(recovery::SessionImage& image) {
  const auto hash=sha256_fixed(bytes(image).substr(recovery::session_image_header_size));std::copy(hash.begin(),hash.end(),image.bytes.begin()+20);
}
void word(recovery::SessionImage& image,std::size_t position,std::uint64_t value) {
  for(unsigned i=0;i<8;++i)image.bytes[position+i]=static_cast<char>(value>>(8*i));
}
template<class Action> void preflight_failure(Action action) {
  bool failed=false;{s04_alloc::Scope deny(0);try{action();}catch(const recovery::ImageFailure&){failed=true;}
    check(failed && s04_alloc::calls==0,"malformed/limited binary session was not rejected before allocation");}
}
void corruptions_and_limits() {
  // The hard-coded offsets below follow the layout with an explicit
  // 1,000,000-record input limit (the earlier default; it is now unbounded).
  SessionOptions fixed_layout;fixed_layout.input.limits.records=1'000'000;
  const auto test=typed::fixture(false,0);const auto compiler=CompiledProgram::standalone(test.plan);auto source=QuerySession::create_typed(test.plan,io::QueueLimits{},fixed_layout);
  source->start();Database database;database.tables.resize(1);typed::step(*source,test,database,test.updates[0],DeltaMode::delta);source->stop();
  auto image=source->checkpoint_image();const auto info=recovery::inspect_session_image(bytes(image));
  // The fixed-width prefix offsets are derived independently from the documented
  // layout. This fixture uses default input policies and one "feed" position.
  for(const auto offset:std::to_array<std::size_t>({84,88,89,90,91,100,124,132,140,180,212,220,228,236,332,341,374,425,427,428,437,438,447,472,497,526})) {
    auto bad=image;bad.bytes[offset]=static_cast<char>(0xff);reseal(bad);
    preflight_failure([&]{static_cast<void>(recovery::inspect_session_image(bytes(bad)));});
  }
  {auto bad=image;word(bad,100,0);reseal(bad);preflight_failure([&]{static_cast<void>(recovery::inspect_session_image(bytes(bad)));});}
  for(const auto offset:std::to_array<std::size_t>({92,473,481,489,510})) {
    auto bad=image;word(bad,offset,UINT64_MAX);reseal(bad);preflight_failure([&]{static_cast<void>(recovery::inspect_session_image(bytes(bad)));});
  }
  {auto bad=image;bad.bytes[497]='\0';reseal(bad);preflight_failure([&]{static_cast<void>(recovery::inspect_session_image(bytes(bad)));});}
  // Reseal both layers after changing a valid plan hash. Structural inspection
  // succeeds; only admission against the actual immutable Program can reject it.
  {auto bad=image;constexpr std::size_t blob=518;bad.bytes[blob+84]=bad.bytes[blob+84]=='0'?'1':'0';
    const auto inner=sha256_fixed(bytes(bad).substr(blob+84));std::copy(inner.begin(),inner.end(),bad.bytes.begin()+static_cast<std::ptrdiff_t>(blob+20));reseal(bad);
    static_cast<void>(recovery::inspect_session_image(bytes(bad)));bool rejected=false;
    try{auto value=QuerySession::restore_image(compiler,bytes(bad));}catch(const recovery::ImageFailure& error){rejected=error.fault()==recovery::ImageFault::binding;}
    check(rejected && typed::rows(*source)==Relation{{Row{std::int64_t{1}}}},"valid wrong binding admitted or changed source");}
  for(const bool work:{false,true}) {
    recovery::SessionImageLimits exact;if(work)exact.envelope.work=info.statistics.work;else exact.envelope.bytes=image.bytes.size();
    static_cast<void>(recovery::inspect_session_image(bytes(image),{},exact));
    if(work)--exact.envelope.work;else --exact.envelope.bytes;
    preflight_failure([&]{static_cast<void>(recovery::inspect_session_image(bytes(image),{},exact));});
  }
  {SessionCheckpointLimits low;low.source.work=0;preflight_failure([&]{static_cast<void>(recovery::inspect_session_image(bytes(image),low));});}
  const auto original=source.get_deleter().account();auto native=source->checkpoint_state();
  recovery::SessionImageLimits exact;exact.envelope.work=image.statistics.work;
  {auto value=recovery::encode_session_image(original,native,{},exact);check(value.bytes==image.bytes,"exact encode work changed image");}
  --exact.envelope.work;preflight_failure([&]{auto value=recovery::encode_session_image(original,native,{},exact);});
  auto unused=std::make_unique<std::istringstream>();preflight_failure([&]{auto value=QuerySession::restore_image(compiler,bytes(image),std::move(unused));});
  std::cout<<"binary checksum-valid corruptions/binding/exact limits/canonical optionals passed\n";
}
void lifetime_csv_and_scalars(bool indexed) {
  const auto test=typed::fixture(indexed,1);const auto compiler=CompiledProgram::standalone(test.plan);SessionOptions options;
  options.input.format=io::InputFormat::csv;options.input.table=TableId{0};options.input.source="csv";options.input.delimiter=';';options.input.byte_offset=123;
  auto source=QuerySession::create(test.plan,std::make_unique<std::istringstream>("y;x\n2;1\n3;2\n"),options);const auto original=source.get_deleter().account();
  source->start();check(source->begin_next(),"CSV permutation fixture missing");typed::finish(*source);source->pause();
  std::optional<recovery::SessionImage> image=source->checkpoint_image();const auto progress=source->progress();source.reset();
  auto target=QuerySession::restore_image(compiler,bytes(*image),std::make_unique<std::istringstream>("3;2\n"));typed::grant(*target,indexed);
  check(target->progress()==progress,"source-closed binary restore lost position");
  {s04_alloc::Scope deny(0);image.reset();check(!s04_alloc::triggered,"binary image destruction allocated");}
  check(original.statistics().current.requested_bytes==resource::MemoryAccount::control_bytes(),"binary image retained destroyed source storage");
  target->start();check(target->begin_next(),"CSV restored permutation missing next row");typed::finish(*target);
  check(typed::rows(*target)==Relation{{Row{std::int64_t{1},std::int64_t{2},std::int64_t{3}}}},"binary CSV mapping or alias fan-out differs");
  Catalog catalog{7,{{"r",{{"x",ScalarType::int64},{"s",ScalarType::string},{"b",ScalarType::boolean},{"d",ScalarType::date},
      {"n",ScalarType::decimal,false,Collation::binary,DecimalSpec{38,2}}}}}};
  Query query{{{"x",ScalarType::int64},{"s",ScalarType::string},{"b",ScalarType::boolean},{"d",ScalarType::date},{"n",ScalarType::decimal}},
      {{"r",TableId{0},{VariableId{0},VariableId{1},VariableId{2},VariableId{3},VariableId{4}}}},
      {{VariableId{0},"x"},{VariableId{1},"s"},{VariableId{2},"b"},{VariableId{3},"d"},{VariableId{4},"n"}},false};
  FreeConnexTree tree{NodeId{0},{{"r",NodeKind::native,{VariableId{0},VariableId{1},VariableId{2},VariableId{3},VariableId{4}},{},0,{}}},{},{}};
  const auto plan=planner::lower_tree(catalog,query,tree,indexed?s04_runtime::options():PhysicalOptions{});
  const auto artifact=CompiledProgram::standalone(plan);WindowOptions window_options;window_options.managed_tables={TableId{0}};window_options.width=10;
  const Row row{INT64_MIN,std::string(8192,'s')+std::string("\0\xff",2),true,Date::parse("0001-01-01"),Decimal::parse("123456789012345678901234567890123456.12")};
  // The native component boundary accepts raw scalar bytes. Text input adapters
  // validate UTF-8 separately; seed this codec fixture through native admission.
  DeltaRuntime runtime(artifact);const auto native_account=runtime.plan().account();
  WindowController controller(native_account,runtime.plan().source_catalog(),window_options);
  auto prepared=controller.prepare({1,io::WindowInsert{1,TableId{0},row,0},{}},1);
  auto pending=runtime.begin_view(*prepared.update());pending.drain();auto epoch=pending.commit();prepared.publish();epoch.discard();
  SessionCheckpoint state;state.state=SessionState::running;state.input_kind=SessionInputKind::typed_window;state.committed_sequence=1;
  state.input_options=io::AccountedInputOptions(native_account,io::InputOptions{});state.queue_limits=io::QueueLimits{};
  state.runtime_image=runtime.checkpoint_image();state.window=controller.checkpoint_state();
  io::QueueCheckpoint queue;queue.mode=io::QueueMode::window;queue.limits=*state.queue_limits;queue.input_limits=state.input_options.get().limits;
  queue.progress=io::AccountedInputProgress(native_account);queue.progress.sequence=1;
  const auto digest=io::input_catalog_sha256(runtime.plan().source_catalog());std::copy(digest.begin(),digest.end(),queue.catalog_sha256.begin());state.source=std::move(queue);
  auto full=QuerySession::restore_state(artifact,state);auto payload=full->checkpoint_image();
  auto restored=QuerySession::restore_image(artifact,bytes(payload));typed::grant(*restored,indexed);
  check(typed::rows(*restored)==Relation{{row}} && restored->window_state()==full->window_state(),"binary window exact scalar bytes differ");
  check(window::command(*restored,{2,io::AdvanceWatermark{10},{}})==typed::Output{{SetOperation::erase,row}} && typed::rows(*restored).empty(),"restored scalar window expiration differs");
  std::cout<<"binary indexed="<<indexed<<" source-closed/CSV permutation/all window scalars passed\n";
}
void barriers_and_failed_source(bool indexed) {
  const auto test=typed::fixture(indexed,5);auto source=QuerySession::create_typed(test.plan);
  typed::enqueue(*source,io::InputEvent{test.updates[0],{}});typed::rejected([&]{auto image=source->checkpoint_image();});
  source->start();check(source->begin_next(),"binary busy fixture missing");typed::rejected([&]{auto image=source->checkpoint_image();});
  while(source->step()!=DeltaStep::prepared){}typed::rejected([&]{auto image=source->checkpoint_image();});source->commit();
  check(source->status().output_remaining==2,"binary partial-output fixture missing");static_cast<void>(source->next_output());
  typed::rejected([&]{auto image=source->checkpoint_image();});source->drain();auto ready=source->checkpoint_image();
  bool wrong_thread=false;std::thread other([&]{try{auto image=source->checkpoint_image();}catch(const Error& error){wrong_thread=error.code()=="session_wrong_thread";}});other.join();
  check(wrong_thread,"binary capture bypassed writer guard");source->drop();typed::rejected([&]{auto image=source->checkpoint_image();});
  const auto unary=typed::fixture(indexed,0);auto broken=QuerySession::create(unary.plan,std::make_unique<std::istringstream>("{\n"));broken->start();
  typed::rejected([&]{static_cast<void>(broken->begin_next());});typed::rejected([&]{auto image=broken->checkpoint_image();});broken->stop();
  auto failed=broken->checkpoint_image();auto terminal=QuerySession::restore_image(CompiledProgram::standalone(unary.plan),bytes(failed));
  check(terminal->status().state==SessionState::stopped && terminal->status().input_failed && terminal->progress().sequence==0 && typed::rows(*terminal).empty(),
      "binary stopped failed reader lost accepted prefix/failure");
  const auto plan=window::plan(indexed);auto active=QuerySession::create_windowed(plan,window::config(WindowFifoPolicy::global));window::seed(*active);
  window::enqueue(*active,{6,io::AdvanceWatermark{20},{}});check(active->begin_next(),"binary active watermark fixture missing");window::finish(*active);
  typed::rejected([&]{auto image=active->checkpoint_image();});active->stop();preflight_failure([&]{auto image=active->checkpoint_image();});
  if(indexed) {
    auto options=s04_runtime::options();options.indexed_storage->per_operation.structural_steps=0;
    const auto base=typed::fixture(true,0);const auto limited=planner::lower_tree(base.plan.source_catalog(),base.plan.query(),base.plan.tree(),options);
    bool limited_work=false;try{auto value=QuerySession::restore_image(CompiledProgram::standalone(limited),bytes(ready));}
    catch(const Error& error){limited_work=error.code()=="storage_work_limit";}
    check(limited_work,"binary zero indexed grant escaped public storage-work presentation");
  }
  std::cout<<"binary indexed="<<indexed<<" writer/busy/failed-reader/active-watermark/zero-grant barriers passed\n";
}
void encoder_consistency() {
  const auto test=typed::fixture(false,0);auto source=QuerySession::create_typed(test.plan);const auto account=source.get_deleter().account();
  for(unsigned mutation=0;mutation<4;++mutation) {
    auto state=source->checkpoint_state();
    if(mutation==0)std::get<io::QueueCheckpoint>(state.source).progress.sequence=1;
    if(mutation==1)state.end_of_input=true;
    if(mutation==2){io::InputOptions options;options.format=io::InputFormat::binary;state.input_options=io::AccountedInputOptions(account,options);}
    if(mutation==3){state.state=SessionState::running;state.committed_sequence=1;}
    preflight_failure([&]{auto image=recovery::encode_session_image(account,state);});
  }
  auto window_source=QuerySession::create_windowed(window::plan(false),window::config(WindowFifoPolicy::global));window::seed(*window_source);
  const auto window_account=window_source.get_deleter().account();
  for(unsigned mutation=0;mutation<8;++mutation) {
    auto state=window_source->checkpoint_state();auto& value=*state.window;
    if(mutation==0)value.options.width=0;
    if(mutation==1)value.progress.completed_command_sequence=0;
    if(mutation==2)value.counts[0].id=0;
    if(mutation==3)value.counts[0].count=0;
    if(mutation==4)value.labels[0].deadline=0;
    if(mutation==5)value.stopped=true;
    if(mutation==6)value.last_command_work=value.options.command_work_limit+1;
    if(mutation==7)value.options.fifo=static_cast<WindowFifoPolicy>(5);
    preflight_failure([&]{auto image=recovery::encode_session_image(window_account,state);});
  }
  std::cout<<"binary mutable-native encoder/inspector consistency passed\n";
}
}
int main(int argc,char** argv) {
  try {
    check(argc==2,"session fixture path required");golden(argv[1]);corruptions_and_limits();encoder_consistency();
    for(const bool indexed:{false,true}) {
      for(unsigned kind=0;kind<6;++kind)for(const auto state:{SessionState::created,SessionState::running,SessionState::paused,SessionState::stopped})typed_case(indexed,kind,state);
      for(const auto format:{io::InputFormat::jsonl,io::InputFormat::binary,io::InputFormat::csv,io::InputFormat::legacy_signed,io::InputFormat::legacy_relations,
          io::InputFormat::legacy_insert_only,io::InputFormat::legacy_flags,io::InputFormat::legacy_timestamp_flags})stream_case(indexed,format);
      for(const auto fifo:{WindowFifoPolicy::global,WindowFifoPolicy::per_relation,WindowFifoPolicy::physical_global,WindowFifoPolicy::physical_per_relation})
        for(const auto state:{SessionState::created,SessionState::running,SessionState::paused,SessionState::stopped})window_case(indexed,fifo,state);
      lifetime_csv_and_scalars(indexed);barriers_and_failed_source(indexed);
    }
  }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
