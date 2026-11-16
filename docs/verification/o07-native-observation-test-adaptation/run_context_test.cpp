#include "crown/api/error.hpp"
#include "crown/io/batch.hpp"
#include "crown/io/ingest.hpp"
#include "crown/io/run_context.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/delta.hpp"
#include "crown/runtime/observation.hpp"
#include "crown/runtime/session.hpp"
#include "crown/runtime/window.hpp"
#include "evaluator.hpp"
#include <nlohmann/json.hpp>

#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <memory>
#include <new>
#include <optional>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

namespace allocation_probe {
constexpr std::size_t no_failure = std::numeric_limits<std::size_t>::max();
std::atomic<bool> active{false};
std::atomic<std::size_t> count{0};
std::atomic<std::size_t> fail_at{no_failure};
std::atomic<std::size_t> failures{0};
std::atomic<bool> injected{false};

void note() {
  if (!active.load(std::memory_order_relaxed)) return;
  const auto index = count.fetch_add(1, std::memory_order_relaxed);
  if (index >= fail_at.load(std::memory_order_relaxed)) {
    failures.fetch_add(1, std::memory_order_relaxed);
    injected.store(true, std::memory_order_relaxed);
    throw std::bad_alloc{};
  }
}

void* allocate(std::size_t bytes) {
  note();
  if (void* result = std::malloc(bytes == 0 ? 1 : bytes)) return result;
  throw std::bad_alloc{};
}

void* allocate_aligned(std::size_t bytes, std::size_t alignment) {
  note();
  void* result = nullptr;
  if (posix_memalign(&result, alignment, bytes == 0 ? alignment : bytes) == 0)
    return result;
  throw std::bad_alloc{};
}

struct Measurement {
  std::size_t allocations = 0;
  std::size_t injected_failures = 0;
  bool injected = false;
};

template <class Action>
void measure(Action&& action, std::size_t fail_index, Measurement& result) {
  count.store(0, std::memory_order_relaxed);
  failures.store(0, std::memory_order_relaxed);
  injected.store(false, std::memory_order_relaxed);
  fail_at.store(fail_index, std::memory_order_relaxed);
  active.store(true, std::memory_order_relaxed);
  try {
    std::forward<Action>(action)();
  } catch (...) {
    active.store(false, std::memory_order_relaxed);
    result = {count.load(std::memory_order_relaxed),
              failures.load(std::memory_order_relaxed),
              injected.load(std::memory_order_relaxed)};
    throw;
  }
  active.store(false, std::memory_order_relaxed);
  result = {count.load(std::memory_order_relaxed),
            failures.load(std::memory_order_relaxed),
            injected.load(std::memory_order_relaxed)};
}

void disarm() noexcept {
  active.store(false, std::memory_order_relaxed);
  fail_at.store(no_failure, std::memory_order_relaxed);
  failures.store(0, std::memory_order_relaxed);
  injected.store(false, std::memory_order_relaxed);
}
}  // namespace allocation_probe

void* operator new(std::size_t bytes) { return allocation_probe::allocate(bytes); }
void* operator new[](std::size_t bytes) { return allocation_probe::allocate(bytes); }
void* operator new(std::size_t bytes, std::align_val_t alignment) {
  return allocation_probe::allocate_aligned(bytes, static_cast<std::size_t>(alignment));
}
void* operator new[](std::size_t bytes, std::align_val_t alignment) {
  return allocation_probe::allocate_aligned(bytes, static_cast<std::size_t>(alignment));
}
void operator delete(void* pointer) noexcept { std::free(pointer); }
void operator delete[](void* pointer) noexcept { std::free(pointer); }
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }
void operator delete(void* pointer, std::align_val_t) noexcept { std::free(pointer); }
void operator delete[](void* pointer, std::align_val_t) noexcept { std::free(pointer); }
void operator delete(void* pointer, std::size_t, std::align_val_t) noexcept {
  std::free(pointer);
}
void operator delete[](void* pointer, std::size_t, std::align_val_t) noexcept {
  std::free(pointer);
}

namespace {
using namespace crown;
using namespace crown::runtime;
using Json = nlohmann::json;

std::uint64_t optional_clock_reads = 0;
std::uint64_t fake_clock() noexcept { return ++optional_clock_reads; }

void check(bool condition, std::string_view message) {
  if (!condition) throw std::runtime_error(std::string(message));
}

template <class Action>
void expect_error(std::string_view code, Action&& action, std::string_view message) {
  bool caught = false;
  try {
    std::forward<Action>(action)();
  } catch (const Error& error) {
    caught = true;
    check(error.code() == code, message);
  }
  check(caught, message);
}

Value integer(std::int64_t value) { return Value{value}; }
Row row(std::int64_t value) { return Row{integer(value)}; }
Row edge(std::int64_t x, std::int64_t y) { return Row{integer(x), integer(y)}; }

struct QFixture {
  Catalog catalog{1, {
      {"R", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}},
      {"S", {{"y", ScalarType::int64}}},
  }};
  Query query{
      {{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"R", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"S", TableId{1}, {VariableId{1}}}},
      {{VariableId{0}, "x"}}, false,
  };
  PhysicalPlan plan;
  Database initial;

  QFixture()
      : plan(planner::lower_tree(catalog, query, FreeConnexTree{
            NodeId{0},
            {{"R", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{1}}, 0, {}},
             {"S", NodeKind::native, {VariableId{1}}, {}, 1, {}}},
            {}, {},
        })) {
    initial.tables.resize(2);
    initial.tables[0].insert(edge(7, 9));
  }

  [[nodiscard]] Database with_s() const {
    auto result = initial;
    result.tables[1].insert(row(9));
    return result;
  }

  [[nodiscard]] Database two_roots() const {
    auto result = initial;
    result.tables[0].insert(edge(8, 9));
    return result;
  }
};

ObservationOptions observation_options(ObservationMode mode) {
  ObservationOptions result;
  result.mode = mode;
  result.trace_capacity = 41;
  result.sample_period = 1;
  result.sample_offset = 0;
  result.trace_timings = true;
  return result;
}

DeltaOptions exact_delta_options(ObservationMode mode = ObservationMode::counters) {
  DeltaOptions result;
  result.physical.support.work_limit = std::uint64_t{7103};
  result.physical.support.support_limit = 9209;
  result.physical.support.order = PropagationOrder::lifo;
  result.physical.support.capture_transitions = false;
  result.physical.support.observation = observation_options(mode);
  result.physical.work_limit = std::uint64_t{11003};
  result.physical.derivation_limit = 13007;
  result.mode = DeltaMode::delta;
  result.view = ResultView::sql;
  result.live_maintenance = LiveMaintenance::eager;
  result.completion = DeltaCompletion::automatic;
  result.work_limit = std::uint64_t{17011};
  result.cursor.work_limit = std::uint64_t{19001};
  result.epoch_view.work_limit = std::uint64_t{23003};
  result.spool_row_limit = 251;
  result.spool_byte_limit = 28001;
  return result;
}

bool same_observation_options(const ObservationOptions& a, const ObservationOptions& b) {
  return a.mode == b.mode && a.trace_capacity == b.trace_capacity &&
      a.sample_period == b.sample_period && a.sample_offset == b.sample_offset &&
      a.trace_timings == b.trace_timings;
}

bool same_delta_options(const DeltaOptions& a, const DeltaOptions& b) {
  return a.physical.support.work_limit == b.physical.support.work_limit &&
      a.physical.support.support_limit == b.physical.support.support_limit &&
      a.physical.support.order == b.physical.support.order &&
      a.physical.support.capture_transitions == b.physical.support.capture_transitions &&
      same_observation_options(a.physical.support.observation,
                               b.physical.support.observation) &&
      a.physical.work_limit == b.physical.work_limit &&
      a.physical.derivation_limit == b.physical.derivation_limit &&
      a.mode == b.mode && a.view == b.view &&
      a.live_maintenance == b.live_maintenance && a.completion == b.completion &&
      a.work_limit == b.work_limit && a.cursor.work_limit == b.cursor.work_limit &&
      a.epoch_view.work_limit == b.epoch_view.work_limit &&
      a.spool_row_limit == b.spool_row_limit &&
      a.spool_byte_limit == b.spool_byte_limit;
}

bool same_input_limits(const io::InputLimits& a, const io::InputLimits& b) {
  return a.record_bytes == b.record_bytes && a.field_bytes == b.field_bytes &&
      a.columns == b.columns && a.source_bytes == b.source_bytes &&
      a.sources == b.sources && a.total_bytes == b.total_bytes &&
      a.records == b.records;
}

bool same_input_options(const io::InputOptions& a, const io::InputOptions& b) {
  return a.format == b.format && same_input_limits(a.limits, b.limits) &&
      a.table == b.table && a.delimiter == b.delimiter && a.header == b.header &&
      a.csv_operation == b.csv_operation && a.relation_tokens == b.relation_tokens &&
      a.null_token == b.null_token && a.source == b.source &&
      a.byte_offset == b.byte_offset;
}

bool same_snapshot_limits(const SnapshotLimits& a, const SnapshotLimits& b) {
  return a.rows == b.rows && a.bytes == b.bytes &&
      a.cursor.work_limit == b.cursor.work_limit;
}

bool same_build(const std::optional<BuildOptions>& a,
                const std::optional<BuildOptions>& b) {
  if (a.has_value() != b.has_value()) return false;
  if (!a) return true;
  return a->method == b->method && a->work_limit == b->work_limit;
}

void check_initialization(const InitializationContext& actual,
                          InitializationRoute route,
                          std::optional<BuildOptions> applied,
                          std::string_view label) {
  check(actual.route == route && same_build(actual.applied_build, applied), label);
}

Relation drain(SupportRuntime::ResultCursor cursor) {
  Relation rows;
  while (auto tuple = cursor.next())
    check(rows.insert(tuple->values()).second, "Q result cursor emitted a duplicate set row");
  return rows;
}

Relation evaluate(const QFixture& fixture, const Database& database) {
  return reference::evaluate(fixture.catalog, fixture.query, database);
}

DeltaOptions mode_options(ObservationMode mode) {
  auto result = exact_delta_options(mode);
  result.physical.support.capture_transitions = false;
  return result;
}

DeltaRuntime make_delta_runtime(const QFixture& fixture, const Database& initial,
                                DeltaOptions options = mode_options(ObservationMode::counters)) {
  return DeltaRuntime::initialize(fixture.plan, initial, options);
}

void check_output(const ObservationSummary& summary, const OutputDisposition& expected,
                  std::string_view message) {
  check(summary.output.has_value(), message);
  const auto& actual = *summary.output;
  check(actual.discard_drain_requested == expected.discard_drain_requested &&
        actual.completion_drain_invoked == expected.completion_drain_invoked &&
        actual.retention_disabled == expected.retention_disabled &&
        actual.prepared == expected.prepared && actual.published == expected.published &&
        actual.released == expected.released && actual.transferred == expected.transferred &&
        actual.serialization_invoked == expected.serialization_invoked &&
        actual.sink_invoked == expected.sink_invoked &&
        actual.unread_discarded == expected.unread_discarded, message);
}

OutputDisposition disposition(bool discard_requested, bool completion_drain,
                              bool retention_disabled, bool prepared, bool published,
                              bool released, bool transferred, bool serialization,
                              bool sink, bool unread_discarded) {
  return {discard_requested, completion_drain, retention_disabled, prepared,
          published, released, transferred, serialization, sink, unread_discarded};
}

void check_metric(const ObservationSummary& summary, MetricId id,
                  std::uint64_t value, std::string_view message) {
  const auto& metric = summary.metric(id);
  check(metric.availability == MetricAvailability::available && metric.value == value,
        message);
}

void check_context(const std::shared_ptr<const SessionRunContext>& context,
                  SessionInputKind kind, const io::InputOptions& input,
                  std::optional<io::QueueLimits> queue,
                  std::optional<WindowOptions> window,
                  const SnapshotLimits& snapshot,
                  InitializationRoute route, BuildOptions build,
                  const DeltaOptions& requested) {
  check(context != nullptr, "session run context handle is null");
  check(context->input_kind == kind && same_input_options(context->input, input),
        "session run context input kind/options differ from independent request");
  check(context->queue.has_value() == queue.has_value(),
        "session run context queue applicability differs from input kind");
  if (queue)
    check(context->queue->batches == queue->batches &&
          context->queue->events == queue->events &&
          context->queue->bytes == queue->bytes,
          "session run context queue limits differ from independent request");
  check(context->window.has_value() == window.has_value(),
        "session run context window applicability differs from input kind");
  if (window) {
    const auto& actual = *context->window;
    check(actual.managed_tables == window->managed_tables && actual.width == window->width &&
          actual.fifo == window->fifo && actual.max_labels == window->max_labels &&
          actual.max_accounted_bytes == window->max_accounted_bytes &&
          actual.command_work_limit == window->command_work_limit,
          "session run context window options differ from independent request");
  }
  check(same_snapshot_limits(context->snapshot, snapshot),
        "session run context snapshot limits differ from independent request");
  check_initialization(context->initialization, route, build,
                       "session run context initialization route/build options differ");
  check(same_delta_options(context->requested_delta, requested) &&
        context->resolved_mode == DeltaMode::delta &&
        context->resolved_completion == DeltaCompletion::anchored,
        "session run context requested/resolved delta options differ");
}

void check_json_delta(const Json& actual, const DeltaOptions& expected) {
  check(actual["requested_mode"] == "delta" &&
        actual["requested_completion"] == "automatic" &&
        actual["live_maintenance"] == "eager" && actual["view"] == "sql",
        "exported delta enum fields differ from exact requested options");
  const auto check_optional = [&](const char* key,
                                  const std::optional<std::uint64_t>& value) {
    if (value) check(actual[key] == *value, "exported work ceiling differs from exact request");
    else check(actual[key].is_null(), "exported absent work ceiling was not null");
  };
  check_optional("work_limit", expected.work_limit);
  check_optional("cursor_work_limit", expected.cursor.work_limit);
  check_optional("epoch_view_work_limit", expected.epoch_view.work_limit);
  check(actual["spool_rows"] == expected.spool_row_limit &&
        actual["spool_accounted_bytes"] == expected.spool_byte_limit,
        "exported spool ceilings differ from exact request");
  check_optional("physical_work_limit", expected.physical.work_limit);
  check(actual["derivation_limit"] == expected.physical.derivation_limit,
        "exported derivation limit differs from exact request");
  const auto& support = expected.physical.support;
  check_optional("support_work_limit", support.work_limit);
  check(actual["support_limit"] == support.support_limit &&
        actual["propagation_order"] == "lifo" &&
        actual["capture_transitions"] == support.capture_transitions,
        "exported support fields differ from exact request");
  const auto& observation = actual["observation"];
  check(observation["mode"] == "counters" &&
        observation["trace_capacity"] == support.observation.trace_capacity &&
        observation["sample_period"] == support.observation.sample_period &&
        observation["sample_offset"] == support.observation.sample_offset &&
        observation["trace_timings"] == support.observation.trace_timings,
        "exported observation options differ from exact request");
}

void check_json_input(const Json& actual, const io::InputOptions& expected) {
  const auto name = [&]() -> std::string_view {
    switch (expected.format) {
      case io::InputFormat::jsonl: return "jsonl";
      case io::InputFormat::binary: return "binary";
      case io::InputFormat::csv: return "csv";
      case io::InputFormat::legacy_signed: return "legacy_signed";
      case io::InputFormat::legacy_relations: return "legacy_relations";
      case io::InputFormat::legacy_insert_only: return "legacy_insert_only";
      case io::InputFormat::legacy_flags: return "legacy_flags";
      case io::InputFormat::legacy_timestamp_flags: return "legacy_timestamp_flags";
    }
    return "unknown";
  };
  check(actual["format"] == name(), "exported input format differs from run context");
  if (expected.table) check(actual["table"] == expected.table->value,
                            "exported input table differs from run context");
  else check(actual["table"].is_null(), "exported missing input table was not null");
  check(actual["delimiter_byte"] == static_cast<unsigned char>(expected.delimiter) &&
        actual["header"] == expected.header &&
        actual["csv_operation"] ==
          (expected.csv_operation == SetOperation::insert ? "insert" : "erase") &&
        actual["byte_offset"] == expected.byte_offset,
        "exported CSV/header/offset input fields differ from run context");
  check(actual["relation_tokens"].is_array() &&
        actual["relation_tokens"].size() == expected.relation_tokens.size(),
        "exported relation-token map size differs from run context");
  std::size_t index = 0;
  for (const auto& [token, table] : expected.relation_tokens) {
    check(actual["relation_tokens"][index]["token"] == token &&
          actual["relation_tokens"][index]["table"] == table.value,
          "exported relation-token map entry differs from run context");
    ++index;
  }
  if (expected.null_token) check(actual["null_token"] == *expected.null_token,
                                  "exported null token differs from run context");
  else check(actual["null_token"].is_null(), "exported missing null token was not null");
  if (expected.source) check(actual["source"] == *expected.source,
                              "exported input source differs from run context");
  else check(actual["source"].is_null(), "exported missing input source was not null");
  const auto& limits = actual["limits"];
  check(limits["record_bytes"] == expected.limits.record_bytes &&
        limits["field_bytes"] == expected.limits.field_bytes &&
        limits["columns"] == expected.limits.columns &&
        limits["source_bytes"] == expected.limits.source_bytes &&
        limits["sources"] == expected.limits.sources,
        "exported input limit fields differ from run context");
  if (expected.limits.total_bytes)
    check(limits["total_bytes"] == *expected.limits.total_bytes,
          "exported total-byte limit differs from run context");
  else check(limits["total_bytes"].is_null(), "missing total-byte limit was not null");
  if (expected.limits.records)
    check(limits["records"] == *expected.limits.records,
          "exported record limit differs from run context");
  else check(limits["records"].is_null(), "missing record limit was not null");
}

void verify_session_export(const std::string& encoded,
                           const SessionRunContext& expected,
                           std::string_view input_kind,
                           std::string_view wire_scope) {
  const auto parsed = Json::parse(encoded);
  check(parsed["format"] == "crown_run_context" && parsed["version"] == 1 &&
        parsed["missing_identity"] == "null_not_inferred",
        "run-context export header differs from version-1 literal");
  const auto& session = parsed["session"];
  check(session["provenance"] == "recorded_session_admission" &&
        session["input_kind"] == input_kind &&
        session["wire_format_scope"] == wire_scope,
        "exported session provenance/input applicability differs from expected kind");
  check_json_input(session["input_options"], expected.input);
  if (expected.queue) {
    check(session["queue"]["batches"] == expected.queue->batches &&
          session["queue"]["events"] == expected.queue->events &&
          session["queue"]["accounted_bytes"] == expected.queue->bytes,
          "exported queue limits differ from typed session context");
  } else check(session["queue"].is_null(), "stream session incorrectly exported a queue");
  if (expected.window) {
    const auto& window = session["window"];
    check(window["managed_tables"].size() == expected.window->managed_tables.size(),
          "exported managed-table list size differs from window context");
    for (std::size_t i = 0; i < expected.window->managed_tables.size(); ++i)
      check(window["managed_tables"][i] == expected.window->managed_tables[i].value,
            "exported managed-table ID differs from window context");
    check(window["width"] == expected.window->width &&
          window["fifo"] == (expected.window->fifo == WindowFifoPolicy::global
              ? "global" : "per_relation") &&
          window["max_labels"] == expected.window->max_labels &&
          window["max_accounted_bytes"] == expected.window->max_accounted_bytes &&
          window["command_work_limit"] == expected.window->command_work_limit,
          "exported window options differ from run context");
  } else check(session["window"].is_null(), "non-window session exported window options");
  check(session["snapshot"]["rows"] == expected.snapshot.rows &&
        session["snapshot"]["accounted_bytes"] == expected.snapshot.bytes,
        "exported snapshot ceilings differ from run context");
  if (expected.snapshot.cursor.work_limit)
    check(session["snapshot"]["cursor_work_limit"] == *expected.snapshot.cursor.work_limit,
          "exported snapshot cursor ceiling differs from context");
  else check(session["snapshot"]["cursor_work_limit"].is_null(),
             "absent snapshot cursor ceiling was not null");
  check(session["initialization"]["route"] == "initialized_database" &&
        session["initialization"]["applied_build"]["method"] ==
          (expected.initialization.applied_build->method == BuildMethod::direct
              ? "direct" : "insertion_replay") &&
        session["initialization"]["applied_build"]["work_limit"] ==
          *expected.initialization.applied_build->work_limit,
        "exported session initialization route/build options differ");
  check_json_delta(session["requested_delta"], expected.requested_delta);
  check(session["resolved_mode"] == "delta" &&
        session["resolved_completion"] == "anchored",
        "exported resolved mode/completion differ from literal eager/automatic resolution");
}

void scenario_initialization_routes_and_build_options() {
  QFixture fixture;
  auto options = exact_delta_options(ObservationMode::counters);
  options.mode = DeltaMode::maintenance;
  options.physical.support.capture_transitions = false;
  Database empty;
  empty.tables.resize(2);

  DeltaRuntime empty_constructor(fixture.plan, options);
  check_initialization(empty_constructor.initialization_context(),
      InitializationRoute::empty_constructor, std::nullopt,
      "empty constructor falsely claimed an applied BuildOptions value");

  BuildOptions empty_direct{BuildMethod::direct, std::uint64_t{13001}};
  BuildOptions empty_replay{BuildMethod::insertion_replay, std::uint64_t{17009}};
  auto direct_empty = DeltaRuntime::initialize(fixture.plan, empty, options, empty_direct);
  auto replay_empty = DeltaRuntime::initialize(fixture.plan, empty, options, empty_replay);
  check_initialization(direct_empty.initialization_context(),
      InitializationRoute::initialized_database, empty_direct,
      "empty direct database initialization lost its exact BuildOptions");
  check_initialization(replay_empty.initialization_context(),
      InitializationRoute::initialized_database, empty_replay,
      "empty insertion-replay database initialization lost its exact BuildOptions");
  check(evaluate(fixture, direct_empty.snapshot().physical) ==
            evaluate(fixture, replay_empty.snapshot().physical) &&
        direct_empty.snapshot().physical.tables == empty.tables &&
        replay_empty.snapshot().physical.tables == empty.tables,
        "empty direct and replay initialization produced different literal state");

  BuildOptions populated_direct{BuildMethod::direct, std::uint64_t{23011}};
  BuildOptions populated_replay{BuildMethod::insertion_replay, std::uint64_t{29009}};
  auto direct = DeltaRuntime::initialize(fixture.plan, fixture.initial, options,
                                         populated_direct);
  auto replay = DeltaRuntime::initialize(fixture.plan, fixture.initial, options,
                                         populated_replay);
  check_initialization(direct.initialization_context(),
      InitializationRoute::initialized_database, populated_direct,
      "populated direct initialization lost its exact BuildOptions");
  check_initialization(replay.initialization_context(),
      InitializationRoute::initialized_database, populated_replay,
      "populated replay initialization lost its exact BuildOptions");
  check(direct.snapshot().physical.tables == fixture.initial.tables &&
        replay.snapshot().physical.tables == fixture.initial.tables &&
        evaluate(fixture, direct.snapshot().physical) ==
          evaluate(fixture, replay.snapshot().physical),
        "populated direct/replay routes differ from independent Q state");

  BuildOptions rebuilt_build{BuildMethod::insertion_replay, std::uint64_t{31013}};
  const auto direct_owner = direct.owner().value;
  auto rebuilt = direct.rebuilt(rebuilt_build);
  check_initialization(rebuilt.initialization_context(),
      InitializationRoute::rebuilt_snapshot, rebuilt_build,
      "rebuilt runtime lost its new route or exact rebuild BuildOptions");
  check(rebuilt.owner().value != direct_owner &&
        rebuilt.snapshot().physical.tables == fixture.initial.tables &&
        evaluate(fixture, rebuilt.snapshot().physical) ==
          evaluate(fixture, fixture.initial),
        "rebuilt runtime changed owner/source identity or independent result");

  PhysicalRuntime physical_empty(fixture.plan, options.physical);
  check_initialization(physical_empty.initialization_context(),
      InitializationRoute::empty_constructor, std::nullopt,
      "direct PhysicalRuntime empty constructor claimed an applied build");
  auto physical_initialized = PhysicalRuntime::initialize(
      fixture.plan, empty, options.physical, empty_replay);
  check_initialization(physical_initialized.initialization_context(),
      InitializationRoute::initialized_database, empty_replay,
      "PhysicalRuntime did not preserve its initialized-database BuildOptions");
  auto physical_rebuilt = physical_initialized.rebuilt(rebuilt_build);
  check_initialization(physical_rebuilt.initialization_context(),
      InitializationRoute::rebuilt_snapshot, rebuilt_build,
      "PhysicalRuntime rebuild route/options differ from exact request");

  BuildOptions impossible{BuildMethod::direct, std::uint64_t{0}};
  expect_error("resource_limit", [&] {
    static_cast<void>(DeltaRuntime::initialize(fixture.plan, fixture.initial,
                                               options, impossible));
  }, "zero work limit should reject an unsuccessful build without a context artifact");
  check(fixture.initial.tables[0].contains(edge(7, 9)) &&
        fixture.initial.tables[1].empty(),
        "failed initialization modified the caller-owned literal database");
}

io::InputLimits custom_limits() {
  io::InputLimits limits;
  limits.record_bytes = 4096;
  limits.field_bytes = 512;
  limits.columns = 13;
  limits.source_bytes = 29;
  limits.sources = 7;
  limits.total_bytes = std::uint64_t{9011};
  limits.records = std::uint64_t{31};
  return limits;
}

SnapshotLimits custom_snapshot() {
  SnapshotLimits result;
  result.rows = 37;
  result.bytes = 8009;
  result.cursor.work_limit = std::uint64_t{401};
  return result;
}

io::QueueLimits custom_queue(std::size_t salt) {
  return {5 + salt, 17 + salt, 12001 + salt};
}

std::shared_ptr<const DeclaredBenchmarkContext> session_label() {
  BenchmarkLabels labels;
  labels.run = std::string("session\0run", 11);
  labels.input_adapter = std::string{};
  labels.output_codec = std::nullopt;
  labels.sink = std::string{"typed-sink"};
  return std::make_shared<const DeclaredBenchmarkContext>(std::move(labels));
}

void check_session_survived_drop(
    std::shared_ptr<const SessionRunContext> saved,
    SessionInputKind kind, const io::InputOptions& input,
    std::optional<io::QueueLimits> queue,
    std::optional<WindowOptions> window, const SnapshotLimits& snapshot,
    BuildOptions build, const DeltaOptions& requested,
    const ObservationSnapshot& after_drop,
    std::string_view input_kind_name, std::string_view wire_scope) {
  check_context(saved, kind, input, queue, window, snapshot,
                InitializationRoute::initialized_database, build, requested);
  check(after_drop.session_attached && after_drop.session_context == saved &&
        !after_drop.last,
        "session drop did not retain the same context handle or fabricated history");
  const auto encoded = io::write_run_context_json(after_drop);
  verify_session_export(encoded, *saved, input_kind_name, wire_scope);
  check(io::write_run_context_json(after_drop, encoded.size()) == encoded,
        "exact encoded-byte limit rejected a complete run-context artifact");
  expect_error("resource_limit", [&] {
    static_cast<void>(io::write_run_context_json(after_drop, encoded.size() - 1));
  }, "one-byte-short encoded limit must reject the whole artifact");
}

void scenario_session_context_owned_stream_typed_window_and_admission_oom() {
  QFixture fixture;
  auto requested = exact_delta_options(ObservationMode::counters);
  requested.mode = DeltaMode::delta;
  requested.physical.support.capture_transitions = false;
  const auto snapshot = custom_snapshot();

  io::InputOptions stream_input;
  stream_input.format = io::InputFormat::csv;
  stream_input.limits = custom_limits();
  stream_input.table = TableId{1};
  stream_input.delimiter = '|';
  stream_input.header = true;
  stream_input.csv_operation = SetOperation::insert;
  stream_input.source = std::string{"source-stream"};
  stream_input.byte_offset = 73;
  BuildOptions stream_build{BuildMethod::direct, std::uint64_t{41003}};
  SessionOptions stream_options;
  stream_options.input = stream_input;
  stream_options.delta = requested;
  stream_options.snapshot = snapshot;
  stream_options.declared_benchmark = session_label();
  std::shared_ptr<const SessionRunContext> stream_context;
  ObservationSnapshot stream_after_drop;
  {
    std::unique_ptr<std::istream> stream =
        std::make_unique<std::istringstream>("y\n9\n");
    auto session = QuerySession::create(fixture.plan, fixture.initial,
        std::move(stream), stream_options, stream_build);
    stream_context = session->run_context();
    check_context(stream_context, SessionInputKind::owned_stream, stream_input,
                  std::nullopt, std::nullopt, snapshot,
                  InitializationRoute::initialized_database, stream_build, requested);
    session->stop();
    session->drop();
    stream_after_drop = session->observations();
  }
  check_session_survived_drop(stream_context, SessionInputKind::owned_stream,
      stream_input, std::nullopt, std::nullopt, snapshot, stream_build, requested,
      stream_after_drop, "owned_stream", "applied_to_owned_stream");

  auto typed_input = io::InputOptions{};
  typed_input.limits = custom_limits();
  typed_input.limits.total_bytes.reset(); // Typed queues use queue/batch byte limits.
  const auto physical_queue = custom_queue(2);
  BuildOptions typed_build{BuildMethod::insertion_replay, std::uint64_t{47017}};
  SessionOptions typed_options;
  typed_options.input = typed_input;
  typed_options.delta = requested;
  typed_options.snapshot = snapshot;
  typed_options.declared_benchmark = session_label();
  std::shared_ptr<const SessionRunContext> typed_context;
  ObservationSnapshot typed_after_drop;
  {
    auto session = QuerySession::create_typed(fixture.plan, fixture.initial,
        physical_queue, typed_options, typed_build);
    typed_context = session->run_context();
    check_context(typed_context, SessionInputKind::typed_physical, typed_input,
                  physical_queue, std::nullopt, snapshot,
                  InitializationRoute::initialized_database, typed_build, requested);
    session->stop();
    session->drop();
    typed_after_drop = session->observations();
  }
  check_session_survived_drop(typed_context, SessionInputKind::typed_physical,
      typed_input, physical_queue, std::nullopt, snapshot, typed_build, requested,
      typed_after_drop, "typed_physical", "not_applicable_typed_input");

  auto window_options = WindowOptions{};
  window_options.managed_tables = {TableId{1}};
  window_options.width = 6;
  window_options.fifo = WindowFifoPolicy::per_relation;
  window_options.max_labels = 43;
  window_options.max_accounted_bytes = 9901;
  window_options.command_work_limit = 3701;
  const auto window_queue = custom_queue(4);
  BuildOptions window_build{BuildMethod::direct, std::uint64_t{51001}};
  SessionOptions window_session_options;
  window_session_options.input = typed_input;
  window_session_options.delta = requested;
  window_session_options.snapshot = snapshot;
  window_session_options.declared_benchmark = session_label();
  std::shared_ptr<const SessionRunContext> window_context;
  ObservationSnapshot window_after_drop;
  {
    auto session = QuerySession::create_windowed(fixture.plan, fixture.initial,
        window_options, window_queue, window_session_options, window_build);
    window_context = session->run_context();
    check_context(window_context, SessionInputKind::typed_window, typed_input,
                  window_queue, window_options, snapshot,
                  InitializationRoute::initialized_database, window_build, requested);
    session->stop();
    session->drop();
    window_after_drop = session->observations();
  }
  check_session_survived_drop(window_context, SessionInputKind::typed_window,
      typed_input, window_queue, window_options, snapshot, window_build, requested,
      window_after_drop, "typed_window", "not_applicable_typed_input");

  // Admission intentionally allocates its owned immutable metadata once. Sweep
  // every observed operator-new position under persistent failure to ensure a
  // partially created run context is never published; this is not a no-alloc
  // assertion about session construction.
  auto oom_options = SessionOptions{};
  oom_options.input.limits = custom_limits();
  oom_options.input.limits.total_bytes.reset(); // Typed queues use queue/batch byte limits.
  oom_options.delta = requested;
  oom_options.delta.mode = DeltaMode::maintenance;
  oom_options.snapshot = snapshot;
  const auto oom_queue = custom_queue(1);
  const auto expected_oom_delta = oom_options.delta;
  const auto expected_oom_input = oom_options.input;
  allocation_probe::Measurement calibration;
  std::unique_ptr<QuerySession> successful;
  allocation_probe::measure([&] {
    successful = QuerySession::create_typed(fixture.plan, oom_queue, oom_options);
  }, allocation_probe::no_failure, calibration);
  check(calibration.allocations > 0 && !calibration.injected,
        "session admission calibration did not observe its documented allocations");
  successful->drop();
  successful.reset();

  std::size_t injected_count = 0;
  for (std::size_t fail_index = 0; fail_index < calibration.allocations; ++fail_index) {
    std::unique_ptr<QuerySession> failed_session;
    allocation_probe::Measurement failure;
    bool caught = false;
    try {
      allocation_probe::measure([&] {
        failed_session = QuerySession::create_typed(fixture.plan, oom_queue, oom_options);
      }, fail_index, failure);
    } catch (const std::bad_alloc&) {
      caught = true;
    }
    check(caught && failure.injected && failure.injected_failures >= 1 &&
          failure.allocations >= fail_index + 1 && !failed_session,
          "persistent session-admission OOM published a partial session/context");
    injected_count += failure.injected_failures;
    allocation_probe::disarm();
    check(fixture.initial.tables[0].contains(edge(7, 9)) &&
          fixture.initial.tables[1].empty() &&
          same_delta_options(oom_options.delta, expected_oom_delta) &&
          same_input_options(oom_options.input, expected_oom_input),
          "session-admission OOM changed caller-owned query input/options");
  }
  std::cout << "  session admission allocated " << calibration.allocations
            << " times; persistent OOM sweep observed " << injected_count
            << " injected bad_alloc requests\n";
  allocation_probe::disarm();
  auto recovered = QuerySession::create_typed(fixture.plan, oom_queue, oom_options);
  check(recovered->run_context() &&
        recovered->run_context()->initialization.route == InitializationRoute::empty_constructor,
        "successful session creation after persistent OOM sweep lacks a complete context");
  recovered->drop();
}

PhysicalSetUpdate insert_s(std::uint64_t sequence) {
  return {sequence, TableId{1}, SetOperation::insert, row(9)};
}

PhysicalSetUpdate erase_s(std::uint64_t sequence) {
  return {sequence, TableId{1}, SetOperation::erase, row(9)};
}

void scenario_actual_output_disposition_lifecycle() {
  QFixture fixture;

  {
    auto runtime = make_delta_runtime(fixture, fixture.initial);
    auto pending = runtime.begin(insert_s(1));
    pending.start_drain();
    pending.drain();
    auto epoch = pending.commit();
    check(epoch.remaining() == 0 && !epoch.active(),
          "suppressed output unexpectedly retained a committed row");
    const auto observed = runtime.observations();
    check(observed.last && observed.last->outcome == ObservationOutcome::committed,
          "suppressed output attempt was not committed");
    check_output(*observed.last,
        disposition(true, true, true, true, true, true, false, false, false, false),
        "discard drain disposition flags differ from actual suppressed Q output");
    const auto expected = evaluate(fixture, fixture.with_s());
    check(expected == Relation{row(7)} && drain(runtime.results()) == expected,
          "suppressed output changed the independent Q state/result");
  }

  {
    auto runtime = make_delta_runtime(fixture, fixture.initial);
    auto epoch = runtime.apply(insert_s(1));
    check(epoch.remaining() == 1 && epoch.active(),
          "retained Q update did not publish its literal one-row output");
    auto before_transfer = runtime.observations();
    check(before_transfer.last && before_transfer.last->output,
          "retained output attempt lacks disposition state");
    check_output(*before_transfer.last,
        disposition(false, true, false, true, true, false, false, false, false, false),
        "default retention flags differ before transfer");
    const auto record = epoch.next();
    check(record && record->operation == SetOperation::insert &&
          record->tuple.values() == row(7),
          "retained Q output differs from literal insertion of projected row 7");
    const auto after_transfer = runtime.observations();
    check_output(*after_transfer.last,
        disposition(false, true, false, true, true, true, true, false, false, false),
        "successful next() transfer did not mark transfer/release separately");
    check_metric(*after_transfer.last, MetricId::delta_transferred_records, 1,
                 "transferred-record counter differs from one literal row");
    check(evaluate(fixture, fixture.with_s()) == drain(runtime.results()),
          "retained output changed the independent committed Q result");
  }

  {
    const auto already_present = fixture.with_s();
    auto runtime = make_delta_runtime(fixture, already_present);
    auto empty_epoch = runtime.apply(insert_s(1));
    check(empty_epoch.remaining() == 0 && !empty_epoch.active(),
          "duplicate physical insert should publish an empty output epoch");
    const auto observed = runtime.observations();
    check(observed.last && observed.last->outcome == ObservationOutcome::committed,
          "empty duplicate attempt was not retained as a committed attempt");
    check_output(*observed.last,
        disposition(false, true, false, true, true, true, false, false, false, false),
        "empty retained publication was confused with suppressed output");
    check(drain(runtime.results()) == evaluate(fixture, already_present),
          "empty duplicate epoch changed independent Q result");
  }

  {
    const auto two_roots = fixture.two_roots();
    auto runtime = make_delta_runtime(fixture, two_roots);
    auto epoch = runtime.apply(insert_s(1));
    check(epoch.remaining() == 2,
          "two-row R fixture should prepare exactly two independent Q outputs");
    const auto first = epoch.next();
    check(first && first->operation == SetOperation::insert &&
          (first->tuple.values() == row(7) || first->tuple.values() == row(8)) &&
          epoch.remaining() == 1,
          "partial transfer did not move one of the two literal Q outputs");
    const auto partial = runtime.observations();
    check(partial.last.has_value(), "partial transfer attempt summary disappeared");
    check_output(*partial.last,
        disposition(false, true, false, true, true, false, true, false, false, false),
        "partial transfer was confused with final release/discard");
    epoch.discard();
    const auto discarded = runtime.observations();
    check_output(*discarded.last,
        disposition(false, true, false, true, true, true, true, false, false, true),
        "partial transfer followed by discard did not retain both facts");
    check_metric(*discarded.last, MetricId::delta_transferred_records, 1,
                 "partial transfer count differs from literal single row");
    check_metric(*discarded.last, MetricId::delta_discarded_records, 1,
                 "unread discard count differs from literal remaining row");
    auto expected = two_roots;
    expected.tables[1].insert(row(9));
    check(drain(runtime.results()) == evaluate(fixture, expected),
          "partial transfer/discard changed committed reference state");
  }

  {
    auto runtime = make_delta_runtime(fixture, fixture.initial);
    auto pending = runtime.begin(insert_s(1));
    pending.rollback();
    const auto aborted = runtime.observations();
    check(aborted.last && aborted.last->outcome == ObservationOutcome::aborted,
          "explicit rollback did not retain an aborted attempt");
    check_output(*aborted.last,
        disposition(false, false, false, false, false, true, false, false, false, false),
        "rollback output disposition contains a false prepare/publish/transfer claim");
    check(runtime.sequence() == 0 &&
          runtime.snapshot().physical.tables == fixture.initial.tables &&
          drain(runtime.results()) == evaluate(fixture, fixture.initial),
          "aborted output preparation changed physical or independent query state");
  }

  {
    auto runtime = make_delta_runtime(fixture, fixture.initial);
    auto old_empty = runtime.apply(erase_s(1));
    auto old_snapshot = runtime.observations();
    check(old_snapshot.last && old_snapshot.last->sequence == 1,
          "first no-op epoch did not produce a retained summary");
    check_output(*old_snapshot.last,
        disposition(false, true, false, true, true, true, false, false, false, false),
        "old empty publication has incorrect terminal disposition");

    auto current = runtime.apply(insert_s(2));
    check(current.remaining() == 1,
          "second event did not publish its literal Q result after old empty epoch");
    const auto before_late_close = runtime.observations();
    check(before_late_close.last && before_late_close.last->sequence == 2,
          "second attempt did not replace the retained summary");
    check_output(*before_late_close.last,
        disposition(false, true, false, true, true, false, false, false, false, false),
        "current nonempty publication flags differ before transfer");
    old_empty.discard();
    const auto after_late_close = runtime.observations();
    check(after_late_close.last && after_late_close.last->sequence == 2,
          "late close of an old empty epoch replaced a newer summary");
    check_output(*after_late_close.last,
        disposition(false, true, false, true, true, false, false, false, false, false),
        "late close of an old empty epoch rewrote a newer output disposition");
    const auto record = current.next();
    check(record && record->operation == SetOperation::insert &&
          record->tuple.values() == row(7),
          "current event output changed after old empty epoch cleanup");
  }

  {
    auto runtime = make_delta_runtime(fixture, fixture.initial);
    auto pending = runtime.begin(insert_s(1));
    pending.pause();
    check(pending.state() == DeltaState::paused,
          "fixture failed to pause its pending delta attempt");
    pending.drain();
    check(pending.state() == DeltaState::epoch_prepared,
          "completion drain did not resume and prepare the paused attempt");
    auto epoch = pending.commit();
    auto observed = runtime.observations();
    check(observed.last && observed.last->outcome == ObservationOutcome::committed,
          "paused completion drain did not commit its attempt");
    check_output(*observed.last,
        disposition(false, true, false, true, true, false, false, false, false, false),
        "paused completion drain incorrectly disabled output retention");
    epoch.discard();
    observed = runtime.observations();
    check_output(*observed.last,
        disposition(false, true, false, true, true, true, false, false, false, true),
        "discard after paused retained drain did not release unread output");
  }

  {
    auto options = mode_options(ObservationMode::counters);
    options.spool_row_limit = 0;
    auto runtime = make_delta_runtime(fixture, fixture.initial, options);
    expect_error("resource_limit", [&] {
      static_cast<void>(runtime.apply(insert_s(1)));
    }, "zero spool rows should abort the output preparation before publication");
    const auto failed = runtime.observations();
    check(failed.last && failed.last->outcome == ObservationOutcome::aborted,
          "spool-cap failure did not leave an aborted attempt summary");
    check_output(*failed.last,
        disposition(false, true, false, false, false, true, false, false, false, false),
        "spool-cap abort disposition falsely claims prepared/published output");
    check(runtime.sequence() == 0 &&
          runtime.snapshot().physical.tables == fixture.initial.tables &&
          drain(runtime.results()) == evaluate(fixture, fixture.initial),
          "spool-cap output failure did not restore the complete prior Q state");
  }
}

std::shared_ptr<const DeclaredBenchmarkContext> benchmark_context(
    std::optional<std::string> run,
    std::optional<std::string> input_adapter,
    std::optional<std::string> output_codec,
    std::optional<std::string> sink) {
  BenchmarkLabels labels;
  labels.run = std::move(run);
  labels.input_adapter = std::move(input_adapter);
  labels.output_codec = std::move(output_codec);
  labels.sink = std::move(sink);
  return std::make_shared<const DeclaredBenchmarkContext>(std::move(labels));
}

bool same_labels(const BenchmarkLabels& a, const BenchmarkLabels& b) {
  return a.run == b.run && a.input_adapter == b.input_adapter &&
      a.output_codec == b.output_codec && a.sink == b.sink;
}

void check_attempt_labels(const ObservationSummary& summary,
                          const BenchmarkLabels& expected,
                          std::uint64_t sequence,
                          ObservationOutcome outcome) {
  check(summary.sequence == sequence && summary.outcome == outcome &&
        summary.declared_benchmark &&
        same_labels(summary.declared_benchmark->labels(), expected),
        "attempt did not retain the caller declarations bound at begin");
}

void scenario_callbacks_begin_bound_labels_and_utf8_export() {
  QFixture fixture;
  auto runtime = make_delta_runtime(fixture, fixture.initial,
                                   mode_options(ObservationMode::counters));
  const auto label_a = benchmark_context(std::string("run-A\0tail", 10),
      std::nullopt, std::string{}, std::string{"sink-A"});
  const auto label_b = benchmark_context(
      std::string(1, static_cast<char>(0xff)), std::string{}, std::nullopt,
      std::string("sink\0B", 6));
  const auto label_c = benchmark_context(std::string("run-C\0tail", 10),
      std::string{}, std::nullopt, std::string{"sink-C"});
  const auto label_d = benchmark_context(std::nullopt, std::string{},
      std::string{"codec-D"}, std::nullopt);

  runtime.declare_benchmark_context(label_a);
  check(same_labels(runtime.observations().current_declared_benchmark->labels(),
                    label_a->labels()),
        "initial caller declaration was not readable from current snapshot");

  auto first_pending = runtime.begin(insert_s(1));
  auto first_open = runtime.observations();
  check(first_open.current && first_open.current->declared_benchmark &&
        same_labels(first_open.current->declared_benchmark->labels(), label_a->labels()),
        "first attempt did not bind declaration A at begin");
  runtime.declare_benchmark_context(label_b);
  auto mid_first = runtime.observations();
  check(mid_first.current_declared_benchmark &&
        same_labels(mid_first.current_declared_benchmark->labels(), label_b->labels()) &&
        mid_first.current && mid_first.current->declared_benchmark &&
        same_labels(mid_first.current->declared_benchmark->labels(), label_a->labels()) &&
        mid_first.current_configuration->generation() == 0,
        "mid-attempt declaration B relabeled attempt A or advanced semantic generation");
  first_pending.drain();
  auto first_epoch = first_pending.commit();
  const auto first_record = first_epoch.next();
  check(first_record && first_record->operation == SetOperation::insert &&
        first_record->tuple.values() == row(7),
        "declaration change altered the independent first Q output");
  auto first_closed = runtime.observations();
  check_attempt_labels(*first_closed.last, label_a->labels(), 1,
                       ObservationOutcome::committed);
  check(first_closed.current_declared_benchmark &&
        same_labels(first_closed.current_declared_benchmark->labels(), label_b->labels()),
        "committed A attempt overwrote current B declaration");

  static_cast<void>(runtime.set_mode(DeltaMode::maintenance));
  auto maintenance = runtime.observations();
  check(maintenance.current_configuration &&
        maintenance.current_configuration->generation() == 1 &&
        maintenance.last && maintenance.last->configuration &&
        maintenance.last->configuration->generation() == 0,
        "mode switch relabeled declaration history or failed to separate current config");
  static_cast<void>(runtime.set_mode(DeltaMode::delta));

  auto second_pending = runtime.begin(erase_s(2));
  auto second_open = runtime.observations();
  check(second_open.current && second_open.current->declared_benchmark &&
        same_labels(second_open.current->declared_benchmark->labels(), label_b->labels()),
        "second attempt did not bind then-current B declaration");
  runtime.declare_benchmark_context(label_c);
  second_pending.rollback();
  auto second_closed = runtime.observations();
  check_attempt_labels(*second_closed.last, label_b->labels(), 2,
                       ObservationOutcome::aborted);
  check(second_closed.current_declared_benchmark &&
        same_labels(second_closed.current_declared_benchmark->labels(), label_c->labels()),
        "aborted B attempt overwrote current C declaration");
  check(second_closed.last->declared_benchmark->labels().run ==
            std::optional<std::string>{std::string(1, static_cast<char>(0xff))} &&
        second_closed.last->declared_benchmark->labels().sink ==
            std::optional<std::string>{std::string("sink\0B", 6)},
        "native invalid-UTF8/NUL declarations were changed during storage");
  expect_error("text_encoding", [&] {
    static_cast<void>(io::write_run_context_json(second_closed));
  }, "invalid native label should fail strict export only");
  check(runtime.sequence() == 1 && runtime.mode() == DeltaMode::delta &&
        drain(runtime.results()) == evaluate(fixture, fixture.with_s()),
        "invalid UTF-8 caller declaration changed runtime semantics");

  auto third_pending = runtime.begin(erase_s(2));
  third_pending.drain();
  auto third_epoch = third_pending.commit();
  const auto erase_record = third_epoch.next();
  check(erase_record && erase_record->operation == SetOperation::erase &&
        erase_record->tuple.values() == row(7),
        "C declaration retry changed independent Q erase output");
  auto third_summary = runtime.observations();
  check_attempt_labels(*third_summary.last, label_c->labels(), 2,
                       ObservationOutcome::committed);
  runtime.declare_benchmark_context(label_d);
  auto final_snapshot = runtime.observations();
  check(final_snapshot.current_declared_benchmark && final_snapshot.last &&
        final_snapshot.last->declared_benchmark &&
        same_labels(final_snapshot.current_declared_benchmark->labels(), label_d->labels()) &&
        same_labels(final_snapshot.last->declared_benchmark->labels(), label_c->labels()),
        "current declaration D was copied onto historical attempt C");

  const auto encoded = io::write_run_context_json(final_snapshot);
  const auto parsed = Json::parse(encoded);
  check(parsed["current_declared_benchmark"]["provenance"] ==
            "caller_declared_unmeasured" &&
        parsed["current_declared_benchmark"]["authority"] == "none" &&
        parsed["last_attempt"]["declared_benchmark"]["provenance"] ==
            "caller_declared_unmeasured",
        "exported declared context overstated provenance or authority");
  check(parsed["current_declared_benchmark"]["run"].is_null() &&
        parsed["current_declared_benchmark"]["input_adapter"] == "" &&
        parsed["current_declared_benchmark"]["output_codec"] == "codec-D" &&
        parsed["current_declared_benchmark"]["sink"].is_null(),
        "export failed to preserve current missing-versus-empty labels");
  const auto& history = parsed["last_attempt"]["declared_benchmark"];
  check(history["run"] == std::string("run-C\0tail", 10) &&
        history["input_adapter"] == "" && history["output_codec"].is_null() &&
        history["sink"] == "sink-C",
        "export copied current declaration D onto historical declaration C");
  check(encoded.find("\\u0000") != std::string::npos,
        "embedded NUL was not encoded as a JSON control escape");
  check(parsed["last_attempt"]["initialization"]["route"] ==
            "initialized_database" &&
        parsed["last_attempt"]["initialization"]["applied_build"]["method"] ==
            "direct",
        "attempt export omitted the actual initialized-database route");
  check(parsed["session"].is_null() && parsed["current_attempt"].is_null(),
        "runtime-only export fabricated session/current-attempt state");
  check(io::write_run_context_json(final_snapshot, encoded.size()) == encoded,
        "exact encoded-byte cap rejected the complete label artifact");
  expect_error("resource_limit", [&] {
    static_cast<void>(io::write_run_context_json(final_snapshot, encoded.size() - 1));
  }, "encoded-size cap one byte below the exact artifact should fail");
}

void scenario_callback_retries_deferred_discard_and_oom() {
  QFixture fixture;
  auto runtime = make_delta_runtime(fixture, fixture.two_roots(),
                                   mode_options(ObservationMode::counters));
  auto epoch = runtime.apply(insert_s(1));
  check(epoch.remaining() == 2,
        "callback retry fixture did not create two literal output rows");

  std::size_t serialization_calls = 0;
  std::optional<Row> first_row;
  const auto expected_rows = std::set<Row>{row(7), row(8)};
  const auto serializer = [&](const SignedResult& result) {
    ++serialization_calls;
    const auto values = result.tuple.values();
    check(result.operation == SetOperation::insert && expected_rows.contains(values),
          "serializer observed a nonliteral Q result");
    if (serialization_calls == 1) first_row = values;
    else if (serialization_calls <= 4)
      check(first_row && *first_row == values,
            "serializer retry did not receive the same unacknowledged row");
    else
      check(first_row && *first_row != values,
            "post-ack callback did not advance to the remaining row");
    if (serialization_calls <= 2) throw std::bad_alloc{};
  };

  bool serializer_failed = false;
  try {
    static_cast<void>(epoch.deliver_one(serializer,
        [](const SignedResult&) {}));
  } catch (const std::bad_alloc&) { serializer_failed = true; }
  check(serializer_failed, "first serializer OOM was swallowed instead of retaining output");
  auto after_first_oom = runtime.observations();
  check(after_first_oom.last && after_first_oom.last->outcome == ObservationOutcome::committed,
        "serializer OOM changed the committed attempt outcome");
  check_output(*after_first_oom.last,
      disposition(false, true, false, true, true, false, false, true, false, false),
      "serializer OOM disposition does not distinguish invoked from acknowledged");
  check_metric(*after_first_oom.last, MetricId::delta_serialization_attempts, 1,
               "first serializer attempt count differs");
  check_metric(*after_first_oom.last, MetricId::delta_serialization_failures, 1,
               "first serializer OOM failure count differs");
  check_metric(*after_first_oom.last, MetricId::delta_sink_attempts, 0,
               "sink ran after serializer OOM");

  bool second_oom = false;
  try {
    static_cast<void>(epoch.deliver_one(serializer,
        [](const SignedResult&) {}));
  } catch (const std::bad_alloc&) { second_oom = true; }
  check(second_oom, "repeated serializer OOM did not preserve the same output row");

  std::size_t sink_calls = 0;
  const auto failing_sink = [&](const SignedResult& result) {
    ++sink_calls;
    check(first_row && result.tuple.values() == *first_row,
          "sink retry did not receive the serializer's same unacknowledged row");
    throw std::runtime_error("synthetic sink rejection");
  };
  bool sink_failed = false;
  try { static_cast<void>(epoch.deliver_one(serializer, failing_sink)); }
  catch (const std::runtime_error&) { sink_failed = true; }
  check(sink_failed && sink_calls == 1,
        "sink exception was not propagated as an unacknowledged retryable row");
  const auto after_sink_failure = runtime.observations();
  check_output(*after_sink_failure.last,
      disposition(false, true, false, true, true, false, false, true, true, false),
      "failed sink disposition differs from the invoked-but-unacknowledged facts");
  check_metric(*after_sink_failure.last, MetricId::delta_serialization_attempts, 3,
               "serializer retry count differs after two OOM and one success");
  check_metric(*after_sink_failure.last, MetricId::delta_serialization_successes, 1,
               "serializer success count differs before sink failure");
  check_metric(*after_sink_failure.last, MetricId::delta_serialization_failures, 2,
               "serializer OOM failures were not both retained");
  check_metric(*after_sink_failure.last, MetricId::delta_sink_attempts, 1,
               "sink attempt count differs after one failed callback");
  check_metric(*after_sink_failure.last, MetricId::delta_sink_failures, 1,
               "sink failure count differs after one failed callback");
  check_metric(*after_sink_failure.last, MetricId::delta_acknowledged_records, 0,
               "failed serializer/sink path acknowledged an output row");

  const auto successful_sink = [&](const SignedResult& result) {
    ++sink_calls;
    check(first_row && result.tuple.values() == *first_row,
          "successful retry changed the first literal result before acknowledgment");
  };
  check(epoch.deliver_one(serializer, successful_sink),
        "successful callback retry did not deliver and acknowledge one row");
  auto after_ack = runtime.observations();
  check_metric(*after_ack.last, MetricId::delta_sink_successes, 1,
               "successful sink callback count differs");
  check_metric(*after_ack.last, MetricId::delta_acknowledged_records, 1,
               "successful sink callback did not acknowledge exactly one row");
  check(!after_ack.last->output->transferred && !after_ack.last->output->released,
        "callback acknowledgment was confused with next() transfer or output close");

  const auto discard_from_sink = [&](const SignedResult& result) {
    check(first_row && result.tuple.values() != *first_row &&
          expected_rows.contains(result.tuple.values()),
          "deferred-discard callback did not receive the second literal output");
    epoch.discard();  // Deferred until the currently borrowed row's callback returns.
  };
  check(epoch.deliver_one(serializer, discard_from_sink),
        "callback-requested deferred discard did not complete the current invocation");
  const auto after_deferred_discard = runtime.observations();
  check_output(*after_deferred_discard.last,
      disposition(false, true, false, true, true, true, false, true, true, true),
      "deferred callback discard lost invocation, unread discard or release facts");
  check_metric(*after_deferred_discard.last, MetricId::delta_serialization_attempts, 5,
               "serializer invocations were confused with successful acknowledgments");
  check_metric(*after_deferred_discard.last, MetricId::delta_serialization_successes, 3,
               "serializer success/failure totals differ from five callback attempts");
  check_metric(*after_deferred_discard.last, MetricId::delta_serialization_failures, 2,
               "persistent serializer OOM count differs from literal two failures");
  check_metric(*after_deferred_discard.last, MetricId::delta_sink_attempts, 3,
               "sink invocation count differs from failed/success/deferred calls");
  check_metric(*after_deferred_discard.last, MetricId::delta_sink_successes, 2,
               "sink success count differs from literal two successful callbacks");
  check_metric(*after_deferred_discard.last, MetricId::delta_sink_failures, 1,
               "sink failure count differs from literal one failure");
  check_metric(*after_deferred_discard.last, MetricId::delta_acknowledged_records, 1,
               "callback invocation count was confused with acknowledged row count");
  check(epoch.remaining() == 0 && !epoch.active(),
        "deferred callback discard did not close remaining output ownership");
  auto expected_db = fixture.two_roots();
  expected_db.tables[1].insert(row(9));
  check(drain(runtime.results()) == evaluate(fixture, expected_db),
        "callback failures/deferred discard changed committed query state");
}

struct ModeMatrixResult {
  std::size_t apply_allocations = 0;
  std::size_t rollback_allocations = 0;
  std::size_t failure_allocations = 0;
};

void scenario_mode_parity_work_failures_clock_and_rollback() {
  detail::set_observation_clock_for_testing(&fake_clock);
  struct RestoreClock {
    ~RestoreClock() { detail::set_observation_clock_for_testing(nullptr); }
  } restore_clock;

  std::optional<ModeMatrixResult> baseline;
  for (const auto mode : {ObservationMode::off, ObservationMode::counters,
                          ObservationMode::timed, ObservationMode::trace}) {
    QFixture fixture;
    auto options = mode_options(mode);
    options.completion = DeltaCompletion::automatic;
    auto runtime = DeltaRuntime::initialize(fixture.plan, fixture.initial, options);

    optional_clock_reads = 0;
    std::optional<DeltaRuntime::Epoch> epoch;
    allocation_probe::Measurement apply_measurement;
    allocation_probe::measure([&] {
      epoch.emplace(runtime.apply(insert_s(1)));
    }, allocation_probe::no_failure, apply_measurement);
    const auto attempt_clock_reads = optional_clock_reads;
    const auto attempt_before_current_results = runtime.observations();
    check(epoch && epoch->remaining() == 1,
          "matched mode update did not prepare the one literal Q output");
    check(epoch->input().support.metrics.work == 40 &&
          epoch->input().input.metrics.work == 44,
          "matched mode update changed mandatory support/physical work literals");
    const auto signed_output = epoch->next();
    const Relation expected_result = evaluate(fixture, fixture.with_s());
    check(expected_result == Relation{row(7)} && signed_output &&
          signed_output->operation == SetOperation::insert &&
          signed_output->tuple.values() == row(7) && !epoch->next(),
          "matched mode update changed independent Q result or signed output");
    check(optional_clock_reads == attempt_clock_reads,
          "prepared output ownership transfer unexpectedly evaluated a clock");
    const auto before_current_cursor_reads = optional_clock_reads;
    check(runtime.snapshot().physical.tables == fixture.with_s().tables &&
          drain(runtime.results()) == expected_result,
          "matched mode update changed committed physical state or reference answer");
    const auto after_current_cursor_reads = optional_clock_reads;
    const auto current_cursor = runtime.last_cursor_observation();

    const auto observed = runtime.observations();
    if (mode == ObservationMode::off) {
      check(observed.options.mode == ObservationMode::off &&
            observed.mandatory_accounting && !observed.current_configuration &&
            !observed.current && !observed.last && observed.attempts == 0 &&
            observed.trace == TraceDisposition::disabled && optional_clock_reads == 0,
            "off mode retained optional history or read the optional clock");
    } else {
      check(observed.last && observed.last->sequence == 1 &&
            observed.last->outcome == ObservationOutcome::committed &&
            observed.current_configuration &&
            observed.current_configuration->requested_options().physical.support.work_limit ==
                std::optional<std::uint64_t>{7103},
            "enabled mode did not retain its successful attempt/configuration");
      check_metric(*observed.last, MetricId::support_work, 40,
                   "matched mode support registry work differs from literal 40");
      check_metric(*observed.last, MetricId::physical_work_inclusive, 44,
                   "matched mode inclusive physical work differs from literal 44");
      check_metric(*observed.last, MetricId::physical_work_exclusive, 4,
                   "matched mode exclusive physical work differs from literal 4");
      check_metric(*observed.last, MetricId::delta_work, epoch->metrics().work,
                   "delta mandatory-work registry does not reconcile with epoch work");
      const auto& clock_reads = observed.last->metric(MetricId::delta_clock_reads);
      const auto& nested_reads = observed.last->metric(MetricId::nested_cursor_clock_reads);
      check(clock_reads.availability == MetricAvailability::available &&
            nested_reads.availability == MetricAvailability::available &&
            clock_reads.value + nested_reads.value == attempt_clock_reads,
            "fake clock attempt interval must equal disjoint delta and nested-cursor reads");
      check(attempt_before_current_results.last &&
            clock_reads.value == attempt_before_current_results.last->metric(MetricId::delta_clock_reads).value &&
            nested_reads.value == attempt_before_current_results.last->metric(MetricId::nested_cursor_clock_reads).value,
            "later committed cursor rewrote the previous delta attempt clock counts");
      check(current_cursor &&
            current_cursor->metric(CursorMetricId::clock_reads).availability == MetricAvailability::available &&
            current_cursor->metric(CursorMetricId::clock_reads).value ==
                after_current_cursor_reads - before_current_cursor_reads,
            "later committed cursor interval does not match its own clock-read counter");
      if (mode == ObservationMode::counters) {
        check(optional_clock_reads == 0 &&
              observed.trace == TraceDisposition::disabled,
              "counters mode read the optional clock or retained a trace");
      } else {
        check(optional_clock_reads > 0,
              "timed/trace mode did not read the injected optional clock");
      }
      if (mode == ObservationMode::timed || mode == ObservationMode::trace) {
        const auto& timing = observed.last->metric(MetricId::delta_propagation_ns);
        check(timing.availability == MetricAvailability::available && timing.value > 0,
              "timed/trace mode failed to record positive propagation time");
      }
      if (mode == ObservationMode::trace) {
        const auto trace = runtime.observation_trace();
        check(trace.snapshot.trace == TraceDisposition::committed &&
              trace.snapshot.trace_records == trace.records.size() &&
              trace.records.size() <= 41 && !trace.records.empty() &&
              trace.records.front().kind == TraceKind::begin &&
              trace.records.back().kind == TraceKind::transferred,
              "matched trace mode lacks a bounded begin/delivery causal trace");
        const auto commit = std::find_if(trace.records.begin(), trace.records.end(),
            [](const auto& record) { return record.kind == TraceKind::commit; });
        check(commit != trace.records.end() &&
              std::count_if(trace.records.begin(), trace.records.end(),
                  [](const auto& record) { return record.kind == TraceKind::commit; }) == 1 &&
              std::any_of(commit, trace.records.end(),
                  [](const auto& record) { return record.kind == TraceKind::transferred; }),
              "committed trace must record input commit before post-commit row delivery");
      }
    }

    // Closing an already prepared result and rolling back an unpublished
    // attempt must not allocate in any mode. The measured region excludes
    // snapshot/export copies and ordinary runtime admission.
    allocation_probe::Measurement release_measurement;
    allocation_probe::measure([&] { epoch->discard(); },
                              allocation_probe::no_failure, release_measurement);
    check(release_measurement.allocations == 0,
          "output release allocated while closing its already-owned spool");

    auto cancel_runtime = DeltaRuntime::initialize(fixture.plan, fixture.initial, options);
    auto pending = cancel_runtime.begin(insert_s(1));
    optional_clock_reads = 0;
    allocation_probe::Measurement rollback_measurement;
    allocation_probe::measure([&] { pending.rollback(); },
                              allocation_probe::no_failure, rollback_measurement);
    check(rollback_measurement.allocations == 0 && cancel_runtime.sequence() == 0 &&
          cancel_runtime.snapshot().physical.tables == fixture.initial.tables &&
          drain(cancel_runtime.results()) == evaluate(fixture, fixture.initial),
          "cancel hook allocated or changed the pre-update physical/query state");
    const auto canceled = cancel_runtime.observations();
    if (mode == ObservationMode::off) {
      check(!canceled.last && canceled.attempts == 0 && optional_clock_reads == 0,
            "off-mode rollback retained history or read the optional clock");
    } else {
      check(canceled.last && canceled.last->outcome == ObservationOutcome::aborted,
            "enabled-mode rollback did not retain an aborted attempt");
      if (mode == ObservationMode::counters)
        check(optional_clock_reads == 0,
              "counters-mode rollback read the optional clock");
      else
        check(optional_clock_reads > 0,
              "timed/trace rollback did not read the optional clock");
    }

    // The same literal 39-unit support cap rejects the 40-unit update in
    // every mode. Verify the error and state independently of telemetry.
    auto limited_options = mode_options(mode);
    limited_options.physical.support.work_limit = std::uint64_t{39};
    auto limited = DeltaRuntime::initialize(fixture.plan, fixture.initial,
                                              limited_options);
    optional_clock_reads = 0;
    allocation_probe::Measurement failed_measurement;
    bool resource_rejected = false;
    try {
      allocation_probe::measure([&] {
        static_cast<void>(limited.apply(insert_s(1)));
      }, allocation_probe::no_failure, failed_measurement);
    } catch (const Error& error) {
      resource_rejected = error.code() == "resource_limit";
    }
    check(resource_rejected && failed_measurement.allocations > 0,
          "matched mode failed to preserve the literal 39/40 resource-limit error");
    check(limited.sequence() == 0 && limited.ready() &&
          limited.snapshot().physical.tables == fixture.initial.tables &&
          drain(limited.results()) == evaluate(fixture, fixture.initial),
          "39/40 support-cap failure did not roll back the independent Q state");
    const auto failed = limited.observations();
    if (mode == ObservationMode::off) {
      check(!failed.last && failed.attempts == 0 && optional_clock_reads == 0,
            "off-mode failure retained optional history or read the clock");
    } else {
      check(failed.last && failed.last->outcome == ObservationOutcome::aborted,
            "enabled-mode 39/40 failure did not close an aborted attempt");
      const auto& partial_support = failed.last->metric(MetricId::support_work);
      check(partial_support.availability == MetricAvailability::available &&
            partial_support.value < 40,
            "failed support work did not preserve a bounded partial total");
      if (mode == ObservationMode::counters)
        check(optional_clock_reads == 0,
              "counters-mode cap failure read the optional clock");
      else
        check(optional_clock_reads > 0,
              "timed/trace cap failure did not read the optional clock");
      if (mode == ObservationMode::trace)
        check(failed.trace == TraceDisposition::aborted,
              "trace mode did not retain an aborted cap-failure trace");
    }

    const ModeMatrixResult result{apply_measurement.allocations,
                                  rollback_measurement.allocations,
                                  failed_measurement.allocations};
    if (!baseline) baseline = result;
    else
      check(baseline->apply_allocations == result.apply_allocations &&
            baseline->rollback_allocations == result.rollback_allocations &&
            baseline->failure_allocations == result.failure_allocations,
            "optional observation mode changed mutation/rollback allocation counts");
  }
}

template <class Action>
void run_group(std::string_view name, Action&& action) {
  std::cout << "[ RUN      ] " << name << '\n';
  std::forward<Action>(action)();
  std::cout << "[       OK ] " << name << '\n';
}
}  // namespace

int main() {
  try {
    run_group("initialization routes and exact BuildOptions",
              scenario_initialization_routes_and_build_options);
    run_group("owned session contexts and persistent admission OOM",
              scenario_session_context_owned_stream_typed_window_and_admission_oom);
    run_group("actual output disposition lifecycle",
              scenario_actual_output_disposition_lifecycle);
    run_group("begin-bound labels and strict JSON export",
              scenario_callbacks_begin_bound_labels_and_utf8_export);
    run_group("callback retries and deferred discard",
              scenario_callback_retries_deferred_discard_and_oom);
    run_group("mode parity, work limits, clocks and allocation-free cleanup",
              scenario_mode_parity_work_failures_clock_and_rollback);
    std::cout << "[  PASSED  ] 6 independent run-context groups\n";
    return 0;
  } catch (const std::exception& error) {
    allocation_probe::disarm();
    detail::set_observation_clock_for_testing(nullptr);
    std::cerr << "[  FAILED  ] " << error.what() << '\n';
    return 1;
  }
}
