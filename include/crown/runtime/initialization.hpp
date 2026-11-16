#pragma once

#include "crown/ir/model.hpp"
#include "crown/api/error.hpp"
#include "crown/storage/accounted_layout.hpp"
#include <limits>

namespace crown::runtime {
enum class BuildMethod { direct, insertion_replay };
struct BuildOptions {
  BuildMethod method=BuildMethod::direct;
  std::optional<std::uint64_t> work_limit=1000000;
};
struct BuildMetrics {
  std::uint64_t work=0, source_rows=0, constraint_rows=0;
  std::uint64_t adapter_visits=0, adapter_rejections=0, derivation_changes=0;
  std::uint64_t native_keys=0, generalized_candidates=0, child_probes=0;
  std::uint64_t survivors=0, parent_keys=0, visible_keys=0;
  std::uint64_t storage_records=0, index_memberships=0;
  std::uint64_t replay_inputs=0, replay_events=0, replay_work=0;
  std::uint64_t live_bootstrap_work=0, live_rows=0, live_parent_rows=0, live_child_rows=0;
};
namespace detail {
// Shared cumulative build accounting; distinct from ordinary per-event caps.
inline void build_charge(BuildMetrics& metrics,const BuildOptions& options,std::uint64_t amount=1) {
  const auto used=metrics.work;
  if (amount>std::numeric_limits<std::uint64_t>::max()-used ||
      (options.work_limit && (used>*options.work_limit || amount>*options.work_limit-used)))
    throw Error("resource_limit","runtime initialization work limit exceeded");
  metrics.work+=amount;
}
// Use a category distinct from metrics.work. Its overflow can occur after
// cumulative charging; spent work is not refunded by that later failure.
inline void build_metric(BuildMetrics& metrics,const BuildOptions& options,std::uint64_t& counter,std::uint64_t amount=1) {
  build_charge(metrics,options,amount);
  if (amount>std::numeric_limits<std::uint64_t>::max()-counter)
    throw Error("resource_limit","runtime initialization counter exhausted");
  counter+=amount;
}
struct NativeSeed { NodeId node; storage::AccountedTuple tuple; };
}  // namespace detail
}  // namespace crown::runtime
