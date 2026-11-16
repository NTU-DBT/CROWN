#pragma once
// Linux regular-file storage for the version-1 journal. One cooperating writer
// owns an advisory flock for its lifetime. The containing namespace is trusted.
#include "crown/recovery/journal.hpp"
#include <sys/stat.h>

namespace crown::runtime {class QuerySession;}
namespace crown::recovery::journal {
enum class FileStage : std::uint8_t {
  path,open_directory,entropy,create_temporary,open_file,stat_file,lock_file,
  read_data,write_data,sync_file,link_file,unlink_temporary,sync_directory,
  truncate_tail,close_file,close_directory,state
};
enum class FileFault : std::uint8_t {io,limit,path,not_regular,busy,changed,truncated,state};
// Outcome concerns the attempted operation. Unknown requires reopening and
// validating the surviving prefix; it never authorizes an in-place retry.
enum class FileOutcome : std::uint8_t {unchanged,unknown,durable};
class FileFailure final:public std::exception {
 public:
  FileFailure(FileFault fault,FileStage stage,FileOutcome outcome,int error=0,bool cleanup=false) noexcept
      :fault_(fault),stage_(stage),outcome_(outcome),error_(error),cleanup_(cleanup) {}
  [[nodiscard]] FileFault fault() const noexcept {return fault_;}
  [[nodiscard]] FileStage stage() const noexcept {return stage_;}
  [[nodiscard]] FileOutcome outcome() const noexcept {return outcome_;}
  [[nodiscard]] int native_error() const noexcept {return error_;}
  [[nodiscard]] bool temporary_cleanup_failed() const noexcept {return cleanup_;}
  [[nodiscard]] const char* what() const noexcept override {return "journal file operation failed";}
 private:
  FileFault fault_;FileStage stage_;FileOutcome outcome_;int error_;bool cleanup_;
};
struct FileLimits {
  ScanLimits scan;
  std::size_t path_bytes=4095,chunk_bytes=1024*1024;
  std::uint64_t operations=1'000'000;
};
class File {
  // Owns the actual descriptor/lock; copied Scanned values retain neither.
  // After validator advance and failed IO, poison forbids same-owner retry.
 public:
  // Create never replaces an existing entry, including a symlink. Header and
  // directory entry are synced before success. Open syncs a validated existing
  // file/name before returning; complete visible records become its durable prefix.
  [[nodiscard]] static File create(const resource::MemoryAccount&,std::string_view,const Header&,FileLimits={});
  [[nodiscard]] static File open(const resource::MemoryAccount&,std::string_view,const Header&,FileLimits={});
  ~File();
  File(const File&)=delete;File& operator=(const File&)=delete;
  File(File&&) noexcept;File& operator=(File&&)=delete;
  // State/pending frame borrow this owner until another operation, move or
  // destruction. Only successful durable operations
  // expose state. Destruction closes best effort; use close() for checked close.
  [[nodiscard]] Scanned state() const &;
  Scanned state() const &&=delete;
  [[nodiscard]] std::uint64_t operations() const noexcept {return operations_;}
  void append(std::string_view full_record) &;
  // Removes only a validated incomplete tail, retaining every complete input
  // and partial window commit. No committed history or pending input is retired.
  void repair_tail() &;
  void close() &;
 private:
  friend class crown::runtime::QuerySession;
  using ReplayVisitor=void(*)(std::string_view,const Scanned&,void*);
  // Visitor effects must stay private to the receiving factory until the whole
  // prefix, EOF/stamp and file/name sync complete. Throws unwind both owners.
  static File open_replay(const resource::MemoryAccount&,std::string_view,const Header&,FileLimits,ReplayVisitor,void*);
  File(const resource::MemoryAccount&,const Header&,FileLimits);
  void ready() const;
  void unchanged_file();
  void refresh();
  void retain_pending(std::uint64_t old_records);
  std::int64_t call(FileStage,std::size_t=0,int=-1,const char* =nullptr,
      int=-1,const char* =nullptr,void* =nullptr,std::uint64_t=0,struct stat* =nullptr,bool emergency_cleanup=false);
  std::int64_t checked(FileStage,std::size_t=0,int=-1,const char* =nullptr,
      int=-1,const char* =nullptr,void* =nullptr,std::uint64_t=0,struct stat* =nullptr);
  void transfer(bool write,char*,std::size_t,std::uint64_t);
  bool cleanup_temporary(int,const char*) noexcept;
  FileLimits limits_;Cursor cursor_;
  ImageVector<char> scratch_,pending_;
  int fd_=-1;
  struct stat stamp_{};
  std::uint64_t operations_=0;
  FileOutcome outcome_=FileOutcome::unchanged;
  bool poisoned_=false,torn_=false;
};
} // namespace crown::recovery::journal
