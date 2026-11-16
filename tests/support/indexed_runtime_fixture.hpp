#pragma once
#include "crown/planner/lower.hpp"

// Backend selector only. Derived fixtures retain their existing independent
// row/assignment joins, expected results, invalid inputs and failure assertions.
namespace crown::s04_runtime {
// Limits are component counts and one aggregate operation grant, not query bytes.
inline PhysicalOptions options() {
  PhysicalOptions value;
  value.indexed_storage=storage::IndexedBackendSpec{
      {4096,64,32768,65536,131072,524288,8192,32768,8192},
      {1'000'000'000,1'000'000'000,1'000'000'000,1'000'000'000,1'000'000'000}};
  return value;
}
inline PhysicalPlan lower_tree(const Catalog& catalog,const Query& query,const FreeConnexTree& tree) {
  return planner::lower_tree(catalog,query,tree,options());
}
inline PhysicalPlan lower_normalized(const frontend::NormalizedSql& program,const FreeConnexTree& tree) {
  return planner::lower_normalized(program,tree,options());
}
}  // namespace crown::s04_runtime
