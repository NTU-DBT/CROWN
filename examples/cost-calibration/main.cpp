#include <crown/api/error.hpp>
#include <crown/frontend/admission.hpp>
#include <crown/io/catalog.hpp>
#include <crown/io/document.hpp>
#include <crown/ir/digest.hpp>
#include <crown/planner/lower.hpp>
#include <crown/runtime/maintenance_cost.hpp>
#include <algorithm>
#include <charconv>
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/utsname.h>

namespace {
using namespace crown;
namespace model=runtime::cost;
using Clock=std::chrono::steady_clock;
using U64=std::uint64_t;
void require(bool value,std::string_view message){if(!value)throw Error("calibration_failed",std::string(message));}
std::string read(const char* path,std::size_t limit) {
  std::ifstream file(path,std::ios::binary);require(bool(file),"cannot open input file");std::string result;char block[4096];
  while(file){file.read(block,sizeof(block));const auto n=static_cast<std::size_t>(file.gcount());require(n<=limit-result.size(),"input file byte limit");result.append(block,n);}
  require(!file.bad(),"input file read failed");return result;
}
U64 number(const char* text,U64 minimum,U64 maximum) {
  const std::string_view value(text);U64 result=0;const auto parsed=std::from_chars(value.data(),value.data()+value.size(),result);
  require(parsed.ec==std::errc{} && parsed.ptr==value.data()+value.size() && result>=minimum && result<=maximum,"invalid bounded numeric argument");return result;
}
U64 elapsed(Clock::time_point begin,Clock::time_point end) {
  const auto value=std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();require(value>=0,"nonmonotone clock");return static_cast<U64>(value);
}
planner::CandidateSnapshot candidates(const frontend::NormalizedSql& normalized,std::size_t count) {
  planner::SearchOptions options;options.limits.producer.work=10'000'000;options.limits.replay.work=10'000'000;
  auto exact=planner::ExactSearch::create(normalized.core_catalog,normalized.core,options);
  for(std::size_t i=0;i<10000 && !exact.optimum();++i){const auto progress=exact.advance({1000,{}});require(progress.progress.result!=planner::ResultKind::failed,"minimum-height proof failed");}
  require(exact.optimum().has_value(),"minimum-height proof did not finish within calibration search budget");
  auto provider=planner::CandidateProvider::create(*exact.optimum());
  for(std::size_t i=0;i<10000 && provider.candidate_count()<count && !provider.progress().family_exhausted;++i) {
    const auto progress=provider.advance({1000,{}});require(progress.progress.phase!=planner::CandidatePhase::failed,"candidate enumeration failed");
  }
  require(provider.candidate_count()>0,"no checked calibration candidate");return provider.snapshot();
}
io::Json ratio(const std::optional<model::Ratio>& value) {
  if(!value)return nullptr;
  return {{"numerator",value->numerator},{"denominator",value->denominator}};
}
int run(int argc,char** argv) {
  require(argc>=4 && argc<=7,"usage: crown_cost_calibrate QUERY.sql CATALOG.json INPUT.jsonl [EVENTS<=256] [REPETITIONS<=5] [CANDIDATES<=8]");
  const auto event_limit=argc>4?number(argv[4],1,256):64;
  const auto repetitions=argc>5?number(argv[5],1,5):3;
  const auto candidate_limit=argc>6?number(argv[6],1,8):3;
  const auto catalog=io::read_catalog(read(argv[2],16U*1024U*1024U));
  const auto sql=read(argv[1],frontend::ParseLimits{}.source_bytes);const auto input=read(argv[3],8U*1024U*1024U);
  auto admitted=frontend::admit_sql(sql,catalog);require(admitted.status==frontend::AdmissionStatus::admitted,"SQL admission rejected calibration input");
  require(admitted.route!=frontend::AdmissionRoute::constant_empty,"constant-empty operator has no tree-candidate calibration workload");
  const auto snapshot=candidates(*admitted.program,static_cast<std::size_t>(candidate_limit));
  auto account=resource::MemoryAccount::create(64U*1024U*1024U);
  io::Json reports=io::Json::array();
  for(std::size_t index=0;index<snapshot.candidate_count();++index) {
    const auto candidate=*snapshot.candidate(index);const auto plan=planner::lower_normalized(*admitted.program,candidate.tree());
    std::vector<model::FitObservation> observations;io::Json raw=io::Json::array();std::optional<model::Profile> profile;
    U64 records=0,rows=0,snapshot_rows=0;io::Json final_rows;
    for(U64 repetition=0;repetition<repetitions;++repetition) {
      runtime::SessionOptions options;options.delta.mode=runtime::DeltaMode::delta;options.delta.physical.support.observation.mode=runtime::ObservationMode::off;
      auto session=runtime::QuerySession::create(plan,std::make_unique<std::istringstream>(input),options);
      runtime::workload::Options collect;collect.mode=runtime::workload::Mode::counters;session->configure_workload_statistics(collect);session->start();
      const auto initial=model::features(*session->workload_statistics());require(initial.census.has_value(),"initial exact counters unavailable");
      auto before=*initial.census;U64 run_records=0,run_rows=0,run_snapshot_rows=0;
      for(U64 event=0;event<event_limit;++event) {
        const auto begin=Clock::now();if(!session->begin_next())break;
        while(session->step()!=runtime::DeltaStep::prepared){}session->commit();const auto committed=Clock::now();
        // This timer includes owning output temporaries; JSON encoding and sinks are absent.
        U64 output_rows=0;const auto output_begin=Clock::now();while(session->next_output())++output_rows;const auto output_end=Clock::now();
        const auto captured=model::features(*session->workload_statistics());require(captured.census.has_value(),"complete exact event counters unavailable");const auto& after=*captured.census;
        require(after.stamp.owner==before.stamp.owner && after.stamp.reset_generation==before.stamp.reset_generation &&
            after.stamp.configuration_generation==before.stamp.configuration_generation && after.stamp.segment==before.stamp.segment,"counter interval changed during calibration");
        model::FitObservation maintenance,output;maintenance.elapsed_ns=elapsed(begin,committed);output.elapsed_ns=elapsed(output_begin,output_end);
        for(std::size_t c=0;c<model::component_count;++c){require(after.units[c]>=before.units[c],"counter regressed");maintenance.units[c]=after.units[c]-before.units[c];}
        require(maintenance.units[static_cast<std::size_t>(model::Component::base_input)]==1,"timing phase is not one physical input");
        output.units[static_cast<std::size_t>(model::Component::delta_start)]=1;
        output.units[static_cast<std::size_t>(model::Component::delta_row)]=output_rows;
        output.units[static_cast<std::size_t>(model::Component::delta_end)]=1;
        observations.push_back(maintenance);observations.push_back(output);
        raw.push_back({{"repetition",repetition},{"sequence",after.stamp.committed_epoch},{"phase","input_decode_native_prepare_commit"},
          {"elapsed_ns",maintenance.elapsed_ns},{"units",maintenance.units}});
        raw.push_back({{"repetition",repetition},{"sequence",after.stamp.committed_epoch},{"phase","read_committed_output_spool"},
          {"elapsed_ns",output.elapsed_ns},{"units",output.units}});
        // Snapshot construction is timed; destruction of the returned state happens later.
        const auto snapshot_begin=Clock::now();const auto state=session->snapshot();const auto snapshot_end=Clock::now();
        model::FitObservation full;full.elapsed_ns=elapsed(snapshot_begin,snapshot_end);
        full.units[static_cast<std::size_t>(model::Component::snapshot_start)]=1;
        full.units[static_cast<std::size_t>(model::Component::snapshot_row)]=static_cast<U64>(state.rows.size());
        full.units[static_cast<std::size_t>(model::Component::snapshot_end)]=1;observations.push_back(full);
        raw.push_back({{"repetition",repetition},{"sequence",after.stamp.committed_epoch},{"phase","materialize_committed_snapshot"},{"elapsed_ns",full.elapsed_ns},{"units",full.units}});
        run_snapshot_rows+=static_cast<U64>(state.rows.size());
        before=after;++run_records;run_rows+=output_rows;
      }
      session->pause();const auto captured=model::capture(snapshot,index,*session);require(captured.profile.has_value(),"candidate-bound profile capture failed");profile=*captured.profile;
      auto state=session->snapshot();auto current=io::Json::array();
      for(const auto& tuple:state.rows){auto row=io::Json::array();for(const auto& value:tuple.values())row.push_back(io::write_scalar_view(value));current.push_back(std::move(row));}
      if(repetition){require(run_records==records && run_rows==rows && run_snapshot_rows==snapshot_rows && current==final_rows,"repeated replay changed exact state or output count");}
      records=run_records;rows=run_rows;snapshot_rows=run_snapshot_rows;final_rows=std::move(current);
    }
    require(records>0 && profile.has_value(),"no physical inputs measured");
    // Whole-phase fitting attributes cost by model assumption; rank diagnostics remain explicit.
    model::FitOptions fitting;fitting.modes=profile->evidence().captured()->workload().modes();
    planner::ranking::Limits limits;limits.work=20'000'000;
    const std::string context="in_memory_jsonl;volatile_session_no_WAL_no_sink;workload_exact_counters;observation_off;"+std::string(__VERSION__);
    const auto fitted=model::fit(account,context,plan.guarantee().storage_backend,observations,fitting,limits);
    require(fitted.calibration.has_value(),"calibration fitting did not converge within its work/iteration/arithmetic budget");
    const auto& calibration=*fitted.calibration;const auto& summary=*calibration.fit_summary();
    // Fit pools repetitions; the requested demand below is one verified replay horizon.
    std::vector<model::InputDemand> demand;const auto& observed=profile->evidence().captured()->workload();
    for(std::size_t i=0;i<observed.descriptors().size();++i){const auto& descriptor=observed.descriptors()[i];
      if(descriptor.kind==runtime::workload::Kind::physical)demand.push_back({TableId{descriptor.table},descriptor.operation,observed.cells()[i].inputs});}
    model::Request request;request.input=demand;request.output.delta_epochs=records;request.output.delta_rows=rows;
    request.output.snapshot_requests=records;request.output.snapshot_rows_total=snapshot_rows;request.limits.work=20'000'000;
    const std::array<model::Profile,1> profiles{*profile};const auto estimate=model::estimate(account,snapshot,profiles,calibration,request);
    require(estimate.result.has_value(),"in-sample estimate exhausted its resource budget");const auto& price=estimate.result->candidates()[index];
    io::Json coefficients=io::Json::object();
    for(std::size_t c=0;c<model::component_count;++c){const auto& value=calibration.coefficients()[c];
      coefficients[std::string(model::component_name(static_cast<model::Component>(c)))]=value?io::Json{{"rate",ratio(value->nanoseconds_per_unit)},
        {"observed_samples",value->samples},{"observed_units",value->units},{"origin","fitted_linear_assumption"}}:io::Json(nullptr);}
    const auto modes=*fitting.modes;
    reports.push_back({{"candidate",index},{"structural_key",candidate.structural_key()},{"physical_sha256",plan.physical_sha256()},
      {"backend",calibration.backend()},
      {"modes",{{"delta_owner",modes.delta_owner},{"requested_mode",modes.requested_mode==runtime::DeltaMode::delta?"delta":"maintenance"},
        {"resolved_mode",modes.resolved_mode==runtime::DeltaMode::delta?"delta":"maintenance"},
        {"requested_completion",static_cast<U64>(modes.requested_completion)},{"resolved_completion",static_cast<U64>(modes.resolved_completion)},
        {"live_maintenance",static_cast<U64>(modes.live_maintenance)},{"view",static_cast<U64>(modes.view)}}},
      {"records_per_repetition",records},{"delta_rows_per_repetition",rows},{"snapshot_rows_per_repetition",snapshot_rows},{"final_rows",final_rows},
      {"context",context},{"observations",raw},{"coefficients",coefficients},
      {"fit",{{"algorithm","zero_initialized_fixed_order_nonnegative_coordinates_v1"},{"iterations",summary.iterations},
        {"numerical_rank",summary.numerical_rank},{"observed_features",summary.observed_features},{"underdetermined",summary.underdetermined},
        {"rmse_ns_on_calibration_data",summary.root_mean_square_error_ns},{"max_error_ns_on_calibration_data",summary.maximum_absolute_error_ns},
        {"relative_tolerance",fitting.relative_tolerance},{"rank_tolerance",fitting.rank_tolerance},{"ridge_numerator",fitting.ridge.numerator},
        {"ridge_denominator",fitting.ridge.denominator},{"quantization_denominator",fitting.quantization_denominator}}},
      {"replay_horizon_estimate",{{"maintenance_ns",ratio(price.maintenance_ns)},{"delta_ns",ratio(price.delta_ns)},
        {"snapshot_ns",ratio(price.snapshot_ns)},
        {"total_ns",ratio(price.total_ns)},{"issues",price.issues},{"memory_budget_bytes",price.memory_budget_bytes},{"future_memory_unknown",true}}}});
  }
  struct utsname system{};const auto known=uname(&system)==0;
  io::Json report{{"schema_version",1},{"kind","c03_measured_calibration"},{"source_sha256",sha256(sql)},
    {"input_sha256",sha256(input)},
    {"compiler",__VERSION__},{"cpp_standard",__cplusplus},{"pointer_bytes",sizeof(void*)},
    {"kernel",known?system.release:"unknown"},{"machine",known?system.machine:"unknown"},
    {"candidate_count",snapshot.candidate_count()},{"candidate_family_exhausted",snapshot.family_exhausted()},
    {"repetitions",repetitions},{"event_limit",event_limit},{"candidates",reports},
    {"scope","native input/prepare/commit, separate committed-spool reads and committed snapshot materialization; statistics capture/fitting/reporting and returned snapshot destruction excluded; no WAL or sink; calibration-data estimates only"},
    {"qualification","fitted attributions are model assumptions; correlated features are not individually identified; no held-out accuracy or performance guarantee"}};
#ifdef NDEBUG
  report["assertions_enabled"]=false;
#else
  report["assertions_enabled"]=true;
#endif
  const auto text=report.dump();require(text.size()<=16U*1024U*1024U,"calibration report exceeds16MiB");std::cout<<text<<'\n';std::cout.flush();return std::cout?0:1;
}
}
int main(int argc,char** argv){try{return run(argc,argv);}catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}}
