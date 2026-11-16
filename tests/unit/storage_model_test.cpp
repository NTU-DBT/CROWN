#include "crown/api/error.hpp"
#include "crown/storage/reference.hpp"

#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <iterator>
#include <map>
#include <optional>
#include <random>
#include <set>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace {
using namespace crown;
using namespace crown::storage;
using Slots = std::vector<std::size_t>;

void check(bool condition, const std::string& message) {
  if (!condition) throw std::runtime_error(message);
}
template <class Action>
void expect_error(Action&& action, std::string_view code) {
  try { action(); }
  catch (const Error& failure) {
    check(failure.code() == code, "wrong storage error: " + failure.code());
    return;
  }
  throw std::runtime_error("expected storage error: " + std::string(code));
}

TupleLayout source_layout(LayoutId id = LayoutId{1}, LayoutContext context = {17, "storage-model"}) {
  return TupleLayout{id,
    {Field{ScalarType::int64}, Field{ScalarType::string}, Field{ScalarType::boolean},
     Field{ScalarType::date}, Field{ScalarType::decimal}},
    std::move(context)};
}

Row sample_row(std::int64_t integer, std::string text, bool flag, std::string_view day,
               std::string_view amount) {
  return Row{Value{integer}, Value{std::move(text)}, Value{flag},
             Value{Date::parse(day)}, Value{Decimal::parse(amount)}};
}

std::vector<FieldId> fields_for(const Slots& slots) {
  std::vector<FieldId> fields;
  fields.reserve(slots.size());
  for (const auto slot : slots) fields.push_back(FieldId{slot});
  return fields;
}

// The model's key extraction is deliberately a raw positional loop. It never
// calls Projection::apply or uses a key returned by the production index.
Row raw_key(const Row& row, const Slots& slots) {
  Row result;
  result.reserve(slots.size());
  for (const auto slot : slots) result.push_back(row.at(slot));
  return result;
}

std::vector<Slots> projection_shapes() {
  return {{}, {0}, {1, 0}, {4, 1, 4}, {2, 3, 1}, {3, 2, 0, 4}};
}

std::size_t pick(std::mt19937_64& random, std::size_t bound) {
  return static_cast<std::size_t>(random() % static_cast<std::uint64_t>(bound));
}

Row random_row(std::mt19937_64& random) {
  static const std::array<std::string, 7> texts{
    "", "a", "b", "1", "true", std::string("n\0ul", 4), "é"};
  static const std::array<Date, 4> dates{
    Date::parse("1969-12-31"), Date::parse("2000-02-29"),
    Date::parse("2024-02-29"), Date::parse("9999-12-31")};
  static const std::array<Decimal, 6> amounts{
    Decimal::parse("0"), Decimal::parse("-2.5"), Decimal::parse("1"),
    Decimal::parse("1.00"), Decimal::parse("0.0001"), Decimal::parse("100")};
  const auto integer = static_cast<std::int64_t>(random() % 7U) - 3;
  return Row{Value{integer}, Value{texts[pick(random, texts.size())]},
    Value{(random() & 1U) != 0U}, Value{dates[pick(random, dates.size())]},
    Value{amounts[pick(random, amounts.size())]}};
}

struct ModelIndex {
  Projection program;
  Slots slots;
};

using Rows = std::set<Row>;
using HandlesByRow = std::map<Row, TupleHandle>;
using ExpectedBuckets = std::map<Row, Rows>;
using Indexes = std::map<IndexId, ModelIndex>;

ExpectedBuckets expected_buckets(const Rows& rows, const Slots& slots) {
  ExpectedBuckets result;
  for (const auto& row : rows) result[raw_key(row, slots)].insert(row);
  return result;
}

void compare_table(ReferenceTable& table, const TupleLayout& source, const Rows& rows,
                   const HandlesByRow& handles, const Indexes& indexes,
                   const std::string& where) {
  table.check_invariants();
  check(table.size() == rows.size(), where + ": primary row count");

  const auto snapshot = table.snapshot();
  Rows snapshot_rows;
  for (const auto& tuple : snapshot) {
    check(tuple.layout().same_token(source), where + ": snapshot source token");
    check(snapshot_rows.insert(crown::storage::export_row(tuple.values())).second, where + ": duplicate snapshot row");
  }
  check(snapshot_rows == rows, where + ": snapshot rows differ from model");

  std::set<TupleHandle> expected_live;
  for (const auto& row : rows) {
    const auto found = handles.find(row);
    check(found != handles.end(), where + ": model row has no tuple handle");
    expected_live.insert(found->second);
    const auto tuple = source.tuple(row);
    const auto found_handle = table.find(tuple);
    check(found_handle.has_value() && *found_handle == found->second,
          where + ": primary equality lookup differs from model");
    const auto* stored = table.get(found->second);
    check(stored != nullptr && stored->values() == row,
          where + ": live handle resolves to the wrong owned row");
  }
  check(handles.size() == rows.size(), where + ": stale model handle retained");

  std::set<TupleHandle> actual_live;
  auto cursor = table.live();
  while (const auto handle = cursor.next()) {
    check(actual_live.insert(*handle).second, where + ": live cursor repeated a handle");
  }
  check(actual_live == expected_live, where + ": live cursor handles differ from model");

  std::set<IndexId> registered;
  for (const auto id : table.indices()) registered.insert(id);
  std::set<IndexId> expected_registered;
  for (const auto& [id, index] : indexes) {
    static_cast<void>(index);
    expected_registered.insert(id);
  }
  check(registered == expected_registered, where + ": registered index IDs differ from model");

  for (const auto& [id, index] : indexes) {
    const auto production_program = table.projection(id);
    check(production_program.same_token(index.program), where + ": registered projection token changed");
    check(std::ranges::equal(production_program.fields(),fields_for(index.slots)), where + ": compiled slots differ from model");

    const auto expected = expected_buckets(rows, index.slots);
    check(table.key_count(id) == expected.size(), where + ": separator key count differs from model");

    Rows actual_keys;
    for (const auto& key : table.keys(id)) {
      check(key.layout().same_token(index.program.target()), where + ": key has the wrong shared target token");
      check(actual_keys.insert(crown::storage::export_row(key.values())).second, where + ": separator key repeated");
    }
    Rows expected_keys;
    for (const auto& [key, bucket_rows] : expected) {
      static_cast<void>(bucket_rows);
      expected_keys.insert(key);
    }
    check(actual_keys == expected_keys, where + ": separator keys differ from raw-slot model");

    for (const auto& [key_row, bucket_rows] : expected) {
      const auto key = index.program.target().tuple(key_row);
      std::set<TupleHandle> expected_bucket;
      for (const auto& row : bucket_rows) expected_bucket.insert(handles.at(row));
      std::set<TupleHandle> actual_bucket;
      for (const auto handle : table.bucket(id, key)) {
        check(actual_bucket.insert(handle).second, where + ": bucket repeated a tuple handle");
        const auto* stored = table.get(handle);
        check(stored != nullptr && bucket_rows.contains(crown::storage::export_row(stored->values())),
              where + ": bucket returned a row outside its raw-slot key");
      }
      check(actual_bucket == expected_bucket,
            where + ": separator bucket differs from independent raw-slot model");
      std::set<TupleHandle> traversed_bucket;
      auto bucket_cursor = table.bucket_cursor(id, key);
      while (const auto handle = bucket_cursor.next()) {
        check(traversed_bucket.insert(*handle).second, where + ": bucket cursor repeated a handle");
      }
      check(traversed_bucket == expected_bucket,
            where + ": bucket cursor differs from independent raw-slot model");
    }
  }
}

void add_model_index(ReferenceTable& table, const TupleLayout& source, const Slots& slots,
                     LayoutId target_id, Indexes& indexes,
                     std::set<std::uint64_t>& seen_ids, std::uint64_t& largest_id) {
  const auto fields = fields_for(slots);
  const auto target = projected_layout(target_id, source, fields);
  Projection program(source, target, fields);
  const auto id = table.add_index(program);
  const auto [entry, inserted] = indexes.emplace(id, ModelIndex{program, slots});
  check(inserted, "fresh projection registration unexpectedly reused an active index ID");
  static_cast<void>(entry);
  check(seen_ids.insert(id.value).second, "index ID was reused after drop or clear");
  check(id.value > largest_id, "index IDs were not monotonic within the table");
  largest_id = id.value;
  check(table.add_index(program) == id, "registering the same immutable projection was not idempotent");
}

void no_op_and_cursor_contract() {
  const auto layout = source_layout();
  ReferenceTable table(RelationId{41}, layout);
  const auto first = sample_row(1, "one", true, "2024-02-29", "1.0");
  const auto absent = sample_row(99, "missing", false, "1969-12-31", "-2.5");
  const auto inserted = table.insert(layout.tuple(first));
  check(inserted.inserted, "initial row was not inserted");

  auto cursor = table.live();
  const auto revision = table.revision();
  const auto duplicate = table.insert(layout.tuple(first));
  check(!duplicate.inserted && duplicate.handle == inserted.handle,
        "duplicate insertion did not return the existing row");
  check(table.revision() == revision, "duplicate insertion advanced the table revision");
  check(!table.erase(layout.tuple(absent)), "deletion of an absent row reported a change");
  check(table.revision() == revision, "absent deletion advanced the table revision");
  const auto still_live = cursor.next();
  check(still_live.has_value() && *still_live == inserted.handle,
        "no-op operations invalidated a live cursor");

  const auto before_real_change = table.revision();
  const auto second = sample_row(2, "two", false, "2000-02-29", "2.5");
  check(table.insert(layout.tuple(second)).inserted, "real mutation was not inserted");
  check(table.revision() != before_real_change, "real insertion did not advance the table revision");
  bool invalidated = false;
  try { static_cast<void>(cursor.next()); }
  catch (const Error&) { invalidated = true; }
  check(invalidated, "real mutation did not invalidate a live cursor");

  const Slots only_integer{0};
  const auto fields = fields_for(only_integer);
  const auto target = projected_layout(LayoutId{90}, layout, fields);
  const auto index = table.add_index(Projection(layout, target, fields));
  auto key = target.tuple(Row{Value{std::int64_t{1}}});
  check(table.key_count(index) == 2, "single-column index did not contain both keys");
  const auto deleted = table.erase_key(index, key);
  check(deleted == 1, "erase_key did not remove exactly the matching row");
  check(table.key_count(index) == 1 && table.bucket(index, key).empty(),
        "deleted last row left its separator key/bucket behind");
}

void shared_target_layout_interoperability() {
  const LayoutContext context{23, "shared-key-model"};
  const auto left_layout = source_layout(LayoutId{101}, context);
  TupleLayout right_layout(LayoutId{102},
    {Field{ScalarType::string}, Field{ScalarType::int64}, Field{ScalarType::boolean},
     Field{ScalarType::date}, Field{ScalarType::decimal}}, context);
  const auto shared_target = TupleLayout(LayoutId{103},
    {Field{ScalarType::string}, Field{ScalarType::int64}}, context);
  const std::vector<FieldId> left_fields{FieldId{1}, FieldId{0}};
  const std::vector<FieldId> right_fields{FieldId{0}, FieldId{1}};
  Projection left_projection(left_layout, shared_target, left_fields);
  Projection right_projection(right_layout, shared_target, right_fields);
  check(!left_projection.source().same_token(right_projection.source()),
        "interoperability fixture unexpectedly shares a source layout token");
  check(left_projection.target().same_token(right_projection.target()),
        "independent source layouts did not share the target key token");

  ReferenceTable left(RelationId{51}, left_layout);
  ReferenceTable right(RelationId{52}, right_layout);
  const auto left_row = sample_row(5, "alpha", true, "2024-02-29", "1.00");
  const auto right_row = Row{Value{std::string("alpha")}, Value{std::int64_t{5}},
    Value{false}, Value{Date::parse("2000-02-29")}, Value{Decimal::parse("1")}};
  const auto right_other = Row{Value{std::string("alpha")}, Value{std::int64_t{6}},
    Value{false}, Value{Date::parse("2000-02-29")}, Value{Decimal::parse("1")}};
  const auto left_id = left.add_index(left_projection);
  const auto right_id = right.add_index(right_projection);
  check(left.insert(left_layout.tuple(left_row)).inserted, "left source row insertion failed");
  check(right.insert(right_layout.tuple(right_row)).inserted, "right matching row insertion failed");
  check(right.insert(right_layout.tuple(right_other)).inserted, "right nonmatching row insertion failed");

  // Production projection is used only to form the actual lookup key here.
  // The expected rows below are selected independently by raw source slots.
  const auto key = left_projection.apply(left_layout.tuple(left_row));
  check(left.bucket(left_id, key).size() == 1, "left key index did not contain its source row");
  std::set<Row> actual_rows;
  for (const auto handle : right.bucket(right_id, key)) actual_rows.insert(crown::storage::export_row(right.get(handle)->values()));
  std::set<Row> expected_rows;
  for (const auto& row : {right_row, right_other}) {
    const Row raw{row[0], row[1]};
    if (raw == Row{Value{std::string("alpha")}, Value{std::int64_t{5}}}) expected_rows.insert(row);
  }
  check(actual_rows == expected_rows && actual_rows.size() == 1,
        "shared key token did not interoperate across distinct source layouts");

  const auto foreign = right.find(right_layout.tuple(right_row));
  check(foreign.has_value(), "right row handle missing for ownership check");
  const Tuple* foreign_value = nullptr;
  bool get_rejected = false;
  try { foreign_value = left.get(*foreign); }
  catch (const Error&) { get_rejected = true; }
  check(get_rejected || foreign_value == nullptr, "foreign owner handle resolved in another backend");
  bool erase_rejected = false;
  bool erased_foreign = false;
  try { erased_foreign = left.erase(*foreign); }
  catch (const Error&) { erase_rejected = true; }
  check(erase_rejected || !erased_foreign, "foreign owner handle erased a local row");
  left.check_invariants();
  right.check_invariants();
}

void ids_survive_clear_and_reinsertion() {
  const auto layout = source_layout(LayoutId{201}, LayoutContext{29, "id-lifetime-model"});
  ReferenceTable table(RelationId{61}, layout);
  const auto row = sample_row(7, "seven", true, "2024-02-29", "7.0");
  const auto first = table.insert(layout.tuple(row));
  check(first.inserted && first.handle.tuple.value != 0, "first tuple ID was not allocated");

  const Slots slots{1, 0};
  const auto fields = fields_for(slots);
  const auto first_target = projected_layout(LayoutId{202}, layout, fields);
  const auto first_index = table.add_index(Projection(layout, first_target, fields));
  check(first_index.value != 0, "first index ID was not allocated");
  table.clear();
  check(table.size() == 0 && table.key_count(first_index) == 0,
        "clear retained live rows or separator keys");
  check(table.drop_index(first_index), "first index could not be dropped");

  const auto second_target = projected_layout(LayoutId{203}, layout, fields);
  const auto second_index = table.add_index(Projection(layout, second_target, fields));
  check(second_index.value > first_index.value, "index ID was reused after clear/drop");
  const auto second = table.insert(layout.tuple(row));
  check(second.inserted && second.handle.tuple.value > first.handle.tuple.value,
        "tuple ID was reused after clear/reinsertion");
  table.check_invariants();
}

void cursor_ownership_and_moves() {
  const auto layout = source_layout(LayoutId{301}, {31, "cursor-lifetime-model"});
  const auto key_layout = projected_layout(LayoutId{302}, layout, std::vector<FieldId>{{0}});
  const Projection program{layout, key_layout, {{0}}};
  const auto row = sample_row(7, "owned-string", true, "2024-02-29", "1.00");
  const auto key = key_layout.tuple(Row{Value{std::int64_t{7}}});
  const auto absent_key = key_layout.tuple(Row{Value{std::int64_t{999}}});
  ReferenceTable table{RelationId{71}, layout};
  const auto index = table.add_index(program);
  auto empty = table.live();
  auto missing = table.bucket_cursor(index, absent_key);
  const auto empty_revision = table.revision();
  table.clear();
  check(!table.erase(layout.tuple(row)) && table.erase_key(index, absent_key) == 0,
        "absent row/key operation changed an empty table");
  check(!table.drop_index(IndexId{999}) && table.add_index(program) == index,
        "index no-op changed an existing definition");
  check(table.revision() == empty_revision && !empty.next() && !missing.next(),
        "empty/no-op operations invalidated a cursor");

  const auto first = table.insert(layout.tuple(row));
  expect_error([&] { static_cast<void>(empty.next()); }, "invalid_cursor");
  expect_error([&] { static_cast<void>(missing.next()); }, "invalid_cursor");
  check(table.insert(layout.tuple(sample_row(7, "second", false, "2000-02-29", "2.5"))).inserted,
        "second row was not inserted for bucket traversal");
  check(table.insert(layout.tuple(sample_row(9, "third", true, "1969-12-31", "-2.5"))).inserted,
        "third row was not inserted for live traversal");
  auto live_before_move = table.live();
  auto bucket_before_move = table.bucket_cursor(index, key);
  ReferenceTable moved{std::move(table)};
  expect_error([&] { static_cast<void>(table.size()); }, "invalid_storage");
  check(moved.get(first.handle)->values() == row && live_before_move.next().has_value() &&
        bucket_before_move.next().has_value(), "table move construction invalidated its owner/handles/cursors");

  ReferenceTable destination{RelationId{72}, layout};
  const auto displaced_handle = destination.insert(layout.tuple(row)).handle;
  auto displaced_cursor = destination.live();
  auto retained_cursor = moved.live();
  destination = std::move(moved);
  expect_error([&] { static_cast<void>(moved.size()); }, "invalid_storage");
  expect_error([&] { static_cast<void>(displaced_cursor.next()); }, "invalid_cursor");
  expect_error([&] { static_cast<void>(destination.get(displaced_handle)); }, "foreign_handle");
  check(destination.get(first.handle)->values() == row && retained_cursor.next().has_value(),
        "table move assignment invalidated the transferred state");
  auto old_cursor = destination.live();
  auto moved_cursor = std::move(old_cursor);
  expect_error([&] { static_cast<void>(old_cursor.next()); }, "invalid_cursor");
  check(moved_cursor.next().has_value(), "cursor move lost its live owner");

  auto before_index_add = destination.live();
  const auto extra_layout = projected_layout(LayoutId{303}, layout, std::vector<FieldId>{{0}});
  const auto extra = destination.add_index({layout, extra_layout, {{0}}});
  expect_error([&] { static_cast<void>(before_index_add.next()); }, "invalid_cursor");
  auto before_index_drop = destination.live();
  auto bucket_before_drop = destination.bucket_cursor(index, key);
  check(destination.drop_index(extra), "real index drop failed");
  expect_error([&] { static_cast<void>(before_index_drop.next()); }, "invalid_cursor");
  expect_error([&] { static_cast<void>(bucket_before_drop.next()); }, "invalid_cursor");

  const auto captured = destination.snapshot();
  auto before_clear = destination.live();
  auto bucket_before_clear = destination.bucket_cursor(index, key);
  destination.clear();
  expect_error([&] { static_cast<void>(before_clear.next()); }, "invalid_cursor");
  expect_error([&] { static_cast<void>(bucket_before_clear.next()); }, "invalid_cursor");
  check(captured.size() == 3 && std::any_of(captured.begin(), captured.end(), [&](const Tuple& tuple) {
    return tuple.values() == row;
  }), "owning snapshot lost its strings/values after table clear");
  check(destination.get(first.handle) == nullptr && !destination.erase(first.handle),
        "stale owned handle remained live after clear");
  destination.check_invariants();

  std::optional<ReferenceTable::Cursor> expired_live, expired_bucket, expired_empty;
  {
    ReferenceTable temporary{RelationId{73}, layout};
    const auto temporary_index = temporary.add_index(program);
    static_cast<void>(temporary.insert(layout.tuple(row)));
    expired_live.emplace(temporary.live());
    expired_bucket.emplace(temporary.bucket_cursor(temporary_index, key));
    expired_empty.emplace(temporary.bucket_cursor(temporary_index, absent_key));
  }
  expect_error([&] { static_cast<void>(expired_live->next()); }, "invalid_cursor");
  expect_error([&] { static_cast<void>(expired_bucket->next()); }, "invalid_cursor");
  expect_error([&] { static_cast<void>(expired_empty->next()); }, "invalid_cursor");
}

void randomized_model() {
  const auto shapes = projection_shapes();
  const auto source = source_layout();
  for (std::uint64_t seed = 1; seed <= 12; ++seed) {
    std::mt19937_64 random(seed * 0x9e3779b97f4a7c15ULL);
    ReferenceTable table(RelationId{static_cast<std::size_t>(100 + seed)}, source);
    Rows rows;
    HandlesByRow handles;
    Indexes indexes;
    std::set<std::uint64_t> seen_tuple_ids;
    std::set<std::uint64_t> seen_index_ids;
    std::uint64_t largest_tuple_id = 0;
    std::uint64_t largest_index_id = 0;
    std::size_t next_layout_id = static_cast<std::size_t>(1000 + seed * 1000);

    for (std::size_t shape = 0; shape < shapes.size(); ++shape) {
      add_model_index(table, source, shapes[shape], LayoutId{next_layout_id++},
                     indexes, seen_index_ids, largest_index_id);
    }

    const auto verify = [&](std::size_t step) {
      compare_table(table, source, rows, handles, indexes,
                    "seed " + std::to_string(seed) + " step " + std::to_string(step));
    };
    verify(0);

    for (std::size_t step = 0; step < 100; ++step) {
      const auto operation = pick(random, 100);
      if (operation < 30 && rows.size() < 60) {
        const auto row = random_row(random);
        const auto before = table.revision();
        const auto result = table.insert(source.tuple(row));
        const auto existing = handles.find(row);
        if (existing == handles.end()) {
          check(result.inserted, "new row insertion was reported as duplicate");
          check(rows.insert(row).second, "model rejected a supposedly new row");
          check(handles.emplace(row, result.handle).second, "model could not retain new handle");
          check(seen_tuple_ids.insert(result.handle.tuple.value).second,
                "tuple ID was reused after deletion or clear");
          check(result.handle.tuple.value > largest_tuple_id,
                "tuple IDs were not monotonic within the table");
          largest_tuple_id = result.handle.tuple.value;
          check(table.revision() != before, "successful insertion did not advance revision");
        } else {
          check(!result.inserted && result.handle == existing->second,
                "duplicate insert did not preserve the live tuple ID");
          check(table.revision() == before, "duplicate insert advanced revision");
        }
      } else if (operation < 50) {
        const auto row = random_row(random);
        const auto before = table.revision();
        const auto erased = table.erase(source.tuple(row));
        const auto existing = handles.find(row);
        check(erased == (existing != handles.end()), "tuple deletion disagrees with primary model");
        if (existing != handles.end()) {
          rows.erase(row);
          handles.erase(existing);
          check(table.revision() != before, "successful deletion did not advance revision");
        } else {
          check(table.revision() == before, "absent deletion advanced revision");
        }
      } else if (operation < 59 && !rows.empty()) {
        const std::vector<Row> current(rows.begin(), rows.end());
        const auto row = current[pick(random, current.size())];
        const auto handle = handles.at(row);
        const auto before = table.revision();
        check(table.erase(handle), "live handle deletion failed");
        rows.erase(row);
        handles.erase(row);
        check(table.revision() != before, "handle deletion did not advance revision");
      } else if (operation < 70 && !indexes.empty()) {
        auto index_it = indexes.begin();
        std::advance(index_it, static_cast<std::ptrdiff_t>(pick(random, indexes.size())));
        const auto id = index_it->first;
        const auto& index = index_it->second;
        const auto candidate = random_row(random);
        const auto key_row = raw_key(candidate, index.slots);
        const auto key = index.program.target().tuple(key_row);
        Rows matching;
        for (const auto& row : rows) {
          if (raw_key(row, index.slots) == key_row) matching.insert(row);
        }
        const auto before = table.revision();
        const auto erased = table.erase_key(id, key);
        check(erased == matching.size(), "erase_key count differs from raw-slot model");
        for (const auto& row : matching) {
          rows.erase(row);
          handles.erase(row);
        }
        if (matching.empty()) check(table.revision() == before, "absent key deletion advanced revision");
        else check(table.revision() != before, "key deletion did not advance revision");
      } else if (operation < 77) {
        const auto before = table.revision();
        const bool had_rows = !rows.empty();
        table.clear();
        rows.clear();
        handles.clear();
        if (had_rows) check(table.revision() != before, "nonempty clear did not advance revision");
        else check(table.revision() == before, "empty clear advanced revision");
      } else if (operation < 89) {
        add_model_index(table, source, shapes[pick(random, shapes.size())],
          LayoutId{next_layout_id++}, indexes, seen_index_ids, largest_index_id);
      } else if (operation < 97 && !indexes.empty()) {
        auto index_it = indexes.begin();
        std::advance(index_it, static_cast<std::ptrdiff_t>(pick(random, indexes.size())));
        const auto id = index_it->first;
        check(table.drop_index(id), "active index drop failed");
        indexes.erase(index_it);
      } else {
        // Check that duplicate/absent row operations leave an already-created
        // cursor usable; no-op revision assertions are made above as well.
        auto cursor = table.live();
        const auto before = table.revision();
        const auto absent = sample_row(99, "never-present", false, "1969-12-31", "-999");
        check(!table.erase(source.tuple(absent)), "no-op probe absent deletion changed state");
        if (rows.empty()) {
          check(table.revision() == before, "absent deletion advanced revision on an empty table");
          check(!cursor.next(), "empty live cursor returned a row after a no-op");
        } else {
          const auto row = *rows.begin();
          const auto duplicate = table.insert(source.tuple(row));
          check(!duplicate.inserted && duplicate.handle == handles.at(row),
                "no-op probe duplicate changed tuple identity");
          check(table.revision() == before, "duplicate/absent no-op advanced revision");
          check(cursor.next().has_value(), "no-op operations invalidated a live cursor");
        }
      }

      // Keep the randomized row count bounded even for a future-expanded value
      // domain; the present domain and 100-step trace stay well below this.
      check(rows.size() <= 60, "random model exceeded its live-row bound");
      verify(step + 1);
    }
  }
}

}  // namespace

int main() {
  try {
    no_op_and_cursor_contract();
    shared_target_layout_interoperability();
    ids_survive_clear_and_reinsertion();
    cursor_ownership_and_moves();
    randomized_model();
    std::cout << "reference storage model, projections, buckets and cursor lifecycle passed\n";
    return 0;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
