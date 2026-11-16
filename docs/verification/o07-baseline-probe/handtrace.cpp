#include "crown/planner/lower.hpp"
#include "crown/runtime/physical.hpp"
#include "crown/runtime/support.hpp"
#include "evaluator.hpp"

#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

namespace {
using namespace crown;
using namespace crown::runtime;

void check(bool condition, std::string_view message) {
  if (!condition) throw std::runtime_error(std::string(message));
}

Value integer(std::int64_t value) { return Value{value}; }
Row row(std::int64_t value) { return Row{integer(value)}; }
Row edge(std::int64_t x, std::int64_t y) { return Row{integer(x), integer(y)}; }

Relation drain(SupportRuntime::ResultCursor cursor) {
  Relation result;
  while (auto tuple = cursor.next()) {
    check(result.insert(tuple->values()).second, "result cursor emitted a duplicate set row");
  }
  return result;
}

std::string method_name(BuildMethod method) {
  return method == BuildMethod::direct ? "direct" : "insertion_replay";
}

PhysicalPlan q_plan(Catalog& catalog, Query& query) {
  catalog = Catalog{1, {
      {"R", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}},
      {"S", {{"y", ScalarType::int64}}},
  }};
  query = Query{
      {{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"R", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"S", TableId{1}, {VariableId{1}}}},
      {{VariableId{0}, "x"}},
      false,
  };
  const FreeConnexTree tree{
      NodeId{0},
      {{"R", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{1}}, 0, {}},
       {"S", NodeKind::native, {VariableId{1}}, {}, 1, {}}},
      {},
      {},
  };
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan unary_plan(Catalog& catalog, Query& query) {
  catalog = Catalog{1, {{"U", {{"x", ScalarType::int64}}}}};
  query = Query{
      {{"x", ScalarType::int64}},
      {{"U", TableId{0}, {VariableId{0}}}},
      {{VariableId{0}, "x"}},
      false,
  };
  const FreeConnexTree tree{
      NodeId{0},
      {{"U", NodeKind::native, {VariableId{0}}, {}, 0, {}}},
      {},
      {},
  };
  return planner::lower_tree(catalog, query, tree);
}

void check_no_generalized_nodes(const PhysicalPlan& plan) {
  for (const auto& node : plan.nodes())
    check(node.kind == NodeKind::native, "fixture unexpectedly contains a generalized node");
}

void check_q_metrics(const SupportMetrics& m, std::string_view label) {
  check(m.work == 40, std::string(label) + ": support work must be 40");
  check(m.copied_rows == 0 && m.copied_index_memberships == 0 &&
        m.copied_metadata_entries == 0 && m.copied_child_flags == 0,
        std::string(label) + ": historical whole-state copy counters must be zero");
  check(m.native_record_visits == 2, std::string(label) + ": native record visits must be 2");
  check(m.child_key_probes == 0 && m.child_key_events == 1,
        std::string(label) + ": child probes/events must be 0/1");
  check(m.survivor_transitions == 2 && m.parent_key_transitions == 2 &&
        m.visible_key_transitions == 1,
        std::string(label) + ": survivor/parent/visible transitions must be 2/2/1");
  check(m.candidates_created == 0 && m.candidates_reclaimed == 0,
        std::string(label) + ": generalized candidate counters must be zero");
  check(m.storage_changes == 6 && m.metadata_changes == 5 &&
        m.saved_child_flags == 1 && m.journal_records == 7,
        std::string(label) + ": storage/metadata/flag/journal counters must be 6/5/1/7");
  check(m.events_enqueued == 2 && m.events_applied == 2 && m.queue_peak == 1,
        std::string(label) + ": enqueue/apply/queue peak must be 2/2/1");
}

void check_q_physical_metrics(const PhysicalMetrics& m, std::string_view label) {
  check(m.work == 44, std::string(label) + ": physical work must include support and equal 44");
  check(m.source_changes == 1 && m.aliases_visited == 1 && m.aliases_filtered == 0 &&
        m.derivation_changes == 1 && m.native_crossings == 1,
        std::string(label) + ": source/alias/derivation/crossing increments differ");
  check(m.constraint_rows == 0 && m.constraint_validations == 0,
        std::string(label) + ": unconstrained fixture charged constraint work");
}

void check_unary_support_metrics(const SupportMetrics& m, std::string_view label) {
  check(m.work == 21, std::string(label) + ": unary support work must be 21");
  check(m.copied_rows == 0 && m.copied_index_memberships == 0 &&
        m.copied_metadata_entries == 0 && m.copied_child_flags == 0,
        std::string(label) + ": historical whole-state copy counters must be zero");
  check(m.native_record_visits == 1 && m.child_key_probes == 0 && m.child_key_events == 0,
        std::string(label) + ": unary visit/probe/event counts differ");
  check(m.survivor_transitions == 1 && m.parent_key_transitions == 1 &&
        m.visible_key_transitions == 1,
        std::string(label) + ": unary survivor/parent/visible transitions differ");
  check(m.candidates_created == 0 && m.candidates_reclaimed == 0,
        std::string(label) + ": unary fixture created a generalized candidate");
  check(m.storage_changes == 4 && m.metadata_changes == 3 &&
        m.saved_child_flags == 0 && m.journal_records == 4,
        std::string(label) + ": unary storage/metadata/flag/journal counts differ");
  check(m.events_enqueued == 1 && m.events_applied == 1 && m.queue_peak == 0,
        std::string(label) + ": unary enqueue/apply/queue peak differ");
}

void check_unary_physical_metrics(const PhysicalMetrics& m, std::string_view label) {
  check(m.work == 25, std::string(label) + ": unary physical work must include support and equal 25");
  check(m.source_changes == 1 && m.aliases_visited == 1 && m.aliases_filtered == 0 &&
        m.derivation_changes == 1 && m.native_crossings == 1,
        std::string(label) + ": unary source/alias/derivation/crossing increments differ");
  check(m.constraint_rows == 0 && m.constraint_validations == 0,
        std::string(label) + ": unary fixture charged constraint work");
}

void check_zero_support_metrics(const SupportMetrics& m, std::string_view label) {
  check(m.work == 0 && m.copied_rows == 0 && m.copied_index_memberships == 0 &&
        m.copied_metadata_entries == 0 && m.copied_child_flags == 0 &&
        m.native_record_visits == 0 && m.child_key_probes == 0 && m.child_key_events == 0 &&
        m.survivor_transitions == 0 && m.parent_key_transitions == 0 &&
        m.visible_key_transitions == 0 && m.candidates_created == 0 &&
        m.candidates_reclaimed == 0 && m.storage_changes == 0 && m.metadata_changes == 0 &&
        m.saved_child_flags == 0 && m.journal_records == 0 && m.events_enqueued == 0 &&
        m.events_applied == 0 && m.queue_peak == 0,
        std::string(label) + ": no-op logical epoch was charged");
}

void check_zero_physical_metrics(const PhysicalMetrics& m, std::string_view label) {
  check(m.work == 0 && m.source_changes == 0 && m.aliases_visited == 0 &&
        m.aliases_filtered == 0 && m.derivation_changes == 0 && m.native_crossings == 0 &&
        m.constraint_rows == 0 && m.constraint_validations == 0,
        std::string(label) + ": no-op physical epoch was charged");
}

void check_support_state(const SupportSnapshot& state, std::uint64_t expected_sequence,
                         std::string_view label) {
  check(state.sequence == expected_sequence && state.has_answer,
        std::string(label) + ": support epoch or Boolean result differs");
  check(state.nodes.size() == 2, std::string(label) + ": expected exactly two support nodes");

  const auto& root = state.nodes[0];
  check(root.node == NodeId{0} && root.kind == NodeKind::native,
        std::string(label) + ": root descriptor differs");
  check(root.records.size() == 1 && root.records[0].tuple.values() == edge(7, 9) &&
        root.records[0].satisfied.value == 1 &&
        root.records[0].child_present == std::vector<bool>{true} && root.records[0].survives,
        std::string(label) + ": R(7,9) record state differs");
  check(root.survivors.size() == 1 && root.survivors[0].values() == edge(7, 9),
        std::string(label) + ": R survivor differs");
  check(root.parent_keys.size() == 1 && root.parent_keys[0].key.values().empty() &&
        root.parent_keys[0].support.value == 1,
        std::string(label) + ": root empty parent key differs");
  check(root.visible_keys.has_value() && root.visible_keys->size() == 1 &&
        root.visible_keys->front().key.values() == row(7) &&
        root.visible_keys->front().support.value == 1,
        std::string(label) + ": root visible key E(7) differs");

  const auto& child = state.nodes[1];
  check(child.node == NodeId{1} && child.kind == NodeKind::native,
        std::string(label) + ": child descriptor differs");
  check(child.records.size() == 1 && child.records[0].tuple.values() == row(9) &&
        child.records[0].satisfied.value == 0 && child.records[0].child_present.empty() &&
        child.records[0].survives,
        std::string(label) + ": S(9) record state differs");
  check(child.survivors.size() == 1 && child.survivors[0].values() == row(9),
        std::string(label) + ": S survivor differs");
  check(child.parent_keys.size() == 1 && child.parent_keys[0].key.values() == row(9) &&
        child.parent_keys[0].support.value == 1,
        std::string(label) + ": child separator support P(9) differs");
  check(!child.visible_keys.has_value(), std::string(label) + ": S unexpectedly owns a visible relation");
}

void check_q_trace(const SupportEpoch& epoch, std::string_view label) {
  check(epoch.journal != nullptr, std::string(label) + ": changed epoch omitted its support journal");
  const auto& journal = *epoch.journal;
  check(journal.sequence == epoch.sequence && journal.records.size() == 7 && journal.events.size() == 2,
        std::string(label) + ": journal record/event totals differ");
  const auto event0 = journal.events[0];
  check(event0.id == 1 && event0.cause == 0 && event0.applied_ordinal == 1 &&
        event0.kind == SupportEventKind::native_update && event0.target == NodeId{1} &&
        event0.operation == SetOperation::insert && event0.before == false && event0.after == true &&
        event0.key.values() == row(9),
        std::string(label) + ": native S event differs from the hand trace");
  const auto event1 = journal.events[1];
  check(event1.id == 2 && event1.cause == 1 && event1.applied_ordinal == 2 &&
        event1.kind == SupportEventKind::child_key && event1.target == NodeId{0} &&
        event1.child_slot == std::optional<std::size_t>{0} &&
        event1.operation == SetOperation::insert && event1.before == false && event1.after == true &&
        event1.key.values() == row(9),
        std::string(label) + ": propagated P(9) event differs from the hand trace");

  const auto has_record = [&](NodeId node, SupportRole role, const Row& key, std::uint64_t cause) {
    for (const auto& record : journal.records) {
      if (record.handle.node == node && record.handle.role == role &&
          record.tuple().values() == key && record.cause == cause &&
          !record.before.member && record.after.member)
        return true;
    }
    return false;
  };
  check(has_record(NodeId{1}, SupportRole::records, row(9), 1) &&
        has_record(NodeId{1}, SupportRole::survivors, row(9), 1) &&
        has_record(NodeId{1}, SupportRole::parent_support, row(9), 1),
        std::string(label) + ": child journal changes do not all have cause 1");
  check(has_record(NodeId{0}, SupportRole::survivors, edge(7, 9), 2) &&
        has_record(NodeId{0}, SupportRole::parent_support, Row{}, 2) &&
        has_record(NodeId{0}, SupportRole::visible, row(7), 2),
        std::string(label) + ": root output journal changes do not all have cause 2");
  bool root_record_update = false;
  for (const auto& record : journal.records) {
    if (record.handle.node == NodeId{0} && record.handle.role == SupportRole::records &&
        record.tuple().values() == edge(7, 9)) {
      root_record_update = record.cause == 2 && record.before.member && record.after.member &&
          record.before.satisfied == SatisfiedChildCount{0} &&
          record.after.satisfied == SatisfiedChildCount{1} &&
          record.before.child_present == std::vector<bool>{false} &&
          record.after.child_present == std::vector<bool>{true};
    }
  }
  check(root_record_update, std::string(label) + ": R child flag journal did not change false to true under cause 2");
}

void run_q_physical(BuildMethod method) {
  Catalog catalog;
  Query query;
  auto plan = q_plan(catalog, query);
  check_no_generalized_nodes(plan);
  check(plan.enumeration().steps.size() == 1 && plan.nodes()[0].visible_relation.has_value() &&
        !plan.nodes()[1].visible_relation.has_value(), "Q(x) fixture did not retain only R in C*");

  Database database;
  database.tables.resize(2);
  database.tables[0].insert(edge(7, 9));
  const auto initial_expected = reference::evaluate(catalog, query, database);
  check(initial_expected.empty(), "independent evaluator found an initial Q answer");
  PhysicalRuntimeOptions options;
  options.support.capture_transitions = true;
  const BuildOptions build{method, std::nullopt};
  auto runtime = PhysicalRuntime::initialize(plan, database, options, build);
  check(runtime.initialization_metrics().native_keys > 0,
        "physical initializer did not load the initial R row");
  check(runtime.snapshot().physical.tables == database.tables,
        "physical initializer changed the independent source database");
  check(drain(runtime.results()) == initial_expected,
        "pre-update physical current-result cursor differs from independent evaluation");

  const PhysicalSetUpdate update{1, TableId{1}, SetOperation::insert, row(9)};
  reference::Session reference(catalog, query, database);
  const auto reference_epoch = reference.apply(update);
  check(reference_epoch.input_changed && reference_epoch.delta.added == Relation{row(7)} &&
        reference_epoch.delta.removed.empty() && reference_epoch.current == Relation{row(7)},
        "independent reference evaluator did not derive the literal +7 delta");
  auto pending = runtime.prepare(update);
  auto before_view = pending.view(SnapshotSide::before);
  check(drain(before_view.results()) == initial_expected,
        "physical before-publication cursor exposed the pending answer");
  before_view.close();
  auto after_view = pending.view(SnapshotSide::after);
  check(drain(after_view.results()) == reference_epoch.current,
        "physical tentative after-view differs from the independent answer");
  after_view.close();
  const auto epoch = pending.commit();
  check_q_physical_metrics(epoch.input.metrics, method_name(method));
  check_q_metrics(epoch.support.metrics, method_name(method));
  check(epoch.support.native_changed && epoch.support.sequence == 1 && epoch.input.sequence == 1,
        "physical Q update did not publish one changed sequence");
  check_q_trace(epoch.support, method_name(method));
  check_support_state(runtime.snapshot().support, 1, method_name(method));
  check(runtime.derivation_count(OccurrenceId{0}, edge(7, 9)) == 1 &&
        runtime.derivation_count(OccurrenceId{1}, row(9)) == 1,
        "physical source routing did not retain the two expected native derivations");
  check(runtime.snapshot().physical.tables == reference.database().tables,
        "physical source after-state differs from the independent source update");
  check(drain(runtime.results()) == reference_epoch.current,
        "post-commit physical current-result cursor differs from independent evaluation");
  runtime.check_invariants();

  std::cout << "Q physical init=" << method_name(method)
            << " physical_work=" << epoch.input.metrics.work
            << " support_work=" << epoch.support.metrics.work
            << " events=" << epoch.support.metrics.events_enqueued << "/"
            << epoch.support.metrics.events_applied
            << " native_visits=" << epoch.support.metrics.native_record_visits
            << " reverse_index_records_visited=unavailable_public_metric"
            << " result_rows=" << reference_epoch.current.size() << '\n';
}

void run_q_direct_support() {
  Catalog catalog;
  Query query;
  auto plan = q_plan(catalog, query);
  check_no_generalized_nodes(plan);
  SupportOptions options;
  options.capture_transitions = true;
  SupportRuntime support(plan, options);

  // SupportRuntime has no public bulk initializer. This first native epoch
  // establishes the before-state and is intentionally outside the measured S epoch.
  const auto seed = support.apply({1, NodeId{0}, SetOperation::insert, edge(7, 9)});
  check(seed.native_changed && !seed.has_answer && seed.sequence == 1,
        "direct support setup did not establish only the unsatisfied R record");
  const auto measured = support.apply({2, NodeId{1}, SetOperation::insert, row(9)});
  check_q_metrics(measured.metrics, "direct_support");
  check(measured.native_changed && measured.has_answer && measured.sequence == 2,
        "direct support S insertion did not commit the expected answer");
  check_q_trace(measured, "direct_support");
  check_support_state(support.snapshot(), 2, "direct_support");

  Database database;
  database.tables.resize(2);
  database.tables[0].insert(edge(7, 9));
  database.tables[1].insert(row(9));
  const auto expected = reference::evaluate(catalog, query, database);
  check(expected == Relation{row(7)} && drain(support.results()) == expected,
        "direct support current-result cursor differs from independent evaluation");
  support.check_invariants();
  std::cout << "Q direct_support measured_sequence=" << measured.sequence
            << " support_work=" << measured.metrics.work
            << " events=" << measured.metrics.events_enqueued << "/"
            << measured.metrics.events_applied
            << " native_visits=" << measured.metrics.native_record_visits
            << " reverse_index_records_visited=unavailable_public_metric"
            << " result_rows=" << expected.size() << '\n';
}

void run_unary_physical() {
  Catalog catalog;
  Query query;
  auto plan = unary_plan(catalog, query);
  check_no_generalized_nodes(plan);
  PhysicalRuntimeOptions options;
  options.support.capture_transitions = true;
  auto runtime = PhysicalRuntime::initialize(plan, Database{std::vector<Relation>(1)}, options);
  Database reference_database{std::vector<Relation>(1)};
  reference::Session reference(catalog, query, reference_database);

  const PhysicalSetUpdate insert{1, TableId{0}, SetOperation::insert, row(7)};
  const auto expected_insert = reference.apply(insert);
  const auto inserted = runtime.apply(insert);
  check_unary_physical_metrics(inserted.input.metrics, "unary_physical_insert");
  check_unary_support_metrics(inserted.support.metrics, "unary_physical_insert");
  check(expected_insert.delta.added == Relation{row(7)} && expected_insert.delta.removed.empty() &&
        drain(runtime.results()) == expected_insert.current,
        "unary physical insertion result differs from the independent evaluator");

  const PhysicalSetUpdate duplicate{2, TableId{0}, SetOperation::insert, row(7)};
  const auto expected_duplicate = reference.apply(duplicate);
  const auto repeated = runtime.apply(duplicate);
  check(!expected_duplicate.input_changed && expected_duplicate.delta.added.empty() &&
        expected_duplicate.delta.removed.empty(), "reference duplicate insert changed the result set");
  check(!repeated.input.physical_changed && !repeated.support.native_changed &&
        repeated.support.journal == nullptr && repeated.support.transitions.empty(),
        "physical duplicate insert changed support state or emitted a logical delta journal");
  check_zero_physical_metrics(repeated.input.metrics, "unary_physical_duplicate");
  check_zero_support_metrics(repeated.support.metrics, "unary_physical_duplicate");
  check(repeated.input.sequence == 2 && repeated.support.sequence == 2 &&
        drain(runtime.results()) == expected_duplicate.current,
        "physical duplicate did not commit the next sequence with unchanged current results");

  const PhysicalSetUpdate erase{3, TableId{0}, SetOperation::erase, row(7)};
  const auto expected_erase = reference.apply(erase);
  const auto erased = runtime.apply(erase);
  check(erased.input.physical_changed && erased.support.native_changed &&
        expected_erase.delta.removed == Relation{row(7)} && expected_erase.delta.added.empty() &&
        drain(runtime.results()).empty() && drain(runtime.results()) == expected_erase.current,
        "unary erase did not restore empty result membership");
  runtime.check_invariants();
  std::cout << "U physical insert_work=" << inserted.input.metrics.work
            << " insert_support_work=" << inserted.support.metrics.work
            << " duplicate_work=" << repeated.input.metrics.work << "/"
            << repeated.support.metrics.work
            << " erase_result_rows=" << expected_erase.current.size() << '\n';
}

void run_unary_direct_support() {
  Catalog catalog;
  Query query;
  auto plan = unary_plan(catalog, query);
  check_no_generalized_nodes(plan);
  SupportOptions options;
  options.capture_transitions = true;
  SupportRuntime support(plan, options);

  const auto inserted = support.apply({1, NodeId{0}, SetOperation::insert, row(7)});
  check_unary_support_metrics(inserted.metrics, "unary_direct_insert");
  check(inserted.native_changed && inserted.has_answer &&
        drain(support.results()) == Relation{row(7)},
        "unary direct support insertion did not return exactly U(7)");

  const auto duplicate = support.apply({2, NodeId{0}, SetOperation::insert, row(7)});
  check(!duplicate.native_changed && duplicate.has_answer && duplicate.journal == nullptr &&
        duplicate.transitions.empty(), "direct support duplicate changed membership or emitted a delta");
  check_zero_support_metrics(duplicate.metrics, "unary_direct_duplicate");
  check(drain(support.results()) == Relation{row(7)},
        "direct support duplicate changed current-result membership");

  const auto erased = support.apply({3, NodeId{0}, SetOperation::erase, row(7)});
  check(erased.native_changed && !erased.has_answer && drain(support.results()).empty(),
        "direct support erase did not restore the empty result set");
  support.check_invariants();
  std::cout << "U direct_support insert_work=" << inserted.metrics.work
            << " duplicate_work=" << duplicate.metrics.work
            << " erase_result_rows=0\n";
}

}  // namespace

int main() {
  run_q_physical(BuildMethod::direct);
  run_q_physical(BuildMethod::insertion_replay);
  run_q_direct_support();
  run_unary_physical();
  run_unary_direct_support();
  std::cout << "O07 excluded baseline hand-trace probe passed\n";
}
