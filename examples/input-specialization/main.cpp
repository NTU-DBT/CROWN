#include <crown/frontend/admission.hpp>
#include <crown/io/catalog.hpp>
#include <crown/io/ingest.hpp>
#include <crown/io/physical.hpp>
#include <crown/io/tree.hpp>
#include <crown/ir/digest.hpp>
#include <crown/ir/program.hpp>
#include <crown/planner/lower.hpp>
#include <crown/planner/oracle.hpp>
#include <crown/runtime/delta.hpp>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <optional>
#include <set>
#include <sstream>

namespace {
using namespace crown;
using io::Json;
using U64=std::uint64_t;
using Clock=std::chrono::steady_clock;
void require(bool value,const char* message) {if(!value)throw Error("input_specialization",message);}
U64 integer(const Json& value,U64 maximum) {
  require(value.is_number_integer() && (value.is_number_unsigned() || value.get<std::int64_t>()>=0),"expected a finite unsigned integer");
  const auto result=value.get<U64>();require(result<=maximum,"input specialization grant exceeded");return result;
}
std::string read(const char* path,std::size_t maximum) {
  std::ifstream stream(path,std::ios::binary);require(bool(stream),"cannot read specialization input");
  std::string text;char block[4096];
  while(stream) {stream.read(block,sizeof(block));const auto count=static_cast<std::size_t>(stream.gcount());
    require(count<=maximum-text.size(),"specialization file exceeds byte grant");text.append(block,count);}
  require(!stream.bad(),"specialization input read failed");return text;
}
void closed(const Json& value,const std::set<std::string>& fields) {
  require(value.is_object() && value.size()==fields.size(),"closed specialization request fields differ");
  for(const auto& field:value.items())require(fields.contains(field.key()),"unknown specialization request field");
}
Json row(storage::TupleValuesView values) {
  auto result=Json::array();for(const auto value:values)result.push_back(io::write_scalar_view(value));return result;
}
Json current(runtime::DeltaRuntime& owner,U64 work,U64& records,U64 limit,bool verify) {
  auto result=Json::array();auto cursor=owner.results({work});
  while(auto tuple=cursor.next()) {require(records<limit,"specialization output record grant exhausted");++records;
    if(verify)result.push_back(row(tuple->values()));}
  return result;
}
Json memory(const resource::MemoryStatistics& value) {
  return {{"limit_bytes",value.limit_bytes},{"current_requested_bytes",value.current.requested_bytes},
    {"peak_requested_bytes",value.peak_requested_bytes},{"current_allocations",value.current.allocations}};
}
Json work(storage::IndexWork value) {
  return {{"structural_steps",value.structural_steps},{"scalar_fields",value.scalar_fields},{"scalar_bytes",value.scalar_bytes},
    {"pointer_slots",value.pointer_slots},{"link_actions",value.link_actions}};
}
int run(int argc,char** argv) {
  const auto request_begin=Clock::now();
  require(argc==5,"usage: crown_input_specialization SQL CATALOG BOUND_INPUT.jsonl REQUEST.json");
  const auto request=io::read_json(read(argv[4],1024*1024));
  closed(request,{"schema_version","command","case_id","execution","physical_options","preparation","memory_limit_bytes", "work_limit",
      "warmup_passes","measured_passes","max_events","max_output_records","max_output_bytes","phases"});
  require(integer(request.at("schema_version"),1)==1,"unknown specialization request version");
  const auto command=request.at("command").get<std::string>();const bool verify=command=="verify";
  require(verify || command=="measure","unknown specialization command");
  const auto execution=request.at("execution").get<std::string>();
  require(execution=="interpreted_v1" || execution=="threaded_v1","unknown input execution mode");
  require(request.at("case_id").is_string() && request.at("case_id").get_ref<const std::string&>().size()<=256,"invalid specialization case label");
  closed(request.at("preparation"),{"work","instructions"});
  program::InputPreparationLimits preparation{integer(request.at("preparation").at("work"),10000000),
      static_cast<std::size_t>(integer(request.at("preparation").at("instructions"),100000))};
  const auto memory_limit=integer(request.at("memory_limit_bytes"),1024ULL*1024*1024);
  require(memory_limit>=1024*1024,"specialization account grant below one MiB");
  const auto step_work=integer(request.at("work_limit"),1000000000);
  const auto warmups=integer(request.at("warmup_passes"),5),repetitions=integer(request.at("measured_passes"),10);
  require(repetitions>0,"specialization requires a measured owner");
  const auto max_events=integer(request.at("max_events"),4096),max_records=integer(request.at("max_output_records"),1000000);
  const auto max_bytes=integer(request.at("max_output_bytes"),64ULL*1024*1024);
  require(max_records>0 && max_bytes>0,"empty specialization output grant");
  const auto phases=request.at("phases").get<std::vector<std::string>>();require(phases.size()<=max_events,"too many specialization phases");
  for(const auto& phase:phases)require(!phase.empty() && phase.size()<=64,"invalid specialization phase");
  const auto now=[&](){return verify?Clock::time_point{}:Clock::now();};
  const auto elapsed=[](Clock::time_point begin,Clock::time_point end) {
    const auto value=std::chrono::duration_cast<std::chrono::nanoseconds>(end-begin).count();
    require(value>=0,"specialization clock regressed");return static_cast<U64>(value);
  };
  const auto ns=[&](Clock::time_point begin,Clock::time_point end)->Json {
    return verify?Json{}:Json(elapsed(begin,end));
  };
  const auto sql_text=read(argv[1],1024*1024),catalog_text=read(argv[2],16*1024*1024);
  const auto input_text=read(argv[3],8*1024*1024);const auto read_ns=ns(request_begin,now());
  const auto compiling=now();const auto catalog=io::read_catalog(catalog_text);
  auto admitted=frontend::admit_sql(sql_text,catalog);
  require(admitted.status==frontend::AdmissionStatus::admitted && admitted.program.has_value(),"specialization SQL not admitted");
  FreeConnexTree tree;
  if(admitted.route!=frontend::AdmissionRoute::constant_empty) {
    const auto optimum=planner::minimum_tree(admitted.program->core_catalog,admitted.program->core);
    require(optimum.status==planner::OracleStatus::proven_minimum && optimum.tree.has_value(),"specialization source lacks genuine optimum");
    tree=*optimum.tree;
  }
  const auto physical=io::read_physical_options(request.at("physical_options").dump());
  const auto lowered=planner::lower_normalized(*admitted.program,tree,physical);
  const auto compiler_account=resource::MemoryAccount::create(memory_limit);
  const auto basis=CompiledProgram::compile(compiler_account,lowered);const auto shared_ns=ns(compiling,now());
  const auto preparing=now();const auto execution_account=resource::MemoryAccount::create(memory_limit);
  const storage::IndexWork base_limit=physical.indexed_storage?physical.indexed_storage->per_operation:
      storage::IndexWork{100000000,100000000,1024ULL*1024*1024,100000000,100000000};
  storage::IndexWorkAllowance base_work(base_limit,true);const auto before_base=base_work.remaining();
  const auto compiled=execution=="threaded_v1"?CompiledProgram::prepare_inputs(execution_account,basis,preparation,&base_work):
      CompiledProgram::freeze(execution_account,basis,&base_work);
  const auto preparation_ns=ns(preparing,now());const auto remaining=base_work.remaining();
  const storage::IndexWork total_preparing{before_base.structural_steps-remaining.structural_steps,before_base.scalar_fields-remaining.scalar_fields,
    before_base.scalar_bytes-remaining.scalar_bytes,before_base.pointer_slots-remaining.pointer_slots,before_base.link_actions-remaining.link_actions};
  const auto usage=compiled.input_preparation();
  runtime::DeltaOptions options;options.mode=runtime::DeltaMode::delta;options.view=runtime::ResultView::sql;
  options.physical.support.memory_limit_bytes=memory_limit;options.work_limit=step_work;
  auto passes=Json::array();U64 captured=0;
  for(U64 pass=0;pass<warmups+repetitions;++pass) {
    const auto initializing=now();auto owner=std::make_optional<runtime::DeltaRuntime>(compiled,options);
    std::istringstream input(input_text);io::InputOptions input_options;input_options.limits.records=max_events;
    input_options.limits.total_bytes=input_text.size();auto reader=std::make_optional<io::EventReader>(input,owner->plan(),input_options);
    U64 records=0;auto initial=current(*owner,step_work,records,max_records,verify);
    const auto initial_records=records;
    if(verify) {const auto bytes=initial.dump().size();require(bytes<=max_bytes-captured,"specialization initial capture exceeds grant");captured+=bytes;}
    const auto initialize_ns=ns(initializing,now());auto epochs=Json::array();const auto looping=now();
    while(const auto* event=reader->peek()) {
      const auto index=epochs.size();require(index<phases.size() && index<max_events,"specialization input horizon exceeded");
      const auto applying=now();std::optional<runtime::DeltaRuntime::Epoch> epoch;
      {auto pending=owner->begin_view(event->update);while(pending.step()!=runtime::DeltaStep::prepared){}
        epoch.emplace(pending.commit());}
      const auto apply_ns=ns(applying,now());
      const auto observing=now();auto delta=Json::array();U64 emitted=0;
      while(auto change=epoch->next()) {
        require(records<max_records,"specialization output record grant exhausted");++records;++emitted;
        if(verify)delta.push_back({{"operation",change->operation==SetOperation::insert?"insert":"delete"},{"values",row(change->tuple.values())}});
      }
      const auto delta_done=now();const auto metrics=epoch->metrics();epoch.reset();const auto released=now();
      const auto release_ns=ns(delta_done,released);
      const auto before_snapshot=records;auto rows=current(*owner,step_work,records,max_records,verify);
      const auto snapshot_records=records-before_snapshot;
      const auto output_ns=verify?Json{}:Json(elapsed(observing,delta_done)+elapsed(released,now()));
      const auto sequence=event->update.sequence;reader->acknowledge();
      Json actual=verify?Json{{"rows",std::move(rows)},{"delta",std::move(delta)}}:Json{};
      if(verify) {const auto bytes=actual.dump().size();require(bytes<=max_bytes-captured,"specialization capture bytes exceeded");captured+=bytes;}
      epochs.push_back({{"sequence",sequence},{"physical_input_end",index+1},{"phase",phases[index]},
          {"apply_ns",apply_ns},{"output_ns",output_ns},{"release_ns",release_ns},{"output_records",emitted},
          {"delta_records",emitted},{"snapshot_records",snapshot_records},
          {"native_work",metrics.work},{"actual",std::move(actual)}});
    }
    const auto loop_ns=ns(looping,now());require(epochs.size()==phases.size(),"specialization input ended before declared horizon");
    const auto accepted=reader->progress().sequence;const auto native=memory(owner->accounted_memory_statistics());
    const auto admitted_mode=std::string(owner->plan().input_execution_key());const auto admitted_usage=owner->plan().input_preparation();
    const auto destroying=now();reader.reset();owner.reset();const auto teardown_ns=ns(destroying,now());
    passes.push_back({{"warmup",pass<warmups},{"initialize_ns",initialize_ns},{"loop_wall_ns",loop_ns},{"teardown_ns",teardown_ns},
      {"initial_rows",verify?std::move(initial):Json{}},{"initial_output_records",initial_records},
      {"accepted_sequence",accepted},{"execution_key",admitted_mode},
      {"owner_prepared_instructions",admitted_usage.instructions},{"owner_extra_table_bytes",admitted_usage.metadata_bytes},
      {"output_records",records},{"native_memory_before_teardown",native},{"epochs",std::move(epochs)}});
  }
  const auto base_freeze=execution=="threaded_v1"?usage.base_freeze_work:total_preparing;
  Json report{{"schema_version",1},{"kind","b04_input_specialization_report_v1"},{"case_id",request.at("case_id")},
    {"command",command},{"execution",execution},{"execution_key",compiled.input_execution_key()},{"request",request},
    {"sql_sha256",sha256(sql_text)},{"catalog_sha256",io::input_catalog_sha256(catalog)},{"input_sha256",sha256(input_text)},
    {"physical_sha256",compiled.physical_sha256()},{"source_sha256",compiled.physical_source_sha256()},
    {"tree",io::write_tree(tree,admitted.program->core_catalog,admitted.program->core)},
    {"constant_operator",admitted.route==frontend::AdmissionRoute::constant_empty},
    {"physical_options",io::write_physical_options(physical)},{"read_request_ns",read_ns},{"shared_program_ns",shared_ns},
    {"execution_prepare_ns",preparation_ns},{"preparation",{{"work",usage.work},{"instructions",usage.instructions},
      {"metadata_bytes",usage.metadata_bytes},{"base_freeze_work",work(base_freeze)},{"total_preparing_index_work",work(total_preparing)}}},
    {"compiler_memory",memory(compiler_account.statistics())},{"execution_program_memory",memory(execution_account.statistics())},
    {"output_protocol","signed_delta_and_full_snapshot_each_input_v1"},
    {"output_record_units",{{"epoch.output_records","signed delta records"},{"epoch.snapshot_records","full snapshot rows"},
      {"pass.output_records","initial snapshot plus every signed delta and full snapshot row"}}},
    {"cache_policy","none;immutable source reused across fresh pass owners;each owner funds its own admitted program"},
    {"passes",std::move(passes)},
    {"scope","same SQL/program/tree/storage/CP/journal/output pipeline;both commands drain signed delta and full snapshot after every input;initial snapshot is included in initialize;input-expression interpretation versus prebound data-program workers;no per-query machine code/JIT,global cache,full executor compiler or predetermined speedup;prepare timer includes receiving base freeze;whole-child wall/RSS include compiler,warmups,report and teardown"}};
  const auto encoded=report.dump();require(encoded.size()<=64ULL*1024*1024,"specialization report exceeds64MiB");
  std::cout<<encoded<<'\n';std::cout.flush();return std::cout?0:1;
}
} // namespace
int main(int argc,char** argv) {
  try{return run(argc,argv);}catch(const std::exception& failure){std::cerr<<failure.what()<<'\n';return 1;}
}
