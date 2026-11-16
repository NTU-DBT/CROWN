#pragma once

#include "crown/runtime/delta.hpp"
#include <array>
#include <span>
#include <vector>

namespace crown::runtime { class QuerySession; }
namespace crown::runtime::workload {
using U64 = std::uint64_t;
enum class Kind { physical, occurrence, support, degree, logical };
enum class Operation { insert, erase };
// Timed collection is deliberately not implemented. These modes read no clocks.
enum class Mode { off, counters };
enum class InputScope { physical_table, logical_epoch };
enum class Role { input, adapter, derivation, survivor, parent_support, visible_support,
                  native_touched_degree, generalized_probe };
struct Descriptor {
  Kind kind{};
  U64 table{}, scope{};
  Operation operation{};
  InputScope input_scope{InputScope::physical_table};
  Role role{Role::input};
  std::optional<NodeId> node{};
  std::optional<OccurrenceId> occurrence{};
  std::optional<std::size_t> edge{};
  std::optional<IndexRequirementId> index{};
  std::optional<Operation> event_operation{};
  [[nodiscard]] std::optional<TableId> initiating_table() const noexcept {
    return input_scope==InputScope::physical_table?std::optional<TableId>{{table}}:std::nullopt;
  }
  bool operator==(const Descriptor&) const = default;
};
struct Options {
  Mode mode{Mode::off};
  std::size_t max_cells{4096};
  U64 period{1}, offset{}, detail_budget{65536};
  bool operator==(const Options&) const = default;
};
// Numeric payload; snapshots expose only const spans. Histogram population is
// event after-values (support) or one actual child-event degree (degree).
// Bin 0 is zero; bins 1..64 are [2^(b-1),2^b-1]. Empty extrema are unavailable.
struct Cell {
  U64 inputs{}, changed{}, noop{}, visited{}, accepted{}, rejected{};
  // Root cells only: committed, selected, untruncated detail samples. Selected
  // no-ops are included; aborted/truncated attempts never enter this count.
  U64 complete_detail_inputs{};
  U64 changes{}, zero_to_positive{}, positive_to_zero{};
  std::array<U64,65> bins{};
  U64 count{}, sum{}, min{}, max{};
  bool saturated{};
  void observe(U64) noexcept;
  void merge(const Cell&) noexcept;
  bool operator==(const Cell&) const = default;
};
struct Metadata {
  U64 attempts{}, committed{}, aborted{}, selected{}, complete{};
  U64 aborted_selected{}, truncated{}, committed_truncated{};
  U64 guards{}, detail_actions{}, cleared_cells{}, merged_cells{};
  bool saturated{}, invalid_descriptor{}, protocol_error{}, ordinal_exhausted{};
};
struct Memory {
  std::size_t object_bytes{}, descriptors_bytes{}, committed_bytes{}, attempt_bytes{}, previous_bytes{};
  std::size_t retained_payload_bytes{}, routes_bytes{};
};
struct ModeFacts {
  bool delta_owner{};
  DeltaMode requested_mode{DeltaMode::maintenance}, resolved_mode{DeltaMode::maintenance};
  DeltaCompletion requested_completion{DeltaCompletion::automatic}, resolved_completion{DeltaCompletion::automatic};
  LiveMaintenance live_maintenance{LiveMaintenance::on_output};
  ResultView view{ResultView::sql};
  bool operator==(const ModeFacts&) const = default;
};
struct Stamp {
  SupportOwnerId owner;
  U64 committed_epoch{}, interval_start_epoch{}, reset_generation{}, configuration_generation{}, segment{};
  U64 format_version{1};
  bool reset_saturated{}, configuration_saturated{}, segment_saturated{};
};
enum class Availability { disabled, unavailable, exact, sampled, incomplete, lower_bound };
enum class DenominatorScope { unavailable, all_committed_physical_inputs,
    committed_physical_stratum, complete_detail_sample_physical_stratum,
    observed_support_count_changes, observed_visited_routes };
struct Fraction {
  U64 numerator{}, denominator{};
  Availability availability{Availability::unavailable};
  DenominatorScope denominator_scope{DenominatorScope::unavailable};
};
namespace detail { class State; }
// Factory-produced owning handle. The private immutable payload contains only
// numeric copies and owning plan metadata: never rows, runtime pointers or pins.
class Snapshot {
 public:
  Snapshot(const Snapshot&) noexcept = default;
  // Copy-like moves keep both factory-produced handles readable.
  Snapshot(Snapshot&& value) noexcept :data_(value.data_) {}
  Snapshot& operator=(const Snapshot&) noexcept = default;
  Snapshot& operator=(Snapshot&& value) noexcept { data_=value.data_; return *this; }
  [[nodiscard]] const PhysicalPlan& plan() const noexcept;
  [[nodiscard]] const Stamp& stamp() const noexcept;
  [[nodiscard]] const Options& options() const noexcept;
  [[nodiscard]] const ModeFacts& modes() const noexcept;
  [[nodiscard]] const ModeFacts& previous_modes() const noexcept;
  [[nodiscard]] std::span<const Descriptor> descriptors() const noexcept;
  [[nodiscard]] std::span<const Cell> cells() const noexcept;
  [[nodiscard]] std::span<const Cell> previous_cells() const noexcept;
  [[nodiscard]] const Metadata& metadata() const noexcept;
  [[nodiscard]] const Metadata& previous_metadata() const noexcept;
  [[nodiscard]] const Memory& memory() const noexcept;
  [[nodiscard]] bool pending() const noexcept;
  [[nodiscard]] bool has_previous() const noexcept;
  [[nodiscard]] bool replaced_history() const noexcept;
  [[nodiscard]] U64 previous_interval_start_epoch() const noexcept;
  [[nodiscard]] U64 previous_interval_end_epoch() const noexcept;
  [[nodiscard]] Availability detail_availability() const noexcept;
  // input_share uses ALL committed physical inputs. Detail event means use
  // the matching initiating table/op's committed complete-sample inputs,
  // including selected no-ops. No sampled population mean is claimed.
  // Lower-only logical scopes have no physical denominator. Overflowed raw
  // counters remain visible, but a ratio of capped counts is unavailable.
  [[nodiscard]] Fraction input_share(std::size_t descriptor) const noexcept;
  [[nodiscard]] Fraction events_per_physical_input(std::size_t descriptor) const noexcept;
  [[nodiscard]] Fraction crossing_fraction(std::size_t descriptor) const noexcept;
  [[nodiscard]] Fraction adapter_selectivity(std::size_t descriptor) const noexcept;
  [[nodiscard]] Availability arrival_per_second() const noexcept { return Availability::unavailable; }
 private:
  friend class detail::State;
  friend class ::crown::runtime::QuerySession;
  [[nodiscard]] Snapshot with_pending() const;
  struct Data;
  explicit Snapshot(std::shared_ptr<const Data> value) noexcept : data_(std::move(value)) {}
  std::shared_ptr<const Data> data_;
};
} // namespace crown::runtime::workload
