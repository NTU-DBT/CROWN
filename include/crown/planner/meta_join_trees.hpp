#pragma once
#include "crown/planner/meta.hpp"

namespace crown::planner::meta {
// Occurrence-labelled ordinary rooted join tree, not a CROWN height capability.
// parent has one entry per original atom; only root has parent[root] == root.
struct JoinTree { std::size_t root; std::vector<std::size_t> parent; };
struct EnumerationLimits {
  Limits metadata{}; // Independent admission/checking grants, reported below.
  std::uint64_t work = 10'000'000, fragments = 100'000, cells = 10'000'000;
  std::size_t output_trees = 10'000;
  bool all_roots = true; // False emits only canonical physical root0 per J.
};
struct EnumerationUsage {
  std::uint64_t work = 0, fragments = 0, cells = 0;
  std::size_t output_trees = 0;
};
enum class EnumerationStop {
  complete, invalid_metadata, metadata_limit, work_limit, fragment_limit,
  cell_limit, output_limit, invalid_expansion, noncanonical_metadata
};
struct Enumeration {
  EnumerationStop stop = EnumerationStop::invalid_metadata;
  Check metadata{Stop::invalid_decomposition,{},false};
  EnumerationUsage usage;
  std::vector<JoinTree> trees;
  bool all_roots = true; // Requested mode, including on early/resource stops.
};
// P3v2 Algorithms2/5, with the reviewed placeholder/Cartesian/reroot repairs.
// Input must additionally use Algorithm1's minor-first parenting: whenever a
// distinct minor has scope==a node's interface, that minor must be its parent.
// Literal Definition4.3 alone does not enforce this; reject, never claim full
// coverage for such a noncanonical edited graph.
// Every completed unrooted fragment is independently checked, then every
// physical root is emitted once in all_roots mode; otherwise only root0.
// Complete canonical mode covers all undirected J, not all their rootings.
// Limits return only a valid rooted prefix;
// a stop during subtree expansion can return no output. This cold batch is
// not resumable: raising grants means a new call. OOM/admission errors propagate.
// Work counts selected checkpoints; fragments/cells count cumulative admitted
// scratch/explicit vector entries, not allocator bytes, capacity or total CPU.
// The checker has its own existing limits. No paper delay/complexity claim.
[[nodiscard]] Enumeration enumerate(const Catalog&,const Query&,
                                    const Decomposition&,EnumerationLimits = {});
} // namespace crown::planner::meta
