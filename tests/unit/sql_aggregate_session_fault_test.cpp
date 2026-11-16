#include "sql_aggregate_session_probe.hpp"
#include <iostream>
#include <sys/wait.h>

namespace {
using namespace crown;
using namespace crown::sql_aggregate_session_test;
enum class Mode {create,log,commit,reject,deliver,checkpoint,recover};
const std::array<Cell,2> row{Cell{},number(5)};
void log(ar::Session& s,bool reject=false) {
  const std::array edit{runtime::sql_rows::SourceReplacement{TableId{0},row,reject?9U:0U,1}};
  s.log({1,edit,ar::SourcePosition{"feed",10},ar::ReaderPosition{10,1}});
}
// Reset only this fixture's disposable namespace after all owners release locks.
void prepare(Fixture& f,Mode mode,std::optional<ar::Session>& owner) {
  owner.reset();for(const auto& entry:std::filesystem::directory_iterator(f.directory.name))std::filesystem::remove_all(entry.path());
  if(mode==Mode::create)return;
  owner.emplace(f.create());if(mode==Mode::log)return;
  log(*owner,mode==Mode::reject);if(mode==Mode::commit || mode==Mode::reject)return;
  assert(!owner->decide().rejected);if(mode==Mode::deliver)return;
  assert(owner->deliver());if(mode==Mode::checkpoint)return;
  owner.reset();const auto wal=generation_file(f,1);put(wal,contents(wal)+"C");put(f.sink,contents(f.sink)+"C");
}
using Namespace=std::vector<std::pair<std::string,std::string>>;
// Capture bytes only after a genuine baseline owner closes. Restoring a
// disposable fixture is followed by actual recovery before the target action;
// recorded bytes are not used as a native state/receipt shortcut.
Namespace capture(const Fixture& f) {
  Namespace result;for(const auto& entry:std::filesystem::directory_iterator(f.directory.name))result.emplace_back(entry.path().string(),contents(entry.path().string()));return result;
}
void restore(Fixture& f,const Namespace& image,Mode mode,std::optional<ar::Session>& owner) {
  owner.reset();for(const auto& entry:std::filesystem::directory_iterator(f.directory.name))std::filesystem::remove_all(entry.path());
  for(const auto& [path,bytes]:image)put(path,bytes);
  if(mode!=Mode::create && mode!=Mode::recover)owner.emplace(f.recover());
}
void perform(Fixture& f,Mode mode,std::optional<ar::Session>& owner) {
  switch(mode) {
    case Mode::create:owner.emplace(f.create());break;
    case Mode::recover:owner.emplace(f.recover());break;
    case Mode::log:log(*owner);break;
    case Mode::commit:assert(!owner->decide().rejected);break;
    case Mode::reject:assert(owner->decide().rejected==ar::RejectReason::weight_mismatch);break;
    case Mode::deliver:assert(owner->deliver());break;
    case Mode::checkpoint:assert(owner->checkpoint().generation==2);break;
  }
}
// Reopen the authoritative files after releasing the failed owner. Complete
// surviving decisions are replayed; an undecided Input remains the same head.
void surviving(Fixture& f,Mode mode) {
  if(!std::filesystem::exists(f.root)) {assert(mode==Mode::create);return;}
  auto s=f.recover();const auto before=s.state();
  assert(before.logged<=1 && before.disposed<=before.logged && before.committed<=before.disposed && before.delivered<=before.committed);
  if(mode==Mode::checkpoint || mode==Mode::recover)assert(before.committed==1 && before.delivered==1);
  if(before.pending)assert(s.decide().rejected.has_value()==(mode==Mode::reject));
  if(s.output())assert(s.deliver());
  const auto after=s.state();assert(after.logged==after.disposed && after.delivered==after.committed);
  assert(s.source_weight(TableId{0},row)==(after.committed?1U:0U));
  if(after.disposed)assert(s.progress().source_positions.at("feed")==10 && s.reader_position()==(ar::ReaderPosition{10,1}));
}
// Inject before every observed call and after supported successful effects;
// acquisition-after EIO is normalized before acquisition. Every durability
// boundary gets a real child exit in the same filesystem, not a power-loss test.
void io_matrix() {
  Fixture f;std::optional<ar::Session> owner;const auto baseline=f.account.statistics().current.allocations;
  const auto baseline_fds=sql_aggregate_file_test::descriptors();
  std::size_t faults=0,cuts=0;
  for(const auto mode:{Mode::create,Mode::log,Mode::commit,Mode::reject,Mode::deliver,Mode::checkpoint,Mode::recover}) {
    prepare(f,mode,owner);owner.reset();const auto image=capture(f);restore(f,image,mode,owner);
    Hook trace;{Installed installed(trace);perform(f,mode,owner);}owner.reset();
    for(std::size_t i=0;i<trace.size;++i) {
      const auto event=trace.events[i];if(event.after && event.result<0)continue;
      restore(f,image,mode,owner);Hook hook;hook.fail=event.point;hook.after=event.after;bool failed=false;
      {Installed installed(hook);try {perform(f,mode,owner);}catch(const ar::FileFailure&){failed=true;}catch(const recovery::GenerationFailure&){failed=true;}}
      assert(failed);
      if(owner && (mode==Mode::log || mode==Mode::commit || mode==Mode::reject || mode==Mode::deliver)) {
        assert(owner->requires_reopen());refused([&]{static_cast<void>(owner->state());});
        refused([&]{static_cast<void>(owner->progress());});refused([&]{static_cast<void>(owner->output());});
      }
      owner.reset();assert(f.account.statistics().current.allocations==baseline);
      // Factories can acquire descriptors during perform; all are released now.
      assert(sql_aggregate_file_test::descriptors()==baseline_fds);surviving(f,mode);++faults;
    }
    for(std::size_t i=0;i<trace.size;++i) {
      const auto event=trace.events[i];if(!durability(event))continue;
      restore(f,image,Mode::recover,owner);
      const auto child=::fork();assert(child>=0);
      if(child==0) {
        // Recreate the live owner in the child, before installing the cut.
        if(mode!=Mode::create && mode!=Mode::recover)owner.emplace(f.recover());
        Hook hook;hook.crash=event.point;hook.after=event.after;Installed installed(hook);perform(f,mode,owner);::_exit(1);
      }
      int status=0;assert(::waitpid(child,&status,0)==child && WIFEXITED(status) && WEXITSTATUS(status)==77);
      surviving(f,mode);assert(f.account.statistics().current.allocations==baseline);++cuts;
    }
  }
  std::cout<<"R2 session syscall faults="<<faults<<", real process cuts="<<cuts<<'\n'<<std::flush;
}
// From the first append stamp through confirmed native/progress publication,
// no covered C++ allocation is permitted. The same holds for sink acknowledgement.
void prepaid_publication() {
  Fixture f;std::optional<ar::Session> owner;
  for(const auto mode:{Mode::log,Mode::commit,Mode::reject,Mode::deliver}) {
    prepare(f,mode,owner);Hook hook;hook.deny=1;
    {Installed installed(hook);s04_alloc::Scope allocations;perform(f,mode,owner);assert(hook.armed && !s04_alloc::triggered && s04_alloc::calls==0);}
    assert(!owner->requires_reopen());const auto s=owner->state();
    if(mode==Mode::log)assert(s.pending && s.logged==1 && s.disposed==0);
    if(mode==Mode::commit)assert(s.committed==1 && s.output_pending);
    if(mode==Mode::reject)assert(s.disposed==1 && s.committed==0 && !s.pending);
    if(mode==Mode::deliver)assert(s.delivered==1 && !s.output_pending);
  }
  prepare(f,Mode::checkpoint,owner);Hook trace;{Installed installed(trace);perform(f,Mode::checkpoint,owner);}owner.reset();
  std::uint64_t selected=0;
  for(std::size_t i=0;i<trace.size;++i) {
    const auto event=trace.events[i];if(event.generation && event.after && event.target==recovery::GenerationTarget::root &&
        event.root==recovery::GenerationStage::sync_directory)selected=event.point;
  }
  assert(selected>0);prepare(f,Mode::checkpoint,owner);Hook hook;hook.deny=selected;
  {Installed installed(hook);s04_alloc::Scope allocations;perform(f,Mode::checkpoint,owner);assert(hook.armed && !s04_alloc::triggered && s04_alloc::calls==0);}
  assert(!owner->requires_reopen() && owner->selected_root().generation==2);
}
// Each covered allocation in live preparation/log funding and cold recovery can
// fail independently. Live cuts retry the same healthy owner, exercising actual
// undo. Cold cuts preserve the same files/account and need only one final healthy
// reopen. Covered new attempts remain separate from receiving-account bytes.
void allocation_cuts() {
  Fixture f;std::optional<ar::Session> owner;std::size_t cuts=0;
  for(const auto mode:{Mode::log,Mode::commit,Mode::reject,Mode::recover}) {
    prepare(f,mode,owner);owner.reset();const auto image=capture(f);restore(f,image,mode,owner);std::size_t attempts=0;
    {s04_alloc::Scope count;perform(f,mode,owner);attempts=s04_alloc::calls;}
    owner.reset();const auto baseline=f.account.statistics().current.allocations;
    restore(f,image,mode,owner);const auto wal=generation_file(f,1),prior=contents(wal),sink=contents(f.sink);owner.reset();
    for(std::size_t point=0;point<attempts;++point) {
      if(mode!=Mode::recover)restore(f,image,mode,owner);
      bool failed=false;
      {s04_alloc::Scope deny(static_cast<std::ptrdiff_t>(point));try {perform(f,mode,owner);}catch(const std::bad_alloc&){failed=true;}}
      assert(failed && contents(wal)==prior && contents(f.sink)==sink);
      if(owner) {
        assert(!owner->requires_reopen());const auto state=owner->state();assert(state.committed==0 && state.disposed==0);
        assert(owner->source_weight(TableId{0},row)==0 && owner->snapshot().groups.empty() && owner->progress().source_positions.empty());
        perform(f,mode,owner);if(mode==Mode::log)assert(!owner->decide().rejected);
        if(owner->output())assert(owner->deliver());
        assert(owner->state().disposed==1 && owner->state().committed==(mode==Mode::reject?0U:1U));
      }
      owner.reset();assert(f.account.statistics().current.allocations==baseline);++cuts;
    }
    surviving(f,mode);
  }
  std::cout<<"R2 session covered allocation cuts="<<cuts<<'\n'<<std::flush;
}
// Root-validation failures invalidate the owner; failure deleting/syncing only
// the unselected next candidates leaves the selected generation usable/retryable.
void root_retry_boundaries() {
  Fixture f;std::optional<ar::Session> owner;prepare(f,Mode::checkpoint,owner);Hook trace;
  {Installed installed(trace);perform(f,Mode::checkpoint,owner);}owner.reset();
  bool unlink=false,sync=false,validation=false;
  for(std::size_t i=0;i<trace.size;++i) {
    const auto event=trace.events[i];if(!event.generation || event.after)continue;
    const bool candidate=event.root==recovery::GenerationStage::unlink_candidate;
    const bool candidate_sync=event.root==recovery::GenerationStage::sync_directory && !sync;
    const bool root_read=event.root==recovery::GenerationStage::read_data && !validation;
    if(!candidate && !candidate_sync && !root_read)continue;
    prepare(f,Mode::checkpoint,owner);Hook hook;hook.fail=event.point;
    {Installed installed(hook);refused([&]{perform(f,Mode::checkpoint,owner);});}
    if(root_read) {validation=true;assert(owner->requires_reopen());}
    else {assert(!owner->requires_reopen() && owner->selected_root().generation==1);assert(owner->checkpoint().generation==2);if(candidate)unlink=true;else sync=true;}
  }
  assert(unlink && sync && validation);
}
} // namespace
int main() {io_matrix();prepaid_publication();allocation_cuts();root_retry_boundaries();}
