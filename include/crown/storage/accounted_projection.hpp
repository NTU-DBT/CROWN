#pragma once

#include "crown/storage/accounted_layout.hpp"
#include <exception>
#include <memory>
#include <span>
#include <string_view>
#include <utility>

namespace crown::storage {

enum class ProjectionProblem {
  invalid_layout, foreign_account, context, arity, field, scalar_domain,
  variable_identity, repeated_variable, layout_mismatch
};
class ProjectionValidationFailure final : public std::exception {
 public:
  explicit ProjectionValidationFailure(ProjectionProblem issue) noexcept : issue_(issue) {}
  [[nodiscard]] ProjectionProblem issue() const noexcept { return issue_; }
  [[nodiscard]] std::string_view code() const noexcept;
  [[nodiscard]] const char* what() const noexcept override;
 private:
  ProjectionProblem issue_;
};

// Construction proves the mapping against two frozen layouts sharing one
// query account. Only owned numeric fields and those frozen tokens survive;
// no original Projection/Row or unaccounted container is retained.
class AccountedProjection {
  struct Data;
 public:
  AccountedProjection() noexcept = default;
  [[nodiscard]] static AccountedProjection freeze(const AccountedLayout& source,
      const AccountedLayout& target, std::span<const FieldId>,
      resource::MemoryAttribution = {resource::MemoryOwnerKind::immutable_metadata, 0});
  [[nodiscard]] explicit operator bool() const noexcept { return bool(data_); }
  [[nodiscard]] const AccountedLayout& source() const &;
  const AccountedLayout& source() const && = delete;
  [[nodiscard]] const AccountedLayout& target() const &;
  const AccountedLayout& target() const && = delete;
  [[nodiscard]] std::span<const FieldId> fields() const &;
  std::span<const FieldId> fields() const && = delete;
  // Exact shared program identity; equal field lists do not share a token.
  [[nodiscard]] bool same_token(const AccountedProjection& other) const noexcept {
    return data_ && data_ == other.data_;
  }
  [[nodiscard]] AccountedTuple apply(const AccountedTuple&) const;
  [[nodiscard]] AccountedTuple apply(const AccountedTuple&, resource::MemoryAttribution) const;
  // External/adapter row view: validation proves the source descriptor; the
  // result owns copied bytes under this projection's original account.
  [[nodiscard]] AccountedTuple apply(RowView,resource::MemoryAttribution = {}) const;
  [[nodiscard]] Projection descriptor() const;
 private:
  explicit AccountedProjection(std::shared_ptr<const Data> data) noexcept : data_(std::move(data)) {}
  [[nodiscard]] const Data& required() const;
  [[nodiscard]] static Tuple make_public_tuple(const Projection&,const Tuple&);
  std::shared_ptr<const Data> data_;
};

}  // namespace crown::storage
