#pragma once
#include "statistics_collection.hpp"

namespace crown::runtime::workload::detail {
using Ticket=statistics_collection::Ticket;
class State {
 public:
  void configure(const PhysicalPlan&, bool physical, const Options&, U64 sequence);
  void reset(U64 sequence) noexcept;
  [[nodiscard]] Options options() const noexcept { return collector_.options(); }
#ifdef CROWN_RUNTIME_TESTING
  void seed_report_saturation() noexcept {
    collector_.seed_report_saturation();configuration_generation_=UINT64_MAX;configuration_saturated_=true;
    segment_=UINT64_MAX;segment_saturated_=true;
  }
#endif
  [[nodiscard]] Snapshot snapshot(const PhysicalPlan&, SupportOwnerId, U64 sequence, bool pending=false) const;
  [[nodiscard]] Ticket physical(TableId,SetOperation) noexcept;
  [[nodiscard]] Ticket logical(SetOperation) noexcept;
  void physical_fact(bool changed) noexcept;
  void logical_fact(Ticket,bool changed) noexcept;
  void finish(Ticket,bool commit) noexcept;
  void occurrence(OccurrenceId,bool accepted) noexcept;
  void derivation(OccurrenceId,U64 before,U64 after) noexcept;
  void support(NodeId,SupportRole,U64 before,U64 after) noexcept;
  void touched(std::size_t edge,bool appeared,U64 degree) noexcept;
  // Initial binding does not rotate a stream; constructor replay stays off.
  void modes(ModeFacts,U64 sequence,bool initial=false) noexcept;
 private:
#ifdef CROWN_RUNTIME_TESTING
  friend struct StateTestAccess; // Numeric boundary injection in standalone tests only.
#endif
  static constexpr std::size_t absent=std::numeric_limits<std::size_t>::max();
  [[nodiscard]] std::size_t route(std::size_t local) const noexcept;
  [[nodiscard]] Ticket enter(std::size_t group) noexcept;
  statistics_collection::Collector collector_;
  std::vector<std::size_t> routes_;
  std::size_t stride_{}, active_group_{}, occurrence_offset_{1}, derivation_offset_{1}, survivor_offset_{1}, parent_offset_{1}, visible_offset_{1}, edge_offset_{1};
  bool physical_owner_{}, modes_bound_{};
  ModeFacts modes_{}, previous_modes_{};
  U64 configuration_generation_{}, segment_{}, interval_start_{}, previous_start_{}, previous_end_{};
  bool configuration_saturated_{}, segment_saturated_{};
};
} // namespace crown::runtime::workload::detail
