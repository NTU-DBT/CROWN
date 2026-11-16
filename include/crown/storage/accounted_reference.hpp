#pragma once

#include "crown/storage/accounted_arena.hpp"
#include "crown/storage/accounted_projection.hpp"
#include "crown/storage/table_types.hpp"
#include "crown/resource/ownership.hpp"
#include <vector>

namespace crown::storage {
enum class TableProblem { invalid_table, invalid_journal, invalid_cursor, foreign_handle,
  stale_handle, layout_mismatch, unknown_index, busy, invariant };
class TableValidationFailure final : public std::exception {
 public:
  explicit TableValidationFailure(TableProblem problem) noexcept : problem_(problem) {}
  [[nodiscard]] std::string_view code() const noexcept;
  [[nodiscard]] const char* what() const noexcept override;
 private:
  TableProblem problem_;
};
template<class T> using AccountedVector = std::vector<T, resource::MemoryAllocator<T>>;
struct TableMemoryStatistics {
  std::size_t live_records = 0, indices = 0, secondary_keys = 0, memberships = 0;
  std::size_t active_undo_entries = 0, retained_undo_entries = 0;
  resource::AttributedMemoryStatistics table;
  ArenaMemoryStatistics arena;
  resource::MemoryUsage owned; // Table + arena, shared metadata counted separately.
  auto operator<=>(const TableMemoryStatistics&) const = default;
};

// Native ordered reference backend. All owned containers, deep keys, state,
// cursors, journals and returned collections use the layout's existing account.
// Retain this simple backend for semantic comparison with native indexed storage;
// the unaccounted ReferenceTable also serves standalone compiler/tool callers.
class AccountedReferenceTable {
  struct State;
 public:
  class Cursor;
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
    // List-backed O(index) access. The pin-backed tuple survives commit while
    // this journal lives; rollback/destruction releases its borrowed reference.
    [[nodiscard]] ChangeView change(std::size_t) const &;
    ChangeView change(std::size_t) const && = delete;
    [[nodiscard]] InsertResult insert(const AccountedTuple&);
    [[nodiscard]] bool erase(TupleHandle);
    [[nodiscard]] Cursor live() const;
    [[nodiscard]] Cursor bucket_cursor(IndexId, const AccountedTuple&) const;
    void commit() noexcept;
    void rollback() noexcept;
   private:
    friend class AccountedReferenceTable;
    struct Data;
    explicit Journal(resource::AccountedUnique<Data>) noexcept;
    resource::AccountedUnique<Data> data_;
  };
  // Low-level cursors borrow weak table ownership and check revisions. Runtime
  // result/view cursors separately retain the strong owner and reader lease.
  class Cursor {
   public:
    struct Entry { TupleHandle handle; const AccountedTuple& tuple; };
    Cursor(const Cursor&) = delete;
    Cursor& operator=(const Cursor&) = delete;
    Cursor(Cursor&&) noexcept;
    Cursor& operator=(Cursor&&) noexcept;
    ~Cursor();
    [[nodiscard]] std::optional<TupleHandle> next();
    [[nodiscard]] std::optional<Entry> next_entry() &;
    std::optional<Entry> next_entry() && = delete;
   private:
    friend class AccountedReferenceTable;
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
    [[nodiscard]] std::optional<Entry> next() &;
    std::optional<Entry> next() && = delete;
   private:
    friend class AccountedReferenceTable;
    struct Data;
    explicit IndexKeyCursor(resource::AccountedUnique<Data>) noexcept;
    resource::AccountedUnique<Data> data_;
  };
  AccountedReferenceTable(RelationId, AccountedLayout);
  ~AccountedReferenceTable();
  AccountedReferenceTable(const AccountedReferenceTable&) = delete;
  AccountedReferenceTable& operator=(const AccountedReferenceTable&) = delete;
  AccountedReferenceTable(AccountedReferenceTable&&) noexcept;
  AccountedReferenceTable& operator=(AccountedReferenceTable&&) noexcept;
  [[nodiscard]] StorageOwnerId owner() const;
  [[nodiscard]] RelationId relation() const;
  [[nodiscard]] const AccountedLayout& layout() const &;
  const AccountedLayout& layout() const && = delete;
  [[nodiscard]] std::size_t size() const;
  [[nodiscard]] std::uint64_t revision() const;
  [[nodiscard]] resource::MemoryAttribution attribution() const;
  [[nodiscard]] ArenaStatistics arena_statistics() const;
  [[nodiscard]] TableMemoryStatistics memory_statistics() const;
  [[nodiscard]] InsertResult insert(const AccountedTuple&);
  [[nodiscard]] std::optional<TupleHandle> find(const AccountedTuple&) const;
  [[nodiscard]] const AccountedTuple* get(TupleHandle) const &;
  const AccountedTuple* get(TupleHandle) const && = delete;
  [[nodiscard]] AccountedTupleArena::Pin pin(TupleHandle) const;
  [[nodiscard]] bool erase(TupleHandle);
  [[nodiscard]] bool erase(const AccountedTuple&);
  [[nodiscard]] IndexId add_index(AccountedProjection);
  [[nodiscard]] bool drop_index(IndexId);
  [[nodiscard]] AccountedVector<IndexId> indices() const;
  [[nodiscard]] AccountedProjection projection(IndexId) const;
  [[nodiscard]] std::size_t key_count(IndexId) const;
  [[nodiscard]] AccountedVector<AccountedTuple> keys(IndexId) const;
  [[nodiscard]] AccountedVector<TupleHandle> bucket(IndexId, const AccountedTuple&) const;
  [[nodiscard]] std::size_t erase_key(IndexId, const AccountedTuple&);
  void clear();
  [[nodiscard]] Cursor live() const;
  [[nodiscard]] Cursor bucket_cursor(IndexId, const AccountedTuple&) const;
  [[nodiscard]] IndexKeyCursor index_keys(IndexId) const;
  [[nodiscard]] Journal journal();
  [[nodiscard]] AccountedVector<AccountedTuple> snapshot() const;
  [[nodiscard]] AccountedReferenceTable snapshot_copy() const;
  void check_invariants() const;
 private:
  [[nodiscard]] State& state() const;
  static resource::MemoryAccount account_for(const AccountedLayout&);
  static void classify(AccountedTuple&, resource::AllocationLifetime) noexcept;
  static void revive(AccountedTupleArena&, const AccountedTupleArena::Pin&) noexcept;
  explicit AccountedReferenceTable(std::shared_ptr<State>) noexcept;
  std::shared_ptr<State> state_;
};
}
