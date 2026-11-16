#include "crown/api/error.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/delta.hpp"
#include "evaluator.hpp"
#ifdef CROWN_STATISTICS_ACCEPTANCE
#include "statistics_acceptance.hpp"
#endif

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <initializer_list>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
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
void expect_error_code(Action&& action, const std::string& expected,
                       const std::string& label) {
  try {
    action();
  } catch (const Error& failure) {
    check(failure.code() == expected,
          label + ": expected " + expected + ", got " + failure.code());
    return;
  }
  check(false, label + ": invalid options were accepted");
}

void check_profile_text(const DeltaRuntimeProfile& profile,
                        const std::string& label) {
  for (const auto text : {profile.semantics, profile.query_class,
                          profile.arithmetic, profile.update_contract,
                          profile.backend, profile.state_bound,
                          profile.maintenance_bound,
                          profile.preparation_bound, profile.candidate_bound,
                          profile.accepted_bound, profile.finalization_bound,
                          profile.public_startup_bound, profile.ordered_costs,
                          profile.assumptions, profile.output_accounting}) {
    check(!text.empty() && text.find('\0') == std::string_view::npos,
          label + ": profile text is empty or unreadable");
  }
}

Value n(std::int64_t value) { return value; }

VariableSet variables(std::initializer_list<std::size_t> values) {
  VariableSet result;
  for (const auto value : values) result.insert(VariableId{value});
  return result;
}

DeltaOptions replay_options() {
  DeltaOptions result;
  result.mode = DeltaMode::maintenance;
  result.live_maintenance = LiveMaintenance::on_output;
  result.completion = DeltaCompletion::ordered_replay;
  return result;
}

Relation a04(const PhysicalPlan& plan, const Database& database) {
  return reference::evaluate(plan.catalog(), plan.query(), database);
}

std::set<SignedKey> difference(const Relation& before,
                              const Relation& after) {
  std::set<SignedKey> result;
  for (const auto& row : after)
    if (!before.contains(row)) result.emplace(SetOperation::insert, row);
  for (const auto& row : before)
    if (!after.contains(row)) result.emplace(SetOperation::erase, row);
  return result;
}

Relation drain_current(SupportRuntime::ResultCursor cursor,
                       const storage::TupleLayout& expected_layout,
                       const std::string& label) {
  Relation result;
  check(cursor.layout().same_token(expected_layout),
        label + ": current result layout differs from the runtime");
  while (auto tuple = cursor.next()) {
    check(tuple->layout().same_token(expected_layout),
          label + ": current tuple changed layout");
    check(result.insert(tuple->values()).second,
          label + ": current result cursor emitted a duplicate row");
  }
  check(cursor.state() == ResultCursorState::exhausted && !cursor.active(),
        label + ": current result cursor retained its lease");
  return result;
}

std::vector<Relation> a04_live(const PhysicalPlan& plan,
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

struct Event {
  std::vector<SignedKey> raw;
  std::vector<DeltaStage> stages;
  DeltaMetrics metrics;
};

class ReplayRun {
 public:
  ReplayRun(PhysicalPlan plan, std::size_t table_count)
      : runtime_(std::move(plan), replay_options()) {
    database_.tables.resize(table_count);
#ifdef CROWN_STATISTICS_ACCEPTANCE
    statistics_acceptance::enable(runtime_);
#endif
    check(runtime_.completion() == DeltaCompletion::ordered_replay,
          "explicit ordered replay did not resolve to the replay strategy");
  }

  void seed(TableId table, Row row, const std::string& label) {
    const auto sequence = ++sequence_;
    auto epoch = runtime_.apply(
        {sequence, table, SetOperation::insert, row});
    check(epoch.sequence() == sequence && epoch.remaining() == 0 &&
              !epoch.active(),
          label + ": maintenance seed prepared output");
    check(!epoch.next(), label + ": maintenance seed returned a record");
    check(database_.tables.at(table.value).insert(std::move(row)).second,
          label + ": fixture seeded a duplicate physical row");
    runtime_.check_invariants();
  }

  void bootstrap(const std::string& label) {
    check(runtime_.mode() == DeltaMode::maintenance,
          label + ": bootstrap did not start in maintenance mode");
    static_cast<void>(runtime_.set_mode(DeltaMode::delta));
    check(runtime_.live_snapshot().has_value(),
          label + ": delta bootstrap did not publish L");
    check_current(label + " bootstrap");
  }

  void maintenance(const std::string& label) {
    static_cast<void>(runtime_.set_mode(DeltaMode::maintenance));
    check(!runtime_.live_snapshot(),
          label + ": maintenance mode retained a live image");
    check_current(label + " maintenance");
  }

  Event apply(TableId table, SetOperation operation, Row row,
              const std::string& label) {
    const auto before = a04(runtime_.plan(), database_);
    auto after_database = database_;
    auto& relation = after_database.tables.at(table.value);
    const bool changed = operation == SetOperation::insert
        ? relation.insert(row).second : relation.erase(row) == 1;
    check(changed, label + ": source update did not cross set membership");
    const auto expected = difference(
        before, a04(runtime_.plan(), after_database));

#ifdef CROWN_STATISTICS_ACCEPTANCE
    const auto c01_before = runtime_.workload_statistics();
    const PhysicalSetUpdate c01_update{sequence_ + 1, table, operation, row};
#endif
    const auto sequence = ++sequence_;
    auto epoch = runtime_.apply({sequence, table, operation, std::move(row)});
    check(epoch.sequence() == sequence,
          label + ": committed sequence differs from the input");
    check(epoch.remaining() == expected.size() &&
              epoch.active() == !expected.empty(),
          label + ": signed output cardinality or lease state differs from A04");

    Event result;
    std::set<SignedKey> unique;
    std::uint64_t ordinal = 0;
    while (auto record = epoch.next()) {
      check(record->ordinal == ++ordinal,
            label + ": signed result ordinals are not contiguous");
      check(record->tuple.layout().same_token(epoch.layout()),
            label + ": signed result tuple changed layout");
      check(record->tuple.values().size() == epoch.layout().fields().size(),
            label + ": signed result has the wrong arity");
      const SignedKey key{record->operation, record->tuple.values()};
      check(unique.insert(key).second,
            label + ": epoch emitted a duplicate operation/row pair");
      result.raw.push_back(key);
    }
    check(unique == expected && result.raw.size() == expected.size(),
          label + ": raw signed output differs from the independent A04 delta");
    check(epoch.remaining() == 0 && !epoch.active() && runtime_.ready(),
          label + ": draining output did not release the writer barrier");
    check(!epoch.next(), label + ": exhausted epoch returned another record");

    result.stages.assign(epoch.stages().begin(), epoch.stages().end());
    result.metrics = epoch.metrics();
    check(result.metrics.candidates == result.metrics.accepted &&
              result.metrics.rejected == 0 &&
              result.metrics.earlier_probes == 0,
          label + ": ordered replay performed canonical candidate rejection");
    if (result.metrics.accepted != 0) {
      check(result.metrics.replay_first_work != 0 &&
                result.metrics.replay_termination_work != 0 &&
                result.metrics.replay_max_first_work != 0 &&
                result.metrics.replay_max_last_work != 0,
            label + ": productive replay omitted first/termination phase work");
      if (result.metrics.accepted > 1)
        check(result.metrics.replay_results_work != 0 &&
                  result.metrics.replay_max_next_work != 0,
              label + ": multi-answer replay omitted between-result work");
    }
    std::size_t stage_outputs = 0;
    std::uint64_t stage_candidates = 0;
    std::uint64_t stage_accepted = 0;
    for (const auto& stage : result.stages) {
      check(stage.candidates == stage.accepted && stage.rejected == 0,
            label + ": a route stage rejected a canonical duplicate");
      check(stage.output_count == stage.accepted,
            label + ": accepted replay rows do not match the route spool interval");
      check(stage.output_begin == stage_outputs,
            label + ": route output intervals are not contiguous");
      check(stage.output_count <= result.raw.size() - stage_outputs,
            label + ": route output interval exceeds the raw result");
      stage_outputs += stage.output_count;
      stage_candidates += stage.candidates;
      stage_accepted += stage.accepted;
    }
    check(stage_outputs == result.raw.size() &&
              stage_candidates == result.metrics.candidates &&
              stage_accepted == result.metrics.accepted,
          label + ": route-stage counters do not reconcile with the epoch");

#ifdef CROWN_STATISTICS_ACCEPTANCE
    statistics_acceptance::event(c01_before, runtime_.workload_statistics(), c01_update, changed, label,
        std::span<const DerivationChange>{epoch.input().input.derivations});
#endif
    database_ = std::move(after_database);
    check_current(label + " after-state");
    return result;
  }

  [[nodiscard]] const DeltaRuntime& runtime() const { return runtime_; }
  [[nodiscard]] const Database& database() const { return database_; }

 private:
  void check_current(const std::string& label) {
    const auto expected = a04(runtime_.plan(), database_);
    check(runtime_.has_answer() == !expected.empty(),
          label + ": answer truth differs from A04");
    check(drain_current(runtime_.core_results(), runtime_.result_layout(),
                        label + " core") == expected,
          label + ": current core results differ from A04");
    check(drain_current(runtime_.results(), runtime_.result_layout(),
                        label + " output") == expected,
          label + ": current output results differ from A04");
    if (runtime_.mode() == DeltaMode::delta) {
      const auto live = runtime_.live_snapshot();
      check(live.has_value() && live->sequence == runtime_.sequence(),
            label + ": L snapshot is missing or stale");
      check(live->factors == a04_live(runtime_.plan(), expected),
            label + ": maintained L factors differ from independent A04 projections");
    }
    runtime_.check_invariants();
#ifdef CROWN_STATISTICS_ACCEPTANCE
    statistics_acceptance::sources(runtime_, database_, label);
#endif
  }

  DeltaRuntime runtime_;
  Database database_;
  std::uint64_t sequence_ = 0;
};

PhysicalPlan root_child_plan() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}}},
       {"s", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}}},
       {"s", TableId{1}, {VariableId{0}, VariableId{1}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "y"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, variables({0}), {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, variables({0, 1}), {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

void runtime_profile_reports_effective_strategy_and_limits() {
  DeltaRuntime default_runtime(root_child_plan());
  const auto automatic = default_runtime.profile();
  check(automatic.mode == DeltaMode::delta &&
            automatic.live_maintenance == LiveMaintenance::on_output &&
            automatic.completion == DeltaCompletion::ordered_replay,
        "default automatic profile did not resolve row-coupled replay");
  check(automatic.candidate_transitions ==
                DeltaBound::bounded_indexed_actions &&
            automatic.accepted_transitions ==
                DeltaBound::bounded_indexed_actions &&
            automatic.publication == DeltaPublication::eager_atomic_spool &&
            !automatic.public_first_record_constant_delay,
        "default replay profile reported the wrong internal/public bounds");
  check(automatic.view == ResultView::sql &&
            automatic.query_factors ==
                default_runtime.plan().enumeration().steps.size() &&
            automatic.spool_row_limit ==
                default_runtime.options().spool_row_limit &&
            automatic.spool_byte_limit ==
                default_runtime.options().spool_byte_limit,
        "default profile did not expose the effective view, shape or caps");

  for (const auto policy : {LiveMaintenance::incremental,
                             LiveMaintenance::eager}) {
    DeltaOptions options;
    options.live_maintenance = policy;
    DeltaRuntime runtime(root_child_plan(), options);
    const auto profile = runtime.profile();
    check(profile.mode == DeltaMode::delta &&
              profile.live_maintenance == policy &&
              profile.completion == DeltaCompletion::anchored,
          "automatic comparison policy did not resolve anchored completion");
    check(profile.candidate_transitions ==
                  DeltaBound::bounded_indexed_actions &&
              profile.accepted_transitions == DeltaBound::unclaimed,
          "anchored comparison path claimed a bounded accepted transition");
  }

  DeltaOptions root_first_options;
  root_first_options.completion = DeltaCompletion::root_first;
  DeltaRuntime root_first_runtime(root_child_plan(), root_first_options);
  const auto root_first = root_first_runtime.profile();
  check(root_first.completion == DeltaCompletion::root_first &&
            root_first.candidate_transitions == DeltaBound::unclaimed &&
            root_first.accepted_transitions == DeltaBound::unclaimed,
        "root-first profile claimed bounded candidate or accepted transitions");

  DeltaOptions customized;
  customized.view = ResultView::core;
  customized.spool_row_limit = 17;
  customized.spool_byte_limit = 4096;
  DeltaRuntime customized_runtime(root_child_plan(), customized);
  const auto customized_profile = customized_runtime.profile();
  check(customized_profile.view == ResultView::core &&
            customized_profile.spool_row_limit == 17 &&
            customized_profile.spool_byte_limit == 4096,
        "profile did not reflect configured view and spool caps");
}

void runtime_profile_tracks_active_mode_changes() {
  DeltaOptions options;
  options.mode = DeltaMode::maintenance;
  DeltaRuntime runtime(root_child_plan(), options);

  const auto maintenance = runtime.profile();
  check(maintenance.mode == DeltaMode::maintenance &&
            maintenance.publication == DeltaPublication::no_delta_output &&
            maintenance.candidate_transitions == DeltaBound::unclaimed &&
            maintenance.accepted_transitions == DeltaBound::unclaimed,
        "maintenance profile advertised delta output or bounds");

  static_cast<void>(runtime.set_mode(DeltaMode::delta));
  const auto delta = runtime.profile();
  check(delta.mode == DeltaMode::delta &&
            delta.publication == DeltaPublication::eager_atomic_spool &&
            delta.candidate_transitions ==
                DeltaBound::bounded_indexed_actions &&
            delta.accepted_transitions ==
                DeltaBound::bounded_indexed_actions,
        "profile did not expose the active delta mode after bootstrap");

  static_cast<void>(runtime.set_mode(DeltaMode::maintenance));
  const auto switched_off = runtime.profile();
  check(switched_off.mode == DeltaMode::maintenance &&
            switched_off.publication == DeltaPublication::no_delta_output &&
            switched_off.candidate_transitions == DeltaBound::unclaimed &&
            switched_off.accepted_transitions == DeltaBound::unclaimed,
        "profile retained delta claims after switching to maintenance");

  static_cast<void>(runtime.set_mode(DeltaMode::delta));
  const auto switched_back = runtime.profile();
  check(switched_back.mode == DeltaMode::delta &&
            switched_back.completion == DeltaCompletion::ordered_replay &&
            switched_back.accepted_transitions ==
                DeltaBound::bounded_indexed_actions,
        "profile did not restore replay claims after rebootstrap");
}

void runtime_profile_rejects_incompatible_replay_options() {
  for (const auto policy : {LiveMaintenance::incremental,
                             LiveMaintenance::eager}) {
    DeltaOptions options;
    options.live_maintenance = policy;
    options.completion = DeltaCompletion::ordered_replay;
    expect_error_code(
        [&] { static_cast<void>(DeltaRuntime(root_child_plan(), options)); },
        "invalid_options", "ordered replay with a comparison policy");
  }
}

DeltaRuntimeProfile detached_delta_profile() {
  DeltaOptions options;
  options.spool_row_limit = 23;
  options.spool_byte_limit = 8192;
  DeltaRuntime runtime(root_child_plan(), options);
  return runtime.profile();
}

void runtime_profile_text_outlives_its_facade() {
  const auto detached = detached_delta_profile();
  check(detached.mode == DeltaMode::delta &&
            detached.completion == DeltaCompletion::ordered_replay &&
            detached.spool_row_limit == 23 &&
            detached.spool_byte_limit == 8192,
        "detached profile lost its value fields after facade destruction");
  check_profile_text(detached, "detached runtime profile");
}

void ancestor_child_crossings_have_no_replay_tail() {
  ReplayRun run(root_child_plan(), 2);
  run.seed(TableId{0}, {n(7)}, "ancestor/child root seed");
  run.bootstrap("ancestor/child");
  check(a04(run.runtime().plan(), run.database()).empty(),
        "ancestor/child fixture unexpectedly answered before the child row");

  const Row answer{n(7), n(70)};
  const auto inserted = run.apply(TableId{1}, SetOperation::insert,
      {n(7), n(70)}, "ancestor/child insertion");
  check(inserted.raw == std::vector<SignedKey>{{SetOperation::insert, answer}},
        "ancestor/child insertion did not emit its one answer");
  check(inserted.metrics.changed_keys == 2 &&
            inserted.metrics.candidates == 1 && inserted.metrics.accepted == 1,
        "ancestor/child insertion did not replay both crossings with one owner");
  check(inserted.metrics.finalization_work > 0 &&
            inserted.metrics.finalization_changed_keys ==
                inserted.metrics.changed_keys &&
            inserted.metrics.finalization_view_entry_bound > 0 &&
            inserted.metrics.finalization_kernel_record_bound > 0 &&
            inserted.metrics.finalization_driver_changes > 0 &&
            inserted.metrics.finalization_undo_entries > 0,
        "replay finalization work and retained state were not charged separately");

  const auto erased = run.apply(TableId{1}, SetOperation::erase,
      {n(7), n(70)}, "ancestor/child deletion");
  check(erased.raw == std::vector<SignedKey>{{SetOperation::erase, answer}},
        "ancestor/child deletion did not emit its one retraction");
  check(erased.metrics.changed_keys == 2 &&
            erased.metrics.candidates == 1 && erased.metrics.accepted == 1,
        "ancestor/child deletion enumerated a duplicate candidate tail");
}

PhysicalPlan dead_child_plan() { return root_child_plan(); }

void dead_changed_keys_are_filtered_before_root_activation() {
  constexpr std::size_t count = 48;
  ReplayRun run(dead_child_plan(), 2);
  run.bootstrap("dead-child queue");

  std::uint64_t filtered_witnesses = 0;
  for (std::size_t i = 0; i < count; ++i) {
    const auto y = n(static_cast<std::int64_t>(i));
    const auto event = run.apply(TableId{1}, SetOperation::insert,
        {n(7), y}, "dead child E crossing " + std::to_string(i));
    check(event.raw.empty() && event.metrics.changed_keys == 1 &&
              event.metrics.candidates == 0 && event.metrics.accepted == 0,
          "a dead child E crossing produced a candidate or output");
    check(event.metrics.replay_queue_inserts == 0 &&
              event.metrics.replay_queue_peak == 0,
          "an initially dead child key entered the productive replay queue");
    filtered_witnesses += event.metrics.replay_witness_tests;
  }
  check(filtered_witnesses >= count,
        "dead changed keys were not checked against initial parent support");

  const auto activated = run.apply(TableId{0}, SetOperation::insert,
      {n(7)}, "later productive root activation");
  check(activated.raw.size() == count && activated.metrics.candidates == count &&
            activated.metrics.accepted == count,
        "root activation did not complete every previously dead child key");
  check(activated.metrics.replay_queue_pops > 0,
        "productive root anchor did not pass through the replay queue");
}

PhysicalPlan sibling_alias_plan() {
  const Catalog catalog{1,
      {{"edge", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}}}};
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

std::set<SignedKey> stage_records(const Event& event, const DeltaStage& stage) {
  std::set<SignedKey> result;
  for (std::size_t offset = 0; offset < stage.output_count; ++offset)
    result.insert(event.raw.at(stage.output_begin + offset));
  return result;
}

void sibling_alias_prefixes_wait_for_their_route() {
  ReplayRun run(sibling_alias_plan(), 1);
  run.seed(TableId{0}, {n(1), n(2)}, "alias cycle edge one");
  run.seed(TableId{0}, {n(2), n(1)}, "alias cycle edge two");
  run.bootstrap("sibling aliases");

  const auto inserted = run.apply(TableId{0}, SetOperation::insert,
      {n(1), n(1)}, "sibling alias loop insertion");
  check(inserted.stages.size() == 2 &&
            inserted.stages[0].output_count == 1 &&
            inserted.stages[1].output_count == 2,
        "sibling alias insertion changed its physical-prefix output ownership");
  const std::set<SignedKey> first_insert{{SetOperation::insert,
      Row{n(1), n(1), n(2)}}};
  const std::set<SignedKey> second_insert{
      {SetOperation::insert, Row{n(2), n(1), n(1)}},
      {SetOperation::insert, Row{n(1), n(1), n(1)}}};
  check(stage_records(inserted, inserted.stages[0]) == first_insert &&
            stage_records(inserted, inserted.stages[1]) == second_insert,
        "a later sibling alias answer appeared in an earlier route prefix");
  check(inserted.metrics.anchor_child_rows > 0,
        "rerooted sibling completion did not read the current child-L index");

  const auto erased = run.apply(TableId{0}, SetOperation::erase,
      {n(1), n(1)}, "sibling alias loop deletion");
  check(erased.stages.size() == 2 && erased.stages[0].output_count == 2 &&
            erased.stages[1].output_count == 1,
        "sibling alias deletion changed its physical-prefix output ownership");
  const std::set<SignedKey> first_erase{
      {SetOperation::erase, Row{n(1), n(1), n(1)}},
      {SetOperation::erase, Row{n(1), n(1), n(2)}}};
  const std::set<SignedKey> second_erase{
      {SetOperation::erase, Row{n(2), n(1), n(1)}}};
  check(stage_records(erased, erased.stages[0]) == first_erase &&
            stage_records(erased, erased.stages[1]) == second_erase,
        "an earlier sibling alias prefix consumed a later deletion route");
}

PhysicalPlan sibling_plan() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}}},
       {"s", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}},
       {"t", {{"x", ScalarType::int64}, {"z", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64},
                     {"z", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}}},
       {"s", TableId{1}, {VariableId{0}, VariableId{1}}},
       {"t", TableId{2}, {VariableId{0}, VariableId{2}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "y"},
       {VariableId{2}, "z"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, variables({0}),
         {NodeId{1}, NodeId{2}}, 0, {}},
       {"s", NodeKind::native, variables({0, 1}), {}, 1, {}},
       {"t", NodeKind::native, variables({0, 2}), {}, 2, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

void deleting_parent_prunes_queued_child_before_its_turn() {
  ReplayRun run(sibling_plan(), 3);
  run.seed(TableId{0}, {n(1)}, "prune root seed");
  run.seed(TableId{1}, {n(1), n(10)}, "prune S seed");
  run.seed(TableId{2}, {n(1), n(20)}, "prune T seed");
  run.bootstrap("queued child deletion");
  check(a04(run.runtime().plan(), run.database()).size() == 1,
        "queued child fixture did not start with one answer");

  const auto deleted = run.apply(TableId{1}, SetOperation::erase,
      {n(1), n(10)}, "ancestor fragment removes future sibling key");
  check(deleted.raw == std::vector<SignedKey>{{SetOperation::erase,
      Row{n(1), n(10), n(20)}}},
        "ancestor deletion did not emit its unique answer retraction");
  check(deleted.metrics.changed_keys == 2 && deleted.metrics.candidates == 1 &&
            deleted.metrics.accepted == 1,
        "a queued future child became a duplicate candidate after parent deletion");
  check(deleted.metrics.replay_queue_pops == 1 &&
            deleted.metrics.replay_queue_erases == 1,
        "parent fragment did not remove the now-dead future child from the queue");
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

void shared_parent_separator_keeps_child_until_last_parent() {
  ReplayRun run(shared_separator_plan(), 2);
  run.seed(TableId{0}, {n(1), n(7)}, "shared separator parent one");
  run.seed(TableId{0}, {n(2), n(7)}, "shared separator parent two");
  run.seed(TableId{1}, {n(7), n(9)}, "shared separator child");
  run.bootstrap("shared separator replay");

  const auto first = run.apply(TableId{0}, SetOperation::erase,
      {n(1), n(7)}, "shared separator two-to-one");
  check(first.raw == std::vector<SignedKey>{{SetOperation::erase,
      Row{n(1), n(7), n(9)}}},
        "first parent deletion produced the wrong answer delta");
  check(run.runtime().live_snapshot()->factors[1].contains(
            Row{n(7), n(9)}),
        "child L disappeared while its separator still had a parent");
  check(first.metrics.live_separator_updates == 1 &&
            first.metrics.live_separator_crossings == 0 &&
            first.metrics.live_child_index_updates == 0,
        "shared child index changed before the last parent disappeared");

  const auto last = run.apply(TableId{0}, SetOperation::erase,
      {n(2), n(7)}, "shared separator one-to-zero");
  check(last.raw == std::vector<SignedKey>{{SetOperation::erase,
      Row{n(2), n(7), n(9)}}},
        "last parent deletion produced the wrong answer delta");
  check(!run.runtime().live_snapshot()->factors[1].contains(
            Row{n(7), n(9)}),
        "child L survived the last-parent certificate");
  check(last.metrics.live_separator_updates == 1 &&
            last.metrics.live_separator_crossings == 1 &&
            last.metrics.live_child_index_updates == 1,
        "last-parent deletion did not remove the child key from B");
}

PhysicalPlan nullary_product_plan() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}}},
       {"s", {{"y", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}}},
       {"s", TableId{1}, {VariableId{1}}}},
      {{VariableId{1}, "y"}, {VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"product", NodeKind::generalized, {}, {NodeId{1}, NodeId{2}}, {}, {}},
       {"r", NodeKind::native, variables({0}), {}, 0, {}},
       {"s", NodeKind::native, variables({1}), {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

void nullary_anchor_product_and_rebootstrap() {
  ReplayRun run(nullary_product_plan(), 2);
  run.seed(TableId{0}, {n(1)}, "nullary product row one");
  run.seed(TableId{0}, {n(2)}, "nullary product row two");
  run.bootstrap("nullary product");
  check(a04(run.runtime().plan(), run.database()).empty(),
        "nullary fixture answered before either child completed");

  const auto inserted = run.apply(TableId{1}, SetOperation::insert,
      {n(10)}, "nullary separator activation");
  const std::set<SignedKey> expected_insertions{
      {SetOperation::insert, Row{n(10), n(1)}},
      {SetOperation::insert, Row{n(10), n(2)}}};
  check(std::set<SignedKey>(inserted.raw.begin(), inserted.raw.end()) ==
            expected_insertions && inserted.raw.size() == 2,
        "nullary anchor did not emit the complete disconnected product");
  const auto& steps = run.runtime().plan().enumeration().steps;
  const auto root = std::find_if(steps.begin(), steps.end(),
      [](const EnumerationStep& step) { return step.node == NodeId{0}; });
  check(root != steps.end() &&
            run.runtime().live_snapshot()->factors.at(
                static_cast<std::size_t>(root - steps.begin())).contains(Row{}),
        "nullary root key was not retained in L");

  const auto erased = run.apply(TableId{1}, SetOperation::erase,
      {n(10)}, "nullary separator deactivation");
  const std::set<SignedKey> expected_deletions{
      {SetOperation::erase, Row{n(10), n(1)}},
      {SetOperation::erase, Row{n(10), n(2)}}};
  check(std::set<SignedKey>(erased.raw.begin(), erased.raw.end()) ==
            expected_deletions && erased.raw.size() == 2,
        "nullary anchor did not retract the complete disconnected product");

  run.maintenance("nullary rebootstrap");
  run.seed(TableId{1}, {n(11)}, "maintenance-only nullary row");
  run.bootstrap("nullary second bootstrap");
  check(run.runtime().completion() == DeltaCompletion::ordered_replay,
        "mode rebootstrap changed the selected completion strategy");
}

}  // namespace

int main() {
  try {
    runtime_profile_reports_effective_strategy_and_limits();
    runtime_profile_tracks_active_mode_changes();
    runtime_profile_rejects_incompatible_replay_options();
    runtime_profile_text_outlives_its_facade();
    ancestor_child_crossings_have_no_replay_tail();
    dead_changed_keys_are_filtered_before_root_activation();
    sibling_alias_prefixes_wait_for_their_route();
    deleting_parent_prunes_queued_child_before_its_turn();
    shared_parent_separator_keeps_child_until_last_parent();
    nullary_anchor_product_and_rebootstrap();
    std::cout << "ordered delta replay fixtures passed\n";
#ifdef CROWN_STATISTICS_ACCEPTANCE
    statistics_acceptance::print();
#endif
  } catch (const std::exception& failure) {
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
