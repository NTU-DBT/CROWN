#include "crown/annotations/policy.hpp"
#include <iostream>
#include <stdexcept>
#include <type_traits>

namespace {
using namespace crown;
using namespace crown::annotations;
void check(bool condition, const char* message) {
  if (!condition) throw std::runtime_error(message);
}
template<class F> void rejects(F action, std::string_view code) {
  try { action(); }
  catch (const Error& error) { check(error.code() == code, "wrong annotation error"); return; }
  throw std::runtime_error("expected annotation rejection");
}
DecimalPayload d(std::string_view text) { return {Decimal::parse(text)}; }
void support_and_payload() {
  static_assert(!std::is_convertible_v<Multiplicity, IntegerPayload>);
  static_assert(!std::is_convertible_v<IntegerPayload, Multiplicity>);
  const MultiplicityPolicy counts;
  const IntegerPolicy integers;
  const Annotation<IntegerPayload> two{{2}, {7}};
  const auto three = replace_contribution(two, {}, Annotation<IntegerPayload>{{1}, {-7}}, counts, integers);
  check(three.present() && three.support.value == 3 && three.payload.value == 0,
        "SUM cancellation erased a live group");
  const ValueChange<IntegerPayload> cancellation{two, three};
  check(cancellation.membership() == MembershipChange::unchanged && cancellation.support_changed() &&
        cancellation.payload_changed(), "count and numeric changes need their own events");
  const ValueChange<IntegerPayload> weight{{{2}, {0}}, {{3}, {0}}};
  check(weight.membership() == MembershipChange::unchanged && weight.support_changed() && !weight.payload_changed(),
        "weight-only change was lost");
  const auto replaced = replace_contribution(three, Annotation<IntegerPayload>{{1}, {-7}},
                                           Annotation<IntegerPayload>{{1}, {-9}}, counts, integers);
  const ValueChange<IntegerPayload> payload{three, replaced};
  check(payload.membership() == MembershipChange::unchanged && !payload.support_changed() && payload.payload_changed(),
        "payload-only replacement was lost");
  const auto gone = replace_contribution(replaced, replaced, {}, counts, integers);
  check(!gone.present() && gone.payload.value == 0 &&
        ValueChange<IntegerPayload>{replaced, gone}.membership() == MembershipChange::disappeared,
        "last contribution must produce an explicit disappearance");
  check(ValueChange<IntegerPayload>{gone, two}.membership() == MembershipChange::appeared,
        "first contribution must produce an appearance");
  rejects([&] { static_cast<void>(replace_contribution(two, Annotation<IntegerPayload>{{2}, {8}}, {}, counts, integers)); },
          "invalid_annotation");
  rejects([&] { static_cast<void>(replace_contribution(two, Annotation<IntegerPayload>{{0}, {8}}, {}, counts, integers)); },
          "invalid_annotation");

  const auto maximum = std::numeric_limits<std::int64_t>::max();
  const Annotation<IntegerPayload> stable{{2}, {maximum}};
  rejects([&] { static_cast<void>(replace_contribution(stable, {}, Annotation<IntegerPayload>{{1}, {1}}, counts, integers)); },
          "annotation_overflow");
  check(stable == Annotation<IntegerPayload>{{2}, {maximum}}, "failed preparation mutated its input");
  check(integers.replace({maximum}, {-1}, {-1}).value == maximum,
        "representable replacement rejected an unrepresentable intermediate");
  const auto minimum = std::numeric_limits<std::int64_t>::min();
  check(integers.replace({minimum}, {1}, {1}).value == minimum, "negative replacement intermediate");
  rejects([&] { static_cast<void>(integers.multiply({minimum}, IntegerPayload{-1})); }, "annotation_overflow");
  check(integers.multiply({-1}, Multiplicity{std::uint64_t{1} << 63}).value == minimum,
        "unsigned weight must not narrow to signed int64");

  const DecimalPolicy decimals({38, 18});
  const Annotation<DecimalPayload> original{{1}, d("1.25")};
  const auto zero_sum = replace_contribution(original, {}, Annotation<DecimalPayload>{{1}, d("-1.25")}, counts, decimals);
  check(zero_sum.present() && zero_sum.payload == d("0"), "decimal zero SUM erased a group");
  check(ValueChange<DecimalPayload>{original, zero_sum}.payload_changed(), "decimal payload event missing");
  const MultiplicityPolicy small(3);
  check(small.replace({3}, {1}, {1}).value == 3, "count replacement should retract before adding");
  rejects([&] { static_cast<void>(small.add({3}, {1})); }, "annotation_overflow");
  rejects([&] { static_cast<void>(small.remove({1}, {2})); }, "annotation_underflow");
  rejects([&] { static_cast<void>(small.multiply({4}, {0})); }, "annotation_overflow");
  rejects([] { static_cast<void>(MultiplicityPolicy(0)); }, "invalid_annotation");
}
void decimals() {
  const DecimalPolicy policy({6, 2});
  check(policy.add(d("1.2"), d("-0.21")) == d("0.99"), "exact scale alignment");
  check(policy.multiply(d("1.2"), d("2.5")) == d("3"), "exact product removes only insignificant zeros");
  rejects([&] { static_cast<void>(policy.multiply(d("0.01"), d("0.01"))); }, "annotation_overflow");
  rejects([&] { static_cast<void>(policy.add(d("9999.99"), d("0.01"))); }, "annotation_overflow");
  rejects([&] { static_cast<void>(policy.add(d("0.001"), d("0"))); }, "annotation_overflow");
  check(policy.replace(d("9999.99"), d("-0.01"), d("-0.01")) == d("9999.99"),
        "only the final decimal replacement needs to fit");
  const DecimalPolicy fractions({38, 38});
  check(fractions.add(d("0"), d("0")) == d("0"), "DECIMAL(p,p) admits canonical zero");
  check(fractions.add(d("0.00000000000000000000000000000000000001"),
                      d("-0.00000000000000000000000000000000000001")) == d("0"),
        "scale38 signed cancellation");
  rejects([&] { static_cast<void>(fractions.multiply(d("0.00000000000000000001"),
                                                               d("0.00000000000000000001"))); }, "annotation_overflow");
  const DecimalPolicy wide({38, 0});
  const auto max = d("99999999999999999999999999999999999999");
  check(wide.replace(max, d("-1"), d("-1")) == max, "39-digit replacement intermediate");
  check(wide.multiply(d("1"), Multiplicity{9007199254740993ULL}) == d("9007199254740993"),
        "decimal weight above binary64 precision stays exact");
  check(wide.multiply(max, d("0")) == d("0"), "max precision multiplied by zero");
  rejects([&] { static_cast<void>(wide.multiply(max, max)); }, "annotation_overflow");
}
void admission() {
  const auto set = admit({}, Backend::certified_set_tree);
  check(set.admitted() && set.policy == "exact-nonnull-v1" && set.capabilities.zero_sum_free &&
        !set.capabilities.additive_cancellation && !set.capabilities.exact_retraction,
        "Boolean support cannot retract without witness state");
  for (const auto domain : {Domain::boolean_support, Domain::nonnegative_multiplicity,
                            Domain::signed_integer, Domain::fixed_decimal}) {
    Request request{domain, Deletion::replacement, {}};
    if (domain == Domain::fixed_decimal) request.decimal = DecimalSpec{38, 18};
    const auto kernel = admit(request, Backend::arithmetic_policy);
    check(kernel.admitted() && kernel.capabilities.exact && kernel.capabilities.replacement,
          "supported exact policy rejected");
    check(admit(request, Backend::certified_set_tree).admitted() == (domain == Domain::boolean_support),
          "arithmetic kernels must not grant a weighted maintenance theorem");
    request.deletion = Deletion::exact_retraction;
    check(admit(request, Backend::arithmetic_policy).admitted() == (domain != Domain::boolean_support),
          "deletion capabilities differ from replacement");
  }
  check(!admit({Domain::signed_integer}, Backend::arithmetic_policy).capabilities.zero_sum_free,
        "signed payload has additive cancellation");
  check(admit({Domain::nonnegative_multiplicity}, Backend::arithmetic_policy).capabilities.zero_sum_free,
        "nonnegative multiplicity is zero-sum-free");
  for (const auto domain : {Domain::general_semiring, Domain::approximate, static_cast<Domain>(99)})
    for (const auto backend : {Backend::arithmetic_policy, Backend::certified_set_tree})
      check(!admit({domain}, backend).admitted(), "unsupported algebra admitted");
  check(admit({Domain::fixed_decimal}, Backend::arithmetic_policy).status == AdmissionStatus::invalid_decimal,
        "decimal requires an explicit result specification");
  for (const auto spec : {DecimalSpec{0, 0}, DecimalSpec{39, 2}, DecimalSpec{3, 4}}) {
    check(admit({Domain::fixed_decimal, Deletion::replacement, spec}, Backend::arithmetic_policy).status == AdmissionStatus::invalid_decimal,
          "invalid decimal specification admitted");
    rejects([&] { static_cast<void>(DecimalPolicy(spec)); }, "invalid_annotation");
  }
  check(admit({Domain::signed_integer, Deletion::replacement, DecimalSpec{3, 2}}, Backend::arithmetic_policy).status == AdmissionStatus::unexpected_decimal,
        "foreign decimal specification ignored");
  check(!admit({Domain::signed_integer, static_cast<Deletion>(99), {}}, Backend::arithmetic_policy).admitted(),
        "unknown deletion admitted");
  check(!admit({}, static_cast<Backend>(99)).admitted(), "unknown backend admitted");
}
}  // namespace
int main() {
  try {
    support_and_payload();
    decimals();
    admission();
    std::cout << "Annotation support, payload, replacement and closed admission checks passed\n";
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n'; return 1;
  }
}
