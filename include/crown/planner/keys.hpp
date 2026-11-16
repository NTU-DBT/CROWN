#pragma once

#include "crown/planner/lower.hpp"
#include "crown/planner/oracle.hpp"

namespace crown::planner::keys {
enum class Reason { specialized, normalized_sql, constant_route, no_match };
// All IDs name the original query/catalog. Constraint indices address the
// witness table's FK and removed table's enforced UNIQUE respectively.
struct Elimination {
  OccurrenceId removed, witness;
  std::size_t foreign_key, unique_key;
};
struct Limits {
  std::uint64_t work = 1'000'000; // One shared selected guard/mapping grant.
  SearchLimits search; // Existing independent producer/replay search limits.
  std::optional<PhysicalLimits> lowering; // Existing host lowering/identity ceilings.
};
struct Usage {
  std::uint64_t work = 0, lowering_work = 0;
  SearchStatistics search;
};

// Cold, opt-in direct-CQ set specialization. The original comparison plan and
// complete original source catalog survive; only redundant FK parent occurrences
// leave the executable query. Existing PhysicalRuntime retains source state and
// enforces every constraint, including updates to referenced/unused tables.
// New wrapper/vector metadata is ordinary compiler-owned storage; retained plan
// and layout handles keep their existing ownership. Runtime admission freezes
// the chosen plan into its receiving query account. Copies/moves retain source
// validity; last-owner release can destroy the retained compiler/proof graph.
class Plan {
 public:
  Plan(const Plan&) noexcept = default;
  Plan& operator=(const Plan&) noexcept = default;
  Plan(Plan&& other) noexcept : data_(other.data_) {}
  Plan& operator=(Plan&& other) noexcept { data_ = other.data_; return *this; }
  const PhysicalPlan& general() const & noexcept;
  const PhysicalPlan& general() const && = delete;
  const PhysicalPlan& execution() const & noexcept;
  const PhysicalPlan& execution() const && = delete;
  Reason reason() const noexcept;
  bool specialized() const noexcept;
  std::span<const Elimination> eliminations() const & noexcept;
  std::span<const Elimination> eliminations() const && = delete;
  std::span<const OccurrenceId> occurrences() const & noexcept; // New -> original.
  std::span<const OccurrenceId> occurrences() const && = delete;
  std::span<const VariableId> variables() const & noexcept; // New -> original.
  std::span<const VariableId> variables() const && = delete;
  const Usage& usage() const & noexcept;
  const Usage& usage() const && = delete;
  // This certificate belongs only to execution().query(), not general().query().
  const std::optional<HeightCertificate>& reduced_certificate() const & noexcept;
  const std::optional<HeightCertificate>& reduced_certificate() const && = delete;
  static constexpr unsigned format_version = 1;
 private:
  struct Data;
  explicit Plan(std::shared_ptr<const Data> data) : data_(std::move(data)) {}
  friend Plan specialize(const PhysicalPlan&, const Limits&);
  std::shared_ptr<const Data> data_;
};

// A rule needs a distinct live witness, an enforced FK and enforced target key.
// Every key component has the same non-wildcard typed term in both occurrences.
// A non-key target field is ignored or a once-used private existential variable.
// Non-key constants, repeated variables and externally used payloads block it.
// Rules run sequentially; a cycle cannot erase its final live witness.
// Normalized SQL and constant operators remain unchanged. No match performs no
// new tree search. A resource/search/lowering refusal returns no partial Plan;
// the caller retains its general plan. No catch/retry or runtime owner is added.
// Guard work excludes scalar widths, metadata copies, allocation and existing
// search/replay/lowering costs, which retain their separate limits and costs.
[[nodiscard]] Plan specialize(const PhysicalPlan& general, const Limits& = {});
} // namespace crown::planner::keys
