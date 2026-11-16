#include "crown/io/explain.hpp"
#include "crown/api/error.hpp"
#include <charconv>
#include <limits>
#include <type_traits>
#include <utility>

namespace crown::io {
namespace {
using observability::PlanExplanation;
using namespace runtime;
void utf8(std::string_view text) {
  for (std::size_t i=0;i<text.size();) {
    const auto first=static_cast<unsigned char>(text[i++]);
    if (first<0x80) continue;
    unsigned remaining=0; std::uint32_t code=0,minimum=0;
    if (first>=0xc2 && first<=0xdf) { remaining=1; code=first&0x1fU; minimum=0x80; }
    else if (first>=0xe0 && first<=0xef) { remaining=2; code=first&0x0fU; minimum=0x800; }
    else if (first>=0xf0 && first<=0xf4) { remaining=3; code=first&0x07U; minimum=0x10000; }
    else throw Error("text_encoding","EXPLAIN text requires valid UTF-8; native values are unchanged");
    if (remaining>text.size()-i) throw Error("text_encoding","truncated UTF-8 in EXPLAIN text");
    while (remaining--) {
      const auto next=static_cast<unsigned char>(text[i++]);
      if ((next&0xc0U)!=0x80U) throw Error("text_encoding","invalid UTF-8 continuation in EXPLAIN text");
      code=(code<<6U)|(next&0x3fU);
    }
    if (code<minimum || code>0x10ffff || (code>=0xd800 && code<=0xdfff))
      throw Error("text_encoding","non-scalar UTF-8 in EXPLAIN text");
  }
}
struct Writer {
  std::string out;
  std::size_t limit;
  explicit Writer(std::size_t bytes):limit(bytes) {}
  void raw(std::string_view value) {
    if (out.size()>limit || value.size()>limit-out.size()) throw Error("resource_limit","EXPLAIN encoded-byte limit exceeded");
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
#define CASE(Type,Item) case Type::Item: return #Item
const char* name(PhysicalRoute value) {
  switch (value) { CASE(PhysicalRoute,tree); CASE(PhysicalRoute,constant_true); CASE(PhysicalRoute,constant_false); }
  throw Error("explain_enum","unknown physical route");
}
const char* name(NodeKind value) {
  switch (value) { CASE(NodeKind,native); CASE(NodeKind,generalized); }
  throw Error("explain_enum","unknown node kind");
}
const char* name(DeltaMode value) { switch(value) { CASE(DeltaMode,maintenance); CASE(DeltaMode,delta); } throw Error("explain_enum","unknown delta mode"); }
const char* name(LiveMaintenance value) { switch(value) { CASE(LiveMaintenance,on_output); CASE(LiveMaintenance,incremental); CASE(LiveMaintenance,eager); } throw Error("explain_enum","unknown live mode"); }
const char* name(DeltaCompletion value) { switch(value) { CASE(DeltaCompletion,automatic); CASE(DeltaCompletion,ordered_replay); CASE(DeltaCompletion,anchored); CASE(DeltaCompletion,root_first); } throw Error("explain_enum","unknown completion"); }
const char* name(ResultView value) { switch(value) { CASE(ResultView,core); CASE(ResultView,sql); } throw Error("explain_enum","unknown result view"); }
const char* name(PropagationOrder value) { switch(value) { CASE(PropagationOrder,fifo); CASE(PropagationOrder,lifo); } throw Error("explain_enum","unknown propagation order"); }
const char* name(ObservationMode value) { switch(value) { CASE(ObservationMode,off); CASE(ObservationMode,counters); CASE(ObservationMode,timed); CASE(ObservationMode,trace); } throw Error("explain_enum","unknown observation mode"); }
const char* name(DeltaState value) {
  switch(value) { CASE(DeltaState,ready); CASE(DeltaState,pending_delta); CASE(DeltaState,paused); CASE(DeltaState,draining); CASE(DeltaState,epoch_prepared); CASE(DeltaState,committed_output); CASE(DeltaState,committed); CASE(DeltaState,aborted); }
  throw Error("explain_enum","unknown delta state");
}
const char* name(ObservationLayer value) { switch(value) { CASE(ObservationLayer,support); CASE(ObservationLayer,physical); CASE(ObservationLayer,delta); } throw Error("explain_enum","unknown observation layer"); }
const char* name(ObservationOutcome value) { switch(value) { CASE(ObservationOutcome,pending); CASE(ObservationOutcome,committed); CASE(ObservationOutcome,aborted); } throw Error("explain_enum","unknown observation outcome"); }
const char* name(MetricAvailability value) { switch(value) { CASE(MetricAvailability,unavailable); CASE(MetricAvailability,disabled); CASE(MetricAvailability,available); } throw Error("explain_enum","unknown metric availability"); }
const char* name(MetricKind value) { switch(value) { CASE(MetricKind,counter); CASE(MetricKind,high_water); CASE(MetricKind,timing); } throw Error("explain_enum","unknown metric kind"); }
const char* name(TraceDisposition value) {
  switch(value) { CASE(TraceDisposition,disabled); CASE(TraceDisposition,not_sampled); CASE(TraceDisposition,pending); CASE(TraceDisposition,committed); CASE(TraceDisposition,aborted); CASE(TraceDisposition,released); }
  throw Error("explain_enum","unknown trace disposition");
}
const char* name(planner::CandidateSource value) { switch(value) { CASE(planner::CandidateSource,exact_witness); CASE(planner::CandidateSource,residual_seed); CASE(planner::CandidateSource,normal_form); } throw Error("explain_enum","unknown candidate source"); }
#undef CASE
const char* height_status(const PlanExplanation& report) { return report.height_status()==observability::HeightStatus::verified_original_minimum?"verified_original_minimum":"checked_upper"; }
void scalar(Writer& w,const Value& value) {
  w.object([&](auto& o) {
    o.text("type",type_name(type_of(value)));
    o.field("value",[&] { std::visit([&](const auto& item) {
      using T=std::decay_t<decltype(item)>;
      if constexpr(std::is_same_v<T,std::int64_t>) w.number(item);
      else if constexpr(std::is_same_v<T,bool>) w.boolean(item);
      else if constexpr(std::is_same_v<T,std::string>) w.quote(item);
      else w.quote(item.to_string());
    },value); });
  });
}
void term(Writer& w,const Term& value) {
  w.object([&](auto& o) {
    if (const auto* variable=std::get_if<VariableId>(&value)) { o.text("kind","variable"); o.number("variable",variable->value); }
    else if (const auto* constant=std::get_if<Value>(&value)) { o.text("kind","constant"); o.field("constant",[&] { scalar(w,*constant); }); }
    else o.text("kind","ignored_column");
  });
}
void tree(Writer& w,const FreeConnexTree& value,const planner::ValidationReport* validation=nullptr) {
  // Diagnostic scratch is linear in the admitted tree size. Do not scan C*
  // afresh for each node: large validated trees must not become quadratic IO.
  std::vector<bool> connex;
  if (validation) {
    connex.resize(value.nodes.size());
    for (const auto id:validation->maximal_connex) connex.at(id.value)=true;
  }
  w.object([&](auto& o) {
    o.field("root",[&] { if (value.root) w.number(value.root->value); else w.null(); });
    o.field("nodes",[&] {
      std::size_t index=0;
      w.array(value.nodes,[&](const TreeNode& node) {
        const auto id=index++;
        w.object([&](auto& n) {
          n.number("id",id); n.text("label",node.id); n.text("kind",name(node.kind));
          n.field("occurrence",[&] { w.optional(node.occurrence); });
          n.field("scope",[&] { w.ids(node.scope); }); n.field("children",[&] { w.ids(node.children); });
          n.field("separator",[&] { if (validation) w.ids(validation->separators.at(id)); else w.null(); });
          n.field("connex",[&] {
            if (!validation) { w.null(); return; }
            w.boolean(connex.at(id));
          });
        });
      });
    });
  });
}
void profile(Writer& w,const DeltaRuntimeProfile& p) {
  w.object([&](auto& o) {
    o.text("semantics",p.semantics); o.text("query_class",p.query_class); o.text("arithmetic",p.arithmetic);
    o.text("backend",p.backend); o.text("update_contract",p.update_contract);
    o.text("state_bound",p.state_bound); o.text("maintenance_bound",p.maintenance_bound); o.text("preparation_bound",p.preparation_bound);
    o.text("candidate_bound",p.candidate_bound); o.text("accepted_bound",p.accepted_bound); o.text("finalization_bound",p.finalization_bound);
    o.text("public_startup_bound",p.public_startup_bound); o.boolean("public_first_record_constant_delay",p.public_first_record_constant_delay);
    o.text("ordered_costs",p.ordered_costs); o.text("assumptions",p.assumptions); o.text("output_accounting",p.output_accounting);
  });
}
void mode(Writer& w,const observability::ModeDescriptor& m) {
  w.object([&](auto& o) {
    o.text("scope",m.running()?"current_runtime_configuration":"compile_only");
    o.text("historical_metric_mode_binding","see_each_attempt_mode_binding");
    o.text("codec","external_unmeasured"); o.text("sink","external_unmeasured");
    o.text("retention_policy","per_attempt_not_recorded"); o.text("input_adapter","not_recorded");
    o.text("initialization_method","not_recorded"); o.text("durable_delivery","not_implemented");
    o.text("semantics",m.plan().guarantee().semantics); o.text("arithmetic",m.plan().guarantee().arithmetic);
    o.text("backend",m.plan().guarantee().storage_backend);
    if (!m.running()) { o.null("runtime"); return; }
    const auto& opts=*m.options(); const auto& p=*m.profile();
    o.field("runtime",[&] { w.object([&](auto& r) {
      r.number("owner",m.owner()); r.number("committed_sequence",m.sequence()); r.text("state",name(m.state()));
      r.text("mode",name(p.mode)); r.text("requested_initial_mode",name(opts.mode)); r.text("requested_completion",name(opts.completion)); r.text("resolved_completion",name(p.completion));
      r.text("live_maintenance",name(p.live_maintenance)); r.text("result_view",name(p.view));
      r.text("propagation",name(opts.physical.support.order)); r.text("observation",name(opts.physical.support.observation.mode));
      r.boolean("legacy_full_transition_capture",opts.physical.support.capture_transitions);
      r.field("observation_options",[&] { w.object([&](auto& a) {
        const auto& obs=opts.physical.support.observation;
        a.number("trace_capacity",obs.trace_capacity); a.number("sample_period",obs.sample_period); a.number("sample_offset",obs.sample_offset); a.boolean("trace_timings",obs.trace_timings);
      }); });
      r.field("limits",[&] { w.object([&](auto& l) {
        l.field("delta_work",[&] { w.optional(opts.work_limit); }); l.field("physical_work",[&] { w.optional(opts.physical.work_limit); });
        l.field("support_work",[&] { w.optional(opts.physical.support.work_limit); }); l.number("support_count",opts.physical.support.support_limit);
        l.number("derivation_count",opts.physical.derivation_limit); l.field("cursor_work",[&] { w.optional(opts.cursor.work_limit); });
        l.field("view_work",[&] { w.optional(opts.epoch_view.work_limit); });
        l.number("spool_rows",opts.spool_row_limit); l.number("spool_accounted_bytes",opts.spool_byte_limit);
      }); });
      r.field("guarantee",[&] { profile(w,p); });
    }); });
  });
}
[[maybe_unused]] void requested_options(Writer& w,const DeltaOptions& opts) {
  w.object([&](auto& o) {
    o.text("mode",name(opts.mode)); o.text("view",name(opts.view)); o.text("live_maintenance",name(opts.live_maintenance)); o.text("completion",name(opts.completion));
    o.field("work_limit",[&] { w.optional(opts.work_limit); });
    o.field("cursor_work_limit",[&] { w.optional(opts.cursor.work_limit); }); o.field("view_work_limit",[&] { w.optional(opts.epoch_view.work_limit); });
    o.number("spool_row_limit",opts.spool_row_limit); o.number("spool_byte_limit",opts.spool_byte_limit);
    o.field("physical",[&] { w.object([&](auto& p) {
      p.field("work_limit",[&] { w.optional(opts.physical.work_limit); }); p.number("derivation_limit",opts.physical.derivation_limit);
      p.field("support",[&] { w.object([&](auto& a) {
        const auto& support=opts.physical.support;
        a.field("work_limit",[&] { w.optional(support.work_limit); }); a.number("support_limit",support.support_limit);
        a.text("order",name(support.order)); a.boolean("capture_transitions",support.capture_transitions);
        a.field("observation",[&] { w.object([&](auto& v) {
          const auto& obs=support.observation;
          v.text("mode",name(obs.mode)); v.number("trace_capacity",obs.trace_capacity); v.number("sample_period",obs.sample_period);
          v.number("sample_offset",obs.sample_offset); v.boolean("trace_timings",obs.trace_timings);
        }); });
      }); });
    }); });
  });
}
template<class Configuration> void configuration(Writer& w,const Configuration& c) {
  w.object([&](auto& o) {
    o.number("format_version",c.format_version()); o.number("support_owner",c.support_owner());
    o.number("generation",c.generation()); o.boolean("generation_saturated",c.generation_saturated());
    o.text("mode",name(c.mode())); o.text("completion",name(c.completion()));
    o.text("live_maintenance",name(c.live_maintenance())); o.text("view",name(c.view())); o.number("query_factors",c.query_factors());
    o.field("requested_options",[&] { requested_options(w,c.requested_options()); });
    o.text("identity_scope","process_local_owner_generation; saturated_generation_is_not_unique");
    o.text("guarantee_prose","not_copied_from_current_profile");
  });
}
template<class Summary> bool mode_bound(const Summary& s) {
  if constexpr(requires { s.configuration; }) return s.configuration.has_value();
  else return false;
}
template<class Summary> void historical_mode(Writer& w,Writer::Object& o,const Summary& s) {
  o.text("mode_binding",mode_bound(s)?"exact_begin_configuration":"not_recorded");
  o.field("configuration",[&] {
    if constexpr(requires { s.configuration; }) { if (s.configuration) { configuration(w,*s.configuration); return; } }
    w.null();
  });
}
template<class Snapshot> void current_configuration(Writer& w,const Snapshot& snapshot) {
  if constexpr(requires { snapshot.current_configuration; }) {
    if (snapshot.current_configuration) { configuration(w,*snapshot.current_configuration); return; }
  }
  w.null();
}
void summary(Writer& w,const std::optional<ObservationSummary>& value) {
  if (!value) { w.null(); return; }
  w.object([&](auto& o) {
    o.number("attempt",value->attempt); o.number("sequence",value->sequence); o.text("owner_layer",name(value->owner)); o.text("outcome",name(value->outcome));
    historical_mode(w,o,*value);
    o.field("values",[&] { w.array(observation_registry(),[&](const auto& descriptor) {
      const auto& metric=value->metric(descriptor.id);
      w.object([&](auto& m) {
        m.number("id",static_cast<std::size_t>(descriptor.id)); m.text("availability",name(metric.availability));
        // An unavailable metric can retain a stale internal payload. It is not
        // a numeric report value and MUST NOT escape as a plausible total.
        if (metric.availability==MetricAvailability::available) { m.number("value",metric.value); m.boolean("saturated",metric.saturated); }
        else { m.null("value"); m.null("saturated"); }
      });
    }); });
  });
}
void observations(Writer& w,const PlanExplanation& report) {
  w.object([&](auto& o) {
    o.text("version","runtime-observation-v1");
    const auto& obs=report.observation();
    const bool collected=obs && obs->options.mode!=ObservationMode::off;
    o.text("availability",!obs?"unavailable":collected?"available":"disabled");
    o.text("scope","admitted_attempt; aborted values are attempted work, not committed changes");
    o.text("mode_binding","per_attempt_configuration_or_not_recorded"); o.boolean("mandatory_accounting",true);
    o.field("current_configuration",[&] { if (obs) current_configuration(w,*obs); else w.null(); });
    o.field("registry",[&] { w.array(observation_registry(),[&](const auto& d) { w.object([&](auto& entry) {
      entry.number("id",static_cast<std::size_t>(d.id)); entry.text("name",d.name); entry.text("unit",d.unit);
      entry.text("kind",name(d.kind)); entry.text("layer",name(d.layer)); entry.text("accounting",d.accounting);
      entry.text("scope",d.scope); entry.text("includes",d.includes);
    }); }); });
    o.field("current",[&] { if (obs) summary(w,obs->current); else w.null(); });
    o.field("last",[&] { if (obs) summary(w,obs->last); else w.null(); });
    o.field("lifetime",[&] {
      if (!collected) { w.null(); return; }
      w.object([&](auto& a) { a.number("attempts",obs->attempts); a.number("commits",obs->commits); a.number("aborts",obs->aborts); a.boolean("saturated",obs->lifetime_counts_saturated); });
    });
    o.field("trace",[&] {
      if (!obs) { w.null(); return; }
      w.object([&](auto& t) {
        t.text("disposition",name(obs->trace)); t.number("support_owner",obs->support_owner);
        t.number("attempt",obs->trace_attempt); t.number("sequence",obs->trace_sequence);
        t.number("retained_records",obs->trace_records); t.number("dropped_records",obs->trace_dropped);
        t.boolean("dropped_saturated",obs->trace_dropped_saturated); t.boolean("truncated",obs->trace_truncated);
        t.text("records","not_copied_by_explain");
      });
    });
  });
}
void query(Writer& w,const PhysicalPlan& plan) {
  const auto& q=plan.query();
  w.object([&](auto& o) {
    o.boolean("contradiction",q.contradiction);
    o.field("variables",[&] { std::size_t index=0; w.array(q.variables,[&](const auto& variable) { w.object([&](auto& v) { v.number("id",index++); v.text("name",variable.name); v.text("type",type_name(variable.type)); }); }); });
    o.field("occurrences",[&] { std::size_t index=0; w.array(q.atoms,[&](const auto& atom) { w.object([&](auto& a) {
      a.number("id",index++); a.text("name",atom.occurrence); a.number("table",atom.table.value);
      a.text("table_name",plan.catalog().tables.at(atom.table.value).name); a.field("terms",[&] { w.array(atom.terms,[&](const auto& t) { term(w,t); }); });
    }); }); });
    o.field("head",[&] { w.array(q.head,[&](const auto& output) { w.object([&](auto& a) { a.number("variable",output.variable.value); a.text("alias",output.alias); }); }); });
    o.field("sql",[&] {
      if (!plan.normalized()) { w.null(); return; }
      const auto& normalized=*plan.normalized();
      w.object([&](auto& a) {
        a.text("source",normalized.binding.source); a.text("wrapper",normalized.binding.wrapper==frontend::SqlWrapper::exists?"exists":"rows");
        a.field("parameters",[&] { w.array(normalized.parameters,[&](const auto& value) { if (value) scalar(w,*value); else w.null(); }); });
        a.field("outputs",[&] { w.array(normalized.outputs,[&](const auto& output) { w.object([&](auto& v) {
          v.text("name",output.name); v.text("type",frontend::sql_kind_name(output.type.kind));
          v.boolean("nullable",output.type.nullable);
          v.field("decimal",[&] { if (!output.type.decimal) { w.null(); return; }
            w.object([&](auto& d) { d.number("precision",output.type.decimal->precision); d.number("scale",output.type.decimal->scale); });
          });
          if (const auto* core=std::get_if<frontend::CoreOutput>(&output.value)) { v.text("kind","core_column"); v.number("column",core->column); }
          else { v.text("kind","constant"); v.field("constant",[&] { scalar(w,std::get<frontend::ConstantOutput>(output.value).value); }); }
        }); }); });
      });
    });
  });
}
void json(Writer& w,const PlanExplanation& e) {
  const auto& plan=e.plan();
  w.object([&](auto& o) {
    o.number("schema_version",1); o.text("artifact","crown_explain"); o.text("authority","diagnostic_export_only");
    o.field("identity",[&] { const auto& i=plan.identity(); w.object([&](auto& x) {
      x.text("physical_sha256",plan.physical_sha256()); x.text("semantic_sha256",i.semantic_sha256); x.text("output_contract_sha256",i.output_contract_sha256);
      x.text("cost_inputs_sha256",i.cost_inputs_sha256); x.text("plan_cache_sha256",i.plan_cache_sha256);
      x.number("core_catalog_version",plan.catalog().version); x.number("source_catalog_version",plan.source_catalog().version);
      x.text("binding_rule","exact_original_native_catalog_query; digests_are_navigation_only");
    }); });
    o.text("route",name(plan.route())); o.text("recognized_class",plan.guarantee().query_class);
    o.field("query",[&] { query(w,plan); });
    o.field("structure",[&] { w.object([&](auto& s) {
      s.text("validity_source",plan.route()==PhysicalRoute::constant_false?"p08_constant_operator":"p08_independently_validated_tree");
      s.number("native_height",e.selected_height()); s.field("edge_depth",[&] { w.optional(plan.validation().edge_depth); });
      s.field("selected_tree",[&] { tree(w,plan.tree(),&plan.validation()); });
    }); });
    o.field("height_evidence",[&] { w.object([&](auto& h) {
      h.text("status",height_status(e)); h.number("selected_height",e.selected_height());
      h.text("scope","original_core_query"); h.text("search_progress","not_attached");
      if (const auto original=e.optimum()) {
        const auto& cert=original->certificate();
        h.text("source",std::holds_alternative<planner::MinimumHeightCandidate>(e.evidence())?"p07_checked_candidate_with_original_p06_proof":"p06_verified_optimum");
        h.number("original_minimum",original->height()); h.text("algorithm",cert.algorithm);
        h.text("certificate_role","typed_handle_retained; diagnostic_not_certificate_input");
        h.field("original_witness",[&] { tree(w,original->upper().tree()); });
        h.field("lower_bound_claims",[&] { w.array(cert.lower_bounds,[&](const auto& claim) { w.object([&](auto& c) {
          c.field("occurrences",[&] { w.array(claim.occurrences,[&](auto id) { w.number(id); }); });
          c.boolean("generalized_allowed",claim.generalized_allowed); c.boolean("connex_reachable",claim.connex_reachable); c.field("bound",[&] { w.optional(claim.bound); });
        }); }); });
      } else { h.text("source","p08_checked_upper_only"); h.null("original_minimum"); h.null("algorithm"); h.null("original_witness"); h.null("lower_bound_claims"); h.text("certificate_role","none"); }
    }); });
    o.field("candidate_family",[&] {
      if (!e.family()) { w.null(); return; }
      const auto& f=*e.family();
      w.object([&](auto& c) { c.text("family","exact-seed/residual-seed/normal-form-v1"); c.boolean("exhausted",f.family_exhausted()); c.number("count",f.candidate_count()); c.text("exhaustion_scope","admitted_seeds_and_normal_form_v1_only"); c.boolean("global_cost_complete",false); });
    });
    o.field("selected_candidate",[&] {
      const auto* c=std::get_if<planner::MinimumHeightCandidate>(&e.evidence()); if (!c) { w.null(); return; }
      const auto provenance=c->provenance(); w.object([&](auto& a) {
        a.text("source",name(provenance.source)); a.number("sequence",provenance.sequence); a.text("structural_key",c->structural_key());
        a.text("key_scope","exact_binding_and_candidate_context_only");
      });
    });
    o.field("physical",[&] { w.object([&](auto& p) {
      p.field("policy",[&] { const auto& policy=plan.options().policy; w.object([&](auto& a) {
        a.text("arithmetic",policy.arithmetic); a.text("planner",policy.planner); a.text("optimization",policy.optimization); a.text("cost_model",policy.cost_model);
      }); });
      p.field("inputs",[&] { w.array(plan.inputs(),[&](const auto& input) { w.object([&](auto& i) {
        i.number("occurrence",input.occurrence.value); i.number("node",input.node.value); i.number("source_table",input.base.value);
        i.text("source_name",plan.source_catalog().tables.at(input.base.value).name); i.field("projection_fields",[&] { w.ids(input.projection.fields()); });
      }); }); });
      p.field("indexes",[&] { w.array(plan.indexes(),[&](const auto& index) { w.object([&](auto& i) {
        i.number("id",index.id.value); i.number("relation",index.relation.value); i.field("fields",[&] { w.ids(index.projection.fields()); });
        i.field("uses",[&] { w.array(index.uses,[&](auto use) { w.quote(use==IndexUse::reverse_child_support?"reverse_child_support":"visible_enumeration"); }); });
      }); }); });
      p.field("enumeration_nodes",[&] { w.array(plan.enumeration().steps,[&](const auto& step) { w.number(step.node.value); }); });
      p.text("enumeration","nary_visible_assignments"); p.number("enumeration_depth",plan.enumeration().depth);
      p.text("update_contract",plan.guarantee().update_contract); p.field("assumptions",[&] { w.array(plan.guarantee().assumptions,[&](const auto& item) { w.quote(item); }); });
    }); });
    o.field("cost",[&] { w.object([&](auto& c) { c.text("selection","not_implemented"); c.text("statistics","unavailable"); c.text("estimated_state","unavailable"); c.boolean("global_optimality",false); }); });
    o.field("mode",[&] { mode(w,e.mode()); });
    o.field("observations",[&] { observations(w,e); });
    o.field("open_gates",[&] { w.array(std::array{"S05_total_allocator_bytes","O04_checkpoint","O05_recovery","O06_durable_delivery","C01_statistics","C02_ranking","B03_benchmark","per_attempt_mode_generation"},[&](auto item) { w.quote(item); }); });
  });
}
void human_metrics(Writer& w,const char* label,const std::optional<ObservationSummary>& summary_value) {
  if (!summary_value) return;
  const auto& s=*summary_value;
  w.raw(label); w.raw(" attempt "); w.number(s.attempt); w.raw(", physical sequence "); w.number(s.sequence); w.raw(", "); w.raw(name(s.outcome)); w.raw(mode_bound(s)?". Historical mode: exact begin configuration.\n":". Historical mode: not recorded.\n");
  if (mode_bound(s)) { w.raw("  Historical configuration: "); w.object([&](auto& o) { historical_mode(w,o,s); }); w.raw("\n"); }
  for (const auto& d:observation_registry()) {
    const auto& m=s.metric(d.id); w.raw("  "); w.raw(d.name); w.raw(" = ");
    if (m.availability==MetricAvailability::available) { w.number(m.value); if (m.saturated) w.raw(" (saturated)"); }
    else w.raw(name(m.availability));
    w.raw(" ["); w.raw(d.unit); w.raw("; "); w.raw(d.accounting); w.raw("]");
    if (!d.includes.empty()) { w.raw(" "); w.raw(d.includes); } w.raw("\n");
  }
}
}
std::string write_explain_json(const PlanExplanation& report,ExplainTextLimits limits) { Writer w(limits.bytes); json(w,report); return std::move(w.out); }
std::string write_explain_text(const PlanExplanation& report,ExplainTextLimits limits) {
  Writer w(limits.bytes); const auto& plan=report.plan();
  w.raw("CROWN EXPLAIN v1 — diagnostic export, not proof input\nPhysical plan: "); w.raw(plan.physical_sha256());
  w.raw("\nSemantic/output identity: "); w.raw(plan.identity().semantic_sha256); w.raw(" / "); w.raw(plan.identity().output_contract_sha256);
  w.raw("\nRoute/class: "); w.raw(name(plan.route())); w.raw(" / "); w.quote(plan.guarantee().query_class);
  w.raw("\nHeight: "); w.number(report.selected_height()); w.raw(" ("); w.raw(height_status(report)); w.raw(")\n");
  if (const auto p=report.optimum()) { w.raw("Original-query proof: "); w.quote(p->certificate().algorithm); w.raw("; lower-bound claims "); w.number(p->certificate().lower_bounds.size()); w.raw("; certificate keeps its original witness.\nOriginal witness: "); tree(w,p->upper().tree()); w.raw("\n"); }
  else w.raw("Minimum height is not proved by the supplied plan.\n");
  w.raw("Cost selection: not implemented; statistics and estimated state unavailable.\n");
  if (report.family()) { w.raw("Candidate family: exact seeds/residual seeds/normal form; retained "); w.number(report.family()->candidate_count()); w.raw(report.family()->family_exhausted()?"; family exhausted":"; family not exhausted"); w.raw("; no global cost completeness.\n"); }
  w.raw("Occurrences:\n"); std::size_t id=0;
  for (const auto& atom:plan.query().atoms) { w.raw("  "); w.number(id++); w.raw(" "); w.quote(atom.occurrence); w.raw(" table "); w.quote(plan.catalog().tables.at(atom.table.value).name); w.raw(" "); w.array(atom.terms,[&](const auto& t) { term(w,t); }); w.raw("\n"); }
  w.raw("Ordered core head: "); w.array(plan.query().head,[&](const auto& output) { w.object([&](auto& a) { a.number("variable",output.variable.value); a.text("alias",output.alias); }); }); w.raw("\n");
  if (plan.normalized()) { w.raw("Normalized SQL/output mapping: "); query(w,plan); w.raw("\n"); }
  w.raw("Selected tree (scope/separator IDs; C* marks connex membership):\n");
  for (const auto& n:plan.nodes()) {
    w.raw("  n"); w.number(n.id.value); w.raw(" "); w.raw(name(n.kind)); w.raw(" "); w.quote(plan.tree().nodes.at(n.id.value).id);
    w.raw(" scope="); w.ids(n.scope); w.raw(" separator="); w.ids(plan.validation().separators.at(n.id.value)); w.raw(n.connex?" C*":""); w.raw(" children="); w.ids(n.children); w.raw("\n");
  }
  w.raw("Required indexes:\n"); for (const auto& index:plan.indexes()) { w.raw("  "); w.number(index.id.value); w.raw(" relation="); w.number(index.relation.value); w.raw(" fields="); w.ids(index.projection.fields()); w.raw("\n"); }
  w.raw("Enumeration: nary_visible_assignments; depth "); w.number(plan.enumeration().depth);
  w.raw("\nArithmetic/update contract: "); w.quote(plan.guarantee().arithmetic); w.raw(" / "); w.quote(plan.guarantee().update_contract);
  w.raw("\nMode descriptor: "); mode(w,report.mode()); w.raw("\n");
  if (report.observation()) {
    if (report.observation()->options.mode==ObservationMode::off) w.raw("Runtime observation disabled; mandatory accounting remains active.\n");
    human_metrics(w,"Current",report.observation()->current); human_metrics(w,"Last",report.observation()->last);
  }
  else w.raw("Runtime metrics unavailable: compile-only report.\n");
  w.raw("Metric scope: admitted attempt; aborted values are attempted work, not committed changes. Unavailable/disabled numeric payloads are omitted.\n");
  w.raw("Open: allocator-total bytes, durable delivery/recovery, statistics/ranking, benchmark validation, historical mode binding.\n");
  return std::move(w.out);
}
std::string write_explain_dot(const PlanExplanation& report,ExplainTextLimits limits) {
  Writer w(limits.bytes); const auto& plan=report.plan();
  w.raw("digraph crown {\n  graph [label=");
  Writer caption(limits.bytes); caption.raw("CROWN native height "); caption.number(report.selected_height()); caption.raw(" "); caption.raw(height_status(report));
  w.quote(caption.out,true); w.raw("];\n");
  for (const auto& node:plan.nodes()) {
    w.raw("  n"); w.number(node.id.value); w.raw(node.kind==NodeKind::native?" [shape=box,":" [shape=diamond,");
    if (node.connex) w.raw("style=filled,fillcolor=lightblue,");
    Writer label(limits.bytes); label.raw(plan.tree().nodes.at(node.id.value).id); label.raw(" scope="); label.ids(node.scope); if (node.connex) label.raw(" C*");
    w.raw("label="); w.quote(label.out,true); w.raw("];\n");
  }
  for (const auto& edge:plan.edges()) {
    w.raw("  n"); w.number(edge.parent.value); w.raw(" -> n"); w.number(edge.child.value); w.raw(" [label=");
    Writer label(limits.bytes); label.raw("separator="); label.ids(plan.validation().separators.at(edge.child.value)); w.quote(label.out,true); w.raw("];\n");
  }
  if (plan.nodes().empty()) { w.raw("  constant [shape=plaintext,label="); w.quote(name(plan.route())); w.raw("];\n"); }
  w.raw("}\n"); return std::move(w.out);
}
} // namespace crown::io
