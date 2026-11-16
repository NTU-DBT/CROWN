#include "crown/annotations/policy.hpp"

#include <algorithm>
#include <array>
#include <cstddef>
#include <string>

namespace crown::annotations {
namespace {
[[noreturn]] void overflow() {
  throw Error("annotation_overflow", "exact annotation result exceeds its declared domain");
}
bool valid_spec(DecimalSpec spec) noexcept {
  return spec.precision >= 1 && spec.precision <= 38 && spec.scale <= spec.precision;
}
// At most 76 aligned/product digits, plus a carry for a three-term replacement.
// All scratch arithmetic stays on the stack; only the final Decimal owns text.
struct Coefficient {
  std::array<unsigned char, 80> digits{};  // Least significant first.
  std::size_t size = 1;
  bool negative = false;
};
void normalize(Coefficient& value) {
  while (value.size > 1 && value.digits[value.size - 1] == 0) --value.size;
  if (value.size == 1 && value.digits[0] == 0) value.negative = false;
}
Coefficient coefficient(std::uint64_t value) {
  Coefficient result;
  result.size = 0;
  do {
    result.digits[result.size++] = static_cast<unsigned char>(value % 10);
    value /= 10;
  } while (value != 0);
  return result;
}
Coefficient coefficient(IntegerPayload value) {
  const auto magnitude = value.value < 0 ? std::uint64_t{0} - static_cast<std::uint64_t>(value.value)
                                        : static_cast<std::uint64_t>(value.value);
  auto result = coefficient(magnitude);
  result.negative = value.value < 0;
  return result;
}
Coefficient coefficient(const DecimalPayload& value, std::uint32_t scale) {
  const auto parts = value.value.parts();
  Coefficient result;
  const auto shift = static_cast<std::size_t>(scale - parts.scale);
  result.size = parts.digits.size() + shift;
  for (std::size_t i = 0; i < parts.digits.size(); ++i)
    result.digits[i + shift] = static_cast<unsigned char>(parts.digits[parts.digits.size() - i - 1] - '0');
  result.negative = parts.negative;
  normalize(result);
  return result;
}
int compare(const Coefficient& a, const Coefficient& b) {
  if (a.size != b.size) return a.size < b.size ? -1 : 1;
  for (std::size_t i = a.size; i != 0; --i)
    if (a.digits[i - 1] != b.digits[i - 1]) return a.digits[i - 1] < b.digits[i - 1] ? -1 : 1;
  return 0;
}
Coefficient negate(Coefficient value) {
  value.negative = !value.negative;
  normalize(value);
  return value;
}
Coefficient add(const Coefficient& a, const Coefficient& b) {
  Coefficient result;
  if (a.negative == b.negative) {
    result.size = std::max(a.size, b.size);
    unsigned carry = 0;
    for (std::size_t i = 0; i < result.size; ++i) {
      const auto sum = static_cast<unsigned>(a.digits[i]) + b.digits[i] + carry;
      result.digits[i] = static_cast<unsigned char>(sum % 10);
      carry = sum / 10;
    }
    if (carry != 0) result.digits[result.size++] = static_cast<unsigned char>(carry);
    result.negative = a.negative;
  } else {
    const bool a_larger = compare(a, b) >= 0;
    const auto& larger = a_larger ? a : b;
    const auto& smaller = a_larger ? b : a;
    result.size = larger.size;
    int borrow = 0;
    for (std::size_t i = 0; i < result.size; ++i) {
      const int difference = larger.digits[i] - smaller.digits[i] - borrow;
      result.digits[i] = static_cast<unsigned char>(difference < 0 ? difference + 10 : difference);
      borrow = difference < 0 ? 1 : 0;
    }
    result.negative = larger.negative;
  }
  normalize(result);
  return result;
}
Coefficient multiply(const Coefficient& a, const Coefficient& b) {
  std::array<unsigned, 80> products{};
  for (std::size_t i = 0; i < a.size; ++i)
    for (std::size_t j = 0; j < b.size; ++j)
      products[i + j] += static_cast<unsigned>(a.digits[i]) * b.digits[j];
  Coefficient result;
  result.size = a.size + b.size;
  unsigned carry = 0;
  for (std::size_t i = 0; i < result.size; ++i) {
    const auto digit = products[i] + carry;
    result.digits[i] = static_cast<unsigned char>(digit % 10);
    carry = digit / 10;
  }
  result.negative = a.negative != b.negative;
  normalize(result);
  return result;
}
IntegerPayload integer(const Coefficient& value) {
  constexpr auto maximum = static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::max());
  const auto limit = value.negative ? maximum + 1 : maximum;
  std::uint64_t magnitude = 0;
  for (std::size_t i = value.size; i != 0; --i) {
    const auto digit = value.digits[i - 1];
    if (magnitude > (limit - digit) / 10) overflow();
    magnitude = magnitude * 10 + digit;
  }
  if (value.negative && magnitude == maximum + 1) return {std::numeric_limits<std::int64_t>::min()};
  const auto result = static_cast<std::int64_t>(magnitude);
  return {value.negative ? -result : result};
}
DecimalPayload decimal(Coefficient value, std::uint32_t scale, DecimalSpec spec) {
  if (value.size == 1 && value.digits[0] == 0) return {};
  while (scale != 0 && value.digits[0] == 0) {
    std::move(value.digits.begin() + 1, value.digits.begin() + static_cast<std::ptrdiff_t>(value.size), value.digits.begin());
    value.digits[--value.size] = 0;
    --scale;
    if (value.size == 0) { value.size = 1; scale = 0; break; }
  }
  const auto integer_digits = value.size > scale ? value.size - scale : 0;
  if (value.size > 38 || scale > spec.scale || integer_digits > spec.precision - spec.scale) overflow();
  std::string text;
  if (value.negative) text.push_back('-');
  if (scale >= value.size) text += "0." + std::string(scale - value.size, '0');
  for (std::size_t i = value.size; i != 0; --i) {
    text.push_back(static_cast<char>('0' + value.digits[i - 1]));
    if (i > 1 && i - 1 == scale) text.push_back('.');
  }
  return {Decimal::parse(text)};
}
}  // namespace

MultiplicityPolicy::MultiplicityPolicy(std::uint64_t limit) : limit_(limit) {
  if (limit == 0) throw Error("invalid_annotation", "multiplicity limit must be positive");
}
void MultiplicityPolicy::validate(Multiplicity value) const {
  if (value.value > limit_) overflow();
}
Multiplicity MultiplicityPolicy::add(Multiplicity a, Multiplicity b) const {
  validate(a); validate(b);
  if (b.value > limit_ - a.value) overflow();
  return {a.value + b.value};
}
Multiplicity MultiplicityPolicy::multiply(Multiplicity a, Multiplicity b) const {
  validate(a); validate(b);
  if (b.value != 0 && a.value > limit_ / b.value) overflow();
  return {a.value * b.value};
}
Multiplicity MultiplicityPolicy::remove(Multiplicity total, Multiplicity old) const {
  validate(total); validate(old);
  if (old.value > total.value) throw Error("annotation_underflow", "removed multiplicity exceeds the current total");
  return {total.value - old.value};
}
Multiplicity MultiplicityPolicy::replace(Multiplicity total, Multiplicity old, Multiplicity next) const {
  return add(remove(total, old), next);
}

IntegerPayload IntegerPolicy::add(IntegerPayload a, IntegerPayload b) {
  return integer(annotations::add(coefficient(a), coefficient(b)));
}
IntegerPayload IntegerPolicy::multiply(IntegerPayload a, IntegerPayload b) {
  return integer(annotations::multiply(coefficient(a), coefficient(b)));
}
IntegerPayload IntegerPolicy::multiply(IntegerPayload a, Multiplicity b) {
  return integer(annotations::multiply(coefficient(a), coefficient(b.value)));
}
IntegerPayload IntegerPolicy::remove(IntegerPayload total, IntegerPayload old) {
  return integer(annotations::add(coefficient(total), negate(coefficient(old))));
}
IntegerPayload IntegerPolicy::replace(IntegerPayload total, IntegerPayload old, IntegerPayload next) {
  return integer(annotations::add(annotations::add(coefficient(total), negate(coefficient(old))), coefficient(next)));
}

DecimalPolicy::DecimalPolicy(DecimalSpec spec) : specification_(spec) {
  if (!valid_spec(spec)) throw Error("invalid_annotation", "decimal policy requires 1 <= precision <= 38 and scale <= precision");
}
void DecimalPolicy::validate(const DecimalPayload& value) const {
  const auto parts = value.value.parts();
  const auto integer_digits = parts.digits == "0" ? 0 : parts.digits.size() > parts.scale ? parts.digits.size() - parts.scale : 0;
  if (parts.scale > specification_.scale || integer_digits > specification_.precision - specification_.scale) overflow();
}
DecimalPayload DecimalPolicy::add(const DecimalPayload& a, const DecimalPayload& b) const {
  validate(a); validate(b);
  const auto scale = std::max(a.value.parts().scale, b.value.parts().scale);
  return decimal(annotations::add(coefficient(a, scale), coefficient(b, scale)), scale, specification_);
}
DecimalPayload DecimalPolicy::multiply(const DecimalPayload& a, const DecimalPayload& b) const {
  validate(a); validate(b);
  const auto left_scale = a.value.parts().scale, right_scale = b.value.parts().scale;
  return decimal(annotations::multiply(coefficient(a, left_scale), coefficient(b, right_scale)),
                 left_scale + right_scale, specification_);
}
DecimalPayload DecimalPolicy::multiply(const DecimalPayload& a, Multiplicity b) const {
  validate(a);
  const auto scale = a.value.parts().scale;
  return decimal(annotations::multiply(coefficient(a, scale), coefficient(b.value)), scale, specification_);
}
DecimalPayload DecimalPolicy::remove(const DecimalPayload& total, const DecimalPayload& old) const {
  return replace(total, old, {});
}
DecimalPayload DecimalPolicy::replace(const DecimalPayload& total, const DecimalPayload& old, const DecimalPayload& next) const {
  validate(total); validate(old); validate(next);
  const auto scale = std::max({total.value.parts().scale, old.value.parts().scale, next.value.parts().scale});
  return decimal(annotations::add(annotations::add(coefficient(total, scale), negate(coefficient(old, scale))),
                                  coefficient(next, scale)), scale, specification_);
}

Admission admit(const Request& request, Backend backend) noexcept {
  Admission result{AdmissionStatus::admitted, {}, {}};
  auto& c = result.capabilities;
  switch (request.domain) {
    case Domain::boolean_support:
      c = {true, true, true, false, false, true, Representation::fixed_word};
      result.policy = "exact-nonnull-v1"; break;
    case Domain::nonnegative_multiplicity:
      c = {true, true, true, true, true, true, Representation::fixed_word};
      result.policy = MultiplicityPolicy::name; break;
    case Domain::signed_integer:
      c = {true, false, true, true, true, true, Representation::fixed_word};
      result.policy = IntegerPolicy::name; break;
    case Domain::fixed_decimal:
      c = {true, false, true, true, true, true, Representation::bounded_decimal};
      result.policy = DecimalPolicy::name; break;
    case Domain::general_semiring: case Domain::approximate:
      result.status = AdmissionStatus::unsupported_algebra; return result;
    default: result.status = AdmissionStatus::unknown_domain; return result;
  }
  if (request.domain == Domain::fixed_decimal) {
    if (!request.decimal || !valid_spec(*request.decimal)) result.status = AdmissionStatus::invalid_decimal;
  } else if (request.decimal) result.status = AdmissionStatus::unexpected_decimal;
  if (result.status != AdmissionStatus::admitted) return result;
  if ((request.deletion == Deletion::exact_retraction && !c.exact_retraction) ||
      (request.deletion != Deletion::none && request.deletion != Deletion::exact_retraction && request.deletion != Deletion::replacement))
    result.status = AdmissionStatus::unsupported_deletion;
  else if (backend != Backend::arithmetic_policy &&
           !((backend == Backend::certified_set_tree && request.domain == Domain::boolean_support) ||
             (backend == Backend::weighted_subtree_messages && request.domain == Domain::nonnegative_multiplicity)))
    result.status = AdmissionStatus::unsupported_backend;
  return result;
}
void require_set_backend_policy(std::string_view policy) {
  const auto admitted = admit({}, Backend::certified_set_tree);
  if (!admitted.admitted() || policy != admitted.policy)
    throw Error("invalid_policy", "the set backend requires its exact supported annotation policy");
}
}  // namespace crown::annotations
