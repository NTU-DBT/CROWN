#pragma once

// Isolated design proposal. Not part of crown_core; P07 remains not_started.
#include "../p07-generator-proposal/machine.hpp"

#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

namespace crown::planner::alternatives_proposal {

enum class KeyEvent { advanced, key_ready, stopped };
enum class KeyStop {
  none,
  depth_limit,
  record_limit,
  cell_limit,
  counter_overflow,
  cancelled,
  invalid_input,
};
struct KeyStep {
  KeyEvent event = KeyEvent::advanced;
  KeyStop reason = KeyStop::none;
  std::size_t requested_depth = 0;
};
struct KeyStatistics {
  std::uint64_t completed_steps = 0;
  std::uint64_t completed_nodes = 0;
  std::uint64_t compared_characters = 0;
  std::size_t peak_depth = 0;
};

class StructuralKeyMachine {
 public:
  // Preconditions: tree is nonnull and P02 has checked it against the original
  // binding. That binding/context is part of the caller's future cache key; this
  // structural token alone is not globally unique or proof authority.
  StructuralKeyMachine(std::shared_ptr<const FreeConnexTree>,
                       std::shared_ptr<ContentBudget>);
  ~StructuralKeyMachine();
  StructuralKeyMachine(StructuralKeyMachine&&) noexcept;
  StructuralKeyMachine& operator=(StructuralKeyMachine&&) noexcept;
  StructuralKeyMachine(const StructuralKeyMachine&) = delete;
  StructuralKeyMachine& operator=(const StructuralKeyMachine&) = delete;

  // One saved producer_cursor operation per successful call. UnitContext is
  // only the delegated logical-depth ceiling; there is no clock or work facade.
  // std::bad_alloc escapes with the same operation pending for retry.
  KeyStep step(const continuation_detail::UnitContext&);
  std::shared_ptr<const std::string> key() const noexcept;
  const KeyStatistics& statistics() const noexcept;
  std::size_t current_depth() const noexcept;
  bool cancelled() const noexcept;
  void cancel() noexcept;

 private:
  struct Impl;
  std::unique_ptr<Impl> data_;
};

}  // namespace crown::planner::alternatives_proposal
