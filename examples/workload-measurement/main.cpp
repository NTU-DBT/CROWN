#include <crown/api/error.hpp>
#include <crown/io/document.hpp>
#include <crown/io/ingest.hpp>
#include <crown/io/oracle.hpp>
#include <crown/io/physical.hpp>
#include <crown/io/tree.hpp>
#include <crown/ir/digest.hpp>
#include <crown/planner/search.hpp>
#include <crown/runtime/delta.hpp>
#include <crown/runtime/workload_statistics.hpp>
#include <algorithm>
#include <cerrno>
#include <chrono>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <limits>
#include <optional>
#include <sched.h>
#include <set>
#include <sstream>
#include <sys/utsname.h>
#include <thread>
#include <unistd.h>

namespace {
using namespace crown;
using io::Json;
using U64=std::uint64_t;
using Clock=std::chrono::steady_clock;
void require(bool value,const char* message) {if(!value)throw Error("measurement_error",message);}
U64 add(U64 a,U64 b) {require(b<=UINT64_MAX-a,"measurement counter overflow");return a+b;}
U64 ns(Clock::time_point a,Clock::time_point b) {
  const auto count=std::chrono::duration_cast<std::chrono::nanoseconds>(b-a).count();
  require(count>=0,"steady clock regressed");return static_cast<U64>(count);
}
U64 number(const Json& object,const char* key,U64 maximum) {
  const auto& value=object.at(key);
  require(value.is_number_integer() && (!value.is_number_integer() || value.is_number_unsigned() || value.get<std::int64_t>()>=0),"expected unsigned request integer");
  const auto result=value.get<U64>();require(result<=maximum,"request integer exceeds collector limit");return result;
}
std::string read(const char* path,std::size_t limit) {
  std::ifstream input(path,std::ios::binary);require(bool(input),"cannot open measurement input");
  std::string text;char block[4096];
  while(input) {input.read(block,sizeof(block));const auto count=static_cast<std::size_t>(input.gcount());
    require(count<=limit-text.size(),"measurement file exceeds byte limit");text.append(block,count);}
  require(!input.bad(),"measurement input read failed");return text;
}
// Cold artifact admission keeps the original proof separate from the actual upper.
struct Artifact {
  PhysicalPlan plan;
  std::optional<std::size_t> original_height;
  bool upper_only{};
};
Artifact artifact(const Json& data) {
  require(data.is_object() && data.at("schema_version").is_number_integer(),"expected compiled workflow version");
  const bool alternative=data.at("schema_version")==2;
  const bool upper_only=data.at("schema_version")==3;
  require((data.at("schema_version")==1 && data.size()==3) ||
    (alternative && data.size()==4 && data.at("height_binding")=="independently_checked_equal_height_upper_v1") ||
    (upper_only && data.size()==4 && data.at("height_binding")=="independently_checked_original_lower_actual_upper_v1"),
    "expected compiled workflow v1, checked candidate v2 or experimental upper v3");
  auto plan=io::read_physical(data.at("physical").dump());const auto& encoded=data.at("height_certificate");
  if(plan.route()==PhysicalRoute::constant_false) {
    require(!alternative && !upper_only && encoded.is_null(),"constant false has an unrelated height claim");
    return {std::move(plan),{},false};
  }
  auto claim=io::read_height_certificate(encoded.dump(),plan.catalog(),plan.query());
  auto replay=planner::CertificateReplay::create(plan.catalog(),plan.query(),std::move(claim));
  static_cast<void>(replay.advance({10'000'000,{}}));const auto checked=replay.checked();
  require(checked.has_value(),"height proof did not complete within collector budget");const auto optimum=checked->optimum();
  require(optimum.has_value(),"height proof does not establish an original optimum");
  const auto height=*plan.validation().native_height;
  require(upper_only?optimum->height()<=height:optimum->height()==height,
    upper_only?"experimental upper is below independently proved optimum":"compiled height differs from independently proved optimum");
  if(!alternative && !upper_only)require(io::write_tree(optimum->upper().tree(),plan.catalog(),plan.query())==
    io::write_tree(plan.tree(),plan.catalog(),plan.query()),"compiled height witness mismatch");
  return {std::move(plan),optimum->height(),upper_only};
}
template<class Values> Json row(const Values& values) {
  auto result=Json::array();for(const auto& value:values)result.push_back(io::write_scalar_view(value));return result;
}
std::set<std::string> rows(const Json& values) {
  std::set<std::string> result;for(const auto& value:values)require(result.insert(value.dump()).second,"duplicate verification row");return result;
}
Json current(runtime::DeltaRuntime& owner) {
  auto result=Json::array();auto cursor=owner.results();while(auto value=cursor.next())result.push_back(row(value->values()));return result;
}
Json memory(const resource::MemoryStatistics& value) {
  return {{"limit_bytes",value.limit_bytes},{"current_requested_bytes",value.current.requested_bytes},
    {"current_payload_bytes",value.current.payload_bytes},{"current_allocations",value.current.allocations},
    {"peak_requested_bytes",value.peak_requested_bytes},{"successful_allocations",value.successful_allocations},{"freed_allocations",value.freed_allocations}};
}
Json arena(const storage::ArenaStatistics& value) {
  return {{"slots",value.slots},{"live_records",value.live_records},{"retained_records",value.retained_records},
    {"pins",value.pins},{"free_slots",value.free_slots},{"exhausted_slots",value.exhausted_slots}};
}
Json storage_statistics(const runtime::PhysicalStorageStatistics& value) {
  return {{"source",arena(value.source)},{"support",arena(value.support)},{"derivation_keys",value.derivation_keys}};
}
const char* availability(runtime::MetricAvailability value) {
  switch(value) {case runtime::MetricAvailability::available:return "available";
    case runtime::MetricAvailability::disabled:return "disabled";case runtime::MetricAvailability::unavailable:return "unavailable";}
  return "unavailable";
}
Json observations(const runtime::ObservationSnapshot& value) {
  auto result=Json::object();for(const auto& descriptor:runtime::observation_registry()) {
    runtime::MetricValue cell;if(value.last)cell=value.last->metric(descriptor.id);
    else if(value.options.mode==runtime::ObservationMode::off)cell.availability=runtime::MetricAvailability::disabled;
    result[std::string(descriptor.name)]={{"value",cell.value},{"availability",availability(cell.availability)},
      {"saturated",cell.saturated},{"unit",descriptor.unit},{"includes",descriptor.includes},{"scope",descriptor.scope}};
  }return result;
}
Json mandatory(const runtime::DeltaMetrics& value) {
  return {{"work",value.work},{"stages",value.stages},{"journal_records",value.journal_records},
    {"view_work",value.view_work},{"candidates",value.candidates},{"accepted",value.accepted},{"rejected",value.rejected},
    {"spool_rows",value.spool_rows},{"spool_bytes",value.spool_bytes},{"finalization_work",value.finalization_work},
    {"replay_preparation_work",value.replay_preparation_work},{"live_rows_copied",value.live_rows_copied}};
}
Json workload(const runtime::workload::Snapshot& snapshot) {
  auto descriptors=Json::array();const auto keys=snapshot.descriptors();const auto cells=snapshot.cells();
  require(keys.size()==cells.size(),"workload descriptor mismatch");
  for(std::size_t i=0;i<keys.size();++i) {const auto& key=keys[i];const auto& cell=cells[i];
    descriptors.push_back({{"kind",static_cast<unsigned>(key.kind)},{"table",key.table},{"scope",key.scope},
      {"operation",static_cast<unsigned>(key.operation)},{"role",static_cast<unsigned>(key.role)},
      {"node",key.node?Json(key.node->value):Json(nullptr)},{"occurrence",key.occurrence?Json(key.occurrence->value):Json(nullptr)},
      {"edge",key.edge?Json(*key.edge):Json(nullptr)},{"index",key.index?Json(key.index->value):Json(nullptr)},
      {"event_operation",key.event_operation?Json(static_cast<unsigned>(*key.event_operation)):Json(nullptr)},
      {"inputs",cell.inputs},{"changed",cell.changed},{"noop",cell.noop},{"visited",cell.visited},
      {"complete_detail_inputs",cell.complete_detail_inputs},{"changes",cell.changes},
      {"zero_to_positive",cell.zero_to_positive},{"positive_to_zero",cell.positive_to_zero},
      {"count",cell.count},{"sum",cell.sum},{"min",cell.min},{"max",cell.max},{"bins",cell.bins},{"saturated",cell.saturated}});
  }
  const auto& metadata=snapshot.metadata();
  return {{"mode",snapshot.options().mode==runtime::workload::Mode::off?"off":"counters"},
    {"detail_availability",static_cast<unsigned>(snapshot.detail_availability())},
    {"metadata",{{"attempts",metadata.attempts},{"committed",metadata.committed},{"aborted",metadata.aborted},
      {"selected",metadata.selected},{"complete",metadata.complete},{"truncated",metadata.truncated},
      {"committed_truncated",metadata.committed_truncated},{"saturated",metadata.saturated},
      {"invalid_descriptor",metadata.invalid_descriptor},{"protocol_error",metadata.protocol_error}}},
    {"committed_epoch",snapshot.stamp().committed_epoch},{"descriptors",std::move(descriptors)}};
}
// External collector writes are not a native durable sink: no WAL or fsync.
// This run-local fd owner is never copied.
struct Sink {
  int descriptor=-1;bool enabled{};U64 delay_us{},bytes{},calls{},byte_limit{};
  Sink(bool active,const std::string& kind,const char* path,U64 delay,U64 limit):enabled(active),delay_us(delay),byte_limit(limit) {
    if(active && kind=="file") {descriptor=::open(path,O_WRONLY|O_CREAT|O_EXCL|O_CLOEXEC,0600);require(descriptor>=0,"cannot exclusively create measurement sink");}
  }
  ~Sink(){if(descriptor>=0)static_cast<void>(::close(descriptor));}
  void consume(const std::string& text) {
    if(!enabled)return;
    require(static_cast<U64>(text.size())<=byte_limit-bytes,"measurement encoded-byte limit exceeded");
    if(delay_us)std::this_thread::sleep_for(std::chrono::microseconds(static_cast<std::chrono::microseconds::rep>(delay_us)));
    std::size_t offset=0;
    while(descriptor>=0 && offset<text.size()) {const auto count=::write(descriptor,text.data()+offset,text.size()-offset);
      if(count<0 && errno==EINTR)continue;
      require(count>0,"measurement sink write failed");
      offset+=static_cast<std::size_t>(count);
    }
    bytes=add(bytes,static_cast<U64>(text.size()));calls=add(calls,1);
  }
  void close() {if(descriptor>=0){const auto value=descriptor;descriptor=-1;require(::close(value)==0,"measurement sink close failed");}}
};
// Host-owned records keep raw calls; their buffers are outside the native query grant.
struct Record {
  U64 sequence{},decode{},native{},setup{},enumerate{},encoding{},sink{},release{},epoch_release{},ack{},active{},diagnostics{},output_rows{};
  std::string phase;std::vector<std::pair<U64,bool>> calls;
  resource::MemoryStatistics bytes;runtime::DeltaMetrics core;runtime::ObservationSnapshot observation;
  runtime::PhysicalStorageStatistics storage{};
  U64 cursor_startup_work{},cursor_result_work{},cursor_termination_work{};
};
int run(int argc,char** argv) {
  require(argc==6,"usage: crown_measure_workload COMPILED.json INPUT.jsonl REQUEST.json EXPECTED.json|- SINK_PATH");
  const auto request=io::read_json(read(argv[3],1024U*1024U));
  const std::set<std::string> fields{"schema_version","command","output_mode","codec","sink","sink_delay_us","observation","workload_counters","memory_limit_bytes","max_events","max_output_calls","max_encoded_bytes","phases","label","preflight_receipt_sha256"};
  require(request.is_object() && request.size()==fields.size(),"measurement request field mismatch");
  for(const auto& item:request.items())require(fields.contains(item.key()),"unknown measurement request field");
  require(request.at("schema_version").is_number_integer() && request.at("schema_version")==1,"unknown request version");
  require(request.at("label").is_string() && request.at("label").get_ref<const std::string&>().size()<=256,"invalid run label");
  // This checks digest shape only; the controlled runner verifies the receipt linkage.
  const auto& preflight=request.at("preflight_receipt_sha256");
  require(preflight.is_null() || (preflight.is_string() && preflight.get_ref<const std::string&>().size()==64 &&
    std::all_of(preflight.get_ref<const std::string&>().begin(),preflight.get_ref<const std::string&>().end(),[](char c){return (c>='0' && c<='9') || (c>='a' && c<='f');})),"invalid preflight receipt digest");
  const auto command=request.at("command").get<std::string>();const bool verify=command=="verify";
  require(verify || command=="measure","invalid collector command");
  const auto mode=request.at("output_mode").get<std::string>();const auto codec=request.at("codec").get<std::string>();const auto sink_kind=request.at("sink").get<std::string>();
  require(mode=="maintenance" || mode=="snapshot" || mode=="delta","unknown output mode");
  require(codec=="none" || codec=="jsonl","unknown output codec");require(sink_kind=="discard" || sink_kind=="file","unknown collector sink");
  const auto max_events=number(request,"max_events",4096);const auto max_calls=number(request,"max_output_calls",1'000'000);
  const auto encoded_limit=number(request,"max_encoded_bytes",1024ULL*1024ULL*1024ULL);
  const auto memory_limit=number(request,"memory_limit_bytes",4ULL*1024ULL*1024ULL*1024ULL);
  const auto delay=number(request,"sink_delay_us",100000);require(memory_limit>0 && max_calls>0,"zero measurement resource grant");
  const auto phases=request.at("phases").get<std::vector<std::string>>();require(phases.size()<=max_events,"too many phase labels");
  for(const auto& phase:phases)require(!phase.empty() && phase.size()<=64,"invalid input phase label");
  auto binding_request=request;binding_request.erase("command");binding_request.erase("preflight_receipt_sha256");
  auto now=[&](){return verify?Clock::time_point{}:Clock::now();};
  const auto files_begin=now();const auto artifact_text=read(argv[1],16U*1024U*1024U);const auto input_text=read(argv[2],8U*1024U*1024U);const auto files_end=now();
  const auto artifact_begin=now();auto compiled=artifact(io::read_json(artifact_text));auto& plan=compiled.plan;const auto artifact_end=now();
  Json expected;if(verify){require(std::string_view(argv[4])!="-","verification requires independent expected results");expected=io::read_json(read(argv[4],64U*1024U*1024U));require(expected.at("epochs").size()==phases.size(),"oracle/phase count mismatch");}
  runtime::DeltaOptions options;options.mode=mode=="delta"?runtime::DeltaMode::delta:runtime::DeltaMode::maintenance;
  options.physical.support.memory_limit_bytes=memory_limit;
  const auto observe=request.at("observation").get<std::string>();
  if(observe=="off")options.physical.support.observation.mode=runtime::ObservationMode::off;
  else if(observe=="counters")options.physical.support.observation.mode=runtime::ObservationMode::counters;
  else if(observe=="timed")options.physical.support.observation.mode=runtime::ObservationMode::timed;
  else throw Error("measurement_error","unknown observation mode");
  require(request.at("workload_counters").is_boolean(),"invalid workload collector flag");
  const auto initialize_begin=now();
  auto owner=std::make_unique<runtime::DeltaRuntime>(plan,options);std::istringstream input(input_text);
  auto reader=std::make_unique<io::EventReader>(input,owner->plan());
  runtime::workload::Options collect;collect.mode=request.at("workload_counters").get<bool>()?runtime::workload::Mode::counters:runtime::workload::Mode::off;
  owner->configure_workload_statistics(collect);
  Sink sink(!verify,sink_kind,argv[5],delay,encoded_limit);const auto initialize_end=now();
  if(verify)require(rows(current(*owner))==rows(expected.at("initial_rows")),"initial native result differs from independent oracle");
  const auto initial_memory=owner->accounted_memory_statistics();std::vector<Record> records;records.reserve(phases.size());
  U64 output_calls=0,output_total=0;const auto loop_begin=now();U64 eof_decode=0;
  for(;;) {
    Record record;const auto begin=now();const auto* event=reader->peek();const auto decoded=now();record.decode=ns(begin,decoded);
    if(!event){eof_decode=record.decode;break;}
    require(records.size()<max_events && records.size()<phases.size(),"measurement event/phase limit exceeded");
    record.sequence=event->update.sequence;record.phase=phases[records.size()];
    // The reader view stays cached until acknowledgment; begin_view imports owned state.
    std::optional<runtime::DeltaRuntime::PendingEpoch> pending{owner->begin_view(event->update)};
    while(pending->step()!=runtime::DeltaStep::prepared){}
    std::optional<runtime::DeltaRuntime::Epoch> epoch{pending->commit()};pending.reset();
    const auto committed=now();record.native=ns(decoded,committed);record.core=epoch->metrics();
    Json actual_delta=Json::array();std::optional<runtime::SupportRuntime::ResultCursor> cursor;
    if(mode=="snapshot"){const auto start=now();cursor.emplace(owner->results());record.setup=ns(start,now());}
    if(mode!="maintenance")for(;;) {
      require(output_calls<max_calls,"measurement output-call limit exceeded");++output_calls;
      const auto call_begin=now();std::optional<storage::Tuple> value;std::optional<runtime::SignedResult> signed_value;
      if(cursor)value=cursor->next();else signed_value=epoch->next();const auto call_end=now();
      const bool present=value.has_value() || signed_value.has_value();const auto call_ns=ns(call_begin,call_end);
      record.enumerate=add(record.enumerate,call_ns);record.calls.emplace_back(call_ns,present);if(!present)break;
      record.output_rows=add(record.output_rows,1);const auto& tuple=value?*value:signed_value->tuple;
      if(verify && mode=="delta")actual_delta.push_back({{"operation",signed_value->operation==SetOperation::insert?"insert":"delete"},{"values",row(tuple.values())}});
      std::string encoded;
      if(codec=="jsonl" && !verify) {const auto start=now();Json output{{"sequence",record.sequence},{"values",row(tuple.values())}};
        if(mode=="delta")output["operation"]=signed_value->operation==SetOperation::insert?"insert":"delete";
        encoded=output.dump()+"\n";record.encoding=add(record.encoding,ns(start,now()));}
      if(!verify){const auto start=now();sink.consume(encoded);record.sink=add(record.sink,ns(start,now()));}
      const auto released=now();value.reset();signed_value.reset();record.release=add(record.release,ns(released,now()));
    }
    if(cursor){const auto& metrics=cursor->metrics();record.cursor_startup_work=metrics.startup.work;record.cursor_result_work=metrics.results.work;record.cursor_termination_work=metrics.termination.work;
      const auto released=now();cursor.reset();record.release=add(record.release,ns(released,now()));}
    // Finish committed-output ownership before publishing accepted reader progress.
    const auto epoch_released=now();epoch.reset();record.epoch_release=ns(epoch_released,now());
    const auto accepted=now();reader->acknowledge();const auto active_end=now();record.ack=ns(accepted,active_end);record.active=ns(begin,active_end);
    if(verify){const auto& frame=expected.at("epochs").at(records.size());require(frame.at("sequence")==record.sequence,"oracle/native sequence mismatch");
      require(rows(current(*owner))==rows(frame.at("current_rows")),"native current rows differ from independent oracle");
      if(mode=="delta")require(rows(actual_delta)==rows(frame.at("signed_delta")),"native signed delta differs from independent oracle");}
    // Slot counts are explicit tool diagnostics after the timed epoch and ack.
    // They visit logical tables/nodes, not every historical arena slot.
    const auto diagnostic=now();record.bytes=owner->accounted_memory_statistics();record.observation=owner->observations();
    record.storage=owner->storage_statistics();record.diagnostics=ns(diagnostic,now());
    output_total=add(output_total,record.output_rows);records.push_back(std::move(record));
  }
  const auto loop_end=now();require(records.size()==phases.size(),"input ended before declared phase horizon");
  const auto final_memory=owner->accounted_memory_statistics();const auto actual_mode=owner->mode()==runtime::DeltaMode::delta?"delta":"maintenance";
  const auto backend=std::string(owner->plan().guarantee().storage_backend);const auto physical_sha=std::string(owner->plan().physical_sha256());
  const auto progress=reader->progress().export_value();
  const auto binding=sha256(physical_sha+sha256(input_text)+binding_request.dump());
  Json report{{"schema_version",2},{"kind",verify?"native_workload_verification":"native_workload_measurement"},
    {"request",request},{"binding_sha256",binding},{"physical_sha256",physical_sha},{"artifact_sha256",sha256(artifact_text)},
    {"input_sha256",sha256(input_text)},{"output_mode",mode},{"runtime_mode",actual_mode},{"backend",backend},
    {"records",records.size()},{"output_rows",output_total},{"sequence",progress.sequence},{"source_positions",progress.source_positions}};
  if(compiled.upper_only) {
    const auto actual=*plan.validation().native_height;const auto original=*compiled.original_height;
    report["experimental_height"]={{"status","checked_upper_only"},{"original_minimum_height",original},
      {"actual_native_height",actual},{"height_gap",actual-original}};
  }
  if(verify){report["verified"]=true;std::cout<<report.dump()<<'\n';std::cout.flush();return std::cout?0:1;}
  // The final memory sample precedes this diagnostic export and explicit teardown.
  const auto final_diagnostics_begin=now();auto workload_report=workload(owner->workload_statistics());
  const auto final_diagnostics=ns(final_diagnostics_begin,now());const auto sink_close_begin=now();sink.close();const auto sink_close=ns(sink_close_begin,now());
  auto frames=Json::array();
  for(const auto& record:records){auto calls=Json::array();for(const auto& call:record.calls)calls.push_back({{"nanoseconds",call.first},{"returned_row",call.second}});
    frames.push_back({{"sequence",record.sequence},{"phase",record.phase},{"decode_ns",record.decode},{"native_prepare_commit_ns",record.native},
      {"output_setup_ns",record.setup},{"output_next_ns",record.enumerate},{"encoding_ns",record.encoding},{"sink_write_wait_ns",record.sink},
      {"output_release_ns",record.release},{"epoch_release_ns",record.epoch_release},{"input_ack_ns",record.ack},{"event_active_ns",record.active},{"diagnostics_ns",record.diagnostics},
      {"output_rows",record.output_rows},{"output_calls",std::move(calls)},{"memory",memory(record.bytes)},
      {"storage",storage_statistics(record.storage)},
      {"mandatory_at_commit",mandatory(record.core)},{"operator_metrics",observations(record.observation)},
      {"cursor_work",{{"startup",record.cursor_startup_work},{"results",record.cursor_result_work},{"termination",record.cursor_termination_work}}}});
  }
  const auto teardown_begin=now();reader.reset();owner.reset();const auto teardown=ns(teardown_begin,now());
  struct utsname machine{};require(::uname(&machine)==0,"cannot read machine context");
  report["timings"]={{"file_read_ns",ns(files_begin,files_end)},{"artifact_validation_ns",ns(artifact_begin,artifact_end)},
    {"initialization_ns",ns(initialize_begin,initialize_end)},{"loop_wall_ns",ns(loop_begin,loop_end)},{"eof_decode_ns",eof_decode},
    {"final_diagnostics_ns",final_diagnostics},{"sink_close_ns",sink_close},{"teardown_ns",teardown}};
  report["memory_initial"]=memory(initial_memory);report["memory_final"]=memory(final_memory);report["epochs"]=std::move(frames);
  report["workload"]=std::move(workload_report);report["sink"]={{"kind",sink_kind},{"calls",sink.calls},{"bytes",sink.bytes},{"requested_delay_us_per_record",delay}};
  report["environment"]={{"collector_compiler",__VERSION__},{"cplusplus",__cplusplus},{"pointer_bits",8*sizeof(void*)},
    {"kernel",machine.release},{"machine",machine.machine},{"clock","std::chrono::steady_clock"},{"clock_is_steady",Clock::is_steady}};
  auto cpus=Json::array();
#if defined(__linux__)
  cpu_set_t affinity;CPU_ZERO(&affinity);require(::sched_getaffinity(0,sizeof(affinity),&affinity)==0,"cannot read actual CPU affinity");
  for(std::size_t cpu=0;cpu<static_cast<std::size_t>(CPU_SETSIZE);++cpu)if(CPU_ISSET(cpu,&affinity))cpus.push_back(cpu);
#else
  // No affinity API on this platform: report every online CPU.
  for(unsigned cpu=0;cpu<std::thread::hardware_concurrency();++cpu)cpus.push_back(cpu);
#endif
  report["environment"]["actual_affinity"]=std::move(cpus);
  std::ifstream status("/proc/self/status");std::string status_line;
  while(std::getline(status,status_line))if(status_line.starts_with("Threads:"))report["environment"]["actual_threads"]=std::stoull(status_line.substr(8));
  report["runtime_options"]={{"delta_work_limit",options.work_limit?Json(*options.work_limit):Json(nullptr)},
    {"spool_row_limit",options.spool_row_limit},{"spool_byte_limit",options.spool_byte_limit},{"input_format","jsonl"},
    {"initial_state","empty_all_tables"},{"memory_scope","shared_native_runtime_program_and_EventReader_account"},
    {"annotation_semantics","not_enabled_exact_set_core"}};
  report["scope"]="volatile native DeltaRuntime plus funded EventReader; empty initial state; JSONL input buffered before loop; no WAL/checkpoint/fsync; external collector encoding and POSIX-write/discard sink; report encoding excluded";
  report["qualification"]="raw collector record requires the controlled runner's prior correctness/build/environment/repetition packet; account bytes exclude caller/compiler/report/input-stream DTOs and are not RSS; peak is cumulative; storage slots are actual source/support arena counts, not visits or allocator bytes; native optional encoding/sink hooks are unused; loop wall includes tool diagnostics/record storage; no speedup claim";
  const auto encoded=report.dump();require(encoded.size()<=64U*1024U*1024U,"collector report exceeds64MiB");std::cout<<encoded<<'\n';std::cout.flush();return std::cout?0:1;
}
} // namespace
int main(int argc,char** argv) {try{return run(argc,argv);}catch(const std::exception& error){std::cerr<<error.what()<<'\n';return 1;}}
