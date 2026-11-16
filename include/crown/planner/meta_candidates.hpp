#pragma once

#include "crown/planner/candidates.hpp"
#include "crown/planner/meta_join_trees.hpp"
#include <cstddef>
#include <cstdint>
#include <optional>
#include <string_view>

namespace crown::planner::meta {
struct MetaMappingLimits {
  std::uint64_t work = 10'000'000, fragments = 100'000, cells = 10'000'000;
  std::size_t output_trees = 10'000, depth = 256;
};
struct MetaMappingUsage {
  std::uint64_t work = 0, fragments = 0, cells = 0;
  std::size_t output_trees = 0, peak_depth = 0;
};
enum class MappingStop {
  not_started, complete, invalid_join_tree, work_limit, fragment_limit,
  cell_limit, output_limit, depth_limit
};
struct MetaCandidateLimits {
  Limits construction{};
  EnumerationLimits enumeration{.all_roots=false};
  MetaMappingLimits mapping{};
  planner::CandidateLimits admission{};
};
// Preparation diagnostics, not a height certificate or a checked capability.
// Exhaustion of returned ordinary input fibers is separate from exhaustion of
// all ordinary trees and from actual P02/height/key admission below.
struct MetaCandidateReport {
  Stop construction_stop = Stop::invalid_decomposition;
  Usage construction_usage;
  EnumerationStop enumeration_stop = EnumerationStop::invalid_metadata;
  Check enumeration_metadata{Stop::invalid_decomposition, {}, false};
  EnumerationUsage enumeration_usage;
  MappingStop mapping_stop = MappingStop::not_started;
  MetaMappingUsage mapping_usage;
  bool ordinary_exhausted = false, mapped_input_fibers_exhausted = false;
  // Canonical mode exhausts undirected J with one root0 record each. Fibers
  // still cover every eligible CROWN rooting. This avoids n discarded copies.
  bool all_ordinary_roots_materialized = false;
  std::size_t rooted_ordinary_trees = 0, undirected_trees = 0;
  std::uint64_t root_sets = 0, height_pruned_root_sets = 0, generalized_partitions = 0;
  static constexpr std::string_view scope =
      "canonical inverse contractions; normalized CROWN trees at the supplied original minimum";
  static constexpr std::string_view cost_scope =
      "no unary-generalized shape coverage or globally minimum maintenance-cost claim";
  static constexpr bool heuristic_used = false;
};
struct PreparedMetaCandidates {
  MetaCandidateReport report;
  std::optional<CandidateProvider> provider;
  // Fresh diagnostic: complete preparation alone never means P02 admission.
  // Moving the provider out makes this result unable to attest its progress.
  // As a diagnostic, this assumes its returned report/provider were not replaced.
  bool normalized_minimum_family_exhausted() const noexcept {
    return report.ordinary_exhausted && report.mapped_input_fibers_exhausted &&
        provider && provider->progress().family_exhausted;
  }
};

// P3v2 supplies ordinary trees; local inverse contractions supply normalized
// generalized prefixes. Never convert paper minor bags directly into CROWN
// nodes. Generalized scopes are intersections of first-native root scopes;
// final P02 alone admits head/Guard/Connect/Above and the supplied proof height.
// No exact-witness/residual seed or unconstrained normal-form fallback is added.
//
// Exact preparation when all grants complete; otherwise return only completed
// mapped drafts, with separate stop/exhaustion diagnostics. Preparation is a
// cold, nonresumable batch: a larger preparation grant means a fresh call.
// Advance the returned finite provider under its own existing grants. Its
// exhaustion covers that batch only; use the method above for combined scope.
//
// Work counts selected scalar/set/graph checkpoints; fragments and explicit
// vector/scope/frame cells are cumulative construction charges. Depth is checked
// before recursive pushes. Capacities, allocator bytes, strings, admission,
// container relocation and destruction are separate costs, not CPU/byte bounds.
// Query admission and OOM retain the existing APIs' propagating errors.
[[nodiscard]] PreparedMetaCandidates prepare_meta_candidates(
    VerifiedOptimum, MetaCandidateLimits = {});
} // namespace crown::planner::meta
