#pragma once

#include "crown/ir/physical.hpp"
#include "crown/storage/table.hpp"
#include "crown/storage/accounted_plan.hpp"

namespace crown::storage {
// Empty internal storage follows the immutable plan's actual backend choice.
// Indexed initialization/copy borrows one aggregate grant no larger than the
// plan's declared operation allowance. No independent per-table grants exist.
// This is not a public query update/epoch API or a memory-byte guarantee.
// Standalone vectors/tables own ordinary storage; finite work admission
// here does not establish native query-account requested-byte accounting.
class PlanStorage {
 public:
  explicit PlanStorage(PhysicalPlan, IndexWorkAllowance* = nullptr);
  PlanStorage(const PlanStorage&) = delete;
  PlanStorage& operator=(const PlanStorage&) = delete;
  PlanStorage(PlanStorage&&) noexcept = default;
  PlanStorage& operator=(PlanStorage&&) noexcept = default;
  [[nodiscard]] const PhysicalPlan& plan() const noexcept { return plan_; }
  [[nodiscard]] StorageBackend backend() const;
  [[nodiscard]] StorageTable& table(RelationId);
  [[nodiscard]] const StorageTable& table(RelationId) const;
  [[nodiscard]] IndexId index(IndexRequirementId) const;
  [[nodiscard]] PlanStorage snapshot_copy(IndexWorkAllowance* = nullptr) const;
  // Full diagnostics may scan/allocate; indexed binding probes still use the
  // caller's finite grant and never invent an unbounded allowance.
  void check_invariants(IndexWorkAllowance* = nullptr) const;
 private:
  PlanStorage(PhysicalPlan, std::vector<StorageTable>, std::vector<IndexId>);
  PhysicalPlan plan_;
  std::vector<StorageTable> tables_;
  std::vector<IndexId> indexes_;
};
}  // namespace crown::storage
