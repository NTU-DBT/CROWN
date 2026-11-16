#include "component_request.hpp"
#include <crown/frontend/sql_aggregate.hpp>
#include <crown/io/catalog.hpp>
#include <crown/io/physical.hpp>
#include <crown/io/tree.hpp>
#include <crown/planner/oracle.hpp>
#include <crown/runtime/sql_aggregate.hpp>
#include <iostream>
#include <map>
#include <optional>

namespace {
using namespace crown;
using namespace component;
namespace ag = runtime::aggregate;

// Export only observations. The returned ordinary JSON is caller/report memory,
// separate from the original query account and its owning result tuples.
Json tuple(const ag::Tuple& value) {
  auto output = Json::array();
  for (const auto& cell : value.view()) output.push_back(cell ? io::write_scalar_view(*cell) : Json{});
  return output;
}
Json memory(const resource::MemoryStatistics& value) {
  return {{"limit_bytes", value.limit_bytes}, {"current_requested_bytes", value.current.requested_bytes},
      {"peak_requested_bytes", value.peak_requested_bytes}, {"current_allocations", value.current.allocations}};
}

// COUNT-only source presentation is a guarded component ablation. The genuine
// original compiler supplies the exact same derived bag source; no replacement
// query or joined-row ledger is constructed. See docs/weighted_enumeration.md.
void source_count_contract(const frontend::AggregateProgram& kernel) {
  require(kernel.full_input_group_key() && !kernel.group_columns().empty(),
      "source-only COUNT requires the complete nonempty input grouping key");
  require(kernel.measures().empty(), "source-only presentation admits COUNT(*) only");
  bool counted = false;
  for (const auto& output : kernel.outputs()) {
    require(output.kind == frontend::AggregateOutputKind::group ||
        output.kind == frontend::AggregateOutputKind::count_all,
        "source-only presentation requires group columns and COUNT(*)");
    counted |= output.kind == frontend::AggregateOutputKind::count_all;
  }
  require(counted, "source-only presentation needs COUNT(*)");
}
// Public SQL rows retain repeated SELECT/GROUP BY references. Select the
// canonical kernel inputs through the compiler's source-output mapping once;
// native payload/presence positions do not index this decoded SQL tuple.
Json source_group(const runtime::sql_rows::Result& row, const frontend::SqlAggregateProgram& program) {
  const auto& kernel = program.kernel_program();
  const auto inputs = program.inputs();
  const auto cells = row.tuple.view();
  auto key = Json::array();
  for (const auto column : kernel.group_columns()) {
    const auto& cell = cells[inputs[column.value].source_output];
    key.push_back(cell ? io::write_scalar_view(*cell) : Json{});
  }
  auto output = Json::array();
  for (const auto& field : kernel.outputs()) {
    if (field.kind == frontend::AggregateOutputKind::count_all) output.push_back(row.multiplicity);
    else output.push_back(key[field.index]);
  }
  return {{"key", std::move(key)}, {"values", std::move(output)}};
}

int run(int argc, char** argv) {
  const auto reading = Clock::now();
  const auto request = read_request(argc, argv);
  const auto read_ns = elapsed(reading, Clock::now());
  const auto mode = request.document.at("output").get<std::string>();
  require(mode == "groups_full" || mode == "groups_replacements", "aggregate output mode is unsupported");
  const auto& native = request.document.at("native");
  const bool source_only = native.value("aggregate_source_only", false);
  require(!source_only || mode == "groups_full", "source-only COUNT has no replacement output port");

  // Shared cold SQL/proof work is charged once per invocation, never per pass.
  // The family is an output label; only actual SQL/catalog factories admit code.
  const auto compiling = Clock::now();
  const auto& input_program = request.document.at("program");
  const auto catalog = io::read_catalog(input_program.at("catalog").dump());
  auto binding = frontend::bind_sql_aggregate(input_program.at("sql").get<std::string>(), catalog);
  if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&binding))
    throw std::runtime_error(failure->diagnostic.code + ": " + failure->diagnostic.message);
  const auto program = std::get<frontend::SqlAggregateProgram>(std::move(binding));
  const auto core = program.source_program().export_core();
  FreeConnexTree tree;
  if (!program.source_program().contradiction()) {
    const auto selected = planner::minimum_tree(core.catalog, core.query);
    require(selected.status == planner::OracleStatus::proven_minimum && selected.tree.has_value(),
        "aggregate source has no proved admissible tree");
    tree = *selected.tree;
  }
  const auto encoded_options = native.value("physical_options", Json::object());
  const auto physical = encoded_options.is_object() && encoded_options.empty()
      ? PhysicalOptions{} : io::read_physical_options(encoded_options.dump());
  if (source_only) source_count_contract(program.kernel_program());

  // Resolve transport names once. Each physical +/- edit remains one unit-weight
  // transaction across all self-join aliases; no alias updates enter publicly.
  std::map<std::string, TableId> names;
  for (std::size_t i=0; i<catalog.tables.size(); ++i) names.emplace(catalog.tables[i].name, TableId{i});
  std::vector<TableId> targets; targets.reserve(request.events.size());
  for (const auto& event : request.events) {
    const auto position = names.find(event.table);
    require(position != names.end(), "component event names an unknown table");
    targets.push_back(position->second);
  }
  runtime::sql_aggregate::Options options;
  options.memory_limit_bytes = number(native.at("memory_limit_bytes"));
  const auto work = number(native.value("work_limit", Json(1000000)));
  options.group_work_limit = work; options.source.native.work_limit = work;
  options.count_limit = number(native.value("count_limit", Json(INT64_MAX)), INT64_MAX);
  options.source.native.multiplicity_limit = number(native.value("multiplicity_limit", Json(UINT64_MAX)));
  options.capture_changes = mode == "groups_replacements";
  const auto compile_ns = elapsed(compiling, Clock::now());
  auto passes = Json::array();
  for (std::size_t pass=0; pass<request.warmups+request.repetitions; ++pass) {
    const auto initializing = Clock::now();
    const auto account = resource::MemoryAccount::create(options.memory_limit_bytes);
    std::optional<runtime::SqlAggregateRuntime> owner;
    std::optional<runtime::SqlRowsRuntime> source;
    if (source_only) source.emplace(runtime::SqlRowsRuntime::create_into(
        account, program.source_program(), tree, physical, options.source));
    else owner.emplace(runtime::SqlAggregateRuntime::create_into(account, program, tree, physical, options));
    const auto initialize_ns = elapsed(initializing, Clock::now());
    auto epochs = Json::array(); U64 records = 0, captured_bytes = 0;
    const auto looping = Clock::now();
    for (std::size_t i=0; i<request.events.size(); ++i) {
      const auto& event = request.events[i];
      const std::array<runtime::sql_rows::Cell,2> cells{
          storage::ScalarView{event.values[0]}, storage::ScalarView{event.values[1]}};
      const U64 before = event.operation == "+" ? 0 : 1, after = 1-before;
      const auto applying = Clock::now();
      std::optional<runtime::sql_aggregate::Epoch> epoch;
      std::optional<runtime::sql_rows::Epoch> source_epoch;
      if (source_only) source_epoch.emplace(source->apply({i+1, targets[i], cells, before, after}));
      else {
        const runtime::sql_rows::SourceReplacement edit{targets[i], cells, before, after};
        auto pending = owner->prepare_batch({i+1, std::span{&edit,1}});
        epoch.emplace(pending.commit());
      }
      const auto apply_ns = elapsed(applying, Clock::now());
      const auto observing = Clock::now();
      Json actual; if (request.verify) actual = Json::array();
      U64 emitted = 0;
      std::optional<runtime::sql_aggregate::Snapshot> snapshot;
      if (source_only) {
        auto cursor = source->results({work});
        while (auto row = cursor.next()) {
          add_records(records, 1, request.max_records); ++emitted;
          require(row->multiplicity <= options.count_limit, "source-only COUNT exceeds count limit");
          if (request.verify) actual.push_back(source_group(*row, program));
        }
      } else if (mode == "groups_full") {
        snapshot.emplace(owner->snapshot({request.max_records, work}));
        add_records(records, snapshot->groups.size(), request.max_records); emitted = snapshot->groups.size();
        if (request.verify) for (const auto& group : snapshot->groups)
          actual.push_back({{"key", tuple(group.key)}, {"values", tuple(group.values)}});
      } else {
        add_records(records, epoch->output.size(), request.max_records); emitted = epoch->output.size();
        if (request.verify) for (const auto& group : epoch->output)
          actual.push_back({{"key", tuple(group.key)},
              {"before", group.before ? tuple(*group.before) : Json{}},
              {"after", group.after ? tuple(*group.after) : Json{}}});
      }
      const auto output_ns = elapsed(observing, Clock::now());
      const auto releasing = Clock::now();
      snapshot.reset(); epoch.reset(); source_epoch.reset();
      const auto release_ns = elapsed(releasing, Clock::now());
      // Verification serialization/report storage is outside the measured API.
      // Measure mode retains counts/latencies, never a second group/row graph.
      if (request.verify) {
        const auto bytes = static_cast<U64>(actual.dump().size());
        require(bytes <= request.max_bytes-captured_bytes, "component capture-byte limit exceeded");
        captured_bytes += bytes;
      }
      epochs.push_back({{"sequence", i+1}, {"phase", event.phase}, {"apply_ns", time_value(request,apply_ns)},
          {"output_ns", time_value(request,output_ns)}, {"release_ns", time_value(request,release_ns)},
          {"output_records", emitted}, {"actual", request.verify ? std::move(actual) : Json{}}});
    }
    const auto loop_ns = elapsed(looping, Clock::now());
    const auto final_memory = memory(account.statistics());
    const auto destroying = Clock::now(); source.reset(); owner.reset();
    const auto teardown_ns = elapsed(destroying, Clock::now());
    passes.push_back({{"warmup", pass < request.warmups}, {"initialize_ns", time_value(request,initialize_ns)},
        {"loop_wall_ns", time_value(request,loop_ns)}, {"teardown_ns", time_value(request,teardown_ns)},
        {"output_records", records}, {"captured_result_bytes", request.verify ? Json(captured_bytes) : Json{}},
        {"native_memory_before_teardown", final_memory}, {"epochs", std::move(epochs)}});
  }
  Json report{{"schema_version",1}, {"implementation",source_only ? "native_w03_count_source" : "native_sql_aggregate"},
      {"case_id",request.document.at("case_id")}, {"query_family",request.document.at("query_family")},
      {"command",request.document.at("command")}, {"output",mode}, {"read_request_ns",time_value(request,read_ns)},
      {"shared_program_ns",time_value(request,compile_ns)}, {"passes",std::move(passes)},
      {"binding_sha256",std::string(program.identity().binding.begin(),program.identity().binding.end())},
      {"physical_options",io::write_physical_options(physical)},
      {"tree",program.source_program().contradiction() ? Json{} : io::write_tree(tree,core.catalog,core.query)},
      {"scope","fresh logical owner per pass; original SQL compiler plus genuine source/tree; volatile native preparation/commit and required group output; no WAL/fsync; report JSON outside service; measure output is count/discard; query account excludes caller/compiler/report DTOs"}};
  std::cout << report.dump() << '\n'; std::cout.flush();
  return std::cout ? 0 : 1;
}
}  // namespace
int main(int argc, char** argv) {
  try { return run(argc,argv); }
  catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
