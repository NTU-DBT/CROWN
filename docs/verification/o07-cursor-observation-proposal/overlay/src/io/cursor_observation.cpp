#include "crown/io/cursor_observation.hpp"
#include "crown/api/error.hpp"
#include <charconv>
#include <utility>
namespace crown::io {
namespace {
using namespace runtime;
void utf8(std::string_view text) {
  for (std::size_t i=0;i<text.size();) {
    const auto first=static_cast<unsigned char>(text[i++]);
    if (first<0x80) continue;
    unsigned remaining=0; std::uint32_t code=0,minimum=0;
    if (first>=0xc2 && first<=0xdf) { remaining=1; code=first&0x1fU; minimum=0x80; }
    else if (first>=0xe0 && first<=0xef) { remaining=2; code=first&0x0fU; minimum=0x800; }
    else if (first>=0xf0 && first<=0xf4) { remaining=3; code=first&0x07U; minimum=0x10000; }
    else throw Error("text_encoding","run-context text requires valid UTF-8; native values are unchanged");
    if (remaining>text.size()-i) throw Error("text_encoding","truncated UTF-8 in run-context text");
    while (remaining--) {
      const auto next=static_cast<unsigned char>(text[i++]);
      if ((next&0xc0U)!=0x80U) throw Error("text_encoding","invalid UTF-8 continuation in run-context text");
      code=(code<<6U)|(next&0x3fU);
    }
    if (code<minimum || code>0x10ffff || (code>=0xd800 && code<=0xdfff))
      throw Error("text_encoding","non-scalar UTF-8 in run-context text");
  }
}
struct Writer {
  std::string out;
  std::size_t limit;
  explicit Writer(std::size_t bytes):limit(bytes) {}
  void raw(std::string_view value) {
    if (out.size()>limit || value.size()>limit-out.size()) throw Error("resource_limit","run-context encoded-byte limit exceeded");
    out.append(value);
  }
  void quote(std::string_view value,bool dot=false) {
    utf8(value); raw("\"");
    constexpr char hex[]="0123456789abcdef";
    for (const char ch:value) {
      const auto byte=static_cast<unsigned char>(ch);
      if (ch=='\"') raw("\\\""); else if (ch=='\\') raw("\\\\");
      else if (byte<32) { if (dot) raw("\\"); const char encoded[]={'\\','u','0','0',hex[byte>>4U],hex[byte&15U]}; raw({encoded,6}); }
      else raw({&ch,1});
    }
    raw("\"");
  }
  template<class Integer> void number(Integer value) {
    char buffer[32]; const auto result=std::to_chars(buffer,buffer+sizeof(buffer),value);
    if (result.ec!=std::errc{}) throw Error("explain_encoding","integer encoding failed");
    raw({buffer,static_cast<std::size_t>(result.ptr-buffer)});
  }
  void boolean(bool value) { raw(value?"true":"false"); }
  void null() { raw("null"); }
  template<class T> void optional(const std::optional<T>& value) { if (value) number(*value); else null(); }
  template<class Range,class Fn> void array(const Range& values,Fn fn) {
    raw("["); bool first=true; for (const auto& value:values) { if (!first) raw(","); first=false; fn(value); } raw("]");
  }
  struct Object {
    Writer& w; bool first=true;
    template<class Fn> void field(std::string_view key,Fn fn) { if (!first) w.raw(","); first=false; w.quote(key); w.raw(":"); fn(); }
    void text(std::string_view key,std::string_view value) { field(key,[&] { w.quote(value); }); }
    template<class Integer> void number(std::string_view key,Integer value) { field(key,[&] { w.number(value); }); }
    void boolean(std::string_view key,bool value) { field(key,[&] { w.boolean(value); }); }
    void null(std::string_view key) { field(key,[&] { w.null(); }); }
  };
  template<class Fn> void object(Fn fn) { raw("{"); Object o{*this}; fn(o); raw("}"); }
  template<class Range> void ids(const Range& values) { array(values,[&](const auto& value) { number(value.value); }); }
};

const char* name(ResultCursorState v){switch(v){case ResultCursorState::active:return "active";case ResultCursorState::exhausted:return "exhausted";case ResultCursorState::cancelled:return "cancelled";case ResultCursorState::failed:return "failed";}return "unknown";}
const char* name(CursorTerminalReason v){switch(v){case CursorTerminalReason::not_recorded:return "not_recorded";case CursorTerminalReason::none:return "none";case CursorTerminalReason::exhausted:return "exhausted";case CursorTerminalReason::explicit_cancel:return "explicit_cancel";case CursorTerminalReason::destruction:return "destruction";case CursorTerminalReason::move_replacement:return "move_replacement";case CursorTerminalReason::invalidated:return "invalidated";case CursorTerminalReason::startup_failure:return "startup_failure";case CursorTerminalReason::next_failure:return "next_failure";}return "unknown";}
const char* name(CursorObservationSource v){switch(v){case CursorObservationSource::committed_results:return "committed_results";case CursorObservationSource::epoch_visible:return "epoch_visible";case CursorObservationSource::epoch_witnesses:return "epoch_witnesses";case CursorObservationSource::epoch_keys:return "epoch_keys";case CursorObservationSource::epoch_bucket:return "epoch_bucket";}return "unknown";}
const char* name(MetricAvailability v){switch(v){case MetricAvailability::unavailable:return "unavailable";case MetricAvailability::disabled:return "disabled";case MetricAvailability::available:return "available";}return "unknown";}
const char* name(MetricKind v){switch(v){case MetricKind::counter:return "counter";case MetricKind::high_water:return "high_water";case MetricKind::timing:return "timing";}return "unknown";}
const char* name(ResultView v){switch(v){case ResultView::core:return "core";case ResultView::sql:return "sql";}return "unknown";}
const char* name(SnapshotSide v){switch(v){case SnapshotSide::before:return "before";case SnapshotSide::after:return "after";}return "unknown";}
const char* name(ObservationMode v){switch(v){case ObservationMode::off:return "off";case ObservationMode::counters:return "counters";case ObservationMode::timed:return "timed";case ObservationMode::trace:return "trace";}return "unknown";}
const char* name(DeltaMode v){switch(v){case DeltaMode::maintenance:return "maintenance";case DeltaMode::delta:return "delta";}return "unknown";}
const char* name(DeltaCompletion v){switch(v){case DeltaCompletion::automatic:return "automatic";case DeltaCompletion::ordered_replay:return "ordered_replay";case DeltaCompletion::anchored:return "anchored";case DeltaCompletion::root_first:return "root_first";}return "unknown";}
const char* name(LiveMaintenance v){switch(v){case LiveMaintenance::on_output:return "on_output";case LiveMaintenance::incremental:return "incremental";case LiveMaintenance::eager:return "eager";}return "unknown";}
const char* name(PropagationOrder v){switch(v){case PropagationOrder::fifo:return "fifo";case PropagationOrder::lifo:return "lifo";}return "unknown";}
const char* name(NodeKind v){switch(v){case NodeKind::native:return "native";case NodeKind::generalized:return "generalized";}return "unknown";}
void work(Writer& w,const CursorWork& value){w.object([&](auto& o){o.number("work",value.work);o.number("calls",value.calls);o.number("route_checks",value.route_checks);o.number("descriptor_steps",value.descriptor_steps);o.number("frame_initializations",value.frame_initializations);o.number("cursor_opens",value.cursor_opens);o.number("cursor_advances",value.cursor_advances);o.number("frame_closes",value.frame_closes);o.number("tuple_lookups",value.tuple_lookups);o.number("selected_rows",value.selected_rows);o.number("bucket_lookups",value.bucket_lookups);o.number("key_fields",value.key_fields);o.number("equality_checks",value.equality_checks);o.number("output_fields",value.output_fields);o.number("rows_emitted",value.rows_emitted);o.number("binding_checks",value.binding_checks);o.number("binding_rejections",value.binding_rejections);o.number("direct_lookups",value.direct_lookups);o.number("overlay_rows",value.overlay_rows);o.number("fragment_steps",value.fragment_steps);o.number("binding_values",value.binding_values);o.number("witness_probes",value.witness_probes);o.number("witness_rows",value.witness_rows);o.number("join_rejections",value.join_rejections);});}
void delta_options(Writer& w,const DeltaOptions& d) { w.object([&](auto& o){
 o.text("requested_mode",name(d.mode));o.text("requested_completion",name(d.completion));
 o.text("live_maintenance",name(d.live_maintenance));o.text("view",name(d.view));
 o.field("work_limit",[&]{w.optional(d.work_limit);});o.field("cursor_work_limit",[&]{w.optional(d.cursor.work_limit);});
 o.field("epoch_view_work_limit",[&]{w.optional(d.epoch_view.work_limit);});
 o.number("spool_rows",d.spool_row_limit);o.number("spool_accounted_bytes",d.spool_byte_limit);
 o.field("physical_work_limit",[&]{w.optional(d.physical.work_limit);});o.number("derivation_limit",d.physical.derivation_limit);
 const auto& s=d.physical.support;o.field("support_work_limit",[&]{w.optional(s.work_limit);});o.number("support_limit",s.support_limit);
 o.text("propagation_order",name(s.order));o.boolean("capture_transitions",s.capture_transitions);
 o.field("observation",[&]{w.object([&](auto& x){const auto& a=s.observation;x.text("mode",name(a.mode));x.number("trace_capacity",a.trace_capacity);
 x.number("sample_period",a.sample_period);x.number("sample_offset",a.sample_offset);x.boolean("trace_timings",a.trace_timings);});});
}); }

void metric(Writer& w,const MetricValue& value){w.object([&](auto& o){
 o.text("availability",name(value.availability));o.field("value",[&]{if(value.availability==MetricAvailability::available)w.number(value.value);else w.null();});
 o.field("saturated",[&]{if(value.availability==MetricAvailability::available)w.boolean(value.saturated);else w.null();});
});}
void configuration(Writer& w,const std::optional<ObservationConfiguration>& value){
 if(!value){w.null();return;}w.object([&](auto& o){
 o.text("provenance","cursor_begin_runtime_configuration");o.number("owner",value->support_owner());o.number("generation",value->generation());o.boolean("generation_saturated",value->generation_saturated());
 o.text("mode",name(value->mode()));o.text("completion",name(value->completion()));o.number("query_factors",value->query_factors());
 o.field("requested_options",[&]{delta_options(w,value->requested_options());});
 });
}
} // namespace
std::string write_cursor_observation_json(const CursorObservation& value,std::size_t max_bytes){
 Writer w(max_bytes);w.object([&](auto& o){
 o.text("format","crown_cursor_observation");o.number("version",1);o.text("scope","one_cursor_lifetime_not_delta_output_spooling");
 o.number("owner",value.owner);o.number("sequence",value.sequence);
 o.field("cursor_id",[&]{if(value.options.mode==ObservationMode::off)w.null();else w.number(value.cursor_id);});
 o.field("cursor_id_saturated",[&]{if(value.options.mode==ObservationMode::off)w.null();else w.boolean(value.cursor_id_saturated);});
 o.boolean("constructed",value.constructed);o.text("source",name(value.source));o.text("view",name(value.view));
 o.field("side",[&]{if(value.side)w.quote(name(*value.side));else w.null();});o.boolean("tentative_at_creation",value.tentative_at_creation);
 o.text("state",name(value.state));o.text("terminal_reason",name(value.terminal_reason));
 o.field("cursor_work_limit",[&]{w.optional(value.limits.work_limit);});o.field("configuration",[&]{configuration(w,value.configuration);});
 o.text("timing_partition","startup_then_disjoint_successful_exhausted_failed_calls_and_cleanup; excludes_caller_pause; failed_startup_includes_unwinding");
 o.field("observation_options",[&]{w.object([&](auto& x){x.text("mode",name(value.options.mode));x.number("trace_capacity",value.options.trace_capacity);x.number("sample_period",value.options.sample_period);x.number("sample_offset",value.options.sample_offset);x.boolean("trace_timings",value.options.trace_timings);});});
 o.text("sampling_scope","per_cursor_counters_and_timings_are_not_per_update_trace_sampling");
 o.field("metrics",[&]{w.array(cursor_observation_registry(),[&](const auto& d){w.object([&](auto& x){x.number("id",static_cast<std::size_t>(d.id));x.text("name",d.name);x.text("unit",d.unit);x.text("scope",d.scope);x.text("kind",name(d.kind));x.field("measurement",[&]{metric(w,value.metric(d.id));});});});});
 o.field("mandatory",[&]{w.object([&](auto& x){const auto& m=value.mandatory;x.number("total_work",m.total_work);x.number("max_result_work",m.max_result_work);x.number("cleanup_frames",m.cleanup_frames);
 x.text("work_unit","existing_abstract_cursor_actions");x.text("last_scope","last_active_call_already_in_results_termination_or_failed_not_additive");
 x.field("startup",[&]{work(w,m.startup);});x.field("results",[&]{work(w,m.results);});x.field("termination",[&]{work(w,m.termination);});x.field("failed",[&]{work(w,m.failed);});x.field("last",[&]{work(w,m.last);});});});
 });return std::move(w.out);
}
std::string write_committed_state_gauges_json(const CommittedStateGauges& value,std::size_t max_bytes){
 Writer w(max_bytes);w.object([&](auto& o){
 o.text("format","crown_committed_state_gauges");o.number("version",1);o.number("owner",value.owner);o.number("sequence",value.sequence);
 o.text("scope","explicit_committed_state_read_available_with_telemetry_off");o.text("cardinality_unit","tuples_or_distinct_keys_as_named");
 o.text("visible_scope","per_node_E_factor_assignments_not_full_join_output_count");
 o.field("base_tuples",[&]{metric(w,value.base_tuples);});o.field("bases",[&]{w.array(value.bases,[&](const auto& b){w.object([&](auto& x){x.number("table",b.table.value);x.number("tuples",b.tuples);});});});
 o.field("nodes",[&]{w.array(value.nodes,[&](const auto& n){w.object([&](auto& x){x.number("node",n.node.value);x.text("kind",name(n.kind));x.number("records",n.records);x.number("survivors",n.survivors);x.number("projected_parent_keys",n.projected_parent_keys);x.field("visible_factor_assignments",[&]{metric(w,n.visible_factor_assignments);});});});});
 o.field("full_result_count",[&]{metric(w,value.full_result_count);});o.field("allocated_bytes",[&]{metric(w,value.allocated_bytes);});o.field("live_bytes",[&]{metric(w,value.live_bytes);});
 o.field("checkpoint_bytes",[&]{metric(w,value.checkpoint_bytes);});o.field("checkpoint_ns",[&]{metric(w,value.checkpoint_ns);});o.field("recovery_replay_length",[&]{metric(w,value.recovery_replay_length);});
 o.text("limitations","no_total_memory_or_durable_recovery_claim; allocating_snapshot_metadata_not_an_update_charge");
 });return std::move(w.out);
}
} // namespace crown::io
