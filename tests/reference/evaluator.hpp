#pragma once

#include "crown/ir/model.hpp"

namespace crown::reference {
// A slow, materializing relational definition. No planner/support/cursor helpers.
[[nodiscard]] Relation evaluate(const Catalog& catalog, const Query& query, const Database& database);

class Session {
 public:
  Session(Catalog catalog, Query query, Database database);
  [[nodiscard]] Relation snapshot() const;
  [[nodiscard]] CommittedReferenceEpoch apply(const PhysicalSetUpdate& update);
  [[nodiscard]] std::uint64_t sequence() const noexcept { return sequence_; }
  [[nodiscard]] const Database& database() const noexcept { return database_; }
 private:
  Catalog catalog_;
  Query query_;
  Database database_;
  std::uint64_t sequence_ = 0;
};
}  // namespace crown::reference
