#pragma once
#include <array>
#include <cstddef>
#include <cstdint>
#include <span>
#include <vector>

// Excluded preparatory internal component. No native owner/report integration.
namespace crown::runtime::statistics_collection {
using U64 = std::uint64_t;
enum class Kind { physical, occurrence, support, degree };
enum class Operation { insert, erase };
enum class Mode { off, counters };
struct Descriptor {
  Kind kind{};
  U64 table{}, scope{}; // admitted identity; scope distinguishes node/edge/role
  Operation operation{};
  bool operator==(const Descriptor&) const = default;
};
struct Options {
  Mode mode{Mode::off};
  std::size_t max_cells{4096};
  U64 period{1}, offset{}, detail_budget{65536};
};
// Saturation means numeric lower bounds; no derived exact mean may be claimed.
struct Cell {
  U64 inputs{}, changed{}, noop{}, visited{}, accepted{}, rejected{};
  U64 changes{}, zero_to_positive{}, positive_to_zero{};
  std::array<U64,65> bins{};
  U64 count{}, sum{}, min{}, max{};
  bool saturated{};
  void observe(U64 value) noexcept;
  void merge(const Cell&) noexcept;
};
struct Metadata {
  U64 attempts{}, committed{}, aborted{}, selected{}, complete{};
  U64 aborted_selected{}, truncated{}, committed_truncated{};
  U64 guards{}, detail_actions{}, cleared_cells{}, merged_cells{};
  bool saturated{}, invalid_descriptor{}, protocol_error{}, ordinal_exhausted{};
};
struct Ticket { U64 serial{}, depth{}, parent{}; };
struct Memory {
  std::size_t object_bytes{}, descriptors_bytes{}, committed_bytes{}, attempt_bytes{}, previous_bytes{};
  std::size_t retained_payload_bytes{};
};
class Collector {
 public:
  Collector() = default;
  Collector(const Collector&) = delete;
  Collector& operator=(const Collector&) = delete;
  Collector(Collector&&) = delete;
  Collector& operator=(Collector&&) = delete;
  // Explicit quiescent allocating barrier. Throws on invalid config/OOM;
  // old collector is intact. Descriptor IDs are positions in this span.
  void configure(Options, std::span<const Descriptor>);
  Ticket begin(std::size_t physical_descriptor, bool changed) noexcept;
  Ticket nest(Ticket parent) noexcept;
  bool finish(Ticket, bool commit) noexcept;
  void occurrence(std::size_t descriptor, bool accepted) noexcept;
  void support(std::size_t descriptor, U64 before, U64 after) noexcept;
  void degree(std::size_t descriptor, U64 value) noexcept;
  bool reset() noexcept;
  // Caller must invoke only after a SUCCESSFUL semantic mode switch.
  bool rotate(U64 resolved_configuration) noexcept;
  std::span<const Cell> committed() const noexcept { return committed_; }
  std::span<const Cell> previous() const noexcept { return previous_; }
  std::span<const Descriptor> descriptors() const noexcept { return descriptors_; }
  const Metadata& metadata() const noexcept { return meta_; }
  const Metadata& previous_metadata() const noexcept { return previous_meta_; }
  const Options& options() const noexcept { return options_; }
  Memory memory() const noexcept;
  bool pending() const noexcept { return depth_ != 0; }
  bool has_previous() const noexcept { return has_previous_; }
  bool replaced_history() const noexcept { return replaced_history_; }
  U64 generation() const noexcept { return generation_; }
  bool generation_saturated() const noexcept { return generation_saturated_; }
  U64 configuration() const noexcept { return configuration_; }
  U64 previous_configuration() const noexcept { return previous_configuration_; }
 private:
  friend struct CollectorTestAccess; // standalone boundary injection only; no public setter
  Cell* detail(std::size_t, Kind) noexcept;
  void clear(std::vector<Cell>&) noexcept;
  Options options_{};
  std::vector<Descriptor> descriptors_;
  std::vector<Cell> committed_, attempt_, previous_;
  Metadata meta_{}, previous_meta_{};
  U64 serial_{}, active_serial_{}, depth_{}, ordinal_{}, actions_{}, generation_{};
  U64 configuration_{}, previous_configuration_{};
  std::size_t physical_{};
  bool selected_{}, truncated_{}, poisoned_{}, ordinal_done_{};
  bool generation_saturated_{}, has_previous_{}, replaced_history_{};
};
} // namespace crown::runtime::statistics_collection
