#pragma once

#include "crown/ir/physical.hpp"
#include "crown/storage/reference.hpp"

namespace crown::storage {
// Empty storage instantiated exclusively from an immutable validated plan.
// Internal backend access, not a public query-update/epoch API.
class ReferencePlanStorage {
 public:
  explicit ReferencePlanStorage(PhysicalPlan plan);
  ReferencePlanStorage(const ReferencePlanStorage&) = delete;
  ReferencePlanStorage& operator=(const ReferencePlanStorage&) = delete;
  ReferencePlanStorage(ReferencePlanStorage&&) noexcept = default;
  ReferencePlanStorage& operator=(ReferencePlanStorage&& other) noexcept;
  [[nodiscard]] const PhysicalPlan& plan() const noexcept { return plan_; }
  [[nodiscard]] ReferenceTable& table(RelationId relation);
  [[nodiscard]] const ReferenceTable& table(RelationId relation) const;
  [[nodiscard]] IndexId index(IndexRequirementId requirement) const;
  // Full owning reference copy with fresh backend owners, preserving live
  // tuple/index IDs and counters. Cost includes all rows/index memberships.
  [[nodiscard]] ReferencePlanStorage snapshot_copy() const;
  void check_invariants() const;
 private:
  ReferencePlanStorage(PhysicalPlan plan, std::vector<ReferenceTable> tables, std::vector<IndexId> indexes);
  PhysicalPlan plan_;
  std::vector<ReferenceTable> tables_;
  std::vector<IndexId> indexes_;
};
}  // namespace crown::storage
