#include "indexed_runtime_fixture.hpp"
#include "crown/api/error.hpp"
#include "crown/frontend/bind.hpp"
#include "crown/frontend/normalize.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/delta.hpp"
#include "evaluator.hpp"
#include "native_input.hpp"
#ifdef CROWN_STATISTICS_ACCEPTANCE
#include "statistics_acceptance.hpp"
#endif

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <map>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace {
using namespace crown;
using namespace crown::runtime;
using SignedKey = std::pair<SetOperation, Row>;

std::uint64_t checked_updates = 0;
LiveMaintenance selected_policy=DeltaOptions{}.live_maintenance;
DeltaCompletion selected_completion=DeltaOptions{}.completion;
DeltaRuntime make_runtime(PhysicalPlan plan,DeltaOptions options={}) {
  options.live_maintenance=selected_policy;
  options.completion=selected_completion;
#ifdef CROWN_STATISTICS_ACCEPTANCE
  options.physical.support.order = statistics_acceptance::requested_order;
  DeltaRuntime runtime(std::move(plan),options);
  statistics_acceptance::enable(runtime);
  return runtime;
#else
  return DeltaRuntime(std::move(plan),options);
#endif
}
std::uint64_t checked_records = 0;
std::uint64_t checked_exhaustive_transitions = 0;
void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

template <class Action>
void expect_error(Action&& action, std::string_view code) {
  try {
    action();
  } catch (const Error& failure) {
    check(failure.code() == code,
          "expected " + std::string(code) + ", got " + failure.code());
    return;
  }
  throw std::runtime_error("expected error " + std::string(code));
}

Value n(std::int64_t value) { return value; }
Value s(std::string value) { return value; }

std::string row_string(const Row& row) {
  std::string result = "(";
  for (std::size_t i = 0; i < row.size(); ++i) {
    if (i != 0) result += ",";
    result += std::visit([](const auto& value) -> std::string {
      using T = std::decay_t<decltype(value)>;
      if constexpr (std::is_same_v<T, std::string>) return "\"" + value + "\"";
      else if constexpr (std::is_same_v<T, bool>) return value ? "true" : "false";
      else if constexpr (std::is_same_v<T, Date> || std::is_same_v<T, Decimal>)
        return value.to_string();
      else return std::to_string(value);
    }, row[i]);
  }
  return result + ")";
}

std::set<SignedKey> exact_difference(const Relation& before,
                                     const Relation& after) {
  std::set<SignedKey> result;
  for (const auto& row : after)
    if (!before.contains(row)) result.emplace(SetOperation::insert, row);
  for (const auto& row : before)
    if (!after.contains(row)) result.emplace(SetOperation::erase, row);
  return result;
}

std::set<SignedKey> record_set(const std::vector<SignedResult>& records) {
  std::set<SignedKey> result;
  for (const auto& record : records)
    check(result.emplace(record.operation, crown::storage::export_row(record.tuple.values())).second,
          "signed output vector contains a duplicate operation/row pair");
  check(result.size() == records.size(), "raw signed output cardinality changed");
  return result;
}

VariableSet variable_set(std::initializer_list<std::size_t> values) {
  VariableSet result;
  for (const auto value : values) result.insert(VariableId{value});
  return result;
}

FreeConnexTree sql_tree(const Query& query) {
  if (query.contradiction || query.atoms.empty()) return {};
  std::vector<VariableSet> scopes(query.atoms.size());
  for (std::size_t atom = 0; atom < query.atoms.size(); ++atom)
    for (const auto& term : query.atoms[atom].terms)
      if (const auto* variable = std::get_if<VariableId>(&term))
        scopes[atom].insert(*variable);
  if (query.atoms.size() == 1) {
    return {NodeId{0},
            {{query.atoms[0].occurrence, NodeKind::native, scopes[0], {}, 0, {}}},
            {}, {}};
  }

  auto common = scopes.front();
  for (std::size_t atom = 1; atom < scopes.size(); ++atom) {
    VariableSet overlap;
    std::set_intersection(common.begin(), common.end(), scopes[atom].begin(),
                          scopes[atom].end(),
                          std::inserter(overlap, overlap.end()));
    common = std::move(overlap);
  }
  std::vector<NodeId> children;
  for (std::size_t atom = 0; atom < query.atoms.size(); ++atom)
    children.push_back(NodeId{atom + 1});
  FreeConnexTree tree;
  tree.root = NodeId{0};
  tree.nodes.push_back({"sql_product", NodeKind::generalized, common,
                        children, {}, {}});
  for (std::size_t atom = 0; atom < query.atoms.size(); ++atom)
    tree.nodes.push_back({query.atoms[atom].occurrence, NodeKind::native,
                          scopes[atom], {}, atom, {}});
  return tree;
}

PhysicalPlan sql_plan(std::string_view sql, const Catalog& catalog) {
  const auto bound = frontend::bind_sql(sql, catalog);
  if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&bound))
    throw std::runtime_error(failure->diagnostic.code + ": " +
                             failure->diagnostic.message);
  auto normalized = frontend::normalize_sql(std::get<frontend::BoundSql>(bound));
  if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&normalized))
    throw std::runtime_error(failure->diagnostic.code + ": " +
                             failure->diagnostic.message);
  auto program = std::get<frontend::NormalizedSql>(std::move(normalized));
  return s04_runtime::lower_normalized(program, sql_tree(program.core));
}

Relation a04_core(const auto& plan, const Database& physical) {
  const auto& normalized = plan.normalized();
  if (!normalized)
    return reference::evaluate(reference::input::catalog(plan.catalog()), reference::input::query(plan.query()), physical);

  const auto& program = reference::input::normalized(*normalized);
  Database logical;
  logical.tables.resize(program.core_catalog.tables.size());
  for (const auto& adapter : program.adapters) {
    const auto target = program.core.atoms.at(adapter.occurrence.value).table.value;
    for (const auto& row : physical.tables.at(adapter.base.value))
      if (auto mapped = frontend::adapt_row(program, adapter.occurrence, row))
        logical.tables.at(target).insert(std::move(*mapped));
  }
  return reference::evaluate(program.core_catalog, program.core, logical);
}

Relation a04_output(const auto& plan, const Database& physical) {
  const auto core = a04_core(plan, physical);
  if (plan.normalized())
    return frontend::map_sql_result(reference::input::normalized(*plan.normalized()), core);
  return core;
}

std::vector<Relation> project_core_to_live_scopes(const auto& plan,
                                                  const Relation& core) {
  std::map<VariableId, std::size_t> head_positions;
  for (std::size_t field = 0; field < plan.query().head.size(); ++field)
    head_positions.try_emplace(plan.query().head[field].variable, field);

  std::vector<Relation> result;
  result.reserve(plan.enumeration().steps.size());
  for (const auto& step : plan.enumeration().steps) {
    const auto& scope = plan.nodes().at(step.node.value).visible_scope;
    Relation factor;
    for (const auto& assignment : core) {
      Row key;
      key.reserve(scope.size());
      for (const auto variable : scope) {
        const auto position = head_positions.find(variable);
        check(position != head_positions.end(),
              "A04 live-scope variable is absent from the core result head");
        key.push_back(assignment.at(position->second));
      }
      factor.insert(std::move(key));
    }
    result.push_back(std::move(factor));
  }
  return result;
}

void check_live(const DeltaRuntime& runtime, const Database& physical,
                const std::string& where) {
  if (runtime.mode() == DeltaMode::maintenance) {
    check(!runtime.live_snapshot(), where + ": maintenance mode retained L");
    return;
  }
  const auto live = runtime.live_snapshot();
  check(live.has_value(), where + ": delta mode has no live snapshot");
  check(live->sequence == runtime.sequence(), where + ": live sequence is stale");
  const auto expected = project_core_to_live_scopes(runtime.plan(),
                                                     a04_core(runtime.plan(), physical));
  check(live->factors == expected,
        where + ": maintained live factors differ from A04 answer projections");
}

struct OracleRoute {
  TableId base;
  TableId target;
  Relation shadow;
};

// Independent occurrence-prefix evaluator. It expands each physical input
// occurrence into its own table and invokes the materializing A04 evaluator
// after every routed derivation. It does not use the D03 partition model.
template<class Plan> class PrefixOracle {
 public:
  PrefixOracle(const Plan& plan, const Database& physical)
      : plan_(plan), normalized_(plan.normalized().has_value()) {
    if (normalized_) {
      const auto& program = reference::input::normalized(*plan_.normalized());
      catalog_ = reference::input::catalog(plan_.catalog());
      query_ = reference::input::query(plan_.query());
      database_.tables.resize(catalog_.tables.size());
      if (plan_.route() != PhysicalRoute::tree) return;
      routes_.resize(plan_.inputs().size());
      for (const auto& adapter : program.adapters) {
        const auto occurrence = adapter.occurrence.value;
        const auto target = program.core.atoms.at(occurrence).table;
        routes_.at(occurrence) = OracleRoute{
            adapter.base, target, physical.tables.at(adapter.base.value)};
        rebuild_normalized(OccurrenceId{occurrence});
      }
    } else {
      catalog_ = reference::input::catalog(plan_.source_catalog());
      query_ = reference::input::query(plan_.query());
      database_ = physical;
      routes_.resize(plan_.inputs().size());
      for (const auto& input : plan_.inputs()) {
        const auto occurrence = input.occurrence.value;
        const auto target = TableId{catalog_.tables.size()};
        auto table = catalog_.tables.at(input.base.value);
        table.name += "__prefix_occ" + std::to_string(occurrence);
        catalog_.tables.push_back(std::move(table));
        query_.atoms.at(occurrence).table = target;
        auto shadow = physical.tables.at(input.base.value);
        database_.tables.push_back(shadow);
        routes_.at(occurrence) = OracleRoute{input.base, target, std::move(shadow)};
      }
    }
  }

  [[nodiscard]] Relation core() const {
    return reference::evaluate(catalog_, query_, database_);
  }

  [[nodiscard]] Relation output() const {
    const auto result = core();
    if (normalized_)
      return frontend::map_sql_result(reference::input::normalized(*plan_.normalized()), result);
    return result;
  }

  void apply(OccurrenceId occurrence, const PhysicalSetUpdate& update) {
    auto& route = routes_.at(occurrence.value);
    check(route.base == update.table,
          "physical derivation was routed to an unrelated base table");
    if (update.operation == SetOperation::insert) {
      check(route.shadow.insert(update.values).second,
            "prefix oracle inserted a duplicate occurrence source row");
    } else {
      check(route.shadow.erase(update.values) == 1,
            "prefix oracle deleted an absent occurrence source row");
    }
    if (normalized_) rebuild_normalized(occurrence);
    else database_.tables.at(route.target.value) = route.shadow;
  }

 private:
  void rebuild_normalized(OccurrenceId occurrence) {
    const auto& program = reference::input::normalized(*plan_.normalized());
    const auto& route = routes_.at(occurrence.value);
    Relation logical;
    for (const auto& row : route.shadow)
      if (auto mapped = frontend::adapt_row(program, occurrence, row))
        logical.insert(std::move(*mapped));
    database_.tables.at(route.target.value) = std::move(logical);
  }

  const Plan& plan_;
  bool normalized_;
  Catalog catalog_;
  Query query_;
  Database database_;
  std::vector<OracleRoute> routes_;
};

struct ActualEpoch {
  std::vector<SignedResult> records;
  std::vector<DeltaStage> stages;
  DeltaMetrics metrics;
  PhysicalMetrics physical_metrics;
  std::vector<DerivationChange> derivations;
  bool physical_changed = false;
};

Relation drain_current(SupportRuntime::ResultCursor& cursor,
                       const std::string& where) {
  Relation rows;
  while (auto tuple = cursor.next()) {
    check(tuple->layout().same_token(cursor.layout()),
          where + ": current tuple has a different layout token");
    check(tuple->values().size() == cursor.layout().fields().size(),
          where + ": current tuple has the wrong arity");
    for (std::size_t field = 0; field < tuple->values().size(); ++field)
      check(type_of(tuple->values()[field]) == cursor.layout().fields()[field].type,
            where + ": current tuple has a wrong field type");
    check(rows.insert(crown::storage::export_row(tuple->values())).second,
          where + ": current result cursor emitted a duplicate row");
  }
  check(cursor.state() == ResultCursorState::exhausted && !cursor.active(),
        where + ": current result cursor did not release its lease");
  return rows;
}

void check_current(const DeltaRuntime& runtime, const Database& physical,
                   const std::string& where) {
  auto core_cursor = runtime.core_results();
  check(drain_current(core_cursor, where + " core") ==
            a04_core(runtime.plan(), physical),
        where + ": current core cursor differs from A04");
  auto output_cursor = runtime.results();
  check(drain_current(output_cursor, where + " SQL") ==
            a04_output(runtime.plan(), physical),
        where + ": current public cursor differs from A04");
}

ActualEpoch drain_epoch(DeltaRuntime& runtime, DeltaRuntime::Epoch& epoch,
                        const std::set<SignedKey>& expected,
                        const std::string& where) {
  check(epoch.layout().same_token(runtime.result_layout()),
        where + ": epoch output layout token differs from runtime");
  check(epoch.remaining() == expected.size(),
        where + ": spool remaining count differs from exact A04 delta");
  check(epoch.active() == !expected.empty(),
        where + ": output lease state differs from the signed result count");
  check(runtime.ready() == expected.empty(),
        where + ": runtime readiness differs from pending output state");

  ActualEpoch actual;
  actual.records.reserve(expected.size());
  std::uint64_t prior_ordinal = 0;
  while (auto record = epoch.next()) {
    check(record->tuple.layout().same_token(epoch.layout()),
          where + ": signed tuple has a different layout token");
    check(record->tuple.values().size() == epoch.layout().fields().size(),
          where + ": signed tuple has the wrong arity");
    for (std::size_t field = 0; field < record->tuple.values().size(); ++field)
      check(type_of(record->tuple.values()[field]) == epoch.layout().fields()[field].type,
            where + ": signed tuple has a wrong field type");
    check(record->ordinal == prior_ordinal + 1,
          where + ": output ordinal is not a contiguous accepted-record order");
    prior_ordinal = record->ordinal;
    actual.records.push_back(std::move(*record));
  }
  check(record_set(actual.records) == expected,
        where + ": signed output differs from the independent A04 set difference");
  check(!epoch.active() && runtime.ready(),
        where + ": draining output did not release the writer barrier");
  check(!epoch.next(), where + ": exhausted output returned an extra record");
  checked_records += static_cast<std::uint64_t>(actual.records.size());
  return actual;
}

ActualEpoch apply_checked(DeltaRuntime& runtime, Database& database,
                          const PhysicalSetUpdate& update,
                          const std::string& label, bool print_trace = false) {
  check(update.sequence == runtime.sequence() + 1,
        label + ": fixture sequence is not contiguous");
  const auto before_output = a04_output(runtime.plan(), database);
  const auto before_core = a04_core(runtime.plan(), database);
  auto after_database = database;
  auto& table = after_database.tables.at(update.table.value);
  const bool physical_changed = update.operation == SetOperation::insert
      ? table.insert(update.values).second
      : table.erase(update.values) == 1;
  const auto after_output = a04_output(runtime.plan(), after_database);
  const auto expected = exact_difference(before_output, after_output);

  PrefixOracle prefixes(runtime.plan(), database);
#ifdef CROWN_STATISTICS_ACCEPTANCE
  const auto c01_before = runtime.workload_statistics();
#endif
  auto input = runtime.apply(update);
  check(input.sequence() == update.sequence && runtime.sequence() == update.sequence,
        label + ": physical/delta sequence did not commit");
  check(input.input().input.physical_changed == physical_changed,
        label + ": physical changed flag differs from source-set update");
  check(static_cast<std::uint64_t>(input.input().input.derivations.size()) ==
            input.input().input.metrics.derivation_changes,
        label + ": physical derivation audit count differs");

  std::map<OccurrenceId, const DeltaStage*> stages;
  for (const auto& stage : input.stages())
    check(stages.emplace(stage.occurrence, &stage).second,
          label + ": one input produced duplicate native stages for an occurrence");

  const auto scalar_exists = runtime.plan().normalized() &&
      runtime.options().view == ResultView::sql &&
      runtime.plan().normalized()->binding.wrapper == frontend::SqlWrapper::exists;
  std::vector<SignedResult> records;
  records.reserve(expected.size());
  struct StageExpectation {
    OccurrenceId occurrence;
    std::uint64_t prefix;
    std::set<SignedKey> outputs;
    std::size_t live_rows;
  };
  std::vector<StageExpectation> stage_expectations;
  auto prefix_core = prefixes.core();
  auto prefix_output = prefixes.output();
  check(prefix_core == before_core && prefix_output == before_output,
        label + ": expanded occurrence-prefix A04 differs before the event");

  std::size_t stage_index = 0;
  for (const auto& derivation : input.input().input.derivations) {
    const auto before_route_core = prefixes.core();
    const auto before_route_output = prefixes.output();
    prefixes.apply(derivation.occurrence, update);
    const auto after_route_core = prefixes.core();
    const auto after_route_output = prefixes.output();
    const auto stage = stages.find(derivation.occurrence);
    if (stage == stages.end()) {
      check(derivation.before > 0 && derivation.after > 0 &&
                !derivation.native_changed,
            label + ": a zero crossing did not produce its DeltaStage metadata");
      check(before_route_core == after_route_core,
            label + ": count-only occurrence changed the A04 answer");
      check(before_route_output == after_route_output || scalar_exists,
            label + ": count-only occurrence changed mapped A04 output");
      continue;
    }

    const auto& route_stage = *stage->second;
    check(derivation.native_changed &&
              ((derivation.before == 0) != (derivation.after == 0)),
          label + ": staged occurrence did not cross native support zero");
    const auto& physical_routes =
        runtime.plan().base_routes().at(update.table.value);
    const auto route_position = std::find(physical_routes.begin(),
                                          physical_routes.end(),
                                          derivation.occurrence);
    check(route_position != physical_routes.end(),
          label + ": changed occurrence is absent from its physical route list");
    const auto expected_prefix = static_cast<std::uint64_t>(
        std::distance(physical_routes.begin(), route_position) + 1);
    ++stage_index;
    check(route_stage.prefix == expected_prefix,
          label + ": stage tag does not preserve its physical route ordinal");
    check(route_stage.before_answer == !before_route_core.empty() &&
              route_stage.after_answer == !after_route_core.empty(),
          label + ": stage truth flags differ from prefix A04");
    const auto live = project_core_to_live_scopes(runtime.plan(), after_route_core);
    std::size_t live_rows = 0;
    for (const auto& factor : live) live_rows += factor.size();
    check(route_stage.live_rows == live_rows,
          label + ": stage live row count differs from exact A04 projections");

    const auto stage_expected = exact_difference(before_route_output,
                                                  after_route_output);
    std::set<SignedKey> expected_stage_outputs = stage_expected;
    if (scalar_exists) {
      check(route_stage.output_count == 0,
            label + ": EXISTS replacement leaked into a per-route output interval");
      expected_stage_outputs.clear();
    } else {
      check(route_stage.output_count == stage_expected.size(),
            label + ": per-route spool interval length differs from A04 prefix delta");
      check(route_stage.output_begin <= expected.size() &&
                route_stage.output_count <= expected.size() - route_stage.output_begin,
            label + ": route interval exceeds the final output size");
    }
    stage_expectations.push_back({derivation.occurrence, route_stage.prefix,
                                  std::move(expected_stage_outputs), live_rows});
    stages.erase(stage);
  }
  check(stages.empty(), label + ": DeltaStage has no matching occurrence route");
  check(prefixes.output() == after_output,
        label + ": fully expanded occurrence-prefix A04 differs from physical A04");
  check(input.stages().size() == stage_index,
        label + ": stage count differs from native crossing routes");

  auto actual = drain_epoch(runtime, input, expected, label);
  records = std::move(actual.records);
  check(input.stages().size() == stage_expectations.size(),
        label + ": stage metadata count changed after output delivery");
  std::size_t expected_output_begin = 0;
  for (std::size_t i = 0; i < input.stages().size(); ++i) {
    const auto& stage = input.stages()[i];
    const auto& oracle = stage_expectations[i];
    check(stage.occurrence == oracle.occurrence && stage.prefix == oracle.prefix,
          label + ": stage occurrence/prefix changed after output delivery");
    check(stage.output_begin == expected_output_begin,
          label + ": stage output intervals are not contiguous in route order");
    check(stage.output_count == oracle.outputs.size() &&
              stage.live_rows == oracle.live_rows,
          label + ": stage output or live-row count differs from A04 prefix");
    check(stage.candidates == stage.accepted + stage.rejected,
          label + ": stage candidate accounting does not reconcile");
    check(stage.output_begin <= records.size() &&
              stage.output_count <= records.size() - stage.output_begin,
          label + ": stage output interval is outside the committed spool");
    std::vector<SignedResult> stage_records;
    for (std::size_t offset = 0; offset < stage.output_count; ++offset)
      stage_records.push_back(records.at(stage.output_begin + offset));
    check(record_set(stage_records) == oracle.outputs,
          label + ": route spool interval differs from independent A04 prefix delta");
    expected_output_begin += stage.output_count;
  }
  if (!scalar_exists)
    check(expected_output_begin == records.size(),
          label + ": ordinary output records escaped all occurrence stage ranges");

  database = std::move(after_database);
  check(runtime.snapshot().physical.tables == database.tables,
        label + ": committed physical source differs from A04 database");
  check(runtime.has_answer() == !a04_core(runtime.plan(), database).empty(),
        label + ": runtime answer truth differs from A04");
  check_live(runtime, database, label);
  check_current(runtime, database, label);
  runtime.check_invariants();
  const bool replay=runtime.completion()==DeltaCompletion::ordered_replay;
  if (runtime.completion()!=DeltaCompletion::root_first) {
    check(input.metrics().anchor_cursors==input.metrics().live_witnesses,
          label+": live witnesses and anchored cursor ownership differ");
    if (input.metrics().candidates!=0)
      check(input.metrics().anchor_max_startup_work>0 && input.metrics().anchor_max_result_work>0 &&
                input.metrics().anchor_max_termination_work>0,
            label+": anchored candidate startup/result/termination maxima were not recorded");
  }
  if (replay) {
    const auto& metrics=input.metrics();
    check(metrics.rejected==0 && metrics.earlier_probes==0 && metrics.candidates==metrics.accepted &&
              metrics.replay_witness_tests==metrics.changed_keys &&
              metrics.replay_queue_inserts==metrics.replay_queue_pops+metrics.replay_queue_erases &&
              metrics.replay_queue_pops==metrics.live_witnesses && metrics.replay_queue_releases==metrics.replay_queue_pops,
          label+": replay queue/owner partition retained rejected or dead candidates");
    const auto final_sql_work=scalar_exists?2*records.size():0;
    check(metrics.replay_preparation_work+metrics.replay_first_work+metrics.replay_results_work+
              metrics.replay_termination_work+metrics.finalization_work+final_sql_work==metrics.work,
          label+": replay preparation/producer/SQL-final work does not partition total delta work");
    if (metrics.accepted!=0)
      check(metrics.replay_max_first_work>0 && metrics.replay_max_last_work>0,
            label+": replay first/last accepted transition maxima missing");
  }
  if (runtime.options().live_maintenance!=LiveMaintenance::eager) {
    const auto after_core=a04_core(runtime.plan(),database);
    const auto old_live=project_core_to_live_scopes(runtime.plan(),before_core);
    const auto new_live=project_core_to_live_scopes(runtime.plan(),after_core);
    std::vector<std::uint64_t> changed_live(old_live.size(),0), degree(old_live.size(),0);
    std::uint64_t inserted=0,erased=0,updates=0,edges=0,index_rows=0,index_fields=0;
    std::uint64_t child_changes=0,child_rows=0,child_fields=0,child_separator_fields=0;
    for (std::size_t i=0;i<old_live.size();++i) {
      for (const auto& key : new_live[i]) if (!old_live[i].contains(key)) { ++inserted; ++changed_live[i]; }
      for (const auto& key : old_live[i]) if (!new_live[i].contains(key)) { ++erased; ++changed_live[i]; }
    }
    for (const auto& step : runtime.plan().enumeration().steps) if (step.parent_step) { ++degree[*step.parent_step]; ++edges; }
    for (std::size_t i=0;i<degree.size();++i) {
      updates+=degree[i]*changed_live[i];
      index_rows+=degree[i]*new_live[i].size();
      index_fields+=degree[i]*changed_live[i]*runtime.plan().nodes()[runtime.plan().enumeration().steps[i].node.value].visible_scope.size();
      const auto& step=runtime.plan().enumeration().steps[i];
      if (step.parent_step) {
        child_changes+=changed_live[i]; child_rows+=new_live[i].size();
        child_fields+=changed_live[i]*runtime.plan().nodes()[step.node.value].visible_scope.size();
        child_separator_fields+=changed_live[i]*runtime.plan().indexes()[step.bucket_index->value].projection.fields().size();
      }
    }
    const auto& metrics=input.metrics(); const auto changes=inserted+erased;
    check(metrics.live_changes==changes && metrics.live_inserts==inserted && metrics.live_erases==erased,
          label+": incremental L mutations differ from exact global projections");
    const bool buckets=runtime.options().live_maintenance==LiveMaintenance::incremental;
    check(metrics.live_bucket_rows<=changes && metrics.live_separator_updates==updates &&
              (buckets?metrics.live_bucket_opens==metrics.live_separator_crossings:
                       metrics.live_bucket_opens==0 && metrics.live_bucket_rows==0) &&
              metrics.live_journal_entries==changes+updates+child_changes &&
              metrics.live_rows_copied==(!replay || update.operation==SetOperation::insert?changes:0),
          label+": incremental live bucket/count/undo accounting does not match the proof");
    const bool parent_copy=!replay || update.operation==SetOperation::insert;
    check(metrics.live_parent_index_updates==updates && metrics.live_parent_index_rows_copied==(parent_copy?updates:0) &&
              metrics.live_parent_index_fields==(parent_copy?index_fields:0) &&
              metrics.live_parent_index_cleanup_rows==(!replay && update.operation==SetOperation::erase?updates:0) &&
              metrics.parent_index_rows==index_rows && metrics.peak_parent_index_rows>=index_rows,
          label+": live-parent index mutation/copy/cleanup counters differ from degree-weighted L changes");
    check(metrics.live_child_index_updates==child_changes &&
              metrics.live_child_index_rows_copied==(update.operation==SetOperation::insert?child_changes:0) &&
              metrics.live_child_index_fields==(update.operation==SetOperation::insert?child_fields:0) &&
              metrics.live_child_separator_fields==child_separator_fields && metrics.child_index_rows==child_rows &&
              metrics.peak_child_index_rows>=child_rows,
          label+": live-child index changes/copies/fields/rows differ from exact A04 L projections");
    if (replay) check(metrics.replay_queue_lookups==erased,
        label+": replay queue pruning did not inspect every actual L erasure exactly once");
    check(metrics.finalization_undo_entries==metrics.live_journal_entries,
          label+": finalization did not charge every actual live/index undo entry");
    check(metrics.e_rows_scanned==0 && metrics.parent_live_rows==0,
          label+": incremental update performed a full live rebuild");
    const auto delta_size=exact_difference(before_core,after_core).size();
    check(changes<=static_cast<std::uint64_t>(old_live.size())*delta_size && updates<=edges*delta_size,
          label+": incremental live/count changes exceed their factor/edge times exact core delta bounds");
  }
  actual.stages.assign(input.stages().begin(), input.stages().end());
  actual.metrics = input.metrics();
  actual.physical_metrics = input.input().input.metrics;
  actual.derivations.assign(input.input().input.derivations.begin(), input.input().input.derivations.end());
  actual.physical_changed = input.input().input.physical_changed;
#ifdef CROWN_STATISTICS_ACCEPTANCE
  statistics_acceptance::event(c01_before, runtime.workload_statistics(), update, physical_changed, label,
      std::span<const DerivationChange>{actual.derivations});
  statistics_acceptance::sources(runtime, database, label);
#endif
  ++checked_updates;

  if (print_trace && !records.empty()) {
    std::cout << "trace " << label << " seq=" << update.sequence << " outputs=";
    for (std::size_t i = 0; i < records.size(); ++i) {
      if (i != 0) std::cout << ",";
      std::cout << (records[i].operation == SetOperation::insert ? "+" : "-")
                << row_string(crown::storage::export_row(records[i].tuple.values()));
    }
    std::cout << '\n';
  }
  actual.records = std::move(records);
  return actual;
}

void seed_maintenance(DeltaRuntime& runtime, const Database& database,
                      const std::string& label) {
  check(runtime.mode() == DeltaMode::maintenance && !runtime.live_snapshot(),
        label + ": seed runtime must start in maintenance mode without L");
  for (std::size_t table = 0; table < database.tables.size(); ++table) {
    for (const auto& row : database.tables[table]) {
      auto seed = runtime.apply({runtime.sequence() + 1, TableId{table},
                                 SetOperation::insert, row});
      check(seed.remaining() == 0 && !seed.active() && runtime.ready() &&
                !seed.next(),
            label + ": maintenance seed unexpectedly produced output");
    }
  }
  check(runtime.snapshot().physical.tables == database.tables,
        label + ": maintenance seed source state differs from fixture");
  static_cast<void>(runtime.set_mode(DeltaMode::delta));
  check_live(runtime, database, label + " bootstrap");
}

PhysicalPlan hidden_projection_plan() {
  const Catalog catalog{1, {{"r", {{"x", ScalarType::int64},
                                    {"z", ScalarType::int64},
                                    {"payload", ScalarType::string}}}}};
  const Query query{{{"x", ScalarType::int64}, {"z", ScalarType::int64}},
                    {{"r", TableId{0}, {VariableId{0}, VariableId{1},
                                        IgnoredColumn{}}}},
                    {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, variable_set({0, 1}), {}, 0, {}}}, {}, {}};
  return s04_runtime::lower_tree(catalog, query, tree);
}

PhysicalPlan hidden_binary_plan() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}, {"z", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"z", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}, VariableId{1}}}},
      {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, variable_set({0, 1}), {}, 0, {}}}, {}, {}};
  return s04_runtime::lower_tree(catalog, query, tree);
}

PhysicalPlan root_pair_plan() {
  const Catalog catalog{1, {{"r", {{"x", ScalarType::int64},
                                    {"y", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}, VariableId{1}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "y"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, variable_set({0, 1}), {}, 0, {}}}, {}, {}};
  return s04_runtime::lower_tree(catalog, query, tree);
}

PhysicalPlan ancestor_child_plan() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}}},
       {"s", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}}},
       {"s", TableId{1}, {VariableId{0}, VariableId{1}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "y"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, variable_set({0}), {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, variable_set({0, 1}), {}, 1, {}}}, {}, {}};
  return s04_runtime::lower_tree(catalog, query, tree);
}

PhysicalPlan deep_chain_plan() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}},
       {"s", {{"y", ScalarType::int64}, {"z", ScalarType::int64}}},
       {"t", {{"z", ScalarType::int64}, {"w", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64},
                     {"z", ScalarType::int64}, {"w", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"s", TableId{1}, {VariableId{1}, VariableId{2}}},
       {"t", TableId{2}, {VariableId{2}, VariableId{3}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "y"}, {VariableId{2}, "z"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, variable_set({0, 1}), {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, variable_set({1, 2}), {NodeId{2}}, 1, {}},
       {"t", NodeKind::native, variable_set({2, 3}), {}, 2, {}}}, {}, {}};
  return s04_runtime::lower_tree(catalog, query, tree);
}

PhysicalPlan root_child_plan() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}}},
       {"s", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}}},
       {"s", TableId{1}, {VariableId{0}, VariableId{1}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "y"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, variable_set({0}), {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, variable_set({0, 1}), {}, 1, {}}}, {}, {}};
  return s04_runtime::lower_tree(catalog, query, tree);
}

PhysicalPlan projected_path_plan() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}}},
       {"s", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}}},
       {"s", TableId{1}, {VariableId{0}, VariableId{1}}}},
      {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, variable_set({0}), {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, variable_set({0, 1}), {}, 1, {}}}, {}, {}};
  return s04_runtime::lower_tree(catalog, query, tree);
}

PhysicalPlan hidden_separator_plan() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}, {"z", ScalarType::int64}}},
       {"s", {{"z", ScalarType::int64}, {"y", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"z", ScalarType::int64},
                     {"y", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"s", TableId{1}, {VariableId{1}, VariableId{2}}}},
      {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, variable_set({0, 1}), {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, variable_set({1, 2}), {}, 1, {}}}, {}, {}};
  return s04_runtime::lower_tree(catalog, query, tree);
}

PhysicalPlan boolean_unary_plan() {
  const Catalog catalog{1, {{"r", {{"x", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}}}}, {}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, variable_set({0}), {}, 0, {}}}, {}, {}};
  return s04_runtime::lower_tree(catalog, query, tree);
}

PhysicalPlan shared_separator_plan() {
  const Catalog catalog{1,
      {{"r", {{"a", ScalarType::int64}, {"x", ScalarType::int64}}},
       {"s", {{"x", ScalarType::int64}, {"z", ScalarType::int64}}}}};
  const Query query{{{"a", ScalarType::int64}, {"x", ScalarType::int64},
                     {"z", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"s", TableId{1}, {VariableId{1}, VariableId{2}}}},
      {{VariableId{0}, "a"}, {VariableId{1}, "x"}, {VariableId{2}, "z"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, variable_set({0, 1}), {NodeId{1}}, 0, {}},
       {"s", NodeKind::native, variable_set({1, 2}), {}, 1, {}}}, {}, {}};
  return s04_runtime::lower_tree(catalog, query, tree);
}

PhysicalPlan self_join_plan() {
  const Catalog catalog{1,
      {{"edge", {{"src", ScalarType::int64}, {"dst", ScalarType::int64},
                   {"payload", ScalarType::string}}}}};
  const Query query{{{"x", ScalarType::int64}, {"z", ScalarType::int64},
                     {"y", ScalarType::int64}},
      {{"left", TableId{0}, {VariableId{0}, VariableId{1}, IgnoredColumn{}}},
       {"right", TableId{0}, {VariableId{1}, VariableId{2}, IgnoredColumn{}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "z"}, {VariableId{2}, "y"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"join", NodeKind::generalized, variable_set({1}), {NodeId{1}, NodeId{2}}, {}, {}},
       {"left", NodeKind::native, variable_set({0, 1}), {}, 0, {}},
       {"right", NodeKind::native, variable_set({1, 2}), {}, 1, {}}}, {}, {}};
  return s04_runtime::lower_tree(catalog, query, tree);
}

PhysicalPlan same_scope_alias_plan() {
  const Catalog catalog{1,
      {{"edge", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"left", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"right", TableId{0}, {VariableId{0}, VariableId{1}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "y"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"join", NodeKind::generalized, variable_set({0, 1}), {NodeId{1}, NodeId{2}}, {}, {}},
       {"left", NodeKind::native, variable_set({0, 1}), {}, 0, {}},
       {"right", NodeKind::native, variable_set({0, 1}), {}, 1, {}}}, {}, {}};
  return s04_runtime::lower_tree(catalog, query, tree);
}

PhysicalPlan product_plan(std::size_t arity) {
  Catalog catalog;
  Query query;
  FreeConnexTree tree;
  tree.root = NodeId{0};
  std::vector<NodeId> children;
  for (std::size_t i = 0; i < arity; ++i) {
    query.variables.push_back({"x" + std::to_string(i), ScalarType::int64});
    query.atoms.push_back({"r" + std::to_string(i), TableId{i},
                           {VariableId{i}}});
    query.head.push_back({VariableId{i}, "x" + std::to_string(i)});
    catalog.tables.push_back({"r" + std::to_string(i),
                              {{"x", ScalarType::int64}}});
    children.push_back(NodeId{i + 1});
  }
  tree.nodes.push_back({"product", NodeKind::generalized, {}, children, {}, {}});
  for (std::size_t i = 0; i < arity; ++i)
    tree.nodes.push_back({"r" + std::to_string(i), NodeKind::native,
                          variable_set({i}), {}, i, {}});
  return s04_runtime::lower_tree(catalog, query, tree);
}

void exhaustive_family(const std::string& label, const PhysicalPlan& plan,
                       const std::vector<std::vector<Row>>& domains) {
  std::size_t state_count = 1;
  for (const auto& domain : domains) {
    check(domain.size() < sizeof(std::size_t) * 8,
          label + ": exhaustive domain is too large for its mask");
    state_count *= std::size_t{1} << domain.size();
  }
  const auto family_start = checked_exhaustive_transitions;

  // For each binary relation state, toggle each domain row in fixed order.
  // At toggle i, prior toggles XOR a fixed prefix of bits. As the initial mask
  // ranges over every state, the pre-toggle state ranges over every state too;
  // therefore this walk covers every directed one-row toggle exactly once.
  for (std::size_t initial_state = 0; initial_state < state_count;
       ++initial_state) {
    Database database;
    database.tables.resize(domains.size());
    std::size_t encoded_state = initial_state;
    for (std::size_t table = 0; table < domains.size(); ++table) {
      const auto radix = std::size_t{1} << domains[table].size();
      const auto mask = encoded_state % radix;
      encoded_state /= radix;
      for (std::size_t row = 0; row < domains[table].size(); ++row)
        if ((mask & (std::size_t{1} << row)) != 0)
          database.tables[table].insert(domains[table][row]);
    }

    DeltaOptions options;
    options.mode = DeltaMode::maintenance;
    auto runtime = make_runtime(plan, options);
    for (std::size_t table = 0; table < database.tables.size(); ++table) {
      for (const auto& row : database.tables[table]) {
        auto seed = runtime.apply({runtime.sequence() + 1, TableId{table},
                                   SetOperation::insert, row});
        check(seed.remaining() == 0 && runtime.ready() && !seed.next(),
              label + ": maintenance fixture seed unexpectedly emitted output");
      }
    }
    check(runtime.snapshot().physical.tables == database.tables,
          label + ": maintenance seed differs from its selected state");
    static_cast<void>(runtime.set_mode(DeltaMode::delta));
    check_live(runtime, database, label + " bootstrap");

    std::size_t tuple_index = 0;
    for (std::size_t table = 0; table < domains.size(); ++table) {
      for (const auto& row : domains[table]) {
        const auto operation = database.tables[table].contains(row)
            ? SetOperation::erase : SetOperation::insert;
        static_cast<void>(apply_checked(runtime, database,
            {runtime.sequence() + 1, TableId{table}, operation, row},
            "exhaustive " + label + " state=" +
                std::to_string(initial_state) + " tuple=" +
                std::to_string(tuple_index)));
        ++tuple_index;
        ++checked_exhaustive_transitions;
      }
    }
  }

  std::cout << "exhaustive " << label << " transitions="
            << (checked_exhaustive_transitions - family_start) << '\n';
}

void exhaustive_binary_domain_toggles() {
  const std::vector<Row> hidden_domain{
      {n(0), n(0)}, {n(0), n(1)}, {n(1), n(0)}, {n(1), n(1)}};
  exhaustive_family("hidden R(x,z)", hidden_binary_plan(), {hidden_domain});

  const std::vector<Row> root_domain{{n(0)}, {n(1)}};
  const std::vector<Row> child_domain{
      {n(0), n(0)}, {n(0), n(1)}, {n(1), n(0)}, {n(1), n(1)}};
  exhaustive_family("projected R(x), S(x,y)", projected_path_plan(),
                    {root_domain, child_domain});

  const std::vector<Row> chain_domain{
      {n(0), n(0)}, {n(0), n(1)}, {n(1), n(0)}, {n(1), n(1)}};
  exhaustive_family("hidden-separator R(x,z), S(z,y)",
                    hidden_separator_plan(), {chain_domain, chain_domain});

  const std::vector<Row> boolean_domain{{n(0)}, {n(1)}};
  exhaustive_family("Boolean R(x)", boolean_unary_plan(), {boolean_domain});
  check(checked_exhaustive_transitions == 2504,
        "maintained exhaustive binary-domain toggle count differs from 2,504");
}

void projection_collisions_noops_and_count_only() {
  auto runtime = make_runtime(hidden_projection_plan());
  Database database;
  database.tables.resize(1);
  check_live(runtime, database, "hidden projection bootstrap");
  static_cast<void>(apply_checked(runtime, database,
      {1, TableId{0}, SetOperation::insert, {n(1), n(10), s("a")}},
      "hidden first witness"));
  const auto collision = apply_checked(runtime, database,
      {2, TableId{0}, SetOperation::insert, {n(1), n(11), s("b")}},
      "hidden projected collision");
  check(collision.records.empty(), "hidden z collision emitted projected x");
  check(collision.stages.size() == 1 &&
            collision.stages.front().changed_keys == 0 &&
            collision.stages.front().output_count == 0,
        "hidden z collision did not complete an empty visible-key stage");

  const auto count_only = apply_checked(runtime, database,
      {3, TableId{0}, SetOperation::insert, {n(1), n(11), s("c")}},
      "positive derivation count only");
  check(count_only.records.empty() && count_only.stages.empty() &&
            count_only.physical_metrics.derivation_changes == 1,
        "positive-to-positive derivation emitted output or a false native stage");
  const auto nonlast = apply_checked(runtime, database,
      {4, TableId{0}, SetOperation::erase, {n(1), n(11), s("b")}},
      "nonlast projected row derivation");
  check(nonlast.records.empty(), "nonlast physical witness emitted a delta");
  const auto hidden_key_removed = apply_checked(runtime, database,
      {5, TableId{0}, SetOperation::erase, {n(1), n(11), s("c")}},
      "hidden E key removed under surviving x");
  check(hidden_key_removed.records.empty(),
        "removing one hidden E key removed a still-live projected x");
  const auto last = apply_checked(runtime, database,
      {6, TableId{0}, SetOperation::erase, {n(1), n(10), s("a")}},
      "last projected witness deletion", true);
  check(record_set(last.records) ==
            std::set<SignedKey>{{SetOperation::erase, {n(1)}}},
        "last projected witness did not delete x exactly once");

  const auto reinsert = apply_checked(runtime, database,
      {7, TableId{0}, SetOperation::insert, {n(1), n(10), s("a")}},
      "reinsert last projected witness");
  check(record_set(reinsert.records) ==
            std::set<SignedKey>{{SetOperation::insert, {n(1)}}},
        "reinserting the last projected witness did not add x");
  const auto duplicate = apply_checked(runtime, database,
      {8, TableId{0}, SetOperation::insert, {n(1), n(10), s("a")}},
      "duplicate physical insert");
  const auto absent = apply_checked(runtime, database,
      {9, TableId{0}, SetOperation::erase, {n(9), n(90), s("absent")}},
      "absent physical erase");
  check(duplicate.records.empty() && absent.records.empty(),
        "physical no-op changed the output set");
  check(runtime.sequence() == 9,
        "physical no-op did not consume its contiguous sequence");
}

void root_ancestor_deep_and_global_liveness() {
  {
    DeltaOptions options;
    options.mode = DeltaMode::maintenance;
    auto runtime = make_runtime(root_pair_plan(), options);
    Database database{{Relation{{n(1), n(2)}, {n(3), n(4)}}}};
    seed_maintenance(runtime, database, "root pair seed");
    static_cast<void>(apply_checked(runtime, database,
        {runtime.sequence() + 1, TableId{0}, SetOperation::insert, {n(5), n(6)}},
        "empty separator root full-key binding", true));
  }
  {
    DeltaOptions options;
    options.mode = DeltaMode::maintenance;
    auto runtime = make_runtime(ancestor_child_plan(), options);
    Database database{{Relation{Row{n(1)}}, Relation{{n(1), n(10)}}}};
    seed_maintenance(runtime, database, "ancestor-child seed");
    const auto deletion = apply_checked(runtime, database,
        {runtime.sequence() + 1, TableId{1}, SetOperation::erase, {n(1), n(10)}},
        "ancestor child before-context deletion", true);
    check(deletion.records.size() == 1,
          "ancestor/child removal did not emit exactly one assignment");
    check(deletion.stages.size() == 1 &&
              deletion.stages.front().changed_keys == 2 &&
              deletion.stages.front().accepted == 1 &&
              deletion.stages.front().rejected == (runtime.completion()==DeltaCompletion::ordered_replay?0:1),
          "ancestor/child deletion did not assign one owner and reject its duplicate candidate");
  }
  {
    DeltaOptions options;
    options.mode = DeltaMode::maintenance;
    auto runtime = make_runtime(deep_chain_plan(), options);
    Database database{{Relation{{n(1), n(1)}}, Relation{{n(1), n(10)}},
                       Relation{{n(10), n(100)}, {n(20), n(100)}}}};
    seed_maintenance(runtime, database, "deep chain seed");
    const auto below_root = apply_checked(runtime, database,
        {runtime.sequence() + 1, TableId{1}, SetOperation::insert, {n(1), n(20)}},
        "unchanged-root deeper liveness", true);
    check(record_set(below_root.records) ==
              std::set<SignedKey>{{SetOperation::insert,
                                   {n(1), n(1), n(20)}}},
          "deep liveness change missed its completion");
    const auto live = runtime.live_snapshot();
    check(live && live->factors.back().contains({n(20)}),
          "deep child key did not become globally live under unchanged root E");
  }
  {
    auto runtime = make_runtime(root_child_plan());
    Database database{{Relation{}, Relation{}}};
    const auto dead = apply_checked(runtime, database,
        {1, TableId{1}, SetOperation::insert, {n(3), n(30)}},
        "unlive child E insertion");
    check(dead.records.empty(), "unlive child key emitted a result");
    check(dead.stages.size() == 1 && dead.metrics.dead_witnesses > 0 &&
              dead.metrics.candidates == 0,
          "unlive child E change was not accounted as a dead witness");
    const auto live = runtime.live_snapshot();
    check(live && std::all_of(live->factors.begin(), live->factors.end(),
                              [](const Relation& factor) { return factor.empty(); }),
          "unmatched child E row entered a global live set");
    const auto activation = apply_checked(runtime, database,
        {2, TableId{0}, SetOperation::insert, {n(3)}},
        "root activation of existing child E", true);
    check(record_set(activation.records) ==
              std::set<SignedKey>{{SetOperation::insert, {n(3), n(30)}}},
          "root activation failed to enumerate an existing child E key");
  }
  {
    DeltaOptions options;
    options.mode = DeltaMode::maintenance;
    auto runtime = make_runtime(shared_separator_plan(), options);
    Database database{{Relation{{n(1), n(7)}, {n(2), n(7)}},
                       Relation{{n(7), n(9)}}}};
    seed_maintenance(runtime, database, "shared separator seed");
    const auto removed = apply_checked(runtime, database,
        {runtime.sequence() + 1, TableId{0}, SetOperation::erase, {n(1), n(7)}},
        "shared separator surviving parent support");
    check(record_set(removed.records) ==
              std::set<SignedKey>{{SetOperation::erase,
                                   {n(1), n(7), n(9)}}},
          "removing one parent erased another parent's shared child completion");
    const auto live = runtime.live_snapshot();
    check(live && live->factors.size() == 2 &&
              live->factors[1].contains({n(7), n(9)}),
          "shared separator child key died while a matching parent remained");
  }
}

void products_alias_prefixes_and_self_join() {
  for (const std::size_t arity : {std::size_t{3}, std::size_t{8}}) {
    auto runtime = make_runtime(product_plan(arity));
    Database database;
    database.tables.resize(arity);
    for (std::size_t table = 0; table + 1 < arity; ++table) {
      const auto first = static_cast<std::int64_t>(table * 10 + 1);
      const auto second = static_cast<std::int64_t>(table * 10 + 2);
      static_cast<void>(apply_checked(runtime, database,
          {runtime.sequence() + 1, TableId{table}, SetOperation::insert, {n(first)}},
          "product factor first row"));
      static_cast<void>(apply_checked(runtime, database,
          {runtime.sequence() + 1, TableId{table}, SetOperation::insert, {n(second)}},
          "product factor second row"));
    }
    static_cast<void>(apply_checked(runtime, database,
        {runtime.sequence() + 1, TableId{arity - 1}, SetOperation::insert,
         {n(static_cast<std::int64_t>(arity * 10 + 1))}}, "product last first row"));
    const auto last = apply_checked(runtime, database,
        {runtime.sequence() + 1, TableId{arity - 1}, SetOperation::insert,
         {n(static_cast<std::int64_t>(arity * 10 + 2))}},
        "generalized " + std::to_string(arity) + "-child product", arity == 3);
    std::size_t expected = 1;
    for (std::size_t i = 1; i < arity; ++i) expected *= 2;
    check(last.records.size() == expected,
          "generalized product omitted or duplicated a sibling combination");
  }

  {
    DeltaOptions options;
    options.mode = DeltaMode::maintenance;
    auto runtime = make_runtime(same_scope_alias_plan(), options);
    Database database{{Relation{Row{n(1), n(10)}}}};
    seed_maintenance(runtime, database, "same-scope alias seed");
    const auto same_scope = apply_checked(runtime, database,
        {runtime.sequence() + 1, TableId{0}, SetOperation::insert, {n(2), n(20)}},
        "same-scope alias route partition", true);
    check(same_scope.records.size() == 1,
          "two same-scope aliases duplicated one physical output");
    check(same_scope.stages.size() == 2 &&
              same_scope.stages[0].occurrence == OccurrenceId{0} &&
              same_scope.stages[0].output_count == 0 &&
              same_scope.stages[1].occurrence == OccurrenceId{1} &&
              same_scope.stages[1].output_count == 1,
          "same-scope aliases did not emit at the completing prefix exactly once");
  }

  {
    DeltaOptions options;
    options.mode = DeltaMode::maintenance;
    auto runtime = make_runtime(self_join_plan(), options);
    Database database{{Relation{{n(1), n(2), s("a")},
                                {n(2), n(1), s("a")}}}};
    seed_maintenance(runtime, database, "self-join seed");
    const auto insertion = apply_checked(runtime, database,
        {runtime.sequence() + 1, TableId{0}, SetOperation::insert,
         {n(1), n(1), s("loop")}},
        "self-join new-new insertion", true);
    check(record_set(insertion.records) == std::set<SignedKey>{
              {SetOperation::insert, {n(1), n(1), n(1)}},
              {SetOperation::insert, {n(1), n(1), n(2)}},
              {SetOperation::insert, {n(2), n(1), n(1)}}},
          "self-join loop did not emit all three exact prefix-owned answers");
    check(insertion.stages.size() == 2 &&
              insertion.stages[0].occurrence == OccurrenceId{0} &&
              insertion.stages[0].output_count == 1 &&
              insertion.stages[1].occurrence == OccurrenceId{1} &&
              insertion.stages[1].output_count == 2 &&
              insertion.derivations.size() == 2,
          "self-join insert did not expose its one-plus-two route prefix trace");
    const auto erase = apply_checked(runtime, database,
        {runtime.sequence() + 1, TableId{0}, SetOperation::erase,
         {n(1), n(1), s("loop")}},
        "self-join new-new deletion", true);
    check(record_set(erase.records) == std::set<SignedKey>{
              {SetOperation::erase, {n(1), n(1), n(1)}},
              {SetOperation::erase, {n(1), n(1), n(2)}},
              {SetOperation::erase, {n(2), n(1), n(1)}}},
          "self-join loop deletion did not retract the exact endpoint difference");
    check(erase.stages.size() == 2 && erase.stages[0].output_count == 2 &&
              erase.stages[1].output_count == 1,
          "self-join deletion did not expose its two-plus-one route prefix trace");
  }
}

void sql_mapping_predicates_and_exists() {
  {
    const Catalog catalog{1,
        {{"lefts", {{"x", ScalarType::int64}, {"witness", ScalarType::string}}},
         {"rights", {{"x", ScalarType::int64}, {"witness", ScalarType::string}}}}};
    auto runtime = make_runtime(sql_plan(
        "SELECT DISTINCT r.x, l.x, r.x AS again, 7 AS fixed FROM lefts l, rights r",
        catalog));
    Database database;
    database.tables.resize(2);
    static_cast<void>(apply_checked(runtime, database,
        {1, TableId{0}, SetOperation::insert, {n(1), s("left-a")}},
        "mapped SQL left input"));
    static_cast<void>(apply_checked(runtime, database,
        {2, TableId{1}, SetOperation::insert, {n(10), s("right-a")}},
        "mapped SQL reordered repeated constant output", true));
    const auto output = a04_output(runtime.plan(), database);
    check(output.contains({n(10), n(1), n(10), n(7)}),
          "SQL mapped result lost repeated, reordered or constant head fields");
    static_cast<void>(apply_checked(runtime, database,
        {3, TableId{0}, SetOperation::insert, {n(2), s("left-b")}},
        "mapped SQL product extension", true));
  }

  {
    const Catalog catalog{1,
        {{"r", {{"x", ScalarType::int64}, {"flag", ScalarType::int64}}}}};
    auto runtime = make_runtime(sql_plan(
        "SELECT DISTINCT a.x FROM r a JOIN r b ON a.x=b.x WHERE a.flag=1",
        catalog));
    Database database{std::vector<Relation>(1)};
    static_cast<void>(apply_checked(runtime, database,
        {1, TableId{0}, SetOperation::insert, {n(1), n(1)}},
        "predicate aliases initial answer"));
    const auto filtered = apply_checked(runtime, database,
        {2, TableId{0}, SetOperation::insert, {n(2), n(0)}},
        "different predicate alias filtered route");
    check(filtered.records.empty(), "filtered SQL alias emitted output");
    check(filtered.physical_metrics.aliases_filtered == 1 &&
              filtered.derivations.size() == 1 && filtered.stages.size() == 1 &&
              filtered.stages.front().occurrence == OccurrenceId{1} &&
              filtered.stages.front().prefix == 2 &&
              filtered.stages.front().output_count == 0,
          "different-predicate aliases lost the filtered route ordinal/dead distinction");
    static_cast<void>(apply_checked(runtime, database,
        {3, TableId{0}, SetOperation::insert, {n(2), n(1)}},
        "filtered then live alias route", true));
  }

  {
    const Catalog catalog{1, {{"r", {{"x", ScalarType::int64}}}}};
    auto runtime = make_runtime(sql_plan("SELECT EXISTS(SELECT NULL FROM r)", catalog));
    Database database{std::vector<Relation>(1)};
    const auto made_true = apply_checked(runtime, database,
        {1, TableId{0}, SetOperation::insert, {n(1)}},
        "EXISTS false to true replacement", true);
    check(record_set(made_true.records) == std::set<SignedKey>{
              {SetOperation::erase, {Value{false}}},
              {SetOperation::insert, {Value{true}}}},
          "EXISTS false-to-true replacement omitted one signed Boolean row");
    check(made_true.stages.size() == 1 &&
              made_true.stages.front().output_count == 0,
          "EXISTS replacement records were attached to a per-route stage");
    const auto second = apply_checked(runtime, database,
        {2, TableId{0}, SetOperation::insert, {n(2)}},
        "EXISTS positive count only");
    check(second.records.empty(), "second EXISTS witness repeated truth output");
    static_cast<void>(apply_checked(runtime, database,
        {3, TableId{0}, SetOperation::erase, {n(1)}},
        "EXISTS nonlast witness delete"));
    const auto made_false = apply_checked(runtime, database,
        {4, TableId{0}, SetOperation::erase, {n(2)}},
        "EXISTS true to false replacement", true);
    check(record_set(made_false.records) == std::set<SignedKey>{
              {SetOperation::erase, {Value{true}}},
              {SetOperation::insert, {Value{false}}}},
          "EXISTS true-to-false replacement omitted one signed Boolean row");
  }

  {
    const Catalog catalog{1, {{"r", {{"x", ScalarType::int64}}}}};
    const std::vector<std::pair<std::string, Relation>> constant_sql{
        {"SELECT DISTINCT 7 AS fixed", Relation{{n(7)}}},
        {"SELECT DISTINCT 7 AS fixed FROM r WHERE 1=0", Relation{}}};
    for (const auto& [sql, expected] : constant_sql) {
      auto runtime = make_runtime(sql_plan(sql, catalog));
      Database database{std::vector<Relation>(1)};
      check(a04_output(runtime.plan(), database) == expected,
            "normalized constant SQL A04 setup differs");
      const auto inserted = apply_checked(runtime, database,
          {1, TableId{0}, SetOperation::insert, {n(99)}},
          "normalized constant SQL insert");
      const auto erased = apply_checked(runtime, database,
          {2, TableId{0}, SetOperation::erase, {n(99)}},
          "normalized constant SQL erase");
      check(inserted.records.empty() && erased.records.empty() &&
                inserted.stages.empty() && erased.stages.empty(),
            "normalized constant SQL route emitted an input delta");
    }
  }

  {
    const Catalog catalog{1, {{"unused", {{"x", ScalarType::int64}}}}};
    for (const bool contradiction : {false, true}) {
      const Query query{{}, {}, {}, contradiction};
      const FreeConnexTree tree{};
      auto runtime = make_runtime(s04_runtime::lower_tree(catalog, query, tree));
      Database database{std::vector<Relation>(1)};
      const auto initial = a04_output(runtime.plan(), database);
      check(initial == (contradiction ? Relation{} : Relation{Row{}}),
            "source-free constant A04 setup differs");
      const auto insert = apply_checked(runtime, database,
          {1, TableId{0}, SetOperation::insert, {n(1)}},
          "source-free constant insert");
      const auto erase = apply_checked(runtime, database,
          {2, TableId{0}, SetOperation::erase, {n(1)}},
          "source-free constant erase");
      check(insert.records.empty() && erase.records.empty(),
            "source-free constant route emitted an input delta");
    }
  }
}

void seeded_updates_and_modes_discard_readiness() {
  for (const std::uint64_t seed : {std::uint64_t{7}, std::uint64_t{91}}) {
    auto runtime = make_runtime(self_join_plan());
    Database database{std::vector<Relation>(1)};
    std::uint64_t random = seed;
    std::uint64_t sequence = 0;
    for (std::size_t step = 0; step < 72; ++step) {
      random = random * 6364136223846793005ULL + 1442695040888963407ULL;
      const auto x = static_cast<std::int64_t>((random >> 8) % 3U);
      const auto y = static_cast<std::int64_t>((random >> 16) % 3U);
      const auto payload = ((random >> 24) % 2U) == 0 ? "a" : "b";
      const auto operation = ((random >> 32) % 2U) == 0
          ? SetOperation::insert : SetOperation::erase;
      static_cast<void>(apply_checked(runtime, database,
          {++sequence, TableId{0}, operation, {n(x), n(y), s(payload)}},
          "seeded alias update"));
    }
  }

  {
    auto runtime = make_runtime(root_pair_plan());
    Database database{std::vector<Relation>(1)};
    auto empty_epoch = runtime.apply(
        {1, TableId{0}, SetOperation::erase, {n(9), n(9)}});
    check(empty_epoch.remaining() == 0 && !empty_epoch.active() && runtime.ready(),
          "empty delta epoch retained an output or writer lease");
    static_cast<void>(apply_checked(runtime, database,
        {2, TableId{0}, SetOperation::insert, {n(1), n(2)}},
        "input immediately after empty epoch"));
    check(!empty_epoch.next(),
          "empty epoch handle returned output after a later input committed");
  }

  {
    DeltaOptions options;
    options.mode = DeltaMode::maintenance;
    auto runtime = make_runtime(root_child_plan(), options);
    Database database{{Relation{}, Relation{}}};
    check(!runtime.live_snapshot(), "maintenance mode bootstrapped a delta cache");
    auto maintenance_child = runtime.apply(
        {1, TableId{1}, SetOperation::insert, {n(3), n(30)}});
    check(maintenance_child.remaining() == 0 && runtime.ready(),
          "maintenance child load unexpectedly published a delta result");
    database.tables[1].insert({n(3), n(30)});
    auto maintenance_root = runtime.apply(
        {2, TableId{0}, SetOperation::insert, {n(3)}});
    check(maintenance_root.remaining() == 0 && runtime.ready(),
          "maintenance root load unexpectedly published a delta result");
    database.tables[0].insert({n(3)});
    check(runtime.has_answer() && !runtime.live_snapshot(),
          "maintenance update exposed stale L or wrong query truth");
    check(runtime.snapshot().physical.tables == database.tables,
          "maintenance load physical state differs from A04 fixture");
    const auto bootstrap = runtime.set_mode(DeltaMode::delta);
    check(bootstrap.e_rows_scanned > 0 && runtime.mode() == DeltaMode::delta,
          "delta-mode rebootstrap did not scan current E factors");
    check_live(runtime, database, "maintenance to delta rebootstrap");

    const auto removed_root = apply_checked(runtime, database,
        {3, TableId{0}, SetOperation::erase, {n(3)}},
        "post-rebootstrap delta event");
    check(removed_root.records.size() == 1,
          "rebootstrapped delta mode missed its first exact output");
    static_cast<void>(runtime.set_mode(DeltaMode::maintenance));
    check(!runtime.live_snapshot(), "switching to maintenance retained L");
    const auto maintenance_delete = runtime.apply(
        {4, TableId{1}, SetOperation::erase, {n(3), n(30)}});
    check(maintenance_delete.remaining() == 0 && runtime.ready(),
          "maintenance deletion retained output ownership");
    database.tables[1].erase({n(3), n(30)});
    static_cast<void>(runtime.set_mode(DeltaMode::delta));
    check_live(runtime, database, "second delta-mode rebootstrap");
  }

  {
    auto runtime = make_runtime(root_pair_plan());
    Database database{std::vector<Relation>(1)};
    auto discarded = runtime.apply(
        {1, TableId{0}, SetOperation::insert, {n(4), n(5)}});
    check(!runtime.ready() && discarded.remaining() == 1,
          "pending output did not hold the writer barrier");
    expect_error([&] { static_cast<void>(runtime.set_mode(DeltaMode::maintenance)); },
                 "runtime_busy");
    discarded.discard();
    database.tables[0].insert({n(4), n(5)});
    check(runtime.ready() && runtime.sequence() == 1,
          "discard rolled back committed input or retained the output lease");
    check_live(runtime, database, "discarded output committed L");
    const auto next = apply_checked(runtime, database,
        {2, TableId{0}, SetOperation::erase, {n(4), n(5)}},
        "event after discarded output", true);
    check(record_set(next.records) ==
              std::set<SignedKey>{{SetOperation::erase,
                                   {n(4), n(5)}}},
          "next event after discard did not use the committed input state");
  }

  {
    auto runtime = make_runtime(root_pair_plan());
    Database database{{Relation{}}};
    static_cast<void>(apply_checked(runtime, database,
        {1, TableId{0}, SetOperation::insert, {n(1), n(2)}},
        "reader barrier first result"));
    static_cast<void>(apply_checked(runtime, database,
        {2, TableId{0}, SetOperation::insert, {n(3), n(4)}},
        "reader barrier second result"));
    auto reader = runtime.results();
    check(reader.next().has_value() && reader.active(),
          "result reader did not retain an active snapshot lease");
    expect_error([&] {
      static_cast<void>(runtime.apply(
          {3, TableId{0}, SetOperation::insert, {n(5), n(6)}}));
    }, "runtime_busy");
    reader.cancel();
    static_cast<void>(apply_checked(runtime, database,
        {3, TableId{0}, SetOperation::insert, {n(5), n(6)}},
        "event after result reader closes"));
  }
}

}  // namespace

int main(int argc,char** argv) {
  try {
    if (argc==2 && std::string_view(argv[1])=="eager") selected_policy=LiveMaintenance::eager;
    else if (argc==2 && std::string_view(argv[1])=="incremental") selected_policy=LiveMaintenance::incremental;
    else if (argc==2 && std::string_view(argv[1])=="root_first") selected_completion=DeltaCompletion::root_first;
    else if (argc==2 && std::string_view(argv[1])=="anchored") selected_completion=DeltaCompletion::anchored;
    else check(argc==1,"expected no argument, eager, incremental, anchored or root_first policy");
    std::cout<<"live_policy="<<(selected_policy==LiveMaintenance::eager?"eager":
        selected_policy==LiveMaintenance::on_output?"on_output":"incremental")<<'\n';
    std::cout<<"completion_request="<<(selected_completion==DeltaCompletion::automatic?"automatic":
        selected_completion==DeltaCompletion::anchored?"anchored":
        selected_completion==DeltaCompletion::ordered_replay?"ordered_replay":"root_first")<<'\n';
    projection_collisions_noops_and_count_only();
    root_ancestor_deep_and_global_liveness();
    products_alias_prefixes_and_self_join();
    sql_mapping_predicates_and_exists();
    seeded_updates_and_modes_discard_readiness();
    exhaustive_binary_domain_toggles();
#ifdef CROWN_STATISTICS_ACCEPTANCE
    statistics_acceptance::print();
#endif
    std::cout << "D04 DeltaRuntime acceptance passed updates=" << checked_updates
              << " emitted=" << checked_records
              << " exhaustive_toggles=" << checked_exhaustive_transitions << '\n';
  } catch (const std::exception& failure) {
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
