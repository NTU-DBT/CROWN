#include "crown/io/document.hpp"
#include "crown/io/support.hpp"
#include "crown/planner/lower.hpp"
#include "crown/runtime/support.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <new>
#include <optional>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

// This fault injector lives in its own executable so allocations elsewhere in
// the test suite keep their normal behavior.
namespace {
thread_local std::ptrdiff_t fail_after = -1;
[[gnu::noinline]] void* allocate(std::size_t bytes) {
  if (fail_after >= 0) {
    if (fail_after == 0) throw std::bad_alloc{};
    --fail_after;
  }
  if (auto* result = std::malloc(bytes == 0 ? 1 : bytes)) return result;
  throw std::bad_alloc{};
}
struct FaultScope {
  explicit FaultScope(std::ptrdiff_t step) { fail_after = step; }
  ~FaultScope() { fail_after = -1; }
  FaultScope(const FaultScope&) = delete;
  FaultScope& operator=(const FaultScope&) = delete;
};
}  // namespace

void* operator new(std::size_t bytes) { return allocate(bytes); }
void* operator new[](std::size_t bytes) { return allocate(bytes); }
void operator delete(void* pointer) noexcept { std::free(pointer); }
void operator delete[](void* pointer) noexcept { std::free(pointer); }
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }

namespace {
using namespace crown;
using namespace crown::runtime;

void check(bool value, const std::string& message) {
  if (!value) throw std::runtime_error(message);
}
Value n(std::int64_t value) { return value; }
Value s(std::string value) { return value; }
std::string padded(char value) { return std::string(180, value); }

PhysicalPlan make_plan() {
  Catalog catalog{1, {
      {"R", {{"x", ScalarType::int64}, {"r_witness", ScalarType::string}}},
      {"S", {{"x", ScalarType::int64}, {"s_witness", ScalarType::string}}}}};
  Query query{
      {{"x", ScalarType::int64}, {"r_witness", ScalarType::string}, {"s_witness", ScalarType::string}},
      {{"r", TableId{0}, {VariableId{0}, VariableId{1}}},
       {"s", TableId{1}, {VariableId{0}, VariableId{2}}}},
      {{VariableId{0}, "x"}}, false};
  FreeConnexTree tree{NodeId{0}, {
      {"g", NodeKind::generalized, {VariableId{0}}, {NodeId{1}, NodeId{2}}, {}, {}},
      {"r", NodeKind::native, {VariableId{0}, VariableId{1}}, {}, 0, {}},
      {"s", NodeKind::native, {VariableId{0}, VariableId{2}}, {}, 1, {}}}, {}, {}};
  return planner::lower_tree(catalog, query, tree);
}

enum class Case {
  insert_last_child,
  erase_supported_child,
  erase_redundant_child_support,
  reclaim_candidate
};
const char* case_name(Case value) {
  switch (value) {
    case Case::insert_last_child: return "insert_last_child";
    case Case::erase_supported_child: return "erase_supported_child";
    case Case::erase_redundant_child_support: return "erase_redundant_child_support";
    case Case::reclaim_candidate: return "reclaim_candidate";
  }
  return "unknown";
}

SupportOptions options() {
  SupportOptions result;
  result.capture_transitions = true;
  return result;
}

std::vector<NativeSetUpdate> setup_updates(Case which) {
  const auto r_a = Row{n(10), s(padded('a'))};
  const auto r_b = Row{n(10), s(padded('b'))};
  const auto r_unrelated = Row{n(99), s(padded('c'))};
  const auto s_x = Row{n(10), s(padded('s'))};
  if (which == Case::reclaim_candidate)
    return {{1, NodeId{2}, SetOperation::insert, s_x}};
  std::vector<NativeSetUpdate> result{
      {1, NodeId{1}, SetOperation::insert, r_a},
      {2, NodeId{1}, SetOperation::insert, r_b},
      {3, NodeId{1}, SetOperation::insert, r_unrelated}};
  if (which == Case::erase_supported_child || which == Case::erase_redundant_child_support)
    result.push_back({4, NodeId{2}, SetOperation::insert, s_x});
  return result;
}

NativeSetUpdate target_update(Case which) {
  const auto s_x = Row{n(10), s(padded('s'))};
  const auto r_a = Row{n(10), s(padded('a'))};
  switch (which) {
    case Case::insert_last_child: return {4, NodeId{2}, SetOperation::insert, s_x};
    case Case::erase_supported_child: return {5, NodeId{2}, SetOperation::erase, s_x};
    case Case::erase_redundant_child_support: return {5, NodeId{1}, SetOperation::erase, r_a};
    case Case::reclaim_candidate: return {2, NodeId{2}, SetOperation::erase, s_x};
  }
  throw std::runtime_error("unknown support fault case");
}

std::shared_ptr<const SupportJournal> initialize(SupportRuntime& runtime, Case which) {
  std::shared_ptr<const SupportJournal> last_journal;
  for (const auto& update : setup_updates(which)) {
    const auto epoch = runtime.apply(update);
    check(epoch.native_changed, "setup update did not change a native set");
    check(epoch.journal != nullptr && !epoch.journal->records.empty(),
          "successful setup update did not return an affected-record journal");
    last_journal = epoch.journal;
  }
  runtime.check_invariants();
  return last_journal;
}

io::Json normalized_snapshot(const SupportRuntime& runtime, const PhysicalPlan& plan) {
  auto result = io::write_support_snapshot(runtime.snapshot(), plan);
  for (auto& node : result.at("nodes")) {
    for (auto& record : node.at("records")) record.at("handle")["owner"] = 0;
    const auto normalize_keys = [](io::Json& keys) {
      if (keys.is_null()) return;
      for (auto& key : keys) key.at("handle")["owner"] = 0;
    };
    normalize_keys(node.at("parent_keys"));
    normalize_keys(node.at("visible_keys"));
  }
  return result;
}

io::Json normalized_epoch(const SupportEpoch& epoch) {
  auto result = io::write_support_epoch(epoch);
  const auto normalize_owners = [&](const auto& self, io::Json& value) -> void {
    if (value.is_object()) {
      if (value.contains("owner")) value["owner"] = 0;
      for (auto& member : value.items()) self(self, member.value());
    } else if (value.is_array()) {
      for (auto& member : value) self(self, member);
    }
  };
  // This includes transition handles, journal record handles, and event
  // source handles while preserving deterministic causes and ordinals.
  normalize_owners(normalize_owners, result);
  return result;
}

struct JournalValue {
  storage::AccountedLayout layout;
  Row values;
  bool operator==(const JournalValue& other) const {
    return layout.same_token(other.layout) && values == other.values;
  }
};

std::vector<JournalValue> retained_values(const std::shared_ptr<const SupportJournal>& journal) {
  check(journal != nullptr, "successful update has no retained support journal");
  std::vector<JournalValue> result;
  result.reserve(journal->records.size());
  for (const auto& record : journal->records) result.push_back({record.tuple().layout(), storage::export_row(record.tuple().values())});
  return result;
}

void check_rollback_statistics(const storage::ArenaStatistics& before,
                               const storage::ArenaStatistics& after,
                               const std::string& context) {
  check(before.pins == after.pins && before.live_records == after.live_records &&
            before.retained_records == after.retained_records,
        context + ": failed apply changed pins or live/retired tuple counts");
}

struct LiveHandle {
  SupportHandle handle;
  storage::Tuple tuple;
  bool operator==(const LiveHandle&) const = default;
};

std::vector<LiveHandle> public_handles(const SupportRuntime& runtime) {
  const auto snapshot = runtime.snapshot();
  std::vector<LiveHandle> result;
  const auto remember = [&](SupportHandle handle, const storage::Tuple& tuple) {
    const auto owned = runtime.get(handle);
    check(owned && *owned == tuple, "snapshot exposed an invalid public support handle");
    result.push_back({handle, *owned});
  };
  for (const auto& node : snapshot.nodes) {
    for (const auto& record : node.records) remember(record.handle, record.tuple);
    for (const auto& tuple : node.survivors) {
      const auto handle = runtime.find(node.node, SupportRole::survivors, crown::storage::export_row(tuple.values()));
      check(handle.has_value(), "survivor snapshot has no public handle");
      remember(*handle, tuple);
    }
    for (const auto& key : node.parent_keys) remember(key.handle, key.key);
    if (node.visible_keys)
      for (const auto& key : *node.visible_keys) remember(key.handle, key.key);
  }
  return result;
}

struct ExpectedResult {
  io::Json snapshot;
  io::Json epoch;
  bool has_answer;
};

ExpectedResult clean_result(const PhysicalPlan& plan, Case which) {
  SupportRuntime runtime{plan, options()};
  const auto previous_journal = initialize(runtime, which);
  static_cast<void>(previous_journal);
  const auto epoch = runtime.apply(target_update(which));
  runtime.check_invariants();
  return {normalized_snapshot(runtime, plan), normalized_epoch(epoch), runtime.has_answer()};
}

void check_expected_state(const SupportRuntime& runtime, Case which, const SupportEpoch& epoch) {
  const NodeId root{0};
  const Row x{n(10)};
  const auto record = runtime.find(root, SupportRole::records, x);
  const auto survivor = runtime.find(root, SupportRole::survivors, x);
  const auto parent_key = runtime.find(root, SupportRole::parent_support, Row{});
  const auto visible_key = runtime.find(root, SupportRole::visible, x);
  const auto root_snapshot = runtime.snapshot().nodes.at(root.value);

  switch (which) {
    case Case::insert_last_child: {
      check(runtime.has_answer() && record && survivor && parent_key && visible_key,
            "last-child insertion did not publish the root survivor and its projections");
      const auto row = std::find_if(root_snapshot.records.begin(), root_snapshot.records.end(),
          [&](const SupportRecordSnapshot& value) { return value.tuple.values() == x; });
      check(row != root_snapshot.records.end() && row->satisfied.value == 2 &&
                row->child_present == std::vector<bool>{true, true} && row->survives,
            "last-child insertion did not mark both generalized-root children present");
      check(epoch.metrics.candidates_created == 0 && epoch.metrics.survivor_transitions == 2 &&
                epoch.metrics.parent_key_transitions == 2 && epoch.metrics.visible_key_transitions == 2,
            "last-child insertion missed generalized survivor or projection transitions");
      break;
    }
    case Case::erase_supported_child: {
      check(!runtime.has_answer() && record && !survivor && !parent_key && !visible_key,
            "supported last-child deletion did not withdraw the root output");
      const auto row = std::find_if(root_snapshot.records.begin(), root_snapshot.records.end(),
          [&](const SupportRecordSnapshot& value) { return value.tuple.values() == x; });
      check(row != root_snapshot.records.end() && row->satisfied.value == 1 &&
                row->child_present == std::vector<bool>{true, false} && !row->survives,
            "deletion removed a generalized candidate that still has R support");
      check(epoch.metrics.candidates_reclaimed == 0 && epoch.metrics.survivor_transitions == 2 &&
                epoch.metrics.parent_key_transitions == 2 && epoch.metrics.visible_key_transitions == 2,
            "supported last-child deletion missed root withdrawal transitions");
      break;
    }
    case Case::erase_redundant_child_support: {
      const auto r_key = runtime.find(NodeId{1}, SupportRole::parent_support, Row{n(10)});
      const auto r_record = runtime.find(NodeId{1}, SupportRole::records,
                                         Row{n(10), s(padded('a'))});
      check(runtime.has_answer() && record && survivor && parent_key && visible_key && r_key &&
                !r_record,
            "deleting one of several child supports removed a still-supported root candidate");
      const auto row = std::find_if(root_snapshot.records.begin(), root_snapshot.records.end(),
          [&](const SupportRecordSnapshot& value) { return value.tuple.values() == x; });
      check(row != root_snapshot.records.end() && row->satisfied.value == 2 &&
                row->child_present == std::vector<bool>{true, true} && row->survives,
            "redundant child-support deletion changed the existing parent child flags or count");
      const auto r_snapshot = runtime.snapshot().nodes.at(1);
      const auto key = std::find_if(r_snapshot.parent_keys.begin(), r_snapshot.parent_keys.end(),
          [&](const ProjectionKeySnapshot& value) { return value.key.values() == Row{n(10)}; });
      check(key != r_snapshot.parent_keys.end() && key->support.value == 1 &&
                epoch.metrics.candidates_reclaimed == 0 && epoch.metrics.survivor_transitions == 1 &&
                epoch.metrics.parent_key_transitions == 0,
            "redundant child-support deletion did not decrement its support count from two to one");
      break;
    }
    case Case::reclaim_candidate:
      check(!runtime.has_answer() && !record && !survivor && !parent_key && !visible_key &&
                root_snapshot.records.empty() && epoch.metrics.candidates_reclaimed == 1 &&
                epoch.metrics.survivor_transitions == 1 && epoch.metrics.parent_key_transitions == 1 &&
                epoch.metrics.visible_key_transitions == 1,
            "last child-key deletion did not reclaim its zero-support generalized candidate");
      break;
  }
}

std::size_t sweep(const PhysicalPlan& plan, Case which) {
  constexpr std::ptrdiff_t max_points = 2048;
  const auto expected = clean_result(plan, which);
  const auto update = target_update(which);
  std::size_t failures = 0;

  for (std::ptrdiff_t step = 0; step < max_points; ++step) {
    SupportRuntime runtime{plan, options()};
    const auto previous_journal = initialize(runtime, which);
    const auto previous_values = retained_values(previous_journal);
    const auto before = normalized_snapshot(runtime, plan);
    const auto sequence = runtime.sequence();
    const auto answer = runtime.has_answer();
    const auto owner = runtime.owner();
    const auto live_visible = runtime.find(NodeId{0}, SupportRole::visible, Row{n(10)});
    const auto live_visible_value = live_visible ? runtime.get(*live_visible) : std::nullopt;
    const auto handles_before = public_handles(runtime);
    const auto storage_before = runtime.storage_statistics();

    bool failed = false;
    std::optional<SupportEpoch> result;
    {
      FaultScope fault(step);
      try {
        result = runtime.apply(update);
      } catch (const std::bad_alloc&) {
        // allocate() leaves fail_after at zero through runtime rollback.
        failed = true;
      }
    }

    if (failed) {
      ++failures;
      check(runtime.sequence() == sequence && runtime.has_answer() == answer && runtime.owner() == owner,
            std::string(case_name(which)) + ": failed apply changed sequence, answer, or owner");
      check(normalized_snapshot(runtime, plan) == before,
            std::string(case_name(which)) + ": failed apply changed snapshot values or public tuple IDs");
      check(public_handles(runtime) == handles_before,
            std::string(case_name(which)) + ": failed apply changed or invalidated a public support handle");
      const auto after_visible = runtime.find(NodeId{0}, SupportRole::visible, Row{n(10)});
      check(after_visible == live_visible &&
                (after_visible ? runtime.get(*after_visible) : std::nullopt) == live_visible_value,
            std::string(case_name(which)) + ": failed apply invalidated a live visible handle");
      check_rollback_statistics(storage_before, runtime.storage_statistics(), case_name(which));
      check(retained_values(previous_journal) == previous_values,
            std::string(case_name(which)) + ": failed apply damaged a previous epoch's pinned values");
      runtime.check_invariants();

      // Reuse the exact sequence after rollback. This also checks that
      // rollback restored the relation-local tuple ID counters.
      const auto retry = runtime.apply(update);
      check(normalized_epoch(retry) == expected.epoch &&
                normalized_snapshot(runtime, plan) == expected.snapshot &&
                runtime.has_answer() == expected.has_answer,
            std::string(case_name(which)) + ": same-sequence retry differed from a clean run");
      check(retry.metrics.work == expected.epoch.at("metrics").at("work").get<std::uint64_t>(),
            std::string(case_name(which)) + ": same-sequence retry used different metric work");
      check(retained_values(previous_journal) == previous_values,
            std::string(case_name(which)) + ": retry damaged a previous epoch's pinned values");
      check_expected_state(runtime, which, retry);
      runtime.check_invariants();
      continue;
    }

    check(failures > 0, std::string(case_name(which)) + ": no allocation failure was injected");
    check(result.has_value() && normalized_epoch(*result) == expected.epoch &&
              normalized_snapshot(runtime, plan) == expected.snapshot && runtime.has_answer() == expected.has_answer,
          std::string(case_name(which)) + ": first non-failing apply differed from a clean run");
    check_expected_state(runtime, which, *result);
    runtime.check_invariants();
    return failures;
  }
  throw std::runtime_error(std::string(case_name(which)) +
      ": allocation fault sweep exceeded 2048 points before reaching success");
}

void check_journal_survives_runtime_destruction(const PhysicalPlan& plan) {
  std::shared_ptr<const SupportJournal> retained;
  std::vector<JournalValue> expected_values;
  const Row s_x{n(10), s(padded('s'))};
  {
    SupportRuntime runtime{plan, options()};
    auto inserted = runtime.apply({1, NodeId{2}, SetOperation::insert, s_x});
    retained = inserted.journal;
    check(retained != nullptr && !retained->records.empty(),
          "insert epoch did not expose a retained affected-record journal");
    expected_values = retained_values(retained);
    const auto source = std::find_if(retained->records.begin(), retained->records.end(),
        [&](const JournalRecord& record) {
          return record.handle.node == NodeId{2} && record.handle.role == SupportRole::records &&
                 record.tuple().values() == s_x;
        });
    check(source != retained->records.end(), "insert journal did not retain its source row");

    inserted.journal.reset();
    const auto erased = runtime.apply({2, NodeId{2}, SetOperation::erase, s_x});
    check(erased.journal != nullptr && !runtime.find(NodeId{2}, SupportRole::records, s_x),
          "later update did not erase the row retained by the previous epoch");
    check(retained_values(retained) == expected_values && source->tuple().values() == s_x,
          "previous epoch journal lost its source value after a later erase");
    runtime.check_invariants();
  }

  check(retained_values(retained) == expected_values,
        "previous epoch journal lost pinned values after runtime destruction");
  const auto source = std::find_if(retained->records.begin(), retained->records.end(),
      [&](const JournalRecord& record) {
        return record.handle.node == NodeId{2} && record.handle.role == SupportRole::records &&
               record.tuple().values() == s_x;
      });
  check(source != retained->records.end() && source->tuple().values() == s_x,
        "source row pin did not survive destruction of its runtime");
}
}  // namespace

int main() {
  try {
    const auto plan = make_plan();
    const auto insert = sweep(plan, Case::insert_last_child);
    const auto supported_erase = sweep(plan, Case::erase_supported_child);
    const auto redundant_support_erase = sweep(plan, Case::erase_redundant_child_support);
    const auto reclaim = sweep(plan, Case::reclaim_candidate);
    check(insert > 0 && supported_erase > 0 && redundant_support_erase > 0 && reclaim > 0,
          "support runtime fault sweep did not exercise every failure path");
    check_journal_survives_runtime_destruction(plan);
    std::cout << "support allocation rollback points: insert_last_child=" << insert
              << " erase_supported_child=" << supported_erase
              << " erase_redundant_child_support=" << redundant_support_erase
              << " reclaim_candidate=" << reclaim << '\n';
  } catch (const std::exception& failure) {
    fail_after = -1;
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
