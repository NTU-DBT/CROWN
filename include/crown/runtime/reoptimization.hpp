#pragma once
#include "crown/runtime/initialization.hpp"
#include "crown/ir/program.hpp"
#include "crown/recovery/plan_descriptor.hpp"
#include <array>
#include <cstdint>
#include <optional>

namespace crown::runtime::reoptimization {
namespace detail {class Budget;class State;struct Access;}
// A caller prediction in explicit time units, not a C02 height/depth/slot
// score, measured fact, structural certificate or automatic C03 enablement.
struct Forecast {
  std::uint64_t current_ns_per_input=0,target_ns_per_input=0,horizon_inputs=0;
};
struct Policy {
  std::uint64_t minimum_epoch_gap=1000;
  std::uint32_t minimum_saving_basis_points=100; // 100/10000 = 1%.
  std::uint64_t minimum_saving_ns_per_input=0;
  // A declared reserve for work which must follow the irreversible durable
  // barrier. Actual publication/cleanup time is reported after completion;
  // this reserve is not a latency guarantee or permission to roll back a root.
  std::uint64_t publication_and_cleanup_reserve_ns=10'000'000;
};
struct PreparationCosts {
  std::uint64_t snapshot_rebuild_ns=0,catch_up_ns=0,equivalence_ns=0;
  std::uint64_t compiler_artifact_ns=0,publication_prepare_ns=0;
  std::uint64_t selection_prepare_ns=0;
};
struct PublicationOptions {recovery::PlanDescriptorLimits descriptor;};
enum class PolicyStop {
  eligible,invalid_policy,forecast_unavailable,invalid_forecast,invalid_epoch,
  hysteresis,not_faster,insufficient_saving,arithmetic_overflow,not_paid_back
};
struct PolicyDecision {
  PolicyStop stop=PolicyStop::invalid_policy;
  std::uint64_t saving_ns_per_input=0,charged_and_reserved_ns=0,
      required_future_inputs=0;
};
// Pure allocation-free policy arithmetic. Eligibility grants no source/plan,
// equivalence, epoch, memory, output or durable-publication authority. Native
// switching must independently establish every one of those barriers.
[[nodiscard]] PolicyDecision evaluate(const Policy&,const std::optional<Forecast>&,
    std::uint64_t current_epoch,std::optional<std::uint64_t> last_switch_epoch,
    PreparationCosts={}) noexcept;

struct Limits {
  std::uint64_t backlog_records=4096,backlog_bytes=16*1024*1024,
      staging_work=64*1024*1024,catch_up_steps=16*1024*1024,
      equivalence_work=64*1024*1024,equivalence_rows=65536,
      equivalence_cursor_work=1'000'000; // Per native result cursor; two at most.
};
struct Boundary {std::uint64_t owner=0,epoch=0;};
struct Options {
  BuildOptions build;
  program::ReplanLimits replan;
  Limits limits;
  Policy policy;
  std::optional<Forecast> forecast;
  // Optional C05 bridge fence, checked again against the actual owner.
  std::optional<Boundary> expected;
};
enum class Phase {inactive,catching_up,barrier_requested,waiting_output,verified,
  rejected,cancelled,failed,complete,recovery_required};
enum class Stop {none,backlog_limit,staging_limit,catch_up_limit,equivalence_limit,
  allocation_failure,source_changed,sequence_mismatch,source_mismatch,
  result_mismatch,native_failure,counter_overflow,clock_regression};
struct Status {
  Phase phase=Phase::inactive;
  Stop stop=Stop::none;
  bool admission_frozen=false;
  bool compiler_input_charged=false,publication_timings_complete=true;
  std::uint64_t source_owner=0,target_owner=0,snapshot_epoch=0,source_epoch=0,target_epoch=0,
      backlog_records=0,backlog_bytes=0,peak_backlog_records=0,peak_backlog_bytes=0,
      staged_records=0,replayed_records=0,staging_work=0,catch_up_steps=0,
      catch_up_native_work=0,equivalence_work=0,equivalence_native_work=0,equivalence_unobserved_startups=0,
      source_rows_compared=0,result_rows_compared=0,
      lowering_work=0,build_work=0,ledger_staging_ns=0,old_drain_ns=0,clock_reads=0;
  std::uint64_t publication_ns=0,cleanup_ns=0;
  std::array<char,64> source_physical_sha256{},target_physical_sha256{};
  PreparationCosts costs;
  PolicyDecision decision;
  resource::MemoryStatistics query_memory;
  resource::MemoryStatistics compiler_input_memory;
};
} // namespace crown::runtime::reoptimization
