#pragma once
#include "crown/planner/oracle.hpp"
#ifdef CROWN_PLANNER_TESTING
namespace crown::planner::testing {
OracleResult minimum_tree_baseline(const Catalog&, const Query&, const SearchLimits& = {});
}
#endif
