#include "crown/api/error.hpp"
#include "crown/frontend/bind.hpp"
#include "crown/frontend/normalize.hpp"
#include "crown/io/ingest.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/session.hpp"
#include "evaluator.hpp"

#include <algorithm>
#include <cstdint>
#include <functional>
#include <iostream>
#include <memory>
#include <optional>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <type_traits>
#include <utility>
#include <vector>

namespace {
using namespace crown;
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

template <class Action>
void run_case(const std::string& label, Action&& action) {
  try {
    std::forward<Action>(action)();
  } catch (const std::exception& failure) {
    throw std::runtime_error(label + ": " + failure.what());
  }
}

static_assert(!std::is_copy_constructible_v<QuerySession>);
static_assert(!std::is_copy_assignable_v<QuerySession>);
static_assert(!std::is_move_constructible_v<QuerySession>);
static_assert(!std::is_move_assignable_v<QuerySession>);

Value n(std::int64_t value) { return value; }

PhysicalPlan unary_plan() {
  const Catalog catalog{1, {{"unary", {{"x", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}},
                    {{"unary", TableId{0}, {VariableId{0}}}},
                    {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"unary", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan self_join_plan() {
  const Catalog catalog{1,
      {{"edge", {{"src", ScalarType::int64},
                  {"dst", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"z", ScalarType::int64},
                     {"y", ScalarType::int64}},
      {{"left", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"right", TableId{0}, {VariableId{1}, VariableId{2}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "z"},
       {VariableId{2}, "y"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"join", NodeKind::generalized, {VariableId{1}},
        {NodeId{1}, NodeId{2}}, {}, {}},
       {"left", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}},
       {"right", NodeKind::native, {VariableId{1}, VariableId{2}}, {}, 1, {}}},
      {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan projected_join_plan() {
  const Catalog catalog{1,
      {{"r", {{"a", ScalarType::int64}, {"x", ScalarType::int64}}},
       {"s", {{"x", ScalarType::int64}, {"z", ScalarType::int64}}}}};
  const Query query{{{"a", ScalarType::int64}, {"x", ScalarType::int64},
                     {"z", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"s", TableId{1}, {VariableId{1}, VariableId{2}}}},
      {{VariableId{0}, "a"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}, VariableId{1}},
        {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, {VariableId{1}, VariableId{2}}, {}, 1, {}}},
      {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan deep_chain_plan() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}},
       {"s", {{"y", ScalarType::int64}, {"z", ScalarType::int64}}},
       {"t", {{"z", ScalarType::int64}, {"w", ScalarType::int64}}},
       {"u", {{"w", ScalarType::int64}, {"q", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64},
                     {"z", ScalarType::int64}, {"w", ScalarType::int64},
                     {"q", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"s", TableId{1}, {VariableId{1}, VariableId{2}}},
       {"t", TableId{2}, {VariableId{2}, VariableId{3}}},
       {"u", TableId{3}, {VariableId{3}, VariableId{4}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "y"},
       {VariableId{2}, "z"}, {VariableId{3}, "w"},
       {VariableId{4}, "q"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}, VariableId{1}},
        {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, {VariableId{1}, VariableId{2}},
        {NodeId{2}}, 1, {}},
       {"t", NodeKind::native, {VariableId{2}, VariableId{3}},
        {NodeId{3}}, 2, {}},
       {"u", NodeKind::native, {VariableId{3}, VariableId{4}}, {}, 3, {}}},
      {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan projected_source_plan() {
  const Catalog catalog{1,
      {{"source", {{"x", ScalarType::int64},
                    {"payload", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"payload", ScalarType::int64}},
      {{"source", TableId{0}, {VariableId{0}, VariableId{1}}}},
      {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"source", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}}},
      {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan repeated_column_plan() {
  const Catalog catalog{1,
      {{"pair", {{"first", ScalarType::int64},
                  {"second", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}},
      {{"pair", TableId{0}, {VariableId{0}, VariableId{0}}}},
      {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"pair", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan boolean_column_plan() {
  const Catalog catalog{1,
      {{"flags", {{"enabled", ScalarType::boolean}}}}};
  const Query query{{{"enabled", ScalarType::boolean}},
      {{"flags", TableId{0}, {VariableId{0}}}},
      {{VariableId{0}, "enabled"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"flags", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan nullary_plan() {
  const Catalog catalog{1,
      {{"unary", {{"x", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}},
      {{"unary", TableId{0}, {VariableId{0}}}}, {}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"unary", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan constant_nullary_plan(bool truth) {
  const Catalog catalog{1, {}};
  const Query query{{}, {}, {}, !truth};
  return planner::lower_tree(catalog, query, FreeConnexTree{});
}

PhysicalPlan exists_plan() {
  const Catalog catalog{19, {{"r", {{"x", ScalarType::int64}}}}};
  const auto binding = frontend::bind_sql(
      "SELECT EXISTS(SELECT NULL FROM r)", catalog);
  if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&binding))
    throw std::runtime_error(failure->diagnostic.code + ": " +
                             failure->diagnostic.message);
  auto normalized = frontend::normalize_sql(std::get<frontend::BoundSql>(binding));
  if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&normalized))
    throw std::runtime_error(failure->diagnostic.code + ": " +
                             failure->diagnostic.message);
  auto program = std::get<frontend::NormalizedSql>(std::move(normalized));
  const FreeConnexTree tree{NodeId{0},
      {{program.core.atoms.at(0).occurrence, NodeKind::native, {}, {}, 0, {}}},
      {}, {}};
  return planner::lower_normalized(program, tree);
}

QuerySession::Owner create_session(
    PhysicalPlan plan, std::string input, SessionOptions options = {}) {
  return QuerySession::create(std::move(plan),
      std::make_unique<std::istringstream>(std::move(input)), std::move(options));
}

std::string json_record(const PhysicalPlan& plan, std::uint64_t sequence,
                        TableId table, Row values,
                        SetOperation operation = SetOperation::insert,
                        std::optional<io::SourcePosition> position = std::nullopt) {
  io::InputEvent event{
      PhysicalSetUpdate{sequence, table, operation, std::move(values)},
      std::move(position)};
  return io::write_input_json(event, plan.source_catalog()) + "\n";
}

struct Event {
  TableId table;
  Row values;
  SetOperation operation = SetOperation::insert;
};

std::string json_trace(const PhysicalPlan& plan, const std::vector<Event>& events,
                       std::uint64_t first_offset = 100) {
  std::string text;
  for (std::size_t i = 0; i < events.size(); ++i) {
    text += json_record(plan, i + 1, events[i].table, events[i].values,
        events[i].operation,
        io::SourcePosition{"feed", first_offset + static_cast<std::uint64_t>(i) * 10});
  }
  return text;
}

Relation a04(const PhysicalPlan& plan, const Database& database) {
  return reference::evaluate(plan.source_catalog(), plan.query(), database);
}

std::set<SignedKey> signed_difference(const Relation& before,
                                     const Relation& after) {
  std::set<SignedKey> result;
  for (const auto& row : after)
    if (!before.contains(row)) result.emplace(SetOperation::insert, row);
  for (const auto& row : before)
    if (!after.contains(row)) result.emplace(SetOperation::erase, row);
  return result;
}

Database after_update(const Database& before, const PhysicalSetUpdate& update) {
  auto result = before;
  auto& rows = result.tables.at(update.table.value);
  if (update.operation == SetOperation::insert)
    static_cast<void>(rows.insert(update.values));
  else
    static_cast<void>(rows.erase(update.values));
  return result;
}

std::set<SignedKey> collect_output(QuerySession& session,
                                   const std::string& label) {
  std::set<SignedKey> result;
  std::uint64_t ordinal = 0;
  while (auto record = session.next_output()) {
    check(record->ordinal == ++ordinal,
          label + ": output ordinals are not contiguous from one");
    check(result.emplace(record->operation, crown::storage::export_row(record->tuple.values())).second,
          label + ": duplicate signed row escaped the session");
  }
  return result;
}

void step_to_prepared(QuerySession& session, const std::string& label) {
  std::size_t calls = 0;
  while (session.status().phase != SessionPhase::prepared) {
    static_cast<void>(session.step());
    check(++calls < 100000,
          label + ": private epoch did not reach prepared state");
  }
}

void check_snapshot_against_a04(QuerySession& session, const PhysicalPlan& plan,
                                const Database& database,
                                std::uint64_t sequence,
                                const std::string& label) {
  const auto snapshot = session.snapshot();
  std::set<Row> observed;
  for (const auto& tuple : snapshot.rows) {
    check(tuple.layout().same_token(snapshot.layout),
          label + ": snapshot tuple does not own the advertised result layout");
    check(observed.insert(crown::storage::export_row(tuple.values())).second,
          label + ": snapshot emitted a duplicate result row");
  }
  check(snapshot.sequence == sequence && snapshot.progress.sequence == sequence &&
            snapshot.progress == session.progress(),
        label + ": snapshot sequence or accepted source progress is stale");
  check(observed == a04(plan, database),
        label + ": committed session snapshot differs from independent A04");
}

void apply_epoch_and_check(QuerySession& session, const PhysicalPlan& plan,
                           Database& database,
                           const PhysicalSetUpdate& update,
                           const std::string& label) {
  const auto before = a04(plan, database);
  auto after = after_update(database, update);
  const auto expected = signed_difference(before, a04(plan, after));
  check(session.begin_next(), label + ": expected another input event");
  check(session.status().pending_sequence == update.sequence,
        label + ": pending status does not name the decoded event");
  step_to_prepared(session, label);
  session.commit();
  const auto actual = collect_output(session, label);
  check(actual == expected,
        label + ": public signed output differs from A04 before/after difference");
  database = std::move(after);
  check_snapshot_against_a04(session, plan, database, update.sequence,
                             label + " committed snapshot");
}

struct LifecycleScenario {
  std::string label;
  PhysicalPlan plan;
  std::vector<Event> events;
};

LifecycleScenario self_join_scenario() {
  return {"self join", self_join_plan(),
      {{TableId{0}, {n(1), n(2)}},
       {TableId{0}, {n(3), n(2)}},
       {TableId{0}, {n(2), n(9)}},
       {TableId{0}, {n(8), n(9)}}}};
}

LifecycleScenario projected_scenario() {
  return {"projected join", projected_join_plan(),
      {{TableId{0}, {n(1), n(7)}},
       {TableId{0}, {n(2), n(7)}},
       {TableId{1}, {n(7), n(10)}},
       {TableId{1}, {n(7), n(11)}}}};
}

LifecycleScenario deep_chain_scenario() {
  return {"deep chain", deep_chain_plan(),
      {{TableId{0}, {n(1), n(7)}},
       {TableId{0}, {n(2), n(7)}},
       {TableId{1}, {n(7), n(8)}},
       {TableId{2}, {n(8), n(10)}},
       {TableId{3}, {n(10), n(100)}},
       {TableId{3}, {n(10), n(101)}}}};
}

void pause_after_each_core_result(const LifecycleScenario& scenario) {
  auto options = SessionOptions{};
  options.delta.mode = DeltaMode::delta;
  auto input = json_trace(scenario.plan, scenario.events);
  auto session = create_session(scenario.plan, std::move(input), options);
  Database database;
  database.tables.resize(scenario.plan.source_catalog().tables.size());
  session->start();

  const auto target_index = scenario.events.size() - 2;
  for (std::size_t i = 0; i < target_index; ++i) {
    const auto& event = scenario.events[i];
    const PhysicalSetUpdate update{static_cast<std::uint64_t>(i + 1), event.table,
                                   event.operation, event.values};
    apply_epoch_and_check(*session, scenario.plan, database, update,
                          scenario.label + " seed " + std::to_string(i + 1));
  }

  const auto& target = scenario.events[target_index];
  const PhysicalSetUpdate update{static_cast<std::uint64_t>(target_index + 1),
                                 target.table, target.operation, target.values};
  const auto expected = signed_difference(a04(scenario.plan, database),
      a04(scenario.plan, after_update(database, update)));
  check(expected.size() >= 2,
        scenario.label + ": fixture does not create a multi-row answer change");
  check(session->begin_next(), scenario.label + ": target event is missing");
  const auto committed_progress = session->progress();
  check(session->status().pending_sequence == update.sequence &&
            committed_progress.sequence == target_index,
        scenario.label + ": input acknowledgement occurred before commit");

  std::size_t accepted = 0;
  std::size_t calls = 0;
  while (session->status().phase != SessionPhase::prepared) {
    const auto result = session->step();
    ++calls;
    check(calls < 100000, scenario.label + ": target did not prepare");
    if (result != DeltaStep::core_result) continue;
    ++accepted;
    check(session->status().committed_sequence == target_index &&
              session->progress() == committed_progress,
          scenario.label + ": private core result advanced public progress");
    session->pause();
    const auto paused = session->status();
    check(paused.state == SessionState::paused &&
              (paused.phase == SessionPhase::paused_pending ||
               paused.phase == SessionPhase::prepared),
          scenario.label + ": pause did not retain its private D06 phase");
    expect_code([&] { static_cast<void>(session->snapshot()); },
                "session_pending_epoch", scenario.label + " snapshot while private");
    expect_code([&] { static_cast<void>(session->next_output()); },
                "session_pending_epoch", scenario.label + " output while private");
    expect_code([&] { static_cast<void>(session->begin_next()); },
                "session_paused", scenario.label + " begin while paused");
    session->pause();
    session->start();
    check(session->status().state == SessionState::running,
          scenario.label + ": start did not resume a paused D06 epoch");
  }
  check(accepted == expected.size(),
        scenario.label + ": core-result prefixes differ from A04 change count");
  session->commit();
  check(collect_output(*session, scenario.label + " paused prefixes") == expected,
        scenario.label + ": resumed output differs from A04");
  database = after_update(database, update);
  check_snapshot_against_a04(*session, scenario.plan, database, update.sequence,
                             scenario.label + " after paused commit");

  check(session->status().phase == SessionPhase::ready &&
            session->status().output_remaining == 0,
        scenario.label + ": consuming output did not return to ready");
  check(session->begin_next(), scenario.label + ": following event was not preserved");
  check(session->status().pending_sequence == target_index + 2,
        scenario.label + ": session did not retain the next input after commit");
  session->stop();
  check(session->progress().sequence == update.sequence,
        scenario.label + ": stopping private next input acknowledged it");
}

void control_state_and_phase_matrix() {
  const auto plan = unary_plan();
  Database empty_database;
  empty_database.tables.resize(plan.source_catalog().tables.size());
  auto created = create_session(plan, "");
  const auto initial = created->status();
  check(initial.state == SessionState::created &&
            initial.phase == SessionPhase::ready &&
            initial.committed_sequence == 0 && !initial.input_failed &&
            !initial.end_of_input && !initial.pending_sequence &&
            initial.pending_work == 0 && initial.output_remaining == 0,
        "new session did not expose the empty created/ready state");
  check(created->progress() == io::InputProgress{},
        "new session progress did not start at sequence zero");
  check_snapshot_against_a04(*created, plan, empty_database, 0,
                             "empty created session");
  expect_code([&] { created->pause(); }, "session_not_started", "pause created");
  expect_code([&] { static_cast<void>(created->begin_next()); },
              "session_not_started", "begin created");
  expect_code([&] { static_cast<void>(created->step()); },
              "session_not_started", "step created");
  expect_code([&] { created->commit(); },
              "session_not_started", "commit created");
  expect_code([&] { created->start_drain(); },
              "session_not_started", "start drain created");
  expect_code([&] { created->drain(); },
              "session_not_started", "drain created");
  expect_code([&] { static_cast<void>(created->next_output()); },
              "session_not_started", "output created");

  created->start();
  created->start();
  check(created->status().state == SessionState::running,
        "start is not idempotent while running");
  check(!created->begin_next() && created->status().end_of_input,
        "empty input did not report a validated EOF");
  check(!created->begin_next() && created->status().end_of_input,
        "validated EOF was not stable on repeated begin");
  check(!created->next_output(), "ready session returned an output row");
  check(created->status().phase == SessionPhase::ready,
        "empty output changed the ready phase");
  expect_code([&] { static_cast<void>(created->step()); },
              "session_no_pending_epoch", "step running without pending input");
  expect_code([&] { created->commit(); },
              "session_no_pending_epoch", "commit running without pending input");
  expect_code([&] { created->start_drain(); },
              "session_no_pending_epoch", "start drain without pending input");
  check(!created->next_output(), "running ready session returned output");
  // Ready draining is explicitly idempotent, including an empty input.
  created->drain();
  created->pause();
  created->pause();
  check(created->status().state == SessionState::paused,
        "pause is not idempotent while paused");
  expect_code([&] { created->start_drain(); },
              "session_no_pending_epoch", "start drain paused without pending input");
  check(!created->next_output(), "paused ready session returned output");
  expect_code([&] { static_cast<void>(created->begin_next()); },
              "session_paused", "begin paused");
  expect_code([&] { static_cast<void>(created->step()); },
              "session_paused", "step paused ready");
  expect_code([&] { created->commit(); }, "session_paused", "commit paused ready");
  created->start();
  check(created->status().state == SessionState::running,
        "start did not resume a non-pending pause");

  created->stop();
  created->stop();
  check(created->status().state == SessionState::stopped,
        "stop is not idempotent or failed to become terminal");
  check(created->progress() == io::InputProgress{},
        "stop did not retain accepted progress");
  check_snapshot_against_a04(*created, plan, empty_database, 0,
                             "stopped empty session");
  expect_code([&] { created->start(); }, "session_stopped", "start stopped");
  expect_code([&] { created->pause(); }, "session_stopped", "pause stopped");
  expect_code([&] { static_cast<void>(created->begin_next()); },
              "session_stopped", "begin stopped");
  expect_code([&] { static_cast<void>(created->step()); },
              "session_stopped", "step stopped");
  expect_code([&] { created->commit(); }, "session_stopped", "commit stopped");
  expect_code([&] { created->start_drain(); },
              "session_stopped", "start drain stopped");
  expect_code([&] { created->drain(); }, "session_stopped", "drain stopped");
  expect_code([&] { static_cast<void>(created->next_output()); },
              "session_stopped", "output stopped");

  created->drop();
  created->drop();
  created->stop();
  check(created->status().state == SessionState::dropped &&
            created->status().committed_sequence == 0 &&
            created->status().output_remaining == 0,
        "drop did not retain its tombstone status or was not idempotent");
  expect_code([&] { static_cast<void>(created->progress()); },
              "session_dropped", "progress dropped");
  expect_code([&] { static_cast<void>(created->snapshot()); },
              "session_dropped", "snapshot dropped");
  expect_code([&] { created->start(); }, "session_dropped", "start dropped");
  expect_code([&] { created->pause(); }, "session_dropped", "pause dropped");
  expect_code([&] { static_cast<void>(created->begin_next()); },
              "session_dropped", "begin dropped");
  expect_code([&] { static_cast<void>(created->step()); },
              "session_dropped", "step dropped");
  expect_code([&] { created->commit(); }, "session_dropped", "commit dropped");
  expect_code([&] { created->start_drain(); },
              "session_dropped", "start drain dropped");
  expect_code([&] { created->drain(); }, "session_dropped", "drain dropped");
  expect_code([&] { static_cast<void>(created->next_output()); },
              "session_dropped", "output dropped");
}

void private_phase_guards_and_draining() {
  const auto plan = unary_plan();
  const std::vector<Event> events{{TableId{0}, {n(7)}},
                                  {TableId{0}, {n(8)}},
                                  {TableId{0}, {n(9)}}};
  auto options = SessionOptions{};
  options.delta.mode = DeltaMode::delta;
  auto session = create_session(plan, json_trace(plan, events), options);
  Database database;
  database.tables.resize(1);

  session->start();
  check(session->begin_next(), "first private-phase input is missing");
  check(session->status().phase == SessionPhase::pending &&
            session->status().pending_sequence == 1,
        "begin_next did not establish the pending phase");
  const auto committed = session->progress();
  expect_code([&] { static_cast<void>(session->begin_next()); },
              "session_pending_epoch", "begin with pending epoch");
  expect_code([&] { static_cast<void>(session->next_output()); },
              "session_pending_epoch", "output with pending epoch");
  expect_code([&] { static_cast<void>(session->snapshot()); },
              "session_pending_epoch", "snapshot with pending epoch");
  expect_code([&] { session->commit(); },
              "session_epoch_not_prepared", "commit pending epoch");
  check(session->progress() == committed,
        "failed pending-phase calls changed accepted progress");

  session->pause();
  check(session->status().state == SessionState::paused &&
            session->status().phase == SessionPhase::paused_pending,
        "pause did not pause the real pending D06 epoch");
  expect_code([&] { static_cast<void>(session->step()); },
              "session_paused", "step paused pending epoch");
  session->start();
  check(session->status().state == SessionState::running &&
            session->status().phase == SessionPhase::pending,
        "start did not resume a paused pending D06 epoch");
  step_to_prepared(*session, "first private epoch");
  check(session->status().phase == SessionPhase::prepared,
        "pending work did not expose its prepared phase");
  check(session->step() == DeltaStep::prepared,
        "step on prepared epoch was not idempotent");
  session->pause();
  check(session->status().state == SessionState::paused &&
            session->status().phase == SessionPhase::prepared,
        "pause did not act as a control pause in prepared phase");
  expect_code([&] { session->commit(); }, "session_paused",
              "commit control-paused prepared epoch");
  session->start();
  session->start_drain();
  check(session->status().phase == SessionPhase::prepared,
        "start_drain did not keep a prepared epoch in its prepared phase");
  session->drain();
  check(session->status().state == SessionState::running &&
            session->status().phase == SessionPhase::ready &&
            session->status().committed_sequence == 1 &&
            session->status().output_remaining == 0,
        "drain did not commit and discard the current prepared epoch");
  database = after_update(database,
      PhysicalSetUpdate{1, TableId{0}, SetOperation::insert, {n(7)}});
  check_snapshot_against_a04(*session, plan, database, 1,
                             "drained first epoch");
  check(session->progress().sequence == 1,
        "drain did not acknowledge exactly the committed input");
  check(!session->next_output(),
        "drain exposed output after applying the discard policy");

  check(session->begin_next(), "second input was lost while draining");
  check(session->status().pending_sequence == 2,
        "drain read beyond the current input epoch");
  session->pause();
  check(session->status().phase == SessionPhase::paused_pending,
        "pause in a second pending epoch did not retain its D06 state");
  session->start_drain();
  check(session->status().state == SessionState::paused &&
            session->status().phase == SessionPhase::draining,
        "start_drain failed to preserve control-paused admission");
  session->start();
  check(session->status().state == SessionState::running &&
            session->status().phase == SessionPhase::draining,
        "start after start_drain tried to resume a non-paused D06 token");
  session->pause();
  check(session->status().state == SessionState::paused &&
            session->status().phase == SessionPhase::draining,
        "pause while draining changed the D06 draining phase");
  expect_code([&] { static_cast<void>(session->step()); },
              "session_paused", "step while control-paused and draining");
  session->drain();
  check(session->status().state == SessionState::paused &&
            session->status().phase == SessionPhase::ready &&
            session->progress().sequence == 2,
        "draining paused work did not leave admission paused after commit");
  expect_code([&] { static_cast<void>(session->begin_next()); },
              "session_paused", "begin after paused drain");
  session->start();
  check(session->begin_next(), "drain consumed the next event in the stream");
  check(session->status().pending_sequence == 3,
        "session did not resume at the event after the drained epoch");
  session->stop();
  check(session->progress().sequence == 2,
        "stop acknowledged the private event after drain");
}

void output_snapshot_and_limits() {
  const auto plan = unary_plan();
  const auto line = json_record(plan, 1, TableId{0}, {n(42)},
                                SetOperation::insert,
                                io::SourcePosition{"one", 6});
  auto session = create_session(plan, line);
  SnapshotLimits empty_only;
  empty_only.rows = 0;
  empty_only.bytes = 0;
  const auto empty = session->snapshot(empty_only);
  check(empty.rows.empty() && empty.sequence == 0 && empty.accounted_bytes == 0,
        "zero-row/zero-byte limits did not admit an empty snapshot");
  session->start();
  Database database;
  database.tables.resize(1);
  const PhysicalSetUpdate update{1, TableId{0}, SetOperation::insert, {n(42)}};
  check(session->begin_next(), "snapshot fixture input is missing");
  step_to_prepared(*session, "snapshot fixture");
  session->commit();
  auto after = after_update(database, update);
  const auto pending_output_snapshot = session->snapshot();
  check(pending_output_snapshot.sequence == 1 &&
            pending_output_snapshot.rows.size() == 1 &&
            pending_output_snapshot.rows.front().values() == Row{n(42)},
        "snapshot during unread output did not return committed results");
  check_snapshot_against_a04(*session, plan, after, 1,
                             "snapshot while output remains");
  expect_code([&] { static_cast<void>(session->snapshot(empty_only)); },
              "resource_limit", "zero-row snapshot over nonempty answer");
  auto no_bytes = SnapshotLimits{};
  no_bytes.bytes = 0;
  expect_code([&] { static_cast<void>(session->snapshot(no_bytes)); },
              "resource_limit", "zero-byte snapshot over retained answer");
  check(pending_output_snapshot.accounted_bytes > 0,
        "nonempty owning snapshot did not account for retained rows");

  auto configured_limits = SessionOptions{};
  configured_limits.snapshot = empty_only;
  auto configured = create_session(plan, line, configured_limits);
  configured->start();
  check(configured->begin_next(), "configured-limit snapshot input is missing");
  step_to_prepared(*configured, "configured-limit snapshot");
  configured->commit();
  expect_code([&] { static_cast<void>(configured->snapshot()); },
              "resource_limit", "SessionOptions default snapshot limit");
  check(configured->snapshot(SnapshotLimits{}).rows.size() == 1,
        "per-call snapshot limits did not override SessionOptions.snapshot");
  configured->stop();

  session->pause();
  check(session->status().state == SessionState::paused &&
            session->status().phase == SessionPhase::output,
        "pause in output changed or discarded the committed output phase");
  expect_code([&] { static_cast<void>(session->begin_next()); },
              "session_paused", "begin while output is control-paused");
  const auto output = session->next_output();
  check(output && output->operation == SetOperation::insert &&
            output->tuple.values() == Row{n(42)},
        "paused session output did not own the expected inserted result");
  check(!session->next_output() &&
            session->status().phase == SessionPhase::ready &&
            session->status().state == SessionState::paused,
        "exhausting committed output did not retain paused admission");
  session->start();
  session->stop();
  check_snapshot_against_a04(*session, plan, after, 1,
                             "snapshot after stop");
  session->drop();
  check(pending_output_snapshot.rows.size() == 1 &&
            pending_output_snapshot.rows.front().values() == Row{n(42)} &&
            pending_output_snapshot.layout.fields().size() == 1 &&
            output && output->tuple.values() == Row{n(42)},
        "a returned snapshot did not own its rows/layout across drop");
}

void drain_committed_output_without_reading_next_input() {
  const auto plan = unary_plan();
  const std::vector<Event> events{{TableId{0}, {n(1)}},
                                  {TableId{0}, {n(2)}}};
  auto session = create_session(plan, json_trace(plan, events));
  session->start();
  Database database;
  database.tables.resize(1);
  const PhysicalSetUpdate first{1, TableId{0}, SetOperation::insert, {n(1)}};
  const auto expected = signed_difference(a04(plan, database),
      a04(plan, after_update(database, first)));
  check(expected == std::set<SignedKey>{{SetOperation::insert, {n(1)}}},
        "output drain fixture A04 oracle does not yield its inserted row");
  check(session->begin_next(), "output drain fixture has no first input");
  step_to_prepared(*session, "output drain first event");
  session->commit();
  database = after_update(database, first);
  check(session->status().phase == SessionPhase::output &&
            session->status().output_remaining == expected.size(),
        "output drain fixture did not retain its first result");
  expect_code([&] { static_cast<void>(session->begin_next()); },
              "session_output_pending", "begin while output retained");
  expect_code([&] { static_cast<void>(session->step()); },
              "session_no_pending_epoch", "step while output retained");
  expect_code([&] { session->commit(); },
              "session_no_pending_epoch", "commit while output retained");
  expect_code([&] { session->start_drain(); },
              "session_no_pending_epoch", "start drain while output retained");
  session->drain();
  check(session->status().phase == SessionPhase::ready &&
            session->status().output_remaining == 0 &&
            session->progress().sequence == 1,
        "drain did not discard only the committed output artifact");
  check_snapshot_against_a04(*session, plan, database, 1,
                             "committed result after output drain");
  check(session->begin_next() && session->status().pending_sequence == 2,
        "output drain read or discarded the following input event");
  session->stop();
  check(session->progress().sequence == 1,
        "stop acknowledged the event after the output drain");
}

void projection_noop_filter_and_source_progress() {
  const auto plan = projected_source_plan();
  const std::vector<Event> events{
      {TableId{0}, {n(1), n(10)}},
      {TableId{0}, {n(1), n(11)}},  // New physical row, same projected answer.
      {TableId{0}, {n(1), n(10)}},  // Set no-op.
      {TableId{0}, {n(2), n(20)}, SetOperation::erase},  // Delete no-op.
      {TableId{0}, {n(2), n(20)}}};
  auto options = SessionOptions{};
  options.delta.mode = DeltaMode::delta;
  auto session = create_session(plan, json_trace(plan, events), options);
  session->start();
  Database database;
  database.tables.resize(1);
  for (std::size_t i = 0; i < events.size(); ++i) {
    const auto& event = events[i];
    const PhysicalSetUpdate update{static_cast<std::uint64_t>(i + 1),
        event.table, event.operation, event.values};
    apply_epoch_and_check(*session, plan, database, update,
                          "projection/no-op event " + std::to_string(i + 1));
    const auto progress = session->progress();
    check(progress.sequence == i + 1 &&
              progress.source_positions.at("feed") == 100 + i * 10,
          "accepted sequence/source offset did not advance with committed event");
  }

  const auto filtered_plan = repeated_column_plan();
  auto filtered = create_session(filtered_plan,
      json_record(filtered_plan, 1, TableId{0}, {n(4), n(9)},
                  SetOperation::insert, io::SourcePosition{"filter", 500}),
      options);
  filtered->start();
  Database filtered_database;
  filtered_database.tables.resize(1);
  const PhysicalSetUpdate filtered_event{1, TableId{0}, SetOperation::insert,
                                        {n(4), n(9)}};
  apply_epoch_and_check(*filtered, filtered_plan, filtered_database,
                        filtered_event, "filtered repeated-column event");
  check(filtered->progress().sequence == 1 &&
            filtered->progress().source_positions.at("filter") == 500,
        "filtered input did not commit its sequence and source position");
}

void maintenance_mode_keeps_results_without_delta_output() {
  const auto plan = unary_plan();
  const std::vector<Event> events{{TableId{0}, {n(12)}},
                                  {TableId{0}, {n(13)}}};
  auto options = SessionOptions{};
  options.delta.mode = DeltaMode::maintenance;
  auto session = create_session(plan, json_trace(plan, events), options);
  session->start();
  Database database;
  database.tables.resize(1);
  for (std::size_t i = 0; i < events.size(); ++i) {
    const auto& event = events[i];
    const PhysicalSetUpdate update{static_cast<std::uint64_t>(i + 1),
        event.table, event.operation, event.values};
    check(session->begin_next(), "maintenance-mode input event is missing");
    step_to_prepared(*session, "maintenance-mode event");
    session->commit();
    check(collect_output(*session, "maintenance-mode output").empty(),
          "maintenance-only session published delta output");
    database = after_update(database, update);
    check_snapshot_against_a04(*session, plan, database, update.sequence,
                               "maintenance-mode committed result");
  }
}

void scalar_exists_boolean_and_nullary_snapshots() {
  const auto exists = exists_plan();
  const std::vector<Event> exists_events{
      {TableId{0}, {n(5)}},
      {TableId{0}, {n(5)}, SetOperation::erase}};
  auto session = create_session(exists, json_trace(exists, exists_events));
  auto empty = session->snapshot();
  check(empty.sequence == 0 && empty.rows.size() == 1 &&
            empty.rows.front().values() == Row{Value{false}},
        "epoch-zero EXISTS snapshot omitted its actual scalar false result");
  SnapshotLimits no_rows;
  no_rows.rows = 0;
  no_rows.bytes = 0;
  expect_code([&] { static_cast<void>(session->snapshot(no_rows)); },
              "resource_limit", "zero-row limit for scalar EXISTS false");
  session->start();
  Database source;
  source.tables.resize(1);
  for (std::size_t i = 0; i < exists_events.size(); ++i) {
    const auto& event = exists_events[i];
    const PhysicalSetUpdate update{static_cast<std::uint64_t>(i + 1),
        event.table, event.operation, event.values};
    const bool before = !source.tables[0].empty();
    auto after = after_update(source, update);
    const bool after_value = !after.tables[0].empty();
    check(session->begin_next(), "EXISTS input event is missing");
    step_to_prepared(*session, "EXISTS epoch");
    session->commit();
    std::set<SignedKey> expected;
    if (before != after_value) {
      expected.emplace(SetOperation::erase, Row{Value{before}});
      expected.emplace(SetOperation::insert, Row{Value{after_value}});
    }
    check(collect_output(*session, "EXISTS scalar output") == expected,
          "EXISTS scalar output differs from its before/after truth transition");
    source = std::move(after);
    const auto snapshot = session->snapshot();
    check(snapshot.rows.size() == 1 &&
              snapshot.rows.front().values() == Row{Value{after_value}} &&
              snapshot.sequence == update.sequence,
          "EXISTS committed snapshot lost its true/false scalar row");
  }

  const auto boolean_plan = boolean_column_plan();
  auto boolean_session = create_session(boolean_plan,
      json_record(boolean_plan, 1, TableId{0}, {Value{true}}));
  check(boolean_session->snapshot().rows.empty(),
        "empty native Boolean query has an epoch-zero answer");
  boolean_session->start();
  Database bool_db;
  bool_db.tables.resize(1);
  apply_epoch_and_check(*boolean_session, boolean_plan, bool_db,
      PhysicalSetUpdate{1, TableId{0}, SetOperation::insert, {Value{true}}},
      "native Boolean result");
  check(boolean_session->snapshot().rows.front().values() == Row{Value{true}},
        "native Boolean result was not retained as a Boolean value");

  const auto nullary = nullary_plan();
  auto nullary_session = create_session(nullary,
      json_record(nullary, 1, TableId{0}, {n(99)}));
  check(nullary_session->snapshot().rows.empty(),
        "empty nullary CQ did not begin with an empty result");
  nullary_session->start();
  Database nullary_db;
  nullary_db.tables.resize(1);
  apply_epoch_and_check(*nullary_session, nullary, nullary_db,
      PhysicalSetUpdate{1, TableId{0}, SetOperation::insert, {n(99)}},
      "nullary result");
  const auto nullary_snapshot = nullary_session->snapshot();
  check(nullary_snapshot.rows.size() == 1 &&
            nullary_snapshot.rows.front().values().empty(),
        "nullary answer did not retain its actual empty tuple");

  auto true_constant = create_session(constant_nullary_plan(true), "");
  const auto true_at_zero = true_constant->snapshot();
  check(true_at_zero.sequence == 0 && true_at_zero.rows.size() == 1 &&
            true_at_zero.rows.front().values().empty(),
        "epoch-zero native nullary truth did not retain its empty tuple");
  auto false_constant = create_session(constant_nullary_plan(false), "");
  check(false_constant->snapshot().rows.empty(),
        "epoch-zero native nullary false query retained a row");

  auto core_options = SessionOptions{};
  core_options.delta.view = ResultView::core;
  auto core_exists = create_session(exists,
      json_record(exists, 1, TableId{0}, {n(5)}), core_options);
  check(core_exists->snapshot().rows.empty(),
        "core-view EXISTS snapshot exposed a SQL false scalar at sequence zero");
  core_exists->start();
  check(core_exists->begin_next(), "core-view EXISTS input event is missing");
  step_to_prepared(*core_exists, "core-view EXISTS epoch");
  core_exists->commit();
  check(collect_output(*core_exists, "core-view EXISTS delta") ==
            std::set<SignedKey>{{SetOperation::insert, Row{}}},
        "core-view EXISTS delta did not emit its nullary core insertion");
  const auto core_snapshot = core_exists->snapshot();
  check(core_snapshot.sequence == 1 && core_snapshot.rows.size() == 1 &&
            core_snapshot.rows.front().values().empty(),
        "core-view EXISTS snapshot did not expose the true nullary core row");
}

class TrackingStream final : public std::istringstream {
 public:
  TrackingStream(std::string text, bool& destroyed)
      : std::istringstream(std::move(text)), destroyed_(destroyed) {}
  ~TrackingStream() override { destroyed_ = true; }
 private:
  bool& destroyed_;
};

class ReentrantBuffer final : public std::streambuf {
 public:
  ReentrantBuffer(std::string text, std::function<void()> callback)
      : text_(std::move(text)), callback_(std::move(callback)) {}
 protected:
  int_type underflow() override {
    notify();
    if (position_ == text_.size()) return traits_type::eof();
    return traits_type::to_int_type(text_[position_]);
  }
  int_type uflow() override {
    const auto next = underflow();
    if (!traits_type::eq_int_type(next, traits_type::eof())) ++position_;
    return next;
  }
  std::streamsize xsgetn(char* destination, std::streamsize count) override {
    notify();
    if (count <= 0) return 0;
    const auto available = text_.size() - position_;
    const auto copied = std::min(available, static_cast<std::size_t>(count));
    std::copy_n(text_.data() + position_, copied, destination);
    position_ += copied;
    return static_cast<std::streamsize>(copied);
  }
 private:
  void notify() {
    if (!called_ && callback_) {
      called_ = true;
      callback_();
    }
  }
  std::string text_;
  std::size_t position_ = 0;
  std::function<void()> callback_;
  bool called_ = false;
};

class ReentrantStream final : public std::istream {
 public:
  ReentrantStream(std::string text, std::function<void()> callback)
      : std::istream(nullptr), buffer_(std::move(text), std::move(callback)) {
    rdbuf(&buffer_);
  }
 private:
  ReentrantBuffer buffer_;
};

void parser_stickiness_cleanup_and_retry() {
  const auto plan = unary_plan();
  bool destroyed = false;
  auto input = json_record(plan, 1, TableId{0}, {n(1)},
                           SetOperation::insert,
                           io::SourcePosition{"src", 10}) +
               "{\"schema_version\":\n";
  auto session = QuerySession::create(plan,
      std::make_unique<TrackingStream>(input, destroyed));
  session->start();
  Database database;
  database.tables.resize(1);
  apply_epoch_and_check(*session, plan, database,
      PhysicalSetUpdate{1, TableId{0}, SetOperation::insert, {n(1)}},
      "valid record before parser failure");
  bool parser_error = false;
  try {
    static_cast<void>(session->begin_next());
  } catch (const Error&) {
    parser_error = true;
  }
  check(parser_error && session->status().input_failed &&
            !session->status().end_of_input &&
            session->progress().sequence == 1,
        "parser error did not become sticky while preserving prior progress");
  expect_code([&] { static_cast<void>(session->begin_next()); },
              "input_failed", "repeat after parser error");
  check_snapshot_against_a04(*session, plan, database, 1,
                             "committed state after parser failure");
  session->stop();
  check(destroyed, "stop did not release the owned input stream");

  bool aborted_stream_destroyed = false;
  const std::vector<Event> events{{TableId{0}, {n(4)}},
                                  {TableId{0}, {n(5)}}};
  auto aborting = QuerySession::create(plan,
      std::make_unique<TrackingStream>(json_trace(plan, events),
                                      aborted_stream_destroyed));
  aborting->start();
  Database committed_db;
  committed_db.tables.resize(1);
  apply_epoch_and_check(*aborting, plan, committed_db,
      PhysicalSetUpdate{1, TableId{0}, SetOperation::insert, {n(4)}},
      "committed event before stop abort");
  check(aborting->begin_next(), "stop-abort fixture has no private second event");
  static_cast<void>(aborting->step());
  aborting->stop();
  check(aborting->status().state == SessionState::stopped &&
            aborting->status().committed_sequence == 1 &&
            aborting->progress().sequence == 1 &&
            aborting->status().pending_work == 0 &&
            aborting->status().output_remaining == 0 &&
            aborted_stream_destroyed,
        "stop did not abort private work, retain progress and release input");
  check_snapshot_against_a04(*aborting, plan, committed_db, 1,
                             "retained runtime after pending stop");

  auto spool_limited = SessionOptions{};
  spool_limited.delta.spool_row_limit = 0;
  auto retry = create_session(plan,
      json_record(plan, 1, TableId{0}, {n(17)}), spool_limited);
  retry->start();
  check(retry->begin_next(), "spool-limit retry fixture has no input");
  const auto fail_during_spooling = [&] {
    bool spool_error = false;
    try {
      std::size_t calls = 0;
      while (retry->status().phase != SessionPhase::prepared) {
        static_cast<void>(retry->step());
        check(++calls < 1000,
              "zero-row spool limit did not stop private output production");
      }
    } catch (const Error& failure) {
      check(failure.code() == "resource_limit",
            "spool failure returned an unexpected error code");
      spool_error = true;
    }
    check(spool_error, "zero-row spool limit did not reject its output row");
  };
  fail_during_spooling();
  check(!retry->status().input_failed &&
            retry->progress().sequence == 0,
        "spool failure was treated as parser failure or acknowledged input");
  check(retry->begin_next() && retry->status().pending_sequence == 1 &&
            retry->progress().sequence == 0,
        "spool failure did not retain the cached input for retry");
  fail_during_spooling();
  check(retry->progress().sequence == 0 && !retry->status().input_failed,
        "repeated spool failure changed accepted progress or parser state");
  retry->stop();
}

void output_stop_and_drop_tombstone() {
  const auto plan = unary_plan();
  bool destroyed = false;
  auto session = QuerySession::create(plan,
      std::make_unique<TrackingStream>(
          json_record(plan, 1, TableId{0}, {n(77)}), destroyed));
  session->start();
  Database database;
  database.tables.resize(1);
  const PhysicalSetUpdate update{1, TableId{0}, SetOperation::insert, {n(77)}};
  const auto after = after_update(database, update);
  check(session->begin_next(), "output-stop fixture has no input");
  step_to_prepared(*session, "output-stop fixture");
  session->commit();
  check(session->status().phase == SessionPhase::output &&
            session->status().output_remaining == 1,
        "committed output was not retained before stop");
  session->stop();
  check(destroyed && session->status().state == SessionState::stopped &&
            session->status().output_remaining == 0 &&
            session->status().phase == SessionPhase::ready,
        "stop did not destroy unread output and its input owner");
  check_snapshot_against_a04(*session, plan, after, 1,
                             "snapshot after unread-output stop");
  session->drop();
  check(session->status().state == SessionState::dropped &&
            session->status().committed_sequence == 1,
        "drop did not retain the committed sequence in its tombstone");
  expect_code([&] { static_cast<void>(session->progress()); },
              "session_dropped", "progress after committed drop");
  expect_code([&] { static_cast<void>(session->snapshot()); },
              "session_dropped", "snapshot after committed drop");
  session->stop();
  session->drop();
  check(session->status().state == SessionState::dropped &&
            session->status().committed_sequence == 1,
        "terminal stop/drop calls changed the dropped tombstone");
}

void creator_thread_and_stream_reentry() {
  const auto plan = unary_plan();
  auto session = create_session(plan,
      json_record(plan, 1, TableId{0}, {n(3)}));
  session->start();
  std::string wrong_thread_code;
  std::thread other([&] {
    try {
      static_cast<void>(session->status());
    } catch (const Error& failure) {
      wrong_thread_code = failure.code();
    }
  });
  other.join();
  check(wrong_thread_code == "session_wrong_thread",
        "creator-thread guard did not reject a cross-thread API call");

  auto reentrant_plan = unary_plan();
  std::string callback_error;
  QuerySession* session_pointer = nullptr;
  auto stream = std::make_unique<ReentrantStream>(
      json_record(reentrant_plan, 1, TableId{0}, {n(9)}), [&] {
        try {
          static_cast<void>(session_pointer->status());
        } catch (const Error& failure) {
          callback_error = failure.code();
        }
      });
  auto reentrant = QuerySession::create(std::move(reentrant_plan),
                                        std::move(stream));
  session_pointer = reentrant.get();
  reentrant->start();
  check(reentrant->begin_next(), "reentrant stream did not decode its event");
  check(callback_error == "session_busy",
        "owned stream callback was allowed to reenter the public session API");
  reentrant->stop();
}

void run() {
  run_case("control state and phase matrix", control_state_and_phase_matrix);
  run_case("private phases and draining", private_phase_guards_and_draining);
  run_case("output snapshots and limits", output_snapshot_and_limits);
  run_case("drain committed output", drain_committed_output_without_reading_next_input);
  run_case("projection, no-op, filter and progress",
           projection_noop_filter_and_source_progress);
  run_case("maintenance mode", maintenance_mode_keeps_results_without_delta_output);
  run_case("scalar EXISTS, Boolean and nullary snapshots",
           scalar_exists_boolean_and_nullary_snapshots);
  const auto self_join = self_join_scenario();
  const auto projected = projected_scenario();
  const auto deep_chain = deep_chain_scenario();
  for (const auto* scenario : {&self_join, &projected, &deep_chain})
    run_case(scenario->label + " pause at each core prefix", [&] {
      pause_after_each_core_result(*scenario);
    });
  run_case("parser failure, cleanup and retry",
           parser_stickiness_cleanup_and_retry);
  run_case("output stop and drop tombstone", output_stop_and_drop_tombstone);
  run_case("creator thread and stream reentry", creator_thread_and_stream_reentry);
}
}  // namespace

int main() {
  try {
    run();
    std::cout << "query session lifecycle, oracle, and ownership checks passed\n";
  } catch (const std::exception& failure) {
    std::cerr << failure.what() << '\n';
    return 1;
  }
  return 0;
}
