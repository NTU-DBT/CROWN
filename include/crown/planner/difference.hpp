#pragma once

#include "crown/annotations/policy.hpp"
#include "crown/planner/fallback.hpp"
#include <cstdint>
#include <memory>
#include <optional>
#include <span>
#include <string_view>
#include <utility>

namespace crown::planner::difference {
enum class Mode { set_except, bag_except_all };
struct Profile {
  Mode mode = Mode::set_except;
  std::string_view backend = "exact_difference_recompute_v1";
  std::string_view semantics = "exact_set_except";
  std::string_view input = "physical_full_row_set_events";
  std::string_view arithmetic = annotations::MultiplicityPolicy::name;
  std::string_view output = "owning_tuple_and_positive_multiplicity";
  std::string_view delta = "exact_endpoint_multiplicity_replacements_not_aggregate_payload";
  std::string_view state = "sources_plus_residual_keys_and_private_operand_images";
  std::string_view startup = "eager_two_operand_recomputation_and_materialization";
  std::string_view delay = "materialized_output_no_constant_delay_claim";
  std::string_view termination = "owned_scratch_and_result_cleanup";
  std::string_view height = "no_CROWN_GHD_or_P11_certificate";
  QueryClass left_class = QueryClass::free_connex, right_class = QueryClass::free_connex;
  fallback::Reason left_reason = fallback::Reason::explicit_reference_choice;
  fallback::Reason right_reason = fallback::Reason::explicit_reference_choice;
};
struct Estimates {
  fallback::Estimates left, right;
  // Committed logical rows and compressed residual keys, not peak bytes.
  // Multiplicity is a separate upper bound; never subtract operand bounds.
  std::optional<std::uint64_t> source_rows, output_rows_upper;
  std::optional<std::uint64_t> output_multiplicity_upper, state_rows_upper;
  bool overflow = false;
  bool advisory = true;
};
struct Limits {
  std::uint64_t work = 1'000'000; // Pair entry and positional head checks only.
  fallback::Limits left, right; // Separate cold metadata/recognition/lowering grants.
};

// Immutable explicit difference between two positive classical CQ operands.
// Each is admitted against the same original catalog/options. Cold admission
// copies/lowers both operands; execution selects only source_only() below.
class Plan {
 public:
  Plan(const Plan&) noexcept = default;
  Plan& operator=(const Plan&) noexcept = default;
  Plan(Plan&& other) noexcept : data_(other.data_) {}
  Plan& operator=(Plan&& other) noexcept { data_ = other.data_; return *this; }
  [[nodiscard]] const fallback::Plan& left() const & noexcept;
  const fallback::Plan& left() const && = delete;
  [[nodiscard]] const fallback::Plan& right() const & noexcept;
  const fallback::Plan& right() const && = delete;
  [[nodiscard]] const PhysicalPlan& source_only() const & noexcept;
  const PhysicalPlan& source_only() const && = delete;
  [[nodiscard]] const Profile& profile() const & noexcept;
  const Profile& profile() const && = delete;
  [[nodiscard]] std::uint64_t work() const noexcept; // Selected pair work, not operand work.
  [[nodiscard]] Estimates estimates(std::span<const std::uint64_t> tablecounts) const;
 private:
  struct Data;
  explicit Plan(std::shared_ptr<const Data> data) : data_(std::move(data)) {}
  friend Plan admit(const Catalog&, const Query&, const Query&, Mode, const PhysicalOptions&, const Limits&);
  std::shared_ptr<const Data> data_;
};

// Compare ordered output positions by ScalarType; aliases/variable IDs may
// differ. Canonical Decimal equality needs no precision/scale coercion: all
// residual tuples originate from the left operand and retain its valid layout.
// Set mode uses left presence AND right absence. Bag mode counts complete
// physical-row assignments before projection and computes max(left-right,0).
// Physical sources stay sets; this adds no weighted source-update or SQL-NULL
// semantics. Neither operand can contain recursion/negation/difference nodes.
// Errors use difference_admission or difference_work_limit; memory failures
// retain their native type. No original-query CROWN/GHD/P11 bound is implied.
[[nodiscard]] Plan admit(const Catalog&, const Query& left, const Query& right,
                         Mode = Mode::set_except, const PhysicalOptions& = {}, const Limits& = {});
} // namespace crown::planner::difference
