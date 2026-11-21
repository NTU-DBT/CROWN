#pragma once

#include "crown/recovery/sql_aggregate_files.hpp"
#include <sys/stat.h>

namespace crown::recovery::sql_aggregate::file_detail {
[[noreturn]] void fail(FileFault,FileStage,FileOutcome,int=0);
void raw_close(int) noexcept;
// Stack descriptor guard for directory handles; explicit release enables one
// checked close without accidentally retrying Linux close after EINTR.
struct Directory {
  int fd=-1;
  Directory()=default;
  Directory(const Directory&)=delete;
  Directory& operator=(const Directory&)=delete;
  Directory(Directory&&) noexcept;
  ~Directory();
  int release() noexcept;
};
// Fixed path split: no unaccounted owning string, embedded NUL or empty basename.
struct Path {
  std::array<char,4096> parent{},name{};
  Path(std::string_view,const FileLimits&);
};
[[nodiscard]] std::string_view view(const ImageVector<char>&) noexcept;
void binding(const Descriptor&,const Binding&);
// Validate all available envelope bytes before trusting a stored body length.
// A complete envelope authenticates its protected length before any resize.
[[nodiscard]] std::uint64_t envelope(std::string_view,const Limits&,
    std::string_view magic="CROWNAG2");
void tail(std::string_view,std::uint64_t ordinal,bool input,bool decision,bool group);
[[nodiscard]] Hash chain(const Hash&,const char* prefix_sha256);

// Shared R2 regular-file I/O. The eight-byte magic selects only framing; typed
// callers separately validate every complete SQL row/group record. No source
// rows, native tokens, undo state or retry queue belongs to this file primitive.
struct Io {
  explicit Io(FileLimits,std::string_view magic="CROWNAG2");
  ~Io();
  Io(const Io&)=delete;
  Io& operator=(const Io&)=delete;
  FileLimits limits;
  std::array<char,8> magic;
  int fd=-1;
  struct stat stamp{};
  // operations is the lifetime syscall ordinal; FileLimits::operations bounds the
  // syscalls of one call (or one scanned frame) counted from budget_base.
  std::uint64_t operations=0,work=0,budget_base=0;
  void rebase() noexcept {budget_base=operations;}
  FileOutcome outcome=FileOutcome::unchanged;
  bool poisoned=false,torn=false;
  void ready() const;
  void consume(std::uint64_t);
  [[nodiscard]] Limits record_limits() const;
  [[nodiscard]] FileStatistics statistics() const noexcept;
  // Create installs one synced header without replacing any existing entry.
  // Open only locks/stats; caller scans, then finish_open syncs validated bytes.
  void create(const Path&,std::string_view header);
  [[nodiscard]] Directory open(const Path&);
  void finish_open(Directory&);
  // Returns a complete frame or a validated partial envelope/body, using one
  // receiving-account scratch. Caller validates available kind/ordinal on tail.
  [[nodiscard]] bool read_frame(std::uint64_t,ImageVector<char>&);
  void unchanged();
  void validate();
  void refresh();
  void read(char*,std::size_t,std::uint64_t);
  void append(std::string_view,std::uint64_t);
  void repair(std::uint64_t);
  void close();
 private:
  std::int64_t call(FileStage,std::size_t=0,int=-1,const char* =nullptr,
      int=-1,const char* =nullptr,void* =nullptr,std::uint64_t=0,struct stat* =nullptr,bool emergency_cleanup=false);
  std::int64_t checked(FileStage,std::size_t=0,int=-1,const char* =nullptr,
      int=-1,const char* =nullptr,void* =nullptr,std::uint64_t=0,struct stat* =nullptr);
  void transfer(bool,char*,std::size_t,std::uint64_t);
  bool cleanup(int,const char*) noexcept;
};
} // namespace crown::recovery::sql_aggregate::file_detail
