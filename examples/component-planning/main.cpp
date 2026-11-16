#include <crown/api/error.hpp>
#include <crown/frontend/admission.hpp>
#include <crown/io/candidates.hpp>
#include <crown/io/catalog.hpp>
#include <crown/io/ingest.hpp>
#include <crown/io/physical.hpp>
#include <crown/io/residual.hpp>
#include <crown/ir/digest.hpp>
#include <crown/planner/lower.hpp>
#include <crown/planner/meta_candidates.hpp>
#include <crown/runtime/maintenance_cost.hpp>
#include <algorithm>
#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <limits>
#include <set>
#include <sstream>
#include <string>
#include <vector>

namespace {
using namespace crown;
using io::Json;
using U64=std::uint64_t;
using Clock=std::chrono::steady_clock;
namespace rank=planner::ranking;
namespace cost=runtime::cost;
namespace meta=planner::meta;

// This executable is a cold experiment exporter. It never installs a choice,
// opens held-out inputs, or adds clocks/hooks to production update primitives.
void require(bool value,std::string_view message) {
  if(!value)throw Error("component_planning_error",std::string(message));
}
std::string read(const char* path,std::size_t limit) {
  std::ifstream file(path,std::ios::binary);require(bool(file),"cannot open component input");
  std::string result;char block[4096];
  while(file) {
    file.read(block,sizeof(block));const auto count=static_cast<std::size_t>(file.gcount());
    require(count<=limit-result.size(),"component input byte grant exceeded");result.append(block,count);
  }
  require(!file.bad(),"component input read failed");return result;
}
U64 integer(const Json& value,U64 minimum,U64 maximum) {
  require(value.is_number_integer() && (value.is_number_unsigned() || value.get<std::int64_t>()>=0),"expected nonnegative integer");
  const auto result=value.get<U64>();require(result>=minimum && result<=maximum,"integer outside finite component grant");return result;
}
U64 grant(const Json& request,const char* key,U64 fallback,U64 minimum,U64 maximum) {
  return request.contains(key)?integer(request.at(key),minimum,maximum):fallback;
}
U64 elapsed(Clock::time_point begin,Clock::time_point end) {
  const auto count=std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
  require(count>=0,"component clock regressed");return static_cast<U64>(count);
}
template<class Text> std::string text(const Text& value) {return {value.data(),value.size()};}
Json ratio(const std::optional<cost::Ratio>& value) {
  return value?Json{{"numerator",value->numerator},{"denominator",value->denominator}}:Json(nullptr);
}
Json usage(const rank::Usage& value) {
  return {{"work",value.work},{"cells",value.cells},{"payload_bytes",value.payload_bytes},
    {"binding_key_bytes",value.binding_key_bytes},{"active_nanoseconds",value.active_nanoseconds},
    {"lowering_work",value.lowering_work},{"identity_work",value.identity_work},
    {"binding_replay_work",value.binding_replay_work},{"normalization_work",value.normalization_work}};
}
Json stamp(const runtime::workload::Stamp& value) {
  return {{"owner",value.owner.value},{"epoch",value.committed_epoch},{"interval_start",value.interval_start_epoch},
    {"reset",value.reset_generation},{"configuration",value.configuration_generation},{"segment",value.segment}};
}
Json modes(const runtime::workload::ModeFacts& value) {
  return {{"delta_owner",value.delta_owner},{"requested_mode",static_cast<unsigned>(value.requested_mode)},
    {"resolved_mode",static_cast<unsigned>(value.resolved_mode)},{"requested_completion",static_cast<unsigned>(value.requested_completion)},
    {"resolved_completion",static_cast<unsigned>(value.resolved_completion)},
    {"live_maintenance",static_cast<unsigned>(value.live_maintenance)},{"view",static_cast<unsigned>(value.view)}};
}

// All bounds are finite. Logical planner grants and native account bytes are
// different units; ordinary vector/JSON storage and admission remain explicit.
struct Request {
  PhysicalOptions physical;
  U64 search_work,enumeration_work,memory,event_limit,repetitions,sample_period,sample_offset,stale_prefix,meta_work,model_work;
  std::size_t candidates,calibration_plans,meta_outputs,depth;
  U64 records,cells;
  std::string context;
  rank::Limits model_limits() const {
    rank::Limits result;result.work=model_work;result.cells=cells;result.payload_bytes=64U*1024U*1024U;return result;
  }
  planner::CandidateLimits candidate_limits() const {
    planner::CandidateLimits result;result.enumeration.work=enumeration_work;result.retained_candidates=candidates;
    result.logical_depth=depth;result.records=records;result.cells=cells;return result;
  }
  runtime::DeltaOptions runtime_options() const {
    runtime::DeltaOptions result;result.mode=runtime::DeltaMode::maintenance;
    result.physical.support.memory_limit_bytes=memory;result.physical.support.observation.mode=runtime::ObservationMode::off;
    return result;
  }
};
Request parse_request(const Json& json) {
  const std::set<std::string> fields{"schema_version","physical_options","context","input_demand","search_work","enumeration_work",
    "candidate_limit","memory_limit_bytes","max_events","calibration_repetitions","calibration_plan_limit","sample_period",
    "sample_offset","stale_prefix_events","meta_work","meta_output_limit","depth_limit","record_limit","cell_limit","model_work","prior_calibration"};
  require(json.is_object(),"component request must be an object");
  for(const auto& field:json.items())require(fields.contains(field.key()),"unknown component request field");
  require(integer(json.at("schema_version"),1,1)==1,"unknown component request version");
  const auto context=json.at("context").get<std::string>();require(!context.empty() && context.size()<=1024,"bounded calibration context required");
  Request r{io::read_physical_options(json.at("physical_options").dump()),
    grant(json,"search_work",10'000'000,0,100'000'000),grant(json,"enumeration_work",10'000'000,0,100'000'000),
    grant(json,"memory_limit_bytes",256U*1024U*1024U,1024U*1024U,4ULL*1024ULL*1024ULL*1024ULL),
    grant(json,"max_events",256,1,4096),grant(json,"calibration_repetitions",2,1,5),
    grant(json,"sample_period",4,2,1'000'000),grant(json,"sample_offset",0,0,999'999),
    grant(json,"stale_prefix_events",1,0,4096),grant(json,"meta_work",10'000'000,0,100'000'000),
    grant(json,"model_work",20'000'000,1,100'000'000),
    static_cast<std::size_t>(grant(json,"candidate_limit",8,1,32)),static_cast<std::size_t>(grant(json,"calibration_plan_limit",4,1,32)),
    static_cast<std::size_t>(grant(json,"meta_output_limit",1000,1,10'000)),static_cast<std::size_t>(grant(json,"depth_limit",128,0,256)),
    grant(json,"record_limit",1'000'000,0,10'000'000),grant(json,"cell_limit",10'000'000,0,100'000'000),context};
  require(r.sample_offset<r.sample_period,"sample offset must be below its period");
  require(r.event_limit*r.repetitions*r.calibration_plans<=65536,"calibration observation grant exceeds65536");
  return r;
}
void emit(const Json& report) {
  const auto encoded=report.dump();require(encoded.size()<=64U*1024U*1024U,"component report exceeds64MiB");
  std::cout<<encoded<<'\n';std::cout.flush();require(bool(std::cout),"component report output failed");
}

// The original certificate keeps its original witness. V3 is explicitly an
// experimental checked upper; it never becomes MinimumHeightCandidate.
Json artifact(const PhysicalPlan& plan,const Json& certificate,bool minimum) {
  return {{"schema_version",minimum?2:3},
    {"height_binding",minimum?"independently_checked_equal_height_upper_v1":"independently_checked_original_lower_actual_upper_v1"},
    {"physical",io::write_physical(plan)},{"height_certificate",certificate}};
}
Json shape(const FreeConnexTree& tree) {
  std::size_t fanout=0,generalized=0;
  for(const auto& node:tree.nodes){fanout=std::max(fanout,node.children.size());if(node.kind==NodeKind::generalized)++generalized;}
  return {{"nodes",tree.nodes.size()},{"generalized_nodes",generalized},{"maximum_child_fanout",fanout}};
}
void drain(planner::CandidateProvider& provider,std::size_t count) {
  while(provider.candidate_count()<count && !provider.progress().family_exhausted) {
    const auto step=provider.advance({10000,{}});
    if(step.stopped_for!=planner::CandidateStop::candidate_ready && step.stopped_for!=planner::CandidateStop::quantum_work &&
       step.stopped_for!=planner::CandidateStop::quantum_time)break;
  }
}
struct Family {std::string id;planner::CandidateSnapshot snapshot;Json report;};
Family family(std::string id,planner::CandidateProvider provider,const Request& request,Json preparation) {
  const auto begin=Clock::now();drain(provider,request.candidates);const auto end=Clock::now();
  auto report=Json{{"id",id},{"preparation",std::move(preparation)},{"admission_ns",elapsed(begin,end)},
    {"progress",io::write_candidate_progress(provider)}};
  return {std::move(id),provider.snapshot(),std::move(report)};
}
Json meta_report(const meta::MetaCandidateReport& p) {
  return {{"construction_stop",static_cast<unsigned>(p.construction_stop)},
    {"construction",{{"work",p.construction_usage.work},{"nodes",p.construction_usage.nodes},{"scope_cells",p.construction_usage.scope_cells}}},
    {"enumeration_stop",static_cast<unsigned>(p.enumeration_stop)},{"metadata_valid",p.enumeration_metadata.valid},
    {"enumeration",{{"work",p.enumeration_usage.work},{"fragments",p.enumeration_usage.fragments},{"cells",p.enumeration_usage.cells},{"output_trees",p.enumeration_usage.output_trees}}},
    {"mapping_stop",static_cast<unsigned>(p.mapping_stop)},
    {"mapping",{{"work",p.mapping_usage.work},{"fragments",p.mapping_usage.fragments},{"cells",p.mapping_usage.cells},
      {"output_trees",p.mapping_usage.output_trees},{"peak_depth",p.mapping_usage.peak_depth}}},
    {"ordinary_exhausted",p.ordinary_exhausted},{"mapped_input_fibers_exhausted",p.mapped_input_fibers_exhausted},
    {"all_ordinary_roots_materialized",p.all_ordinary_roots_materialized},{"rooted_ordinary_trees",p.rooted_ordinary_trees},
    {"undirected_trees",p.undirected_trees},{"root_sets",p.root_sets},{"height_pruned_root_sets",p.height_pruned_root_sets},
    {"generalized_partitions",p.generalized_partitions},{"scope",std::string(p.scope)},{"cost_scope",std::string(p.cost_scope)}};
}
FreeConnexTree ordinary_tree(const Query& query,const meta::JoinTree& join) {
  FreeConnexTree tree;tree.root=NodeId{join.root};
  for(std::size_t i=0;i<query.atoms.size();++i) {
    VariableSet scope;for(const auto& term:query.atoms[i].terms)if(const auto* variable=std::get_if<VariableId>(&term))scope.insert(*variable);
    tree.nodes.push_back({"ordinary_"+std::to_string(i),NodeKind::native,std::move(scope),{},i,{}});
  }
  for(std::size_t i=0;i<join.parent.size();++i)if(i!=join.root)tree.nodes[join.parent[i]].children.push_back(NodeId{i});
  return tree;
}

// A profile always comes from this actual candidate's lowered owner. A stale
// profile is captured before the suffix, retained unchanged and revalidated.
struct Training {std::optional<cost::Profile> profile;Json report;};
Training train(const Family& family,std::size_t index,const PhysicalPlan& plan,const std::string& input,
    const Request& request,std::string_view variant) {
  runtime::DeltaRuntime owner(plan,request.runtime_options());runtime::workload::Options collect;
  collect.mode=variant=="absent"?runtime::workload::Mode::off:runtime::workload::Mode::counters;
  if(variant=="sampled"){collect.period=request.sample_period;collect.offset=request.sample_offset;}
  owner.configure_workload_statistics(collect);std::istringstream stream(input);io::EventReader reader(stream,owner.plan());
  std::optional<cost::Profile> profile;rank::Stop capture_stop=rank::Stop::internal_error;U64 count=0;
  auto capture=[&] {const auto attempt=cost::capture(family.snapshot,index,owner,request.model_limits());capture_stop=attempt.stop;profile=attempt.profile;};
  if(variant=="stale" && !request.stale_prefix)capture();
  while(const auto* event=reader.peek()) {
    require(count<request.event_limit,"training input exceeds event grant");
    {auto pending=owner.begin_view(event->update);while(pending.step()!=runtime::DeltaStep::prepared){}auto epoch=pending.commit();static_cast<void>(epoch);}
    reader.acknowledge();++count;
    if(variant=="stale" && count==request.stale_prefix)capture();
  }
  require(count>0,"training input is empty");if(variant!="stale" || request.stale_prefix>count)capture();
  Json report{{"variant",variant},{"events",count},{"owner_epoch",owner.sequence()},{"capture_stop",static_cast<unsigned>(capture_stop)},
    {"collection",{{"mode",variant=="absent"?"off":"counters"},{"period",collect.period},{"offset",collect.offset},{"detail_budget",collect.detail_budget}}}};
  if(profile) {
    const auto& evidence=profile->evidence();const auto& observed=evidence.captured()->workload();const auto valid=cost::revalidate(*profile,owner);
    auto weights=Json::array();for(const auto& value:evidence.inputs().weights())weights.push_back({{"table",value.table.value},
      {"inserts",value.inserts},{"erases",value.erases},{"changed",value.changed},{"noop",value.noop}});
    report["stamp"]=stamp(observed.stamp());report["modes"]=modes(observed.modes());report["detail_availability"]=static_cast<unsigned>(observed.detail_availability());
    report["depth_reasons"]=evidence.inputs().depth_reasons();report["memory_reasons"]=evidence.inputs().memory_reasons();
    report["denominator"]=evidence.inputs().denominator();report["weights"]=std::move(weights);
    report["revalidation"]={{"boundary",valid.boundary},{"depth",valid.depth},{"memory",valid.memory}};
    report["lag_events"]=owner.sequence()-observed.stamp().committed_epoch;
    report["is_stale"]=owner.sequence()!=observed.stamp().committed_epoch;
  }
  return {std::move(profile),std::move(report)};
}

// All calibration observations use committed full-detail census features. The
// timer excludes JSON decoding, feature snapshots, owner setup and fitting; it
// includes prepare/commit and returned epoch cleanup, with no output/WAL/sink.
Json measure_calibration(const std::vector<PhysicalPlan>& plans,const std::string& input,const Request& request) {
  auto raw=Json::array();
  for(std::size_t index=0;index<std::min(plans.size(),request.calibration_plans);++index)for(U64 repetition=0;repetition<request.repetitions;++repetition) {
    runtime::DeltaRuntime owner(plans[index],request.runtime_options());runtime::workload::Options collect;collect.mode=runtime::workload::Mode::counters;
    owner.configure_workload_statistics(collect);std::istringstream stream(input);io::EventReader reader(stream,owner.plan());
    auto initial=cost::features(owner.workload_statistics(),request.model_limits());require(initial.census.has_value(),"initial calibration census unavailable");
    auto before=*initial.census;U64 count=0;
    while(const auto* event=reader.peek()) {
      require(count<request.event_limit,"calibration input exceeds event grant");const auto begin=Clock::now();
      {auto pending=owner.begin_view(event->update);while(pending.step()!=runtime::DeltaStep::prepared){}auto epoch=pending.commit();static_cast<void>(epoch);}
      const auto end=Clock::now();reader.acknowledge();++count;
      const auto measured=cost::features(owner.workload_statistics(),request.model_limits());require(measured.census.has_value(),"exact calibration census unavailable");
      const auto& after=*measured.census;require(after.modes==before.modes,"calibration modes changed");
      cost::FitObservation sample;sample.elapsed_ns=elapsed(begin,end);
      for(std::size_t c=0;c<cost::component_count;++c){require(after.units[c]>=before.units[c],"calibration counter regressed");sample.units[c]=after.units[c]-before.units[c];}
      require(sample.units[static_cast<std::size_t>(cost::Component::base_input)]==1,"calibration phase is not one physical input");
      raw.push_back({{"physical_sha256",plans[index].physical_sha256()},{"repetition",repetition},{"sequence",after.stamp.committed_epoch},
        {"units",sample.units},{"elapsed_ns",sample.elapsed_ns}});before=after;
    }
    require(count>0,"calibration input is empty");
  }
  return raw;
}
std::vector<cost::FitObservation> observations(const Json& raw) {
  require(raw.is_array() && !raw.empty() && raw.size()<=65536,"invalid frozen calibration observation grant");
  std::vector<cost::FitObservation> result;result.reserve(raw.size());
  for(const auto& row:raw) {
    const auto& units=row.at("units");require(units.is_array() && units.size()==cost::component_count,"calibration feature width mismatch");
    cost::FitObservation sample;sample.elapsed_ns=integer(row.at("elapsed_ns"),0,std::numeric_limits<U64>::max());
    for(std::size_t c=0;c<cost::component_count;++c)sample.units[c]=integer(units.at(c),0,std::numeric_limits<U64>::max());
    require(sample.units[static_cast<std::size_t>(cost::Component::base_input)]==1,"calibration phase must contain one physical input");
    for(auto c=static_cast<std::size_t>(cost::Component::annotation_change);c<cost::component_count;++c)
      require(sample.units[c]==0,"maintenance-only calibration includes output/annotation features");
    result.push_back(sample);
  }
  return result;
}
Json calibration_report(const cost::CalibrationAttempt& fitted) {
  Json report{{"stop",static_cast<unsigned>(fitted.stop)},{"usage",usage(fitted.usage)}};
  if(!fitted.calibration)return report;
  const auto& model=*fitted.calibration;auto coefficients=Json::object();
  for(std::size_t c=0;c<cost::component_count;++c) {
    const auto& value=model.coefficients()[c];coefficients[std::string(cost::component_name(static_cast<cost::Component>(c)))]=
      value?Json{{"rate",ratio(value->nanoseconds_per_unit)},{"observed_units",value->units},{"samples",value->samples}}:Json(nullptr);
  }
  const auto& summary=*model.fit_summary();report["coefficients"]=std::move(coefficients);
  report["fit"]={{"algorithm","zero_initialized_fixed_order_nonnegative_coordinates_v1"},{"iterations",summary.iterations},
    {"observations",summary.observations},{"numerical_rank",summary.numerical_rank},{"observed_features",summary.observed_features},
    {"underdetermined",summary.underdetermined},{"rmse_ns_on_calibration_data",summary.root_mean_square_error_ns},
    {"max_error_ns_on_calibration_data",summary.maximum_absolute_error_ns},{"quantization_denominator",summary.options.quantization_denominator}};
  return report;
}
Json ranking(const planner::CandidateSnapshot& snapshot,const resource::MemoryAccount& account,
    const std::optional<rank::Evidence>& evidence,rank::Policy policy,const Request& request) {
  rank::Request ask;ask.policy=policy;ask.fallback=rank::Fallback::require_evidence;ask.limits=request.model_limits();
  const auto attempt=rank::rank_with_account(account,snapshot,ask,evidence);
  Json report{{"policy",policy==rank::Policy::height_only?"height_only":"committed_input_native_depth"},
    {"stop",static_cast<unsigned>(attempt.stop)},{"reasons",attempt.reasons},{"usage",usage(attempt.usage)},{"evaluated",attempt.evaluated}};
  if(attempt.result) {
    const auto& result=*attempt.result;auto scores=Json::array();
    for(const auto& value:result.scores())scores.push_back({{"structural_key",text(value.structural_key)},
      {"numerator",policy==rank::Policy::height_only?std::to_string(value.height):text(value.numerator)},
      {"denominator",policy==rank::Policy::height_only?"1":text(value.denominator)}});
    report["selected_index"]=result.selected_index();report["selected_key"]=result.selected().structural_key();report["scores"]=std::move(scores);
  }
  return report;
}
Json estimates(const cost::Attempt& attempt) {
  Json report{{"stop",static_cast<unsigned>(attempt.stop)},{"usage",usage(attempt.usage)},{"candidates",Json::array()}};
  if(attempt.result)for(const auto& value:attempt.result->candidates()) {
    auto terms=Json::array();for(const auto& term:value.terms)terms.push_back({{"component",std::string(cost::component_name(term.component))},
      {"descriptor",term.descriptor?Json(*term.descriptor):Json(nullptr)},{"units",ratio(term.units)},{"nanoseconds",ratio(term.nanoseconds)},
      {"issues",term.issues},{"confidence",{{"basis",static_cast<unsigned>(term.confidence.basis)},
        {"availability",static_cast<unsigned>(term.confidence.availability)},{"complete_inputs",term.confidence.complete_inputs},{"observed_events",term.confidence.observed_events}}}});
    report["candidates"].push_back({{"structural_key",value.candidate.structural_key()},{"maintenance_ns",ratio(value.maintenance_ns)},
      {"total_ns",ratio(value.total_ns)},{"issues",value.issues},{"future_memory_unknown",value.future_memory_unknown},
      {"memory_budget_bytes",value.memory_budget_bytes},{"asof_requested_bytes",value.memory_at_capture?Json(value.memory_at_capture->current.requested_bytes):Json(nullptr)},
      {"observed_stamp",value.observed_stamp?stamp(*value.observed_stamp):Json(nullptr)},{"terms",std::move(terms)}});
  }
  return report;
}

int run(int argc,char** argv) {
  require(argc==6,"usage: crown_export_components QUERY.sql CATALOG.json TRAIN.jsonl CALIBRATION.jsonl REQUEST.json");
  const auto json=io::read_json(read(argv[5],32U*1024U*1024U));const auto request=parse_request(json);
  const auto sql=read(argv[1],frontend::ParseLimits{}.source_bytes),catalog_text=read(argv[2],16U*1024U*1024U);
  const auto training=read(argv[3],8U*1024U*1024U),calibration_input=read(argv[4],8U*1024U*1024U);
  const auto begin=Clock::now();const auto catalog=io::read_catalog(catalog_text);const auto admitted=frontend::admit_sql(sql,catalog);
  require(admitted.status==frontend::AdmissionStatus::admitted && admitted.route!=frontend::AdmissionRoute::constant_empty,"component planning requires admitted nonconstant set SQL");
  const auto& normalized=*admitted.program;const auto admitted_at=Clock::now();
  planner::SearchOptions exact_options;exact_options.policy=planner::SearchPolicy::best_found;
  exact_options.limits.producer.work=request.search_work;exact_options.limits.replay.work=request.search_work;exact_options.limits.logical_depth=request.depth;
  auto search=planner::ExactSearch::create(normalized.core_catalog,normalized.core,exact_options);
  while(!search.optimum()) {
    const auto step=search.advance({10000,{}});
    if(step.stopped_for!=planner::StopReason::quantum_work && step.stopped_for!=planner::StopReason::quantum_time)break;
  }
  const auto proved_at=Clock::now();Json report{{"schema_version",1},{"kind","b04_cold_component_planning_export"},{"request",json},
    {"source_sha256",sha256(sql)},{"catalog_sha256",sha256(catalog_text)},{"training_sha256",sha256(training)},
    {"calibration_sha256",sha256(calibration_input)},{"compiler",__VERSION__},{"cpp_standard",__cplusplus},
    {"search",io::write_search_progress(search)},{"setup_timings",{{"admission_ns",elapsed(begin,admitted_at)},{"original_proof_ns",elapsed(admitted_at,proved_at)}}},
    {"families",Json::array()},{"ordinary",nullptr},
    {"qualification","cold conditional experiment data; exact answers; offline C03 assumptions only; no C05 maintenance_cost enablement, runtime installation, global cost optimum or held-out acceptance"}};
  const auto structural=search.progress().structural;
  report["search_structural"]={{"states",structural.states},{"partitions",structural.partitions},{"candidates",structural.candidates},
    {"cache_hits",structural.cache_hits},{"hierarchy_tests",structural.hierarchy_tests},{"hierarchy_hits",structural.hierarchy_hits},
    {"component_splits",structural.component_splits},{"symmetry_skips",structural.symmetry_skips},{"bound_prunes",structural.bound_prunes}};
  report["effective_grants"]={{"search_work_per_phase",request.search_work},{"enumeration_work",request.enumeration_work},
    {"candidate_limit",request.candidates},{"max_events_per_trace",request.event_limit},{"calibration_repetitions",request.repetitions},
    {"calibration_plan_limit",request.calibration_plans},{"meta_work_per_stage",request.meta_work},{"meta_output_limit",request.meta_outputs},
    {"depth_limit",request.depth},{"record_limit",request.records},{"cell_limit",request.cells},{"model_work",request.model_work},
    {"native_memory_limit_per_owner_bytes",request.memory},{"report_bytes",64U*1024U*1024U}};
  if(!search.optimum()){report["status"]="original_minimum_unavailable";emit(report);return 0;}
  const auto proof=*search.optimum();const auto certificate=io::write_verified_optimum(proof);
  report["proved_height"]=proof.height();report["original_certificate"]=certificate;
  std::vector<Family> families;std::vector<PhysicalPlan> calibration_plans;
  auto add_plan=[&](const PhysicalPlan& plan) {
    if(std::none_of(calibration_plans.begin(),calibration_plans.end(),[&](const PhysicalPlan& x){return x.physical_sha256()==plan.physical_sha256();}))calibration_plans.push_back(plan);
  };
  // Common calibration initialization is not an implicit member of any family.
  const auto basis=planner::lower_normalized(normalized,proof.upper().tree(),request.physical);add_plan(basis);
  const auto exact_begin=Clock::now();auto exact_provider=planner::CandidateProvider::create(proof,{},request.candidate_limits());
  families.push_back(family("exact",std::move(exact_provider),request,{{"method","P07_exact_seed_normal_form"},
    {"creation_ns",elapsed(exact_begin,Clock::now())},{"common_original_proof_charged_separately",true}}));

  const auto residual_begin=Clock::now();planner::ResidualOptions residual_options;residual_options.mode=planner::ResidualMode::candidates_with_exact_repair;
  residual_options.limits.residual.work=request.enumeration_work;residual_options.limits.logical_depth=request.depth;
  residual_options.limits.record_limit=request.records;residual_options.limits.cell_limit=request.cells;residual_options.limits.exact=exact_options.limits;
  auto residual=planner::ResidualSearch::create(normalized.core_catalog,normalized.core,residual_options);
  while(residual.progress().result==planner::ResidualResult::unfinished) {
    const auto step=residual.advance({10000,{}});if(step.stopped_for!=planner::ResidualStopReason::quantum_work && step.stopped_for!=planner::ResidualStopReason::quantum_time)break;
  }
  std::vector<FreeConnexTree> proposals;Json residual_upper=nullptr;
  if(const auto value=residual.candidate()) {
    require(value->height()>=proof.height(),"residual upper below independently proved original height");
    proposals.push_back(value->tree());const auto plan=planner::lower_normalized(normalized,value->tree(),request.physical);
    residual_upper={{"height",value->height()},{"height_gap",value->height()-proof.height()},{"origin",static_cast<unsigned>(value->origin())},{"checked",io::write_residual_candidate(*value)},
      {"artifact",artifact(plan,certificate,false)}};
  }
  families.push_back(family("residual",planner::CandidateProvider::from_proposals(proof,std::move(proposals),{},request.candidate_limits()),request,
    {{"method","bounded_residual_candidate_as_finite_proposal"},{"elapsed_ns",elapsed(residual_begin,Clock::now())},
      {"progress",io::write_residual_progress(residual)},{"checked_upper",std::move(residual_upper)},
      {"exact_repair_may_run",true},{"no_implicit_exact_or_normal_form_seed",true}}));

  const auto meta_begin=Clock::now();meta::MetaCandidateLimits limits;
  limits.construction.work=request.meta_work;limits.construction.nodes=static_cast<std::size_t>(std::min<U64>(request.records,100'000));limits.construction.scope_cells=request.cells;
  limits.enumeration.work=request.meta_work;limits.enumeration.fragments=request.records;limits.enumeration.cells=request.cells;limits.enumeration.output_trees=request.meta_outputs;
  limits.enumeration.metadata=limits.construction;limits.mapping.work=request.meta_work;limits.mapping.fragments=request.records;limits.mapping.cells=request.cells;
  limits.mapping.output_trees=request.meta_outputs;limits.mapping.depth=request.depth;limits.admission=request.candidate_limits();
  auto prepared=meta::prepare_meta_candidates(proof,limits);auto prepared_report=meta_report(prepared.report);
  prepared_report["elapsed_ns"]=elapsed(meta_begin,Clock::now());
  if(prepared.provider) {
    auto entry=family("meta",std::move(*prepared.provider),request,std::move(prepared_report));
    entry.report["normalized_minimum_family_exhausted"]=prepared.report.ordinary_exhausted && prepared.report.mapped_input_fibers_exhausted && entry.snapshot.family_exhausted();
    families.push_back(std::move(entry));
  } else report["meta_unavailable"]=std::move(prepared_report);

  const auto ordinary_begin=Clock::now();const auto decomposition=meta::construct(normalized.core_catalog,normalized.core,limits.construction);
  Json ordinary{{"construction_stop",static_cast<unsigned>(decomposition.stop)},
    {"construction",{{"work",decomposition.usage.work},{"nodes",decomposition.usage.nodes},{"scope_cells",decomposition.usage.scope_cells}}},
    {"candidates",Json::array()},{"rejections",Json::array()},{"rejected_by_P02",0},{"ordinary_exhausted",false}};
  if(decomposition.decomposition) {
    auto enumeration_limits=limits.enumeration;enumeration_limits.all_roots=true;
    const auto enumerated=meta::enumerate(normalized.core_catalog,normalized.core,*decomposition.decomposition,enumeration_limits);
    ordinary["enumeration_stop"]=static_cast<unsigned>(enumerated.stop);ordinary["ordinary_exhausted"]=enumerated.stop==meta::EnumerationStop::complete;
    ordinary["usage"]={{"work",enumerated.usage.work},{"fragments",enumerated.usage.fragments},{"cells",enumerated.usage.cells},{"output_trees",enumerated.usage.output_trees}};
    std::size_t rejected=0;
    for(const auto& join:enumerated.trees) {
      const auto tree=ordinary_tree(normalized.core,join);const auto checked=planner::validate_tree(normalized.core_catalog,normalized.core,tree);
      if(!checked.valid) {
        auto rules=Json::array();for(const auto& violation:checked.violations)rules.push_back(violation.rule);
        ordinary["rejections"].push_back({{"root_occurrence",join.root},{"rules",std::move(rules)}});++rejected;continue;
      }
      const auto plan=planner::lower_normalized(normalized,tree,request.physical);require(*checked.native_height>=proof.height(),"checked ordinary upper below independently proved original height");
      ordinary["candidates"].push_back({{"root_occurrence",join.root},{"height",*checked.native_height},{"physical_sha256",plan.physical_sha256()},
        {"height_gap",*checked.native_height-proof.height()},{"shape",shape(tree)},{"artifact",artifact(plan,certificate,false)}});
    }
    ordinary["rejected_by_P02"]=rejected;
  }
  ordinary["elapsed_ns"]=elapsed(ordinary_begin,Clock::now());report["ordinary"]=std::move(ordinary);

  // Every minimum-family member keeps its family/provenance. Equal physical
  // plans may share a calibration replay, never a provider prefix or proof.
  for(auto& entry:families) {
    auto candidates=Json::array();
    for(std::size_t index=0;index<entry.snapshot.candidate_count();++index) {
      const auto value=*entry.snapshot.candidate(index);const auto plan=planner::lower_normalized(normalized,value.tree(),request.physical);add_plan(plan);
      candidates.push_back({{"index",index},{"structural_key",value.structural_key()},{"height",value.height()},
        {"shape",shape(value.tree())},
        {"physical_sha256",plan.physical_sha256()},{"provenance",io::write_minimum_height_candidate(value).at("provenance")},
        {"artifact",artifact(plan,certificate,true)}});
    }
    entry.report["candidates"]=std::move(candidates);
  }
  const auto planned_at=Clock::now();report["setup_timings"]["families_and_ordinary_ns"]=elapsed(proved_at,planned_at);
  std::vector<cost::InputDemand> demand;auto demand_keys=std::set<std::pair<U64,unsigned>>{};
  require(json.at("input_demand").is_array(),"input_demand must list every physical table and operation");
  for(const auto& row:json.at("input_demand")) {
    const auto table=integer(row.at("table"),0,std::numeric_limits<U64>::max());const auto operation=row.at("operation").get<std::string>();
    require(operation=="insert" || operation=="erase","unknown demanded operation");const auto op=operation=="insert"?runtime::workload::Operation::insert:runtime::workload::Operation::erase;
    require(table<basis.source_catalog().tables.size() && demand_keys.emplace(table,static_cast<unsigned>(op)).second,"duplicate or foreign demand stratum");
    demand.push_back({TableId{table},op,integer(row.at("inputs"),0,1'000'000'000)});
  }
  require(demand.size()==basis.source_catalog().tables.size()*2,"every physical table/op including zero must be declared");

  auto account=resource::MemoryAccount::create(request.memory);
  runtime::DeltaRuntime mode_owner(basis,request.runtime_options());runtime::workload::Options census;census.mode=runtime::workload::Mode::counters;
  mode_owner.configure_workload_statistics(census);cost::FitOptions fit_options;fit_options.modes=mode_owner.workload_statistics().modes();
  Json identity{{"schema_version",1},{"context",request.context},{"source_sha256",sha256(sql)},{"catalog_sha256",sha256(catalog_text)},
    {"calibration_sha256",sha256(calibration_input)},{"physical_options_sha256",sha256(json.at("physical_options").dump())},
    {"backend",basis.guarantee().storage_backend},{"compiler",__VERSION__},{"cpp_standard",__cplusplus},
    {"phase","native_begin_prepare_commit_epoch_release"},{"runtime_mode","maintenance"},{"observation","off"},
    {"actual_modes",modes(*fit_options.modes)},{"memory_limit_bytes",request.memory},
    {"calibration_collection",{{"mode","counters"},{"period",1},{"offset",0},{"max_cells",census.max_cells},{"detail_budget",census.detail_budget}}},
    {"fit_options",{{"max_iterations",fit_options.max_iterations},{"relative_tolerance",fit_options.relative_tolerance},
      {"rank_tolerance",fit_options.rank_tolerance},{"ridge_numerator",fit_options.ridge.numerator},{"ridge_denominator",fit_options.ridge.denominator},
      {"quantization_denominator",fit_options.quantization_denominator}}},
    {"output_demand","all_zero_no_output_WAL_sink_encoding_annotation"}};
  Json raw;bool imported=json.contains("prior_calibration") && !json.at("prior_calibration").is_null();
  if(imported) {
    const auto& prior=json.at("prior_calibration");require(prior.at("identity")==identity,"frozen calibration context/provenance mismatch");
    raw=prior.at("observations");require(prior.at("observations_sha256")==sha256(raw.dump()),"frozen calibration observation digest mismatch");
  } else raw=measure_calibration(calibration_plans,calibration_input,request);
  const auto samples=observations(raw);
  const auto fitted=cost::fit(account,request.context,basis.guarantee().storage_backend,samples,fit_options,request.model_limits());
  report["calibration"]={{"identity",identity},{"observations",raw},{"observations_sha256",sha256(raw.dump())},
    {"origin",imported?"caller_supplied_frozen_observations_not_remeasured":"actual_full_census_native_phases"},
    {"model",calibration_report(fitted)},{"modes",modes(*fit_options.modes)},
    {"qualification","one pooled fixed calibration for all family/statistics variants; linear attributions and missing columns remain assumptions/unavailable; evaluation instrumentation must match this context"}};
  if(fitted.calibration)report["calibration"]["coefficients_sha256"]=sha256(report["calibration"]["model"]["coefficients"].dump());
  const auto calibrated_at=Clock::now();report["setup_timings"]["calibration_and_fit_ns"]=elapsed(planned_at,calibrated_at);

  const std::array<std::string_view,4> variants{"full","sampled","stale","absent"};
  for(auto& entry:families) {
    auto statistics=Json::array();
    for(const auto variant:variants) {
      std::vector<cost::Profile> profiles;auto captures=Json::array();std::optional<rank::Evidence> evidence;
      for(std::size_t index=0;index<entry.snapshot.candidate_count();++index) {
        const auto value=*entry.snapshot.candidate(index);const auto plan=planner::lower_normalized(normalized,value.tree(),request.physical);
        auto trained=train(entry,index,plan,training,request,variant);trained.report["candidate"]=index;
        if(trained.profile){if(!evidence)evidence=trained.profile->evidence().inputs();profiles.push_back(*trained.profile);}
        captures.push_back(std::move(trained.report));
      }
      Json group{{"variant",variant},{"captures",std::move(captures)},
        {"height",ranking(entry.snapshot,account,{},rank::Policy::height_only,request)},
        {"weighted_depth",ranking(entry.snapshot,account,evidence,rank::Policy::committed_input_native_depth,request)}};
      if(fitted.calibration) {
        cost::Request ask;ask.input=demand;ask.memory_budget_bytes=request.memory;ask.limits=request.model_limits();
        group["event_cost"]=estimates(cost::estimate(account,entry.snapshot,profiles,*fitted.calibration,ask));
      } else group["event_cost"]={{"unavailable","calibration_fit_not_published"}};
      statistics.push_back(std::move(group));
    }
    entry.report["statistics"]=std::move(statistics);report["families"].push_back(std::move(entry.report));
  }
  report["setup_timings"]["training_capture_ranking_estimation_ns"]=elapsed(calibrated_at,Clock::now());
  const auto model_memory=account.statistics();
  report["model_account_memory"]={{"current_requested_bytes",model_memory.current.requested_bytes},
    {"peak_requested_bytes",model_memory.peak_requested_bytes},{"limit_bytes",model_memory.limit_bytes},
    {"scope","fit/rank/estimate receiving account; candidate-specific native owners and ordinary JSON/planner storage are separate; not process RSS"}};
  report["cost_scope"]={{"objective","offline_C03_maintenance_only_conditional_forecast"},{"input_demand",json.at("input_demand")},
    {"output_annotation_checkpoint_encoding_demand",0},{"C05_maintenance_cost","unsupported_unchanged"},
    {"selection","external_exact_Fraction_over_available_ratios_with_structural_key_ties"},
    {"stale_profiles","retained_asof_with_actual_owner_revalidation_no_current_installation"},
    {"excluded_costs","parsing/decoding; planner/admission; owner/statistics initialization; feature/profile capture; fit/rank/estimate; output/WAL/sink; final runtime teardown"}};
  report["status"]="exported_conditional_data";emit(report);return 0;
}
} // namespace
int main(int argc,char** argv) {
  try{return run(argc,argv);}catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}
}
