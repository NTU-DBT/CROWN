#include "crown/api/error.hpp"
#include "crown/frontend/bind.hpp"
#include "crown/frontend/normalize.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/delta.hpp"
#include "evaluator.hpp"
#include "native_input.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <initializer_list>
#include <map>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace {
using namespace crown;
using namespace crown::runtime;
using SignedKey = std::pair<SetOperation, Row>;

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

template <class Action>
void expect_error(Action&& action, const std::string& code,
                  const std::string& label) {
  try {
    action();
  } catch (const Error& failure) {
    check(failure.code() == code,
          label + ": expected " + code + ", got " + failure.code());
    return;
  }
  check(false, label + ": expected an error with code " + code);
}

Value n(std::int64_t value) { return value; }

VariableSet variables(std::initializer_list<std::size_t> values) {
  VariableSet result;
  for (const auto value : values) result.insert(VariableId{value});
  return result;
}

Relation a04(const auto& plan, const Database& database) {
  return reference::evaluate(reference::input::catalog(plan.catalog()), reference::input::query(plan.query()), database);
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

std::vector<Relation> a04_live(const auto& plan,
                               const Relation& answer) {
  std::map<VariableId, std::size_t> head_positions;
  for (std::size_t field = 0; field < plan.query().head.size(); ++field)
    head_positions.try_emplace(plan.query().head[field].variable, field);

  std::vector<Relation> result;
  result.reserve(plan.enumeration().steps.size());
  for (const auto& step : plan.enumeration().steps) {
    const auto& scope = plan.nodes().at(step.node.value).visible_scope;
    Relation factor;
    for (const auto& assignment : answer) {
      Row key;
      key.reserve(scope.size());
      for (const auto variable : scope) {
        const auto position = head_positions.find(variable);
        check(position != head_positions.end(),
              "A04 answer omits a variable from a visible E scope");
        key.push_back(assignment.at(position->second));
      }
      factor.insert(std::move(key));
    }
    result.push_back(std::move(factor));
  }
  return result;
}

std::set<SignedKey> collect(DeltaRuntime::Epoch& epoch,
                            const std::string& label) {
  std::set<SignedKey> rows;
  std::uint64_t ordinal = 0;
  while (auto record = epoch.next()) {
    check(record->ordinal == ++ordinal, label + ": non-contiguous ordinal");
    check(record->tuple.layout().same_token(epoch.layout()),
          label + ": output tuple changed layout");
    check(rows.emplace(record->operation, crown::storage::export_row(record->tuple.values())).second,
          label + ": duplicate signed output row");
  }
  check(epoch.remaining() == 0 && !epoch.active(),
        label + ": output consumption retained the epoch lease");
  check(!epoch.next(), label + ": exhausted output returned another row");
  return rows;
}

Relation collect_results(DeltaRuntime& runtime) {
  Relation result;
  auto cursor = runtime.results();
  while (auto tuple = cursor.next())
    check(result.insert(crown::storage::export_row(tuple->values())).second,
          "current-result cursor emitted a duplicate row");
  return result;
}

void check_committed(DeltaRuntime& runtime, const Database& database,
                    const std::string& label) {
  const auto expected = a04(runtime.plan(), database);
  check(runtime.has_answer() == !expected.empty(),
        label + ": answer truth differs from the independent A04 result");
  check(collect_results(runtime) == expected,
        label + ": public current result differs from A04");
  const auto snapshot = runtime.snapshot();
  check(snapshot.physical.tables == database.tables &&
            snapshot.sequence == runtime.sequence(),
        label + ": committed physical snapshot differs from the input state");
  if (runtime.mode() == DeltaMode::delta) {
    const auto live = runtime.live_snapshot();
    check(live && live->sequence == runtime.sequence(),
          label + ": live image is missing or stale");
    check(live->factors == a04_live(runtime.plan(), expected),
          label + ": live factors differ from independent A04 projections");
  } else {
    check(!runtime.live_snapshot(),
          label + ": maintenance mode retained a delta live image");
  }
  runtime.check_invariants();
}

struct Scenario {
  std::string label;
  PhysicalPlan plan;
  std::size_t table_count;
  std::vector<std::pair<TableId, Row>> seeds;
  TableId update_table;
  SetOperation operation;
  Row values;
};

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
      {{"join", NodeKind::generalized, variables({1}),
        {NodeId{1}, NodeId{2}}, {}, {}},
       {"left", NodeKind::native, variables({0, 1}), {}, 0, {}},
       {"right", NodeKind::native, variables({1, 2}), {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan shared_separator_plan() {
  const Catalog catalog{1,
      {{"r", {{"a", ScalarType::int64}, {"x", ScalarType::int64}}},
       {"s", {{"x", ScalarType::int64}, {"z", ScalarType::int64}}}}};
  const Query query{{{"a", ScalarType::int64}, {"x", ScalarType::int64},
                     {"z", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"s", TableId{1}, {VariableId{1}, VariableId{2}}}},
      {{VariableId{0}, "a"}, {VariableId{1}, "x"},
       {VariableId{2}, "z"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, variables({0, 1}), {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, variables({1, 2}), {}, 1, {}}}, {}, {}};
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
      {{"r", NodeKind::native, variables({0, 1}), {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, variables({1, 2}), {NodeId{2}}, 1, {}},
       {"t", NodeKind::native, variables({2, 3}), {NodeId{3}}, 2, {}},
       {"u", NodeKind::native, variables({3, 4}), {}, 3, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

Scenario self_join_scenario() {
  return {"multi-alias self-join", self_join_plan(), 1,
      {{TableId{0}, {n(1), n(2)}}, {TableId{0}, {n(2), n(1)}}},
      TableId{0}, SetOperation::insert, {n(1), n(1)}};
}

Scenario shared_separator_scenario() {
  return {"shared-separator support", shared_separator_plan(), 2,
      {{TableId{0}, {n(1), n(7)}}, {TableId{0}, {n(2), n(7)}},
       {TableId{1}, {n(7), n(10)}}, {TableId{1}, {n(7), n(11)}},
       {TableId{1}, {n(7), n(12)}}},
      TableId{0}, SetOperation::erase, {n(1), n(7)}};
}

Scenario deep_chain_scenario() {
  return {"deep chain product", deep_chain_plan(), 4,
      {{TableId{1}, {n(7), n(8)}}, {TableId{1}, {n(7), n(9)}},
       {TableId{2}, {n(8), n(10)}}, {TableId{2}, {n(9), n(11)}},
       {TableId{3}, {n(10), n(100)}}, {TableId{3}, {n(10), n(101)}},
       {TableId{3}, {n(11), n(110)}}, {TableId{3}, {n(11), n(111)}}},
      TableId{0}, SetOperation::insert, {n(1), n(7)}};
}

struct Harness {
  DeltaRuntime runtime;
  Database database;

  Harness(const Scenario& scenario, DeltaOptions options)
      : runtime(scenario.plan, options) {
    database.tables.resize(scenario.table_count);
    for (const auto& [table, row] : scenario.seeds) {
      auto after = database;
      check(after.tables.at(table.value).insert(row).second,
            scenario.label + ": duplicate seed row");
      const PhysicalSetUpdate update{runtime.sequence() + 1, table,
                                     SetOperation::insert, row};
      auto output = runtime.apply(update);
      check(output.remaining() == 0 && !output.active(),
            scenario.label + ": maintenance seed unexpectedly produced delta output");
      check(!output.next(), scenario.label + ": maintenance seed returned a row");
      database = std::move(after);
    }
    check(runtime.mode() == DeltaMode::maintenance,
          scenario.label + ": test harness did not begin in maintenance mode");
    static_cast<void>(runtime.set_mode(DeltaMode::delta));
    check_committed(runtime, database, scenario.label + " bootstrap");
  }

  PhysicalSetUpdate target(const Scenario& scenario) const {
    return {runtime.sequence() + 1, scenario.update_table,
            scenario.operation, scenario.values};
  }

  PhysicalSetUpdate inverse(const Scenario& scenario) const {
    return {runtime.sequence() + 1, scenario.update_table,
            scenario.operation == SetOperation::insert ? SetOperation::erase
                                                        : SetOperation::insert,
            scenario.values};
  }

  Database after(const PhysicalSetUpdate& update) const {
    auto next = database;
    auto& rows = next.tables.at(update.table.value);
    if (update.operation == SetOperation::insert)
      static_cast<void>(rows.insert(update.values));
    else
      static_cast<void>(rows.erase(update.values));
    return next;
  }

  std::set<SignedKey> expected(const PhysicalSetUpdate& update) const {
    return signed_difference(a04(runtime.plan(), database),
                             a04(runtime.plan(), after(update)));
  }

  std::set<SignedKey> apply_and_check(const PhysicalSetUpdate& update,
                                     const std::string& label) {
    const auto wanted = expected(update);
    auto output = runtime.apply(update);
    check(output.sequence() == update.sequence,
          label + ": committed sequence differs from the input");
    const auto observed = collect(output, label);
    check(observed == wanted && observed.size() == wanted.size(),
          label + ": committed signed output differs from independent A04 delta");
    database = after(update);
    check_committed(runtime, database, label + " after-state");
    return observed;
  }

  void publish_database(const PhysicalSetUpdate& update) {
    database = after(update);
  }
};

DeltaOptions lifecycle_options() {
  DeltaOptions result;
  result.mode = DeltaMode::maintenance;
  result.live_maintenance = LiveMaintenance::on_output;
  result.completion = DeltaCompletion::automatic;
  return result;
}

void check_replay_work_partition(const DeltaMetrics& metrics,
                                 const std::string& label) {
  const auto partition = metrics.replay_preparation_work +
      metrics.replay_first_work + metrics.replay_results_work +
      metrics.replay_termination_work + metrics.finalization_work;
  check(partition == metrics.work,
        label + ": replay producer and finalization work do not reconcile");
}

void step_once(DeltaRuntime::PendingEpoch& pending, std::size_t expected,
               const std::string& label) {
  const auto accepted_before = pending.metrics().accepted;
  const auto result = pending.step();
  const auto accepted_after = pending.metrics().accepted;
  check(accepted_after >= accepted_before &&
            accepted_after - accepted_before <= 1,
        label + ": one step accepted more than one core result");
  if (result == DeltaStep::core_result)
    check(accepted_after == accepted_before + 1,
          label + ": core_result did not account for exactly one accepted row");
  else
    check(accepted_after == accepted_before,
          label + ": a progress/prepared step changed the accepted count");
  if (accepted_after == 1 && expected > 1)
    check(pending.state() != DeltaState::epoch_prepared,
          label + ": epoch prepared after its first row despite more A04 output");
}

void drive_to_prefix(DeltaRuntime::PendingEpoch& pending, std::size_t prefix,
                     std::size_t expected, const std::string& label) {
  std::size_t calls = 0;
  while (pending.metrics().accepted < prefix) {
    check(pending.state() != DeltaState::epoch_prepared,
          label + ": epoch prepared before the requested output prefix");
    step_once(pending, expected, label);
    check(++calls < 100000, label + ": progress did not reach the requested prefix");
  }
  check(pending.metrics().accepted == prefix,
        label + ": accepted count skipped the requested output prefix");
}

void drive_prepared(DeltaRuntime::PendingEpoch& pending, std::size_t expected,
                   const std::string& label) {
  std::size_t calls = 0;
  while (pending.state() != DeltaState::epoch_prepared) {
    step_once(pending, expected, label);
    check(++calls < 100000, label + ": preparation did not terminate");
  }
  check(pending.metrics().accepted == expected,
        label + ": accepted count differs from the A04 delta size");
}

void check_barrier(Harness& harness, const PhysicalSetUpdate& update,
                   const std::string& label) {
  const auto sequence = harness.runtime.sequence();
  expect_error([&] { static_cast<void>(harness.runtime.results()); },
               "runtime_busy", label + " current results");
  expect_error([&] { static_cast<void>(harness.runtime.core_results()); },
               "runtime_busy", label + " core results");
  expect_error([&] { static_cast<void>(harness.runtime.current_view()); },
               "runtime_busy", label + " current view");
  expect_error([&] { static_cast<void>(harness.runtime.snapshot()); },
               "runtime_busy", label + " snapshot");
  expect_error([&] { static_cast<void>(harness.runtime.live_snapshot()); },
               "runtime_busy", label + " live snapshot");
  expect_error([&] { static_cast<void>(harness.runtime.storage_statistics()); },
               "runtime_busy", label + " storage statistics");
  expect_error([&] { static_cast<void>(harness.runtime.has_answer()); },
               "runtime_busy", label + " answer status");
  expect_error([&] {
    static_cast<void>(harness.runtime.set_mode(DeltaMode::maintenance));
  }, "runtime_busy", label + " mode change");
  auto competing = update;
  competing.sequence = sequence + 1;
  expect_error([&] { static_cast<void>(harness.runtime.apply(competing)); },
               "runtime_busy", label + " competing update");
  check(harness.runtime.sequence() == sequence,
        label + ": a blocked read or write advanced the committed sequence");
}

bool same_timings(const DeltaTimings& left, const DeltaTimings& right) {
  return left.propagation_ns == right.propagation_ns &&
         left.internal_delta_ns == right.internal_delta_ns &&
         left.output_mapping_ns == right.output_mapping_ns &&
         left.serialization_ns == right.serialization_ns &&
         left.sink_wait_ns == right.sink_wait_ns;
}

bool monotone_timings(const DeltaTimings& earlier,
                      const DeltaTimings& later) {
  return later.propagation_ns >= earlier.propagation_ns &&
         later.internal_delta_ns >= earlier.internal_delta_ns &&
         later.output_mapping_ns >= earlier.output_mapping_ns &&
         later.serialization_ns >= earlier.serialization_ns &&
         later.sink_wait_ns >= earlier.sink_wait_ns;
}

void pause_resume_each_output_prefix(const Scenario& scenario) {
  Harness count_harness(scenario, lifecycle_options());
  const auto update = count_harness.target(scenario);
  const auto expected = count_harness.expected(update);
  const auto output_count = expected.size();
  check(output_count > 1,
        scenario.label + ": fixture must produce several public rows");

  for (std::size_t prefix = 0; prefix < output_count; ++prefix) {
    Harness harness(scenario, lifecycle_options());
    auto event = harness.target(scenario);
    const auto wanted = harness.expected(event);
    auto pending = harness.runtime.begin(event);
    check(pending.active() && pending.state() == DeltaState::pending_delta &&
              harness.runtime.state() == DeltaState::pending_delta,
          scenario.label + ": begin did not own a pending delta epoch");
    drive_to_prefix(pending, prefix, output_count,
                    scenario.label + " prefix " + std::to_string(prefix));
    const auto before_barrier_reads = pending.timings();
    check_barrier(harness, event, scenario.label + " pending barrier");
    check(same_timings(before_barrier_reads, pending.timings()),
          scenario.label + ": blocked runtime reads changed phase timings");
    if (prefix == 0) {
      expect_error([&] { static_cast<void>(pending.resume()); },
                   "invalid_delta_state", scenario.label + " resume while running");
      expect_error([&] { static_cast<void>(pending.commit()); },
                   "runtime_busy", scenario.label + " early commit");
      check(pending.active(),
            scenario.label + ": rejected early commit consumed its token");
    }
    const auto before_pause = pending.timings();
    pending.pause();
    check(pending.state() == DeltaState::paused &&
              harness.runtime.state() == DeltaState::paused,
          scenario.label + ": pause did not change both lifecycle states");
    expect_error([&] { pending.pause(); }, "invalid_delta_state",
                 scenario.label + " repeated pause");
    const auto accepted_before = pending.metrics().accepted;
    expect_error([&] { static_cast<void>(pending.step()); }, "delta_paused",
                 scenario.label + " step while paused");
    check(pending.active() && pending.metrics().accepted == accepted_before,
          scenario.label + ": failed paused step consumed progress or token");
    check(same_timings(before_pause, pending.timings()),
          scenario.label + ": pause or rejected paused step changed phase timings");
    pending.resume();
    check(pending.state() == DeltaState::pending_delta &&
              harness.runtime.state() == DeltaState::pending_delta,
          scenario.label + ": resume did not restore pending state");
    expect_error([&] { pending.resume(); }, "invalid_delta_state",
                 scenario.label + " repeated resume");
    check(same_timings(before_pause, pending.timings()),
          scenario.label + ": resume or timing reads changed phase timings");
    drive_prepared(pending, output_count,
                   scenario.label + " resumed prefix " + std::to_string(prefix));
    check(monotone_timings(before_pause, pending.timings()),
          scenario.label + ": phase timing counters moved backwards");
    check(harness.runtime.state() == DeltaState::epoch_prepared,
          scenario.label + ": runtime did not expose epoch_prepared");
    auto committed = pending.commit();
    check(committed.sequence() == event.sequence,
          scenario.label + ": commit changed the update sequence");
    check(collect(committed, scenario.label + " committed prefix") == wanted,
          scenario.label + ": resumed output differs from the A04 oracle");
    harness.publish_database(event);
    check_committed(harness.runtime, harness.database,
                    scenario.label + " after resumed prefix");
    const auto followup = harness.inverse(scenario);
    const auto inverse_rows = harness.apply_and_check(
        followup, scenario.label + " subsequent update after resume");
    check(inverse_rows.size() == output_count,
          scenario.label + ": subsequent update failed to reverse the prior answer delta");
  }
}

void discard_each_output_prefix(const Scenario& scenario) {
  const auto count_options = lifecycle_options();
  Harness count_harness(scenario, count_options);
  const auto output_count = count_harness.expected(count_harness.target(scenario)).size();
  for (std::size_t prefix = 0; prefix < output_count; ++prefix) {
    Harness harness(scenario, lifecycle_options());
    const auto event = harness.target(scenario);
    auto pending = harness.runtime.begin(event);
    drive_to_prefix(pending, prefix, output_count,
                    scenario.label + " discard prefix " + std::to_string(prefix));
    const auto accepted_before_discard = pending.metrics().accepted;
    auto discarded = pending.discard();
    check(discarded.sequence() == event.sequence && discarded.remaining() == 0 &&
              !discarded.active(),
          scenario.label + ": discard published a retained output row");
    check(discarded.metrics().accepted == output_count,
          scenario.label + ": discard skipped internal accepted results");
    check(discarded.metrics().discarded_records == output_count,
          scenario.label + ": discarded-record accounting differs from A04 output");
    check_replay_work_partition(discarded.metrics(),
        scenario.label + " discard prefix " + std::to_string(prefix));
    check(collect(discarded, scenario.label + " discarded").empty(),
          scenario.label + ": discarded epoch exposed a public row");
    check(accepted_before_discard == prefix,
          scenario.label + ": discard began at the wrong accepted prefix");
    harness.publish_database(event);
    check_committed(harness.runtime, harness.database,
                    scenario.label + " after discard");
    const auto inverse_rows = harness.apply_and_check(
        harness.inverse(scenario), scenario.label + " subsequent update after discard");
    check(inverse_rows.size() == output_count,
          scenario.label + ": live state was stale after discard");
  }
}

void start_drain_drops_staged_output(const Scenario& scenario) {
  Harness harness(scenario, lifecycle_options());
  const auto event = harness.target(scenario);
  const auto expected = harness.expected(event).size();
  auto pending = harness.runtime.begin(event);
  drive_to_prefix(pending, std::min<std::size_t>(1, expected - 1), expected,
                  scenario.label + " start_drain prefix");
  pending.pause();
  pending.start_drain();
  check(pending.state() == DeltaState::draining &&
            harness.runtime.state() == DeltaState::draining,
        scenario.label + ": start_drain did not enter draining state");
  drive_prepared(pending, expected, scenario.label + " start_drain finish");
  for (const auto& stage : pending.stages())
    check(stage.output_begin == 0 && stage.output_count == 0,
          scenario.label + ": start_drain retained a public stage interval");
  auto committed = pending.commit();
  check(committed.remaining() == 0 &&
            committed.metrics().discarded_records == expected,
        scenario.label + ": drained commit retained output or lost discard accounting");
  check_replay_work_partition(committed.metrics(),
                              scenario.label + " start_drain work");
  check(collect(committed, scenario.label + " drained output").empty(),
        scenario.label + ": start_drain exposed a prepared result");
  harness.publish_database(event);
  check_committed(harness.runtime, harness.database,
                  scenario.label + " after start_drain");
  static_cast<void>(harness.apply_and_check(
      harness.inverse(scenario), scenario.label + " update after start_drain"));
}

void abort_each_output_prefix(const Scenario& scenario, bool destroy_token) {
  Harness count_harness(scenario, lifecycle_options());
  const auto output_count = count_harness.expected(count_harness.target(scenario)).size();
  for (std::size_t prefix = 0; prefix < output_count; ++prefix) {
    Harness harness(scenario, lifecycle_options());
    const auto event = harness.target(scenario);
    const auto old_sequence = harness.runtime.sequence();
    const auto old_answer = a04(harness.runtime.plan(), harness.database);
    if (destroy_token) {
      {
        auto pending = harness.runtime.begin(event);
        drive_to_prefix(pending, prefix, output_count,
                        scenario.label + " destruction prefix " + std::to_string(prefix));
      }
    } else {
      auto pending = harness.runtime.begin(event);
      drive_to_prefix(pending, prefix, output_count,
                      scenario.label + " rollback prefix " + std::to_string(prefix));
      pending.rollback();
      check(!pending.active(), scenario.label + ": rollback left its token active");
    }
    check(harness.runtime.sequence() == old_sequence && harness.runtime.ready(),
          scenario.label + ": abort published the input or kept the writer busy");
    check(a04(harness.runtime.plan(), harness.database) == old_answer,
          scenario.label + ": abort changed the independent committed answer");
    check_committed(harness.runtime, harness.database,
                    scenario.label + (destroy_token ? " after token destruction"
                                                    : " after rollback"));
    const auto retried = harness.apply_and_check(
        event, scenario.label + " same-sequence retry after abort");
    check(retried.size() == output_count,
          scenario.label + ": retry did not publish the complete A04 delta");
    static_cast<void>(harness.apply_and_check(
        harness.inverse(scenario), scenario.label + " inverse after retry"));
  }
}

void owning_input_and_move_lifecycle(const Scenario& scenario) {
  {
    Harness harness(scenario, lifecycle_options());
    auto event = harness.target(scenario);
    const auto wanted = harness.expected(event);
    auto original_pending = [&] {
      auto source = event;
      auto token = harness.runtime.begin(source);
      std::fill(source.values.begin(), source.values.end(), Value{n(9999)});
      source.values.clear();
      source.values.shrink_to_fit();
      return token;
    }();
    auto pending = std::move(original_pending);
    check(!original_pending.active() && pending.active(),
          scenario.label + ": moving the pending token changed its ownership state");
    check(pending.active(), scenario.label + ": begin lost its pending input");
    DeltaRuntime moved{std::move(harness.runtime)};
    check(moved.state() == DeltaState::pending_delta,
          scenario.label + ": moving the facade detached its pending token");
    drive_prepared(pending, wanted.size(), scenario.label + " moved facade");
    auto output = pending.commit();
    check(collect(output, scenario.label + " owned update") == wanted,
          scenario.label + ": begin did not own the source values");
    harness.database = harness.after(event);
    check_committed(moved, harness.database, scenario.label + " moved facade commit");
    const PhysicalSetUpdate inverse{
        moved.sequence() + 1, scenario.update_table,
        scenario.operation == SetOperation::insert ? SetOperation::erase
                                                    : SetOperation::insert,
        scenario.values};
    auto after_inverse = harness.database;
    auto& inverse_rows = after_inverse.tables.at(inverse.table.value);
    if (inverse.operation == SetOperation::insert)
      static_cast<void>(inverse_rows.insert(inverse.values));
    else
      static_cast<void>(inverse_rows.erase(inverse.values));
    const auto inverse_expected = signed_difference(
        a04(moved.plan(), harness.database), a04(moved.plan(), after_inverse));
    auto inverse_output = moved.apply(inverse);
    check(collect(inverse_output, scenario.label + " moved facade next update") ==
              inverse_expected,
          scenario.label + ": moved facade next update differs from A04");
    harness.database = std::move(after_inverse);
    check_committed(moved, harness.database,
                    scenario.label + " moved facade next-update state");
  }
}

void canonical_policy_pause_resume(const Scenario& scenario,
                                   LiveMaintenance maintenance,
                                   DeltaCompletion completion,
                                   const std::string& label) {
  auto options = lifecycle_options();
  options.live_maintenance = maintenance;
  options.completion = completion;
  Harness harness(scenario, options);
  check(harness.runtime.completion() == completion,
        label + ": configured canonical completion was not selected");
  const auto event = harness.target(scenario);
  const auto wanted = harness.expected(event);
  auto pending = harness.runtime.begin(event);
  drive_to_prefix(pending, 1, wanted.size(), label + " partial row");
  pending.pause();
  pending.resume();
  drive_prepared(pending, wanted.size(), label + " resumed");
  auto output = pending.commit();
  check(collect(output, label + " output") == wanted,
        label + ": canonical-policy output differs from A04");
  harness.publish_database(event);
  check_committed(harness.runtime, harness.database, label + " state");
  static_cast<void>(harness.apply_and_check(
      harness.inverse(scenario), label + " subsequent update"));
}

void drain_resumes_paused_token(const Scenario& scenario) {
  Harness harness(scenario, lifecycle_options());
  const auto event = harness.target(scenario);
  const auto wanted = harness.expected(event);
  auto pending = harness.runtime.begin(event);
  drive_to_prefix(pending, 1, wanted.size(), scenario.label + " paused drain");
  pending.pause();
  pending.drain();
  check(pending.state() == DeltaState::epoch_prepared,
        scenario.label + ": drain did not resume and prepare paused work");
  auto output = pending.commit();
  check(collect(output, scenario.label + " drained retained output") == wanted,
        scenario.label + ": drain failed to retain prepared output");
  harness.publish_database(event);
  check_committed(harness.runtime, harness.database,
                  scenario.label + " after drain");
  static_cast<void>(harness.apply_and_check(
      harness.inverse(scenario), scenario.label + " update after drain"));
}

PhysicalPlan projection_count_plan() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}, VariableId{1}}}},
      {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, variables({0, 1}), {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan filtered_plan() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}, {"flag", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}, Value{n(1)}}}},
      {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, variables({0}), {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

void finish_empty_delta(DeltaRuntime& runtime, Database& database,
                        const PhysicalSetUpdate& update,
                        const std::string& label) {
  auto next = database;
  auto& rows = next.tables.at(update.table.value);
  if (update.operation == SetOperation::insert)
    static_cast<void>(rows.insert(update.values));
  else
    static_cast<void>(rows.erase(update.values));
  check(signed_difference(a04(runtime.plan(), database),
                          a04(runtime.plan(), next)).empty(),
        label + ": fixture was expected to have empty A04 delta");
  auto pending = runtime.begin(update);
  drive_prepared(pending, 0, label);
  check(pending.metrics().accepted == 0,
        label + ": empty event unexpectedly accepted a core result");
  auto output = pending.commit();
  check(output.remaining() == 0 && collect(output, label).empty(),
        label + ": empty event produced a public output record");
  database = std::move(next);
  check_committed(runtime, database, label + " committed state");
}

void no_op_count_only_filtered_and_maintenance() {
  {
    Scenario scenario{"no-op duplicate", self_join_plan(), 1,
        {{TableId{0}, {n(1), n(2)}}, {TableId{0}, {n(2), n(1)}}},
        TableId{0}, SetOperation::insert, {n(1), n(2)}};
    Harness harness(scenario, lifecycle_options());
    const auto event = harness.target(scenario);
    check(harness.expected(event).empty(), "duplicate insert changed A04 answer");
    finish_empty_delta(harness.runtime, harness.database, event,
                       "duplicate insert no-op");
  }

  {
    DeltaOptions options = lifecycle_options();
    Harness harness(Scenario{"projection-count-only", projection_count_plan(), 1,
        {{TableId{0}, {n(1), n(10)}}}, TableId{0}, SetOperation::insert,
        {n(1), n(11)}}, options);
    const PhysicalSetUpdate event{harness.runtime.sequence() + 1, TableId{0},
                                  SetOperation::insert, {n(1), n(11)}};
    finish_empty_delta(harness.runtime, harness.database, event,
                       "projection count-only insertion");
  }

  {
    Harness harness(Scenario{"filtered route", filtered_plan(), 1,
        {{TableId{0}, {n(1), n(1)}}}, TableId{0}, SetOperation::insert,
        {n(2), n(0)}}, lifecycle_options());
    const PhysicalSetUpdate event{harness.runtime.sequence() + 1, TableId{0},
                                  SetOperation::insert, {n(2), n(0)}};
    finish_empty_delta(harness.runtime, harness.database, event,
                       "filtered insertion");
  }

  {
    const auto scenario = shared_separator_scenario();
    auto options = lifecycle_options();
    DeltaRuntime runtime{scenario.plan, options};
    Database database;
    database.tables.resize(scenario.table_count);
    for (const auto& [table, row] : scenario.seeds) {
      auto seeded = database;
      seeded.tables.at(table.value).insert(row);
      auto output = runtime.apply(
          {runtime.sequence() + 1, table, SetOperation::insert, row});
      check(output.remaining() == 0,
            "maintenance seed produced a delta output");
      database = std::move(seeded);
    }
    const PhysicalSetUpdate event{runtime.sequence() + 1, scenario.update_table,
                                  scenario.operation, scenario.values};
    auto after = database;
    after.tables[event.table.value].erase(event.values);
    auto pending = runtime.begin(event);
    pending.drain();
    check(pending.metrics().accepted == 0,
          "maintenance update performed delta-only answer enumeration");
    auto output = pending.commit();
    check(output.remaining() == 0 && collect(output, "maintenance").empty(),
          "maintenance mode retained delta output");
    check(runtime.mode() == DeltaMode::maintenance && !runtime.live_snapshot(),
          "maintenance commit unexpectedly installed a live image");
    database = std::move(after);
    check_committed(runtime, database, "maintenance after pending update");
    static_cast<void>(runtime.set_mode(DeltaMode::delta));
    check_committed(runtime, database, "delta mode after maintenance bootstrap");
    const PhysicalSetUpdate restore{runtime.sequence() + 1, event.table,
                                    SetOperation::insert, event.values};
    auto restored = database;
    restored.tables[event.table.value].insert(event.values);
    auto expected = signed_difference(a04(runtime.plan(), database),
                                     a04(runtime.plan(), restored));
    auto restored_output = runtime.apply(restore);
    check(collect(restored_output, "post-maintenance delta mode") == expected,
          "delta mode after maintenance bootstrap differs from A04");
    database = std::move(restored);
    check_committed(runtime, database, "after maintenance-to-delta update");
  }
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
  check(program.binding.wrapper == frontend::SqlWrapper::exists &&
            program.core.atoms.size() == 1,
        "EXISTS fixture did not lower to a nullary one-atom core");
  const FreeConnexTree tree{NodeId{0},
      {{program.core.atoms[0].occurrence, NodeKind::native, {}, {}, 0, {}}},
      {}, {}};
  return planner::lower_normalized(program, tree);
}

Relation exists_sql_answer(bool value) { return Relation{{Value{value}}}; }

Relation a04_exists_core(const auto& plan, const Database& database) {
  const auto& catalog = plan.source_catalog();
  check(catalog.tables.size() == 1 && !catalog.tables[0].columns.empty(),
        "EXISTS fixture source catalog is not the expected one-column table");
  Query source_query;
  source_query.variables.push_back(
      {"x", catalog.tables[0].columns[0].type});
  source_query.atoms.push_back(
      {"source", TableId{0}, {VariableId{0}}});
  // This source-level nullary query is an independent A04 definition of the
  // EXISTS wrapper truth; normalized core atoms use a different catalog.
  return reference::evaluate(reference::input::catalog(catalog), source_query, database);
}

void check_exists_results(DeltaRuntime& runtime, bool expected,
                          const std::string& label) {
  check(collect_results(runtime) == exists_sql_answer(expected),
        label + ": scalar EXISTS result differs from expected Boolean row");
  check(runtime.has_answer() == expected,
        label + ": core answer truth differs from expected EXISTS value");
  const auto live = runtime.live_snapshot();
  check(live && live->factors.size() == 1 &&
            live->factors.front() == (expected ? Relation{Row{}} : Relation{}),
        label + ": nullary live factor differs from the A04 core truth value");
  runtime.check_invariants();
}

std::set<SignedKey> exists_flip(bool before, bool after) {
  std::set<SignedKey> expected;
  if (before == after) return expected;
  expected.emplace(SetOperation::erase, Row{Value{before}});
  expected.emplace(SetOperation::insert, Row{Value{after}});
  return expected;
}

void scalar_exists_pending_mapping() {
  DeltaRuntime runtime{exists_plan()};
  check_exists_results(runtime, false, "initial EXISTS false");
  Database database;
  database.tables.resize(1);
  const PhysicalSetUpdate insert{runtime.sequence() + 1, TableId{0},
                                SetOperation::insert, {n(5)}};
  auto after = database;
  after.tables[0].insert(insert.values);
  check(a04_exists_core(runtime.plan(), database).empty() &&
            a04_exists_core(runtime.plan(), after) == Relation{Row{}},
        "EXISTS A04 core truth did not flip from false to true");
  auto pending = runtime.begin(insert);
  std::size_t calls = 0;
  while (pending.state() != DeltaState::epoch_prepared) {
    step_once(pending, 1, "EXISTS core update");
    check(++calls < 10000, "EXISTS update did not prepare");
  }
  auto output = pending.commit();
  const std::set<SignedKey> expected{
      {SetOperation::erase, {Value{false}}},
      {SetOperation::insert, {Value{true}}}};
  const auto old_false = output.next();
  const auto new_true = output.next();
  check(old_false && new_true && old_false->ordinal == 1 &&
            new_true->ordinal == 2 &&
            old_false->operation == SetOperation::erase &&
            old_false->tuple.values() == Row{Value{false}} &&
            new_true->operation == SetOperation::insert &&
            new_true->tuple.values() == Row{Value{true}} &&
            !output.next() && output.remaining() == 0 && !output.active(),
        "EXISTS wrapper mapping did not stage false erase and true insert");
  check(expected == exists_flip(false, true),
        "EXISTS wrapper oracle did not encode the before/after row replacement");
  database = std::move(after);
  check_exists_results(runtime, true, "EXISTS true after pending commit");

  const PhysicalSetUpdate erase{runtime.sequence() + 1, TableId{0},
                                SetOperation::erase, {n(5)}};
  auto empty = database;
  empty.tables[0].erase(erase.values);
  check(a04_exists_core(runtime.plan(), empty).empty(),
        "EXISTS A04 core truth did not return to false");
  const auto reverse = exists_flip(true, false);
  auto reverse_output = runtime.apply(erase);
  check(collect(reverse_output, "EXISTS true-to-false output") == reverse,
        "EXISTS true-to-false SQL mapping differs from the wrapper oracle");
  database = std::move(empty);
  check_exists_results(runtime, false, "EXISTS false after deletion");
}

void deliver_one_acknowledges_after_callback_success() {
  const auto scenario = self_join_scenario();
  Harness harness(scenario, lifecycle_options());
  const auto event = harness.target(scenario);
  const auto wanted = harness.expected(event);
  auto pending = harness.runtime.begin(event);
  drive_prepared(pending, wanted.size(), "delivery pending epoch");
  auto epoch = pending.commit();
  check(epoch.remaining() == wanted.size(),
        "committed delivery epoch does not contain the A04 rows");

  std::optional<SignedResult> failed_row;
  try {
    static_cast<void>(epoch.deliver_one([&](const SignedResult& row) {
      failed_row = row;
      throw std::runtime_error("temporary sink failure");
    }));
  } catch (const std::runtime_error& failure) {
    check(std::string(failure.what()) == "temporary sink failure",
          "deliver_one changed the callback exception");
  }
  check(failed_row && epoch.remaining() == wanted.size(),
        "failed sink callback acknowledged or lost its peeked row");
  const auto first_remaining = epoch.remaining();
  check(epoch.deliver_one([&](const SignedResult& row) {
          check(row.ordinal == failed_row->ordinal &&
                    row.operation == failed_row->operation &&
                    row.tuple.values() == failed_row->tuple.values(),
                "retry did not receive the retained callback row");
          check(epoch.remaining() == first_remaining,
                "deliver_one removed the row before callback success");
          expect_error([&] { static_cast<void>(epoch.next()); }, "runtime_busy",
                       "reentrant next from sink callback");
        }),
        "successful callback did not acknowledge one output row");
  check(epoch.remaining() + 1 == first_remaining,
        "successful callback did not remove exactly one row");

  const auto codec_remaining = epoch.remaining();
  const auto timings_before_codec = epoch.timings();
  std::optional<SignedResult> codec_row;
  std::size_t serializer_calls = 0;
  std::size_t sink_calls = 0;
  try {
    static_cast<void>(epoch.deliver_one(
        [&](const SignedResult& row) {
          ++serializer_calls;
          codec_row = row;
          if (serializer_calls == 1)
            throw std::runtime_error("temporary serializer failure");
        },
        [&](const SignedResult&) { ++sink_calls; }));
  } catch (const std::runtime_error& failure) {
    check(std::string(failure.what()) == "temporary serializer failure",
          "serializer failure changed while leaving deliver_one");
  }
  check(serializer_calls == 1 && sink_calls == 0 &&
            epoch.remaining() == codec_remaining && codec_row,
        "serializer failure called the sink or acknowledged its row");
  const auto timings_after_codec_error = epoch.timings();
  check(monotone_timings(timings_before_codec, timings_after_codec_error),
        "serialization timing moved backwards after a codec error");
  std::vector<std::string> callback_order;
  check(epoch.deliver_one(
            [&](const SignedResult& row) {
              callback_order.push_back("serialize");
              check(row.ordinal == codec_row->ordinal &&
                        row.operation == codec_row->operation &&
                        row.tuple.values() == codec_row->tuple.values(),
                    "codec retry did not receive the retained row identity");
            },
            [&](const SignedResult& row) {
              callback_order.push_back("sink");
              ++sink_calls;
              check(row.ordinal == codec_row->ordinal &&
                        row.tuple.values() == codec_row->tuple.values(),
                    "sink callback received a different row from the codec");
            }),
        "successful serializer and sink callbacks did not acknowledge a row");
  check(callback_order == std::vector<std::string>{"serialize", "sink"} &&
            sink_calls == 1 && epoch.remaining() + 1 == codec_remaining,
        "serializer did not precede the sink or successful callbacks did not ack");
  check(monotone_timings(timings_after_codec_error, epoch.timings()),
        "callback timing counters moved backwards after successful delivery");

  std::size_t delivered_before_discard = 0;
  check(epoch.deliver_one([&](const SignedResult&) {
          ++delivered_before_discard;
          epoch.discard();
          check(epoch.active(),
                "callback discard retired the epoch before callback return");
        }),
        "callback discard did not report its in-flight row");
  check(delivered_before_discard == 1 && !epoch.active() &&
            epoch.remaining() == 0 && harness.runtime.ready(),
        "deferred callback discard did not safely release unread output");
  harness.publish_database(event);
  check_committed(harness.runtime, harness.database,
                  "after callback delivery and discard");
  static_cast<void>(harness.apply_and_check(
      harness.inverse(scenario), "update after callback discard"));
}

void facade_destruction_keeps_token_rollback_safe() {
  const auto scenario = self_join_scenario();
  std::optional<DeltaRuntime::PendingEpoch> token;
  {
    auto options = lifecycle_options();
    DeltaRuntime runtime{scenario.plan, options};
    Database database;
    database.tables.resize(scenario.table_count);
    for (const auto& [table, row] : scenario.seeds) {
      database.tables.at(table.value).insert(row);
      auto output = runtime.apply(
          {runtime.sequence() + 1, table, SetOperation::insert, row});
      check(output.remaining() == 0,
            "facade-destruction fixture seed unexpectedly emitted output");
    }
    static_cast<void>(runtime.set_mode(DeltaMode::delta));
    token.emplace(runtime.begin(
        {runtime.sequence() + 1, scenario.update_table,
         scenario.operation, scenario.values}));
    step_once(*token, 3, "token survives facade destruction");
  }
  check(token->active(), "destroyed facade invalidated its pending token");
  token->rollback();
  check(!token->active(), "pending token could not rollback after facade destruction");
}

void run() {
  const auto self_join = self_join_scenario();
  const auto shared = shared_separator_scenario();
  const auto deep = deep_chain_scenario();
  for (const auto* scenario : {&self_join, &shared, &deep}) {
    pause_resume_each_output_prefix(*scenario);
    discard_each_output_prefix(*scenario);
    start_drain_drops_staged_output(*scenario);
    abort_each_output_prefix(*scenario, false);
    abort_each_output_prefix(*scenario, true);
    drain_resumes_paused_token(*scenario);
  }
  canonical_policy_pause_resume(shared, LiveMaintenance::incremental,
                                DeltaCompletion::anchored,
                                "incremental anchored lifecycle");
  canonical_policy_pause_resume(deep, LiveMaintenance::eager,
                                DeltaCompletion::root_first,
                                "eager root-first lifecycle");
  owning_input_and_move_lifecycle(self_join);
  owning_input_and_move_lifecycle(shared);
  no_op_count_only_filtered_and_maintenance();
  scalar_exists_pending_mapping();
  deliver_one_acknowledges_after_callback_success();
  facade_destruction_keeps_token_rollback_safe();
}
}  // namespace

int main() {
  try {
    run();
    std::cout << "delta pending lifecycle, draining, abort, and sink checks passed\n";
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
  return 0;
}
