#pragma once

#include "crown/recovery/session_image.hpp"

namespace crown::recovery {
enum class PublicationState { not_published, unknown, published_unsynced, durable };
enum class FileStage {
  path,open_directory,entropy,create_temporary,write_data,sync_file,close_file,
  rename_file,sync_directory,close_directory,open_read,stat_read,read_data,close_read,unlink_temporary
};
enum class FileFault { io,limit,path,not_regular,changed,truncated };
class FileFailure final:public std::exception {
 public:
  FileFailure(FileFault fault,FileStage stage,PublicationState state,int native_error=0,bool cleanup_failed=false) noexcept
      :fault_(fault),stage_(stage),state_(state),native_error_(native_error),cleanup_failed_(cleanup_failed) {}
  [[nodiscard]] FileFault fault() const noexcept {return fault_;}
  [[nodiscard]] FileStage stage() const noexcept {return stage_;}
  [[nodiscard]] PublicationState publication() const noexcept {return state_;}
  [[nodiscard]] int native_error() const noexcept {return native_error_;}
  [[nodiscard]] bool temporary_cleanup_failed() const noexcept {return cleanup_failed_;}
  [[nodiscard]] const char* what() const noexcept override {return "checkpoint file operation failed";}
 private:
  FileFault fault_;
  FileStage stage_;
  PublicationState state_;
  int native_error_;
  bool cleanup_failed_;
};
struct CheckpointFileLimits {
  SessionImageLimits image;
  std::size_t path_bytes=4095,chunk_bytes=1024*1024;
  std::uint64_t operations=1000000;
};
struct PublishedCheckpoint {
  SessionImageManifest manifest;
  std::uint64_t bytes=0,operations=0;
  PublicationState publication=PublicationState::durable;
};
// Linux local-file publication: exclusive sibling temporary, complete write,
// file fsync/checked close, atomic rename, parent-directory fsync/checked close.
// A rename error has unknown publication status. Directory-sync failure after
// successful rename leaves a complete visible file with unconfirmed durability.
// The existing parent namespace must be trusted against external edits to the
// writer's private temporary entries. Names are opaque non-NUL bytes; the final entry is
// replaced, never followed. A matching Program is still required for restore.
[[nodiscard]] PublishedCheckpoint publish_session_image(std::string_view path,const SessionImage&,
    const runtime::SessionCheckpointLimits& = {},CheckpointFileLimits={});
} // namespace crown::recovery
