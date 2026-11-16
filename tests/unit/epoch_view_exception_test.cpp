#include "crown/api/error.hpp"
#include "crown/io/support.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/physical.hpp"
#include "crown/storage/reference.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
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

// This executable owns a persistent global-new injector so factory and next
// failures unwind through the same no-allocation cleanup path being checked.
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
using View = SupportRuntime::EpochView;
using Cursor = SupportRuntime::ResultCursor;

static_assert(std::is_nothrow_move_constructible_v<SupportRuntime::PendingEpoch>);
static_assert(std::is_nothrow_move_assignable_v<SupportRuntime::PendingEpoch>);
static_assert(std::is_nothrow_move_constructible_v<PhysicalRuntime::PendingUpdate>);
static_assert(std::is_nothrow_move_assignable_v<PhysicalRuntime::PendingUpdate>);
static_assert(std::is_nothrow_move_constructible_v<View>);
static_assert(std::is_nothrow_move_assignable_v<View>);

void check(bool condition, std::string_view message) {
  if (!condition) throw std::runtime_error(std::string(message));
}

template <class Action>
void expect_error(Action&& action, std::string_view code) {
  try {
    std::forward<Action>(action)();
  } catch (const Error& failure) {
    check(failure.code() == code, "unexpected epoch-view error code");
    return;
  }
  throw std::runtime_error("expected epoch-view error code " + std::string(code));
}

Value n(std::int64_t value) { return value; }
Value s(std::string value) { return value; }
Row a_row(std::int64_t x, std::int64_t y, std::string witness) {
  return {n(x), n(y), s(std::move(witness))};
}
Row b_row(std::int64_t x, std::int64_t y, std::string witness) {
  return {n(x), n(y), s(std::move(witness))};
}
Row c_row(std::int64_t x, std::int64_t z, std::string witness) {
  return {n(x), n(z), s(std::move(witness))};
}

const Row& inserted_a() { static const Row value = a_row(3, 30, "a-3"); return value; }
const Row& inserted_b() { static const Row value = b_row(3, 30, "b-3"); return value; }
const Row& inserted_c() { static const Row value = c_row(3, 9, "a-3"); return value; }
const Row& erased_b() { static const Row value = b_row(1, 10, "b-10"); return value; }
const Row& later_a() { static const Row value = a_row(4, 40, "a-4"); return value; }
const Row& later_b() { static const Row value = b_row(1, 11, "b-11"); return value; }

constexpr VariableId x{0};
constexpr VariableId y{1};
constexpr VariableId z{2};
constexpr VariableId a_witness{3};
constexpr VariableId b_witness{4};

PhysicalPlan make_plan() {
  const Catalog catalog{73, {
      {"A", {{"x", ScalarType::int64}, {"y", ScalarType::int64}, {"a_witness", ScalarType::string}}},
      {"B", {{"x", ScalarType::int64}, {"y", ScalarType::int64}, {"b_witness", ScalarType::string}}},
      {"C", {{"x", ScalarType::int64}, {"z", ScalarType::int64}, {"c_witness", ScalarType::string}}}}};
  const Query query{
      {{"x", ScalarType::int64}, {"y", ScalarType::int64}, {"z", ScalarType::int64},
       {"a_witness", ScalarType::string}, {"b_witness", ScalarType::string}},
      {{"a", TableId{0}, {x, y, a_witness}},
       {"b", TableId{1}, {x, y, b_witness}},
       {"c", TableId{2}, {x, z, a_witness}}},
      {{x, "x"}, {y, "y"}}, false};
  // C shares A's hidden witness and contributes to the query, but lies outside
  // the root-connected C* subtree for visible head {x,y}.
  const FreeConnexTree tree{NodeId{0}, {
      {"root", NodeKind::generalized, {x, y}, {NodeId{1}, NodeId{2}}, {}, {}},
      {"a", NodeKind::native, {x, y, a_witness}, {NodeId{3}}, 0, {}},
      {"b", NodeKind::native, {x, y, b_witness}, {}, 1, {}},
      {"c", NodeKind::native, {x, z, a_witness}, {}, 2, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

SupportOptions support_options() {
  SupportOptions result;
  result.capture_transitions = true;
  return result;
}

PhysicalRuntimeOptions physical_options() {
  PhysicalRuntimeOptions result;
  result.support = support_options();
  return result;
}

const std::vector<Row>& a_rows() {
  static const std::vector<Row> value{
      a_row(1, 10, "a-10"), a_row(1, 11, "a-11"), a_row(1, 12, "a-12"), a_row(2, 20, "a-20")};
  return value;
}
const std::vector<Row>& b_rows() {
  static const std::vector<Row> value{
      b_row(1, 10, "b-10"), b_row(1, 11, "b-11"), b_row(1, 12, "b-12"), b_row(2, 20, "b-20")};
  return value;
}
const std::vector<Row>& c_rows() {
  static const std::vector<Row> value{c_row(1, 7, "a-10"), c_row(1, 8, "a-11"),
                                      c_row(1, 9, "a-12"), c_row(2, 8, "a-20")};
  return value;
}
const std::vector<Row>& base_results() {
  static const std::vector<Row> value{{n(1), n(10)}, {n(1), n(11)}, {n(1), n(12)}, {n(2), n(20)}};
  return value;
}
const std::vector<Row>& inserted_results() {
  static const std::vector<Row> value{
      {n(1), n(10)}, {n(1), n(11)}, {n(1), n(12)}, {n(2), n(20)}, {n(3), n(30)}};
  return value;
}
const std::vector<Row>& erased_results() {
  static const std::vector<Row> value{{n(1), n(11)}, {n(1), n(12)}, {n(2), n(20)}};
  return value;
}
const std::vector<Row>& x_one_results() {
  static const std::vector<Row> value{{n(1), n(10)}, {n(1), n(11)}, {n(1), n(12)}};
  return value;
}

SupportRuntime make_support(const PhysicalPlan& plan) {
  SupportRuntime runtime{plan, support_options()};
  std::uint64_t sequence = 1;
  for (const auto& row : a_rows())
    static_cast<void>(runtime.apply({sequence++, NodeId{1}, SetOperation::insert, row}));
  for (const auto& row : b_rows())
    static_cast<void>(runtime.apply({sequence++, NodeId{2}, SetOperation::insert, row}));
  for (const auto& row : c_rows())
    static_cast<void>(runtime.apply({sequence++, NodeId{3}, SetOperation::insert, row}));
  check(runtime.sequence() == sequence - 1 && runtime.has_answer(), "support epoch-view fixture did not initialize");
  runtime.check_invariants();
  return runtime;
}

PhysicalRuntime make_physical(const PhysicalPlan& plan) {
  PhysicalRuntime runtime{plan, physical_options()};
  std::uint64_t sequence = 1;
  for (const auto& row : a_rows())
    static_cast<void>(runtime.apply({sequence++, TableId{0}, SetOperation::insert, row}));
  for (const auto& row : b_rows())
    static_cast<void>(runtime.apply({sequence++, TableId{1}, SetOperation::insert, row}));
  for (const auto& row : c_rows())
    static_cast<void>(runtime.apply({sequence++, TableId{2}, SetOperation::insert, row}));
  check(runtime.sequence() == sequence - 1 && runtime.has_answer(), "physical epoch-view fixture did not initialize");
  runtime.check_invariants();
  return runtime;
}

io::Json row_image(const Row& row) {
  auto result = io::Json::array();
  for (const auto& value : row) result.push_back(io::write_scalar(value));
  return result;
}

io::Json support_snapshot_image(const SupportSnapshot& snapshot, const auto& plan) {
  return {{"sequence", snapshot.sequence}, {"answer", snapshot.has_answer},
          {"support", io::write_support_snapshot(snapshot, plan)}};
}

io::Json state_image(const SupportRuntime& runtime) {
  return support_snapshot_image(runtime.snapshot(), runtime.plan());
}

io::Json physical_snapshot_image(const PhysicalSnapshot& snapshot, const auto& plan) {
  auto physical = io::Json::array();
  for (const auto& table : snapshot.physical.tables) {
    auto rows = io::Json::array();
    for (const auto& row : table) rows.push_back(row_image(row));
    physical.push_back(std::move(rows));
  }
  auto derivations = io::Json::array();
  for (const auto& occurrence : snapshot.derivations) {
    auto rows = io::Json::array();
    for (const auto& item : occurrence)
      rows.push_back({{"values", row_image(crown::storage::export_row(item.tuple.values()))}, {"count", item.count}});
    derivations.push_back(std::move(rows));
  }
  return {{"sequence", snapshot.sequence}, {"physical", std::move(physical)},
          {"derivations", std::move(derivations)},
          {"support", io::write_support_snapshot(snapshot.support, plan)}};
}

io::Json state_image(const PhysicalRuntime& runtime) {
  const auto snapshot = runtime.snapshot();
  auto result = physical_snapshot_image(snapshot, runtime.plan());
  auto handles = io::Json::array();
  for (std::size_t table = 0; table < snapshot.physical.tables.size(); ++table) {
    for (const auto& row : snapshot.physical.tables[table]) {
      const auto handle = runtime.find_source(TableId{table}, row);
      check(handle.has_value(), "physical epoch-view row lost its public source handle");
      const auto stored = runtime.get_source(TableId{table}, *handle);
      check(stored && stored->values() == row, "physical epoch-view handle did not resolve");
      handles.push_back({{"table", table}, {"owner", handle->owner.value},
                         {"relation", handle->relation.value}, {"tuple", handle->tuple.value}});
    }
  }
  result["source_handles"] = std::move(handles);
  return result;
}

io::Json pending_image(const SupportRuntime::PendingEpoch& pending, const PhysicalPlan& plan) {
  return support_snapshot_image(pending.snapshot(), plan);
}

io::Json pending_image(const PhysicalRuntime::PendingUpdate& pending, const PhysicalPlan& plan) {
  auto result = physical_snapshot_image(pending.snapshot(), plan);
  const auto& source = pending.preview().source;
  if (source) {
    const auto& handle = source->handle;
    result["pending_source"] = {{"owner", handle.owner.value}, {"relation", handle.relation.value},
                                {"tuple", handle.tuple.value}, {"values", row_image(storage::export_row(source->tuple().values()))}};
  }
  return result;
}

void sort_rows(std::vector<Row>& rows) {
  std::sort(rows.begin(), rows.end(), [](const Row& left, const Row& right) {
    const auto lx = std::get<std::int64_t>(left[0]);
    const auto rx = std::get<std::int64_t>(right[0]);
    if (lx != rx) return lx < rx;
    if (left.size() > 1 && right.size() > 1) return std::get<std::int64_t>(left[1]) < std::get<std::int64_t>(right[1]);
    return false;
  });
}

std::vector<Row> drain(Cursor& cursor) {
  std::vector<Row> result;
  for (;;) {
    auto item = cursor.next();
    if (!item) break;
    result.push_back(crown::storage::export_row(item->values()));
  }
  sort_rows(result);
  check(cursor.state() == ResultCursorState::exhausted && !cursor.active(),
        "epoch-view result cursor did not close at exhaustion");
  return result;
}

std::vector<Row> drain(SupportRuntime::EpochView& view, ResultCursorOptions options = {}) {
  auto cursor = view.results(options);
  return drain(cursor);
}

void check_support_view_factory_sweep(const PhysicalPlan& plan, SnapshotSide side, bool erase) {
  std::size_t failures = 0;
  for (std::ptrdiff_t step = 0; step < 256; ++step) {
    auto runtime = make_support(plan);
    const auto committed = state_image(runtime);
    auto pending = runtime.begin_epoch(runtime.sequence() + 1, erase ? SetOperation::erase : SetOperation::insert);
    if (erase) {
      check(pending.stage(NodeId{2}, erased_b()), "support delete view-factory fixture was a no-op");
    } else {
      check(pending.stage(NodeId{1}, inserted_a()), "support insert view-factory A stage was a no-op");
      check(pending.stage(NodeId{2}, inserted_b()), "support insert view-factory B stage was a no-op");
      check(pending.stage(NodeId{3}, inserted_c()), "support insert view-factory C stage was a no-op");
    }
    const auto tentative = pending_image(pending, plan);
    bool failed = false;
    try {
      FaultScope fault(step);
      auto view = pending.view(side);
      view.close();
    } catch (const std::bad_alloc&) {
      failed = true;
    }
    if (!failed) {
      check(failures > 0, "SupportRuntime view factory sweep missed its allocation failures");
      check(pending.active() && pending_image(pending, plan) == tentative,
            "successful SupportRuntime view factory changed the drained pending prefix");
      pending.rollback();
      check(runtime.ready() && state_image(runtime) == committed,
            "successful SupportRuntime view factory retained a lease or changed committed state");
      std::cout << "support view factory side=" << (side == SnapshotSide::before ? "before" : "after")
                << " erase=" << erase << " failures=" << failures << '\n';
      return;
    }

    ++failures;
    check(pending.active() && pending_image(pending, plan) == tentative,
          "SupportRuntime view factory bad_alloc changed its pending epoch or sequence");
    auto retry = pending.view(side);
    const auto expected = erase ? (side == SnapshotSide::before ? base_results() : erased_results())
                                : (side == SnapshotSide::before ? base_results() : inserted_results());
    check(drain(retry) == expected, "SupportRuntime view retry did not match the clean before/after prefix");
    retry.close();
    if (erase) {
      check(pending.stage(NodeId{2}, later_b()),
            "failed SupportRuntime erase view factory left the pending epoch unstaged");
    } else {
      check(pending.stage(NodeId{1}, later_a()),
            "failed SupportRuntime insert view factory left the pending epoch unstaged");
    }
    pending.rollback();
    check(runtime.ready() && state_image(runtime) == committed,
          "SupportRuntime view retry leaked a reader or changed committed handles");
  }
  throw std::runtime_error("SupportRuntime view-factory fault sweep did not reach success");
}

void check_physical_view_factory_sweep(const PhysicalPlan& plan, SnapshotSide side) {
  std::size_t failures = 0;
  for (std::ptrdiff_t step = 0; step < 256; ++step) {
    auto runtime = make_physical(plan);
    const auto committed = state_image(runtime);
    auto pending = runtime.prepare({runtime.sequence() + 1, TableId{0}, SetOperation::insert, inserted_a()});
    const auto tentative = pending_image(pending, plan);
    bool failed = false;
    try {
      FaultScope fault(step);
      auto view = pending.view(side);
      view.close();
    } catch (const std::bad_alloc&) {
      failed = true;
    }
    if (!failed) {
      check(failures > 0, "physical view factory sweep missed its allocation failures");
      check(pending.active() && pending_image(pending, plan) == tentative,
            "physical view factory changed its prepared source update");
      pending.rollback();
      check(runtime.ready() && state_image(runtime) == committed,
            "physical view factory retained a lease or changed committed source handles");
      std::cout << "physical view factory side=" << (side == SnapshotSide::before ? "before" : "after")
                << " failures=" << failures << '\n';
      return;
    }
    ++failures;
    check(pending.active() && pending_image(pending, plan) == tentative,
          "physical view factory bad_alloc changed the source/kernel pending prefix");
    auto retry = pending.view(side);
    check(drain(retry) == base_results(), "physical view retry did not match the clean visible prefix");
    retry.close();
    pending.rollback();
    check(runtime.ready() && state_image(runtime) == committed,
          "physical view retry leaked a reader or changed committed source handles");
  }
  throw std::runtime_error("PhysicalRuntime view-factory fault sweep did not reach success");
}

void check_completion_factory_sweep(const PhysicalPlan& plan, bool physical) {
  std::size_t failures = 0;
  for (std::ptrdiff_t step = 0; step < 256; ++step) {
    std::optional<SupportRuntime> support;
    std::optional<PhysicalRuntime> coordinator;
    View view = [&]() {
      if (physical) {
        coordinator.emplace(make_physical(plan));
        return coordinator->current_view();
      }
      support.emplace(make_support(plan));
      return support->current_view();
    }();
    const auto committed = physical ? state_image(*coordinator) : state_image(*support);
    bool failed = false;
    try {
      FaultScope fault(step);
      auto cursor = view.completions({{x, n(1)}}, VisibleFragment{NodeId{0}});
      cursor.cancel();
    } catch (const std::bad_alloc&) {
      failed = true;
    }
    if (!failed) {
      check(failures > 0, "completions factory sweep missed its allocation failures");
      check(view.valid(), "successful completions factory invalidated its source view");
      view.close();
      check((physical ? coordinator->ready() : support->ready()) &&
                (physical ? state_image(*coordinator) : state_image(*support)) == committed,
            "successful completions factory leaked a cursor lease or changed readonly state");
      std::cout << "completions factory runtime=" << (physical ? "physical" : "support")
                << " failures=" << failures << '\n';
      return;
    }
    ++failures;
    check(view.valid() && !(physical ? coordinator->ready() : support->ready()),
          "completions factory bad_alloc invalidated the view or released its guard");
    auto retry = view.completions({{x, n(1)}}, VisibleFragment{NodeId{0}});
    check(drain(retry) == x_one_results(), "completions factory retry returned a different visible set");
    view.close();
    check((physical ? coordinator->ready() : support->ready()) &&
              (physical ? state_image(*coordinator) : state_image(*support)) == committed,
          "completions factory retry leaked a cursor lease or changed readonly state");
  }
  throw std::runtime_error("epoch-view completions-factory fault sweep did not reach success");
}

void check_completion_validation(const PhysicalPlan& plan) {
  auto runtime = make_support(plan);
  const auto before = state_image(runtime);
  auto view = runtime.current_view();
  expect_error([&] { static_cast<void>(view.completions({{x, s("wrong type")}})); }, "invalid_binding");
  expect_error([&] { static_cast<void>(view.completions({{x, n(1)}, {x, n(2)}})); }, "invalid_binding");
  expect_error([&] { static_cast<void>(view.completions({{VariableId{99}, n(1)}})); }, "invalid_binding");
  auto hidden_restriction = view.completions({{a_witness, s("a-10")}});
  check(drain(hidden_restriction) == std::vector<Row>{{n(1), n(10)}},
        "hidden completion binding did not restrict full witnesses before projection");
  expect_error([&] { static_cast<void>(view.completions({}, VisibleFragment{NodeId{3}})); }, "invalid_fragment");
  expect_error([&] { static_cast<void>(view.completions({}, VisibleFragment{NodeId{99}})); }, "invalid_fragment");
  check(drain(view) == base_results(), "current snapshot view results differ from committed support output");
  auto whole = view.completions({}, VisibleFragment{NodeId{0}});
  check(drain(whole) == base_results(), "full C* fragment did not return sorted visible variables");
  check(view.valid(), "invalid completion requests closed their source view");
  view.close();
  check(runtime.ready() && state_image(runtime) == before,
        "invalid completion requests leaked a reader or changed public handles");
}

void check_completions_filter_paths(const PhysicalPlan& plan) {
  auto runtime = make_support(plan);
  auto view = runtime.current_view();
  auto partial = view.completions({{x, n(1)}});
  check(drain(partial) == x_one_results(), "partial visible binding did not filter the live root bucket");
  const auto& partial_metrics = partial.metrics();
  check(partial_metrics.results.binding_checks > 0 &&
            partial_metrics.results.binding_rejections + partial_metrics.termination.binding_rejections > 0 &&
            partial_metrics.results.bucket_lookups + partial_metrics.results.direct_lookups +
                partial_metrics.termination.bucket_lookups + partial_metrics.termination.direct_lookups > 0,
        "partial binding did not exercise filtered live rows and a concrete factor lookup path");

  auto direct = view.completions({{x, n(1)}, {y, n(11)}});
  check(drain(direct) == std::vector<Row>{{n(1), n(11)}},
        "fully fixed visible row did not use its exact primary lookup result");
  const auto& direct_work = direct.metrics().results;
  check(direct_work.direct_lookups > 0,
        "fully fixed completion did not exercise direct primary lookups");
  view.close();
  check(runtime.ready(), "filtered completion cursors kept the committed runtime read-only");
}

void check_rollback_aborts_linked_cursors_noalloc(const PhysicalPlan& plan) {
  auto runtime = make_support(plan);
  auto pending = runtime.begin_epoch(runtime.sequence() + 1, SetOperation::insert);
  check(pending.stage(NodeId{1}, inserted_a()) && pending.stage(NodeId{2}, inserted_b()) &&
            pending.stage(NodeId{3}, inserted_c()), "rollback abort fixture did not stage its visible row");
  auto view = pending.view(SnapshotSide::after);
  auto copy = view;
  auto first = view.results();
  auto second = copy.results();
  auto saved = first.next();
  check(saved && first.active() && second.active(), "rollback fixture did not keep two active cursors");
  bool noalloc = true;
  {
    FaultScope fault;
    fault.forbid_allocations();
    pending.rollback();
    noalloc = !pending.active() && !view.valid() && !copy.valid() &&
        first.state() == ResultCursorState::failed && second.state() == ResultCursorState::failed &&
        !first.active() && !second.active();
  }
  check(noalloc, "rolling back a view with two linked cursors allocated or failed to unlink the list head");
  check(runtime.ready() && saved->values() == base_results().front(),
        "aborted view lease survived rollback or invalidated an already returned owning row");
  auto retry = runtime.begin_epoch(runtime.sequence() + 1, SetOperation::insert);
  check(retry.stage(NodeId{1}, later_a()), "held aborted view prevented a new epoch from staging");
  retry.rollback();
  view.close();
  copy.close();
  runtime.check_invariants();
}

void check_commit_preserves_views_noalloc(const PhysicalPlan& plan) {
  auto runtime = make_support(plan);
  const auto sequence = runtime.sequence();
  auto pending = runtime.begin_epoch(sequence + 1, SetOperation::insert);
  check(pending.stage(NodeId{1}, inserted_a()) && pending.stage(NodeId{2}, inserted_b()) &&
            pending.stage(NodeId{3}, inserted_c()), "commit fixture did not stage its matching row");
  auto before = pending.view(SnapshotSide::before);
  auto after = pending.view(SnapshotSide::after);
  auto after_copy = after;
  auto before_cursor = before.results();
  auto after_cursor = after.results();
  auto saved_before = before_cursor.next();
  auto saved_after = after_cursor.next();
  check(saved_before && saved_after && before_cursor.active() && after_cursor.active(),
        "commit fixture did not start both snapshot cursors");

  std::optional<SupportEpoch> output;
  {
    FaultScope fault;
    fault.forbid_allocations();
    output.emplace(pending.commit());
  }
  check(output && !pending.active() && runtime.sequence() == sequence + 1 &&
            !runtime.ready() && before.valid() && after.valid() && !after.tentative(),
        "no-allocation commit did not preserve both epoch views and their reader lease");
  check(before_cursor.sequence() == sequence && after_cursor.sequence() == sequence + 1,
        "committed before/after cursors captured the wrong fixed sequence");
  auto before_rows = drain(before_cursor);
  auto after_rows = drain(after_cursor);
  before_rows.push_back(crown::storage::export_row(saved_before->values()));
  after_rows.push_back(crown::storage::export_row(saved_after->values()));
  sort_rows(before_rows);
  sort_rows(after_rows);
  check(before_rows == base_results() && after_rows == inserted_results(),
        "view cursors did not finish their immutable before/after result sets after commit");
  before.close();
  after.close();
  check(!runtime.ready() && after_copy.valid(), "closing one copied view invalidated or released another copy");
  expect_error([&] {
    static_cast<void>(runtime.apply({runtime.sequence() + 1, NodeId{1}, SetOperation::insert, later_a()}));
  }, "runtime_busy");
  after_copy.close();
  check(runtime.ready(), "last copied view close did not release the writer lease");
  static_cast<void>(runtime.apply({runtime.sequence() + 1, NodeId{1}, SetOperation::insert, later_a()}));
  runtime.check_invariants();
}

void check_pending_move_cleanup_noalloc(const PhysicalPlan& plan) {
  auto destination_runtime = make_support(plan);
  auto source_runtime = make_support(plan);
  std::optional<SupportRuntime::PendingEpoch> destination;
  std::optional<SupportRuntime::PendingEpoch> source;
  destination.emplace(destination_runtime.begin_epoch(destination_runtime.sequence() + 1, SetOperation::insert));
  check(destination->stage(NodeId{1}, inserted_a()), "move destination did not stage");
  auto old_view = destination->view(SnapshotSide::after);
  auto old_cursor = old_view.results();
  check(old_cursor.next().has_value(), "move destination cursor did not yield");
  source.emplace(source_runtime.begin_epoch(source_runtime.sequence() + 1, SetOperation::insert));
  check(source->stage(NodeId{1}, inserted_a()), "move source did not stage");
  bool moved = false;
  {
    FaultScope fault;
    fault.forbid_allocations();
    *destination = std::move(*source);
    moved = destination->active() && !source->active() && !old_view.valid() &&
        old_cursor.state() == ResultCursorState::failed && !old_cursor.active();
  }
  check(moved && destination_runtime.ready() && !source_runtime.ready(),
        "no-allocation pending move assignment did not abort its destination view and cursor");
  auto new_view = destination->view(SnapshotSide::after);
  check(drain(new_view) == base_results(), "moved pending token did not retain the source runtime's epoch prefix");
  new_view.close();
  {
    FaultScope fault;
    fault.forbid_allocations();
    destination->rollback();
  }
  check(source_runtime.ready() && destination_runtime.ready(), "moved pending rollback leaked a runtime lease");
  old_view.close();
}

void check_pending_destruction_noalloc(const PhysicalPlan& plan) {
  auto runtime = make_support(plan);
  std::optional<View> view;
  std::optional<Cursor> first;
  std::optional<Cursor> second;
  std::optional<storage::Tuple> saved;
  std::optional<SupportRuntime::PendingEpoch> pending;
  {
    pending.emplace(runtime.begin_epoch(runtime.sequence() + 1, SetOperation::insert));
    check(pending->stage(NodeId{1}, inserted_a()), "destruction fixture did not stage");
    view.emplace(pending->view(SnapshotSide::after));
    first.emplace(view->results());
    second.emplace(view->results());
    saved = first->next();
    check(saved && first->active() && second->active(), "destruction fixture did not hold two cursors");
  }
  {
    FaultScope fault;
    fault.forbid_allocations();
    pending.reset();
  }
  check(view && !view->valid() && first->state() == ResultCursorState::failed &&
            second->state() == ResultCursorState::failed && runtime.ready(),
        "no-allocation pending destruction did not abort and release its linked views");
  check(saved && saved->values() == base_results().front(),
        "pending destruction invalidated an already returned owning result row");
  view->close();
}

void check_physical_pending_lifecycle_noalloc(const PhysicalPlan& plan) {
  auto runtime = make_physical(plan);
  auto pending = runtime.prepare({runtime.sequence() + 1, TableId{0}, SetOperation::insert, inserted_a()});
  auto view = pending.view(SnapshotSide::after);
  auto copy = view;
  auto first = view.results();
  auto second = copy.results();
  auto saved = first.next();
  check(saved && first.active() && second.active(), "physical pending fixture did not start its cursors");
  bool rolled_back = false;
  {
    FaultScope fault;
    fault.forbid_allocations();
    pending.rollback();
    rolled_back = !pending.active() && !view.valid() && !copy.valid() &&
        first.state() == ResultCursorState::failed && second.state() == ResultCursorState::failed;
  }
  check(rolled_back && runtime.ready() && saved->values() == base_results().front(),
        "physical rollback did not invalidate linked cursors and release its view lease without allocation");
  auto retry = runtime.prepare({runtime.sequence() + 1, TableId{0}, SetOperation::insert, later_a()});
  retry.rollback();

  auto next = runtime.prepare({runtime.sequence() + 1, TableId{0}, SetOperation::insert, inserted_a()});
  auto committed_view = next.view(SnapshotSide::after);
  auto committed_cursor = committed_view.results();
  auto saved_commit = committed_cursor.next();
  std::optional<PhysicalEpoch> output;
  {
    FaultScope fault;
    fault.forbid_allocations();
    output.emplace(next.commit());
  }
  check(output && committed_view.valid() && !committed_view.tentative() && !runtime.ready(),
        "physical no-allocation commit failed to preserve the delegated view");
  auto remaining = drain(committed_cursor);
  remaining.push_back(crown::storage::export_row(saved_commit->values()));
  sort_rows(remaining);
  check(remaining == base_results(), "physical view cursor changed after its source facade committed");
  committed_view.close();
  check(runtime.ready(), "closing the physical delegated view did not release its writer lease");
  runtime.check_invariants();

  auto destination_runtime = make_physical(plan);
  auto source_runtime = make_physical(plan);
  auto destination = destination_runtime.prepare({destination_runtime.sequence() + 1, TableId{0},
                                                   SetOperation::insert, inserted_a()});
  auto old_view = destination.view(SnapshotSide::after);
  auto old_cursor = old_view.results();
  check(old_cursor.next().has_value(), "physical move destination cursor did not yield");
  auto source = source_runtime.prepare({source_runtime.sequence() + 1, TableId{0},
                                        SetOperation::insert, later_a()});
  bool moved = false;
  {
    FaultScope fault;
    fault.forbid_allocations();
    destination = std::move(source);
    moved = destination.active() && !source.active() && !old_view.valid() &&
        old_cursor.state() == ResultCursorState::failed && !old_cursor.active();
  }
  check(moved && destination_runtime.ready() && !source_runtime.ready(),
        "physical pending move assignment did not abort its old view and cursor without allocation");
  auto moved_view = destination.view(SnapshotSide::after);
  check(drain(moved_view) == base_results(), "physical moved token lost its source-side epoch prefix");
  moved_view.close();
  {
    FaultScope fault;
    fault.forbid_allocations();
    destination.rollback();
  }
  check(destination_runtime.ready() && source_runtime.ready(),
        "physical moved pending rollback leaked a source or destination lease");

  auto destruction_runtime = make_physical(plan);
  std::optional<PhysicalRuntime::PendingUpdate> abandoned;
  View destruction_view = [&]() {
    abandoned.emplace(destruction_runtime.prepare({destruction_runtime.sequence() + 1, TableId{0},
                                                    SetOperation::insert, inserted_a()}));
    return abandoned->view(SnapshotSide::after);
  }();
  auto destruction_cursor = destruction_view.results();
  auto destruction_peer = destruction_view.results();
  check(destruction_cursor.next().has_value(), "physical destruction cursor did not yield");
  {
    FaultScope fault;
    fault.forbid_allocations();
    abandoned.reset();
  }
  check(!destruction_view.valid() && destruction_cursor.state() == ResultCursorState::failed &&
            destruction_peer.state() == ResultCursorState::failed && destruction_runtime.ready(),
        "physical pending destruction failed to abort its linked views without allocation");
  destruction_view.close();
}

void check_next_fault_sweep(const PhysicalPlan& plan, bool erase, SnapshotSide side, bool later) {
  std::size_t failures = 0;
  const auto& expected = erase ? (side == SnapshotSide::before ? base_results() : erased_results())
                              : (side == SnapshotSide::before ? base_results() : inserted_results());
  for (std::ptrdiff_t step = 0; step < 192; ++step) {
    auto runtime = make_support(plan);
    auto pending = runtime.begin_epoch(runtime.sequence() + 1, erase ? SetOperation::erase : SetOperation::insert);
    if (erase) {
      check(pending.stage(NodeId{2}, erased_b()), "delete next-fault fixture was a no-op");
    } else {
      check(pending.stage(NodeId{1}, inserted_a()) && pending.stage(NodeId{2}, inserted_b()) &&
                pending.stage(NodeId{3}, inserted_c()), "insert next-fault fixture did not stage all leaves");
    }
    auto view = pending.view(side);
    const auto tentative = pending_image(pending, plan);
    auto cursor = view.results();
    std::optional<storage::Tuple> first;
    std::optional<storage::Tuple> second;
    if (later) {
      first = cursor.next();
      second = cursor.next();
      check(first && second, "later next-fault fixture did not produce its clean prefix");
    }
    bool failed = false;
    std::optional<storage::Tuple> yielded;
    try {
      FaultScope fault(step);
      yielded = cursor.next();
    } catch (const std::bad_alloc&) {
      failed = true;
    }
    if (!failed) {
      check(failures > 0, "view next sweep missed its allocation failures");
      check(yielded.has_value() && cursor.active() && view.valid(),
            "successful view next sweep did not return a row with its view still held");
      cursor.cancel();
      view.close();
      pending.rollback();
      std::cout << "view next erase=" << erase << " side=" << (side == SnapshotSide::before ? "before" : "after")
                << " later=" << later << " failures=" << failures << '\n';
      return;
    }
    ++failures;
    check(cursor.state() == ResultCursorState::failed && !cursor.active() && view.valid() && pending.active(),
          "view next bad_alloc closed its guard or corrupted the pending epoch");
    if (later) {
      check(first && second && first->values() != second->values() && cursor.metrics().results.rows_emitted == 2,
            "later view next failure lost its previously returned owning rows");
    }
    check(pending_image(pending, plan) == tentative,
          "view next failure changed its pending overlay, handles, or sequence");
    expect_error([&] { static_cast<void>(cursor.next()); }, "invalid_cursor");
    auto retry = view.results();
    check(drain(retry) == expected, "view next retry did not return the clean before/after result set");
    view.close();
    pending.rollback();
    check(runtime.ready(), "view next fault cleanup leaked a read lease");
  }
  throw std::runtime_error("epoch-view next-fault sweep did not reach success");
}

void check_current_view_next_lease(const PhysicalPlan& plan, bool later) {
  std::size_t failures = 0;
  for (std::ptrdiff_t step = 0; step < 192; ++step) {
    auto runtime = make_support(plan);
    const auto before = state_image(runtime);
    auto view = runtime.current_view();
    auto cursor = view.completions({{x, n(1)}});
    auto peer = view.results();
    if (later) {
      check(cursor.next().has_value() && cursor.next().has_value(), "later current-view fault prefix was empty");
    }
    bool failed = false;
    try {
      FaultScope fault(step);
      static_cast<void>(cursor.next());
    } catch (const std::bad_alloc&) {
      failed = true;
    }
    if (!failed) {
      check(failures > 0, "current-view next sweep missed its allocation failures");
      cursor.cancel();
      peer.cancel();
      view.close();
      check(runtime.ready() && state_image(runtime) == before,
            "successful current-view next sweep changed readonly state or retained a lease");
      std::cout << "current-view next later=" << later << " failures=" << failures << '\n';
      return;
    }
    ++failures;
    check(cursor.state() == ResultCursorState::failed && !cursor.active() && peer.active() && view.valid(),
          "failed current-view cursor closed a peer or its shared view guard");
    if (later) check(cursor.metrics().results.rows_emitted == 2,
                     "later current-view failure corrupted the earlier result phase");
    expect_error([&] {
      static_cast<void>(runtime.apply({runtime.sequence() + 1, NodeId{1}, SetOperation::insert, later_a()}));
    }, "runtime_busy");
    auto retry = view.completions({{x, n(1)}});
    check(drain(retry) == x_one_results(), "failed current-view cursor could not be retried under its shared guard");
    peer.cancel();
    view.close();
    check(runtime.ready() && state_image(runtime) == before,
          "last current-view guard close did not restore writable unchanged state");
  }
  throw std::runtime_error("current-view next-fault lease sweep did not reach success");
}

void check_facade_destruction_stability(const PhysicalPlan& plan) {
  std::optional<View> support_view;
  std::optional<Cursor> support_cursor;
  std::optional<storage::Tuple> support_saved;
  {
    auto runtime = make_support(plan);
    auto pending = runtime.begin_epoch(runtime.sequence() + 1, SetOperation::insert);
    check(pending.stage(NodeId{1}, inserted_a()) && pending.stage(NodeId{2}, inserted_b()) &&
              pending.stage(NodeId{3}, inserted_c()), "facade-destruction support fixture did not stage");
    support_view.emplace(pending.view(SnapshotSide::after));
    support_cursor.emplace(support_view->results());
    support_saved = support_cursor->next();
    static_cast<void>(pending.commit());
  }
  check(support_view->valid() && support_cursor->active() && support_saved,
        "committed support view did not survive destruction of both facades");
  auto support_rows = drain(*support_cursor);
  support_rows.push_back(crown::storage::export_row(support_saved->values()));
  sort_rows(support_rows);
  check(support_rows == inserted_results(), "support facade destruction invalidated returned or future rows");
  support_view->close();

  std::optional<View> aborted_view;
  std::optional<Cursor> aborted_cursor;
  std::optional<storage::Tuple> aborted_saved;
  {
    auto runtime = make_support(plan);
    auto pending = runtime.begin_epoch(runtime.sequence() + 1, SetOperation::insert);
    check(pending.stage(NodeId{1}, inserted_a()), "aborted facade support fixture did not stage");
    aborted_view.emplace(pending.view(SnapshotSide::after));
    aborted_cursor.emplace(aborted_view->results());
    aborted_saved = aborted_cursor->next();
    pending.rollback();
  }
  check(aborted_saved && !aborted_view->valid() && aborted_cursor->state() == ResultCursorState::failed &&
            aborted_saved->values() == base_results().front(),
        "aborted support view after facade destruction lost its failure state or owning row");
  aborted_view->close();

  std::optional<View> physical_view;
  std::optional<Cursor> physical_cursor;
  std::optional<storage::Tuple> physical_saved;
  {
    auto runtime = make_physical(plan);
    auto pending = runtime.prepare({runtime.sequence() + 1, TableId{0}, SetOperation::insert, inserted_a()});
    physical_view.emplace(pending.view(SnapshotSide::after));
    physical_cursor.emplace(physical_view->results());
    physical_saved = physical_cursor->next();
    static_cast<void>(pending.commit());
  }
  check(physical_view->valid() && physical_cursor->active() && physical_saved,
        "committed physical delegated view did not survive facade destruction");
  auto physical_rows = drain(*physical_cursor);
  physical_rows.push_back(crown::storage::export_row(physical_saved->values()));
  sort_rows(physical_rows);
  check(physical_rows == base_results(), "physical facade destruction invalidated a view row");
  physical_view->close();
}

std::vector<Row> reference_rows(const storage::ReferenceTable& table) {
  std::vector<Row> result;
  for (const auto& tuple : table.snapshot()) result.push_back(crown::storage::export_row(tuple.values()));
  return result;
}

void check_reference_journal_owned_cursor_lifecycle() {
  using ReferenceTable = storage::ReferenceTable;
  using TableCursor = storage::ReferenceTable::Cursor;
  const storage::TupleLayout layout{LayoutId{601}, {storage::Field{ScalarType::int64}, storage::Field{ScalarType::string}}};
  const auto row1 = layout.tuple(Row{n(1), s("one")});
  const auto row2 = layout.tuple(Row{n(2), s("two")});
  const auto row3 = layout.tuple(Row{n(1), s("three")});
  const auto row4 = layout.tuple(Row{n(4), s("four")});
  const std::vector<Row> rows_after_row3{crown::storage::export_row(row1.values()), crown::storage::export_row(row3.values()), crown::storage::export_row(row2.values())};
  const auto fields = std::vector<FieldId>{FieldId{0}};
  const auto key_layout = projected_layout(LayoutId{602}, layout, fields);
  const auto key_one = key_layout.tuple(Row{n(1)});
  ReferenceTable table{RelationId{601}, layout};
  const auto handle1 = table.insert(row1).handle;
  const auto handle2 = table.insert(row2).handle;
  const auto index = table.add_index(storage::Projection{layout, key_layout, fields});
  check(reference_rows(table) == std::vector<Row>{crown::storage::export_row(row1.values()), crown::storage::export_row(row2.values())},
        "reference journal fixture did not initialize");

  // An ordinary cursor cannot advance while a journal owns the table. The
  // journal cursor reads the tentative insert and remains usable after commit.
  auto ordinary = table.live();
  auto journal = table.journal();
  const auto inserted = journal.insert(row3);
  check(inserted.inserted, "owner cursor fixture insert was a no-op");
  expect_error([&] { static_cast<void>(ordinary.next()); }, "storage_busy");
  expect_error([&] { static_cast<void>(table.live()); }, "storage_busy");
  std::optional<TableCursor> live;
  std::optional<TableCursor> bucket;
  live.emplace(journal.live());
  bucket.emplace(journal.bucket_cursor(index, key_one));
  const auto first = live->next();
  check(first.has_value(), "owner live cursor missed its first tentative row");
  journal.commit();
  std::set<TupleHandle> live_handles{*first};
  while (const auto handle = live->next()) live_handles.insert(*handle);
  check(live_handles == std::set<TupleHandle>{handle1, handle2, inserted.handle},
        "owner live cursor did not survive commit with the tentative relation contents");
  std::set<TupleHandle> bucket_handles;
  while (const auto handle = bucket->next()) bucket_handles.insert(*handle);
  check(bucket_handles == std::set<TupleHandle>{handle1, inserted.handle},
        "owner bucket cursor did not survive commit with the tentative index contents");

  // Even an empty different journal makes the old owner cursor reject reads
  // until that journal closes. A no-op journal must not revise the table.
  auto owner_journal = table.journal();
  auto committed_cursor = owner_journal.live();
  auto first_committed = committed_cursor.next();
  check(first_committed.has_value(), "committed owner cursor fixture was empty");
  owner_journal.commit();
  auto unrelated = table.journal();
  expect_error([&] { static_cast<void>(committed_cursor.next()); }, "storage_busy");
  unrelated.rollback();
  check(committed_cursor.next().has_value(),
        "owner cursor did not resume after an empty different journal rolled back");

  // A real mutation by the owning journal changes the revision and invalidates
  // previously opened tentative cursors before their iterator is reused.
  auto mutating = table.journal();
  auto stale = mutating.live();
  check(stale.next().has_value(), "same-journal invalidation cursor was empty");
  check(mutating.insert(row4).inserted, "same-journal invalidation insert was a no-op");
  expect_error([&] { static_cast<void>(stale.next()); }, "invalid_cursor");
  mutating.rollback();
  check(reference_rows(table) == rows_after_row3,
        "same-journal cursor invalidation rollback changed committed rows");

  // Rollback marks an owner cursor stale before undo erases the tentative row.
  auto aborting = table.journal();
  check(aborting.insert(row4).inserted, "rollback invalidation insert was a no-op");
  auto aborted = aborting.live();
  check(aborted.next().has_value(), "rollback invalidation cursor was empty");
  aborting.rollback();
  expect_error([&] { static_cast<void>(aborted.next()); }, "invalid_cursor");
  check(reference_rows(table) == rows_after_row3,
        "rolled-back owner cursor observed or retained an undone row");

  auto cancelling = table.journal();
  std::optional<TableCursor> cancelled;
  cancelled.emplace(cancelling.live());
  check(cancelled->next().has_value(), "owner cursor cancellation fixture was empty");
  {
    FaultScope fault;
    fault.forbid_allocations();
    cancelled.reset();
  }
  check(cancelling.insert(row4).inserted,
        "same-journal insert after owner-cursor reset was not reported inserted");
  cancelling.rollback();
  table.check_invariants();
}

void check_reference_journal_cursor_fault_sweep() {
  using ReferenceTable = storage::ReferenceTable;
  using TableCursor = storage::ReferenceTable::Cursor;
  const storage::TupleLayout layout{LayoutId{611}, {storage::Field{ScalarType::int64}, storage::Field{ScalarType::string}}};
  const auto row1 = layout.tuple(Row{n(1), s("one")});
  const auto row2 = layout.tuple(Row{n(2), s("two")});
  const auto row3 = layout.tuple(Row{n(3), s("three")});
  std::size_t failures = 0;
  bool saw_factory_failure = false;
  for (std::ptrdiff_t step = 0; step < 48; ++step) {
    ReferenceTable table{RelationId{611}, layout};
    const auto handle1 = table.insert(row1).handle;
    const auto handle2 = table.insert(row2).handle;
    auto journal = table.journal();
    check(journal.insert(row3).inserted, "journal cursor fault fixture insert was a no-op");
    std::optional<TableCursor> cursor;
    bool failed = false;
    {
      FaultScope fault(step);
      try {
        cursor.emplace(journal.live());
      } catch (const std::bad_alloc&) {
        failed = true;
        saw_factory_failure = true;
        cursor.reset();  // Cleanup runs while persistent fail-zero is active.
      }
    }
    if (!failed) {
      check(cursor.has_value(), "successful journal cursor factory returned no cursor");
      bool first_read = false;
      {
        FaultScope fault;
        fault.forbid_allocations();
        first_read = cursor->next().has_value();
      }
      check(first_read, "valid owner cursor first read allocated or returned no row");
      cursor.reset();
      journal.rollback();
      check(reference_rows(table) == std::vector<Row>{crown::storage::export_row(row1.values()), crown::storage::export_row(row2.values())} &&
                table.find(row1) == handle1 && table.find(row2) == handle2,
            "successful owner cursor fault-sweep step changed committed handles");
      check(failures > 0 && saw_factory_failure,
            "owner cursor fault sweep missed a lazy factory allocation");
      std::cout << "reference journal cursor factory_failures=" << failures
                << " first_read_noalloc=" << first_read << '\n';
      return;
    }
    ++failures;
    check(journal.active(), "owner cursor bad_alloc closed its enclosing journal");
    auto retry = journal.live();
    check(retry.next().has_value(), "owner cursor retry after persistent bad_alloc returned no row");
    journal.rollback();
    check(reference_rows(table) == std::vector<Row>{crown::storage::export_row(row1.values()), crown::storage::export_row(row2.values())} &&
              table.find(row1) == handle1 && table.find(row2) == handle2,
          "owner cursor fault rollback changed committed rows or handles");
  }
  throw std::runtime_error("owner cursor factory/first-read fault sweep did not reach success");
}

}  // namespace

int main() {
  try {
    const auto plan = make_plan();
    check_support_view_factory_sweep(plan, SnapshotSide::before, false);
    check_support_view_factory_sweep(plan, SnapshotSide::after, false);
    check_support_view_factory_sweep(plan, SnapshotSide::before, true);
    check_support_view_factory_sweep(plan, SnapshotSide::after, true);
    check_physical_view_factory_sweep(plan, SnapshotSide::before);
    check_physical_view_factory_sweep(plan, SnapshotSide::after);
    check_completion_factory_sweep(plan, false);
    check_completion_factory_sweep(plan, true);
    check_completion_validation(plan);
    check_completions_filter_paths(plan);
    check_rollback_aborts_linked_cursors_noalloc(plan);
    check_commit_preserves_views_noalloc(plan);
    check_pending_move_cleanup_noalloc(plan);
    check_pending_destruction_noalloc(plan);
    check_physical_pending_lifecycle_noalloc(plan);
    check_next_fault_sweep(plan, false, SnapshotSide::before, false);
    check_next_fault_sweep(plan, false, SnapshotSide::after, true);
    check_next_fault_sweep(plan, true, SnapshotSide::before, true);
    check_next_fault_sweep(plan, true, SnapshotSide::after, false);
    check_current_view_next_lease(plan, false);
    check_current_view_next_lease(plan, true);
    check_facade_destruction_stability(plan);
    check_reference_journal_owned_cursor_lifecycle();
    check_reference_journal_cursor_fault_sweep();
    std::cout << "epoch-view allocation factories, overlay cursors, completion filters, and no-allocation lifecycle checks passed\n";
  } catch (const std::exception& failure) {
    fail_after = -1;
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
