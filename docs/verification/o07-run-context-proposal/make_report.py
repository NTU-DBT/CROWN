from pathlib import Path
H=Path(__file__).resolve().parent
p=H/'overlay/include/crown/io/run_context.hpp';p.parent.mkdir(parents=True,exist_ok=True)
p.write_text('''#pragma once
#include "crown/runtime/session.hpp"
namespace crown::io {
// Explicit allocating export outside mutation. Strict UTF-8; native bytes are
// accepted/retained unchanged. Missing metadata is null, never inferred.
[[nodiscard]] std::string write_run_context_json(const runtime::ObservationSnapshot&,
    std::size_t max_bytes=16*1024*1024);
} // namespace crown::io
''')
old=(H.parent/'o07-explain-proposal/overlay/src/io/explain.cpp').read_text()
helper=old[old.index('void utf8('):old.index('#define CASE')].replace('EXPLAIN','run-context')
p=H/'overlay/src/io/run_context.cpp';p.parent.mkdir(parents=True,exist_ok=True)
p.write_text('''#include "crown/io/run_context.hpp"
#include "crown/api/error.hpp"
#include <charconv>
#include <utility>
namespace crown::io {
namespace {
using namespace runtime;
'''+helper+'''
#define ENUM_NAME(T,V) case T::V:return #V
const char* name(InitializationRoute v) { switch(v) {
 ENUM_NAME(InitializationRoute,empty_constructor);ENUM_NAME(InitializationRoute,initialized_database);ENUM_NAME(InitializationRoute,rebuilt_snapshot);
} return "unknown"; }
const char* name(BuildMethod v) { switch(v) { ENUM_NAME(BuildMethod,direct);ENUM_NAME(BuildMethod,insertion_replay); } return "unknown"; }
const char* name(SessionInputKind v) { switch(v) { ENUM_NAME(SessionInputKind,owned_stream);ENUM_NAME(SessionInputKind,typed_physical);ENUM_NAME(SessionInputKind,typed_window); } return "unknown"; }
const char* name(InputFormat v) { switch(v) { ENUM_NAME(InputFormat,jsonl);ENUM_NAME(InputFormat,binary);ENUM_NAME(InputFormat,csv);ENUM_NAME(InputFormat,legacy_signed);ENUM_NAME(InputFormat,legacy_relations);ENUM_NAME(InputFormat,legacy_insert_only);ENUM_NAME(InputFormat,legacy_flags);ENUM_NAME(InputFormat,legacy_timestamp_flags); } return "unknown"; }
const char* name(DeltaMode v) { switch(v) { ENUM_NAME(DeltaMode,maintenance);ENUM_NAME(DeltaMode,delta); } return "unknown"; }
const char* name(DeltaCompletion v) { switch(v) { ENUM_NAME(DeltaCompletion,automatic);ENUM_NAME(DeltaCompletion,ordered_replay);ENUM_NAME(DeltaCompletion,anchored);ENUM_NAME(DeltaCompletion,root_first); } return "unknown"; }
const char* name(LiveMaintenance v) { switch(v) { ENUM_NAME(LiveMaintenance,on_output);ENUM_NAME(LiveMaintenance,incremental);ENUM_NAME(LiveMaintenance,eager); } return "unknown"; }
const char* name(ResultView v) { switch(v) { ENUM_NAME(ResultView,core);ENUM_NAME(ResultView,sql); } return "unknown"; }
const char* name(PropagationOrder v) { switch(v) { ENUM_NAME(PropagationOrder,fifo);ENUM_NAME(PropagationOrder,lifo); } return "unknown"; }
const char* name(ObservationMode v) { switch(v) { ENUM_NAME(ObservationMode,off);ENUM_NAME(ObservationMode,counters);ENUM_NAME(ObservationMode,timed);ENUM_NAME(ObservationMode,trace); } return "unknown"; }
#undef ENUM_NAME
void optional_text(Writer& w,const std::optional<std::string>& value) { if(value)w.quote(*value);else w.null(); }
void initialization(Writer& w,const InitializationContext& c) { w.object([&](auto& o) {
 o.text("provenance","recorded_successful_construction");o.text("route",name(c.route));
 o.field("applied_build",[&] { if(!c.applied_build){w.null();return;}w.object([&](auto& b){
 b.text("method",name(c.applied_build->method));b.field("work_limit",[&]{w.optional(c.applied_build->work_limit);});});});
}); }
void declared(Writer& w,const std::shared_ptr<const DeclaredBenchmarkContext>& c) {
 if(!c){w.null();return;}w.object([&](auto& o){
 o.text("provenance","caller_declared_unmeasured");o.text("authority","none");
 const auto& labels=c->labels();
 o.field("run",[&]{optional_text(w,labels.run);});o.field("input_adapter",[&]{optional_text(w,labels.input_adapter);});
 o.field("output_codec",[&]{optional_text(w,labels.output_codec);});o.field("sink",[&]{optional_text(w,labels.sink);});
 });
}
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
void session(Writer& w,const std::shared_ptr<const SessionRunContext>& c) {
 if(!c){w.null();return;}w.object([&](auto& o){
 o.text("provenance","recorded_session_admission");o.text("input_kind",name(c->input_kind));
 o.text("wire_format_scope",c->input_kind==SessionInputKind::owned_stream?"applied_to_owned_stream":"not_applicable_typed_input");
 o.field("input_options",[&]{w.object([&](auto& x){const auto& i=c->input;x.text("format",name(i.format));
 x.field("table",[&]{if(i.table)w.number(i.table->value);else w.null();});
 x.number("delimiter_byte",static_cast<unsigned char>(i.delimiter));x.boolean("header",i.header);
 x.text("csv_operation",i.csv_operation==SetOperation::insert?"insert":"erase");
 x.field("relation_tokens",[&]{w.array(i.relation_tokens,[&](const auto& entry){w.object([&](auto& r){r.text("token",entry.first);r.number("table",entry.second.value);});});});
 x.field("null_token",[&]{optional_text(w,i.null_token);});x.field("source",[&]{optional_text(w,i.source);});x.number("byte_offset",i.byte_offset);
 x.field("limits",[&]{w.object([&](auto& l){l.number("record_bytes",i.limits.record_bytes);l.number("field_bytes",i.limits.field_bytes);
 l.number("columns",i.limits.columns);l.number("source_bytes",i.limits.source_bytes);l.number("sources",i.limits.sources);
 l.field("total_bytes",[&]{w.optional(i.limits.total_bytes);});l.field("records",[&]{w.optional(i.limits.records);});});});});});
 o.field("queue",[&]{if(!c->queue){w.null();return;}w.object([&](auto& q){q.number("batches",c->queue->batches);q.number("events",c->queue->events);q.number("accounted_bytes",c->queue->bytes);});});
 o.field("window",[&]{if(!c->window){w.null();return;}w.object([&](auto& x){const auto& v=*c->window;x.field("managed_tables",[&]{w.ids(v.managed_tables);});
 x.number("width",v.width);x.text("fifo",v.fifo==WindowFifoPolicy::global?"global":"per_relation");x.number("max_labels",v.max_labels);x.number("max_accounted_bytes",v.max_accounted_bytes);x.number("command_work_limit",v.command_work_limit);});});
 o.field("snapshot",[&]{w.object([&](auto& x){x.number("rows",c->snapshot.rows);x.number("accounted_bytes",c->snapshot.bytes);x.field("cursor_work_limit",[&]{w.optional(c->snapshot.cursor.work_limit);});});});
 o.field("initialization",[&]{initialization(w,c->initialization);});o.field("requested_delta",[&]{delta_options(w,c->requested_delta);});
 o.text("resolved_mode",name(c->resolved_mode));o.text("resolved_completion",name(c->resolved_completion));
 });
}
void attempt(Writer& w,const std::optional<ObservationSummary>& s) {
 if(!s){w.null();return;}w.object([&](auto& o){
 o.number("attempt",s->attempt);o.number("sequence",s->sequence);
 o.text("scope","attempt_begin_context_and_actual_output_lifecycle");
 o.field("initialization",[&]{if(s->initialization)initialization(w,*s->initialization);else w.null();});
 o.field("declared_benchmark",[&]{declared(w,s->declared_benchmark);});
 o.field("configuration_owner",[&]{if(s->configuration)w.number(s->configuration->support_owner());else w.null();});
 o.field("configuration_generation",[&]{if(s->configuration)w.number(s->configuration->generation());else w.null();});
 o.field("configuration_generation_saturated",[&]{if(s->configuration)w.boolean(s->configuration->generation_saturated());else w.null();});
 o.field("output",[&]{if(!s->output){w.null();return;}w.object([&](auto& x){const auto& v=*s->output;
 x.text("provenance","observed_attempt_actions");x.text("initial_retention","retain");
 x.boolean("discard_drain_requested",v.discard_drain_requested);x.boolean("completion_drain_invoked",v.completion_drain_invoked);
 x.boolean("retention_disabled",v.retention_disabled);x.boolean("prepared",v.prepared);x.boolean("published",v.published);x.boolean("released",v.released);
 x.boolean("transferred",v.transferred);x.boolean("serialization_invoked",v.serialization_invoked);x.boolean("sink_invoked",v.sink_invoked);x.boolean("unread_discarded",v.unread_discarded);
 });});
 });
}
} // namespace
std::string write_run_context_json(const ObservationSnapshot& s,std::size_t max_bytes) {
 Writer w(max_bytes);w.object([&](auto& o){
 o.text("format","crown_run_context");o.number("version",1);
 o.text("scope","diagnostic_metadata_companion_to_explain");o.text("missing_identity","null_not_inferred");
 o.text("external_callback_identity","caller_declarations_do_not_identify_or_validate_std_function_targets");
 o.text("external_guarantees","unmeasured_no_durability_or_recovery_claim");
 o.text("accounted_byte_scope","component_payload_accounting_excludes_allocator_overhead_transients_and_metadata_not_total_memory");
 o.field("current_initialization",[&]{if(s.initialization)initialization(w,*s.initialization);else w.null();});
 o.field("current_declared_benchmark",[&]{declared(w,s.current_declared_benchmark);});
 o.field("session",[&]{session(w,s.session_context);});
 o.field("current_attempt",[&]{attempt(w,s.current);});o.field("last_attempt",[&]{attempt(w,s.last);});
 });return std::move(w.out);
}
} // namespace crown::io
''')
