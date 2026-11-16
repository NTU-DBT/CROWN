#include "sql_aggregate_session_probe.hpp"
#include "crown/io/catalog.hpp"
#include <fstream>
#include <iostream>
#include <sys/wait.h>

namespace {
using namespace crown;
using namespace crown::sql_aggregate_session_test;
namespace ag = runtime::aggregate;
using Row = ag::Row;
using Edits = std::vector<runtime::sql_rows::SourceReplacement>;
using Json = io::Json;

// One true left anchor joins every right row, including itself. Compressed
// opposite contributions exceed bigint individually; their final sum is zero.
// Initial COUNT(*) is exactly INT64_MAX, without expanding any physical row.
constexpr std::uint64_t weight = (std::uint64_t{INT64_MAX} - 3) / 2;
enum class Group { empty, seed, mixed, erased, probe_mixed, probe_small };
enum class Command { seed, mixed, cast_reject, sum_reject, erase, probe };
enum class Action { log, commit, cast_reject, sum_reject, deliver, checkpoint, recover };
constexpr std::array actions{Action::log, Action::commit, Action::cast_reject,
    Action::sum_reject, Action::deliver, Action::checkpoint, Action::recover};
ag::SqlValue integer(std::int64_t value) { return Value{value}; }
ag::SqlValue decimal(std::string_view value) { return Value{Decimal::parse(value)}; }
bool present(Group group) { return group != Group::empty && group != Group::erased; }
std::string hex(std::string_view bytes) {
  constexpr char digits[] = "0123456789abcdef";
  std::string result;
  result.reserve(2*bytes.size());
  for (const char raw : bytes) {
    const auto byte = static_cast<unsigned char>(raw);
    result += digits[byte>>4]; result += digits[byte&15];
  }
  return result;
}
Row key(Group group) {
  assert(present(group));
  return {integer(7), group == Group::seed ? ag::SqlValue{} : ag::SqlValue{Value{std::string("next")}}};
}
Row values(Group group) {
  assert(present(group));
  const bool probe = group == Group::probe_mixed || group == Group::probe_small;
  const auto count = group == Group::probe_small ? std::int64_t{2} :
      group == Group::mixed ? INT64_MAX - 1 : INT64_MAX;
  const auto nonnull = group == Group::probe_small ? std::int64_t{2} :
      group == Group::probe_mixed ? INT64_MAX - 1 : INT64_MAX - 2;
  return {key(group)[1], integer(count), integer(nonnull), integer(probe ? 1 : 0),
      decimal(probe ? "1" : "0"), decimal(group == Group::probe_small ? "0.5" : "0")};
}
ag::Tuple tuple(const resource::MemoryAccount& account, const Row& row) {
  std::vector<Cell> cells;
  for (const auto& value : row) cells.push_back(value ? Cell{storage::borrow_scalar(*value)} : Cell{});
  return ag::Tuple::copy_of(account, cells);
}
// Five explicit before/final changes form the output oracle. The very small
// probe after the large state has AVG=1/(INT64_MAX-1), which rounds to zero at18.
std::vector<ag::GroupChange> changes(const resource::MemoryAccount& account, Group before, Group after) {
  std::vector<ag::GroupChange> result;
  if (present(before) && (!present(after) || key(before) != key(after)))
    result.push_back({tuple(account, key(before)), tuple(account, values(before)), {}});
  if (present(after)) {
    std::optional<ag::Tuple> old;
    if (present(before) && key(before) == key(after)) old = tuple(account, values(before));
    result.push_back({tuple(account, key(after)), std::move(old), tuple(account, values(after))});
  }
  return result;
}
Catalog catalog() {
  return {1, {{"r", {{"id", ScalarType::int64, true}, {"g", ScalarType::string, true},
      {"x", ScalarType::int64, true}, {"flag", ScalarType::boolean, true}}},
      {"unused", {{"z", ScalarType::string, true}}}}};
}
struct Scenario : Fixture {
  // These caller-owned physical buffers survive every synchronous log call.
  const std::array<Cell, 4> anchor_null{number(7), Cell{}, number(0), storage::ScalarView{true}};
  const std::array<Cell, 4> anchor_next{number(7), text("next"), number(0), storage::ScalarView{true}};
  const std::array<Cell, 4> positive{number(7), Cell{}, number(INT32_MAX), storage::ScalarView{false}};
  const std::array<Cell, 4> negative{number(7), text("negative"), number(-INT32_MAX), storage::ScalarView{false}};
  const std::array<Cell, 4> null{number(7), text("null"), Cell{}, storage::ScalarView{false}};
  const std::array<Cell, 4> filtered{number(9), text("filtered"), number(INT64_MAX), Cell{}};
  const std::array<Cell, 4> bad{number(7), text("bad"), number(std::int64_t{INT32_MAX}+1), storage::ScalarView{false}};
  const std::array<Cell, 4> probe{number(7), text("probe"), number(1), storage::ScalarView{false}};
  const std::array<Cell, 1> unused{text("retained original source")};
  resource::MemoryAccount oracle = resource::MemoryAccount::create(4ULL*1024*1024);
  std::string expected_sink;

  explicit Scenario(bool indexed) : Fixture(indexed, catalog(),
      "SELECT a.g,COUNT(*),COUNT(b.x::integer),SUM(b.x::integer),SUM(b.x),AVG(b.x::integer) "
      "FROM r a JOIN r b ON a.id=b.id WHERE a.flag GROUP BY a.id,a.g") {}
  Edits edits(Command command, bool erased = false) const {
    const auto r = [](std::span<const Cell> row, std::uint64_t before, std::uint64_t after) {
      return runtime::sql_rows::SourceReplacement{TableId{0}, row, before, after};
    };
    const auto u = [&](std::uint64_t before, std::uint64_t after) {
      return runtime::sql_rows::SourceReplacement{TableId{1}, unused, before, after};
    };
    switch (command) {
      case Command::seed: return {r(anchor_null,0,1), r(positive,0,weight),
          r(negative,0,weight), r(null,0,2)};
      case Command::mixed: return {r(anchor_next,0,1), r(anchor_null,1,0), r(null,2,1),
          r(positive,weight,weight-1), r(positive,weight-1,weight), r(filtered,0,2), u(0,3)};
      case Command::cast_reject: return {u(3,5), r(bad,0,1)};
      case Command::sum_reject: return {u(3,7), r(negative,weight,0)};
      case Command::erase: return {r(anchor_next,1,0), r(positive,weight,0),
          r(negative,weight,0), r(null,1,0)};
      case Command::probe: return {r(probe,0,1), r(anchor_next,erased?0U:1U,1)};
    }
    std::abort();
  }
  void log_command(ar::Session& owner, Command command, bool erased = false) const {
    const auto next = owner.state().disposed+1;
    const auto rows = edits(command, erased);
    owner.log({next, rows, ar::SourcePosition{"feed", 10*next}, ar::ReaderPosition{100*next,next}});
  }
  void check(const ar::Session& owner, Group group) const {
    const auto snapshot = owner.snapshot();
    assert(snapshot.groups.size() == (present(group) ? 1U : 0U));
    if (present(group)) {
      assert(snapshot.groups[0].key.export_values() == key(group));
      assert(snapshot.groups[0].values.export_values() == values(group));
    }
    const bool heavy = group == Group::seed || group == Group::mixed || group == Group::probe_mixed;
    const bool changed = group != Group::empty && group != Group::seed;
    assert(owner.source_weight(TableId{0}, anchor_null) == (group == Group::seed ? 1U : 0U));
    assert(owner.source_weight(TableId{0}, anchor_next) == (present(group) && group != Group::seed ? 1U : 0U));
    assert(owner.source_weight(TableId{0}, positive) == (heavy ? weight : 0));
    assert(owner.source_weight(TableId{0}, negative) == (heavy ? weight : 0));
    assert(owner.source_weight(TableId{0}, null) == (group == Group::seed ? 2U : heavy ? 1U : 0U));
    assert(owner.source_weight(TableId{0}, filtered) == (changed ? 2U : 0U));
    assert(owner.source_weight(TableId{0}, bad) == 0);
    assert(owner.source_weight(TableId{0}, probe) == (group == Group::probe_mixed || group == Group::probe_small ? 1U : 0U));
    assert(owner.source_weight(TableId{1}, unused) == (changed ? 3U : 0U));
  }
  std::string expected_epoch(const ar::Session& owner, Group before, Group after) const {
    const auto state = owner.state();
    std::optional<ar::Hash> input;
    for (const auto& bytes : frames(contents(generation_file(*this, state.generation)))) {
      const auto frame = ar::inspect(program, bytes);
      if (frame.kind == ar::Kind::input &&
          std::get<ar::InputInfo>(frame.payload).command_sequence == state.disposed) input = frame.body_sha256;
    }
    assert(input);
    const auto output = changes(oracle, before, after);
    const auto frame = ar::encode(oracle, program, state.committed,
        ar::GroupEpochView{state.generation,state.disposed,state.committed,*input,true,true,output});
    return std::string(frame.bytes());
  }
  // Baseline preparation uses the same real API as later recovery. Expected
  // group payloads above are independently specified, not copied from snapshots.
  void apply(ar::Session& owner, Command command, Group before, Group after, bool deliver = true) {
    log_command(owner, command);
    assert(!owner.decide().rejected);
    const auto epoch = expected_epoch(owner, before, after);
    assert(owner.output() == epoch); check(owner, after);
    expected_sink += epoch;
    if (deliver) { assert(owner.deliver()); assert(contents(sink) == expected_sink); }
  }
  void reject(ar::Session& owner, Command command) {
    log_command(owner, command);
    assert(owner.decide().rejected == ar::RejectReason::aggregate_overflow);
    check(owner, Group::mixed); assert(!owner.output() && contents(sink) == expected_sink);
  }
};

using Namespace = std::vector<std::pair<std::string,std::string>>;
Namespace capture(const Scenario& f) {
  Namespace result;
  for (const auto& file : std::filesystem::directory_iterator(f.directory.name))
    result.emplace_back(file.path().string(), contents(file.path().string()));
  return result;
}
void restore(Scenario& f, const Namespace& files, Action action, std::optional<ar::Session>& owner) {
  owner.reset();
  for (const auto& file : std::filesystem::directory_iterator(f.directory.name)) std::filesystem::remove_all(file.path());
  for (const auto& [path, bytes] : files) put(path, bytes);
  if (action != Action::recover) owner.emplace(f.recover());
}
// The selected checkpoint at C1 already contains compressed weights at the
// bigint count boundary. Later cases retain I>C after genuine semantic Rejects.
void prepare(Scenario& f, Action action, std::optional<ar::Session>& owner) {
  owner.emplace(f.create());
  const auto header = ar::encode(f.oracle, f.program, 0,
      ar::SinkHeader{{f.identity.query_id,owner->descriptor().sha256()},f.identity.sink_id,0});
  f.expected_sink = header.bytes(); assert(contents(f.sink) == f.expected_sink);
  f.apply(*owner, Command::seed, Group::empty, Group::seed);
  assert(owner->checkpoint().generation == 2);
  if (action == Action::log) return;
  f.log_command(*owner, Command::mixed);
  if (action == Action::commit) return;
  assert(!owner->decide().rejected);
  const auto mixed = f.expected_epoch(*owner, Group::seed, Group::mixed);
  assert(owner->output() == mixed); f.expected_sink += mixed; f.check(*owner, Group::mixed);
  if (action == Action::deliver) return;
  assert(owner->deliver()); assert(contents(f.sink) == f.expected_sink);
  if (action == Action::cast_reject) { f.log_command(*owner, Command::cast_reject); return; }
  f.reject(*owner, Command::cast_reject);
  if (action == Action::sum_reject) { f.log_command(*owner, Command::sum_reject); return; }
  f.reject(*owner, Command::sum_reject);
  if (action == Action::checkpoint) return;
  assert(owner->checkpoint().generation == 3);
  f.apply(*owner, Command::erase, Group::mixed, Group::erased, false);
  owner.reset();
  const auto wal = generation_file(f, 3);
  put(wal, contents(wal)+"C"); put(f.sink, contents(f.sink)+"C");
}
void perform(Scenario& f, Action action, std::optional<ar::Session>& owner) {
  switch (action) {
    case Action::log: f.log_command(*owner, Command::mixed); break;
    case Action::commit: assert(!owner->decide().rejected); break;
    case Action::cast_reject:
    case Action::sum_reject: assert(owner->decide().rejected == ar::RejectReason::aggregate_overflow); break;
    case Action::deliver: assert(owner->deliver()); break;
    case Action::checkpoint: assert(owner->checkpoint().generation == 3); break;
    case Action::recover: owner.emplace(f.recover()); break;
  }
}
// Resolve only the same surviving Input, compare complete state/sink, and then
// make a fresh small update to expose stale ancestor or sufficient-statistic state.
Json surviving(Scenario& f, Action action, std::optional<ar::Session>& owner, bool reopen = true) {
  if (reopen || !owner) { owner.reset(); owner.emplace(f.recover()); }
  const auto command = action == Action::recover ? 5U : action == Action::cast_reject ? 3U :
      action == Action::sum_reject || action == Action::checkpoint ? 4U : 2U;
  const auto committed = action == Action::recover ? 3U : 2U;
  if (owner->state().logged < command) {
    assert(action == Action::log && owner->state().logged == 1);
    f.log_command(*owner, Command::mixed);
  }
  if (owner->pending_input()) {
    const auto decision = owner->decide();
    if (action == Action::cast_reject || action == Action::sum_reject)
      assert(decision.rejected == ar::RejectReason::aggregate_overflow);
    else assert(!decision.rejected);
  }
  std::string expected = f.expected_sink;
  if (action == Action::log || action == Action::commit)
    expected += f.expected_epoch(*owner, Group::seed, Group::mixed);
  if (owner->output()) { assert(*owner->output() == frames(expected).back()); assert(owner->deliver()); }
  state(*owner, command, command, committed, committed);
  assert(contents(f.sink) == expected);
  const auto group = action == Action::recover ? Group::erased : Group::mixed;
  f.check(*owner, group);
  assert(owner->progress().source_positions.at("feed") == 10*command);
  assert(owner->reader_position() == (ar::ReaderPosition{100*command,command}));
  if (action == Action::checkpoint) assert(owner->selected_root().generation == 2 || owner->selected_root().generation == 3);
  // Save the actual tape before the follow-up; Python independently decodes it.
  Json observation{{"command",command},{"committed",committed},{"sink_hex",hex(expected)}};
  f.log_command(*owner, Command::probe, group == Group::erased);
  assert(!owner->decide().rejected);
  const auto after = group == Group::erased ? Group::probe_small : Group::probe_mixed;
  const auto epoch = f.expected_epoch(*owner, group, after);
  assert(owner->output() == epoch && owner->deliver()); expected += epoch;
  state(*owner, command+1, command+1, committed+1, committed+1);
  f.check(*owner, after); assert(contents(f.sink) == expected);
  owner.reset(); owner.emplace(f.recover());
  state(*owner, command+1, command+1, committed+1, committed+1); f.check(*owner, after);
  assert(contents(f.sink) == expected && !owner->output());
  assert(owner->progress().source_positions.at("feed") == 10*(command+1));
  assert(owner->reader_position() == (ar::ReaderPosition{100*(command+1),command+1}));
  observation["probe_sink_hex"] = hex(expected);
  owner.reset();
  return observation;
}

Json matrix(bool indexed) {
  Json report = Json::array();
  for (const auto action : actions) {
    Scenario f(indexed); std::optional<ar::Session> owner;
    prepare(f, action, owner); owner.reset();
    const auto baseline = f.account.statistics().current;
    const auto descriptors = sql_aggregate_file_test::descriptors();
    const auto image = capture(f); restore(f, image, action, owner);
    Hook trace;
    { Installed installed(trace); perform(f, action, owner); }
    // The no-fault control probes the live owner too, before its first reopen.
    // Fault/process cases must first recover uncertain surviving files.
    auto evidence = surviving(f, action, owner, false);
    std::size_t faults = 0, cuts = 0;
    for (std::size_t i = 0; i < trace.size; ++i) {
      const auto event = trace.events[i]; if (event.after && event.result < 0) continue;
      restore(f, image, action, owner); Hook hook; hook.fail = event.point; hook.after = event.after;
      bool failed = false;
      { Installed installed(hook);
        try { perform(f, action, owner); }
        catch (const ar::FileFailure&) { failed = true; }
        catch (const recovery::GenerationFailure&) { failed = true; }
      }
      assert(failed);
      if (owner && action != Action::checkpoint && action != Action::recover) {
        assert(owner->requires_reopen());
        refused([&] { static_cast<void>(owner->snapshot()); });
      }
      static_cast<void>(surviving(f, action, owner));
      assert(f.account.statistics().current == baseline);
      assert(sql_aggregate_file_test::descriptors() == descriptors); ++faults;
    }
    for (std::size_t i = 0; i < trace.size; ++i) {
      const auto event = trace.events[i]; if (!durability(event)) continue;
      restore(f, image, Action::recover, owner);
      const auto child = ::fork(); assert(child >= 0);
      if (child == 0) {
        if (action != Action::recover) owner.emplace(f.recover());
        Hook hook; hook.crash = event.point; hook.after = event.after;
        Installed installed(hook); perform(f, action, owner); ::_exit(1);
      }
      int status = 0;
      assert(::waitpid(child, &status, 0) == child && WIFEXITED(status) && WEXITSTATUS(status) == 77);
      static_cast<void>(surviving(f, action, owner));
      assert(f.account.statistics().current == baseline);
      assert(sql_aggregate_file_test::descriptors() == descriptors); ++cuts;
    }
    assert(faults > 0 && cuts > 0);
    evidence["indexed"] = indexed; evidence["action"] = static_cast<int>(action);
    evidence["syscall_EIO_cuts"] = faults; evidence["process_cuts"] = cuts;
    std::cout << "transaction backend=" << indexed << " action=" << static_cast<int>(action)
              << " EIO=" << faults << " process=" << cuts << '\n' << std::flush;
    report.push_back(std::move(evidence));
  }
  return report;
}
} // namespace

int main(int argc, char** argv) {
  assert(argc == 2);
  Json report = Json::array();
  for (const bool indexed : {false,true}) for (auto& item : matrix(indexed)) report.push_back(std::move(item));
  std::ofstream out(argv[1]); out << report.dump() << '\n'; out.flush(); assert(out.good());
  std::cout << "mixed nullable self-join: exact count boundary, signed sums, complete source, W/I/C/D, probe and every observed persistence cut passed\n";
}
