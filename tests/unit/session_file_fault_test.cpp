#include "session_file_fixture.hpp"
#include "checkpoint_file_probe.hpp"
#include <sys/wait.h>
#include <cerrno>
#include <csignal>
#include <fcntl.h>

using namespace crown;
using namespace crown::runtime;
using namespace crown::recovery;
using namespace crown::session_file_test;
namespace {
struct Hook {
  std::array<testing::FileEvent,4096> events{};
  std::size_t size=0,short_bytes=SIZE_MAX;
  std::uint64_t fail_at=0,crash_at=0;
  bool after=false,crash_after=false;
  bool zero_entropy=false;
  int cleanup_error=0;
  int error=EIO;
  static testing::FileDecision call(const testing::FileEvent& event,void* pointer) noexcept {
    auto& self=*static_cast<Hook*>(pointer);
    if(self.size<self.events.size())self.events[self.size++]=event;
    if(event.ordinal==self.crash_at && event.after==self.crash_after)::_exit(77);
    testing::FileDecision result;
    if(!event.after) {
      result.maximum_transfer=self.short_bytes;
      result.zero_entropy=self.zero_entropy;
      if(event.stage==FileStage::unlink_temporary)result.error_before=self.cleanup_error;
      if(event.ordinal==self.fail_at) {
        if(self.after)result.error_after=self.error;else result.error_before=self.error;
      }
    }
    return result;
  }
  void install(){testing::set_file_hook(call,this);}
  static void clear(){testing::set_file_hook(nullptr,nullptr);}
};
struct Installed {
  explicit Installed(Hook& hook){hook.install();}
  ~Installed(){Hook::clear();}
};
void assert_epoch(const Pair& pair,const std::string& path,std::uint64_t sequence) {
  auto value=QuerySession::restore_file(pair.compiler,path);typed::grant(*value,pair.test.plan.options().indexed_storage.has_value());
  check(value->status().committed_sequence==sequence && value->progress().sequence==sequence,"published checkpoint epoch differs");
  Database database;database.tables.resize(1);
  for(std::uint64_t i=0;i<sequence;++i)database.tables[0].insert(pair.test.updates[static_cast<std::size_t>(i)].values);
  check(typed::rows(*value)==typed::oracle(pair.test,database),"published exact state differs from independent definition");
  typed::step(*value,pair.test,database,pair.test.updates[static_cast<std::size_t>(sequence)],DeltaMode::delta);
}
void io_faults(bool indexed) {
  Directory directory;const auto path=directory.file();Pair pair(indexed);CheckpointFileLimits limits;limits.chunk_bytes=64;
  static_cast<void>(publish_session_image(path,pair.old_image,{},limits));Hook trace;PublishedCheckpoint baseline;
  {Installed hook(trace);s04_alloc::Scope deny(0);baseline=publish_session_image(path,pair.new_image,{},limits);check(s04_alloc::calls==0,"file publisher allocated staging outside native image");}
  for(std::uint64_t point=1;point<=baseline.operations;++point)for(const bool after:{false,true}) {
    Hook::clear();static_cast<void>(publish_session_image(path,pair.old_image,{},limits));const auto fds=descriptors();Hook failure;failure.fail_at=point;failure.after=after;
    bool rejected=false;FileStage stage=FileStage::path;PublicationState publication=PublicationState::not_published;
    {Installed hook(failure);try{static_cast<void>(publish_session_image(path,pair.new_image,{},limits));}
      catch(const FileFailure& error){rejected=true;stage=error.stage();publication=error.publication();check(!error.temporary_cleanup_failed(),"normal injected failure left orphan temporary");}}
    check(rejected && descriptors()==fds && temporaries(directory)==0,"file error leaked descriptors/temporary or did not reject");
    const bool new_visible=stage==FileStage::sync_directory || stage==FileStage::close_directory || (stage==FileStage::rename_file && after);
    const auto expected=stage==FileStage::rename_file?PublicationState::unknown:stage==FileStage::sync_directory?PublicationState::published_unsynced:
        stage==FileStage::close_directory?PublicationState::durable:PublicationState::not_published;
    check(publication==expected,"file failure misreported publication/durability");assert_epoch(pair,path,new_visible?2:1);
  }
  {Hook short_io;short_io.short_bytes=3;Installed hook(short_io);auto value=publish_session_image(path,pair.new_image,{},limits);check(value.publication==PublicationState::durable,"short-write publisher failed");}
  assert_epoch(pair,path,2);
  for(const auto stage:{FileStage::write_data,FileStage::sync_file,FileStage::sync_directory}) {
    const auto event=std::find_if(trace.events.begin(),trace.events.begin()+static_cast<std::ptrdiff_t>(trace.size),[&](const auto& e){return e.stage==stage && !e.after;});
    check(event!=trace.events.begin()+static_cast<std::ptrdiff_t>(trace.size),"retry stage missing from trace");Hook interrupted;interrupted.fail_at=event->ordinal;interrupted.error=EINTR;
    {Installed hook(interrupted);auto value=publish_session_image(path,pair.new_image,{},limits);check(value.publication==PublicationState::durable,"EINTR publication did not retry safely");}
  }
  {Hook zero;zero.short_bytes=0;bool rejected=false;Installed hook(zero);try{static_cast<void>(publish_session_image(path,pair.new_image,{},limits));}catch(const FileFailure&){rejected=true;}check(rejected,"zero-progress entropy/write accepted");}
  for(std::uint64_t work=1;work<baseline.operations;++work) {
    Hook::clear();static_cast<void>(publish_session_image(path,pair.old_image,{},limits));auto low=limits;low.operations=work;const auto fds=descriptors();bool rejected=false;
    try{static_cast<void>(publish_session_image(path,pair.new_image,{},low));}catch(const FileFailure& error){rejected=error.fault()==FileFault::limit;}
    check(rejected && descriptors()==fds && temporaries(directory)==0,"file operation budget leaked/published partial data");
    const auto current=contents(path);check(current==std::string(pair.old_image.bytes.begin(),pair.old_image.bytes.end()) || current==std::string(pair.new_image.bytes.begin(),pair.new_image.bytes.end()),"operation budget left partial checkpoint");
  }
  Hook::clear();static_cast<void>(publish_session_image(path,pair.new_image,{},limits));Hook read_trace;
  {Installed hook(read_trace);auto value=QuerySession::restore_file(pair.compiler,path,SessionRestoreOptions{},limits);typed::grant(*value,indexed);}
  const auto read_operations=read_trace.events[read_trace.size-1].ordinal;
  for(std::uint64_t point=1;point<=read_operations;++point)for(const bool after:{false,true}) {
    Hook failure;failure.fail_at=point;failure.after=after;const auto fds=descriptors();bool rejected=false;
    {Installed hook(failure);try{auto value=QuerySession::restore_file(pair.compiler,path,SessionRestoreOptions{},limits);}catch(const FileFailure&){rejected=true;}}
    check(rejected && descriptors()==fds,"read fault escaped or leaked descriptor");assert_epoch(pair,path,2);
  }
  {Hook short_read;short_read.short_bytes=3;Installed hook(short_read);auto value=QuerySession::restore_file(pair.compiler,path,SessionRestoreOptions{},limits);check(value->status().committed_sequence==2,"short-read load differs");}
  std::cout<<"file faults indexed="<<indexed<<" publish="<<baseline.operations<<" read="<<read_operations<<" before/after, short I/O, EINTR and operation caps passed\n";
}
void crashes(bool indexed) {
  Directory directory;const auto path=directory.file();Pair pair(indexed);CheckpointFileLimits limits;limits.chunk_bytes=64;Hook trace;PublishedCheckpoint baseline;
  {Installed hook(trace);baseline=publish_session_image(path,pair.new_image,{},limits);}
  for(const auto& event:std::span<const testing::FileEvent>(trace.events.data(),trace.size)) {
    if(event.stage==FileStage::close_directory && !event.after){} // Included: complete directory sync already happened.
    Hook::clear();static_cast<void>(publish_session_image(path,pair.old_image,{},limits));const auto process=::fork();check(process>=0,"fork checkpoint crash fixture failed");
    if(process==0) {
      Hook crash;crash.crash_at=event.ordinal;crash.crash_after=event.after;crash.install();
      try{static_cast<void>(publish_session_image(path,pair.new_image,{},limits));}catch(...){::_exit(78);}::_exit(79);
    }
    int status=0;while(::waitpid(process,&status,0)<0){check(errno==EINTR,"waitpid checkpoint fixture failed");}
    check(WIFEXITED(status) && WEXITSTATUS(status)==77,"crash hook did not stop at actual syscall boundary");
    const bool new_visible=(event.stage==FileStage::rename_file && event.after) || event.stage==FileStage::sync_directory || event.stage==FileStage::close_directory;
    assert_epoch(pair,path,new_visible?2:1);remove_temporaries(directory);
  }
  std::cout<<"file crash indexed="<<indexed<<" boundaries="<<trace.size<<" old/new exact epoch and next-update behavior passed\n";
}
void namespace_collisions() {
  Directory directory;Pair pair(false);Hook fixed;fixed.zero_entropy=true;
  const auto path=directory.file(".crown-checkpoint-"+std::string(32,'0'));
  bool rejected=false;{Installed hook(fixed);try{static_cast<void>(publish_session_image(path,pair.new_image));}catch(const FileFailure&){rejected=true;}}
  check(rejected && !std::filesystem::exists(path),"temporary basename collision exposed destination before publication");
  const auto ordinary=directory.file();static_cast<void>(publish_session_image(ordinary,pair.old_image));
  {std::ofstream output(path,std::ios::binary);output<<"sentinel";}
  rejected=false;{Installed hook(fixed);try{static_cast<void>(publish_session_image(ordinary,pair.new_image));}catch(const FileFailure&){rejected=true;}}
  check(rejected && contents(path)=="sentinel","exclusive temporary creation overwrote another inode");assert_epoch(pair,ordinary,1);
  const auto linked=directory.file("link");check(::symlink("state.crown",linked.c_str())==0,"publication symlink fixture failed");
  static_cast<void>(publish_session_image(linked,pair.new_image));check(!std::filesystem::is_symlink(linked),"publication failed to replace symlink entry");
  assert_epoch(pair,ordinary,1);assert_epoch(pair,linked,2);
  std::cout<<"file temporary/destination collision and symlink-entry replacement passed\n";
}
struct ChangeFile {
  const char* path;
  unsigned kind;
  bool changed=false,attempted=false;
  static testing::FileDecision call(const testing::FileEvent& event,void* pointer) noexcept {
    auto& self=*static_cast<ChangeFile*>(pointer);
    if(event.after && event.stage==FileStage::stat_read && !self.attempted) {
      self.attempted=true;const int fd=::open(self.path,O_WRONLY|O_CLOEXEC);
      if(fd>=0) {
        if(self.kind==0)self.changed=::ftruncate(fd,0)==0;
        else if(self.kind==1){const auto end=::lseek(fd,0,SEEK_END);const char value='x';self.changed=end>=0 && ::write(fd,&value,1)==1;}
        else {const char value='x';self.changed=::pwrite(fd,&value,1,static_cast<off_t>(400))==1;}
        static_cast<void>(::close(fd));
      }
    }
    return {};
  }
};
void changing_files() {
  Directory directory;Pair pair(false);const auto path=directory.file();
  for(unsigned kind=0;kind<3;++kind) {
    static_cast<void>(publish_session_image(path,pair.new_image));ChangeFile change{path.c_str(),kind};const auto fds=descriptors();bool rejected=false;
    testing::set_file_hook(ChangeFile::call,&change);
    try{auto value=QuerySession::restore_file(pair.compiler,path);}catch(const FileFailure&){rejected=true;}catch(const ImageFailure&){rejected=true;}
    Hook::clear();check(change.changed && rejected && descriptors()==fds,"concurrent truncation/growth/overwrite accepted or leaked");
  }
  static_cast<void>(publish_session_image(path,pair.new_image));Hook trace;
  {Installed hook(trace);auto value=QuerySession::restore_file(pair.compiler,path);}
  const auto event=std::find_if(trace.events.begin(),trace.events.begin()+static_cast<std::ptrdiff_t>(trace.size),[](const auto& e){return !e.after && e.stage==FileStage::read_data;});
  check(event!=trace.events.begin()+static_cast<std::ptrdiff_t>(trace.size),"read EINTR trace missing");Hook interrupted;interrupted.fail_at=event->ordinal;interrupted.error=EINTR;
  {Installed hook(interrupted);auto value=QuerySession::restore_file(pair.compiler,path);check(value->status().committed_sequence==2,"EINTR read did not retain position");}
  std::cout<<"file changing-length/content and EINTR-read rejection/continuity passed\n";
}
void cleanup_failures() {
  Directory directory;const auto path=directory.file();Pair pair(false);Hook trace;
  {Installed hook(trace);static_cast<void>(publish_session_image(path,pair.new_image));}
  const auto event=std::find_if(trace.events.begin(),trace.events.begin()+static_cast<std::ptrdiff_t>(trace.size),[](const auto& e){return !e.after && e.stage==FileStage::write_data;});
  check(event!=trace.events.begin()+static_cast<std::ptrdiff_t>(trace.size),"cleanup write trace missing");
  for(const int error:{EACCES,EINTR}) {
    static_cast<void>(publish_session_image(path,pair.old_image));const auto fds=descriptors();Hook fault;fault.fail_at=event->ordinal;fault.cleanup_error=error;bool rejected=false;
    {Installed hook(fault);try{static_cast<void>(publish_session_image(path,pair.new_image));}
      catch(const FileFailure& failure){rejected=failure.publication()==PublicationState::not_published && failure.temporary_cleanup_failed() && failure.stage()==FileStage::write_data;}}
    check(rejected && descriptors()==fds && temporaries(directory)==1,"cleanup failure was hidden or leaked descriptor");assert_epoch(pair,path,1);remove_temporaries(directory);
  }
  std::cout<<"file bounded cleanup failure reporting and old-artifact retention passed\n";
}
}
int main(int argc,char** argv) {
  try {check(argc==2,"file fault mode missing");if(std::string_view(argv[1])=="collisions"){namespace_collisions();return 0;}
    if(std::string_view(argv[1])!="crash"){namespace_collisions();changing_files();cleanup_failures();}
    for(const bool indexed:{false,true}){if(std::string_view(argv[1])=="crash")crashes(indexed);else io_faults(indexed);}}
  catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
