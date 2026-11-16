#pragma once

#include "crown/recovery/session_file.hpp"
#include <array>
#include <sys/stat.h>

namespace crown::recovery::detail {
inline constexpr std::size_t file_path_capacity=4096,session_preamble_size=316;
class FileDescriptor {
 public:
  FileDescriptor() noexcept=default;
  ~FileDescriptor();
  FileDescriptor(const FileDescriptor&)=delete;
  FileDescriptor& operator=(const FileDescriptor&)=delete;
  [[nodiscard]] int get() const noexcept {return fd_;}
  void reset(int value=-1) noexcept;
  [[nodiscard]] int release() noexcept {const int value=fd_;fd_=-1;return value;}
 private:
  int fd_=-1;
};
struct FileIo {
  CheckpointFileLimits limits;
  std::uint64_t operations=0;
  PublicationState publication=PublicationState::not_published;
  [[nodiscard]] std::int64_t call(FileStage,std::size_t,int fd,const char* name=nullptr,
      int other_fd=-1,const char* other_name=nullptr,void* buffer=nullptr,struct stat* status=nullptr);
};
// Stack-only path/fd/preamble state. Loading allocates exactly one receiving-
// account byte buffer, then runtime/source/window decode uses that same owner.
class SessionFileReader {
 public:
  SessionFileReader(std::string_view,CheckpointFileLimits);
  [[nodiscard]] std::uint64_t memory_limit_bytes() const noexcept {return memory_limit_;}
  // Consume once; reconstruct after read progress or descriptor release fails.
  [[nodiscard]] ImageVector<char> read(const resource::MemoryAccount&);
 private:
  FileIo io_;
  FileDescriptor directory_,file_;
  struct stat original_{};
  std::array<char,session_preamble_size> prefix_{};
  std::size_t size_=0;
  std::uint64_t memory_limit_=0;
};
} // namespace crown::recovery::detail
