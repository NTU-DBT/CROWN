#include "tick_clock.hpp"
#include "native_request.hpp"
#include "flat_driver.hpp"
#include <charconv>
#include <filesystem>
#include <fstream>
#include <map>
#include <string_view>
#include <zlib.h>
#include <memory>

namespace {
using namespace crown;
using namespace component;
using Clock = paper_clock::TickClock;  // tick_clock.hpp: cheap per-phase timers
using paper_clock::nanos;
std::int64_t integer(std::string_view text) {
  std::int64_t value{};
  const auto [end,error] = std::from_chars(text.data(),text.data()+text.size(),value);
  require(error==std::errc{} && end==text.data()+text.size(),"invalid input integer");
  return value;
}
struct Input {
  bool enumerate{};
  SetOperation operation{};
  TableId table{};
  Row values;
  std::string tag;
  std::vector<std::string_view> source_cells;
};
// Decodes into `result`, reused across lines (its buffers keep their capacity).
void decode(const std::string& line, const std::map<std::string,TableId>& tables,
            const std::string& format, TableId graph, Input& result) {
  result.enumerate=false; result.operation={}; result.table={};
  result.values.clear(); result.tag.clear(); result.source_cells.clear();
  if (format=="graph_csv") {
    if (line=="*") { result.enumerate=true; return; }
    require(line.size()>4 && line[1]==',' && (line[0]=='+' || line[0]=='-'),"invalid graph stream record");
    const auto separator=line.find(',',2);
    require(separator!=std::string::npos && line.find(',',separator+1)==std::string::npos,"invalid graph pair");
    result.operation=line[0]=='+' ? SetOperation::insert : SetOperation::erase;
    result.table=graph;
    result.values={integer(std::string_view(line).substr(2,separator-2)),integer(std::string_view(line).substr(separator+1))};
    return;
  }
  if(format=="snb_pipe") {
    if(line=="*") { result.enumerate=true; return; }
    require(line.size()>4 && line[1]=='|' && (line[0]=='+' || line[0]=='-'),"invalid SNB source record");
    result.operation=line[0]=='+' ? SetOperation::insert : SetOperation::erase;
    const auto separator=line.find('|',2);
    require(separator!=std::string::npos,"missing SNB source cells");
    result.tag.assign(line,2,separator-2);
    std::size_t begin=separator+1;
    for(;;) {
      const auto end=line.find('|',begin);
      result.source_cells.push_back(std::string_view(line).substr(begin,end==std::string::npos?end:end-begin));
      if(end==std::string::npos) break;
      begin=end+1;
    }
    return;
  }
  if(format=="tagged_csv") {
    if(line=="*") { result.enumerate=true; return; }
    require(line.size()>4 && line[1]==',' && (line[0]=='+' || line[0]=='-'),"invalid tagged CSV record");
    result.operation=line[0]=='+' ? SetOperation::insert : SetOperation::erase;
    const auto separator=line.find(',',2);
    require(separator!=std::string::npos,"missing tagged CSV values");
    result.tag.assign(line,2,separator-2);
    std::size_t begin=separator+1;
    for(;;) {
      const auto end=line.find(',',begin);
      result.values.emplace_back(integer(std::string_view(line).substr(begin,end==std::string::npos?end:end-begin)));
      if(end==std::string::npos) break;
      begin=end+1;
    }
    return;
  }
  require(format=="jsonl","unknown paper input format");
  const auto value=io::read_json(line);
  if (value.value("enumerate",false)) { result.enumerate=true; return; }
  const auto name=value.at("table").get<std::string>();
  const auto found=tables.find(name); require(found!=tables.end(),"unknown input table");
  result.table=found->second;
  const auto operation=value.at("operation").get<std::string>();
  require(operation=="+" || operation=="-","invalid input operation");
  result.operation=operation=="+" ? SetOperation::insert : SetOperation::erase;
  for (const auto& cell:value.at("values")) result.values.push_back(io::read_scalar(cell));
  return;
}

class GzipBuffer : public std::streambuf {
  gzFile file_{};
  std::vector<char> buffer_=std::vector<char>(std::size_t{1}<<20);
 protected:
  int_type underflow() override {
    if(gptr()!=egptr()) return traits_type::to_int_type(*gptr());
    const auto count=gzread(file_,buffer_.data(),static_cast<unsigned>(buffer_.size()));
    require(count>=0,"gzip input read failed");
    if(!count) return traits_type::eof();
    setg(buffer_.data(),buffer_.data(),buffer_.data()+count);
    return traits_type::to_int_type(*gptr());
  }
 public:
  explicit GzipBuffer(const char* path) : file_(gzopen(path,"rb")) {
    require(file_,"cannot open gzip input");
    require(gzbuffer(file_,1u<<20)==0,"cannot size gzip input buffer");
  }
  ~GzipBuffer() override { if(file_) gzclose(file_); }
};

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
  struct SourceRoute {
    TableId table;
    std::vector<std::pair<std::size_t,bool>> fields;
    std::optional<std::pair<std::size_t,std::int64_t>> when_lt;
    std::optional<std::size_t> when_null;
  };
  std::map<std::string,std::vector<SourceRoute>> source_routes;
  if(format=="snb_pipe") {
    for(const auto& [tag,values]:request.at("source_routes").items()) {
      source_routes.try_emplace(tag);
      for(const auto& value:values) {
      const auto found=tables.find(value.at("table").get<std::string>());
      require(found!=tables.end(),"unknown SNB destination table");
      SourceRoute route{found->second,{},std::nullopt,std::nullopt};
      for(const auto& field:value.at("fields")) {
        const auto type=field.at("type").get<std::string>();
        require(type=="int64" || type=="text","unknown SNB payload scalar");
        route.fields.emplace_back(field.at("index").get<std::size_t>(),type=="text");
      }
      if(value.contains("when_int_lt")) {
        const auto& guard=value.at("when_int_lt");
        route.when_lt=std::pair{guard.at("index").get<std::size_t>(),guard.at("value").get<std::int64_t>()};
      }
      if(value.contains("when_null")) route.when_null=value.at("when_null").get<std::size_t>();
      source_routes[tag].push_back(std::move(route));
      }
    }
  }
  std::optional<std::pair<std::size_t,std::size_t>> full_not_equal;
  if(request.contains("full_head_not_equal") && !request.at("full_head_not_equal").is_null()) {
    const auto& pair=request.at("full_head_not_equal");
    require(pair.size()==2,"invalid full head inequality");
    full_not_equal=std::pair{pair.at(0).get<std::size_t>(),pair.at(1).get<std::size_t>()};
  }
  auto passes_full_head=[&](storage::TupleValuesView values) {
    if(!full_not_equal) return true;
    const auto [left,right]=*full_not_equal;
    require(left<values.size() && right<values.size(),"full head predicate index out of range");
    return std::get<std::int64_t>(values[left])!=std::get<std::int64_t>(values[right]);
  };
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
  std::uint64_t captured{},sequence{},relation_sequence{},input_lines{},markers{},output_rows{},delta_rows{},snapshot_rows{},candidate_snapshot_rows{};
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
  std::vector<storage::ScalarView> route_cells;
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
          FlatCounter counter; counter.owner=&*flat; counter.not_equal=full_not_equal;
          if(verify) counter.capture=[&](SetOperation,Json values){emit({{"kind","snapshot_row"},{"sequence",sequence},{"marker",markers},{"values",std::move(values)}});};
          flat->snapshot(counter.sink());
          rows=counter.rows; candidate_snapshot_rows+=counter.candidates; snapshot_rows+=rows;
          require(output_rows+rows<=maximum_rows,"paper output row limit exceeded"); output_rows+=rows;
        } else {
        auto cursor=owner->results({work});
        for (;;) {
          ++output_calls; auto value=cursor.next(); if(!value) break;
          ++candidate_snapshot_rows;
          if(!passes_full_head(value->values())) continue;
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
    if(mode=="delta" && verify) emit({{"kind","delta_begin"},{"sequence",sequence}});
    // `values` is a Row, or (keyed engine only) borrowed cells.
    auto apply_relation=[&](TableId table,const auto& values) {
      if constexpr(!std::is_same_v<std::remove_cvref_t<decltype(values)>,Row>) require(!flat,"flat executor input must be a Row");
      else if(flat) {
        encoded.resize(flat->arity(table)); flat->encode(table,values,encoded.data());
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
      const auto applying=Clock::now();
      std::optional<runtime::DeltaRuntime::Epoch> epoch;
      ++relation_sequence;
      epoch.emplace(owner->apply_view({relation_sequence,table,decoded.operation,storage::TupleValuesView::borrow(values)}));
      apply_ns+=nanos(applying);
      const auto observing=Clock::now();
      if(mode=="delta") for(;;) {
        ++output_calls; auto value=epoch->next(); if(!value) break;
        count_row(); ++raw_delta_rows; ++delta_rows;
        if(verify) emit({{"kind","delta_row"},{"sequence",sequence},{"relation_sequence",relation_sequence},
                        {"operation",value->operation==SetOperation::insert?"+":"-"},
                        {"values",tuple_values(value->tuple.values())}});
      }
      output_ns+=nanos(observing);
      const auto releasing=Clock::now(); epoch.reset(); epoch_release_ns+=nanos(releasing);
    };
    if(routed) {
      const auto right=std::get<std::int64_t>(decoded.values.at(1));
      for(const auto& route:routes) if(!route.threshold || right>*route.threshold) apply_relation(route.table,decoded.values);
    } else if(format=="tagged_csv") {
      const auto found=tag_routes.find(decoded.tag);
      require(found!=tag_routes.end(),"unknown tagged input relation");
      for(const auto& route:found->second)
        if(!route.threshold || std::get<std::int64_t>(decoded.values.at(1))>*route.threshold) apply_relation(route.table,decoded.values);
    } else if(format=="snb_pipe") {
      const auto found=source_routes.find(decoded.tag);
      require(found!=source_routes.end(),"unknown SNB source tag");
      for(const auto& route:found->second) {
        if(route.when_lt && integer(decoded.source_cells.at(route.when_lt->first))>=route.when_lt->second) continue;
        if(route.when_null) {
          const auto cell=decoded.source_cells.at(*route.when_null);
          if(!cell.empty() && cell!="\\N") continue;
        }
        if(flat) {
          Row values; values.reserve(route.fields.size());
          for(const auto& [index,text]:route.fields) {
            const auto cell=decoded.source_cells.at(index);
            if(text) values.emplace_back(std::string(cell));
            else values.emplace_back(integer(cell));
          }
          apply_relation(route.table,values);
          continue;
        }
        // Text cells borrow the input line, which outlives the update.
        route_cells.clear();
        for(const auto& [index,text]:route.fields) {
          const auto cell=decoded.source_cells.at(index);
          if(text) route_cells.emplace_back(cell);
          else route_cells.emplace_back(integer(cell));
        }
        apply_relation(route.table,storage::RowView::borrow(route_cells));
      }
    } else apply_relation(decoded.table,decoded.values);
    if(mode=="delta" && verify) emit({{"kind","delta_end"},{"sequence",sequence},{"rows",raw_delta_rows}});
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
      FlatCounter counter; counter.owner=&*flat; counter.not_equal=full_not_equal;
      counter.capture=[&](SetOperation,Json values){emit({{"kind","final_row"},{"sequence",sequence},{"values",std::move(values)}});};
      flat->snapshot(counter.sink()); final_rows=counter.rows;
    } else {
    auto cursor=owner->results({work});
    while(auto value=cursor.next()) {
      if(!passes_full_head(value->values())) continue;
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
  return report({{"full_head_not_equal",request.value("full_head_not_equal",Json{})},{"schema_version",1},{"engine",engine_name},{"gc_mode",crown::storage::keyed::gc_mode_name(options.gc.mode)},{"threads",threads},{"gc",gc_report},{"implementation","native_crown_serial_original_snb_routing"},
      {"status","complete"},{"case_id",request.at("case_id")},{"command",request.at("command")},
      {"output_mode",mode},{"full_at_markers",full_at_markers},{"input_format",format},{"physical_inputs",sequence},{"input_lines",input_lines},
      {"relation_updates",relation_sequence},{"routing",request.value("routing",std::string("physical_source"))},
      {"enumeration_markers",markers},{"output_rows",output_rows},{"delta_rows",delta_rows},
      {"snapshot_rows",snapshot_rows},{"candidate_snapshot_rows",candidate_snapshot_rows},{"output_calls",output_calls},{"capture_bytes",captured},
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
