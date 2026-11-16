#include "session_file_fixture.hpp"
#include <sys/stat.h>

using namespace crown;
using namespace crown::runtime;
using namespace crown::session_file_test;
namespace {
void typed_case(bool indexed,unsigned kind,SessionState control) {
  Directory directory;const auto path=directory.file();const auto test=typed::fixture(indexed,kind);
  const auto compiler=CompiledProgram::standalone(test.plan);SessionOptions options;options.delta.mode=kind==2?DeltaMode::maintenance:DeltaMode::delta;
  auto source=QuerySession::create_typed(test.plan,{},options);const auto account=source.get_deleter().account();Database database;database.tables.resize(test.plan.source_catalog().tables.size());
  if(control!=SessionState::created) {
    source->start();typed::step(*source,test,database,test.updates[0],options.delta.mode);typed::step(*source,test,database,test.updates[1],options.delta.mode);
    if(control==SessionState::paused){source->pause();}if(control==SessionState::stopped){source->stop();}
  }
  const auto expected=typed::rows(*source);const auto progress=source->progress();const auto before=account.statistics();std::size_t saves=0,loads=0;
  {s04_alloc::Scope count;const auto saved=source->checkpoint_file(path);saves=s04_alloc::calls;
    check(saved.publication==recovery::PublicationState::durable && saved.manifest.committed_sequence==source->status().committed_sequence,"file publication lost durable manifest");}
  check(saves==account.statistics().successful_allocations-before.successful_allocations,"file save escaped original account");
  std::optional<QuerySession::Owner> target;{s04_alloc::Scope count;target=QuerySession::restore_file(compiler,path);loads=s04_alloc::calls;}
  typed::grant(**target,indexed);const auto receiving=target->get_deleter().account();const auto peak=receiving.statistics().peak_requested_bytes;
  check(loads==receiving.statistics().successful_allocations,"file load escaped receiving account");
  check((**target).status().state==control && (**target).progress()==progress && typed::rows(**target)==expected,"file session round trip differs");
  const auto resident=account.statistics().current;
  for(unsigned i=0;i<4;++i){const auto saved=source->checkpoint_file(path);static_cast<void>(saved);}
  check(account.statistics().current==resident && temporaries(directory)==0,"file saving leaked resident storage or temporary entries");
  if(kind==1 && control==SessionState::running) {
    Pair old(indexed);static_cast<void>(recovery::publish_session_image(path,old.old_image));const auto prior=contents(path);
    for(std::size_t point=0;point<saves;++point) {
      bool failed=false;{s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{static_cast<void>(source->checkpoint_file(path));}catch(const std::bad_alloc&){failed=true;}}
      check(failed && contents(path)==prior && account.statistics().current==resident && typed::rows(*source)==expected,"file save OOM changed publication/source");
    }
    static_cast<void>(source->checkpoint_file(path));
    for(std::size_t point=0;point<loads;++point) {
      const auto fds=descriptors();bool failed=false;
      {s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{auto value=QuerySession::restore_file(compiler,path);}catch(const std::bad_alloc&){failed=true;}}
      check(failed && descriptors()==fds && typed::rows(*source)==expected,"file restore OOM leaked descriptors or changed source");
    }
    SessionRestoreOptions exact;exact.memory_limit_bytes=peak;
    {auto value=QuerySession::restore_file(compiler,path,exact);check(value.get_deleter().account().statistics().peak_requested_bytes==peak,"exact file-load cap failed");}
    --*exact.memory_limit_bytes;bool limited=false;try{auto value=QuerySession::restore_file(compiler,path,exact);}catch(const resource::MemoryFailure& error){limited=error.fault()==resource::MemoryFault::limit;}
    check(limited,"one-under file-load cap accepted");
  }
  if(control!=SessionState::stopped) {
    source->start();(**target).start();auto other=database;
    for(std::size_t i=control==SessionState::created?std::size_t{0}:std::size_t{2};i<test.updates.size();++i)
      check(typed::step(*source,test,database,test.updates[i],options.delta.mode)==typed::step(**target,test,other,test.updates[i],options.delta.mode),"file next-update behavior differs");
  }
  std::cout<<"file typed indexed="<<indexed<<" query="<<kind<<" control="<<static_cast<unsigned>(control)<<" capture/restore="<<saves<<'/'<<loads<<" passed\n";
}
void windows_and_stream(bool indexed) {
  Directory directory;const auto path=directory.file();const auto plan=window::plan(indexed);const auto compiler=CompiledProgram::standalone(plan);
  for(const auto fifo:{WindowFifoPolicy::global,WindowFifoPolicy::per_relation}) {
    auto source=QuerySession::create_windowed(plan,window::config(fifo));window::seed(*source);static_cast<void>(source->checkpoint_file(path));
    const auto expected=source->window_state();source.reset();auto target=QuerySession::restore_file(compiler,path);typed::grant(*target,indexed);
    check(target->window_state()==expected && target->progress().sequence==5 && target->status().committed_sequence==2,"file window independent sequences differ");
    const auto delta=window::command(*target,{6,io::AdvanceWatermark{20},{}});
    check(delta==typed::Output{{SetOperation::erase,Row{std::int64_t{1}}}} && typed::rows(*target).empty(),"file restored watermark differs");
  }
  const auto test=typed::fixture(indexed,1);const auto program=CompiledProgram::standalone(test.plan);SessionOptions options;
  options.input.format=io::InputFormat::csv;options.input.table=TableId{0};options.input.source="csv";options.input.delimiter=';';options.input.byte_offset=123;
  auto source=QuerySession::create(test.plan,std::make_unique<std::istringstream>("y;x\n2;1\n3;2\n"),options);
  source->start();check(source->begin_next(),"file CSV fixture missing");typed::finish(*source);source->pause();const auto progress=source->progress();
  static_cast<void>(source->checkpoint_file(path));source.reset();auto target=QuerySession::restore_file(program,path,std::make_unique<std::istringstream>("3;2\n"));typed::grant(*target,indexed);
  check(target->progress()==progress && target->status().state==SessionState::paused,"file stream origin/control lost");target->start();check(target->begin_next(),"file stream continuation missing");typed::finish(*target);
  check(typed::rows(*target)==Relation{{Row{std::int64_t{1},std::int64_t{2},std::int64_t{3}}}},"file CSV permutation/self-join continuation differs");
  std::cout<<"file indexed="<<indexed<<" window/source-closed/CSV continuation passed\n";
}
void rejected_files() {
  Directory directory;const auto path=directory.file();const auto test=typed::fixture(false,0);const auto program=CompiledProgram::standalone(test.plan);
  auto source=QuerySession::create_typed(test.plan);static_cast<void>(source->checkpoint_file(path));const auto valid=contents(path);
  for(const std::size_t size:{std::size_t{0},std::size_t{20},valid.size()-1}) {
    {std::ofstream output(path,std::ios::binary|std::ios::trunc);output.write(valid.data(),static_cast<std::streamsize>(size));}
    bool failed=false;try{auto value=QuerySession::restore_file(program,path);}catch(const recovery::FileFailure&){failed=true;}catch(const recovery::ImageFailure&){failed=true;}
    check(failed,"truncated checkpoint file accepted");
  }
  {std::ofstream output(path,std::ios::binary|std::ios::trunc);auto bad=valid;bad.back()^=1;output.write(bad.data(),static_cast<std::streamsize>(bad.size()));}
  bool corrupt=false;try{auto value=QuerySession::restore_file(program,path);}catch(const recovery::ImageFailure&){corrupt=true;}check(corrupt,"corrupt checkpoint file accepted");
  static_cast<void>(source->checkpoint_file(path));const auto link=directory.file("link");check(::symlink("state.crown",link.c_str())==0,"symlink fixture failed");
  bool symlink=false;try{auto value=QuerySession::restore_file(program,link);}catch(const recovery::FileFailure&){symlink=true;}check(symlink,"file loader followed symlink");
  const auto fifo=directory.file("fifo");check(::mkfifo(fifo.c_str(),0600)==0,"FIFO fixture failed");bool special=false;
  try{auto value=QuerySession::restore_file(program,fifo);}catch(const recovery::FileFailure& error){special=error.fault()==recovery::FileFault::not_regular;}check(special,"file loader accepted special file");
  for(const auto& bad:{std::string{},std::string("bad\0path",8),directory.name+"/",std::string(4096,'x')}) {
    bool rejected=false;try{static_cast<void>(source->checkpoint_file(bad));}catch(const recovery::FileFailure&){rejected=true;}check(rejected,"invalid checkpoint path accepted");
  }
  check(contents(path)==valid && temporaries(directory)==0,"rejected file operation changed previous artifact");
  std::cout<<"file corruption/truncation/path/symlink/special-file rejection passed\n";
}
}
int main() {
  try {
    rejected_files();for(const bool indexed:{false,true}) {
      for(unsigned kind=0;kind<6;++kind)for(const auto state:{SessionState::created,SessionState::running,SessionState::paused,SessionState::stopped})typed_case(indexed,kind,state);
      windows_and_stream(indexed);
    }
  }catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
