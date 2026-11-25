#include "crown/runtime/observation.hpp"
#include "crown/runtime/delta.hpp"
#include "crown/resource/ownership.hpp"
#include <type_traits>
#include "crown/api/error.hpp"
#include <algorithm>
#include <bit>
#include <chrono>
#if defined(__x86_64__)
#include <cpuid.h>
#include <x86intrin.h>
#endif
#include <limits>

namespace crown::runtime {
// These inline diagnostic values remain nonallocating through copy, unwind,
// output release and session drop. Native options currently contain only fixed
// scalar/optional members; keep this contract explicit when extending them.
static_assert(std::is_trivially_copyable_v<DeltaOptions>);
static_assert(std::is_trivially_copyable_v<ObservationConfiguration>);
// Owned immutable admission metadata adds shared handles; copying/refcounting
// is nonallocating and cannot throw. Destruction may release owned metadata.
static_assert(std::is_nothrow_copy_constructible_v<ObservationSnapshot>);
static_assert(std::is_nothrow_copy_assignable_v<ObservationSnapshot>);
ObservationConfiguration ObservationConfiguration::capture(const DeltaOptions& options,
    DeltaMode resolved,DeltaCompletion completion,std::uint64_t owner,
    std::uint64_t generation,bool saturated,std::size_t factors) noexcept {
  ObservationConfiguration result;
  result.owner_=owner; result.generation_=generation;
  result.generation_saturated_=saturated; result.factors_=factors;
  result.requested_mode_=options.mode; result.resolved_mode_=resolved;
  result.live_=options.live_maintenance; result.requested_completion_=options.completion;
  result.resolved_completion_=completion; result.view_=options.view;
  result.support_work_=options.physical.support.work_limit;
  result.support_limit_=options.physical.support.support_limit;
  result.memory_limit_bytes_=options.physical.support.memory_limit_bytes;
  result.order_=options.physical.support.order;
  result.capture_transitions_=options.physical.support.capture_transitions;
  result.observation_=options.physical.support.observation;
  result.physical_work_=options.physical.work_limit;
  result.derivation_limit_=options.physical.derivation_limit;
  result.delta_work_=options.work_limit; result.cursor_work_=options.cursor.work_limit;
  result.view_work_=options.epoch_view.work_limit;
  result.spool_rows_=options.spool_row_limit; result.spool_bytes_=options.spool_byte_limit;
  return result;
}
DeltaOptions ObservationConfiguration::requested_options() const noexcept {
  DeltaOptions result;
  result.mode=requested_mode_; result.live_maintenance=live_;
  result.completion=requested_completion_; result.view=view_;
  result.physical.support.work_limit=support_work_;
  result.physical.support.support_limit=support_limit_;
  result.physical.support.memory_limit_bytes=memory_limit_bytes_;
  result.physical.support.order=order_;
  result.physical.support.capture_transitions=capture_transitions_;
  result.physical.support.observation=observation_;
  result.physical.work_limit=physical_work_;
  result.physical.derivation_limit=derivation_limit_;
  result.work_limit=delta_work_; result.cursor.work_limit=cursor_work_;
  result.epoch_view.work_limit=view_work_;
  result.spool_row_limit=spool_rows_; result.spool_byte_limit=spool_bytes_;
  return result;
}
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
  {MetricId::nested_cursor_clock_reads, "cursor.nested_clock_reads", "count", "optional-observation-v1", "cursor clock reads while this delta attempt is active; excludes later current-result reads", ObservationLayer::delta, MetricKind::counter, "subset of per-cursor clock_reads; do not add both; delta.clock_reads + this count reconciles active-attempt clock calls"},
}};
// Compact views of the registry for the per-epoch paths: the metrics of each
// layer (begin() visits only those) and each metric's kind.
struct LayerMetrics { std::array<std::uint16_t,observation_metric_count> ids{}; std::size_t size=0; };
constexpr auto layer_metrics=[] {
  std::array<LayerMetrics,3> out{};
  for (const auto& descriptor:registry) {
    auto& list=out[static_cast<std::size_t>(descriptor.layer)];
    list.ids[list.size++]=static_cast<std::uint16_t>(descriptor.id);
  }
  return out;
}();
constexpr auto metric_kinds=[] {
  std::array<MetricKind,observation_metric_count> out{};
  for (const auto& descriptor:registry) out[static_cast<std::size_t>(descriptor.id)]=descriptor.kind;
  return out;
}();
void increment(std::uint64_t& value,std::uint64_t amount,bool& saturated) noexcept {
  const auto room=std::numeric_limits<std::uint64_t>::max()-value;
  if (amount>room) { value=std::numeric_limits<std::uint64_t>::max(); saturated=true; }
  else value+=amount;
}
#ifdef CROWN_RUNTIME_TESTING
detail::ObservationClock test_clock=nullptr;
std::uint64_t test_initial_generation=0;
#endif
}
std::span<const MetricDescriptor> observation_registry() noexcept { return registry; }
namespace detail {
std::shared_ptr<ObservationState> ObservationState::create(const resource::MemoryAccount& account,ObservationOptions options) {
  if (options.mode!=ObservationMode::off && options.mode!=ObservationMode::counters &&
      options.mode!=ObservationMode::timed && options.mode!=ObservationMode::trace)
    throw Error("invalid_observation_options","unknown observation mode");
  if (options.sample_period==0 || options.sample_offset>=options.sample_period)
    throw Error("invalid_observation_options","invalid causal sampling period/offset");
  if (options.mode==ObservationMode::off) return {};
  return resource::make_accounted_shared<ObservationState>(observation_memory_owner,account,
      resource::MemoryPurpose::observation,account,options);
}
ObservationState::ObservationState(const resource::MemoryAccount& account,ObservationOptions options)
    :options_(options),buffer_(resource::MemoryAllocator<TraceRecord>(account,
        resource::MemoryPurpose::observation,observation_memory_owner)) {
  snapshot_.options=options;
  if (options.mode==ObservationMode::trace) buffer_.resize(options.trace_capacity);
  const bool clocks=clocks_enabled();
  for (std::size_t layer=0;layer<fresh_.size();++layer) {
    const auto& metrics=layer_metrics[layer];
    for (std::size_t i=0;i<metrics.size;++i) {
      const auto id=metrics.ids[i];
      fresh_[layer].values[id].availability=metric_kinds[id]==MetricKind::timing && !clocks?
          MetricAvailability::disabled:MetricAvailability::available;
    }
  }
}
ObservationTicket ObservationState::begin(ObservationLayer layer,std::uint64_t sequence) noexcept {
  // Nested layers share the outer attempt. Trace sampling uses physical
  // sequence, so retries differ from C01 attempt-ordinal sampling.
  bool owns=current_<0;
  if (owns) {
    increment(snapshot_.attempts,1,snapshot_.lifetime_counts_saturated);
    current_=last_==0?1:0;
    const auto slot=static_cast<std::size_t>(current_);
    auto& summary=slots_[slot];
    // Equivalent to copying fresh_[layer] (the availability of this layer's
    // metrics set), restoring only the values written since the last reset.
    const auto& fresh=fresh_[static_cast<std::size_t>(layer)];
    if (slot_layer_[slot]==static_cast<int>(layer)) {
      for (auto bits=dirty_[slot];bits;bits&=bits-1) {
        const auto id=static_cast<std::size_t>(std::countr_zero(bits));
        summary.values[id]=fresh.values[id];
      }
    } else { summary.values=fresh.values; slot_layer_[slot]=static_cast<int>(layer); }
    dirty_[slot]=0;
    summary.configuration=fresh.configuration; summary.declared_benchmark=fresh.declared_benchmark;
    summary.output=fresh.output; summary.outcome=fresh.outcome;
    occurrence_=observation_no_id; prefix_=0;
    summary.attempt=snapshot_.attempts; summary.sequence=sequence; summary.owner=layer;
    summary.initialization=snapshot_.initialization;
    if (layer==ObservationLayer::delta) {
      summary.configuration=snapshot_.current_configuration;
      summary.declared_benchmark=snapshot_.current_declared_benchmark;
      summary.output.emplace();
    }
    selected_=options_.mode==ObservationMode::trace && !snapshot_.lifetime_counts_saturated &&
        sequence%options_.sample_period==options_.sample_offset;
    snapshot_.trace=options_.mode!=ObservationMode::trace?TraceDisposition::disabled:
        selected_?TraceDisposition::pending:TraceDisposition::not_sampled;
    snapshot_.trace_attempt=summary.attempt; snapshot_.trace_sequence=sequence;
    snapshot_.trace_records=0; snapshot_.trace_dropped=0; snapshot_.trace_dropped_saturated=false; snapshot_.trace_truncated=false;
    event(TraceKind::begin);
    return {summary.attempt,owns};
  }
  // A nested layer shares the outer attempt and makes its metrics available.
  auto& summary=slots_[static_cast<std::size_t>(current_)];
  const auto& metrics=layer_metrics[static_cast<std::size_t>(layer)];
  const bool clocks=clocks_enabled();
  for (std::size_t i=0;i<metrics.size;++i) {
    const auto id=metrics.ids[i];
    auto& value=summary.values[id];
    if (value.availability==MetricAvailability::unavailable) {
      value.availability=metric_kinds[id]==MetricKind::timing && !clocks?
          MetricAvailability::disabled:MetricAvailability::available;
      touch(current_,static_cast<MetricId>(id));
    }
  }
  return {summary.attempt,owns};
}
void ObservationState::finish(ObservationTicket ticket,ObservationOutcome outcome) noexcept {
  if (!ticket.owns || current_<0 || slots_[static_cast<std::size_t>(current_)].attempt!=ticket.attempt) return;
  event(outcome==ObservationOutcome::committed?TraceKind::commit:TraceKind::abort);
  slots_[static_cast<std::size_t>(current_)].outcome=outcome;
  if (outcome==ObservationOutcome::committed) increment(snapshot_.commits,1,snapshot_.lifetime_counts_saturated);
  else increment(snapshot_.aborts,1,snapshot_.lifetime_counts_saturated);
  if (selected_) snapshot_.trace=outcome==ObservationOutcome::committed?TraceDisposition::committed:TraceDisposition::aborted;
  last_=current_; current_=-1;
}
void ObservationState::saturate_timing(MetricId id,MetricValue& value) noexcept {
  if (metric_kinds[static_cast<std::size_t>(id)]==MetricKind::timing) value.saturated=true;
}
void ObservationState::unavailable(MetricId id) noexcept {
  const int slot=target_slot();
  if (slot<0) return;
  slots_[static_cast<std::size_t>(slot)].values[static_cast<std::size_t>(id)].availability=MetricAvailability::unavailable;
  touch(slot,id);
}
void ObservationState::record(TraceKind kind,std::uint64_t event_id,std::uint64_t cause,
    std::uint64_t node,std::uint64_t occurrence,std::uint64_t prefix,std::uint64_t before,
    std::uint64_t after,std::uint64_t role,std::uint64_t tuple) noexcept {
  // Numeric records only, in the admitted fixed buffer. Full traces report
  // loss without allocating or changing query maintenance.
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
  return read_observation_clock();
}
namespace {
std::uint64_t steady_nanoseconds() noexcept {
  const auto tick=std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
  return tick>0?static_cast<std::uint64_t>(tick):0;
}
#if defined(__x86_64__)
// Timed observation reads the clock twice per delta attempt; a vDSO
// steady_clock read costs ~20 ns, an invariant-TSC read a few. The TSC is
// calibrated once against steady_clock (1 ms, at the first read) and then
// extends that steady_clock reading, so observation times stay in the
// steady_clock nanosecond domain. Without an invariant TSC (CPUID
// 0x80000007 EDX bit 8) every read uses steady_clock.
struct TscScale {
  bool usable=false;
  double scale=0;
  std::uint64_t base_ns=0, base_ticks=0;
};
const TscScale& tsc_scale() noexcept {
  static const TscScale value=[] {
    TscScale result;
    unsigned a=0,b=0,c=0,d=0;
    if (!__get_cpuid(0x80000007,&a,&b,&c,&d) || !(d>>8&1u)) return result;
    const auto s0=steady_nanoseconds(); const auto c0=__rdtsc();
    auto s1=s0; while (s1-s0<1000000) s1=steady_nanoseconds();
    const auto c1=__rdtsc();
    if (c1<=c0) return result;
    result.usable=true; result.scale=static_cast<double>(s1-s0)/static_cast<double>(c1-c0);
    result.base_ns=s1; result.base_ticks=c1;
    return result;
  }();
  return value;
}
#endif
}  // namespace
std::uint64_t read_observation_clock() noexcept {
#ifdef CROWN_RUNTIME_TESTING
  if (test_clock) return test_clock();
#endif
#if defined(__x86_64__)
  const auto& tsc=tsc_scale();
  if (tsc.usable) {
    // Another core's counter may trail the calibration read slightly.
    const auto ticks=static_cast<std::int64_t>(__rdtsc()-tsc.base_ticks);
    return ticks<=0?tsc.base_ns:tsc.base_ns+static_cast<std::uint64_t>(static_cast<double>(ticks)*tsc.scale);
  }
#endif
  return steady_nanoseconds();
}
ObservationSnapshot ObservationState::snapshot() const noexcept {
  auto result=snapshot_;
  if (current_>=0) result.current=slots_[static_cast<std::size_t>(current_)];
  if (last_>=0) result.last=slots_[static_cast<std::size_t>(last_)];
  return result;
}
ObservationTrace ObservationState::trace() const {
  ObservationTrace result; result.snapshot=snapshot();
  result.records.assign(buffer_.begin(),buffer_.begin()+static_cast<std::ptrdiff_t>(snapshot_.trace_records));
  return result;
}
CapturedObservationTrace ObservationState::capture_trace() const {
  // Explicit owning diagnostic copy on the live buffer account; hot event
  // hooks never allocate this retained record vector.
  CapturedObservationTrace result(buffer_.get_allocator().account());result.snapshot=snapshot();
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
CapturedObservationTrace capture_observation_trace(const std::shared_ptr<ObservationState>& state,
    ObservationOptions options,const resource::MemoryAccount& account) {
  if(state)return state->capture_trace();
  CapturedObservationTrace result(account);result.snapshot=observation_snapshot(state,options);return result;
}
#ifdef CROWN_RUNTIME_TESTING
void set_observation_clock_for_testing(ObservationClock clock) noexcept { test_clock=clock; }
void set_observation_initial_generation_for_testing(std::uint64_t value) noexcept { test_initial_generation=value; }
std::uint64_t observation_initial_generation_for_testing() noexcept { return test_initial_generation; }
#endif
} // namespace detail
} // namespace crown::runtime
