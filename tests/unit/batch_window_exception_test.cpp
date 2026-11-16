#include "crown/api/error.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/session.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <new>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

// This executable owns global new so injected failures stay armed while
// partially prepared queues, sessions, and engine epochs unwind.
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

Value n(std::int64_t value) { return value; }

Catalog unary_catalog() {
  return {91, {{"R", {{"x", ScalarType::int64}}}}};
}

PhysicalPlan unary_plan() {
  const auto catalog = unary_catalog();
  const Query query{{{"x", ScalarType::int64}},
                    {{"r", TableId{0}, {VariableId{0}}}},
                    {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"root", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan alias_plan() {
  const Catalog catalog{92, {{"E", {{"x", ScalarType::int64},
                                      {"z", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"z", ScalarType::int64}},
                    {{"forward", TableId{0}, {VariableId{0}, VariableId{1}}},
                     {"reverse", TableId{0}, {VariableId{1}, VariableId{0}}}},
                    {{VariableId{0}, "x"}, {VariableId{1}, "z"}}, false};
  const FreeConnexTree tree{NodeId{0}, {
      {"intersection", NodeKind::generalized,
       {VariableId{0}, VariableId{1}}, {NodeId{1}, NodeId{2}}, {}, {}},
      {"forward", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}},
      {"reverse", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

io::InputItem physical_item(std::uint64_t sequence, Row row,
                            std::string source = "source-A",
                            std::uint64_t offset = 0) {
  return io::InputEvent{{sequence, TableId{0}, SetOperation::insert,
                         std::move(row)},
                        io::SourcePosition{std::move(source), offset}};
}

io::InputItem window_insert(std::uint64_t sequence, std::uint64_t label,
                            Row row, std::uint64_t timestamp,
                            std::string source = "window-source") {
  return io::WindowCommand{sequence,
      io::WindowInsert{label, TableId{0}, std::move(row), timestamp},
      io::SourcePosition{std::move(source), sequence * 10}};
}

io::InputItem watermark(std::uint64_t sequence, std::uint64_t time,
                        std::string source = "window-source") {
  return io::WindowCommand{sequence, io::AdvanceWatermark{time},
      io::SourcePosition{std::move(source), sequence * 10}};
}

io::TransportBatch batch(std::vector<io::InputItem> items) {
  return io::TransportBatch(std::move(items));
}

struct SessionImage {
  std::uint64_t sequence = 0;
  io::InputProgress progress;
  std::vector<Row> rows;
  std::optional<WindowProgress> window;
  bool operator==(const SessionImage&) const = default;
};

SessionImage image(const QuerySession& session) {
  const auto snapshot = session.snapshot();
  SessionImage result;
  result.sequence = snapshot.sequence;
  result.progress = snapshot.progress;
  result.window = snapshot.window;
  for (const auto& row : snapshot.rows) result.rows.push_back(crown::storage::export_row(row.values()));
  return result;
}

std::optional<io::QueueStats> queue_stats(const QuerySession& session) {
  return session.status().queue;
}

WindowOptions window_options() {
  WindowOptions options;
  options.managed_tables = {TableId{0}};
  options.width = 5;
  options.fifo = WindowFifoPolicy::per_relation;
  return options;
}

void drain_output(QuerySession& session) {
  while (session.next_output()) {}
}

void prepare_current(QuerySession& session) {
  for (;;) {
    if (session.step() == DeltaStep::prepared) return;
  }
}

void finish_current(QuerySession& session) {
  prepare_current(session);
  session.commit();
  drain_output(session);
}

void accept(QuerySession& session, io::TransportBatch& input) {
  check(session.enqueue(input) == io::Admission::accepted,
        "fixture batch was not admitted");
}

template <class Context, class Factory, class Operation, class AfterFailure,
          class AfterSuccess>
std::size_t sweep_fault_positions(std::string_view label, Factory factory,
                                  Operation operation,
                                  AfterFailure after_failure,
                                  AfterSuccess after_success) {
  std::size_t failures = 0;
  for (std::ptrdiff_t point = 0;; ++point) {
    Context context = factory();
    bool failed = false;
    {
      FaultScope fault(point);
      try {
        operation(context);
      } catch (const std::bad_alloc&) {
        failed = true;
        // Leave failures armed through all stack unwinding, then inspect only
        // after the fault scope has disabled the injector.
        fault.forbid_allocations();
      }
    }
    if (failed) {
      ++failures;
      after_failure(context);
      if (point == std::numeric_limits<std::ptrdiff_t>::max())
        throw std::runtime_error(std::string(label) + ": fault index exhausted");
      continue;
    }
    check(failures > 0,
          std::string(label) + ": allocation sweep injected no bad_alloc");
    after_success(context);
    std::cout << label << " fault_positions=" << failures << '\n';
    return failures;
  }
}

struct CreateAttempt {
  PhysicalPlan plan;
  QuerySession::Owner session;
  explicit CreateAttempt(PhysicalPlan value) : plan(std::move(value)) {}
};

void typed_session_construction_unwinds_cleanly() {
  sweep_fault_positions<CreateAttempt>("create_typed", [] {
    return CreateAttempt{unary_plan()};
  }, [](CreateAttempt& attempt) {
    attempt.session = QuerySession::create_typed(std::move(attempt.plan));
  }, [](CreateAttempt& attempt) {
    check(!attempt.session, "failed typed construction published a session");
  }, [](CreateAttempt& attempt) {
    check(attempt.session &&
              attempt.session->status().state == SessionState::created &&
              attempt.session->progress() == io::InputProgress{},
          "typed construction did not reach its empty state after retry");
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    attempt.session.reset();
  });

  sweep_fault_positions<CreateAttempt>("create_windowed", [] {
    return CreateAttempt{unary_plan()};
  }, [](CreateAttempt& attempt) {
    attempt.session = QuerySession::create_windowed(
        std::move(attempt.plan), window_options());
  }, [](CreateAttempt& attempt) {
    check(!attempt.session, "failed windowed construction published a session");
  }, [](CreateAttempt& attempt) {
    std::optional<WindowCanonicalState> state;
    if (attempt.session) state = attempt.session->window_state();
    check(attempt.session && state && state->labels.empty() &&
              state->counts.empty() && state->expiration_index.empty() &&
              state->global_fifo.empty() && state->completed_command_sequence == 0 &&
              state->physical_sequence == 0 && state->completed_watermark == 0 &&
              state->last_label == 0 && attempt.session->status().state ==
                  SessionState::created &&
              attempt.session->progress() == io::InputProgress{},
          "windowed construction did not reach its empty state after retry");
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    attempt.session.reset();
  });
}

struct QueueAttempt {
  QuerySession::Owner session;
  io::TransportBatch input;
  QueueAttempt(QuerySession::Owner value, io::TransportBatch batch_value)
      : session(std::move(value)), input(std::move(batch_value)) {}
};

QueueAttempt queue_attempt(io::QueueLimits limits = {}) {
  auto session = QuerySession::create_typed(unary_plan(), limits);
  return {std::move(session), batch({physical_item(1, {n(7)}, "new-source", 50)})};
}

void queue_admission_is_transactional_and_retriable() {
  sweep_fault_positions<QueueAttempt>("queue enqueue", [] {
    return queue_attempt();
  }, [](QueueAttempt& attempt) {
    static_cast<void>(attempt.session->enqueue(attempt.input));
  }, [](QueueAttempt& attempt) {
    check(attempt.input.size() == 1 && !attempt.input.empty() &&
              queue_stats(*attempt.session) == io::QueueStats{},
          "enqueue allocation failure changed the batch or queue");
    check(attempt.session->enqueue(attempt.input) == io::Admission::accepted &&
              attempt.input.empty() &&
              queue_stats(*attempt.session)->events == 1,
          "the unchanged batch did not retry after enqueue allocation failure");
  }, [](QueueAttempt& attempt) {
    check(attempt.input.empty() &&
              queue_stats(*attempt.session)->events == 1 &&
              queue_stats(*attempt.session)->batches == 1,
          "successful enqueue did not transfer the complete batch");
  });

  io::QueueLimits limits;
  limits.batches = 1;
  limits.events = 1;
  auto session = QuerySession::create_typed(unary_plan(), limits);
  auto first = batch({physical_item(1, {n(1)}, "full-source", 10)});
  auto second = batch({physical_item(2, {n(2)}, "full-source", 20)});
  check(session->enqueue(first) == io::Admission::accepted,
        "queue-full fixture did not accept its first batch");
  const auto full_stats = queue_stats(*session);
  check(session->enqueue(second) == io::Admission::full &&
            second.size() == 1 && queue_stats(*session) == full_stats,
        "full rejection mutated the caller batch or queue statistics");
  session->start();
  check(session->begin_next(), "first full-queue event did not begin");
  finish_current(*session);
  check(session->enqueue(second) == io::Admission::accepted && second.empty(),
        "full-rejected batch did not retry after queue capacity was released");
}

struct PeekAttempt {
  io::TypedQueue queue;
  io::TransportBatch input;
  io::QueueStats queue_before;
  PeekAttempt()
      : queue(unary_catalog(), io::QueueMode::physical),
        input(batch({physical_item(1, {n(7)}, "peek-new-source", 51)})) {
    check(queue.enqueue(input) == io::Admission::accepted,
          "peek fixture batch was not accepted");
    queue_before = queue.stats();
  }
};

void new_source_peek_node_allocation_is_retriable() {
  sweep_fault_positions<PeekAttempt>("new source peek", [] {
    return PeekAttempt{};
  }, [](PeekAttempt& attempt) {
    static_cast<void>(attempt.queue.peek());
  }, [](PeekAttempt& attempt) {
    check(!attempt.queue.failed() && attempt.queue.progress() == io::InputProgress{} &&
              attempt.queue.stats() == attempt.queue_before,
          "new-source map-node allocation failure poisoned or acknowledged the queue");
    const auto* retry = attempt.queue.peek();
    check(retry && std::get<io::InputEventView>(*retry).source_position &&
              std::get<io::InputEventView>(*retry).source_position->source ==
                  "peek-new-source",
          "new-source queue head was not retriable after allocation failure");
    attempt.queue.acknowledge();
    check(attempt.queue.progress().sequence == 1 &&
              attempt.queue.progress().source_positions.at("peek-new-source") == 51,
          "retried source position was not acknowledged exactly once");
  }, [](PeekAttempt& attempt) {
    const auto* head = attempt.queue.peek();
    check(head && !attempt.queue.failed() &&
              attempt.queue.progress() == io::InputProgress{} &&
              attempt.queue.stats() == attempt.queue_before,
          "successful peek acknowledged or failed its prepared head");
  });
}

struct PhysicalRetryAttempt {
  QuerySession::Owner session;
  SessionImage before;
  std::optional<WindowCanonicalState> window_before;
  std::optional<io::QueueStats> queue_before;
};

PhysicalRetryAttempt alias_retry_attempt() {
  auto session = QuerySession::create_typed(alias_plan());
  auto input = batch({physical_item(1, {n(1), n(2)}, "alias-source", 10),
                      physical_item(2, {n(2), n(1)}, "alias-source", 20)});
  accept(*session, input);
  session->start();
  check(session->begin_next(), "alias seed input did not begin");
  finish_current(*session);
  PhysicalRetryAttempt attempt;
  attempt.session = std::move(session);
  attempt.before = image(*attempt.session);
  attempt.window_before = attempt.session->window_state();
  attempt.queue_before = queue_stats(*attempt.session);
  return attempt;
}

void check_alias_rollback(const PhysicalRetryAttempt& attempt) {
  const auto status = attempt.session->status();
  check(status.phase == SessionPhase::ready && !status.pending_sequence &&
            !status.pending_command_sequence && !status.input_failed &&
            status.committed_sequence == 1 &&
            attempt.session->progress().sequence == 1 &&
            image(*attempt.session) == attempt.before &&
            attempt.session->window_state() == attempt.window_before &&
            queue_stats(*attempt.session) == attempt.queue_before,
        "alias allocation failure changed the committed engine prefix or queue head");
}

void retry_alias_input(PhysicalRetryAttempt& attempt) {
  check(attempt.session->begin_next(), "same alias input was lost on retry");
  finish_current(*attempt.session);
  const auto after = image(*attempt.session);
  const auto has = [&](const Row& row) {
    return std::find(after.rows.begin(), after.rows.end(), row) != after.rows.end();
  };
  check(after.sequence == 2 && after.progress.sequence == 2 &&
            after.rows.size() == 2 && has({n(1), n(2)}) && has({n(2), n(1)}),
        "same self-join alias insertion did not produce the complete engine result");
  check(attempt.session->status().queue->events == 0,
        "successful self-join retry did not acknowledge its queue head");
}

void self_join_pending_epoch_begin_and_step_failures_retry() {
  sweep_fault_positions<PhysicalRetryAttempt>("alias begin", [] {
    return alias_retry_attempt();
  }, [](PhysicalRetryAttempt& attempt) {
    static_cast<void>(attempt.session->begin_next());
  }, [](PhysicalRetryAttempt& attempt) {
    check_alias_rollback(attempt);
    retry_alias_input(attempt);
  }, [](PhysicalRetryAttempt& attempt) {
    finish_current(*attempt.session);
    const auto rows = image(*attempt.session).rows;
    check(rows.size() == 2,
          "successful alias begin did not prepare the expected pending epoch");
  });

  sweep_fault_positions<PhysicalRetryAttempt>("alias persistent step", [] {
    auto attempt = alias_retry_attempt();
    check(attempt.session->begin_next(), "alias step fixture did not begin");
    return attempt;
  }, [](PhysicalRetryAttempt& attempt) {
    prepare_current(*attempt.session);
  }, [](PhysicalRetryAttempt& attempt) {
    check_alias_rollback(attempt);
    retry_alias_input(attempt);
  }, [](PhysicalRetryAttempt& attempt) {
    attempt.session->commit();
    drain_output(*attempt.session);
    const auto rows = image(*attempt.session).rows;
    check(rows.size() == 2,
          "successful alias persistent step did not publish the complete result");
  });
}

struct WindowAttempt {
  QuerySession::Owner session;
  SessionImage before;
  std::optional<WindowCanonicalState> canonical_before;
  std::optional<io::QueueStats> queue_before;
};

WindowAttempt initial_window_attempt(WindowOptions options = window_options()) {
  auto session = QuerySession::create_windowed(unary_plan(), std::move(options));
  auto input = batch({window_insert(1, 1, {n(7)}, 0),
                      window_insert(2, 2, {n(8)}, 0)});
  accept(*session, input);
  session->start();
  WindowAttempt attempt;
  attempt.session = std::move(session);
  attempt.before = image(*attempt.session);
  attempt.canonical_before = attempt.session->window_state();
  attempt.queue_before = queue_stats(*attempt.session);
  return attempt;
}

void check_window_rollback(const WindowAttempt& attempt) {
  const auto status = attempt.session->status();
  check(status.phase == SessionPhase::ready && !status.pending_sequence &&
            !status.pending_command_sequence && !status.input_failed &&
            status.committed_sequence == attempt.before.sequence &&
            attempt.session->progress() == attempt.before.progress &&
            image(*attempt.session) == attempt.before &&
            attempt.session->window_state() == attempt.canonical_before &&
            queue_stats(*attempt.session) == attempt.queue_before,
        "window allocation failure changed a committed prefix, canonical state, or queue head");
}

void retry_first_window_insert(WindowAttempt& attempt) {
  check(attempt.session->begin_next(), "same window insertion was lost on retry");
  finish_current(*attempt.session);
  const auto state = attempt.session->window_state();
  check(state && state->labels.size() == 1 && state->counts.size() == 1 &&
            state->labels.front().label == 1 && state->counts.front().count == 1 &&
            attempt.session->progress().sequence == 1 &&
            image(*attempt.session).rows == std::vector<Row>{{n(7)}},
        "same first window insertion did not publish its label and retained row");
}

void window_new_label_and_count_nodes_rollback() {
  sweep_fault_positions<WindowAttempt>("window insertion begin", [] {
    return initial_window_attempt();
  }, [](WindowAttempt& attempt) {
    static_cast<void>(attempt.session->begin_next());
  }, [](WindowAttempt& attempt) {
    check_window_rollback(attempt);
    retry_first_window_insert(attempt);
  }, [](WindowAttempt& attempt) {
    finish_current(*attempt.session);
    check(attempt.session->window_state()->labels.size() == 1,
          "successful window insertion preparation did not retain its label");
  });

  sweep_fault_positions<WindowAttempt>("window persistent step", [] {
    auto attempt = initial_window_attempt();
    check(attempt.session->begin_next(), "window step fixture did not begin");
    return attempt;
  }, [](WindowAttempt& attempt) {
    prepare_current(*attempt.session);
  }, [](WindowAttempt& attempt) {
    check_window_rollback(attempt);
    retry_first_window_insert(attempt);
  }, [](WindowAttempt& attempt) {
    attempt.session->commit();
    drain_output(*attempt.session);
    check(attempt.session->window_state()->counts.front().count == 1,
          "successful persistent window step did not publish the row reference");
  });
}

WindowAttempt duplicate_window_attempt() {
  auto session = QuerySession::create_windowed(unary_plan(), window_options());
  auto input = batch({window_insert(1, 1, {n(7)}, 0),
                      window_insert(2, 2, {n(7)}, 1),
                      watermark(3, 5)});
  accept(*session, input);
  session->start();
  check(session->begin_next(), "duplicate window seed did not begin");
  finish_current(*session);
  WindowAttempt attempt;
  attempt.session = std::move(session);
  attempt.before = image(*attempt.session);
  attempt.canonical_before = attempt.session->window_state();
  attempt.queue_before = queue_stats(*attempt.session);
  return attempt;
}

void finish_duplicate_metadata_command(QuerySession& session,bool begin_input=true) {
  if (begin_input)
    check(session.begin_next(), "duplicate full-row command did not retry");
  const auto status = session.status();
  check(!status.pending_sequence && status.pending_command_sequence == 2,
        "duplicate full-row command unexpectedly started a physical epoch");
  check(session.step() == DeltaStep::prepared,
        "duplicate full-row command did not reach its metadata barrier");
  allocation_count = 0;
  {
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    session.commit();
  }
  const auto metadata_commit_allocations = allocation_count;
  check(metadata_commit_allocations == 0,
        "metadata-only window publication or source acknowledgement allocated");
}

void duplicate_row_metadata_prepare_and_commit() {
  sweep_fault_positions<WindowAttempt>("duplicate window metadata begin", [] {
    return duplicate_window_attempt();
  }, [](WindowAttempt& attempt) {
    static_cast<void>(attempt.session->begin_next());
  }, [](WindowAttempt& attempt) {
    check_window_rollback(attempt);
    finish_duplicate_metadata_command(*attempt.session);
  }, [](WindowAttempt& attempt) {
    finish_duplicate_metadata_command(*attempt.session,false);
  });

  auto attempt = duplicate_window_attempt();
  check(attempt.session->begin_next(), "duplicate no-allocation fixture did not begin");
  check(attempt.session->step() == DeltaStep::prepared,
        "duplicate no-allocation fixture did not reach preparation");
  allocation_count = 0;
  {
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    attempt.session->commit();
  }
  const auto duplicate_commit_allocations = allocation_count;
  check(duplicate_commit_allocations == 0,
        "prepared duplicate metadata commit allocated");
  const auto state = attempt.session->window_state();
  const auto status = attempt.session->status();
  check(state && state->labels.size() == 2 && state->counts.size() == 1 &&
            state->counts.front().count == 2 && state->physical_sequence == 1 &&
            state->completed_command_sequence == 2 &&
            status.committed_sequence == 1 && status.queue->events == 1 &&
            attempt.session->progress().sequence == 2 &&
            image(*attempt.session).rows == std::vector<Row>{{n(7)}},
        "duplicate command changed physical multiplicity or failed to acknowledge metadata");
}

WindowAttempt watermark_attempt(bool partial_prefix, bool prepare_second) {
  auto options = window_options();
  auto session = QuerySession::create_windowed(unary_plan(), options);
  auto input = batch({window_insert(1, 1, {n(1)}, 0),
                      window_insert(2, 2, {n(2)}, 0),
                      watermark(3, 5),
                      window_insert(4, 3, {n(3)}, 5)});
  accept(*session, input);
  session->start();
  check(session->begin_next(), "watermark fixture did not begin its first insert");
  finish_current(*session);
  check(session->begin_next(), "watermark fixture did not begin its second insert");
  finish_current(*session);
  if (partial_prefix) {
    check(session->begin_next(), "watermark fixture did not begin preflight");
    finish_current(*session);
  }
  WindowAttempt attempt;
  attempt.session = std::move(session);
  attempt.before = image(*attempt.session);
  attempt.canonical_before = attempt.session->window_state();
  attempt.queue_before = queue_stats(*attempt.session);
  if (prepare_second) {
    check(attempt.session->begin_next(),
          "later watermark expiration did not prepare");
  }
  return attempt;
}

void check_watermark_prefix_rollback(const WindowAttempt& attempt) {
  const auto status = attempt.session->status();
  check(status.phase == SessionPhase::ready && !status.pending_sequence &&
            status.pending_command_sequence == std::nullopt &&
            !status.input_failed && status.committed_sequence == attempt.before.sequence &&
            attempt.session->progress() == attempt.before.progress &&
            image(*attempt.session) == attempt.before &&
            attempt.session->window_state() == attempt.canonical_before &&
            queue_stats(*attempt.session) == attempt.queue_before,
        "watermark failure moved its committed prefix, active command, or source progress");
}

void retry_watermark_step(WindowAttempt& attempt) {
  check(attempt.session->begin_next(), "watermark command head was lost on retry");
  finish_current(*attempt.session);
  const auto status = attempt.session->status();
  const auto state = attempt.session->window_state();
  check(state && status.queue && state->active_command &&
            state->active_command->sequence == 3 &&
            state->active_command->completed_steps == 1 &&
            attempt.session->progress().sequence == 2 &&
            status.queue->events == 2,
        "watermark retry did not commit exactly one expiration prefix");
}

void watermark_preflight_and_first_step_failures_retry() {
  sweep_fault_positions<WindowAttempt>("watermark preflight", [] {
    return watermark_attempt(false, false);
  }, [](WindowAttempt& attempt) {
    static_cast<void>(attempt.session->begin_next());
  }, [](WindowAttempt& attempt) {
    check_watermark_prefix_rollback(attempt);
    retry_watermark_step(attempt);
  }, [](WindowAttempt& attempt) {
    finish_current(*attempt.session);
    const auto state = attempt.session->window_state();
    check(state && state->active_command &&
              state->active_command->completed_steps == 1,
          "successful watermark preflight did not publish its first expiration");
  });

  sweep_fault_positions<WindowAttempt>("watermark first persistent step", [] {
    auto attempt = watermark_attempt(false, false);
    check(attempt.session->begin_next(), "watermark first-step fixture did not begin");
    return attempt;
  }, [](WindowAttempt& attempt) {
    prepare_current(*attempt.session);
  }, [](WindowAttempt& attempt) {
    check_watermark_prefix_rollback(attempt);
    retry_watermark_step(attempt);
  }, [](WindowAttempt& attempt) {
    attempt.session->commit();
    drain_output(*attempt.session);
    const auto state = attempt.session->window_state();
    check(state && state->active_command &&
              state->active_command->completed_steps == 1,
          "successful first watermark engine step did not publish its prefix");
  });
}

void later_watermark_step_failure_preserves_real_prefix_and_retries() {
  sweep_fault_positions<WindowAttempt>("later watermark begin", [] {
    return watermark_attempt(true, false);
  }, [](WindowAttempt& attempt) {
    static_cast<void>(attempt.session->begin_next());
  }, [](WindowAttempt& attempt) {
    check_watermark_prefix_rollback(attempt);
    check(attempt.before.sequence == 3 && attempt.before.progress.sequence == 2 &&
              attempt.canonical_before &&
              attempt.canonical_before->active_command &&
              attempt.canonical_before->active_command->completed_steps == 1,
          "later watermark fixture did not retain a real committed prefix");
    check(attempt.session->begin_next(),
          "later watermark command was not retryable after begin allocation failure");
    finish_current(*attempt.session);
    check(attempt.session->progress().sequence == 3 &&
              image(*attempt.session).rows.empty(),
          "later watermark retry did not finish the same command");
  }, [](WindowAttempt& attempt) {
    finish_current(*attempt.session);
    check(attempt.session->progress().sequence == 3 &&
              image(*attempt.session).rows.empty(),
          "successful later watermark begin did not finish the same input");
  });

  sweep_fault_positions<WindowAttempt>("later watermark persistent step", [] {
    return watermark_attempt(true, true);
  }, [](WindowAttempt& attempt) {
    prepare_current(*attempt.session);
  }, [](WindowAttempt& attempt) {
    check_watermark_prefix_rollback(attempt);
    check(attempt.before.sequence == 3 && attempt.before.progress.sequence == 2 &&
              attempt.canonical_before &&
              attempt.canonical_before->active_command &&
              attempt.canonical_before->active_command->completed_steps == 1,
          "later watermark step fixture did not retain a real committed prefix");
    check(attempt.session->begin_next(),
          "later watermark head was not retriable after engine allocation failure");
    finish_current(*attempt.session);
    check(attempt.session->progress().sequence == 3 &&
              image(*attempt.session).rows.empty(),
          "later watermark engine retry did not finish the same input");
  }, [](WindowAttempt& attempt) {
    attempt.session->commit();
    drain_output(*attempt.session);
    check(attempt.session->progress().sequence == 3 &&
              image(*attempt.session).rows.empty(),
          "successful later watermark engine step did not finish the input");
  });
}

void resource_limits_preserve_last_committed_window_state() {
  {
    auto options = window_options();
    options.max_labels = 1;
    auto session = QuerySession::create_windowed(unary_plan(), options);
    auto input = batch({window_insert(1, 1, {n(7)}, 0),
                        window_insert(2, 2, {n(8)}, 0)});
    accept(*session, input);
    session->start();
    check(session->begin_next(), "max-label fixture did not begin its seed");
    finish_current(*session);
    const auto before = image(*session);
    const auto canonical = session->window_state();
    const auto stats = queue_stats(*session);
    expect_error([&] { static_cast<void>(session->begin_next()); }, "resource_limit");
    check(image(*session) == before && session->window_state() == canonical &&
              session->progress() == before.progress && queue_stats(*session) == stats &&
              !session->status().input_failed,
          "max-label rejection changed the last committed window command");
  }

  std::size_t byte_limit = 0;
  {
    auto session = QuerySession::create_windowed(unary_plan(), window_options());
    auto input = batch({window_insert(1, 1, {n(7)}, 0)});
    accept(*session, input);
    session->start();
    check(session->begin_next(), "byte-limit calibration did not begin");
    finish_current(*session);
    byte_limit = session->window_state()->metrics.accounted_bytes;
  }
  {
    auto options = window_options();
    options.max_accounted_bytes = byte_limit;
    auto session = QuerySession::create_windowed(unary_plan(), options);
    auto input = batch({window_insert(1, 1, {n(7)}, 0),
                        window_insert(2, 2, {n(8)}, 0)});
    accept(*session, input);
    session->start();
    check(session->begin_next(), "byte-limit fixture did not begin its seed");
    finish_current(*session);
    const auto before = image(*session);
    const auto canonical = session->window_state();
    const auto stats = queue_stats(*session);
    expect_error([&] { static_cast<void>(session->begin_next()); }, "resource_limit");
    check(image(*session) == before && session->window_state() == canonical &&
              session->progress() == before.progress && queue_stats(*session) == stats &&
              !session->status().input_failed,
          "retained-byte rejection changed the last committed window command");
  }

  {
    auto options = window_options();
    options.command_work_limit = 3;
    auto session = QuerySession::create_windowed(unary_plan(), options);
    auto input = batch({window_insert(1, 1, {n(1)}, 0),
                        window_insert(2, 2, {n(2)}, 0),
                        watermark(3, 5)});
    accept(*session, input);
    session->start();
    check(session->begin_next(), "work-limit fixture did not begin its first insert");
    finish_current(*session);
    check(session->begin_next(), "work-limit fixture did not begin its second insert");
    finish_current(*session);
    const auto before = image(*session);
    const auto canonical = session->window_state();
    const auto stats = queue_stats(*session);
    expect_error([&] { static_cast<void>(session->begin_next()); }, "resource_limit");
    check(image(*session) == before && session->window_state() == canonical &&
              session->progress() == before.progress && queue_stats(*session) == stats &&
              !session->status().input_failed,
          "watermark work-limit rejection changed the last committed prefix");
  }
}

void prepared_window_publication_and_ack_are_allocation_free() {
  auto session = QuerySession::create_windowed(unary_plan(), window_options());
  auto input = batch({window_insert(1, 1, {n(7)}, 0)});
  accept(*session, input);
  session->start();
  check(session->begin_next(), "no-allocation physical window step did not begin");
  prepare_current(*session);
  allocation_count = 0;
  {
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    session->commit();
  }
  const auto publication_allocations = allocation_count;
  check(publication_allocations == 0,
        "prepared physical engine/window publication or source acknowledgement allocated");
  const auto state = session->window_state();
  check(state && state->physical_sequence == 1 &&
            state->completed_command_sequence == 1 &&
            session->progress().sequence == 1 &&
            session->status().queue->events == 0 &&
            image(*session).rows == std::vector<Row>{{n(7)}},
        "no-allocation publication did not atomically commit engine, window, and source state");
}

struct CleanupAttempt {
  QuerySession::Owner session;
  std::optional<SignedResult> returned;
};

CleanupAttempt prepared_window_cleanup_attempt() {
  auto session = QuerySession::create_windowed(unary_plan(), window_options());
  auto input = batch({window_insert(1, 1, {n(7)}, 0),
                      window_insert(2, 2, {n(8)}, 0),
                      watermark(3, 5),
                      window_insert(4, 3, {n(9)}, 5)});
  accept(*session, input);
  session->start();
  check(session->begin_next(), "cleanup fixture did not begin its retained insert");
  prepare_current(*session);
  session->commit();
  CleanupAttempt attempt;
  attempt.session = std::move(session);
  attempt.returned = attempt.session->next_output();
  check(attempt.returned && attempt.returned->tuple.values() == Row{n(7)},
        "cleanup fixture did not retain its returned value");
  check(attempt.session->begin_next(), "cleanup fixture did not prepare its queued tail");
  return attempt;
}

void stop_drop_and_final_owner_cleanup_allocate_nothing() {
  {
    auto attempt = prepared_window_cleanup_attempt();
    allocation_count = 0;
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      attempt.session->stop();
      attempt.session->drop();
    }
    const auto cleanup_allocations = allocation_count;
    check(cleanup_allocations == 0 && attempt.returned &&
              attempt.returned->tuple.values() == Row{n(7)} &&
              attempt.session->status().state == SessionState::dropped,
          "stop/drop allocated or invalidated a value returned before cleanup");
  }
  {
    auto attempt = prepared_window_cleanup_attempt();
    allocation_count = 0;
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      attempt.session.reset();
    }
    const auto destruction_allocations = allocation_count;
    check(destruction_allocations == 0 && attempt.returned &&
              attempt.returned->tuple.values() == Row{n(7)},
          "final-owner cleanup allocated or invalidated its returned value");
  }
}

void partial_watermark_stop_releases_prepared_tail_without_allocation() {
  const auto returned = Row{n(1)};
  // The first committed insert output is retained independently of the session.
  auto session = QuerySession::create_windowed(unary_plan(), window_options());
  auto input = batch({window_insert(1, 1, {n(1)}, 0),
                      window_insert(2, 2, {n(2)}, 0),
                      watermark(3, 5),
                      window_insert(4, 3, {n(3)}, 5)});
  accept(*session, input);
  session->start();
  check(session->begin_next(), "partial-stop fixture did not begin insert one");
  prepare_current(*session);
  session->commit();
  auto saved = session->next_output();
  check(saved && saved->tuple.values() == returned,
        "partial-stop fixture did not obtain an owning result");
  check(session->begin_next(), "partial-stop fixture did not begin insert two");
  finish_current(*session);
  check(session->begin_next(), "partial-stop fixture did not begin watermark");
  finish_current(*session);
  check(session->begin_next(), "partial-stop fixture did not prepare the next expiration");
  allocation_count = 0;
  {
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    session->stop();
  }
  const auto partial_stop_allocations = allocation_count;
  check(partial_stop_allocations == 0 &&
            session->status().state == SessionState::stopped &&
            session->progress().sequence == 2 &&
            image(*session).rows == std::vector<Row>{{n(2)}} && saved &&
            saved->tuple.values() == returned,
        "stop changed a committed watermark prefix or released an owned result");
  const auto state = session->window_state();
  check(state && state->active_command &&
            state->active_command->sequence == 3 &&
            state->active_command->completed_steps == 1 &&
            state->active_command->total_steps == 2 &&
            state->active_command->expiration_labels.empty() &&
            state->labels.size() == 1 && state->labels.front().label == 2,
        "stop did not release partial watermark expansion while retaining its committed prefix");
  allocation_count = 0;
  {
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    session->drop();
    session.reset();
  }
  const auto partial_drop_allocations = allocation_count;
  check(partial_drop_allocations == 0 && saved && saved->tuple.values() == returned,
        "drop/final-owner cleanup of partial watermark state allocated or lost returned data");
}

}  // namespace

int main() {
  try {
    typed_session_construction_unwinds_cleanly();
    queue_admission_is_transactional_and_retriable();
    new_source_peek_node_allocation_is_retriable();
    self_join_pending_epoch_begin_and_step_failures_retry();
    window_new_label_and_count_nodes_rollback();
    duplicate_row_metadata_prepare_and_commit();
    watermark_preflight_and_first_step_failures_retry();
    later_watermark_step_failure_preserves_real_prefix_and_retries();
    resource_limits_preserve_last_committed_window_state();
    prepared_window_publication_and_ack_are_allocation_free();
    stop_drop_and_final_owner_cleanup_allocate_nothing();
    partial_watermark_stop_releases_prepared_tail_without_allocation();
  } catch (const std::exception& failure) {
    std::cerr << "batch/window allocation exception test failed: "
              << failure.what() << '\n';
    return 1;
  }
  return 0;
}
