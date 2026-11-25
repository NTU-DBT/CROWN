#include "paper_input.hpp"
#include "flat_driver.hpp"
#include <charconv>
#include <filesystem>
#include <fstream>
#include <map>
#include <string_view>
#include <zlib.h>
#include <memory>

namespace {

int run(int argc,char** argv) {
  require(argc==3,"usage: paper_native REQUEST.json INPUT");
  const auto starting=Clock::now();
  std::ifstream configuration(argv[1]); require(bool(configuration),"cannot open paper request");
  const auto request=io::read_json(std::string(std::istreambuf_iterator<char>(configuration),{}));
  require(request.at("schema_version")==1,"unknown paper request version");
  const bool verify=request.at("command")=="verify";
  require(verify || request.at("command")=="measure","unknown paper replay command");
  const auto mode=request.at("output_mode").get<std::string>();
  require(mode=="delta" || mode=="full" || mode=="none","unknown paper output mode");
  const bool full_at_markers=request.value("full_at_markers",mode=="full");
  const auto read_ns=nanos(starting);
  const auto compiling=Clock::now();
  const auto compiled=compile_set(request);
  auto options=delta_options(request.at("native"));
  if(std::getenv("CROWN_OBS_OFF")) options.physical.support.observation.mode=runtime::ObservationMode::off;
  options.gc=paper_gc_options();
  options.mode=mode=="delta" ? runtime::DeltaMode::delta : runtime::DeltaMode::maintenance;
  const auto compile_ns=nanos(compiling);
  const auto initializing=Clock::now();
  std::optional<runtime::DeltaRuntime> owner;
  std::optional<runtime::FlatRuntime> flat;
  if(flat_engine_requested()) {
    const auto problem=runtime::FlatRuntime::unsupported(compiled.program);
    require(problem.empty(),"flat engine cannot run this program");
    flat.emplace(compiled.program,runtime::FlatOptions{mode=="delta"});
  } else owner.emplace(compiled.program,options);
  const bool flat_mode=flat.has_value();
  const std::string engine_name=flat_mode?"flat":std::string(owner->profile().engine);
  std::vector<std::int64_t> encoded;
  const auto initialize_ns=nanos(initializing);
  std::map<std::string,TableId> tables;
  for (std::size_t i=0;i<compiled.catalog.tables.size();++i) tables.emplace(compiled.catalog.tables[i].name,TableId{i});
  const auto graph_name=request.value("graph_table",std::string("graph"));
  const auto graph=tables.find(graph_name);
  const auto format=request.at("input_format").get<std::string>();
  const bool routed=request.value("routing",std::string("physical_source"))=="original_flink_graph_aliases";
  struct Route { TableId table; std::optional<std::int64_t> threshold; };
  std::vector<Route> routes;
  if(routed) {
    require(format=="graph_csv","original graph routing requires graph CSV");
    for(const auto& route:request.at("graph_aliases")) {
      const auto found=tables.find(route.at("table").get<std::string>());
      require(found!=tables.end(),"unknown labelled graph relation");
      std::optional<std::int64_t> threshold;
      if(route.contains("min_dst_exclusive") && !route.at("min_dst_exclusive").is_null())
        threshold=route.at("min_dst_exclusive").get<std::int64_t>();
      routes.push_back({found->second,threshold});
    }
    require(!routes.empty(),"empty original graph routing");
  }
  std::map<std::string,std::vector<Route>> tag_routes;
  if(format=="tagged_csv") {
    for(const auto& [tag,values]:request.at("tag_routes").items()) for(const auto& value:values) {
      const auto found=tables.find(value.at("table").get<std::string>());
      require(found!=tables.end(),"unknown tagged destination table");
      std::optional<std::int64_t> threshold;
      if(value.contains("min_dst_exclusive") && !value.at("min_dst_exclusive").is_null())
        threshold=value.at("min_dst_exclusive").get<std::int64_t>();
      tag_routes[tag].push_back({found->second,threshold});
    }
  }
  require(routed || format!="graph_csv" || graph!=tables.end(),"missing graph source table");
  std::unique_ptr<GzipBuffer> gzip_buffer;
  std::unique_ptr<std::istream> input_owner;
  if(std::string(argv[2]).ends_with(".gz")) {
    gzip_buffer=std::make_unique<GzipBuffer>(argv[2]);
    input_owner=std::make_unique<std::istream>(gzip_buffer.get());
  } else input_owner=std::make_unique<std::ifstream>(argv[2]);
  auto& input=*input_owner;
  require(bool(input),"cannot open paper stream");
  const auto maximum_events=request.at("limits").at("input_events").get<std::uint64_t>();
  const auto maximum_rows=request.at("limits").at("output_rows").get<std::uint64_t>();
  const auto maximum_bytes=request.at("limits").at("capture_bytes").get<std::uint64_t>();
  const auto work=request.at("native").at("work_limit").get<std::uint64_t>();
  std::ofstream capture;
  if (verify) {
    const auto path=request.at("capture_file").get<std::string>();
    require(!std::filesystem::exists(path),"paper capture already exists");
    capture.open(path); require(bool(capture),"cannot create paper capture");
  }
  std::uint64_t captured{},sequence{},relation_sequence{},input_lines{},markers{},output_rows{},delta_rows{},snapshot_rows{};
  std::uint64_t decode_ns{},apply_ns{},output_ns{},epoch_release_ns{},output_calls{};
  auto frames=Json::array();
  std::array<std::uint64_t,65> latency_histogram{};
  std::uint64_t latency_sum{},latency_max{};
  auto emit=[&](const Json& value) {
    if (!verify) return;
    auto encoded=value.dump(); encoded.push_back('\n');
    require(encoded.size()<=maximum_bytes-captured,"paper capture byte limit exceeded");
    capture.write(encoded.data(),static_cast<std::streamsize>(encoded.size()));
    require(bool(capture),"paper capture write failed");
    captured+=encoded.size();
  };
  auto count_row=[&] { require(output_rows<maximum_rows,"paper output row limit exceeded"); ++output_rows; };
  const auto looping=Clock::now();
  std::string line;
  Input decoded;
  const bool delta_mode=mode=="delta";
  while (std::getline(input,line)) {
    ++input_lines;
    const auto beginning=Clock::now();
    decode(line,tables,format,graph==tables.end()?TableId{}:graph->second,decoded);
    decode_ns+=nanos(beginning);
    if (decoded.enumerate) {
      ++markers;
      if (full_at_markers) {
        const auto observing=Clock::now();
        emit({{"kind","snapshot_begin"},{"sequence",sequence},{"marker",markers}});
        std::uint64_t rows{};
        if(flat) {
          FlatCounter counter; counter.owner=&*flat;
          if(verify) counter.capture=[&](SetOperation,Json values){emit({{"kind","snapshot_row"},{"sequence",sequence},{"marker",markers},{"values",std::move(values)}});};
          flat->snapshot(counter.sink());
          rows=counter.rows; snapshot_rows+=rows;
          require(output_rows+rows<=maximum_rows,"paper output row limit exceeded"); output_rows+=rows;
        } else {
        auto cursor=owner->results({work});
        for (;;) {
          ++output_calls; auto value=cursor.next(); if(!value) break;
          count_row(); ++rows; ++snapshot_rows;
          if(verify) emit({{"kind","snapshot_row"},{"sequence",sequence},{"marker",markers},{"values",tuple_values(value->values())}});
        }
        }
        emit({{"kind","snapshot_end"},{"sequence",sequence},{"marker",markers},{"rows",rows}});
        output_ns+=nanos(observing);
        frames.push_back({{"sequence",sequence},{"marker",markers},{"rows",rows}});
      }
      continue;
    }
    require(sequence<maximum_events,"paper input event limit exceeded"); ++sequence;
    std::uint64_t raw_delta_rows{};
    if(delta_mode && verify) emit({{"kind","delta_begin"},{"sequence",sequence}});
    auto apply_relation=[&](TableId table) {
      if(flat) {
        encoded.resize(flat->arity(table)); flat->encode(table,decoded.values,encoded.data());
        ++relation_sequence;
        FlatCounter counter; counter.owner=&*flat;
        if(verify && mode=="delta") counter.capture=[&](SetOperation operation,Json cells){emit({{"kind","delta_row"},{"sequence",sequence},
            {"relation_sequence",relation_sequence},{"operation",operation==SetOperation::insert?"+":"-"},{"values",std::move(cells)}});};
        const auto applying=Clock::now();
        flat->apply(table,decoded.operation,encoded.data(),counter.sink());
        apply_ns+=nanos(applying);
        raw_delta_rows+=counter.rows; delta_rows+=counter.rows;
        require(output_rows+counter.rows<=maximum_rows,"paper output row limit exceeded"); output_rows+=counter.rows;
        return;
      }
      // Chained timer reads: apply | output | release (four reads per update).
      const auto applying=Clock::now();
      std::optional<runtime::DeltaRuntime::Epoch> epoch;
      ++relation_sequence;
      epoch.emplace(owner->apply_view({relation_sequence,table,decoded.operation,storage::TupleValuesView::borrow(decoded.values)}));
      const auto observing=Clock::now();
      apply_ns+=paper_clock::elapsed(applying,observing);
      if(delta_mode) for(;;) {
        ++output_calls; auto value=epoch->next(); if(!value) break;
        count_row(); ++raw_delta_rows; ++delta_rows;
        if(verify) emit({{"kind","delta_row"},{"sequence",sequence},{"relation_sequence",relation_sequence},
                        {"operation",value->operation==SetOperation::insert?"+":"-"},
                        {"values",tuple_values(value->tuple.values())}});
      }
      const auto releasing=Clock::now();
      output_ns+=paper_clock::elapsed(observing,releasing);
      epoch.reset(); epoch_release_ns+=nanos(releasing);
    };
    if(routed) {
      const auto right=std::get<std::int64_t>(decoded.values.at(1));
      for(const auto& route:routes) if(!route.threshold || right>*route.threshold) apply_relation(route.table);
    } else if(format=="tagged_csv") {
      const auto found=tag_routes.find(decoded.tag);
      require(found!=tag_routes.end(),"unknown tagged input relation");
      for(const auto& route:found->second)
        if(!route.threshold || std::get<std::int64_t>(decoded.values.at(1))>*route.threshold) apply_relation(route.table);
    } else apply_relation(decoded.table);
    if(delta_mode && verify) emit({{"kind","delta_end"},{"sequence",sequence},{"rows",raw_delta_rows}});
    const auto latency=nanos(beginning); latency_sum+=latency; latency_max=std::max(latency_max,latency);
    std::size_t bin{}; auto remaining=latency; while(remaining) { ++bin; remaining>>=1; }
    ++latency_histogram[bin];
    if(sequence%100000==0) std::cerr<<"paper replay accepted "<<sequence<<" physical updates\n";
  }
  require(!input.bad(),"paper stream read failed");
  const auto loop_ns=nanos(looping);const auto threads=process_threads();const auto gc_report=paper_gc_report(options.gc);
  // This final read follows all measured input work; it cannot change any later
  // input epoch. It is kept separate from the timed paper output protocol.
  const auto finalizing=Clock::now();
  std::uint64_t final_rows{};
  if(verify) {
    emit({{"kind","final_begin"},{"sequence",sequence}});
    if(flat) {
      FlatCounter counter; counter.owner=&*flat;
      counter.capture=[&](SetOperation,Json values){emit({{"kind","final_row"},{"sequence",sequence},{"values",std::move(values)}});};
      flat->snapshot(counter.sink()); final_rows=counter.rows;
    } else {
    auto cursor=owner->results({work});
    while(auto value=cursor.next()) {
      require(final_rows<maximum_rows,"paper final result limit exceeded"); ++final_rows;
      emit({{"kind","final_row"},{"sequence",sequence},{"values",tuple_values(value->values())}});
    }
    }
    emit({{"kind","final_end"},{"sequence",sequence},{"rows",final_rows}});
    capture.flush(); require(bool(capture),"paper capture flush failed");
  }
  const auto final_check_ns=nanos(finalizing);
  const auto usage=flat?Json{}:memory(owner->accounted_memory_statistics());
  const auto destroying=Clock::now(); owner.reset(); flat.reset(); const auto teardown_ns=nanos(destroying);
  return report({{"schema_version",1},{"engine",engine_name},{"gc_mode",crown::storage::keyed::gc_mode_name(options.gc.mode)},{"threads",threads},{"gc",gc_report},{"implementation","native_crown_serial_original_routing"},
      {"status","complete"},{"case_id",request.at("case_id")},{"command",request.at("command")},
      {"output_mode",mode},{"full_at_markers",full_at_markers},{"input_format",format},{"physical_inputs",sequence},{"input_lines",input_lines},
      {"relation_updates",relation_sequence},{"routing",request.value("routing",std::string("physical_source"))},
      {"enumeration_markers",markers},{"output_rows",output_rows},{"delta_rows",delta_rows},
      {"snapshot_rows",snapshot_rows},{"output_calls",output_calls},{"capture_bytes",captured},
      {"final_rows",verify?Json(final_rows):Json{}},{"snapshots",std::move(frames)},
      {"physical_sha256",std::string(compiled.program.physical_sha256())},
      {"source_sha256",std::string(compiled.program.physical_source_sha256())},
      {"physical_options",io::write_physical_options(compiled.physical)},
      {"read_request_ns",read_ns},{"compile_ns",compile_ns},{"initialize_ns",initialize_ns},
      {"loop_wall_ns",loop_ns},{"decode_ns",decode_ns},{"apply_ns",apply_ns},{"output_ns",output_ns},
      {"epoch_release_ns",epoch_release_ns},{"final_check_ns",final_check_ns},{"teardown_ns",teardown_ns},
      {"physical_input_latency_sum_ns",latency_sum},{"physical_input_latency_max_ns",latency_max},
      {"physical_input_latency_histogram_bit_length",latency_histogram},{"memory_before_teardown",usage},
      {"scope","Serial original labelled CQ with the same ordered per-relation routing/filter as unchanged original Flink graph jobs. Raw graph edits and logical relation updates are counted separately. Full snapshots only at original input markers, or all signed deltas, or no output. Parser/routing/API work included; no native core/baseline patch, WAL, cluster or paper-completion claim."}});
}
} // namespace
int main(int argc,char** argv) {
  try { return run(argc,argv); }
  catch(const std::exception& error) { std::cerr<<error.what()<<'\n'; return 1; }
}
