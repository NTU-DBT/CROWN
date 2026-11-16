#pragma once

#include "crown/storage/indexed.hpp"
#include "crown/storage/accounted_reference.hpp"
#include "crown/storage/accounted_index_work.hpp"

namespace crown::storage {
namespace detail { class AccountedIndexedTesting; }
struct AccountedIndexedMemoryStatistics {
  IndexedStatistics records;
  resource::AttributedMemoryStatistics table;
  ArenaMemoryStatistics arena;
  resource::MemoryUsage directories;
  resource::MemoryUsage owned;
  std::size_t retained_history_entries = 0;
  auto operator<=>(const AccountedIndexedMemoryStatistics&) const = default;
};
// Native indexed backend selected by AccountedStorageTable. Every node,
// capacity allocation, deep value and control uses the layout's existing account.
// Prepare growth/undo under the shared operation grant before pointer publication.
// Usage and costs: docs/code_specs/primitives.md#hash-directory-and-live-list.
class AccountedIndexedTable {
  struct State;
 public:
  class Cursor;
  class IndexKeyCursor;
  struct ChangeView { bool inserted; TupleHandle handle; const AccountedTuple& tuple; };
  class Journal {
   public:
    Journal(const Journal&) = delete;
    Journal& operator=(const Journal&) = delete;
    Journal(Journal&&) noexcept;
    Journal& operator=(Journal&&) noexcept;
    ~Journal();
    [[nodiscard]] bool active() const noexcept;
    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] ChangeView change(std::size_t) const &;
    ChangeView change(std::size_t) const && = delete;
    [[nodiscard]] InsertResult insert(const AccountedTuple&);
    [[nodiscard]] bool erase(TupleHandle);
    [[nodiscard]] Cursor live() const;
    [[nodiscard]] Cursor bucket_cursor(IndexId, const AccountedTuple&) const;
    [[nodiscard]] IndexKeyCursor index_keys(IndexId) const;
    // Both paths consume work prepaid by each mutation, never a new grant.
    // Commit retains change-view pins until this journal is destroyed.
    void commit() noexcept;
    void rollback() noexcept;
   private:
    friend class AccountedIndexedTable;
    struct Data;
    explicit Journal(resource::AccountedUnique<Data>) noexcept;
    resource::AccountedUnique<Data> data_;
  };
  // All table journals in one composed transaction must share this exact grant.
  // Tentative reads/handles stay internal until commit. Capacity retained by a
  // successful tentative operation can survive rollback; logical state cannot.
  [[nodiscard]] Journal journal(AccountedIndexWork);
  class Cursor {
   public:
    struct Entry { TupleHandle handle; const AccountedTuple& tuple; };
    Cursor(const Cursor&) = delete;
    Cursor& operator=(const Cursor&) = delete;
    Cursor(Cursor&&) noexcept;
    Cursor& operator=(Cursor&&) noexcept;
    ~Cursor();
    // Successful next is one admitted live-link step, including end detection.
    // No hash, ID lookup or payload copy. Fixed diagnostics require no
    // ordinary-new allocation. Mutation, owner loss or journal rollback
    // invalidates cursors and borrows, including rollback of an empty journal.
    // This low-level cursor has weak table ownership. Journal cursors require
    // their exact original grant; repeated end calls still debit a native step.
    [[nodiscard]] std::optional<Entry> next(IndexWorkAllowance&) &;
    std::optional<Entry> next(IndexWorkAllowance&) && = delete;
   private:
    friend class AccountedIndexedTable;
    friend class Journal;
    struct Data;
    explicit Cursor(resource::AccountedUnique<Data>) noexcept;
    resource::AccountedUnique<Data> data_;
  };
  class IndexKeyCursor {
   public:
    struct Entry { const AccountedTuple& key; std::size_t degree; };
    IndexKeyCursor(const IndexKeyCursor&) = delete;
    IndexKeyCursor& operator=(const IndexKeyCursor&) = delete;
    IndexKeyCursor(IndexKeyCursor&&) noexcept;
    IndexKeyCursor& operator=(IndexKeyCursor&&) noexcept;
    ~IndexKeyCursor();
    // Borrow expires on next traversal, mutation, index drop or owner loss.
    // Journal cursors require their exact original work allowance. Any journal
    // rollback, including an empty rollback, invalidates the cursor and borrow.
    [[nodiscard]] std::optional<Entry> next(IndexWorkAllowance&) &;
    std::optional<Entry> next(IndexWorkAllowance&) && = delete;
   private:
    friend class AccountedIndexedTable;
    friend class Journal;
    struct Data;
    explicit IndexKeyCursor(resource::AccountedUnique<Data>) noexcept;
    resource::AccountedUnique<Data> data_;
  };
  AccountedIndexedTable(RelationId relation, AccountedLayout layout, IndexedLimits limits);
  ~AccountedIndexedTable();
  AccountedIndexedTable(const AccountedIndexedTable&) = delete;
  AccountedIndexedTable& operator=(const AccountedIndexedTable&) = delete;
  AccountedIndexedTable(AccountedIndexedTable&&) noexcept;
  AccountedIndexedTable& operator=(AccountedIndexedTable&&) noexcept;

  [[nodiscard]] StorageOwnerId owner() const;
  [[nodiscard]] RelationId relation() const;
  [[nodiscard]] const AccountedLayout& layout() const &;
  const AccountedLayout& layout() const && = delete;
  [[nodiscard]] const IndexedLimits& limits() const &;
  const IndexedLimits& limits() const && = delete;
  [[nodiscard]] std::size_t size() const;
  [[nodiscard]] std::uint64_t revision() const;
  [[nodiscard]] IndexedStatistics statistics() const;
  [[nodiscard]] ArenaStatistics arena_statistics() const;
  [[nodiscard]] AccountedIndexedMemoryStatistics memory_statistics() const;

  [[nodiscard]] InsertResult insert(const AccountedTuple&, IndexWorkAllowance&);
  [[nodiscard]] std::optional<TupleHandle> find(const AccountedTuple&, IndexWorkAllowance&) const;
  [[nodiscard]] const AccountedTuple* get(TupleHandle, IndexWorkAllowance&) const &;
  const AccountedTuple* get(TupleHandle, IndexWorkAllowance&) const && = delete;
  [[nodiscard]] AccountedTupleArena::Pin pin(TupleHandle, IndexWorkAllowance&) const;
  [[nodiscard]] bool erase(const AccountedTuple&, IndexWorkAllowance&);
  [[nodiscard]] bool erase(TupleHandle, IndexWorkAllowance&);
  [[nodiscard]] IndexId add_index(AccountedProjection, IndexWorkAllowance&);
  [[nodiscard]] bool drop_index(IndexId, IndexWorkAllowance&);
  [[nodiscard]] AccountedVector<IndexId> indices(IndexWorkAllowance&) const;
  [[nodiscard]] AccountedProjection projection(IndexId, IndexWorkAllowance&) const;
  [[nodiscard]] std::size_t key_count(IndexId, IndexWorkAllowance&) const;
  [[nodiscard]] AccountedVector<AccountedTuple> keys(IndexId, IndexWorkAllowance&) const;
  [[nodiscard]] AccountedVector<TupleHandle> bucket(IndexId, const AccountedTuple&, IndexWorkAllowance&) const;
  [[nodiscard]] std::size_t erase_key(IndexId, const AccountedTuple&, IndexWorkAllowance&);
  void clear(IndexWorkAllowance&);
  [[nodiscard]] AccountedVector<AccountedTuple> snapshot(IndexWorkAllowance&) const;
  [[nodiscard]] Cursor live(IndexWorkAllowance&) const;
  [[nodiscard]] Cursor bucket_cursor(IndexId, const AccountedTuple&, IndexWorkAllowance&) const;
  [[nodiscard]] IndexKeyCursor index_keys(IndexId, IndexWorkAllowance&) const;
  // Fresh storage/arena owners; preserve live sparse IDs, high-water counters,
  // revision and traversal order. Action history resets to the copied baseline.
  // Copies no external pins or retired allocations; rejects an active journal.
  [[nodiscard]] AccountedIndexedTable snapshot_copy(IndexWorkAllowance&) const;

  // Explicit nonallocating diagnostic: scans capacity/arena high-water and
  // includes collision-heavy, row/key and active-journal cross-checks that can
  // be quadratic or population cross-products. Separate from operational grants;
  // never used to implement cursor/probe work.
  void check_invariants() const;

 private:
  friend class detail::AccountedIndexedTesting;
  [[nodiscard]] static InsertResult insert_impl(const std::shared_ptr<State>&, const AccountedTuple&, IndexWorkAllowance&, Journal::Data*);
  static resource::MemoryAccount account_for(const AccountedLayout&);
  static void classify(AccountedTuple&, resource::AllocationLifetime) noexcept;
  [[nodiscard]] State& state() const;
  std::shared_ptr<State> state_;
};

}  // namespace crown::storage
