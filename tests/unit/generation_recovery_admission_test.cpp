#include "local_sink_fixture.hpp"
#include <map>

namespace {
using namespace crown;
using namespace crown::runtime;
using generation_test::check;
struct Fixture {
  local_sink_test::Fixture source;
  CompiledProgram program;
  std::string wal;
  std::map<std::string, std::string> saved;
  explicit Fixture(bool indexed) : source(indexed), program(CompiledProgram::standalone(source.query.test.plan)),
      wal(generation_test::path(source.query.name, 1, ".wal")) {
    for (std::size_t i = 0; i != 2; ++i) {
      source.commit(i);
      check(source.query.session->deliver_local_epoch().sequence == i + 1, "legacy delivery missed an epoch");
    }
    source.query.session.reset();
    generation_test::put(wal, session_file_test::contents(wal) + "CROWN");
    generation_test::put(source.path, session_file_test::contents(source.path) + "CROWN");
    for (const auto& path : {source.query.name, source.path, wal,
                             generation_test::path(source.query.name, 1, ".ckpt")})
      saved.emplace(path, session_file_test::contents(path));
  }
  void reset() const { for (const auto& [path, bytes] : saved) generation_test::put(path, bytes); }
  void intact() const {
    for (const auto& [path, bytes] : saved)
      check(session_file_test::contents(path) == bytes, "rejected legacy recovery changed durable files");
  }
  QuerySession::Owner restore(SessionGenerationRecoveryOptions options = generation_test::recovery_options()) {
    return QuerySession::restore_generation_with_local_sink(program, source.query.name, options, source.path, local_sink_test::options());
  }
  void verify(QuerySession& session) const {
    check(session.status().committed_sequence == 2 && session.progress().sequence == 2 &&
          session.local_sink_state().verified_sequence == 2, "legacy recovery changed committed progress");
    check(session_file_test::contents(wal).size() + 5 == saved.at(wal).size() &&
          session_file_test::contents(source.path).size() + 5 == saved.at(source.path).size(), "validated legacy tails were not repaired");
    session.start();
    session_checkpoint_test::enqueue(session, io::InputEvent{source.query.test.updates[2], io::SourcePosition{"feed", 30}});
    check(session.begin_next(), "legacy recovery lost the next input");
    local_sink_test::finish(session);
    check(session.deliver_local_epoch().sequence == 3, "legacy recovery lost the next output");
    Database database; database.tables.resize(1);
    for (std::size_t i = 0; i != 3; ++i) database.tables[0].insert(source.query.test.updates[i].values);
    check(session_checkpoint_test::rows(session) == session_checkpoint_test::oracle(source.query.test, database),
          "legacy recovery next state differs from independent oracle");
  }
};
std::size_t sweep(bool indexed) {
  Fixture fixture(indexed);
  std::size_t allocations = 0;
  std::uint64_t peak = 0;
  {
    QuerySession::Owner session;
    { s04_alloc::Scope count; session = fixture.restore(); allocations = s04_alloc::calls; }
    const auto measured = session->accounted_memory_statistics();
    check(measured->successful_allocations == allocations, "legacy recovery C++ new/account counts differ");
    peak = measured->peak_requested_bytes;
    fixture.verify(*session);
  }
  check(allocations > 0 && allocations < 10000, "legacy recovery sweep has no finite measured bound");
  for (std::size_t point = 0; point < allocations; ++point) {
    fixture.reset();
    const auto descriptors = session_file_test::descriptors();
    bool failed = false, triggered = false;
    {
      s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(point));
      try { static_cast<void>(fixture.restore()); }
      catch (const std::bad_alloc&) { failed = true; }
      triggered = s04_alloc::triggered;
    }
    check(failed && triggered && session_file_test::descriptors() == descriptors,
          "legacy recovery missed injected C++ new failure or leaked descriptors");
    fixture.intact();
    auto retry = fixture.restore(); fixture.verify(*retry);
  }
  fixture.reset();
  auto exact = generation_test::recovery_options(); exact.replay.memory_limit_bytes = peak;
  { auto session = fixture.restore(exact); check(session->accounted_memory_statistics()->peak_requested_bytes == peak,
      "legacy exact receiving cap changed peak"); fixture.verify(*session); }
  fixture.reset(); --*exact.replay.memory_limit_bytes;
  bool denied = false;
  try { static_cast<void>(fixture.restore(exact)); }
  catch (const resource::MemoryFailure& failure) { denied = failure.fault() == resource::MemoryFault::limit; }
  check(denied, "legacy one-under receiving cap was admitted"); fixture.intact();
  auto retry = fixture.restore(); fixture.verify(*retry);
  return allocations;
}
}  // namespace
int main() {
  try {
    const auto points = sweep(false) + sweep(true);
    std::cout << "Legacy recovery admission: " << points << " allocation cuts, both backends, torn WAL/sink, exact/one-under cap, next update\n";
  } catch (const std::exception& error) { std::cerr << error.what() << '\n'; return 1; }
}
