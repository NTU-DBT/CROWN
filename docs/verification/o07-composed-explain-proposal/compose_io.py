from pathlib import Path
H=Path(__file__).resolve().parent;p=H/'overlay/src/io/explain.cpp';s=p.read_text()
s=s.replace('#include "crown/io/explain.hpp"','#include "crown/io/explain.hpp"\n#include "crown/io/run_context.hpp"\n#include "crown/io/cursor_observation.hpp"\n#include "crown/io/query_explain.hpp"')
s=s.replace('  void raw(std::string_view value) {','  std::size_t remaining() const noexcept { return limit-out.size(); }\n  void raw(std::string_view value) {')
s=s.replace('    utf8(value); raw("\\\"");','    if(value.size()>remaining())throw Error("resource_limit","EXPLAIN text exceeds encoded limit");\n    utf8(value); raw("\\\"");')
anchor='#undef CASE'
names={
'observability::RuntimePresence':['compile_only','live','stopped_retained','released'],
'observability::ExplanationKind':['physical','runtime','session'],
'observability::GaugeAvailability':['available','compile_only','pending_private_state','runtime_released'],
'SessionState':['created','running','paused','stopped','dropped'],
'SessionPhase':['ready','pending','paused_pending','draining','prepared','output'],
'SessionInputKind':['owned_stream','typed_physical','typed_window'],
'InitializationRoute':['empty_constructor','initialized_database','rebuilt_snapshot'],
'BuildMethod':['direct','insertion_replay'],
'io::InputFormat':['jsonl','binary','csv','legacy_signed','legacy_relations','legacy_insert_only','legacy_flags','legacy_timestamp_flags'],
'ResultCursorState':['active','exhausted','cancelled','failed'],
'CursorObservationSource':['committed_results','epoch_visible','epoch_witnesses','epoch_keys','epoch_bucket'],
'CursorTerminalReason':['not_recorded','none','exhausted','explicit_cancel','destruction','move_replacement','invalidated','startup_failure','next_failure']}
enums='\n'.join('const char* name('+t+' v){switch(v){'+''.join('CASE('+t+','+x+');' for x in vs)+'}throw Error("explain_enum","unknown report enum");}' for t,vs in names.items())
s=s.replace(anchor,enums+'\n'+anchor)
s=s.replace('const char* height_status(const PlanExplanation& report) { return report.height_status()==observability::HeightStatus::verified_original_minimum?"verified_original_minimum":"checked_upper"; }','''const char* height_status(const PlanExplanation& report) {
  if(report.plan().route()==PhysicalRoute::constant_false && !report.optimum())return "checked_constant_operator";
  return report.height_status()==observability::HeightStatus::verified_original_minimum?"verified_original_minimum":"checked_upper";
}''')
s=s.replace('o.text("scope",m.running()?"current_runtime_configuration":"compile_only");','''o.text("scope",m.presence()==observability::RuntimePresence::released?"retained_session_configuration":m.options()?"current_owner_configuration":"compile_only");
    o.text("runtime_presence",name(m.presence()));''')
s=s.replace('    o.text("codec","external_unmeasured"); o.text("sink","external_unmeasured");\n    o.text("retention_policy","per_attempt_not_recorded"); o.text("input_adapter","not_recorded");\n    o.text("initialization_method","not_recorded"); o.text("durable_delivery","not_implemented");','''    o.text("construction_input_and_external_identity","integrated_run_context; external_labels_are_caller_declared_unmeasured");
    o.text("output_disposition","integrated_current_and_last_attempt_output_actions");
    o.text("durable_delivery","not_implemented");''')
s=s.replace('    if (!m.running()) { o.null("runtime"); return; }','    if (!m.options()) { o.null("runtime"); return; }')
s=s.replace('r.text("state",name(m.state()));','r.field("state",[&]{if(m.state())w.quote(name(*m.state()));else w.null();});')
begin=s.index('template<class Summary> bool mode_bound(');end=s.index('void summary(',begin)
s=s[:begin]+'''bool mode_bound(const ObservationSummary& s) {return s.configuration.has_value();}
void historical_mode(Writer& w,Writer::Object& o,const ObservationSummary& s) {
  o.text("mode_binding",s.configuration?"exact_begin_configuration":"not_recorded");
  o.field("configuration",[&]{if(s.configuration)configuration(w,*s.configuration);else w.null();});
}
void current_configuration(Writer& w,const ObservationSnapshot& s) {
  if(s.current_configuration)configuration(w,*s.current_configuration);else w.null();
}
'''+s[end:]
s=s.replace('o.number("schema_version",1); o.text("artifact","crown_explain");','o.number("schema_version",2); o.text("artifact","crown_explain"); o.text("kind",name(e.kind()));')
s=s.replace('h.text("scope","original_core_query"); h.text("search_progress","not_attached");','h.text("scope",plan.route()==PhysicalRoute::constant_false?"p08_constant_false_operator_not_original_CQ_structural_minimum":"original_core_query"); h.text("search_progress","separate_query_explanation_form");')
s=s.replace('h.text("source","p08_checked_upper_only");','h.text("source",plan.route()==PhysicalRoute::constant_false?"p08_checked_constant_operator":"p08_checked_upper_only");')
s=s.replace('"B03_benchmark","per_attempt_mode_generation"','"B03_benchmark_validation","O08_release_workflow","native_integration_and_acceptance"')
# Add integrated fields directly to the final artifact, retaining typed values
# until this explicit export. Nested writers share the remaining encoded cap.
s=s.replace('    o.field("observations",[&] { observations(w,e); });','''    o.field("observations",[&] { observations(w,e); });
    o.field("run_context",[&]{if(e.observation())w.raw(write_run_context_json(*e.observation(),w.remaining()));else w.null();});
    o.field("session",[&]{session_status(w,e);});
    o.field("cursor",[&]{w.object([&](auto& c){
      c.text("scope","latest_enabled_cursor_lifecycle_publication; not_lifetime_or_update_total");
      c.text("availability",e.cursor()?"recorded":e.observation() && e.observation()->options.mode==ObservationMode::off?"disabled":"not_recorded");
      c.field("value",[&]{if(e.cursor())w.raw(write_cursor_observation_json(*e.cursor(),w.remaining()));else w.null();});
    });});
    o.field("committed_gauges",[&]{w.object([&](auto& g){g.text("availability",name(e.gauge_availability()));
      g.field("value",[&]{if(e.gauges())w.raw(write_committed_state_gauges_json(*e.gauges(),w.remaining()));else w.null();});
    });});''')
# Session facts are the exact captured owner status, including unavailable
# queue/window state after release, distinct from immutable configured limits.
extra=r'''
void session_status(Writer& w,const PlanExplanation& e){
 if(!e.session_status()){w.null();return;}const auto& s=*e.session_status();
 const auto context=e.observation()?e.observation()->session_context:nullptr;
 w.object([&](auto& o){o.text("state",name(s.state));o.text("phase",name(s.phase));o.number("committed_sequence",s.committed_sequence);
 o.boolean("input_failed",s.input_failed);o.boolean("end_of_input",s.end_of_input);o.field("pending_sequence",[&]{w.optional(s.pending_sequence);});o.number("pending_work",s.pending_work);o.number("output_remaining",s.output_remaining);o.field("pending_command_sequence",[&]{w.optional(s.pending_command_sequence);});
 o.text("queue_availability",s.queue?"available":context && context->queue?"released":"not_applicable");
 o.field("queue",[&]{if(!s.queue){w.null();return;}w.object([&](auto& q){q.number("batches",s.queue->batches);q.number("events",s.queue->events);q.number("accounted_bytes",s.queue->accounted_bytes);q.boolean("closed",s.queue->closed);q.boolean("failed",s.queue->failed);});});
 o.text("window_availability",s.window?"available":context && context->window?"released":"not_applicable");
 o.field("window",[&]{if(!s.window){w.null();return;}w.object([&](auto& a){const auto& v=*s.window;a.number("completed_command_sequence",v.completed_command_sequence);a.number("physical_sequence",v.physical_sequence);a.number("completed_watermark",v.completed_watermark);a.number("last_label",v.last_label);a.field("active_command_sequence",[&]{w.optional(v.active_command_sequence);});a.number("completed_steps",v.completed_steps);a.number("total_steps",v.total_steps);});});
 o.text("binding","actual_owning_session_metadata; no_supplied_plan_or_hash_join");
 });
}
'''
s=s.replace('void json(Writer& w,const PlanExplanation& e) {',extra+'\nvoid json(Writer& w,const PlanExplanation& e) {')
# Human helpers use actual typed fields, not compatibility JSON placeholders.
human=r'''
void human_declared(Writer& w,std::string_view label,const std::shared_ptr<const DeclaredBenchmarkContext>& value){
 w.raw(label);w.raw(" caller-declared identity (unmeasured): ");
 if(!value){w.raw("not declared\n");return;}
 const auto& v=value->labels();
 const auto field=[&](std::string_view n,const std::optional<std::string>& text){w.raw(n);w.raw("=");if(text)w.quote(*text);else w.raw("not_declared");w.raw(" ");};
 field("run",v.run);field("input_adapter",v.input_adapter);field("codec",v.output_codec);field("sink",v.sink);w.raw("\n");
}
void human_output(Writer& w,std::string_view label,const std::optional<ObservationSummary>& s){
 if(!s)return;
 human_declared(w,label,s->declared_benchmark);w.raw(label);w.raw(" output disposition: ");
 if(!s->output){w.raw("not recorded\n");return;}const auto& v=*s->output;
 const auto flag=[&](std::string_view n,bool value){w.raw(n);w.raw("=");w.boolean(value);w.raw(" ");};
 flag("discard_drain_requested",v.discard_drain_requested);flag("completion_drain_invoked",v.completion_drain_invoked);flag("retention_disabled",v.retention_disabled);flag("prepared",v.prepared);flag("published",v.published);flag("released",v.released);flag("transferred",v.transferred);flag("serialization_invoked",v.serialization_invoked);flag("sink_invoked",v.sink_invoked);flag("unread_discarded",v.unread_discarded);w.raw("\n");
}
void human_integrated(Writer& w,const PlanExplanation& e){
 w.raw("Runtime presence: ");w.raw(name(e.mode().presence()));w.raw("\n");
 if(e.observation()){
  const auto& obs=*e.observation();w.raw("Initialization: ");
  if(obs.initialization){const auto& i=*obs.initialization;w.raw(name(i.route));if(i.applied_build){w.raw("; build=");w.raw(name(i.applied_build->method));w.raw("; build work cap=");w.optional(i.applied_build->work_limit);}else w.raw("; no BuildOptions applied");}else w.raw("not recorded");w.raw("\n");
  human_declared(w,"Current",obs.current_declared_benchmark);
  if(obs.session_context){const auto& c=*obs.session_context;w.raw("Session input: ");w.raw(name(c.input_kind));w.raw("; ");
   if(c.input_kind==SessionInputKind::owned_stream){w.raw("wire format=");w.raw(name(c.input.format));}else w.raw("wire format not applicable to typed input");
   w.raw("; record/field caps=");w.number(c.input.limits.record_bytes);w.raw("/");w.number(c.input.limits.field_bytes);w.raw("\n");
   if(c.queue){w.raw("Queue limits (batches/events/accounted bytes): ");w.number(c.queue->batches);w.raw("/");w.number(c.queue->events);w.raw("/");w.number(c.queue->bytes);w.raw("\n");}
   if(c.window){w.raw("Window width/FIFO/labels/accounted bytes/work cap: ");w.number(c.window->width);w.raw(c.window->fifo==WindowFifoPolicy::global?"/global/":"/per_relation/");w.number(c.window->max_labels);w.raw("/");w.number(c.window->max_accounted_bytes);w.raw("/");w.number(c.window->command_work_limit);w.raw("\n");}
   w.raw("Default snapshot limits (rows/accounted bytes/cursor work): ");w.number(c.snapshot.rows);w.raw("/");w.number(c.snapshot.bytes);w.raw("/");w.optional(c.snapshot.cursor.work_limit);w.raw("; individual snapshots may override\n");
   w.raw("Exact construction/input/run options: ");w.raw(write_run_context_json(obs,w.remaining()));w.raw("\n");
  }
  human_output(w,"Current attempt",obs.current);human_output(w,"Last attempt",obs.last);
 }
 if(e.session_status()){w.raw("Session lifecycle and occupancy: ");session_status(w,e);w.raw("\n");}
 w.raw("Latest cursor (not an update/lifetime total): ");
 if(e.cursor()){
  const auto& c=*e.cursor();w.raw(name(c.source));w.raw("; sequence=");w.number(c.sequence);w.raw("; state=");w.raw(name(c.state));w.raw("; reason=");w.raw(name(c.terminal_reason));w.raw("\n");
  for(const auto& d:cursor_observation_registry()){const auto& v=c.metric(d.id);w.raw("  ");w.raw(d.name);w.raw("=");if(v.availability==MetricAvailability::available){w.number(v.value);if(v.saturated)w.raw(" (saturated)");}else w.raw(name(v.availability));w.raw(" [");w.raw(d.unit);w.raw("] ");w.raw(d.scope);w.raw("\n");}
  w.raw("  Mandatory cursor work total/max-result/cleanup frames: ");w.number(c.mandatory.total_work);w.raw("/");w.number(c.mandatory.max_result_work);w.raw("/");w.number(c.mandatory.cleanup_frames);w.raw("\n");
  w.raw("  Exact cursor binding/options and work phases: ");w.raw(write_cursor_observation_json(c,w.remaining()));w.raw("\n");
 }else w.raw(e.observation() && e.observation()->options.mode==ObservationMode::off?"disabled\n":"not recorded\n");
 w.raw("Committed gauges: ");w.raw(name(e.gauge_availability()));w.raw("\n");
 if(e.gauges()){w.raw("  Source/S/P/E counts and availability: ");w.raw(write_committed_state_gauges_json(*e.gauges(),w.remaining()));w.raw("\n");}
 w.raw("Memory/recovery: total allocator/live bytes, durable checkpoint/replay/delivery unavailable; component accounted bytes exclude allocator/transient/metadata costs.\n");
}
'''
pos=s.index('\n}\nstd::string write_explain_json(')
s=s[:pos]+'\n'+human+s[pos:]
s=s.replace('CROWN EXPLAIN v1','CROWN EXPLAIN v2')
s=s.replace('  else w.raw("Minimum height is not proved by the supplied plan.\\n");','  else w.raw(plan.route()==PhysicalRoute::constant_false?"Height 0 is the executable constant-false operator; no original CQ structural optimum is claimed.\\n":"Minimum height is not proved by the supplied plan.\\n");')
s=s.replace('  w.raw("Open: allocator-total bytes, durable delivery/recovery, statistics/ranking, benchmark validation, historical mode binding.\\n");','  human_integrated(w,report);\n  w.raw("Open: allocator-total bytes, durable delivery/recovery, statistics/ranking, benchmark/release validation and native integration acceptance.\\n");')
pos=s.rfind('} // namespace crown::io')
s=s[:pos]+r'''
std::string write_explain_tree_json(const PlanExplanation& e,ExplainTextLimits limits){Writer w(limits.bytes);w.object([&](auto& o){o.number("schema_version",2);o.text("artifact","crown_explain_tree");o.text("kind",name(e.kind()));o.text("scope",e.plan().route()==PhysicalRoute::constant_false?"p08_constant_false_operator":"p08_validated_selected_tree");o.number("native_height",e.selected_height());o.field("tree",[&]{tree(w,e.plan().tree(),&e.plan().validation());});});return std::move(w.out);}
std::string write_explain_json(const observability::QueryExplanation& e,ExplainTextLimits limits){Writer w(limits.bytes);w.object([&](auto& o){o.number("schema_version",2);o.text("artifact","crown_explain");o.text("kind","query");o.field("query_explanation",[&]{w.raw(write_query_explain_json(e,{w.remaining()}));});});return std::move(w.out);}
std::string write_explain_text(const observability::QueryExplanation& e,ExplainTextLimits limits){Writer w(limits.bytes);w.raw("CROWN EXPLAIN v2 — query/search form\n");w.raw(write_query_explain_text(e,{w.remaining()}));return std::move(w.out);}
std::string write_explain_dot(const observability::QueryExplanation& e,ExplainTextLimits limits){return write_query_explain_dot(e,{limits.bytes});}
std::string write_explain_tree_json(const observability::QueryExplanation& e,ExplainTextLimits limits){Writer w(limits.bytes);w.object([&](auto& o){o.number("schema_version",2);o.text("artifact","crown_explain_tree");o.text("kind","query");o.field("witness",[&]{w.raw(write_query_explain_tree_json(e,{w.remaining()}));});});return std::move(w.out);}
'''+s[pos:]
p.write_text(s)
# Avoid lexical >= tokens in unnamed defaulted template parameters.
p=H/'overlay/include/crown/observability/explain.hpp';s=p.read_text().replace('>={}','> = {}');p.write_text(s)
# The selected constant-false operator's height is not an original CQ upper.
p=H/'overlay/include/crown/observability/explain.hpp';s=p.read_text().replace('enum class HeightStatus { checked_upper, verified_original_minimum };','enum class HeightStatus { checked_upper, verified_original_minimum, checked_constant_operator };');p.write_text(s)
p=H/'overlay/src/observability/explain.cpp';s=p.read_text().replace('  if (proof(result->evidence)) result->status=HeightStatus::verified_original_minimum;','''  if(result->mode.plan().route()==PhysicalRoute::constant_false && std::holds_alternative<std::monostate>(result->evidence))
    result->status=HeightStatus::checked_constant_operator;
  if (proof(result->evidence)) result->status=HeightStatus::verified_original_minimum;''');p.write_text(s)
p=H/'overlay/src/io/explain.cpp';s=p.read_text().replace('report.plan().route()==PhysicalRoute::constant_false && !report.optimum()','report.height_status()==observability::HeightStatus::checked_constant_operator')
s=s.replace('s.number("native_height",e.selected_height());','s.number("native_height",e.selected_height()); s.text("height_domain",plan.route()==PhysicalRoute::constant_false?"executable_operator":"validated_query_tree");')
s=s.replace('h.text("scope",plan.route()==PhysicalRoute::constant_false?"p08_constant_false_operator_not_original_CQ_structural_minimum":"original_core_query");','''h.text("scope",e.height_status()==observability::HeightStatus::checked_constant_operator?"p08_constant_false_operator_not_original_CQ_structural_minimum":"original_core_query");
      h.field("original_upper",[&]{if(e.height_status()==observability::HeightStatus::checked_constant_operator)w.null();else w.number(e.selected_height());});''')
s=s.replace('h.text("source",plan.route()==PhysicalRoute::constant_false?"p08_checked_constant_operator":"p08_checked_upper_only");','h.text("source",e.height_status()==observability::HeightStatus::checked_constant_operator?"p08_checked_constant_operator":std::holds_alternative<planner::ValidatedIncumbent>(e.evidence())?"p06_validated_original_upper":"p08_checked_upper_only");')
p.write_text(s)
