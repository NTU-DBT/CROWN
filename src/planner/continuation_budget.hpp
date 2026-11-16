#pragma once

#include "crown/planner/search.hpp"

#include <algorithm>
#include <limits>

namespace crown::planner::continuation_detail {
inline bool valid_ceiling(const PhaseCeiling& limit) noexcept {
  return !limit.active_time || limit.active_time->count() >= 0;
}
template <class T>
bool monotone_ceiling(const std::optional<T>& old_value,
                      const std::optional<T>& new_value) noexcept {
  if (!old_value) return !new_value;
  return !new_value || *new_value >= *old_value;
}
inline bool monotone_phase(const PhaseCeiling& old_value,
                          const PhaseCeiling& new_value) noexcept {
  return monotone_ceiling(old_value.work, new_value.work) &&
         monotone_ceiling(old_value.active_time, new_value.active_time);
}
inline void saturating_add(std::uint64_t& target, std::uint64_t amount) noexcept {
  const auto maximum = std::numeric_limits<std::uint64_t>::max();
  target = amount > maximum - target ? maximum : target + amount;
}
// Producer/replay ceilings count attempted transitions and active nanoseconds
// separately. They do not account allocator bytes or all work within a transition.
struct ResourceLedger {
  PhaseCeiling limit;
  WorkCounters counters;

  explicit ResourceLedger(PhaseCeiling value) noexcept : limit(value) {}
  StopReason check() const noexcept {
    if (limit.work && counters.attempted >= *limit.work) return StopReason::total_work;
    if (limit.active_time && counters.active_nanoseconds >=
        static_cast<std::uint64_t>(limit.active_time->count())) return StopReason::total_time;
    if (counters.attempted == std::numeric_limits<std::uint64_t>::max())
      return StopReason::counter_overflow;
    return StopReason::none;
  }
  void active(std::chrono::steady_clock::duration elapsed) noexcept {
    const auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(elapsed).count();
    if (ns > 0) saturating_add(counters.active_nanoseconds, static_cast<std::uint64_t>(ns));
  }
  void depth(std::size_t current) noexcept {
    counters.current_depth = current;
    counters.peak_depth = std::max(counters.peak_depth, current);
  }
  bool below_consumed(const PhaseCeiling& value) const noexcept {
    return (value.work && *value.work < counters.attempted) ||
           (value.active_time && static_cast<std::uint64_t>(value.active_time->count()) <
            counters.active_nanoseconds);
  }
};

// Clock samples cover active advance execution only. Admission, caller pauses,
// serialization and cancellation/destruction are separate explicit costs.
class ActiveMeter {
 public:
  explicit ActiveMeter(ResourceLedger& ledger) noexcept
      : ledger_(&ledger), last_(std::chrono::steady_clock::now()) {}
  ~ActiveMeter() { sample(); }
  void sample() noexcept {
    const auto now = std::chrono::steady_clock::now();
    ledger_->active(now - last_);
    last_ = now;
  }
  void switch_to(ResourceLedger& ledger) noexcept { sample(); ledger_ = &ledger; }
 private:
  ResourceLedger* ledger_;
  std::chrono::steady_clock::time_point last_;
};
}  // namespace crown::planner::continuation_detail
