#include "crown/storage/table.hpp"
#include "index_allocation.hpp"
#ifdef CROWN_STORAGE_TESTING
#include "table_testing.hpp"
#endif

#include <algorithm>
#include <array>
#include <cstdint>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <type_traits>
#include <vector>

using namespace crown;
using namespace crown::storage;
namespace {
void verify(bool value, std::string_view message) {
  if (!value) throw std::runtime_error(std::string(message));
}
template<class Function> void error(std::string_view code, Function&& operation) {
  try { operation(); }
  catch (const Error& failure) { verify(failure.code() == code, "unexpected facade error");return; }
  throw std::runtime_error("expected facade error");
}
IndexWork budget() { return {1'000'000'000, 1'000'000'000, 1'000'000'000, 1'000'000'000, 1'000'000'000}; }
IndexWorkAllowance ample() { return IndexWorkAllowance(budget()); }
std::shared_ptr<IndexWorkAllowance> grant() { return std::make_shared<IndexWorkAllowance>(budget()); }
IndexedLimits limits() { return {128, 8, 4096, 4096, 8192, 32768, 256, 1024, 128}; }
struct Definition {
  TupleLayout layout{LayoutId{1}, {{ScalarType::int64}, {ScalarType::string}, {ScalarType::boolean},
      {ScalarType::date}, {ScalarType::decimal}}};
  std::vector<Projection> programs;
  Definition() {
    const std::vector<std::vector<FieldId>> fields{{FieldId{1}}, {}, {FieldId{4}, FieldId{0}, FieldId{2}, FieldId{1}, FieldId{4}}};
    for (std::size_t i = 0; i < fields.size(); ++i)
      programs.emplace_back(layout, projected_layout(LayoutId{2 + i}, layout, fields[i]), fields[i]);
  }
  std::string group(std::int64_t id) const {
    auto value = std::string(128, static_cast<char>('a' + id % 3));
    value.push_back(char{0});value.push_back(static_cast<char>(0xff));return value;
  }
  Tuple row(std::int64_t id) const {
    return layout.tuple({std::int64_t{9'007'199'254'740'992LL + id}, group(id), id % 2 == 0,
        Date::parse(id % 2 == 0 ? "0001-01-01" : "9999-12-31"),
        Decimal::parse("-12345678901234567890123456789012345678")});
  }
  Tuple key(std::int64_t id) const { return programs[0].target().tuple({group(id)}); }
};
StorageTable table(const Definition& d, bool indexed) {
  if (!indexed) return StorageTable(RelationId{1}, d.layout);
  StorageTable result(RelationId{1}, d.layout, limits());
#if defined(CROWN_STORAGE_COLLISION_PROFILE) && CROWN_STORAGE_COLLISION_PROFILE == 1
  detail::StorageTableTesting::collisions(result, detail::CollisionMode::same_bucket);
#elif defined(CROWN_STORAGE_COLLISION_PROFILE) && CROWN_STORAGE_COLLISION_PROFILE == 2
  detail::StorageTableTesting::collisions(result, detail::CollisionMode::same_full_hash);
#endif
  return result;
}
std::vector<std::int64_t> values(StorageTable& stored, IndexWorkAllowance* work) {
  std::vector<std::int64_t> result;
  for (const auto& row : stored.snapshot(work)) result.push_back(std::get<std::int64_t>(row.values()[0]) - 9'007'199'254'740'992LL);
  return result;
}
void facade_model(const Definition& d) {
  auto reference = table(d, false);auto indexed = table(d, true);auto work = ample();
  verify(reference.backend() == StorageBackend::reference_ordered_v1 &&
      indexed.backend() == StorageBackend::indexed_chained_v1 && !reference.indexed_limits() &&
      indexed.indexed_limits() == std::optional<IndexedLimits>(limits()), "facade reported the wrong actual backend");
  verify(reference.owner() != indexed.owner(), "facade backends use duplicate owner counters");
  std::vector<IndexId> left_indices, right_indices;
  for (const auto& program : d.programs) {
    left_indices.push_back(reference.add_index(program));right_indices.push_back(indexed.add_index(program, &work));
  }
  verify(reference.indices() == left_indices && indexed.indices(&work) == right_indices &&
      indexed.projection(right_indices[2], &work).same_token(d.programs[2]), "facade index programs differ");
  const auto before = indexed.indexed_statistics();
  error("storage_contract", [&] { static_cast<void>(indexed.insert(d.row(0))); });
  error("storage_contract", [&] { static_cast<void>(indexed.find(d.row(0))); });
  error("storage_contract", [&] { static_cast<void>(indexed.snapshot_copy()); });
  error("storage_contract", [&] { static_cast<void>(indexed.journal()); });
  verify(indexed.indexed_statistics() == before, "missing grant changed indexed state");
  std::vector<std::int64_t> model, key_order;std::map<std::int64_t, TupleId> ids;
  std::uint64_t last = 0, random = 0x53544f52414745;
  for (unsigned step = 0; step < 500; ++step) {
    random = random * 6364136223846793005ULL + 1442695040888963407ULL;
    const auto id = static_cast<std::int64_t>((random >> 32) % 16);const auto row = d.row(id);
    auto found = std::find(model.begin(), model.end(), id);const bool present = found != model.end();
    if (step % 71 == 70) { reference.clear();indexed.clear(&work);model.clear();ids.clear();key_order.clear(); }
    else if ((random & 4) != 0) {
      const auto a = reference.insert(row);const auto b = indexed.insert(row, &work);
      verify(a.inserted == !present && b.inserted == !present, "facade model insert flag differs");
      if (!present) {
        if (std::none_of(model.begin(), model.end(), [&](auto value) { return value % 3 == id % 3; })) key_order.push_back(id % 3);
        model.push_back(id);ids[id] = TupleId{++last};
      }
      verify(a.handle.tuple == ids.at(id) && b.handle.tuple == ids.at(id), "facade renumbered IDs");
      error("foreign_handle", [&] { static_cast<void>(indexed.get(a.handle, &work)); });
    } else {
      verify(reference.erase(row) == present && indexed.erase(row, &work) == present, "facade model erase flag differs");
      if (present) {
        model.erase(found);ids.erase(id);
        if (std::none_of(model.begin(), model.end(), [&](auto value) { return value % 3 == id % 3; }))
          key_order.erase(std::find(key_order.begin(), key_order.end(), id % 3));
      }
    }
    auto sorted = model;std::sort(sorted.begin(), sorted.end());
    verify(values(reference, nullptr) == sorted && values(indexed, &work) == model, "facade row membership/order differs from independent model");
    for (std::int64_t group = 0; group < 3; ++group) {
      std::vector<TupleId> expected, a, b;
      for (auto value : model) if (value % 3 == group) expected.push_back(ids.at(value));
      const auto key = d.key(group);
      for (auto h : reference.bucket(left_indices[0], key)) a.push_back(h.tuple);
      for (auto h : indexed.bucket(right_indices[0], key, &work)) b.push_back(h.tuple);
      verify(a == expected && b == expected, "facade bucket dispatch differs from independent model");
    }
    const auto keys = indexed.keys(right_indices[0], &work);verify(keys.size() == key_order.size(), "facade key count differs");
    for (std::size_t i = 0; i < keys.size(); ++i)
      verify(std::get<std::string>(crown::storage::export_row(keys[i].values())[0]) == d.group(key_order[i]), "facade first-live key order differs");
    reference.check_invariants();indexed.check_invariants();
  }
  const auto extra = d.row(99);auto copy = indexed.snapshot_copy(&work);auto reference_copy = reference.snapshot_copy();
  verify(copy.backend() == indexed.backend() && copy.owner() != indexed.owner() &&
      reference_copy.owner() != reference.owner() && values(copy, &work) == model &&
      values(reference_copy, nullptr) == values(reference, nullptr), "facade copy lost backend/owner/order");
  verify(copy.insert(extra, &work).handle.tuple == TupleId{last + 1} &&
      reference_copy.insert(extra).handle.tuple == TupleId{last + 1}, "facade copy lost deleted-ID high water");
  verify(copy.drop_index(right_indices[2], &work) && reference_copy.drop_index(left_indices[2]), "facade index drop failed");
  copy.check_invariants();reference_copy.check_invariants();
}
void cursors_and_copy(const Definition& d, bool indexed) {
  auto stored = table(d, indexed);auto work = ample();const auto index = stored.add_index(d.programs[0], &work);
  const auto a = stored.insert(d.row(6), &work).handle;const auto b = stored.insert(d.row(0), &work).handle;
  auto pin = stored.pin(a, &work);const auto* address = &pin.get();
  auto live = stored.live(&work);auto bucket = stored.bucket_cursor(index, d.key(0), &work);
  auto keys = stored.index_keys(index, &work);auto moved = std::move(stored);
  {
    s04_alloc::Scope deny(0);
    for (unsigned i = 0; i < 2; ++i) {
      const auto row = live.next_entry(&work);verify(bool(row), "facade live cursor omitted a row");
      verify(&row->tuple == moved.get(row->handle, &work), "facade borrowed a different allocation");
      const auto member = bucket.next_entry(&work);verify(bool(member), "facade bucket cursor omitted a row");
      verify(&member->tuple == moved.get(member->handle, &work), "bucket borrowed a different allocation");
    }
    verify(!live.next_entry(&work) && !bucket.next_entry(&work) && keys.next(&work)->degree == 2 && !keys.next(&work),
        "facade cursor end/key degree differs");
  }
  verify(!s04_alloc::triggered && s04_alloc::calls == 0, "facade successful borrowed steps allocated");
  auto before = moved.snapshot(&work);std::size_t count = 0;
  { s04_alloc::Scope measure;auto copy = moved.snapshot_copy(&work);count = s04_alloc::calls; }
  verify(count > 0, "facade copy allocation baseline absent");
  for (std::size_t position = 0; position < count; ++position) {
    bool caught = false;auto cursor = moved.live(&work);
    try { s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(position));auto copy = moved.snapshot_copy(&work); }
    catch (const std::bad_alloc&) { caught = true; }
    verify(caught && s04_alloc::triggered && moved.snapshot(&work) == before &&
        cursor.next(&work).has_value() && &pin.get() == address && pin.is_live(), "facade failed copy changed source");
  }
  verify(moved.erase(b, &work) && moved.erase_key(index, d.key(0), &work) == 1 && moved.size() == 0 &&
      !pin.is_live() && &pin.get() == address, "facade erasure or pin retention differs");
  moved.check_invariants();
}
void journal_lifetimes(const Definition& d, bool indexed) {
  auto stored = table(d, indexed);auto setup = ample();const auto id = stored.add_index(d.programs[2], &setup);
  static_cast<void>(id);const auto original = stored.insert(d.row(1), &setup).handle;
  auto pin = stored.pin(original, &setup);const auto before = stored.snapshot(&setup);
  auto work = grant();auto active = stored.journal(work);verify(active.erase(original), "facade journal erase failed");
  verify(active.insert(d.row(2)).inserted, "facade journal insert failed");auto own = active.live();
  auto wrong = ample();if (indexed) error("storage_contract", [&] { static_cast<void>(own.next(&wrong)); });
  std::optional<StorageTable::Journal> rollback(std::move(active));work->admit(work->remaining());
  { s04_alloc::Scope deny(0);rollback.reset(); }
  verify(!s04_alloc::triggered && s04_alloc::calls == 0 && stored.snapshot(&setup) == before && pin.is_live(),
      "implicit facade journal destruction failed to undo without allocation");
  error("invalid_cursor", [&] { static_cast<void>(own.next()); });
  auto other = table(d, !indexed);static_cast<void>(other.insert(d.row(7), &setup));
  auto a_work = grant(), b_work = grant();auto a = stored.journal(a_work);auto b = other.journal(b_work);
  verify(a.erase(original) && b.insert(d.row(8)).inserted, "facade move-assignment setup failed");
  a_work->admit(a_work->remaining());
  { s04_alloc::Scope deny(0);a = std::move(b); }
  verify(!s04_alloc::triggered && s04_alloc::calls == 0 && stored.snapshot(&setup) == before && a.active() && !b.active(),
      "cross-backend journal assignment failed to roll back replaced scope");
  b_work->admit(b_work->remaining());{ s04_alloc::Scope deny(0);a.rollback(); }
  verify(!s04_alloc::triggered && s04_alloc::calls == 0 && other.size() == 1, "moved facade journal undo failed");
  auto owner = std::make_unique<StorageTable>(table(d, indexed));auto retained_work = grant();
  std::optional<StorageTable::Journal> surviving(owner->journal(retained_work));
  verify(surviving->insert(d.row(3)).inserted, "surviving journal insert failed");auto cursor = surviving->live();
  const auto* payload = &surviving->change(0).tuple;owner.reset();
  verify(cursor.next_entry()->tuple == d.row(3), "active journal did not retain its state after wrapper loss");
  retained_work->admit(retained_work->remaining());{ s04_alloc::Scope deny(0);surviving->commit(); }
  verify(!s04_alloc::triggered && s04_alloc::calls == 0 && &surviving->change(0).tuple == payload &&
      surviving->change(0).tuple == d.row(3), "commit lost an ownerless retained change view");
  error("invalid_cursor", [&] { static_cast<void>(cursor.next_entry()); });
}
void literal_journal_boundaries() {
  // Literal admission oracle for the selected 64-bit ABI: open11 metadata
  // words, one entry pointer and19 undo words. No production cost/sizeof-Undo
  // helper computes these limits. The primitive's ordinary insert oracle is
  // {4,4,25,16,18}; a journal prepays its inverse and owns its metadata too.
  static_assert(sizeof(void*) == 8 && sizeof(TupleArena::Pin) == 40);
  const std::array<std::uint64_t IndexWork::*, 5> domains{&IndexWork::structural_steps,
      &IndexWork::scalar_fields, &IndexWork::scalar_bytes, &IndexWork::pointer_slots, &IndexWork::link_actions};
  TupleLayout layout(LayoutId{901}, {{ScalarType::int64}});const auto row = layout.tuple({std::int64_t{0}});
  const IndexedLimits cap{1, 0, 0, 0, 1, 16, 1, 1, 1};
  for (bool erasing : {false, true}) {
    const IndexWork exact = erasing ? IndexWork{6, 2, 8, 31, 42} : IndexWork{7, 4, 25, 47, 42};
    for (int domain = -1; domain < 5; ++domain) {
      for (bool commit : {false, true}) {
        StorageTable stored(RelationId{901}, layout, cap);auto observer = ample();TupleHandle handle{};
        if (erasing) handle = stored.insert(row, &observer).handle;
        const auto before = stored.snapshot(&observer);const auto statistics = stored.indexed_statistics();
        auto outside = stored.live(&observer);auto limit = exact;
        if (domain >= 0) --(limit.*domains[static_cast<std::size_t>(domain)]);
        auto work = std::make_shared<IndexWorkAllowance>(limit);
        if (domain >= 0) {
          error("storage_work_limit", [&] {
            auto scope = stored.journal(work);
            if (erasing) static_cast<void>(scope.erase(handle));else static_cast<void>(scope.insert(row));
          });
          verify(stored.snapshot(&observer) == before && stored.indexed_statistics() == statistics &&
              bool(outside.next(&observer)) == erasing, "one-under journal grant changed state or cursor");
        } else {
          auto scope = stored.journal(work);
          verify(erasing ? scope.erase(handle) : scope.insert(row).inserted, "exact journal grant rejected mutation");
          verify(work->remaining() == IndexWork{}, "literal journal budget was not exact");
          { s04_alloc::Scope deny(0);if (commit) scope.commit();else scope.rollback(); }
          verify(!s04_alloc::triggered && s04_alloc::calls == 0 && !scope.active(), "exact exhausted journal close allocated");
          verify(stored.size() == (commit ? (erasing ? 0U : 1U) : (erasing ? 1U : 0U)),
              "exact journal close produced wrong membership");
          stored.check_invariants();
        }
      }
    }
    for (bool pin_limit : {false, true}) {
      auto smaller = cap;if (pin_limit) smaller.arena_pins = 0;else smaller.journal_entries = 0;
      StorageTable stored(RelationId{902}, layout, smaller);auto observer = ample();TupleHandle handle{};
      if (erasing) handle = stored.insert(row, &observer).handle;
      const auto before = stored.snapshot(&observer);const auto statistics = stored.indexed_statistics();
      auto work = grant();auto scope = stored.journal(work);
      error("storage_capacity", [&] {
        if (erasing) static_cast<void>(scope.erase(handle));else static_cast<void>(scope.insert(row));
      });
      verify(scope.size() == 0 && stored.snapshot(&observer) == before && stored.indexed_statistics() == statistics,
          "one-under pin/entry cap changed committed state");
      work->admit(work->remaining());{ s04_alloc::Scope deny(0);scope.rollback(); }
      verify(!s04_alloc::triggered && s04_alloc::calls == 0, "empty capped journal rollback allocated");
    }
  }
}
}  // namespace
static_assert(std::is_nothrow_move_constructible_v<StorageTable>);
static_assert(std::is_nothrow_move_assignable_v<StorageTable::Journal>);
int main() {
  Definition definition;facade_model(definition);
  for (bool indexed : {false, true}) { cursors_and_copy(definition, indexed);journal_lifetimes(definition, indexed); }
  literal_journal_boundaries();
  std::cout << "StorageTable:500 independent operations, explicit grants, borrowed cursors, all copy faults and cross-backend journal lifetimes passed\n";
}
