#include "crown/planner/lower.hpp"
#include "crown/runtime/delta.hpp"
#include "evaluator.hpp"
#include "native_input.hpp"

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <initializer_list>
#include <map>
#include <set>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace {
using namespace crown;
using namespace crown::runtime;
using SignedKey = std::pair<SetOperation, Row>;

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

Value n(std::int64_t value) { return value; }

VariableSet variables(std::initializer_list<std::size_t> values) {
  VariableSet result;
  for (const auto value : values) result.insert(VariableId{value});
  return result;
}

DeltaOptions options(DeltaCompletion completion) {
  DeltaOptions result;
  result.mode = DeltaMode::maintenance;
  result.live_maintenance = completion == DeltaCompletion::ordered_replay
      ? LiveMaintenance::on_output : LiveMaintenance::incremental;
  result.completion = completion;
  return result;
}

PhysicalPlan chain_plan() {
  const Catalog catalog{1,
      {{"r", {{"a", ScalarType::int64}, {"x", ScalarType::int64}}},
       {"s", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}}}};
  const Query query{{{"a", ScalarType::int64}, {"x", ScalarType::int64},
                     {"y", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"s", TableId{1}, {VariableId{1}, VariableId{2}}}},
      {{VariableId{0}, "a"}, {VariableId{1}, "x"},
       {VariableId{2}, "y"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, variables({0, 1}), {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, variables({1, 2}), {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

Relation a04(const auto& plan, const Database& database) {
  return reference::evaluate(reference::input::catalog(plan.catalog()), reference::input::query(plan.query()), database);
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

Relation drain_current(SupportRuntime::ResultCursor cursor,
                       const storage::TupleLayout& layout,
                       const std::string& label) {
  Relation result;
  check(cursor.layout().same_token(layout),
        label + ": result cursor layout differs from the runtime");
  while (auto tuple = cursor.next()) {
    check(tuple->layout().same_token(layout),
          label + ": current tuple changed layout");
    check(result.insert(crown::storage::export_row(tuple->values())).second,
          label + ": current results contain a duplicate row");
  }
  check(cursor.state() == ResultCursorState::exhausted && !cursor.active(),
        label + ": current result cursor retained its lease");
  return result;
}

struct Event {
  std::vector<SignedKey> raw;
  std::vector<DeltaStage> stages;
  DeltaMetrics metrics;
};

Event collect(DeltaRuntime& runtime, DeltaRuntime::Epoch& epoch,
              const std::set<SignedKey>& expected, const std::string& label) {
  check(epoch.remaining() == expected.size() &&
            epoch.active() == !expected.empty(),
        label + ": raw signed cardinality or lease state differs from A04");
  Event result;
  std::set<SignedKey> unique;
  std::uint64_t ordinal = 0;
  while (auto record = epoch.next()) {
    check(record->ordinal == ++ordinal,
          label + ": signed result ordinals are not contiguous");
    check(record->tuple.layout().same_token(epoch.layout()),
          label + ": signed tuple changed layout");
    const SignedKey key{record->operation, crown::storage::export_row(record->tuple.values())};
    check(unique.insert(key).second,
          label + ": runtime emitted a duplicate signed row");
    result.raw.push_back(key);
  }
  check(unique == expected && result.raw.size() == expected.size(),
        label + ": raw signed result differs from the independent A04 delta");
  check(epoch.remaining() == 0 && !epoch.active() && runtime.ready(),
        label + ": draining output did not release the writer barrier");
  check(!epoch.next(), label + ": exhausted output returned another record");
  result.stages.assign(epoch.stages().begin(), epoch.stages().end());
  result.metrics = epoch.metrics();
  check(result.stages.size() == 1,
        label + ": one native input did not produce one route stage");
  check(result.stages.front().output_count == result.raw.size(),
        label + ": route spool count differs from raw signed cardinality");
  return result;
}

class ScaleRun {
 public:
  ScaleRun(PhysicalPlan plan, std::size_t count)
      : replay_(plan, options(DeltaCompletion::ordered_replay)),
        anchored_(std::move(plan), options(DeltaCompletion::anchored)) {
    database_.tables.resize(2);
    check(replay_.completion() == DeltaCompletion::ordered_replay &&
              anchored_.completion() == DeltaCompletion::anchored,
          "comparison runtimes did not retain their explicit completion modes");
    for (std::size_t i = 0; i < count; ++i) {
      const auto a = n(static_cast<std::int64_t>(i));
      seed({a, n(7)});
    }
  }

  void bootstrap(std::size_t count) {
    static_cast<void>(replay_.set_mode(DeltaMode::delta));
    static_cast<void>(anchored_.set_mode(DeltaMode::delta));
    check_current(replay_, "ordered replay bootstrap");
    check_current(anchored_, "anchored bootstrap");
    check(a04(replay_.plan(), database_).empty(),
          "scale fixture answered before S was inserted");
    check(count != 0, "scale fixture requires at least one root row");
  }

  std::pair<Event, Event> update(SetOperation operation, const std::string& label) {
    const auto before = a04(replay_.plan(), database_);
    auto after_database = database_;
    const Row s_row{n(7), n(9)};
    auto& source = after_database.tables.at(1);
    const bool changed = operation == SetOperation::insert
        ? source.insert(s_row).second : source.erase(s_row) == 1;
    check(changed, label + ": S event did not cross source set membership");
    const auto expected = difference(before, a04(replay_.plan(), after_database));

    const auto sequence = ++sequence_;
    const PhysicalSetUpdate input{sequence, TableId{1}, operation, s_row};
    auto replay_epoch = replay_.apply(input);
    auto anchored_epoch = anchored_.apply(input);
    check(replay_epoch.sequence() == sequence &&
              anchored_epoch.sequence() == sequence,
          label + ": paired runtimes committed different sequence numbers");
    auto replay_result = collect(replay_, replay_epoch, expected,
                                 label + " ordered replay");
    auto anchored_result = collect(anchored_, anchored_epoch, expected,
                                   label + " anchored");
    check(std::set<SignedKey>(replay_result.raw.begin(), replay_result.raw.end()) ==
              std::set<SignedKey>(anchored_result.raw.begin(), anchored_result.raw.end()),
          label + ": completion strategies emitted different signed rows");
    database_ = std::move(after_database);
    check_current(replay_, label + " ordered replay after-state");
    check_current(anchored_, label + " anchored after-state");
    return {std::move(replay_result), std::move(anchored_result)};
  }

 private:
  void seed(Row row) {
    const PhysicalSetUpdate input{++sequence_, TableId{0}, SetOperation::insert,
                                 row};
    auto replay_epoch = replay_.apply(input);
    auto anchored_epoch = anchored_.apply(input);
    check(replay_epoch.remaining() == 0 && anchored_epoch.remaining() == 0,
          "maintenance seed unexpectedly prepared delta output");
    check(!replay_epoch.next() && !anchored_epoch.next(),
          "maintenance seed returned a signed record");
    check(database_.tables.at(0).insert(std::move(row)).second,
          "scale fixture seeded a duplicate root row");
    check_current(replay_, "ordered replay maintenance seed");
    check_current(anchored_, "anchored maintenance seed");
  }

  void check_current(const DeltaRuntime& runtime, const std::string& label) {
    const auto expected = a04(runtime.plan(), database_);
    check(runtime.has_answer() == !expected.empty(),
          label + ": answer truth differs from A04");
    check(drain_current(runtime.core_results(), runtime.result_layout(),
                        label + " core") == expected,
          label + ": current core results differ from A04");
    check(drain_current(runtime.results(), runtime.result_layout(),
                        label + " output") == expected,
          label + ": current output results differ from A04");
    if (runtime.mode() == DeltaMode::delta) {
      const auto live = runtime.live_snapshot();
      check(live.has_value() && live->sequence == runtime.sequence(),
            label + ": current L snapshot is missing or stale");
      check(live->factors == a04_live(runtime.plan(), expected),
            label + ": current L factors differ from independent A04 projections");
    } else {
      check(!runtime.live_snapshot(),
            label + ": maintenance mode retained a live image");
    }
    runtime.check_invariants();
  }

  DeltaRuntime replay_;
  DeltaRuntime anchored_;
  Database database_;
  std::uint64_t sequence_ = 0;
};

struct ScaleMetrics {
  DeltaMetrics insertion_replay;
  DeltaMetrics insertion_anchored;
  DeltaMetrics deletion_replay;
  DeltaMetrics deletion_anchored;
};

void check_insert_contract(const Event& replay, const Event& anchored,
                           std::size_t count, const std::string& label) {
  const auto& r = replay.metrics;
  const auto& a = anchored.metrics;
  check(r.changed_keys == count + 1 && r.candidates == count &&
            r.accepted == count && r.rejected == 0 && r.earlier_probes == 0,
        label + ": replay did not accept exactly one owner per answer");
  check(a.changed_keys == count + 1 && a.candidates == 2 * count &&
            a.accepted == count && a.rejected == count &&
            a.earlier_probes == count,
        label + ": anchored comparison did not expose the canonical duplicate tail");
  check(r.replay_queue_inserts == count && r.replay_queue_pops == count &&
            r.replay_queue_erases == 0 && r.replay_queue_peak == count,
        label + ": insertion queue did not filter the initially unsupported child");
  check(r.spool_rows == count && r.spool_capacity_rows == count,
        label + ": replay spool does not retain one owning node per output");
  check(replay.stages.front().changed_keys == count + 1 &&
            replay.stages.front().candidates == count &&
            replay.stages.front().accepted == count &&
            replay.stages.front().rejected == 0,
        label + ": insertion route-stage counters differ from the epoch");
}

void check_delete_contract(const Event& replay, const Event& anchored,
                           std::size_t count, const std::string& label) {
  const auto& r = replay.metrics;
  const auto& a = anchored.metrics;
  check(r.changed_keys == count + 1 && r.candidates == count &&
            r.accepted == count && r.rejected == 0 && r.earlier_probes == 0,
        label + ": replay deletion did not accept exactly one owner per answer");
  check(a.changed_keys == count + 1 && a.candidates == 2 * count &&
            a.accepted == count && a.rejected == count &&
            a.earlier_probes == count,
        label + ": anchored deletion did not expose the canonical duplicate tail");
  check(r.replay_queue_inserts == count + 1 &&
            r.replay_queue_pops == count && r.replay_queue_erases == 1 &&
            r.replay_queue_peak == count + 1,
        label + ": last-parent removal did not prune the queued child key");
  check(r.spool_rows == count && r.spool_capacity_rows == count,
        label + ": deletion spool does not retain one owning node per output");
  check(replay.stages.front().changed_keys == count + 1 &&
            replay.stages.front().candidates == count &&
            replay.stages.front().accepted == count &&
            replay.stages.front().rejected == 0,
        label + ": deletion route-stage counters differ from the epoch");
}

ScaleMetrics run_scale(std::size_t count) {
  ScaleRun run(chain_plan(), count);
  run.bootstrap(count);
  const auto inserted = run.update(SetOperation::insert,
                                   "scale child insertion N=" + std::to_string(count));
  check_insert_contract(inserted.first, inserted.second, count,
                        "scale insertion N=" + std::to_string(count));
  check(inserted.first.raw.size() == count &&
            inserted.second.raw.size() == count,
        "scale insertion raw output cardinality differs from N");

  const auto erased = run.update(SetOperation::erase,
                                 "scale child deletion N=" + std::to_string(count));
  check_delete_contract(erased.first, erased.second, count,
                        "scale deletion N=" + std::to_string(count));
  check(erased.first.raw.size() == count && erased.second.raw.size() == count,
        "scale deletion raw output cardinality differs from N");
  return {inserted.first.metrics, inserted.second.metrics,
          erased.first.metrics, erased.second.metrics};
}

using PhaseMaxima = std::tuple<std::uint64_t, std::uint64_t, std::uint64_t>;

PhaseMaxima phase_maxima(const DeltaMetrics& metrics) {
  return {metrics.replay_max_first_work, metrics.replay_max_next_work,
          metrics.replay_max_last_work};
}

void check_phase_metrics(const DeltaMetrics& metrics, const std::string& label) {
  check(metrics.replay_max_first_work != 0 &&
            metrics.replay_max_next_work != 0 &&
            metrics.replay_max_last_work != 0,
        label + ": first/next/last successful-transition phases were not charged");
}

void accepted_transition_work_does_not_grow_with_output_count() {
  constexpr std::size_t small_count = 2;
  constexpr std::size_t large_count = 64;
  const auto small = run_scale(small_count);
  const auto large = run_scale(large_count);

  check_phase_metrics(small.insertion_replay, "N=2 insertion");
  check_phase_metrics(large.insertion_replay, "N=64 insertion");
  check_phase_metrics(small.deletion_replay, "N=2 deletion");
  check_phase_metrics(large.deletion_replay, "N=64 deletion");

  check(phase_maxima(small.insertion_replay) ==
            phase_maxima(large.insertion_replay) &&
            phase_maxima(small.deletion_replay) ==
            phase_maxima(large.deletion_replay),
        "ordered replay first/next/last producer work grew from N=2 to N=64");
  check(large.insertion_replay.replay_preparation_work >
            small.insertion_replay.replay_preparation_work &&
            large.deletion_replay.replay_preparation_work >
            small.deletion_replay.replay_preparation_work,
        "replay preparation failed to expose its changed-key growth");
  check(large.insertion_replay.finalization_work >
            small.insertion_replay.finalization_work &&
            large.deletion_replay.finalization_work >
            small.deletion_replay.finalization_work,
        "explicit finalization work failed to expose its changed-key growth");

  const auto print = [](const char* label, const DeltaMetrics& metrics) {
    std::cout << label << " first/next/last="
              << metrics.replay_max_first_work << '/'
              << metrics.replay_max_next_work << '/'
              << metrics.replay_max_last_work << " preparation="
              << metrics.replay_preparation_work << " finalization="
              << metrics.finalization_work << '\n';
  };
  print("N=2 insert", small.insertion_replay);
  print("N=64 insert", large.insertion_replay);
  print("N=2 erase", small.deletion_replay);
  print("N=64 erase", large.deletion_replay);
}

}  // namespace

int main() {
  try {
    accepted_transition_work_does_not_grow_with_output_count();
    std::cout << "ordered replay accepted-transition scale checks passed\n";
  } catch (const std::exception& failure) {
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
