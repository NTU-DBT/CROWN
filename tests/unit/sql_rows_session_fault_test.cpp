#include "sql_rows_session_fixture.hpp"
#include "sql_aggregate_session_probe.hpp"
#include <iostream>
#include <sys/wait.h>

namespace {
using namespace crown;
using namespace crown::sql_rows_session_test;
namespace probe = crown::sql_aggregate_session_test;
enum class Mode { log, commit, deliver, checkpoint, recover };
const std::array<Cell,1> cells{Cell{}};

void log_row(sr::Session& session) {
  const std::array edits{runtime::sql_rows::SourceReplacement{TableId{0},cells,0,2}};
  session.log({1,edits,sr::SourcePosition{"feed",10},sr::ReaderPosition{10,1}});
}

// Each action starts from a genuine closed root. Namespace copies below are
// disposable test fixtures and never substitute for public native recovery.
void prepare(Fixture& fixture,Mode mode) {
  auto owner=fixture.create();
  if(mode==Mode::log)return;
  log_row(owner);if(mode==Mode::commit)return;
  assert(!owner.decide().rejected);if(mode==Mode::deliver)return;
  assert(owner.deliver());
}
using Namespace=std::vector<std::pair<std::string,std::string>>;
Namespace capture(const Fixture& fixture) {
  Namespace result;
  for(const auto& entry:std::filesystem::directory_iterator(fixture.directory.name))
    result.emplace_back(entry.path().string(),contents(entry.path().string()));
  return result;
}
void restore(Fixture& fixture,const Namespace& image) {
  for(const auto& entry:std::filesystem::directory_iterator(fixture.directory.name))
    std::filesystem::remove_all(entry.path());
  for(const auto& [path,bytes]:image)put(path,bytes);
}
void perform(Fixture& fixture,Mode mode,std::optional<sr::Session>& owner) {
  switch(mode) {
    case Mode::log:log_row(*owner);return;
    case Mode::commit:assert(!owner->decide().rejected);return;
    case Mode::deliver:assert(owner->deliver());return;
    case Mode::checkpoint:static_cast<void>(owner->checkpoint());return;
    case Mode::recover:owner.emplace(fixture.recover());return;
  }
}
void receive(Fixture& fixture) {
  auto owner=fixture.recover();auto state=owner.state();
  assert(state.delivered<=state.committed && state.committed<=state.disposed &&
      state.disposed<=state.logged && state.logged<=1);
  if(state.pending)assert(!owner.decide().rejected);
  if(owner.output())assert(owner.deliver());
  state=owner.state();
  assert(state.logged==state.disposed && state.disposed==state.committed &&
      state.committed==state.delivered);
  const auto current=current_bag(owner);
  if(state.committed==0)assert(current.empty());
  else {
    const Bag expected{{runtime::aggregate::Row{std::nullopt},2}};assert(current==expected);
    assert(owner.source_weight(TableId{0},cells)==2);
    assert(owner.progress().source_positions.at("feed")==10);
  }
}

// The existing two syscall seams exercise the same bounded POSIX implementation
// for typed rows. Inject both sides of every observed syscall; then use actual
// reopening/native replay, not an inferred fsync outcome, to receive survivors.
void syscall_failures_and_cuts(bool indexed) {
  std::uint64_t failures=0,cuts=0;
  const Catalog catalog{1,{{"r",{{"x",ScalarType::int64,true}}}}};
  for(const auto mode:{Mode::log,Mode::commit,Mode::deliver,Mode::checkpoint,Mode::recover}) {
    Fixture fixture(indexed,catalog,"SELECT x FROM r");prepare(fixture,mode);
    if(mode==Mode::recover) {
      const auto wal=generation_file(fixture,1);
      put(wal,contents(wal)+"C");put(fixture.sink,contents(fixture.sink)+"C");
    }
    const auto image=capture(fixture);
    const auto memory=fixture.account.statistics().current.allocations;
    const auto descriptors=sql_aggregate_file_test::descriptors();
    std::optional<sr::Session> owner;
    if(mode!=Mode::recover)owner.emplace(fixture.recover());
    probe::Hook trace;
    {probe::Installed installed(trace);perform(fixture,mode,owner);}
    owner.reset();
    assert(fixture.account.statistics().current.allocations==memory);
    for(std::size_t index=0;index<trace.size;++index) {
      const auto event=trace.events[index];
      // The seam cannot replace the result of an already-failed syscall with
      // an after-effect error. Optional ENOENT observations remain such data.
      if(event.after && event.result<0)continue;
      restore(fixture,image);
      if(mode!=Mode::recover)owner.emplace(fixture.recover());
      probe::Hook hook;hook.fail=event.point;hook.after=event.after;bool failed=false;
      {
        probe::Installed installed(hook);
        try {perform(fixture,mode,owner);}
        catch(const sr::FileFailure&) {failed=true;}
        catch(const recovery::GenerationFailure&) {failed=true;}
      }
      assert(failed);
      if(owner) {
        assert(owner->requires_reopen());
        refused([&]{static_cast<void>(owner->state());});
      }
      owner.reset();
      assert(fixture.account.statistics().current.allocations==memory);
      assert(sql_aggregate_file_test::descriptors()==descriptors);
      receive(fixture);++failures;
    }
    for(std::size_t index=0;index<trace.size;++index) {
      const auto event=trace.events[index];if(!probe::durability(event))continue;
      restore(fixture,image);
      if(mode!=Mode::recover)owner.emplace(fixture.recover());
      const auto child=::fork();assert(child>=0);
      if(child==0) {
        probe::Hook hook;hook.crash=event.point;hook.after=event.after;
        probe::Installed installed(hook);perform(fixture,mode,owner);::_exit(1);
      }
      owner.reset();int status=0;
      assert(::waitpid(child,&status,0)==child && WIFEXITED(status) && WEXITSTATUS(status)==77);
      receive(fixture);++cuts;
      assert(fixture.account.statistics().current.allocations==memory);
      assert(sql_aggregate_file_test::descriptors()==descriptors);
    }
  }
  std::cout<<"SQL rows indexed="<<indexed<<" syscall failures="<<failures
      <<" real process cuts="<<cuts<<'\n';
}

// The first append stat occurs after native output/frame/index funding. Deny
// covered C++ allocations from that point through publication/acknowledgement.
void prepaid_publication(bool indexed) {
  const Catalog catalog{1,{{"r",{{"x",ScalarType::int64,true}}}}};
  for(const bool delivery:{false,true}) {
    Fixture fixture(indexed,catalog,"SELECT x FROM r");prepare(fixture,delivery?Mode::deliver:Mode::commit);
    const auto image=capture(fixture);std::optional<sr::Session> owner;owner.emplace(fixture.recover());
    const auto mode=delivery?Mode::deliver:Mode::commit;probe::Hook trace;
    {probe::Installed installed(trace);perform(fixture,mode,owner);}
    owner.reset();restore(fixture,image);owner.emplace(fixture.recover());
    probe::Hook hook;
    for(std::size_t i=0;i<trace.size;++i) {
      const auto event=trace.events[i];
      if(!event.generation && !event.after && event.file==sr::FileStage::stat_file) {hook.deny=event.point;break;}
    }
    assert(hook.deny>0);
    {
      s04_alloc::Scope allocation;probe::Installed installed(hook);perform(fixture,mode,owner);
      assert(hook.armed && s04_alloc::calls==0 && !s04_alloc::triggered);
    }
    owner.reset();receive(fixture);
  }
}
} // namespace

int main() {
  for(const bool indexed:{false,true}) {
    syscall_failures_and_cuts(indexed);prepaid_publication(indexed);
  }
}
