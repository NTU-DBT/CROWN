#pragma once

#include "crown/ir/update_pattern.hpp"
#include <optional>

namespace crown::runtime {
// Admission copies requested rules into the original query account under this
// finite metadata grant. Only rejection is implemented; no dormant policies.
struct UpdatePatternOptions {
  patterns::Declaration declaration;
  patterns::Limits capture_limits;
};
enum class PatternViolationKind { erase_command, physical_erase, fifo_scope };
// Fixed diagnostic, filled before throwing a semantic error. It owns no row.
struct PatternViolation {
  PatternViolationKind kind = PatternViolationKind::erase_command;
  TableId table{};
  std::uint64_t command_sequence = 0, label = 0;
  bool operator==(const PatternViolation&) const = default;
};
enum class PatternHistory { current_session, restored_checkpoint };
enum class PatternInsertionPolicy { reject_erase_commands, reject_lifetime_termination };

// Ordinary committed diagnostic, not structural proof or a CPU/delay theorem.
// Declaration copies retain its original funded immutable owner. A restored
// history is explicitly identified; its prefix assumes a trusted checkpoint.
struct UpdatePatternStatus {
  patterns::Declaration declaration;
  PatternHistory history = PatternHistory::current_session;
  PatternInsertionPolicy insertion = PatternInsertionPolicy::reject_erase_commands;
  std::uint64_t origin_sequence = 0, origin_command_sequence = 0;
  std::uint64_t monitored_sequence = 0, completed_command_sequence = 0;
  std::array<char, 64> physical_sha256{};
  std::optional<PatternViolation> violation;
};
} // namespace crown::runtime
