#pragma once

#include "crown/frontend/sql_rows.hpp"
#include "crown/storage/index_failure.hpp"

namespace crown::frontend::rows_detail {
// The SQL family admits UTF8 TEXT under binary/C comparison, without U+0000.
// This is a byte pass at source admission; native core bytes keep their wider
// existing domain. No locale object, conversion buffer or owning string.
inline bool text_fits(std::string_view text) noexcept {
  std::size_t i = 0;
  while (i < text.size()) {
    const auto first = static_cast<unsigned char>(text[i++]);
    if (first == 0) return false;
    if (first < 0x80) continue;
    const auto count = first >= 0xc2 && first <= 0xdf ? 1U :
        first >= 0xe0 && first <= 0xef ? 2U : first >= 0xf0 && first <= 0xf4 ? 3U : 0U;
    if (count == 0 || text.size() - i < count) return false;
    const auto second = static_cast<unsigned char>(text[i]);
    if ((first == 0xe0 && second < 0xa0) || (first == 0xed && second >= 0xa0) ||
        (first == 0xf0 && second < 0x90) || (first == 0xf4 && second >= 0x90)) return false;
    for (unsigned j = 0; j < count; ++j)
      if ((static_cast<unsigned char>(text[i++]) & 0xc0U) != 0x80U) return false;
  }
  return true;
}
inline ScalarType scalar(SqlKind kind) {
  switch (kind) {
    case SqlKind::int32: case SqlKind::int64: return ScalarType::int64;
    case SqlKind::string: return ScalarType::string;
    case SqlKind::boolean: return ScalarType::boolean;
    case SqlKind::date: return ScalarType::date;
    case SqlKind::decimal: return ScalarType::decimal;
    case SqlKind::unknown: break;
  }
  throw storage::IndexFailure(storage::IndexFault::contract);
}
inline SqlType sql_type(const Column& column) {
  switch (column.type) {
    case ScalarType::int64: return {SqlKind::int64, column.nullable, column.decimal};
    case ScalarType::string: return {SqlKind::string, column.nullable, column.decimal};
    case ScalarType::boolean: return {SqlKind::boolean, column.nullable, column.decimal};
    case ScalarType::date: return {SqlKind::date, column.nullable, column.decimal};
    case ScalarType::decimal: return {SqlKind::decimal, column.nullable, column.decimal};
  }
  throw storage::IndexFailure(storage::IndexFault::contract);
}
// Type/spec metadata is factory-validated. Decimal parts are already canonical;
// inspect widths directly rather than render text during a row update.
inline bool fits(const SqlRowCell& value, const SqlType& type) {
  if (!value) return type.nullable;
  if (type.kind == SqlKind::unknown || storage::type_of(*value) != scalar(type.kind)) return false;
  if (type.kind == SqlKind::int32) {
    const auto number = std::get<std::int64_t>(*value);
    if (number < INT32_MIN || number > INT32_MAX) return false;
  }
  if (type.kind == SqlKind::string && !text_fits(std::get<std::string_view>(*value))) return false;
  if (type.decimal) {
    const auto parts = std::get<storage::InlineDecimal>(*value).parts();
    const auto integers = parts.digits == "0" || parts.digits.size() <= parts.scale ? 0 : parts.digits.size() - parts.scale;
    if (parts.scale > type.decimal->scale || integers > type.decimal->precision - type.decimal->scale) return false;
  }
  return true;
}
inline storage::ScalarView zero(ScalarType type) {
  switch (type) {
    case ScalarType::int64: return std::int64_t{0};
    case ScalarType::string: return std::string_view{};
    case ScalarType::boolean: return false;
    case ScalarType::date: return Date{};
    case ScalarType::decimal: return storage::InlineDecimal{};
  }
  throw storage::IndexFailure(storage::IndexFault::contract);
}
}  // namespace crown::frontend::rows_detail
