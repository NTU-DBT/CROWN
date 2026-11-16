#pragma once

#include "crown/frontend/normalize.hpp"
#include <map>

namespace crown::frontend {
using SupportCounts = std::map<Row, std::uint64_t>;
struct OccurrenceTransition { OccurrenceId occurrence; SetDelta delta; };
struct AdaptedEpoch {
  std::uint64_t sequence;
  bool input_changed;
  std::vector<OccurrenceTransition> occurrences;
};

// Correctness-first adapter state, independent of the maintained join runtime.
// Full physical row identity is retained. A public physical update commits all
// affected aliases together, after constraint checks and output allocation.
// Each apply copies physical, logical and support state, including valid no-ops;
// this reference adapter does not carry the native runtime's update cost bound.
class AdapterState {
 public:
  AdapterState(NormalizedSql query, Database physical);
  [[nodiscard]] AdaptedEpoch apply(const PhysicalSetUpdate& update);
  [[nodiscard]] const NormalizedSql& query() const noexcept { return query_; }
  [[nodiscard]] const Database& physical() const noexcept { return physical_; }
  [[nodiscard]] const Database& logical() const noexcept { return logical_; }
  [[nodiscard]] const std::vector<SupportCounts>& supports() const noexcept { return supports_; }
  [[nodiscard]] std::uint64_t sequence() const noexcept { return sequence_; }
 private:
  NormalizedSql query_;
  Database physical_;
  Database logical_;
  std::vector<SupportCounts> supports_;
  std::uint64_t sequence_ = 0;
};
}  // namespace crown::frontend
