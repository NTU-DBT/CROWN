#pragma once

#include "crown/api/error.hpp"
#include <exception>
#include <string_view>

namespace crown::storage {
enum class IndexFault { contract, capacity, overflow, work_limit, layout_mismatch,
  foreign_handle, unknown_index, stale_handle, busy, invalid_storage, invalid_journal, invalid_cursor };
// The carrier owns no dynamic diagnostic text; throwing still uses the
// implementation's exception-runtime storage.
class IndexFailure final : public std::exception {
 public:
  explicit IndexFailure(IndexFault fault) noexcept : fault_(fault) {}
  [[nodiscard]] std::string_view code() const noexcept {
    switch (fault_) {
      case IndexFault::contract: return "storage_contract";
      case IndexFault::capacity: return "storage_capacity";
      case IndexFault::overflow: return "storage_overflow";
      case IndexFault::work_limit: return "storage_work_limit";
      case IndexFault::layout_mismatch: return "layout_mismatch";
      case IndexFault::foreign_handle: return "foreign_handle";
      case IndexFault::unknown_index: return "unknown_index";
      case IndexFault::stale_handle: return "stale_handle";
      case IndexFault::busy: return "storage_busy";
      case IndexFault::invalid_storage: return "invalid_storage";
      case IndexFault::invalid_journal: return "invalid_journal";
      case IndexFault::invalid_cursor: return "invalid_cursor";
    }
    return "storage_contract";
  }
  [[nodiscard]] const char* what() const noexcept override { return code().data(); }
 private:
  IndexFault fault_;
};
namespace detail {
struct LegacyIndexErrors {
  [[noreturn]] static void fail(IndexFault fault, const char* message) {
    throw Error(std::string(IndexFailure(fault).code()), message);
  }
};
struct FixedIndexErrors {
  [[noreturn]] static void fail(IndexFault fault, const char*) { throw IndexFailure(fault); }
};
}
}
