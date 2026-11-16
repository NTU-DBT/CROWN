#include "crown/storage/accounted_table.hpp"

#ifdef CROWN_ACCOUNTED_INDEXED_TESTING
#include "accounted_table_testing.hpp"
#endif
#include <utility>

namespace crown::storage {
namespace {
IndexWorkAllowance& required(IndexWorkAllowance* work) {
  if (!work) throw IndexFailure(IndexFault::contract);
  return *work;
}
IndexWorkAllowance& cursor_work(IndexWorkAllowance* requested, const AccountedIndexWork& owned) {
  if (owned && requested && owned.get() != requested) throw IndexFailure(IndexFault::contract);
  return required(requested ? requested : owned.get());
}
}  // namespace

AccountedStorageTable::AccountedStorageTable(RelationId relation, AccountedLayout layout)
    : native_(std::in_place_type<AccountedReferenceTable>, relation, std::move(layout)) {}
AccountedStorageTable::AccountedStorageTable(RelationId relation, AccountedLayout layout, IndexedLimits limits)
    : native_(std::in_place_type<AccountedIndexedTable>, relation, std::move(layout), limits) {}
AccountedStorageTable::AccountedStorageTable(AccountedReferenceTable&& table) noexcept
    : native_(std::in_place_type<AccountedReferenceTable>, std::move(table)) {}
AccountedStorageTable::AccountedStorageTable(AccountedIndexedTable&& table) noexcept
    : native_(std::in_place_type<AccountedIndexedTable>, std::move(table)) {}
StorageBackend AccountedStorageTable::backend() const noexcept {
  return native_.index() == 0 ? StorageBackend::reference_ordered_v1 : StorageBackend::indexed_chained_v1;
}
StorageOwnerId AccountedStorageTable::owner() const { return std::visit([](const auto& table) { return table.owner(); }, native_); }
RelationId AccountedStorageTable::relation() const { return std::visit([](const auto& table) { return table.relation(); }, native_); }
const AccountedLayout& AccountedStorageTable::layout() const & {
  return std::visit([](const auto& table) -> const AccountedLayout& { return table.layout(); }, native_);
}
std::size_t AccountedStorageTable::size() const { return std::visit([](const auto& table) { return table.size(); }, native_); }
std::uint64_t AccountedStorageTable::revision() const { return std::visit([](const auto& table) { return table.revision(); }, native_); }
ArenaStatistics AccountedStorageTable::arena_statistics() const {
  return std::visit([](const auto& table) { return table.arena_statistics(); }, native_);
}
std::optional<IndexedLimits> AccountedStorageTable::indexed_limits() const {
  if (const auto* table = std::get_if<AccountedIndexedTable>(&native_)) return table->limits();
  return {};
}
std::optional<IndexedStatistics> AccountedStorageTable::indexed_statistics() const {
  if (const auto* table = std::get_if<AccountedIndexedTable>(&native_)) return table->statistics();
  return {};
}
AccountedStorageTable::MemoryStatistics AccountedStorageTable::memory_statistics() const {
  return std::visit([](const auto& table) -> MemoryStatistics { return table.memory_statistics(); }, native_);
}
InsertResult AccountedStorageTable::insert(const AccountedTuple& tuple, IndexWorkAllowance* work) {
  if (auto* table = std::get_if<AccountedReferenceTable>(&native_)) return table->insert(tuple);
  return std::get<AccountedIndexedTable>(native_).insert(tuple, required(work));
}
std::optional<TupleHandle> AccountedStorageTable::find(const AccountedTuple& tuple, IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<AccountedReferenceTable>(&native_)) return table->find(tuple);
  return std::get<AccountedIndexedTable>(native_).find(tuple, required(work));
}
const AccountedTuple* AccountedStorageTable::get(TupleHandle handle, IndexWorkAllowance* work) const & {
  if (const auto* table = std::get_if<AccountedReferenceTable>(&native_)) return table->get(handle);
  return std::get<AccountedIndexedTable>(native_).get(handle, required(work));
}
AccountedTupleArena::Pin AccountedStorageTable::pin(TupleHandle handle, IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<AccountedReferenceTable>(&native_)) return table->pin(handle);
  return std::get<AccountedIndexedTable>(native_).pin(handle, required(work));
}
bool AccountedStorageTable::erase(const AccountedTuple& tuple, IndexWorkAllowance* work) {
  if (auto* table = std::get_if<AccountedReferenceTable>(&native_)) return table->erase(tuple);
  return std::get<AccountedIndexedTable>(native_).erase(tuple, required(work));
}
bool AccountedStorageTable::erase(TupleHandle handle, IndexWorkAllowance* work) {
  if (auto* table = std::get_if<AccountedReferenceTable>(&native_)) return table->erase(handle);
  return std::get<AccountedIndexedTable>(native_).erase(handle, required(work));
}
IndexId AccountedStorageTable::add_index(AccountedProjection projection, IndexWorkAllowance* work) {
  if (auto* table = std::get_if<AccountedReferenceTable>(&native_)) return table->add_index(std::move(projection));
  auto& grant = required(work);
  return std::get<AccountedIndexedTable>(native_).add_index(std::move(projection), grant);
}
bool AccountedStorageTable::drop_index(IndexId index, IndexWorkAllowance* work) {
  if (auto* table = std::get_if<AccountedReferenceTable>(&native_)) return table->drop_index(index);
  return std::get<AccountedIndexedTable>(native_).drop_index(index, required(work));
}
AccountedVector<IndexId> AccountedStorageTable::indices(IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<AccountedReferenceTable>(&native_)) return table->indices();
  return std::get<AccountedIndexedTable>(native_).indices(required(work));
}
AccountedProjection AccountedStorageTable::projection(IndexId index, IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<AccountedReferenceTable>(&native_)) return table->projection(index);
  return std::get<AccountedIndexedTable>(native_).projection(index, required(work));
}
std::size_t AccountedStorageTable::key_count(IndexId index, IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<AccountedReferenceTable>(&native_)) return table->key_count(index);
  return std::get<AccountedIndexedTable>(native_).key_count(index, required(work));
}
AccountedVector<AccountedTuple> AccountedStorageTable::keys(IndexId index, IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<AccountedReferenceTable>(&native_)) return table->keys(index);
  return std::get<AccountedIndexedTable>(native_).keys(index, required(work));
}
AccountedVector<TupleHandle> AccountedStorageTable::bucket(IndexId index, const AccountedTuple& key, IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<AccountedReferenceTable>(&native_)) return table->bucket(index, key);
  return std::get<AccountedIndexedTable>(native_).bucket(index, key, required(work));
}
std::size_t AccountedStorageTable::erase_key(IndexId index, const AccountedTuple& key, IndexWorkAllowance* work) {
  if (auto* table = std::get_if<AccountedReferenceTable>(&native_)) return table->erase_key(index, key);
  return std::get<AccountedIndexedTable>(native_).erase_key(index, key, required(work));
}
void AccountedStorageTable::clear(IndexWorkAllowance* work) {
  if (auto* table = std::get_if<AccountedReferenceTable>(&native_)) table->clear();
  else std::get<AccountedIndexedTable>(native_).clear(required(work));
}
AccountedVector<AccountedTuple> AccountedStorageTable::snapshot(IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<AccountedReferenceTable>(&native_)) return table->snapshot();
  return std::get<AccountedIndexedTable>(native_).snapshot(required(work));
}
AccountedStorageTable AccountedStorageTable::snapshot_copy(IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<AccountedReferenceTable>(&native_)) return AccountedStorageTable(table->snapshot_copy());
  return AccountedStorageTable(std::get<AccountedIndexedTable>(native_).snapshot_copy(required(work)));
}
void AccountedStorageTable::check_invariants() const {
  std::visit([](const auto& table) { table.check_invariants(); }, native_);
}

AccountedStorageTable::Cursor::Cursor(AccountedReferenceTable::Cursor&& cursor, AccountedIndexWork work)
    : native_(std::in_place_type<AccountedReferenceTable::Cursor>, std::move(cursor)), work_(std::move(work)) {}
AccountedStorageTable::Cursor::Cursor(AccountedIndexedTable::Cursor&& cursor, AccountedIndexWork work)
    : native_(std::in_place_type<AccountedIndexedTable::Cursor>, std::move(cursor)), work_(std::move(work)) {}
std::optional<TupleHandle> AccountedStorageTable::Cursor::next(IndexWorkAllowance* work) & {
  if (auto* cursor = std::get_if<AccountedReferenceTable::Cursor>(&native_)) return cursor->next();
  const auto entry = std::get<AccountedIndexedTable::Cursor>(native_).next(cursor_work(work, work_));
  if (!entry) return {};
  return entry->handle;
}
std::optional<AccountedStorageTable::Cursor::Entry> AccountedStorageTable::Cursor::next_entry(IndexWorkAllowance* work) & {
  if (auto* cursor = std::get_if<AccountedReferenceTable::Cursor>(&native_)) {
    const auto entry = cursor->next_entry();
    if (!entry) return {};
    return Entry{entry->handle, entry->tuple};
  }
  const auto entry = std::get<AccountedIndexedTable::Cursor>(native_).next(cursor_work(work, work_));
  if (!entry) return {};
  return Entry{entry->handle, entry->tuple};
}
AccountedStorageTable::Cursor AccountedStorageTable::live(IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<AccountedReferenceTable>(&native_)) return Cursor(table->live());
  return Cursor(std::get<AccountedIndexedTable>(native_).live(required(work)));
}
AccountedStorageTable::Cursor AccountedStorageTable::bucket_cursor(IndexId index, const AccountedTuple& key, IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<AccountedReferenceTable>(&native_)) return Cursor(table->bucket_cursor(index, key));
  return Cursor(std::get<AccountedIndexedTable>(native_).bucket_cursor(index, key, required(work)));
}
AccountedStorageTable::IndexKeyCursor::IndexKeyCursor(AccountedReferenceTable::IndexKeyCursor&& cursor)
    : native_(std::in_place_type<AccountedReferenceTable::IndexKeyCursor>, std::move(cursor)) {}
AccountedStorageTable::IndexKeyCursor::IndexKeyCursor(AccountedIndexedTable::IndexKeyCursor&& cursor)
    : native_(std::in_place_type<AccountedIndexedTable::IndexKeyCursor>, std::move(cursor)) {}
std::optional<AccountedStorageTable::IndexKeyCursor::Entry> AccountedStorageTable::IndexKeyCursor::next(IndexWorkAllowance* work) & {
  if (auto* cursor = std::get_if<AccountedReferenceTable::IndexKeyCursor>(&native_)) {
    const auto entry = cursor->next();
    if (!entry) return {};
    return Entry{entry->key, entry->degree};
  }
  const auto entry = std::get<AccountedIndexedTable::IndexKeyCursor>(native_).next(required(work));
  if (!entry) return {};
  return Entry{entry->key, entry->degree};
}
AccountedStorageTable::IndexKeyCursor AccountedStorageTable::index_keys(IndexId index, IndexWorkAllowance* work) const {
  if (const auto* table = std::get_if<AccountedReferenceTable>(&native_)) return IndexKeyCursor(table->index_keys(index));
  return IndexKeyCursor(std::get<AccountedIndexedTable>(native_).index_keys(index, required(work)));
}

AccountedStorageTable::Journal::Journal(AccountedReferenceTable::Journal&& journal, AccountedIndexWork work)
    : native_(std::in_place_type<AccountedReferenceTable::Journal>, std::move(journal)), work_(std::move(work)) {}
AccountedStorageTable::Journal::Journal(AccountedIndexedTable::Journal&& journal, AccountedIndexWork work)
    : native_(std::in_place_type<AccountedIndexedTable::Journal>, std::move(journal)), work_(std::move(work)) {}
bool AccountedStorageTable::Journal::active() const noexcept {
  return std::visit([](const auto& journal) { return journal.active(); }, native_);
}
std::size_t AccountedStorageTable::Journal::size() const noexcept {
  return std::visit([](const auto& journal) { return journal.size(); }, native_);
}
AccountedStorageTable::ChangeView AccountedStorageTable::Journal::change(std::size_t index) const & {
  return std::visit([&](const auto& journal) -> ChangeView {
    const auto value = journal.change(index);
    return {value.inserted, value.handle, value.tuple};
  }, native_);
}
InsertResult AccountedStorageTable::Journal::insert(const AccountedTuple& tuple) {
  return std::visit([&](auto& journal) { return journal.insert(tuple); }, native_);
}
bool AccountedStorageTable::Journal::erase(TupleHandle handle) {
  return std::visit([&](auto& journal) { return journal.erase(handle); }, native_);
}
void AccountedStorageTable::Journal::commit() noexcept {
  std::visit([](auto& journal) { journal.commit(); }, native_);
}
void AccountedStorageTable::Journal::rollback() noexcept {
  std::visit([](auto& journal) { journal.rollback(); }, native_);
}
AccountedStorageTable::Cursor AccountedStorageTable::Journal::live() const {
  return std::visit([&](const auto& journal) { return Cursor(journal.live(), work_); }, native_);
}
AccountedStorageTable::Cursor AccountedStorageTable::Journal::bucket_cursor(IndexId index, const AccountedTuple& key) const {
  return std::visit([&](const auto& journal) { return Cursor(journal.bucket_cursor(index, key), work_); }, native_);
}
AccountedStorageTable::Journal AccountedStorageTable::journal(AccountedIndexWork work) {
  if (work && !work.same_account(layout().query_account())) throw IndexFailure(IndexFault::contract);
  if (auto* table = std::get_if<AccountedReferenceTable>(&native_)) return Journal(table->journal(), std::move(work));
  auto journal = std::get<AccountedIndexedTable>(native_).journal(work);
  return Journal(std::move(journal), std::move(work));
}

#ifdef CROWN_ACCOUNTED_INDEXED_TESTING
void detail::AccountedStorageTableTesting::collisions(AccountedStorageTable& table, AccountedCollisionMode mode) {
  auto* indexed = std::get_if<AccountedIndexedTable>(&table.native_);
  if (!indexed) throw IndexFailure(IndexFault::contract);
  AccountedIndexedTesting::collisions(*indexed, mode);
}
#endif
}  // namespace crown::storage
