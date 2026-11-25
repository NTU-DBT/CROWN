#include "paper_input.hpp"
#include <crown/frontend/sql_aggregate.hpp>
#include <crown/runtime/sql_aggregate.hpp>
#include <crown/runtime/flat_count.hpp>
#include <crown/planner/lower.hpp>
#include "flat_driver.hpp"

namespace {
Json aggregate_tuple(const runtime::aggregate::Tuple& tuple) {
  auto row=Json::array();for(const auto& cell:tuple.view()) row.push_back(cell?io::write_scalar_view(*cell):Json{});return row;
}
int run(int argc,char** argv) {
  require(argc==3,"usage: paper_native_aggregate REQUEST INPUT");
  const auto beginning=Clock::now();std::ifstream configuration(argv[1]);require(bool(configuration),"cannot open request");
  const auto request=io::read_json(std::string(std::istreambuf_iterator<char>(configuration),{}));
  require(request.at("schema_version")==1,"unknown request version");
  const bool verify=request.at("command")=="verify";require(verify || request.at("command")=="measure","unknown command");
  const auto mode=request.at("output_mode").get<std::string>();require(mode=="full" || mode=="delta" || mode=="none","unknown output mode");
  const auto& native=request.at("native");const auto work=native.at("work_limit").get<std::uint64_t>();
  const auto maximum_events=request.at("limits").at("input_events").get<std::uint64_t>();
  const auto maximum_rows=request.at("limits").at("output_rows").get<std::uint64_t>();
  const auto maximum_bytes=request.at("limits").at("capture_bytes").get<std::uint64_t>();
  const auto& input_program=request.at("program");const auto catalog=io::read_catalog(input_program.at("catalog").dump());
  auto binding=frontend::bind_sql_aggregate(input_program.at("sql").get<std::string>(),catalog);
  if(const auto* failure=std::get_if<frontend::BindingDiagnostic>(&binding))throw std::runtime_error(failure->diagnostic.code+": "+failure->diagnostic.message);
  const auto program=std::get<frontend::SqlAggregateProgram>(std::move(binding));const auto core=program.source_program().export_core();
  const auto selected=planner::minimum_tree(core.catalog,core.query);require(selected.status==planner::OracleStatus::proven_minimum && selected.tree.has_value(),"aggregate source has no proved tree");
  const auto physical=physical_options(native);runtime::sql_aggregate::Options options;
  options.memory_limit_bytes=native.at("memory_limit_bytes").get<std::uint64_t>();options.group_work_limit=work;
  options.source.native.work_limit=work;options.source.native.multiplicity_limit=UINT64_MAX;
  options.source.native.gc=paper_gc_options();
  options.count_limit=INT64_MAX;options.capture_changes=mode=="delta";
  // Fused keyed batches (sql_aggregate::Options::fused); CROWN_AGGREGATE_FUSED=0 keeps the layered path.
  {const char* fused=std::getenv("CROWN_AGGREGATE_FUSED");options.fused=!(fused && std::string_view(fused)=="0");}
  const auto compile_ns=nanos(beginning);const auto initializing=Clock::now();
  std::optional<runtime::SqlAggregateRuntime> owner;
  // CROWN_ENGINE=flat: bag COUNT(*) of the exported core CQ on FlatCountRuntime.
  // Each SQL source row maps to its occurrences' core rows (plain column
  // projections only); groups and SELECT outputs are rebuilt from the core head.
  std::optional<runtime::FlatCountRuntime> flat;
  struct FlatRoute { TableId core; std::vector<std::size_t> columns; };
  std::vector<std::vector<FlatRoute>> flat_routes;
  std::vector<std::size_t> group_columns;
  std::vector<std::pair<bool,std::size_t>> flat_outputs;  // (count, group position)
  if(flat_engine_requested()) {
    const auto& kernel=program.kernel_program();
    for(const auto& output:kernel.outputs()) {
      require(output.kind==frontend::AggregateOutputKind::group || output.kind==frontend::AggregateOutputKind::count_all,"flat aggregate supports COUNT(*) and group columns only");
      flat_outputs.emplace_back(output.kind==frontend::AggregateOutputKind::count_all,output.index);
    }
    for(const auto column:kernel.group_columns()) group_columns.push_back(column.value);
    require(!program.static_source_weight(),"flat aggregate needs a nonempty FROM");
    const auto& rows_program=program.source_program();
    const auto core_program=CompiledProgram::standalone(planner::lower_tree(core.catalog,core.query,*selected.tree,physical));
    require(runtime::FlatCountRuntime::unsupported(core_program).empty(),"flat engine cannot run this program");
    flat.emplace(core_program,runtime::FlatOptions{mode=="delta"});
    require(core.query.head.size()==program.native_fields(),"core head differs from native fields");
    flat_routes.resize(catalog.tables.size());
    for(const auto& occurrence:rows_program.occurrences()) {
      require(occurrence.operations.empty() && occurrence.predicates.empty() && occurrence.equal_columns.empty() &&
              occurrence.constant_columns.empty(),"flat aggregate supports plain column projections only");
      FlatRoute route{TableId{occurrence.occurrence.value},{}};
      for(const auto& field:occurrence.projection) {
        require(field.kind==frontend::SqlRowsFieldKind::value,"flat aggregate needs non-null value fields");
        std::optional<std::size_t> column;
        for(const auto& input:occurrence.inputs) if(input.target==field.expression) column=input.column.value;
        require(column.has_value(),"flat aggregate projection is not a source column");
        route.columns.push_back(*column);
      }
      require(route.columns.size()==flat->arity(route.core),"core occurrence arity differs");
      flat_routes.at(occurrence.source.value).push_back(std::move(route));
    }
  } else owner.emplace(program,*selected.tree,physical,options);
  const bool flat_mode=flat.has_value();
  const std::string engine_name=flat_mode?std::string("flat"):std::string(owner->engine());
  const auto initialize_ns=nanos(initializing);
  std::vector<std::int64_t> flat_row;
  // Group JSON from a core head row: key = group columns, values = SELECT outputs.
  auto flat_group_json=[&](const std::int64_t* head,std::uint64_t count) {
    auto key=Json::array(); for(const auto column:group_columns) key.push_back(io::write_scalar(flat->decode(column,head[column])));
    auto values=Json::array();
    for(const auto& [is_count,position]:flat_outputs)
      values.push_back(is_count?Json(static_cast<std::int64_t>(count)):io::write_scalar(flat->decode(group_columns.at(position),head[group_columns.at(position)])));
    return std::pair{std::move(key),std::move(values)};
  };
  std::map<std::string,TableId> tables;for(std::size_t i=0;i<catalog.tables.size();++i)tables.emplace(catalog.tables[i].name,TableId{i});
  std::vector<TableId> routes;for(const auto& route:request.at("graph_aliases")) {
    require(!route.contains("min_src_exclusive") && !route.contains("min_dst_exclusive"),"star count original source has no filter");
    const auto found=tables.find(route.at("table").get<std::string>());require(found!=tables.end(),"unknown star alias");routes.push_back(found->second);
  }
  require(routes.size()==4,"original star count requires all four aliases");
  std::unique_ptr<GzipBuffer> gzip_buffer;std::unique_ptr<std::istream> input_owner;
  if(std::string(argv[2]).ends_with(".gz")){gzip_buffer=std::make_unique<GzipBuffer>(argv[2]);input_owner=std::make_unique<std::istream>(gzip_buffer.get());}
  else {input_owner=std::make_unique<std::ifstream>(argv[2]);}
  auto& input=*input_owner;require(bool(input),"cannot open input");
  std::ofstream capture;if(verify){const auto path=request.at("capture_file").get<std::string>();require(!std::filesystem::exists(path),"capture exists");capture.open(path);require(bool(capture),"cannot create capture");}
  std::uint64_t sequence{},relation_sequence{},markers{},input_lines{},rows{},delta_rows{},snapshot_rows{},captured{};
  std::uint64_t decode_ns{},apply_ns{},output_ns{},release_ns{};auto frames=Json::array();
  auto emit=[&](const Json& record){if(!verify)return;auto bytes=record.dump();bytes+='\n';require(bytes.size()<=maximum_bytes-captured,"capture byte limit");capture<<bytes;require(bool(capture),"capture write failed");captured+=bytes.size();};
  auto count=[&]{require(rows<maximum_rows,"output row limit");++rows;};
  auto snapshot=[&](const char* prefix,bool final){const auto observing=Clock::now();std::uint64_t groups{};
    emit({{"kind",std::string(prefix)+"begin"},{"sequence",sequence},{"marker",markers}});
    if(flat) {
      struct Context { std::uint64_t groups{}; std::function<void(const std::int64_t*,std::uint64_t)> visit; } context;
      context.visit=[&](const std::int64_t* head,std::uint64_t after){
        if(!final){count();++snapshot_rows;}
        if(verify){auto [key,values]=flat_group_json(head,after);emit({{"kind",std::string(prefix)+"group"},{"sequence",sequence},{"marker",markers},{"key",std::move(key)},{"values",std::move(values)}});}
      };
      runtime::FlatCountSink sink{&context,[](void* c,const std::int64_t* head,std::size_t,std::uint64_t,std::uint64_t after){
        auto& self=*static_cast<Context*>(c);++self.groups;self.visit(head,after);}};
      flat->snapshot(sink); groups=context.groups;
    } else {
    auto image=owner->snapshot({maximum_rows,work});
    for(const auto& group:image.groups){if(!final){count();++snapshot_rows;}++groups;if(verify)emit({{"kind",std::string(prefix)+"group"},{"sequence",sequence},{"marker",markers},{"key",aggregate_tuple(group.key)},{"values",aggregate_tuple(group.values)}});}
    }
    emit({{"kind",std::string(prefix)+"end"},{"sequence",sequence},{"marker",markers},{"rows",groups}});
    if(!final) {frames.push_back({{"sequence",sequence},{"marker",markers},{"groups",groups}});}
    output_ns+=nanos(observing);return groups;};
  const auto looping=Clock::now();std::string line;
  const std::string graph_csv="graph_csv";Input event;
  while(std::getline(input,line)){
    ++input_lines;const auto decoding=Clock::now();decode(line,tables,graph_csv,TableId{},event);decode_ns+=nanos(decoding);
    if(event.enumerate){++markers;if(mode=="full")snapshot("snapshot_",false);continue;}
    require(sequence<maximum_events,"input event limit");++sequence;std::uint64_t raw_changes{};
    if(mode=="delta" && verify)emit({{"kind","delta_begin"},{"sequence",sequence}});
    for(const auto table:routes){
      if(flat) {
        ++relation_sequence;
        // Net per relation edit: one change per group, as the reference reports.
        std::map<std::vector<std::int64_t>,std::pair<std::uint64_t,std::uint64_t>> net;
        struct Context { std::map<std::vector<std::int64_t>,std::pair<std::uint64_t,std::uint64_t>>* net; std::size_t width; } context{&net,0};
        runtime::FlatCountSink sink{&context,[](void* c,const std::int64_t* head,std::size_t size,std::uint64_t before,std::uint64_t after){
          auto& self=*static_cast<Context*>(c);auto [it,fresh]=self.net->try_emplace(std::vector<std::int64_t>(head,head+size),before,after);
          if(!fresh) it->second.second=after;}};
        const auto applying=Clock::now();
        for(const auto& route:flat_routes.at(table.value)) {
          flat_row.resize(route.columns.size());
          for(std::size_t i=0;i<route.columns.size();++i) flat_row[i]=std::get<std::int64_t>(event.values.at(route.columns[i]));
          flat->apply(route.core,event.operation==SetOperation::insert?1:-1,flat_row.data(),sink);
        }
        apply_ns+=nanos(applying);
        if(mode=="delta") for(const auto& [head,change]:net) {
          if(change.first==change.second) continue;
          count();++delta_rows;++raw_changes;
          if(verify){auto [key,after]=flat_group_json(head.data(),change.second);auto before=flat_group_json(head.data(),change.first).second;
            emit({{"kind","group_change"},{"sequence",sequence},{"relation_sequence",relation_sequence},{"key",std::move(key)},
              {"before",change.first?before:Json{}},{"after",change.second?after:Json{}}});}
        }
        continue;
      }
      const auto applying=Clock::now();const std::array<runtime::sql_rows::Cell,2> cells{storage::ScalarView{std::get<std::int64_t>(event.values[0])},storage::ScalarView{std::get<std::int64_t>(event.values[1])}};
      const std::uint64_t before=event.operation==SetOperation::insert?0:1;const runtime::sql_rows::SourceReplacement edit{table,cells,before,1-before};
      auto pending=owner->prepare_batch({++relation_sequence,std::span{&edit,1}});auto epoch=std::make_optional(pending.commit());apply_ns+=nanos(applying);
      const auto observing=Clock::now();if(mode=="delta")for(const auto& group:epoch->output){count();++delta_rows;++raw_changes;
        if(verify)emit({{"kind","group_change"},{"sequence",sequence},{"relation_sequence",relation_sequence},{"key",aggregate_tuple(group.key)},
          {"before",group.before?aggregate_tuple(*group.before):Json{}},{"after",group.after?aggregate_tuple(*group.after):Json{}}});}
      output_ns+=nanos(observing);const auto releasing=Clock::now();epoch.reset();release_ns+=nanos(releasing);
    }
    if(mode=="delta" && verify)emit({{"kind","delta_end"},{"sequence",sequence},{"rows",raw_changes}});
    if(sequence%100000==0)std::cerr<<"paper aggregate accepted "<<sequence<<" physical updates\n";
  }
  require(!input.bad(),"input read failed");const auto loop_ns=nanos(looping);const auto threads=process_threads();const auto gc_report=paper_gc_report(options.source.native.gc);const auto final_groups=verify?snapshot("final_",true):0;
  if(verify){capture.flush();require(bool(capture),"capture flush failed");}const auto usage=flat?Json{}:memory(owner->accounted_memory_statistics());
  const auto destroying=Clock::now();owner.reset();flat.reset();const auto teardown_ns=nanos(destroying);
  return report({{"schema_version",1},{"engine",engine_name},{"gc_mode",crown::storage::keyed::gc_mode_name(options.source.native.gc.mode)},{"threads",threads},{"gc",gc_report},{"implementation","native_serial_sql_star_count"},{"fused",options.fused},{"status","complete"},{"case_id",request.at("case_id")},
    {"output_mode",mode},{"physical_inputs",sequence},{"input_lines",input_lines},{"relation_updates",relation_sequence},{"enumeration_markers",markers},
    {"output_rows",rows},{"delta_rows",delta_rows},{"snapshot_rows",snapshot_rows},{"capture_bytes",captured},{"snapshots",std::move(frames)},
    {"final_groups",verify?Json(final_groups):Json{}},{"compile_ns",compile_ns},{"initialize_ns",initialize_ns},{"loop_wall_ns",loop_ns},
    {"decode_ns",decode_ns},{"apply_ns",apply_ns},{"output_ns",output_ns},{"epoch_release_ns",release_ns},{"teardown_ns",teardown_ns},
    {"memory_before_teardown",usage},{"physical_options",io::write_physical_options(physical)},
    {"scope","Original four-alias star GROUP BY and COUNT(*) through unchanged genuine SQL aggregate runtime; exact ordered per-relation original source dispatch. Full groups only at input markers or all per-relation group replacements; serial, unit physical sources, no COUNT(DISTINCT), no native core/baseline patch or paper-completion claim."}});
}
}
int main(int argc,char** argv){try{return run(argc,argv);}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
