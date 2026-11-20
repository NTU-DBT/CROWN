#include "sql_aggregate_file_fixture.hpp"
#include "sql_aggregate_file_probe.hpp"
#include "index_allocation.hpp"
#include <cerrno>
#include <iostream>
#include <optional>
#include <sys/wait.h>

namespace {
using namespace crown;
using namespace crown::sql_aggregate_file_test;
// Bounded syscall observations only. Faults run real I/O unless denied; crash
// cuts exit the child before/after the actual call and let the parent reopen.
struct Hook {
  std::array<ar::testing::FileEvent,4096> events{};std::size_t size=0;
  std::uint64_t fail_at=0,crash_at=0,deny_after=0;
  bool after=false,crash_after=false,zero_entropy=false,armed=false;
  int error=EIO,cleanup_error=0;
  std::size_t short_bytes=SIZE_MAX;
  std::optional<ar::FileStage> short_stage,repeat_interrupt;
  static ar::testing::FileDecision call(const ar::testing::FileEvent& event,void* context) noexcept {
    auto& h=*static_cast<Hook*>(context);if(h.size<h.events.size())h.events[h.size++]=event;
    if(event.ordinal==h.crash_at && event.after==h.crash_after)::_exit(77);
    if(event.after && event.ordinal==h.deny_after) { s04_alloc::remaining=0;s04_alloc::calls=0;s04_alloc::triggered=false;h.armed=true; }
    ar::testing::FileDecision result;
    if(!event.after) {
      if(!h.short_stage || *h.short_stage==event.stage)result.maximum_transfer=h.short_bytes;
      result.zero_entropy=h.zero_entropy;
      if(h.repeat_interrupt && *h.repeat_interrupt==event.stage)result.error_before=EINTR;
      if(event.stage==ar::FileStage::unlink_temporary && h.cleanup_error!=0)result.error_before=h.cleanup_error;
      if(event.ordinal==h.fail_at) { if(h.after)result.error_after=h.error;else result.error_before=h.error; }
    }
    return result;
  }
};
struct Installed {
  explicit Installed(Hook& hook) { ar::testing::set_file_hook(Hook::call,&hook); }
  ~Installed() { ar::testing::set_file_hook(nullptr,nullptr); }
};
enum class Mode { create,open,append,repair,duplicate };
std::string prior(bool sink,Mode mode,const Packets& p) {
  if(mode==Mode::create)return {};
  const auto& frames=sink?p.sink:p.wal;
  const std::size_t count=mode==Mode::open || mode==Mode::duplicate?(sink?2U:3U):(sink?1U:2U);
  auto result=Packets::prefix(frames,count);
  if(mode==Mode::repair)result+=frames[sink?1:2].bytes().substr(0,23);
  return result;
}
void setup(bool sink,Mode mode,const std::string& path,const Packets& p) {
  std::filesystem::remove(path);if(mode!=Mode::create)put(path,prior(sink,mode,p));
}
// No coordinator/native publication is exercised here: this is the actual
// lower file create/open/append/repair/duplicate protocol and checked close.
void exercise(bool sink,Mode mode,const std::string& path,Schema& s,const Packets& p,
    const resource::MemoryAccount& account,ar::FileLimits limits={}) {
  const auto run=[&](auto file) {
    if(mode==Mode::append)file.append((sink?p.sink:p.wal)[sink?1:2]);
    if(mode==Mode::repair)file.repair_tail();
    if constexpr(std::is_same_v<decltype(file),ar::SinkFile>)if(mode==Mode::duplicate)file.verify(p.sink[1]);
    file.close();
  };
  if(sink) {
    if(mode==Mode::create)run(ar::SinkFile::create(account,path,s.admitted.descriptor,s.sink,limits));
    else run(ar::SinkFile::open(account,path,s.admitted.descriptor,s.sink,limits));
  } else {
    if(mode==Mode::create)run(ar::WalFile::create(account,path,s.admitted.descriptor,s.wal,limits));
    else run(ar::WalFile::open(account,path,s.admitted.descriptor,s.wal,limits));
  }
}
// Recovery adopts only complete surviving prefix bytes. A failed repair may
// retain its torn suffix; neither repair outcome discards a complete Input.
void surviving(bool sink,Mode mode,const std::string& path,Schema& s,const Packets& p,
    const resource::MemoryAccount& account) {
  if(!std::filesystem::exists(path)) { assert(mode==Mode::create);return; }
  const auto bytes=contents(path),before=prior(sink,mode,p);
  const auto& frames=sink?p.sink:p.wal;
  const auto complete=Packets::prefix(frames,mode==Mode::create?1:(sink?1:2));
  assert(bytes==before || (mode==Mode::create && bytes==complete) ||
      (mode==Mode::append && bytes==before+std::string(frames[sink?1:2].bytes())) || (mode==Mode::repair && bytes==complete));
  if(sink) { auto file=ar::SinkFile::open(account,path,s.admitted.descriptor,s.sink);assert(file.state().prefix.physical_sequence<=1); }
  else { auto file=ar::WalFile::open(account,path,s.admitted.descriptor,s.wal);
    assert(file.state().wal.command_sequence<=1);if(mode==Mode::repair)assert(file.state().wal.pending); }
}
// Inject before each call and after supported actual effects; acquisition-after
// errors normalize before open. Check smaller quotas, retryable EINTR and short I/O. Track
// receiving account allocations and actual FD/temp namespace cleanup separately.
void syscall_matrix(Schema& s,const Packets& p) {
  Directory dir;const auto path=dir.file();const auto account=resource::MemoryAccount::create(128ULL*1024*1024);
  std::size_t failures=0,crashes=0;
  for(bool sink:{false,true})for(auto mode:{Mode::create,Mode::open,Mode::append,Mode::repair,Mode::duplicate}) {
    if(!sink && mode==Mode::duplicate)continue;
    setup(sink,mode,path,p);Hook trace;{Installed install(trace);exercise(sink,mode,path,s,p,account);}
    assert(trace.size>0 && trace.size<trace.events.size());const auto operations=trace.events[trace.size-1].ordinal;
    for(std::uint64_t point=1;point<=operations;++point)for(bool after:{false,true}) {
      setup(sink,mode,path,p);Hook hook;hook.fail_at=point;hook.after=after;
      const auto fds=descriptors();bool failed=false;
      {Installed install(hook);try { exercise(sink,mode,path,s,p,account); } catch(const ar::FileFailure& error) {failed=true;assert(!error.temporary_cleanup_failed());}}
      assert(failed && descriptors()==fds && account.statistics().current.allocations==1 && temporaries(dir)==0);
      surviving(sink,mode,path,s,p,account);++failures;
    }
    // The quota bounds one call (or one scanned frame), not the file lifetime:
    // small caps refuse cleanly, and once a cap suffices every larger one does.
    std::uint64_t threshold=0;
    for(std::uint64_t cap=1;cap<=operations;++cap) {
      setup(sink,mode,path,p);auto limits=ar::FileLimits{};limits.operations=cap;bool failed=false;
      try {exercise(sink,mode,path,s,p,account,limits);}catch(const ar::FileFailure& error){failed=true;assert(error.fault()==ar::FileFault::limit);}
      assert((!failed || threshold==0) && temporaries(dir)==0 && account.statistics().current.allocations==1);
      if(!failed && threshold==0)threshold=cap;
      surviving(sink,mode,path,s,p,account);
    }
    assert(threshold>1);
    for(auto stage:{ar::FileStage::open_directory,ar::FileStage::open_file,ar::FileStage::entropy,ar::FileStage::create_temporary,
        ar::FileStage::read_data,ar::FileStage::write_data,ar::FileStage::sync_file,ar::FileStage::sync_directory,
        ar::FileStage::truncate_tail,ar::FileStage::lock_file,ar::FileStage::stat_file,ar::FileStage::unlink_temporary}) {
      const auto end=trace.events.begin()+static_cast<std::ptrdiff_t>(trace.size);
      const auto at=std::find_if(trace.events.begin(),end,[&](const auto& e){return !e.after && e.stage==stage;});
      if(at==end)continue;
      setup(sink,mode,path,p);Hook hook;hook.fail_at=at->ordinal;hook.error=EINTR;
      {Installed install(hook);exercise(sink,mode,path,s,p,account);}surviving(sink,mode,path,s,p,account);
    }
    setup(sink,mode,path,p);Hook short_io;short_io.short_bytes=3;{Installed install(short_io);exercise(sink,mode,path,s,p,account);}
    // Real child exits at each durability-relevant boundary. Incomplete create
    // temporaries are intentionally left for namespace maintenance, not invented
    // as successful destination publication or automatically retired history.
    for(std::size_t i=0;i<trace.size;++i) {
      const auto event=trace.events[i];
      if(event.stage!=ar::FileStage::write_data && event.stage!=ar::FileStage::sync_file &&
          event.stage!=ar::FileStage::sync_directory && event.stage!=ar::FileStage::link_file && event.stage!=ar::FileStage::truncate_tail)continue;
      setup(sink,mode,path,p);const auto child=::fork();assert(child>=0);
      if(child==0) {Hook hook;hook.crash_at=event.ordinal;hook.crash_after=event.after;Installed install(hook);exercise(sink,mode,path,s,p,account);::_exit(1);}
      int status=0;assert(::waitpid(child,&status,0)==child && WIFEXITED(status) && WEXITSTATUS(status)==77);
      surviving(sink,mode,path,s,p,account);++crashes;
      for(const auto& entry:std::filesystem::directory_iterator(dir.name))if(entry.path().filename().native().starts_with(".crown-r2-"))std::filesystem::remove(entry.path());
    }
  }
  std::cout<<"R2 file faults="<<failures<<", real crash cuts="<<crashes<<"; all syscall quotas/EINTR/short transfers passed\n";
}
// An uncertain append poisons all authority getters at prewrite-stat, write,
// fsync and post-sync-stat. Reopening can adopt an actual complete surviving
// record even if the previous owner reported unknown or a final-stat failure.
void poison_and_short_tail(Schema& s,const Packets& p) {
  Directory dir;const auto path=dir.file();
  for(bool sink:{false,true})for(std::uint64_t boundary=1;boundary<=4;++boundary)for(bool after:{false,true}) {
    setup(sink,Mode::append,path,p);
    const auto run=[&](auto file) {
      const auto before=file.state().statistics.operations;Hook hook;hook.fail_at=before+boundary;hook.after=after;bool failed=false;
      {Installed install(hook);try {file.append((sink?p.sink:p.wal)[sink?1:2]);}catch(const ar::FileFailure& error) {
        failed=true;assert(error.outcome()==(boundary==1?ar::FileOutcome::unchanged:boundary<4?ar::FileOutcome::unknown:ar::FileOutcome::durable));
      }}
      assert(failed && file.requires_reopen());refused([&]{static_cast<void>(file.state());});
      refused([&]{file.append((sink?p.sink:p.wal)[sink?1:2]);});
      if constexpr(std::is_same_v<decltype(file),ar::SinkFile>) {
        refused([&]{static_cast<void>(file.prefix(0));});refused([&]{static_cast<void>(file.receipt());});
      }
      file.close();
    };
    if(sink)run(ar::SinkFile::open(s.account,path,s.admitted.descriptor,s.sink));
    else run(ar::WalFile::open(s.account,path,s.admitted.descriptor,s.wal));
    surviving(sink,Mode::append,path,s,p,s.account);
  }
  // Three real bytes followed by a second-write failure leave a valid magic
  // prefix. A new owner repairs it explicitly; the old owner cannot retry.
  setup(false,Mode::append,path,p);auto wal=ar::WalFile::open(s.account,path,s.admitted.descriptor,s.wal);
  Hook hook;hook.short_stage=ar::FileStage::write_data;hook.short_bytes=3;hook.fail_at=wal.state().statistics.operations+3;
  {Installed install(hook);refused([&]{wal.append(p.wal[2]);});}assert(wal.requires_reopen());wal.close();
  auto reopened=ar::WalFile::open(s.account,path,s.admitted.descriptor,s.wal);assert(reopened.state().torn_tail && reopened.state().wal.pending);
  reopened.repair_tail();reopened.append(p.wal[2]);assert(reopened.state().wal.command_sequence==1);
}
// Keep failed repair/duplicate owners alive to prove that their getters and
// retry paths stay poisoned, beyond survivor-byte checks after destruction.
void retained_repair_and_verify(Schema& s,const Packets& p) {
  Directory dir;const auto path=dir.file();
  for(bool sink:{false,true})for(bool repair:{false,true}) {
    if(!sink && !repair)continue;
    for(std::uint64_t boundary=1;boundary<=(repair?4U:3U);++boundary)for(bool after:{false,true}) {
      setup(sink,repair?Mode::repair:Mode::duplicate,path,p);
      const auto run=[&](auto file) {
        Hook hook;hook.fail_at=file.state().statistics.operations+boundary;hook.after=after;bool failed=false;
        {Installed install(hook);try {
          if(repair)file.repair_tail();
          else if constexpr(std::is_same_v<decltype(file),ar::SinkFile>)file.verify(p.sink[1]);
        }catch(const ar::FileFailure&){failed=true;}}
        assert(failed && file.requires_reopen());refused([&]{static_cast<void>(file.state());});refused([&]{file.repair_tail();});
        if constexpr(std::is_same_v<decltype(file),ar::SinkFile>) {
          refused([&]{static_cast<void>(file.receipt());});refused([&]{file.verify(p.sink[1]);});
        }
        file.close();
      };
      if(sink)run(ar::SinkFile::open(s.account,path,s.admitted.descriptor,s.sink));
      else run(ar::WalFile::open(s.account,path,s.admitted.descriptor,s.wal));
      surviving(sink,repair?Mode::repair:Mode::duplicate,path,s,p,s.account);
    }
  }
}
// Explicit exhaustion/collision/cleanup cases remain finite and do not hide
// resource denial in broad exception fallbacks. Allocation from the first
// successful prewrite stamp check through mutation/publication is denied,
// after all required pre-funding has completed.
void exceptional_paths(Schema& s,const Packets& p) {
  Directory dir;const auto path=dir.file();
  for(bool sink:{false,true}) {
    setup(sink,Mode::append,path,p);
    const auto run=[&](auto file) {
      Hook hook;hook.deny_after=file.state().statistics.operations+1;
      {Installed install(hook);s04_alloc::Scope count;file.append((sink?p.sink:p.wal)[sink?1:2]);assert(hook.armed && s04_alloc::calls==0 && !s04_alloc::triggered);}
      assert(!file.requires_reopen());file.close();
    };
    if(sink)run(ar::SinkFile::open(s.account,path,s.admitted.descriptor,s.sink));
    else run(ar::WalFile::open(s.account,path,s.admitted.descriptor,s.wal));
  }
  for(auto stage:{ar::FileStage::entropy,ar::FileStage::write_data,ar::FileStage::read_data}) {
    const bool opening=stage==ar::FileStage::read_data;setup(false,opening?Mode::open:Mode::create,path,p);
    Hook hook;hook.short_stage=stage;hook.short_bytes=0;
    {Installed install(hook);refused([&]{exercise(false,opening?Mode::open:Mode::create,path,s,p,s.account);});}
    assert(temporaries(dir)==0);
  }
  for(auto stage:{ar::FileStage::entropy,ar::FileStage::create_temporary,ar::FileStage::write_data,ar::FileStage::unlink_temporary}) {
    setup(false,Mode::create,path,p);Hook hook;hook.repeat_interrupt=stage;ar::FileLimits limits;limits.operations=30;
    {Installed install(hook);refused([&]{exercise(false,Mode::create,path,s,p,s.account,limits);});}
    if(stage==ar::FileStage::unlink_temporary) {
      assert(hook.events[hook.size-1].ordinal<=limits.operations+8 && temporaries(dir)==1);
      auto file=ar::WalFile::open(s.account,path,s.admitted.descriptor,s.wal);assert(file.state().wal.records==1);
      for(const auto& entry:std::filesystem::directory_iterator(dir.name))if(entry.path().filename().native().starts_with(".crown-r2-"))std::filesystem::remove(entry.path());
    } else assert(temporaries(dir)==0);
  }
  // Deterministic entropy meets an actual pre-existing temporary inode 16 times.
  const auto collision=dir.file(".crown-r2-00000000000000000000000000000000");put(collision,"keep");
  setup(false,Mode::create,path,p);Hook zeros;zeros.zero_entropy=true;
  {Installed install(zeros);refused([&]{exercise(false,Mode::create,path,s,p,s.account);});}assert(contents(collision)=="keep");std::filesystem::remove(collision);
  setup(false,Mode::create,path,p);Hook cleanup;cleanup.fail_at=5;cleanup.cleanup_error=EACCES;bool reported=false;
  {Installed install(cleanup);try {exercise(false,Mode::create,path,s,p,s.account);}catch(const ar::FileFailure& error){reported=error.temporary_cleanup_failed();}}
  assert(reported && !std::filesystem::exists(path) && temporaries(dir)==1);
  // A post-open external change violates the cooperative-writer contract; the
  // next checked I/O detects its stamp and poisons the old owner before writes.
  const auto changed=dir.file("changed");put(changed,Packets::prefix(p.sink,1));
  auto file=ar::SinkFile::open(s.account,changed,s.admitted.descriptor,s.sink);put(changed,contents(changed)+"C");
  refused([&]{static_cast<void>(file.append(p.sink[1]));});assert(file.requires_reopen());file.close();
}
} // namespace
int main() {
  Schema schema;const Packets packets(schema);syscall_matrix(schema,packets);poison_and_short_tail(schema,packets);
  retained_repair_and_verify(schema,packets);exceptional_paths(schema,packets);
}
