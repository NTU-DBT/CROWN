#pragma once

#include "crown/runtime/session_generation.hpp"

namespace crown::runtime {
// Owns the actual root lock and receiving account while caller/compiler IO
// decodes the selected immutable input. Consumed by native session admission;
// this is not an unlocked inspection result or a caller-selected plan token.
class LockedGenerationRecovery {
 public:
  using Owner=resource::AccountedUnique<LockedGenerationRecovery>;
  ~LockedGenerationRecovery();
  LockedGenerationRecovery(const LockedGenerationRecovery&)=delete;
  LockedGenerationRecovery& operator=(const LockedGenerationRecovery&)=delete;
  [[nodiscard]] bool has_plan() const noexcept;
  // Borrowed selected bytes; no compilation or independent ownership here.
  [[nodiscard]] std::string_view compiler_artifact() const & noexcept;
  std::string_view compiler_artifact() const &&=delete;
  [[nodiscard]] resource::MemoryStatistics accounted_memory_statistics() const;
 private:
  friend class QuerySession;
  struct Data;
  explicit LockedGenerationRecovery(resource::AccountedUnique<Data>) noexcept;
  resource::AccountedUnique<Data> data_;
};
} // namespace crown::runtime
