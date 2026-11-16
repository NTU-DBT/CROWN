#include "session_checkpoint_test_fixture.hpp"
using namespace crown;
using namespace crown::runtime;
using namespace crown::session_checkpoint_test;
namespace {
void typed(bool indexed,unsigned kind,SessionState control) {
  const auto test=fixture(indexed,kind);const auto compiler=CompiledProgram::standalone(test.plan);
  SessionOptions options;options.snapshot.rows=31;options.snapshot.bytes=1024*1024;
  options.delta.mode=kind==2?DeltaMode::maintenance:DeltaMode::delta;
  options.delta.physical.support.order=indexed?PropagationOrder::lifo:PropagationOrder::fifo;
  auto source=QuerySession::create_typed(test.plan,{},options);const auto original=source.get_deleter().account();
  Database database;database.tables.resize(test.plan.source_catalog().tables.size());
  if(control!=SessionState::created) {
    source->start();step(*source,test,database,test.updates[0],options.delta.mode);step(*source,test,database,test.updates[1],options.delta.mode);
    if(control==SessionState::paused){source->pause();}
    if(control==SessionState::stopped){source->stop();}
  }
  workload::Options configured;configured.mode=workload::Mode::counters;configured.period=2;
  source->configure_workload_statistics(configured);
  const auto expected=rows(*source);const auto progress=source->progress();const auto before=original.statistics();std::size_t captures=0;
  std::optional<SessionCheckpoint> checkpoint;
  {s04_alloc::Scope count;checkpoint=source->checkpoint_state();captures=s04_alloc::calls;}
  check(captures==original.statistics().successful_allocations-before.successful_allocations && captures>0,"session capture allocated outside original account");
  std::optional<QuerySession::Owner> restored;std::size_t restores=0;
  {s04_alloc::Scope count;restored=QuerySession::restore_state(compiler,*checkpoint);restores=s04_alloc::calls;}
  auto& result=**restored;grant(result,indexed);const auto target=restored->get_deleter().account();
  const auto restore_peak=target.statistics().peak_requested_bytes;
  check(restores==target.statistics().successful_allocations,"session restore allocated outside its receiving account");
  check(result.status().state==control && result.status().phase==SessionPhase::ready && rows(result)==expected && result.progress()==progress,"session restore lost control/sequence/source/results");
  check(result.workload_statistics_options()==configured && result.run_context()->snapshot.rows==31 && result.run_context()->snapshot.bytes==1024*1024,"session restore lost configuration");
  const auto resident=original.statistics().current;
  for(unsigned i=0;i<10;++i){auto value=source->checkpoint_state();}
  check(original.statistics().current==resident,"repeated session checkpoint grew resident storage");
  if(kind==1 && control==SessionState::running) {
    for(std::size_t point=0;point<captures;++point) {
      bool failed=false;{s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{auto value=source->checkpoint_state();}catch(const std::bad_alloc&){failed=true;}}
      check(failed && original.statistics().current==resident && source->progress()==progress && rows(*source)==expected,"capture OOM changed source epoch or leaked");
    }
    for(std::size_t point=0;point<restores;++point) {
      bool failed=false;{s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{auto value=QuerySession::restore_state(compiler,*checkpoint);}catch(const std::bad_alloc&){failed=true;}}
      check(failed && original.statistics().current==resident && rows(*source)==expected,"restore OOM changed source epoch");
    }
    SessionRestoreOptions exact;exact.memory_limit_bytes=restore_peak;
    {
      auto value=QuerySession::restore_state(compiler,*checkpoint,exact);
      check(value->status().state==control && value->status().committed_sequence==checkpoint->committed_sequence &&
          value.get_deleter().account().statistics().peak_requested_bytes==restore_peak,
          "exact whole-session restore byte cap failed");
    }
    --*exact.memory_limit_bytes;bool failed=false;
    try{auto value=QuerySession::restore_state(compiler,*checkpoint,exact);}catch(const resource::MemoryFailure& error){failed=error.fault()==resource::MemoryFault::limit;}
    check(failed,"one-under whole-session byte cap did not reject");
  }
  if(control!=SessionState::stopped) {
    source->start();result.start();auto other=database;
    const auto begin=control==SessionState::created?std::size_t{0}:std::size_t{2};
    for(std::size_t i=begin;i<test.updates.size();++i)check(step(*source,test,database,test.updates[i],options.delta.mode)==step(result,test,other,test.updates[i],options.delta.mode),"next exact deltas differ after restore");
    source->finish_input();result.finish_input();check(!source->begin_next() && !result.begin_next(),"restored queue EOF differs");
  }else rejected([&]{result.start();});
  std::cout<<"typed indexed="<<indexed<<" query="<<kind<<" control="<<static_cast<unsigned>(control)<<" capture/restore="<<captures<<'/'<<restores<<" passed\n";
}
void stream(io::InputFormat format,bool indexed) {
  const auto test=fixture(indexed,0);const auto compiler=CompiledProgram::standalone(test.plan);SessionOptions options;options.input.format=format;
  options.input.limits.records=2;std::string prefix,tail;
  if(format==io::InputFormat::jsonl || format==io::InputFormat::binary) {
    const io::InputEvent a{{1,TableId{0},SetOperation::insert,{std::int64_t{1}}},io::SourcePosition{"wire",10}},
        b{{2,TableId{0},SetOperation::insert,{std::int64_t{2}}},io::SourcePosition{"wire",20}};
    if(format==io::InputFormat::jsonl){prefix=io::write_input_json(a,test.plan.source_catalog())+"\n";tail=io::write_input_json(b,test.plan.source_catalog())+"\n";}
    else {prefix=io::write_input_binary(a,test.plan.source_catalog());tail=io::write_input_binary(b,test.plan.source_catalog());}
  }else {
    options.input.source="stream";
    if(format!=io::InputFormat::legacy_relations)options.input.table=TableId{0};
    if(format==io::InputFormat::csv){prefix="x\n1\n";tail="2\n";options.input.byte_offset=123;}
    if(format==io::InputFormat::legacy_signed){prefix="+,1\n";tail="+,2\n";}
    if(format==io::InputFormat::legacy_relations){options.input.relation_tokens.emplace("R",TableId{0});prefix="+,R,1\n";tail="+,R,2\n";}
    if(format==io::InputFormat::legacy_insert_only){prefix="1\n";tail="2\n";}
    if(format==io::InputFormat::legacy_flags){prefix="1,1\n";tail="1,2\n";}
    if(format==io::InputFormat::legacy_timestamp_flags){prefix="10,1,1\n";tail="20,1,2\n";}
  }
  options.input.limits.total_bytes=prefix.size()+tail.size();auto source=QuerySession::create(test.plan,std::make_unique<std::istringstream>(prefix+tail),options);
  source->start();check(source->begin_next(),"stream first event missing");finish(*source);source->pause();auto checkpoint=source->checkpoint_state();
  for(unsigned mutation=0;mutation<2;++mutation) {
    auto bad=source->checkpoint_state();auto& saved=std::get<io::ReaderCheckpoint>(bad.source);
    if(mutation==0)saved.records=0;
    else {
      auto invalid=source->progress();invalid.source_positions.emplace("extra",10);
      check(invalid.source_positions.size()>invalid.sequence,"invalid accepted-position fixture missing");
      saved.progress=io::AccountedInputProgress(source.get_deleter().account(),invalid);
    }
    auto unread=std::make_unique<std::istringstream>(tail);
    {s04_alloc::Scope deny(0);bool corrupt=false;
      try{auto value=QuerySession::restore_state(compiler,bad,std::move(unread));}
      catch(const recovery::ImageFailure& error){corrupt=error.fault()==recovery::ImageFault::corrupt;}
      check(corrupt && s04_alloc::calls==0,"inconsistent reader counter/positions were not rejected before allocation");}
  }
  auto continuation=std::make_unique<std::istringstream>(tail);auto target=QuerySession::restore_state(compiler,checkpoint,std::move(continuation));grant(*target,indexed);
  check(target->status().state==SessionState::paused && target->progress()==source->progress() && rows(*target)==rows(*source),"stream restore lost paused state");
  source->start();target->start();check(source->begin_next() && target->begin_next(),"continued stream event missing");
  check(finish(*source)==finish(*target) && source->progress()==target->progress() && rows(*source)==rows(*target),"continued stream state differs");
  check(!source->begin_next() && !target->begin_next(),"stream EOF differs");
  auto ended=target->checkpoint_state();auto restored=QuerySession::restore_state(compiler,ended,std::make_unique<std::istringstream>(prefix));
  check(!restored->begin_next() && restored->status().end_of_input,"restored EOF consumed new data");
  target->stop();auto stopped=target->checkpoint_state();auto terminal=QuerySession::restore_state(compiler,stopped);
  check(terminal->status().state==SessionState::stopped && rows(*terminal)==rows(*target),"stopped stream restore differs");
  std::cout<<"stream indexed="<<indexed<<" profile="<<static_cast<unsigned>(format)<<" paused/EOF/stopped continuation passed\n";
}
void barriers(bool indexed) {
  const auto test=fixture(indexed,5);auto source=QuerySession::create_typed(test.plan);
  const auto busy=[&] {
    const auto before=source->status();const auto progress=source->progress();
    rejected([&]{auto value=source->checkpoint_state();});const auto after=source->status();
    check(after.state==before.state && after.phase==before.phase && after.committed_sequence==before.committed_sequence &&
        after.output_remaining==before.output_remaining && source->progress()==progress,"rejected capture changed session phase/progress");
  };
  enqueue(*source,io::InputEvent{test.updates[0],{}});busy();source->start();check(source->begin_next(),"barrier input missing");busy();
  source->pause();check(source->status().phase==SessionPhase::paused_pending,"paused private fixture missing");busy();source->start();
  while(source->step()!=DeltaStep::prepared){}busy();source->commit();
  check(source->status().output_remaining==2,"SQL EXISTS two-result transition missing");busy();
  check(source->next_output().has_value() && source->status().output_remaining==1,"partially consumed output fixture missing");busy();
  while(source->next_output()){}auto complete=source->checkpoint_state();
  enqueue(*source,io::InputEvent{test.updates[1],{}});check(source->begin_next(),"drain barrier input missing");source->start_drain();
  check(source->status().phase==SessionPhase::draining,"draining fixture missing");busy();source->drain();
  auto drained=source->checkpoint_state();check(drained.committed_sequence==2,"drained checkpoint sequence missing");
  bool wrong_thread=false;std::thread other([&]{try{auto value=source->checkpoint_state();}catch(const Error& error){wrong_thread=error.code()=="session_wrong_thread";}});other.join();
  check(wrong_thread,"physical checkpoint bypassed creator-thread guard");source->drop();rejected([&]{auto value=source->checkpoint_state();});
  std::cout<<"typed indexed="<<indexed<<" queued/private/paused/prepared/partial-output/drain barriers passed\n";
}
void failed_readers(bool indexed) {
  const auto test=fixture(indexed,5);const auto compiler=CompiledProgram::standalone(test.plan);
  SessionOptions options;options.delta.physical.derivation_limit=1;
  const auto record=[&](const PhysicalSetUpdate& update){return io::write_input_json(io::InputEvent{update,{}},test.plan.source_catalog())+"\n";};
  auto source=QuerySession::create(test.plan,std::make_unique<std::istringstream>(record(test.updates[0])+record(test.updates[1])),options);
  source->start();check(source->begin_next(),"cached reader fixture missing");finish(*source);
  bool overflow=false;try{check(source->begin_next(),"cached second record missing");finish(*source);}catch(const Error& error){overflow=error.code()=="derivation_overflow";}
  check(overflow && !source->status().input_failed && source->progress().sequence==1 && source->status().phase==SessionPhase::ready,
      "healthy cached reader rejection fixture missing");
  rejected([&]{auto value=source->checkpoint_state();});source->stop();auto saved=source->checkpoint_state();
  auto restored=QuerySession::restore_state(compiler,saved);
  check(restored->status().state==SessionState::stopped && !restored->status().input_failed && restored->progress()==source->progress() &&
      rows(*restored)==Relation{{Row{true}}},"stopped healthy cached reader lost committed prefix");
  auto bad=source->checkpoint_state();io::InputProgress impossible{1,{{"one",10},{"two",20}}};
  bad.source=io::AccountedInputProgress(source.get_deleter().account(),impossible);
  rejected([&]{auto value=QuerySession::restore_state(compiler,bad);});
  const auto unary=fixture(indexed,0);const auto unary_compiler=CompiledProgram::standalone(unary.plan);
  auto broken=QuerySession::create(unary.plan,std::make_unique<std::istringstream>("{\n"));broken->start();
  bool invalid=false;try{static_cast<void>(broken->begin_next());}catch(const Error&){invalid=true;}
  check(invalid && broken->status().input_failed && broken->progress().sequence==0,"broken reader fixture missing");
  rejected([&]{auto value=broken->checkpoint_state();});broken->stop();auto failed=broken->checkpoint_state();
  SessionCheckpointLimits low;low.source.work=1;
  {s04_alloc::Scope deny(0);bool limited=false;
    try{auto value=broken->checkpoint_state(low);}catch(const recovery::ImageFailure& error){limited=error.fault()==recovery::ImageFault::work;}
    check(limited && s04_alloc::calls==0,"stopped source options/progress limit was not checked before allocation");}
  auto terminal=QuerySession::restore_state(unary_compiler,failed);
  check(terminal->status().state==SessionState::stopped && terminal->status().input_failed && terminal->progress().sequence==0 && rows(*terminal).empty(),
      "stopped failed reader lost failure or committed state");
  std::cout<<"stream indexed="<<indexed<<" healthy cached and failed reader stop/restore passed\n";
}
void lifetime_and_initialization(bool indexed) {
  const auto test=fixture(indexed,0);const auto compiler=CompiledProgram::standalone(test.plan);
  Database database;database.tables.resize(1);database.tables[0].insert(Row{std::int64_t{7}});
  auto source=QuerySession::create_typed(test.plan,database);const auto original=source.get_deleter().account();
  std::optional<SessionCheckpoint> saved=source->checkpoint_state();const auto expected=oracle(test,database);source.reset();
  const auto retained=original.statistics();
  for(const auto purpose:{resource::MemoryPurpose::table_state,resource::MemoryPurpose::arena_slot,resource::MemoryPurpose::source_counts,
      resource::MemoryPurpose::delta_state,resource::MemoryPurpose::journal_undo,resource::MemoryPurpose::cursor})
    check(retained.by_purpose[static_cast<std::size_t>(purpose)].requested_bytes==0,"checkpoint retained destroyed runtime storage");
  check(retained.by_purpose[static_cast<std::size_t>(resource::MemoryPurpose::recovery_log)].requested_bytes>0,"checkpoint image lost native owner");
  auto target=QuerySession::restore_state(compiler,*saved);grant(*target,indexed);
  check(target->status().state==SessionState::created && target->status().committed_sequence==0 && rows(*target)==expected,"created initialized restore lost epoch-zero rows");
  {s04_alloc::Scope deny(0);saved.reset();check(!s04_alloc::triggered,"checkpoint destruction allocated");}
  check(original.statistics().current.requested_bytes==resource::MemoryAccount::control_bytes(),"released checkpoint retained original query allocations");
  original.check_invariants();target->start();step(*target,test,database,test.updates[0],DeltaMode::delta);
  const auto owner=target.get_deleter().account();auto active=target->checkpoint_state();
  // A stream continuation is caller-owned; a typed checkpoint cannot use one.
  rejected([&]{auto value=QuerySession::restore_state(compiler,active,std::make_unique<std::istringstream>());});
  auto stream_source=QuerySession::create(test.plan,std::make_unique<std::istringstream>());auto stream_state=stream_source->checkpoint_state();
  rejected([&]{auto value=QuerySession::restore_state(compiler,stream_state);});
  io::InputOptions different;different.format=io::InputFormat::binary;
  stream_state.input_options=io::AccountedInputOptions(owner,different);
  rejected([&]{auto value=QuerySession::restore_state(compiler,stream_state,std::make_unique<std::istringstream>());});
  std::cout<<"typed indexed="<<indexed<<" source-closed lifetime/initialized epoch-zero/policy mismatch passed\n";
}
}
int main() {
  try {
    for(const bool indexed:{false,true}) {
      for(unsigned kind=0;kind<6;++kind)for(const auto state:{SessionState::created,SessionState::running,SessionState::paused,SessionState::stopped})typed(indexed,kind,state);
      for(const auto format:{io::InputFormat::jsonl,io::InputFormat::binary,io::InputFormat::csv,io::InputFormat::legacy_signed,
          io::InputFormat::legacy_relations,io::InputFormat::legacy_insert_only,io::InputFormat::legacy_flags,io::InputFormat::legacy_timestamp_flags})stream(format,indexed);
      barriers(indexed);failed_readers(indexed);lifetime_and_initialization(indexed);
    }
  }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
