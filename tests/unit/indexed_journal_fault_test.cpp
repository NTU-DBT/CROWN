#include "crown/storage/indexed.hpp"
#include "index_allocation.hpp"
#ifdef CROWN_STORAGE_TESTING
#include "indexed_testing.hpp"
#endif

#include <cstdint>
#include <iostream>
#include <limits>
#include <memory>
#include <optional>
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
IndexWork budget() { return {100'000'000, 100'000'000, 100'000'000, 100'000'000, 100'000'000}; }
IndexWorkAllowance ample() { return IndexWorkAllowance(budget()); }
std::shared_ptr<IndexWorkAllowance> grant() { return std::make_shared<IndexWorkAllowance>(budget()); }
struct Definition {
  TupleLayout layout{LayoutId{1}, {{ScalarType::int64}, {ScalarType::int64},
      {ScalarType::string}, {ScalarType::decimal}}};
  std::vector<Projection> programs;
  std::vector<Tuple> rows;
  Tuple addition;
  Definition() : addition(row(5, 99)) {
    const std::vector<std::vector<FieldId>> fields{{}, {FieldId{1}}, {FieldId{0}, FieldId{1}, FieldId{0}}};
    for (std::size_t i = 0; i < fields.size(); ++i)
      programs.emplace_back(layout, projected_layout(LayoutId{2 + i}, layout, fields[i]), fields[i]);
    rows.push_back(row(1, 9));rows.push_back(row(2, 10));rows.push_back(row(3, 9));rows.push_back(row(4, 11));
  }
  Tuple row(std::int64_t id, std::int64_t key) const {
    return layout.tuple({id, key, std::string(512, static_cast<char>('a' + id)),
        Decimal::parse("-12345678901234567890123456789012345678")});
  }
};
struct Fixture {
  IndexedTable table;
  std::vector<IndexId> indices;
  std::vector<TupleHandle> handles;
  TupleArena::Pin pin;
  const Tuple* pinned_address;
  explicit Fixture(const Definition& d)
      : table(RelationId{1}, d.layout, {64, 8, 1024, 2048, 4096, 16384, 256, 256, 128}),
        pin(build(d)), pinned_address(&pin.get()) {}
  TupleArena::Pin build(const Definition& d) {
#if defined(CROWN_STORAGE_COLLISION_PROFILE) && CROWN_STORAGE_COLLISION_PROFILE == 1
    detail::IndexedTesting::collisions(table, detail::CollisionMode::same_bucket);
#elif defined(CROWN_STORAGE_COLLISION_PROFILE) && CROWN_STORAGE_COLLISION_PROFILE == 2
    detail::IndexedTesting::collisions(table, detail::CollisionMode::same_full_hash);
#endif
    auto work = ample();
    for (const auto& p : d.programs) indices.push_back(table.add_index(p, work));
    for (const auto& row : d.rows) handles.push_back(table.insert(row, work).handle);
    return table.pin(handles.front(), work);
  }
};
struct KeyImage {
  Tuple value;
  std::vector<TupleId> members;
  bool operator==(const KeyImage&) const = default;
};
struct Image {
  IndexedStatistics statistics;
  std::uint64_t revision;
  std::vector<Tuple> rows;
  std::vector<std::vector<KeyImage>> indices;
  bool pin_live;
  bool operator==(const Image&) const = default;
};
// A separate observer owns these copies. They neither replenish the journal's
// grant nor run inside its failure window.
Image image(Fixture& f) {
  auto work = ample();Image result{f.table.statistics(), f.table.revision(), f.table.snapshot(work), {}, f.pin.is_live()};
  for (auto id : f.indices) {
    std::vector<KeyImage> keys;
    for (const auto& key : f.table.keys(id, work)) {
      KeyImage entry{key, {}};
      for (auto handle : f.table.bucket(id, key, work)) entry.members.push_back(handle.tuple);
      keys.push_back(std::move(entry));
    }
    result.indices.push_back(std::move(keys));
  }
  f.table.check_invariants();verify(&f.pin.get() == f.pinned_address, "fault moved a pinned allocation");return result;
}
struct Streams {
  IndexedTable::Cursor live;
  std::vector<IndexedTable::IndexKeyCursor> keys;
  std::vector<IndexedTable::Cursor> buckets;
  Streams(Fixture& f, IndexedTable::Journal& journal, const Image& before) : live(journal.live()) {
    for (std::size_t i = 0; i < f.indices.size(); ++i) {
      keys.push_back(journal.index_keys(f.indices[i]));
      for (const auto& key : before.indices[i]) buckets.push_back(journal.bucket_cursor(f.indices[i], key.value));
    }
  }
  // All metadata/copies were prepared before failure. Comparison follows only
  // already-owned cursors and exact borrowed values, including every end check.
  bool same(Fixture& f, const Image& before, IndexWorkAllowance& work) {
    if (f.table.statistics() != before.statistics || f.table.revision() != before.revision ||
        f.pin.is_live() != before.pin_live || &f.pin.get() != f.pinned_address) return false;
    for (const auto& row : before.rows) {
      const auto entry = live.next(work);if (!entry || entry->tuple != row) return false;
    }
    if (live.next(work)) return false;
    std::size_t position = 0;
    for (std::size_t i = 0; i < keys.size(); ++i) {
      for (const auto& expected : before.indices[i]) {
        const auto key = keys[i].next(work);
        if (!key || key->key != expected.value || key->degree != expected.members.size()) return false;
        auto& bucket = buckets[position++];
        for (auto id : expected.members) {
          const auto entry = bucket.next(work);
          if (!entry || entry->handle.tuple != id || entry->handle.owner != f.table.owner() ||
              entry->handle.relation != RelationId{1}) return false;
        }
        if (bucket.next(work)) return false;
      }
      if (keys[i].next(work)) return false;
    }
    return position == buckets.size();
  }
};
enum class Operation { insert, erase, duplicate, absent, live, bucket, keys };
std::uint64_t apply(Fixture& f, const Definition& d, IndexedTable::Journal& journal, Operation operation) {
  switch (operation) {
    case Operation::insert: return journal.insert(d.addition).handle.tuple.value;
    case Operation::erase: return journal.erase(f.handles[1]) ? 1 : 0;
    case Operation::duplicate: return journal.insert(d.rows[1]).inserted ? 1 : 0;
    case Operation::absent: return journal.erase({f.table.owner(), RelationId{1}, TupleId{999}}) ? 1 : 0;
    case Operation::live: { auto cursor = journal.live();return 0; }
    case Operation::bucket: { auto cursor = journal.bucket_cursor(f.indices.front(), d.programs.front().target().tuple({}));return 0; }
    case Operation::keys: { auto cursor = journal.index_keys(f.indices[1]);return 0; }
  }
  throw std::runtime_error("unknown journal fault operation");
}
void sweep(const Definition& d, Operation operation, const char* label, bool must_allocate) {
  Fixture baseline(d);auto baseline_work = grant();auto baseline_journal = baseline.table.journal(baseline_work);
  verify(baseline_journal.erase(baseline.handles[0]), "baseline prefix erase failed");
  std::size_t count = 0;std::uint64_t expected_result = 0;
  { s04_alloc::Scope measure;expected_result = apply(baseline, d, baseline_journal, operation);count = s04_alloc::calls; }
  verify(!s04_alloc::triggered && (must_allocate ? count > 0 : count == 0), "journal allocation class differs");
  baseline_work->admit(baseline_work->remaining());
  { s04_alloc::Scope deny(0);baseline_journal.commit(); }
  verify(!s04_alloc::triggered && s04_alloc::calls == 0, "successful journal commit allocated");
  const auto completed = image(baseline);Fixture subject(d);const auto initial = image(subject);
  for (std::size_t position = 0; position < count; ++position) {
    verify(position <= static_cast<std::size_t>(std::numeric_limits<std::ptrdiff_t>::max()), "journal injector overflow");
    auto work = grant();auto journal = subject.table.journal(work);
    verify(journal.erase(subject.handles[0]), "subject prefix erase failed");
    const auto before = image(subject);Streams cursors(subject, journal, before);
    bool caught = false, intact = false, no_recovery_attempt = false;
    {
      s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(position));
      try { static_cast<void>(apply(subject, d, journal, operation)); }
      catch (const std::bad_alloc&) { caught = true; }
      no_recovery_attempt = s04_alloc::triggered && s04_alloc::calls == position + 1;
      try { intact = caught && cursors.same(subject, before, *work); }
      catch (...) { intact = false; }
      work->admit(work->remaining());journal.rollback();
      no_recovery_attempt = no_recovery_attempt && s04_alloc::calls == position + 1;
    }
    verify(caught && intact && no_recovery_attempt && !journal.active(),
        "persistent journal failure changed state/cursors or allocated during recovery");
    const auto restored = image(subject);
    verify(restored.rows == initial.rows && restored.indices == initial.indices && restored.pin_live &&
        restored.statistics.committed == initial.statistics.committed && restored.statistics.retained_rows == 0 &&
        restored.statistics.retained_memberships == 0 && restored.statistics.journal_entries == 0 &&
        restored.statistics.tentative == IndexedActions{} && restored.statistics.nodes == initial.statistics.nodes,
        "prefix rollback after persistent failure changed committed state");
  }
  auto retry_work = grant();auto retry = subject.table.journal(retry_work);
  verify(retry.erase(subject.handles[0]), "retry prefix failed");std::uint64_t result = 0;
  if (count == 0) { s04_alloc::Scope deny(0);result = apply(subject, d, retry, operation); }
  else result = apply(subject, d, retry, operation);
  retry_work->admit(retry_work->remaining());
  { s04_alloc::Scope deny(0);retry.commit(); }
  auto actual = image(subject);actual.revision = completed.revision;
  verify(!s04_alloc::triggered && s04_alloc::calls == 0 && result == expected_result && actual == completed,
      "journal retry differs from successful full-state baseline");
  std::cout << label << " positions=" << count << " recovery_allocations=0 retry=complete\n";
}
void opening(const Definition& d) {
  Fixture baseline(d);auto work = grant();std::optional<IndexedTable::Journal> journal;std::size_t count = 0;
  { s04_alloc::Scope measure;journal.emplace(baseline.table.journal(work));count = s04_alloc::calls; }
  verify(count > 0 && !s04_alloc::triggered, "opening allocation baseline absent");journal->rollback();
  Fixture subject(d);const auto initial = image(subject);
  for (std::size_t position = 0; position < count; ++position) {
    auto allowance = grant();std::optional<IndexedTable::Journal> candidate;bool caught = false;
    { s04_alloc::Scope fault(static_cast<std::ptrdiff_t>(position));
      try { candidate.emplace(subject.table.journal(allowance)); }
      catch (const std::bad_alloc&) { caught = true; }
    }
    verify(caught && s04_alloc::triggered && !candidate && image(subject) == initial,
        "failed journal opening published exclusivity or changed state");
  }
  std::cout << "journal_open positions=" << count << " no_published_exclusivity\n";
}
}  // namespace
int main() {
  Definition definition;opening(definition);
  sweep(definition, Operation::insert, "partial_insert", true);
  sweep(definition, Operation::erase, "partial_erase", true);
  sweep(definition, Operation::duplicate, "partial_duplicate", true);
  sweep(definition, Operation::absent, "partial_absent", false);
  sweep(definition, Operation::live, "partial_live_cursor", true);
  sweep(definition, Operation::bucket, "partial_bucket_cursor", true);
  sweep(definition, Operation::keys, "partial_key_cursor", true);
}
