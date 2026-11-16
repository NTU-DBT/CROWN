#pragma once

// Private W04 arithmetic. Admitted groups have at most INT64_MAX rows of
// int64 input; their exact signed sum fits 127 bits. SQL output keeps its
// separately declared type/scale. See docs/aggregates.md.
#include "crown/storage/accounted_row.hpp"
#include <array>
#include <cassert>
#include <compare>
#include <cstdint>
#include <limits>
#include <string_view>

namespace crown::runtime::aggregate::detail {

struct Magnitude {
  std::uint64_t high = 0, low = 0;
  auto operator<=>(const Magnitude&) const = default;
  [[nodiscard]] bool zero() const noexcept { return high == 0 && low == 0; }
};

// Four 32-bit partial products form the exact 64-by-64 product without a
// compiler-specific extended integer or an allocating arbitrary-precision type.
[[nodiscard]] inline Magnitude multiply(std::uint64_t left, std::uint64_t right) noexcept {
  constexpr std::uint64_t mask = UINT32_MAX;
  const auto a = left & mask, b = left >> 32;
  const auto c = right & mask, d = right >> 32;
  const auto first = a * c;
  const auto second = b * c + (first >> 32);
  const auto third = a * d + (second & mask);
  return {b * d + (second >> 32) + (third >> 32), (third << 32) | (first & mask)};
}

// Callers have already admitted the group row bound; signed-sum intermediates
// stay below 2^127. The extra word carry therefore cannot overflow high.
[[nodiscard]] inline Magnitude add(Magnitude left, Magnitude right) noexcept {
  const auto low = left.low + right.low;
  return {left.high + right.high + static_cast<std::uint64_t>(low < left.low), low};
}

// Precondition left >= right is established by the signed caller's comparison.
[[nodiscard]] inline Magnitude subtract(Magnitude left, Magnitude right) noexcept {
  return {left.high - right.high - static_cast<std::uint64_t>(left.low < right.low), left.low - right.low};
}

struct Quotient { Magnitude value; std::uint64_t remainder; };

// Divisor is a positive admitted SQL count (at most INT64_MAX). The remainder
// is always below it, so shifting the next numerator bit fits uint64 exactly.
[[nodiscard]] inline Quotient divide(Magnitude numerator, std::uint64_t divisor) noexcept {
  assert(divisor > 0 && divisor <= static_cast<std::uint64_t>(INT64_MAX));
  Quotient out{{}, 0};
  for (unsigned position = 128; position > 0; --position) {
    const auto bit = position - 1;
    const auto incoming = bit >= 64 ? (numerator.high >> (bit - 64)) & 1 : (numerator.low >> bit) & 1;
    out.remainder = (out.remainder << 1) | incoming;
    if (out.remainder >= divisor) {
      out.remainder -= divisor;
      if (bit >= 64) out.value.high |= std::uint64_t{1} << (bit - 64);
      else out.value.low |= std::uint64_t{1} << bit;
    }
  }
  return out;
}

// Decimal rendering divides four base-2^32 words by ten. This fixed stack
// workspace is used only for requested output, not for every state update.
[[nodiscard]] inline std::uint32_t decimal_digit(Magnitude& value) noexcept {
  std::array<std::uint32_t, 4> words{
      static_cast<std::uint32_t>(value.high >> 32), static_cast<std::uint32_t>(value.high),
      static_cast<std::uint32_t>(value.low >> 32), static_cast<std::uint32_t>(value.low)};
  std::uint64_t remainder = 0;
  for (auto& word : words) {
    const auto current = (remainder << 32) | word;
    word = static_cast<std::uint32_t>(current / 10);
    remainder = current % 10;
  }
  value = {(static_cast<std::uint64_t>(words[0]) << 32) | words[1],
           (static_cast<std::uint64_t>(words[2]) << 32) | words[3]};
  return static_cast<std::uint32_t>(remainder);
}

// Coefficient has at most 38 digits and scale is 0..18. InlineDecimal owns
// the returned digits; no string view into these stack buffers escapes.
[[nodiscard]] inline storage::InlineDecimal decimal(Magnitude coefficient, bool negative, std::uint8_t scale) {
  std::array<char, 38> digits{};
  std::size_t count = 0;
  const bool nonzero = !coefficient.zero();
  do {
    assert(count < digits.size());
    digits[count++] = static_cast<char>('0' + decimal_digit(coefficient));
  } while (!coefficient.zero());
  std::array<char, storage::InlineDecimal::text_capacity> text{};
  std::size_t length = 0;
  if (negative && nonzero) text[length++] = '-';
  const auto places = static_cast<std::size_t>(scale);
  if (places >= count) {
    text[length++] = '0';
    if (places) text[length++] = '.';
    for (std::size_t i = count; i < places; ++i) text[length++] = '0';
  }
  for (std::size_t i = count; i > 0; --i) {
    text[length++] = digits[i - 1];
    if (places && places < count && i == places + 1) text[length++] = '.';
  }
  return storage::InlineDecimal::parse(std::string_view(text.data(), length));
}

// One trivially copied sufficient statistic. Group existence and non-null
// count are separate state: a live group's signed sum may cancel to zero.
class IntegerSum {
 public:
  // Add or retract value*multiplicity after the caller checks row-count bounds.
  // INT64_MIN is converted without signed negation overflow.
  void replace(std::int64_t value, std::uint64_t multiplicity, bool erase) noexcept {
    if (value == 0 || multiplicity == 0) return;
    const auto absolute = value < 0 ? static_cast<std::uint64_t>(-(value + 1)) + 1 : static_cast<std::uint64_t>(value);
    const auto term = multiply(absolute, multiplicity);
    const bool negative = (value < 0) != erase;
    if (negative_ == negative) magnitude_ = add(magnitude_, term);
    else if (magnitude_ >= term) magnitude_ = subtract(magnitude_, term);
    else { magnitude_ = subtract(term, magnitude_); negative_ = negative; }
    if (magnitude_.zero()) negative_ = false;
  }
  [[nodiscard]] bool fits_int64() const noexcept {
    const auto limit = negative_ ? (std::uint64_t{1} << 63) : static_cast<std::uint64_t>(INT64_MAX);
    return magnitude_.high == 0 && magnitude_.low <= limit;
  }
  [[nodiscard]] std::int64_t int64_value() const noexcept {
    assert(fits_int64());
    if (negative_ && magnitude_.low == (std::uint64_t{1} << 63)) return INT64_MIN;
    const auto value = static_cast<std::int64_t>(magnitude_.low);
    return negative_ ? -value : value;
  }
  [[nodiscard]] storage::InlineDecimal value() const { return decimal(magnitude_, negative_, 0); }
  // Count matches this sum's exact non-NULL multiplicity (1..INT64_MAX).
  // Scale is fixed by the bound
  // output type; ties round away from zero without floating-point conversion.
  [[nodiscard]] storage::InlineDecimal average(std::uint64_t count, std::uint8_t scale) const {
    assert(scale <= 18);
    std::uint64_t factor = 1;
    for (std::uint8_t i = 0; i < scale; ++i) factor *= 10;
    const auto whole = divide(magnitude_, count);
    assert(whole.value.high == 0);
    const auto fraction = divide(multiply(whole.remainder, factor), count);
    auto coefficient = add(multiply(whole.value.low, factor), fraction.value);
    if (fraction.remainder >= count - fraction.remainder) coefficient = add(coefficient, {0, 1});
    return decimal(coefficient, negative_, scale);
  }
 private:
  Magnitude magnitude_;
  bool negative_ = false;
};
}  // namespace crown::runtime::aggregate::detail
