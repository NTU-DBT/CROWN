#include "paper_input.hpp"
#include <crown/resource/allocator.hpp>
#include <set>
#include <unordered_map>
#include <unordered_set>

namespace {
using Vertex = std::int64_t;
using Triangle = std::array<Vertex, 3>;
using resource::MemoryAccount;
using resource::MemoryAllocator;
using resource::MemoryPurpose;

template<bool Indexed, class Key, class Value>
using Map = std::conditional_t<Indexed,
    std::unordered_map<Key, Value, std::hash<Key>, std::equal_to<Key>,
                       MemoryAllocator<std::pair<const Key, Value>>>,
    std::map<Key, Value, std::less<Key>, MemoryAllocator<std::pair<const Key, Value>>>>;

template<bool Indexed>
class DirectedEdges {
  using Neighbors = std::conditional_t<Indexed,
      std::unordered_set<Vertex, std::hash<Vertex>, std::equal_to<Vertex>, MemoryAllocator<Vertex>>,
      std::set<Vertex, std::less<Vertex>, MemoryAllocator<Vertex>>>;
  using Buckets = Map<Indexed, Vertex, Neighbors>;
  using BucketAllocator = MemoryAllocator<std::pair<const Vertex, Neighbors>>;

 public:
  explicit DirectedEdges(const MemoryAccount& account)
      : account_(account), outgoing_(BucketAllocator(account, MemoryPurpose::table_state)),
        incoming_(BucketAllocator(account, MemoryPurpose::table_state)) {}

  bool update(Vertex source, Vertex destination, bool insert) {
    const auto found = outgoing_.find(source);
    const bool present = found != outgoing_.end() && found->second.contains(destination);
    if (present == insert) return false;
    if (insert) {
      add(outgoing_, source, destination);
      add(incoming_, destination, source);
    } else {
      remove(outgoing_, source, destination);
      remove(incoming_, destination, source);
    }
    return true;
  }

  const Neighbors* successors(Vertex vertex) const { return neighbors(outgoing_, vertex); }
  const Neighbors* predecessors(Vertex vertex) const { return neighbors(incoming_, vertex); }

 private:
  static const Neighbors* neighbors(const Buckets& buckets, Vertex key) {
    const auto found = buckets.find(key);
    return found == buckets.end() ? nullptr : &found->second;
  }

  void add(Buckets& buckets, Vertex key, Vertex value) {
    const auto bucket = buckets.try_emplace(key, MemoryAllocator<Vertex>(account_, MemoryPurpose::table_state)).first;
    bucket->second.insert(value);
  }

  static void remove(Buckets& buckets, Vertex key, Vertex value) {
    const auto bucket = buckets.find(key);
    require(bucket != buckets.end() && bucket->second.erase(value) == 1, "missing reverse edge");
    if (bucket->second.empty()) buckets.erase(bucket);
  }

  MemoryAccount account_;
  Buckets outgoing_, incoming_;
};

template<bool Indexed>
class TriangleState {
 public:
  TriangleState(const MemoryAccount& account, std::size_t anchor)
      : edges_{DirectedEdges<Indexed>(account), DirectedEdges<Indexed>(account), DirectedEdges<Indexed>(account)},
        support_(MemoryAllocator<std::pair<const Vertex, std::uint64_t>>(account, MemoryPurpose::support_metadata)),
        anchor_(anchor) {}

  template<class Publish>
  void update(std::size_t edge, Vertex source, Vertex destination, bool insert, bool project, Publish&& publish) {
    if (!edges_[edge].update(source, destination, insert)) return;
    const auto next = (edge + 1) % 3;
    const auto end = (edge + 2) % 3;
    auto first = edges_[next].successors(destination);
    auto second = edges_[end].predecessors(source);
    if (!first || !second) return;
    if (first->size() > second->size()) std::swap(first, second);
    Triangle row{};
    row[edge] = source;
    row[next] = destination;
    // The three edge labels own separate sets, even when their values coincide.
    for (const auto vertex : *first) {
      if (!second->contains(vertex)) continue;
      row[end] = vertex;
      if (!project) {
        publish(std::span<const Vertex>(row));
      } else if (change_support(row[anchor_], insert)) {
        publish(std::span<const Vertex>(&row[anchor_], 1));
      }
    }
  }

 private:
  bool change_support(Vertex key, bool insert) {
    if (insert) {
      auto [entry, fresh] = support_.try_emplace(key, 0);
      require(entry->second < UINT64_MAX, "triangle support overflow");
      ++entry->second;
      return fresh;
    }
    const auto entry = support_.find(key);
    require(entry != support_.end() && entry->second != 0, "triangle support underflow");
    if (--entry->second != 0) return false;
    support_.erase(entry);
    return true;
  }

  std::array<DirectedEdges<Indexed>, 3> edges_;
  Map<Indexed, Vertex, std::uint64_t> support_;
  std::size_t anchor_;
};

Table table(std::string name, std::string_view columns) {
  Table result;
  result.name = std::move(name);
  for (char column : columns) result.columns.push_back({std::string(1, column), ScalarType::int64});
  return result;
}

constexpr std::string_view original_join =
    " FROM m,lbc,lca,rde,rfd,lab,ref WHERE lab.b=lbc.b AND lbc.c=lca.c AND lca.a=lab.a"
    " AND m.c=lbc.c AND m.d=rde.d AND rde.e=ref.e AND ref.f=rfd.f AND rfd.d=m.d";
constexpr std::string_view outer_join =
    " FROM left_triangle,middle,right_triangle WHERE left_triangle.c=middle.c AND middle.d=right_triangle.d";
constexpr std::array<std::string_view, 7> aliases{"m", "lbc", "lca", "rde", "rfd", "lab", "ref"};

enum class Side { middle, left, right };
struct Route {
  Side side;
  std::size_t edge;
};
constexpr std::array<Route, 7> routes{{
    {Side::middle, 0}, {Side::left, 1}, {Side::left, 2}, {Side::right, 0},
    {Side::right, 2}, {Side::left, 0}, {Side::right, 1},
}};

struct Binding {
  bool project;
  Vertex threshold;
  SetProgram outer;
};

Binding bind(const Json& request) {
  require(request.at("schema_version") == 1 && request.at("input_format") == "graph_csv" &&
          request.at("routing") == "original_dumbbell_ordered_aliases", "unsupported dumbbell binding");
  const bool project = request.at("query_family") == "dumbbell-project";
  require(project || request.at("query_family") == "dumbbell-full", "unsupported dumbbell query family");
  require(request.at("case_id").is_string(), "dumbbell case ID must be a string");
  const Catalog source{1, {table("m", "cd"), table("lbc", "bc"), table("lca", "ca"),
                           table("rde", "de"), table("rfd", "fd"), table("lab", "ab"), table("ref", "ef")}};
  const auto& program = request.at("program");
  const auto supplied = io::read_catalog(program.at("catalog").dump());
  require(io::write_catalog(supplied) == io::write_catalog(source), "unexpected dumbbell source catalog");
  const std::string expected_sql = std::string(project ? "SELECT DISTINCT m.c,m.d" :
      "SELECT DISTINCT lab.a,lab.b,m.c,m.d,rde.e,ref.f") + std::string(original_join);
  const auto expected = frontend::admit_sql(expected_sql, source);
  const auto admitted = frontend::admit_sql(program.at("sql").get<std::string>(), supplied);
  require(expected.status == frontend::AdmissionStatus::cyclic_body && expected.program &&
          admitted.status == frontend::AdmissionStatus::cyclic_body && admitted.program,
          "dumbbell requires normalized original cyclic SQL");
  const auto normalized = [](const auto& plan) {
    return io::write_physical_source(plan.core_catalog, plan.core, plan);
  };
  require(normalized(*admitted.program) == normalized(*expected.program), "unexpected dumbbell join or output");
  const auto& supplied_routes = request.at("graph_aliases");
  const auto& filter = request.at("filter_threshold");
  require(filter.is_number_integer() && (!filter.is_number_unsigned() ||
      filter.get<std::uint64_t>() <= static_cast<std::uint64_t>(INT64_MAX)), "invalid dumbbell filter threshold");
  const auto threshold = filter.get<Vertex>();
  require(supplied_routes.size() == routes.size(), "unexpected dumbbell route count");
  for (std::size_t i = 0; i < routes.size(); ++i) {
    Json expected_route = {{"table", aliases[i]}};
    if (i != 0) {
      expected_route["min_src_exclusive"] = threshold;
      expected_route["min_dst_exclusive"] = threshold;
    }
    require(supplied_routes[i] == expected_route, "unexpected dumbbell route order or filter");
  }
  const Catalog outer{1, {table("left_triangle", project ? "c" : "abc"), table("middle", "cd"),
                          table("right_triangle", project ? "d" : "def")}};
  const std::string sql = std::string(project ? "SELECT DISTINCT middle.c,middle.d" :
      "SELECT DISTINCT left_triangle.a,left_triangle.b,middle.c,middle.d,right_triangle.e,right_triangle.f") +
      std::string(outer_join);
  return {project, threshold, compile_set(Json{
      {"program", {{"sql", sql}, {"catalog", io::write_catalog(outer)}}},
      {"native", request.at("native")},
  })};
}

template<bool Indexed>
int replay(const Json& request, const char* path, Binding binding, std::uint64_t compile_ns) {
  const bool verify = request.at("command") == "verify";
  require(verify || request.at("command") == "measure", "unknown replay command");
  const auto mode = request.at("output_mode").get<std::string>();
  const bool delta = mode == "delta";
  const bool full = mode == "full";
  require(delta || full || mode == "none", "unknown output mode");
  require(request.value("full_at_markers", full) == full, "unexpected dumbbell output schedule");
  const auto& limits = request.at("limits");
  const auto maximum_events = number(limits.at("input_events"));
  const auto maximum_rows = number(limits.at("output_rows"));
  const auto maximum_bytes = number(limits.at("capture_bytes"));
  const auto& native = request.at("native");
  const auto work = number(native.at("work_limit"));
  auto options = delta_options(native);
  options.mode = delta ? runtime::DeltaMode::delta : runtime::DeltaMode::maintenance;

  const auto initializing = Clock::now();
  auto owner = std::make_optional<runtime::DeltaRuntime>(std::move(binding.outer.program), options);
  const auto profile = owner->profile();
  const auto account = owner->plan().account();
  std::optional<TriangleState<Indexed>> left(std::in_place, account, 2), right(std::in_place, account, 0);
  const auto initialize_ns = nanos(initializing);
  // The pinned dumbbell inputs are plain CSV.
  std::ifstream input(path);
  require(bool(input), "cannot open dumbbell input");
  std::ofstream capture;
  std::filesystem::path capture_path;
  std::filesystem::path partial_capture;
  if (verify) {
    capture_path = request.at("capture_file").get<std::string>();
    partial_capture = capture_path.string() + ".partial";
    require(!std::filesystem::exists(capture_path) && !std::filesystem::exists(partial_capture),
            "capture already exists");
    capture.open(partial_capture);
    require(bool(capture), "cannot create capture");
  }

  std::uint64_t sequence{}, relation_sequence{}, outer_sequence{}, markers{}, input_lines{};
  std::uint64_t rows{}, delta_rows{}, snapshot_rows{}, captured{};
  std::uint64_t decode_ns{}, apply_ns{}, output_ns{}, release_ns{};
  auto frames = Json::array();
  auto emit = [&](const Json& record) {
    auto bytes = record.dump() + '\n';
    require(bytes.size() <= maximum_bytes - captured, "capture byte limit");
    capture << bytes;
    require(bool(capture), "capture write failed");
    captured += bytes.size();
  };
  auto count = [&] { require(rows < maximum_rows, "output row limit"); ++rows; };
  auto snapshot = [&](bool final) {
    const auto observing = Clock::now();
    const auto prefix = final ? std::string("final_") : std::string("snapshot_");
    if (verify) emit({{"kind", prefix + "begin"}, {"sequence", sequence}, {"marker", markers}});
    auto cursor = owner->results({work});
    std::uint64_t count_rows{};
    while (auto tuple = cursor.next()) {
      if (!final) { count(); ++snapshot_rows; }
      else require(count_rows < maximum_rows, "final output row limit");
      ++count_rows;
      if (verify) emit({{"kind", prefix + "row"}, {"sequence", sequence}, {"marker", markers},
                        {"values", tuple_values(tuple->values())}});
    }
    if (verify) emit({{"kind", prefix + "end"}, {"sequence", sequence}, {"marker", markers}, {"rows", count_rows}});
    if (!final) frames.push_back({{"sequence", sequence}, {"marker", markers}, {"rows", count_rows}});
    output_ns += nanos(observing);
    return count_rows;
  };

  const auto looping = Clock::now();
  std::string line;
  while (std::getline(input, line)) {
    ++input_lines;
    const auto decoding = Clock::now();
    const auto event = decode(line, {}, "graph_csv", TableId{});
    decode_ns += nanos(decoding);
    if (event.enumerate) {
      ++markers;
      if (full) snapshot(false);
      continue;
    }
    require(sequence < maximum_events, "input event limit");
    ++sequence;
    const auto source = std::get<Vertex>(event.values[0]);
    const auto destination = std::get<Vertex>(event.values[1]);
    const bool insert = event.operation == SetOperation::insert;
    const auto delta_before = delta_rows;
    if (verify && delta) emit({{"kind", "delta_begin"}, {"sequence", sequence}});
    auto submit = [&](TableId table_id, std::span<const Vertex> values) {
      std::array<storage::ScalarView, 3> cells;
      for (std::size_t i = 0; i < values.size(); ++i) cells[i] = values[i];
      const auto row = storage::RowView::borrow(std::span<const storage::ScalarView>(cells).first(values.size()));
      const auto applying = Clock::now();
      auto epoch = std::make_optional(owner->apply_view({
          ++outer_sequence, table_id, event.operation, storage::TupleValuesView::borrow(row),
      }));
      apply_ns += nanos(applying);
      const auto observing = Clock::now();
      if (delta) while (auto changed = epoch->next()) {
        count();
        ++delta_rows;
        if (verify) emit({{"kind", "delta_row"}, {"sequence", sequence}, {"relation_sequence", relation_sequence},
                          {"operation", changed->operation == SetOperation::insert ? "+" : "-"},
                          {"values", tuple_values(changed->tuple.values())}});
      }
      output_ns += nanos(observing);
      const auto releasing = Clock::now();
      epoch.reset();
      release_ns += nanos(releasing);
    };

    ++relation_sequence;
    const std::array endpoints{source, destination};
    submit(TableId{1}, endpoints);
    if (source > binding.threshold && destination > binding.threshold) {
      for (std::size_t route = 1; route < routes.size(); ++route) {
        ++relation_sequence;
        const bool on_left = routes[route].side == Side::left;
        auto& state = on_left ? *left : *right;
        auto local_start = Clock::now();
        state.update(routes[route].edge, source, destination, insert, binding.project,
            [&](std::span<const Vertex> tuple) {
              apply_ns += nanos(local_start);
              submit(TableId{on_left ? 0U : 2U}, tuple);
              local_start = Clock::now();
            });
        apply_ns += nanos(local_start);
      }
    }
    if (verify && delta) emit({{"kind", "delta_end"}, {"sequence", sequence}, {"rows", delta_rows - delta_before}});
  }
  require(!input.bad(), "dumbbell input read failed");
  const auto loop_ns = nanos(looping);
  // The original full-head process enumerates once on its terminal timer.
  const auto final_rows = verify || !binding.project ? snapshot(true) : 0;
  if (verify) {
    capture.close();
    require(bool(capture), "capture close failed");
    std::filesystem::create_hard_link(partial_capture, capture_path);
    std::filesystem::remove(partial_capture);
  }
  const auto usage = memory(account.statistics());
  const auto destroying = Clock::now();
  left.reset();
  right.reset();
  owner.reset();
  const auto teardown_ns = nanos(destroying);
  return report({{"schema_version", 1}, {"implementation", "native_serial_incremental_dumbbell"},
      {"status", "complete"}, {"case_id", request.at("case_id")}, {"output_mode", mode},
      {"physical_inputs", sequence}, {"input_lines", input_lines}, {"relation_updates", relation_sequence},
      {"normalized_source_updates", relation_sequence}, {"derived_outer_updates", outer_sequence},
      {"enumeration_markers", markers}, {"full_at_markers", full}, {"output_rows", rows},
      {"delta_rows", delta_rows}, {"snapshot_rows", snapshot_rows}, {"capture_bytes", captured},
      {"final_rows", verify ? Json(final_rows) : Json{}}, {"terminal_timer_rows", binding.project ? 0 : final_rows},
      {"snapshots", std::move(frames)},
      {"compile_ns", compile_ns}, {"initialize_ns", initialize_ns}, {"loop_wall_ns", loop_ns},
      {"decode_ns", decode_ns}, {"apply_ns", apply_ns}, {"output_ns", output_ns},
      {"epoch_release_ns", release_ns}, {"teardown_ns", teardown_ns}, {"memory_before_teardown", usage},
      {"query_class", "cyclic"}, {"outer_backend", std::string(profile.backend)},
      {"triangle_backend", Indexed ? "hash_adjacency" : "ordered_adjacency"},
      {"physical_options", io::write_physical_options(binding.outer.physical)}});
}

int run(int argc, char** argv) {
  require(argc == 3, "usage: paper_native_dumbbell REQUEST INPUT");
  const auto beginning = Clock::now();
  std::ifstream configuration(argv[1]);
  require(bool(configuration), "cannot open request");
  const auto request = io::read_json(std::string(std::istreambuf_iterator<char>(configuration), {}));
  auto binding = bind(request);
  const auto compile_ns = nanos(beginning);
  if (binding.outer.physical.indexed_storage)
    return replay<true>(request, argv[2], std::move(binding), compile_ns);
  return replay<false>(request, argv[2], std::move(binding), compile_ns);
}
}

int main(int argc, char** argv) {
  try { return run(argc, argv); }
  catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
