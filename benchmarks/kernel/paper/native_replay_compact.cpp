#include "paper_input.hpp"
#include <crown/runtime/compact.hpp>
#include <sched.h>

namespace {
namespace compact = crown::runtime::compact;
constexpr std::string_view backend = "compact_typed_row_v1";

struct Route {
  TableId table;
  std::optional<std::int64_t> minimum_destination;
};

std::vector<Route> resolve_routes(const Json& bindings, const std::map<std::string, TableId>& tables) {
  std::vector<Route> routes;
  for (const auto& item : bindings) {
    const auto table = tables.find(item.at("table").get<std::string>());
    require(table != tables.end(), "unknown routed table");
    std::optional<std::int64_t> threshold;
    if (item.contains("min_dst_exclusive") && !item.at("min_dst_exclusive").is_null())
      threshold = item.at("min_dst_exclusive").get<std::int64_t>();
    routes.push_back({table->second, threshold});
  }
  require(!routes.empty(), "empty alias list");
  return routes;
}

int pinned_cpu() {
  cpu_set_t cpus;
  CPU_ZERO(&cpus);
  require(sched_getaffinity(0, sizeof(cpus), &cpus) == 0 && CPU_COUNT(&cpus) == 1,
          "compact paper replay requires affinity to exactly one CPU");
  for (int cpu = 0; cpu < CPU_SETSIZE; ++cpu)
    if (CPU_ISSET(cpu, &cpus)) return cpu;
  throw std::runtime_error("empty CPU affinity");
}

enum class Frame { snapshot, delta, final };

class Output final : public compact::RowSink {
 public:
  Output(const Json& request, const compact::Runtime& runtime, bool verify)
      : runtime_(runtime), verify_(verify), max_rows_(request.at("limits").at("output_rows").get<U64>()),
        max_bytes_(request.at("limits").at("capture_bytes").get<U64>()) {
    if (verify_) {
      file_.open(request.at("capture_file").get<std::string>(), std::ios::out | std::ios::noreplace);
      require(bool(file_), "cannot create fresh compact capture");
    }
  }

  void begin(Frame frame, U64 sequence, U64 marker = 0) {
    frame_ = frame;
    sequence_ = sequence;
    marker_ = marker;
    frame_rows = 0;
    if (!verify_) return;
    if (frame == Frame::snapshot)
      emit({{"kind", "snapshot_begin"}, {"sequence", sequence}, {"marker", marker}});
    else
      emit({{"kind", frame == Frame::delta ? "delta_begin" : "final_begin"}, {"sequence", sequence}});
  }

  void relation(U64 sequence, SetOperation operation) {
    relation_ = sequence;
    operation_ = operation;
  }

  void row(const compact::Word* words) override {
    if (frame_ == Frame::final) {
      require(frame_rows < max_rows_, "final result row limit exceeded");
    } else {
      require(timed_rows < max_rows_, "paper output row limit exceeded");
      ++timed_rows;
    }
    ++frame_rows;
    if (!verify_) return;
    Json result = {{"sequence", sequence_}, {"values", Json::array()}};
    for (const auto& cell : runtime_.decode(words)) result["values"].push_back(io::write_scalar(cell));
    if (frame_ == Frame::delta) {
      result["kind"] = "delta_row";
      result["relation_sequence"] = relation_;
      result["operation"] = operation_ == SetOperation::insert ? "+" : "-";
    } else if (frame_ == Frame::snapshot) {
      result["kind"] = "snapshot_row";
      result["marker"] = marker_;
    } else {
      result["kind"] = "final_row";
    }
    emit(result);
  }

  void end() {
    if (!verify_) return;
    if (frame_ == Frame::snapshot)
      emit({{"kind", "snapshot_end"}, {"sequence", sequence_}, {"marker", marker_}, {"rows", frame_rows}});
    else
      emit({{"kind", frame_ == Frame::delta ? "delta_end" : "final_end"}, {"sequence", sequence_}, {"rows", frame_rows}});
  }

  void finish_capture() {
    if (verify_) {
      file_.close();
      require(!file_.fail(), "compact capture close failed");
    }
  }

  U64 frame_rows{}, timed_rows{}, captured_bytes{};

 private:
  void emit(const Json& value) {
    auto line = value.dump();
    line.push_back('\n');
    require(line.size() <= max_bytes_ - captured_bytes, "paper capture byte limit exceeded");
    file_.write(line.data(), static_cast<std::streamsize>(line.size()));
    require(bool(file_), "paper capture write failed");
    captured_bytes += line.size();
  }
  const compact::Runtime& runtime_;
  bool verify_;
  U64 max_rows_, max_bytes_;
  std::ofstream file_;
  Frame frame_ = Frame::final;
  U64 sequence_{}, relation_{}, marker_{};
  SetOperation operation_ = SetOperation::insert;
};

int run(int argc, char** argv) {
  require(argc == 3, "usage: paper_native_compact_routed REQUEST.json INPUT");
  const int cpu = pinned_cpu();
  auto started = Clock::now();
  std::ifstream configuration(argv[1]);
  require(bool(configuration), "cannot open compact request");
  const auto request = io::read_json(std::string(std::istreambuf_iterator<char>(configuration), {}));
  require(request.at("schema_version") == 1 && request.at("measurement_backend") == backend,
          "expected an explicit compact_typed_row_v1 paper request");
  const auto mode = request.at("output_mode").get<std::string>();
  require(mode == "full" || mode == "delta" || mode == "none", "unknown paper output mode");
  const bool verify = request.at("command") == "verify";
  require(verify || request.at("command") == "measure", "unknown paper replay command");
  require(request.value("native_execution", std::string("routed_set")) == "routed_set",
          "compact adapter accepts original routed set bindings only");
  const auto format = request.at("input_format").get<std::string>();
  const auto routing = request.at("routing").get<std::string>();
  const bool tagged = routing == "original_tagged_relations" && format == "tagged_csv";
  require(tagged || (routing == "original_flink_graph_aliases" && format == "graph_csv"),
          "unknown original routed set format");
  const bool full_at_markers = mode == "full" || request.value("full_at_markers", false);
  const auto read_ns = nanos(started);
  started = Clock::now();
  const auto compiled = compile_set(request);
  const auto plan = PhysicalPlan::from_compiled(compiled.program);
  const auto compile_ns = nanos(started);
  started = Clock::now();
  compact::Options options;
  options.memory_limit_bytes = number(request.at("native").at("memory_limit_bytes"));
  auto runtime = std::make_unique<compact::Runtime>(plan, options);
  const auto initialize_ns = nanos(started);
  std::map<std::string, TableId> tables;
  for (std::size_t i = 0; i < compiled.catalog.tables.size(); ++i)
    tables.emplace(compiled.catalog.tables[i].name, TableId{i});
  std::vector<Route> graph_routes;
  std::map<std::string, std::vector<Route>> tag_routes;
  if (tagged) {
    for (const auto& [tag, entries] : request.at("tag_routes").items())
      tag_routes.emplace(tag, resolve_routes(entries, tables));
  } else {
    graph_routes = resolve_routes(request.at("graph_aliases"), tables);
  }

  std::unique_ptr<GzipBuffer> gzip;
  std::unique_ptr<std::istream> input;
  if (std::string_view(argv[2]).ends_with(".gz")) {
    gzip = std::make_unique<GzipBuffer>(argv[2]);
    input = std::make_unique<std::istream>(gzip.get());
  } else {
    input = std::make_unique<std::ifstream>(argv[2]);
  }
  require(bool(*input), "cannot open paper input");
  Output output(request, *runtime, verify);
  const auto max_events = request.at("limits").at("input_events").get<U64>();
  U64 edits{}, relations{}, markers{}, input_lines{}, unchanged{}, snapshot_rows{}, positive{}, negative{};
  U64 decode_ns{}, apply_ns{}, output_ns{};
  auto frames = Json::array();
  std::vector<std::array<U64, 2>> by_table(tables.size());
  const auto looping = Clock::now();
  std::string line;
  while (std::getline(*input, line)) {
    ++input_lines;
    started = Clock::now();
    const auto edit = decode(line, tables, format, TableId{});
    decode_ns += nanos(started);
    if (edit.enumerate) {
      ++markers;
      if (full_at_markers) {
        started = Clock::now();
        output.begin(Frame::snapshot, edits, markers);
        runtime->enumerate(output);
        output.end();
        output_ns += nanos(started);
        snapshot_rows += output.frame_rows;
        frames.push_back({{"sequence", edits}, {"marker", markers}, {"rows", output.frame_rows}});
      }
      continue;
    }
    require(edits < max_events, "paper input event limit exceeded");
    ++edits;
    const auto* routes = &graph_routes;
    if (tagged) {
      const auto found = tag_routes.find(edit.tag);
      require(found != tag_routes.end(), "unknown tagged input relation");
      routes = &found->second;
    }
    if (mode == "delta") output.begin(Frame::delta, edits);
    for (const auto& route : *routes) {
      if (route.minimum_destination && std::get<std::int64_t>(edit.values.at(1)) <= *route.minimum_destination)
        continue;
      ++relations;
      output.relation(relations, edit.operation);
      const auto before = output.frame_rows;
      started = Clock::now();
      const bool changed = runtime->apply(route.table, edit.operation, edit.values, mode == "delta" ? &output : nullptr);
      apply_ns += nanos(started);
      if (!changed) ++unchanged;
      if (mode == "delta")
        by_table[route.table.value][edit.operation == SetOperation::insert ? 0 : 1] += output.frame_rows - before;
    }
    if (mode == "delta") {
      output.end();
      (edit.operation == SetOperation::insert ? positive : negative) += output.frame_rows;
    }
  }
  require(!input->bad(), "paper stream read failed");
  const auto loop_ns = nanos(looping);
  if (request.contains("expected_physical_inputs"))
    require(edits == request.at("expected_physical_inputs").get<U64>(), "physical input horizon mismatch");
  if (request.contains("expected_markers"))
    require(markers == request.at("expected_markers").get<U64>(), "marker horizon mismatch");
  started = Clock::now();
  Json final_rows;
  if (verify) {
    output.begin(Frame::final, edits);
    runtime->enumerate(output);
    output.end();
    output.finish_capture();
    final_rows = output.frame_rows;
  }
  const auto final_check_ns = nanos(started);
  auto alias_counts = Json::object();
  for (const auto& [name, table] : tables) {
    const auto& rows = by_table[table.value];
    alias_counts[name] = {{"insert", rows[0]}, {"erase", rows[1]}};
  }
  const auto usage = memory(runtime->memory_statistics());
  started = Clock::now();
  runtime.reset();
  const auto teardown_ns = nanos(started);
  return report({{"schema_version", 1}, {"implementation", "native_crown_compact_routed"},
      {"backend", backend}, {"parallelism", 1}, {"cpu", cpu}, {"case_id", request.at("case_id")},
      {"status", "complete"}, {"command", request.at("command")}, {"output_mode", mode},
      {"input_format", format}, {"routing", routing}, {"full_at_markers", full_at_markers},
      {"physical_inputs", edits}, {"input_lines", input_lines}, {"relation_updates", relations},
      {"unchanged_relation_updates", unchanged}, {"enumeration_markers", markers}, {"output_rows", output.timed_rows},
      {"signed_insert_rows", positive}, {"signed_erase_rows", negative}, {"delta_rows", positive + negative},
      {"delta_rows_by_table", std::move(alias_counts)}, {"snapshot_rows", snapshot_rows},
      {"snapshots", std::move(frames)}, {"final_rows", final_rows}, {"capture_bytes", output.captured_bytes},
      {"physical_sha256", std::string(compiled.program.physical_sha256())},
      {"source_sha256", std::string(compiled.program.physical_source_sha256())},
      {"physical_options", io::write_physical_options(compiled.physical)},
      {"read_request_ns", read_ns}, {"compile_ns", compile_ns}, {"initialize_ns", initialize_ns},
      {"loop_wall_ns", loop_ns}, {"decode_ns", decode_ns}, {"apply_ns", apply_ns}, {"output_ns", output_ns},
      {"epoch_release_ns", 0}, {"api_active_ns", apply_ns + output_ns}, {"final_check_ns", final_check_ns},
      {"teardown_ns", teardown_ns}, {"memory_before_teardown", usage},
      {"timing", "apply_ns includes synchronous signed row callbacks; output_ns covers marker enumeration; compact has no epoch release."}});
}
}  // namespace

int main(int argc, char** argv) {
  try { return run(argc, argv); }
  catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
