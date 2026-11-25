#pragma once
// Small POSIX portability layer for the recovery file code.
// Linux exposes nanosecond timestamps as st_mtim/st_ctim and provides getrandom();
// macOS/BSD use st_mtimespec/st_ctimespec and getentropy() (at most 256 bytes per call).
#include <cstddef>
#include <cstdint>
#include <sys/random.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace crown::recovery::posix {

[[nodiscard]] inline const struct timespec& modification_time(const struct stat& status) noexcept {
#if defined(__APPLE__)
  return status.st_mtimespec;
#else
  return status.st_mtim;
#endif
}

[[nodiscard]] inline const struct timespec& change_time(const struct stat& status) noexcept {
#if defined(__APPLE__)
  return status.st_ctimespec;
#else
  return status.st_ctim;
#endif
}

// Identity check used before trusting a previously opened file: same inode, size and
// nanosecond modification/change times.
[[nodiscard]] inline bool same_file_state(const struct stat& a, const struct stat& b) noexcept {
  const auto& am = modification_time(a); const auto& bm = modification_time(b);
  const auto& ac = change_time(a); const auto& bc = change_time(b);
  return a.st_dev == b.st_dev && a.st_ino == b.st_ino && a.st_size == b.st_size &&
      am.tv_sec == bm.tv_sec && am.tv_nsec == bm.tv_nsec &&
      ac.tv_sec == bc.tv_sec && ac.tv_nsec == bc.tv_nsec;
}

// Nonblocking entropy with getrandom(..., GRND_NONBLOCK) semantics: returns the number of
// bytes written (possibly fewer than requested) or -1 with errno set.
[[nodiscard]] inline std::int64_t random_bytes(void* buffer, std::size_t count) noexcept {
#if defined(__APPLE__)
  const std::size_t chunk = count < 256 ? count : 256;
  if (::getentropy(buffer, chunk) != 0) return -1;
  return static_cast<std::int64_t>(chunk);
#else
  return static_cast<std::int64_t>(::getrandom(buffer, count, GRND_NONBLOCK));
#endif
}

}  // namespace crown::recovery::posix
