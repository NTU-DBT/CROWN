#pragma once

#include "crown/api/error.hpp"
#include "crown/ir/model.hpp"
#include <cstdint>
#include <initializer_list>
#include <limits>
#include <optional>
#include <string_view>

namespace crown::annotations {
// Presence belongs to support, never to the sign or zero of a SUM payload.
struct Multiplicity {
  std::uint64_t value = 0;
  [[nodiscard]] bool present() const noexcept { return value != 0; }
  auto operator<=>(const Multiplicity&) const = default;
};
struct IntegerPayload {
  std::int64_t value = 0;
  auto operator<=>(const IntegerPayload&) const = default;
};
struct DecimalPayload {
  Decimal value;
  bool operator==(const DecimalPayload&) const = default;
};

class MultiplicityPolicy {
 public:
  static constexpr std::string_view name = "checked-uint64-multiplicity-v1";
  explicit MultiplicityPolicy(std::uint64_t limit = std::numeric_limits<std::uint64_t>::max());
  [[nodiscard]] Multiplicity add(Multiplicity, Multiplicity) const;
  [[nodiscard]] Multiplicity multiply(Multiplicity, Multiplicity) const;
  [[nodiscard]] Multiplicity remove(Multiplicity total, Multiplicity old) const;
  [[nodiscard]] Multiplicity replace(Multiplicity total, Multiplicity old, Multiplicity next) const;
 private:
  void validate(Multiplicity) const;
  std::uint64_t limit_;
};

struct IntegerPolicy {
  static constexpr std::string_view name = "checked-int64-payload-v1";
  [[nodiscard]] static IntegerPayload add(IntegerPayload, IntegerPayload);
  [[nodiscard]] static IntegerPayload multiply(IntegerPayload, IntegerPayload);
  [[nodiscard]] static IntegerPayload multiply(IntegerPayload, Multiplicity);
  [[nodiscard]] static IntegerPayload remove(IntegerPayload total, IntegerPayload old);
  // Checks the final exact total-old+next, even if an intermediate is outside int64.
  [[nodiscard]] static IntegerPayload replace(IntegerPayload total, IntegerPayload old, IntegerPayload next);
};

class DecimalPolicy {
 public:
  static constexpr std::string_view name = "checked-fixed-decimal-payload-v1";
  // Every operand and result must fit DECIMAL(p,s). No rounding or rescaling loss.
  explicit DecimalPolicy(DecimalSpec);
  [[nodiscard]] DecimalSpec specification() const noexcept { return specification_; }
  [[nodiscard]] DecimalPayload add(const DecimalPayload&, const DecimalPayload&) const;
  [[nodiscard]] DecimalPayload multiply(const DecimalPayload&, const DecimalPayload&) const;
  [[nodiscard]] DecimalPayload multiply(const DecimalPayload&, Multiplicity) const;
  [[nodiscard]] DecimalPayload remove(const DecimalPayload& total, const DecimalPayload& old) const;
  [[nodiscard]] DecimalPayload replace(const DecimalPayload& total, const DecimalPayload& old,
                                      const DecimalPayload& next) const;
 private:
  void validate(const DecimalPayload&) const;
  DecimalSpec specification_;
};

template<class Payload> struct Annotation {
  Multiplicity support;
  Payload payload;
  [[nodiscard]] bool present() const noexcept { return support.present(); }
  bool operator==(const Annotation&) const = default;
};
enum class MembershipChange { unchanged, appeared, disappeared };
template<class Payload> struct ValueChange {
  Annotation<Payload> before, after;
  [[nodiscard]] MembershipChange membership() const noexcept {
    if (before.present() == after.present()) return MembershipChange::unchanged;
    return after.present() ? MembershipChange::appeared : MembershipChange::disappeared;
  }
  [[nodiscard]] bool support_changed() const noexcept { return before.support != after.support; }
  [[nodiscard]] bool payload_changed() const { return before.payload != after.payload; }
};

// Pure preparation: callers publish the returned value only after every policy
// check succeeds. This supplies no runtime transaction or ancestor rollback.
template<class Payload, class Policy>
[[nodiscard]] Annotation<Payload> replace_contribution(const Annotation<Payload>& total,
    const Annotation<Payload>& old, const Annotation<Payload>& next, const MultiplicityPolicy& counts,
    const Policy& payloads) {
  for (const auto* value : {&total, &old, &next}) {
    if (!value->present() && value->payload != Payload{})
      throw Error("invalid_annotation", "an absent contribution must have a zero payload");
  }
  auto support = counts.replace(total.support, old.support, next.support);
  auto payload = payloads.replace(total.payload, old.payload, next.payload);
  if (!support.present() && payload != Payload{})
    throw Error("invalid_annotation", "removing the last row must leave a zero payload");
  return {support, payload};
}

enum class Domain { boolean_support, nonnegative_multiplicity, signed_integer, fixed_decimal,
                    general_semiring, approximate };
enum class Deletion { none, exact_retraction, replacement };
enum class Backend { arithmetic_policy, certified_set_tree, weighted_subtree_messages };
enum class Representation { fixed_word, bounded_decimal, unspecified };
struct Capabilities {
  bool exact = false;
  bool zero_sum_free = false;
  bool no_zero_divisors = false;
  bool additive_cancellation = false;
  bool exact_retraction = false;
  bool replacement = false;
  Representation representation = Representation::unspecified;
};
struct Request {
  Domain domain = Domain::boolean_support;
  Deletion deletion = Deletion::replacement;
  std::optional<DecimalSpec> decimal = std::nullopt;
};
enum class AdmissionStatus { admitted, unknown_domain, unsupported_algebra, invalid_decimal,
                             unexpected_decimal, unsupported_deletion, unsupported_backend };
struct Admission {
  AdmissionStatus status;
  Capabilities capabilities;
  std::string_view policy;
  [[nodiscard]] bool admitted() const noexcept { return status == AdmissionStatus::admitted; }
};
// Closed registry: caller-provided algebra traits cannot confer backend authority.
// Policy arithmetic admission carries no maintenance/enumeration theorem.
[[nodiscard]] Admission admit(const Request&, Backend) noexcept;
// Used by actual plan identity/options admission. W01 adds kernels, not a
// weighted runtime: only the existing exact-set profile can select that backend.
void require_set_backend_policy(std::string_view policy);
}  // namespace crown::annotations
