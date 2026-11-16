#pragma once

#include "crown/runtime/sql_rows.hpp"
#include "storage_work.hpp"

namespace crown::runtime::detail {
// Concrete closed bridge for fresh SQL owners. No live mutation/bypass port is
// exported; every definition stays next to the actual opaque owner's Data.
class SqlColdRebuild {
 public:
  [[nodiscard]] static CompiledProgram freeze(const resource::MemoryAccount&,
      const PhysicalPlan&,storage::IndexWorkAllowance*);
  [[nodiscard]] static storage::AccountedPlanStorage storage(const CompiledProgram&,
      storage::IndexWorkAllowance*);
  [[nodiscard]] static WeightedRuntime native(const resource::MemoryAccount&,const PhysicalPlan&,
      weighted::Options,const std::shared_ptr<StorageWorkContext>&,std::uint64_t base);
  static void close_native(WeightedRuntime&,weighted::Options);
  [[nodiscard]] static std::shared_ptr<StorageWorkContext> context(const resource::MemoryAccount&,
      const sql_rows::SourceSnapshot&,const sql_rows::RebuildLimits&);
  [[nodiscard]] static SqlRowsRuntime empty(const resource::MemoryAccount&,const sql_rows::SourceSnapshot&,
      frontend::SqlRowsProgram,sql_rows::Options,const sql_rows::RebuildLimits&,const std::shared_ptr<StorageWorkContext>&,
      storage::IndexWorkAllowance&,sql_rows::RebuildMetrics&);
  [[nodiscard]] static SqlRowsRuntime::PreparedBatch seed(SqlRowsRuntime&,const sql_rows::SourceSnapshot&,
      storage::IndexWorkAllowance&,weighted::DeltaCapture);
  static void close_source(SqlRowsRuntime&,sql_rows::Options);
};
}  // namespace crown::runtime::detail
