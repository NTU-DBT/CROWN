#include "crown/storage/table.hpp"

#include "crown/api/error.hpp"
#ifdef CROWN_STORAGE_TESTING
#include "table_testing.hpp"
#endif
#include <utility>

namespace crown::storage {
namespace {
IndexWorkAllowance& required(IndexWorkAllowance* work) {
  if (!work) throw Error("storage_contract", "indexed operation requires an explicit finite work grant");
  return *work;
}
IndexWorkAllowance& cursor_work(IndexWorkAllowance* requested, const std::shared_ptr<IndexWorkAllowance>& owned) {
  if (owned && requested && owned.get() != requested)
    throw Error("storage_contract", "journal cursor requires its original owning work grant");
  return required(requested ? requested : owned.get());
}
}  // namespace

StorageTable::StorageTable(RelationId relation, TupleLayout layout)
    : native_(std::in_place_type<ReferenceTable>, relation, std::move(layout)) {}
StorageTable::StorageTable(RelationId relation, TupleLayout layout, IndexedLimits limits)
    : native_(std::in_place_type<IndexedTable>, relation, std::move(layout), limits) {}
StorageTable::StorageTable(ReferenceTable&& table) noexcept
    : native_(std::in_place_type<ReferenceTable>, std::move(table)) {}
StorageTable::StorageTable(IndexedTable&& table) noexcept
    : native_(std::in_place_type<IndexedTable>, std::move(table)) {}
StorageBackend StorageTable::backend() const noexcept {
  return native_.index() == 0 ? StorageBackend::reference_ordered_v1 : StorageBackend::indexed_chained_v1;
}
StorageOwnerId StorageTable::owner() const { return std::visit([](const auto& table) { return table.owner(); }, native_); }
RelationId StorageTable::relation() const { return std::visit([](const auto& table) { return table.relation(); }, native_); }
const TupleLayout& StorageTable::layout() const {
  return std::visit([](const auto& table) -> const TupleLayout& { return table.layout(); }, native_);
}
std::size_t StorageTable::size() const { return std::visit([](const auto& table) { return table.size(); }, native_); }
std::uint64_t StorageTable::revision() const { return std::visit([](const auto& table) { return table.revision(); }, native_); }
ArenaStatistics StorageTable::arena_statistics() const {
  return std::visit([](const auto& table) { return table.arena_statistics(); }, native_);
}
std::optional<IndexedLimits> StorageTable::indexed_limits() const {
  if (const auto* table = std::get_if<IndexedTable>(&native_)) return table->limits();
  return {};
}
std::optional<IndexedStatistics> StorageTable::indexed_statistics() const {
  if (const auto* table = std::get_if<IndexedTable>(&native_)) return table->statistics();
  return {};
}
InsertResult StorageTable::insert(const Tuple& tuple, IndexWorkAllowance* work) {
  if (auto* table = std::get_if<ReferenceTable>(&native_)) return table->insert(tuple);
  return std::get<IndexedTable>(native_).insert(tuple, required(work));
}
std::optional<TupleHandle> StorageTable::find(const Tuple& tuple, IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<ReferenceTable>(&native_)) return table->find(tuple);
  return std::get<IndexedTable>(native_).find(tuple, required(work));
}
const Tuple* StorageTable::get(TupleHandle handle, IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<ReferenceTable>(&native_)) return table->get(handle);
  return std::get<IndexedTable>(native_).get(handle, required(work));
}
TupleArena::Pin StorageTable::pin(TupleHandle handle, IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<ReferenceTable>(&native_)) return table->pin(handle);
  return std::get<IndexedTable>(native_).pin(handle, required(work));
}
bool StorageTable::erase(const Tuple& tuple, IndexWorkAllowance* work) {
  if (auto* table = std::get_if<ReferenceTable>(&native_)) return table->erase(tuple);
  return std::get<IndexedTable>(native_).erase(tuple, required(work));
}
bool StorageTable::erase(TupleHandle handle, IndexWorkAllowance* work) {
  if (auto* table = std::get_if<ReferenceTable>(&native_)) return table->erase(handle);
  return std::get<IndexedTable>(native_).erase(handle, required(work));
}
IndexId StorageTable::add_index(Projection projection, IndexWorkAllowance* work) {
  if (auto* table = std::get_if<ReferenceTable>(&native_)) return table->add_index(std::move(projection));
  auto& allowance = required(work);
  return std::get<IndexedTable>(native_).add_index(std::move(projection), allowance);
}
bool StorageTable::drop_index(IndexId index, IndexWorkAllowance* work) {
  if (auto* table = std::get_if<ReferenceTable>(&native_)) return table->drop_index(index);
  return std::get<IndexedTable>(native_).drop_index(index, required(work));
}
std::vector<IndexId> StorageTable::indices(IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<ReferenceTable>(&native_)) return table->indices();
  return std::get<IndexedTable>(native_).indices(required(work));
}
Projection StorageTable::projection(IndexId index, IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<ReferenceTable>(&native_)) return table->projection(index);
  return std::get<IndexedTable>(native_).projection(index, required(work));
}
std::size_t StorageTable::key_count(IndexId index, IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<ReferenceTable>(&native_)) return table->key_count(index);
  return std::get<IndexedTable>(native_).key_count(index, required(work));
}
std::vector<Tuple> StorageTable::keys(IndexId index, IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<ReferenceTable>(&native_)) return table->keys(index);
  return std::get<IndexedTable>(native_).keys(index, required(work));
}
std::vector<TupleHandle> StorageTable::bucket(IndexId index, const Tuple& key, IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<ReferenceTable>(&native_)) return table->bucket(index, key);
  return std::get<IndexedTable>(native_).bucket(index, key, required(work));
}
std::size_t StorageTable::erase_key(IndexId index, const Tuple& key, IndexWorkAllowance* work) {
  if (auto* table = std::get_if<ReferenceTable>(&native_)) return table->erase_key(index, key);
  return std::get<IndexedTable>(native_).erase_key(index, key, required(work));
}
void StorageTable::clear(IndexWorkAllowance* work) {
  if (auto* table = std::get_if<ReferenceTable>(&native_)) table->clear();
  else std::get<IndexedTable>(native_).clear(required(work));
}
std::vector<Tuple> StorageTable::snapshot(IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<ReferenceTable>(&native_)) return table->snapshot();
  return std::get<IndexedTable>(native_).snapshot(required(work));
}
StorageTable StorageTable::snapshot_copy(IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<ReferenceTable>(&native_)) return StorageTable(table->snapshot_copy());
  return StorageTable(std::get<IndexedTable>(native_).snapshot_copy(required(work)));
}
void StorageTable::check_invariants() const { std::visit([](const auto& table) { table.check_invariants(); }, native_); }

StorageTable::Cursor::Cursor(ReferenceTable::Cursor&& cursor, std::shared_ptr<IndexWorkAllowance> work)
    : native_(std::in_place_type<ReferenceTable::Cursor>, std::move(cursor)), work_(std::move(work)) {}
StorageTable::Cursor::Cursor(IndexedTable::Cursor&& cursor, std::shared_ptr<IndexWorkAllowance> work)
    : native_(std::in_place_type<IndexedTable::Cursor>, std::move(cursor)), work_(std::move(work)) {}
std::optional<TupleHandle> StorageTable::Cursor::next(IndexWorkAllowance* work) {
  // Keep the ordered backend on its direct handle walk; next_entry() would
  // add a ById lookup for every reference bucket member.
  if (auto* cursor = std::get_if<ReferenceTable::Cursor>(&native_)) return cursor->next();
  const auto entry = std::get<IndexedTable::Cursor>(native_).next(cursor_work(work, work_));
  if (!entry) return {};
  return entry->handle;
}
std::optional<StorageTable::Cursor::Entry> StorageTable::Cursor::next_entry(IndexWorkAllowance* work) {
  if (auto* cursor = std::get_if<ReferenceTable::Cursor>(&native_)) {
    const auto entry = cursor->next_entry();if (!entry) return {};
    return Entry{entry->handle, entry->tuple};
  }
  const auto entry = std::get<IndexedTable::Cursor>(native_).next(cursor_work(work, work_));
  if (!entry) return {};
  return Entry{entry->handle, entry->tuple};
}
StorageTable::Cursor StorageTable::live(IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<ReferenceTable>(&native_)) return Cursor(table->live());
  return Cursor(std::get<IndexedTable>(native_).live(required(work)));
}
StorageTable::Cursor StorageTable::bucket_cursor(IndexId index, const Tuple& key, IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<ReferenceTable>(&native_)) return Cursor(table->bucket_cursor(index, key));
  return Cursor(std::get<IndexedTable>(native_).bucket_cursor(index, key, required(work)));
}
StorageTable::IndexKeyCursor::IndexKeyCursor(ReferenceTable::IndexKeyCursor&& cursor)
    : native_(std::in_place_type<ReferenceTable::IndexKeyCursor>, std::move(cursor)) {}
StorageTable::IndexKeyCursor::IndexKeyCursor(IndexedTable::IndexKeyCursor&& cursor)
    : native_(std::in_place_type<IndexedTable::IndexKeyCursor>, std::move(cursor)) {}
std::optional<StorageTable::IndexKeyCursor::Entry> StorageTable::IndexKeyCursor::next(IndexWorkAllowance* work) {
  if (auto* cursor = std::get_if<ReferenceTable::IndexKeyCursor>(&native_)) {
    const auto entry = cursor->next();if (!entry) return {};
    return Entry{entry->key, entry->degree};
  }
  const auto entry = std::get<IndexedTable::IndexKeyCursor>(native_).next(required(work));
  if (!entry) return {};
  return Entry{entry->key, entry->degree};
}
StorageTable::IndexKeyCursor StorageTable::index_keys(IndexId index, IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<ReferenceTable>(&native_)) return IndexKeyCursor(table->index_keys(index));
  return IndexKeyCursor(std::get<IndexedTable>(native_).index_keys(index, required(work)));
}

StorageTable::Journal::Journal(ReferenceTable::Journal&& journal, std::shared_ptr<IndexWorkAllowance> work)
    : native_(std::in_place_type<ReferenceTable::Journal>, std::move(journal)), work_(std::move(work)) {}
StorageTable::Journal::Journal(IndexedTable::Journal&& journal, std::shared_ptr<IndexWorkAllowance> work)
    : native_(std::in_place_type<IndexedTable::Journal>, std::move(journal)), work_(std::move(work)) {}
bool StorageTable::Journal::active() const noexcept {
  return std::visit([](const auto& journal) { return journal.active(); }, native_);
}
std::size_t StorageTable::Journal::size() const noexcept {
  return std::visit([](const auto& journal) { return journal.size(); }, native_);
}
StorageTable::ChangeView StorageTable::Journal::change(std::size_t index) const {
  return std::visit([&](const auto& journal) -> ChangeView {
    const auto value = journal.change(index);return {value.inserted, value.handle, value.tuple};
  }, native_);
}
InsertResult StorageTable::Journal::insert(const Tuple& tuple) {
  return std::visit([&](auto& journal) { return journal.insert(tuple); }, native_);
}
bool StorageTable::Journal::erase(TupleHandle handle) {
  return std::visit([&](auto& journal) { return journal.erase(handle); }, native_);
}
void StorageTable::Journal::commit() noexcept { std::visit([](auto& journal) { journal.commit(); }, native_); }
void StorageTable::Journal::rollback() noexcept { std::visit([](auto& journal) { journal.rollback(); }, native_); }
StorageTable::Cursor StorageTable::Journal::live() const {
  return std::visit([&](const auto& journal) { return Cursor(journal.live(), work_); }, native_);
}
StorageTable::Cursor StorageTable::Journal::bucket_cursor(IndexId index, const Tuple& key) const {
  return std::visit([&](const auto& journal) { return Cursor(journal.bucket_cursor(index, key), work_); }, native_);
}
StorageTable::Journal StorageTable::journal(std::shared_ptr<IndexWorkAllowance> work) {
  if (auto* table = std::get_if<ReferenceTable>(&native_)) return Journal(table->journal(), std::move(work));
  auto journal = std::get<IndexedTable>(native_).journal(work);
  return Journal(std::move(journal), std::move(work));
}

#ifdef CROWN_STORAGE_TESTING
void detail::StorageTableTesting::collisions(StorageTable& table, CollisionMode mode) {
  auto* indexed = std::get_if<IndexedTable>(&table.native_);
  if (!indexed) throw Error("storage_contract", "collision injection requires an indexed testing table");
  IndexedTesting::collisions(*indexed, mode);
}
#endif
}  // namespace crown::storage
