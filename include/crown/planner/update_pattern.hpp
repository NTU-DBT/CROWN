#pragma once

// Conditional sufficient cases on genuine P02/P07 candidates. These results
// do not assert that a runtime trace enforces the requested assumptions.
// Usage and transfer argument: docs/update_patterns.md.
#include "crown/ir/update_pattern.hpp"
#include "crown/planner/ranking.hpp"
#include <string_view>

namespace crown::planner::patterns {
using ::crown::patterns::Declaration;
using ::crown::patterns::TableRule;

// Unknown is an unproved case, never a hardness or impossibility result.
enum class SufficientCase { unknown, constant_result, insertion_only, height_one, height_two_edges, subtree_edges };
// Event mapping bounds zero/one row per occurrence; monotone_source additionally
// checks every participating physical base is insertion-only. typed_cq passes
// the stronger injective/self-join-free lifetime gate for higher mixed trees.
// Other named source statuses explain why that stronger gate did not pass.
enum class Transfer { checked_typed_cq, normalized_source, nullable_source, self_join, ignored_column,
  not_checked, not_required, checked_event_mapping, checked_monotone_source };
// Child insertion-only and joint FIFO bases describe native leaves. A subtree
// basis requires insertion-only at every native descendant, including the child.
enum class EdgeBasis { unproved, child_insertion_only, joint_fifo_scope, subtree_insertion_only };
// Stable diagnostic names; unknown values grant no additional authority.
[[nodiscard]] std::string_view name(SufficientCase) noexcept;
[[nodiscard]] std::string_view name(Transfer) noexcept;
[[nodiscard]] std::string_view name(EdgeBasis) noexcept;
struct EdgeCondition {
  NodeId parent, child;
  TableId parent_table, child_table;
  EdgeBasis basis = EdgeBasis::unproved;
  std::uint64_t fifo_scope = 0;
};
template<class T> using Vector = std::vector<T, resource::OwnerAllocator<T>>;

// Plain diagnostic report, not proof authority. Handles retain the exact
// checked CQ/tree and source-bound rules without cloning those funded owners.
// Edge storage is newly funded by the receiving account. A report never asserts
// live compliance, total session CPU/delay, exhaustive families or optimal cost.
struct Analysis {
  MinimumHeightCandidate candidate;
  Declaration declaration;
  SufficientCase sufficient = SufficientCase::unknown;
  Transfer transfer = Transfer::not_checked;
  std::size_t height = 0;
  Vector<EdgeCondition> edges;
  Analysis(const resource::MemoryAccount& account, const MinimumHeightCandidate& candidate,
      const Declaration& declaration);
};
struct Attempt {
  ranking::Stop stop = ranking::Stop::internal_error;
  std::optional<Analysis> analysis;
  ranking::Usage usage;
};
// Full typed binding is checked before the private visitor. A failed grant
// returns no partial analysis; only this public noexcept boundary translates errors.
[[nodiscard]] Attempt analyse(const resource::MemoryAccount& account, const CompiledProgram& source,
    const MinimumHeightCandidate& candidate, const Declaration& declaration,
    const ranking::Limits& limits = {}) noexcept;
} // namespace crown::planner::patterns
