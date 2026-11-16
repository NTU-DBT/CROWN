#include "ranking_detail.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace {
namespace rank = crown::planner::ranking;
using rank::detail::Budget;
using rank::detail::Failure;
using rank::detail::UInt;

void require(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

// Independent oracle: big-endian base-10 ASCII digits. Multiplication uses
// repeated decimal addition and decimal shifts; bit length uses long division
// by two. No production limb access, native-wide product, or rank helper.
std::string canonical(std::string value) {
  const auto first = value.find_first_not_of('0');
  return first == std::string::npos ? "0" : value.substr(first);
}

std::string plus(const std::string& a, const std::string& b) {
  std::string result;
  auto i = a.size();
  auto j = b.size();
  unsigned carry = 0;
  while (i != 0 || j != 0 || carry != 0) {
    unsigned digit = carry;
    if (i != 0) digit += static_cast<unsigned>(a[--i] - '0');
    if (j != 0) digit += static_cast<unsigned>(b[--j] - '0');
    result.push_back(static_cast<char>('0' + digit % 10));
    carry = digit / 10;
  }
  std::reverse(result.begin(), result.end());
  return canonical(result);
}

std::string times(const std::string& a, const std::string& b) {
  std::string result = "0";
  for (const char ch : b) {
    result = canonical(result + '0');
    for (unsigned count = 0; count < static_cast<unsigned>(ch - '0'); ++count) {
      result = plus(result, a);
    }
  }
  return result;
}

std::string predecessor(std::string value) {
  require(value != "0", "decimal predecessor of zero");
  for (std::size_t i = value.size(); i != 0; --i) {
    if (value[i - 1] != '0') {
      --value[i - 1];
      return canonical(value);
    }
    value[i - 1] = '9';
  }
  throw std::runtime_error("invalid decimal predecessor");
}

unsigned bit_length(std::string value) {
  unsigned count = 0;
  while (value != "0") {
    unsigned remainder = 0;
    std::string quotient;
    for (const char ch : value) {
      const auto digit = remainder * 10 + static_cast<unsigned>(ch - '0');
      quotient.push_back(static_cast<char>('0' + digit / 2));
      remainder = digit % 2;
    }
    value = canonical(quotient);
    ++count;
  }
  return count;
}

int ordering(const std::string& a, const std::string& b) {
  if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
  return a == b ? 0 : a < b ? -1 : 1;
}

std::string decimal(const UInt& value) {
  Budget budget{rank::Limits{}};
  return value.decimal(budget);
}

void value_is(const UInt& actual, const std::string& expected) {
  const auto rendered = decimal(actual);
  require(rendered == expected, "decimal mismatch: expected " + expected + ", got " + rendered);
  require(actual.bits() == bit_length(expected), "independent bit-length mismatch");
  require(actual.zero() == (expected == "0"), "zero mismatch");
  require(rendered == canonical(rendered), "noncanonical decimal");
  require(rendered.find_first_not_of("0123456789") == std::string::npos, "nondecimal output");
}

UInt parse_for_driver(const std::string& value) {
  // Only this private unit driver constructs wide values. Each constructed
  // value is checked immediately against the independent decimal oracle.
  Budget budget{rank::Limits{}};
  auto actual = UInt::from(0, budget);
  const auto ten = UInt::from(10, budget);
  for (const char ch : value) {
    const auto digit = UInt::from(static_cast<std::uint64_t>(ch - '0'), budget);
    actual = UInt::add(UInt::multiply(actual, ten, budget), digit, budget);
  }
  value_is(actual, value);
  return actual;
}

template<class Function>
void fails(rank::Stop expected, Function&& operation) {
  try {
    operation();
  } catch (const Failure& failure) {
    require(failure.stop == expected, "wrong arithmetic failure category");
    return;
  }
  throw std::runtime_error("arithmetic operation unexpectedly succeeded");
}

template<class Operation>
void exact_work(Operation operation) {
  Budget measured{rank::Limits{}};
  operation(measured);
  require(measured.usage.work != 0, "operation has no charged work");
  auto limits = rank::Limits{};
  limits.work = measured.usage.work;
  Budget exact{limits};
  operation(exact);
  require(exact.usage.work == limits.work, "exact work budget not reproducible");
  --limits.work;
  Budget short_budget{limits};
  fails(rank::Stop::work_limit, [&] { operation(short_budget); });
  require(short_budget.usage.work <= limits.work, "work counter exceeded its cap");
}

void binary_value(const UInt& a, const UInt& b, const std::string& expected, bool multiply) {
  Budget budget{rank::Limits{}};
  if (bit_length(expected) > 512) {
    fails(rank::Stop::bit_limit, [&] {
      if (multiply) static_cast<void>(UInt::multiply(a, b, budget));
      else static_cast<void>(UInt::add(a, b, budget));
    });
    return;
  }
  const auto actual = multiply ? UInt::multiply(a, b, budget) : UInt::add(a, b, budget);
  value_is(actual, expected);
  auto limits = rank::Limits{};
  limits.score_bits = std::max(1U, bit_length(expected));
  Budget exact{limits};
  value_is(multiply ? UInt::multiply(a, b, exact) : UInt::add(a, b, exact), expected);
  if (limits.score_bits > 1) {
    --limits.score_bits;
    Budget short_budget{limits};
    fails(rank::Stop::bit_limit, [&] {
      if (multiply) static_cast<void>(UInt::multiply(a, b, short_budget));
      else static_cast<void>(UInt::add(a, b, short_budget));
    });
  }
}

void primitive_inputs() {
  const std::array<std::uint64_t, 12> values{
      0, 1, 2, 3, 0x7fffffffULL, 0x80000000ULL, 0xffffffffULL,
      0x100000000ULL, 0x100000001ULL, 0x7fffffffffffffffULL,
      std::numeric_limits<std::uint64_t>::max() - 1,
      std::numeric_limits<std::uint64_t>::max()};
  for (const auto value : values) {
    Budget budget{rank::Limits{}};
    value_is(UInt::from(value, budget), std::to_string(value));
    exact_work([&](Budget& b) { static_cast<void>(UInt::from(value, b)); });
    auto limits = rank::Limits{};
    limits.score_bits = std::max(1U, bit_length(std::to_string(value)));
    Budget exact{limits};
    value_is(UInt::from(value, exact), std::to_string(value));
    if (limits.score_bits > 1) {
      --limits.score_bits;
      Budget short_budget{limits};
      fails(rank::Stop::bit_limit, [&] { static_cast<void>(UInt::from(value, short_budget)); });
    }
  }
  for (const unsigned invalid : {0U, 513U}) {
    auto limits = rank::Limits{};
    limits.score_bits = invalid;
    fails(rank::Stop::invalid_limits, [&] { Budget unused{limits}; });
  }
}

std::vector<std::string> boundary_values() {
  std::set<std::string> values{"0", "1", "2", "3", "18446744073709551614", "18446744073709551615"};
  std::string power = "1";
  for (unsigned bit = 1; bit <= 512; ++bit) {
    power = plus(power, power);
    if (bit % 32 != 0) continue;
    values.insert(predecessor(power));
    if (bit < 512) {
      values.insert(power);
      values.insert(plus(power, "1"));
    }
  }
  // Alternating and sparse decimal operands give unequal low limbs and carry
  // patterns beyond powers of two, without depending on the binary backend.
  values.insert("123456789012345678901234567890123456789012345678901234567890");
  values.insert("98765432109876543210987654321098765432109876543210987654321");
  values.insert("100000000000000000000000000000000000000000000000000000000001");
  return {values.begin(), values.end()};
}

void cross_boundary_arithmetic() {
  const auto expected = boundary_values();
  std::vector<UInt> values;
  for (const auto& value : expected) values.push_back(parse_for_driver(value));
  std::size_t pairs = 0;
  for (std::size_t i = 0; i < values.size(); ++i) {
    for (std::size_t j = 0; j < values.size(); ++j) {
      const auto left = decimal(values[i]);
      const auto right = decimal(values[j]);
      binary_value(values[i], values[j], plus(expected[i], expected[j]), false);
      binary_value(values[i], values[j], times(expected[i], expected[j]), true);
      Budget compare{rank::Limits{}};
      require(UInt::compare(values[i], values[j], compare) == ordering(expected[i], expected[j]),
              "independent decimal ordering mismatch");
      require(decimal(values[i]) == left && decimal(values[j]) == right, "operand modified");
      ++pairs;
    }
  }
  std::cout << "independent decimal arithmetic values=" << values.size() << " ordered_pairs=" << pairs << '\n';
}

void budgets_and_aliases() {
  const auto a = parse_for_driver("18446744073709551615");
  const auto b = parse_for_driver("340282366920938463463374607431768211455");
  const auto one = parse_for_driver("1");
  const auto zero = parse_for_driver("0");
  exact_work([&](Budget& budget) { static_cast<void>(UInt::add(a, b, budget)); });
  exact_work([&](Budget& budget) { static_cast<void>(UInt::multiply(a, b, budget)); });
  exact_work([&](Budget& budget) { static_cast<void>(UInt::compare(a, b, budget)); });
  for (const auto& value : {zero, one, a, b}) {
    exact_work([&](Budget& budget) { static_cast<void>(value.decimal(budget)); });
    auto limits = rank::Limits{};
    const auto text = decimal(value);
    limits.payload_bytes = static_cast<std::uint64_t>(text.size());
    Budget exact{limits};
    require(value.decimal(exact) == text, "exact decimal byte cap failed");
    --limits.payload_bytes;
    Budget short_budget{limits};
    std::string retained = "prior-result";
    fails(rank::Stop::byte_limit, [&] { retained = value.decimal(short_budget); });
    require(retained == "prior-result" && decimal(value) == text, "decimal failure published partial output");
  }
  auto alias = a;
  auto limits = rank::Limits{};
  limits.work = 0;
  Budget no_work{limits};
  fails(rank::Stop::work_limit, [&] { alias = UInt::add(alias, alias, no_work); });
  value_is(alias, "18446744073709551615");
  Budget no_multiply{limits};
  fails(rank::Stop::work_limit, [&] { alias = UInt::multiply(alias, alias, no_multiply); });
  value_is(alias, "18446744073709551615");
  Budget exact{rank::Limits{}};
  alias = UInt::multiply(alias, alias, exact);
  value_is(alias, "340282366920938463426481119284349108225");
  const auto old = decimal(alias);
  limits = rank::Limits{};
  limits.score_bits = 64;
  Budget low_cap{limits};
  fails(rank::Stop::bit_limit, [&] { alias = UInt::add(alias, alias, low_cap); });
  require(decimal(alias) == old, "aliased bit failure modified old result");
  std::string power512 = "1";
  for (unsigned bit = 0; bit < 512; ++bit) power512 = plus(power512, power512);
  auto largest = parse_for_driver(predecessor(power512));
  const auto largest_text = decimal(largest);
  require(bit_length(largest_text) == 512, "max512 fixture size");
  require(largest_text.size() == 155, "max512 decimal digit count");
  exact_work([&](Budget& budget) { static_cast<void>(largest.decimal(budget)); });
  limits = rank::Limits{};
  limits.payload_bytes = 155;
  Budget exact_digits{limits};
  require(largest.decimal(exact_digits) == largest_text, "155-digit exact byte cap failed");
  --limits.payload_bytes;
  Budget short_digits{limits};
  std::string prior = "owned-history";
  fails(rank::Stop::byte_limit, [&] { prior = largest.decimal(short_digits); });
  require(prior == "owned-history", "max512 failed export replaced retained string");
  Budget carry{rank::Limits{}};
  fails(rank::Stop::bit_limit, [&] { largest = UInt::add(largest, one, carry); });
  require(decimal(largest) == largest_text, "max512 carry modified operand");
  Budget overflow{rank::Limits{}};
  fails(rank::Stop::bit_limit, [&] { largest = UInt::multiply(largest, largest, overflow); });
  require(decimal(largest) == largest_text, "max512 product modified operand");
}
}  // namespace

int main() {
  try {
    primitive_inputs();
    cross_boundary_arithmetic();
    budgets_and_aliases();
    std::cout << "independent integer groups=3 boundaries=16\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << "independent integer failure: " << error.what() << '\n';
    return 1;
  } catch (const Failure& failure) {
    std::cerr << "unexpected integer stop=" << static_cast<unsigned>(failure.stop) << '\n';
    return 2;
  }
}
