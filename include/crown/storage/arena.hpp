#pragma once

#include "crown/storage/layout.hpp"
#include <memory>

namespace crown::storage {
class ReferenceTable;
class IndexedTable;
// Counts records/slots, not allocator bytes. Free slots retain metadata only;
// payloads (including owned strings) are destroyed as soon as no pin needs them.
struct ArenaStatistics {
  std::size_t slots = 0;
  std::size_t live_records = 0;
  std::size_t retained_records = 0;  // Erased records with one or more pins.
  std::size_t pins = 0;              // Pin objects, including pins on live rows.
  std::size_t free_slots = 0;
  std::size_t exhausted_slots = 0;   // Generation cannot advance without wrap.
  auto operator<=>(const ArenaStatistics&) const = default;
};

// Single-threaded, noncopyable tuple owner. Allocation returns a stable slot
// and generation; erase/clear invalidate ordinary handles immediately.
class TupleArena {
  struct State;
 public:
  class Pin {
   public:
    Pin(const Pin&) = delete;
    Pin& operator=(const Pin&) = delete;
    Pin(Pin&&) noexcept;
    Pin& operator=(Pin&& other) noexcept;
    ~Pin();
    [[nodiscard]] ArenaHandle handle() const;
    [[nodiscard]] const Tuple& get() const;
    [[nodiscard]] bool is_live() const;
    // Releases retention without allocating. A reset/moved-from pin is empty;
    // its other accessors reject with invalid_pin.
    // Last retained release can destroy the payload and, after owner loss,
    // all high-water slot metadata; only pin bookkeeping is constant work.
    void reset() noexcept;
   private:
    friend class TupleArena;
    Pin(std::shared_ptr<State> state, ArenaHandle handle) noexcept;
    std::shared_ptr<State> state_;
    ArenaHandle handle_{};
  };

  explicit TupleArena(TupleLayout layout);
  ~TupleArena();
  TupleArena(const TupleArena&) = delete;
  TupleArena& operator=(const TupleArena&) = delete;
  TupleArena(TupleArena&&) noexcept;
  TupleArena& operator=(TupleArena&& other) noexcept;
  [[nodiscard]] ArenaOwnerId owner() const;
  [[nodiscard]] const TupleLayout& layout() const;
  [[nodiscard]] ArenaStatistics statistics() const;
  // Failed allocation leaves every published slot, generation and counter
  // unchanged. Reusing a free slot advances its generation after value copy.
  [[nodiscard]] ArenaHandle insert(const Tuple& tuple);
  [[nodiscard]] bool contains(ArenaHandle handle) const;
  // Stale handles throw stale_handle in all builds; foreign owners throw
  // foreign_handle. Borrowed address stays stable until erase/clear/destruction.
  [[nodiscard]] const Tuple& get(ArenaHandle handle) const;
  [[nodiscard]] Pin pin(ArenaHandle handle) const;
  [[nodiscard]] bool erase(ArenaHandle handle);
  void clear();
  void check_invariants() const;
 private:
  friend class ReferenceTable;
  friend class IndexedTable;
  // Undo only: a retained allocation is restored with its original generation.
  // Never exposed as a way to resurrect a stale public handle.
  void revive(const Pin& pin) noexcept;
  [[nodiscard]] State& state() const;
  std::shared_ptr<State> state_;
};
// A pin retains its immutable payload across erase, clear, owner replacement or
// destruction. Retired slots cannot be reused until their last pin is released.
// After owner destruction, only pinned payloads and slot metadata remain; the
// metadata is freed with the last pin. Pins do not preserve membership/cursors.
}  // namespace crown::storage
