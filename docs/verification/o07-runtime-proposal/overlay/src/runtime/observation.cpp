#include "crown/runtime/observation.hpp"
#include "crown/api/error.hpp"
#include <algorithm>
#include <chrono>
#include <limits>

namespace crown::runtime {
namespace {
constexpr std::array<MetricDescriptor,observation_metric_count> registry{{
  {MetricId::support_work, "support.work", "abstract_actions", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::support, MetricKind::counter, ""},
  {MetricId::support_native_record_visits, "support.native_record_visits", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::support, MetricKind::counter, ""},
  {MetricId::support_reverse_index_records_visited, "support.reverse_index_records_visited", "count", "optional-observation-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::support, MetricKind::counter, ""},
  {MetricId::support_child_key_probes, "support.child_key_probes", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::support, MetricKind::counter, ""},
  {MetricId::support_child_key_events, "support.child_key_events", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::support, MetricKind::counter, ""},
  {MetricId::support_survivor_transitions, "support.survivor_transitions", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::support, MetricKind::counter, ""},
  {MetricId::support_parent_key_transitions, "support.parent_key_transitions", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::support, MetricKind::counter, ""},
  {MetricId::support_visible_key_transitions, "support.visible_key_transitions", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::support, MetricKind::counter, ""},
  {MetricId::support_candidates_created, "support.candidates_created", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::support, MetricKind::counter, ""},
  {MetricId::support_candidates_reclaimed, "support.candidates_reclaimed", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::support, MetricKind::counter, ""},
  {MetricId::support_storage_changes, "support.storage_changes", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::support, MetricKind::counter, ""},
  {MetricId::support_metadata_changes, "support.metadata_changes", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::support, MetricKind::counter, ""},
  {MetricId::support_saved_child_flags, "support.saved_child_flags", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::support, MetricKind::counter, ""},
  {MetricId::support_journal_records, "support.journal_records", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::support, MetricKind::counter, ""},
  {MetricId::support_events_enqueued, "support.events_enqueued", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::support, MetricKind::counter, ""},
  {MetricId::support_events_applied, "support.events_applied", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::support, MetricKind::counter, ""},
  {MetricId::support_queue_peak, "support.queue_peak", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::support, MetricKind::high_water, ""},
  {MetricId::support_copied_rows, "support.copied_rows", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::support, MetricKind::counter, ""},
  {MetricId::support_copied_index_memberships, "support.copied_index_memberships", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::support, MetricKind::counter, ""},
  {MetricId::support_copied_metadata_entries, "support.copied_metadata_entries", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::support, MetricKind::counter, ""},
  {MetricId::support_copied_child_flags, "support.copied_child_flags", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::support, MetricKind::counter, ""},
  {MetricId::physical_work_inclusive, "physical.work_inclusive", "abstract_actions", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::physical, MetricKind::counter, "successfully charged support.work; incomplete nested charge is unavailable"},
  {MetricId::physical_work_exclusive, "physical.work_exclusive", "abstract_actions", "optional-observation-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::physical, MetricKind::counter, "support.work excluded"},
  {MetricId::physical_source_changes, "physical.source_changes", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::physical, MetricKind::counter, ""},
  {MetricId::physical_aliases_visited, "physical.aliases_visited", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::physical, MetricKind::counter, ""},
  {MetricId::physical_aliases_filtered, "physical.aliases_filtered", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::physical, MetricKind::counter, ""},
  {MetricId::physical_derivation_changes, "physical.derivation_changes", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::physical, MetricKind::counter, ""},
  {MetricId::physical_native_crossings, "physical.native_crossings", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::physical, MetricKind::counter, ""},
  {MetricId::physical_constraint_rows, "physical.constraint_rows", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::physical, MetricKind::counter, ""},
  {MetricId::physical_constraint_validations, "physical.constraint_validations", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::physical, MetricKind::counter, ""},
  {MetricId::delta_work, "delta.work", "abstract_actions", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::counter, "view/cursor actions; excludes physical/support work"},
  {MetricId::delta_candidates, "delta.candidates", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::counter, ""},
  {MetricId::delta_accepted, "delta.accepted", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::counter, ""},
  {MetricId::delta_rejected, "delta.rejected", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::counter, ""},
  {MetricId::delta_replay_preparation_work, "delta.replay_preparation_work", "abstract_actions", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::counter, "subset of layer work; not additive with total"},
  {MetricId::delta_replay_first_work, "delta.replay_first_work", "abstract_actions", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::counter, "subset of layer work; not additive with total"},
  {MetricId::delta_replay_results_work, "delta.replay_results_work", "abstract_actions", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::counter, "subset of layer work; not additive with total"},
  {MetricId::delta_replay_termination_work, "delta.replay_termination_work", "abstract_actions", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::counter, "subset of layer work; not additive with total"},
  {MetricId::delta_finalization_work, "delta.finalization_work", "abstract_actions", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::counter, "subset of layer work; not additive with total"},
  {MetricId::delta_spool_rows_prepared, "delta.spool_rows_prepared", "count", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::high_water, ""},
  {MetricId::delta_spool_bytes_prepared, "delta.spool_bytes_prepared", "accounted_bytes", "mandatory-runtime-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::high_water, ""},
  {MetricId::delta_mapped_records, "delta.mapped_records", "count", "optional-observation-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::counter, ""},
  {MetricId::delta_transferred_records, "delta.transferred_records", "count", "optional-observation-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::counter, ""},
  {MetricId::delta_discarded_records, "delta.discarded_records", "count", "optional-observation-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::counter, ""},
  {MetricId::delta_serialization_attempts, "delta.serialization_attempts", "count", "optional-observation-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::counter, ""},
  {MetricId::delta_serialization_successes, "delta.serialization_successes", "count", "optional-observation-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::counter, ""},
  {MetricId::delta_serialization_failures, "delta.serialization_failures", "count", "optional-observation-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::counter, ""},
  {MetricId::delta_sink_attempts, "delta.sink_attempts", "count", "optional-observation-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::counter, ""},
  {MetricId::delta_sink_successes, "delta.sink_successes", "count", "optional-observation-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::counter, ""},
  {MetricId::delta_sink_failures, "delta.sink_failures", "count", "optional-observation-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::counter, ""},
  {MetricId::delta_acknowledged_records, "delta.acknowledged_records", "count", "optional-observation-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::counter, ""},
  {MetricId::delta_propagation_ns, "delta.propagation_ns", "nanoseconds", "optional-observation-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::timing, "disjoint legacy delta timing phase"},
  {MetricId::delta_internal_delta_ns, "delta.internal_delta_ns", "nanoseconds", "optional-observation-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::timing, "disjoint legacy delta timing phase"},
  {MetricId::delta_output_mapping_ns, "delta.output_mapping_ns", "nanoseconds", "optional-observation-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::timing, "disjoint legacy delta timing phase"},
  {MetricId::delta_serialization_ns, "delta.serialization_ns", "nanoseconds", "optional-observation-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::timing, "disjoint legacy delta timing phase"},
  {MetricId::delta_sink_wait_ns, "delta.sink_wait_ns", "nanoseconds", "optional-observation-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::timing, "disjoint legacy delta timing phase"},
  {MetricId::delta_clock_reads, "delta.clock_reads", "count", "optional-observation-v1", "admitted_attempt; aborted values are attempted work, not committed changes", ObservationLayer::delta, MetricKind::counter, ""},
}};
void increment(std::uint64_t& value,std::uint64_t amount,bool& saturated) noexcept {
  const auto room=std::numeric_limits<std::uint64_t>::max()-value;
  if (amount>room) { value=std::numeric_limits<std::uint64_t>::max(); saturated=true; }
  else value+=amount;
}
#ifdef CROWN_RUNTIME_TESTING
detail::ObservationClock test_clock=nullptr;
#endif
}
std::span<const MetricDescriptor> observation_registry() noexcept { return registry; }
namespace detail {
std::shared_ptr<ObservationState> ObservationState::create(ObservationOptions options) {
  if (options.mode!=ObservationMode::off && options.mode!=ObservationMode::counters &&
      options.mode!=ObservationMode::timed && options.mode!=ObservationMode::trace)
    throw Error("invalid_observation_options","unknown observation mode");
  if (options.sample_period==0 || options.sample_offset>=options.sample_period)
    throw Error("invalid_observation_options","invalid causal sampling period/offset");
  if (options.mode==ObservationMode::off) return {};
  return std::make_shared<ObservationState>(options);
}
ObservationState::ObservationState(ObservationOptions options):options_(options) {
  snapshot_.options=options;
  if (options.mode==ObservationMode::trace) buffer_.resize(options.trace_capacity);
}
ObservationSummary* ObservationState::target() noexcept {
  if (snapshot_.current) return &*snapshot_.current;
  return snapshot_.last?&*snapshot_.last:nullptr;
}
ObservationTicket ObservationState::begin(ObservationLayer layer,std::uint64_t sequence) noexcept {
  bool owns=!snapshot_.current;
  if (owns) {
    increment(snapshot_.attempts,1,snapshot_.lifetime_counts_saturated);
    snapshot_.current.emplace(); occurrence_=observation_no_id; prefix_=0;
    auto& summary=*snapshot_.current;
    summary.attempt=snapshot_.attempts; summary.sequence=sequence; summary.owner=layer;
    selected_=options_.mode==ObservationMode::trace && !snapshot_.lifetime_counts_saturated &&
        sequence%options_.sample_period==options_.sample_offset;
    snapshot_.trace=options_.mode!=ObservationMode::trace?TraceDisposition::disabled:
        selected_?TraceDisposition::pending:TraceDisposition::not_sampled;
    snapshot_.trace_attempt=summary.attempt; snapshot_.trace_sequence=sequence;
    snapshot_.trace_records=0; snapshot_.trace_dropped=0; snapshot_.trace_dropped_saturated=false; snapshot_.trace_truncated=false;
    event(TraceKind::begin);
  }
  for (const auto& descriptor:registry) if (descriptor.layer==layer) {
    auto& value=snapshot_.current->values[static_cast<std::size_t>(descriptor.id)];
    if (value.availability==MetricAvailability::unavailable)
      value.availability=descriptor.kind==MetricKind::timing && !clocks_enabled()?
          MetricAvailability::disabled:MetricAvailability::available;
  }
  return {snapshot_.current->attempt,owns};
}
void ObservationState::finish(ObservationTicket ticket,ObservationOutcome outcome) noexcept {
  if (!ticket.owns || !snapshot_.current || snapshot_.current->attempt!=ticket.attempt) return;
  event(outcome==ObservationOutcome::committed?TraceKind::commit:TraceKind::abort);
  snapshot_.current->outcome=outcome;
  if (outcome==ObservationOutcome::committed) increment(snapshot_.commits,1,snapshot_.lifetime_counts_saturated);
  else increment(snapshot_.aborts,1,snapshot_.lifetime_counts_saturated);
  if (selected_) snapshot_.trace=outcome==ObservationOutcome::committed?TraceDisposition::committed:TraceDisposition::aborted;
  snapshot_.last=*snapshot_.current; snapshot_.current.reset();
}
void ObservationState::set(MetricId id,std::uint64_t amount) noexcept {
  if (auto* summary=target()) {
    auto& value=summary->values[static_cast<std::size_t>(id)];
    if (value.availability==MetricAvailability::available && !value.saturated) {
      value.value=amount;
      if (registry[static_cast<std::size_t>(id)].kind==MetricKind::timing && amount==UINT64_MAX)
        value.saturated=true;
    }
  }
}
void ObservationState::unavailable(MetricId id) noexcept {
  if (auto* summary=target()) summary->values[static_cast<std::size_t>(id)].availability=MetricAvailability::unavailable;
}
void ObservationState::add(MetricId id,std::uint64_t amount) noexcept {
  if (auto* summary=target()) {
    auto& value=summary->values[static_cast<std::size_t>(id)];
    if (value.availability==MetricAvailability::available) increment(value.value,amount,value.saturated);
  }
}
void ObservationState::event(TraceKind kind,std::uint64_t event_id,std::uint64_t cause,
    std::uint64_t node,std::uint64_t occurrence,std::uint64_t prefix,std::uint64_t before,
    std::uint64_t after,std::uint64_t role,std::uint64_t tuple) noexcept {
  if (!selected_) return;
  if (snapshot_.trace_records==buffer_.size()) {
    increment(snapshot_.trace_dropped,1,snapshot_.trace_dropped_saturated); snapshot_.trace_truncated=true; return;
  }
  buffer_[snapshot_.trace_records++]={kind,event_id,cause,node,
      occurrence==observation_no_id?occurrence_:occurrence,prefix==0?prefix_:prefix,before,after,role,tuple};
}
bool ObservationState::clocks_enabled() const noexcept {
  return options_.mode==ObservationMode::timed || (options_.mode==ObservationMode::trace && options_.trace_timings);
}
std::uint64_t ObservationState::now() noexcept {
  add(MetricId::delta_clock_reads);
#ifdef CROWN_RUNTIME_TESTING
  if (test_clock) return test_clock();
#endif
  const auto tick=std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
  return tick>0?static_cast<std::uint64_t>(tick):0;
}
ObservationSnapshot ObservationState::snapshot() const noexcept { return snapshot_; }
ObservationTrace ObservationState::trace() const {
  ObservationTrace result; result.snapshot=snapshot_;
  result.records.assign(buffer_.begin(),buffer_.begin()+static_cast<std::ptrdiff_t>(snapshot_.trace_records));
  return result;
}
ObservationSnapshot observation_snapshot(const std::shared_ptr<ObservationState>& state,ObservationOptions options) noexcept {
  if (state) return state->snapshot();
  ObservationSnapshot result; result.options=options; return result;
}
ObservationTrace observation_trace(const std::shared_ptr<ObservationState>& state,ObservationOptions options) {
  if (state) return state->trace();
  return {observation_snapshot(state,options),{}};
}
#ifdef CROWN_RUNTIME_TESTING
void set_observation_clock_for_testing(ObservationClock clock) noexcept { test_clock=clock; }
#endif
} // namespace detail
} // namespace crown::runtime
