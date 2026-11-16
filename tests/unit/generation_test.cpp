#include "generation_fixture.hpp"
#include "session_journal_stream_cases.hpp"
#include "crown/api/error.hpp"
using namespace crown;
using namespace crown::runtime;
using namespace crown::generation_test;
namespace {
void replay_outputs(QuerySession& session,const typed::Output& expected,std::uint64_t generation,std::uint64_t epoch) {
  typed::Output actual;
  while(auto item=session.next_recovered_output()) {
    check(item->query_id==options().journal.query_id && item->generation==generation && item->physical_sequence==epoch,"root-selected replay output identity differs");
    check(actual.emplace(item->value.operation,storage::export_row(item->value.tuple.values())).second,"duplicate generation replay output");
  }
  check(actual==expected,"root-selected replay output differs");
}
void apply(Database& database,const PhysicalSetUpdate& event) {
  auto& rows=database.tables[event.table.value];if(event.operation==SetOperation::insert)rows.insert(event.values);else rows.erase(event.values);
}
void typed_case(bool indexed,unsigned kind,bool pending) {
  Fixture f(indexed,kind,false);auto config=options();config.journal.generation=7;f.session->enable_generation(f.name,config);
  Database database;database.tables.resize(f.test.plan.source_catalog().tables.size());
  const auto mode=kind==2?DeltaMode::maintenance:DeltaMode::delta;
  for(std::size_t i=0;i<2;++i)static_cast<void>(typed::step(*f.session,f.test,database,f.test.updates[i],mode));
  const auto old_checkpoint=contents(path(f.name,7,".ckpt")),old_log=contents(path(f.name,7,".wal"));
  f.session->rotate_generation();const auto selected=root(f.name);
  check(selected.generation==8 && selected.first_generation==7 && selected.physical_sequence==2 && selected.command_sequence==2 &&
      selected.checkpoint_sha256==sha256_fixed(contents(path(f.name,8,".ckpt"))) && jp::scan(contents(path(f.name,8,".wal"))).records==1,"rotation selected wrong pair/bases");
  auto after=database;apply(after,f.test.updates[2]);const auto expected=mode==DeltaMode::delta?typed::difference(typed::oracle(f.test,database),typed::oracle(f.test,after)):typed::Output{};
  if(pending){typed::enqueue(*f.session,io::InputEvent{f.test.updates[2],io::SourcePosition{"feed",30}});check(f.session->begin_next(),"pending generation input missing");}
  else {static_cast<void>(typed::step(*f.session,f.test,database,f.test.updates[2],mode));}
  f.session.reset();auto restore=recovery_options();restore.replay.journal.generation=UINT64_MAX;
  auto result=QuerySession::restore_generation(CompiledProgram::standalone(f.test.plan),f.name,restore);typed::grant(*result,indexed);
  check(result->status().state==SessionState::paused && result->generation_state().selected==selected && typed::rows(*result)==typed::oracle(f.test,database) &&
      result->recovery_status().pending_input_sequence.has_value()==pending,"generation restore state/source/pending differs");
  replay_outputs(*result,pending?typed::Output{}:expected,8,3);result->start();
  if(pending){check(result->begin_next(),"retained generation input missing");check(typed::finish(*result)==expected,"pending generation update differs");database=std::move(after);}
  static_cast<void>(typed::step(*result,f.test,database,f.test.updates[3],mode));
  check(result->progress().sequence==4 && result->status().committed_sequence==4 && contents(path(f.name,7,".ckpt"))==old_checkpoint && contents(path(f.name,7,".wal"))==old_log,"generation resume changed historical pair or counters");
  result->rotate_generation();check(root(f.name).generation==9 && root(f.name).first_generation==7,"second rotation lost retained generation range");
  std::cout<<"generation typed indexed="<<indexed<<" query="<<kind<<" pending="<<pending<<" exact native state/output/source/next update passed\n";
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
  throw std::runtime_error("unknown generation stream profile");
}
void stream_case(bool indexed,const session_journal_stream_test::Case& profile,bool pending) {
  Directory dir;const auto test=typed::fixture(indexed,1);const auto name=dir.file("stream.root");const Catalog catalog{5,{{"e",{{"x",ScalarType::int64},{"y",ScalarType::int64}}}}};
  const auto input=profile.data+third_record(profile,catalog);SessionOptions policy;policy.input=profile.options;policy.input.limits.records=3;policy.input.limits.total_bytes=input.size();
  auto source=QuerySession::create(test.plan,std::make_unique<std::istringstream>(input),policy);source->start();source->enable_generation(name,options());check(source->begin_next(),"generation first stream row missing");static_cast<void>(typed::finish(*source));source->rotate_generation();
  check(source->begin_next(),"generation second stream row missing");if(!pending)static_cast<void>(typed::finish(*source));source.reset();auto restore=recovery_options();restore.replay.seek_source_from_origin=true;
  auto result=QuerySession::restore_generation(CompiledProgram::standalone(test.plan),name,restore,std::make_unique<std::istringstream>(input));
  replay_outputs(*result,pending?typed::Output{}:typed::Output{{SetOperation::insert,Row{std::int64_t{1},std::int64_t{2},std::int64_t{3}}}},2,2);
  result->start();if(pending){check(result->begin_next(),"generation retained stream row missing");static_cast<void>(typed::finish(*result));}
  check(result->begin_next(),"generation unread third row missing");static_cast<void>(typed::finish(*result));
  check(!result->begin_next() && result->progress().sequence==3 && result->status().committed_sequence==3 &&
      typed::rows(*result)==Relation{{Row{std::int64_t{1},std::int64_t{2},std::int64_t{3}}},{Row{std::int64_t{2},std::int64_t{3},std::int64_t{4}}}},"generation decoder/source/EOF differs");
  std::cout<<"generation stream "<<profile.name<<" indexed="<<indexed<<" pending="<<pending<<" header/source/seek/next update passed\n";
}
void window_case(bool indexed,WindowFifoPolicy fifo,unsigned steps) {
  Directory dir;const auto plan=window::plan(indexed);const auto name=dir.file("window.root");auto source=QuerySession::create_windowed(plan,window::config(fifo));source->start();source->enable_generation(name,options());
  for(std::uint64_t label=1;label<=3;++label)static_cast<void>(window::command(*source,{label,io::WindowInsert{label,TableId{0},Row{std::int64_t{1}},label},{}}));
  source->rotate_generation();typed::enqueue(*source,io::WindowCommand{4,io::AdvanceWatermark{30},io::SourcePosition{"watermark",100}});
  if(steps==0)check(source->begin_next(),"generation pending window missing");
  for(unsigned i=0;i<steps;++i){check(source->begin_next(),"generation window substep missing");static_cast<void>(typed::finish(*source));}
  source.reset();auto result=QuerySession::restore_generation(CompiledProgram::standalone(plan),name,recovery_options());result->discard_recovered_output();result->start();
  if(steps<3){bool blocked=false;try{result->rotate_generation();}catch(const SessionJournalFailure&){blocked=true;}check(blocked,"rotation admitted a partial window command");}
  for(unsigned i=steps;i<3;++i){check(result->begin_next(),"generation window continuation missing");static_cast<void>(typed::finish(*result));}
  check(result->progress().sequence==4 && result->status().committed_sequence==2 && typed::rows(*result).empty(),"generation window replay lost command boundary");
  result->rotate_generation();check(root(name).generation==3 && root(name).physical_sequence==2 && root(name).command_sequence==4,"generation window checkpoint bases differ");
  std::cout<<"generation window indexed="<<indexed<<" fifo="<<static_cast<unsigned>(fifo)<<" steps="<<steps<<" partial metadata/physical continuation passed\n";
}
void repair_checksum(std::string& bytes) {const auto hash=sha256_fixed(std::string_view(bytes).substr(0,recovery::generation_root_size-64));std::copy(hash.begin(),hash.end(),bytes.end()-64);}
void corruption() {
  Fixture f;f.update(0);f.update(1);f.session.reset();const auto original=contents(f.name);const auto log=path(f.name,1,".wal"),full=contents(log);const auto compiler=CompiledProgram::standalone(f.test.plan);
  const auto rejected=[&](std::string_view bytes){put(f.name,bytes);bool bad=false;try{auto value=QuerySession::restore_generation(compiler,f.name,recovery_options());}catch(const recovery::GenerationFailure&){bad=true;}catch(const jp::Failure&){bad=true;}
    check(bad && contents(log)==full,"malformed generation root repaired/accepted selected log");};
  for(std::size_t cut=0;cut<original.size();++cut)rejected(std::string_view(original).substr(0,cut));
  for(std::size_t i=0;i<original.size();++i){auto bad=original;bad[i]^=1;rejected(bad);}
  rejected(original+"x");
  for(const std::size_t field:{std::size_t{8},std::size_t{20},std::size_t{52},std::size_t{60},std::size_t{68},std::size_t{132},std::size_t{140}}) {
    auto bad=original;bad[field]^=1;repair_checksum(bad);rejected(bad);
  }
  auto wrong=original;wrong[68]=wrong[68]=='0'?'1':'0';repair_checksum(wrong);put(f.name,wrong);put(log,full.substr(0,full.size()-1));bool bound=false;
  try{auto value=QuerySession::restore_generation(compiler,f.name,recovery_options());}catch(const recovery::GenerationFailure& e){bound=e.fault()==recovery::GenerationFault::binding;}
  check(bound && contents(log)==full.substr(0,full.size()-1),"root/checkpoint mismatch repaired log before binding validation");put(f.name,original);put(log,full);
  auto value=QuerySession::restore_generation(compiler,f.name,recovery_options());check(value->status().committed_sequence==2,"valid root lost after hostile corpus");
  std::cout<<"generation every root truncation/bit flip, checksum-valid binding and validation-before-repair passed\n";
}
void ownership_and_limits() {
  Fixture f(false,1,false);auto config=options();config.retained_generations=2;f.session->enable_generation(f.name,config);config.retained_generations=UINT64_MAX;f.update(0);f.session->rotate_generation();
  const auto selected=contents(f.name);bool capped=false;try{f.session->rotate_generation();}catch(const recovery::GenerationFailure& e){capped=e.fault()==recovery::GenerationFault::limit;}
  check(capped && contents(f.name)==selected && !f.session->generation_state().recovery_required,"copied generation retention cap bypassed/poisoned preflight");
  bool busy=false;try{auto value=QuerySession::restore_generation(CompiledProgram::standalone(f.test.plan),f.name,recovery_options());}catch(const recovery::GenerationFailure& e){busy=e.fault()==recovery::GenerationFault::busy;}check(busy,"root lock allowed a second writer");
  f.session->drop();auto recovery=recovery_options();recovery.retained_generations=1;bool too_many=false;
  try{auto value=QuerySession::restore_generation(CompiledProgram::standalone(f.test.plan),f.name,recovery);}catch(const recovery::GenerationFailure& e){too_many=e.fault()==recovery::GenerationFault::limit;}check(too_many,"recovery retention limit ignored");
  std::uint64_t operations=0,work=0;{auto value=QuerySession::restore_generation(CompiledProgram::standalone(f.test.plan),f.name,recovery_options());operations=value->generation_state().operations;work=value->generation_state().validation_work;}
  for(const bool work_limit:{false,true}) {
    auto exact=recovery_options();if(work_limit)exact.root.validation_work=work;else exact.root.operations=operations;
    {auto value=QuerySession::restore_generation(CompiledProgram::standalone(f.test.plan),f.name,exact);}
    if(work_limit)--exact.root.validation_work;else --exact.root.operations;const auto before=descriptors();bool limit=false;
    try{auto value=QuerySession::restore_generation(CompiledProgram::standalone(f.test.plan),f.name,exact);}catch(const recovery::GenerationFailure& e){limit=e.fault()==recovery::GenerationFault::limit;}
    check(limit && descriptors()==before && contents(f.name)==selected,"exact/under generation quota or descriptor contract failed");
  }
  {Fixture orphan;orphan.update(0);const auto old_cp=contents(path(orphan.name,1,".ckpt")),old_wal=contents(path(orphan.name,1,".wal"));put(path(orphan.name,2,".ckpt"),"orphan checkpoint");put(path(orphan.name,2,".wal"),"orphan log");orphan.session->rotate_generation();
    check(root(orphan.name).generation==2 && contents(path(orphan.name,1,".ckpt"))==old_cp && contents(path(orphan.name,1,".wal"))==old_wal,"unselected candidate cleanup touched committed history");}
  {Fixture initial(false,1,false);const auto candidate=path(initial.name,1,".ckpt");put(candidate,"reserved orphan");bool exists=false;try{initial.session->enable_generation(initial.name,options());}catch(const recovery::GenerationFailure&){exists=true;}
    check(exists && contents(candidate)=="reserved orphan" && !std::filesystem::exists(initial.name),"initial generation replaced an existing candidate");}
  {Fixture maximum(false,1,false);auto last=options();last.journal.generation=UINT64_MAX;maximum.session->enable_generation(maximum.name,last);bool overflow=false;try{maximum.session->rotate_generation();}catch(const recovery::GenerationFailure& e){overflow=e.fault()==recovery::GenerationFault::limit;}check(overflow && root(maximum.name).generation==UINT64_MAX,"generation counter overflow accepted");}
  std::cout<<"generation ownership/drop, retained histories/orphans, copied policy and exact/under work/I/O caps passed\n";
}
void paths_and_golden(const char* golden) {
  const auto hex=contents(golden);std::string bytes;int high=-1;
  for(const char c:hex) {
    if(c=='\n' || c=='\r' || c==' ' || c=='\t')continue;
    const int digit=c>='0' && c<='9'?c-'0':c>='a' && c<='f'?c-'a'+10:-1;check(digit>=0,"invalid independent golden hex");
    if(high<0)high=digit;else{bytes.push_back(static_cast<char>(16*high+digit));high=-1;}
  }
  const auto selected=recovery::inspect_generation_root(bytes);
  check(high<0 && bytes.size()==212 && sha256(bytes)=="bc82d64bb74bdf4ca99958b41d9bf83d33025e15c08407b3cfceef0168543d9c" && selected.query_id==options().journal.query_id && selected.generation==7 && selected.first_generation==3 &&
      selected.checkpoint_sha256==sha256_fixed("checkpoint-payload") && selected.physical_sequence==11 && selected.command_sequence==13,"independent root golden differs");
  for(const bool lock:{false,true}) {
    Fixture f(false,1,false);const auto victim=f.directory.file("victim");put(victim,"keep target");const auto link=lock?f.name+".lock":f.name;
    check(::symlink(victim.c_str(),link.c_str())==0,"generation symlink fixture failed");bool rejected=false;
    try{f.session->enable_generation(f.name,options());}catch(const recovery::GenerationFailure&){rejected=true;}
    check(rejected && contents(victim)=="keep target" && std::filesystem::is_symlink(link),"generation followed/replaced root/lock symlink");
  }
  {Fixture f(false,1,false);const auto name=f.directory.file(std::string(233,'x'));bool rejected=false;try{f.session->enable_generation(name,options());}catch(const recovery::GenerationFailure& e){rejected=e.fault()==recovery::GenerationFault::path;}check(rejected,"generation admitted an overlong derived sibling name");}
  for(unsigned kind=0;kind<3;++kind) {
    Fixture f(false,1,false);auto policy=options();if(kind==0)policy.journal.checkpoint.path_bytes=1;else if(kind==1)policy.journal.checkpoint.chunk_bytes=0;else policy.journal.checkpoint.operations=0;
    bool rejected=false;try{f.session->enable_generation(f.name,policy);}catch(const recovery::GenerationFailure& e){rejected=e.fault()==recovery::GenerationFault::limit;}
    check(rejected && !std::filesystem::exists(f.name) && !std::filesystem::exists(path(f.name,1,".ckpt")) && !f.session->generation_state().enabled,"invalid checkpoint I/O policy selected an unreadable pair");
    f.session->enable_generation(f.name,options());check(root(f.name).generation==1,"preflight rejection prevented valid retry");
  }
  {Fixture f;f.session.reset();std::filesystem::remove(f.name);bool missing=false;try{auto value=QuerySession::restore_generation(CompiledProgram::standalone(f.test.plan),f.name,recovery_options());}catch(const recovery::GenerationFailure&){missing=true;}check(missing && std::filesystem::exists(path(f.name,1,".ckpt")) && std::filesystem::exists(path(f.name,1,".wal")),"recovery guessed selected generation from orphan files");}
  std::cout<<"generation independent212-byte root golden, nofollow paths and no orphan selection passed\n";
}
}
int main(int argc,char** argv){try{
  check(argc==2,"expected independent root golden path");
  for(const bool indexed:{false,true}) {
    for(unsigned kind=0;kind<6;++kind)for(const bool pending:{false,true})typed_case(indexed,kind,pending);
    const Catalog catalog{5,{{"e",{{"x",ScalarType::int64},{"y",ScalarType::int64}}}}};for(const auto& profile:session_journal_stream_test::cases(catalog))for(const bool pending:{false,true})stream_case(indexed,profile,pending);
    for(const auto fifo:{WindowFifoPolicy::global,WindowFifoPolicy::per_relation})for(unsigned step=0;step<4;++step)window_case(indexed,fifo,step);
  }
  corruption();ownership_and_limits();paths_and_golden(argv[1]);
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
