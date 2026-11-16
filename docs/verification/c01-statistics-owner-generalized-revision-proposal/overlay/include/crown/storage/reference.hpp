#pragma once

#include "crown/storage/arena.hpp"
#include <memory>

namespace crown::storage {
class ReferencePlanStorage;
struct InsertResult { bool inserted; TupleHandle handle; };

// Standard-container storage for one logical relation. Owning/noncopyable,
// movable; tuple/index IDs are never reused within its unique storage owner.
class ReferenceTable {
  struct State;
 public:
  class Cursor;
  struct ChangeView { bool inserted; TupleHandle handle; const Tuple& tuple; };
  // Exclusive, single-writer mutation scope. Tentative handles/reads must stay
  // internal until commit. Destruction rolls back in reverse order without
  // allocating. Commit retains affected payloads until this journal is freed.
  class Journal {
   public:
    Journal(const Journal&) = delete;
    Journal& operator=(const Journal&) = delete;
    Journal(Journal&&) noexcept;
    Journal& operator=(Journal&&) noexcept;
    ~Journal();
    [[nodiscard]] InsertResult insert(const Tuple& tuple);
    [[nodiscard]] bool erase(TupleHandle handle);
    [[nodiscard]] bool active() const noexcept;
    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] ChangeView change(std::size_t index) const;
    // Owner-only tentative reads. Further real mutation invalidates them;
    // commit preserves them, rollback invalidates before inverse operations.
    [[nodiscard]] Cursor live() const;
    [[nodiscard]] Cursor bucket_cursor(IndexId index, const Tuple& key) const;
    void commit() noexcept;
    void rollback() noexcept;
   private:
    friend class ReferenceTable;
    struct Data;
    explicit Journal(std::unique_ptr<Data> data) noexcept;
    std::unique_ptr<Data> data_;
  };
  [[nodiscard]] Journal journal();
  class Cursor {
   public:
    Cursor(Cursor&&) noexcept;
    Cursor& operator=(Cursor&&) noexcept;
    ~Cursor();
    Cursor(const Cursor&) = delete;
    Cursor& operator=(const Cursor&) = delete;
    // Visits live handles only. Real mutation/owner destruction invalidates
    // the cursor; duplicate/absent no-ops leave it usable. No record pinning.
    [[nodiscard]] std::optional<TupleHandle> next();
   private:
    friend class ReferenceTable;
    friend class Journal;
    struct Data;
    explicit Cursor(std::unique_ptr<Data> data);
    std::unique_ptr<Data> data_;
  };
  class IndexKeyCursor {
   public:
    struct Entry { const Tuple& key; std::size_t degree; };
    IndexKeyCursor(IndexKeyCursor&&) noexcept;
    IndexKeyCursor& operator=(IndexKeyCursor&&) noexcept;
    ~IndexKeyCursor();
    IndexKeyCursor(const IndexKeyCursor&) = delete;
    IndexKeyCursor& operator=(const IndexKeyCursor&) = delete;
    // Borrow expires on mutation, destruction, or next traversal. No pins.
    [[nodiscard]] std::optional<Entry> next();
   private:
    friend class ReferenceTable;
    struct Data;
    explicit IndexKeyCursor(std::unique_ptr<Data>);
    std::unique_ptr<Data> data_;
  };
  [[nodiscard]] IndexKeyCursor index_keys(IndexId index) const;
  ReferenceTable(RelationId relation, TupleLayout layout);
  ~ReferenceTable();
  ReferenceTable(ReferenceTable&&) noexcept;
  ReferenceTable& operator=(ReferenceTable&&) noexcept;
  ReferenceTable(const ReferenceTable&) = delete;
  ReferenceTable& operator=(const ReferenceTable&) = delete;

  [[nodiscard]] StorageOwnerId owner() const;
  [[nodiscard]] RelationId relation() const;
  [[nodiscard]] const TupleLayout& layout() const;
  [[nodiscard]] std::size_t size() const;
  [[nodiscard]] std::uint64_t revision() const;
  [[nodiscard]] InsertResult insert(const Tuple& tuple);
  [[nodiscard]] std::optional<TupleHandle> find(const Tuple& tuple) const;
  [[nodiscard]] const Tuple* get(TupleHandle handle) const;  // Borrowed until erase/clear/destruction.
  // Retains immutable payload across erase/clear/table destruction. Membership
  // still disappears immediately; a pin does not keep the row in any index.
  [[nodiscard]] TupleArena::Pin pin(TupleHandle handle) const;
  [[nodiscard]] ArenaStatistics arena_statistics() const;
  [[nodiscard]] bool erase(const Tuple& tuple);
  [[nodiscard]] bool erase(TupleHandle handle);
  // Same immutable program registration is idempotent; independent programs
  // can coexist even when they select identical fields.
  [[nodiscard]] IndexId add_index(Projection projection);
  [[nodiscard]] bool drop_index(IndexId index);
  [[nodiscard]] std::vector<IndexId> indices() const;
  [[nodiscard]] Projection projection(IndexId index) const;
  [[nodiscard]] std::size_t key_count(IndexId index) const;
  [[nodiscard]] std::vector<Tuple> keys(IndexId index) const;
  [[nodiscard]] std::vector<TupleHandle> bucket(IndexId index, const Tuple& key) const;
  [[nodiscard]] std::size_t erase_key(IndexId index, const Tuple& key);
  void clear();
  [[nodiscard]] Cursor live() const;
  [[nodiscard]] Cursor bucket_cursor(IndexId index, const Tuple& key) const;
  [[nodiscard]] std::vector<Tuple> snapshot() const;
  void check_invariants() const;
 private:
  friend class ReferencePlanStorage;
  // Independent owning copy with fresh backend owner, identical tuple/index
  // IDs/counters and rebound internal iterators. Used by reference transactions.
  [[nodiscard]] ReferenceTable snapshot_copy() const;
  explicit ReferenceTable(std::shared_ptr<State> state);
  [[nodiscard]] State& state() const;
  std::shared_ptr<State> state_;
};
}  // namespace crown::storage
