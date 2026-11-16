#pragma once
#include "crown/runtime/workload_statistics.hpp"
#include <array>
#include <cstddef>
#include <cstdint>
#include <span>
#include <vector>

// Bounded component extended from the accepted warning-only proposal.
namespace crown::runtime::statistics_collection {
using workload::U64;
using workload::Kind;
using workload::Operation;
using workload::Mode;
using workload::Descriptor;
using workload::Options;
using workload::Cell;
using workload::Metadata;
using workload::Memory;
struct Ticket { U64 serial{}, depth{}, parent{}; };
class Collector {
 public:
  Collector() = default;
  Collector(const Collector&) = delete;
  Collector& operator=(const Collector&) = delete;
  Collector(Collector&&) = delete;
  Collector& operator=(Collector&&) = delete;
  // Explicit quiescent allocating barrier. Throws on invalid config/OOM;
  // old collector is intact. Descriptor IDs are positions in this span.
  void configure(Options, std::span<const Descriptor>, std::size_t external_bytes=0);
  // Root admission precedes source membership lookup in Delta. Actual facts
  // are supplied once, later, without allocation. Logical roots are distinct.
  Ticket admit(std::size_t root_descriptor) noexcept;
  void physical_fact(bool changed) noexcept;
  void logical_fact(bool changed) noexcept;
  Ticket current_ticket() const noexcept { return {active_serial_,depth_,0}; }
  Ticket begin(std::size_t physical_descriptor, bool changed) noexcept;
  Ticket nest(Ticket parent) noexcept;
  bool finish(Ticket, bool commit) noexcept;
  void occurrence(std::size_t descriptor, bool accepted) noexcept;
  void support(std::size_t descriptor, U64 before, U64 after) noexcept;
  void degree(std::size_t descriptor, U64 value) noexcept;
  bool reset() noexcept;
  // Caller must invoke only after a SUCCESSFUL semantic mode switch.
  bool rotate(U64 resolved_configuration, bool force=false) noexcept;
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
  bool input_staged_{};
  bool generation_saturated_{}, has_previous_{}, replaced_history_{};
};
} // namespace crown::runtime::statistics_collection
