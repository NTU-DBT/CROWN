#include "crown/api/error.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/session.hpp"
#include "evaluator.hpp"

#include <cstdint>
#include <iostream>
#include <memory>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

namespace {
using namespace crown;
using namespace crown::io;
using namespace crown::runtime;
using SignedKey = std::pair<SetOperation, Row>;

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

template <class Action>
void expect_code(Action&& action, std::string_view code,
                 const std::string& label) {
  try {
    std::forward<Action>(action)();
  } catch (const Error& failure) {
    check(failure.code() == code,
          label + ": expected " + std::string(code) + ", got " + failure.code());
    return;
  }
  throw std::runtime_error(label + ": expected error " + std::string(code));
}

static_assert(!std::is_copy_constructible_v<TransportBatch>);
static_assert(!std::is_copy_assignable_v<TransportBatch>);
static_assert(std::is_nothrow_move_constructible_v<TransportBatch>);
static_assert(std::is_nothrow_move_assignable_v<TransportBatch>);
static_assert(!std::is_copy_constructible_v<TypedQueue>);

Value n(std::int64_t value) { return value; }

Catalog unary_catalog() {
  return {1, {{"unary", {{"x", ScalarType::int64}}}}};
}

PhysicalPlan unary_plan() {
  const auto catalog = unary_catalog();
  const Query query{{{"x", ScalarType::int64}},
                    {{"unary", TableId{0}, {VariableId{0}}}},
                    {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"unary", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan ignored_projection_plan() {
  const Catalog catalog{3, {{"pair", {{"x", ScalarType::int64},
                                       {"payload", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}},
      {{"pair", TableId{0}, {VariableId{0}, IgnoredColumn{}}}},
      {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"pair", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan self_join_plan() {
  const Catalog catalog{5,
      {{"edge", {{"src", ScalarType::int64}, {"dst", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"z", ScalarType::int64},
                     {"y", ScalarType::int64}},
      {{"left", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"right", TableId{0}, {VariableId{1}, VariableId{2}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "z"},
       {VariableId{2}, "y"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"join", NodeKind::generalized, {VariableId{1}}, {NodeId{1}, NodeId{2}}, {}, {}},
       {"left", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}},
       {"right", NodeKind::native, {VariableId{1}, VariableId{2}}, {}, 1, {}}},
      {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan boolean_plan() {
  const Catalog catalog{7,
      {{"flags", {{"enabled", ScalarType::boolean}}}}};
  const Query query{{{"enabled", ScalarType::boolean}},
      {{"flags", TableId{0}, {VariableId{0}}}},
      {{VariableId{0}, "enabled"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"flags", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

InputEvent event(std::uint64_t sequence, Row values,
                 SetOperation operation = SetOperation::insert,
                 std::optional<SourcePosition> position = std::nullopt,
                 TableId table = TableId{0}) {
  return {{sequence, table, operation, std::move(values)}, std::move(position)};
}

TransportBatch batch(std::vector<InputEvent> events, BatchLimits limits = {}) {
  std::vector<InputItem> items;
  items.reserve(events.size());
  for (auto& item : events) items.emplace_back(std::move(item));
  return TransportBatch(std::move(items), limits);
}

QueueLimits generous_queue_limits() {
  QueueLimits limits;
  limits.batches = 32;
  limits.events = 64;
  return limits;
}

void transport_batch_and_admission_limits() {
  auto empty = batch({});
  check(empty.empty() && empty.size() == 0,
        "empty batch retained an input event");
  BatchLimits zero_batch_limits;
  zero_batch_limits.events = 0;
  zero_batch_limits.bytes = 0;
  auto allowed_empty = batch({}, zero_batch_limits);
  check(allowed_empty.empty(), "zero-capacity batch rejected an empty batch");

  expect_code([&] {
    static_cast<void>(batch({event(1, {n(1)})}, BatchLimits{0, 1024}));
  }, "resource_limit", "batch event cap");
  expect_code([&] {
    static_cast<void>(batch({event(1, {n(1)})}, BatchLimits{1, 0}));
  }, "resource_limit", "batch byte cap");

  const auto catalog = unary_catalog();
  QueueLimits empty_limits;
  empty_limits.batches = 0;
  empty_limits.events = 0;
  empty_limits.bytes = 0;
  TypedQueue empty_queue(catalog, QueueMode::physical, empty_limits);
  check(empty_queue.enqueue(allowed_empty) == Admission::accepted &&
            allowed_empty.empty() && allowed_empty.accounted_bytes() == 0 &&
            empty_queue.stats() == QueueStats{} &&
            !empty_queue.closed(),
        "empty admission used capacity, retained a descriptor, or closed input");

  auto two_events = batch({event(1, {n(1)}), event(2, {n(2)})});
  const auto owned_size = two_events.size();
  const auto owned_bytes = two_events.accounted_bytes();
  check(owned_size == 2 && owned_bytes > 0,
        "nonempty batch did not report its owned event payload");

  QueueLimits event_limited = generous_queue_limits();
  event_limited.events = 1;
  TypedQueue event_queue(catalog, QueueMode::physical, event_limited);
  const auto before = event_queue.stats();
  check(event_queue.enqueue(two_events) == Admission::full,
        "event cap admitted a batch that exceeded its remaining capacity");
  check(two_events.size() == owned_size &&
            two_events.accounted_bytes() == owned_bytes &&
            event_queue.stats() == before,
        "full rejection changed caller ownership or queue accounting");

  QueueLimits byte_limited = generous_queue_limits();
  byte_limited.bytes = 0;
  TypedQueue byte_queue(catalog, QueueMode::physical, byte_limited);
  auto one_event = batch({event(1, {n(1)})});
  const auto one_bytes = one_event.accounted_bytes();
  check(byte_queue.enqueue(one_event) == Admission::full &&
            one_event.size() == 1 && one_event.accounted_bytes() == one_bytes &&
            byte_queue.stats() == QueueStats{},
        "byte-cap rejection consumed a batch or retained accounting");

  QueueLimits descriptor_limited = generous_queue_limits();
  descriptor_limited.batches = 1;
  TypedQueue descriptor_queue(catalog, QueueMode::physical, descriptor_limited);
  auto first = batch({event(1, {n(1)})});
  auto second = batch({event(2, {n(2)})});
  check(descriptor_queue.enqueue(first) == Admission::accepted,
        "queue rejected its first bounded batch");
  const auto first_stats = descriptor_queue.stats();
  const auto second_bytes = second.accounted_bytes();
  check(descriptor_queue.enqueue(second) == Admission::full &&
            second.size() == 1 && second.accounted_bytes() == second_bytes &&
            descriptor_queue.stats() == first_stats,
        "batch-count rejection changed queue or caller state");
}

std::vector<InputEvent> alternating_trace() {
  return {event(1, {n(8)}, SetOperation::insert, SourcePosition{"feed", 10}),
          event(2, {n(8)}, SetOperation::erase, SourcePosition{"feed", 20}),
          event(3, {n(8)}, SetOperation::insert, SourcePosition{"feed", 30}),
          event(4, {n(8)}, SetOperation::erase, SourcePosition{"feed", 40})};
}

void fifo_barriers_for_every_batch_partition() {
  const auto catalog = unary_catalog();
  const auto trace = alternating_trace();
  // There are three possible cut points. Exercise every contiguous partition,
  // including one batch and four singleton batches.
  for (unsigned cuts = 0; cuts < 8; ++cuts) {
    TypedQueue queue(catalog, QueueMode::physical, generous_queue_limits());
    std::size_t batch_count = 0;
    std::size_t begin = 0;
    for (std::size_t i = 0; i < trace.size(); ++i) {
      if (i + 1 != trace.size() && (cuts & (1U << i)) == 0) continue;
      std::vector<InputEvent> part;
      for (auto j = begin; j <= i; ++j) part.push_back(trace[j]);
      auto offered = batch(std::move(part));
      check(queue.enqueue(offered) == Admission::accepted && offered.empty(),
            "an admissible partition was not transferred to the queue");
      ++batch_count;
      begin = i + 1;
    }

    const auto retained = queue.stats();
    check(retained.batches == batch_count && retained.events == trace.size() &&
              retained.accounted_bytes > 0,
          "queue statistics omitted an admitted partition or its payload");
    queue.finish();
    check(queue.closed() && queue.stats().closed && queue.stats().events == trace.size(),
          "finishing input discarded or uncounted its queued prefix");
    for (const auto& expected : trace) {
      const auto* head = queue.peek();
      check(head != nullptr && std::holds_alternative<InputEventView>(*head),
            "FIFO queue lost an input event");
      const auto& actual = std::get<InputEventView>(*head);
      check(actual.update.sequence == expected.update.sequence &&
                actual.update.operation == expected.update.operation &&
                actual.update.values == expected.update.values &&
                actual.source_position == expected.source_position,
            "queue coalesced or reordered a signed update barrier");
      check(queue.stats().events == trace.size() - expected.update.sequence + 1,
            "peek stopped counting the pending head before acknowledgement");
      queue.acknowledge();
      check(queue.progress().sequence == expected.update.sequence,
            "queue progress advanced by more or less than one acknowledged event");
    }
    check(queue.peek() == nullptr && queue.empty() && queue.stats().events == 0 &&
              queue.progress().source_positions.at("feed") == 40,
          "acknowledging the accepted prefix did not preserve its final source offset");
    check(queue.peek() == nullptr && queue.stats().closed,
          "finishing an empty queue did not establish stable EOF");
  }
}

void queue_sticky_validation_and_owned_rows() {
  const auto catalog = unary_catalog();
  QueueLimits limits = generous_queue_limits();
  TypedQueue sequence_queue(catalog, QueueMode::physical, limits);
  auto invalid_sequence = batch({
      event(1, {n(1)}), event(7, {n(2)}), event(8, {n(3)})});
  check(sequence_queue.enqueue(invalid_sequence) == Admission::accepted,
        "queue validated a later event before accepting its bounded batch");
  check(sequence_queue.peek() != nullptr, "valid prefix was not made available");
  sequence_queue.acknowledge();
  expect_code([&] { static_cast<void>(sequence_queue.peek()); },
              "invalid_sequence", "late sequence validation");
  check(sequence_queue.failed() && sequence_queue.progress().sequence == 1 &&
            sequence_queue.stats().events == 2,
        "late sequence failure did not preserve the accepted prefix and head");
  expect_code([&] { static_cast<void>(sequence_queue.peek()); },
              "input_failed", "sticky queue validation failure");
  check(sequence_queue.progress().sequence == 1 &&
            sequence_queue.stats().events == 2,
        "re-reading a sticky failure consumed malformed or following input");

  TypedQueue source_queue(catalog, QueueMode::physical, limits);
  auto invalid_source = batch({
      event(1, {n(1)}, SetOperation::insert, SourcePosition{"feed", 15}),
      event(2, {n(2)}, SetOperation::insert, SourcePosition{"feed", 15})});
  check(source_queue.enqueue(invalid_source) == Admission::accepted,
        "source-position validation ran during batch admission");
  check(source_queue.peek() != nullptr, "source-position valid prefix is missing");
  source_queue.acknowledge();
  expect_code([&] { static_cast<void>(source_queue.peek()); },
              "invalid_source_position", "nonincreasing source offset");
  check(source_queue.progress().sequence == 1 &&
            source_queue.progress().source_positions.at("feed") == 15 &&
            source_queue.stats().events == 1,
        "source-position error advanced progress or released its head");

  TypedQueue schema_queue(catalog, QueueMode::physical, limits);
  auto bad_schema = batch({event(1, {std::string("wrong type")})});
  check(schema_queue.enqueue(bad_schema) == Admission::accepted,
        "row schema was validated during queue admission");
  expect_code([&] { static_cast<void>(schema_queue.peek()); },
              "invalid_update", "typed row schema validation");
  check(schema_queue.failed() && schema_queue.progress().sequence == 0 &&
            schema_queue.stats().events == 1,
        "bad typed row was acknowledged or removed after validation failure");

  TypedQueue kind_queue(catalog, QueueMode::physical, limits);
  std::vector<InputItem> wrong_kind;
  wrong_kind.emplace_back(WindowCommand{1, AdvanceWatermark{50}, std::nullopt});
  TransportBatch window_item(std::move(wrong_kind));
  check(kind_queue.enqueue(window_item) == Admission::accepted,
        "queue rejected an item before validating its selected mode");
  expect_code([&] { static_cast<void>(kind_queue.peek()); },
              "invalid_input_kind", "window command in physical queue");

  const Catalog strings{2, {{"text", {{"value", ScalarType::string}}}}};
  const std::string payload(300, 'q');
  TypedQueue owning_queue(strings, QueueMode::physical, limits);
  {
    auto source = batch({event(1, {payload})});
    check(owning_queue.enqueue(source) == Admission::accepted && source.empty(),
          "string row batch was not transferred");
  }
  const auto* owned = owning_queue.peek();
  check(owned && std::get<InputEventView>(*owned).update.values == Row{payload},
        "queued source row did not own its string after caller destruction");
}

std::set<SignedKey> collect_epoch_output(QuerySession& session,
                                         const std::string& label) {
  std::set<SignedKey> rows;
  std::uint64_t ordinal = 0;
  while (auto record = session.next_output()) {
    check(record->ordinal == ++ordinal,
          label + ": output ordinals did not begin at one for the barrier");
    check(rows.emplace(record->operation, crown::storage::export_row(record->tuple.values())).second,
          label + ": duplicate signed row crossed the session boundary");
  }
  return rows;
}

void step_to_prepared(QuerySession& session, const std::string& label) {
  std::size_t calls = 0;
  while (session.status().phase != SessionPhase::prepared) {
    static_cast<void>(session.step());
    check(++calls < 100000, label + ": epoch failed to reach preparation");
  }
}

void check_snapshot(QuerySession& session, const reference::Session& oracle,
                    std::uint64_t sequence, const std::string& label) {
  const auto snapshot = session.snapshot();
  Relation rows;
  for (const auto& tuple : snapshot.rows) {
    check(tuple.layout().same_token(snapshot.layout),
          label + ": snapshot row does not own the published layout");
    check(rows.insert(crown::storage::export_row(tuple.values())).second,
          label + ": snapshot contains a duplicate projected row");
  }
  check(snapshot.sequence == sequence && snapshot.progress.sequence == sequence &&
            snapshot.progress == session.progress() && rows == oracle.snapshot(),
        label + ": committed snapshot differs from the independent reference session");
}

void apply_and_compare(QuerySession& session, reference::Session& oracle,
                       const InputEvent& input, const std::string& label) {
  const auto expected_epoch = oracle.apply(input.update);
  std::set<SignedKey> expected;
  for (const auto& row : expected_epoch.delta.added)
    expected.emplace(SetOperation::insert, row);
  for (const auto& row : expected_epoch.delta.removed)
    expected.emplace(SetOperation::erase, row);

  check(session.begin_next_result() == SessionBegin::pending,
        label + ": admitted typed event did not create an epoch");
  check(session.status().pending_sequence == input.update.sequence &&
            session.progress().sequence + 1 == input.update.sequence,
        label + ": pending event was acknowledged before commit");
  step_to_prepared(session, label);
  session.commit();
  check(collect_epoch_output(session, label) == expected,
        label + ": signed output differs from independent before/after evaluation");
  if (input.source_position) {
    const auto progress = session.progress();
    const auto position = progress.source_positions.find(input.source_position->source);
    check(position != progress.source_positions.end() &&
              position->second == input.source_position->offset,
          label + ": source position was not committed with its input barrier");
  }
  check_snapshot(session, oracle, input.update.sequence, label);
}

void run_typed_oracle_case(const std::string& label, PhysicalPlan plan,
                           Database initial,
                           std::vector<std::vector<InputEvent>> partitions) {
  SessionOptions options;
  options.delta.mode = DeltaMode::delta;
  auto session = QuerySession::create_typed(
      plan, initial, generous_queue_limits(), options);
  reference::Session oracle(plan.source_catalog(), plan.query(), initial);
  check_snapshot(*session, oracle, 0, label + " initial typed snapshot");

  std::vector<InputEvent> flattened;
  for (auto& part : partitions) {
    for (const auto& item : part) flattened.push_back(item);
    auto offered = batch(std::move(part));
    check(session->enqueue(offered) == Admission::accepted && offered.empty(),
          label + ": ordinary nonempty typed batch was not admitted");
  }
  session->start();
  for (const auto& input : flattened)
    apply_and_compare(*session, oracle, input,
                      label + " sequence " + std::to_string(input.update.sequence));
  session->finish_input();
  check(session->begin_next_result() == SessionBegin::end &&
            session->status().end_of_input,
        label + ": drained typed batches did not end at explicit finish");
  check_snapshot(*session, oracle, oracle.sequence(), label + " final snapshot");
}

void typed_session_nonblocking_finish_and_pause() {
  const auto plan = unary_plan();
  auto session = QuerySession::create_typed(plan);
  session->start();
  check(session->begin_next_result() == SessionBegin::would_block &&
            !session->status().end_of_input && session->progress().sequence == 0,
        "open empty typed input was mistaken for EOF");
  expect_code([&] { static_cast<void>(session->begin_next()); },
              "input_would_block", "blocking begin on open empty typed input");
  check(!session->status().end_of_input,
        "would-block begin marked typed input as finished");

  auto explicitly_finished_empty = QuerySession::create_typed(plan);
  explicitly_finished_empty->start();
  check(explicitly_finished_empty->begin_next_result() == SessionBegin::would_block,
        "fresh open typed input did not initially report would-block");
  explicitly_finished_empty->finish_input();
  check(explicitly_finished_empty->begin_next_result() == SessionBegin::end &&
            explicitly_finished_empty->status().end_of_input,
        "explicitly finishing an empty typed queue did not report EOF");

  auto no_op_batch = batch({});
  check(session->enqueue(no_op_batch) == Admission::accepted && no_op_batch.empty() &&
            session->begin_next_result() == SessionBegin::would_block,
        "empty batch admission created an event or implied EOF");

  auto first = batch({event(1, {n(5)})});
  check(session->enqueue(first) == Admission::accepted,
        "running typed session refused valid input admission");
  check(session->begin_next_result() == SessionBegin::pending,
        "newly admitted typed input did not wake the session");
  session->pause();
  auto while_paused = batch({event(2, {n(6)})});
  const auto retained_size = while_paused.size();
  expect_code([&] { static_cast<void>(session->enqueue(while_paused)); },
              "session_paused", "typed admission while paused");
  expect_code([&] { static_cast<void>(session->step()); },
              "session_paused", "typed stepping while paused");
  check(while_paused.size() == retained_size &&
            session->status().pending_sequence == 1 && session->progress().sequence == 0,
        "paused admission or stepping changed the pending input");
  session->start();
  step_to_prepared(*session, "resumed typed epoch");
  session->commit();
  static_cast<void>(collect_epoch_output(*session, "resumed typed epoch"));
  session->finish_input();
  check(session->begin_next_result() == SessionBegin::end &&
            session->status().end_of_input,
        "finished typed input did not report EOF after its accepted prefix");
  auto after_finish = batch({event(2, {n(6)})});
  expect_code([&] { static_cast<void>(session->enqueue(after_finish)); },
              "input_closed", "enqueue after typed finish");
  check(after_finish.size() == 1,
        "closed-input rejection consumed the caller's batch");
}

void typed_epochs_match_reference_with_projection_aliases_and_types() {
  auto projected = ignored_projection_plan();
  Database initial_projected;
  initial_projected.tables.resize(1);
  initial_projected.tables[0].insert({n(0), n(50)});
  run_typed_oracle_case("ignored-column projection", std::move(projected),
      std::move(initial_projected), {
        {event(1, {n(7), n(10)}, SetOperation::insert, SourcePosition{"pairs", 1}),
         event(2, {n(7), n(11)}, SetOperation::insert, SourcePosition{"pairs", 2})},
        {event(3, {n(7), n(10)}, SetOperation::erase, SourcePosition{"pairs", 3})},
        {event(4, {n(7), n(11)}, SetOperation::erase, SourcePosition{"pairs", 4}),
         event(5, {n(7), n(11)}, SetOperation::insert, SourcePosition{"pairs", 5})}});

  auto joined = self_join_plan();
  Database initial_join;
  initial_join.tables.resize(1);
  initial_join.tables[0].insert({n(0), n(1)});
  run_typed_oracle_case("multiple aliases in a self join", std::move(joined),
      std::move(initial_join), {
        {event(1, {n(1), n(2)}), event(2, {n(2), n(3)})},
        {event(3, {n(2), n(4)}), event(4, {n(8), n(2)})},
        {event(5, {n(2), n(3)}, SetOperation::erase)}});

  auto booleans = boolean_plan();
  Database initial_boolean;
  initial_boolean.tables.resize(1);
  run_typed_oracle_case("Boolean typed rows", std::move(booleans),
      std::move(initial_boolean), {
        {event(1, {true}), event(2, {false})},
        {event(3, {true}, SetOperation::erase)}});
}

void bad_initial_database_is_rejected() {
  auto plan = unary_plan();
  Database malformed;
  malformed.tables.resize(1);
  malformed.tables[0].insert({std::string("not an int64")});
  expect_code([&] {
    static_cast<void>(QuerySession::create_typed(
        plan, malformed, generous_queue_limits()));
  }, "invalid_update", "typed session initial database schema");
}

void run() {
  transport_batch_and_admission_limits();
  fifo_barriers_for_every_batch_partition();
  queue_sticky_validation_and_owned_rows();
  typed_session_nonblocking_finish_and_pause();
  typed_epochs_match_reference_with_projection_aliases_and_types();
  bad_initial_database_is_rejected();
}
}  // namespace

int main() {
  try {
    run();
    std::cout << "typed transport batch and session checks passed\n";
  } catch (const std::exception& failure) {
    std::cerr << failure.what() << '\n';
    return 1;
  }
  return 0;
}
