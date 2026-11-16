#include "crown/storage/accounted_layout.hpp"
#include "descriptor.hpp"

#include "crown/resource/ownership.hpp"
#include "crown/api/error.hpp"
#include <algorithm>
#include <cstring>
#include <limits>
#include <map>
#include <memory>
#include <type_traits>
#include <utility>

namespace crown::storage {
namespace {
using resource::MemoryFailure;
using resource::MemoryFault;
using Equality=detail::DescriptorEquality;
static_assert(std::is_trivially_destructible_v<Field> && std::is_nothrow_copy_constructible_v<Field>);
static_assert(std::is_trivially_destructible_v<Equality>);

std::size_t add(std::size_t left, std::size_t right) {
  if (right > std::numeric_limits<std::size_t>::max() - left) throw MemoryFailure(MemoryFault::overflow);
  return left + right;
}
std::size_t multiply(std::size_t left, std::size_t right) {
  if (right != 0 && left > std::numeric_limits<std::size_t>::max() / right) throw MemoryFailure(MemoryFault::overflow);
  return left * right;
}
std::size_t aligned(std::size_t value, std::size_t alignment) {
  const auto remainder = value % alignment;
  return remainder == 0 ? value : add(value, alignment - remainder);
}
bool decimal_fits(DecimalParts value, DecimalSpec spec) noexcept {
  const auto integer_digits = value.digits == "0" || value.digits.size() <= value.scale ? std::size_t{0} :
      value.digits.size() - value.scale;
  return value.scale <= spec.scale && integer_digits + spec.scale <= spec.precision;
}
bool fits(const Value& value, DecimalSpec spec) noexcept {
  const auto* decimal = std::get_if<Decimal>(&value);
  return decimal && decimal_fits(decimal->parts(), spec);
}
bool fits(const ScalarView& value, DecimalSpec spec) noexcept {
  const auto* decimal = std::get_if<InlineDecimal>(&value);
  return decimal && decimal_fits(decimal->parts(), spec);
}
template<class Read>
TupleValidationIssue validate(std::span<const Field> fields, std::span<const Equality> equalities,
                              std::size_t size, Read read) noexcept {
  if (size != fields.size()) return {TupleProblem::arity, FieldId{0}};
  for (std::size_t i = 0; i < size; ++i) {
    const auto& value = read(i);
    if (value.index() != static_cast<std::size_t>(fields[i].type)) return {TupleProblem::scalar_kind, FieldId{i}};
    if (fields[i].decimal && !fits(value, *fields[i].decimal)) return {TupleProblem::decimal_domain, FieldId{i}};
  }
  for (const auto equality : equalities)
    if (read(equality.first.value) != read(equality.repeated.value))
      return {TupleProblem::repeated_variable, equality.repeated};
  return {};
}
}  // namespace

struct AccountedLayout::Data:detail::LayoutDescriptor {
  resource::MemoryAccount account;
  resource::MemoryBlock storage;
  LayoutId id;
  std::size_t arity;
  std::size_t equality_count;
  std::size_t equality_offset;
  std::size_t binding_offset;
  std::size_t binding_size;
  std::uint64_t catalog_version;
  std::optional<LayoutOrigin> origin;
  Data(resource::MemoryAccount owner, resource::MemoryBlock block, LayoutId layout_id, std::size_t count,
       std::size_t equal_count, std::size_t equal_offset, std::size_t text_offset, std::size_t text_size,
       std::uint64_t version, std::optional<LayoutOrigin> source_origin) noexcept
      : account(std::move(owner)), storage(std::move(block)), id(layout_id), arity(count),
        equality_count(equal_count), equality_offset(equal_offset), binding_offset(text_offset),
        binding_size(text_size), catalog_version(version), origin(source_origin) {
    detail::LayoutDescriptor::layout_id=layout_id;field_view=fields();context_view=context();
    origin_value=origin;equality_view=equalities();
    make_native_tuple=&AccountedLayout::make_public_tuple;
  }
  [[nodiscard]] std::span<const Field> fields() const noexcept {
    return {static_cast<const Field*>(storage.data()), arity};
  }
  [[nodiscard]] std::span<const Equality> equalities() const noexcept {
    return {reinterpret_cast<const Equality*>(static_cast<const std::byte*>(storage.data()) + equality_offset), equality_count};
  }
  [[nodiscard]] LayoutContextView context() const noexcept {
    return {catalog_version, std::string_view(static_cast<const char*>(storage.data()) + binding_offset, binding_size)};
  }
};

std::string_view TupleValidationFailure::code() const noexcept {
  if (issue_.problem == TupleProblem::invalid_layout) return "invalid_layout";
  if (issue_.problem == TupleProblem::decimal_domain) return "scalar_overflow";
  return "invalid_tuple";
}
const char* TupleValidationFailure::what() const noexcept {
  switch (issue_.problem) {
    case TupleProblem::invalid_layout: return "invalid accounted layout";
    case TupleProblem::arity: return "tuple arity differs from compiled layout";
    case TupleProblem::scalar_kind: return "tuple scalar kind differs from compiled layout";
    case TupleProblem::decimal_domain: return "tuple decimal exceeds exact field domain";
    case TupleProblem::repeated_variable: return "repeated layout variable has unequal values";
    case TupleProblem::none: return "tuple validation has no failure";
  }
  return "invalid tuple validation status";
}

AccountedLayout AccountedLayout::freeze(const resource::MemoryAccount& account, const TupleLayout& source,
                                        resource::MemoryAttribution attribution) {
  if (!source.same_token(source)) throw TupleValidationFailure({TupleProblem::invalid_layout, FieldId{0}});
  return make(account,source.id(),source.fields(),source.context(),source.origin(),attribution);
}
AccountedLayout AccountedLayout::make(const resource::MemoryAccount& account,LayoutId id,
    std::span<const Field> fields,LayoutContextView context,std::optional<LayoutOrigin> origin,
    resource::MemoryAttribution attribution) {
  if(!context.catalog_version || (origin && !origin->source_schema_version))
    throw TupleValidationFailure({TupleProblem::invalid_layout,FieldId{0}});
  const auto equality_offset = aligned(multiply(fields.size(), sizeof(Field)), alignof(Equality));
  // At most one first-occurrence equality per field. Reserve this controlled
  // capacity up front and charge its unused tail; no post-hoc size ticket.
  const auto binding_offset = add(equality_offset, multiply(fields.size(), sizeof(Equality)));
  const auto bytes = add(binding_offset, context.binding.size());
  auto storage = account.allocate(bytes, std::max(alignof(Field), alignof(Equality)),
                                  resource::MemoryPurpose::immutable_metadata, attribution);
  auto* output = static_cast<Field*>(storage.data());
  auto* equalities = reinterpret_cast<Equality*>(static_cast<std::byte*>(storage.data()) + equality_offset);
  using Pair = std::pair<const VariableId, FieldId>;
  using Allocator = resource::MemoryAllocator<Pair>;
  std::map<VariableId, FieldId, std::less<VariableId>, Allocator> first{
      std::less<VariableId>{}, Allocator(account, resource::MemoryPurpose::scratch, attribution)};
  std::size_t equality_count = 0;
  for (std::size_t i = 0; i < fields.size(); ++i) {
    switch(fields[i].type) {
      case ScalarType::int64:case ScalarType::string:case ScalarType::boolean:case ScalarType::date:case ScalarType::decimal:break;
      default:throw TupleValidationFailure({TupleProblem::invalid_layout,FieldId{i}});
    }
    if(fields[i].decimal && (fields[i].type!=ScalarType::decimal || !fields[i].decimal->precision ||
        fields[i].decimal->precision>38 || fields[i].decimal->scale>fields[i].decimal->precision))
      throw TupleValidationFailure({TupleProblem::invalid_layout,FieldId{i}});
    std::construct_at(output + i, fields[i]);
    if (fields[i].variable) {
      const auto [entry, inserted] = first.emplace(*fields[i].variable, FieldId{i});
      if (!inserted) {
        if(fields[entry->second.value].type!=fields[i].type)throw TupleValidationFailure({TupleProblem::invalid_layout,FieldId{i}});
        std::construct_at(equalities + equality_count++, Equality{entry->second, FieldId{i}});
      }
    }
  }
  if (!context.binding.empty())
    std::memcpy(static_cast<char*>(storage.data()) + binding_offset, context.binding.data(), context.binding.size());
  auto data = resource::make_accounted_shared<Data>(attribution, account, resource::MemoryPurpose::immutable_metadata,
      account, std::move(storage), id, fields.size(), equality_count, equality_offset, binding_offset,
      context.binding.size(), context.catalog_version, origin);
  return AccountedLayout(std::move(data));
}
const AccountedLayout::Data& AccountedLayout::required() const {
  if (!data_) throw MemoryFailure(MemoryFault::contract);
  return *data_;
}
LayoutId AccountedLayout::id() const { return required().id; }
std::span<const Field> AccountedLayout::fields() const & { return required().fields(); }
LayoutContextView AccountedLayout::context() const & { return required().context(); }
std::optional<LayoutOrigin> AccountedLayout::origin() const { return required().origin; }
std::size_t AccountedLayout::frozen_payload_bytes() const { return required().storage.size(); }
resource::MemoryStatistics AccountedLayout::account_statistics() const { return required().account.statistics(); }
const resource::MemoryAccount& AccountedLayout::query_account() const { return required().account; }
AccountedLayout AccountedLayout::clone_to(const resource::MemoryAccount& account) const {
  return clone_to(account, required().storage.attribution());
}
AccountedLayout AccountedLayout::clone_to(const resource::MemoryAccount& account,
                                         resource::MemoryAttribution attribution) const {
  const auto& source = required();
  auto storage = account.allocate(source.storage.size(), std::max(alignof(Field), alignof(Equality)),
                                  resource::MemoryPurpose::immutable_metadata, attribution);
  auto* fields = static_cast<Field*>(storage.data());
  for (std::size_t i = 0; i < source.arity; ++i) std::construct_at(fields + i, source.fields()[i]);
  auto* equalities = reinterpret_cast<Equality*>(static_cast<std::byte*>(storage.data()) + source.equality_offset);
  for (std::size_t i = 0; i < source.equality_count; ++i) std::construct_at(equalities + i, source.equalities()[i]);
  if (source.binding_size != 0)
    std::memcpy(static_cast<char*>(storage.data()) + source.binding_offset,
                source.context().binding.data(), source.binding_size);
  auto data = resource::make_accounted_shared<Data>(attribution, account, resource::MemoryPurpose::immutable_metadata,
      account, std::move(storage), source.id, source.arity, source.equality_count, source.equality_offset,
      source.binding_offset, source.binding_size, source.catalog_version, source.origin);
  return AccountedLayout(std::move(data));
}
bool AccountedLayout::same_token(const AccountedLayout& other) const noexcept { return data_ && data_ == other.data_; }
TupleLayout AccountedLayout::descriptor() const {static_cast<void>(required());return TupleLayout(data_);}
bool AccountedLayout::same_token(const TupleLayout& other) const noexcept {return data_ && descriptor().same_token(other);}
bool AccountedLayout::same_descriptor(const AccountedLayout& other) const noexcept {
  return data_ && other.data_ && data_->id == other.data_->id && data_->context() == other.data_->context() &&
      data_->origin == other.data_->origin && data_->arity == other.data_->arity &&
      std::equal(data_->fields().begin(), data_->fields().end(), other.data_->fields().begin());
}
TupleValidationIssue AccountedLayout::validation_issue(const Row& values) const noexcept {
  if (!data_) return {TupleProblem::invalid_layout, FieldId{0}};
  return validate(data_->fields(), data_->equalities(), values.size(), [&](std::size_t i) -> const Value& { return values[i]; });
}
TupleValidationIssue AccountedLayout::validation_issue(RowView values) const noexcept {
  if (!data_) return {TupleProblem::invalid_layout, FieldId{0}};
  return validate(data_->fields(), data_->equalities(), values.size(), [&](std::size_t i) -> const ScalarView& { return values[i]; });
}
AccountedTuple AccountedLayout::tuple(const Row& values, resource::MemoryAttribution attribution) const {
  const auto issue = validation_issue(values);
  if (!issue.ok()) throw TupleValidationFailure(issue);
  return AccountedTuple(*this, AccountedRow::copy_of(required().account, values, attribution));
}
AccountedTuple AccountedLayout::tuple(RowView values, resource::MemoryAttribution attribution) const {
  const auto issue = validation_issue(values);
  if (!issue.ok()) throw TupleValidationFailure(issue);
  return AccountedTuple(*this, AccountedRow::copy_of(required().account, values, attribution));
}
TupleValidationIssue AccountedLayout::validation_issue_view(TupleValuesView values) const noexcept {
  if(const auto* legacy=values.legacy_row())return validation_issue(*legacy);
  return validation_issue(values.native_view().value_or(RowView{}));
}
AccountedTuple AccountedLayout::tuple_view(TupleValuesView values,resource::MemoryAttribution attribution) const {
  if(const auto* legacy=values.legacy_row())return tuple(*legacy,attribution);
  return tuple(values.native_view().value_or(RowView{}),attribution);
}
Tuple AccountedLayout::make_public_tuple(const TupleLayout& descriptor,TupleValuesView values) {
  auto native=AccountedLayout(std::static_pointer_cast<const Data>(descriptor.data_));
  try{return Tuple::from_accounted(native.tuple_view(std::move(values),{resource::MemoryOwnerKind::output,0}));}
  catch(const TupleValidationFailure& failure){throw Error(std::string(failure.code()),failure.what());}
}

LayoutFreezeRegistry::LayoutFreezeRegistry(const resource::MemoryAccount& account, std::span<const TupleLayout> sources,
                                         resource::MemoryAttribution attribution)
    : account_(account), attribution_(attribution), sources_(sources),
      slots_(resource::MemoryAllocator<Slot>(account, resource::MemoryPurpose::scratch, attribution)) {
  for (const auto& source : sources)
    if (!source.same_token(source)) throw TupleValidationFailure({TupleProblem::invalid_layout, FieldId{0}});
  slots_.resize(sources.size());
}
AccountedLayout LayoutFreezeRegistry::get(std::size_t index) {
  if (index >= sources_.size()) throw MemoryFailure(MemoryFault::contract);
  for (std::size_t i = 0; i <= index; ++i) {
    if (!sources_[i].same_token(sources_[index])) continue;
    if (!slots_[i]) slots_[i].emplace(AccountedLayout::freeze(account_, sources_[i], attribution_));
    return *slots_[i];
  }
  throw MemoryFailure(MemoryFault::contract);
}

}  // namespace crown::storage
