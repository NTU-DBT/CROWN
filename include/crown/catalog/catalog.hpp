#pragma once

#include "crown/ir/model.hpp"
#include <optional>
#include <span>
#include <string_view>

namespace crown::catalog {
// Metadata validation accepts nullable source declarations. A direct-CQ core
// separately rejects them until an explicit SQL adapter proves non-nullness.
void validate_catalog(const Catalog& catalog);
void validate_constraints(const Catalog& catalog, const Database& database);
void validate_catalog(const program::Catalog& catalog);
void validate_constraints(const program::Catalog& catalog, const Database& database);
[[nodiscard]] bool requires_format3(const Catalog& catalog);
[[nodiscard]] bool requires_format3(const program::Catalog& catalog);
[[nodiscard]] bool decimal_fits(const Decimal& value, DecimalSpec specification);

struct RelationBinding {
  TableId table;
  std::string qualifier;
};
struct ColumnReference {
  std::size_t binding;
  ColumnId column;
  auto operator<=>(const ColumnReference&) const = default;
};
[[nodiscard]] TableId find_table(const Catalog& catalog, std::string_view name);
[[nodiscard]] TableId find_table(const program::Catalog& catalog, std::string_view name);
// Qualifiers are the visible aliases. Self-join bindings remain distinct even
// when they refer to the same table. An explicit alias hides the base name.
[[nodiscard]] ColumnReference resolve_column(const Catalog& catalog,
    std::span<const RelationBinding> bindings, std::optional<std::string_view> qualifier,
    std::string_view name);
// No representation-changing casts are admitted by the initial scalar core.
// The binder must call this before merging equality classes or dropping casts.
void require_identity_cast(ScalarType source, ScalarType target);
void require_identity_cast(const Column& source, const Column& target);
}  // namespace crown::catalog
