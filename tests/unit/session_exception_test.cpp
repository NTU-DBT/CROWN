#include "crown/api/error.hpp"
#include "crown/io/ingest.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/physical.hpp"
#include "crown/runtime/session.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <new>
#include <optional>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

// This executable replaces ordinary throwing scalar and array global new so
// those requests can fail while session, reader, and pending-epoch destructors
// unwind. No dedicated aligned or nothrow replacements are defined; indirect
// library delegation is not asserted as coverage. Direct malloc/realloc, system
// calls, and MemoryAccount admission denials are not injected by this seam.
namespace {
thread_local std::ptrdiff_t fail_after = -1;
thread_local std::size_t allocation_count = 0;

[[gnu::noinline]] void* malloc_new(std::size_t bytes) {
  ++allocation_count;
  if (fail_after >= 0) {
    if (fail_after == 0) throw std::bad_alloc{};
    --fail_after;
  }
  if (auto* result = std::malloc(bytes == 0 ? 1 : bytes)) return result;
  throw std::bad_alloc{};
}

struct FaultScope {
  explicit FaultScope(std::ptrdiff_t point = -1) noexcept { fail_after = point; }
  ~FaultScope() { fail_after = -1; }
  FaultScope(const FaultScope&) = delete;
  FaultScope& operator=(const FaultScope&) = delete;
  void forbid_allocations() noexcept { fail_after = 0; }
};
}  // namespace

void* operator new(std::size_t bytes) { return malloc_new(bytes); }
void* operator new[](std::size_t bytes) { return malloc_new(bytes); }
void operator delete(void* pointer) noexcept { std::free(pointer); }
void operator delete[](void* pointer) noexcept { std::free(pointer); }
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }

namespace {
using namespace crown;
using namespace crown::runtime;

static_assert(std::is_nothrow_destructible_v<QuerySession>);

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

template <class Action>
void expect_error(Action&& action, std::string_view code) {
  try {
    std::forward<Action>(action)();
  } catch (const Error& failure) {
    check(failure.code() == code,
          "expected " + std::string(code) + ", got " + failure.code());
    return;
  }
  throw std::runtime_error("expected error code " + std::string(code));
}

template <class Action>
auto run_phase(std::string_view label, Action&& action) -> decltype(action()) {
  try {
    return std::forward<Action>(action)();
  } catch (const std::exception& failure) {
    throw std::runtime_error(std::string(label) + ": " + failure.what());
  }
}

Value n(std::int64_t value) { return value; }

PhysicalPlan make_plan() {
  const Catalog catalog{41, {{"R", {{"x", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}},
                    {{"r", TableId{0}, {VariableId{0}}}},
                    {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"root", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan make_alias_plan() {
  const Catalog catalog{42, {{"E", {{"x", ScalarType::int64},
                                      {"z", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"z", ScalarType::int64}},
                    {{"forward", TableId{0}, {VariableId{0}, VariableId{1}}},
                     {"reverse", TableId{0}, {VariableId{1}, VariableId{0}}}},
                    {{VariableId{0}, "x"}, {VariableId{1}, "z"}}, false};
  const FreeConnexTree tree{NodeId{0}, {
      {"intersection", NodeKind::generalized, {VariableId{0}, VariableId{1}},
       {NodeId{1}, NodeId{2}}, {}, {}},
      {"forward", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}},
      {"reverse", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

io::InputEvent event(std::uint64_t sequence, SetOperation operation,
                     std::int64_t value, std::string source,
                     std::uint64_t offset) {
  return {{sequence, TableId{0}, operation, {n(value)}},
          io::SourcePosition{std::move(source), offset}};
}

std::string encode(const PhysicalPlan& plan, const io::InputEvent& input) {
  return io::write_input_json(input, plan.catalog()) + "\n";
}

std::string stream_bytes(const PhysicalPlan& plan) {
  return encode(plan, event(1, SetOperation::insert, 7, "source-A-long", 10)) +
         encode(plan, event(2, SetOperation::insert, 8, "source-A-long", 20)) +
         encode(plan, event(3, SetOperation::erase, 7, "source-B-long", 50));
}

class OwnedStream final : public std::istringstream {
 public:
  OwnedStream(std::string bytes, bool* destroyed)
      : std::istringstream(std::move(bytes)), destroyed_(destroyed) {
    if (destroyed_) *destroyed_ = false;
  }
  ~OwnedStream() override {
    if (destroyed_) *destroyed_ = true;
  }

 private:
  bool* destroyed_;
};

QuerySession::Owner make_session(
    PhysicalPlan plan, std::string bytes, SessionOptions options = {},
    bool* stream_destroyed = nullptr) {
  std::unique_ptr<std::istream> input =
      std::make_unique<OwnedStream>(std::move(bytes), stream_destroyed);
  return QuerySession::create(std::move(plan), std::move(input),
                              std::move(options));
}

struct OutputImage {
  std::uint64_t ordinal;
  SetOperation operation;
  Row values;
  bool operator==(const OutputImage&) const = default;
};

struct SnapshotImage {
  std::uint64_t sequence = 0;
  io::InputProgress progress;
  std::vector<Row> rows;
  bool operator==(const SnapshotImage&) const = default;
};

SnapshotImage image(const SessionSnapshot& snapshot) {
  SnapshotImage result;
  result.sequence = snapshot.sequence;
  result.progress = snapshot.progress;
  result.rows.reserve(snapshot.rows.size());
  for (const auto& tuple : snapshot.rows) result.rows.push_back(crown::storage::export_row(tuple.values()));
  return result;
}

SnapshotImage image(const QuerySession& session) {
  return image(session.snapshot());
}

std::vector<OutputImage> take_all_output(QuerySession& session) {
  std::vector<OutputImage> result;
  while (auto output = session.next_output())
    result.push_back({output->ordinal, output->operation,
                      crown::storage::export_row(output->tuple.values())});
  return result;
}

void drive_to_prepared(QuerySession& session) {
  for (;;) {
    const auto result = session.step();
    if (result == DeltaStep::prepared) return;
  }
}

void accept_current(QuerySession& session) {
  drive_to_prepared(session);
  session.commit();
}

struct CleanRun {
  SnapshotImage final_snapshot;
  std::vector<OutputImage> outputs;
};

CleanRun run_clean(PhysicalPlan plan, std::string bytes) {
  auto session = make_session(std::move(plan), std::move(bytes));
  session->start();
  CleanRun result;
  while (session->begin_next()) {
    accept_current(*session);
    auto outputs = take_all_output(*session);
    result.outputs.insert(result.outputs.end(), outputs.begin(), outputs.end());
  }
  check(session->status().end_of_input && !session->begin_next() &&
            !session->begin_next(),
        "clean EOF was not validated idempotently");
  result.final_snapshot = image(*session);
  return result;
}

io::InputProgress first_progress() {
  io::InputProgress result;
  result.sequence = 1;
  result.source_positions.emplace("source-A-long", 10);
  return result;
}

io::InputProgress second_progress() {
  auto result = first_progress();
  result.sequence = 2;
  result.source_positions.at("source-A-long") = 20;
  return result;
}

io::InputProgress full_progress() {
  auto result = second_progress();
  result.sequence = 3;
  result.source_positions.emplace("source-B-long", 50);
  return result;
}

SnapshotImage first_snapshot() {
  return {1, first_progress(), {{n(7)}}};
}

SnapshotImage second_snapshot() {
  return {2, second_progress(), {{n(7)}, {n(8)}}};
}

SnapshotImage final_snapshot() {
  return {3, full_progress(), {{n(8)}}};
}

void setup_first_commit(QuerySession& session) {
  session.start();
  check(session.begin_next(), "session did not admit its first input");
  accept_current(session);
  const auto output = take_all_output(session);
  check(output == std::vector<OutputImage>{{1, SetOperation::insert, {n(7)}}},
        "first seed input did not publish its exact unary result");
  check(image(session) == first_snapshot(),
        "first seed input did not publish the expected committed snapshot");
}

void reader_close_moves_only_accepted_progress_without_allocation() {
  const auto plan = make_plan();
  const auto bytes = encode(plan,
      event(1, SetOperation::insert, 7, "new-source-long", 10));
  io::InputProgress initial;
  initial.source_positions.emplace("old-source-long", 3);
  bool stream_destroyed = false;
  {
    OwnedStream stream(bytes, &stream_destroyed);
    io::EventReader reader(stream, plan.catalog(), {}, initial);
    const auto* cached = reader.peek();
    check(cached && cached->update.sequence == 1 &&
              cached->source_position &&
              cached->source_position->source == "new-source-long" &&
              reader.progress() == initial,
          "close fixture did not prepare a cached, unacknowledged source event");

    io::AccountedInputProgress closed;
    bool repeated_close_empty = false;
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      closed = reader.close();
      reader.acknowledge();
      const auto repeated = reader.close();
      repeated_close_empty = repeated.sequence == 0 &&
                             repeated.source_positions.empty();
    }
    check(closed == initial &&
              !closed.source_positions.contains("new-source-long") &&
              repeated_close_empty && !reader.failed() && !stream_destroyed,
          "close acknowledged the cached row, requested intercepted ordinary new, or destroyed its borrowed stream");
    expect_error([&] { static_cast<void>(reader.peek()); },
                 "invalid_input_reader");
    expect_error([&] { static_cast<void>(reader.progress()); },
                 "invalid_input_reader");
    expect_error([&] { static_cast<void>(reader.catalog()); },
                 "invalid_input_reader");
    expect_error([&] { static_cast<void>(reader.catalog_sha256()); },
                 "invalid_input_reader");
    expect_error([&] { static_cast<void>(reader.bytes_read()); },
                 "invalid_input_reader");
    expect_error([&] { static_cast<void>(reader.records_read()); },
                 "invalid_input_reader");
  }
  check(stream_destroyed,
        "borrowed input stream was not kept alive through reader destruction");
}

void retry_second_input(QuerySession& session, const CleanRun& clean) {
  check(session.begin_next(), "cached second input was lost after engine OOM");
  accept_current(session);
  const auto output = take_all_output(session);
  check(output == std::vector<OutputImage>{clean.outputs.at(1)},
        "same cached event retry differed from the clean result");
  check(image(session) == second_snapshot(),
        "same cached event retry changed the committed result or accepted progress");
}

std::size_t sweep_create_failures(const std::string& bytes) {
  constexpr std::ptrdiff_t max_points = 8192;
  std::size_t failures = 0;
  for (std::ptrdiff_t point = 0; point < max_points; ++point) {
    bool destroyed = false;
    bool failed = false;
    QuerySession::Owner session;
    auto plan = make_plan();
    auto input = std::unique_ptr<std::istream>(
        std::make_unique<OwnedStream>(bytes, &destroyed));
    {
      FaultScope fault(point);
      try {
        session = QuerySession::create(std::move(plan), std::move(input));
      } catch (const std::bad_alloc&) {
        failed = true;
        fail_after = 0;
      }
    }
    if (failed) {
      ++failures;
      check(destroyed,
            "failed session construction did not destroy its transferred input stream");
      continue;
    }

    check(failures > 0,
          "session construction sweep observed no ordinary-new failures");
    const auto status = session->status();
    check(status.state == SessionState::created &&
              status.phase == SessionPhase::ready &&
              status.committed_sequence == 0 && !status.input_failed &&
              !status.end_of_input && !status.pending_sequence &&
              status.pending_work == 0 && status.output_remaining == 0,
          "successful construction did not start from the empty session state");
    check(session->progress() == io::InputProgress{} &&
              image(*session) == SnapshotImage{0, {}, {}},
          "successful construction did not start with empty progress and results");
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      session.reset();
    }
    check(destroyed,
          "session destruction did not release its exclusively owned input stream");
    return failures;
  }
  throw std::runtime_error("session construction sweep exceeded 8192 fault points");
}

std::size_t sweep_begin_next_failures(const std::string& bytes,
                                      const CleanRun& clean) {
  constexpr std::ptrdiff_t max_points = 8192;
  std::size_t failures = 0;
  std::size_t parser_failures = 0;
  std::size_t engine_begin_failures = 0;
  for (std::ptrdiff_t point = 0; point < max_points; ++point) {
    auto session = make_session(make_plan(), bytes);
    setup_first_commit(*session);
    bool failed = false;
    {
      FaultScope fault(point);
      try {
        static_cast<void>(session->begin_next());
      } catch (const std::bad_alloc&) {
        failed = true;
        fail_after = 0;
      }
    }
    if (failed) {
      ++failures;
      const auto status = session->status();
      check(status.committed_sequence == 1 &&
                !status.pending_sequence && status.output_remaining == 0 &&
                session->progress() == first_progress() &&
                image(*session) == first_snapshot(),
            "begin_next OOM changed accepted progress or the prior commit");
      if (status.input_failed) {
        ++parser_failures;
        expect_error([&] { static_cast<void>(session->begin_next()); },
                     "input_failed");
      } else {
        ++engine_begin_failures;
        retry_second_input(*session, clean);
      }
      continue;
    }

    check(failures > 0,
          "begin_next sweep observed no ordinary-new failures");
    check(session->status().pending_sequence == 2 &&
              session->progress() == first_progress() &&
              !session->status().input_failed,
          "successful begin_next acknowledged input before engine commit");
    accept_current(*session);
    check(take_all_output(*session) ==
              std::vector<OutputImage>{clean.outputs.at(1)} &&
              image(*session) == second_snapshot(),
          "successful begin_next differed from the clean event result");
    break;
  }
  check(parser_failures > 0,
        "begin_next sweep missed an ordinary-new failure inside the sticky parser");
  check(engine_begin_failures > 0,
        "begin_next sweep missed an ordinary-new failure in engine begin after parsing");
  std::cout << "session begin_next parser ordinary-new failures=" << parser_failures
            << ", engine-begin ordinary-new failures=" << engine_begin_failures << '\n';
  return failures;
}

std::size_t sweep_retaining_step_failures(const std::string& bytes,
                                          const CleanRun& clean) {
  constexpr std::ptrdiff_t max_points = 16384;
  std::size_t failures = 0;
  for (std::ptrdiff_t point = 0; point < max_points; ++point) {
    auto session = make_session(make_plan(), bytes);
    setup_first_commit(*session);
    check(session->begin_next(), "step sweep did not begin its second input");
    expect_error([&] { static_cast<void>(session->snapshot()); },
                 "session_pending_epoch");
    bool failed = false;
    {
      FaultScope fault(point);
      try {
        drive_to_prepared(*session);
      } catch (const std::bad_alloc&) {
        failed = true;
        fail_after = 0;
      }
    }
    if (failed) {
      ++failures;
      const auto status = session->status();
      check(status.state == SessionState::running &&
                status.phase == SessionPhase::ready &&
                status.committed_sequence == 1 && !status.pending_sequence &&
                !status.input_failed && session->progress() == first_progress() &&
                image(*session) == first_snapshot(),
            "retaining step OOM left private work or changed the old committed prefix");
      retry_second_input(*session, clean);
      continue;
    }

    check(failures > 0,
          "retaining preparation sweep observed no ordinary-new failures");
    check(session->status().phase == SessionPhase::prepared &&
              session->status().pending_sequence == 2 &&
              session->status().committed_sequence == 1 &&
              session->progress() == first_progress(),
          "retaining preparation did not preserve the private commit boundary");
    session->commit();
    check(take_all_output(*session) ==
              std::vector<OutputImage>{clean.outputs.at(1)} &&
              image(*session) == second_snapshot(),
          "successful retaining preparation differed from a clean retry");
    std::cout << "session retaining step/preparation ordinary-new failures="
              << failures << '\n';
    return failures;
  }
  throw std::runtime_error("session retaining step sweep exceeded 16384 fault points");
}

std::size_t sweep_snapshot_failures(const std::string& bytes,
                                    const CleanRun& clean) {
  constexpr std::ptrdiff_t max_points = 8192;
  std::size_t failures = 0;
  for (std::ptrdiff_t point = 0; point < max_points; ++point) {
    auto session = make_session(make_plan(), bytes);
    setup_first_commit(*session);
    check(session->begin_next(), "snapshot sweep did not begin its second input");
    accept_current(*session);
    check(take_all_output(*session) ==
              std::vector<OutputImage>{clean.outputs.at(1)},
          "snapshot sweep could not release the second committed output");
    check(session->begin_next(), "snapshot sweep did not begin its third input");
    accept_current(*session);
    // Keep one output unread so the snapshot path is exercised while a
    // committed output epoch still owns its lease.
    bool failed = false;
    std::optional<SessionSnapshot> copied;
    {
      FaultScope fault(point);
      try {
        copied.emplace(session->snapshot());
      } catch (const std::bad_alloc&) {
        failed = true;
        fail_after = 0;
      }
    }
    if (failed) {
      ++failures;
      check(session->status().committed_sequence == 3 &&
                session->status().output_remaining == 1 &&
                session->progress() == full_progress() &&
                image(*session) == final_snapshot(),
            "snapshot OOM changed committed rows, copied progress, or unread output");
      continue;
    }

    check(failures > 0,
          "snapshot copy/cursor sweep observed no ordinary-new failures");
    check(copied && image(*copied) == final_snapshot() &&
              session->status().output_remaining == 1,
          "snapshot during committed unread output was incomplete or consumed output");
    expect_error([&] { static_cast<void>(session->begin_next()); },
                 "session_output_pending");
    SnapshotLimits too_small;
    too_small.rows = 0;
    expect_error([&] { static_cast<void>(session->snapshot(too_small)); },
                 "resource_limit");
    check(image(*session) == final_snapshot() &&
              session->status().output_remaining == 1,
          "snapshot row-limit failure changed committed state or output");
    const auto tail = take_all_output(*session);
    check(tail == std::vector<OutputImage>{clean.outputs.at(2)},
          "snapshot failure changed the original pending output row");
    std::cout << "session snapshot ordinary-new failures=" << failures << '\n';
    return failures;
  }
  throw std::runtime_error("session snapshot sweep exceeded 8192 fault points");
}

void commit_output_and_cleanup_are_allocation_free(const std::string& first_bytes,
                                                   const std::string& second_bytes) {
  {
    auto session = make_session(make_plan(), first_bytes);
    session->start();
    check(session->begin_next(), "new-source guarded fixture did not begin");
    drive_to_prepared(*session);
    std::optional<SignedResult> first;
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      session->commit();
      first = session->next_output();
      session->stop();
    }
    check(first && first->ordinal == 1 &&
              first->operation == SetOperation::insert &&
              first->tuple.values() == Row{n(7)} &&
              session->status().state == SessionState::stopped &&
              session->progress() == first_progress() &&
              image(*session) == first_snapshot(),
          "new-source prepared commit/output/stop requested intercepted ordinary new or lost committed state");
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      session->drop();
      session.reset();
    }
    check(first->tuple.values() == Row{n(7)},
          "returned output did not own its values past session drop");
  }

  {
    auto session = make_session(make_plan(), second_bytes);
    setup_first_commit(*session);
    check(session->begin_next(), "existing-source guarded fixture did not begin");
    drive_to_prepared(*session);
    std::optional<SignedResult> second;
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      session->commit();
      second = session->next_output();
    }
    check(second && second->operation == SetOperation::insert &&
              second->tuple.values() == Row{n(8)} &&
              session->progress() == second_progress() &&
              image(*session) == second_snapshot(),
          "existing-source commit/output requested intercepted ordinary new or failed to commit progress");
    // Reading the last row must destroy the output epoch and release the
    // engine lease, so the next input can begin immediately.
    check(session->begin_next(),
          "exhausting session output did not release the engine output epoch");
    drive_to_prepared(*session);
    session->commit();
    auto third = session->next_output();
    check(third && third->operation == SetOperation::erase &&
              third->tuple.values() == Row{n(7)},
          "third input did not publish the expected erase output");
    check(!session->next_output() &&
              session->progress() == full_progress() &&
              image(*session) == final_snapshot(),
          "empty output read did not release the final session output epoch");
    session->drop();
  }

  {
    // A duplicate insertion has no signed output. Its committed empty output
    // epoch must still be destroyed by next_output() so admission can resume.
    const auto duplicate = encode(make_plan(),
        event(2, SetOperation::insert, 7, "source-A-long", 20));
    auto session = make_session(make_plan(), first_bytes + duplicate);
    setup_first_commit(*session);
    check(session->begin_next(), "no-op output fixture did not begin");
    drive_to_prepared(*session);
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      session->commit();
    }
    check(!session->next_output() &&
              session->status().output_remaining == 0 &&
              session->progress().sequence == 2 &&
              session->progress().source_positions.at("source-A-long") == 20,
          "empty output epoch did not commit no-op input progress");
    check(!session->begin_next(),
          "no-op output epoch prevented validated EOF from being reached");
  }
}

void paused_drain_and_start_drain() {
  {
    auto no_output = SessionOptions{};
    no_output.delta.spool_row_limit = 0;
    no_output.delta.spool_byte_limit = 0;
    const auto bytes = encode(make_plan(),
        event(1, SetOperation::insert, 7, "source-A-long", 10));
    auto session = make_session(make_plan(), bytes, std::move(no_output));
    session->start();
    check(session->begin_next(), "drain fixture did not begin");
    session->pause();
    check(session->status().state == SessionState::paused &&
              session->status().phase == SessionPhase::paused_pending,
          "pause did not retain the private epoch");
    expect_error([&] { static_cast<void>(session->begin_next()); },
                 "session_paused");
    expect_error([&] { static_cast<void>(session->step()); }, "session_paused");
    expect_error([&] { session->commit(); }, "session_paused");
    session->start_drain();
    session->drain();
    check(session->status().state == SessionState::paused &&
              session->status().phase == SessionPhase::ready &&
              session->status().committed_sequence == 1 &&
              session->progress() == first_progress() &&
              session->status().output_remaining == 0 &&
              image(*session) == first_snapshot(),
          "paused drain did not commit one input while keeping admission paused");
    session->start();
    check(session->status().state == SessionState::running &&
              session->status().output_remaining == 0 &&
              session->progress() == first_progress() &&
              image(*session) == first_snapshot(),
          "paused start_drain did not publish the input without retaining output");
    session->drop();
  }

  {
    // Exercise output-spool quota failure after the event has been decoded.
    // start_drain retries the very same cached event under the no-retention
    // policy, which is permitted even with both output limits set to zero.
    auto no_output = SessionOptions{};
    no_output.delta.spool_row_limit = 0;
    no_output.delta.spool_byte_limit = 0;
    const auto bytes = encode(make_plan(),
        event(1, SetOperation::insert, 9, "quota-source", 100));
    auto session = make_session(make_plan(), bytes, std::move(no_output));
    session->start();
    check(session->begin_next(), "quota retry fixture did not begin");
    bool limited = false;
    try {
      drive_to_prepared(*session);
    } catch (const Error& failure) {
      limited = failure.code() == "resource_limit";
    }
    check(limited && session->status().committed_sequence == 0 &&
              !session->status().pending_sequence &&
              !session->status().input_failed &&
              session->progress() == io::InputProgress{} &&
              image(*session) == SnapshotImage{0, {}, {}},
          "late spool quota failure published a prefix or acknowledged source input");
    check(session->begin_next(),
          "quota failure discarded the cached engine event before retry");
    session->start_drain();
    session->drain();
    check(!session->next_output() &&
              session->progress().sequence == 1 &&
              session->progress().source_positions.at("quota-source") == 100 &&
              image(*session) == SnapshotImage{1,
                  io::InputProgress{1, {{"quota-source", 100}}}, {{n(9)}}},
          "cached event could not retry after a quota failure with output disabled");
    session->drop();
  }
}

void late_alias_quota_failure_retries_without_a_committed_prefix() {
  const auto plan = make_alias_plan();
  const auto make_alias_event = [&](std::uint64_t sequence, std::int64_t x,
                                    std::int64_t z, std::uint64_t offset) {
    return io::InputEvent{{sequence, TableId{0}, SetOperation::insert,
                           {n(x), n(z)}},
                          io::SourcePosition{"alias-source-long", offset}};
  };
  const auto bytes = encode(plan, make_alias_event(1, 1, 2, 10)) +
                     encode(plan, make_alias_event(2, 2, 1, 20));
  SessionOptions limited_options;
  limited_options.delta.spool_row_limit = 1;
  auto session = make_session(make_alias_plan(), bytes,
                              std::move(limited_options));
  session->start();
  check(session->begin_next(), "alias quota fixture did not begin its seed");
  accept_current(*session);
  check(!session->next_output() && session->progress().sequence == 1 &&
            session->progress().source_positions.at("alias-source-long") == 10 &&
            session->snapshot().rows.empty(),
        "alias quota seed unexpectedly produced an answer or accepted progress early");
  check(session->begin_next(), "alias quota fixture did not begin its joining event");

  bool limited = false;
  try {
    drive_to_prepared(*session);
  } catch (const Error& failure) {
    limited = failure.code() == "resource_limit";
  }
  io::InputProgress before_progress;
  before_progress.sequence = 1;
  before_progress.source_positions.emplace("alias-source-long", 10);
  check(limited && session->status().committed_sequence == 1 &&
            !session->status().pending_sequence &&
            !session->status().input_failed &&
            session->progress() == before_progress &&
            session->snapshot().sequence == 1 &&
            session->snapshot().rows.empty(),
        "late alias spool quota failure published a partial result or source position");

  check(session->begin_next(),
        "late alias quota failure discarded its cached decoded input");
  session->start_drain();
  session->drain();
  const auto after = session->snapshot();
  check(after.sequence == 2 && after.progress.sequence == 2 &&
            after.progress.source_positions.at("alias-source-long") == 20 &&
            after.rows.size() == 2,
        "same cached alias event did not commit completely with retention disabled");
  const bool has_forward = std::any_of(after.rows.begin(), after.rows.end(),
      [](const storage::Tuple& row) {
        return row.values() == Row{n(1), n(2)};
      });
  const bool has_reverse = std::any_of(after.rows.begin(), after.rows.end(),
      [](const storage::Tuple& row) {
        return row.values() == Row{n(2), n(1)};
      });
  check(has_forward && has_reverse,
        "alias retry lost one result from the two-route committed join");
  session->drop();
}

std::size_t sweep_start_drain_failures(const std::string& bytes) {
  constexpr std::ptrdiff_t max_points = 8192;
  std::size_t failures = 0;
  for (std::ptrdiff_t point = 0; point < max_points; ++point) {
    auto session = make_session(make_plan(), bytes);
    setup_first_commit(*session);
    check(session->begin_next(), "start_drain sweep did not begin its second event");
    static_cast<void>(session->step());
    bool failed = false;
    {
      FaultScope fault(point);
      try {
        session->start_drain();
        session->drain();
      } catch (const std::bad_alloc&) {
        failed = true;
        fail_after = 0;
      }
    }
    if (failed) {
      ++failures;
      check(session->status().committed_sequence == 1 &&
                !session->status().pending_sequence &&
                !session->status().input_failed &&
                session->progress() == first_progress() &&
                image(*session) == first_snapshot(),
            "start_drain/drain OOM acknowledged a private event or changed old results");
      check(session->begin_next(),
            "start_drain/drain OOM discarded the decoded event needed for retry");
      session->start_drain();
      session->drain();
      check(session->progress() == second_progress() &&
                session->status().committed_sequence == 2 &&
                session->status().output_remaining == 0 &&
                image(*session) == second_snapshot(),
            "no-retention retry after start_drain/drain OOM was not atomic");
      continue;
    }

    check(failures > 0,
          "start_drain/drain sweep observed no ordinary-new failures");
    check(session->status().committed_sequence == 2 &&
              session->progress() == second_progress() &&
              session->status().output_remaining == 0 &&
              image(*session) == second_snapshot(),
          "successful start_drain did not commit exactly the current event");
    std::cout << "session start_drain/drain ordinary-new failures=" << failures
              << '\n';
    return failures;
  }
  throw std::runtime_error("session start_drain/drain sweep exceeded 8192 fault points");
}

void stop_and_drop_abort_private_prefixes(const std::string& bytes) {
  {
    bool destroyed = false;
    auto session = make_session(make_plan(), bytes, {}, &destroyed);
    session->start();
    check(session->begin_next(), "unread-output stop fixture did not begin");
    accept_current(*session);
    check(session->status().output_remaining == 1,
          "unread-output stop fixture did not retain its committed epoch");
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      session->stop();
    }
    check(destroyed && session->status().state == SessionState::stopped &&
              session->status().output_remaining == 0 &&
              session->progress() == first_progress() &&
              image(*session) == first_snapshot(),
          "stop did not destroy unread output while retaining committed rows/progress");
    session->drop();
  }

  for (const std::size_t prefix : {std::size_t{0}, std::size_t{1}}) {
    bool destroyed = false;
    auto session = make_session(make_plan(), bytes, {}, &destroyed);
    setup_first_commit(*session);
    check(session->begin_next(), "stop fixture did not begin its pending event");
    for (std::size_t step = 0; step < prefix; ++step)
      static_cast<void>(session->step());
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      session->stop();
    }
    check(destroyed && session->status().state == SessionState::stopped &&
              session->status().committed_sequence == 1 &&
              !session->status().pending_sequence &&
              session->progress() == first_progress() &&
              image(*session) == first_snapshot(),
          "stop acknowledged or retained private input at a private work prefix");
    expect_error([&] { session->start(); }, "session_stopped");
    expect_error([&] { session->pause(); }, "session_stopped");
    expect_error([&] { static_cast<void>(session->begin_next()); },
                 "session_stopped");
    expect_error([&] { static_cast<void>(session->step()); },
                 "session_stopped");
    expect_error([&] { session->commit(); }, "session_stopped");
    expect_error([&] { session->start_drain(); }, "session_stopped");
    expect_error([&] { session->drain(); }, "session_stopped");
    expect_error([&] { static_cast<void>(session->next_output()); },
                 "session_stopped");
    check(image(*session) == first_snapshot(),
          "stopped session lost its committed snapshot");
    session->stop();
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      session.reset();
    }
  }

  for (const std::size_t prefix : {std::size_t{0}, std::size_t{1}}) {
    bool destroyed = false;
    auto session = make_session(make_plan(), bytes, {}, &destroyed);
    setup_first_commit(*session);
    check(session->begin_next(), "drop fixture did not begin its pending event");
    for (std::size_t step = 0; step < prefix; ++step)
      static_cast<void>(session->step());
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      session->drop();
    }
    check(destroyed && session->status().state == SessionState::dropped &&
              session->status().committed_sequence == 1 &&
              !session->status().pending_sequence,
          "drop did not abort pending work and destroy the runtime/input");
    expect_error([&] { static_cast<void>(session->progress()); },
                 "session_dropped");
    expect_error([&] { static_cast<void>(session->snapshot()); },
                 "session_dropped");
    expect_error([&] { static_cast<void>(session->begin_next()); },
                 "session_dropped");
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      session.reset();
    }
  }
}

void snapshot_rows_and_committed_output_outlive_session() {
  const auto plan = make_plan();
  const auto bytes = encode(plan,
      event(1, SetOperation::insert, 7, "source-A-long", 10)) +
      encode(plan, event(2, SetOperation::erase, 7, "source-A-long", 20));
  auto session = make_session(make_plan(), bytes);
  session->start();
  check(session->begin_next(), "snapshot lifetime fixture did not begin");
  accept_current(*session);
  auto held_snapshot = session->snapshot();
  auto held_output = session->next_output();
  check(held_snapshot.rows.size() == 1 &&
            held_snapshot.rows.front().values() == Row{n(7)} && held_output &&
            held_output->tuple.values() == Row{n(7)},
        "lifetime fixture did not retain owning snapshot/output rows");
  check(session->begin_next(),
        "consuming the first output did not release its epoch before the delete");
  accept_current(*session);
  auto erased = session->next_output();
  check(erased && erased->operation == SetOperation::erase &&
            erased->tuple.values() == Row{n(7)} && !session->next_output() &&
            session->snapshot().rows.empty(),
        "delete output or empty committed result was incorrect");
  session->drop();
  check(held_snapshot.rows.front().values() == Row{n(7)} &&
            held_snapshot.progress.sequence == 1 &&
            held_output->tuple.values() == Row{n(7)},
        "returned snapshot/output retained engine pins instead of owning their rows");
}

void lifecycle_errors_and_guards() {
  const auto first = encode(make_plan(),
      event(1, SetOperation::insert, 7, "source-A-long", 10));

  {
    auto session = make_session(make_plan(), first);
    check(session->status().state == SessionState::created,
          "created session has the wrong initial state");
    expect_error([&] { session->pause(); }, "session_not_started");
    expect_error([&] { static_cast<void>(session->begin_next()); },
                 "session_not_started");
    expect_error([&] { static_cast<void>(session->step()); },
                 "session_not_started");
    expect_error([&] { session->commit(); }, "session_not_started");
    expect_error([&] { session->start_drain(); }, "session_not_started");
    expect_error([&] { session->drain(); }, "session_not_started");
    expect_error([&] { static_cast<void>(session->next_output()); },
                 "session_not_started");
    check(session->progress() == io::InputProgress{} &&
              image(*session) == SnapshotImage{0, {}, {}},
          "created-state misuse changed session progress or results");
    session->start();
    session->pause();
    expect_error([&] { static_cast<void>(session->begin_next()); },
                 "session_paused");
    expect_error([&] { static_cast<void>(session->step()); }, "session_paused");
    expect_error([&] { session->commit(); }, "session_paused");
    session->start();
    session->stop();
    expect_error([&] { session->start(); }, "session_stopped");
    expect_error([&] { static_cast<void>(session->begin_next()); },
                 "session_stopped");
    check(session->progress() == io::InputProgress{} &&
              image(*session) == SnapshotImage{0, {}, {}},
          "stop from an empty session discarded retained snapshot access");
    session->drop();
    check(session->status().state == SessionState::dropped,
          "drop after stop did not become terminal");
    expect_error([&] { session->start(); }, "session_dropped");
    expect_error([&] { session->pause(); }, "session_dropped");
    expect_error([&] { static_cast<void>(session->begin_next()); },
                 "session_dropped");
    expect_error([&] { static_cast<void>(session->step()); },
                 "session_dropped");
    expect_error([&] { session->commit(); }, "session_dropped");
    expect_error([&] { session->start_drain(); }, "session_dropped");
    expect_error([&] { session->drain(); }, "session_dropped");
    expect_error([&] { static_cast<void>(session->next_output()); },
                 "session_dropped");
    expect_error([&] { static_cast<void>(session->progress()); },
                 "session_dropped");
    expect_error([&] { static_cast<void>(session->snapshot()); },
                 "session_dropped");
    session->stop();
    session->drop();
  }

  {
    auto session = make_session(make_plan(), first);
    std::string worker_error;
    std::thread worker([&] {
      try {
        session->pause();
      } catch (const Error& failure) {
        worker_error = failure.code();
      }
    });
    worker.join();
    check(worker_error == "session_wrong_thread" &&
              session->status().state == SessionState::created,
          "wrong-thread guard did not run before the created-state check");
    session->start();
    session->stop();
  }

  {
    class ReentrantBuffer final : public std::streambuf {
     public:
      explicit ReentrantBuffer(std::string bytes)
          : bytes(std::move(bytes)) {}
      std::function<void()> callback;
      bool fired = false;

     protected:
      int_type underflow() override {
        if (!fired && callback) {
          fired = true;
          callback();
        }
        if (position == bytes.size()) return traits_type::eof();
        return traits_type::to_int_type(bytes[position]);
      }
      int_type uflow() override {
        const auto next = underflow();
        if (!traits_type::eq_int_type(next, traits_type::eof())) ++position;
        return next;
      }
      std::streamsize xsgetn(char* destination,
                             std::streamsize count) override {
        std::streamsize copied = 0;
        while (copied < count) {
          const auto next = uflow();
          if (traits_type::eq_int_type(next, traits_type::eof())) break;
          destination[copied++] = traits_type::to_char_type(next);
        }
        return copied;
      }

     private:
      std::string bytes;
      std::size_t position = 0;
    };
    class ReentrantStream final : public std::istream {
     public:
      explicit ReentrantStream(std::string bytes)
          : std::istream(nullptr), buffer(std::move(bytes)) {
        rdbuf(&buffer);
      }
      ReentrantBuffer buffer;
    };

    auto plan = make_plan();
    const auto bytes = encode(plan,
        event(1, SetOperation::insert, 7, "source-A-long", 10));
    auto input = std::make_unique<ReentrantStream>(bytes);
    auto* raw = input.get();
    std::unique_ptr<std::istream> owned = std::move(input);
    auto session = QuerySession::create(std::move(plan), std::move(owned));
    std::string reentry_error;
    raw->buffer.callback = [&] {
      try {
        session->pause();
      } catch (const Error& failure) {
        reentry_error = failure.code();
      }
    };
    session->start();
    check(session->begin_next() && reentry_error == "session_busy" &&
              session->status().state == SessionState::running,
          "reentrant stream callback bypassed the session operation guard");
    session->stop();
  }
}

}  // namespace

int main() {
  try {
    const auto plan = make_plan();
    const auto bytes = stream_bytes(plan);
    const auto first = encode(plan,
        event(1, SetOperation::insert, 7, "source-A-long", 10));
    const auto first_two = encode(plan,
        event(2, SetOperation::insert, 8, "source-A-long", 20));
    const auto clean = run_phase("clean run", [&] {
      return run_clean(make_plan(), bytes);
    });
    check(clean.final_snapshot == final_snapshot() &&
              clean.outputs == std::vector<OutputImage>{
                  {1, SetOperation::insert, {n(7)}},
                  {1, SetOperation::insert, {n(8)}},
                  {1, SetOperation::erase, {n(7)}}},
          "clean session did not match the exact unary query result and signed deltas");

    const auto create_failures = run_phase("create ordinary-new failure sweep", [&] {
      return sweep_create_failures(bytes);
    });
    const auto begin_failures = run_phase("begin_next ordinary-new failure sweep", [&] {
      return sweep_begin_next_failures(bytes, clean);
    });
    const auto step_failures = run_phase("retaining step ordinary-new failure sweep", [&] {
      return sweep_retaining_step_failures(bytes, clean);
    });
    const auto snapshot_failures = run_phase("snapshot ordinary-new failure sweep", [&] {
      return sweep_snapshot_failures(bytes, clean);
    });
    const auto start_drain_failures = run_phase("start_drain ordinary-new failure sweep", [&] {
      return sweep_start_drain_failures(bytes);
    });
    run_phase("late alias quota retry", [&] {
      late_alias_quota_failure_retries_without_a_committed_prefix();
    });
    run_phase("EventReader close", [&] {
      reader_close_moves_only_accepted_progress_without_allocation();
    });
    run_phase("commit/output/cleanup", [&] {
      commit_output_and_cleanup_are_allocation_free(first, first + first_two +
          encode(plan, event(3, SetOperation::erase, 7, "source-B-long", 50)));
    });
    run_phase("paused drain", [&] { paused_drain_and_start_drain(); });
    run_phase("stop/drop prefixes", [&] {
      stop_and_drop_abort_private_prefixes(bytes);
    });
    run_phase("snapshot ownership", [&] {
      snapshot_rows_and_committed_output_outlive_session();
    });
    run_phase("state/thread/reentry guards", [&] {
      lifecycle_errors_and_guards();
    });
    std::cout << "session create ordinary-new failures=" << create_failures
              << ", begin_next ordinary-new failures=" << begin_failures
              << ", retaining step ordinary-new failures=" << step_failures
              << ", snapshot ordinary-new failures=" << snapshot_failures
              << ", start_drain/drain ordinary-new failures="
              << start_drain_failures << '\n';
    std::cout << "QuerySession failure atomicity, output, snapshot, and lifecycle checks passed\n";
  } catch (const std::exception& failure) {
    fail_after = -1;
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
