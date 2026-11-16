#include "generation_fixture.hpp"
#include "generation_file_probe.hpp"
#include "journal_file_probe.hpp"
#include "checkpoint_file_probe.hpp"
#include "crown/api/error.hpp"
#include <cerrno>
#include <sys/wait.h>
using namespace crown;
using namespace crown::runtime;
using namespace crown::generation_test;
namespace {
enum class Action {enable,rotate,reopen};
struct Hook {
  std::uint64_t count=0,fail=0,crash=0;
  bool after=false,repeat=false,checkpoint_synced=false,journal_synced=false,order_violation=false,already_absent=false;
  bool deny_allocations=false,allocation_barrier=false;
  std::size_t allocations_at_root=0;
  std::size_t maximum=SIZE_MAX;
  void visit(bool done) noexcept {if(!done)++count;if(count==crash && done==after)::_exit(77);}
  template<class Decision> Decision decision(bool done) const noexcept {
    Decision result;if(!done){result.maximum_transfer=maximum;if(count==fail){if(after)result.error_after=EIO;else result.error_before=EIO;}}return result;
  }
  static recovery::testing::GenerationDecision generation(const recovery::testing::GenerationEvent& event,void* context) noexcept {
    auto& h=*static_cast<Hook*>(context);h.visit(event.after);
    // An after-success error cannot replace an unlink that already failed with
    // ENOENT. That boundary still proves the candidate is absent; it is not an
    // injected I/O failure. Before errors and both crash sides remain covered.
    if(event.after && h.after && h.count==h.fail && event.stage==recovery::GenerationStage::unlink_candidate && event.native_error==ENOENT)h.already_absent=true;
    if(event.after && event.result>=0 && event.native_error==0 && event.target==recovery::GenerationTarget::checkpoint && event.stage==recovery::GenerationStage::sync_directory)h.checkpoint_synced=true;
    if(!event.after && event.target==recovery::GenerationTarget::root && (event.stage==recovery::GenerationStage::rename_root || event.stage==recovery::GenerationStage::link_file)) {
      if(!h.checkpoint_synced || !h.journal_synced)h.order_violation=true;
      if(h.deny_allocations){h.allocation_barrier=true;h.allocations_at_root=s04_alloc::calls;s04_alloc::remaining=0;}
    }
    auto result=h.decision<recovery::testing::GenerationDecision>(event.after);if(!event.after && h.repeat && event.stage==recovery::GenerationStage::read_data)result.error_before=EINTR;return result;
  }
  static jp::testing::FileDecision journal(const jp::testing::FileEvent& event,void* context) noexcept {
    auto& h=*static_cast<Hook*>(context);h.visit(event.after);
    if(event.after && event.result>=0 && event.native_error==0 && event.stage==jp::FileStage::sync_directory)h.journal_synced=true;
    return h.decision<jp::testing::FileDecision>(event.after);
  }
  static recovery::testing::FileDecision checkpoint(const recovery::testing::FileEvent& event,void* context) noexcept {
    auto& h=*static_cast<Hook*>(context);h.visit(event.after);return h.decision<recovery::testing::FileDecision>(event.after);
  }
};
struct Installed {
  explicit Installed(Hook& hook){recovery::testing::set_generation_hook(Hook::generation,&hook);jp::testing::set_file_hook(Hook::journal,&hook);recovery::testing::set_file_hook(Hook::checkpoint,&hook);}
  ~Installed(){recovery::testing::set_generation_hook(nullptr,nullptr);jp::testing::set_file_hook(nullptr,nullptr);recovery::testing::set_file_hook(nullptr,nullptr);}
};
struct Saved {
  Fixture f;
  CompiledProgram program;
  std::string old_checkpoint,old_log,old_root;
  explicit Saved(Action action):f(false,1,action!=Action::enable),program(CompiledProgram::standalone(f.test.plan)) {
    if(action!=Action::enable){f.update(0);f.update(1);old_checkpoint=contents(path(f.name,1,".ckpt"));old_log=contents(path(f.name,1,".wal"));old_root=contents(f.name);}
    f.session.reset();
  }
  QuerySession::Owner owner(Action action) {
    if(action==Action::enable){auto value=QuerySession::create_typed(program);value->start();return value;}
    if(action==Action::rotate){auto value=QuerySession::restore_generation(program,f.name,recovery_options());value->discard_recovered_output();value->start();return value;}
    return {};
  }
  void perform(Action action,QuerySession::Owner& value) {
    if(action==Action::enable)value->enable_generation(f.name,options());
    else if(action==Action::rotate)value->rotate_generation();
    else value=QuerySession::restore_generation(program,f.name,recovery_options());
  }
  void verify(Action action) {
    if(action==Action::enable && !std::filesystem::exists(f.name))return;
    auto value=QuerySession::restore_generation(program,f.name,recovery_options());
    if(action==Action::enable){check(value->status().committed_sequence==0 && value->progress().sequence==0 && typed::rows(*value).empty(),"initial generation recovery exposed an epoch");return;}
    const auto selected=value->generation_state().selected;
    check((selected.generation==1 || selected.generation==2) && value->status().committed_sequence==2 && value->progress().sequence==2 &&
        typed::rows(*value)==Relation{{Row{std::int64_t{1},std::int64_t{2},std::int64_t{3}}}},"root fault recovered partial self-join/state/source");
    check(contents(path(f.name,1,".ckpt"))==old_checkpoint && contents(path(f.name,1,".wal"))==old_log,"generation fault changed historical pair");
    std::size_t rows=0;while(auto item=value->next_recovered_output()){
      check(selected.generation==1 && item->generation==1 && item->physical_sequence==2 && item->value.tuple.values()==Row{std::int64_t{1},std::int64_t{2},std::int64_t{3}},"old/new selected output identity differs");++rows;
    }
    check(rows==(selected.generation==1?1U:0U),"root fault lost/repeated reconstructed output");
    value->start();typed::enqueue(*value,io::InputEvent{f.test.updates[2],io::SourcePosition{"feed",30}});check(value->begin_next(),"root fault lost next update");static_cast<void>(typed::finish(*value));
    Database database;database.tables.resize(1);for(std::size_t i=0;i<3;++i)database.tables[0].insert(f.test.updates[i].values);
    check(value->progress().sequence==3 && typed::rows(*value)==typed::oracle(f.test,database),"root fault next update differs from oracle");
  }
};
Hook trace(Action action) {
  Saved saved(action);auto value=saved.owner(action);Hook hook;{Installed installed(hook);saved.perform(action,value);}
  check(!hook.order_violation,"root selected a pair before both files/names were synced");return hook;
}
void io_faults() {
  std::size_t cases=0,absent=0;
  for(const auto action:{Action::enable,Action::rotate,Action::reopen}) {
    const auto baseline=trace(action);
    for(std::uint64_t point=1;point<=baseline.count;++point)for(const bool after:{false,true}) {
      Saved saved(action);const auto before=descriptors();auto value=saved.owner(action);Hook hook;hook.fail=point;hook.after=after;bool failed=false;
      {Installed installed(hook);try{saved.perform(action,value);}catch(const recovery::GenerationFailure&){failed=true;}catch(const recovery::FileFailure&){failed=true;}catch(const jp::FileFailure&){failed=true;}}
      check(failed || (action==Action::rotate && hook.already_absent),"generation syscall error was ignored");
      if(value && value->generation_state().recovery_required){bool blocked=false;try{static_cast<void>(value->begin_next());}catch(const SessionJournalFailure&){blocked=true;}catch(const Error&){blocked=true;}check(blocked,"uncertain root owner admitted work");}
      value.reset();check(descriptors()==before,"generation syscall error leaked a descriptor");saved.verify(action);if(failed)++cases;else ++absent;
    }
    Saved short_io(action);auto value=short_io.owner(action);Hook small;small.maximum=3;{Installed installed(small);short_io.perform(action,value);}value.reset();short_io.verify(action);
    std::cout<<"generation I/O action="<<static_cast<unsigned>(action)<<" actual boundaries="<<baseline.count<<" both-side errors/short transfers/native reopen passed\n";
  }
  Saved interrupted(Action::reopen);auto limits=recovery_options();limits.root.operations=30;Hook hook;hook.repeat=true;bool bounded=false;const auto before=descriptors();
  {Installed installed(hook);try{auto value=QuerySession::restore_generation(interrupted.program,interrupted.f.name,limits);}catch(const recovery::GenerationFailure& e){bounded=e.fault()==recovery::GenerationFault::limit;}}
  check(bounded && descriptors()==before && contents(interrupted.f.name)==interrupted.old_root,"root interruption escaped cumulative I/O quota");
  std::cout<<"generation actual syscall failures="<<cases<<" already-absent candidate after-boundaries="<<absent<<" publication order/native old-new recovery and finite interruption passed\n";
}
void crashes() {
  std::size_t cases=0;
  for(const auto action:{Action::enable,Action::rotate,Action::reopen}) {
    const auto baseline=trace(action);
    for(std::uint64_t point=1;point<=baseline.count;++point)for(const bool after:{false,true}) {
      Saved saved(action);const auto child=::fork();check(child>=0,"generation fork failed");
      if(child==0){auto value=saved.owner(action);Hook hook;hook.crash=point;hook.after=after;Installed installed(hook);try{saved.perform(action,value);}catch(...){::_exit(3);}::_exit(4);}
      int status=0;check(::waitpid(child,&status,0)==child && WIFEXITED(status) && WEXITSTATUS(status)==77,"generation process crash boundary missed");
      saved.verify(action);++cases;
    }
  }
  std::cout<<"generation process exits="<<cases<<" every actual boundary/native state/source/output/next update passed (not power loss)\n";
}
void allocations() {
  Saved saved(Action::reopen);std::size_t allocations=0;std::uint64_t peak=0;
  {std::optional<QuerySession::Owner> value;{s04_alloc::Scope count;value.emplace(QuerySession::restore_generation(saved.program,saved.f.name,recovery_options()));allocations=s04_alloc::calls;}
    const auto account=value->get_deleter().account();check(allocations==account.statistics().successful_allocations,"generation recovery C++ new/account counts differ");peak=account.statistics().peak_requested_bytes;}
  for(std::size_t point=0;point<allocations;++point) {
    const auto before=descriptors();bool failed=false;{s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));try{auto value=QuerySession::restore_generation(saved.program,saved.f.name,recovery_options());}catch(const std::bad_alloc&){failed=true;}}
    check(failed && descriptors()==before && contents(saved.f.name)==saved.old_root && contents(path(saved.f.name,1,".wal"))==saved.old_log,"generation allocation fault leaked/changed prefix");
  }
  auto exact=recovery_options();exact.replay.memory_limit_bytes=peak;{auto value=QuerySession::restore_generation(saved.program,saved.f.name,exact);}
  --*exact.replay.memory_limit_bytes;bool under=false;try{auto value=QuerySession::restore_generation(saved.program,saved.f.name,exact);}catch(const resource::MemoryFailure& e){under=e.fault()==resource::MemoryFault::limit;}
  check(under,"one-under generation receiving peak accepted");
  std::cout<<"generation receiving allocations="<<allocations<<" every fault/exact-under cap/account/descriptor cleanup passed\n";
  for(const auto action:{Action::enable,Action::rotate}) {
    Saved barrier(action);auto value=barrier.owner(action);Hook hook;hook.deny_allocations=true;
    {Installed installed(hook);s04_alloc::Scope count;barrier.perform(action,value);}
    check(hook.allocation_barrier && !s04_alloc::triggered && s04_alloc::calls==hook.allocations_at_root && !hook.order_violation,"generation completion attempted C++ new after root selection syscall");
  }
  std::cout<<"generation root selection completion made no intercepted C++ new attempts for initial/rotation\n";
}
}
int main(int argc,char** argv){try{check(argc==2,"expected generation test mode");if(std::string_view(argv[1])=="crash")crashes();else{allocations();io_faults();}}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
