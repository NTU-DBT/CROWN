#pragma once
#include "crown/ir/physical.hpp"
#include "allocation_counter.hpp"
#include <array>
#include <string_view>

namespace allocation_probe {
inline constexpr std::array<std::string_view,2> operation_modes={"compile_only","reference_storage_initialization"};
inline constexpr std::array<std::string_view,3> assumptions={"single_writer","nonnull_exact_binary_values","ordered_standard_containers"};
inline constexpr std::array<std::string_view,2> output_accounting={"one_action_per_emitted_tuple","retained_snapshots_and_buffers_accounted_separately"};
template<std::size_t N> void vector_values(const std::vector<std::string>& actual,const std::array<std::string_view,N>& expected) {
  check(actual.size()==N,"profile vector cardinality changed");
  for(std::size_t i=0;i<N;++i)check(actual[i]==expected[i],"profile vector bytes changed");
}
template<class Profile> void scalar_values(const Profile& p) {
  check(p.semantics=="exact_set" && p.query_class=="free_connex" && p.update_contract=="physical_full_row_set_events" &&
        p.arithmetic=="exact-nonnull-v1" && p.storage_backend=="reference_ordered_v1" && p.execution_status=="lowered_not_started" &&
        p.height_status=="valid_upper_bound" && p.state_bound=="runtime_not_implemented" && p.maintenance_bound=="runtime_not_implemented" &&
        p.cursor_startup_bound=="runtime_not_implemented" && p.cursor_delay_bound=="runtime_not_implemented" &&
        p.cursor_termination_bound=="runtime_not_implemented","profile scalar descriptor bytes changed");
}
inline void verify(const crown::GuaranteeProfile& p) {
  scalar_values(p);vector_values(p.operation_modes,operation_modes);vector_values(p.assumptions,assumptions);vector_values(p.output_accounting,output_accounting);
}
inline void verify(const crown::io::CachePolicy& p) {
  check(p.arithmetic=="exact-nonnull-v1" && p.planner=="crown-tree-v1" && p.optimization=="structural-height-v1" && p.cost_model=="no-cost-v1","cache policy descriptor bytes changed");
}
inline void verify(const crown::PhysicalOptions& p) {
  verify(p.policy);check(p.limits.work_limit==1'000'000 && p.limits.identity.work_limit==1'000'000,"physical option defaults changed");
}
// Local diagnostic controls only; no PhysicalPlan::Data or proof/evidence factory.
struct OptionsProfile {crown::PhysicalOptions options;crown::GuaranteeProfile guarantee;~OptionsProfile()=default;};
inline void verify(const OptionsProfile& p){verify(p.options);verify(p.guarantee);}
struct OperationModes {std::vector<std::string> values={"compile_only","reference_storage_initialization"};};
struct Assumptions {std::vector<std::string> values={"single_writer","nonnull_exact_binary_values","ordered_standard_containers"};};
struct OutputAccounting {std::vector<std::string> values={"one_action_per_emitted_tuple","retained_snapshots_and_buffers_accounted_separately"};};
inline void verify(const OperationModes& p){vector_values(p.values,operation_modes);}
inline void verify(const Assumptions& p){vector_values(p.values,assumptions);}
inline void verify(const OutputAccounting& p){vector_values(p.values,output_accounting);}
struct ScalarStrings {
  std::string semantics="exact_set";
  std::string query_class="free_connex";
  std::string update_contract="physical_full_row_set_events";
  std::string arithmetic="exact-nonnull-v1";
  std::string storage_backend="reference_ordered_v1";
  std::string execution_status="lowered_not_started";
  std::string height_status="valid_upper_bound";
  std::string state_bound="runtime_not_implemented";
  std::string maintenance_bound="runtime_not_implemented";
  std::string cursor_startup_bound="runtime_not_implemented";
  std::string cursor_delay_bound="runtime_not_implemented";
  std::string cursor_termination_bound="runtime_not_implemented";
};
inline void verify(const ScalarStrings& p){scalar_values(p);}
} // namespace allocation_probe
