#include "crown/api/error.hpp"
#include "crown/frontend/bind.hpp"
#include "crown/frontend/normalize.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/session.hpp"
#include "evaluator.hpp"
#ifdef CROWN_STATISTICS_ACCEPTANCE
#include "statistics_acceptance.hpp"
#endif

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
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

PhysicalPlan projected_pair_plan() {
  const Catalog catalog{1,
      {{"pairs", {{"key", ScalarType::int64},
                   {"payload", ScalarType::int64}}}}};
  const Query query{{{"key", ScalarType::int64},
                     {"payload", ScalarType::int64}},
      {{"pairs", TableId{0}, {VariableId{0}, VariableId{1}}}},
      {{VariableId{0}, "key"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"pairs", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}}},
      {}, {}};
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

PhysicalPlan two_relation_plan() {
  const Catalog catalog{1,
      {{"left_rows", {{"x", ScalarType::int64}}},
       {"right_rows", {{"y", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"left", TableId{0}, {VariableId{0}}},
       {"right", TableId{1}, {VariableId{1}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "y"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"cross", NodeKind::generalized, {}, {NodeId{1}, NodeId{2}}, {}, {}},
       {"left", NodeKind::native, {VariableId{0}}, {}, 0, {}},
       {"right", NodeKind::native, {VariableId{1}}, {}, 1, {}}},
      {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan exists_plan() {
  const Catalog catalog{19, {{"flags", {{"x", ScalarType::int64}}}}};
  const auto binding = frontend::bind_sql(
      "SELECT EXISTS(SELECT NULL FROM flags)", catalog);
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

io::SourcePosition source_position(std::uint64_t offset) {
  return io::SourcePosition{"window-feed", offset};
}

io::WindowCommand insert_command(std::uint64_t sequence, std::uint64_t label,
                                 TableId table, Row values,
                                 std::uint64_t timestamp,
                                 std::optional<std::uint64_t> offset = {}) {
  return {sequence, io::WindowInsert{label, table, std::move(values), timestamp},
          offset ? std::optional<io::SourcePosition>{source_position(*offset)}
                 : std::nullopt};
}

io::WindowCommand withdraw_command(std::uint64_t sequence,
                                   std::uint64_t label,
                                   std::optional<std::uint64_t> offset = {}) {
  return {sequence, io::WindowWithdraw{label},
          offset ? std::optional<io::SourcePosition>{source_position(*offset)}
                 : std::nullopt};
}

io::WindowCommand watermark_command(std::uint64_t sequence,
                                    std::uint64_t watermark,
                                    std::optional<std::uint64_t> offset = {}) {
  return {sequence, io::AdvanceWatermark{watermark},
          offset ? std::optional<io::SourcePosition>{source_position(*offset)}
                 : std::nullopt};
}

WindowOptions window_options(std::vector<TableId> tables, std::uint64_t width,
                             WindowFifoPolicy fifo = WindowFifoPolicy::global) {
  WindowOptions result;
  result.managed_tables = std::move(tables);
  result.width = width;
  result.fifo = fifo;
  return result;
}

struct ModelLabel {
  std::uint64_t id;
  TableId table;
  Row values;
  std::uint64_t timestamp;
  std::uint64_t deadline;
  std::uint64_t count_id;
};

struct ModelActive {
  std::uint64_t sequence;
  std::uint64_t watermark;
  std::vector<std::uint64_t> expiration_labels;
  std::size_t completed_steps;
  std::size_t total_steps;
};

struct Oracle {
  WindowOptions options;
  Database database;
  std::vector<ModelLabel> labels;
  std::uint64_t completed_command_sequence = 0;
  std::uint64_t physical_sequence = 0;
  std::uint64_t completed_watermark = 0;
  std::uint64_t last_label = 0;
  std::optional<ModelActive> active;
  io::InputProgress accepted;
};

struct PlannedStep {
  std::optional<PhysicalSetUpdate> update;
  Oracle after;
};

std::size_t count_labels(const Oracle& oracle, TableId table, const Row& row) {
  return static_cast<std::size_t>(std::count_if(oracle.labels.begin(), oracle.labels.end(),
      [&](const ModelLabel& label) {
        return label.table == table && label.values == row;
      }));
}

std::uint64_t count_id_for(const Oracle& oracle, TableId table, const Row& row) {
  const auto found = std::find_if(oracle.labels.begin(), oracle.labels.end(),
      [&](const ModelLabel& label) {
        return label.table == table && label.values == row;
      });
  return found == oracle.labels.end() ? 0 : found->count_id;
}

void add_physical(Oracle& oracle, TableId table, SetOperation operation,
                  const Row& row, std::optional<PhysicalSetUpdate>& update) {
  ++oracle.physical_sequence;
  update.emplace(PhysicalSetUpdate{oracle.physical_sequence, table, operation, row});
  auto& relation = oracle.database.tables.at(table.value);
  if (operation == SetOperation::insert) relation.insert(row);
  else relation.erase(row);
}

void complete_command(Oracle& oracle, const io::WindowCommand& command) {
  oracle.completed_command_sequence = command.sequence;
  oracle.accepted.sequence = command.sequence;
  if (command.source_position) {
    oracle.accepted.source_positions[command.source_position->source] =
        command.source_position->offset;
  }
}

std::vector<PlannedStep> plan_independently(
    const Oracle& before, const io::WindowCommand& command) {
  std::vector<PlannedStep> result;
  Oracle current = before;
  const auto* insertion = std::get_if<io::WindowInsert>(&command.command);
  const auto* withdrawal = std::get_if<io::WindowWithdraw>(&command.command);
  const auto* watermark = std::get_if<io::AdvanceWatermark>(&command.command);

  if (insertion) {
    const auto old_count = count_labels(current, insertion->table, insertion->values);
    const auto count_id = count_id_for(current, insertion->table, insertion->values);
    std::optional<PhysicalSetUpdate> update;
    if (old_count == 0)
      add_physical(current, insertion->table, SetOperation::insert,
                   insertion->values, update);
    current.labels.push_back({insertion->label, insertion->table,
        insertion->values, insertion->timestamp,
        insertion->timestamp + current.options.width,
        old_count == 0 ? insertion->label : count_id});
    current.last_label = insertion->label;
    complete_command(current, command);
    result.push_back({std::move(update), std::move(current)});
    return result;
  }

  auto remove_label = [&](Oracle& state, std::uint64_t id,
                          std::optional<PhysicalSetUpdate>& update) {
    const auto found = std::find_if(state.labels.begin(), state.labels.end(),
        [&](const ModelLabel& label) { return label.id == id; });
    if (found == state.labels.end()) throw std::runtime_error("oracle lost a live label");
    const auto table = found->table;
    const auto row = found->values;
    state.labels.erase(found);
    if (count_labels(state, table, row) == 0)
      add_physical(state, table, SetOperation::erase, row, update);
  };

  if (withdrawal) {
    const auto found = std::find_if(current.labels.begin(), current.labels.end(),
        [&](const ModelLabel& label) { return label.id == withdrawal->label; });
    if (found == current.labels.end()) throw std::runtime_error("oracle withdrawal is unknown");
    const auto expected_oldest = std::find_if(current.labels.begin(), current.labels.end(),
        [&](const ModelLabel& label) {
          return before.options.fifo == WindowFifoPolicy::global ||
                 label.table == found->table;
        });
    if (expected_oldest == current.labels.end() || expected_oldest->id != withdrawal->label)
      throw std::runtime_error("oracle withdrawal violates declared FIFO");
    std::optional<PhysicalSetUpdate> update;
    remove_label(current, withdrawal->label, update);
    complete_command(current, command);
    result.push_back({std::move(update), std::move(current)});
    return result;
  }

  if (!watermark) throw std::runtime_error("oracle received an unknown command");
  std::vector<std::pair<std::uint64_t, std::uint64_t>> ordered;
  for (const auto& label : current.labels)
    if (label.deadline <= watermark->watermark)
      ordered.emplace_back(label.deadline, label.id);
  std::sort(ordered.begin(), ordered.end());

  // Compare the entire timestamp-selected order against the insertion-list
  // order before modeling any removal, as the operational contract requires.
  std::map<TableId, std::vector<std::uint64_t>> expected_fifo;
  for (const auto& label : current.labels)
    expected_fifo[label.table].push_back(label.id);
  std::map<TableId, std::size_t> relation_cursor;
  std::size_t global_cursor = 0;
  std::vector<std::uint64_t> expiration_labels;
  for (const auto& [deadline, id] : ordered) {
    (void)deadline;
    const auto found = std::find_if(current.labels.begin(), current.labels.end(),
        [&](const ModelLabel& label) { return label.id == id; });
    if (found == current.labels.end()) throw std::runtime_error("oracle expiration lost a label");
    if (current.options.fifo == WindowFifoPolicy::global) {
      while (global_cursor < current.labels.size() &&
             current.labels[global_cursor].deadline <= watermark->watermark &&
             current.labels[global_cursor].id != id) {
        // The next insertion may be outside the expiration set; it still
        // blocks any later insertion from expiring first.
        throw std::runtime_error("oracle watermark violates global FIFO");
      }
      if (global_cursor >= current.labels.size() || current.labels[global_cursor].id != id)
        throw std::runtime_error("oracle watermark violates global FIFO");
      ++global_cursor;
    } else {
      auto& cursor = relation_cursor[found->table];
      const auto& fifo = expected_fifo[found->table];
      if (cursor >= fifo.size() || fifo[cursor] != id)
        throw std::runtime_error("oracle watermark violates relation FIFO");
      ++cursor;
    }
    expiration_labels.push_back(id);
  }

  if (expiration_labels.empty()) {
    current.completed_watermark = watermark->watermark;
    complete_command(current, command);
    result.push_back({std::nullopt, std::move(current)});
    return result;
  }

  const auto total = expiration_labels.size();
  for (std::size_t index = 0; index < total; ++index) {
    if (index == 0)
      current.active = ModelActive{command.sequence, watermark->watermark,
                                   expiration_labels, 0, total};
    std::optional<PhysicalSetUpdate> update;
    remove_label(current, expiration_labels[index], update);
    current.active->completed_steps = index + 1;
    if (index + 1 == total) {
      current.completed_watermark = watermark->watermark;
      current.active.reset();
      complete_command(current, command);
    }
    result.push_back({std::move(update), current});
  }
  return result;
}

WindowProgress expected_progress(const Oracle& oracle) {
  WindowProgress result{oracle.completed_command_sequence,
      oracle.physical_sequence, oracle.completed_watermark, oracle.last_label,
      std::nullopt, 0, 0};
  if (oracle.active) {
    result.active_command_sequence = oracle.active->sequence;
    result.completed_steps = oracle.active->completed_steps;
    result.total_steps = oracle.active->total_steps;
  }
  return result;
}

void compare_canonical(QuerySession& session, const Oracle& oracle,
                       const std::string& label) {
  const auto actual = session.window_state();
  check(actual.has_value(), label + ": session omitted canonical window state");
  std::vector<WindowLabel> expected_labels;
  std::map<std::uint64_t, WindowCount> expected_counts;
  std::vector<std::pair<std::uint64_t, std::uint64_t>> expected_expirations;
  std::vector<std::uint64_t> expected_global;
  std::map<TableId, std::vector<std::uint64_t>> expected_relations;
  for (auto table : oracle.options.managed_tables) expected_relations[table] = {};
  for (const auto& label_row : oracle.labels) {
    expected_labels.push_back({label_row.id, label_row.table, label_row.values,
        label_row.timestamp, label_row.deadline, label_row.count_id});
    expected_expirations.emplace_back(label_row.deadline, label_row.id);
    expected_global.push_back(label_row.id);
    expected_relations[label_row.table].push_back(label_row.id);
    auto found = expected_counts.find(label_row.count_id);
    if (found == expected_counts.end()) {
      expected_counts.emplace(label_row.count_id,
          WindowCount{label_row.count_id, label_row.table, label_row.values, 1});
    } else {
      ++found->second.count;
    }
  }
  std::sort(expected_expirations.begin(), expected_expirations.end());
  std::vector<WindowCount> counts;
  for (const auto& [id, count] : expected_counts) {
    (void)id;
    counts.push_back(count);
  }
  std::vector<std::pair<TableId, std::vector<std::uint64_t>>> relations;
  for (const auto& [table, ids] : expected_relations) relations.push_back({table, ids});

  check(actual->labels == expected_labels, label + ": full live label list differs from list oracle");
  check(actual->counts == counts, label + ": full-row reference counts differ from list oracle");
  check(actual->expiration_index == expected_expirations,
        label + ": timestamp/deadline index differs from independently sorted labels");
  check(actual->global_fifo == expected_global,
        label + ": global live insertion order differs from label list");
  check(actual->relation_fifo == relations,
        label + ": per-relation insertion order differs from label list");
  check(actual->completed_command_sequence == oracle.completed_command_sequence &&
        actual->physical_sequence == oracle.physical_sequence &&
        actual->completed_watermark == oracle.completed_watermark &&
        actual->last_label == oracle.last_label,
        label + ": command, physical, watermark, or label progress differs");
  check(actual->active_command.has_value() == oracle.active.has_value(),
        label + ": active watermark presence differs");
  if (oracle.active) {
    const auto& a = *actual->active_command;
    const auto& e = *oracle.active;
    check(a.sequence == e.sequence && a.watermark == e.watermark &&
          a.expiration_labels == e.expiration_labels &&
          a.completed_steps == e.completed_steps && a.total_steps == e.total_steps,
          label + ": active watermark expansion progress differs");
  }
  check(actual->metrics.live_labels == oracle.labels.size() &&
        actual->metrics.distinct_rows == expected_counts.size(),
        label + ": public live-label or distinct-row metric differs");
}

std::set<SignedKey> collect_output(QuerySession& session,
                                   const std::string& label) {
  std::set<SignedKey> result;
  std::uint64_t ordinal = 0;
  while (auto record = session.next_output()) {
    check(record->ordinal == ++ordinal,
          label + ": output ordinals are not contiguous from one");
    check(result.emplace(record->operation, crown::storage::export_row(record->tuple.values())).second,
          label + ": signed output contains a duplicate row");
  }
  return result;
}

std::set<SignedKey> reference_delta(const CommittedReferenceEpoch& epoch) {
  std::set<SignedKey> result;
  for (const auto& row : epoch.delta.added) result.emplace(SetOperation::insert, row);
  for (const auto& row : epoch.delta.removed) result.emplace(SetOperation::erase, row);
  return result;
}

Query exists_source_query() {
  // This physical R(x) query yields one nullary row for nonempty R. The SQL
  // EXISTS wrapper maps that truth value to a scalar false/true result row.
  return Query{{{"x", ScalarType::int64}},
      {{"flags", TableId{0}, {VariableId{0}}}}, {}, false};
}

Query independent_query(const PhysicalPlan& plan, bool sql_exists_wrapper) {
  return sql_exists_wrapper ? exists_source_query() : plan.query();
}

Relation sql_exists_rows(const Relation& nullary_answer) {
  return Relation{Row{Value{!nullary_answer.empty()}}};
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

void compare_snapshot(QuerySession& session, const PhysicalPlan& plan,
                      const reference::Session& reference_session,
                      const Oracle& oracle, const std::string& label,
                      bool sql_exists_wrapper = false) {
  const auto snapshot = session.snapshot();
  std::set<Row> observed;
  for (const auto& tuple : snapshot.rows) {
    check(tuple.layout().same_token(snapshot.layout),
          label + ": snapshot tuple lost the advertised result layout");
    check(observed.insert(crown::storage::export_row(tuple.values())).second,
          label + ": snapshot contains duplicate SQL rows");
  }
  const auto query = independent_query(plan, sql_exists_wrapper);
  const auto independently_evaluated = reference::evaluate(
      plan.source_catalog(), query, oracle.database);
  const auto reference_source = reference_session.snapshot();
  const auto independent = sql_exists_wrapper
      ? sql_exists_rows(independently_evaluated) : independently_evaluated;
  const auto reference_answer = sql_exists_wrapper
      ? sql_exists_rows(reference_source) : reference_source;
  check(independent == reference_answer,
        label + ": independent label-derived database differs from reference session");
  check(observed == independent, label + ": physical session differs from independent result");
  check(snapshot.sequence == oracle.physical_sequence &&
        snapshot.progress == oracle.accepted && session.progress() == oracle.accepted,
        label + ": physical sequence or completed input/source progress differs");
  const auto progress = expected_progress(oracle);
  check(snapshot.window == std::optional<WindowProgress>{progress} &&
        session.status().window == std::optional<WindowProgress>{progress},
        label + ": snapshot/session window prefix progress differs");
}

struct Harness {
  PhysicalPlan plan;
  WindowOptions options;
  bool sql_exists_wrapper = false;
  QuerySession::Owner session;
  std::unique_ptr<reference::Session> reference_session;
  Oracle oracle;

  Harness(PhysicalPlan value, WindowOptions windows,
          Database initial = {}, bool wrap_sql_exists = false)
      : plan(std::move(value)), options(std::move(windows)),
        sql_exists_wrapper(wrap_sql_exists) {
    if (initial.tables.empty()) initial.tables.resize(plan.source_catalog().tables.size());
#ifdef CROWN_STATISTICS_ACCEPTANCE
    SessionOptions c01_session_options;
    c01_session_options.delta.physical.support.order = statistics_acceptance::requested_order;
    session = QuerySession::create_windowed(plan, initial, options, {}, c01_session_options);
#else
    session = QuerySession::create_windowed(plan, initial, options);
#endif
#ifdef CROWN_STATISTICS_ACCEPTANCE
    statistics_acceptance::enable(*session);
#endif
    reference_session = std::make_unique<reference::Session>(
        plan.source_catalog(), independent_query(plan, sql_exists_wrapper), initial);
    oracle.options = options;
    oracle.database = std::move(initial);
  }

  void enqueue(const std::vector<io::WindowCommand>& commands) {
    std::vector<io::InputItem> items;
    items.reserve(commands.size());
    for (const auto& command : commands) items.emplace_back(command);
    io::TransportBatch batch(std::move(items));
    check(session->enqueue(batch) == io::Admission::accepted,
          "window trace batch was rejected despite default capacity");
    check(batch.empty(), "successful batch admission did not transfer its ownership");
  }

  void commit_step(const io::WindowCommand& command,
                   const PlannedStep& planned, bool check_output_barrier,
                   const std::string& label) {
    const auto& update = planned.update;
#ifdef CROWN_STATISTICS_ACCEPTANCE
    const auto c01_before = *session->workload_statistics();
    const bool c01_changed = update && (update->operation == SetOperation::insert
        ? !oracle.database.tables.at(update->table.value).contains(update->values)
        : oracle.database.tables.at(update->table.value).contains(update->values));
#endif
    check(session->status().pending_command_sequence == command.sequence,
          label + ": pending command status lost the external command sequence");
    std::set<SignedKey> expected_output;
    if (update) {
      check(session->status().pending_sequence == update->sequence,
            label + ": D06 pending sequence did not use the physical sequence domain");
      std::size_t calls = 0;
      while (session->status().phase != SessionPhase::prepared) {
        static_cast<void>(session->step());
        check(++calls < 100000, label + ": D06 work did not reach prepared state");
      }
      const auto reference_before = sql_exists_wrapper
          ? reference_session->snapshot() : Relation{};
      session->commit();
      const auto epoch = reference_session->apply(*update);
      expected_output = sql_exists_wrapper
          ? signed_difference(sql_exists_rows(reference_before),
                              sql_exists_rows(epoch.current))
          : reference_delta(epoch);
    } else {
      check(!session->status().pending_sequence,
            label + ": metadata-only barrier invented a physical pending sequence");
      check(session->step() == DeltaStep::prepared,
            label + ": metadata-only barrier did not prepare explicitly");
      session->commit();
    }
    oracle = planned.after;
    check(session->status().committed_sequence == oracle.physical_sequence,
          label + ": committed physical sequence differs from model");
    check(session->status().pending_sequence == std::nullopt &&
          session->status().pending_command_sequence == std::nullopt,
          label + ": completed step still exposes private input status");
    check(session->progress() == oracle.accepted,
          label + ": transport sequence/source position advanced at the wrong step");
    if (check_output_barrier && !expected_output.empty()) {
      expect_code([&] { static_cast<void>(session->begin_next_result()); },
                  "session_output_pending", label + ": unread physical output barrier");
    }
    check(collect_output(*session, label) == expected_output,
          label + ": raw signed output differs from independent reference epoch");
    compare_snapshot(*session, plan, *reference_session, oracle, label,
                     sql_exists_wrapper);
    compare_canonical(*session, oracle, label);
#ifdef CROWN_STATISTICS_ACCEPTANCE
    statistics_acceptance::event(c01_before, *session->workload_statistics(), update, c01_changed, label, std::nullopt, update.has_value());
    statistics_acceptance::sources(*session, oracle.database, label);
#endif
  }

  void process(const io::WindowCommand& command, bool check_output_barrier = false) {
    const auto steps = plan_independently(oracle, command);
    check(!steps.empty(), "list oracle returned an empty command expansion");
    auto result = session->begin_next_result();
    check(result == SessionBegin::pending,
          "window batch head did not begin as a pending command");
    check(session->status().pending_command_sequence == command.sequence,
          "begin did not expose the external window command sequence");
    for (std::size_t i = 0; i < steps.size(); ++i) {
      commit_step(command, steps[i], check_output_barrier,
                  "command " + std::to_string(command.sequence) +
                  " step " + std::to_string(i + 1));
      const auto expected_queue_events = static_cast<std::size_t>(
          session->status().queue ? session->status().queue->events : 0);
      if (i + 1 < steps.size()) {
        check(session->progress().sequence == oracle.completed_command_sequence,
              "an incomplete watermark acknowledged its source command");
        check(expected_queue_events > 0,
              "an incomplete watermark released its command from the queue");
        check(session->begin_next_result() == SessionBegin::pending,
              "next watermark step could not resume at the same queue head");
        check(session->status().pending_command_sequence == command.sequence,
              "resumed watermark step changed the pending external sequence");
      }
    }
  }
};

void finish_and_check_eof(Harness& harness) {
  check(harness.session->status().queue &&
        harness.session->status().queue->events == 0,
        "window trace retained acknowledged queue events");
  check(harness.session->begin_next_result() == SessionBegin::would_block,
        "open empty typed queue did not report would-block");
  harness.session->finish_input();
  check(harness.session->begin_next_result() == SessionBegin::end,
        "closed empty typed queue did not report end-of-input");
}

void projected_duplicates_and_watermark_prefixes() {
  Harness harness(projected_pair_plan(), window_options({TableId{0}}, 10));
  const std::vector<io::WindowCommand> commands{
      insert_command(1, 1, TableId{0}, {n(7), n(101)}, 0, 10),
      insert_command(2, 2, TableId{0}, {n(7), n(101)}, 0, 20),
      insert_command(3, 3, TableId{0}, {n(7), n(102)}, 0, 30),
      insert_command(4, 4, TableId{0}, {n(8), n(999)}, 1, 40),
      watermark_command(5, 9, 50),  // No deadline has reached the boundary.
      watermark_command(6, 10, 60), // Count-only, then physical expiration steps.
      watermark_command(7, 11, 70)};
  harness.enqueue(commands);
  harness.session->start();
  for (std::size_t i = 0; i < commands.size(); ++i)
    harness.process(commands[i], i >= 5);
  finish_and_check_eof(harness);
  check(harness.oracle.physical_sequence == 6 &&
        harness.oracle.completed_watermark == 11 &&
        harness.oracle.accepted.sequence == 7,
        "physical sequence, boundary watermark, or external command sequence was conflated");
}

void nonmonotone_times_and_alias_loop_expirations() {
  {
    Harness harness(unary_plan(), window_options({TableId{0}}, 5));
    const std::vector<io::WindowCommand> commands{
        insert_command(1, 1, TableId{0}, {n(9)}, 4),
        insert_command(2, 2, TableId{0}, {n(0)}, 0),
        watermark_command(3, 0)};
    harness.enqueue(commands);
    harness.session->start();
    for (const auto& command : commands) harness.process(command);
    check(harness.oracle.labels.size() == 2,
          "out-of-time insertion was incorrectly rejected before its timestamp expired");
  }

  {
    Harness harness(self_join_plan(), window_options({TableId{0}}, 5));
    const std::vector<io::WindowCommand> commands{
        insert_command(1, 1, TableId{0}, {n(1), n(1)}, 0),
        insert_command(2, 2, TableId{0}, {n(1), n(2)}, 1),
        insert_command(3, 3, TableId{0}, {n(2), n(1)}, 1),
        insert_command(4, 4, TableId{0}, {n(1), n(1)}, 2),
        watermark_command(5, 5),
        watermark_command(6, 6),
        watermark_command(7, 7)};
    harness.enqueue(commands);
    harness.session->start();
    for (std::size_t i = 0; i < commands.size(); ++i)
      harness.process(commands[i], i == 5);
    check(harness.oracle.labels.empty() &&
          harness.oracle.physical_sequence == 6,
          "self-join loop/alias fixture did not fully expire its physical set rows");
    finish_and_check_eof(harness);
  }
}

void global_and_relation_fifo_contracts() {
  {
    Harness harness(two_relation_plan(),
        window_options({TableId{0}, TableId{1}}, 1,
                       WindowFifoPolicy::global));
    const std::vector<io::WindowCommand> commands{
        insert_command(1, 1, TableId{0}, {n(1)}, 9),
        insert_command(2, 2, TableId{1}, {n(2)}, 0),
        watermark_command(3, 1)};
    harness.enqueue(commands);
    harness.session->start();
    harness.process(commands[0]);
    harness.process(commands[1]);
    const auto before = *harness.session->window_state();
    expect_code([&] { static_cast<void>(harness.session->begin_next_result()); },
                "window_fifo_violation", "global watermark full-order preflight");
    check(*harness.session->window_state() == before,
          "rejected global expiration changed any live label, count, or watermark prefix");
    check(harness.session->progress() == harness.oracle.accepted &&
          harness.session->status().pending_command_sequence == std::nullopt &&
          harness.session->status().input_failed &&
          harness.session->status().queue->events == 1,
          "FIFO preflight failure acknowledged or discarded its command");
    expect_code([&] { static_cast<void>(harness.session->begin_next_result()); },
                "input_failed", "sticky global FIFO head");
  }

  {
    Harness harness(two_relation_plan(),
        window_options({TableId{0}, TableId{1}}, 1,
                       WindowFifoPolicy::per_relation));
    const std::vector<io::WindowCommand> commands{
        insert_command(1, 1, TableId{0}, {n(1)}, 9),
        insert_command(2, 2, TableId{1}, {n(2)}, 0),
        watermark_command(3, 1)};
    harness.enqueue(commands);
    harness.session->start();
    harness.process(commands[0]);
    harness.process(commands[1]);
    harness.process(commands[2], true);
    check(harness.oracle.labels.size() == 1 &&
          harness.oracle.labels.front().id == 1,
          "per-relation policy did not expire the eligible second relation label");
    finish_and_check_eof(harness);
  }

  {
    Harness harness(two_relation_plan(),
        window_options({TableId{0}, TableId{1}}, 20,
                       WindowFifoPolicy::global));
    const std::vector<io::WindowCommand> commands{
        insert_command(1, 1, TableId{0}, {n(1)}, 0),
        insert_command(2, 2, TableId{1}, {n(2)}, 0),
        withdraw_command(3, 2)};
    harness.enqueue(commands);
    harness.session->start();
    harness.process(commands[0]);
    harness.process(commands[1]);
    expect_code([&] { static_cast<void>(harness.session->begin_next_result()); },
                "window_fifo_violation", "global explicit withdrawal order");
  }

  {
    Harness harness(two_relation_plan(),
        window_options({TableId{0}, TableId{1}}, 20,
                       WindowFifoPolicy::per_relation));
    const std::vector<io::WindowCommand> commands{
        insert_command(1, 1, TableId{0}, {n(1)}, 0),
        insert_command(2, 2, TableId{1}, {n(2)}, 0),
        insert_command(3, 3, TableId{0}, {n(3)}, 0),
        withdraw_command(4, 2)};
    harness.enqueue(commands);
    harness.session->start();
    for (const auto& command : commands) harness.process(command);
    check(harness.oracle.labels.size() == 2 &&
          harness.oracle.labels[0].id == 1 && harness.oracle.labels[1].id == 3,
          "per-relation withdrawal did not permit the oldest label of its own relation");
    finish_and_check_eof(harness);
  }
}

void rejected_head_preserves_committed_prefix(const PhysicalPlan& plan,
                                              WindowOptions options,
                                              std::vector<io::WindowCommand> commands,
                                              std::size_t prefix_count,
                                              std::string_view code,
                                              const std::string& label) {
  Harness harness(plan, std::move(options));
  harness.enqueue(commands);
  harness.session->start();
  for (std::size_t i = 0; i < prefix_count; ++i) harness.process(commands.at(i));
  const auto canonical_before = *harness.session->window_state();
  const auto snapshot_before = harness.session->snapshot();
  expect_code([&] { static_cast<void>(harness.session->begin_next_result()); },
              code, label);
  const auto canonical_after = *harness.session->window_state();
  check(canonical_after == canonical_before,
        label + ": rejected head changed the committed window prefix");
  check(harness.session->progress() == harness.oracle.accepted &&
        harness.session->status().input_failed &&
        !harness.session->status().pending_command_sequence &&
        harness.session->status().queue->events == 1,
        label + ": rejected input was acknowledged or lost its sticky head");
  check(harness.session->snapshot().rows.size() == snapshot_before.rows.size() &&
        harness.session->snapshot().sequence == snapshot_before.sequence,
        label + ": rejected input changed the committed physical snapshot");
  compare_snapshot(*harness.session, harness.plan, *harness.reference_session,
                   harness.oracle, label + " committed prefix");
  expect_code([&] { static_cast<void>(harness.session->begin_next_result()); },
              "input_failed", label + " retry");
}

void strict_time_labels_watermarks_and_overflow() {
  const auto unary = unary_plan();
  const auto options = window_options({TableId{0}}, 10);
  rejected_head_preserves_committed_prefix(unary, options,
      {watermark_command(1, 10),
       insert_command(2, 1, TableId{0}, {n(1)}, 9)},
      1, "late_window_event", "strict late insertion");
  rejected_head_preserves_committed_prefix(unary, options,
      {watermark_command(1, 10), watermark_command(2, 9)},
      1, "invalid_window_command", "decreasing watermark");
  rejected_head_preserves_committed_prefix(unary, options,
      {insert_command(1, 1, TableId{0}, {n(1)},
                      std::numeric_limits<std::uint64_t>::max() - 9)},
      0, "invalid_window_command", "expiration deadline overflow");
  rejected_head_preserves_committed_prefix(unary, options,
      {insert_command(1, 2, TableId{0}, {n(1)}, 0),
       insert_command(2, 2, TableId{0}, {n(2)}, 0)},
      1, "invalid_window_command", "duplicate insertion label");
  rejected_head_preserves_committed_prefix(unary, options,
      {insert_command(1, 0, TableId{0}, {n(1)}, 0)},
      0, "invalid_window_command", "zero insertion label");
  rejected_head_preserves_committed_prefix(unary, options,
      {insert_command(1, 2, TableId{0}, {n(1)}, 0),
       withdraw_command(2, 2),
       insert_command(3, 2, TableId{0}, {n(2)}, 0)},
      2, "invalid_window_command", "reused insertion label after withdrawal");
  rejected_head_preserves_committed_prefix(unary, options,
      {withdraw_command(1, 77)}, 0,
      "invalid_window_command", "unknown withdrawal label");

  {
    Harness harness(unary, options);
    const std::vector<io::WindowCommand> commands{
        watermark_command(1, 10),
        insert_command(2, 1, TableId{0}, {n(1)}, 10),
        watermark_command(3, 19),
        watermark_command(4, 20)};
    harness.enqueue(commands);
    harness.session->start();
    harness.process(commands[0]);
    harness.process(commands[1]);
    check(harness.oracle.labels.size() == 1 &&
          harness.oracle.labels.front().timestamp == 10,
          "insertion at the completed watermark was not accepted");
    harness.process(commands[2]);
    check(harness.oracle.labels.size() == 1 &&
          harness.oracle.completed_watermark == 19,
          "timestamp-at-watermark row expired before its deadline 20");
    harness.process(commands[3]);
    check(harness.oracle.labels.empty() &&
          harness.oracle.completed_watermark == 20,
          "timestamp-at-watermark row did not expire at its exact deadline 20");
    finish_and_check_eof(harness);
  }

  {
    Harness harness(unary, options);
    const std::vector<io::WindowCommand> commands{
        insert_command(1, 1, TableId{0}, {n(9)}, 9),
        insert_command(2, 2, TableId{0}, {n(0)}, 0)};
    harness.enqueue(commands);
    harness.session->start();
    for (const auto& command : commands) harness.process(command);
    check(harness.oracle.labels.size() == 2 &&
          harness.oracle.labels[0].timestamp > harness.oracle.labels[1].timestamp,
          "event-time ordering was incorrectly substituted for live-label insertion order");
  }
}

void invalid_window_options_and_managed_initial_state() {
  const auto plan = unary_plan();
  expect_code([&] {
    static_cast<void>(QuerySession::create_windowed(plan, WindowOptions{}));
  }, "invalid_window_options", "managed tables must be explicit");
  expect_code([&] {
    static_cast<void>(QuerySession::create_windowed(
        plan, window_options({TableId{0}}, 0)));
  }, "invalid_window_options", "window width must be positive");
  expect_code([&] {
    static_cast<void>(QuerySession::create_windowed(
        plan, window_options({TableId{4}}, 1)));
  }, "invalid_window_options", "managed table must exist");
  expect_code([&] {
    static_cast<void>(QuerySession::create_windowed(
        plan, window_options({TableId{0}, TableId{0}}, 1)));
  }, "invalid_window_options", "managed table list cannot duplicate a relation");

  const Catalog catalog{1,
      {{"managed", {{"x", ScalarType::int64}}},
       {"static", {{"y", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}},
      {{"managed", TableId{0}, {VariableId{0}}}},
      {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"managed", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
  const auto two_tables_with_one_managed = planner::lower_tree(catalog, query, tree);
  Database static_data;
  static_data.tables.resize(2);
  static_data.tables[1].insert({n(800)});
  Harness allowed(two_tables_with_one_managed,
      window_options({TableId{0}}, 10), static_data);
  check(allowed.session->snapshot().rows.empty(),
        "nonempty un-managed static relation was not retained as allowed initial data");

  Database managed_data;
  managed_data.tables.resize(2);
  managed_data.tables[0].insert({n(700)});
  expect_code([&] {
    static_cast<void>(QuerySession::create_windowed(
        two_tables_with_one_managed, managed_data,
        window_options({TableId{0}}, 10)));
  }, "invalid_window_initial_state", "managed tables must start empty");
}

void boolean_exists_counts_and_empty_delta_barriers() {
  Harness harness(exists_plan(), window_options({TableId{0}}, 2),
                  Database{}, true);
  const auto initial = harness.session->snapshot();
  check(initial.rows.size() == 1 &&
        initial.rows.front().values() == Row{Value{false}},
        "SQL EXISTS wrapper did not expose false for an empty physical source");
  compare_snapshot(*harness.session, harness.plan, *harness.reference_session,
                   harness.oracle, "empty SQL EXISTS source", true);
  const std::vector<io::WindowCommand> commands{
      insert_command(1, 1, TableId{0}, {n(1)}, 0),
      insert_command(2, 2, TableId{0}, {n(1)}, 0),
      watermark_command(3, 2),
      watermark_command(4, 2)};
  harness.enqueue(commands);
  harness.session->start();
  for (const auto& command : commands) harness.process(command);
  check(harness.oracle.labels.empty() && harness.oracle.physical_sequence == 2,
        "EXISTS duplicate-count window did not produce exactly the first insert and final erase");
  finish_and_check_eof(harness);
}

void pause_drain_and_stop_keep_only_committed_watermark_steps() {
  Harness harness(unary_plan(), window_options({TableId{0}}, 1));
  const std::vector<io::WindowCommand> commands{
      insert_command(1, 1, TableId{0}, {n(1)}, 0, 10),
      insert_command(2, 2, TableId{0}, {n(2)}, 0, 20),
      insert_command(3, 3, TableId{0}, {n(3)}, 0, 30),
      watermark_command(4, 1, 40)};
  harness.enqueue(commands);
  harness.session->start();
  for (std::size_t i = 0; i < 3; ++i) harness.process(commands[i]);
  const auto watermark_steps = plan_independently(harness.oracle, commands[3]);
  check(watermark_steps.size() == 3,
        "drain/stop fixture did not form a three-step watermark command");

  check(harness.session->begin_next_result() == SessionBegin::pending,
        "watermark did not begin for pause/drain fixture");
  harness.session->pause();
  check(harness.session->status().phase == SessionPhase::paused_pending,
        "pause did not preserve the current physical window step");
  harness.session->start_drain();
  harness.session->drain();
  auto first = watermark_steps[0];
  check(first.update.has_value(), "first watermark step unexpectedly lacks a physical erase");
  const auto first_epoch = harness.reference_session->apply(*first.update);
  (void)first_epoch;
  harness.oracle = first.after;
  check(harness.session->status().state == SessionState::paused &&
        harness.session->status().phase == SessionPhase::ready &&
        harness.session->progress().sequence == 3,
        "one-step drain advanced admission or acknowledged the whole watermark command");
  compare_snapshot(*harness.session, harness.plan, *harness.reference_session,
                   harness.oracle, "after draining only watermark step one");
  compare_canonical(*harness.session, harness.oracle,
                    "after draining only watermark step one");
  check(harness.session->status().window->completed_steps == 1 &&
        harness.session->status().window->total_steps == 3 &&
        harness.session->status().queue->events == 1,
        "one-step drain discarded the rest of the active command");

  harness.session->start();
  check(harness.session->begin_next_result() == SessionBegin::pending,
        "resuming did not return to watermark step two");
  const auto second = watermark_steps[1];
  check(second.update.has_value(), "second watermark step unexpectedly lacks a physical erase");
  harness.session->pause();
  harness.session->start_drain();
  harness.session->drain();
  static_cast<void>(harness.reference_session->apply(*second.update));
  harness.oracle = second.after;
  check(harness.session->progress().sequence == 3 &&
        harness.session->status().window->completed_steps == 2 &&
        harness.session->status().window->total_steps == 3 &&
        harness.session->status().queue->events == 1,
        "second one-step drain acknowledged or consumed the active watermark tail");
  compare_snapshot(*harness.session, harness.plan, *harness.reference_session,
                   harness.oracle, "after draining only watermark step two");

  harness.session->start();
  check(harness.session->begin_next_result() == SessionBegin::pending,
        "resuming did not return to the final watermark step");
  check(harness.session->status().pending_sequence == 6,
        "private final step used the wrong next physical sequence");
  static_cast<void>(harness.session->step());
  harness.session->stop();
  check(harness.session->status().state == SessionState::stopped &&
        harness.session->status().committed_sequence == 5 &&
        harness.session->progress().sequence == 3,
        "stop committed the private third step or acknowledged the unfinished command");
  const auto stopped_state = harness.session->window_state();
  check(stopped_state && stopped_state->labels.size() == 1 &&
        stopped_state->labels.front().label == 3 &&
        stopped_state->physical_sequence == 5 &&
        stopped_state->completed_command_sequence == 3 &&
        stopped_state->completed_watermark == 0 &&
        stopped_state->active_command &&
        stopped_state->active_command->completed_steps == 2 &&
        stopped_state->active_command->total_steps == 3 &&
        stopped_state->active_command->expiration_labels.empty(),
        "stop did not preserve exactly the committed watermark prefix while releasing expansion storage");
  const auto committed_snapshot = harness.session->snapshot();
  check(committed_snapshot.rows.size() == 1 &&
        committed_snapshot.rows.front().values() == Row{n(3)} &&
        committed_snapshot.sequence == 5 &&
        committed_snapshot.progress.sequence == 3,
        "stopped snapshot did not expose the committed physical/window prefix");
  harness.session->drop();
  check(committed_snapshot.rows.size() == 1 &&
        committed_snapshot.rows.front().values() == Row{n(3)},
        "owned committed snapshot was invalidated by terminal cleanup");
}

void run() {
  run_case("projection, duplicate full rows, boundaries and prefixes",
           projected_duplicates_and_watermark_prefixes);
  run_case("out-of-time labels and self-join loop/alias expirations",
           nonmonotone_times_and_alias_loop_expirations);
  run_case("global and per-relation FIFO contracts",
           global_and_relation_fifo_contracts);
  run_case("late, decreasing, overflow and label validation",
           strict_time_labels_watermarks_and_overflow);
  run_case("window options and initialized static/managed tables",
           invalid_window_options_and_managed_initial_state);
  run_case("Boolean EXISTS and duplicate counts",
           boolean_exists_counts_and_empty_delta_barriers);
  run_case("pause, one-step drain, stop and prefix cleanup",
           pause_drain_and_stop_keep_only_committed_watermark_steps);
}
}  // namespace

int main() {
  try {
    run();
#ifdef CROWN_STATISTICS_ACCEPTANCE
    statistics_acceptance::print();
#endif
    std::cout << "operational window list-oracle acceptance checks passed\n";
  } catch (const std::exception& failure) {
    std::cerr << failure.what() << '\n';
    return 1;
  }
  return 0;
}

