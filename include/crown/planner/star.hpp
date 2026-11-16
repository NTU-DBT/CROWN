#pragma once

#include "crown/planner/lower.hpp"
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <span>
#include <utility>

namespace crown::planner::star {
struct Limits {
  std::uint64_t work = 1'000'000; // One selected admission/mapping balance.
  std::optional<PhysicalLimits> lowering; // Existing independent cold limits.
};
struct Usage {
  std::uint64_t work = 0, lowering_work = 0;
};

// Cold opt-in metadata for the exact set family in P2 v1 Definition 4.5,
// PDF p14: one all-variable center and distinct unary satellites. The caller
// chooses the center explicitly; admission neither searches for a new tree nor
// converts a checked original upper bound into minimum-height authority.
// This wrapper and its vectors use ordinary compiler storage. Native runtime
// admission must copy retained metadata into its receiving query account.
class Plan {
 public:
  Plan(const Plan&) noexcept = default;
  Plan& operator=(const Plan&) noexcept = default;
  Plan(Plan&& other) noexcept : data_(other.data_) {}
  Plan& operator=(Plan&& other) noexcept { data_ = other.data_; return *this; }
  const PhysicalPlan& general() const & noexcept;
  const PhysicalPlan& general() const && = delete;
  // Private source coordinator: the complete original catalog/options with an
  // empty constant-true query and no occurrence routes. It is not the star
  // answer program or an original-query proof. PhysicalRuntime still stores
  // every physical source and enforces its complete after-state constraints.
  const PhysicalPlan& source_only() const & noexcept;
  const PhysicalPlan& source_only() const && = delete;
  OccurrenceId center() const noexcept; // Original query occurrence ID.
  TableId center_table() const noexcept; // Original physical catalog ID.
  std::size_t dimension() const noexcept; // Center arity d, not structural dimension.
  std::size_t distinct_head() const noexcept; // Distinct head variables j.
  // Center-coordinate order; absent satellites are conceptually always true.
  std::span<const std::optional<TableId>> satellite_tables() const & noexcept;
  std::span<const std::optional<TableId>> satellite_tables() const && = delete;
  // Original ordered/repeated output positions mapped to center coordinates.
  std::span<const std::size_t> head_coordinates() const & noexcept;
  std::span<const std::size_t> head_coordinates() const && = delete;
  const Usage& usage() const & noexcept;
  const Usage& usage() const && = delete;
 private:
  struct Data;
  explicit Plan(std::shared_ptr<const Data> data) : data_(std::move(data)) {}
  friend Plan admit(const PhysicalPlan&, OccurrenceId, const Limits&);
  std::shared_ptr<const Data> data_;
};

// Requires a genuine direct-CQ tree plan, non-null exact set semantics and
// distinct physical tables. Every center term is a different variable; every
// other atom is a unary variable on a different center coordinate. Every hidden
// coordinate has a satellite. Head order/repetitions survive; j counts distinct
// variables. No constants, ignored fields, self-joins, nullable/SQL adapters or
// constant operators are admitted, and no arbitrary 64-coordinate cap is added.
//
// Unsupported shapes throw star_admission; exhausted selected work throws
// star_work_limit. Lowering retains its own failure categories and allowance.
// All fallible construction is private; the supplied general plan survives a
// refusal. Copies/moves retain valid owners; final release can destroy compiler
// graphs. Work excludes copies, allocation, scalar widths, ordered-set costs and
// the existing source-only lowering/identity/validation costs.
//
// Admission alone supplies no P2 delay/update theorem. In particular d is center
// arity: full heads with fewer than d satellites need separate structural-
// dimension qualification. P2 v1 Theorem 1.4 and the actual runtime profile must
// be examined independently before claiming a bound.
[[nodiscard]] Plan admit(const PhysicalPlan& general, OccurrenceId center, const Limits& = {});
} // namespace crown::planner::star
