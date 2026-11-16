#pragma once

#include "crown/planner/lower.hpp"
#include "crown/planner/recognize.hpp"
#include <cstdint>
#include <memory>
#include <optional>
#include <span>
#include <string_view>
#include <utility>

namespace crown::planner::fallback {
enum class Backend { exact_recompute_v1 };
enum class Reason { cyclic_body, non_free_connex_head, explicit_reference_choice, contradiction };
struct Profile {
  std::string_view backend = "exact_recompute_v1";
  std::string_view semantics = "exact_set";
  std::string_view update = "physical_full_row_set_events_with_exact_endpoint_deltas";
  std::string_view state = "sources_plus_materialized_distinct_answers_and_private_images";
  std::string_view startup = "eager_exact_recomputation_and_materialization";
  std::string_view delay = "materialized_output_no_constant_delay_claim";
  std::string_view termination = "owned_scratch_and_result_cleanup";
  std::string_view height = "no_CROWN_or_GHD_certificate";
  QueryClass query_class = QueryClass::free_connex;
  Reason reason = Reason::explicit_reference_choice;
};
struct Estimates {
  // Logical committed source/answer rows, not peak bytes or image/journal space.
  std::optional<std::uint64_t> source_rows, assignments_upper, output_rows_upper, state_rows_upper;
  bool overflow = false;
  bool advisory = true;
};
struct Limits {
  std::uint64_t work = 1'000'000;
  RecognitionLimits recognition;
  PhysicalLimits lowering;
};

// Cold explicit reference-backend choice for any validated non-null set CQ.
// The constant source coordinator retains every source/constraint/backend;
// its identity and tree are not an original-query certificate or guarantee.
class Plan {
 public:
  Plan(const Plan&) noexcept = default;
  Plan& operator=(const Plan&) noexcept = default;
  Plan(Plan&& other) noexcept : data_(other.data_) {}
  Plan& operator=(Plan&& other) noexcept { data_ = other.data_; return *this; }
  [[nodiscard]] const Catalog& originalcatalog() const & noexcept;
  const Catalog& originalcatalog() const && = delete;
  [[nodiscard]] const Query& query() const & noexcept;
  const Query& query() const && = delete;
  [[nodiscard]] const PhysicalPlan& source_only() const & noexcept;
  const PhysicalPlan& source_only() const && = delete;
  [[nodiscard]] const StructuralAnalysis& structure() const & noexcept;
  const StructuralAnalysis& structure() const && = delete;
  [[nodiscard]] const Profile& profile() const & noexcept;
  const Profile& profile() const && = delete;
  [[nodiscard]] std::uint64_t work() const noexcept; // Selected metadata admission only.
  // Explicit per-physical-table counts. Alias factors repeat per occurrence;
  // source rows count each catalog table once, including unused sources.
  [[nodiscard]] Estimates estimates(std::span<const std::uint64_t> tablecounts) const;
 private:
  struct Data;
  explicit Plan(std::shared_ptr<const Data> data) : data_(std::move(data)) {}
  friend Plan admit(const Catalog&, const Query&, const PhysicalOptions&, const Limits&);
  std::shared_ptr<const Data> data_;
};

// Preserves every original atom/constant/repeated or ignored term and ordered
// head. All three structural classes are admitted explicitly; recognition
// exhaustion is never a class. Original metadata uses ordinary compiler
// ownership; native execution must freeze it into its original query account.
// Selected cold visits/string bytes, GYO and lowering have separate limits;
// validation, allocation and copy/identity costs retain their real costs.
// Invalid inputs use fallback_admission; exhausted selected admission or
// recognition/lowering work uses fallback_work_limit. Other typed admission
// errors use fallback_admission; allocation failures retain their own type.
[[nodiscard]] Plan admit(const Catalog&, const Query&, const PhysicalOptions& = {}, const Limits& = {});
} // namespace crown::planner::fallback
