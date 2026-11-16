#include "crown/api/error.hpp"
#include "crown/storage/reference.hpp"

#include <cstddef>
#include <cstdlib>
#include <cstdint>
#include <iostream>
#include <new>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

// This binary injects failures at ordinary global-new allocation attempts.
// Direct allocator calls and aligned-new overloads are outside this seam.
namespace {
thread_local std::ptrdiff_t fail_after = -1;
[[gnu::noinline]] void* malloc_new(std::size_t bytes) {
  if (fail_after >= 0 && fail_after-- == 0) throw std::bad_alloc{};
  if (auto* result = std::malloc(bytes == 0 ? 1 : bytes)) return result;
  throw std::bad_alloc{};
}
struct ResetFailure {
  ~ResetFailure() { fail_after = -1; }
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
using namespace crown::storage;

void check(bool condition, std::string_view message) {
  if (!condition) throw std::runtime_error(std::string(message));
}

template <class Action>
void expect_error(Action&& action, std::string_view code) {
  try {
    action();
  } catch (const Error& failure) {
    check(failure.code() == code, "unexpected storage error code");
    return;
  }
  throw std::runtime_error(std::string("expected storage error: ") + std::string(code));
}

TupleLayout source_layout() {
  return TupleLayout{LayoutId{1},
      {Field{ScalarType::int64}, Field{ScalarType::string}, Field{ScalarType::decimal, DecimalSpec{18, 2}},
       Field{ScalarType::int64}}};
}

std::string long_text(char fill, std::string_view suffix) {
  std::string result(240, fill);
  result.append(suffix);
  return result;
}

Tuple make_row(const TupleLayout& layout, std::int64_t group, std::string value,
               std::string_view amount, std::int64_t ordinal) {
  return layout.tuple(Row{Value{group}, Value{std::move(value)}, Value{Decimal::parse(amount)}, Value{ordinal}});
}

struct Fixture {
  TupleLayout layout{source_layout()};
  ReferenceTable table{RelationId{7}, layout};
  std::vector<Tuple> rows;
  std::vector<TupleHandle> handles;
  std::vector<TupleArena::Pin> pins;
  std::vector<ArenaHandle> pin_handles;
  std::vector<IndexId> indexes;

  Fixture() {
    rows.push_back(make_row(layout, 1, long_text('a', "-shared"), "1.25", 10));
    rows.push_back(make_row(layout, 1, long_text('a', "-shared"), "2.50", 11));
    rows.push_back(make_row(layout, 1, long_text('b', "-shared"), "2.50", 12));
    rows.push_back(make_row(layout, 2, long_text('b', "-shared"), "3.75", 13));
    rows.push_back(make_row(layout, 2, long_text('c', "-single"), "3.75", 14));
    rows.push_back(make_row(layout, 3, long_text('d', "-single"), "4.00", 15));
    handles.reserve(rows.size());
    for (const auto& row : rows) {
      const auto result = table.insert(row);
      check(result.inserted, "fixture row unexpectedly duplicated");
      handles.push_back(result.handle);
    }

    const std::vector<std::vector<std::size_t>> shapes{{0}, {1}, {2}, {0, 2}, {3}};
    indexes.reserve(shapes.size());
    for (std::size_t i = 0; i < shapes.size(); ++i) {
      std::vector<FieldId> fields;
      fields.reserve(shapes[i].size());
      for (const auto field : shapes[i]) fields.push_back(FieldId{field});
      auto target = projected_layout(LayoutId{static_cast<std::size_t>(20 + i)}, layout, fields);
      indexes.push_back(table.add_index(Projection{layout, std::move(target), std::move(fields)}));
    }

    pins.reserve(handles.size());
    pin_handles.reserve(handles.size());
    for (const auto handle : handles) {
      pins.push_back(table.pin(handle));
      pin_handles.push_back(pins.back().handle());
    }
  }
};

struct IndexImage {
  IndexId id;
  std::vector<Tuple> keys;
  std::vector<std::vector<TupleHandle>> buckets;
};

struct TableImage {
  std::vector<Tuple> rows;
  std::vector<TupleHandle> handles;
  std::vector<const Tuple*> addresses;
  std::vector<IndexImage> indexes;
  ArenaStatistics arena;
};

TableImage capture(const ReferenceTable& table) {
  TableImage result;
  result.rows = table.snapshot();
  result.handles.reserve(result.rows.size());
  result.addresses.reserve(result.rows.size());
  for (const auto& row : result.rows) {
    const auto handle = table.find(row);
    check(handle.has_value(), "snapshot row has no handle");
    result.handles.push_back(*handle);
    result.addresses.push_back(table.get(*handle));
  }
  const auto ids = table.indices();
  result.indexes.reserve(ids.size());
  for (const auto id : ids) {
    IndexImage index{id, table.keys(id), {}};
    index.buckets.reserve(index.keys.size());
    for (const auto& key : index.keys) index.buckets.push_back(table.bucket(id, key));
    result.indexes.push_back(std::move(index));
  }
  result.arena = table.arena_statistics();
  return result;
}

void expect_image(const ReferenceTable& table, const TableImage& before,
                  const Fixture& fixture) {
  const auto after_rows = table.snapshot();
  check(after_rows == before.rows, "journal rollback did not restore full rows");
  check(table.size() == before.rows.size(), "journal rollback changed primary row count");
  check(table.indices().size() == before.indexes.size(), "journal rollback changed index count");
  for (std::size_t i = 0; i < before.indexes.size(); ++i) {
    const auto& expected = before.indexes[i];
    check(table.indices()[i] == expected.id, "journal rollback changed an index ID");
    const auto keys = table.keys(expected.id);
    check(keys == expected.keys, "journal rollback changed index keys");
    check(table.key_count(expected.id) == expected.keys.size(), "journal rollback changed key count");
    for (std::size_t key = 0; key < expected.keys.size(); ++key) {
      check(table.bucket(expected.id, expected.keys[key]) == expected.buckets[key],
            "journal rollback changed index bucket members");
    }
  }
  for (std::size_t i = 0; i < before.rows.size(); ++i) {
    check(table.find(before.rows[i]) == before.handles[i], "journal rollback changed a prior logical handle");
    check(table.get(before.handles[i]) == before.addresses[i], "journal rollback changed a prior tuple address");
  }
  for (std::size_t i = 0; i < fixture.handles.size(); ++i) {
    check(fixture.pins[i].is_live(), "journal rollback did not revive a pinned tuple");
    check(fixture.pins[i].handle() == fixture.pin_handles[i], "journal rollback changed a pinned generation");
    check(&fixture.pins[i].get() == table.get(fixture.handles[i]), "pinned tuple address diverged from restored row");
  }
  const auto stats = table.arena_statistics();
  check(stats.live_records == before.arena.live_records, "journal rollback changed live arena count");
  check(stats.retained_records == before.arena.retained_records, "journal rollback changed retained arena count");
  check(stats.pins == before.arena.pins, "journal rollback changed explicit pin count");
  table.check_invariants();
}

Tuple retry_row(const TupleLayout& layout) {
  return make_row(layout, 8, long_text('r', "-retry"), "9.99", 90);
}

struct TransactionRows {
  Tuple first;
  Tuple second;
  Tuple retry_value;
  explicit TransactionRows(const TupleLayout& layout)
      : first(make_row(layout, 1, long_text('x', "-new-one"), "8.25", 80)),
        second(make_row(layout, 4, long_text('y', "-new-two"), "8.25", 81)),
        retry_value(retry_row(layout)) {}
};

void apply_mixed_transaction(ReferenceTable::Journal& journal, Fixture& fixture,
                             const TransactionRows& rows) {
  const auto first = journal.insert(rows.first);
  check(first.inserted && first.handle.tuple.value == 7, "first journal insert consumed the wrong ID");
  const auto second = journal.insert(rows.second);
  check(second.inserted && second.handle.tuple.value == 8, "second journal insert consumed the wrong ID");
  check(journal.erase(fixture.handles[4]), "journal failed to erase a singleton-key row");
  check(journal.erase(fixture.handles[3]), "journal failed to erase the final shared-bucket member");
  check(!journal.erase(fixture.handles[3]), "repeated journal erase was not a no-op");
  const auto restored_value = journal.insert(fixture.rows[4]);
  check(restored_value.inserted && restored_value.handle.tuple.value == 9,
        "journal failed to reinsert an erased value with a new logical ID");
  check(journal.erase(restored_value.handle), "journal failed to erase a reinserted value");
  check(!journal.erase(restored_value.handle), "repeated erase of a reinserted value was not a no-op");
  const auto reinserted_again = journal.insert(fixture.rows[4]);
  check(reinserted_again.inserted && reinserted_again.handle.tuple.value == 10,
        "journal failed to reinsert a value more than once");
  check(journal.erase(first.handle), "journal failed to erase an earlier successful insert");
}

std::size_t allocation_failures() {
  std::size_t failures = 0;
  std::size_t mutated_failures = 0;
  for (std::ptrdiff_t step = 0; step < 2048; ++step) {
    Fixture fixture;
    const auto before = capture(fixture.table);
    const auto old_revision = fixture.table.revision();
    auto live = fixture.table.live();
    const auto group_key = fixture.table.projection(fixture.indexes[0]).target()
                               .tuple(Row{Value{std::int64_t{1}}});
    auto bucket = fixture.table.bucket_cursor(fixture.indexes[0], group_key);
    const TransactionRows rows(fixture.layout);
    bool failed = false;
    {
      ResetFailure reset;
      fail_after = step;
      try {
        {
          auto journal = fixture.table.journal();
          try {
            apply_mixed_transaction(journal, fixture, rows);
          } catch (const std::bad_alloc&) {
            failed = true;
            fail_after = 0;  // Keep failure injection active through no-throw destruction.
            throw;
          }
          fail_after = 0;
        }
      } catch (const std::bad_alloc&) {
        failed = true;
        fail_after = 0;
      }
    }
    if (failed) ++failures;
    expect_image(fixture.table, before, fixture);
    if (failed && fixture.table.revision() != old_revision) ++mutated_failures;
    if (fixture.table.revision() == old_revision) {
      check(live.next().has_value(), "journal begin failure invalidated a cursor without mutation");
      check(bucket.next().has_value(), "journal begin failure invalidated a bucket cursor without mutation");
    } else {
      expect_error([&live] { static_cast<void>(live.next()); }, "invalid_cursor");
      expect_error([&bucket] { static_cast<void>(bucket.next()); }, "invalid_cursor");
    }
    if (!failed) {
      check(mutated_failures > 0, "allocation sweep never failed after a tentative journal mutation");
      const auto retry = fixture.table.insert(rows.retry_value);
      check(retry.inserted && retry.handle.tuple.value == 7,
            "rollback after the first normal run did not restore the tuple counter");
      fixture.table.check_invariants();
      return failures;
    }
    const auto retry = fixture.table.insert(rows.retry_value);
    check(retry.inserted && retry.handle.tuple.value == 7,
          "allocation failure consumed a logical tuple ID");
    fixture.table.check_invariants();
  }
  throw std::runtime_error("journal allocation sweep did not reach its first normal run");
}

void active_journal_guards() {
  Fixture fixture;
  const auto before = capture(fixture.table);
  const auto revision = fixture.table.revision();
  const auto added = make_row(fixture.layout, 7, long_text('g', "-guard"), "7.00", 70);
  const auto projection = fixture.table.projection(fixture.indexes[0]);
  const auto key = projection.target().tuple(Row{Value{std::int64_t{1}}});
  auto live = fixture.table.live();
  auto bucket = fixture.table.bucket_cursor(fixture.indexes[0], key);
  {
    auto journal = fixture.table.journal();
    check(journal.active(), "new journal is not active");
    expect_error([&] { static_cast<void>(fixture.table.insert(added)); }, "storage_busy");
    expect_error([&] { static_cast<void>(fixture.table.erase(fixture.handles[0])); }, "storage_busy");
    expect_error([&] { static_cast<void>(fixture.table.erase(fixture.rows[0])); }, "storage_busy");
    expect_error([&] { static_cast<void>(fixture.table.add_index(projection)); }, "storage_busy");
    expect_error([&] { static_cast<void>(fixture.table.drop_index(fixture.indexes[0])); }, "storage_busy");
    expect_error([&] { static_cast<void>(fixture.table.erase_key(fixture.indexes[0], key)); }, "storage_busy");
    expect_error([&] { fixture.table.clear(); }, "storage_busy");
    expect_error([&] { static_cast<void>(fixture.table.journal()); }, "storage_busy");
    expect_error([&] { static_cast<void>(fixture.table.live()); }, "storage_busy");
    expect_error([&] { static_cast<void>(fixture.table.bucket_cursor(fixture.indexes[0], key)); }, "storage_busy");
    expect_error([&] { static_cast<void>(live.next()); }, "storage_busy");
    expect_error([&] { static_cast<void>(bucket.next()); }, "storage_busy");
    check(fixture.table.revision() == revision, "rejected direct mutation advanced revision");
    journal.rollback();
    check(!journal.active(), "explicit rollback left journal active");
    expect_error([&] { static_cast<void>(journal.insert(added)); }, "invalid_journal");
    expect_error([&] { static_cast<void>(journal.erase(fixture.handles[0])); }, "invalid_journal");
  }
  expect_image(fixture.table, before, fixture);
  check(fixture.table.revision() == revision, "empty rollback advanced revision");
  check(live.next().has_value(), "empty rollback invalidated a live cursor");
  check(bucket.next().has_value(), "empty rollback invalidated a bucket cursor");
}

void exercise_mixed_operations(ReferenceTable::Journal& journal, Fixture& fixture,
                               const TransactionRows& rows) {
  apply_mixed_transaction(journal, fixture, rows);
  check(journal.size() == 8, "journal change history omitted a real change or recorded a no-op");
  const auto first = journal.change(0);
  check(first.inserted && first.handle.tuple.value == 7 && first.tuple == rows.first,
        "journal change view differs for first insertion");
  const auto erased = journal.change(2);
  check(!erased.inserted && erased.handle == fixture.handles[4] && erased.tuple == fixture.rows[4],
        "journal change view differs for an erased tuple");
}

void explicit_rollback_is_allocation_free() {
  Fixture fixture;
  const auto before = capture(fixture.table);
  const auto old_revision = fixture.table.revision();
  auto live = fixture.table.live();
  auto bucket = fixture.table.bucket_cursor(fixture.indexes[0],
      fixture.table.projection(fixture.indexes[0]).target().tuple(Row{Value{std::int64_t{1}}}));
  const TransactionRows rows(fixture.layout);
  auto journal = fixture.table.journal();
  exercise_mixed_operations(journal, fixture, rows);
  check(fixture.table.revision() > old_revision, "tentative journal mutations did not advance revision");
  {
    ResetFailure reset;
    fail_after = 0;
    journal.rollback();
    journal.rollback();
  }
  check(!journal.active(), "explicit rollback left journal active");
  expect_image(fixture.table, before, fixture);
  check(fixture.table.revision() > old_revision, "rollback pretended to restore the old revision");
  expect_error([&live] { static_cast<void>(live.next()); }, "invalid_cursor");
  expect_error([&bucket] { static_cast<void>(bucket.next()); }, "invalid_cursor");
  expect_error([&] { static_cast<void>(journal.insert(rows.retry_value)); }, "invalid_journal");
  expect_error([&] { static_cast<void>(journal.erase(fixture.handles[0])); }, "invalid_journal");
}

void destructor_rollback_is_allocation_free() {
  Fixture fixture;
  const auto before = capture(fixture.table);
  const auto old_revision = fixture.table.revision();
  const TransactionRows rows(fixture.layout);
  {
    auto journal = fixture.table.journal();
    exercise_mixed_operations(journal, fixture, rows);
    // Let the journal destructor roll back while ordinary global-new attempts fail.
    fail_after = 0;
  }
  fail_after = -1;
  expect_image(fixture.table, before, fixture);
  check(fixture.table.revision() > old_revision, "destructor rollback restored the old revision");
}

ReferenceTable::Journal committed_journal_after_owner_destruction() {
  Fixture fixture;
  const auto inserted = make_row(fixture.layout, 9, long_text('z', "-committed"), "5.75", 99);
  ReferenceTable::Journal retained = [&]() {
    auto journal = fixture.table.journal();
    const auto new_row = journal.insert(inserted);
    check(new_row.inserted, "commit fixture insert was not inserted");
    check(journal.erase(fixture.handles[4]), "commit fixture erase failed");
    check(journal.size() == 2, "commit fixture recorded the wrong number of changes");
    {
      ResetFailure reset;
      fail_after = 0;
      journal.commit();
    }
    fail_after = -1;
    check(!journal.active(), "commit left journal active");
    check(journal.change(0).tuple == inserted, "committed insert view lost its value before clear");
    check(journal.change(1).tuple == fixture.rows[4], "committed erase view lost its value before clear");
    expect_error([&] { static_cast<void>(journal.insert(inserted)); }, "invalid_journal");
    expect_error([&] { static_cast<void>(journal.erase(fixture.handles[0])); }, "invalid_journal");
    fixture.table.clear();
    check(fixture.table.size() == 0, "clear after commit did not empty the owner");
    fixture.pins[4].reset();
    check(journal.change(0).tuple == inserted, "committed insert view did not survive table clear");
    check(journal.change(1).tuple == fixture.rows[4], "committed erase view did not survive table clear");
    return journal;
  }();
  check(!retained.active(), "moved committed journal became active");
  check(retained.change(0).tuple == inserted, "committed insert view did not survive table destruction");
  check(retained.change(1).tuple == fixture.rows[4], "committed erase view did not survive table destruction");
  return retained;
}

}  // namespace

int main() {
  try {
    const auto failures = allocation_failures();
    check(failures > 0, "journal allocation sweep did not exercise allocation failures");
    active_journal_guards();
    explicit_rollback_is_allocation_free();
    destructor_rollback_is_allocation_free();
    auto committed = committed_journal_after_owner_destruction();
    check(committed.size() == 2, "committed journal lost its retained change views");
    const auto inserted = committed.change(0);
    check(inserted.inserted && inserted.tuple.values() ==
              Row{Value{std::int64_t{9}}, Value{long_text('z', "-committed")}, Value{Decimal::parse("5.75")}, Value{std::int64_t{99}}},
          "committed insert payload was unreadable after table destruction");
    const auto erased = committed.change(1);
    check(!erased.inserted && erased.tuple.values() ==
              Row{Value{std::int64_t{2}}, Value{long_text('c', "-single")}, Value{Decimal::parse("3.75")}, Value{std::int64_t{14}}},
          "committed erase payload was unreadable after table destruction");
    std::cout << "journal allocation rollback points: " << failures << '\n';
  } catch (const std::exception& failure) {
    fail_after = -1;
    std::cerr << failure.what() << '\n';
    return 1;
  }
}
