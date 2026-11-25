// Replays an edge stream in the original CROWN experiment format on one engine,
// so the result can be set beside the Scala/Flink implementation's
// `AccumulateTime` for the same file (see docs/handoff-performance.md).
//
//   crown_stream_bench QUERY FILE MODE [ENGINE [REPS]]
//     QUERY   l3     Q(a,b,c,d)   :- G(a,b), G(b,c), G(c,d)
//             l4     Q(a,b,c,d,e) :- G(a,b), G(b,c), G(c,d), G(d,e)
//             star   Q(a,b,c,d,e) :- G(a,b), G(a,c), G(a,d), G(a,e)
//     FILE    lines `+,src,dst`, `-,src,dst` and `*` (full-enumeration trigger)
//     MODE    maint  maintenance only; `*` is ignored
//             full   every `*` enumerates the whole result and drops it
//             delta  every update enumerates its result delta and drops it
//     ENGINE  cmp (default) compact kernel, updates passed in batches of
//             BATCH (environment, default 1024) between two `*` lines;
//             cmp1  compact kernel, one call per update;
//             ref | idx  DeltaRuntime on the reference / indexed backend
//     REPS    timed repetitions, each on a fresh engine (default 5)
//
// All aliases read the one edge table, as in the original jobs, so one edge
// update is one engine call that changes three (l3) or four relations. The file
// is parsed before the clock starts: the timed region is engine calls only,
// which is what the original's process-function timer covers.
#include "crown/planner/lower.hpp"
#include "crown/planner/oracle.hpp"
#include "crown/runtime/compact.hpp"
#include "crown/runtime/delta.hpp"
#include <algorithm>
#include <charconv>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

using namespace crown;
using namespace crown::runtime;
using Clock = std::chrono::steady_clock;

namespace {
struct Event { char kind; std::int64_t source, target; };
struct Counter final : compact::RowSink {
  std::uint64_t rows = 0, sum = 0;
  void row(const compact::Word* words) override { ++rows; if (words) sum += words[0]; }
};
std::optional<std::size_t> positive_size(std::string_view text) {
  std::size_t value = 0;
  const auto end = text.data() + text.size();
  const auto parsed = std::from_chars(text.data(), end, value);
  if (parsed.ec != std::errc{} || parsed.ptr != end || value == 0) return std::nullopt;
  return value;
}
std::vector<Event> load(const std::string& path) {
  std::ifstream in(path);
  if (!in) { std::cerr << "cannot open " << path << "\n"; std::exit(2); }
  std::vector<Event> events;
  std::string line;
  while (std::getline(in, line)) {
    if (line.empty()) continue;
    if (line[0] == '*') { events.push_back({'*', 0, 0}); continue; }
    const auto first = line.find(','), second = line.find(',', first + 1);
    if ((line[0] != '+' && line[0] != '-') || first == std::string::npos || second == std::string::npos) {
      std::cerr << "bad line: " << line << "\n"; std::exit(2);
    }
    events.push_back({line[0], std::stoll(line.substr(first + 1, second - first - 1)), std::stoll(line.substr(second + 1))});
  }
  return events;
}
}  // namespace

int main(int argc, char** argv) {
  if (argc < 4 || argc > 6) { std::cerr << "usage: crown_stream_bench QUERY(l3|l4|star) FILE MODE(maint|full|delta) [ENGINE(cmp|cmp1|ref|idx) [REPS]]\n"; return 2; }
  const std::string shape = argv[1], path = argv[2], mode = argv[3], engine = argc > 4 ? argv[4] : "cmp";
  if ((mode != "maint" && mode != "full" && mode != "delta") || (engine != "cmp" && engine != "cmp1" && engine != "ref" && engine != "idx")) {
    std::cerr << "bad mode or engine\n"; return 2;
  }
  const auto repetitions = argc > 5 ? positive_size(argv[5]) : std::optional<std::size_t>{5};
  const auto* batch_setting = engine == "cmp" ? std::getenv("BATCH") : nullptr;
  const auto batch_size = batch_setting ? positive_size(batch_setting)
                                        : std::optional<std::size_t>{engine == "cmp1" ? 1U : 1024U};
  if (!repetitions || !batch_size) { std::cerr << "REPS and BATCH must be positive integers\n"; return 2; }
  const std::size_t reps = *repetitions;
  const std::size_t batch = *batch_size;
  Table edge; edge.name = "G"; edge.columns = {Column{"src", ScalarType::int64}, Column{"dst", ScalarType::int64}};
  const Catalog catalog{1, {edge}};
  Query query;
  const auto atom = [&](const char* name, std::size_t left, std::size_t right) {
    query.atoms.push_back({name, TableId{0}, {VariableId{left}, VariableId{right}}});
  };
  std::size_t variables = 0;
  if (shape == "l3") { variables = 4; atom("G1", 0, 1); atom("G2", 1, 2); atom("G3", 2, 3); }
  else if (shape == "l4") { variables = 5; atom("G1", 0, 1); atom("G2", 1, 2); atom("G3", 2, 3); atom("G4", 3, 4); }
  else if (shape == "star") { variables = 5; atom("G1", 0, 1); atom("G2", 0, 2); atom("G3", 0, 3); atom("G4", 0, 4); }
  else { std::cerr << "bad query\n"; return 2; }
  for (std::size_t i = 0; i < variables; ++i) {
    const std::string name(1, static_cast<char>('a' + i));
    query.variables.push_back(Variable{name, ScalarType::int64});
    query.head.push_back({VariableId{i}, name});
  }
  const auto tree = planner::minimum_tree(catalog, query);
  if (!tree.tree) { std::cerr << "no join tree: " << tree.reason << "\n"; return 1; }
  PhysicalOptions physical;
  if (engine == "idx") {
    const std::size_t big = 64'000'000; const std::uint64_t work = 1'000'000'000'000ULL;
    physical.indexed_storage = storage::IndexedBackendSpec{{big, 64, big, big, big, big, big, big, big}, {work, work, work, work, work}};
  }
  const auto plan = planner::lower_tree(catalog, query, *tree.tree, physical);
  DeltaOptions options;
  options.mode = mode == "delta" ? DeltaMode::delta : DeltaMode::maintenance;
  options.work_limit = std::nullopt; options.physical.work_limit = std::nullopt; options.physical.support.work_limit = std::nullopt;
  options.physical.support.memory_limit_bytes = 60ULL << 30; options.physical.support.observation.mode = ObservationMode::off;
  options.cursor.work_limit = std::nullopt; options.spool_row_limit = 1ULL << 40; options.spool_byte_limit = 1ULL << 40;

  const auto events = load(path);
  const bool compact_engine = engine == "cmp" || engine == "cmp1";
  std::vector<Row> rows;                 // DeltaRuntime input.
  std::vector<compact::Word> words;      // Compact kernel input: two words per event.
  std::vector<compact::Update> encoded;
  words.reserve(events.size() * 2);
  std::uint64_t updates = 0, triggers = 0;
  for (const auto& event : events) {
    if (!compact_engine) rows.push_back(event.kind == '*' ? Row{} : Row{Value{event.source}, Value{event.target}});
    words.push_back(static_cast<compact::Word>(event.source));
    words.push_back(static_cast<compact::Word>(event.target));
    if (event.kind == '*') ++triggers; else ++updates;
  }
  for (std::size_t i = 0; i < events.size(); ++i)
    encoded.push_back({TableId{0}, events[i].kind == '-' ? SetOperation::erase : SetOperation::insert, words.data() + 2 * i});
  std::vector<double> seconds;
  std::uint64_t out_rows = 0, refused = 0, bytes = 0, peak = 0;
  for (std::size_t rep = 0; rep < reps; ++rep) {
    std::optional<compact::Runtime> fast;
    std::optional<DeltaRuntime> full;
    if (compact_engine) fast.emplace(plan); else full.emplace(plan, options);
    Counter counter;
    compact::RowSink* const sink = mode == "delta" ? &counter : nullptr;
    std::uint64_t sequence = 0, produced = 0, rejected = 0;
    const auto start = Clock::now();
    for (std::size_t i = 0; i < events.size();) {
      const auto& event = events[i];
      if (event.kind == '*') {
        ++i;
        if (mode != "full") continue;
        if (fast) fast->enumerate(counter);
        else { auto cursor = full->results(ResultCursorOptions{std::nullopt}); while (cursor.next()) ++produced; }
        continue;
      }
      if (!fast) {
        auto epoch = full->apply(PhysicalSetUpdate{++sequence, TableId{0}, event.kind == '+' ? SetOperation::insert : SetOperation::erase, rows[i]});
        while (epoch.next()) ++produced;
        ++i;
      } else if (batch == 1) {
        if (!fast->apply(TableId{0}, encoded[i].operation, std::span<const compact::Word>(encoded[i].row, 2), sink)) ++rejected;
        ++i;
      } else {
        std::size_t last = i;
        while (last < events.size() && last - i < batch && events[last].kind != '*') ++last;
        rejected += (last - i) - fast->apply(std::span<const compact::Update>(encoded.data() + i, last - i), sink);
        i = last;
      }
    }
    seconds.push_back(std::chrono::duration<double>(Clock::now() - start).count());
    out_rows = produced + counter.rows; refused = rejected;
    const auto memory = fast ? fast->memory_statistics() : full->accounted_memory_statistics();
    bytes = memory.current.requested_bytes; peak = memory.peak_requested_bytes;
  }
  std::sort(seconds.begin(), seconds.end());
  const double median = seconds[seconds.size() / 2];
  std::printf("%-4s %-5s %-3s edge-updates=%llu triggers=%llu rows=%llu refused=%llu | median %.4f s [%.4f-%.4f] | %.1f ns/edge-update | end %.1f MiB, peak %.1f MiB\n",
      shape.c_str(), mode.c_str(), engine.c_str(), static_cast<unsigned long long>(updates), static_cast<unsigned long long>(triggers),
      static_cast<unsigned long long>(out_rows), static_cast<unsigned long long>(refused), median, seconds.front(), seconds.back(),
      median * 1e9 / static_cast<double>(std::max<std::uint64_t>(1, updates)), static_cast<double>(bytes) / 1048576.0,
      static_cast<double>(peak) / 1048576.0);
  return 0;
}
