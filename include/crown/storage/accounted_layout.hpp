#pragma once

#include "crown/storage/accounted_row.hpp"
#include "crown/storage/layout.hpp"
#include "crown/resource/allocator.hpp"
#include <exception>
#include <memory>
#include <optional>
#include <span>
#include <string_view>
#include <utility>
#include <vector>

namespace crown::storage {

enum class TupleProblem { none, invalid_layout, arity, scalar_kind, decimal_domain, repeated_variable };
struct TupleValidationIssue {
  TupleProblem problem = TupleProblem::none;
  FieldId field{0};
  [[nodiscard]] bool ok() const noexcept { return problem == TupleProblem::none; }
};
// Fixed diagnostics for an internal validation boundary. Formatting a detailed
// external message is separate; no owning string is built while unwinding.
class TupleValidationFailure final : public std::exception {
 public:
  explicit TupleValidationFailure(TupleValidationIssue issue) noexcept : issue_(issue) {}
  [[nodiscard]] TupleValidationIssue issue() const noexcept { return issue_; }
  [[nodiscard]] std::string_view code() const noexcept;
  [[nodiscard]] const char* what() const noexcept override;
 private:
  TupleValidationIssue issue_;
};

class AccountedTuple;
class AccountedProjection;
class AccountedPlanStorage;
class AccountedTupleArena;
// S05 immutable metadata copy. Only flat fields, compiled equalities
// and binary binding bytes are retained. There is no original TupleLayout or
// unmeasured shared_ptr mirror in the owned Data. The same account funds both
// metadata storage and its shared object/control block.
class AccountedLayout {
  struct Data;
 public:
  AccountedLayout() noexcept = default;
  [[nodiscard]] static AccountedLayout freeze(const resource::MemoryAccount&, const TupleLayout&,
      resource::MemoryAttribution = {resource::MemoryOwnerKind::immutable_metadata, 0});
  [[nodiscard]] static AccountedLayout make(const resource::MemoryAccount&,LayoutId,
      std::span<const Field>,LayoutContextView = {},std::optional<LayoutOrigin> = {},
      resource::MemoryAttribution = {resource::MemoryOwnerKind::immutable_metadata,0});
  [[nodiscard]] explicit operator bool() const noexcept { return bool(data_); }
  [[nodiscard]] LayoutId id() const;
  [[nodiscard]] std::span<const Field> fields() const &;
  std::span<const Field> fields() const && = delete;
  [[nodiscard]] LayoutContextView context() const &;
  LayoutContextView context() const && = delete;
  [[nodiscard]] std::optional<LayoutOrigin> origin() const;
  [[nodiscard]] bool same_token(const AccountedLayout&) const noexcept;
  [[nodiscard]] bool same_token(const TupleLayout&) const noexcept;
  // A read-only descriptor handle sharing this funded metadata and token.
  // It allocates no legacy fields, binding text or control block.
  [[nodiscard]] TupleLayout descriptor() const;
  [[nodiscard]] bool same_descriptor(const AccountedLayout&) const noexcept;
  [[nodiscard]] std::size_t frozen_payload_bytes() const;
  [[nodiscard]] resource::MemoryStatistics account_statistics() const;
  [[nodiscard]] AccountedLayout clone_to(const resource::MemoryAccount&) const;
  [[nodiscard]] AccountedLayout clone_to(const resource::MemoryAccount&, resource::MemoryAttribution) const;
  [[nodiscard]] TupleValidationIssue validation_issue(const Row&) const noexcept;
  [[nodiscard]] TupleValidationIssue validation_issue(RowView) const noexcept;
  [[nodiscard]] TupleValidationIssue validation_issue_view(TupleValuesView) const noexcept;
  [[nodiscard]] AccountedTuple tuple(const Row&, resource::MemoryAttribution = {}) const;
  [[nodiscard]] AccountedTuple tuple(RowView, resource::MemoryAttribution = {}) const;
  [[nodiscard]] AccountedTuple tuple_view(TupleValuesView, resource::MemoryAttribution = {}) const;
  template<class Values> requires std::is_same_v<std::remove_cvref_t<Values>,TupleValuesView>
  [[nodiscard]] AccountedTuple tuple(Values&& values,resource::MemoryAttribution attribution={}) const;
 private:
  friend class AccountedPlanStorage;
  friend class AccountedProjection;
  friend class Tuple;
  friend class AccountedTupleArena;
  friend class AccountedReferenceTable;
  friend class AccountedIndexedTable;
  friend class AccountedStorageTable;
  explicit AccountedLayout(std::shared_ptr<const Data> data) noexcept : data_(std::move(data)) {}
  [[nodiscard]] const Data& required() const;
  [[nodiscard]] const resource::MemoryAccount& query_account() const;
  [[nodiscard]] static Tuple make_public_tuple(const TupleLayout&,TupleValuesView);
  std::shared_ptr<const Data> data_;
};

class AccountedTuple {
 public:
  AccountedTuple(const AccountedTuple&) = delete;
  AccountedTuple& operator=(const AccountedTuple&) = delete;
  AccountedTuple(AccountedTuple&&) noexcept = default;
  AccountedTuple& operator=(AccountedTuple&&) noexcept = default;
  [[nodiscard]] const AccountedLayout& layout() const & noexcept { return layout_; }
  const AccountedLayout& layout() const && = delete;
  [[nodiscard]] RowView values() const & noexcept { return values_.view(); }
  RowView values() const && = delete;
  // Hash/equality visit actual cells and string bytes; the layout token
  // is checked by equality and is not part of this row-value hash.
  [[nodiscard]] std::uint64_t hash() const noexcept { return values_.view().hash(); }
  [[nodiscard]] resource::MemoryAttribution attribution() const { return values_.attribution(); }
  [[nodiscard]] resource::MemoryUsage memory_usage() const noexcept { return values_.memory_usage(); }
  // An explicit deep clone uses the metadata's existing query account. Moving
  // a tuple transfers its complete layout+row ownership without allocation.
  [[nodiscard]] AccountedTuple clone() const { return layout_.tuple(values_.view(), values_.attribution()); }
  [[nodiscard]] bool operator==(const AccountedTuple& other) const noexcept {
    return layout_.same_token(other.layout_) && values_.view() == other.values_.view();
  }
 private:
  friend class AccountedLayout;
  friend class AccountedProjection;
  friend class AccountedTupleArena;
  friend class AccountedReferenceTable;
  friend class AccountedIndexedTable;
  void set_lifetime(resource::AllocationLifetime lifetime) { values_.set_lifetime(lifetime); }
  AccountedTuple(AccountedLayout layout, AccountedRow values) noexcept
      : layout_(std::move(layout)), values_(std::move(values)) {}
  AccountedLayout layout_;
  AccountedRow values_;
};
template<class Values> requires std::is_same_v<std::remove_cvref_t<Values>,TupleValuesView>
AccountedTuple AccountedLayout::tuple(Values&& values,resource::MemoryAttribution attribution) const {
  return tuple_view(std::forward<Values>(values),attribution);
}

// A construction-only token registry. The source span/objects are borrowed and
// must stay alive and unmoved until registry destruction. Returned layouts
// retain no source reference and survive both registry and source destruction.
// Copy aliases share exactly one newly frozen token; descriptor-equal source
// layouts with different tokens remain different. Registry storage is charged.
class LayoutFreezeRegistry {
 public:
  LayoutFreezeRegistry(const resource::MemoryAccount&, std::span<const TupleLayout>,
      resource::MemoryAttribution = {resource::MemoryOwnerKind::immutable_metadata, 0});
  LayoutFreezeRegistry(const LayoutFreezeRegistry&) = delete;
  LayoutFreezeRegistry& operator=(const LayoutFreezeRegistry&) = delete;
  // Linear-prefix token scan, with one lazy freeze per source token;
  // this registry is construction scratch rather than a hot lookup index.
  [[nodiscard]] AccountedLayout get(std::size_t);
 private:
  using Slot = std::optional<AccountedLayout>;
  resource::MemoryAccount account_;
  resource::MemoryAttribution attribution_;
  std::span<const TupleLayout> sources_;
  std::vector<Slot, resource::MemoryAllocator<Slot>> slots_;
};

}  // namespace crown::storage
