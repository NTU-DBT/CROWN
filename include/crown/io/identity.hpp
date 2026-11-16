#pragma once

#include "crown/frontend/normalize.hpp"
#include "crown/io/document.hpp"

namespace crown::io {
struct IdentityLimits { std::optional<std::uint64_t> work_limit = 1000000; };
struct CachePolicy {
  std::string arithmetic = "exact-nonnull-v1";
  std::string planner = "crown-tree-v1";
  std::string optimization = "structural-height-v1";
  std::string cost_model = "no-cost-v1";
};
// Ordinary editable identity DTO. Digests/flags are not executable, proof or
// native source-admission authority.
struct QueryIdentity {
  Json canonical;
  std::string semantic_sha256;
  std::string output_contract_sha256;
  std::string cost_inputs_sha256;
  std::string plan_cache_sha256;
  // Canonical position -> original ID. A cache consumer must translate IDs.
  std::vector<std::size_t> occurrence_order;
  std::vector<std::size_t> variable_order;
  std::uint64_t work;
};
// Complete colored-occurrence labeling within an operational work budget.
// Alpha-renaming, conjunction/occurrence order and variable IDs are erased;
// output positions, all atoms, types, constants and source schemas remain.
// On exhaustion throw resource_limit; never return a partial/fallback digest.
[[nodiscard]] QueryIdentity query_identity(const Catalog& catalog, const Query& query, const CachePolicy& policy = {}, IdentityLimits limits = {});
// Requires an owned producer/reader-validated program, as do its adapters.
[[nodiscard]] QueryIdentity query_identity(const frontend::NormalizedSql& query, const CachePolicy& policy = {}, IdentityLimits limits = {});
[[nodiscard]] Json write_identity(const QueryIdentity& identity);
}  // namespace crown::io
