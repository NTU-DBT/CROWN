#pragma once

#include "crown/storage/indexed.hpp"
#include "crown/storage/reference.hpp"
#include <variant>

namespace crown::storage {
namespace detail { class StorageTableTesting; }

// Internal backend dispatch. The two-argument constructor preserves S02;
// the explicit IndexedLimits overload selects the indexed backend permanently.
// Indexed ordinary operations require a finite caller-owned borrowed grant.
// Reference operations retain their existing admission/ordering contract.
// Dispatch adds no heap allocation, traversal or replacement work allowance.
class StorageTable {
 public:
  class Cursor;
  struct ChangeView { bool inserted; TupleHandle handle; const Tuple& tuple; };
  // Concrete journals retain their own inverse/change pins; dispatch only
  // retains the same shared work grant and introduces no second mutation log.
  class Journal {
   public:
    Journal(const Journal&) = delete;
    Journal& operator=(const Journal&) = delete;
    Journal(Journal&&) noexcept = default;
    Journal& operator=(Journal&&) noexcept = default;
    ~Journal() = default;
    [[nodiscard]] bool active() const noexcept;
    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] ChangeView change(std::size_t) const;
    [[nodiscard]] InsertResult insert(const Tuple&);
    [[nodiscard]] bool erase(TupleHandle);
    [[nodiscard]] Cursor live() const;
    [[nodiscard]] Cursor bucket_cursor(IndexId, const Tuple&) const;
    void commit() noexcept;
    void rollback() noexcept;
   private:
    friend class StorageTable;
    explicit Journal(ReferenceTable::Journal&&, std::shared_ptr<IndexWorkAllowance>);
    explicit Journal(IndexedTable::Journal&&, std::shared_ptr<IndexWorkAllowance>);
    std::variant<ReferenceTable::Journal, IndexedTable::Journal> native_;
    std::shared_ptr<IndexWorkAllowance> work_;
  };
  class Cursor {
   public:
    struct Entry { TupleHandle handle; const Tuple& tuple; };
    Cursor(const Cursor&) = delete;
    Cursor& operator=(const Cursor&) = delete;
    Cursor(Cursor&&) noexcept = default;
    Cursor& operator=(Cursor&&) noexcept = default;
    ~Cursor() = default;
    // Keep the reference bucket-handle next O(1). Borrowed reference bucket
    // entries additionally resolve the ordered ID map. Indexed entries use a
    // direct admitted live-link step; neither path copies or pins a payload.
    [[nodiscard]] std::optional<TupleHandle> next(IndexWorkAllowance* = nullptr);
    [[nodiscard]] std::optional<Entry> next_entry(IndexWorkAllowance* = nullptr);
   private:
    friend class StorageTable;
    friend class Journal;
    explicit Cursor(ReferenceTable::Cursor&&, std::shared_ptr<IndexWorkAllowance> = {});
    explicit Cursor(IndexedTable::Cursor&&, std::shared_ptr<IndexWorkAllowance> = {});
    std::variant<ReferenceTable::Cursor, IndexedTable::Cursor> native_;
    // Only journal cursors retain a grant. Ordinary calls borrow synchronously.
    std::shared_ptr<IndexWorkAllowance> work_;
  };
  class IndexKeyCursor {
   public:
    struct Entry { const Tuple& key; std::size_t degree; };
    IndexKeyCursor(const IndexKeyCursor&) = delete;
    IndexKeyCursor& operator=(const IndexKeyCursor&) = delete;
    IndexKeyCursor(IndexKeyCursor&&) noexcept = default;
    IndexKeyCursor& operator=(IndexKeyCursor&&) noexcept = default;
    ~IndexKeyCursor() = default;
    [[nodiscard]] std::optional<Entry> next(IndexWorkAllowance* = nullptr);
   private:
    friend class StorageTable;
    explicit IndexKeyCursor(ReferenceTable::IndexKeyCursor&&);
    explicit IndexKeyCursor(IndexedTable::IndexKeyCursor&&);
    std::variant<ReferenceTable::IndexKeyCursor, IndexedTable::IndexKeyCursor> native_;
  };

  StorageTable(RelationId, TupleLayout);
  StorageTable(RelationId, TupleLayout, IndexedLimits);
  StorageTable(const StorageTable&) = delete;
  StorageTable& operator=(const StorageTable&) = delete;
  StorageTable(StorageTable&&) noexcept = default;
  StorageTable& operator=(StorageTable&&) noexcept = default;
  ~StorageTable() = default;
  [[nodiscard]] StorageBackend backend() const noexcept;
  [[nodiscard]] StorageOwnerId owner() const;
  [[nodiscard]] RelationId relation() const;
  [[nodiscard]] const TupleLayout& layout() const;
  [[nodiscard]] std::size_t size() const;
  [[nodiscard]] std::uint64_t revision() const;
  [[nodiscard]] ArenaStatistics arena_statistics() const;
  [[nodiscard]] std::optional<IndexedLimits> indexed_limits() const;
  [[nodiscard]] std::optional<IndexedStatistics> indexed_statistics() const;

  [[nodiscard]] InsertResult insert(const Tuple&, IndexWorkAllowance* = nullptr);
  [[nodiscard]] std::optional<TupleHandle> find(const Tuple&, IndexWorkAllowance* = nullptr) const;
  [[nodiscard]] const Tuple* get(TupleHandle, IndexWorkAllowance* = nullptr) const;
  [[nodiscard]] TupleArena::Pin pin(TupleHandle, IndexWorkAllowance* = nullptr) const;
  [[nodiscard]] bool erase(const Tuple&, IndexWorkAllowance* = nullptr);
  [[nodiscard]] bool erase(TupleHandle, IndexWorkAllowance* = nullptr);
  [[nodiscard]] IndexId add_index(Projection, IndexWorkAllowance* = nullptr);
  [[nodiscard]] bool drop_index(IndexId, IndexWorkAllowance* = nullptr);
  [[nodiscard]] std::vector<IndexId> indices(IndexWorkAllowance* = nullptr) const;
  [[nodiscard]] Projection projection(IndexId, IndexWorkAllowance* = nullptr) const;
  [[nodiscard]] std::size_t key_count(IndexId, IndexWorkAllowance* = nullptr) const;
  [[nodiscard]] std::vector<Tuple> keys(IndexId, IndexWorkAllowance* = nullptr) const;
  [[nodiscard]] std::vector<TupleHandle> bucket(IndexId, const Tuple&, IndexWorkAllowance* = nullptr) const;
  [[nodiscard]] std::size_t erase_key(IndexId, const Tuple&, IndexWorkAllowance* = nullptr);
  void clear(IndexWorkAllowance* = nullptr);
  [[nodiscard]] std::vector<Tuple> snapshot(IndexWorkAllowance* = nullptr) const;
  [[nodiscard]] Cursor live(IndexWorkAllowance* = nullptr) const;
  [[nodiscard]] Cursor bucket_cursor(IndexId, const Tuple&, IndexWorkAllowance* = nullptr) const;
  [[nodiscard]] IndexKeyCursor index_keys(IndexId, IndexWorkAllowance* = nullptr) const;
  [[nodiscard]] StorageTable snapshot_copy(IndexWorkAllowance* = nullptr) const;
  // An indexed journal requires a nonnull shared grant. All tables of a
  // composed transaction receive the same object, never separate budgets.
  [[nodiscard]] Journal journal(std::shared_ptr<IndexWorkAllowance> = {});
  void check_invariants() const;
 private:
  friend class detail::StorageTableTesting;
  explicit StorageTable(ReferenceTable&&) noexcept;
  explicit StorageTable(IndexedTable&&) noexcept;
  std::variant<ReferenceTable, IndexedTable> native_;
};
}  // namespace crown::storage
