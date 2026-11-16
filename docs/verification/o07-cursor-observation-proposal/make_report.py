from pathlib import Path
import re
H=Path(__file__).resolve().parent
p=H/'overlay/include/crown/io/cursor_observation.hpp';p.parent.mkdir(parents=True,exist_ok=True)
p.write_text('''#pragma once
#include "crown/runtime/delta.hpp"
namespace crown::io {
[[nodiscard]] std::string write_cursor_observation_json(const runtime::CursorObservation&,std::size_t max_bytes=16*1024*1024);
[[nodiscard]] std::string write_committed_state_gauges_json(const runtime::CommittedStateGauges&,std::size_t max_bytes=16*1024*1024);
} // namespace crown::io
''')
prior=(H.parent/'o07-run-context-proposal/overlay/src/io/run_context.cpp').read_text()
helpers=prior[prior.index('void utf8('):prior.index('#define ENUM_NAME')]
options=prior[prior.index('void delta_options('):prior.index('void session(')]
names={'ResultCursorState':['active','exhausted','cancelled','failed'],'CursorTerminalReason':['not_recorded','none','exhausted','explicit_cancel','destruction','move_replacement','invalidated','startup_failure','next_failure'],'CursorObservationSource':['committed_results','epoch_visible','epoch_witnesses','epoch_keys','epoch_bucket'],'MetricAvailability':['unavailable','disabled','available'],'MetricKind':['counter','high_water','timing'],'ResultView':['core','sql'],'SnapshotSide':['before','after'],'ObservationMode':['off','counters','timed','trace'],'DeltaMode':['maintenance','delta'],'DeltaCompletion':['automatic','ordered_replay','anchored','root_first'],'LiveMaintenance':['on_output','incremental','eager'],'PropagationOrder':['fifo','lifo'],'NodeKind':['native','generalized']}
enums='\n'.join('const char* name('+t+' v){switch(v){'+''.join('case '+t+'::'+v+':return "'+v+'";' for v in vs)+'}return "unknown";}' for t,vs in names.items())
header=(H/'overlay/include/crown/runtime/support.hpp').read_text();fields=re.findall(r'(\w+)\s*=\s*0',header[header.index('struct CursorWork {'):header.index('struct ResultCursorMetrics {')])
work='void work(Writer& w,const CursorWork& value){w.object([&](auto& o){'+''.join('o.number("'+f+'",value.'+f+');' for f in fields)+'});}\n'
body='''
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
'''
p=H/'overlay/src/io/cursor_observation.cpp';p.parent.mkdir(parents=True,exist_ok=True);p.write_text('#include "crown/io/cursor_observation.hpp"\n#include "crown/api/error.hpp"\n#include <charconv>\n#include <utility>\nnamespace crown::io {\nnamespace {\nusing namespace runtime;\n'+helpers+enums+'\n'+work+options+body)
