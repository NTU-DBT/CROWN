#include "crown/api/error.hpp"
#include "crown/frontend/bind.hpp"
#include "crown/frontend/normalize.hpp"
#include "crown/io/cursor_observation.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/delta.hpp"
#include "crown/runtime/observation.hpp"
#include "crown/runtime/physical.hpp"
#include "crown/runtime/session.hpp"
#include "crown/runtime/support.hpp"
#include "evaluator.hpp"

#include <algorithm>
#include <array>
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <initializer_list>
#include <iterator>
#include <limits>
#include <memory>
#include <new>
#include <optional>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

namespace allocation_probe {
constexpr std::size_t disabled = std::numeric_limits<std::size_t>::max();
std::atomic<bool> armed{false};
std::atomic<std::size_t> calls{0};
std::atomic<std::size_t> fail_at{disabled};

void note() {
  if (!armed.load(std::memory_order_relaxed)) return;
  const auto index = calls.fetch_add(1, std::memory_order_relaxed);
  if (index >= fail_at.load(std::memory_order_relaxed)) throw std::bad_alloc{};
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

void arm(std::size_t threshold) noexcept {
  calls.store(0, std::memory_order_relaxed);
  fail_at.store(threshold, std::memory_order_relaxed);
  armed.store(true, std::memory_order_relaxed);
}

void disarm() noexcept {
  armed.store(false, std::memory_order_relaxed);
  fail_at.store(disabled, std::memory_order_relaxed);
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

static_assert(std::is_nothrow_copy_constructible_v<ObservationConfiguration>);
static_assert(std::is_nothrow_copy_constructible_v<ObservationSnapshot>);
static_assert(std::is_nothrow_copy_constructible_v<ObservationSummary>);
static_assert(!std::is_trivially_copyable_v<ObservationSnapshot>);
static_assert(!std::is_trivially_copyable_v<ObservationSummary>);
static_assert(std::is_nothrow_copy_constructible_v<CursorObservation>);
static_assert(std::is_nothrow_move_constructible_v<SupportRuntime::ResultCursor>);
static_assert(std::is_nothrow_move_assignable_v<SupportRuntime::ResultCursor>);

std::uint64_t checks = 0;
std::uint64_t fake_clock_calls = 0;
std::uint64_t fake_clock_value = 0;
std::array<std::uint64_t, 8> scripted_clock{};
std::size_t scripted_clock_count = 0;
std::size_t scripted_clock_position = 0;

std::uint64_t fake_clock() noexcept {
  ++fake_clock_calls;
  if (scripted_clock_position < scripted_clock_count)
    return scripted_clock[scripted_clock_position++];
  fake_clock_value += 10;
  return fake_clock_value;
}

void reset_clock(std::uint64_t first = 100) noexcept {
  fake_clock_calls = 0;
  fake_clock_value = first;
  scripted_clock_count = 0;
  scripted_clock_position = 0;
  detail::set_observation_clock_for_testing(fake_clock);
}

void script_clock(std::initializer_list<std::uint64_t> values) noexcept {
  fake_clock_calls = 0;
  scripted_clock_position = 0;
  scripted_clock_count = std::min(values.size(), scripted_clock.size());
  std::copy_n(values.begin(), scripted_clock_count, scripted_clock.begin());
  fake_clock_value = scripted_clock_count == 0 ? 0 : scripted_clock[scripted_clock_count - 1];
  detail::set_observation_clock_for_testing(fake_clock);
}

void clear_clock() noexcept {
  detail::set_observation_clock_for_testing(nullptr);
  fake_clock_calls = 0;
  scripted_clock_count = 0;
  scripted_clock_position = 0;
}

void group_complete(std::string_view label) {
  allocation_probe::disarm();
  clear_clock();
  detail::set_observation_initial_generation_for_testing(0);
  std::cerr << "PASS group: " << label << '\n';
}

void check(bool condition, std::string_view message) {
  ++checks;
  if (!condition) throw std::runtime_error(std::string(message));
}

template <class Action>
void expect_error(std::string_view code, Action&& action, std::string_view label) {
  ++checks;
  try {
    std::forward<Action>(action)();
  } catch (const Error& error) {
    if (error.code() == code) return;
    throw std::runtime_error(std::string(label) + ": expected " + std::string(code) +
                             ", got " + error.code());
  }
  throw std::runtime_error(std::string(label) + ": missing error " + std::string(code));
}

void self_move(SupportRuntime::ResultCursor& cursor) {
  auto* same_object = &cursor;
  cursor = std::move(*same_object);
}

Value integer(std::int64_t value) { return Value{value}; }
Row int_row(std::int64_t value) { return Row{integer(value)}; }
Row edge(std::int64_t left, std::int64_t right) {
  return Row{integer(left), integer(right)};
}

struct ReportCollection {
  std::vector<std::pair<std::string, std::string>> cursors;
  std::vector<std::pair<std::string, std::string>> gauges;

  void cursor(std::string label, const CursorObservation& report) {
    constexpr std::size_t ceiling = 16 * 1024 * 1024;
    const auto json = io::write_cursor_observation_json(report, ceiling);
    check(!json.empty(), "cursor exporter returned an empty document");
    check(io::write_cursor_observation_json(report, json.size()) == json,
          "cursor exporter rejected its exact encoded-byte ceiling");
    expect_error("resource_limit", [&] {
      static_cast<void>(io::write_cursor_observation_json(report, json.size() - 1));
    }, "cursor exporter N-1 byte ceiling");
    cursors.emplace_back(std::move(label), json);
  }

  void gauge(std::string label, const CommittedStateGauges& value) {
    constexpr std::size_t ceiling = 16 * 1024 * 1024;
    const auto json = io::write_committed_state_gauges_json(value, ceiling);
    check(!json.empty(), "gauge exporter returned an empty document");
    check(io::write_committed_state_gauges_json(value, json.size()) == json,
          "gauge exporter rejected its exact encoded-byte ceiling");
    expect_error("resource_limit", [&] {
      static_cast<void>(io::write_committed_state_gauges_json(value, json.size() - 1));
    }, "gauge exporter N-1 byte ceiling");
    gauges.emplace_back(std::move(label), json);
  }
};

Relation drain(SupportRuntime::ResultCursor& cursor) {
  Relation rows;
  while (auto row = cursor.next()) {
    check(row->layout().same_token(cursor.layout()),
          "cursor output did not retain the cursor layout token");
    check(rows.insert(row->values()).second, "cursor emitted a duplicate set row");
  }
  check(cursor.state() == ResultCursorState::exhausted && !cursor.active(),
        "cursor did not release its lease on exhaustion");
  check(!cursor.next(), "repeated next on an exhausted cursor did not return nullopt");
  return rows;
}

PhysicalPlan unary_plan() {
  const Catalog catalog{1, {{"r", {{"x", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}},
                    {{"r", TableId{0}, {VariableId{0}}}},
                    {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan projected_many_to_one_plan() {
  const Catalog catalog{1, {{"r", {{"x", ScalarType::int64},
                                     {"w", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"w", ScalarType::int64}},
                    {{"r", TableId{0}, {VariableId{0}, VariableId{1}}}},
                    {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan unary_with_ignored_text_plan() {
  const Catalog catalog{1, {{"r", {{"x", ScalarType::int64},
                                     {"payload", ScalarType::string}}}}};
  const Query query{{{"x", ScalarType::int64}},
                    {{"r", TableId{0}, {VariableId{0}, IgnoredColumn{}}}},
                    {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan nullary_plan() {
  const Catalog catalog{1, {{"flags", {{"tag", ScalarType::string}}}}};
  const Query query{{}, {{"flags", TableId{0}, {IgnoredColumn{}}}}, {}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"flags", NodeKind::native, {}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan constant_plan(bool contradiction) {
  const Catalog catalog{1, {}};
  const Query query{{}, {}, {}, contradiction};
  return planner::lower_tree(catalog, query, FreeConnexTree{});
}

PhysicalPlan disconnected_product_plan(std::size_t arity) {
  check(arity == 3 || arity == 8, "product fixture arity is outside the literal test set");
  Catalog catalog;
  catalog.version = 1;
  Query query;
  FreeConnexTree tree;
  tree.root = NodeId{0};
  std::vector<NodeId> children;
  for (std::size_t i = 0; i < arity; ++i) {
    const auto table_name = "t" + std::to_string(i);
    const auto variable_name = "v" + std::to_string(i);
    catalog.tables.push_back({table_name, {{"value", ScalarType::int64}}});
    query.variables.push_back({variable_name, ScalarType::int64});
    query.atoms.push_back({table_name, TableId{i}, {VariableId{i}}});
    query.head.push_back({VariableId{i}, variable_name});
    children.push_back(NodeId{i + 1});
  }
  tree.nodes.push_back({"product", NodeKind::generalized, {}, children, {}, {}});
  for (std::size_t i = 0; i < arity; ++i)
    tree.nodes.push_back({"t" + std::to_string(i), NodeKind::native,
        {VariableId{i}}, {}, i, {}});
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan joined_visible_factor_plan() {
  const Catalog catalog{1,
      {{"a", {{"x", ScalarType::int64}}},
       {"b", {{"x", ScalarType::int64}, {"z", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"z", ScalarType::int64}},
      {{"a", TableId{0}, {VariableId{0}}},
       {"b", TableId{1}, {VariableId{0}, VariableId{1}}}},
      {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"a", NodeKind::native, {VariableId{0}}, {NodeId{1}}, 0, {}},
       {"b", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan aliased_generalized_plan() {
  const Catalog catalog{1,
      {{"r", {{"a", ScalarType::int64}, {"b", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64},
                     {"z", ScalarType::int64}},
      {{"r_left", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"r_right", TableId{0}, {VariableId{1}, VariableId{2}}}},
      {{VariableId{0}, "x"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"r_left", NodeKind::native, {VariableId{0}, VariableId{1}},
          {NodeId{1}}, 0, {}},
       {"r_right", NodeKind::native, {VariableId{1}, VariableId{2}},
          {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

PhysicalPlan three_factor_y_head_plan() {
  const Catalog catalog{1,
      {{"r", {{"x", ScalarType::int64}, {"y", ScalarType::int64}}},
       {"s", {{"y", ScalarType::int64}, {"z", ScalarType::int64}}}}};
  const Query query{{{"x", ScalarType::int64}, {"y", ScalarType::int64},
                     {"z", ScalarType::int64}},
      {{"r", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"s", TableId{1}, {VariableId{1}, VariableId{2}}}},
      {{VariableId{1}, "y"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"g", NodeKind::generalized, {VariableId{1}},
          {NodeId{1}, NodeId{2}}, {}, {}},
       {"r", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}},
       {"s", NodeKind::native, {VariableId{1}, VariableId{2}}, {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

std::optional<VariableId> term_variable(const Term& term) {
  if (const auto* variable = std::get_if<VariableId>(&term)) return *variable;
  return {};
}

FreeConnexTree sql_tree(const Query& query) {
  FreeConnexTree tree;
  if (query.contradiction || query.atoms.empty()) return tree;
  std::vector<VariableSet> scopes(query.atoms.size());
  for (std::size_t i = 0; i < query.atoms.size(); ++i)
    for (const auto& term : query.atoms[i].terms)
      if (const auto variable = term_variable(term)) scopes[i].insert(*variable);
  if (query.atoms.size() == 1) {
    tree.root = NodeId{0};
    tree.nodes.push_back({query.atoms[0].occurrence, NodeKind::native,
        scopes[0], {}, 0, {}});
    return tree;
  }
  VariableSet common = scopes.front();
  for (std::size_t i = 1; i < scopes.size(); ++i) {
    VariableSet overlap;
    std::set_intersection(common.begin(), common.end(), scopes[i].begin(), scopes[i].end(),
        std::inserter(overlap, overlap.end()));
    common = std::move(overlap);
  }
  std::vector<NodeId> children;
  for (std::size_t i = 0; i < query.atoms.size(); ++i) children.push_back(NodeId{i + 1});
  tree.root = NodeId{0};
  tree.nodes.push_back({"sql_product", NodeKind::generalized, common, children, {}, {}});
  for (std::size_t i = 0; i < query.atoms.size(); ++i)
    tree.nodes.push_back({query.atoms[i].occurrence, NodeKind::native, scopes[i], {}, i, {}});
  return tree;
}

PhysicalPlan exists_sql_plan(const Catalog& catalog) {
  const auto bound = frontend::bind_sql("SELECT EXISTS(SELECT NULL FROM r)", catalog);
  if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&bound))
    throw std::runtime_error(failure->diagnostic.code + ": " + failure->diagnostic.message);
  auto normalized = frontend::normalize_sql(std::get<frontend::BoundSql>(bound));
  if (const auto* failure = std::get_if<frontend::BindingDiagnostic>(&normalized))
    throw std::runtime_error(failure->diagnostic.code + ": " + failure->diagnostic.message);
  auto program = std::get<frontend::NormalizedSql>(std::move(normalized));
  auto tree = sql_tree(program.core);
  return planner::lower_normalized(program, tree);
}

Relation normalized_core_reference(const PhysicalPlan& plan, const Database& physical) {
  const auto& program = *plan.normalized();
  Database logical;
  logical.tables.resize(program.core_catalog.tables.size());
  for (std::size_t i = 0; i < program.adapters.size(); ++i) {
    const auto& adapter = program.adapters[i];
    const auto occurrence = adapter.occurrence.value;
    const auto target = program.core.atoms.at(occurrence).table.value;
    for (const auto& row : physical.tables.at(adapter.base.value))
      if (auto mapped = frontend::adapt_row(program, adapter.occurrence, row))
        logical.tables.at(target).insert(std::move(*mapped));
  }
  return reference::evaluate(program.core_catalog, program.core, logical);
}

void apply(PhysicalRuntime& runtime, Database& database, std::uint64_t& sequence,
           TableId table, SetOperation operation, Row values) {
  ++sequence;
  const auto result = runtime.apply({sequence, table, operation, values});
  check(result.input.physical_changed ==
        (operation == SetOperation::insert ? !database.tables.at(table.value).contains(values)
                                           : database.tables.at(table.value).contains(values)),
        "physical set event changed flag differs from independent set state");
  if (operation == SetOperation::insert) database.tables.at(table.value).insert(std::move(values));
  else database.tables.at(table.value).erase(values);
}

bool same_work(const CursorWork& a, const CursorWork& b) {
  return std::tie(a.work, a.calls, a.route_checks, a.descriptor_steps,
                  a.frame_initializations, a.cursor_opens, a.cursor_advances,
                  a.frame_closes, a.tuple_lookups, a.selected_rows,
                  a.bucket_lookups, a.key_fields, a.equality_checks,
                  a.output_fields, a.rows_emitted, a.binding_checks,
                  a.binding_rejections, a.direct_lookups, a.overlay_rows,
                  a.fragment_steps, a.binding_values, a.witness_probes,
                  a.witness_rows, a.join_rejections) ==
         std::tie(b.work, b.calls, b.route_checks, b.descriptor_steps,
                  b.frame_initializations, b.cursor_opens, b.cursor_advances,
                  b.frame_closes, b.tuple_lookups, b.selected_rows,
                  b.bucket_lookups, b.key_fields, b.equality_checks,
                  b.output_fields, b.rows_emitted, b.binding_checks,
                  b.binding_rejections, b.direct_lookups, b.overlay_rows,
                  b.fragment_steps, b.binding_values, b.witness_probes,
                  b.witness_rows, b.join_rejections);
}

bool same_metrics(const ResultCursorMetrics& a, const ResultCursorMetrics& b) {
  return same_work(a.startup, b.startup) && same_work(a.results, b.results) &&
      same_work(a.termination, b.termination) && same_work(a.failed, b.failed) &&
      same_work(a.last, b.last) && a.total_work == b.total_work &&
      a.max_result_work == b.max_result_work && a.cleanup_frames == b.cleanup_frames;
}

bool same_lifecycle_values(const CursorObservation& a, const CursorObservation& b) {
  if (a.mandatory.total_work != b.mandatory.total_work ||
      a.mandatory.max_result_work != b.mandatory.max_result_work ||
      a.mandatory.cleanup_frames != b.mandatory.cleanup_frames ||
      a.mandatory.startup.work != b.mandatory.startup.work ||
      a.mandatory.results.work != b.mandatory.results.work ||
      a.mandatory.termination.work != b.mandatory.termination.work ||
      a.mandatory.failed.work != b.mandatory.failed.work ||
      a.mandatory.last.work != b.mandatory.last.work) return false;
  for (std::size_t i = 0; i < cursor_metric_count; ++i) {
    const auto& left = a.values[i];
    const auto& right = b.values[i];
    if (left.value != right.value || left.availability != right.availability ||
        left.saturated != right.saturated) return false;
  }
  return a.state == b.state && a.terminal_reason == b.terminal_reason &&
      a.cursor_id == b.cursor_id && a.owner == b.owner && a.sequence == b.sequence;
}

void check_registry() {
  constexpr std::array<std::string_view, cursor_metric_count> names{
      "cursor.startup_ns", "cursor.successful_next_ns", "cursor.exhausted_next_ns",
      "cursor.failed_next_ns", "cursor.cleanup_ns", "cursor.successful_calls",
      "cursor.exhausted_calls", "cursor.failed_calls", "cursor.cancel_calls",
      "cursor.cleanup_calls", "cursor.clock_reads", "cursor.clock_regressions"};
  const auto registry = cursor_observation_registry();
  check(registry.size() == names.size(), "cursor registry length differs from literal v1 set");
  for (std::size_t i = 0; i < registry.size(); ++i) {
    check(static_cast<std::size_t>(registry[i].id) == i,
          "cursor registry IDs are not contiguous in declared order");
    check(registry[i].name == names[i], "cursor registry name differs from literal v1 descriptor");
    check(!registry[i].unit.empty() && !registry[i].scope.empty(),
          "cursor registry omitted unit or accounting scope");
    const bool timing = i < 5;
    check(registry[i].kind == (timing ? MetricKind::timing : MetricKind::counter),
          "cursor registry kind differs from literal timing/counter partition");
  }
}

void compare_reference_and_scalar_routes(ReportCollection& reports) {
  {
    const auto plan = projected_many_to_one_plan();
    PhysicalRuntime runtime(plan);
    Database db;
    db.tables.resize(1);
    std::uint64_t sequence = 0;
    apply(runtime, db, sequence, TableId{0}, SetOperation::insert, edge(1, 10));
    apply(runtime, db, sequence, TableId{0}, SetOperation::insert, edge(1, 11));
    apply(runtime, db, sequence, TableId{0}, SetOperation::insert, edge(2, 20));
    const auto expected = reference::evaluate(plan.catalog(), plan.query(), db);
    check(expected == Relation{{integer(1)}, {integer(2)}},
          "independent A04 projection fixture changed its literal expectation");
    auto cursor = runtime.core_results();
    const auto actual = drain(cursor);
    check(actual == expected, "projected many-witness cursor differs from A04");
    const auto report = cursor.observation();
    reports.cursor("projected-many-to-one", report);
  }

  {
    for (const auto contradiction : {false, true}) {
      const auto plan = constant_plan(contradiction);
      PhysicalRuntime runtime(plan);
      Database db;
      const auto expected = reference::evaluate(plan.catalog(), plan.query(), db);
      check(expected == (contradiction ? Relation{} : Relation{{}}),
            "independent A04 constant route fixture changed its literal expectation");
      auto cursor = runtime.core_results();
      check(drain(cursor) == expected, "constant true/false cursor differs from A04");
      reports.cursor(contradiction ? "constant-false" : "constant-true", cursor.observation());
    }
  }

  {
    const auto plan = nullary_plan();
    PhysicalRuntime runtime(plan);
    Database db;
    db.tables.resize(1);
    const auto empty_expected = reference::evaluate(plan.catalog(), plan.query(), db);
    check(empty_expected.empty(), "empty nullary A04 fixture unexpectedly has a row");
    auto empty_cursor = runtime.core_results();
    check(drain(empty_cursor).empty(), "empty nullary cursor emitted the identity row");
    reports.cursor("nullary-empty", empty_cursor.observation());
    std::uint64_t sequence = 0;
    apply(runtime, db, sequence, TableId{0}, SetOperation::insert, Row{std::string{"flag"}});
    const auto full_expected = reference::evaluate(plan.catalog(), plan.query(), db);
    check(full_expected == Relation{{}}, "nonempty nullary A04 fixture changed its literal result");
    auto full_cursor = runtime.core_results();
    check(drain(full_cursor) == full_expected, "nonempty nullary cursor differs from A04");
    reports.cursor("nullary-present", full_cursor.observation());
  }

  {
    const Catalog catalog{4, {{"r", {{"x", ScalarType::int64}}}}};
    const auto plan = exists_sql_plan(catalog);
    PhysicalRuntime runtime(plan);
    Database db;
    db.tables.resize(1);
    std::uint64_t sequence = 0;
    for (const auto exists : {false, true}) {
      if (exists) apply(runtime, db, sequence, TableId{0},
                        SetOperation::insert, int_row(41));
      const auto core = normalized_core_reference(plan, db);
      const auto expected = frontend::map_sql_result(*plan.normalized(), core);
      check(expected == Relation{{Value{exists}}},
            "independent normalized A04/SQL mapper changed EXISTS truth");
      auto cursor = runtime.results();
      check(drain(cursor) == expected, "SQL Boolean cursor differs from independent A04 mapping");
      reports.cursor(exists ? "sql-exists-true" : "sql-exists-false", cursor.observation());
    }
  }
}

void product_reference_and_factor_gauges(ReportCollection& reports) {
  for (const auto arity : {std::size_t{3}, std::size_t{8}}) {
    const auto plan = disconnected_product_plan(arity);
    PhysicalRuntime runtime(plan);
    Database db;
    db.tables.resize(arity);
    std::uint64_t sequence = 0;
    for (std::size_t i = 0; i < arity; ++i) {
      apply(runtime, db, sequence, TableId{i}, SetOperation::insert,
            int_row(static_cast<std::int64_t>(i * 10 + 1)));
      apply(runtime, db, sequence, TableId{i}, SetOperation::insert,
            int_row(static_cast<std::int64_t>(i * 10 + 2)));
    }
    const auto expected = reference::evaluate(plan.catalog(), plan.query(), db);
    const auto expected_count = std::size_t{1} << arity;
    check(expected.size() == expected_count,
          "independent A04 product cardinality differs from literal 2^arity");
    auto cursor = runtime.core_results();
    check(drain(cursor) == expected, "3/8-child generalized product differs from A04");
    reports.cursor("generalized-product-" + std::to_string(arity), cursor.observation());
    const auto gauges = runtime.committed_state_gauges();
    check(gauges.base_tuples.availability == MetricAvailability::available &&
          gauges.base_tuples.value == static_cast<std::uint64_t>(arity * 2),
          "product base gauge did not count each physical table once");
    check(gauges.full_result_count.availability == MetricAvailability::unavailable,
          "product gauges claimed a full answer cardinality");
    check(gauges.nodes.size() == arity + 1,
          "product gauge node list does not match its physical tree");
    for (std::size_t i = 1; i < gauges.nodes.size(); ++i) {
      check(gauges.nodes[i].kind == NodeKind::native && gauges.nodes[i].records == 2 &&
            gauges.nodes[i].survivors == 2,
            "leaf factor gauge differs from independently inserted two-row relation");
      check(gauges.nodes[i].visible_factor_assignments.availability == MetricAvailability::available &&
            gauges.nodes[i].visible_factor_assignments.value == 2,
            "C* leaf gauge is not its local factor assignment count");
    }
    reports.gauge("generalized-product-" + std::to_string(arity), gauges);
  }

  const auto head_y_plan = three_factor_y_head_plan();
  DeltaOptions options;
  options.physical.support.observation.mode = ObservationMode::timed;
  DeltaRuntime runtime(head_y_plan, options);
  auto cursor = runtime.core_results();
  const auto config = cursor.observation().configuration;
  check(config.has_value() && config->query_factors() == 3,
        "G{y} with R(x,y),S(y,z), head y must bind three C* factors");
  cursor.cancel();
  reports.cursor("three-cstar-factors-head-y", cursor.observation());
}

void observation_mode_matrix(ReportCollection& reports) {
  const auto plan = unary_with_ignored_text_plan();
  Database db;
  db.tables.resize(1);
  db.tables[0].insert(Row{integer(7), std::string{"stable"}});
  const auto expected = reference::evaluate(plan.catalog(), plan.query(), db);
  check(expected == Relation{{integer(7)}}, "unary A04 mode-matrix fixture changed");

  std::optional<ResultCursorMetrics> baseline;
  for (const auto& [mode, trace_timings, label] : {
           std::tuple{ObservationMode::off, true, "off"},
           std::tuple{ObservationMode::counters, true, "counters"},
           std::tuple{ObservationMode::timed, true, "timed"},
           std::tuple{ObservationMode::trace, false, "trace-no-timing"},
           std::tuple{ObservationMode::trace, true, "trace-timing"}}) {
    reset_clock();
    PhysicalRuntimeOptions options;
    options.support.observation.mode = mode;
    options.support.observation.trace_timings = trace_timings;
    options.support.observation.sample_period = 17;
    options.support.observation.sample_offset = 16;
    PhysicalRuntime runtime(plan, options);
    static_cast<void>(runtime.apply({1, TableId{0}, SetOperation::insert,
                                     Row{integer(7), std::string{"stable"}}}));
    const auto calls_before_cursor = fake_clock_calls;
    auto cursor = runtime.results();
    const auto actual = drain(cursor);
    const auto report = cursor.observation();
    const auto metrics = cursor.metrics();
    const auto per_cursor_clock_reads = report.metric(CursorMetricId::clock_reads);
    if (mode == ObservationMode::off || mode == ObservationMode::counters ||
        (mode == ObservationMode::trace && !trace_timings)) {
      check(fake_clock_calls - calls_before_cursor == 0,
            "off/counters/trace-without-timings read the optional fake clock");
      check(report.metric(CursorMetricId::startup_ns).availability == MetricAvailability::disabled,
            "optional cursor times were not disabled in a no-clock mode");
    } else {
      check(fake_clock_calls - calls_before_cursor > 0 &&
            per_cursor_clock_reads.availability == MetricAvailability::available &&
            per_cursor_clock_reads.value == fake_clock_calls - calls_before_cursor,
            "timed cursor clock reads did not reconcile exactly");
    }
    check(actual == expected, "observation mode changed unary result rows");
    check(metrics.total_work > 0 && metrics.results.rows_emitted == expected.size(),
          "mandatory cursor work changed or disappeared under an observation mode");
    if (baseline) check(same_metrics(*baseline, metrics),
                        "mandatory cursor work differs across observation modes");
    else baseline = metrics;
    if (mode == ObservationMode::off) {
      check(!runtime.last_cursor_observation().has_value(),
            "off mode retained runtime cursor history");
      check(report.cursor_id == 0 && report.terminal_reason == CursorTerminalReason::not_recorded,
            "off cursor exposed a recorded identity or terminal reason");
    } else {
      const auto published = runtime.last_cursor_observation();
      check(published.has_value() && published->cursor_id == report.cursor_id,
            "enabled runtime did not publish its latest cursor lifecycle");
    }
    reports.cursor("mode-" + std::string(label), report);
  }
  clear_clock();
}

void epoch_cursor_sources_and_invalidation(ReportCollection& reports) {
  const auto plan = joined_visible_factor_plan();
  PhysicalRuntime runtime(plan);
  Database db;
  db.tables.resize(2);
  std::uint64_t sequence = 0;
  apply(runtime, db, sequence, TableId{0}, SetOperation::insert, int_row(1));
  apply(runtime, db, sequence, TableId{0}, SetOperation::insert, int_row(2));
  apply(runtime, db, sequence, TableId{1}, SetOperation::insert, edge(1, 10));
  apply(runtime, db, sequence, TableId{1}, SetOperation::insert, edge(1, 11));
  apply(runtime, db, sequence, TableId{1}, SetOperation::insert, edge(3, 30));
  const auto expected = reference::evaluate(plan.catalog(), plan.query(), db);
  check(expected == Relation{{integer(1)}}, "visible-factor A04 fixture changed its literal answer");
  const Query all_query{
      {{"x", ScalarType::int64}, {"z", ScalarType::int64}},
      {{"a", TableId{0}, {VariableId{0}}},
       {"b", TableId{1}, {VariableId{0}, VariableId{1}}}},
      {{VariableId{0}, "x"}, {VariableId{1}, "z"}}, false};
  const auto expected_witnesses = reference::evaluate(plan.catalog(), all_query, db);
  check(expected_witnesses == Relation{{integer(1), integer(10)},
                                       {integer(1), integer(11)}},
        "independent all-variable A04 fixture changed its literal witnesses");

  auto view = runtime.current_view();
  auto completions = view.completions({});
  check(drain(completions) == expected, "epoch completions differ from A04");
  auto completions_report = completions.observation();
  check(completions_report.source == CursorObservationSource::epoch_visible &&
        completions_report.side == SnapshotSide::after && !completions_report.tentative_at_creation,
        "committed completions cursor lost its source/side binding");
  reports.cursor("epoch-visible-committed", completions_report);

  auto witnesses = view.witnesses();
  check(drain(witnesses) == expected_witnesses,
        "epoch witnesses differ from full-assignment A04 reference");
  const auto witnesses_report = witnesses.observation();
  check(witnesses_report.source == CursorObservationSource::epoch_witnesses,
        "witness cursor lost its source identity");
  reports.cursor("epoch-witnesses-committed", witnesses_report);

  auto root_keys = view.visible_keys(NodeId{0});
  check(drain(root_keys) == Relation{{integer(1)}},
        "root visible-key factor differs from independently traced x values");
  const auto root_keys_report = root_keys.observation();
  check(root_keys_report.source == CursorObservationSource::epoch_keys,
        "visible-key cursor lost its source identity");
  reports.cursor("epoch-visible-root-keys", root_keys_report);

  auto child_keys = view.visible_keys(NodeId{1});
  const auto child_local_keys = Relation{{integer(1)}, {integer(3)}};
  check(drain(child_keys) == child_local_keys,
        "child visible-key scan omitted a local projected E key that is globally unlive");
  reports.cursor("epoch-visible-child-keys", child_keys.observation());

  auto bucket = view.visible_bucket(NodeId{1}, Row{integer(1)});
  const auto bucket_expected = Relation{{integer(1)}};
  check(drain(bucket) == bucket_expected,
        "visible bucket differs from independent separator selection");
  const auto bucket_report = bucket.observation();
  check(bucket_report.source == CursorObservationSource::epoch_bucket,
        "visible-bucket cursor lost its source identity");
  reports.cursor("epoch-visible-bucket", bucket_report);
  const auto visible_gauges = runtime.committed_state_gauges();
  check(visible_gauges.base_tuples.value == 5 && visible_gauges.nodes.size() == 2 &&
        visible_gauges.nodes[0].records == 2 && visible_gauges.nodes[0].survivors == 1 &&
        visible_gauges.nodes[0].projected_parent_keys == 1 &&
        visible_gauges.nodes[0].visible_factor_assignments.availability == MetricAvailability::available &&
        visible_gauges.nodes[0].visible_factor_assignments.value == 1 &&
        visible_gauges.nodes[1].records == 3 && visible_gauges.nodes[1].survivors == 3 &&
        visible_gauges.nodes[1].projected_parent_keys == 2 &&
        visible_gauges.nodes[1].visible_factor_assignments.availability == MetricAvailability::available &&
        visible_gauges.nodes[1].visible_factor_assignments.value == 2,
        "C* gauges do not distinguish local E keys from globally reachable output");
  check(visible_gauges.full_result_count.availability == MetricAvailability::unavailable,
        "per-node E-factor gauges were promoted into a full result count");
  reports.gauge("visible-factor-globally-unlive-key", visible_gauges);
  view.close();
  check(runtime.ready(), "closing the committed view did not release its read lease");

  const auto one_plan = unary_plan();
  PhysicalRuntime rollback_runtime(one_plan);
  auto pending = rollback_runtime.prepare({1, TableId{0}, SetOperation::insert, int_row(99)});
  auto tentative_view = pending.view(SnapshotSide::after);
  auto tentative_cursor = tentative_view.results();
  check(tentative_cursor.observation().tentative_at_creation &&
        tentative_cursor.observation().side == SnapshotSide::after,
        "pending view cursor lost tentative side at creation");
  check(tentative_cursor.next().has_value(), "tentative after cursor omitted staged row");
  pending.rollback();
  const auto invalidated = tentative_cursor.observation();
  check(tentative_cursor.state() == ResultCursorState::failed &&
        invalidated.terminal_reason == CursorTerminalReason::invalidated,
        "rollback did not invalidate and close its live view cursor");
  reports.cursor("tentative-invalidated-after-rollback", invalidated);
  tentative_view.close();
  check(rollback_runtime.ready(), "rollback invalidation retained a read lease");
}

void lifecycle_caps_and_failed_startup(ReportCollection& reports) {
  reset_clock();
  PhysicalRuntimeOptions timed_options;
  timed_options.support.observation.mode = ObservationMode::timed;
  PhysicalRuntime runtime(unary_plan(), timed_options);
  static_cast<void>(runtime.apply({1, TableId{0}, SetOperation::insert, int_row(5)}));

  check(!runtime.last_cursor_observation().has_value(),
        "runtime recorded a cursor before any cursor construction");
  SupportRuntime admission_guard(unary_plan(), timed_options.support);
  expect_error("invalid_cursor_options", [&] {
    static_cast<void>(admission_guard.results({}, static_cast<ResultView>(999)));
  }, "invalid result view admission");
  check(!admission_guard.last_cursor_observation().has_value(),
        "pre-admission invalid view created a cursor identity");
  auto closed_view = admission_guard.current_view();
  closed_view.close();
  expect_error("invalid_snapshot", [&] { static_cast<void>(closed_view.results()); },
               "closed epoch-view cursor admission");
  check(!admission_guard.last_cursor_observation().has_value(),
        "closed-view guard created or published a cursor identity");

  auto cancelled = runtime.core_results();
  const auto active_copy = cancelled.observation();
  check(active_copy.state == ResultCursorState::active &&
        active_copy.terminal_reason == CursorTerminalReason::none,
        "active cursor copy did not preserve its current lifecycle state");
  reports.cursor("active-copy-before-next", active_copy);
  const auto first = cancelled.next();
  check(first && first->values() == Row{integer(5)},
        "lifecycle fixture failed to return its literal row");
  const auto after_row = cancelled.observation();
  cancelled.cancel();
  const auto after_cancel = cancelled.observation();
  check(cancelled.state() == ResultCursorState::cancelled &&
        after_cancel.terminal_reason == CursorTerminalReason::explicit_cancel &&
        after_cancel.metric(CursorMetricId::cancel_calls).value == 1,
        "explicit cancel did not publish its terminal reason and count");
  check(active_copy.state == ResultCursorState::active &&
        active_copy.terminal_reason == CursorTerminalReason::none,
        "saved active observation was mutated by a later cancel");
  check(!cancelled.next(), "cancelled cursor did not reject another row as nullopt");
  cancelled.cancel();
  check(same_lifecycle_values(after_cancel, cancelled.observation()),
        "repeated next/cancel changed a closed cursor summary");
  reports.cursor("active-copy-after-row", after_row);
  reports.cursor("explicit-cancel", after_cancel);

  auto destination = runtime.core_results();
  const auto destination_id = destination.observation().cursor_id;
  auto source = runtime.core_results();
  destination = std::move(source);
  check(runtime.last_cursor_observation().has_value() &&
        runtime.last_cursor_observation()->cursor_id == destination_id &&
        runtime.last_cursor_observation()->terminal_reason == CursorTerminalReason::move_replacement,
        "move assignment did not close the replaced destination with its own report");
  const auto replaced = *runtime.last_cursor_observation();
  reports.cursor("move-replacement-destination", replaced);
  expect_error("invalid_cursor", [&] { static_cast<void>(source.state()); },
               "moved-from source state");
  expect_error("invalid_cursor", [&] { static_cast<void>(source.next()); },
               "moved-from source next");
  self_move(destination);
  check(destination.active(), "self move assignment closed the live cursor");
  destination.cancel();
  reports.cursor("move-assignment-source", destination.observation());

  auto move_source = runtime.core_results();
  auto move_constructed = std::move(move_source);
  expect_error("invalid_cursor", [&] { static_cast<void>(move_source.observation()); },
               "moved-from observation accessor");
  check(move_constructed.active() && move_constructed.owner().value == runtime.owner().value,
        "move construction lost the stable owner or cursor lease");
  move_constructed.cancel();
  reports.cursor("move-construction", move_constructed.observation());

  auto first_live = runtime.core_results();
  auto second_live = runtime.core_results();
  const auto first_live_report = first_live.observation();
  const auto second_live_report = second_live.observation();
  check(second_live_report.cursor_id > first_live_report.cursor_id &&
        runtime.last_cursor_observation()->cursor_id == second_live_report.cursor_id,
        "multiple live cursor starts did not publish their independently increasing IDs");
  check(first_live.next().has_value(), "first of two live cursors did not produce its row");
  const auto latest_completion = runtime.last_cursor_observation();
  check(latest_completion && latest_completion->cursor_id == first_live_report.cursor_id,
        "last cursor history followed construction order instead of publication order");
  first_live.cancel();
  second_live.cancel();
  reports.cursor("multiple-live-first-completion", first_live.observation());
  reports.cursor("multiple-live-second-cancel", second_live.observation());

  {
    auto destroyed = runtime.core_results();
    check(destroyed.active(), "destructor fixture cursor was not active");
  }
  const auto destruction = runtime.last_cursor_observation();
  check(destruction.has_value() &&
        destruction->terminal_reason == CursorTerminalReason::destruction &&
        destruction->state == ResultCursorState::cancelled,
        "cursor destruction did not publish its distinct terminal reason");
  reports.cursor("destructor-close", *destruction);

  PhysicalRuntime cap_runtime(unary_plan());
  static_cast<void>(cap_runtime.apply({1, TableId{0}, SetOperation::insert, int_row(17)}));
  auto unlimited = cap_runtime.core_results();
  check(drain(unlimited) == Relation{{integer(17)}},
        "work-cap baseline cursor failed its singleton row");
  const auto exact_limit = unlimited.metrics().total_work;
  check(exact_limit > 0, "work-cap baseline did not charge mandatory work");
  auto exact = cap_runtime.core_results(ResultCursorOptions{exact_limit});
  check(drain(exact) == Relation{{integer(17)}},
        "cursor failed at its independently measured exact work ceiling");
  check(cap_runtime.ready(), "exact work ceiling retained a result lease");
  reports.cursor("exact-work-ceiling-off", exact.observation());
  auto below_limit = cap_runtime.core_results(ResultCursorOptions{exact_limit - 1});
  expect_error("resource_limit", [&] { static_cast<void>(drain(below_limit)); },
               "one-less-than-exact cursor work ceiling");
  check(below_limit.state() == ResultCursorState::failed && cap_runtime.ready(),
        "N-1 work cap did not fail and release its cursor lease");
  reports.cursor("work-ceiling-minus-one-off", below_limit.observation());

  bool startup_failed = false;
  try {
    static_cast<void>(runtime.core_results(ResultCursorOptions{0}));
  } catch (const Error& failure) {
    startup_failed = failure.code() == "resource_limit";
  }
  check(startup_failed && runtime.ready(),
        "startup cap did not fail before cursor return and release admission");
  const auto failed_start = runtime.last_cursor_observation();
  check(failed_start.has_value() && !failed_start->constructed &&
        failed_start->state == ResultCursorState::failed &&
        failed_start->terminal_reason == CursorTerminalReason::startup_failure,
        "failed startup was represented as a constructed or exhausted cursor");
  check(failed_start->metric(CursorMetricId::cleanup_ns).availability == MetricAvailability::unavailable &&
        failed_start->metric(CursorMetricId::cleanup_calls).availability == MetricAvailability::unavailable,
        "failed construction fabricated a separately measured cleanup interval");
  reports.cursor("failed-startup-cap", *failed_start);

  auto failed_next = runtime.core_results(ResultCursorOptions{unlimited.metrics().startup.work});
  expect_error("resource_limit", [&] { static_cast<void>(failed_next.next()); },
               "active next with exact startup-only work ceiling");
  const auto failed_next_report = failed_next.observation();
  check(failed_next.state() == ResultCursorState::failed && runtime.ready() &&
        failed_next_report.terminal_reason == CursorTerminalReason::next_failure &&
        failed_next_report.metric(CursorMetricId::failed_calls).value == 1,
        "active next failure did not publish and release its lease");
  expect_error("invalid_cursor", [&] { static_cast<void>(failed_next.next()); },
               "rejected next after active failure");
  check(same_lifecycle_values(failed_next_report, failed_next.observation()),
        "rejected post-failure next altered the admitted call counters");
  reports.cursor("failed-active-next", failed_next_report);

  auto view = runtime.current_view();
  const auto before_invalid = runtime.last_cursor_observation();
  expect_error("invalid_fragment", [&] { static_cast<void>(view.visible_keys(NodeId{99})); },
               "out-of-range visible-key construction");
  check(runtime.last_cursor_observation()->cursor_id > before_invalid->cursor_id,
        "constructor failure did not count its admitted cursor identity");
  const auto invalid_constructor = *runtime.last_cursor_observation();
  check(!invalid_constructor.constructed &&
        invalid_constructor.terminal_reason == CursorTerminalReason::startup_failure,
        "view cursor constructor failure was not recorded as failed startup");
  reports.cursor("failed-view-cursor-constructor", invalid_constructor);
  view.close();
  clear_clock();
}

PhysicalPlan string_unary_plan() {
  const Catalog catalog{1, {{"s", {{"text", ScalarType::string}}}}};
  const Query query{{{"text", ScalarType::string}},
                    {{"s", TableId{0}, {VariableId{0}}}},
                    {{VariableId{0}, "text"}}, false};
  const FreeConnexTree tree{NodeId{0},
      {{"s", NodeKind::native, {VariableId{0}}, {}, 0, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

void persistent_oom_and_nonallocating_copies(ReportCollection& reports) {
  PhysicalRuntime runtime(string_unary_plan());
  static_cast<void>(runtime.apply({1, TableId{0}, SetOperation::insert,
                                   Row{std::string{"payload with an owned string"}}}));
  const auto owner = runtime.owner();

  bool factory_failed = false;
  allocation_probe::arm(0);
  try {
    static_cast<void>(runtime.core_results());
  } catch (const std::bad_alloc&) {
    factory_failed = true;
  }
  allocation_probe::disarm();
  check(factory_failed && runtime.ready() && runtime.owner() == owner,
        "persistent factory OOM did not unwind to the same ready owner");
  const auto startup = runtime.last_cursor_observation();
  check(startup.has_value() && startup->owner == owner.value && !startup->constructed &&
        startup->terminal_reason == CursorTerminalReason::startup_failure,
        "persistent factory OOM did not publish its failed-startup summary");
  reports.cursor("persistent-oom-factory", *startup);

  auto copy_probe = runtime.core_results();
  CursorObservation copied_cursor;
  ObservationSnapshot copied_snapshot;
  bool noalloc_copy_failed = false;
  allocation_probe::arm(0);
  try {
    copied_cursor = copy_probe.observation();
    copied_snapshot = runtime.observations();
    if (copied_snapshot.current_configuration)
      static_cast<void>(copied_snapshot.current_configuration->requested_options());
  } catch (...) {
    noalloc_copy_failed = true;
  }
  allocation_probe::disarm();
  check(!noalloc_copy_failed && allocation_probe::calls.load(std::memory_order_relaxed) == 0,
        "fixed cursor/observation snapshot copies allocated under persistent OOM");
  const auto calls_before_cancel = allocation_probe::calls.load(std::memory_order_relaxed);
  allocation_probe::arm(0);
  copy_probe.cancel();
  allocation_probe::disarm();
  check(allocation_probe::calls.load(std::memory_order_relaxed) == 0 &&
        calls_before_cancel == 0,
        "cursor cancellation attempted an allocation");
  reports.cursor("nonallocating-copied-observation", copy_probe.observation());

  auto failing_next = runtime.core_results();
  bool next_failed = false;
  allocation_probe::arm(0);
  try {
    static_cast<void>(failing_next.next());
  } catch (const std::bad_alloc&) {
    next_failed = true;
  }
  allocation_probe::disarm();
  check(next_failed && failing_next.state() == ResultCursorState::failed && runtime.ready(),
        "persistent next OOM did not fail and release the cursor lease");
  const auto failed = failing_next.observation();
  check(failed.owner == owner.value && failed.terminal_reason == CursorTerminalReason::next_failure &&
        failed.metric(CursorMetricId::failed_calls).availability == MetricAvailability::available &&
        failed.metric(CursorMetricId::failed_calls).value == 1,
        "persistent next OOM did not retain its admitted failure measurements");
  reports.cursor("persistent-oom-next", failed);

  auto retry = runtime.core_results();
  const auto output = drain(retry);
  check(output == Relation{{std::string{"payload with an owned string"}}},
        "same owner did not recover after persistent factory/next OOM");
  reports.cursor("same-owner-recovery-after-oom", retry.observation());
}

void detached_cursor_and_query_session(ReportCollection& reports) {
  std::optional<SupportRuntime::ResultCursor> detached;
  CursorObservation detached_report;
  std::uint64_t owner = 0;
  {
    auto runtime = std::make_unique<PhysicalRuntime>(unary_plan());
    static_cast<void>(runtime->apply({1, TableId{0}, SetOperation::insert, int_row(23)}));
    owner = runtime->owner().value;
    detached.emplace(runtime->core_results());
    detached_report = detached->observation();
    runtime.reset();
  }
  check(detached && detached->active() && detached->owner().value == owner,
        "cursor did not retain its owner state after facade destruction");
  check(drain(*detached) == Relation{{integer(23)}},
        "cursor could not finish after facade destruction");
  const auto after_destroy = detached->observation();
  check(after_destroy.owner == detached_report.owner &&
        after_destroy.sequence == detached_report.sequence &&
        after_destroy.terminal_reason == CursorTerminalReason::exhausted,
        "detached cursor changed its identity or lost its terminal report");
  reports.cursor("cursor-after-facade-destruction", after_destroy);

  Database initial;
  initial.tables.resize(1);
  initial.tables[0].insert(int_row(31));
  SessionOptions options;
  options.delta.physical.support.observation.mode = ObservationMode::timed;
  auto session = QuerySession::create(unary_plan(), initial,
      std::make_unique<std::istringstream>(), options);
  const auto snapshot = session->snapshot();
  check(snapshot.rows.size() == 1 && snapshot.rows[0].values() == int_row(31),
        "QuerySession snapshot did not use the expected committed result");
  const auto before_stop = session->last_cursor_observation();
  check(before_stop.has_value() && before_stop->source == CursorObservationSource::committed_results &&
        before_stop->state == ResultCursorState::exhausted,
        "QuerySession snapshot did not retain its actual result cursor summary");
  reports.cursor("query-session-snapshot", *before_stop);
  session->stop();
  const auto after_stop = session->last_cursor_observation();
  check(after_stop.has_value() && after_stop->cursor_id == before_stop->cursor_id,
        "QuerySession stop changed the committed cursor summary");
  session->drop();
  const auto after_drop = session->last_cursor_observation();
  check(after_drop.has_value() && after_drop->owner == before_stop->owner &&
        after_drop->cursor_id == before_stop->cursor_id,
        "QuerySession drop did not preserve the fixed cursor observation");
  reports.cursor("query-session-after-stop-drop", *after_drop);
}

bool same_observation_options(const ObservationOptions& a, const ObservationOptions& b) {
  return a.mode == b.mode && a.trace_capacity == b.trace_capacity &&
      a.sample_period == b.sample_period && a.sample_offset == b.sample_offset &&
      a.trace_timings == b.trace_timings;
}

bool same_delta_options(const DeltaOptions& a, const DeltaOptions& b) {
  const auto& as = a.physical.support;
  const auto& bs = b.physical.support;
  return as.work_limit == bs.work_limit && as.support_limit == bs.support_limit &&
      as.order == bs.order && as.capture_transitions == bs.capture_transitions &&
      same_observation_options(as.observation, bs.observation) &&
      a.physical.work_limit == b.physical.work_limit &&
      a.physical.derivation_limit == b.physical.derivation_limit &&
      a.mode == b.mode && a.view == b.view &&
      a.live_maintenance == b.live_maintenance && a.completion == b.completion &&
      a.work_limit == b.work_limit && a.cursor.work_limit == b.cursor.work_limit &&
      a.epoch_view.work_limit == b.epoch_view.work_limit &&
      a.spool_row_limit == b.spool_row_limit && a.spool_byte_limit == b.spool_byte_limit;
}

DeltaOptions exact_binding_options(ObservationMode mode = ObservationMode::timed) {
  DeltaOptions options;
  options.physical.support.work_limit = std::uint64_t{713};
  options.physical.support.support_limit = 911;
  options.physical.support.order = PropagationOrder::lifo;
  options.physical.support.capture_transitions = false;
  options.physical.support.observation.mode = mode;
  options.physical.support.observation.trace_capacity = 19;
  options.physical.support.observation.sample_period = 3;
  options.physical.support.observation.sample_offset = 1;
  options.physical.support.observation.trace_timings = false;
  options.physical.work_limit = std::nullopt;
  options.physical.derivation_limit = 1409;
  options.mode = DeltaMode::maintenance;
  options.view = ResultView::core;
  options.live_maintenance = LiveMaintenance::eager;
  options.completion = DeltaCompletion::automatic;
  options.work_limit = std::uint64_t{1601};
  options.cursor.work_limit = std::nullopt;
  options.epoch_view.work_limit = std::uint64_t{1801};
  options.spool_row_limit = 1901;
  options.spool_byte_limit = 2003;
  return options;
}

void check_binding(const ObservationConfiguration& actual, const DeltaOptions& requested,
                   DeltaMode mode, DeltaCompletion completion,
                   std::uint64_t owner, std::uint64_t generation, bool saturated,
                   std::size_t factors) {
  const auto copied = actual.requested_options();
  check(same_delta_options(copied, requested),
        "cursor configuration did not retain every requested nested option");
  check(actual.mode() == mode && actual.completion() == completion &&
        actual.live_maintenance() == requested.live_maintenance &&
        actual.view() == requested.view,
        "cursor configuration's resolved mode or view differs from expectation");
  check(actual.support_owner() == owner && actual.support_owner() != 0,
        "cursor configuration is not bound to its physical support owner");
  check(actual.generation() == generation && actual.generation_saturated() == saturated,
        "cursor configuration generation/saturation differs from literal switch history");
  check(actual.query_factors() == factors,
        "cursor configuration factor count differs from the independent C* fixture");
}

void mode_binding_and_bootstrap_cursors(ReportCollection& reports) {
  const auto plan = unary_plan();
  auto options = exact_binding_options();
  DeltaRuntime runtime(plan, options);
  const auto owner = runtime.owner().value;
  const auto initial = runtime.observations().current_configuration;
  check(initial.has_value(), "enabled DeltaRuntime did not capture its initial configuration");
  check_binding(*initial, options, DeltaMode::maintenance, DeltaCompletion::anchored,
                owner, 0, false, 1);

  auto old_cursor = runtime.core_results();
  auto old_report = old_cursor.observation();
  check(old_report.configuration.has_value(),
        "committed-result cursor omitted the begin-runtime configuration");
  check_binding(*old_report.configuration, options, DeltaMode::maintenance,
                DeltaCompletion::anchored, owner, 0, false, 1);
  expect_error("runtime_busy", [&] { static_cast<void>(runtime.set_mode(DeltaMode::delta)); },
               "mode switch while result cursor lease is active");
  old_cursor.cancel();

  static_cast<void>(runtime.set_mode(DeltaMode::delta));
  check(runtime.mode() == DeltaMode::delta && runtime.ready(),
        "successful mode bootstrap did not publish a ready delta mode");
  const auto bootstrap_cursor = runtime.last_cursor_observation();
  check(bootstrap_cursor.has_value() &&
        bootstrap_cursor->source == CursorObservationSource::epoch_keys &&
        bootstrap_cursor->state == ResultCursorState::exhausted,
        "delta bootstrap did not publish its actual visible-key cursor lifecycle");
  reports.cursor("mode-bootstrap-visible-key-cursor", *bootstrap_cursor);

  const auto generation_after_switch = runtime.observations().current_configuration;
  check(generation_after_switch.has_value(), "mode switch lost current configuration");
  check_binding(*generation_after_switch, options, DeltaMode::delta,
                DeltaCompletion::anchored, owner, 1, false, 1);
  static_cast<void>(runtime.set_mode(DeltaMode::delta));
  const auto after_noop = runtime.observations().current_configuration;
  check(after_noop.has_value() && after_noop->generation() == 1 &&
        !after_noop->generation_saturated(),
        "no-op mode switch incremented its immutable generation");

  auto delta_cursor = runtime.core_results();
  const auto delta_report = delta_cursor.observation();
  check(delta_report.configuration.has_value(), "delta cursor omitted its current binding");
  check_binding(*delta_report.configuration, options, DeltaMode::delta,
                DeltaCompletion::anchored, owner, 1, false, 1);
  delta_cursor.cancel();
  static_cast<void>(runtime.set_mode(DeltaMode::maintenance));
  const auto maintenance = runtime.observations().current_configuration;
  check(maintenance.has_value(), "maintenance mode switch lost current configuration");
  check_binding(*maintenance, options, DeltaMode::maintenance,
                DeltaCompletion::anchored, owner, 2, false, 1);
  check(old_report.configuration->generation() == 0 &&
        old_report.configuration->mode() == DeltaMode::maintenance,
        "later mode switches relabeled a saved cursor configuration");
  reports.cursor("mode-old-maintenance-binding-retained", old_report);
  reports.cursor("mode-current-delta-binding", delta_report);

  ObservationSnapshot copied_snapshot;
  std::optional<ObservationConfiguration> copied_config;
  bool allocation_during_copy = false;
  allocation_probe::arm(0);
  try {
    copied_snapshot = runtime.observations();
    copied_config = *copied_snapshot.current_configuration;
    static_cast<void>(copied_config->requested_options());
  } catch (...) {
    allocation_during_copy = true;
  }
  const auto allocations = allocation_probe::calls.load(std::memory_order_relaxed);
  allocation_probe::disarm();
  check(!allocation_during_copy && allocations == 0,
        "nontrivial observation/configuration snapshots allocated while being copied");

  auto failing_options = exact_binding_options();
  failing_options.cursor.work_limit = std::uint64_t{0};
  DeltaRuntime failed_bootstrap(unary_plan(), failing_options);
  const auto before_failure = failed_bootstrap.observations().current_configuration;
  expect_error("resource_limit", [&] {
    static_cast<void>(failed_bootstrap.set_mode(DeltaMode::delta));
  }, "delta bootstrap cursor work cap");
  const auto after_failure = failed_bootstrap.observations().current_configuration;
  check(failed_bootstrap.mode() == DeltaMode::maintenance && failed_bootstrap.ready() &&
        before_failure && after_failure &&
        before_failure->generation() == after_failure->generation() &&
        before_failure->mode() == after_failure->mode(),
        "failed bootstrap changed current mode or configuration");
  const auto failed_cursor = failed_bootstrap.last_cursor_observation();
  check(failed_cursor.has_value() && !failed_cursor->constructed &&
        failed_cursor->source == CursorObservationSource::epoch_keys &&
        failed_cursor->terminal_reason == CursorTerminalReason::startup_failure,
        "failed bootstrap did not expose the real failed internal cursor construction");
  reports.cursor("failed-mode-bootstrap-cursor", *failed_cursor);

  struct ResetGenerationOverride {
    ~ResetGenerationOverride() {
      detail::set_observation_initial_generation_for_testing(0);
    }
  } reset_generation;
  detail::set_observation_initial_generation_for_testing(
      std::numeric_limits<std::uint64_t>::max() - 1);
  auto saturated_options = exact_binding_options();
  DeltaRuntime saturated(unary_plan(), saturated_options);
  const auto saturated_owner = saturated.owner().value;
  auto pre_max_cursor = saturated.core_results();
  const auto pre_max = pre_max_cursor.observation();
  check(pre_max.configuration &&
        pre_max.configuration->generation() == std::numeric_limits<std::uint64_t>::max() - 1 &&
        !pre_max.configuration->generation_saturated(),
        "generation test seam did not begin at the literal unsaturated predecessor");
  pre_max_cursor.cancel();
  static_cast<void>(saturated.set_mode(DeltaMode::delta));
  auto max_cursor = saturated.core_results();
  const auto max_unsaturated = max_cursor.observation();
  check(max_unsaturated.configuration &&
        max_unsaturated.configuration->generation() == std::numeric_limits<std::uint64_t>::max() &&
        !max_unsaturated.configuration->generation_saturated(),
        "generation did not reach an exact unsaturated uint64 maximum");
  max_cursor.cancel();
  static_cast<void>(saturated.set_mode(DeltaMode::maintenance));
  auto saturated_cursor = saturated.core_results();
  const auto at_cap = saturated_cursor.observation();
  check(at_cap.configuration &&
        at_cap.configuration->generation() == std::numeric_limits<std::uint64_t>::max() &&
        at_cap.configuration->generation_saturated(),
        "generation did not preserve its cap and mark diagnostic saturation");
  check(pre_max.configuration->generation() == std::numeric_limits<std::uint64_t>::max() - 1 &&
        !pre_max.configuration->generation_saturated() &&
        max_unsaturated.configuration->generation() == std::numeric_limits<std::uint64_t>::max() &&
        !max_unsaturated.configuration->generation_saturated(),
        "later saturation mutated saved older cursor configurations");
  check_binding(*at_cap.configuration, saturated_options, DeltaMode::maintenance,
                DeltaCompletion::anchored, saturated_owner,
                std::numeric_limits<std::uint64_t>::max(), true, 1);
  saturated_cursor.cancel();
  reports.cursor("generation-saturated-cursor", at_cap);
  detail::set_observation_initial_generation_for_testing(0);

  auto three_factor = three_factor_y_head_plan();
  DeltaRuntime factor_runtime(three_factor, exact_binding_options());
  auto factor_cursor = factor_runtime.core_results();
  check(factor_cursor.observation().configuration->query_factors() == 3,
        "C* factor count incorrectly used physical-node/head-count shortcuts");
  factor_cursor.cancel();
  reports.cursor("three-factor-current-binding", factor_cursor.observation());
}

void delta_nested_clock_and_unsampled_trace(ReportCollection& reports) {
  auto options = exact_binding_options(ObservationMode::timed);
  options.mode = DeltaMode::maintenance;
  DeltaRuntime runtime(joined_visible_factor_plan(), options);
  static_cast<void>(runtime.apply({1, TableId{0}, SetOperation::insert, int_row(1)}));
  static_cast<void>(runtime.set_mode(DeltaMode::delta));

  reset_clock(1000);
  const auto calls_before = fake_clock_calls;
  static_cast<void>(runtime.apply({2, TableId{1}, SetOperation::insert, edge(1, 10)}));
  const auto calls_during_attempt = fake_clock_calls - calls_before;
  const auto after_attempt = runtime.observations();
  check(after_attempt.last.has_value() &&
        after_attempt.last->owner == ObservationLayer::delta,
        "timed delta operation did not publish its attempt summary");
  const auto delta_reads = after_attempt.last->metric(MetricId::delta_clock_reads);
  const auto nested_reads = after_attempt.last->metric(MetricId::nested_cursor_clock_reads);
  check(delta_reads.availability == MetricAvailability::available &&
        nested_reads.availability == MetricAvailability::available &&
        calls_during_attempt == delta_reads.value + nested_reads.value,
        "active delta fake-clock calls did not reconcile as own plus nested reads");
  check(nested_reads.value > 0,
        "delta attempt fixture did not exercise any nested epoch-view cursor clocks");
  const auto saved_attempt_clock_values = std::pair{delta_reads.value, nested_reads.value};
  auto current = runtime.results();
  check(drain(current) == Relation{{integer(1)}},
        "current enumeration after delta attempt differs from its independent row");
  const auto current_report = current.observation();
  check(current_report.metric(CursorMetricId::clock_reads).availability == MetricAvailability::available &&
        current_report.metric(CursorMetricId::clock_reads).value > 0,
        "current-result cursor did not retain its own optional clock reads");
  const auto after_current = runtime.observations();
  check(after_current.last.has_value() &&
        after_current.last->metric(MetricId::delta_clock_reads).value == saved_attempt_clock_values.first &&
        after_current.last->metric(MetricId::nested_cursor_clock_reads).value == saved_attempt_clock_values.second,
        "later current enumeration incremented a historical delta attempt");
  reports.cursor("delta-current-result-after-attempt", current_report);
  clear_clock();

  auto trace_options = exact_binding_options(ObservationMode::trace);
  trace_options.physical.support.observation.sample_period = 17;
  trace_options.physical.support.observation.sample_offset = 16;
  trace_options.physical.support.observation.trace_timings = true;
  DeltaRuntime unsampled(unary_plan(), trace_options);
  static_cast<void>(unsampled.apply({1, TableId{0}, SetOperation::insert, int_row(9)}));
  const auto unsampled_update = unsampled.observations();
  check(unsampled_update.trace == TraceDisposition::not_sampled,
        "trace fixture's sequence-one update unexpectedly matched its sample offset");
  reset_clock();
  auto cursor = unsampled.core_results();
  check(drain(cursor) == Relation{{integer(9)}},
        "unsampled trace cursor did not emit the current committed row");
  const auto cursor_report = cursor.observation();
  check(fake_clock_calls > 0 &&
        cursor_report.metric(CursorMetricId::clock_reads).value == fake_clock_calls,
        "per-cursor timing was incorrectly suppressed by per-update trace sampling");
  reports.cursor("trace-update-unsampled-cursor-timed", cursor_report);
  clear_clock();
}

void fake_clock_zero_and_regression(ReportCollection& reports) {
  PhysicalRuntimeOptions options;
  options.support.observation.mode = ObservationMode::timed;
  PhysicalRuntime runtime(unary_plan(), options);
  static_cast<void>(runtime.apply({1, TableId{0}, SetOperation::insert, int_row(6)}));

  script_clock({10, 5});
  auto regressing = runtime.core_results();
  auto regression_report = regressing.observation();
  check(regression_report.metric(CursorMetricId::startup_ns).availability ==
        MetricAvailability::unavailable &&
        regression_report.metric(CursorMetricId::clock_regressions).value == 1,
        "backward test clock did not mark startup timing unavailable");
  regressing.cancel();
  reports.cursor("fake-clock-backward-startup", regressing.observation());

  script_clock({11, 11});
  auto zero = runtime.core_results();
  const auto zero_report = zero.observation();
  check(zero_report.metric(CursorMetricId::startup_ns).availability ==
        MetricAvailability::available && zero_report.metric(CursorMetricId::startup_ns).value == 0,
        "available exact-zero timing collapsed into unavailable");
  zero.cancel();
  reports.cursor("fake-clock-available-zero", zero.observation());
  clear_clock();
}

void committed_gauges_and_private_guards(ReportCollection& reports) {
  PhysicalRuntimeOptions options;
  options.support.observation.mode = ObservationMode::off;
  const auto plan = aliased_generalized_plan();
  PhysicalRuntime runtime(plan, options);
  Database db;
  db.tables.resize(1);
  std::uint64_t sequence = 0;
  for (const auto& row : {edge(1, 10), edge(10, 2), edge(2, 20), edge(20, 3)})
    apply(runtime, db, sequence, TableId{0}, SetOperation::insert, row);
  const auto expected = reference::evaluate(plan.catalog(), plan.query(), db);
  check(expected == Relation{{integer(1)}, {integer(10)}, {integer(2)}},
        "independent aliased self-join A04 fixture changed its expected projection");
  auto result_cursor = runtime.core_results();
  check(drain(result_cursor) == expected, "aliased projected result differs from A04");

  const auto initial = runtime.committed_state_gauges();
  check(initial.base_tuples.availability == MetricAvailability::available &&
        initial.base_tuples.value == 4 && initial.bases.size() == 1 &&
        initial.bases[0].tuples == 4,
        "alias gauge counted one physical source table more than once");
  check(initial.nodes.size() == 2 && initial.nodes[0].records == 4 &&
        initial.nodes[1].records == 4 && initial.nodes[0].survivors == 3 &&
        initial.nodes[1].survivors == 4 &&
        initial.nodes[0].projected_parent_keys == 1 &&
        initial.nodes[1].projected_parent_keys == 4,
        "aliased projected support gauges differ from independent literal relation counts");
  check(initial.nodes[0].visible_factor_assignments.availability == MetricAvailability::available &&
        initial.nodes[0].visible_factor_assignments.value == 3 &&
        initial.nodes[1].visible_factor_assignments.availability == MetricAvailability::unavailable,
        "projected C* factor and outside-factor gauge scopes were mislabeled");
  check(initial.full_result_count.availability == MetricAvailability::unavailable &&
        initial.allocated_bytes.availability == MetricAvailability::unavailable &&
        initial.live_bytes.availability == MetricAvailability::unavailable &&
        initial.checkpoint_bytes.availability == MetricAvailability::unavailable &&
        initial.checkpoint_ns.availability == MetricAvailability::unavailable &&
        initial.recovery_replay_length.availability == MetricAvailability::unavailable,
        "gauge API promoted explicitly unsupported full-result/memory/durable facts");
  reports.gauge("aliased-projected-off-initial", initial);

  auto pending = runtime.prepare({sequence + 1, TableId{0}, SetOperation::insert, edge(99, 100)});
  expect_error("runtime_busy", [&] { static_cast<void>(runtime.committed_state_gauges()); },
               "private physical update gauge read");
  pending.rollback();
  const auto after_rollback = runtime.committed_state_gauges();
  check(after_rollback.sequence == initial.sequence &&
        after_rollback.base_tuples.value == initial.base_tuples.value &&
        after_rollback.nodes[0].records == initial.nodes[0].records,
        "rollback changed committed state gauges");
  reports.gauge("aliased-projected-after-rollback", after_rollback);

  apply(runtime, db, sequence, TableId{0}, SetOperation::insert, edge(99, 100));
  const auto inserted = runtime.committed_state_gauges();
  check(inserted.base_tuples.value == 5 && inserted.nodes[0].records == 5 &&
        inserted.nodes[1].records == 5 && inserted.nodes[1].survivors == 5 &&
        inserted.nodes[1].projected_parent_keys == 5,
        "committed insert did not update source and both alias record gauges");
  check(reference::evaluate(plan.catalog(), plan.query(), db) == expected,
        "unmatched insert unexpectedly changed the independent A04 answer");
  reports.gauge("aliased-projected-after-insert", inserted);

  apply(runtime, db, sequence, TableId{0}, SetOperation::insert, edge(99, 100));
  const auto noop = runtime.committed_state_gauges();
  check(noop.sequence == inserted.sequence + 1 && noop.base_tuples.value == inserted.base_tuples.value &&
        noop.nodes[0].records == inserted.nodes[0].records &&
        noop.nodes[1].projected_parent_keys == inserted.nodes[1].projected_parent_keys,
        "no-op insertion changed exact set-cardinality gauges");
  reports.gauge("aliased-projected-after-noop", noop);

  apply(runtime, db, sequence, TableId{0}, SetOperation::erase, edge(99, 100));
  const auto erased = runtime.committed_state_gauges();
  check(erased.base_tuples.value == 4 && erased.nodes[0].records == 4 &&
        erased.nodes[1].records == 4 && erased.nodes[1].survivors == 4 &&
        erased.nodes[1].projected_parent_keys == 4,
        "committed delete did not restore both alias record gauges");
  check(reference::evaluate(plan.catalog(), plan.query(), db) == expected,
        "delete of unmatched row changed the independent A04 answer");
  reports.gauge("aliased-projected-after-delete", erased);

  PhysicalRuntime empty(plan, options);
  const auto zero = empty.committed_state_gauges();
  check(zero.base_tuples.availability == MetricAvailability::available &&
        zero.base_tuples.value == 0 && zero.nodes[0].records == 0 &&
        zero.nodes[0].visible_factor_assignments.availability == MetricAvailability::available &&
        zero.nodes[0].visible_factor_assignments.value == 0 &&
        zero.nodes[1].visible_factor_assignments.availability == MetricAvailability::unavailable,
        "exact zero gauges were confused with an out-of-scope unavailable value");
  reports.gauge("aliased-projected-off-exact-zero", zero);

  SupportRuntime support(plan, options.support);
  const auto support_only = support.committed_state_gauges();
  check(support_only.base_tuples.availability == MetricAvailability::unavailable,
        "logical support-only read fabricated physical base-table authority");
  reports.gauge("support-only-base-unavailable", support_only);
}

}  // namespace

int main() {
  ReportCollection reports;
  try {
    check_registry();
    group_complete("registry");
    compare_reference_and_scalar_routes(reports);
    group_complete("independent A04 result fixtures");
    product_reference_and_factor_gauges(reports);
    group_complete("generalized products and factor gauges");
    observation_mode_matrix(reports);
    group_complete("observation mode matrix");
    epoch_cursor_sources_and_invalidation(reports);
    group_complete("epoch cursor sources and rollback invalidation");
    lifecycle_caps_and_failed_startup(reports);
    group_complete("cursor lifecycle, work caps, and failed startup");
    persistent_oom_and_nonallocating_copies(reports);
    group_complete("persistent OOM and same-owner recovery");
    detached_cursor_and_query_session(reports);
    group_complete("detached cursors and QuerySession retention");
    mode_binding_and_bootstrap_cursors(reports);
    group_complete("configuration binding and mode bootstrap");
    delta_nested_clock_and_unsampled_trace(reports);
    group_complete("nested delta clocks and unsampled trace");
    fake_clock_zero_and_regression(reports);
    group_complete("zero and backward fake clocks");
    committed_gauges_and_private_guards(reports);
    group_complete("committed gauges and private-state guards");
    clear_clock();

    std::cout << "{\"format\":\"o07_cursor_observation_independent_test\","
              << "\"test_revision\":\"o07-cursor-observation-test-fixture-proposal\","
              << "\"cursor_package_sha256\":\"5dcd916bda78bbe1bef6047a65b4a1fa7ef6ad405ee54877c8033b818d3b8259\","
              << "\"checks\":" << checks << ",\"cursor_reports\":[";
    for (std::size_t i = 0; i < reports.cursors.size(); ++i) {
      if (i != 0) std::cout << ',';
      std::cout << "{\"case\":\"" << reports.cursors[i].first
                << "\",\"report\":" << reports.cursors[i].second << '}';
    }
    std::cout << "],\"gauge_reports\":[";
    for (std::size_t i = 0; i < reports.gauges.size(); ++i) {
      if (i != 0) std::cout << ',';
      std::cout << "{\"case\":\"" << reports.gauges[i].first
                << "\",\"report\":" << reports.gauges[i].second << '}';
    }
    std::cout << "]}\n";
    return 0;
  } catch (const std::exception& failure) {
    clear_clock();
    allocation_probe::disarm();
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
