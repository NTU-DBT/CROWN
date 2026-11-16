#include "crown/storage/indexed.hpp"
#include "index_allocation.hpp"
#ifdef CROWN_STORAGE_TESTING
#include "indexed_testing.hpp"
#endif
#if defined(CROWN_STORAGE_COLLISION_PROFILE) && !defined(CROWN_STORAGE_TESTING)
#error "Collision fault fixture requires the coherent testing storage library"
#endif

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

using namespace crown;
using namespace crown::storage;

namespace {
void verify(bool value, std::string_view message) {
  if (!value) throw std::runtime_error(std::string(message));
}
IndexWorkAllowance ample() {
  return IndexWorkAllowance(IndexWork{100'000'000, 100'000'000, 100'000'000, 100'000'000, 100'000'000});
}
IndexedLimits limits() { return {32, 8, 256, 512, 1024, 4096, 64, 8}; }

struct Definition {
  TupleLayout layout{LayoutId{1}, {{ScalarType::int64}, {ScalarType::string},
      {ScalarType::boolean}, {ScalarType::date}, {ScalarType::decimal}}};
  std::vector<Projection> programs;
  std::vector<Tuple> initial;
  Tuple new_keys;
  Tuple same_keys;
  Tuple nullary_probe;

  Definition()
      : new_keys(layout.tuple(Row{std::int64_t{999}, std::string(600, 'n'), true,
          Date::parse("9999-12-31"), Decimal::parse("-12345678901234567890123456789012345678")})),
        same_keys(layout.tuple(Row{std::int64_t{0}, std::string(512, 'a'), true,
          Date::parse("1970-01-01"), Decimal::parse("12345678901234567890123456789012345678")})),
        nullary_probe(TupleLayout(LayoutId{2}, {}).tuple({})) {
    const std::vector<std::vector<FieldId>> fields{{}, {FieldId{1}}, {FieldId{0}, FieldId{4}, FieldId{1}},
        {FieldId{3}}, {FieldId{2}}, {FieldId{0}}, {FieldId{2}, FieldId{3}, FieldId{2}, FieldId{0}}};
    for (std::size_t i = 0; i < fields.size(); ++i) {
      auto target = i == 0 ? nullary_probe.layout() : projected_layout(LayoutId{10 + i}, layout, fields[i]);
      programs.emplace_back(layout, std::move(target), fields[i]);
    }
    for (std::int64_t i = 0; i < 6; ++i) {
      auto text = std::string(512, static_cast<char>('a' + i));
      initial.push_back(layout.tuple(Row{i, std::move(text), (i % 2) != 0,
          Date::parse("1970-01-01"), Decimal::parse("12345678901234567890123456789012345678")}));
    }
  }
};

struct Fixture {
  IndexedTable table;
  std::vector<IndexId> indices;
  std::vector<TupleHandle> handles;
  TupleArena::Pin pin;
  const Tuple* pinned_address;

  explicit Fixture(const Definition& definition)
      : table(RelationId{1}, definition.layout, limits()),
        pin(build(definition)), pinned_address(&pin.get()) {}

  TupleArena::Pin build(const Definition& definition) {
#if defined(CROWN_STORAGE_COLLISION_PROFILE) && CROWN_STORAGE_COLLISION_PROFILE == 1
    detail::IndexedTesting::collisions(table, detail::CollisionMode::same_bucket);
#elif defined(CROWN_STORAGE_COLLISION_PROFILE) && CROWN_STORAGE_COLLISION_PROFILE == 2
    detail::IndexedTesting::collisions(table, detail::CollisionMode::same_full_hash);
#elif defined(CROWN_STORAGE_COLLISION_PROFILE)
#error "Unknown collision fault fixture profile"
#endif
    auto work = ample();
    for (std::size_t i = 0; i < 6; ++i) indices.push_back(table.add_index(definition.programs[i], work));
    for (const auto& row : definition.initial) handles.push_back(table.insert(row, work).handle);
    return table.pin(handles.front(), work);
  }
};

struct IndexImage {
  IndexId id;
  std::size_t program;
  std::vector<Tuple> keys;
  std::vector<std::vector<TupleId>> members;
  bool operator==(const IndexImage&) const = default;
};
struct Image {
  IndexedStatistics statistics;
  std::uint64_t revision;
  std::vector<Tuple> rows;
  std::vector<IndexImage> indices;
  bool pin_live;
  bool operator==(const Image&) const = default;
};

Image image(Fixture& fixture, const Definition& definition) {
  auto work = ample();Image result{fixture.table.statistics(), fixture.table.revision(),
      fixture.table.snapshot(work), {}, fixture.pin.is_live()};
  for (const auto id : fixture.table.indices(work)) {
    const auto program = fixture.table.projection(id, work);std::size_t label = definition.programs.size();
    for (std::size_t i = 0; i < definition.programs.size(); ++i)
      if (program.same_token(definition.programs[i])) { label = i;break; }
    verify(label < definition.programs.size(), "fault image has a foreign projection program");
    IndexImage index{id, label, fixture.table.keys(id, work), {}};
    for (const auto& key : index.keys) {
      std::vector<TupleId> members;
      for (const auto handle : fixture.table.bucket(id, key, work)) {
        verify(handle.owner == fixture.table.owner() && handle.relation == RelationId{1}, "fault image has a foreign bucket handle");
        members.push_back(handle.tuple);
      }
      index.members.push_back(std::move(members));
    }
    result.indices.push_back(std::move(index));
  }
  fixture.table.check_invariants();
  verify(&fixture.pin.get() == fixture.pinned_address && fixture.pin.get() == definition.initial.front(),
         "fault image lost the original pinned tuple allocation");
  return result;
}

enum class Operation { insert_new_keys, insert_existing_keys, add_index, erase_handle,
                       erase_key, clear, drop_index, duplicate, absent_erase,
                       snapshot, keys, bucket };
std::uint64_t apply(Fixture& fixture, const Definition& definition, Operation operation, IndexWorkAllowance& work) {
  switch (operation) {
    case Operation::insert_new_keys: {
      const auto result = fixture.table.insert(definition.new_keys, work);
      verify(result.inserted, "new-key fault fixture was a duplicate");return result.handle.tuple.value;
    }
    case Operation::insert_existing_keys: {
      const auto result = fixture.table.insert(definition.same_keys, work);
      verify(result.inserted, "shared-key fault fixture was a duplicate");return result.handle.tuple.value;
    }
    case Operation::add_index: return fixture.table.add_index(definition.programs[6], work).value;
    case Operation::erase_handle: return fixture.table.erase(fixture.handles.front(), work) ? 1 : 0;
    case Operation::erase_key: return static_cast<std::uint64_t>(fixture.table.erase_key(fixture.indices.front(), definition.nullary_probe, work));
    case Operation::clear: fixture.table.clear(work);return 0;
    case Operation::drop_index: return fixture.table.drop_index(fixture.indices.front(), work) ? 1 : 0;
    case Operation::duplicate: {
      const auto result = fixture.table.insert(definition.initial.front(), work);
      verify(!result.inserted, "duplicate fault fixture inserted a row");return result.handle.tuple.value;
    }
    case Operation::absent_erase: return fixture.table.erase(definition.new_keys, work) ? 1 : 0;
    case Operation::snapshot: return static_cast<std::uint64_t>(fixture.table.snapshot(work).size());
    case Operation::keys: return static_cast<std::uint64_t>(fixture.table.keys(fixture.indices[1], work).size());
    case Operation::bucket: return static_cast<std::uint64_t>(fixture.table.bucket(fixture.indices.front(), definition.nullary_probe, work).size());
  }
  throw std::runtime_error("unknown fault fixture operation");
}

void sweep(const Definition& definition, Operation operation, const char* label, bool must_allocate) {
  Fixture baseline(definition);auto baseline_work = ample();std::uint64_t expected_result = 0;std::size_t count = 0;
  {
    s04_alloc::Scope measure;expected_result = apply(baseline, definition, operation, baseline_work);count = s04_alloc::calls;
  }
  verify(!s04_alloc::triggered && (must_allocate ? count > 0 : count == 0), "fault allocation baseline contradicted its operation class");
  const auto completed = image(baseline, definition);Fixture subject(definition);const auto initial = image(subject, definition);
  for (std::size_t position = 0; position < count; ++position) {
    verify(position <= static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max()), "fault position exceeds injector domain");
    auto work = ample();auto cursor_work = ample();auto live = subject.table.live(cursor_work);
    auto bucket = subject.table.bucket_cursor(subject.indices.front(), definition.nullary_probe, cursor_work);
    auto keys = subject.table.index_keys(subject.indices.front(), cursor_work);bool failed = false;
    try {
      s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(position));
      static_cast<void>(apply(subject, definition, operation, work));
    } catch (const std::bad_alloc&) { failed = true; }
    verify(failed && s04_alloc::triggered, "operation missed a reached persistent allocation position");
    verify(image(subject, definition) == initial, "persistent allocation failure changed complete table state");
    verify(live.next(cursor_work)->handle == subject.handles.front() &&
        bucket.next(cursor_work)->handle == subject.handles.front() && keys.next(cursor_work)->degree == 6,
        "persistent allocation failure invalidated an old row/bucket/key cursor");
  }
  auto retry_work = ample();std::uint64_t actual_result = 0;
  if (count == 0) {
    s04_alloc::Scope deny(0);actual_result = apply(subject, definition, operation, retry_work);
  } else {
    actual_result = apply(subject, definition, operation, retry_work);
  }
  verify((count != 0 || (!s04_alloc::triggered && s04_alloc::calls == 0)) && actual_result == expected_result &&
      image(subject, definition) == completed, "post-failure retry or allocation-free publication differed from baseline");
  std::cout << label << " allocation_positions=" << count << " retry=complete\n";
}
}  // namespace

int main() {
  Definition definition;
  sweep(definition, Operation::insert_new_keys, "insert_new_keys", true);
  sweep(definition, Operation::insert_existing_keys, "insert_existing_keys", true);
  sweep(definition, Operation::add_index, "add_index_growth", true);
  sweep(definition, Operation::erase_handle, "erase_pinned_handle", false);
  sweep(definition, Operation::erase_key, "erase_complete_bucket", true);
  sweep(definition, Operation::clear, "clear", false);
  sweep(definition, Operation::drop_index, "drop_index", false);
  sweep(definition, Operation::duplicate, "duplicate_lookup", true);
  sweep(definition, Operation::absent_erase, "absent_lookup", true);
  sweep(definition, Operation::snapshot, "owning_snapshot", true);
  sweep(definition, Operation::keys, "owning_keys", true);
  sweep(definition, Operation::bucket, "owning_bucket", true);
}
