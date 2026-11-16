#include "crown/ir/scalar.hpp"

#include "crown/api/error.hpp"
#include <algorithm>
#include <chrono>
#include <cstddef>
#include <utility>

namespace crown {
namespace {
bool digit(char value) { return value >= '0' && value <= '9'; }
[[noreturn]] void invalid_date() {
  throw Error("invalid_scalar", "date must be a valid Gregorian YYYY-MM-DD in 0001..9999");
}
}  // namespace

Date Date::parse(std::string_view text) {
  if (text.size() != 10 || text[4] != '-' || text[7] != '-') invalid_date();
  for (std::size_t i = 0; i < text.size(); ++i) {
    if (i != 4 && i != 7 && !digit(text[i])) invalid_date();
  }
  const int year_number = (text[0] - '0') * 1000 + (text[1] - '0') * 100 + (text[2] - '0') * 10 + text[3] - '0';
  const auto month_number = static_cast<unsigned>((text[5] - '0') * 10 + text[6] - '0');
  const auto day_number = static_cast<unsigned>((text[8] - '0') * 10 + text[9] - '0');
  const std::chrono::year_month_day date{std::chrono::year{year_number}, std::chrono::month{month_number}, std::chrono::day{day_number}};
  if (year_number == 0 || !date.ok()) invalid_date();
  const auto days = std::chrono::sys_days{date}.time_since_epoch().count();
  return Date{static_cast<std::int32_t>(days)};  // The declared date range fits int32.
}

std::string Date::to_string() const {
  const std::chrono::year_month_day date{std::chrono::sys_days{std::chrono::days{days_}}};
  const auto year_number = static_cast<unsigned>(static_cast<int>(date.year()));
  const auto month_number = static_cast<unsigned>(date.month());
  const auto day_number = static_cast<unsigned>(date.day());
  std::string result = "0000-00-00";
  result[0] = static_cast<char>('0' + year_number / 1000);
  result[1] = static_cast<char>('0' + (year_number / 100) % 10);
  result[2] = static_cast<char>('0' + (year_number / 10) % 10);
  result[3] = static_cast<char>('0' + year_number % 10);
  result[5] = static_cast<char>('0' + month_number / 10);
  result[6] = static_cast<char>('0' + month_number % 10);
  result[8] = static_cast<char>('0' + day_number / 10);
  result[9] = static_cast<char>('0' + day_number % 10);
  return result;
}

Decimal Decimal::parse(std::string_view text) {
  if (text.empty()) throw Error("invalid_scalar", "decimal must contain digits");
  Decimal result;
  std::size_t begin = 0;
  if (text[0] == '+' || text[0] == '-') {
    result.negative_ = text[0] == '-';
    begin = 1;
  }
  const auto point = text.find('.', begin);
  const auto integer_end = point == std::string_view::npos ? text.size() : point;
  if (begin == integer_end || (point != std::string_view::npos && point + 1 == text.size())) {
    throw Error("invalid_scalar", "decimal requires digits on both sides of a decimal point");
  }
  for (std::size_t i = begin; i < text.size(); ++i) {
    if (i != point && !digit(text[i])) throw Error("invalid_scalar", "decimal admits only an optional sign, digits and one decimal point");
  }
  // Strip insignificant zeros before the precision/scale checks. Exact aliases
  // such as -0.000 and +001.2300 consequently have one stored representation.
  std::size_t fraction_end = text.size();
  if (point != std::string_view::npos) {
    while (fraction_end > point + 1 && text[fraction_end - 1] == '0') --fraction_end;
  }
  const auto scale = point == std::string_view::npos ? 0 : fraction_end - point - 1;
  std::string coefficient;
  coefficient.reserve(std::min<std::size_t>(text.size(), 39));
  bool significant = false;
  for (std::size_t i = begin; i < fraction_end; ++i) {
    if (i == point) continue;
    significant = significant || text[i] != '0';
    if (!significant) continue;
    if (coefficient.size() == 38) throw Error("scalar_overflow", "decimal coefficient exceeds 38 digits");
    coefficient.push_back(text[i]);
  }
  if (coefficient.empty()) return Decimal{};
  if (scale > 38) throw Error("scalar_overflow", "decimal scale exceeds 38");
  result.digits_ = std::move(coefficient);
  result.scale_ = static_cast<std::uint32_t>(scale);
  return result;
}

std::string Decimal::to_string() const {
  std::string result = negative_ ? "-" : "";
  if (scale_ == 0) return result + digits_;
  if (digits_.size() > scale_) {
    const auto point = digits_.size() - scale_;
    return result + digits_.substr(0, point) + "." + digits_.substr(point);
  }
  return result + "0." + std::string(scale_ - digits_.size(), '0') + digits_;
}

std::strong_ordering Decimal::operator<=>(const Decimal& other) const {
  if (digits_ == "0" || other.digits_ == "0") {
    if (digits_ == other.digits_) return std::strong_ordering::equal;
    if (digits_ == "0") return other.negative_ ? std::strong_ordering::greater : std::strong_ordering::less;
    return negative_ ? std::strong_ordering::less : std::strong_ordering::greater;
  }
  if (negative_ != other.negative_) return negative_ ? std::strong_ordering::less : std::strong_ordering::greater;
  const auto exponent = static_cast<std::int64_t>(digits_.size()) - static_cast<std::int64_t>(scale_);
  const auto other_exponent = static_cast<std::int64_t>(other.digits_.size()) - static_cast<std::int64_t>(other.scale_);
  auto order = exponent <=> other_exponent;
  if (order == 0) {
    for (std::size_t i = 0; i < std::max(digits_.size(), other.digits_.size()); ++i) {
      const auto left = i < digits_.size() ? digits_[i] : '0';
      const auto right = i < other.digits_.size() ? other.digits_[i] : '0';
      order = left <=> right;
      if (order != 0) break;
    }
  }
  if (!negative_ || order == 0) return order;
  return order < 0 ? std::strong_ordering::greater : std::strong_ordering::less;
}
}  // namespace crown
