#include "journal_file_fixture.hpp"
#include "index_allocation.hpp"
#include <sys/wait.h>
#include <fcntl.h>
using namespace crown;
using namespace crown::journal_file_test;
namespace {
template<class Action> void file_rejected(Action action,jp::FileFault expected) {
  bool failed=false;try{action();}catch(const jp::FileFailure& error){failed=error.fault()==expected;}check(failed,"file rejection differs");
}
void basic(const Frames& f) {
  Directory dir;const auto path=dir.file();auto account=resource::MemoryAccount::create(4*1024*1024);const auto resident=account.statistics().current;
  std::size_t allocations=0;const auto before=account.statistics().successful_allocations;
  {
    std::optional<jp::File> file;{s04_alloc::Scope count;file.emplace(jp::File::create(account,path,f.binding));allocations=s04_alloc::calls;}
    check(account.statistics().successful_allocations-before==allocations,"journal create C++ new/account counts differ");
    check(contents(path)==f.header && file->state().records==1 && temporaries(dir)==0,"created journal header differs");
    struct stat status{};check(::stat(path.c_str(),&status)==0 && (status.st_mode&0777)==0600,"journal mode differs");
    file_rejected([&]{auto second=jp::File::open(account,path,f.binding);},jp::FileFault::busy);
    const pid_t child=::fork();check(child>=0,"fork failed");
    if(child==0){try{auto other=jp::File::open(account,path,f.binding);::_exit(2);}catch(const jp::FileFailure& e){::_exit(e.fault()==jp::FileFault::busy?0:3);}catch(...){::_exit(4);}}
    int result=0;check(::waitpid(child,&result,0)==child && WIFEXITED(result) && WEXITSTATUS(result)==0,"cross-process writer lock failed");
    bool invalid=false;{s04_alloc::Scope deny(0);try{file->append("bad");}catch(const jp::Failure&){invalid=true;}}
    check(invalid && contents(path)==f.header && file->state().records==1,"invalid append changed disk/cursor");
    file->append(f.input);check(file->state().pending->frame==f.input,"pending file input lifetime differs");
    const auto saved=file->state().pending->frame;file->append(f.commit);check(file->state().command_sequence==1 && !file->state().pending,"file commit differs");
    static_cast<void>(saved);file->close();file_rejected([&]{static_cast<void>(file->state());},jp::FileFault::state);
  }
  check(account.statistics().current==resident,"journal file owner leaked");
  const auto full=f.header+f.input+f.commit;check(contents(path)==full,"append changed wire bytes");
  {auto reopened=jp::File::open(account,path,f.binding);check(reopened.state().records==3 && reopened.state().command_sequence==1,"reopened committed prefix differs");auto moved=std::move(reopened);file_rejected([&]{static_cast<void>(reopened.state());},jp::FileFault::state);moved.close();}
  const auto fds=descriptors();bool duplicate=false;try{auto value=jp::File::create(account,path,f.binding);}catch(const jp::FileFailure& e){duplicate=e.stage()==jp::FileStage::link_file;}
  check(duplicate && contents(path)==full && descriptors()==fds && temporaries(dir)==0,"exclusive create changed existing journal");
  auto wrong=f.binding;++wrong.generation;bool binding=false;try{auto value=jp::File::open(account,path,wrong);}catch(const jp::Failure& e){binding=e.fault()==jp::Fault::binding;}check(binding && contents(path)==full,"wrong generation accepted/mutated");
  auto changed=jp::File::open(account,path,f.binding);{std::ofstream out(path,std::ios::app);out<<'x';}
  jp::Checkpoint mark{1,1,{}};mark.checkpoint_sha256.fill('d');auto next=jp::encode(account,3,jp::PayloadView{mark});
  file_rejected([&]{changed.append(bytes(next));},jp::FileFault::changed);changed.close();
  std::cout<<"exclusive create, two-process ownership, durable append/reopen, move, binding, mutation and account ownership passed\n";
}
void recovery_cases(const Frames& f) {
  Directory dir;const auto path=dir.file();auto account=resource::MemoryAccount::create(4*1024*1024);
  // Open retains complete Input records and reports incomplete trailing bytes.
  // Explicit repair removes only that tail; pending Input records remain.
  const auto full=f.header+f.input+f.commit;
  for(std::size_t cut=f.header.size();cut<=full.size();++cut) {
    put(path,std::string_view(full).substr(0,cut));auto file=jp::File::open(account,path,f.binding);const auto state=file.state();
    const auto complete=cut< f.header.size()+f.input.size()?f.header.size():cut<full.size()?f.header.size()+f.input.size():full.size();
    check(state.consumed==complete && state.torn_tail==(cut!=complete),"file prefix cut differs");
    if(state.torn_tail)file_rejected([&]{file.append(f.commit);},jp::FileFault::state);
    file.repair_tail();check(!file.state().torn_tail && contents(path)==full.substr(0,complete),"repair discarded a complete record or kept torn bytes");
    if(complete==f.header.size()){file.append(f.input);file.append(f.commit);}
    else if(complete<full.size()){check(file.state().pending->frame==f.input,"repair lost pending input");file.append(f.commit);}
    check(file.state().command_sequence==1 && contents(path)==full,"post-repair append differs");file.close();
  }
  for(const std::size_t cut:{std::size_t{0},std::size_t{147},f.header.size()-1}) {
    put(path,std::string_view(full).substr(0,cut));bool failed=false;try{auto value=jp::File::open(account,path,f.binding);}catch(const jp::Failure&){failed=true;}catch(const jp::FileFailure&){failed=true;}check(failed,"incomplete mandatory header accepted");
  }
  for(std::size_t byte=0;byte<full.size();++byte) {
    auto bad=full;bad[byte]^=1;put(path,bad);bool failed=false;try{auto value=jp::File::open(account,path,f.binding);}catch(const jp::Failure&){failed=true;}
    check(failed && contents(path)==bad,"file corruption accepted or repaired without authority");
  }
  // A watermark can durably commit physical substeps before command completion.
  auto binding=f.binding;binding.input_kind=jp::InputKind::window;auto header=jp::encode(account,0,jp::PayloadView{binding});
  const io::WindowCommandView watermark{1,io::AdvanceWatermark{30},{}};auto input=jp::encode(account,1,jp::PayloadView{jp::InputView{watermark,{}}});
  jp::Commit step;step.input_ordinal=1;step.input_sha256=jp::inspect(bytes(input)).body_sha256;step.physical_sequence=1;step.completes_input=false;
  auto commit=jp::encode(account,2,jp::PayloadView{step});std::string prefix(bytes(header));prefix+=bytes(input);prefix+=bytes(commit);put(path,prefix+f.commit.substr(0,20));
  {auto file=jp::File::open(account,path,binding);file.repair_tail();check(file.state().physical_sequence==1 && file.state().command_sequence==0 && file.state().pending->next_substep==1 && file.state().pending->frame==bytes(input) && contents(path)==prefix,"repair lost committed watermark substep/input");
    step.kind=jp::CommitKind::metadata;step.substep=1;step.command_sequence=1;step.completes_input=true;auto last=jp::encode(account,3,jp::PayloadView{step});file.append(bytes(last));check(!file.state().pending && file.state().command_sequence==1,"watermark resume differs");file.close();}
  std::cout<<"every input/commit byte cut, every corruption byte, explicit repair and partial-window continuation passed\n";
}
void resources_and_paths(const Frames& f) {
  Directory dir;const auto path=dir.file();put(path,f.header+f.input+f.commit);auto account=resource::MemoryAccount::create(4*1024*1024);
  std::uint64_t peak=0;std::size_t allocations=0;
  {auto receiving=resource::MemoryAccount::create(4*1024*1024);const auto before=receiving.statistics().successful_allocations;{s04_alloc::Scope count;auto value=jp::File::open(receiving,path,f.binding);value.close();allocations=s04_alloc::calls;}check(allocations==receiving.statistics().successful_allocations-before,"journal open C++ new/account counts differ");peak=receiving.statistics().peak_requested_bytes;}
  {auto receiving=resource::MemoryAccount::create(peak);auto value=jp::File::open(receiving,path,f.binding);value.close();}
  bool limited=false;try{auto receiving=resource::MemoryAccount::create(peak-1);auto value=jp::File::open(receiving,path,f.binding);}catch(const resource::MemoryFailure& e){limited=e.fault()==resource::MemoryFault::limit;}check(limited,"one-under journal receiving cap accepted");
  for(std::size_t k=0;k<allocations;++k) {
    const auto fds=descriptors();const auto resident=account.statistics().current;bool failed=false;
    {s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(k));try{auto value=jp::File::open(account,path,f.binding);}catch(const std::bad_alloc&){failed=true;}}
    check(failed && descriptors()==fds && account.statistics().current==resident,"journal open allocation failure leaked");
  }
  // Intercepted C++ new failures during create precede file publication.
  std::filesystem::remove(path);std::size_t creates=0;
  {s04_alloc::Scope count;auto value=jp::File::create(account,path,f.binding);value.close();creates=s04_alloc::calls;}
  for(std::size_t k=0;k<creates;++k) {
    std::filesystem::remove(path);const auto fds=descriptors();const auto resident=account.statistics().current;bool failed=false;
    {s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(k));try{auto value=jp::File::create(account,path,f.binding);}catch(const std::bad_alloc&){failed=true;}}
    check(failed && !std::filesystem::exists(path) && temporaries(dir)==0 && descriptors()==fds && account.statistics().current==resident,"create OOM published or leaked");
  }
  // A commit-buffer allocation failure leaves its durable pending input intact
  // and the same writer can retry: no cursor mutation or file operation occurred.
  put(path,f.header+f.input);
  {auto value=jp::File::open(account,path,f.binding);const auto operations=value.operations();bool failed=false;
    {s04_alloc::Scope fault(0);try{value.append(f.commit);}catch(const std::bad_alloc&){failed=true;}}
    check(failed && value.operations()==operations && value.state().pending->frame==f.input && contents(path)==f.header+f.input,"append OOM changed cursor/file");
    value.append(f.commit);value.close();}
  const auto scanned=jp::scan(f.header+f.input+f.commit);jp::FileLimits exact;exact.scan.bytes=scanned.consumed;exact.scan.work=scanned.work;exact.scan.records=scanned.records;
  {auto value=jp::File::open(account,path,f.binding,exact);value.close();}
  for(unsigned which=0;which<3;++which){auto low=exact;if(which==0)--low.scan.bytes;else if(which==1)--low.scan.work;else --low.scan.records;bool failed=false;try{auto value=jp::File::open(account,path,f.binding,low);}catch(const jp::Failure&){failed=true;}catch(const jp::FileFailure&){failed=true;}check(failed,"one-under file scan cap accepted");}
  const auto fifo=dir.file("fifo");check(::mkfifo(fifo.c_str(),0600)==0,"mkfifo failed");file_rejected([&]{auto value=jp::File::open(account,fifo,f.binding);},jp::FileFault::not_regular);
  const auto link=dir.file("link");check(::symlink("state.wal",link.c_str())==0,"symlink failed");file_rejected([&]{auto value=jp::File::open(account,link,f.binding);},jp::FileFault::io);
  bool duplicate=false;try{auto value=jp::File::create(account,link,f.binding);}catch(const jp::FileFailure&){duplicate=true;}check(duplicate && std::filesystem::is_symlink(link),"create replaced symlink");
  for(const auto& bad:{std::string{},dir.name+"/",std::string("bad\0path",8),std::string(4096,'x'),dir.file(".")})file_rejected([&]{auto value=jp::File::create(account,bad,f.binding);},jp::FileFault::path);
  std::cout<<"intercepted C++ new calls="<<allocations<<" exact/under memory/scan caps, allocation faults, regular/no-follow and path admission passed\n";
}
}
int main(int argc,char** argv) {try{check(argc==2,"expected fixture directory");const Frames f(argv[1]);basic(f);recovery_cases(f);resources_and_paths(f);}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
