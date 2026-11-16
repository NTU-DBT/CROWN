#pragma once

#include "crown/ir/model.hpp"
#include "crown/storage/tuple_values.hpp"
#include <memory>
#include <span>
#include <string_view>
#include <utility>
#include <type_traits>

namespace crown::storage {
struct Field {
  ScalarType type;
  std::optional<DecimalSpec> decimal = std::nullopt;
  std::optional<VariableId> variable = std::nullopt;
  auto operator<=>(const Field&) const = default;
};
struct LayoutContext {
  std::uint64_t catalog_version = 1;
  std::string binding;  // Optional owning query/schema binding, never a field name.
  auto operator<=>(const LayoutContext&) const = default;
};
struct LayoutContextView {
  std::uint64_t catalog_version=1;
  std::string_view binding{};
  auto operator<=>(const LayoutContextView&) const = default;
};
[[nodiscard]] inline bool operator==(LayoutContextView view,const LayoutContext& owner) noexcept {
  return view.catalog_version==owner.catalog_version && view.binding==owner.binding;
}
struct LayoutOrigin {
  TableId table;
  std::uint64_t source_schema_version;
  auto operator<=>(const LayoutOrigin&) const = default;
};
class Tuple;
class Projection;
class AccountedLayout;
class AccountedProjection;
class AccountedTuple;
namespace detail {struct LayoutDescriptor;struct ProjectionDescriptor;}
class TupleLayout {
 public:
  TupleLayout(LayoutId id, std::vector<Field> fields, LayoutContext context = {}, std::optional<LayoutOrigin> origin = {});
  [[nodiscard]] LayoutId id() const;
  [[nodiscard]] const std::span<const Field>& fields() const;
  [[nodiscard]] const LayoutContextView& context() const;
  [[nodiscard]] const std::optional<LayoutOrigin>& origin() const;
  // Copies share an immutable runtime token. Deserialized/equal descriptors do
  // not implicitly acquire another layout's token.
  [[nodiscard]] bool same_token(const TupleLayout& other) const noexcept;
  [[nodiscard]] bool same_token(const AccountedLayout& other) const noexcept;
  [[nodiscard]] bool same_descriptor(const TupleLayout& other) const;
  void validate(const Row& values) const;
  void validate_view(TupleValuesView values) const;
  [[nodiscard]] Tuple tuple(const Row& values) const;
  [[nodiscard]] Tuple tuple(Row&& values) const;
  [[nodiscard]] Tuple tuple_view(TupleValuesView values) const;
  template<class Values> requires std::is_same_v<std::remove_cvref_t<Values>,TupleValuesView>
  [[nodiscard]] Tuple tuple(Values&& values) const;
  template<class Values> requires std::is_same_v<std::remove_cvref_t<Values>,TupleValuesView>
  void validate(Values&& values) const {validate_view(std::forward<Values>(values));}
 private:
  friend class AccountedLayout;
  explicit TupleLayout(std::shared_ptr<const detail::LayoutDescriptor> data) noexcept:data_(std::move(data)) {}
  struct Data;
  std::shared_ptr<const detail::LayoutDescriptor> data_;
};
// Legacy payload copies own deep Row/string copies; native payload copies
// share their funded immutable owner. Copy cost depends on representation.
class Tuple {
 public:
  Tuple(const Tuple&);
  Tuple(Tuple&&) noexcept = default;
  Tuple& operator=(const Tuple& other);
  Tuple& operator=(Tuple&& other) noexcept;
  [[nodiscard]] const TupleLayout& layout() const noexcept { return layout_; }
  [[nodiscard]] TupleValuesView values() const noexcept { return TupleValuesView(payload_); }
  [[nodiscard]] std::uint64_t hash() const { return values().hash(); }
  [[nodiscard]] bool operator==(const Tuple& other) const { return layout_.same_token(other.layout_) && values() == other.values(); }
  // Transfers native payload ownership without scalar/metadata export and
  // allocates its actual immutable shared owner under the original account.
  [[nodiscard]] static Tuple from_accounted(AccountedTuple);
  [[nodiscard]] bool is_accounted() const noexcept;
  [[nodiscard]] resource::MemoryUsage memory_usage() const noexcept;
  [[nodiscard]] resource::MemoryStatistics account_statistics() const;
 private:
  friend class TupleLayout;
  friend class Projection;
  Tuple(TupleLayout,std::shared_ptr<const detail::TuplePayload>) noexcept;
  TupleLayout layout_;
  std::shared_ptr<const detail::TuplePayload> payload_;
};
template<class Values> requires std::is_same_v<std::remove_cvref_t<Values>,TupleValuesView>
Tuple TupleLayout::tuple(Values&& values) const{return tuple_view(std::forward<Values>(values));}
class Projection {
 public:
  Projection(TupleLayout source, TupleLayout target, std::vector<FieldId> fields);
  [[nodiscard]] const TupleLayout& source() const;
  [[nodiscard]] const TupleLayout& target() const;
  [[nodiscard]] const std::span<const FieldId>& fields() const;
  [[nodiscard]] bool same_token(const Projection& other) const noexcept;
  [[nodiscard]] bool same_token(const AccountedProjection& other) const noexcept;
  // Checks the input token before gathering selected fields. Native-backed
  // public descriptors also revalidate source values; standalone descriptors
  // validate the constructed target. Direct AccountedTuple projection uses
  // its separate prevalidated-token path. Output bytes are copied explicitly.
  [[nodiscard]] Tuple apply(const Tuple& tuple) const;
 private:
  friend class AccountedProjection;
  explicit Projection(std::shared_ptr<const detail::ProjectionDescriptor> data) noexcept:data_(std::move(data)) {}
  struct Data;
  std::shared_ptr<const detail::ProjectionDescriptor> data_;
};
[[nodiscard]] TupleLayout table_layout(LayoutId id, const Catalog& catalog, TableId table, std::string binding = {});
[[nodiscard]] TupleLayout scope_layout(LayoutId id, const Query& query, std::span<const VariableId> variables, LayoutContext context = {});
[[nodiscard]] TupleLayout projected_layout(LayoutId id, const TupleLayout& source, std::span<const FieldId> fields);
}  // namespace crown::storage
