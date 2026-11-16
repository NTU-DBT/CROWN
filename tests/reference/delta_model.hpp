#pragma once

#include "crown/ir/model.hpp"
#include "crown/ir/tree.hpp"
#include <map>

namespace crown::reference::delta {
// Test-only, materializing executable specification. It never reads the
// maintained runtime, its journals, live cache or result/delta cursors.
using FixedAssignment = std::map<VariableId,Value>;
struct Factor {
  NodeId node{0};
  std::optional<std::size_t> parent;
  std::vector<VariableId> scope;  // Sorted visible variable IDs.
  Relation rows;
};
struct Snapshot {
  std::vector<VariableId> head;  // Original order, including repeated fields.
  std::vector<Factor> factors;  // Parent before child; first factor is root.
  bool constant_answer=false;   // Used only for a constant route (no factors).
};

// Native rows have complete ascending-variable-ID node scopes, after local
// adapters/derivation counting. Generalized nodes have no external rows.
// Full subtree joins independently reconstruct visible E factors.
[[nodiscard]] Snapshot recompute(const Catalog& catalog,const Query& query,
    const FreeConnexTree& tree,const std::vector<Relation>& native_rows);
// E-only fixed bindings (visible head variables). This is not the D02
// hidden-binding cursor; subtree witnesses have already been projected here.
[[nodiscard]] std::vector<Row> enumerate(const Snapshot& snapshot,const FixedAssignment& fixed = {});
// Requires the maintained E downward-totality property. Uses top-down
// semijoins, not a projection of materialized global answers.
[[nodiscard]] std::vector<Relation> bootstrap_live(const Snapshot& snapshot);

struct Fragment {
  std::size_t factor=0;
  Row witness;
  std::vector<Row> candidates,accepted,rejected;
};
struct Metrics {
  std::uint64_t changed_keys=0,live_witnesses=0,dead_witnesses=0;
  std::uint64_t candidates=0,accepted=0,rejected=0,earlier_probes=0;
};
struct Transition {
  SetOperation operation;
  std::vector<Relation> changed,before_live,after_live;
  std::vector<Fragment> fragments;
  std::vector<Row> rows;  // Append only: no deduplication across fragments.
  Metrics metrics;
};
// One fully drained same-sign logical occurrence step. Select changed E
// memberships that are live on after (insert) or before (erase), enumerate
// completions in that context, and accept only their first changed factor.
// Rejects mixed factor-membership polarity or incompatible snapshots. It does
// not validate a physical input history or implement a mixed-batch contract.
[[nodiscard]] Transition partition(const Snapshot& before,const Snapshot& after,SetOperation operation);
}  // namespace crown::reference::delta
