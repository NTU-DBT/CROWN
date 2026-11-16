#include "window_checkpoint_test_fixture.hpp"
using namespace crown;
using namespace crown::runtime;
using namespace crown::window_checkpoint_test;
namespace {
void scenario(bool indexed,WindowFifoPolicy fifo,SessionState state) {
  const auto artifact=plan(indexed);const auto compiler=CompiledProgram::standalone(artifact);
  auto source=QuerySession::create_windowed(artifact,config(fifo));const auto original=source.get_deleter().account();
  if(state!=SessionState::created)seed(*source);
  if(state==SessionState::paused)source->pause();
  if(state==SessionState::stopped)source->stop();
  const auto expected=source->window_state();const auto expected_rows=rows(*source);const auto progress=source->progress();
  const auto before=original.statistics();std::optional<SessionCheckpoint> checkpoint;std::size_t captures=0;
  {s04_alloc::Scope count;checkpoint=source->checkpoint_state();captures=s04_alloc::calls;}
  check(captures>0 && captures==original.statistics().successful_allocations-before.successful_allocations,"window session capture escaped original account");
  std::optional<QuerySession::Owner> target;std::size_t restores=0;
  {s04_alloc::Scope count;target=QuerySession::restore_state(compiler,*checkpoint);restores=s04_alloc::calls;}
  auto& restored=**target;grant(restored,indexed);const auto account=target->get_deleter().account();
  const auto restore_peak=account.statistics().peak_requested_bytes;
  check(restores==account.statistics().successful_allocations,"window session restore escaped receiving account");
  check(restored.status().state==state && restored.window_state()==expected && rows(restored)==expected_rows && restored.progress()==progress,"complete window session state differs after restore");
  if(state==SessionState::running) {
    check(checkpoint->committed_sequence==2 && progress.sequence==5 && checkpoint->window->counts[0].id==1,"independent command/physical/count-ID fixture missing");
    const auto resident=original.statistics().current;
    for(std::size_t point=0;point<captures;++point) {
      bool failed=false;{s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{auto value=source->checkpoint_state();}catch(const std::bad_alloc&){failed=true;}}
      check(failed && original.statistics().current==resident && source->window_state()==expected,"window session capture OOM changed state");
    }
    for(std::size_t point=0;point<restores;++point) {
      bool failed=false;{s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{auto value=QuerySession::restore_state(compiler,*checkpoint);}catch(const std::bad_alloc&){failed=true;}}
      check(failed && original.statistics().current==resident && source->window_state()==expected,"window session restore OOM changed source");
    }
    SessionRestoreOptions exact;exact.memory_limit_bytes=restore_peak;
    {auto value=QuerySession::restore_state(compiler,*checkpoint,exact);check(value->window_state()==expected,"exact window-session query cap failed");}
    --*exact.memory_limit_bytes;bool failed=false;
    try{auto value=QuerySession::restore_state(compiler,*checkpoint,exact);}catch(const resource::MemoryFailure& error){failed=error.fault()==resource::MemoryFault::limit;}
    check(failed,"one-under window-session byte cap accepted");
    for(unsigned mutation=0;mutation<8;++mutation) {
      auto bad=source->checkpoint_state();
      if(mutation==0)++bad.committed_sequence;
      if(mutation==1)++std::get<io::QueueCheckpoint>(bad.source).progress.sequence;
      if(mutation==2)++bad.window->progress.physical_sequence;
      if(mutation==3)bad.input_kind=SessionInputKind::typed_physical;
      if(mutation==4)bad.version=2;
      if(mutation==5)bad.state=SessionState::dropped;
      if(mutation==6)++bad.queue_limits->events;
      if(mutation==7)bad.input_failed=true;
      rejected([&]{auto value=QuerySession::restore_state(compiler,bad);});
      check(source->window_state()==expected && rows(*source)==expected_rows,"malformed restore changed existing query");
    }
    {
      auto bad=source->checkpoint_state();const auto replacement=storage::AccountedRow::copy_of(original,Row{std::int64_t{999}});
      const auto id=bad.window->counts[0].id;bad.window->counts[0].values=replacement.clone(original);
      for(auto& label:bad.window->labels)if(label.count_id==id)label.values=replacement.clone(original);
      // This window is internally valid; only its join to the managed base
      // snapshot is wrong. A standalone import proves the distinction.
      auto local_account=resource::MemoryAccount::create(1024*1024);WindowController valid(local_account,compiler.source_catalog(),*bad.window);
      rejected([&]{auto value=QuerySession::restore_state(compiler,bad);});
    }
    {auto limits=SessionRestoreOptions{};limits.limits.matching_work=0;rejected([&]{auto value=QuerySession::restore_state(compiler,*checkpoint,limits);});}
    std::uint64_t minimum=0;
    for(std::uint64_t work=0;work<256;++work) {
      auto limits=SessionRestoreOptions{};limits.limits.matching_work=work;
      try{auto value=QuerySession::restore_state(compiler,*checkpoint,limits);minimum=work;break;}
      catch(const recovery::ImageFailure& error){check(error.fault()==recovery::ImageFault::work,"unexpected matching-work rejection");}
    }
    check(minimum>0 && minimum<256,"managed-row matching had no finite exact work boundary");
  }
  if(state!=SessionState::stopped) {
    source->start();restored.start();
    if(state==SessionState::created){seed(*source);seed(restored);}
    check(command(*source,{6,io::AdvanceWatermark{20},{}})==command(restored,{6,io::AdvanceWatermark{20},{}}),"restored full watermark deltas differ");
    check(source->window_state()==restored.window_state() && rows(*source)==rows(restored),"restored full watermark state differs");
    check(command(*source,insertion(7,4,TableId{0},3,20))==command(restored,insertion(7,4,TableId{0},3,20)),"restored window insertion differs");
    check(command(*source,{8,io::AdvanceWatermark{30},{}})==command(restored,{8,io::AdvanceWatermark{30},{}}),"restored later expiration differs");
  }else rejected([&]{restored.start();});
  std::cout<<"window-session indexed="<<indexed<<" fifo="<<static_cast<unsigned>(fifo)<<" control="<<static_cast<unsigned>(state)
      <<" capture/restore="<<captures<<'/'<<restores<<" passed\n";
}
void barriers(bool indexed) {
  const auto artifact=plan(indexed);auto source=QuerySession::create_windowed(artifact,config(WindowFifoPolicy::global));
  seed(*source);enqueue(*source,{6,io::AdvanceWatermark{20},{}});
  rejected([&]{auto value=source->checkpoint_state();});check(source->begin_next(),"watermark pending fixture missing");
  rejected([&]{auto value=source->checkpoint_state();});finish(*source);
  check(source->status().phase==SessionPhase::ready && source->window_state()->active_command.has_value(),"between-step watermark fixture missing");
  rejected([&]{auto value=source->checkpoint_state();});
  check(source->begin_next(),"watermark remainder missing");finish(*source);auto value=source->checkpoint_state();
  bool wrong_thread=false;std::thread other([&]{try{auto copy=source->checkpoint_state();}catch(const Error& error){wrong_thread=error.code()=="session_wrong_thread";}});other.join();
  check(wrong_thread,"checkpoint bypassed session writer guard");source->drop();rejected([&]{auto copy=source->checkpoint_state();});
  auto partial=QuerySession::create_windowed(artifact,config(WindowFifoPolicy::global));seed(*partial);
  enqueue(*partial,{6,io::AdvanceWatermark{20},{}});check(partial->begin_next(),"terminal partial watermark missing");finish(*partial);partial->stop();
  const auto before=partial->window_state();const auto progress=partial->progress();
  check(partial->status().state==SessionState::stopped && partial->status().committed_sequence==3 && progress.sequence==5 &&
      before->active_command.has_value(),"stopped partial watermark tombstone missing");
  {s04_alloc::Scope deny(0);rejected([&]{auto saved=partial->checkpoint_state();});
    check(s04_alloc::calls==0,"stopped active-watermark rejection allocated");}
  check(partial->window_state()==before && partial->progress()==progress,"stopped active-watermark rejection changed committed prefix");
  std::cout<<"window-session indexed="<<indexed<<" stopped partial watermark barrier passed\n";
}
void unmanaged_initialization(bool indexed) {
  const auto artifact=plan(indexed);const auto compiler=CompiledProgram::standalone(artifact);
  auto options=config(WindowFifoPolicy::global);options.managed_tables={TableId{0}};
  Database initial;initial.tables.resize(2);initial.tables[1].insert(Row{std::int64_t{9}});
  auto source=QuerySession::create_windowed(artifact,initial,options);auto saved=source->checkpoint_state();
  auto target=QuerySession::restore_state(compiler,saved);grant(*target,indexed);
  check(target->status().state==SessionState::created && target->status().committed_sequence==0 &&
      target->checkpoint_state().runtime_image.bytes==saved.runtime_image.bytes,"window restore changed unmanaged initial base rows");
  source->start();target->start();
  check(command(*source,insertion(1,1,TableId{0},3,0))==command(*target,insertion(1,1,TableId{0},3,0)) && rows(*target)==Relation{{Row{std::int64_t{3}}}},
      "unmanaged initialized window next insertion differs");
  check(command(*source,{2,io::AdvanceWatermark{10},{}})==command(*target,{2,io::AdvanceWatermark{10},{}}) && rows(*target).empty(),
      "unmanaged initialized window expiration differs");
  std::cout<<"window-session indexed="<<indexed<<" unmanaged initialized base rows preserved\n";
}
void lifetime_rejection(bool indexed,WindowFifoPolicy fifo) {
  auto source=QuerySession::create_windowed(plan(indexed),config(fifo));source->start();
  command(*source,insertion(1,1,TableId{0},1,0));
  command(*source,insertion(2,2,TableId{0},2,1));
  command(*source,insertion(3,3,TableId{0},1,2));
  const auto window=source->window_state();const auto visible=rows(*source);const auto progress=source->progress();
  const auto sequence=source->status().committed_sequence;
  enqueue(*source,{4,io::AdvanceWatermark{11},{}});
  for(unsigned retry=0;retry<2;++retry) {
    bool failed=false;try{static_cast<void>(source->begin_next());}
    catch(const Error& error){failed=error.code()==(retry==0?"window_fifo_violation":"input_failed");}
    check(failed && source->status().input_failed,"physical FIFO session rejection was not sticky");
    check(source->window_state()==window && rows(*source)==visible && source->progress()==progress &&
        source->status().committed_sequence==sequence,"physical FIFO session rejection acknowledged or published a command prefix");
  }
  std::cout<<"window-session indexed="<<indexed<<" policy="<<window_fifo_name(fifo)<<" physical watermark sticky rejection preserved source/rows/epoch\n";
}
}
int main() {
  try {
    for(const bool indexed:{false,true}) {
      for(const auto fifo:{WindowFifoPolicy::global,WindowFifoPolicy::per_relation,WindowFifoPolicy::physical_global,WindowFifoPolicy::physical_per_relation})
        for(const auto state:{SessionState::created,SessionState::running,SessionState::paused,SessionState::stopped})scenario(indexed,fifo,state);
      barriers(indexed);unmanaged_initialization(indexed);
      for(const auto fifo:{WindowFifoPolicy::physical_global,WindowFifoPolicy::physical_per_relation})lifetime_rejection(indexed,fifo);
    }
  }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
