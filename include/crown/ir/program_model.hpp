#pragma once

#include "crown/ir/program_json.hpp"
#include "crown/ir/program_span.hpp"
#include "crown/storage/accounted_layout.hpp"
#include "crown/storage/accounted_projection.hpp"
#include "crown/ir/physical.hpp"

#include <cstddef>
#include <cstdint>
#include <optional>
#include <string_view>
#include <variant>

namespace crown::program {

// Read-only views over immutable native program storage. All text, spans, and
// nested views borrow storage owned elsewhere.

struct Column {
  std::string_view name;
  ScalarType type;
  bool nullable = false;
  Collation collation = Collation::binary;
  std::optional<DecimalSpec> decimal = std::nullopt;
};

struct UniqueConstraint {
  std::string_view name;
  Span<ColumnId> columns;
  ::crown::ConstraintStatus status = ::crown::ConstraintStatus::untrusted;
};
struct ForeignKeyConstraint {
  std::string_view name;
  Span<ColumnId> columns;
  TableId referenced_table;
  Span<ColumnId> referenced_columns;
  ::crown::ConstraintStatus status = ::crown::ConstraintStatus::untrusted;
};
using Constraint = std::variant<UniqueConstraint, ForeignKeyConstraint>;

struct DistinctEstimate {
  Span<ColumnId> columns;
  std::uint64_t estimate;
};
struct TableStatistics {
  std::optional<std::uint64_t> row_count = std::nullopt;
  Span<DistinctEstimate> distinct_counts;
};
struct KeyHint {
  Span<ColumnId> columns;
  std::string_view reason;
};
struct Table {
  std::string_view name;
  Span<Column> columns;
  std::uint64_t source_schema_version = 1;
  Span<Constraint> constraints;
  TableStatistics statistics;
  Span<KeyHint> key_hints;
};
struct Catalog {
  std::uint64_t version = 1;
  Span<Table> tables;
};

struct Variable {
  std::string_view name;
  ScalarType type;
};
using Term = std::variant<VariableId, storage::ScalarView, ::crown::IgnoredColumn>;
struct Atom {
  std::string_view occurrence;
  TableId table;
  Span<Term> terms;
};
struct Output {
  VariableId variable;
  std::string_view alias;
};
struct Query {
  Span<Variable> variables;
  Span<Atom> atoms;
  Span<Output> head;
  bool contradiction = false;
};

struct TreeNode {
  std::string_view id;
  NodeKind kind;
  Set<VariableId> scope;
  Span<NodeId> children;
  std::optional<std::size_t> occurrence;
  std::optional<Set<VariableId>> claimed_separator;
};
struct FreeConnexTree {
  std::optional<NodeId> root;
  Span<TreeNode> nodes;
  std::optional<Span<NodeId>> claimed_connex;
  std::optional<std::size_t> claimed_native_height;
};

struct PlanViolation {
  std::string_view rule;
  std::string_view message;
  std::optional<NodeId> node;
  std::optional<VariableId> variable;
  std::optional<std::size_t> occurrence;
  std::optional<NodeId> related_node;
};
struct ValidationReport {
  bool valid = false;
  std::optional<std::size_t> native_height;
  std::optional<std::size_t> edge_depth;
  Span<NodeId> maximal_connex;
  Span<Set<VariableId>> separators;
  Span<PlanViolation> violations;
};

struct BoundLiteral { std::optional<storage::ScalarView> value; };
using BoundColumn=frontend::BoundColumn;
using BoundParameter=frontend::BoundParameter;
struct BoundOperation {
  frontend::SqlOperator operation;
  Span<frontend::ExpressionId> arguments;
};
using BoundNode = std::variant<BoundColumn, BoundLiteral, BoundParameter, BoundOperation>;
struct BoundExpression {
  frontend::SqlType type;
  BoundNode node;
  std::optional<std::size_t> location;
};
struct BoundOccurrence {
  TableId table;
  std::string_view alias;
  Span<std::string_view> column_names;
  std::optional<std::size_t> location;
  bool include_descendants = true;
};
struct BoundOutput {
  std::string_view name;
  frontend::ExpressionId expression;
};
struct BoundSql {
  std::string_view source;
  Catalog catalog;
  Span<frontend::SqlType> parameters;
  frontend::SqlSemantics semantics = frontend::SqlSemantics::bag;
  std::optional<frontend::SqlSemantics> inner_semantics = std::nullopt;
  frontend::SqlWrapper wrapper = frontend::SqlWrapper::rows;
  std::string_view wrapper_alias = "exists";
  Span<BoundOccurrence> occurrences;
  Span<BoundExpression> expressions;
  Span<frontend::ExpressionId> predicates;
  Span<BoundOutput> outputs;
  frontend::BindLimits limits;
  std::uint64_t work = 0;
};

using SqlValue = std::optional<storage::ScalarView>;
struct ColumnConstant {
  ColumnId column;
  storage::ScalarView value;
};
struct OccurrenceAdapter {
  frontend::OccurrenceId occurrence;
  TableId base;
  Span<frontend::ExpressionId> predicates;
  Span<ColumnId> non_null_columns;
  Span<frontend::ColumnEquality> equal_columns;
  Span<std::optional<VariableId>> column_classes;
  Span<frontend::AdapterProjection> projection;
  Span<frontend::ExpressionId> program;
  Span<ColumnConstant> constant_columns;
};
struct ConstantOutput { storage::ScalarView value; };
struct NormalizedOutput {
  std::string_view name;
  frontend::SqlType type;
  std::variant<frontend::CoreOutput, ConstantOutput> value;
};
struct NormalizedSql {
  BoundSql binding;
  Span<SqlValue> parameters;
  Span<SqlValue> constants;
  Catalog core_catalog;
  Query core;
  Span<OccurrenceAdapter> adapters;
  Span<Span<frontend::OccurrenceId>> base_routes;
  Span<NormalizedOutput> outputs;
  frontend::NormalizeLimits limits;
  std::uint64_t work = 0;
  std::uint64_t schema_version = 2;
};

struct CachePolicy {
  std::string_view arithmetic = "exact-nonnull-v1";
  std::string_view planner = "crown-tree-v1";
  std::string_view optimization = "structural-height-v1";
  std::string_view cost_model = "no-cost-v1";
};
struct PhysicalOptions {
  CachePolicy policy;
  PhysicalLimits limits;
  std::optional<storage::IndexedBackendSpec> indexed_storage;
};
struct GuaranteeProfile {
  std::string_view semantics = "exact_set";
  std::string_view query_class = "free_connex";
  std::string_view update_contract = "physical_full_row_set_events";
  std::string_view arithmetic = "exact-nonnull-v1";
  std::string_view storage_backend = "reference_ordered_v1";
  std::string_view execution_status = "lowered_not_started";
  std::string_view height_status = "valid_upper_bound";
  std::string_view state_bound = "runtime_not_implemented";
  std::string_view maintenance_bound = "runtime_not_implemented";
  std::string_view cursor_startup_bound = "runtime_not_implemented";
  std::string_view cursor_delay_bound = "runtime_not_implemented";
  std::string_view cursor_termination_bound = "runtime_not_implemented";
  Span<std::string_view> operation_modes;
  Span<std::string_view> assumptions;
  Span<std::string_view> output_accounting;
};
struct QueryIdentity {
  JsonView canonical;
  std::string_view semantic_sha256;
  std::string_view output_contract_sha256;
  std::string_view cost_inputs_sha256;
  std::string_view plan_cache_sha256;
  Span<std::size_t> occurrence_order;
  Span<std::size_t> variable_order;
  std::uint64_t work;
};

struct PhysicalRelation {
  RelationId id;
  RelationRole role;
  storage::AccountedLayout layout;
  std::optional<NodeId> node;
  std::optional<TableId> base;
};
struct SourceTable {RelationId relation;storage::AccountedLayout layout;};
struct IndexRequirement {
  IndexRequirementId id;
  RelationId relation;
  storage::AccountedProjection projection;
  Span<IndexUse> uses;
};
struct InputConstant {
  FieldId field;
  storage::ScalarView value;
};
struct PhysicalInput {
  OccurrenceId occurrence;
  NodeId node;
  TableId base;
  TableId logical_table;
  storage::AccountedLayout physical_layout;
  storage::AccountedProjection projection;
  Span<InputEquality> equalities;
  Span<InputConstant> constants;
};
struct PhysicalNode {
  NodeId id;
  NodeKind kind;
  std::optional<OccurrenceId> occurrence;
  std::optional<NodeId> parent;
  Span<NodeId> children;
  Span<VariableId> scope;
  Span<VariableId> visible_scope;
  bool connex;
  storage::AccountedLayout layout;
  storage::AccountedProjection parent_key;
  std::optional<storage::AccountedProjection> visible_projection;
  RelationId records;
  RelationId survivors;
  RelationId parent_support;
  std::optional<RelationId> visible_relation;
};
struct PhysicalEdge {
  NodeId parent;
  NodeId child;
  std::size_t child_slot;
  storage::AccountedProjection parent_key;
  std::optional<IndexRequirementId> reverse_index;
};
struct EnumerationStep {
  NodeId node;
  RelationId relation;
  std::size_t depth;
  std::optional<std::size_t> parent_step;
  std::optional<storage::AccountedProjection> parent_key;
  std::optional<IndexRequirementId> bucket_index;
};
struct EnumerationProgram {
  Span<EnumerationStep> steps;
  Span<AssignmentSlot> output;
  Span<AssignmentEquality> equalities;
  std::size_t depth = 0;
};

}  // namespace crown::program
