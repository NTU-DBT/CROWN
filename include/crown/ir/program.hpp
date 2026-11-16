#pragma once

#include "crown/ir/program_model.hpp"
#include "crown/storage/accounted_plan.hpp"
#include "crown/storage/index_work.hpp"
#include <exception>

namespace crown {
namespace runtime::detail { class SqlColdRebuild; }
namespace planner {class MinimumHeightCandidate;}
namespace program {
namespace detail {class NativeLowering;}
enum class InputExecution {interpreted_v1,threaded_v1};
struct InputPreparationLimits {
  std::uint64_t work=1'000'000;
  std::size_t instructions=100'000;
};
struct InputPreparationUsage {
  std::uint64_t work=0;
  std::size_t instructions=0;
  // Only allocated instruction/range table capacity; excludes Data/control
  // blocks and the base receiving copy, all still charged to the account.
  std::size_t metadata_bytes=0;
  storage::IndexWork base_freeze_work{};
};
struct ReplanLimits {
  PhysicalLimits physical;
  std::optional<std::uint64_t> binding_replay_work=1'000'000;
  std::optional<std::uint64_t> normalization_work=1'000'000;
};
enum class ReplanFault {binding,lowering_work,identity_work,binding_replay_work,normalization_work};
class ReplanFailure final:public std::exception {
 public:
  explicit ReplanFailure(ReplanFault value) noexcept:value_(value) {}
  [[nodiscard]] ReplanFault fault() const noexcept {return value_;}
  [[nodiscard]] const char* what() const noexcept override {return "native candidate lowering failed";}
 private:ReplanFault value_;
};
}

// Immutable executable metadata: admission owns copied payload and tokens.
// Replanning retains the canonical source for shared views. tree()/validation()
// describe the executable operator; the candidate retains its original proof.
class CompiledProgram {
  struct Data;
 public:
  CompiledProgram() noexcept=default;
  [[nodiscard]] static CompiledProgram freeze(const resource::MemoryAccount&,
      const PhysicalPlan&,storage::IndexWorkAllowance* =nullptr);
  // Native compiler/cache input admission: all text/arrays/tokens are copied
  // into the receiving runtime's original account, without a legacy export.
  [[nodiscard]] static CompiledProgram freeze(const resource::MemoryAccount&,
      const CompiledProgram&,storage::IndexWorkAllowance* =nullptr);
  // Compiler/tool ownership, before an execution account exists. Execution
  // owners instead freeze directly into their original query account/grant.
  [[nodiscard]] static CompiledProgram standalone(const PhysicalPlan&);
  // Initial compiler artifact, with new payload charged to the supplied
  // component account. Runtime admission still uses freeze and its one grant.
  [[nodiscard]] static CompiledProgram compile(const resource::MemoryAccount&,const PhysicalPlan&);
  // Cold automatic specialization of an admitted program, with no caller code
  // or instructions. New metadata and the base copy use the receiving account.
  // Denial leaves source unchanged. Physical/source identities do not change.
  // Requires a SQL-normalized source; plain CQ programs keep their interpreter.
  [[nodiscard]] static CompiledProgram prepare_inputs(const resource::MemoryAccount&,
      const CompiledProgram&,const program::InputPreparationLimits& = {},
      storage::IndexWorkAllowance* =nullptr);
  [[nodiscard]] program::InputExecution input_execution() const;
  [[nodiscard]] std::string_view input_execution_key() const;
  [[nodiscard]] program::InputPreparationUsage input_preparation() const;
  [[nodiscard]] std::optional<program::InputPreparationLimits> input_preparation_limits() const;
  // Lower checked candidate structure directly into the basis's original query
  // account. Immutable admitted source/identity fields alias the retained basis.
  [[nodiscard]] static CompiledProgram replan(const CompiledProgram&,
      const planner::MinimumHeightCandidate&,const program::ReplanLimits& = {});
  // An explicitly supplied compiler basis is immutable input. New graph and
  // scratch storage belongs to the receiving query's existing account.
  [[nodiscard]] static CompiledProgram replan_into(const resource::MemoryAccount&,const CompiledProgram&,
      const planner::MinimumHeightCandidate&,const program::ReplanLimits& = {});
  [[nodiscard]] explicit operator bool() const noexcept {return bool(data_);}
  [[nodiscard]] const resource::MemoryAccount& account() const &;
  const resource::MemoryAccount& account() const &&=delete;
  [[nodiscard]] PhysicalRoute route() const;
  [[nodiscard]] const program::Catalog& catalog() const &;
  const program::Catalog& catalog() const &&=delete;
  [[nodiscard]] const program::Catalog& source_catalog() const &;
  const program::Catalog& source_catalog() const &&=delete;
  // Aliases the existing accounted program control; creates no mirror/control.
  [[nodiscard]] std::shared_ptr<const program::Catalog> source_catalog_owner() const;
  [[nodiscard]] const program::Query& query() const &;
  const program::Query& query() const &&=delete;
  [[nodiscard]] const program::FreeConnexTree& tree() const &;
  const program::FreeConnexTree& tree() const &&=delete;
  [[nodiscard]] const std::optional<program::NormalizedSql>& normalized() const &;
  const std::optional<program::NormalizedSql>& normalized() const &&=delete;
  [[nodiscard]] const program::ValidationReport& validation() const &;
  const program::ValidationReport& validation() const &&=delete;
  [[nodiscard]] const program::QueryIdentity& identity() const &;
  const program::QueryIdentity& identity() const &&=delete;
  [[nodiscard]] std::string_view physical_sha256() const &;
  std::string_view physical_sha256() const &&=delete;
  [[nodiscard]] std::string_view physical_source_sha256() const &;
  std::string_view physical_source_sha256() const &&=delete;
  [[nodiscard]] const program::PhysicalOptions& options() const &;
  const program::PhysicalOptions& options() const &&=delete;
  [[nodiscard]] const program::GuaranteeProfile& guarantee() const &;
  const program::GuaranteeProfile& guarantee() const &&=delete;
  [[nodiscard]] const program::Span<storage::AccountedLayout>& layouts() const &;
  const program::Span<storage::AccountedLayout>& layouts() const &&=delete;
  [[nodiscard]] const program::Span<program::PhysicalRelation>& relations() const &;
  const program::Span<program::PhysicalRelation>& relations() const &&=delete;
  [[nodiscard]] const program::Span<program::IndexRequirement>& indexes() const &;
  const program::Span<program::IndexRequirement>& indexes() const &&=delete;
  [[nodiscard]] const program::Span<program::PhysicalInput>& inputs() const &;
  const program::Span<program::PhysicalInput>& inputs() const &&=delete;
  [[nodiscard]] const program::Span<program::Span<OccurrenceId>>& base_routes() const &;
  const program::Span<program::Span<OccurrenceId>>& base_routes() const &&=delete;
  [[nodiscard]] const program::Span<program::PhysicalNode>& nodes() const &;
  const program::Span<program::PhysicalNode>& nodes() const &&=delete;
  [[nodiscard]] const program::Span<program::PhysicalEdge>& edges() const &;
  const program::Span<program::PhysicalEdge>& edges() const &&=delete;
  [[nodiscard]] const program::EnumerationProgram& enumeration() const &;
  const program::EnumerationProgram& enumeration() const &&=delete;
  [[nodiscard]] const storage::AccountedLayout& result_layout() const &;
  const storage::AccountedLayout& result_layout() const &&=delete;
  [[nodiscard]] const storage::AccountedLayout& sql_result_layout() const &;
  const storage::AccountedLayout& sql_result_layout() const &&=delete;
  [[nodiscard]] const program::Span<program::SourceTable>& sources() const &;
  const program::Span<program::SourceTable>& sources() const &&=delete;
  [[nodiscard]] storage::AccountedLayout scope_layout(LayoutId,std::span<const VariableId>,
      std::string_view binding_suffix,storage::IndexWorkAllowance* =nullptr) const;
  [[nodiscard]] std::uint64_t work() const;
  [[nodiscard]] storage::AccountedPlanStorage make_storage(storage::IndexWorkAllowance* =nullptr) const;
  [[nodiscard]] std::optional<storage::AccountedTuple> adapt_input(OccurrenceId,
      storage::RowView,storage::IndexWorkAllowance* =nullptr) const;
 private:
  friend class runtime::detail::SqlColdRebuild;
  [[nodiscard]] static CompiledProgram freeze_impl(const resource::MemoryAccount&,
      const PhysicalPlan&,storage::IndexWorkAllowance*,storage::MetadataWork);
  [[nodiscard]] static CompiledProgram freeze_program(const resource::MemoryAccount&,
      const CompiledProgram&,storage::IndexWorkAllowance*,
      const std::optional<program::InputPreparationLimits>&);
  friend class program::detail::Builder;
  friend class program::detail::NativeLowering;
  explicit CompiledProgram(std::shared_ptr<const Data> data) noexcept:data_(std::move(data)) {}
  [[nodiscard]] const Data& data() const;
  std::shared_ptr<const Data> data_;
};
} // namespace crown
