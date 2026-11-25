#include "paper_input.hpp"
#include <crown/runtime/fallback.hpp>
#include <crown/runtime/flat_cyclic.hpp>
#include "flat_driver.hpp"

namespace {
int run(int argc,char** argv) {
  require(argc==3,"usage: paper_native_fallback REQUEST INPUT");
  const auto beginning=Clock::now();
  std::ifstream configuration(argv[1]); require(bool(configuration),"cannot open request");
  const auto request=io::read_json(std::string(std::istreambuf_iterator<char>(configuration),{}));
  require(request.at("schema_version")==1,"unknown request version");
  const bool verify=request.at("command")=="verify";
  require(verify || request.at("command")=="measure","unknown replay command");
  const auto mode=request.at("output_mode").get<std::string>();
  require(mode=="full" || mode=="delta" || mode=="none","unknown output mode");
  const auto& native=request.at("native");
  const auto work=native.at("work_limit").get<std::uint64_t>();
  const auto maximum_events=request.at("limits").at("input_events").get<std::uint64_t>();
  const auto maximum_rows=request.at("limits").at("output_rows").get<std::uint64_t>();
  const auto maximum_bytes=request.at("limits").at("capture_bytes").get<std::uint64_t>();
  const auto& input_program=request.at("program");
  const auto catalog=io::read_catalog(input_program.at("catalog").dump());
  auto admission=frontend::admit_sql(input_program.at("sql").get<std::string>(),catalog);
  require(admission.program.has_value() && admission.status==frontend::AdmissionStatus::cyclic_body,
          "explicit fallback caller requires the actual normalized cyclic SQL");
  const auto& normalized=*admission.program;
  const auto physical=physical_options(native);
  const auto plan=planner::fallback::admit(normalized.core_catalog,normalized.core,physical);
  require(plan.profile().query_class==planner::QueryClass::cyclic,"fallback lost actual cyclic query");
  runtime::fallback::Options options;
  options.sources.support.memory_limit_bytes=native.at("memory_limit_bytes").get<std::uint64_t>();
  options.sources.work_limit=work; options.sources.support.work_limit=work;
  options.gc=paper_gc_options();
  options.answer_changes=mode=="delta";  // none/full: maintain without per-epoch answer changes
  options.recompute={work,native.value("fallback_source_rows",std::uint64_t{100000000}),
                    native.value("fallback_result_rows",std::uint64_t{100000000})};
  const auto compile_ns=nanos(beginning);
  const auto initializing=Clock::now();
  std::optional<runtime::fallback::Runtime> owner;
  std::optional<runtime::FlatCyclicRuntime> flat;
  if(flat_engine_requested()) {
    require(runtime::FlatCyclicRuntime::unsupported(plan.originalcatalog(),plan.query()).empty(),"flat engine cannot run this program");
    flat.emplace(plan.originalcatalog(),plan.query());
  } else owner.emplace(plan,options);
  const bool flat_mode=flat.has_value();
  const std::string engine_name=flat_mode?std::string("flat"):std::string(owner->engine());
  const std::string cyclic_algorithm=flat_mode?std::string("flat"):std::string(owner->algorithm());
  std::vector<std::int64_t> encoded;
  const auto initialize_ns=nanos(initializing);
  std::map<std::string,TableId> tables;
  for(std::size_t i=0;i<catalog.tables.size();++i) tables.emplace(catalog.tables[i].name,TableId{i});
  struct Route { TableId table; std::optional<std::int64_t> source_min,destination_min; };
  std::vector<Route> routes;
  for(const auto& route:request.at("graph_aliases")) {
    const auto found=tables.find(route.at("table").get<std::string>());
    require(found!=tables.end(),"unknown graph alias");
    routes.push_back({found->second,
      route.contains("min_src_exclusive")?std::optional{route.at("min_src_exclusive").get<std::int64_t>()}:std::nullopt,
      route.contains("min_dst_exclusive")?std::optional{route.at("min_dst_exclusive").get<std::int64_t>()}:std::nullopt});
  }
  std::unique_ptr<GzipBuffer> gzip_buffer;
  std::unique_ptr<std::istream> input_owner;
  if(std::string(argv[2]).ends_with(".gz")) {
    gzip_buffer=std::make_unique<GzipBuffer>(argv[2]);
    input_owner=std::make_unique<std::istream>(gzip_buffer.get());
  } else input_owner=std::make_unique<std::ifstream>(argv[2]);
  auto& input=*input_owner; require(bool(input),"cannot open input");
  std::ofstream capture;
  if(verify) { const auto path=request.at("capture_file").get<std::string>();
    require(!std::filesystem::exists(path),"capture already exists"); capture.open(path); require(bool(capture),"cannot create capture"); }
  std::uint64_t sequence{},relation_sequence{},source_sequence{},markers{},input_lines{},rows{},delta_rows{},snapshot_rows{},captured{};
  std::uint64_t decode_ns{},apply_ns{},output_ns{},release_ns{};
  auto frames=Json::array();
  auto emit=[&](const Json& record) { if(!verify) return; auto bytes=record.dump(); bytes+='\n';
    require(bytes.size()<=maximum_bytes-captured,"capture byte limit");capture<<bytes;require(bool(capture),"capture write failed");captured+=bytes.size(); };
  auto count=[&] { require(rows<maximum_rows,"output row limit");++rows; };
  auto snapshot=[&](const char* prefix,bool final) {
    const auto observing=Clock::now();
    std::uint64_t count_rows{};
    emit({{"kind",std::string(prefix)+"begin"},{"sequence",sequence},{"marker",markers}});
    if(flat) {
      FlatCounter counter; counter.owner=nullptr;
      if(verify) counter.capture=[&](SetOperation,Json values){emit({{"kind",std::string(prefix)+"row"},{"sequence",sequence},{"marker",markers},{"values",std::move(values)}});};
      flat_snapshot(*flat,counter); count_rows=counter.rows;
      if(!final) { require(rows+count_rows<=maximum_rows,"output row limit"); rows+=count_rows; snapshot_rows+=count_rows; }
    } else {
    // Streaming snapshot: one result tuple per answer, not a sorted image.
    owner->visit([&](const storage::Tuple& tuple) {
      if(!final) { count();++snapshot_rows; }
      ++count_rows;
      if(verify) emit({{"kind",std::string(prefix)+"row"},{"sequence",sequence},{"marker",markers},{"values",tuple_values(tuple.values())}});
    },{work,options.recompute.source_rows,maximum_rows});
    }
    emit({{"kind",std::string(prefix)+"end"},{"sequence",sequence},{"marker",markers},{"rows",count_rows}});
    if(!final) frames.push_back({{"sequence",sequence},{"marker",markers},{"rows",count_rows}});
    output_ns+=nanos(observing);
    return count_rows;
  };
  const auto looping=Clock::now();
  std::string line;
  const std::string graph_csv="graph_csv";Input event;
  PhysicalSetUpdate update{};std::vector<std::optional<Value>> adapt_scratch;  // reused per relation update
  while(std::getline(input,line)) {
    ++input_lines;const auto decoding=Clock::now();decode(line,tables,graph_csv,TableId{},event);decode_ns+=nanos(decoding);
    if(event.enumerate) {++markers;if(mode=="full") snapshot("snapshot_",false);continue;}
    require(sequence<maximum_events,"input event limit");++sequence;
    std::uint64_t raw_delta{};
    if(mode=="delta" && verify) emit({{"kind","delta_begin"},{"sequence",sequence}});
    for(const auto& route:routes) {
      if(route.source_min && std::get<std::int64_t>(event.values[0])<=*route.source_min) continue;
      if(route.destination_min && std::get<std::int64_t>(event.values[1])<=*route.destination_min) continue;
      ++relation_sequence;
      for(const auto occurrence:normalized.base_routes.at(route.table.value)) {
        const auto applying=Clock::now();
        if(!frontend::adapt_row_into(normalized,occurrence,event.values,update.values,adapt_scratch)) continue;
        if(flat) {
          const TableId target{occurrence.value};
          encoded.resize(flat->arity(target)); flat->encode(target,update.values,encoded.data());
          FlatCounter counter;
          if(verify && mode=="delta") counter.capture=[&](SetOperation operation,Json cells){emit({{"kind","delta_row"},{"sequence",sequence},
              {"relation_sequence",relation_sequence},{"operation",operation==SetOperation::insert?"+":"-"},{"values",std::move(cells)}});};
          ++source_sequence;
          flat->apply(target,event.operation,encoded.data(),flat_sink(*flat,counter));
          apply_ns+=nanos(applying);
          if(mode=="delta") { require(rows+counter.rows<=maximum_rows,"output row limit"); rows+=counter.rows; delta_rows+=counter.rows; raw_delta+=counter.rows; }
          continue;
        }
        update.sequence=++source_sequence; update.table=TableId{occurrence.value}; update.operation=event.operation;
        auto epoch=std::make_optional(owner->apply(update));
        apply_ns+=nanos(applying);const auto observing=Clock::now();
        if(mode=="delta") {
          for(const auto* changes:{&epoch->removed,&epoch->added}) for(const auto& tuple:*changes) {
            count();++delta_rows;++raw_delta;
            if(verify) emit({{"kind","delta_row"},{"sequence",sequence},{"relation_sequence",relation_sequence},
              {"operation",changes==&epoch->added?"+":"-"},{"values",tuple_values(tuple.values())}});
          }
        }
        output_ns+=nanos(observing);const auto releasing=Clock::now();epoch.reset();release_ns+=nanos(releasing);
      }
    }
    if(mode=="delta" && verify) emit({{"kind","delta_end"},{"sequence",sequence},{"rows",raw_delta}});
    if(sequence%10000==0) std::cerr<<"paper fallback accepted "<<sequence<<" physical updates\n";
  }
  require(!input.bad(),"input read failed");const auto loop_ns=nanos(looping);const auto threads=process_threads();const auto gc_report=paper_gc_report(options.gc);
  const auto final_rows=verify?snapshot("final_",true):0;
  if(verify) {capture.flush();require(bool(capture),"capture flush failed");}
  const auto usage=flat?Json{}:memory(owner->account().statistics());
  const auto destroying=Clock::now();owner.reset();flat.reset();const auto teardown_ns=nanos(destroying);
  return report({{"schema_version",1},{"engine",engine_name},{"gc_mode",crown::storage::keyed::gc_mode_name(options.gc.mode)},{"threads",threads},{"gc",gc_report},{"implementation","native_serial_explicit_cyclic_fallback"},{"status","complete"},
    {"case_id",request.at("case_id")},{"output_mode",mode},{"physical_inputs",sequence},{"input_lines",input_lines},
    {"relation_updates",relation_sequence},{"normalized_source_updates",source_sequence},{"enumeration_markers",markers},
    {"output_rows",rows},{"delta_rows",delta_rows},{"snapshot_rows",snapshot_rows},{"capture_bytes",captured},
    {"final_rows",verify?Json(final_rows):Json{}},{"snapshots",std::move(frames)},
    {"compile_ns",compile_ns},{"initialize_ns",initialize_ns},{"loop_wall_ns",loop_ns},{"decode_ns",decode_ns},
    {"apply_ns",apply_ns},{"output_ns",output_ns},{"epoch_release_ns",release_ns},{"teardown_ns",teardown_ns},
    {"memory_before_teardown",usage},{"physical_options",io::write_physical_options(physical)},
    {"query_class","cyclic"},{"fallback_backend",std::string(plan.profile().backend)},{"cyclic_algorithm",cyclic_algorithm},
    {"scope","Actual original cyclic SQL normalized without removing atoms/head/equalities. Exact native fallback over original ordered labelled source updates; source-side endpoint filters retained. Conservative full recomputation/materialized set results, no CROWN tree, GHD algorithm, constant-delay or paper-completion claim. Original Flink baseline unchanged."}});
}
}
int main(int argc,char** argv) {try{return run(argc,argv);}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
