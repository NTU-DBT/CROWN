#include "native_request.hpp"
#include <crown/frontend/sql_rows.hpp>
#include <crown/runtime/sql_rows.hpp>
#include <crown/io/tree.hpp>
#include <algorithm>
#include <optional>

namespace {
using namespace crown;
using namespace component;
namespace rows = runtime::sql_rows;

int run(int argc, char** argv) {
  const auto reading = Clock::now();
  const auto request = read_request(argc,argv);
  const auto read_ns = elapsed(reading, Clock::now());
  require(request.document.at("output") == "compressed_bag", "SQL rows require compressed_bag output");
  const auto compiling = Clock::now();
  const auto& input = request.document.at("program");
  require(!input.contains("compiled_set") || input.at("compiled_set").is_null(),
      "a set normalization artifact cannot select a SQL-rows source tree");
  const auto catalog = io::read_catalog(input.at("catalog").dump());
  auto binding = frontend::bind_sql_rows(input.at("sql").get<std::string>(), catalog);
  if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&binding))
    throw std::runtime_error(failure->diagnostic.code + ": " + failure->diagnostic.message);
  const auto program = std::get<frontend::SqlRowsProgram>(std::move(binding));
  const auto core = program.export_core();
  FreeConnexTree tree;
  if (!program.contradiction()) {
    const auto selected = planner::minimum_tree(core.catalog,core.query);
    require(selected.status == planner::OracleStatus::proven_minimum && selected.tree.has_value(),
        "SQL rows source has no proved admissible tree");
    tree = *selected.tree;
  }
  const auto& native = request.document.at("native");
  require(!native.contains("mode"), "SQL rows has no unweighted DeltaMode control");
  const auto physical = physical_options(native);
  const auto targets = target_tables(request,catalog);
  const auto batch_size = number(native.value("transaction_batch_size",Json(1)),1000000);
  const auto interval = number(native.value("observation_interval",Json(1)),1000000);
  require(batch_size > 0 && interval > 0 && interval%batch_size == 0,
      "observation interval must be a positive multiple of transaction batch size");
  rows::Options options;
  options.native.memory_limit_bytes = number(native.at("memory_limit_bytes"));
  const auto work = number(native.value("work_limit",Json(1000000)));
  options.native.work_limit = work;
  options.native.multiplicity_limit = number(native.value("multiplicity_limit",Json(UINT64_MAX)));
  const auto compile_ns = elapsed(compiling,Clock::now());
  auto passes = Json::array();
  for (std::size_t pass=0; pass<request.warmups+request.repetitions; ++pass) {
    const auto initializing = Clock::now();
    const auto account = resource::MemoryAccount::create(options.native.memory_limit_bytes);
    auto owner = std::make_optional(runtime::SqlRowsRuntime::create_into(account,program,tree,physical,options));
    const auto initialize_ns = elapsed(initializing,Clock::now());
    auto transactions = Json::array(), epochs = Json::array();
    U64 sequence = 0, records = 0, captured = 0;
    const auto looping = Clock::now();
    for (std::size_t begin=0; begin<request.events.size();) {
      const auto end = begin+std::min<std::size_t>(batch_size,request.events.size()-begin);
      const bool observed = end%interval == 0 || end == request.events.size();
      U64 prepare_ns = 0, apply_ns = 0, output_ns = 0, emitted = 0, native_work = 0;
      storage::IndexWork source_work{}; bool changed = false;
      Json actual; Clock::time_point releasing;
      {
        const auto preparing = Clock::now();
        std::vector<std::array<rows::Cell,2>> cells; cells.reserve(end-begin);
        std::vector<rows::SourceReplacement> replacements; replacements.reserve(end-begin);
        for (std::size_t i=begin; i<end; ++i) {
          cells.push_back({storage::ScalarView{request.events[i].values[0]},
              storage::ScalarView{request.events[i].values[1]}});
          const U64 before = request.events[i].operation == "+" ? 0 : 1;
          replacements.push_back({targets[i],cells.back(),before,1-before});
        }
        prepare_ns = elapsed(preparing,Clock::now());
        const auto applying = Clock::now();
        // Repeated full-row edits form genuine before/after chains. The native
        // batch consolidates and publishes one endpoint; transport order is not
        // exposed as intermediate output and no adapter row ledger is retained.
        auto pending = owner->prepare_batch({++sequence,replacements});
        auto epoch = std::make_optional(pending.commit());
        apply_ns = elapsed(applying,Clock::now());
        native_work = epoch->native.metrics.work; source_work = epoch->source_work; changed = epoch->changed;
        const auto observing = Clock::now();
        if (observed) {
          if (request.verify) actual = Json::array();
          auto cursor = owner->results({work});
          while (auto row = cursor.next()) {
            add_records(records,1,request.max_records); ++emitted;
            if (request.verify) actual.push_back({{"values",nullable_values(row->tuple.view())},
                {"multiplicity",row->multiplicity}});
          }
        }
        output_ns = elapsed(observing,Clock::now());
        releasing = Clock::now(); epoch.reset();
      } // Transaction input buffers are destroyed inside the release phase.
      const auto release_ns = elapsed(releasing,Clock::now());
      if (observed) {
        admit_capture(actual,captured,request);
        epochs.push_back({{"sequence",sequence},{"physical_input_end",end},
            {"final_partial_observation",end%interval != 0},{"output_ns",time_value(request,output_ns)},
            {"output_records",emitted},{"actual",request.verify ? std::move(actual) : Json{}}});
      }
      transactions.push_back({{"sequence",sequence},{"physical_input_begin",begin+1},{"physical_input_end",end},
          {"source_replacements",end-begin},{"final_partial_transaction",end-begin != batch_size},
          {"first_input_phase",request.events[begin].phase},{"last_input_phase",request.events[end-1].phase},
          {"transaction_prepare_ns",time_value(request,prepare_ns)},{"apply_ns",time_value(request,apply_ns)},
          {"output_ns",time_value(request,output_ns)},{"release_ns",time_value(request,release_ns)},
          {"observed",observed},{"source_changed",changed},{"native_work",native_work},
          {"source_work",{{"structural_steps",source_work.structural_steps},{"scalar_fields",source_work.scalar_fields},
              {"scalar_bytes",source_work.scalar_bytes},{"pointer_slots",source_work.pointer_slots},
              {"link_actions",source_work.link_actions}}}});
      begin = end;
    }
    const auto loop_ns = elapsed(looping,Clock::now());
    const auto usage = memory(account.statistics());
    const auto destroying = Clock::now(); owner.reset();
    const auto teardown_ns = elapsed(destroying,Clock::now());
    passes.push_back({{"warmup",pass < request.warmups},{"initialize_ns",time_value(request,initialize_ns)},
        {"loop_wall_ns",time_value(request,loop_ns)},{"teardown_ns",time_value(request,teardown_ns)},
        {"transactions",std::move(transactions)},{"epochs",std::move(epochs)},
        {"output_records",records},{"captured_result_bytes",request.verify ? Json(captured) : Json{}},
        {"native_memory_before_teardown",usage}});
  }
  return report({{"schema_version",1},{"implementation","native_sql_rows"},
      {"sql_semantics",program.semantics() == frontend::SqlSemantics::bag ? "bag" : "distinct"},
      {"case_id",request.document.at("case_id")},{"query_family",request.document.at("query_family")},
      {"command",request.document.at("command")},{"output","compressed_bag"},
      {"read_request_ns",time_value(request,read_ns)},{"shared_program_ns",time_value(request,compile_ns)},
      {"transaction_batch_size",batch_size},{"observation_interval",interval},
      {"tree",program.contradiction() ? Json{} : io::write_tree(tree,core.catalog,core.query)},
      {"source_sha256",std::string(program.source_sha256())},{"physical_options",io::write_physical_options(physical)},
      {"passes",std::move(passes)},
      {"scope","genuine weighted SQL rows over unit-set physical facts; original SELECT bag or DISTINCT semantics; exact compressed tuple multiplicity, separate from unweighted set execution; real atomic net batches with native consolidation and no adapter row ledger; common physical observation boundaries and explicit final partials; no retained measured result graph, WAL, timing acceptance or dispatch-only causal claim"}});
}
} // namespace
int main(int argc, char** argv) {
  try { return run(argc,argv); }
  catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
