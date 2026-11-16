#include "crown/api/error.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/support.hpp"

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace {
template<class Layout> auto readable(const Layout& layout){
  if constexpr(requires{layout.descriptor();})return layout.descriptor();
  else return layout;
}

using namespace crown;
using namespace crown::runtime;
static_assert(std::is_nothrow_move_constructible_v<SupportEpoch>);
static_assert(!std::is_copy_constructible_v<SupportJournal>);

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
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

PhysicalPlan generalized_three_plan() {
  const Catalog catalog{3, {
      {"a", {{"x", ScalarType::int64}}},
      {"b", {{"x", ScalarType::int64}}},
      {"c", {{"x", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}},
      {{"a", TableId{0}, {VariableId{0}}},
       {"b", TableId{1}, {VariableId{0}}},
       {"c", TableId{2}, {VariableId{0}}}},
      {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0}, {
      {"intersection", NodeKind::generalized, {VariableId{0}},
       {NodeId{1}, NodeId{2}, NodeId{3}}, {}, {}},
      {"a", NodeKind::native, {VariableId{0}}, {}, 0, {}},
      {"b", NodeKind::native, {VariableId{0}}, {}, 1, {}},
      {"c", NodeKind::native, {VariableId{0}}, {}, 2, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan nested_plan() {
  const Catalog catalog{6, {
      {"b", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}},
      {"c", {{"y", ScalarType::int64}}},
      {"g", {{"x", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"b", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"c", TableId{1}, {VariableId{1}}},
       {"g", TableId{2}, {VariableId{0}}}},
      {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0}, {
      {"root", NodeKind::generalized, {VariableId{0}}, {NodeId{1}, NodeId{3}}, {}, {}},
      {"b", NodeKind::native, {VariableId{0}, VariableId{1}}, {NodeId{2}}, 0, {}},
      {"c", NodeKind::native, {VariableId{1}}, {}, 1, {}},
      {"g", NodeKind::native, {VariableId{0}}, {}, 2, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan boolean_root_plan() {
  const Catalog catalog{1, {{"bool_source", {{"hidden", ScalarType::int64}}}}};
  const Query query{{{"hidden", ScalarType::int64}},
                    {{"bool_source", TableId{0}, {VariableId{0}}}}, {}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"bool_source", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan nullary_plan() {
  const Catalog catalog{1, {{"unit_source", {}}}};
  const Query query{{}, {{"unit_source", TableId{0}, {}}}, {}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"unit_source", NodeKind::native, {}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan projected_count_plan() {
  const Catalog catalog{1, {{"pair", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
                    {{"pair", TableId{0}, {VariableId{0}, VariableId{1}}}},
                    {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"pair", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan deep_chain_plan(std::size_t length) {
  Catalog catalog;
  Query query;
  query.variables = {{"x", ScalarType::int64}};
  query.head = {{VariableId{0}, "x"}};
  FreeConnexTree tree;
  tree.root = NodeId{0};
  for (std::size_t i = 0; i < length; ++i) {
    const auto name = "chain_" + std::to_string(i);
    catalog.tables.push_back({name, {{"x", ScalarType::int64}}});
    query.atoms.push_back({name, TableId{i}, {VariableId{0}}});
    tree.nodes.push_back({name, NodeKind::native, {VariableId{0}}, {}, i, {}});
    if (i > 0) tree.nodes[i - 1].children.push_back(NodeId{i});
  }
  return planner::lower_tree(catalog, query, tree);
}

struct ReferenceValueState {
  bool member=false;
  std::optional<SatisfiedChildCount> satisfied;
  std::vector<bool> child_present;
  std::optional<ProjectionSupportCount> support;
};
ReferenceValueState export_state(const SupportValueState& value) {
  return {value.member,value.satisfied,{value.child_present.begin(),value.child_present.end()},value.support};
}
template<class Left,class Right>bool same_value_state(const Left& left, const Right& right) {
  return left.member == right.member && left.satisfied == right.satisfied &&
      std::ranges::equal(left.child_present, right.child_present) && left.support == right.support;
}

struct RoleValue {
  storage::Tuple tuple;
  ReferenceValueState state;
};
using StateMap = std::map<SupportHandle, RoleValue>;

RelationId role_relation(const auto& node, SupportRole role) {
  switch (role) {
    case SupportRole::records: return node.records;
    case SupportRole::survivors: return node.survivors;
    case SupportRole::parent_support: return node.parent_support;
    case SupportRole::visible:
      check(node.visible_relation.has_value(), "visible journal record has no visible relation");
      return *node.visible_relation;
  }
  throw std::runtime_error("unknown support role");
}

void check_role_state_shape(const auto& plan, const SupportHandle& handle,
                            const auto& state) {
  check(handle.node.value < plan.nodes().size(), "journal handle refers to an unknown node");
  const auto& node = plan.nodes()[handle.node.value];
  if (!state.member) return;
  switch (handle.role) {
    case SupportRole::records:
      check(state.satisfied.has_value() && state.child_present.size() == node.children.size() && !state.support,
            "record state has the wrong child-count shape");
      check(state.satisfied->value == static_cast<std::size_t>(
                std::count(state.child_present.begin(), state.child_present.end(), true)),
            "record state child count disagrees with its flags");
      break;
    case SupportRole::survivors:
      check(!state.satisfied && state.child_present.empty() && !state.support,
            "survivor state contains unrelated metadata");
      break;
    case SupportRole::parent_support:
    case SupportRole::visible:
      check(!state.satisfied && state.child_present.empty() && state.support && state.support->value > 0,
            "projection state has the wrong support-count shape");
      break;
  }
}

void add_role_value(StateMap& result, const SupportRuntime& runtime, SupportHandle handle,
                    const storage::Tuple& tuple, ReferenceValueState state) {
  check(handle.owner == runtime.owner(), "snapshot exposes a foreign support handle");
  const auto owned = runtime.get(handle);
  check(owned && owned->layout().same_token(tuple.layout()) && owned->values() == tuple.values(),
        "committed public handle does not resolve to the snapshot tuple");
  check_role_state_shape(runtime.plan(), handle, state);
  check(result.emplace(handle, RoleValue{tuple, std::move(state)}).second,
        "snapshot contains duplicate handles");
}

StateMap snapshot_state(const SupportRuntime& runtime, const SupportSnapshot& snapshot) {
  StateMap result;
  for (const auto& node : snapshot.nodes) {
    for (const auto& record : node.records) {
      ReferenceValueState state;
      state.member = true;
      state.satisfied = record.satisfied;
      state.child_present = record.child_present;
      add_role_value(result, runtime, record.handle, record.tuple, std::move(state));
    }
    for (const auto& tuple : node.survivors) {
      const auto handle = runtime.find(node.node, SupportRole::survivors, crown::storage::export_row(tuple.values()));
      check(handle.has_value(), "snapshot survivor is absent from the committed membership table");
      ReferenceValueState state;
      state.member = true;
      add_role_value(result, runtime, *handle, tuple, std::move(state));
    }
    for (const auto& key : node.parent_keys) {
      ReferenceValueState state;
      state.member = true;
      state.support = key.support;
      add_role_value(result, runtime, key.handle, key.key, std::move(state));
    }
    if (node.visible_keys) {
      for (const auto& key : *node.visible_keys) {
        ReferenceValueState state;
        state.member = true;
        state.support = key.support;
        add_role_value(result, runtime, key.handle, key.key, std::move(state));
      }
    }
  }
  return result;
}

bool same_tuple(const storage::Tuple& left, const storage::Tuple& right) {
  return left.layout().same_token(right.layout()) && left.values() == right.values();
}

bool same_tuple(const storage::AccountedTuple& left, const storage::AccountedTuple& right) {
  return left.layout().same_token(right.layout()) && left.values() == right.values();
}

storage::Tuple exported_tuple(const auto& plan, const storage::AccountedTuple& tuple) {
  const auto layout=tuple.layout().descriptor();
  check(layout.same_descriptor(readable(plan.layouts().at(tuple.layout().id().value))),
        "native journal layout differs from the compiled definition");
  return layout.tuple(storage::export_row(tuple.values()));
}

void compare_state_maps(const StateMap& left, const StateMap& right, const std::string& message) {
  check(left.size() == right.size(), message + ": membership cardinality differs");
  auto a = left.begin();
  auto b = right.begin();
  for (; a != left.end(); ++a, ++b) {
    check(a->first == b->first && same_tuple(a->second.tuple, b->second.tuple) &&
          same_value_state(a->second.state, b->second.state), message + ": role state differs");
  }
}

using SemanticKey = std::tuple<NodeId, SupportRole, Row>;
using SemanticStateMap = std::map<SemanticKey, ReferenceValueState>;

SemanticStateMap semantic_state_map(const StateMap& state) {
  SemanticStateMap result;
  for (const auto& [handle, value] : state)
    check(result.emplace(SemanticKey{handle.node, handle.role, crown::storage::export_row(value.tuple.values())}, value.state).second,
          "runtime state contains duplicate logical role values");
  return result;
}

void compare_semantic_state_maps(const StateMap& left, const StateMap& right, const std::string& message) {
  const auto a = semantic_state_map(left);
  const auto b = semantic_state_map(right);
  check(a.size() == b.size(), message + ": membership cardinality differs");
  auto i = a.begin();
  auto j = b.begin();
  for (; i != a.end(); ++i, ++j)
    check(i->first == j->first && same_value_state(i->second, j->second),
          message + ": logical role state differs");
}

void replay_journal(const SupportRuntime& runtime, const SupportEpoch& epoch,
                    const StateMap& before, const StateMap& after) {
  check(epoch.journal != nullptr, "a real update omitted its journal");
  const auto& journal = *epoch.journal;
  check(journal.sequence == epoch.sequence, "journal sequence differs from its epoch");
  check(epoch.metrics.copied_rows == 0 && epoch.metrics.copied_index_memberships == 0 &&
        epoch.metrics.copied_metadata_entries == 0 && epoch.metrics.copied_child_flags == 0,
        "affected-record update reports copied state");
  check(epoch.metrics.journal_records == journal.records.size() && !journal.records.empty(),
        "journal record accounting is inaccurate");
  check(epoch.metrics.storage_changes > 0 && epoch.metrics.metadata_changes > 0,
        "real update omitted storage or metadata accounting");
  check(epoch.metrics.events_enqueued == 1 + epoch.metrics.child_key_events &&
        epoch.metrics.events_applied == epoch.metrics.events_enqueued,
        "real update did not enqueue and apply each native/child event exactly once");

  StateMap replayed = before;
  for (std::size_t i = 0; i < journal.records.size(); ++i) {
    const auto& record = journal.records[i];
    check(record.ordinal == i + 1, "journal ordinals are not contiguous and one-based");
    check(record.handle.owner == runtime.owner(), "journal record has a foreign support owner");
    check(record.handle.node.value < runtime.plan().nodes().size(), "journal record has an invalid node");
    const auto relation = role_relation(runtime.plan().nodes()[record.handle.node.value], record.handle.role);
    const auto& expected_layout = runtime.plan().relations()[relation.value].layout;
    check(record.tuple().layout().same_token(runtime.relation_layout(record.handle.node,record.handle.role)) &&
          record.tuple().layout().descriptor().same_descriptor(readable(expected_layout)) &&
          same_tuple(record.tuple(), record.retained.get()),
          "journal pin does not retain the role's exact tuple value");
    check_role_state_shape(runtime.plan(), record.handle, record.before);
    check_role_state_shape(runtime.plan(), record.handle, record.after);

    const auto current = replayed.find(record.handle);
    check(record.before.member == (current != replayed.end()),
          "journal before-membership does not match the reconstructed state");
    if (current != replayed.end()) {
      check(same_tuple(current->second.tuple, exported_tuple(runtime.plan(),record.tuple())) &&
            same_value_state(current->second.state, record.before),
            "journal before-value does not match the reconstructed state");
    }
    if (record.after.member) {
      check_role_state_shape(runtime.plan(), record.handle, record.after);
      replayed.insert_or_assign(record.handle, RoleValue{exported_tuple(runtime.plan(),record.tuple()), export_state(record.after)});
    } else if (current != replayed.end()) {
      replayed.erase(current);
    }
  }
  compare_state_maps(replayed, after, "applying the journal in ordinal order");

  for (const auto& record : journal.records) {
    check(record.cause > 0 && record.cause <= epoch.metrics.events_applied,
          "journal record cause is not an applied event ID");
  }
  for (const auto& transition : epoch.transitions) {
    check(transition.cause > 0 && transition.cause <= epoch.metrics.events_applied,
          "membership transition cause is not an applied event ID");
    check(transition.handle.owner == runtime.owner() &&
          transition.handle.node.value < runtime.plan().nodes().size(),
          "membership transition has an invalid handle");
    const auto relation = role_relation(runtime.plan().nodes()[transition.handle.node.value],
                                        transition.handle.role);
    check(transition.tuple.layout().same_token(runtime.relation_layout(transition.handle.node,transition.handle.role)) &&
          transition.tuple.layout().same_descriptor(readable(runtime.plan().relations()[relation.value].layout)),
          "membership transition tuple has the wrong role layout");
    const auto cause_record = std::find_if(journal.records.begin(), journal.records.end(), [&](const auto& record) {
      return record.handle == transition.handle && record.cause == transition.cause &&
          same_tuple(exported_tuple(runtime.plan(),record.tuple()), transition.tuple) &&
          (transition.operation == SetOperation::insert
              ? (!record.before.member && record.after.member)
              : (record.before.member && !record.after.member));
    });
    check(cause_record != journal.records.end(),
          "membership transition cause has no matching journal membership crossing");
  }
}

auto metrics_view(const SupportMetrics& m) {
  return std::tuple{m.work, m.copied_rows, m.copied_index_memberships,
      m.copied_metadata_entries, m.copied_child_flags, m.native_record_visits,
      m.child_key_probes, m.child_key_events, m.survivor_transitions,
      m.parent_key_transitions, m.visible_key_transitions, m.candidates_created,
      m.candidates_reclaimed, m.storage_changes, m.metadata_changes, m.saved_child_flags,
      m.journal_records, m.events_enqueued, m.events_applied, m.queue_peak};
}

auto state_view(const auto& state) {
  return std::tuple{state.member,
      state.satisfied ? std::optional<std::size_t>{state.satisfied->value} : std::optional<std::size_t>{},
      std::vector<bool>(state.child_present.begin(),state.child_present.end()),
      state.support ? std::optional<std::uint64_t>{state.support->value} : std::optional<std::uint64_t>{}};
}

void check_event_trace(const SupportRuntime& runtime, const NativeSetUpdate& update,
                       const SupportEpoch& epoch, const StateMap& before,
                       const StateMap& after, bool trace_enabled) {
  check(epoch.journal != nullptr, "event validation requires the real-update journal");
  const auto& events = epoch.journal->events;
  if (!trace_enabled) {
    check(events.empty(), "disabled event capture still returned propagation events");
    return;
  }
  check(events.size() == epoch.metrics.events_applied,
        "captured event count differs from the number of applied events");
  check(!events.empty(), "real update did not capture its native event");

  std::map<std::uint64_t, const PropagationEvent*> by_id;
  std::set<std::uint64_t> ordinals;
  for (const auto& event : events) {
    check(event.id > 0 && by_id.emplace(event.id, &event).second,
          "event IDs are not unique and positive");
    check(event.sequence == update.sequence && event.applied_ordinal > 0 &&
          ordinals.insert(event.applied_ordinal).second,
          "events do not identify the current epoch and a unique applied ordinal");
    check(event.source.owner == runtime.owner(), "event source has a foreign support owner");
    check(event.before != event.after &&
          event.operation == (event.after ? SetOperation::insert : SetOperation::erase),
          "event operation disagrees with its membership crossing");
  }
  for (std::uint64_t id = 1; id <= events.size(); ++id)
    check(by_id.contains(id), "event IDs are not contiguous in enqueue order");
  for (std::uint64_t ordinal = 1; ordinal <= events.size(); ++ordinal)
    check(ordinals.contains(ordinal), "event applied ordinals are not contiguous");

  const auto* native = by_id.at(1);
  check(native->cause == 0 && native->applied_ordinal == 1 &&
        native->kind == SupportEventKind::native_update && native->target == update.node &&
        !native->child_slot && native->key.values() == update.values,
        "native update is not event 1 with cause 0 and applied ordinal 1");
  check(native->source.node == update.node && native->source.role == SupportRole::records,
        "native event source is not its native record");
  const auto& source_map = update.operation == SetOperation::insert ? after : before;
  const auto source = source_map.find(native->source);
  check(source != source_map.end() && source->second.tuple.values() == update.values,
        "native event source handle does not identify the updated tuple");
  check(native->before == (update.operation == SetOperation::erase) &&
        native->after == (update.operation == SetOperation::insert),
        "native event has incorrect before/after membership");

  for (const auto& event : events) {
    if (event.id == 1) continue;
    check(event.kind == SupportEventKind::child_key && event.cause > 0 && event.cause < event.id,
          "propagated event does not name an earlier enqueueing event");
    const auto* parent = by_id.at(event.cause);
    check(parent->applied_ordinal < event.applied_ordinal,
          "propagated event was applied before its cause");
    check(event.child_slot.has_value() && event.target.value < runtime.plan().nodes().size(),
          "child event omits its target slot");
    const auto& target = runtime.plan().nodes()[event.target.value];
    check(*event.child_slot < target.children.size() &&
          target.children[*event.child_slot] == event.source.node &&
          event.source.role == SupportRole::parent_support,
          "child event source and target slot do not identify a physical edge");
    const auto& source_for_child = event.after ? after : before;
    const auto child_source = source_for_child.find(event.source);
    check(child_source != source_for_child.end() &&
          same_tuple(child_source->second.tuple, event.key),
          "child event key differs from its retained child support tuple");
    const auto causing_record = std::find_if(epoch.journal->records.begin(), epoch.journal->records.end(),
        [&](const auto& record) {
          return record.handle == event.source && record.cause == event.cause &&
              record.before.member == event.before && record.after.member == event.after;
        });
    check(causing_record != epoch.journal->records.end(),
          "child event cause has no matching child-support journal crossing");
  }
  for (const auto& record : epoch.journal->records)
    check(by_id.contains(record.cause), "journal record refers to an uncaptured event ID");
  for (const auto& transition : epoch.transitions)
    check(by_id.contains(transition.cause), "membership transition refers to an uncaptured event ID");
}

SupportEpoch apply_checked(SupportRuntime& runtime, const NativeSetUpdate& update) {
  const auto before_snapshot = runtime.snapshot();
  const auto before = snapshot_state(runtime, before_snapshot);
  const auto epoch = runtime.apply(update);
  check(epoch.native_changed && epoch.sequence == update.sequence,
        "test update was expected to change the native set");
  const auto after_snapshot = runtime.snapshot();
  const auto after = snapshot_state(runtime, after_snapshot);
  check(after_snapshot.sequence == update.sequence && epoch.has_answer == after_snapshot.has_answer,
        "committed snapshot does not match its epoch");

  // Every membership that survives this update must retain its public identity.
  for (const auto& [handle, value] : before) {
    const auto now = std::find_if(after.begin(), after.end(), [&](const auto& entry) {
      return entry.first.node == handle.node && entry.first.role == handle.role &&
          entry.second.tuple.values() == value.tuple.values();
    });
    if (now != after.end())
      check(now->first == handle, "an unchanged committed membership lost its stable handle");
  }
  replay_journal(runtime, epoch, before, after);
  check_event_trace(runtime, update, epoch, before, after, runtime.options().capture_transitions);
  return epoch;
}

void trace_on_and_off_have_identical_accounting() {
  const auto plan = nested_plan();
  SupportOptions traced_options;
  traced_options.capture_transitions = true;
  SupportOptions quiet_options;
  quiet_options.capture_transitions = false;
  SupportRuntime traced(plan, traced_options);
  SupportRuntime quiet(plan, quiet_options);
  const std::vector<NativeSetUpdate> updates{
      {1, NodeId{1}, SetOperation::insert, {n(1), n(10)}},
      {2, NodeId{3}, SetOperation::insert, {n(1)}},
      {3, NodeId{2}, SetOperation::insert, {n(10)}},
      {4, NodeId{2}, SetOperation::erase, {n(10)}}};
  for (const auto& update : updates) {
    const auto a = apply_checked(traced, update);
    const auto b = apply_checked(quiet, update);
    check(a.has_answer == b.has_answer && a.native_changed == b.native_changed &&
          metrics_view(a.metrics) == metrics_view(b.metrics),
          "event trace capture changed answers or support work/accounting metrics");
    check(a.journal->records.size() == b.journal->records.size(),
          "trace capture changed the number of retained journal records");
    for (std::size_t i = 0; i < a.journal->records.size(); ++i) {
      const auto& ar = a.journal->records[i];
      const auto& br = b.journal->records[i];
      check(ar.ordinal == br.ordinal && ar.cause == br.cause && ar.handle.node == br.handle.node &&
          ar.handle.role == br.handle.role && ar.tuple().layout().same_descriptor(br.tuple().layout()) &&
            ar.tuple().values() == br.tuple().values() &&
            state_view(ar.before) == state_view(br.before) &&
            state_view(ar.after) == state_view(br.after),
            "trace capture changed journal state or record identity");
    }
    check(a.journal->events.size() == a.metrics.events_applied && b.journal->events.empty(),
          "trace-on/off event retention does not follow the option");
    check(a.transitions.size() > 0 && b.transitions.empty(),
          "membership transition capture does not follow its option");
    compare_semantic_state_maps(snapshot_state(traced, traced.snapshot()),
                                snapshot_state(quiet, quiet.snapshot()),
                                "trace-on/off committed state");
  }

  const auto traced_noop = traced.apply({5, NodeId{1}, SetOperation::insert, {n(1), n(10)}});
  const auto quiet_noop = quiet.apply({5, NodeId{1}, SetOperation::insert, {n(1), n(10)}});
  check(!traced_noop.native_changed && !quiet_noop.native_changed &&
        !traced_noop.journal && !quiet_noop.journal &&
        metrics_view(traced_noop.metrics) == metrics_view(quiet_noop.metrics),
        "trace capture changed a no-op epoch");
}

void model_native_generalized_boolean_nullary_and_projection_counts() {
  {
    SupportOptions options;
    options.capture_transitions = true;
    SupportRuntime runtime(unary_plan(), options);
    const auto insert = apply_checked(runtime, {1, NodeId{0}, SetOperation::insert, {n(7)}});
    const auto erase = apply_checked(runtime, {2, NodeId{0}, SetOperation::erase, {n(7)}});
    check(insert.has_answer && !erase.has_answer, "native root journal replay missed answer crossings");
  }
  {
    SupportOptions options;
    options.capture_transitions = true;
    SupportRuntime runtime(generalized_three_plan(), options);
    static_cast<void>(apply_checked(runtime, {1, NodeId{1}, SetOperation::insert, {n(7)}}));
    static_cast<void>(apply_checked(runtime, {2, NodeId{2}, SetOperation::insert, {n(7)}}));
    const auto complete = apply_checked(runtime, {3, NodeId{3}, SetOperation::insert, {n(7)}});
    check(complete.has_answer && runtime.snapshot().nodes[0].records.size() == 1 &&
          runtime.snapshot().nodes[0].records[0].child_present == std::vector<bool>{true, true, true},
          "three-child generalized journal replay missed its final flags or answer");
  }
  {
    SupportOptions options;
    options.capture_transitions = true;
    SupportRuntime runtime(boolean_root_plan(), options);
    const auto yes = apply_checked(runtime, {1, NodeId{0}, SetOperation::insert, {n(12)}});
    const auto no = apply_checked(runtime, {2, NodeId{0}, SetOperation::erase, {n(12)}});
    check(yes.has_answer && !no.has_answer, "root Boolean query journal did not preserve truth semantics");
  }
  {
    SupportOptions options;
    options.capture_transitions = true;
    SupportRuntime runtime(nullary_plan(), options);
    const auto yes = apply_checked(runtime, {1, NodeId{0}, SetOperation::insert, {}});
    const auto no = apply_checked(runtime, {2, NodeId{0}, SetOperation::erase, {}});
    check(yes.has_answer && !no.has_answer && yes.journal->records.size() > 0,
          "nullary native tuple journal did not retain its Boolean membership");
  }
  {
    SupportOptions options;
    options.capture_transitions = true;
    SupportRuntime runtime(projected_count_plan(), options);
    static_cast<void>(apply_checked(runtime, {1, NodeId{0}, SetOperation::insert, {n(1), n(10)}}));
    const auto second = apply_checked(runtime, {2, NodeId{0}, SetOperation::insert, {n(1), n(20)}});
    const auto snapshot = runtime.snapshot();
    const auto& node = snapshot.nodes[0];
    const auto key = std::find_if(node.visible_keys->begin(), node.visible_keys->end(),
        [](const auto& value) { return value.key.values() == Row{n(1)}; });
    check(key != node.visible_keys->end() && key->support.value == 2 &&
          second.metrics.visible_key_transitions == 0 && second.metrics.metadata_changes > 0,
          "projected count journal failed to update a shared visible key without a membership crossing");
  }
}

void nested_event_chain_and_deep_cascade() {
  {
    SupportOptions options;
    options.capture_transitions = true;
    SupportRuntime runtime(nested_plan(), options);
    static_cast<void>(apply_checked(runtime, {1, NodeId{1}, SetOperation::insert, {n(1), n(10)}}));
    static_cast<void>(apply_checked(runtime, {2, NodeId{3}, SetOperation::insert, {n(1)}}));
    const auto cascade = apply_checked(runtime, {3, NodeId{2}, SetOperation::insert, {n(10)}});
    check(cascade.metrics.events_enqueued == 3 && cascade.metrics.events_applied == 3 &&
          cascade.metrics.child_key_events == 2 && cascade.journal->events.size() == 3 &&
          cascade.has_answer,
          "nested native-to-native-to-generalized propagation did not capture its three-event chain");
    const auto& events = cascade.journal->events;
    const auto native = std::find_if(events.begin(), events.end(), [](const auto& event) { return event.id == 1; });
    const auto parent = std::find_if(events.begin(), events.end(), [](const auto& event) { return event.id == 2; });
    const auto root = std::find_if(events.begin(), events.end(), [](const auto& event) { return event.id == 3; });
    check(native != events.end() && parent != events.end() && root != events.end() &&
          parent->cause == native->id && root->cause == parent->id &&
          native->applied_ordinal < parent->applied_ordinal && parent->applied_ordinal < root->applied_ordinal,
          "nested propagation event causes do not form the expected applied chain");
  }
  {
    constexpr std::size_t length = 128;
    SupportOptions options;
    options.work_limit.reset();
    options.capture_transitions = true;
    SupportRuntime runtime(deep_chain_plan(length), options);
    for (std::size_t i = 0; i + 1 < length; ++i)
      static_cast<void>(apply_checked(runtime, {runtime.sequence() + 1, NodeId{i},
          SetOperation::insert, {n(7)}}));
    const auto appeared = apply_checked(runtime, {runtime.sequence() + 1, NodeId{length - 1},
        SetOperation::insert, {n(7)}});
    check(appeared.metrics.survivor_transitions == length &&
          appeared.metrics.child_key_events == length - 1 &&
          appeared.metrics.events_applied == length && appeared.journal->events.size() == length &&
          runtime.has_answer(), "128-node journal cascade stopped before the root");
    const auto vanished = apply_checked(runtime, {runtime.sequence() + 1, NodeId{length - 1},
        SetOperation::erase, {n(7)}});
    check(vanished.metrics.survivor_transitions == length &&
          vanished.metrics.child_key_events == length - 1 &&
          vanished.metrics.events_applied == length && !runtime.has_answer(),
          "128-node journal deletion cascade stopped before the root");
  }
}

const JournalRecord& record_for(const SupportJournal& journal, SupportRole role,
                                const Row& values, bool after_member) {
  const auto found = std::find_if(journal.records.begin(), journal.records.end(), [&](const auto& record) {
    return record.handle.role == role && record.tuple().values() == values &&
        (after_member ? record.after.member : record.before.member);
  });
  if (found == journal.records.end()) throw std::runtime_error("journal omitted expected retained role value");
  return *found;
}

void retained_pins_outlive_updates_move_and_destruction() {
  const Row retained_row{n(42)};
  std::shared_ptr<const SupportJournal> insertion_journal;
  std::shared_ptr<const SupportJournal> deletion_journal;
  std::uint64_t owner = 0;
  {
    SupportOptions options;
    options.capture_transitions = false;
    SupportRuntime runtime(unary_plan(), options);
    owner = runtime.owner().value;
    const auto inserted = runtime.apply({1, NodeId{0}, SetOperation::insert, {n(42)}});
    insertion_journal = inserted.journal;
    check(insertion_journal && insertion_journal->events.empty(),
          "trace-off update omitted journal retention or captured an event trace");
    const auto& insert_record = record_for(*insertion_journal, SupportRole::records, retained_row, true);
    check(!insert_record.before.member && insert_record.after.member && insert_record.tuple().values() == Row{n(42)},
          "insert journal does not preserve its before/after record values");
    const auto inserted_stats = runtime.storage_statistics();
    check(inserted_stats.pins >= insertion_journal->records.size(),
          "storage statistics omit caller-retained insertion journal pins");

    SupportRuntime moved(std::move(runtime));
    const auto live_handle = moved.find(NodeId{0}, SupportRole::records, {n(42)});
    check(moved.owner().value == owner && live_handle && moved.get(*live_handle),
          "moving a runtime invalidated committed handles or its owner");
    const auto erased = moved.apply({2, NodeId{0}, SetOperation::erase, {n(42)}});
    deletion_journal = erased.journal;
    check(deletion_journal && deletion_journal->events.empty() && !moved.get(*live_handle),
          "trace-off deletion did not commit or unexpectedly retained a live handle");
    const auto& erased_record = record_for(*deletion_journal, SupportRole::records, retained_row, false);
    check(erased_record.before.member && !erased_record.after.member &&
          erased_record.tuple().values() == Row{n(42)},
          "delete journal does not retain its erased tuple and metadata");
    check(!insert_record.retained.is_live() && !erased_record.retained.is_live() &&
          moved.storage_statistics().retained_records > 0,
          "erased journal values are not pinned in aggregate storage statistics");
  }
  check(insertion_journal && deletion_journal && insertion_journal->sequence == 1 &&
        deletion_journal->sequence == 2,
        "journal lifetime depended on the moved/destroyed runtime");
  const auto& old_record = record_for(*insertion_journal, SupportRole::records, retained_row, true);
  const auto& removed_record = record_for(*deletion_journal, SupportRole::records, retained_row, false);
  check(old_record.tuple().values() == Row{n(42)} && removed_record.tuple().values() == Row{n(42)} &&
        old_record.handle.owner.value == owner && removed_record.handle.owner.value == owner,
        "retained before/after tuple values did not survive runtime destruction");
}

void unrelated_rows_are_not_copied_or_logged() {
  SupportOptions options;
  options.capture_transitions = true;
  SupportRuntime runtime(unary_plan(), options);
  constexpr std::int64_t unrelated = 32;
  for (std::int64_t i = 0; i < unrelated; ++i)
    static_cast<void>(runtime.apply({runtime.sequence() + 1, NodeId{0}, SetOperation::insert, {n(i)}}));
  const auto before = runtime.snapshot();
  check(before.nodes[0].records.size() == static_cast<std::size_t>(unrelated),
        "unrelated-row fixture did not populate 32 records");
  const auto epoch = apply_checked(runtime, {runtime.sequence() + 1, NodeId{0},
      SetOperation::insert, {n(1000)}});
  check(epoch.metrics.journal_records < static_cast<std::uint64_t>(unrelated),
        "one row update logged unrelated records from the 32-row state");
  for (const auto& record : epoch.journal->records) {
    if (record.handle.role == SupportRole::records || record.handle.role == SupportRole::survivors ||
        record.handle.role == SupportRole::visible) {
      check(record.tuple().values() == Row{n(1000)},
            "journal retained an unrelated tuple during a one-row update");
    }
  }

  SupportRuntime retained_runtime(unary_plan(), options);
  SupportEpoch retained_epoch = retained_runtime.apply({1, NodeId{0}, SetOperation::insert, {n(0)}});
  for (std::int64_t i = 1; i < unrelated; ++i)
    retained_epoch = retained_runtime.apply({retained_runtime.sequence() + 1, NodeId{0},
        SetOperation::insert, {n(i)}});
  for (std::int64_t i = 0; i < unrelated; ++i)
    static_cast<void>(retained_runtime.apply({retained_runtime.sequence() + 1, NodeId{0},
        SetOperation::erase, {n(i)}}));
  const auto stats = retained_runtime.storage_statistics();
  check(stats.live_records == 0 && stats.retained_records < static_cast<std::size_t>(unrelated) &&
        retained_epoch.journal && retained_epoch.journal->records.size() < static_cast<std::size_t>(unrelated),
        "one caller-retained update journal kept the whole 32-record state alive");
}

}  // namespace

int main() {
  try {
    model_native_generalized_boolean_nullary_and_projection_counts();
    trace_on_and_off_have_identical_accounting();
    nested_event_chain_and_deep_cascade();
    retained_pins_outlive_updates_move_and_destruction();
    unrelated_rows_are_not_copied_or_logged();
  } catch (const std::exception& failure) {
    std::cerr << failure.what() << '\n';
    return 1;
  }
  return 0;
}
