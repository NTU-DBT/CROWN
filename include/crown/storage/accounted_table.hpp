#pragma once

#include "crown/storage/accounted_indexed.hpp"
#include <variant>

namespace crown::storage {
namespace detail { class AccountedStorageTableTesting; }

// Native dispatch for compact values. The layout supplies the existing query
// account; dispatch owns no separate allocation or replacement work allowance.
// StorageTable is the separate standalone/tool and differential interface;
// native runtime state uses this facade and retains its original query account.
class AccountedStorageTable {
 public:
  using MemoryStatistics = std::variant<TableMemoryStatistics, AccountedIndexedMemoryStatistics>;
  class Cursor;
  struct ChangeView { bool inserted; TupleHandle handle; const AccountedTuple& tuple; };
  class Journal {
   public:
    Journal(const Journal&) = delete;
    Journal& operator=(const Journal&) = delete;
    Journal(Journal&&) noexcept = default;
    Journal& operator=(Journal&&) noexcept = default;
    ~Journal() = default;
    [[nodiscard]] bool active() const noexcept;
    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] ChangeView change(std::size_t) const &;
    ChangeView change(std::size_t) const && = delete;
    [[nodiscard]] InsertResult insert(const AccountedTuple&);
    [[nodiscard]] bool erase(TupleHandle);
    [[nodiscard]] Cursor live() const;
    [[nodiscard]] Cursor bucket_cursor(IndexId, const AccountedTuple&) const;
    void commit() noexcept;
    void rollback() noexcept;
   private:
    friend class AccountedStorageTable;
    explicit Journal(AccountedReferenceTable::Journal&&, AccountedIndexWork);
    explicit Journal(AccountedIndexedTable::Journal&&, AccountedIndexWork);
    std::variant<AccountedReferenceTable::Journal, AccountedIndexedTable::Journal> native_;
    AccountedIndexWork work_;
  };
  // Entries borrow native tuples. Ordinary indexed cursors use the caller's
  // allowance; indexed journal cursors retain and require their original grant.
  class Cursor {
   public:
    struct Entry { TupleHandle handle; const AccountedTuple& tuple; };
    Cursor(const Cursor&) = delete;
    Cursor& operator=(const Cursor&) = delete;
    Cursor(Cursor&&) noexcept = default;
    Cursor& operator=(Cursor&&) noexcept = default;
    ~Cursor() = default;
    [[nodiscard]] std::optional<TupleHandle> next(IndexWorkAllowance* = nullptr) &;
    std::optional<TupleHandle> next(IndexWorkAllowance* = nullptr) && = delete;
    [[nodiscard]] std::optional<Entry> next_entry(IndexWorkAllowance* = nullptr) &;
    std::optional<Entry> next_entry(IndexWorkAllowance* = nullptr) && = delete;
   private:
    friend class AccountedStorageTable;
    friend class Journal;
    explicit Cursor(AccountedReferenceTable::Cursor&&, AccountedIndexWork = {});
    explicit Cursor(AccountedIndexedTable::Cursor&&, AccountedIndexWork = {});
    std::variant<AccountedReferenceTable::Cursor, AccountedIndexedTable::Cursor> native_;
    AccountedIndexWork work_;
  };
  class IndexKeyCursor {
   public:
    struct Entry { const AccountedTuple& key; std::size_t degree; };
    IndexKeyCursor(const IndexKeyCursor&) = delete;
    IndexKeyCursor& operator=(const IndexKeyCursor&) = delete;
    IndexKeyCursor(IndexKeyCursor&&) noexcept = default;
    IndexKeyCursor& operator=(IndexKeyCursor&&) noexcept = default;
    ~IndexKeyCursor() = default;
    [[nodiscard]] std::optional<Entry> next(IndexWorkAllowance* = nullptr) &;
    std::optional<Entry> next(IndexWorkAllowance* = nullptr) && = delete;
   private:
    friend class AccountedStorageTable;
    explicit IndexKeyCursor(AccountedReferenceTable::IndexKeyCursor&&);
    explicit IndexKeyCursor(AccountedIndexedTable::IndexKeyCursor&&);
    std::variant<AccountedReferenceTable::IndexKeyCursor, AccountedIndexedTable::IndexKeyCursor> native_;
  };

  AccountedStorageTable(RelationId, AccountedLayout);
  AccountedStorageTable(RelationId, AccountedLayout, IndexedLimits);
  AccountedStorageTable(const AccountedStorageTable&) = delete;
  AccountedStorageTable& operator=(const AccountedStorageTable&) = delete;
  AccountedStorageTable(AccountedStorageTable&&) noexcept = default;
  AccountedStorageTable& operator=(AccountedStorageTable&&) noexcept = default;
  ~AccountedStorageTable() = default;
  [[nodiscard]] StorageBackend backend() const noexcept;
  [[nodiscard]] StorageOwnerId owner() const;
  [[nodiscard]] RelationId relation() const;
  [[nodiscard]] const AccountedLayout& layout() const &;
  const AccountedLayout& layout() const && = delete;
  [[nodiscard]] std::size_t size() const;
  [[nodiscard]] std::uint64_t revision() const;
  [[nodiscard]] ArenaStatistics arena_statistics() const;
  [[nodiscard]] std::optional<IndexedLimits> indexed_limits() const;
  [[nodiscard]] std::optional<IndexedStatistics> indexed_statistics() const;
  [[nodiscard]] MemoryStatistics memory_statistics() const;

  [[nodiscard]] InsertResult insert(const AccountedTuple&, IndexWorkAllowance* = nullptr);
  [[nodiscard]] std::optional<TupleHandle> find(const AccountedTuple&, IndexWorkAllowance* = nullptr) const;
  [[nodiscard]] const AccountedTuple* get(TupleHandle, IndexWorkAllowance* = nullptr) const &;
  const AccountedTuple* get(TupleHandle, IndexWorkAllowance* = nullptr) const && = delete;
  [[nodiscard]] AccountedTupleArena::Pin pin(TupleHandle, IndexWorkAllowance* = nullptr) const;
  [[nodiscard]] bool erase(const AccountedTuple&, IndexWorkAllowance* = nullptr);
  [[nodiscard]] bool erase(TupleHandle, IndexWorkAllowance* = nullptr);
  [[nodiscard]] IndexId add_index(AccountedProjection, IndexWorkAllowance* = nullptr);
  [[nodiscard]] bool drop_index(IndexId, IndexWorkAllowance* = nullptr);
  [[nodiscard]] AccountedVector<IndexId> indices(IndexWorkAllowance* = nullptr) const;
  [[nodiscard]] AccountedProjection projection(IndexId, IndexWorkAllowance* = nullptr) const;
  [[nodiscard]] std::size_t key_count(IndexId, IndexWorkAllowance* = nullptr) const;
  [[nodiscard]] AccountedVector<AccountedTuple> keys(IndexId, IndexWorkAllowance* = nullptr) const;
  // Materializes O(matches) handles in an accounted buffer; it pins no rows.
  [[nodiscard]] AccountedVector<TupleHandle> bucket(IndexId, const AccountedTuple&, IndexWorkAllowance* = nullptr) const;
  [[nodiscard]] std::size_t erase_key(IndexId, const AccountedTuple&, IndexWorkAllowance* = nullptr);
  void clear(IndexWorkAllowance* = nullptr);
  [[nodiscard]] AccountedVector<AccountedTuple> snapshot(IndexWorkAllowance* = nullptr) const;
  [[nodiscard]] Cursor live(IndexWorkAllowance* = nullptr) const;
  [[nodiscard]] Cursor bucket_cursor(IndexId, const AccountedTuple&, IndexWorkAllowance* = nullptr) const;
  [[nodiscard]] IndexKeyCursor index_keys(IndexId, IndexWorkAllowance* = nullptr) const;
  [[nodiscard]] AccountedStorageTable snapshot_copy(IndexWorkAllowance* = nullptr) const;
  // The optional reference grant, and required indexed grant, must belong to
  // this account. A journal cursor retains the exact original shared grant.
  [[nodiscard]] Journal journal(AccountedIndexWork = {});
  void check_invariants() const;
 private:
  friend class detail::AccountedStorageTableTesting;
  explicit AccountedStorageTable(AccountedReferenceTable&&) noexcept;
  explicit AccountedStorageTable(AccountedIndexedTable&&) noexcept;
  std::variant<AccountedReferenceTable, AccountedIndexedTable> native_;
};
}  // namespace crown::storage
