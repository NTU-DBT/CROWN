#include "crown/io/query_explain.hpp"
#include "crown/api/error.hpp"
#include <charconv>
#include <type_traits>
#include <utility>
namespace crown::io {
namespace {
using namespace planner;using namespace observability;
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
// Private text buffer: encoded length is capped, allocator capacity is separate.
// Failure publishes no partial artifact and never advances the typed producer.
struct Writer {
  std::string out;
  std::size_t limit;
  explicit Writer(std::size_t bytes):limit(bytes) {}
  void raw(std::string_view value) {
    if (out.size()>limit || value.size()>limit-out.size()) throw Error("resource_limit","EXPLAIN encoded-byte limit exceeded");
    out.append(value);
  }
  void quote(std::string_view value,bool dot=false) {
    if(value.size()>limit-out.size()) throw Error("resource_limit","query EXPLAIN text exceeds encoded limit");
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
const char* name(QueryExplainSource v){switch(v){case QueryExplainSource::exact_search:return "exact_search";case QueryExplainSource::certificate_replay:return "certificate_replay";case QueryExplainSource::checked_upper:return "checked_upper";case QueryExplainSource::verified_optimum:return "verified_optimum";case QueryExplainSource::verified_infeasible:return "verified_infeasible";case QueryExplainSource::checked_certificate:return "checked_certificate";}throw Error("query_explain_enum","unknown report enum");}
const char* name(QueryHeightStatus v){switch(v){case QueryHeightStatus::unknown:return "unknown";case QueryHeightStatus::owner_checked_upper_unpublished:return "owner_checked_upper_unpublished";case QueryHeightStatus::checked_upper:return "checked_upper";case QueryHeightStatus::verified_optimum:return "verified_optimum";case QueryHeightStatus::verified_infeasible:return "verified_infeasible";}throw Error("query_explain_enum","unknown report enum");}
const char* name(SearchPolicy v){switch(v){case SearchPolicy::strict:return "strict";case SearchPolicy::best_found:return "best_found";}throw Error("query_explain_enum","unknown report enum");}
const char* name(NodeKind v){switch(v){case NodeKind::native:return "native";case NodeKind::generalized:return "generalized";}throw Error("query_explain_enum","unknown report enum");}
const char* name(BoundEvidence v){switch(v){case BoundEvidence::universal:return "universal";case BoundEvidence::independently_checked:return "independently_checked";}throw Error("query_explain_enum","unknown report enum");}
const char* name(ResultKind v){switch(v){case ResultKind::unfinished:return "unfinished";case ResultKind::verified_optimum:return "verified_optimum";case ResultKind::verified_infeasible:return "verified_infeasible";case ResultKind::failed:return "failed";}throw Error("query_explain_enum","unknown report enum");}
const char* name(SearchPhase v){switch(v){case SearchPhase::admitted:return "admitted";case SearchPhase::preprocess:return "preprocess";case SearchPhase::search:return "search";case SearchPhase::build_incumbent:return "build_incumbent";case SearchPhase::validate_incumbent:return "validate_incumbent";case SearchPhase::export_proof:return "export_proof";case SearchPhase::replay:return "replay";case SearchPhase::complete:return "complete";case SearchPhase::failed:return "failed";case SearchPhase::cancelled:return "cancelled";case SearchPhase::moved_from:return "moved_from";}throw Error("query_explain_enum","unknown report enum");}
const char* name(ReplayPhase v){switch(v){case ReplayPhase::admitted:return "admitted";case ReplayPhase::dispatch:return "dispatch";case ReplayPhase::validate_upper:return "validate_upper";case ReplayPhase::build_scopes:return "build_scopes";case ReplayPhase::classify_scope_orbits:return "classify_scope_orbits";case ReplayPhase::index_claims:return "index_claims";case ReplayPhase::order_claims:return "order_claims";case ReplayPhase::prove_claim:return "prove_claim";case ReplayPhase::match_root:return "match_root";case ReplayPhase::complete:return "complete";case ReplayPhase::failed:return "failed";case ReplayPhase::cancelled:return "cancelled";case ReplayPhase::moved_from:return "moved_from";}throw Error("query_explain_enum","unknown report enum");}
const char* name(StopReason v){switch(v){case StopReason::none:return "none";case StopReason::quantum_work:return "quantum_work";case StopReason::quantum_time:return "quantum_time";case StopReason::total_work:return "total_work";case StopReason::total_time:return "total_time";case StopReason::depth_limit:return "depth_limit";case StopReason::allocation_failure:return "allocation_failure";case StopReason::counter_overflow:return "counter_overflow";case StopReason::invalid_quantum:return "invalid_quantum";case StopReason::invalid_certificate:return "invalid_certificate";case StopReason::internal_failure:return "internal_failure";case StopReason::complete:return "complete";case StopReason::cancelled:return "cancelled";case StopReason::moved_from:return "moved_from";}throw Error("query_explain_enum","unknown report enum");}
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
void statistics(Writer& w,const SearchStatistics& s){w.object([&](auto& o){o.number("work",s.work);o.number("states",s.states);o.number("partitions",s.partitions);o.number("candidates",s.candidates);o.number("cache_hits",s.cache_hits);o.number("certificate_work",s.certificate_work);o.number("hierarchy_tests",s.hierarchy_tests);o.number("hierarchy_hits",s.hierarchy_hits);o.number("singleton_hits",s.singleton_hits);o.number("empty_body_hits",s.empty_body_hits);o.number("component_splits",s.component_splits);o.number("symmetry_skips",s.symmetry_skips);o.number("bound_prunes",s.bound_prunes);});}

void decimal(Writer& w,const std::optional<DecimalSpec>& d){if(!d){w.null();return;}w.object([&](auto& o){o.number("precision",d->precision);o.number("scale",d->scale);});}
void catalog(Writer& w,const Catalog& c){w.object([&](auto& o){o.number("version",c.version);o.field("tables",[&]{w.array(c.tables,[&](const Table& t){w.object([&](auto& x){
 x.text("name",t.name);x.number("source_schema_version",t.source_schema_version);
 x.field("columns",[&]{w.array(t.columns,[&](const Column& col){w.object([&](auto& a){a.text("name",col.name);a.text("type",type_name(col.type));a.boolean("nullable",col.nullable);a.text("collation",col.collation==Collation::binary?"binary":"unknown");a.field("decimal",[&]{decimal(w,col.decimal);});});});});
 x.field("constraints",[&]{w.array(t.constraints,[&](const Constraint& constraint){std::visit([&](const auto& a){w.object([&](auto& b){
 using T=std::decay_t<decltype(a)>;b.text("kind",std::is_same_v<T,UniqueConstraint>?"unique":"foreign_key");b.text("name",a.name);b.text("status",a.status==ConstraintStatus::enforced?"enforced":"untrusted");b.field("columns",[&]{w.ids(a.columns);});
 if constexpr(std::is_same_v<T,ForeignKeyConstraint>){b.number("referenced_table",a.referenced_table.value);b.field("referenced_columns",[&]{w.ids(a.referenced_columns);});}
 });},constraint);});});
 x.field("statistics",[&]{w.object([&](auto& a){a.field("row_count",[&]{w.optional(t.statistics.row_count);});a.field("distinct_counts",[&]{w.array(t.statistics.distinct_counts,[&](const auto& d){w.object([&](auto& b){b.field("columns",[&]{w.ids(d.columns);});b.number("estimate",d.estimate);});});});});});
 x.field("key_hints",[&]{w.array(t.key_hints,[&](const auto& hint){w.object([&](auto& a){a.field("columns",[&]{w.ids(hint.columns);});a.text("reason",hint.reason);});});});
 });});});});}
void query(Writer& w,const Query& q){w.object([&](auto& o){o.boolean("contradiction",q.contradiction);
 o.field("variables",[&]{w.array(q.variables,[&](const Variable& v){w.object([&](auto& a){a.text("name",v.name);a.text("type",type_name(v.type));});});});
 o.field("atoms",[&]{w.array(q.atoms,[&](const Atom& atom){w.object([&](auto& a){a.text("occurrence",atom.occurrence);a.number("table",atom.table.value);a.field("terms",[&]{w.array(atom.terms,[&](const Term& t){term(w,t);});});});});});
 o.field("head",[&]{w.array(q.head,[&](const Output& out){w.object([&](auto& a){a.number("variable",out.variable.value);a.text("alias",out.alias);});});});
 });}
// Diagnostic text preserves the original binding; it cannot create that authority.
void binding(Writer& w,const SearchBinding& b){w.object([&](auto& o){o.field("catalog",[&]{catalog(w,b.catalog());});o.field("query",[&]{query(w,b.query());});});}
void tree(Writer& w,const FreeConnexTree& t){w.object([&](auto& o){
 o.field("root",[&]{if(t.root)w.number(t.root->value);else w.null();});
 o.field("claimed_connex",[&]{if(t.claimed_connex)w.ids(*t.claimed_connex);else w.null();});o.field("claimed_native_height",[&]{w.optional(t.claimed_native_height);});
 o.field("nodes",[&]{w.array(t.nodes,[&](const TreeNode& node){w.object([&](auto& n){n.text("id",node.id);n.text("kind",name(node.kind));n.field("scope",[&]{w.ids(node.scope);});n.field("children",[&]{w.ids(node.children);});n.field("occurrence",[&]{w.optional(node.occurrence);});n.field("claimed_separator",[&]{if(node.claimed_separator)w.ids(*node.claimed_separator);else w.null();});});});});
 });}
void counters(Writer& w,const WorkCounters& c){w.object([&](auto& o){
 o.number("attempted",c.attempted);o.number("committed_transitions",c.committed_transitions);o.number("allocation_failures",c.allocation_failures);o.number("active_nanoseconds",c.active_nanoseconds);o.boolean("active_nanoseconds_at_cap",c.active_nanoseconds==UINT64_MAX);o.number("current_depth",c.current_depth);o.number("peak_depth",c.peak_depth);
 });}
void phase_limit(Writer& w,const PhaseCeiling& p){w.object([&](auto& o){o.field("work",[&]{w.optional(p.work);});o.field("active_nanoseconds",[&]{if(p.active_time)w.number(p.active_time->count());else w.null();});});}
void search(Writer& w,const QueryExplanation& e){if(!e.search_progress()){w.null();return;}const auto& p=*e.search_progress();w.object([&](auto& o){
 o.text("policy",name(*e.policy()));o.text("phase",name(p.phase));o.text("recorded_last_stop",name(p.last_stop));o.text("result_kind",name(p.result));
 o.text("stop_scope","owner_last_stop; nonmutating_zero_quantum_return_is_not_retained");
 o.field("observed_height_interval",[&]{w.object([&](auto& a){a.field("lower",[&]{w.optional(p.heights.lower);});a.field("upper",[&]{w.optional(p.heights.upper);});a.text("lower_evidence",name(p.heights.lower_evidence));a.boolean("infeasible",p.heights.infeasible);});});
 o.boolean("producer_complete",p.producer_complete);o.boolean("proof_complete",p.proof_complete);o.number("limit_revision",p.limit_revision);
 o.field("producer",[&]{counters(w,p.producer);});o.field("replay",[&]{counters(w,p.replay);});o.field("structural_counters",[&]{statistics(w,p.structural);});
 o.field("limits",[&]{const auto& l=*e.search_limits();w.object([&](auto& a){a.field("producer",[&]{phase_limit(w,l.producer);});a.field("replay",[&]{phase_limit(w,l.replay);});a.field("logical_depth",[&]{w.optional(l.logical_depth);});});});
 });}
void replay(Writer& w,const QueryExplanation& e){if(!e.replay_progress()){w.null();return;}const auto& p=*e.replay_progress();w.object([&](auto& o){
 o.text("phase",name(p.phase));o.text("recorded_last_stop",name(p.last_stop));o.boolean("complete",p.complete);o.boolean("valid",p.valid);o.number("checked_claims",p.checked_claims);o.number("limit_revision",p.limit_revision);o.field("work",[&]{counters(w,p.work);});
 o.text("claim_scope","unchecked_input_claim_details_not_exposed_until_checked_handle");o.text("stop_scope","owner_last_stop; nonmutating_zero_quantum_return_is_not_retained");
 o.field("limits",[&]{const auto& l=*e.replay_limits();w.object([&](auto& a){a.field("phase",[&]{phase_limit(w,l.limits);});a.field("logical_depth",[&]{w.optional(l.logical_depth);});});});
 });}
// Observed upper, published checked witness and independently proved minimum
// are distinct. An unpublished strict-search upper cannot authorize tree export.
void height(Writer& w,const QueryExplanation& e){w.object([&](auto& o){
 o.text("status",name(e.height_status()));o.field("lower",[&]{w.optional(e.lower());});o.field("upper",[&]{w.optional(e.upper());});
 o.text("lower_evidence",e.optimum()||e.infeasibility()?"typed_independent_proof":"p06_universal_nonempty_or_empty_body_bound");
 o.text("upper_evidence",e.witness()?"typed_checked_original_witness":e.upper()?"owner_observed_checked_upper_witness_unpublished":"none");
 o.boolean("minimum_proven",e.optimum().has_value());o.boolean("infeasible_proven",e.infeasibility().has_value());o.boolean("witness_exportable",e.witness().has_value());
 });}
void witness(Writer& w,const QueryExplanation& e){if(!e.witness()){w.null();return;}w.object([&](auto& o){o.text("authority","typed_validated_incumbent_exact_original_binding");o.number("height",e.witness()->height());o.field("tree",[&]{tree(w,e.witness()->tree());});});}
void certificate(Writer& w,const QueryExplanation& e){const auto* p=e.certificate();if(!p){w.null();return;}w.object([&](auto& o){
 o.text("authority","typed_independently_checked_original_binding");o.text("algorithm",p->algorithm);o.field("minimum_height",[&]{w.optional(p->minimum_height);});o.field("tree",[&]{if(p->tree)tree(w,*p->tree);else w.null();});
 o.field("lower_bounds",[&]{w.array(p->lower_bounds,[&](const LowerBoundEntry& c){w.object([&](auto& a){a.field("occurrences",[&]{w.array(c.occurrences,[&](auto id){w.number(id);});});a.boolean("generalized_allowed",c.generalized_allowed);a.boolean("connex_reachable",c.connex_reachable);a.field("bound",[&]{w.optional(c.bound);});});});});
 });}
void report(Writer& w,const QueryExplanation& e){w.object([&](auto& o){
 o.text("format","crown_query_explain");o.number("version",1);o.text("source",name(e.source()));o.text("accounting","continuation_v1");
 o.field("binding",[&]{binding(w,e.binding());});o.field("height",[&]{height(w,e);});o.field("search",[&]{search(w,e);});o.field("replay",[&]{replay(w,e);});
 o.field("witness",[&]{witness(w,e);});o.field("certificate",[&]{certificate(w,e);});
 o.field("recognized_class",[&]{w.object([&](auto& a){a.text("status","not_collected");a.number("diagnostic_work",0);a.text("reason","capture_does_not_run_recognizer_or_reclassify_producer_statistics");});});
 o.field("cost",[&]{w.object([&](auto& a){a.text("status","not_run");a.null("estimates");a.text("statistics","not_collected");a.text("catalog_estimates","original_input_metadata_only");a.null("candidate_family_exhaustion");});});
 o.text("active_time_semantics","producer_recorded_active_time_excludes_pause; UINT64_MAX_may_be_capped_not_exact");
 o.text("proof_scope","original_structural_height_only; no_cost_optimum_runtime_or_durable_guarantee");
 o.text("structural_domain","original_CQ_atom_head_tree_family; contradiction_metadata_preserved; excludes_P08_constant_false_operator_shortcut");
 o.text("counter_scopes","producer_and_replay_attempted_are_separate_phases; structural.work_aliases_producer.attempted; structural.certificate_work_aliases_replay.attempted; transitions_not_additive_work");
 });}
// A bound alone is insufficient: both tree transports require this typed owner.
const ValidatedIncumbent& need_witness(const QueryExplanation& e){if(!e.witness())throw Error("query_explain_no_witness","no published typed checked witness for tree export");return *e.witness();}
} // namespace
std::string write_query_explain_json(const QueryExplanation& e,QueryExplainTextLimits limits){Writer w(limits.bytes);report(w,e);return std::move(w.out);}
std::string write_query_explain_tree_json(const QueryExplanation& e,QueryExplainTextLimits limits){const auto& upper=need_witness(e);Writer w(limits.bytes);w.object([&](auto& o){o.text("format","crown_query_witness");o.number("version",1);o.text("authority","typed_checked_original_witness");o.number("height",upper.height());o.field("binding",[&]{binding(w,e.binding());});o.field("tree",[&]{tree(w,upper.tree());});});return std::move(w.out);}
std::string write_query_explain_text(const QueryExplanation& e,QueryExplainTextLimits limits){Writer w(limits.bytes);
 w.raw("Query EXPLAIN — ");w.raw(name(e.source()));w.raw("\nStructural height: ");w.raw(name(e.height_status()));w.raw("; lower=");w.optional(e.lower());w.raw(" upper=");w.optional(e.upper());w.raw("\n");
 if(e.search_progress()){const auto& p=*e.search_progress();w.raw("Search policy: ");w.raw(name(*e.policy()));w.raw("; phase=");w.raw(name(p.phase));w.raw("; recorded stop=");w.raw(name(p.last_stop));w.raw("\nProducer attempted work: ");w.number(p.producer.attempted);w.raw("; replay attempted work: ");w.number(p.replay.attempted);w.raw("\nSearch detail: ");search(w,e);w.raw("\n");}
 if(e.replay_progress()){w.raw("Replay detail: ");replay(w,e);w.raw("\n");}
 w.raw("Checked witness: ");if(e.witness()){w.number(e.witness()->tree().nodes.size());w.raw(" nodes; original checked upper");}else w.raw("not published; tree export unavailable");w.raw("\n");
 w.raw("Independent minimum proof: ");w.raw(e.optimum()?"present":"absent");w.raw("; independent infeasibility proof: ");w.raw(e.infeasibility()?"present":"absent");w.raw("\n");
 if(e.certificate()){w.raw("Certificate algorithm: ");w.quote(e.certificate()->algorithm);w.raw("; checked lower-bound entries: ");w.number(e.certificate()->lower_bounds.size());w.raw("\n");}
 w.raw("Structural proof domain: original CQ atom/head tree family; a nonempty contradiction-marked query keeps P06 lower 1, distinct from P08 constant_false operator height 0.\n");
 w.raw("Recognized class: not collected (no recognizer or search advancement).\nCost/ranking/statistics: unavailable; catalog estimates are input metadata only.\nRuntime plan, indices, cursor mode and durable guarantees: not available from this query-search artifact.\nRecorded last stop excludes nonmutating zero-quantum return reasons.\nExact original binding: ");binding(w,e.binding());w.raw("\n");return std::move(w.out);
}
std::string write_query_explain_dot(const QueryExplanation& e,QueryExplainTextLimits limits){const auto& upper=need_witness(e);const auto& t=upper.tree();Writer w(limits.bytes);w.raw("digraph checked_query_witness {\n  label=\"original checked witness; height ");w.number(upper.height());w.raw("\";\n");
 for(std::size_t i=0;i<t.nodes.size();++i){const auto& n=t.nodes[i];w.raw("  n");w.number(i);w.raw(" [label=");w.quote(n.id,true);w.raw(", shape=");w.raw(n.kind==NodeKind::native?"box":"ellipse");w.raw("];\n");for(const auto child:n.children){w.raw("  n");w.number(i);w.raw(" -> n");w.number(child.value);w.raw(";\n");}}
 w.raw("}\n");return std::move(w.out);
}
} // namespace crown::io
