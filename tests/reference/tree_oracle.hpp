#pragma once

#include "crown/planner/oracle.hpp"

namespace crown::reference {
// Deliberately literal §5.4 baseline: labelled topologies and the full union
// of native power sets. No partition-search or proof-construction helpers.
[[nodiscard]] planner::OracleResult exhaustive_minimum_tree(const Catalog& catalog, const Query& query,
                                                           const planner::SearchLimits& limits = {});
}  // namespace crown::reference
