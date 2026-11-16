#pragma once

#include "crown/runtime/initialization.hpp"
#include <string>
#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <span>
#include <string_view>
#include <vector>

namespace crown::runtime {
// Optional observation never disables deterministic budget/accounting state.
// One configuration lives in SupportOptions and is inherited by all wrappers.
enum class ObservationMode { off, counters, timed, trace };
struct ObservationOptions {
  ObservationMode mode = ObservationMode::timed; // Retains legacy delta clocks.
  std::size_t trace_capacity = 256;
  std::uint64_t sample_period = 1, sample_offset = 0;
  bool trace_timings = true;
  bool operator==(const ObservationOptions&) const = default;
};
// Forward declarations keep the observation header below the support/physical/
// delta include chain. Definitions remain in their existing owning headers.
enum class DeltaMode;
enum class LiveMaintenance;
enum class DeltaCompletion;
enum class ResultView;
enum class PropagationOrder;
struct DeltaOptions;
class DeltaRuntime;

// Immutable, inline copy of all requested DeltaOptions and the resolved runtime
// configuration. It owns no runtime, rows, allocation, clock or mutable lookup.
// Owner/generation is process-local identity, not proof/durable authority. Once
// generation_saturated() is true the generation is only a capped diagnostic;
// the exact requested options and resolved mode remain available.
class ObservationConfiguration {
 public:
  ObservationConfiguration(const ObservationConfiguration&) noexcept = default;
  ObservationConfiguration& operator=(const ObservationConfiguration&) noexcept = default;
  [[nodiscard]] static constexpr std::uint32_t format_version() noexcept { return 1; }
  [[nodiscard]] DeltaOptions requested_options() const noexcept;
  [[nodiscard]] DeltaMode mode() const noexcept { return resolved_mode_; }
  [[nodiscard]] LiveMaintenance live_maintenance() const noexcept { return live_; }
  [[nodiscard]] DeltaCompletion completion() const noexcept { return resolved_completion_; }
  [[nodiscard]] ResultView view() const noexcept { return view_; }
  [[nodiscard]] std::uint64_t support_owner() const noexcept { return owner_; }
  [[nodiscard]] std::uint64_t generation() const noexcept { return generation_; }
  [[nodiscard]] bool generation_saturated() const noexcept { return generation_saturated_; }
  [[nodiscard]] std::size_t query_factors() const noexcept { return factors_; }
 private:
  friend class DeltaRuntime;
  ObservationConfiguration() noexcept = default;
  [[nodiscard]] static ObservationConfiguration capture(const DeltaOptions&,
      DeltaMode,DeltaCompletion,std::uint64_t,std::uint64_t,bool,std::size_t) noexcept;
  std::uint64_t owner_=0,generation_=0;
  bool generation_saturated_=false;
  std::size_t factors_=0;
  DeltaMode requested_mode_{},resolved_mode_{};
  LiveMaintenance live_{};
  DeltaCompletion requested_completion_{},resolved_completion_{};
  ResultView view_{};
  std::optional<std::uint64_t> support_work_,physical_work_,delta_work_,cursor_work_,view_work_;
  std::uint64_t support_limit_=0,derivation_limit_=0;
  PropagationOrder order_{};
  bool capture_transitions_=false;
  ObservationOptions observation_;
  std::size_t spool_rows_=0,spool_bytes_=0;
};
// Successful construction metadata is independent of optional event counters.
enum class InitializationRoute { empty_constructor, initialized_database, rebuilt_snapshot };
struct InitializationContext {
  InitializationRoute route=InitializationRoute::empty_constructor;
  // No BuildOptions were applied by the empty constructor.
  std::optional<BuildOptions> applied_build;
};
struct SessionRunContext;
struct BenchmarkLabels {
  std::optional<std::string> run, input_adapter, output_codec, sink;
};
// Explicit caller declarations only: no callback inspection, validation of
// claims, durability, completeness, measured cost, or proof authority.
class DeclaredBenchmarkContext {
 public:
  explicit DeclaredBenchmarkContext(BenchmarkLabels labels):labels_(std::move(labels)) {}
  [[nodiscard]] const BenchmarkLabels& labels() const noexcept { return labels_; }
 private:
  const BenchmarkLabels labels_;
};
struct OutputDisposition {
  bool discard_drain_requested=false, completion_drain_invoked=false, retention_disabled=false;
  bool prepared=false, published=false, released=false;
  bool transferred=false, serialization_invoked=false, sink_invoked=false;
  bool unread_discarded=false;
};
enum class ObservationLayer { support, physical, delta };
enum class ObservationOutcome { pending, committed, aborted };
enum class MetricAvailability { unavailable, disabled, available };
enum class MetricKind { counter, high_water, timing };
enum class MetricId {
  support_work,
  support_native_record_visits,
  support_reverse_index_records_visited,
  support_child_key_probes,
  support_child_key_events,
  support_survivor_transitions,
  support_parent_key_transitions,
  support_visible_key_transitions,
  support_candidates_created,
  support_candidates_reclaimed,
  support_storage_changes,
  support_metadata_changes,
  support_saved_child_flags,
  support_journal_records,
  support_events_enqueued,
  support_events_applied,
  support_queue_peak,
  support_copied_rows,
  support_copied_index_memberships,
  support_copied_metadata_entries,
  support_copied_child_flags,
  physical_work_inclusive,
  physical_work_exclusive,
  physical_source_changes,
  physical_aliases_visited,
  physical_aliases_filtered,
  physical_derivation_changes,
  physical_native_crossings,
  physical_constraint_rows,
  physical_constraint_validations,
  delta_work,
  delta_candidates,
  delta_accepted,
  delta_rejected,
  delta_replay_preparation_work,
  delta_replay_first_work,
  delta_replay_results_work,
  delta_replay_termination_work,
  delta_finalization_work,
  delta_spool_rows_prepared,
  delta_spool_bytes_prepared,
  delta_mapped_records,
  delta_transferred_records,
  delta_discarded_records,
  delta_serialization_attempts,
  delta_serialization_successes,
  delta_serialization_failures,
  delta_sink_attempts,
  delta_sink_successes,
  delta_sink_failures,
  delta_acknowledged_records,
  delta_propagation_ns,
  delta_internal_delta_ns,
  delta_output_mapping_ns,
  delta_serialization_ns,
  delta_sink_wait_ns,
  delta_clock_reads,
  nested_cursor_clock_reads,
  count
};
inline constexpr std::size_t observation_metric_count = static_cast<std::size_t>(MetricId::count);
struct MetricDescriptor {
  MetricId id;
  std::string_view name, unit, accounting, scope;
  ObservationLayer layer;
  MetricKind kind;
  // An inclusive work total contains lower-level work; it must not be summed
  // with that work again. Other phase subsets also overlap their layer total.
  std::string_view includes;
};
[[nodiscard]] std::span<const MetricDescriptor> observation_registry() noexcept;
struct MetricValue {
  std::uint64_t value = 0;
  MetricAvailability availability = MetricAvailability::unavailable;
  bool saturated = false;
};
struct ObservationSummary {
  ObservationSummary() noexcept = default;
  ObservationSummary(const ObservationSummary&) noexcept = default;
  ObservationSummary& operator=(const ObservationSummary&) noexcept = default;
  ObservationSummary(ObservationSummary&&) noexcept = default;
  ObservationSummary& operator=(ObservationSummary&&) noexcept = default;
  // Captured once by the outer delta begin; never relabeled by set_mode().
  // Lower-only attempts and disabled observation have no delta configuration.
  std::optional<ObservationConfiguration> configuration;
  std::optional<InitializationContext> initialization;
  std::shared_ptr<const DeclaredBenchmarkContext> declared_benchmark;
  std::optional<OutputDisposition> output;
  std::uint64_t attempt = 0, sequence = 0;
  ObservationLayer owner = ObservationLayer::support;
  ObservationOutcome outcome = ObservationOutcome::pending;
  std::array<MetricValue,observation_metric_count> values{};
  [[nodiscard]] const MetricValue& metric(MetricId id) const noexcept {
    const auto index=static_cast<std::size_t>(id);
    static constexpr MetricValue unavailable{};
    return index<values.size()?values[index]:unavailable;
  }
};
enum class TraceDisposition { disabled, not_sampled, pending, committed, aborted, released };
enum class TraceKind {
  begin, source_change, alias, native_event, child_enqueued, child_applied,
  journal, reverse_visit, core_result, mapped_record, prepared, drain,
  commit, abort, transferred, discarded, serialization_attempt,
  serialization_success, serialization_failure, sink_attempt, sink_success,
  sink_failure, acknowledged
};
inline constexpr std::uint64_t observation_no_id = UINT64_MAX;
// Numeric IDs only. No tuple pins, string pointers, borrowed rows or callbacks.
struct TraceRecord {
  TraceKind kind = TraceKind::begin;
  std::uint64_t event = 0, cause = 0;
  std::uint64_t node = observation_no_id, occurrence = observation_no_id, prefix = 0;
  std::uint64_t before = 0, after = 0, role = observation_no_id, tuple = observation_no_id;
};
struct ObservationSnapshot {
  ObservationSnapshot() noexcept = default;
  ObservationSnapshot(const ObservationSnapshot&) noexcept = default;
  ObservationSnapshot& operator=(const ObservationSnapshot&) noexcept = default;
  ObservationSnapshot(ObservationSnapshot&&) noexcept = default;
  ObservationSnapshot& operator=(ObservationSnapshot&&) noexcept = default;
  // Current configuration is distinct from current/last attempt binding.
  std::optional<ObservationConfiguration> current_configuration;
  std::optional<InitializationContext> initialization;
  std::shared_ptr<const DeclaredBenchmarkContext> current_declared_benchmark;
  std::shared_ptr<const SessionRunContext> session_context;
  ObservationOptions options;
  bool mandatory_accounting = true;
  std::uint64_t support_owner = 0;
  std::optional<ObservationSummary> current, last;
  std::uint64_t attempts = 0, commits = 0, aborts = 0;
  bool lifetime_counts_saturated = false;
  TraceDisposition trace = TraceDisposition::disabled;
  std::uint64_t trace_attempt = 0, trace_sequence = 0;
  std::size_t trace_records = 0;
  std::uint64_t trace_dropped = 0;
  bool trace_dropped_saturated = false;
  bool trace_truncated = false;
  // Session decoration is read-only, and does not assert durable acceptance.
  bool session_attached = false;
  std::uint64_t session_committed_sequence = 0;
};
struct ObservationTrace {
  ObservationSnapshot snapshot;
  std::vector<TraceRecord> records;
};
namespace detail {
// Shared monotonic/test clock without attributing a read to delta metrics.
[[nodiscard]] std::uint64_t read_observation_clock() noexcept;
struct ObservationTicket { std::uint64_t attempt=0; bool owns=false; };
class ObservationState {
 public:
  [[nodiscard]] static std::shared_ptr<ObservationState> create(ObservationOptions);
  explicit ObservationState(ObservationOptions);
  [[nodiscard]] ObservationTicket begin(ObservationLayer,std::uint64_t) noexcept;
  void finish(ObservationTicket,ObservationOutcome) noexcept;
  void bind_owner(std::uint64_t owner) noexcept { snapshot_.support_owner=owner; }
  void initialize(InitializationContext value) noexcept { snapshot_.initialization=value; }
  void declare_benchmark(std::shared_ptr<const DeclaredBenchmarkContext> value) noexcept {
    snapshot_.current_declared_benchmark=std::move(value);
  }
  void output(ObservationTicket ticket,OutputDisposition value) noexcept {
    auto* summary=target();
    if (summary && summary->owner==ObservationLayer::delta && summary->attempt==ticket.attempt)
      summary->output=value;
  }
  void configure(ObservationConfiguration value) noexcept { snapshot_.current_configuration=value; }
  [[nodiscard]] const std::optional<ObservationConfiguration>& configuration() const noexcept {
    return snapshot_.current_configuration;
  }
  void route(std::uint64_t occurrence,std::uint64_t prefix) noexcept {
    occurrence_=occurrence; prefix_=prefix;
  }
  void set(MetricId,std::uint64_t) noexcept;
  void add(MetricId,std::uint64_t=1) noexcept;
  void unavailable(MetricId) noexcept;
  void event(TraceKind,std::uint64_t event=0,std::uint64_t cause=0,
      std::uint64_t node=observation_no_id,std::uint64_t occurrence=observation_no_id,
      std::uint64_t prefix=0,std::uint64_t before=0,std::uint64_t after=0,
      std::uint64_t role=observation_no_id,std::uint64_t tuple=observation_no_id) noexcept;
  void note_cursor_clock_read() noexcept {
    if(snapshot_.current && snapshot_.current->owner==ObservationLayer::delta)
      add(MetricId::nested_cursor_clock_reads);
  }
  [[nodiscard]] bool clocks_enabled() const noexcept;
  [[nodiscard]] std::uint64_t now() noexcept;
  [[nodiscard]] ObservationSnapshot snapshot() const noexcept;
  // Explicit allocating diagnostic read; hooks never call this method.
  [[nodiscard]] ObservationTrace trace() const;
 private:
  ObservationOptions options_;
  ObservationSnapshot snapshot_;
  std::vector<TraceRecord> buffer_; // Resized once at admission, never grown.
  bool selected_=false;
  std::uint64_t occurrence_=observation_no_id,prefix_=0;
  [[nodiscard]] ObservationSummary* target() noexcept;
};
[[nodiscard]] ObservationSnapshot observation_snapshot(const std::shared_ptr<ObservationState>&,ObservationOptions) noexcept;
[[nodiscard]] ObservationTrace observation_trace(const std::shared_ptr<ObservationState>&,ObservationOptions);
#ifdef CROWN_RUNTIME_TESTING
// Exclusive test ownership only; nullptr restores the real steady clock.
using ObservationClock = std::uint64_t (*)() noexcept;
void set_observation_clock_for_testing(ObservationClock) noexcept;
// Exclusive test construction override for the diagnostic generation boundary.
// Zero restores normal initial generation. Does not mutate an existing owner.
void set_observation_initial_generation_for_testing(std::uint64_t) noexcept;
[[nodiscard]] std::uint64_t observation_initial_generation_for_testing() noexcept;
#endif
} // namespace detail
} // namespace crown::runtime
