#pragma once

#include "crown/planner/recognize.hpp"
#include <cstddef>
#include <cstdint>
#include <optional>
#include <vector>

namespace crown::planner::meta {
// P3 arXiv:2603.15465v2, Definition 4.3 and Algorithm 1 (PDF pp.10–12).
// This is planning metadata, not a CROWN tree or a checked-height capability.
// Physical identities are occurrence indices, including equal scopes/aliases.
struct Node {
  std::optional<std::size_t> occurrence; // lambda: one original edge, or minor.
  Scope scope;                          // chi: variables in this node.
  Scope interface;                      // kappa: variables shared outside it.
  std::optional<std::size_t> parent;
};
struct Decomposition {
  std::vector<Node> nodes;
  std::size_t root = 0;
};
struct Limits {
  std::uint64_t work = 1'000'000;
  std::size_t nodes = 1024;
  std::uint64_t scope_cells = 1'000'000;
};
struct Usage {
  std::uint64_t work = 0, scope_cells = 0;
  std::size_t nodes = 0;
};
enum class Stop {
  complete, empty_body, nullary_occurrence, cyclic, invalid_decomposition,
  work_limit, node_limit, cell_limit
};
struct Build {
  Stop stop;
  Usage usage;
  std::optional<Decomposition> decomposition;
};
struct Check { Stop stop; Usage usage; bool valid; };

// Validation of Catalog/Query is existing allocating admission outside these
// counters. Construction/checking charge selected metadata steps and cumulative
// explicit scope-cell copies, not allocator bytes or total CPU. OOM propagates.
// No partial decomposition is published on a stop. Empty/nullary bodies have
// explicit statuses; disconnected nonempty scopes use an empty-interface root.
// Scope-equal occurrences remain distinct; special edges have separate identity.
// Checking additionally requires every minor scope to fit one original scope,
// an Algorithm 1 invariant which, with coverage/RIP, excludes cyclic bodies.
[[nodiscard]] Build construct(const Catalog&, const Query&, Limits = {});
[[nodiscard]] Check check(const Catalog&, const Query&, const Decomposition&, Limits = {});
} // namespace crown::planner::meta
