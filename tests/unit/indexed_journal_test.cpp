#include "crown/storage/indexed.hpp"
#include "crown/storage/reference.hpp"
#include "index_allocation.hpp"
#ifdef CROWN_STORAGE_TESTING
#include "indexed_testing.hpp"
#endif

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <map>
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
template<class Function> void error(std::string_view code, Function&& operation) {
  try { operation(); }
  catch (const Error& failure) { verify(failure.code() == code, "unexpected journal error");return; }
  throw std::runtime_error("expected journal error");
}
IndexWork budget() { return {1'000'000'000, 1'000'000'000, 1'000'000'000, 1'000'000'000, 1'000'000'000}; }
IndexWorkAllowance ample() { return IndexWorkAllowance(budget()); }
std::shared_ptr<IndexWorkAllowance> grant() { return std::make_shared<IndexWorkAllowance>(budget()); }
IndexedLimits limits() { return {64, 8, 1024, 2048, 4096, 16384, 256, 256, 128}; }
struct Definition {
  TupleLayout layout{LayoutId{1}, {{ScalarType::int64}, {ScalarType::int64},
      {ScalarType::string}, {ScalarType::decimal}}};
  std::vector<Projection> programs;
  Definition() {
    const std::vector<std::vector<FieldId>> slots{{}, {FieldId{1}}, {FieldId{0}, FieldId{1}, FieldId{0}}};
    for (std::size_t i = 0; i < slots.size(); ++i)
      programs.emplace_back(layout, projected_layout(LayoutId{2 + i}, layout, slots[i]), slots[i]);
  }
  Tuple row(std::int64_t id, std::int64_t key) const {
    return layout.tuple({id, key, std::string(512, static_cast<char>('a' + id % 20)),
        Decimal::parse("-0.00000000000000000000000000000000000001")});
  }
  Tuple key(std::int64_t value) const { return programs[1].target().tuple({value}); }
};
void profile(IndexedTable& table) {
#if defined(CROWN_STORAGE_COLLISION_PROFILE) && CROWN_STORAGE_COLLISION_PROFILE == 1
  detail::IndexedTesting::collisions(table, detail::CollisionMode::same_bucket);
#elif defined(CROWN_STORAGE_COLLISION_PROFILE) && CROWN_STORAGE_COLLISION_PROFILE == 2
  detail::IndexedTesting::collisions(table, detail::CollisionMode::same_full_hash);
#else
  static_cast<void>(table);
#endif
}
struct Fixture {
  IndexedTable table;
  std::vector<IndexId> indices;
  std::vector<TupleHandle> handles;
  TupleArena::Pin pin;
  Fixture(const Definition& d, IndexedLimits cap = limits())
      : table(RelationId{1}, d.layout, cap), pin(build(d)) {}
  TupleArena::Pin build(const Definition& d) {
    profile(table);auto work = ample();
    for (const auto& p : d.programs) indices.push_back(table.add_index(p, work));
    const std::vector<std::int64_t> keys{9, 10, 9, 11};
    for (std::size_t i = 0; i < keys.size(); ++i)
      handles.push_back(table.insert(d.row(static_cast<std::int64_t>(i + 1), keys[i]), work).handle);
    return table.pin(handles.front(), work);
  }
};
struct KeyImage {
  Tuple key;
  std::vector<TupleId> members;
  bool operator==(const KeyImage&) const = default;
};
struct Image {
  std::vector<Tuple> rows;
  std::vector<std::vector<KeyImage>> indices;
  bool operator==(const Image&) const = default;
};
// Observer snapshots are separate from the operation being tested. Their
// allocations/work never run inside a fault/denial scope or replenish a journal.
Image image(Fixture& f) {
  auto work = ample();Image result{f.table.snapshot(work), {}};
  for (auto id : f.indices) {
    std::vector<KeyImage> keys;
    for (const auto& key : f.table.keys(id, work)) {
      KeyImage item{key, {}};
      for (auto h : f.table.bucket(id, key, work)) item.members.push_back(h.tuple);
      keys.push_back(std::move(item));
    }
    result.indices.push_back(std::move(keys));
  }
  f.table.check_invariants();return result;
}
void rollback_order_growth(const Definition& d) {
  Fixture f(d);const auto before = image(f);const auto actions = f.table.statistics().committed;
  const auto* address = &f.pin.get();auto external_work = ample();auto outside = f.table.live(external_work);
  auto work = grant();auto journal = f.table.journal(work);
  error("storage_busy", [&] { static_cast<void>(f.table.insert(d.row(99, 99), *work)); });
  error("storage_busy", [&] { static_cast<void>(f.table.snapshot_copy(*work)); });
  verify(journal.erase(f.handles[0]) && journal.erase(f.handles[2]), "journal erased wrong initial rows");
  verify(!f.pin.is_live() && &f.pin.get() == address, "tentative erase changed pinned payload");
  for (std::int64_t i = 5; i <= 9; ++i)
    verify(journal.insert(d.row(i, i == 5 ? 9 : i + 6)).inserted, "journal growth insertion failed");
  const auto unchanged = journal.size();
  verify(!journal.insert(d.row(2, 10)).inserted &&
      !journal.erase({f.table.owner(), RelationId{1}, TupleId{999}}) && journal.size() == unchanged,
      "journal no-op appended history");
  std::vector<std::int64_t> order;
  for (const auto& key : f.table.keys(f.indices[1], *work)) order.push_back(std::get<std::int64_t>(key.values()[0]));
  verify(order == std::vector<std::int64_t>({10, 11, 9, 12, 13, 14, 15}), "empty-key reactivation order differs");
  const auto stats = f.table.statistics();
  verify(stats.retained_rows == 2 && stats.retained_memberships == 6 && stats.journal_entries == 7 &&
      stats.tentative.inserted_rows == 5 && stats.tentative.erased_rows == 2 && stats.committed == actions,
      "tentative ownership/actions were counted as committed");
  auto live = journal.live();auto bucket = journal.bucket_cursor(f.indices[1], d.key(9));
  auto keys = journal.index_keys(f.indices[1]);auto other = ample();
  error("storage_contract", [&] { static_cast<void>(live.next(other)); });
  {
    s04_alloc::Scope deny(0);
    static_cast<void>(live.next(*work));static_cast<void>(bucket.next(*work));static_cast<void>(keys.next(*work));
  }
  verify(!s04_alloc::triggered && s04_alloc::calls == 0, "tentative cursor step allocated");
  f.table.check_invariants();work->admit(work->remaining());
  { s04_alloc::Scope deny(0);journal.rollback(); }
  verify(!s04_alloc::triggered && s04_alloc::calls == 0 && !journal.active() && journal.size() == 0,
      "rollback allocated or retained active history");
  verify(image(f) == before && f.pin.is_live() && &f.pin.get() == address &&
      f.table.statistics().committed == actions, "rollback changed logical rows/order/pins/actions");
  error("invalid_cursor", [&] { static_cast<void>(live.next(*work)); });
  error("invalid_cursor", [&] { static_cast<void>(outside.next(external_work)); });
  auto after = ample();verify(f.table.insert(d.row(5, 12), after).handle.tuple == TupleId{5},
      "rollback did not restore the private tentative ID counter");
}
void commit_retention(const Definition& d) {
  Fixture f(d);auto work = grant();auto journal = f.table.journal(work);
  verify(journal.erase(f.handles[0]) && journal.erase(f.handles[2]), "commit fixture erasure failed");
  verify(journal.insert(d.row(5, 10)).inserted, "commit fixture insertion failed");
  auto cursor = journal.live();const auto* erased = &journal.change(0).tuple;
  { s04_alloc::Scope deny(0);journal.commit(); }
  verify(!s04_alloc::triggered && s04_alloc::calls == 0 && !journal.active() && journal.size() == 3,
      "commit allocated or lost change views");
  verify(&journal.change(0).tuple == erased && cursor.next(*work)->handle == f.handles[1],
      "commit lost payload/cursor authority");
  const auto s = f.table.statistics();
  verify(s.rows == 3 && s.keys == 6 && s.memberships == 9 && s.nodes == 21 && s.retained_rows == 0 &&
      s.retained_memberships == 0 && s.journal_entries == 0 && s.tentative == IndexedActions{} &&
      s.committed.inserted_rows == 5 && s.committed.erased_rows == 2,
      "committed physical/logical counters do not reconcile");
  f.table.check_invariants();
}
void limits_and_ownership(const Definition& d) {
  Fixture f(d);auto observer = ample();auto cursor = f.table.live(observer);
  error("storage_contract", [&] { static_cast<void>(f.table.journal(nullptr)); });
  verify(cursor.next(observer)->handle == f.handles[0], "null journal changed a cursor");
  auto work = grant();std::weak_ptr<IndexWorkAllowance> weak = work;
  auto empty = f.table.journal(work);auto owned = empty.live();empty.commit();
  verify(owned.next(*work)->handle == f.handles[0], "empty commit invalidated its own cursor");
  auto aborted = f.table.journal(work);auto invalid = aborted.live();aborted.rollback();
  error("invalid_cursor", [&] { static_cast<void>(invalid.next(*work)); });
  work.reset();verify(!weak.expired(), "journal/cursor borrowed rather than owned its grant");
  auto cap = limits();cap.rows = 4;cap.journal_entries = 2;Fixture bounded(d, cap);auto shared = grant();
  auto journal = bounded.table.journal(shared);verify(journal.erase(bounded.handles[0]), "bounded erase failed");
  const auto before = image(bounded);const auto stats = bounded.table.statistics();
  error("storage_capacity", [&] { static_cast<void>(journal.insert(d.row(5, 12))); });
  verify(image(bounded) == before && bounded.table.statistics() == stats,
      "physical row retention cap failed after tentative erase");
  journal.rollback();
  cap = limits();cap.journal_entries = 1;Fixture one(d, cap);auto one_work = grant();auto single = one.table.journal(one_work);
  verify(single.erase(one.handles[0]) && !single.erase(one.handles[0]), "history cap rejected an absent no-op");
  error("storage_capacity", [&] { static_cast<void>(single.erase(one.handles[1])); });single.rollback();
  Fixture second(d);auto aggregate = grant();auto a = f.table.journal(aggregate);auto b = second.table.journal(aggregate);
  verify(a.erase(f.handles[0]), "composed first mutation failed");aggregate->admit(aggregate->remaining());
  error("storage_work_limit", [&] { static_cast<void>(b.insert(d.row(5, 12))); });
  { s04_alloc::Scope deny(0);a.rollback();b.rollback(); }
  verify(!s04_alloc::triggered && s04_alloc::calls == 0, "composed exhausted-grant rollback allocated");
}
void differential_tape(const Definition& d) {
  IndexedTable indexed(RelationId{1}, d.layout, limits());profile(indexed);
  ReferenceTable reference(RelationId{1}, d.layout);auto observer = ample();
  const auto index = indexed.add_index(d.programs[1], observer);const auto reference_index = reference.add_index(d.programs[1]);
  std::vector<std::int64_t> model;std::map<std::int64_t, TupleId> ids;std::uint64_t last = 0, random = 0x736f3434;
  for (unsigned epoch = 0; epoch < 40; ++epoch) {
    const auto saved = model;const auto saved_ids = ids;const auto saved_last = last;
    auto work = grant();auto a = indexed.journal(work);auto b = reference.journal();
    for (unsigned step = 0; step < 12; ++step) {
      random = random * 6364136223846793005ULL + 1442695040888963407ULL;
      const auto value = static_cast<std::int64_t>((random >> 24) % 16);const auto tuple = d.row(value, value % 4);
      const auto existing = std::find(model.begin(), model.end(), value);const bool present = existing != model.end();
      if ((random & 4) != 0) {
        const auto x = a.insert(tuple);const auto y = b.insert(tuple);
        verify(x.inserted == !present && y.inserted == !present, "journal model insertion flag differs");
        if (!present) { model.push_back(value);ids[value] = TupleId{++last}; }
        verify(x.handle.tuple == ids.at(value) && y.handle.tuple == ids.at(value), "journal model ID differs");
      } else {
        const auto x = indexed.find(tuple, *work);const auto y = reference.find(tuple);
        verify(bool(x) == present && bool(y) == present, "journal model lookup differs");
        if (present) { verify(a.erase(*x) && b.erase(*y), "journal model erase failed");model.erase(existing);ids.erase(value); }
      }
      std::vector<std::int64_t> actual;
      for (const auto& row : indexed.snapshot(observer)) actual.push_back(std::get<std::int64_t>(row.values()[0]));
      verify(actual == model, "journal live order differs from independent vector model");
      auto normalized = model;std::sort(normalized.begin(), normalized.end());actual.clear();
      for (const auto& row : reference.snapshot()) actual.push_back(std::get<std::int64_t>(row.values()[0]));
      std::sort(actual.begin(), actual.end());verify(actual == normalized, "S02 membership differs from independent model");
      for (std::int64_t key = 0; key < 4; ++key) {
        std::vector<TupleId> expected;
        for (auto value2 : model) if (value2 % 4 == key) expected.push_back(ids.at(value2));
        const auto probe = d.key(key);std::vector<TupleId> x, y;
        for (auto h : indexed.bucket(index, probe, observer)) x.push_back(h.tuple);
        for (auto h : reference.bucket(reference_index, probe)) y.push_back(h.tuple);
        verify(x == expected && y == expected, "journal bucket members/order differ from independent model");
      }
      indexed.check_invariants();reference.check_invariants();
    }
    work->admit(work->remaining());
    if (epoch % 3 == 0) {
      { s04_alloc::Scope deny(0);a.rollback(); }
      b.rollback();model = saved;ids = saved_ids;last = saved_last;
    } else {
      { s04_alloc::Scope deny(0);a.commit(); }
      b.commit();
    }
    verify(!s04_alloc::triggered && s04_alloc::calls == 0, "journal tape close allocated");
    indexed.check_invariants();reference.check_invariants();
  }
}
}  // namespace
int main() {
  Definition definition;rollback_order_growth(definition);commit_retention(definition);
  limits_and_ownership(definition);differential_tape(definition);
  std::cout << "S04 finite owning journals: order/growth, committed retention, exhausted nonallocating undo and480 independent-model operations passed\n";
}
