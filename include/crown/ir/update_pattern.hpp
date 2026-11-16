#pragma once

// Source-bound assumptions, independent of planner ranking and runtime state.
// Usage, ownership and costs: docs/update_patterns.md and the per-file code spec.
#include "crown/ir/ids.hpp"
#include <array>
#include <exception>
#include <memory>
#include <span>
#include <vector>

namespace crown {
class CompiledProgram;
namespace resource { class MemoryAccount; }
}
namespace crown::patterns {
namespace detail { struct Data; struct Factory; }

// insertion_only forbids ending a physical full-row lifetime. Zero means no
// FIFO scope; equal positive IDs explicitly name one joint scope. One rule per
// table prevents inference of unions between overlapping scope declarations.
struct TableRule {
  TableId table;
  bool insertion_only = false;
  std::uint64_t fifo_scope = 0;
  bool operator==(const TableRule&) const = default;
};
// Logical construction limits; the actual receiving account is a separate cap.
struct Limits {
  std::uint64_t work = 1'000'000, cells = 1'000'000, payload_bytes = 16 * 1024 * 1024;
};
struct Usage {
  std::uint64_t work = 0, cells = 0, payload_bytes = 0;
  bool operator==(const Usage&) const = default;
};
enum class Fault { invalid_declaration, work_limit, cell_limit, byte_limit };
// Fixed diagnostics cross this construction boundary without allocating text.
class Failure final : public std::exception {
 public:
  explicit Failure(Fault fault) noexcept : fault_(fault) {}
  [[nodiscard]] Fault fault() const noexcept { return fault_; }
  [[nodiscard]] const char* what() const noexcept override {
    return "invalid update-pattern declaration or processing limit";
  }
 private:
  Fault fault_;
};
// Ordinary caller-owned import/export DTO; it grants no runtime authority.
struct Record {
  std::array<char, 64> source_sha256{};
  std::uint64_t source_tables = 0;
  std::vector<TableRule> rules;
};

// A validated declaration is a requested assumption, never observed history or
// a theorem token. Import validates shape; matches() checks the actual compiler
// source. Copies share immutable storage funded by its original account.
class Declaration {
 public:
  Declaration() noexcept = default;
  [[nodiscard]] static Declaration capture(const resource::MemoryAccount& account,
      const CompiledProgram& source, std::span<const TableRule> rules, const Limits& limits = {});
  [[nodiscard]] static Declaration import(const resource::MemoryAccount& account,
      const Record& record, const Limits& limits = {});
  // Caller pre-admits copy_usage(); the receiving allocator still enforces its cap.
  [[nodiscard]] static Declaration copy_of(const resource::MemoryAccount& account, const Declaration& source);
  // Bounded admission variant; checks copy_usage before any new allocation.
  [[nodiscard]] static Declaration copy_of(const resource::MemoryAccount& account,
      const Declaration& source, const Limits& limits);
  // Funded decoder input without an intermediate ordinary Record vector.
  [[nodiscard]] static Declaration import(const resource::MemoryAccount& account,
      std::array<char, 64> source_sha256, std::uint64_t source_tables,
      std::span<const TableRule> rules, const Limits& limits = {});
  // Explicit O(R) caller-owned allocation/copy; std::bad_alloc may propagate.
  [[nodiscard]] Record export_record() const;
  [[nodiscard]] explicit operator bool() const noexcept { return bool(data_); }
  [[nodiscard]] bool matches(const CompiledProgram& source) const noexcept;
  [[nodiscard]] bool constrained() const noexcept;
  [[nodiscard]] std::uint64_t source_tables() const noexcept;
  [[nodiscard]] Usage captured_usage() const noexcept;
  [[nodiscard]] Usage copy_usage() const noexcept;
  // Views/pointers borrow this handle's storage; temporary-handle borrows are deleted.
  [[nodiscard]] std::span<const TableRule> rules() const & noexcept;
  std::span<const TableRule> rules() const && = delete;
  [[nodiscard]] const TableRule* find(TableId table) const & noexcept;
  const TableRule* find(TableId) const && = delete;
  [[nodiscard]] const std::array<char, 64>& source_sha256() const &;
  const std::array<char, 64>& source_sha256() const && = delete;
 private:
  friend struct detail::Factory;
  explicit Declaration(std::shared_ptr<const detail::Data> data) noexcept : data_(std::move(data)) {}
  std::shared_ptr<const detail::Data> data_;
};
} // namespace crown::patterns
