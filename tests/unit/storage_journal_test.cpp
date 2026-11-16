#include "crown/api/error.hpp"
#include "crown/storage/reference.hpp"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <map>
#include <new>
#include <optional>
#include <random>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

// This test is its own binary so allocation tracking cannot affect other tests.
namespace {
thread_local bool track_allocations = false;
thread_local std::size_t tracked_allocations = 0;
thread_local std::ptrdiff_t fail_after = -1;

[[gnu::noinline]] void* allocate(std::size_t bytes) {
  if (track_allocations) ++tracked_allocations;
  if (fail_after >= 0 && fail_after-- == 0) throw std::bad_alloc{};
  const std::size_t allocation_size = bytes == 0U ? 1U : bytes;
  if (auto* result = std::malloc(allocation_size)) return result;
  throw std::bad_alloc{};
}
}  // namespace

void* operator new(std::size_t bytes) { return allocate(bytes); }
void* operator new[](std::size_t bytes) { return allocate(bytes); }
void operator delete(void* pointer) noexcept { std::free(pointer); }
void operator delete[](void* pointer) noexcept { std::free(pointer); }
void operator delete(void* pointer, std::size_t) noexcept { std::free(pointer); }
void operator delete[](void* pointer, std::size_t) noexcept { std::free(pointer); }

namespace {
using namespace crown;
using namespace crown::storage;
using RowsByValue = std::map<Row, TupleHandle>;
using IndexSlots = std::map<IndexId, std::vector<std::size_t>>;

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}

template <class Action>
void expect_error(Action&& action, std::string_view code) {
  try {
    std::forward<Action>(action)();
  } catch (const Error& failure) {
    check(failure.code() == code, "wrong storage error: " + failure.code());
    return;
  }
  throw std::runtime_error("expected storage error: " + std::string(code));
}

template <class Action>
std::size_t count_allocations(Action&& action) {
  tracked_allocations = 0;
  track_allocations = true;
  fail_after = 0;
  try {
    std::forward<Action>(action)();
  } catch (...) {
    fail_after = -1;
    track_allocations = false;
    throw;
  }
  fail_after = -1;
  track_allocations = false;
  return tracked_allocations;
}

class AllocationFailureScope {
 public:
  explicit AllocationFailureScope(std::ptrdiff_t step) noexcept { fail_after = step; }
  ~AllocationFailureScope() { fail_after = -1; }
  AllocationFailureScope(const AllocationFailureScope&) = delete;
  AllocationFailureScope& operator=(const AllocationFailureScope&) = delete;
};

TupleLayout source_layout() {
  return TupleLayout{LayoutId{1},
    {Field{ScalarType::int64}, Field{ScalarType::string}, Field{ScalarType::boolean},
     Field{ScalarType::date}, Field{ScalarType::decimal}},
    LayoutContext{37, "storage-journal-model"}};
}

Row sample_row(std::int64_t integer, std::string text, bool flag,
               std::string_view day, std::string_view amount) {
  return Row{Value{integer}, Value{std::move(text)}, Value{flag},
             Value{Date::parse(day)}, Value{Decimal::parse(amount)}};
}

std::vector<FieldId> fields_for(const std::vector<std::size_t>& slots) {
  std::vector<FieldId> fields;
  fields.reserve(slots.size());
  for (const auto slot : slots) fields.push_back(FieldId{slot});
  return fields;
}

IndexId add_index(ReferenceTable& table, const TupleLayout& source,
                  const std::vector<std::size_t>& slots, LayoutId target_id) {
  const auto fields = fields_for(slots);
  const auto target = projected_layout(target_id, source, fields);
  return table.add_index(Projection{source, target, fields});
}

Row raw_key(const Row& row, const std::vector<std::size_t>& slots) {
  Row result;
  result.reserve(slots.size());
  for (const auto slot : slots) result.push_back(row.at(slot));
  return result;
}

void compare_model(ReferenceTable& table, const TupleLayout& source,
                   const RowsByValue& rows, const IndexSlots& indexes,
                   const std::string& where) {
  table.check_invariants();
  check(table.size() == rows.size(), where + ": row count differs from model");

  std::set<Row> expected_rows;
  for (const auto& [row, handle] : rows) {
    expected_rows.insert(row);
    const auto found = table.find(source.tuple(row));
    check(found.has_value() && *found == handle, where + ": find differs from model");
    const auto* stored = table.get(handle);
    check(stored != nullptr && stored->values() == row,
          where + ": handle resolves to a different row");
  }
  std::set<Row> snapshot_rows;
  for (const auto& tuple : table.snapshot()) {
    check(tuple.layout().same_token(source), where + ": snapshot layout token changed");
    check(snapshot_rows.insert(crown::storage::export_row(tuple.values())).second, where + ": snapshot repeated a row");
  }
  check(snapshot_rows == expected_rows, where + ": snapshot differs from model");

  std::set<IndexId> expected_indexes;
  for (const auto& [id, slots] : indexes) {
    static_cast<void>(slots);
    expected_indexes.insert(id);
  }
  const auto index_ids = table.indices();
  const std::set<IndexId> actual_indexes(index_ids.begin(), index_ids.end());
  check(actual_indexes == expected_indexes, where + ": index IDs differ from model");

  for (const auto& [id, slots] : indexes) {
    std::map<Row, std::set<Row>> expected_buckets;
    for (const auto& [row, handle] : rows) {
      static_cast<void>(handle);
      expected_buckets[raw_key(row, slots)].insert(row);
    }
    check(table.key_count(id) == expected_buckets.size(),
          where + ": index key count differs from model");
    std::set<Row> expected_keys;
    for (const auto& [key, bucket_rows] : expected_buckets) {
      static_cast<void>(bucket_rows);
      expected_keys.insert(key);
    }
    std::set<Row> actual_keys;
    for (const auto& key : table.keys(id)) {
      check(actual_keys.insert(crown::storage::export_row(key.values())).second, where + ": index repeated a key");
    }
    check(actual_keys == expected_keys, where + ": index keys differ from model");

    const auto target = table.projection(id).target();
    for (const auto& [key, bucket_rows] : expected_buckets) {
      const auto lookup = target.tuple(key);
      std::set<TupleHandle> expected_handles;
      for (const auto& row : bucket_rows) expected_handles.insert(rows.at(row));
      const auto bucket = table.bucket(id, lookup);
      const std::set<TupleHandle> actual_handles(bucket.begin(), bucket.end());
      check(actual_handles == expected_handles,
            where + ": index bucket differs from raw-slot model");
    }
  }
}

void lock_and_noop_contract() {
  const auto layout = source_layout();
  ReferenceTable table{RelationId{41}, layout};
  const auto row = sample_row(1, "one", true, "2024-02-29", "1.00");
  const auto absent = sample_row(99, "absent", false, "1969-12-31", "-2.5");
  const auto original = table.insert(layout.tuple(row)).handle;
  const auto index = add_index(table, layout, {0}, LayoutId{2});
  auto cursor = table.live();
  ReferenceTable other{RelationId{41}, layout};
  const auto foreign = other.insert(layout.tuple(row)).handle;

  const auto revision = table.revision();
  auto journal = table.journal();
  check(journal.active() && journal.size() == 0U, "new journal is not empty and active");

  expect_error([&] { static_cast<void>(table.insert(layout.tuple(row))); }, "storage_busy");
  expect_error([&] { static_cast<void>(table.erase(layout.tuple(absent))); }, "storage_busy");
  expect_error([&] { static_cast<void>(table.erase(original)); }, "storage_busy");
  expect_error([&] { static_cast<void>(table.add_index(table.projection(index))); }, "storage_busy");
  expect_error([&] { static_cast<void>(table.drop_index(index)); }, "storage_busy");
  expect_error([&] {
    static_cast<void>(table.erase_key(index,
      table.projection(index).target().tuple(Row{Value{std::int64_t{1}}})));
  }, "storage_busy");
  expect_error([&] { table.clear(); }, "storage_busy");
  expect_error([&] { static_cast<void>(table.live()); }, "storage_busy");
  expect_error([&] {
    static_cast<void>(table.bucket_cursor(index,
      table.projection(index).target().tuple(Row{Value{std::int64_t{1}}})));
  }, "storage_busy");
  expect_error([&] { static_cast<void>(cursor.next()); }, "storage_busy");

  check(table.size() == 1U && table.revision() == revision,
        "failed direct mutations changed the table");
  check(table.find(layout.tuple(row)) == original && table.get(original) != nullptr,
        "table reads were blocked during a journal");
  check(table.snapshot().size() == 1U && table.bucket(index,
        table.projection(index).target().tuple(Row{Value{std::int64_t{1}}})).size() == 1U,
        "snapshot or index reads were blocked during a journal");
  table.check_invariants();

  expect_error([&] { static_cast<void>(journal.erase(foreign)); }, "foreign_handle");
  check(journal.size() == 0U, "foreign erase was recorded");
  const auto duplicate = journal.insert(layout.tuple(row));
  check(!duplicate.inserted && duplicate.handle == original && journal.size() == 0U,
        "duplicate journal insertion was recorded or changed identity");
  check(!journal.erase(TupleHandle{original.owner, original.relation, TupleId{99999}}),
        "erasing a missing local handle reported a change");
  check(journal.size() == 0U, "missing-handle erase was recorded");

  check(journal.erase(original), "journal failed to erase a live handle");
  check(!journal.erase(original), "journal repeated an erase of an absent handle");
  const auto reinserted = journal.insert(layout.tuple(row));
  check(reinserted.inserted, "journal did not insert a row after erasing it");
  check(journal.size() == 2U, "journal did not record only logical changes");
  const auto erased_change = journal.change(0U);
  const auto inserted_change = journal.change(1U);
  check(!erased_change.inserted && erased_change.handle == original &&
        erased_change.tuple.values() == row, "erase change view is incorrect");
  check(inserted_change.inserted && inserted_change.handle == reinserted.handle &&
        inserted_change.tuple.values() == row, "insert change view is incorrect");

  journal.rollback();
  journal.rollback();
  journal.commit();
  check(!journal.active(), "rolled-back journal remained active");
  check(table.find(layout.tuple(row)) == original && table.get(original) != nullptr,
        "rollback did not restore the original row and handle");
  check(table.revision() != revision, "rollback did not leave an advanced revision");
  expect_error([&] { static_cast<void>(journal.insert(layout.tuple(absent))); }, "invalid_journal");
  expect_error([&] { static_cast<void>(journal.erase(original)); }, "invalid_journal");
  expect_error([&] { static_cast<void>(cursor.next()); }, "invalid_cursor");
  table.check_invariants();
}

struct PinnedIdentity {
  Row row;
  TupleHandle tuple_handle;
  ArenaHandle arena_handle;
  const Tuple* address;
  TupleArena::Pin pin;
};

void rollback_restores_rows_indexes_and_generations() {
  const auto layout = source_layout();
  ReferenceTable table{RelationId{42}, layout};
  const auto by_integer = add_index(table, layout, {0}, LayoutId{3});
  const auto by_text = add_index(table, layout, {1}, LayoutId{4});
  const auto nullary = add_index(table, layout, {}, LayoutId{5});
  const IndexSlots index_slots{{by_integer, {0}}, {by_text, {1}}, {nullary, {}}};
  const std::vector<Row> original_rows{
    sample_row(7, "shared", true, "2024-02-29", "1.00"),
    sample_row(7, "shared", false, "2000-02-29", "2.5"),
    sample_row(7, "other", true, "1969-12-31", "-2.5"),
    sample_row(8, "shared", false, "9999-12-31", "0.0001"),
    sample_row(8, "last", true, "2024-02-29", "100")};
  RowsByValue original_model;
  std::vector<PinnedIdentity> identities;
  identities.reserve(original_rows.size());
  for (const auto& row : original_rows) {
    const auto handle = table.insert(layout.tuple(row)).handle;
    check(original_model.emplace(row, handle).second, "duplicate rollback fixture row");
    auto pin = table.pin(handle);
    identities.push_back(PinnedIdentity{row, handle, pin.handle(), &pin.get(), std::move(pin)});
  }
  compare_model(table, layout, original_model, index_slots, "rollback fixture");
  const auto original_revision = table.revision();
  auto cursor = table.live();
  std::vector<std::pair<bool, std::pair<TupleHandle, Row>>> expected_changes;
  const auto tentative = sample_row(7, "new", true, "2000-02-29", "1.00");

  {
    auto journal = table.journal();
    RowsByValue tentative_model = original_model;
    for (const auto& row : original_rows) {
      const auto handle = tentative_model.at(row);
      check(journal.erase(handle), "journal failed to erase an original row");
      expected_changes.push_back({false, {handle, row}});
      tentative_model.erase(row);
      compare_model(table, layout, tentative_model, index_slots,
                    "journal after shared-bucket erase");
    }
    check(table.key_count(nullary) == 0U,
          "journal erase of every row left the nullary key registered");

    const auto first_insert = journal.insert(layout.tuple(tentative));
    check(first_insert.inserted, "journal insertion of tentative row failed");
    expected_changes.push_back({true, {first_insert.handle, tentative}});
    tentative_model.emplace(tentative, first_insert.handle);
    const auto duplicate = journal.insert(layout.tuple(tentative));
    check(!duplicate.inserted && duplicate.handle == first_insert.handle,
          "duplicate tentative insertion changed identity");
    check(journal.size() == expected_changes.size(),
          "duplicate tentative insertion added a journal entry");
    check(journal.erase(first_insert.handle), "could not erase tentative insertion");
    expected_changes.push_back({false, {first_insert.handle, tentative}});
    tentative_model.erase(tentative);
    check(!journal.erase(first_insert.handle), "second tentative erase reported a change");

    const auto second_insert = journal.insert(layout.tuple(tentative));
    check(second_insert.inserted, "reinsert after tentative erase failed");
    expected_changes.push_back({true, {second_insert.handle, tentative}});
    tentative_model.emplace(tentative, second_insert.handle);
    compare_model(table, layout, tentative_model, index_slots,
                  "journal after erase and reinsert");

    check(journal.size() == expected_changes.size(), "journal change count is incorrect");
    for (std::size_t i = 0; i < expected_changes.size(); ++i) {
      const auto view = journal.change(i);
      const auto& expected = expected_changes[i];
      check(view.inserted == expected.first && view.handle == expected.second.first &&
            view.tuple.values() == expected.second.second,
            "journal change order or payload is incorrect");
    }
    expect_error([&] { static_cast<void>(cursor.next()); }, "storage_busy");
    journal.rollback();
    check(!journal.active(), "explicit rollback did not close the journal");
    journal.rollback();
    compare_model(table, layout, original_model, index_slots, "rolled-back model");
    check(table.revision() != original_revision,
          "rollback did not advance revision after tentative mutations");
    expect_error([&] { static_cast<void>(cursor.next()); }, "invalid_cursor");
  }

  for (const auto& identity : identities) {
    check(identity.pin.is_live() && identity.pin.handle() == identity.arena_handle,
          "rollback changed a pinned arena handle or generation");
    check(&identity.pin.get() == identity.address && identity.pin.get().values() == identity.row,
          "rollback moved or changed the original pinned payload");
    check(table.get(identity.tuple_handle) == identity.address,
          "rollback changed the original tuple address");
  }
  const auto statistics = table.arena_statistics();
  check(statistics.live_records == original_rows.size() && statistics.retained_records == 0U &&
        statistics.pins == identities.size(),
        "rollback left temporary payloads retained after journal destruction");
  table.check_invariants();
}

void committed_changes_keep_payloads_after_clear_and_destruction() {
  const auto layout = source_layout();
  const auto first_row = sample_row(1, "first", true, "2024-02-29", "1.00");
  const auto second_row = sample_row(1, "second", false, "2000-02-29", "2.5");
  const auto third_row = sample_row(1, "third", true, "1969-12-31", "-2.5");
  std::optional<ReferenceTable::Journal> retained;
  std::vector<bool> expected_inserted;
  std::vector<TupleHandle> expected_handles;
  std::vector<Row> expected_rows;
  std::vector<const Tuple*> expected_addresses;

  {
    ReferenceTable table{RelationId{43}, layout};
    const auto first = table.insert(layout.tuple(first_row)).handle;
    const auto second = table.insert(layout.tuple(second_row)).handle;
    retained.emplace(table.journal());
    auto& journal = *retained;
    check(journal.erase(first), "commit fixture could not erase first row");
    const auto inserted = journal.insert(layout.tuple(third_row));
    check(inserted.inserted, "commit fixture could not insert third row");
    check(journal.erase(second), "commit fixture could not erase second row");
    const auto reinserted = journal.insert(layout.tuple(second_row));
    check(reinserted.inserted && reinserted.handle != second,
          "reinsertion did not allocate a fresh logical tuple handle");

    check(journal.size() == 4U, "commit fixture recorded the wrong change count");
    for (std::size_t i = 0; i < journal.size(); ++i) {
      const auto view = journal.change(i);
      expected_inserted.push_back(view.inserted);
      expected_handles.push_back(view.handle);
      expected_rows.push_back(crown::storage::export_row(view.tuple.values()));
      expected_addresses.push_back(&view.tuple);
    }
    journal.commit();
    journal.commit();
    check(!journal.active() && journal.size() == 4U,
          "committed journal lost its change views");
    expect_error([&] { static_cast<void>(journal.insert(layout.tuple(first_row))); },
                 "invalid_journal");
    expect_error([&] { static_cast<void>(journal.erase(first)); }, "invalid_journal");

    // The committed journal releases the table's write lock. The ordinary
    // clear retires every changed record while the journal keeps its payloads.
    table.clear();
    check(table.size() == 0U, "post-commit clear failed");
    table.check_invariants();
    for (std::size_t i = 0; i < journal.size(); ++i) {
      const auto view = journal.change(i);
      check(view.inserted == expected_inserted[i] && view.handle == expected_handles[i] &&
            view.tuple.values() == expected_rows[i] && &view.tuple == expected_addresses[i],
            "committed change payload did not survive clear");
    }

    auto moved = std::move(journal);
    check(!journal.active() && journal.size() == 0U,
          "moved-from journal retained active state or changes");
    check(!moved.active() && moved.size() == expected_rows.size(),
          "moving a committed journal lost its retained changes");
    retained.emplace(std::move(moved));
  }

  check(retained.has_value() && !retained->active(),
        "committed journal did not outlive its table");
  for (std::size_t i = 0; i < expected_rows.size(); ++i) {
    const auto view = retained->change(i);
    check(view.inserted == expected_inserted[i] && view.handle == expected_handles[i] &&
          view.tuple.values() == expected_rows[i] && &view.tuple == expected_addresses[i],
          "committed change payload did not survive table destruction");
  }
  retained->rollback();
  retained->commit();
}

void move_assignment_and_destructor_rollback() {
  const auto layout = source_layout();
  ReferenceTable left{RelationId{44}, layout};
  ReferenceTable right{RelationId{45}, layout};
  const auto left_row = sample_row(11, "left", true, "2024-02-29", "11");
  const auto right_row = sample_row(12, "right", false, "2000-02-29", "12");
  const auto left_handle = left.insert(layout.tuple(left_row)).handle;
  const auto right_handle = right.insert(layout.tuple(right_row)).handle;
  const auto left_revision = left.revision();
  const auto right_revision = right.revision();

  auto destination = left.journal();
  check(destination.erase(left_handle), "move-assignment fixture left erase failed");
  auto source = right.journal();
  check(source.erase(right_handle), "move-assignment fixture right erase failed");
  destination = std::move(source);
  check(!source.active() && source.size() == 0U,
        "move-assigned-from journal retained state");
  check(left.find(layout.tuple(left_row)) == left_handle && left.revision() != left_revision,
        "move assignment did not roll back the destination journal");
  expect_error([&] { static_cast<void>(right.live()); }, "storage_busy");
  destination.rollback();
  check(right.find(layout.tuple(right_row)) == right_handle && right.revision() != right_revision,
        "moved journal did not roll back against its new owner");

  const auto destructor_revision = left.revision();
  {
    auto journal = left.journal();
    check(journal.erase(left_handle), "destructor fixture erase failed");
  }
  check(left.find(layout.tuple(left_row)) == left_handle &&
        left.revision() != destructor_revision,
        "journal destruction did not roll back and invalidate the revision");
  left.check_invariants();
  right.check_invariants();
}

void rollback_and_commit_do_not_allocate() {
  static_assert(noexcept(std::declval<ReferenceTable::Journal&>().rollback()));
  static_assert(noexcept(std::declval<ReferenceTable::Journal&>().commit()));
  const auto layout = source_layout();
  ReferenceTable table{RelationId{46}, layout};
  const auto existing = sample_row(21, "existing", true, "2024-02-29", "21");
  const auto added = sample_row(22, "added", false, "2000-02-29", "22");
  const auto handle = table.insert(layout.tuple(existing)).handle;

  auto rollback_journal = table.journal();
  check(rollback_journal.erase(handle), "no-allocation rollback fixture erase failed");
  static_cast<void>(rollback_journal.insert(layout.tuple(added)));
  check(count_allocations([&] { rollback_journal.rollback(); }) == 0U,
        "journal rollback made an intercepted global-new attempt");
  check(table.find(layout.tuple(existing)) == handle,
        "no-allocation rollback failed to restore its row");

  std::optional<ReferenceTable::Journal> destructor_journal;
  destructor_journal.emplace(table.journal());
  check(destructor_journal->erase(handle), "no-allocation destructor fixture erase failed");
  check(count_allocations([&] { destructor_journal.reset(); }) == 0U,
        "active journal destruction made an intercepted global-new attempt");
  check(table.find(layout.tuple(existing)) == handle,
        "no-allocation destruction failed to restore its row");

  auto commit_journal = table.journal();
  static_cast<void>(commit_journal.insert(layout.tuple(added)));
  check(count_allocations([&] { commit_journal.commit(); }) == 0U,
        "journal commit made an intercepted global-new attempt");
  table.check_invariants();
}

struct AllocationFixture {
  TupleLayout layout;
  ReferenceTable table;
  IndexSlots indexes;
  RowsByValue rows;

  AllocationFixture()
      : layout(source_layout()), table(RelationId{48}, layout) {
    const auto by_integer = add_index(table, layout, {0}, LayoutId{20});
    const auto by_text = add_index(table, layout, {1}, LayoutId{21});
    const auto nullary = add_index(table, layout, {}, LayoutId{22});
    indexes = {{by_integer, {0}}, {by_text, {1}}, {nullary, {}}};
    for (std::size_t i = 0; i < 9U; ++i) {
      const auto number = static_cast<std::int64_t>(i);
      const auto row = sample_row(number % 3, "group" + std::to_string(i % 2U),
        (i & 1U) != 0U, "2024-02-29", std::to_string(i + 1U));
      const auto inserted = table.insert(layout.tuple(row));
      check(inserted.inserted, "allocation fixture unexpectedly duplicated a row");
      rows.emplace(row, inserted.handle);
    }
  }
};

std::size_t journal_insert_allocation_failures() {
  std::size_t failures = 0;
  for (std::ptrdiff_t step = 0; step < 512; ++step) {
    AllocationFixture fixture;
    const auto candidate = sample_row(77, "journal-allocation", true,
                                      "2000-02-29", "0.0001");
    const auto candidate_tuple = fixture.layout.tuple(candidate);
    std::uint64_t largest_tuple_id = 0;
    for (const auto& [row, handle] : fixture.rows) {
      static_cast<void>(row);
      largest_tuple_id = std::max(largest_tuple_id, handle.tuple.value);
    }
    auto journal = fixture.table.journal();
    const auto before_revision = fixture.table.revision();
    bool failed = false;
    std::optional<InsertResult> outcome;
    {
      [[maybe_unused]] AllocationFailureScope failure_scope{step};
      try {
        outcome = journal.insert(candidate_tuple);
      } catch (const std::bad_alloc&) {
        failed = true;
      }
    }

    if (failed) {
      ++failures;
      check(journal.active() && journal.size() == 0U,
            "failed journal insert published an entry");
      check(fixture.table.revision() == before_revision,
            "failed journal insert advanced the revision");
      compare_model(fixture.table, fixture.layout, fixture.rows, fixture.indexes,
                    "failed journal insertion state");
      const auto retry = journal.insert(candidate_tuple);
      check(retry.inserted && retry.handle.tuple.value == largest_tuple_id + 1U,
            "failed journal insert consumed a tuple ID");
      journal.rollback();
      compare_model(fixture.table, fixture.layout, fixture.rows, fixture.indexes,
                    "journal insertion retry rollback");
      continue;
    }

    check(outcome.has_value() && outcome->inserted && journal.size() == 1U,
          "journal insertion fault sweep did not eventually insert");
    check(outcome->handle.tuple.value == largest_tuple_id + 1U,
          "successful journal insertion allocated an unexpected ID");
    journal.rollback();
    compare_model(fixture.table, fixture.layout, fixture.rows, fixture.indexes,
                  "successful journal insertion rollback");
    return failures;
  }
  throw std::runtime_error("journal insertion fault sweep did not reach success");
}

std::size_t journal_erase_allocation_failures() {
  std::size_t failures = 0;
  for (std::ptrdiff_t step = 0; step < 512; ++step) {
    AllocationFixture fixture;
    const auto target = fixture.rows.begin();
    const auto target_row = target->first;
    const auto target_handle = target->second;
    auto journal = fixture.table.journal();
    const auto before_revision = fixture.table.revision();
    bool failed = false;
    bool erased = false;
    {
      [[maybe_unused]] AllocationFailureScope failure_scope{step};
      try {
        erased = journal.erase(target_handle);
      } catch (const std::bad_alloc&) {
        failed = true;
      }
    }

    if (failed) {
      ++failures;
      check(journal.active() && journal.size() == 0U,
            "failed journal erase published an entry");
      check(fixture.table.revision() == before_revision,
            "failed journal erase advanced the revision");
      compare_model(fixture.table, fixture.layout, fixture.rows, fixture.indexes,
                    "failed journal erase state");
      check(journal.erase(target_handle), "journal erase retry failed");
      journal.rollback();
      check(fixture.table.find(fixture.layout.tuple(target_row)) == target_handle,
            "journal erase retry rollback changed tuple identity");
      compare_model(fixture.table, fixture.layout, fixture.rows, fixture.indexes,
                    "journal erase retry rollback");
      continue;
    }

    check(erased && journal.size() == 1U,
          "journal erase fault sweep did not eventually erase");
    auto reduced = fixture.rows;
    reduced.erase(target_row);
    compare_model(fixture.table, fixture.layout, reduced, fixture.indexes,
                  "successful tentative journal erase");
    journal.rollback();
    compare_model(fixture.table, fixture.layout, fixture.rows, fixture.indexes,
                  "successful journal erase rollback");
    return failures;
  }
  throw std::runtime_error("journal erase fault sweep did not reach success");
}

std::size_t pick(std::mt19937_64& random, std::size_t bound) {
  return static_cast<std::size_t>(random() % static_cast<std::uint64_t>(bound));
}

Row random_row(std::mt19937_64& random) {
  static const std::vector<std::string> texts{
    "", "a", "b", std::string("n\0ul", 4), "é"};
  static const std::vector<Date> dates{
    Date::parse("1969-12-31"), Date::parse("2000-02-29"), Date::parse("2024-02-29")};
  static const std::vector<Decimal> amounts{
    Decimal::parse("0"), Decimal::parse("-2.5"), Decimal::parse("1.00"),
    Decimal::parse("0.0001")};
  const auto integer = static_cast<std::int64_t>(random() % 7U) - 3;
  return Row{Value{integer}, Value{texts[pick(random, texts.size())]},
    Value{(random() & 1U) != 0U}, Value{dates[pick(random, dates.size())]},
    Value{amounts[pick(random, amounts.size())]}};
}

void randomized_journal_model() {
  std::size_t operations = 0;
  for (std::uint64_t seed = 1; seed <= 12; ++seed) {
    const auto layout = source_layout();
    ReferenceTable table{RelationId{47}, layout};
    const auto by_integer = add_index(table, layout, {0}, LayoutId{10});
    const auto by_text = add_index(table, layout, {1}, LayoutId{11});
    const auto by_flag_and_date = add_index(table, layout, {2, 3}, LayoutId{12});
    const auto nullary = add_index(table, layout, {}, LayoutId{13});
    const IndexSlots indexes{{by_integer, {0}}, {by_text, {1}},
                             {by_flag_and_date, {2, 3}}, {nullary, {}}};
    RowsByValue rows;
    std::mt19937_64 random{seed};
    for (std::size_t i = 0; i < 16U; ++i) {
      const auto row = random_row(random);
      const auto result = table.insert(layout.tuple(row));
      if (result.inserted) rows.emplace(row, result.handle);
    }
    compare_model(table, layout, rows, indexes, "random model initial state");

    for (std::size_t transaction = 0; transaction < 90U; ++transaction) {
      auto cursor = table.live();
      const auto before_revision = table.revision();
      const RowsByValue before_rows = rows;
      bool has_real_change = false;
      auto journal = table.journal();

      for (std::size_t step = 0; step < 12U; ++step) {
        const auto choice = random() % 10U;
        if (choice < 5U) {
          const auto candidate = random_row(random);
          const auto prior = rows.find(candidate);
          const auto result = journal.insert(layout.tuple(candidate));
          check(result.inserted == (prior == rows.end()),
                "random journal insert disagreed with independent map model");
          if (prior == rows.end()) {
            rows.emplace(candidate, result.handle);
            has_real_change = true;
          } else {
            check(result.handle == prior->second,
                  "random duplicate journal insert changed tuple identity");
          }
        } else if (choice < 9U) {
          const auto candidate = random_row(random);
          const auto prior = rows.find(candidate);
          if ((random() & 1U) != 0U && prior != rows.end()) {
            const auto handle = prior->second;
            check(journal.erase(handle), "random journal handle erase missed a row");
            rows.erase(prior);
            has_real_change = true;
          } else if (prior != rows.end()) {
            check(!journal.erase(TupleHandle{table.owner(), table.relation(), TupleId{0}}),
                  "random journal erase of a missing handle changed state");
          } else {
            check(!journal.erase(TupleHandle{table.owner(), table.relation(), TupleId{0}}),
                  "random journal erase of an absent row changed state");
          }
        } else {
          // Remove all rows represented by a selected secondary key. The
          // model computes raw source slots independently of Projection::apply.
          const auto chosen = random_row(random);
          const std::vector<std::size_t> slots = (random() & 1U) != 0U
            ? std::vector<std::size_t>{0} : std::vector<std::size_t>{1};
          const auto key_row = raw_key(chosen, slots);
          std::vector<Row> matching;
          for (const auto& [row, handle] : rows) {
            static_cast<void>(handle);
            if (raw_key(row, slots) == key_row) matching.push_back(row);
          }
          for (const auto& row : matching) {
            check(journal.erase(rows.at(row)), "random shared-bucket erase missed a row");
            rows.erase(row);
            has_real_change = true;
          }
        }
        compare_model(table, layout, rows, indexes, "random tentative journal state");
        ++operations;
      }

      const bool commit = (random() & 1U) != 0U;
      if (commit) {
        journal.commit();
      } else {
        journal.rollback();
        rows = before_rows;
      }
      check(!journal.active(), "random transaction did not finish");
      compare_model(table, layout, rows, indexes,
                    commit ? "random committed state" : "random rolled-back state");
      if (has_real_change) {
        check(table.revision() != before_revision,
              "random journal failed to leave revision advanced");
        expect_error([&] { static_cast<void>(cursor.next()); }, "invalid_cursor");
      } else {
        check(table.revision() == before_revision,
              "random journal no-op transaction advanced revision");
        static_cast<void>(cursor.next());
      }
    }
  }
  std::cout << "reference journal model: " << operations
            << " tentative operations across 12 seeds\n";
}
}  // namespace

int main() {
  try {
    lock_and_noop_contract();
    rollback_restores_rows_indexes_and_generations();
    committed_changes_keep_payloads_after_clear_and_destruction();
    move_assignment_and_destructor_rollback();
    rollback_and_commit_do_not_allocate();
    const auto insert_failures = journal_insert_allocation_failures();
    const auto erase_failures = journal_erase_allocation_failures();
    std::cout << "reference journal allocation failures: insert=" << insert_failures
              << ", erase=" << erase_failures << '\n';
    randomized_journal_model();
    std::cout << "reference storage journal contract passed\n";
    return 0;
  } catch (const std::exception& failure) {
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
