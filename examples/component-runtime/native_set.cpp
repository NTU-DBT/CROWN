#include "native_request.hpp"
#include <crown/runtime/update_view.hpp>
#include <optional>

namespace {
using namespace crown;
using namespace component;

// Read genuine epoch-zero results, including nullary truth and EXISTS(false).
// Only the cardinality survives; no result-row dictionary is retained.
U64 initial_cardinality(runtime::DeltaRuntime& owner, U64 work) {
  U64 result = 0;
  auto cursor = owner.results({work});
  while (cursor.next()) add_records(result,1,UINT64_MAX);
  return result;
}
void fold_cardinality(U64& count, SetOperation sign) {
  if (sign == SetOperation::insert) add_records(count,1,UINT64_MAX);
  else { require(count > 0, "set delta would underflow cardinality"); --count; }
}
int run(int argc, char** argv) {
  const auto reading = Clock::now();
  const auto request = read_request(argc, argv);
  const auto read_ns = elapsed(reading, Clock::now());
  const auto output = request.document.at("output").get<std::string>();
  require(output == "cardinality" || output == "delta_and_snapshot", "unsupported native set output");
  const auto compiling = Clock::now();
  const auto compiled = compile_set(request.document);
  const auto& native = request.document.at("native");
  const auto options = delta_options(native);
  require(number(native.value("transaction_batch_size",Json(1))) == 1,
      "unweighted set execution preserves one transaction per physical event");
  const auto targets = target_tables(request, compiled.catalog);
  const auto interval = number(native.value("observation_interval", Json(1)), SIZE_MAX);
  require(interval > 0, "observation interval must be positive");
  require(output != "delta_and_snapshot" || (interval == 1 && options.mode == runtime::DeltaMode::delta),
      "delta and snapshot output requires one observation per delta-mode input");
  const auto work = number(native.value("work_limit", Json(1000000)));
  const auto compile_ns = elapsed(compiling, Clock::now());
  auto passes = Json::array();
  for (std::size_t pass=0; pass<request.warmups+request.repetitions; ++pass) {
    const auto initializing = Clock::now();
    auto owner = std::make_optional<runtime::DeltaRuntime>(compiled.program, options);
    U64 cardinality = initial_cardinality(*owner, work);
    const auto initialize_ns = elapsed(initializing, Clock::now());
    auto epochs = Json::array(); U64 records = 0, captured = 0, delta_records = 0;
    const auto looping = Clock::now();
    for (std::size_t i=0; i<request.events.size(); ++i) {
      const auto& event = request.events[i];
      const std::array<storage::ScalarView,2> cells{event.values[0], event.values[1]};
      const auto applying = Clock::now();
      auto epoch = std::make_optional(owner->apply_view({i+1, targets[i], operation(event),
          storage::TupleValuesView::borrow(storage::RowView::borrow(cells))}));
      const auto apply_ns = elapsed(applying, Clock::now());
      const bool observed = (i+1)%interval == 0 || i+1 == request.events.size();
      const auto observing = Clock::now();
      auto delta = Json::array();
      U64 emitted_delta = 0;
      // These are actual projected DISTINCT set records. Folding them retains
      // one scalar and includes all internal delta-output work in this phase.
      while (auto row = epoch->next()) {
        fold_cardinality(cardinality,row->operation);
        ++emitted_delta; ++delta_records;
        if (request.verify && output == "delta_and_snapshot")
          delta.push_back(signed_values(row->operation, row->tuple.values()));
      }
      auto rows = Json::array(); U64 snapshot_rows = 0;
      if (observed && (output == "delta_and_snapshot" || options.mode == runtime::DeltaMode::maintenance)) {
        auto cursor = owner->results({work});
        while (auto row = cursor.next()) {
          ++snapshot_rows;
          if (request.verify && output == "delta_and_snapshot") rows.push_back(tuple_values(row->values()));
        }
        cardinality = snapshot_rows;
      }
      if (observed) add_records(records, output == "cardinality" ? 1 : emitted_delta+snapshot_rows, request.max_records);
      const auto output_ns = elapsed(observing, Clock::now());
      const auto releasing = Clock::now(); epoch.reset();
      const auto release_ns = elapsed(releasing, Clock::now());
      Json actual;
      if (request.verify && observed) actual = output == "cardinality" ? Json(cardinality) :
          Json{{"delta", std::move(delta)}, {"rows", std::move(rows)}};
      if (observed) admit_capture(actual, captured, request);
      epochs.push_back({{"sequence", i+1}, {"physical_input_end", i+1}, {"phase", event.phase},
          {"observed", observed}, {"final_partial_observation", observed && (i+1)%interval != 0},
          {"apply_ns", time_value(request,apply_ns)}, {"output_ns", time_value(request,output_ns)},
          {"release_ns", time_value(request,release_ns)}, {"delta_records", emitted_delta},
          {"snapshot_records", snapshot_rows}, {"cardinality", observed ? Json(cardinality) : Json{}},
          {"actual", request.verify ? std::move(actual) : Json{}}});
    }
    const auto loop_ns = elapsed(looping, Clock::now());
    const auto usage = memory(owner->accounted_memory_statistics());
    const auto destroying = Clock::now(); owner.reset();
    const auto teardown_ns = elapsed(destroying, Clock::now());
    passes.push_back({{"warmup", pass < request.warmups}, {"initialize_ns", time_value(request,initialize_ns)},
        {"loop_wall_ns", time_value(request,loop_ns)}, {"teardown_ns", time_value(request,teardown_ns)},
        {"output_records", records}, {"internal_delta_records", delta_records},
        {"captured_result_bytes", request.verify ? Json(captured) : Json{}},
        {"native_memory_before_teardown", usage}, {"epochs", std::move(epochs)}});
  }
  return report({{"schema_version",1}, {"implementation","native_unweighted_set"},
      {"case_id",request.document.at("case_id")}, {"query_family",request.document.at("query_family")},
      {"command",request.document.at("command")}, {"output",output},
      {"read_request_ns",time_value(request,read_ns)}, {"shared_program_ns",time_value(request,compile_ns)},
      {"physical_sha256",std::string(compiled.program.physical_sha256())},
      {"source_sha256",std::string(compiled.program.physical_source_sha256())},
      {"physical_options",io::write_physical_options(compiled.physical)}, {"passes",std::move(passes)},
      {"scope","unweighted original-SQL projected set; cardinality is COUNT DISTINCT of actual SQL output tuples, never COUNT(*); delta mode folds exact signed set records, maintenance cardinality drains actual current results; fresh owner per pass; compiler/input/report DTOs outside native account; no WAL, row ledger, timing acceptance or pure-dispatch claim"}});
}
} // namespace
int main(int argc, char** argv) {
  try { return run(argc,argv); }
  catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
