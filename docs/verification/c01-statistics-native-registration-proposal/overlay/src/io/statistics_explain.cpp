#include "crown/io/statistics_explain.hpp"
#include "crown/api/error.hpp"
#include <charconv>
#include <string_view>
#include <type_traits>

namespace crown::io {
namespace {
using namespace crown::runtime;
namespace st=runtime::statistics;
namespace ws=runtime::workload;
using Report=observability::StatisticsExplanation;
struct Writer {
  StatisticsTextLimits limit;
  StatisticsText result;
  void raw(std::string_view value){
    if(value.size()>limit.bytes-result.text.size())throw Error("resource_limit","statistics export byte limit exceeded");
    result.text.append(value);
  }
  void item(){if(result.items==limit.items)throw Error("resource_limit","statistics export item limit exceeded");++result.items;}
  void quoted(std::string_view value){
    raw("\"");
    for(char ch:value){
      const auto byte=static_cast<unsigned char>(ch);
      if(byte<32 || byte>126)throw Error("statistics_encoding","internal text is not ASCII");
      if(ch=='"' || ch=='\\')raw("\\");
      raw({&ch,1});
    }
    raw("\"");
  }
  void text(std::string_view value){item();quoted(value);}
  void bytes(std::string_view value){
    item();raw("\"");constexpr char hex[]="0123456789abcdef";
    for(char ch:value){const auto byte=static_cast<unsigned char>(ch);const char pair[]={hex[byte>>4U],hex[byte&15U]};raw({pair,2});}
    raw("\"");
  }
  template<class T>void number(T value){item();char buffer[32];const auto converted=std::to_chars(buffer,buffer+sizeof(buffer),value);
    if(converted.ec!=std::errc{})throw Error("statistics_encoding","integer encoding failed");
    raw({buffer,static_cast<std::size_t>(converted.ptr-buffer)});
  }
  void boolean(bool value){item();raw(value?"true":"false");}
  void null(){item();raw("null");}
  struct Object {
    Writer& w;bool first=true;
    template<class F>void field(std::string_view key,F fn){if(!first)w.raw(",");first=false;w.quoted(key);w.raw(":");fn();}
    void text(std::string_view key,std::string_view value){field(key,[&]{w.text(value);});}
    void bytes(std::string_view key,std::string_view value){field(key,[&]{w.bytes(value);});}
    template<class T>void number(std::string_view key,T value){field(key,[&]{w.number(value);});}
    void boolean(std::string_view key,bool value){field(key,[&]{w.boolean(value);});}
    void null(std::string_view key){field(key,[&]{w.null();});}
  };
  template<class F>void object(F fn){item();raw("{");Object object{*this};fn(object);raw("}");}
  template<class Range,class F>void array(const Range& values,F fn){item();raw("[");bool first=true;for(const auto& value:values){if(!first)raw(",");first=false;fn(value);}raw("]");}
  template<class T>void optional(const std::optional<T>& value){if(value)number(*value);else null();}
};
const char* name(runtime::DeltaMode value){switch(value){case runtime::DeltaMode::maintenance:return "maintenance";case runtime::DeltaMode::delta:return "delta";}throw Error("statistics_encoding","unknown report enum");}
const char* name(runtime::DeltaCompletion value){switch(value){case runtime::DeltaCompletion::automatic:return "automatic";case runtime::DeltaCompletion::ordered_replay:return "ordered_replay";case runtime::DeltaCompletion::anchored:return "anchored";case runtime::DeltaCompletion::root_first:return "root_first";}throw Error("statistics_encoding","unknown report enum");}
const char* name(runtime::LiveMaintenance value){switch(value){case runtime::LiveMaintenance::on_output:return "on_output";case runtime::LiveMaintenance::incremental:return "incremental";case runtime::LiveMaintenance::eager:return "eager";}throw Error("statistics_encoding","unknown report enum");}
const char* name(runtime::ResultView value){switch(value){case runtime::ResultView::core:return "core";case runtime::ResultView::sql:return "sql";}throw Error("statistics_encoding","unknown report enum");}
const char* name(runtime::PropagationOrder value){switch(value){case runtime::PropagationOrder::fifo:return "fifo";case runtime::PropagationOrder::lifo:return "lifo";}throw Error("statistics_encoding","unknown report enum");}
const char* name(runtime::ObservationMode value){switch(value){case runtime::ObservationMode::off:return "off";case runtime::ObservationMode::counters:return "counters";case runtime::ObservationMode::timed:return "timed";case runtime::ObservationMode::trace:return "trace";}throw Error("statistics_encoding","unknown report enum");}
const char* name(runtime::DeltaState value){switch(value){case runtime::DeltaState::ready:return "ready";case runtime::DeltaState::pending_delta:return "pending_delta";case runtime::DeltaState::paused:return "paused";case runtime::DeltaState::draining:return "draining";case runtime::DeltaState::epoch_prepared:return "epoch_prepared";case runtime::DeltaState::committed_output:return "committed_output";case runtime::DeltaState::committed:return "committed";case runtime::DeltaState::aborted:return "aborted";}throw Error("statistics_encoding","unknown report enum");}
const char* name(runtime::SessionState value){switch(value){case runtime::SessionState::created:return "created";case runtime::SessionState::running:return "running";case runtime::SessionState::paused:return "paused";case runtime::SessionState::stopped:return "stopped";case runtime::SessionState::dropped:return "dropped";}throw Error("statistics_encoding","unknown report enum");}
const char* name(runtime::SessionPhase value){switch(value){case runtime::SessionPhase::ready:return "ready";case runtime::SessionPhase::pending:return "pending";case runtime::SessionPhase::paused_pending:return "paused_pending";case runtime::SessionPhase::draining:return "draining";case runtime::SessionPhase::prepared:return "prepared";case runtime::SessionPhase::output:return "output";}throw Error("statistics_encoding","unknown report enum");}
const char* name(runtime::ObservationOutcome value){switch(value){case runtime::ObservationOutcome::pending:return "pending";case runtime::ObservationOutcome::committed:return "committed";case runtime::ObservationOutcome::aborted:return "aborted";}throw Error("statistics_encoding","unknown report enum");}
const char* name(runtime::ObservationLayer value){switch(value){case runtime::ObservationLayer::support:return "support";case runtime::ObservationLayer::physical:return "physical";case runtime::ObservationLayer::delta:return "delta";}throw Error("statistics_encoding","unknown report enum");}
const char* name(runtime::MetricAvailability value){switch(value){case runtime::MetricAvailability::unavailable:return "unavailable";case runtime::MetricAvailability::disabled:return "disabled";case runtime::MetricAvailability::available:return "available";}throw Error("statistics_encoding","unknown report enum");}
const char* name(runtime::TraceDisposition value){switch(value){case runtime::TraceDisposition::disabled:return "disabled";case runtime::TraceDisposition::not_sampled:return "not_sampled";case runtime::TraceDisposition::pending:return "pending";case runtime::TraceDisposition::committed:return "committed";case runtime::TraceDisposition::aborted:return "aborted";case runtime::TraceDisposition::released:return "released";}throw Error("statistics_encoding","unknown report enum");}
const char* name(runtime::MetricKind value){switch(value){case runtime::MetricKind::counter:return "counter";case runtime::MetricKind::high_water:return "high_water";case runtime::MetricKind::timing:return "timing";}throw Error("statistics_encoding","unknown report enum");}
const char* name(observability::RuntimePresence value){switch(value){case observability::RuntimePresence::compile_only:return "compile_only";case observability::RuntimePresence::live:return "live";case observability::RuntimePresence::stopped_retained:return "stopped_retained";case observability::RuntimePresence::released:return "released";}throw Error("statistics_encoding","unknown report enum");}
const char* name(observability::IntervalComparison value){switch(value){case observability::IntervalComparison::same:return "same";case observability::IntervalComparison::changed:return "changed";case observability::IntervalComparison::foreign_owner:return "foreign_owner";case observability::IntervalComparison::saturated:return "saturated";case observability::IntervalComparison::unavailable:return "unavailable";}throw Error("statistics_encoding","unknown report enum");}
const char* name(st::Availability value){switch(value){case st::Availability::available:return "available";case st::Availability::budget_exhausted:return "budget_exhausted";case st::Availability::pending_private_state:return "pending_private_state";case st::Availability::unavailable:return "unavailable";case st::Availability::not_applicable:return "not_applicable";}throw Error("statistics_encoding","unknown report enum");}
const char* name(st::Freshness value){switch(value){case st::Freshness::current:return "current";case st::Freshness::within_lag:return "within_lag";case st::Freshness::stale:return "stale";case st::Freshness::foreign_owner:return "foreign_owner";case st::Freshness::future_sequence:return "future_sequence";case st::Freshness::scope_mismatch:return "scope_mismatch";}throw Error("statistics_encoding","unknown report enum");}
const char* name(ws::Mode value){switch(value){case ws::Mode::off:return "off";case ws::Mode::counters:return "counters";}throw Error("statistics_encoding","unknown report enum");}
const char* name(ws::Availability value){switch(value){case ws::Availability::disabled:return "disabled";case ws::Availability::unavailable:return "unavailable";case ws::Availability::exact:return "exact";case ws::Availability::sampled:return "sampled";case ws::Availability::incomplete:return "incomplete";case ws::Availability::lower_bound:return "lower_bound";}throw Error("statistics_encoding","unknown report enum");}
const char* name(ws::Kind value){switch(value){case ws::Kind::physical:return "physical";case ws::Kind::occurrence:return "occurrence";case ws::Kind::support:return "support";case ws::Kind::degree:return "degree";case ws::Kind::logical:return "logical";}throw Error("statistics_encoding","unknown report enum");}
const char* name(ws::Operation value){switch(value){case ws::Operation::insert:return "insert";case ws::Operation::erase:return "erase";}throw Error("statistics_encoding","unknown report enum");}
const char* name(ws::Role value){switch(value){case ws::Role::input:return "input";case ws::Role::adapter:return "adapter";case ws::Role::derivation:return "derivation";case ws::Role::survivor:return "survivor";case ws::Role::parent_support:return "parent_support";case ws::Role::visible_support:return "visible_support";case ws::Role::native_touched_degree:return "native_touched_degree";case ws::Role::generalized_probe:return "generalized_probe";}throw Error("statistics_encoding","unknown report enum");}
const char* name(ws::InputScope value){switch(value){case ws::InputScope::physical_table:return "physical_table";case ws::InputScope::logical_epoch:return "logical_epoch";}throw Error("statistics_encoding","unknown report enum");}
const char* name(ws::DenominatorScope value){switch(value){case ws::DenominatorScope::unavailable:return "unavailable";case ws::DenominatorScope::all_committed_physical_inputs:return "all_committed_physical_inputs";case ws::DenominatorScope::committed_physical_stratum:return "committed_physical_stratum";case ws::DenominatorScope::complete_detail_sample_physical_stratum:return "complete_detail_sample_physical_stratum";case ws::DenominatorScope::observed_support_count_changes:return "observed_support_count_changes";case ws::DenominatorScope::observed_visited_routes:return "observed_visited_routes";}throw Error("statistics_encoding","unknown report enum");}
const char* name(SupportRole value){switch(value){case SupportRole::records:return "records";case SupportRole::survivors:return "survivors";case SupportRole::parent_support:return "parent_support";case SupportRole::visible:return "visible";}throw Error("statistics_encoding","unknown report enum");}
const char* name(NodeKind value){switch(value){case NodeKind::native:return "native";case NodeKind::generalized:return "generalized";}throw Error("statistics_encoding","unknown report enum");}
const char* name(PhysicalRoute value){switch(value){case PhysicalRoute::tree:return "tree";case PhysicalRoute::constant_true:return "constant_true";case PhysicalRoute::constant_false:return "constant_false";}throw Error("statistics_encoding","unknown report enum");}
void scalar(Writer& w,const Value& value){
  w.object([&](auto& o){o.text("type",type_name(type_of(value)));o.field("value",[&]{std::visit([&](const auto& v){
    using T=std::decay_t<decltype(v)>;
    if constexpr(std::is_same_v<T,std::string>)w.bytes(v);
    else if constexpr(std::is_same_v<T,bool>)w.boolean(v);
    else if constexpr(std::is_integral_v<T>)w.number(v);
    else w.text(v.to_string());
  },value);});o.text("encoding",std::holds_alternative<std::string>(value)?"hex_bytes":"native_canonical");});
}
void row(Writer& w,const Row& value){w.array(value,[&](const auto& v){scalar(w,v);});}
void fact(Writer& w,std::optional<std::uint64_t> value,std::string_view reason){
  w.object([&](auto& o){o.field("value",[&]{w.optional(value);});o.field("reason",[&]{if(value)w.null();else w.text(reason);});});
}
void observation_options(Writer& w,const ObservationOptions& value){
  w.object([&](auto& o){o.text("mode",name(value.mode));o.number("trace_capacity",value.trace_capacity);
    o.number("sample_period",value.sample_period);o.number("sample_offset",value.sample_offset);o.boolean("trace_timings",value.trace_timings);});
}
void delta_options(Writer& w,const DeltaOptions& value){
  w.object([&](auto& o){
    o.text("mode",name(value.mode));o.text("completion",name(value.completion));o.text("live_maintenance",name(value.live_maintenance));o.text("view",name(value.view));
    o.text("propagation",name(value.physical.support.order));o.boolean("capture_transitions",value.physical.support.capture_transitions);
    o.field("delta_work",[&]{w.optional(value.work_limit);});o.field("physical_work",[&]{w.optional(value.physical.work_limit);});
    o.field("support_work",[&]{w.optional(value.physical.support.work_limit);});o.field("cursor_work",[&]{w.optional(value.cursor.work_limit);});
    o.field("view_work",[&]{w.optional(value.epoch_view.work_limit);});
    o.number("support_count",value.physical.support.support_limit);o.number("derivation_count",value.physical.derivation_limit);
    o.number("spool_rows",value.spool_row_limit);o.number("spool_accounted_bytes",value.spool_byte_limit);
    o.field("o07",[&]{observation_options(w,value.physical.support.observation);});
  });
}
void mode_facts(Writer& w,const ws::ModeFacts& value){
  w.object([&](auto& o){o.boolean("delta_owner",value.delta_owner);o.text("requested_mode",name(value.requested_mode));
    o.text("resolved_mode",name(value.resolved_mode));o.text("requested_completion",name(value.requested_completion));o.text("resolved_completion",name(value.resolved_completion));
    o.text("live_maintenance",name(value.live_maintenance));o.text("view",name(value.view));});
}
void configuration(Writer& w,const ObservationConfiguration& value){
  w.object([&](auto& o){o.number("owner",value.support_owner());o.number("generation",value.generation());o.boolean("generation_saturated",value.generation_saturated());
    o.text("resolved_mode",name(value.mode()));o.text("resolved_completion",name(value.completion()));o.text("live_maintenance",name(value.live_maintenance()));
    o.text("view",name(value.view()));o.number("query_factors",value.query_factors());o.field("requested",[&]{delta_options(w,value.requested_options());});});
}
void labels(Writer& w,const std::shared_ptr<const DeclaredBenchmarkContext>& value){
  if(!value){w.null();return;}const auto& v=value->labels();
  w.object([&](auto& o){o.text("authority","caller_declared_unmeasured");const auto field=[&](std::string_view key,const auto& text){o.field(key,[&]{if(text)w.bytes(*text);else w.null();});};
    field("run_hex",v.run);field("input_adapter_hex",v.input_adapter);field("output_codec_hex",v.output_codec);field("sink_hex",v.sink);});
}
void observation_summary(Writer& w,const std::optional<ObservationSummary>& value){
  if(!value){w.null();return;}const auto& v=*value;
  w.object([&](auto& o){o.number("attempt",v.attempt);o.number("sequence",v.sequence);o.text("layer",name(v.owner));o.text("outcome",name(v.outcome));
    o.field("begin_configuration",[&]{if(v.configuration)configuration(w,*v.configuration);else w.null();});
    o.field("declared_labels",[&]{labels(w,v.declared_benchmark);});
    o.field("metrics",[&]{w.array(observation_registry(),[&](const auto& descriptor){const auto& metric=v.metric(descriptor.id);
      w.object([&](auto& m){m.text("name",descriptor.name);m.text("unit",descriptor.unit);m.text("kind",name(descriptor.kind));m.text("availability",name(metric.availability));
        m.number("raw",metric.value);m.boolean("saturated",metric.saturated);
        m.text("raw_status",metric.saturated || metric.availability==MetricAvailability::unavailable?"lower_bound":metric.availability==MetricAvailability::disabled?"disabled":"exact");
        m.field("fact",[&]{fact(w,metric.availability==MetricAvailability::available && !metric.saturated?std::optional<std::uint64_t>{metric.value}:std::nullopt,
            metric.saturated?"saturated":name(metric.availability));});
      });});});
  });
}
void o07(Writer& w,const Report& report){
  const auto& v=report.observation();
  w.object([&](auto& o){o.field("options",[&]{observation_options(w,v.options);});
    o.field("recorded_owner",[&]{if(v.support_owner)w.number(v.support_owner);else w.null();});
    o.field("current_configuration",[&]{if(v.current_configuration)configuration(w,*v.current_configuration);else w.null();});
    o.field("current_declared_labels",[&]{labels(w,v.current_declared_benchmark);});
    o.text("counts_status",v.options.mode==ObservationMode::off?"disabled":v.lifetime_counts_saturated?"lower_bound":"exact");
    o.field("attempts",[&]{if(v.options.mode==ObservationMode::off)w.null();else w.number(v.attempts);});
    o.field("commits",[&]{if(v.options.mode==ObservationMode::off)w.null();else w.number(v.commits);});
    o.field("aborts",[&]{if(v.options.mode==ObservationMode::off)w.null();else w.number(v.aborts);});
    o.field("current",[&]{observation_summary(w,v.current);});o.field("last",[&]{observation_summary(w,v.last);});
    o.text("trace_disposition",name(v.trace));o.number("trace_retained",report.trace().size());o.number("trace_dropped",v.trace_dropped);
    o.boolean("trace_dropped_saturated",v.trace_dropped_saturated);o.boolean("trace_truncated",v.trace_truncated);
    o.text("export_scope","options_current_and_begin_mode_bound_summaries; trace_records_and_cursor_details_not_exported");
  });
}
void limits(Writer& w,const st::Limits& v){w.object([&](auto& o){
  o.number("work",v.work);o.number("rows",v.rows);o.number("distinct_keys",v.distinct_keys);o.number("accounted_bytes",v.accounted_bytes);
  o.number("projection_width",v.projection_width);o.number("heavy_keys",v.heavy_keys);
});}
void usage(Writer& w,const st::Usage& v){w.object([&](auto& o){
  o.number("work",v.work);o.number("rows",v.rows);o.number("distinct_keys",v.distinct_keys);o.number("accounted_bytes",v.accounted_bytes);
  o.number("max_row_capacity",v.max_row_capacity);o.number("max_histogram_capacity",v.max_histogram_capacity);o.number("max_heavy_capacity",v.max_heavy_capacity);
});}
void layout(Writer& w,const storage::TupleLayout& v){w.object([&](auto& o){
  o.number("id",v.id().value);o.number("catalog_version",v.context().catalog_version);o.bytes("binding_hex",v.context().binding);
  o.field("origin",[&]{if(!v.origin()){w.null();return;}w.object([&](auto& x){x.number("table",v.origin()->table.value);x.number("source_schema_version",v.origin()->source_schema_version);});});
  o.field("fields",[&]{w.array(v.fields(),[&](const auto& f){w.object([&](auto& x){x.text("type",type_name(f.type));x.field("variable",[&]{if(f.variable)w.number(f.variable->value);else w.null();});
    x.field("decimal",[&]{if(!f.decimal){w.null();return;}w.object([&](auto& d){d.number("precision",f.decimal->precision);d.number("scale",f.decimal->scale);});});
  });});});
});}
void selection(Writer& w,const st::Selection& v){w.object([&](auto& o){
  std::visit([&](const auto& scope){using T=std::decay_t<decltype(scope)>;
    if constexpr(std::is_same_v<T,st::SourceScope>){o.text("kind","source");o.number("id",scope.table.value);o.null("role");}
    else if constexpr(std::is_same_v<T,st::NodeScope>){o.text("kind","node");o.number("id",scope.node.value);o.text("role",name(scope.role));}
    else if constexpr(std::is_same_v<T,st::OccurrenceScope>){o.text("kind","occurrence");o.number("id",scope.occurrence.value);o.null("role");}
    else{o.text("kind","index");o.number("id",scope.requirement.value);o.null("role");}
  },v.scope);
  o.field("projection_fields",[&]{if(v.fields)w.array(*v.fields,[&](auto field){w.number(field.value);});else w.null();});
});}
void distribution(Writer& w,const st::Distribution& v){
  const bool exact=v.completion==st::Completion::exact;
  w.object([&](auto& o){o.text("completion",exact?"exact":"budget_exhausted");o.number("visited",v.visited);
    o.field("ndv",[&]{fact(w,v.ndv,"budget_exhausted");});
    o.field("histogram",[&]{if(!exact){w.null();return;}w.array(v.histogram,[&](const auto& pair){w.object([&](auto& x){x.number("multiplicity",pair.first);x.number("positive_keys",pair.second);});});});
    o.field("top_k",[&]{if(!v.heavy_keys){w.null();return;}w.array(*v.heavy_keys,[&](const auto& key){w.object([&](auto& x){x.field("key",[&]{row(w,key.key);});x.number("multiplicity",key.count);});});});
    o.field("unknown_reason",[&]{if(exact)w.null();else w.text("budget_exhausted");});
  });
}
void state(Writer& w,const Report& report){
  const auto reason=!report.combined()?"runtime_released":!report.state_requested()?"not_requested":name(report.combined()->state().availability());
  w.object([&](auto& o){o.boolean("requested",report.state_requested());o.text("availability",reason);
    o.field("value",[&]{if(!report.combined() || !report.state_requested()){w.null();return;}const auto& v=report.combined()->state();
      w.object([&](auto& s){s.number("owner",v.stamp().owner.value);s.number("sequence",v.stamp().sequence);s.text("layer",v.stamp().layer==st::OwnerLayer::physical?"physical":"support");
        s.number("requested_components",v.requested_components());s.text("physical_source_scope",name(v.physical_source_scope()));
        s.field("limits",[&]{limits(w,v.limits());});s.field("usage",[&]{usage(w,v.usage());});
        s.field("components",[&]{w.array(v.components(),[&](const auto& c){w.object([&](auto& item){item.field("selection",[&]{selection(w,c.selection);});
          item.text("availability",name(c.availability));item.field("node_kind",[&]{if(c.node_kind)w.text(name(*c.node_kind));else w.null();});
          item.field("layout",[&]{if(c.layout)layout(w,*c.layout);else w.null();});
          item.field("cardinality",[&]{fact(w,c.cardinality,name(c.availability));});
          item.field("distribution",[&]{if(c.distribution)distribution(w,*c.distribution);else w.null();});
          item.text("distribution_absence_reason",c.distribution?"present":c.availability==st::Availability::available?"not_requested":name(c.availability));
          item.field("storage_invalidation",[&]{if(!c.storage_invalidation){w.null();return;}const auto& inv=*c.storage_invalidation;w.object([&](auto& x){x.number("owner",inv.owner.value);x.number("relation",inv.relation.value);x.number("revision",inv.revision);x.text("scope","invalidation_not_committed_freshness");});});
        });});});
      });
    });
  });
}
void workload_options(Writer& w,const ws::Options& v){w.object([&](auto& o){o.text("mode",name(v.mode));o.number("max_cells",v.max_cells);
  o.number("period",v.period);o.number("offset",v.offset);o.number("detail_budget",v.detail_budget);});}
void stamp(Writer& w,const ws::Stamp& v){w.object([&](auto& o){
  o.number("owner",v.owner.value);o.number("committed_epoch",v.committed_epoch);o.number("interval_start_epoch",v.interval_start_epoch);
  o.number("reset_generation",v.reset_generation);o.number("configuration_generation",v.configuration_generation);o.number("segment",v.segment);o.number("format_version",v.format_version);
  o.boolean("reset_saturated",v.reset_saturated);o.boolean("configuration_saturated",v.configuration_saturated);o.boolean("segment_saturated",v.segment_saturated);
});}
void metadata(Writer& w,const ws::Metadata& v){w.object([&](auto& o){
#define N(member) o.number(#member,v.member)
  N(attempts);N(committed);N(aborted);N(selected);N(complete);N(aborted_selected);N(truncated);N(committed_truncated);N(guards);N(detail_actions);N(cleared_cells);N(merged_cells);
#undef N
  o.text("numeric_status",v.saturated?"lower_bound":"exact");o.boolean("saturated",v.saturated);o.boolean("invalid_descriptor",v.invalid_descriptor);
  o.boolean("protocol_error",v.protocol_error);o.boolean("ordinal_exhausted",v.ordinal_exhausted);
});}
void descriptor(Writer& w,const ws::Descriptor& v){w.object([&](auto& o){o.text("kind",name(v.kind));o.text("input_scope",name(v.input_scope));
  o.field("initiating_table",[&]{if(v.initiating_table())w.number(v.initiating_table()->value);else w.null();});
  o.number("scope",v.scope);o.text("operation",name(v.operation));o.text("role",name(v.role));
  o.field("node",[&]{if(v.node)w.number(v.node->value);else w.null();});o.field("occurrence",[&]{if(v.occurrence)w.number(v.occurrence->value);else w.null();});
  o.field("edge",[&]{w.optional(v.edge);});o.field("index",[&]{if(v.index)w.number(v.index->value);else w.null();});
  o.field("event_operation",[&]{if(v.event_operation)w.text(name(*v.event_operation));else w.null();});
});}
void fraction(Writer& w,const ws::Fraction& v,bool clipped=false){
  const auto availability=clipped?ws::Availability::unavailable:v.availability;
  const bool known=availability==ws::Availability::exact || availability==ws::Availability::sampled;
  w.object([&](auto& o){o.text("availability",name(availability));o.text("denominator_scope",name(v.denominator_scope));
    o.field("numerator",[&]{if(known)w.number(v.numerator);else w.null();});o.field("denominator",[&]{if(known)w.number(v.denominator);else w.null();});
    o.field("reason",[&]{if(known)w.null();else w.text(clipped?"lower_bound":name(v.availability));});
  });
}
void cell(Writer& w,const ws::Cell& v,const ws::Descriptor& d,bool global_saturation){
  w.object([&](auto& o){o.text("numeric_status",v.saturated || global_saturation?"lower_bound":"exact");o.boolean("saturated",v.saturated);
    o.text("population",d.kind==ws::Kind::support?"unequal_support_event_after_values":d.role==ws::Role::generalized_probe?"generalized_pre_probe_presence":d.kind==ws::Kind::degree?"directed_child_event_degrees":d.kind==ws::Kind::occurrence?"adapter_route_visits":"committed_input_census");
#define N(member) o.number(#member,v.member)
    N(inputs);N(changed);N(noop);N(visited);N(accepted);N(rejected);N(complete_detail_inputs);N(changes);N(zero_to_positive);N(positive_to_zero);N(count);N(sum);
#undef N
    const auto extrema=v.count && !v.saturated && !global_saturation;
    o.field("minimum",[&]{fact(w,extrema?std::optional<std::uint64_t>{v.min}:std::nullopt,v.saturated || global_saturation?"saturated":"empty_population");});
    o.field("maximum",[&]{fact(w,extrema?std::optional<std::uint64_t>{v.max}:std::nullopt,v.saturated || global_saturation?"saturated":"empty_population");});
    o.field("bins",[&]{w.array(v.bins,[&](auto n){w.number(n);});});
  });
}
void workload(Writer& w,const Report& report){
  const auto* snapshot=report.combined()?&report.combined()->workload():nullptr;
  w.object([&](auto& o){o.text("availability",!snapshot?"runtime_released":name(snapshot->detail_availability()));
    o.field("stamp",[&]{if(snapshot)stamp(w,snapshot->stamp());else w.null();});
    o.field("pending",[&]{if(snapshot)w.boolean(snapshot->pending());else w.null();});
    o.field("value",[&]{if(!snapshot || snapshot->options().mode==ws::Mode::off){w.null();return;}const auto& v=*snapshot;
      w.object([&](auto& s){s.field("modes",[&]{mode_facts(w,v.modes());});s.field("metadata",[&]{metadata(w,v.metadata());});
        s.text("histogram_bins","0=zero; b=1..64 covers [2^(b-1),2^b-1]");s.text("sampling","deterministic_complete_samples_no_population_extrapolation");
        s.field("cells",[&]{std::size_t i=0;w.array(v.descriptors(),[&](const auto& d){const auto index=i++;w.object([&](auto& x){x.number("id",index);
          x.field("descriptor",[&]{descriptor(w,d);});x.field("observations",[&]{cell(w,v.cells()[index],d,v.metadata().saturated);});
          const auto clipped=v.metadata().saturated || v.cells()[index].saturated;
          x.field("input_share",[&]{fraction(w,v.input_share(index),clipped);});x.field("events_per_input",[&]{fraction(w,v.events_per_physical_input(index),clipped);});
          x.field("crossing_fraction",[&]{fraction(w,v.crossing_fraction(index),clipped);});x.field("adapter_selectivity",[&]{fraction(w,v.adapter_selectivity(index),clipped);});
        });});});
        s.boolean("replaced_history",v.replaced_history());s.field("previous",[&]{if(!v.has_previous()){w.null();return;}
          w.object([&](auto& p){p.number("start_epoch",v.previous_interval_start_epoch());p.number("end_epoch",v.previous_interval_end_epoch());
            p.field("modes",[&]{mode_facts(w,v.previous_modes());});p.field("metadata",[&]{metadata(w,v.previous_metadata());});
            p.text("scope","previous_segment_raw_observations_no_derived_ratios");p.field("cells",[&]{std::size_t i=0;w.array(v.previous_cells(),[&](const auto& value){cell(w,value,v.descriptors()[i++],v.previous_metadata().saturated);});});
          });});
        s.field("memory",[&]{const auto& m=v.memory();w.object([&](auto& a){
#define M(member) a.number(#member,m.member)
          M(object_bytes);M(descriptors_bytes);M(routes_bytes);M(committed_bytes);M(attempt_bytes);M(previous_bytes);M(retained_payload_bytes);
#undef M
        });});s.null("arrival_per_second");s.text("arrival_reason","no_clock_measurement");
      });
    });
  });
}
void render(Writer& w,const Report& r){
  w.object([&](auto& o){o.number("schema_version",Report::schema_version);o.text("scope","owner_statistics_with_current_and_begin_bound_mode_context");
    o.field("capabilities",[&]{w.object([&](auto& c){c.text("cost_selection","not_implemented");c.null("estimated_total_state_bytes");c.boolean("global_cost_optimality",false);c.text("structural_proof","not_added_by_statistics");});});
    o.field("plan",[&]{w.object([&](auto& p){p.text("physical_sha256",r.plan().physical_sha256());p.number("checked_native_height",*r.plan().validation().native_height);
      p.text("route",name(r.plan().route()));p.text("authority","native_admitted_plan; identity_is_not_import_or_proof_authority");});});
    const auto& mode=r.mode();o.field("boundary",[&]{w.object([&](auto& b){b.text("presence",name(mode.presence()));b.number("owner",mode.owner());b.number("committed_sequence",mode.sequence());
      b.field("delta_state",[&]{if(mode.state())w.text(name(*mode.state()));else w.null();});b.field("pending",[&]{if(r.combined())w.boolean(r.combined()->workload().pending());else w.null();});
      b.text("scope",mode.presence()==observability::RuntimePresence::released?"last_owner_metadata_runtime_released":"actual_owner_as_of_capture");});});
    o.field("mode",[&]{w.object([&](auto& m){m.field("requested",[&]{delta_options(w,*mode.options());});
      m.text("resolved_mode",name(mode.profile()->mode));m.text("resolved_completion",name(mode.profile()->completion));m.text("live_maintenance",name(mode.profile()->live_maintenance));m.text("view",name(mode.profile()->view));});});
    o.field("session",[&]{if(!r.session()){w.null();return;}const auto& s=*r.session();w.object([&](auto& x){x.text("state",name(s.state));x.text("phase",name(s.phase));
      x.number("committed_sequence",s.committed_sequence);x.field("pending_sequence",[&]{w.optional(s.pending_sequence);});x.number("pending_work",s.pending_work);x.number("output_remaining",s.output_remaining);
      x.boolean("input_failed",s.input_failed);x.boolean("end_of_input",s.end_of_input);x.field("pending_command_sequence",[&]{w.optional(s.pending_command_sequence);});
    });});
    o.field("o07",[&]{o07(w,r);});o.field("c01",[&]{w.object([&](auto& c){c.field("options",[&]{workload_options(w,r.workload_options());});
      c.text("options_scope",r.combined()?"actual_owner_configuration":"retained_last_configuration_runtime_released");
      c.field("state",[&]{state(w,r);});c.field("workload",[&]{workload(w,r);});
    });});
    o.field("comparison",[&]{if(!r.comparison()){w.null();return;}const auto& c=*r.comparison();w.object([&](auto& x){
      x.number("previous_owner",c.previous_owner);x.number("previous_sequence",c.previous_sequence);x.number("actual_owner",c.actual_owner);x.number("actual_sequence",c.actual_sequence);x.number("max_event_lag",c.max_event_lag);
      x.field("data",[&]{if(c.data)w.text(name(*c.data));else w.null();});x.field("data_reason",[&]{if(c.data)w.null();else w.text("runtime_released_or_previous_unavailable");});
      x.text("workload_configuration",name(c.configuration));x.text("workload_reset",name(c.reset));x.text("workload_segment",name(c.segment));
    });});
    o.field("accounting",[&]{w.object([&](auto& a){a.text("state","cumulative_accounted_component_payload; request_construction_allocator_cursor_plan_and_retention_excluded");
      a.text("workload","retained_vector_capacity_components; allocator_snapshot_configure_overlap_and_engine_storage_excluded");
      a.text("joint","numeric_snapshot_copies_and_fixed_joint_control_outside_state_limits");
      a.text("export","independent_complete_artifact_item_and_encoded_byte_caps; string_capacity_and_allocator_overhead_excluded");
    });});
  });
}
}
StatisticsText write_statistics_json(const Report& report,StatisticsTextLimits limits){Writer w{limits,{}};render(w,report);return std::move(w.result);}
StatisticsText write_statistics_text(const Report& report,StatisticsTextLimits limits){
  Writer w{limits,{}};w.raw("CROWN statistics report v3\nState populations and workload events have separate availability and freshness.\nAll native string values below are hexadecimal bytes. Cost ranking and total state bytes are unavailable.\n");
  render(w,report);w.raw("\n");return std::move(w.result);
}
}

