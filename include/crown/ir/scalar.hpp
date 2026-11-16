#pragma once

#include <compare>
#include <cstdint>
#include <string>
#include <string_view>

namespace crown {
// Borrowed canonical coefficient, with no formatting/copy allocation. The
// view remains valid only while its Decimal is alive and unmodified.
struct DecimalParts {
  std::string_view digits;
  std::uint32_t scale;
  bool negative;
};
// Finite Gregorian dates, 0001-01-01 through 9999-12-31. No timezone,
// locale-dependent input, BC dates or PostgreSQL infinity sentinels.
class Date {
 public:
  Date() = default;  // 1970-01-01
  [[nodiscard]] static Date parse(std::string_view text);
  [[nodiscard]] std::string to_string() const;
  [[nodiscard]] std::int32_t epoch_days() const { return days_; }
  auto operator<=>(const Date&) const = default;
 private:
  explicit Date(std::int32_t days) : days_(days) {}
  std::int32_t days_ = 0;
};

// An exact finite decimal. Its canonical coefficient has at most 38 digits,
// and its scale is 0..38. This is a value domain, not SQL DECIMAL(p,s) coercion.
// Parse never rounds, converts through floating point, or silently overflows.
class Decimal {
 public:
  Decimal() = default;  // Canonical positive zero, scale zero.
  // Copying also handles rvalues: the bounded coefficient stays canonical in
  // both objects. A default string move would leave the source with empty
  // digits but its old scale/sign, outside this value domain.
  Decimal(const Decimal&) = default;
  Decimal& operator=(const Decimal&) = default;
  [[nodiscard]] static Decimal parse(std::string_view text);
  [[nodiscard]] std::string to_string() const;
  [[nodiscard]] DecimalParts parts() const noexcept { return {digits_, scale_, negative_}; }
  [[nodiscard]] bool operator==(const Decimal&) const = default;
  [[nodiscard]] std::strong_ordering operator<=>(const Decimal& other) const;
 private:
  std::string digits_ = "0";
  std::uint32_t scale_ = 0;
  bool negative_ = false;
};
}  // namespace crown
