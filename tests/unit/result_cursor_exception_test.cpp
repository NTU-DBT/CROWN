#include "crown/api/error.hpp"
#include "crown/frontend/normalize.hpp"
#include "crown/io/document.hpp"
#include "crown/io/support.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/physical.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <memory>
#include <new>
#include <optional>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <utility>
#include <vector>

// Keep the injector local to this executable. The noinline wrapper prevents
// GCC's replaceable-new mismatch warning around the custom global operators.
// Only ordinary throwing scalar/array new is directly replaced. There are no
// dedicated aligned/nothrow replacements; indirect delegation is not asserted.
// Direct malloc/realloc/system calls and MemoryAccount admission denials are
// outside this injected fault seam.
namespace {
thread_local std::ptrdiff_t fail_after = -1;
[[gnu::noinline]] void* malloc_new(std::size_t bytes) {
  if (fail_after >= 0) {
    if (fail_after == 0) throw std::bad_alloc{};
    --fail_after;
  }
  if (auto* result = std::malloc(bytes == 0 ? 1 : bytes)) return result;
  throw std::bad_alloc{};
}
struct FaultScope {
  explicit FaultScope(std::ptrdiff_t step = -1) { fail_after = step; }
  ~FaultScope() { fail_after = -1; }
  FaultScope(const FaultScope&) = delete;
  FaultScope& operator=(const FaultScope&) = delete;
  void forbid_allocations() noexcept { fail_after = 0; }
};
}  // namespace

void* operator new(std::size_t bytes) { return malloc_new(bytes); }
void* operator new[](std::size_t bytes) { return malloc_new(bytes); }
void operator delete(void* pointer) noexcept { std::free(pointer); }
void operator delete[](void* pointer) noexcept { std::free(pointer); }
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }

namespace {
using namespace crown;
using namespace crown::runtime;
using ResultCursor = SupportRuntime::ResultCursor;

static_assert(std::is_nothrow_move_constructible_v<ResultCursor>);
static_assert(std::is_nothrow_move_assignable_v<ResultCursor>);

void check(bool condition, std::string_view message) {
  if (!condition) throw std::runtime_error(std::string(message));
}

template <class Action>
void expect_error(Action&& action, std::string_view code) {
  try {
    std::forward<Action>(action)();
  } catch (const Error& failure) {
    check(failure.code() == code, "unexpected cursor error code");
    return;
  }
  throw std::runtime_error("expected cursor error code " + std::string(code));
}

Value n(std::int64_t value) { return value; }
Value s(std::string value) { return value; }

const std::string& long_key() {
  static const std::string value(512, 'k');
  return value;
}

const std::string& long_sql_constant() {
  static const std::string value(512, 'q');
  return value;
}

PhysicalPlan join_plan() {
  const Catalog catalog{7, {
      {"a", {{"k", ScalarType::string}, {"x", ScalarType::int64}}},
      {"b", {{"k", ScalarType::string}, {"y", ScalarType::int64}}}}};
  const Query query{
      {{"k", ScalarType::string}, {"x", ScalarType::int64}, {"y", ScalarType::int64}},
      {{"left", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"right", TableId{1}, {VariableId{0}, VariableId{2}}}},
      {{VariableId{0}, "k"}, {VariableId{1}, "x"}, {VariableId{2}, "y"}}, false};
  const FreeConnexTree tree{NodeId{0}, {
      {"join-key", NodeKind::generalized, {VariableId{0}}, {NodeId{1}, NodeId{2}}, {}, {}},
      {"left", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}},
      {"right", NodeKind::native, {VariableId{0}, VariableId{2}}, {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

std::optional<VariableId> variable_term(const Term& term) {
  if (const auto* variable = std::get_if<VariableId>(&term)) return *variable;
  return {};
}

FreeConnexTree sql_tree(const Query& query) {
  if (query.atoms.empty()) return {};
  using VariableSet = std::set<VariableId>;
  std::vector<VariableSet> scopes(query.atoms.size());
  for (std::size_t i = 0; i < query.atoms.size(); ++i)
    for (const auto& term : query.atoms[i].terms)
      if (const auto variable = variable_term(term)) scopes[i].insert(*variable);

  FreeConnexTree tree;
  if (query.atoms.size() == 1) {
    tree.root = NodeId{0};
    tree.nodes.push_back({query.atoms[0].occurrence, NodeKind::native, scopes[0], {}, 0, {}});
    return tree;
  }

  VariableSet common = scopes.front();
  for (std::size_t i = 1; i < scopes.size(); ++i) {
    VariableSet overlap;
    std::set_intersection(common.begin(), common.end(), scopes[i].begin(), scopes[i].end(),
                          std::inserter(overlap, overlap.end()));
    common = std::move(overlap);
  }
  tree.root = NodeId{0};
  std::vector<NodeId> children;
  for (std::size_t i = 0; i < query.atoms.size(); ++i) children.push_back(NodeId{i + 1});
  tree.nodes.push_back({"sql_product", NodeKind::generalized, common, children, {}, {}});
  for (std::size_t i = 0; i < query.atoms.size(); ++i)
    tree.nodes.push_back({query.atoms[i].occurrence, NodeKind::native, scopes[i], {}, i, {}});
  return tree;
}

PhysicalPlan sql_output_plan() {
  const Catalog catalog{8, {{"r", {{"x", ScalarType::int64}}}}};
  const std::string sql = "SELECT DISTINCT r.x, '" + long_sql_constant() +
                          "' AS marker, r.x AS again FROM r";
  const auto binding = frontend::bind_sql(sql, catalog);
  check(std::holds_alternative<frontend::BoundSql>(binding), "SQL output mapping fixture did not bind");
  auto normalized = frontend::normalize_sql(std::get<frontend::BoundSql>(binding));
  check(std::holds_alternative<frontend::NormalizedSql>(normalized), "SQL output mapping fixture did not normalize");
  auto program = std::get<frontend::NormalizedSql>(std::move(normalized));
  const auto tree = sql_tree(program.core);
  auto plan = planner::lower_normalized(program, tree);
  check(plan.normalized() && plan.normalized()->outputs.size() == 3 &&
            std::holds_alternative<frontend::ConstantOutput>(plan.normalized()->outputs[1].value),
        "SQL output mapping fixture lost its repeated and constant outputs");
  return plan;
}

PhysicalPlan exists_plan() {
  const Catalog catalog{9, {{"r", {{"x", ScalarType::int64}}}}};
  const auto binding = frontend::bind_sql("SELECT EXISTS(SELECT DISTINCT r.x FROM r)", catalog);
  check(std::holds_alternative<frontend::BoundSql>(binding), "EXISTS cursor fixture did not bind");
  auto normalized = frontend::normalize_sql(std::get<frontend::BoundSql>(binding));
  check(std::holds_alternative<frontend::NormalizedSql>(normalized), "EXISTS cursor fixture did not normalize");
  auto program = std::get<frontend::NormalizedSql>(std::move(normalized));
  const auto tree = sql_tree(program.core);
  return planner::lower_normalized(program, tree);
}

PhysicalRuntimeOptions runtime_options() {
  PhysicalRuntimeOptions result;
  result.support.capture_transitions = true;
  return result;
}

Row left_row(std::int64_t x) { return {s(long_key()), n(x)}; }
Row right_row(std::int64_t y) { return {s(long_key()), n(y)}; }

std::vector<Row> expected_join_rows() {
  return {{s(long_key()), n(1), n(10)}, {s(long_key()), n(1), n(20)},
          {s(long_key()), n(2), n(10)}, {s(long_key()), n(2), n(20)}};
}

PhysicalRuntime make_physical_join(const PhysicalPlan& plan) {
  PhysicalRuntime runtime{plan, runtime_options()};
  static_cast<void>(runtime.apply({1, TableId{0}, SetOperation::insert, left_row(1)}));
  static_cast<void>(runtime.apply({2, TableId{0}, SetOperation::insert, left_row(2)}));
  static_cast<void>(runtime.apply({3, TableId{1}, SetOperation::insert, right_row(10)}));
  static_cast<void>(runtime.apply({4, TableId{1}, SetOperation::insert, right_row(20)}));
  check(runtime.has_answer() && runtime.sequence() == 4, "physical cursor fixture did not reach its full join");
  runtime.check_invariants();
  return runtime;
}

SupportRuntime make_support_join(const PhysicalPlan& plan) {
  SupportRuntime runtime{plan, runtime_options().support};
  static_cast<void>(runtime.apply({1, NodeId{1}, SetOperation::insert, left_row(1)}));
  static_cast<void>(runtime.apply({2, NodeId{1}, SetOperation::insert, left_row(2)}));
  static_cast<void>(runtime.apply({3, NodeId{2}, SetOperation::insert, right_row(10)}));
  static_cast<void>(runtime.apply({4, NodeId{2}, SetOperation::insert, right_row(20)}));
  check(runtime.has_answer() && runtime.sequence() == 4, "support cursor fixture did not reach its full join");
  runtime.check_invariants();
  return runtime;
}

io::Json row_image(const Row& row) {
  auto result = io::Json::array();
  for (const auto& value : row) result.push_back(io::write_scalar(value));
  return result;
}

std::optional<SupportHandle> lookup_support(const SupportRuntime& runtime, NodeId node,
                                           SupportRole role, const Row& values) {
  return runtime.find(node, role, values);
}
std::optional<SupportHandle> lookup_support(const PhysicalRuntime& runtime, NodeId node,
                                           SupportRole role, const Row& values) {
  return runtime.find_support(node, role, values);
}
std::optional<storage::Tuple> read_support(const SupportRuntime& runtime, SupportHandle handle) {
  return runtime.get(handle);
}
std::optional<storage::Tuple> read_support(const PhysicalRuntime& runtime, SupportHandle handle) {
  return runtime.get_support(handle);
}

template <class Runtime>
io::Json support_handle_image(const Runtime& runtime, const SupportSnapshot& snapshot) {
  auto result = io::Json::array();
  const auto add = [&](SupportHandle handle, const storage::Tuple& tuple) {
    const auto stored = read_support(runtime, handle);
    check(stored && stored->layout().same_token(tuple.layout()) && stored->values() == tuple.values(),
          "public support handle no longer resolves to its snapshot tuple");
    result.push_back({{"owner", handle.owner.value}, {"node", handle.node.value},
                      {"role", static_cast<unsigned>(handle.role)}, {"tuple", handle.tuple.value},
                      {"values", row_image(crown::storage::export_row(tuple.values()))}});
  };
  for (const auto& node : snapshot.nodes) {
    for (const auto& record : node.records) add(record.handle, record.tuple);
    for (const auto& tuple : node.survivors) {
      const auto handle = lookup_support(runtime, node.node, SupportRole::survivors, crown::storage::export_row(tuple.values()));
      check(handle.has_value(), "support survivor lost its public handle");
      add(*handle, tuple);
    }
    for (const auto& key : node.parent_keys) add(key.handle, key.key);
    if (node.visible_keys)
      for (const auto& key : *node.visible_keys) add(key.handle, key.key);
  }
  return result;
}

io::Json state_image(const SupportRuntime& runtime) {
  const auto snapshot = runtime.snapshot();
  return {{"sequence", runtime.sequence()}, {"answer", runtime.has_answer()},
          {"support", io::write_support_snapshot(snapshot, runtime.plan())},
          {"handles", support_handle_image(runtime, snapshot)}};
}

io::Json state_image(const PhysicalRuntime& runtime) {
  const auto snapshot = runtime.snapshot();
  auto physical = io::Json::array();
  auto source_handles = io::Json::array();
  for (std::size_t table = 0; table < snapshot.physical.tables.size(); ++table) {
    auto rows = io::Json::array();
    for (const auto& row : snapshot.physical.tables[table]) {
      rows.push_back(row_image(row));
      const auto handle = runtime.find_source(TableId{table}, row);
      check(handle.has_value(), "physical snapshot row lost its public source handle");
      const auto stored = runtime.get_source(TableId{table}, *handle);
      check(stored && stored->values() == row, "public source handle no longer resolves to its row");
      source_handles.push_back({{"table", table}, {"owner", handle->owner.value},
                                {"relation", handle->relation.value}, {"tuple", handle->tuple.value}});
    }
    physical.push_back(std::move(rows));
  }
  auto derivations = io::Json::array();
  for (const auto& occurrence : snapshot.derivations) {
    auto rows = io::Json::array();
    for (const auto& item : occurrence)
      rows.push_back({{"values", row_image(crown::storage::export_row(item.tuple.values()))}, {"count", item.count}});
    derivations.push_back(std::move(rows));
  }
  return {{"sequence", runtime.sequence()}, {"answer", runtime.has_answer()},
          {"physical", std::move(physical)}, {"source_handles", std::move(source_handles)},
          {"derivations", std::move(derivations)},
          {"support", io::write_support_snapshot(snapshot.support, runtime.plan())},
          {"support_handles", support_handle_image(runtime, snapshot.support)}};
}

void check_startup(const ResultCursor& cursor, const auto& plan, bool scalar = false) {
  const auto& startup = cursor.metrics().startup;
  const auto expected_frames = scalar ? std::size_t{0} : plan.enumeration().steps.size();
  check(startup.route_checks == 1 && startup.frame_initializations == expected_frames,
        "cursor startup counters do not match route and frame initialization work");
  check(startup.calls == 0 && startup.cursor_opens == 0 && startup.cursor_advances == 0,
        "cursor startup advanced an enumeration cursor");
  check(cursor.metrics().total_work == startup.work && cursor.metrics().results.work == 0 &&
            cursor.metrics().termination.work == 0 && cursor.metrics().failed.work == 0,
        "cursor startup work was charged to another phase");
}

void check_phase_sum(const ResultCursorMetrics& metrics) {
  check(metrics.total_work == metrics.startup.work + metrics.results.work +
            metrics.termination.work + metrics.failed.work,
        "cursor phase work does not sum to its abstract total budget");
}

std::vector<Row> drain(ResultCursor& cursor) {
  std::vector<Row> result;
  for (;;) {
    auto item = cursor.next();
    if (!item) break;
    result.push_back(crown::storage::export_row(item->values()));
    check(cursor.metrics().last.rows_emitted == 1 &&
              cursor.metrics().results.rows_emitted == result.size(),
          "successful cursor output was not charged in the result phase");
  }
  check(cursor.state() == ResultCursorState::exhausted && !cursor.active(),
        "cursor did not close its lease after null termination");
  check(cursor.metrics().termination.calls == 1 && cursor.metrics().termination.rows_emitted == 0 &&
            cursor.metrics().last.rows_emitted == 0,
        "null termination was not charged in its own phase");
  check_phase_sum(cursor.metrics());
  const auto work = cursor.metrics().total_work;
  check(!cursor.next() && !cursor.next() && cursor.metrics().total_work == work,
        "an exhausted cursor charged work or returned rows on repeated next calls");
  return result;
}

template <class Runtime, class MakeRuntime, class MakeCursor, class Image>
std::size_t sweep_factory_faults(MakeRuntime make_runtime, MakeCursor make_cursor, Image image,
                                std::string_view label) {
  std::size_t failures = 0;
  for (std::ptrdiff_t step = 0; step < 64; ++step) {
    Runtime runtime = make_runtime();
    const auto before = image(runtime);
    bool allocation_failed = false;
    try {
      FaultScope fault(step);
      auto cursor = make_cursor(runtime);
      cursor.cancel();
    } catch (const std::bad_alloc&) {
      allocation_failed = true;
    }
    if (!allocation_failed) {
      check(runtime.ready(), std::string(label) + ": successful factory left a reader lease");
      return failures;
    }
    ++failures;
    check(runtime.ready() && image(runtime) == before,
          std::string(label) + ": ordinary-new failure changed state or retained a factory lease");
    auto retry = make_cursor(runtime);
    check(retry.sequence() == runtime.sequence(), std::string(label) + ": factory retry captured a stale epoch");
    retry.cancel();
    check(runtime.ready(), std::string(label) + ": successful retry did not release its lease");
  }
  throw std::runtime_error(std::string(label) + ": factory fault sweep did not reach a successful step");
}

struct NextFailureKinds {
  bool live_cursor_open = false;
  bool key_projection = false;
  bool bucket_cursor_open = false;
  bool result_assembly = false;
  bool sql_mapping = false;
};

template <class Runtime, class MakeRuntime, class MakeCursor, class Image>
std::size_t sweep_next_faults(MakeRuntime make_runtime, MakeCursor make_cursor, Image image,
                              const std::vector<Row>& expected, NextFailureKinds& kinds,
                              std::string_view label) {
  std::size_t failures = 0;
  for (std::ptrdiff_t step = 0; step < 96; ++step) {
    Runtime runtime = make_runtime();
    const auto before = image(runtime);
    auto cursor = make_cursor(runtime);
    check_startup(cursor, runtime.plan());
    const auto sequence = cursor.sequence();
    bool allocation_failed = false;
    std::optional<storage::Tuple> yielded;
    try {
      FaultScope fault(step);
      yielded = cursor.next();
    } catch (const std::bad_alloc&) {
      allocation_failed = true;
    }
    if (!allocation_failed) {
      check(yielded && yielded->values() == expected.front(),
            std::string(label) + ": successful next sweep step did not return the first expected row");
      cursor.cancel();
      check(runtime.ready(), std::string(label) + ": cancelling successful sweep cursor retained a lease");
      return failures;
    }

    ++failures;
    check(cursor.state() == ResultCursorState::failed && !cursor.active() && runtime.ready(),
          std::string(label) + ": bad_alloc did not fail the cursor and close its lease");
    const auto& failed = cursor.metrics().failed;
    kinds.live_cursor_open = kinds.live_cursor_open ||
        (failed.cursor_opens > failed.cursor_advances && failed.bucket_lookups == 0);
    kinds.key_projection = kinds.key_projection || failed.key_fields > failed.bucket_lookups;
    kinds.bucket_cursor_open = kinds.bucket_cursor_open ||
        (failed.bucket_lookups > 0 && failed.cursor_opens > failed.cursor_advances);
    kinds.result_assembly = kinds.result_assembly || failed.output_fields > 0;
    kinds.sql_mapping = kinds.sql_mapping || failed.output_fields >= 2;
    check(cursor.metrics().last.work == failed.work && cursor.metrics().results.work == 0 &&
              cursor.metrics().termination.work == 0,
          std::string(label) + ": failed next counters leaked into another phase");
    check_phase_sum(cursor.metrics());
    expect_error([&] { static_cast<void>(cursor.next()); }, "invalid_cursor");
    check(image(runtime) == before && runtime.sequence() == sequence,
          std::string(label) + ": failed next changed snapshot, sequence, derivations, or public handles");

    auto retry = make_cursor(runtime);
    check(retry.sequence() == sequence, std::string(label) + ": retry cursor did not resume the same epoch");
    check(drain(retry) == expected, std::string(label) + ": retry after next failure did not return the clean result");
    check(runtime.ready() && image(runtime) == before,
          std::string(label) + ": retry changed the runtime or retained its lease");
  }
  throw std::runtime_error(std::string(label) + ": next fault sweep did not reach a successful step");
}

template <class Runtime, class MakeRuntime, class MakeCursor, class Image>
std::size_t sweep_later_next_faults(MakeRuntime make_runtime, MakeCursor make_cursor, Image image,
                                    const std::vector<Row>& expected, std::string_view label) {
  std::size_t failures = 0;
  bool saw_backtrack_and_bucket_reopen = false;
  for (std::ptrdiff_t step = 0; step < 96; ++step) {
    Runtime runtime = make_runtime();
    const auto before = image(runtime);
    auto cursor = make_cursor(runtime);
    check_startup(cursor, runtime.plan());
    std::vector<storage::Tuple> held;
    held.reserve(2);
    for (std::size_t i = 0; i < 2; ++i) {
      auto row = cursor.next();
      check(row && row->values() == expected[i],
            std::string(label) + ": prefix did not match the first two clean rows");
      held.push_back(std::move(*row));
    }
    check(cursor.metrics().results.rows_emitted == 2,
          std::string(label) + ": pre-injection results were not charged before the later next call");
    const auto sequence = cursor.sequence();

    bool allocation_failed = false;
    std::optional<storage::Tuple> third;
    try {
      FaultScope fault(step);
      third = cursor.next();
    } catch (const std::bad_alloc&) {
      allocation_failed = true;
    }
    if (!allocation_failed) {
      check(third && third->values() == expected[2],
            std::string(label) + ": successful later next did not return the third expected row");
      check(cursor.metrics().results.rows_emitted == 3 && cursor.active(),
            std::string(label) + ": successful later next lost its result phase or lease");
      cursor.cancel();
      check(runtime.ready(), std::string(label) + ": successful later-next cancellation retained a lease");
      check(held[0].values() == expected[0] && held[1].values() == expected[1],
            std::string(label) + ": prefix rows changed after a successful later next");
      check(saw_backtrack_and_bucket_reopen,
            std::string(label) + ": fault sweep never failed during deepest-frame backtracking and bucket reopen");
      return failures;
    }

    ++failures;
    check(cursor.state() == ResultCursorState::failed && !cursor.active() && runtime.ready(),
          std::string(label) + ": later-next bad_alloc did not fail and close the cursor");
    check(cursor.metrics().results.rows_emitted == 2 && cursor.metrics().failed.rows_emitted == 0 &&
              cursor.metrics().last.work == cursor.metrics().failed.work,
          std::string(label) + ": later-next failure corrupted its prior result phase");
    check_phase_sum(cursor.metrics());
    saw_backtrack_and_bucket_reopen = saw_backtrack_and_bucket_reopen ||
        (cursor.metrics().failed.frame_closes > 0 && cursor.metrics().failed.bucket_lookups > 0);
    check(image(runtime) == before && runtime.sequence() == sequence,
          std::string(label) + ": later-next failure changed state, sequence, or public handles");
    check(held[0].values() == expected[0] && held[1].values() == expected[1],
          std::string(label) + ": previously yielded owning rows changed after later-next failure");
    expect_error([&] { static_cast<void>(cursor.next()); }, "invalid_cursor");

    auto retry = make_cursor(runtime);
    check(retry.sequence() == sequence, std::string(label) + ": later-next retry captured a different epoch");
    check(drain(retry) == expected,
          std::string(label) + ": fresh cursor did not return the full clean result after later-next failure");
    check(runtime.ready() && image(runtime) == before,
          std::string(label) + ": fresh later-next retry changed state or retained its lease");
    check(held[0].values() == expected[0] && held[1].values() == expected[1],
          std::string(label) + ": previously yielded owning rows changed after a full retry");
  }
  check(saw_backtrack_and_bucket_reopen,
        std::string(label) + ": fault sweep never failed during deepest-frame backtracking and bucket reopen");
  throw std::runtime_error(std::string(label) + ": later-next fault sweep did not reach a successful step");
}

template <class Runtime, class MakeCursor, class Image>
void check_factory_work_limit(Runtime& runtime, MakeCursor make_cursor, Image image,
                              const std::vector<Row>& expected, std::string_view label) {
  const auto before = image(runtime);
  expect_error([&] {
    auto impossible = make_cursor(runtime, ResultCursorOptions{std::uint64_t{0}});
    static_cast<void>(impossible);
  }, "resource_limit");
  check(runtime.ready() && image(runtime) == before,
        std::string(label) + ": startup budget failure left a lease or changed state");
  auto retry = make_cursor(runtime, ResultCursorOptions{});
  check(drain(retry) == expected, std::string(label) + ": retry after startup budget failure was not complete");
  check(runtime.ready() && image(runtime) == before,
        std::string(label) + ": retry after startup budget failure changed state");
}

template <class Runtime, class MakeCursor, class Image>
void check_next_work_limit(Runtime& runtime, MakeCursor make_cursor, Image image,
                           const std::vector<Row>& expected, std::string_view label) {
  auto probe = make_cursor(runtime, ResultCursorOptions{});
  const auto startup_work = probe.metrics().startup.work;
  const auto first = probe.next();
  check(first && first->values() == expected.front(), std::string(label) + ": work probe missed first output");
  const auto result_work = probe.metrics().results.work;
  probe.cancel();
  check(result_work > 1, std::string(label) + ": work probe was too small to exercise a cursor budget");

  const auto before = image(runtime);
  const auto budget = startup_work + result_work - 1;
  auto limited = make_cursor(runtime, ResultCursorOptions{budget});
  check(limited.metrics().startup.work == startup_work, std::string(label) + ": startup work changed between probes");
  expect_error([&] { static_cast<void>(limited.next()); }, "resource_limit");
  check(limited.state() == ResultCursorState::failed && !limited.active() && runtime.ready(),
        std::string(label) + ": next work-limit failure did not close the failed cursor lease");
  check(limited.metrics().total_work == budget && limited.metrics().failed.work == result_work - 1,
        std::string(label) + ": work-limit failure did not stop at the measured abstract budget");
  check_phase_sum(limited.metrics());
  expect_error([&] { static_cast<void>(limited.next()); }, "invalid_cursor");
  check(image(runtime) == before, std::string(label) + ": work-limit failure changed runtime state");
  auto retry = make_cursor(runtime, ResultCursorOptions{});
  check(drain(retry) == expected, std::string(label) + ": retry after work-limit failure was not complete");
  check(image(runtime) == before && runtime.ready(), std::string(label) + ": work-limit retry changed state or retained a lease");
}

template <class Runtime, class MakeCursor, class Image, class Mutate>
void check_read_only_lease(Runtime& runtime, MakeCursor make_cursor, Image image, Mutate mutate,
                           const std::vector<Row>& expected, std::string_view label) {
  const auto before = image(runtime);
  auto cursor = make_cursor(runtime, ResultCursorOptions{});
  check(!runtime.ready() && cursor.active(), std::string(label) + ": active result cursor did not hold a read lease");
  check(image(runtime) == before, std::string(label) + ": ordinary snapshot reads changed state under a cursor lease");
  expect_error([&] { mutate(runtime); }, "runtime_busy");
  check(!runtime.ready() && image(runtime) == before,
        std::string(label) + ": rejected writer changed state or released the cursor lease");
  cursor.cancel();
  check(cursor.state() == ResultCursorState::cancelled && !cursor.active() && runtime.ready(),
        std::string(label) + ": cancellation did not release the final writer lease");
  auto retry = make_cursor(runtime, ResultCursorOptions{});
  check(!cursor.next() && drain(retry) == expected,
        std::string(label) + ": cancelled cursor did not stay empty or a new cursor was incomplete");
  mutate(runtime);
  check(runtime.ready(), std::string(label) + ": runtime was not writable after final cursor cancellation");
}

template <class Runtime, class MakeCursor, class Image>
void check_one_failed_lease_keeps_another(Runtime& runtime, MakeCursor make_cursor, Image image,
                                          const std::vector<Row>& expected, std::string_view label) {
  auto probe = make_cursor(runtime, ResultCursorOptions{});
  const auto startup_work = probe.metrics().startup.work;
  probe.cancel();
  const auto before = image(runtime);
  auto failing = make_cursor(runtime, ResultCursorOptions{startup_work});
  auto peer = make_cursor(runtime, ResultCursorOptions{});
  check(!runtime.ready(), std::string(label) + ": multiple cursors did not hold the runtime read-only");
  expect_error([&] { static_cast<void>(failing.next()); }, "resource_limit");
  check(failing.state() == ResultCursorState::failed && !failing.active() && peer.active() && !runtime.ready(),
        std::string(label) + ": one failed cursor released another cursor's lease");
  check(image(runtime) == before, std::string(label) + ": first cursor failure changed a shared runtime snapshot");
  check(drain(peer) == expected && runtime.ready(),
        std::string(label) + ": final cursor exhaustion did not release the writer lease");
  check(image(runtime) == before, std::string(label) + ": peer cursor changed state while draining");
}

template <class MakeRuntime, class Image>
void check_cursor_allocation_failure_preserves_yielded_row(const PhysicalPlan& plan,
                                                            MakeRuntime make_runtime, Image image) {
  std::optional<storage::Tuple> saved;
  {
    auto runtime = make_runtime();
    const auto before = image(runtime);
    auto cursor = runtime.results();
    saved = cursor.next();
    check(saved && saved->values() == expected_join_rows().front(), "yielded row fixture missed its first row");
    bool failed = false;
    try {
      // Scalar-view scratch is allocated first. The complete compact row is
      // admitted next, after every output field has been read; this allocation
      // must fail after a prior result was yielded.
      FaultScope fault(1);
      static_cast<void>(cursor.next());
    } catch (const std::bad_alloc&) {
      failed = true;
    }
    check(failed && cursor.state() == ResultCursorState::failed && !cursor.active() && runtime.ready(),
          "second-next ordinary-new failure did not close the cursor lease");
    check(cursor.metrics().failed.output_fields == cursor.layout().fields().size(),
          "second-next ordinary-new failure did not report every field read before native row admission");
    check(image(runtime) == before, "cursor failure changed state after an earlier row was yielded");
    expect_error([&] { static_cast<void>(cursor.next()); }, "invalid_cursor");
    static_cast<void>(runtime.apply({runtime.sequence() + 1, TableId{0}, SetOperation::erase, left_row(1)}));
    runtime.check_invariants();
  }
  check(saved && saved->values() == expected_join_rows().front() &&
            std::get<std::string_view>(saved->values()[0]) == long_key(),
        "previously yielded owning row became invalid after failure, update, or facade destruction");
  static_cast<void>(plan);
}

void check_no_allocation_cleanup(const PhysicalPlan& plan) {
  auto support = make_support_join(plan);
  {
    auto cursor = support.results();
    {
      FaultScope no_allocations;
      no_allocations.forbid_allocations();
      cursor.cancel();
    }
    check(cursor.state() == ResultCursorState::cancelled && support.ready(),
          "cancel requested intercepted ordinary new or retained a SupportRuntime cursor lease");
  }

  auto physical = make_physical_join(plan);
  std::optional<ResultCursor> destroyed;
  destroyed.emplace(physical.results());
  {
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    destroyed.reset();
  }
  check(physical.ready(), "cursor destruction requested intercepted ordinary new or retained a PhysicalRuntime lease");

  auto destination_runtime = make_physical_join(plan);
  auto source_runtime = make_physical_join(plan);
  auto destination = destination_runtime.results();
  auto source = source_runtime.results();
  bool transferred = false;
  {
    FaultScope no_allocations;
    no_allocations.forbid_allocations();
    destination = std::move(source);
    transferred = destination.active() && !source.active() && destination_runtime.ready() &&
                  !source_runtime.ready();
    destination.cancel();
    transferred = transferred && source_runtime.ready();
  }
  check(transferred, "cursor move assignment requested intercepted ordinary new or failed to release/transfer reader leases");
  expect_error([&] { static_cast<void>(source.next()); }, "invalid_cursor");
}

void check_active_facade_moves_and_destruction(const PhysicalPlan& plan) {
  std::optional<ResultCursor> cursor;
  const auto expected = expected_join_rows();
  {
    PhysicalRuntime original{plan, runtime_options()};
    static_cast<void>(original.apply({1, TableId{0}, SetOperation::insert, left_row(1)}));
    static_cast<void>(original.apply({2, TableId{0}, SetOperation::insert, left_row(2)}));
    static_cast<void>(original.apply({3, TableId{1}, SetOperation::insert, right_row(10)}));
    static_cast<void>(original.apply({4, TableId{1}, SetOperation::insert, right_row(20)}));
    cursor.emplace(original.results());
    PhysicalRuntime moved(std::move(original));
    check(!moved.ready() && cursor->active(), "moving an active facade detached its result cursor lease");
  }
  check(cursor->active(), "destroying the moved facade invalidated the active cursor");
  check(drain(*cursor) == expected, "cursor could not resume and clean up after facade movement and destruction");
}

void check_sql_outputs_and_exists(const PhysicalPlan& output_plan, const PhysicalPlan& boolean_plan) {
  PhysicalRuntime runtime{output_plan, runtime_options()};
  static_cast<void>(runtime.apply({1, TableId{0}, SetOperation::insert, {n(7)}}));
  auto first = runtime.results();
  auto second = runtime.results();
  check(first.layout().same_token(second.layout()), "SQL cursors did not share their runtime output layout token");
  check_startup(first, output_plan);
  const Row sql_row{n(7), s(long_sql_constant()), n(7)};
  check(drain(first) == std::vector<Row>{sql_row}, "SQL result mapping lost repeated or constant outputs");
  second.cancel();
  check(runtime.ready(), "second SQL cursor cancellation did not release its lease");
  auto core = runtime.core_results();
  check_startup(core, output_plan);
  const Row core_row(output_plan.query().head.size(), n(7));
  check(drain(core) == std::vector<Row>{core_row}, "core cursor did not retain its core output mapping");

  PhysicalRuntime boolean{boolean_plan, runtime_options()};
  static_cast<void>(boolean.apply({1, TableId{0}, SetOperation::insert, {n(1)}}));
  auto exists = boolean.results();
  check_startup(exists, boolean_plan, true);
  check(exists.metrics().startup.frame_initializations == 0,
        "SQL EXISTS startup initialized enumeration frames despite its scalar wrapper");
  const auto answer = exists.next();
  check(answer && answer->values() == Row{Value{true}} && exists.metrics().results.rows_emitted == 1,
        "SQL EXISTS cursor did not emit its scalar result in the output phase");
  check(!exists.next() && exists.state() == ResultCursorState::exhausted &&
            exists.metrics().termination.calls == 1 && exists.metrics().termination.rows_emitted == 0,
        "SQL EXISTS cursor did not phase its scalar null termination");
  check(boolean.ready(), "SQL EXISTS cursor did not release its lease after termination");
}

}  // namespace

int main() {
  try {
    const auto plan = join_plan();
    const auto output_plan = sql_output_plan();
    const auto boolean_plan = exists_plan();
    const auto expected = expected_join_rows();

    auto make_support = [&] { return make_support_join(plan); };
    auto make_physical = [&] { return make_physical_join(plan); };
    auto support_cursor = [](auto& runtime, ResultCursorOptions options = {}) { return runtime.results(options); };
    auto physical_cursor = [](auto& runtime, ResultCursorOptions options = {}) { return runtime.results(options); };
    auto physical_core_cursor = [](auto& runtime, ResultCursorOptions options = {}) { return runtime.core_results(options); };
    auto support_image = [](const SupportRuntime& runtime) { return state_image(runtime); };
    auto physical_image = [](const PhysicalRuntime& runtime) { return state_image(runtime); };

    const auto support_factory_points = sweep_factory_faults<SupportRuntime>(make_support, support_cursor, support_image,
                                                                             "SupportRuntime result factory");
    const auto physical_factory_points = sweep_factory_faults<PhysicalRuntime>(make_physical, physical_cursor, physical_image,
                                                                               "PhysicalRuntime result factory");
    const auto core_factory_points = sweep_factory_faults<PhysicalRuntime>(make_physical, physical_core_cursor,
                                                                            physical_image, "PhysicalRuntime core result factory");
    check(support_factory_points > 0 && physical_factory_points > 0,
          "factory ordinary-new sweeps missed injected failure points");

    NextFailureKinds support_kinds, physical_kinds, core_kinds;
    const auto support_next_points = sweep_next_faults<SupportRuntime>(make_support, support_cursor, support_image,
                                                                        expected, support_kinds,
                                                                        "SupportRuntime next");
    const auto physical_next_points = sweep_next_faults<PhysicalRuntime>(make_physical, physical_cursor, physical_image,
                                                                          expected, physical_kinds,
                                                                          "PhysicalRuntime next");
    const auto core_next_points = sweep_next_faults<PhysicalRuntime>(make_physical, physical_core_cursor, physical_image,
                                                                      expected, core_kinds,
                                                                      "PhysicalRuntime core next");
    const auto later_next_points = sweep_later_next_faults<PhysicalRuntime>(make_physical, physical_core_cursor,
                                                                             physical_image, expected,
                                                                             "PhysicalRuntime later next");
    const auto covers_join_allocations = [](const NextFailureKinds& kinds) {
      return kinds.live_cursor_open && kinds.key_projection && kinds.bucket_cursor_open && kinds.result_assembly;
    };
    check(support_next_points > 0 && physical_next_points > 0 && core_next_points > 0 && later_next_points > 0 &&
              core_factory_points > 0 &&
              covers_join_allocations(support_kinds) && covers_join_allocations(physical_kinds) &&
              covers_join_allocations(core_kinds),
          "next ordinary-new sweeps missed live/bucket opening, key projection, or output assembly");

    auto sql_runtime_factory = [&] {
      PhysicalRuntime runtime{output_plan, runtime_options()};
      static_cast<void>(runtime.apply({1, TableId{0}, SetOperation::insert, {n(7)}}));
      return runtime;
    };
    auto sql_cursor = [](auto& runtime, ResultCursorOptions options = {}) { return runtime.results(options); };
    const std::vector<Row> sql_expected{{n(7), s(long_sql_constant()), n(7)}};
    const auto sql_factory_points = sweep_factory_faults<PhysicalRuntime>(sql_runtime_factory, sql_cursor,
                                                                          physical_image, "SQL result factory");
    NextFailureKinds sql_kinds;
    const auto sql_next_points = sweep_next_faults<PhysicalRuntime>(sql_runtime_factory, sql_cursor, physical_image,
                                                                     sql_expected, sql_kinds,
                                                                     "SQL result mapping next");
    check(sql_factory_points > 0 && sql_next_points > 0 && sql_kinds.sql_mapping,
          "SQL ordinary-new sweeps missed factory or long constant-output mapping failure points");

    auto support_budget_runtime = make_support();
    auto physical_budget_runtime = make_physical();
    check_factory_work_limit(support_budget_runtime, support_cursor, support_image, expected,
                             "SupportRuntime startup work limit");
    check_factory_work_limit(physical_budget_runtime, physical_cursor, physical_image, expected,
                             "PhysicalRuntime startup work limit");
    check_next_work_limit(support_budget_runtime, support_cursor, support_image, expected,
                          "SupportRuntime next work limit");
    check_next_work_limit(physical_budget_runtime, physical_cursor, physical_image, expected,
                          "PhysicalRuntime next work limit");

    auto support_readonly = make_support();
    auto physical_readonly = make_physical();
    auto mutate_support = [](SupportRuntime& runtime) {
      static_cast<void>(runtime.apply({runtime.sequence() + 1, NodeId{1}, SetOperation::insert, left_row(99)}));
    };
    auto mutate_physical = [](PhysicalRuntime& runtime) {
      static_cast<void>(runtime.apply({runtime.sequence() + 1, TableId{0}, SetOperation::insert, left_row(99)}));
    };
    check_read_only_lease(support_readonly, support_cursor, support_image, mutate_support, expected,
                          "SupportRuntime read lease");
    check_read_only_lease(physical_readonly, physical_cursor, physical_image, mutate_physical, expected,
                          "PhysicalRuntime read lease");

    auto support_multiple = make_support();
    auto physical_multiple = make_physical();
    check_one_failed_lease_keeps_another(support_multiple, support_cursor, support_image, expected,
                                         "SupportRuntime multiple cursors");
    check_one_failed_lease_keeps_another(physical_multiple, physical_cursor, physical_image, expected,
                                         "PhysicalRuntime multiple cursors");

    check_cursor_allocation_failure_preserves_yielded_row(plan, make_physical, physical_image);
    check_no_allocation_cleanup(plan);
    check_active_facade_moves_and_destruction(plan);
    check_sql_outputs_and_exists(output_plan, boolean_plan);

    std::cout << "result cursor ordinary-new failure points: support_factory=" << support_factory_points
              << " physical_factory=" << physical_factory_points
              << " core_factory=" << core_factory_points << " support_next=" << support_next_points
              << " physical_next=" << physical_next_points << " core_next=" << core_next_points
              << " later_next=" << later_next_points
              << " sql_factory=" << sql_factory_points << " sql_next=" << sql_next_points << '\n';
  } catch (const std::exception& failure) {
    fail_after = -1;
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
