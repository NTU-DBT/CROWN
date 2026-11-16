#include "local_sink_fixture.hpp"
#include "local_sink_probe.hpp"
#include <cerrno>
#include <sys/wait.h>
using namespace crown;
using namespace crown::runtime;
using namespace crown::local_sink_test;
namespace {
enum class Action {create,deliver,open,read,repair};
struct Hook {
  std::uint64_t count=0,fail=0,crash=0;
  bool after=false,repeat=false,deny_after_sync=false,barrier=false;
  std::size_t maximum=SIZE_MAX,allocations_at_sync=0;
  static sk::testing::Decision call(const sk::testing::Event& event,void* context) noexcept {
    auto& h=*static_cast<Hook*>(context);if(!event.after)++h.count;
    if(h.count==h.crash && event.after==h.after)::_exit(77);
    if(h.deny_after_sync && event.after && event.stage==sk::Stage::sync_file && event.result>=0 && event.native_error==0){h.barrier=true;h.allocations_at_sync=s04_alloc::calls;s04_alloc::remaining=0;}
    sk::testing::Decision result;
    if(!event.after){result.maximum_transfer=h.maximum;if(h.repeat && event.stage==sk::Stage::read_data)result.error_before=EINTR;if(h.count==h.fail){if(h.after)result.error_after=EIO;else result.error_before=EIO;}}
    return result;
  }
};
struct Installed {explicit Installed(Hook& hook){sk::testing::set_hook(Hook::call,&hook);}~Installed(){sk::testing::set_hook(nullptr,nullptr);}};
struct Saved {
  generation_test::Fixture f;
  CompiledProgram program;
  std::string path,bytes;
  sk::Header header;
  explicit Saved(Action action):f(false,1),program(CompiledProgram::standalone(f.test.plan)),path(f.directory.file("output.sink")) {
    if(action!=Action::create) {
      f.session->create_local_sink(path,options());
      commit(0);static_cast<void>(f.session->deliver_local_epoch());commit(1);
      if(action!=Action::deliver)static_cast<void>(f.session->deliver_local_epoch());
      header=f.session->local_sink_state().persisted.header;
    }
    f.session.reset();
    if(action==Action::repair){auto data=contents(path);data.pop_back();generation_test::put(path,data);}
    bytes=contents(path);
  }
  void commit(std::size_t index) {typed::enqueue(*f.session,io::InputEvent{f.test.updates[index],io::SourcePosition{"feed",f.test.updates[index].sequence*10}});check(f.session->begin_next(),"sink fault source missing");finish(*f.session);}
  QuerySession::Owner owner(Action action) {
    auto value=QuerySession::restore_generation(program,f.name,generation_test::recovery_options());
    if(action==Action::deliver || action==Action::read) {
      value->open_local_sink(path,options());static_cast<void>(value->deliver_local_epoch());if(action==Action::read)static_cast<void>(value->deliver_local_epoch());
    }
    return value;
  }
  void perform(Action action,QuerySession& value) {
    if(action==Action::create)value.create_local_sink(path,options());
    else if(action==Action::deliver)static_cast<void>(value.deliver_local_epoch());
    else if(action==Action::read)static_cast<void>(value.read_local_epoch(2));
    else value.open_local_sink(path,options());
  }
  void verify(Action action) {
    auto value=QuerySession::restore_generation(program,f.name,generation_test::recovery_options());
    if(action==Action::create) {
      if(std::filesystem::exists(path))value->open_local_sink(path,options());else value->create_local_sink(path,options());
      check(value->local_sink_receipt().sequence()==0 && value->status().committed_sequence==0,"sink creation exposed an input/output epoch");return;
    }
    value->open_local_sink(path,options());for(std::uint64_t sequence=1;sequence<=2;++sequence)check(value->deliver_local_epoch().sequence==sequence,"sink restart lost replay epoch");
    check(value->local_sink_receipt().sequence()==2 && value->progress().sequence==2 && value->status().committed_sequence==2 && output(value->read_local_epoch(2))==typed::Output{{SetOperation::insert,Row{std::int64_t{1},std::int64_t{2},std::int64_t{3}}}},"sink error/crash recovered partial state/source/output");
    value->start();typed::enqueue(*value,io::InputEvent{f.test.updates[2],io::SourcePosition{"feed",30}});check(value->begin_next(),"sink restart next input missing");finish(*value);static_cast<void>(value->deliver_local_epoch());
    Database database;database.tables.resize(1);for(std::size_t i=0;i<3;++i)database.tables[0].insert(f.test.updates[i].values);
    check(value->local_sink_receipt().sequence()==3 && typed::rows(*value)==typed::oracle(f.test,database) && output(value->read_local_epoch(3)).size()==3,"sink restart next self-join epoch differs");
  }
};
Hook trace(Action action) {Saved saved(action);auto value=saved.owner(action);Hook hook;{Installed installed(hook);saved.perform(action,*value);}return hook;}
void failures() {
  std::size_t cases=0;
  for(const auto action:{Action::create,Action::deliver,Action::open,Action::read,Action::repair}) {
    const auto baseline=trace(action);
    for(std::uint64_t point=1;point<=baseline.count;++point)for(const bool after:{false,true}) {
      Saved saved(action);const auto before=descriptors();auto value=saved.owner(action);Hook hook;hook.fail=point;hook.after=after;bool failed=false;
      {Installed installed(hook);try{saved.perform(action,*value);}catch(const sk::Failure&){failed=true;}}
      check(failed,"sink syscall error ignored");
      check(value->status().committed_sequence==(action==Action::create?0U:2U) && value->local_sink_state().recovery_required,"sink error lost committed state or allowed uncertain continuation");
      value.reset();check(descriptors()==before,"sink syscall error leaked descriptor/lock");saved.verify(action);++cases;
    }
    Saved shortened(action);auto value=shortened.owner(action);Hook short_io;short_io.maximum=3;{Installed installed(short_io);shortened.perform(action,*value);}value.reset();shortened.verify(action);
    std::cout<<"local sink I/O action="<<static_cast<unsigned>(action)<<" actual boundaries="<<baseline.count<<" before/after errors/short I/O/native recovery passed\n";
  }
  Saved saved(Action::open);auto value=saved.owner(Action::open);auto limits=options();limits.file.operations=30;Hook h;h.repeat=true;bool bounded=false;
  {Installed installed(h);try{value->open_local_sink(saved.path,limits);}catch(const sk::Failure& e){bounded=e.fault()==sk::Fault::limit;}}
  check(bounded && contents(saved.path)==saved.bytes,"sink repeated interruption bypassed finite I/O limit");
  std::cout<<"local sink actual syscall errors="<<cases<<" native state/output/next update and interruption quota passed\n";
}
void crashes() {
  std::size_t cases=0;
  for(const auto action:{Action::create,Action::deliver,Action::open,Action::read,Action::repair}) {
    const auto baseline=trace(action);
    for(std::uint64_t point=1;point<=baseline.count;++point)for(const bool after:{false,true}) {
      Saved saved(action);const auto child=::fork();check(child>=0,"sink crash fork failed");
      if(child==0){auto value=saved.owner(action);Hook hook;hook.crash=point;hook.after=after;Installed installed(hook);try{saved.perform(action,*value);}catch(...){::_exit(3);}::_exit(4);}
      int status=0;check(::waitpid(child,&status,0)==child && WIFEXITED(status) && WEXITSTATUS(status)==77,"sink process crash boundary missed");saved.verify(action);++cases;
    }
  }
  std::cout<<"local sink process exits="<<cases<<" every boundary/native state/source/output/dedup/next update passed (not power loss)\n";
}
void allocations() {
  Saved saved(Action::deliver);auto value=saved.owner(Action::deliver);std::size_t count=0;
  {s04_alloc::Scope scope;static_cast<void>(value->deliver_local_epoch());count=s04_alloc::calls;}value.reset();
  for(std::size_t point=0;point<count;++point) {
    Saved item(Action::deliver);const auto before=descriptors();auto owner=item.owner(Action::deliver);const auto old=contents(item.path);bool failed=false;
    {s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{static_cast<void>(owner->deliver_local_epoch());}catch(const std::bad_alloc&){failed=true;}}
    check(failed && contents(item.path)==old && owner->status().output_remaining==1 && owner->local_sink_state().verified_sequence==1,"sink OOM removed output or published partial epoch");
    static_cast<void>(owner->deliver_local_epoch());owner.reset();check(descriptors()==before,"sink OOM leaked file ownership");item.verify(Action::deliver);
  }
  Saved barrier(Action::deliver);auto owner=barrier.owner(Action::deliver);Hook hook;hook.deny_after_sync=true;
  {Installed installed(hook);s04_alloc::Scope scope;static_cast<void>(owner->deliver_local_epoch());}
  check(hook.barrier && !s04_alloc::triggered && s04_alloc::calls==hook.allocations_at_sync,"sink acknowledgment allocated after durable sync");
  std::cout<<"local sink delivery allocations="<<count<<" every fault/output retention/retry and post-sync allocation-free acknowledgment passed\n";
}
}
int main(int argc,char** argv){try{check(argc==2,"expected sink fault mode");if(std::string_view(argv[1])=="crash")crashes();else{allocations();failures();}}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
