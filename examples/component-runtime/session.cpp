#include "native_request.hpp"
#include <crown/runtime/session_generation.hpp>
#include <crown/runtime/session_local_sink.hpp>
#include <algorithm>
#include <filesystem>
#include <optional>
#include <thread>

namespace {
using namespace crown;
using namespace component;
struct Controls {
  std::size_t batch_size;
  std::string action, durability, output;
  U64 checkpoint_interval;
  U64 consumer_delay_us;
  std::set<U64> recover_after;
  std::filesystem::path directory;
};
Controls controls(const Request& request, const runtime::DeltaOptions& options) {
  const auto& input = request.document.at("session");
  Controls result{number(input.value("transport_batch_size",Json(1)),1000000),
      input.value("output_action",std::string("discard")),
      input.value("durability",std::string("volatile")),request.document.at("output").get<std::string>(),
      number(input.value("checkpoint_interval",Json(0))),
      number(input.value("consumer_delay_us",Json(0)),100000),{},input.value("state_directory",std::string{})};
  require(result.batch_size > 0, "transport batch size must be positive");
  require(result.output == "none" || result.output == "cardinality" || result.output == "delta_and_snapshot",
      "unsupported session observation output");
  require(result.action == "maintenance" || result.action == "discard" || result.action == "serialize" || result.action == "durable",
      "unsupported session output action");
  require(result.durability == "volatile" || result.durability == "wal", "unsupported session durability");
  require(result.action != "maintenance" || (options.mode == runtime::DeltaMode::maintenance && result.output == "none"),
      "maintenance-only output requires maintenance mode and no service output");
  require(result.action != "durable" || (result.durability == "wal" && options.mode == runtime::DeltaMode::delta),
      "durable output requires a journaled delta-mode session");
  require(result.action != "serialize" || options.mode == runtime::DeltaMode::delta,
      "serialization requires actual delta output");
  require(result.consumer_delay_us == 0 || result.action != "maintenance",
      "synthetic consumer delay requires an output service boundary");
  require(result.output != "delta_and_snapshot" || options.mode == runtime::DeltaMode::delta,
      "delta observation requires delta mode");
  require(result.checkpoint_interval == 0 || result.checkpoint_interval%result.batch_size == 0,
      "checkpoint interval must align with transport boundaries");
  U64 previous = 0;
  for (const auto& item : input.value("recover_after",Json::array())) {
    const auto offset = number(item,request.events.size());
    require(offset > previous && (offset%result.batch_size == 0 || offset == request.events.size()),
        "recovery points must increase at empty-queue transport boundaries");
    result.recover_after.insert(offset); previous = offset;
  }
  require(result.durability == "wal" || (result.checkpoint_interval == 0 && result.recover_after.empty()),
      "checkpoint and reconstruction controls require WAL");
  require(result.durability != "wal" || !result.directory.empty(), "WAL requires a fresh state directory");
  return result;
}
std::array<char,32> identity(std::string_view hash) {
  std::array<char,32> result{}; std::copy_n(hash.begin(),result.size(),result.begin()); return result;
}
Json progress(const io::InputProgress& value) {
  return {{"sequence",value.sequence},{"source_positions",value.source_positions}};
}
int run(int argc, char** argv) {
  const auto reading = Clock::now();
  const auto request = read_request(argc,argv);
  const auto read_ns = elapsed(reading,Clock::now());
  const auto compiling = Clock::now();
  const auto compiled = compile_set(request.document);
  const auto& native = request.document.at("native");
  const auto options = delta_options(native);
  require(number(native.value("transaction_batch_size",Json(1))) == 1 &&
      number(native.value("observation_interval",Json(1))) == 1,
      "QuerySession preserves per-physical-event transactions and observations");
  const auto control = controls(request,options);
  const auto targets = target_tables(request,compiled.catalog);
  io::QueueLimits queue;
  queue.batches = 1; queue.events = control.batch_size;
  queue.bytes = number(native.value("queue_bytes",Json(64U*1024U*1024U)),SIZE_MAX);
  runtime::SessionOptions session_options;
  session_options.delta = options;
  session_options.snapshot.rows = static_cast<std::size_t>(std::min<U64>(request.max_records,SIZE_MAX));
  session_options.snapshot.bytes = static_cast<std::size_t>(std::min<U64>(request.max_bytes,SIZE_MAX));
  session_options.snapshot.cursor = options.cursor;
  runtime::SessionGenerationOptions generation;
  generation.journal.query_id = identity(compiled.program.physical_source_sha256());
  // Rotation retains history. This finite trace-derived grant avoids silently
  // deleting old generations to keep a trial running.
  generation.retained_generations = request.events.size()+1;
  runtime::SessionGenerationRecoveryOptions recovery;
  recovery.replay.journal.query_id = generation.journal.query_id;
  recovery.replay.memory_limit_bytes = options.physical.support.memory_limit_bytes;
  recovery.replay.output_rows = static_cast<std::size_t>(std::min<U64>(request.max_records,SIZE_MAX));
  recovery.replay.output_bytes = static_cast<std::size_t>(std::min<U64>(request.max_bytes,SIZE_MAX));
  recovery.retained_generations = generation.retained_generations;
  runtime::SessionLocalSinkOptions sink;
  sink.sink_id = identity(compiled.program.physical_sha256());
  const auto compile_ns = elapsed(compiling,Clock::now());
  auto passes = Json::array();
  for (std::size_t pass=0; pass<request.warmups+request.repetitions; ++pass) {
    const auto initializing = Clock::now();
    auto owner = runtime::QuerySession::create_typed(compiled.program,queue,session_options);
    std::filesystem::path pass_directory, root_path, sink_path;
    if (control.durability == "wal") {
      std::filesystem::create_directories(control.directory);
      pass_directory = control.directory/("pass-"+std::to_string(pass));
      require(std::filesystem::create_directory(pass_directory), "session pass directory already exists");
      root_path = pass_directory/"query.root"; sink_path = pass_directory/"query.sink";
      owner->enable_generation(root_path.string(),generation);
      if (control.action == "durable") owner->create_local_sink(sink_path.string(),sink);
    }
    owner->start();
    const auto initialize_ns = elapsed(initializing,Clock::now());
    TextSink text_sink(false,request.max_bytes); std::ostream serialized(&text_sink);
    auto epochs = Json::array(), batches = Json::array(); U64 records = 0, captured = 0;
    U64 owner_peak_max = owner->accounted_memory_statistics()->peak_requested_bytes;
    const auto looping = Clock::now();
    for (std::size_t begin=0; begin<request.events.size();) {
      const auto end = begin+std::min(control.batch_size,request.events.size()-begin);
      U64 prepare_ns = 0, enqueue_ns = 0;
      {
        const auto preparing = Clock::now();
        std::vector<io::InputItem> items; items.reserve(end-begin);
        for (std::size_t i=begin; i<end; ++i) items.emplace_back(io::InputEvent{
            {i+1,targets[i],operation(request.events[i]),Row{request.events[i].values[0],request.events[i].values[1]}},
            io::SourcePosition{"component_event_offset",i+1}});
        io::TransportBatch batch(std::move(items),{control.batch_size,queue.bytes});
        prepare_ns = elapsed(preparing,Clock::now());
        const auto enqueuing = Clock::now();
        require(owner->enqueue(batch) == io::Admission::accepted, "session transport queue is full");
        enqueue_ns = elapsed(enqueuing,Clock::now());
      }
      for (std::size_t i=begin; i<end; ++i) {
        const auto applying = Clock::now();
        require(owner->begin_next(), "session ended before its queued physical input");
        while (owner->step() != runtime::DeltaStep::prepared) {}
        owner->commit();
        const auto apply_ns = elapsed(applying,Clock::now());
        const auto observing = Clock::now();
        // An explicit synthetic slow consumer retains this actual committed
        // epoch. The wait is included in output/loop wall time, not native work.
        U64 consumer_wait_ns = 0;
        if (control.consumer_delay_us) {
          const auto waiting = Clock::now();
          std::this_thread::sleep_for(std::chrono::microseconds(control.consumer_delay_us));
          consumer_wait_ns = elapsed(waiting,Clock::now());
        }
        auto delta = Json::array(); U64 delta_rows = 0;
        if (control.action == "durable") {
          auto delivered = owner->deliver_local_epoch();
          while (delivered.kind != runtime::LocalDeliveryKind::idle) {
            delta_rows += delivered.rows; delivered = owner->deliver_local_epoch();
          }
          if (request.verify && control.output == "delta_and_snapshot") {
            const auto persisted = owner->read_local_epoch(owner->status().committed_sequence);
            for (const auto& row : persisted.rows)
              delta.push_back(signed_values(row.operation,storage::TupleValuesView::borrow(row.values.view())));
          }
        } else {
          while (auto row = owner->next_output()) {
            ++delta_rows;
            if (control.action == "serialize") {
              const auto encoded = signed_values(row->operation,row->tuple.values()).dump();
              serialized << encoded << '\n'; serialized.flush();
              require(bool(serialized), "session serialization output failed");
            }
            if (request.verify && control.output == "delta_and_snapshot")
              delta.push_back(signed_values(row->operation,row->tuple.values()));
          }
        }
        U64 snapshot_rows = 0; auto rows = Json::array();
        std::optional<runtime::SessionSnapshot> snapshot;
        // With no service output, verification alone performs this explicit
        // committed read. Measure maintenance-only trials never enumerate here.
        if (control.output != "none" || request.verify) {
          snapshot.emplace(owner->snapshot()); snapshot_rows = snapshot->rows.size();
          if (request.verify && control.output != "cardinality")
            for (const auto& row : snapshot->rows) rows.push_back(tuple_values(row.values()));
        }
        add_records(records,delta_rows+(control.output == "none" ? 0 : snapshot_rows),request.max_records);
        const auto output_ns = elapsed(observing,Clock::now());
        const auto releasing = Clock::now(); snapshot.reset();
        const auto release_ns = elapsed(releasing,Clock::now());
        Json actual;
        if (request.verify) {
          if (control.output == "cardinality") actual = snapshot_rows;
          else if (control.output == "none") actual = {{"rows",std::move(rows)}};
          else actual = {{"delta",std::move(delta)},{"rows",std::move(rows)}};
        }
        admit_capture(actual,captured,request);
        epochs.push_back({{"sequence",owner->status().committed_sequence},{"physical_input_end",i+1},
            {"phase",request.events[i].phase},{"apply_ns",time_value(request,apply_ns)},
            {"output_ns",time_value(request,output_ns)},{"release_ns",time_value(request,release_ns)},
            {"consumer_wait_ns",time_value(request,consumer_wait_ns)},
            {"delta_records",delta_rows},{"snapshot_records",control.output == "none" ? Json{} : Json(snapshot_rows)},
            {"actual",request.verify ? std::move(actual) : Json{}}});
      }
      U64 checkpoint_ns = 0, recovery_ns = 0, replay_output_rows = 0;
      const bool checkpointed = control.checkpoint_interval > 0 &&
          (end%control.checkpoint_interval == 0 || end == request.events.size());
      if (checkpointed) {
        const auto checkpointing = Clock::now(); owner->pause(); owner->rotate_generation(); owner->start();
        checkpoint_ns = elapsed(checkpointing,Clock::now());
      }
      const bool reconstructed = control.recover_after.contains(end);
      const auto before_recovery = *owner->accounted_memory_statistics();
      owner_peak_max = std::max(owner_peak_max,before_recovery.peak_requested_bytes);
      if (reconstructed) {
        const auto reconstructing = Clock::now(); owner->pause(); owner.reset();
        if (control.action == "durable") owner = runtime::QuerySession::restore_generation_with_local_sink(
            compiled.program,root_path.string(),recovery,sink_path.string(),sink);
        else {
          owner = runtime::QuerySession::restore_generation(compiled.program,root_path.string(),recovery);
          while (owner->next_recovered_output()) ++replay_output_rows;
        }
        owner->start(); recovery_ns = elapsed(reconstructing,Clock::now());
      }
      const auto after_recovery = *owner->accounted_memory_statistics();
      owner_peak_max = std::max(owner_peak_max,after_recovery.peak_requested_bytes);
      batches.push_back({{"physical_input_begin",begin+1},{"physical_input_end",end},
          {"transport_events",end-begin},{"final_partial_transport",end-begin != control.batch_size},
          {"transport_prepare_ns",time_value(request,prepare_ns)},{"enqueue_ns",time_value(request,enqueue_ns)},
          {"checkpointed",checkpointed},{"checkpoint_ns",time_value(request,checkpoint_ns)},
          {"reconstructed",reconstructed},{"recovery_ns",time_value(request,recovery_ns)},
          {"native_memory_before_recovery",memory(before_recovery)},
          {"native_memory_after_recovery",memory(after_recovery)},
          {"replay_output_rows_consumed",replay_output_rows}});
      begin = end;
    }
    owner->finish_input();
    require(owner->begin_next_result() == runtime::SessionBegin::end, "session input did not reach clean EOF");
    const auto loop_ns = elapsed(looping,Clock::now());
    const auto accepted_progress = progress(owner->progress());
    const auto final_memory = *owner->accounted_memory_statistics();
    const auto usage = memory(final_memory);
    owner_peak_max = std::max(owner_peak_max,final_memory.peak_requested_bytes);
    Json durable_state;
    if (control.durability == "wal") durable_state = {{"generation",owner->generation_state().selected.generation},
        {"wal_records",owner->journal_state().records},{"wal_physical_sequence",owner->journal_state().physical_sequence},
        {"verified_sink_sequence",control.action == "durable" ? Json(owner->local_sink_receipt().sequence()) : Json{}},
        {"root_path",root_path.string()},{"sink_path",control.action == "durable" ? Json(sink_path.string()) : Json{}}};
    const auto destroying = Clock::now(); owner.reset();
    const auto teardown_ns = elapsed(destroying,Clock::now());
    passes.push_back({{"warmup",pass < request.warmups},{"initialize_ns",time_value(request,initialize_ns)},
        {"loop_wall_ns",time_value(request,loop_ns)},{"teardown_ns",time_value(request,teardown_ns)},
        {"output_records",records},{"serialized_bytes",text_sink.bytes},
        {"captured_result_bytes",request.verify ? Json(captured) : Json{}},{"accepted_progress",accepted_progress},
        {"native_memory_before_teardown",usage},{"durable_state",std::move(durable_state)},
        {"sampled_owner_peak_max_requested_bytes",owner_peak_max},
        {"batches",std::move(batches)},{"epochs",std::move(epochs)}});
  }
  return report({{"schema_version",1},{"implementation","native_query_session"},
      {"case_id",request.document.at("case_id")},{"query_family",request.document.at("query_family")},
      {"command",request.document.at("command")},{"output",control.output},{"session",request.document.at("session")},
      {"read_request_ns",time_value(request,read_ns)},{"shared_program_ns",time_value(request,compile_ns)},
      {"physical_sha256",std::string(compiled.program.physical_sha256())},
      {"physical_options",io::write_physical_options(compiled.physical)},{"passes",std::move(passes)},
      {"scope","actual typed QuerySession with per-physical-event commitment; transport batching preserves every event boundary; real output discard/serialization or whole durable local delivery, not delivery inferred from WAL; WAL includes initial checkpoint and retained history; clean-owner recovery/checkpoint phases use public factories, no process-crash or power-loss claim; cardinality observation materializes actual SessionSnapshot; verification-only reads with output none are outside any accepted timing; no timing acceptance or row ledger"}});
}
} // namespace
int main(int argc, char** argv) {
  try { return run(argc,argv); }
  catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
