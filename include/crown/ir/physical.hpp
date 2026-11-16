#pragma once

#include "crown/frontend/normalize.hpp"
#include "crown/io/identity.hpp"
#include "crown/planner/verify.hpp"
#include "crown/storage/layout.hpp"
#include "crown/storage/backend.hpp"
#include <memory>
#include <span>
#include <string_view>

namespace crown {
namespace planner { class Lowering; }
class CompiledProgram;
enum class PhysicalRoute { tree, constant_true, constant_false };
enum class RelationRole { physical_base, native_records, generalized_candidates, survivors, parent_support, visible };
enum class IndexUse { reverse_child_support, visible_enumeration };
struct PhysicalRelation {
  RelationId id;
  RelationRole role;
  storage::TupleLayout layout;
  std::optional<NodeId> node;
  std::optional<TableId> base;
};
struct IndexRequirement {
  IndexRequirementId id;
  RelationId relation;
  storage::Projection projection;
  std::vector<IndexUse> uses;
};
struct InputEquality { FieldId left; FieldId right; };
struct InputConstant { FieldId field; Value value; };
struct PhysicalInput {
  OccurrenceId occurrence;
  NodeId node;
  TableId base;                 // Original physical catalog, including SQL aliases.
  TableId logical_table;        // Core catalog before numeric CQ filtering/projection.
  storage::TupleLayout physical_layout;
  storage::Projection projection;
  std::vector<InputEquality> equalities;
  std::vector<InputConstant> constants;
};
struct PhysicalNode {
  NodeId id;
  NodeKind kind;
  std::optional<OccurrenceId> occurrence;
  std::optional<NodeId> parent;
  std::vector<NodeId> children;
  std::vector<VariableId> scope;
  std::vector<VariableId> visible_scope;
  bool connex;
  storage::TupleLayout layout;
  storage::Projection parent_key;
  std::optional<storage::Projection> visible_projection;
  RelationId records;           // Native records or generalized candidate union.
  RelationId survivors;
  RelationId parent_support;
  std::optional<RelationId> visible_relation;
};
struct PhysicalEdge {
  NodeId parent;
  NodeId child;
  std::size_t child_slot;
  storage::Projection parent_key;
  std::optional<IndexRequirementId> reverse_index;
};
struct AssignmentSlot { std::size_t step; FieldId field; };
struct AssignmentEquality { AssignmentSlot left; AssignmentSlot right; };
struct EnumerationStep {
  NodeId node;
  RelationId relation;
  std::size_t depth;
  std::optional<std::size_t> parent_step;
  std::optional<storage::Projection> parent_key;
  std::optional<IndexRequirementId> bucket_index;
};
struct EnumerationProgram {
  std::vector<EnumerationStep> steps;   // Parent-before-child order over C* only.
  std::vector<AssignmentSlot> output;  // Original ordered/repeated core head.
  std::vector<AssignmentEquality> equalities;
  std::size_t depth = 0;
};
// Work and identity limits count selected checkpoints; neither caps elapsed time
// or allocator bytes, and tree validation/serialization have separate costs.
struct PhysicalLimits {
  std::optional<std::uint64_t> work_limit = 1000000;
  io::IdentityLimits identity;
};
struct PhysicalOptions {
  io::CachePolicy policy;
  PhysicalLimits limits;
  // Absent preserves the exact reference v1 format and binding.
  std::optional<storage::IndexedBackendSpec> indexed_storage;
};
struct GuaranteeProfile {
  // These are compile-time capabilities. No maintained runtime or cursor
  // performance bound is implied by constructing a physical plan.
  std::string semantics = "exact_set";
  std::string query_class = "free_connex";
  std::string update_contract = "physical_full_row_set_events";
  std::string arithmetic = "exact-nonnull-v1";
  std::string storage_backend = "reference_ordered_v1";
  std::string execution_status = "lowered_not_started";
  std::string height_status = "valid_upper_bound";
  std::string state_bound = "runtime_not_implemented";
  std::string maintenance_bound = "runtime_not_implemented";
  std::string cursor_startup_bound = "runtime_not_implemented";
  std::string cursor_delay_bound = "runtime_not_implemented";
  std::string cursor_termination_bound = "runtime_not_implemented";
  std::vector<std::string> operation_modes = {"compile_only", "reference_storage_initialization"};
  std::vector<std::string> assumptions = {"single_writer", "nonnull_exact_binary_values", "ordered_standard_containers"};
  std::vector<std::string> output_accounting = {"one_action_per_emitted_tuple", "retained_snapshots_and_buffers_accounted_separately"};
};

class PhysicalPlan {
 public:
  // Explicit caller-owned export of an immutable native program. Ordinary
  // payload is copied; layout/projection handles share account-backed metadata.
  // It establishes no new proof or import authority.
  [[nodiscard]] static PhysicalPlan from_compiled(const CompiledProgram&);
  PhysicalPlan(const PhysicalPlan&) noexcept = default;
  PhysicalPlan(PhysicalPlan&&) noexcept = default;
  PhysicalPlan& operator=(const PhysicalPlan&) noexcept = default;
  PhysicalPlan& operator=(PhysicalPlan&&) noexcept = default;
  [[nodiscard]] PhysicalRoute route() const;
  [[nodiscard]] const Catalog& catalog() const;
  [[nodiscard]] const Catalog& source_catalog() const;
  [[nodiscard]] const Query& query() const;
  [[nodiscard]] const FreeConnexTree& tree() const;
  [[nodiscard]] const std::optional<frontend::NormalizedSql>& normalized() const;
  [[nodiscard]] const planner::ValidationReport& validation() const;
  [[nodiscard]] const io::QueryIdentity& identity() const;
  [[nodiscard]] const std::string& physical_sha256() const;
  // Prepared compiler identity, reused by native candidate lowering. This does
  // not require serializing or copying the source after query admission.
  [[nodiscard]] std::string_view physical_source_sha256() const;
  [[nodiscard]] const PhysicalOptions& options() const;
  [[nodiscard]] const GuaranteeProfile& guarantee() const;
  [[nodiscard]] const std::vector<storage::TupleLayout>& layouts() const;
  [[nodiscard]] const std::vector<PhysicalRelation>& relations() const;
  [[nodiscard]] const std::vector<IndexRequirement>& indexes() const;
  [[nodiscard]] const std::vector<PhysicalInput>& inputs() const;
  [[nodiscard]] const std::vector<std::vector<OccurrenceId>>& base_routes() const;
  [[nodiscard]] const std::vector<PhysicalNode>& nodes() const;
  [[nodiscard]] const std::vector<PhysicalEdge>& edges() const;
  [[nodiscard]] const EnumerationProgram& enumeration() const;
  [[nodiscard]] const storage::TupleLayout& result_layout() const;
  [[nodiscard]] std::uint64_t work() const;
  // Execute only compiled input/assembly programs, not join maintenance.
  [[nodiscard]] std::optional<storage::Tuple> adapt_input(OccurrenceId occurrence, const Row& row) const;
  [[nodiscard]] storage::Tuple assemble_result(std::span<const storage::Tuple> assignments) const;
 private:
  friend class planner::Lowering;
  struct Data;
  explicit PhysicalPlan(std::shared_ptr<const Data> data);
  [[nodiscard]] const Data& data() const;
  std::shared_ptr<const Data> data_;
};
}  // namespace crown
