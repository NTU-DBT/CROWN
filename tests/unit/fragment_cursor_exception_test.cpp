#include "crown/api/error.hpp"
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

// Keep the injector persistent so cursor and intrusive-list cleanup runs with
// allocation failure still enabled.
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

void check(bool condition, std::string_view message) {
  if (!condition) throw std::runtime_error(std::string(message));
}

template <class Action>
void expect_error(Action&& action, std::string_view code) {
  try {
    std::forward<Action>(action)();
  } catch (const Error& failure) {
    check(failure.code() == code, "unexpected fragment cursor error code");
    return;
  }
  throw std::runtime_error("expected fragment cursor error code " + std::string(code));
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

constexpr VariableId x{0};
constexpr VariableId y{1};
constexpr VariableId z{2};
constexpr VariableId a_witness{3};
constexpr VariableId b_witness{4};

PhysicalPlan make_plan() {
  const Catalog catalog{91, {
      {"A", {{"x", ScalarType::int64}, {"y", ScalarType::int64}, {"a_witness", ScalarType::string}}},
      {"B", {{"x", ScalarType::int64}, {"y", ScalarType::int64}, {"b_witness", ScalarType::string}}},
      {"C", {{"x", ScalarType::int64}, {"z", ScalarType::int64}, {"a_witness", ScalarType::string}}}}};
  const Query query{
      {{"x", ScalarType::int64}, {"y", ScalarType::int64}, {"z", ScalarType::int64},
       {"a_witness", ScalarType::string}, {"b_witness", ScalarType::string}},
      {{"a", TableId{0}, {x, y, a_witness}},
       {"b", TableId{1}, {x, y, b_witness}},
       {"c", TableId{2}, {x, z, a_witness}}},
      {{x, "x"}, {y, "y"}}, false};
  // C is below A but outside the root-connected C* subtree for head {x,y}.
  const FreeConnexTree tree{NodeId{0}, {
      {"root", NodeKind::generalized, {x, y}, {NodeId{1}, NodeId{2}}, {}, {}},
      {"a", NodeKind::native, {x, y, a_witness}, {NodeId{3}}, 0, {}},
      {"b", NodeKind::native, {x, y, b_witness}, {}, 1, {}},
      {"c", NodeKind::native, {x, z, a_witness}, {}, 2, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

const std::vector<Row>& a_rows() {
  static const std::vector<Row> rows{
      a_row(1, 10, "a10"), a_row(1, 10, "a10b"), a_row(1, 11, "a11"),
      a_row(1, 11, "orphan"), a_row(2, 20, "a20")};
  return rows;
}
const std::vector<Row>& b_rows() {
  static const std::vector<Row> rows{
      b_row(1, 10, "b10"), b_row(1, 10, "b10b"), b_row(1, 11, "b11"),
      b_row(2, 20, "b20")};
  return rows;
}
const std::vector<Row>& c_rows() {
  static const std::vector<Row> rows{
      c_row(1, 7, "a10"), c_row(1, 8, "a10b"), c_row(1, 9, "a11"),
      c_row(2, 8, "a20")};
  return rows;
}

SupportRuntime make_support(const PhysicalPlan& plan) {
  SupportRuntime runtime{plan};
  std::uint64_t sequence = 1;
  for (const auto& row : a_rows())
    static_cast<void>(runtime.apply({sequence++, NodeId{1}, SetOperation::insert, row}));
  for (const auto& row : b_rows())
    static_cast<void>(runtime.apply({sequence++, NodeId{2}, SetOperation::insert, row}));
  for (const auto& row : c_rows())
    static_cast<void>(runtime.apply({sequence++, NodeId{3}, SetOperation::insert, row}));
  check(runtime.sequence() == sequence - 1 && runtime.has_answer(), "support witness fixture did not initialize");
  runtime.check_invariants();
  return runtime;
}

PhysicalRuntime make_physical(const PhysicalPlan& plan) {
  PhysicalRuntime runtime{plan};
  std::uint64_t sequence = 1;
  for (const auto& row : a_rows())
    static_cast<void>(runtime.apply({sequence++, TableId{0}, SetOperation::insert, row}));
  for (const auto& row : b_rows())
    static_cast<void>(runtime.apply({sequence++, TableId{1}, SetOperation::insert, row}));
  for (const auto& row : c_rows())
    static_cast<void>(runtime.apply({sequence++, TableId{2}, SetOperation::insert, row}));
  check(runtime.sequence() == sequence - 1 && runtime.has_answer(), "physical witness fixture did not initialize");
  runtime.check_invariants();
  return runtime;
}

void sort_rows(std::vector<Row>& rows) { std::sort(rows.begin(), rows.end()); }

std::vector<Row> drain(Cursor& cursor) {
  std::vector<Row> rows;
  while (auto tuple = cursor.next()) rows.push_back(crown::storage::export_row(tuple->values()));
  sort_rows(rows);
  check(cursor.state() == ResultCursorState::exhausted && !cursor.active(),
        "fragment cursor did not close at exhaustion");
  return rows;
}

std::vector<Row> expected_all_witnesses(bool omit_b10 = false) {
  std::vector<Row> rows;
  for (const auto& a : a_rows()) {
    for (const auto& c : c_rows()) {
      if (a[0] != c[0] || a[2] != c[2]) continue;
      for (const auto& b : b_rows()) {
        if (a[0] != b[0] || a[1] != b[1]) continue;
        if (omit_b10 && b == b_row(1, 10, "b10")) continue;
        rows.push_back({a[0], a[1], c[1], a[2], b[2]});
      }
    }
  }
  sort_rows(rows);
  return rows;
}

std::vector<Row> expected_a_b() {
  std::vector<Row> rows;
  for (const auto& a : a_rows()) for (const auto& b : b_rows()) {
    const bool has_child_witness = std::any_of(c_rows().begin(), c_rows().end(), [&](const Row& c) {
      return a[0] == c[0] && a[2] == c[2];
    });
    if (has_child_witness && a[0] == b[0] && a[1] == b[1])
      rows.push_back({a[0], a[1], a[2], b[2]});
  }
  sort_rows(rows);
  return rows;
}

std::vector<Row> expected_b_c() {
  std::vector<Row> rows;
  for (const auto& b : b_rows()) for (const auto& c : c_rows())
    if (b[0] == c[0]) rows.push_back({b[0], b[1], c[1], c[2], b[2]});
  sort_rows(rows);
  return rows;
}

std::vector<Row> expected_a_c() {
  std::vector<Row> rows;
  for (const auto& a : a_rows()) for (const auto& c : c_rows())
    if (a[0] == c[0] && a[2] == c[2]) rows.push_back({a[0], a[1], c[1], a[2]});
  sort_rows(rows);
  return rows;
}

void check_schema(const storage::TupleLayout& layout, std::initializer_list<VariableId> variables,
                  std::string_view message) {
  check(layout.fields().size() == variables.size(), message);
  std::size_t field = 0;
  for (const auto variable : variables)
    check(layout.fields()[field++].variable == variable, message);
}

void check_fragment_semantics(const PhysicalPlan& plan) {
  auto runtime = make_support(plan);
  auto view = runtime.current_view();

  auto whole = view.witnesses();
  check_schema(whole.layout(), {x, y, z, a_witness, b_witness}, "whole witness schema was not sorted or complete");
  check(drain(whole) == expected_all_witnesses(), "whole-tree witness traversal lost a factor or hidden value");

  auto root = view.witnesses({}, WitnessFragment{NodeId{0}});
  check_schema(root.layout(), {x, y, z, a_witness, b_witness}, "root witness schema omitted an outside-C* descendant");
  check(drain(root) == expected_all_witnesses(), "root witness traversal did not include all descendants");

  auto a_subtree = view.witnesses({}, WitnessFragment{NodeId{1}});
  check_schema(a_subtree.layout(), {x, y, z, a_witness}, "subtree witness schema was not sorted");
  check(drain(a_subtree) == expected_a_c(), "subtree witnesses ignored a hidden child factor");

  auto c_root = view.witnesses({}, WitnessFragment{NodeId{3}});
  check_schema(c_root.layout(), {x, z, a_witness}, "arbitrary physical-node witness root was rejected or projected");
  check(drain(c_root) == std::vector<Row>{{n(1), n(7), s("a10")}, {n(1), n(8), s("a10b")},
                                            {n(1), n(9), s("a11")}, {n(2), n(8), s("a20")}},
        "arbitrary-node witnesses did not traverse the selected subtree");

  auto siblings = view.witnesses({}, WitnessFragment{std::nullopt, std::vector<NodeId>{NodeId{1}, NodeId{2}}});
  check_schema(siblings.layout(), {x, y, a_witness, b_witness}, "explicit factor schema was not sorted");
  check(drain(siblings) == expected_a_b(), "exact selected sibling factors did not join on shared variables");

  // B and C are not adjacent. Their exact factor set joins only on x, so
  // mismatching candidates exercise local join rejection checks.
  auto disconnected = view.witnesses({}, WitnessFragment{std::nullopt, std::vector<NodeId>{NodeId{2}, NodeId{3}}});
  check_schema(disconnected.layout(), {x, y, z, a_witness, b_witness}, "disconnected factor schema was not sorted");
  check(drain(disconnected) == expected_b_c(), "nonadjacent selected factors did not join on their shared variable");
  const auto& disconnected_metrics = disconnected.metrics();
  const auto rejected = disconnected_metrics.startup.join_rejections + disconnected_metrics.results.join_rejections +
      disconnected_metrics.termination.join_rejections;
  check(rejected > 0, "disconnected factor traversal did not account for incompatible join candidates");

  auto empty = view.witnesses({}, WitnessFragment{std::nullopt, std::vector<NodeId>{}});
  check_schema(empty.layout(), {}, "empty factor set was not nullary");
  check(drain(empty) == std::vector<Row>{Row{}}, "empty factor set did not emit the nullary identity once");

  auto absent_binding = view.witnesses({{b_witness, s("unused")}}, WitnessFragment{NodeId{3}});
  check(drain(absent_binding).size() == c_rows().size(),
        "a validated binding absent from a selected factor set was not ignored");

  expect_error([&] { static_cast<void>(view.witnesses({}, WitnessFragment{NodeId{99}})); }, "invalid_fragment");
  expect_error([&] {
    static_cast<void>(view.witnesses({}, WitnessFragment{std::nullopt, std::vector<NodeId>{NodeId{1}, NodeId{1}}}));
  }, "invalid_fragment");
  expect_error([&] {
    static_cast<void>(view.witnesses({}, WitnessFragment{NodeId{0}, std::vector<NodeId>{NodeId{1}}}));
  }, "invalid_fragment");
  expect_error([&] {
    static_cast<void>(view.witnesses({}, WitnessFragment{std::nullopt, std::vector<NodeId>{NodeId{99}}}));
  }, "invalid_fragment");
  expect_error([&] { static_cast<void>(view.witnesses({{b_witness, n(1)}})); }, "invalid_binding");
  expect_error([&] { static_cast<void>(view.witnesses({{VariableId{99}, n(1)}})); }, "invalid_binding");
  expect_error([&] {
    static_cast<void>(view.witnesses({{x, n(1)}, {x, n(2)}}));
  }, "invalid_binding");

  auto direct = view.witnesses({{x, n(1)}, {y, n(10)}, {a_witness, s("a10")}, {b_witness, s("b10")}},
                               WitnessFragment{NodeId{0}});
  check(drain(direct) == std::vector<Row>{{n(1), n(10), n(7), s("a10"), s("b10")}},
        "fully fixed full-witness lookup returned the wrong assignment");
  check(direct.metrics().results.direct_lookups > 0,
        "fully fixed factors did not use exact survivor lookups");

  auto partial = view.witnesses({{x, n(1)}}, WitnessFragment{NodeId{0}});
  const auto partial_rows = drain(partial);
  check(partial_rows.size() == 5 && partial.metrics().results.binding_checks > 0,
        "partial witness binding did not scan and filter factor rows");

  const auto visible = std::vector<Row>{{n(1), n(10)}, {n(1), n(11)}, {n(2), n(20)}};
  auto ordinary_completions = view.completions({});
  check(drain(ordinary_completions) == visible,
        "witness traversal changed the core-head projected completion relation");
  auto bound_hidden = view.completions({{a_witness, s("a10b")} });
  check(drain(bound_hidden) == std::vector<Row>{{n(1), n(10)}},
        "hidden witness binding did not preserve its projected completion");
  auto bound_hidden_fragment = view.completions({{a_witness, s("a10b")}}, VisibleFragment{NodeId{0}});
  check_schema(bound_hidden_fragment.layout(), {x, y}, "local visible fragment exposed hidden witness columns");
  check(drain(bound_hidden_fragment) == std::vector<Row>{{n(1), n(10)}},
        "hidden restriction did not apply while projecting a local visible fragment");
  auto hidden_orphan = view.completions({{a_witness, s("orphan")} });
  check(drain(hidden_orphan).empty(), "hidden binding bypassed a full-query factor outside C*");

  auto hidden_probe = view.completions({{x, n(1)}, {a_witness, s("a10")}});
  check(drain(hidden_probe) == std::vector<Row>{{n(1), n(10)}}, "hidden witness probe changed the projected answer");
  const auto& probe_metrics = hidden_probe.metrics();
  const auto probes = probe_metrics.startup.witness_probes + probe_metrics.results.witness_probes +
      probe_metrics.termination.witness_probes;
  const auto probed_rows = probe_metrics.startup.witness_rows + probe_metrics.results.witness_rows +
      probe_metrics.termination.witness_rows;
  check(probes > 0 && probed_rows > 0,
        "hidden projected completion omitted full-witness probe phase metrics");

  auto support_witnesses = runtime.witnesses();
  check(drain(support_witnesses) == expected_all_witnesses(),
        "SupportRuntime witness facade disagreed with its epoch view");
  auto physical = make_physical(plan);
  auto physical_witnesses = physical.witnesses();
  check(drain(physical_witnesses) == expected_all_witnesses(),
        "PhysicalRuntime witness facade disagreed with its support view");
  view.close();
  check(runtime.ready(), "fragment semantic cursors retained a current-view lease");
}

template <class MakeRuntime>
void check_current_witness_factory_sweep(const PhysicalPlan& plan, std::string_view name, MakeRuntime make_runtime) {
  std::size_t failures = 0;
  for (std::ptrdiff_t step = 0; step < 1024; ++step) {
    auto runtime = make_runtime(plan);
    const auto sequence = runtime.sequence();
    auto view = runtime.current_view();
    bool failed = false;
    try {
      FaultScope fault(step);
      auto cursor = view.witnesses({}, WitnessFragment{NodeId{0}});
      cursor.cancel();
    } catch (const std::bad_alloc&) {
      failed = true;
    }
    if (!failed) {
      check(failures > 0, "current witness factory sweep missed allocation failures");
      check(view.valid() && runtime.sequence() == sequence, "successful current witness factory changed its view");
      view.close();
      check(runtime.ready(), "successful current witness factory leaked a reader lease");
      std::cout << name << " witness factory failures=" << failures << '\n';
      return;
    }
    ++failures;
    check(view.valid() && !runtime.ready() && runtime.sequence() == sequence,
          "current witness factory bad_alloc invalidated its view or changed runtime state");
    auto retry = view.witnesses({}, WitnessFragment{NodeId{0}});
    check(drain(retry) == expected_all_witnesses(), "current witness factory retry returned a changed witness set");
    view.close();
    check(runtime.ready() && runtime.sequence() == sequence,
          "current witness factory retry leaked its lease or changed runtime state");
  }
  throw std::runtime_error("current witness factory fault sweep did not reach success");
}

void check_pending_witness_factory_sweep(const PhysicalPlan& plan, SnapshotSide side) {
  std::size_t failures = 0;
  const auto expected = expected_all_witnesses(side == SnapshotSide::after);
  for (std::ptrdiff_t step = 0; step < 1024; ++step) {
    auto runtime = make_support(plan);
    const auto sequence = runtime.sequence();
    auto pending = runtime.begin_epoch(sequence + 1, SetOperation::erase);
    check(pending.stage(NodeId{2}, b_row(1, 10, "b10")), "pending witness factory delete was a no-op");
    auto view = pending.view(side);
    bool failed = false;
    try {
      FaultScope fault(step);
      auto cursor = view.witnesses({}, WitnessFragment{NodeId{0}});
      cursor.cancel();
    } catch (const std::bad_alloc&) {
      failed = true;
    }
    if (!failed) {
      check(failures > 0, "pending witness factory sweep missed allocation failures");
      check(view.valid() && pending.active(), "successful pending witness factory changed its epoch");
      view.close();
      pending.rollback();
      check(runtime.ready() && runtime.sequence() == sequence,
            "successful pending witness factory leaked a lease or changed committed state");
      std::cout << "pending witness factory side=" << (side == SnapshotSide::before ? "before" : "after")
                << " failures=" << failures << '\n';
      return;
    }
    ++failures;
    check(view.valid() && pending.active() && runtime.sequence() == sequence,
          "pending witness factory bad_alloc changed its frozen epoch prefix");
    auto retry = view.witnesses({}, WitnessFragment{NodeId{0}});
    check(drain(retry) == expected, "pending witness factory retry did not return its before/after full witnesses");
    view.close();
    pending.rollback();
    check(runtime.ready() && runtime.sequence() == sequence,
          "pending witness factory retry leaked its lease or changed committed state");
  }
  throw std::runtime_error("pending witness factory fault sweep did not reach success");
}

void check_hidden_completion_factory_sweep(const PhysicalPlan& plan) {
  std::size_t failures = 0;
  for (std::ptrdiff_t step = 0; step < 1024; ++step) {
    auto runtime = make_support(plan);
    const auto sequence = runtime.sequence();
    auto view = runtime.current_view();
    bool failed = false;
    try {
      FaultScope fault(step);
      auto cursor = view.completions({{a_witness, s("a10b")}});
      cursor.cancel();
    } catch (const std::bad_alloc&) {
      failed = true;
    }
    if (!failed) {
      check(failures > 0, "hidden completion factory sweep missed allocation failures");
      view.close();
      check(runtime.ready() && runtime.sequence() == sequence,
            "successful hidden completion factory leaked a current view");
      std::cout << "hidden completion factory failures=" << failures << '\n';
      return;
    }
    ++failures;
    check(view.valid() && runtime.sequence() == sequence,
          "hidden completion factory bad_alloc invalidated its source view");
    auto retry = view.completions({{a_witness, s("a10b")} });
    check(drain(retry) == std::vector<Row>{{n(1), n(10)}},
          "hidden completion factory retry returned a different projection");
    view.close();
    check(runtime.ready() && runtime.sequence() == sequence,
          "hidden completion factory retry leaked its current view");
  }
  throw std::runtime_error("hidden completion factory fault sweep did not reach success");
}

void check_witness_next_fault_sweep(const PhysicalPlan& plan, SnapshotSide side, bool later) {
  std::size_t failures = 0;
  const auto expected = expected_all_witnesses(side == SnapshotSide::after);
  for (std::ptrdiff_t step = 0; step < 1024; ++step) {
    auto runtime = make_support(plan);
    auto pending = runtime.begin_epoch(runtime.sequence() + 1, SetOperation::erase);
    check(pending.stage(NodeId{2}, b_row(1, 10, "b10")), "witness next fixture delete was a no-op");
    auto view = pending.view(side);
    auto cursor = view.witnesses({}, WitnessFragment{NodeId{0}});
    auto peer = view.completions({{a_witness, s("a10")}});
    std::optional<storage::Tuple> first;
    std::optional<storage::Tuple> second;
    if (later) {
      first = cursor.next();
      second = cursor.next();
      check(first && second && first->values() != second->values(), "later witness cursor prefix was not distinct");
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
      check(failures > 0, "witness next sweep missed allocation failures");
      check(yielded && cursor.active() && view.valid(), "successful witness next did not yield an owning row");
      cursor.cancel();
      peer.cancel();
      view.close();
      pending.rollback();
      check(runtime.ready(), "successful witness next cleanup leaked its pending view");
      std::cout << "witness next side=" << (side == SnapshotSide::before ? "before" : "after")
                << " later=" << later << " failures=" << failures << '\n';
      return;
    }
    ++failures;
    check(cursor.state() == ResultCursorState::failed && !cursor.active() &&
              peer.active() && view.valid() && pending.active(),
          "failed witness cursor closed its peer or changed the pending view");
    if (later) {
      check(first && second && first->values() != second->values() && cursor.metrics().results.rows_emitted == 2,
            "later witness failure lost its owning prefix rows");
    }
    if (first) check(first->values().size() == 5, "saved witness row stopped owning its full tuple");
    if (second) check(second->values().size() == 5, "saved later witness row stopped owning its full tuple");
    check(drain(peer) == std::vector<Row>{{n(1), n(10)}},
          "peer projected cursor failed with the witness cursor");
    expect_error([&] { static_cast<void>(cursor.next()); }, "invalid_cursor");
    auto retry = view.witnesses({}, WitnessFragment{NodeId{0}});
    check(drain(retry) == expected,
          "failed witness next retry lost before-side deleted S rows or included after-side ghosts");
    view.close();
    pending.rollback();
    check(runtime.ready(), "witness next failure cleanup retained a pending view lease");
  }
  throw std::runtime_error("witness next-fault sweep did not reach success");
}

void check_pending_commit_noalloc(const PhysicalPlan& plan) {
  auto runtime = make_support(plan);
  const auto sequence = runtime.sequence();
  auto pending = runtime.begin_epoch(sequence + 1, SetOperation::erase);
  check(pending.stage(NodeId{2}, b_row(1, 10, "b10")), "commit witness fixture delete was a no-op");
  auto view = pending.view(SnapshotSide::before);
  auto witness_cursor = view.witnesses({}, WitnessFragment{NodeId{0}});
  auto completion_cursor = view.completions({{a_witness, s("a10")} });
  auto saved_witness = witness_cursor.next();
  auto saved_completion = completion_cursor.next();
  check(saved_witness && saved_completion && witness_cursor.active() && completion_cursor.active(),
        "commit fixture did not start both witness and projected-probe cursors");
  std::optional<SupportEpoch> output;
  {
    FaultScope fault;
    fault.forbid_allocations();
    output.emplace(pending.commit());
  }
  check(output && !pending.active() && runtime.sequence() == sequence + 1 &&
            view.valid() && !view.tentative() && witness_cursor.active() && completion_cursor.active(),
        "no-allocation commit did not preserve full-witness and projected-probe cursors");
  auto remaining_witnesses = drain(witness_cursor);
  remaining_witnesses.push_back(crown::storage::export_row(saved_witness->values()));
  sort_rows(remaining_witnesses);
  check(remaining_witnesses == expected_all_witnesses(),
        "committed before-side witness cursor lost the deleted S ghost or its owning row");
  auto remaining_completions = drain(completion_cursor);
  remaining_completions.push_back(crown::storage::export_row(saved_completion->values()));
  sort_rows(remaining_completions);
  check(remaining_completions == std::vector<Row>{{n(1), n(10)}},
        "committed before-side projected cursor changed its hidden-bound result");
  view.close();
  check(runtime.ready(), "closing the committed witness view did not release its lease");
}

void check_pending_rollback_noalloc(const PhysicalPlan& plan) {
  auto runtime = make_support(plan);
  auto pending = runtime.begin_epoch(runtime.sequence() + 1, SetOperation::erase);
  check(pending.stage(NodeId{2}, b_row(1, 10, "b10")), "rollback witness fixture delete was a no-op");
  auto view = pending.view(SnapshotSide::after);
  auto witness_cursor = view.witnesses({}, WitnessFragment{NodeId{0}});
  auto completion_cursor = view.completions({{a_witness, s("a10")} });
  auto saved_witness = witness_cursor.next();
  auto saved_completion = completion_cursor.next();
  check(saved_witness && saved_completion, "rollback fixture did not retain owning cursor rows");
  bool rolled_back = false;
  {
    FaultScope fault;
    fault.forbid_allocations();
    pending.rollback();
    rolled_back = !pending.active() && !view.valid() &&
        witness_cursor.state() == ResultCursorState::failed && !witness_cursor.active() &&
        completion_cursor.state() == ResultCursorState::failed && !completion_cursor.active();
  }
  check(rolled_back && runtime.ready() && saved_witness->values().size() == 5 &&
            saved_completion->values() == Row{n(1), n(10)},
        "no-allocation rollback did not invalidate both cursors and preserve their owning rows");
  view.close();
}

void check_pending_move_and_destruction_noalloc(const PhysicalPlan& plan) {
  auto destination_runtime = make_support(plan);
  auto source_runtime = make_support(plan);
  std::optional<SupportRuntime::PendingEpoch> destination;
  std::optional<SupportRuntime::PendingEpoch> source;
  destination.emplace(destination_runtime.begin_epoch(destination_runtime.sequence() + 1, SetOperation::erase));
  check(destination->stage(NodeId{2}, b_row(1, 10, "b10")), "move destination witness update was a no-op");
  auto old_view = destination->view(SnapshotSide::before);
  auto old_witness = old_view.witnesses({}, WitnessFragment{NodeId{0}});
  auto old_completion = old_view.completions({{b_witness, s("b10")} });
  auto saved_witness = old_witness.next();
  auto saved_completion = old_completion.next();
  check(saved_witness && saved_completion, "move destination did not start full and projected cursors");

  source.emplace(source_runtime.begin_epoch(source_runtime.sequence() + 1, SetOperation::insert));
  check(source->stage(NodeId{1}, a_row(3, 30, "a30")), "move source witness update was a no-op");
  bool moved = false;
  {
    FaultScope fault;
    fault.forbid_allocations();
    *destination = std::move(*source);
    moved = destination->active() && !source->active() && !old_view.valid() &&
        old_witness.state() == ResultCursorState::failed && !old_witness.active() &&
        old_completion.state() == ResultCursorState::failed && !old_completion.active();
  }
  check(moved && destination_runtime.ready() && !source_runtime.ready() &&
            saved_witness->values().size() == 5 && saved_completion->values() == Row{n(1), n(10)},
        "no-allocation pending move did not abort both destination cursors safely");
  {
    FaultScope fault;
    fault.forbid_allocations();
    destination->rollback();
  }
  check(destination_runtime.ready() && source_runtime.ready(), "moved pending rollback leaked a runtime lease");
  old_view.close();

  auto destruction_runtime = make_support(plan);
  std::optional<View> destruction_view;
  std::optional<Cursor> destruction_witness;
  std::optional<Cursor> destruction_completion;
  std::optional<SupportRuntime::PendingEpoch> abandoned;
  {
    abandoned.emplace(destruction_runtime.begin_epoch(destruction_runtime.sequence() + 1, SetOperation::erase));
    check(abandoned->stage(NodeId{2}, b_row(1, 10, "b10")), "destruction witness update was a no-op");
    destruction_view.emplace(abandoned->view(SnapshotSide::after));
    destruction_witness.emplace(destruction_view->witnesses({}, WitnessFragment{NodeId{0}}));
    destruction_completion.emplace(destruction_view->completions({{a_witness, s("a10")} }));
    check(destruction_witness->next().has_value() && destruction_completion->next().has_value(),
          "destruction fixture did not start full and projected cursors");
  }
  {
    FaultScope fault;
    fault.forbid_allocations();
    abandoned.reset();
  }
  check(destruction_view && !destruction_view->valid() &&
            destruction_witness->state() == ResultCursorState::failed &&
            destruction_completion->state() == ResultCursorState::failed && destruction_runtime.ready(),
        "no-allocation pending destruction did not abort its linked witness cursors");
  destruction_view->close();
}

void check_phase_limits(const PhysicalPlan& plan) {
  auto runtime = make_support(plan);
  auto view = runtime.current_view();
  expect_error([&] {
    static_cast<void>(view.witnesses({}, WitnessFragment{NodeId{0}}, ResultCursorOptions{.work_limit = 0}));
  }, "resource_limit");
  check(view.valid(), "startup work-limit failure invalidated its epoch view");

  auto probe = view.witnesses({}, WitnessFragment{NodeId{0}});
  const auto startup_work = probe.metrics().startup.work;
  probe.cancel();
  auto limited = view.witnesses({}, WitnessFragment{NodeId{0}},
                                ResultCursorOptions{.work_limit = startup_work + 1});
  expect_error([&] { static_cast<void>(limited.next()); }, "resource_limit");
  check(limited.state() == ResultCursorState::failed && !limited.active() &&
            limited.metrics().failed.calls == 1 && limited.metrics().failed.work == 1 &&
            limited.metrics().total_work == startup_work + 1,
        "result-phase work limit did not retain its failed phase metrics");
  auto retry = view.witnesses({}, WitnessFragment{NodeId{0}});
  check(drain(retry) == expected_all_witnesses(), "work-limit failure prevented a clean cursor retry");
  view.close();
  check(runtime.ready(), "work-limit cursors retained a current-view lease");
}

}  // namespace

int main() {
  try {
    const auto plan = make_plan();
    check_fragment_semantics(plan);
    check_current_witness_factory_sweep(plan, "support", make_support);
    check_current_witness_factory_sweep(plan, "physical", make_physical);
    check_pending_witness_factory_sweep(plan, SnapshotSide::before);
    check_pending_witness_factory_sweep(plan, SnapshotSide::after);
    check_hidden_completion_factory_sweep(plan);
    check_witness_next_fault_sweep(plan, SnapshotSide::before, false);
    check_witness_next_fault_sweep(plan, SnapshotSide::before, true);
    check_witness_next_fault_sweep(plan, SnapshotSide::after, false);
    check_witness_next_fault_sweep(plan, SnapshotSide::after, true);
    check_pending_commit_noalloc(plan);
    check_pending_rollback_noalloc(plan);
    check_pending_move_and_destruction_noalloc(plan);
    check_phase_limits(plan);
    std::cout << "fragment witness factories, local joins, hidden probes, and no-allocation lifecycle checks passed\n";
  } catch (const std::exception& failure) {
    fail_after = -1;
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
