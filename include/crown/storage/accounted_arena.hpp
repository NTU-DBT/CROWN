#pragma once

#include "crown/storage/accounted_layout.hpp"
#include "crown/storage/arena.hpp"
#include <exception>
#include <memory>
#include <string_view>

namespace crown::storage {
enum class ArenaProblem { invalid_arena, invalid_pin, foreign_handle, stale_handle, layout_mismatch, invariant };
class ArenaValidationFailure final : public std::exception {
 public:
  explicit ArenaValidationFailure(ArenaProblem issue) noexcept : issue_(issue) {}
  [[nodiscard]] ArenaProblem issue() const noexcept { return issue_; }
  [[nodiscard]] std::string_view code() const noexcept;
  [[nodiscard]] const char* what() const noexcept override;
 private:
  ArenaProblem issue_;
};

// Slot/row figures contain actual request, payload and allocation counts.
// Directory spare payload is a portion of its existing allocation, not a
// second charge. Shared layout metadata and the query controller are separate
// owners in the same query account and are not counted again here.
struct ArenaMemoryStatistics {
  ArenaStatistics records;
  resource::AttributedMemoryStatistics owner;
  resource::MemoryUsage state_control;
  resource::MemoryUsage directory;
  resource::MemoryUsage live_slots, retained_slots, free_slots, exhausted_slots;
  resource::MemoryUsage live_values, retained_values;
  std::size_t directory_capacity = 0;
  std::uint64_t directory_spare_payload_bytes = 0;
  auto operator<=>(const ArenaMemoryStatistics&) const = default;
};

class AccountedReferenceTable;
class AccountedIndexedTable;
// Native arena with stable owner/slot/generation handles. Layout metadata,
// State/control block, slot objects,
// directory capacity and deep row payloads all retain one existing account.
// This component follows the same single-mutating-thread contract as it.
class AccountedTupleArena {
  struct State;
 public:
  class Pin {
   public:
    Pin(const Pin&) = delete;
    Pin& operator=(const Pin&) = delete;
    Pin(Pin&&) noexcept;
    Pin& operator=(Pin&&) noexcept;
    ~Pin();
    [[nodiscard]] ArenaHandle handle() const;
    [[nodiscard]] const AccountedTuple& get() const &;
    const AccountedTuple& get() const && = delete;
    [[nodiscard]] bool is_live() const;
    void reset() noexcept;
   private:
    friend class AccountedTupleArena;
    Pin(std::shared_ptr<State>, ArenaHandle) noexcept;
    std::shared_ptr<State> state_;
    ArenaHandle handle_{};
  };

  explicit AccountedTupleArena(AccountedLayout);
  ~AccountedTupleArena();
  AccountedTupleArena(const AccountedTupleArena&) = delete;
  AccountedTupleArena& operator=(const AccountedTupleArena&) = delete;
  AccountedTupleArena(AccountedTupleArena&&) noexcept;
  AccountedTupleArena& operator=(AccountedTupleArena&&) noexcept;
  [[nodiscard]] ArenaOwnerId owner() const;
  [[nodiscard]] resource::MemoryAttribution attribution() const;
  [[nodiscard]] const AccountedLayout& layout() const &;
  const AccountedLayout& layout() const && = delete;
  [[nodiscard]] ArenaStatistics statistics() const;
  [[nodiscard]] ArenaMemoryStatistics memory_statistics() const;
  [[nodiscard]] resource::MemoryStatistics account_statistics() const;
  [[nodiscard]] ArenaHandle insert(const AccountedTuple&);
  [[nodiscard]] bool contains(ArenaHandle) const;
  [[nodiscard]] const AccountedTuple& get(ArenaHandle) const &;
  const AccountedTuple& get(ArenaHandle) const && = delete;
  [[nodiscard]] Pin pin(ArenaHandle) const;
  [[nodiscard]] bool erase(ArenaHandle);
  void clear();
  // Explicit whole-arena diagnostic; bounded storage and no allocations.
  void check_invariants() const;
 private:
  friend class AccountedReferenceTable;
  friend class AccountedIndexedTable;
  [[nodiscard]] State& state() const;
  static void classify(AccountedTuple&, resource::AllocationLifetime) noexcept;
  // Owner-only undo restores a retained slot at its original generation.
  void revive(const Pin&) noexcept;
  std::shared_ptr<State> state_;
};
}
