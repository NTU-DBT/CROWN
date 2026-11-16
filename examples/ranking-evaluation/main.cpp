#include <crown/api/error.hpp>
#include <crown/frontend/admission.hpp>
#include <crown/io/catalog.hpp>
#include <crown/io/document.hpp>
#include <crown/io/ingest.hpp>
#include <crown/io/oracle.hpp>
#include <crown/io/physical.hpp>
#include <crown/ir/digest.hpp>
#include <crown/runtime/selection.hpp>
#include <array>
#include <chrono>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>

namespace {
using namespace crown;
using io::Json;
using U64=std::uint64_t;
using Clock=std::chrono::steady_clock;
namespace ps=planner::selection;
namespace rank=planner::ranking;
void require(bool value,const char* message) {if(!value)throw Error("ranking_evaluation_error",message);}
std::string read(const char* path,std::size_t limit) {
  std::ifstream file(path,std::ios::binary);require(bool(file),"cannot open evaluation input");std::string result;char block[4096];
  while(file) {file.read(block,sizeof(block));const auto count=static_cast<std::size_t>(file.gcount());
    require(count<=limit-result.size(),"evaluation input byte limit exceeded");result.append(block,count);}
  require(!file.bad(),"evaluation input read failed");return result;
}
U64 number(const Json& object,const char* key,U64 maximum) {
  const auto& value=object.at(key);require(value.is_number_integer() && (value.is_number_unsigned() || value.get<std::int64_t>()>=0),"expected unsigned evaluation integer");
  const auto result=value.get<U64>();require(result>0 && result<=maximum,"evaluation resource grant outside finite bounds");return result;
}
U64 elapsed(Clock::time_point begin,Clock::time_point end) {
  const auto count=std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();require(count>=0,"evaluation clock regressed");return static_cast<U64>(count);
}
template<class Text> std::string text(const Text& value) {return {value.data(),value.size()};}
Json usage(const rank::Usage& value) {
  return {{"work",value.work},{"cells",value.cells},{"binding_key_bytes",value.binding_key_bytes},{"payload_bytes",value.payload_bytes},
    {"lowering_work",value.lowering_work},{"identity_work",value.identity_work},{"binding_replay_work",value.binding_replay_work},
    {"normalization_work",value.normalization_work},{"active_nanoseconds",value.active_nanoseconds}};
}
// This exports a genuine handle to editable transport; consumers must independently replay it.
Json certificate(const planner::VerifiedOptimum& proof) {
  const auto& claim=proof.certificate();planner::OracleResult dto;
  dto.status=planner::OracleStatus::proven_minimum;dto.minimum_height=proof.height();dto.tree=proof.upper().tree();
  dto.lower_bounds=claim.lower_bounds;dto.algorithm=claim.algorithm;dto.certificate_verified=true;
  const auto binding=proof.binding();return io::write_oracle(dto,binding.catalog(),binding.query()).at("certificate");
}
Json score(const rank::CandidateScore& value,rank::Policy policy) {
  auto depths=Json::array(),tables=Json::array(),terms=Json::array();
  for(const auto& item:value.depths)depths.push_back({{"occurrence",item.occurrence.value},{"table",item.table.value},{"depth",item.depth}});
  for(const auto& item:value.table_depths)tables.push_back({{"table",item.table.value},{"inserts",item.inserts},{"erases",item.erases},{"depth_sum",text(item.depth_sum)},{"contribution",text(item.contribution)}});
  for(const auto& item:value.slot_terms)terms.push_back({{"relation",item.relation.value},{"index",item.index?Json(item.index->value):Json(nullptr)},
    {"width",item.width},{"population",text(item.population)},{"contribution",text(item.contribution)}});
  return {{"structural_key",text(value.structural_key)},{"height",value.height},
    {"proxy_numerator",policy==rank::Policy::height_only?std::to_string(value.height):policy==rank::Policy::tuple_index_slots?text(value.slots):text(value.numerator)},
    {"proxy_denominator",policy==rank::Policy::committed_input_native_depth?text(value.denominator):"1"},
    {"unit",policy==rank::Policy::height_only?"native_height":policy==rank::Policy::tuple_index_slots?"tuple_index_slots":"committed_input_native_depth"},
    {"occurrence_depths",std::move(depths)},{"table_depths",std::move(tables)},{"slot_terms",std::move(terms)}};
}
int run(int argc,char** argv) {
  require(argc==5,"usage: crown_export_ranking QUERY.sql CATALOG.json TRAIN.jsonl REQUEST.json");
  const auto request=io::read_json(read(argv[4],1024U*1024U));
  const std::set<std::string> fields{"schema_version","physical_options","candidate_limit","search_work","enumeration_work","memory_limit_bytes","max_events","require_exhausted_family","fallback","slot_limit"};
  require(request.is_object() && request.size()==fields.size(),"ranking request field mismatch");
  for(const auto& item:request.items())require(fields.contains(item.key()),"unknown ranking request field");
  require(request.at("schema_version").is_number_integer() && request.at("schema_version")==1,"unknown ranking request version");
  const auto count=number(request,"candidate_limit",32),search_work=number(request,"search_work",100'000'000),enumeration_work=number(request,"enumeration_work",100'000'000);
  const auto memory_limit=number(request,"memory_limit_bytes",4ULL*1024ULL*1024ULL*1024ULL),event_limit=number(request,"max_events",4096);
  require(request.at("require_exhausted_family").is_boolean(),"invalid family requirement");
  const auto fallback=request.at("fallback").get<std::string>();require(fallback=="height_only" || fallback=="require_evidence","invalid ranking fallback");
  require(request.at("slot_limit").is_null() || request.at("slot_limit").is_string(),"invalid tuple/index slot limit");
  const auto options=io::read_physical_options(request.at("physical_options").dump());
  const auto sql=read(argv[1],frontend::ParseLimits{}.source_bytes),catalog_text=read(argv[2],16U*1024U*1024U),training=read(argv[3],8U*1024U*1024U);
  const auto begin=Clock::now();const auto catalog=io::read_catalog(catalog_text);const auto admitted=frontend::admit_sql(sql,catalog);
  require(admitted.status==frontend::AdmissionStatus::admitted && admitted.route!=frontend::AdmissionRoute::constant_empty,"ranking evaluation requires admitted nonconstant SQL");
  const auto& normalized=*admitted.program;const auto admitted_at=Clock::now();
  planner::SearchOptions search_options;search_options.limits.producer.work=search_work;search_options.limits.replay.work=search_work;
  auto search=planner::ExactSearch::create(normalized.core_catalog,normalized.core,search_options);
  while(!search.optimum()) {
    const auto step=search.advance({10000,{}});
    require(search.optimum().has_value() || step.stopped_for==planner::StopReason::quantum_work || step.stopped_for==planner::StopReason::quantum_time,"exact minimum-height search stopped without proof");
  }
  const auto proof=*search.optimum();const auto proved_at=Clock::now();
  planner::CandidateLimits candidate_options;candidate_options.enumeration.work=enumeration_work;candidate_options.retained_candidates=static_cast<std::size_t>(count);
  auto provider=planner::CandidateProvider::create(proof,{},candidate_options);
  while(provider.candidate_count()<count && !provider.progress().family_exhausted) {
    const auto step=provider.advance({10000,{}});
    if(step.stopped_for==planner::CandidateStop::total_work || step.stopped_for==planner::CandidateStop::candidate_capacity)break;
    require(step.stopped_for==planner::CandidateStop::candidate_ready || step.stopped_for==planner::CandidateStop::quantum_work ||
      step.stopped_for==planner::CandidateStop::quantum_time || step.stopped_for==planner::CandidateStop::exhausted,"candidate enumeration failed");
  }
  const auto snapshot=provider.snapshot();require(snapshot.candidate_count()>0,"no checked ranking candidate");const auto enumerated_at=Clock::now();
  const auto basis=planner::lower_normalized(normalized,snapshot.candidate(0)->tree(),options);
  runtime::DeltaOptions runtime_options;runtime_options.mode=runtime::DeltaMode::maintenance;
  runtime_options.physical.support.memory_limit_bytes=memory_limit;runtime_options.physical.support.observation.mode=runtime::ObservationMode::off;
  runtime::DeltaRuntime owner(basis,runtime_options);std::istringstream input(training);io::EventReader reader(input,owner.plan());
  runtime::workload::Options collect;collect.mode=runtime::workload::Mode::counters;owner.configure_workload_statistics(collect);
  U64 events=0;
  while(const auto* event=reader.peek()) {
    require(events<event_limit,"training event grant exceeded");
    {auto pending=owner.begin_view(event->update);while(pending.step()!=runtime::DeltaStep::prepared){}auto epoch=pending.commit();static_cast<void>(epoch);}
    reader.acknowledge();++events;
  }
  require(events>0,"ranking training trace is empty");const auto trained_at=Clock::now();
  // Only committed training facts enter these policy choices; no held-out input is opened.
  const auto captured=runtime::ranking::capture(snapshot,owner);require(captured.evidence.has_value(),"bounded training evidence capture failed");
  const auto& evidence=captured.evidence->inputs();auto weights=Json::array(),sources=Json::array();
  for(const auto& value:evidence.weights())weights.push_back({{"table",value.table.value},{"inserts",value.inserts},{"erases",value.erases},{"changed",value.changed},{"noop",value.noop}});
  for(const auto& value:evidence.sources())sources.push_back({{"table",value.table.value},{"rows",value.rows}});
  auto policies=Json::array();
  const std::array<std::pair<ps::Policy,const char*>,3> policies_to_run{{{ps::Policy::height_only,"height_only"},
    {ps::Policy::committed_input_native_depth,"committed_input_native_depth"},{ps::Policy::tuple_index_slots,"tuple_index_slots"}}};
  for(const auto& [policy,name]:policies_to_run) {
    ps::Request select_request;select_request.policy=policy;select_request.fallback=fallback=="height_only"?rank::Fallback::height_only:rank::Fallback::require_evidence;
    select_request.family=request.at("require_exhausted_family").get<bool>()?ps::FamilyPolicy::require_exhausted_family:ps::FamilyPolicy::retained_prefix;
    select_request.limits.aggregate.work=20'000'000;select_request.limits.aggregate.payload_bytes=64U*1024U*1024U;
    if(!request.at("slot_limit").is_null())select_request.constraint=ps::TupleIndexSlotLimit{request.at("slot_limit").get<std::string>()};
    const auto selected=ps::select(snapshot,ps::PhysicalBasis{owner.plan()},select_request,evidence);
    Json report{{"policy",name},{"stop",static_cast<unsigned>(selected.stop)},{"stage",static_cast<unsigned>(selected.stage)},
      {"resource",static_cast<unsigned>(selected.resource)},{"reasons",selected.reasons},{"usage",usage(selected.usage)},
      {"retained",selected.retained},{"constraint_evaluated",selected.constraint_evaluated},{"primary_evaluated",selected.primary_evaluated}};
    if(selected.selection) {
      const auto& result=*selected.selection;auto assessments=Json::array(),decisions=Json::array();
      for(const auto& assessment:result.assessments()) {
        auto scores=Json::array();for(const auto& value:assessment.result.scores())scores.push_back(score(value,assessment.result.effective_policy()));
        assessments.push_back({{"purpose",static_cast<unsigned>(assessment.purpose)},{"effective_policy",static_cast<unsigned>(assessment.result.effective_policy())},{"scores",std::move(scores)}});
      }
      for(const auto& value:result.decisions())decisions.push_back({{"candidate",value.candidate_index},{"eligibility",static_cast<unsigned>(value.eligibility)}});
      report["selected_index"]=result.selected_index();report["selected_key"]=result.selected().structural_key();
      report["selected_physical_sha256"]=result.plan().physical_sha256();report["effective_policy"]=static_cast<unsigned>(result.effective_policy());
      report["fallback_reasons"]=result.fallback_reasons();report["assessments"]=std::move(assessments);report["decisions"]=std::move(decisions);
    }
    policies.push_back(std::move(report));
  }
  // Preserve the original certificate witness in every V2 candidate artifact.
  const auto selected_at=Clock::now();const auto original_certificate=certificate(proof);auto candidates=Json::array();
  for(std::size_t index=0;index<snapshot.candidate_count();++index) {
    const auto candidate=*snapshot.candidate(index);const auto plan=planner::lower_normalized(normalized,candidate.tree(),options);
    candidates.push_back({{"index",index},{"structural_key",candidate.structural_key()},{"height",candidate.height()},
      {"physical_sha256",plan.physical_sha256()},{"backend",plan.guarantee().storage_backend},
      {"artifact",{{"schema_version",2},{"height_binding","independently_checked_equal_height_upper_v1"},
        {"physical",io::write_physical(plan)},{"height_certificate",original_certificate}}}});
  }
  const auto& search_status=search.progress();const auto status=provider.progress();const auto& identity=evidence.identity();
  Json report{{"schema_version",1},{"kind","c07_native_ranking_export"},{"request",request},{"source_sha256",sha256(sql)},
    {"catalog_sha256",sha256(catalog_text)},{"training_sha256",sha256(training)},{"training_events",events},
    {"training",{{"runtime_mode","maintenance"},{"observation","off"},{"workload","counters"},{"initial_state","empty_all_tables"},
      {"epoch",identity.epoch},{"interval_start",identity.interval_start},{"denominator",evidence.denominator()},
      {"depth_reasons",evidence.depth_reasons()},{"memory_reasons",evidence.memory_reasons()},
      {"weights",std::move(weights)},{"source_cardinalities",std::move(sources)}}},
    {"search",{{"proved_height",proof.height()},{"producer_work",search_status.producer.attempted},{"replay_work",search_status.replay.attempted},
      {"family_exhausted",snapshot.family_exhausted()},{"candidate_count",snapshot.candidate_count()},{"enumeration_work",status.work.attempted},
      {"enumeration_stop",static_cast<unsigned>(status.last_stop)},{"proposed",status.statistics.proposed},{"duplicates",status.statistics.duplicates},
      {"rejected",status.statistics.rejected},{"taller",status.statistics.taller},{"family","exact_seed_residual_seed_normal_form_v1"},
      {"coverage","retained_checked_minimum_height_family_not_global_minimum_cost_search"}}},
    {"setup_timings",{{"admission_ns",elapsed(begin,admitted_at)},{"minimum_height_search_ns",elapsed(admitted_at,proved_at)},
      {"candidate_enumeration_ns",elapsed(proved_at,enumerated_at)},{"basis_initialization_and_training_ns",elapsed(enumerated_at,trained_at)},
      {"evidence_and_selection_ns",elapsed(trained_at,selected_at)}}},
    {"policies",std::move(policies)},{"candidates",std::move(candidates)},
    {"qualification","C05 choices and exact C02 unitless proxies use training only; no nanosecond prediction, held-out optimality, C03/C04/C06 enablement or deployment authority. Alternative trees retain the original certificate witness; the collector independently checks original optimum plus actual candidate height."}};
  const auto encoded=report.dump();require(encoded.size()<=64U*1024U*1024U,"ranking export exceeds64MiB");std::cout<<encoded<<'\n';std::cout.flush();return std::cout?0:1;
}
} // namespace
int main(int argc,char** argv) {try{return run(argc,argv);}catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}}
