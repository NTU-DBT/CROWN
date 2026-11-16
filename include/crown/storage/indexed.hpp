#pragma once

#include "crown/storage/arena.hpp"
#include "crown/storage/backend.hpp"
#include "crown/storage/index_work.hpp"
#include "crown/storage/table_types.hpp"
#include <compare>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

namespace crown::storage {
namespace detail { class IndexedTesting; }

// Explicit finite component counts, not allocator-byte or peak-memory limits.
// Zero permits no corresponding objects; there is no unlimited default.

struct IndexedActions {
  std::uint64_t inserted_rows = 0;
  std::uint64_t erased_rows = 0;
  std::uint64_t added_indices = 0;
  std::uint64_t dropped_indices = 0;
  std::uint64_t clears = 0;
  auto operator<=>(const IndexedActions&) const = default;
};
// Population/action diagnostics, separate from allocator bytes or CPU time.
struct IndexedStatistics {
  std::size_t rows = 0;
  std::size_t indices = 0;
  std::size_t keys = 0;
  std::size_t live_keys = 0;
  std::size_t memberships = 0;
  std::size_t nodes = 0;
  std::size_t directory_slots = 0;
  ArenaStatistics arena;
  IndexedActions committed;
  // Initial population of a checked owning copy; never source-owner actions.
  std::size_t copied_rows = 0;
  std::size_t copied_indices = 0;
  std::size_t retained_rows = 0;
  std::size_t retained_memberships = 0;
  std::size_t journal_entries = 0;
  IndexedActions tentative;
  auto operator<=>(const IndexedStatistics&) const = default;
};

// Standalone indexed storage using public Tuple values and ordinary owners.
// Native runtime execution uses AccountedIndexedTable through its storage facade;
// this type remains a tool/test boundary and differential implementation.
// Live owning snapshots use insertion/first-live-key order, not lexical order.
class IndexedTable {
  struct State;
 public:
  class Cursor;
  class IndexKeyCursor;
  struct ChangeView { bool inserted; TupleHandle handle; const Tuple& tuple; };
  class Journal {
   public:
    Journal(const Journal&) = delete;
    Journal& operator=(const Journal&) = delete;
    Journal(Journal&&) noexcept;
    Journal& operator=(Journal&&) noexcept;
    ~Journal();
    [[nodiscard]] bool active() const noexcept;
    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] ChangeView change(std::size_t) const;
    [[nodiscard]] InsertResult insert(const Tuple&);
    [[nodiscard]] bool erase(TupleHandle);
    [[nodiscard]] Cursor live() const;
    [[nodiscard]] Cursor bucket_cursor(IndexId, const Tuple&) const;
    [[nodiscard]] IndexKeyCursor index_keys(IndexId) const;
    // Both paths consume work prepaid by each mutation, never a new grant.
    // Commit retains change-view pins until this journal is destroyed.
    void commit() noexcept;
    void rollback() noexcept;
   private:
    friend class IndexedTable;
    struct Data;
    explicit Journal(std::unique_ptr<Data>) noexcept;
    std::unique_ptr<Data> data_;
  };
  // All table journals in one composed transaction must share this exact grant.
  // Tentative reads/handles stay internal until commit. Capacity retained by a
  // successful tentative operation can survive rollback; logical state cannot.
  [[nodiscard]] Journal journal(std::shared_ptr<IndexWorkAllowance>);
  class Cursor {
   public:
    struct Entry { TupleHandle handle; const Tuple& tuple; };
    Cursor(const Cursor&) = delete;
    Cursor& operator=(const Cursor&) = delete;
    Cursor(Cursor&&) noexcept;
    Cursor& operator=(Cursor&&) noexcept;
    ~Cursor();
    // Successful next is one admitted live-link step, including end detection.
    // No hash, ID lookup, payload copy or allocation; errors may allocate their
    // exception. Journal cursors require their exact original work allowance.
    // Mutation, owner loss or journal rollback invalidates cursors and borrows,
    // including rollback of an empty journal.
    [[nodiscard]] std::optional<Entry> next(IndexWorkAllowance&);
   private:
    friend class IndexedTable;
    friend class Journal;
    struct Data;
    explicit Cursor(std::unique_ptr<Data>) noexcept;
    std::unique_ptr<Data> data_;
  };
  class IndexKeyCursor {
   public:
    struct Entry { const Tuple& key; std::size_t degree; };
    IndexKeyCursor(const IndexKeyCursor&) = delete;
    IndexKeyCursor& operator=(const IndexKeyCursor&) = delete;
    IndexKeyCursor(IndexKeyCursor&&) noexcept;
    IndexKeyCursor& operator=(IndexKeyCursor&&) noexcept;
    ~IndexKeyCursor();
    // Borrow expires on next traversal, mutation, index drop or owner loss.
    // Journal cursors require their exact original work allowance. Any journal
    // rollback, including an empty rollback, invalidates the cursor and borrow.
    [[nodiscard]] std::optional<Entry> next(IndexWorkAllowance&);
   private:
    friend class IndexedTable;
    friend class Journal;
    struct Data;
    explicit IndexKeyCursor(std::unique_ptr<Data>) noexcept;
    std::unique_ptr<Data> data_;
  };
  IndexedTable(RelationId relation, TupleLayout layout, IndexedLimits limits);
  ~IndexedTable();
  IndexedTable(const IndexedTable&) = delete;
  IndexedTable& operator=(const IndexedTable&) = delete;
  IndexedTable(IndexedTable&&) noexcept;
  IndexedTable& operator=(IndexedTable&&) noexcept;

  [[nodiscard]] StorageOwnerId owner() const;
  [[nodiscard]] RelationId relation() const;
  [[nodiscard]] const TupleLayout& layout() const;
  [[nodiscard]] const IndexedLimits& limits() const;
  [[nodiscard]] std::size_t size() const;
  [[nodiscard]] std::uint64_t revision() const;
  [[nodiscard]] IndexedStatistics statistics() const;
  [[nodiscard]] ArenaStatistics arena_statistics() const;

  [[nodiscard]] InsertResult insert(const Tuple&, IndexWorkAllowance&);
  [[nodiscard]] std::optional<TupleHandle> find(const Tuple&, IndexWorkAllowance&) const;
  [[nodiscard]] const Tuple* get(TupleHandle, IndexWorkAllowance&) const;
  [[nodiscard]] TupleArena::Pin pin(TupleHandle, IndexWorkAllowance&) const;
  [[nodiscard]] bool erase(const Tuple&, IndexWorkAllowance&);
  [[nodiscard]] bool erase(TupleHandle, IndexWorkAllowance&);
  [[nodiscard]] IndexId add_index(Projection, IndexWorkAllowance&);
  [[nodiscard]] bool drop_index(IndexId, IndexWorkAllowance&);
  [[nodiscard]] std::vector<IndexId> indices(IndexWorkAllowance&) const;
  [[nodiscard]] Projection projection(IndexId, IndexWorkAllowance&) const;
  [[nodiscard]] std::size_t key_count(IndexId, IndexWorkAllowance&) const;
  [[nodiscard]] std::vector<Tuple> keys(IndexId, IndexWorkAllowance&) const;
  [[nodiscard]] std::vector<TupleHandle> bucket(IndexId, const Tuple&, IndexWorkAllowance&) const;
  [[nodiscard]] std::size_t erase_key(IndexId, const Tuple&, IndexWorkAllowance&);
  void clear(IndexWorkAllowance&);
  [[nodiscard]] std::vector<Tuple> snapshot(IndexWorkAllowance&) const;
  [[nodiscard]] Cursor live(IndexWorkAllowance&) const;
  [[nodiscard]] Cursor bucket_cursor(IndexId, const Tuple&, IndexWorkAllowance&) const;
  [[nodiscard]] IndexKeyCursor index_keys(IndexId, IndexWorkAllowance&) const;
  // Fresh storage/arena owners, exact live sparse IDs/counters and traversal
  // order. Copies no external pins or retired allocations; rejects a journal.
  [[nodiscard]] IndexedTable snapshot_copy(IndexWorkAllowance&) const;

  // Explicit full diagnostic: may allocate and scan arena high-water state.
  // Separate from operational grants; never used to implement cursor/probe work.
  void check_invariants() const;

 private:
  friend class detail::IndexedTesting;
  explicit IndexedTable(std::shared_ptr<State>) noexcept;
  [[nodiscard]] InsertResult insert_impl(const Tuple&, IndexWorkAllowance&, Journal::Data*);
  [[nodiscard]] State& state() const;
  std::shared_ptr<State> state_;
};

}  // namespace crown::storage
