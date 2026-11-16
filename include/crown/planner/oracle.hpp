#pragma once

#include "crown/ir/tree.hpp"
#include <chrono>

namespace crown::planner {
// Compatibility ceilings apply independently to producer and replay. literal_scope_limit
// affects the literal oracle, not partition search. See docs/planner_continuations.md,
// resource accounting.
struct SearchLimits {
  // P06 continuation_v1 counts fine cursor/control transitions as well as input
  // cells. Explicit ceilings remain exact; the default accommodates the finer
  // accounting of the mandatory residual cases.
  std::optional<std::uint64_t> work_limit = 10'000'000;
  std::optional<std::size_t> recursion_limit = 256;
  std::optional<std::size_t> literal_scope_limit = 4096;
  std::optional<std::chrono::milliseconds> time_limit;
};
// Counters identify executed routes and attempted work; proof authority comes from complete
// independent replay. See docs/planner_continuations.md, resource accounting.
struct SearchStatistics {
  std::uint64_t work = 0;
  std::uint64_t states = 0;
  std::uint64_t partitions = 0;
  std::uint64_t candidates = 0;
  std::uint64_t cache_hits = 0;
  std::uint64_t certificate_work = 0;
  std::uint64_t hierarchy_tests = 0, hierarchy_hits = 0;
  std::uint64_t singleton_hits = 0, empty_body_hits = 0;
  std::uint64_t component_splits = 0, symmetry_skips = 0, bound_prunes = 0;
};
// Claim a contextual lower bound, with null for infinity; it becomes usable only after
// independent proof. See docs/planner_proofs.md, lower-bound evidence.
struct LowerBoundEntry {
  std::vector<std::size_t> occurrences;
  bool generalized_allowed;
  bool connex_reachable;
  // null is infinity: the state has no admissible completion.
  std::optional<std::size_t> bound;
};
// This aggregate is an unverified claim: pair a matching upper with complete lower replay
// before granting optimum or infeasibility authority. See docs/planner_continuations.md,
// authority.
struct HeightCertificate {
  std::string algorithm = "crown_partition_exact_v1";
  std::optional<std::size_t> minimum_height;
  std::optional<FreeConnexTree> tree;
  std::vector<LowerBoundEntry> lower_bounds;
};
// Strict results separate a checked minimum, a checked empty tree family and an incomplete
// resource stop. See docs/planner_continuations.md, authority.
enum class OracleStatus { proven_minimum, unsupported, resource_limit };
// Own strict adapter evidence; a resource stop returns no partial minimum/tree/certificate.
// See docs/planner_continuations.md, authority.
struct OracleResult {
  OracleStatus status = OracleStatus::resource_limit;
  std::optional<std::size_t> minimum_height;
  std::optional<FreeConnexTree> tree;
  std::vector<LowerBoundEntry> lower_bounds;
  SearchStatistics statistics;
  std::string reason;
  std::string algorithm;
  bool certificate_verified = false;
  SearchLimits limits;
};
// Report completed checking separately from replay resource exhaustion; the report is a
// summary, not an owning optimum handle. See docs/planner_continuations.md, authority.
struct CertificateReport {
  bool valid = false;
  bool resource_limit = false;
  std::uint64_t work = 0;
  std::string message;
};

// Complete normal-form search with memoization. A completed public result has
// its upper witness and finite lower-bound proof checked independently.
// Block in strict policy until independent lower replay completes or resources stop;
// incomplete results expose no incumbent certificate. See docs/planner_continuations.md,
// authority.
[[nodiscard]] OracleResult minimum_tree(const Catalog& catalog, const Query& query, const SearchLimits& limits = {});
// Replay claims against the owned binding with independent scopes and enumeration;
// distinguish invalid evidence from exhausted resources. See docs/planner_proofs.md,
// lower-bound evidence.
[[nodiscard]] CertificateReport verify_height_certificate(const Catalog& catalog, const Query& query,
                                                          const HeightCertificate& certificate,
                                                          const SearchLimits& limits = {});
}  // namespace crown::planner
