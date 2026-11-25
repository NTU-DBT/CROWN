#include "crown/storage/accounted_projection.hpp"
#include "descriptor.hpp"

#include "crown/resource/ownership.hpp"
#include "crown/api/error.hpp"
#include <limits>
#include <map>
#include <memory>
#include <type_traits>

namespace crown::storage {
namespace {
[[noreturn, gnu::cold, gnu::noinline]] void fail(ProjectionProblem problem) { throw ProjectionValidationFailure(problem); }
inline void require(bool value, ProjectionProblem problem) {
  if (!value) [[unlikely]] fail(problem);
}
bool fits_domain(const Field& source, const Field& target) noexcept {
  if (source.type != target.type) return false;
  if (!target.decimal) return true;
  return source.decimal && source.decimal->scale <= target.decimal->scale &&
      source.decimal->precision - source.decimal->scale <= target.decimal->precision - target.decimal->scale;
}
static_assert(std::is_nothrow_copy_constructible_v<FieldId> && std::is_trivially_destructible_v<FieldId>);
}  // namespace

struct AccountedProjection::Data:detail::ProjectionDescriptor {
  resource::MemoryAccount account;
  AccountedLayout source;
  AccountedLayout target;
  resource::MemoryBlock storage;
  std::size_t size;
  Data(resource::MemoryAccount owner, AccountedLayout input, AccountedLayout output,
       resource::MemoryBlock fields, std::size_t count) noexcept
      : detail::ProjectionDescriptor(input.descriptor(),output.descriptor()),account(std::move(owner)), source(std::move(input)), target(std::move(output)),
        storage(std::move(fields)), size(count) {
    field_view=this->fields();apply_native_tuple=&AccountedProjection::make_public_tuple;
  }
  [[nodiscard]] std::span<const FieldId> fields() const noexcept {
    return {static_cast<const FieldId*>(storage.data()), size};
  }
};

std::string_view ProjectionValidationFailure::code() const noexcept {
  return issue_ == ProjectionProblem::layout_mismatch ? "layout_mismatch" : "invalid_projection";
}
const char* ProjectionValidationFailure::what() const noexcept {
  switch (issue_) {
    case ProjectionProblem::invalid_layout: return "projection requires valid frozen layouts";
    case ProjectionProblem::foreign_account: return "projection layouts belong to different query accounts";
    case ProjectionProblem::context: return "projection layouts have different catalog/query contexts";
    case ProjectionProblem::arity: return "projection arity differs from the target layout";
    case ProjectionProblem::field: return "projection source field is out of range";
    case ProjectionProblem::scalar_domain: return "projection changes scalar kind or narrows the exact domain";
    case ProjectionProblem::variable_identity: return "projection changes a bound variable identity";
    case ProjectionProblem::repeated_variable: return "target equality is not justified by source fields";
    case ProjectionProblem::layout_mismatch: return "projection input has another immutable layout token";
  }
  return "invalid projection status";
}

AccountedProjection AccountedProjection::freeze(const AccountedLayout& source, const AccountedLayout& target,
    std::span<const FieldId> fields, resource::MemoryAttribution attribution) {
  require(bool(source) && bool(target), ProjectionProblem::invalid_layout);
  const auto& account = source.query_account();
  require(account.statistics().owner == target.query_account().statistics().owner, ProjectionProblem::foreign_account);
  require(source.context() == target.context(), ProjectionProblem::context);
  require(fields.size() == target.fields().size(), ProjectionProblem::arity);
  if (fields.size() > std::numeric_limits<std::size_t>::max() / sizeof(FieldId))
    throw resource::MemoryFailure(resource::MemoryFault::overflow);
  using Pair = std::pair<const VariableId, FieldId>;
  using Allocator = resource::MemoryAllocator<Pair>;
  std::map<VariableId, FieldId, std::less<VariableId>, Allocator> first{
      std::less<VariableId>{}, Allocator(account, resource::MemoryPurpose::scratch, attribution)};
  for (std::size_t i = 0; i < fields.size(); ++i) {
    require(fields[i].value < source.fields().size(), ProjectionProblem::field);
    const auto& input = source.fields()[fields[i].value];
    const auto& output = target.fields()[i];
    require(fits_domain(input, output), ProjectionProblem::scalar_domain);
    require(!input.variable || !output.variable || input.variable == output.variable, ProjectionProblem::variable_identity);
    if (output.variable) {
      const auto [entry, inserted] = first.emplace(*output.variable, fields[i]);
      if (!inserted) {
        const auto& previous = source.fields()[entry->second.value];
        require(entry->second == fields[i] || (previous.variable && previous.variable == input.variable),
                ProjectionProblem::repeated_variable);
      }
    }
  }
  auto storage = account.allocate(fields.size_bytes(), alignof(FieldId),
      resource::MemoryPurpose::immutable_metadata, attribution);
  auto* output = static_cast<FieldId*>(storage.data());
  for (std::size_t i = 0; i < fields.size(); ++i) std::construct_at(output + i, fields[i]);
  auto data = resource::make_accounted_shared<Data>(attribution, account, resource::MemoryPurpose::immutable_metadata,
      account, source, target, std::move(storage), fields.size());
  return AccountedProjection(std::move(data));
}
const AccountedProjection::Data& AccountedProjection::required() const {
  if (!data_) throw ProjectionValidationFailure(ProjectionProblem::invalid_layout);
  return *data_;
}
const AccountedLayout& AccountedProjection::source() const & { return required().source; }
const AccountedLayout& AccountedProjection::target() const & { return required().target; }
std::span<const FieldId> AccountedProjection::fields() const & { return required().fields(); }
AccountedTuple AccountedProjection::apply(const AccountedTuple& tuple) const {
  const auto& data = required();
  require(data.source.same_token(tuple.layout()), ProjectionProblem::layout_mismatch);
  return apply(tuple, tuple.attribution());
}
AccountedTuple AccountedProjection::apply(const AccountedTuple& tuple, resource::MemoryAttribution attribution) const {
  const auto& data = required();
  require(data.source.same_token(tuple.layout()), ProjectionProblem::layout_mismatch);
  // Construction already proved the target domains/equalities. No metadata
  // lookup, owning diagnostic or temporary value container is needed here.
  return AccountedTuple(data.target, AccountedRow::project(data.account, tuple.values(), data.fields(), attribution));
}
Projection AccountedProjection::descriptor() const {static_cast<void>(required());return Projection(data_);}
AccountedTuple AccountedProjection::apply(RowView values,resource::MemoryAttribution attribution) const {
  const auto& data=required();
  const auto issue=data.source.validation_issue(values);
  if(!issue.ok())throw TupleValidationFailure(issue);
  return AccountedTuple(data.target,AccountedRow::project(data.account,values,data.fields(),attribution));
}
Tuple AccountedProjection::make_public_tuple(const Projection& descriptor,const Tuple& tuple) {
  auto projection=AccountedProjection(std::static_pointer_cast<const Data>(descriptor.data_));
  const auto values=tuple.values();const auto native=values.native_view();
  if(!native)throw Error("storage_contract","native projection has no native input payload");
  try{return Tuple::from_accounted(projection.apply(*native,{resource::MemoryOwnerKind::output,0}));}
  catch(const ProjectionValidationFailure& failure){throw Error(std::string(failure.code()),failure.what());}
  catch(const TupleValidationFailure& failure){throw Error(std::string(failure.code()),failure.what());}
}

}  // namespace crown::storage
