#pragma once
// Cycle-counter clock for the harnesses' per-phase timers. A steady_clock read
// costs ~20 ns (vDSO clock_gettime); the replay loops read the clock several
// times per relation update, which made the timers a visible share of short
// runs. The TSC is invariant on the measurement hosts (constant_tsc,
// nonstop_tsc); one ~5 ms calibration against steady_clock at start converts
// ticks to nanoseconds. Process end-to-end time is measured outside (GNU time).
#include <chrono>
#include <cstdint>
#if defined(__x86_64__) || defined(__i386__)
#include <x86intrin.h>
#endif

namespace paper_clock {
struct TickClock {
  struct time_point { std::uint64_t ticks; };
  static time_point now() noexcept {
#if defined(__x86_64__) || defined(__i386__)
    return {__rdtsc()};
#else
    return {static_cast<std::uint64_t>(std::chrono::steady_clock::now().time_since_epoch().count())};
#endif
  }
};
inline double calibrate() {
#if defined(__x86_64__) || defined(__i386__)
  using steady = std::chrono::steady_clock;
  const auto s0 = steady::now();
  const auto c0 = __rdtsc();
  while (steady::now() - s0 < std::chrono::milliseconds(5)) {}
  const auto s1 = steady::now();
  const auto c1 = __rdtsc();
  return std::chrono::duration<double, std::nano>(s1 - s0).count() / static_cast<double>(c1 - c0);
#else
  return 1.0;
#endif
}
inline const double ns_per_tick = calibrate();
inline std::uint64_t elapsed(TickClock::time_point begin, TickClock::time_point end) noexcept {
  return static_cast<std::uint64_t>(static_cast<double>(end.ticks - begin.ticks) * ns_per_tick);
}
inline std::uint64_t nanos(TickClock::time_point begin) noexcept {
  const auto ticks = TickClock::now().ticks - begin.ticks;
  return static_cast<std::uint64_t>(static_cast<double>(ticks) * ns_per_tick);
}
}  // namespace paper_clock
