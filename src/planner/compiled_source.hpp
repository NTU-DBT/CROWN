#pragma once
#include "crown/ir/program.hpp"
#include <array>
#include <cstdint>
#include <optional>
#include <set>
#include <string>
#include <type_traits>
#include <vector>

namespace crown::planner::compiler_source_detail {
// Compile-time positional DTO map. Keep every fields count/order aligned
// with both aggregates; descriptor leaves use explicit sharing overloads.
template<class T> struct Owned {using Result=T;static constexpr std::size_t fields=0;};
template<> struct Owned<::crown::program::Column> {using Result=::crown::Column;static constexpr std::size_t fields=5;};
template<> struct Owned<::crown::program::UniqueConstraint> {using Result=::crown::UniqueConstraint;static constexpr std::size_t fields=3;};
template<> struct Owned<::crown::program::ForeignKeyConstraint> {using Result=::crown::ForeignKeyConstraint;static constexpr std::size_t fields=5;};
template<> struct Owned<::crown::program::DistinctEstimate> {using Result=::crown::DistinctEstimate;static constexpr std::size_t fields=2;};
template<> struct Owned<::crown::program::TableStatistics> {using Result=::crown::TableStatistics;static constexpr std::size_t fields=2;};
template<> struct Owned<::crown::program::KeyHint> {using Result=::crown::KeyHint;static constexpr std::size_t fields=2;};
template<> struct Owned<::crown::program::Table> {using Result=::crown::Table;static constexpr std::size_t fields=6;};
template<> struct Owned<::crown::program::Catalog> {using Result=::crown::Catalog;static constexpr std::size_t fields=2;};
template<> struct Owned<::crown::program::Variable> {using Result=::crown::Variable;static constexpr std::size_t fields=2;};
template<> struct Owned<::crown::program::Atom> {using Result=::crown::Atom;static constexpr std::size_t fields=3;};
template<> struct Owned<::crown::program::Output> {using Result=::crown::Output;static constexpr std::size_t fields=2;};
template<> struct Owned<::crown::program::Query> {using Result=::crown::Query;static constexpr std::size_t fields=4;};
template<> struct Owned<::crown::program::TreeNode> {using Result=::crown::TreeNode;static constexpr std::size_t fields=6;};
template<> struct Owned<::crown::program::FreeConnexTree> {using Result=::crown::FreeConnexTree;static constexpr std::size_t fields=4;};
template<> struct Owned<::crown::program::PlanViolation> {using Result=::crown::planner::PlanViolation;static constexpr std::size_t fields=6;};
template<> struct Owned<::crown::program::ValidationReport> {using Result=::crown::planner::ValidationReport;static constexpr std::size_t fields=6;};
template<> struct Owned<::crown::program::BoundLiteral> {using Result=::crown::frontend::BoundLiteral;static constexpr std::size_t fields=1;};
template<> struct Owned<::crown::program::BoundOperation> {using Result=::crown::frontend::BoundOperation;static constexpr std::size_t fields=2;};
template<> struct Owned<::crown::program::BoundExpression> {using Result=::crown::frontend::BoundExpression;static constexpr std::size_t fields=3;};
template<> struct Owned<::crown::program::BoundOccurrence> {using Result=::crown::frontend::BoundOccurrence;static constexpr std::size_t fields=5;};
template<> struct Owned<::crown::program::BoundOutput> {using Result=::crown::frontend::BoundOutput;static constexpr std::size_t fields=2;};
template<> struct Owned<::crown::program::BoundSql> {using Result=::crown::frontend::BoundSql;static constexpr std::size_t fields=13;};
template<> struct Owned<::crown::program::ColumnConstant> {using Result=::crown::frontend::ColumnConstant;static constexpr std::size_t fields=2;};
template<> struct Owned<::crown::program::OccurrenceAdapter> {using Result=::crown::frontend::OccurrenceAdapter;static constexpr std::size_t fields=9;};
template<> struct Owned<::crown::program::ConstantOutput> {using Result=::crown::frontend::ConstantOutput;static constexpr std::size_t fields=1;};
template<> struct Owned<::crown::program::NormalizedOutput> {using Result=::crown::frontend::NormalizedOutput;static constexpr std::size_t fields=3;};
template<> struct Owned<::crown::program::NormalizedSql> {using Result=::crown::frontend::NormalizedSql;static constexpr std::size_t fields=11;};
template<> struct Owned<::crown::program::CachePolicy> {using Result=::crown::io::CachePolicy;static constexpr std::size_t fields=4;};
template<> struct Owned<::crown::program::PhysicalOptions> {using Result=::crown::PhysicalOptions;static constexpr std::size_t fields=3;};
template<> struct Owned<::crown::program::GuaranteeProfile> {using Result=::crown::GuaranteeProfile;static constexpr std::size_t fields=15;};
template<> struct Owned<::crown::program::QueryIdentity> {using Result=::crown::io::QueryIdentity;static constexpr std::size_t fields=8;};
template<> struct Owned<::crown::program::PhysicalRelation> {using Result=::crown::PhysicalRelation;static constexpr std::size_t fields=5;};
template<> struct Owned<::crown::program::IndexRequirement> {using Result=::crown::IndexRequirement;static constexpr std::size_t fields=4;};
template<> struct Owned<::crown::program::InputConstant> {using Result=::crown::InputConstant;static constexpr std::size_t fields=2;};
template<> struct Owned<::crown::program::PhysicalInput> {using Result=::crown::PhysicalInput;static constexpr std::size_t fields=8;};
template<> struct Owned<::crown::program::PhysicalNode> {using Result=::crown::PhysicalNode;static constexpr std::size_t fields=15;};
template<> struct Owned<::crown::program::PhysicalEdge> {using Result=::crown::PhysicalEdge;static constexpr std::size_t fields=5;};
template<> struct Owned<::crown::program::EnumerationStep> {using Result=::crown::EnumerationStep;static constexpr std::size_t fields=6;};
template<> struct Owned<::crown::program::EnumerationProgram> {using Result=::crown::EnumerationProgram;static constexpr std::size_t fields=4;};
template<> struct Owned<std::string_view> {using Result=std::string;};
template<> struct Owned<storage::InlineDecimal> {using Result=Decimal;};
template<> struct Owned<storage::AccountedLayout> {using Result=storage::TupleLayout;};
template<> struct Owned<storage::AccountedProjection> {using Result=storage::Projection;};
template<class T> struct Owned<program::Span<T>> {using Result=std::vector<typename Owned<T>::Result>;};
template<class T> struct Owned<program::Set<T>> {using Result=std::set<typename Owned<T>::Result>;};
template<class T> struct Owned<std::optional<T>> {using Result=std::optional<typename Owned<T>::Result>;};
template<class... T> struct Owned<std::variant<T...>> {using Result=std::variant<typename Owned<T>::Result...>;};
// Type alias only: conversion and ownership live in Copy overloads.
template<class T> using OwnedType=typename Owned<T>::Result;
// Caller-owned DTO export of the immutable native compiler artifact. Ordinary
// fields are copied; layout/projection descriptors share account-backed metadata
// and can retain those blocks after the CompiledProgram itself is destroyed.
// This is not an internal lowering intermediate or an import path.
struct ProgramExport {
  PhysicalRoute route=PhysicalRoute::constant_false;
  Catalog catalog;
  Query query;
  FreeConnexTree tree;
  std::optional<frontend::NormalizedSql> normalized;
  planner::ValidationReport validation;
  io::QueryIdentity identity;
  std::string physical_sha256;
  std::array<char,64> physical_source_sha256{};
  PhysicalOptions options;
  GuaranteeProfile guarantee;
  std::vector<storage::TupleLayout> layouts;
  std::vector<PhysicalRelation> relations;
  std::vector<IndexRequirement> indexes;
  std::vector<PhysicalInput> inputs;
  std::vector<std::vector<OccurrenceId>> base_routes;
  std::vector<PhysicalNode> nodes;
  std::vector<PhysicalEdge> edges;
  EnumerationProgram enumeration;
  std::optional<storage::TupleLayout> result_layout;
  std::uint64_t work{};
};
// These copies are compiler inputs, admitted before explicit candidate lowering.
// Runtime owners retain only the native program; no compiler graph is cached.
Catalog catalog(const program::Catalog&);
Query query(const program::Query&);
frontend::NormalizedSql normalized(const program::NormalizedSql&);
PhysicalOptions options(const program::PhysicalOptions&);
// Cold supplied-tree replay copies only the actual immutable tree recipe.
FreeConnexTree tree(const program::FreeConnexTree&);
// Caller-owned serializer/report DTO export. Internal native lowering must use
// CompiledProgram::replan instead of this copying path.
ProgramExport export_program(const CompiledProgram&);
} // namespace crown::planner::compiler_source_detail
